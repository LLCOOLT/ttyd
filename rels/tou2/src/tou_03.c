// FAKE: whole-unit asm (asmfake.py --whole, F2): every function is asm generated from the target, with its C kept under #ifdef NONMATCHING; .rodata/.data re-declared in target order, EVT string literals pointed at the named str_/zero_ objects. Best pure C: 29/30 (screen_tev 99.44).
#define GXSetTexCoordGen GXSetTexCoordGen_inline_hidden
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "driver/npcdrv.h"
#include "driver/mapdrv.h"
#include "driver/animdrv.h"
#include "dolphin/gx.h"
#include "driver/itemdrv.h"
#include "driver/effdrv.h"
#include "manager/evtmgr_cmd.h"
#include "system.h"
#include "pmario_sound.h"
#include "dolphin/mtx.h"
#include "stdio.h"
#include "string.h"
#include "driver/camdrv.h"
#include "dolphin/os.h"
#include "stdlib.h"
#include "driver/dispdrv.h"
#include "memory.h"
#include "mario/mariost.h"
#include "driver/hitdrv.h"
extern const char str_00000350[];
extern const char str_00000360[];
extern const char str_00000474[];
extern const char str_000004BC[];
extern const char str_00000518[];
extern const char str_00000540[];
extern const char str_00000698[];
extern const char str_00000000[];
extern const char str_0000000C[];
extern const char str_00000014[];
extern const char str_00000020[];
extern const char str_00000028[];
extern const char str_00000030[];
extern const char str_00000034[];
extern const char str_00000040[];
extern const char str_00000054[];
extern const char str_0000005C[];
extern const char str_00000064[];
extern const char str_0000006C[];
extern const char str_00000074[];
extern const char str_00000080[];
extern const char str_0000008C[];
extern const char str_00000094[];
extern const char str_000000A0[];
extern const char str_000000AC[];
extern const char str_000000B8[];
extern const char str_000000C8[];
extern const char str_000000D4[];
extern const char str_000000E0[];
extern const char str_000000EC[];
extern const char str_000000F8[];
extern const char str_00000104[];
extern const char str_00000110[];
extern const char str_0000011C[];
extern const char str_00000128[];
extern const char str_00000130[];
extern const char str_00000138[];
extern const char str_00000144[];
extern const char str_0000014C[];
extern const char str_00000158[];
extern const char str_00000164[];
extern const char str_0000016C[];
extern const u32 zero_tou2_00009ea8[1];
extern const char str_0000017C[];
extern const char str_00000184[];
extern const char str_0000019C[];
extern const char str_000001A8[];
extern const char str_000001B4[];
extern const char str_000001CC[];
extern const char str_000001D0[];
extern const char str_000001D4[];
extern const char str_000001E0[];
extern const char str_000001E8[];
extern const char str_000001EC[];
extern const char str_000001F0[];
extern const char str_000001FC[];
extern const char str_00000208[];
extern const char str_0000020C[];
extern const char str_00000210[];
extern const char str_0000021C[];
extern const char str_00000220[];
extern const char str_00000224[];
extern const char str_00000228[];
extern const char str_0000022C[];
extern const char str_00000230[];
extern const char str_00000234[];
extern const char str_0000023C[];
extern const char str_00000248[];
extern const char str_0000024C[];
extern const char str_00000258[];
extern const char str_00000270[];
extern const char str_00000274[];
extern const char str_00000280[];
extern const char str_0000028C[];
extern const char str_00000298[];
extern const char str_000002B0[];
extern const char str_000002C0[];
extern const char str_000002D0[];
extern const char str_000002D8[];
extern const char str_000002E0[];
extern const char str_000002E8[];
extern const char str_000002EC[];
extern const char str_000002F4[];
extern const char str_000002FC[];
extern const char str_00000304[];
extern const char str_0000030C[];
extern const char str_00000314[];
extern const char str_0000031C[];
extern const char str_00000320[];
extern const char str_00000328[];
extern const char str_00000330[];
extern const char str_00000338[];
extern const char str_00000340[];
extern const char str_00000370[];
extern const char str_0000037C[];
extern const char str_00000384[];
extern const char str_00000390[];
extern const char str_0000039C[];
extern const char str_000003A8[];
extern const char str_000003C0[];
extern const char str_000003CC[];
extern const char str_000003D8[];
extern const char str_000003E4[];
extern const char str_000003F4[];
extern const char str_00000404[];
extern const char str_00000414[];
extern const char str_00000420[];
extern const char str_00000434[];
extern const char str_0000043C[];
extern const char str_00000444[];
extern const char str_0000044C[];
extern const char str_00000454[];
extern const char str_0000045C[];
extern const char str_00000464[];
extern const char str_0000046C[];
extern const char str_00000480[];
extern const char str_00000498[];
extern const char str_000004B0[];
extern const char str_000004B4[];
extern const char str_000004C4[];
extern const char str_000004DC[];
extern const char str_000004F4[];
extern const char str_0000050C[];
extern const char str_0000052C[];
extern const char str_00000534[];
extern const char str_00000554[];
extern const char str_0000056C[];
extern const char str_00000570[];
extern const char str_00000580[];
extern const char str_00000588[];
extern const char str_00000598[];
extern const char str_000005A8[];
extern const char str_000005B8[];
extern const char str_000005C0[];
extern const char str_000005C8[];
extern const char str_000005D8[];
extern const char str_000005E8[];
extern const char str_000005F8[];
extern const char str_00000608[];
extern const char str_00000618[];
extern const char str_00000628[];
extern const char str_00000638[];
extern const char str_00000648[];
extern const char str_00000650[];
extern const char str_00000658[];
extern const char str_00000668[];
extern const char str_00000678[];
extern const char str_00000688[];
extern const char str_000006A8[];
extern const char str_000006B0[];
extern const char str_000006B8[];
extern const char str_000006C0[];
extern const char str_000006C8[];
extern const char str_000006D0[];
extern const char str_000006DC[];
extern const char str_000006E4[];
extern const char str_000006EC[];
extern const char str_000006F4[];
extern const char str_000006FC[];
extern const char str_00000704[];
extern const char str_00000720[];
extern const char str_00000730[];
extern const char str_00000740[];
extern const char str_00000748[];
extern const char str_00000750[];
extern const char str_00000758[];
extern const char str_00000768[];
extern const char str_00000774[];
extern const char str_00000780[];
extern const char str_0000078C[];
extern const char str_00000794[];
extern const char str_000007A8[];
extern const char str_000007B4[];
extern const char str_000007D0[];
extern const char str_000007EC[];
extern const char str_00000808[];
extern const char str_00000814[];
extern const char str_00000820[];
extern const char str_0000083C[];
extern const char str_00000844[];
extern const char str_0000085C[];
extern const char str_00000864[];
extern const char str_0000086C[];
extern const char str_00000884[];
extern const char str_00000890[];
extern const char str_0000089C[];
extern const char str_000008AC[];
extern const char str_000008BC[];
extern const char str_000008C8[];
extern const char str_000008E0[];
extern const char str_000008F0[];
extern const char str_000008FC[];
extern const char str_0000090C[];
extern const char str_0000091C[];
extern const char str_00000938[];
extern const char str_00000948[];
extern const char str_00000958[];
extern const char str_00000968[];
extern const char str_00000978[];
extern const char str_00000988[];
extern const char str_00000998[];
extern const char str_000009A8[];
extern const char str_000009AC[];
extern const char str_000009BC[];
extern const char str_000009CC[];
extern const char str_000009DC[];
extern const char str_000009EC[];
extern const char str_000009FC[];
extern const char str_00000A0C[];
extern const char str_00000A10[];
extern const char str_00000A14[];
extern const char str_00000A18[];
extern const char str_00000A2C[];
extern const char str_00000A3C[];
extern const char str_00000A4C[];
extern const char str_00000A5C[];
extern const char str_00000A64[];
extern const char str_00000A7C[];
extern const char str_00000A84[];
extern const char str_00000A94[];
extern const char str_00000AA4[];
extern const char str_00000ABC[];
extern const char str_00000ACC[];
extern const char str_00000AD0[];
extern const char str_00000AE0[];
extern const char str_00000AF0[];
extern const char str_00000B00[];
extern const char str_00000B10[];
extern const char str_00000B20[];
extern const char str_00000B30[];
extern const char str_00000B40[];
extern const char str_00000B5C[];
extern const char str_00000B6C[];
extern const char str_00000B7C[];
extern const char str_00000B8C[];
extern const char str_00000B9C[];
extern const char str_00000BAC[];
extern const char str_00000BBC[];
extern const char str_00000BCC[];
extern const char str_00000BDC[];
extern const char str_00000BEC[];
extern const char str_00000BFC[];
extern const char str_00000C0C[];
extern const char str_00000C1C[];
extern const char str_00000C2C[];
extern const char str_00000C3C[];
extern const char str_00000C4C[];
extern const char str_00000C5C[];
extern const char str_00000C6C[];
extern const char str_00000C7C[];
extern const char str_00000C8C[];
extern const char str_00000C9C[];
extern const char str_00000CAC[];
extern const char str_00000CBC[];
extern const char str_00000CCC[];
extern const char str_00000CDC[];
extern const char str_00000CEC[];
extern const char str_00000CFC[];
extern const char str_00000D0C[];
extern const char str_00000D10[];
extern const char str_00000D14[];
extern const char str_00000D24[];
extern const char str_00000D34[];
extern const char str_00000D44[];
extern const char str_00000D54[];
extern const char str_00000D64[];
extern const char str_00000D78[];
extern const char str_00000D80[];
extern const char str_00000D88[];
extern const char str_00000D98[];
extern const char str_00000DA8[];
extern const char str_00000DB8[];
extern const char str_00000DC8[];
extern const char str_00000DD8[];
extern const char str_00000DE8[];
extern const char str_00000DF8[];
extern const char str_00000E08[];
extern const char str_00000E18[];
extern const char str_00000E28[];
extern const char str_00000E38[];
extern const char str_00000E48[];
extern const char str_00000E58[];
extern const char str_00000E68[];
extern const char str_00000E78[];
extern const char str_00000E88[];
extern const char str_00000E98[];
extern const char str_00000EA8[];
extern const char str_00000EB8[];
extern const char str_00000EC8[];
extern const char str_00000ED8[];
extern const char str_00000EE8[];
extern const char str_00000EF8[];
extern const char str_00000F08[];
extern const char str_00000F18[];
extern const char str_00000F28[];
extern const char str_00000F38[];
extern const char str_00000F48[];
extern const char str_00000F58[];
extern const char str_00000F68[];
extern const char str_00000F78[];
extern const char str_00000F88[];
extern const char str_00000F98[];
extern const char str_00000FA8[];
extern const char str_00000FB8[];
extern const char str_00000FC8[];
extern const char str_00000FD8[];
extern const char str_00000FE8[];
extern const char str_00000FF8[];
extern const char str_00001008[];
extern const char str_00001018[];
extern const char str_00001028[];
extern const char str_00001038[];
extern const char str_00001048[];
extern const char str_00001058[];
extern const char str_00001068[];
extern const char str_00001078[];
extern const char str_00001080[];
extern const char str_00001088[];
extern const char str_00001098[];
extern const char str_000010A8[];
extern const char str_000010B8[];
extern const char str_000010C8[];
extern const char str_000010E8[];
extern const char str_000010F0[];
extern const char str_000010F8[];
extern const char str_00001100[];
extern const char str_00001108[];
extern const char str_00001110[];
extern const char str_00001118[];
extern const char str_00001120[];
extern const char str_00001128[];
extern const char str_00001130[];
extern const char str_00001138[];
extern const char str_0000114C[];
extern const char str_00001154[];
extern const char str_00001160[];
extern const char str_00001168[];
extern const char str_0000117C[];
extern const char str_0000118C[];
extern const char str_000011A4[];
extern const char str_000011A8[];
extern const char str_000011B0[];
extern const char str_000011B8[];
extern const char str_000011C0[];
extern const char str_000011CC[];
extern const char str_000011D4[];
extern const char str_000011DC[];
extern const char str_000011E4[];
extern const char str_00001200[];
extern const char str_00001220[];
extern const char str_00001234[];
extern const char str_0000123C[];
extern const char str_0000124C[];
extern const char str_0000125C[];
extern const char str_0000126C[];
extern const char str_0000127C[];
extern const char str_00001280[];
extern const char str_00001284[];
extern const char str_0000129C[];
extern const char str_000012B0[];
extern const char str_000012BC[];
extern const char str_000012D0[];
extern const char str_000012D4[];
extern const char str_000012E4[];
extern const char str_000012EC[];
extern const char str_000012FC[];
extern const char str_0000130C[];
extern const char str_00001324[];
extern const char str_00001328[];
extern const char str_0000132C[];
extern const char str_0000133C[];
extern const char str_0000134C[];
extern const char str_0000135C[];
extern const char str_00001374[];
extern const char str_00001384[];
extern const char str_00001394[];
extern const char str_000013A4[];
extern const char str_000013B4[];
extern const char str_000013C4[];
extern const char str_000013D4[];
extern const char str_000013E8[];
extern const char str_000013FC[];
extern const char str_00001410[];
extern const char str_00001424[];
extern const char str_00001428[];
extern const char str_00001438[];
extern const char str_00001450[];
extern const char str_00001458[];
extern const char str_0000146C[];
extern const char str_00001488[];
extern const char str_00001490[];
extern const char str_000014A4[];
extern const char str_000014B8[];
extern const char str_000014CC[];
extern const char str_000014E0[];
extern const char str_000014F4[];
extern const char str_00001504[];
extern const char str_00001520[];
extern const char str_00001530[];
extern const char str_00001540[];
extern const char str_00001550[];
extern const char str_00001568[];
extern const char str_00001570[];
extern const char str_00001584[];
extern const char str_00001594[];
extern const char str_000015A4[];
extern const char str_000015B4[];
extern const char str_000015C4[];
extern const char str_000015D4[];
extern const char str_000015E4[];
extern const char str_000015F4[];
extern const char str_00001604[];
extern const char str_00001614[];
extern const char str_00001624[];
extern const char str_00001634[];
extern const char str_00001644[];
extern const char str_00001654[];
extern const char str_00001664[];
extern const char str_00001674[];
extern const char str_00001684[];
extern const char str_00001694[];
extern const char str_000016A4[];
extern const char str_000016B4[];
extern const char str_000016C4[];
extern const char str_000016D4[];
extern const char str_000016E4[];
extern const char str_000016F4[];
extern const char str_00001704[];
extern const char str_00001714[];
extern const char str_00001724[];
extern const char str_00001734[];
extern const char str_00001744[];
extern const char str_00001754[];
extern const char str_00001764[];
extern const char str_00001774[];
extern const char str_00001784[];
extern const char str_00001794[];
extern const char str_000017A4[];
extern const char str_000017B4[];
extern const char str_000017C4[];
extern const char str_000017D4[];
extern const char str_000017D8[];
extern const char str_000017E8[];
extern const char str_000017F0[];
extern const char str_000017F8[];
extern const char str_00001804[];
extern const char str_00001810[];
extern const char str_0000181C[];
extern const char str_00001824[];
extern const char str_0000182C[];
extern const char str_00001834[];
#undef GXSetTexCoordGen
static void callback(MapTevCallbackInfo* info);
static void callback(MapTevCallbackInfo* info);
typedef struct StoneEffWork { s32 field_0x0; Vec pos; } StoneEffWork;
typedef struct StoneEffWork2 { u8 field_0x0[0x1C]; f32 rot; } StoneEffWork2;
typedef struct StoneEffWork3 { s32 field_0x0; u16 flags; } StoneEffWork3;
void mapObjGetPos(const char* name, Vec* pos);
static f32 cosf(f32 x);
static f32 cosf(f32 x);
static f32 sinf(f32 x);
static f32 sinf(f32 x);
double cos(double x);
double sin(double x);
void psndMapChange(void);
typedef struct ScreenWork { void* buf; s32 ready; f32 scale; f32 scaleTarget; f32 x; f32 xTarget; f32 y; f32 yTarget; s32 count; s32 mode; f32 field_0x28; u8* noise; } ScreenWork;
static f32 randf(f32 min, f32 max);
static f32 randf(f32 min, f32 max);
void GXSetTexCoordGen(GXTexCoordID dst, GXTexGenType func, GXTexGenSrc src, u32 mtx);
static void screen_capture(CameraId cameraId, void* param);
static void screen_capture(CameraId cameraId, void* param);
void kyaku_disp(CameraId camera, void* param);
void kyaku_disp(CameraId camera, void* param);
static void pose_main(void);
static void pose_main(void);
void extLoadRenderMode(void);
void extLoadVertex(void);
void extLoadTexture(void);
void extLoadTev(void);
void extDraw(void);
void extLoadTextureExit(void);
typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
typedef struct Kyaku { u16 flags; u8 pad_0x2[2]; Vec pos; s16 animIdx; u8 pad_0x12[6]; u64 time; } Kyaku;
typedef struct KyakuAnim { char name[16]; char anim[8]; s16 loop; f32 rate; s32 start; s32 count; } KyakuAnim;
typedef struct KyakuWork { s32 field_0x0; s32 num; Kyaku* kyakus; s32 animNum; KyakuAnim anim[32]; } KyakuWork;
typedef struct KyakuData { const char* name; const char* anim; f32 rate; } KyakuData;
static s32 tou_03_bss_0xC;
KyakuWork* kyaku_wp;
static ScreenWork* screen_wp;
s32 gans_alpha;
ExtPose* extGetPosePtr(void);
s32 extGetPoseNum(void);
static void pose_init(void);
static void pose_init(void);
static void pose_change(Kyaku* kyaku, const char* name, const char* anim);
static void pose_change(Kyaku* kyaku, const char* name, const char* anim);
u32 __tou_rand(void);
u32 __tou_rand(void);
void __tou_srand(u32 seed);
void __tou_srand(u32 seed);
void fbatSetAttackAnnounce(s32 type);
void fbatSetAttackAnnounceEnable(void);

s32 _firstattack_setting(EventEntry* event, BOOL isFirstCall);
s32 _firstattack_setting(EventEntry* event, BOOL isFirstCall);
s32 burst_chain(EventEntry* event, BOOL isFirstCall);
s32 burst_chain(EventEntry* event, BOOL isFirstCall);
s32 confupose(EventEntry* event, BOOL isFirstCall);
s32 confupose(EventEntry* event, BOOL isFirstCall);
s32 eff_pos(EventEntry* event, BOOL isFirstCall);
s32 eff_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_exec_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_entername(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_info(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_mapchange(EventEntry* event, BOOL isFirstCall);
s32 evt_boss_stone_r(EventEntry* event, BOOL isFirstCall);
s32 evt_boss_stone_r(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_off(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_set(EventEntry* event, BOOL isFirstCall);
s32 evt_cam_shake(EventEntry* event, BOOL isFirstCall);
s32 evt_eff(EventEntry* event, BOOL isFirstCall);
s32 evt_eff64(EventEntry* event, BOOL isFirstCall);
s32 evt_eff_delete(EventEntry* event, BOOL isFirstCall);
s32 evt_eff_fukidashi(EventEntry* event, BOOL isFirstCall);
s32 evt_ext_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_fade_set_mapchange_type(EventEntry* event, BOOL isFirstCall);
s32 evt_hitobj_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_item_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_item_set_position(EventEntry* event, BOOL isFirstCall);
s32 evt_map_checkanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_pauseanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_playanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_replayanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_set_playrate(EventEntry* event, BOOL isFirstCall);
s32 evt_map_set_tevcallback(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_rotate(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_cont_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_dispflag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_name_hitobj_ride(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_party(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_jump_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_key_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_kill_party(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_mov_pos2(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_normalize(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_dir(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_dir_npc(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_pose(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print_add(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print_add_insert(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print_insert(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print_party(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_select(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_toge(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_battle_start(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_check(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_clear_paper(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_get_battle_result(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_get_battle_rule_keep_result(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_jump_position_nohit(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_move_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_anim(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_attack_mode(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_autotalkpose(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_battle_info(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_battle_rule(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_height(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_paper(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_paper_anim(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_rotate(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_ry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_scale(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_stay_anim(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_tribe(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_width(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_setup(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_status_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_wait_battle_end(EventEntry* event, BOOL isFirstCall);
s32 evt_paper_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_party_cont_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_party_get_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_jump_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_move_pos2(EventEntry* event, BOOL isFirstCall);
s32 evt_party_run(EventEntry* event, BOOL isFirstCall);
s32 evt_party_set_dir(EventEntry* event, BOOL isFirstCall);
s32 evt_party_set_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_set_pose(EventEntry* event, BOOL isFirstCall);
s32 evt_party_stop(EventEntry* event, BOOL isFirstCall);
s32 evt_run_case_evt(EventEntry* event, BOOL isFirstCall);
s32 evt_seq_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_set_dir_to_target(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgm_scope(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmoff_f(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmon_f(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_envoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_envon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfx_pit(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfx_vol(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxon_3d(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_get_sincos(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_get_system_flag(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_intpl_get_value(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_intpl_init(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_intpl_msec_get_value(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_intpl_msec_init(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_random(EventEntry* event, BOOL isFirstCall);
s32 evt_tou_get_fighter_battle_msg_28_text_3CB4(EventEntry* event, BOOL isFirstCall);
s32 evt_tou_get_fighter_info_28_text_3E58(EventEntry* event, BOOL isFirstCall);
s32 evt_tou_get_fighter_name2_28_text_3DD4(EventEntry* event, BOOL isFirstCall);
s32 evt_tou_get_fighter_num(EventEntry* event, BOOL isFirstCall);
s32 evt_tou_get_ranking_28_text_4048(EventEntry* event, BOOL isFirstCall);
s32 evt_tou_set_ranking_win_lose_28_text_35C0(EventEntry* event, BOOL isFirstCall);
s32 evt_tou_set_rule_result_28_text_355C(EventEntry* event, BOOL isFirstCall);
s32 gans_white_off(EventEntry* event, BOOL isFirstCall);
s32 gans_white_off(EventEntry* event, BOOL isFirstCall);
s32 gans_white_on(EventEntry* event, BOOL isFirstCall);
s32 gans_white_on(EventEntry* event, BOOL isFirstCall);
s32 getY(EventEntry* event, BOOL isFirstCall);
s32 getY(EventEntry* event, BOOL isFirstCall);
s32 item_jump(EventEntry* event, BOOL isFirstCall);
s32 item_jump(EventEntry* event, BOOL isFirstCall);
static s32 screen_evt(EventEntry* event, BOOL isFirstCall);
static s32 screen_evt(EventEntry* event, BOOL isFirstCall);
s32 screen_init(EventEntry* event, BOOL isFirstCall);
s32 screen_init(EventEntry* event, BOOL isFirstCall);
s32 snd_sfx_stop(EventEntry* event, BOOL isFirstCall);
s32 snd_sfx_stop(EventEntry* event, BOOL isFirstCall);
s32 starstone_sound_onoff(EventEntry* event, BOOL isFirstCall);
s32 starstone_sound_onoff(EventEntry* event, BOOL isFirstCall);
s32 tou_champion_belt_28_text_2A10(EventEntry* event, BOOL isFirstCall);
s32 tou_champion_belt_onoff_28_text_29DC(EventEntry* event, BOOL isFirstCall);
static void callback(MapTevCallbackInfo* info);
static f32 cosf(f32 x);
static f32 sinf(f32 x);
s32 tribe_chk(EventEntry* event, BOOL isFirstCall);
s32 tribe_chk(EventEntry* event, BOOL isFirstCall);
void screen_tev(MapTevCallbackInfo* info);
void screen_tev(MapTevCallbackInfo* info);
void GXSetTexCoordGen(GXTexCoordID dst, GXTexGenType func, GXTexGenSrc src, u32 mtx);
static void screen_capture(CameraId cameraId, void* param);
void ext_kyaku_dispent(void);
void ext_kyaku_dispent(void);
void ext_kyaku_main(void);
void ext_kyaku_main(void);
void kyaku_disp(CameraId camera, void* param);
void ext_kyaku_init(void);
void ext_kyaku_init(void);
static f32 randf(f32 min, f32 max);
u32 __tou_rand(void);
void __tou_srand(u32 seed);
static void pose_change(Kyaku* kyaku, const char* name, const char* anim);
static void pose_main(void);
static void pose_init(void);
extern s32 bero_case_entry[];
extern s32 bero_case_switch_off[];
extern s32 bero_close_door_play_se[];
extern s32 evt_bero_info_run[];
extern s32 evt_msg_continue[];
extern s32 evt_npc_get_height[];
extern s32 evt_npc_sound_data_reset[];
extern s32 evt_npc_sound_data_set[];
extern s32 evt_party_set_dir_npc[];
extern s32 evt_sub_starstone[];
extern s32 evt_tou_get_fighter_tribe[];

__declspec(section ".data") u64 fd_tou_03_negone_one_374;
__declspec(section ".data") s32 fd_tou_03_neg_one_382[1];
__declspec(section ".data") s32 fd_tou_03___local_PI_383[1];
__declspec(section ".data") s32 fd_tou_03___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tou_03_one_negone_373;
__declspec(section ".data") s32 fd_tou_03___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tou_03_one_381[1];
__declspec(section ".data") u64 fd_tou_03_negone_one_360;
__declspec(section ".data") s32 fd_tou_03_neg_one_365[1];
__declspec(section ".data") s32 fd_tou_03___local_PI_366[1];
__declspec(section ".data") s32 fd_tou_03___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tou_03_one_negone_359;
__declspec(section ".data") s32 fd_tou_03___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tou_03_one_364[1];
__declspec(section ".data") s32 fd_tou_03__three_localstatic4_sqrtf[2];
__declspec(section ".data") s32 fd_tou_03__half_localstatic3_sqrtf[2];
s32 ext_kyaku_data[153];
__declspec(section ".data") s32 x[1];
s32 evt_kyaku[138];
__declspec(section ".data") static s32 inta_tex[8];
s32 open_main[53];
s32 close_main[37];
static s32 w_door_open[22];
static s32 w_door_close[22];
__declspec(section ".data") static s32 w_open[5];
__declspec(section ".data") static s32 w_close[5];
static s32 e_door_open[22];
static s32 e_door_close[22];
__declspec(section ".data") static s32 e_open[5];
__declspec(section ".data") static s32 e_close[5];
s32 s1_door_open[22];
s32 s1_door_close[22];
s32 s1_door_open2[19];
static s32 s1_open[18];
static s32 s1_close[17];
s32 s2_door_open[22];
s32 s2_door_close[22];
s32 s2_door_open2[19];
static s32 s2_open[18];
static s32 s2_close[17];
static s32 bero_data[75];
s32 evt_tougi[777];
s32 init_kinosikowa[13];
static s32 npcEnt[115];
s32 evt_damage_pose[63];
static s32 evt_kime_pose[56];
s32 npc_entry[623];
s32 evt_random_battle[335];
s32 evt_random_battle2[317];
s32 evt_teki_nyuujyou[107];
s32 evt_teki_nyuujyou_default[183];
s32 burst_chain_entry[289];
s32 burst_wangwang[69];
s32 evt_match[362];
s32 evt_kurikuri_opening[442];
s32 evt_kurikuri_win[231];
s32 evt_kurikuri_lose[146];
s32 evt_shinemon_opening[647];
s32 evt_shinemon_win[199];
s32 evt_shinemon_lose[84];
s32 evt_champ_opening[556];
s32 evt_champ_opening_re[767];
s32 evt_champ_win[335];
s32 evt_champ_lose[124];
s32 evt_default_opening[748];
s32 evt_default_win[201];
s32 evt_default_lose[137];
static s32 evt_champion[365];
s32 evt_champion2[178];
__declspec(section ".data") s32 block_data[9];
static s32 evt_shake[39];
s32 evt_boss_stone[63];
static s32 evt_boss[1916];
s32 evt_watch_match[515];
s32 evt_kyaku_1[56];
s32 evt_kyaku_2[56];
s32 evt_kyaku_3[56];
s32 evt_kyaku_4[88];
s32 evt_kyaku_5[56];
s32 evt_kyaku_6[56];
s32 evt_kyaku_7[56];
s32 evt_kyaku_8[88];
s32 tou_03_init_evt[370];

__declspec(section ".data") u64 fd_tou_03_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tou_03_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tou_03___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tou_03___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tou_03_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tou_03___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tou_03_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tou_03_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tou_03_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tou_03___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tou_03___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tou_03_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tou_03___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tou_03_one_364[] = {
    1065353216,
};

__declspec(section ".data") s32 fd_tou_03__three_localstatic4_sqrtf[] = {
    1074266112, 0,
};

__declspec(section ".data") s32 fd_tou_03__half_localstatic3_sqrtf[] = {
    1071644672, 0,
};

s32 ext_kyaku_data[] = {
    (s32)((char*)str_00000000), (s32)((char*)str_0000000C), 0, (s32)((char*)str_00000000), (s32)((char*)str_0000000C), 1092616192, (s32)((char*)str_00000000), (s32)((char*)str_0000000C),
    1101004800, (s32)((char*)str_00000000), (s32)((char*)str_0000000C), 1106247680, (s32)((char*)str_00000000), (s32)((char*)str_0000000C), 1109393408, (s32)((char*)str_00000000),
    (s32)((char*)str_0000000C), 1112014848, (s32)((char*)str_00000000), (s32)((char*)str_0000000C), 1114636288, (s32)((char*)str_00000000), (s32)((char*)str_0000000C), 1116471296,
    (s32)((char*)str_00000000), (s32)((char*)str_0000000C), 1117782016, (s32)((char*)str_00000000), (s32)((char*)str_0000000C), 1119092736, (s32)((char*)str_00000000), (s32)((char*)str_0000000C),
    1120403456, (s32)((char*)str_00000000), (s32)((char*)str_0000000C), 1121714176, (s32)((char*)str_00000000), (s32)((char*)str_0000000C), 1123024896, (s32)((char*)str_00000000),
    (s32)((char*)str_0000000C), 1124204544, (s32)((char*)str_00000000), (s32)((char*)str_0000000C), 1124859904, (s32)((char*)str_00000000), (s32)((char*)str_0000000C), 1125515264,
    (s32)((char*)str_00000000), (s32)((char*)str_0000000C), 1126170624, (s32)((char*)str_00000000), (s32)((char*)str_0000000C), 1126825984, (s32)((char*)str_00000000), (s32)((char*)str_0000000C),
    1127481344, (s32)((char*)str_00000000), (s32)((char*)str_0000000C), 1128136704, (s32)((char*)str_00000014), (s32)((char*)str_00000020), 0, (s32)((char*)str_00000014),
    (s32)((char*)str_00000020), 1092616192, (s32)((char*)str_00000014), (s32)((char*)str_00000020), 1101004800, (s32)((char*)str_00000014), (s32)((char*)str_00000020), 1106247680,
    (s32)((char*)str_00000014), (s32)((char*)str_00000020), 1109393408, (s32)((char*)str_00000014), (s32)((char*)str_00000020), 1112014848, (s32)((char*)str_00000014), (s32)((char*)str_00000020),
    1114636288, (s32)((char*)str_00000014), (s32)((char*)str_00000020), 1116471296, (s32)((char*)str_00000014), (s32)((char*)str_00000020), 1117782016, (s32)((char*)str_00000014),
    (s32)((char*)str_00000020), 1119092736, (s32)((char*)str_00000014), (s32)((char*)str_00000020), 1120403456, (s32)((char*)str_00000014), (s32)((char*)str_00000020), 1121714176,
    (s32)((char*)str_00000014), (s32)((char*)str_00000020), 1123024896, (s32)((char*)str_00000014), (s32)((char*)str_00000020), 1124204544, (s32)((char*)str_00000014), (s32)((char*)str_00000020),
    1124859904, (s32)((char*)str_00000014), (s32)((char*)str_00000020), 1125515264, (s32)((char*)str_00000014), (s32)((char*)str_00000020), 1126170624, (s32)((char*)str_00000028),
    (s32)((char*)str_00000030), 0, (s32)((char*)str_00000028), (s32)((char*)str_00000030), 1092616192, (s32)((char*)str_00000028), (s32)((char*)str_00000030), 1101004800,
    (s32)((char*)str_00000028), (s32)((char*)str_00000030), 1106247680, (s32)((char*)str_00000028), (s32)((char*)str_00000030), 1109393408, (s32)((char*)str_00000028), (s32)((char*)str_00000030),
    1112014848, (s32)((char*)str_00000034), (s32)((char*)str_00000040), 0, (s32)((char*)str_00000034), (s32)((char*)str_00000040), 1092616192, (s32)((char*)str_00000034),
    (s32)((char*)str_00000040), 1101004800, (s32)((char*)str_00000034), (s32)((char*)str_00000040), 1106247680, (s32)((char*)str_00000034), (s32)((char*)str_00000040), 1109393408,
    (s32)((char*)str_00000034), (s32)((char*)str_00000040), 1112014848, (s32)((char*)str_00000034), (s32)((char*)str_00000040), 1114636288, 0, 0,
    0,
};

__declspec(section ".data") EVT_BEGIN(x)
EVT_END()

#ifdef NONMATCHING
s32 _firstattack_setting(EventEntry* event, BOOL isFirstCall) {
    FieldBattleData* fbat = fbatGetPointer();

    *(s32*)&fbat->field_C[4] = 0x10000000;
    *(s32*)&fbat->field_C[8] = 0x10;
    *(u32*)&fbat->field_C[0x10] &= ~1;
    fbatSetAttackAnnounce(0x10000000);
    fbatSetAttackAnnounceEnable();
    return EVT_RETURN_DONE;
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
static void pose_init(void) {
    char name[32];
    char anim[32];
    KyakuData* d = (KyakuData*)ext_kyaku_data;
    s32 i = 0;
    s32 start;

    strcpy(name, "");
    strcpy(anim, "");
    kyaku_wp->animNum = -1;
    do {
        if (strcmp(d->name, name) != 0) {
            strcpy(name, d->name);
            strcpy(anim, "");
        }
        if (strcmp(d->anim, anim) != 0) {
            strcpy(anim, d->anim);
            start = i;
            kyaku_wp->animNum++;
        }
        strcpy(kyaku_wp->anim[kyaku_wp->animNum].name, name);
        strcpy(kyaku_wp->anim[kyaku_wp->animNum].anim, anim);
        kyaku_wp->anim[kyaku_wp->animNum].start = start;
        kyaku_wp->anim[kyaku_wp->animNum].count = i - start + 1;
        kyaku_wp->anim[kyaku_wp->animNum].rate = d->rate;
        kyaku_wp->anim[kyaku_wp->animNum].loop = 1;
        i++;
        d++;
    } while (d->name != NULL);
    kyaku_wp->animNum++;
}
#endif
#pragma dont_inline reset

#pragma dont_inline on
#ifdef NONMATCHING
static void pose_main(void) {
    s32 i;
    ExtPose* pose;
    Kyaku* kyaku;
    KyakuAnim* a;
    f32 t;

    pose = extGetPosePtr();
    kyaku = kyaku_wp->kyakus;

    for (i = 0; i < kyaku_wp->num; i++, kyaku++, pose++) {
        a = &kyaku_wp->anim[kyaku->animIdx];
        t = 60.0f * OSTicksToMilliseconds((u64)(gp->renderTime - kyaku->time)) / 1000.0f / a->rate;
        if (t >= 1.0f) {
            kyaku->time = gp->renderTime;
            t = 0.0f;
        }
        pose->frame = a->start + (s32)((a->count - 1) * t);
    }
}
#endif
#pragma dont_inline reset

#pragma dont_inline on
#ifdef NONMATCHING
static void pose_change(Kyaku* kyaku, const char* name, const char* anim) {
    KyakuAnim* a;
    s32 i;

    for (i = 0, a = kyaku_wp->anim; i < kyaku_wp->animNum; i++, a++) {
        if (strcmp(a->name, name) == 0 && strcmp(a->anim, anim) == 0) {
            break;
        }
    }
    if (i < kyaku_wp->animNum && kyaku->animIdx != i) {
        kyaku->animIdx = i;
        kyaku->time = gp->renderTime + rand();
    }
}
#endif
#pragma dont_inline reset

#pragma dont_inline on
#ifdef NONMATCHING
void __tou_srand(u32 seed) {
    x[0] = seed;
}
#endif
#pragma dont_inline reset

#pragma dont_inline on
#ifdef NONMATCHING
u32 __tou_rand(void) {
    x[0] = x[0] * 1103515245 + 12345;
    return ((u32)x[0] >> 16) & 0x7FFF;
}
#endif
#pragma dont_inline reset

#pragma dont_inline on
#ifdef NONMATCHING
static f32 randf(f32 min, f32 max) {
    f32 r = __tou_rand() / 32767.0f;

    return r * (max - min) + min;
}
#endif
#pragma dont_inline reset

#ifdef NONMATCHING
void ext_kyaku_init(void) {
    s32 far;
    s32 i;
    ExtPose* pose;
    Kyaku* kyaku;
    s32 side;
    f32 dist;
    f32 angle;
    f32 x;
    f32 z;
    f32 hx;
    f32 hy;
    f32 hz;
    f32 hd;
    f32 nx;
    f32 ny;
    f32 nz;

    kyaku_wp = _mapAlloc(sizeof(KyakuWork));
    memset(kyaku_wp, 0, sizeof(KyakuWork));
    kyaku_wp->num = extGetPoseNum();
    kyaku_wp->kyakus = _mapAlloc(kyaku_wp->num * sizeof(Kyaku));
    memset(kyaku_wp->kyakus, 0, kyaku_wp->num * sizeof(Kyaku));
    pose_init();
    __tou_srand(0x25B0E2B);
    pose = extGetPosePtr();
    kyaku = kyaku_wp->kyakus;
    for (i = 0; i < kyaku_wp->num; i++, pose++, kyaku++) {
        pose->flags |= 7;
        PSMTXIdentity(pose->mtx);
        while (TRUE) {
            far = __tou_rand() % 100 >= 30;
            angle = randf(0.0f, 6.283184f);
            if (!far) {
                dist = randf(250.0f, 500.0f);
            } else {
                side = angle < 0.7853982f || angle > 5.4977875f;
                dist = side ? randf(550.0f, 650.0f) : randf(550.0f, 850.0f);
            }
            x = dist * sinf(angle);
            z = dist * cosf(angle);
            if (!far) {
                if (!(__fabs(z) > 70.0)) {
                    continue;
                }
                hd = 100000.0f;
                if (hitCheckFilter(NULL, &hx, &hy, &hz, &hd, &nx, &ny, &nz, x, 100.0f, z, 0.0f, -1.0f, 0.0f) == NULL) {
                    continue;
                }
                if (0.0f != hy) {
                    continue;
                }
                pose->mtx[0][3] = hx;
                pose->mtx[2][3] = hz;
                pose->rot = angleABf(0.0f, 0.0f, hx, hz);
            } else {
                hd = 100000.0f;
                if (hitCheckFilter(NULL, &hx, &hy, &hz, &hd, &nx, &ny, &nz, x, 500.0f, z, 0.0f, -1.0f, 0.0f) == NULL) {
                    continue;
                }
                pose->mtx[0][3] = hx;
                pose->mtx[1][3] = hy;
                pose->mtx[2][3] = hz;
                if (hz > 570.0f && __fabsf(hx) > 40.0f && __fabsf(hx) < 60.0f) {
                    pose->mtx[0][3] += hx > 0.0f ? -15 : 15;
                }
                pose->rot = angleABf(0.0f, 0.0f, hx, hz);
            }
            break;
        }
        if (strcmp(gp->beroEnterName, "s_bero_2") != 0 && pose->mtx[2][3] > 350.0f) {
            pose->flags &= ~1;
        }
        if (0.0f != pose->mtx[1][3]) {
            kyaku->flags |= 1;
        }
        kyaku->pos = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
        switch (irand(1000) % 4) {
            case 0:
                pose_change(kyaku, "c_kinopio", "KNP_S_1");
                break;
            case 1:
                pose_change(kyaku, "c_kinopiko", "KNF_S_1");
                break;
            case 2:
                pose_change(kyaku, "c_roten", "S_1");
                break;
            case 3:
                pose_change(kyaku, "c_jugemu", "JGM_S_1");
                break;
        }
    }
}
#endif

EVT_BEGIN(evt_kyaku)
    CALL(evt_npc_entry, STRING(((char*)str_00000054)), STRING(((char*)str_00000000)))
    CALL(evt_npc_entry, STRING(((char*)str_0000005C)), STRING(((char*)str_00000014)))
    CALL(evt_npc_entry, STRING(((char*)str_00000064)), STRING(((char*)str_00000028)))
    CALL(evt_npc_entry, STRING(((char*)str_0000006C)), STRING(((char*)str_00000034)))
    CALL(evt_npc_set_tribe, STRING(((char*)str_00000054)), STRING(((char*)str_00000074)))
    CALL(evt_npc_set_tribe, STRING(((char*)str_0000005C)), STRING(((char*)str_00000080)))
    CALL(evt_npc_set_tribe, STRING(((char*)str_00000064)), STRING(((char*)str_0000008C)))
    CALL(evt_npc_set_tribe, STRING(((char*)str_0000006C)), STRING(((char*)str_00000094)))
    CALL(evt_npc_set_ry, STRING(((char*)str_00000054)), 90)
    CALL(evt_npc_set_ry, STRING(((char*)str_0000005C)), 90)
    CALL(evt_npc_set_ry, STRING(((char*)str_00000064)), 270)
    CALL(evt_npc_set_ry, STRING(((char*)str_0000006C)), 270)
    CALL(evt_bero_get_entername, LW(0))
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000000A0)))
        CALL(evt_npc_set_position, STRING(((char*)str_00000054)), -40, 120, 680)
        CALL(evt_npc_set_position, STRING(((char*)str_0000005C)), -15, 120, 670)
        CALL(evt_npc_set_position, STRING(((char*)str_00000064)), 15, 120, 680)
        CALL(evt_npc_set_position, STRING(((char*)str_0000006C)), 40, 120, 670)
        ELSE
        CALL(evt_npc_set_position, STRING(((char*)str_00000054)), -50, 0, 370)
        CALL(evt_npc_set_position, STRING(((char*)str_0000005C)), -20, 0, 360)
        CALL(evt_npc_set_position, STRING(((char*)str_00000064)), 20, 0, 370)
        CALL(evt_npc_set_position, STRING(((char*)str_0000006C)), 50, 0, 360)
    END_IF
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00000054)), 1073743360)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_0000005C)), 1073743360)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00000064)), 1073743360)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_0000006C)), 1073743360)
    CALL(evt_ext_entry, 1000, PTR(ext_kyaku_data), PTR(ext_kyaku_init), PTR(ext_kyaku_main), PTR(ext_kyaku_dispent))
    CALL(evt_hitobj_onoff, STRING(((char*)str_000000AC)), 1, 0)
    RETURN
EVT_END()

__declspec(section ".data") static s32 inta_tex[] __attribute__((aligned(32))) = {
    -1, 0, -1, 0, -1, 0, -1, 0,
};

EVT_BEGIN(open_main)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, LW(8), LW(0), 0, 0)
    CALL(evt_mapobj_rotate, 1, LW(9), LW(0), 0, 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000000B8)), LW(0), LW(1), LW(2), 0)
    RETURN
EVT_END()

EVT_BEGIN(close_main)
    CALL(evt_sub_intpl_msec_init, 2, 180, 0, 500)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, LW(8), LW(0), 0, 0)
    CALL(evt_mapobj_rotate, 1, LW(9), LW(0), 0, 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000C8)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000D4)), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000C8)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000D4)), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(w_open)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(w_close)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000E0)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000EC)), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000E0)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000EC)), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(e_open)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(e_close)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(s1_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000F8)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000104)), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(s1_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000F8)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000104)), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(s1_door_open2)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000F8)), LW(0), 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000104)), LW(0), 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(s1_open)
    BEGIN_INLINE_EVENT
        CALL(evt_bero_exec_wait, 65536)
        SET_VALUE(LW(8), STRING(((char*)str_000000F8)))
        SET_VALUE(LW(9), STRING(((char*)str_00000104)))
        CALL_CHILD(PTR(open_main))
    END_INLINE_EVENT
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(s1_close)
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(8), STRING(((char*)str_000000F8)))
        SET_VALUE(LW(9), STRING(((char*)str_00000104)))
        CALL_CHILD(PTR(close_main))
    END_INLINE_EVENT
    WAIT_MS(500)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(s2_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000110)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_0000011C)), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(s2_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000110)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_0000011C)), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(s2_door_open2)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000110)), LW(0), 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_0000011C)), LW(0), 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(s2_open)
    BEGIN_INLINE_EVENT
        CALL(evt_bero_exec_wait, 65536)
        SET_VALUE(LW(8), STRING(((char*)str_00000110)))
        SET_VALUE(LW(9), STRING(((char*)str_0000011C)))
        CALL_CHILD(PTR(open_main))
    END_INLINE_EVENT
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(s2_close)
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(8), STRING(((char*)str_00000110)))
        SET_VALUE(LW(9), STRING(((char*)str_0000011C)))
        CALL_CHILD(PTR(close_main))
    END_INLINE_EVENT
    WAIT_MS(500)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_data[] = {
    (s32)((char*)str_00000128), 65542, 20000, 100000, 0, 0, -1, (s32)w_open,
    -1, (s32)w_close, (s32)((char*)str_00000130), (s32)((char*)str_00000138), 327685, (s32)w_door_close, (s32)w_door_open, (s32)((char*)str_00000144),
    65542, 20000, 100000, 0, 0, -1, (s32)e_open, -1,
    (s32)e_close, (s32)((char*)str_00000130), (s32)((char*)str_0000014C), 327685, (s32)e_door_close, (s32)e_door_open, (s32)((char*)str_00000158), 65542,
    20000, 100000, 0, 0, -1, (s32)s1_open, -1, (s32)s1_close,
    (s32)((char*)str_00000164), (s32)((char*)str_0000014C), 327685, (s32)s1_door_close, (s32)s1_door_open, (s32)((char*)str_000000A0), 65542, 20000,
    100000, 0, 0, -1, (s32)s2_open, -1, (s32)s2_close, (s32)((char*)str_00000164),
    (s32)((char*)str_00000138), 327685, (s32)s2_door_close, (s32)s2_door_open, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

s32 evt_tougi[] = {
    131163, (s32)evt_mario_key_onoff, 0, 131163, (s32)evt_party_stop, 0, 131122, -70000000,
    0, 131163, (s32)evt_bero_get_entername, -30000000, 131084, -30000000, (s32)((char*)str_000000A0), 131122,
    -70000000, 1, 33, 131096, -70000000, 0, 262235, (s32)evt_mario_set_pos,
    -25, 0, 635, 327771, (s32)evt_party_set_pos, 0, 25, 0,
    635, 262235, (s32)evt_mario_set_dir, 90, 0, 0, 262235, (s32)evt_party_set_dir,
    0, 270, 0, 32, 262235, (s32)evt_mario_set_pos, -25, 120,
    980, 327771, (s32)evt_party_set_pos, 0, 25, 120, 980, 262235,
    (s32)evt_mario_set_dir, 90, 0, 0, 262235, (s32)evt_party_set_dir, 0, 270,
    0, 33, 131163, (s32)evt_mario_set_dir_npc, (s32)/*"チャンピョン"*/(char*)str_0000016C, 196699, (s32)evt_party_set_dir_npc, 0,
    (s32)/*"相手"*/(char*)str_0000017C, 196699, (s32)evt_set_dir_to_target, (s32)/*"チャンピョン"*/(char*)str_0000016C, (s32)/*"相手"*/(char*)str_0000017C, 589915, (s32)evt_cam3d_evt_set, 0,
    563, 962, 0, 554, 412, 0, 11, 65545,
    1, 458843, (s32)evt_npc_sound_data_set, (s32)/*"相手"*/(char*)str_0000017C, -250000000, -250000000, -250000000, -250000000,
    (s32)((char*)str_00000184), 131124, -30000000, -230184320, 131096, -70000000, 0, 65630,
    (s32)s1_door_open, 32, 65630, (s32)s2_door_open, 33, 131163, (s32)evt_seq_wait, 2,
    589915, (s32)evt_cam3d_evt_set, 0, 258, 962, 0, 215, 412,
    5000, 0, 65546, 5000, 65546, 2000, 131096, -70000000,
    0, 589915, (s32)evt_cam3d_evt_set, 0, 130, 840, 0, 50,
    397, 1500, 11, 32, 589915, (s32)evt_cam3d_evt_set, 0, 240,
    1187, 0, 170, 742, 1500, 11, 33, 107,
    327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 131126, -29999998,
    230, 262235, (s32)evt_mario_mov_pos2, -30000000, -29999998, -229918080, 109, 327771,
    (s32)evt_party_get_pos, 0, -30000000, -29999999, -29999998, 131126, -29999998, 230,
    327771, (s32)evt_party_move_pos2, 0, -30000000, -29999998, -229918080, 131122, -29999999,
    2, 65628, (s32)bero_close_door_play_se, 327771, (s32)evt_sub_intpl_msec_init, 11, 180, 0,
    500, 65539, 1, 65627, (s32)evt_sub_intpl_msec_get_value, 131096, -70000000, 0,
    65630, (s32)s1_door_close, 32, 65630, (s32)s2_door_close, 33, 131096, -29999999,
    1, 65540, 1, 33, 327771, (s32)evt_sub_intpl_msec_init, 2, 0,
    180, 500, 65539, 2, 65627, (s32)evt_sub_intpl_msec_get_value, 131096, -70000000,
    0, 65630, (s32)s1_door_open2, 32, 65630, (s32)s2_door_open2, 33, 131096,
    -29999999, 1, 65540, 2, 33, 107, 262235, (s32)evt_mario_set_dir,
    90, 300, 0, 109, 262235, (s32)evt_party_set_dir, 0, 270,
    -1, 65546, 500, 131163, (s32)evt_msg_print_party, (s32)((char*)str_0000019C), 65546, 300,
    131163, (s32)evt_mario_set_dir_npc, (s32)/*"チャンピョン"*/(char*)str_0000016C, 65546, 1000, 589915, (s32)evt_cam3d_evt_set, 85,
    172, 326, 85, 96, -104, 0, 11, 65545,
    1, 327771, (s32)evt_msg_print, 0, (s32)((char*)str_000001A8), 0, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), 65546,
    300, 589915, (s32)evt_cam3d_evt_set, -85, 172, 326, -85, 96,
    -104, 1000, 11, 327771, (s32)evt_npc_get_position, (s32)/*"チャンピョン"*/(char*)str_0000016C, -29999990, -29999989,
    -29999988, 262235, (s32)evt_npc_status_onoff, 1, (s32)/*"チャンピョン"*/(char*)str_0000016C, 2, 327771, (s32)evt_npc_get_position,
    (s32)/*"チャンピョン"*/(char*)str_0000016C, -30000000, -29999999, -29999998, 131126, -30000000, 50, 458843,
    (s32)evt_npc_move_position, (s32)/*"チャンピョン"*/(char*)str_0000016C, -30000000, -29999998, 0, -229897600, 1, 327771,
    (s32)evt_npc_set_rotate, (s32)/*"チャンピョン"*/(char*)str_0000016C, 0, 0, -30, 327771, (s32)evt_npc_get_position, (s32)/*"相手"*/(char*)str_0000017C,
    -30000000, -29999999, -29999998, 131125, -29999999, 20, 458843, (s32)evt_npc_jump_position_nohit,
    (s32)/*"チャンピョン"*/(char*)str_0000016C, -30000000, -29999999, -29999998, 700, -229959040, 393307, (s32)evt_snd_sfxon_3d,
    (s32)((char*)str_000001B4), -30000000, -29999999, -29999998, 0, 983131, (s32)evt_eff, 0,
    (s32)((char*)str_000001CC), 0, -30000000, -29999999, -29999998, -229996928, 10, 0,
    0, 0, 0, 0, 0, 107, 327771, (s32)evt_cam_shake,
    4, -229999990, -230000000, 300, 109, 107, 131122, -30000000,
    -30, 65541, 10, 327771, (s32)evt_npc_set_rotate, (s32)/*"チャンピョン"*/(char*)str_0000016C, 0, 0,
    -30000000, 131125, -30000000, 3, 65545, 1, 6, 327771,
    (s32)evt_npc_set_rotate, (s32)/*"チャンピョン"*/(char*)str_0000016C, 0, 0, 0, 109, 107, 458843,
    (s32)evt_npc_sound_data_set, (s32)/*"チャンピョン"*/(char*)str_0000016C, -250000000, -250000000, -250000000, 0, 0, 131125,
    -30000000, 30, 131126, -29999999, 20, 458843, (s32)evt_npc_jump_position_nohit, (s32)/*"チャンピョン"*/(char*)str_0000016C,
    -30000000, -29999999, -29999998, 300, -229979520, 131125, -30000000, 30,
    458843, (s32)evt_npc_jump_position_nohit, (s32)/*"チャンピョン"*/(char*)str_0000016C, -30000000, -29999999, -29999998, 300, -229989760,
    458843, (s32)evt_npc_jump_position_nohit, (s32)/*"チャンピョン"*/(char*)str_0000016C, -29999990, -29999989, -29999988, 300, -229989760,
    131163, (s32)evt_npc_sound_data_reset, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), 109, 196699, (s32)evt_npc_set_anim, (s32)/*((char*)str_0000017C)*/((char*)str_0000017C), (s32)((char*)str_000001D0),
    107, 327771, (s32)evt_npc_get_position, (s32)/*"相手"*/(char*)str_0000017C, -30000000, -29999999, -29999998, 131126,
    -30000000, 30, 458843, (s32)evt_npc_jump_position_nohit, (s32)/*"相手"*/(char*)str_0000017C, -30000000, -29999999, -29999998,
    300, -229979520, 131126, -30000000, 30, 458843, (s32)evt_npc_jump_position_nohit, (s32)/*"相手"*/(char*)str_0000017C,
    -30000000, -29999999, -29999998, 300, -229989760, 109, 327771, (s32)evt_msg_print,
    0, (s32)((char*)str_000001D4), 0, (s32)/*((char*)str_0000017C)*/((char*)str_0000017C), 589915, (s32)evt_cam3d_evt_set, 65, 172,
    326, 65, 96, -104, 1000, 11, 131122, -90000000,
    0, 107, 262235, (s32)evt_npc_status_onoff, 1, (s32)/*"ガンス"*/(char*)str_000001E0, 2, 327771,
    (s32)evt_npc_set_position, (s32)/*"ガンス"*/(char*)str_000001E0, 160, 60, -65, 458843, (s32)evt_npc_move_position, (s32)/*"ガンス"*/(char*)str_000001E0,
    45, -65, 0, -229948800, 1, 458843, (s32)evt_npc_move_position, (s32)/*"ガンス"*/(char*)str_000001E0,
    20, 0, 0, -229948800, 1, 196699, (s32)evt_set_dir_to_target, (s32)/*"ガンス"*/(char*)str_000001E0,
    (s32)/*"チャンピョン"*/(char*)str_0000016C, 131122, -90000000, 1, 109, 65546, 1200, 196699,
    (s32)evt_npc_set_anim, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), (s32)((char*)str_000001E8), 262235, (s32)evt_npc_set_autotalkpose, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), (s32)((char*)str_000001E8), (s32)((char*)str_000001EC),
    327771, (s32)evt_msg_print, 0, (s32)((char*)str_000001F0), 0, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), 65546, 300,
    65541, 0, 131096, -90000000, 1, 7, 33, 65545,
    1, 6, 327771, (s32)evt_msg_print, 0, (s32)((char*)str_000001FC), 0, (s32)/*((char*)str_000001E0)*/((char*)str_000001E0),
    65546, 300, 196699, (s32)evt_npc_set_anim, (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), (s32)((char*)str_00000208), 65546, 300,
    196699, (s32)evt_npc_set_anim, (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), (s32)((char*)str_0000020C), 327771, (s32)evt_msg_print, 0, (s32)((char*)str_00000210),
    0, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), 196699, (s32)evt_npc_set_anim, (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), (s32)((char*)str_0000021C), 65546, 300,
    196699, (s32)evt_npc_set_anim, (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), (s32)((char*)str_00000220), 196699, (s32)evt_npc_set_anim, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), (s32)((char*)str_00000224),
    262235, (s32)evt_npc_set_autotalkpose, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), (s32)((char*)str_00000220), (s32)((char*)str_00000228), 65627, (s32)evt_msg_continue, 65546,
    1500, 196699, (s32)evt_npc_set_anim, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), (s32)((char*)str_0000022C), 65546, 200, 196699,
    (s32)evt_npc_set_anim, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), (s32)((char*)str_00000230), 196699, (s32)evt_npc_entry, (s32)/*((char*)str_00000234)*/((char*)str_00000234), (s32)((char*)str_0000023C), 327771,
    (s32)evt_npc_get_position, (s32)/*"チャンピョン"*/(char*)str_0000016C, -30000000, -29999999, -29999998, 131126, -30000000, 5,
    131125, -29999999, 65, 327771, (s32)evt_npc_set_position, (s32)/*"ベルト"*/(char*)str_00000234, -30000000, -29999999,
    -29999998, 196699, (s32)evt_npc_set_anim, (s32)/*((char*)str_00000234)*/((char*)str_00000234), (s32)((char*)str_00000248), 131125, -29999998, 10,
    983131, (s32)evt_eff, 0, (s32)((char*)str_0000024C), 9, -30000000, -29999999, -29999998,
    -229999232, 0, 0, 0, 0, 0, 0, 0,
    393307, (s32)evt_snd_sfxon_3d, (s32)((char*)str_00000258), -30000000, -29999999, -29999998, 0, 65546,
    2000, 131096, -70000000, 0, 589915, (s32)evt_cam3d_evt_set, 0, 95,
    692, 0, 43, 397, 0, 11, 32, 589915,
    (s32)evt_cam3d_evt_set, 0, 218, 1037, 0, 165, 742, 0,
    11, 33, 65545, 1, 131163, (s32)evt_mario_set_dir_npc, (s32)/*"チャンピョン"*/(char*)str_0000016C, 196699,
    (s32)evt_party_set_dir_npc, 0, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), 786523, (s32)evt_eff_fukidashi, 3, (s32)((char*)str_00000270), 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    65546, 1000, 131163, (s32)evt_msg_print_party, (s32)((char*)str_00000274), 65546, 300, 589915,
    (s32)evt_cam3d_evt_set, 80, 67, 225, 80, 172, -161, 0,
    11, 65545, 1, 65546, 1000, 327771, (s32)evt_msg_toge, 1,
    0, 0, 0, 131163, (s32)evt_msg_print_party, (s32)((char*)str_00000280), 65546, 300,
    393307, (s32)evt_fade_set_mapchange_type, 0, 2, 500, 1, 500, 131122,
    -129997626, 1, 131096, -70000000, 0, 196699, (s32)evt_bero_mapchange, (s32)((char*)str_00000164),
    (s32)((char*)str_0000014C), 32, 196699, (s32)evt_bero_mapchange, (s32)((char*)str_00000164), (s32)((char*)str_00000138), 33, 2,
    1,
};

EVT_BEGIN(init_kinosikowa)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 172)
        CALL(evt_npc_set_tribe, STRING(((char*)str_0000028C)), STRING(((char*)str_00000298)))
        CALL(evt_npc_set_stay_anim, STRING(((char*)str_0000028C)))
    END_IF
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"ガンス"*/(char*)str_000001E0, 1073743360, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"キノシコワ"*/(char*)str_0000028C,
    1073743360, 0, (s32)init_kinosikowa, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"マッチョガンス"*/(char*)str_000002B0, 1073743360,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"キノシチョフ"*/(char*)str_000002C0, 1073743360, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

EVT_BEGIN(evt_damage_pose)
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_set_pose, STRING(((char*)str_000002D0)))
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_000002D8)))
        CASE_EQUAL(2)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_000002E0)))
        CASE_EQUAL(3)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_000002E8)))
        CASE_EQUAL(4)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_000002EC)))
        CASE_EQUAL(5)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_000002F4)))
        CASE_EQUAL(6)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_000002FC)))
        CASE_EQUAL(7)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000304)))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(evt_kime_pose)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_0000030C)))
        CASE_EQUAL(2)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000314)))
        CASE_EQUAL(3)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_0000031C)))
        CASE_EQUAL(4)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000320)))
        CASE_EQUAL(5)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000328)))
        CASE_EQUAL(6)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000330)))
        CASE_EQUAL(7)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000338)))
    END_SWITCH
    RETURN
EVT_END()

s32 npc_entry[] = {
    131098, -170000000, 128, 196699, (s32)evt_npc_entry, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), (s32)((char*)str_0000023C), 327771,
    (s32)evt_npc_set_position, (s32)/*"チャンピョン"*/(char*)str_0000016C, 80, 60, 0, 196699, (s32)evt_npc_entry, (s32)/*"相手"*/(char*)str_0000017C,
    (s32)((char*)str_00000340), 327771, (s32)evt_npc_set_position, (s32)/*((char*)str_0000017C)*/((char*)str_0000017C), -80, 60, 0, 196699,
    (s32)evt_npc_set_tribe, (s32)/*"チャンピョン"*/(char*)str_0000016C, (s32)/*"ブレッドハート"*/(char*)str_00000350, 196699, (s32)evt_npc_set_tribe, (s32)/*"相手"*/(char*)str_0000017C, (s32)/*"トゲノコエース"*/(char*)str_00000360, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)/*"チャンピョン"*/(char*)str_0000016C, 1073743360, 262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"相手"*/(char*)str_0000017C,
    1073741824, 196699, (s32)evt_npc_set_ry, (s32)/*"チャンピョン"*/(char*)str_0000016C, 270, 196699, (s32)evt_npc_set_ry, (s32)/*"相手"*/(char*)str_0000017C,
    90, 2, 33, 131122, -70000000, 0, 65570, -170000000,
    131119, 128, 162, 131122, -70000000, 1, 65574, 164,
    42, 131122, -70000000, 1, 49, 131096, -70000000, 1,
    131096, -129997612, 0, 196699, (s32)evt_sub_random, 10000, -29999990, 131098,
    -29999990, 5000, 65541, 0, 196699, (s32)evt_sub_random, 3000, -29999990,
    65570, -29999990, 65574, 1000, 131122, -30000000, (s32)((char*)str_00000370), 131122,
    -29999999, (s32)/*((char*)str_0000037C)*/((char*)str_0000037C), 65574, 2000, 131122, -30000000, (s32)((char*)str_00000384), 131122,
    -29999999, (s32)/*((char*)str_00000390)*/((char*)str_00000390), 42, 131122, -30000000, (s32)((char*)str_0000039C), 131122, -29999999,
    (s32)/*"モノクロクロクモーン"*/(char*)str_000003A8, 49, 196699, (s32)evt_sub_random, 3000, -29999990, 65570, -29999990,
    65574, 1000, 131122, -29999998, (s32)((char*)str_00000370), 131122, -29999997, (s32)/*((char*)str_0000037C)*/((char*)str_0000037C),
    65574, 2000, 131122, -29999998, (s32)((char*)str_00000384), 131122, -29999997, (s32)/*((char*)str_00000390)*/((char*)str_00000390),
    42, 131122, -29999998, (s32)((char*)str_0000039C), 131122, -29999997, (s32)/*((char*)str_000003A8)*/((char*)str_000003A8), 49,
    131085, -30000000, -29999998, 7, 33, 6, 32, 65541,
    0, 196699, (s32)evt_sub_random, 4000, -29999990, 65570, -29999990, 65574,
    1000, 131122, -30000000, (s32)((char*)str_000003C0), 131122, -29999999, (s32)/*((char*)str_000003CC)*/((char*)str_000003CC), 65574,
    2000, 131122, -30000000, (s32)((char*)str_000003D8), 131122, -29999999, (s32)/*((char*)str_000003E4)*/((char*)str_000003E4), 65574,
    3000, 131122, -30000000, (s32)((char*)str_000003F4), 131122, -29999999, (s32)/*((char*)str_00000404)*/((char*)str_00000404), 42,
    131122, -30000000, (s32)((char*)str_00000414), 131122, -29999999, (s32)/*((char*)str_00000420)*/((char*)str_00000420), 49, 196699,
    (s32)evt_sub_random, 4000, -29999990, 65570, -29999990, 65574, 1000, 131122,
    -29999998, (s32)((char*)str_000003C0), 131122, -29999997, (s32)/*((char*)str_000003CC)*/((char*)str_000003CC), 65574, 2000, 131122,
    -29999998, (s32)((char*)str_000003D8), 131122, -29999997, (s32)/*((char*)str_000003E4)*/((char*)str_000003E4), 65574, 3000, 131122,
    -29999998, (s32)((char*)str_000003F4), 131122, -29999997, (s32)/*((char*)str_00000404)*/((char*)str_00000404), 42, 131122, -29999998,
    (s32)((char*)str_00000414), 131122, -29999997, (s32)/*((char*)str_00000420)*/((char*)str_00000420), 49, 131085, -30000000, -29999998,
    7, 33, 6, 33, 196699, (s32)evt_npc_entry, (s32)/*"選手1"*/(char*)str_00000434, -30000000,
    327771, (s32)evt_npc_set_position, (s32)/*"選手1"*/(char*)str_00000434, -80, 60, 0, 196699, (s32)evt_npc_entry,
    (s32)/*"選手2"*/(char*)str_0000043C, -29999998, 327771, (s32)evt_npc_set_position, (s32)/*"選手2"*/(char*)str_0000043C, 80, 60, 0,
    196699, (s32)evt_npc_set_tribe, (s32)/*"選手1"*/(char*)str_00000434, -29999999, 196699, (s32)evt_npc_set_tribe, (s32)/*"選手2"*/(char*)str_0000043C, -29999997,
    262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"選手1"*/(char*)str_00000434, 1073743392, 262235, (s32)evt_npc_flag_onoff, 1,
    (s32)/*"選手2"*/(char*)str_0000043C, 1073743392, 196699, (s32)evt_npc_set_ry, (s32)/*"選手1"*/(char*)str_00000434, 90, 196699, (s32)evt_npc_set_ry,
    (s32)/*"選手2"*/(char*)str_0000043C, 270, 131084, -29999999, (s32)/*"バーストワンワン"*/(char*)str_00000420, 196699, (s32)evt_npc_set_anim, (s32)/*"選手1"*/(char*)str_00000434,
    (s32)((char*)str_00000444), 131122, -30000000, 6, 65628, (s32)burst_chain_entry, 33, 131084,
    -29999997, (s32)/*((char*)str_00000420)*/((char*)str_00000420), 196699, (s32)evt_npc_set_anim, (s32)/*((char*)str_00000434)*/((char*)str_00000434), (s32)((char*)str_00000444), 131122, -30000000,
    7, 65628, (s32)burst_chain_entry, 33, 2, 33, 33, 131096,
    -129997612, 1, 196699, (s32)evt_tou_get_fighter_num, -169999499, -30000000, 131122, -29999999,
    0, 65541, 0, 131096, -30000000, -29999999, 7, 33,
    131096, -169999499, 11, 65570, -29999999, 65572, 0, 131122,
    -29999998, (s32)/*"敵３"*/(char*)str_0000044C, 65572, 1, 131122, -29999998, (s32)/*"敵４"*/(char*)str_00000454, 65572,
    2, 131122, -29999998, (s32)/*"敵１"*/(char*)str_0000045C, 65572, 3, 131122, -29999998,
    (s32)/*"敵２"*/(char*)str_00000464, 65572, 4, 131122, -29999998, (s32)/*"敵５"*/(char*)str_0000046C, 42, 65649,
    (s32)/*"おかしい"*/(char*)str_00000474, 7, 49, 32, 65570, -29999999, 65572, 0,
    131122, -29999998, (s32)/*"敵１"*/(char*)str_0000045C, 65572, 1, 131122, -29999998, (s32)/*"敵２"*/(char*)str_00000464,
    65572, 2, 131122, -29999998, (s32)/*"敵３"*/(char*)str_0000044C, 65572, 3, 131122,
    -29999998, (s32)/*"敵４"*/(char*)str_00000454, 65572, 4, 131122, -29999998, (s32)/*"敵５"*/(char*)str_0000046C, 42,
    65649, (s32)/*"おかしい"*/(char*)str_00000474, 7, 49, 33, 327771, (s32)evt_tou_get_fighter_tribe, -169999499,
    -29999999, -29999997, -29999996, 196699, (s32)evt_npc_entry, -29999998, -29999997, 196699,
    (s32)evt_npc_set_tribe, -29999998, -29999996, 327771, (s32)evt_npc_set_position, -29999998, 0, -1000,
    0, 262235, (s32)evt_npc_flag_onoff, 1, -29999998, 1073743360, 196699, (s32)evt_npc_set_ry,
    -29999998, 270, 107, 196699, (s32)evt_npc_get_height, -29999998, -30000000, 131099,
    -30000000, 50, 196699, (s32)evt_npc_set_height, -29999998, 50, 33, 109,
    107, 131096, -169999499, 2, 65570, -29999999, 65572, 0,
    131122, -30000000, 0, 65628, (s32)burst_chain_entry, 65572, 1, 131122,
    -30000000, 1, 65628, (s32)burst_chain_entry, 49, 33, 109, 131125,
    -29999999, 1, 6, 262235, (s32)evt_tou_get_fighter_info_28_text_3E58, -169999499, -30000000, -29999999,
    131096, -29999999, 10, 327771, (s32)evt_npc_set_scale, (s32)/*"敵１"*/(char*)str_0000045C, -229998464, -229998464,
    -229998976, 327771, (s32)evt_npc_set_scale, (s32)/*"敵２"*/(char*)str_00000464, -229998464, -229998464, -229998976, 458843,
    (s32)evt_npc_sound_data_set, (s32)/*((char*)str_0000045C)*/((char*)str_0000045C), (s32)((char*)str_00000480), (s32)((char*)str_00000498), -250000000, -250000000, -250000000, 458843,
    (s32)evt_npc_sound_data_set, (s32)/*((char*)str_00000464)*/((char*)str_00000464), (s32)((char*)str_00000480), (s32)((char*)str_00000498), -250000000, -250000000, -250000000, 33,
    131122, -70000000, 0, 131163, (s32)evt_tou_get_ranking_28_text_4048, -30000000, 131096, -30000000,
    6, 196699, (s32)evt_npc_entry, (s32)/*((char*)str_000004B0)*/((char*)str_000004B0), (s32)((char*)str_000004B4), 327771, (s32)evt_npc_set_position, (s32)/*((char*)str_000004B0)*/((char*)str_000004B0),
    0, -1000, 0, 196699, (s32)evt_npc_set_tribe, (s32)/*"乱"*/(char*)str_000004B0, (s32)/*"クッパ"*/(char*)str_000004BC, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)/*"乱"*/(char*)str_000004B0, 1073743360, 196699, (s32)evt_npc_set_ry, (s32)/*"乱"*/(char*)str_000004B0, 270,
    458843, (s32)evt_npc_sound_data_set, (s32)/*((char*)str_000004B0)*/((char*)str_000004B0), (s32)((char*)str_000004C4), (s32)((char*)str_000004DC), 12000, (s32)((char*)str_000004F4), -250000000,
    32, 196699, (s32)evt_npc_entry, (s32)/*((char*)str_000004B0)*/((char*)str_000004B0), (s32)((char*)str_0000050C), 327771, (s32)evt_npc_set_position, (s32)/*((char*)str_000004B0)*/((char*)str_000004B0),
    0, -1000, 0, 196699, (s32)evt_npc_set_tribe, (s32)/*"乱"*/(char*)str_000004B0, (s32)/*"アイアンシンエモン"*/(char*)str_00000518, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)/*"乱"*/(char*)str_000004B0, 1073743360, 196699, (s32)evt_npc_set_ry, (s32)/*"乱"*/(char*)str_000004B0, 270,
    327771, (s32)evt_npc_set_scale, (s32)/*"乱"*/(char*)str_000004B0, -229998464, -229998464, -229998976, 458843, (s32)evt_npc_sound_data_set,
    (s32)/*((char*)str_000004B0)*/((char*)str_000004B0), (s32)((char*)str_00000480), (s32)((char*)str_00000498), -250000000, -250000000, -250000000, 196699, (s32)evt_npc_entry,
    (s32)/*((char*)str_0000052C)*/((char*)str_0000052C), (s32)((char*)str_00000534), 327771, (s32)evt_npc_set_position, (s32)/*((char*)str_0000052C)*/((char*)str_0000052C), 0, -1000, 0,
    196699, (s32)evt_npc_set_tribe, (s32)/*"乱２"*/(char*)str_0000052C, (s32)/*"アイアンシンエモン2"*/(char*)str_00000540, 262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"乱２"*/(char*)str_0000052C,
    1073743360, 196699, (s32)evt_npc_set_ry, (s32)/*"乱２"*/(char*)str_0000052C, 270, 327771, (s32)evt_npc_set_scale, (s32)/*"乱２"*/(char*)str_0000052C,
    -229998464, -229998464, -229998976, 458843, (s32)evt_npc_sound_data_set, (s32)/*((char*)str_0000052C)*/((char*)str_0000052C), (s32)((char*)str_00000480), (s32)((char*)str_00000498),
    -250000000, -250000000, -250000000, 33, 33, 2, 1,
};

EVT_BEGIN(evt_random_battle)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000554)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)str_0000056C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    CALL(evt_npc_set_position, STRING(((char*)str_000004B0)), 370, 0, 210)
    CALL(evt_npc_set_position, STRING(((char*)str_0000052C)), 390, 0, 235)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000570)), 0, STRING(((char*)str_000004B0)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 300, 134, 732, 300, 38, 190, 1000, 11)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)str_0000052C)), 290, 235, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000052C)), 200, 60, 192, 500, 30)
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING(((char*)str_000004B0)), 270, 210, 0, FLOAT(80.0f), 1)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000004B0)), 180, 60, 167, 500, 30)
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_set_pose, STRING(((char*)str_00000580)))
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)str_0000052C)), 75, 75, 0, FLOAT(80.0f), 1)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)str_000004B0)), 55, 50, 0, FLOAT(80.0f), 1)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 180, 517, 0, 95, -145, 0, 11)
    WAIT_FRAMES(1)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_cam3d_evt_set, 0, 130, 62, 0, 115, -22, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000588)), 0, STRING(((char*)str_000001E0)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 40, 155, 320, 40, 96, -8, 0, 0)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000598)), 0, STRING(((char*)str_000004B0)))
    WAIT_MS(300)
    CALL(evt_snd_sfxon, STRING(((char*)str_000005A8)), 0)
    WAIT_MS(500)
    CALL(evt_npc_set_battle_info, STRING(((char*)str_000004B0)), 10)
    CALL(evt_npc_battle_start, STRING(((char*)str_000004B0)))
    CALL(evt_npc_wait_battle_end)
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_mario_set_pose, STRING(((char*)str_000005B8)))
    CALL(evt_npc_check, STRING(((char*)str_0000045C)), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 0, -1000, 0)
    END_IF
    CALL(evt_npc_check, STRING(((char*)str_00000464)), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 0, -1000, 0)
    END_IF
    CALL(evt_npc_check, STRING(((char*)str_0000044C)), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_npc_set_position, STRING(((char*)str_0000044C)), 0, -1000, 0)
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), -50)
    ADD(LW(2), -20)
    CALL(evt_party_set_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_battle_result, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_npc_set_anim, STRING(((char*)str_000004B0)), STRING(((char*)str_000005C0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_0000052C)), STRING(((char*)str_000005C0)))
        CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_000004B0)), 1536)
        CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_0000052C)), 1536)
        CALL(evt_msg_print, 0, STRING(((char*)str_000005C8)), 0, STRING(((char*)str_000004B0)))
        WAIT_MS(300)
        CALL(evt_msg_print, 0, STRING(((char*)str_000005D8)), 0, STRING(((char*)str_000001E0)))
        WAIT_MS(300)
        ELSE
        CALL_CHILD(PTR(evt_damage_pose))
        CALL(evt_msg_print, 0, STRING(((char*)str_000005E8)), 0, STRING(((char*)str_000004B0)))
        WAIT_MS(300)
        CALL(evt_msg_print, 0, STRING(((char*)str_000005F8)), 0, STRING(((char*)str_000001E0)))
        WAIT_MS(300)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_random_battle2)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000554)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)str_0000056C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    CALL(evt_npc_set_position, STRING(((char*)str_000004B0)), 370, 0, 210)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000608)), 0, STRING(((char*)str_000004B0)))
    WAIT_MS(300)
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000618)))
    CALL(evt_cam3d_evt_set, 300, 134, 732, 300, 38, 190, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_npc_move_position, STRING(((char*)str_000004B0)), 270, 210, 0, FLOAT(80.0f), 1)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000004B0)), 180, 60, 167, 500, 30)
    BEGIN_INLINE_EVENT
        CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.029296875f), 500)
    END_INLINE_EVENT
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_set_pose, STRING(((char*)str_00000580)))
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)str_000004B0)), 55, 50, 0, FLOAT(80.0f), 1)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 180, 517, 0, 95, -145, 0, 11)
    WAIT_FRAMES(1)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_cam3d_evt_set, 0, 130, 62, 0, 115, -22, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000628)), 0, STRING(((char*)str_000001E0)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 15, 189, 396, 15, 116, -8, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000638)), 0, STRING(((char*)str_000004B0)))
    WAIT_MS(300)
    CALL(evt_snd_sfxon, STRING(((char*)str_000005A8)), 0)
    WAIT_MS(500)
    CALL(evt_npc_set_battle_info, STRING(((char*)str_000004B0)), 24)
    CALL(evt_npc_battle_start, STRING(((char*)str_000004B0)))
    CALL(evt_npc_wait_battle_end)
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_mario_set_pose, STRING(((char*)str_000005B8)))
    CALL(evt_npc_check, STRING(((char*)str_0000045C)), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 0, -1000, 0)
    END_IF
    CALL(evt_npc_check, STRING(((char*)str_00000464)), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 0, -1000, 0)
    END_IF
    CALL(evt_npc_check, STRING(((char*)str_0000044C)), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_npc_set_position, STRING(((char*)str_0000044C)), 0, -1000, 0)
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), -50)
    ADD(LW(2), -20)
    CALL(evt_party_set_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_battle_result, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_npc_set_anim, STRING(((char*)str_000004B0)), STRING(((char*)str_00000648)))
        CALL(evt_npc_set_autotalkpose, STRING(((char*)str_000004B0)), STRING(((char*)str_00000648)), STRING(((char*)str_00000650)))
        CALL(evt_msg_print, 0, STRING(((char*)str_00000658)), 0, STRING(((char*)str_000004B0)))
        WAIT_MS(300)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000668)), 0, STRING(((char*)str_000001E0)))
        WAIT_MS(300)
        ELSE
        CALL_CHILD(PTR(evt_damage_pose))
        CALL(evt_msg_print, 0, STRING(((char*)str_00000678)), 0, STRING(((char*)str_000004B0)))
        WAIT_MS(300)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000688)), 0, STRING(((char*)str_000001E0)))
        WAIT_MS(300)
    END_IF
    SET_VALUE(LW(0), GSW(0))
    SET_VALUE(GSW(0), 178)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    SET_VALUE(GSW(0), LW(0))
    RETURN
EVT_END()

EVT_BEGIN(evt_teki_nyuujyou)
    SWITCH(LW(1))
        CASE_EQUAL(0)
        SET_VALUE(LW(3), 70)
        SET_VALUE(LW(4), 0)
        CASE_EQUAL(1)
        SET_VALUE(LW(3), 40)
        SET_VALUE(LW(4), 25)
        CASE_EQUAL(2)
        SET_VALUE(LW(3), 20)
        SET_VALUE(LW(4), -25)
        CASE_EQUAL(3)
        SET_VALUE(LW(3), 60)
        SET_VALUE(LW(4), 0)
        CASE_EQUAL(4)
        SET_VALUE(LW(3), 80)
        SET_VALUE(LW(4), -25)
    END_SWITCH
    SET_VALUE(LW(5), 450)
    ADD(LW(5), LW(3))
    CALL(evt_npc_move_position, LW(0), LW(5), LW(4), 0, FLOAT(60.0f), 1)
    WAIT_MS(1000)
    CALL(evt_npc_move_position, LW(0), 280, LW(4), 0, FLOAT(60.0f), 1)
    CALL(evt_npc_jump_position_nohit, LW(0), 250, 20, LW(4), 500, 30)
    CALL(evt_npc_jump_position_nohit, LW(0), 215, 40, LW(4), 500, 30)
    CALL(evt_npc_jump_position_nohit, LW(0), 185, 60, LW(4), 500, 30)
    SET_VALUE(LW(5), 50)
    ADD(LW(5), LW(3))
    CALL(evt_npc_move_position, LW(0), LW(5), LW(4), 0, FLOAT(60.0f), 1)
    RETURN
EVT_END()

s32 evt_teki_nyuujyou_default[] = {
    65570, -29999999, 65572, 0, 131096, -29999998, 1, 131122,
    -29999997, 70, 131122, -29999996, 0, 32, 131122, -29999997,
    50, 131122, -29999996, 0, 33, 65572, 1, 131122,
    -29999997, 90, 131122, -29999996, 25, 65572, 2, 131122,
    -29999997, 70, 131122, -29999996, -25, 65572, 3, 131122,
    -29999997, 110, 131122, -29999996, 0, 65572, 4, 131122,
    -29999997, 130, 131122, -29999996, -25, 49, 262235, (s32)tribe_chk,
    -30000000, (s32)/*"カメック緑空"*/(char*)str_00000698, -29999995, 131096, -29999995, 1, 327771, (s32)evt_npc_get_position,
    -30000000, -29999994, -29999993, -29999992, 131125, -29999993, 25, 327771,
    (s32)evt_npc_set_position, -30000000, -29999994, -29999993, -29999992, 458843, (s32)evt_npc_move_position, -30000000,
    280, -29999996, 0, -229938560, 1, 458843, (s32)evt_npc_jump_position_nohit, -30000000,
    250, 45, -29999996, 500, 30, 458843, (s32)evt_npc_jump_position_nohit, -30000000,
    215, 65, -29999996, 500, 30, 458843, (s32)evt_npc_jump_position_nohit, -30000000,
    185, 85, -29999996, 500, 30, 458843, (s32)evt_npc_move_position, -30000000,
    -29999997, -29999996, 0, -229938560, 1, 32, 458843, (s32)evt_npc_move_position,
    -30000000, 280, -29999996, 0, -229938560, 1, 458843, (s32)evt_npc_jump_position_nohit,
    -30000000, 250, 20, -29999996, 500, 30, 458843, (s32)evt_npc_jump_position_nohit,
    -30000000, 215, 40, -29999996, 500, 30, 458843, (s32)evt_npc_jump_position_nohit,
    -30000000, 185, 60, -29999996, 500, 30, 458843, (s32)evt_npc_sound_data_set,
    -30000000, 0, 0, -250000000, -250000000, -250000000, 458843, (s32)evt_npc_move_position,
    -30000000, -29999997, -29999996, 0, -229938560, 1, 131163, (s32)evt_npc_sound_data_reset,
    -30000000, 262235, (s32)tribe_chk, -30000000, (s32)/*"バーストワンワン"*/(char*)str_00000420, -29999995, 131096, -29999995,
    1, 65628, (s32)burst_wangwang, 33, 33, 2, 1,
};

EVT_BEGIN(burst_chain_entry)
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(evt_npc_entry, STRING(((char*)str_000006A8)), STRING(((char*)str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)str_000006B0)), STRING(((char*)str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)str_000006B8)), STRING(((char*)str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)str_000006C0)), STRING(((char*)str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)str_000006C8)), STRING(((char*)str_00000414)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006A8)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006B0)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006B8)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006C0)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006C8)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006A8)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006B0)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006B8)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006C0)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006C8)), 1074003968)
        CALL(burst_chain, STRING(((char*)str_0000045C)), 0)
        CASE_EQUAL(1)
        CALL(evt_npc_entry, STRING(((char*)str_000006DC)), STRING(((char*)str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)str_000006E4)), STRING(((char*)str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)str_000006EC)), STRING(((char*)str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)str_000006F4)), STRING(((char*)str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)str_000006FC)), STRING(((char*)str_00000414)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006DC)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006E4)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006EC)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006F4)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006FC)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006DC)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006E4)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006EC)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006F4)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006FC)), 1074003968)
        CALL(burst_chain, STRING(((char*)str_00000464)), 1)
        CASE_EQUAL(6)
        CALL(evt_npc_entry, STRING(((char*)str_000006A8)), STRING(((char*)str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)str_000006B0)), STRING(((char*)str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)str_000006B8)), STRING(((char*)str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)str_000006C0)), STRING(((char*)str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)str_000006C8)), STRING(((char*)str_00000414)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006A8)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006B0)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006B8)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006C0)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006C8)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006A8)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006B0)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006B8)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006C0)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006C8)), 1074003968)
        CALL(burst_chain, STRING(((char*)str_00000434)), 0)
        CASE_EQUAL(7)
        CALL(evt_npc_entry, STRING(((char*)str_000006DC)), STRING(((char*)str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)str_000006E4)), STRING(((char*)str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)str_000006EC)), STRING(((char*)str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)str_000006F4)), STRING(((char*)str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)str_000006FC)), STRING(((char*)str_00000414)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006DC)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006E4)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006EC)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006F4)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000006FC)), STRING(((char*)str_000006D0)))
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006DC)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006E4)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006EC)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006F4)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000006FC)), 1074003968)
        CALL(burst_chain, STRING(((char*)str_0000043C)), 1)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(burst_wangwang)
    SET_VALUE(LW(10), LW(0))
    CALL(evt_npc_get_position, LW(10), LW(0), LW(1), LW(2))
    LOOP(0)
        CALL(evt_sub_random, 360, LW(3))
        CALL(evt_sub_get_sincos, LW(3), LW(4), LW(5))
        MULTIPLY_FLOAT(LW(4), FLOAT(10.0f))
        MULTIPLY_FLOAT(LW(5), FLOAT(10.0f))
        ADD_FLOAT(LW(4), LW(0))
        ADD_FLOAT(LW(5), LW(2))
        CALL(evt_sub_random, 200, LW(6))
        ADD(LW(6), 300)
        CALL(evt_sub_random, 20, LW(7))
        ADD(LW(7), 20)
        CALL(evt_npc_flag_onoff, 0, LW(10), 1024)
        CALL(evt_npc_jump_position_nohit, LW(10), LW(4), LW(1), LW(5), LW(6), LW(7))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000704)), LW(4), LW(1), LW(5), 0)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_match)
    SWITCH(GSW(501))
        CASE_EQUAL(19)
        IF_INT_EQUAL(GSWF(2395), 0)
            SET_VALUE(GSWF(2395), 1)
            CALL_CHILD(PTR(evt_kurikuri_opening))
            ELSE
            CALL_CHILD(PTR(evt_default_opening))
        END_IF
        CASE_EQUAL(10)
        IF_INT_EQUAL(GSWF(2397), 0)
            SET_VALUE(GSWF(2397), 1)
            CALL_CHILD(PTR(evt_shinemon_opening))
            ELSE
            CALL_CHILD(PTR(evt_default_opening))
        END_IF
        CASE_EQUAL(0)
        IF_INT_EQUAL(GSWF(2399), 0)
            SET_VALUE(GSWF(2399), 1)
            IF_INT_LESS(GSW(0), 172)
                CALL_CHILD(PTR(evt_champ_opening))
                ELSE
                CALL_CHILD(PTR(evt_champ_opening_re))
            END_IF
            ELSE
            CALL_CHILD(PTR(evt_default_opening))
        END_IF
        CASE_DEFAULT
        CALL_CHILD(PTR(evt_default_opening))
    END_SWITCH
    CALL(evt_tou_get_fighter_info_28_text_3E58, GSW(501), LW(0), LW(1))
    IF_INT_EQUAL(GSWF(2509), 0)
        CALL(evt_npc_set_attack_mode, STRING(((char*)str_0000045C)), 16)
        CALL(_firstattack_setting)
    END_IF
    CALL(evt_npc_set_battle_info, STRING(((char*)str_0000045C)), LW(1))
    CALL(evt_npc_set_battle_rule, STRING(((char*)str_0000045C)), GSW(502), GSW(503), GSW(504))
    CALL(evt_npc_battle_start, STRING(((char*)str_0000045C)))
    CALL(evt_npc_wait_battle_end)
    CALL(evt_npc_get_battle_rule_keep_result, LW(0))
    CALL(evt_tou_set_rule_result_28_text_355C, LW(0))
    SET_VALUE(GSWF(2388), 0)
    SET_VALUE(GSWF(2389), 1)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), -50)
    ADD(LW(2), -20)
    CALL(evt_party_set_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_battle_result, LW(0))
    BEGIN_INLINE_EVENT
        IF_INT_LESS(GSW(0), 172)
            CALL(evt_npc_set_stay_anim, STRING(((char*)str_000001E0)))
            CALL(evt_npc_set_autotalkpose, STRING(((char*)str_000001E0)), STRING(((char*)str_00000220)), STRING(((char*)str_00000228)))
            ELSE
            CALL(evt_npc_set_stay_anim, STRING(((char*)str_0000028C)))
            CALL(evt_npc_set_autotalkpose, STRING(((char*)str_0000028C)), STRING(((char*)str_00000220)), STRING(((char*)str_00000228)))
        END_IF
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(0), 1)
        SWITCH(GSW(501))
            CASE_EQUAL(19)
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000720)))
            IF_INT_EQUAL(GSWF(2396), 0)
                SET_VALUE(GSWF(2396), 1)
                CALL_CHILD(PTR(evt_kurikuri_win))
                ELSE
                CALL_CHILD(PTR(evt_default_win))
            END_IF
            CASE_EQUAL(10)
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000720)))
            IF_INT_EQUAL(GSWF(2398), 0)
                SET_VALUE(GSWF(2398), 1)
                CALL_CHILD(PTR(evt_shinemon_win))
                ELSE
                CALL_CHILD(PTR(evt_default_win))
            END_IF
            CASE_EQUAL(0)
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000730)))
            IF_INT_EQUAL(GSWF(2400), 0)
                SET_VALUE(GSWF(2400), 1)
                CALL_CHILD(PTR(evt_champ_win))
                ELSE
                CALL_CHILD(PTR(evt_default_win))
            END_IF
            CASE_DEFAULT
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000720)))
            CALL_CHILD(PTR(evt_default_win))
        END_SWITCH
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        CALL(evt_tou_set_ranking_win_lose_28_text_35C0, 0, GSW(501))
        IF_INT_LESS(GSW(0), 172)
            IF_INT_GREATER_OR_EQUAL(GSW(0), 158)
                CALL(evt_tou_get_ranking_28_text_4048, LW(10))
                ELSE
                IF_INT_GREATER_OR_EQUAL(GSW(0), 138)
                    IF_INT_GREATER(LW(10), 1)
                        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
                    END_IF
                END_IF
            END_IF
            CALL(evt_tou_get_ranking_28_text_4048, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(7)
                IF_INT_EQUAL(GSWF(2417), 0)
                    CALL_CHILD(PTR(evt_random_battle))
                END_IF
                CASE_EQUAL(5)
                IF_INT_EQUAL(GSWF(2419), 0)
                    CALL_CHILD(PTR(evt_random_battle2))
                END_IF
            END_SWITCH
            ELSE
            IF_INT_EQUAL(LW(10), 1)
                IF_INT_EQUAL(GSW(501), 0)
                    SET_VALUE(LW(10), 0)
                END_IF
            END_IF
        END_IF
        ELSE
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000720)))
        SWITCH(GSW(501))
            CASE_EQUAL(19)
            CALL_CHILD(PTR(evt_kurikuri_lose))
            CASE_EQUAL(10)
            CALL_CHILD(PTR(evt_shinemon_lose))
            CASE_EQUAL(0)
            CALL_CHILD(PTR(evt_champ_lose))
            CASE_DEFAULT
            CALL_CHILD(PTR(evt_default_lose))
        END_SWITCH
        IF_INT_EQUAL(GSW(501), 10)
            IF_INT_LESS(GSW(505), 100)
                ADD(GSW(505), 1)
            END_IF
        END_IF
        CALL(evt_tou_set_ranking_win_lose_28_text_35C0, 1, GSW(501))
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
    END_IF
    IF_INT_LESS(GSW(0), 133)
        SET_VALUE(GSW(0), 133)
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(0), 172)
        SET_VALUE(GSWF(2383), 0)
    END_IF
    CALL(evt_fade_set_mapchange_type, 0, 2, 300, 1, 300)
    CALL(evt_snd_envoff, 512)
    CALL(snd_sfx_stop)
    SWITCH(LW(10))
        CASE_LESS(1)
        CALL(evt_bero_mapchange, STRING(((char*)str_00000740)), 0)
        CASE_LESS(11)
        CALL(evt_bero_mapchange, STRING(((char*)str_00000748)), 0)
        CASE_DEFAULT
        CALL(evt_bero_mapchange, STRING(((char*)str_00000750)), 0)
    END_SWITCH
    RETURN
EVT_END()

s32 evt_kurikuri_opening[] = {
    131163, (s32)evt_mario_key_onoff, 0, 262235, (s32)evt_npc_status_onoff, 1, (s32)/*"ガンス"*/(char*)str_000001E0, 2,
    327771, (s32)evt_npc_set_position, (s32)/*"ガンス"*/(char*)str_000001E0, 0, 60, -130, 327771, (s32)evt_npc_set_position,
    (s32)/*"敵１"*/(char*)str_0000045C, 50, 60, 0, 327771, (s32)evt_npc_set_position, (s32)/*"敵２"*/(char*)str_00000464, 90,
    60, 25, 327771, (s32)evt_npc_set_position, (s32)/*"敵３"*/(char*)str_0000044C, 70, 60, -25,
    327771, (s32)evt_npc_set_position, (s32)/*"敵４"*/(char*)str_00000454, 110, 60, 0, 327771, (s32)evt_npc_set_position,
    (s32)/*"敵５"*/(char*)str_0000046C, 130, 60, -25, 589915, (s32)evt_cam3d_evt_set, 1075, 547,
    998, 0, 287, -8, 0, 11, 131163, (s32)evt_seq_wait,
    2, 196699, (s32)evt_snd_bgmon, 512, (s32)((char*)str_00000758), 589915, (s32)evt_cam3d_evt_set, -1024,
    547, 1050, 0, 287, -8, 6000, 0, 65546,
    6000, 589915, (s32)evt_cam3d_evt_set, 0, 127, 105, 0, 95,
    -145, 0, 0, 327771, (s32)evt_msg_print, 0, (s32)((char*)str_00000768), 0,
    (s32)/*"ガンス"*/(char*)str_000001E0, 589915, (s32)evt_cam3d_evt_set, 70, 137, 260, 70, 96,
    -70, 2000, 0, 458843, (s32)evt_npc_move_position, (s32)/*"ガンス"*/(char*)str_000001E0, 10, -20,
    0, -229938560, 1, 327771, (s32)evt_msg_print, 0, (s32)((char*)str_00000774), 0,
    (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), 196699, (s32)evt_npc_set_anim, (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), (s32)((char*)str_00000208), 65546, 300, 196699,
    (s32)evt_npc_set_anim, (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), (s32)((char*)str_0000020C), 327771, (s32)evt_msg_print, 0, (s32)((char*)str_00000780), 0,
    (s32)/*((char*)str_00000464)*/((char*)str_00000464), 786523, (s32)evt_eff_fukidashi, 1, (s32)((char*)str_00000270), (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), 0, 0,
    0, 0, 0, 0, 0, 0, 196699, (s32)evt_npc_set_anim,
    (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), (s32)((char*)str_0000021C), 65546, 300, 196699, (s32)evt_npc_set_anim, (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), (s32)((char*)str_00000220),
    196699, (s32)evt_set_dir_to_target, (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), (s32)((char*)str_0000078C), 262235, (s32)evt_mario_set_pos, -550, 0,
    0, 327771, (s32)evt_party_set_pos, 0, -560, 0, -10, 131124,
    -30000000, -230184320, 65630, (s32)w_door_open, 196699, (s32)evt_cam3d_evt_off, 1000, 11,
    65546, 1000, 107, 65546, 1000, 393307, (s32)evt_snd_sfxon_3d, (s32)((char*)str_00000794),
    -565, 0, 0, 0, 327771, (s32)evt_sub_intpl_init, 11, -180,
    0, 20, 65541, 21, 65627, (s32)evt_sub_intpl_get_value, 65630, (s32)w_door_open,
    6, 109, 131122, -90000000, 0, 107, 65546, 1000,
    327771, (s32)evt_msg_print, 0, (s32)((char*)str_000007A8), 0, 0, 131122, -90000000,
    1, 109, 262235, (s32)evt_mario_mov_pos2, -450, 0, -229877120, 65546,
    1000, 107, 65546, 300, 327771, (s32)evt_party_move_pos2, 0, -280,
    25, -229877120, 65545, 1, 524379, (s32)evt_party_jump_pos, 0, -250,
    20, 25, 400, 1, -1000, 65545, 1, 524379,
    (s32)evt_party_jump_pos, 0, -215, 40, 25, 400, 1, -1000,
    65545, 1, 524379, (s32)evt_party_jump_pos, 0, -185, 60, 25,
    400, 1, -1000, 65545, 1, 327771, (s32)evt_party_move_pos2, 0,
    -90, -25, -229877120, 109, 262235, (s32)evt_mario_mov_pos2, -280, 0,
    -229877120, 327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 393307,
    (s32)evt_snd_sfxon_3d, (s32)((char*)str_000007B4), -30000000, -29999999, -29999998, 0, 458843, (s32)evt_mario_jump_pos,
    -250, 20, 0, 400, 1, -1000, 327771, (s32)evt_mario_get_pos,
    0, -30000000, -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)((char*)str_000007D0), -30000000,
    -29999999, -29999998, 0, 458843, (s32)evt_mario_jump_pos, -215, 40, 0,
    400, 1, -1000, 327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999,
    -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)((char*)str_000007EC), -30000000, -29999999, -29999998, 0,
    458843, (s32)evt_mario_jump_pos, -185, 60, 0, 400, 1, -1000,
    262235, (s32)evt_mario_mov_pos2, -55, 0, -229877120, 65541, 0, 131096,
    -90000000, 1, 7, 33, 65545, 1, 6, 458843,
    (s32)evt_npc_move_position, (s32)/*"ガンス"*/(char*)str_000001E0, -20, -20, 0, -229938560, 1, 327771,
    (s32)evt_msg_print, 0, (s32)((char*)str_00000808), 0, (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), 107, 327771, (s32)evt_msg_print,
    0, (s32)((char*)str_00000814), 0, (s32)/*((char*)str_0000045C)*/((char*)str_0000045C), 109, 458843, (s32)evt_npc_move_position, (s32)/*((char*)str_0000045C)*/((char*)str_0000045C),
    0, 0, 0, -229897600, 1, 327771, (s32)evt_mario_get_pos, 0,
    -30000000, -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)((char*)str_00000820), -30000000, -29999999,
    -29999998, 0, 131163, (s32)evt_mario_set_pose, (s32)((char*)str_0000083C), 107, 131124, -30000000,
    -230000000, 65541, 10, 131130, -30000000, -229986176, 327771, (s32)evt_npc_set_rotate,
    (s32)/*"敵１"*/(char*)str_0000045C, 0, 0, -30000000, 65545, 1, 6, 109,
    458843, (s32)evt_npc_sound_data_set, (s32)/*((char*)str_0000045C)*/((char*)str_0000045C), -250000000, -250000000, -250000000, (s32)((char*)str_00000844), -250000000,
    458843, (s32)evt_npc_jump_position_nohit, (s32)/*"敵１"*/(char*)str_0000045C, -30, 100, 0, 800, 100,
    2, 1,
};

EVT_BEGIN(evt_kurikuri_win)
    CALL(evt_cam3d_evt_set, 70, 138, 263, 70, 90, -8, 0, 11)
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 50, 60, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 90, 80, 25)
    CALL(evt_npc_set_position, STRING(((char*)str_0000044C)), 70, 60, -25)
    CALL(evt_npc_set_position, STRING(((char*)str_00000454)), 110, 60, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_0000046C)), 130, 60, -25)
    WAIT_FRAMES(1)
    CALL(evt_npc_set_rotate, STRING(((char*)str_0000045C)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)str_00000464)), 0, 0, 180)
    CALL(evt_npc_set_rotate, STRING(((char*)str_0000044C)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)str_00000454)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)str_0000046C)), 0, 0, 0)
    WAIT_FRAMES(1)
    CALL(evt_npc_set_anim, STRING(((char*)str_0000045C)), STRING(((char*)str_0000085C)))
    CALL(evt_npc_set_anim, STRING(((char*)str_00000464)), STRING(((char*)str_00000864)))
    CALL(evt_npc_set_anim, STRING(((char*)str_0000044C)), STRING(((char*)str_0000085C)))
    CALL(evt_npc_set_anim, STRING(((char*)str_00000454)), STRING(((char*)str_0000085C)))
    CALL(evt_npc_set_anim, STRING(((char*)str_0000046C)), STRING(((char*)str_0000085C)))
    CALL(evt_mario_set_pose, STRING(((char*)str_000005B8)))
    CALL_CHILD(PTR(evt_kime_pose))
    CALL(evt_npc_get_position, STRING(((char*)str_0000044C)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_0000086C)), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_0000045C)), 512)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000884)), 0, STRING(((char*)str_0000045C)))
    WAIT_MS(300)
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001E0)), STRING(((char*)str_0000078C)))
    CALL(evt_cam3d_evt_set, -70, 138, 263, -70, 90, -8, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000890)), 0, STRING(((char*)str_000001E0)))
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000208)))
    WAIT_MS(300)
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_0000020C)))
    CALL(evt_msg_select, 0, STRING(((char*)str_0000089C)))
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_0000021C)))
    WAIT_MS(300)
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000220)))
    CALL(evt_msg_print_add, 0, STRING(((char*)str_000008AC)))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(1), 100)
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000258)), LW(0), LW(1), LW(2), 0)
    CALL(evt_cam3d_evt_set, 0, 850, 2160, 0, 287, -8, 10000, 0)
    WAIT_MS(7000)
    RETURN
EVT_END()

EVT_BEGIN(evt_kurikuri_lose)
    CALL_CHILD(PTR(evt_damage_pose))
    CALL(evt_npc_set_rotate, STRING(((char*)str_0000045C)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)str_00000464)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)str_0000044C)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)str_00000454)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)str_0000046C)), 0, 0, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 50, 60, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 90, 60, 25)
    CALL(evt_npc_set_position, STRING(((char*)str_0000044C)), 70, 60, -25)
    CALL(evt_npc_set_position, STRING(((char*)str_00000454)), 110, 60, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_0000046C)), 130, 60, -25)
    CALL(evt_npc_get_position, STRING(((char*)str_00000464)), LW(0), LW(1), LW(2))
    ADD(LW(1), 100)
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_cam3d_evt_set, 70, 138, 263, 70, 90, -8, 0, 0)
    WAIT_FRAMES(1)
    CALL(evt_snd_sfxon, STRING(((char*)str_000008C8)), 0)
    IF_INT_LESS(GSW(0), 172)
        SET_VALUE(LW(2), STRING(((char*)str_000001E0)))
        ELSE
        SET_VALUE(LW(2), STRING(((char*)str_0000028C)))
    END_IF
    CALL(evt_npc_set_position, LW(2), 33, 60, -83)
    CALL(evt_set_dir_to_target, LW(2), STRING(((char*)str_0000045C)))
    CALL(evt_tou_get_fighter_info_28_text_3E58, GSW(501), LW(0), LW(1))
    CALL(evt_msg_print_insert, 0, STRING(((char*)str_000008E0)), 0, LW(2), LW(0))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_000008F0)), 0, STRING(((char*)str_0000045C)))
    RETURN
EVT_END()

EVT_BEGIN(evt_shinemon_opening)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_npc_status_onoff, 1, STRING(((char*)str_000001E0)), 2)
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), 0, 60, -130)
    CALL(evt_cam3d_evt_set, 1075, 547, 998, 0, 287, -8, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000758)))
    CALL(evt_cam3d_evt_set, -1024, 547, 1050, 0, 287, -8, 5000, 0)
    WAIT_MS(5000)
    CALL(evt_cam3d_evt_set, 0, 127, 105, 0, 95, -145, 0, 0)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_000008FC)), 0, STRING(((char*)str_000001E0)))
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING(((char*)str_0000090C)), 0, STRING(((char*)str_000001E0)))
    CALL(evt_mario_set_pos, -550, 0, 0)
    CALL(evt_party_set_pos, 0, -560, 0, -10)
    SET_FLOAT_VALUE(LW(0), FLOAT(-180.0f))
    CALL_CHILD(PTR(w_door_open))
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000794)), -565, 0, 0, 0)
        CALL(evt_sub_intpl_init, 11, -180, 0, 20)
        LOOP(21)
            CALL(evt_sub_intpl_get_value)
            CALL_CHILD(PTR(w_door_open))
        END_LOOP
    END_INLINE_EVENT
    SET_VALUE(GF(0), 0)
    SET_VALUE(GF(1), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, -450, 0, FLOAT(120.0f))
        WAIT_MS(1000)
        SET_VALUE(GF(1), 1)
        CALL(evt_mario_mov_pos2, -280, 0, FLOAT(120.0f))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000007D0)), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_jump_pos, -250, 20, 0, 400, 1, -1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_0000091C)), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_jump_pos, -215, 40, 0, 400, 1, -1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000007B4)), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_jump_pos, -185, 60, 0, 400, 1, -1000)
        CALL(evt_mario_mov_pos2, -80, 0, FLOAT(120.0f))
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            IF_INT_EQUAL(GF(1), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        WAIT_MS(300)
        CALL(evt_party_move_pos2, 0, -280, 25, FLOAT(120.0f))
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -250, 20, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -215, 40, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -185, 60, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
        CALL(evt_party_move_pos2, 0, -130, -25, FLOAT(120.0f))
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -426, 30, -195)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000938)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(800)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -379, 30, 133)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000948)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(800)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -293, 60, -180)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000958)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(800)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -272, 90, 200)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000968)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(800)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_move_position, STRING(((char*)str_000001E0)), -20, -20, 0, FLOAT(70.0f), 1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000978)), 0, STRING(((char*)str_000001E0)))
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000208)))
    WAIT_MS(300)
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_0000020C)))
    CALL(evt_msg_select, 0, STRING(((char*)str_00000988)))
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_0000021C)))
    WAIT_MS(300)
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000220)))
    CALL(evt_msg_print_add, 0, STRING(((char*)str_00000998)))
    CALL(evt_eff_fukidashi, 1, STRING(((char*)str_000009A8)), STRING(((char*)str_000001E0)), 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(500)
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001E0)), STRING(((char*)str_0000045C)))
    SET_FLOAT_VALUE(LW(0), FLOAT(-180.0f))
    CALL_CHILD(PTR(e_door_open))
    CALL(evt_cam3d_evt_set, 475, 134, 533, 475, 38, -8, 0, 0)
    WAIT_FRAMES(1)
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 550, 0, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 550, 0, 0)
    SET_VALUE(LW(0), STRING(((char*)str_00000464)))
    SET_VALUE(LW(1), 0)
    SET_VALUE(LW(2), 2)
    SPAWN_EVENT(PTR(evt_teki_nyuujyou))
    WAIT_MS(500)
    SET_VALUE(LW(0), STRING(((char*)str_0000045C)))
    SET_VALUE(LW(1), 1)
    SET_VALUE(LW(2), 2)
    SPAWN_EVENT(PTR(evt_teki_nyuujyou))
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000794)), 565, 0, 0, 0)
        CALL(evt_sub_intpl_init, 11, -180, 0, 20)
        LOOP(21)
            CALL(evt_sub_intpl_get_value)
            CALL_CHILD(PTR(e_door_open))
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_msg_toge, 2, 426, 30, -195)
        CALL(evt_msg_print, 0, STRING(((char*)str_000009AC)), 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(3000)
        CALL(evt_msg_toge, 2, 379, 30, 133)
        CALL(evt_msg_print, 0, STRING(((char*)str_000009BC)), 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_msg_toge, 2, 293, 30, -180)
        CALL(evt_msg_print, 0, STRING(((char*)str_000009CC)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(3000)
    CALL(evt_cam3d_evt_set, 50, 146, 273, 50, 96, -8, 6000, 0)
    WAIT_MS(6000)
    CALL(evt_npc_move_position, STRING(((char*)str_000001E0)), 0, -30, 0, FLOAT(70.0f), 1)
    CALL(evt_msg_print, 0, STRING(((char*)str_000009DC)), 0, STRING(((char*)str_000001E0)))
    CALL(evt_msg_print, 0, STRING(((char*)str_000009EC)), 0, STRING(((char*)str_0000045C)))
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 80, 146, 273, 80, 96, -8, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)str_000009FC)), 0, STRING(((char*)str_00000464)))
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), 0, 60, -130)
    CALL(evt_cam3d_evt_set, 0, 150, 141, 0, 100, -154, 0, 11)
    WAIT_MS(200)
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A0C)))
    WAIT_MS(200)
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A10)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A10)), STRING(((char*)str_00000A14)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000A18)), 0, STRING(((char*)str_000001E0)))
    WAIT_MS(300)
    CALL(evt_snd_sfxon, STRING(((char*)str_000005A8)), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_cam3d_evt_set, 0, 250, 730, 0, 100, -154, 2000, 11)
    END_INLINE_EVENT
    WAIT_MS(1000)
    RETURN
EVT_END()

EVT_BEGIN(evt_shinemon_win)
    SET_VALUE(GSWF(2512), 1)
    CALL(evt_cam3d_evt_set, 60, 143, 263, 60, 95, -8, 0, 0)
    WAIT_FRAMES(1)
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 55, 60, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 95, 60, 0)
    CALL(evt_npc_set_anim, STRING(((char*)str_0000045C)), STRING(((char*)str_000005C0)))
    CALL(evt_npc_set_anim, STRING(((char*)str_00000464)), STRING(((char*)str_000005C0)))
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_0000045C)), 1536)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00000464)), 1536)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), 30)
    ADD(LW(2), -30)
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), LW(0), LW(1), LW(2))
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001E0)), STRING(((char*)str_0000078C)))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000A2C)), 0, STRING(((char*)str_0000045C)))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000A3C)), 0, STRING(((char*)str_00000464)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -65, 143, 263, -65, 95, -8, 0, 0)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000A4C)), 0, STRING(((char*)str_000001E0)))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(1), 100)
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_00000A5C)))
    CALL(evt_mario_set_dir, 270, 300, 0)
    WAIT_MS(400)
    CALL(evt_mario_set_dir, 90, 300, 0)
    WAIT_MS(400)
    CALL(evt_mario_set_dir, 270, 300, 0)
    WAIT_MS(400)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000A64)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_00000A7C)))
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000258)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 850, 2160, 0, 287, -8, 10000, 0)
    WAIT_MS(7000)
    RETURN
EVT_END()

EVT_BEGIN(evt_shinemon_lose)
    CALL_CHILD(PTR(evt_damage_pose))
    CALL(evt_npc_get_position, STRING(((char*)str_0000045C)), LW(0), LW(1), LW(2))
    ADD(LW(1), 100)
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING(((char*)str_000008C8)), 0)
    IF_INT_LESS(GSW(0), 172)
        SET_VALUE(LW(2), STRING(((char*)str_000001E0)))
        ELSE
        SET_VALUE(LW(2), STRING(((char*)str_0000028C)))
    END_IF
    CALL(evt_tou_get_fighter_info_28_text_3E58, GSW(501), LW(0), LW(1))
    CALL(evt_msg_print_insert, 0, STRING(((char*)str_000008E0)), 0, LW(2), LW(0))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 60, 143, 263, 60, 95, -8, 0, 0)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000A84)), 0, STRING(((char*)str_0000045C)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000A94)), 0, STRING(((char*)str_00000464)))
    WAIT_MS(300)
    RETURN
EVT_END()

EVT_BEGIN(evt_champ_opening)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_npc_status_onoff, 1, STRING(((char*)str_000001E0)), 2)
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), 0, 60, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 80, 60, 0)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000001E0)), 32768)
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001E0)), STRING(((char*)str_0000045C)))
    CALL(evt_set_dir_to_target, STRING(((char*)str_0000045C)), STRING(((char*)str_000001E0)))
    CALL(evt_cam3d_evt_set, 0, 192, 620, 0, 95, -145, 0, 11)
    CALL(evt_npc_set_tribe, STRING(((char*)str_0000045C)), STRING(((char*)str_00000AA4)))
    BEGIN_INLINE_EVENT
        CALL(tou_champion_belt_28_text_2A10, STRING(((char*)str_0000045C)))
    END_INLINE_EVENT
    CALL(evt_seq_wait, 2)
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000ABC)))
    CALL(evt_snd_bgm_scope, 0, 1)
    WAIT_MS(2000)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_000001E0)), 32768)
    CALL(evt_eff_fukidashi, 1, STRING(((char*)str_00000ACC)), STRING(((char*)str_000001E0)), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_npc_set_ry, STRING(((char*)str_000001E0)), 270)
    WAIT_MS(500)
    CALL(evt_mario_set_pos, -550, 0, 0)
    CALL(evt_party_set_pos, 0, -560, 0, -10)
    SET_FLOAT_VALUE(LW(0), FLOAT(-180.0f))
    CALL_CHILD(PTR(w_door_open))
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000794)), -565, 0, 0, 0)
        CALL(evt_sub_intpl_init, 11, -180, 0, 20)
        LOOP(21)
            CALL(evt_sub_intpl_get_value)
            CALL_CHILD(PTR(w_door_open))
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, -450, 0, FLOAT(120.0f))
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 0, 155, 330, 0, 95, -145, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000AD0)), 0, STRING(((char*)str_000001E0)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 328, 1219, 0, 130, 145, 3000, 11)
    BEGIN_INLINE_EVENT
        WAIT_MS(2000)
        CALL(evt_msg_toge, 2, -200, 30, -200)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000AE0)), 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(3000)
        CALL(evt_msg_toge, 2, 200, 30, 200)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000AF0)), 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_msg_toge, 2, -300, 200, -400)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B00)), 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_msg_toge, 2, 200, 200, -300)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B10)), 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(5000)
        CALL(evt_msg_toge, 2, 200, 30, 133)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B20)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(7000)
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING(((char*)str_00000B30)))
    WAIT_MS(300)
    CALL(evt_party_run, 0)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, -280, 0, FLOAT(60.0f))
        CALL(evt_cam3d_evt_set, 0, 192, 620, 0, 95, -145, 4000, 11)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000007EC)), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_jump_pos, -250, 20, 0, 400, 1, -1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000B40)), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_jump_pos, -215, 40, 0, 400, 1, -1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000007B4)), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_jump_pos, -185, 60, 0, 400, 1, -1000)
        CALL(evt_mario_mov_pos2, -80, 0, FLOAT(60.0f))
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_stop, 0)
        WAIT_MS(300)
        CALL(evt_party_move_pos2, 0, -280, 25, FLOAT(60.0f))
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -250, 20, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -215, 40, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -185, 60, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
        CALL(evt_party_move_pos2, 0, -130, -25, FLOAT(60.0f))
        CALL(evt_party_stop, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -426, 30, -195)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B5C)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -379, 30, 233)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B6C)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -293, 30, -180)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B7C)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -272, 30, 100)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B8C)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -150, 100, -200)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B8C)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(1000)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(500)
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A0C)))
    WAIT_MS(200)
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A10)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A10)), STRING(((char*)str_00000A14)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000B9C)), 0, STRING(((char*)str_000001E0)))
    WAIT_MS(300)
    CALL(evt_snd_sfxon, STRING(((char*)str_000005A8)), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_cam3d_evt_set, 0, 250, 730, 0, 100, -154, 2000, 11)
    END_INLINE_EVENT
    WAIT_MS(1000)
    RETURN
EVT_END()

EVT_BEGIN(evt_champ_opening_re)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_npc_status_onoff, 1, STRING(((char*)str_0000028C)), 2)
    CALL(evt_npc_set_position, STRING(((char*)str_0000028C)), 0, 60, -130)
    CALL(evt_cam3d_evt_set, 0, 481, 1310, 0, 295, -145, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000ABC)))
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_cam3d_evt_set, 0, 281, 1310, 0, 95, -145, 3000, 0)
    WAIT_MS(3000)
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 0, 127, 105, 0, 95, -145, 0, 0)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000BAC)), 0, STRING(((char*)str_0000028C)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000BBC)), 0, STRING(((char*)str_0000028C)))
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 550, 0, 0)
    SET_FLOAT_VALUE(LW(0), FLOAT(-180.0f))
    CALL_CHILD(PTR(e_door_open))
    CALL(evt_cam3d_evt_set, 475, 134, 533, 475, 38, -8, 0, 0)
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000794)), 565, 0, 0, 0)
        CALL(evt_sub_intpl_init, 11, -180, 0, 20)
        LOOP(21)
            CALL(evt_sub_intpl_get_value)
            CALL_CHILD(PTR(e_door_open))
        END_LOOP
    END_INLINE_EVENT
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)str_0000045C)), 450, 0, 0, FLOAT(60.0f), 1)
        WAIT_MS(1000)
        CALL(evt_npc_move_position, STRING(((char*)str_0000045C)), 310, 0, 0, FLOAT(60.0f), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000045C)), 280, 20, 0, 500, 30)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000045C)), 245, 40, 0, 500, 30)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000045C)), 215, 60, 0, 500, 30)
        CALL(evt_npc_move_position, STRING(((char*)str_0000045C)), 80, 0, 0, FLOAT(60.0f), 1)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_msg_toge, 2, 426, 30, -195)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BCC)), 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(3000)
        CALL(evt_msg_toge, 2, 379, 30, 133)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BDC)), 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_msg_toge, 2, 293, 30, -180)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BEC)), 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(5000)
        CALL(evt_msg_toge, 2, 200, 30, 133)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BFC)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(3000)
    CALL(evt_cam3d_evt_set, 50, 146, 273, 50, 96, -8, 6000, 0)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(1000)
    CALL(evt_npc_move_position, STRING(((char*)str_0000028C)), 20, -20, 0, FLOAT(70.0f), 1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000C0C)), 0, STRING(((char*)str_0000028C)))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000C1C)), 0, STRING(((char*)str_0000045C)))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000C2C)), 0, STRING(((char*)str_0000028C)))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000C3C)), 0, STRING(((char*)str_0000045C)))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000C4C)), 0, STRING(((char*)str_0000028C)))
    CALL(evt_npc_set_ry, STRING(((char*)str_0000028C)), 270)
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_npc_move_position, STRING(((char*)str_0000028C)), 0, -130, 0, FLOAT(70.0f), 1)
    END_INLINE_EVENT
    CALL(evt_mario_set_pos, -550, 0, 0)
    CALL(evt_party_set_pos, 0, -560, 0, -10)
    SET_FLOAT_VALUE(LW(0), FLOAT(-180.0f))
    CALL_CHILD(PTR(w_door_open))
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000794)), -565, 0, 0, 0)
        CALL(evt_sub_intpl_init, 11, -180, 0, 20)
        LOOP(21)
            CALL(evt_sub_intpl_get_value)
            CALL_CHILD(PTR(w_door_open))
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, -450, 0, FLOAT(120.0f))
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 0, 328, 1219, 0, 130, 145, 3000, 11)
    BEGIN_INLINE_EVENT
        WAIT_MS(2000)
        CALL(evt_msg_toge, 2, -200, 30, -200)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000C5C)), 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(3000)
        CALL(evt_msg_toge, 2, 200, 30, 200)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000C6C)), 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_msg_toge, 2, -300, 200, -400)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000C7C)), 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_msg_toge, 2, 200, 200, -300)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000C8C)), 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(5000)
        CALL(evt_msg_toge, 2, 200, 30, 133)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000C9C)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(7000)
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING(((char*)str_00000CAC)))
    WAIT_MS(300)
    CALL(evt_party_run, 0)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, -280, 0, FLOAT(60.0f))
        CALL(evt_cam3d_evt_set, 0, 192, 620, 0, 95, -145, 5000, 11)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000007EC)), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_jump_pos, -250, 20, 0, 400, 1, -1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_0000091C)), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_jump_pos, -215, 40, 0, 400, 1, -1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000B40)), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_jump_pos, -185, 60, 0, 400, 1, -1000)
        CALL(evt_mario_mov_pos2, -80, 0, FLOAT(60.0f))
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(300)
        CALL(evt_party_move_pos2, 0, -280, 25, FLOAT(60.0f))
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -250, 20, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -215, 40, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -185, 60, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
        CALL(evt_party_move_pos2, 0, -130, -25, FLOAT(60.0f))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -426, 30, -195)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000CBC)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -379, 30, 233)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000CCC)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -293, 60, -180)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000CDC)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -272, 90, 300)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000CEC)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -150, 100, -200)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000CFC)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(1000)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_set_anim, STRING(((char*)str_0000028C)), STRING(((char*)str_00000D0C)))
    WAIT_MS(200)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)str_0000028C)), STRING(((char*)str_00000230)), STRING(((char*)str_00000D10)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000D14)), 0, STRING(((char*)str_0000028C)))
    WAIT_MS(300)
    CALL(evt_snd_sfxon, STRING(((char*)str_000005A8)), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_cam3d_evt_set, 0, 250, 730, 0, 100, -154, 2000, 11)
    END_INLINE_EVENT
    WAIT_MS(1000)
    RETURN
EVT_END()

EVT_BEGIN(evt_champ_win)
    CALL(tou_champion_belt_onoff_28_text_29DC, 1)
    IF_INT_LESS(GSW(0), 172)
        SET_VALUE(LW(15), STRING(((char*)str_000001E0)))
        SET_VALUE(LW(14), STRING(((char*)str_00000D24)))
        SET_VALUE(LW(13), STRING(((char*)str_00000D34)))
        ELSE
        SET_VALUE(LW(15), STRING(((char*)str_0000028C)))
        SET_VALUE(LW(14), STRING(((char*)str_00000D44)))
        SET_VALUE(LW(13), STRING(((char*)str_00000D54)))
    END_IF
    CALL(evt_npc_set_position, LW(15), -20, 60, -50)
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 80, 60, 0)
    CALL(evt_npc_get_position, STRING(((char*)str_0000045C)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000D64)), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_anim, STRING(((char*)str_0000045C)), STRING(((char*)str_000002E8)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)str_0000045C)), STRING(((char*)str_00000D78)), STRING(((char*)str_00000D80)))
    CALL(evt_cam3d_evt_set, 80, 146, 273, 80, 96, -8, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, LW(14), 0, STRING(((char*)str_0000045C)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -80, 146, 273, -80, 96, -8, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, LW(13), 0, LW(15))
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(1), 100)
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING(((char*)str_000008C8)), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_00000A5C)))
    CALL(evt_mario_set_dir, 270, 300, 0)
    WAIT_MS(400)
    CALL(evt_mario_set_dir, 90, 300, 0)
    WAIT_MS(400)
    CALL(evt_mario_set_dir, 270, 300, 0)
    WAIT_MS(400)
    CALL(evt_mario_set_dir, 90, 300, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000A64)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_00000A7C)))
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000258)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING(((char*)str_000005B8)))
    CALL(evt_cam3d_evt_set, 1075, 547, 998, 0, 287, -8, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_cam3d_evt_set, -1024, 547, 1050, 0, 287, -8, 5000, 0)
    IF_INT_LESS(GSW(0), 172)
        SET_VALUE(LW(15), STRING(((char*)str_00000D88)))
        SET_VALUE(LW(14), STRING(((char*)str_00000D98)))
        SET_VALUE(LW(13), STRING(((char*)str_00000DA8)))
        SET_VALUE(LW(12), STRING(((char*)str_00000DB8)))
        SET_VALUE(LW(11), STRING(((char*)str_00000DC8)))
        ELSE
        SET_VALUE(LW(15), STRING(((char*)str_00000DD8)))
        SET_VALUE(LW(14), STRING(((char*)str_00000DE8)))
        SET_VALUE(LW(13), STRING(((char*)str_00000DF8)))
        SET_VALUE(LW(12), STRING(((char*)str_00000E08)))
        SET_VALUE(LW(11), STRING(((char*)str_00000E18)))
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -300, 300, -195)
        CALL(evt_msg_print, 0, LW(15), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(800)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -150, 100, -133)
        CALL(evt_msg_print, 0, LW(14), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(800)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, 0, 300, -180)
        CALL(evt_msg_print, 0, LW(13), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(800)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, 150, 30, -200)
        CALL(evt_msg_print, 0, LW(12), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(800)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, 300, 200, -200)
        CALL(evt_msg_print, 0, LW(11), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(1000)
    RETURN
EVT_END()

EVT_BEGIN(evt_champ_lose)
    CALL_CHILD(PTR(evt_damage_pose))
    CALL(evt_npc_get_position, STRING(((char*)str_0000045C)), LW(0), LW(1), LW(2))
    ADD(LW(1), 100)
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING(((char*)str_000008C8)), 0)
    CALL(evt_tou_get_fighter_info_28_text_3E58, GSW(501), LW(0), LW(1))
    IF_INT_LESS(GSW(0), 172)
        SET_VALUE(LW(2), STRING(((char*)str_000001E0)))
        ELSE
        SET_VALUE(LW(2), STRING(((char*)str_0000028C)))
    END_IF
    CALL(evt_msg_print_insert, 0, STRING(((char*)str_000008E0)), 0, LW(2), LW(0))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 40, 142, 250, 40, 96, -8, 0, 0)
    WAIT_FRAMES(1)
    CALL(evt_tou_get_ranking_28_text_4048, LW(1))
    IF_INT_LESS(GSW(0), 172)
        IF_INT_EQUAL(GSWF(2383), 1)
            SET_VALUE(LW(0), STRING(((char*)str_00000E28)))
            ELSE
            IF_INT_EQUAL(LW(1), 0)
                SET_VALUE(LW(0), STRING(((char*)str_00000E38)))
                ELSE
                SET_VALUE(LW(0), STRING(((char*)str_00000E48)))
            END_IF
        END_IF
        ELSE
        IF_INT_EQUAL(GSWF(2383), 1)
            SET_VALUE(LW(0), STRING(((char*)str_00000E58)))
            ELSE
            IF_INT_EQUAL(LW(1), 0)
                SET_VALUE(LW(0), STRING(((char*)str_00000E68)))
                ELSE
                SET_VALUE(LW(0), STRING(((char*)str_00000E78)))
            END_IF
        END_IF
    END_IF
    CALL(evt_msg_print, 0, LW(0), 0, STRING(((char*)str_0000045C)))
    WAIT_MS(300)
    RETURN
EVT_END()

EVT_BEGIN(evt_default_opening)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    IF_INT_LESS(GSW(0), 172)
        SET_VALUE(LW(0), STRING(((char*)str_000001E0)))
        ELSE
        SET_VALUE(LW(0), STRING(((char*)str_0000028C)))
    END_IF
    CALL(evt_npc_status_onoff, 1, LW(0), 2)
    CALL(evt_npc_set_position, LW(0), 0, 60, -130)
    CALL(evt_mario_set_pos, -350, 0, 0)
    CALL(evt_party_set_pos, 0, -390, 0, 25)
    CALL(evt_tou_get_fighter_num, GSW(501), LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 350, 0, 0)
        CASE_EQUAL(2)
        CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 350, 0, 0)
        CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 390, 0, 25)
        CASE_EQUAL(3)
        CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 350, 0, 0)
        CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 390, 0, 25)
        CALL(evt_npc_set_position, STRING(((char*)str_0000044C)), 370, 0, -25)
        CASE_EQUAL(4)
        CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 350, 0, 0)
        CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 390, 0, 25)
        CALL(evt_npc_set_position, STRING(((char*)str_0000044C)), 370, 0, -25)
        CALL(evt_npc_set_position, STRING(((char*)str_00000454)), 410, 0, 0)
        CASE_EQUAL(5)
        CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 350, 0, 0)
        CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 390, 0, 25)
        CALL(evt_npc_set_position, STRING(((char*)str_0000044C)), 370, 0, -25)
        CALL(evt_npc_set_position, STRING(((char*)str_00000454)), 410, 0, 0)
        CALL(evt_npc_set_position, STRING(((char*)str_0000046C)), 430, 0, -25)
    END_SWITCH
    CALL(evt_cam3d_evt_set, 0, 585, 1310, 0, 400, -145, 0, 11)
    IF_INT_LESS(GSW(0), 158)
        IF_INT_EQUAL(GSW(501), 0)
            CALL(evt_npc_set_tribe, STRING(((char*)str_0000045C)), STRING(((char*)str_00000AA4)))
            BEGIN_INLINE_EVENT
                CALL(tou_champion_belt_28_text_2A10, STRING(((char*)str_0000045C)))
            END_INLINE_EVENT
        END_IF
    END_IF
    CALL(evt_seq_wait, 2)
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000758)))
    CALL(evt_cam3d_evt_set, 0, 331, 1310, 0, 145, -145, 3000, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, -280, 0, FLOAT(120.0f))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_0000091C)), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_jump_pos, -250, 20, 0, 400, 1, -1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000B40)), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_jump_pos, -215, 40, 0, 400, 1, -1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000007D0)), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_jump_pos, -185, 60, 0, 400, 1, -1000)
        CALL(evt_mario_mov_pos2, -55, 0, FLOAT(120.0f))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT_GET_ID(LW(10))
        CALL(evt_party_move_pos2, 0, -280, 25, FLOAT(120.0f))
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -250, 20, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -215, 40, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -185, 60, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
        CALL(evt_party_move_pos2, 0, -90, -25, FLOAT(120.0f))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_tou_get_fighter_num, GSW(501), LW(0))
        SET_VALUE(LW(3), LW(0))
        SET_VALUE(LW(4), 0)
        LOOP(0)
            IF_INT_EQUAL(LW(3), LW(4))
                BREAK_LOOP
            END_IF
            SWITCH(LW(4))
                CASE_EQUAL(0)
                SET_VALUE(LW(0), STRING(((char*)str_0000045C)))
                CASE_EQUAL(1)
                SET_VALUE(LW(0), STRING(((char*)str_00000464)))
                CASE_EQUAL(2)
                SET_VALUE(LW(0), STRING(((char*)str_0000044C)))
                CASE_EQUAL(3)
                SET_VALUE(LW(0), STRING(((char*)str_00000454)))
                CASE_EQUAL(4)
                SET_VALUE(LW(0), STRING(((char*)str_0000046C)))
            END_SWITCH
            SET_VALUE(LW(1), LW(4))
            SET_VALUE(LW(2), LW(3))
            SPAWN_EVENT(PTR(evt_teki_nyuujyou_default))
            ADD(LW(4), 1)
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(3000)
    LOOP(0)
        IS_EVENT_RUNNING(LW(10), LW(11))
        IF_INT_EQUAL(LW(11), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_party_set_pos, 0, -95, 60, -25)
    CALL(evt_cam3d_evt_set, 0, 127, 105, 0, 95, -145, 0, 0)
    WAIT_FRAMES(1)
    CALL(evt_tou_get_fighter_info_28_text_3E58, GSW(501), LW(0), LW(1))
    CALL(evt_tou_get_fighter_name2_28_text_3DD4, GSW(501), LW(2))
    IF_INT_EQUAL(GSW(501), 0)
        IF_INT_LESS(GSW(0), 172)
            SET_VALUE(LW(0), STRING(((char*)str_000001E0)))
            ELSE
            SET_VALUE(LW(0), STRING(((char*)str_0000028C)))
        END_IF
        CALL(evt_tou_get_ranking_28_text_4048, LW(1))
        SWITCH(LW(1))
            CASE_EQUAL(0)
            IF_INT_LESS(GSW(0), 172)
                SET_VALUE(LW(1), STRING(((char*)str_00000E88)))
                ELSE
                SET_VALUE(LW(1), STRING(((char*)str_00000E98)))
            END_IF
            CASE_EQUAL(1)
            IF_INT_LESS(GSW(0), 172)
                SET_VALUE(LW(1), STRING(((char*)str_00000EA8)))
                ELSE
                SET_VALUE(LW(1), STRING(((char*)str_00000EB8)))
            END_IF
        END_SWITCH
        CALL(evt_msg_print, 0, LW(1), 0, LW(0))
        ELSE
        IF_INT_LESS(GSW(0), 172)
            SET_VALUE(LW(3), STRING(((char*)str_000001E0)))
            SET_VALUE(LW(4), STRING(((char*)str_00000EC8)))
            SET_VALUE(LW(5), STRING(((char*)str_00000ED8)))
            ELSE
            SET_VALUE(LW(3), STRING(((char*)str_0000028C)))
            SET_VALUE(LW(4), STRING(((char*)str_00000EE8)))
            SET_VALUE(LW(5), STRING(((char*)str_00000EF8)))
        END_IF
        CALL(evt_msg_print, 0, LW(4), 0, LW(3))
        CALL(evt_msg_print_add_insert, 0, LW(5), LW(2), LW(0))
    END_IF
    CALL(evt_cam3d_evt_set, -65, 143, 263, -65, 95, -8, 0, 0)
    WAIT_FRAMES(1)
    IF_INT_LESS(GSW(0), 172)
        CALL(evt_mario_get_party, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(evt_party_stop, 0)
            WAIT_MS(300)
            CALL(evt_sub_random, 1000, LW(0))
            IF_INT_LESS(LW(0), 500)
                CALL(evt_msg_print_party, STRING(((char*)str_00000F08)))
                ELSE
                CALL(evt_msg_print_party, STRING(((char*)str_00000F18)))
            END_IF
            WAIT_MS(300)
            ELSE
            CALL(evt_msg_print, 0, STRING(((char*)str_00000F28)), 0, STRING(((char*)str_000001E0)))
        END_IF
        ELSE
        CALL(evt_party_stop, 0)
        WAIT_MS(300)
        CALL(evt_msg_print_party, STRING(((char*)str_00000F38)))
        WAIT_MS(300)
    END_IF
    CALL(evt_tou_get_fighter_info_28_text_3E58, GSW(501), LW(0), LW(1))
    SWITCH(LW(1))
        CASE_EQUAL(3)
        CALL(evt_cam3d_evt_set, 65, 183, 263, 65, 135, -8, 0, 0)
        CASE_DEFAULT
        CALL(evt_cam3d_evt_set, 60, 143, 263, 60, 95, -8, 0, 0)
    END_SWITCH
    WAIT_FRAMES(1)
    CALL(evt_tou_get_ranking_28_text_4048, LW(2))
    CALL(evt_tou_get_fighter_battle_msg_28_text_3CB4, GSW(501), LW(0), LW(1))
    SWITCH(GSW(501))
        CASE_EQUAL(10)
        SWITCH(GSW(0))
            CASE_BETWEEN(138, 172)
            SET_VALUE(LW(0), STRING(((char*)str_00000F48)))
            CASE_GREATER_OR_EQUAL(172)
            IF_INT_LESS_OR_EQUAL(LW(2), 10)
                SET_VALUE(LW(0), STRING(((char*)str_00000F48)))
            END_IF
        END_SWITCH
        CASE_EQUAL(0)
        SWITCH(GSW(0))
            CASE_LESS(172)
            IF_INT_EQUAL(LW(2), 1)
                SET_VALUE(LW(0), STRING(((char*)str_00000F58)))
            END_IF
            CASE_DEFAULT
            IF_INT_EQUAL(LW(2), 1)
                SET_VALUE(LW(0), STRING(((char*)str_00000F68)))
            END_IF
        END_SWITCH
    END_SWITCH
    WAIT_MS(300)
    CALL(evt_msg_print, 0, LW(0), 0, STRING(((char*)str_0000045C)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 150, 141, 0, 100, -154, 0, 11)
    IF_INT_LESS(GSW(0), 172)
        SET_VALUE(LW(0), STRING(((char*)str_000001E0)))
        SET_VALUE(LW(1), STRING(((char*)str_00000A18)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A0C)))
        WAIT_MS(200)
        CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A10)))
        CALL(evt_npc_set_autotalkpose, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A10)), STRING(((char*)str_00000A14)))
        ELSE
        SET_VALUE(LW(0), STRING(((char*)str_0000028C)))
        SET_VALUE(LW(1), STRING(((char*)str_00000F78)))
        CALL(evt_npc_set_anim, STRING(((char*)str_0000028C)), STRING(((char*)str_00000D0C)))
        WAIT_MS(200)
        CALL(evt_npc_set_autotalkpose, STRING(((char*)str_0000028C)), STRING(((char*)str_00000230)), STRING(((char*)str_00000D10)))
    END_IF
    CALL(evt_msg_print, 0, LW(1), 0, LW(0))
    WAIT_MS(300)
    CALL(evt_snd_sfxon, STRING(((char*)str_000005A8)), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_cam3d_evt_set, 0, 250, 730, 0, 100, -154, 2000, 11)
    END_INLINE_EVENT
    WAIT_MS(1000)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_default_win)
    CALL(evt_cam3d_evt_set, 0, 220, 533, 0, 125, -8, 0, 0)
    WAIT_FRAMES(1)
    CALL(tou_champion_belt_onoff_28_text_29DC, 1)
    CALL(evt_tou_get_fighter_num, GSW(501), LW(0))
    SET_VALUE(LW(1), 0)
    LOOP(0)
        IF_INT_EQUAL(LW(0), LW(1))
            BREAK_LOOP
        END_IF
        SWITCH(LW(1))
            CASE_EQUAL(0)
            SET_VALUE(LW(2), STRING(((char*)str_0000045C)))
            CASE_EQUAL(1)
            SET_VALUE(LW(2), STRING(((char*)str_00000464)))
            CASE_EQUAL(2)
            SET_VALUE(LW(2), STRING(((char*)str_0000044C)))
            CASE_EQUAL(3)
            SET_VALUE(LW(2), STRING(((char*)str_00000454)))
            CASE_EQUAL(4)
            SET_VALUE(LW(2), STRING(((char*)str_0000046C)))
        END_SWITCH
        CALL(confupose, LW(2), LW(3))
        CALL(evt_npc_set_anim, LW(2), LW(3))
        ADD(LW(1), 1)
    END_LOOP
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(1), 100)
    CALL(evt_eff, 0, STRING(((char*)str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000A64)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_00000A7C)))
    CALL_CHILD(PTR(evt_kime_pose))
    BEGIN_INLINE_EVENT
        WAIT_MS(100)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000258)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    IF_INT_LESS(GSW(0), 172)
        SET_VALUE(LW(0), STRING(((char*)str_000001E0)))
        ELSE
        SET_VALUE(LW(0), STRING(((char*)str_0000028C)))
    END_IF
    CALL(evt_msg_print, 0, STRING(((char*)str_00000F88)), 0, LW(0))
    WAIT_MS(300)
    CALL(evt_mario_set_pose, STRING(((char*)str_000005B8)))
    CALL(evt_cam3d_evt_set, -65, 143, 263, -65, 95, -8, 0, 0)
    WAIT_FRAMES(1)
    IF_INT_LESS(GSW(0), 172)
        CALL(evt_mario_get_party, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(evt_party_stop, 0)
            WAIT_MS(300)
            CALL(evt_sub_random, 1000, LW(0))
            IF_INT_LESS(LW(0), 500)
                CALL(evt_msg_print_party, STRING(((char*)str_00000F98)))
                ELSE
                CALL(evt_msg_print_party, STRING(((char*)str_00000FA8)))
            END_IF
            WAIT_MS(300)
        END_IF
        ELSE
        CALL(evt_party_stop, 0)
        WAIT_MS(300)
        CALL(evt_msg_print_party, STRING(((char*)str_00000FB8)))
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_default_lose)
    CALL(evt_cam3d_evt_set, 0, 220, 533, 0, 125, -8, 0, 0)
    CALL_CHILD(PTR(evt_damage_pose))
    WAIT_FRAMES(1)
    CALL(evt_npc_get_position, STRING(((char*)str_0000045C)), LW(0), LW(1), LW(2))
    ADD(LW(1), 100)
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING(((char*)str_000008C8)), 0)
    CALL(evt_tou_get_fighter_info_28_text_3E58, GSW(501), LW(0), LW(1))
    IF_INT_LESS(GSW(0), 172)
        SET_VALUE(LW(1), STRING(((char*)str_000001E0)))
        ELSE
        SET_VALUE(LW(1), STRING(((char*)str_0000028C)))
    END_IF
    CALL(evt_msg_print_insert, 0, STRING(((char*)str_000008E0)), 0, LW(1), LW(0))
    CALL(evt_tou_get_fighter_info_28_text_3E58, GSW(501), LW(0), LW(1))
    SWITCH(LW(1))
        CASE_EQUAL(3)
        CALL(evt_cam3d_evt_set, 65, 183, 263, 65, 135, -8, 0, 0)
        CASE_DEFAULT
        CALL(evt_cam3d_evt_set, 60, 143, 263, 60, 95, -8, 0, 0)
    END_SWITCH
    WAIT_FRAMES(1)
    CALL(evt_tou_get_fighter_battle_msg_28_text_3CB4, GSW(501), LW(0), LW(1))
    SWITCH(GSW(501))
        CASE_EQUAL(10)
        SWITCH(GSW(0))
            CASE_BETWEEN(138, 172)
            SET_VALUE(LW(0), STRING(((char*)str_00000FC8)))
            CASE_GREATER_OR_EQUAL(172)
            IF_INT_LESS_OR_EQUAL(LW(2), 10)
                SET_VALUE(LW(0), STRING(((char*)str_00000FC8)))
            END_IF
        END_SWITCH
    END_SWITCH
    CALL(evt_msg_print, 0, LW(1), 0, STRING(((char*)str_0000045C)))
    WAIT_MS(300)
    RETURN
EVT_END()

static EVT_BEGIN(evt_champion)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000ABC)))
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000000F8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000104)), 1)
    CALL(evt_npc_status_onoff, 1, STRING(((char*)str_000001E0)), 2)
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), 0, 60, 0)
    CALL(evt_npc_set_ry, STRING(((char*)str_000001E0)), 270)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000001E0)), 32768)
    CALL(evt_cam3d_evt_set, 0, 281, 1310, 0, 95, -145, 0, 11)
    CALL(evt_npc_set_tribe, STRING(((char*)str_0000045C)), STRING(((char*)str_00000AA4)))
    BEGIN_INLINE_EVENT
        CALL(tou_champion_belt_28_text_2A10, STRING(((char*)str_0000045C)))
    END_INLINE_EVENT
    CALL(evt_seq_wait, 2)
    WAIT_MS(2000)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_000001E0)), 32768)
    CALL(evt_cam3d_evt_set, 0, 155, 327, 0, 96, -8, 0, 0)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000FD8)), 0, STRING(((char*)str_000001E0)))
    CALL(evt_npc_set_ry, STRING(((char*)str_000001E0)), 90)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000FE8)), 0, STRING(((char*)str_000001E0)))
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 550, 0, 0)
    SET_FLOAT_VALUE(LW(0), FLOAT(-180.0f))
    CALL_CHILD(PTR(e_door_open))
    CALL(evt_cam3d_evt_set, 475, 134, 533, 475, 38, -8, 0, 0)
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000794)), 565, 0, 0, 0)
        CALL(evt_sub_intpl_init, 11, -180, 0, 20)
        LOOP(21)
            CALL(evt_sub_intpl_get_value)
            CALL_CHILD(PTR(e_door_open))
        END_LOOP
    END_INLINE_EVENT
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)str_0000045C)), 450, 0, 0, FLOAT(60.0f), 1)
        WAIT_MS(1000)
        CALL(evt_npc_move_position, STRING(((char*)str_0000045C)), 310, 0, 0, FLOAT(60.0f), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000045C)), 280, 20, 0, 500, 30)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000045C)), 245, 40, 0, 500, 30)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000045C)), 215, 60, 0, 500, 30)
        CALL(evt_npc_move_position, STRING(((char*)str_0000045C)), 80, 0, 0, FLOAT(60.0f), 1)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_msg_toge, 2, 426, 30, -195)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000FF8)), 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(3000)
        CALL(evt_msg_toge, 2, 379, 30, 133)
        CALL(evt_msg_print, 0, STRING(((char*)str_00001008)), 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_msg_toge, 2, 293, 30, -180)
        CALL(evt_msg_print, 0, STRING(((char*)str_00001018)), 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(5000)
        CALL(evt_msg_toge, 2, 200, 30, 133)
        CALL(evt_msg_print, 0, STRING(((char*)str_00001028)), 0, 0)
    END_INLINE_EVENT
    WAIT_MS(3000)
    CALL(evt_cam3d_evt_set, 50, 155, 273, 50, 106, -8, 6000, 0)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(1000)
    CALL(evt_npc_move_position, STRING(((char*)str_000001E0)), 20, -20, 0, FLOAT(70.0f), 1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00001038)), 0, STRING(((char*)str_000001E0)))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00001048)), 0, STRING(((char*)str_0000045C)))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00001058)), 0, STRING(((char*)str_000001E0)))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00001068)), 0, STRING(((char*)str_0000045C)))
    WAIT_MS(300)
    WAIT_MS(1000)
    SET_VALUE(GSWF(2455), 1)
    CALL(evt_fade_set_mapchange_type, 0, 2, 300, 1, 300)
    CALL(evt_bero_mapchange, STRING(((char*)str_00001078)), STRING(((char*)str_00001080)))
    RETURN
EVT_END()

EVT_BEGIN(evt_champion2)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000ABC)))
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_cam3d_evt_set, 50, 155, 273, 50, 106, -8, 0, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 80, 60, 0)
    CALL(evt_npc_set_ry, STRING(((char*)str_0000045C)), 270)
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), 20, 60, -20)
    CALL(evt_npc_set_ry, STRING(((char*)str_000001E0)), 90)
    CALL(evt_npc_set_tribe, STRING(((char*)str_0000045C)), STRING(((char*)str_00000AA4)))
    BEGIN_INLINE_EVENT
        CALL(tou_champion_belt_28_text_2A10, STRING(((char*)str_0000045C)))
    END_INLINE_EVENT
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    CALL(evt_npc_set_ry, STRING(((char*)str_000001E0)), 270)
    CALL(evt_msg_print, 0, STRING(((char*)str_00001088)), 0, STRING(((char*)str_000001E0)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -475, 134, 533, -475, 38, -8, 0, 0)
    WAIT_MS(3000)
    CALL(evt_cam3d_evt_set, 20, 155, 273, 20, 106, -8, 0, 0)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00001098)), 0, STRING(((char*)str_000001E0)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 80, 155, 273, 80, 106, -8, 1000, 0)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING(((char*)str_000010A8)), 0, STRING(((char*)str_0000045C)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 20, 155, 273, 20, 106, -8, 1000, 0)
    WAIT_MS(1000)
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001E0)), STRING(((char*)str_0000045C)))
    CALL(evt_msg_print, 0, STRING(((char*)str_000010B8)), 0, STRING(((char*)str_000001E0)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 850, 2160, 0, 287, -8, 10000, 0)
    WAIT_MS(7000)
    CALL(evt_fade_set_mapchange_type, 0, 2, 300, 1, 300)
    CALL(evt_bero_mapchange, STRING(((char*)str_00001078)), STRING(((char*)str_000010C8)))
    RETURN
EVT_END()

#ifdef NONMATCHING
void kyaku_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}
#endif

#ifdef NONMATCHING
void ext_kyaku_main(void) {
    pose_main();
}
#endif

#ifdef NONMATCHING
void ext_kyaku_dispent(void) {
    dispEntry(CAMERA_3D, 0.0f, 1, kyaku_disp, NULL);
}
#endif

#ifdef NONMATCHING
static void screen_capture(CameraId cameraId, void* param) {
    GXSetTexCopySrc(0, 0, 0x260, 0x1E0);
    GXSetTexCopyDst(0x130, 0xF0, GX_TF_RGB565, GX_TRUE);
    GXCopyTex(screen_wp->buf, GX_FALSE);
    GXPixModeSync();
    screen_wp->ready = 1;
}
#endif

#ifdef NONMATCHING
s32 screen_init(EventEntry* event, BOOL isFirstCall) {
    u32 size = GXGetTexBufferSize(0x260, 0x1E0, GX_TF_I4, GX_FALSE, 0);

    screen_wp = _mapAlloc(sizeof(ScreenWork));
    screen_wp->buf = _mapAlloc(size);
    screen_wp->ready = 0;
    screen_wp->scale = screen_wp->scaleTarget = 1.0f;
    screen_wp->x = screen_wp->xTarget = 0.0f;
    screen_wp->y = screen_wp->yTarget = 0.0f;
    screen_wp->count = 0;
    screen_wp->field_0x28 = -1.0f;
    screen_wp->noise = _mapAlloc(GXGetTexBufferSize(64, 64, GX_TF_I8, GX_FALSE, 0));
    if (evtGetValue(event, GSW(0)) == 163) {
        screen_wp->mode = 1;
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
static s32 screen_evt(EventEntry* event, BOOL isFirstCall) {
    dispEntry(CAMERA_2D, 1000.0f, 0, screen_capture, NULL);
    return EVT_RETURN_BLOCK;
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
void GXSetTexCoordGen(GXTexCoordID dst, GXTexGenType func, GXTexGenSrc src, u32 mtx) {
    GXSetTexCoordGen2(dst, func, src, mtx, GX_FALSE, GX_PTIDENTITY);
}
#endif
#pragma dont_inline reset

#ifdef NONMATCHING
void screen_tev(MapTevCallbackInfo* info) {
    GXTexObj tex;
    Mtx mtx;
    Mtx scale;
    Mtx trans;
    s32 by;
    s32 ry;
    u8* buf;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 len;
    s32 off;
    s32 start;
    u8 col;
    s32 y0;
    s32 y1;
    f32 lim;
    f32 x;
    f32 y;
    CameraEntry* cam;

    if (screen_wp->ready) {
        if (screen_wp->mode) {
            buf = screen_wp->noise;
            for (i = 0; i < 64; i++) {
                by = i / 4;
                ry = i % 4;
                for (j = 0; j < 64; j++) {
                    off = (j / 8) * 32 + (by << 8); off += j % 8; off += (ry << 3); buf[off] = (i & 1) ? 0xFF : 0;
                }
                n = rand() % 100 + 100;
                y0 = by * 256;
                y1 = ry * 8;
                for (k = 0; k < n; k++) {
                    len = rand() % 4 + 2;
                    start = rand() % (65 - len);
                    col = rand() % 256;
                    for (j = start; j < start + len; j++) {
                        off = j / 8 * 32; off = off + y0; off += j % 8; off += y1; buf[off] = col;
                    }
                }
            }
            DCFlushRange(buf, 0x1000);
            GXInitTexObj(&tex, buf, 64, 64, GX_TF_I8, GX_REPEAT, GX_REPEAT, GX_FALSE);
            GXInitTexObjLOD(&tex, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            GXLoadTexObj(&tex, GX_TEXMAP0);
        } else {
            GXInitTexObj(&tex, screen_wp->buf, 0x130, 0xF0, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&tex, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        }
        GXLoadTexObj(&tex, GX_TEXMAP0);
        GXInitTexObj(&tex, inta_tex, 4, 8, GX_TF_I4, GX_REPEAT, GX_REPEAT, GX_FALSE);
        GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&tex, GX_TEXMAP1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_CPREV, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
        if (screen_wp->mode == 0) {
            screen_wp->count++;
            if (screen_wp->count % 200 == 0) {
                switch (rand() % 3) {
                    case 0:
                        screen_wp->xTarget = randf(0.0f, (1.0f - screen_wp->scale) / screen_wp->scale);
                        screen_wp->yTarget = randf(0.0f, (1.0f - screen_wp->scale) / screen_wp->scale);
                        break;
                    case 1:
                        screen_wp->scaleTarget = randf(1.0f, 0.25f);
                        break;
                    case 2:
                        break;
                }
            }
            screen_wp->scale += (screen_wp->scaleTarget - screen_wp->scale) / 60.0f;
            screen_wp->x += (screen_wp->xTarget - screen_wp->x) / 60.0f;
            screen_wp->y += (screen_wp->yTarget - screen_wp->y) / 60.0f;
            PSMTXScale(scale, screen_wp->scale, screen_wp->scale, 1.0f);
            lim = (1.0f - screen_wp->scale) / screen_wp->scale;
            y = screen_wp->y > lim ? lim : screen_wp->y;
            if (screen_wp->x > lim) {
                x = lim;
            } else {
                x = screen_wp->x;
            }
            PSMTXTrans(trans, x, y, 0.0f);
            PSMTXConcat(scale, trans, mtx);
        } else {
            PSMTXScale(mtx, 4.75f, 3.75f, 0.0f);
        }
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0);
        GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
        cam = camGetPtr(CAMERA_3D);
        x = 100.0f - cam->cameraPos.z;
        PSMTXScale(mtx, 1.0f, 6.0f * (x / 1000.0f) + 16.0f, 1.0f);
        GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1);
        GXLoadTexMtxImm(mtx, GX_TEXMTX1, GX_MTX2x4);
        info->tevStage = 2;
        info->texMap = 2;
        info->texCoord = 2;
    }
}
#endif

#ifdef NONMATCHING
s32 tribe_chk(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    const char* tribe = (const char*)evtGetValue(event, args[1]);

    if (strcmp(npcNameToPtr(name)->tribe->nameJp, tribe) == 0) {
        evtSetValue(event, args[2], 1);
    } else {
        evtSetValue(event, args[2], 0);
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 burst_chain(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 id = evtGetValue(event, args[1]);
    NpcEntry* npc = npcNameToPtr(name);
    NpcEntry* a;
    NpcEntry* b;
    char buf[32];
    s32 i;
    f32 t;
    f32 dist;

    sprintf(buf, "\215\275%d_%d", id, 0);
    npcNameToPtr(buf)->position = npc->position;
    for (i = 0; i < 4; i++) {
        sprintf(buf, "\215\275%d_%d", id, i);
        a = npcNameToPtr(buf);
        sprintf(buf, "\215\275%d_%d", id, i + 1);
        b = npcNameToPtr(buf);
        b->position.y -= 3.0f;
        dist = PSVECDistance(&a->position, &b->position);
        t = 1.0f - 10.0f / dist;
        b->position.x += t * (a->position.x - b->position.x);
        b->position.y += t * (a->position.y - b->position.y);
        b->position.z += t * (a->position.z - b->position.z);
        if (b->position.x > 210.0f || b->position.x < -210.0f) {
            if (b->position.y < 0.0f) {
                b->position.y = 0.0f;
            }
        } else {
            if (b->position.y < 60.0f) {
                b->position.y = 60.0f;
            }
        }
    }
    return EVT_RETURN_BLOCK;
}
#endif

#ifdef NONMATCHING
s32 snd_sfx_stop(EventEntry* event, BOOL isFirstCall) {
    psndMapChange();
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 confupose(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    NpcEntry* npc = npcNameToPtr((const char*)evtGetValue(event, args[0]));

    evtSetValue(event, args[1], (s32)npc->tribe->confuseAnimation);
    return EVT_RETURN_DONE;
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
static f32 sinf(f32 x) {
    return sin(x);
}
#endif
#pragma dont_inline reset

#pragma dont_inline on
#ifdef NONMATCHING
static f32 cosf(f32 x) {
    return cos(x);
}
#endif
#pragma dont_inline reset

#ifdef NONMATCHING
static inline s32 item_jump_sub(EventEntry* event, BOOL isFirstCall, f32 speed, f32 g) {
    s32* args = event->args;
    f32 z;
    f32 y;
    f32 x;
    ItemEntry* item;
    f32 angle;
    f32 dy;
    f32 t;
    f32 vy;

    x = evtGetFloat(event, args[0]);
    y = evtGetFloat(event, args[1]);
    z = evtGetFloat(event, args[2]);
    item = itemNameToPtr("stone");
    if (isFirstCall) {
        dy = y - item->position.y;
        t = distABf(x, z, item->position.x, item->position.z) / speed;
        vy = dy / t + 0.5f * t * g;
        angle = angleABf(item->position.x, item->position.z, x, z);
        event->userdata[0] = *(s32*)&t;
        event->userdata[1] = *(s32*)&vy;
        event->userdata[2] = *(s32*)&angle;
    }
    t = event->userdataf[0];
    vy = event->userdataf[1];
    angle = event->userdataf[2];
    item->position.x += speed * sinf(6.2831855f * angle / 360.0f);
    item->position.z -= speed * cosf(6.2831855f * angle / 360.0f);
    item->position.y += vy;
    vy -= g;
    t -= speed;
    if (t < 0.0f) {
        item->position.x = x;
        item->position.y = y;
        item->position.z = z;
        {
            Vec zero = {0.0f, 0.0f, 0.0f};
            Vec tmp = {0.0f, 0.0f, 0.0f};
            Vec pos;

            tmp.x = item->position.x;
            tmp.y = item->position.y;
            tmp.z = item->position.z;
            pos = tmp;
            psndSFXOn_3D("SFX_EVT_STARSTONE_JUMP1", &pos);
        }
        return 1;
    }
    event->userdata[0] = *(s32*)&t;
    event->userdata[1] = *(s32*)&vy;
    return EVT_RETURN_BLOCK;
}
#endif

#ifdef NONMATCHING
s32 item_jump(EventEntry* event, BOOL isFirstCall) {
    return item_jump_sub(event, isFirstCall, 1.0f, 0.5f);
}
#endif

__declspec(section ".data") s32 block_data[] = {
    (s32)((char*)str_000010E8), (s32)((char*)str_000010F0), (s32)((char*)str_000010F8), (s32)((char*)str_00001100), (s32)((char*)str_00001108), (s32)((char*)str_00001110), (s32)((char*)str_00001118), (s32)((char*)str_00001120),
    (s32)((char*)str_00001128),
};

static EVT_BEGIN(evt_shake)
    LOOP(0)
        CALL(evt_npc_get_position, STRING(((char*)str_000001E0)), LW(0), LW(1), LW(2))
        ADD(LW(0), 2)
        CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), LW(0), LW(1), LW(2))
        WAIT_FRAMES(2)
        CALL(evt_npc_get_position, STRING(((char*)str_000001E0)), LW(0), LW(1), LW(2))
        ADD(LW(0), -2)
        CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), LW(0), LW(1), LW(2))
        WAIT_FRAMES(2)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_boss_stone)
    SET_VALUE(LW(10), 0)
    CALL(evt_item_entry, STRING(((char*)str_00001130)), 116, 0, 0, 0, 17, -1, 0)
    LOOP(0)
        CALL(evt_mapobj_get_position, STRING(((char*)str_00001138)), LW(0), LW(1), LW(2))
        ADD_FLOAT(LW(1), FLOAT(20.0f))
        CALL(evt_sub_get_sincos, LW(10), LW(11), LW(12))
        MULTIPLY_FLOAT(LW(12), FLOAT(10.0f))
        ADD(LW(1), LW(12))
        ADD(LW(10), FLOAT(2.5f))
        MODULO(LW(10), 360)
        IF_INT_LESS(LW(1), 50)
            CALL(starstone_sound_onoff, 0)
            ELSE
            CALL(starstone_sound_onoff, 1)
        END_IF
        CALL(evt_item_set_position, STRING(((char*)str_00001130)), LW(0), LW(1), LW(2))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

#ifdef NONMATCHING
s32 getY(EventEntry* event, BOOL isFirstCall) {
    NpcEntry* npc = npcNameToPtr("\203K\203\223\203X");
    MapObject* obj = mapGetMapObj("block_5");
    Vec pos;
    f32 y;

    mapObjGetPos("group151", &pos);
    y = 100.0f + obj->modelWorldMtx[1][3];
    if (y > pos.y) {
        npc->position.y = y;
    } else {
        npc->position.x = npc->position.z = 0.0f;
        npc->position.y = pos.y;
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 starstone_sound_onoff(EventEntry* event, BOOL isFirstCall) {
    s32 flag = evtGetValue(event, event->args[0]);
    EffectEntry* eff = itemNameToPtr("stone")->effect;

    if (eff) {
        if (flag == 0) {
            ((StoneEffWork3*)eff->userdata)->flags &= ~4;
        }
        if (flag == 1) {
            ((StoneEffWork3*)eff->userdata)->flags |= 4;
        }
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 evt_boss_stone_r(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    EffectEntry* eff = itemNameToPtr("stone")->effect;

    ((StoneEffWork2*)eff->userdata)->rot = evtGetFloat(event, args[0]);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 eff_pos(EventEntry* event, BOOL isFirstCall) {
    ItemEntry* item = itemNameToPtr("stone");
    EffectEntry* eff1 = effNameToPtr("eff_1");
    EffectEntry* eff2 = effNameToPtr("eff_2");

    if (item) {
        if (eff1) {
            ((StoneEffWork*)eff1->userdata)->pos.x = item->position.x;
            ((StoneEffWork*)eff1->userdata)->pos.y = 15.0f + item->position.y;
            ((StoneEffWork*)eff1->userdata)->pos.z = item->position.z;
        }
        if (eff2) {
            ((StoneEffWork*)eff2->userdata)->pos.x = item->position.x;
            ((StoneEffWork*)eff2->userdata)->pos.y = 15.0f + item->position.y;
            ((StoneEffWork*)eff2->userdata)->pos.z = item->position.z;
        }
    }
    return EVT_RETURN_BLOCK;
}
#endif

#ifdef NONMATCHING
static inline void cb_set_color(u8 a) {
    GXColor color = {255, 255, 255, 0};

    color.a = a;
    GXSetTevColor(GX_TEVREG0, color);
}
#endif

#ifdef NONMATCHING
static void callback(MapTevCallbackInfo* info) {
    s32 stage = info->tevStage;
    s32 texCoord = info->texCoord;
    s32 texMap = info->texMap;
    s32 field_0x18 = info->indStage;

    cb_set_color(gans_alpha);
    GXSetTevOrder(stage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(stage, GX_CC_CPREV, GX_CC_C0, GX_CC_A0, GX_CC_ZERO);
    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevSwapMode(stage, GX_TEV_SWAP0, GX_TEV_SWAP0);
    info->tevStage = stage + 1;
    info->texMap = texMap;
    info->indStage = field_0x18;
    info->texCoord = texCoord;
}
#endif

#ifdef NONMATCHING
s32 gans_white_on(EventEntry* event, BOOL isFirstCall) {
    NpcEntry* npc = npcNameToPtr("\203K\203\223\203X");

    if (isFirstCall) {
        gans_alpha = 0;
        mapSetTevCallback(12, callback);
        animPoseSetMaterialFlagOn(npc->poseId, 0xC000000);
    }
    gans_alpha += 5;
    if (gans_alpha > 255) {
        gans_alpha = 255;
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
#endif

#ifdef NONMATCHING
s32 gans_white_off(EventEntry* event, BOOL isFirstCall) {
    NpcEntry* npc = npcNameToPtr("\203K\203\223\203X");

    mapSetTevCallback(12, NULL);
    animPoseSetMaterialFlagOff(npc->poseId, 0xC000000);
    return EVT_RETURN_DONE;
}
#endif

static EVT_BEGIN(evt_boss)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_0000114C)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)str_00001154)), 0, 0)
    SET_VALUE(LW(0), STRING(((char*)str_00000144)))
    CALL_CHILD(PTR(bero_case_switch_off))
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), 0, 60, 0)
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001E0)), STRING(((char*)str_0000078C)))
    CALL(evt_npc_set_tribe, STRING(((char*)str_000001E0)), STRING(((char*)str_000001E0)))
    SPAWN_EVENT_GET_ID(PTR(evt_boss_stone), GW(10))
    WAIT_FRAMES(2)
    SET_VALUE(GW(12), 1000)
    BEGIN_INLINE_EVENT_GET_ID(GW(11))
        LOOP(0)
            CALL(evt_sub_intpl_msec_init, 0, 0, 360, GW(12))
            LOOP(0)
                CALL(evt_sub_intpl_msec_get_value)
                CALL(evt_boss_stone_r, LW(0))
                WAIT_FRAMES(1)
                IF_INT_EQUAL(LW(1), 0)
                    BREAK_LOOP
                END_IF
            END_LOOP
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
    LOOP(0)
        CALL(evt_mario_get_name_hitobj_ride, LW(9))
        IF_STR_EQUAL(LW(9), STRING(((char*)str_00001160)))
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_cam3d_evt_set, 0, 197, 484, 0, 110, -8, 2000, 11)
    CALL(evt_mario_mov_pos2, -75, 0, FLOAT(60.0f))
    CALL(evt_mario_set_dir, 90, 200, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_party_set_dir, 0, 90, 200)
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00001168)))
    CALL(evt_msg_print, 0, STRING(((char*)str_0000117C)), 0, STRING(((char*)str_000001E0)))
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_sfxon, STRING(((char*)str_0000118C)), LW(10))
        CALL(evt_cam_shake, 4, FLOAT(0.0029296875f), FLOAT(0.0029296875f), 13000)
        CALL(evt_snd_sfxoff, LW(10))
    END_INLINE_EVENT
    WAIT_MS(1000)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000820)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)str_0000056C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
    IF_INT_GREATER(LW(1), 50)
        CALL(evt_eff_fukidashi, 3, STRING(((char*)str_000011A4)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    END_IF
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_set_pose, STRING(((char*)str_0000083C)))
    CALL(evt_cam3d_evt_set, 0, 242, 821, 0, 96, -8, 3000, 11)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, -180, 0, FLOAT(60.0f))
        CALL(evt_party_set_dir, 0, 90, 200)
        CALL(evt_party_stop, 0)
    END_INLINE_EVENT
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_mario_jump_pos, -150, 60, 0, 500, 0, -1000)
    CALL(evt_mario_set_dir, 90, 200, 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000011A8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000011B0)), 1)
    CALL(evt_map_playanim, STRING(((char*)str_000011B8)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_000011C0)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_000011CC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_000011D4)), 0, 0)
    CALL(evt_map_playanim, STRING(((char*)str_000011DC)), 1, 0)
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_map_pauseanim, 0, STRING(((char*)str_000011D4)))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000011E4)), 0, 60, 0, LW(10))
        WAIT_MS(2000)
        CALL(evt_map_replayanim, 0, STRING(((char*)str_000011D4)))
        CALL(evt_map_checkanim, STRING(((char*)str_000011D4)), LW(0), LW(1))
        SUBTRACT(LW(1), 100)
        WAIT_MS(LW(1))
        CALL(evt_snd_sfxoff, LW(10))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001200)), 0, 60, 0, 0)
    END_INLINE_EVENT
    SET_INT_READ_ADDR(PTR(block_data))
    LOOP(9)
        READ_INT(LW(5))
        BEGIN_INLINE_EVENT
            CALL(evt_mapobj_get_position, LW(5), LW(0), LW(1), LW(2))
            LOOP(0)
                CALL(evt_mapobj_get_position, LW(5), LW(10), LW(11), LW(12))
                IF_INT_NOT_EQUAL(LW(1), LW(11))
                    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001220)), LW(10), LW(11), LW(12), 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_LOOP
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_000001E0)), 1024)
    LOOP(0)
        CALL(evt_map_checkanim, STRING(((char*)str_000011D4)), LW(0), LW(1))
        IF_INT_EQUAL(LW(0), 1)
            BREAK_LOOP
        END_IF
        CALL(getY)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000001E0)), 1024)
    CALL(evt_hitobj_onoff, STRING(((char*)str_00001234)), 1, 1)
    WAIT_MS(1000)
    CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
    IF_INT_GREATER(LW(1), 50)
        CALL(evt_eff_fukidashi, 3, STRING(((char*)str_000011A4)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    END_IF
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 0, 305, 384, 0, 325, -15, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print_party, STRING(((char*)str_0000123C)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 155, 288, 0, 105, -8, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_0000124C)), 0, STRING(((char*)str_000001E0)))
    WAIT_MS(300)
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_set_pose, STRING(((char*)str_00000580)))
    CALL(evt_party_set_pos, 0, -180, 60, 0)
    CALL(evt_party_stop, 0)
    WAIT_FRAMES(1)
    CALL(evt_cam3d_evt_set, -150, 155, 288, -150, 105, -8, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING(((char*)str_0000125C)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 155, 288, 0, 105, -8, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_0000126C)), 0, STRING(((char*)str_000001E0)))
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_0000127C)))
        WAIT_MS(333)
        CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00001280)))
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SET_VALUE(GF(10), 0)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001284)), 0, 60, 0, LW(9))
        LOOP(0)
            CALL(evt_sub_intpl_msec_init, 11, 0, 2000, 500)
            LOOP(0)
                CALL(evt_sub_intpl_msec_get_value)
                CALL(evt_snd_sfx_pit, LW(9), LW(0))
                WAIT_FRAMES(1)
                IF_INT_EQUAL(LW(1), 0)
                    BREAK_LOOP
                END_IF
            END_LOOP
            CALL(evt_sub_intpl_msec_init, 11, 2000, 0, 500)
            LOOP(0)
                CALL(evt_sub_intpl_msec_get_value)
                CALL(evt_snd_sfx_pit, LW(9), LW(0))
                WAIT_FRAMES(1)
                IF_INT_EQUAL(LW(1), 0)
                    BREAK_LOOP
                END_IF
            END_LOOP
            IF_INT_EQUAL(GF(10), 1)
                BREAK_LOOP
            END_IF
        END_LOOP
        CALL(evt_sub_intpl_msec_init, 11, 90, 0, 1000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_snd_sfx_vol, LW(9), LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
        CALL(evt_snd_sfxoff, LW(9))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 0, 100, 800, 5000)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        CALL(evt_map_set_playrate, STRING(((char*)str_000011B8)), LW(0))
        CALL(evt_map_set_playrate, STRING(((char*)str_000011CC)), LW(0))
        CALL(evt_map_set_playrate, STRING(((char*)str_000011C0)), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
    END_INLINE_EVENT
    SPAWN_EVENT_GET_ID(PTR(evt_shake), LW(9))
    CALL(evt_cam3d_evt_set, 0, 142, 215, 0, 105, -8, 5000, 11)
    WAIT_MS(5000)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_get_position, STRING(((char*)str_000001E0)), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_0000129C)), LW(10), LW(11), LW(12), 0)
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000224)))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 100, 200, 300)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            CALL(evt_npc_set_scale, STRING(((char*)str_000001E0)), LW(0), LW(0), LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 170, 385, 0, 135, -11, 300, 11)
    WAIT_MS(300)
    CALL(gans_white_on)
    CALL(evt_paper_entry, STRING(((char*)str_000012B0)))
    CALL(evt_npc_get_position, STRING(((char*)str_000001E0)), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING(((char*)str_000002B0)), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_ry, STRING(((char*)str_000002B0)), 270)
    CALL(evt_npc_set_width, STRING(((char*)str_000002B0)), 60)
    CALL(evt_npc_set_height, STRING(((char*)str_000002B0)), 80)
    CALL(evt_snd_sfxon, STRING(((char*)str_000012BC)), 0)
    CALL(evt_npc_set_paper, STRING(((char*)str_000001E0)), STRING(((char*)str_000012B0)))
    CALL(evt_npc_set_paper_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_000012D0)))
    WAIT_MS(2500)
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), 0, -1000, 0)
    CALL(evt_npc_clear_paper, STRING(((char*)str_000001E0)))
    CALL(gans_white_off)
    DELETE_EVENT(LW(9))
    CALL(evt_msg_print, 0, STRING(((char*)str_000012D4)), 0, STRING(((char*)str_000002B0)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -150, 155, 288, -150, 105, -8, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_pose, STRING(((char*)str_000012E4)))
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_mario_jump_pos, LW(0), LW(1), LW(2), 300, 0, -1000)
    CALL(evt_msg_print_party, STRING(((char*)str_000012EC)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 170, 385, 0, 135, -11, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_000012FC)), 0, STRING(((char*)str_000002B0)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 210, 852, 0, 135, -12, 1000, 11)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_npc_set_battle_info, STRING(((char*)str_000002B0)), 23)
    CALL(evt_npc_battle_start, STRING(((char*)str_000002B0)))
    CALL(evt_npc_wait_battle_end)
    CALL(evt_snd_sfxon, STRING(((char*)str_0000130C)), LW(15))
    CALL(evt_snd_sfx_vol, LW(15), 38)
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_mario_set_pose, STRING(((char*)str_000005B8)))
    CALL(evt_party_stop, 0)
    CALL(evt_npc_get_position, STRING(((char*)str_000002B0)), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING(((char*)str_000002B0)), 0, -1000, 0)
    CALL(evt_npc_set_scale, STRING(((char*)str_000001E0)), FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00001324)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)str_000001E0)), STRING(((char*)str_00001324)), STRING(((char*)str_00001328)))
    CALL(evt_cam3d_evt_set, 0, 140, 385, 0, 105, -11, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_0000132C)), 0, STRING(((char*)str_000001E0)))
    WAIT_MS(300)
    SET_VALUE(GF(10), 1)
    CALL(evt_cam3d_evt_set, -130, 140, 385, -130, 105, -11, 700, 11)
    WAIT_MS(700)
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_snd_bgmon_f, 768, STRING(((char*)str_0000133C)), 3000)
    END_INLINE_EVENT
    CALL(evt_npc_set_position, STRING(((char*)str_0000028C)), -325, 0, 0)
    CALL(evt_npc_status_onoff, 1, STRING(((char*)str_0000028C)), 2)
    CALL(evt_msg_print, 0, STRING(((char*)str_0000134C)), 0, STRING(((char*)str_0000028C)))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_0000135C)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)str_0000056C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, STRING(((char*)str_000011A4)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1500)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 270, 200, 0)
    END_INLINE_EVENT
    CALL(evt_party_set_dir, 0, 270, 200)
    CALL(evt_cam3d_evt_set, -320, 95, 287, -320, 40, -8, 1000, 11)
    WAIT_MS(1000)
    WAIT_MS(333)
    CALL(evt_msg_print, 0, STRING(((char*)str_00001374)), 0, STRING(((char*)str_0000028C)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -160, 150, 288, -160, 100, -8, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print_party, STRING(((char*)str_00001384)))
    CALL(evt_cam3d_evt_set, -200, 222, 682, -200, 100, -8, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(333)
    CALL(evt_msg_print, 0, STRING(((char*)str_00001394)), 0, STRING(((char*)str_0000028C)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -320, 95, 287, -320, 40, -8, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(333)
    CALL(evt_msg_print, 0, STRING(((char*)str_000013A4)), 0, STRING(((char*)str_0000028C)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -160, 150, 288, -160, 100, -8, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print_party, STRING(((char*)str_000013B4)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -320, 95, 287, -320, 40, -8, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(333)
    CALL(evt_msg_print, 0, STRING(((char*)str_000013C4)), 0, STRING(((char*)str_0000028C)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -25, 197, 574, -25, 105, -8, 3000, 11)
    CALL(evt_npc_move_position, STRING(((char*)str_0000028C)), -280, 20, 0, FLOAT(60.0f), 1)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000028C)), -250, 20, 20, 500, 30)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000028C)), -215, 40, 20, 500, 30)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000028C)), -185, 60, 20, 500, 30)
    CALL(evt_npc_move_position, STRING(((char*)str_0000028C)), -135, 80, 0, FLOAT(60.0f), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 90, 300, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 90, 300)
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING(((char*)str_0000028C)), -50, 75, 0, FLOAT(60.0f), 1)
    CALL(evt_msg_print, 0, STRING(((char*)str_000013D4)), 0, STRING(((char*)str_0000028C)))
    WAIT_MS(300)
    WAIT_MS(333)
    CALL(evt_msg_print, 0, STRING(((char*)str_000013E8)), 0, STRING(((char*)str_000001E0)))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)str_000013FC)), 0, STRING(((char*)str_0000028C)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -160, 150, 288, -160, 100, -8, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print_party, STRING(((char*)str_00001410)))
    WAIT_MS(300)
    BEGIN_INLINE_EVENT_GET_ID(LW(10))
        CALL(eff_pos)
    END_INLINE_EVENT
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), 30)
    ADD(LW(1), 30)
    CALL(evt_eff64, STRING(((char*)str_00001424)), STRING(((char*)str_00001428)), 1, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(300)
    CALL(evt_eff_fukidashi, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1500)
    CALL(evt_msg_print_party, STRING(((char*)str_00001438)))
    CALL(evt_mapobj_get_position, STRING(((char*)str_00001138)), LW(0), LW(1), LW(2))
    ADD_FLOAT(LW(1), FLOAT(40.0f))
    CALL(evt_eff64, STRING(((char*)str_00001450)), STRING(((char*)str_00001458)), 11, LW(0), LW(1), LW(2), FLOAT(1.0f), 270, 0, 0, 0, 0, 0, 0)
    WAIT_MS(300)
    CALL(evt_snd_sfxon, STRING(((char*)str_0000146C)), 0)
    CALL(evt_snd_sfx_vol, LW(15), 161)
    CALL(evt_cam3d_evt_set, 0, 400, 357, 0, 325, -8, 0, 11)
    CALL(evt_eff_delete, STRING(((char*)str_00001424)))
    WAIT_FRAMES(1)
    SET_VALUE(GW(12), 650)
    WAIT_MS(600)
    SET_VALUE(GW(12), 400)
    WAIT_MS(350)
    SET_VALUE(GW(12), 250)
    WAIT_MS(250)
    CALL(evt_mapobj_get_position, STRING(((char*)str_00001138)), LW(0), LW(1), LW(2))
    ADD_FLOAT(LW(1), FLOAT(40.0f))
    CALL(evt_eff64, STRING(((char*)str_00001488)), STRING(((char*)str_00001458)), 4, LW(0), LW(1), LW(2), FLOAT(1.0f), 180, 0, 0, 0, 0, 0, 0)
    WAIT_MS(2000)
    CALL(evt_npc_set_scale, STRING(((char*)str_000002C0)), FLOAT(0.0f), FLOAT(0.0f), FLOAT(0.0f))
    CALL(evt_mapobj_get_position, STRING(((char*)str_00001138)), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING(((char*)str_000002C0)), LW(0), LW(1), LW(2))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_000002C0)), 1024)
        CALL(evt_sub_intpl_msec_init, 11, 0, 1800, 3000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_npc_set_rotate, STRING(((char*)str_000002C0)), FLOAT(0.0f), LW(0), FLOAT(0.0f))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000002C0)), 1024)
        CALL(evt_npc_set_rotate, STRING(((char*)str_000002C0)), FLOAT(0.0f), FLOAT(0.0f), FLOAT(0.0f))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 100, 300)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            CALL(evt_npc_set_scale, STRING(((char*)str_000002C0)), LW(0), LW(0), LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000002C0)), 100, 60, 75, 800, 170)
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), 127)
        LOOP(10)
            ADD(LW(0), -8)
            CALL(evt_snd_sfx_vol, LW(15), LW(0))
            WAIT_MS(100)
        END_LOOP
        CALL(evt_snd_sfx_vol, LW(15), 38)
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 100, 166, 536, 100, 90, -8, 1000, 11)
    WAIT_MS(1000)
    WAIT_MS(2000)
    WAIT_MS(400)
    CALL(evt_cam3d_evt_set, 100, 133, 339, 100, 85, -8, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING(((char*)str_00001490)), 0, STRING(((char*)str_000002C0)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -75, 133, 339, -75, 85, -8, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_000014A4)), 0, STRING(((char*)str_0000028C)))
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)str_0000028C)), 75, 75, 0, FLOAT(100.0f), 1)
    END_INLINE_EVENT
    WAIT_MS(200)
    CALL(evt_cam3d_evt_set, 88, 133, 339, 88, 85, -8, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_set_dir_to_target, STRING(((char*)str_000002C0)), STRING(((char*)str_0000028C)))
    CALL(evt_msg_print, 0, STRING(((char*)str_000014B8)), 0, STRING(((char*)str_000002C0)))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_000014CC)), 0, STRING(((char*)str_0000028C)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -160, 150, 288, -160, 100, -8, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print_party, STRING(((char*)str_000014E0)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 356, 1016, 25, 180, 32, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_npc_move_position, STRING(((char*)str_0000028C)), 75, 75, 0, FLOAT(60.0f), 1)
    WAIT_MS(333)
    CALL(evt_set_dir_to_target, STRING(((char*)str_0000028C)), STRING(((char*)str_0000078C)))
    CALL(evt_msg_print, 0, STRING(((char*)str_000014F4)), 0, STRING(((char*)str_0000028C)))
    WAIT_MS(300)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(evt_snd_sfxon, STRING(((char*)str_00001504)), 0)
    CALL(evt_npc_set_anim, STRING(((char*)str_0000028C)), STRING(((char*)str_000012D0)))
    WAIT_MS(500)
    CALL(evt_map_pauseanim, 0, STRING(((char*)str_000011DC)))
    CALL(evt_sub_intpl_msec_init, 0, 800, 0, 5000)
    LABEL(10)
    CALL(evt_sub_intpl_msec_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
    CALL(evt_map_set_playrate, STRING(((char*)str_000011B8)), LW(0))
    CALL(evt_map_set_playrate, STRING(((char*)str_000011CC)), LW(0))
    CALL(evt_map_set_playrate, STRING(((char*)str_000011C0)), LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(10)
    END_IF
    CALL(evt_map_pauseanim, 0, STRING(((char*)str_000011B8)))
    CALL(evt_map_pauseanim, 0, STRING(((char*)str_000011C0)))
    CALL(evt_map_pauseanim, 0, STRING(((char*)str_000011CC)))
    DELETE_EVENT(GW(11))
    DELETE_EVENT(GW(10))
    CALL(evt_boss_stone_r, FLOAT(0.0f))
    CALL(item_jump, FLOAT(0.0f), FLOAT(200.0f), FLOAT(60.0f))
    CALL(item_jump, FLOAT(0.0f), FLOAT(60.0f), FLOAT(100.0f))
    CALL(item_jump, FLOAT(0.0f), FLOAT(60.0f), FLOAT(100.0f))
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, -160, 150, 288, -160, 100, -8, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING(((char*)str_00001520)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 88, 133, 339, 88, 85, -8, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)str_00001530)), 0, STRING(((char*)str_0000028C)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -160, 150, 288, -160, 100, -8, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print_party, STRING(((char*)str_00001540)))
    WAIT_MS(300)
    CALL(evt_mario_set_dir, 270, 300, 0)
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001550)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_00001568)))
    WAIT_MS(500)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_party_run, 0)
    CALL(evt_cam3d_evt_set, 0, 200, 584, 0, 100, -8, 2000, 11)
    CALL(evt_mario_mov_pos2, 0, 75, FLOAT(60.0f))
    SET_VALUE(GSW(0), 164)
    SET_VALUE(LW(0), 3)
    SET_VALUE(LW(1), STRING(((char*)str_00001130)))
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_snd_bgmoff, 513)
    CALL_CHILD(PTR(evt_sub_starstone))
    RETURN
EVT_END()

EVT_BEGIN(evt_watch_match)
    IF_INT_LESS(GSW(0), 172)
        CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), 0, 60, -130)
        ELSE
        CALL(evt_npc_set_position, STRING(((char*)str_0000028C)), 0, 60, -130)
    END_IF
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00000434)), 32)
    LOOP(0)
        CALL(evt_sub_random, 3, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL(evt_npc_move_position, STRING(((char*)str_00000434)), -30, 0, 0, FLOAT(200.0f), 0)
            CALL(evt_npc_jump_position_nohit, STRING(((char*)str_00000434)), 20, 60, 0, 500, 30)
            CALL(evt_npc_jump_position_nohit, STRING(((char*)str_00000434)), 80, 70, 0, 500, 60)
            CALL(evt_eff, 0, STRING(((char*)str_000001CC)), 0, 80, 80, 0, FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
            CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001570)), 80, 80, 0, 0)
            CALL(evt_npc_jump_position_nohit, STRING(((char*)str_00000434)), 60, 60, 0, 500, 30)
            CALL(evt_npc_jump_position_nohit, STRING(((char*)str_00000434)), 30, 60, 0, 300, 20)
            CALL(evt_npc_move_position, STRING(((char*)str_00000434)), -80, 0, 0, FLOAT(200.0f), 0)
            CALL(evt_npc_move_position, STRING(((char*)str_0000043C)), 30, 0, 0, FLOAT(200.0f), 0)
            CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000043C)), -20, 60, 0, 500, 30)
            CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000043C)), -80, 70, 0, 500, 60)
            CALL(evt_eff, 0, STRING(((char*)str_000001CC)), 0, -80, 80, 0, FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
            CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001570)), -80, 80, 0, 0)
            CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000043C)), -60, 60, 0, 500, 30)
            CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000043C)), -30, 60, 0, 300, 20)
            CALL(evt_npc_move_position, STRING(((char*)str_0000043C)), 80, 0, 0, FLOAT(200.0f), 0)
            CASE_EQUAL(1)
            BEGIN_INLINE_EVENT_GET_ID(LW(12))
                CALL(evt_npc_move_position, STRING(((char*)str_00000434)), -10, 0, 300, 0, 0)
            END_INLINE_EVENT
            CALL(evt_npc_move_position, STRING(((char*)str_0000043C)), 10, 0, 300, 0, 0)
            CALL(evt_eff, 0, STRING(((char*)str_000001CC)), 1, 0, 80, 0, FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
            CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001570)), 0, 80, 0, 0)
            WAIT_MS(100)
            LOOP(0)
                IS_EVENT_RUNNING(LW(12), LW(13))
                IF_INT_EQUAL(LW(13), 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_random, 4, LW(10))
            ADD(LW(10), 1)
            LOOP(LW(10))
                CALL(evt_sub_random, 100, LW(0))
                IF_INT_LESS(LW(0), 50)
                    BEGIN_INLINE_EVENT_GET_ID(LW(12))
                        CALL(evt_npc_move_position, STRING(((char*)str_00000434)), -140, 0, 800, 0, 0)
                    END_INLINE_EVENT
                    CALL(evt_npc_move_position, STRING(((char*)str_0000043C)), -120, 0, 800, 0, 0)
                    CALL(evt_eff, 0, STRING(((char*)str_000001CC)), 0, -130, 80, 0, FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
                    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001570)), -130, 80, 0, 0)
                    ELSE
                    BEGIN_INLINE_EVENT_GET_ID(LW(12))
                        CALL(evt_npc_move_position, STRING(((char*)str_00000434)), 120, 0, 800, 0, 0)
                    END_INLINE_EVENT
                    CALL(evt_npc_move_position, STRING(((char*)str_0000043C)), 140, 0, 800, 0, 0)
                    CALL(evt_eff, 0, STRING(((char*)str_000001CC)), 0, 130, 80, 0, FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
                    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001570)), 130, 80, 0, 0)
                END_IF
                WAIT_MS(100)
                LOOP(0)
                    IS_EVENT_RUNNING(LW(12), LW(13))
                    IF_INT_EQUAL(LW(13), 0)
                        BREAK_LOOP
                    END_IF
                    WAIT_FRAMES(1)
                END_LOOP
            END_LOOP
            BEGIN_INLINE_EVENT_GET_ID(LW(12))
                CALL(evt_npc_jump_position_nohit, STRING(((char*)str_00000434)), -80, 60, 0, 500, 30)
            END_INLINE_EVENT
            CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000043C)), 80, 60, 0, 500, 30)
            WAIT_MS(100)
            LOOP(0)
                IS_EVENT_RUNNING(LW(12), LW(13))
                IF_INT_EQUAL(LW(13), 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            CASE_DEFAULT
            BEGIN_INLINE_EVENT_GET_ID(LW(12))
                CALL(evt_npc_move_position, STRING(((char*)str_00000434)), -40, 0, 500, 0, 0)
            END_INLINE_EVENT
            CALL(evt_npc_move_position, STRING(((char*)str_0000043C)), 40, 0, 500, 0, 0)
            WAIT_MS(100)
            LOOP(0)
                IS_EVENT_RUNNING(LW(12), LW(13))
                IF_INT_EQUAL(LW(13), 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            BEGIN_INLINE_EVENT_GET_ID(LW(12))
                CALL(evt_npc_jump_position_nohit, STRING(((char*)str_00000434)), -10, 100, 0, 400, 30)
            END_INLINE_EVENT
            CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000043C)), 10, 100, 0, 400, 30)
            CALL(evt_eff, 0, STRING(((char*)str_000001CC)), 2, 0, 120, 0, FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
            CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001570)), 0, 120, 0, 0)
            WAIT_MS(100)
            LOOP(0)
                IS_EVENT_RUNNING(LW(12), LW(13))
                IF_INT_EQUAL(LW(13), 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            BEGIN_INLINE_EVENT_GET_ID(LW(12))
                CALL(evt_npc_jump_position_nohit, STRING(((char*)str_00000434)), -80, 60, 0, 500, 30)
            END_INLINE_EVENT
            CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000043C)), 80, 60, 0, 500, 30)
            WAIT_MS(100)
            LOOP(0)
                IS_EVENT_RUNNING(LW(12), LW(13))
                IF_INT_EQUAL(LW(13), 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
        END_SWITCH
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_kyaku_1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_set_dir_to_target, STRING(((char*)str_00000054)), STRING(((char*)str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)str_00000054)))
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_00001584)), 0, STRING(((char*)str_00000054)))
        CASE_DEFAULT
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        SWITCH(LW(10))
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_00001584)), 0, STRING(((char*)str_00000054)))
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00001594)), 0, STRING(((char*)str_00000054)))
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)str_000015A4)), 0, STRING(((char*)str_00000054)))
        END_SWITCH
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_kyaku_2)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_set_dir_to_target, STRING(((char*)str_0000005C)), STRING(((char*)str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)str_0000005C)))
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_000015B4)), 0, STRING(((char*)str_0000005C)))
        CASE_DEFAULT
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        SWITCH(LW(10))
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_000015B4)), 0, STRING(((char*)str_0000005C)))
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_000015C4)), 0, STRING(((char*)str_0000005C)))
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)str_000015D4)), 0, STRING(((char*)str_0000005C)))
        END_SWITCH
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_kyaku_3)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_set_dir_to_target, STRING(((char*)str_00000064)), STRING(((char*)str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)str_00000064)))
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_000015E4)), 0, STRING(((char*)str_00000064)))
        CASE_DEFAULT
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        SWITCH(LW(10))
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_000015E4)), 0, STRING(((char*)str_00000064)))
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_000015F4)), 0, STRING(((char*)str_00000064)))
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)str_00001604)), 0, STRING(((char*)str_00000064)))
        END_SWITCH
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_kyaku_4)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_set_dir_to_target, STRING(((char*)str_0000006C)), STRING(((char*)str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)str_0000006C)))
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_00001614)), 0, STRING(((char*)str_0000006C)))
        CALL(evt_msg_select, 0, STRING(((char*)str_00001624)))
        CALL(evt_msg_print_add, 0, STRING(((char*)str_00001634)))
        CASE_DEFAULT
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        SWITCH(LW(10))
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_00001614)), 0, STRING(((char*)str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)str_00001624)))
            CALL(evt_msg_print_add, 0, STRING(((char*)str_00001634)))
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00001644)), 0, STRING(((char*)str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)str_00001654)))
            CALL(evt_msg_print_add, 0, STRING(((char*)str_00001664)))
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)str_00001674)), 0, STRING(((char*)str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)str_00001684)))
            CALL(evt_msg_print_add, 0, STRING(((char*)str_00001694)))
        END_SWITCH
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_kyaku_5)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_set_dir_to_target, STRING(((char*)str_00000054)), STRING(((char*)str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)str_00000054)))
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_000016A4)), 0, STRING(((char*)str_00000054)))
        CASE_DEFAULT
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        SWITCH(LW(10))
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_000016A4)), 0, STRING(((char*)str_00000054)))
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_000016B4)), 0, STRING(((char*)str_00000054)))
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)str_000016C4)), 0, STRING(((char*)str_00000054)))
        END_SWITCH
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_kyaku_6)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_set_dir_to_target, STRING(((char*)str_0000005C)), STRING(((char*)str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)str_0000005C)))
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_000016D4)), 0, STRING(((char*)str_0000005C)))
        CASE_DEFAULT
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        SWITCH(LW(10))
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_000016D4)), 0, STRING(((char*)str_0000005C)))
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_000016E4)), 0, STRING(((char*)str_0000005C)))
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)str_000016F4)), 0, STRING(((char*)str_0000005C)))
        END_SWITCH
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_kyaku_7)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_set_dir_to_target, STRING(((char*)str_00000064)), STRING(((char*)str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)str_00000064)))
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_00001704)), 0, STRING(((char*)str_00000064)))
        CASE_DEFAULT
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        SWITCH(LW(10))
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_00001704)), 0, STRING(((char*)str_00000064)))
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00001714)), 0, STRING(((char*)str_00000064)))
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)str_00001724)), 0, STRING(((char*)str_00000064)))
        END_SWITCH
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_kyaku_8)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_set_dir_to_target, STRING(((char*)str_0000006C)), STRING(((char*)str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)str_0000006C)))
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_00001734)), 0, STRING(((char*)str_0000006C)))
        CALL(evt_msg_select, 0, STRING(((char*)str_00001744)))
        CALL(evt_msg_print_add, 0, STRING(((char*)str_00001754)))
        CASE_DEFAULT
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        SWITCH(LW(10))
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_00001734)), 0, STRING(((char*)str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)str_00001744)))
            CALL(evt_msg_print_add, 0, STRING(((char*)str_00001754)))
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00001764)), 0, STRING(((char*)str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)str_00001774)))
            CALL(evt_msg_print_add, 0, STRING(((char*)str_00001784)))
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)str_00001794)), 0, STRING(((char*)str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)str_000017A4)))
            CALL(evt_msg_print_add, 0, STRING(((char*)str_000017B4)))
        END_SWITCH
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(tou_03_init_evt)
    SWITCH(GSW(0))
        CASE_EQUAL(163)
        CALL(evt_snd_bgmoff, 512)
        CALL(evt_snd_envoff, 512)
        CASE_DEFAULT
        BEGIN_INLINE_EVENT
            CALL(evt_snd_envoff, 512)
            WAIT_MS(1000)
            CALL(evt_snd_envon, 272, STRING(((char*)str_000017C4)))
        END_INLINE_EVENT
    END_SWITCH
    CALL(evt_bero_get_entername, LW(0))
    IF_STR_NOT_EQUAL(LW(0), STRING(((char*)str_000000A0)))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000017D4)), 1)
    END_IF
    CALL(evt_map_playanim, STRING(((char*)str_000017D8)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_000017E8)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_000017F0)), 1, 0)
    IF_INT_NOT_EQUAL(GSW(0), 163)
        CALL_CHILD(PTR(evt_kyaku))
        WAIT_FRAMES(1)
    END_IF
    CALL(screen_init)
    BEGIN_INLINE_EVENT
        CALL(screen_evt)
    END_INLINE_EVENT
    WAIT_FRAMES(1)
    CALL(evt_map_set_tevcallback, 1, PTR(screen_tev))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000017F8)), 16777216)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000017F8)), 256)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000011A8)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)str_00001234)), 1, 0)
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_SET(LW(0), 2)
        RETURN
    END_IF
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL_CHILD(PTR(npc_entry))
    SWITCH(GSW(0))
        CASE_LESS(128)
        SET_VALUE(LW(0), PTR(bero_data))
        CALL(evt_bero_get_info)
        CALL_CHILD(PTR(bero_case_entry))
        CASE_DEFAULT
        SET_VALUE(LW(0), PTR(bero_data))
        CALL(evt_bero_get_info)
        CALL_CHILD(PTR(evt_bero_info_run))
    END_SWITCH
    SWITCH(GSW(0))
        CASE_LESS(128)
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000ABC)))
        CALL(evt_snd_bgmon, 160, 0)
        SPAWN_EVENT(PTR(evt_tougi))
        CASE_EQUAL(163)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000000F8)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000104)), 1)
        SET_VALUE(LW(0), STRING(((char*)str_00000158)))
        CALL_CHILD(PTR(bero_case_switch_off))
        SPAWN_EVENT(PTR(evt_boss))
    END_SWITCH
    IF_INT_EQUAL(GSWF(2450), 1)
        IF_INT_EQUAL(GSWF(2451), 0)
            CALL(evt_mario_kill_party, 0)
            CALL(evt_mario_kill_party, 1)
        END_IF
    END_IF
    IF_INT_LESS(GSW(0), 172)
        IF_INT_EQUAL(GSW(501), 0)
            IF_INT_EQUAL(GSWF(2383), 1)
                IF_INT_EQUAL(GSWF(2455), 0)
                    CALL(evt_snd_bgmoff, 512)
                    SPAWN_EVENT(PTR(evt_champion))
                    ELSE
                    SPAWN_EVENT(PTR(evt_champion2))
                END_IF
                RETURN
            END_IF
        END_IF
    END_IF
    IF_INT_EQUAL(GSWF(2388), 1)
        CALL(evt_mario_set_pos, 0, 0, 0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_party_set_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_party_set_pos, 1, LW(0), LW(1), LW(2))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000000F8)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000104)), 1)
        CALL(evt_tou_get_ranking_28_text_4048, LW(0))
        SET_VALUE(GSW(506), LW(0))
        SPAWN_EVENT(PTR(evt_match))
        ELSE
        SWITCH(GSW(0))
            CASE_BETWEEN(128, 162)
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000ABC)))
            CALL(evt_snd_bgmon, 160, 0)
            SPAWN_EVENT(PTR(evt_watch_match))
            CASE_LESS(164)
            CASE_DEFAULT
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000ABC)))
            CALL(evt_snd_bgmon, 160, 0)
            SPAWN_EVENT(PTR(evt_watch_match))
        END_SWITCH
    END_IF
    IF_INT_NOT_EQUAL(GSW(0), 163)
        CALL(evt_hitobj_onoff, STRING(((char*)str_00001804)), 1, 1)
        CALL(evt_hitobj_onoff, STRING(((char*)str_00001810)), 1, 1)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)str_00000054)), 0, PTR(evt_kyaku_1), 0)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)str_0000005C)), 0, PTR(evt_kyaku_2), 0)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)str_00000064)), 0, PTR(evt_kyaku_3), 0)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)str_0000006C)), 0, PTR(evt_kyaku_4), 0)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)str_0000181C)), 0, PTR(evt_kyaku_5), 0)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)str_00001824)), 0, PTR(evt_kyaku_6), 0)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)str_0000182C)), 0, PTR(evt_kyaku_7), 0)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)str_00001834)), 0, PTR(evt_kyaku_8), 0)
        ELSE
        CALL(evt_hitobj_onoff, STRING(((char*)str_00001804)), 1, 0)
        CALL(evt_hitobj_onoff, STRING(((char*)str_00001810)), 1, 0)
    END_IF
    RETURN
EVT_END()

#ifndef NONMATCHING
// FAKE (asm stopgap, asmfake.py --whole): _firstattack_setting (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
#pragma force_active on
__declspec(section ".rodata") const char str_00000000[] = "c_kinopio\000\000";
__declspec(section ".rodata") const char str_0000000C[] = "KNP_S_1";
__declspec(section ".rodata") const char str_00000014[] = "c_kinopiko\000";
__declspec(section ".rodata") const char str_00000020[] = "KNF_S_1";
__declspec(section ".rodata") const char str_00000028[] = "c_roten";
__declspec(section ".rodata") const char str_00000030[] = "S_1";
__declspec(section ".rodata") const char str_00000034[] = "c_jugemu\000\000\000";
__declspec(section ".rodata") const char str_00000040[] = "JGM_S_1";
__declspec(section ".rodata") const f32 vec3_tou2_00009638[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const char str_00000054[] = "kyaku1\000";
__declspec(section ".rodata") const char str_0000005C[] = "kyaku2\000";
__declspec(section ".rodata") const char str_00000064[] = "kyaku3\000";
__declspec(section ".rodata") const char str_0000006C[] = "kyaku4\000";
__declspec(section ".rodata") const char str_00000074[] = "\203L\203m\203s\203I\000\000\000";
__declspec(section ".rodata") const char str_00000080[] = "\203L\203m\203s\203I\217\227\000";
__declspec(section ".rodata") const char str_0000008C[] = "\203\215\203e\203\223\000";
__declspec(section ".rodata") const char str_00000094[] = "\203W\203\205\203Q\203\200\000\000\000";
__declspec(section ".rodata") const char str_000000A0[] = "s_bero_2\000\000\000";
__declspec(section ".rodata") const char str_000000AC[] = "group246\000\000\000";
__declspec(section ".rodata") const char str_000000B8[] = "SFX_DOOR_FALL1\000";
__declspec(section ".rodata") const char str_000000C8[] = "aka_door_a\000";
__declspec(section ".rodata") const char str_000000D4[] = "aka_door_b\000";
__declspec(section ".rodata") const char str_000000E0[] = "ao_door_a\000\000";
__declspec(section ".rodata") const char str_000000EC[] = "ao_ddor_b\000\000";
__declspec(section ".rodata") const char str_000000F8[] = "door_2_a\000\000\000";
__declspec(section ".rodata") const char str_00000104[] = "door_2_b\000\000\000";
__declspec(section ".rodata") const char str_00000110[] = "door_3_a\000\000\000";
__declspec(section ".rodata") const char str_0000011C[] = "door_3_b\000\000\000";
__declspec(section ".rodata") const char str_00000128[] = "w_bero\000";
__declspec(section ".rodata") const char str_00000130[] = "tou_04\000";
__declspec(section ".rodata") const char str_00000138[] = "n_bero_2\000\000\000";
__declspec(section ".rodata") const char str_00000144[] = "e_bero\000";
__declspec(section ".rodata") const char str_0000014C[] = "n_bero_1\000\000\000";
__declspec(section ".rodata") const char str_00000158[] = "s_bero_1\000\000\000";
__declspec(section ".rodata") const char str_00000164[] = "tou_02\000";
__declspec(section ".rodata") const char str_0000016C[] = "\203`\203\203\203\223\203s\203\207\203\223\000\000\000";
__declspec(section ".rodata") const char str_0000017C[] = "\221\212\216\350\000\000\000";
__declspec(section ".rodata") const char str_00000184[] = "SFX_STG3_TOGENOKO_DOWN1";
__declspec(section ".rodata") const char str_0000019C[] = "stg3_tou_25";
__declspec(section ".rodata") const char str_000001A8[] = "stg3_tou_26";
__declspec(section ".rodata") const char str_000001B4[] = "SFX_STG3_BLED_ATTACK1\000\000";
__declspec(section ".rodata") const char str_000001CC[] = "hit";
__declspec(section ".rodata") const char str_000001D0[] = "K_2";
__declspec(section ".rodata") const char str_000001D4[] = "stg3_tou_27";
__declspec(section ".rodata") const char str_000001E0[] = "\203K\203\223\203X\000";
__declspec(section ".rodata") const char str_000001E8[] = "S_4";
__declspec(section ".rodata") const char str_000001EC[] = "T_4";
__declspec(section ".rodata") const char str_000001F0[] = "stg3_tou_28";
__declspec(section ".rodata") const char str_000001FC[] = "stg3_tou_29";
__declspec(section ".rodata") const char str_00000208[] = "M_5";
__declspec(section ".rodata") const char str_0000020C[] = "M_6";
__declspec(section ".rodata") const char str_00000210[] = "stg3_tou_30";
__declspec(section ".rodata") const char str_0000021C[] = "M_7";
__declspec(section ".rodata") const char str_00000220[] = "S_2";
__declspec(section ".rodata") const char str_00000224[] = "H_1";
__declspec(section ".rodata") const char str_00000228[] = "T_2";
__declspec(section ".rodata") const char str_0000022C[] = "H_2";
__declspec(section ".rodata") const char str_00000230[] = "S_3";
__declspec(section ".rodata") const char str_00000234[] = "\203x\203\213\203g\000";
__declspec(section ".rodata") const char str_0000023C[] = "c_bred_h\000\000\000";
__declspec(section ".rodata") const char str_00000248[] = "C_1";
__declspec(section ".rodata") const char str_0000024C[] = "starstone\000\000";
__declspec(section ".rodata") const char str_00000258[] = "SFX_STG3_WIN_AUDIENCE2\000";
__declspec(section ".rodata") const char str_00000270[] = "eff";
__declspec(section ".rodata") const char str_00000274[] = "stg3_tou_31";
__declspec(section ".rodata") const char str_00000280[] = "stg3_tou_32";
__declspec(section ".rodata") const char str_0000028C[] = "\203L\203m\203V\203R\203\217\000";
__declspec(section ".rodata") const char str_00000298[] = "\203L\203m\203V\203R\203\217\201i\203}\203C\203N\201j\000\000\000";
__declspec(section ".rodata") const char str_000002B0[] = "\203}\203b\203`\203\207\203K\203\223\203X\000";
__declspec(section ".rodata") const char str_000002C0[] = "\203L\203m\203V\203`\203\207\203t\000\000\000";
__declspec(section ".rodata") const char str_000002D0[] = "M_D_2\000\000";
__declspec(section ".rodata") const char str_000002D8[] = "PKR_D_3";
__declspec(section ".rodata") const char str_000002E0[] = "PNK_D_3";
__declspec(section ".rodata") const char str_000002E8[] = "D_3";
__declspec(section ".rodata") const char str_000002EC[] = "PYS_D_3";
__declspec(section ".rodata") const char str_000002F4[] = "PWD_D_3";
__declspec(section ".rodata") const char str_000002FC[] = "PTR_D_3";
__declspec(section ".rodata") const char str_00000304[] = "PCH_D_3";
__declspec(section ".rodata") const char str_0000030C[] = "PKR_Y_1";
__declspec(section ".rodata") const char str_00000314[] = "PNK_Y_1";
__declspec(section ".rodata") const char str_0000031C[] = "Y_1";
__declspec(section ".rodata") const char str_00000320[] = "PYS_Y_1";
__declspec(section ".rodata") const char str_00000328[] = "PWD_Y_1";
__declspec(section ".rodata") const char str_00000330[] = "PTR_Y_1";
__declspec(section ".rodata") const char str_00000338[] = "PCH_Y_1";
__declspec(section ".rodata") const char str_00000340[] = "c_togenoko_b\000\000\000";
__declspec(section ".rodata") const char str_00000350[] = "\203u\203\214\203b\203h\203n\201[\203g\000";
__declspec(section ".rodata") const char str_00000360[] = "\203g\203Q\203m\203R\203G\201[\203X\000";
__declspec(section ".rodata") const char str_00000370[] = "c_bomhey\000\000\000";
__declspec(section ".rodata") const char str_0000037C[] = "\203{\203\200\225\272\000";
__declspec(section ".rodata") const char str_00000384[] = "c_kuribo\000\000\000";
__declspec(section ".rodata") const char str_00000390[] = "\203N\203\212\203{\201[\000\000\000";
__declspec(section ".rodata") const char str_0000039C[] = "c_kmoon_wb\000";
__declspec(section ".rodata") const char str_000003A8[] = "\203\202\203m\203N\203\215\203N\203\215\203N\203\202\201[\203\223\000\000\000";
__declspec(section ".rodata") const char str_000003C0[] = "c_chorobon\000";
__declspec(section ".rodata") const char str_000003CC[] = "\203`\203\207\203\215\203{\203\223\000";
__declspec(section ".rodata") const char str_000003D8[] = "c_monban_t\000";
__declspec(section ".rodata") const char str_000003E4[] = "\203_\201[\203N\203L\201[\203p\201[\000";
__declspec(section ".rodata") const char str_000003F4[] = "c_togedaruma\000\000\000";
__declspec(section ".rodata") const char str_00000404[] = "\203g\203Q\203_\203\213\203}\201[\000\000\000";
__declspec(section ".rodata") const char str_00000414[] = "c_wanwan_a\000";
__declspec(section ".rodata") const char str_00000420[] = "\203o\201[\203X\203g\203\217\203\223\203\217\203\223\000\000\000";
__declspec(section ".rodata") const char str_00000434[] = "\221I\216\3501\000\000";
__declspec(section ".rodata") const char str_0000043C[] = "\221I\216\3502\000\000";
__declspec(section ".rodata") const char str_00000444[] = "WAN_A_1";
__declspec(section ".rodata") const char str_0000044C[] = "\223G\202R\000\000\000";
__declspec(section ".rodata") const char str_00000454[] = "\223G\202S\000\000\000";
__declspec(section ".rodata") const char str_0000045C[] = "\223G\202P\000\000\000";
__declspec(section ".rodata") const char str_00000464[] = "\223G\202Q\000\000\000";
__declspec(section ".rodata") const char str_0000046C[] = "\223G\202T\000\000\000";
__declspec(section ".rodata") const char str_00000474[] = "\202\250\202\251\202\265\202\242\000\000\000";
__declspec(section ".rodata") const char str_00000480[] = "SFX_STG3_ISIN_MOVE1L\000\000\000";
__declspec(section ".rodata") const char str_00000498[] = "SFX_STG3_ISIN_MOVE1R\000\000\000";
__declspec(section ".rodata") const char str_000004B0[] = "\227\220\000";
__declspec(section ".rodata") const char str_000004B4[] = "c_koopa";
__declspec(section ".rodata") const char str_000004BC[] = "\203N\203b\203p\000";
__declspec(section ".rodata") const char str_000004C4[] = "SFX_STG3_KOOPA_MOVE1L\000\000";
__declspec(section ".rodata") const char str_000004DC[] = "SFX_STG3_KOOPA_MOVE1R\000\000";
__declspec(section ".rodata") const char str_000004F4[] = "SFX_STG3_KOOPA_JUMP1\000\000\000";
__declspec(section ".rodata") const char str_0000050C[] = "c_sinemon_a";
__declspec(section ".rodata") const char str_00000518[] = "\203A\203C\203A\203\223\203V\203\223\203G\203\202\203\223\000";
__declspec(section ".rodata") const char str_0000052C[] = "\227\220\202Q\000\000\000";
__declspec(section ".rodata") const char str_00000534[] = "c_sinemon_m";
__declspec(section ".rodata") const char str_00000540[] = "\203A\203C\203A\203\223\203V\203\223\203G\203\202\203\2232";
__declspec(section ".rodata") const char str_00000554[] = "SFX_VOICE_MARIO_FIND1_3";
__declspec(section ".rodata") const char str_0000056C[] = "m\000\000";
__declspec(section ".rodata") const char str_00000570[] = "stg3_tou_403\000\000\000";
__declspec(section ".rodata") const char str_00000580[] = "M_I_Y\000\000";
__declspec(section ".rodata") const char str_00000588[] = "stg3_tou_403_01";
__declspec(section ".rodata") const char str_00000598[] = "stg3_tou_404\000\000\000";
__declspec(section ".rodata") const char str_000005A8[] = "SFX_STG3_GONG1\000";
__declspec(section ".rodata") const char str_000005B8[] = "M_S_1\000\000";
__declspec(section ".rodata") const char str_000005C0[] = "SIN_K_1";
__declspec(section ".rodata") const char str_000005C8[] = "stg3_tou_406\000\000\000";
__declspec(section ".rodata") const char str_000005D8[] = "stg3_tou_403_02";
__declspec(section ".rodata") const char str_000005E8[] = "stg3_tou_405\000\000\000";
__declspec(section ".rodata") const char str_000005F8[] = "stg3_tou_406_01";
__declspec(section ".rodata") const char str_00000608[] = "stg3_tou_403_04";
__declspec(section ".rodata") const char str_00000618[] = "BGM_EVT_KUPPA2\000";
__declspec(section ".rodata") const char str_00000628[] = "stg3_tou_403_05";
__declspec(section ".rodata") const char str_00000638[] = "stg3_tou_403_06";
__declspec(section ".rodata") const char str_00000648[] = "KPA_Z_3";
__declspec(section ".rodata") const char str_00000650[] = "KPA_T_8";
__declspec(section ".rodata") const char str_00000658[] = "stg3_tou_403_08";
__declspec(section ".rodata") const char str_00000668[] = "stg3_tou_403_10";
__declspec(section ".rodata") const char str_00000678[] = "stg3_tou_403_07";
__declspec(section ".rodata") const char str_00000688[] = "stg3_tou_403_09";
__declspec(section ".rodata") const char str_00000698[] = "\203J\203\201\203b\203N\227\316\213\363\000\000\000";
__declspec(section ".rodata") const char str_000006A8[] = "\215\2750_0\000\000";
__declspec(section ".rodata") const char str_000006B0[] = "\215\2750_1\000\000";
__declspec(section ".rodata") const char str_000006B8[] = "\215\2750_2\000\000";
__declspec(section ".rodata") const char str_000006C0[] = "\215\2750_3\000\000";
__declspec(section ".rodata") const char str_000006C8[] = "\215\2750_4\000\000";
__declspec(section ".rodata") const char str_000006D0[] = "WAN_S_1B\000\000\000";
__declspec(section ".rodata") const char str_000006DC[] = "\215\2751_0\000\000";
__declspec(section ".rodata") const char str_000006E4[] = "\215\2751_1\000\000";
__declspec(section ".rodata") const char str_000006EC[] = "\215\2751_2\000\000";
__declspec(section ".rodata") const char str_000006F4[] = "\215\2751_3\000\000";
__declspec(section ".rodata") const char str_000006FC[] = "\215\2751_4\000\000";
__declspec(section ".rodata") const char str_00000704[] = "SFX_FLD_ENM_WAN_LANDING1\000\000\000";
__declspec(section ".rodata") const char str_00000720[] = "BGM_FF_ENV_TOU2";
__declspec(section ".rodata") const char str_00000730[] = "BGM_FF_ENV_TOU3";
__declspec(section ".rodata") const char str_00000740[] = "tou_07\000";
__declspec(section ".rodata") const char str_00000748[] = "tou_08\000";
__declspec(section ".rodata") const char str_00000750[] = "tou_10\000";
__declspec(section ".rodata") const char str_00000758[] = "BGM_FF_ENV_TOU1";
__declspec(section ".rodata") const char str_00000768[] = "stg3_tou_77";
__declspec(section ".rodata") const char str_00000774[] = "stg3_tou_78";
__declspec(section ".rodata") const char str_00000780[] = "stg3_tou_79";
__declspec(section ".rodata") const char str_0000078C[] = "mario\000\000";
__declspec(section ".rodata") const char str_00000794[] = "SFX_DOOR_SHUT_IRON2";
__declspec(section ".rodata") const char str_000007A8[] = "stg3_tou_80";
__declspec(section ".rodata") const char str_000007B4[] = "SFX_VOICE_MARIO_FLD_JUMP3\000\000";
__declspec(section ".rodata") const char str_000007D0[] = "SFX_VOICE_MARIO_FLD_JUMP1\000\000";
__declspec(section ".rodata") const char str_000007EC[] = "SFX_VOICE_MARIO_FLD_JUMP5\000\000";
__declspec(section ".rodata") const char str_00000808[] = "stg3_tou_81";
__declspec(section ".rodata") const char str_00000814[] = "stg3_tou_82";
__declspec(section ".rodata") const char str_00000820[] = "SFX_VOICE_MARIO_SURPRISED1\000";
__declspec(section ".rodata") const char str_0000083C[] = "M_N_7\000\000";
__declspec(section ".rodata") const char str_00000844[] = "SFX_STG3_KURI_ATTACK1\000\000";
__declspec(section ".rodata") const char str_0000085C[] = "KUR_K_1";
__declspec(section ".rodata") const char str_00000864[] = "KUR_D_1";
__declspec(section ".rodata") const char str_0000086C[] = "SFX_STG3_KURI_FURAFURA1";
__declspec(section ".rodata") const char str_00000884[] = "stg3_tou_86";
__declspec(section ".rodata") const char str_00000890[] = "stg3_tou_87";
__declspec(section ".rodata") const char str_0000089C[] = "stg3_tou_87_yn\000";
__declspec(section ".rodata") const char str_000008AC[] = "stg3_tou_88";
__declspec(section ".rodata") const u32 zero_tou2_00009ea8[1] = { 0x00000000 };
__declspec(section ".rodata") const char str_000008BC[] = "confetti\000\000\000";
__declspec(section ".rodata") const char str_000008C8[] = "SFX_STG3_WIN_AUDIENCE1\000";
__declspec(section ".rodata") const char str_000008E0[] = "stg3_tou_118_61";
__declspec(section ".rodata") const char str_000008F0[] = "stg3_tou_85";
__declspec(section ".rodata") const char str_000008FC[] = "stg3_tou_257\000\000\000";
__declspec(section ".rodata") const char str_0000090C[] = "stg3_tou_258_00";
__declspec(section ".rodata") const char str_0000091C[] = "SFX_VOICE_MARIO_FLD_JUMP2\000\000";
__declspec(section ".rodata") const char str_00000938[] = "stg3_tou_258_01";
__declspec(section ".rodata") const char str_00000948[] = "stg3_tou_258_02";
__declspec(section ".rodata") const char str_00000958[] = "stg3_tou_258_03";
__declspec(section ".rodata") const char str_00000968[] = "stg3_tou_258_04";
__declspec(section ".rodata") const char str_00000978[] = "stg3_tou_259\000\000\000";
__declspec(section ".rodata") const char str_00000988[] = "stg3_tou_259_yn";
__declspec(section ".rodata") const char str_00000998[] = "stg3_tou_260\000\000\000";
__declspec(section ".rodata") const char str_000009A8[] = "e\000\000";
__declspec(section ".rodata") const char str_000009AC[] = "stg3_tou_261_01";
__declspec(section ".rodata") const char str_000009BC[] = "stg3_tou_261_02";
__declspec(section ".rodata") const char str_000009CC[] = "stg3_tou_261_03";
__declspec(section ".rodata") const char str_000009DC[] = "stg3_tou_262\000\000\000";
__declspec(section ".rodata") const char str_000009EC[] = "stg3_tou_263\000\000\000";
__declspec(section ".rodata") const char str_000009FC[] = "stg3_tou_264\000\000\000";
__declspec(section ".rodata") const char str_00000A0C[] = "M_1";
__declspec(section ".rodata") const char str_00000A10[] = "M_2";
__declspec(section ".rodata") const char str_00000A14[] = "M_3";
__declspec(section ".rodata") const char str_00000A18[] = "stg3_tou_116_20_01\000";
__declspec(section ".rodata") const char str_00000A2C[] = "stg3_tou_275\000\000\000";
__declspec(section ".rodata") const char str_00000A3C[] = "stg3_tou_276\000\000\000";
__declspec(section ".rodata") const char str_00000A4C[] = "stg3_tou_277\000\000\000";
__declspec(section ".rodata") const char str_00000A5C[] = "M_I_U\000\000";
__declspec(section ".rodata") const char str_00000A64[] = "SFX_VOICE_MARIO_PAUSE2\000";
__declspec(section ".rodata") const char str_00000A7C[] = "M_V_2\000\000";
__declspec(section ".rodata") const char str_00000A84[] = "stg3_tou_274\000\000\000";
__declspec(section ".rodata") const char str_00000A94[] = "stg3_tou_274_01";
__declspec(section ".rodata") const char str_00000AA4[] = "\203u\203\214\203b\203h\203n\201[\203g\203x\203\213\203g\000\000\000";
__declspec(section ".rodata") const char str_00000ABC[] = "BGM_STG3_TOU2\000\000";
__declspec(section ".rodata") const char str_00000ACC[] = "a\000\000";
__declspec(section ".rodata") const char str_00000AD0[] = "stg3_tou_424\000\000\000";
__declspec(section ".rodata") const char str_00000AE0[] = "stg3_tou_425\000\000\000";
__declspec(section ".rodata") const char str_00000AF0[] = "stg3_tou_426\000\000\000";
__declspec(section ".rodata") const char str_00000B00[] = "stg3_tou_427\000\000\000";
__declspec(section ".rodata") const char str_00000B10[] = "stg3_tou_428\000\000\000";
__declspec(section ".rodata") const char str_00000B20[] = "stg3_tou_429\000\000\000";
__declspec(section ".rodata") const char str_00000B30[] = "stg3_tou_430\000\000\000";
__declspec(section ".rodata") const char str_00000B40[] = "SFX_VOICE_MARIO_FLD_JUMP4\000\000";
__declspec(section ".rodata") const char str_00000B5C[] = "stg3_tou_430_01";
__declspec(section ".rodata") const char str_00000B6C[] = "stg3_tou_430_02";
__declspec(section ".rodata") const char str_00000B7C[] = "stg3_tou_430_03";
__declspec(section ".rodata") const char str_00000B8C[] = "stg3_tou_430_04";
__declspec(section ".rodata") const char str_00000B9C[] = "stg3_tou_431\000\000\000";
__declspec(section ".rodata") const char str_00000BAC[] = "stg3_tou_re_086";
__declspec(section ".rodata") const char str_00000BBC[] = "stg3_tou_re_087";
__declspec(section ".rodata") const char str_00000BCC[] = "stg3_tou_re_089";
__declspec(section ".rodata") const char str_00000BDC[] = "stg3_tou_re_090";
__declspec(section ".rodata") const char str_00000BEC[] = "stg3_tou_re_091";
__declspec(section ".rodata") const char str_00000BFC[] = "stg3_tou_re_092";
__declspec(section ".rodata") const char str_00000C0C[] = "stg3_tou_re_093";
__declspec(section ".rodata") const char str_00000C1C[] = "stg3_tou_re_094";
__declspec(section ".rodata") const char str_00000C2C[] = "stg3_tou_re_095";
__declspec(section ".rodata") const char str_00000C3C[] = "stg3_tou_re_096";
__declspec(section ".rodata") const char str_00000C4C[] = "stg3_tou_re_097";
__declspec(section ".rodata") const char str_00000C5C[] = "stg3_tou_re_098";
__declspec(section ".rodata") const char str_00000C6C[] = "stg3_tou_re_099";
__declspec(section ".rodata") const char str_00000C7C[] = "stg3_tou_re_100";
__declspec(section ".rodata") const char str_00000C8C[] = "stg3_tou_re_101";
__declspec(section ".rodata") const char str_00000C9C[] = "stg3_tou_re_102";
__declspec(section ".rodata") const char str_00000CAC[] = "stg3_tou_re_103";
__declspec(section ".rodata") const char str_00000CBC[] = "stg3_tou_re_110";
__declspec(section ".rodata") const char str_00000CCC[] = "stg3_tou_re_111";
__declspec(section ".rodata") const char str_00000CDC[] = "stg3_tou_re_112";
__declspec(section ".rodata") const char str_00000CEC[] = "stg3_tou_re_113";
__declspec(section ".rodata") const char str_00000CFC[] = "stg3_tou_re_114";
__declspec(section ".rodata") const char str_00000D0C[] = "A_2";
__declspec(section ".rodata") const char str_00000D10[] = "T_3";
__declspec(section ".rodata") const char str_00000D14[] = "stg3_tou_re_115";
__declspec(section ".rodata") const char str_00000D24[] = "stg3_tou_438\000\000\000";
__declspec(section ".rodata") const char str_00000D34[] = "stg3_tou_439\000\000\000";
__declspec(section ".rodata") const char str_00000D44[] = "stg3_tou_re_133";
__declspec(section ".rodata") const char str_00000D54[] = "stg3_tou_re_134";
__declspec(section ".rodata") const char str_00000D64[] = "SFX_STG3_BLED_DIE1\000";
__declspec(section ".rodata") const char str_00000D78[] = "S_10\000\000\000";
__declspec(section ".rodata") const char str_00000D80[] = "T_10\000\000\000";
__declspec(section ".rodata") const char str_00000D88[] = "stg3_tou_440\000\000\000";
__declspec(section ".rodata") const char str_00000D98[] = "stg3_tou_441\000\000\000";
__declspec(section ".rodata") const char str_00000DA8[] = "stg3_tou_442\000\000\000";
__declspec(section ".rodata") const char str_00000DB8[] = "stg3_tou_443\000\000\000";
__declspec(section ".rodata") const char str_00000DC8[] = "stg3_tou_444\000\000\000";
__declspec(section ".rodata") const char str_00000DD8[] = "stg3_tou_re_135";
__declspec(section ".rodata") const char str_00000DE8[] = "stg3_tou_re_136";
__declspec(section ".rodata") const char str_00000DF8[] = "stg3_tou_re_137";
__declspec(section ".rodata") const char str_00000E08[] = "stg3_tou_re_138";
__declspec(section ".rodata") const char str_00000E18[] = "stg3_tou_re_139";
__declspec(section ".rodata") const char str_00000E28[] = "stg3_tou_437\000\000\000";
__declspec(section ".rodata") const char str_00000E38[] = "stg3_tou_400_03";
__declspec(section ".rodata") const char str_00000E48[] = "stg3_tou_400_01";
__declspec(section ".rodata") const char str_00000E58[] = "stg3_tou_re_132";
__declspec(section ".rodata") const char str_00000E68[] = "stg3_tou_re_290";
__declspec(section ".rodata") const char str_00000E78[] = "stg3_tou_re_288";
__declspec(section ".rodata") const char str_00000E88[] = "stg3_tou_378\000\000\000";
__declspec(section ".rodata") const char str_00000E98[] = "stg3_tou_re_266";
__declspec(section ".rodata") const char str_00000EA8[] = "stg3_tou_377\000\000\000";
__declspec(section ".rodata") const char str_00000EB8[] = "stg3_tou_re_265";
__declspec(section ".rodata") const char str_00000EC8[] = "stg3_tou_115\000\000\000";
__declspec(section ".rodata") const char str_00000ED8[] = "stg3_tou_116_20";
__declspec(section ".rodata") const char str_00000EE8[] = "stg3_tou_re_147";
__declspec(section ".rodata") const char str_00000EF8[] = "stg3_tou_re_149";
__declspec(section ".rodata") const char str_00000F08[] = "stg3_tou_117_00";
__declspec(section ".rodata") const char str_00000F18[] = "stg3_tou_117_01";
__declspec(section ".rodata") const char str_00000F28[] = "stg3_tou_305\000\000\000";
__declspec(section ".rodata") const char str_00000F38[] = "stg3_tou_re_151";
__declspec(section ".rodata") const char str_00000F48[] = "stg3_tou_118_37";
__declspec(section ".rodata") const char str_00000F58[] = "stg3_tou_400_00";
__declspec(section ".rodata") const char str_00000F68[] = "stg3_tou_re_287";
__declspec(section ".rodata") const char str_00000F78[] = "stg3_tou_re_150";
__declspec(section ".rodata") const char str_00000F88[] = "stg3_tou_118_39";
__declspec(section ".rodata") const char str_00000F98[] = "stg3_tou_117_02";
__declspec(section ".rodata") const char str_00000FA8[] = "stg3_tou_117_03";
__declspec(section ".rodata") const char str_00000FB8[] = "stg3_tou_re_153";
__declspec(section ".rodata") const char str_00000FC8[] = "stg3_tou_118_38";
__declspec(section ".rodata") const char str_00000FD8[] = "stg3_tou_411\000\000\000";
__declspec(section ".rodata") const char str_00000FE8[] = "stg3_tou_412\000\000\000";
__declspec(section ".rodata") const char str_00000FF8[] = "stg3_tou_413_01";
__declspec(section ".rodata") const char str_00001008[] = "stg3_tou_413_02";
__declspec(section ".rodata") const char str_00001018[] = "stg3_tou_413_03";
__declspec(section ".rodata") const char str_00001028[] = "stg3_tou_413_04";
__declspec(section ".rodata") const char str_00001038[] = "stg3_tou_414\000\000\000";
__declspec(section ".rodata") const char str_00001048[] = "stg3_tou_415\000\000\000";
__declspec(section ".rodata") const char str_00001058[] = "stg3_tou_416\000\000\000";
__declspec(section ".rodata") const char str_00001068[] = "stg3_tou_417\000\000\000";
__declspec(section ".rodata") const char str_00001078[] = "tou_11\000";
__declspec(section ".rodata") const char str_00001080[] = "nidome\000";
__declspec(section ".rodata") const char str_00001088[] = "stg3_tou_418\000\000\000";
__declspec(section ".rodata") const char str_00001098[] = "stg3_tou_419\000\000\000";
__declspec(section ".rodata") const char str_000010A8[] = "stg3_tou_420\000\000\000";
__declspec(section ".rodata") const char str_000010B8[] = "stg3_tou_421\000\000\000";
__declspec(section ".rodata") const char str_000010C8[] = "sandome";
__declspec(section ".rodata") const f32 vec3_tou2_0000a6c0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_tou2_0000a6cc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const char str_000010E8[] = "block_1";
__declspec(section ".rodata") const char str_000010F0[] = "block_2";
__declspec(section ".rodata") const char str_000010F8[] = "block_3";
__declspec(section ".rodata") const char str_00001100[] = "block_4";
__declspec(section ".rodata") const char str_00001108[] = "block_5";
__declspec(section ".rodata") const char str_00001110[] = "block_6";
__declspec(section ".rodata") const char str_00001118[] = "block_7";
__declspec(section ".rodata") const char str_00001120[] = "block_8";
__declspec(section ".rodata") const char str_00001128[] = "block_9";
__declspec(section ".rodata") const char str_00001130[] = "stone\000\000";
__declspec(section ".rodata") const char str_00001138[] = "kaiten_souti\000\000\000";
__declspec(section ".rodata") const u32 dat_tou2_0000a738[1] = { 0xFFFFFF00 };
__declspec(section ".rodata") const char str_0000114C[] = "group34";
__declspec(section ".rodata") const char str_00001154[] = "a_kai_right";
__declspec(section ".rodata") const char str_00001160[] = "a_butai";
__declspec(section ".rodata") const char str_00001168[] = "BGM_EVT_STG3_GANCE2";
__declspec(section ".rodata") const char str_0000117C[] = "stg3_tou_463\000\000\000";
__declspec(section ".rodata") const char str_0000118C[] = "SFX_STG3_GROUND_SHAKE1\000";
__declspec(section ".rodata") const char str_000011A4[] = "p\000\000";
__declspec(section ".rodata") const char str_000011A8[] = "butai_2";
__declspec(section ".rodata") const char str_000011B0[] = "butai_1";
__declspec(section ".rodata") const char str_000011B8[] = "tyuubu\000";
__declspec(section ".rodata") const char str_000011C0[] = "guruguru\000\000\000";
__declspec(section ".rodata") const char str_000011CC[] = "hakkou\000";
__declspec(section ".rodata") const char str_000011D4[] = "souti\000\000";
__declspec(section ".rodata") const char str_000011DC[] = "comp\000\000\000";
__declspec(section ".rodata") const char str_000011E4[] = "SFX_STG3_ABSORB_DEVICE_UP1\000";
__declspec(section ".rodata") const char str_00001200[] = "SFX_STG3_ABSORB_DEVICE_UP_STOP1";
__declspec(section ".rodata") const char str_00001220[] = "SFX_STG3_RING_DOWN1";
__declspec(section ".rodata") const char str_00001234[] = "a_souti";
__declspec(section ".rodata") const char str_0000123C[] = "stg3_tou_464\000\000\000";
__declspec(section ".rodata") const char str_0000124C[] = "stg3_tou_465\000\000\000";
__declspec(section ".rodata") const char str_0000125C[] = "stg3_tou_465_01";
__declspec(section ".rodata") const char str_0000126C[] = "stg3_tou_466\000\000\000";
__declspec(section ".rodata") const char str_0000127C[] = "P_1";
__declspec(section ".rodata") const char str_00001280[] = "P_2";
__declspec(section ".rodata") const char str_00001284[] = "SFX_STG3_ABSORB_DEVICE1";
__declspec(section ".rodata") const char str_0000129C[] = "SFX_STG3_GANSU_BIG1";
__declspec(section ".rodata") const char str_000012B0[] = "OFF_d_bom\000\000";
__declspec(section ".rodata") const char str_000012BC[] = "SFX_STG3_GANSU_BIG2";
__declspec(section ".rodata") const char str_000012D0[] = "A_1";
__declspec(section ".rodata") const char str_000012D4[] = "stg3_tou_466_01";
__declspec(section ".rodata") const char str_000012E4[] = "M_I_N\000\000";
__declspec(section ".rodata") const char str_000012EC[] = "stg3_tou_467\000\000\000";
__declspec(section ".rodata") const char str_000012FC[] = "stg3_tou_468\000\000\000";
__declspec(section ".rodata") const char str_0000130C[] = "SFX_STG3_ABSORB_DEVICE2";
__declspec(section ".rodata") const char str_00001324[] = "D_1";
__declspec(section ".rodata") const char str_00001328[] = "D_2";
__declspec(section ".rodata") const char str_0000132C[] = "stg3_tou_473\000\000\000";
__declspec(section ".rodata") const char str_0000133C[] = "BGM_EVT_ORGEL1\000";
__declspec(section ".rodata") const char str_0000134C[] = "stg3_tou_473_01";
__declspec(section ".rodata") const char str_0000135C[] = "SFX_VOICE_MARIO_FIND1_2";
__declspec(section ".rodata") const char str_00001374[] = "stg3_tou_473_02";
__declspec(section ".rodata") const char str_00001384[] = "stg3_tou_473_03";
__declspec(section ".rodata") const char str_00001394[] = "stg3_tou_473_04";
__declspec(section ".rodata") const char str_000013A4[] = "stg3_tou_473_05";
__declspec(section ".rodata") const char str_000013B4[] = "stg3_tou_473_06";
__declspec(section ".rodata") const char str_000013C4[] = "stg3_tou_473_07";
__declspec(section ".rodata") const char str_000013D4[] = "stg3_tou_473_07_01\000";
__declspec(section ".rodata") const char str_000013E8[] = "stg3_tou_473_07_02\000";
__declspec(section ".rodata") const char str_000013FC[] = "stg3_tou_473_07_03\000";
__declspec(section ".rodata") const char str_00001410[] = "stg3_tou_473_07_04\000";
__declspec(section ".rodata") const char str_00001424[] = "sl\000";
__declspec(section ".rodata") const char str_00001428[] = "sunlight_n64\000\000\000";
__declspec(section ".rodata") const char str_00001438[] = "stg3_tou_473_07_04_01\000\000";
__declspec(section ".rodata") const char str_00001450[] = "eff_2\000\000";
__declspec(section ".rodata") const char str_00001458[] = "pokopi_pcharge_n64\000";
__declspec(section ".rodata") const char str_0000146C[] = "SFX_STG3_STARSTONE_ROUND1\000\000";
__declspec(section ".rodata") const char str_00001488[] = "eff_1\000\000";
__declspec(section ".rodata") const char str_00001490[] = "stg3_tou_473_07_05\000";
__declspec(section ".rodata") const char str_000014A4[] = "stg3_tou_473_07_06\000";
__declspec(section ".rodata") const char str_000014B8[] = "stg3_tou_473_07_07\000";
__declspec(section ".rodata") const char str_000014CC[] = "stg3_tou_473_07_08\000";
__declspec(section ".rodata") const char str_000014E0[] = "stg3_tou_473_07_09\000";
__declspec(section ".rodata") const char str_000014F4[] = "stg3_tou_473_08";
__declspec(section ".rodata") const char str_00001504[] = "SFX_STG3_STARSTONE_ROUND2\000\000";
__declspec(section ".rodata") const char str_00001520[] = "stg3_tou_473_09";
__declspec(section ".rodata") const char str_00001530[] = "stg3_tou_473_10";
__declspec(section ".rodata") const char str_00001540[] = "stg3_tou_473_11";
__declspec(section ".rodata") const char str_00001550[] = "SFX_VOICE_MARIO_NOD1_4\000";
__declspec(section ".rodata") const char str_00001568[] = "M_N_2\000\000";
__declspec(section ".rodata") const char str_00001570[] = "SFX_STG3_FIGHTING3\000";
__declspec(section ".rodata") const char str_00001584[] = "stg3_tou_119\000\000\000";
__declspec(section ".rodata") const char str_00001594[] = "stg3_tou_120\000\000\000";
__declspec(section ".rodata") const char str_000015A4[] = "stg3_tou_121\000\000\000";
__declspec(section ".rodata") const char str_000015B4[] = "stg3_tou_122\000\000\000";
__declspec(section ".rodata") const char str_000015C4[] = "stg3_tou_123\000\000\000";
__declspec(section ".rodata") const char str_000015D4[] = "stg3_tou_124\000\000\000";
__declspec(section ".rodata") const char str_000015E4[] = "stg3_tou_125\000\000\000";
__declspec(section ".rodata") const char str_000015F4[] = "stg3_tou_126\000\000\000";
__declspec(section ".rodata") const char str_00001604[] = "stg3_tou_127\000\000\000";
__declspec(section ".rodata") const char str_00001614[] = "stg3_tou_128\000\000\000";
__declspec(section ".rodata") const char str_00001624[] = "stg3_tou_128_01";
__declspec(section ".rodata") const char str_00001634[] = "stg3_tou_128_02";
__declspec(section ".rodata") const char str_00001644[] = "stg3_tou_129\000\000\000";
__declspec(section ".rodata") const char str_00001654[] = "stg3_tou_129_01";
__declspec(section ".rodata") const char str_00001664[] = "stg3_tou_129_02";
__declspec(section ".rodata") const char str_00001674[] = "stg3_tou_130\000\000\000";
__declspec(section ".rodata") const char str_00001684[] = "stg3_tou_130_01";
__declspec(section ".rodata") const char str_00001694[] = "stg3_tou_130_02";
__declspec(section ".rodata") const char str_000016A4[] = "stg3_tou_131\000\000\000";
__declspec(section ".rodata") const char str_000016B4[] = "stg3_tou_132\000\000\000";
__declspec(section ".rodata") const char str_000016C4[] = "stg3_tou_133\000\000\000";
__declspec(section ".rodata") const char str_000016D4[] = "stg3_tou_134\000\000\000";
__declspec(section ".rodata") const char str_000016E4[] = "stg3_tou_135\000\000\000";
__declspec(section ".rodata") const char str_000016F4[] = "stg3_tou_136\000\000\000";
__declspec(section ".rodata") const char str_00001704[] = "stg3_tou_137\000\000\000";
__declspec(section ".rodata") const char str_00001714[] = "stg3_tou_138\000\000\000";
__declspec(section ".rodata") const char str_00001724[] = "stg3_tou_139\000\000\000";
__declspec(section ".rodata") const char str_00001734[] = "stg3_tou_140\000\000\000";
__declspec(section ".rodata") const char str_00001744[] = "stg3_tou_140_01";
__declspec(section ".rodata") const char str_00001754[] = "stg3_tou_140_02";
__declspec(section ".rodata") const char str_00001764[] = "stg3_tou_141\000\000\000";
__declspec(section ".rodata") const char str_00001774[] = "stg3_tou_141_01";
__declspec(section ".rodata") const char str_00001784[] = "stg3_tou_141_02";
__declspec(section ".rodata") const char str_00001794[] = "stg3_tou_142\000\000\000";
__declspec(section ".rodata") const char str_000017A4[] = "stg3_tou_142_01";
__declspec(section ".rodata") const char str_000017B4[] = "stg3_tou_142_02";
__declspec(section ".rodata") const char str_000017C4[] = "ENV_STG3_TOU3\000\000";
__declspec(section ".rodata") const char str_000017D4[] = "ue\000";
__declspec(section ".rodata") const char str_000017D8[] = "light_coloer\000\000\000";
__declspec(section ".rodata") const char str_000017E8[] = "light_l";
__declspec(section ".rodata") const char str_000017F0[] = "light_r";
__declspec(section ".rodata") const char str_000017F8[] = "monittor\000\000\000";
__declspec(section ".rodata") const char str_00001804[] = "a_kyaku_A\000\000";
__declspec(section ".rodata") const char str_00001810[] = "a_kyaku_B\000\000";
__declspec(section ".rodata") const char str_0000181C[] = "kyaku5\000";
__declspec(section ".rodata") const char str_00001824[] = "kyaku6\000";
__declspec(section ".rodata") const char str_0000182C[] = "kyaku7\000";
__declspec(section ".rodata") const char str_00001834[] = "kyaku8\000";
__declspec(section ".rodata") const f32 float_15_tou2_0000ae2c[1] = { 15.0f };
__declspec(section ".rodata") const char str_00001840[] = "group151\000\000\000";
__declspec(section ".rodata") const f32 float_100_tou2_0000ae3c[1] = { 100.0f };
__declspec(section ".rodata") const f32 zero_tou2_0000ae40[1] = { 0.0f };
__declspec(section ".rodata") const f32 float_1_tou2_0000ae44[1] = { 1.0f };
__declspec(section ".rodata") const f32 float_0p5_tou2_0000ae48[1] = { 0.5f };
__declspec(section ".rodata") const f32 float_6p2832_tou2_0000ae4c[1] = { 6.2831855f };
__declspec(section ".rodata") const f32 float_360_tou2_0000ae50[1] = { 360.0f };
__declspec(section ".rodata") const char str_00001864[] = "SFX_EVT_STARSTONE_JUMP1";
__declspec(section ".rodata") const char str_0000187C[] = "\215\275%d_%d";
__declspec(section ".rodata") const f32 float_3_tou2_0000ae74[1] = { 3.0f };
__declspec(section ".rodata") const f32 float_10_tou2_0000ae78[1] = { 10.0f };
__declspec(section ".rodata") const f32 float_210_tou2_0000ae7c[1] = { 210.0f };
__declspec(section ".rodata") const f32 float_neg210_tou2_0000ae80[1] = { -210.0f };
__declspec(section ".rodata") const f32 float_60_tou2_0000ae84[1] = { 60.0f };
__declspec(section ".rodata") const f32 float_0p25_tou2_0000ae88[1] = { 0.25f };
__declspec(section ".rodata") const f32 float_4p75_tou2_0000ae8c[1] = { 4.75f };
__declspec(section ".rodata") const f32 float_3p75_tou2_0000ae90[1] = { 3.75f };
__declspec(section ".rodata") const f32 float_16_tou2_0000ae94[1] = { 16.0f };
__declspec(section ".rodata") const f32 float_6_tou2_0000ae98[1] = { 6.0f };
__declspec(section ".rodata") const f32 float_1000_tou2_0000ae9c[1] = { 1000.0f };
__declspec(section ".rodata") const f32 float_neg1_tou2_0000aea0[1] = { -1.0f };
__declspec(section ".rodata") const f32 float_6p2832_tou2_0000aea4[1] = { 6.283184f };
__declspec(section ".rodata") const f32 float_250_tou2_0000aea8[1] = { 250.0f };
__declspec(section ".rodata") const f32 float_500_tou2_0000aeac[1] = { 500.0f };
__declspec(section ".rodata") const f32 float_550_tou2_0000aeb0[1] = { 550.0f };
__declspec(section ".rodata") const f32 float_650_tou2_0000aeb4[1] = { 650.0f };
__declspec(section ".rodata") const f32 float_850_tou2_0000aeb8[1] = { 850.0f };
__declspec(section ".rodata") const f32 float_0p7854_tou2_0000aebc[1] = { 0.7853982f };
__declspec(section ".rodata") const f32 float_5p4978_tou2_0000aec0[1] = { 5.4977875f };
__declspec(section ".rodata") const f64 double_70_tou2_0000aec8 = 70;
__declspec(section ".rodata") const f32 float_1E05_tou2_0000aed0[1] = { 100000.0f };
__declspec(section ".rodata") const f32 float_570_tou2_0000aed4[1] = { 570.0f };
__declspec(section ".rodata") const f32 float_40_tou2_0000aed8[1] = { 40.0f };
__declspec(section ".rodata") const f32 float_350_tou2_0000aedc[1] = { 350.0f };
__declspec(section ".rodata") const f64 double_to_int_tou2_0000aee0 = 4503601774854144;
__declspec(section ".rodata") const f32 float_32767_tou2_0000aee8[1] = { 32767.0f };
__declspec(section ".rodata") const f64 double_to_int_mask_tou2_0000aef0 = 4503599627370496;
#pragma force_active reset
s32 gans_white_off(EventEntry* event, BOOL isFirstCall);
s32 gans_white_on(EventEntry* event, BOOL isFirstCall);
static void callback(MapTevCallbackInfo* info);
s32 eff_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_boss_stone_r(EventEntry* event, BOOL isFirstCall);
s32 starstone_sound_onoff(EventEntry* event, BOOL isFirstCall);
s32 getY(EventEntry* event, BOOL isFirstCall);
s32 item_jump(EventEntry* event, BOOL isFirstCall);
static f32 cosf(f32 x);
static f32 sinf(f32 x);
s32 confupose(EventEntry* event, BOOL isFirstCall);
s32 snd_sfx_stop(EventEntry* event, BOOL isFirstCall);
s32 burst_chain(EventEntry* event, BOOL isFirstCall);
s32 tribe_chk(EventEntry* event, BOOL isFirstCall);
void screen_tev(MapTevCallbackInfo* info);
void GXSetTexCoordGen(GXTexCoordID dst, GXTexGenType func, GXTexGenSrc src, u32 mtx);
static s32 screen_evt(EventEntry* event, BOOL isFirstCall);
s32 screen_init(EventEntry* event, BOOL isFirstCall);
static void screen_capture(CameraId cameraId, void* param);
void ext_kyaku_dispent(void);
void ext_kyaku_main(void);
void kyaku_disp(CameraId camera, void* param);
void ext_kyaku_init(void);
static f32 randf(f32 min, f32 max);
u32 __tou_rand(void);
void __tou_srand(u32 seed);
static void pose_change(Kyaku* kyaku, const char* name, const char* anim);
static void pose_main(void);
static void pose_init(void);
s32 _firstattack_setting(EventEntry* event, BOOL isFirstCall);

void DCFlushRange(void* addr, u32 nBytes);
void GXCopyTex(void* dest, GXBool clear);
u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, u8 mipmap, u8 max_lod);
void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXTexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
    f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp,
    GXBool do_edge_lod, GXAnisotropy max_aniso);
void GXLoadTexMtxImm(const f32 mtx[][4], u32 id, GXTexMtxType type);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
void GXPixModeSync(void);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevColor(GXTevRegID id, GXColor color);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras_sel, GXTevSwapSel tex_sel);
void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx);
void GXSetTexCopyDst(u16 wd, u16 ht, GXTexFmt fmt, GXBool mipmap);
void GXSetTexCopySrc(u16 left, u16 top, u16 wd, u16 ht);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXIdentity(Mtx m);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
f32 PSVECDistance(const Vec* a, const Vec* b);
void __cvt_ull_flt();
void __div2u();
void* _mapAlloc(u32 size);
f32 angleABf(f32 x1, f32 y1, f32 x2, f32 y2);
void animPoseSetMaterialFlagOff(s32 poseId, u32 mask);
void animPoseSetMaterialFlagOn(s32 poseId, u32 mask);
CameraEntry* camGetPtr(CameraId cameraId);
void dispEntry(CameraId camera, f32 order, s32 renderMode, DispCallback callback, void* param);
f32 distABf(f32 x1, f32 y1, f32 x2, f32 y2);
EffectEntry* effNameToPtr(const char* name);
f32 evtGetFloat(EventEntry* entry, s32 index);
s32 evtGetValue(EventEntry* entry, s32 index);
s32 evtSetValue(EventEntry* entry, s32 index, s32 value);
FieldBattleData* fbatGetPointer(void);
HitEntry* hitCheckFilter(HitFilterCallback callback, f32* hitX, f32* hitY, f32* hitZ, f32* distance, f32* hitNX,
                         f32* hitNY, f32* hitNZ, f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz);
s32 irand(s32 scalar);
ItemEntry* itemNameToPtr(char*);
MapObject* mapGetMapObj(const char* name);
void mapSetTevCallback(s32 index, MapTevCallback callback);
void *memset(void *dest, int ch, size_t count);
NpcEntry* npcNameToPtr(const char* name);
s32 psndSFXOn_3D(const char* name, Vec* position);
int rand(void);
int sprintf(char *s, const char *format, ...);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
asm s32 gans_white_off(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, str_000001E0@ha
	stw r0, 0x14(r1)
	addi r3, r3, str_000001E0@l
	stw r31, 0xc(r1)
	bl npcNameToPtr
	mr r31, r3
	li r3, 0xc
	li r4, 0x0
	bl mapSetTevCallback
	lwz r3, 0x104(r31)
	lis r4, 0xc00
	bl animPoseSetMaterialFlagOff
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 gans_white_on(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, str_000001E0@ha
	stw r0, 0x14(r1)
	addi r3, r3, str_000001E0@l
	stw r31, 0xc(r1)
	mr r31, r4
	bl npcNameToPtr
	cmpwi r31, 0x0
	mr r31, r3
	beq @1
	lis r4, gans_alpha@ha
	li r0, 0x0
	addi r5, r4, gans_alpha@l
	lis r3, callback@ha
	stw r0, 0x0(r5)
	addi r4, r3, callback@l
	li r3, 0xc
	bl mapSetTevCallback
	lwz r3, 0x104(r31)
	lis r4, 0xc00
	bl animPoseSetMaterialFlagOn
	@1:
	lis r3, gans_alpha@ha
	addi r4, r3, gans_alpha@l
	lwz r3, 0x0(r4)
	addi r0, r3, 0x5
	cmpwi r0, 0xff
	stw r0, 0x0(r4)
	ble @2
	li r0, 0xff
	li r3, 0x2
	stw r0, 0x0(r4)
	b @3
	@2:
	li r3, 0x0
	@3:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static void callback(MapTevCallbackInfo* info) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	lis r4, dat_tou2_0000a738@ha
	stw r0, 0x34(r1)
	stmw r27, 0x1c(r1)
	mr r27, r3
	lis r3, gans_alpha@ha
	lwz r5, dat_tou2_0000a738@l(r4)
	addi r4, r1, 0xc
	lwz r0, gans_alpha@l(r3)
	li r3, 0x1
	stw r5, 0x8(r1)
	lwz r31, 0xc(r27)
	stb r0, 0xb(r1)
	lwz r30, 0x10(r27)
	lwz r29, 0x14(r27)
	lwz r28, 0x18(r27)
	lwz r0, 0x8(r1)
	stw r0, 0xc(r1)
	bl GXSetTevColor
	mr r3, r31
	li r4, 0xff
	li r5, 0xff
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r31
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r31
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r31
	li r4, 0x0
	li r5, 0x2
	li r6, 0x3
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r31
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	mr r3, r31
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	addi r0, r31, 0x1
	stw r0, 0xc(r27)
	stw r29, 0x14(r27)
	stw r28, 0x18(r27)
	stw r30, 0x10(r27)
	lmw r27, 0x1c(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 eff_pos(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, str_00001130@ha
	stw r0, 0x14(r1)
	addi r3, r3, str_00001130@l
	stmw r30, 0x8(r1)
	bl itemNameToPtr
	lis r4, str_00001488@ha
	mr r30, r3
	addi r3, r4, str_00001488@l
	bl effNameToPtr
	lis r4, str_00001450@ha
	mr r31, r3
	addi r3, r4, str_00001450@l
	bl effNameToPtr
	cmplwi r30, 0x0
	beq @1
	cmplwi r31, 0x0
	beq @2
	lfs f0, 0x3c(r30)
	lis r4, float_15_tou2_0000ae2c@ha
	lwz r5, 0xc(r31)
	lfs f1, float_15_tou2_0000ae2c@l(r4)
	stfs f0, 0x4(r5)
	lfs f0, 0x40(r30)
	lwz r4, 0xc(r31)
	fadds f0, f1, f0
	stfs f0, 0x8(r4)
	lfs f0, 0x44(r30)
	lwz r4, 0xc(r31)
	stfs f0, 0xc(r4)
	@2:
	cmplwi r3, 0x0
	beq @1
	lfs f0, 0x3c(r30)
	lis r4, float_15_tou2_0000ae2c@ha
	lwz r5, 0xc(r3)
	lfs f1, float_15_tou2_0000ae2c@l(r4)
	stfs f0, 0x4(r5)
	lfs f0, 0x40(r30)
	lwz r4, 0xc(r3)
	fadds f0, f1, f0
	stfs f0, 0x8(r4)
	lfs f0, 0x44(r30)
	lwz r3, 0xc(r3)
	stfs f0, 0xc(r3)
	@1:
	lmw r30, 0x8(r1)
	li r3, 0x0
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_boss_stone_r(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r29, 0x14(r1)
	mr r29, r3
	lis r3, str_00001130@ha
	addi r3, r3, str_00001130@l
	lwz r31, 0x18(r29)
	bl itemNameToPtr
	lwz r30, 0x1c(r3)
	mr r3, r29
	lwz r4, 0x0(r31)
	bl evtGetFloat
	lwz r4, 0xc(r30)
	li r3, 0x2
	stfs f1, 0x1c(r4)
	lmw r29, 0x14(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 starstone_sound_onoff(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	lis r4, str_00001130@ha
	mr r31, r3
	addi r3, r4, str_00001130@l
	bl itemNameToPtr
	lwz r4, 0x1c(r3)
	cmplwi r4, 0x0
	beq @1
	cmpwi r31, 0x0
	bne @2
	lwz r3, 0xc(r4)
	lhz r0, 0x4(r3)
	rlwinm r0, r0, 0, 30, 28
	sth r0, 0x4(r3)
	@2:
	cmpwi r31, 0x1
	bne @1
	lwz r3, 0xc(r4)
	lhz r0, 0x4(r3)
	ori r0, r0, 0x4
	sth r0, 0x4(r3)
	@1:
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 getY(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r3, str_000001E0@ha
	stw r0, 0x24(r1)
	addi r3, r3, str_000001E0@l
	stmw r30, 0x18(r1)
	bl npcNameToPtr
	lis r4, str_00001108@ha
	mr r30, r3
	addi r3, r4, str_00001108@l
	bl mapGetMapObj
	lis r4, str_00001840@ha
	mr r31, r3
	addi r3, r4, str_00001840@l
	addi r4, r1, 0x8
	bl mapObjGetPos
	lis r3, float_100_tou2_0000ae3c@ha
	lfs f1, 0x38(r31)
	lfs f2, float_100_tou2_0000ae3c@l(r3)
	lfs f0, 0xc(r1)
	fadds f1, f2, f1
	fcmpo cr0, f1, f0
	ble @1
	stfs f1, 0x90(r30)
	b @2
	@1:
	lis r3, zero_tou2_0000ae40@ha
	lfs f0, zero_tou2_0000ae40@l(r3)
	stfs f0, 0x94(r30)
	stfs f0, 0x8c(r30)
	lfs f0, 0xc(r1)
	stfs f0, 0x90(r30)
	@2:
	lmw r30, 0x18(r1)
	li r3, 0x2
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 item_jump(EventEntry* event, BOOL isFirstCall) {
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
	stmw r29, 0x34(r1)
	mr r30, r3
	mr r29, r4
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x4(r31)
	mr r3, r30
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r31)
	mr r3, r30
	bl evtGetFloat
	fmr f29, f1
	lis r3, str_00001130@ha
	addi r3, r3, str_00001130@l
	bl itemNameToPtr
	cmpwi r29, 0x0
	mr r31, r3
	beq @1
	lfs f0, 0x40(r31)
	fmr f1, f30
	fmr f2, f29
	lfs f3, 0x3c(r31)
	fsubs f28, f31, f0
	lfs f4, 0x44(r31)
	bl distABf
	lis r4, float_1_tou2_0000ae44@ha
	lis r3, float_0p5_tou2_0000ae48@ha
	lfs f0, float_1_tou2_0000ae44@l(r4)
	fmr f3, f30
	lfs f6, float_0p5_tou2_0000ae48@l(r3)
	fmr f4, f29
	fdivs f5, f1, f0
	lfs f1, 0x3c(r31)
	lfs f2, 0x44(r31)
	fdivs f0, f28, f5
	stfs f5, 0xc(r1)
	fmuls f5, f6, f5
	fmadds f0, f5, f6, f0
	stfs f0, 0x10(r1)
	bl angleABf
	lwz r0, 0xc(r1)
	stfs f1, 0x8(r1)
	lwz r3, 0x10(r1)
	stw r0, 0x78(r30)
	lwz r0, 0x8(r1)
	stw r3, 0x7c(r30)
	stw r0, 0x80(r30)
	@1:
	lis r3, float_6p2832_tou2_0000ae4c@ha
	lfs f2, 0x80(r30)
	addi r4, r3, float_6p2832_tou2_0000ae4c@l
	lfs f4, 0x78(r30)
	lfs f0, 0x0(r4)
	lis r3, float_360_tou2_0000ae50@ha
	lfs f3, 0x7c(r30)
	fmuls f1, f0, f2
	lfs f0, float_360_tou2_0000ae50@l(r3)
	stfs f4, 0xc(r1)
	fdivs f1, f1, f0
	stfs f3, 0x10(r1)
	stfs f2, 0x8(r1)
	bl sinf
	lis r3, float_6p2832_tou2_0000ae4c@ha
	lis r5, float_1_tou2_0000ae44@ha
	addi r4, r3, float_6p2832_tou2_0000ae4c@l
	lfs f0, 0x8(r1)
	lfs f2, 0x0(r4)
	lis r3, float_360_tou2_0000ae50@ha
	lfs f4, float_1_tou2_0000ae44@l(r5)
	fmuls f2, f2, f0
	lfs f3, 0x3c(r31)
	lfs f0, float_360_tou2_0000ae50@l(r3)
	fmadds f3, f4, f1, f3
	fdivs f1, f2, f0
	stfs f3, 0x3c(r31)
	bl cosf
	lis r3, float_1_tou2_0000ae44@ha
	lfs f2, 0x44(r31)
	addi r5, r3, float_1_tou2_0000ae44@l
	lfs f0, 0xc(r1)
	lfs f5, 0x0(r5)
	lis r4, float_0p5_tou2_0000ae48@ha
	lis r3, zero_tou2_0000ae40@ha
	lfs f3, 0x10(r1)
	fnmsubs f4, f5, f1, f2
	lfs f2, float_0p5_tou2_0000ae48@l(r4)
	fsubs f1, f0, f5
	lfs f0, zero_tou2_0000ae40@l(r3)
	fsubs f2, f3, f2
	stfs f4, 0x44(r31)
	fcmpo cr0, f1, f0
	lfs f4, 0x40(r31)
	stfs f1, 0xc(r1)
	fadds f0, f4, f3
	stfs f2, 0x10(r1)
	stfs f0, 0x40(r31)
	bge @2
	stfs f30, 0x3c(r31)
	lis r5, vec3_tou2_0000a6cc@ha
	lis r3, str_00001864@ha
	addi r4, r1, 0x20
	stfs f31, 0x40(r31)
	addi r7, r5, vec3_tou2_0000a6cc@l
	addi r3, r3, str_00001864@l
	stfs f29, 0x44(r31)
	lwz r6, 0x0(r7)
	lwz r5, 0x4(r7)
	lwz r0, 0x8(r7)
	stw r6, 0x14(r1)
	lfs f0, 0x3c(r31)
	stw r5, 0x18(r1)
	lfs f1, 0x40(r31)
	stfs f0, 0x14(r1)
	lfs f0, 0x44(r31)
	stw r0, 0x1c(r1)
	lwz r6, 0x14(r1)
	stfs f1, 0x18(r1)
	stfs f0, 0x1c(r1)
	lwz r5, 0x18(r1)
	lwz r0, 0x1c(r1)
	stw r6, 0x20(r1)
	stw r5, 0x24(r1)
	stw r0, 0x28(r1)
	bl psndSFXOn_3D
	li r3, 0x1
	b @3
	@2:
	lwz r4, 0xc(r1)
	li r3, 0x0
	lwz r0, 0x10(r1)
	stw r4, 0x78(r30)
	stw r0, 0x7c(r30)
	@3:
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	psq_l f30, 0x68(r1), 0, 0
	lfd f30, 0x60(r1)
	psq_l f29, 0x58(r1), 0, 0
	lfd f29, 0x50(r1)
	psq_l f28, 0x48(r1), 0, 0
	lfd f28, 0x40(r1)
	lmw r29, 0x34(r1)
	lwz r0, 0x84(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm static f32 cosf(f32 x) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl cos
	lwz r0, 0x14(r1)
	frsp f1, f1
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static f32 sinf(f32 x) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl sin
	lwz r0, 0x14(r1)
	frsp f1, f1
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 confupose(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	bl npcNameToPtr
	lwz r5, 0x28(r3)
	mr r3, r30
	lwz r4, 0x4(r31)
	lwz r5, 0x24(r5)
	bl evtSetValue
	lmw r30, 0x8(r1)
	li r3, 0x2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 snd_sfx_stop(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl psndMapChange
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 burst_chain(EventEntry* event, BOOL isFirstCall) {
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
	stmw r27, 0x2c(r1)
	mr r27, r3
	lwz r28, 0x18(r3)
	lwz r4, 0x0(r28)
	bl evtGetValue
	lwz r4, 0x4(r28)
	mr r28, r3
	mr r3, r27
	bl evtGetValue
	mr r0, r3
	mr r3, r28
	mr r31, r0
	bl npcNameToPtr
	lis r4, str_0000187C@ha
	mr r28, r3
	addi r4, r4, str_0000187C@l
	mr r5, r31
	addi r3, r1, 0x8
	li r6, 0x0
	crclr 6
	bl sprintf
	addi r3, r1, 0x8
	bl npcNameToPtr
	lwz r8, 0x8c(r28)
	lis r7, float_3_tou2_0000ae74@ha
	lwz r0, 0x90(r28)
	lis r6, float_1_tou2_0000ae44@ha
	lis r5, float_10_tou2_0000ae78@ha
	lis r4, float_210_tou2_0000ae7c@ha
	stw r8, 0x8c(r3)
	lis r8, str_0000187C@ha
	lfs f29, float_3_tou2_0000ae74@l(r7)
	li r27, 0x0
	stw r0, 0x90(r3)
	lfs f30, float_1_tou2_0000ae44@l(r6)
	lwz r0, 0x94(r28)
	addi r28, r8, str_0000187C@l
	lfs f31, float_10_tou2_0000ae78@l(r5)
	stw r0, 0x94(r3)
	lfs f28, float_210_tou2_0000ae7c@l(r4)
	@1:
	mr r4, r28
	mr r5, r31
	mr r6, r27
	addi r3, r1, 0x8
	crclr 6
	bl sprintf
	addi r3, r1, 0x8
	bl npcNameToPtr
	mr r29, r3
	mr r4, r28
	mr r5, r31
	addi r3, r1, 0x8
	addi r6, r27, 0x1
	crclr 6
	bl sprintf
	addi r3, r1, 0x8
	bl npcNameToPtr
	mr r30, r3
	addi r3, r29, 0x8c
	lfs f0, 0x90(r30)
	addi r4, r30, 0x8c
	fsubs f0, f0, f29
	stfs f0, 0x90(r30)
	bl PSVECDistance
	fdivs f2, f31, f1
	lfs f0, 0x8c(r29)
	lfs f1, 0x8c(r30)
	fsubs f2, f30, f2
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x8c(r30)
	lfs f0, 0x90(r29)
	lfs f1, 0x90(r30)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x90(r30)
	lfs f0, 0x94(r29)
	lfs f1, 0x94(r30)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x94(r30)
	lfs f1, 0x8c(r30)
	fcmpo cr0, f1, f28
	bgt @2
	lis r3, float_neg210_tou2_0000ae80@ha
	lfs f0, float_neg210_tou2_0000ae80@l(r3)
	fcmpo cr0, f1, f0
	bge @3
	@2:
	lis r3, zero_tou2_0000ae40@ha
	lfs f1, 0x90(r30)
	lfs f0, zero_tou2_0000ae40@l(r3)
	fcmpo cr0, f1, f0
	bge @4
	stfs f0, 0x90(r30)
	b @4
	@3:
	lis r3, float_60_tou2_0000ae84@ha
	lfs f1, 0x90(r30)
	lfs f0, float_60_tou2_0000ae84@l(r3)
	fcmpo cr0, f1, f0
	bge @4
	stfs f0, 0x90(r30)
	@4:
	addi r27, r27, 0x1
	cmpwi r27, 0x4
	blt @1
	li r3, 0x0
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	psq_l f30, 0x68(r1), 0, 0
	lfd f30, 0x60(r1)
	psq_l f29, 0x58(r1), 0, 0
	lfd f29, 0x50(r1)
	psq_l f28, 0x48(r1), 0, 0
	lfd f28, 0x40(r1)
	lmw r27, 0x2c(r1)
	lwz r0, 0x84(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm s32 tribe_chk(EventEntry* event, BOOL isFirstCall) {
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
	mr r0, r3
	mr r3, r30
	mr r30, r0
	bl npcNameToPtr
	lwz r3, 0x28(r3)
	mr r4, r30
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @1
	lwz r4, 0x8(r31)
	mr r3, r29
	li r5, 0x1
	bl evtSetValue
	b @2
	@1:
	lwz r4, 0x8(r31)
	mr r3, r29
	li r5, 0x0
	bl evtSetValue
	@2:
	lmw r29, 0x14(r1)
	li r3, 0x2
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void screen_tev(MapTevCallbackInfo* info) {
	nofralloc
	stwu r1, -0xe0(r1)
	mflr r0
	lis r4, screen_wp@ha
	stw r0, 0xe4(r1)
	stmw r23, 0xbc(r1)
	mr r27, r3
	addi r3, r4, screen_wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x4(r3)
	cmpwi r0, 0x0
	beq @1
	lwz r0, 0x24(r3)
	cmpwi r0, 0x0
	beq @2
	lwz r29, 0x2c(r3)
	li r28, 0x0
	@3:
	slwi r0, r28, 30
	srwi r4, r28, 31
	subf r0, r4, r0
	srawi r5, r28, 2
	rotlwi r3, r0, 2
	li r0, 0x40
	addze r31, r5
	clrlwi r9, r28, 31
	add r30, r3, r4
	li r10, 0x0
	slwi r4, r31, 8
	li r5, 0xff
	slwi r3, r30, 3
	mtctr r0
	@4:
	srawi r6, r10, 3
	slwi r0, r10, 29
	srwi r8, r10, 31
	addi r10, r10, 0x1
	addze r11, r6
	subf r0, r8, r0
	subfic r6, r9, 0x0
	rotlwi r7, r0, 3
	slwi r0, r11, 5
	subfe r6, r6, r6
	add r7, r7, r8
	add r0, r0, r4
	and r6, r5, r6
	add r0, r0, r7
	add r0, r0, r3
	stbx r6, r29, r0
	bdnz @4
	bl rand
	li r4, 0x64
	slwi r25, r31, 8
	divw r0, r3, r4
	slwi r26, r30, 3
	li r30, 0x0
	mullw r0, r0, r4
	subf r3, r0, r3
	addi r31, r3, 0x64
	b @5
	@6:
	bl rand
	slwi r0, r3, 30
	srwi r3, r3, 31
	subf r0, r3, r0
	rotlwi r0, r0, 2
	add r3, r0, r3
	addi r24, r3, 0x2
	bl rand
	subfic r4, r24, 0x41
	divw r0, r3, r4
	mullw r0, r0, r4
	subf r23, r0, r3
	bl rand
	slwi r0, r3, 24
	srwi r3, r3, 31
	subf r0, r3, r0
	add r4, r23, r24
	rotlwi r0, r0, 8
	mr r5, r23
	add r3, r0, r3
	subf r0, r23, r4
	clrlwi r6, r3, 24
	mtctr r0
	cmpw r23, r4
	bge @7
	@8:
	srawi r4, r5, 3
	slwi r0, r5, 29
	srwi r3, r5, 31
	addi r5, r5, 0x1
	addze r4, r4
	subf r0, r3, r0
	slwi r4, r4, 5
	rotlwi r0, r0, 3
	add r4, r4, r25
	add r0, r0, r3
	add r0, r4, r0
	add r0, r0, r26
	stbx r6, r29, r0
	bdnz @8
	@7:
	addi r30, r30, 0x1
	@5:
	cmpw r30, r31
	blt @6
	addi r28, r28, 0x1
	cmpwi r28, 0x40
	blt @3
	mr r3, r29
	li r4, 0x1000
	bl DCFlushRange
	mr r4, r29
	addi r3, r1, 0x8
	li r5, 0x40
	li r6, 0x40
	li r7, 0x1
	li r8, 0x1
	li r9, 0x1
	li r10, 0x0
	bl GXInitTexObj
	lis r4, zero_tou2_0000ae40@ha
	addi r3, r1, 0x8
	addi r5, r4, zero_tou2_0000ae40@l
	li r4, 0x0
	lfs f1, 0x0(r5)
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	fmr f2, f1
	li r8, 0x0
	fmr f3, f1
	bl GXInitTexObjLOD
	addi r3, r1, 0x8
	li r4, 0x0
	bl GXLoadTexObj
	b @9
	@2:
	lwz r4, 0x0(r3)
	addi r3, r1, 0x8
	li r5, 0x130
	li r6, 0xf0
	li r7, 0x4
	li r8, 0x0
	li r9, 0x0
	li r10, 0x0
	bl GXInitTexObj
	lis r4, zero_tou2_0000ae40@ha
	addi r3, r1, 0x8
	addi r5, r4, zero_tou2_0000ae40@l
	li r4, 0x0
	lfs f1, 0x0(r5)
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	fmr f2, f1
	li r8, 0x0
	fmr f3, f1
	bl GXInitTexObjLOD
	@9:
	addi r3, r1, 0x8
	li r4, 0x0
	bl GXLoadTexObj
	lis r4, inta_tex@ha
	addi r3, r1, 0x8
	addi r4, r4, inta_tex@l
	li r5, 0x4
	li r6, 0x8
	li r7, 0x0
	li r8, 0x1
	li r9, 0x1
	li r10, 0x0
	bl GXInitTexObj
	lis r4, zero_tou2_0000ae40@ha
	addi r3, r1, 0x8
	addi r5, r4, zero_tou2_0000ae40@l
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
	li r4, 0x1
	bl GXLoadTexObj
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x1
	li r4, 0x1
	li r5, 0x1
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x1
	li r4, 0xf
	li r5, 0x8
	li r6, 0x0
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x6
	bl GXSetTevAlphaIn
	lis r3, screen_wp@ha
	addi r5, r3, screen_wp@l
	lwz r6, 0x0(r5)
	lwz r0, 0x24(r6)
	cmpwi r0, 0x0
	bne @10
	lwz r4, 0x20(r6)
	li r3, 0xc8
	addi r0, r4, 0x1
	stw r0, 0x20(r6)
	lwz r4, 0x0(r5)
	lwz r4, 0x20(r4)
	divw r0, r4, r3
	mullw r0, r0, r3
	subf. r0, r0, r4
	bne @11
	bl rand
	li r4, 0x3
	divw r0, r3, r4
	mullw r0, r0, r4
	subf r0, r0, r3
	cmpwi r0, 0x1
	beq @12
	bge @11
	cmpwi r0, 0x0
	bge @13
	b @11
	b @11
	@13:
	lis r4, screen_wp@ha
	lis r3, float_1_tou2_0000ae44@ha
	addi r4, r4, screen_wp@l
	lis r5, zero_tou2_0000ae40@ha
	lwz r4, 0x0(r4)
	lfs f0, float_1_tou2_0000ae44@l(r3)
	lfs f2, 0x8(r4)
	lfs f1, zero_tou2_0000ae40@l(r5)
	fsubs f0, f0, f2
	fdivs f2, f0, f2
	bl randf
	lis r4, screen_wp@ha
	lis r3, float_1_tou2_0000ae44@ha
	addi r6, r4, screen_wp@l
	lfs f0, float_1_tou2_0000ae44@l(r3)
	lwz r5, 0x0(r6)
	lis r4, zero_tou2_0000ae40@ha
	stfs f1, 0x14(r5)
	lfs f1, zero_tou2_0000ae40@l(r4)
	lwz r3, 0x0(r6)
	lfs f2, 0x8(r3)
	fsubs f0, f0, f2
	fdivs f2, f0, f2
	bl randf
	lis r3, screen_wp@ha
	addi r3, r3, screen_wp@l
	lwz r3, 0x0(r3)
	stfs f1, 0x1c(r3)
	b @11
	@12:
	lis r4, float_1_tou2_0000ae44@ha
	lis r3, float_0p25_tou2_0000ae88@ha
	lfs f1, float_1_tou2_0000ae44@l(r4)
	lfs f2, float_0p25_tou2_0000ae88@l(r3)
	bl randf
	lis r3, screen_wp@ha
	addi r3, r3, screen_wp@l
	lwz r3, 0x0(r3)
	stfs f1, 0xc(r3)
	@11:
	lis r3, screen_wp@ha
	lis r4, float_60_tou2_0000ae84@ha
	addi r6, r3, screen_wp@l
	lwz r7, 0x0(r6)
	addi r5, r4, float_60_tou2_0000ae84@l
	lis r3, float_1_tou2_0000ae44@ha
	lfs f2, 0x0(r5)
	lfs f1, 0x8(r7)
	addi r4, r3, float_1_tou2_0000ae44@l
	lfs f0, 0xc(r7)
	addi r3, r1, 0x58
	lfs f3, 0x0(r4)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	fadds f0, f1, f0
	stfs f0, 0x8(r7)
	lwz r4, 0x0(r6)
	lfs f1, 0x10(r4)
	lfs f0, 0x14(r4)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	fadds f0, f1, f0
	stfs f0, 0x10(r4)
	lwz r4, 0x0(r6)
	lfs f1, 0x18(r4)
	lfs f0, 0x1c(r4)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	fadds f0, f1, f0
	stfs f0, 0x18(r4)
	lwz r4, 0x0(r6)
	lfs f1, 0x8(r4)
	fmr f2, f1
	bl PSMTXScale
	lis r4, screen_wp@ha
	lis r3, float_1_tou2_0000ae44@ha
	addi r4, r4, screen_wp@l
	lfs f0, float_1_tou2_0000ae44@l(r3)
	lwz r4, 0x0(r4)
	lfs f1, 0x8(r4)
	lfs f2, 0x18(r4)
	fsubs f0, f0, f1
	fdivs f1, f0, f1
	fcmpo cr0, f2, f1
	ble @14
	fmr f2, f1
	@14:
	lfs f0, 0x10(r4)
	fcmpo cr0, f0, f1
	ble @15
	b @16
	@15:
	fmr f1, f0
	@16:
	lis r3, zero_tou2_0000ae40@ha
	lfs f3, zero_tou2_0000ae40@l(r3)
	addi r3, r1, 0x28
	bl PSMTXTrans
	addi r3, r1, 0x58
	addi r4, r1, 0x28
	addi r5, r1, 0x88
	bl PSMTXConcat
	b @17
	@10:
	lis r6, float_4p75_tou2_0000ae8c@ha
	lis r5, float_3p75_tou2_0000ae90@ha
	lis r4, zero_tou2_0000ae40@ha
	lfs f1, float_4p75_tou2_0000ae8c@l(r6)
	lfs f2, float_3p75_tou2_0000ae90@l(r5)
	addi r3, r1, 0x88
	lfs f3, zero_tou2_0000ae40@l(r4)
	bl PSMTXScale
	@17:
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x1e
	bl GXSetTexCoordGen
	addi r3, r1, 0x88
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	li r3, 0x4
	bl camGetPtr
	lis r4, float_100_tou2_0000ae3c@ha
	lfs f0, 0x14(r3)
	addi r5, r4, float_100_tou2_0000ae3c@l
	lis r6, float_1_tou2_0000ae44@ha
	lfs f1, 0x0(r5)
	lis r5, float_6_tou2_0000ae98@ha
	lis r4, float_1000_tou2_0000ae9c@ha
	lis r3, float_16_tou2_0000ae94@ha
	fsubs f2, f1, f0
	lfs f0, float_1000_tou2_0000ae9c@l(r4)
	lfs f1, float_1_tou2_0000ae44@l(r6)
	lfs f4, float_6_tou2_0000ae98@l(r5)
	fdivs f2, f2, f0
	lfs f0, float_16_tou2_0000ae94@l(r3)
	addi r3, r1, 0x88
	fmr f3, f1
	fmadds f2, f4, f2, f0
	bl PSMTXScale
	li r3, 0x1
	li r4, 0x1
	li r5, 0x4
	li r6, 0x21
	bl GXSetTexCoordGen
	addi r3, r1, 0x88
	li r4, 0x21
	li r5, 0x1
	bl GXLoadTexMtxImm
	li r0, 0x2
	stw r0, 0xc(r27)
	stw r0, 0x14(r27)
	stw r0, 0x10(r27)
	@1:
	lmw r23, 0xbc(r1)
	lwz r0, 0xe4(r1)
	mtlr r0
	addi r1, r1, 0xe0
	blr
}

asm void GXSetTexCoordGen(GXTexCoordID dst, GXTexGenType func, GXTexGenSrc src, u32 mtx) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r7, 0x0
	li r8, 0x7d
	stw r0, 0x14(r1)
	bl GXSetTexCoordGen2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static s32 screen_evt(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, float_1000_tou2_0000ae9c@ha
	lis r4, screen_capture@ha
	addi r6, r3, float_1000_tou2_0000ae9c@l
	stw r0, 0x14(r1)
	lfs f1, 0x0(r6)
	addi r5, r4, screen_capture@l
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

asm s32 screen_init(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r4, 0x1e0
	li r5, 0x0
	stw r0, 0x14(r1)
	li r6, 0x0
	li r7, 0x0
	stmw r30, 0x8(r1)
	mr r31, r3
	li r3, 0x260
	bl GXGetTexBufferSize
	mr r0, r3
	li r3, 0x30
	mr r30, r0
	bl _mapAlloc
	lis r4, screen_wp@ha
	stw r3, screen_wp@l(r4)
	mr r3, r30
	bl _mapAlloc
	lis r4, screen_wp@ha
	lis r5, float_1_tou2_0000ae44@ha
	addi r9, r4, screen_wp@l
	lis r4, zero_tou2_0000ae40@ha
	lwz r6, 0x0(r9)
	addi r7, r5, float_1_tou2_0000ae44@l
	addi r5, r4, zero_tou2_0000ae40@l
	lis r4, float_neg1_tou2_0000aea0@ha
	stw r3, 0x0(r6)
	addi r6, r4, float_neg1_tou2_0000aea0@l
	li r0, 0x0
	lfs f2, 0x0(r7)
	lwz r7, 0x0(r9)
	li r3, 0x40
	lfs f1, 0x0(r5)
	li r4, 0x40
	stw r0, 0x4(r7)
	li r5, 0x1
	lfs f0, 0x0(r6)
	li r6, 0x0
	lwz r8, 0x0(r9)
	li r7, 0x0
	stfs f2, 0xc(r8)
	lwz r8, 0x0(r9)
	stfs f2, 0x8(r8)
	lwz r8, 0x0(r9)
	stfs f1, 0x14(r8)
	lwz r8, 0x0(r9)
	stfs f1, 0x10(r8)
	lwz r8, 0x0(r9)
	stfs f1, 0x1c(r8)
	lwz r8, 0x0(r9)
	stfs f1, 0x18(r8)
	lwz r8, 0x0(r9)
	stw r0, 0x20(r8)
	lwz r8, 0x0(r9)
	stfs f0, 0x28(r8)
	bl GXGetTexBufferSize
	bl _mapAlloc
	lis r5, screen_wp@ha
	lis r4, 0xf5de
	addi r5, r5, screen_wp@l
	lwz r5, 0x0(r5)
	addi r4, r4, 0x180
	stw r3, 0x2c(r5)
	mr r3, r31
	bl evtGetValue
	cmpwi r3, 0xa3
	bne @1
	lis r3, screen_wp@ha
	li r0, 0x1
	addi r3, r3, screen_wp@l
	lwz r3, 0x0(r3)
	stw r0, 0x24(r3)
	@1:
	lmw r30, 0x8(r1)
	li r3, 0x2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static void screen_capture(CameraId cameraId, void* param) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x0
	li r4, 0x0
	stw r0, 0x14(r1)
	li r5, 0x260
	li r6, 0x1e0
	bl GXSetTexCopySrc
	li r3, 0x130
	li r4, 0xf0
	li r5, 0x4
	li r6, 0x1
	bl GXSetTexCopyDst
	lis r3, screen_wp@ha
	li r4, 0x0
	addi r3, r3, screen_wp@l
	lwz r3, 0x0(r3)
	lwz r3, 0x0(r3)
	bl GXCopyTex
	bl GXPixModeSync
	lis r3, screen_wp@ha
	li r0, 0x1
	addi r3, r3, screen_wp@l
	lwz r3, 0x0(r3)
	stw r0, 0x4(r3)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void ext_kyaku_dispent(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, zero_tou2_0000ae40@ha
	lis r4, kyaku_disp@ha
	addi r6, r3, zero_tou2_0000ae40@l
	stw r0, 0x14(r1)
	lfs f1, 0x0(r6)
	addi r5, r4, kyaku_disp@l
	li r3, 0x4
	li r4, 0x1
	li r6, 0x0
	bl dispEntry
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void ext_kyaku_main(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl pose_main
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void kyaku_disp(CameraId camera, void* param) {
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

asm void ext_kyaku_init(void) {
	nofralloc
	stwu r1, -0xa0(r1)
	mflr r0
	stw r0, 0xa4(r1)
	stfd f31, 0x90(r1)
	psq_st f31, 0x98(r1), 0, 0
	stfd f30, 0x80(r1)
	psq_st f30, 0x88(r1), 0, 0
	stfd f29, 0x70(r1)
	psq_st f29, 0x78(r1), 0, 0
	stfd f28, 0x60(r1)
	psq_st f28, 0x68(r1), 0, 0
	stmw r22, 0x38(r1)
	li r3, 0x510
	bl _mapAlloc
	lis r5, kyaku_wp@ha
	li r4, 0x0
	addi r6, r5, kyaku_wp@l
	li r5, 0x510
	stw r3, 0x0(r6)
	bl memset
	bl extGetPoseNum
	lis r4, kyaku_wp@ha
	addi r5, r4, kyaku_wp@l
	lwz r4, 0x0(r5)
	stw r3, 0x4(r4)
	lwz r3, 0x0(r5)
	lwz r0, 0x4(r3)
	slwi r3, r0, 5
	bl _mapAlloc
	lis r5, kyaku_wp@ha
	li r4, 0x0
	addi r6, r5, kyaku_wp@l
	lwz r5, 0x0(r6)
	stw r3, 0x8(r5)
	lwz r3, 0x0(r6)
	lwz r0, 0x4(r3)
	lwz r3, 0x8(r3)
	slwi r5, r0, 5
	bl memset
	bl pose_init
	lis r3, 0x25b
	addi r3, r3, 0xe2b
	bl __tou_srand
	bl extGetPosePtr
	lis r5, kyaku_wp@ha
	lis r4, zero_tou2_0000ae40@ha
	addi r30, r5, kyaku_wp@l
	lis r7, float_6p2832_tou2_0000aea4@ha
	lwz r8, 0x0(r30)
	addi r31, r4, zero_tou2_0000ae40@l
	lis r6, gp@ha
	lis r5, str_000000A0@ha
	lis r4, vec3_tou2_00009638@ha
	lwz r27, 0x8(r8)
	lfs f31, 0x0(r31)
	mr r28, r3
	addi r23, r7, float_6p2832_tou2_0000aea4@l
	addi r24, r6, gp@l
	addi r25, r5, str_000000A0@l
	addi r26, r4, vec3_tou2_00009638@l
	li r29, 0x0
	b @1
	@2:
	lwz r0, 0x0(r28)
	ori r0, r0, 0x7
	stw r0, 0x0(r28)
	lwz r3, 0xc(r28)
	bl PSMTXIdentity
	@3:
	bl __tou_rand
	li r6, 0x64
	li r0, 0x1e
	divwu r5, r3, r6
	lfs f1, 0x0(r31)
	lfs f2, 0x0(r23)
	li r4, -0x1
	mullw r5, r5, r6
	subf r3, r5, r3
	subfc r0, r0, r3
	subfze r22, r4
	bl randf
	cmpwi r22, 0x0
	fmr f29, f1
	bne @4
	lis r4, float_250_tou2_0000aea8@ha
	lis r3, float_500_tou2_0000aeac@ha
	lfs f1, float_250_tou2_0000aea8@l(r4)
	lfs f2, float_500_tou2_0000aeac@l(r3)
	bl randf
	fmr f30, f1
	b @5
	@4:
	lis r3, float_0p7854_tou2_0000aebc@ha
	li r0, 0x0
	lfs f0, float_0p7854_tou2_0000aebc@l(r3)
	fcmpo cr0, f29, f0
	blt @6
	lis r3, float_5p4978_tou2_0000aec0@ha
	lfs f0, float_5p4978_tou2_0000aec0@l(r3)
	fcmpo cr0, f29, f0
	ble @7
	@6:
	li r0, 0x1
	@7:
	cmpwi r0, 0x0
	beq @8
	lis r4, float_550_tou2_0000aeb0@ha
	lis r3, float_650_tou2_0000aeb4@ha
	lfs f1, float_550_tou2_0000aeb0@l(r4)
	lfs f2, float_650_tou2_0000aeb4@l(r3)
	bl randf
	b @9
	@8:
	lis r4, float_550_tou2_0000aeb0@ha
	lis r3, float_850_tou2_0000aeb8@ha
	lfs f1, float_550_tou2_0000aeb0@l(r4)
	lfs f2, float_850_tou2_0000aeb8@l(r3)
	bl randf
	@9:
	fmr f30, f1
	@5:
	fmr f1, f29
	bl sinf
	fmuls f28, f30, f1
	fmr f1, f29
	bl cosf
	cmpwi r22, 0x0
	fmuls f3, f30, f1
	bne @10
	lis r3, double_70_tou2_0000aec8@ha
	fabs f1, f3
	lfd f0, double_70_tou2_0000aec8@l(r3)
	fcmpo cr0, f1, f0
	ble @3
	lis r3, zero_tou2_0000ae40@ha
	lis r5, float_1E05_tou2_0000aed0@ha
	lfs f4, zero_tou2_0000ae40@l(r3)
	lis r4, float_100_tou2_0000ae3c@ha
	lfs f0, float_1E05_tou2_0000aed0@l(r5)
	lis r3, float_neg1_tou2_0000aea0@ha
	fmr f1, f28
	lfs f2, float_100_tou2_0000ae3c@l(r4)
	lfs f5, float_neg1_tou2_0000aea0@l(r3)
	fmr f6, f4
	stfs f0, 0x14(r1)
	addi r4, r1, 0x20
	addi r5, r1, 0x1c
	addi r6, r1, 0x18
	addi r7, r1, 0x14
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @3
	lis r3, zero_tou2_0000ae40@ha
	lfs f0, 0x1c(r1)
	lfs f1, zero_tou2_0000ae40@l(r3)
	fcmpu cr0, f1, f0
	bne @3
	lfs f0, 0x20(r1)
	fmr f2, f1
	lwz r3, 0xc(r28)
	stfs f0, 0xc(r3)
	lfs f0, 0x18(r1)
	lwz r3, 0xc(r28)
	stfs f0, 0x2c(r3)
	lfs f3, 0x20(r1)
	lfs f4, 0x18(r1)
	bl angleABf
	stfs f1, 0x4(r28)
	b @11
	@10:
	lis r3, zero_tou2_0000ae40@ha
	lis r5, float_1E05_tou2_0000aed0@ha
	lfs f4, zero_tou2_0000ae40@l(r3)
	lis r4, float_500_tou2_0000aeac@ha
	lfs f0, float_1E05_tou2_0000aed0@l(r5)
	lis r3, float_neg1_tou2_0000aea0@ha
	fmr f1, f28
	lfs f2, float_500_tou2_0000aeac@l(r4)
	lfs f5, float_neg1_tou2_0000aea0@l(r3)
	fmr f6, f4
	stfs f0, 0x14(r1)
	addi r4, r1, 0x20
	addi r5, r1, 0x1c
	addi r6, r1, 0x18
	addi r7, r1, 0x14
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @3
	lfs f1, 0x20(r1)
	lis r3, float_570_tou2_0000aed4@ha
	lwz r4, 0xc(r28)
	lfs f0, float_570_tou2_0000aed4@l(r3)
	stfs f1, 0xc(r4)
	lfs f1, 0x1c(r1)
	lwz r3, 0xc(r28)
	stfs f1, 0x1c(r3)
	lfs f1, 0x18(r1)
	lwz r3, 0xc(r28)
	stfs f1, 0x2c(r3)
	lfs f1, 0x18(r1)
	fcmpo cr0, f1, f0
	ble @12
	lfs f3, 0x20(r1)
	lis r3, float_40_tou2_0000aed8@ha
	lfs f0, float_40_tou2_0000aed8@l(r3)
	fabs f1, f3
	fcmpo cr0, f1, f0
	ble @12
	lis r3, float_60_tou2_0000ae84@ha
	lfs f0, float_60_tou2_0000ae84@l(r3)
	fcmpo cr0, f1, f0
	bge @12
	lis r3, zero_tou2_0000ae40@ha
	lwz r5, 0xc(r28)
	lfs f0, zero_tou2_0000ae40@l(r3)
	lfs f2, 0xc(r5)
	fcmpo cr0, f3, f0
	ble @13
	li r0, -0xf
	b @14
	@13:
	li r0, 0xf
	@14:
	xoris r3, r0, 0x8000
	lis r0, 0x4330
	stw r3, 0x34(r1)
	lis r4, double_to_int_tou2_0000aee0@ha
	lfd f1, double_to_int_tou2_0000aee0@l(r4)
	stw r0, 0x30(r1)
	lfd f0, 0x30(r1)
	fsubs f0, f0, f1
	fadds f0, f2, f0
	stfs f0, 0xc(r5)
	@12:
	lis r3, zero_tou2_0000ae40@ha
	lfs f3, 0x20(r1)
	lfs f1, zero_tou2_0000ae40@l(r3)
	lfs f4, 0x18(r1)
	fmr f2, f1
	bl angleABf
	stfs f1, 0x4(r28)
	@11:
	lwz r3, 0x0(r24)
	mr r4, r25
	addi r3, r3, 0x11c
	bl strcmp
	cmpwi r3, 0x0
	beq @15
	lwz r4, 0xc(r28)
	lis r3, float_350_tou2_0000aedc@ha
	lfs f0, float_350_tou2_0000aedc@l(r3)
	lfs f1, 0x2c(r4)
	fcmpo cr0, f1, f0
	ble @15
	lwz r0, 0x0(r28)
	clrrwi r0, r0, 1
	stw r0, 0x0(r28)
	@15:
	lwz r3, 0xc(r28)
	lfs f0, 0x1c(r3)
	fcmpu cr0, f31, f0
	beq @16
	lhz r0, 0x0(r27)
	ori r0, r0, 0x1
	sth r0, 0x0(r27)
	@16:
	lwz r4, 0xc(r28)
	li r3, 0x3e8
	lwz r0, 0x0(r26)
	lwz r5, 0x4(r26)
	stw r0, 0x24(r1)
	lfs f0, 0xc(r4)
	lwz r0, 0x8(r26)
	stfs f0, 0x24(r1)
	lfs f1, 0x1c(r4)
	stw r5, 0x28(r1)
	lfs f0, 0x2c(r4)
	stw r0, 0x2c(r1)
	lwz r0, 0x24(r1)
	stfs f1, 0x28(r1)
	stfs f0, 0x2c(r1)
	lwz r4, 0x28(r1)
	stw r0, 0x4(r27)
	lwz r0, 0x2c(r1)
	stw r4, 0x8(r27)
	stw r0, 0xc(r27)
	bl irand
	slwi r0, r3, 30
	srwi r3, r3, 31
	subf r0, r3, r0
	rotlwi r0, r0, 2
	add r0, r0, r3
	cmpwi r0, 0x2
	beq @17
	bge @18
	cmpwi r0, 0x0
	beq @19
	bge @20
	b @21
	@18:
	cmpwi r0, 0x4
	bge @21
	b @22
	@19:
	lis r3, str_00000000@ha
	lis r5, str_0000000C@ha
	addi r4, r3, str_00000000@l
	mr r3, r27
	addi r5, r5, str_0000000C@l
	bl pose_change
	b @21
	@20:
	lis r3, str_00000014@ha
	lis r5, str_00000020@ha
	addi r4, r3, str_00000014@l
	mr r3, r27
	addi r5, r5, str_00000020@l
	bl pose_change
	b @21
	@17:
	lis r3, str_00000028@ha
	lis r5, str_00000030@ha
	addi r4, r3, str_00000028@l
	mr r3, r27
	addi r5, r5, str_00000030@l
	bl pose_change
	b @21
	@22:
	lis r3, str_00000034@ha
	lis r5, str_00000040@ha
	addi r4, r3, str_00000034@l
	mr r3, r27
	addi r5, r5, str_00000040@l
	bl pose_change
	@21:
	addi r29, r29, 0x1
	addi r28, r28, 0x20
	addi r27, r27, 0x20
	@1:
	lwz r3, 0x0(r30)
	lwz r0, 0x4(r3)
	cmpw r29, r0
	blt @2
	psq_l f31, 0x98(r1), 0, 0
	lfd f31, 0x90(r1)
	psq_l f30, 0x88(r1), 0, 0
	lfd f30, 0x80(r1)
	psq_l f29, 0x78(r1), 0, 0
	lfd f29, 0x70(r1)
	psq_l f28, 0x68(r1), 0, 0
	lfd f28, 0x60(r1)
	lmw r22, 0x38(r1)
	lwz r0, 0xa4(r1)
	mtlr r0
	addi r1, r1, 0xa0
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
	bl __tou_rand
	lis r0, 0x4330
	stw r3, 0xc(r1)
	lis r4, double_to_int_mask_tou2_0000aef0@ha
	lis r3, float_32767_tou2_0000aee8@ha
	stw r0, 0x8(r1)
	fsubs f0, f31, f30
	lfd f3, double_to_int_mask_tou2_0000aef0@l(r4)
	lfd f2, 0x8(r1)
	lfs f1, float_32767_tou2_0000aee8@l(r3)
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

asm u32 __tou_rand(void) {
	nofralloc
	lis r4, x@ha
	lis r3, 0x41c6
	addi r5, r4, x@l
	lwz r4, 0x0(r5)
	addi r0, r3, 0x4e6d
	mullw r3, r4, r0
	addi r0, r3, 0x3039
	stw r0, 0x0(r5)
	extrwi r3, r0, 15, 1
	blr
}

asm void __tou_srand(u32 seed) {
	nofralloc
	lis r4, x@ha
	stw r3, x@l(r4)
	blr
}

asm static void pose_change(Kyaku* kyaku, const char* name, const char* anim) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r6, kyaku_wp@ha
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	addi r30, r6, kyaku_wp@l
	mr r31, r3
	mr r26, r4
	mr r27, r5
	li r28, 0x0
	lwz r3, 0x0(r30)
	addi r29, r3, 0x10
	b @1
	@2:
	mr r3, r29
	mr r4, r26
	bl strcmp
	cmpwi r3, 0x0
	bne @3
	mr r4, r27
	addi r3, r29, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @4
	@3:
	addi r28, r28, 0x1
	addi r29, r29, 0x28
	@1:
	lwz r3, 0x0(r30)
	lwz r0, 0xc(r3)
	cmpw r28, r0
	blt @2
	@4:
	lis r3, kyaku_wp@ha
	addi r3, r3, kyaku_wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0xc(r3)
	cmpw r28, r0
	bge @5
	lha r0, 0x10(r31)
	cmpw r0, r28
	beq @5
	sth r28, 0x10(r31)
	bl rand
	lis r4, gp@ha
	srawi r0, r3, 31
	addi r4, r4, gp@l
	lwz r4, 0x0(r4)
	lwz r5, 0x3c(r4)
	lwz r4, 0x38(r4)
	addc r3, r5, r3
	stw r3, 0x1c(r31)
	adde r0, r4, r0
	stw r0, 0x18(r31)
	@5:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm static void pose_main(void) {
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
	lis r4, kyaku_wp@ha
	lis r7, float_60_tou2_0000ae84@ha
	addi r29, r4, kyaku_wp@l
	lis r6, float_1000_tou2_0000ae9c@ha
	lwz r9, 0x0(r29)
	lis r5, float_1_tou2_0000ae44@ha
	lis r4, double_to_int_tou2_0000aee0@ha
	lis r8, gp@ha
	lwz r24, 0x8(r9)
	mr r25, r3
	lfs f28, float_60_tou2_0000ae84@l(r7)
	addi r30, r8, gp@l
	lfs f29, float_1000_tou2_0000ae9c@l(r6)
	li r26, 0x0
	lfs f30, float_1_tou2_0000ae44@l(r5)
	lis r31, 0x8000
	lfd f31, double_to_int_tou2_0000aee0@l(r4)
	lis r23, 0x4330
	b @1
	@2:
	lwz r3, 0xf8(r31)
	li r0, 0x3e8
	lwz r4, 0x0(r30)
	li r5, 0x0
	srwi r3, r3, 2
	lha r7, 0x10(r24)
	divwu r6, r3, r0
	lwz r27, 0x3c(r4)
	lwz r0, 0x1c(r24)
	lwz r28, 0x38(r4)
	subfc r4, r0, r27
	lwz r0, 0x18(r24)
	mulli r7, r7, 0x28
	subfe r3, r0, r28
	addi r22, r7, 0x10
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
	stw r27, 0x1c(r24)
	lis r3, zero_tou2_0000ae40@ha
	lfs f1, zero_tou2_0000ae40@l(r3)
	stw r28, 0x18(r24)
	@3:
	lwz r3, 0x24(r22)
	addi r26, r26, 0x1
	stw r23, 0x8(r1)
	addi r24, r24, 0x20
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

asm static void pose_init(void) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	lis r4, zero_tou2_00009ea8@ha
	lis r3, ext_kyaku_data@ha
	stw r0, 0x64(r1)
	addi r0, r3, ext_kyaku_data@l
	addi r3, r1, 0x28
	addi r4, r4, zero_tou2_00009ea8@l
	stmw r28, 0x50(r1)
	li r29, 0x0
	mr r30, r0
	bl strcpy
	lis r4, zero_tou2_00009ea8@ha
	addi r3, r1, 0x8
	addi r4, r4, zero_tou2_00009ea8@l
	bl strcpy
	lis r3, kyaku_wp@ha
	li r0, -0x1
	addi r31, r3, kyaku_wp@l
	lwz r3, 0x0(r31)
	stw r0, 0xc(r3)
	@1:
	lwz r3, 0x0(r30)
	addi r4, r1, 0x28
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	lwz r4, 0x0(r30)
	addi r3, r1, 0x28
	bl strcpy
	lis r4, zero_tou2_00009ea8@ha
	addi r3, r1, 0x8
	addi r4, r4, zero_tou2_00009ea8@l
	bl strcpy
	@2:
	lwz r3, 0x4(r30)
	addi r4, r1, 0x8
	bl strcmp
	cmpwi r3, 0x0
	beq @3
	lwz r4, 0x4(r30)
	addi r3, r1, 0x8
	bl strcpy
	lis r3, kyaku_wp@ha
	mr r28, r29
	lwz r4, kyaku_wp@l(r3)
	lwz r3, 0xc(r4)
	addi r0, r3, 0x1
	stw r0, 0xc(r4)
	@3:
	lwz r5, 0x0(r31)
	addi r4, r1, 0x28
	lwz r0, 0xc(r5)
	mulli r3, r0, 0x28
	addi r3, r3, 0x10
	add r3, r5, r3
	bl strcpy
	lwz r5, 0x0(r31)
	addi r4, r1, 0x8
	lwz r0, 0xc(r5)
	mulli r3, r0, 0x28
	addi r3, r3, 0x20
	add r3, r5, r3
	bl strcpy
	lwz r6, 0x0(r31)
	subf r3, r28, r29
	addi r5, r3, 0x1
	li r4, 0x1
	lwz r0, 0xc(r6)
	addi r29, r29, 0x1
	mulli r3, r0, 0x28
	addi r0, r3, 0x30
	stwx r28, r6, r0
	lwz r6, 0x0(r31)
	lwz r0, 0xc(r6)
	mulli r3, r0, 0x28
	addi r0, r3, 0x34
	stwx r5, r6, r0
	lwz r5, 0x0(r31)
	lfs f0, 0x8(r30)
	lwz r0, 0xc(r5)
	mulli r3, r0, 0x28
	addi r0, r3, 0x2c
	stfsx f0, r5, r0
	lwz r5, 0x0(r31)
	lwz r0, 0xc(r5)
	mulli r3, r0, 0x28
	addi r0, r3, 0x28
	sthx r4, r5, r0
	lwzu r0, 0xc(r30)
	cmplwi r0, 0x0
	bne @1
	lis r3, kyaku_wp@ha
	lwz r4, kyaku_wp@l(r3)
	lwz r3, 0xc(r4)
	addi r0, r3, 0x1
	stw r0, 0xc(r4)
	lmw r28, 0x50(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm s32 _firstattack_setting(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl fbatGetPointer
	lis r4, 0x1000
	li r0, 0x10
	stw r4, 0x10(r3)
	stw r0, 0x14(r3)
	lwz r0, 0x1c(r3)
	clrrwi r0, r0, 1
	stw r0, 0x1c(r3)
	lis r3, 0x1000
	bl fbatSetAttackAnnounce
	bl fbatSetAttackAnnounceEnable
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
#pragma force_active reset
