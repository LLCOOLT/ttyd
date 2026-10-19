#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "string.h"
#include "mario/mariost.h"
#include "dolphin/os.h"
#include "stdlib.h"
#include "memory.h"
#include "pmario_sound.h"
#include "system.h"
#include "dolphin/mtx.h"
#include "driver/camdrv.h"
#include "mario/mario.h"
#include "party/party_cloud.h"
#include "driver/npcdrv.h"
#include "driver/hitdrv.h"
#include "driver/dispdrv.h"
#include "party.h"
#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
__declspec(section ".rodata") extern const f32 vec3_tou_0000d028[3];
__declspec(section ".rodata") extern const f32 vec3_tou_0000d034[3];
__declspec(section ".rodata") extern const f32 vec3_tou_0000d040[3];
__declspec(section ".rodata") extern const f32 vec3_tou_0000d04c[3];
__declspec(section ".rodata") extern const f32 vec3_tou_0000d058[3];
__declspec(section ".rodata") extern const f32 vec3_tou_0000d064[3];
__declspec(section ".rodata") extern const f32 zero_tou_0000d328;
__declspec(section ".rodata") extern const f32 float_6p2832_tou_0000d32c;
__declspec(section ".rodata") extern const f32 float_90_tou_0000d330;
__declspec(section ".rodata") extern const f32 float_360_tou_0000d334;
__declspec(section ".rodata") extern const f32 float_0p00761_tou_0000d338;
__declspec(section ".rodata") extern const f32 float_0p16605_tou_0000d33c;
__declspec(section ".rodata") extern const f32 float_1_tou_0000d340;
__declspec(section ".rodata") extern const f32 float_3p1416_tou_0000d344;
__declspec(section ".rodata") extern const f32 float_1p5708_tou_0000d348;
__declspec(section ".rodata") extern const f32 float_4p7124_tou_0000d34c;
__declspec(section ".rodata") extern const f32 float_35_tou_0000d350;
__declspec(section ".rodata") extern const f32 float_0p03705_tou_0000d354;
__declspec(section ".rodata") extern const f32 float_0p4967_tou_0000d358;
__declspec(section ".rodata") extern const f32 float_65_tou_0000d35c;
__declspec(section ".rodata") extern const f32 float_30_tou_0000d360;
__declspec(section ".rodata") extern const f32 float_60_tou_0000d364;
__declspec(section ".rodata") extern const f32 float_1000_tou_0000d368;
__declspec(section ".rodata") extern const f64 double_to_int_tou_0000d370;
__declspec(section ".rodata") extern const f32 float_0p1_tou_0000d378;
__declspec(section ".rodata") extern const f32 float_900_tou_0000d37c;
__declspec(section ".rodata") extern const f32 float_5_tou_0000d380;
__declspec(section ".rodata") extern const char tou_02_str_00004A54[28];
__declspec(section ".rodata") extern const f32 float_32767_tou_0000d3a0;
__declspec(section ".rodata") extern const f32 float_135_tou_0000d3a4;
__declspec(section ".rodata") extern const f32 float_400_tou_0000d3a8;
__declspec(section ".rodata") extern const f32 float_100_tou_0000d3ac;
__declspec(section ".rodata") extern const f32 float_neg100_tou_0000d3b0;
__declspec(section ".rodata") extern const f32 float_4_tou_0000d3b4;
__declspec(section ".rodata") extern const f32 float_2_tou_0000d3b8;
__declspec(section ".rodata") extern const f32 float_0p5_tou_0000d3bc;
__declspec(section ".rodata") extern const f32 float_0p03_tou_0000d3c0;
__declspec(section ".rodata") extern const f32 float_25_tou_0000d3c4;
__declspec(section ".rodata") extern const f32 float_0p6_tou_0000d3c8;
__declspec(section ".rodata") extern const f32 float_neg350_tou_0000d3cc;
__declspec(section ".rodata") extern const f32 float_350_tou_0000d3d0;
__declspec(section ".rodata") extern const f32 float_195_tou_0000d3d4;
__declspec(section ".rodata") extern const u32 zero_tou_0000d3d8;
__declspec(section ".rodata") extern const f32 float_200_tou_0000d3dc;
__declspec(section ".rodata") extern const char tou_02_str_00004AB0[24];
#endif
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)
#pragma force_active on
u32 gap_05_00000024_bss[1];
extern const char tou_02_str_0000455C[];
extern const char tou_02_str_00004564[];
extern const char tou_02_str_00004570[];
extern const char tou_02_str_00004580[];
extern const char tou_02_str_0000459C[];
extern const char tou_02_str_000045A8[];
extern const char tou_02_str_000045B4[];
extern const char tou_02_str_000045E8[];
extern const char tou_02_str_000045F4[];
extern const char str_00004600[];
extern const char tou_02_str_00003BC0[];
extern const char tou_02_str_00003BD4[];
extern const char tou_02_str_00003BE0[];
extern const char str_00003BEC[];
extern const char tou_02_str_00003BF8[];
extern const char tou_02_str_00003C04[];
extern const char tou_02_str_00003C10[];
extern const char tou_02_str_00003C1C[];
extern const char tou_02_str_00003C24[];
extern const char tou_02_str_00003C2C[];
extern const char str_00003C34[];
extern const char tou_02_str_00003C3C[];
extern const char tou_02_str_00003C48[];
extern const char tou_02_str_00003C54[];
extern const char str_00003C5C[];
extern const char tou_02_str_00003C68[];
extern const char tou_02_str_00003C74[];
extern const char tou_02_str_00003C80[];
extern const char tou_02_str_00003C8C[];
extern const char tou_02_str_00003C94[];
extern const char tou_02_str_00003C9C[];
extern const char tou_02_str_00003CA8[];
extern const char tou_02_str_00003CB0[];
extern const char tou_02_str_00003CB4[];
extern const char tou_02_str_00003CC4[];
extern const char tou_02_str_00003CCC[];
extern const char tou_02_str_00003CDC[];
extern const char tou_02_str_00003CE8[];
extern const char tou_02_str_00003CF4[];
extern const char tou_02_str_00003D04[];
extern const char tou_02_str_00003D14[];
extern const char tou_02_str_00003D28[];
extern const char tou_02_str_00003D38[];
extern const char tou_02_str_00003D48[];
extern const char tou_02_str_00003D5C[];
extern const char tou_02_str_00003D70[];
extern const char str_00003D84[];
extern const char tou_02_str_00003D98[];
extern const char tou_02_str_00003DAC[];
extern const char tou_02_str_00003DC0[];
extern const char tou_02_str_00003DD4[];
extern const char tou_02_str_00003DE8[];
extern const char tou_02_str_00003DFC[];
extern const char tou_02_str_00003E10[];
extern const char str_00003E24[];
extern const char tou_02_str_00003E38[];
extern const char tou_02_str_00003E4C[];
extern const char str_00003E60[];
extern const char tou_02_str_00003E70[];
extern const char tou_02_str_00003E84[];
extern const char tou_02_str_00003E94[];
extern const char tou_02_str_00003EA8[];
extern const char tou_02_str_00003EBC[];
extern const char tou_02_str_00003ED0[];
extern const char tou_02_str_00003EE4[];
extern const char tou_02_str_00003EF8[];
extern const char tou_02_str_00003F0C[];
extern const char tou_02_str_00003F20[];
extern const char tou_02_str_00003F30[];
extern const char tou_02_str_00003F44[];
extern const char str_00003F54[];
extern const char tou_02_str_00003F68[];
extern const char tou_02_str_00003F7C[];
extern const char tou_02_str_00003F90[];
extern const char tou_02_str_00003FA4[];
extern const char tou_02_str_00003FB8[];
extern const char tou_02_str_00003FCC[];
extern const char tou_02_str_00003FE0[];
extern const char tou_02_str_00003FF0[];
extern const char tou_02_str_00004004[];
extern const char tou_02_str_00004014[];
extern const char tou_02_str_00004028[];
extern const char tou_02_str_0000403C[];
extern const char tou_02_str_00004050[];
extern const char str_00004064[];
extern const char tou_02_str_00004078[];
extern const char tou_02_str_0000408C[];
extern const char tou_02_str_000040A0[];
extern const char tou_02_str_000040B0[];
extern const char tou_02_str_000040C4[];
extern const char str_000040D4[];
extern const char tou_02_str_000040E8[];
extern const char tou_02_str_000040FC[];
extern const char tou_02_str_00004110[];
extern const char tou_02_str_00004128[];
extern const char tou_02_str_0000413C[];
extern const char tou_02_str_00004154[];
extern const char tou_02_str_00004168[];
extern const char tou_02_str_00004180[];
extern const char tou_02_str_00004194[];
extern const char tou_02_str_000041AC[];
extern const char tou_02_str_000041C0[];
extern const char tou_02_str_000041D4[];
extern const char tou_02_str_000041E4[];
extern const char tou_02_str_000041FC[];
extern const char tou_02_str_00004210[];
extern const char tou_02_str_00004224[];
extern const char tou_02_str_00004234[];
extern const char tou_02_str_00004248[];
extern const char tou_02_str_0000425C[];
extern const char tou_02_str_00004270[];
extern const char tou_02_str_00004284[];
extern const char tou_02_str_00004298[];
extern const char tou_02_str_000042AC[];
extern const char tou_02_str_000042C0[];
extern const char tou_02_str_000042D0[];
extern const char tou_02_str_000042E4[];
extern const char str_000042F4[];
extern const char tou_02_str_00004300[];
extern const char tou_02_str_00004314[];
extern const char tou_02_str_00004328[];
extern const char tou_02_str_0000433C[];
extern const char tou_02_str_00004350[];
extern const char tou_02_str_00004364[];
extern const char tou_02_str_00004378[];
extern const char tou_02_str_0000438C[];
extern const char tou_02_str_0000439C[];
extern const char tou_02_str_000043B0[];
extern const char tou_02_str_000043C0[];
extern const char tou_02_str_000043D4[];
extern const char tou_02_str_000043E8[];
extern const char tou_02_str_000043FC[];
extern const char tou_02_str_00004410[];
extern const char tou_02_str_00004424[];
extern const char tou_02_str_00004438[];
extern const char tou_02_str_0000444C[];
extern const char tou_02_str_0000445C[];
extern const char tou_02_str_0000446C[];
extern const char tou_02_str_0000447C[];
extern const char tou_02_str_0000448C[];
extern const char tou_02_str_0000449C[];
extern const char tou_02_str_000044AC[];
extern const char tou_02_str_000044BC[];
extern const char tou_02_str_000044CC[];
extern const char tou_02_str_000044DC[];
extern const char tou_02_str_000044EC[];
extern const char tou_02_str_000044FC[];
extern const char tou_02_str_0000450C[];
extern const char tou_02_str_0000451C[];
extern const char tou_02_str_0000452C[];
extern const char tou_02_str_0000453C[];
extern const char tou_02_str_0000454C[];
extern const char tou_02_str_00004590[];
extern const char tou_02_str_000045C0[];
extern const char tou_02_str_000045D0[];
extern const char tou_02_str_000045DC[];
extern const char tou_02_str_0000460C[];
extern const char tou_02_str_00004618[];
extern const char tou_02_str_00004628[];
extern const char tou_02_str_00004638[];
extern const char tou_02_str_00004648[];
extern const char tou_02_str_00004658[];
extern const char tou_02_str_00004668[];
extern const char tou_02_str_00004678[];
extern const char tou_02_str_00004688[];
extern const char tou_02_str_000046A0[];
extern const char tou_02_str_000046A8[];
extern const char tou_02_str_000046B0[];
extern const char tou_02_str_000046BC[];
extern const char tou_02_str_000046C8[];
extern const char tou_02_str_000046D0[];
extern const char tou_02_str_000046DC[];
extern const char tou_02_str_000046E4[];
extern const char tou_02_str_000046F0[];
extern const char tou_02_str_00004740[];
extern const char tou_02_str_00004750[];
extern const char tou_02_str_00004760[];
extern const char tou_02_str_00004770[];
extern const char tou_02_str_00004780[];
extern const char tou_02_str_00004790[];
extern const char tou_02_str_000047A0[];
extern const char tou_02_str_000047A4[];
extern const char tou_02_str_000047AC[];
extern const char tou_02_str_000047B4[];
extern const char tou_02_str_000047B8[];
extern const char tou_02_str_000047C8[];
extern const char str_000047E0[];
extern const char tou_02_str_000047F8[];
extern const char tou_02_str_0000480C[];
extern const char tou_02_str_00004814[];
extern const char tou_02_str_00004828[];
extern const char tou_02_str_00004830[];
extern const char tou_02_str_00004840[];
extern const char tou_02_str_00004848[];
extern const char tou_02_str_0000485C[];
extern const char tou_02_str_00004870[];
extern const char tou_02_str_00004884[];
extern const char str_00004898[];
extern const char tou_02_str_000048AC[];
extern const char tou_02_str_000048B4[];
extern const char tou_02_str_000048C4[];
extern const char tou_02_str_000048D4[];
extern const char tou_02_str_000048E4[];
extern const char tou_02_str_000048F0[];
extern const char tou_02_str_000048F8[];
extern const char tou_02_str_00004904[];
extern const char tou_02_str_00004920[];
extern const char tou_02_str_0000493C[];
extern const char tou_02_str_00004944[];
extern const char tou_02_str_0000494C[];
extern const char tou_02_str_00004954[];
extern const char tou_02_str_0000495C[];
extern const char tou_02_str_00004964[];
extern const char tou_02_str_0000496C[];
extern const char tou_02_str_00004974[];
extern const char tou_02_str_0000497C[];
extern const char tou_02_str_00004984[];
extern const char tou_02_str_0000498C[];
extern const char tou_02_str_00004994[];
extern const char tou_02_str_0000499C[];
extern const char tou_02_str_000049A4[];
extern const char tou_02_str_000049AC[];
extern const char tou_02_str_000049B4[];
extern const char tou_02_str_000049BC[];
extern const char tou_02_str_000049C4[];
extern const char tou_02_str_000049CC[];
extern const char tou_02_str_000049D4[];
extern const char tou_02_str_000049DC[];
extern const char tou_02_str_000049E4[];
extern const char tou_02_str_000049EC[];

typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
typedef struct Fan { u16 flags; s16 state; s16 animIdx; u8 pad_0x6[2]; u64 time; Vec pos; Vec vel; f32 field_0x28; Vec target; Vec param; s16 timer; } Fan;
typedef struct FanAnim { char name[16]; char anim[8]; s16 loop; f32 rate; s32 start; s32 count; } FanAnim;
typedef struct FanWork { s32 num; Fan* fans; s32 animNum; FanAnim anim[32]; s32 hammerTimer; s32 count; s32 sfxId; u8 vol; } FanWork;
typedef struct FanData { const char* name; const char* anim; f32 rate; } FanData;
FanWork* fan_wp;
ExtPose* extGetPosePtr(void);
s32 extGetPoseNum(void);
static void pose_init(void);
static void pose_init(void);
static void pose_change(Fan* fan, const char* name, const char* anim);
static void pose_change(Fan* fan, const char* name, const char* anim);
static f32 randf(f32 min, f32 max);
static f32 randf(f32 min, f32 max);
u8 psndSFX_get_vol(s32 id);
void extLoadRenderMode(void);
void extLoadVertex(void);
void extLoadTexture(void);
void extLoadTev(void);
void extDraw(void);
void extLoadTextureExit(void);
#ifdef NONMATCHING
static inline f32 fan_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
#endif
#ifdef NONMATCHING
static inline f32 fan_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
#endif
s32 check_hammer(Fan* fan);
s32 check_hammer(Fan* fan);
void psndSFX_pos(s32 id, Vec* pos);
void psndSFX_vol(s32 id, u8 vol);
static void pose_main(void);
static void pose_main(void);
void fan_disp(CameraId camera, void* param);
void fan_disp(CameraId camera, void* param);
f32 cloudGetBreathDist(void);

s32 N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_exec_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_entername(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_info(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_mapchange(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_off(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_set(EventEntry* event, BOOL isFirstCall);
s32 evt_cloud_ent(EventEntry* event, BOOL isFirstCall);
s32 evt_cloud_init(EventEntry* event, BOOL isFirstCall);
s32 evt_eff_fukidashi(EventEntry* event, BOOL isFirstCall);
s32 evt_end_count(EventEntry* event, BOOL isFirstCall);
s32 evt_end_count(EventEntry* event, BOOL isFirstCall);
s32 evt_ext_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_fade_end_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_hitobj_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_item_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_item_get_item_end_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_item_set_bound_rate(EventEntry* event, BOOL isFirstCall);
s32 evt_item_set_gravity(EventEntry* event, BOOL isFirstCall);
s32 evt_item_set_jump_power(EventEntry* event, BOOL isFirstCall);
s32 evt_item_set_move_dir_speed(EventEntry* event, BOOL isFirstCall);
s32 evt_item_status_on(EventEntry* event, BOOL isFirstCall);
s32 evt_key_get_buttontrg(EventEntry* event, BOOL isFirstCall);
s32 evt_map_checkanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_playanim(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_rotate(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_trans(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_balloon_bikkuri(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_balloon_off(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_party(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_key_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_mov_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_mov_pos2(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_normalize(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_dir(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_party(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_pose(EventEntry* event, BOOL isFirstCall);
s32 evt_mobj_kururing_floor(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print_add(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print_insert(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print_party(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_select(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_toge(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_change_interrupt(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_move_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_reverse_ry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_scale(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_setup(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_status_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_party_get_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_move_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_run(EventEntry* event, BOOL isFirstCall);
s32 evt_party_set_dir(EventEntry* event, BOOL isFirstCall);
s32 evt_party_set_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_stop(EventEntry* event, BOOL isFirstCall);
s32 evt_party_yoshi_ride(EventEntry* event, BOOL isFirstCall);
s32 evt_pouch_all_party_recovery(EventEntry* event, BOOL isFirstCall);
s32 evt_pouch_get_yoshiname(EventEntry* event, BOOL isFirstCall);
s32 evt_pouch_mario_recovery(EventEntry* event, BOOL isFirstCall);
s32 evt_pouch_open_mail(EventEntry* event, BOOL isFirstCall);
s32 evt_pouch_receive_mail(EventEntry* event, BOOL isFirstCall);
s32 evt_pouch_remove_item(EventEntry* event, BOOL isFirstCall);
s32 evt_seq_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_set_dir_to_target(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_envon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxon_3d(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_intpl_msec_get_value(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_intpl_msec_init(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_random(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_rumble_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_tou_get_ranking_27_text_1ED4(EventEntry* event, BOOL isFirstCall);
s32 check_hammer(Fan* fan);
void ext_fan_dispent(void);
void ext_fan_dispent(void);
void ext_fan_main(void);
void ext_fan_main(void);
void fan_disp(CameraId camera, void* param);
void ext_fan_init(void);
void ext_fan_init(void);
static f32 randf(f32 min, f32 max);
static void pose_change(Fan* fan, const char* name, const char* anim);
static void pose_main(void);
static void pose_init(void);
extern s32 bero_case_entry[];
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 bero_close_door_play_se[];
extern s32 bero_open_door_play_se[];
extern s32 evt_bero_info_run[];
extern s32 evt_sub_mail_vibration[];

__declspec(section ".data") u64 fd_tou_02_negone_one_374;
__declspec(section ".data") s32 fd_tou_02_neg_one_382[1];
__declspec(section ".data") s32 fd_tou_02___local_PI_383[1];
__declspec(section ".data") s32 fd_tou_02___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tou_02_one_negone_373;
__declspec(section ".data") s32 fd_tou_02___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tou_02_one_381[1];
__declspec(section ".data") u64 fd_tou_02_negone_one_360;
__declspec(section ".data") s32 fd_tou_02_neg_one_365[1];
__declspec(section ".data") s32 fd_tou_02___local_PI_366[1];
__declspec(section ".data") s32 fd_tou_02___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tou_02_one_negone_359;
__declspec(section ".data") s32 fd_tou_02___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tou_02_one_364[1];
static s32 s_door_open[58];
static s32 s_door_close[58];
s32 n_1_door_open[22];
s32 n_1_door_close[22];
static s32 n_2_door_open[22];
static s32 n_2_door_close[22];
__declspec(section ".data") s32 n_3_door_open[12];
__declspec(section ".data") s32 n_3_door_close[12];
__declspec(section ".data") s32 n_4_door_open[12];
__declspec(section ".data") s32 n_4_door_close[12];
static s32 bero_data[90];
s32 evt_move_g[63];
s32 init_gard1[39];
s32 talk_gard1[70];
s32 init_gard2[39];
s32 talk_gard2[70];
static s32 init_madam[39];
static s32 talk_madam[67];
__declspec(section ".data") s32 init_repo[8];
s32 talk_repo[112];
__declspec(section ".data") s32 init_cam1[8];
s32 talk_cam1[112];
s32 init_cam2[19];
s32 talk_cam2[112];
s32 init_kino4[13];
s32 reg_kino4[31];
s32 talk_kino4[112];
__declspec(section ".data") s32 init_kino5[8];
s32 talk_kino5[236];
__declspec(section ".data") s32 init_kinopiko[8];
s32 talk_kinopiko[112];
__declspec(section ".data") s32 init_kinopio_f[8];
s32 talk_kinopio_f[112];
s32 init_chu[20];
s32 talk_chu[67];
static s32 init_champ[32];
s32 move_pos[26];
s32 move_champ[155];
s32 talk_champ[34];
s32 init_shikowa[32];
s32 talk_shikowa[13];
static s32 init_uranoko[32];
static s32 talk_uranoko[13];
s32 init_ironA[38];
s32 talk_ironA[13];
s32 init_ironB[38];
s32 talk_ironB[13];
s32 init_borodo[32];
s32 talk_borodo[13];
static s32 npcEnt[391];
s32 evt_tougi2[285];
s32 ext_fan_data[84];
s32 mario_momikucha_msg[111];
s32 evt_momikucha[105];
static s32 evt_key[173];
__declspec(section ".data") static s32 evt_poster_1[5];
__declspec(section ".data") static s32 evt_poster_2[5];
__declspec(section ".data") static s32 evt_poster_3[5];
__declspec(section ".data") static s32 evt_poster_4[5];
__declspec(section ".data") static s32 evt_poster_5[5];
__declspec(section ".data") static s32 evt_poster_6[5];
__declspec(section ".data") static s32 evt_poster_7[5];
static s32 evt_poster_8[46];
__declspec(section ".data") static s32 evt_poster_9[5];
static s32 evt_after_peach[188];
s32 tou_02_init_evt[576];

void C_VECReflect(const Vec* src, const Vec* normal, Vec* dst);
void PSMTXIdentity(Mtx m);
void PSVECAdd(const Vec* a, const Vec* b, Vec* ab);
f32 PSVECDistance(const Vec* a, const Vec* b);
f32 PSVECMag(const Vec* v);
void PSVECNormalize(const Vec* src, Vec* dst);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
f32 PSVECSquareDistance(const Vec* a, const Vec* b);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
int __cvt_ull_flt();
int __div2u();
s32 evtGetValue(EventEntry* entry, s32 index);
void *memset(void *dest, int ch, size_t count);
int rand(void);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
#ifdef NONMATCHING
static void pose_init(void) {
    char name[32];
    char anim[32];
    FanData* d = (FanData*)ext_fan_data;
    s32 i = 0;
    s32 start;

    strcpy(name, "");
    strcpy(anim, "");
    fan_wp->animNum = -1;
    do {
        if (strcmp(d->name, name) != 0) {
            strcpy(name, d->name);
            strcpy(anim, "");
        }
        if (strcmp(d->anim, anim) != 0) {
            strcpy(anim, d->anim);
            start = i;
            fan_wp->animNum++;
        }
        strcpy(fan_wp->anim[fan_wp->animNum].name, name);
        strcpy(fan_wp->anim[fan_wp->animNum].anim, anim);
        fan_wp->anim[fan_wp->animNum].start = start;
        fan_wp->anim[fan_wp->animNum].count = i - start + 1;
        fan_wp->anim[fan_wp->animNum].rate = d->rate;
        fan_wp->anim[fan_wp->animNum].loop = 1;
        i++;
        d++;
    } while (d->name != NULL);
    fan_wp->animNum++;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
static void pose_init(void) {
	char _af_pad[64];
	asm {
		lis r4, zero_tou_0000d3d8@ha
		lis r3, ext_fan_data@ha
		addi r0, r3, ext_fan_data@l
		la r3, _af_pad+32
		addi r4, r4, zero_tou_0000d3d8@l
	}
	asm volatile {
		opword 0x3BA00000
		opword 0x7C1E0378
		bl strcpy
		lis r4, zero_tou_0000d3d8@ha
		opword 0x38610008
		addi r4, r4, zero_tou_0000d3d8@l
		bl strcpy
		lis r3, fan_wp@ha
		opword 0x3800FFFF
		addi r31, r3, fan_wp@l
		opword 0x807F0000
		opword 0x90030008
		opword 0x807E0000
		opword 0x38810028
		bl strcmp
		opword 0x2C030000
		opword 0x41820020
		opword 0x809E0000
		opword 0x38610028
		bl strcpy
		lis r4, zero_tou_0000d3d8@ha
		opword 0x38610008
		addi r4, r4, zero_tou_0000d3d8@l
		bl strcpy
		opword 0x807E0004
		opword 0x38810008
		bl strcmp
		opword 0x2C030000
		opword 0x41820028
		opword 0x809E0004
		opword 0x38610008
		bl strcpy
		lis r3, fan_wp@ha
		mr r28, r29
		lwz r4, fan_wp@l(r3)
		opword 0x80640008
		opword 0x38030001
		opword 0x90040008
		opword 0x80BF0000
		opword 0x38810028
		opword 0x80050008
		opword 0x1C600028
		opword 0x3863000C
		opword 0x7C651A14
		bl strcpy
		opword 0x80BF0000
		opword 0x38810008
		opword 0x80050008
		opword 0x1C600028
		opword 0x3863001C
		opword 0x7C651A14
		bl strcpy
		opword 0x80DF0000
		opword 0x7C7CE850
		opword 0x38A30001
		opword 0x38800001
		opword 0x80060008
		opword 0x3BBD0001
		opword 0x1C600028
		opword 0x3803002C
		opword 0x7F86012E
		opword 0x80DF0000
		opword 0x80060008
		opword 0x1C600028
		opword 0x38030030
		opword 0x7CA6012E
		opword 0x80BF0000
		opword 0xC01E0008
		opword 0x80050008
		opword 0x1C600028
		opword 0x38030028
		opword 0x7C05052E
		opword 0x80BF0000
		opword 0x80050008
		opword 0x1C600028
		opword 0x38030024
		opword 0x7C85032E
		opword 0x841E000C
		opword 0x28000000
		opword 0x4082FEF4
		lis r3, fan_wp@ha
		lwz r4, fan_wp@l(r3)
		opword 0x80640008
		opword 0x38030001
		opword 0x90040008
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
static void pose_main(void) {
    s32 i;
    ExtPose* pose;
    Fan* fan;
    FanAnim* a;
    f32 t;

    pose = extGetPosePtr();
    fan = fan_wp->fans;

    for (i = 0; i < fan_wp->num; i++, fan++, pose++) {
        a = &fan_wp->anim[fan->animIdx];
        t = EXT_LIT(float_60_tou_0000d364, 60.0f) * OSTicksToMilliseconds((u64)(gp->renderTime - fan->time)) / EXT_LIT(float_1000_tou_0000d368, 1000.0f) / a->rate;
        if (t >= EXT_LIT(float_1_tou_0000d340, 1.0f)) {
            fan->time = gp->renderTime;
            t = EXT_LIT(zero_tou_0000d328, 0.0f);
        }
        pose->frame = a->start + (s32)((a->count - 1) * t);
    }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
static void pose_main(void) {
	char _af_pad[8];
	asm volatile {
		bl extGetPosePtr
		lis r4, fan_wp@ha
		lis r7, float_60_tou_0000d364@ha
		addi r29, r4, fan_wp@l
		lis r6, float_1000_tou_0000d368@ha
		opword 0x813D0000
		lis r5, float_1_tou_0000d340@ha
		lis r4, double_to_int_tou_0000d370@ha
		lis r8, gp@ha
		opword 0x83090004
		opword 0x7C791B78
		lfs f28, float_60_tou_0000d364@l(r7)
		addi r30, r8, gp@l
		lfs f29, float_1000_tou_0000d368@l(r6)
		opword 0x3B400000
		lfs f30, float_1_tou_0000d340@l(r5)
		opword 0x3FE08000
		lfd f31, double_to_int_tou_0000d370@l(r4)
		opword 0x3EE04330
		opword 0x480000BC
		opword 0x807F00F8
		opword 0x380003E8
		opword 0x809E0000
		opword 0x38A00000
		opword 0x5463F0BE
		opword 0xA8F80004
		opword 0x7CC30396
		opword 0x8364003C
		opword 0x8018000C
		opword 0x83840038
		opword 0x7C80D810
		opword 0x80180008
		opword 0x1CE70028
		opword 0x7C60E110
		addi r22, r7, 0xc
		opword 0x7EC8B214
		bl __div2u
		bl __cvt_ull_flt
		opword 0xEC3C0072
		opword 0xC016001C
		opword 0xEC21E824
		opword 0xEC210024
		opword 0xFC01F040
		opword 0x4C411382
		opword 0x40820014
		opword 0x9378000C
		lis r3, zero_tou_0000d328@ha
		lfs f1, zero_tou_0000d328@l(r3)
		opword 0x93980008
		opword 0x80760024
		opword 0x3B5A0001
		stw r23, _af_pad+0(r1)
		opword 0x3B180048
		opword 0x3803FFFF
		opword 0x80760020
		opword 0x6C008000
		opword 0x9001000C
		opword 0xC8010008
		opword 0xEC00F828
		opword 0xEC000072
		opword 0xFC00001E
		opword 0xD8010010
		opword 0x80010014
		opword 0x7C030214
		opword 0x90190010
		opword 0x3B390020
		opword 0x811D0000
		opword 0x80080000
		opword 0x7C1A0000
		opword 0x4180FF3C
	}
}
#pragma pop
#endif

static void pose_change(Fan* fan, const char* name, const char* anim) {
    FanAnim* a;
    s32 i;

    for (i = 0, a = fan_wp->anim; i < fan_wp->animNum; i++, a++) {
        if (strcmp(a->name, name) == 0 && strcmp(a->anim, anim) == 0) {
            break;
        }
    }
    if (i < fan_wp->animNum && fan->animIdx != i) {
        fan->animIdx = i;
        fan->time = gp->renderTime;
    }
}

#ifdef NONMATCHING
static f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return r * (max - min) + min;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
static f32 randf(f32 min, f32 max) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0xDBE10020
		opword 0xF3E10028
		opword 0xDBC10010
		opword 0xF3C10018
		opword 0xFFC00890
		opword 0xFFE01090
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061000C
		lis r4, double_to_int_tou_0000d370@ha
		lis r3, float_32767_tou_0000d3a0@ha
		lfd f3, double_to_int_tou_0000d370@l(r4)
		opword 0x90010008
		opword 0xEC1FF028
		lfs f1, float_32767_tou_0000d3a0@l(r3)
		opword 0xC8410008
		opword 0xEC421828
		opword 0xEC220824
		opword 0xEC21F03A
		opword 0xE3E10028
		opword 0xCBE10020
		opword 0xE3C10018
		opword 0x80010034
		opword 0xCBC10010
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop
#endif

__declspec(section ".data") u64 fd_tou_02_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tou_02_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tou_02___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tou_02___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tou_02_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tou_02___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tou_02_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tou_02_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tou_02_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tou_02___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tou_02___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tou_02_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tou_02___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tou_02_one_364[] = {
    1065353216,
};

static EVT_BEGIN(s_door_open)
    IF_FLOAT_EQUAL(LW(0), FLOAT((0.0f)))
        IF_INT_EQUAL(GSWF(2526), 0)
            SET_VALUE(GSWF(2526), 1)
            BEGIN_INLINE_EVENT
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING(((char*)tou_02_str_00003BC0)), LW(0), LW(1), LW(2), GW(13))
            END_INLINE_EVENT
        END_IF
    END_IF
    IF_FLOAT_EQUAL(LW(0), FLOAT(180.0f))
        SET_VALUE(GSWF(2526), 0)
        CALL(evt_snd_sfxoff, GW(13))
    END_IF
    MULTIPLY_FLOAT(LW(0), FLOAT(0.3330078f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)tou_02_str_00003BD4)), LW(0), 0, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)tou_02_str_00003BE0)), LW(0), 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(s_door_close)
    IF_FLOAT_EQUAL(LW(0), FLOAT(180.0f))
        IF_INT_EQUAL(GSWF(2526), 0)
            SET_VALUE(GSWF(2526), 1)
            BEGIN_INLINE_EVENT
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING(((char*)tou_02_str_00003BC0)), LW(0), LW(1), LW(2), GW(13))
            END_INLINE_EVENT
        END_IF
    END_IF
    IF_FLOAT_EQUAL(LW(0), FLOAT((0.0f)))
        SET_VALUE(GSWF(2526), 0)
        CALL(evt_snd_sfxoff, GW(13))
    END_IF
    MULTIPLY_FLOAT(LW(0), FLOAT(0.3330078f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)tou_02_str_00003BD4)), LW(0), 0, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)tou_02_str_00003BE0)), LW(0), 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(n_1_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00003BEC)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_02_str_00003BF8)), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(n_1_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00003BEC)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_02_str_00003BF8)), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(n_2_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_02_str_00003C04)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_02_str_00003C10)), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(n_2_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_02_str_00003C04)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_02_str_00003C10)), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n_3_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_02_str_00003C1C)), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n_3_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_02_str_00003C1C)), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n_4_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_02_str_00003C24)), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n_4_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_02_str_00003C24)), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_data[] = {
    (s32)((char*)tou_02_str_00003C2C), 65536, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)str_00003C34), (s32)((char*)tou_02_str_00003C3C), 327685, (s32)s_door_close, (s32)s_door_open, (s32)((char*)tou_02_str_00003C48),
    65542, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)((char*)tou_02_str_00003C54), (s32)((char*)str_00003C5C), 327685, (s32)n_1_door_close, (s32)n_1_door_open, (s32)((char*)tou_02_str_00003C68), 65542,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)((char*)tou_02_str_00003C54), (s32)((char*)tou_02_str_00003C74), 327685, (s32)n_2_door_close, (s32)n_2_door_open, (s32)((char*)tou_02_str_00003C80), 65540, 20000,
    100000, 0, 0, -1, 0, -1, 0, (s32)((char*)tou_02_str_00003C8C),
    (s32)((char*)tou_02_str_00003C94), 327685, (s32)n_3_door_close, (s32)n_3_door_open, (s32)((char*)tou_02_str_00003C9C), 65540, 20000, 100000,
    0, 0, -1, 0, -1, 0, (s32)((char*)tou_02_str_00003C8C), (s32)((char*)tou_02_str_00003CA8),
    327685, (s32)n_4_door_close, (s32)n_4_door_open, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

EVT_BEGIN(evt_move_g)
    CALL(evt_npc_get_position, STRING(((char*)tou_02_str_00003CB0)), LW(0), LW(1), LW(2))
    ADD(LW(2), 100)
    CALL(evt_mario_mov_pos, LW(0), LW(2), 500)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)tou_02_str_00003CB4)), -530, -185, 0, FLOAT(80.0f), 1)
        CALL(evt_set_dir_to_target, STRING(((char*)tou_02_str_00003CB4)), STRING(((char*)tou_02_str_00003CC4)))
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING(((char*)tou_02_str_00003CCC)), 530, -185, 0, FLOAT(80.0f), 1)
    CALL(evt_set_dir_to_target, STRING(((char*)tou_02_str_00003CCC)), STRING(((char*)tou_02_str_00003CC4)))
    SET_VALUE(LW(0), 3)
    CALL_CHILD(PTR(bero_case_switch_on))
    SET_VALUE(LW(0), 4)
    CALL_CHILD(PTR(bero_case_switch_on))
    IF_INT_LESS(GSW(0), 129)
        SET_VALUE(GSW(0), 129)
        ELSE
        SET_VALUE(GSWF(2497), 1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(init_gard1)
    SWITCH(GSW(0))
        CASE_LESS(129)
        CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), -470, 0, -185)
        CASE_LESS(171)
        CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), -530, 0, -185)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2497), 0)
            CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), -470, 0, -185)
            ELSE
            CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), -530, 0, -185)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_gard1)
    SWITCH(GSW(0))
        CASE_LESS(128)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003CDC)), 0, 0)
        CASE_LESS(129)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003CE8)), 0, 0)
        CALL_CHILD(PTR(evt_move_g))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003CF4)), 0, 0)
        CASE_LESS(171)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003D04)), 0, 0)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003D14)), 0, 0)
            ELSE
            IF_INT_EQUAL(GSWF(2497), 0)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003D28)), 0, 0)
                CALL_CHILD(PTR(evt_move_g))
                ELSE
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003D38)), 0, 0)
            END_IF
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_gard2)
    SWITCH(GSW(0))
        CASE_LESS(129)
        CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), 470, 0, -185)
        CASE_LESS(171)
        CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), 530, 0, -185)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2497), 0)
            CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), 470, 0, -185)
            ELSE
            CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), 530, 0, -185)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_gard2)
    SWITCH(GSW(0))
        CASE_LESS(128)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003CDC)), 0, 0)
        CASE_LESS(129)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003CE8)), 0, 0)
        CALL_CHILD(PTR(evt_move_g))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003CF4)), 0, 0)
        CASE_LESS(171)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003D04)), 0, 0)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003D14)), 0, 0)
            ELSE
            IF_INT_EQUAL(GSWF(2497), 0)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003D28)), 0, 0)
                CALL_CHILD(PTR(evt_move_g))
                ELSE
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003D38)), 0, 0)
            END_IF
        END_IF
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(init_madam)
    SWITCH(GSW(0))
        CASE_LESS(172)
        CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), 525, 0, 0)
        CASE_EQUAL(172)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), 525, 0, 0)
            ELSE
            CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), 0, -1000, 0)
        END_IF
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), 0, -1000, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_madam)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003D48)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003D5C)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003D70)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003D84)), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003D98)), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003DAC)), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003DC0)), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_repo)
    CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), -100, 0, -25)
    RETURN
EVT_END()

EVT_BEGIN(talk_repo)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003DD4)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003DE8)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003DFC)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003E10)), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003E24)), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003E38)), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003E4C)), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING(((char*)str_00003E60)), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003E70)), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003E84)), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003E70)), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_cam1)
    CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), -150, 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(talk_cam1)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003E94)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003EA8)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003EBC)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003ED0)), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003EE4)), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003EF8)), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003F0C)), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003F20)), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003F30)), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003F44)), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003F30)), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_cam2)
    IF_INT_LESS(GSW(0), 128)
        CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), 80, 200, -125)
        ELSE
        CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), 30, 200, -60)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(talk_cam2)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003F54)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003F68)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003F7C)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003F90)), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003FA4)), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003FB8)), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003FCC)), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003FE0)), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003FF0)), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004004)), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00003FF0)), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_kino4)
    CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), -350, 0, 75)
    CALL(evt_npc_status_onoff, 1, STRING(((char*)tou_02_str_00003CB0)), 2)
    RETURN
EVT_END()

EVT_BEGIN(reg_kino4)
    LOOP(0)
        CALL(evt_npc_move_position, STRING(((char*)tou_02_str_00003CB0)), -350, 75, 0, FLOAT(48.0f), 0)
        WAIT_MS(1000)
        CALL(evt_npc_reverse_ry, STRING(((char*)tou_02_str_00003CB0)))
        CALL(evt_npc_move_position, STRING(((char*)tou_02_str_00003CB0)), 350, 75, 0, FLOAT(48.0f), 0)
        WAIT_MS(1000)
        CALL(evt_npc_reverse_ry, STRING(((char*)tou_02_str_00003CB0)))
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(talk_kino4)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004014)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004028)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000403C)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004050)), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00004064)), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004078)), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000408C)), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000040A0)), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000040B0)), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000040C4)), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000040B0)), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_kino5)
    CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), -520, 0, 25)
    RETURN
EVT_END()

EVT_BEGIN(talk_kino5)
    CALL(evt_pouch_get_yoshiname, LW(10))
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_000040D4)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000040E8)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000040FC)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_mario_get_party, LW(0))
            IF_INT_EQUAL(LW(0), 4)
                CALL(evt_msg_print_insert, 0, STRING(((char*)tou_02_str_00004110)), 0, 0, LW(10))
                ELSE
                CALL(evt_msg_print_insert, 0, STRING(((char*)tou_02_str_00004128)), 0, 0, LW(10))
            END_IF
            CASE_GREATER(0)
            CALL(evt_mario_get_party, LW(0))
            IF_INT_EQUAL(LW(0), 4)
                CALL(evt_msg_print_insert, 0, STRING(((char*)tou_02_str_0000413C)), 0, 0, LW(10), LW(10))
                ELSE
                CALL(evt_msg_print_insert, 0, STRING(((char*)tou_02_str_00004154)), 0, 0, LW(10))
            END_IF
            CASE_DEFAULT
            CALL(evt_mario_get_party, LW(0))
            IF_INT_EQUAL(LW(0), 4)
                CALL(evt_msg_print_insert, 0, STRING(((char*)tou_02_str_00004168)), 0, 0, LW(10))
                ELSE
                CALL(evt_msg_print_insert, 0, STRING(((char*)tou_02_str_00004180)), 0, 0, LW(10))
            END_IF
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_mario_get_party, LW(0))
            IF_INT_EQUAL(LW(0), 4)
                CALL(evt_msg_print_insert, 0, STRING(((char*)tou_02_str_00004194)), 0, 0, LW(10))
                ELSE
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000041AC)), 0, 0)
            END_IF
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_mario_get_party, LW(0))
                IF_INT_EQUAL(LW(0), 4)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000041C0)), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000041D4)), 0, 0)
                END_IF
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_mario_get_party, LW(0))
                IF_INT_EQUAL(LW(0), 4)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000041E4)), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000041FC)), 0, 0)
                END_IF
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_mario_get_party, LW(0))
                    IF_INT_EQUAL(LW(0), 4)
                        CALL(evt_msg_print_insert, 0, STRING(((char*)tou_02_str_00004210)), 0, 0, LW(10))
                        ELSE
                        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004224)), 0, 0)
                    END_IF
                    ELSE
                    CALL(evt_mario_get_party, LW(0))
                    IF_INT_EQUAL(LW(0), 4)
                        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000041E4)), 0, 0)
                        ELSE
                        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000041FC)), 0, 0)
                    END_IF
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_kinopiko)
    CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), -490, 0, 25)
    RETURN
EVT_END()

EVT_BEGIN(talk_kinopiko)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004234)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004248)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000425C)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004270)), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004284)), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004298)), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000042AC)), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000042C0)), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000042D0)), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000042E4)), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000042D0)), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_kinopio_f)
    CALL(evt_npc_set_position, STRING(((char*)str_000042F4)), 100, 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(talk_kinopio_f)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004300)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004314)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004328)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000433C)), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004350)), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004364)), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004378)), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000438C)), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000439C)), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000043B0)), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000439C)), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_chu)
    SWITCH(GSW(0))
        CASE_LESS(144)
        CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), 245, 0, 125)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), 0, -1000, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_chu)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000043C0)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000043D4)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000043E8)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000043FC)), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004410)), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004424)), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004438)), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(init_champ)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), -15, 0, 25)
            CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_02_str_00003CB0)), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING(((char*)tou_02_str_00003CB0)), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

s32 move_pos[] = {
    0, 0, -100, -70, -225, 50, -230, 135,
    -105, 110, 10, -10, 135, 135, 220, 40,
    138, -65, 35, -50, 0, 110, -80, -40,
    110, -40,
};

EVT_BEGIN(move_champ)
    SET_VALUE(LW(10), 0)
    LOOP(0)
        SET_INT_READ_ADDR(PTR(move_pos))
        LOOP(13)
            READ_INT2(LW(0), LW(1))
            CALL(evt_sub_random, 5, LW(0))
            ADD(LW(0), 2)
            MULTIPLY(LW(0), 1000)
            WAIT_MS(LW(0))
            CALL(evt_npc_get_position, STRING(((char*)tou_02_str_00003CB0)), LW(5), LW(6), LW(7))
            CALL(evt_sub_random, 100, LW(0))
            CALL(evt_sub_random, 100, LW(1))
            SUBTRACT(LW(0), 50)
            ADD(LW(5), LW(0))
            ADD(LW(6), 40)
            SUBTRACT(LW(7), LW(1))
            CALL(evt_msg_toge, 2, LW(5), LW(6), LW(7))
            CALL(evt_end_count, LW(0))
            IF_INT_LESS(LW(0), 10)
                RETURN
            END_IF
            BEGIN_INLINE_EVENT
                SWITCH(LW(10))
                    CASE_EQUAL(0)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000444C)), 0, 0)
                    CASE_EQUAL(1)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000445C)), 0, 0)
                    CASE_EQUAL(2)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000446C)), 0, 0)
                    CASE_EQUAL(3)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000447C)), 0, 0)
                    CASE_EQUAL(4)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000448C)), 0, 0)
                    CASE_EQUAL(5)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000449C)), 0, 0)
                    CASE_EQUAL(6)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000044AC)), 0, 0)
                    CASE_EQUAL(7)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000044BC)), 0, 0)
                    CASE_EQUAL(8)
                    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000044CC)), 0, 0)
                END_SWITCH
            END_INLINE_EVENT
            ADD(LW(10), 1)
            IF_INT_GREATER(LW(10), 8)
                SET_VALUE(LW(10), 0)
            END_IF
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(talk_champ)
    SWITCH(GSW(0))
        CASE_LESS(171)
        CALL(evt_end_count, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000044DC)), 0, STRING(((char*)tou_02_str_00003CB0)))
            ELSE
            CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000044EC)), 0, STRING(((char*)tou_02_str_00003CB0)))
        END_IF
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_000044FC)), 0, STRING(((char*)tou_02_str_00003CB0)))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_shikowa)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), -25, 0, 75)
            CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_02_str_00003CB0)), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING(((char*)tou_02_str_00003CB0)), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_shikowa)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000450C)), 0, STRING(((char*)tou_02_str_00003CB0)))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(init_uranoko)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), -75, 0, 50)
            CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_02_str_00003CB0)), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING(((char*)tou_02_str_00003CB0)), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_uranoko)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000451C)), 0, STRING(((char*)tou_02_str_00003CB0)))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_ironA)
    CALL(evt_npc_set_scale, STRING(((char*)tou_02_str_00003CB0)), FLOAT(1.5f), FLOAT(1.5f), FLOAT((1.0f)))
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), -30, 0, -50)
            CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_02_str_00003CB0)), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING(((char*)tou_02_str_00003CB0)), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_ironA)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000452C)), 0, STRING(((char*)tou_02_str_00003CB0)))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_ironB)
    CALL(evt_npc_set_scale, STRING(((char*)tou_02_str_00003CB0)), FLOAT(1.5f), FLOAT(1.5f), FLOAT((1.0f)))
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), -60, 0, -25)
            CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_02_str_00003CB0)), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING(((char*)tou_02_str_00003CB0)), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_ironB)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000453C)), 0, STRING(((char*)tou_02_str_00003CB0)))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_borodo)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00003CB0)), -100, 0, 100)
            CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_02_str_00003CB0)), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING(((char*)tou_02_str_00003CB0)), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_borodo)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000454C)), 0, STRING(((char*)tou_02_str_00003CB0)))
    END_SWITCH
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"ガードマン１"*/(char*)tou_02_str_00003CB4, 1074267648, 0, (s32)init_gard1, 0, (s32)talk_gard1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ガードマン２"*/(char*)tou_02_str_00003CCC,
    1074267648, 0, (s32)init_gard2, 0, (s32)talk_gard2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"マダム"*/(char*)tou_02_str_0000455C, 1074267648,
    0, (s32)init_madam, 0, (s32)talk_madam, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"レポーター"*/(char*)tou_02_str_00004564, 1074267648, 0,
    (s32)init_repo, 0, (s32)talk_repo, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"カメラマン１"*/(char*)tou_02_str_00004570, 1074267648, 0, (s32)init_cam1,
    0, (s32)talk_cam1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"カメラマン２"*/(char*)tou_02_str_00004580, 1074267648, 0, (s32)init_cam2, 0,
    (s32)talk_cam2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"キノピオ４"*/(char*)tou_02_str_00004590, 1074267648, 0, (s32)init_kino4, (s32)reg_kino4, (s32)talk_kino4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)/*"キノピオ５"*/(char*)tou_02_str_0000459C, 1074267648, 0, (s32)init_kino5, 0, (s32)talk_kino5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    (s32)/*"キノピコ"*/(char*)tou_02_str_000045A8, 1074267648, 0, (s32)init_kinopiko, 0, (s32)talk_kinopiko, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"バッジ屋"*/(char*)tou_02_str_000045B4,
    1074267648, 0, (s32)init_chu, 0, (s32)talk_chu, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"チャンピョン"*/(char*)tou_02_str_000045C0, 1074267648,
    0, (s32)init_champ, 0, (s32)talk_champ, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"キノシコワ"*/(char*)tou_02_str_000045D0, 1074267648, 0,
    (s32)init_shikowa, 0, (s32)talk_shikowa, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"ウラノコ"*/(char*)tou_02_str_000045DC, 1074267648, 0, (s32)init_uranoko,
    0, (s32)talk_uranoko, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"アイアンＡ"*/(char*)tou_02_str_000045E8, 1074267648, 0, (s32)init_ironA, 0,
    (s32)talk_ironA, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"アイアンＢ"*/(char*)tou_02_str_000045F4, 1074267648, 0, (s32)init_ironB, 0, (s32)talk_ironB,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)/*"ボロドー"*/(char*)str_00004600, 1074267648, 0, (s32)init_borodo, 0, (s32)talk_borodo, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(evt_tougi2)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    SET_VALUE(LF(0), 0)
    CALL(evt_bero_get_entername, LW(0))
    IF_STR_EQUAL(LW(0), STRING(((char*)tou_02_str_00003C68)))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_EQUAL(LF(0), 1)
        CALL(evt_mario_set_pos, -25, 200, -220)
        CALL(evt_party_set_pos, 0, 25, 200, -220)
        ELSE
        CALL(evt_mario_set_pos, -25, 0, -220)
        CALL(evt_party_set_pos, 0, 25, 0, -220)
    END_IF
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_set_dir, 0, 270, -1)
    IF_INT_EQUAL(LF(0), 1)
        CALL(evt_cam3d_evt_set, 0, 290, 190, 0, 238, -158, 0, 11)
        ELSE
        CALL(evt_cam3d_evt_set, 0, 90, 190, 0, 38, -158, 0, 11)
    END_IF
    CALL(evt_seq_wait, 2)
    SET_VALUE(LW(1), 2)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, -180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        IF_INT_EQUAL(LF(0), 1)
            CALL_CHILD(PTR(n_2_door_open))
            ELSE
            CALL_CHILD(PTR(n_1_door_open))
        END_IF
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(2), 100)
        CALL(evt_mario_mov_pos, LW(0), LW(2), 1000)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(2), 100)
        CALL(evt_party_move_pos, 0, LW(0), LW(2), 1000)
    END_INLINE_EVENT
    WAIT_MS(700)
    SET_VALUE(LW(1), 2)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        IF_INT_EQUAL(LF(0), 1)
            CALL_CHILD(PTR(n_2_door_close))
            ELSE
            CALL_CHILD(PTR(n_1_door_close))
        END_IF
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_msg_print_party, STRING(((char*)tou_02_str_0000460C)))
    CALL(evt_msg_select, 0, STRING(((char*)tou_02_str_00004618)))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_mario_get_party, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(1)
            CALL(evt_msg_print_add, 0, STRING(((char*)tou_02_str_00004628)))
            CASE_EQUAL(2)
            CALL(evt_msg_print_add, 0, STRING(((char*)tou_02_str_00004638)))
            CASE_EQUAL(5)
            CALL(evt_msg_print_add, 0, STRING(((char*)tou_02_str_00004648)))
        END_SWITCH
        ELSE
        CALL(evt_mario_get_party, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(1)
            CALL(evt_msg_print_add, 0, STRING(((char*)tou_02_str_00004658)))
            CASE_EQUAL(2)
            CALL(evt_msg_print_add, 0, STRING(((char*)tou_02_str_00004668)))
            CASE_EQUAL(5)
            CALL(evt_msg_print_add, 0, STRING(((char*)tou_02_str_00004678)))
        END_SWITCH
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_02_str_00004688)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)tou_02_str_000046A0)))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING(((char*)tou_02_str_000046A8)))
    CALL(evt_msg_print_party, STRING(((char*)tou_02_str_000046B0)))
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    SET_VALUE(GSWF(2374), 0)
    SET_VALUE(GSW(0), 128)
    CALL(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

s32 ext_fan_data[] = {
    (s32)((char*)tou_02_str_000046BC), (s32)((char*)tou_02_str_000046C8), 1073741824, (s32)((char*)tou_02_str_000046BC), (s32)((char*)tou_02_str_000046C8), 1086324736, (s32)((char*)tou_02_str_000046BC), (s32)((char*)tou_02_str_000046C8),
    1092616192, (s32)((char*)tou_02_str_000046BC), (s32)((char*)tou_02_str_000046C8), 1096810496, (s32)((char*)tou_02_str_000046BC), (s32)((char*)tou_02_str_000046C8), 1099956224, (s32)((char*)tou_02_str_000046BC),
    (s32)((char*)tou_02_str_000046C8), 1102053376, (s32)((char*)tou_02_str_000046BC), (s32)((char*)tou_02_str_000046C8), 1104150528, (s32)((char*)tou_02_str_000046BC), (s32)((char*)tou_02_str_000046C8), 1106247680,
    (s32)((char*)tou_02_str_000046BC), (s32)((char*)tou_02_str_000046C8), 1107820544, (s32)((char*)tou_02_str_000046D0), (s32)((char*)tou_02_str_000046DC), 1073741824, (s32)((char*)tou_02_str_000046D0), (s32)((char*)tou_02_str_000046DC),
    1086324736, (s32)((char*)tou_02_str_000046D0), (s32)((char*)tou_02_str_000046DC), 1092616192, (s32)((char*)tou_02_str_000046D0), (s32)((char*)tou_02_str_000046DC), 1096810496, (s32)((char*)tou_02_str_000046D0),
    (s32)((char*)tou_02_str_000046DC), 1099956224, (s32)((char*)tou_02_str_000046D0), (s32)((char*)tou_02_str_000046DC), 1102053376, (s32)((char*)tou_02_str_000046D0), (s32)((char*)tou_02_str_000046DC), 1104150528,
    (s32)((char*)tou_02_str_000046D0), (s32)((char*)tou_02_str_000046DC), 1106247680, (s32)((char*)tou_02_str_000046D0), (s32)((char*)tou_02_str_000046DC), 1107820544, (s32)((char*)tou_02_str_000046D0), (s32)((char*)tou_02_str_000046DC),
    1108869120, (s32)((char*)tou_02_str_000046E4), (s32)((char*)tou_02_str_000046F0), 0, (s32)((char*)tou_02_str_000046E4), (s32)((char*)tou_02_str_000046F0), 1082130432, (s32)((char*)tou_02_str_000046E4),
    (s32)((char*)tou_02_str_000046F0), 1090519040, (s32)((char*)tou_02_str_000046E4), (s32)((char*)tou_02_str_000046F0), 1094713344, (s32)((char*)tou_02_str_000046E4), (s32)((char*)tou_02_str_000046F0), 1098907648,
    (s32)((char*)tou_02_str_000046E4), (s32)((char*)tou_02_str_000046F0), 1101004800, (s32)((char*)tou_02_str_000046E4), (s32)((char*)tou_02_str_000046F0), 1103101952, (s32)((char*)tou_02_str_000046E4), (s32)((char*)tou_02_str_000046F0),
    1105199104, 0, 0, 0,
};

#ifdef NONMATCHING
void ext_fan_init(void) {
    s32 i;
    ExtPose* pose;
    Fan* fan;

    fan_wp = _mapAlloc(sizeof(FanWork));
    memset(fan_wp, 0, sizeof(FanWork));
    fan_wp->num = extGetPoseNum();
    fan_wp->fans = _mapAlloc(fan_wp->num * sizeof(Fan));
    memset(fan_wp->fans, 0, fan_wp->num * sizeof(Fan));
    pose_init();
    pose = extGetPosePtr();
    fan = fan_wp->fans;
    for (i = 0; i < fan_wp->num; i++, pose++, fan++) {
        pose->flags |= 7;
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = EXT_LIT(zero_tou_0000d328, 0.0f);
        pose->mtx[1][3] = EXT_LIT(zero_tou_0000d328, 0.0f);
        pose->mtx[2][3] = EXT_LIT(zero_tou_0000d328, 0.0f);
        pose->rot = randf(EXT_LIT(zero_tou_0000d328, 0.0f), EXT_LIT(float_360_tou_0000d334, 360.0f));
        switch (irand(1000) % 3) {
            case 0:
                pose_change(fan, "c_kinopio", "KNP_W_1");
                break;
            case 1:
                pose_change(fan, "c_kinopiko", "KNF_W_1");
                break;
            case 2:
            default:
                pose_change(fan, "c_jugemu", "JGM_W_1");
                break;
        }
        fan->state = 0;
        {
            Vec pos = {0.0f, 0.0f, 0.0f};

            pos.x = randf(EXT_LIT(float_neg100_tou_0000d3b0, -100.0f), EXT_LIT(float_100_tou_0000d3ac, 100.0f));
            pos.z = randf(EXT_LIT(float_neg100_tou_0000d3b0, -100.0f), EXT_LIT(float_100_tou_0000d3ac, 100.0f));
            fan->pos = pos;
            fan->vel = (Vec){EXT_LIT(zero_tou_0000d328, 0.0f), EXT_LIT(zero_tou_0000d328, 0.0f), EXT_LIT(zero_tou_0000d328, 0.0f)};
        }
    }
    fan_wp->sfxId = psndSFXOn_3D("SFX_STG3_AUDIENCE_FAN1\0", &(Vec){EXT_LIT(zero_tou_0000d328, 0.0f), EXT_LIT(zero_tou_0000d328, 0.0f), EXT_LIT(zero_tou_0000d328, 0.0f)});
    fan_wp->vol = psndSFX_get_vol(fan_wp->sfxId);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void ext_fan_init(void) {
	char _af_pad[96];
	asm volatile {
		opword 0x3860051C
		bl _mapAlloc
		lis r5, fan_wp@ha
		opword 0x38800000
		addi r6, r5, fan_wp@l
		opword 0x38A0051C
		opword 0x90660000
		bl memset
		bl extGetPoseNum
		lis r4, fan_wp@ha
		addi r5, r4, fan_wp@l
		opword 0x80850000
		opword 0x90640000
		opword 0x80650000
		opword 0x80030000
		opword 0x1C600048
		bl _mapAlloc
		lis r5, fan_wp@ha
		opword 0x38800000
		addi r6, r5, fan_wp@l
		opword 0x80A60000
		opword 0x90650004
		opword 0x80660000
		opword 0x80030000
		opword 0x80630004
		opword 0x1CA00048
		bl memset
		lis r3, ext_fan_data@ha
		lis r4, zero_tou_0000d3d8@ha
		addi r28, r3, ext_fan_data@l
		opword 0x3BE00000
		la r3, _af_pad+24
		addi r4, r4, zero_tou_0000d3d8@l
		bl strcpy
		lis r4, zero_tou_0000d3d8@ha
		opword 0x38610040
		addi r4, r4, zero_tou_0000d3d8@l
		bl strcpy
		lis r3, fan_wp@ha
		opword 0x3800FFFF
		addi r29, r3, fan_wp@l
		opword 0x807D0000
		opword 0x90030008
		opword 0x807C0000
		opword 0x38810020
		bl strcmp
		opword 0x2C030000
		opword 0x41820020
		opword 0x809C0000
		opword 0x38610020
		bl strcpy
		lis r4, zero_tou_0000d3d8@ha
		opword 0x38610040
		addi r4, r4, zero_tou_0000d3d8@l
		bl strcpy
		opword 0x807C0004
		opword 0x38810040
		bl strcmp
		opword 0x2C030000
		opword 0x41820028
		opword 0x809C0004
		opword 0x38610040
		bl strcpy
		lis r3, fan_wp@ha
		opword 0x7FFEFB78
		lwz r4, fan_wp@l(r3)
		opword 0x80640008
		opword 0x38030001
		opword 0x90040008
		opword 0x80BD0000
		opword 0x38810020
		opword 0x80050008
		opword 0x1C600028
		opword 0x3863000C
		opword 0x7C651A14
		bl strcpy
		opword 0x80BD0000
		opword 0x38810040
		opword 0x80050008
		opword 0x1C600028
		opword 0x3863001C
		opword 0x7C651A14
		bl strcpy
		opword 0x80DD0000
		opword 0x7C7EF850
		opword 0x38A30001
		opword 0x38800001
		opword 0x80060008
		opword 0x3BFF0001
		opword 0x1C600028
		opword 0x3803002C
		opword 0x7FC6012E
		opword 0x80DD0000
		opword 0x80060008
		opword 0x1C600028
		opword 0x38030030
		opword 0x7CA6012E
		opword 0x80BD0000
		opword 0xC01C0008
		opword 0x80050008
		opword 0x1C600028
		opword 0x38030028
		opword 0x7C05052E
		opword 0x80BD0000
		opword 0x80050008
		opword 0x1C600028
		opword 0x38030024
		opword 0x7C85032E
		opword 0x841C000C
		opword 0x28000000
		opword 0x4082FEF4
		lis r3, fan_wp@ha
		lwz r4, fan_wp@l(r3)
		opword 0x80640008
		opword 0x38030001
		opword 0x90040008
		bl extGetPosePtr
		lis r4, fan_wp@ha
		lis r9, zero_tou_0000d328@ha
		addi r29, r4, fan_wp@l
		lis r8, double_to_int_tou_0000d370@ha
		opword 0x819D0000
		lis r7, float_32767_tou_0000d3a0@ha
		addi r11, r9, zero_tou_0000d328@l
		addi r10, r8, double_to_int_tou_0000d370@l
		addi r9, r7, float_32767_tou_0000d3a0@l
		lis r6, float_360_tou_0000d334@ha
		addi r8, r6, float_360_tou_0000d334@l
		lis r5, float_200_tou_0000d3dc@ha
		addi r6, r5, float_200_tou_0000d3dc@l
		lis r4, float_neg100_tou_0000d3b0@ha
		addi r5, r4, float_neg100_tou_0000d3b0@l
		lis r7, vec3_tou_0000d028@ha
		lis r4, vec3_tou_0000d034@ha
		opword 0x832C0004
		lfs f26, 0x0(r11)
		opword 0x7C7A1B78
		opword 0xCB6A0000
		addi r31, r7, vec3_tou_0000d028@l
		opword 0xC3890000
		addi r24, r4, vec3_tou_0000d034@l
		opword 0xC3A80000
		opword 0x3B600000
		opword 0xC3C60000
		opword 0x3FC04330
		opword 0xC3E50000
		opword 0x48000338
		opword 0x801A0000
		opword 0x60000007
		opword 0x901A0000
		opword 0x807A000C
		bl PSMTXIdentity
		opword 0x807A000C
		opword 0xD343000C
		opword 0x807A000C
		opword 0xD343001C
		opword 0x807A000C
		opword 0xD343002C
		bl rand
		opword 0x6C608000
		opword 0x93C10060
		opword 0x386003E8
		opword 0x90010064
		opword 0xC8010060
		opword 0xEC00D828
		opword 0xEC00E024
		opword 0xEC00D77A
		opword 0xD01A0004
		bl irand
		opword 0x38800003
		opword 0x7C0323D6
		opword 0x7C0021D6
		opword 0x7C001850
		opword 0x2C000001
		opword 0x418200C8
		opword 0x40800174
		opword 0x2C000000
		opword 0x4080000C
		opword 0x48000168
		opword 0x48000164
		lis r4, fan_wp@ha
		lis r3, tou_02_str_000046C8@ha
		addi r23, r4, fan_wp@l
		lis r4, tou_02_str_000046BC@ha
		opword 0x80B70000
		addi r21, r3, tou_02_str_000046C8@l
		addi r22, r4, tou_02_str_000046BC@l
		opword 0x3B800000
		addi r20, r5, 0xc
		opword 0x48000034
		opword 0x7E83A378
		opword 0x7EC4B378
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x7EA4AB78
		opword 0x38740010
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3B9C0001
		opword 0x3A940028
		opword 0x80770000
		opword 0x80030008
		opword 0x7C1C0000
		opword 0x4180FFC4
		lis r3, fan_wp@ha
		addi r3, r3, fan_wp@l
		opword 0x80630000
		opword 0x80030008
		opword 0x7C1C0000
		opword 0x40800190
		opword 0xA8190004
		opword 0x7C00E000
		opword 0x41820184
		lis r3, gp@ha
		opword 0xB3990004
		addi r3, r3, gp@l
		opword 0x80630000
		opword 0x80030038
		opword 0x8063003C
		opword 0x9079000C
		opword 0x90190008
		opword 0x48000160
		lis r4, fan_wp@ha
		lis r3, tou_02_str_000046DC@ha
		addi r23, r4, fan_wp@l
		lis r4, tou_02_str_000046D0@ha
		opword 0x80B70000
		addi r21, r3, tou_02_str_000046DC@l
		addi r22, r4, tou_02_str_000046D0@l
		opword 0x3B800000
		opword 0x3A85000C
		opword 0x48000034
		opword 0x7E83A378
		opword 0x7EC4B378
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x7EA4AB78
		opword 0x38740010
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3B9C0001
		opword 0x3A940028
		opword 0x80770000
		opword 0x80030008
		opword 0x7C1C0000
		opword 0x4180FFC4
		lis r3, fan_wp@ha
		addi r3, r3, fan_wp@l
		opword 0x80630000
		opword 0x80030008
		opword 0x7C1C0000
		opword 0x408000E0
		opword 0xA8190004
		opword 0x7C00E000
		opword 0x418200D4
		lis r3, gp@ha
		opword 0xB3990004
		addi r3, r3, gp@l
		opword 0x80630000
		opword 0x80030038
		opword 0x8063003C
		opword 0x9079000C
		opword 0x90190008
		opword 0x480000B0
		lis r4, fan_wp@ha
		lis r3, tou_02_str_000046F0@ha
		addi r21, r4, fan_wp@l
		lis r4, tou_02_str_000046E4@ha
		opword 0x80B50000
		addi r23, r3, tou_02_str_000046F0@l
		addi r22, r4, tou_02_str_000046E4@l
		opword 0x3B800000
		opword 0x3A85000C
		opword 0x48000034
		opword 0x7E83A378
		opword 0x7EC4B378
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x7EE4BB78
		opword 0x38740010
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3B9C0001
		opword 0x3A940028
		opword 0x80750000
		opword 0x80030008
		opword 0x7C1C0000
		opword 0x4180FFC4
		lis r3, fan_wp@ha
		addi r3, r3, fan_wp@l
		opword 0x80630000
		opword 0x80030008
		opword 0x7C1C0000
		opword 0x40800030
		opword 0xA8190004
		opword 0x7C00E000
		opword 0x41820024
		lis r3, gp@ha
		opword 0xB3990004
		addi r3, r3, gp@l
		opword 0x80630000
		opword 0x80030038
		opword 0x8063003C
		opword 0x9079000C
		opword 0x90190008
		opword 0x38000000
		opword 0xB0190002
		opword 0x809F0000
		opword 0x807F0004
		opword 0x801F0008
		opword 0x90810014
		opword 0x90610018
		opword 0x9001001C
		bl rand
		opword 0x6C608000
		opword 0x93C10060
		opword 0x90010064
		opword 0xC8010060
		opword 0xEC00D828
		opword 0xEC00E024
		opword 0xEC00FFBA
		opword 0xD0010014
		bl rand
		opword 0x6C608000
		opword 0x80610014
		opword 0x9001006C
		opword 0x3B7B0001
		opword 0x80010018
		opword 0x3B5A0020
		opword 0x93C10068
		opword 0xC8010068
		opword 0x90790010
		opword 0xEC00D828
		opword 0x90190014
		opword 0xEC00E024
		opword 0xEC00FFBA
		opword 0xD001001C
		opword 0x8001001C
		opword 0x90190018
		opword 0x80780000
		opword 0x80180004
		opword 0x9079001C
		opword 0x90190020
		opword 0x80180008
		opword 0x90190024
		opword 0x3B390048
		opword 0x807D0000
		opword 0x80030000
		opword 0x7C1B0000
		opword 0x4180FCC0
		lis r4, vec3_tou_0000d040@ha
		lis r3, tou_02_str_00004AB0@ha
		addi r7, r4, vec3_tou_0000d040@l
		opword 0x80C70000
		opword 0x38810008
		opword 0x80A70004
		addi r3, r3, tou_02_str_00004AB0@l
		opword 0x80070008
		opword 0x90C10008
		opword 0x90A1000C
		opword 0x90010010
		bl psndSFXOn_3D
		lis r4, fan_wp@ha
		addi r5, r4, fan_wp@l
		opword 0x80850000
		opword 0x90640514
		opword 0x80650000
		opword 0x80630514
		bl psndSFX_get_vol
		lis r4, fan_wp@ha
		addi r4, r4, fan_wp@l
		opword 0x80840000
		opword 0x98640518
	}
}
#pragma pop
#endif

void fan_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING // only the NONMATCHING C uses it
static __declspec(section ".rodata") Vec fan_zero = {0.0f, 0.0f, 0.0f};
#endif
#ifdef NONMATCHING
void ext_fan_main(void) {
    MarioWork* mario = marioGetPtr();
    Vec dir;
    Vec target = {0.0f, 0.0f, 0.0f};
    Fan* fan;
    ExtPose* pose;
    s32 i;

    if (mario->currMotionId == 0x12) {
        fan_wp->hammerTimer++;
    } else {
        fan_wp->hammerTimer = 0;
    }
    if (evtGetValue(NULL, GF(10))) {
        ExtPose* pose = extGetPosePtr();
        Fan* fan = fan_wp->fans;

        for (i = 0; i < fan_wp->num; i++, fan++, pose++) {
            if (fan->state == 0) {
                fan->pos = mario->position;
                target = fan->pos;
                pose->flags &= ~1;
                fan->flags |= 1;
                break;
            }
        }
    } else {
        s32 i;
        s32 found = 0;

        pose = extGetPosePtr();
        fan = fan_wp->fans;

        for (i = 0; i < fan_wp->num; i++, fan++, pose++) {
            if (fan->state == 0) {
                if (!found) {
                    found = 1;
                    fan->pos = mario->position;
                    pose->flags &= ~1;
                    fan->flags |= 1;
                } else {
                    fan->pos = npcNameToPtr("\203`\203\203\203\223\203s\203\207\203\223")->position;
                    target = fan->pos;
                    pose->flags &= ~1;
                    fan->flags |= 1;
                    break;
                }
            }
        }
    }

    {

        Fan* fan;
        s32 i;

        for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
            if (fan->state == 0) {
                PSVECSubtract(&target, &fan->pos, &dir);
                if (PSVECMag(&dir)) {
                    PSVECNormalize(&dir, &dir);
                    dir.y = EXT_LIT(zero_tou_0000d328, 0.0f);
                    PSVECScale(&dir, &dir, EXT_LIT(float_0p1_tou_0000d378, 0.1f));
                    PSVECAdd(&fan->vel, &dir, &fan->vel);
                }
            }
        }
    }

    {

        for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
            if (fan->state == 0) {
                s32 j;
                Fan* other;

                for (j = 0, other = fan_wp->fans; j < fan_wp->num; j++, other++) {
                    if (other->state == 0 && i != j && PSVECSquareDistance(&fan->pos, &other->pos) < 900.0f) {
                        PSVECSubtract(&fan->pos, &other->pos, &dir);
                        dir.y = EXT_LIT(zero_tou_0000d328, 0.0f);
                        PSVECNormalize(&dir, &dir);
                        PSVECScale(&dir, &dir, EXT_LIT(float_5_tou_0000d380, 5.0f));
                        PSVECAdd(&fan->vel, &dir, &fan->vel);
                        PSVECSubtract(&other->vel, &dir, &other->vel);
                    }
                }
            }
        }
    }

    {
        const char* sfx2;
        const char* sfx1;
        f32 angle;
        f32 dist;
        f32 dy;
        f32 spd;
        f32 x;
        f32 z;
        f32 dir2;
        sfx2 = sfx1 = "SFX_STG3_AUDIENCE_FAN_FLY1";
        for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
            if (fan->state == 0) {
                switch (check_hammer(fan)) {
                    case 0:
                        break;
                    case 1:
                        fan->state = 10;
                        dist = EXT_LIT(float_6p2832_tou_0000d32c, 6.2831855f); angle = EXT_LIT(float_6p2832_tou_0000d32c, 6.2831855f) * randf(EXT_LIT(float_135_tou_0000d3a4, 135.0f), 225.0f) / EXT_LIT(float_360_tou_0000d334, 360.0f);
                        dist = randf(EXT_LIT(float_400_tou_0000d3a8, 400.0f), 500.0f);
                        x = fan->pos.x + dist * fan_sin(angle);
                        z = fan->pos.z - dist * fan_cos(angle);
                        {
                            Vec tgt = {0.0f, 0.0f, 0.0f};

                            tgt.x = x;
                            tgt.y = EXT_LIT(float_neg100_tou_0000d3b0, -100.0f);
                            tgt.z = z;
                            fan->target = tgt;
                        }
                        fan->param.y = randf(EXT_LIT(float_4_tou_0000d3b4, 4.0f), 6.0f);
                        fan->param.z = randf(EXT_LIT(float_0p1_tou_0000d378, 0.1f), 0.2f);
                        dy = fan->target.y - fan->pos.y;
                        dist = distABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                        angleABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                        fan->timer = dist / fan->param.y;
                        fan->param.x = dy / fan->timer + fan->param.z * fan->timer / EXT_LIT(float_2_tou_0000d3b8, 2.0f);
                        psndSFXOn_3D(sfx1, &fan->pos);
                        break;
                    case 2: {

                        angle = angleABf(mario->position.x, mario->position.z, fan->pos.x, fan->pos.z);
                        dir2 = cloudGetBreathDir();
                        fan->state = 20;
                        fan->target = fan_zero;
                        angle = (angle + dir2) / EXT_LIT(float_2_tou_0000d3b8, 2.0f);
                        spd = randf(EXT_LIT(float_0p1_tou_0000d378, 0.1f), 0.2f);
                        angle = EXT_LIT(float_6p2832_tou_0000d32c, 6.2831855f) * angle / EXT_LIT(float_360_tou_0000d334, 360.0f);
                        fan->param.x = spd * fan_sin(angle);
                        fan->param.y = randf(EXT_LIT(float_0p03_tou_0000d3c0, 0.03f), 0.06f);
                        fan->param.z = spd * -fan_cos(angle);
                        fan->timer = 120;
                        psndSFXOn_3D(sfx2, &fan->pos);
                        break;
                    }
                }
            }
        }
    }
    fan_wp->count = fan_wp->num;

    {
        f32 angle;
        f32 dist;
        f32 h;

        pose = extGetPosePtr();
        fan = fan_wp->fans;
        for (i = 0; i < fan_wp->num; i++, pose++, fan++) {
            switch (fan->state) {
                case 0: {
                    HitCheckQuery query;
                    HitCheckQuery* q = &query;
                    PSVECNormalize(&fan->vel, &fan->vel);
                    dist = PSVECMag(&fan->vel);
                    query.targetPos = fan->pos;
                    query.targetPos.y += EXT_LIT(float_4_tou_0000d3b4, 4.0f);
                    query.targetDir = fan->vel;
                    query.targetDir.y = EXT_LIT(zero_tou_0000d328, 0.0f);
                    query.targetDistance = EXT_LIT(float_25_tou_0000d3c4, 25.0f) + dist;
                    if (hitCheckVecFilter(&query, NULL)) {
                        C_VECReflect(&fan->vel, &q->hitNormal, &fan->vel);
                    } else {
                        fan->pos.x += fan->vel.x;
                        fan->pos.z += fan->vel.z;
                        fan->vel.x *= EXT_LIT(float_0p6_tou_0000d3c8, 0.6f);
                        fan->vel.z *= EXT_LIT(float_0p6_tou_0000d3c8, 0.6f);
                    }
                    if (fan->pos.x < EXT_LIT(float_neg350_tou_0000d3cc, -350.0f)) {
                        fan->pos.x = -350.0f;
                    }
                    if (fan->pos.x > EXT_LIT(float_350_tou_0000d3d0, 350.0f)) {
                        fan->pos.x = 350.0f;
                    }
                    if (fan->pos.z > (h = EXT_LIT(float_195_tou_0000d3d4, 195.0f) + i / EXT_LIT(float_100_tou_0000d3ac, 100.0f))) {
                        fan->pos.z = h;
                    }
                    break;
                }
                case 10:
                    fan->pos.y += fan->param.x;
                    fan->param.x -= fan->param.z;
                    angle = angleABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                    angle = EXT_LIT(float_6p2832_tou_0000d32c, 6.2831855f) * angle / EXT_LIT(float_360_tou_0000d334, 360.0f);
                    fan->pos.x += fan->param.y * fan_sin(angle);
                    fan->pos.z += fan->param.y * -fan_cos(angle);
                    if (--fan->timer < 0) {
                        fan->state = 100;
                    }
                    break;
                case 20:
                    if (--fan->timer > 0) {
                        fan->target.x += fan->param.x;
                        fan->target.y += fan->param.y;
                        fan->target.z += fan->param.z;
                        fan->pos.x += fan->target.x;
                        fan->pos.y += fan->target.y;
                        fan->pos.z += fan->target.z;
                    } else {
                        fan->state = 100;
                    }
                    break;
                case 100:
                    pose->flags &= ~3;
                    fan->state++;
                    break;
                case 101:
                    break;
            }
            if (fan->flags & 1) {
                fan_wp->count--;
            } else if (fan->state != 0) {
                fan_wp->count--;
            }
            pose->mtx[0][3] = fan->pos.x;
            pose->mtx[1][3] = fan->pos.y;
            pose->mtx[2][3] = fan->pos.z;
            pose->rot = angleABf(target.x, target.z, fan->pos.x, fan->pos.z);
        }
    }
    psndSFX_pos(fan_wp->sfxId, &target);
    psndSFX_vol(fan_wp->sfxId, fan_wp->vol * fan_wp->count / fan_wp->num);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void ext_fan_main(void) {
	char _af_pad[148];
	asm volatile {
		bl marioGetPtr
		lis r4, vec3_tou_0000d04c@ha
		opword 0x7C7F1B78
		addi r5, r4, vec3_tou_0000d04c@l
		opword 0x80850000
		opword 0x80650004
		opword 0x80050008
		stw r4, _af_pad+12(r1)
		opword 0x90610018
		opword 0x9001001C
		opword 0xA01F002E
		opword 0x28000012
		opword 0x4082001C
		lis r3, fan_wp@ha
		lwz r4, fan_wp@l(r3)
		opword 0x8064050C
		opword 0x38030001
		opword 0x9004050C
		opword 0x48000018
		lis r3, fan_wp@ha
		opword 0x38000000
		addi r3, r3, fan_wp@l
		opword 0x80630000
		opword 0x9003050C
		opword 0x3C80FAA3
		opword 0x38600000
		opword 0x3884B58A
		bl evtGetValue
		opword 0x2C030000
		opword 0x41820090
		bl extGetPosePtr
		lis r4, fan_wp@ha
		addi r4, r4, fan_wp@l
		opword 0x80840000
		opword 0x80040000
		opword 0x80A40004
		opword 0x7C0903A6
		opword 0x2C000000
		opword 0x40810150
		opword 0xA8050002
		opword 0x2C000000
		opword 0x40820050
		opword 0x809F008C
		opword 0x801F0090
		opword 0x90850010
		opword 0x90050014
		opword 0x801F0094
		opword 0x90050018
		opword 0x80850010
		opword 0x80050014
		opword 0x90810014
		opword 0x90010018
		opword 0x80050018
		opword 0x9001001C
		opword 0x80030000
		opword 0x5400003C
		opword 0x90030000
		opword 0xA0050000
		opword 0x60000001
		opword 0xB0050000
		opword 0x480000F8
		opword 0x38A50048
		opword 0x38630020
		opword 0x4200FFA0
		opword 0x480000E8
		opword 0x3B600000
		bl extGetPosePtr
		lis r4, fan_wp@ha
		opword 0x38C00000
		addi r5, r4, fan_wp@l
		opword 0x7C7D1B78
		opword 0x80850000
		opword 0x83840004
		opword 0x480000B4
		opword 0xA81C0002
		opword 0x2C000000
		opword 0x4082009C
		opword 0x2C1B0000
		opword 0x4082003C
		opword 0x807F008C
		opword 0x3B600001
		opword 0x801F0090
		opword 0x907C0010
		opword 0x901C0014
		opword 0x801F0094
		opword 0x901C0018
		opword 0x801D0000
		opword 0x5400003C
		opword 0x901D0000
		opword 0xA01C0000
		opword 0x60000001
		opword 0xB01C0000
		opword 0x4800005C
		lis r3, tou_02_str_000045C0@ha
		addi r3, r3, tou_02_str_000045C0@l
		bl npcNameToPtr
		opword 0x8083008C
		opword 0x80030090
		opword 0x909C0010
		opword 0x901C0014
		opword 0x80030094
		opword 0x901C0018
		opword 0x807C0010
		opword 0x801C0014
		opword 0x90610014
		opword 0x90010018
		opword 0x801C0018
		opword 0x9001001C
		opword 0x801D0000
		opword 0x5400003C
		opword 0x901D0000
		opword 0xA01C0000
		opword 0x60000001
		opword 0xB01C0000
		opword 0x48000020
		opword 0x38C60001
		opword 0x3B9C0048
		opword 0x3BBD0020
		opword 0x80650000
		opword 0x80030000
		opword 0x7C060000
		opword 0x4180FF44
		lis r3, fan_wp@ha
		opword 0x3B800000
		addi r26, r3, fan_wp@l
		opword 0x807A0000
		opword 0x83630004
		opword 0x48000080
		opword 0xA81B0002
		opword 0x2C000000
		opword 0x4082006C
		opword 0x38610014
		opword 0x389B0010
		opword 0x38A10020
		bl PSVECSubtract
		opword 0x38610020
		bl PSVECMag
		lis r3, zero_tou_0000d328@ha
		lfs f0, zero_tou_0000d328@l(r3)
		opword 0xFC010000
		opword 0x41820044
		opword 0x38610020
		opword 0x7C641B78
		bl PSVECNormalize
		lis r3, zero_tou_0000d328@ha
		lis r4, float_0p1_tou_0000d378@ha
		addi r5, r3, zero_tou_0000d328@l
		lfs f1, float_0p1_tou_0000d378@l(r4)
		opword 0xC0050000
		opword 0x38610020
		opword 0x7C641B78
		opword 0xD0010024
		bl PSVECScale
		opword 0x387B001C
		opword 0x38810020
		opword 0x7C651B78
		bl PSVECAdd
		opword 0x3B9C0001
		opword 0x3B7B0048
		opword 0x809A0000
		opword 0x80040000
		opword 0x7C1C0000
		opword 0x4180FF78
		lis r3, fan_wp@ha
		opword 0x83840004
		addi r26, r3, fan_wp@l
		opword 0x3B600000
		opword 0x480000D0
		opword 0xA81C0002
		opword 0x2C000000
		opword 0x408200BC
		lis r3, fan_wp@ha
		lwz r25, 0x4(r5)
		addi r29, r3, fan_wp@l
		opword 0x3BC00000
		opword 0x48000098
		opword 0xA8190002
		opword 0x2C000000
		opword 0x40820084
		opword 0x7C1BF000
		opword 0x4182007C
		opword 0x387C0010
		opword 0x38990010
		bl PSVECSquareDistance
		lis r3, float_900_tou_0000d37c@ha
		lfs f0, float_900_tou_0000d37c@l(r3)
		opword 0xFC010040
		opword 0x40800060
		opword 0x387C0010
		opword 0x38990010
		opword 0x38A10020
		bl PSVECSubtract
		lis r4, zero_tou_0000d328@ha
		opword 0x38610020
		lfs f0, zero_tou_0000d328@l(r4)
		opword 0x7C641B78
		opword 0xD0010024
		bl PSVECNormalize
		lis r4, float_5_tou_0000d380@ha
		opword 0x38610020
		lfs f1, float_5_tou_0000d380@l(r4)
		opword 0x7C641B78
		bl PSVECScale
		opword 0x387C001C
		opword 0x38810020
		opword 0x7C651B78
		bl PSVECAdd
		opword 0x3879001C
		opword 0x38810020
		opword 0x7C651B78
		bl PSVECSubtract
		opword 0x3BDE0001
		opword 0x3B390048
		opword 0x807D0000
		opword 0x80030000
		opword 0x7C1E0000
		opword 0x4180FF60
		opword 0x3B7B0001
		opword 0x3B9C0048
		opword 0x80BA0000
		opword 0x80050000
		opword 0x7C1B0000
		opword 0x4180FF28
		lis r4, tou_02_str_00004A54@ha
		lis r3, fan_wp@ha
		addi r30, r4, tou_02_str_00004A54@l
		opword 0x83850004
		addi r26, r3, fan_wp@l
		opword 0x3B600000
		opword 0x7FDDF378
		opword 0x480006A8
		opword 0xA81C0002
		opword 0x2C000000
		opword 0x40820694
		opword 0x7F83E378
		bl check_hammer
		opword 0x2C030001
		opword 0x41820018
		opword 0x40800008
		opword 0x4800067C
		opword 0x2C030003
		opword 0x40800674
		opword 0x480003E0
		opword 0x3800000A
		opword 0xB01C0002
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x90610074
		lis r4, double_to_int_tou_0000d370@ha
		lfd f2, double_to_int_tou_0000d370@l(r4)
		lis r3, float_32767_tou_0000d3a0@ha
		opword 0x90010070
		addi r5, r3, float_32767_tou_0000d3a0@l
		lis r6, float_6p2832_tou_0000d32c@ha
		opword 0xC0050000
		opword 0xC8210070
		lis r4, float_90_tou_0000d330@ha
		lis r3, float_135_tou_0000d3a4@ha
		lfs f3, float_6p2832_tou_0000d32c@l(r6)
		opword 0xEC211028
		addi r5, r4, float_90_tou_0000d330@l
		addi r4, r3, float_135_tou_0000d3a4@l
		opword 0xC0450000
		lis r3, float_360_tou_0000d334@ha
		opword 0xEC810024
		opword 0xC0240000
		lfs f0, float_360_tou_0000d334@l(r3)
		opword 0xEC2408BA
		opword 0xEC230072
		fdivs f30, f1, f0
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_tou_0000d370@ha
		opword 0x9061007C
		addi r5, r4, double_to_int_tou_0000d370@l
		lis r3, float_32767_tou_0000d3a0@ha
		opword 0x90010078
		addi r4, r3, float_32767_tou_0000d3a0@l
		opword 0xC8450000
		lis r5, float_100_tou_0000d3ac@ha
		opword 0xC8210078
		addi r7, r5, float_100_tou_0000d3ac@l
		opword 0xC0040000
		lis r4, float_400_tou_0000d3a8@ha
		opword 0xEC411028
		lis r3, float_3p1416_tou_0000d344@ha
		lfs f1, float_3p1416_tou_0000d344@l(r3)
		addi r6, r4, float_400_tou_0000d3a8@l
		lis r5, float_0p00761_tou_0000d338@ha
		lis r4, float_0p16605_tou_0000d33c@ha
		opword 0xEC620024
		opword 0xC0470000
		opword 0xC0060000
		lis r3, float_1_tou_0000d340@ha
		lfs f4, float_0p00761_tou_0000d338@l(r5)
		opword 0xECA300BA
		opword 0xFC1E0840
		lfs f3, float_0p16605_tou_0000d33c@l(r4)
		lfs f2, float_1_tou_0000d340@l(r3)
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_tou_0000d348@ha
		lfs f1, float_1p5708_tou_0000d348@l(r3)
		opword 0xFC1E0840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC1E07B2
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC8407B2
		opword 0x48000070
		opword 0xEC1E0828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0x48000054
		lis r3, float_4p7124_tou_0000d34c@ha
		lfs f0, float_4p7124_tou_0000d34c@l(r3)
		opword 0xFC1E0040
		opword 0x40800020
		opword 0xEC3E0828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_tou_0000d348@ha
		opword 0xEC1E0028
		lfs f1, float_1p5708_tou_0000d348@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		lis r3, float_3p1416_tou_0000d344@ha
		opword 0xC01C0010
		lfs f1, float_3p1416_tou_0000d344@l(r3)
		lis r4, float_0p4967_tou_0000d358@ha
		lis r3, float_1_tou_0000d340@ha
		lis r5, float_0p03705_tou_0000d354@ha
		opword 0xFC1E0840
		lfs f3, float_0p4967_tou_0000d358@l(r4)
		opword 0xECC5013A
		lfs f4, float_0p03705_tou_0000d354@l(r5)
		lfs f2, float_1_tou_0000d340@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_tou_0000d348@ha
		lfs f1, float_1p5708_tou_0000d348@l(r3)
		opword 0xFC1E0840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC1E07B2
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x48000064
		opword 0xEC1E0828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000048
		lis r3, float_4p7124_tou_0000d34c@ha
		lfs f0, float_4p7124_tou_0000d34c@l(r3)
		opword 0xFC1E0040
		opword 0x4080001C
		opword 0xEC1E0828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_tou_0000d348@ha
		opword 0xEC1E0028
		lfs f1, float_1p5708_tou_0000d348@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r4, vec3_tou_0000d058@ha
		opword 0xC01C0018
		addi r5, r4, vec3_tou_0000d058@l
		lis r3, float_neg100_tou_0000d3b0@ha
		opword 0x80850000
		opword 0xEC25013C
		opword 0x80050004
		opword 0x90810008
		opword 0x80850008
		opword 0xD0C10008
		lfs f0, float_neg100_tou_0000d3b0@l(r3)
		opword 0x9001000C
		opword 0x80010008
		opword 0x90810010
		opword 0xD001000C
		opword 0xD0210010
		opword 0x8061000C
		opword 0x901C002C
		opword 0x80010010
		opword 0x907C0030
		opword 0x901C0034
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061007C
		lis r4, double_to_int_tou_0000d370@ha
		lfd f1, double_to_int_tou_0000d370@l(r4)
		lis r3, float_32767_tou_0000d3a0@ha
		opword 0x90010078
		addi r5, r3, float_32767_tou_0000d3a0@l
		opword 0xC0450000
		lis r4, float_2_tou_0000d3b8@ha
		opword 0xC8010078
		lis r3, float_4_tou_0000d3b4@ha
		opword 0xEC600828
		lfs f1, float_2_tou_0000d3b8@l(r4)
		lfs f0, float_4_tou_0000d3b4@l(r3)
		opword 0xEC431024
		opword 0xEC02007A
		opword 0xD01C003C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_tou_0000d370@ha
		opword 0x90610074
		addi r5, r4, double_to_int_tou_0000d370@l
		lis r3, float_32767_tou_0000d3a0@ha
		opword 0x90010070
		addi r4, r3, float_32767_tou_0000d3a0@l
		opword 0xC8450000
		lis r3, float_0p1_tou_0000d378@ha
		opword 0xC8010070
		opword 0xC0240000
		opword 0xEC401028
		lfs f0, float_0p1_tou_0000d378@l(r3)
		opword 0xEC220824
		opword 0xEC01003A
		opword 0xD01C0040
		opword 0xC05C0030
		opword 0xC01C0014
		opword 0xC03C0010
		opword 0xEFE20028
		opword 0xC05C0018
		opword 0xC07C002C
		opword 0xC09C0034
		bl distABf
		opword 0xFFC00890
		opword 0xC03C0010
		opword 0xC05C0018
		opword 0xC07C002C
		opword 0xC09C0034
		bl angleABf
		opword 0xC01C003C
		opword 0x3C004330
		lis r4, double_to_int_tou_0000d370@ha
		lis r3, float_0p5_tou_0000d3bc@ha
		opword 0xEC1E0024
		addi r5, r4, double_to_int_tou_0000d370@l
		addi r4, r3, float_0p5_tou_0000d3bc@l
		opword 0x90010090
		opword 0xC8650000
		opword 0x7FC3F378
		opword 0xFC00001E
		opword 0x90010088
		opword 0xC0240000
		opword 0x389C0010
		opword 0xD8010080
		opword 0x80010084
		opword 0xB01C0044
		opword 0xA81C0044
		opword 0xC09C0040
		opword 0x6C008000
		opword 0x90010094
		opword 0xC8010090
		opword 0x9001008C
		opword 0xEC001828
		opword 0xC8410088
		opword 0xEC1F0024
		opword 0xEC421828
		opword 0xEC4400B2
		opword 0xEC02007A
		opword 0xD01C0038
		bl psndSFXOn_3D
		opword 0x48000294
		opword 0xC03F008C
		opword 0xC05F0094
		opword 0xC07C0010
		opword 0xC09C0018
		bl angleABf
		opword 0xFFC00890
		bl cloudGetBreathDir
		opword 0x38000014
		lis r3, vec3_tou_0000d064@ha
		opword 0xB01C0002
		addi r4, r3, vec3_tou_0000d064@l
		lis r5, float_0p5_tou_0000d3bc@ha
		opword 0xEC3E082A
		opword 0x80640000
		opword 0x80040004
		lfs f0, float_0p5_tou_0000d3bc@l(r5)
		opword 0x907C002C
		opword 0xEFC10032
		opword 0x901C0030
		opword 0x80040008
		opword 0x901C0034
		bl rand
		opword 0x6C648000
		opword 0x3C004330
		lis r3, float_6p2832_tou_0000d32c@ha
		opword 0x90810094
		lfs f0, float_6p2832_tou_0000d32c@l(r3)
		lis r5, double_to_int_tou_0000d370@ha
		opword 0x90010090
		lis r3, float_360_tou_0000d334@ha
		lfd f3, double_to_int_tou_0000d370@l(r5)
		opword 0xEC2007B2
		lfs f0, float_360_tou_0000d334@l(r3)
		lis r4, float_32767_tou_0000d3a0@ha
		opword 0xC8410090
		lis r5, float_0p00761_tou_0000d338@ha
		opword 0xEFC10024
		lis r3, float_3p1416_tou_0000d344@ha
		lfs f5, float_0p00761_tou_0000d338@l(r5)
		lfs f1, float_3p1416_tou_0000d344@l(r3)
		lis r3, float_1_tou_0000d340@ha
		opword 0xEC621828
		lfs f2, float_32767_tou_0000d3a0@l(r4)
		lis r4, float_0p1_tou_0000d378@ha
		addi r6, r4, float_0p1_tou_0000d378@l
		opword 0xFC1E0840
		opword 0xEC431024
		opword 0xC0060000
		lis r4, float_0p16605_tou_0000d33c@ha
		lfs f4, float_0p16605_tou_0000d33c@l(r4)
		lfs f3, float_1_tou_0000d340@l(r3)
		opword 0xEFE2003A
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_tou_0000d348@ha
		lfs f1, float_1p5708_tou_0000d348@l(r3)
		opword 0xFC1E0840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC1E07B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA507B2
		opword 0x48000070
		opword 0xEC1E0828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0x48000054
		lis r3, float_4p7124_tou_0000d34c@ha
		lfs f0, float_4p7124_tou_0000d34c@l(r3)
		opword 0xFC1E0040
		opword 0x40800020
		opword 0xEC3E0828
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_tou_0000d348@ha
		opword 0xEC1E0028
		lfs f1, float_1p5708_tou_0000d348@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0xEC1F0172
		opword 0xD01C0038
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_tou_0000d370@ha
		opword 0x90610094
		addi r5, r4, double_to_int_tou_0000d370@l
		lis r3, float_32767_tou_0000d3a0@ha
		opword 0x90010090
		addi r4, r3, float_32767_tou_0000d3a0@l
		opword 0xC8450000
		lis r3, float_0p03_tou_0000d3c0@ha
		opword 0xC8210090
		addi r6, r3, float_0p03_tou_0000d3c0@l
		opword 0xC0040000
		lis r5, float_0p03705_tou_0000d354@ha
		opword 0xEC411028
		lis r3, float_3p1416_tou_0000d344@ha
		lfs f1, float_3p1416_tou_0000d344@l(r3)
		lis r4, float_0p4967_tou_0000d358@ha
		lis r3, float_1_tou_0000d340@ha
		lfs f4, float_0p03705_tou_0000d354@l(r5)
		opword 0xEC420024
		opword 0xC0060000
		lfs f3, float_0p4967_tou_0000d358@l(r4)
		opword 0xEC02003A
		lfs f2, float_1_tou_0000d340@l(r3)
		opword 0xFC1E0840
		opword 0xD01C003C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_tou_0000d348@ha
		lfs f1, float_1p5708_tou_0000d348@l(r3)
		opword 0xFC1E0840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC1E07B2
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x48000064
		opword 0xEC1E0828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000048
		lis r3, float_4p7124_tou_0000d34c@ha
		lfs f0, float_4p7124_tou_0000d34c@l(r3)
		opword 0xFC1E0040
		opword 0x4080001C
		opword 0xEC1E0828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_tou_0000d348@ha
		opword 0xEC1E0028
		lfs f1, float_1p5708_tou_0000d348@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC002050
		opword 0x38000078
		opword 0x7FA3EB78
		opword 0x389C0010
		opword 0xEC1F0032
		opword 0xD01C0040
		opword 0xB01C0044
		bl psndSFXOn_3D
		opword 0x3B7B0001
		opword 0x3B9C0048
		opword 0x807A0000
		opword 0x80030000
		opword 0x7C1B0000
		opword 0x4180F950
		opword 0x90030510
		bl extGetPosePtr
		lis r4, fan_wp@ha
		opword 0x3B800000
		addi r31, r4, fan_wp@l
		opword 0x7C7D1B78
		opword 0x809F0000
		opword 0x83C40004
		opword 0x480004D4
		opword 0xA81E0002
		opword 0x2C000014
		opword 0x418203A0
		opword 0x4080001C
		opword 0x2C00000A
		opword 0x41820190
		opword 0x4080042C
		opword 0x2C000000
		opword 0x41820020
		opword 0x48000420
		opword 0x2C000065
		opword 0x41820418
		opword 0x40800414
		opword 0x2C000064
		opword 0x408003F4
		opword 0x48000408
		opword 0x387E001C
		opword 0x7C641B78
		bl PSVECNormalize
		opword 0x387E001C
		bl PSVECMag
		opword 0x80FE0010
		lis r3, float_4_tou_0000d3b4@ha
		opword 0x801E0014
		addi r6, r3, float_4_tou_0000d3b4@l
		lis r3, float_25_tou_0000d3c4@ha
		lis r4, zero_tou_0000d328@ha
		opword 0x9001003C
		addi r5, r3, float_25_tou_0000d3c4@l
		opword 0xC0060000
		addi r6, r4, zero_tou_0000d328@l
		opword 0xC041003C
		opword 0x3861002C
		opword 0x90E10038
		opword 0x38800000
		opword 0xEC42002A
		opword 0xC0050000
		opword 0x801E0018
		opword 0xEC00082A
		opword 0xC0260000
		opword 0x90010040
		opword 0xD041003C
		opword 0x80BE001C
		opword 0x801E0020
		opword 0x90A10044
		opword 0x90010048
		opword 0x801E0024
		opword 0x9001004C
		opword 0xD0210048
		opword 0xD0010068
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x41820018
		opword 0x387E001C
		opword 0x3881005C
		opword 0x7C651B78
		bl C_VECReflect
		opword 0x48000044
		opword 0xC05E0010
		lis r3, float_0p6_tou_0000d3c8@ha
		opword 0xC01E001C
		lfs f1, float_0p6_tou_0000d3c8@l(r3)
		opword 0xEC02002A
		opword 0xD01E0010
		opword 0xC05E0018
		opword 0xC01E0024
		opword 0xEC02002A
		opword 0xD01E0018
		opword 0xC01E001C
		opword 0xEC000072
		opword 0xD01E001C
		opword 0xC01E0024
		opword 0xEC000072
		opword 0xD01E0024
		lis r3, float_neg350_tou_0000d3cc@ha
		opword 0xC03E0010
		lfs f0, float_neg350_tou_0000d3cc@l(r3)
		opword 0xFC010040
		opword 0x40800008
		opword 0xD01E0010
		lis r3, float_350_tou_0000d3d0@ha
		opword 0xC03E0010
		lfs f0, float_350_tou_0000d3d0@l(r3)
		opword 0xFC010040
		opword 0x40810008
		opword 0xD01E0010
		opword 0x6F838000
		opword 0x3C004330
		opword 0x90610094
		lis r4, double_to_int_tou_0000d370@ha
		lfd f2, double_to_int_tou_0000d370@l(r4)
		lis r3, float_100_tou_0000d3ac@ha
		opword 0x90010090
		lis r4, float_195_tou_0000d3d4@ha
		lfs f0, float_100_tou_0000d3ac@l(r3)
		opword 0xC8210090
		opword 0xC07E0018
		opword 0xEC211028
		lfs f2, float_195_tou_0000d3d4@l(r4)
		opword 0xEC010024
		opword 0xEC02002A
		opword 0xFC030040
		opword 0x408102AC
		opword 0xD01E0018
		opword 0x480002A4
		opword 0xC03E0014
		opword 0xC01E0038
		opword 0xEC01002A
		opword 0xD01E0014
		opword 0xC03E0038
		opword 0xC01E0040
		opword 0xEC010028
		opword 0xD01E0038
		opword 0xC03E0010
		opword 0xC05E0018
		opword 0xC07E002C
		opword 0xC09E0034
		bl angleABf
		lis r3, float_6p2832_tou_0000d32c@ha
		lis r6, float_0p00761_tou_0000d338@ha
		addi r5, r3, float_6p2832_tou_0000d32c@l
		lis r4, float_360_tou_0000d334@ha
		opword 0xC0050000
		lis r5, float_0p16605_tou_0000d33c@ha
		lis r3, float_3p1416_tou_0000d344@ha
		lfs f4, float_0p00761_tou_0000d338@l(r6)
		opword 0xEC400072
		lfs f0, float_360_tou_0000d334@l(r4)
		lfs f1, float_3p1416_tou_0000d344@l(r3)
		lis r4, float_1_tou_0000d340@ha
		lfs f3, float_0p16605_tou_0000d33c@l(r5)
		opword 0xECA20024
		lfs f2, float_1_tou_0000d340@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_tou_0000d348@ha
		lfs f1, float_1p5708_tou_0000d348@l(r3)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0x48000070
		opword 0xEC050828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0x48000054
		lis r3, float_4p7124_tou_0000d34c@ha
		lfs f0, float_4p7124_tou_0000d34c@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_tou_0000d348@ha
		opword 0xEC050028
		lfs f1, float_1p5708_tou_0000d348@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		lis r3, float_3p1416_tou_0000d344@ha
		opword 0xC05E003C
		lfs f1, float_3p1416_tou_0000d344@l(r3)
		lis r4, float_0p4967_tou_0000d358@ha
		opword 0xC01E0010
		lis r5, float_0p03705_tou_0000d354@ha
		opword 0xFC050840
		lis r3, float_1_tou_0000d340@ha
		opword 0xEC02013A
		lfs f4, float_0p03705_tou_0000d354@l(r5)
		lfs f3, float_0p4967_tou_0000d358@l(r4)
		lfs f2, float_1_tou_0000d340@l(r3)
		opword 0xD01E0010
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_tou_0000d348@ha
		lfs f1, float_1p5708_tou_0000d348@l(r3)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x48000064
		opword 0xEC050828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000048
		lis r3, float_4p7124_tou_0000d34c@ha
		lfs f0, float_4p7124_tou_0000d34c@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_tou_0000d348@ha
		opword 0xEC050028
		lfs f1, float_1p5708_tou_0000d348@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC202050
		opword 0xC05E003C
		opword 0xC01E0018
		opword 0xEC02007A
		opword 0xD01E0018
		opword 0xA87E0044
		opword 0x3863FFFF
		opword 0x7C600735
		opword 0xB07E0044
		opword 0x408000AC
		opword 0x38000064
		opword 0xB01E0002
		opword 0x480000A0
		opword 0xA87E0044
		opword 0x3863FFFF
		opword 0x7C600735
		opword 0xB07E0044
		opword 0x40810068
		opword 0xC03E002C
		opword 0xC01E0038
		opword 0xEC01002A
		opword 0xD01E002C
		opword 0xC03E0030
		opword 0xC01E003C
		opword 0xEC01002A
		opword 0xD01E0030
		opword 0xC03E0034
		opword 0xC01E0040
		opword 0xEC01002A
		opword 0xD01E0034
		opword 0xC03E0010
		opword 0xC01E002C
		opword 0xEC01002A
		opword 0xD01E0010
		opword 0xC03E0014
		opword 0xC01E0030
		opword 0xEC01002A
		opword 0xD01E0014
		opword 0xC03E0018
		opword 0xC01E0034
		opword 0xEC01002A
		opword 0xD01E0018
		opword 0x48000028
		opword 0x38000064
		opword 0xB01E0002
		opword 0x4800001C
		opword 0x801D0000
		opword 0x5400003A
		opword 0x901D0000
		opword 0xA87E0002
		opword 0x38030001
		opword 0xB01E0002
		opword 0xA01E0000
		opword 0x540007FF
		opword 0x4182001C
		lis r3, fan_wp@ha
		lwz r4, fan_wp@l(r3)
		opword 0x80640510
		opword 0x3803FFFF
		opword 0x90040510
		opword 0x48000024
		opword 0xA81E0002
		opword 0x2C000000
		opword 0x41820018
		lis r3, fan_wp@ha
		lwz r4, fan_wp@l(r3)
		opword 0x80640510
		opword 0x3803FFFF
		opword 0x90040510
		opword 0xC01E0010
		opword 0x807D000C
		opword 0xD003000C
		opword 0xC01E0014
		opword 0x807D000C
		opword 0xD003001C
		opword 0xC01E0018
		opword 0x807D000C
		opword 0xD003002C
		opword 0xC0210014
		opword 0xC041001C
		opword 0xC07E0010
		opword 0xC09E0018
		bl angleABf
		opword 0xD03D0004
		opword 0x3B9C0001
		opword 0x3BBD0020
		opword 0x3BDE0048
		opword 0x807F0000
		opword 0x80030000
		opword 0x7C1C0000
		opword 0x4180FB24
		opword 0x80630514
		opword 0x38810014
		bl psndSFX_pos
		lis r3, fan_wp@ha
		lwz r5, fan_wp@l(r3)
		opword 0x88850518
		opword 0x80650510
		opword 0x80050000
		opword 0x7C8419D6
		opword 0x80650514
		opword 0x7C0403D6
		opword 0x5404063E
		bl psndSFX_vol
	}
}
#pragma pop
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

EVT_BEGIN(mario_momikucha_msg)
    SET_VALUE(LW(10), 0)
    LOOP(0)
        CALL(evt_sub_random, 5, LW(0))
        ADD(LW(0), 2)
        MULTIPLY(LW(0), 1000)
        WAIT_MS(LW(0))
        CALL(evt_sub_random, 200, LW(0))
        CALL(evt_sub_random, 200, LW(1))
        SUBTRACT(LW(0), 50)
        SUBTRACT(LW(1), 50)
        CALL(evt_msg_toge, 2, LW(0), 30, LW(1))
        CALL(evt_end_count, LW(0))
        IF_INT_LESS(LW(0), 10)
            RETURN
        END_IF
        BEGIN_INLINE_EVENT
            SWITCH(LW(10))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004740)), 0, 0)
                CASE_EQUAL(1)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004750)), 0, 0)
                CASE_EQUAL(2)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004760)), 0, 0)
                CASE_EQUAL(3)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004770)), 0, 0)
                CASE_EQUAL(4)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004780)), 0, 0)
                CASE_EQUAL(5)
                CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004790)), 0, 0)
            END_SWITCH
        END_INLINE_EVENT
        ADD(LW(10), 1)
        IF_INT_GREATER(LW(10), 5)
            SET_VALUE(LW(10), 0)
        END_IF
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_momikucha)
    SET_VALUE(LF(0), 0)
    SET_VALUE(GF(10), 0)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 133)
        IF_INT_EQUAL(GSWF(2402), 0)
            SET_VALUE(GSWF(2402), 1)
            SET_VALUE(LF(0), 1)
            SET_VALUE(GF(10), 0)
        END_IF
    END_IF
    CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        IF_INT_EQUAL(GSWF(2403), 0)
            SET_VALUE(GSWF(2403), 1)
            SET_VALUE(LF(0), 1)
            SET_VALUE(GF(10), 1)
        END_IF
    END_IF
    IF_INT_EQUAL(LF(0), 0)
        RETURN
    END_IF
    CALL(evt_npc_entry, STRING(((char*)tou_02_str_000047A0)), STRING(((char*)tou_02_str_000046BC)))
    CALL(evt_npc_entry, STRING(((char*)tou_02_str_000047A4)), STRING(((char*)tou_02_str_000046D0)))
    CALL(evt_npc_entry, STRING(((char*)tou_02_str_000047AC)), STRING(((char*)tou_02_str_000046E4)))
    CALL(evt_npc_set_position, STRING(((char*)tou_02_str_000047A0)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)tou_02_str_000047A4)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)tou_02_str_000047AC)), 0, -1000, 0)
    CALL(evt_ext_entry, 200, PTR(ext_fan_data), PTR(ext_fan_init), PTR(ext_fan_main), PTR(ext_fan_dispent))
    IF_INT_EQUAL(GF(10), 0)
        CALL(evt_npc_set_position, STRING(((char*)tou_02_str_000045C0)), 0, 0, 0)
        CALL(evt_npc_change_interrupt, STRING(((char*)tou_02_str_000045C0)), 1, PTR(move_champ))
        ELSE
        SPAWN_EVENT(PTR(mario_momikucha_msg))
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(evt_key)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_party_yoshi_ride, 0, 0)
    SET_VALUE(GSW(0), 154)
    CALL(evt_item_get_item_end_wait, STRING(((char*)tou_02_str_000047B4)))
    CALL(evt_party_stop, 0)
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING(((char*)tou_02_str_000047B8)))
    WAIT_MS(500)
    BEGIN_INLINE_EVENT_GET_ID(LW(11))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_02_str_000047C8)), LW(0), LW(1), LW(2), 0)
        CALL(evt_eff_fukidashi, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(1500)
    END_INLINE_EVENT
    CALL(evt_snd_bgmoff, 1024)
    CALL(evt_snd_bgmon, 1, STRING(((char*)str_000047E0)))
    SPAWN_EVENT_GET_ID(PTR(evt_sub_mail_vibration), LW(10))
    WAIT_MS(500)
    LOOP(0)
        IS_EVENT_RUNNING(LW(11), LW(12))
        IF_INT_EQUAL(LW(12), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_bikkuri)
    LOOP(0)
        CALL(evt_key_get_buttontrg, 0, LW(0))
        IF_INT_EQUAL(LW(0), 256)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_off)
    CALL(evt_snd_bgmoff, 513)
    CALL(evt_snd_bgmon, 288, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_02_str_000047F8)), LW(0), LW(1), LW(2), 0)
    DELETE_EVENT(LW(10))
    WAIT_FRAMES(1)
    CALL(evt_sub_rumble_onoff, 1, 0)
    CALL(evt_mario_set_pose, STRING(((char*)tou_02_str_0000480C)))
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_02_str_00004814)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)tou_02_str_00004828)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004830)), 0, 0)
    CALL(evt_mario_set_pose, STRING(((char*)tou_02_str_000046A8)))
    CALL(evt_pouch_receive_mail, 15)
    CALL(evt_pouch_open_mail, 15)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

#ifdef NONMATCHING
void ext_fan_dispent(void) {
    pose_main();
    dispEntry(CAMERA_3D, EXT_LIT(zero_tou_0000d328, 0.0f), 1, fan_disp, NULL);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void ext_fan_dispent(void) {
	char _af_pad[8];
	asm volatile {
		bl extGetPosePtr
		lis r4, fan_wp@ha
		lis r7, float_60_tou_0000d364@ha
		addi r29, r4, fan_wp@l
		lis r6, float_1000_tou_0000d368@ha
		opword 0x813D0000
		lis r5, float_1_tou_0000d340@ha
		lis r4, double_to_int_tou_0000d370@ha
		lis r8, gp@ha
		opword 0x83890004
		opword 0x7C7B1B78
		lfs f28, float_60_tou_0000d364@l(r7)
		addi r30, r8, gp@l
		lfs f29, float_1000_tou_0000d368@l(r6)
		opword 0x3B400000
		lfs f30, float_1_tou_0000d340@l(r5)
		opword 0x3FE08000
		lfd f31, double_to_int_tou_0000d370@l(r4)
		opword 0x3EE04330
		opword 0x480000BC
		opword 0x807F00F8
		opword 0x380003E8
		opword 0x809E0000
		opword 0x38A00000
		opword 0x5463F0BE
		opword 0xA8FC0004
		opword 0x7CC30396
		opword 0x8304003C
		opword 0x801C000C
		opword 0x83240038
		opword 0x7C80C010
		opword 0x801C0008
		opword 0x1CE70028
		opword 0x7C60C910
		addi r22, r7, 0xc
		opword 0x7EC8B214
		bl __div2u
		bl __cvt_ull_flt
		opword 0xEC3C0072
		opword 0xC016001C
		opword 0xEC21E824
		opword 0xEC210024
		opword 0xFC01F040
		opword 0x4C411382
		opword 0x40820014
		opword 0x931C000C
		lis r3, zero_tou_0000d328@ha
		lfs f1, zero_tou_0000d328@l(r3)
		opword 0x933C0008
		opword 0x80760024
		opword 0x3B5A0001
		stw r23, _af_pad+0(r1)
		opword 0x3B9C0048
		opword 0x3803FFFF
		opword 0x80760020
		opword 0x6C008000
		opword 0x9001000C
		opword 0xC8010008
		opword 0xEC00F828
		opword 0xEC000072
		opword 0xFC00001E
		opword 0xD8010010
		opword 0x80010014
		opword 0x7C030214
		opword 0x901B0010
		opword 0x3B7B0020
		opword 0x811D0000
		opword 0x80080000
		opword 0x7C1A0000
		opword 0x4180FF3C
		lis r3, zero_tou_0000d328@ha
		lis r4, fan_disp@ha
		addi r6, r3, zero_tou_0000d328@l
		opword 0xC0260000
		addi r5, r4, fan_disp@l
		opword 0x38600004
		opword 0x38800001
		opword 0x38C00000
		bl dispEntry
	}
}
#pragma pop
#endif

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING
s32 check_hammer(Fan* fan) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;
    f32 rot;
    f32 x;
    f32 z;
    f32 angle;
    f32 dist;
    Vec pos;

    if (mario->position.y > EXT_LIT(zero_tou_0000d328, 0.0f)) {
        return 0;
    }
    if (fan->flags & 1) {
        return 0;
    }
    if (mario->currMotionId == 0x12 && fan_wp->hammerTimer > 10) {
        rot = 6.2831855f * reviseAngle(mario->displayDirection - 90.0f + camGetPtr(CAMERA_3D)->viewYaw) / 360.0f;

        x = mario->position.x + EXT_LIT(float_35_tou_0000d350, 35.0f) * fan_sin(rot);
        z = mario->position.z - 35.0f * fan_cos(rot);
        if (distABf(fan->pos.x, fan->pos.z, x, z) < EXT_LIT(float_35_tou_0000d350, 35.0f)) {
            return 1;
        }
    }
    if (mario->currMotionId == 0x13 && (s32)mario->currSubMotionId == 0x14 && PSVECDistance(&mario->position, &fan->pos) < EXT_LIT(float_65_tou_0000d35c, 65.0f)) {
        return 1;
    }
    party = partyGetPtr(0);
    if (party != NULL && party->currentMemberId == 5 && (party->flags & 0x100)) {
        angle = 6.2831855f * cloudGetBreathDir() / 360.0f;
        dist = cloudGetBreathDist();
        pos.x = party->position.x + dist * fan_sin(angle);
        pos.y = party->position.y;
        pos.z = party->position.z - dist * fan_cos(angle);
        if (angle >= EXT_LIT(zero_tou_0000d328, 0.0f) && PSVECDistance(&pos, &fan->pos) < EXT_LIT(float_30_tou_0000d360, 30.0f)) {
            return 2;
        }
    }
    return 0;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 check_hammer(Fan* fan) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0xDBE10020
		opword 0xF3E10028
		opword 0xBFC10018
		opword 0x7C7E1B78
		bl marioGetPtr
		lis r4, zero_tou_0000d328@ha
		opword 0xC0230090
		lfs f0, zero_tou_0000d328@l(r4)
		opword 0x7C7F1B78
		opword 0xFC010040
		opword 0x4081000C
		opword 0x38600000
		opword 0x48000480
		opword 0xA01E0000
		opword 0x540007FF
		opword 0x4182000C
		opword 0x38600000
		opword 0x4800046C
		opword 0xA01F002E
		opword 0x28000012
		opword 0x40820210
		lis r3, fan_wp@ha
		addi r3, r3, fan_wp@l
		opword 0x80630000
		opword 0x8003050C
		opword 0x2C00000A
		opword 0x408101F8
		opword 0x38600004
		bl camGetPtr
		lis r4, float_90_tou_0000d330@ha
		opword 0xC03F01A8
		lfs f0, float_90_tou_0000d330@l(r4)
		opword 0xC0430114
		opword 0xEC010028
		opword 0xEC20102A
		bl reviseAngle
		lis r3, float_6p2832_tou_0000d32c@ha
		lis r6, float_0p00761_tou_0000d338@ha
		addi r5, r3, float_6p2832_tou_0000d32c@l
		lis r4, float_360_tou_0000d334@ha
		opword 0xC0050000
		lis r5, float_0p16605_tou_0000d33c@ha
		lis r3, float_3p1416_tou_0000d344@ha
		lfs f4, float_0p00761_tou_0000d338@l(r6)
		opword 0xEC400072
		lfs f0, float_360_tou_0000d334@l(r4)
		lfs f1, float_3p1416_tou_0000d344@l(r3)
		lis r4, float_1_tou_0000d340@ha
		lfs f3, float_0p16605_tou_0000d33c@l(r5)
		opword 0xECC20024
		lfs f2, float_1_tou_0000d340@l(r4)
		opword 0xFC060840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_tou_0000d348@ha
		lfs f1, float_1p5708_tou_0000d348@l(r3)
		opword 0xFC060840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC0601B2
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC8401B2
		opword 0x48000070
		opword 0xEC060828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0x48000054
		lis r3, float_4p7124_tou_0000d34c@ha
		lfs f0, float_4p7124_tou_0000d34c@l(r3)
		opword 0xFC060040
		opword 0x40800020
		opword 0xEC260828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_tou_0000d348@ha
		opword 0xEC060028
		lfs f1, float_1p5708_tou_0000d348@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		lis r3, float_3p1416_tou_0000d344@ha
		lis r4, float_35_tou_0000d350@ha
		lfs f1, float_3p1416_tou_0000d344@l(r3)
		lis r5, float_0p03705_tou_0000d354@ha
		lfs f2, float_35_tou_0000d350@l(r4)
		lis r4, float_0p4967_tou_0000d358@ha
		opword 0xC01F008C
		opword 0xFC060840
		lis r3, float_1_tou_0000d340@ha
		lfs f5, float_0p03705_tou_0000d354@l(r5)
		opword 0xEC62013A
		lfs f4, float_0p4967_tou_0000d358@l(r4)
		lfs f2, float_1_tou_0000d340@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_tou_0000d348@ha
		lfs f1, float_1p5708_tou_0000d348@l(r3)
		opword 0xFC060840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC0601B2
		opword 0xECA52038
		opword 0xECA5103A
		opword 0x48000064
		opword 0xEC060828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xECA52038
		opword 0xECA5103A
		opword 0xFCA02850
		opword 0x48000048
		lis r3, float_4p7124_tou_0000d34c@ha
		lfs f0, float_4p7124_tou_0000d34c@l(r3)
		opword 0xFC060040
		opword 0x4080001C
		opword 0xEC060828
		opword 0xEC000032
		opword 0xECA52038
		opword 0xECA5103A
		opword 0xFCA02850
		opword 0x48000020
		lis r3, float_1p5708_tou_0000d348@ha
		opword 0xEC060028
		lfs f1, float_1p5708_tou_0000d348@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xECA52038
		opword 0xECA5103A
		lis r3, float_35_tou_0000d350@ha
		opword 0xC01F0094
		lfs f2, float_35_tou_0000d350@l(r3)
		opword 0xC03E0010
		opword 0xEC82017C
		opword 0xC05E0018
		bl distABf
		lis r3, float_35_tou_0000d350@ha
		lfs f0, float_35_tou_0000d350@l(r3)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600001
		opword 0x48000254
		opword 0xA01F002E
		opword 0x28000013
		opword 0x40820034
		opword 0x801F0044
		opword 0x2C000014
		opword 0x40820028
		opword 0x387F008C
		opword 0x389E0010
		bl PSVECDistance
		lis r3, float_65_tou_0000d35c@ha
		lfs f0, float_65_tou_0000d35c@l(r3)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600001
		opword 0x48000218
		opword 0x38600000
		bl partyGetPtr
		opword 0x7C7F1B79
		opword 0x41820204
		opword 0x881F0031
		opword 0x2C000005
		opword 0x408201F8
		opword 0x801F0000
		opword 0x540005EF
		opword 0x418201EC
		bl cloudGetBreathDir
		lis r4, float_6p2832_tou_0000d32c@ha
		lis r3, float_360_tou_0000d334@ha
		lfs f2, float_6p2832_tou_0000d32c@l(r4)
		lfs f0, float_360_tou_0000d334@l(r3)
		opword 0xEC220072
		opword 0xEFE10024
		bl cloudGetBreathDist
		lis r3, float_3p1416_tou_0000d344@ha
		lis r5, float_0p00761_tou_0000d338@ha
		lfs f2, float_3p1416_tou_0000d344@l(r3)
		lis r4, float_0p16605_tou_0000d33c@ha
		lis r3, float_1_tou_0000d340@ha
		lfs f5, float_0p00761_tou_0000d338@l(r5)
		opword 0xFC1F1040
		lfs f4, float_0p16605_tou_0000d33c@l(r4)
		lfs f3, float_1_tou_0000d340@l(r3)
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_tou_0000d348@ha
		lfs f2, float_1p5708_tou_0000d348@l(r3)
		opword 0xFC1F1040
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC1F07F2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA507F2
		opword 0x48000070
		opword 0xEC1F1028
		opword 0xEC420028
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA500B2
		opword 0x48000054
		lis r3, float_4p7124_tou_0000d34c@ha
		lfs f0, float_4p7124_tou_0000d34c@l(r3)
		opword 0xFC1F0040
		opword 0x40800020
		opword 0xEC5F1028
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA500B2
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_tou_0000d348@ha
		opword 0xEC1F0028
		lfs f2, float_1p5708_tou_0000d348@l(r3)
		opword 0xEC420028
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA500B2
		opword 0xFCA02850
		opword 0xC01F0058
		lis r3, float_3p1416_tou_0000d344@ha
		lfs f2, float_3p1416_tou_0000d344@l(r3)
		lis r4, float_0p4967_tou_0000d358@ha
		opword 0xEC01017A
		lis r5, float_0p03705_tou_0000d354@ha
		lis r3, float_1_tou_0000d340@ha
		opword 0xFC1F1040
		lfs f5, float_0p03705_tou_0000d354@l(r5)
		opword 0xD0010008
		lfs f4, float_0p4967_tou_0000d358@l(r4)
		opword 0xC01F005C
		lfs f3, float_1_tou_0000d340@l(r3)
		opword 0xD001000C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_tou_0000d348@ha
		lfs f2, float_1p5708_tou_0000d348@l(r3)
		opword 0xFC1F1040
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC1F07F2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0x48000064
		opword 0xEC1F1028
		opword 0xEC020028
		opword 0xEC000032
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xFCA02850
		opword 0x48000048
		lis r3, float_4p7124_tou_0000d34c@ha
		lfs f0, float_4p7124_tou_0000d34c@l(r3)
		opword 0xFC1F0040
		opword 0x4080001C
		opword 0xEC1F1028
		opword 0xEC000032
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xFCA02850
		opword 0x48000020
		lis r3, float_1p5708_tou_0000d348@ha
		opword 0xEC1F0028
		lfs f2, float_1p5708_tou_0000d348@l(r3)
		opword 0xEC020028
		opword 0xEC000032
		opword 0xECA52038
		opword 0xECA5183A
		lis r3, zero_tou_0000d328@ha
		opword 0xC05F0060
		lfs f0, zero_tou_0000d328@l(r3)
		opword 0xEC21117C
		opword 0xFC1F0040
		opword 0xD0210010
		opword 0x4C411382
		opword 0x40820028
		opword 0x38610008
		opword 0x389E0010
		bl PSVECDistance
		lis r3, float_30_tou_0000d360@ha
		lfs f0, float_30_tou_0000d360@l(r3)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600002
		opword 0x48000008
		opword 0x38600000
		opword 0xE3E10028
		opword 0xCBE10020
		opword 0xBBC10018
		opword 0x80010034
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

s32 evt_end_count(EventEntry* event, BOOL isFirstCall) {
    evtSetValue(event, event->args[0], fan_wp->count);
    return EVT_RETURN_DONE;
}

__declspec(section ".data") static EVT_BEGIN(evt_poster_1)
    SET_VALUE(GSWF(2456), 1)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_poster_2)
    SET_VALUE(GSWF(2457), 1)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_poster_3)
    SET_VALUE(GSWF(2458), 1)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_poster_4)
    SET_VALUE(GSWF(2459), 1)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_poster_5)
    SET_VALUE(GSWF(2460), 1)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_poster_6)
    SET_VALUE(GSWF(2461), 1)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_poster_7)
    SET_VALUE(GSWF(2462), 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_poster_8)
    SET_VALUE(GSWF(2463), 1)
    IF_INT_EQUAL(GSW(0), 153)
        CALL(evt_mapobj_get_position, STRING(((char*)tou_02_str_00004840)), LW(0), LW(1), LW(2))
        CALL(evt_item_entry, STRING(((char*)tou_02_str_000047B4)), 19, LW(0), LW(1), LW(2), 4, -1, PTR(evt_key))
        CALL(evt_item_set_move_dir_speed, STRING(((char*)tou_02_str_000047B4)), FLOAT(180.0f), FLOAT((90.0f)))
        CALL(evt_item_set_gravity, STRING(((char*)tou_02_str_000047B4)), FLOAT((1.0f)))
        CALL(evt_item_set_bound_rate, STRING(((char*)tou_02_str_000047B4)), FLOAT(0.5996094f))
        CALL(evt_item_set_jump_power, STRING(((char*)tou_02_str_000047B4)), FLOAT(500.0f))
        CALL(evt_item_status_on, STRING(((char*)tou_02_str_000047B4)), 16)
    END_IF
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_poster_9)
    SET_VALUE(GSWF(2464), 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_after_peach)
    CALL(evt_cam3d_evt_set, 0, 120, 494, 0, 40, 0, 0, 11)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_dir, 0, 270, 0)
    CALL(evt_mario_set_pos, 25, 0, 75)
    CALL(evt_party_set_pos, 0, 60, 0, 100)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_02_str_00003BE0)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_02_str_00003BD4)), 1)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_fade_end_wait)
    WAIT_MS(2000)
    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004848)), 0, STRING(((char*)tou_02_str_000045D0)))
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_02_str_00004688)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)tou_02_str_000046A0)))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING(((char*)tou_02_str_000046A8)))
    CALL(evt_cam3d_evt_set, 0, 100, 395, 0, 40, 0, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_0000485C)), 0, STRING(((char*)tou_02_str_000045D0)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -40, 100, 395, -40, 40, 0, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004870)), 0, STRING(((char*)tou_02_str_000045C0)))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)tou_02_str_00004884)), 0, STRING(((char*)tou_02_str_000045DC)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 100, 395, 0, 40, 0, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)str_00004898)), 0, STRING(((char*)tou_02_str_000045D0)))
    WAIT_MS(300)
    CALL(evt_mario_set_pose, STRING(((char*)tou_02_str_000048AC)))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING(((char*)tou_02_str_000046A8)))
    CALL(evt_cam3d_evt_set, 0, 120, 494, 0, 40, 0, 500, 11)
    CALL(evt_party_run, 0)
    CALL(evt_mario_mov_pos2, 0, 190, FLOAT(80.0f))
    CALL(evt_bero_mapchange, STRING(((char*)str_00003C34)), STRING(((char*)tou_02_str_00003C3C)))
    RETURN
EVT_END()

EVT_BEGIN(tou_02_init_evt)
    SWITCH(GSW(0))
        CASE_BETWEEN(127, 137)
        CALL(evt_snd_bgmon, 512, STRING(((char*)tou_02_str_000048B4)))
        CALL(evt_snd_envon, 272, STRING(((char*)tou_02_str_000048C4)))
        CALL(evt_snd_bgmoff, 26624)
        CASE_GREATER_OR_EQUAL(165)
        CALL(evt_snd_bgmon, 512, STRING(((char*)tou_02_str_000048B4)))
        CALL(evt_snd_envon, 272, STRING(((char*)tou_02_str_000048C4)))
        CALL(evt_snd_bgmoff, 26624)
        CASE_DEFAULT
        CALL(evt_snd_bgmon, 512, STRING(((char*)tou_02_str_000048D4)))
        CALL(evt_snd_bgmon, 160, 0)
        CALL(evt_snd_envon, 272, STRING(((char*)tou_02_str_000048C4)))
    END_SWITCH
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    IF_INT_EQUAL(GSWF(2374), 1)
        CALL_CHILD(PTR(bero_case_entry))
        SPAWN_EVENT(PTR(evt_tougi2))
        ELSE
        CALL_CHILD(PTR(evt_bero_info_run))
    END_IF
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL_CHILD(PTR(init_kinopio_f))
    CALL(evt_npc_change_interrupt, STRING(((char*)str_000042F4)), 6, PTR(talk_kinopio_f))
    CALL(evt_mobj_kururing_floor, STRING(((char*)tou_02_str_000048E4)), -260, 0, -120, STRING(((char*)tou_02_str_000048F0)), 125, GSWF(5623))
    IF_INT_LESS(GSW(0), 129)
        SET_VALUE(LW(0), 3)
        CALL_CHILD(PTR(bero_case_switch_off))
        SET_VALUE(LW(0), 4)
        CALL_CHILD(PTR(bero_case_switch_off))
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(0), 172)
        IF_INT_EQUAL(GSWF(2497), 0)
            SET_VALUE(LW(0), 3)
            CALL_CHILD(PTR(bero_case_switch_off))
            SET_VALUE(LW(0), 4)
            CALL_CHILD(PTR(bero_case_switch_off))
        END_IF
    END_IF
    IF_INT_EQUAL(GSW(0), 171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING(((char*)str_000042F4)), 0, -1000, 0)
            CALL(evt_npc_set_position, STRING(((char*)tou_02_str_00004590)), 0, -1000, 0)
        END_IF
    END_IF
    IF_INT_EQUAL(GSW(0), 171)
        CALL(evt_mario_get_party, LW(15))
        IF_INT_EQUAL(LW(15), 0)
            CALL(evt_mario_set_party, 0, 1)
            CALL(evt_party_run, 0)
            CALL(evt_pouch_mario_recovery)
            CALL(evt_pouch_all_party_recovery)
        END_IF
        CALL(evt_pouch_remove_item, 65, LW(0))
        SPAWN_EVENT(PTR(evt_after_peach))
        SET_VALUE(GSWF(2402), 1)
        SET_VALUE(GSWF(2403), 1)
    END_IF
    CALL(evt_map_playanim, STRING(((char*)tou_02_str_000048F8)), 1, 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            LOOP(0)
                CALL(evt_map_checkanim, STRING(((char*)tou_02_str_000048F8)), LW(0), LW(1))
                IF_INT_LESS(LW(1), 5333)
                    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_02_str_00004904)), 178, 0, -98, 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            WAIT_FRAMES(10)
            CALL(evt_snd_sfxon_3d, STRING(((char*)tou_02_str_00004920)), 178, 0, -98, 0)
            LOOP(0)
                CALL(evt_map_checkanim, STRING(((char*)tou_02_str_000048F8)), LW(0), LW(1))
                IF_INT_LESS(LW(1), 2000)
                    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_02_str_00004904)), 178, 0, -98, 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            WAIT_FRAMES(5)
            CALL(evt_snd_sfxon_3d, STRING(((char*)tou_02_str_00004920)), 178, 0, -98, 0)
            LOOP(0)
                CALL(evt_map_checkanim, STRING(((char*)tou_02_str_000048F8)), LW(0), LW(1))
                IF_INT_GREATER(LW(1), 6333)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
        END_LOOP
    END_INLINE_EVENT
    CALL_CHILD(PTR(evt_momikucha))
    CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
    SWITCH(LW(0))
        CASE_LESS(2)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_02_str_0000493C)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_02_str_00004944)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)tou_02_str_0000494C)), 1)
        CALL(evt_hitobj_onoff, STRING(((char*)tou_02_str_00004954)), 1, 0)
        CALL(evt_hitobj_onoff, STRING(((char*)tou_02_str_0000495C)), 1, 1)
        CALL(evt_cloud_init)
        IF_INT_EQUAL(GSWF(2457), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)tou_02_str_00004964)), STRING(((char*)tou_02_str_0000496C)), PTR(evt_poster_2))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)tou_02_str_00004964)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)tou_02_str_0000496C)), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2458), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)tou_02_str_00004974)), STRING(((char*)tou_02_str_0000497C)), PTR(evt_poster_3))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)tou_02_str_00004974)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)tou_02_str_0000497C)), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2459), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)tou_02_str_00004984)), STRING(((char*)tou_02_str_0000498C)), PTR(evt_poster_4))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)tou_02_str_00004984)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)tou_02_str_0000498C)), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2460), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)tou_02_str_00004994)), STRING(((char*)tou_02_str_0000499C)), PTR(evt_poster_5))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)tou_02_str_00004994)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)tou_02_str_0000499C)), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2461), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)tou_02_str_000049A4)), STRING(((char*)tou_02_str_000049AC)), PTR(evt_poster_6))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)tou_02_str_000049A4)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)tou_02_str_000049AC)), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2462), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)tou_02_str_000049B4)), STRING(((char*)tou_02_str_000049BC)), PTR(evt_poster_7))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)tou_02_str_000049B4)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)tou_02_str_000049BC)), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2463), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)tou_02_str_00004840)), STRING(((char*)tou_02_str_000049C4)), PTR(evt_poster_8))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)tou_02_str_00004840)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)tou_02_str_000049C4)), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2464), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)tou_02_str_000049CC)), STRING(((char*)tou_02_str_000049D4)), PTR(evt_poster_9))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)tou_02_str_000049CC)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)tou_02_str_000049D4)), 1, 0)
        END_IF
        CASE_LESS(11)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_02_str_0000493C)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)tou_02_str_00004944)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_02_str_0000494C)), 1)
        CALL(evt_hitobj_onoff, STRING(((char*)tou_02_str_00004954)), 1, 1)
        CALL(evt_hitobj_onoff, STRING(((char*)tou_02_str_0000495C)), 1, 0)
        CALL(evt_cloud_init)
        IF_INT_EQUAL(GSWF(2456), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)tou_02_str_000049DC)), STRING(((char*)tou_02_str_000049E4)), PTR(evt_poster_1))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)tou_02_str_000049DC)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)tou_02_str_000049E4)), 1, 0)
        END_IF
        CASE_DEFAULT
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)tou_02_str_0000493C)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_02_str_00004944)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_02_str_0000494C)), 1)
        CALL(evt_hitobj_onoff, STRING(((char*)tou_02_str_00004954)), 1, 0)
        CALL(evt_hitobj_onoff, STRING(((char*)tou_02_str_0000495C)), 1, 0)
    END_SWITCH
    IF_INT_EQUAL(GSWF(2463), 1)
        IF_INT_EQUAL(GSW(0), 153)
            CALL(evt_item_entry, STRING(((char*)tou_02_str_000047B4)), 19, -110, 200, -180, 16, -1, PTR(evt_key))
        END_IF
    END_IF
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)tou_02_str_000049EC)), 2)
    RETURN
EVT_END()


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const char tou_02_str_00003BC0[20] = "SFX_STG3_AUTO_DOOR1";
__declspec(section ".rodata") const char tou_02_str_00003BD4[12] = "door_1_b\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00003BE0[12] = "door_1_a\0\0\0";
__declspec(section ".rodata") const char str_00003BEC[12] = "door_2_b\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00003BF8[12] = "door_2_a\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00003C04[12] = "door_3_b\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00003C10[12] = "door_3_a\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00003C1C[8] = "door_4\0";
__declspec(section ".rodata") const char tou_02_str_00003C24[8] = "door_5\0";
__declspec(section ".rodata") const char tou_02_str_00003C2C[8] = "s_bero\0";
__declspec(section ".rodata") const char str_00003C34[8] = "tou_01\0";
__declspec(section ".rodata") const char tou_02_str_00003C3C[12] = "a_door_mon\0";
__declspec(section ".rodata") const char tou_02_str_00003C48[12] = "n_bero_1\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00003C54[8] = "tou_03\0";
__declspec(section ".rodata") const char str_00003C5C[12] = "s_bero_1\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00003C68[12] = "n_bero_2\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00003C74[12] = "s_bero_2\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00003C80[12] = "n_bero_3\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00003C8C[8] = "tou_04\0";
__declspec(section ".rodata") const char tou_02_str_00003C94[8] = "e_bero\0";
__declspec(section ".rodata") const char tou_02_str_00003C9C[12] = "n_bero_4\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00003CA8[8] = "w_bero\0";
__declspec(section ".rodata") const char tou_02_str_00003CB0[4] = "me\0";
__declspec(section ".rodata") const char tou_02_str_00003CB4[16] = "\x83K\x81[\x83h\x83}\x83\x93\x82P\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00003CC4[8] = "mario\0\0";
__declspec(section ".rodata") const char tou_02_str_00003CCC[16] = "\x83K\x81[\x83h\x83}\x83\x93\x82Q\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00003CDC[12] = "stg3_tou_24";
__declspec(section ".rodata") const char tou_02_str_00003CE8[12] = "stg3_tou_37";
__declspec(section ".rodata") const char tou_02_str_00003CF4[16] = "stg3_tou_37_01\0";
__declspec(section ".rodata") const char tou_02_str_00003D04[16] = "stg3_tou_37_02\0";
__declspec(section ".rodata") const char tou_02_str_00003D14[20] = "stg3_tou_re_002_1\0\0";
__declspec(section ".rodata") const char tou_02_str_00003D28[16] = "stg3_tou_re_001";
__declspec(section ".rodata") const char tou_02_str_00003D38[16] = "stg3_tou_re_002";
__declspec(section ".rodata") const char tou_02_str_00003D48[20] = "stg3_npc_02_01_01\0\0";
__declspec(section ".rodata") const char tou_02_str_00003D5C[20] = "stg3_npc_02_01_02\0\0";
__declspec(section ".rodata") const char tou_02_str_00003D70[20] = "stg3_npc_02_01_03\0\0";
__declspec(section ".rodata") const char str_00003D84[20] = "stg3_npc_02_01_04\0\0";
__declspec(section ".rodata") const char tou_02_str_00003D98[20] = "stg3_npc_02_01_05\0\0";
__declspec(section ".rodata") const char tou_02_str_00003DAC[20] = "stg3_npc_02_01_06\0\0";
__declspec(section ".rodata") const char tou_02_str_00003DC0[20] = "stg3_npc_02_01_07\0\0";
__declspec(section ".rodata") const char tou_02_str_00003DD4[20] = "stg3_npc_02_02_01\0\0";
__declspec(section ".rodata") const char tou_02_str_00003DE8[20] = "stg3_npc_02_02_02\0\0";
__declspec(section ".rodata") const char tou_02_str_00003DFC[20] = "stg3_npc_02_02_03\0\0";
__declspec(section ".rodata") const char tou_02_str_00003E10[20] = "stg3_npc_02_02_04\0\0";
__declspec(section ".rodata") const char str_00003E24[20] = "stg3_npc_02_02_05\0\0";
__declspec(section ".rodata") const char tou_02_str_00003E38[20] = "stg3_npc_02_02_06\0\0";
__declspec(section ".rodata") const char tou_02_str_00003E4C[20] = "stg3_npc_02_02_07\0\0";
__declspec(section ".rodata") const char str_00003E60[16] = "stg3_npc_re_024";
__declspec(section ".rodata") const char tou_02_str_00003E70[20] = "stg3_npc_re_024_1\0\0";
__declspec(section ".rodata") const char tou_02_str_00003E84[16] = "stg3_npc_re_023";
__declspec(section ".rodata") const char tou_02_str_00003E94[20] = "stg3_npc_02_03_01\0\0";
__declspec(section ".rodata") const char tou_02_str_00003EA8[20] = "stg3_npc_02_03_02\0\0";
__declspec(section ".rodata") const char tou_02_str_00003EBC[20] = "stg3_npc_02_03_03\0\0";
__declspec(section ".rodata") const char tou_02_str_00003ED0[20] = "stg3_npc_02_03_04\0\0";
__declspec(section ".rodata") const char tou_02_str_00003EE4[20] = "stg3_npc_02_03_05\0\0";
__declspec(section ".rodata") const char tou_02_str_00003EF8[20] = "stg3_npc_02_03_06\0\0";
__declspec(section ".rodata") const char tou_02_str_00003F0C[20] = "stg3_npc_02_03_07\0\0";
__declspec(section ".rodata") const char tou_02_str_00003F20[16] = "stg3_npc_re_026";
__declspec(section ".rodata") const char tou_02_str_00003F30[20] = "stg3_npc_re_026_1\0\0";
__declspec(section ".rodata") const char tou_02_str_00003F44[16] = "stg3_npc_re_025";
__declspec(section ".rodata") const char str_00003F54[20] = "stg3_npc_02_04_01\0\0";
__declspec(section ".rodata") const char tou_02_str_00003F68[20] = "stg3_npc_02_04_02\0\0";
__declspec(section ".rodata") const char tou_02_str_00003F7C[20] = "stg3_npc_02_04_03\0\0";
__declspec(section ".rodata") const char tou_02_str_00003F90[20] = "stg3_npc_02_04_04\0\0";
__declspec(section ".rodata") const char tou_02_str_00003FA4[20] = "stg3_npc_02_04_05\0\0";
__declspec(section ".rodata") const char tou_02_str_00003FB8[20] = "stg3_npc_02_04_06\0\0";
__declspec(section ".rodata") const char tou_02_str_00003FCC[20] = "stg3_npc_02_04_07\0\0";
__declspec(section ".rodata") const char tou_02_str_00003FE0[16] = "stg3_npc_re_028";
__declspec(section ".rodata") const char tou_02_str_00003FF0[20] = "stg3_npc_re_028_1\0\0";
__declspec(section ".rodata") const char tou_02_str_00004004[16] = "stg3_npc_re_027";
__declspec(section ".rodata") const char tou_02_str_00004014[20] = "stg3_npc_02_05_01\0\0";
__declspec(section ".rodata") const char tou_02_str_00004028[20] = "stg3_npc_02_05_02\0\0";
__declspec(section ".rodata") const char tou_02_str_0000403C[20] = "stg3_npc_02_05_03\0\0";
__declspec(section ".rodata") const char tou_02_str_00004050[20] = "stg3_npc_02_05_04\0\0";
__declspec(section ".rodata") const char str_00004064[20] = "stg3_npc_02_05_05\0\0";
__declspec(section ".rodata") const char tou_02_str_00004078[20] = "stg3_npc_02_05_06\0\0";
__declspec(section ".rodata") const char tou_02_str_0000408C[20] = "stg3_npc_02_05_07\0\0";
__declspec(section ".rodata") const char tou_02_str_000040A0[16] = "stg3_npc_re_030";
__declspec(section ".rodata") const char tou_02_str_000040B0[20] = "stg3_npc_re_030_1\0\0";
__declspec(section ".rodata") const char tou_02_str_000040C4[16] = "stg3_npc_re_029";
__declspec(section ".rodata") const char str_000040D4[20] = "stg3_npc_02_06_01\0\0";
__declspec(section ".rodata") const char tou_02_str_000040E8[20] = "stg3_npc_02_06_02\0\0";
__declspec(section ".rodata") const char tou_02_str_000040FC[20] = "stg3_npc_02_06_03\0\0";
__declspec(section ".rodata") const char tou_02_str_00004110[24] = "stg3_npc_02_06_04_yos\0\0";
__declspec(section ".rodata") const char tou_02_str_00004128[20] = "stg3_npc_02_06_04\0\0";
__declspec(section ".rodata") const char tou_02_str_0000413C[24] = "stg3_npc_02_06_05_yos\0\0";
__declspec(section ".rodata") const char tou_02_str_00004154[20] = "stg3_npc_02_06_05\0\0";
__declspec(section ".rodata") const char tou_02_str_00004168[24] = "stg3_npc_02_06_06_yos\0\0";
__declspec(section ".rodata") const char tou_02_str_00004180[20] = "stg3_npc_02_06_06\0\0";
__declspec(section ".rodata") const char tou_02_str_00004194[24] = "stg3_npc_02_06_07_yos\0\0";
__declspec(section ".rodata") const char tou_02_str_000041AC[20] = "stg3_npc_02_06_07\0\0";
__declspec(section ".rodata") const char tou_02_str_000041C0[20] = "stg3_npc_re_032_yos";
__declspec(section ".rodata") const char tou_02_str_000041D4[16] = "stg3_npc_re_032";
__declspec(section ".rodata") const char tou_02_str_000041E4[24] = "stg3_npc_re_032_1_yos\0\0";
__declspec(section ".rodata") const char tou_02_str_000041FC[20] = "stg3_npc_re_032_1\0\0";
__declspec(section ".rodata") const char tou_02_str_00004210[20] = "stg3_npc_re_031_yos";
__declspec(section ".rodata") const char tou_02_str_00004224[16] = "stg3_npc_re_031";
__declspec(section ".rodata") const char tou_02_str_00004234[20] = "stg3_npc_02_07_01\0\0";
__declspec(section ".rodata") const char tou_02_str_00004248[20] = "stg3_npc_02_07_02\0\0";
__declspec(section ".rodata") const char tou_02_str_0000425C[20] = "stg3_npc_02_07_03\0\0";
__declspec(section ".rodata") const char tou_02_str_00004270[20] = "stg3_npc_02_07_04\0\0";
__declspec(section ".rodata") const char tou_02_str_00004284[20] = "stg3_npc_02_07_05\0\0";
__declspec(section ".rodata") const char tou_02_str_00004298[20] = "stg3_npc_02_07_06\0\0";
__declspec(section ".rodata") const char tou_02_str_000042AC[20] = "stg3_npc_02_07_07\0\0";
__declspec(section ".rodata") const char tou_02_str_000042C0[16] = "stg3_npc_re_034";
__declspec(section ".rodata") const char tou_02_str_000042D0[20] = "stg3_npc_re_034_1\0\0";
__declspec(section ".rodata") const char tou_02_str_000042E4[16] = "stg3_npc_re_033";
__declspec(section ".rodata") const char str_000042F4[12] = "\x83L\x83m\x83s\x83I\x8f\x97\0";
__declspec(section ".rodata") const char tou_02_str_00004300[20] = "stg3_npc_02_08_01\0\0";
__declspec(section ".rodata") const char tou_02_str_00004314[20] = "stg3_npc_02_08_02\0\0";
__declspec(section ".rodata") const char tou_02_str_00004328[20] = "stg3_npc_02_08_03\0\0";
__declspec(section ".rodata") const char tou_02_str_0000433C[20] = "stg3_npc_02_08_04\0\0";
__declspec(section ".rodata") const char tou_02_str_00004350[20] = "stg3_npc_02_08_05\0\0";
__declspec(section ".rodata") const char tou_02_str_00004364[20] = "stg3_npc_02_08_06\0\0";
__declspec(section ".rodata") const char tou_02_str_00004378[20] = "stg3_npc_02_08_07\0\0";
__declspec(section ".rodata") const char tou_02_str_0000438C[16] = "stg3_npc_re_036";
__declspec(section ".rodata") const char tou_02_str_0000439C[20] = "stg3_npc_re_036_1\0\0";
__declspec(section ".rodata") const char tou_02_str_000043B0[16] = "stg3_npc_re_035";
__declspec(section ".rodata") const char tou_02_str_000043C0[20] = "stg3_npc_02_10_01\0\0";
__declspec(section ".rodata") const char tou_02_str_000043D4[20] = "stg3_npc_02_10_02\0\0";
__declspec(section ".rodata") const char tou_02_str_000043E8[20] = "stg3_npc_02_10_03\0\0";
__declspec(section ".rodata") const char tou_02_str_000043FC[20] = "stg3_npc_02_10_04\0\0";
__declspec(section ".rodata") const char tou_02_str_00004410[20] = "stg3_npc_02_10_05\0\0";
__declspec(section ".rodata") const char tou_02_str_00004424[20] = "stg3_npc_02_10_06\0\0";
__declspec(section ".rodata") const char tou_02_str_00004438[20] = "stg3_npc_02_10_07\0\0";
__declspec(section ".rodata") const char tou_02_str_0000444C[16] = "stg3_tou_182\0\0\0";
__declspec(section ".rodata") const char tou_02_str_0000445C[16] = "stg3_tou_183\0\0\0";
__declspec(section ".rodata") const char tou_02_str_0000446C[16] = "stg3_tou_184\0\0\0";
__declspec(section ".rodata") const char tou_02_str_0000447C[16] = "stg3_tou_185\0\0\0";
__declspec(section ".rodata") const char tou_02_str_0000448C[16] = "stg3_tou_186\0\0\0";
__declspec(section ".rodata") const char tou_02_str_0000449C[16] = "stg3_tou_187\0\0\0";
__declspec(section ".rodata") const char tou_02_str_000044AC[16] = "stg3_tou_188\0\0\0";
__declspec(section ".rodata") const char tou_02_str_000044BC[16] = "stg3_tou_189\0\0\0";
__declspec(section ".rodata") const char tou_02_str_000044CC[16] = "stg3_tou_186_01";
__declspec(section ".rodata") const char tou_02_str_000044DC[16] = "stg3_tou_190_01";
__declspec(section ".rodata") const char tou_02_str_000044EC[16] = "stg3_tou_190\0\0\0";
__declspec(section ".rodata") const char tou_02_str_000044FC[16] = "stg3_tou_479_02";
__declspec(section ".rodata") const char tou_02_str_0000450C[16] = "stg3_tou_479_01";
__declspec(section ".rodata") const char tou_02_str_0000451C[16] = "stg3_tou_479_03";
__declspec(section ".rodata") const char tou_02_str_0000452C[16] = "stg3_tou_479_04";
__declspec(section ".rodata") const char tou_02_str_0000453C[16] = "stg3_tou_479_05";
__declspec(section ".rodata") const char tou_02_str_0000454C[16] = "stg3_tou_479_06";
__declspec(section ".rodata") const char tou_02_str_0000455C[8] = "\x83}\x83_\x83\x80\0";
__declspec(section ".rodata") const char tou_02_str_00004564[12] = "\x83\x8c\x83|\x81[\x83^\x81[\0";
__declspec(section ".rodata") const char tou_02_str_00004570[16] = "\x83J\x83\x81\x83\x89\x83}\x83\x93\x82P\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00004580[16] = "\x83J\x83\x81\x83\x89\x83}\x83\x93\x82Q\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00004590[12] = "\x83L\x83m\x83s\x83I\x82S\0";
__declspec(section ".rodata") const char tou_02_str_0000459C[12] = "\x83L\x83m\x83s\x83I\x82T\0";
__declspec(section ".rodata") const char tou_02_str_000045A8[12] = "\x83L\x83m\x83s\x83R\0\0\0";
__declspec(section ".rodata") const char tou_02_str_000045B4[12] = "\x83o\x83" "b\x83W\x89\xae\0\0\0";
__declspec(section ".rodata") const char tou_02_str_000045C0[16] = "\x83`\x83\x83\x83\x93\x83s\x83\x87\x83\x93\0\0\0";
__declspec(section ".rodata") const char tou_02_str_000045D0[12] = "\x83L\x83m\x83V\x83R\x83\x8f\0";
__declspec(section ".rodata") const char tou_02_str_000045DC[12] = "\x83" "E\x83\x89\x83m\x83R\0\0\0";
__declspec(section ".rodata") const char tou_02_str_000045E8[12] = "\x83" "A\x83" "C\x83" "A\x83\x93\x82`\0";
__declspec(section ".rodata") const char tou_02_str_000045F4[12] = "\x83" "A\x83" "C\x83" "A\x83\x93\x82" "a\0";
__declspec(section ".rodata") const char str_00004600[12] = "\x83{\x83\x8d\x83h\x81[\0\0\0";
__declspec(section ".rodata") const char tou_02_str_0000460C[12] = "stg3_tou_33";
__declspec(section ".rodata") const char tou_02_str_00004618[16] = "stg3_tou_33_yn\0";
__declspec(section ".rodata") const char tou_02_str_00004628[16] = "stg3_tou_34_kur";
__declspec(section ".rodata") const char tou_02_str_00004638[16] = "stg3_tou_34_nok";
__declspec(section ".rodata") const char tou_02_str_00004648[16] = "stg3_tou_34_win";
__declspec(section ".rodata") const char tou_02_str_00004658[16] = "stg3_tou_35_kur";
__declspec(section ".rodata") const char tou_02_str_00004668[16] = "stg3_tou_35_nok";
__declspec(section ".rodata") const char tou_02_str_00004678[16] = "stg3_tou_35_win";
__declspec(section ".rodata") const char tou_02_str_00004688[24] = "SFX_VOICE_MARIO_NOD1_4\0";
__declspec(section ".rodata") const char tou_02_str_000046A0[8] = "M_N_2\0\0";
__declspec(section ".rodata") const char tou_02_str_000046A8[8] = "M_S_1\0\0";
__declspec(section ".rodata") const char tou_02_str_000046B0[12] = "stg3_tou_36";
__declspec(section ".rodata") const char tou_02_str_000046BC[12] = "c_kinopio\0\0";
__declspec(section ".rodata") const char tou_02_str_000046C8[8] = "KNP_W_1";
__declspec(section ".rodata") const char tou_02_str_000046D0[12] = "c_kinopiko\0";
__declspec(section ".rodata") const char tou_02_str_000046DC[8] = "KNF_W_1";
__declspec(section ".rodata") const char tou_02_str_000046E4[12] = "c_jugemu\0\0\0";
__declspec(section ".rodata") const char tou_02_str_000046F0[8] = "JGM_W_1";
__declspec(section ".rodata") const f32 vec3_tou_0000d028[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_tou_0000d034[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_tou_0000d040[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_tou_0000d04c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_tou_0000d058[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_tou_0000d064[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const char tou_02_str_00004740[16] = "stg3_tou_236\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00004750[16] = "stg3_tou_237\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00004760[16] = "stg3_tou_238\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00004770[16] = "stg3_tou_239\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00004780[16] = "stg3_tou_240\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00004790[16] = "stg3_tou_240_01";
__declspec(section ".rodata") const char tou_02_str_000047A0[4] = "fan";
__declspec(section ".rodata") const char tou_02_str_000047A4[8] = "fan2\0\0\0";
__declspec(section ".rodata") const char tou_02_str_000047AC[8] = "fan3\0\0\0";
__declspec(section ".rodata") const char tou_02_str_000047B4[4] = "key";
__declspec(section ".rodata") const char tou_02_str_000047B8[16] = "stg3_tou_307_08";
__declspec(section ".rodata") const char tou_02_str_000047C8[24] = "SFX_VOICE_MARIO_FIND1_3";
__declspec(section ".rodata") const char str_000047E0[24] = "BGM_FF_MAIL_RECEPTION2\0";
__declspec(section ".rodata") const char tou_02_str_000047F8[20] = "SFX_MAIL_RECEPTION1";
__declspec(section ".rodata") const char tou_02_str_0000480C[8] = "M_N_9\0\0";
__declspec(section ".rodata") const char tou_02_str_00004814[20] = "SFX_MAIL_RECEPTION2";
__declspec(section ".rodata") const char tou_02_str_00004828[8] = "M_N_10\0";
__declspec(section ".rodata") const char tou_02_str_00004830[16] = "stg3_tou_307_09";
__declspec(section ".rodata") const char tou_02_str_00004840[8] = "p_m_8\0\0";
__declspec(section ".rodata") const char tou_02_str_00004848[20] = "stg3_tou_479_00_01\0";
__declspec(section ".rodata") const char tou_02_str_0000485C[20] = "stg3_tou_479_00_02\0";
__declspec(section ".rodata") const char tou_02_str_00004870[20] = "stg3_tou_479_00_03\0";
__declspec(section ".rodata") const char tou_02_str_00004884[20] = "stg3_tou_479_00_04\0";
__declspec(section ".rodata") const char str_00004898[20] = "stg3_tou_479_00_05\0";
__declspec(section ".rodata") const char tou_02_str_000048AC[8] = "M_I_2\0\0";
__declspec(section ".rodata") const char tou_02_str_000048B4[16] = "BGM_STG3_TOU2\0\0";
__declspec(section ".rodata") const char tou_02_str_000048C4[16] = "ENV_STG3_TOU2\0\0";
__declspec(section ".rodata") const char tou_02_str_000048D4[16] = "BGM_STG3_TOU1\0\0";
__declspec(section ".rodata") const char tou_02_str_000048E4[12] = "kururin1\0\0\0";
__declspec(section ".rodata") const char tou_02_str_000048F0[8] = "sita\0\0\0";
__declspec(section ".rodata") const char tou_02_str_000048F8[12] = "anm_paneru\0";
__declspec(section ".rodata") const char tou_02_str_00004904[28] = "SFX_STG3_AMB_OBJ_SCREEN2\0\0\0";
__declspec(section ".rodata") const char tou_02_str_00004920[28] = "SFX_STG3_AMB_OBJ_SCREEN1\0\0\0";
__declspec(section ".rodata") const char tou_02_str_0000493C[8] = "p_p_1\0\0";
__declspec(section ".rodata") const char tou_02_str_00004944[8] = "p_p_2\0\0";
__declspec(section ".rodata") const char tou_02_str_0000494C[8] = "p_p_3\0\0";
__declspec(section ".rodata") const char tou_02_str_00004954[8] = "a_p_p_2";
__declspec(section ".rodata") const char tou_02_str_0000495C[8] = "a_p_p_3";
__declspec(section ".rodata") const char tou_02_str_00004964[8] = "p_m_2\0\0";
__declspec(section ".rodata") const char tou_02_str_0000496C[8] = "a_p_m_2";
__declspec(section ".rodata") const char tou_02_str_00004974[8] = "p_m_3\0\0";
__declspec(section ".rodata") const char tou_02_str_0000497C[8] = "a_p_m_3";
__declspec(section ".rodata") const char tou_02_str_00004984[8] = "p_m_4\0\0";
__declspec(section ".rodata") const char tou_02_str_0000498C[8] = "a_p_m_4";
__declspec(section ".rodata") const char tou_02_str_00004994[8] = "p_m_5\0\0";
__declspec(section ".rodata") const char tou_02_str_0000499C[8] = "a_p_m_5";
__declspec(section ".rodata") const char tou_02_str_000049A4[8] = "p_m_6\0\0";
__declspec(section ".rodata") const char tou_02_str_000049AC[8] = "a_p_m_6";
__declspec(section ".rodata") const char tou_02_str_000049B4[8] = "p_m_7\0\0";
__declspec(section ".rodata") const char tou_02_str_000049BC[8] = "a_p_m_7";
__declspec(section ".rodata") const char tou_02_str_000049C4[8] = "a_p_m_8";
__declspec(section ".rodata") const char tou_02_str_000049CC[8] = "p_m_9\0\0";
__declspec(section ".rodata") const char tou_02_str_000049D4[8] = "a_p_m_9";
__declspec(section ".rodata") const char tou_02_str_000049DC[8] = "p_m_1\0\0";
__declspec(section ".rodata") const char tou_02_str_000049E4[8] = "a_p_m_1";
__declspec(section ".rodata") const char tou_02_str_000049EC[12] = "s_kaidan_7\0";
__declspec(section ".rodata") const f32 zero_tou_0000d328 = 0.0f;
__declspec(section ".rodata") const f32 float_6p2832_tou_0000d32c = 6.2831855f;
__declspec(section ".rodata") const f32 float_90_tou_0000d330 = 90.0f;
__declspec(section ".rodata") const f32 float_360_tou_0000d334 = 360.0f;
__declspec(section ".rodata") const f32 float_0p00761_tou_0000d338 = 0.00761f;
__declspec(section ".rodata") const f32 float_0p16605_tou_0000d33c = 0.16605f;
__declspec(section ".rodata") const f32 float_1_tou_0000d340 = 1.0f;
__declspec(section ".rodata") const f32 float_3p1416_tou_0000d344 = 3.1415927f;
__declspec(section ".rodata") const f32 float_1p5708_tou_0000d348 = 1.5707964f;
__declspec(section ".rodata") const f32 float_4p7124_tou_0000d34c = 4.712389f;
__declspec(section ".rodata") const f32 float_35_tou_0000d350 = 35.0f;
__declspec(section ".rodata") const f32 float_0p03705_tou_0000d354 = 0.03705f;
__declspec(section ".rodata") const f32 float_0p4967_tou_0000d358 = 0.4967f;
__declspec(section ".rodata") const f32 float_65_tou_0000d35c = 65.0f;
__declspec(section ".rodata") const f32 float_30_tou_0000d360 = 30.0f;
__declspec(section ".rodata") const f32 float_60_tou_0000d364 = 60.0f;
__declspec(section ".rodata") const f32 float_1000_tou_0000d368 = 1000.0f;
__declspec(section ".rodata") const f64 double_to_int_tou_0000d370 = 4503601774854144.0;
__declspec(section ".rodata") const f32 float_0p1_tou_0000d378 = 0.1f;
__declspec(section ".rodata") const f32 float_900_tou_0000d37c = 900.0f;
__declspec(section ".rodata") const f32 float_5_tou_0000d380 = 5.0f;
__declspec(section ".rodata") const char tou_02_str_00004A54[28] = "SFX_STG3_AUDIENCE_FAN_FLY1\0";
__declspec(section ".rodata") const f32 float_32767_tou_0000d3a0 = 32767.0f;
__declspec(section ".rodata") const f32 float_135_tou_0000d3a4 = 135.0f;
__declspec(section ".rodata") const f32 float_400_tou_0000d3a8 = 400.0f;
__declspec(section ".rodata") const f32 float_100_tou_0000d3ac = 100.0f;
__declspec(section ".rodata") const f32 float_neg100_tou_0000d3b0 = -100.0f;
__declspec(section ".rodata") const f32 float_4_tou_0000d3b4 = 4.0f;
__declspec(section ".rodata") const f32 float_2_tou_0000d3b8 = 2.0f;
__declspec(section ".rodata") const f32 float_0p5_tou_0000d3bc = 0.5f;
__declspec(section ".rodata") const f32 float_0p03_tou_0000d3c0 = 0.03f;
__declspec(section ".rodata") const f32 float_25_tou_0000d3c4 = 25.0f;
__declspec(section ".rodata") const f32 float_0p6_tou_0000d3c8 = 0.6f;
__declspec(section ".rodata") const f32 float_neg350_tou_0000d3cc = -350.0f;
__declspec(section ".rodata") const f32 float_350_tou_0000d3d0 = 350.0f;
__declspec(section ".rodata") const f32 float_195_tou_0000d3d4 = 195.0f;
__declspec(section ".rodata") const u32 zero_tou_0000d3d8 = 0x00000000;
__declspec(section ".rodata") const f32 float_200_tou_0000d3dc = 200.0f;
__declspec(section ".rodata") const char tou_02_str_00004AB0[24] = "SFX_STG3_AUDIENCE_FAN1\0";
#endif

#ifdef NONMATCHING // all-C link: pool objects the C names, defined on the asm side only
__declspec(section ".data") const char str_00003BEC[12] = "door_2_b\0\0\0";
__declspec(section ".data") const char str_00003C34[8] = "tou_01\0";
__declspec(section ".data") const char str_00003C5C[12] = "s_bero_1\0\0\0";
__declspec(section ".data") const char str_00003D84[20] = "stg3_npc_02_01_04\0\0";
__declspec(section ".data") const char str_00003E24[20] = "stg3_npc_02_02_05\0\0";
__declspec(section ".data") const char str_00003E60[16] = "stg3_npc_re_024";
__declspec(section ".data") const char str_00003F54[20] = "stg3_npc_02_04_01\0\0";
__declspec(section ".data") const char str_00004064[20] = "stg3_npc_02_05_05\0\0";
__declspec(section ".data") const char str_000040D4[20] = "stg3_npc_02_06_01\0\0";
__declspec(section ".data") const char str_000042F4[12] = "\x83L\x83m\x83s\x83I\x8f\x97\0";
__declspec(section ".data") const char str_00004600[12] = "\x83{\x83\x8d\x83h\x81[\0\0\0";
__declspec(section ".data") const char str_000047E0[24] = "BGM_FF_MAIL_RECEPTION2\0";
__declspec(section ".data") const char str_00004898[20] = "stg3_tou_479_00_05\0";
__declspec(section ".data") const char tou_02_str_00003BC0[20] = "SFX_STG3_AUTO_DOOR1";
__declspec(section ".data") const char tou_02_str_00003BD4[12] = "door_1_b\0\0\0";
__declspec(section ".data") const char tou_02_str_00003BE0[12] = "door_1_a\0\0\0";
__declspec(section ".data") const char tou_02_str_00003BF8[12] = "door_2_a\0\0\0";
__declspec(section ".data") const char tou_02_str_00003C04[12] = "door_3_b\0\0\0";
__declspec(section ".data") const char tou_02_str_00003C10[12] = "door_3_a\0\0\0";
__declspec(section ".data") const char tou_02_str_00003C1C[8] = "door_4\0";
__declspec(section ".data") const char tou_02_str_00003C24[8] = "door_5\0";
__declspec(section ".data") const char tou_02_str_00003C2C[8] = "s_bero\0";
__declspec(section ".data") const char tou_02_str_00003C3C[12] = "a_door_mon\0";
__declspec(section ".data") const char tou_02_str_00003C48[12] = "n_bero_1\0\0\0";
__declspec(section ".data") const char tou_02_str_00003C54[8] = "tou_03\0";
__declspec(section ".data") const char tou_02_str_00003C68[12] = "n_bero_2\0\0\0";
__declspec(section ".data") const char tou_02_str_00003C74[12] = "s_bero_2\0\0\0";
__declspec(section ".data") const char tou_02_str_00003C80[12] = "n_bero_3\0\0\0";
__declspec(section ".data") const char tou_02_str_00003C8C[8] = "tou_04\0";
__declspec(section ".data") const char tou_02_str_00003C94[8] = "e_bero\0";
__declspec(section ".data") const char tou_02_str_00003C9C[12] = "n_bero_4\0\0\0";
__declspec(section ".data") const char tou_02_str_00003CA8[8] = "w_bero\0";
__declspec(section ".data") const char tou_02_str_00003CB0[4] = "me\0";
__declspec(section ".data") const char tou_02_str_00003CB4[16] = "\x83K\x81[\x83h\x83}\x83\x93\x82P\0\0\0";
__declspec(section ".data") const char tou_02_str_00003CC4[8] = "mario\0\0";
__declspec(section ".data") const char tou_02_str_00003CCC[16] = "\x83K\x81[\x83h\x83}\x83\x93\x82Q\0\0\0";
__declspec(section ".data") const char tou_02_str_00003CDC[12] = "stg3_tou_24";
__declspec(section ".data") const char tou_02_str_00003CE8[12] = "stg3_tou_37";
__declspec(section ".data") const char tou_02_str_00003CF4[16] = "stg3_tou_37_01\0";
__declspec(section ".data") const char tou_02_str_00003D04[16] = "stg3_tou_37_02\0";
__declspec(section ".data") const char tou_02_str_00003D14[20] = "stg3_tou_re_002_1\0\0";
__declspec(section ".data") const char tou_02_str_00003D28[16] = "stg3_tou_re_001";
__declspec(section ".data") const char tou_02_str_00003D38[16] = "stg3_tou_re_002";
__declspec(section ".data") const char tou_02_str_00003D48[20] = "stg3_npc_02_01_01\0\0";
__declspec(section ".data") const char tou_02_str_00003D5C[20] = "stg3_npc_02_01_02\0\0";
__declspec(section ".data") const char tou_02_str_00003D70[20] = "stg3_npc_02_01_03\0\0";
__declspec(section ".data") const char tou_02_str_00003D98[20] = "stg3_npc_02_01_05\0\0";
__declspec(section ".data") const char tou_02_str_00003DAC[20] = "stg3_npc_02_01_06\0\0";
__declspec(section ".data") const char tou_02_str_00003DC0[20] = "stg3_npc_02_01_07\0\0";
__declspec(section ".data") const char tou_02_str_00003DD4[20] = "stg3_npc_02_02_01\0\0";
__declspec(section ".data") const char tou_02_str_00003DE8[20] = "stg3_npc_02_02_02\0\0";
__declspec(section ".data") const char tou_02_str_00003DFC[20] = "stg3_npc_02_02_03\0\0";
__declspec(section ".data") const char tou_02_str_00003E10[20] = "stg3_npc_02_02_04\0\0";
__declspec(section ".data") const char tou_02_str_00003E38[20] = "stg3_npc_02_02_06\0\0";
__declspec(section ".data") const char tou_02_str_00003E4C[20] = "stg3_npc_02_02_07\0\0";
__declspec(section ".data") const char tou_02_str_00003E70[20] = "stg3_npc_re_024_1\0\0";
__declspec(section ".data") const char tou_02_str_00003E84[16] = "stg3_npc_re_023";
__declspec(section ".data") const char tou_02_str_00003E94[20] = "stg3_npc_02_03_01\0\0";
__declspec(section ".data") const char tou_02_str_00003EA8[20] = "stg3_npc_02_03_02\0\0";
__declspec(section ".data") const char tou_02_str_00003EBC[20] = "stg3_npc_02_03_03\0\0";
__declspec(section ".data") const char tou_02_str_00003ED0[20] = "stg3_npc_02_03_04\0\0";
__declspec(section ".data") const char tou_02_str_00003EE4[20] = "stg3_npc_02_03_05\0\0";
__declspec(section ".data") const char tou_02_str_00003EF8[20] = "stg3_npc_02_03_06\0\0";
__declspec(section ".data") const char tou_02_str_00003F0C[20] = "stg3_npc_02_03_07\0\0";
__declspec(section ".data") const char tou_02_str_00003F20[16] = "stg3_npc_re_026";
__declspec(section ".data") const char tou_02_str_00003F30[20] = "stg3_npc_re_026_1\0\0";
__declspec(section ".data") const char tou_02_str_00003F44[16] = "stg3_npc_re_025";
__declspec(section ".data") const char tou_02_str_00003F68[20] = "stg3_npc_02_04_02\0\0";
__declspec(section ".data") const char tou_02_str_00003F7C[20] = "stg3_npc_02_04_03\0\0";
__declspec(section ".data") const char tou_02_str_00003F90[20] = "stg3_npc_02_04_04\0\0";
__declspec(section ".data") const char tou_02_str_00003FA4[20] = "stg3_npc_02_04_05\0\0";
__declspec(section ".data") const char tou_02_str_00003FB8[20] = "stg3_npc_02_04_06\0\0";
__declspec(section ".data") const char tou_02_str_00003FCC[20] = "stg3_npc_02_04_07\0\0";
__declspec(section ".data") const char tou_02_str_00003FE0[16] = "stg3_npc_re_028";
__declspec(section ".data") const char tou_02_str_00003FF0[20] = "stg3_npc_re_028_1\0\0";
__declspec(section ".data") const char tou_02_str_00004004[16] = "stg3_npc_re_027";
__declspec(section ".data") const char tou_02_str_00004014[20] = "stg3_npc_02_05_01\0\0";
__declspec(section ".data") const char tou_02_str_00004028[20] = "stg3_npc_02_05_02\0\0";
__declspec(section ".data") const char tou_02_str_0000403C[20] = "stg3_npc_02_05_03\0\0";
__declspec(section ".data") const char tou_02_str_00004050[20] = "stg3_npc_02_05_04\0\0";
__declspec(section ".data") const char tou_02_str_00004078[20] = "stg3_npc_02_05_06\0\0";
__declspec(section ".data") const char tou_02_str_0000408C[20] = "stg3_npc_02_05_07\0\0";
__declspec(section ".data") const char tou_02_str_000040A0[16] = "stg3_npc_re_030";
__declspec(section ".data") const char tou_02_str_000040B0[20] = "stg3_npc_re_030_1\0\0";
__declspec(section ".data") const char tou_02_str_000040C4[16] = "stg3_npc_re_029";
__declspec(section ".data") const char tou_02_str_000040E8[20] = "stg3_npc_02_06_02\0\0";
__declspec(section ".data") const char tou_02_str_000040FC[20] = "stg3_npc_02_06_03\0\0";
__declspec(section ".data") const char tou_02_str_00004110[24] = "stg3_npc_02_06_04_yos\0\0";
__declspec(section ".data") const char tou_02_str_00004128[20] = "stg3_npc_02_06_04\0\0";
__declspec(section ".data") const char tou_02_str_0000413C[24] = "stg3_npc_02_06_05_yos\0\0";
__declspec(section ".data") const char tou_02_str_00004154[20] = "stg3_npc_02_06_05\0\0";
__declspec(section ".data") const char tou_02_str_00004168[24] = "stg3_npc_02_06_06_yos\0\0";
__declspec(section ".data") const char tou_02_str_00004180[20] = "stg3_npc_02_06_06\0\0";
__declspec(section ".data") const char tou_02_str_00004194[24] = "stg3_npc_02_06_07_yos\0\0";
__declspec(section ".data") const char tou_02_str_000041AC[20] = "stg3_npc_02_06_07\0\0";
__declspec(section ".data") const char tou_02_str_000041C0[20] = "stg3_npc_re_032_yos";
__declspec(section ".data") const char tou_02_str_000041D4[16] = "stg3_npc_re_032";
__declspec(section ".data") const char tou_02_str_000041E4[24] = "stg3_npc_re_032_1_yos\0\0";
__declspec(section ".data") const char tou_02_str_000041FC[20] = "stg3_npc_re_032_1\0\0";
__declspec(section ".data") const char tou_02_str_00004210[20] = "stg3_npc_re_031_yos";
__declspec(section ".data") const char tou_02_str_00004224[16] = "stg3_npc_re_031";
__declspec(section ".data") const char tou_02_str_00004234[20] = "stg3_npc_02_07_01\0\0";
__declspec(section ".data") const char tou_02_str_00004248[20] = "stg3_npc_02_07_02\0\0";
__declspec(section ".data") const char tou_02_str_0000425C[20] = "stg3_npc_02_07_03\0\0";
__declspec(section ".data") const char tou_02_str_00004270[20] = "stg3_npc_02_07_04\0\0";
__declspec(section ".data") const char tou_02_str_00004284[20] = "stg3_npc_02_07_05\0\0";
__declspec(section ".data") const char tou_02_str_00004298[20] = "stg3_npc_02_07_06\0\0";
__declspec(section ".data") const char tou_02_str_000042AC[20] = "stg3_npc_02_07_07\0\0";
__declspec(section ".data") const char tou_02_str_000042C0[16] = "stg3_npc_re_034";
__declspec(section ".data") const char tou_02_str_000042D0[20] = "stg3_npc_re_034_1\0\0";
__declspec(section ".data") const char tou_02_str_000042E4[16] = "stg3_npc_re_033";
__declspec(section ".data") const char tou_02_str_00004300[20] = "stg3_npc_02_08_01\0\0";
__declspec(section ".data") const char tou_02_str_00004314[20] = "stg3_npc_02_08_02\0\0";
__declspec(section ".data") const char tou_02_str_00004328[20] = "stg3_npc_02_08_03\0\0";
__declspec(section ".data") const char tou_02_str_0000433C[20] = "stg3_npc_02_08_04\0\0";
__declspec(section ".data") const char tou_02_str_00004350[20] = "stg3_npc_02_08_05\0\0";
__declspec(section ".data") const char tou_02_str_00004364[20] = "stg3_npc_02_08_06\0\0";
__declspec(section ".data") const char tou_02_str_00004378[20] = "stg3_npc_02_08_07\0\0";
__declspec(section ".data") const char tou_02_str_0000438C[16] = "stg3_npc_re_036";
__declspec(section ".data") const char tou_02_str_0000439C[20] = "stg3_npc_re_036_1\0\0";
__declspec(section ".data") const char tou_02_str_000043B0[16] = "stg3_npc_re_035";
__declspec(section ".data") const char tou_02_str_000043C0[20] = "stg3_npc_02_10_01\0\0";
__declspec(section ".data") const char tou_02_str_000043D4[20] = "stg3_npc_02_10_02\0\0";
__declspec(section ".data") const char tou_02_str_000043E8[20] = "stg3_npc_02_10_03\0\0";
__declspec(section ".data") const char tou_02_str_000043FC[20] = "stg3_npc_02_10_04\0\0";
__declspec(section ".data") const char tou_02_str_00004410[20] = "stg3_npc_02_10_05\0\0";
__declspec(section ".data") const char tou_02_str_00004424[20] = "stg3_npc_02_10_06\0\0";
__declspec(section ".data") const char tou_02_str_00004438[20] = "stg3_npc_02_10_07\0\0";
__declspec(section ".data") const char tou_02_str_0000444C[16] = "stg3_tou_182\0\0\0";
__declspec(section ".data") const char tou_02_str_0000445C[16] = "stg3_tou_183\0\0\0";
__declspec(section ".data") const char tou_02_str_0000446C[16] = "stg3_tou_184\0\0\0";
__declspec(section ".data") const char tou_02_str_0000447C[16] = "stg3_tou_185\0\0\0";
__declspec(section ".data") const char tou_02_str_0000448C[16] = "stg3_tou_186\0\0\0";
__declspec(section ".data") const char tou_02_str_0000449C[16] = "stg3_tou_187\0\0\0";
__declspec(section ".data") const char tou_02_str_000044AC[16] = "stg3_tou_188\0\0\0";
__declspec(section ".data") const char tou_02_str_000044BC[16] = "stg3_tou_189\0\0\0";
__declspec(section ".data") const char tou_02_str_000044CC[16] = "stg3_tou_186_01";
__declspec(section ".data") const char tou_02_str_000044DC[16] = "stg3_tou_190_01";
__declspec(section ".data") const char tou_02_str_000044EC[16] = "stg3_tou_190\0\0\0";
__declspec(section ".data") const char tou_02_str_000044FC[16] = "stg3_tou_479_02";
__declspec(section ".data") const char tou_02_str_0000450C[16] = "stg3_tou_479_01";
__declspec(section ".data") const char tou_02_str_0000451C[16] = "stg3_tou_479_03";
__declspec(section ".data") const char tou_02_str_0000452C[16] = "stg3_tou_479_04";
__declspec(section ".data") const char tou_02_str_0000453C[16] = "stg3_tou_479_05";
__declspec(section ".data") const char tou_02_str_0000454C[16] = "stg3_tou_479_06";
__declspec(section ".data") const char tou_02_str_0000455C[8] = "\x83}\x83_\x83\x80\0";
__declspec(section ".data") const char tou_02_str_00004564[12] = "\x83\x8c\x83|\x81[\x83^\x81[\0";
__declspec(section ".data") const char tou_02_str_00004570[16] = "\x83J\x83\x81\x83\x89\x83}\x83\x93\x82P\0\0\0";
__declspec(section ".data") const char tou_02_str_00004580[16] = "\x83J\x83\x81\x83\x89\x83}\x83\x93\x82Q\0\0\0";
__declspec(section ".data") const char tou_02_str_00004590[12] = "\x83L\x83m\x83s\x83I\x82S\0";
__declspec(section ".data") const char tou_02_str_0000459C[12] = "\x83L\x83m\x83s\x83I\x82T\0";
__declspec(section ".data") const char tou_02_str_000045A8[12] = "\x83L\x83m\x83s\x83R\0\0\0";
__declspec(section ".data") const char tou_02_str_000045B4[12] = "\x83o\x83" "b\x83W\x89\xae\0\0\0";
__declspec(section ".data") const char tou_02_str_000045C0[16] = "\x83`\x83\x83\x83\x93\x83s\x83\x87\x83\x93\0\0\0";
__declspec(section ".data") const char tou_02_str_000045D0[12] = "\x83L\x83m\x83V\x83R\x83\x8f\0";
__declspec(section ".data") const char tou_02_str_000045DC[12] = "\x83" "E\x83\x89\x83m\x83R\0\0\0";
__declspec(section ".data") const char tou_02_str_000045E8[12] = "\x83" "A\x83" "C\x83" "A\x83\x93\x82`\0";
__declspec(section ".data") const char tou_02_str_000045F4[12] = "\x83" "A\x83" "C\x83" "A\x83\x93\x82" "a\0";
__declspec(section ".data") const char tou_02_str_0000460C[12] = "stg3_tou_33";
__declspec(section ".data") const char tou_02_str_00004618[16] = "stg3_tou_33_yn\0";
__declspec(section ".data") const char tou_02_str_00004628[16] = "stg3_tou_34_kur";
__declspec(section ".data") const char tou_02_str_00004638[16] = "stg3_tou_34_nok";
__declspec(section ".data") const char tou_02_str_00004648[16] = "stg3_tou_34_win";
__declspec(section ".data") const char tou_02_str_00004658[16] = "stg3_tou_35_kur";
__declspec(section ".data") const char tou_02_str_00004668[16] = "stg3_tou_35_nok";
__declspec(section ".data") const char tou_02_str_00004678[16] = "stg3_tou_35_win";
__declspec(section ".data") const char tou_02_str_00004688[24] = "SFX_VOICE_MARIO_NOD1_4\0";
__declspec(section ".data") const char tou_02_str_000046A0[8] = "M_N_2\0\0";
__declspec(section ".data") const char tou_02_str_000046A8[8] = "M_S_1\0\0";
__declspec(section ".data") const char tou_02_str_000046B0[12] = "stg3_tou_36";
__declspec(section ".data") const char tou_02_str_000046BC[12] = "c_kinopio\0\0";
__declspec(section ".data") const char tou_02_str_000046C8[8] = "KNP_W_1";
__declspec(section ".data") const char tou_02_str_000046D0[12] = "c_kinopiko\0";
__declspec(section ".data") const char tou_02_str_000046DC[8] = "KNF_W_1";
__declspec(section ".data") const char tou_02_str_000046E4[12] = "c_jugemu\0\0\0";
__declspec(section ".data") const char tou_02_str_000046F0[8] = "JGM_W_1";
__declspec(section ".data") const char tou_02_str_00004740[16] = "stg3_tou_236\0\0\0";
__declspec(section ".data") const char tou_02_str_00004750[16] = "stg3_tou_237\0\0\0";
__declspec(section ".data") const char tou_02_str_00004760[16] = "stg3_tou_238\0\0\0";
__declspec(section ".data") const char tou_02_str_00004770[16] = "stg3_tou_239\0\0\0";
__declspec(section ".data") const char tou_02_str_00004780[16] = "stg3_tou_240\0\0\0";
__declspec(section ".data") const char tou_02_str_00004790[16] = "stg3_tou_240_01";
__declspec(section ".data") const char tou_02_str_000047A0[4] = "fan";
__declspec(section ".data") const char tou_02_str_000047A4[8] = "fan2\0\0\0";
__declspec(section ".data") const char tou_02_str_000047AC[8] = "fan3\0\0\0";
__declspec(section ".data") const char tou_02_str_000047B4[4] = "key";
__declspec(section ".data") const char tou_02_str_000047B8[16] = "stg3_tou_307_08";
__declspec(section ".data") const char tou_02_str_000047C8[24] = "SFX_VOICE_MARIO_FIND1_3";
__declspec(section ".data") const char tou_02_str_000047F8[20] = "SFX_MAIL_RECEPTION1";
__declspec(section ".data") const char tou_02_str_0000480C[8] = "M_N_9\0\0";
__declspec(section ".data") const char tou_02_str_00004814[20] = "SFX_MAIL_RECEPTION2";
__declspec(section ".data") const char tou_02_str_00004828[8] = "M_N_10\0";
__declspec(section ".data") const char tou_02_str_00004830[16] = "stg3_tou_307_09";
__declspec(section ".data") const char tou_02_str_00004840[8] = "p_m_8\0\0";
__declspec(section ".data") const char tou_02_str_00004848[20] = "stg3_tou_479_00_01\0";
__declspec(section ".data") const char tou_02_str_0000485C[20] = "stg3_tou_479_00_02\0";
__declspec(section ".data") const char tou_02_str_00004870[20] = "stg3_tou_479_00_03\0";
__declspec(section ".data") const char tou_02_str_00004884[20] = "stg3_tou_479_00_04\0";
__declspec(section ".data") const char tou_02_str_000048AC[8] = "M_I_2\0\0";
__declspec(section ".data") const char tou_02_str_000048B4[16] = "BGM_STG3_TOU2\0\0";
__declspec(section ".data") const char tou_02_str_000048C4[16] = "ENV_STG3_TOU2\0\0";
__declspec(section ".data") const char tou_02_str_000048D4[16] = "BGM_STG3_TOU1\0\0";
__declspec(section ".data") const char tou_02_str_000048E4[12] = "kururin1\0\0\0";
__declspec(section ".data") const char tou_02_str_000048F0[8] = "sita\0\0\0";
__declspec(section ".data") const char tou_02_str_000048F8[12] = "anm_paneru\0";
__declspec(section ".data") const char tou_02_str_00004904[28] = "SFX_STG3_AMB_OBJ_SCREEN2\0\0\0";
__declspec(section ".data") const char tou_02_str_00004920[28] = "SFX_STG3_AMB_OBJ_SCREEN1\0\0\0";
__declspec(section ".data") const char tou_02_str_0000493C[8] = "p_p_1\0\0";
__declspec(section ".data") const char tou_02_str_00004944[8] = "p_p_2\0\0";
__declspec(section ".data") const char tou_02_str_0000494C[8] = "p_p_3\0\0";
__declspec(section ".data") const char tou_02_str_00004954[8] = "a_p_p_2";
__declspec(section ".data") const char tou_02_str_0000495C[8] = "a_p_p_3";
__declspec(section ".data") const char tou_02_str_00004964[8] = "p_m_2\0\0";
__declspec(section ".data") const char tou_02_str_0000496C[8] = "a_p_m_2";
__declspec(section ".data") const char tou_02_str_00004974[8] = "p_m_3\0\0";
__declspec(section ".data") const char tou_02_str_0000497C[8] = "a_p_m_3";
__declspec(section ".data") const char tou_02_str_00004984[8] = "p_m_4\0\0";
__declspec(section ".data") const char tou_02_str_0000498C[8] = "a_p_m_4";
__declspec(section ".data") const char tou_02_str_00004994[8] = "p_m_5\0\0";
__declspec(section ".data") const char tou_02_str_0000499C[8] = "a_p_m_5";
__declspec(section ".data") const char tou_02_str_000049A4[8] = "p_m_6\0\0";
__declspec(section ".data") const char tou_02_str_000049AC[8] = "a_p_m_6";
__declspec(section ".data") const char tou_02_str_000049B4[8] = "p_m_7\0\0";
__declspec(section ".data") const char tou_02_str_000049BC[8] = "a_p_m_7";
__declspec(section ".data") const char tou_02_str_000049C4[8] = "a_p_m_8";
__declspec(section ".data") const char tou_02_str_000049CC[8] = "p_m_9\0\0";
__declspec(section ".data") const char tou_02_str_000049D4[8] = "a_p_m_9";
__declspec(section ".data") const char tou_02_str_000049DC[8] = "p_m_1\0\0";
__declspec(section ".data") const char tou_02_str_000049E4[8] = "a_p_m_1";
__declspec(section ".data") const char tou_02_str_000049EC[12] = "s_kaidan_7\0";
#endif
