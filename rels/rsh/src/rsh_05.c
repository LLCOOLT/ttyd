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
#ifdef NONMATCHING
#undef EXT_LIT
#define EXT_LIT(sym, val) (val)
#endif
#ifndef NONMATCHING
__declspec(section ".rodata") extern const f32 vec3_rsh_000136d4[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_000136e0[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_000136ec[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_000136f8[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013704[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013710[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_0001371c[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013728[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013734[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013740[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_0001374c[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013758[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013764[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013770[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_0001377c[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013788[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013794[3];
__declspec(section ".rodata") extern const f32 float_0p00761_rsh_00013b30;
__declspec(section ".rodata") extern const f32 float_0p16605_rsh_00013b34;
__declspec(section ".rodata") extern const f32 float_3p1416_rsh_00013b3c;
__declspec(section ".rodata") extern const f32 float_1p5708_rsh_00013b40;
__declspec(section ".rodata") extern const f32 float_4p7124_rsh_00013b44;
__declspec(section ".rodata") extern const f32 float_0p03705_rsh_00013b48;
__declspec(section ".rodata") extern const f32 float_0p4967_rsh_00013b4c;
__declspec(section ".rodata") extern const f64 double_to_int_rsh_00013b50;
__declspec(section ".rodata") extern const f32 float_neg5000_rsh_00013b58;
__declspec(section ".rodata") extern const f32 float_neg1_rsh_00013b5c;
__declspec(section ".rodata") extern const f32 float_1p2_rsh_00013b98;
__declspec(section ".rodata") extern const f32 float_0p2_rsh_00013ba4;
__declspec(section ".rodata") extern const f32 float_neg45_rsh_00013bb4;
__declspec(section ".rodata") extern const f32 float_0p1_rsh_00013bdc;
__declspec(section ".rodata") extern const f32 float_neg100_rsh_00013be0;
__declspec(section ".rodata") extern const f32 float_neg275_rsh_00013be8;
__declspec(section ".rodata") extern const f32 float_neg350_rsh_00013bf4;
__declspec(section ".rodata") extern const f32 float_neg1000_rsh_00013c04;
__declspec(section ".rodata") extern const f32 float_neg290_rsh_00013c0c;
__declspec(section ".rodata") extern const f32 float_neg130_rsh_00013c10;
__declspec(section ".rodata") extern const f64 double_to_int_mask_rsh_00013c18;
__declspec(section ".rodata") extern const f32 float_530_rsh_00013c58;
__declspec(section ".rodata") extern const u32 gap_03_000041CC_rodata;
#define EXT_LIT(sym, val) (sym)
#endif
extern const char zero_rsh_00013c64[];
#ifdef NONMATCHING
extern const char str_000041C8[];
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_000041C8[];
#endif
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
#ifdef NONMATCHING
extern const char str_00003BB8[];
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003BB8[];
#endif
extern const char str_00003BC4[];
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003BC8[];
extern const char rsh_05_str_00003BCC[];
extern const char rsh_05_str_00003BD8[];
extern const char rsh_05_str_00003BE4[];
extern const char rsh_05_str_00003BE8[];
extern const char rsh_05_str_00003BF4[];
extern const char rsh_05_str_00003BF8[];
extern const char rsh_05_str_00003C00[];
extern const char rsh_05_str_00003C04[];
extern const char rsh_05_str_00003C0C[];
extern const char rsh_05_str_00003C10[];
extern const char rsh_05_str_00003C18[];
extern const char rsh_05_str_00003C20[];
extern const char rsh_05_str_00003C28[];
extern const char rsh_05_str_00003D00[];
extern const char rsh_05_str_00003D08[];
extern const char rsh_05_str_00003D10[];
extern const char rsh_05_str_00003D20[];
extern const char rsh_05_str_00003D28[];
extern const char rsh_05_str_00003D44[];
extern const char rsh_05_str_00003D4C[];
extern const char rsh_05_str_00003D54[];
extern const char rsh_05_str_00003D64[];
extern const char rsh_05_str_00003D74[];
#endif
extern const char str_00003D7C[];
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003D8C[];
extern const char rsh_05_str_00003D9C[];
extern const char rsh_05_str_00003DAC[];
extern const char rsh_05_str_00003DBC[];
extern const char rsh_05_str_00003DCC[];
extern const char rsh_05_str_00003DDC[];
extern const char rsh_05_str_00003DEC[];
extern const char rsh_05_str_00003DFC[];
extern const char rsh_05_str_00003E00[];
extern const char rsh_05_str_00003E10[];
extern const char rsh_05_str_00003E20[];
extern const char rsh_05_str_00003E30[];
extern const char rsh_05_str_00003E38[];
extern const char rsh_05_str_00003E3C[];
extern const char rsh_05_str_00003E40[];
#endif
extern const char str_00003E48[];
#ifdef NONMATCHING
extern const char str_00003E5C[];
extern const char str_00003E6C[];
extern const char str_00003E70[];
extern const char str_00003E80[];
extern const char str_00003E94[];
extern const char str_00003EA4[];
extern const char str_00003EAC[];
extern const char str_00003EB8[];
extern const char str_00003EC8[];
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003E5C[];
extern const char rsh_05_str_00003E6C[];
extern const char rsh_05_str_00003E70[];
extern const char rsh_05_str_00003E80[];
extern const char rsh_05_str_00003E94[];
extern const char rsh_05_str_00003EA4[];
extern const char rsh_05_str_00003EAC[];
extern const char rsh_05_str_00003EB8[];
extern const char rsh_05_str_00003EC8[];
#endif
extern const char str_00003ED4[];
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003EE0[];
extern const char rsh_05_str_00003EEC[];
extern const char rsh_05_str_00003EF8[];
extern const char rsh_05_str_00003F08[];
extern const char rsh_05_str_00003F18[];
extern const char rsh_05_str_00003F28[];
extern const char rsh_05_str_00003F38[];
extern const char rsh_05_str_00003F48[];
extern const char rsh_05_str_00003F58[];
extern const char rsh_05_str_00003F64[];
extern const char rsh_05_str_00003F70[];
extern const char rsh_05_str_00003F80[];
#endif
extern const char str_00003F8C[];
#ifdef NONMATCHING
extern const char str_00003F94[];
extern const char str_00003FA4[];
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003F94[];
extern const char rsh_05_str_00003FA4[];
#endif
extern const char str_00003FAC[];
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003FBC[];
extern const char rsh_05_str_00003FC4[];
extern const char rsh_05_str_00003FD4[];
extern const char rsh_05_str_00003FDC[];
extern const char rsh_05_str_00003FEC[];
extern const char rsh_05_str_00003FF0[];
extern const char rsh_05_str_00004000[];
extern const char rsh_05_str_00004008[];
extern const char rsh_05_str_00004010[];
extern const char rsh_05_str_00004020[];
extern const char rsh_05_str_00004030[];
extern const char rsh_05_str_00004040[];
extern const char rsh_05_str_00004050[];
extern const char rsh_05_str_00004060[];
extern const char rsh_05_str_00004068[];
extern const char rsh_05_str_000040C0[];
extern const char rsh_05_str_000041A0[];
extern const char rsh_05_str_000041AC[];
extern const char rsh_05_str_000041B0[];
extern const char rsh_05_str_000041B4[];
extern const char rsh_05_str_000041BC[];
extern const char rsh_05_str_00003BB8[];
#endif
extern const char str_00003BC4[];
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003BC8[];
extern const char rsh_05_str_00003BCC[];
extern const char rsh_05_str_00003BD8[];
extern const char rsh_05_str_00003BE4[];
extern const char rsh_05_str_00003BE8[];
extern const char rsh_05_str_00003BF4[];
extern const char rsh_05_str_00003BF8[];
extern const char rsh_05_str_00003C00[];
extern const char rsh_05_str_00003C04[];
extern const char rsh_05_str_00003C0C[];
extern const char rsh_05_str_00003C10[];
extern const char rsh_05_str_00003C18[];
extern const char rsh_05_str_00003C20[];
extern const char rsh_05_str_00003C28[];
extern const char rsh_05_str_00003D00[];
extern const char rsh_05_str_00003D08[];
extern const char rsh_05_str_00003D10[];
extern const char rsh_05_str_00003D20[];
extern const char rsh_05_str_00003D28[];
extern const char rsh_05_str_00003D44[];
extern const char rsh_05_str_00003D4C[];
extern const char rsh_05_str_00003D54[];
extern const char rsh_05_str_00003D64[];
extern const char rsh_05_str_00003D74[];
#endif
extern const char str_00003D7C[];
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003D8C[];
extern const char rsh_05_str_00003D9C[];
extern const char rsh_05_str_00003DAC[];
extern const char rsh_05_str_00003DBC[];
extern const char rsh_05_str_00003DCC[];
extern const char rsh_05_str_00003DDC[];
extern const char rsh_05_str_00003DEC[];
extern const char rsh_05_str_00003DFC[];
extern const char rsh_05_str_00003E00[];
extern const char rsh_05_str_00003E10[];
extern const char rsh_05_str_00003E20[];
extern const char rsh_05_str_00003E30[];
extern const char rsh_05_str_00003E38[];
extern const char rsh_05_str_00003E3C[];
extern const char rsh_05_str_00003E40[];
#endif
extern const char str_00003E48[];
#ifdef NONMATCHING
extern const char str_00003E5C[];
extern const char str_00003E6C[];
extern const char str_00003E70[];
extern const char str_00003E80[];
extern const char str_00003E94[];
extern const char str_00003EA4[];
extern const char str_00003EAC[];
extern const char str_00003EB8[];
extern const char str_00003EC8[];
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003E5C[];
extern const char rsh_05_str_00003E6C[];
extern const char rsh_05_str_00003E70[];
extern const char rsh_05_str_00003E80[];
extern const char rsh_05_str_00003E94[];
extern const char rsh_05_str_00003EA4[];
extern const char rsh_05_str_00003EAC[];
extern const char rsh_05_str_00003EB8[];
extern const char rsh_05_str_00003EC8[];
#endif
extern const char str_00003ED4[];
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003EE0[];
extern const char rsh_05_str_00003EEC[];
extern const char rsh_05_str_00003EF8[];
extern const char rsh_05_str_00003F08[];
extern const char rsh_05_str_00003F18[];
extern const char rsh_05_str_00003F28[];
extern const char rsh_05_str_00003F38[];
extern const char rsh_05_str_00003F48[];
extern const char rsh_05_str_00003F58[];
extern const char rsh_05_str_00003F64[];
extern const char rsh_05_str_00003F70[];
extern const char rsh_05_str_00003F80[];
#endif
extern const char str_00003F8C[];
#ifdef NONMATCHING
extern const char str_00003F94[];
extern const char str_00003FA4[];
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003F94[];
extern const char rsh_05_str_00003FA4[];
#endif
extern const char str_00003FAC[];
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003FBC[];
extern const char rsh_05_str_00003FC4[];
extern const char rsh_05_str_00003FD4[];
extern const char rsh_05_str_00003FDC[];
extern const char rsh_05_str_00003FEC[];
extern const char rsh_05_str_00003FF0[];
extern const char rsh_05_str_00004000[];
extern const char rsh_05_str_00004008[];
extern const char rsh_05_str_00004010[];
extern const char rsh_05_str_00004020[];
extern const char rsh_05_str_00004030[];
extern const char rsh_05_str_00004040[];
extern const char rsh_05_str_00004050[];
extern const char rsh_05_str_00004060[];
extern const char rsh_05_str_00004068[];
#endif
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)
#pragma force_active on
#pragma force_active reset
#ifdef NONMATCHING
extern const char str_00003BB8[];
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003BB8[];
#endif
extern const char str_00003BC4[];
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003BC8[];
extern const char rsh_05_str_00003BCC[];
extern const char rsh_05_str_00003BD8[];
extern const char rsh_05_str_00003BE4[];
extern const char rsh_05_str_00003BE8[];
extern const char rsh_05_str_00003BF4[];
extern const char rsh_05_str_00003BF8[];
extern const char rsh_05_str_00003C00[];
extern const char rsh_05_str_00003C04[];
extern const char rsh_05_str_00003C0C[];
extern const char rsh_05_str_00003C10[];
extern const char rsh_05_str_00003C18[];
extern const char rsh_05_str_00003C20[];
extern const char rsh_05_str_00003C28[];
extern const char rsh_05_str_00003D00[];
extern const char rsh_05_str_00003D08[];
extern const char rsh_05_str_00003D10[];
extern const char rsh_05_str_00003D20[];
extern const char rsh_05_str_00003D28[];
extern const char rsh_05_str_00003D44[];
extern const char rsh_05_str_00003D4C[];
extern const char rsh_05_str_00003D54[];
extern const char rsh_05_str_00003D64[];
extern const char rsh_05_str_00003D74[];
#endif
extern const char str_00003D7C[];
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003D8C[];
extern const char rsh_05_str_00003D9C[];
extern const char rsh_05_str_00003DAC[];
extern const char rsh_05_str_00003DBC[];
extern const char rsh_05_str_00003DCC[];
extern const char rsh_05_str_00003DDC[];
extern const char rsh_05_str_00003DEC[];
extern const char rsh_05_str_00003DFC[];
extern const char rsh_05_str_00003E00[];
extern const char rsh_05_str_00003E10[];
extern const char rsh_05_str_00003E20[];
extern const char rsh_05_str_00003E30[];
extern const char rsh_05_str_00003E38[];
extern const char rsh_05_str_00003E3C[];
extern const char rsh_05_str_00003E40[];
#endif
extern const char str_00003E48[];
#ifdef NONMATCHING
extern const char str_00003E5C[];
extern const char str_00003E6C[];
extern const char str_00003E70[];
extern const char str_00003E80[];
extern const char str_00003E94[];
extern const char str_00003EA4[];
extern const char str_00003EAC[];
extern const char str_00003EB8[];
extern const char str_00003EC8[];
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003E5C[];
extern const char rsh_05_str_00003E6C[];
extern const char rsh_05_str_00003E70[];
extern const char rsh_05_str_00003E80[];
extern const char rsh_05_str_00003E94[];
extern const char rsh_05_str_00003EA4[];
extern const char rsh_05_str_00003EAC[];
extern const char rsh_05_str_00003EB8[];
extern const char rsh_05_str_00003EC8[];
#endif
extern const char str_00003ED4[];
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003EE0[];
extern const char rsh_05_str_00003EEC[];
extern const char rsh_05_str_00003EF8[];
extern const char rsh_05_str_00003F08[];
extern const char rsh_05_str_00003F18[];
extern const char rsh_05_str_00003F28[];
extern const char rsh_05_str_00003F38[];
extern const char rsh_05_str_00003F48[];
extern const char rsh_05_str_00003F58[];
extern const char rsh_05_str_00003F64[];
extern const char rsh_05_str_00003F70[];
extern const char rsh_05_str_00003F80[];
#endif
extern const char str_00003F8C[];
#ifdef NONMATCHING
extern const char str_00003F94[];
extern const char str_00003FA4[];
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003F94[];
extern const char rsh_05_str_00003FA4[];
#endif
extern const char str_00003FAC[];
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
extern const char rsh_05_str_00003FBC[];
extern const char rsh_05_str_00003FC4[];
extern const char rsh_05_str_00003FD4[];
extern const char rsh_05_str_00003FDC[];
extern const char rsh_05_str_00003FEC[];
extern const char rsh_05_str_00003FF0[];
extern const char rsh_05_str_00004000[];
extern const char rsh_05_str_00004008[];
extern const char rsh_05_str_00004010[];
extern const char rsh_05_str_00004020[];
extern const char rsh_05_str_00004030[];
extern const char rsh_05_str_00004040[];
extern const char rsh_05_str_00004050[];
extern const char rsh_05_str_00004060[];
extern const char rsh_05_str_00004068[];
#endif

typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; f32 field_0x14; f32 field_0x18; f32 field_0x1c; } ExtPose;
typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
typedef struct Moamoa { u16 flags; s16 state; s16 timer; u8 field_0x6[2]; Vec target; f32 vy; s16 jumpTimer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[2]; f32 lastX; f32 lastZ; u8 field_0x30[0x3c - 0x30]; s16 pose; u8 field_0x3e[2]; OSTime startTime; u8 field_0x48[4]; u8 kind; u8 field_0x4d[3]; } Moamoa;
typedef struct MoamoaWork { u16 flags; u8 field_0x2[2]; s32 count; Moamoa* moa; MapObject* mobj; f32 mobjY; Vec target[3]; s16 hitCount; s16 field_0x3a[2]; s16 field_0x3e; s16 field_0x40; s16 idleFrames; EventEntry* escapeEvt; u8 field_0x48[0x4c - 0x48]; s32 numDefs; MoamoaPoseDef defs[32]; f32 angle; f32 dist; s32 bounceCount; f32 breathDir; f32 breathDist; Vec breathPos; u8 field_0x570[0x870 - 0x570]; } MoamoaWork;
typedef struct MoamoaData { const char* model; const char* anim; f32 speed; } MoamoaData;
#ifdef NONMATCHING
static s32 bss_pad;
#endif
#ifndef NONMATCHING
static u8 gap_05_0000004C_bss[4];  // .bss pad after wp
#endif
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
#ifdef NONMATCHING
static inline f32 moa_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
static inline f32 moa_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
static inline f32 moa_sinx(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } return a; }
static inline f32 moa_cosx(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; } return a; }
#endif
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
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
    (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4), 0, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4), 1073741824, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4),
    1082130432, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4), 1086324736, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4), 1090519040, (s32)((char*)rsh_05_str_00003BB8),
    (s32)((char*)str_00003BC4), 1092616192, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4), 1094713344, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4), 1096810496,
    (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4), 1098907648, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4), 1099956224, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4),
    1101004800, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4), 1102053376, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4), 1103101952, (s32)((char*)rsh_05_str_00003BB8),
    (s32)((char*)str_00003BC4), 1104150528, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4), 1105199104, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4), 1106247680,
    (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4), 1107296256, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4), 1107820544, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4),
    1108344832, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)str_00003BC4), 1108869120, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)rsh_05_str_00003BC8), 0, (s32)((char*)rsh_05_str_00003BB8),
    (s32)((char*)rsh_05_str_00003BC8), 1082130432, (s32)((char*)rsh_05_str_00003BB8), (s32)((char*)rsh_05_str_00003BC8), 1090519040, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4), 0,
    (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4), 1073741824, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4), 1082130432, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4),
    1086324736, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4), 1090519040, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4), 1092616192, (s32)((char*)rsh_05_str_00003BCC),
    (s32)((char*)str_00003BC4), 1094713344, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4), 1096810496, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4), 1098907648,
    (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4), 1099956224, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4), 1101004800, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4),
    1102053376, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4), 1103101952, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4), 1104150528, (s32)((char*)rsh_05_str_00003BCC),
    (s32)((char*)str_00003BC4), 1105199104, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4), 1106247680, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4), 1107296256,
    (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4), 1107820544, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4), 1108344832, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)str_00003BC4),
    1108869120, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)rsh_05_str_00003BC8), 0, (s32)((char*)rsh_05_str_00003BCC), (s32)((char*)rsh_05_str_00003BC8), 1082130432, (s32)((char*)rsh_05_str_00003BCC),
    (s32)((char*)rsh_05_str_00003BC8), 1090519040, 0, 0, 0,
#endif
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
#ifdef NONMATCHING
        if (!strncmp(anim, (char*)str_000041C8, 1)) {
#endif
#ifndef NONMATCHING
        if (!strncmp(anim, (char*)rsh_05_str_000041C8, 1)) {
#endif
            wp->defs[wp->numDefs].loop = 0;
        }
        i++;
    } while ((++data)->model != NULL);
    wp->numDefs++;
}

#ifndef NONMATCHING
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
#endif
#ifndef NONMATCHING
	char _af_pad[8];
	asm volatile {
		bl extGetPosePtr
		lis r4, wp@ha
		lis r7, float_60_rsh_00013b18@ha
		addi r29, r4, wp@l
		lis r6, float_1000_rsh_00013b1c@ha
		opword 0x813D0000
		lis r5, float_1_rsh_00013b38@ha
		lis r4, double_to_int_rsh_00013b50@ha
		lis r8, gp@ha
		opword 0x83090008
		opword 0x7C791B78
		lfs f28, float_60_rsh_00013b18@l(r7)
		addi r30, r8, gp@l
		lfs f29, float_1000_rsh_00013b1c@l(r6)
		opword 0x3B400000
		lfs f30, float_1_rsh_00013b38@l(r5)
		opword 0x3FE08000
		lfd f31, double_to_int_rsh_00013b50@l(r4)
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
		lis r3, zero_rsh_00013b20@ha
		lfs f1, zero_rsh_00013b20@l(r3)
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
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif
#pragma dont_inline reset

static const char* group_tbl[][2] = {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
    {((char*)rsh_05_str_00003BB8), ((char*)str_00003BC4)},
    {((char*)rsh_05_str_00003BCC), ((char*)str_00003BC4)},
    {((char*)rsh_05_str_00003BD8), ((char*)rsh_05_str_00003BE4)},
    {((char*)rsh_05_str_00003BE8), ((char*)rsh_05_str_00003BF4)},
    {((char*)rsh_05_str_00003BF8), ((char*)rsh_05_str_00003C00)},
    {((char*)rsh_05_str_00003C04), ((char*)rsh_05_str_00003C0C)},
    {((char*)rsh_05_str_00003C10), ((char*)rsh_05_str_00003BE4)},
    {((char*)rsh_05_str_00003C18), ((char*)rsh_05_str_00003BE4)},
    {((char*)rsh_05_str_00003C20), ((char*)rsh_05_str_00003BE4)},
    {((char*)rsh_05_str_00003C28), ((char*)rsh_05_str_00003BE4)},
    {((char*)rsh_05_str_00003BB8), ((char*)str_00003BC4)},
#endif
};
static inline void /**/ moamoa_pose_change_i(Moamoa* moa, const char* model, const char* anim) {
    MoamoaPoseDef* def = wp->defs;
    s32 i;

    if (moa->flags & 0x800) {
        model = group_tbl[moa->kind][0];
        if (moa->kind >= 2) {
            anim = group_tbl[moa->kind][1];
        }
        if (moa->kind == 10) {
#ifdef NONMATCHING
            anim = (char*)str_000041AC;
#endif
#ifndef NONMATCHING
            anim = (char*)rsh_05_str_000041AC;
#endif
        }
    }
    for (i = 0; i < wp->numDefs; i++, def++) {
        if (!strcmp(def->model, model) && !strcmp(def->anim, anim)) {
            break;
        }
    }
    if (i < wp->numDefs && moa->pose != i) {
        if (moa->flags & 4) {
#ifdef NONMATCHING
            if (strncmp(anim, (char*)str_000041B0, 1)) {
#endif
#ifndef NONMATCHING
            if (strncmp(anim, (char*)rsh_05_str_000041B0, 1)) {
#endif
                return;
            }
        }
        if (moa->flags & 0x10) {
#ifdef NONMATCHING
            if (strncmp(anim, (char*)str_000041B4, 1)) {
#endif
#ifndef NONMATCHING
            if (strncmp(anim, (char*)rsh_05_str_000041B4, 1)) {
#endif
                return;
            }
        }
        moa->pose = i;
        moa->startTime = gp->renderTime;
    }
}

#pragma dont_inline on
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim) {
    MoamoaPoseDef* def = wp->defs;
    s32 i;

    if (moa->flags & 0x800) {
        model = group_tbl[moa->kind][0];
        if (moa->kind >= 2) {
            anim = group_tbl[moa->kind][1];
        }
        if (moa->kind == 10) {
#ifdef NONMATCHING
            anim = (char*)str_000041AC;
#endif
#ifndef NONMATCHING
            anim = (char*)rsh_05_str_000041AC;
#endif
        }
    }
    for (i = 0; i < wp->numDefs; i++, def++) {
        if (!strcmp(def->model, model) && !strcmp(def->anim, anim)) {
            break;
        }
    }
    if (i < wp->numDefs && moa->pose != i) {
        if (moa->flags & 4) {
#ifdef NONMATCHING
            if (strncmp(anim, (char*)str_000041B0, 1)) {
#endif
#ifndef NONMATCHING
            if (strncmp(anim, (char*)rsh_05_str_000041B0, 1)) {
#endif
                return;
            }
        }
        if (moa->flags & 0x10) {
#ifdef NONMATCHING
            if (strncmp(anim, (char*)str_000041B4, 1)) {
#endif
#ifndef NONMATCHING
            if (strncmp(anim, (char*)rsh_05_str_000041B4, 1)) {
#endif
                return;
            }
        }
        moa->pose = i;
        moa->startTime = gp->renderTime;
    }
}
#pragma dont_inline reset

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

static s32 evt_moamoa_exit(EventEntry* event, BOOL isFirstCall) {
    extReset();
    return EVT_RETURN_DONE;
}

static s32 evt_moamoa_ry_reset(EventEntry* event, BOOL isFirstCall) {
    s32 i;
    ExtPose* pose = extGetPosePtr();

    for (i = 0; i < wp->count; i++, pose++) {
        pose->field_0x14 = zero_rsh_00013b20[0];
        pose->field_0x1c = zero_rsh_00013b20[0];
    }
    return EVT_RETURN_DONE;
}

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
#ifdef NONMATCHING
        moamoa_pose_change_i(moa, (char*)str_00003BB8, (char*)str_00003BC4);
#endif
#ifndef NONMATCHING
        moamoa_pose_change_i(moa, (char*)rsh_05_str_00003BB8, (char*)str_00003BC4);
#endif
    }
    return EVT_RETURN_DONE;
}

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
#ifdef NONMATCHING
        moamoa_pose_change_i(moa, (char*)str_00003BB8, (char*)str_00003BC4);
#endif
#ifndef NONMATCHING
        moamoa_pose_change_i(moa, (char*)rsh_05_str_00003BB8, (char*)str_00003BC4);
#endif
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
#ifdef NONMATCHING
        moamoa_pose_change_i(moa, (char*)str_00003BB8, (char*)str_00003BC4);
#endif
#ifndef NONMATCHING
        moamoa_pose_change_i(moa, (char*)rsh_05_str_00003BB8, (char*)str_00003BC4);
#endif
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

int rand(void);

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
static f32 randf(f32 min, f32 max) {
#ifdef NONMATCHING
    f32 r = rand() / float_32767_rsh_00013b7c[0];
#endif
#ifndef NONMATCHING
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
		lis r4, double_to_int_rsh_00013b50@ha
		lis r3, float_32767_rsh_00013b7c@ha
		lfd f3, double_to_int_rsh_00013b50@l(r4)
		opword 0x90010008
		opword 0xEC1FF028
		lfs f1, float_32767_rsh_00013b7c@l(r3)
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

#ifdef NONMATCHING
    return r * (max - min) + min;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
static void ext_moamoa_init(void) {
	char _af_pad[44];
	asm volatile {
		opword 0x38600870
		bl _mapAlloc
		lis r5, wp@ha
		opword 0x38800000
		addi r6, r5, wp@l
		opword 0x38A00870
		opword 0x90660000
		bl memset
		lis r3, rsh_05_str_00003D10@ha
		addi r3, r3, rsh_05_str_00003D10@l
		bl npcNameToPtr
		lis r5, wp@ha
		lis r4, rsh_05_str_00003D20@ha
		addi r6, r5, wp@l
		opword 0x80A3008C
		opword 0x80C60000
		addi r0, r4, rsh_05_str_00003D20@l
		opword 0x80830090
		opword 0x90A60014
		opword 0x90860018
		opword 0x80830094
		opword 0x7C030378
		opword 0x9086001C
		bl npcNameToPtr
		lis r5, wp@ha
		opword 0x80030090
		addi r7, r5, wp@l
		opword 0x80A3008C
		opword 0x80C70000
		lis r4, vec3_rsh_000136d4@ha
		opword 0x90A60020
		opword 0x90060024
		opword 0x80030094
		opword 0x90060028
		lwzu r3, vec3_rsh_000136d4@l(r4)
		opword 0x80A70000
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
		lis r8, zero_rsh_00013b20@ha
		addi r26, r4, wp@l
		lis r12, double_to_int_rsh_00013b50@ha
		opword 0x827A0000
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
		lis r21, rsh_05_str_00003BB8@ha
		lis r4, float_neg1_rsh_00013b5c@ha
		addi r28, r21, rsh_05_str_00003BB8@l
		opword 0x82730008
		lfd f23, double_to_int_rsh_00013b50@l(r12)
		opword 0x7C741B78
		lfs f24, float_32767_rsh_00013b7c@l(r11)
		addi r27, r22, str_00003BC4@l
		lfs f25, float_530_rsh_00013c58@l(r10)
		addi r31, r4, float_neg1_rsh_00013b5c@l
		lfs f26, float_neg290_rsh_00013c0c@l(r9)
		opword 0x3AA00000
		opword 0xC37E0000
		opword 0x3FA04330
		opword 0xC3880000
		opword 0xC3A70000
		opword 0xC3C60000
		opword 0xC3E50000
		opword 0x48000218
		opword 0x38000000
		opword 0x7F76DB78
		opword 0xB0130000
		opword 0x7F97E378
		opword 0xB0130002
		opword 0xB0130004
		opword 0xA0130000
		opword 0x807A0000
		opword 0x54000529
		opword 0x3B030050
		opword 0x41820038
		opword 0x8893004C
		lis r3, group_tbl@ha
		addi r0, r3, group_tbl@l
		opword 0x54831D78
		opword 0x28040002
		opword 0x7C601A14
		opword 0x82E30000
		opword 0x41800008
		opword 0x82C30004
		opword 0x2804000A
		opword 0x4082000C
		lis r3, rsh_05_str_000041AC@ha
		addi r22, r3, rsh_05_str_000041AC@l
		opword 0x3B200000
		opword 0x48000034
		opword 0x7F03C378
		opword 0x7EE4BB78
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x7EC4B378
		opword 0x38780010
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3B390001
		opword 0x3B180028
		opword 0x807A0000
		opword 0x8003004C
		opword 0x7C190000
		opword 0x4180FFC4
		opword 0x807A0000
		opword 0x8003004C
		opword 0x7C190000
		opword 0x40800080
		opword 0xA813003C
		opword 0x7C00C800
		opword 0x41820074
		opword 0xA0130000
		opword 0x5400077B
		opword 0x41820020
		lis r4, rsh_05_str_000041B0@ha
		opword 0x7EC3B378
		addi r4, r4, rsh_05_str_000041B0@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x4082004C
		opword 0xA0130000
		opword 0x540006F7
		opword 0x41820020
		lis r4, rsh_05_str_000041B4@ha
		opword 0x7EC3B378
		addi r4, r4, rsh_05_str_000041B4@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x40820024
		lis r3, gp@ha
		opword 0xB333003C
		addi r3, r3, gp@l
		opword 0x80630000
		opword 0x80030038
		opword 0x8063003C
		opword 0x90730044
		opword 0x90130040
		opword 0x80140000
		opword 0x60000003
		opword 0x90140000
		opword 0x8074000C
		bl PSMTXIdentity
		bl rand
		opword 0x6C608000
		stw r29, _af_pad+32(r1)
		opword 0x8074000C
		opword 0x9001002C
		opword 0xC8010028
		opword 0xEC00B828
		opword 0xEC00C024
		opword 0xEC00D67A
		opword 0xD003000C
		opword 0x8074000C
		opword 0xD363001C
		bl rand
		opword 0x6C608000
		opword 0xC09E0000
		opword 0x90010034
		opword 0x38810020
		opword 0x8174000C
		opword 0xFCC02090
		opword 0x93A10030
		opword 0x38A1001C
		opword 0xC0BF0000
		opword 0x38C10018
		opword 0xC8010030
		opword 0x38E10014
		opword 0x39010010
		opword 0xEC00B828
		opword 0x3921000C
		opword 0x39410008
		opword 0x38600000
		opword 0xEC00C024
		opword 0xEC00EF3A
		opword 0xD00B002C
		opword 0xD3610018
		opword 0xD361001C
		opword 0xD3610020
		opword 0xD3C10014
		opword 0x8174000C
		opword 0xC00B001C
		opword 0xC02B000C
		opword 0xEC5F002A
		opword 0xC06B002C
		bl hitCheckFilter
		opword 0x28030000
		opword 0x41820010
		opword 0xC001001C
		opword 0x8074000C
		opword 0xD003001C
		opword 0x3AB50001
		opword 0x3A940020
		opword 0x3A730050
		opword 0x807A0000
		opword 0x80030004
		opword 0x7C150000
		opword 0x4180FDE0
		lis r3, rsh_05_str_000041BC@ha
		addi r3, r3, rsh_05_str_000041BC@l
		bl mapGetMapObj
		lis r4, wp@ha
		li r19, 0x0
		addi r5, r4, wp@l
		opword 0x80850000
		opword 0x9064000C
		opword 0x80850000
		opword 0x8064000C
		opword 0xC0030098
		opword 0xD0040010
		bl ext_moamoa_main
		opword 0x3A730001
		opword 0x2C130258
		opword 0x4180FFF4
	}
#endif
}
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
#ifndef NONMATCHING
#pragma pop
#endif

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
#ifdef NONMATCHING
        offscreenAddBoundingBox(offscreenNameToId((char*)str_000041A0), left, top, right, bottom);
#endif
#ifndef NONMATCHING
        offscreenAddBoundingBox(offscreenNameToId((char*)rsh_05_str_000041A0), left, top, right, bottom);
#endif
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
#ifdef NONMATCHING
        offscreenAddBoundingBox(offscreenNameToId((char*)str_000041A0), left, top, right, bottom);
#endif
#ifndef NONMATCHING
        offscreenAddBoundingBox(offscreenNameToId((char*)rsh_05_str_000041A0), left, top, right, bottom);
#endif
    }
}

#pragma dont_inline on
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
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
		lis r4, zero_rsh_00013b20@ha
		lis r3, float_100_rsh_00013bc0@ha
		addi r5, r4, zero_rsh_00013b20@l
		lfs f0, float_100_rsh_00013bc0@l(r3)
		opword 0xC0850000
		lis r4, float_1E06_rsh_00013c34@ha
		lfs f7, float_1E06_rsh_00013c34@l(r4)
		lis r3, float_neg1_rsh_00013b5c@ha
		opword 0xFCC02090
		lfs f5, float_neg1_rsh_00013b5c@l(r3)
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
		lis r3, double_30_rsh_00013c38@ha
		opword 0xEC3C0028
		lfd f0, double_30_rsh_00013c38@l(r3)
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x40810014
		lis r3, float_0p1_rsh_00013b80@ha
		lfs f0, float_0p1_rsh_00013b80@l(r3)
		opword 0xEFFF0028
		opword 0xEFDE002A
		opword 0xC381001C
		lis r3, vec3_rsh_000136e0@ha
		addi r4, r3, vec3_rsh_000136e0@l
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
		lis r4, double_to_int_rsh_00013b50@ha
		lis r3, float_0p5_rsh_00013b24@ha
		opword 0xEC1F0024
		addi r6, r4, double_to_int_rsh_00013b50@l
		addi r4, r3, float_0p5_rsh_00013b24@l
		lis r3, float_180_rsh_00013bc4@ha
		opword 0x90A10040
		opword 0x38000003
		opword 0xFC40001E
		lfs f0, float_180_rsh_00013bc4@l(r3)
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
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
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
		lis r4, float_20_rsh_00013c20@ha
		lfs f0, float_20_rsh_00013c20@l(r4)
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
		lis r4, float_20_rsh_00013c20@ha
		lis r3, float_0p5_rsh_00013b24@ha
		opword 0xC05F01B4
		lfs f3, float_20_rsh_00013c20@l(r4)
		lfs f0, float_0p5_rsh_00013b24@l(r3)
		opword 0xEC43102A
		opword 0xEC020032
		opword 0xFC010040
		opword 0x40800088
		opword 0x807D000C
		lis r4, float_10_rsh_00013c24@ha
		lfs f1, float_10_rsh_00013c24@l(r4)
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
		lis r4, float_90_rsh_00013bb8@ha
		opword 0xC03F01A8
		lfs f0, float_90_rsh_00013bb8@l(r4)
		opword 0xC0430114
		opword 0xEC010028
		opword 0xEC20102A
		bl reviseAngle
		lis r3, float_6p2832_rsh_00013b28@ha
		lis r6, float_0p00761_rsh_00013b30@ha
		addi r5, r3, float_6p2832_rsh_00013b28@l
		lis r4, float_360_rsh_00013b2c@ha
		opword 0xC0050000
		lis r5, float_0p16605_rsh_00013b34@ha
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f4, float_0p00761_rsh_00013b30@l(r6)
		opword 0xEC400072
		lfs f0, float_360_rsh_00013b2c@l(r4)
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r4, float_1_rsh_00013b38@ha
		lfs f3, float_0p16605_rsh_00013b34@l(r5)
		opword 0xECC20024
		lfs f2, float_1_rsh_00013b38@l(r4)
		opword 0xFC060840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC060040
		opword 0x40800020
		opword 0xEC260828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC060028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		lis r3, float_3p1416_rsh_00013b3c@ha
		lis r4, float_35_rsh_00013c28@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r5, float_0p03705_rsh_00013b48@ha
		lfs f2, float_35_rsh_00013c28@l(r4)
		lis r4, float_0p4967_rsh_00013b4c@ha
		opword 0xC01F008C
		opword 0xFC060840
		lis r3, float_1_rsh_00013b38@ha
		lfs f5, float_0p03705_rsh_00013b48@l(r5)
		opword 0xEC62013A
		lfs f4, float_0p4967_rsh_00013b4c@l(r4)
		lfs f2, float_1_rsh_00013b38@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC060040
		opword 0x4080001C
		opword 0xEC060828
		opword 0xEC000032
		opword 0xECA52038
		opword 0xECA5103A
		opword 0xFCA02850
		opword 0x48000020
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC060028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xECA52038
		opword 0xECA5103A
		lis r3, float_35_rsh_00013c28@ha
		opword 0x809D000C
		opword 0xC01F0094
		lfs f2, float_35_rsh_00013c28@l(r3)
		opword 0xC024000C
		opword 0xEC82017C
		opword 0xC044002C
		bl distABf
		lis r3, float_35_rsh_00013c28@ha
		lfs f0, float_35_rsh_00013c28@l(r3)
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
		lis r3, vec3_rsh_000136ec@ha
		opword 0x811D000C
		addi r7, r3, vec3_rsh_000136ec@l
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
		lis r3, float_65_rsh_00013c2c@ha
		lfs f0, float_65_rsh_00013c2c@l(r3)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600002
		opword 0x48000700
		lis r4, wp@ha
		lis r3, zero_rsh_00013b20@ha
		addi r4, r4, wp@l
		lfs f0, zero_rsh_00013b20@l(r3)
		opword 0x80840000
		opword 0xC024055C
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082007C
		lis r3, vec3_rsh_000136f8@ha
		opword 0x811D000C
		addi r7, r3, vec3_rsh_000136f8@l
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
		lis r3, float_30_rsh_00013bc8@ha
		lfs f0, float_30_rsh_00013bc8@l(r3)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600003
		opword 0x48000664
		opword 0x38600000
		bl partyGetPtr
		bl nokonokoGetStatus
		opword 0x2C030002
		opword 0x40820084
		lis r3, vec3_rsh_00013704@ha
		opword 0x80FD000C
		addi r6, r3, vec3_rsh_00013704@l
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
		lis r3, float_30_rsh_00013bc8@ha
		lfs f0, float_30_rsh_00013bc8@l(r3)
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
		lis r3, vec3_rsh_00013710@ha
		opword 0x80FD000C
		addi r6, r3, vec3_rsh_00013710@l
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
		lis r3, float_50_rsh_00013b88@ha
		lfs f0, float_50_rsh_00013b88@l(r3)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600004
		opword 0x48000528
		lis r3, vec3_rsh_0001371c@ha
		opword 0x817D000C
		addi r5, r3, vec3_rsh_0001371c@l
		lis r3, vec3_rsh_00013728@ha
		opword 0x80850000
		addi r9, r3, vec3_rsh_00013728@l
		opword 0x80050004
		lis r3, float_20_rsh_00013c20@ha
		opword 0x81450008
		addi r6, r3, float_20_rsh_00013c20@l
		opword 0x90810020
		lis r3, float_0p5_rsh_00013b24@ha
		opword 0xC01F008C
		addi r5, r3, float_0p5_rsh_00013b24@l
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
		lis r3, vec3_rsh_00013734@ha
		opword 0x80BD000C
		addi r7, r3, vec3_rsh_00013734@l
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
		lis r3, float_40_rsh_00013c30@ha
		opword 0xFC200A10
		lfs f0, float_40_rsh_00013c30@l(r3)
		opword 0xFC010040
		opword 0x408001D4
		lis r3, float_6p2832_rsh_00013b28@ha
		lis r6, float_0p00761_rsh_00013b30@ha
		addi r5, r3, float_6p2832_rsh_00013b28@l
		opword 0xC01F01A0
		opword 0xC0250000
		lis r5, float_0p16605_rsh_00013b34@ha
		lis r4, float_360_rsh_00013b2c@ha
		lis r3, float_3p1416_rsh_00013b3c@ha
		opword 0xEC410032
		lfs f0, float_360_rsh_00013b2c@l(r4)
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r4, float_1_rsh_00013b38@ha
		lfs f4, float_0p00761_rsh_00013b30@l(r6)
		opword 0xECA20024
		lfs f3, float_0p16605_rsh_00013b34@l(r5)
		lfs f2, float_1_rsh_00013b38@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xECA50828
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xECA10028
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0xFC802050
		opword 0xECDFE828
		lis r3, float_6p2832_rsh_00013b28@ha
		addi r8, r3, float_6p2832_rsh_00013b28@l
		lis r6, float_0p03705_rsh_00013b48@ha
		lis r3, float_360_rsh_00013b2c@ha
		opword 0xC0680000
		opword 0xEC060132
		addi r7, r3, float_360_rsh_00013b2c@l
		lis r5, float_0p4967_rsh_00013b4c@ha
		lis r3, float_3p1416_rsh_00013b3c@ha
		lis r4, float_1_rsh_00013b38@ha
		lfs f5, float_0p03705_rsh_00013b48@l(r6)
		opword 0xFC200050
		opword 0xC0070000
		lfs f4, float_0p4967_rsh_00013b4c@l(r5)
		opword 0xD03F0174
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		opword 0xC05F01A0
		opword 0xEC4300B2
		lfs f3, float_1_rsh_00013b38@l(r4)
		opword 0xEC420024
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC020040
		opword 0x4080001C
		opword 0xEC420828
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xFCA02850
		opword 0x48000020
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC020028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC410028
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xEC060172
		opword 0xD01F017C
		opword 0x480001C0
		lis r3, float_6p2832_rsh_00013b28@ha
		lis r6, float_0p00761_rsh_00013b30@ha
		addi r5, r3, float_6p2832_rsh_00013b28@l
		lis r4, float_360_rsh_00013b2c@ha
		opword 0xC0050000
		lis r3, float_3p1416_rsh_00013b3c@ha
		lis r5, float_0p16605_rsh_00013b34@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		opword 0xEC4007B2
		lfs f0, float_360_rsh_00013b2c@l(r4)
		lis r4, float_1_rsh_00013b38@ha
		lfs f4, float_0p00761_rsh_00013b30@l(r6)
		lfs f3, float_0p16605_rsh_00013b34@l(r5)
		opword 0xECA20024
		lfs f2, float_1_rsh_00013b38@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x809D000C
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r5, float_0p03705_rsh_00013b48@ha
		opword 0xC004000C
		lis r4, float_0p4967_rsh_00013b4c@ha
		opword 0xFC050840
		lis r3, float_1_rsh_00013b38@ha
		opword 0xEC5F013C
		opword 0xC01F008C
		lfs f4, float_0p03705_rsh_00013b48@l(r5)
		lfs f3, float_0p4967_rsh_00013b4c@l(r4)
		opword 0xEC020028
		lfs f2, float_1_rsh_00013b38@l(r3)
		opword 0xD01F0174
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

#pragma dont_inline reset

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING
__declspec(section ".rodata") static Vec moamoa_zero_vec = {0.0f, 0.0f, 0.0f};
#endif
#ifndef NONMATCHING
extern void* rsh_05_jumptable_00014F3C[];
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
static void ext_moamoa_main(void) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	char _af_pad[168];
	asm volatile {
		bl marioGetPtr
		opword 0x7C7E1B78
		opword 0x38600000
		bl partyGetPtr
		opword 0x7C771B78
		opword 0x38600004
		bl camGetPtr
		opword 0xA01E002E
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
		opword 0xA01E002E
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
		lis r4, float_neg1_rsh_00013b5c@ha
		lis r3, wp@ha
		addi r5, r4, float_neg1_rsh_00013b5c@l
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
		lis r4, float_6p2832_rsh_00013b28@ha
		addi r10, r3, wp@l
		lis r7, float_0p00761_rsh_00013b30@ha
		opword 0x80AA0000
		lis r3, float_360_rsh_00013b2c@ha
		addi r8, r3, float_360_rsh_00013b2c@l
		addi r9, r4, float_6p2832_rsh_00013b28@l
		opword 0xD0250560
		lis r3, float_3p1416_rsh_00013b3c@ha
		addi r4, r3, float_3p1416_rsh_00013b3c@l
		lis r6, float_0p16605_rsh_00013b34@ha
		opword 0x806A0000
		lis r5, float_1_rsh_00013b38@ha
		opword 0xC0490000
		opword 0xC023055C
		opword 0xC0080000
		opword 0xEC420072
		opword 0xC0240000
		lfs f4, float_0p00761_rsh_00013b30@l(r7)
		lfs f3, float_0p16605_rsh_00013b34@l(r6)
		opword 0xECA20024
		lfs f2, float_1_rsh_00013b38@l(r5)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r4, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r4)
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
		lis r4, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r4)
		opword 0xFC050040
		opword 0x40800020
		opword 0xECA50828
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0xFC802050
		opword 0x48000028
		lis r4, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r4)
		opword 0xECA10028
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0xFC802050
		opword 0xC0230560
		lis r9, wp@ha
		opword 0xC0170058
		lis r4, float_6p2832_rsh_00013b28@ha
		addi r8, r4, float_6p2832_rsh_00013b28@l
		lis r6, float_0p03705_rsh_00013b48@ha
		opword 0xEC01013A
		lis r4, float_360_rsh_00013b2c@ha
		addi r7, r4, float_360_rsh_00013b2c@l
		lis r5, float_0p4967_rsh_00013b4c@ha
		lis r4, float_3p1416_rsh_00013b3c@ha
		addi r10, r9, wp@l
		opword 0xD0030564
		lis r3, float_1_rsh_00013b38@ha
		opword 0xC0680000
		opword 0xC017005C
		opword 0x812A0000
		lfs f1, float_3p1416_rsh_00013b3c@l(r4)
		opword 0xD0090568
		opword 0xC0070000
		opword 0x80EA0000
		lfs f5, float_0p03705_rsh_00013b48@l(r6)
		opword 0xC047055C
		lfs f4, float_0p4967_rsh_00013b4c@l(r5)
		opword 0xEC4300B2
		lfs f3, float_1_rsh_00013b38@l(r3)
		opword 0xEC420024
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC020040
		opword 0x4080001C
		opword 0xEC420828
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xFCA02850
		opword 0x48000020
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC020028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC410028
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xC0270560
		opword 0xC0170060
		opword 0xEC01017C
		opword 0xD007056C
		lis r3, wp@ha
		addi r4, r3, wp@l
		opword 0x80A40000
		opword 0xA805003A
		opword 0x2C000032
		opword 0x40810048
		opword 0x80650020
		opword 0x80050024
		opword 0x90650014
		opword 0x90050018
		opword 0x80050028
		opword 0x9005001C
		opword 0x80840000
		opword 0xA0640000
		opword 0x546004E7
		opword 0x40820020
		opword 0x60601000
		lis r3, evt_moamoa_escape0@ha
		opword 0xB0040000
		addi r3, r3, evt_moamoa_escape0@l
		opword 0x38800000
		opword 0x38A00000
		bl evtEntry
		lis r3, wp@ha
		addi r4, r3, wp@l
		opword 0x80A40000
		opword 0xA805003C
		opword 0x2C000032
		opword 0x40810048
		opword 0x80650014
		opword 0x80050018
		opword 0x90650020
		opword 0x90050024
		opword 0x8005001C
		opword 0x90050028
		opword 0x80840000
		opword 0xA0640000
		opword 0x546004A5
		opword 0x40820020
		opword 0x60602000
		lis r3, evt_moamoa_escape1@ha
		opword 0xB0040000
		addi r3, r3, evt_moamoa_escape1@l
		opword 0x38800000
		opword 0x38A00000
		bl evtEntry
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0xA0630000
		opword 0x546004E7
		opword 0x418200A0
		opword 0x546004A5
		opword 0x41820098
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
		lis r4, rsh_05_str_000040C0@ha
		addi r31, r5, wp@l
		opword 0x7C7C1B78
		opword 0x80BF0000
		addi r29, r4, rsh_05_str_000040C0@l
		opword 0x3B000000
		opword 0x3B400000
		opword 0x83650008
		opword 0x48002BDC
		opword 0x807C000C
		opword 0xC03E008C
		opword 0xC05E0094
		opword 0xC063000C
		opword 0xC083002C
		bl angleABf
		opword 0x807F0000
		opword 0xD0230550
		opword 0x807C000C
		opword 0xC03E008C
		opword 0xC05E0094
		opword 0xC063000C
		opword 0xC083002C
		bl distABf
		opword 0x807F0000
		opword 0xD0230554
		opword 0x807F0000
		opword 0xA0630000
		opword 0x546007FF
		opword 0x418204E8
		opword 0x5460077B
		opword 0x408204E0
		bl marioKeyOffChk
		opword 0x2C030000
		opword 0x408204D4
		bl marioCtrlOffChk
		opword 0x2C030000
		opword 0x408204C8
		opword 0x2C190000
		opword 0x408204C0
		opword 0xA01B0000
		opword 0x70000154
		opword 0x408204B4
		opword 0x7F83E378
		opword 0x7F64DB78
		bl moamoa_hit_check
		opword 0x7C771B78
		opword 0x2C170001
		opword 0x408200B0
		opword 0x38600003
		opword 0xA0BB0000
		opword 0x7C1A1BD6
		opword 0x38C00024
		opword 0x60A50004
		opword 0xB0BB0000
		lis r4, wp@ha
		opword 0xB0DB0002
		addi r5, r4, wp@l
		opword 0x7C0019D6
		opword 0x80850000
		opword 0xA8640038
		opword 0x7EE0D050
		opword 0x38030001
		opword 0xB0040038
		opword 0x1C17000C
		opword 0x809C000C
		opword 0x80650000
		opword 0xC024000C
		opword 0x7C630214
		opword 0xC044002C
		opword 0xC0630014
		opword 0xC083001C
		bl distABf
		lis r3, float_200_rsh_00013b78@ha
		lfs f0, float_200_rsh_00013b78@l(r3)
		opword 0xFC010040
		opword 0x40800020
		lis r4, wp@ha
		opword 0x56E3083C
		lwz r5, wp@l(r4)
		opword 0x3883003A
		opword 0x7C6522AE
		opword 0x38030001
		opword 0x7C05232E
		lis r3, rsh_05_str_00003BB8@ha
		lis r5, rsh_05_str_00003BC8@ha
		addi r4, r3, rsh_05_str_00003BB8@l
		opword 0x7F63DB78
		addi r5, r5, rsh_05_str_00003BC8@l
		bl moamoa_pose_change
		opword 0x3B200001
		opword 0x480003F0
		opword 0x2C170002
		opword 0x4182000C
		opword 0x2C170004
		opword 0x408200B8
		opword 0x38600003
		opword 0xA0BB0000
		opword 0x7C1A1BD6
		opword 0x38C0002F
		opword 0x60A5000C
		opword 0xB0BB0000
		lis r4, wp@ha
		opword 0xB0DB0002
		addi r5, r4, wp@l
		opword 0x7C0019D6
		opword 0x80850000
		opword 0xA8640038
		subf r22, r0, r26
		opword 0x38030001
		opword 0xB0040038
		opword 0x1C16000C
		opword 0x809C000C
		opword 0x80650000
		opword 0xC024000C
		opword 0x7C630214
		opword 0xC044002C
		opword 0xC0630014
		opword 0xC083001C
		bl distABf
		lis r3, float_200_rsh_00013b78@ha
		lfs f0, float_200_rsh_00013b78@l(r3)
		opword 0xFC010040
		opword 0x40800020
		lis r4, wp@ha
		opword 0x56C3083C
		lwz r5, wp@l(r4)
		opword 0x3883003A
		opword 0x7C6522AE
		opword 0x38030001
		opword 0x7C05232E
		lis r3, rsh_05_str_00003BB8@ha
		lis r5, rsh_05_str_00003BC8@ha
		addi r4, r3, rsh_05_str_00003BB8@l
		opword 0x7F63DB78
		addi r5, r5, rsh_05_str_00003BC8@l
		bl moamoa_pose_change
		opword 0x2C170004
		opword 0x41820334
		opword 0x3B200001
		opword 0x4800032C
		opword 0x2C170003
		opword 0x40820324
		lis r3, wp@ha
		opword 0xA01B0000
		addi r4, r3, wp@l
		opword 0x80E40000
		opword 0x60050084
		lis r4, float_0p5_rsh_00013b24@ha
		opword 0x38000030
		opword 0xC047055C
		addi r6, r4, float_0p5_rsh_00013b24@l
		opword 0xC0270550
		lis r3, vec3_rsh_00013740@ha
		addi r4, r3, vec3_rsh_00013740@l
		opword 0xC0060000
		opword 0xB0BB0000
		opword 0xEC22082A
		opword 0xB01B0002
		fmuls f27, f1, f0
		opword 0x80640000
		opword 0x80040004
		opword 0x907B0008
		opword 0x901B000C
		opword 0x80040008
		opword 0x901B0010
		bl rand
		opword 0x6C648000
		opword 0x3C004330
		lis r3, float_6p2832_rsh_00013b28@ha
		stw r4, _af_pad+164(r1)
		lfs f0, float_6p2832_rsh_00013b28@l(r3)
		lis r5, double_to_int_rsh_00013b50@ha
		opword 0x900100A8
		lis r3, float_360_rsh_00013b2c@ha
		lfd f3, double_to_int_rsh_00013b50@l(r5)
		opword 0xEC2006F2
		lfs f0, float_360_rsh_00013b2c@l(r3)
		lis r4, float_32767_rsh_00013b7c@ha
		opword 0xC84100A8
		lis r5, float_0p00761_rsh_00013b30@ha
		opword 0xEFC10024
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f5, float_0p00761_rsh_00013b30@l(r5)
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r3, float_1_rsh_00013b38@ha
		opword 0xEC621828
		lfs f2, float_32767_rsh_00013b7c@l(r4)
		lis r4, float_0p1_rsh_00013b80@ha
		addi r6, r4, float_0p1_rsh_00013b80@l
		opword 0xFC1E0840
		opword 0xEC431024
		opword 0xC0060000
		lis r4, float_0p16605_rsh_00013b34@ha
		lfs f4, float_0p16605_rsh_00013b34@l(r4)
		lfs f3, float_1_rsh_00013b38@l(r3)
		opword 0xEFE2003A
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC1E0040
		opword 0x40800020
		opword 0xEC3E0828
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC1E0028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0xEC1F0172
		opword 0xD01B0014
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_rsh_00013b50@ha
		opword 0x906100AC
		addi r5, r4, double_to_int_rsh_00013b50@l
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100A8
		addi r4, r3, float_32767_rsh_00013b7c@l
		opword 0xC8450000
		lis r3, float_0p03_rsh_00013b84@ha
		opword 0xC82100A8
		addi r6, r3, float_0p03_rsh_00013b84@l
		opword 0xC0040000
		lis r5, float_0p03705_rsh_00013b48@ha
		opword 0xEC411028
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r4, float_0p4967_rsh_00013b4c@ha
		lis r3, float_1_rsh_00013b38@ha
		lfs f4, float_0p03705_rsh_00013b48@l(r5)
		opword 0xEC420024
		opword 0xC0060000
		lfs f3, float_0p4967_rsh_00013b4c@l(r4)
		opword 0xEC02003A
		lfs f2, float_1_rsh_00013b38@l(r3)
		opword 0xFC1E0840
		opword 0xD01B001C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC1E0040
		opword 0x4080001C
		opword 0xEC1E0828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC1E0028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x38600003
		opword 0xFC002050
		opword 0x7C1A1BD6
		lis r4, wp@ha
		opword 0x38C00078
		opword 0xEC1F0032
		addi r5, r4, wp@l
		opword 0xD01B0020
		opword 0xB0DB0018
		opword 0x7C0019D6
		opword 0x80850000
		opword 0xA8640038
		opword 0x7EC0D050
		opword 0x38030001
		opword 0xB0040038
		opword 0x1C16000C
		opword 0x809C000C
		opword 0x80650000
		opword 0xC024000C
		opword 0x7C630214
		opword 0xC044002C
		opword 0xC0630014
		opword 0xC083001C
		bl distABf
		lis r3, float_200_rsh_00013b78@ha
		lfs f0, float_200_rsh_00013b78@l(r3)
		opword 0xFC010040
		opword 0x40800020
		lis r4, wp@ha
		opword 0x56C3083C
		lwz r5, wp@l(r4)
		opword 0x3883003A
		opword 0x7C6522AE
		opword 0x38030001
		opword 0x7C05232E
		lis r3, rsh_05_str_00003BB8@ha
		lis r5, rsh_05_str_00003BC8@ha
		addi r4, r3, rsh_05_str_00003BB8@l
		opword 0x7F63DB78
		addi r5, r5, rsh_05_str_00003BC8@l
		bl moamoa_pose_change
		opword 0x3B200001
		opword 0x809F0000
		opword 0xA0040000
		opword 0x540007FF
		opword 0x41820040
		opword 0xA0BB0000
		opword 0x70A00155
		opword 0x40820034
		lis r3, float_50_rsh_00013b88@ha
		opword 0xC0240554
		lfs f0, float_50_rsh_00013b88@l(r3)
		opword 0xFC010040
		opword 0x40800020
		opword 0x54A007BD
		opword 0x41820010
		opword 0x38000001
		opword 0xB01B0024
		opword 0x4800000C
		opword 0x38000001
		opword 0xB01B0002
		opword 0x807F0000
		opword 0xA0030000
		opword 0x540007FF
		opword 0x418200A8
		opword 0xA01B0000
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
		opword 0x7C1A0040
		opword 0x40820074
		opword 0x386003E8
		bl irand
		opword 0x2C0300C8
		opword 0x40800064
		lis r3, vec3_rsh_0001374c@ha
		opword 0x80BC000C
		addi r8, r3, vec3_rsh_0001374c@l
		opword 0x7FA3EB78
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
		opword 0xA81B0002
		opword 0x28000041
		opword 0x418124D8
		lis r3, rsh_05_jumptable_00014F3C@ha
		opword 0x5400103A
		addi r3, r3, rsh_05_jumptable_00014F3C@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x38600085
		opword 0x7C1A1BD6
		opword 0x7C0019D6
		opword 0x7C00D050
		opword 0x2C000064
		opword 0x408004B4
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f1, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_00013b7c@l
		opword 0xC0450000
		lis r4, float_6p2832_rsh_00013b28@ha
		opword 0xC80100A8
		lis r3, zero_rsh_00013b20@ha
		opword 0xEC600828
		lfs f1, float_6p2832_rsh_00013b28@l(r4)
		lfs f0, zero_rsh_00013b20@l(r3)
		opword 0xEC431024
		opword 0xEFE2007A
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_rsh_00013b50@ha
		opword 0x906100B4
		addi r5, r4, double_to_int_rsh_00013b50@l
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100B0
		addi r4, r3, float_32767_rsh_00013b7c@l
		opword 0xC8450000
		lis r5, float_50_rsh_00013b88@ha
		opword 0xC82100B0
		addi r7, r5, float_50_rsh_00013b88@l
		opword 0xC0040000
		lis r4, zero_rsh_00013b20@ha
		opword 0xEC411028
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		addi r6, r4, zero_rsh_00013b20@l
		lis r5, float_0p00761_rsh_00013b30@ha
		lis r4, float_0p16605_rsh_00013b34@ha
		opword 0xEC620024
		opword 0xC0470000
		opword 0xC0060000
		lis r3, float_1_rsh_00013b38@ha
		lfs f4, float_0p00761_rsh_00013b30@l(r5)
		opword 0xECE300BA
		opword 0xFC1F0840
		lfs f3, float_0p16605_rsh_00013b34@l(r4)
		lfs f2, float_1_rsh_00013b38@l(r3)
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC1F0040
		opword 0x40800020
		opword 0xEC3F0828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC1F0028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x38800003
		lis r5, wp@ha
		opword 0x7C1A23D6
		lwz r6, wp@l(r5)
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r5, float_0p03705_rsh_00013b48@ha
		lis r3, float_1_rsh_00013b38@ha
		opword 0x7C0021D6
		lis r4, float_0p4967_rsh_00013b4c@ha
		lfs f5, float_0p4967_rsh_00013b4c@l(r4)
		opword 0xFC1F0840
		lfs f6, float_0p03705_rsh_00013b48@l(r5)
		lfs f2, float_1_rsh_00013b38@l(r3)
		opword 0x7C00D050
		opword 0x1C00000C
		opword 0x7C860214
		opword 0xC0040014
		opword 0xEC67013A
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC1F0040
		opword 0x4080001C
		opword 0xEC1F0828
		opword 0xEC000032
		opword 0xECC62838
		opword 0xECC6103A
		opword 0xFCC03050
		opword 0x48000020
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC1F0028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xECC62838
		opword 0xECC6103A
		opword 0xC004001C
		opword 0x807C000C
		opword 0xEC8701BC
		opword 0xC023000C
		opword 0xC043002C
		bl angleABf
		lis r3, float_6p2832_rsh_00013b28@ha
		lis r6, float_0p00761_rsh_00013b30@ha
		addi r5, r3, float_6p2832_rsh_00013b28@l
		lis r4, float_360_rsh_00013b2c@ha
		opword 0xC0050000
		lis r5, float_0p16605_rsh_00013b34@ha
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f4, float_0p00761_rsh_00013b30@l(r6)
		opword 0xEC400072
		lfs f0, float_360_rsh_00013b2c@l(r4)
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r4, float_1_rsh_00013b38@ha
		lfs f3, float_0p16605_rsh_00013b34@l(r5)
		opword 0xECA20024
		lfs f2, float_1_rsh_00013b38@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x80DC000C
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r4, float_15_rsh_00013b8c@ha
		lfs f2, float_15_rsh_00013b8c@l(r4)
		lis r4, float_0p4967_rsh_00013b4c@ha
		opword 0xC006000C
		opword 0xFC050840
		lis r5, float_0p03705_rsh_00013b48@ha
		lis r3, float_1_rsh_00013b38@ha
		opword 0xEF82013A
		opword 0xC3A6001C
		lfs f4, float_0p03705_rsh_00013b48@l(r5)
		lfs f3, float_0p4967_rsh_00013b4c@l(r4)
		lfs f2, float_1_rsh_00013b38@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_15_rsh_00013b8c@ha
		opword 0xC006002C
		lfs f1, float_15_rsh_00013b8c@l(r3)
		opword 0xEF61013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_rsh_00013b50@ha
		lis r3, float_32767_rsh_00013b7c@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		opword 0x900100B0
		lfs f0, float_32767_rsh_00013b7c@l(r3)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEFC10024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100A8
		lis r5, float_1p5_rsh_00013b90@ha
		lfs f4, float_1p5_rsh_00013b90@l(r5)
		lis r4, float_1p2_rsh_00013b98@ha
		opword 0xC82100A8
		opword 0xFC60D890
		lfs f0, float_32767_rsh_00013b7c@l(r3)
		lis r3, float_0p8_rsh_00013b94@ha
		opword 0xEC411028
		lfs f5, float_1p2_rsh_00013b98@l(r4)
		opword 0xFC20E090
		opword 0xEC9E213A
		opword 0xA8BB0002
		opword 0xECC20024
		lfs f0, float_0p8_rsh_00013b94@l(r3)
		opword 0x7F83E378
		opword 0x7F64DB78
		opword 0x38C00001
		opword 0xFC40E890
		opword 0xECA6017A
		bl moamoa_jump
		opword 0xA01B0000
		opword 0x60000001
		opword 0xB01B0000
		opword 0x48001FF8
		opword 0x38600003
		opword 0x80BC000C
		opword 0x7C1A1BD6
		lis r4, wp@ha
		opword 0xC025000C
		addi r4, r4, wp@l
		opword 0xC045002C
		opword 0x80840000
		opword 0x7C0019D6
		opword 0x7C00D050
		opword 0x1EC0000C
		opword 0x7C64B214
		opword 0xC0630014
		opword 0xC083001C
		bl distABf
		lis r3, wp@ha
		opword 0x809C000C
		lwz r0, wp@l(r3)
		opword 0xFF800890
		opword 0xC024000C
		opword 0x7C60B214
		opword 0xC044002C
		opword 0xC0630014
		opword 0xC083001C
		bl angleABf
		lis r3, float_200_rsh_00013b78@ha
		lfs f0, float_200_rsh_00013b78@l(r3)
		opword 0xFC1C0040
		opword 0x4080004C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f1, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100B0
		addi r5, r3, float_32767_rsh_00013b7c@l
		opword 0xC0450000
		lis r4, float_360_rsh_00013b2c@ha
		opword 0xC80100B0
		lis r3, zero_rsh_00013b20@ha
		opword 0xEC600828
		lfs f1, float_360_rsh_00013b2c@l(r4)
		lfs f0, zero_rsh_00013b20@l(r3)
		opword 0xEC431024
		opword 0xEC22007A
		lis r3, float_6p2832_rsh_00013b28@ha
		lis r6, float_0p00761_rsh_00013b30@ha
		addi r5, r3, float_6p2832_rsh_00013b28@l
		lis r4, float_360_rsh_00013b2c@ha
		opword 0xC0050000
		lis r5, float_0p16605_rsh_00013b34@ha
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f4, float_0p00761_rsh_00013b30@l(r6)
		opword 0xEC400072
		lfs f0, float_360_rsh_00013b2c@l(r4)
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r4, float_1_rsh_00013b38@ha
		lfs f3, float_0p16605_rsh_00013b34@l(r5)
		opword 0xECA20024
		lfs f2, float_1_rsh_00013b38@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x80DC000C
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r4, float_5_rsh_00013b9c@ha
		lfs f2, float_5_rsh_00013b9c@l(r4)
		lis r4, float_0p4967_rsh_00013b4c@ha
		opword 0xC006000C
		opword 0xFC050840
		lis r5, float_0p03705_rsh_00013b48@ha
		lis r3, float_1_rsh_00013b38@ha
		opword 0xEFC2013A
		opword 0xC3E6001C
		lfs f4, float_0p03705_rsh_00013b48@l(r5)
		lfs f3, float_0p4967_rsh_00013b4c@l(r4)
		lfs f2, float_1_rsh_00013b38@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_5_rsh_00013b9c@ha
		opword 0xC006002C
		lfs f1, float_5_rsh_00013b9c@l(r3)
		opword 0xEF61013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_rsh_00013b50@ha
		lis r3, float_32767_rsh_00013b7c@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		opword 0x900100B0
		lfs f0, float_32767_rsh_00013b7c@l(r3)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEF810024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100A8
		lis r5, float_0p2_rsh_00013ba4@ha
		lfs f0, float_32767_rsh_00013b7c@l(r3)
		lis r4, float_0p3_rsh_00013ba0@ha
		opword 0xC82100A8
		lis r3, float_0p5_rsh_00013b24@ha
		lfs f4, float_0p2_rsh_00013ba4@l(r5)
		opword 0xFC60D890
		opword 0xEC411028
		lfs f5, float_0p3_rsh_00013ba0@l(r4)
		opword 0xFC20F090
		opword 0xA8BB0002
		opword 0xEC9C293A
		opword 0xECC20024
		lfs f0, float_0p5_rsh_00013b24@l(r3)
		opword 0x7F83E378
		opword 0x7F64DB78
		opword 0x38C00001
		opword 0xFC40F890
		opword 0xECA6017A
		bl moamoa_jump
		opword 0xA01B0000
		opword 0x5400043C
		opword 0xB01B0000
		opword 0x48001CD8
		opword 0xA87B0004
		opword 0x3863FFFF
		opword 0x7C600735
		opword 0xB07B0004
		opword 0x40801CC4
		opword 0x38000000
		opword 0xB01B0004
		opword 0xA87B0002
		opword 0x38030001
		opword 0xB01B0002
		opword 0x48001CAC
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100B0
		addi r5, r3, float_32767_rsh_00013b7c@l
		opword 0xC0250000
		lis r4, float_200_rsh_00013b78@ha
		opword 0xC80100B0
		lis r3, zero_rsh_00013b20@ha
		addi r5, r4, float_200_rsh_00013b78@l
		opword 0xEC601028
		addi r4, r3, zero_rsh_00013b20@l
		opword 0xC0450000
		lis r3, float_300_rsh_00013ba8@ha
		opword 0xC0040000
		opword 0xEC630824
		lfs f1, float_300_rsh_00013ba8@l(r3)
		opword 0xEC0300BA
		opword 0xD01B001C
		opword 0xC01B001C
		opword 0xEC010032
		opword 0xEF801024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_rsh_00013b50@ha
		opword 0x906100AC
		addi r5, r4, double_to_int_rsh_00013b50@l
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100A8
		addi r4, r3, float_32767_rsh_00013b7c@l
		opword 0xC8250000
		lis r3, zero_rsh_00013b20@ha
		opword 0xC80100A8
		opword 0x38000000
		opword 0xC0440000
		opword 0xEC600828
		lfs f1, zero_rsh_00013b20@l(r3)
		opword 0xEC1C0828
		opword 0xEC431024
		opword 0xEC02083A
		opword 0xD01B0020
		opword 0xA87B0002
		opword 0x38630001
		opword 0xB07B0002
		opword 0xB01B0004
		opword 0xA81B0004
		opword 0x2C0000C8
		opword 0x40800010
		lis r3, float_1_rsh_00013b38@ha
		lfs f1, float_1_rsh_00013b38@l(r3)
		opword 0x48000034
		opword 0x20600320
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_rsh_00013b50@ha
		opword 0x906100B4
		lis r3, float_600_rsh_00013bac@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		opword 0x900100B0
		lfs f0, float_600_rsh_00013bac@l(r3)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEC210024
		lis r3, zero_rsh_00013b20@ha
		opword 0xFF800890
		lfs f0, zero_rsh_00013b20@l(r3)
		opword 0xFC010040
		opword 0x40800014
		opword 0xA01B0000
		opword 0xFF800090
		opword 0x60000200
		opword 0xB01B0000
		opword 0x38C00003
		lis r3, gp@ha
		opword 0x7CBA33D6
		lwz r4, gp@l(r3)
		opword 0x3C004330
		opword 0x900100B0
		lis r3, double_to_int_mask_rsh_00013c18@ha
		opword 0x8004001C
		opword 0x7C8531D6
		opword 0x7C1A0214
		opword 0x900100B4
		lis r5, wp@ha
		lfd f1, double_to_int_mask_rsh_00013c18@l(r3)
		lis r3, float_0p25_rsh_00013bb0@ha
		opword 0xC80100B0
		opword 0x7C04D050
		opword 0x1C00000C
		opword 0xEC200828
		lfs f0, float_0p25_rsh_00013bb0@l(r3)
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
		lis r3, double_to_int_mask_rsh_00013c18@ha
		opword 0xC03B0020
		addi r4, r3, double_to_int_mask_rsh_00013c18@l
		opword 0x80A5001C
		opword 0xEC6100B2
		opword 0x900100A8
		opword 0x7C1A2A14
		opword 0xC01B001C
		opword 0x900100AC
		lis r3, float_0p25_rsh_00013bb0@ha
		opword 0xC8440000
		opword 0xEFC0F73A
		opword 0xC82100A8
		opword 0xEF7CD8FA
		lfs f0, float_0p25_rsh_00013bb0@l(r3)
		opword 0xEC211028
		opword 0xEC210032
		bl cos
		opword 0x809C000C
		lis r3, float_15_rsh_00013b8c@ha
		opword 0xC01B0020
		opword 0xFC800818
		opword 0xC064000C
		opword 0xFC200050
		lfs f2, float_15_rsh_00013b8c@l(r3)
		opword 0xEC1B1828
		opword 0xEC210132
		opword 0xEC001024
		opword 0xEC03002A
		opword 0xEFBCE87A
		opword 0xD004000C
		opword 0x807C000C
		opword 0xC023001C
		opword 0xEC1E0828
		opword 0xEC001024
		opword 0xEC01002A
		opword 0xD003001C
		opword 0x807C000C
		opword 0xC023002C
		opword 0xEC1D0828
		opword 0xEC001024
		opword 0xEC01002A
		opword 0xD003002C
		opword 0xA87B0004
		opword 0x38030001
		opword 0xB01B0004
		opword 0x48001A40
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100B0
		addi r5, r3, float_32767_rsh_00013b7c@l
		lis r4, float_90_rsh_00013bb8@ha
		opword 0xC0050000
		opword 0xC82100B0
		lis r3, float_neg45_rsh_00013bb4@ha
		addi r9, r4, float_90_rsh_00013bb8@l
		lis r4, float_6p2832_rsh_00013b28@ha
		opword 0xEC211028
		addi r5, r3, float_neg45_rsh_00013bb4@l
		lis r3, wp@ha
		addi r8, r4, float_6p2832_rsh_00013b28@l
		addi r6, r3, wp@l
		lis r4, float_1_rsh_00013b38@ha
		opword 0xEC410024
		opword 0x81460000
		opword 0xC0050000
		lis r3, float_360_rsh_00013b2c@ha
		opword 0xC0290000
		addi r7, r3, float_360_rsh_00013b2c@l
		opword 0xEC22007A
		opword 0xC06A0550
		opword 0xC0480000
		lis r6, float_0p00761_rsh_00013b30@ha
		lis r5, float_0p16605_rsh_00013b34@ha
		opword 0xC0070000
		opword 0xEC63082A
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		opword 0xC38A0554
		opword 0xEC4200F2
		lfs f5, float_0p00761_rsh_00013b30@l(r6)
		lfs f4, float_0p16605_rsh_00013b34@l(r5)
		lfs f3, float_1_rsh_00013b38@l(r4)
		opword 0xECC20024
		opword 0xFC060840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC060040
		opword 0x40800020
		opword 0xEC260828
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC060028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x80DC000C
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r4, float_15_rsh_00013b8c@ha
		lfs f2, float_15_rsh_00013b8c@l(r4)
		lis r5, float_0p03705_rsh_00013b48@ha
		opword 0xC006000C
		opword 0xFC060840
		lis r4, float_0p4967_rsh_00013b4c@ha
		lis r3, float_1_rsh_00013b38@ha
		opword 0xEFC2017A
		opword 0xC3E6001C
		lfs f4, float_0p03705_rsh_00013b48@l(r5)
		lfs f3, float_0p4967_rsh_00013b4c@l(r4)
		lfs f2, float_1_rsh_00013b38@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC060040
		opword 0x4080001C
		opword 0xEC060828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC060028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_15_rsh_00013b8c@ha
		opword 0xC006002C
		lfs f1, float_15_rsh_00013b8c@l(r3)
		opword 0xEFA1013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f1, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100B0
		addi r5, r3, float_32767_rsh_00013b7c@l
		opword 0xC0450000
		lis r4, zero_rsh_00013b20@ha
		opword 0xC80100B0
		lis r3, float_1_rsh_00013b38@ha
		opword 0xEC600828
		lfs f1, zero_rsh_00013b20@l(r4)
		lfs f0, float_1_rsh_00013b38@l(r3)
		opword 0xEC431024
		opword 0xEF62007A
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_00013b7c@l
		opword 0xC0050000
		lis r4, zero_rsh_00013b20@ha
		opword 0xC82100A8
		lis r3, float_0p4_rsh_00013bbc@ha
		addi r5, r4, zero_rsh_00013b20@l
		opword 0xFC80D890
		opword 0xEC611028
		addi r4, r3, float_0p4_rsh_00013bbc@l
		opword 0xC0240000
		lis r3, float_100_rsh_00013bc0@ha
		opword 0xC0450000
		opword 0xEC630024
		lfs f0, float_100_rsh_00013bc0@l(r3)
		opword 0x7F83E378
		opword 0x7F64DB78
		opword 0xECA308BA
		opword 0xFC20F090
		opword 0xFC40F890
		opword 0xFC60E890
		opword 0xFC1C0040
		opword 0x4080000C
		opword 0xA8BB0002
		opword 0x48000008
		opword 0x38A00000
		opword 0x38C00001
		bl moamoa_jump
		opword 0x48001748
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100B0
		addi r5, r3, float_32767_rsh_00013b7c@l
		lis r4, float_90_rsh_00013bb8@ha
		lis r3, float_neg45_rsh_00013bb4@ha
		opword 0xC82100B0
		addi r7, r4, float_90_rsh_00013bb8@l
		opword 0xC0050000
		addi r6, r3, float_neg45_rsh_00013bb4@l
		opword 0xEC211028
		lis r3, wp@ha
		addi r5, r3, wp@l
		lis r4, float_180_rsh_00013bc4@ha
		opword 0x81250000
		addi r8, r4, float_180_rsh_00013bc4@l
		opword 0xEC410024
		opword 0xC0060000
		opword 0xC0270000
		lis r3, float_6p2832_rsh_00013b28@ha
		addi r5, r3, float_6p2832_rsh_00013b28@l
		lis r4, float_360_rsh_00013b2c@ha
		opword 0xEC02007A
		opword 0xC0890550
		opword 0xC0680000
		addi r7, r4, float_360_rsh_00013b2c@l
		opword 0xC0450000
		lis r3, float_3p1416_rsh_00013b3c@ha
		opword 0xEC84002A
		lis r6, float_0p00761_rsh_00013b30@ha
		opword 0xC0070000
		lis r5, float_0p16605_rsh_00013b34@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r4, float_1_rsh_00013b38@ha
		opword 0xEC84182A
		opword 0xC3890554
		lfs f5, float_0p00761_rsh_00013b30@l(r6)
		lfs f3, float_1_rsh_00013b38@l(r4)
		opword 0xEC420132
		lfs f4, float_0p16605_rsh_00013b34@l(r5)
		opword 0xEC420024
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC020040
		opword 0x40800020
		opword 0xEC420828
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA500B2
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC020028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC410028
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA500B2
		opword 0xFCA02850
		opword 0x809C000C
		lis r3, float_30_rsh_00013bc8@ha
		lfs f1, float_30_rsh_00013bc8@l(r3)
		opword 0xC004000C
		opword 0xC3E4001C
		opword 0xEFC1017A
		opword 0xC3A4002C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f1, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100B0
		addi r5, r3, float_32767_rsh_00013b7c@l
		opword 0xC0450000
		lis r4, zero_rsh_00013b20@ha
		opword 0xC80100B0
		lis r3, float_1_rsh_00013b38@ha
		lis r5, float_2_rsh_00013bcc@ha
		opword 0xEC600828
		lfs f1, zero_rsh_00013b20@l(r4)
		lfs f0, float_1_rsh_00013b38@l(r3)
		opword 0xEC631024
		lfs f2, float_2_rsh_00013bcc@l(r5)
		opword 0xEC03007A
		opword 0xEF620032
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_00013b7c@l
		lis r6, float_2_rsh_00013bcc@ha
		opword 0xC0050000
		opword 0xC82100A8
		lis r4, zero_rsh_00013b20@ha
		lis r3, float_0p4_rsh_00013bbc@ha
		lfs f4, float_2_rsh_00013bcc@l(r6)
		opword 0xEC211028
		addi r5, r4, zero_rsh_00013b20@l
		addi r4, r3, float_0p4_rsh_00013bbc@l
		opword 0xC0450000
		lis r3, float_100_rsh_00013bc0@ha
		opword 0xEC610024
		opword 0xC0240000
		opword 0x7F64DB78
		lfs f0, float_100_rsh_00013bc0@l(r3)
		opword 0x7F83E378
		opword 0xEC6308BA
		opword 0xFC20F090
		opword 0xFC40F890
		opword 0xECA400F2
		opword 0xFC60E890
		opword 0xFC80D890
		opword 0xFC1C0040
		opword 0x4080000C
		opword 0xA8BB0002
		opword 0x48000008
		opword 0x38A00000
		opword 0x38C00001
		bl moamoa_jump
		opword 0x480014E4
		opword 0x807C000C
		opword 0xC01B0014
		opword 0xC023001C
		opword 0xEC01002A
		opword 0xD003001C
		opword 0xC03B0014
		opword 0xC01B0020
		opword 0xEC010028
		opword 0xD01B0014
		opword 0x807C000C
		opword 0xC07B0008
		opword 0xC023000C
		opword 0xC043002C
		opword 0xC09B0010
		bl angleABf
		lis r3, float_6p2832_rsh_00013b28@ha
		lis r6, float_0p00761_rsh_00013b30@ha
		addi r5, r3, float_6p2832_rsh_00013b28@l
		lis r4, float_360_rsh_00013b2c@ha
		opword 0xC0050000
		lis r5, float_0p16605_rsh_00013b34@ha
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f4, float_0p00761_rsh_00013b30@l(r6)
		opword 0xEC400072
		lfs f0, float_360_rsh_00013b2c@l(r4)
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r4, float_1_rsh_00013b38@ha
		lfs f3, float_0p16605_rsh_00013b34@l(r5)
		opword 0xECA20024
		lfs f2, float_1_rsh_00013b38@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x80FC000C
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r5, float_0p4967_rsh_00013b4c@ha
		opword 0xC05B001C
		lis r6, float_0p03705_rsh_00013b48@ha
		opword 0xC007000C
		opword 0xFC050840
		lis r4, float_1_rsh_00013b38@ha
		lfs f3, float_0p4967_rsh_00013b4c@l(r5)
		opword 0xEC02013A
		lfs f4, float_0p03705_rsh_00013b48@l(r6)
		lfs f2, float_1_rsh_00013b38@l(r4)
		opword 0xD007000C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x807C000C
		opword 0xFC202050
		opword 0xC05B001C
		opword 0xC003002C
		opword 0xEC02007A
		opword 0xD003002C
		opword 0xA87B0018
		opword 0x3863FFFF
		opword 0x7C600735
		opword 0xB07B0018
		opword 0x408012DC
		opword 0xC01B0008
		opword 0x38000000
		opword 0x807C000C
		opword 0xD003000C
		opword 0xC01B000C
		opword 0x807C000C
		opword 0xD003001C
		opword 0xC01B0010
		opword 0x807C000C
		opword 0xD003002C
		opword 0xA07B0000
		opword 0x546307FA
		opword 0xB07B0000
		opword 0x807C0000
		opword 0x54630734
		opword 0x907C0000
		opword 0xB01B0004
		opword 0xA87B0002
		opword 0x38030001
		opword 0xB01B0002
		opword 0x48001288
		opword 0xA87B0004
		opword 0x38630001
		opword 0x7C600734
		opword 0xB07B0004
		opword 0x2C000004
		opword 0x40811270
		opword 0xA81B0024
		opword 0xB01B0002
		opword 0x48001264
		opword 0xA01B0000
		opword 0x540007FF
		opword 0x40820010
		opword 0xC37E008C
		opword 0xC39E0094
		opword 0x48000030
		opword 0x38600003
		lis r4, wp@ha
		opword 0x7C1A1BD6
		addi r4, r4, wp@l
		opword 0x80840000
		opword 0x7C0019D6
		opword 0x7C00D050
		opword 0x1C00000C
		opword 0x7C640214
		opword 0xC3630014
		opword 0xC383001C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_rsh_00013b50@ha
		lis r3, float_32767_rsh_00013b7c@ha
		lfd f4, double_to_int_rsh_00013b50@l(r4)
		opword 0x900100B0
		opword 0xFC40E090
		lfs f0, float_32767_rsh_00013b7c@l(r3)
		opword 0xFC20D890
		opword 0xC86100B0
		opword 0x80BC000C
		opword 0xECA32028
		opword 0xC065000C
		opword 0xC085002C
		opword 0xEF850024
		bl angleABf
		lis r3, float_90_rsh_00013bb8@ha
		lis r4, float_neg45_rsh_00013bb4@ha
		addi r5, r3, float_90_rsh_00013bb8@l
		lfs f0, float_neg45_rsh_00013bb4@l(r4)
		opword 0xC0450000
		lis r3, float_6p2832_rsh_00013b28@ha
		addi r8, r3, float_6p2832_rsh_00013b28@l
		lis r4, float_360_rsh_00013b2c@ha
		opword 0xEC1C00BA
		addi r7, r4, float_360_rsh_00013b2c@l
		lis r6, float_0p00761_rsh_00013b30@ha
		lis r5, float_0p16605_rsh_00013b34@ha
		lis r3, float_3p1416_rsh_00013b3c@ha
		lis r4, float_1_rsh_00013b38@ha
		opword 0xEC41002A
		opword 0xC0280000
		opword 0xC0070000
		lfs f4, float_0p00761_rsh_00013b30@l(r6)
		opword 0xEC4100B2
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lfs f3, float_0p16605_rsh_00013b34@l(r5)
		opword 0xECA20024
		lfs f2, float_1_rsh_00013b38@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x80DC000C
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r4, float_15_rsh_00013b8c@ha
		lfs f2, float_15_rsh_00013b8c@l(r4)
		lis r4, float_0p4967_rsh_00013b4c@ha
		opword 0xC006000C
		opword 0xFC050840
		lis r5, float_0p03705_rsh_00013b48@ha
		lis r3, float_1_rsh_00013b38@ha
		opword 0xEFC2013A
		opword 0xC3E6001C
		lfs f4, float_0p03705_rsh_00013b48@l(r5)
		lfs f3, float_0p4967_rsh_00013b4c@l(r4)
		lfs f2, float_1_rsh_00013b38@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_15_rsh_00013b8c@ha
		opword 0xC006002C
		lfs f1, float_15_rsh_00013b8c@l(r3)
		opword 0xEF61013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_rsh_00013b50@ha
		lis r3, float_32767_rsh_00013b7c@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		opword 0x900100B0
		lfs f0, float_32767_rsh_00013b7c@l(r3)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEF810024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_00013b7c@l
		opword 0xC0050000
		lis r4, zero_rsh_00013b20@ha
		opword 0xC82100A8
		lis r3, float_1_rsh_00013b38@ha
		lfs f5, zero_rsh_00013b20@l(r4)
		opword 0x7F64DB78
		opword 0xEC611028
		opword 0xA8BB0002
		opword 0xFC20F090
		opword 0x38C00001
		opword 0xFC40F890
		opword 0x38A50001
		opword 0xECC30024
		lfs f0, float_1_rsh_00013b38@l(r3)
		opword 0x7F83E378
		opword 0xEC9C017A
		opword 0xFC60D890
		opword 0xECA6017A
		bl moamoa_jump
		opword 0x48000F60
		opword 0xA87B0004
		opword 0x38630001
		opword 0x7C600734
		opword 0xB07B0004
		opword 0x2C00001E
		opword 0x40800040
		opword 0x809C000C
		lis r3, float_0p9_rsh_00013bd0@ha
		lfs f1, float_0p9_rsh_00013bd0@l(r3)
		opword 0xC0040000
		opword 0xEC000072
		opword 0xD0040000
		opword 0x807C000C
		opword 0xC0030014
		opword 0xEC000072
		opword 0xD0030014
		opword 0x807C000C
		opword 0xC0030028
		opword 0xEC000072
		opword 0xD0030028
		opword 0x48000F0C
		opword 0x38000031
		opword 0xB01B0002
		opword 0x48000F00
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_rsh_00013b50@ha
		lis r3, float_32767_rsh_00013b7c@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		opword 0x900100B0
		lfs f0, float_32767_rsh_00013b7c@l(r3)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEF810024
		bl rand
		lis r5, float_90_rsh_00013bb8@ha
		lis r4, float_135_rsh_00013bd4@ha
		lfs f0, float_135_rsh_00013bd4@l(r4)
		opword 0x6C668000
		lfs f1, float_90_rsh_00013bb8@l(r5)
		opword 0x3C004330
		lis r3, float_6p2832_rsh_00013b28@ha
		lis r4, double_to_int_rsh_00013b50@ha
		addi r5, r3, float_6p2832_rsh_00013b28@l
		opword 0x90C100AC
		opword 0xEC1C007A
		addi r6, r4, double_to_int_rsh_00013b50@l
		opword 0x900100A8
		lis r3, float_360_rsh_00013b2c@ha
		opword 0xC0250000
		addi r4, r3, float_360_rsh_00013b2c@l
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0xEC210032
		opword 0xC0040000
		addi r5, r3, float_32767_rsh_00013b7c@l
		opword 0xC8660000
		lis r4, float_300_rsh_00013ba8@ha
		opword 0xC84100A8
		opword 0xECE10024
		addi r6, r4, float_300_rsh_00013ba8@l
		lis r3, float_3p1416_rsh_00013b3c@ha
		lis r4, float_0p16605_rsh_00013b34@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r3, float_1_rsh_00013b38@ha
		opword 0xEC621828
		opword 0xC0450000
		lis r5, float_200_rsh_00013b78@ha
		opword 0xC0060000
		addi r7, r5, float_200_rsh_00013b78@l
		opword 0xFC070840
		opword 0xEC631024
		opword 0xC0470000
		lis r5, float_0p00761_rsh_00013b30@ha
		lfs f4, float_0p16605_rsh_00013b34@l(r4)
		lfs f5, float_0p00761_rsh_00013b30@l(r5)
		opword 0xECC300BA
		lfs f2, float_1_rsh_00013b38@l(r3)
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC070040
		opword 0x40800020
		opword 0xEC270828
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5103A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC070028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5103A
		opword 0xECA50072
		opword 0xFCA02850
		lis r3, float_3p1416_rsh_00013b3c@ha
		opword 0x80DC000C
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r5, float_0p03705_rsh_00013b48@ha
		opword 0xC006000C
		lis r4, float_0p4967_rsh_00013b4c@ha
		opword 0xFC070840
		lis r3, float_1_rsh_00013b38@ha
		opword 0xEFC6017A
		lfs f4, float_0p03705_rsh_00013b48@l(r5)
		lfs f3, float_0p4967_rsh_00013b4c@l(r4)
		lfs f2, float_1_rsh_00013b38@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC070040
		opword 0x4080001C
		opword 0xEC070828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC070028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f1, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100B0
		addi r5, r3, float_32767_rsh_00013b7c@l
		opword 0xC0450000
		lis r4, float_1_rsh_00013b38@ha
		opword 0xC80100B0
		lis r3, float_5_rsh_00013b9c@ha
		opword 0xEC600828
		lfs f1, float_1_rsh_00013b38@l(r4)
		lfs f0, float_5_rsh_00013b9c@l(r3)
		opword 0xEC431024
		opword 0xEF62007A
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f1, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_00013b7c@l
		opword 0xC0450000
		lis r4, float_0p1_rsh_00013bdc@ha
		opword 0xC80100A8
		lis r3, float_0p2_rsh_00013bd8@ha
		opword 0x2C180000
		opword 0xEC600828
		lfs f1, float_0p1_rsh_00013bdc@l(r4)
		lfs f0, float_0p2_rsh_00013bd8@l(r3)
		opword 0xEC431024
		opword 0xEF82007A
		opword 0x40820050
		lis r3, vec3_rsh_00013758@ha
		opword 0x38810014
		addi r7, r3, vec3_rsh_00013758@l
		opword 0x386006C3
		opword 0x80C70000
		opword 0x80A70004
		opword 0x80070008
		opword 0x90C10014
		opword 0x90A10018
		opword 0x9001001C
		opword 0x80BC000C
		opword 0xC005000C
		opword 0xD0010014
		opword 0xC005001C
		opword 0xD0010018
		opword 0xC005002C
		opword 0xD001001C
		bl psndSFXOn_3D
		opword 0x3B000001
		lis r3, float_neg100_rsh_00013be0@ha
		opword 0xFC20F090
		lfs f2, float_neg100_rsh_00013be0@l(r3)
		opword 0xFC60F890
		opword 0xFC80D890
		opword 0x7F83E378
		opword 0xFCA0E090
		opword 0x7F64DB78
		opword 0x38A00031
		opword 0x38C00000
		bl moamoa_jump
		opword 0x48000BB0
		opword 0xA87B0018
		opword 0x3863FFFF
		opword 0x7C600735
		opword 0xB07B0018
		opword 0x40810074
		opword 0xC03B0008
		opword 0xC01B0014
		opword 0xEC01002A
		opword 0xD01B0008
		opword 0xC03B000C
		opword 0xC01B001C
		opword 0xEC01002A
		opword 0xD01B000C
		opword 0xC03B0010
		opword 0xC01B0020
		opword 0xEC01002A
		opword 0xD01B0010
		opword 0x807C000C
		opword 0xC01B0008
		opword 0xC023000C
		opword 0xEC01002A
		opword 0xD003000C
		opword 0x807C000C
		opword 0xC01B000C
		opword 0xC023001C
		opword 0xEC01002A
		opword 0xD003001C
		opword 0x807C000C
		opword 0xC01B0010
		opword 0xC023002C
		opword 0xEC01002A
		opword 0xD003002C
		opword 0x48000B2C
		opword 0x38000031
		opword 0xB01B0002
		opword 0x48000B20
		lis r3, wp@ha
		lwz r4, wp@l(r3)
		opword 0xA0640000
		opword 0x546004E7
		opword 0x41820018
		opword 0x546004A5
		opword 0x41820010
		opword 0x3800003E
		opword 0xB01B0002
		opword 0x48000AF8
		opword 0xA8040038
		opword 0x2C0001F4
		opword 0x40800078
		opword 0x807C000C
		bl PSMTXIdentity
		opword 0x38A00003
		lis r6, wp@ha
		opword 0x7C9A2BD6
		opword 0x807C000C
		addi r7, r6, wp@l
		opword 0x80C70000
		opword 0x38000000
		opword 0x7C8429D6
		opword 0x7C84D050
		opword 0x1D04000C
		opword 0x38880014
		opword 0x7C06242E
		opword 0x38A80018
		opword 0x3888001C
		opword 0xD003000C
		opword 0x80C70000
		opword 0x807C000C
		opword 0x7C062C2E
		opword 0xD003001C
		opword 0x80A70000
		opword 0x807C000C
		opword 0x7C05242E
		opword 0xD003002C
		opword 0xB01B0000
		opword 0xB01B0002
		opword 0xB01B0004
		opword 0x48000A78
		opword 0x3800003E
		opword 0xB01B0002
		opword 0x48000A6C
		opword 0xA81B0004
		opword 0x2C00001E
		opword 0x40800048
		lis r4, float_0p20944_rsh_00013be4@ha
		opword 0x38610074
		addi r5, r4, float_0p20944_rsh_00013be4@l
		opword 0x38800079
		opword 0xC0250000
		bl PSMTXRotRad
		opword 0x807C000C
		opword 0x38810074
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x801C0000
		opword 0x540007FA
		opword 0x901C0000
		opword 0xA87B0004
		opword 0x38030001
		opword 0xB01B0004
		opword 0x48000A1C
		opword 0x801C0000
		opword 0x60000002
		opword 0x901C0000
		bl rand
		opword 0x3880001E
		opword 0x7C0323D6
		opword 0x7C0021D6
		opword 0x7C001850
		opword 0xB01B0004
		opword 0xA87B0002
		opword 0x38030001
		opword 0xB01B0002
		opword 0x480009E8
		opword 0xA87B0004
		opword 0x3863FFFF
		opword 0x7C600735
		opword 0xB07B0004
		opword 0x408009D4
		opword 0x38000000
		opword 0xB01B0004
		opword 0xA87B0002
		opword 0x38030001
		opword 0xB01B0002
		opword 0x480009BC
		opword 0x80BC000C
		lis r4, float_neg275_rsh_00013be8@ha
		lis r3, float_neg100_rsh_00013be0@ha
		lfs f3, float_neg275_rsh_00013be8@l(r4)
		opword 0xC025000C
		opword 0xC045002C
		lfs f4, float_neg100_rsh_00013be0@l(r3)
		bl distABf
		opword 0xFF800890
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100B0
		lis r4, float_neg275_rsh_00013be8@ha
		lfs f0, float_32767_rsh_00013b7c@l(r3)
		lis r3, float_neg100_rsh_00013be0@ha
		opword 0xC82100B0
		opword 0x80BC000C
		opword 0xEC611028
		lfs f4, float_neg100_rsh_00013be0@l(r3)
		opword 0xC025000C
		opword 0xC045002C
		opword 0xEFA30024
		lfs f3, float_neg275_rsh_00013be8@l(r4)
		bl angleABf
		lis r3, float_90_rsh_00013bb8@ha
		lis r4, float_neg45_rsh_00013bb4@ha
		addi r5, r3, float_90_rsh_00013bb8@l
		lfs f2, float_neg45_rsh_00013bb4@l(r4)
		opword 0xC0650000
		lis r3, float_6_rsh_00013bec@ha
		lfs f0, float_6_rsh_00013bec@l(r3)
		opword 0xEC5D10FA
		opword 0xFC1C0040
		opword 0xEC21102A
		opword 0x40810274
		opword 0x807C000C
		lis r4, float_60_rsh_00013b18@ha
		lfs f0, float_60_rsh_00013b18@l(r4)
		opword 0xC3C3001C
		opword 0xFC1E0040
		opword 0x4080025C
		lis r4, float_6p2832_rsh_00013b28@ha
		lis r7, float_0p00761_rsh_00013b30@ha
		addi r6, r4, float_6p2832_rsh_00013b28@l
		lis r5, float_360_rsh_00013b2c@ha
		opword 0xC0060000
		lis r6, float_0p16605_rsh_00013b34@ha
		lis r4, float_3p1416_rsh_00013b3c@ha
		lfs f4, float_0p00761_rsh_00013b30@l(r7)
		opword 0xEC400072
		lfs f0, float_360_rsh_00013b2c@l(r5)
		lfs f1, float_3p1416_rsh_00013b3c@l(r4)
		lis r5, float_1_rsh_00013b38@ha
		lfs f3, float_0p16605_rsh_00013b34@l(r6)
		opword 0xECA20024
		lfs f2, float_1_rsh_00013b38@l(r5)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r4, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r4)
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
		lis r4, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r4)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r4, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r4)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		lis r4, float_3p1416_rsh_00013b3c@ha
		lis r5, float_15_rsh_00013b8c@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r4)
		lis r6, float_0p03705_rsh_00013b48@ha
		lfs f2, float_15_rsh_00013b8c@l(r5)
		lis r5, float_0p4967_rsh_00013b4c@ha
		opword 0xC003000C
		opword 0xFC050840
		lis r4, float_1_rsh_00013b38@ha
		lfs f3, float_0p4967_rsh_00013b4c@l(r5)
		opword 0xEFE2013A
		lfs f4, float_0p03705_rsh_00013b48@l(r6)
		lfs f2, float_1_rsh_00013b38@l(r4)
		opword 0x4C401382
		opword 0x40820044
		lis r4, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r4)
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
		lis r4, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r4)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r4, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r4)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r4, float_15_rsh_00013b8c@ha
		opword 0xC003002C
		lfs f1, float_15_rsh_00013b8c@l(r4)
		opword 0xEF61013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_rsh_00013b50@ha
		lis r3, float_32767_rsh_00013b7c@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		opword 0x900100B0
		lfs f0, float_32767_rsh_00013b7c@l(r3)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEF810024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_00013b7c@l
		opword 0xC0050000
		lis r4, zero_rsh_00013b20@ha
		opword 0xC82100A8
		lis r3, float_1_rsh_00013b38@ha
		lfs f6, zero_rsh_00013b20@l(r4)
		lis r5, float_3_rsh_00013bf0@ha
		opword 0xEC211028
		lfs f5, float_1_rsh_00013b38@l(r3)
		lfs f4, float_3_rsh_00013bf0@l(r5)
		opword 0xFC40F090
		opword 0xFC60D890
		opword 0xA8BB0002
		opword 0xECE10024
		opword 0x7F83E378
		opword 0x7F64DB78
		opword 0x38C00001
		opword 0xEC1C29BA
		opword 0xFC20F890
		opword 0xECA729BA
		opword 0xEC840032
		bl moamoa_jump
		opword 0x480006AC
		opword 0xA87B0002
		opword 0x38030001
		opword 0xB01B0002
		opword 0x4800069C
		opword 0x809C000C
		lis r3, float_neg350_rsh_00013bf4@ha
		lfs f0, float_neg350_rsh_00013bf4@l(r3)
		opword 0xC024000C
		opword 0xFC010040
		opword 0x408102D4
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100B0
		lis r4, float_neg350_rsh_00013bf4@ha
		lfs f0, float_32767_rsh_00013b7c@l(r3)
		lis r3, float_neg100_rsh_00013be0@ha
		opword 0xC82100B0
		opword 0x80BC000C
		opword 0xEC611028
		lfs f4, float_neg100_rsh_00013be0@l(r3)
		opword 0xC025000C
		opword 0xC045002C
		opword 0xEF830024
		lfs f3, float_neg350_rsh_00013bf4@l(r4)
		bl angleABf
		lis r3, float_90_rsh_00013bb8@ha
		lis r4, float_neg45_rsh_00013bb4@ha
		addi r5, r3, float_90_rsh_00013bb8@l
		lfs f0, float_neg45_rsh_00013bb4@l(r4)
		opword 0xC0450000
		lis r3, float_6p2832_rsh_00013b28@ha
		addi r8, r3, float_6p2832_rsh_00013b28@l
		lis r4, float_360_rsh_00013b2c@ha
		opword 0xEC1C00BA
		addi r7, r4, float_360_rsh_00013b2c@l
		lis r6, float_0p00761_rsh_00013b30@ha
		lis r5, float_0p16605_rsh_00013b34@ha
		lis r3, float_3p1416_rsh_00013b3c@ha
		lis r4, float_1_rsh_00013b38@ha
		opword 0xEC41002A
		opword 0xC0280000
		opword 0xC0070000
		lfs f4, float_0p00761_rsh_00013b30@l(r6)
		opword 0xEC4100B2
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lfs f3, float_0p16605_rsh_00013b34@l(r5)
		opword 0xECA20024
		lfs f2, float_1_rsh_00013b38@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x80DC000C
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r4, float_15_rsh_00013b8c@ha
		lfs f2, float_15_rsh_00013b8c@l(r4)
		lis r4, float_0p4967_rsh_00013b4c@ha
		opword 0xC006000C
		opword 0xFC050840
		lis r5, float_0p03705_rsh_00013b48@ha
		lis r3, float_1_rsh_00013b38@ha
		opword 0xEFC2013A
		opword 0xC3E6001C
		lfs f4, float_0p03705_rsh_00013b48@l(r5)
		lfs f3, float_0p4967_rsh_00013b4c@l(r4)
		lfs f2, float_1_rsh_00013b38@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_15_rsh_00013b8c@ha
		opword 0xC006002C
		lfs f1, float_15_rsh_00013b8c@l(r3)
		opword 0xEF61013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_rsh_00013b50@ha
		lis r3, float_32767_rsh_00013b7c@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		opword 0x900100B0
		lfs f0, float_32767_rsh_00013b7c@l(r3)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEF810024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_00013b7c@l
		opword 0xC0050000
		lis r4, zero_rsh_00013b20@ha
		opword 0xC82100A8
		lis r3, float_1_rsh_00013b38@ha
		lfs f6, zero_rsh_00013b20@l(r4)
		lis r5, float_3_rsh_00013bf0@ha
		opword 0xEC211028
		lfs f5, float_1_rsh_00013b38@l(r3)
		lfs f4, float_3_rsh_00013bf0@l(r5)
		opword 0xFC40F890
		opword 0xFC60D890
		opword 0xA8BB0002
		opword 0xECE10024
		opword 0x7F83E378
		opword 0x7F64DB78
		opword 0x38C00001
		opword 0xEC1C29BA
		opword 0xFC20F090
		opword 0xECA729BA
		opword 0xEC840032
		bl moamoa_jump
		opword 0x480003B4
		opword 0x3800003E
		opword 0xB01B0002
		opword 0x480003A8
		opword 0xA01B0000
		opword 0x60000020
		opword 0xB01B0000
		opword 0x801C0000
		opword 0x5400003C
		opword 0x901C0000
		opword 0x801C0000
		opword 0x60000004
		opword 0x901C0000
		opword 0x48000380
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		lis r4, double_to_int_rsh_00013b50@ha
		lis r3, float_32767_rsh_00013b7c@ha
		lfd f2, double_to_int_rsh_00013b50@l(r4)
		opword 0x900100B0
		lfs f0, float_32767_rsh_00013b7c@l(r3)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEF810024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00013b50@ha
		lfd f1, double_to_int_rsh_00013b50@l(r4)
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_00013b7c@l
		opword 0xC0450000
		lis r4, float_1_rsh_00013b38@ha
		opword 0xC80100A8
		lis r3, float_2_rsh_00013bcc@ha
		opword 0x7F400E70
		opword 0xEC600828
		lfs f0, float_2_rsh_00013bcc@l(r3)
		lfs f1, float_1_rsh_00013b38@l(r4)
		opword 0x7C600194
		opword 0xEC431024
		opword 0xEFE2007A
		bl irand
		lis r5, float_90_rsh_00013bb8@ha
		lis r4, float_225_rsh_00013bf8@ha
		lfs f1, float_90_rsh_00013bb8@l(r5)
		lis r7, float_0p00761_rsh_00013b30@ha
		lfs f0, float_225_rsh_00013bf8@l(r4)
		lis r6, float_6p2832_rsh_00013b28@ha
		lis r5, float_360_rsh_00013b2c@ha
		lis r4, float_3p1416_rsh_00013b3c@ha
		opword 0xEC1C007A
		lfs f1, float_6p2832_rsh_00013b28@l(r6)
		lis r6, float_0p16605_rsh_00013b34@ha
		opword 0xB07B0004
		lfs f4, float_0p00761_rsh_00013b30@l(r7)
		opword 0xEC410032
		lfs f0, float_360_rsh_00013b2c@l(r5)
		lis r5, float_1_rsh_00013b38@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r4)
		opword 0xEFC20024
		lfs f3, float_0p16605_rsh_00013b34@l(r6)
		lfs f2, float_1_rsh_00013b38@l(r5)
		opword 0xFC1E0840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC1E0040
		opword 0x40800020
		opword 0xEC3E0828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC1E0028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0xEC1F0132
		opword 0xD01B0008
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_rsh_00013b50@ha
		opword 0x906100B4
		addi r5, r4, double_to_int_rsh_00013b50@l
		lis r3, float_32767_rsh_00013b7c@ha
		opword 0x900100B0
		addi r4, r3, float_32767_rsh_00013b7c@l
		opword 0xC8450000
		lis r3, float_1_rsh_00013b38@ha
		opword 0xC82100B0
		addi r5, r3, float_1_rsh_00013b38@l
		opword 0xC0040000
		lis r4, float_0p03705_rsh_00013b48@ha
		opword 0xEC611028
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r3, float_0p4967_rsh_00013b4c@ha
		opword 0xC0450000
		opword 0xEC030024
		lfs f4, float_0p03705_rsh_00013b48@l(r4)
		lfs f3, float_0p4967_rsh_00013b4c@l(r3)
		opword 0xEC0010BA
		opword 0xFC1E0840
		opword 0xD01B000C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC1E0040
		opword 0x4080001C
		opword 0xEC1E0828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC1E0028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC002050
		opword 0xEC1F0032
		opword 0xD01B0010
		opword 0xA87B0002
		opword 0x38030001
		opword 0xB01B0002
		opword 0x480000F4
		opword 0xA87B0004
		opword 0x3863FFFF
		opword 0x7C600735
		opword 0xB07B0004
		opword 0x408000E0
		opword 0xA87B0002
		opword 0x38030001
		opword 0xB01B0002
		opword 0x480000D0
		lis r3, float_1p1_rsh_00013bfc@ha
		lis r4, float_1p02_rsh_00013c00@ha
		addi r6, r3, float_1p1_rsh_00013bfc@l
		lis r3, float_0p20944_rsh_00013be4@ha
		opword 0xC03B0008
		addi r5, r4, float_1p02_rsh_00013c00@l
		opword 0xC0660000
		addi r4, r3, float_0p20944_rsh_00013be4@l
		opword 0xC0050000
		opword 0x38610044
		opword 0xEC4100F2
		opword 0xC0240000
		opword 0x38800079
		opword 0xD05B0008
		opword 0xC05B000C
		opword 0xEC020032
		opword 0xD01B000C
		opword 0xC01B0010
		opword 0xEC0000F2
		opword 0xD01B0010
		opword 0x80BC000C
		opword 0xC01B0008
		opword 0xC045000C
		opword 0xEC02002A
		opword 0xD005000C
		opword 0x80BC000C
		opword 0xC01B000C
		opword 0xC045001C
		opword 0xEC02002A
		opword 0xD005001C
		opword 0x80BC000C
		opword 0xC01B0010
		opword 0xC045002C
		opword 0xEC02002A
		opword 0xD005002C
		bl PSMTXRotRad
		opword 0x807C000C
		opword 0x38810044
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x801C0000
		lis r3, float_neg1000_rsh_00013c04@ha
		lfs f0, float_neg1000_rsh_00013c04@l(r3)
		opword 0x540007FA
		opword 0x901C0000
		opword 0x807C000C
		opword 0xC023000C
		opword 0xFC010040
		opword 0x4080000C
		opword 0x3800003E
		opword 0xB01B0002
		opword 0xA01B0000
		opword 0x70000098
		opword 0x40820074
		opword 0x809C000C
		lis r3, float_290_rsh_00013c08@ha
		lfs f0, float_290_rsh_00013c08@l(r3)
		opword 0xC024000C
		opword 0xFC010040
		opword 0x40810008
		opword 0xD004000C
		opword 0x809C000C
		lis r3, float_neg290_rsh_00013c0c@ha
		lfs f0, float_neg290_rsh_00013c0c@l(r3)
		opword 0xC024000C
		opword 0xFC010040
		opword 0x40800008
		opword 0xD004000C
		opword 0x809C000C
		lis r3, float_50_rsh_00013b88@ha
		lfs f0, float_50_rsh_00013b88@l(r3)
		opword 0xC024002C
		opword 0xFC010040
		opword 0x40810008
		opword 0xD004002C
		opword 0x809C000C
		lis r3, float_neg130_rsh_00013c10@ha
		lfs f0, float_neg130_rsh_00013c10@l(r3)
		opword 0xC024002C
		opword 0xFC010040
		opword 0x40800008
		opword 0xD004002C
		opword 0x80BF0000
		opword 0x3B5A0001
		opword 0x809C000C
		opword 0x8065000C
		opword 0xC0050010
		opword 0xC0230038
		opword 0xC044001C
		opword 0xEC010028
		opword 0xEC02002A
		opword 0xD004001C
		opword 0x807C000C
		opword 0xC003000C
		opword 0xD01B0028
		opword 0x807C000C
		opword 0x3B9C0020
		opword 0xC003002C
		opword 0xD01B002C
		opword 0x3B7B0050
		opword 0x807F0000
		opword 0x80030004
		opword 0x7C1A0000
		opword 0x4180D41C
		bl moamoa_pose_main
		lis r3, wp@ha
		addi r4, r3, wp@l
		opword 0x80A40000
		opword 0x8065000C
		opword 0xC0030038
		opword 0xD0050010
		opword 0x80640000
		opword 0xA0030000
		opword 0x540006F7
		opword 0x4182001C
		lis r3, zero_rsh_00013b20@ha
		lfs f0, zero_rsh_00013b20@l(r3)
		opword 0xD01E0174
		opword 0xD01E0178
		opword 0xD01E017C
		opword 0x480000A4
		lis r3, vec3_rsh_00013764@ha
		opword 0xC05E0174
		addi r6, r3, vec3_rsh_00013764@l
		opword 0xC03E0178
		opword 0x80A60000
		opword 0x3861002C
		opword 0x80860004
		opword 0x80060008
		opword 0x90A10008
		opword 0xC01E017C
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
		lis r3, float_2_rsh_00013bcc@ha
		lfs f0, float_2_rsh_00013bcc@l(r3)
		opword 0xFC010040
		opword 0x4081003C
		opword 0x3861002C
		opword 0x7C641B78
		bl PSVECNormalize
		lis r3, float_2_rsh_00013bcc@ha
		opword 0xC001002C
		lfs f1, float_2_rsh_00013bcc@l(r3)
		opword 0xEC010032
		opword 0xD01E0174
		opword 0xC0010030
		opword 0xEC010032
		opword 0xD01E0178
		opword 0xC0010034
		opword 0xEC010032
		opword 0xD01E017C
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

#pragma dont_inline reset

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
static void ext_moamoa_dispent(void) {
#ifdef NONMATCHING
    if (wp->flags & 1) {
        dispEntry(CAMERA_3D, zero_rsh_00013b20[0], 1, ext_disp, NULL);
        dispEntry(CAMERA_3D, zero_rsh_00013b20[0], 2, ext_shadow_disp, NULL);
    }
    if (wp->flags & 2) {
        dispEntry(CAMERA_OFFSCREEN2, -5000.0f, 1, ext_disp, NULL);
        dispEntry(CAMERA_OFFSCREEN2, -5000.0f, 2, ext_shadow_disp, NULL);
    }
#endif
#ifndef NONMATCHING
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
		lis r3, zero_rsh_00013b20@ha
		lis r4, ext_disp@ha
		addi r6, r3, zero_rsh_00013b20@l
		opword 0xC0260000
		addi r5, r4, ext_disp@l
		opword 0x38600004
		opword 0x38800001
		opword 0x38C00000
		bl dispEntry
		lis r3, zero_rsh_00013b20@ha
		lis r4, ext_shadow_disp@ha
		addi r6, r3, zero_rsh_00013b20@l
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
		lis r3, float_neg5000_rsh_00013b58@ha
		lis r4, ext_disp@ha
		addi r6, r3, float_neg5000_rsh_00013b58@l
		opword 0xC0260000
		addi r5, r4, ext_disp@l
		opword 0x38600001
		opword 0x38800001
		opword 0x38C00000
		bl dispEntry
		lis r3, float_neg5000_rsh_00013b58@ha
		lis r4, ext_shadow_disp@ha
		addi r6, r3, float_neg5000_rsh_00013b58@l
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
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
static s32 npc_jump(EventEntry* event, BOOL isFirstCall) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FF70
		opword 0x7C0802A6
		opword 0x90010094
		opword 0xDBE10080
		opword 0xF3E10088
		opword 0xDBC10070
		opword 0xF3C10078
		opword 0xDBA10060
		opword 0xF3A10068
		opword 0xDB810050
		opword 0xF3810058
		opword 0xBF810040
		opword 0x7C7E1B78
		opword 0x7C9C2378
		opword 0x83E30018
		opword 0x809F0000
		bl evtGetValue
		opword 0x809F0004
		opword 0x7C7D1B78
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFFA00890
		opword 0x809F0008
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFFC00890
		opword 0x809F000C
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFF800890
		opword 0x809F0010
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xD0210010
		opword 0x7FC3F378
		opword 0x809F0014
		bl evtGetFloat
		opword 0xFFE00890
		opword 0x809F0018
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_rsh_00013b50@ha
		opword 0x9061003C
		addi r3, r4, double_to_int_rsh_00013b50@l
		lis r4, float_60_rsh_00013b18@ha
		opword 0x90010038
		addi r5, r4, float_60_rsh_00013b18@l
		opword 0xC8230000
		lis r3, float_1000_rsh_00013b1c@ha
		opword 0xC8010038
		addi r4, r3, float_1000_rsh_00013b1c@l
		opword 0xC0450000
		opword 0x7FA3EB78
		opword 0xEC200828
		opword 0xC0040000
		opword 0xEC220072
		opword 0xEC010024
		opword 0xD001000C
		bl npcNameToPtr
		opword 0x2C1C0000
		opword 0x7C7F1B78
		opword 0x418200DC
		lis r3, vec3_rsh_00013788@ha
		lis r4, vec3_rsh_0001377c@ha
		addi r7, r3, vec3_rsh_00013788@l
		opword 0x3861002C
		opword 0x80C70000
		addi r5, r4, vec3_rsh_0001377c@l
		opword 0x80070004
		opword 0x38810020
		opword 0x80E70008
		opword 0x90C10020
		opword 0x80C50000
		opword 0x90010024
		opword 0x80050008
		opword 0x90E10028
		opword 0x80A50004
		opword 0xC01F008C
		opword 0xD0010020
		opword 0xC01F0094
		opword 0x90C1002C
		opword 0x90010034
		opword 0xD0010028
		opword 0x90A10030
		opword 0xD3A1002C
		opword 0xD3810034
		bl PSVECDistance
		lis r3, zero_rsh_00013b20@ha
		opword 0xC05F0090
		opword 0xC061000C
		lfs f0, zero_rsh_00013b20@l(r3)
		opword 0xEC9E1028
		opword 0xFC001800
		opword 0x7C000026
		opword 0x54001FFF
		opword 0x41820010
		opword 0xC0010010
		opword 0xEC010024
		opword 0xD001000C
		opword 0x2C000000
		opword 0x4082000C
		opword 0xEC011824
		opword 0xD0010010
		opword 0xC041000C
		lis r3, float_0p5_rsh_00013b24@ha
		opword 0x8001000C
		opword 0xEC041024
		lfs f1, float_0p5_rsh_00013b24@l(r3)
		opword 0x901E0078
		opword 0x80010010
		opword 0xEC5F00B2
		opword 0xEC02007A
		opword 0xD0010008
		opword 0x80610008
		opword 0x907E007C
		opword 0x901E0080
		opword 0xC03E0078
		opword 0xFC60E890
		opword 0xC05E007C
		opword 0xFC80E090
		opword 0xC01E0080
		opword 0xD021000C
		opword 0xC03F008C
		opword 0xD0410008
		opword 0xC05F0094
		opword 0xD0010010
		bl angleABf
		lis r3, float_6p2832_rsh_00013b28@ha
		lis r6, float_0p00761_rsh_00013b30@ha
		addi r5, r3, float_6p2832_rsh_00013b28@l
		lis r4, float_360_rsh_00013b2c@ha
		opword 0xC0050000
		lis r5, float_0p16605_rsh_00013b34@ha
		lis r3, float_3p1416_rsh_00013b3c@ha
		lfs f4, float_0p00761_rsh_00013b30@l(r6)
		opword 0xEC400072
		lfs f0, float_360_rsh_00013b2c@l(r4)
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r4, float_1_rsh_00013b38@ha
		lfs f3, float_0p16605_rsh_00013b34@l(r5)
		opword 0xECA20024
		lfs f2, float_1_rsh_00013b38@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		lis r3, float_3p1416_rsh_00013b3c@ha
		opword 0xC0410010
		lfs f1, float_3p1416_rsh_00013b3c@l(r3)
		lis r4, float_0p4967_rsh_00013b4c@ha
		opword 0xC01F008C
		lis r5, float_0p03705_rsh_00013b48@ha
		opword 0xFC050840
		lis r3, float_1_rsh_00013b38@ha
		opword 0xEC02013A
		lfs f4, float_0p03705_rsh_00013b48@l(r5)
		lfs f3, float_0p4967_rsh_00013b4c@l(r4)
		lfs f2, float_1_rsh_00013b38@l(r3)
		opword 0xD01F008C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_00013b40@ha
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
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
		lis r3, float_4p7124_rsh_00013b44@ha
		lfs f0, float_4p7124_rsh_00013b44@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_00013b40@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_00013b40@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xC0210010
		lis r3, float_1_rsh_00013b38@ha
		opword 0xC01F0094
		addi r4, r3, float_1_rsh_00013b38@l
		opword 0xC0610008
		lis r3, zero_rsh_00013b20@ha
		opword 0xEC81013C
		opword 0xC021000C
		opword 0xEC43F828
		opword 0xC0040000
		opword 0xD09F0094
		opword 0xEC210028
		lfs f0, zero_rsh_00013b20@l(r3)
		opword 0xC09F0090
		opword 0xD0410008
		opword 0xFC010040
		opword 0xEC44182A
		opword 0xD021000C
		opword 0xD05F0090
		opword 0x40800050
		lis r4, vec3_rsh_00013794@ha
		opword 0x38600001
		addi r5, r4, vec3_rsh_00013794@l
		opword 0x80050000
		opword 0x80850004
		opword 0x90010014
		opword 0x80050008
		opword 0x90810018
		opword 0xD3A10014
		opword 0x9001001C
		opword 0x80010014
		opword 0xD3C10018
		opword 0xD381001C
		opword 0x80810018
		opword 0x901F008C
		opword 0x8001001C
		opword 0x909F0090
		opword 0x901F0094
		opword 0x48000018
		opword 0x8081000C
		opword 0x38600000
		opword 0x80010008
		opword 0x909E0078
		opword 0x901E007C
		opword 0xE3E10088
		opword 0xCBE10080
		opword 0xE3C10078
		opword 0xCBC10070
		opword 0xE3A10068
		opword 0xCBA10060
		opword 0xE3810058
		opword 0xCB810050
		opword 0xBB810040
		opword 0x80010094
		opword 0x7C0803A6
		opword 0x38210090
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset


static EVT_BEGIN(evt_moamoa_init)
#ifdef NONMATCHING
    CALL(evt_npc_entry, STRING(((char*)str_00003D00)), STRING(((char*)str_00003BB8)))
    CALL(evt_npc_set_position, STRING(((char*)str_00003D00)), 0, -1000, 0)
    CALL(evt_npc_entry, STRING(((char*)str_00003D08)), STRING(((char*)str_00003BCC)))
    CALL(evt_npc_set_position, STRING(((char*)str_00003D08)), 0, -1000, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_entry, STRING(((char*)rsh_05_str_00003D00)), STRING(((char*)rsh_05_str_00003BB8)))
    CALL(evt_npc_set_position, STRING(((char*)rsh_05_str_00003D00)), 0, -1000, 0)
    CALL(evt_npc_entry, STRING(((char*)rsh_05_str_00003D08)), STRING(((char*)rsh_05_str_00003BCC)))
    CALL(evt_npc_set_position, STRING(((char*)rsh_05_str_00003D08)), 0, -1000, 0)
#endif
    CALL(evt_ext_entry, 400, PTR(ext_moamoa_data), PTR(ext_moamoa_init), PTR(ext_moamoa_main), PTR(ext_moamoa_dispent))
    CALL(evt_moamoa_flag_onoff, 1, 1)
    IF_INT_EQUAL(GSWF(3450), 1)
        CALL(evt_moamoa_target_off, 0)
#ifdef NONMATCHING
        CALL(evt_npc_change_interrupt, STRING(((char*)str_00003D10)), 6, PTR(talk_waitless))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_change_interrupt, STRING(((char*)rsh_05_str_00003D10)), 6, PTR(talk_waitless))
#endif
    END_IF
    IF_INT_EQUAL(GSWF(3451), 1)
        CALL(evt_moamoa_target_off, 1)
#ifdef NONMATCHING
        CALL(evt_npc_change_interrupt, STRING(((char*)str_00003D20)), 6, PTR(talk_syashou))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_change_interrupt, STRING(((char*)rsh_05_str_00003D20)), 6, PTR(talk_syashou))
#endif
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(evt_meet_moamoa)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1500)
    CALL(evt_party_stop, 0)
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_00003D10)), STRING(((char*)str_00003BE4)))
    CALL(evt_npc_set_anim, STRING(((char*)str_00003D20)), STRING(((char*)str_00003BE4)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)rsh_05_str_00003D10)), STRING(((char*)rsh_05_str_00003BE4)))
    CALL(evt_npc_set_anim, STRING(((char*)rsh_05_str_00003D20)), STRING(((char*)rsh_05_str_00003BE4)))
#endif
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00003D28)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)str_00003D44)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, STRING(((char*)str_00003D4C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)rsh_05_str_00003D28)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)rsh_05_str_00003D44)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, STRING(((char*)rsh_05_str_00003D4C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#endif
    WAIT_MS(1000)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00003D54)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003D54)), 0, 0)
#endif
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
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00003D64)), 0, STRING(((char*)str_00003D74)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003D64)), 0, STRING(((char*)rsh_05_str_00003D74)))
#endif
        CASE_EQUAL(2)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00003D7C)), 0, STRING(((char*)str_00003D74)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00003D7C)), 0, STRING(((char*)rsh_05_str_00003D74)))
#endif
        CASE_EQUAL(4)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00003D8C)), 0, STRING(((char*)str_00003D74)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003D8C)), 0, STRING(((char*)rsh_05_str_00003D74)))
#endif
        CASE_EQUAL(5)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00003D9C)), 0, STRING(((char*)str_00003D74)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003D9C)), 0, STRING(((char*)rsh_05_str_00003D74)))
#endif
        CASE_EQUAL(6)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00003DAC)), 0, STRING(((char*)str_00003D74)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003DAC)), 0, STRING(((char*)rsh_05_str_00003D74)))
#endif
        CASE_EQUAL(3)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00003DBC)), 0, STRING(((char*)str_00003D74)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003DBC)), 0, STRING(((char*)rsh_05_str_00003D74)))
#endif
        CASE_EQUAL(7)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00003DCC)), 0, STRING(((char*)str_00003D74)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003DCC)), 0, STRING(((char*)rsh_05_str_00003D74)))
#endif
    END_SWITCH
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    SET_VALUE(GSW(0), 330)
    RETURN
EVT_END()

EVT_BEGIN(evt_moamoa_help)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 0, LW(0), 512)
#ifdef NONMATCHING
        IF_STR_EQUAL(LW(0), STRING(((char*)str_00003D20)))
            CALL(evt_msg_print, 0, STRING(((char*)str_00003DDC)), 0, LW(0))
#endif
#ifndef NONMATCHING
        IF_STR_EQUAL(LW(0), STRING(((char*)rsh_05_str_00003D20)))
            CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003DDC)), 0, LW(0))
#endif
            ELSE
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_00003DEC)), 0, LW(0))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003DEC)), 0, LW(0))
#endif
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
#ifdef NONMATCHING
    MULTIPLY_FLOAT(LW(5), FLOAT(30.0f))
    MULTIPLY_FLOAT(LW(6), FLOAT(30.0f))
#endif
#ifndef NONMATCHING
    MULTIPLY_FLOAT(LW(5), FLOAT((30.0f)))
    MULTIPLY_FLOAT(LW(6), FLOAT((30.0f)))
#endif
    ADD_FLOAT(LW(1), LW(5))
    SUBTRACT_FLOAT(LW(3), LW(6))
#ifdef NONMATCHING
    CALL(npc_jump, LW(0), LW(1), LW(2), LW(3), FLOAT(0.0f), FLOAT(0.5f), 400)
#endif
#ifndef NONMATCHING
    CALL(npc_jump, LW(0), LW(1), LW(2), LW(3), FLOAT((0.0f)), FLOAT((0.5f)), 400)
#endif
    CALL(evt_sub_get_sincos, LW(4), LW(5), LW(6))
#ifdef NONMATCHING
    MULTIPLY_FLOAT(LW(5), FLOAT(20.0f))
    MULTIPLY_FLOAT(LW(6), FLOAT(20.0f))
#endif
#ifndef NONMATCHING
    MULTIPLY_FLOAT(LW(5), FLOAT((20.0f)))
    MULTIPLY_FLOAT(LW(6), FLOAT((20.0f)))
#endif
    ADD_FLOAT(LW(1), LW(5))
    SUBTRACT_FLOAT(LW(3), LW(6))
#ifdef NONMATCHING
    CALL(npc_jump, LW(0), LW(1), LW(2), LW(3), FLOAT(0.0f), FLOAT(0.2998047f), 200)
#endif
#ifndef NONMATCHING
    CALL(npc_jump, LW(0), LW(1), LW(2), LW(3), FLOAT((0.0f)), FLOAT(0.2998047f), 200)
#endif
    CALL(evt_sub_get_sincos, LW(4), LW(5), LW(6))
#ifdef NONMATCHING
    MULTIPLY_FLOAT(LW(5), FLOAT(10.0f))
    MULTIPLY_FLOAT(LW(6), FLOAT(10.0f))
#endif
#ifndef NONMATCHING
    MULTIPLY_FLOAT(LW(5), FLOAT((10.0f)))
    MULTIPLY_FLOAT(LW(6), FLOAT((10.0f)))
#endif
    ADD_FLOAT(LW(1), LW(5))
    SUBTRACT_FLOAT(LW(3), LW(6))
#ifdef NONMATCHING
    CALL(npc_jump, LW(0), LW(1), LW(2), LW(3), FLOAT(0.0f), FLOAT(0.19921875f), 100)
#endif
#ifndef NONMATCHING
    CALL(npc_jump, LW(0), LW(1), LW(2), LW(3), FLOAT((0.0f)), FLOAT(0.19921875f), 100)
#endif
    CALL(evt_npc_flag_onoff, 1, LW(0), 1024)
    CALL(evt_npc_flag_onoff, 0, LW(0), 32)
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(10), STRING(((char*)str_00003D20)))
        CALL(evt_npc_set_anim, LW(10), STRING(((char*)str_00003C00)))
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(10), STRING(((char*)rsh_05_str_00003D20)))
        CALL(evt_npc_set_anim, LW(10), STRING(((char*)rsh_05_str_00003C00)))
#endif
        ELSE
#ifdef NONMATCHING
        CALL(evt_npc_set_anim, LW(10), STRING(((char*)str_00003DFC)))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_anim, LW(10), STRING(((char*)rsh_05_str_00003DFC)))
#endif
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_moamoa_escape0)
#ifdef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)str_00003D10)))
#endif
#ifndef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)rsh_05_str_00003D10)))
#endif
    SPAWN_EVENT(PTR(evt_moamoa_help))
    SET_VALUE(GSWF(3450), 1)
#ifdef NONMATCHING
    CALL(evt_npc_change_interrupt, STRING(((char*)str_00003D10)), 6, PTR(talk_waitless))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_change_interrupt, STRING(((char*)rsh_05_str_00003D10)), 6, PTR(talk_waitless))
#endif
    RETURN
EVT_END()

EVT_BEGIN(evt_moamoa_escape1)
#ifdef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)str_00003D20)))
#endif
#ifndef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)rsh_05_str_00003D20)))
#endif
    SPAWN_EVENT(PTR(evt_moamoa_help))
    SET_VALUE(GSWF(3451), 1)
#ifdef NONMATCHING
    CALL(evt_npc_change_interrupt, STRING(((char*)str_00003D20)), 6, PTR(talk_syashou))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_change_interrupt, STRING(((char*)rsh_05_str_00003D20)), 6, PTR(talk_syashou))
#endif
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
#ifdef NONMATCHING
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00003D20)), 32)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00003D10)), 32)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_05_str_00003D20)), 32)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_05_str_00003D10)), 32)
#endif
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_status_onoff, 1, STRING(((char*)str_00003D20)), 2)
        CALL(evt_npc_move_position, STRING(((char*)str_00003D20)), -80, 22, 1000, 0, 1)
        CALL(evt_npc_set_ry, STRING(((char*)str_00003D20)), 90)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_status_onoff, 1, STRING(((char*)rsh_05_str_00003D20)), 2)
        CALL(evt_npc_move_position, STRING(((char*)rsh_05_str_00003D20)), -80, 22, 1000, 0, 1)
        CALL(evt_npc_set_ry, STRING(((char*)rsh_05_str_00003D20)), 90)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_status_onoff, 1, STRING(((char*)str_00003D10)), 2)
        CALL(evt_npc_move_position, STRING(((char*)str_00003D10)), 0, 15, 1000, 0, 1)
        CALL(evt_npc_set_ry, STRING(((char*)str_00003D10)), 270)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_status_onoff, 1, STRING(((char*)rsh_05_str_00003D10)), 2)
        CALL(evt_npc_move_position, STRING(((char*)rsh_05_str_00003D10)), 0, 15, 1000, 0, 1)
        CALL(evt_npc_set_ry, STRING(((char*)rsh_05_str_00003D10)), 270)
#endif
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
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00003E00)), 0, STRING(((char*)str_00003D20)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003E00)), 0, STRING(((char*)rsh_05_str_00003D20)))
#endif
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 90, 300)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 90, 300, 0)
    END_INLINE_EVENT
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00003E10)), 0, STRING(((char*)str_00003D10)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003E10)), 0, STRING(((char*)rsh_05_str_00003D10)))
#endif
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 270, 300)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 270, 300, 0)
    END_INLINE_EVENT
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00003E20)), 0, STRING(((char*)str_00003D20)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003E20)), 0, STRING(((char*)rsh_05_str_00003D20)))
#endif
    WAIT_MS(500)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
#ifdef NONMATCHING
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00003D20)), 32)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00003D10)), 32)
    CALL(evt_npc_change_interrupt, STRING(((char*)str_00003D20)), 6, PTR(talk_syashou))
    CALL(evt_npc_change_interrupt, STRING(((char*)str_00003D10)), 6, PTR(talk_waitless))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)rsh_05_str_00003D20)), 32)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)rsh_05_str_00003D10)), 32)
    CALL(evt_npc_change_interrupt, STRING(((char*)rsh_05_str_00003D20)), 6, PTR(talk_syashou))
    CALL(evt_npc_change_interrupt, STRING(((char*)rsh_05_str_00003D10)), 6, PTR(talk_waitless))
#endif
    SET_VALUE(GSW(0), 331)
#ifdef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)str_00003E30)))
#endif
#ifndef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)rsh_05_str_00003E30)))
#endif
    CALL_CHILD(PTR(bero_case_switch_on))
    RETURN
EVT_END()

static EVT_BEGIN(init_syashou)
    SWITCH(GSW(0))
        CASE_BETWEEN(329, 332)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_00003E38)), -115, 0, 20)
        CALL(evt_npc_set_autotalkpose, STRING(((char*)str_00003E38)), STRING(((char*)str_00003C00)), STRING(((char*)str_00003E3C)))
        CALL(evt_npc_set_tribe, STRING(((char*)str_00003E38)), STRING(((char*)str_00003E40)))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)rsh_05_str_00003E38)), -115, 0, 20)
        CALL(evt_npc_set_autotalkpose, STRING(((char*)rsh_05_str_00003E38)), STRING(((char*)rsh_05_str_00003C00)), STRING(((char*)rsh_05_str_00003E3C)))
        CALL(evt_npc_set_tribe, STRING(((char*)rsh_05_str_00003E38)), STRING(((char*)rsh_05_str_00003E40)))
#endif
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_00003E38)), 0, -1000, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)rsh_05_str_00003E38)), 0, -1000, 0)
#endif
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_syashou)
    IF_INT_LESS(GSW(0), 331)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003E48)), 0, 0)
        ELSE
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00003E5C)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003E5C)), 0, 0)
#endif
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(init_waitless)
    SWITCH(GSW(0))
        CASE_BETWEEN(329, 332)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_00003E38)), 50, 0, 0)
        CALL(evt_npc_set_autotalkpose, STRING(((char*)str_00003E38)), STRING(((char*)str_00003DFC)), STRING(((char*)str_00003E6C)))
        CALL(evt_npc_set_tribe, STRING(((char*)str_00003E38)), STRING(((char*)str_00003E70)))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)rsh_05_str_00003E38)), 50, 0, 0)
        CALL(evt_npc_set_autotalkpose, STRING(((char*)rsh_05_str_00003E38)), STRING(((char*)rsh_05_str_00003DFC)), STRING(((char*)rsh_05_str_00003E6C)))
        CALL(evt_npc_set_tribe, STRING(((char*)rsh_05_str_00003E38)), STRING(((char*)rsh_05_str_00003E70)))
#endif
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_00003E38)), 0, -1000, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)rsh_05_str_00003E38)), 0, -1000, 0)
#endif
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_waitless)
    IF_INT_LESS(GSW(0), 331)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00003E80)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003E80)), 0, 0)
#endif
        ELSE
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00003E94)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003E94)), 0, 0)
#endif
    END_IF
    RETURN
EVT_END()

static s32 bero_data_a[] = {
#ifdef NONMATCHING
    (s32)((char*)str_00003EA4), 65544, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)str_00003EAC), (s32)((char*)str_00003E30), 65537, (s32)((char*)str_00003EB8), (s32)((char*)str_00003EC8), (s32)((char*)str_00003E30),
#endif
#ifndef NONMATCHING
    (s32)((char*)rsh_05_str_00003EA4), 65544, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)rsh_05_str_00003EAC), (s32)((char*)rsh_05_str_00003E30), 65537, (s32)((char*)rsh_05_str_00003EB8), (s32)((char*)rsh_05_str_00003EC8), (s32)((char*)rsh_05_str_00003E30),
#endif
    0, 20000, 100000, 0, 0, -1, 0, -1,
#ifdef NONMATCHING
    0, (s32)((char*)str_00003ED4), (s32)((char*)str_00003E30), 65537, 0, 0, 0, 0,
#endif
#ifndef NONMATCHING
    0, (s32)((char*)str_00003ED4), (s32)((char*)rsh_05_str_00003E30), 65537, 0, 0, 0, 0,
#endif
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static s32 bero_data_b[] = {
#ifdef NONMATCHING
    (s32)((char*)str_00003EA4), 65544, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)str_00003EE0), (s32)((char*)str_00003E30), 65537, (s32)((char*)str_00003EB8), (s32)((char*)str_00003EC8), (s32)((char*)str_00003E30),
#endif
#ifndef NONMATCHING
    (s32)((char*)rsh_05_str_00003EA4), 65544, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)rsh_05_str_00003EE0), (s32)((char*)rsh_05_str_00003E30), 65537, (s32)((char*)rsh_05_str_00003EB8), (s32)((char*)rsh_05_str_00003EC8), (s32)((char*)rsh_05_str_00003E30),
#endif
    0, 20000, 100000, 0, 0, -1, 0, -1,
#ifdef NONMATCHING
    0, (s32)((char*)str_00003ED4), (s32)((char*)str_00003E30), 65537, 0, 0, 0, 0,
#endif
#ifndef NONMATCHING
    0, (s32)((char*)str_00003ED4), (s32)((char*)rsh_05_str_00003E30), 65537, 0, 0, 0, 0,
#endif
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static s32 bero_data_c[] = {
#ifdef NONMATCHING
    (s32)((char*)str_00003EA4), 65544, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)str_00003EEC), (s32)((char*)str_00003E30), 65537, (s32)((char*)str_00003EB8), (s32)((char*)str_00003EC8), (s32)((char*)str_00003E30),
#endif
#ifndef NONMATCHING
    (s32)((char*)rsh_05_str_00003EA4), 65544, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)rsh_05_str_00003EEC), (s32)((char*)rsh_05_str_00003E30), 65537, (s32)((char*)rsh_05_str_00003EB8), (s32)((char*)rsh_05_str_00003EC8), (s32)((char*)rsh_05_str_00003E30),
#endif
    0, 20000, 100000, 0, 0, -1, 0, -1,
#ifdef NONMATCHING
    0, (s32)((char*)str_00003ED4), (s32)((char*)str_00003E30), 65537, 0, 0, 0, 0,
#endif
#ifndef NONMATCHING
    0, (s32)((char*)str_00003ED4), (s32)((char*)rsh_05_str_00003E30), 65537, 0, 0, 0, 0,
#endif
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static s32 npc_data[] = {
#ifdef NONMATCHING
    (s32)/*"車掌"*/(char*)str_00003D20, 1536, 0, (s32)init_syashou, 0, 0, 0, 0,
#endif
#ifndef NONMATCHING
    (s32)/*"車掌"*/(char*)rsh_05_str_00003D20, 1536, 0, (s32)init_syashou, 0, 0, 0, 0,
#endif
    0, 0, 0, 0, 0, 0, 0, 0,
#ifdef NONMATCHING
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ウェイトレス"*/(char*)str_00003D10,
#endif
#ifndef NONMATCHING
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ウェイトレス"*/(char*)rsh_05_str_00003D10,
#endif
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
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00003EF8)), 0, 0)
    CALL(evt_msg_select, 0, STRING(((char*)str_00003F08)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003EF8)), 0, 0)
    CALL(evt_msg_select, 0, STRING(((char*)rsh_05_str_00003F08)))
#endif
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
#ifdef NONMATCHING
    CALL(evt_msg_print_add, 0, STRING(((char*)str_00003F18)))
    CALL(evt_msg_select, 0, STRING(((char*)str_00003F08)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_add, 0, STRING(((char*)rsh_05_str_00003F18)))
    CALL(evt_msg_select, 0, STRING(((char*)rsh_05_str_00003F08)))
#endif
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
#ifdef NONMATCHING
    CALL(evt_msg_print_add, 0, STRING(((char*)str_00003F28)))
    CALL(evt_msg_select, 0, STRING(((char*)str_00003F08)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_add, 0, STRING(((char*)rsh_05_str_00003F28)))
    CALL(evt_msg_select, 0, STRING(((char*)rsh_05_str_00003F08)))
#endif
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
#ifdef NONMATCHING
    CALL(evt_msg_print_add, 0, STRING(((char*)str_00003F38)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00003F48)), 0, STRING(((char*)str_00003F58)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_add, 0, STRING(((char*)rsh_05_str_00003F38)))
    CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003F48)), 0, STRING(((char*)rsh_05_str_00003F58)))
#endif
    RETURN
EVT_END()

static s32 access_tbl[] = {
#ifdef NONMATCHING
    (s32)((char*)str_00003F64), (s32)((char*)str_00003F70), (s32)((char*)str_00003F80), (s32)((char*)str_00003F70), (s32)((char*)str_00003F8C), (s32)((char*)str_00003F94), (s32)((char*)str_00003FA4), (s32)((char*)str_00003FAC),
    (s32)((char*)str_00003FBC), (s32)((char*)str_00003FC4), (s32)((char*)str_00003FD4), (s32)((char*)str_00003FC4), 0,
#endif
#ifndef NONMATCHING
    (s32)((char*)rsh_05_str_00003F64), (s32)((char*)rsh_05_str_00003F70), (s32)((char*)rsh_05_str_00003F80), (s32)((char*)rsh_05_str_00003F70), (s32)((char*)str_00003F8C), (s32)((char*)rsh_05_str_00003F94), (s32)((char*)rsh_05_str_00003FA4), (s32)((char*)str_00003FAC),
    (s32)((char*)rsh_05_str_00003FBC), (s32)((char*)rsh_05_str_00003FC4), (s32)((char*)rsh_05_str_00003FD4), (s32)((char*)rsh_05_str_00003FC4), 0,
#endif
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
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00003FDC)), 0, 0)
        CALL(evt_item_entry, STRING(((char*)str_00003FEC)), 142, 0, -1000, 0, 17, -1, 0)
        CALL(evt_item_get_item, STRING(((char*)str_00003FEC)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003FDC)), 0, 0)
        CALL(evt_item_entry, STRING(((char*)rsh_05_str_00003FEC)), 142, 0, -1000, 0, 17, -1, 0)
        CALL(evt_item_get_item, STRING(((char*)rsh_05_str_00003FEC)))
#endif
        CALL(evt_mario_key_onoff, 1)
        ELSE
        CALL(evt_mario_key_onoff, 0)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00003FF0)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)rsh_05_str_00003FF0)), 0, 0)
#endif
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
#ifdef NONMATCHING
    CALL(evt_run_case_evt, 9, 1, STRING(((char*)str_00004000)), 0, PTR(evt_access2), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_run_case_evt, 9, 1, STRING(((char*)rsh_05_str_00004000)), 0, PTR(evt_access2), 0)
#endif
    RETURN
EVT_END()

EVT_BEGIN(rsh_05_init_evt)
    SWITCH(GSW(0))
        CASE_BETWEEN(310, 325)
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_map_playanim, STRING(((char*)str_00004008)), 1, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_map_playanim, STRING(((char*)rsh_05_str_00004008)), 1, 0)
#endif
    END_SWITCH
    CALL_CHILD(PTR(evt_access_entry))
    SWITCH(GSW(0))
        CASE_BETWEEN(284, 286)
#ifdef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004010)))
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004020)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)rsh_05_str_00004010)))
        CALL(evt_snd_envon, 272, STRING(((char*)rsh_05_str_00004020)))
#endif
        CASE_BETWEEN(304, 309)
#ifdef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004010)))
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004020)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)rsh_05_str_00004010)))
        CALL(evt_snd_envon, 272, STRING(((char*)rsh_05_str_00004020)))
#endif
        CASE_BETWEEN(310, 325)
#ifdef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004030)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)rsh_05_str_00004030)))
#endif
        CALL(evt_snd_envoff, 512)
        CALL(evt_snd_bgmoff, 26624)
        CASE_BETWEEN(327, 328)
        CALL(evt_snd_bgmoff, 512)
#ifdef NONMATCHING
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004020)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_envon, 272, STRING(((char*)rsh_05_str_00004020)))
#endif
        CASE_BETWEEN(329, 331)
#ifdef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004040)))
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004020)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)rsh_05_str_00004040)))
        CALL(evt_snd_envon, 272, STRING(((char*)rsh_05_str_00004020)))
#endif
        CASE_BETWEEN(334, 344)
#ifdef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004050)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)rsh_05_str_00004050)))
#endif
        CALL(evt_snd_envoff, 512)
        CALL(evt_snd_bgmoff, 26624)
        CASE_DEFAULT
        CALL(evt_snd_bgmoff, 512)
#ifdef NONMATCHING
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004020)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_envon, 272, STRING(((char*)rsh_05_str_00004020)))
#endif
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
#ifdef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)str_00003E30)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)rsh_05_str_00003E30)))
#endif
        CALL_CHILD(PTR(bero_case_switch_off))
        CASE_EQUAL(329)
        CALL_CHILD(PTR(evt_moamoa_init))
        SPAWN_EVENT(PTR(evt_meet_moamoa))
#ifdef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)str_00003E30)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)rsh_05_str_00003E30)))
#endif
        CALL_CHILD(PTR(bero_case_switch_off))
        CASE_EQUAL(330)
        CALL_CHILD(PTR(evt_moamoa_init))
#ifdef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)str_00003E30)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)rsh_05_str_00003E30)))
#endif
        CALL_CHILD(PTR(bero_case_switch_off))
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_npc_change_interrupt, STRING(((char*)str_00003D20)), 6, PTR(talk_syashou))
        CALL(evt_npc_change_interrupt, STRING(((char*)str_00003D10)), 6, PTR(talk_waitless))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_change_interrupt, STRING(((char*)rsh_05_str_00003D20)), 6, PTR(talk_syashou))
        CALL(evt_npc_change_interrupt, STRING(((char*)rsh_05_str_00003D10)), 6, PTR(talk_waitless))
#endif
    END_SWITCH
    IF_INT_LESS(GSW(0), 299)
#ifdef NONMATCHING
        CALL(evt_item_entry, STRING(((char*)str_00004060)), 78, -90, 0, -140, 0, -1, PTR(evt_ghost_diary))
#endif
#ifndef NONMATCHING
        CALL(evt_item_entry, STRING(((char*)rsh_05_str_00004060)), 78, -90, 0, -140, 0, -1, PTR(evt_ghost_diary))
#endif
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(rsh_05_init_evt_nidome)
    IF_INT_EQUAL(GSWF(3579), 0)
        IF_INT_EQUAL(GSWF(3580), 0)
            IF_INT_EQUAL(GSWF(3581), 0)
#ifdef NONMATCHING
                CALL(evt_map_playanim, STRING(((char*)str_00004008)), 1, 0)
#endif
#ifndef NONMATCHING
                CALL(evt_map_playanim, STRING(((char*)rsh_05_str_00004008)), 1, 0)
#endif
            END_IF
        END_IF
    END_IF
    CALL(evt_npc_setup, PTR(npc_data))
    IF_INT_EQUAL(GSWF(3460), 1)
#ifdef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004050)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)rsh_05_str_00004050)))
#endif
        CALL(evt_snd_envoff, 512)
        CALL(evt_snd_bgmoff, 26624)
        ELSE
        IF_INT_EQUAL(GSWF(3461), 1)
#ifdef NONMATCHING
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004068)))
#endif
#ifndef NONMATCHING
            CALL(evt_snd_bgmon, 512, STRING(((char*)rsh_05_str_00004068)))
#endif
            CALL(evt_snd_envoff, 512)
            CALL(evt_snd_bgmoff, 26624)
            ELSE
            CALL(evt_snd_bgmoff, 512)
#ifdef NONMATCHING
            CALL(evt_snd_envon, 272, STRING(((char*)str_00004020)))
#endif
#ifndef NONMATCHING
            CALL(evt_snd_envon, 272, STRING(((char*)rsh_05_str_00004020)))
#endif
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

// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const char rsh_05_str_00003BB8[11] = "c_n_moa_a\0\0";
__declspec(section ".rodata") const char str_00003BC4[4] = "S_1";
__declspec(section ".rodata") const char rsh_05_str_00003BC8[4] = "D_1";
__declspec(section ".rodata") const char rsh_05_str_00003BCC[11] = "c_n_moa_b\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003BD8[11] = "c_kinodebu\0";
__declspec(section ".rodata") const char rsh_05_str_00003BE4[4] = "G_1";
__declspec(section ".rodata") const char rsh_05_str_00003BE8[11] = "c_puku_c\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003BF4[4] = "U_1";
__declspec(section ".rodata") const char rsh_05_str_00003BF8[8] = "c_powan";
__declspec(section ".rodata") const char rsh_05_str_00003C00[4] = "O_1";
__declspec(section ".rodata") const char rsh_05_str_00003C04[8] = "c_smoko";
__declspec(section ".rodata") const char rsh_05_str_00003C0C[4] = "T_2";
__declspec(section ".rodata") const char rsh_05_str_00003C10[7] = "c_rose\0";
__declspec(section ".rodata") const char rsh_05_str_00003C18[8] = "c_papab";
__declspec(section ".rodata") const char rsh_05_str_00003C20[8] = "c_mamab";
__declspec(section ".rodata") const char rsh_05_str_00003C28[11] = "c_konari\0\0\0";
__declspec(section ".rodata") const f32 vec3_rsh_000136d4[3] = {-290.0f, 65.0f, -95.0f};
__declspec(section ".rodata") const f32 vec3_rsh_000136e0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_000136ec[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_000136f8[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013704[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013710[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_0001371c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013728[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013734[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013740[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_0001374c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013758[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013764[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013770[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_0001377c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013788[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013794[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const char rsh_05_str_00003D00[7] = "moa_a\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003D08[7] = "moa_b\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003D10[15] = "\x83" "E\x83" "F\x83" "C\x83g\x83\x8c\x83X\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003D20[7] = "\x8e\xd4\x8f\xb6\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003D28[27] = "SFX_VOICE_MARIO_SURPRISED2\0";
__declspec(section ".rodata") const char rsh_05_str_00003D44[7] = "eff0\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003D4C[7] = "eff1\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003D54[15] = "stg6_rsh_237\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003D64[15] = "stg6_rsh_238_0\0";
__declspec(section ".rodata") const char rsh_05_str_00003D74[7] = "party\0\0";
__declspec(section ".rodata") const char str_00003D7C[15] = "stg6_rsh_238_1\0";
__declspec(section ".rodata") const char rsh_05_str_00003D8C[15] = "stg6_rsh_238_2\0";
__declspec(section ".rodata") const char rsh_05_str_00003D9C[15] = "stg6_rsh_238_3\0";
__declspec(section ".rodata") const char rsh_05_str_00003DAC[15] = "stg6_rsh_238_4\0";
__declspec(section ".rodata") const char rsh_05_str_00003DBC[15] = "stg6_rsh_238_5\0";
__declspec(section ".rodata") const char rsh_05_str_00003DCC[15] = "stg6_rsh_238_6\0";
__declspec(section ".rodata") const char rsh_05_str_00003DDC[16] = "stg6_rsh_249_00";
__declspec(section ".rodata") const char rsh_05_str_00003DEC[16] = "stg6_rsh_249_01";
__declspec(section ".rodata") const char rsh_05_str_00003DFC[4] = "P_1";
__declspec(section ".rodata") const char rsh_05_str_00003E00[16] = "stg6_rsh_240_00";
__declspec(section ".rodata") const char rsh_05_str_00003E10[15] = "stg6_rsh_241\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003E20[16] = "stg6_rsh_240_01";
__declspec(section ".rodata") const char rsh_05_str_00003E30[7] = "w_bero\0";
__declspec(section ".rodata") const char rsh_05_str_00003E38[3] = "me\0";
__declspec(section ".rodata") const char rsh_05_str_00003E3C[4] = "T_3";
__declspec(section ".rodata") const char rsh_05_str_00003E40[7] = "\x8e\xd4\x8f\xb6\x94\xdf\0";
__declspec(section ".rodata") const char str_00003E48[19] = "stg6_rsh_249_01_01\0";
__declspec(section ".rodata") const char rsh_05_str_00003E5C[15] = "stg6_rsh_242\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003E6C[4] = "T_5";
__declspec(section ".rodata") const char rsh_05_str_00003E70[15] = "\x83" "E\x83" "F\x83" "C\x83g\x83\x8c\x83X\x94\xdf\0";
__declspec(section ".rodata") const char rsh_05_str_00003E80[19] = "stg6_rsh_249_01_02\0";
__declspec(section ".rodata") const char rsh_05_str_00003E94[15] = "stg6_rsh_243\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003EA4[7] = "e_bero\0";
__declspec(section ".rodata") const char rsh_05_str_00003EAC[11] = "rsh_04_a\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003EB8[15] = "e_door_close\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003EC8[12] = "e_door_open";
__declspec(section ".rodata") const char str_00003ED4[11] = "rsh_06_a\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003EE0[11] = "rsh_04_b\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003EEC[11] = "rsh_04_c\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003EF8[15] = "stg6_rsh_130\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003F08[16] = "stg6_rsh_130_yn";
__declspec(section ".rodata") const char rsh_05_str_00003F18[15] = "stg6_rsh_131\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003F28[15] = "stg6_rsh_132\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003F38[15] = "stg6_rsh_133\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003F48[15] = "stg6_rsh_134\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003F58[11] = "\x82\xe4\x82\xa4\x82\xea\x82\xa2\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003F64[11] = "kihako_1\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003F70[15] = "stg6_rsh_275\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003F80[11] = "kibako_2\0\0\0";
__declspec(section ".rodata") const char str_00003F8C[7] = "bin_1\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003F94[15] = "stg6_rsh_276\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003FA4[7] = "wagon\0\0";
__declspec(section ".rodata") const char str_00003FAC[15] = "stg6_rsh_280\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003FBC[7] = "hako_1\0";
__declspec(section ".rodata") const char rsh_05_str_00003FC4[15] = "stg6_rsh_281\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003FD4[7] = "hako_2\0";
__declspec(section ".rodata") const char rsh_05_str_00003FDC[15] = "stg6_rsh_277\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003FEC[3] = "a\0\0";
__declspec(section ".rodata") const char rsh_05_str_00003FF0[15] = "stg6_rsh_279\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00004000[7] = "bin_2\0\0";
__declspec(section ".rodata") const char rsh_05_str_00004008[7] = "yure\0\0\0";
__declspec(section ".rodata") const char rsh_05_str_00004010[15] = "BGM_EVT_POWAN1\0";
__declspec(section ".rodata") const char rsh_05_str_00004020[16] = "ENV_STG6_RSH1_3";
__declspec(section ".rodata") const char rsh_05_str_00004030[15] = "BGM_STG6_HOM1\0\0";
__declspec(section ".rodata") const char rsh_05_str_00004040[16] = "BGM_EVT_DANGER4";
__declspec(section ".rodata") const char rsh_05_str_00004050[15] = "BGM_STG6_PIK1\0\0";
__declspec(section ".rodata") const char rsh_05_str_00004060[7] = "diary\0\0";
__declspec(section ".rodata") const char rsh_05_str_00004068[15] = "BGM_STG0_GOR1\0\0";
__declspec(section ".rodata") const f32 float_60_rsh_00013b18[1] = {60.0f};
__declspec(section ".rodata") const f32 float_1000_rsh_00013b1c[1] = {1000.0f};
__declspec(section ".rodata") const f32 zero_rsh_00013b20[1] = {0.0f};
__declspec(section ".rodata") const f32 float_0p5_rsh_00013b24[1] = {0.5f};
__declspec(section ".rodata") const f32 float_6p2832_rsh_00013b28[1] = {6.2831855f};
__declspec(section ".rodata") const f32 float_360_rsh_00013b2c[1] = {360.0f};
__declspec(section ".rodata") const f32 float_0p00761_rsh_00013b30 = 0.00761f;
__declspec(section ".rodata") const f32 float_0p16605_rsh_00013b34 = 0.16605f;
__declspec(section ".rodata") const f32 float_1_rsh_00013b38[1] = {1.0f};
__declspec(section ".rodata") const f32 float_3p1416_rsh_00013b3c = 3.1415927f;
__declspec(section ".rodata") const f32 float_1p5708_rsh_00013b40 = 1.5707964f;
__declspec(section ".rodata") const f32 float_4p7124_rsh_00013b44 = 4.712389f;
__declspec(section ".rodata") const f32 float_0p03705_rsh_00013b48 = 0.03705f;
__declspec(section ".rodata") const f32 float_0p4967_rsh_00013b4c = 0.4967f;
__declspec(section ".rodata") const f64 double_to_int_rsh_00013b50 = 4503601774854144.0;
__declspec(section ".rodata") const f32 float_neg5000_rsh_00013b58 = -5000.0f;
__declspec(section ".rodata") const f32 float_neg1_rsh_00013b5c = -1.0f;
__declspec(section ".rodata") const char rsh_05_str_000040C0[23] = "SFX_STG6_MOAMOA_VOICE1\0";
__declspec(section ".rodata") const f32 float_200_rsh_00013b78[1] = {200.0f};
__declspec(section ".rodata") const f32 float_32767_rsh_00013b7c[1] = {32767.0f};
__declspec(section ".rodata") const f32 float_0p1_rsh_00013b80[1] = {0.1f};
__declspec(section ".rodata") const f32 float_0p03_rsh_00013b84[1] = {0.03f};
__declspec(section ".rodata") const f32 float_50_rsh_00013b88[1] = {50.0f};
__declspec(section ".rodata") const f32 float_15_rsh_00013b8c[1] = {15.0f};
__declspec(section ".rodata") const f32 float_1p5_rsh_00013b90[1] = {1.5f};
__declspec(section ".rodata") const f32 float_0p8_rsh_00013b94[1] = {0.8f};
__declspec(section ".rodata") const f32 float_1p2_rsh_00013b98 = 1.2f;
__declspec(section ".rodata") const f32 float_5_rsh_00013b9c[1] = {5.0f};
__declspec(section ".rodata") const f32 float_0p3_rsh_00013ba0[1] = {0.3f};
__declspec(section ".rodata") const f32 float_0p2_rsh_00013ba4 = 0.19999999f;
__declspec(section ".rodata") const f32 float_300_rsh_00013ba8[1] = {300.0f};
__declspec(section ".rodata") const f32 float_600_rsh_00013bac[1] = {600.0f};
__declspec(section ".rodata") const f32 float_0p25_rsh_00013bb0[1] = {0.25f};
__declspec(section ".rodata") const f32 float_neg45_rsh_00013bb4 = -45.0f;
__declspec(section ".rodata") const f32 float_90_rsh_00013bb8[1] = {90.0f};
__declspec(section ".rodata") const f32 float_0p4_rsh_00013bbc[1] = {0.4f};
__declspec(section ".rodata") const f32 float_100_rsh_00013bc0[1] = {100.0f};
__declspec(section ".rodata") const f32 float_180_rsh_00013bc4[1] = {180.0f};
__declspec(section ".rodata") const f32 float_30_rsh_00013bc8[1] = {30.0f};
__declspec(section ".rodata") const f32 float_2_rsh_00013bcc[1] = {2.0f};
__declspec(section ".rodata") const f32 float_0p9_rsh_00013bd0[1] = {0.9f};
__declspec(section ".rodata") const f32 float_135_rsh_00013bd4[1] = {135.0f};
__declspec(section ".rodata") const f32 float_0p2_rsh_00013bd8[1] = {0.2f};
__declspec(section ".rodata") const f32 float_0p1_rsh_00013bdc = 0.10000001f;
__declspec(section ".rodata") const f32 float_neg100_rsh_00013be0 = -100.0f;
__declspec(section ".rodata") const f32 float_0p20944_rsh_00013be4[1] = {0.20943952f};
__declspec(section ".rodata") const f32 float_neg275_rsh_00013be8 = -275.0f;
__declspec(section ".rodata") const f32 float_6_rsh_00013bec[1] = {6.0f};
__declspec(section ".rodata") const f32 float_3_rsh_00013bf0[1] = {3.0f};
__declspec(section ".rodata") const f32 float_neg350_rsh_00013bf4 = -350.0f;
__declspec(section ".rodata") const f32 float_225_rsh_00013bf8[1] = {225.0f};
__declspec(section ".rodata") const f32 float_1p1_rsh_00013bfc[1] = {1.1f};
__declspec(section ".rodata") const f32 float_1p02_rsh_00013c00[1] = {1.02f};
__declspec(section ".rodata") const f32 float_neg1000_rsh_00013c04 = -1000.0f;
__declspec(section ".rodata") const f32 float_290_rsh_00013c08[1] = {290.0f};
__declspec(section ".rodata") const f32 float_neg290_rsh_00013c0c = -290.0f;
__declspec(section ".rodata") const f32 float_neg130_rsh_00013c10 = -130.0f;
__declspec(section ".rodata") const f64 double_to_int_mask_rsh_00013c18 = 4503599627370496.0;
__declspec(section ".rodata") const f32 float_20_rsh_00013c20[1] = {20.0f};
__declspec(section ".rodata") const f32 float_10_rsh_00013c24[1] = {10.0f};
__declspec(section ".rodata") const f32 float_35_rsh_00013c28[1] = {35.0f};
__declspec(section ".rodata") const f32 float_65_rsh_00013c2c[1] = {65.0f};
__declspec(section ".rodata") const f32 float_40_rsh_00013c30[1] = {40.0f};
__declspec(section ".rodata") const f32 float_1E06_rsh_00013c34[1] = {1000000.0f};
__declspec(section ".rodata") const f64 double_30_rsh_00013c38 = 30.0;
__declspec(section ".rodata") const char rsh_05_str_000041A0[11] = "offscreen\0\0";
__declspec(section ".rodata") const char rsh_05_str_000041AC[4] = "S_2";
__declspec(section ".rodata") const char rsh_05_str_000041B0[3] = "D\0\0";
__declspec(section ".rodata") const char rsh_05_str_000041B4[3] = "R\0\0";
__declspec(section ".rodata") const f32 float_530_rsh_00013c58 = 530.0f;
__declspec(section ".rodata") const char rsh_05_str_000041BC[7] = "ressha\0";
__declspec(section ".rodata") const char zero_rsh_00013c64[1] = { (char)0x00000000 };
__declspec(section ".rodata") const char rsh_05_str_000041C8[3] = "J\0\0";
__declspec(section ".rodata") const u32 gap_03_000041CC_rodata = 0x00000000;

// jumptables last, as the target emitted them with their functions
__declspec(section ".data") void* rsh_05_jumptable_00014F3C[] = {
    (char*)ext_moamoa_main + 0xB70,
    (char*)ext_moamoa_main + 0x15F0,
    (char*)ext_moamoa_main + 0x18E8,
    (char*)ext_moamoa_main + 0x1B4C,
    (char*)ext_moamoa_main + 0x1DA8,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x25C4,
    (char*)ext_moamoa_main + 0x2648,
    (char*)ext_moamoa_main + 0x2674,
    (char*)ext_moamoa_main + 0x2994,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x1DCC,
    (char*)ext_moamoa_main + 0x1DCC,
    (char*)ext_moamoa_main + 0x1DCC,
    (char*)ext_moamoa_main + 0x20D0,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x2130,
    (char*)ext_moamoa_main + 0x2480,
    (char*)ext_moamoa_main + 0x2510,
    (char*)ext_moamoa_main + 0x1358,
    (char*)ext_moamoa_main + 0x1384,
    (char*)ext_moamoa_main + 0x144C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x302C,
    (char*)ext_moamoa_main + 0x2C88,
    (char*)ext_moamoa_main + 0x2CB0,
    (char*)ext_moamoa_main + 0x2F3C,
    (char*)ext_moamoa_main + 0x2F60,
};
#endif
// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_04_00015044_data[1] = {0};
#pragma force_active reset

#ifdef NONMATCHING // all-C link: pool objects the C names, defined on the asm side only
__declspec(section ".data") const f64 double_30_rsh_00013c38 = 30.0;
__declspec(section ".data") const f32 float_0p03_rsh_00013b84[1] = {0.03f};
__declspec(section ".data") const f32 float_0p1_rsh_00013b80[1] = {0.1f};
__declspec(section ".data") const f32 float_0p20944_rsh_00013be4[1] = {0.20943952f};
__declspec(section ".data") const f32 float_0p25_rsh_00013bb0[1] = {0.25f};
__declspec(section ".data") const f32 float_0p2_rsh_00013bd8[1] = {0.2f};
__declspec(section ".data") const f32 float_0p3_rsh_00013ba0[1] = {0.3f};
__declspec(section ".data") const f32 float_0p4_rsh_00013bbc[1] = {0.4f};
__declspec(section ".data") const f32 float_0p5_rsh_00013b24[1] = {0.5f};
__declspec(section ".data") const f32 float_0p8_rsh_00013b94[1] = {0.8f};
__declspec(section ".data") const f32 float_0p9_rsh_00013bd0[1] = {0.9f};
__declspec(section ".data") const f32 float_1000_rsh_00013b1c[1] = {1000.0f};
__declspec(section ".data") const f32 float_100_rsh_00013bc0[1] = {100.0f};
__declspec(section ".data") const f32 float_10_rsh_00013c24[1] = {10.0f};
__declspec(section ".data") const f32 float_135_rsh_00013bd4[1] = {135.0f};
__declspec(section ".data") const f32 float_15_rsh_00013b8c[1] = {15.0f};
__declspec(section ".data") const f32 float_180_rsh_00013bc4[1] = {180.0f};
__declspec(section ".data") const f32 float_1E06_rsh_00013c34[1] = {1000000.0f};
__declspec(section ".data") const f32 float_1_rsh_00013b38[1] = {1.0f};
__declspec(section ".data") const f32 float_1p02_rsh_00013c00[1] = {1.02f};
__declspec(section ".data") const f32 float_1p1_rsh_00013bfc[1] = {1.1f};
__declspec(section ".data") const f32 float_1p5_rsh_00013b90[1] = {1.5f};
__declspec(section ".data") const f32 float_200_rsh_00013b78[1] = {200.0f};
__declspec(section ".data") const f32 float_20_rsh_00013c20[1] = {20.0f};
__declspec(section ".data") const f32 float_225_rsh_00013bf8[1] = {225.0f};
__declspec(section ".data") const f32 float_290_rsh_00013c08[1] = {290.0f};
__declspec(section ".data") const f32 float_2_rsh_00013bcc[1] = {2.0f};
__declspec(section ".data") const f32 float_300_rsh_00013ba8[1] = {300.0f};
__declspec(section ".data") const f32 float_30_rsh_00013bc8[1] = {30.0f};
__declspec(section ".data") const f32 float_32767_rsh_00013b7c[1] = {32767.0f};
__declspec(section ".data") const f32 float_35_rsh_00013c28[1] = {35.0f};
__declspec(section ".data") const f32 float_360_rsh_00013b2c[1] = {360.0f};
__declspec(section ".data") const f32 float_3_rsh_00013bf0[1] = {3.0f};
__declspec(section ".data") const f32 float_40_rsh_00013c30[1] = {40.0f};
__declspec(section ".data") const f32 float_50_rsh_00013b88[1] = {50.0f};
__declspec(section ".data") const f32 float_5_rsh_00013b9c[1] = {5.0f};
__declspec(section ".data") const f32 float_600_rsh_00013bac[1] = {600.0f};
__declspec(section ".data") const f32 float_60_rsh_00013b18[1] = {60.0f};
__declspec(section ".data") const f32 float_65_rsh_00013c2c[1] = {65.0f};
__declspec(section ".data") const f32 float_6_rsh_00013bec[1] = {6.0f};
__declspec(section ".data") const f32 float_6p2832_rsh_00013b28[1] = {6.2831855f};
__declspec(section ".data") const f32 float_90_rsh_00013bb8[1] = {90.0f};
__declspec(section ".data") const char str_00003BC4[4] = "S_1";
__declspec(section ".data") const char str_00003D7C[15] = "stg6_rsh_238_1\0";
__declspec(section ".data") const char str_00003E48[19] = "stg6_rsh_249_01_01\0";
__declspec(section ".data") const char str_00003ED4[11] = "rsh_06_a\0\0\0";
__declspec(section ".data") const char str_00003F8C[7] = "bin_1\0\0";
__declspec(section ".data") const char str_00003FAC[15] = "stg6_rsh_280\0\0\0";
__declspec(section ".data") const f32 zero_rsh_00013b20[1] = {0.0f};
__declspec(section ".data") const char zero_rsh_00013c64[1] = { (char)0x00000000 };
#endif
