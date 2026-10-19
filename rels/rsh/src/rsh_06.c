// FAKE: PREFIX asm (F2): functions 1-24 (npc_anim_wait .. moamoa_pose_main) in target order are asm with their C kept under #ifdef NONMATCHING; moamoa_pose_init stays real C. The prefix ends at moamoa_pose_main because randf/pose_main need the compiler int->float constant that the asm pool owns (cannot be shared from C). Named .rodata in target order; suffix C points at the named str_/float objects.
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
#endif
#ifndef NONMATCHING
__declspec(section ".rodata") extern const f32 vec3_rsh_00013cec[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013cf8[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013d04[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013d10[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013d1c[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013d28[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013d34[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013d40[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013d4c[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013d58[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013d64[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013d70[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013d7c[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013d88[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013d94[3];
__declspec(section ".rodata") extern const f32 vec3_rsh_00013da0[3];
__declspec(section ".rodata") extern const f64 double_to_int_mask_rsh_00014480;
__declspec(section ".rodata") extern const f64 double_to_int_rsh_00014488;
__declspec(section ".rodata") extern const f32 float_neg5000_rsh_00014494;
__declspec(section ".rodata") extern const f32 float_neg1_rsh_00014498;
__declspec(section ".rodata") extern const f32 float_0p00761_rsh_000144a4;
__declspec(section ".rodata") extern const f32 float_0p16605_rsh_000144a8;
__declspec(section ".rodata") extern const f32 float_3p1416_rsh_000144ac;
__declspec(section ".rodata") extern const f32 float_1p5708_rsh_000144b0;
__declspec(section ".rodata") extern const f32 float_4p7124_rsh_000144b4;
__declspec(section ".rodata") extern const f32 float_0p03705_rsh_000144b8;
__declspec(section ".rodata") extern const f32 float_0p4967_rsh_000144bc;
__declspec(section ".rodata") extern const f32 float_0p2_rsh_0001450c;
__declspec(section ".rodata") extern const f32 float_neg45_rsh_00014530;
__declspec(section ".rodata") extern const f32 float_0p1_rsh_00014548;
__declspec(section ".rodata") extern const f32 float_neg100_rsh_0001454c;
__declspec(section ".rodata") extern const f32 float_neg1000_rsh_00014560;
__declspec(section ".rodata") extern const f32 float_neg50_rsh_0001456c;
__declspec(section ".rodata") extern const f32 float_neg1870_rsh_00014570;
__declspec(section ".rodata") extern const f32 float_neg500_rsh_000145ac;
__declspec(section ".rodata") extern const f32 float_115_rsh_000145b0;
__declspec(section ".rodata") extern const f32 float_70_rsh_000145b4;
__declspec(section ".rodata") extern const f32 float_neg10_rsh_000145b8;
__declspec(section ".rodata") extern const u32 gap_03_00004B24_rodata;
#define EXT_LIT(sym, val) (sym)

#endif
extern const char zero_rsh_000145bc[];
#ifdef NONMATCHING
extern const char str_00004B20[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004B20[];
#endif
extern const f64 double_30_rsh_00014598;
extern const f32 float_0p03_rsh_000144f4[];
extern const f32 float_0p1_rsh_000144f0[];
extern const f32 float_0p20944_rsh_0001455c[];
extern const f32 float_0p25_rsh_0001452c[];
extern const f32 float_0p2_rsh_00014544[];
extern const f32 float_0p3_rsh_00014508[];
extern const f32 float_0p4_rsh_00014518[];
extern const f32 float_0p5_rsh_000144e8[];
extern const f32 float_0p8_rsh_00014520[];
extern const f32 float_0p9_rsh_0001453c[];
extern const f32 float_1000_rsh_0001457c[];
extern const f32 float_100_rsh_000144f8[];
extern const f32 float_10_rsh_00014584[];
extern const f32 float_135_rsh_00014540[];
extern const f32 float_15_rsh_00014474[];
extern const f32 float_180_rsh_00014538[];
extern const f32 float_1E06_rsh_00014594[];
extern const f32 float_1_rsh_00014470[];
extern const f32 float_1p02_rsh_00014558[];
extern const f32 float_1p1_rsh_00014554[];
extern const f32 float_1p5_rsh_0001451c[];
extern const f32 float_1p8_rsh_00014478[];
extern const f32 float_200_rsh_000144d8[];
extern const f32 float_20_rsh_00014580[];
extern const f32 float_215_rsh_00014504[];
extern const f32 float_225_rsh_00014550[];
extern const f32 float_250_rsh_00014564[];
extern const f32 float_2_rsh_00014514[];
extern const f32 float_300_rsh_00014524[];
extern const f32 float_30_rsh_000144dc[];
extern const f32 float_31_rsh_00014510[];
extern const f32 float_32767_rsh_000144ec[];
extern const f32 float_35_rsh_00014588[];
extern const f32 float_360_rsh_000144a0[];
extern const f32 float_40_rsh_00014590[];
extern const f32 float_450_rsh_00014568[];
extern const f32 float_45_rsh_00014574[];
extern const f32 float_50_rsh_000144fc[];
extern const f32 float_5_rsh_00014500[];
extern const f32 float_600_rsh_00014528[];
extern const f32 float_60_rsh_00014578[];
extern const f32 float_65_rsh_0001458c[];
extern const f32 float_6p2832_rsh_0001449c[];
extern const f32 float_90_rsh_00014534[];
extern const f32 zero_rsh_00014490[];
#ifdef NONMATCHING
extern const char str_000041D0[];
extern const char str_000041DC[];
extern const char str_000041E0[];
extern const char str_000041E4[];
extern const char str_000041F0[];
extern const char str_000041FC[];
extern const char str_00004200[];
extern const char str_0000420C[];
extern const char str_00004210[];
extern const char str_00004218[];
extern const char str_0000421C[];
extern const char str_00004224[];
extern const char str_00004228[];
extern const char str_00004230[];
extern const char str_00004238[];
extern const char str_00004240[];
extern const char str_0000430C[];
extern const char str_00004314[];
extern const char str_0000431C[];
extern const char str_00004324[];
extern const char str_0000432C[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_000041D0[];
extern const char rsh_06_str_000041DC[];
extern const char rsh_06_str_000041E0[];
extern const char rsh_06_str_000041E4[];
extern const char rsh_06_str_000041F0[];
extern const char rsh_06_str_000041FC[];
extern const char rsh_06_str_00004200[];
extern const char rsh_06_str_0000420C[];
extern const char rsh_06_str_00004210[];
extern const char rsh_06_str_00004218[];
extern const char rsh_06_str_0000421C[];
extern const char rsh_06_str_00004224[];
extern const char rsh_06_str_00004228[];
extern const char rsh_06_str_00004230[];
extern const char rsh_06_str_00004238[];
extern const char rsh_06_str_00004240[];
extern const char rsh_06_str_0000430C[];
extern const char rsh_06_str_00004314[];
extern const char rsh_06_str_0000431C[];
extern const char rsh_06_str_00004324[];
extern const char rsh_06_str_0000432C[];
#endif
extern const char str_00004334[];
#ifdef NONMATCHING
extern const char str_0000433C[];
extern const char str_00004344[];
extern const char str_0000434C[];
extern const char str_00004354[];
extern const char str_0000435C[];
extern const char str_00004364[];
extern const char str_0000436C[];
extern const char str_00004374[];
extern const char str_0000437C[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_0000433C[];
extern const char rsh_06_str_00004344[];
extern const char rsh_06_str_0000434C[];
extern const char rsh_06_str_00004354[];
extern const char rsh_06_str_0000435C[];
extern const char rsh_06_str_00004364[];
extern const char rsh_06_str_0000436C[];
extern const char rsh_06_str_00004374[];
extern const char rsh_06_str_0000437C[];
#endif
extern const char str_00004384[];
#ifdef NONMATCHING
extern const char str_0000438C[];
extern const char str_00004394[];
extern const char str_0000439C[];
extern const char str_000043A4[];
extern const char str_000043AC[];
extern const char str_000043B8[];
extern const char str_000043C4[];
extern const char str_000043D0[];
extern const char str_000043DC[];
extern const char str_000043E8[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_0000438C[];
extern const char rsh_06_str_00004394[];
extern const char rsh_06_str_0000439C[];
extern const char rsh_06_str_000043A4[];
extern const char rsh_06_str_000043AC[];
extern const char rsh_06_str_000043B8[];
extern const char rsh_06_str_000043C4[];
extern const char rsh_06_str_000043D0[];
extern const char rsh_06_str_000043DC[];
extern const char rsh_06_str_000043E8[];
#endif
extern const char str_000043F4[];
extern const char str_00004400[];
#ifdef NONMATCHING
extern const char str_0000440C[];
extern const char str_00004414[];
extern const char str_0000441C[];
extern const char str_00004424[];
extern const char str_0000442C[];
extern const char str_00004434[];
extern const char str_0000443C[];
extern const char str_00004444[];
extern const char str_0000444C[];
extern const char str_00004454[];
extern const char str_0000445C[];
extern const char str_00004464[];
extern const char str_00004470[];
extern const char str_0000447C[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_0000440C[];
extern const char rsh_06_str_00004414[];
extern const char rsh_06_str_0000441C[];
extern const char rsh_06_str_00004424[];
extern const char rsh_06_str_0000442C[];
extern const char rsh_06_str_00004434[];
extern const char rsh_06_str_0000443C[];
extern const char rsh_06_str_00004444[];
extern const char rsh_06_str_0000444C[];
extern const char rsh_06_str_00004454[];
extern const char rsh_06_str_0000445C[];
extern const char rsh_06_str_00004464[];
extern const char rsh_06_str_00004470[];
extern const char rsh_06_str_0000447C[];
#endif
extern const char str_00004488[];
#ifdef NONMATCHING
extern const char str_00004498[];
extern const char str_000044A4[];
extern const char str_000044B4[];
extern const char str_000044BC[];
extern const char str_000044D4[];
extern const char str_000044DC[];
extern const char str_000044F4[];
extern const char str_000044FC[];
extern const char str_00004514[];
extern const char str_00004530[];
extern const char str_00004538[];
extern const char str_00004550[];
extern const char str_00004558[];
extern const char str_00004574[];
extern const char str_0000458C[];
extern const char str_000045A4[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004498[];
extern const char rsh_06_str_000044A4[];
extern const char rsh_06_str_000044B4[];
extern const char rsh_06_str_000044BC[];
extern const char rsh_06_str_000044D4[];
extern const char rsh_06_str_000044DC[];
extern const char rsh_06_str_000044F4[];
extern const char rsh_06_str_000044FC[];
extern const char rsh_06_str_00004514[];
extern const char rsh_06_str_00004530[];
extern const char rsh_06_str_00004538[];
extern const char rsh_06_str_00004550[];
extern const char rsh_06_str_00004558[];
extern const char rsh_06_str_00004574[];
extern const char rsh_06_str_0000458C[];
extern const char rsh_06_str_000045A4[];
#endif
extern const char str_000045BC[];
#ifdef NONMATCHING
extern const char str_000045D8[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_000045D8[];
#endif
extern const char str_000045E0[];
#ifdef NONMATCHING
extern const char str_000045EC[];
extern const char str_000045F8[];
extern const char str_00004604[];
extern const char str_00004610[];
extern const char str_00004618[];
extern const char str_00004620[];
extern const char str_00004628[];
extern const char str_00004630[];
extern const char str_00004638[];
extern const char str_00004644[];
extern const char str_00004650[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_000045EC[];
extern const char rsh_06_str_000045F8[];
extern const char rsh_06_str_00004604[];
extern const char rsh_06_str_00004610[];
extern const char rsh_06_str_00004618[];
extern const char rsh_06_str_00004620[];
extern const char rsh_06_str_00004628[];
extern const char rsh_06_str_00004630[];
extern const char rsh_06_str_00004638[];
extern const char rsh_06_str_00004644[];
extern const char rsh_06_str_00004650[];
#endif
extern const char str_0000465C[];
#ifdef NONMATCHING
extern const char str_00004668[];
extern const char str_00004674[];
extern const char str_0000467C[];
extern const char str_00004684[];
extern const char str_0000468C[];
extern const char str_00004698[];
extern const char str_000046A0[];
extern const char str_000046A8[];
extern const char str_000046B4[];
extern const char str_000046C0[];
extern const char str_000046C8[];
extern const char str_000046D0[];
extern const char str_000046DC[];
extern const char str_000046E8[];
extern const char str_000046F8[];
extern const char str_00004700[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004668[];
extern const char rsh_06_str_00004674[];
extern const char rsh_06_str_0000467C[];
extern const char rsh_06_str_00004684[];
extern const char rsh_06_str_0000468C[];
extern const char rsh_06_str_00004698[];
extern const char rsh_06_str_000046A0[];
extern const char rsh_06_str_000046A8[];
extern const char rsh_06_str_000046B4[];
extern const char rsh_06_str_000046C0[];
extern const char rsh_06_str_000046C8[];
extern const char rsh_06_str_000046D0[];
extern const char rsh_06_str_000046DC[];
extern const char rsh_06_str_000046E8[];
extern const char rsh_06_str_000046F8[];
extern const char rsh_06_str_00004700[];
#endif
extern const char str_0000470C[];
#ifdef NONMATCHING
extern const char str_00004718[];
extern const char str_00004724[];
extern const char str_00004730[];
extern const char str_00004738[];
extern const char str_00004740[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004718[];
extern const char rsh_06_str_00004724[];
extern const char rsh_06_str_00004730[];
extern const char rsh_06_str_00004738[];
extern const char rsh_06_str_00004740[];
#endif
extern const char str_0000474C[];
#ifdef NONMATCHING
extern const char str_00004754[];
extern const char str_0000475C[];
extern const char str_00004764[];
extern const char str_0000476C[];
extern const char str_00004774[];
extern const char str_0000477C[];
extern const char str_00004784[];
extern const char str_0000478C[];
extern const char str_00004794[];
extern const char str_0000479C[];
extern const char str_000047B4[];
extern const char str_000047BC[];
extern const char str_000047C8[];
extern const char str_000047D8[];
extern const char str_000047E4[];
extern const char str_000047F0[];
extern const char str_000047FC[];
extern const char str_00004804[];
extern const char str_00004808[];
extern const char str_00004824[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004754[];
extern const char rsh_06_str_0000475C[];
extern const char rsh_06_str_00004764[];
extern const char rsh_06_str_0000476C[];
extern const char rsh_06_str_00004774[];
extern const char rsh_06_str_0000477C[];
extern const char rsh_06_str_00004784[];
extern const char rsh_06_str_0000478C[];
extern const char rsh_06_str_00004794[];
extern const char rsh_06_str_0000479C[];
extern const char rsh_06_str_000047B4[];
extern const char rsh_06_str_000047BC[];
extern const char rsh_06_str_000047C8[];
extern const char rsh_06_str_000047D8[];
extern const char rsh_06_str_000047E4[];
extern const char rsh_06_str_000047F0[];
extern const char rsh_06_str_000047FC[];
extern const char rsh_06_str_00004804[];
extern const char rsh_06_str_00004808[];
extern const char rsh_06_str_00004824[];
#endif
extern const char str_0000483C[];
#ifdef NONMATCHING
extern const char str_00004844[];
extern const char str_0000484C[];
extern const char str_00004868[];
extern const char str_00004874[];
extern const char str_0000488C[];
extern const char str_00004890[];
extern const char str_000048A8[];
extern const char str_000048C0[];
extern const char str_000048C4[];
extern const char str_000048C8[];
extern const char str_000048D0[];
extern const char str_000048E0[];
extern const char str_000048F0[];
extern const char str_00004900[];
extern const char str_00004918[];
extern const char str_0000491C[];
extern const char str_00004920[];
extern const char str_00004930[];
extern const char str_00004938[];
extern const char str_00004948[];
extern const char str_00004964[];
extern const char str_00004970[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004844[];
extern const char rsh_06_str_0000484C[];
extern const char rsh_06_str_00004868[];
extern const char rsh_06_str_00004874[];
extern const char rsh_06_str_0000488C[];
extern const char rsh_06_str_00004890[];
extern const char rsh_06_str_000048A8[];
extern const char rsh_06_str_000048C0[];
extern const char rsh_06_str_000048C4[];
extern const char rsh_06_str_000048C8[];
extern const char rsh_06_str_000048D0[];
extern const char rsh_06_str_000048E0[];
extern const char rsh_06_str_000048F0[];
extern const char rsh_06_str_00004900[];
extern const char rsh_06_str_00004918[];
extern const char rsh_06_str_0000491C[];
extern const char rsh_06_str_00004920[];
extern const char rsh_06_str_00004930[];
extern const char rsh_06_str_00004938[];
extern const char rsh_06_str_00004948[];
extern const char rsh_06_str_00004964[];
extern const char rsh_06_str_00004970[];
#endif
extern const char str_00004980[];
#ifdef NONMATCHING
extern const char str_00004990[];
extern const char str_000049A0[];
extern const char str_000049B0[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004990[];
extern const char rsh_06_str_000049A0[];
extern const char rsh_06_str_000049B0[];
#endif
extern const char str_000049C0[];
#ifdef NONMATCHING
extern const char str_00004A20[];
extern const char str_00004A40[];
extern const char str_00004A44[];
extern const char str_00004B00[];
extern const char str_000041D0[];
extern const char str_000041DC[];
extern const char str_000041E0[];
extern const char str_000041E4[];
extern const char str_000041F0[];
extern const char str_000041FC[];
extern const char str_00004200[];
extern const char str_0000420C[];
extern const char str_00004210[];
extern const char str_00004218[];
extern const char str_0000421C[];
extern const char str_00004224[];
extern const char str_00004228[];
extern const char str_00004230[];
extern const char str_00004238[];
extern const char str_00004240[];
extern const char str_0000430C[];
extern const char str_00004314[];
extern const char str_0000431C[];
extern const char str_00004324[];
extern const char str_0000432C[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004A20[];
extern const char rsh_06_str_00004A40[];
extern const char rsh_06_str_00004A44[];
extern const char rsh_06_str_00004B00[];
extern const char rsh_06_str_000041D0[];
extern const char rsh_06_str_000041DC[];
extern const char rsh_06_str_000041E0[];
extern const char rsh_06_str_000041E4[];
extern const char rsh_06_str_000041F0[];
extern const char rsh_06_str_000041FC[];
extern const char rsh_06_str_00004200[];
extern const char rsh_06_str_0000420C[];
extern const char rsh_06_str_00004210[];
extern const char rsh_06_str_00004218[];
extern const char rsh_06_str_0000421C[];
extern const char rsh_06_str_00004224[];
extern const char rsh_06_str_00004228[];
extern const char rsh_06_str_00004230[];
extern const char rsh_06_str_00004238[];
extern const char rsh_06_str_00004240[];
extern const char rsh_06_str_0000430C[];
extern const char rsh_06_str_00004314[];
extern const char rsh_06_str_0000431C[];
extern const char rsh_06_str_00004324[];
extern const char rsh_06_str_0000432C[];
#endif
extern const char str_00004334[];
#ifdef NONMATCHING
extern const char str_0000433C[];
extern const char str_00004344[];
extern const char str_0000434C[];
extern const char str_00004354[];
extern const char str_0000435C[];
extern const char str_00004364[];
extern const char str_0000436C[];
extern const char str_00004374[];
extern const char str_0000437C[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_0000433C[];
extern const char rsh_06_str_00004344[];
extern const char rsh_06_str_0000434C[];
extern const char rsh_06_str_00004354[];
extern const char rsh_06_str_0000435C[];
extern const char rsh_06_str_00004364[];
extern const char rsh_06_str_0000436C[];
extern const char rsh_06_str_00004374[];
extern const char rsh_06_str_0000437C[];
#endif
extern const char str_00004384[];
#ifdef NONMATCHING
extern const char str_0000438C[];
extern const char str_00004394[];
extern const char str_0000439C[];
extern const char str_000043A4[];
extern const char str_000043AC[];
extern const char str_000043B8[];
extern const char str_000043C4[];
extern const char str_000043D0[];
extern const char str_000043DC[];
extern const char str_000043E8[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_0000438C[];
extern const char rsh_06_str_00004394[];
extern const char rsh_06_str_0000439C[];
extern const char rsh_06_str_000043A4[];
extern const char rsh_06_str_000043AC[];
extern const char rsh_06_str_000043B8[];
extern const char rsh_06_str_000043C4[];
extern const char rsh_06_str_000043D0[];
extern const char rsh_06_str_000043DC[];
extern const char rsh_06_str_000043E8[];
#endif
extern const char str_000043F4[];
extern const char str_00004400[];
#ifdef NONMATCHING
extern const char str_0000440C[];
extern const char str_00004414[];
extern const char str_0000441C[];
extern const char str_00004424[];
extern const char str_0000442C[];
extern const char str_00004434[];
extern const char str_0000443C[];
extern const char str_00004444[];
extern const char str_0000444C[];
extern const char str_00004454[];
extern const char str_0000445C[];
extern const char str_00004464[];
extern const char str_00004470[];
extern const char str_0000447C[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_0000440C[];
extern const char rsh_06_str_00004414[];
extern const char rsh_06_str_0000441C[];
extern const char rsh_06_str_00004424[];
extern const char rsh_06_str_0000442C[];
extern const char rsh_06_str_00004434[];
extern const char rsh_06_str_0000443C[];
extern const char rsh_06_str_00004444[];
extern const char rsh_06_str_0000444C[];
extern const char rsh_06_str_00004454[];
extern const char rsh_06_str_0000445C[];
extern const char rsh_06_str_00004464[];
extern const char rsh_06_str_00004470[];
extern const char rsh_06_str_0000447C[];
#endif
extern const char str_00004488[];
#ifdef NONMATCHING
extern const char str_00004498[];
extern const char str_000044A4[];
extern const char str_000044B4[];
extern const char str_000044BC[];
extern const char str_000044D4[];
extern const char str_000044DC[];
extern const char str_000044F4[];
extern const char str_000044FC[];
extern const char str_00004514[];
extern const char str_00004530[];
extern const char str_00004538[];
extern const char str_00004550[];
extern const char str_00004558[];
extern const char str_00004574[];
extern const char str_0000458C[];
extern const char str_000045A4[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004498[];
extern const char rsh_06_str_000044A4[];
extern const char rsh_06_str_000044B4[];
extern const char rsh_06_str_000044BC[];
extern const char rsh_06_str_000044D4[];
extern const char rsh_06_str_000044DC[];
extern const char rsh_06_str_000044F4[];
extern const char rsh_06_str_000044FC[];
extern const char rsh_06_str_00004514[];
extern const char rsh_06_str_00004530[];
extern const char rsh_06_str_00004538[];
extern const char rsh_06_str_00004550[];
extern const char rsh_06_str_00004558[];
extern const char rsh_06_str_00004574[];
extern const char rsh_06_str_0000458C[];
extern const char rsh_06_str_000045A4[];
#endif
extern const char str_000045BC[];
#ifdef NONMATCHING
extern const char str_000045D8[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_000045D8[];
#endif
extern const char str_000045E0[];
#ifdef NONMATCHING
extern const char str_000045EC[];
extern const char str_000045F8[];
extern const char str_00004604[];
extern const char str_00004610[];
extern const char str_00004618[];
extern const char str_00004620[];
extern const char str_00004628[];
extern const char str_00004630[];
extern const char str_00004638[];
extern const char str_00004644[];
extern const char str_00004650[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_000045EC[];
extern const char rsh_06_str_000045F8[];
extern const char rsh_06_str_00004604[];
extern const char rsh_06_str_00004610[];
extern const char rsh_06_str_00004618[];
extern const char rsh_06_str_00004620[];
extern const char rsh_06_str_00004628[];
extern const char rsh_06_str_00004630[];
extern const char rsh_06_str_00004638[];
extern const char rsh_06_str_00004644[];
extern const char rsh_06_str_00004650[];
#endif
extern const char str_0000465C[];
#ifdef NONMATCHING
extern const char str_00004668[];
extern const char str_00004674[];
extern const char str_0000467C[];
extern const char str_00004684[];
extern const char str_0000468C[];
extern const char str_00004698[];
extern const char str_000046A0[];
extern const char str_000046A8[];
extern const char str_000046B4[];
extern const char str_000046C0[];
extern const char str_000046C8[];
extern const char str_000046D0[];
extern const char str_000046DC[];
extern const char str_000046E8[];
extern const char str_000046F8[];
extern const char str_00004700[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004668[];
extern const char rsh_06_str_00004674[];
extern const char rsh_06_str_0000467C[];
extern const char rsh_06_str_00004684[];
extern const char rsh_06_str_0000468C[];
extern const char rsh_06_str_00004698[];
extern const char rsh_06_str_000046A0[];
extern const char rsh_06_str_000046A8[];
extern const char rsh_06_str_000046B4[];
extern const char rsh_06_str_000046C0[];
extern const char rsh_06_str_000046C8[];
extern const char rsh_06_str_000046D0[];
extern const char rsh_06_str_000046DC[];
extern const char rsh_06_str_000046E8[];
extern const char rsh_06_str_000046F8[];
extern const char rsh_06_str_00004700[];
#endif
extern const char str_0000470C[];
#ifdef NONMATCHING
extern const char str_00004718[];
extern const char str_00004724[];
extern const char str_00004730[];
extern const char str_00004738[];
extern const char str_00004740[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004718[];
extern const char rsh_06_str_00004724[];
extern const char rsh_06_str_00004730[];
extern const char rsh_06_str_00004738[];
extern const char rsh_06_str_00004740[];
#endif
extern const char str_0000474C[];
#ifdef NONMATCHING
extern const char str_00004754[];
extern const char str_0000475C[];
extern const char str_00004764[];
extern const char str_0000476C[];
extern const char str_00004774[];
extern const char str_0000477C[];
extern const char str_00004784[];
extern const char str_0000478C[];
extern const char str_00004794[];
extern const char str_0000479C[];
extern const char str_000047B4[];
extern const char str_000047BC[];
extern const char str_000047C8[];
extern const char str_000047D8[];
extern const char str_000047E4[];
extern const char str_000047F0[];
extern const char str_000047FC[];
extern const char str_00004804[];
extern const char str_00004808[];
extern const char str_00004824[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004754[];
extern const char rsh_06_str_0000475C[];
extern const char rsh_06_str_00004764[];
extern const char rsh_06_str_0000476C[];
extern const char rsh_06_str_00004774[];
extern const char rsh_06_str_0000477C[];
extern const char rsh_06_str_00004784[];
extern const char rsh_06_str_0000478C[];
extern const char rsh_06_str_00004794[];
extern const char rsh_06_str_0000479C[];
extern const char rsh_06_str_000047B4[];
extern const char rsh_06_str_000047BC[];
extern const char rsh_06_str_000047C8[];
extern const char rsh_06_str_000047D8[];
extern const char rsh_06_str_000047E4[];
extern const char rsh_06_str_000047F0[];
extern const char rsh_06_str_000047FC[];
extern const char rsh_06_str_00004804[];
extern const char rsh_06_str_00004808[];
extern const char rsh_06_str_00004824[];
#endif
extern const char str_0000483C[];
#ifdef NONMATCHING
extern const char str_00004844[];
extern const char str_0000484C[];
extern const char str_00004868[];
extern const char str_00004874[];
extern const char str_0000488C[];
extern const char str_00004890[];
extern const char str_000048A8[];
extern const char str_000048C0[];
extern const char str_000048C4[];
extern const char str_000048C8[];
extern const char str_000048D0[];
extern const char str_000048E0[];
extern const char str_000048F0[];
extern const char str_00004900[];
extern const char str_00004918[];
extern const char str_0000491C[];
extern const char str_00004920[];
extern const char str_00004930[];
extern const char str_00004938[];
extern const char str_00004948[];
extern const char str_00004964[];
extern const char str_00004970[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004844[];
extern const char rsh_06_str_0000484C[];
extern const char rsh_06_str_00004868[];
extern const char rsh_06_str_00004874[];
extern const char rsh_06_str_0000488C[];
extern const char rsh_06_str_00004890[];
extern const char rsh_06_str_000048A8[];
extern const char rsh_06_str_000048C0[];
extern const char rsh_06_str_000048C4[];
extern const char rsh_06_str_000048C8[];
extern const char rsh_06_str_000048D0[];
extern const char rsh_06_str_000048E0[];
extern const char rsh_06_str_000048F0[];
extern const char rsh_06_str_00004900[];
extern const char rsh_06_str_00004918[];
extern const char rsh_06_str_0000491C[];
extern const char rsh_06_str_00004920[];
extern const char rsh_06_str_00004930[];
extern const char rsh_06_str_00004938[];
extern const char rsh_06_str_00004948[];
extern const char rsh_06_str_00004964[];
extern const char rsh_06_str_00004970[];
#endif
extern const char str_00004980[];
#ifdef NONMATCHING
extern const char str_00004990[];
extern const char str_000049A0[];
extern const char str_000049B0[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004990[];
extern const char rsh_06_str_000049A0[];
extern const char rsh_06_str_000049B0[];
#endif
extern const char str_000049C0[];
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)
#pragma force_active on
#pragma force_active reset
#ifdef NONMATCHING
extern const char str_000041D0[];
extern const char str_000041DC[];
extern const char str_000041E0[];
extern const char str_000041E4[];
extern const char str_000041F0[];
extern const char str_000041FC[];
extern const char str_00004200[];
extern const char str_0000420C[];
extern const char str_00004210[];
extern const char str_00004218[];
extern const char str_0000421C[];
extern const char str_00004224[];
extern const char str_00004228[];
extern const char str_00004230[];
extern const char str_00004238[];
extern const char str_00004240[];
extern const char str_0000430C[];
extern const char str_00004314[];
extern const char str_0000431C[];
extern const char str_00004324[];
extern const char str_0000432C[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_000041D0[];
extern const char rsh_06_str_000041DC[];
extern const char rsh_06_str_000041E0[];
extern const char rsh_06_str_000041E4[];
extern const char rsh_06_str_000041F0[];
extern const char rsh_06_str_000041FC[];
extern const char rsh_06_str_00004200[];
extern const char rsh_06_str_0000420C[];
extern const char rsh_06_str_00004210[];
extern const char rsh_06_str_00004218[];
extern const char rsh_06_str_0000421C[];
extern const char rsh_06_str_00004224[];
extern const char rsh_06_str_00004228[];
extern const char rsh_06_str_00004230[];
extern const char rsh_06_str_00004238[];
extern const char rsh_06_str_00004240[];
extern const char rsh_06_str_0000430C[];
extern const char rsh_06_str_00004314[];
extern const char rsh_06_str_0000431C[];
extern const char rsh_06_str_00004324[];
extern const char rsh_06_str_0000432C[];
#endif
extern const char str_00004334[];
#ifdef NONMATCHING
extern const char str_0000433C[];
extern const char str_00004344[];
extern const char str_0000434C[];
extern const char str_00004354[];
extern const char str_0000435C[];
extern const char str_00004364[];
extern const char str_0000436C[];
extern const char str_00004374[];
extern const char str_0000437C[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_0000433C[];
extern const char rsh_06_str_00004344[];
extern const char rsh_06_str_0000434C[];
extern const char rsh_06_str_00004354[];
extern const char rsh_06_str_0000435C[];
extern const char rsh_06_str_00004364[];
extern const char rsh_06_str_0000436C[];
extern const char rsh_06_str_00004374[];
extern const char rsh_06_str_0000437C[];
#endif
extern const char str_00004384[];
#ifdef NONMATCHING
extern const char str_0000438C[];
extern const char str_00004394[];
extern const char str_0000439C[];
extern const char str_000043A4[];
extern const char str_000043AC[];
extern const char str_000043B8[];
extern const char str_000043C4[];
extern const char str_000043D0[];
extern const char str_000043DC[];
extern const char str_000043E8[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_0000438C[];
extern const char rsh_06_str_00004394[];
extern const char rsh_06_str_0000439C[];
extern const char rsh_06_str_000043A4[];
extern const char rsh_06_str_000043AC[];
extern const char rsh_06_str_000043B8[];
extern const char rsh_06_str_000043C4[];
extern const char rsh_06_str_000043D0[];
extern const char rsh_06_str_000043DC[];
extern const char rsh_06_str_000043E8[];
#endif
extern const char str_000043F4[];
extern const char str_00004400[];
#ifdef NONMATCHING
extern const char str_0000440C[];
extern const char str_00004414[];
extern const char str_0000441C[];
extern const char str_00004424[];
extern const char str_0000442C[];
extern const char str_00004434[];
extern const char str_0000443C[];
extern const char str_00004444[];
extern const char str_0000444C[];
extern const char str_00004454[];
extern const char str_0000445C[];
extern const char str_00004464[];
extern const char str_00004470[];
extern const char str_0000447C[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_0000440C[];
extern const char rsh_06_str_00004414[];
extern const char rsh_06_str_0000441C[];
extern const char rsh_06_str_00004424[];
extern const char rsh_06_str_0000442C[];
extern const char rsh_06_str_00004434[];
extern const char rsh_06_str_0000443C[];
extern const char rsh_06_str_00004444[];
extern const char rsh_06_str_0000444C[];
extern const char rsh_06_str_00004454[];
extern const char rsh_06_str_0000445C[];
extern const char rsh_06_str_00004464[];
extern const char rsh_06_str_00004470[];
extern const char rsh_06_str_0000447C[];
#endif
extern const char str_00004488[];
#ifdef NONMATCHING
extern const char str_00004498[];
extern const char str_000044A4[];
extern const char str_000044B4[];
extern const char str_000044BC[];
extern const char str_000044D4[];
extern const char str_000044DC[];
extern const char str_000044F4[];
extern const char str_000044FC[];
extern const char str_00004514[];
extern const char str_00004530[];
extern const char str_00004538[];
extern const char str_00004550[];
extern const char str_00004558[];
extern const char str_00004574[];
extern const char str_0000458C[];
extern const char str_000045A4[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004498[];
extern const char rsh_06_str_000044A4[];
extern const char rsh_06_str_000044B4[];
extern const char rsh_06_str_000044BC[];
extern const char rsh_06_str_000044D4[];
extern const char rsh_06_str_000044DC[];
extern const char rsh_06_str_000044F4[];
extern const char rsh_06_str_000044FC[];
extern const char rsh_06_str_00004514[];
extern const char rsh_06_str_00004530[];
extern const char rsh_06_str_00004538[];
extern const char rsh_06_str_00004550[];
extern const char rsh_06_str_00004558[];
extern const char rsh_06_str_00004574[];
extern const char rsh_06_str_0000458C[];
extern const char rsh_06_str_000045A4[];
#endif
extern const char str_000045BC[];
#ifdef NONMATCHING
extern const char str_000045D8[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_000045D8[];
#endif
extern const char str_000045E0[];
#ifdef NONMATCHING
extern const char str_000045EC[];
extern const char str_000045F8[];
extern const char str_00004604[];
extern const char str_00004610[];
extern const char str_00004618[];
extern const char str_00004620[];
extern const char str_00004628[];
extern const char str_00004630[];
extern const char str_00004638[];
extern const char str_00004644[];
extern const char str_00004650[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_000045EC[];
extern const char rsh_06_str_000045F8[];
extern const char rsh_06_str_00004604[];
extern const char rsh_06_str_00004610[];
extern const char rsh_06_str_00004618[];
extern const char rsh_06_str_00004620[];
extern const char rsh_06_str_00004628[];
extern const char rsh_06_str_00004630[];
extern const char rsh_06_str_00004638[];
extern const char rsh_06_str_00004644[];
extern const char rsh_06_str_00004650[];
#endif
extern const char str_0000465C[];
#ifdef NONMATCHING
extern const char str_00004668[];
extern const char str_00004674[];
extern const char str_0000467C[];
extern const char str_00004684[];
extern const char str_0000468C[];
extern const char str_00004698[];
extern const char str_000046A0[];
extern const char str_000046A8[];
extern const char str_000046B4[];
extern const char str_000046C0[];
extern const char str_000046C8[];
extern const char str_000046D0[];
extern const char str_000046DC[];
extern const char str_000046E8[];
extern const char str_000046F8[];
extern const char str_00004700[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004668[];
extern const char rsh_06_str_00004674[];
extern const char rsh_06_str_0000467C[];
extern const char rsh_06_str_00004684[];
extern const char rsh_06_str_0000468C[];
extern const char rsh_06_str_00004698[];
extern const char rsh_06_str_000046A0[];
extern const char rsh_06_str_000046A8[];
extern const char rsh_06_str_000046B4[];
extern const char rsh_06_str_000046C0[];
extern const char rsh_06_str_000046C8[];
extern const char rsh_06_str_000046D0[];
extern const char rsh_06_str_000046DC[];
extern const char rsh_06_str_000046E8[];
extern const char rsh_06_str_000046F8[];
extern const char rsh_06_str_00004700[];
#endif
extern const char str_0000470C[];
#ifdef NONMATCHING
extern const char str_00004718[];
extern const char str_00004724[];
extern const char str_00004730[];
extern const char str_00004738[];
extern const char str_00004740[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004718[];
extern const char rsh_06_str_00004724[];
extern const char rsh_06_str_00004730[];
extern const char rsh_06_str_00004738[];
extern const char rsh_06_str_00004740[];
#endif
extern const char str_0000474C[];
#ifdef NONMATCHING
extern const char str_00004754[];
extern const char str_0000475C[];
extern const char str_00004764[];
extern const char str_0000476C[];
extern const char str_00004774[];
extern const char str_0000477C[];
extern const char str_00004784[];
extern const char str_0000478C[];
extern const char str_00004794[];
extern const char str_0000479C[];
extern const char str_000047B4[];
extern const char str_000047BC[];
extern const char str_000047C8[];
extern const char str_000047D8[];
extern const char str_000047E4[];
extern const char str_000047F0[];
extern const char str_000047FC[];
extern const char str_00004804[];
extern const char str_00004808[];
extern const char str_00004824[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004754[];
extern const char rsh_06_str_0000475C[];
extern const char rsh_06_str_00004764[];
extern const char rsh_06_str_0000476C[];
extern const char rsh_06_str_00004774[];
extern const char rsh_06_str_0000477C[];
extern const char rsh_06_str_00004784[];
extern const char rsh_06_str_0000478C[];
extern const char rsh_06_str_00004794[];
extern const char rsh_06_str_0000479C[];
extern const char rsh_06_str_000047B4[];
extern const char rsh_06_str_000047BC[];
extern const char rsh_06_str_000047C8[];
extern const char rsh_06_str_000047D8[];
extern const char rsh_06_str_000047E4[];
extern const char rsh_06_str_000047F0[];
extern const char rsh_06_str_000047FC[];
extern const char rsh_06_str_00004804[];
extern const char rsh_06_str_00004808[];
extern const char rsh_06_str_00004824[];
#endif
extern const char str_0000483C[];
#ifdef NONMATCHING
extern const char str_00004844[];
extern const char str_0000484C[];
extern const char str_00004868[];
extern const char str_00004874[];
extern const char str_0000488C[];
extern const char str_00004890[];
extern const char str_000048A8[];
extern const char str_000048C0[];
extern const char str_000048C4[];
extern const char str_000048C8[];
extern const char str_000048D0[];
extern const char str_000048E0[];
extern const char str_000048F0[];
extern const char str_00004900[];
extern const char str_00004918[];
extern const char str_0000491C[];
extern const char str_00004920[];
extern const char str_00004930[];
extern const char str_00004938[];
extern const char str_00004948[];
extern const char str_00004964[];
extern const char str_00004970[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004844[];
extern const char rsh_06_str_0000484C[];
extern const char rsh_06_str_00004868[];
extern const char rsh_06_str_00004874[];
extern const char rsh_06_str_0000488C[];
extern const char rsh_06_str_00004890[];
extern const char rsh_06_str_000048A8[];
extern const char rsh_06_str_000048C0[];
extern const char rsh_06_str_000048C4[];
extern const char rsh_06_str_000048C8[];
extern const char rsh_06_str_000048D0[];
extern const char rsh_06_str_000048E0[];
extern const char rsh_06_str_000048F0[];
extern const char rsh_06_str_00004900[];
extern const char rsh_06_str_00004918[];
extern const char rsh_06_str_0000491C[];
extern const char rsh_06_str_00004920[];
extern const char rsh_06_str_00004930[];
extern const char rsh_06_str_00004938[];
extern const char rsh_06_str_00004948[];
extern const char rsh_06_str_00004964[];
extern const char rsh_06_str_00004970[];
#endif
extern const char str_00004980[];
#ifdef NONMATCHING
extern const char str_00004990[];
extern const char str_000049A0[];
extern const char str_000049B0[];
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_00004990[];
extern const char rsh_06_str_000049A0[];
extern const char rsh_06_str_000049B0[];
#endif
extern const char str_000049C0[];

typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; f32 field_0x14; f32 field_0x18; f32 field_0x1c; } ExtPose;
typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
typedef struct Moamoa { u16 flags; s16 state; s16 timer; u8 field_0x6[2]; Vec target; f32 vy; s16 jumpTimer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[2]; f32 lastX; f32 lastZ; Vec jitter; s16 pose; u8 field_0x3e[2]; OSTime startTime; s16 group; s16 order; u8 kind; u8 field_0x4d[3]; } Moamoa;
typedef struct MoamoaWork { u16 flags; u8 field_0x2[2]; s32 count; Moamoa* moa; MapObject* mobj; f32 mobjY; Vec target[3]; s16 hitCount; s16 field_0x3a[2]; s16 field_0x3e; s16 field_0x40; s16 idleFrames; void* escapeEvt; s32 animPoseId; s32 numDefs; MoamoaPoseDef defs[32]; f32 angle; f32 dist; s32 bounceCount; f32 breathDir; f32 breathDist; Vec breathPos; s16 chainNum[128]; s16 chainIdx[128][2]; } MoamoaWork;
typedef struct MoamoaData { const char* model; const char* anim; f32 speed; } MoamoaData;
#ifdef NONMATCHING
static s32 bss_pad;
#endif
#ifndef NONMATCHING
static u8 gap_05_00000054_bss[4];  // .bss pad after wp
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
extern const char* g_moamoa_chain_tbl[][2];
extern const s32 dat_80419a28;
void evalOn(void);
void evalOn(void);
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
static inline f32 moa_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } return a; }
static inline f32 moa_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; } return a; }
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
void moamoa_joint_position(Moamoa* moa, Vec* out);
void moamoa_joint_position(Moamoa* moa, Vec* out);
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
s32 npc_anim_wait(EventEntry* event, BOOL isFirstCall);
s32 npc_anim_wait(EventEntry* event, BOOL isFirstCall);
static s32 ramp_r(EventEntry* event, BOOL isFirstCall);
static s32 ramp_r(EventEntry* event, BOOL isFirstCall);
static void resha_tev(MapTevCallbackInfo* info);
static void resha_tev(MapTevCallbackInfo* info);
void moamoa_joint_position(Moamoa* moa, Vec* out);
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
void evalOn(void);
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
extern s32 evt_sub_stopwatch[];

__declspec(section ".data") u64 fd_rsh_06_negone_one_374;
__declspec(section ".data") s32 fd_rsh_06_neg_one_382[1];
__declspec(section ".data") s32 fd_rsh_06___local_PI_383[1];
__declspec(section ".data") s32 fd_rsh_06___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_rsh_06_one_negone_373;
__declspec(section ".data") s32 fd_rsh_06___local_PIO2_384[1];
__declspec(section ".data") s32 fd_rsh_06_one_381[1];
__declspec(section ".data") u64 fd_rsh_06_negone_one_360;
__declspec(section ".data") s32 fd_rsh_06_neg_one_365[1];
__declspec(section ".data") s32 fd_rsh_06___local_PI_366[1];
__declspec(section ".data") s32 fd_rsh_06___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_rsh_06_one_negone_359;
__declspec(section ".data") s32 fd_rsh_06___local_PIO2_367[1];
__declspec(section ".data") s32 fd_rsh_06_one_364[1];
static s32 ext_moamoa_data[213];
static s32 sharinDt[116];
static s32 evt_sharin_main[87];
static s32 evt_sharin[19];
static s32 clankDt[45];
static s32 evt_clank_main[104];
static s32 evt_clank[21];
static s32 evt_bg[81];
static s32 evt_hoshi[88];
static s32 hom_10_evt_resha_start[244];
static s32 hom_10_evt_resha_start2[259];
__declspec(section ".data") static s32 hom_10_evt_resha_start3[11];
__declspec(section ".data") static s32 hom_10_evt_resha_start4[11];
static s32 stop_1[90];
static s32 stop_2[90];
static s32 hom_10_evt_resha_stop[36];
static s32 evt_ramp[33];
static s32 pika_tbl[15];
__declspec(section ".data") static s32 pika_tbl_rsh_06[10];
static s32 hom_10_evt_resha_sub[102];
static s32 hom_10_evt_resha_right[35];
static s32 hom_10_evt_resha_left[28];
static s32 hom_10_init_evt[140];
s32 evt_resha_init[13];
static s32 bero_data_a[30];
static s32 evt_moamoa_init[187];
s32 evt_great_moamoa[737];
__declspec(section ".data") s32 pose_name[8];
s32 moamoa_debug[230];
s32 rsh_06_init_evt[84];
s32 rsh_06_a_init_evt[32];
s32 rsh_06_init_evt_nidome[41];
__declspec(section ".data") s32 rsh_06_a_init_evt_nidome[11];

__declspec(section ".data") u64 fd_rsh_06_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_rsh_06_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_rsh_06___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_rsh_06___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_rsh_06_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_rsh_06___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_rsh_06_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_rsh_06_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_rsh_06_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_rsh_06___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_rsh_06___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_rsh_06_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_rsh_06___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_rsh_06_one_364[] = {
    1065353216,
};

static s32 ext_moamoa_data[] = {
#ifdef NONMATCHING
    (s32)((char*)str_000041D0), (s32)((char*)str_000041DC), 0, (s32)((char*)str_000041D0), (s32)((char*)str_000041DC), 1073741824, (s32)((char*)str_000041D0), (s32)((char*)str_000041DC),
    1082130432, (s32)((char*)str_000041D0), (s32)((char*)str_000041DC), 1086324736, (s32)((char*)str_000041D0), (s32)((char*)str_000041DC), 1090519040, (s32)((char*)str_000041D0),
    (s32)((char*)str_000041DC), 1092616192, (s32)((char*)str_000041D0), (s32)((char*)str_000041DC), 1094713344, (s32)((char*)str_000041D0), (s32)((char*)str_000041DC), 1096810496,
    (s32)((char*)str_000041D0), (s32)((char*)str_000041DC), 1098907648, (s32)((char*)str_000041D0), (s32)((char*)str_000041DC), 1099956224, (s32)((char*)str_000041D0), (s32)((char*)str_000041DC),
    1101004800, (s32)((char*)str_000041D0), (s32)((char*)str_000041DC), 1102053376, (s32)((char*)str_000041D0), (s32)((char*)str_000041DC), 1103101952, (s32)((char*)str_000041D0),
    (s32)((char*)str_000041DC), 1104150528, (s32)((char*)str_000041D0), (s32)((char*)str_000041DC), 1105199104, (s32)((char*)str_000041D0), (s32)((char*)str_000041DC), 1106247680,
    (s32)((char*)str_000041D0), (s32)((char*)str_000041DC), 1107296256, (s32)((char*)str_000041D0), (s32)((char*)str_000041DC), 1107820544, (s32)((char*)str_000041D0), (s32)((char*)str_000041DC),
    1108344832, (s32)((char*)str_000041D0), (s32)((char*)str_000041DC), 1108869120, (s32)((char*)str_000041D0), (s32)((char*)str_000041E0), 0, (s32)((char*)str_000041D0),
    (s32)((char*)str_000041E0), 1082130432, (s32)((char*)str_000041D0), (s32)((char*)str_000041E0), 1090519040, (s32)((char*)str_000041E4), (s32)((char*)str_000041DC), 0,
    (s32)((char*)str_000041E4), (s32)((char*)str_000041DC), 1073741824, (s32)((char*)str_000041E4), (s32)((char*)str_000041DC), 1082130432, (s32)((char*)str_000041E4), (s32)((char*)str_000041DC),
    1086324736, (s32)((char*)str_000041E4), (s32)((char*)str_000041DC), 1090519040, (s32)((char*)str_000041E4), (s32)((char*)str_000041DC), 1092616192, (s32)((char*)str_000041E4),
    (s32)((char*)str_000041DC), 1094713344, (s32)((char*)str_000041E4), (s32)((char*)str_000041DC), 1096810496, (s32)((char*)str_000041E4), (s32)((char*)str_000041DC), 1098907648,
    (s32)((char*)str_000041E4), (s32)((char*)str_000041DC), 1099956224, (s32)((char*)str_000041E4), (s32)((char*)str_000041DC), 1101004800, (s32)((char*)str_000041E4), (s32)((char*)str_000041DC),
    1102053376, (s32)((char*)str_000041E4), (s32)((char*)str_000041DC), 1103101952, (s32)((char*)str_000041E4), (s32)((char*)str_000041DC), 1104150528, (s32)((char*)str_000041E4),
    (s32)((char*)str_000041DC), 1105199104, (s32)((char*)str_000041E4), (s32)((char*)str_000041DC), 1106247680, (s32)((char*)str_000041E4), (s32)((char*)str_000041DC), 1107296256,
    (s32)((char*)str_000041E4), (s32)((char*)str_000041DC), 1107820544, (s32)((char*)str_000041E4), (s32)((char*)str_000041DC), 1108344832, (s32)((char*)str_000041E4), (s32)((char*)str_000041DC),
    1108869120, (s32)((char*)str_000041E4), (s32)((char*)str_000041E0), 0, (s32)((char*)str_000041E4), (s32)((char*)str_000041E0), 1082130432, (s32)((char*)str_000041E4),
    (s32)((char*)str_000041E0), 1090519040, (s32)((char*)str_000041F0), (s32)((char*)str_000041FC), 0, (s32)((char*)str_000041F0), (s32)((char*)str_000041FC), 1082130432,
    (s32)((char*)str_000041F0), (s32)((char*)str_000041FC), 1090519040, (s32)((char*)str_00004200), (s32)((char*)str_0000420C), 0, (s32)((char*)str_00004200), (s32)((char*)str_0000420C),
    1082130432, (s32)((char*)str_00004200), (s32)((char*)str_0000420C), 1090519040, (s32)((char*)str_00004210), (s32)((char*)str_00004218), 0, (s32)((char*)str_00004210),
    (s32)((char*)str_00004218), 1082130432, (s32)((char*)str_00004210), (s32)((char*)str_00004218), 1090519040, (s32)((char*)str_0000421C), (s32)((char*)str_00004224), 0,
    (s32)((char*)str_0000421C), (s32)((char*)str_00004224), 1082130432, (s32)((char*)str_0000421C), (s32)((char*)str_00004224), 1090519040, (s32)((char*)str_00004228), (s32)((char*)str_000041FC),
    0, (s32)((char*)str_00004228), (s32)((char*)str_000041FC), 1082130432, (s32)((char*)str_00004228), (s32)((char*)str_000041FC), 1090519040, (s32)((char*)str_00004230),
    (s32)((char*)str_000041FC), 0, (s32)((char*)str_00004230), (s32)((char*)str_000041FC), 1082130432, (s32)((char*)str_00004230), (s32)((char*)str_000041FC), 1090519040,
    (s32)((char*)str_00004238), (s32)((char*)str_000041FC), 0, (s32)((char*)str_00004238), (s32)((char*)str_000041FC), 1082130432, (s32)((char*)str_00004238), (s32)((char*)str_000041FC),
    1090519040, (s32)((char*)str_00004240), (s32)((char*)str_000041FC), 0, (s32)((char*)str_00004240), (s32)((char*)str_000041FC), 1082130432, (s32)((char*)str_00004240),
    (s32)((char*)str_000041FC), 1090519040, 0, 0, 0,
#endif
#ifndef NONMATCHING
    (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC), 0, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC), 1073741824, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC),
    1082130432, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC), 1086324736, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC), 1090519040, (s32)((char*)rsh_06_str_000041D0),
    (s32)((char*)rsh_06_str_000041DC), 1092616192, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC), 1094713344, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC), 1096810496,
    (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC), 1098907648, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC), 1099956224, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC),
    1101004800, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC), 1102053376, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC), 1103101952, (s32)((char*)rsh_06_str_000041D0),
    (s32)((char*)rsh_06_str_000041DC), 1104150528, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC), 1105199104, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC), 1106247680,
    (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC), 1107296256, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC), 1107820544, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC),
    1108344832, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041DC), 1108869120, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041E0), 0, (s32)((char*)rsh_06_str_000041D0),
    (s32)((char*)rsh_06_str_000041E0), 1082130432, (s32)((char*)rsh_06_str_000041D0), (s32)((char*)rsh_06_str_000041E0), 1090519040, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC), 0,
    (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC), 1073741824, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC), 1082130432, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC),
    1086324736, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC), 1090519040, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC), 1092616192, (s32)((char*)rsh_06_str_000041E4),
    (s32)((char*)rsh_06_str_000041DC), 1094713344, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC), 1096810496, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC), 1098907648,
    (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC), 1099956224, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC), 1101004800, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC),
    1102053376, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC), 1103101952, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC), 1104150528, (s32)((char*)rsh_06_str_000041E4),
    (s32)((char*)rsh_06_str_000041DC), 1105199104, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC), 1106247680, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC), 1107296256,
    (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC), 1107820544, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC), 1108344832, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041DC),
    1108869120, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041E0), 0, (s32)((char*)rsh_06_str_000041E4), (s32)((char*)rsh_06_str_000041E0), 1082130432, (s32)((char*)rsh_06_str_000041E4),
    (s32)((char*)rsh_06_str_000041E0), 1090519040, (s32)((char*)rsh_06_str_000041F0), (s32)((char*)rsh_06_str_000041FC), 0, (s32)((char*)rsh_06_str_000041F0), (s32)((char*)rsh_06_str_000041FC), 1082130432,
    (s32)((char*)rsh_06_str_000041F0), (s32)((char*)rsh_06_str_000041FC), 1090519040, (s32)((char*)rsh_06_str_00004200), (s32)((char*)rsh_06_str_0000420C), 0, (s32)((char*)rsh_06_str_00004200), (s32)((char*)rsh_06_str_0000420C),
    1082130432, (s32)((char*)rsh_06_str_00004200), (s32)((char*)rsh_06_str_0000420C), 1090519040, (s32)((char*)rsh_06_str_00004210), (s32)((char*)rsh_06_str_00004218), 0, (s32)((char*)rsh_06_str_00004210),
    (s32)((char*)rsh_06_str_00004218), 1082130432, (s32)((char*)rsh_06_str_00004210), (s32)((char*)rsh_06_str_00004218), 1090519040, (s32)((char*)rsh_06_str_0000421C), (s32)((char*)rsh_06_str_00004224), 0,
    (s32)((char*)rsh_06_str_0000421C), (s32)((char*)rsh_06_str_00004224), 1082130432, (s32)((char*)rsh_06_str_0000421C), (s32)((char*)rsh_06_str_00004224), 1090519040, (s32)((char*)rsh_06_str_00004228), (s32)((char*)rsh_06_str_000041FC),
    0, (s32)((char*)rsh_06_str_00004228), (s32)((char*)rsh_06_str_000041FC), 1082130432, (s32)((char*)rsh_06_str_00004228), (s32)((char*)rsh_06_str_000041FC), 1090519040, (s32)((char*)rsh_06_str_00004230),
    (s32)((char*)rsh_06_str_000041FC), 0, (s32)((char*)rsh_06_str_00004230), (s32)((char*)rsh_06_str_000041FC), 1082130432, (s32)((char*)rsh_06_str_00004230), (s32)((char*)rsh_06_str_000041FC), 1090519040,
    (s32)((char*)rsh_06_str_00004238), (s32)((char*)rsh_06_str_000041FC), 0, (s32)((char*)rsh_06_str_00004238), (s32)((char*)rsh_06_str_000041FC), 1082130432, (s32)((char*)rsh_06_str_00004238), (s32)((char*)rsh_06_str_000041FC),
    1090519040, (s32)((char*)rsh_06_str_00004240), (s32)((char*)rsh_06_str_000041FC), 0, (s32)((char*)rsh_06_str_00004240), (s32)((char*)rsh_06_str_000041FC), 1082130432, (s32)((char*)rsh_06_str_00004240),
    (s32)((char*)rsh_06_str_000041FC), 1090519040, 0, 0, 0,
#endif
};














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

    strcpy(model, (char*)zero_rsh_000145bc);
    strcpy(anim, (char*)zero_rsh_000145bc);
    wp->numDefs = -1;
    do {
        if (strcmp(data->model, model)) {
            strcpy(model, data->model);
            strcpy(anim, (char*)zero_rsh_000145bc);
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
        if (!strncmp(anim, (char*)str_00004B20, 1)) {
#endif
#ifndef NONMATCHING
        if (!strncmp(anim, (char*)rsh_06_str_00004B20, 1)) {
#endif
            wp->defs[wp->numDefs].loop = 0;
        }
        i++;
    } while ((++data)->model != NULL);
    wp->numDefs++;
}
#pragma dont_inline reset
#ifndef NONMATCHING
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXIdentity(Mtx m);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSVECAdd(const Vec* a, const Vec* b, Vec* ab);
f32 PSVECDistance(const Vec* a, const Vec* b);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
void *memset(void *dest, int ch, size_t count);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
void __cvt_ull_flt();
void __div2u();
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
static void moamoa_pose_main(void) {
#ifdef NONMATCHING
    f32 t;
    u64 now;
    s32 i;
    s32 sndFlag;
    ExtPose* pose;
    Moamoa* moa;
    MoamoaPoseDef* def;

    pose = extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, moa++, pose++) {
        now = gp->renderTime;
        def = &wp->defs[moa->pose];
        t = float_60_rsh_00014578[0] * OSTicksToMilliseconds(now - moa->startTime) / float_1000_rsh_0001457c[0] / def->speed;

        if (t >= float_1_rsh_00014470[0]) {
            moa->startTime = now;
            t = zero_rsh_00014490[0];
        }
        pose->frame = def->start + (s32)((def->count - 1) * t);
    }
#endif
#ifndef NONMATCHING
	char _af_pad[8];
	asm volatile {
		bl extGetPosePtr
		lis r4, wp@ha
		lis r7, float_60_rsh_00014578@ha
		addi r29, r4, wp@l
		lis r6, float_1000_rsh_0001457c@ha
		opword 0x813D0000
		lis r5, float_1_rsh_00014470@ha
		lis r4, double_to_int_rsh_00014488@ha
		lis r8, gp@ha
		opword 0x83090008
		opword 0x7C791B78
		lfs f28, float_60_rsh_00014578@l(r7)
		addi r30, r8, gp@l
		lfs f29, float_1000_rsh_0001457c@l(r6)
		opword 0x3B400000
		lfs f30, float_1_rsh_00014470@l(r5)
		opword 0x3FE08000
		lfd f31, double_to_int_rsh_00014488@l(r4)
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
		lis r3, zero_rsh_00014490@ha
		lfs f1, zero_rsh_00014490@l(r3)
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
static const char* group_tbl[][2] = {
        {(char*)rsh_06_str_000041D0, (char*)rsh_06_str_000041DC},
        {(char*)rsh_06_str_000041E4, (char*)rsh_06_str_000041DC},
        {(char*)rsh_06_str_000041F0, (char*)rsh_06_str_000041FC},
        {(char*)rsh_06_str_00004200, (char*)rsh_06_str_0000420C},
        {(char*)rsh_06_str_00004210, (char*)rsh_06_str_00004218},
        {(char*)rsh_06_str_0000421C, (char*)rsh_06_str_00004224},
        {(char*)rsh_06_str_00004228, (char*)rsh_06_str_000041FC},
        {(char*)rsh_06_str_00004230, (char*)rsh_06_str_000041FC},
        {(char*)rsh_06_str_00004238, (char*)rsh_06_str_000041FC},
        {(char*)rsh_06_str_00004240, (char*)rsh_06_str_000041FC},
        {(char*)rsh_06_str_000041D0, (char*)rsh_06_str_000041DC},
    };
#endif
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim) {
#ifdef NONMATCHING
    static const char* group_tbl[][2] = {
        {(char*)str_000041D0, (char*)str_000041DC},
        {(char*)str_000041E4, (char*)str_000041DC},
        {(char*)str_000041F0, (char*)str_000041FC},
        {(char*)str_00004200, (char*)str_0000420C},
        {(char*)str_00004210, (char*)str_00004218},
        {(char*)str_0000421C, (char*)str_00004224},
        {(char*)str_00004228, (char*)str_000041FC},
        {(char*)str_00004230, (char*)str_000041FC},
        {(char*)str_00004238, (char*)str_000041FC},
        {(char*)str_00004240, (char*)str_000041FC},
        {(char*)str_000041D0, (char*)str_000041DC},
    };
#endif
    MoamoaPoseDef* def = wp->defs;
    s32 i;

    if (moa->flags & 0x800) {
        model = group_tbl[moa->kind][0];
        if (moa->kind >= 2) {
            anim = group_tbl[moa->kind][1];
        }
        if (moa->kind == 10) {
#ifdef NONMATCHING
            anim = (char*)str_000048C4;
#endif
#ifndef NONMATCHING
            anim = (char*)rsh_06_str_000048C4;
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
            if (strncmp(anim, (char*)str_00004A40, 1)) {
#endif
#ifndef NONMATCHING
            if (strncmp(anim, (char*)rsh_06_str_00004A40, 1)) {
#endif
                return;
            }
        }
        if (moa->flags & 0x10) {
#ifdef NONMATCHING
            if (strncmp(anim, (char*)str_00004A44, 1)) {
#endif
#ifndef NONMATCHING
            if (strncmp(anim, (char*)rsh_06_str_00004A44, 1)) {
#endif
                return;
            }
        }
        moa->pose = i;
        moa->startTime = gp->renderTime;
    }
}
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
        pose->field_0x14 = zero_rsh_00014490[0];
        pose->field_0x1c = zero_rsh_00014490[0];
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
            pose->mtx[2][2] = float_1_rsh_00014470[0];
            pose->mtx[1][1] = float_1_rsh_00014470[0];
            pose->mtx[0][0] = float_1_rsh_00014470[0];
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
        moamoa_pose_change(moa, (char*)str_000041D0, (char*)str_000041DC);
#endif
#ifndef NONMATCHING
        moamoa_pose_change(moa, (char*)rsh_06_str_000041D0, (char*)rsh_06_str_000041DC);
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
        moamoa_pose_change(moa, (char*)str_000041D0, (char*)str_000041DC);
#endif
#ifndef NONMATCHING
        moamoa_pose_change(moa, (char*)rsh_06_str_000041D0, (char*)rsh_06_str_000041DC);
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
        moamoa_pose_change(moa, (char*)str_000041D0, (char*)str_000041DC);
#endif
#ifndef NONMATCHING
        moamoa_pose_change(moa, (char*)rsh_06_str_000041D0, (char*)rsh_06_str_000041DC);
#endif
    }
    return EVT_RETURN_DONE;
}
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
#endif
void evalOn(void) {
#ifdef NONMATCHING
    NpcEntry* npc = npcNameToPtr((char*)str_000047B4);
    AnimationPose* anim;
    Moamoa* moa;
    s32 i;
    s32 j;
    Vec* pos;
    s32 n;

    animPoseWorldPositionEvalOn(npc->poseId);
    wp->animPoseId = npc->poseId;
    anim = animPoseGetAnimPosePtr(npc->poseId);
    pos = anim->worldPositions[0];
    n = anim->numWorldPositions;
    for (i = 0; i < n; i++) {
        pos[i] = (Vec){zero_rsh_00014490[0], -float_1000_rsh_0001457c[0], zero_rsh_00014490[0]};
    }
    for (i = 0; i < dat_80419a28; i++) {
        wp->chainIdx[i][0] = animPoseGetGroupIdx(npc->poseId, g_moamoa_chain_tbl[i][0]);
        wp->chainIdx[i][1] = animPoseGetGroupIdx(npc->poseId, g_moamoa_chain_tbl[i][1]);
    }
    moa = wp->moa;
    for (j = 0; j < wp->count; j++, moa++) {
        moa->group = j % dat_80419a28;
        moa->order = wp->chainNum[moa->group]++;
    }
    moa = wp->moa;
    for (j = 0; j < wp->count; j++, moa++) {
        if (moa->group == 0 || moa->group == 5 || moa->group == 10 || moa->group == 15 || moa->group == 30 ||
            moa->group == 34 || moa->group == 38 || moa->group == 42 || moa->group == 46) {
            moa->kind = 1;
        }
        if (moa->order == 0) {
            if (moa->group == 3) {
                moa->kind = 2;
            }
            if (moa->group == 4) {
                moa->kind = 3;
            }
            if (moa->group == 7) {
                moa->kind = 4;
            }
            if (moa->group == 8) {
                moa->kind = 5;
            }
            if (moa->group == 9) {
                moa->kind = 6;
            }
            if (moa->group == 12) {
                moa->kind = 7;
            }
            if (moa->group == 13) {
                moa->kind = 8;
            }
            if (moa->group == 14) {
                moa->kind = 9;
            }
        }
    }
#endif
#ifndef NONMATCHING
	asm {
		lis r3, rsh_06_str_000047B4@ha
		addi r3, r3, rsh_06_str_000047B4@l
	}
	asm volatile {
		bl npcNameToPtr
		opword 0x7C7F1B78
		opword 0x80630104
		bl animPoseWorldPositionEvalOn
		lis r3, wp@ha
		opword 0x801F0104
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0x90030048
		opword 0x807F0104
		bl animPoseGetAnimPosePtr
		opword 0x80C3015C
		lis r4, vec3_rsh_00013cec@ha
		opword 0x80030160
		addi r5, r4, vec3_rsh_00013cec@l
		opword 0x80E60000
		opword 0x38600000
		opword 0x7C0903A6
		opword 0x2C000000
		opword 0x40810028
		opword 0x80850000
		opword 0x7CC71A14
		opword 0x80050004
		opword 0x3863000C
		opword 0x90860000
		opword 0x90060004
		opword 0x80050008
		opword 0x90060008
		opword 0x4200FFE0
		lis r3, dat_80419a28@ha
		lis r5, g_moamoa_chain_tbl@ha
		lis r4, wp@ha
		lwz r28, dat_80419a28@l(r3)
		addi r26, r5, g_moamoa_chain_tbl@l
		li r24, 0x0
		addi r27, r4, wp@l
		opword 0x3BC00000
		opword 0x3BA00000
		opword 0x48000044
		opword 0x7F3AEA14
		opword 0x807F0104
		opword 0x80990000
		bl animPoseGetGroupIdx
		opword 0x809B0000
		opword 0x381E0670
		opword 0x7C64032E
		opword 0x807F0104
		opword 0x80990004
		bl animPoseGetGroupIdx
		opword 0x809B0000
		opword 0x381E0672
		opword 0x3BDE0004
		opword 0x3BBD0008
		opword 0x7C64032E
		opword 0x3B180001
		opword 0x7C18E000
		opword 0x4180FFBC
		lis r4, wp@ha
		lis r3, dat_80419a28@ha
		addi r7, r4, wp@l
		lwz r6, dat_80419a28@l(r3)
		opword 0x80870000
		opword 0x39200000
		opword 0x81040008
		opword 0x4800003C
		opword 0x7C0933D6
		opword 0x7C0031D6
		opword 0x7C004850
		opword 0x39290001
		opword 0xB0080048
		opword 0xA8080048
		opword 0x80A70000
		opword 0x5403083C
		opword 0x38830570
		opword 0x7C6522AE
		opword 0x38030001
		opword 0x7C05232E
		opword 0xB068004A
		opword 0x39080050
		opword 0x80870000
		opword 0x80040004
		opword 0x7C090000
		opword 0x4180FFBC
		lis r3, wp@ha
		opword 0x80A40008
		addi r4, r3, wp@l
		opword 0x38C00000
		opword 0x4800010C
		opword 0xA8650048
		opword 0x7C600735
		opword 0x41820044
		opword 0x2C030005
		opword 0x4182003C
		opword 0x2C03000A
		opword 0x41820034
		opword 0x2C03000F
		opword 0x4182002C
		opword 0x2C03001E
		opword 0x41820024
		opword 0x2C030022
		opword 0x4182001C
		opword 0x2C030026
		opword 0x41820014
		opword 0x2C03002A
		opword 0x4182000C
		opword 0x2C03002E
		opword 0x4082000C
		opword 0x38000001
		opword 0x9805004C
		opword 0xA805004A
		opword 0x2C000000
		opword 0x408200A4
		opword 0xA8050048
		opword 0x2C000003
		opword 0x4082000C
		opword 0x38000002
		opword 0x9805004C
		opword 0xA8050048
		opword 0x2C000004
		opword 0x4082000C
		opword 0x38000003
		opword 0x9805004C
		opword 0xA8050048
		opword 0x2C000007
		opword 0x4082000C
		opword 0x38000004
		opword 0x9805004C
		opword 0xA8050048
		opword 0x2C000008
		opword 0x4082000C
		opword 0x38000005
		opword 0x9805004C
		opword 0xA8050048
		opword 0x2C000009
		opword 0x4082000C
		opword 0x38000006
		opword 0x9805004C
		opword 0xA8050048
		opword 0x2C00000C
		opword 0x4082000C
		opword 0x38000007
		opword 0x9805004C
		opword 0xA8050048
		opword 0x2C00000D
		opword 0x4082000C
		opword 0x38000008
		opword 0x9805004C
		opword 0xA8050048
		opword 0x2C00000E
		opword 0x4082000C
		opword 0x38000009
		opword 0x9805004C
		opword 0x38C60001
		opword 0x38A50050
		opword 0x80640000
		opword 0x80030004
		opword 0x7C060000
		opword 0x4180FEEC
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif
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
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
static f32 randf(f32 min, f32 max) {
#ifdef NONMATCHING
    f32 r = rand() / float_32767_rsh_000144ec[0];

    return r * (max - min) + min;
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
		lis r4, double_to_int_rsh_00014488@ha
		lis r3, float_32767_rsh_000144ec@ha
		lfd f3, double_to_int_rsh_00014488@l(r4)
		opword 0x90010008
		opword 0xEC1FF028
		lfs f1, float_32767_rsh_000144ec@l(r3)
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
#endif
}
#ifndef NONMATCHING
#pragma pop
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
static void ext_moamoa_init(void) {
#ifdef NONMATCHING
    s32 i;
    ExtPose* pose;
    Moamoa* moa;
    Vec v;
    f32 hitX, hitY, hitZ, dist, nx, ny, nz;

    wp = _mapAlloc(sizeof(MoamoaWork));
    memset(wp, 0, sizeof(MoamoaWork));
    wp->target[0] = (Vec){float_10_rsh_00014584[0], float_215_rsh_00014504[0], zero_rsh_00014490[0]};
    wp->target[1] = (Vec){float_10_rsh_00014584[0], float_215_rsh_00014504[0], zero_rsh_00014490[0]};
    wp->target[2] = (Vec){float_10_rsh_00014584[0], float_215_rsh_00014504[0], zero_rsh_00014490[0]};
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
        moamoa_pose_change(moa, (char*)str_000041D0, (char*)str_000041DC);
        pose->flags |= 7;
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = randf(-500.0f, 500.0f);
        pose->mtx[1][3] = float_215_rsh_00014504[0];
        pose->mtx[2][3] = randf(-float_45_rsh_00014574[0], float_45_rsh_00014574[0]);
        hitX = hitY = hitZ = zero_rsh_00014490[0];
        dist = float_1E06_rsh_00014594[0];
        if (hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &dist, &nx, &ny, &nz, pose->mtx[0][3], float_100_rsh_000144f8[0] + pose->mtx[1][3], pose->mtx[2][3], zero_rsh_00014490[0], -float_1_rsh_00014470[0], zero_rsh_00014490[0])) {
            pose->mtx[1][3] = hitY;
        } else {
            pose->flags |= 4;
            pose->mtx[0][3] = randf(-500.0f, 500.0f);
            pose->mtx[1][3] = randf(float_100_rsh_000144f8[0], float_215_rsh_00014504[0]);
            pose->mtx[2][3] = randf(70.0f, 75.0f);
            moa->flags |= 0x40;
            moamoa_pose_change(moa, (char*)str_000041D0, (char*)str_000041DC);
        }
        v = (Vec){zero_rsh_00014490[0], zero_rsh_00014490[0], zero_rsh_00014490[0]};
        v.x = randf(-float_10_rsh_00014584[0], float_10_rsh_00014584[0]);
        v.y = randf(-float_10_rsh_00014584[0], float_10_rsh_00014584[0]);
        v.z = randf(-float_10_rsh_00014584[0], float_10_rsh_00014584[0]);
        moa->jitter = v;
    }
    evalOn();
    for (i = 0; i < 600; i++) {
        ext_moamoa_main();
    }
#endif
#ifndef NONMATCHING
	char _af_pad[68];
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
		lis r3, vec3_rsh_00013cf8@ha
		addi r7, r3, vec3_rsh_00013cf8@l
		lis r4, vec3_rsh_00013d04@ha
		addi r9, r5, wp@l
		opword 0x80C70000
		opword 0x81090000
		lis r3, vec3_rsh_00013d10@ha
		opword 0x80070004
		addi r5, r4, vec3_rsh_00013d04@l
		addi r4, r3, vec3_rsh_00013d10@l
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
		lis r17, zero_rsh_00014490@ha
		addi r25, r4, wp@l
		lis r12, double_to_int_rsh_00014488@ha
		opword 0x82D90000
		addi r29, r17, zero_rsh_00014490@l
		lis r11, float_32767_rsh_000144ec@ha
		lis r10, float_1000_rsh_0001457c@ha
		lis r9, float_neg500_rsh_000145ac@ha
		lis r8, float_215_rsh_00014504@ha
		lis r7, float_90_rsh_00014534@ha
		lis r6, float_neg45_rsh_00014530@ha
		lis r5, float_1E06_rsh_00014594@ha
		lis r4, float_100_rsh_000144f8@ha
		lis r19, float_20_rsh_00014580@ha
		lis r18, float_neg10_rsh_000145b8@ha
		lis r24, rsh_06_str_000041DC@ha
		lis r21, rsh_06_str_000041D0@ha
		lis r20, vec3_rsh_00013d1c@ha
		lis r17, float_neg1_rsh_00014498@ha
		opword 0x83F60008
		addi r26, r24, rsh_06_str_000041DC@l
		lfd f20, double_to_int_rsh_00014488@l(r12)
		opword 0x7C771B78
		lfs f21, float_32767_rsh_000144ec@l(r11)
		addi r27, r21, rsh_06_str_000041D0@l
		lfs f22, float_1000_rsh_0001457c@l(r10)
		addi r22, r17, float_neg1_rsh_00014498@l
		lfs f23, float_neg500_rsh_000145ac@l(r9)
		addi r30, r20, vec3_rsh_00013d1c@l
		lfs f24, float_215_rsh_00014504@l(r8)
		opword 0x3B000000
		lfs f25, float_90_rsh_00014534@l(r7)
		opword 0x3F804330
		lfs f26, float_neg45_rsh_00014530@l(r6)
		opword 0xC37D0000
		lfs f28, float_1E06_rsh_00014594@l(r5)
		lfs f29, float_100_rsh_000144f8@l(r4)
		lfs f30, float_20_rsh_00014580@l(r19)
		lfs f31, float_neg10_rsh_000145b8@l(r18)
		opword 0x4800050C
		opword 0x38000000
		opword 0x7F52D378
		opword 0xB01F0000
		opword 0x7F73DB78
		opword 0xB01F0002
		opword 0xB01F0004
		opword 0xA01F0000
		opword 0x80790000
		opword 0x54000529
		opword 0x3A830050
		opword 0x41820038
		opword 0x889F004C
		lis r3, group_tbl@ha
		addi r0, r3, group_tbl@l
		opword 0x54831D78
		opword 0x28040002
		opword 0x7C601A14
		opword 0x82630000
		opword 0x41800008
		opword 0x82430004
		opword 0x2804000A
		opword 0x4082000C
		lis r3, rsh_06_str_000048C4@ha
		addi r18, r3, rsh_06_str_000048C4@l
		opword 0x3AA00000
		opword 0x48000034
		opword 0x7E83A378
		opword 0x7E649B78
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x7E449378
		opword 0x38740010
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3AB50001
		opword 0x3A940028
		opword 0x80790000
		opword 0x8003004C
		opword 0x7C150000
		opword 0x4180FFC4
		opword 0x80790000
		opword 0x8003004C
		opword 0x7C150000
		opword 0x40800080
		opword 0xA81F003C
		opword 0x7C00A800
		opword 0x41820074
		opword 0xA01F0000
		opword 0x5400077B
		opword 0x41820020
		lis r4, rsh_06_str_00004A40@ha
		opword 0x7E439378
		addi r4, r4, rsh_06_str_00004A40@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x4082004C
		opword 0xA01F0000
		opword 0x540006F7
		opword 0x41820020
		lis r4, rsh_06_str_00004A44@ha
		opword 0x7E439378
		addi r4, r4, rsh_06_str_00004A44@l
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
		opword 0x80170000
		opword 0x60000007
		opword 0x90170000
		opword 0x8077000C
		bl PSMTXIdentity
		bl rand
		opword 0x6C608000
		stw r28, _af_pad+40(r1)
		opword 0x8077000C
		opword 0x90010034
		opword 0xC8010030
		opword 0xEC00A028
		opword 0xEC00A824
		opword 0xEC00BDBA
		opword 0xD003000C
		opword 0x8077000C
		opword 0xD303001C
		bl rand
		opword 0x6C608000
		opword 0xC09D0000
		opword 0x9001003C
		opword 0x38810020
		opword 0x8177000C
		opword 0xFCC02090
		opword 0x93810038
		opword 0x38A1001C
		opword 0xC0B60000
		opword 0x38C10018
		opword 0xC8010038
		opword 0x38E10014
		opword 0x39010010
		opword 0xEC00A028
		opword 0x3921000C
		opword 0x39410008
		opword 0x38600000
		opword 0xEC00A824
		opword 0xEC00D67A
		opword 0xD00B002C
		opword 0xD3610018
		opword 0xD361001C
		opword 0xD3610020
		opword 0xD3810014
		opword 0x8177000C
		opword 0xC00B001C
		opword 0xC02B000C
		opword 0xEC5D002A
		opword 0xC06B002C
		bl hitCheckFilter
		opword 0x28030000
		opword 0x41820014
		opword 0xC001001C
		opword 0x8077000C
		opword 0xD003001C
		opword 0x48000258
		opword 0x80170000
		opword 0x60000004
		opword 0x90170000
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061003C
		lis r4, double_to_int_rsh_00014488@ha
		lfd f1, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x90010038
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC0450000
		lis r4, float_1000_rsh_0001457c@ha
		opword 0xC8010038
		lis r3, float_neg500_rsh_000145ac@ha
		opword 0xEC600828
		lfs f0, float_neg500_rsh_000145ac@l(r3)
		lfs f1, float_1000_rsh_0001457c@l(r4)
		opword 0x8077000C
		opword 0xEC431024
		opword 0xEC02007A
		opword 0xD003000C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x90610034
		lis r4, double_to_int_rsh_00014488@ha
		lfd f1, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x90010030
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC0450000
		lis r4, float_115_rsh_000145b0@ha
		opword 0xC8010030
		lis r3, float_100_rsh_000144f8@ha
		opword 0xEC600828
		lfs f0, float_100_rsh_000144f8@l(r3)
		lfs f1, float_115_rsh_000145b0@l(r4)
		opword 0x8077000C
		opword 0xEC431024
		opword 0xEC02007A
		opword 0xD003001C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x90610044
		lis r4, double_to_int_rsh_00014488@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x90010040
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC0050000
		lis r4, float_5_rsh_00014500@ha
		opword 0xC8210040
		lis r3, float_70_rsh_000145b4@ha
		addi r7, r4, float_5_rsh_00014500@l
		lis r4, rsh_06_str_000041D0@ha
		opword 0xEC411028
		addi r6, r3, float_70_rsh_000145b4@l
		addi r20, r4, rsh_06_str_000041D0@l
		lis r3, wp@ha
		lis r5, rsh_06_str_000041DC@ha
		opword 0xC0270000
		opword 0xEC420024
		opword 0xC0060000
		opword 0x8097000C
		addi r3, r3, wp@l
		addi r21, r5, rsh_06_str_000041DC@l
		opword 0xEC02007A
		opword 0xD004002C
		opword 0xA01F0000
		opword 0x60000040
		opword 0xB01F0000
		opword 0xA01F0000
		opword 0x80630000
		opword 0x54000529
		opword 0x3A630050
		opword 0x41820038
		opword 0x889F004C
		lis r3, group_tbl@ha
		addi r0, r3, group_tbl@l
		opword 0x54831D78
		opword 0x28040002
		opword 0x7C601A14
		opword 0x82830000
		opword 0x41800008
		opword 0x82A30004
		opword 0x2804000A
		opword 0x4082000C
		lis r3, rsh_06_str_000048C4@ha
		addi r21, r3, rsh_06_str_000048C4@l
		lis r3, wp@ha
		opword 0x3A400000
		addi r17, r3, wp@l
		opword 0x48000034
		opword 0x7E639B78
		opword 0x7E84A378
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x7EA4AB78
		opword 0x38730010
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3A520001
		opword 0x3A730028
		opword 0x80710000
		opword 0x8003004C
		opword 0x7C120000
		opword 0x4180FFC4
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0x8003004C
		opword 0x7C120000
		opword 0x40800080
		opword 0xA81F003C
		opword 0x7C009000
		opword 0x41820074
		opword 0xA01F0000
		opword 0x5400077B
		opword 0x41820020
		lis r4, rsh_06_str_00004A40@ha
		opword 0x7EA3AB78
		addi r4, r4, rsh_06_str_00004A40@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x4082004C
		opword 0xA01F0000
		opword 0x540006F7
		opword 0x41820020
		lis r4, rsh_06_str_00004A44@ha
		opword 0x7EA3AB78
		addi r4, r4, rsh_06_str_00004A44@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x40820024
		lis r3, gp@ha
		opword 0xB25F003C
		addi r3, r3, gp@l
		opword 0x80630000
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F0044
		opword 0x901F0040
		opword 0x809E0000
		opword 0x807E0004
		opword 0x801E0008
		opword 0x90810024
		opword 0x90610028
		opword 0x9001002C
		bl rand
		opword 0x6C608000
		opword 0x93810040
		opword 0x90010044
		opword 0xC8010040
		opword 0xEC00A028
		opword 0xEC00A824
		opword 0xEC00FFBA
		opword 0xD0010024
		bl rand
		opword 0x6C608000
		opword 0x93810038
		opword 0x9001003C
		opword 0xC8010038
		opword 0xEC00A028
		opword 0xEC00A824
		opword 0xEC00FFBA
		opword 0xD0010028
		bl rand
		opword 0x6C608000
		opword 0x80610024
		opword 0x90010034
		opword 0x3B180001
		opword 0x80010028
		opword 0x3AF70020
		opword 0x93810030
		opword 0xC8010030
		opword 0x907F0030
		opword 0xEC00A028
		opword 0x901F0034
		opword 0xEC00A824
		opword 0xEC00FFBA
		opword 0xD001002C
		opword 0x8001002C
		opword 0x901F0038
		opword 0x3BFF0050
		opword 0x80790000
		opword 0x80030004
		opword 0x7C180000
		opword 0x4180FAEC
		bl evalOn
		opword 0x3A200000
		bl ext_moamoa_main
		opword 0x3A310001
		opword 0x2C110258
		opword 0x4180FFF4
	}
#endif
}
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
        offscreenAddBoundingBox(offscreenNameToId((char*)str_00004B00), left, top, right, bottom);
#endif
#ifndef NONMATCHING
        offscreenAddBoundingBox(offscreenNameToId((char*)rsh_06_str_00004B00), left, top, right, bottom);
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
        offscreenAddBoundingBox(offscreenNameToId((char*)str_00004B00), left, top, right, bottom);
#endif
#ifndef NONMATCHING
        offscreenAddBoundingBox(offscreenNameToId((char*)rsh_06_str_00004B00), left, top, right, bottom);
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
        hitX = hitY = hitZ = zero_rsh_00014490[0];
        dist = float_1E06_rsh_00014594[0];
        if (hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &dist, &nx, &ny, &nz, x, float_100_rsh_000144f8[0] + y, z, zero_rsh_00014490[0], -float_1_rsh_00014470[0], zero_rsh_00014490[0])) {
            if (__fabs(y - hitY) > double_30_rsh_00014598) {
                speed -= float_0p1_rsh_000144f0[0];
                gravity += float_0p1_rsh_000144f0[0];
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
    pose->rot = float_180_rsh_00014538[0] + angle;
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
		lis r4, zero_rsh_00014490@ha
		lis r3, float_100_rsh_000144f8@ha
		addi r5, r4, zero_rsh_00014490@l
		lfs f0, float_100_rsh_000144f8@l(r3)
		opword 0xC0850000
		lis r4, float_1E06_rsh_00014594@ha
		lfs f7, float_1E06_rsh_00014594@l(r4)
		lis r3, float_neg1_rsh_00014498@ha
		opword 0xFCC02090
		lfs f5, float_neg1_rsh_00014498@l(r3)
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
		lis r3, double_30_rsh_00014598@ha
		opword 0xEC3C0028
		lfd f0, double_30_rsh_00014598@l(r3)
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x40810014
		lis r3, float_0p1_rsh_000144f0@ha
		lfs f0, float_0p1_rsh_000144f0@l(r3)
		opword 0xEFFF0028
		opword 0xEFDE002A
		opword 0xC381001C
		lis r3, vec3_rsh_00013d28@ha
		addi r4, r3, vec3_rsh_00013d28@l
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
		lis r4, double_to_int_rsh_00014488@ha
		lis r3, float_0p5_rsh_000144e8@ha
		opword 0xEC1F0024
		addi r6, r4, double_to_int_rsh_00014488@l
		addi r4, r3, float_0p5_rsh_000144e8@l
		lis r3, float_180_rsh_00014538@ha
		opword 0x90A10040
		opword 0x38000003
		opword 0xFC40001E
		lfs f0, float_180_rsh_00014538@l(r3)
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
#pragma dont_inline reset
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

    if (mario->position.y > float_20_rsh_00014580[0] + pose->mtx[1][3]) {
        return 0;
    }
    if (pose->mtx[1][3] > mario->position.y + mario->wPlayerCollisionBox.y) {
        return 0;
    }
    if (distABf(pose->mtx[0][3], pose->mtx[2][3], mario->position.x, mario->position.z) < (float_20_rsh_00014580[0] + mario->wPlayerCollisionBox.x) / 2
        && mario->position.y > float_10_rsh_00014584[0] + pose->mtx[1][3] && (mario->flags & 0x20000) && !(mario->flags & 0x10000)
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
        cam = camGetPtr(CAMERA_3D);
        {
            f32 yaw = cam->viewYaw;
            rad = reviseAngle((mario->displayDirection - float_90_rsh_00014534[0]) + yaw);
        }
        angle = float_35_rsh_00014588[0] * moa_sin((float_6p2832_rsh_0001449c[0] * rad) / float_360_rsh_000144a0[0]) + mario->position.x;
        dist = mario->position.z - float_35_rsh_00014588[0] * moa_cos((float_6p2832_rsh_0001449c[0] * rad) / float_360_rsh_000144a0[0]);
        if (distABf(pose->mtx[0][3], pose->mtx[2][3], angle, dist) < float_35_rsh_00014588[0]) {
            return 2;
        }
    }
    if (mario->currMotionId == 0x13 && (s32)mario->currSubMotionId == 0x14) {
        { f32 (*m)[4] = pose->mtx; a = (Vec){m[0][3], m[1][3], m[2][3]}; }
        if (PSVECDistance(&mario->position, &a) < float_65_rsh_0001458c[0]) {
            return 2;
        }
    }
    if (wp->breathDir >= zero_rsh_00014490[0]) {
        { f32 (*m)[4] = pose->mtx; b = (Vec){m[0][3], m[1][3], m[2][3]}; }
        if (PSVECDistance(&wp->breathPos, &b) < float_30_rsh_000144dc[0]) {
            return 3;
        }
    }
    if (nokonokoGetStatus(partyGetPtr(0)) == 2) {
        { f32 (*m)[4] = pose->mtx; c = (Vec){m[0][3], m[1][3], m[2][3]}; }
        if (PSVECDistance(&partyGetPtr(0)->position, &c) < float_30_rsh_000144dc[0]) {
            return 2;
        }
    }
    if (partyGetPtr(0)->currentMemberId == 3 && partyGetPtr(0)->useMotionId == 0x46) {
        { f32 (*m)[4] = pose->mtx; d = (Vec){m[0][3], m[1][3], m[2][3]}; }
        if (PSVECDistance(&partyGetPtr(0)->position, &d) < float_50_rsh_000144fc[0]) {
            return 4;
        }
    }
    e = (Vec){mario->position.x, pose->mtx[1][3], mario->position.z};
    { f32 (*m)[4] = pose->mtx; f = (Vec){m[0][3], m[1][3], m[2][3]}; }
    range = (float_20_rsh_00014580[0] + mario->wPlayerCollisionBox.x) / 2;
    if (PSVECDistance(&e, &f) < range) {
        pose->mtx[0][3] = moa->lastX;
        pose->mtx[2][3] = moa->lastZ;
        { f32 (*m)[4] = pose->mtx; f = (Vec){m[0][3], m[1][3], m[2][3]}; }
        dist = PSVECDistance(&e, &f);
        if (dist < range) {
            angle = angleABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
            if (__fabsf(compAngle(angle, mario->directionView)) < float_40_rsh_00014590[0]) {
                mario->unk174.x = -((range - dist) * moa_sin(float_6p2832_rsh_0001449c[0] * mario->directionView / float_360_rsh_000144a0[0]));
                mario->unk174.z = (range - dist) * moa_cos(float_6p2832_rsh_0001449c[0] * mario->directionView / float_360_rsh_000144a0[0]);
            } else {
                rad = float_6p2832_rsh_0001449c[0] * angle / float_360_rsh_000144a0[0];
                mario->unk174.x = pose->mtx[0][3] - range * moa_sin(rad) - mario->position.x;
                mario->unk174.z = pose->mtx[2][3] + range * moa_cos(rad) - mario->position.z;
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
		lis r4, float_20_rsh_00014580@ha
		lfs f0, float_20_rsh_00014580@l(r4)
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
		lis r4, float_20_rsh_00014580@ha
		lis r3, float_0p5_rsh_000144e8@ha
		opword 0xC05F01B4
		lfs f3, float_20_rsh_00014580@l(r4)
		lfs f0, float_0p5_rsh_000144e8@l(r3)
		opword 0xEC43102A
		opword 0xEC020032
		opword 0xFC010040
		opword 0x40800088
		opword 0x807D000C
		lis r4, float_10_rsh_00014584@ha
		lfs f1, float_10_rsh_00014584@l(r4)
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
		lis r4, float_90_rsh_00014534@ha
		opword 0xC03F01A8
		lfs f0, float_90_rsh_00014534@l(r4)
		opword 0xC0430114
		opword 0xEC010028
		opword 0xEC20102A
		bl reviseAngle
		lis r3, float_6p2832_rsh_0001449c@ha
		lis r6, float_0p00761_rsh_000144a4@ha
		addi r5, r3, float_6p2832_rsh_0001449c@l
		lis r4, float_360_rsh_000144a0@ha
		opword 0xC0050000
		lis r5, float_0p16605_rsh_000144a8@ha
		lis r3, float_3p1416_rsh_000144ac@ha
		lfs f4, float_0p00761_rsh_000144a4@l(r6)
		opword 0xEC400072
		lfs f0, float_360_rsh_000144a0@l(r4)
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r4, float_1_rsh_00014470@ha
		lfs f3, float_0p16605_rsh_000144a8@l(r5)
		opword 0xECC20024
		lfs f2, float_1_rsh_00014470@l(r4)
		opword 0xFC060840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC060040
		opword 0x40800020
		opword 0xEC260828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC060028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		lis r3, float_3p1416_rsh_000144ac@ha
		lis r4, float_35_rsh_00014588@ha
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r5, float_0p03705_rsh_000144b8@ha
		lfs f2, float_35_rsh_00014588@l(r4)
		lis r4, float_0p4967_rsh_000144bc@ha
		opword 0xC01F008C
		opword 0xFC060840
		lis r3, float_1_rsh_00014470@ha
		lfs f5, float_0p03705_rsh_000144b8@l(r5)
		opword 0xEC62013A
		lfs f4, float_0p4967_rsh_000144bc@l(r4)
		lfs f2, float_1_rsh_00014470@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC060040
		opword 0x4080001C
		opword 0xEC060828
		opword 0xEC000032
		opword 0xECA52038
		opword 0xECA5103A
		opword 0xFCA02850
		opword 0x48000020
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC060028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xECA52038
		opword 0xECA5103A
		lis r3, float_35_rsh_00014588@ha
		opword 0x809D000C
		opword 0xC01F0094
		lfs f2, float_35_rsh_00014588@l(r3)
		opword 0xC024000C
		opword 0xEC82017C
		opword 0xC044002C
		bl distABf
		lis r3, float_35_rsh_00014588@ha
		lfs f0, float_35_rsh_00014588@l(r3)
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
		lis r3, vec3_rsh_00013d34@ha
		opword 0x811D000C
		addi r7, r3, vec3_rsh_00013d34@l
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
		lis r3, float_65_rsh_0001458c@ha
		lfs f0, float_65_rsh_0001458c@l(r3)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600002
		opword 0x48000700
		lis r4, wp@ha
		lis r3, zero_rsh_00014490@ha
		addi r4, r4, wp@l
		lfs f0, zero_rsh_00014490@l(r3)
		opword 0x80840000
		opword 0xC024055C
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082007C
		lis r3, vec3_rsh_00013d40@ha
		opword 0x811D000C
		addi r7, r3, vec3_rsh_00013d40@l
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
		lis r3, float_30_rsh_000144dc@ha
		lfs f0, float_30_rsh_000144dc@l(r3)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600003
		opword 0x48000664
		opword 0x38600000
		bl partyGetPtr
		bl nokonokoGetStatus
		opword 0x2C030002
		opword 0x40820084
		lis r3, vec3_rsh_00013d4c@ha
		opword 0x80FD000C
		addi r6, r3, vec3_rsh_00013d4c@l
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
		lis r3, float_30_rsh_000144dc@ha
		lfs f0, float_30_rsh_000144dc@l(r3)
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
		lis r3, vec3_rsh_00013d58@ha
		opword 0x80FD000C
		addi r6, r3, vec3_rsh_00013d58@l
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
		lis r3, float_50_rsh_000144fc@ha
		lfs f0, float_50_rsh_000144fc@l(r3)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600004
		opword 0x48000528
		lis r3, vec3_rsh_00013d64@ha
		opword 0x817D000C
		addi r5, r3, vec3_rsh_00013d64@l
		lis r3, vec3_rsh_00013d70@ha
		opword 0x80850000
		addi r9, r3, vec3_rsh_00013d70@l
		opword 0x80050004
		lis r3, float_20_rsh_00014580@ha
		opword 0x81450008
		addi r6, r3, float_20_rsh_00014580@l
		opword 0x90810020
		lis r3, float_0p5_rsh_000144e8@ha
		opword 0xC01F008C
		addi r5, r3, float_0p5_rsh_000144e8@l
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
		lis r3, vec3_rsh_00013d7c@ha
		opword 0x80BD000C
		addi r7, r3, vec3_rsh_00013d7c@l
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
		lis r3, float_40_rsh_00014590@ha
		opword 0xFC200A10
		lfs f0, float_40_rsh_00014590@l(r3)
		opword 0xFC010040
		opword 0x408001D4
		lis r3, float_6p2832_rsh_0001449c@ha
		lis r6, float_0p00761_rsh_000144a4@ha
		addi r5, r3, float_6p2832_rsh_0001449c@l
		opword 0xC01F01A0
		opword 0xC0250000
		lis r5, float_0p16605_rsh_000144a8@ha
		lis r4, float_360_rsh_000144a0@ha
		lis r3, float_3p1416_rsh_000144ac@ha
		opword 0xEC410032
		lfs f0, float_360_rsh_000144a0@l(r4)
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r4, float_1_rsh_00014470@ha
		lfs f4, float_0p00761_rsh_000144a4@l(r6)
		opword 0xECA20024
		lfs f3, float_0p16605_rsh_000144a8@l(r5)
		lfs f2, float_1_rsh_00014470@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xECA50828
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xECA10028
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0xFC802050
		opword 0xECDFE828
		lis r3, float_6p2832_rsh_0001449c@ha
		addi r8, r3, float_6p2832_rsh_0001449c@l
		lis r6, float_0p03705_rsh_000144b8@ha
		lis r3, float_360_rsh_000144a0@ha
		opword 0xC0680000
		opword 0xEC060132
		addi r7, r3, float_360_rsh_000144a0@l
		lis r5, float_0p4967_rsh_000144bc@ha
		lis r3, float_3p1416_rsh_000144ac@ha
		lis r4, float_1_rsh_00014470@ha
		lfs f5, float_0p03705_rsh_000144b8@l(r6)
		opword 0xFC200050
		opword 0xC0070000
		lfs f4, float_0p4967_rsh_000144bc@l(r5)
		opword 0xD03F0174
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		opword 0xC05F01A0
		opword 0xEC4300B2
		lfs f3, float_1_rsh_00014470@l(r4)
		opword 0xEC420024
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC020040
		opword 0x4080001C
		opword 0xEC420828
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xFCA02850
		opword 0x48000020
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC020028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC410028
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xEC060172
		opword 0xD01F017C
		opword 0x480001C0
		lis r3, float_6p2832_rsh_0001449c@ha
		lis r6, float_0p00761_rsh_000144a4@ha
		addi r5, r3, float_6p2832_rsh_0001449c@l
		lis r4, float_360_rsh_000144a0@ha
		opword 0xC0050000
		lis r3, float_3p1416_rsh_000144ac@ha
		lis r5, float_0p16605_rsh_000144a8@ha
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		opword 0xEC4007B2
		lfs f0, float_360_rsh_000144a0@l(r4)
		lis r4, float_1_rsh_00014470@ha
		lfs f4, float_0p00761_rsh_000144a4@l(r6)
		lfs f3, float_0p16605_rsh_000144a8@l(r5)
		opword 0xECA20024
		lfs f2, float_1_rsh_00014470@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x809D000C
		lis r3, float_3p1416_rsh_000144ac@ha
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r5, float_0p03705_rsh_000144b8@ha
		opword 0xC004000C
		lis r4, float_0p4967_rsh_000144bc@ha
		opword 0xFC050840
		lis r3, float_1_rsh_00014470@ha
		opword 0xEC5F013C
		opword 0xC01F008C
		lfs f4, float_0p03705_rsh_000144b8@l(r5)
		lfs f3, float_0p4967_rsh_000144bc@l(r4)
		opword 0xEC020028
		lfs f2, float_1_rsh_00014470@l(r3)
		opword 0xD01F0174
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING
__declspec(section ".rodata") static Vec moamoa_zero_vec = {0.0f, 0.0f, 0.0f};
#endif
#ifndef NONMATCHING
extern void* rsh_06_jumptable_000183EC[];
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
static void ext_moamoa_main(void) {
#ifdef NONMATCHING
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    s32 hit = 0;
    s32 sndFlag;
    const char* sfx;
    s32 i;
    s32 ret;
    s32 idx;
    ExtPose* pose;
    ExtPose* other;
    Moamoa*  m;
    f32 spd;
    f32 rad;
    f32 dist;
    f32 angle;
    f32 x; f32 y; f32 z;
    f32 x0; f32 z0; f32 x1; f32 z1; f32 x2; f32 z2; f32 x3; f32 z3; f32 x4; f32 z4; f32 x5; f32 z5;
    f32 grav;
    f32 s;
    f32 tx; f32 ty; f32 tz;
    Vec sp;
    Vec jv;
    Vec pv;
    Mtx rot;
    f32 cnt = zero_rsh_00014490[0];
    f32 a;
    f32 d;
    f32 t;
    f32 r;

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
    wp->breathDir = -float_1_rsh_00014470[0];
    wp->breathDist = -float_1_rsh_00014470[0];
    if (( party->currentMemberId == 5 ) && (party->flags & 0x100)) {
        wp->breathDir = cloudGetBreathDir();
        wp->breathDist = cloudGetBreathDist();
        wp->breathPos.x = ( wp->breathDist * moa_sinx(( float_6p2832_rsh_0001449c[0] * wp->breathDir ) / float_360_rsh_000144a0[0]) ) + party->position.x;
        wp->breathPos.y = party->position.y;
        wp->breathPos.z = party->position.z - ( wp->breathDist * moa_cosx(( float_6p2832_rsh_0001449c[0] * wp->breathDir ) / float_360_rsh_000144a0[0]) );
    }

    pose = extGetPosePtr();
    sndFlag = 0;
    m = wp->moa;
    sfx = (char*)str_00004A20;
    for (i = 0; i < wp->count; i++, pose++, m++) {
        wp->angle = angleABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
        wp->dist = distABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
        if ((( !(m->flags & 0x154) ) && ( mario->position.y > float_200_rsh_000144d8[0] )) && ( wp->dist < float_30_rsh_000144dc[0]) ) {
            cnt += float_1_rsh_00014470[0];
        }
        if (((((( wp->flags & 1) && ( !(wp->flags & 4) )) && ( !marioKeyOffChk() )) && ( !marioCtrlOffChk() )) && ( !hit )) && ( !(m->flags & 0x154) )) {
            ret = moamoa_hit_check(pose, m);
            if (ret == 1) {
                m->flags |= 4;
                m->state = 36;
                wp->hitCount++;
                moamoa_pose_change(m, (char*)str_000041D0, (char*)str_000041E0);
                hit = 1;
            } else if (( ret == 2 ) || ( ret == 4) ) {
                m->flags |= 0xc;
                m->state = 47;
                wp->hitCount++;
                moamoa_pose_change(m, (char*)str_000041D0, (char*)str_000041E0);
                if (ret != 4) {
                    hit = 1;
                }
            } else if (ret == 3) {
                angle = wp->breathDir + wp->angle;
                angle *= float_0p5_rsh_000144e8[0];
                m->flags |= 0x84;
                m->state = 48;
                m->target = moamoa_zero_vec;
                { spd = randf(float_0p1_rsh_000144f0[0], float_0p2_rsh_00014544[0]);
                rad = ( float_6p2832_rsh_0001449c[0] * angle ) / float_360_rsh_000144a0[0];
                m->vy = spd * moa_sinx(rad);
                m->speed = randf(float_0p03_rsh_000144f4[0], 0.06f);
                m->gravity = spd * ( -moa_cosx(rad)) ; }
                m->jumpTimer = 120;
                wp->hitCount++;
                moamoa_pose_change(m, (char*)str_000041D0, (char*)str_000041E0);
                hit = 1;
            }
        }
        if ((wp->flags & 1) && ( !(m->flags & 0x155)) ) {
            if ((( (mario->currMotionId == 0 ) || (( (u16)(mario->currMotionId - 1) ) <= 1 )) || (( (u16)(mario->currMotionId - 0x15) ) <= 1 )) ||
                ( mario->currMotionId == 0x1a) ) {
                if ((( (mario->position.y > float_200_rsh_000144d8[0] ) && ( wp->dist > float_30_rsh_000144dc[0] )) && ( wp->dist < float_100_rsh_000144f8[0] )) && (i & 1)) {
                    if (m->flags & 2) {
                        m->next = 2;
                    } else {
                        m->state = 2;
                    }
                }
            } else if (wp->dist < float_50_rsh_000144fc[0]) {
                if (m->flags & 2) {
                    m->next = 1;
                } else {
                    m->state = 1;
                }
            }
        }
        if (((( wp->flags & 1) && ( !(m->flags & 0x444) )) && ( i == ( gp->retraceCount % wp->count ))) && ( irand(1000) < 200) ) {
            sp = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
            psndSFXOn_3D(sfx, &sp);
        }
        switch (m->state) {
            case 0:
                if (m->flags & 0x40) {
                    break;
                }
                angle = randf(zero_rsh_00014490[0], float_360_rsh_000144a0[0]);
                x0 = ( float_5_rsh_00014500[0] * moa_sinx(( float_6p2832_rsh_0001449c[0] * angle ) / float_360_rsh_000144a0[0]) ) + pose->mtx[0][3];
                z0 = pose->mtx[2][3] - ( float_5_rsh_00014500[0] * moa_cosx(( float_6p2832_rsh_0001449c[0] * angle ) / float_360_rsh_000144a0[0]) );
                {
                    f32 r1 = rand() / float_32767_rsh_000144ec[0];
                    f32 r2 = rand() / float_32767_rsh_000144ec[0];
                    moamoa_jump(pose, m, m->state, 0, x0, float_215_rsh_00014504[0], z0, ( r1 * (float_0p5_rsh_000144e8[0] - float_0p3_rsh_00014508[0]) ) + float_0p3_rsh_00014508[0], ( r2 * (float_0p8_rsh_00014520[0] - float_0p5_rsh_000144e8[0]) ) + float_0p5_rsh_000144e8[0]);
                }
                break;
            case 14:
                if (( --m->timer ) < 0) {
                    m->timer = 0;
                    m->state++;
                }
                break;
            case 15:
                dist = distABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[i % 3].x, wp->target[i % 3].z);
                angle = angleABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[i % 3].x, wp->target[i % 3].z);
                if (dist > float_31_rsh_00014510[0]) {
                    x1 = ( float_30_rsh_000144dc[0] * moa_sinx(( float_6p2832_rsh_0001449c[0] * angle ) / float_360_rsh_000144a0[0]) ) + pose->mtx[0][3];
                    z1 = pose->mtx[2][3] - ( float_30_rsh_000144dc[0] * moa_cosx(( float_6p2832_rsh_0001449c[0] * angle ) / float_360_rsh_000144a0[0]) );
                    { f32 r1 = rand() / float_32767_rsh_000144ec[0]; f32 r2 = rand() / float_32767_rsh_000144ec[0]; f32 z0 = zero_rsh_00014490[0]; y = (r1 * z0) + float_1_rsh_00014470[0];
                    moamoa_jump(pose, m, m->state, 0, x1, float_215_rsh_00014504[0], z1, float_2_rsh_00014514[0] * y, float_2_rsh_00014514[0] * (( r2 * z0 ) + float_0p4_rsh_00014518[0])); }
                } else {
                    moamoa_joint_position(m, &jv);
                    PSVECAdd(&jv, &m->jitter, &jv);
                    { f32 r1 = rand() / float_32767_rsh_000144ec[0]; f32 r2 = rand() / float_32767_rsh_000144ec[0]; f32 z0 = zero_rsh_00014490[0]; moamoa_jump(pose, m, 61, 0, jv.x, jv.y, jv.z, float_2_rsh_00014514[0] * (( r1 * z0 ) + float_1p5_rsh_0001451c[0]), float_2_rsh_00014514[0] * (( r2 * z0 ) + float_0p8_rsh_00014520[0])); }
                    m->flags |= 0x200;
                    pose->flags |= 4;
                }
                break;
            case 61:
                moamoa_joint_position(m, &pv);
                PSVECAdd(&pv, &m->jitter, &pv);
                pose->mtx[0][3] = pv.x;
                pose->mtx[1][3] = pv.y;
                pose->mtx[2][3] = pv.z;
                break;
            case 50:
                if (( --m->timer ) < 0) {
                    m->timer = 0;
                    m->state++;
                }
                break;
            case 51:
                m->speed = randf(zero_rsh_00014490[0], float_200_rsh_000144d8[0]);
                m->gravity = randf(zero_rsh_00014490[0], float_300_rsh_00014524[0] * m->speed / float_200_rsh_000144d8[0]);
                m->state++;
                m->timer = 0;
            case 52:
                s = m->timer < 200 ? float_1_rsh_00014470[0] : (800 - m->timer) / float_600_rsh_00014528[0];
                if (s < zero_rsh_00014490[0]) {
                    s = zero_rsh_00014490[0];
                    m->flags |= 0x200;
                }
                tx = wp->target[i % 3].x;
                ty = wp->target[i % 3].y;
                tz = wp->target[i % 3].z;
                tx += s * (m->gravity * (f32)sin((f32)(i + gp->retraceCount) * float_0p25_rsh_0001452c[0]));
                r = i + gp->retraceCount;
                ty += m->speed * s;
                { f32 cv = (f32)cos(r * float_0p25_rsh_0001452c[0]);
                tz += s * (-m->gravity * cv); }
                pose->mtx[0][3] += (tx - pose->mtx[0][3]) / float_15_rsh_00014474[0];
                pose->mtx[1][3] += (ty - pose->mtx[1][3]) / float_15_rsh_00014474[0];
                pose->mtx[2][3] += (tz - pose->mtx[2][3]) / float_15_rsh_00014474[0];
                m->timer++;
                break;
            case 1:
                {
                f32 rad;
                {
                f32 a = wp->angle + randf(-float_45_rsh_00014574[0], float_45_rsh_00014574[0]);
                rad = float_6p2832_rsh_0001449c[0];
                rad = rad * a / float_360_rsh_000144a0[0];
                }
                x = pose->mtx[0][3] + float_15_rsh_00014474[0] * moa_sinx(rad);
                d = wp->dist;
                y = pose->mtx[1][3];
                z = pose->mtx[2][3] - float_15_rsh_00014474[0] * moa_cosx(rad);
                { f32 k; f32 r1 = rand() / float_32767_rsh_000144ec[0]; spd = r1 * (k = float_1_rsh_00014470[0] - float_1_rsh_00014470[0]) + float_1_rsh_00014470[0];
                moamoa_jump(pose, m, d < float_100_rsh_000144f8[0] ? m->state : 0, 0, x, y, z, spd, randf(float_0p4_rsh_00014518[0], float_0p4_rsh_00014518[0])); }
                }
                break;
            case 2:
                a = wp->angle + randf(-float_45_rsh_00014574[0], float_45_rsh_00014574[0]);
                a += float_180_rsh_00014538[0];
                d = wp->dist;
                {
                f32 rad = float_6p2832_rsh_0001449c[0] * a / float_360_rsh_000144a0[0];
                x = pose->mtx[0][3] + float_30_rsh_000144dc[0] * moa_sinx(rad);
                }
                y = pose->mtx[1][3];
                z = pose->mtx[2][3];
                { f32 a1 = float_2_rsh_00014514[0] * randf(float_1_rsh_00014470[0], float_1_rsh_00014470[0]); f32 a2 = float_2_rsh_00014514[0] * randf(float_0p4_rsh_00014518[0], float_0p4_rsh_00014518[0]); moamoa_jump(pose, m, d < float_100_rsh_000144f8[0] ? m->state : 0, 0, x, y, z, a1, a2); }
                break;
            case 3:
                pose->mtx[1][3] += m->vy;
                m->vy -= m->gravity;
                angle = angleABf(pose->mtx[0][3], pose->mtx[2][3], m->target.x, m->target.z);
                pose->mtx[0][3] += m->speed * moa_sinx(( float_6p2832_rsh_0001449c[0] * angle ) / float_360_rsh_000144a0[0]);
                pose->mtx[2][3] += m->speed * ( -moa_cosx( (float_6p2832_rsh_0001449c[0] * angle ) / float_360_rsh_000144a0[0]) );
                if (( --m->jumpTimer ) < 0) {
                    pose->mtx[0][3] = m->target.x;
                    pose->mtx[1][3] = m->target.y;
                    pose->mtx[2][3] = m->target.z;
                    m->flags &= ~2;
                    pose->flags &= ~0x10;
                    m->timer = 0;
                    m->state++;
                }
                break;
            case 4:
                if (( ++m->timer ) > 4) {
                    m->state = m->next;
                }
                break;
            case 36:
            case 37:
            case 38:
                if (!(m->flags & 1)) {
                    tx = mario->position.x;
                    tz = mario->position.z;
                } else {
                    tx = wp->target[i % 3].x;
                    tz = wp->target[i % 3].z;
                }
                {
                f32 r1 = rand() / float_32767_rsh_000144ec[0];
                f32 rad = float_6p2832_rsh_0001449c[0] * (angleABf(tx, tz, pose->mtx[0][3], pose->mtx[2][3]) + (r1 * (float_45_rsh_00014574[0] - -float_45_rsh_00014574[0]) + -float_45_rsh_00014574[0])) / float_360_rsh_000144a0[0];
                x = pose->mtx[0][3] + float_15_rsh_00014474[0] * moa_sinx(rad);
                y = pose->mtx[1][3];
                z = pose->mtx[2][3] - float_15_rsh_00014474[0] * moa_cosx(rad);
                }
                { f32 k; f32 r1 = rand() / float_32767_rsh_000144ec[0]; f32 r2 = rand() / float_32767_rsh_000144ec[0]; k = float_1_rsh_00014470[0] - float_1_rsh_00014470[0]; moamoa_jump(pose, m, m->state + 1, 1, x, y, z, r1 * k + float_1_rsh_00014470[0], r2 * k + float_1_rsh_00014470[0]); }
                break;
            case 39:
                if (( ++m->timer ) < 30) {
                    pose->mtx[0][0] *= float_0p9_rsh_0001453c[0];
                    pose->mtx[1][1] *= float_0p9_rsh_0001453c[0];
                    pose->mtx[2][2] *= float_0p9_rsh_0001453c[0];
                } else {
                    m->state = 49;
                }
                break;
            case 47:
                { f32 rad, d; f32 r1 = rand() / float_32767_rsh_000144ec[0]; f32 r2 = rand() / float_32767_rsh_000144ec[0];
                rad = float_6p2832_rsh_0001449c[0] * (r1 * (float_225_rsh_00014550[0] - float_135_rsh_00014540[0]) + float_135_rsh_00014540[0]) / float_360_rsh_000144a0[0];
                d = r2 * (500.0f - float_200_rsh_000144d8[0]) + float_200_rsh_000144d8[0];
                x5 = pose->mtx[0][3] + d * moa_sinx(rad);
                z5 = pose->mtx[2][3] - d * moa_cosx(rad); }
                ty = rand() / float_32767_rsh_000144ec[0] * (6.0f - float_5_rsh_00014500[0]) + float_5_rsh_00014500[0];
                s = rand() / float_32767_rsh_000144ec[0] * (float_0p3_rsh_00014508[0] - float_0p2_rsh_00014544[0]) + float_0p2_rsh_00014544[0];
                if (!sndFlag) {
                    psndSFXOn_3D((const char*)0x6c3, &(( Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]})) ;
                    sndFlag = 1;
                }
                moamoa_jump(pose, m, 49, 0, x5, -float_100_rsh_000144f8[0], z5, ty, s);
                break;
            case 48:
                if (( --m->jumpTimer ) > 0) {
                    m->target.x += m->vy;
                    m->target.y += m->speed;
                    m->target.z += m->gravity;
                    pose->mtx[0][3] += m->target.x;
                    pose->mtx[1][3] += m->target.y;
                    pose->mtx[2][3] += m->target.z;
                } else {
                    m->state = 49;
                }
                break;
            case 49:
                PSMTXIdentity(pose->mtx);
                { Moamoa* mm;
                do {
                    idx = rand() % 700;
                    mm = &wp->moa[idx];
                } while ((( mm->state != 0 ) && ( mm->state != 3) ) || (mm->flags & 0x40)); }
                other = extGetPosePtr() + idx;
                pose->mtx[0][3] = other->mtx[0][3];
                pose->mtx[1][3] = float_215_rsh_00014504[0];
                pose->mtx[2][3] = other->mtx[2][3];
                m->flags = 0;
                m->state = 0;
                m->timer = 0;
                break;
            case 62:
                m->flags |= 0x20;
                pose->flags &= ~1;
                pose->flags |= 4;
                break;
            case 63:
                { f32 k; f32 r1 = rand() / float_32767_rsh_000144ec[0];
                spd = randf(float_2_rsh_00014514[0], 3.0f);
                m->timer = irand(i / 2);
                rad = float_6p2832_rsh_0001449c[0] * (r1 * (k = 315.0f - float_225_rsh_00014550[0]) + float_225_rsh_00014550[0]) / float_360_rsh_000144a0[0]; }
                m->target.x = spd * moa_sinx(rad);
                m->target.y = randf(float_1_rsh_00014470[0], float_2_rsh_00014514[0]);
                m->target.z = spd * ( -moa_cosx(rad)) ;
                m->state++;
                break;
            case 64:
                if (( --m->timer ) < 0) {
                    m->state++;
                }
                break;
            case 65:
                m->target.x *= float_1p1_rsh_00014554[0];
                m->target.y *= float_1p02_rsh_00014558[0];
                m->target.z *= float_1p1_rsh_00014554[0];
                pose->mtx[0][3] += m->target.x;
                pose->mtx[1][3] += m->target.y;
                pose->mtx[2][3] += m->target.z;
                PSMTXRotRad(rot, 'y', float_0p20944_rsh_0001455c[0]);
                PSMTXConcat(pose->mtx, rot, pose->mtx);
                pose->flags &= ~2;
                if (pose->mtx[0][3] < ( -float_1000_rsh_0001457c[0]) ) {
                    m->state = 62;
                }
                break;
        }
        if (!(m->flags & 0x588)) {
            f32 nx;
            if ( (cam->cameraAt.x - pose->mtx[0][3] ) > float_250_rsh_00014564[0]) {
                nx = float_450_rsh_00014568[0] + pose->mtx[0][3];
                if (nx < ( -float_50_rsh_000144fc[0]) ) {
                    pose->mtx[0][3] = nx;
                }
            } else if (( pose->mtx[0][3] - cam->cameraAt.x ) > float_250_rsh_00014564[0]) {
                nx = pose->mtx[0][3] - float_450_rsh_00014568[0];
                if (nx > ( -1870.0f) ) {
                    pose->mtx[0][3] = nx;
                }
            }
        }
        if (!(m->flags & 0x588)) {
            if (pose->mtx[0][3] > float_100_rsh_000144f8[0]) {
                t = float_100_rsh_000144f8[0];
                pose->mtx[0][3] = t + randf(zero_rsh_00014490[0], float_5_rsh_00014500[0]);
            }
            if (pose->mtx[0][3] < -1870.0f) {
                t = -1870.0f;
                pose->mtx[0][3] = t + randf(zero_rsh_00014490[0], float_5_rsh_00014500[0]);
            }
            if (!(m->flags & 0x40)) {
                if (pose->mtx[2][3] > float_45_rsh_00014574[0]) {
                    t = float_45_rsh_00014574[0];
                    pose->mtx[2][3] = t + randf(zero_rsh_00014490[0], float_5_rsh_00014500[0]);
                }
                if (pose->mtx[2][3] < -float_45_rsh_00014574[0]) {
                    t = -float_45_rsh_00014574[0];
                    pose->mtx[2][3] = t + randf(zero_rsh_00014490[0], float_5_rsh_00014500[0]);
                }
            }
        }
        m->lastX = pose->mtx[0][3];
        m->lastZ = pose->mtx[2][3];
    }
    moamoa_pose_main();
    mario->unk174.x = zero_rsh_00014490[0];
    mario->unk174.y = zero_rsh_00014490[0];
    mario->unk174.z = zero_rsh_00014490[0];
    if (!(wp->flags & 0x18)) {
        mario->unk174.x = ( -cnt ) / float_20_rsh_00014580[0];
    }
#endif
#ifndef NONMATCHING
	char _af_pad[164];
	asm volatile {
		bl marioGetPtr
		opword 0x7C7C1B78
		opword 0x38600000
		bl partyGetPtr
		opword 0x7C751B78
		opword 0x38600004
		bl camGetPtr
		opword 0xA01C002E
		lis r4, zero_rsh_00014490@ha
		lfs f31, zero_rsh_00014490@l(r4)
		opword 0x7C771B78
		opword 0x28000012
		opword 0x3B200000
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
		opword 0x80150000
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
		lis r4, float_neg1_rsh_00014498@ha
		lis r3, wp@ha
		addi r5, r4, float_neg1_rsh_00014498@l
		addi r4, r3, wp@l
		opword 0xC0050000
		opword 0x80640000
		opword 0xD003055C
		opword 0x80640000
		opword 0xD0030560
		opword 0x88150031
		opword 0x2C000005
		opword 0x40820230
		opword 0x80150000
		opword 0x540005EF
		opword 0x41820224
		bl cloudGetBreathDir
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0xD023055C
		bl cloudGetBreathDist
		lis r3, wp@ha
		lis r4, float_6p2832_rsh_0001449c@ha
		addi r10, r3, wp@l
		lis r7, float_0p00761_rsh_000144a4@ha
		opword 0x80AA0000
		lis r3, float_360_rsh_000144a0@ha
		addi r8, r3, float_360_rsh_000144a0@l
		addi r9, r4, float_6p2832_rsh_0001449c@l
		opword 0xD0250560
		lis r3, float_3p1416_rsh_000144ac@ha
		addi r4, r3, float_3p1416_rsh_000144ac@l
		lis r6, float_0p16605_rsh_000144a8@ha
		opword 0x806A0000
		lis r5, float_1_rsh_00014470@ha
		opword 0xC0490000
		opword 0xC023055C
		opword 0xC0080000
		opword 0xEC420072
		opword 0xC0240000
		lfs f4, float_0p00761_rsh_000144a4@l(r7)
		lfs f3, float_0p16605_rsh_000144a8@l(r6)
		opword 0xECA20024
		lfs f2, float_1_rsh_00014470@l(r5)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r4, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r4)
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
		lis r4, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r4)
		opword 0xFC050040
		opword 0x40800020
		opword 0xECA50828
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0xFC802050
		opword 0x48000028
		lis r4, float_1p5708_rsh_000144b0@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_000144b0@l(r4)
		opword 0xECA10028
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0xFC802050
		opword 0xC0230560
		lis r9, wp@ha
		opword 0xC0150058
		lis r4, float_6p2832_rsh_0001449c@ha
		addi r8, r4, float_6p2832_rsh_0001449c@l
		lis r6, float_0p03705_rsh_000144b8@ha
		opword 0xEC01013A
		lis r4, float_360_rsh_000144a0@ha
		addi r7, r4, float_360_rsh_000144a0@l
		lis r5, float_0p4967_rsh_000144bc@ha
		lis r4, float_3p1416_rsh_000144ac@ha
		addi r10, r9, wp@l
		opword 0xD0030564
		lis r3, float_1_rsh_00014470@ha
		opword 0xC0680000
		opword 0xC015005C
		opword 0x812A0000
		lfs f1, float_3p1416_rsh_000144ac@l(r4)
		opword 0xD0090568
		opword 0xC0070000
		opword 0x80EA0000
		lfs f5, float_0p03705_rsh_000144b8@l(r6)
		opword 0xC047055C
		lfs f4, float_0p4967_rsh_000144bc@l(r5)
		opword 0xEC4300B2
		lfs f3, float_1_rsh_00014470@l(r3)
		opword 0xEC420024
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC020040
		opword 0x4080001C
		opword 0xEC420828
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xFCA02850
		opword 0x48000020
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC020028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC410028
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xC0270560
		opword 0xC0150060
		opword 0xEC01017C
		opword 0xD007056C
		bl extGetPosePtr
		lis r5, wp@ha
		lis r4, rsh_06_str_00004A20@ha
		addi r27, r5, wp@l
		opword 0x7C7E1B78
		opword 0x80BB0000
		addi r24, r4, rsh_06_str_00004A20@l
		opword 0x3B400000
		opword 0x3BA00000
		opword 0x83E50008
		opword 0x48002A74
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
		opword 0xA01F0000
		opword 0x70000154
		opword 0x40820044
		lis r3, float_200_rsh_000144d8@ha
		opword 0xC03C0090
		lfs f0, float_200_rsh_000144d8@l(r3)
		opword 0xFC010040
		opword 0x40810030
		lis r4, wp@ha
		lis r3, float_30_rsh_000144dc@ha
		addi r4, r4, wp@l
		lfs f0, float_30_rsh_000144dc@l(r3)
		opword 0x80840000
		opword 0xC0240554
		opword 0xFC010040
		opword 0x40800010
		lis r3, float_1_rsh_00014470@ha
		lfs f0, float_1_rsh_00014470@l(r3)
		opword 0xEFFF002A
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
		opword 0x7C751B78
		opword 0x2C150001
		opword 0x40820170
		opword 0xA01F0000
		lis r4, rsh_06_str_000041E0@ha
		lis r3, rsh_06_str_000041D0@ha
		lis r5, wp@ha
		opword 0x60060004
		opword 0x38000024
		opword 0xB0DF0000
		addi r20, r4, rsh_06_str_000041E0@l
		addi r25, r3, rsh_06_str_000041D0@l
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
		lis r3, group_tbl@ha
		addi r0, r3, group_tbl@l
		opword 0x54831D78
		opword 0x28040002
		opword 0x7C601A14
		opword 0x83230000
		opword 0x41800008
		opword 0x82830004
		opword 0x2804000A
		opword 0x4082000C
		lis r3, rsh_06_str_000048C4@ha
		addi r20, r3, rsh_06_str_000048C4@l
		lis r3, wp@ha
		opword 0x3AA00000
		addi r17, r3, wp@l
		opword 0x48000034
		opword 0x7EC3B378
		opword 0x7F24CB78
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x7E84A378
		opword 0x38760010
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3AB50001
		opword 0x3AD60028
		opword 0x80710000
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
		lis r4, rsh_06_str_00004A40@ha
		opword 0x7E83A378
		addi r4, r4, rsh_06_str_00004A40@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x4082004C
		opword 0xA01F0000
		opword 0x540006F7
		opword 0x41820020
		lis r4, rsh_06_str_00004A44@ha
		opword 0x7E83A378
		addi r4, r4, rsh_06_str_00004A44@l
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
		opword 0x3B200001
		opword 0x48000570
		opword 0x2C150002
		opword 0x4182000C
		opword 0x2C150004
		opword 0x40820178
		opword 0xA01F0000
		lis r4, rsh_06_str_000041E0@ha
		lis r3, rsh_06_str_000041D0@ha
		lis r5, wp@ha
		opword 0x6006000C
		opword 0x3800002F
		opword 0xB0DF0000
		addi r18, r4, rsh_06_str_000041E0@l
		addi r19, r3, rsh_06_str_000041D0@l
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
		lis r3, group_tbl@ha
		addi r0, r3, group_tbl@l
		opword 0x54831D78
		opword 0x28040002
		opword 0x7C601A14
		opword 0x82630000
		opword 0x41800008
		opword 0x82430004
		opword 0x2804000A
		opword 0x4082000C
		lis r3, rsh_06_str_000048C4@ha
		addi r18, r3, rsh_06_str_000048C4@l
		lis r3, wp@ha
		opword 0x3A800000
		addi r17, r3, wp@l
		opword 0x48000034
		opword 0x7EC3B378
		opword 0x7E649B78
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x7E449378
		opword 0x38760010
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3A940001
		opword 0x3AD60028
		opword 0x80710000
		opword 0x8003004C
		opword 0x7C140000
		opword 0x4180FFC4
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0x8003004C
		opword 0x7C140000
		opword 0x40800080
		opword 0xA81F003C
		opword 0x7C00A000
		opword 0x41820074
		opword 0xA01F0000
		opword 0x5400077B
		opword 0x41820020
		lis r4, rsh_06_str_00004A40@ha
		opword 0x7E439378
		addi r4, r4, rsh_06_str_00004A40@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x4082004C
		opword 0xA01F0000
		opword 0x540006F7
		opword 0x41820020
		lis r4, rsh_06_str_00004A44@ha
		opword 0x7E439378
		addi r4, r4, rsh_06_str_00004A44@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x40820024
		lis r3, gp@ha
		opword 0xB29F003C
		addi r3, r3, gp@l
		opword 0x80630000
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F0044
		opword 0x901F0040
		opword 0x2C150004
		opword 0x418203F4
		opword 0x3B200001
		opword 0x480003EC
		opword 0x2C150003
		opword 0x408203E4
		lis r3, wp@ha
		opword 0xA01F0000
		addi r4, r3, wp@l
		opword 0x80E40000
		opword 0x60050084
		lis r4, float_0p5_rsh_000144e8@ha
		opword 0x38000030
		opword 0xC047055C
		addi r6, r4, float_0p5_rsh_000144e8@l
		opword 0xC0270550
		lis r3, vec3_rsh_00013d88@ha
		addi r4, r3, vec3_rsh_00013d88@l
		opword 0xC0060000
		opword 0xB0BF0000
		opword 0xEC22082A
		opword 0xB01F0002
		fmuls f26, f1, f0
		opword 0x80640000
		opword 0x80040004
		opword 0x907F0008
		opword 0x901F000C
		opword 0x80040008
		opword 0x901F0010
		bl rand
		opword 0x6C648000
		opword 0x3C004330
		lis r3, float_6p2832_rsh_0001449c@ha
		stw r4, _af_pad+140(r1)
		lfs f0, float_6p2832_rsh_0001449c@l(r3)
		lis r5, double_to_int_rsh_00014488@ha
		opword 0x90010090
		lis r3, float_360_rsh_000144a0@ha
		lfd f3, double_to_int_rsh_00014488@l(r5)
		opword 0xEC2006B2
		lfs f0, float_360_rsh_000144a0@l(r3)
		lis r4, float_32767_rsh_000144ec@ha
		opword 0xC8410090
		lis r5, float_0p00761_rsh_000144a4@ha
		opword 0xEFA10024
		lis r3, float_3p1416_rsh_000144ac@ha
		lfs f5, float_0p00761_rsh_000144a4@l(r5)
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r3, float_1_rsh_00014470@ha
		opword 0xEC621828
		lfs f2, float_32767_rsh_000144ec@l(r4)
		lis r4, float_0p1_rsh_000144f0@ha
		addi r6, r4, float_0p1_rsh_000144f0@l
		opword 0xFC1D0840
		opword 0xEC431024
		opword 0xC0060000
		lis r4, float_0p16605_rsh_000144a8@ha
		lfs f4, float_0p16605_rsh_000144a8@l(r4)
		lfs f3, float_1_rsh_00014470@l(r3)
		opword 0xEFC2003A
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xFC1D0840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC1D0772
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50772
		opword 0x48000070
		opword 0xEC1D0828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0x48000054
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC1D0040
		opword 0x40800020
		opword 0xEC3D0828
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC1D0028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0xEC1E0172
		opword 0xD01F0014
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_rsh_00014488@ha
		opword 0x90610094
		addi r5, r4, double_to_int_rsh_00014488@l
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x90010090
		addi r4, r3, float_32767_rsh_000144ec@l
		opword 0xC8450000
		lis r3, float_0p03_rsh_000144f4@ha
		opword 0xC8210090
		addi r6, r3, float_0p03_rsh_000144f4@l
		opword 0xC0040000
		lis r5, float_0p03705_rsh_000144b8@ha
		opword 0xEC411028
		lis r3, float_3p1416_rsh_000144ac@ha
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r4, float_0p4967_rsh_000144bc@ha
		lis r3, float_1_rsh_00014470@ha
		lfs f4, float_0p03705_rsh_000144b8@l(r5)
		opword 0xEC420024
		opword 0xC0060000
		lfs f3, float_0p4967_rsh_000144bc@l(r4)
		opword 0xEC02003A
		lfs f2, float_1_rsh_00014470@l(r3)
		opword 0xFC1D0840
		opword 0xD01F001C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xFC1D0840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC1D0772
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x48000064
		opword 0xEC1D0828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000048
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC1D0040
		opword 0x4080001C
		opword 0xEC1D0828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC1D0028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC002050
		lis r4, rsh_06_str_000041E0@ha
		lis r3, rsh_06_str_000041D0@ha
		opword 0x38000078
		lis r5, wp@ha
		addi r21, r4, rsh_06_str_000041E0@l
		opword 0xEC1E0032
		addi r20, r3, rsh_06_str_000041D0@l
		opword 0xD01F0020
		opword 0xB01F0018
		lwzu r4, wp@l(r5)
		opword 0xA8640038
		opword 0x38030001
		opword 0xB0040038
		opword 0xA01F0000
		opword 0x80650000
		opword 0x54000529
		opword 0x3A630050
		opword 0x41820038
		opword 0x889F004C
		lis r3, group_tbl@ha
		addi r0, r3, group_tbl@l
		opword 0x54831D78
		opword 0x28040002
		opword 0x7C601A14
		opword 0x82830000
		opword 0x41800008
		opword 0x82A30004
		opword 0x2804000A
		opword 0x4082000C
		lis r3, rsh_06_str_000048C4@ha
		addi r21, r3, rsh_06_str_000048C4@l
		lis r3, wp@ha
		opword 0x3A400000
		addi r22, r3, wp@l
		opword 0x48000034
		opword 0x7E639B78
		opword 0x7E84A378
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x7EA4AB78
		opword 0x38730010
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3A520001
		opword 0x3A730028
		opword 0x80760000
		opword 0x8003004C
		opword 0x7C120000
		opword 0x4180FFC4
		lis r3, wp@ha
		addi r3, r3, wp@l
		opword 0x80630000
		opword 0x8003004C
		opword 0x7C120000
		opword 0x40800080
		opword 0xA81F003C
		opword 0x7C009000
		opword 0x41820074
		opword 0xA01F0000
		opword 0x5400077B
		opword 0x41820020
		lis r4, rsh_06_str_00004A40@ha
		opword 0x7EA3AB78
		addi r4, r4, rsh_06_str_00004A40@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x4082004C
		opword 0xA01F0000
		opword 0x540006F7
		opword 0x41820020
		lis r4, rsh_06_str_00004A44@ha
		opword 0x7EA3AB78
		addi r4, r4, rsh_06_str_00004A44@l
		opword 0x38A00001
		bl strncmp
		opword 0x2C030000
		opword 0x40820024
		lis r3, gp@ha
		opword 0xB25F003C
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
		opword 0x418200D4
		opword 0xA0BF0000
		opword 0x70A00155
		opword 0x408200C8
		opword 0xA07C002E
		opword 0x28030000
		opword 0x4182002C
		opword 0x3803FFFF
		opword 0x5400043E
		opword 0x28000001
		opword 0x4081001C
		opword 0x3803FFEB
		opword 0x5400043E
		opword 0x28000001
		opword 0x4081000C
		opword 0x2803001A
		opword 0x40820064
		lis r3, float_200_rsh_000144d8@ha
		opword 0xC03C0090
		lfs f0, float_200_rsh_000144d8@l(r3)
		opword 0xFC010040
		opword 0x40810080
		lis r3, float_30_rsh_000144dc@ha
		opword 0xC0240554
		lfs f0, float_30_rsh_000144dc@l(r3)
		opword 0xFC010040
		opword 0x4081006C
		lis r3, float_100_rsh_000144f8@ha
		lfs f0, float_100_rsh_000144f8@l(r3)
		opword 0xFC010040
		opword 0x4080005C
		opword 0x57A007FF
		opword 0x41820054
		opword 0x54A007BD
		opword 0x41820010
		opword 0x38000002
		opword 0xB01F0024
		opword 0x48000040
		opword 0x38000002
		opword 0xB01F0002
		opword 0x48000034
		lis r3, float_50_rsh_000144fc@ha
		opword 0xC0240554
		lfs f0, float_50_rsh_000144fc@l(r3)
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
		lis r3, vec3_rsh_00013d94@ha
		opword 0x80BE000C
		addi r8, r3, vec3_rsh_00013d94@l
		opword 0x7F03C378
		opword 0x80E80000
		opword 0x38810050
		opword 0x80C80004
		opword 0x80080008
		opword 0x90E1002C
		opword 0xC005000C
		opword 0x90C10030
		opword 0xC025001C
		opword 0xD001002C
		opword 0xC005002C
		opword 0x90010034
		opword 0x80C1002C
		opword 0xD0210030
		opword 0xD0010034
		opword 0x80A10030
		opword 0x80010034
		opword 0x90C10050
		opword 0x90A10054
		opword 0x90010058
		bl psndSFXOn_3D
		opword 0xA81F0002
		opword 0x28000041
		opword 0x41811E8C
		lis r3, rsh_06_jumptable_000183EC@ha
		opword 0x5400103A
		addi r3, r3, rsh_06_jumptable_000183EC@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0xA01F0000
		opword 0x54000673
		opword 0x40821E68
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x90610094
		lis r4, double_to_int_rsh_00014488@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x90010090
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC0050000
		lis r4, float_360_rsh_000144a0@ha
		opword 0xC8210090
		lis r3, zero_rsh_00014490@ha
		addi r8, r4, float_360_rsh_000144a0@l
		lis r4, float_6p2832_rsh_0001449c@ha
		opword 0xEC211028
		addi r9, r4, float_6p2832_rsh_0001449c@l
		addi r7, r3, zero_rsh_00014490@l
		lis r6, float_0p00761_rsh_000144a4@ha
		lis r5, float_0p16605_rsh_000144a8@ha
		opword 0xC0480000
		opword 0xEC210024
		opword 0xC0070000
		opword 0xC0690000
		lis r3, float_3p1416_rsh_000144ac@ha
		lis r4, float_1_rsh_00014470@ha
		lfs f5, float_0p00761_rsh_000144a4@l(r6)
		opword 0xEC0100BA
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lfs f4, float_0p16605_rsh_000144a8@l(r5)
		opword 0xEC030032
		lfs f3, float_1_rsh_00014470@l(r4)
		opword 0xECC01024
		opword 0xFC060840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC060040
		opword 0x40800020
		opword 0xEC260828
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC060028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		lis r3, float_3p1416_rsh_000144ac@ha
		opword 0x80DE000C
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r4, float_5_rsh_00014500@ha
		lfs f2, float_5_rsh_00014500@l(r4)
		lis r5, float_0p03705_rsh_000144b8@ha
		opword 0xC006000C
		opword 0xFC060840
		lis r4, float_0p4967_rsh_000144bc@ha
		lis r3, float_1_rsh_00014470@ha
		opword 0xEF62017A
		lfs f4, float_0p03705_rsh_000144b8@l(r5)
		lfs f3, float_0p4967_rsh_000144bc@l(r4)
		lfs f2, float_1_rsh_00014470@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC060040
		opword 0x4080001C
		opword 0xEC060828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC060028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_5_rsh_00014500@ha
		opword 0xC006002C
		lfs f1, float_5_rsh_00014500@l(r3)
		opword 0xEF41013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x90610094
		lis r4, double_to_int_rsh_00014488@ha
		lis r3, float_32767_rsh_000144ec@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		opword 0x90010090
		lfs f0, float_32767_rsh_000144ec@l(r3)
		opword 0xC8210090
		opword 0xEC211028
		opword 0xEF810024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061009C
		lis r4, double_to_int_rsh_00014488@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x90010098
		lis r5, float_0p2_rsh_0001450c@ha
		lfs f0, float_32767_rsh_000144ec@l(r3)
		lis r4, float_0p3_rsh_00014508@ha
		opword 0xC8210098
		lis r3, float_0p5_rsh_000144e8@ha
		lfs f4, float_0p2_rsh_0001450c@l(r5)
		lis r6, float_215_rsh_00014504@ha
		opword 0xEC211028
		lfs f5, float_0p3_rsh_00014508@l(r4)
		lfs f2, float_215_rsh_00014504@l(r6)
		opword 0xFC60D090
		opword 0xEC9C293A
		opword 0xA8BF0002
		opword 0xECC10024
		lfs f0, float_0p5_rsh_000144e8@l(r3)
		opword 0x7FC3F378
		opword 0x7FE4FB78
		opword 0x38C00000
		opword 0xFC20D890
		opword 0xECA6017A
		bl moamoa_jump
		opword 0x48001BC8
		opword 0xA87F0004
		opword 0x3863FFFF
		opword 0x7C600735
		opword 0xB07F0004
		opword 0x40801BB4
		opword 0x38000000
		opword 0xB01F0004
		opword 0xA87F0002
		opword 0x38030001
		opword 0xB01F0002
		opword 0x48001B9C
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
		opword 0x1E20000C
		opword 0x7C648A14
		opword 0xC0630014
		opword 0xC083001C
		bl distABf
		lis r3, wp@ha
		opword 0x809E000C
		lwz r0, wp@l(r3)
		opword 0xFF600890
		opword 0xC024000C
		opword 0x7C608A14
		opword 0xC044002C
		opword 0xC0630014
		opword 0xC083001C
		bl angleABf
		lis r3, float_31_rsh_00014510@ha
		lfs f0, float_31_rsh_00014510@l(r3)
		opword 0xFC1B0040
		opword 0x4081027C
		lis r3, float_6p2832_rsh_0001449c@ha
		lis r6, float_0p00761_rsh_000144a4@ha
		addi r5, r3, float_6p2832_rsh_0001449c@l
		lis r4, float_360_rsh_000144a0@ha
		opword 0xC0050000
		lis r5, float_0p16605_rsh_000144a8@ha
		lis r3, float_3p1416_rsh_000144ac@ha
		lfs f4, float_0p00761_rsh_000144a4@l(r6)
		opword 0xEC400072
		lfs f0, float_360_rsh_000144a0@l(r4)
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r4, float_1_rsh_00014470@ha
		lfs f3, float_0p16605_rsh_000144a8@l(r5)
		opword 0xECA20024
		lfs f2, float_1_rsh_00014470@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		lis r3, float_3p1416_rsh_000144ac@ha
		opword 0x80DE000C
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r4, float_30_rsh_000144dc@ha
		lfs f2, float_30_rsh_000144dc@l(r4)
		lis r4, float_0p4967_rsh_000144bc@ha
		opword 0xC006000C
		opword 0xFC050840
		lis r5, float_0p03705_rsh_000144b8@ha
		lis r3, float_1_rsh_00014470@ha
		opword 0xEFA2013A
		lfs f4, float_0p03705_rsh_000144b8@l(r5)
		lfs f3, float_0p4967_rsh_000144bc@l(r4)
		lfs f2, float_1_rsh_00014470@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_30_rsh_000144dc@ha
		opword 0xC006002C
		lfs f1, float_30_rsh_000144dc@l(r3)
		opword 0xEF81013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061009C
		lis r4, double_to_int_rsh_00014488@ha
		lis r3, float_32767_rsh_000144ec@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		opword 0x90010098
		lfs f0, float_32767_rsh_000144ec@l(r3)
		opword 0xC8210098
		opword 0xEC211028
		opword 0xEF610024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x90610094
		lis r4, double_to_int_rsh_00014488@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x90010090
		lis r5, zero_rsh_00014490@ha
		lfs f0, float_32767_rsh_000144ec@l(r3)
		lis r4, float_1_rsh_00014470@ha
		opword 0xC8210090
		addi r6, r5, zero_rsh_00014490@l
		lis r3, float_0p4_rsh_00014518@ha
		addi r5, r4, float_1_rsh_00014470@l
		opword 0xEC211028
		addi r4, r3, float_0p4_rsh_00014518@l
		opword 0xC0460000
		lis r3, float_2_rsh_00014514@ha
		addi r7, r3, float_2_rsh_00014514@l
		lis r8, float_215_rsh_00014504@ha
		opword 0xEC610024
		opword 0xC0250000
		opword 0xC0040000
		opword 0x7FC3F378
		opword 0xC0A70000
		opword 0x7FE4FB78
		opword 0xEC9B08BA
		opword 0xA8BF0002
		opword 0xEC0300BA
		lfs f2, float_215_rsh_00014504@l(r8)
		opword 0xFC20E890
		opword 0x38C00000
		opword 0xEC850132
		opword 0xFC60E090
		opword 0xECA50032
		bl moamoa_jump
		opword 0x480018B0
		lis r3, rsh_06_str_000047B4@ha
		addi r3, r3, rsh_06_str_000047B4@l
		bl npcNameToPtr
		opword 0x80630104
		bl animPoseGetAnimPosePtr
		opword 0xA8FF0048
		opword 0x3CA04330
		lis r4, wp@ha
		opword 0x8063015C
		addi r6, r4, wp@l
		opword 0x90A10098
		opword 0x54E4083C
		opword 0x81060000
		opword 0x38040570
		opword 0xA89F004A
		opword 0x7C0802AE
		lis r6, double_to_int_rsh_00014488@ha
		opword 0x6C848000
		opword 0x54E7103A
		opword 0x9081009C
		opword 0x6C008000
		lfd f2, double_to_int_rsh_00014488@l(r6)
		opword 0x7D083A14
		opword 0xC8010098
		opword 0x38810044
		opword 0x90010094
		opword 0xEC201028
		opword 0xA8E80672
		opword 0x90A10090
		opword 0xA8080670
		opword 0x1CC7000C
		opword 0xC8010090
		opword 0x80630000
		opword 0xEC001028
		opword 0x1C00000C
		opword 0x7E233214
		opword 0xEF610024
		opword 0x7C630214
		opword 0xFC20D890
		bl PSVECScale
		lis r4, float_1_rsh_00014470@ha
		opword 0x7E238B78
		addi r5, r4, float_1_rsh_00014470@l
		opword 0x38810014
		opword 0xC0050000
		opword 0xEC20D828
		bl PSVECScale
		opword 0x38610044
		opword 0x38810014
		opword 0x7C651B78
		bl PSVECAdd
		opword 0x38610044
		opword 0x389F0030
		opword 0x7C651B78
		bl PSVECAdd
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100A4
		lis r4, double_to_int_rsh_00014488@ha
		lis r3, float_32767_rsh_000144ec@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		opword 0x900100A0
		lfs f0, float_32767_rsh_000144ec@l(r3)
		opword 0xC82100A0
		opword 0xEC211028
		opword 0xEF610024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00014488@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A8
		lis r6, float_2_rsh_00014514@ha
		lfs f0, float_32767_rsh_000144ec@l(r3)
		lis r5, zero_rsh_00014490@ha
		opword 0xC82100A8
		lis r4, float_1p5_rsh_0001451c@ha
		lfs f5, float_2_rsh_00014514@l(r6)
		lis r3, float_0p8_rsh_00014520@ha
		opword 0xEC211028
		lfs f2, zero_rsh_00014490@l(r5)
		opword 0x38A0003D
		opword 0x38C00000
		opword 0xEC610024
		lfs f1, float_1p5_rsh_0001451c@l(r4)
		lfs f0, float_0p8_rsh_00014520@l(r3)
		opword 0x7FC3F378
		opword 0x7FE4FB78
		opword 0xEC9B08BA
		opword 0xEC0300BA
		opword 0xC0210044
		opword 0xC0410048
		opword 0xEC850132
		opword 0xC061004C
		opword 0xECA50032
		bl moamoa_jump
		opword 0xA01F0000
		opword 0x60000200
		opword 0xB01F0000
		opword 0x801E0000
		opword 0x60000004
		opword 0x901E0000
		opword 0x48001708
		lis r3, rsh_06_str_000047B4@ha
		addi r3, r3, rsh_06_str_000047B4@l
		bl npcNameToPtr
		opword 0x80630104
		bl animPoseGetAnimPosePtr
		opword 0xA8FF0048
		opword 0x3CA04330
		lis r4, wp@ha
		opword 0x8063015C
		addi r6, r4, wp@l
		opword 0x90A100A8
		opword 0x54E4083C
		opword 0x81060000
		opword 0x38040570
		opword 0xA89F004A
		opword 0x7C0802AE
		lis r6, double_to_int_rsh_00014488@ha
		opword 0x6C848000
		opword 0x54E7103A
		opword 0x908100AC
		opword 0x6C008000
		lfd f2, double_to_int_rsh_00014488@l(r6)
		opword 0x7D083A14
		opword 0xC80100A8
		opword 0x38810038
		opword 0x900100A4
		opword 0xEC201028
		opword 0xA8E80672
		opword 0x90A100A0
		opword 0xA8080670
		opword 0x1CC7000C
		opword 0xC80100A0
		opword 0x80630000
		opword 0xEC001028
		opword 0x1C00000C
		opword 0x7E233214
		opword 0xEF610024
		opword 0x7C630214
		opword 0xFC20D890
		bl PSVECScale
		lis r4, float_1_rsh_00014470@ha
		opword 0x7E238B78
		addi r5, r4, float_1_rsh_00014470@l
		opword 0x38810008
		opword 0xC0050000
		opword 0xEC20D828
		bl PSVECScale
		opword 0x38610038
		opword 0x38810008
		opword 0x7C651B78
		bl PSVECAdd
		opword 0x38610038
		opword 0x389F0030
		opword 0x7C651B78
		bl PSVECAdd
		opword 0xC0010038
		opword 0x807E000C
		opword 0xD003000C
		opword 0xC001003C
		opword 0x807E000C
		opword 0xD003001C
		opword 0xC0010040
		opword 0x807E000C
		opword 0xD003002C
		opword 0x48001604
		opword 0xA87F0004
		opword 0x3863FFFF
		opword 0x7C600735
		opword 0xB07F0004
		opword 0x408015F0
		opword 0x38000000
		opword 0xB01F0004
		opword 0xA87F0002
		opword 0x38030001
		opword 0xB01F0002
		opword 0x480015D8
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00014488@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC0250000
		lis r4, float_200_rsh_000144d8@ha
		opword 0xC80100A8
		lis r3, zero_rsh_00014490@ha
		addi r5, r4, float_200_rsh_000144d8@l
		opword 0xEC601028
		addi r4, r3, zero_rsh_00014490@l
		opword 0xC0450000
		lis r3, float_300_rsh_00014524@ha
		opword 0xC0040000
		opword 0xEC630824
		lfs f1, float_300_rsh_00014524@l(r3)
		opword 0xEC0300BA
		opword 0xD01F001C
		opword 0xC01F001C
		opword 0xEC010032
		opword 0xEF601024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_rsh_00014488@ha
		opword 0x906100A4
		addi r5, r4, double_to_int_rsh_00014488@l
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A0
		addi r4, r3, float_32767_rsh_000144ec@l
		opword 0xC8250000
		lis r3, zero_rsh_00014490@ha
		opword 0xC80100A0
		opword 0x38000000
		opword 0xC0440000
		opword 0xEC600828
		lfs f1, zero_rsh_00014490@l(r3)
		opword 0xEC1B0828
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
		lis r3, float_1_rsh_00014470@ha
		lfs f1, float_1_rsh_00014470@l(r3)
		opword 0x48000034
		opword 0x20600320
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_rsh_00014488@ha
		opword 0x906100AC
		lis r3, float_600_rsh_00014528@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		opword 0x900100A8
		lfs f0, float_600_rsh_00014528@l(r3)
		opword 0xC82100A8
		opword 0xEC211028
		opword 0xEC210024
		lis r3, zero_rsh_00014490@ha
		opword 0xFFA00890
		lfs f0, zero_rsh_00014490@l(r3)
		opword 0xFC010040
		opword 0x40800014
		opword 0xA01F0000
		opword 0xFFA00090
		opword 0x60000200
		opword 0xB01F0000
		opword 0x38C00003
		lis r3, gp@ha
		opword 0x7CBD33D6
		lwz r4, gp@l(r3)
		opword 0x3C004330
		opword 0x900100A8
		lis r3, double_to_int_mask_rsh_00014480@ha
		opword 0x8004001C
		opword 0x7C8531D6
		opword 0x7C1D0214
		opword 0x900100AC
		lis r5, wp@ha
		lfd f1, double_to_int_mask_rsh_00014480@l(r3)
		lis r3, float_0p25_rsh_0001452c@ha
		opword 0xC80100A8
		opword 0x7C04E850
		opword 0x1C00000C
		opword 0xEC200828
		lfs f0, float_0p25_rsh_0001452c@l(r3)
		lwz r3, wp@l(r5)
		opword 0x7C630214
		opword 0xEC210032
		opword 0xC3430014
		opword 0xC3630018
		opword 0xC383001C
		bl sin
		lis r3, gp@ha
		opword 0x3C004330
		addi r4, r3, gp@l
		opword 0xFC400818
		opword 0x80A40000
		lis r3, double_to_int_mask_rsh_00014480@ha
		opword 0xC03F0020
		addi r4, r3, double_to_int_mask_rsh_00014480@l
		opword 0x80A5001C
		opword 0xEC6100B2
		opword 0x900100A0
		opword 0x7C1D2A14
		opword 0xC01F001C
		opword 0x900100A4
		lis r3, float_0p25_rsh_0001452c@ha
		opword 0xC8440000
		opword 0xEF60DF7A
		opword 0xC82100A0
		opword 0xEF5DD0FA
		lfs f0, float_0p25_rsh_0001452c@l(r3)
		opword 0xEC211028
		opword 0xEC210032
		bl cos
		opword 0x809E000C
		lis r3, float_15_rsh_00014474@ha
		opword 0xC01F0020
		opword 0xFC800818
		opword 0xC064000C
		opword 0xFC200050
		lfs f2, float_15_rsh_00014474@l(r3)
		opword 0xEC1A1828
		opword 0xEC210132
		opword 0xEC001024
		opword 0xEC03002A
		opword 0xEF9DE07A
		opword 0xD004000C
		opword 0x807E000C
		opword 0xC023001C
		opword 0xEC1B0828
		opword 0xEC001024
		opword 0xEC01002A
		opword 0xD003001C
		opword 0x807E000C
		opword 0xC023002C
		opword 0xEC1C0828
		opword 0xEC001024
		opword 0xEC01002A
		opword 0xD003002C
		opword 0xA87F0004
		opword 0x38030001
		opword 0xB01F0004
		opword 0x4800136C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00014488@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_000144ec@l
		lis r4, float_90_rsh_00014534@ha
		opword 0xC0050000
		opword 0xC82100A8
		lis r3, float_neg45_rsh_00014530@ha
		addi r9, r4, float_90_rsh_00014534@l
		lis r4, float_6p2832_rsh_0001449c@ha
		opword 0xEC211028
		addi r5, r3, float_neg45_rsh_00014530@l
		lis r3, wp@ha
		addi r8, r4, float_6p2832_rsh_0001449c@l
		addi r6, r3, wp@l
		lis r4, float_1_rsh_00014470@ha
		opword 0xEC410024
		opword 0x81460000
		opword 0xC0050000
		lis r3, float_360_rsh_000144a0@ha
		opword 0xC0290000
		addi r7, r3, float_360_rsh_000144a0@l
		opword 0xEC22007A
		opword 0xC06A0550
		opword 0xC0480000
		lis r6, float_0p00761_rsh_000144a4@ha
		lis r5, float_0p16605_rsh_000144a8@ha
		opword 0xC0070000
		opword 0xEC63082A
		lis r3, float_3p1416_rsh_000144ac@ha
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		opword 0xC36A0554
		opword 0xEC4200F2
		lfs f5, float_0p00761_rsh_000144a4@l(r6)
		lfs f4, float_0p16605_rsh_000144a8@l(r5)
		lfs f3, float_1_rsh_00014470@l(r4)
		opword 0xECC20024
		opword 0xFC060840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC060040
		opword 0x40800020
		opword 0xEC260828
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC060028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x80DE000C
		lis r3, float_3p1416_rsh_000144ac@ha
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r4, float_15_rsh_00014474@ha
		lfs f2, float_15_rsh_00014474@l(r4)
		lis r5, float_0p03705_rsh_000144b8@ha
		opword 0xC006000C
		opword 0xFC060840
		lis r4, float_0p4967_rsh_000144bc@ha
		lis r3, float_1_rsh_00014470@ha
		opword 0xEFA2017A
		opword 0xC3C6001C
		lfs f4, float_0p03705_rsh_000144b8@l(r5)
		lfs f3, float_0p4967_rsh_000144bc@l(r4)
		lfs f2, float_1_rsh_00014470@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC060040
		opword 0x4080001C
		opword 0xEC060828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC060028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_15_rsh_00014474@ha
		opword 0xC006002C
		lfs f1, float_15_rsh_00014474@l(r3)
		opword 0xEF81013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00014488@ha
		lfd f1, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC0450000
		lis r4, zero_rsh_00014490@ha
		opword 0xC80100A8
		lis r3, float_1_rsh_00014470@ha
		opword 0xEC600828
		lfs f1, zero_rsh_00014490@l(r4)
		lfs f0, float_1_rsh_00014470@l(r3)
		opword 0xEC431024
		opword 0xEF42007A
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100A4
		lis r4, double_to_int_rsh_00014488@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A0
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC0050000
		lis r4, zero_rsh_00014490@ha
		opword 0xC82100A0
		lis r3, float_0p4_rsh_00014518@ha
		addi r5, r4, zero_rsh_00014490@l
		opword 0xFC80D090
		opword 0xEC611028
		addi r4, r3, float_0p4_rsh_00014518@l
		opword 0xC0240000
		lis r3, float_100_rsh_000144f8@ha
		opword 0xC0450000
		opword 0xEC630024
		lfs f0, float_100_rsh_000144f8@l(r3)
		opword 0x7FC3F378
		opword 0x7FE4FB78
		opword 0xECA308BA
		opword 0xFC20E890
		opword 0xFC40F090
		opword 0xFC60E090
		opword 0xFC1B0040
		opword 0x4080000C
		opword 0xA8BF0002
		opword 0x48000008
		opword 0x38A00000
		opword 0x38C00000
		bl moamoa_jump
		opword 0x48001074
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00014488@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_000144ec@l
		lis r4, float_90_rsh_00014534@ha
		lis r3, float_neg45_rsh_00014530@ha
		opword 0xC82100A8
		addi r7, r4, float_90_rsh_00014534@l
		opword 0xC0050000
		addi r6, r3, float_neg45_rsh_00014530@l
		opword 0xEC211028
		lis r3, wp@ha
		addi r5, r3, wp@l
		lis r4, float_180_rsh_00014538@ha
		opword 0x81250000
		addi r8, r4, float_180_rsh_00014538@l
		opword 0xEC410024
		opword 0xC0060000
		opword 0xC0270000
		lis r3, float_6p2832_rsh_0001449c@ha
		addi r5, r3, float_6p2832_rsh_0001449c@l
		lis r4, float_360_rsh_000144a0@ha
		opword 0xEC02007A
		opword 0xC0890550
		opword 0xC0680000
		addi r7, r4, float_360_rsh_000144a0@l
		opword 0xC0450000
		lis r3, float_3p1416_rsh_000144ac@ha
		opword 0xEC84002A
		lis r6, float_0p00761_rsh_000144a4@ha
		opword 0xC0070000
		lis r5, float_0p16605_rsh_000144a8@ha
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r4, float_1_rsh_00014470@ha
		opword 0xEC84182A
		opword 0xC3690554
		lfs f5, float_0p00761_rsh_000144a4@l(r6)
		lfs f3, float_1_rsh_00014470@l(r4)
		opword 0xEC420132
		lfs f4, float_0p16605_rsh_000144a8@l(r5)
		opword 0xEC420024
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC020040
		opword 0x40800020
		opword 0xEC420828
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA500B2
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC020028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC410028
		opword 0xEC0200B2
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA500B2
		opword 0xFCA02850
		opword 0x809E000C
		lis r3, float_30_rsh_000144dc@ha
		lfs f1, float_30_rsh_000144dc@l(r3)
		opword 0xC004000C
		opword 0xC3C4001C
		opword 0xEFA1017A
		opword 0xC384002C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00014488@ha
		lfd f1, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC0450000
		lis r4, zero_rsh_00014490@ha
		opword 0xC80100A8
		lis r3, float_1_rsh_00014470@ha
		lis r5, float_2_rsh_00014514@ha
		opword 0xEC600828
		lfs f1, zero_rsh_00014490@l(r4)
		lfs f0, float_1_rsh_00014470@l(r3)
		opword 0xEC631024
		lfs f2, float_2_rsh_00014514@l(r5)
		opword 0xEC03007A
		opword 0xEF420032
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100A4
		lis r4, double_to_int_rsh_00014488@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A0
		addi r5, r3, float_32767_rsh_000144ec@l
		lis r6, float_2_rsh_00014514@ha
		opword 0xC0050000
		opword 0xC82100A0
		lis r4, zero_rsh_00014490@ha
		lis r3, float_0p4_rsh_00014518@ha
		lfs f4, float_2_rsh_00014514@l(r6)
		opword 0xEC211028
		addi r5, r4, zero_rsh_00014490@l
		addi r4, r3, float_0p4_rsh_00014518@l
		opword 0xC0450000
		lis r3, float_100_rsh_000144f8@ha
		opword 0xEC610024
		opword 0xC0240000
		opword 0x7FE4FB78
		lfs f0, float_100_rsh_000144f8@l(r3)
		opword 0x7FC3F378
		opword 0xEC6308BA
		opword 0xFC20E890
		opword 0xFC40F090
		opword 0xECA400F2
		opword 0xFC60E090
		opword 0xFC80D090
		opword 0xFC1B0040
		opword 0x4080000C
		opword 0xA8BF0002
		opword 0x48000008
		opword 0x38A00000
		opword 0x38C00000
		bl moamoa_jump
		opword 0x48000E10
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
		lis r3, float_6p2832_rsh_0001449c@ha
		lis r6, float_0p00761_rsh_000144a4@ha
		addi r5, r3, float_6p2832_rsh_0001449c@l
		lis r4, float_360_rsh_000144a0@ha
		opword 0xC0050000
		lis r5, float_0p16605_rsh_000144a8@ha
		lis r3, float_3p1416_rsh_000144ac@ha
		lfs f4, float_0p00761_rsh_000144a4@l(r6)
		opword 0xEC400072
		lfs f0, float_360_rsh_000144a0@l(r4)
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r4, float_1_rsh_00014470@ha
		lfs f3, float_0p16605_rsh_000144a8@l(r5)
		opword 0xECA20024
		lfs f2, float_1_rsh_00014470@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x80FE000C
		lis r3, float_3p1416_rsh_000144ac@ha
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r5, float_0p4967_rsh_000144bc@ha
		opword 0xC05F001C
		lis r6, float_0p03705_rsh_000144b8@ha
		opword 0xC007000C
		opword 0xFC050840
		lis r4, float_1_rsh_00014470@ha
		lfs f3, float_0p4967_rsh_000144bc@l(r5)
		opword 0xEC02013A
		lfs f4, float_0p03705_rsh_000144b8@l(r6)
		lfs f2, float_1_rsh_00014470@l(r4)
		opword 0xD007000C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		opword 0x40800C08
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
		opword 0x48000BB4
		opword 0xA87F0004
		opword 0x38630001
		opword 0x7C600734
		opword 0xB07F0004
		opword 0x2C000004
		opword 0x40810B9C
		opword 0xA81F0024
		opword 0xB01F0002
		opword 0x48000B90
		opword 0xA01F0000
		opword 0x540007FF
		opword 0x40820010
		opword 0xC35C008C
		opword 0xC37C0094
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
		opword 0xC3430014
		opword 0xC363001C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00014488@ha
		lis r3, float_32767_rsh_000144ec@ha
		lfd f4, double_to_int_rsh_00014488@l(r4)
		opword 0x900100A8
		opword 0xFC40D890
		lfs f0, float_32767_rsh_000144ec@l(r3)
		opword 0xFC20D090
		opword 0xC86100A8
		opword 0x80BE000C
		opword 0xECA32028
		opword 0xC065000C
		opword 0xC085002C
		opword 0xEF650024
		bl angleABf
		lis r3, float_90_rsh_00014534@ha
		lis r4, float_neg45_rsh_00014530@ha
		addi r5, r3, float_90_rsh_00014534@l
		lfs f0, float_neg45_rsh_00014530@l(r4)
		opword 0xC0450000
		lis r3, float_6p2832_rsh_0001449c@ha
		addi r8, r3, float_6p2832_rsh_0001449c@l
		lis r4, float_360_rsh_000144a0@ha
		opword 0xEC1B00BA
		addi r7, r4, float_360_rsh_000144a0@l
		lis r6, float_0p00761_rsh_000144a4@ha
		lis r5, float_0p16605_rsh_000144a8@ha
		lis r3, float_3p1416_rsh_000144ac@ha
		lis r4, float_1_rsh_00014470@ha
		opword 0xEC41002A
		opword 0xC0280000
		opword 0xC0070000
		lfs f4, float_0p00761_rsh_000144a4@l(r6)
		opword 0xEC4100B2
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lfs f3, float_0p16605_rsh_000144a8@l(r5)
		opword 0xECA20024
		lfs f2, float_1_rsh_00014470@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x80DE000C
		lis r3, float_3p1416_rsh_000144ac@ha
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r4, float_15_rsh_00014474@ha
		lfs f2, float_15_rsh_00014474@l(r4)
		lis r4, float_0p4967_rsh_000144bc@ha
		opword 0xC006000C
		opword 0xFC050840
		lis r5, float_0p03705_rsh_000144b8@ha
		lis r3, float_1_rsh_00014470@ha
		opword 0xEFA2013A
		opword 0xC3C6001C
		lfs f4, float_0p03705_rsh_000144b8@l(r5)
		lfs f3, float_0p4967_rsh_000144bc@l(r4)
		lfs f2, float_1_rsh_00014470@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC050028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_15_rsh_00014474@ha
		opword 0xC006002C
		lfs f1, float_15_rsh_00014474@l(r3)
		opword 0xEF41013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00014488@ha
		lis r3, float_32767_rsh_000144ec@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		opword 0x900100A8
		lfs f0, float_32767_rsh_000144ec@l(r3)
		opword 0xC82100A8
		opword 0xEC211028
		opword 0xEF610024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100A4
		lis r4, double_to_int_rsh_00014488@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A0
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC0050000
		lis r4, zero_rsh_00014490@ha
		opword 0xC82100A0
		lis r3, float_1_rsh_00014470@ha
		lfs f5, zero_rsh_00014490@l(r4)
		opword 0x7FE4FB78
		opword 0xEC611028
		opword 0xA8BF0002
		opword 0xFC20E890
		opword 0x38C00001
		opword 0xFC40F090
		opword 0x38A50001
		opword 0xECC30024
		lfs f0, float_1_rsh_00014470@l(r3)
		opword 0x7FC3F378
		opword 0xEC9B017A
		opword 0xFC60D090
		opword 0xECA6017A
		bl moamoa_jump
		opword 0x4800088C
		opword 0xA87F0004
		opword 0x38630001
		opword 0x7C600734
		opword 0xB07F0004
		opword 0x2C00001E
		opword 0x40800040
		opword 0x809E000C
		lis r3, float_0p9_rsh_0001453c@ha
		lfs f1, float_0p9_rsh_0001453c@l(r3)
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
		opword 0x48000838
		opword 0x38000031
		opword 0xB01F0002
		opword 0x4800082C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00014488@ha
		lis r3, float_32767_rsh_000144ec@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		opword 0x900100A8
		lfs f0, float_32767_rsh_000144ec@l(r3)
		opword 0xC82100A8
		opword 0xEC211028
		opword 0xEF610024
		bl rand
		lis r5, float_90_rsh_00014534@ha
		lis r4, float_135_rsh_00014540@ha
		lfs f0, float_135_rsh_00014540@l(r4)
		opword 0x6C668000
		lfs f1, float_90_rsh_00014534@l(r5)
		opword 0x3C004330
		lis r3, float_6p2832_rsh_0001449c@ha
		lis r4, double_to_int_rsh_00014488@ha
		addi r5, r3, float_6p2832_rsh_0001449c@l
		opword 0x90C100A4
		opword 0xEC1B007A
		addi r6, r4, double_to_int_rsh_00014488@l
		opword 0x900100A0
		lis r3, float_360_rsh_000144a0@ha
		opword 0xC0250000
		addi r4, r3, float_360_rsh_000144a0@l
		lis r3, float_32767_rsh_000144ec@ha
		opword 0xEC210032
		opword 0xC0040000
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC8660000
		lis r4, float_300_rsh_00014524@ha
		opword 0xC84100A0
		opword 0xECE10024
		addi r6, r4, float_300_rsh_00014524@l
		lis r3, float_3p1416_rsh_000144ac@ha
		lis r4, float_0p16605_rsh_000144a8@ha
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r3, float_1_rsh_00014470@ha
		opword 0xEC621828
		opword 0xC0450000
		lis r5, float_200_rsh_000144d8@ha
		opword 0xC0060000
		addi r7, r5, float_200_rsh_000144d8@l
		opword 0xFC070840
		opword 0xEC631024
		opword 0xC0470000
		lis r5, float_0p00761_rsh_000144a4@ha
		lfs f4, float_0p16605_rsh_000144a8@l(r4)
		lfs f5, float_0p00761_rsh_000144a4@l(r5)
		opword 0xECC300BA
		lfs f2, float_1_rsh_00014470@l(r3)
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC070040
		opword 0x40800020
		opword 0xEC270828
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5103A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC070028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5103A
		opword 0xECA50072
		opword 0xFCA02850
		lis r3, float_3p1416_rsh_000144ac@ha
		opword 0x80DE000C
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r5, float_0p03705_rsh_000144b8@ha
		opword 0xC006000C
		lis r4, float_0p4967_rsh_000144bc@ha
		opword 0xFC070840
		lis r3, float_1_rsh_00014470@ha
		opword 0xEFA6017A
		lfs f4, float_0p03705_rsh_000144b8@l(r5)
		lfs f3, float_0p4967_rsh_000144bc@l(r4)
		lfs f2, float_1_rsh_00014470@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC070040
		opword 0x4080001C
		opword 0xEC070828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC070028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xC006002C
		opword 0xEFC6013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00014488@ha
		lfd f1, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC0450000
		lis r4, float_1_rsh_00014470@ha
		opword 0xC80100A8
		lis r3, float_5_rsh_00014500@ha
		opword 0xEC600828
		lfs f1, float_1_rsh_00014470@l(r4)
		lfs f0, float_5_rsh_00014500@l(r3)
		opword 0xEC431024
		opword 0xEF42007A
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100A4
		lis r4, double_to_int_rsh_00014488@ha
		lfd f1, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A0
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC0450000
		lis r4, float_0p1_rsh_00014548@ha
		opword 0xC80100A0
		lis r3, float_0p2_rsh_00014544@ha
		opword 0x2C1A0000
		opword 0xEC600828
		lfs f1, float_0p1_rsh_00014548@l(r4)
		lfs f0, float_0p2_rsh_00014544@l(r3)
		opword 0xEC431024
		opword 0xEF62007A
		opword 0x40820050
		lis r3, vec3_rsh_00013da0@ha
		opword 0x38810020
		addi r7, r3, vec3_rsh_00013da0@l
		opword 0x386006C3
		opword 0x80C70000
		opword 0x80A70004
		opword 0x80070008
		opword 0x90C10020
		opword 0x90A10024
		opword 0x90010028
		opword 0x80BE000C
		opword 0xC005000C
		opword 0xD0010020
		opword 0xC005001C
		opword 0xD0010024
		opword 0xC005002C
		opword 0xD0010028
		bl psndSFXOn_3D
		opword 0x3B400001
		lis r3, float_neg100_rsh_0001454c@ha
		opword 0xFC20E890
		lfs f2, float_neg100_rsh_0001454c@l(r3)
		opword 0xFC60F090
		opword 0xFC80D090
		opword 0x7FC3F378
		opword 0xFCA0D890
		opword 0x7FE4FB78
		opword 0x38A00031
		opword 0x38C00000
		bl moamoa_jump
		opword 0x480004DC
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
		opword 0x48000458
		opword 0x38000031
		opword 0xB01F0002
		opword 0x4800044C
		opword 0x807E000C
		bl PSMTXIdentity
		lis r3, wp@ha
		opword 0x3AA002BC
		addi r22, r3, wp@l
		bl rand
		opword 0x7C03ABD6
		opword 0x80960000
		opword 0x80840008
		opword 0x7C00A9D6
		opword 0x7E401850
		opword 0x1C120050
		opword 0x7C840214
		opword 0xA8640002
		opword 0x7C600735
		opword 0x4182000C
		opword 0x2C030003
		opword 0x4082FFD0
		opword 0xA0040000
		opword 0x54000673
		opword 0x4082FFC4
		bl extGetPosePtr
		opword 0x56402834
		lis r4, float_215_rsh_00014504@ha
		opword 0x7CE30214
		opword 0x80BE000C
		opword 0x80C7000C
		opword 0x38000000
		lfs f0, float_215_rsh_00014504@l(r4)
		opword 0xC026000C
		opword 0xD025000C
		opword 0x807E000C
		opword 0xD003001C
		opword 0x8087000C
		opword 0x807E000C
		opword 0xC004002C
		opword 0xD003002C
		opword 0xB01F0000
		opword 0xB01F0002
		opword 0xB01F0004
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
		opword 0x906100AC
		lis r4, double_to_int_rsh_00014488@ha
		lis r3, float_32767_rsh_000144ec@ha
		lfd f2, double_to_int_rsh_00014488@l(r4)
		opword 0x900100A8
		lfs f0, float_32767_rsh_000144ec@l(r3)
		opword 0xC82100A8
		opword 0xEC211028
		opword 0xEF610024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100A4
		lis r4, double_to_int_rsh_00014488@ha
		lfd f1, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A0
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC0450000
		lis r4, float_1_rsh_00014470@ha
		opword 0xC80100A0
		lis r3, float_2_rsh_00014514@ha
		opword 0x7FA00E70
		opword 0xEC600828
		lfs f0, float_2_rsh_00014514@l(r3)
		lfs f1, float_1_rsh_00014470@l(r4)
		opword 0x7C600194
		opword 0xEC431024
		opword 0xEFC2007A
		bl irand
		lis r5, float_90_rsh_00014534@ha
		lis r4, float_225_rsh_00014550@ha
		lfs f1, float_90_rsh_00014534@l(r5)
		lis r7, float_0p00761_rsh_000144a4@ha
		lfs f0, float_225_rsh_00014550@l(r4)
		lis r6, float_6p2832_rsh_0001449c@ha
		lis r5, float_360_rsh_000144a0@ha
		lis r4, float_3p1416_rsh_000144ac@ha
		opword 0xEC1B007A
		lfs f1, float_6p2832_rsh_0001449c@l(r6)
		lis r6, float_0p16605_rsh_000144a8@ha
		opword 0xB07F0004
		lfs f4, float_0p00761_rsh_000144a4@l(r7)
		opword 0xEC410032
		lfs f0, float_360_rsh_000144a0@l(r5)
		lis r5, float_1_rsh_00014470@ha
		lfs f1, float_3p1416_rsh_000144ac@l(r4)
		opword 0xEFA20024
		lfs f3, float_0p16605_rsh_000144a8@l(r6)
		lfs f2, float_1_rsh_00014470@l(r5)
		opword 0xFC1D0840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xFC1D0840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC1D0772
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840772
		opword 0x48000070
		opword 0xEC1D0828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0x48000054
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC1D0040
		opword 0x40800020
		opword 0xEC3D0828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC1D0028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0xEC1E0132
		opword 0xD01F0008
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_rsh_00014488@ha
		opword 0x906100AC
		addi r5, r4, double_to_int_rsh_00014488@l
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A8
		addi r4, r3, float_32767_rsh_000144ec@l
		opword 0xC8450000
		lis r3, float_1_rsh_00014470@ha
		opword 0xC82100A8
		addi r5, r3, float_1_rsh_00014470@l
		opword 0xC0040000
		lis r4, float_0p03705_rsh_000144b8@ha
		opword 0xEC611028
		lis r3, float_3p1416_rsh_000144ac@ha
		lfs f1, float_3p1416_rsh_000144ac@l(r3)
		lis r3, float_0p4967_rsh_000144bc@ha
		opword 0xC0450000
		opword 0xEC030024
		lfs f4, float_0p03705_rsh_000144b8@l(r4)
		lfs f3, float_0p4967_rsh_000144bc@l(r3)
		opword 0xEC0010BA
		opword 0xFC1D0840
		opword 0xD01F000C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_rsh_000144b0@ha
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xFC1D0840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC1D0772
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x48000064
		opword 0xEC1D0828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000048
		lis r3, float_4p7124_rsh_000144b4@ha
		lfs f0, float_4p7124_rsh_000144b4@l(r3)
		opword 0xFC1D0040
		opword 0x4080001C
		opword 0xEC1D0828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_rsh_000144b0@ha
		opword 0xEC1D0028
		lfs f1, float_1p5708_rsh_000144b0@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC002050
		opword 0xEC1E0032
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
		lis r3, float_1p1_rsh_00014554@ha
		lis r4, float_1p02_rsh_00014558@ha
		addi r6, r3, float_1p1_rsh_00014554@l
		lis r3, float_0p20944_rsh_0001455c@ha
		opword 0xC03F0008
		addi r5, r4, float_1p02_rsh_00014558@l
		opword 0xC0660000
		addi r4, r3, float_0p20944_rsh_0001455c@l
		opword 0xC0050000
		opword 0x3861005C
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
		opword 0x3881005C
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x801E0000
		lis r3, float_neg1000_rsh_00014560@ha
		lfs f0, float_neg1000_rsh_00014560@l(r3)
		opword 0x540007FA
		opword 0x901E0000
		opword 0x807E000C
		opword 0xC023000C
		opword 0xFC010040
		opword 0x4080000C
		opword 0x3800003E
		opword 0xB01F0002
		opword 0xA01F0000
		opword 0x70000588
		opword 0x40820074
		opword 0x80BE000C
		lis r3, float_250_rsh_00014564@ha
		opword 0xC0770018
		opword 0xC045000C
		lfs f1, float_250_rsh_00014564@l(r3)
		opword 0xEC031028
		opword 0xFC000840
		opword 0x40810028
		lis r4, float_450_rsh_00014568@ha
		lis r3, float_neg50_rsh_0001456c@ha
		lfs f1, float_450_rsh_00014568@l(r4)
		lfs f0, float_neg50_rsh_0001456c@l(r3)
		opword 0xEC21102A
		opword 0xFC010040
		opword 0x40800038
		opword 0xD025000C
		opword 0x48000030
		opword 0xEC021828
		opword 0xFC000840
		opword 0x40810024
		lis r4, float_450_rsh_00014568@ha
		lis r3, float_neg1870_rsh_00014570@ha
		lfs f1, float_450_rsh_00014568@l(r4)
		lfs f0, float_neg1870_rsh_00014570@l(r3)
		opword 0xEC220828
		opword 0xFC010040
		opword 0x40810008
		opword 0xD025000C
		opword 0xA01F0000
		opword 0x70000588
		opword 0x408201E0
		opword 0x809E000C
		lis r3, float_100_rsh_000144f8@ha
		lfs f0, float_100_rsh_000144f8@l(r3)
		opword 0xC024000C
		opword 0xFC010040
		opword 0x40810060
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00014488@ha
		lfd f1, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC0450000
		lis r4, float_5_rsh_00014500@ha
		opword 0xC80100A8
		lis r3, zero_rsh_00014490@ha
		lis r5, float_100_rsh_000144f8@ha
		opword 0xEC600828
		lfs f0, zero_rsh_00014490@l(r3)
		lfs f1, float_5_rsh_00014500@l(r4)
		opword 0x807E000C
		opword 0xEC631024
		lfs f2, float_100_rsh_000144f8@l(r5)
		opword 0xEC03007A
		opword 0xEC02002A
		opword 0xD003000C
		opword 0x809E000C
		lis r3, float_neg1870_rsh_00014570@ha
		lfs f0, float_neg1870_rsh_00014570@l(r3)
		opword 0xC024000C
		opword 0xFC010040
		opword 0x40800060
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00014488@ha
		lfd f1, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC0450000
		lis r4, float_5_rsh_00014500@ha
		opword 0xC80100A8
		lis r3, zero_rsh_00014490@ha
		lis r5, float_neg1870_rsh_00014570@ha
		opword 0xEC600828
		lfs f0, zero_rsh_00014490@l(r3)
		lfs f1, float_5_rsh_00014500@l(r4)
		opword 0x807E000C
		opword 0xEC631024
		lfs f2, float_neg1870_rsh_00014570@l(r5)
		opword 0xEC03007A
		opword 0xEC02002A
		opword 0xD003000C
		opword 0xA01F0000
		opword 0x54000673
		opword 0x408200EC
		opword 0x809E000C
		lis r3, float_45_rsh_00014574@ha
		lfs f0, float_45_rsh_00014574@l(r3)
		opword 0xC024002C
		opword 0xFC010040
		opword 0x40810060
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00014488@ha
		lfd f1, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC0450000
		lis r4, float_5_rsh_00014500@ha
		opword 0xC80100A8
		lis r3, zero_rsh_00014490@ha
		lis r5, float_45_rsh_00014574@ha
		opword 0xEC600828
		lfs f0, zero_rsh_00014490@l(r3)
		lfs f1, float_5_rsh_00014500@l(r4)
		opword 0x807E000C
		opword 0xEC631024
		lfs f2, float_45_rsh_00014574@l(r5)
		opword 0xEC03007A
		opword 0xEC02002A
		opword 0xD003002C
		opword 0x809E000C
		lis r3, float_neg45_rsh_00014530@ha
		lfs f0, float_neg45_rsh_00014530@l(r3)
		opword 0xC024002C
		opword 0xFC010040
		opword 0x40800060
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lis r4, double_to_int_rsh_00014488@ha
		lfd f1, double_to_int_rsh_00014488@l(r4)
		lis r3, float_32767_rsh_000144ec@ha
		opword 0x900100A8
		addi r5, r3, float_32767_rsh_000144ec@l
		opword 0xC0450000
		lis r4, float_5_rsh_00014500@ha
		opword 0xC80100A8
		lis r3, zero_rsh_00014490@ha
		lis r5, float_neg45_rsh_00014530@ha
		opword 0xEC600828
		lfs f0, zero_rsh_00014490@l(r3)
		lfs f1, float_5_rsh_00014500@l(r4)
		opword 0x807E000C
		opword 0xEC631024
		lfs f2, float_neg45_rsh_00014530@l(r5)
		opword 0xEC03007A
		opword 0xEC02002A
		opword 0xD003002C
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
		opword 0x4180D584
		bl extGetPosePtr
		lis r4, wp@ha
		lis r7, float_60_rsh_00014578@ha
		addi r25, r4, wp@l
		lis r6, float_1000_rsh_0001457c@ha
		opword 0x81390000
		lis r5, float_1_rsh_00014470@ha
		lis r4, double_to_int_rsh_00014488@ha
		lis r8, gp@ha
		opword 0x82490008
		opword 0x7C731B78
		lfs f30, float_60_rsh_00014578@l(r7)
		addi r24, r8, gp@l
		lfs f29, float_1000_rsh_0001457c@l(r6)
		opword 0x3A800000
		lfs f28, float_1_rsh_00014470@l(r5)
		opword 0x3EE08000
		lfd f27, double_to_int_rsh_00014488@l(r4)
		opword 0x3F404330
		opword 0x480000BC
		opword 0x807700F8
		opword 0x380003E8
		opword 0x80980000
		opword 0x38A00000
		opword 0x5463F0BE
		opword 0xA912003C
		opword 0x7CC30396
		opword 0x82C4003C
		opword 0x80120044
		opword 0x82A40038
		opword 0x7C80B010
		opword 0x80120040
		opword 0x1D080028
		opword 0x7C60A910
		opword 0x3A280050
		opword 0x7E278A14
		bl __div2u
		bl __cvt_ull_flt
		opword 0xEC3E0072
		opword 0xC011001C
		opword 0xEC21E824
		opword 0xEC210024
		opword 0xFC01E040
		opword 0x4C411382
		opword 0x40820014
		opword 0x92D20044
		lis r3, zero_rsh_00014490@ha
		lfs f1, zero_rsh_00014490@l(r3)
		opword 0x92B20040
		opword 0x80710024
		opword 0x3A940001
		opword 0x934100A8
		opword 0x3A520050
		opword 0x3803FFFF
		opword 0x80710020
		opword 0x6C008000
		opword 0x900100AC
		opword 0xC80100A8
		opword 0xEC00D828
		opword 0xEC000072
		opword 0xFC00001E
		opword 0xD80100A0
		opword 0x800100A4
		opword 0x7C030214
		opword 0x90130010
		opword 0x3A730020
		opword 0x80F90000
		opword 0x80070004
		opword 0x7C140000
		opword 0x4180FF3C
		lis r4, zero_rsh_00014490@ha
		lis r3, wp@ha
		lfs f0, zero_rsh_00014490@l(r4)
		addi r3, r3, wp@l
		opword 0xD01C0174
		opword 0xD01C0178
		opword 0xD01C017C
		opword 0x80630000
		opword 0xA0030000
		opword 0x540006F9
		opword 0x40820018
		lis r3, float_20_rsh_00014580@ha
		opword 0xFC20F850
		lfs f0, float_20_rsh_00014580@l(r3)
		opword 0xEC010024
		opword 0xD01C0174
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
static void ext_moamoa_dispent(void) {
#ifdef NONMATCHING
    if (wp->flags & 1) {
        dispEntry(CAMERA_3D, zero_rsh_00014490[0], 1, ext_disp, NULL);
        dispEntry(CAMERA_3D, zero_rsh_00014490[0], 2, ext_shadow_disp, NULL);
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
		lis r3, zero_rsh_00014490@ha
		lis r4, ext_disp@ha
		addi r6, r3, zero_rsh_00014490@l
		opword 0xC0260000
		addi r5, r4, ext_disp@l
		opword 0x38600004
		opword 0x38800001
		opword 0x38C00000
		bl dispEntry
		lis r3, zero_rsh_00014490@ha
		lis r4, ext_shadow_disp@ha
		addi r6, r3, zero_rsh_00014490@l
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
		lis r3, float_neg5000_rsh_00014494@ha
		lis r4, ext_disp@ha
		addi r6, r3, float_neg5000_rsh_00014494@l
		opword 0xC0260000
		addi r5, r4, ext_disp@l
		opword 0x38600001
		opword 0x38800001
		opword 0x38C00000
		bl dispEntry
		lis r3, float_neg5000_rsh_00014494@ha
		lis r4, ext_shadow_disp@ha
		addi r6, r3, float_neg5000_rsh_00014494@l
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
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void moamoa_joint_position(Moamoa* moa, Vec* out) {
#ifdef NONMATCHING
    NpcEntry* npc = npcNameToPtr((char*)str_000047B4);
    AnimationPose* anim = animPoseGetAnimPosePtr(npc->poseId);
    f32 t;
    Vec* a = anim->worldPositions[0] + wp->chainIdx[moa->group][0];
    Vec* b = anim->worldPositions[0] + wp->chainIdx[moa->group][1];
    Vec tmp;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x90010044
		opword 0xDBE10030
		opword 0xF3E10038
		opword 0xBFC10028
		lis r5, rsh_06_str_000047B4@ha
		opword 0x7C7E1B78
		addi r3, r5, rsh_06_str_000047B4@l
		opword 0x7C9F2378
		bl npcNameToPtr
		opword 0x80630104
		bl animPoseGetAnimPosePtr
		lis r4, wp@ha
		opword 0xA91E0048
		lwz r9, wp@l(r4)
		opword 0x3CC04330
		opword 0x5500083C
		opword 0xA8FE004A
		opword 0x7C890214
		opword 0x5508103A
		opword 0xA8040570
		opword 0x6CE48000
		lis r5, double_to_int_rsh_00014488@ha
		opword 0x9081001C
		addi r7, r5, double_to_int_rsh_00014488@l
		opword 0x7D294214
		opword 0x6C058000
		opword 0x90C10018
		opword 0xC8470000
		opword 0x7FE4FB78
		opword 0xC8010018
		opword 0x90A10024
		opword 0xEC201028
		opword 0xA9090672
		opword 0x90C10020
		opword 0xA8090670
		opword 0x1D08000C
		opword 0xC8010020
		opword 0x8063015C
		opword 0xEC001028
		opword 0x1C00000C
		opword 0x80630000
		opword 0xEFE10024
		opword 0x7FC34214
		opword 0x7C630214
		opword 0xFC20F890
		bl PSVECScale
		lis r4, float_1_rsh_00014470@ha
		opword 0x7FC3F378
		addi r5, r4, float_1_rsh_00014470@l
		opword 0x38810008
		opword 0xC0050000
		opword 0xEC20F828
		bl PSVECScale
		opword 0x7FE3FB78
		opword 0x7FE5FB78
		opword 0x38810008
		bl PSVECAdd
		opword 0xE3E10038
		opword 0xCBE10030
		opword 0xBBC10028
		opword 0x80010044
		opword 0x7C0803A6
		opword 0x38210040
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    t = (f32)moa->order / (f32)wp->chainNum[moa->group];
    PSVECScale(a, out, t);
    PSVECScale(b, &tmp, float_1_rsh_00014470[0] - t);
    PSVECAdd(out, &tmp, out);
}

extern const char str_000041D0[];
extern const char str_000041DC[];
extern const char str_000041E4[];
extern const char str_000041F0[];
extern const char str_000041FC[];
extern const char str_00004200[];
extern const char str_0000420C[];
extern const char str_00004210[];
extern const char str_00004218[];
extern const char str_0000421C[];
extern const char str_00004224[];
extern const char str_00004228[];
extern const char str_00004230[];
extern const char str_00004238[];
extern const char str_00004240[];
static const char* fs_group_tbl[][2] = {
        {(char*)str_000041D0, (char*)str_000041DC},
        {(char*)str_000041E4, (char*)str_000041DC},
        {(char*)str_000041F0, (char*)str_000041FC},
        {(char*)str_00004200, (char*)str_0000420C},
        {(char*)str_00004210, (char*)str_00004218},
        {(char*)str_0000421C, (char*)str_00004224},
        {(char*)str_00004228, (char*)str_000041FC},
        {(char*)str_00004230, (char*)str_000041FC},
        {(char*)str_00004238, (char*)str_000041FC},
        {(char*)str_00004240, (char*)str_000041FC},
        {(char*)str_000041D0, (char*)str_000041DC},
    };
static Mtx fs_mt = {
        {8.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 8.0f, 0.0f, 0.5f},
        {0.0f, 0.0f, 8.0f, 0.0f},
    };
#endif
#ifndef NONMATCHING
extern const char rsh_06_str_000041D0[];
extern const char rsh_06_str_000041DC[];
extern const char rsh_06_str_000041E4[];
extern const char rsh_06_str_000041F0[];
extern const char rsh_06_str_000041FC[];
extern const char rsh_06_str_00004200[];
extern const char rsh_06_str_0000420C[];
extern const char rsh_06_str_00004210[];
extern const char rsh_06_str_00004218[];
extern const char rsh_06_str_0000421C[];
extern const char rsh_06_str_00004224[];
extern const char rsh_06_str_00004228[];
extern const char rsh_06_str_00004230[];
extern const char rsh_06_str_00004238[];
extern const char rsh_06_str_00004240[];
#endif
static s32 sharinDt[] = {
#ifdef NONMATCHING
    (s32)((char*)str_0000430C), 0, 0, -229998976, (s32)((char*)str_00004314), 0, 0, -229998976,
    (s32)((char*)str_0000431C), 2, 0, -229998976, (s32)((char*)str_00004324), 1, 1, -229998976,
    (s32)((char*)str_0000432C), 1, 1, -229998976, (s32)((char*)str_00004334), 0, 0, -229998976,
    (s32)((char*)str_0000433C), 0, 0, -229998976, (s32)((char*)str_00004344), 0, 0, -229998976,
    (s32)((char*)str_0000434C), 0, 0, -229998976, (s32)((char*)str_00004354), 0, 0, -229998976,
    (s32)((char*)str_0000435C), 0, 0, -229998976, (s32)((char*)str_00004364), 0, 0, -229998976,
    (s32)((char*)str_0000436C), 0, 0, -229998976, (s32)((char*)str_00004374), 0, 0, -229998976,
    (s32)((char*)str_0000437C), 0, 0, -229998976, (s32)((char*)str_00004384), 0, 0, -229998976,
    (s32)((char*)str_0000438C), 0, 0, -229998976, (s32)((char*)str_00004394), 0, 0, -229998976,
    (s32)((char*)str_0000439C), 0, 0, -229998976, (s32)((char*)str_000043A4), 0, 0, -229998976,
    (s32)((char*)str_000043AC), 0, 0, -230001024, (s32)((char*)str_000043B8), 0, 0, -230001024,
    (s32)((char*)str_000043C4), 2, 0, -230001024, (s32)((char*)str_000043D0), 1, 1, -230001024,
    (s32)((char*)str_000043DC), 1, 1, -230001024, (s32)((char*)str_000043E8), 0, 0, -229998976,
#endif
#ifndef NONMATCHING
    (s32)((char*)rsh_06_str_0000430C), 0, 0, -229998976, (s32)((char*)rsh_06_str_00004314), 0, 0, -229998976,
    (s32)((char*)rsh_06_str_0000431C), 2, 0, -229998976, (s32)((char*)rsh_06_str_00004324), 1, 1, -229998976,
    (s32)((char*)rsh_06_str_0000432C), 1, 1, -229998976, (s32)((char*)str_00004334), 0, 0, -229998976,
    (s32)((char*)rsh_06_str_0000433C), 0, 0, -229998976, (s32)((char*)rsh_06_str_00004344), 0, 0, -229998976,
    (s32)((char*)rsh_06_str_0000434C), 0, 0, -229998976, (s32)((char*)rsh_06_str_00004354), 0, 0, -229998976,
    (s32)((char*)rsh_06_str_0000435C), 0, 0, -229998976, (s32)((char*)rsh_06_str_00004364), 0, 0, -229998976,
    (s32)((char*)rsh_06_str_0000436C), 0, 0, -229998976, (s32)((char*)rsh_06_str_00004374), 0, 0, -229998976,
    (s32)((char*)rsh_06_str_0000437C), 0, 0, -229998976, (s32)((char*)str_00004384), 0, 0, -229998976,
    (s32)((char*)rsh_06_str_0000438C), 0, 0, -229998976, (s32)((char*)rsh_06_str_00004394), 0, 0, -229998976,
    (s32)((char*)rsh_06_str_0000439C), 0, 0, -229998976, (s32)((char*)rsh_06_str_000043A4), 0, 0, -229998976,
    (s32)((char*)rsh_06_str_000043AC), 0, 0, -230001024, (s32)((char*)rsh_06_str_000043B8), 0, 0, -230001024,
    (s32)((char*)rsh_06_str_000043C4), 2, 0, -230001024, (s32)((char*)rsh_06_str_000043D0), 1, 1, -230001024,
    (s32)((char*)rsh_06_str_000043DC), 1, 1, -230001024, (s32)((char*)rsh_06_str_000043E8), 0, 0, -229998976,
#endif
    (s32)((char*)str_000043F4), 0, 0, -229998976, (s32)((char*)str_00004400), 0, 0, -229998976,
    0, 0, 0, 0,
};

static EVT_BEGIN(evt_sharin_main)
#ifdef NONMATCHING
    SET_FLOAT_VALUE(LW(10), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
    SET_FLOAT_VALUE(LW(10), FLOAT((0.0f)))
#endif
    SWITCH(LW(1))
        CASE_EQUAL(0)
        SET_FLOAT_VALUE(LW(11), FLOAT(23.889648f))
        CASE_EQUAL(1)
        SET_FLOAT_VALUE(LW(11), FLOAT(31.139648f))
        CASE_EQUAL(2)
        SET_FLOAT_VALUE(LW(11), FLOAT(55.01953f))
    END_SWITCH
    LOOP(0)
        SWITCH(LW(2))
            CASE_EQUAL(0)
            SET_FLOAT_VALUE(LW(9), GW(0))
            CASE_EQUAL(1)
            SET_FLOAT_VALUE(LW(9), GW(1))
        END_SWITCH
        DIVIDE_FLOAT(LW(9), LW(11))
        MULTIPLY_FLOAT(LW(9), FLOAT(57.29492f))
        ADD_FLOAT(LW(10), LW(9))
#ifdef NONMATCHING
        IF_INT_GREATER(LW(10), FLOAT(360.0f))
            SUBTRACT_FLOAT(LW(10), FLOAT(360.0f))
#endif
#ifndef NONMATCHING
        IF_INT_GREATER(LW(10), FLOAT((360.0f)))
            SUBTRACT_FLOAT(LW(10), FLOAT((360.0f)))
#endif
        END_IF
#ifdef NONMATCHING
        IF_INT_LESS(LW(10), FLOAT(0.0f))
            ADD_FLOAT(LW(10), FLOAT(360.0f))
#endif
#ifndef NONMATCHING
        IF_INT_LESS(LW(10), FLOAT((0.0f)))
            ADD_FLOAT(LW(10), FLOAT((360.0f)))
#endif
        END_IF
        SET_FLOAT_VALUE(LW(12), LW(10))
        MULTIPLY_FLOAT(LW(12), LW(3))
        CALL(evt_mapobj_rotate, 1, LW(0), 0, 0, LW(12))
        WAIT_FRAMES(1)
        LOOP(0)
            IF_INT_EQUAL(GSWF(3583), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(evt_sharin)
    SET_INT_READ_ADDR(PTR(sharinDt))
    LOOP(0)
        READ_INT4(LW(0), LW(1), LW(2), LW(3))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        SPAWN_EVENT(PTR(evt_sharin_main))
    END_LOOP
    RETURN
EVT_END()

static s32 clankDt[] = {
#ifdef NONMATCHING
    (s32)((char*)str_0000440C), 0, 0, -229979520, -229998976, (s32)((char*)str_00004414), 1, 1,
    -229983104, -229998976, (s32)((char*)str_0000441C), 0, 0, -229979520, -229998976, (s32)((char*)str_00004424),
    1, 1, -229983104, -229998976, (s32)((char*)str_0000442C), 0, 0, -229979520,
    -230001024, (s32)((char*)str_00004434), 1, 1, -229983104, -230001024, (s32)((char*)str_0000443C), 0,
    0, -229979520, -230001024, (s32)((char*)str_00004444), 1, 1, -229983104, -230001024,
#endif
#ifndef NONMATCHING
    (s32)((char*)rsh_06_str_0000440C), 0, 0, -229979520, -229998976, (s32)((char*)rsh_06_str_00004414), 1, 1,
    -229983104, -229998976, (s32)((char*)rsh_06_str_0000441C), 0, 0, -229979520, -229998976, (s32)((char*)rsh_06_str_00004424),
    1, 1, -229983104, -229998976, (s32)((char*)rsh_06_str_0000442C), 0, 0, -229979520,
    -230001024, (s32)((char*)rsh_06_str_00004434), 1, 1, -229983104, -230001024, (s32)((char*)rsh_06_str_0000443C), 0,
    0, -229979520, -230001024, (s32)((char*)rsh_06_str_00004444), 1, 1, -229983104, -230001024,
#endif
    0, 0, 0, 0, 0,
};

static EVT_BEGIN(evt_clank_main)
#ifdef NONMATCHING
    SET_FLOAT_VALUE(LW(10), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
    SET_FLOAT_VALUE(LW(10), FLOAT((0.0f)))
#endif
    SWITCH(LW(1))
        CASE_EQUAL(0)
        SET_FLOAT_VALUE(LW(11), FLOAT(23.889648f))
        CASE_EQUAL(1)
        SET_FLOAT_VALUE(LW(11), FLOAT(31.139648f))
        CASE_EQUAL(2)
        SET_FLOAT_VALUE(LW(11), FLOAT(55.01953f))
    END_SWITCH
    LOOP(0)
        SWITCH(LW(2))
            CASE_EQUAL(0)
            SET_FLOAT_VALUE(LW(9), GW(0))
            CASE_EQUAL(1)
            SET_FLOAT_VALUE(LW(9), GW(1))
        END_SWITCH
        DIVIDE_FLOAT(LW(9), LW(11))
        MULTIPLY_FLOAT(LW(9), FLOAT(57.29492f))
        ADD_FLOAT(LW(10), LW(9))
#ifdef NONMATCHING
        IF_INT_GREATER(LW(10), FLOAT(360.0f))
            SUBTRACT_FLOAT(LW(10), FLOAT(360.0f))
#endif
#ifndef NONMATCHING
        IF_INT_GREATER(LW(10), FLOAT((360.0f)))
            SUBTRACT_FLOAT(LW(10), FLOAT((360.0f)))
#endif
        END_IF
#ifdef NONMATCHING
        IF_INT_LESS(LW(10), FLOAT(0.0f))
            ADD_FLOAT(LW(10), FLOAT(360.0f))
#endif
#ifndef NONMATCHING
        IF_INT_LESS(LW(10), FLOAT((0.0f)))
            ADD_FLOAT(LW(10), FLOAT((360.0f)))
#endif
        END_IF
        SET_FLOAT_VALUE(LW(12), LW(10))
        MULTIPLY_FLOAT(LW(12), LW(4))
        CALL(evt_sub_get_sincos, LW(12), LW(13), LW(14))
        MULTIPLY_FLOAT(LW(13), LW(3))
        MULTIPLY_FLOAT(LW(14), LW(3))
        SUBTRACT_FLOAT(LW(14), LW(3))
#ifdef NONMATCHING
        MULTIPLY_FLOAT(LW(14), FLOAT(-1.0f))
        CALL(evt_mapobj_trans, 1, LW(0), LW(14), LW(13), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
        MULTIPLY_FLOAT(LW(14), FLOAT((-1.0f)))
        CALL(evt_mapobj_trans, 1, LW(0), LW(14), LW(13), FLOAT((0.0f)))
#endif
        WAIT_FRAMES(1)
        LOOP(0)
            IF_INT_EQUAL(GSWF(3583), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(evt_clank)
    SET_INT_READ_ADDR(PTR(clankDt))
    LOOP(0)
        READ_INT4(LW(0), LW(1), LW(2), LW(3))
        READ_INT(LW(4))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        SPAWN_EVENT(PTR(evt_clank_main))
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(evt_bg)
#ifdef NONMATCHING
    SET_FLOAT_VALUE(LW(10), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(11), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
    SET_FLOAT_VALUE(LW(10), FLOAT((0.0f)))
    SET_FLOAT_VALUE(LW(11), FLOAT((0.0f)))
#endif
    LOOP(0)
        SET_FLOAT_VALUE(LW(0), GW(0))
        ADD_FLOAT(LW(10), LW(0))
        IF_INT_GREATER(LW(10), FLOAT(1200.0f))
            SUBTRACT_FLOAT(LW(10), FLOAT(2400.0f))
        END_IF
        IF_INT_LESS(LW(10), FLOAT(-1200.0f))
            ADD_FLOAT(LW(10), FLOAT(2400.0f))
        END_IF
        ADD_FLOAT(LW(11), LW(0))
        IF_INT_GREATER(LW(11), FLOAT(3600.0f))
            SUBTRACT_FLOAT(LW(11), FLOAT(7200.0f))
        END_IF
        IF_INT_LESS(LW(11), FLOAT(-3600.0f))
            ADD_FLOAT(LW(11), FLOAT(7200.0f))
        END_IF
#ifdef NONMATCHING
        CALL(evt_mapobj_trans, 1, STRING(((char*)str_0000444C)), LW(10), 0, 0)
        CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004454)), LW(10), 0, 0)
        CALL(evt_mapobj_trans, 1, STRING(((char*)str_0000445C)), LW(11), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_mapobj_trans, 1, STRING(((char*)rsh_06_str_0000444C)), LW(10), 0, 0)
        CALL(evt_mapobj_trans, 1, STRING(((char*)rsh_06_str_00004454)), LW(10), 0, 0)
        CALL(evt_mapobj_trans, 1, STRING(((char*)rsh_06_str_0000445C)), LW(11), 0, 0)
#endif
        WAIT_FRAMES(1)
        LOOP(0)
            IF_INT_EQUAL(GSWF(3583), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(evt_hoshi)
#ifdef NONMATCHING
    SET_FLOAT_VALUE(LW(10), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
    SET_FLOAT_VALUE(LW(10), FLOAT((0.0f)))
#endif
    LOOP(0)
        SET_FLOAT_VALUE(LW(9), GW(0))
#ifdef NONMATCHING
        DIVIDE_FLOAT(LW(9), FLOAT(30.0f))
#endif
#ifndef NONMATCHING
        DIVIDE_FLOAT(LW(9), FLOAT((30.0f)))
#endif
        MULTIPLY_FLOAT(LW(9), FLOAT(57.29492f))
        ADD_FLOAT(LW(10), LW(9))
#ifdef NONMATCHING
        IF_INT_GREATER(LW(10), FLOAT(360.0f))
            SUBTRACT_FLOAT(LW(10), FLOAT(360.0f))
#endif
#ifndef NONMATCHING
        IF_INT_GREATER(LW(10), FLOAT((360.0f)))
            SUBTRACT_FLOAT(LW(10), FLOAT((360.0f)))
#endif
        END_IF
#ifdef NONMATCHING
        IF_INT_LESS(LW(10), FLOAT(0.0f))
            ADD_FLOAT(LW(10), FLOAT(360.0f))
#endif
#ifndef NONMATCHING
        IF_INT_LESS(LW(10), FLOAT((0.0f)))
            ADD_FLOAT(LW(10), FLOAT((360.0f)))
#endif
        END_IF
#ifdef NONMATCHING
        CALL(evt_mapobj_rotate, 0, STRING(((char*)str_00004464)), LW(10), 0, 0)
        CALL(evt_mapobj_rotate, 0, STRING(((char*)str_00004470)), LW(10), 0, 0)
        CALL(evt_mapobj_rotate, 0, STRING(((char*)str_0000447C)), LW(10), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_mapobj_rotate, 0, STRING(((char*)rsh_06_str_00004464)), LW(10), 0, 0)
        CALL(evt_mapobj_rotate, 0, STRING(((char*)rsh_06_str_00004470)), LW(10), 0, 0)
        CALL(evt_mapobj_rotate, 0, STRING(((char*)rsh_06_str_0000447C)), LW(10), 0, 0)
#endif
        CALL(evt_mapobj_rotate, 0, STRING(((char*)str_00004488)), LW(10), 0, 0)
#ifdef NONMATCHING
        CALL(evt_mapobj_rotate, 0, STRING(((char*)str_00004498)), LW(10), 0, 0)
        CALL(evt_mapobj_rotate, 0, STRING(((char*)str_000044A4)), LW(10), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_mapobj_rotate, 0, STRING(((char*)rsh_06_str_00004498)), LW(10), 0, 0)
        CALL(evt_mapobj_rotate, 0, STRING(((char*)rsh_06_str_000044A4)), LW(10), 0, 0)
#endif
        WAIT_FRAMES(1)
        LOOP(0)
            IF_INT_EQUAL(GSWF(3583), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(hom_10_evt_resha_start)
    SET_VALUE(GSWF(3583), 1)
    SET_VALUE(GSWF(3579), 0)
    SET_VALUE(GSWF(3580), 0)
    SET_VALUE(GSWF(3581), 0)
#ifdef NONMATCHING
    CALL(evt_mapobj_get_position, STRING(((char*)str_000044B4)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000044BC)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_get_position, STRING(((char*)rsh_06_str_000044B4)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)rsh_06_str_000044BC)), LW(0), LW(1), LW(2), 0)
#endif
    WAIT_MS(200)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000044BC)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)rsh_06_str_000044BC)), LW(0), LW(1), LW(2), 0)
#endif
    CALL(evt_sub_get_mapname, LW(0))
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044D4)))
        CALL(evt_snd_sfxon, STRING(((char*)str_000044DC)), 0)
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_000044D4)))
        CALL(evt_snd_sfxon, STRING(((char*)rsh_06_str_000044DC)), 0)
#endif
    END_IF
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044F4)))
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_000044F4)))
#endif
        IF_INT_LESS(GSW(0), 339)
#ifdef NONMATCHING
            CALL(evt_snd_sfxon, STRING(((char*)str_000044FC)), 0)
#endif
#ifndef NONMATCHING
            CALL(evt_snd_sfxon, STRING(((char*)rsh_06_str_000044FC)), 0)
#endif
            ELSE
#ifdef NONMATCHING
            CALL(evt_snd_sfxon, STRING(((char*)str_00004514)), 0)
#endif
#ifndef NONMATCHING
            CALL(evt_snd_sfxon, STRING(((char*)rsh_06_str_00004514)), 0)
#endif
        END_IF
    END_IF
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00004530)))
        CALL(evt_snd_sfxon, STRING(((char*)str_00004538)), 0)
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_00004530)))
        CALL(evt_snd_sfxon, STRING(((char*)rsh_06_str_00004538)), 0)
#endif
    END_IF
    CALL(evt_sub_get_mapname, LW(0))
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044F4)))
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_000044F4)))
#endif
        BEGIN_INLINE_EVENT
#ifdef NONMATCHING
            SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
            SET_FLOAT_VALUE(LW(0), FLOAT((0.0f)))
#endif
            LOOP(0)
                ADD_FLOAT(LW(0), GW(0))
#ifdef NONMATCHING
                CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004550)), LW(0), 0, 0)
#endif
#ifndef NONMATCHING
                CALL(evt_mapobj_trans, 1, STRING(((char*)rsh_06_str_00004550)), LW(0), 0, 0)
#endif
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044D4)))
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_000044D4)))
#endif
        BEGIN_INLINE_EVENT
#ifdef NONMATCHING
            SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
            SET_FLOAT_VALUE(LW(0), FLOAT((0.0f)))
#endif
            LOOP(0)
                ADD_FLOAT(LW(0), GW(0))
#ifdef NONMATCHING
                CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004550)), LW(0), 0, 0)
#endif
#ifndef NONMATCHING
                CALL(evt_mapobj_trans, 1, STRING(((char*)rsh_06_str_00004550)), LW(0), 0, 0)
#endif
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
        SET_FLOAT_VALUE(GW(0), FLOAT((0.0f)))
#endif
        CALL(evt_sub_intpl_msec_init, 11, 0, -1500, 20000)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
#endif
#ifndef NONMATCHING
        DIVIDE_FLOAT(LW(0), FLOAT((100.0f)))
#endif
        SET_FLOAT_VALUE(GW(0), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        LOOP(0)
            SET_FLOAT_VALUE(GW(0), FLOAT(-15.0f))
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SPAWN_EVENT_GET_ID(PTR(evt_sub_stopwatch), LW(0))
        LOOP(0)
            SET_FLOAT_VALUE(GW(1), GW(0))
            CALL(evt_sub_get_stopwatch, LW(0), LW(1))
            IF_INT_GREATER(LW(1), 1500)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_msec_init, 11, 0, -1000, 1000)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
#endif
#ifndef NONMATCHING
        DIVIDE_FLOAT(LW(0), FLOAT((100.0f)))
#endif
        SET_FLOAT_VALUE(GW(1), GW(0))
        ADD_FLOAT(GW(1), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
        CALL(evt_sub_intpl_msec_init, 11, -1000, 0, 1000)
        LABEL(2)
        CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
#endif
#ifndef NONMATCHING
        DIVIDE_FLOAT(LW(0), FLOAT((100.0f)))
#endif
        SET_FLOAT_VALUE(GW(1), GW(0))
        ADD_FLOAT(GW(1), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(2)
        END_IF
        LOOP(0)
            SET_FLOAT_VALUE(GW(1), GW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    RETURN
EVT_END()

static EVT_BEGIN(hom_10_evt_resha_start2)
    SET_VALUE(GSWF(3583), 1)
    SET_VALUE(GSWF(3579), 0)
    SET_VALUE(GSWF(3580), 0)
    SET_VALUE(GSWF(3581), 0)
#ifdef NONMATCHING
    CALL(evt_mapobj_get_position, STRING(((char*)str_000044B4)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000044BC)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_get_position, STRING(((char*)rsh_06_str_000044B4)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)rsh_06_str_000044BC)), LW(0), LW(1), LW(2), 0)
#endif
    WAIT_MS(200)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000044BC)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)rsh_06_str_000044BC)), LW(0), LW(1), LW(2), 0)
#endif
    CALL(evt_sub_get_mapname, LW(0))
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044D4)))
        CALL(evt_snd_sfxon, STRING(((char*)str_000044DC)), 0)
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_000044D4)))
        CALL(evt_snd_sfxon, STRING(((char*)rsh_06_str_000044DC)), 0)
#endif
    END_IF
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044F4)))
        CALL(evt_snd_sfxon, STRING(((char*)str_00004558)), 0)
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_000044F4)))
        CALL(evt_snd_sfxon, STRING(((char*)rsh_06_str_00004558)), 0)
#endif
    END_IF
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00004530)))
        CALL(evt_snd_sfxon, STRING(((char*)str_00004538)), 0)
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_00004530)))
        CALL(evt_snd_sfxon, STRING(((char*)rsh_06_str_00004538)), 0)
#endif
    END_IF
    CALL(evt_sub_get_mapname, LW(0))
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044F4)))
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_000044F4)))
#endif
        BEGIN_INLINE_EVENT
#ifdef NONMATCHING
            SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
            SET_FLOAT_VALUE(LW(0), FLOAT((0.0f)))
#endif
            LOOP(0)
                ADD_FLOAT(LW(0), GW(0))
#ifdef NONMATCHING
                CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004550)), LW(0), 0, 0)
#endif
#ifndef NONMATCHING
                CALL(evt_mapobj_trans, 1, STRING(((char*)rsh_06_str_00004550)), LW(0), 0, 0)
#endif
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044D4)))
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_000044D4)))
#endif
        BEGIN_INLINE_EVENT
#ifdef NONMATCHING
            SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
            SET_FLOAT_VALUE(LW(0), FLOAT((0.0f)))
#endif
            LOOP(0)
                ADD_FLOAT(LW(0), GW(0))
#ifdef NONMATCHING
                CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004550)), LW(0), 0, 0)
#endif
#ifndef NONMATCHING
                CALL(evt_mapobj_trans, 1, STRING(((char*)rsh_06_str_00004550)), LW(0), 0, 0)
#endif
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00004530)))
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_00004530)))
#endif
        BEGIN_INLINE_EVENT
#ifdef NONMATCHING
            SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
            SET_FLOAT_VALUE(LW(0), FLOAT((0.0f)))
#endif
            LOOP(0)
                ADD_FLOAT(LW(0), GW(0))
#ifdef NONMATCHING
                CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004550)), LW(0), 0, 0)
#endif
#ifndef NONMATCHING
                CALL(evt_mapobj_trans, 1, STRING(((char*)rsh_06_str_00004550)), LW(0), 0, 0)
#endif
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
        SET_FLOAT_VALUE(GW(0), FLOAT((0.0f)))
#endif
        CALL(evt_sub_intpl_msec_init, 11, 0, 1500, 20000)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
#endif
#ifndef NONMATCHING
        DIVIDE_FLOAT(LW(0), FLOAT((100.0f)))
#endif
        SET_FLOAT_VALUE(GW(0), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        LOOP(0)
#ifdef NONMATCHING
            SET_FLOAT_VALUE(GW(0), FLOAT(15.0f))
#endif
#ifndef NONMATCHING
            SET_FLOAT_VALUE(GW(0), FLOAT((15.0f)))
#endif
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SPAWN_EVENT_GET_ID(PTR(evt_sub_stopwatch), LW(0))
        LOOP(0)
            SET_FLOAT_VALUE(GW(1), GW(0))
            CALL(evt_sub_get_stopwatch, LW(0), LW(1))
            IF_INT_GREATER(LW(1), 1500)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_msec_init, 11, 0, 1000, 1000)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
#endif
#ifndef NONMATCHING
        DIVIDE_FLOAT(LW(0), FLOAT((100.0f)))
#endif
        SET_FLOAT_VALUE(GW(1), GW(0))
        ADD_FLOAT(GW(1), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
        CALL(evt_sub_intpl_msec_init, 11, 1000, 0, 1000)
        LABEL(2)
        CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
#endif
#ifndef NONMATCHING
        DIVIDE_FLOAT(LW(0), FLOAT((100.0f)))
#endif
        SET_FLOAT_VALUE(GW(1), GW(0))
        ADD_FLOAT(GW(1), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(2)
        END_IF
        LOOP(0)
            SET_FLOAT_VALUE(GW(1), GW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(hom_10_evt_resha_start3)
    SET_VALUE(GSWF(3583), 1)
    SET_FLOAT_VALUE(GW(0), FLOAT(-15.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(-15.0f))
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(hom_10_evt_resha_start4)
    SET_VALUE(GSWF(3583), 1)
#ifdef NONMATCHING
    SET_FLOAT_VALUE(GW(0), FLOAT(15.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(15.0f))
#endif
#ifndef NONMATCHING
    SET_FLOAT_VALUE(GW(0), FLOAT((15.0f)))
    SET_FLOAT_VALUE(GW(1), FLOAT((15.0f)))
#endif
    RETURN
EVT_END()

static EVT_BEGIN(stop_1)
    SET_VALUE(GSWF(3583), 1)
#ifdef NONMATCHING
    SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
    SET_FLOAT_VALUE(GW(0), FLOAT((0.0f)))
    SET_FLOAT_VALUE(GW(1), FLOAT((0.0f)))
#endif
    SET_FLOAT_VALUE(LW(2), FLOAT(3000.0f))
    CALL(evt_sub_get_mapname, LW(0))
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044D4)))
        CALL(evt_snd_sfxon, STRING(((char*)str_00004574)), 0)
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_000044D4)))
        CALL(evt_snd_sfxon, STRING(((char*)rsh_06_str_00004574)), 0)
#endif
    END_IF
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044F4)))
        CALL(evt_snd_sfxon, STRING(((char*)str_0000458C)), 0)
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_000044F4)))
        CALL(evt_snd_sfxon, STRING(((char*)rsh_06_str_0000458C)), 0)
#endif
    END_IF
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00004530)))
        CALL(evt_snd_sfxon, STRING(((char*)str_000045A4)), 0)
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_00004530)))
        CALL(evt_snd_sfxon, STRING(((char*)rsh_06_str_000045A4)), 0)
#endif
    END_IF
    CALL(evt_sub_intpl_msec_init, 11, 3000, 0, 10000)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
    MULTIPLY_FLOAT(LW(0), FLOAT(1.0f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004550)), LW(0), 0, 0)
#endif
#ifndef NONMATCHING
    MULTIPLY_FLOAT(LW(0), FLOAT((1.0f)))
    CALL(evt_mapobj_trans, 1, STRING(((char*)rsh_06_str_00004550)), LW(0), 0, 0)
#endif
    SUBTRACT_FLOAT(LW(2), LW(0))
    SET_FLOAT_VALUE(GW(0), LW(2))
    SET_FLOAT_VALUE(GW(1), LW(2))
#ifdef NONMATCHING
    MULTIPLY_FLOAT(GW(0), FLOAT(-1.0f))
    MULTIPLY_FLOAT(GW(1), FLOAT(-1.0f))
#endif
#ifndef NONMATCHING
    MULTIPLY_FLOAT(GW(0), FLOAT((-1.0f)))
    MULTIPLY_FLOAT(GW(1), FLOAT((-1.0f)))
#endif
    SET_FLOAT_VALUE(LW(2), LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    SET_VALUE(GSWF(3583), 0)
    RETURN
EVT_END()

static EVT_BEGIN(stop_2)
    SET_VALUE(GSWF(3583), 1)
#ifdef NONMATCHING
    SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
    SET_FLOAT_VALUE(GW(0), FLOAT((0.0f)))
    SET_FLOAT_VALUE(GW(1), FLOAT((0.0f)))
#endif
    SET_FLOAT_VALUE(LW(2), FLOAT(-3000.0f))
    CALL(evt_sub_get_mapname, LW(0))
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044D4)))
        CALL(evt_snd_sfxon, STRING(((char*)str_00004574)), 0)
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_000044D4)))
        CALL(evt_snd_sfxon, STRING(((char*)rsh_06_str_00004574)), 0)
#endif
    END_IF
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044F4)))
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_000044F4)))
#endif
        CALL(evt_snd_sfxon, STRING(((char*)str_000045BC)), 0)
    END_IF
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00004530)))
        CALL(evt_snd_sfxon, STRING(((char*)str_000045A4)), 0)
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_00004530)))
        CALL(evt_snd_sfxon, STRING(((char*)rsh_06_str_000045A4)), 0)
#endif
    END_IF
    CALL(evt_sub_intpl_msec_init, 11, -3000, 0, 10000)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
    MULTIPLY_FLOAT(LW(0), FLOAT(1.0f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004550)), LW(0), 0, 0)
#endif
#ifndef NONMATCHING
    MULTIPLY_FLOAT(LW(0), FLOAT((1.0f)))
    CALL(evt_mapobj_trans, 1, STRING(((char*)rsh_06_str_00004550)), LW(0), 0, 0)
#endif
    SUBTRACT_FLOAT(LW(2), LW(0))
    SET_FLOAT_VALUE(GW(0), LW(2))
    SET_FLOAT_VALUE(GW(1), LW(2))
#ifdef NONMATCHING
    MULTIPLY_FLOAT(GW(0), FLOAT(-1.0f))
    MULTIPLY_FLOAT(GW(1), FLOAT(-1.0f))
#endif
#ifndef NONMATCHING
    MULTIPLY_FLOAT(GW(0), FLOAT((-1.0f)))
    MULTIPLY_FLOAT(GW(1), FLOAT((-1.0f)))
#endif
    SET_FLOAT_VALUE(LW(2), LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    SET_VALUE(GSWF(3583), 0)
    RETURN
EVT_END()

static EVT_BEGIN(hom_10_evt_resha_stop)
    CALL(evt_sub_get_mapname, LW(0))
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00004530)))
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_00004530)))
#endif
        SPAWN_EVENT(PTR(stop_1))
    END_IF
    CALL(evt_sub_get_mapname, LW(0))
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044D4)))
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_000044D4)))
#endif
        SPAWN_EVENT(PTR(stop_2))
    END_IF
    CALL(evt_sub_get_mapname, LW(0))
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044F4)))
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_000044F4)))
#endif
        IF_INT_EQUAL(GSWF(3578), 0)
            SPAWN_EVENT(PTR(stop_1))
            ELSE
            SPAWN_EVENT(PTR(stop_2))
        END_IF
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(evt_ramp)
    LOOP(0)
        CALL(ramp_r)
#ifdef NONMATCHING
        CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000044B4)), 0, 0, LW(10))
        CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000045D8)), 0, 0, LW(10))
#endif
#ifndef NONMATCHING
        CALL(evt_mapobj_rotate, 1, STRING(((char*)rsh_06_str_000044B4)), 0, 0, LW(10))
        CALL(evt_mapobj_rotate, 1, STRING(((char*)rsh_06_str_000045D8)), 0, 0, LW(10))
#endif
        WAIT_FRAMES(1)
        LOOP(0)
            IF_INT_EQUAL(GSWF(3583), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

static s32 pika_tbl[] = {
#ifdef NONMATCHING
    (s32)((char*)str_000045E0), (s32)((char*)str_000045EC), (s32)((char*)str_000045F8), (s32)((char*)str_00004604), (s32)((char*)str_00004610), (s32)((char*)str_00004618), (s32)((char*)str_00004620), (s32)((char*)str_00004628),
    (s32)((char*)str_00004630), (s32)((char*)str_00004638), (s32)((char*)str_00004644), (s32)((char*)str_00004650), (s32)((char*)str_0000465C), (s32)((char*)str_00004668), 0,
#endif
#ifndef NONMATCHING
    (s32)((char*)str_000045E0), (s32)((char*)rsh_06_str_000045EC), (s32)((char*)rsh_06_str_000045F8), (s32)((char*)rsh_06_str_00004604), (s32)((char*)rsh_06_str_00004610), (s32)((char*)rsh_06_str_00004618), (s32)((char*)rsh_06_str_00004620), (s32)((char*)rsh_06_str_00004628),
    (s32)((char*)rsh_06_str_00004630), (s32)((char*)rsh_06_str_00004638), (s32)((char*)rsh_06_str_00004644), (s32)((char*)rsh_06_str_00004650), (s32)((char*)str_0000465C), (s32)((char*)rsh_06_str_00004668), 0,
#endif
};

__declspec(section ".data") static s32 pika_tbl_rsh_06[] = {
#ifdef NONMATCHING
    (s32)((char*)str_000045E0), (s32)((char*)str_000045EC), (s32)((char*)str_000045F8), (s32)((char*)str_00004604), (s32)((char*)str_00004610), (s32)((char*)str_00004618), (s32)((char*)str_00004620), (s32)((char*)str_00004628),
    (s32)((char*)str_00004630), 0,
#endif
#ifndef NONMATCHING
    (s32)((char*)str_000045E0), (s32)((char*)rsh_06_str_000045EC), (s32)((char*)rsh_06_str_000045F8), (s32)((char*)rsh_06_str_00004604), (s32)((char*)rsh_06_str_00004610), (s32)((char*)rsh_06_str_00004618), (s32)((char*)rsh_06_str_00004620), (s32)((char*)rsh_06_str_00004628),
    (s32)((char*)rsh_06_str_00004630), 0,
#endif
};

static EVT_BEGIN(hom_10_evt_resha_sub)
    SET_VALUE(GSWF(3583), 0)
#ifdef NONMATCHING
    SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
    SET_FLOAT_VALUE(GW(0), FLOAT((0.0f)))
    SET_FLOAT_VALUE(GW(1), FLOAT((0.0f)))
#endif
    SPAWN_EVENT(PTR(evt_sharin))
    SPAWN_EVENT(PTR(evt_clank))
    SET_VALUE(LF(0), 0)
    CALL(evt_sub_get_mapname, LW(0))
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00004674)))
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_00004674)))
#endif
        SET_VALUE(LF(0), 1)
    END_IF
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_0000467C)))
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_0000467C)))
#endif
        SET_VALUE(LF(0), 1)
    END_IF
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00004684)))
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_00004684)))
#endif
        SET_VALUE(LF(0), 1)
    END_IF
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_0000468C)))
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_0000468C)))
#endif
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_EQUAL(LF(0), 1)
        SPAWN_EVENT(PTR(evt_bg))
    END_IF
    SPAWN_EVENT(PTR(evt_hoshi))
    SPAWN_EVENT(PTR(evt_ramp))
    CALL(evt_map_set_tevcallback, 1, PTR(resha_tev))
    SET_INT_READ_ADDR(PTR(pika_tbl))
    CALL(evt_sub_get_mapname, LW(0))
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_0000468C)))
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)rsh_06_str_0000468C)))
#endif
        SET_INT_READ_ADDR(PTR(pika_tbl_rsh_06))
    END_IF
    LOOP(0)
        READ_INT(LW(0))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        CALL(evt_mapobj_flag_onoff, 1, 1, LW(0), 16777216)
        CALL(evt_mapobj_flag_onoff, 1, 0, LW(0), 256)
        CALL(evt_mapobj_flag_onoff, 1, 1, LW(0), 268435456)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(hom_10_evt_resha_right)
    CALL_CHILD(PTR(hom_10_evt_resha_sub))
    CALL(evt_sub_get_mapname, LW(0))
#ifdef NONMATCHING
    IF_STR_NOT_EQUAL(LW(0), STRING(((char*)str_0000468C)))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00004698)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000046A0)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000046A8)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000046B4)), 1)
#endif
#ifndef NONMATCHING
    IF_STR_NOT_EQUAL(LW(0), STRING(((char*)rsh_06_str_0000468C)))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)rsh_06_str_00004698)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)rsh_06_str_000046A0)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)rsh_06_str_000046A8)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)rsh_06_str_000046B4)), 1)
#endif
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(hom_10_evt_resha_left)
    CALL_CHILD(PTR(hom_10_evt_resha_sub))
#ifdef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000046C0)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000046C8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000046D0)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000046DC)), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)rsh_06_str_000046C0)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)rsh_06_str_000046C8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)rsh_06_str_000046D0)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)rsh_06_str_000046DC)), 1)
#endif
    RETURN
EVT_END()

static EVT_BEGIN(hom_10_init_evt)
    CALL(evt_snd_bgmoff, 512)
#ifdef NONMATCHING
    CALL(evt_snd_envon, 272, STRING(((char*)str_000046E8)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_envon, 272, STRING(((char*)rsh_06_str_000046E8)))
#endif
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_party_cont_onoff, 1, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_party_set_pos, 1, 0, -1000, 0)
    IF_INT_EQUAL(GSWF(3578), 0)
        CALL_CHILD(PTR(hom_10_evt_resha_right))
        CALL_CHILD(PTR(hom_10_evt_resha_start3))
        SET_VALUE(LW(0), 500)
        SET_VALUE(LW(1), -500)
#ifdef NONMATCHING
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000046F8)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000046D0)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00004700)), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)rsh_06_str_000046F8)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)rsh_06_str_000046D0)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)rsh_06_str_00004700)), 1)
#endif
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_0000470C)), 1)
#ifdef NONMATCHING
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00004718)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000046DC)), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)rsh_06_str_00004718)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)rsh_06_str_000046DC)), 1)
#endif
        ELSE
        CALL_CHILD(PTR(hom_10_evt_resha_left))
        CALL_CHILD(PTR(hom_10_evt_resha_start4))
        SET_VALUE(LW(0), 0)
        SET_VALUE(LW(1), 1000)
#ifdef NONMATCHING
        CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004550)), -1500, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_mapobj_trans, 1, STRING(((char*)rsh_06_str_00004550)), -1500, 0, 0)
#endif
    END_IF
    CALL(evt_cam_letter_box_onoff, 1, 1)
    CALL(evt_cam3d_evt_set, LW(0), 300, 1400, LW(0), 125, 0, 0, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_seq_wait, 2)
        CALL(evt_cam3d_evt_set, LW(1), 300, 1400, LW(1), 125, 0, 8000, 0)
        WAIT_MS(4000)
#ifdef NONMATCHING
        CALL(evt_bero_mapchange, STRING(((char*)str_00004724)), STRING(((char*)str_00004730)))
#endif
#ifndef NONMATCHING
        CALL(evt_bero_mapchange, STRING(((char*)rsh_06_str_00004724)), STRING(((char*)rsh_06_str_00004730)))
#endif
    END_INLINE_EVENT
    RETURN
EVT_END()

EVT_BEGIN(evt_resha_init)
    CALL_CHILD(PTR(hom_10_evt_resha_right))
    SET_VALUE(GSWF(3583), 1)
    SET_VALUE(GW(0), FLOAT(-15.0f))
    SET_VALUE(GW(1), FLOAT(-15.0f))
    RETURN
EVT_END()

static s32 bero_data_a[] = {
#ifdef NONMATCHING
    (s32)((char*)str_00004738), 8, 2, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)str_00004740), (s32)((char*)str_00004738), 65537, 0, 0, 0,
#endif
#ifndef NONMATCHING
    (s32)((char*)rsh_06_str_00004738), 8, 2, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)rsh_06_str_00004740), (s32)((char*)rsh_06_str_00004738), 65537, 0, 0, 0,
#endif
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static EVT_BEGIN(evt_moamoa_init)
#ifdef NONMATCHING
    CALL(evt_npc_entry, STRING(((char*)str_0000474C)), STRING(((char*)str_000041D0)))
    CALL(evt_npc_entry, STRING(((char*)str_00004754)), STRING(((char*)str_000041E4)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_entry, STRING(((char*)str_0000474C)), STRING(((char*)rsh_06_str_000041D0)))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_00004754)), STRING(((char*)rsh_06_str_000041E4)))
#endif
    CALL(evt_npc_set_position, STRING(((char*)str_0000474C)), 0, -1000, 0)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_00004754)), 0, -1000, 0)
    CALL(evt_npc_entry, STRING(((char*)str_0000475C)), STRING(((char*)str_000041F0)))
    CALL(evt_npc_entry, STRING(((char*)str_00004764)), STRING(((char*)str_00004200)))
    CALL(evt_npc_entry, STRING(((char*)str_0000476C)), STRING(((char*)str_00004210)))
    CALL(evt_npc_entry, STRING(((char*)str_00004774)), STRING(((char*)str_0000421C)))
    CALL(evt_npc_entry, STRING(((char*)str_0000477C)), STRING(((char*)str_00004228)))
    CALL(evt_npc_entry, STRING(((char*)str_00004784)), STRING(((char*)str_00004230)))
    CALL(evt_npc_entry, STRING(((char*)str_0000478C)), STRING(((char*)str_00004238)))
    CALL(evt_npc_entry, STRING(((char*)str_00004794)), STRING(((char*)str_00004240)))
    CALL(evt_npc_set_position, STRING(((char*)str_0000475C)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00004764)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_0000476C)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00004774)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_0000477C)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00004784)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_0000478C)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00004794)), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_0000475C)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00004764)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_0000476C)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00004774)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_0000477C)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00004784)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_0000478C)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00004794)), 2048)
    CALL(evt_snd_sfxon, STRING(((char*)str_0000479C)), GW(2))
    CALL(evt_npc_entry, STRING(((char*)str_000047B4)), STRING(((char*)str_000047BC)))
    CALL(evt_npc_set_position, STRING(((char*)str_000047B4)), 0, -1000, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_00004754)), 0, -1000, 0)
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_0000475C)), STRING(((char*)rsh_06_str_000041F0)))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_00004764)), STRING(((char*)rsh_06_str_00004200)))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_0000476C)), STRING(((char*)rsh_06_str_00004210)))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_00004774)), STRING(((char*)rsh_06_str_0000421C)))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_0000477C)), STRING(((char*)rsh_06_str_00004228)))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_00004784)), STRING(((char*)rsh_06_str_00004230)))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_0000478C)), STRING(((char*)rsh_06_str_00004238)))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_00004794)), STRING(((char*)rsh_06_str_00004240)))
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_0000475C)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_00004764)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_0000476C)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_00004774)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_0000477C)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_00004784)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_0000478C)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_00004794)), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_06_str_0000475C)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_06_str_00004764)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_06_str_0000476C)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_06_str_00004774)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_06_str_0000477C)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_06_str_00004784)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_06_str_0000478C)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_06_str_00004794)), 2048)
    CALL(evt_snd_sfxon, STRING(((char*)rsh_06_str_0000479C)), GW(2))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_000047B4)), STRING(((char*)rsh_06_str_000047BC)))
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_000047B4)), 0, -1000, 0)
#endif
    CALL(evt_ext_entry, 700, PTR(ext_moamoa_data), PTR(ext_moamoa_init), PTR(ext_moamoa_main), PTR(ext_moamoa_dispent))
    CALL(evt_moamoa_flag_onoff, 1, 1)
    BEGIN_INLINE_EVENT
        LABEL(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_LESS(LW(0), -300)
            WAIT_FRAMES(1)
            GOTO(0)
        END_IF
        CALL_CHILD(PTR(evt_great_moamoa))
    END_INLINE_EVENT
    RETURN
EVT_END()

EVT_BEGIN(evt_great_moamoa)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_moamoa_flag_onoff, 1, 8)
    CALL(evt_moamoa_flag_onoff, 1, 4)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000047C8)), 0, 0)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000047D8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000047E4)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000047F0)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000047FC)), 1)
    CALL(evt_npc_set_position, STRING(((char*)str_000047B4)), 10, 190, 0)
    CALL(evt_npc_pera_onoff, STRING(((char*)str_000047B4)), 0)
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_00004804)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)rsh_06_str_000047C8)), 0, 0)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)rsh_06_str_000047D8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)rsh_06_str_000047E4)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)rsh_06_str_000047F0)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)rsh_06_str_000047FC)), 1)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_000047B4)), 10, 190, 0)
    CALL(evt_npc_pera_onoff, STRING(((char*)rsh_06_str_000047B4)), 0)
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_000047B4)), STRING(((char*)rsh_06_str_00004804)))
#endif
    CALL(evt_snd_sfxoff, GW(2))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_00004808)), GW(2))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)rsh_06_str_00004808)), GW(2))
#endif
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004824)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)rsh_06_str_00004824)), LW(0), LW(1), LW(2), 0)
#endif
        CALL(evt_eff_fukidashi, 0, STRING(((char*)str_0000483C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#ifdef NONMATCHING
        CALL(evt_eff_fukidashi, 3, STRING(((char*)str_00004844)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_eff_fukidashi, 3, STRING(((char*)rsh_06_str_00004844)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#endif
        WAIT_MS(1000)
        CALL(evt_mario_set_dir, 90, 200, 0)
        CALL(evt_party_set_dir, 0, 90, 200)
        WAIT_MS(300)
        CALL(evt_cam3d_evt_set, 10, 349, 516, 10, 253, -25, 3000, 11)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(15)
#ifdef NONMATCHING
            CALL(evt_snd_sfxon, STRING(((char*)str_0000484C)), 0)
#endif
#ifndef NONMATCHING
            CALL(evt_snd_sfxon, STRING(((char*)rsh_06_str_0000484C)), 0)
#endif
            WAIT_MS(500)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_moamoa_fusion)
    CALL(evt_snd_sfxoff, GW(2))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_0000479C)), GW(2))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00004868)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000047D8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000047E4)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000047F0)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000047FC)), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)rsh_06_str_0000479C)), GW(2))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)rsh_06_str_00004868)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)rsh_06_str_000047D8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)rsh_06_str_000047E4)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)rsh_06_str_000047F0)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)rsh_06_str_000047FC)), 1)
#endif
    WAIT_MS(2000)
    CALL(evt_moamoa_kind_onoff, 1, 0)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_get_position, STRING(((char*)str_000047B4)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004874)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_get_position, STRING(((char*)rsh_06_str_000047B4)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)rsh_06_str_00004874)), LW(0), LW(1), LW(2), 0)
#endif
        WAIT_MS(800)
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004874)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)rsh_06_str_00004874)), LW(0), LW(1), LW(2), 0)
#endif
        WAIT_MS(800)
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004874)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)rsh_06_str_00004874)), LW(0), LW(1), LW(2), 0)
#endif
        WAIT_MS(800)
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004874)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)rsh_06_str_00004874)), LW(0), LW(1), LW(2), 0)
#endif
    END_INLINE_EVENT
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_0000488C)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_000047B4)), STRING(((char*)rsh_06_str_0000488C)))
#endif
    CALL(npc_anim_wait)
    CALL(evt_cam3d_evt_set, 10, 335, 369, 10, 265, -25, 1000, 11)
    CALL(evt_moamoa_kind_onoff, 1, 1)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_get_position, STRING(((char*)str_000047B4)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004890)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_get_position, STRING(((char*)rsh_06_str_000047B4)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)rsh_06_str_00004890)), LW(0), LW(1), LW(2), 0)
#endif
    END_INLINE_EVENT
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_0000420C)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_000047B4)), STRING(((char*)rsh_06_str_0000420C)))
#endif
    WAIT_MS(2000)
    BEGIN_INLINE_EVENT
        WAIT_MS(1700)
#ifdef NONMATCHING
        CALL(evt_npc_get_position, STRING(((char*)str_000047B4)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000048A8)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_get_position, STRING(((char*)rsh_06_str_000047B4)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)rsh_06_str_000048A8)), LW(0), LW(1), LW(2), 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_cam3d_evt_set, 10, 300, 450, 10, 300, -25, 1000, 11)
    END_INLINE_EVENT
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_000048C0)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_000047B4)), STRING(((char*)rsh_06_str_000048C0)))
#endif
    CALL(npc_anim_wait)
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_000048C4)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_000047B4)), STRING(((char*)rsh_06_str_000048C4)))
#endif
    WAIT_MS(1000)
    CALL(evt_mario_set_pos, -160, 215, 0)
    CALL(evt_party_set_pos, 0, -200, 215, -10)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_set_dir, 0, 90, 0)
    CALL(evt_mario_dispflag_onoff, 1, 2)
#ifdef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)str_000048C8)))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)rsh_06_str_000048C8)))
#endif
    CALL(evt_cam3d_evt_set, -180, 308, 270, -180, 255, -25, 0, 11)
    WAIT_MS(500)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)str_000048D0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)rsh_06_str_000048D0)))
#endif
    WAIT_MS(300)
    CALL(evt_party_run, 0)
    CALL(evt_cam3d_evt_set, 10, 498, 467, 10, 410, -25, 0, 11)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000048E0)), 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)rsh_06_str_000048E0)), 0, 0)
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000048F0)), 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)rsh_06_str_000048F0)), 0, 0)
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 1000, 20, 841, -50, 200, -66, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_cam3d_evt_set, -440, 230, 180, 5, 300, -36, 4000, 11)
    WAIT_MS(4000)
    WAIT_MS(500)
#ifdef NONMATCHING
    CALL(evt_npc_get_position, STRING(((char*)str_000047B4)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004900)), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_00004918)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_get_position, STRING(((char*)rsh_06_str_000047B4)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)rsh_06_str_00004900)), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_000047B4)), STRING(((char*)rsh_06_str_00004918)))
#endif
    CALL(npc_anim_wait)
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_0000491C)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_000047B4)), STRING(((char*)rsh_06_str_0000491C)))
#endif
    WAIT_MS(500)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00004920)), 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)rsh_06_str_00004920)), 0, 0)
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -100, 488, 1370, -100, 245, -8, 4000, 11)
    WAIT_MS(2000)
    CALL(evt_snd_sfxoff, GW(2))
#ifdef NONMATCHING
    CALL(evt_npc_set_battle_info, STRING(((char*)str_000047B4)), 1)
    CALL(evt_npc_battle_start, STRING(((char*)str_000047B4)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_battle_info, STRING(((char*)rsh_06_str_000047B4)), 1)
    CALL(evt_npc_battle_start, STRING(((char*)rsh_06_str_000047B4)))
#endif
    CALL(evt_npc_wait_battle_end)
    CALL(evt_cam3d_evt_set, -50, 355, 534, -50, 260, -8, 0, 11)
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_00004804)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_000047B4)), STRING(((char*)rsh_06_str_00004804)))
#endif
    CALL(evt_mario_dispflag_onoff, 0, 2)
#ifdef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)str_00004930)))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)rsh_06_str_00004930)))
#endif
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), -25)
    CALL(evt_party_set_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_0000475C)), 2048)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00004764)), 2048)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_0000476C)), 2048)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00004774)), 2048)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_0000477C)), 2048)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00004784)), 2048)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_0000478C)), 2048)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00004794)), 2048)
    CALL(evt_npc_set_position, STRING(((char*)str_0000475C)), 0, 215, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00004764)), 0, 215, 1)
    CALL(evt_npc_set_position, STRING(((char*)str_00004774)), 0, 215, 2)
    CALL(evt_npc_set_position, STRING(((char*)str_0000477C)), 0, 215, 3)
    CALL(evt_npc_set_position, STRING(((char*)str_00004784)), 0, 215, 4)
    CALL(evt_npc_set_position, STRING(((char*)str_0000478C)), 0, 215, 5)
    CALL(evt_npc_set_position, STRING(((char*)str_00004794)), 0, 215, 6)
    CALL(evt_npc_set_position, STRING(((char*)str_0000476C)), 20, 215, 7)
    CALL(evt_npc_set_ry, STRING(((char*)str_0000475C)), 270)
    CALL(evt_npc_set_ry, STRING(((char*)str_00004764)), 270)
    CALL(evt_npc_set_ry, STRING(((char*)str_00004774)), 270)
    CALL(evt_npc_set_ry, STRING(((char*)str_0000477C)), 270)
    CALL(evt_npc_set_ry, STRING(((char*)str_00004784)), 270)
    CALL(evt_npc_set_ry, STRING(((char*)str_0000478C)), 270)
    CALL(evt_npc_set_ry, STRING(((char*)str_00004794)), 270)
    CALL(evt_npc_set_ry, STRING(((char*)str_0000476C)), 270)
    CALL(evt_npc_set_anim, STRING(((char*)str_0000475C)), STRING(((char*)str_00004804)))
    CALL(evt_npc_set_anim, STRING(((char*)str_00004764)), STRING(((char*)str_00004804)))
    CALL(evt_npc_set_anim, STRING(((char*)str_00004774)), STRING(((char*)str_00004804)))
    CALL(evt_npc_set_anim, STRING(((char*)str_0000477C)), STRING(((char*)str_00004804)))
    CALL(evt_npc_set_anim, STRING(((char*)str_00004784)), STRING(((char*)str_00004804)))
    CALL(evt_npc_set_anim, STRING(((char*)str_0000478C)), STRING(((char*)str_00004804)))
    CALL(evt_npc_set_anim, STRING(((char*)str_00004794)), STRING(((char*)str_00004804)))
    CALL(evt_npc_set_anim, STRING(((char*)str_0000476C)), STRING(((char*)str_00004804)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)rsh_06_str_0000475C)), 2048)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)rsh_06_str_00004764)), 2048)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)rsh_06_str_0000476C)), 2048)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)rsh_06_str_00004774)), 2048)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)rsh_06_str_0000477C)), 2048)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)rsh_06_str_00004784)), 2048)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)rsh_06_str_0000478C)), 2048)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)rsh_06_str_00004794)), 2048)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_0000475C)), 0, 215, 0)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_00004764)), 0, 215, 1)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_00004774)), 0, 215, 2)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_0000477C)), 0, 215, 3)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_00004784)), 0, 215, 4)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_0000478C)), 0, 215, 5)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_00004794)), 0, 215, 6)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_0000476C)), 20, 215, 7)
    CALL(evt_npc_set_ry, STRING(((char*)rsh_06_str_0000475C)), 270)
    CALL(evt_npc_set_ry, STRING(((char*)rsh_06_str_00004764)), 270)
    CALL(evt_npc_set_ry, STRING(((char*)rsh_06_str_00004774)), 270)
    CALL(evt_npc_set_ry, STRING(((char*)rsh_06_str_0000477C)), 270)
    CALL(evt_npc_set_ry, STRING(((char*)rsh_06_str_00004784)), 270)
    CALL(evt_npc_set_ry, STRING(((char*)rsh_06_str_0000478C)), 270)
    CALL(evt_npc_set_ry, STRING(((char*)rsh_06_str_00004794)), 270)
    CALL(evt_npc_set_ry, STRING(((char*)rsh_06_str_0000476C)), 270)
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_0000475C)), STRING(((char*)rsh_06_str_00004804)))
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_00004764)), STRING(((char*)rsh_06_str_00004804)))
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_00004774)), STRING(((char*)rsh_06_str_00004804)))
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_0000477C)), STRING(((char*)rsh_06_str_00004804)))
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_00004784)), STRING(((char*)rsh_06_str_00004804)))
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_0000478C)), STRING(((char*)rsh_06_str_00004804)))
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_00004794)), STRING(((char*)rsh_06_str_00004804)))
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_0000476C)), STRING(((char*)rsh_06_str_00004804)))
#endif
    CALL(evt_moamoa_kind_onoff, 0, 0)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00004938)), 0, STRING(((char*)str_000047B4)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)rsh_06_str_00004938)), 0, STRING(((char*)rsh_06_str_000047B4)))
#endif
    WAIT_MS(500)
#ifdef NONMATCHING
    CALL(evt_npc_get_position, STRING(((char*)str_000047B4)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004948)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_get_position, STRING(((char*)rsh_06_str_000047B4)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)rsh_06_str_00004948)), LW(0), LW(1), LW(2), 0)
#endif
    CALL(evt_moamoa_blow)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set, -150, 485, 1469, -150, 225, -8, 4000, 11)
    WAIT_MS(4000)
    BEGIN_INLINE_EVENT
        LOOP(0)
#ifdef NONMATCHING
            CALL(evt_npc_reverse_ry, STRING(((char*)str_0000476C)))
#endif
#ifndef NONMATCHING
            CALL(evt_npc_reverse_ry, STRING(((char*)rsh_06_str_0000476C)))
#endif
            WAIT_MS(1500)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
#ifdef NONMATCHING
            CALL(evt_npc_reverse_ry, STRING(((char*)str_00004794)))
#endif
#ifndef NONMATCHING
            CALL(evt_npc_reverse_ry, STRING(((char*)rsh_06_str_00004794)))
#endif
            WAIT_MS(1000)
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(2000)
    SET_VALUE(GSW(0), 332)
#ifdef NONMATCHING
    CALL(evt_bero_mapchange, STRING(((char*)str_00004964)), STRING(((char*)str_00004738)))
#endif
#ifndef NONMATCHING
    CALL(evt_bero_mapchange, STRING(((char*)rsh_06_str_00004964)), STRING(((char*)rsh_06_str_00004738)))
#endif
    RETURN
EVT_END()

__declspec(section ".data") s32 pose_name[] = {
#ifdef NONMATCHING
    (s32)((char*)str_00004804), (s32)((char*)str_0000488C), (s32)((char*)str_000041DC), (s32)((char*)str_0000420C), (s32)((char*)str_000048C0), (s32)((char*)str_000048C4), (s32)((char*)str_00004918), (s32)((char*)str_0000491C),
#endif
#ifndef NONMATCHING
    (s32)((char*)rsh_06_str_00004804), (s32)((char*)rsh_06_str_0000488C), (s32)((char*)rsh_06_str_000041DC), (s32)((char*)rsh_06_str_0000420C), (s32)((char*)rsh_06_str_000048C0), (s32)((char*)rsh_06_str_000048C4), (s32)((char*)rsh_06_str_00004918), (s32)((char*)rsh_06_str_0000491C),
#endif
};

EVT_BEGIN(moamoa_debug)
#ifdef NONMATCHING
    CALL(evt_npc_entry, STRING(((char*)str_0000474C)), STRING(((char*)str_000041D0)))
    CALL(evt_npc_entry, STRING(((char*)str_00004754)), STRING(((char*)str_000041E4)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_entry, STRING(((char*)str_0000474C)), STRING(((char*)rsh_06_str_000041D0)))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_00004754)), STRING(((char*)rsh_06_str_000041E4)))
#endif
    CALL(evt_npc_set_position, STRING(((char*)str_0000474C)), 0, -1000, 0)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_00004754)), 0, -1000, 0)
    CALL(evt_npc_entry, STRING(((char*)str_0000475C)), STRING(((char*)str_000041F0)))
    CALL(evt_npc_entry, STRING(((char*)str_00004764)), STRING(((char*)str_00004200)))
    CALL(evt_npc_entry, STRING(((char*)str_0000476C)), STRING(((char*)str_00004210)))
    CALL(evt_npc_entry, STRING(((char*)str_00004774)), STRING(((char*)str_0000421C)))
    CALL(evt_npc_entry, STRING(((char*)str_0000477C)), STRING(((char*)str_00004228)))
    CALL(evt_npc_entry, STRING(((char*)str_00004784)), STRING(((char*)str_00004230)))
    CALL(evt_npc_entry, STRING(((char*)str_0000478C)), STRING(((char*)str_00004238)))
    CALL(evt_npc_entry, STRING(((char*)str_00004794)), STRING(((char*)str_00004240)))
    CALL(evt_npc_set_position, STRING(((char*)str_0000475C)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00004764)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_0000476C)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00004774)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_0000477C)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00004784)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_0000478C)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00004794)), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_0000475C)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00004764)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_0000476C)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00004774)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_0000477C)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00004784)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_0000478C)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00004794)), 2048)
    CALL(evt_npc_entry, STRING(((char*)str_000047B4)), STRING(((char*)str_000047BC)))
    CALL(evt_npc_set_position, STRING(((char*)str_000047B4)), 0, -1000, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_00004754)), 0, -1000, 0)
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_0000475C)), STRING(((char*)rsh_06_str_000041F0)))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_00004764)), STRING(((char*)rsh_06_str_00004200)))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_0000476C)), STRING(((char*)rsh_06_str_00004210)))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_00004774)), STRING(((char*)rsh_06_str_0000421C)))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_0000477C)), STRING(((char*)rsh_06_str_00004228)))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_00004784)), STRING(((char*)rsh_06_str_00004230)))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_0000478C)), STRING(((char*)rsh_06_str_00004238)))
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_00004794)), STRING(((char*)rsh_06_str_00004240)))
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_0000475C)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_00004764)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_0000476C)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_00004774)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_0000477C)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_00004784)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_0000478C)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_00004794)), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_06_str_0000475C)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_06_str_00004764)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_06_str_0000476C)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_06_str_00004774)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_06_str_0000477C)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_06_str_00004784)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_06_str_0000478C)), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)rsh_06_str_00004794)), 2048)
    CALL(evt_npc_entry, STRING(((char*)rsh_06_str_000047B4)), STRING(((char*)rsh_06_str_000047BC)))
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_000047B4)), 0, -1000, 0)
#endif
    CALL(evt_ext_entry, 700, PTR(ext_moamoa_data), PTR(ext_moamoa_init), PTR(ext_moamoa_main), PTR(ext_moamoa_dispent))
    CALL(evt_moamoa_flag_onoff, 1, 1)
    CALL(evt_moamoa_flag_onoff, 1, 4)
    CALL(evt_moamoa_fusion_debug)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_000047B4)), 10, 190, 0)
    CALL(evt_npc_pera_onoff, STRING(((char*)str_000047B4)), 0)
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_000048C4)))
    CALL(evt_npc_set_scale, STRING(((char*)str_000047B4)), FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)rsh_06_str_000047B4)), 10, 190, 0)
    CALL(evt_npc_pera_onoff, STRING(((char*)rsh_06_str_000047B4)), 0)
    CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_000047B4)), STRING(((char*)rsh_06_str_000048C4)))
    CALL(evt_npc_set_scale, STRING(((char*)rsh_06_str_000047B4)), FLOAT((1.0f)), FLOAT((1.0f)), FLOAT((1.0f)))
#endif
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), 0)
        LOOP(0)
            CALL(evt_key_get_buttontrg, 0, LW(10))
            IF_BITS_SET(LW(10), 256)
                ADD(LW(0), 1)
                MODULO(LW(0), 8)
                SET_VALUE(LW(1), LW(0))
                ADD(LW(1), 1)
                SET_INT_READ_ADDR(PTR(pose_name))
                LOOP(LW(1))
                    READ_INT(LW(2))
                END_LOOP
#ifdef NONMATCHING
                CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), LW(2))
#endif
#ifndef NONMATCHING
                CALL(evt_npc_set_anim, STRING(((char*)rsh_06_str_000047B4)), LW(2))
#endif
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    RETURN
EVT_END()

EVT_BEGIN(rsh_06_init_evt)
    CALL_CHILD(PTR(evt_resha_init))
    SWITCH(GSW(0))
        CASE_BETWEEN(284, 286)
#ifdef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004970)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)rsh_06_str_00004970)))
#endif
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004980)))
        CASE_BETWEEN(304, 309)
#ifdef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004970)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)rsh_06_str_00004970)))
#endif
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004980)))
        CASE_BETWEEN(310, 325)
#ifdef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004990)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)rsh_06_str_00004990)))
#endif
        CALL(evt_snd_envoff, 512)
        CALL(evt_snd_bgmoff, 26624)
        CASE_BETWEEN(327, 328)
        CALL(evt_snd_bgmoff, 512)
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004980)))
        CASE_BETWEEN(329, 331)
#ifdef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_000049A0)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)rsh_06_str_000049A0)))
#endif
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004980)))
        CASE_BETWEEN(334, 344)
#ifdef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_000049B0)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)rsh_06_str_000049B0)))
#endif
        CALL(evt_snd_envoff, 512)
        CALL(evt_snd_bgmoff, 26624)
        CASE_DEFAULT
        CALL(evt_snd_bgmoff, 512)
#ifdef NONMATCHING
        CALL(evt_snd_envon, 272, STRING(((char*)str_000046E8)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_envon, 272, STRING(((char*)rsh_06_str_000046E8)))
#endif
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(rsh_06_a_init_evt)
    CALL(evt_mario_set_pos, -500, 250, 0)
    SET_VALUE(LW(0), PTR(bero_data_a))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(rsh_06_init_evt))
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_SET(LW(0), 2)
        SPAWN_EVENT(PTR(moamoa_debug))
        RETURN
    END_IF
    IF_INT_LESS(GSW(0), 332)
        CALL_CHILD(PTR(evt_moamoa_init))
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(rsh_06_init_evt_nidome)
    CALL_CHILD(PTR(evt_resha_init))
    IF_INT_EQUAL(GSWF(3460), 1)
#ifdef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_000049B0)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)rsh_06_str_000049B0)))
#endif
        CALL(evt_snd_envoff, 512)
        CALL(evt_snd_bgmoff, 26624)
        ELSE
        IF_INT_EQUAL(GSWF(3461), 1)
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_000049C0)))
            CALL(evt_snd_envoff, 512)
            CALL(evt_snd_bgmoff, 26624)
            ELSE
            CALL(evt_snd_bgmoff, 512)
#ifdef NONMATCHING
            CALL(evt_snd_envon, 272, STRING(((char*)str_000046E8)))
#endif
#ifndef NONMATCHING
            CALL(evt_snd_envon, 272, STRING(((char*)rsh_06_str_000046E8)))
#endif
        END_IF
    END_IF
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(rsh_06_a_init_evt_nidome)
    SET_VALUE(LW(0), PTR(bero_data_a))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(rsh_06_init_evt_nidome))
    RETURN
EVT_END()




#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
static s32 ramp_r(EventEntry* event, BOOL isFirstCall) {
#ifdef NONMATCHING
    f32 amp = __fabsf(evtGetFloat(event, GW(0)));
    f32 wave = sin(gp->retraceCount / float_15_rsh_00014474[0]);

    evtSetFloat(event, LW(10), float_1p8_rsh_00014478[0] * amp * wave);
    return EVT_RETURN_DONE;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0xDBE10020
		opword 0xF3E10028
		opword 0x93E1001C
		opword 0x3C80FD05
		opword 0x7C7F1B78
		opword 0x38840F80
		bl evtGetFloat
		lis r3, gp@ha
		opword 0x3C004330
		addi r4, r3, gp@l
		opword 0x90010008
		opword 0x80A40000
		lis r3, double_to_int_mask_rsh_00014480@ha
		addi r4, r3, double_to_int_mask_rsh_00014480@l
		opword 0xFFE00A10
		opword 0x8005001C
		lis r3, float_15_rsh_00014474@ha
		opword 0xC8440000
		opword 0x9001000C
		lfs f0, float_15_rsh_00014474@l(r3)
		opword 0xC8210008
		opword 0xEC211028
		opword 0xEC210024
		bl sin
		lis r3, float_1p8_rsh_00014478@ha
		opword 0x3C80FE36
		lfs f0, float_1p8_rsh_00014478@l(r3)
		opword 0xFC200818
		opword 0x7FE3FB78
		opword 0x38843C8A
		opword 0xEC0007F2
		opword 0xEC200072
		bl evtSetFloat
		opword 0x38600002
		opword 0xE3E10028
		opword 0x80010034
		opword 0xCBE10020
		opword 0x83E1001C
		opword 0x7C0803A6
		opword 0x38210030
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif
static void resha_tev(MapTevCallbackInfo* info) {
    envAddTev(7, info);
}
s32 npc_anim_wait(EventEntry* event, BOOL isFirstCall) {
#ifdef NONMATCHING
    NpcEntry* npc = npcNameToPtr((char*)str_000047B4);
#endif
#ifndef NONMATCHING
    NpcEntry* npc = npcNameToPtr((char*)rsh_06_str_000047B4);
#endif

    if (animPoseGetLoopTimes(npc->poseId) >= float_1_rsh_00014470[0]) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

void __cvt_ull_flt();
void __div2u();

#ifndef NONMATCHING

// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const char rsh_06_str_000041D0[12] = "c_n_moa_a\0\0";
__declspec(section ".rodata") const char rsh_06_str_000041DC[4] = "S_1";
__declspec(section ".rodata") const char rsh_06_str_000041E0[4] = "D_1";
__declspec(section ".rodata") const char rsh_06_str_000041E4[12] = "c_n_moa_b\0\0";
__declspec(section ".rodata") const char rsh_06_str_000041F0[12] = "c_kinodebu\0";
__declspec(section ".rodata") const char rsh_06_str_000041FC[4] = "G_1";
__declspec(section ".rodata") const char rsh_06_str_00004200[12] = "c_puku_c\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_0000420C[4] = "U_1";
__declspec(section ".rodata") const char rsh_06_str_00004210[8] = "c_powan";
__declspec(section ".rodata") const char rsh_06_str_00004218[4] = "O_1";
__declspec(section ".rodata") const char rsh_06_str_0000421C[8] = "c_smoko";
__declspec(section ".rodata") const char rsh_06_str_00004224[4] = "T_2";
__declspec(section ".rodata") const char rsh_06_str_00004228[8] = "c_rose\0";
__declspec(section ".rodata") const char rsh_06_str_00004230[8] = "c_papab";
__declspec(section ".rodata") const char rsh_06_str_00004238[8] = "c_mamab";
__declspec(section ".rodata") const char rsh_06_str_00004240[12] = "c_konari\0\0\0";
__declspec(section ".rodata") const f32 vec3_rsh_00013cec[3] = {0.0f, -1000.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013cf8[3] = {10.0f, 215.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013d04[3] = {10.0f, 215.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013d10[3] = {10.0f, 215.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013d1c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013d28[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013d34[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013d40[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013d4c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013d58[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013d64[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013d70[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013d7c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013d88[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013d94[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_rsh_00013da0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const char rsh_06_str_0000430C[8] = "sha_1_1";
__declspec(section ".rodata") const char rsh_06_str_00004314[8] = "sha_1_2";
__declspec(section ".rodata") const char rsh_06_str_0000431C[8] = "sha_1_3";
__declspec(section ".rodata") const char rsh_06_str_00004324[8] = "sha_1_4";
__declspec(section ".rodata") const char rsh_06_str_0000432C[8] = "sha_1_5";
__declspec(section ".rodata") const char str_00004334[8] = "sha_2_1";
__declspec(section ".rodata") const char rsh_06_str_0000433C[8] = "sha_2_2";
__declspec(section ".rodata") const char rsh_06_str_00004344[8] = "sha_2_3";
__declspec(section ".rodata") const char rsh_06_str_0000434C[8] = "sha_3_1";
__declspec(section ".rodata") const char rsh_06_str_00004354[8] = "sha_3_2";
__declspec(section ".rodata") const char rsh_06_str_0000435C[8] = "sha_3_3";
__declspec(section ".rodata") const char rsh_06_str_00004364[8] = "sha_4_1";
__declspec(section ".rodata") const char rsh_06_str_0000436C[8] = "sha_4_2";
__declspec(section ".rodata") const char rsh_06_str_00004374[8] = "sha_4_3";
__declspec(section ".rodata") const char rsh_06_str_0000437C[8] = "sha_5_1";
__declspec(section ".rodata") const char str_00004384[8] = "sha_5_2";
__declspec(section ".rodata") const char rsh_06_str_0000438C[8] = "sha_5_3";
__declspec(section ".rodata") const char rsh_06_str_00004394[8] = "sha_6_1";
__declspec(section ".rodata") const char rsh_06_str_0000439C[8] = "sha_6_2";
__declspec(section ".rodata") const char rsh_06_str_000043A4[8] = "sha_6_3";
__declspec(section ".rodata") const char rsh_06_str_000043AC[12] = "sha_1_1_c\0\0";
__declspec(section ".rodata") const char rsh_06_str_000043B8[12] = "sha_1_2_c\0\0";
__declspec(section ".rodata") const char rsh_06_str_000043C4[12] = "sha_1_3_c\0\0";
__declspec(section ".rodata") const char rsh_06_str_000043D0[12] = "sha_1_4_c\0\0";
__declspec(section ".rodata") const char rsh_06_str_000043DC[12] = "sha_1_5_c\0\0";
__declspec(section ".rodata") const char rsh_06_str_000043E8[12] = "sha_6_1_c\0\0";
__declspec(section ".rodata") const char str_000043F4[12] = "sha_6_2_c\0\0";
__declspec(section ".rodata") const char str_00004400[12] = "sha_6_3_c\0\0";
__declspec(section ".rodata") const char rsh_06_str_0000440C[8] = "bou_1\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004414[8] = "bou_2\0\0";
__declspec(section ".rodata") const char rsh_06_str_0000441C[8] = "bou_3\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004424[8] = "bou_4\0\0";
__declspec(section ".rodata") const char rsh_06_str_0000442C[8] = "bou_1_c";
__declspec(section ".rodata") const char rsh_06_str_00004434[8] = "bou_2_c";
__declspec(section ".rodata") const char rsh_06_str_0000443C[8] = "bou_3_c";
__declspec(section ".rodata") const char rsh_06_str_00004444[8] = "bou_4_c";
__declspec(section ".rodata") const char rsh_06_str_0000444C[8] = "jimen\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004454[8] = "yama\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_0000445C[8] = "iwayama";
__declspec(section ".rodata") const char rsh_06_str_00004464[12] = "hosi_right\0";
__declspec(section ".rodata") const char rsh_06_str_00004470[12] = "hosi_left\0\0";
__declspec(section ".rodata") const char rsh_06_str_0000447C[12] = "hosi_center";
__declspec(section ".rodata") const char str_00004488[16] = "hosi_right_c\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004498[12] = "hosi_left_c";
__declspec(section ".rodata") const char rsh_06_str_000044A4[16] = "hosi_center_c\0\0";
__declspec(section ".rodata") const char rsh_06_str_000044B4[8] = "ranpu\0\0";
__declspec(section ".rodata") const char rsh_06_str_000044BC[24] = "SFX_STG6_TRAIN_BELL1\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_000044D4[8] = "gor_04\0";
__declspec(section ".rodata") const char rsh_06_str_000044DC[24] = "SFX_STG6_TRAIN_MOVE1\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_000044F4[8] = "hom_00\0";
__declspec(section ".rodata") const char rsh_06_str_000044FC[24] = "SFX_STG6_TRAIN_MOVE1_2\0";
__declspec(section ".rodata") const char rsh_06_str_00004514[28] = "SFX_STG6_TRAIN_MOVE1_2_2\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004530[8] = "pik_00\0";
__declspec(section ".rodata") const char rsh_06_str_00004538[24] = "SFX_STG6_TRAIN_MOVE1_3\0";
__declspec(section ".rodata") const char rsh_06_str_00004550[8] = "train\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004558[28] = "SFX_STG6_TRAIN_MOVE1_2_3\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004574[24] = "SFX_STG6_TRAIN_MOVE2\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_0000458C[24] = "SFX_STG6_TRAIN_MOVE2_2\0";
__declspec(section ".rodata") const char rsh_06_str_000045A4[24] = "SFX_STG6_TRAIN_MOVE2_3\0";
__declspec(section ".rodata") const char str_000045BC[28] = "SFX_STG6_TRAIN_MOVE2_2_2\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_000045D8[8] = "ranpu_c";
__declspec(section ".rodata") const char str_000045E0[12] = "pika_1_1\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_000045EC[12] = "pika_1_2\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_000045F8[12] = "pika_1_3\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004604[12] = "pika_1_4\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004610[8] = "pika_2\0";
__declspec(section ".rodata") const char rsh_06_str_00004618[8] = "pika_3\0";
__declspec(section ".rodata") const char rsh_06_str_00004620[8] = "pika_4\0";
__declspec(section ".rodata") const char rsh_06_str_00004628[8] = "pika_5\0";
__declspec(section ".rodata") const char rsh_06_str_00004630[8] = "pika_6\0";
__declspec(section ".rodata") const char rsh_06_str_00004638[12] = "pika_1_1_c\0";
__declspec(section ".rodata") const char rsh_06_str_00004644[12] = "pika_1_2_c\0";
__declspec(section ".rodata") const char rsh_06_str_00004650[12] = "pika_1_3_c\0";
__declspec(section ".rodata") const char str_0000465C[12] = "pika_1_4_c\0";
__declspec(section ".rodata") const char rsh_06_str_00004668[12] = "pika_6_c\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004674[8] = "hom_10\0";
__declspec(section ".rodata") const char rsh_06_str_0000467C[8] = "hom_11\0";
__declspec(section ".rodata") const char rsh_06_str_00004684[8] = "hom_12\0";
__declspec(section ".rodata") const char rsh_06_str_0000468C[12] = "rsh_06_a\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004698[8] = "train_7";
__declspec(section ".rodata") const char rsh_06_str_000046A0[8] = "train_8";
__declspec(section ".rodata") const char rsh_06_str_000046A8[12] = "renketu_6\0\0";
__declspec(section ".rodata") const char rsh_06_str_000046B4[12] = "renketu_7\0\0";
__declspec(section ".rodata") const char rsh_06_str_000046C0[8] = "train_1";
__declspec(section ".rodata") const char rsh_06_str_000046C8[8] = "train_6";
__declspec(section ".rodata") const char rsh_06_str_000046D0[12] = "renketu_1\0\0";
__declspec(section ".rodata") const char rsh_06_str_000046DC[12] = "renketu_5\0\0";
__declspec(section ".rodata") const char rsh_06_str_000046E8[16] = "ENV_STG6_RSH2\0\0";
__declspec(section ".rodata") const char rsh_06_str_000046F8[8] = "renketu";
__declspec(section ".rodata") const char rsh_06_str_00004700[12] = "renketu_2\0\0";
__declspec(section ".rodata") const char str_0000470C[12] = "renketu_3\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004718[12] = "renketu_4\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004724[12] = "rsh_02_a\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004730[8] = "nidome\0";
__declspec(section ".rodata") const char rsh_06_str_00004738[8] = "w_bero\0";
__declspec(section ".rodata") const char rsh_06_str_00004740[12] = "rsh_05_a\0\0\0";
__declspec(section ".rodata") const char str_0000474C[8] = "moa_a\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004754[8] = "moa_b\0\0";
__declspec(section ".rodata") const char rsh_06_str_0000475C[8] = "kinopio";
__declspec(section ".rodata") const char rsh_06_str_00004764[8] = "cook\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_0000476C[8] = "powan\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004774[8] = "sarary\0";
__declspec(section ".rodata") const char rsh_06_str_0000477C[8] = "rose\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004784[8] = "papa\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_0000478C[8] = "mama\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004794[8] = "konari\0";
__declspec(section ".rodata") const char rsh_06_str_0000479C[24] = "SFX_STG6_MOAMOA_VOICE2\0";
__declspec(section ".rodata") const char rsh_06_str_000047B4[8] = "base\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_000047BC[12] = "c_g_moamoa\0";
__declspec(section ".rodata") const char rsh_06_str_000047C8[16] = "stg6_rsh_244\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_000047D8[12] = "group339\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_000047E4[12] = "group340\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_000047F0[12] = "group341\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_000047FC[8] = "senro\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004804[4] = "Z_1";
__declspec(section ".rodata") const char rsh_06_str_00004808[28] = "SFX_STG6_MOA_TOGETHER_MOVE1";
__declspec(section ".rodata") const char rsh_06_str_00004824[24] = "SFX_VOICE_MARIO_FIND1_3";
__declspec(section ".rodata") const char str_0000483C[8] = "eff0\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004844[8] = "eff1\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_0000484C[28] = "SFX_STG6_MOA_TOGETHER_MOVE2";
__declspec(section ".rodata") const char rsh_06_str_00004868[12] = "group166\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004874[24] = "SFX_STG6_MOAMOA_G_LEG1\0";
__declspec(section ".rodata") const char rsh_06_str_0000488C[4] = "H_1";
__declspec(section ".rodata") const char rsh_06_str_00004890[24] = "SFX_STG6_MOAMOA_G_LEG2\0";
__declspec(section ".rodata") const char rsh_06_str_000048A8[24] = "SFX_STG6_MOAMOA_G_LEG3\0";
__declspec(section ".rodata") const char rsh_06_str_000048C0[4] = "H_2";
__declspec(section ".rodata") const char rsh_06_str_000048C4[4] = "S_2";
__declspec(section ".rodata") const char rsh_06_str_000048C8[8] = "M_I_Y\0\0";
__declspec(section ".rodata") const char rsh_06_str_000048D0[16] = "stg6_rsh_245\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_000048E0[16] = "stg6_rsh_246_02";
__declspec(section ".rodata") const char rsh_06_str_000048F0[16] = "stg6_rsh_246_03";
__declspec(section ".rodata") const char rsh_06_str_00004900[24] = "SFX_STG6_MOAMOA_G_LEG4\0";
__declspec(section ".rodata") const char rsh_06_str_00004918[4] = "P_1";
__declspec(section ".rodata") const char rsh_06_str_0000491C[4] = "S_3";
__declspec(section ".rodata") const char rsh_06_str_00004920[16] = "stg6_rsh_246_01";
__declspec(section ".rodata") const char rsh_06_str_00004930[8] = "M_S_1\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004938[16] = "stg6_rsh_247\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004948[28] = "SFX_STG6_MOAMOA_G_ESCAPE1\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004964[12] = "rsh_01_a\0\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004970[16] = "BGM_EVT_POWAN1\0";
__declspec(section ".rodata") const char str_00004980[16] = "ENV_STG6_RSH1_3";
__declspec(section ".rodata") const char rsh_06_str_00004990[16] = "BGM_STG6_HOM1\0\0";
__declspec(section ".rodata") const char rsh_06_str_000049A0[16] = "BGM_EVT_DANGER4";
__declspec(section ".rodata") const char rsh_06_str_000049B0[16] = "BGM_STG6_PIK1\0\0";
__declspec(section ".rodata") const char str_000049C0[16] = "BGM_STG0_GOR1\0\0";
__declspec(section ".rodata") const f32 float_1_rsh_00014470[1] = {1.0f};
__declspec(section ".rodata") const f32 float_15_rsh_00014474[1] = {15.0f};
__declspec(section ".rodata") const f32 float_1p8_rsh_00014478[1] = {1.8f};
__declspec(section ".rodata") const f64 double_to_int_mask_rsh_00014480 = 4503599627370496.0;
__declspec(section ".rodata") const f64 double_to_int_rsh_00014488 = 4503601774854144.0;
__declspec(section ".rodata") const f32 zero_rsh_00014490[1] = {0.0f};
__declspec(section ".rodata") const f32 float_neg5000_rsh_00014494 = -5000.0f;
__declspec(section ".rodata") const f32 float_neg1_rsh_00014498 = -1.0f;
__declspec(section ".rodata") const f32 float_6p2832_rsh_0001449c[1] = {6.2831855f};
__declspec(section ".rodata") const f32 float_360_rsh_000144a0[1] = {360.0f};
__declspec(section ".rodata") const f32 float_0p00761_rsh_000144a4 = 0.00761f;
__declspec(section ".rodata") const f32 float_0p16605_rsh_000144a8 = 0.16605f;
__declspec(section ".rodata") const f32 float_3p1416_rsh_000144ac = 3.1415927f;
__declspec(section ".rodata") const f32 float_1p5708_rsh_000144b0 = 1.5707964f;
__declspec(section ".rodata") const f32 float_4p7124_rsh_000144b4 = 4.712389f;
__declspec(section ".rodata") const f32 float_0p03705_rsh_000144b8 = 0.03705f;
__declspec(section ".rodata") const f32 float_0p4967_rsh_000144bc = 0.4967f;
__declspec(section ".rodata") const char rsh_06_str_00004A20[24] = "SFX_STG6_MOAMOA_VOICE1\0";
__declspec(section ".rodata") const f32 float_200_rsh_000144d8[1] = {200.0f};
__declspec(section ".rodata") const f32 float_30_rsh_000144dc[1] = {30.0f};
__declspec(section ".rodata") const char rsh_06_str_00004A40[4] = "D\0\0";
__declspec(section ".rodata") const char rsh_06_str_00004A44[4] = "R\0\0";
__declspec(section ".rodata") const f32 float_0p5_rsh_000144e8[1] = {0.5f};
__declspec(section ".rodata") const f32 float_32767_rsh_000144ec[1] = {32767.0f};
__declspec(section ".rodata") const f32 float_0p1_rsh_000144f0[1] = {0.1f};
__declspec(section ".rodata") const f32 float_0p03_rsh_000144f4[1] = {0.03f};
__declspec(section ".rodata") const f32 float_100_rsh_000144f8[1] = {100.0f};
__declspec(section ".rodata") const f32 float_50_rsh_000144fc[1] = {50.0f};
__declspec(section ".rodata") const f32 float_5_rsh_00014500[1] = {5.0f};
__declspec(section ".rodata") const f32 float_215_rsh_00014504[1] = {215.0f};
__declspec(section ".rodata") const f32 float_0p3_rsh_00014508[1] = {0.3f};
__declspec(section ".rodata") const f32 float_0p2_rsh_0001450c = 0.19999999f;
__declspec(section ".rodata") const f32 float_31_rsh_00014510[1] = {31.0f};
__declspec(section ".rodata") const f32 float_2_rsh_00014514[1] = {2.0f};
__declspec(section ".rodata") const f32 float_0p4_rsh_00014518[1] = {0.4f};
__declspec(section ".rodata") const f32 float_1p5_rsh_0001451c[1] = {1.5f};
__declspec(section ".rodata") const f32 float_0p8_rsh_00014520[1] = {0.8f};
__declspec(section ".rodata") const f32 float_300_rsh_00014524[1] = {300.0f};
__declspec(section ".rodata") const f32 float_600_rsh_00014528[1] = {600.0f};
__declspec(section ".rodata") const f32 float_0p25_rsh_0001452c[1] = {0.25f};
__declspec(section ".rodata") const f32 float_neg45_rsh_00014530 = -45.0f;
__declspec(section ".rodata") const f32 float_90_rsh_00014534[1] = {90.0f};
__declspec(section ".rodata") const f32 float_180_rsh_00014538[1] = {180.0f};
__declspec(section ".rodata") const f32 float_0p9_rsh_0001453c[1] = {0.9f};
__declspec(section ".rodata") const f32 float_135_rsh_00014540[1] = {135.0f};
__declspec(section ".rodata") const f32 float_0p2_rsh_00014544[1] = {0.2f};
__declspec(section ".rodata") const f32 float_0p1_rsh_00014548 = 0.10000001f;
__declspec(section ".rodata") const f32 float_neg100_rsh_0001454c = -100.0f;
__declspec(section ".rodata") const f32 float_225_rsh_00014550[1] = {225.0f};
__declspec(section ".rodata") const f32 float_1p1_rsh_00014554[1] = {1.1f};
__declspec(section ".rodata") const f32 float_1p02_rsh_00014558[1] = {1.02f};
__declspec(section ".rodata") const f32 float_0p20944_rsh_0001455c[1] = {0.20943952f};
__declspec(section ".rodata") const f32 float_neg1000_rsh_00014560 = -1000.0f;
__declspec(section ".rodata") const f32 float_250_rsh_00014564[1] = {250.0f};
__declspec(section ".rodata") const f32 float_450_rsh_00014568[1] = {450.0f};
__declspec(section ".rodata") const f32 float_neg50_rsh_0001456c = -50.0f;
__declspec(section ".rodata") const f32 float_neg1870_rsh_00014570 = -1870.0f;
__declspec(section ".rodata") const f32 float_45_rsh_00014574[1] = {45.0f};
__declspec(section ".rodata") const f32 float_60_rsh_00014578[1] = {60.0f};
__declspec(section ".rodata") const f32 float_1000_rsh_0001457c[1] = {1000.0f};
__declspec(section ".rodata") const f32 float_20_rsh_00014580[1] = {20.0f};
__declspec(section ".rodata") const f32 float_10_rsh_00014584[1] = {10.0f};
__declspec(section ".rodata") const f32 float_35_rsh_00014588[1] = {35.0f};
__declspec(section ".rodata") const f32 float_65_rsh_0001458c[1] = {65.0f};
__declspec(section ".rodata") const f32 float_40_rsh_00014590[1] = {40.0f};
__declspec(section ".rodata") const f32 float_1E06_rsh_00014594[1] = {1000000.0f};
__declspec(section ".rodata") const f64 double_30_rsh_00014598 = 30.0;
__declspec(section ".rodata") const char rsh_06_str_00004B00[12] = "offscreen\0\0";
__declspec(section ".rodata") const f32 float_neg500_rsh_000145ac = -500.0f;
__declspec(section ".rodata") const f32 float_115_rsh_000145b0 = 115.0f;
__declspec(section ".rodata") const f32 float_70_rsh_000145b4 = 70.0f;
__declspec(section ".rodata") const f32 float_neg10_rsh_000145b8 = -10.0f;
__declspec(section ".rodata") const char zero_rsh_000145bc[1] = { (char)0x00000000 };
__declspec(section ".rodata") const char rsh_06_str_00004B20[4] = "J\0\0";
__declspec(section ".rodata") const u32 gap_03_00004B24_rodata = 0x00000000;

// jumptables last, as the target emitted them with their functions
__declspec(section ".data") void* rsh_06_jumptable_000183EC[] = {
    (char*)ext_moamoa_main + 0xD38,
    (char*)ext_moamoa_main + 0x1840,
    (char*)ext_moamoa_main + 0x1B38,
    (char*)ext_moamoa_main + 0x1D9C,
    (char*)ext_moamoa_main + 0x1FF8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0xFE4,
    (char*)ext_moamoa_main + 0x1010,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x201C,
    (char*)ext_moamoa_main + 0x201C,
    (char*)ext_moamoa_main + 0x201C,
    (char*)ext_moamoa_main + 0x2320,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2380,
    (char*)ext_moamoa_main + 0x26D0,
    (char*)ext_moamoa_main + 0x2760,
    (char*)ext_moamoa_main + 0x15A8,
    (char*)ext_moamoa_main + 0x15D4,
    (char*)ext_moamoa_main + 0x169C,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x2BA8,
    (char*)ext_moamoa_main + 0x14A4,
    (char*)ext_moamoa_main + 0x2804,
    (char*)ext_moamoa_main + 0x282C,
    (char*)ext_moamoa_main + 0x2AB8,
    (char*)ext_moamoa_main + 0x2ADC,
};
#endif
// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_04_000184F4_data[1] = {0};
#pragma force_active reset

#ifdef NONMATCHING // all-C link: pool objects the C names, defined on the asm side only
__declspec(section ".data") const f64 double_30_rsh_00014598 = 30.0;
__declspec(section ".data") const f32 float_0p03_rsh_000144f4[1] = {0.03f};
__declspec(section ".data") const f32 float_0p1_rsh_000144f0[1] = {0.1f};
__declspec(section ".data") const f32 float_0p20944_rsh_0001455c[1] = {0.20943952f};
__declspec(section ".data") const f32 float_0p25_rsh_0001452c[1] = {0.25f};
__declspec(section ".data") const f32 float_0p2_rsh_00014544[1] = {0.2f};
__declspec(section ".data") const f32 float_0p3_rsh_00014508[1] = {0.3f};
__declspec(section ".data") const f32 float_0p4_rsh_00014518[1] = {0.4f};
__declspec(section ".data") const f32 float_0p5_rsh_000144e8[1] = {0.5f};
__declspec(section ".data") const f32 float_0p8_rsh_00014520[1] = {0.8f};
__declspec(section ".data") const f32 float_0p9_rsh_0001453c[1] = {0.9f};
__declspec(section ".data") const f32 float_1000_rsh_0001457c[1] = {1000.0f};
__declspec(section ".data") const f32 float_100_rsh_000144f8[1] = {100.0f};
__declspec(section ".data") const f32 float_10_rsh_00014584[1] = {10.0f};
__declspec(section ".data") const f32 float_135_rsh_00014540[1] = {135.0f};
__declspec(section ".data") const f32 float_15_rsh_00014474[1] = {15.0f};
__declspec(section ".data") const f32 float_180_rsh_00014538[1] = {180.0f};
__declspec(section ".data") const f32 float_1E06_rsh_00014594[1] = {1000000.0f};
__declspec(section ".data") const f32 float_1_rsh_00014470[1] = {1.0f};
__declspec(section ".data") const f32 float_1p02_rsh_00014558[1] = {1.02f};
__declspec(section ".data") const f32 float_1p1_rsh_00014554[1] = {1.1f};
__declspec(section ".data") const f32 float_1p5_rsh_0001451c[1] = {1.5f};
__declspec(section ".data") const f32 float_1p8_rsh_00014478[1] = {1.8f};
__declspec(section ".data") const f32 float_200_rsh_000144d8[1] = {200.0f};
__declspec(section ".data") const f32 float_20_rsh_00014580[1] = {20.0f};
__declspec(section ".data") const f32 float_215_rsh_00014504[1] = {215.0f};
__declspec(section ".data") const f32 float_225_rsh_00014550[1] = {225.0f};
__declspec(section ".data") const f32 float_250_rsh_00014564[1] = {250.0f};
__declspec(section ".data") const f32 float_2_rsh_00014514[1] = {2.0f};
__declspec(section ".data") const f32 float_300_rsh_00014524[1] = {300.0f};
__declspec(section ".data") const f32 float_30_rsh_000144dc[1] = {30.0f};
__declspec(section ".data") const f32 float_31_rsh_00014510[1] = {31.0f};
__declspec(section ".data") const f32 float_32767_rsh_000144ec[1] = {32767.0f};
__declspec(section ".data") const f32 float_35_rsh_00014588[1] = {35.0f};
__declspec(section ".data") const f32 float_360_rsh_000144a0[1] = {360.0f};
__declspec(section ".data") const f32 float_40_rsh_00014590[1] = {40.0f};
__declspec(section ".data") const f32 float_450_rsh_00014568[1] = {450.0f};
__declspec(section ".data") const f32 float_45_rsh_00014574[1] = {45.0f};
__declspec(section ".data") const f32 float_50_rsh_000144fc[1] = {50.0f};
__declspec(section ".data") const f32 float_5_rsh_00014500[1] = {5.0f};
__declspec(section ".data") const f32 float_600_rsh_00014528[1] = {600.0f};
__declspec(section ".data") const f32 float_60_rsh_00014578[1] = {60.0f};
__declspec(section ".data") const f32 float_65_rsh_0001458c[1] = {65.0f};
__declspec(section ".data") const f32 float_6p2832_rsh_0001449c[1] = {6.2831855f};
__declspec(section ".data") const f32 float_90_rsh_00014534[1] = {90.0f};
__declspec(section ".data") const char str_00004334[8] = "sha_2_1";
__declspec(section ".data") const char str_00004384[8] = "sha_5_2";
__declspec(section ".data") const char str_000043F4[12] = "sha_6_2_c\0\0";
__declspec(section ".data") const char str_00004400[12] = "sha_6_3_c\0\0";
__declspec(section ".data") const char str_00004488[16] = "hosi_right_c\0\0\0";
__declspec(section ".data") const char str_000045BC[28] = "SFX_STG6_TRAIN_MOVE2_2_2\0\0\0";
__declspec(section ".data") const char str_000045E0[12] = "pika_1_1\0\0\0";
__declspec(section ".data") const char str_0000465C[12] = "pika_1_4_c\0";
__declspec(section ".data") const char str_0000470C[12] = "renketu_3\0\0";
__declspec(section ".data") const char str_0000474C[8] = "moa_a\0\0";
__declspec(section ".data") const char str_0000483C[8] = "eff0\0\0\0";
__declspec(section ".data") const char str_00004980[16] = "ENV_STG6_RSH1_3";
__declspec(section ".data") const char str_000049C0[16] = "BGM_STG0_GOR1\0\0";
__declspec(section ".data") const f32 zero_rsh_00014490[1] = {0.0f};
__declspec(section ".data") const char zero_rsh_000145bc[1] = { (char)0x00000000 };
#endif
