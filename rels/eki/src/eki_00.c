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
#ifdef NONMATCHING
#undef EXT_LIT
#define EXT_LIT(sym, val) (val)
extern const char str_00000664[];
#endif
#ifndef NONMATCHING
__declspec(section ".rodata") extern const f32 vec3_eki_00008884[3];
__declspec(section ".rodata") extern const f32 vec3_eki_00008890[3];
__declspec(section ".rodata") extern const f32 vec3_eki_0000889c[3];
__declspec(section ".rodata") extern const f32 vec3_eki_000088a8[3];
__declspec(section ".rodata") extern const f32 vec3_eki_000088b4[3];
__declspec(section ".rodata") extern const f32 vec3_eki_000088c0[3];
__declspec(section ".rodata") extern const f32 vec3_eki_000088cc[3];
__declspec(section ".rodata") extern const f32 vec3_eki_000088d8[3];
__declspec(section ".rodata") extern const f32 vec3_eki_000088e4[3];
__declspec(section ".rodata") extern const f32 vec3_eki_000088f0[3];
__declspec(section ".rodata") extern const f32 vec3_eki_000088fc[3];
__declspec(section ".rodata") extern const f32 vec3_eki_00008908[3];
__declspec(section ".rodata") extern const f32 vec3_eki_00008914[3];
__declspec(section ".rodata") extern const f32 vec3_eki_00008920[3];
__declspec(section ".rodata") extern const f32 vec3_eki_0000892c[3];
__declspec(section ".rodata") extern const u32 zero_eki_00008ba0;
__declspec(section ".rodata") extern const f32 float_neg5000_eki_00008cf8;
__declspec(section ".rodata") extern const f32 float_neg1_eki_00008cfc;
__declspec(section ".rodata") extern const f32 float_0p00761_eki_00008d08;
__declspec(section ".rodata") extern const f32 float_0p16605_eki_00008d0c;
__declspec(section ".rodata") extern const f32 float_3p1416_eki_00008d14;
__declspec(section ".rodata") extern const f32 float_1p5708_eki_00008d18;
__declspec(section ".rodata") extern const f32 float_4p7124_eki_00008d1c;
__declspec(section ".rodata") extern const f32 float_0p03705_eki_00008d20;
__declspec(section ".rodata") extern const f32 float_0p4967_eki_00008d24;
__declspec(section ".rodata") extern const f32 float_0p5_eki_00008d4c;
__declspec(section ".rodata") extern const f32 float_0p03_eki_00008d58;
__declspec(section ".rodata") extern const f32 float_15_eki_00008d60;
__declspec(section ".rodata") extern const f32 float_1p5_eki_00008d64;
__declspec(section ".rodata") extern const f32 float_0p8_eki_00008d68;
__declspec(section ".rodata") extern const f32 float_1p2_eki_00008d6c;
__declspec(section ".rodata") extern const f32 float_5_eki_00008d74;
__declspec(section ".rodata") extern const f32 float_0p3_eki_00008d78;
__declspec(section ".rodata") extern const f32 float_0p2_eki_00008d7c;
__declspec(section ".rodata") extern const f32 float_200_eki_00008d80;
__declspec(section ".rodata") extern const f32 float_300_eki_00008d84;
__declspec(section ".rodata") extern const f32 float_600_eki_00008d88;
__declspec(section ".rodata") extern const f32 float_0p25_eki_00008d8c;
__declspec(section ".rodata") extern const f32 float_neg45_eki_00008d90;
__declspec(section ".rodata") extern const f32 float_0p4_eki_00008d98;
__declspec(section ".rodata") extern const f32 float_2_eki_00008da4;
__declspec(section ".rodata") extern const f32 float_0p9_eki_00008da8;
__declspec(section ".rodata") extern const f32 float_135_eki_00008dac;
__declspec(section ".rodata") extern const f32 float_0p2_eki_00008db0;
__declspec(section ".rodata") extern const f32 float_0p1_eki_00008db4;
__declspec(section ".rodata") extern const f32 float_neg100_eki_00008db8;
__declspec(section ".rodata") extern const f32 float_0p20944_eki_00008dbc;
__declspec(section ".rodata") extern const f64 double_300_eki_00008dc0;
__declspec(section ".rodata") extern const f32 float_3_eki_00008dc8;
__declspec(section ".rodata") extern const f32 float_225_eki_00008dcc;
__declspec(section ".rodata") extern const f32 float_1p1_eki_00008dd0;
__declspec(section ".rodata") extern const f32 float_1p02_eki_00008dd4;
__declspec(section ".rodata") extern const f32 float_neg1000_eki_00008dd8;
__declspec(section ".rodata") extern const f32 float_280_eki_00008ddc;
__declspec(section ".rodata") extern const f32 float_neg120_eki_00008de0;
__declspec(section ".rodata") extern const f32 float_70_eki_00008de4;
__declspec(section ".rodata") extern const f32 float_neg70_eki_00008de8;
__declspec(section ".rodata") extern const f64 double_to_int_eki_00008df8;
__declspec(section ".rodata") extern const f64 double_to_int_mask_eki_00008e00;
#define EXT_LIT(sym, val) (sym)

extern const char eki_00_str_00000664[];
#endif
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
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
extern const char eki_00_str_00000040[];
extern const char eki_00_str_0000004C[];
extern const char eki_00_str_00000050[];
extern const char eki_00_str_00000054[];
extern const char eki_00_str_00000060[];
extern const char eki_00_str_0000006C[];
extern const char eki_00_str_00000070[];
extern const char eki_00_str_0000007C[];
extern const char eki_00_str_00000080[];
extern const char eki_00_str_00000088[];
extern const char eki_00_str_0000008C[];
extern const char eki_00_str_00000094[];
extern const char eki_00_str_00000098[];
extern const char eki_00_str_000000A0[];
extern const char eki_00_str_000000A8[];
extern const char eki_00_str_000000B0[];
extern const char eki_00_str_00000170[];
extern const char eki_00_str_00000178[];
extern const char eki_00_str_00000184[];
extern const char eki_00_str_00000190[];
extern const char eki_00_str_00000198[];
extern const char eki_00_str_000001A0[];
extern const char eki_00_str_000001A8[];
extern const char eki_00_str_000001B0[];
extern const char eki_00_str_000001B8[];
extern const char eki_00_str_000001C4[];
extern const char eki_00_str_000001D0[];
extern const char eki_00_str_000001DC[];
extern const char eki_00_str_000001E8[];
extern const char eki_00_str_000001F4[];
extern const char eki_00_str_000001FC[];
extern const char eki_00_str_00000204[];
extern const char eki_00_str_00000208[];
extern const char eki_00_str_00000214[];
extern const char eki_00_str_0000021C[];
extern const char eki_00_str_00000224[];
extern const char eki_00_str_00000230[];
extern const char eki_00_str_00000238[];
extern const char eki_00_str_00000240[];
extern const char eki_00_str_00000258[];
extern const char eki_00_str_00000274[];
extern const char eki_00_str_00000280[];
extern const char eki_00_str_0000028C[];
extern const char eki_00_str_000002A8[];
extern const char eki_00_str_000002B0[];
extern const char eki_00_str_000002B8[];
extern const char eki_00_str_000002C8[];
extern const char eki_00_str_000002D0[];
extern const char eki_00_str_000002E0[];
extern const char eki_00_str_000002F0[];
extern const char eki_00_str_00000300[];
extern const char eki_00_str_00000310[];
extern const char eki_00_str_00000320[];
extern const char eki_00_str_00000330[];
extern const char eki_00_str_00000348[];
extern const char eki_00_str_00000358[];
extern const char eki_00_str_00000360[];
extern const char eki_00_str_00000370[];
extern const char eki_00_str_00000380[];
extern const char eki_00_str_00000390[];
extern const char eki_00_str_000003A0[];
extern const char eki_00_str_000003B0[];
extern const char eki_00_str_000003C0[];
extern const char eki_00_str_000003D0[];
extern const char eki_00_str_000003DC[];
extern const char eki_00_str_000003E8[];
extern const char eki_00_str_00000404[];
extern const char eki_00_str_00000410[];
extern const char eki_00_str_0000041C[];
extern const char eki_00_str_00000428[];
extern const char eki_00_str_0000042C[];
extern const char eki_00_str_00000430[];
extern const char eki_00_str_00000448[];
extern const char eki_00_str_00000458[];
extern const char eki_00_str_00000474[];
extern const char eki_00_str_00000484[];
extern const char eki_00_str_0000049C[];
extern const char eki_00_str_000004B4[];
extern const char eki_00_str_000004BC[];
extern const char eki_00_str_000004D4[];
extern const char eki_00_str_000004E0[];
extern const char eki_00_str_000004EC[];
extern const char eki_00_str_000004FC[];
extern const char eki_00_str_00000508[];
extern const char eki_00_str_00000514[];
extern const char eki_00_str_00000524[];
extern const char eki_00_str_00000560[];
extern const char eki_00_str_00000578[];
extern const char eki_00_str_0000057C[];
extern const char eki_00_str_00000580[];
extern const char eki_00_str_00000040[];
extern const char eki_00_str_0000004C[];
extern const char eki_00_str_00000050[];
extern const char eki_00_str_00000054[];
extern const char eki_00_str_00000060[];
extern const char eki_00_str_0000006C[];
extern const char eki_00_str_00000070[];
extern const char eki_00_str_0000007C[];
extern const char eki_00_str_00000080[];
extern const char eki_00_str_00000088[];
extern const char eki_00_str_0000008C[];
extern const char eki_00_str_00000094[];
extern const char eki_00_str_00000098[];
extern const char eki_00_str_000000A0[];
extern const char eki_00_str_000000A8[];
extern const char eki_00_str_000000B0[];
extern const char eki_00_str_00000170[];
extern const char eki_00_str_00000178[];
extern const char eki_00_str_00000184[];
extern const char eki_00_str_00000190[];
extern const char eki_00_str_00000198[];
extern const char eki_00_str_000001A0[];
extern const char eki_00_str_000001A8[];
extern const char eki_00_str_000001B0[];
extern const char eki_00_str_000001B8[];
extern const char eki_00_str_000001C4[];
extern const char eki_00_str_000001D0[];
extern const char eki_00_str_000001DC[];
extern const char eki_00_str_000001E8[];
extern const char eki_00_str_000001F4[];
extern const char eki_00_str_000001FC[];
extern const char eki_00_str_00000204[];
extern const char eki_00_str_00000208[];
extern const char eki_00_str_00000214[];
extern const char eki_00_str_0000021C[];
extern const char eki_00_str_00000224[];
extern const char eki_00_str_00000230[];
extern const char eki_00_str_00000238[];
extern const char eki_00_str_00000240[];
extern const char eki_00_str_00000258[];
extern const char eki_00_str_00000274[];
extern const char eki_00_str_00000280[];
extern const char eki_00_str_0000028C[];
extern const char eki_00_str_000002A8[];
extern const char eki_00_str_000002B0[];
extern const char eki_00_str_000002B8[];
extern const char eki_00_str_000002C8[];
extern const char eki_00_str_000002D0[];
extern const char eki_00_str_000002E0[];
extern const char eki_00_str_000002F0[];
extern const char eki_00_str_00000300[];
extern const char eki_00_str_00000310[];
extern const char eki_00_str_00000320[];
extern const char eki_00_str_00000330[];
extern const char eki_00_str_00000348[];
extern const char eki_00_str_00000358[];
extern const char eki_00_str_00000360[];
extern const char eki_00_str_00000370[];
extern const char eki_00_str_00000380[];
extern const char eki_00_str_00000390[];
extern const char eki_00_str_000003A0[];
extern const char eki_00_str_000003B0[];
extern const char eki_00_str_000003C0[];
extern const char eki_00_str_000003D0[];
extern const char eki_00_str_000003DC[];
extern const char eki_00_str_000003E8[];
extern const char eki_00_str_00000404[];
extern const char eki_00_str_00000410[];
extern const char eki_00_str_0000041C[];
extern const char eki_00_str_00000428[];
extern const char eki_00_str_0000042C[];
extern const char eki_00_str_00000430[];
extern const char eki_00_str_00000448[];
extern const char eki_00_str_00000458[];
extern const char eki_00_str_00000474[];
extern const char eki_00_str_00000484[];
extern const char eki_00_str_0000049C[];
extern const char eki_00_str_000004B4[];
extern const char eki_00_str_000004BC[];
extern const char eki_00_str_000004D4[];
extern const char eki_00_str_000004E0[];
extern const char eki_00_str_000004EC[];
extern const char eki_00_str_000004FC[];
extern const char eki_00_str_00000508[];
extern const char eki_00_str_00000514[];
extern const char eki_00_str_00000524[];
#endif
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)
#pragma force_active on
u32 gap_05_00000004_bss[1];
#pragma force_active reset
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
extern const char eki_00_str_00000040[];
extern const char eki_00_str_0000004C[];
extern const char eki_00_str_00000050[];
extern const char eki_00_str_00000054[];
extern const char eki_00_str_00000170[];
extern const char eki_00_str_00000178[];
extern const char eki_00_str_00000184[];
extern const char eki_00_str_00000190[];
extern const char eki_00_str_00000198[];
extern const char eki_00_str_000001A0[];
extern const char eki_00_str_000001A8[];
extern const char eki_00_str_000001B0[];
extern const char eki_00_str_000001B8[];
extern const char eki_00_str_000001C4[];
extern const char eki_00_str_000001D0[];
extern const char eki_00_str_000001DC[];
extern const char eki_00_str_000001E8[];
extern const char eki_00_str_000001F4[];
extern const char eki_00_str_000001FC[];
extern const char eki_00_str_00000204[];
extern const char eki_00_str_00000208[];
extern const char eki_00_str_00000214[];
extern const char eki_00_str_0000021C[];
extern const char eki_00_str_00000224[];
extern const char eki_00_str_00000230[];
extern const char eki_00_str_00000238[];
extern const char eki_00_str_00000240[];
extern const char eki_00_str_00000258[];
extern const char eki_00_str_00000274[];
extern const char eki_00_str_00000280[];
extern const char eki_00_str_0000028C[];
extern const char eki_00_str_000002A8[];
extern const char eki_00_str_000002B0[];
extern const char eki_00_str_000002B8[];
extern const char eki_00_str_000002C8[];
extern const char eki_00_str_000002D0[];
extern const char eki_00_str_000002E0[];
extern const char eki_00_str_000002F0[];
extern const char eki_00_str_00000300[];
extern const char eki_00_str_00000310[];
extern const char eki_00_str_00000320[];
extern const char eki_00_str_00000330[];
extern const char eki_00_str_00000348[];
extern const char eki_00_str_00000358[];
extern const char eki_00_str_00000360[];
extern const char eki_00_str_00000370[];
extern const char eki_00_str_00000380[];
extern const char eki_00_str_00000390[];
extern const char eki_00_str_000003A0[];
extern const char eki_00_str_000003B0[];
extern const char eki_00_str_000003C0[];
extern const char eki_00_str_000003D0[];
extern const char eki_00_str_000003DC[];
extern const char eki_00_str_000003E8[];
extern const char eki_00_str_00000404[];
extern const char eki_00_str_00000410[];
extern const char eki_00_str_0000041C[];
extern const char eki_00_str_00000428[];
extern const char eki_00_str_0000042C[];
extern const char eki_00_str_00000430[];
extern const char eki_00_str_00000448[];
extern const char eki_00_str_00000458[];
extern const char eki_00_str_00000474[];
extern const char eki_00_str_00000484[];
extern const char eki_00_str_0000049C[];
extern const char eki_00_str_000004B4[];
extern const char eki_00_str_000004BC[];
extern const char eki_00_str_000004D4[];
extern const char eki_00_str_000004E0[];
extern const char eki_00_str_000004EC[];
extern const char eki_00_str_000004FC[];
extern const char eki_00_str_00000508[];
extern const char eki_00_str_00000514[];
extern const char eki_00_str_00000524[];
#endif

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
#ifdef NONMATCHING
static inline f32 moa_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
static inline f32 moa_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
static inline f32 moa_sinx(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } return a; }
static inline f32 moa_cosx(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; } return a; }
#endif
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
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
    (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C), 0, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C), 1073741824, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C),
    1082130432, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C), 1086324736, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C), 1090519040, (s32)((char*)eki_00_str_00000040),
    (s32)((char*)eki_00_str_0000004C), 1092616192, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C), 1094713344, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C), 1096810496,
    (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C), 1098907648, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C), 1099956224, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C),
    1101004800, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C), 1102053376, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C), 1103101952, (s32)((char*)eki_00_str_00000040),
    (s32)((char*)eki_00_str_0000004C), 1104150528, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C), 1105199104, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C), 1106247680,
    (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C), 1107296256, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C), 1107820544, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C),
    1108344832, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_0000004C), 1108869120, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_00000050), 0, (s32)((char*)eki_00_str_00000040),
    (s32)((char*)eki_00_str_00000050), 1082130432, (s32)((char*)eki_00_str_00000040), (s32)((char*)eki_00_str_00000050), 1090519040, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C), 0,
    (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C), 1073741824, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C), 1082130432, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C),
    1086324736, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C), 1090519040, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C), 1092616192, (s32)((char*)eki_00_str_00000054),
    (s32)((char*)eki_00_str_0000004C), 1094713344, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C), 1096810496, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C), 1098907648,
    (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C), 1099956224, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C), 1101004800, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C),
    1102053376, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C), 1103101952, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C), 1104150528, (s32)((char*)eki_00_str_00000054),
    (s32)((char*)eki_00_str_0000004C), 1105199104, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C), 1106247680, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C), 1107296256,
    (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C), 1107820544, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C), 1108344832, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_0000004C),
    1108869120, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_00000050), 0, (s32)((char*)eki_00_str_00000054), (s32)((char*)eki_00_str_00000050), 1082130432, (s32)((char*)eki_00_str_00000054),
    (s32)((char*)eki_00_str_00000050), 1090519040, 0, 0, 0,
#endif
};
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
extern const char eki_00_str_00000040[];
extern const char eki_00_str_0000004C[];
extern const char eki_00_str_00000054[];
extern const char eki_00_str_00000060[];
extern const char eki_00_str_0000006C[];
extern const char eki_00_str_00000070[];
extern const char eki_00_str_0000007C[];
extern const char eki_00_str_00000080[];
extern const char eki_00_str_00000088[];
extern const char eki_00_str_0000008C[];
extern const char eki_00_str_00000094[];
extern const char eki_00_str_00000098[];
extern const char eki_00_str_000000A0[];
extern const char eki_00_str_000000A8[];
extern const char eki_00_str_000000B0[];
__declspec(section ".data") static u32 g5_group_tbl_s588[22] = { (u32)(char*)eki_00_str_00000040, (u32)(char*)eki_00_str_0000004C, (u32)(char*)eki_00_str_00000054, (u32)(char*)eki_00_str_0000004C, (u32)(char*)eki_00_str_00000060, (u32)(char*)eki_00_str_0000006C, (u32)(char*)eki_00_str_00000070, (u32)(char*)eki_00_str_0000007C, (u32)(char*)eki_00_str_00000080, (u32)(char*)eki_00_str_00000088, (u32)(char*)eki_00_str_0000008C, (u32)(char*)eki_00_str_00000094, (u32)(char*)eki_00_str_00000098, (u32)(char*)eki_00_str_0000006C, (u32)(char*)eki_00_str_000000A0, (u32)(char*)eki_00_str_0000006C, (u32)(char*)eki_00_str_000000A8, (u32)(char*)eki_00_str_0000006C, (u32)(char*)eki_00_str_000000B0, (u32)(char*)eki_00_str_0000006C, (u32)(char*)eki_00_str_00000040, (u32)(char*)eki_00_str_0000004C };
#endif
__declspec(section ".data") static u32 g5_mt_s758[12] = { 0x41000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x41000000, 0x00000000, 0x3F000000, 0x00000000, 0x00000000, 0x41000000, 0x00000000 };















int rand(void);







double sin(double x);


void envAddTev(s32 type, MapTevCallbackInfo* info);





#ifndef NONMATCHING
static void moamoa_pose_init(void);
void GXClearBoundingBox(void);
void GXReadBoundingBox(u16* left, u16* top, u16* right, u16* bottom);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXIdentity(Mtx m);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
f32 PSVECDistance(const Vec* a, const Vec* b);
f32 PSVECMag(const Vec* v);
void PSVECNormalize(const Vec* src, Vec* dst);
int __cvt_ull_flt();
int __div2u();
void *memset(void *dest, int ch, size_t count);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
static void moamoa_pose_main(void);
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim);
static s32 evt_moamoa_flag_onoff(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_exit(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_ry_reset(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_end_wait(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_fusion(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_kind_onoff(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_blow(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_fusion_debug(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_target_off(EventEntry* event, BOOL isFirstCall);
static f32 randf(f32 min, f32 max);
#pragma opt_propagation off
#pragma opt_lifetimes off
static void ext_moamoa_init(void);
#pragma opt_propagation reset
#pragma opt_lifetimes reset
static void ext_disp(CameraId camera, void* param);
static void ext_shadow_disp(CameraId camera, void* param);
static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
#pragma opt_propagation off
#pragma opt_lifetimes off
static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa);
#pragma opt_propagation reset
#pragma opt_lifetimes reset
#pragma opt_propagation off
#pragma opt_lifetimes off
extern void* eki_00_jumptable_00002400[];
static void ext_moamoa_main(void);
#pragma opt_propagation reset
#pragma opt_lifetimes reset
static void ext_moamoa_dispent(void);


__declspec(section ".data") static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING(((char*)eki_00_str_00000170)), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING(((char*)eki_00_str_00000170)), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(s_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)eki_00_str_00000178)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT((-1.0f)))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)eki_00_str_00000184)), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(s_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)eki_00_str_00000178)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT((-1.0f)))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)eki_00_str_00000184)), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_data[] = {
    (s32)((char*)eki_00_str_00000190), 65539, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)eki_00_str_00000198), (s32)((char*)eki_00_str_000001A0), 327685, (s32)e_door_close, (s32)e_door_open, (s32)((char*)eki_00_str_000001A8),
    65542, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)((char*)eki_00_str_000001B0), (s32)((char*)eki_00_str_000001B8), 327685, (s32)s_door_close, (s32)s_door_open, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(evt_bridge)
    CALL(evt_mario_key_onoff, 0)
    WAIT_MS(500)
    SET_VALUE(GSWF(3576), 1)
    CALL(evt_bero_mapchange, STRING(((char*)eki_00_str_000001B0)), STRING(((char*)eki_00_str_000001B8)))
    RETURN
EVT_END()

EVT_BEGIN(evt_bridge2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)eki_00_str_000001C4)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)eki_00_str_000001D0)), 1, 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_000001DC)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)eki_00_str_000001E8)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)eki_00_str_000001F4)), 2, 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)eki_00_str_000001FC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)eki_00_str_00000204)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_00000208)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_00000214)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_0000021C)), 1)
    CALL(evt_map_playanim, STRING(((char*)eki_00_str_00000224)), 2, 0)
    CALL(evt_mario_set_pos, -210, 60, 0)
    CALL(evt_party_set_pos, 0, -230, 60, 0)
    CALL(evt_item_delete_check, STRING(((char*)eki_00_str_00000230)), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_item_get_position, STRING(((char*)eki_00_str_00000230)), LW(0), LW(1), LW(2))
        SUBTRACT(LW(1), 2000)
        CALL(evt_item_set_position, STRING(((char*)eki_00_str_00000230)), LW(0), LW(1), LW(2))
    END_IF
    CALL(evt_party_cont_onoff, 0, 1)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)eki_00_str_00000238)), 0, 0, -80)
    SET_VALUE(GF(0), 1)
    SET_VALUE(GSW(0), 325)
    SET_VALUE(GSWF(3576), 0)
    RETURN
EVT_END()

static EVT_BEGIN(evt_origami)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_mapobj_get_position, STRING(((char*)eki_00_str_00000238)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000240)), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 0, -800, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT((10.0f)))
        CALL(evt_mapobj_rotate, 1, STRING(((char*)eki_00_str_00000238)), 0, 0, LW(0))
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
    CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000258)), -220, 60, 0, 0)
    CALL(evt_map_playanim, STRING(((char*)eki_00_str_000001F4)), 0, 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)eki_00_str_000001FC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)eki_00_str_00000204)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_00000208)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_00000214)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)eki_00_str_00000274)), 1, 1)
    CALL(evt_map_checkanim, STRING(((char*)eki_00_str_000001F4)), LW(0), LW(1))
    WAIT_MS(1600)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_0000021C)), 1)
    WAIT_MS(1000)
    CALL(evt_mobj_switch_blue, 0, STRING(((char*)eki_00_str_00000280)), -220, 60, 0, PTR(evt_bridge), GSWF(3725))
    CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_0000028C)), -220, 60, 0, 0)
    CALL(evt_mobj_set_scale, STRING(((char*)eki_00_str_00000280)), FLOAT(0.099609375f), FLOAT(0.099609375f), FLOAT(0.099609375f))
    CALL(evt_sub_intpl_msec_init, 8, 100, 1000, 1000)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT((1000.0f)))
    CALL(evt_mobj_set_scale, STRING(((char*)eki_00_str_00000280)), LW(0), LW(0), LW(0))
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
    CALL(evt_npc_entry, STRING(((char*)eki_00_str_000002A8)), STRING(((char*)eki_00_str_00000040)))
    CALL(evt_npc_set_position, STRING(((char*)eki_00_str_000002A8)), 0, -1000, 0)
    CALL(evt_npc_entry, STRING(((char*)eki_00_str_000002B0)), STRING(((char*)eki_00_str_00000054)))
    CALL(evt_npc_set_position, STRING(((char*)eki_00_str_000002B0)), 0, -1000, 0)
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
        CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_000002B8)), 0, STRING(((char*)eki_00_str_000002C8)))
        CASE_EQUAL(2)
        CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_000002D0)), 0, STRING(((char*)eki_00_str_000002C8)))
        CASE_EQUAL(4)
        CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_000002E0)), 0, STRING(((char*)eki_00_str_000002C8)))
        CASE_EQUAL(5)
        CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_000002F0)), 0, STRING(((char*)eki_00_str_000002C8)))
        CASE_EQUAL(6)
        CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_00000300)), 0, STRING(((char*)eki_00_str_000002C8)))
        CASE_EQUAL(3)
        CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_00000310)), 0, STRING(((char*)eki_00_str_000002C8)))
        CASE_EQUAL(7)
        CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_00000320)), 0, STRING(((char*)eki_00_str_000002C8)))
    END_SWITCH
    BEGIN_INLINE_EVENT
        CALL(evt_snd_bgmoff, 1024)
        CALL(evt_snd_bgmon, 1, STRING(((char*)eki_00_str_00000330)))
        WAIT_MS(2000)
        CALL(evt_snd_bgmoff, 513)
        CALL(evt_snd_bgmon, 288, 0)
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 32, 151, 528, 32, 56, -12, 500, 11)
    WAIT_MS(2000)
    CALL(evt_snd_bgmon, 512, STRING(((char*)eki_00_str_00000348)))
    BEGIN_INLINE_EVENT
        CALL(evt_mario_dispflag_onoff, 1, 2)
        WAIT_MS(1000)
        CALL(evt_mario_set_pose, STRING(((char*)eki_00_str_00000358)))
    END_INLINE_EVENT
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_00000360)), 0, STRING(((char*)eki_00_str_000002C8)))
        CASE_EQUAL(2)
        CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_00000370)), 0, STRING(((char*)eki_00_str_000002C8)))
        CASE_EQUAL(4)
        CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_00000380)), 0, STRING(((char*)eki_00_str_000002C8)))
        CASE_EQUAL(5)
        CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_00000390)), 0, STRING(((char*)eki_00_str_000002C8)))
        CASE_EQUAL(6)
        CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_000003A0)), 0, STRING(((char*)eki_00_str_000002C8)))
        CASE_EQUAL(3)
        CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_000003B0)), 0, STRING(((char*)eki_00_str_000002C8)))
        CASE_EQUAL(7)
        CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_000003C0)), 0, STRING(((char*)eki_00_str_000002C8)))
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
    CALL(evt_run_case_evt, 9, 1, STRING(((char*)eki_00_str_000003D0)), 0, PTR(evt_origami), GW(10))
    SET_VALUE(GSW(0), 323)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

s32 img_set_color(EventEntry* event, BOOL isFirstCall);

s32 img_set_color(EventEntry* event, BOOL isFirstCall);

EVT_BEGIN(evt_elv_rumble)
    IF_INT_EQUAL(GF(0), 0)
        CALL(evt_map_checkanim, STRING(((char*)eki_00_str_00000224)), LW(0), LW(1))
        ELSE
        CALL(evt_map_checkanim, STRING(((char*)eki_00_str_000003DC)), LW(0), LW(1))
    END_IF
    SUBTRACT(LW(1), 500)
    CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
    CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_000003E8)), LW(3), LW(4), LW(5), 0)
    CALL(evt_cam_shake, 4, FLOAT((0.0f)), FLOAT(0.0048828125f), 250)
    WAIT_MS(LW(1))
    CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
    CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_000003E8)), LW(3), LW(4), LW(5), 0)
    CALL(evt_cam_shake, 4, FLOAT((0.0f)), FLOAT(0.0048828125f), 250)
    RETURN
EVT_END()

static EVT_BEGIN(evt_elv_init)
    CALL(evt_paper_entry, STRING(((char*)eki_00_str_00000404)))
    CALL(evt_img_entry, STRING(((char*)eki_00_str_00000410)))
    CALL(evt_img_set_paper, STRING(((char*)eki_00_str_00000410)), STRING(((char*)eki_00_str_00000404)))
    CALL(evt_offscreen_entry, STRING(((char*)eki_00_str_0000041C)))
    CALL(evt_img_set_paper_anim, STRING(((char*)eki_00_str_00000410)), STRING(((char*)eki_00_str_00000428)))
    CALL(evt_img_alloc_capture, STRING(((char*)eki_00_str_00000410)), 0, STRING(((char*)eki_00_str_0000041C)), 0, 0, 0, 608, 480)
    CALL(evt_img_alloc_capture, STRING(((char*)eki_00_str_00000410)), 2, STRING(((char*)eki_00_str_0000041C)), 0, 0, 0, 608, 480)
    CALL(evt_img_clear_virtual_point, STRING(((char*)eki_00_str_00000410)))
    CALL(evt_img_onoff, STRING(((char*)eki_00_str_00000410)), 0)
    SET_VALUE(GF(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_elv_down)
    BEGIN_INLINE_EVENT
        CALL(evt_mapobj_get_position, STRING(((char*)eki_00_str_0000042C)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000430)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000430)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)eki_00_str_00000448)), 0, 0)
    WAIT_FRAMES(20)
    CALL(evt_mario_mov_pos2, 190, -65, FLOAT((60.0f)))
    CALL(evt_map_checkanim, STRING(((char*)eki_00_str_00000448)), LW(0), LW(1))
    ADD(LW(1), 1)
    WAIT_MS(LW(1))
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, 190, -65, FLOAT((60.0f)))
        CALL(evt_party_stop, 0)
        CALL(evt_party_jump_pos, 0, 160, 0, -160, 500, 0, -1000)
        CALL(evt_party_stop, 0)
        CALL(evt_party_set_dir, 0, 90, 200)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, 190, -160, FLOAT((60.0f)))
    CALL(evt_mario_set_dir, 270, 200, 0)
    CALL(evt_mapobj_set_offscreen, 1, STRING(((char*)eki_00_str_000001DC)), STRING(((char*)eki_00_str_0000041C)))
    CALL(evt_mapobj_clear_offscreen, 1, STRING(((char*)eki_00_str_000001C4)))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_000001DC)), 1)
    CALL(evt_img_onoff, STRING(((char*)eki_00_str_00000410)), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_mapobj_get_position, STRING(((char*)eki_00_str_0000042C)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000458)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000458)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)eki_00_str_00000474)), 0, 0)
    CALL(evt_map_checkanim, STRING(((char*)eki_00_str_00000474)), LW(0), LW(2))
    CALL(evt_sub_intpl_msec_init, 11, 255, 0, LW(2))
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(img_set_color, STRING(((char*)eki_00_str_00000410)), 255, 255, 255, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_img_onoff, STRING(((char*)eki_00_str_00000410)), 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000484)), LW(0), LW(1), LW(2), LW(10))
        CALL(evt_map_checkanim, STRING(((char*)eki_00_str_00000224)), LW(0), LW(1))
        WAIT_MS(LW(1))
        CALL(evt_snd_sfxoff, LW(10))
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)eki_00_str_00000224)), 0, 0)
    SPAWN_EVENT(PTR(evt_elv_rumble))
    CALL(evt_map_checkanim, STRING(((char*)eki_00_str_00000224)), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_mapobj_get_position, STRING(((char*)eki_00_str_0000042C)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_0000049C)), LW(0), LW(1), LW(2), 0)
    WAIT_MS(400)
    CALL(evt_mapobj_clear_offscreen, 1, STRING(((char*)eki_00_str_000001DC)))
    CALL(evt_mapobj_set_offscreen, 1, STRING(((char*)eki_00_str_000001C4)), STRING(((char*)eki_00_str_0000041C)))
    CALL(evt_img_onoff, STRING(((char*)eki_00_str_00000410)), 1)
    IF_INT_LESS(GSW(0), 323)
        CALL(evt_moamoa_flag_onoff, 0, 1)
        CALL(evt_moamoa_flag_onoff, 1, 2)
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_mapobj_get_position, STRING(((char*)eki_00_str_0000042C)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000430)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000430)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)eki_00_str_00000448)), 0, 0)
    CALL(evt_map_checkanim, STRING(((char*)eki_00_str_00000448)), LW(0), LW(2))
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, LW(2))
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(img_set_color, STRING(((char*)eki_00_str_00000410)), 255, 255, 255, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_img_onoff, STRING(((char*)eki_00_str_00000410)), 0)
    IF_INT_LESS(GSW(0), 323)
        CALL(evt_moamoa_flag_onoff, 1, 1)
        CALL(evt_moamoa_flag_onoff, 0, 2)
    END_IF
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)eki_00_str_000001C4)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)eki_00_str_000001D0)), 1, 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_000001DC)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)eki_00_str_000001E8)), 1, 0)
    SWITCH(GSW(0))
        CASE_LESS(323)
        CASE_EQUAL(323)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)eki_00_str_000003D0)), 0, PTR(evt_origami), GW(10))
        CASE_DEFAULT
        CALL(evt_mapobj_rotate, 1, STRING(((char*)eki_00_str_00000238)), 0, 0, -80)
    END_SWITCH
    IF_INT_EQUAL(GSW(0), 324)
        CALL(evt_mobj_switch_blue, 0, STRING(((char*)eki_00_str_00000280)), -220, 60, 0, PTR(evt_bridge), GSWF(3725))
    END_IF
    CALL(evt_item_delete_check, STRING(((char*)eki_00_str_00000230)), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_item_get_position, STRING(((char*)eki_00_str_00000230)), LW(0), LW(1), LW(2))
        SUBTRACT(LW(1), 2000)
        CALL(evt_item_set_position, STRING(((char*)eki_00_str_00000230)), LW(0), LW(1), LW(2))
    END_IF
    IF_INT_LESS(GSW(0), 324)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_000001FC)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_00000204)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)eki_00_str_00000208)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)eki_00_str_00000214)), 1)
        CALL(evt_hitobj_onoff, STRING(((char*)eki_00_str_00000274)), 1, 0)
        ELSE
        CALL(evt_map_playanim, STRING(((char*)eki_00_str_000001F4)), 2, 0)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)eki_00_str_000001FC)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)eki_00_str_00000204)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_00000208)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_00000214)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_0000021C)), 1)
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_party_stop, 0)
        WAIT_MS(100)
        CALL(evt_party_move_pos2, 0, 190, -65, FLOAT((60.0f)))
        CALL(evt_party_stop, 0)
        WAIT_MS(100)
        CALL(evt_party_move_pos2, 0, 150, -65, FLOAT((60.0f)))
        CALL(evt_party_stop, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    CALL(evt_mario_mov_pos2, 190, -65, FLOAT((60.0f)))
    BEGIN_INLINE_EVENT
        CALL(evt_mapobj_get_position, STRING(((char*)eki_00_str_0000042C)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000458)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000458)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)eki_00_str_00000474)), 0, 0)
    WAIT_MS(500)
    IF_INT_LESS(GSW(0), 322)
        CALL_CHILD(PTR(evt_meet_moamoa))
    END_IF
    IF_INT_EQUAL(GSW(0), 322)
        CALL(evt_snd_bgmon, 512, STRING(((char*)eki_00_str_00000348)))
    END_IF
    CALL(evt_map_checkanim, STRING(((char*)eki_00_str_00000474)), LW(0), LW(1))
    WAIT_MS(LW(1))
    RETURN
EVT_END()

EVT_BEGIN(evt_elv_up)
    CALL(evt_snd_bgmoff, 512)
    BEGIN_INLINE_EVENT
        CALL(evt_mapobj_get_position, STRING(((char*)eki_00_str_0000042C)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000430)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000430)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)eki_00_str_00000448)), 0, 0)
    WAIT_FRAMES(20)
    CALL(evt_mario_mov_pos2, 190, -65, FLOAT((60.0f)))
    CALL(evt_map_checkanim, STRING(((char*)eki_00_str_00000448)), LW(0), LW(1))
    ADD(LW(1), 1)
    WAIT_MS(LW(1))
    BEGIN_INLINE_EVENT
        CALL(evt_hitobj_onoff, STRING(((char*)eki_00_str_000004B4)), 0, 0)
        CALL(evt_party_move_pos, 0, 190, -65, 500)
        CALL(evt_party_stop, 0)
        CALL(evt_party_move_pos, 0, 160, -160, 500)
        CALL(evt_party_stop, 0)
        CALL(evt_party_set_dir, 0, 90, 0)
        CALL(evt_hitobj_onoff, STRING(((char*)eki_00_str_000004B4)), 0, 1)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos, 190, -160, 500)
    CALL(evt_mario_set_dir, 270, 0, 0)
    WAIT_MS(500)
    CALL(evt_mapobj_clear_offscreen, 1, STRING(((char*)eki_00_str_000001DC)))
    CALL(evt_mapobj_set_offscreen, 1, STRING(((char*)eki_00_str_000001C4)), STRING(((char*)eki_00_str_0000041C)))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_000001C4)), 1)
    CALL(evt_img_onoff, STRING(((char*)eki_00_str_00000410)), 1)
    IF_INT_LESS(GSW(0), 323)
        CALL(evt_moamoa_flag_onoff, 0, 1)
        CALL(evt_moamoa_flag_onoff, 1, 2)
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_mapobj_get_position, STRING(((char*)eki_00_str_0000042C)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000458)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000458)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)eki_00_str_00000474)), 0, 0)
    CALL(evt_map_checkanim, STRING(((char*)eki_00_str_00000474)), LW(0), LW(2))
    CALL(evt_sub_intpl_msec_init, 11, 255, 0, LW(2))
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(img_set_color, STRING(((char*)eki_00_str_00000410)), 255, 255, 255, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_img_onoff, STRING(((char*)eki_00_str_00000410)), 0)
    IF_INT_LESS(GSW(0), 323)
        CALL(evt_moamoa_flag_onoff, 0, 2)
    END_IF
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000484)), LW(0), LW(1), LW(2), LW(10))
        CALL(evt_map_checkanim, STRING(((char*)eki_00_str_000003DC)), LW(0), LW(1))
        WAIT_MS(LW(1))
        CALL(evt_snd_sfxoff, LW(10))
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)eki_00_str_000003DC)), 0, 0)
    SPAWN_EVENT(PTR(evt_elv_rumble))
    CALL(evt_map_checkanim, STRING(((char*)eki_00_str_000003DC)), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_mapobj_get_position, STRING(((char*)eki_00_str_0000042C)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_0000049C)), LW(0), LW(1), LW(2), 0)
    WAIT_MS(400)
    CALL(evt_mapobj_set_offscreen, 1, STRING(((char*)eki_00_str_000001DC)), STRING(((char*)eki_00_str_0000041C)))
    CALL(evt_mapobj_clear_offscreen, 1, STRING(((char*)eki_00_str_000001C4)))
    CALL(evt_img_onoff, STRING(((char*)eki_00_str_00000410)), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_mapobj_get_position, STRING(((char*)eki_00_str_0000042C)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000430)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000430)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)eki_00_str_00000448)), 0, 0)
    CALL(evt_map_checkanim, STRING(((char*)eki_00_str_00000448)), LW(0), LW(2))
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, LW(2))
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(img_set_color, STRING(((char*)eki_00_str_00000410)), 255, 255, 255, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_img_onoff, STRING(((char*)eki_00_str_00000410)), 0)
    IF_INT_LESS(GSW(0), 324)
    END_IF
    IF_INT_EQUAL(GSW(0), 324)
        CALL(evt_mobj_delete, STRING(((char*)eki_00_str_00000280)))
    END_IF
    CALL(evt_item_delete_check, STRING(((char*)eki_00_str_00000230)), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_item_get_position, STRING(((char*)eki_00_str_00000230)), LW(0), LW(1), LW(2))
        ADD(LW(1), 2000)
        CALL(evt_item_set_position, STRING(((char*)eki_00_str_00000230)), LW(0), LW(1), LW(2))
    END_IF
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_000001C4)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)eki_00_str_000001D0)), 1, 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)eki_00_str_000001DC)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)eki_00_str_000001E8)), 1, 1)
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
        CALL(evt_mapobj_get_position, STRING(((char*)eki_00_str_0000042C)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000458)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)eki_00_str_00000458)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)eki_00_str_00000474)), 0, 0)
    CALL(evt_map_checkanim, STRING(((char*)eki_00_str_00000474)), LW(0), LW(1))
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
        CALL(evt_snd_sfxon, STRING(((char*)eki_00_str_000004BC)), 0)
        CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_000004D4)), 0, 0)
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
    CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_000004E0)), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_head)
    CALL(evt_item_delete, STRING(((char*)eki_00_str_00000230)))
    CALL(evt_item_entry, STRING(((char*)eki_00_str_00000230)), 300, -260, 160, -60, 4, GSWF(3745), 0)
    CALL(evt_item_set_move_dir_speed, STRING(((char*)eki_00_str_00000230)), FLOAT((135.0f)), FLOAT((90.0f)))
    CALL(evt_item_set_gravity, STRING(((char*)eki_00_str_00000230)), FLOAT((1.0f)))
    CALL(evt_item_set_bound_rate, STRING(((char*)eki_00_str_00000230)), FLOAT(0.5996094f))
    CALL(evt_item_set_jump_power, STRING(((char*)eki_00_str_00000230)), FLOAT(500.0f))
    CALL(evt_item_status_on, STRING(((char*)eki_00_str_00000230)), 16)
    CALL(evt_item_flag_on, STRING(((char*)eki_00_str_00000230)), 2048)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

static EVT_BEGIN(evt_kanban)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING(((char*)eki_00_str_000004EC)), 0, 0)
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
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)eki_00_str_000001C4)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)eki_00_str_000001D0)), 1, 0)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 320)
        CALL_CHILD(PTR(evt_elv_init))
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)eki_00_str_000004FC)), 0, PTR(evt_elv), 0)
        ELSE
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)eki_00_str_000004FC)), 0, PTR(evt_elv_nomsg), 0)
    END_IF
    IF_INT_LESS(GSW(0), 323)
        CALL_CHILD(PTR(evt_moamoa_init))
    END_IF
    CALL(evt_item_entry, STRING(((char*)eki_00_str_00000230)), 300, -260, 130, -60, 17, GSWF(3745), 0)
    IF_INT_EQUAL(GSWF(3745), 0)
        CALL(evt_run_case_evt, 16, 1, STRING(((char*)eki_00_str_00000508)), 0, PTR(evt_head), 0)
    END_IF
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING(((char*)eki_00_str_00000514)))
    IF_INT_EQUAL(GSWF(3576), 1)
        SPAWN_EVENT(PTR(evt_bridge2))
    END_IF
    CALL(evt_run_case_evt, 9, 1, STRING(((char*)eki_00_str_00000524)), 0, PTR(evt_kanban), 0)
    RETURN
EVT_END()


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
#pragma force_active reset

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
		lis r4, double_to_int_eki_00008df8@ha
		lis r3, float_32767_eki_00008d50@ha
		lfd f3, double_to_int_eki_00008df8@l(r4)
		opword 0x90010008
		opword 0xEC1FF028
		lfs f1, float_32767_eki_00008d50@l(r3)
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

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
static void ext_moamoa_init(void) {
	char _af_pad[52];
	asm volatile {
		opword 0x38600870
		bl _mapAlloc
		lis r5, wp@ha
		opword 0x38800000
		addi r6, r5, wp@l
		opword 0x38A00870
		opword 0x90660000
		bl memset
		lis r5, wp@ha
		lis r3, vec3_eki_00008884@ha
		addi r7, r3, vec3_eki_00008884@l
		lis r4, vec3_eki_00008890@ha
		addi r9, r5, wp@l
		opword 0x80C70000
		opword 0x81090000
		lis r3, vec3_eki_0000889c@ha
		opword 0x80070004
		addi r5, r4, vec3_eki_00008890@l
		addi r4, r3, vec3_eki_0000889c@l
		opword 0x90C80014
		opword 0x90080018
		opword 0x80070008
		opword 0x9008001C
		opword 0x80C90000
		opword 0x80650000
		opword 0x80050004
		opword 0x90660020
		opword 0x90060024
		opword 0x80050008
		opword 0x90060028
		opword 0x80A90000
		opword 0x80640000
		opword 0x80040004
		opword 0x9065002C
		opword 0x90050030
		opword 0x80040008
		opword 0x90050034
		bl extGetPoseNum
		lis r4, wp@ha
		addi r5, r4, wp@l
		opword 0x80850000
		opword 0x90640004
		opword 0x80650000
		opword 0x80030004
		opword 0x1C600050
		bl _mapAlloc
		lis r5, wp@ha
		opword 0x38800000
		addi r6, r5, wp@l
		opword 0x80A60000
		opword 0x90650008
		opword 0x80660000
		opword 0x80030004
		opword 0x80630008
		opword 0x1CA00050
		bl memset
		bl moamoa_pose_init
		bl extGetPosePtr
		lis r4, wp@ha
		lis r18, double_to_int_eki_00008df8@ha
		addi r21, r4, wp@l
		lis r17, float_32767_eki_00008d50@ha
		opword 0x80950000
		lis r11, zero_eki_00008cf4@ha
		addi r20, r18, double_to_int_eki_00008df8@l
		lis r12, float_6p2832_eki_00008d00@ha
		addi r18, r12, float_6p2832_eki_00008d00@l
		addi r19, r17, float_32767_eki_00008d50@l
		lis r10, float_100_eki_00008d70@ha
		addi r25, r11, zero_eki_00008cf4@l
		lis r9, float_0p16605_eki_00008d0c@ha
		lis r22, eki_00_str_0000004C@ha
		addi r17, r10, float_100_eki_00008d70@l
		lis r8, float_1_eki_00008d10@ha
		addi r10, r8, float_1_eki_00008d10@l
		addi r11, r9, float_0p16605_eki_00008d0c@l
		lis r7, float_3p1416_eki_00008d14@ha
		lis r23, eki_00_str_00000040@ha
		addi r9, r7, float_3p1416_eki_00008d14@l
		lis r6, float_0p4967_eki_00008d24@ha
		addi r7, r6, float_0p4967_eki_00008d24@l
		lis r5, float_1E06_eki_00008e1c@ha
		addi r6, r5, float_1E06_eki_00008e1c@l
		lis r12, float_0p00761_eki_00008d08@ha
		lis r8, float_0p03705_eki_00008d20@ha
		lis r5, float_neg1_eki_00008cfc@ha
		opword 0x83A40008
		opword 0x7C7E1B78
		opword 0xCB540000
		addi r22, r22, eki_00_str_0000004C@l
		opword 0xC3730000
		addi r23, r23, eki_00_str_00000040@l
		opword 0xC3920000
		addi r26, r12, float_0p00761_eki_00008d08@l
		opword 0xC3B90000
		addi r27, r8, float_0p03705_eki_00008d20@l
		opword 0xC3D10000
		addi r28, r5, float_neg1_eki_00008cfc@l
		opword 0xC30B0000
		opword 0x3BE00000
		opword 0xC32A0000
		opword 0x3F004330
		opword 0xC3E90000
		opword 0xC2E70000
		lfs f20, 0x0(r6)
		opword 0x48000378
		opword 0x38000000
		opword 0x7ED1B378
		opword 0xB01D0000
		opword 0x7EF2BB78
		opword 0xB01D0002
		opword 0xB01D0004
		opword 0xA01D0000
		opword 0x80750000
		opword 0x54000529
		opword 0x3A630050
		opword 0x41820038
		opword 0x889D004C
		lis r3, g5_group_tbl_s588@ha
		addi r0, r3, g5_group_tbl_s588@l
		opword 0x54831D78
		opword 0x28040002
		opword 0x7C601A14
		opword 0x82430000
		opword 0x41800008
		opword 0x82230004
		opword 0x2804000A
		opword 0x4082000C
		lis r3, eki_00_str_00000578@ha
		addi r17, r3, eki_00_str_00000578@l
		opword 0x3A800000
		opword 0x48000034
		opword 0x7E639B78
		opword 0x7E449378
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x7E248B78
		opword 0x38730010
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3A940001
		opword 0x3A730028
		opword 0x80750000
		opword 0x8003004C
		opword 0x7C140000
		opword 0x4180FFC4
		opword 0x80750000
		opword 0x8003004C
		opword 0x7C140000
		opword 0x40800080
		opword 0xA81D003C
		opword 0x7C00A000
		opword 0x41820074
		opword 0xA01D0000
		opword 0x5400077B
		opword 0x41820020
		lis r4, eki_00_str_0000057C@ha
		opword 0x7E238B78
		addi r4, r4, eki_00_str_0000057C@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x4082004C
		opword 0xA01D0000
		opword 0x540006F7
		opword 0x41820020
		lis r4, eki_00_str_00000580@ha
		opword 0x7E238B78
		addi r4, r4, eki_00_str_00000580@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x40820024
		lis r3, gp@ha
		opword 0xB29D003C
		addi r3, r3, gp@l
		opword 0x80630000
		opword 0x80030038
		opword 0x8063003C
		opword 0x907D0044
		opword 0x901D0040
		bl rand
		opword 0x6C608000
		stw r24, _af_pad+32(r1)
		opword 0x9001002C
		opword 0xC8010028
		opword 0xEC00D028
		opword 0xEC00D824
		opword 0xEEC0EF3A
		bl rand
		opword 0x6C638000
		opword 0x801E0000
		opword 0x90610034
		opword 0x60000013
		opword 0x93010030
		opword 0xC8010030
		opword 0x901E0000
		opword 0xEC00D028
		opword 0x807E000C
		opword 0xEC00D824
		opword 0xEEA0EFBA
		bl PSMTXIdentity
		opword 0xFC16F840
		opword 0xC05A0000
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xFC160840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC1605B2
		opword 0xEC42C038
		opword 0xEC42C83A
		opword 0xEC4205B2
		opword 0x48000078
		opword 0xEC160828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC42C038
		opword 0xEC42C83A
		opword 0xEC420072
		opword 0x4800005C
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC160040
		opword 0x40800028
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f0, float_3p1416_eki_00008d14@l(r3)
		opword 0xEC360028
		opword 0xEC010072
		opword 0xEC42C038
		opword 0xEC42C83A
		opword 0xEC420072
		opword 0xFC401050
		opword 0x48000028
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC160028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC42C038
		opword 0xEC42C83A
		opword 0xEC420072
		opword 0xFC401050
		opword 0x80950000
		opword 0xFC16F840
		opword 0x807E000C
		opword 0xC0040014
		opword 0xC07B0000
		opword 0xEC1500BA
		opword 0xD003000C
		opword 0x807E000C
		opword 0xD3A3001C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xFC160840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC1605B2
		opword 0xEC63B838
		opword 0xEC63C83A
		opword 0x4800006C
		opword 0xEC160828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC63B838
		opword 0xEC63C83A
		opword 0xFC601850
		opword 0x48000050
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC160040
		opword 0x40800024
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f0, float_3p1416_eki_00008d14@l(r3)
		opword 0xEC160028
		opword 0xEC000032
		opword 0xEC63B838
		opword 0xEC63C83A
		opword 0xFC601850
		opword 0x48000020
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC160028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC63B838
		opword 0xEC63C83A
		opword 0x80750000
		opword 0x38810020
		opword 0xC0990000
		opword 0x38A1001C
		opword 0xC003001C
		opword 0x38C10018
		opword 0x807E000C
		opword 0xFCC02090
		opword 0xEC1500FC
		opword 0xC0BC0000
		opword 0x38E10014
		opword 0x39010010
		opword 0x3921000C
		opword 0xD003000C
		opword 0x39410008
		opword 0x38600000
		opword 0xD3A10018
		opword 0xD3A1001C
		opword 0xD3A10020
		opword 0xD2810014
		opword 0x817E000C
		opword 0xC00B001C
		opword 0xC02B000C
		opword 0xEC5E002A
		opword 0xC06B002C
		bl hitCheckFilter
		opword 0x28030000
		opword 0x41820010
		opword 0xC001001C
		opword 0x807E000C
		opword 0xD003001C
		opword 0x3BFF0001
		opword 0x3BDE0020
		opword 0x3BBD0050
		opword 0x80750000
		opword 0x80030004
		opword 0x7C1F0000
		opword 0x4180FC80
		opword 0x3A200000
		bl ext_moamoa_main
		opword 0x3A310001
		opword 0x2C110258
		opword 0x4180FFF4
	}
}
#pragma pop

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
        offscreenAddBoundingBox(offscreenNameToId((char*)eki_00_str_0000041C), left, top, right, bottom);
    }
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
static void ext_shadow_disp(CameraId camera, void* param) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x93E1001C
		opword 0x7C7F1B78
		opword 0x2C1F0001
		opword 0x40820008
		bl GXClearBoundingBox
		lis r3, g5_mt_s758@ha
		addi r3, r3, g5_mt_s758@l
		bl extLoadShadowMtx
		bl extLoadShadowRenderMode
		bl extLoadShadowVertex
		bl extLoadShadowTev
		bl extDrawShadow
		opword 0x2C1F0001
		opword 0x4082003C
		bl sysWaitDrawSync
		opword 0x3861000E
		opword 0x3881000C
		opword 0x38A1000A
		opword 0x38C10008
		bl GXReadBoundingBox
		lis r3, eki_00_str_0000041C@ha
		addi r3, r3, eki_00_str_0000041C@l
		bl offscreenNameToId
		opword 0xA081000E
		opword 0xA0A1000C
		opword 0xA0C1000A
		opword 0xA0E10008
		bl offscreenAddBoundingBox
		opword 0x80010024
		opword 0x83E1001C
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop

#pragma dont_inline on
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity) {
	asm volatile {
		opword 0x9421FF50
		opword 0x7C0802A6
		opword 0x900100B4
		opword 0xDBE100A0
		opword 0xF3E100A8
		opword 0xDBC10090
		opword 0xF3C10098
		opword 0xDBA10080
		opword 0xF3A10088
		opword 0xDB810070
		opword 0xF3810078
		opword 0xDB610060
		opword 0xF3610068
		opword 0xBFA10054
		opword 0xFF600890
		opword 0x2C060000
		opword 0xFF801090
		opword 0x7C7D1B78
		opword 0xFFA01890
		opword 0x7C9E2378
		opword 0xFFE02090
		opword 0x7CBF2B78
		opword 0xFFC02890
		opword 0x4182009C
		lis r4, zero_eki_00008cf4@ha
		lis r3, float_100_eki_00008d70@ha
		addi r5, r4, zero_eki_00008cf4@l
		lfs f0, float_100_eki_00008d70@l(r3)
		opword 0xC0850000
		lis r4, float_1E06_eki_00008e1c@ha
		lfs f7, float_1E06_eki_00008e1c@l(r4)
		lis r3, float_neg1_eki_00008cfc@ha
		opword 0xFCC02090
		lfs f5, float_neg1_eki_00008cfc@l(r3)
		opword 0xEC40E02A
		opword 0xD0810018
		opword 0x38810020
		opword 0x38A1001C
		opword 0xD081001C
		opword 0x38C10018
		opword 0x38E10014
		opword 0x39010010
		opword 0xD0810020
		opword 0x3921000C
		opword 0x39410008
		opword 0x38600000
		opword 0xD0E10014
		bl hitCheckFilter
		opword 0x28030000
		opword 0x41820034
		opword 0xC001001C
		lis r3, double_30_eki_00008e20@ha
		opword 0xEC3C0028
		lfd f0, double_30_eki_00008e20@l(r3)
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x40810014
		lis r3, float_0p1_eki_00008d54@ha
		lfs f0, float_0p1_eki_00008d54@l(r3)
		opword 0xEFFF0028
		opword 0xEFDE002A
		opword 0xC381001C
		lis r3, vec3_eki_000088a8@ha
		addi r4, r3, vec3_eki_000088a8@l
		opword 0x80040000
		opword 0x80640004
		opword 0x90010024
		opword 0x80040008
		opword 0x90610028
		opword 0xD3610024
		opword 0x9001002C
		opword 0x80010024
		opword 0xD3810028
		opword 0xD3A1002C
		opword 0x80610028
		opword 0x901E0008
		opword 0x8001002C
		opword 0x907E000C
		opword 0x901E0010
		opword 0xD3FE001C
		opword 0xD3DE0020
		opword 0x807D000C
		opword 0xC05E000C
		opword 0xC003001C
		opword 0xC023000C
		opword 0xEFC20028
		opword 0xC043002C
		opword 0xC07E0008
		opword 0xC09E0010
		bl distABf
		opword 0x807D000C
		opword 0xFFE00890
		opword 0xC07E0008
		opword 0xC023000C
		opword 0xC043002C
		opword 0xC09E0010
		bl angleABf
		opword 0xC01E001C
		opword 0x3CA04330
		lis r4, double_to_int_eki_00008df8@ha
		lis r3, float_0p5_eki_00008d4c@ha
		opword 0xEC1F0024
		addi r6, r4, double_to_int_eki_00008df8@l
		addi r4, r3, float_0p5_eki_00008d4c@l
		lis r3, float_180_eki_00008d9c@ha
		opword 0x90A10040
		opword 0x38000003
		opword 0xFC40001E
		lfs f0, float_180_eki_00008d9c@l(r3)
		opword 0xC8860000
		opword 0xEC00082A
		opword 0x90A10038
		opword 0xD8410030
		opword 0xC0440000
		opword 0x80610034
		opword 0xB07E0018
		opword 0xA87E0018
		opword 0xC0BE0020
		opword 0x6C638000
		opword 0x90610044
		opword 0xC8210040
		opword 0x9061003C
		opword 0xEC212028
		opword 0xC8610038
		opword 0xEC3E0824
		opword 0xEC632028
		opword 0xEC6500F2
		opword 0xEC2308BA
		opword 0xD03E0014
		opword 0xB01E0002
		opword 0xB3FE0024
		opword 0xD01D0004
		opword 0xA01E0000
		opword 0x60000002
		opword 0xB01E0000
		opword 0x801D0000
		opword 0x60000010
		opword 0x901D0000
		opword 0x801D0000
		opword 0x540007B8
		opword 0x901D0000
		opword 0xE3E100A8
		opword 0xCBE100A0
		opword 0xE3C10098
		opword 0xCBC10090
		opword 0xE3A10088
		opword 0xCBA10080
		opword 0xE3810078
		opword 0xCB810070
		opword 0xE3610068
		opword 0xCB610060
		opword 0xBBA10054
		opword 0x800100B4
		opword 0x7C0803A6
		opword 0x382100B0
	}
}
#pragma pop
#pragma dont_inline reset

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa) {
	asm volatile {
		opword 0x9421FF10
		opword 0x7C0802A6
		opword 0x900100F4
		opword 0xDBE100E0
		opword 0xF3E100E8
		opword 0xDBC100D0
		opword 0xF3C100D8
		opword 0xDBA100C0
		opword 0xF3A100C8
		opword 0xBFA100B4
		opword 0x7C7D1B78
		opword 0x7C9E2378
		bl marioGetPtr
		opword 0x80BD000C
		lis r4, float_20_eki_00008e08@ha
		lfs f0, float_20_eki_00008e08@l(r4)
		opword 0x7C7F1B78
		opword 0xC045001C
		opword 0xC0230090
		opword 0xEC00102A
		opword 0xFC010040
		opword 0x4081000C
		opword 0x38600000
		opword 0x48000AA0
		opword 0xC01F01B8
		opword 0xEC01002A
		opword 0xFC020040
		opword 0x4081000C
		opword 0x38600000
		opword 0x48000A88
		opword 0xC025000C
		opword 0xC045002C
		opword 0xC07F008C
		opword 0xC09F0094
		bl distABf
		lis r4, float_20_eki_00008e08@ha
		lis r3, float_0p5_eki_00008d4c@ha
		opword 0xC05F01B4
		lfs f3, float_20_eki_00008e08@l(r4)
		lfs f0, float_0p5_eki_00008d4c@l(r3)
		opword 0xEC43102A
		opword 0xEC020032
		opword 0xFC010040
		opword 0x40800088
		opword 0x807D000C
		lis r4, float_10_eki_00008e0c@ha
		lfs f1, float_10_eki_00008e0c@l(r4)
		opword 0xC003001C
		opword 0xC05F0090
		opword 0xEC01002A
		opword 0xFC020040
		opword 0x40810068
		opword 0x807F0000
		opword 0x5460039D
		opword 0x4182005C
		opword 0x546003DF
		opword 0x40820054
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0x80030558
		opword 0x2C000002
		opword 0x4080003C
		opword 0xA01F002E
		opword 0x28000016
		opword 0x41820014
		opword 0x2800001A
		opword 0x4182000C
		opword 0x38600005
		bl marioChgMot
		lis r4, wp@ha
		opword 0x38600001
		lwz r5, wp@l(r4)
		opword 0x80850558
		opword 0x38040001
		opword 0x90050558
		opword 0x480009CC
		opword 0x801F0000
		opword 0x5400039F
		opword 0x40820018
		lis r3, wp@ha
		opword 0x38000000
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0x90030558
		opword 0xA01F002E
		opword 0x28000012
		opword 0x40820214
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0xA8030040
		opword 0x2C00000A
		opword 0x408101FC
		opword 0x38600004
		bl camGetPtr
		lis r4, float_90_eki_00008d94@ha
		opword 0xC03F01A8
		lfs f0, float_90_eki_00008d94@l(r4)
		opword 0xC0430114
		opword 0xEC010028
		opword 0xEC20102A
		bl reviseAngle
		lis r3, float_6p2832_eki_00008d00@ha
		lis r6, float_0p00761_eki_00008d08@ha
		addi r5, r3, float_6p2832_eki_00008d00@l
		lis r4, float_360_eki_00008d04@ha
		opword 0xC0050000
		lis r5, float_0p16605_eki_00008d0c@ha
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f4, float_0p00761_eki_00008d08@l(r6)
		opword 0xEC400072
		lfs f0, float_360_eki_00008d04@l(r4)
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r4, float_1_eki_00008d10@ha
		lfs f3, float_0p16605_eki_00008d0c@l(r5)
		opword 0xECC20024
		lfs f2, float_1_eki_00008d10@l(r4)
		opword 0xFC060840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC060040
		opword 0x40800020
		opword 0xEC260828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC060028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		lis r3, float_3p1416_eki_00008d14@ha
		lis r4, float_35_eki_00008e10@ha
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r5, float_0p03705_eki_00008d20@ha
		lfs f2, float_35_eki_00008e10@l(r4)
		lis r4, float_0p4967_eki_00008d24@ha
		opword 0xC01F008C
		opword 0xFC060840
		lis r3, float_1_eki_00008d10@ha
		lfs f5, float_0p03705_eki_00008d20@l(r5)
		opword 0xEC62013A
		lfs f4, float_0p4967_eki_00008d24@l(r4)
		lfs f2, float_1_eki_00008d10@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC060040
		opword 0x4080001C
		opword 0xEC060828
		opword 0xEC000032
		opword 0xECA52038
		opword 0xECA5103A
		opword 0xFCA02850
		opword 0x48000020
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC060028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xECA52038
		opword 0xECA5103A
		lis r3, float_35_eki_00008e10@ha
		opword 0x809D000C
		opword 0xC01F0094
		lfs f2, float_35_eki_00008e10@l(r3)
		opword 0xC024000C
		opword 0xEC82017C
		opword 0xC044002C
		bl distABf
		lis r3, float_35_eki_00008e10@ha
		lfs f0, float_35_eki_00008e10@l(r3)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600002
		opword 0x48000790
		opword 0xA01F002E
		opword 0x28000013
		opword 0x40820088
		opword 0x801F0044
		opword 0x2C000014
		opword 0x4082007C
		lis r3, vec3_eki_000088b4@ha
		opword 0x811D000C
		addi r7, r3, vec3_eki_000088b4@l
		opword 0x387F008C
		opword 0x80C70000
		opword 0x38810098
		opword 0x80A70004
		opword 0x80070008
		opword 0x90C10050
		opword 0xC008000C
		opword 0x90A10054
		opword 0xC028001C
		opword 0xD0010050
		opword 0xC008002C
		opword 0x90010058
		opword 0x80C10050
		opword 0xD0210054
		opword 0xD0010058
		opword 0x80A10054
		opword 0x80010058
		opword 0x90C10098
		opword 0x90A1009C
		opword 0x900100A0
		bl PSVECDistance
		lis r3, float_65_eki_00008e14@ha
		lfs f0, float_65_eki_00008e14@l(r3)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600002
		opword 0x48000700
		lis r4, wp@ha
		lis r3, zero_eki_00008cf4@ha
		addi r4, r4, wp@l
		lfs f0, zero_eki_00008cf4@l(r3)
		opword 0x80840000
		opword 0xC024055C
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082007C
		lis r3, vec3_eki_000088c0@ha
		opword 0x811D000C
		addi r7, r3, vec3_eki_000088c0@l
		opword 0x38640564
		opword 0x80C70000
		opword 0x3881008C
		opword 0x80A70004
		opword 0x80070008
		opword 0x90C10044
		opword 0xC008000C
		opword 0x90A10048
		opword 0xC028001C
		opword 0xD0010044
		opword 0xC008002C
		opword 0x9001004C
		opword 0x80C10044
		opword 0xD0210048
		opword 0xD001004C
		opword 0x80A10048
		opword 0x8001004C
		opword 0x90C1008C
		opword 0x90A10090
		opword 0x90010094
		bl PSVECDistance
		lis r3, float_30_eki_00008da0@ha
		lfs f0, float_30_eki_00008da0@l(r3)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600003
		opword 0x48000664
		opword 0x38600000
		bl partyGetPtr
		bl nokonokoGetStatus
		opword 0x2C030002
		opword 0x40820084
		lis r3, vec3_eki_000088cc@ha
		opword 0x80FD000C
		addi r6, r3, vec3_eki_000088cc@l
		opword 0x38600000
		opword 0x80A60000
		opword 0x80860004
		opword 0x80060008
		opword 0x90A10038
		opword 0xC007000C
		opword 0x9081003C
		opword 0xC027001C
		opword 0xD0010038
		opword 0xC007002C
		opword 0x90010040
		opword 0x80A10038
		opword 0xD021003C
		opword 0xD0010040
		opword 0x8081003C
		opword 0x80010040
		opword 0x90A10080
		opword 0x90810084
		opword 0x90010088
		bl partyGetPtr
		opword 0x38630058
		opword 0x38810080
		bl PSVECDistance
		lis r3, float_30_eki_00008da0@ha
		lfs f0, float_30_eki_00008da0@l(r3)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600002
		opword 0x480005D0
		opword 0x38600000
		bl partyGetPtr
		opword 0x88030031
		opword 0x2C000003
		opword 0x40820098
		opword 0x38600000
		bl partyGetPtr
		opword 0x88030039
		opword 0x28000046
		opword 0x40820084
		lis r3, vec3_eki_000088d8@ha
		opword 0x80FD000C
		addi r6, r3, vec3_eki_000088d8@l
		opword 0x38600000
		opword 0x80A60000
		opword 0x80860004
		opword 0x80060008
		opword 0x90A1002C
		opword 0xC007000C
		opword 0x90810030
		opword 0xC027001C
		opword 0xD001002C
		opword 0xC007002C
		opword 0x90010034
		opword 0x80A1002C
		opword 0xD0210030
		opword 0xD0010034
		opword 0x80810030
		opword 0x80010034
		opword 0x90A10074
		opword 0x90810078
		opword 0x9001007C
		bl partyGetPtr
		opword 0x38630058
		opword 0x38810074
		bl PSVECDistance
		lis r3, float_50_eki_00008d5c@ha
		lfs f0, float_50_eki_00008d5c@l(r3)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600004
		opword 0x48000528
		lis r3, vec3_eki_000088e4@ha
		opword 0x817D000C
		addi r5, r3, vec3_eki_000088e4@l
		lis r3, vec3_eki_000088f0@ha
		opword 0x80850000
		addi r9, r3, vec3_eki_000088f0@l
		opword 0x80050004
		lis r3, float_20_eki_00008e08@ha
		opword 0x81450008
		addi r6, r3, float_20_eki_00008e08@l
		opword 0x90810020
		lis r3, float_0p5_eki_00008d4c@ha
		opword 0xC01F008C
		addi r5, r3, float_0p5_eki_00008d4c@l
		opword 0x90010024
		opword 0x38610068
		opword 0xC02B001C
		opword 0x3881005C
		opword 0xD0010020
		opword 0x81090000
		opword 0xD0210024
		opword 0x80E90004
		opword 0x80090008
		opword 0x90E10018
		opword 0xC01F0094
		opword 0x91410028
		opword 0x81410020
		opword 0xD0010028
		opword 0x81210024
		opword 0x80E10028
		opword 0xD0210018
		opword 0xC0460000
		opword 0x91410068
		opword 0x80C10018
		opword 0x9121006C
		opword 0xC0050000
		opword 0x90E10070
		opword 0x91010014
		opword 0xC06B000C
		opword 0xC02B002C
		opword 0x9001001C
		opword 0xD0610014
		opword 0xD021001C
		opword 0x80A10014
		opword 0x8001001C
		opword 0x90A1005C
		opword 0x90C10060
		opword 0x90010064
		opword 0xC03F01B4
		opword 0xEC22082A
		opword 0xEFE10032
		bl PSVECDistance
		opword 0xFC01F840
		opword 0x4080044C
		opword 0xC01E0028
		lis r3, vec3_eki_000088fc@ha
		opword 0x80BD000C
		addi r7, r3, vec3_eki_000088fc@l
		opword 0x38610068
		opword 0x3881005C
		opword 0xD005000C
		opword 0xC01E002C
		opword 0x80BD000C
		opword 0xD005002C
		opword 0x811D000C
		opword 0x80C70000
		opword 0x80A70004
		opword 0x80070008
		opword 0x90C10008
		opword 0xC008000C
		opword 0x90A1000C
		opword 0xC028001C
		opword 0xD0010008
		opword 0xC008002C
		opword 0x90010010
		opword 0x80C10008
		opword 0xD021000C
		opword 0xD0010010
		opword 0x80A1000C
		opword 0x80010010
		opword 0x90C1005C
		opword 0x90A10060
		opword 0x90010064
		bl PSVECDistance
		opword 0xFFA00890
		opword 0xFC1DF840
		opword 0x408003C8
		opword 0x807D000C
		opword 0xC03F008C
		opword 0xC05F0094
		opword 0xC063000C
		opword 0xC083002C
		bl angleABf
		opword 0xFFC00890
		opword 0xC05F01A0
		bl compAngle
		lis r3, float_40_eki_00008e18@ha
		opword 0xFC200A10
		lfs f0, float_40_eki_00008e18@l(r3)
		opword 0xFC010040
		opword 0x408001D4
		lis r3, float_6p2832_eki_00008d00@ha
		lis r6, float_0p00761_eki_00008d08@ha
		addi r5, r3, float_6p2832_eki_00008d00@l
		opword 0xC01F01A0
		opword 0xC0250000
		lis r5, float_0p16605_eki_00008d0c@ha
		lis r4, float_360_eki_00008d04@ha
		lis r3, float_3p1416_eki_00008d14@ha
		opword 0xEC410032
		lfs f0, float_360_eki_00008d04@l(r4)
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r4, float_1_eki_00008d10@ha
		lfs f4, float_0p00761_eki_00008d08@l(r6)
		opword 0xECA20024
		lfs f3, float_0p16605_eki_00008d0c@l(r5)
		lfs f2, float_1_eki_00008d10@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0x48000070
		opword 0xEC050828
		opword 0xECA10028
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0x48000054
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xECA50828
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC050028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xECA10028
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0xFC802050
		opword 0xECDFE828
		lis r3, float_6p2832_eki_00008d00@ha
		addi r8, r3, float_6p2832_eki_00008d00@l
		lis r6, float_0p03705_eki_00008d20@ha
		lis r3, float_360_eki_00008d04@ha
		opword 0xC0680000
		opword 0xEC060132
		addi r7, r3, float_360_eki_00008d04@l
		lis r5, float_0p4967_eki_00008d24@ha
		lis r3, float_3p1416_eki_00008d14@ha
		lis r4, float_1_eki_00008d10@ha
		lfs f5, float_0p03705_eki_00008d20@l(r6)
		opword 0xFC200050
		opword 0xC0070000
		lfs f4, float_0p4967_eki_00008d24@l(r5)
		opword 0xD03F0174
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		opword 0xC05F01A0
		opword 0xEC4300B2
		lfs f3, float_1_eki_00008d10@l(r4)
		opword 0xEC420024
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0x48000064
		opword 0xEC020828
		opword 0xEC410028
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xFCA02850
		opword 0x48000048
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC020040
		opword 0x4080001C
		opword 0xEC420828
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xFCA02850
		opword 0x48000020
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC020028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC410028
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xEC060172
		opword 0xD01F017C
		opword 0x480001C0
		lis r3, float_6p2832_eki_00008d00@ha
		lis r6, float_0p00761_eki_00008d08@ha
		addi r5, r3, float_6p2832_eki_00008d00@l
		lis r4, float_360_eki_00008d04@ha
		opword 0xC0050000
		lis r3, float_3p1416_eki_00008d14@ha
		lis r5, float_0p16605_eki_00008d0c@ha
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		opword 0xEC4007B2
		lfs f0, float_360_eki_00008d04@l(r4)
		lis r4, float_1_eki_00008d10@ha
		lfs f4, float_0p00761_eki_00008d08@l(r6)
		lfs f3, float_0p16605_eki_00008d0c@l(r5)
		opword 0xECA20024
		lfs f2, float_1_eki_00008d10@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC050028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x809D000C
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r5, float_0p03705_eki_00008d20@ha
		opword 0xC004000C
		lis r4, float_0p4967_eki_00008d24@ha
		opword 0xFC050840
		lis r3, float_1_eki_00008d10@ha
		opword 0xEC5F013C
		opword 0xC01F008C
		lfs f4, float_0p03705_eki_00008d20@l(r5)
		lfs f3, float_0p4967_eki_00008d24@l(r4)
		opword 0xEC020028
		lfs f2, float_1_eki_00008d10@l(r3)
		opword 0xD01F0174
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC050028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x807D000C
		opword 0xC01F0094
		opword 0xC023002C
		opword 0xEC3F093A
		opword 0xEC010028
		opword 0xD01F017C
		opword 0x38600000
		opword 0xE3E100E8
		opword 0xCBE100E0
		opword 0xE3C100D8
		opword 0xCBC100D0
		opword 0xE3A100C8
		opword 0xCBA100C0
		opword 0xBBA100B4
		opword 0x800100F4
		opword 0x7C0803A6
		opword 0x382100F0
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
static void ext_moamoa_main(void) {
	char _af_pad[168];
	asm volatile {
		bl marioGetPtr
		opword 0x7C7C1B78
		opword 0x38600000
		bl partyGetPtr
		opword 0x7C771B78
		opword 0x38600004
		bl camGetPtr
		opword 0xA01C002E
		opword 0x3B200000
		opword 0x28000012
		opword 0x4082001C
		lis r3, wp@ha
		lwz r4, wp@l(r3)
		opword 0xA8640040
		opword 0x38030001
		opword 0xB0040040
		opword 0x48000018
		lis r3, wp@ha
		opword 0x38000000
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0xB0030040
		opword 0xA01C002E
		opword 0x28000000
		opword 0x40820038
		lis r3, wp@ha
		addi r5, r3, wp@l
		opword 0x80850000
		opword 0xA8640042
		opword 0x38030001
		opword 0xB0040042
		opword 0x80650000
		opword 0xA8030042
		opword 0x2C0003E8
		opword 0x40810024
		opword 0x380003E8
		opword 0xB0030042
		opword 0x48000018
		lis r3, wp@ha
		opword 0x38000000
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0xB0030042
		opword 0x80170000
		opword 0x540005EF
		opword 0x41820020
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0xA0030000
		opword 0x60000010
		opword 0xB0030000
		opword 0x4800001C
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0xA0030000
		opword 0x54000734
		opword 0xB0030000
		lis r4, float_neg1_eki_00008cfc@ha
		lis r3, wp@ha
		addi r5, r4, float_neg1_eki_00008cfc@l
		addi r4, r3, wp@l
		opword 0xC0050000
		opword 0x80640000
		opword 0xD003055C
		opword 0x80640000
		opword 0xD0030560
		opword 0x88170031
		opword 0x2C000005
		opword 0x40820230
		opword 0x80170000
		opword 0x540005EF
		opword 0x41820224
		bl cloudGetBreathDir
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0xD023055C
		bl cloudGetBreathDist
		lis r3, wp@ha
		lis r4, float_6p2832_eki_00008d00@ha
		addi r10, r3, wp@l
		lis r7, float_0p00761_eki_00008d08@ha
		opword 0x80AA0000
		lis r3, float_360_eki_00008d04@ha
		addi r8, r3, float_360_eki_00008d04@l
		addi r9, r4, float_6p2832_eki_00008d00@l
		opword 0xD0250560
		lis r3, float_3p1416_eki_00008d14@ha
		addi r4, r3, float_3p1416_eki_00008d14@l
		lis r6, float_0p16605_eki_00008d0c@ha
		opword 0x806A0000
		lis r5, float_1_eki_00008d10@ha
		opword 0xC0490000
		opword 0xC023055C
		opword 0xC0080000
		opword 0xEC420072
		opword 0xC0240000
		lfs f4, float_0p00761_eki_00008d08@l(r7)
		lfs f3, float_0p16605_eki_00008d0c@l(r6)
		opword 0xECA20024
		lfs f2, float_1_eki_00008d10@l(r5)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r4, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0x48000070
		opword 0xEC050828
		opword 0xECA10028
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0x48000054
		lis r4, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r4)
		opword 0xFC050040
		opword 0x40800020
		opword 0xECA50828
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0xFC802050
		opword 0x48000028
		lis r4, float_1p5708_eki_00008d18@ha
		opword 0xEC050028
		lfs f1, float_1p5708_eki_00008d18@l(r4)
		opword 0xECA10028
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0xFC802050
		opword 0xC0230560
		lis r9, wp@ha
		opword 0xC0170058
		lis r4, float_6p2832_eki_00008d00@ha
		addi r8, r4, float_6p2832_eki_00008d00@l
		lis r6, float_0p03705_eki_00008d20@ha
		opword 0xEC01013A
		lis r4, float_360_eki_00008d04@ha
		addi r7, r4, float_360_eki_00008d04@l
		lis r5, float_0p4967_eki_00008d24@ha
		lis r4, float_3p1416_eki_00008d14@ha
		addi r10, r9, wp@l
		opword 0xD0030564
		lis r3, float_1_eki_00008d10@ha
		opword 0xC0680000
		opword 0xC017005C
		opword 0x812A0000
		lfs f1, float_3p1416_eki_00008d14@l(r4)
		opword 0xD0090568
		opword 0xC0070000
		opword 0x80EA0000
		lfs f5, float_0p03705_eki_00008d20@l(r6)
		opword 0xC047055C
		lfs f4, float_0p4967_eki_00008d24@l(r5)
		opword 0xEC4300B2
		lfs f3, float_1_eki_00008d10@l(r3)
		opword 0xEC420024
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0x48000064
		opword 0xEC020828
		opword 0xEC410028
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xFCA02850
		opword 0x48000048
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC020040
		opword 0x4080001C
		opword 0xEC420828
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xFCA02850
		opword 0x48000020
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC020028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC410028
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xC0270560
		opword 0xC0170060
		opword 0xEC01017C
		opword 0xD007056C
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0xA8030038
		opword 0x2C0000FA
		opword 0x40810098
		bl extGetPosePtr
		lis r3, wp@ha
		opword 0x39000000
		addi r6, r3, wp@l
		opword 0x38800019
		opword 0x80A60000
		opword 0x38600000
		opword 0x81250008
		opword 0x48000034
		opword 0xA0A90000
		opword 0x54A0077B
		opword 0x40820020
		opword 0x54A006F7
		opword 0x40820030
		opword 0xB0890002
		opword 0xB0690004
		opword 0xA0090000
		opword 0x60000010
		opword 0xB0090000
		opword 0x39080001
		opword 0x39290050
		opword 0x80E60000
		opword 0x80070004
		opword 0x7C080000
		opword 0x4180FFC4
		opword 0x80070044
		opword 0x28000000
		opword 0x40820028
		lis r3, evt_moamoa_escape@ha
		opword 0x38800000
		addi r3, r3, evt_moamoa_escape@l
		opword 0x38A00000
		bl evtEntry
		lis r4, wp@ha
		addi r4, r4, wp@l
		opword 0x80840000
		opword 0x90640044
		bl extGetPosePtr
		lis r5, wp@ha
		lis r4, eki_00_str_00000560@ha
		addi r27, r5, wp@l
		opword 0x7C7E1B78
		opword 0x80BB0000
		addi r24, r4, eki_00_str_00000560@l
		opword 0x3B400000
		opword 0x3BA00000
		opword 0x83E50008
		opword 0x48002B44
		opword 0x807E000C
		opword 0xC03C008C
		opword 0xC05C0094
		opword 0xC063000C
		opword 0xC083002C
		bl angleABf
		opword 0x807B0000
		opword 0xD0230550
		opword 0x807E000C
		opword 0xC03C008C
		opword 0xC05C0094
		opword 0xC063000C
		opword 0xC083002C
		bl distABf
		opword 0x807B0000
		opword 0xD0230554
		opword 0x807B0000
		opword 0xA0630000
		opword 0x546007FF
		opword 0x41820728
		opword 0x5460077B
		opword 0x40820720
		bl marioKeyOffChk
		opword 0x2C030000
		opword 0x40820714
		bl marioCtrlOffChk
		opword 0x2C030000
		opword 0x40820708
		opword 0x2C190000
		opword 0x40820700
		opword 0xA01F0000
		opword 0x70000154
		opword 0x408206F4
		opword 0x7FC3F378
		opword 0x7FE4FB78
		bl moamoa_hit_check
		opword 0x7C771B78
		opword 0x2C170001
		opword 0x40820170
		opword 0xA01F0000
		lis r4, eki_00_str_00000050@ha
		lis r3, eki_00_str_00000040@ha
		lis r5, wp@ha
		opword 0x60060004
		opword 0x38000024
		opword 0xB0DF0000
		addi r21, r4, eki_00_str_00000050@l
		addi r22, r3, eki_00_str_00000040@l
		opword 0xB01F0002
		lwzu r4, wp@l(r5)
		opword 0xA8640038
		opword 0x38030001
		opword 0xB0040038
		opword 0xA01F0000
		opword 0x80650000
		opword 0x54000529
		opword 0x3B230050
		opword 0x41820038
		opword 0x889F004C
		lis r3, g5_group_tbl_s588@ha
		addi r0, r3, g5_group_tbl_s588@l
		opword 0x54831D78
		opword 0x28040002
		opword 0x7C601A14
		opword 0x82C30000
		opword 0x41800008
		opword 0x82A30004
		opword 0x2804000A
		opword 0x4082000C
		lis r3, eki_00_str_00000578@ha
		addi r21, r3, eki_00_str_00000578@l
		lis r3, wp@ha
		opword 0x3AE00000
		addi r18, r3, wp@l
		opword 0x48000034
		opword 0x7F23CB78
		opword 0x7EC4B378
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x7EA4AB78
		opword 0x38790010
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3AF70001
		opword 0x3B390028
		opword 0x80720000
		opword 0x8003004C
		opword 0x7C170000
		opword 0x4180FFC4
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0x8003004C
		opword 0x7C170000
		opword 0x40800080
		opword 0xA81F003C
		opword 0x7C00B800
		opword 0x41820074
		opword 0xA01F0000
		opword 0x5400077B
		opword 0x41820020
		lis r4, eki_00_str_0000057C@ha
		opword 0x7EA3AB78
		addi r4, r4, eki_00_str_0000057C@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x4082004C
		opword 0xA01F0000
		opword 0x540006F7
		opword 0x41820020
		lis r4, eki_00_str_00000580@ha
		opword 0x7EA3AB78
		addi r4, r4, eki_00_str_00000580@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x40820024
		lis r3, gp@ha
		opword 0xB2FF003C
		addi r3, r3, gp@l
		opword 0x80630000
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F0044
		opword 0x901F0040
		opword 0x3B200001
		opword 0x48000570
		opword 0x2C170002
		opword 0x4182000C
		opword 0x2C170004
		opword 0x40820178
		opword 0xA01F0000
		lis r4, eki_00_str_00000050@ha
		lis r3, eki_00_str_00000040@ha
		lis r5, wp@ha
		opword 0x6006000C
		opword 0x3800002F
		opword 0xB0DF0000
		addi r19, r4, eki_00_str_00000050@l
		addi r20, r3, eki_00_str_00000040@l
		opword 0xB01F0002
		lwzu r4, wp@l(r5)
		opword 0xA8640038
		opword 0x38030001
		opword 0xB0040038
		opword 0xA01F0000
		opword 0x80650000
		opword 0x54000529
		opword 0x3AC30050
		opword 0x41820038
		opword 0x889F004C
		lis r3, g5_group_tbl_s588@ha
		addi r0, r3, g5_group_tbl_s588@l
		opword 0x54831D78
		opword 0x28040002
		opword 0x7C601A14
		opword 0x82830000
		opword 0x41800008
		opword 0x82630004
		opword 0x2804000A
		opword 0x4082000C
		lis r3, eki_00_str_00000578@ha
		addi r19, r3, eki_00_str_00000578@l
		lis r3, wp@ha
		opword 0x3AA00000
		addi r18, r3, wp@l
		opword 0x48000034
		opword 0x7EC3B378
		opword 0x7E84A378
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x7E649B78
		opword 0x38760010
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3AB50001
		opword 0x3AD60028
		opword 0x80720000
		opword 0x8003004C
		opword 0x7C150000
		opword 0x4180FFC4
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0x8003004C
		opword 0x7C150000
		opword 0x40800080
		opword 0xA81F003C
		opword 0x7C00A800
		opword 0x41820074
		opword 0xA01F0000
		opword 0x5400077B
		opword 0x41820020
		lis r4, eki_00_str_0000057C@ha
		opword 0x7E639B78
		addi r4, r4, eki_00_str_0000057C@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x4082004C
		opword 0xA01F0000
		opword 0x540006F7
		opword 0x41820020
		lis r4, eki_00_str_00000580@ha
		opword 0x7E639B78
		addi r4, r4, eki_00_str_00000580@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x40820024
		lis r3, gp@ha
		opword 0xB2BF003C
		addi r3, r3, gp@l
		opword 0x80630000
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F0044
		opword 0x901F0040
		opword 0x2C170004
		opword 0x418203F4
		opword 0x3B200001
		opword 0x480003EC
		opword 0x2C170003
		opword 0x408203E4
		lis r3, wp@ha
		opword 0xA01F0000
		addi r4, r3, wp@l
		opword 0x80E40000
		opword 0x60050084
		lis r4, float_0p5_eki_00008d4c@ha
		opword 0x38000030
		opword 0xC047055C
		addi r6, r4, float_0p5_eki_00008d4c@l
		opword 0xC0270550
		lis r3, vec3_eki_00008908@ha
		addi r4, r3, vec3_eki_00008908@l
		opword 0xC0060000
		opword 0xB0BF0000
		opword 0xEC22082A
		opword 0xB01F0002
		fmuls f27, f1, f0
		opword 0x80640000
		opword 0x80040004
		opword 0x907F0008
		opword 0x901F000C
		opword 0x80040008
		opword 0x901F0010
		bl rand
		opword 0x6C648000
		opword 0x3C004330
		lis r3, float_6p2832_eki_00008d00@ha
		stw r4, _af_pad+164(r1)
		lfs f0, float_6p2832_eki_00008d00@l(r3)
		lis r5, double_to_int_eki_00008df8@ha
		opword 0x900100A8
		lis r3, float_360_eki_00008d04@ha
		lfd f3, double_to_int_eki_00008df8@l(r5)
		opword 0xEC2006F2
		lfs f0, float_360_eki_00008d04@l(r3)
		lis r4, float_32767_eki_00008d50@ha
		opword 0xC84100A8
		lis r5, float_0p00761_eki_00008d08@ha
		opword 0xEFC10024
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f5, float_0p00761_eki_00008d08@l(r5)
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r3, float_1_eki_00008d10@ha
		opword 0xEC621828
		lfs f2, float_32767_eki_00008d50@l(r4)
		lis r4, float_0p1_eki_00008d54@ha
		addi r6, r4, float_0p1_eki_00008d54@l
		opword 0xFC1E0840
		opword 0xEC431024
		opword 0xC0060000
		lis r4, float_0p16605_eki_00008d0c@ha
		lfs f4, float_0p16605_eki_00008d0c@l(r4)
		lfs f3, float_1_eki_00008d10@l(r3)
		opword 0xEFE2003A
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC1E0040
		opword 0x40800020
		opword 0xEC3E0828
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC1E0028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0xEC1F0172
		opword 0xD01F0014
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_eki_00008df8@ha
		opword 0x906100AC
		addi r5, r4, double_to_int_eki_00008df8@l
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100A8
		addi r4, r3, float_32767_eki_00008d50@l
		opword 0xC8450000
		lis r3, float_0p03_eki_00008d58@ha
		opword 0xC82100A8
		addi r6, r3, float_0p03_eki_00008d58@l
		opword 0xC0040000
		lis r5, float_0p03705_eki_00008d20@ha
		opword 0xEC411028
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r4, float_0p4967_eki_00008d24@ha
		lis r3, float_1_eki_00008d10@ha
		lfs f4, float_0p03705_eki_00008d20@l(r5)
		opword 0xEC420024
		opword 0xC0060000
		lfs f3, float_0p4967_eki_00008d24@l(r4)
		opword 0xEC02003A
		lfs f2, float_1_eki_00008d10@l(r3)
		opword 0xFC1E0840
		opword 0xD01F001C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC1E0040
		opword 0x4080001C
		opword 0xEC1E0828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC1E0028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC002050
		lis r4, eki_00_str_00000050@ha
		lis r3, eki_00_str_00000040@ha
		opword 0x38000078
		lis r5, wp@ha
		addi r22, r4, eki_00_str_00000050@l
		opword 0xEC1F0032
		addi r21, r3, eki_00_str_00000040@l
		opword 0xD01F0020
		opword 0xB01F0018
		lwzu r4, wp@l(r5)
		opword 0xA8640038
		opword 0x38030001
		opword 0xB0040038
		opword 0xA01F0000
		opword 0x80650000
		opword 0x54000529
		opword 0x3A830050
		opword 0x41820038
		opword 0x889F004C
		lis r3, g5_group_tbl_s588@ha
		addi r0, r3, g5_group_tbl_s588@l
		opword 0x54831D78
		opword 0x28040002
		opword 0x7C601A14
		opword 0x82A30000
		opword 0x41800008
		opword 0x82C30004
		opword 0x2804000A
		opword 0x4082000C
		lis r3, eki_00_str_00000578@ha
		addi r22, r3, eki_00_str_00000578@l
		lis r3, wp@ha
		opword 0x3A600000
		addi r23, r3, wp@l
		opword 0x48000034
		opword 0x7E83A378
		opword 0x7EA4AB78
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x7EC4B378
		opword 0x38740010
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3A730001
		opword 0x3A940028
		opword 0x80770000
		opword 0x8003004C
		opword 0x7C130000
		opword 0x4180FFC4
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0x8003004C
		opword 0x7C130000
		opword 0x40800080
		opword 0xA81F003C
		opword 0x7C009800
		opword 0x41820074
		opword 0xA01F0000
		opword 0x5400077B
		opword 0x41820020
		lis r4, eki_00_str_0000057C@ha
		opword 0x7EC3B378
		addi r4, r4, eki_00_str_0000057C@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x4082004C
		opword 0xA01F0000
		opword 0x540006F7
		opword 0x41820020
		lis r4, eki_00_str_00000580@ha
		opword 0x7EC3B378
		addi r4, r4, eki_00_str_00000580@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x40820024
		lis r3, gp@ha
		opword 0xB27F003C
		addi r3, r3, gp@l
		opword 0x80630000
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F0044
		opword 0x901F0040
		opword 0x3B200001
		opword 0x809B0000
		opword 0xA0040000
		opword 0x540007FF
		opword 0x41820040
		opword 0xA0BF0000
		opword 0x70A00155
		opword 0x40820034
		lis r3, float_50_eki_00008d5c@ha
		opword 0xC0240554
		lfs f0, float_50_eki_00008d5c@l(r3)
		opword 0xFC010040
		opword 0x40800020
		opword 0x54A007BD
		opword 0x41820010
		opword 0x38000001
		opword 0xB01F0024
		opword 0x4800000C
		opword 0x38000001
		opword 0xB01F0002
		opword 0x807B0000
		opword 0xA0030000
		opword 0x540007FF
		opword 0x418200A8
		opword 0xA01F0000
		opword 0x70000444
		opword 0x4082009C
		lis r4, gp@ha
		opword 0x80630004
		addi r4, r4, gp@l
		opword 0x80840000
		opword 0x8084001C
		opword 0x7C041B96
		opword 0x7C0019D6
		opword 0x7C002050
		opword 0x7C1D0040
		opword 0x40820074
		opword 0x386003E8
		bl irand
		opword 0x2C0300C8
		opword 0x40800064
		lis r3, vec3_eki_00008914@ha
		opword 0x80BE000C
		addi r8, r3, vec3_eki_00008914@l
		opword 0x7F03C378
		opword 0x80E80000
		opword 0x38810038
		opword 0x80C80004
		opword 0x80080008
		opword 0x90E10020
		opword 0xC005000C
		opword 0x90C10024
		opword 0xC025001C
		opword 0xD0010020
		opword 0xC005002C
		opword 0x90010028
		opword 0x80C10020
		opword 0xD0210024
		opword 0xD0010028
		opword 0x80A10024
		opword 0x80010028
		opword 0x90C10038
		opword 0x90A1003C
		opword 0x90010040
		bl psndSFXOn_3D
		opword 0xA81F0002
		opword 0x28000041
		opword 0x41812224
		lis r3, eki_00_jumptable_00002400@ha
		opword 0x5400103A
		addi r3, r3, eki_00_jumptable_00002400@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x38600032
		opword 0x7C1D1BD6
		opword 0x7C0019D6
		opword 0x7C00E850
		opword 0x2C000014
		opword 0x408004B4
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_eki_00008df8@ha
		lfd f1, double_to_int_eki_00008df8@l(r4)
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100A8
		addi r5, r3, float_32767_eki_00008d50@l
		opword 0xC0450000
		lis r4, float_6p2832_eki_00008d00@ha
		opword 0xC80100A8
		lis r3, zero_eki_00008cf4@ha
		opword 0xEC600828
		lfs f1, float_6p2832_eki_00008d00@l(r4)
		lfs f0, zero_eki_00008cf4@l(r3)
		opword 0xEC431024
		opword 0xEFE2007A
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_eki_00008df8@ha
		opword 0x906100B4
		addi r5, r4, double_to_int_eki_00008df8@l
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100B0
		addi r4, r3, float_32767_eki_00008d50@l
		opword 0xC8450000
		lis r5, float_50_eki_00008d5c@ha
		opword 0xC82100B0
		addi r7, r5, float_50_eki_00008d5c@l
		opword 0xC0040000
		lis r4, zero_eki_00008cf4@ha
		opword 0xEC411028
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		addi r6, r4, zero_eki_00008cf4@l
		lis r5, float_0p00761_eki_00008d08@ha
		lis r4, float_0p16605_eki_00008d0c@ha
		opword 0xEC620024
		opword 0xC0470000
		opword 0xC0060000
		lis r3, float_1_eki_00008d10@ha
		lfs f4, float_0p00761_eki_00008d08@l(r5)
		opword 0xECE300BA
		opword 0xFC1F0840
		lfs f3, float_0p16605_eki_00008d0c@l(r4)
		lfs f2, float_1_eki_00008d10@l(r3)
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xFC1F0840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC1F07F2
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC8407F2
		opword 0x48000070
		opword 0xEC1F0828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0x48000054
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC1F0040
		opword 0x40800020
		opword 0xEC3F0828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC1F0028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x38800003
		lis r5, wp@ha
		opword 0x7C1D23D6
		lwz r6, wp@l(r5)
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r5, float_0p03705_eki_00008d20@ha
		lis r3, float_1_eki_00008d10@ha
		opword 0x7C0021D6
		lis r4, float_0p4967_eki_00008d24@ha
		lfs f5, float_0p4967_eki_00008d24@l(r4)
		opword 0xFC1F0840
		lfs f6, float_0p03705_eki_00008d20@l(r5)
		lfs f2, float_1_eki_00008d10@l(r3)
		opword 0x7C00E850
		opword 0x1C00000C
		opword 0x7C860214
		opword 0xC0040014
		opword 0xEC67013A
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xFC1F0840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC1F07F2
		opword 0xECC62838
		opword 0xECC6103A
		opword 0x48000064
		opword 0xEC1F0828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xECC62838
		opword 0xECC6103A
		opword 0xFCC03050
		opword 0x48000048
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC1F0040
		opword 0x4080001C
		opword 0xEC1F0828
		opword 0xEC000032
		opword 0xECC62838
		opword 0xECC6103A
		opword 0xFCC03050
		opword 0x48000020
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC1F0028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xECC62838
		opword 0xECC6103A
		opword 0xC004001C
		opword 0x807E000C
		opword 0xEC8701BC
		opword 0xC023000C
		opword 0xC043002C
		bl angleABf
		lis r3, float_6p2832_eki_00008d00@ha
		lis r6, float_0p00761_eki_00008d08@ha
		addi r5, r3, float_6p2832_eki_00008d00@l
		lis r4, float_360_eki_00008d04@ha
		opword 0xC0050000
		lis r5, float_0p16605_eki_00008d0c@ha
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f4, float_0p00761_eki_00008d08@l(r6)
		opword 0xEC400072
		lfs f0, float_360_eki_00008d04@l(r4)
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r4, float_1_eki_00008d10@ha
		lfs f3, float_0p16605_eki_00008d0c@l(r5)
		opword 0xECA20024
		lfs f2, float_1_eki_00008d10@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC050028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x80DE000C
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r4, float_15_eki_00008d60@ha
		lfs f2, float_15_eki_00008d60@l(r4)
		lis r4, float_0p4967_eki_00008d24@ha
		opword 0xC006000C
		opword 0xFC050840
		lis r5, float_0p03705_eki_00008d20@ha
		lis r3, float_1_eki_00008d10@ha
		opword 0xEF82013A
		opword 0xC3A6001C
		lfs f4, float_0p03705_eki_00008d20@l(r5)
		lfs f3, float_0p4967_eki_00008d24@l(r4)
		lfs f2, float_1_eki_00008d10@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC050028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_15_eki_00008d60@ha
		opword 0xC006002C
		lfs f1, float_15_eki_00008d60@l(r3)
		opword 0xEF61013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_eki_00008df8@ha
		lis r3, float_32767_eki_00008d50@ha
		lfd f2, double_to_int_eki_00008df8@l(r4)
		opword 0x900100B0
		lfs f0, float_32767_eki_00008d50@l(r3)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEFC10024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_eki_00008df8@ha
		lfd f2, double_to_int_eki_00008df8@l(r4)
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100A8
		lis r5, float_1p5_eki_00008d64@ha
		lfs f4, float_1p5_eki_00008d64@l(r5)
		lis r4, float_1p2_eki_00008d6c@ha
		opword 0xC82100A8
		opword 0xFC60D890
		lfs f0, float_32767_eki_00008d50@l(r3)
		lis r3, float_0p8_eki_00008d68@ha
		opword 0xEC411028
		lfs f5, float_1p2_eki_00008d6c@l(r4)
		opword 0xFC20E090
		opword 0xEC9E213A
		opword 0xA8BF0002
		opword 0xECC20024
		lfs f0, float_0p8_eki_00008d68@l(r3)
		opword 0x7FC3F378
		opword 0x7FE4FB78
		opword 0x38C00001
		opword 0xFC40E890
		opword 0xECA6017A
		bl moamoa_jump
		opword 0xA01F0000
		opword 0x60000001
		opword 0xB01F0000
		opword 0x48001D44
		opword 0x38600003
		opword 0x80BE000C
		opword 0x7C1D1BD6
		lis r4, wp@ha
		opword 0xC025000C
		addi r4, r4, wp@l
		opword 0xC045002C
		opword 0x80840000
		opword 0x7C0019D6
		opword 0x7C00E850
		opword 0x1E40000C
		opword 0x7C649214
		opword 0xC0630014
		opword 0xC083001C
		bl distABf
		lis r3, wp@ha
		opword 0x809E000C
		lwz r0, wp@l(r3)
		opword 0xFF800890
		opword 0xC024000C
		opword 0x7C609214
		opword 0xC044002C
		opword 0xC0630014
		opword 0xC083001C
		bl angleABf
		lis r3, float_100_eki_00008d70@ha
		lfs f0, float_100_eki_00008d70@l(r3)
		opword 0xFC1C0040
		opword 0x4080004C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_eki_00008df8@ha
		lfd f1, double_to_int_eki_00008df8@l(r4)
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100B0
		addi r5, r3, float_32767_eki_00008d50@l
		opword 0xC0450000
		lis r4, float_360_eki_00008d04@ha
		opword 0xC80100B0
		lis r3, zero_eki_00008cf4@ha
		opword 0xEC600828
		lfs f1, float_360_eki_00008d04@l(r4)
		lfs f0, zero_eki_00008cf4@l(r3)
		opword 0xEC431024
		opword 0xEC22007A
		lis r3, float_6p2832_eki_00008d00@ha
		lis r6, float_0p00761_eki_00008d08@ha
		addi r5, r3, float_6p2832_eki_00008d00@l
		lis r4, float_360_eki_00008d04@ha
		opword 0xC0050000
		lis r5, float_0p16605_eki_00008d0c@ha
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f4, float_0p00761_eki_00008d08@l(r6)
		opword 0xEC400072
		lfs f0, float_360_eki_00008d04@l(r4)
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r4, float_1_eki_00008d10@ha
		lfs f3, float_0p16605_eki_00008d0c@l(r5)
		opword 0xECA20024
		lfs f2, float_1_eki_00008d10@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC050028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x80DE000C
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r4, float_5_eki_00008d74@ha
		lfs f2, float_5_eki_00008d74@l(r4)
		lis r4, float_0p4967_eki_00008d24@ha
		opword 0xC006000C
		opword 0xFC050840
		lis r5, float_0p03705_eki_00008d20@ha
		lis r3, float_1_eki_00008d10@ha
		opword 0xEFC2013A
		opword 0xC3E6001C
		lfs f4, float_0p03705_eki_00008d20@l(r5)
		lfs f3, float_0p4967_eki_00008d24@l(r4)
		lfs f2, float_1_eki_00008d10@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC050028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_5_eki_00008d74@ha
		opword 0xC006002C
		lfs f1, float_5_eki_00008d74@l(r3)
		opword 0xEF61013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_eki_00008df8@ha
		lis r3, float_32767_eki_00008d50@ha
		lfd f2, double_to_int_eki_00008df8@l(r4)
		opword 0x900100B0
		lfs f0, float_32767_eki_00008d50@l(r3)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEF810024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_eki_00008df8@ha
		lfd f2, double_to_int_eki_00008df8@l(r4)
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100A8
		lis r5, float_0p2_eki_00008d7c@ha
		lfs f0, float_32767_eki_00008d50@l(r3)
		lis r4, float_0p3_eki_00008d78@ha
		opword 0xC82100A8
		lis r3, float_0p5_eki_00008d4c@ha
		lfs f4, float_0p2_eki_00008d7c@l(r5)
		opword 0xFC60D890
		opword 0xEC411028
		lfs f5, float_0p3_eki_00008d78@l(r4)
		opword 0xFC20F090
		opword 0xA8BF0002
		opword 0xEC9C293A
		opword 0xECC20024
		lfs f0, float_0p5_eki_00008d4c@l(r3)
		opword 0x7FC3F378
		opword 0x7FE4FB78
		opword 0x38C00001
		opword 0xFC40F890
		opword 0xECA6017A
		bl moamoa_jump
		opword 0xA01F0000
		opword 0x5400043C
		opword 0xB01F0000
		opword 0x48001A24
		opword 0xA87F0004
		opword 0x3863FFFF
		opword 0x7C600735
		opword 0xB07F0004
		opword 0x40801A10
		opword 0x38000000
		opword 0xB01F0004
		opword 0xA87F0002
		opword 0x38030001
		opword 0xB01F0002
		opword 0x480019F8
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_eki_00008df8@ha
		lfd f2, double_to_int_eki_00008df8@l(r4)
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100B0
		addi r5, r3, float_32767_eki_00008d50@l
		opword 0xC0250000
		lis r4, float_200_eki_00008d80@ha
		opword 0xC80100B0
		lis r3, zero_eki_00008cf4@ha
		addi r5, r4, float_200_eki_00008d80@l
		opword 0xEC601028
		addi r4, r3, zero_eki_00008cf4@l
		opword 0xC0450000
		lis r3, float_300_eki_00008d84@ha
		opword 0xC0040000
		opword 0xEC630824
		lfs f1, float_300_eki_00008d84@l(r3)
		opword 0xEC0300BA
		opword 0xD01F001C
		opword 0xC01F001C
		opword 0xEC010032
		opword 0xEF801024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_eki_00008df8@ha
		opword 0x906100AC
		addi r5, r4, double_to_int_eki_00008df8@l
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100A8
		addi r4, r3, float_32767_eki_00008d50@l
		opword 0xC8250000
		lis r3, zero_eki_00008cf4@ha
		opword 0xC80100A8
		opword 0x38000000
		opword 0xC0440000
		opword 0xEC600828
		lfs f1, zero_eki_00008cf4@l(r3)
		opword 0xEC1C0828
		opword 0xEC431024
		opword 0xEC02083A
		opword 0xD01F0020
		opword 0xA87F0002
		opword 0x38630001
		opword 0xB07F0002
		opword 0xB01F0004
		opword 0xA81F0004
		opword 0x2C0000C8
		opword 0x40800010
		lis r3, float_1_eki_00008d10@ha
		lfs f1, float_1_eki_00008d10@l(r3)
		opword 0x48000034
		opword 0x20600320
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_eki_00008df8@ha
		opword 0x906100B4
		lis r3, float_600_eki_00008d88@ha
		lfd f2, double_to_int_eki_00008df8@l(r4)
		opword 0x900100B0
		lfs f0, float_600_eki_00008d88@l(r3)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEC210024
		lis r3, zero_eki_00008cf4@ha
		opword 0xFF800890
		lfs f0, zero_eki_00008cf4@l(r3)
		opword 0xFC010040
		opword 0x40800014
		opword 0xA01F0000
		opword 0xFF800090
		opword 0x60000200
		opword 0xB01F0000
		opword 0x38C00003
		lis r3, gp@ha
		opword 0x7CBD33D6
		lwz r4, gp@l(r3)
		opword 0x3C004330
		opword 0x900100B0
		lis r3, double_to_int_mask_eki_00008e00@ha
		opword 0x8004001C
		opword 0x7C8531D6
		opword 0x7C1D0214
		opword 0x900100B4
		lis r5, wp@ha
		lfd f1, double_to_int_mask_eki_00008e00@l(r3)
		lis r3, float_0p25_eki_00008d8c@ha
		opword 0xC80100B0
		opword 0x7C04E850
		opword 0x1C00000C
		opword 0xEC200828
		lfs f0, float_0p25_eki_00008d8c@l(r3)
		lwz r3, wp@l(r5)
		opword 0x7C630214
		opword 0xEC210032
		opword 0xC3630014
		opword 0xC3C30018
		opword 0xC3A3001C
		bl sin
		lis r3, gp@ha
		opword 0x3C004330
		addi r4, r3, gp@l
		opword 0xFC400818
		opword 0x80A40000
		lis r3, double_to_int_mask_eki_00008e00@ha
		opword 0xC03F0020
		addi r4, r3, double_to_int_mask_eki_00008e00@l
		opword 0x80A5001C
		opword 0xEC6100B2
		opword 0x900100A8
		opword 0x7C1D2A14
		opword 0xC01F001C
		opword 0x900100AC
		lis r3, float_0p25_eki_00008d8c@ha
		opword 0xC8440000
		opword 0xEFC0F73A
		opword 0xC82100A8
		opword 0xEF7CD8FA
		lfs f0, float_0p25_eki_00008d8c@l(r3)
		opword 0xEC211028
		opword 0xEC210032
		bl cos
		opword 0x809E000C
		lis r3, float_15_eki_00008d60@ha
		opword 0xC01F0020
		opword 0xFC800818
		opword 0xC064000C
		opword 0xFC200050
		lfs f2, float_15_eki_00008d60@l(r3)
		opword 0xEC1B1828
		opword 0xEC210132
		opword 0xEC001024
		opword 0xEC03002A
		opword 0xEFBCE87A
		opword 0xD004000C
		opword 0x807E000C
		opword 0xC023001C
		opword 0xEC1E0828
		opword 0xEC001024
		opword 0xEC01002A
		opword 0xD003001C
		opword 0x807E000C
		opword 0xC023002C
		opword 0xEC1D0828
		opword 0xEC001024
		opword 0xEC01002A
		opword 0xD003002C
		opword 0xA87F0004
		opword 0x38030001
		opword 0xB01F0004
		opword 0x4800178C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_eki_00008df8@ha
		lfd f2, double_to_int_eki_00008df8@l(r4)
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100B0
		addi r5, r3, float_32767_eki_00008d50@l
		lis r4, float_90_eki_00008d94@ha
		opword 0xC0050000
		opword 0xC82100B0
		lis r3, float_neg45_eki_00008d90@ha
		addi r9, r4, float_90_eki_00008d94@l
		lis r4, float_6p2832_eki_00008d00@ha
		opword 0xEC211028
		addi r5, r3, float_neg45_eki_00008d90@l
		lis r3, wp@ha
		addi r8, r4, float_6p2832_eki_00008d00@l
		addi r6, r3, wp@l
		lis r4, float_1_eki_00008d10@ha
		opword 0xEC410024
		opword 0x81460000
		opword 0xC0050000
		lis r3, float_360_eki_00008d04@ha
		opword 0xC0290000
		addi r7, r3, float_360_eki_00008d04@l
		opword 0xEC22007A
		opword 0xC06A0550
		opword 0xC0480000
		lis r6, float_0p00761_eki_00008d08@ha
		lis r5, float_0p16605_eki_00008d0c@ha
		opword 0xC0070000
		opword 0xEC63082A
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		opword 0xC38A0554
		opword 0xEC4200F2
		lfs f5, float_0p00761_eki_00008d08@l(r6)
		lfs f4, float_0p16605_eki_00008d0c@l(r5)
		lfs f3, float_1_eki_00008d10@l(r4)
		opword 0xECC20024
		opword 0xFC060840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xFC060840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC0601B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA501B2
		opword 0x48000070
		opword 0xEC060828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0x48000054
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC060040
		opword 0x40800020
		opword 0xEC260828
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC060028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x80DE000C
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r4, float_15_eki_00008d60@ha
		lfs f2, float_15_eki_00008d60@l(r4)
		lis r5, float_0p03705_eki_00008d20@ha
		opword 0xC006000C
		opword 0xFC060840
		lis r4, float_0p4967_eki_00008d24@ha
		lis r3, float_1_eki_00008d10@ha
		opword 0xEFC2017A
		opword 0xC3E6001C
		lfs f4, float_0p03705_eki_00008d20@l(r5)
		lfs f3, float_0p4967_eki_00008d24@l(r4)
		lfs f2, float_1_eki_00008d10@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xFC060840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC0601B2
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x48000064
		opword 0xEC060828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000048
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC060040
		opword 0x4080001C
		opword 0xEC060828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC060028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_15_eki_00008d60@ha
		opword 0xC006002C
		lfs f1, float_15_eki_00008d60@l(r3)
		opword 0xEFA1013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_eki_00008df8@ha
		lfd f1, double_to_int_eki_00008df8@l(r4)
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100B0
		addi r5, r3, float_32767_eki_00008d50@l
		opword 0xC0450000
		lis r4, zero_eki_00008cf4@ha
		opword 0xC80100B0
		lis r3, float_1_eki_00008d10@ha
		opword 0xEC600828
		lfs f1, zero_eki_00008cf4@l(r4)
		lfs f0, float_1_eki_00008d10@l(r3)
		opword 0xEC431024
		opword 0xEF62007A
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_eki_00008df8@ha
		lfd f2, double_to_int_eki_00008df8@l(r4)
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100A8
		addi r5, r3, float_32767_eki_00008d50@l
		opword 0xC0050000
		lis r4, zero_eki_00008cf4@ha
		opword 0xC82100A8
		lis r3, float_0p4_eki_00008d98@ha
		addi r5, r4, zero_eki_00008cf4@l
		opword 0xFC80D890
		opword 0xEC611028
		addi r4, r3, float_0p4_eki_00008d98@l
		opword 0xC0240000
		lis r3, float_100_eki_00008d70@ha
		opword 0xC0450000
		opword 0xEC630024
		lfs f0, float_100_eki_00008d70@l(r3)
		opword 0x7FC3F378
		opword 0x7FE4FB78
		opword 0xECA308BA
		opword 0xFC20F090
		opword 0xFC40F890
		opword 0xFC60E890
		opword 0xFC1C0040
		opword 0x4080000C
		opword 0xA8BF0002
		opword 0x48000008
		opword 0x38A00000
		opword 0x38C00001
		bl moamoa_jump
		opword 0x48001494
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_eki_00008df8@ha
		lfd f2, double_to_int_eki_00008df8@l(r4)
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100B0
		addi r5, r3, float_32767_eki_00008d50@l
		lis r4, float_90_eki_00008d94@ha
		lis r3, float_neg45_eki_00008d90@ha
		opword 0xC82100B0
		addi r7, r4, float_90_eki_00008d94@l
		opword 0xC0050000
		addi r6, r3, float_neg45_eki_00008d90@l
		opword 0xEC211028
		lis r3, wp@ha
		addi r5, r3, wp@l
		lis r4, float_180_eki_00008d9c@ha
		opword 0x81250000
		addi r8, r4, float_180_eki_00008d9c@l
		opword 0xEC410024
		opword 0xC0060000
		opword 0xC0270000
		lis r3, float_6p2832_eki_00008d00@ha
		addi r5, r3, float_6p2832_eki_00008d00@l
		lis r4, float_360_eki_00008d04@ha
		opword 0xEC02007A
		opword 0xC0890550
		opword 0xC0680000
		addi r7, r4, float_360_eki_00008d04@l
		opword 0xC0450000
		lis r3, float_3p1416_eki_00008d14@ha
		opword 0xEC84002A
		lis r6, float_0p00761_eki_00008d08@ha
		opword 0xC0070000
		lis r5, float_0p16605_eki_00008d0c@ha
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r4, float_1_eki_00008d10@ha
		opword 0xEC84182A
		opword 0xC3890554
		lfs f5, float_0p00761_eki_00008d08@l(r6)
		lfs f3, float_1_eki_00008d10@l(r4)
		opword 0xEC420132
		lfs f4, float_0p16605_eki_00008d0c@l(r5)
		opword 0xEC420024
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA500B2
		opword 0x48000070
		opword 0xEC020828
		opword 0xEC410028
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA500B2
		opword 0x48000054
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC020040
		opword 0x40800020
		opword 0xEC420828
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA500B2
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC020028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC410028
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA500B2
		opword 0xFCA02850
		opword 0x809E000C
		lis r3, float_30_eki_00008da0@ha
		lfs f1, float_30_eki_00008da0@l(r3)
		opword 0xC004000C
		opword 0xC3E4001C
		opword 0xEFC1017A
		opword 0xC3A4002C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_eki_00008df8@ha
		lfd f1, double_to_int_eki_00008df8@l(r4)
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100B0
		addi r5, r3, float_32767_eki_00008d50@l
		opword 0xC0450000
		lis r4, zero_eki_00008cf4@ha
		opword 0xC80100B0
		lis r3, float_1_eki_00008d10@ha
		lis r5, float_2_eki_00008da4@ha
		opword 0xEC600828
		lfs f1, zero_eki_00008cf4@l(r4)
		lfs f0, float_1_eki_00008d10@l(r3)
		opword 0xEC631024
		lfs f2, float_2_eki_00008da4@l(r5)
		opword 0xEC03007A
		opword 0xEF620032
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_eki_00008df8@ha
		lfd f2, double_to_int_eki_00008df8@l(r4)
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100A8
		addi r5, r3, float_32767_eki_00008d50@l
		lis r6, float_2_eki_00008da4@ha
		opword 0xC0050000
		opword 0xC82100A8
		lis r4, zero_eki_00008cf4@ha
		lis r3, float_0p4_eki_00008d98@ha
		lfs f4, float_2_eki_00008da4@l(r6)
		opword 0xEC211028
		addi r5, r4, zero_eki_00008cf4@l
		addi r4, r3, float_0p4_eki_00008d98@l
		opword 0xC0450000
		lis r3, float_100_eki_00008d70@ha
		opword 0xEC610024
		opword 0xC0240000
		opword 0x7FE4FB78
		lfs f0, float_100_eki_00008d70@l(r3)
		opword 0x7FC3F378
		opword 0xEC6308BA
		opword 0xFC20F090
		opword 0xFC40F890
		opword 0xECA400F2
		opword 0xFC60E890
		opword 0xFC80D890
		opword 0xFC1C0040
		opword 0x4080000C
		opword 0xA8BF0002
		opword 0x48000008
		opword 0x38A00000
		opword 0x38C00001
		bl moamoa_jump
		opword 0x48001230
		opword 0x807E000C
		opword 0xC01F0014
		opword 0xC023001C
		opword 0xEC01002A
		opword 0xD003001C
		opword 0xC03F0014
		opword 0xC01F0020
		opword 0xEC010028
		opword 0xD01F0014
		opword 0x807E000C
		opword 0xC07F0008
		opword 0xC023000C
		opword 0xC043002C
		opword 0xC09F0010
		bl angleABf
		lis r3, float_6p2832_eki_00008d00@ha
		lis r6, float_0p00761_eki_00008d08@ha
		addi r5, r3, float_6p2832_eki_00008d00@l
		lis r4, float_360_eki_00008d04@ha
		opword 0xC0050000
		lis r5, float_0p16605_eki_00008d0c@ha
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f4, float_0p00761_eki_00008d08@l(r6)
		opword 0xEC400072
		lfs f0, float_360_eki_00008d04@l(r4)
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r4, float_1_eki_00008d10@ha
		lfs f3, float_0p16605_eki_00008d0c@l(r5)
		opword 0xECA20024
		lfs f2, float_1_eki_00008d10@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC050028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x80FE000C
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r5, float_0p4967_eki_00008d24@ha
		opword 0xC05F001C
		lis r6, float_0p03705_eki_00008d20@ha
		opword 0xC007000C
		opword 0xFC050840
		lis r4, float_1_eki_00008d10@ha
		lfs f3, float_0p4967_eki_00008d24@l(r5)
		opword 0xEC02013A
		lfs f4, float_0p03705_eki_00008d20@l(r6)
		lfs f2, float_1_eki_00008d10@l(r4)
		opword 0xD007000C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC050028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x807E000C
		opword 0xFC202050
		opword 0xC05F001C
		opword 0xC003002C
		opword 0xEC02007A
		opword 0xD003002C
		opword 0xA87F0018
		opword 0x3863FFFF
		opword 0x7C600735
		opword 0xB07F0018
		opword 0x40801028
		opword 0xC01F0008
		opword 0x38000000
		opword 0x807E000C
		opword 0xD003000C
		opword 0xC01F000C
		opword 0x807E000C
		opword 0xD003001C
		opword 0xC01F0010
		opword 0x807E000C
		opword 0xD003002C
		opword 0xA07F0000
		opword 0x546307FA
		opword 0xB07F0000
		opword 0x807E0000
		opword 0x54630734
		opword 0x907E0000
		opword 0xB01F0004
		opword 0xA87F0002
		opword 0x38030001
		opword 0xB01F0002
		opword 0x48000FD4
		opword 0xA87F0004
		opword 0x38630001
		opword 0x7C600734
		opword 0xB07F0004
		opword 0x2C000004
		opword 0x40810FBC
		opword 0xA81F0024
		opword 0xB01F0002
		opword 0x48000FB0
		opword 0xA01F0000
		opword 0x540007FF
		opword 0x40820010
		opword 0xC37C008C
		opword 0xC39C0094
		opword 0x48000030
		opword 0x38600003
		lis r4, wp@ha
		opword 0x7C1D1BD6
		addi r4, r4, wp@l
		opword 0x80840000
		opword 0x7C0019D6
		opword 0x7C00E850
		opword 0x1C00000C
		opword 0x7C640214
		opword 0xC3630014
		opword 0xC383001C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_eki_00008df8@ha
		lis r3, float_32767_eki_00008d50@ha
		lfd f4, double_to_int_eki_00008df8@l(r4)
		opword 0x900100B0
		opword 0xFC40E090
		lfs f0, float_32767_eki_00008d50@l(r3)
		opword 0xFC20D890
		opword 0xC86100B0
		opword 0x80BE000C
		opword 0xECA32028
		opword 0xC065000C
		opword 0xC085002C
		opword 0xEF850024
		bl angleABf
		lis r3, float_90_eki_00008d94@ha
		lis r4, float_neg45_eki_00008d90@ha
		addi r5, r3, float_90_eki_00008d94@l
		lfs f0, float_neg45_eki_00008d90@l(r4)
		opword 0xC0450000
		lis r3, float_6p2832_eki_00008d00@ha
		addi r8, r3, float_6p2832_eki_00008d00@l
		lis r4, float_360_eki_00008d04@ha
		opword 0xEC1C00BA
		addi r7, r4, float_360_eki_00008d04@l
		lis r6, float_0p00761_eki_00008d08@ha
		lis r5, float_0p16605_eki_00008d0c@ha
		lis r3, float_3p1416_eki_00008d14@ha
		lis r4, float_1_eki_00008d10@ha
		opword 0xEC41002A
		opword 0xC0280000
		opword 0xC0070000
		lfs f4, float_0p00761_eki_00008d08@l(r6)
		opword 0xEC4100B2
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lfs f3, float_0p16605_eki_00008d0c@l(r5)
		opword 0xECA20024
		lfs f2, float_1_eki_00008d10@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC050028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x80DE000C
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r4, float_15_eki_00008d60@ha
		lfs f2, float_15_eki_00008d60@l(r4)
		lis r4, float_0p4967_eki_00008d24@ha
		opword 0xC006000C
		opword 0xFC050840
		lis r5, float_0p03705_eki_00008d20@ha
		lis r3, float_1_eki_00008d10@ha
		opword 0xEFC2013A
		opword 0xC3E6001C
		lfs f4, float_0p03705_eki_00008d20@l(r5)
		lfs f3, float_0p4967_eki_00008d24@l(r4)
		lfs f2, float_1_eki_00008d10@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC050028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_15_eki_00008d60@ha
		opword 0xC006002C
		lfs f1, float_15_eki_00008d60@l(r3)
		opword 0xEF61013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_eki_00008df8@ha
		lis r3, float_32767_eki_00008d50@ha
		lfd f2, double_to_int_eki_00008df8@l(r4)
		opword 0x900100B0
		lfs f0, float_32767_eki_00008d50@l(r3)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEF810024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_eki_00008df8@ha
		lfd f2, double_to_int_eki_00008df8@l(r4)
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100A8
		addi r5, r3, float_32767_eki_00008d50@l
		opword 0xC0050000
		lis r4, zero_eki_00008cf4@ha
		opword 0xC82100A8
		lis r3, float_1_eki_00008d10@ha
		lfs f5, zero_eki_00008cf4@l(r4)
		opword 0x7FE4FB78
		opword 0xEC611028
		opword 0xA8BF0002
		opword 0xFC20F090
		opword 0x38C00001
		opword 0xFC40F890
		opword 0x38A50001
		opword 0xECC30024
		lfs f0, float_1_eki_00008d10@l(r3)
		opword 0x7FC3F378
		opword 0xEC9C017A
		opword 0xFC60D890
		opword 0xECA6017A
		bl moamoa_jump
		opword 0x48000CAC
		opword 0xA87F0004
		opword 0x38630001
		opword 0x7C600734
		opword 0xB07F0004
		opword 0x2C00001E
		opword 0x40800040
		opword 0x809E000C
		lis r3, float_0p9_eki_00008da8@ha
		lfs f1, float_0p9_eki_00008da8@l(r3)
		opword 0xC0040000
		opword 0xEC000072
		opword 0xD0040000
		opword 0x807E000C
		opword 0xC0030014
		opword 0xEC000072
		opword 0xD0030014
		opword 0x807E000C
		opword 0xC0030028
		opword 0xEC000072
		opword 0xD0030028
		opword 0x48000C58
		opword 0x38000031
		opword 0xB01F0002
		opword 0x48000C4C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_eki_00008df8@ha
		lis r3, float_32767_eki_00008d50@ha
		lfd f2, double_to_int_eki_00008df8@l(r4)
		opword 0x900100B0
		lfs f0, float_32767_eki_00008d50@l(r3)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEF810024
		bl rand
		lis r5, float_90_eki_00008d94@ha
		lis r4, float_135_eki_00008dac@ha
		lfs f0, float_135_eki_00008dac@l(r4)
		opword 0x6C668000
		lfs f1, float_90_eki_00008d94@l(r5)
		opword 0x3C004330
		lis r3, float_6p2832_eki_00008d00@ha
		lis r4, double_to_int_eki_00008df8@ha
		addi r5, r3, float_6p2832_eki_00008d00@l
		opword 0x90C100AC
		opword 0xEC1C007A
		addi r6, r4, double_to_int_eki_00008df8@l
		opword 0x900100A8
		lis r3, float_360_eki_00008d04@ha
		opword 0xC0250000
		addi r4, r3, float_360_eki_00008d04@l
		lis r3, float_32767_eki_00008d50@ha
		opword 0xEC210032
		opword 0xC0040000
		addi r5, r3, float_32767_eki_00008d50@l
		opword 0xC8660000
		lis r4, float_300_eki_00008d84@ha
		opword 0xC84100A8
		opword 0xECE10024
		addi r6, r4, float_300_eki_00008d84@l
		lis r3, float_3p1416_eki_00008d14@ha
		lis r4, float_0p16605_eki_00008d0c@ha
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r3, float_1_eki_00008d10@ha
		opword 0xEC621828
		opword 0xC0450000
		lis r5, float_200_eki_00008d80@ha
		opword 0xC0060000
		addi r7, r5, float_200_eki_00008d80@l
		opword 0xFC070840
		opword 0xEC631024
		opword 0xC0470000
		lis r5, float_0p00761_eki_00008d08@ha
		lfs f4, float_0p16605_eki_00008d0c@l(r4)
		lfs f5, float_0p00761_eki_00008d08@l(r5)
		opword 0xECC300BA
		lfs f2, float_1_eki_00008d10@l(r3)
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xFC070840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC0701F2
		opword 0xECA52038
		opword 0xECA5103A
		opword 0xECA501F2
		opword 0x48000070
		opword 0xEC070828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5103A
		opword 0xECA50072
		opword 0x48000054
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC070040
		opword 0x40800020
		opword 0xEC270828
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5103A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC070028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5103A
		opword 0xECA50072
		opword 0xFCA02850
		lis r3, float_3p1416_eki_00008d14@ha
		opword 0x80DE000C
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r5, float_0p03705_eki_00008d20@ha
		opword 0xC006000C
		lis r4, float_0p4967_eki_00008d24@ha
		opword 0xFC070840
		lis r3, float_1_eki_00008d10@ha
		opword 0xEFC6017A
		lfs f4, float_0p03705_eki_00008d20@l(r5)
		lfs f3, float_0p4967_eki_00008d24@l(r4)
		lfs f2, float_1_eki_00008d10@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xFC070840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC0701F2
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x48000064
		opword 0xEC070828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000048
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC070040
		opword 0x4080001C
		opword 0xEC070828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC070028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xC006002C
		opword 0xEFE6013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_eki_00008df8@ha
		lfd f1, double_to_int_eki_00008df8@l(r4)
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100B0
		addi r5, r3, float_32767_eki_00008d50@l
		opword 0xC0450000
		lis r4, float_1_eki_00008d10@ha
		opword 0xC80100B0
		lis r3, float_5_eki_00008d74@ha
		opword 0xEC600828
		lfs f1, float_1_eki_00008d10@l(r4)
		lfs f0, float_5_eki_00008d74@l(r3)
		opword 0xEC431024
		opword 0xEF62007A
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_eki_00008df8@ha
		lfd f1, double_to_int_eki_00008df8@l(r4)
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100A8
		addi r5, r3, float_32767_eki_00008d50@l
		opword 0xC0450000
		lis r4, float_0p1_eki_00008db4@ha
		opword 0xC80100A8
		lis r3, float_0p2_eki_00008db0@ha
		opword 0x2C1A0000
		opword 0xEC600828
		lfs f1, float_0p1_eki_00008db4@l(r4)
		lfs f0, float_0p2_eki_00008db0@l(r3)
		opword 0xEC431024
		opword 0xEF82007A
		opword 0x40820050
		lis r3, vec3_eki_00008920@ha
		opword 0x38810014
		addi r7, r3, vec3_eki_00008920@l
		opword 0x386006C3
		opword 0x80C70000
		opword 0x80A70004
		opword 0x80070008
		opword 0x90C10014
		opword 0x90A10018
		opword 0x9001001C
		opword 0x80BE000C
		opword 0xC005000C
		opword 0xD0010014
		opword 0xC005001C
		opword 0xD0010018
		opword 0xC005002C
		opword 0xD001001C
		bl psndSFXOn_3D
		opword 0x3B400001
		lis r3, float_neg100_eki_00008db8@ha
		opword 0xFC20F090
		lfs f2, float_neg100_eki_00008db8@l(r3)
		opword 0xFC60F890
		opword 0xFC80D890
		opword 0x7FC3F378
		opword 0xFCA0E090
		opword 0x7FE4FB78
		opword 0x38A00031
		opword 0x38C00000
		bl moamoa_jump
		opword 0x480008FC
		opword 0xA87F0018
		opword 0x3863FFFF
		opword 0x7C600735
		opword 0xB07F0018
		opword 0x40810074
		opword 0xC03F0008
		opword 0xC01F0014
		opword 0xEC01002A
		opword 0xD01F0008
		opword 0xC03F000C
		opword 0xC01F001C
		opword 0xEC01002A
		opword 0xD01F000C
		opword 0xC03F0010
		opword 0xC01F0020
		opword 0xEC01002A
		opword 0xD01F0010
		opword 0x807E000C
		opword 0xC01F0008
		opword 0xC023000C
		opword 0xEC01002A
		opword 0xD003000C
		opword 0x807E000C
		opword 0xC01F000C
		opword 0xC023001C
		opword 0xEC01002A
		opword 0xD003001C
		opword 0x807E000C
		opword 0xC01F0010
		opword 0xC023002C
		opword 0xEC01002A
		opword 0xD003002C
		opword 0x48000878
		opword 0x38000031
		opword 0xB01F0002
		opword 0x4800086C
		lis r3, wp@ha
		lwz r4, wp@l(r3)
		opword 0xA0640000
		opword 0x546004E7
		opword 0x41820018
		opword 0x546004A5
		opword 0x41820010
		opword 0x3800003E
		opword 0xB01F0002
		opword 0x48000844
		opword 0xA8040038
		opword 0x2C0000FA
		opword 0x40800078
		opword 0x807E000C
		bl PSMTXIdentity
		opword 0x38A00003
		lis r6, wp@ha
		opword 0x7C9D2BD6
		opword 0x807E000C
		addi r7, r6, wp@l
		opword 0x80C70000
		opword 0x38000000
		opword 0x7C8429D6
		opword 0x7C84E850
		opword 0x1D04000C
		opword 0x38880014
		opword 0x7C06242E
		opword 0x38A80018
		opword 0x3888001C
		opword 0xD003000C
		opword 0x80C70000
		opword 0x807E000C
		opword 0x7C062C2E
		opword 0xD003001C
		opword 0x80A70000
		opword 0x807E000C
		opword 0x7C05242E
		opword 0xD003002C
		opword 0xB01F0000
		opword 0xB01F0002
		opword 0xB01F0004
		opword 0x480007C4
		opword 0x3800003E
		opword 0xB01F0002
		opword 0x480007B8
		opword 0xA81F0004
		opword 0x2C00001E
		opword 0x40800048
		lis r4, float_0p20944_eki_00008dbc@ha
		opword 0x38610074
		addi r5, r4, float_0p20944_eki_00008dbc@l
		opword 0x38800079
		opword 0xC0250000
		bl PSMTXRotRad
		opword 0x807E000C
		opword 0x38810074
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x801E0000
		opword 0x540007FA
		opword 0x901E0000
		opword 0xA87F0004
		opword 0x38030001
		opword 0xB01F0004
		opword 0x48000768
		opword 0x38600003
		opword 0x80BE0000
		opword 0x7C1D1BD6
		lis r4, wp@ha
		opword 0x60A50002
		opword 0x90BE0000
		opword 0x80BE000C
		opword 0xC025000C
		opword 0x7C0019D6
		lwz r3, wp@l(r4)
		opword 0xC045002C
		opword 0x7C00E850
		opword 0x1C00000C
		opword 0x7C630214
		opword 0xC0630014
		opword 0xC083001C
		bl distABf
		lis r4, float_100_eki_00008d70@ha
		lis r3, float_0p5_eki_00008d4c@ha
		lfs f2, float_100_eki_00008d70@l(r4)
		lfs f0, float_0p5_eki_00008d4c@l(r3)
		opword 0xEC220828
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD80100B0
		opword 0x800100B4
		opword 0xB01F0004
		opword 0xA87F0002
		opword 0x38030001
		opword 0xB01F0002
		opword 0x480006EC
		opword 0xA87F0004
		opword 0x3863FFFF
		opword 0x7C600735
		opword 0xB07F0004
		opword 0x408006D8
		opword 0xA87F0002
		opword 0x38030001
		opword 0xB01F0002
		opword 0x480006C8
		opword 0x809E000C
		lis r3, double_300_eki_00008dc0@ha
		lfd f1, double_300_eki_00008dc0@l(r3)
		opword 0xC004000C
		opword 0xFC000210
		opword 0xFC000840
		opword 0x408002FC
		opword 0xC004002C
		opword 0xFC000210
		opword 0xFC000840
		opword 0x408002EC
		bl rand
		opword 0x38800003
		opword 0x6C658000
		opword 0x7C1D23D6
		opword 0x80DE000C
		opword 0x3C604330
		opword 0x90A100B4
		lis r5, double_to_int_eki_00008df8@ha
		opword 0xC066000C
		opword 0x906100B0
		lis r3, float_32767_eki_00008d50@ha
		lfs f0, float_32767_eki_00008d50@l(r3)
		opword 0x7C0021D6
		lfd f2, double_to_int_eki_00008df8@l(r5)
		lis r3, wp@ha
		opword 0xC82100B0
		addi r3, r3, wp@l
		opword 0xC086002C
		opword 0xEC211028
		opword 0x7C00E850
		opword 0x1C00000C
		opword 0x80630000
		opword 0xEF810024
		opword 0x7C630214
		opword 0xC0230014
		opword 0xC043001C
		bl angleABf
		lis r3, float_90_eki_00008d94@ha
		lis r4, float_neg45_eki_00008d90@ha
		addi r5, r3, float_90_eki_00008d94@l
		lfs f0, float_neg45_eki_00008d90@l(r4)
		opword 0xC0450000
		lis r3, float_6p2832_eki_00008d00@ha
		addi r8, r3, float_6p2832_eki_00008d00@l
		lis r4, float_360_eki_00008d04@ha
		opword 0xEC1C00BA
		addi r7, r4, float_360_eki_00008d04@l
		lis r6, float_0p00761_eki_00008d08@ha
		lis r5, float_0p16605_eki_00008d0c@ha
		lis r3, float_3p1416_eki_00008d14@ha
		lis r4, float_1_eki_00008d10@ha
		opword 0xEC41002A
		opword 0xC0280000
		opword 0xC0070000
		lfs f4, float_0p00761_eki_00008d08@l(r6)
		opword 0xEC4100B2
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lfs f3, float_0p16605_eki_00008d0c@l(r5)
		opword 0xECA20024
		lfs f2, float_1_eki_00008d10@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC050028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		lis r3, float_3p1416_eki_00008d14@ha
		opword 0x80DE000C
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r4, float_15_eki_00008d60@ha
		lfs f2, float_15_eki_00008d60@l(r4)
		lis r4, float_0p4967_eki_00008d24@ha
		opword 0xC006000C
		opword 0xFC050840
		lis r5, float_0p03705_eki_00008d20@ha
		lis r3, float_1_eki_00008d10@ha
		opword 0xEFC2013A
		lfs f4, float_0p03705_eki_00008d20@l(r5)
		lfs f3, float_0p4967_eki_00008d24@l(r4)
		lfs f2, float_1_eki_00008d10@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC050028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_15_eki_00008d60@ha
		opword 0xC006002C
		lfs f1, float_15_eki_00008d60@l(r3)
		opword 0xEF61013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_eki_00008df8@ha
		lis r3, float_32767_eki_00008d50@ha
		lfd f2, double_to_int_eki_00008df8@l(r4)
		opword 0x900100B0
		lfs f0, float_32767_eki_00008d50@l(r3)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEF810024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_eki_00008df8@ha
		lfd f2, double_to_int_eki_00008df8@l(r4)
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100A8
		addi r5, r3, float_32767_eki_00008d50@l
		lis r3, float_1_eki_00008d10@ha
		opword 0xC0050000
		opword 0xC82100A8
		lis r4, zero_eki_00008cf4@ha
		addi r5, r4, zero_eki_00008cf4@l
		lfs f5, float_1_eki_00008d10@l(r3)
		opword 0xEC211028
		opword 0xC0450000
		lis r4, float_3_eki_00008dc8@ha
		opword 0xFC60D890
		lfs f4, float_3_eki_00008dc8@l(r4)
		opword 0x7FC3F378
		opword 0xECC10024
		opword 0xA8BF0002
		opword 0x7FE4FB78
		opword 0x38C00001
		opword 0xEC1C28BA
		opword 0xFC20F090
		opword 0xECA628BA
		opword 0xEC840032
		bl moamoa_jump
		opword 0x480003B4
		opword 0x3800003E
		opword 0xB01F0002
		opword 0x480003A8
		opword 0xA01F0000
		opword 0x60000020
		opword 0xB01F0000
		opword 0x801E0000
		opword 0x5400003C
		opword 0x901E0000
		opword 0x801E0000
		opword 0x60000004
		opword 0x901E0000
		opword 0x48000380
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_eki_00008df8@ha
		lis r3, float_32767_eki_00008d50@ha
		lfd f2, double_to_int_eki_00008df8@l(r4)
		opword 0x900100B0
		lfs f0, float_32767_eki_00008d50@l(r3)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEF810024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_eki_00008df8@ha
		lfd f1, double_to_int_eki_00008df8@l(r4)
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100A8
		addi r5, r3, float_32767_eki_00008d50@l
		opword 0xC0450000
		lis r4, float_1_eki_00008d10@ha
		opword 0xC80100A8
		lis r3, float_2_eki_00008da4@ha
		opword 0x7FA00E70
		opword 0xEC600828
		lfs f0, float_2_eki_00008da4@l(r3)
		lfs f1, float_1_eki_00008d10@l(r4)
		opword 0x7C600194
		opword 0xEC431024
		opword 0xEFE2007A
		bl irand
		lis r5, float_90_eki_00008d94@ha
		lis r4, float_225_eki_00008dcc@ha
		lfs f1, float_90_eki_00008d94@l(r5)
		lis r7, float_0p00761_eki_00008d08@ha
		lfs f0, float_225_eki_00008dcc@l(r4)
		lis r6, float_6p2832_eki_00008d00@ha
		lis r5, float_360_eki_00008d04@ha
		lis r4, float_3p1416_eki_00008d14@ha
		opword 0xEC1C007A
		lfs f1, float_6p2832_eki_00008d00@l(r6)
		lis r6, float_0p16605_eki_00008d0c@ha
		opword 0xB07F0004
		lfs f4, float_0p00761_eki_00008d08@l(r7)
		opword 0xEC410032
		lfs f0, float_360_eki_00008d04@l(r5)
		lis r5, float_1_eki_00008d10@ha
		lfs f1, float_3p1416_eki_00008d14@l(r4)
		opword 0xEFC20024
		lfs f3, float_0p16605_eki_00008d0c@l(r6)
		lfs f2, float_1_eki_00008d10@l(r5)
		opword 0xFC1E0840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC1E0040
		opword 0x40800020
		opword 0xEC3E0828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC1E0028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0xEC1F0132
		opword 0xD01F0008
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_eki_00008df8@ha
		opword 0x906100B4
		addi r5, r4, double_to_int_eki_00008df8@l
		lis r3, float_32767_eki_00008d50@ha
		opword 0x900100B0
		addi r4, r3, float_32767_eki_00008d50@l
		opword 0xC8450000
		lis r3, float_1_eki_00008d10@ha
		opword 0xC82100B0
		addi r5, r3, float_1_eki_00008d10@l
		opword 0xC0040000
		lis r4, float_0p03705_eki_00008d20@ha
		opword 0xEC611028
		lis r3, float_3p1416_eki_00008d14@ha
		lfs f1, float_3p1416_eki_00008d14@l(r3)
		lis r3, float_0p4967_eki_00008d24@ha
		opword 0xC0450000
		opword 0xEC030024
		lfs f4, float_0p03705_eki_00008d20@l(r4)
		lfs f3, float_0p4967_eki_00008d24@l(r3)
		opword 0xEC0010BA
		opword 0xFC1E0840
		opword 0xD01F000C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_eki_00008d18@ha
		lfs f1, float_1p5708_eki_00008d18@l(r3)
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
		lis r3, float_4p7124_eki_00008d1c@ha
		lfs f0, float_4p7124_eki_00008d1c@l(r3)
		opword 0xFC1E0040
		opword 0x4080001C
		opword 0xEC1E0828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_eki_00008d18@ha
		opword 0xEC1E0028
		lfs f1, float_1p5708_eki_00008d18@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC002050
		opword 0xEC1F0032
		opword 0xD01F0010
		opword 0xA87F0002
		opword 0x38030001
		opword 0xB01F0002
		opword 0x480000F4
		opword 0xA87F0004
		opword 0x3863FFFF
		opword 0x7C600735
		opword 0xB07F0004
		opword 0x408000E0
		opword 0xA87F0002
		opword 0x38030001
		opword 0xB01F0002
		opword 0x480000D0
		lis r3, float_1p1_eki_00008dd0@ha
		lis r4, float_1p02_eki_00008dd4@ha
		addi r6, r3, float_1p1_eki_00008dd0@l
		lis r3, float_0p20944_eki_00008dbc@ha
		opword 0xC03F0008
		addi r5, r4, float_1p02_eki_00008dd4@l
		opword 0xC0660000
		addi r4, r3, float_0p20944_eki_00008dbc@l
		opword 0xC0050000
		opword 0x38610044
		opword 0xEC4100F2
		opword 0xC0240000
		opword 0x38800079
		opword 0xD05F0008
		opword 0xC05F000C
		opword 0xEC020032
		opword 0xD01F000C
		opword 0xC01F0010
		opword 0xEC0000F2
		opword 0xD01F0010
		opword 0x80BE000C
		opword 0xC01F0008
		opword 0xC045000C
		opword 0xEC02002A
		opword 0xD005000C
		opword 0x80BE000C
		opword 0xC01F000C
		opword 0xC045001C
		opword 0xEC02002A
		opword 0xD005001C
		opword 0x80BE000C
		opword 0xC01F0010
		opword 0xC045002C
		opword 0xEC02002A
		opword 0xD005002C
		bl PSMTXRotRad
		opword 0x807E000C
		opword 0x38810044
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x801E0000
		lis r3, float_neg1000_eki_00008dd8@ha
		lfs f0, float_neg1000_eki_00008dd8@l(r3)
		opword 0x540007FA
		opword 0x901E0000
		opword 0x807E000C
		opword 0xC023000C
		opword 0xFC010040
		opword 0x4080000C
		opword 0x3800003E
		opword 0xB01F0002
		opword 0xA01F0000
		opword 0x70000098
		opword 0x40820074
		opword 0x809E000C
		lis r3, float_280_eki_00008ddc@ha
		lfs f0, float_280_eki_00008ddc@l(r3)
		opword 0xC024000C
		opword 0xFC010040
		opword 0x40810008
		opword 0xD004000C
		opword 0x809E000C
		lis r3, float_neg120_eki_00008de0@ha
		lfs f0, float_neg120_eki_00008de0@l(r3)
		opword 0xC024000C
		opword 0xFC010040
		opword 0x40800008
		opword 0xD004000C
		opword 0x809E000C
		lis r3, float_70_eki_00008de4@ha
		lfs f0, float_70_eki_00008de4@l(r3)
		opword 0xC024002C
		opword 0xFC010040
		opword 0x40810008
		opword 0xD004002C
		opword 0x809E000C
		lis r3, float_neg70_eki_00008de8@ha
		lfs f0, float_neg70_eki_00008de8@l(r3)
		opword 0xC024002C
		opword 0xFC010040
		opword 0x40800008
		opword 0xD004002C
		opword 0x807E000C
		opword 0x3BBD0001
		opword 0xC003000C
		opword 0xD01F0028
		opword 0x807E000C
		opword 0x3BDE0020
		opword 0xC003002C
		opword 0xD01F002C
		opword 0x3BFF0050
		opword 0x807B0000
		opword 0x80030004
		opword 0x7C1D0000
		opword 0x4180D4B4
		bl extGetPosePtr
		lis r4, wp@ha
		lis r7, float_60_eki_00008dec@ha
		addi r26, r4, wp@l
		lis r6, float_1000_eki_00008df0@ha
		opword 0x813A0000
		lis r5, float_1_eki_00008d10@ha
		lis r4, double_to_int_eki_00008df8@ha
		lis r8, gp@ha
		opword 0x82690008
		opword 0x7C741B78
		lfs f31, float_60_eki_00008dec@l(r7)
		addi r25, r8, gp@l
		lfs f30, float_1000_eki_00008df0@l(r6)
		opword 0x3AA00000
		lfs f29, float_1_eki_00008d10@l(r5)
		opword 0x3F008000
		lfd f28, double_to_int_eki_00008df8@l(r4)
		opword 0x3F604330
		opword 0x480000BC
		opword 0x807800F8
		opword 0x380003E8
		opword 0x80990000
		opword 0x38A00000
		opword 0x5463F0BE
		opword 0xA913003C
		opword 0x7CC30396
		opword 0x82E4003C
		opword 0x80130044
		opword 0x82C40038
		opword 0x7C80B810
		opword 0x80130040
		opword 0x1D080028
		opword 0x7C60B110
		opword 0x3A480050
		opword 0x7E479214
		bl __div2u
		bl __cvt_ull_flt
		opword 0xEC3F0072
		opword 0xC012001C
		opword 0xEC21F024
		opword 0xEC210024
		opword 0xFC01E840
		opword 0x4C411382
		opword 0x40820014
		opword 0x92F30044
		lis r3, zero_eki_00008cf4@ha
		lfs f1, zero_eki_00008cf4@l(r3)
		opword 0x92D30040
		opword 0x80720024
		opword 0x3AB50001
		opword 0x936100B0
		opword 0x3A730050
		opword 0x3803FFFF
		opword 0x80720020
		opword 0x6C008000
		opword 0x900100B4
		opword 0xC80100B0
		opword 0xEC00E028
		opword 0xEC000072
		opword 0xFC00001E
		opword 0xD80100A8
		opword 0x800100AC
		opword 0x7C030214
		opword 0x90140010
		opword 0x3A940020
		opword 0x80FA0000
		opword 0x80070004
		opword 0x7C150000
		opword 0x4180FF3C
		opword 0xA0070000
		opword 0x540006F7
		opword 0x4182001C
		lis r3, zero_eki_00008cf4@ha
		lfs f0, zero_eki_00008cf4@l(r3)
		opword 0xD01C0174
		opword 0xD01C0178
		opword 0xD01C017C
		opword 0x480000A4
		lis r3, vec3_eki_0000892c@ha
		opword 0xC05C0174
		addi r6, r3, vec3_eki_0000892c@l
		opword 0xC03C0178
		opword 0x80A60000
		opword 0x3861002C
		opword 0x80860004
		opword 0x80060008
		opword 0x90A10008
		opword 0xC01C017C
		opword 0x9081000C
		opword 0x90010010
		opword 0xD0410008
		opword 0xD021000C
		opword 0x80A10008
		opword 0xD0010010
		opword 0x8081000C
		opword 0x80010010
		opword 0x90A1002C
		opword 0x90810030
		opword 0x90010034
		bl PSVECMag
		lis r3, float_2_eki_00008da4@ha
		lfs f0, float_2_eki_00008da4@l(r3)
		opword 0xFC010040
		opword 0x4081003C
		opword 0x3861002C
		opword 0x7C641B78
		bl PSVECNormalize
		lis r3, float_2_eki_00008da4@ha
		opword 0xC001002C
		lfs f1, float_2_eki_00008da4@l(r3)
		opword 0xEC010032
		opword 0xD01C0174
		opword 0xC0010030
		opword 0xEC010032
		opword 0xD01C0178
		opword 0xC0010034
		opword 0xEC010032
		opword 0xD01C017C
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
static void ext_moamoa_dispent(void) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, wp@ha
		opword 0x90010014
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0xA0030000
		opword 0x540007FF
		opword 0x4182004C
		lis r3, zero_eki_00008cf4@ha
		lis r4, ext_disp@ha
		addi r6, r3, zero_eki_00008cf4@l
		opword 0xC0260000
		addi r5, r4, ext_disp@l
		opword 0x38600004
		opword 0x38800001
		opword 0x38C00000
		bl dispEntry
		lis r3, zero_eki_00008cf4@ha
		lis r4, ext_shadow_disp@ha
		addi r6, r3, zero_eki_00008cf4@l
		opword 0xC0260000
		addi r5, r4, ext_shadow_disp@l
		opword 0x38600004
		opword 0x38800002
		opword 0x38C00000
		bl dispEntry
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0xA0030000
		opword 0x540007BD
		opword 0x4182004C
		lis r3, float_neg5000_eki_00008cf8@ha
		lis r4, ext_disp@ha
		addi r6, r3, float_neg5000_eki_00008cf8@l
		opword 0xC0260000
		addi r5, r4, ext_disp@l
		opword 0x38600001
		opword 0x38800001
		opword 0x38C00000
		bl dispEntry
		lis r3, float_neg5000_eki_00008cf8@ha
		lis r4, ext_shadow_disp@ha
		addi r6, r3, float_neg5000_eki_00008cf8@l
		opword 0xC0260000
		addi r5, r4, ext_shadow_disp@l
		opword 0x38600001
		opword 0x38800002
		opword 0x38C00000
		bl dispEntry
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop

#pragma defer_codegen off
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 img_set_color(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0xBF410018
		opword 0x7C7A1B78
		opword 0x83E30018
		opword 0x809F0000
		bl evtGetValue
		opword 0x809F0004
		opword 0x7C7E1B78
		opword 0x7F43D378
		bl evtGetValue
		opword 0x809F0008
		opword 0x547D063E
		opword 0x7F43D378
		bl evtGetValue
		opword 0x809F000C
		opword 0x547C063E
		opword 0x7F43D378
		bl evtGetValue
		opword 0x809F0010
		opword 0x547B063E
		opword 0x7F43D378
		bl evtGetValue
		lis r4, gp@ha
		opword 0x547A063E
		addi r4, r4, gp@l
		opword 0x7FC3F378
		opword 0x80840000
		opword 0x80840014
		opword 0x3004FFFF
		opword 0x7C802110
		bl imgNameToPtr
		opword 0x7C7F1B78
		opword 0x38800040
		opword 0x80630104
		bl animPoseSetMaterialFlagOn
		lis r3, zero_eki_00008ba0@ha
		opword 0x3881000C
		lwz r0, zero_eki_00008ba0@l(r3)
		opword 0x90010008
		opword 0x9BA10008
		opword 0x9B810009
		opword 0x9B61000A
		opword 0x9B41000B
		opword 0x80010008
		opword 0x9001000C
		opword 0x807F0104
		bl animPoseSetMaterialEvtColor
		opword 0xBB410018
		opword 0x38600002
		opword 0x80010034
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop

#pragma defer_codegen reset

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
asm static s32 evt_moamoa_fusion_debug(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r22, 0x8(r1)
	bl extGetPosePtr
	lis r4, wp@ha
	lis r5, eki_00_str_0000004C@ha
	addi r29, r4, wp@l
	mr r24, r3
	lwz r6, 0x0(r29)
	lis r4, eki_00_str_00000040@ha
	addi r30, r5, eki_00_str_0000004C@l
	li r25, 0x0
	lwz r23, 0x8(r6)
	addi r31, r4, eki_00_str_00000040@l
	b L_af_1
L_af_2:
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
	beq L_af_3
	lbz r4, 0x4c(r23)
	lis r3, g5_group_tbl_s588@ha
	addi r0, r3, g5_group_tbl_s588@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r27, 0x0(r3)
	blt L_af_4
	lwz r26, 0x4(r3)
L_af_4:
	cmplwi r4, 0xa
	bne L_af_3
	lis r3, eki_00_str_00000578@ha
	addi r26, r3, eki_00_str_00000578@l
L_af_3:
	li r28, 0x0
	b L_af_5
L_af_6:
	mr r3, r22
	mr r4, r27
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	mr r4, r26
	addi r3, r22, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq L_af_8
L_af_7:
	addi r28, r28, 0x1
	addi r22, r22, 0x28
L_af_5:
	lwz r3, 0x0(r29)
	lwz r0, 0x4c(r3)
	cmpw r28, r0
	blt L_af_6
L_af_8:
	lwz r3, 0x0(r29)
	lwz r0, 0x4c(r3)
	cmpw r28, r0
	bge L_af_9
	lha r0, 0x3c(r23)
	cmpw r0, r28
	beq L_af_9
	lhz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 29, 29
	beq L_af_10
	lis r4, eki_00_str_0000057C@ha
	mr r3, r26
	addi r4, r4, eki_00_str_0000057C@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne L_af_9
L_af_10:
	lhz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 27, 27
	beq L_af_11
	lis r4, eki_00_str_00000580@ha
	mr r3, r26
	addi r4, r4, eki_00_str_00000580@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne L_af_9
L_af_11:
	lis r3, gp@ha
	sth r28, 0x3c(r23)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x44(r23)
	stw r0, 0x40(r23)
L_af_9:
	addi r25, r25, 0x1
	addi r24, r24, 0x20
	addi r23, r23, 0x50
L_af_1:
	lwz r3, 0x0(r29)
	lwz r0, 0x4(r3)
	cmpw r25, r0
	blt L_af_2
	lmw r22, 0x8(r1)
	li r3, 0x2
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

#pragma defer_codegen off
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

#pragma defer_codegen reset

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
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
	lis r4, eki_00_str_0000004C@ha
	addi r29, r3, wp@l
	lis r3, eki_00_str_00000040@ha
	lwz r5, 0x0(r29)
	addi r30, r4, eki_00_str_0000004C@l
	addi r31, r3, eki_00_str_00000040@l
	li r24, 0x0
	lwz r23, 0x8(r5)
	b L_af_1
L_af_2:
	cmpwi r27, 0x0
	beq L_af_3
	cmpwi r28, 0x0
	bne L_af_4
	lbz r0, 0x4c(r23)
	cmplwi r0, 0x1
	bne L_af_5
	lhz r0, 0x0(r23)
	ori r0, r0, 0x800
	sth r0, 0x0(r23)
	b L_af_5
L_af_4:
	lhz r0, 0x0(r23)
	ori r0, r0, 0x800
	sth r0, 0x0(r23)
	b L_af_5
L_af_3:
	cmpwi r28, 0x0
	bne L_af_6
	lbz r0, 0x4c(r23)
	cmplwi r0, 0x1
	beq L_af_5
	lhz r0, 0x0(r23)
	rlwinm r0, r0, 0, 21, 19
	sth r0, 0x0(r23)
	b L_af_5
L_af_6:
	lhz r0, 0x0(r23)
	rlwinm r0, r0, 0, 21, 19
	sth r0, 0x0(r23)
L_af_5:
	lhz r0, 0x0(r23)
	mr r25, r30
	lwz r3, 0x0(r29)
	mr r21, r31
	rlwinm. r0, r0, 0, 20, 20
	addi r22, r3, 0x50
	beq L_af_7
	lbz r4, 0x4c(r23)
	lis r3, g5_group_tbl_s588@ha
	addi r0, r3, g5_group_tbl_s588@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r21, 0x0(r3)
	blt L_af_8
	lwz r25, 0x4(r3)
L_af_8:
	cmplwi r4, 0xa
	bne L_af_7
	lis r3, eki_00_str_00000578@ha
	addi r25, r3, eki_00_str_00000578@l
L_af_7:
	li r26, 0x0
	b L_af_9
L_af_10:
	mr r3, r22
	mr r4, r21
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_11
	mr r4, r25
	addi r3, r22, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq L_af_12
L_af_11:
	addi r26, r26, 0x1
	addi r22, r22, 0x28
L_af_9:
	lwz r3, 0x0(r29)
	lwz r0, 0x4c(r3)
	cmpw r26, r0
	blt L_af_10
L_af_12:
	lwz r3, 0x0(r29)
	lwz r0, 0x4c(r3)
	cmpw r26, r0
	bge L_af_13
	lha r0, 0x3c(r23)
	cmpw r0, r26
	beq L_af_13
	lhz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 29, 29
	beq L_af_14
	lis r4, eki_00_str_0000057C@ha
	mr r3, r25
	addi r4, r4, eki_00_str_0000057C@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne L_af_13
L_af_14:
	lhz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 27, 27
	beq L_af_15
	lis r4, eki_00_str_00000580@ha
	mr r3, r25
	addi r4, r4, eki_00_str_00000580@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne L_af_13
L_af_15:
	lis r3, gp@ha
	sth r26, 0x3c(r23)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x44(r23)
	stw r0, 0x40(r23)
L_af_13:
	addi r24, r24, 0x1
	addi r23, r23, 0x50
L_af_1:
	lwz r3, 0x0(r29)
	lwz r0, 0x4(r3)
	cmpw r24, r0
	blt L_af_2
	lmw r21, 0x14(r1)
	li r3, 0x2
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

#endif
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
#ifdef NONMATCHING
        if (!strncmp(anim, (char*)str_00000664, 1)) {
#endif
#ifndef NONMATCHING
        if (!strncmp(anim, (char*)eki_00_str_00000664, 1)) {
#endif
            wp->defs[wp->numDefs].loop = 0;
        }
        i++;
    } while ((++data)->model != NULL);
    wp->numDefs++;
}
#pragma dont_inline reset
#ifndef NONMATCHING

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
static void moamoa_pose_main(void) {
#ifdef NONMATCHING
    f32 t;
    u64 now;
    s32 i;
    ExtPose* pose;
    Moamoa* moa;
    MoamoaPoseDef* def;
#endif
#ifndef NONMATCHING
	char _af_pad[8];
	asm volatile {
		bl extGetPosePtr
		lis r4, wp@ha
		lis r7, float_60_eki_00008dec@ha
		addi r29, r4, wp@l
		lis r6, float_1000_eki_00008df0@ha
		opword 0x813D0000
		lis r5, float_1_eki_00008d10@ha
		lis r4, double_to_int_eki_00008df8@ha
		lis r8, gp@ha
		opword 0x83090008
		opword 0x7C791B78
		lfs f28, float_60_eki_00008dec@l(r7)
		addi r30, r8, gp@l
		lfs f29, float_1000_eki_00008df0@l(r6)
		opword 0x3B400000
		lfs f30, float_1_eki_00008d10@l(r5)
		opword 0x3FE08000
		lfd f31, double_to_int_eki_00008df8@l(r4)
		opword 0x3EE04330
		opword 0x480000BC
		opword 0x807F00F8
		opword 0x380003E8
		opword 0x809E0000
		opword 0x38A00000
		opword 0x5463F0BE
		opword 0xA8F8003C
		opword 0x7CC30396
		opword 0x8364003C
		opword 0x80180044
		opword 0x83840038
		opword 0x7C80D810
		opword 0x80180040
		opword 0x1CE70028
		opword 0x7C60E110
		addi r22, r7, 0x50
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
		opword 0x93780044
		lis r3, zero_eki_00008cf4@ha
		lfs f1, zero_eki_00008cf4@l(r3)
		opword 0x93980040
		opword 0x80760024
		opword 0x3B5A0001
		stw r23, _af_pad+0(r1)
		opword 0x3B180050
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
		opword 0x80080004
		opword 0x7C1A0000
		opword 0x4180FF3C
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    pose = extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, moa++, pose++) {
        now = gp->renderTime;
        def = &wp->defs[moa->pose];
        t = float_60_eki_00008dec[0] * OSTicksToMilliseconds(now - moa->startTime) / float_1000_eki_00008df0[0] / def->speed;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim) {
	asm volatile {
		opword 0x7C7D1B78
		lis r3, wp@ha
		opword 0x7C9A2378
		addi r3, r3, wp@l
		opword 0x7CBE2B78
		opword 0xA01D0000
		opword 0x80630000
		opword 0x54000529
		opword 0x3B630050
		opword 0x4182003C
		opword 0x881D004C
		lis r3, g5_group_tbl_s588@ha
		addi r3, r3, g5_group_tbl_s588@l
		opword 0x54041D78
		opword 0x28000002
		lwzx r26, r3, r4
		opword 0x4180000C
		opword 0x7C632214
		opword 0x83C30004
		opword 0x2800000A
		opword 0x40820010
		lis r3, eki_00_str_00000578@ha
		addi r0, r3, eki_00_str_00000578@l
		opword 0x7C1E0378
		lis r3, wp@ha
		opword 0x3BE00000
		addi r28, r3, wp@l
		opword 0x48000034
		opword 0x7F63DB78
		opword 0x7F44D378
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x7FC4F378
		opword 0x387B0010
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3BFF0001
		opword 0x3B7B0028
		opword 0x807C0000
		opword 0x8003004C
		opword 0x7C1F0000
		opword 0x4180FFC4
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0x8003004C
		opword 0x7C1F0000
		opword 0x40800080
		opword 0xA81D003C
		opword 0x7C00F800
		opword 0x41820074
		opword 0xA01D0000
		opword 0x5400077B
		opword 0x41820020
		lis r4, eki_00_str_0000057C@ha
		opword 0x7FC3F378
		addi r4, r4, eki_00_str_0000057C@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x4082004C
		opword 0xA01D0000
		opword 0x540006F7
		opword 0x41820020
		lis r4, eki_00_str_00000580@ha
		opword 0x7FC3F378
		addi r4, r4, eki_00_str_00000580@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x40820024
		lis r3, gp@ha
		opword 0xB3FD003C
		addi r3, r3, gp@l
		opword 0x80630000
		opword 0x80030038
		opword 0x8063003C
		opword 0x907D0044
		opword 0x901D0040
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
        if (t >= float_1_eki_00008d10[0]) {
            moa->startTime = now;
            t = zero_eki_00008cf4[0];
        }
        pose->frame = def->start + (s32)((def->count - 1) * t);
    }
}
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
#ifndef NONMATCHING

#endif
static s32 evt_moamoa_exit(EventEntry* event, BOOL isFirstCall) {
    extReset();
    return EVT_RETURN_DONE;
}
#ifndef NONMATCHING

#endif
static s32 evt_moamoa_ry_reset(EventEntry* event, BOOL isFirstCall) {
    s32 i;
    ExtPose* pose = extGetPosePtr();

    for (i = 0; i < wp->count; i++, pose++) {
        pose->field_0x14 = zero_eki_00008cf4[0];
        pose->field_0x1c = zero_eki_00008cf4[0];
    }
    return EVT_RETURN_DONE;
}
#ifndef NONMATCHING

#endif
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
#ifndef NONMATCHING

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
#endif
static s32 evt_moamoa_fusion(EventEntry* event, BOOL isFirstCall) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	asm {
		cmpwi r4, 0x0
	}
	asm volatile {
		opword 0x418200A8
		bl extGetPosePtr
		lis r5, wp@ha
		lis r4, float_1_eki_00008d10@ha
		addi r6, r5, wp@l
		lfs f0, float_1_eki_00008d10@l(r4)
		opword 0x80A60000
		opword 0x80E50008
		opword 0x38A00000
		opword 0x48000074
		opword 0x8083000C
		opword 0x3800000E
		opword 0x2C050064
		opword 0xD0040028
		opword 0x8083000C
		opword 0xD0040014
		opword 0x8083000C
		opword 0xD0040000
		opword 0xB0070024
		opword 0xB0070002
		opword 0x40800018
		opword 0x38800064
		opword 0x7C0523D6
		opword 0x7C0021D6
		opword 0x7C002850
		opword 0x48000018
		opword 0x3880003C
		opword 0x7C0523D6
		opword 0x7C0021D6
		opword 0x7C802850
		opword 0x38040064
		opword 0xB0070004
		opword 0x38A50001
		opword 0x38630020
		opword 0xA0070000
		opword 0x60000100
		opword 0xB0070000
		opword 0x38E70050
		opword 0x80860000
		opword 0x80040004
		opword 0x7C050000
		opword 0x4180FF84
		bl extGetPosePtr
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0x80030004
		opword 0x80630008
		opword 0x7C0903A6
		opword 0x2C000000
		opword 0x40810020
		opword 0xA0030000
		opword 0x540005AD
		opword 0x4082000C
		opword 0x38600000
		opword 0x480001A0
		opword 0x38630050
		opword 0x4200FFE8
		bl extGetPosePtr
		lis r4, wp@ha
		lis r5, eki_00_str_0000004C@ha
		addi r29, r4, wp@l
		opword 0x7C791B78
		opword 0x80DD0000
		lis r4, eki_00_str_00000040@ha
		addi r30, r5, eki_00_str_0000004C@l
		opword 0x3AE00000
		opword 0x83060008
		addi r31, r4, eki_00_str_00000040@l
		opword 0x48000154
		opword 0x80790000
		opword 0x3800003D
		opword 0x7FDAF378
		opword 0x7FFBFB78
		opword 0x60630004
		opword 0x90790000
		opword 0xA0780000
		opword 0x60630400
		opword 0xB0780000
		opword 0xB0180002
		opword 0xA0180000
		opword 0x807D0000
		opword 0x54000529
		addi r22, r3, 0x50
		opword 0x41820038
		opword 0x8898004C
		lis r3, g5_group_tbl_s588@ha
		addi r0, r3, g5_group_tbl_s588@l
		opword 0x54831D78
		opword 0x28040002
		opword 0x7C601A14
		opword 0x83630000
		opword 0x41800008
		opword 0x83430004
		opword 0x2804000A
		opword 0x4082000C
		lis r3, eki_00_str_00000578@ha
		addi r26, r3, eki_00_str_00000578@l
		opword 0x3B800000
		opword 0x48000034
		opword 0x7EC3B378
		opword 0x7F64DB78
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x7F44D378
		opword 0x38760010
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3B9C0001
		opword 0x3AD60028
		opword 0x807D0000
		opword 0x8003004C
		opword 0x7C1C0000
		opword 0x4180FFC4
		opword 0x807D0000
		opword 0x8003004C
		opword 0x7C1C0000
		opword 0x40800080
		opword 0xA818003C
		opword 0x7C00E000
		opword 0x41820074
		opword 0xA0180000
		opword 0x5400077B
		opword 0x41820020
		lis r4, eki_00_str_0000057C@ha
		opword 0x7F43D378
		addi r4, r4, eki_00_str_0000057C@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x4082004C
		opword 0xA0180000
		opword 0x540006F7
		opword 0x41820020
		lis r4, eki_00_str_00000580@ha
		opword 0x7F43D378
		addi r4, r4, eki_00_str_00000580@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x40820024
		lis r3, gp@ha
		opword 0xB398003C
		addi r3, r3, gp@l
		opword 0x80630000
		opword 0x80030038
		opword 0x8063003C
		opword 0x90780044
		opword 0x90180040
		opword 0x3AF70001
		opword 0x3B390020
		opword 0x3B180050
		opword 0x807D0000
		opword 0x80030004
		opword 0x7C170000
		opword 0x4180FEA4
		opword 0x38600002
	}
#endif
}
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
static f32 randf(f32 min, f32 max) {
    f32 r = rand() / float_32767_eki_00008d50[0];

    return r * (max - min) + min;
}
#pragma opt_propagation off
#pragma opt_lifetimes off
__declspec(section ".rodata") static Vec ext_moamoa_t0 = {0.0f, 0.0f, 10.0f};
__declspec(section ".rodata") static Vec ext_moamoa_t1 = {0.0f, 0.0f, 10.0f};
__declspec(section ".rodata") static Vec ext_moamoa_t2 = {0.0f, 0.0f, 10.0f};
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
#pragma opt_propagation reset
#pragma opt_lifetimes reset
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
#pragma dont_inline on
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
#pragma dont_inline reset
#pragma opt_propagation off
#pragma opt_lifetimes off
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
#pragma opt_propagation reset
#pragma opt_lifetimes reset
#pragma opt_propagation off
#pragma opt_lifetimes off
__declspec(section ".rodata") static Vec moamoa_zero_vec = {0.0f, 0.0f, 0.0f};
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
#pragma opt_propagation reset
#pragma opt_lifetimes reset
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
#ifndef NONMATCHING
#pragma pop
#endif


#ifdef NONMATCHING
__declspec(section ".data") static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING(((char*)str_00000170)), 0, LW(0), 0)
    RETURN
EVT_END()
#endif
#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const char eki_00_str_00000040[12] = "c_n_moa_a\0\0";
__declspec(section ".rodata") const char eki_00_str_0000004C[4] = "S_1";
__declspec(section ".rodata") const char eki_00_str_00000050[4] = "D_1";
__declspec(section ".rodata") const char eki_00_str_00000054[12] = "c_n_moa_b\0\0";
__declspec(section ".rodata") const char eki_00_str_00000060[12] = "c_kinodebu\0";
__declspec(section ".rodata") const char eki_00_str_0000006C[4] = "G_1";
__declspec(section ".rodata") const char eki_00_str_00000070[12] = "c_puku_c\0\0\0";
__declspec(section ".rodata") const char eki_00_str_0000007C[4] = "U_1";
__declspec(section ".rodata") const char eki_00_str_00000080[8] = "c_powan";
__declspec(section ".rodata") const char eki_00_str_00000088[4] = "O_1";
__declspec(section ".rodata") const char eki_00_str_0000008C[8] = "c_smoko";
__declspec(section ".rodata") const char eki_00_str_00000094[4] = "T_2";
__declspec(section ".rodata") const char eki_00_str_00000098[8] = "c_rose\0";
__declspec(section ".rodata") const char eki_00_str_000000A0[8] = "c_papab";
__declspec(section ".rodata") const char eki_00_str_000000A8[8] = "c_mamab";
__declspec(section ".rodata") const char eki_00_str_000000B0[12] = "c_konari\0\0\0";
__declspec(section ".rodata") const f32 vec3_eki_00008884[3] = {0.0f, 0.0f, 10.0f};
__declspec(section ".rodata") const f32 vec3_eki_00008890[3] = {0.0f, 0.0f, 10.0f};
__declspec(section ".rodata") const f32 vec3_eki_0000889c[3] = {0.0f, 0.0f, 10.0f};
__declspec(section ".rodata") const f32 vec3_eki_000088a8[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_eki_000088b4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_eki_000088c0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_eki_000088cc[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_eki_000088d8[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_eki_000088e4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_eki_000088f0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_eki_000088fc[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_eki_00008908[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_eki_00008914[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_eki_00008920[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_eki_0000892c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const char eki_00_str_00000170[8] = "e_door\0";
__declspec(section ".rodata") const char eki_00_str_00000178[12] = "s_door_a\0\0\0";
__declspec(section ".rodata") const char eki_00_str_00000184[12] = "s_door_b\0\0\0";
__declspec(section ".rodata") const char eki_00_str_00000190[8] = "e_bero\0";
__declspec(section ".rodata") const char eki_00_str_00000198[8] = "eki_01\0";
__declspec(section ".rodata") const char eki_00_str_000001A0[8] = "w_dero\0";
__declspec(section ".rodata") const char eki_00_str_000001A8[8] = "s_bero\0";
__declspec(section ".rodata") const char eki_00_str_000001B0[8] = "hom_00\0";
__declspec(section ".rodata") const char eki_00_str_000001B8[12] = "n_bero_2\0\0\0";
__declspec(section ".rodata") const char eki_00_str_000001C4[12] = "s_eki_07\0\0\0";
__declspec(section ".rodata") const char eki_00_str_000001D0[12] = "a_eki_07\0\0\0";
__declspec(section ".rodata") const char eki_00_str_000001DC[12] = "s_eki_00\0\0\0";
__declspec(section ".rodata") const char eki_00_str_000001E8[12] = "a_eki_00\0\0\0";
__declspec(section ".rodata") const char eki_00_str_000001F4[8] = "anm_ori";
__declspec(section ".rodata") const char eki_00_str_000001FC[8] = "kaidann";
__declspec(section ".rodata") const char eki_00_str_00000204[4] = "ori";
__declspec(section ".rodata") const char eki_00_str_00000208[12] = "n_kaidan\0\0\0";
__declspec(section ".rodata") const char eki_00_str_00000214[8] = "n_ori\0\0";
__declspec(section ".rodata") const char eki_00_str_0000021C[8] = "n_kabe\0";
__declspec(section ".rodata") const char eki_00_str_00000224[12] = "anm_ere_1\0\0";
__declspec(section ".rodata") const char eki_00_str_00000230[8] = "item\0\0\0";
__declspec(section ".rodata") const char eki_00_str_00000238[8] = "s_lever";
__declspec(section ".rodata") const char eki_00_str_00000240[24] = "SFX_STG6_SWITCH_MOVE1\0\0";
__declspec(section ".rodata") const char eki_00_str_00000258[28] = "SFX_STG6_ORIGAMI_APPEAR1\0\0\0";
__declspec(section ".rodata") const char eki_00_str_00000274[12] = "kaidann_A\0\0";
__declspec(section ".rodata") const char eki_00_str_00000280[12] = "bridge_sw\0\0";
__declspec(section ".rodata") const char eki_00_str_0000028C[28] = "SFX_STG6_OBJ_SWITCH_APPEAR1";
__declspec(section ".rodata") const char eki_00_str_000002A8[8] = "moa_a\0\0";
__declspec(section ".rodata") const char eki_00_str_000002B0[8] = "moa_b\0\0";
__declspec(section ".rodata") const char eki_00_str_000002B8[16] = "stg6_eki_02_0\0\0";
__declspec(section ".rodata") const char eki_00_str_000002C8[8] = "party\0\0";
__declspec(section ".rodata") const char eki_00_str_000002D0[16] = "stg6_eki_02_1\0\0";
__declspec(section ".rodata") const char eki_00_str_000002E0[16] = "stg6_eki_02_2\0\0";
__declspec(section ".rodata") const char eki_00_str_000002F0[16] = "stg6_eki_02_3\0\0";
__declspec(section ".rodata") const char eki_00_str_00000300[16] = "stg6_eki_02_4\0\0";
__declspec(section ".rodata") const char eki_00_str_00000310[16] = "stg6_eki_02_5\0\0";
__declspec(section ".rodata") const char eki_00_str_00000320[16] = "stg6_eki_02_6\0\0";
__declspec(section ".rodata") const char eki_00_str_00000330[24] = "BGM_FF_ENV_SURPRISED1\0\0";
__declspec(section ".rodata") const char eki_00_str_00000348[16] = "BGM_EVT_DANGER4";
__declspec(section ".rodata") const char eki_00_str_00000358[8] = "M_N_2\0\0";
__declspec(section ".rodata") const char eki_00_str_00000360[16] = "stg6_eki_03_0\0\0";
__declspec(section ".rodata") const char eki_00_str_00000370[16] = "stg6_eki_03_1\0\0";
__declspec(section ".rodata") const char eki_00_str_00000380[16] = "stg6_eki_03_2\0\0";
__declspec(section ".rodata") const char eki_00_str_00000390[16] = "stg6_eki_03_3\0\0";
__declspec(section ".rodata") const char eki_00_str_000003A0[16] = "stg6_eki_03_4\0\0";
__declspec(section ".rodata") const char eki_00_str_000003B0[16] = "stg6_eki_03_5\0\0";
__declspec(section ".rodata") const char eki_00_str_000003C0[16] = "stg6_eki_03_6\0\0";
__declspec(section ".rodata") const char eki_00_str_000003D0[8] = "a_lever";
__declspec(section ".rodata") const u32 zero_eki_00008ba0 = 0x00000000;
__declspec(section ".rodata") const char eki_00_str_000003DC[12] = "anm_ere_2\0\0";
__declspec(section ".rodata") const char eki_00_str_000003E8[28] = "SFX_STG6_ELEVATOR_SHAKE1\0\0\0";
__declspec(section ".rodata") const char eki_00_str_00000404[12] = "OFF_hei_07\0";
__declspec(section ".rodata") const char eki_00_str_00000410[12] = "capture_img";
__declspec(section ".rodata") const char eki_00_str_0000041C[12] = "offscreen\0\0";
__declspec(section ".rodata") const char eki_00_str_00000428[4] = "Z_1";
__declspec(section ".rodata") const char eki_00_str_0000042C[4] = "d_1";
__declspec(section ".rodata") const char eki_00_str_00000430[24] = "SFX_STG6_ELEVATOR_OPEN1";
__declspec(section ".rodata") const char eki_00_str_00000448[16] = "anm_ere_door_1\0";
__declspec(section ".rodata") const char eki_00_str_00000458[28] = "SFX_STG6_ELEVATOR_CLOSE1\0\0\0";
__declspec(section ".rodata") const char eki_00_str_00000474[16] = "anm_ere_door_2\0";
__declspec(section ".rodata") const char eki_00_str_00000484[24] = "SFX_STG6_ELEVATOR_MOVE1";
__declspec(section ".rodata") const char eki_00_str_0000049C[24] = "SFX_STG6_ELEVATOR_BELL1";
__declspec(section ".rodata") const char eki_00_str_000004B4[8] = "ere__A\0";
__declspec(section ".rodata") const char eki_00_str_000004BC[24] = "SFX_STG6_ELEVATOR_KEY1\0";
__declspec(section ".rodata") const char eki_00_str_000004D4[12] = "stg6_eki_07";
__declspec(section ".rodata") const char eki_00_str_000004E0[12] = "stg6_eki_06";
__declspec(section ".rodata") const char eki_00_str_000004EC[16] = "stg6_eki_00_01\0";
__declspec(section ".rodata") const char eki_00_str_000004FC[12] = "a_suitti\0\0\0";
__declspec(section ".rodata") const char eki_00_str_00000508[12] = "a_dai_sita\0";
__declspec(section ".rodata") const char eki_00_str_00000514[16] = "ENV_STG6_EKI2\0\0";
__declspec(section ".rodata") const char eki_00_str_00000524[8] = "a_kan\0\0";
__declspec(section ".rodata") const f32 zero_eki_00008cf4[1] = {0.0f};
__declspec(section ".rodata") const f32 float_neg5000_eki_00008cf8 = -5000.0f;
__declspec(section ".rodata") const f32 float_neg1_eki_00008cfc = -1.0f;
__declspec(section ".rodata") const f32 float_6p2832_eki_00008d00[1] = {6.2831855f};
__declspec(section ".rodata") const f32 float_360_eki_00008d04[1] = {360.0f};
__declspec(section ".rodata") const f32 float_0p00761_eki_00008d08 = 0.00761f;
__declspec(section ".rodata") const f32 float_0p16605_eki_00008d0c = 0.16605f;
__declspec(section ".rodata") const f32 float_1_eki_00008d10[1] = {1.0f};
__declspec(section ".rodata") const f32 float_3p1416_eki_00008d14 = 3.1415927f;
__declspec(section ".rodata") const f32 float_1p5708_eki_00008d18 = 1.5707964f;
__declspec(section ".rodata") const f32 float_4p7124_eki_00008d1c = 4.712389f;
__declspec(section ".rodata") const f32 float_0p03705_eki_00008d20 = 0.03705f;
__declspec(section ".rodata") const f32 float_0p4967_eki_00008d24 = 0.4967f;
__declspec(section ".rodata") const char eki_00_str_00000560[24] = "SFX_STG6_MOAMOA_VOICE1\0";
__declspec(section ".rodata") const char eki_00_str_00000578[4] = "S_2";
__declspec(section ".rodata") const char eki_00_str_0000057C[4] = "D\0\0";
__declspec(section ".rodata") const char eki_00_str_00000580[4] = "R\0\0";
__declspec(section ".rodata") const f32 float_0p5_eki_00008d4c = 0.5f;
__declspec(section ".rodata") const f32 float_32767_eki_00008d50[1] = {32767.0f};
__declspec(section ".rodata") const f32 float_0p1_eki_00008d54[1] = {0.1f};
__declspec(section ".rodata") const f32 float_0p03_eki_00008d58 = 0.03f;
__declspec(section ".rodata") const f32 float_50_eki_00008d5c[1] = {50.0f};
__declspec(section ".rodata") const f32 float_15_eki_00008d60 = 15.0f;
__declspec(section ".rodata") const f32 float_1p5_eki_00008d64 = 1.5f;
__declspec(section ".rodata") const f32 float_0p8_eki_00008d68 = 0.8f;
__declspec(section ".rodata") const f32 float_1p2_eki_00008d6c = 1.2f;
__declspec(section ".rodata") const f32 float_100_eki_00008d70[1] = {100.0f};
__declspec(section ".rodata") const f32 float_5_eki_00008d74 = 5.0f;
__declspec(section ".rodata") const f32 float_0p3_eki_00008d78 = 0.3f;
__declspec(section ".rodata") const f32 float_0p2_eki_00008d7c = 0.19999999f;
__declspec(section ".rodata") const f32 float_200_eki_00008d80 = 200.0f;
__declspec(section ".rodata") const f32 float_300_eki_00008d84 = 300.0f;
__declspec(section ".rodata") const f32 float_600_eki_00008d88 = 600.0f;
__declspec(section ".rodata") const f32 float_0p25_eki_00008d8c = 0.25f;
__declspec(section ".rodata") const f32 float_neg45_eki_00008d90 = -45.0f;
__declspec(section ".rodata") const f32 float_90_eki_00008d94[1] = {90.0f};
__declspec(section ".rodata") const f32 float_0p4_eki_00008d98 = 0.4f;
__declspec(section ".rodata") const f32 float_180_eki_00008d9c[1] = {180.0f};
__declspec(section ".rodata") const f32 float_30_eki_00008da0[1] = {30.0f};
__declspec(section ".rodata") const f32 float_2_eki_00008da4 = 2.0f;
__declspec(section ".rodata") const f32 float_0p9_eki_00008da8 = 0.9f;
__declspec(section ".rodata") const f32 float_135_eki_00008dac = 135.0f;
__declspec(section ".rodata") const f32 float_0p2_eki_00008db0 = 0.2f;
__declspec(section ".rodata") const f32 float_0p1_eki_00008db4 = 0.10000001f;
__declspec(section ".rodata") const f32 float_neg100_eki_00008db8 = -100.0f;
__declspec(section ".rodata") const f32 float_0p20944_eki_00008dbc = 0.20943952f;
__declspec(section ".rodata") const f64 double_300_eki_00008dc0 = 300.0;
__declspec(section ".rodata") const f32 float_3_eki_00008dc8 = 3.0f;
__declspec(section ".rodata") const f32 float_225_eki_00008dcc = 225.0f;
__declspec(section ".rodata") const f32 float_1p1_eki_00008dd0 = 1.1f;
__declspec(section ".rodata") const f32 float_1p02_eki_00008dd4 = 1.02f;
__declspec(section ".rodata") const f32 float_neg1000_eki_00008dd8 = -1000.0f;
__declspec(section ".rodata") const f32 float_280_eki_00008ddc = 280.0f;
__declspec(section ".rodata") const f32 float_neg120_eki_00008de0 = -120.0f;
__declspec(section ".rodata") const f32 float_70_eki_00008de4 = 70.0f;
__declspec(section ".rodata") const f32 float_neg70_eki_00008de8 = -70.0f;
__declspec(section ".rodata") const f32 float_60_eki_00008dec[1] = {60.0f};
__declspec(section ".rodata") const f32 float_1000_eki_00008df0[1] = {1000.0f};
__declspec(section ".rodata") const f64 double_to_int_eki_00008df8 = 4503601774854144.0;
__declspec(section ".rodata") const f64 double_to_int_mask_eki_00008e00 = 4503599627370496.0;
__declspec(section ".rodata") const f32 float_20_eki_00008e08[1] = {20.0f};
__declspec(section ".rodata") const f32 float_10_eki_00008e0c[1] = {10.0f};
__declspec(section ".rodata") const f32 float_35_eki_00008e10[1] = {35.0f};
__declspec(section ".rodata") const f32 float_65_eki_00008e14[1] = {65.0f};
__declspec(section ".rodata") const f32 float_40_eki_00008e18[1] = {40.0f};
__declspec(section ".rodata") const f32 float_1E06_eki_00008e1c[1] = {1000000.0f};
__declspec(section ".rodata") const f64 double_30_eki_00008e20 = 30.0;
__declspec(section ".rodata") const char zero_eki_00008e28[1] = { (char)0x00000000 };
__declspec(section ".rodata") const char eki_00_str_00000664[4] = "J\0\0";
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
// jumptables last, as the target emitted them with their functions
__declspec(section ".data") void* eki_00_jumptable_00002400[] = {
    (char*)ext_moamoa_main + 0xCF0,
    (char*)ext_moamoa_main + 0x1770,
    (char*)ext_moamoa_main + 0x1A68,
    (char*)ext_moamoa_main + 0x1CCC,
    (char*)ext_moamoa_main + 0x1F28,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2744,
    (char*)ext_moamoa_main + 0x2810,
    (char*)ext_moamoa_main + 0x2834,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x1F4C,
    (char*)ext_moamoa_main + 0x1F4C,
    (char*)ext_moamoa_main + 0x1F4C,
    (char*)ext_moamoa_main + 0x2250,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x22B0,
    (char*)ext_moamoa_main + 0x2600,
    (char*)ext_moamoa_main + 0x2690,
    (char*)ext_moamoa_main + 0x14D8,
    (char*)ext_moamoa_main + 0x1504,
    (char*)ext_moamoa_main + 0x15CC,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2EF8,
    (char*)ext_moamoa_main + 0x2B54,
    (char*)ext_moamoa_main + 0x2B7C,
    (char*)ext_moamoa_main + 0x2E08,
    (char*)ext_moamoa_main + 0x2E2C,
#endif
};

#ifdef NONMATCHING
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


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
#pragma force_active reset

#endif

#ifdef NONMATCHING // all-C link: pool objects the C names, defined on the asm side only
__declspec(section ".data") const f64 double_30_eki_00008e20 = 30.0;
__declspec(section ".data") const f32 float_0p1_eki_00008d54[1] = {0.1f};
__declspec(section ".data") const f32 float_1000_eki_00008df0[1] = {1000.0f};
__declspec(section ".data") const f32 float_100_eki_00008d70[1] = {100.0f};
__declspec(section ".data") const f32 float_10_eki_00008e0c[1] = {10.0f};
__declspec(section ".data") const f32 float_180_eki_00008d9c[1] = {180.0f};
__declspec(section ".data") const f32 float_1E06_eki_00008e1c[1] = {1000000.0f};
__declspec(section ".data") const f32 float_1_eki_00008d10[1] = {1.0f};
__declspec(section ".data") const f32 float_20_eki_00008e08[1] = {20.0f};
__declspec(section ".data") const f32 float_30_eki_00008da0[1] = {30.0f};
__declspec(section ".data") const f32 float_32767_eki_00008d50[1] = {32767.0f};
__declspec(section ".data") const f32 float_35_eki_00008e10[1] = {35.0f};
__declspec(section ".data") const f32 float_360_eki_00008d04[1] = {360.0f};
__declspec(section ".data") const f32 float_40_eki_00008e18[1] = {40.0f};
__declspec(section ".data") const f32 float_50_eki_00008d5c[1] = {50.0f};
__declspec(section ".data") const f32 float_60_eki_00008dec[1] = {60.0f};
__declspec(section ".data") const f32 float_65_eki_00008e14[1] = {65.0f};
__declspec(section ".data") const f32 float_6p2832_eki_00008d00[1] = {6.2831855f};
__declspec(section ".data") const f32 float_90_eki_00008d94[1] = {90.0f};
__declspec(section ".data") const f32 zero_eki_00008cf4[1] = {0.0f};
__declspec(section ".data") const char zero_eki_00008e28[1] = { (char)0x00000000 };
#endif
