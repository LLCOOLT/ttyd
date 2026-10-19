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
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
#define EXT_LIT(sym, val) (sym)
__declspec(section ".rodata") extern const f32 vec3_tou2_00009638[3];
__declspec(section ".rodata") extern const f32 vec3_tou2_0000a6c0[3];
__declspec(section ".rodata") extern const f32 vec3_tou2_0000a6cc[3];
__declspec(section ".rodata") extern const u32 dat_tou2_0000a738;
__declspec(section ".rodata") extern const f32 float_15_tou2_0000ae2c;
__declspec(section ".rodata") extern const char tou_03_str_00001840[12];
__declspec(section ".rodata") extern const f32 float_100_tou2_0000ae3c;
__declspec(section ".rodata") extern const f32 zero_tou2_0000ae40;
__declspec(section ".rodata") extern const f32 float_1_tou2_0000ae44;
__declspec(section ".rodata") extern const f32 float_0p5_tou2_0000ae48;
__declspec(section ".rodata") extern const f32 float_6p2832_tou2_0000ae4c;
__declspec(section ".rodata") extern const f32 float_360_tou2_0000ae50;
__declspec(section ".rodata") extern const char tou_03_str_00001864[24];
__declspec(section ".rodata") extern const char tou_03_str_0000187C[8];
__declspec(section ".rodata") extern const f32 float_3_tou2_0000ae74;
__declspec(section ".rodata") extern const f32 float_10_tou2_0000ae78;
__declspec(section ".rodata") extern const f32 float_210_tou2_0000ae7c;
__declspec(section ".rodata") extern const f32 float_neg210_tou2_0000ae80;
__declspec(section ".rodata") extern const f32 float_60_tou2_0000ae84;
__declspec(section ".rodata") extern const f32 float_0p25_tou2_0000ae88;
__declspec(section ".rodata") extern const f32 float_4p75_tou2_0000ae8c;
__declspec(section ".rodata") extern const f32 float_3p75_tou2_0000ae90;
__declspec(section ".rodata") extern const f32 float_16_tou2_0000ae94;
__declspec(section ".rodata") extern const f32 float_6_tou2_0000ae98;
__declspec(section ".rodata") extern const f32 float_1000_tou2_0000ae9c;
__declspec(section ".rodata") extern const f32 float_neg1_tou2_0000aea0;
__declspec(section ".rodata") extern const f32 float_6p2832_tou2_0000aea4;
__declspec(section ".rodata") extern const f32 float_250_tou2_0000aea8;
__declspec(section ".rodata") extern const f32 float_500_tou2_0000aeac;
__declspec(section ".rodata") extern const f32 float_550_tou2_0000aeb0;
__declspec(section ".rodata") extern const f32 float_650_tou2_0000aeb4;
__declspec(section ".rodata") extern const f32 float_850_tou2_0000aeb8;
__declspec(section ".rodata") extern const f32 float_0p7854_tou2_0000aebc;
__declspec(section ".rodata") extern const f32 float_5p4978_tou2_0000aec0;
__declspec(section ".rodata") extern const f64 double_70_tou2_0000aec8;
__declspec(section ".rodata") extern const f32 float_1E05_tou2_0000aed0;
__declspec(section ".rodata") extern const f32 float_570_tou2_0000aed4;
__declspec(section ".rodata") extern const f32 float_40_tou2_0000aed8;
__declspec(section ".rodata") extern const f32 float_350_tou2_0000aedc;
__declspec(section ".rodata") extern const f64 double_to_int_tou2_0000aee0;
extern const char tou_03_str_00000350[];
extern const char tou_03_str_00000360[];
extern const char tou_03_str_00000474[];
extern const char tou_03_str_000004BC[];
extern const char tou_03_str_00000518[];
extern const char tou_03_str_00000540[];
extern const char tou_03_str_00000698[];
extern const char tou_03_str_00000000[];
extern const char tou_03_str_0000000C[];
extern const char tou_03_str_00000014[];
extern const char tou_03_str_00000020[];
extern const char tou_03_str_00000028[];
extern const char tou_03_str_00000030[];
extern const char tou_03_str_00000034[];
extern const char tou_03_str_00000040[];
extern const char tou_03_str_00000054[];
extern const char tou_03_str_0000005C[];
extern const char tou_03_str_00000064[];
extern const char tou_03_str_0000006C[];
extern const char tou_03_str_00000074[];
extern const char tou_03_str_00000080[];
extern const char tou_03_str_0000008C[];
extern const char tou_03_str_00000094[];
extern const char tou_03_str_000000A0[];
extern const char tou_03_str_000000AC[];
extern const char tou_03_str_000000B8[];
extern const char tou_03_str_000000C8[];
extern const char tou_03_str_000000D4[];
extern const char tou_03_str_000000E0[];
extern const char tou_03_str_000000EC[];
extern const char tou_03_str_000000F8[];
extern const char tou_03_str_00000104[];
extern const char tou_03_str_00000110[];
extern const char tou_03_str_0000011C[];
extern const char tou_03_str_00000128[];
extern const char tou_03_str_00000130[];
extern const char tou_03_str_00000138[];
extern const char tou_03_str_00000144[];
extern const char tou_03_str_0000014C[];
extern const char tou_03_str_00000158[];
extern const char tou_03_str_00000164[];
extern const char tou_03_str_0000016C[];
#endif
extern const u32 zero_tou2_00009ea8[1];
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
extern const char tou_03_str_0000017C[];
extern const char tou_03_str_00000184[];
extern const char tou_03_str_0000019C[];
extern const char tou_03_str_000001A8[];
extern const char tou_03_str_000001B4[];
extern const char tou_03_str_000001CC[];
extern const char tou_03_str_000001D0[];
extern const char tou_03_str_000001D4[];
extern const char tou_03_str_000001E0[];
extern const char tou_03_str_000001E8[];
extern const char tou_03_str_000001EC[];
extern const char tou_03_str_000001F0[];
extern const char tou_03_str_000001FC[];
extern const char tou_03_str_00000208[];
extern const char tou_03_str_0000020C[];
extern const char tou_03_str_00000210[];
extern const char tou_03_str_0000021C[];
extern const char tou_03_str_00000220[];
extern const char tou_03_str_00000224[];
extern const char tou_03_str_00000228[];
extern const char tou_03_str_0000022C[];
extern const char tou_03_str_00000230[];
extern const char tou_03_str_00000234[];
extern const char tou_03_str_0000023C[];
extern const char tou_03_str_00000248[];
extern const char tou_03_str_0000024C[];
extern const char tou_03_str_00000258[];
extern const char tou_03_str_00000270[];
extern const char tou_03_str_00000274[];
extern const char tou_03_str_00000280[];
extern const char tou_03_str_0000028C[];
extern const char tou_03_str_00000298[];
extern const char tou_03_str_000002B0[];
extern const char tou_03_str_000002C0[];
extern const char tou_03_str_000002D0[];
extern const char tou_03_str_000002D8[];
extern const char tou_03_str_000002E0[];
extern const char tou_03_str_000002E8[];
extern const char tou_03_str_000002EC[];
extern const char tou_03_str_000002F4[];
extern const char tou_03_str_000002FC[];
extern const char tou_03_str_00000304[];
extern const char tou_03_str_0000030C[];
extern const char tou_03_str_00000314[];
extern const char tou_03_str_0000031C[];
extern const char tou_03_str_00000320[];
extern const char tou_03_str_00000328[];
extern const char tou_03_str_00000330[];
extern const char tou_03_str_00000338[];
extern const char tou_03_str_00000340[];
extern const char tou_03_str_00000370[];
extern const char tou_03_str_0000037C[];
extern const char tou_03_str_00000384[];
extern const char tou_03_str_00000390[];
extern const char tou_03_str_0000039C[];
extern const char tou_03_str_000003A8[];
extern const char tou_03_str_000003C0[];
extern const char tou_03_str_000003CC[];
extern const char tou_03_str_000003D8[];
extern const char tou_03_str_000003E4[];
extern const char tou_03_str_000003F4[];
extern const char tou_03_str_00000404[];
extern const char tou_03_str_00000414[];
extern const char tou_03_str_00000420[];
extern const char tou_03_str_00000434[];
extern const char tou_03_str_0000043C[];
extern const char tou_03_str_00000444[];
extern const char tou_03_str_0000044C[];
extern const char tou_03_str_00000454[];
extern const char tou_03_str_0000045C[];
extern const char tou_03_str_00000464[];
extern const char tou_03_str_0000046C[];
extern const char tou_03_str_00000480[];
extern const char tou_03_str_00000498[];
extern const char tou_03_str_000004B0[];
extern const char tou_03_str_000004B4[];
extern const char tou_03_str_000004C4[];
extern const char tou_03_str_000004DC[];
extern const char tou_03_str_000004F4[];
extern const char tou_03_str_0000050C[];
extern const char tou_03_str_0000052C[];
extern const char tou_03_str_00000534[];
extern const char tou_03_str_00000554[];
extern const char tou_03_str_0000056C[];
extern const char tou_03_str_00000570[];
extern const char tou_03_str_00000580[];
extern const char tou_03_str_00000588[];
extern const char tou_03_str_00000598[];
extern const char tou_03_str_000005A8[];
extern const char tou_03_str_000005B8[];
extern const char tou_03_str_000005C0[];
extern const char tou_03_str_000005C8[];
extern const char tou_03_str_000005D8[];
extern const char tou_03_str_000005E8[];
extern const char tou_03_str_000005F8[];
extern const char tou_03_str_00000608[];
extern const char tou_03_str_00000618[];
extern const char tou_03_str_00000628[];
extern const char tou_03_str_00000638[];
extern const char tou_03_str_00000648[];
extern const char tou_03_str_00000650[];
extern const char tou_03_str_00000658[];
extern const char tou_03_str_00000668[];
extern const char tou_03_str_00000678[];
extern const char tou_03_str_00000688[];
extern const char tou_03_str_000006A8[];
extern const char tou_03_str_000006B0[];
extern const char tou_03_str_000006B8[];
extern const char tou_03_str_000006C0[];
extern const char tou_03_str_000006C8[];
extern const char tou_03_str_000006D0[];
extern const char tou_03_str_000006DC[];
extern const char tou_03_str_000006E4[];
extern const char tou_03_str_000006EC[];
extern const char tou_03_str_000006F4[];
extern const char tou_03_str_000006FC[];
extern const char tou_03_str_00000704[];
extern const char tou_03_str_00000720[];
extern const char tou_03_str_00000730[];
extern const char tou_03_str_00000740[];
extern const char tou_03_str_00000748[];
extern const char tou_03_str_00000750[];
extern const char tou_03_str_00000758[];
extern const char tou_03_str_00000768[];
extern const char tou_03_str_00000774[];
extern const char tou_03_str_00000780[];
extern const char tou_03_str_0000078C[];
extern const char tou_03_str_00000794[];
extern const char tou_03_str_000007A8[];
extern const char tou_03_str_000007B4[];
extern const char tou_03_str_000007D0[];
extern const char tou_03_str_000007EC[];
extern const char tou_03_str_00000808[];
extern const char tou_03_str_00000814[];
extern const char tou_03_str_00000820[];
extern const char tou_03_str_0000083C[];
extern const char tou_03_str_00000844[];
extern const char tou_03_str_0000085C[];
extern const char tou_03_str_00000864[];
extern const char tou_03_str_0000086C[];
extern const char tou_03_str_00000884[];
extern const char tou_03_str_00000890[];
extern const char tou_03_str_0000089C[];
extern const char tou_03_str_000008AC[];
extern const char tou_03_str_000008BC[];
extern const char tou_03_str_000008C8[];
extern const char tou_03_str_000008E0[];
extern const char tou_03_str_000008F0[];
extern const char tou_03_str_000008FC[];
extern const char tou_03_str_0000090C[];
extern const char tou_03_str_0000091C[];
extern const char tou_03_str_00000938[];
extern const char tou_03_str_00000948[];
extern const char tou_03_str_00000958[];
extern const char tou_03_str_00000968[];
extern const char tou_03_str_00000978[];
extern const char tou_03_str_00000988[];
extern const char tou_03_str_00000998[];
extern const char tou_03_str_000009A8[];
extern const char tou_03_str_000009AC[];
extern const char tou_03_str_000009BC[];
extern const char tou_03_str_000009CC[];
extern const char tou_03_str_000009DC[];
extern const char tou_03_str_000009EC[];
extern const char tou_03_str_000009FC[];
extern const char tou_03_str_00000A0C[];
extern const char tou_03_str_00000A10[];
extern const char tou_03_str_00000A14[];
extern const char tou_03_str_00000A18[];
extern const char tou_03_str_00000A2C[];
extern const char tou_03_str_00000A3C[];
extern const char tou_03_str_00000A4C[];
extern const char tou_03_str_00000A5C[];
extern const char tou_03_str_00000A64[];
extern const char tou_03_str_00000A7C[];
extern const char tou_03_str_00000A84[];
extern const char tou_03_str_00000A94[];
extern const char tou_03_str_00000AA4[];
extern const char tou_03_str_00000ABC[];
extern const char tou_03_str_00000ACC[];
extern const char tou_03_str_00000AD0[];
extern const char tou_03_str_00000AE0[];
extern const char tou_03_str_00000AF0[];
extern const char tou_03_str_00000B00[];
extern const char tou_03_str_00000B10[];
extern const char tou_03_str_00000B20[];
extern const char tou_03_str_00000B30[];
extern const char tou_03_str_00000B40[];
extern const char tou_03_str_00000B5C[];
extern const char tou_03_str_00000B6C[];
extern const char tou_03_str_00000B7C[];
extern const char tou_03_str_00000B8C[];
extern const char tou_03_str_00000B9C[];
extern const char tou_03_str_00000BAC[];
extern const char tou_03_str_00000BBC[];
extern const char tou_03_str_00000BCC[];
extern const char tou_03_str_00000BDC[];
extern const char tou_03_str_00000BEC[];
extern const char tou_03_str_00000BFC[];
extern const char tou_03_str_00000C0C[];
extern const char tou_03_str_00000C1C[];
extern const char tou_03_str_00000C2C[];
extern const char tou_03_str_00000C3C[];
extern const char tou_03_str_00000C4C[];
extern const char tou_03_str_00000C5C[];
extern const char tou_03_str_00000C6C[];
extern const char tou_03_str_00000C7C[];
extern const char tou_03_str_00000C8C[];
extern const char tou_03_str_00000C9C[];
extern const char tou_03_str_00000CAC[];
extern const char tou_03_str_00000CBC[];
extern const char tou_03_str_00000CCC[];
extern const char tou_03_str_00000CDC[];
extern const char tou_03_str_00000CEC[];
extern const char tou_03_str_00000CFC[];
extern const char tou_03_str_00000D0C[];
extern const char tou_03_str_00000D10[];
extern const char tou_03_str_00000D14[];
extern const char tou_03_str_00000D24[];
extern const char tou_03_str_00000D34[];
extern const char tou_03_str_00000D44[];
extern const char tou_03_str_00000D54[];
extern const char tou_03_str_00000D64[];
extern const char tou_03_str_00000D78[];
extern const char tou_03_str_00000D80[];
extern const char tou_03_str_00000D88[];
extern const char tou_03_str_00000D98[];
extern const char tou_03_str_00000DA8[];
extern const char tou_03_str_00000DB8[];
extern const char tou_03_str_00000DC8[];
extern const char tou_03_str_00000DD8[];
extern const char tou_03_str_00000DE8[];
extern const char tou_03_str_00000DF8[];
extern const char tou_03_str_00000E08[];
extern const char tou_03_str_00000E18[];
extern const char tou_03_str_00000E28[];
extern const char tou_03_str_00000E38[];
extern const char tou_03_str_00000E48[];
extern const char tou_03_str_00000E58[];
extern const char tou_03_str_00000E68[];
extern const char tou_03_str_00000E78[];
extern const char tou_03_str_00000E88[];
extern const char tou_03_str_00000E98[];
extern const char tou_03_str_00000EA8[];
extern const char tou_03_str_00000EB8[];
extern const char tou_03_str_00000EC8[];
extern const char tou_03_str_00000ED8[];
extern const char tou_03_str_00000EE8[];
extern const char tou_03_str_00000EF8[];
extern const char tou_03_str_00000F08[];
extern const char tou_03_str_00000F18[];
extern const char tou_03_str_00000F28[];
extern const char tou_03_str_00000F38[];
extern const char tou_03_str_00000F48[];
extern const char tou_03_str_00000F58[];
extern const char tou_03_str_00000F68[];
extern const char tou_03_str_00000F78[];
extern const char tou_03_str_00000F88[];
extern const char tou_03_str_00000F98[];
extern const char tou_03_str_00000FA8[];
extern const char tou_03_str_00000FB8[];
extern const char tou_03_str_00000FC8[];
extern const char tou_03_str_00000FD8[];
extern const char tou_03_str_00000FE8[];
extern const char tou_03_str_00000FF8[];
extern const char tou_03_str_00001008[];
extern const char tou_03_str_00001018[];
extern const char tou_03_str_00001028[];
extern const char tou_03_str_00001038[];
extern const char tou_03_str_00001048[];
extern const char tou_03_str_00001058[];
extern const char tou_03_str_00001068[];
extern const char tou_03_str_00001078[];
extern const char tou_03_str_00001080[];
extern const char tou_03_str_00001088[];
extern const char tou_03_str_00001098[];
extern const char tou_03_str_000010A8[];
extern const char tou_03_str_000010B8[];
extern const char tou_03_str_000010C8[];
extern const char tou_03_str_000010E8[];
extern const char tou_03_str_000010F0[];
extern const char tou_03_str_000010F8[];
extern const char tou_03_str_00001100[];
extern const char tou_03_str_00001108[];
extern const char tou_03_str_00001110[];
extern const char tou_03_str_00001118[];
extern const char tou_03_str_00001120[];
extern const char tou_03_str_00001128[];
extern const char tou_03_str_00001130[];
extern const char tou_03_str_00001138[];
extern const char tou_03_str_0000114C[];
extern const char tou_03_str_00001154[];
extern const char tou_03_str_00001160[];
extern const char tou_03_str_00001168[];
extern const char tou_03_str_0000117C[];
extern const char tou_03_str_0000118C[];
extern const char tou_03_str_000011A4[];
extern const char tou_03_str_000011A8[];
extern const char tou_03_str_000011B0[];
extern const char tou_03_str_000011B8[];
extern const char tou_03_str_000011C0[];
extern const char tou_03_str_000011CC[];
extern const char tou_03_str_000011D4[];
extern const char tou_03_str_000011DC[];
extern const char tou_03_str_000011E4[];
extern const char tou_03_str_00001200[];
extern const char tou_03_str_00001220[];
extern const char tou_03_str_00001234[];
extern const char tou_03_str_0000123C[];
extern const char tou_03_str_0000124C[];
extern const char tou_03_str_0000125C[];
extern const char tou_03_str_0000126C[];
extern const char tou_03_str_0000127C[];
extern const char tou_03_str_00001280[];
extern const char tou_03_str_00001284[];
extern const char tou_03_str_0000129C[];
extern const char tou_03_str_000012B0[];
extern const char tou_03_str_000012BC[];
extern const char tou_03_str_000012D0[];
extern const char tou_03_str_000012D4[];
extern const char tou_03_str_000012E4[];
extern const char tou_03_str_000012EC[];
extern const char tou_03_str_000012FC[];
extern const char tou_03_str_0000130C[];
extern const char tou_03_str_00001324[];
extern const char tou_03_str_00001328[];
extern const char tou_03_str_0000132C[];
extern const char tou_03_str_0000133C[];
extern const char tou_03_str_0000134C[];
extern const char tou_03_str_0000135C[];
extern const char tou_03_str_00001374[];
extern const char tou_03_str_00001384[];
extern const char tou_03_str_00001394[];
extern const char tou_03_str_000013A4[];
extern const char tou_03_str_000013B4[];
extern const char tou_03_str_000013C4[];
extern const char tou_03_str_000013D4[];
extern const char tou_03_str_000013E8[];
extern const char tou_03_str_000013FC[];
extern const char tou_03_str_00001410[];
extern const char tou_03_str_00001424[];
extern const char tou_03_str_00001428[];
extern const char tou_03_str_00001438[];
extern const char tou_03_str_00001450[];
extern const char tou_03_str_00001458[];
extern const char tou_03_str_0000146C[];
extern const char tou_03_str_00001488[];
extern const char tou_03_str_00001490[];
extern const char tou_03_str_000014A4[];
extern const char tou_03_str_000014B8[];
extern const char tou_03_str_000014CC[];
extern const char tou_03_str_000014E0[];
extern const char tou_03_str_000014F4[];
extern const char tou_03_str_00001504[];
extern const char tou_03_str_00001520[];
extern const char tou_03_str_00001530[];
extern const char tou_03_str_00001540[];
extern const char tou_03_str_00001550[];
extern const char tou_03_str_00001568[];
extern const char tou_03_str_00001570[];
extern const char tou_03_str_00001584[];
extern const char tou_03_str_00001594[];
extern const char tou_03_str_000015A4[];
extern const char tou_03_str_000015B4[];
extern const char tou_03_str_000015C4[];
extern const char tou_03_str_000015D4[];
extern const char tou_03_str_000015E4[];
extern const char tou_03_str_000015F4[];
extern const char tou_03_str_00001604[];
extern const char tou_03_str_00001614[];
extern const char tou_03_str_00001624[];
extern const char tou_03_str_00001634[];
extern const char tou_03_str_00001644[];
extern const char tou_03_str_00001654[];
extern const char tou_03_str_00001664[];
extern const char tou_03_str_00001674[];
extern const char tou_03_str_00001684[];
extern const char tou_03_str_00001694[];
extern const char tou_03_str_000016A4[];
extern const char tou_03_str_000016B4[];
extern const char tou_03_str_000016C4[];
extern const char tou_03_str_000016D4[];
extern const char tou_03_str_000016E4[];
extern const char tou_03_str_000016F4[];
extern const char tou_03_str_00001704[];
extern const char tou_03_str_00001714[];
extern const char tou_03_str_00001724[];
extern const char tou_03_str_00001734[];
extern const char tou_03_str_00001744[];
extern const char tou_03_str_00001754[];
extern const char tou_03_str_00001764[];
extern const char tou_03_str_00001774[];
extern const char tou_03_str_00001784[];
extern const char tou_03_str_00001794[];
extern const char tou_03_str_000017A4[];
extern const char tou_03_str_000017B4[];
extern const char tou_03_str_000017C4[];
extern const char tou_03_str_000017D4[];
extern const char tou_03_str_000017D8[];
extern const char tou_03_str_000017E8[];
extern const char tou_03_str_000017F0[];
extern const char tou_03_str_000017F8[];
extern const char tou_03_str_00001804[];
extern const char tou_03_str_00001810[];
extern const char tou_03_str_0000181C[];
extern const char tou_03_str_00001824[];
extern const char tou_03_str_0000182C[];
extern const char tou_03_str_00001834[];
#endif
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
#ifdef NONMATCHING
static s32 tou_03_bss_0xC;
#endif
#ifndef NONMATCHING
static u8 gap_05_0000000C_bss[4];  // .bss pad after kyaku_wp
#endif
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
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
    (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C), 0, (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C), 1092616192, (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C),
    1101004800, (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C), 1106247680, (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C), 1109393408, (s32)((char*)tou_03_str_00000000),
    (s32)((char*)tou_03_str_0000000C), 1112014848, (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C), 1114636288, (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C), 1116471296,
    (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C), 1117782016, (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C), 1119092736, (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C),
    1120403456, (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C), 1121714176, (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C), 1123024896, (s32)((char*)tou_03_str_00000000),
    (s32)((char*)tou_03_str_0000000C), 1124204544, (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C), 1124859904, (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C), 1125515264,
    (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C), 1126170624, (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C), 1126825984, (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C),
    1127481344, (s32)((char*)tou_03_str_00000000), (s32)((char*)tou_03_str_0000000C), 1128136704, (s32)((char*)tou_03_str_00000014), (s32)((char*)tou_03_str_00000020), 0, (s32)((char*)tou_03_str_00000014),
    (s32)((char*)tou_03_str_00000020), 1092616192, (s32)((char*)tou_03_str_00000014), (s32)((char*)tou_03_str_00000020), 1101004800, (s32)((char*)tou_03_str_00000014), (s32)((char*)tou_03_str_00000020), 1106247680,
    (s32)((char*)tou_03_str_00000014), (s32)((char*)tou_03_str_00000020), 1109393408, (s32)((char*)tou_03_str_00000014), (s32)((char*)tou_03_str_00000020), 1112014848, (s32)((char*)tou_03_str_00000014), (s32)((char*)tou_03_str_00000020),
    1114636288, (s32)((char*)tou_03_str_00000014), (s32)((char*)tou_03_str_00000020), 1116471296, (s32)((char*)tou_03_str_00000014), (s32)((char*)tou_03_str_00000020), 1117782016, (s32)((char*)tou_03_str_00000014),
    (s32)((char*)tou_03_str_00000020), 1119092736, (s32)((char*)tou_03_str_00000014), (s32)((char*)tou_03_str_00000020), 1120403456, (s32)((char*)tou_03_str_00000014), (s32)((char*)tou_03_str_00000020), 1121714176,
    (s32)((char*)tou_03_str_00000014), (s32)((char*)tou_03_str_00000020), 1123024896, (s32)((char*)tou_03_str_00000014), (s32)((char*)tou_03_str_00000020), 1124204544, (s32)((char*)tou_03_str_00000014), (s32)((char*)tou_03_str_00000020),
    1124859904, (s32)((char*)tou_03_str_00000014), (s32)((char*)tou_03_str_00000020), 1125515264, (s32)((char*)tou_03_str_00000014), (s32)((char*)tou_03_str_00000020), 1126170624, (s32)((char*)tou_03_str_00000028),
    (s32)((char*)tou_03_str_00000030), 0, (s32)((char*)tou_03_str_00000028), (s32)((char*)tou_03_str_00000030), 1092616192, (s32)((char*)tou_03_str_00000028), (s32)((char*)tou_03_str_00000030), 1101004800,
    (s32)((char*)tou_03_str_00000028), (s32)((char*)tou_03_str_00000030), 1106247680, (s32)((char*)tou_03_str_00000028), (s32)((char*)tou_03_str_00000030), 1109393408, (s32)((char*)tou_03_str_00000028), (s32)((char*)tou_03_str_00000030),
    1112014848, (s32)((char*)tou_03_str_00000034), (s32)((char*)tou_03_str_00000040), 0, (s32)((char*)tou_03_str_00000034), (s32)((char*)tou_03_str_00000040), 1092616192, (s32)((char*)tou_03_str_00000034),
    (s32)((char*)tou_03_str_00000040), 1101004800, (s32)((char*)tou_03_str_00000034), (s32)((char*)tou_03_str_00000040), 1106247680, (s32)((char*)tou_03_str_00000034), (s32)((char*)tou_03_str_00000040), 1109393408,
    (s32)((char*)tou_03_str_00000034), (s32)((char*)tou_03_str_00000040), 1112014848, (s32)((char*)tou_03_str_00000034), (s32)((char*)tou_03_str_00000040), 1114636288, 0, 0,
#endif
    0,
};

__declspec(section ".data") EVT_BEGIN(x)
EVT_END()

s32 _firstattack_setting(EventEntry* event, BOOL isFirstCall) {
    FieldBattleData* fbat = fbatGetPointer();

    *(s32*)&fbat->field_C[4] = 0x10000000;
    *(s32*)&fbat->field_C[8] = 0x10;
    *(u32*)&fbat->field_C[0x10] &= ~1;
    fbatSetAttackAnnounce(0x10000000);
    fbatSetAttackAnnounceEnable();
    return EVT_RETURN_DONE;
}

#pragma dont_inline on
#ifndef NONMATCHING
void DCFlushRange(void* addr, u32 nBytes);
u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, u8 mipmap, u8 max_lod);
void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXTexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
    f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp,
    GXBool do_edge_lod, GXAnisotropy max_aniso);
void GXLoadTexMtxImm(const f32 mtx[][4], u32 id, GXTexMtxType type);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevColor(GXTevRegID id, GXColor color);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras_sel, GXTevSwapSel tex_sel);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXIdentity(Mtx m);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
f32 PSVECDistance(const Vec* a, const Vec* b);
int __cvt_ull_flt();
int __div2u();
void *memset(void *dest, int ch, size_t count);
int rand(void);
int sprintf(char *s, const char *format, ...);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
#endif
static void pose_init(void) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	char _af_pad[64];
	asm {
		lis r4, zero_tou2_00009ea8@ha
		lis r3, ext_kyaku_data@ha
		addi r0, r3, ext_kyaku_data@l
		la r3, _af_pad+32
		addi r4, r4, zero_tou2_00009ea8@l
	}
	asm volatile {
		opword 0x3BA00000
		opword 0x7C1E0378
		bl strcpy
		lis r4, zero_tou2_00009ea8@ha
		opword 0x38610008
		addi r4, r4, zero_tou2_00009ea8@l
		bl strcpy
		lis r3, kyaku_wp@ha
		opword 0x3800FFFF
		addi r31, r3, kyaku_wp@l
		opword 0x807F0000
		opword 0x9003000C
		opword 0x807E0000
		opword 0x38810028
		bl strcmp
		opword 0x2C030000
		opword 0x41820020
		opword 0x809E0000
		opword 0x38610028
		bl strcpy
		lis r4, zero_tou2_00009ea8@ha
		opword 0x38610008
		addi r4, r4, zero_tou2_00009ea8@l
		bl strcpy
		opword 0x807E0004
		opword 0x38810008
		bl strcmp
		opword 0x2C030000
		opword 0x41820028
		opword 0x809E0004
		opword 0x38610008
		bl strcpy
		lis r3, kyaku_wp@ha
		mr r28, r29
		lwz r4, kyaku_wp@l(r3)
		opword 0x8064000C
		opword 0x38030001
		opword 0x9004000C
		opword 0x80BF0000
		opword 0x38810028
		opword 0x8005000C
		opword 0x1C600028
		opword 0x38630010
		opword 0x7C651A14
		bl strcpy
		opword 0x80BF0000
		opword 0x38810008
		opword 0x8005000C
		opword 0x1C600028
		opword 0x38630020
		opword 0x7C651A14
		bl strcpy
		opword 0x80DF0000
		opword 0x7C7CE850
		opword 0x38A30001
		opword 0x38800001
		opword 0x8006000C
		opword 0x3BBD0001
		opword 0x1C600028
		opword 0x38030030
		opword 0x7F86012E
		opword 0x80DF0000
		opword 0x8006000C
		opword 0x1C600028
		opword 0x38030034
		opword 0x7CA6012E
		opword 0x80BF0000
		opword 0xC01E0008
		opword 0x8005000C
		opword 0x1C600028
		opword 0x3803002C
		opword 0x7C05052E
		opword 0x80BF0000
		opword 0x8005000C
		opword 0x1C600028
		opword 0x38030028
		opword 0x7C85032E
		opword 0x841E000C
		opword 0x28000000
		opword 0x4082FEF4
		lis r3, kyaku_wp@ha
		lwz r4, kyaku_wp@l(r3)
		opword 0x8064000C
		opword 0x38030001
		opword 0x9004000C
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif
#pragma dont_inline reset

#pragma dont_inline on
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
static void pose_main(void) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	char _af_pad[8];
	asm volatile {
		bl extGetPosePtr
		lis r4, kyaku_wp@ha
		lis r7, float_60_tou2_0000ae84@ha
		addi r29, r4, kyaku_wp@l
		lis r6, float_1000_tou2_0000ae9c@ha
		opword 0x813D0000
		lis r5, float_1_tou2_0000ae44@ha
		lis r4, double_to_int_tou2_0000aee0@ha
		lis r8, gp@ha
		opword 0x83090008
		opword 0x7C791B78
		lfs f28, float_60_tou2_0000ae84@l(r7)
		addi r30, r8, gp@l
		lfs f29, float_1000_tou2_0000ae9c@l(r6)
		opword 0x3B400000
		lfs f30, float_1_tou2_0000ae44@l(r5)
		opword 0x3FE08000
		lfd f31, double_to_int_tou2_0000aee0@l(r4)
		opword 0x3EE04330
		opword 0x480000BC
		opword 0x807F00F8
		opword 0x380003E8
		opword 0x809E0000
		opword 0x38A00000
		opword 0x5463F0BE
		opword 0xA8F80010
		opword 0x7CC30396
		opword 0x8364003C
		opword 0x8018001C
		opword 0x83840038
		opword 0x7C80D810
		opword 0x80180018
		opword 0x1CE70028
		opword 0x7C60E110
		addi r22, r7, 0x10
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
		opword 0x9378001C
		lis r3, zero_tou2_0000ae40@ha
		lfs f1, zero_tou2_0000ae40@l(r3)
		opword 0x93980018
		opword 0x80760024
		opword 0x3B5A0001
		stw r23, _af_pad+0(r1)
		opword 0x3B180020
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

#pragma dont_inline on
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
#pragma dont_inline reset

#pragma dont_inline on
void __tou_srand(u32 seed) {
    x[0] = seed;
}
#pragma dont_inline reset

#pragma dont_inline on
u32 __tou_rand(void) {
    x[0] = x[0] * 1103515245 + 12345;
    return ((u32)x[0] >> 16) & 0x7FFF;
}
#pragma dont_inline reset

#pragma dont_inline on
static f32 randf(f32 min, f32 max) {
    f32 r = __tou_rand() / 32767.0f;

    return r * (max - min) + min;
}
#pragma dont_inline reset

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void ext_kyaku_init(void) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	char _af_pad[40];
	asm volatile {
		opword 0x38600510
		bl _mapAlloc
		lis r5, kyaku_wp@ha
		opword 0x38800000
		addi r6, r5, kyaku_wp@l
		opword 0x38A00510
		opword 0x90660000
		bl memset
		bl extGetPoseNum
		lis r4, kyaku_wp@ha
		addi r5, r4, kyaku_wp@l
		opword 0x80850000
		opword 0x90640004
		opword 0x80650000
		opword 0x80030004
		opword 0x54032834
		bl _mapAlloc
		lis r5, kyaku_wp@ha
		opword 0x38800000
		addi r6, r5, kyaku_wp@l
		opword 0x80A60000
		opword 0x90650008
		opword 0x80660000
		opword 0x80030004
		opword 0x80630008
		opword 0x54052834
		bl memset
		bl pose_init
		opword 0x3C60025B
		opword 0x38630E2B
		bl __tou_srand
		bl extGetPosePtr
		lis r5, kyaku_wp@ha
		lis r4, zero_tou2_0000ae40@ha
		addi r30, r5, kyaku_wp@l
		lis r7, float_6p2832_tou2_0000aea4@ha
		opword 0x811E0000
		addi r31, r4, zero_tou2_0000ae40@l
		lis r6, gp@ha
		lis r5, tou_03_str_000000A0@ha
		lis r4, vec3_tou2_00009638@ha
		opword 0x83680008
		opword 0xC3FF0000
		opword 0x7C7C1B78
		addi r23, r7, float_6p2832_tou2_0000aea4@l
		addi r24, r6, gp@l
		addi r25, r5, tou_03_str_000000A0@l
		addi r26, r4, vec3_tou2_00009638@l
		opword 0x3BA00000
		opword 0x48000420
		opword 0x801C0000
		opword 0x60000007
		opword 0x901C0000
		opword 0x807C000C
		bl PSMTXIdentity
		bl __tou_rand
		opword 0x38C00064
		opword 0x3800001E
		opword 0x7CA33396
		opword 0xC03F0000
		opword 0xC0570000
		opword 0x3880FFFF
		opword 0x7CA531D6
		opword 0x7C651850
		opword 0x7C001810
		subfze r22, r4
		bl randf
		opword 0x2C160000
		opword 0xFFA00890
		opword 0x40820020
		lis r4, float_250_tou2_0000aea8@ha
		lis r3, float_500_tou2_0000aeac@ha
		lfs f1, float_250_tou2_0000aea8@l(r4)
		lfs f2, float_500_tou2_0000aeac@l(r3)
		bl randf
		opword 0xFFC00890
		opword 0x48000064
		lis r3, float_0p7854_tou2_0000aebc@ha
		opword 0x38000000
		lfs f0, float_0p7854_tou2_0000aebc@l(r3)
		opword 0xFC1D0040
		opword 0x41800014
		lis r3, float_5p4978_tou2_0000aec0@ha
		lfs f0, float_5p4978_tou2_0000aec0@l(r3)
		opword 0xFC1D0040
		opword 0x40810008
		opword 0x38000001
		opword 0x2C000000
		opword 0x4182001C
		lis r4, float_550_tou2_0000aeb0@ha
		lis r3, float_650_tou2_0000aeb4@ha
		lfs f1, float_550_tou2_0000aeb0@l(r4)
		lfs f2, float_650_tou2_0000aeb4@l(r3)
		bl randf
		opword 0x48000018
		lis r4, float_550_tou2_0000aeb0@ha
		lis r3, float_850_tou2_0000aeb8@ha
		lfs f1, float_550_tou2_0000aeb0@l(r4)
		lfs f2, float_850_tou2_0000aeb8@l(r3)
		bl randf
		opword 0xFFC00890
		opword 0xFC20E890
		bl sinf
		fmuls f28, f30, f1
		opword 0xFC20E890
		bl cosf
		opword 0x2C160000
		opword 0xEC7E0072
		opword 0x408200B4
		lis r3, double_70_tou2_0000aec8@ha
		opword 0xFC201A10
		lfd f0, double_70_tou2_0000aec8@l(r3)
		opword 0xFC010040
		opword 0x4081FF18
		lis r3, zero_tou2_0000ae40@ha
		lis r5, float_1E05_tou2_0000aed0@ha
		lfs f4, zero_tou2_0000ae40@l(r3)
		lis r4, float_100_tou2_0000ae3c@ha
		lfs f0, float_1E05_tou2_0000aed0@l(r5)
		lis r3, float_neg1_tou2_0000aea0@ha
		opword 0xFC20E090
		lfs f2, float_100_tou2_0000ae3c@l(r4)
		lfs f5, float_neg1_tou2_0000aea0@l(r3)
		opword 0xFCC02090
		stfs f0, _af_pad+12(r1)
		opword 0x38810020
		opword 0x38A1001C
		opword 0x38C10018
		opword 0x38E10014
		opword 0x39010010
		opword 0x3921000C
		opword 0x39410008
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x4182FEC0
		lis r3, zero_tou2_0000ae40@ha
		opword 0xC001001C
		lfs f1, zero_tou2_0000ae40@l(r3)
		opword 0xFC010000
		opword 0x4082FEAC
		opword 0xC0010020
		opword 0xFC400890
		opword 0x807C000C
		opword 0xD003000C
		opword 0xC0010018
		opword 0x807C000C
		opword 0xD003002C
		opword 0xC0610020
		opword 0xC0810018
		bl angleABf
		opword 0xD03C0004
		opword 0x48000124
		lis r3, zero_tou2_0000ae40@ha
		lis r5, float_1E05_tou2_0000aed0@ha
		lfs f4, zero_tou2_0000ae40@l(r3)
		lis r4, float_500_tou2_0000aeac@ha
		lfs f0, float_1E05_tou2_0000aed0@l(r5)
		lis r3, float_neg1_tou2_0000aea0@ha
		opword 0xFC20E090
		lfs f2, float_500_tou2_0000aeac@l(r4)
		lfs f5, float_neg1_tou2_0000aea0@l(r3)
		opword 0xFCC02090
		opword 0xD0010014
		opword 0x38810020
		opword 0x38A1001C
		opword 0x38C10018
		opword 0x38E10014
		opword 0x39010010
		opword 0x3921000C
		opword 0x39410008
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x4182FE24
		opword 0xC0210020
		lis r3, float_570_tou2_0000aed4@ha
		opword 0x809C000C
		lfs f0, float_570_tou2_0000aed4@l(r3)
		opword 0xD024000C
		opword 0xC021001C
		opword 0x807C000C
		opword 0xD023001C
		opword 0xC0210018
		opword 0x807C000C
		opword 0xD023002C
		opword 0xC0210018
		opword 0xFC010040
		opword 0x40810078
		opword 0xC0610020
		lis r3, float_40_tou2_0000aed8@ha
		lfs f0, float_40_tou2_0000aed8@l(r3)
		opword 0xFC201A10
		opword 0xFC010040
		opword 0x40810060
		lis r3, float_60_tou2_0000ae84@ha
		lfs f0, float_60_tou2_0000ae84@l(r3)
		opword 0xFC010040
		opword 0x40800050
		lis r3, zero_tou2_0000ae40@ha
		opword 0x80BC000C
		lfs f0, zero_tou2_0000ae40@l(r3)
		opword 0xC045000C
		opword 0xFC030040
		opword 0x4081000C
		opword 0x3800FFF1
		opword 0x48000008
		opword 0x3800000F
		opword 0x6C038000
		opword 0x3C004330
		opword 0x90610034
		lis r4, double_to_int_tou2_0000aee0@ha
		lfd f1, double_to_int_tou2_0000aee0@l(r4)
		opword 0x90010030
		opword 0xC8010030
		opword 0xEC000828
		opword 0xEC02002A
		opword 0xD005000C
		lis r3, zero_tou2_0000ae40@ha
		opword 0xC0610020
		lfs f1, zero_tou2_0000ae40@l(r3)
		opword 0xC0810018
		opword 0xFC400890
		bl angleABf
		opword 0xD03C0004
		opword 0x80780000
		opword 0x7F24CB78
		opword 0x3863011C
		bl strcmp
		opword 0x2C030000
		opword 0x41820028
		opword 0x809C000C
		lis r3, float_350_tou2_0000aedc@ha
		lfs f0, float_350_tou2_0000aedc@l(r3)
		opword 0xC024002C
		opword 0xFC010040
		opword 0x40810010
		opword 0x801C0000
		opword 0x5400003C
		opword 0x901C0000
		opword 0x807C000C
		opword 0xC003001C
		opword 0xFC1F0000
		opword 0x41820010
		opword 0xA01B0000
		opword 0x60000001
		opword 0xB01B0000
		opword 0x809C000C
		opword 0x386003E8
		opword 0x801A0000
		opword 0x80BA0004
		opword 0x90010024
		opword 0xC004000C
		opword 0x801A0008
		opword 0xD0010024
		opword 0xC024001C
		opword 0x90A10028
		opword 0xC004002C
		opword 0x9001002C
		opword 0x80010024
		opword 0xD0210028
		opword 0xD001002C
		opword 0x80810028
		opword 0x901B0004
		opword 0x8001002C
		opword 0x909B0008
		opword 0x901B000C
		bl irand
		opword 0x5460F002
		opword 0x54630FFE
		opword 0x7C030050
		opword 0x5400103E
		opword 0x7C001A14
		opword 0x2C000002
		opword 0x4182005C
		opword 0x40800014
		opword 0x2C000000
		opword 0x41820018
		opword 0x40800030
		opword 0x4800007C
		opword 0x2C000004
		opword 0x40800074
		opword 0x48000058
		lis r3, tou_03_str_00000000@ha
		lis r5, tou_03_str_0000000C@ha
		addi r4, r3, tou_03_str_00000000@l
		opword 0x7F63DB78
		addi r5, r5, tou_03_str_0000000C@l
		bl pose_change
		opword 0x48000054
		lis r3, tou_03_str_00000014@ha
		lis r5, tou_03_str_00000020@ha
		addi r4, r3, tou_03_str_00000014@l
		opword 0x7F63DB78
		addi r5, r5, tou_03_str_00000020@l
		bl pose_change
		opword 0x48000038
		lis r3, tou_03_str_00000028@ha
		lis r5, tou_03_str_00000030@ha
		addi r4, r3, tou_03_str_00000028@l
		opword 0x7F63DB78
		addi r5, r5, tou_03_str_00000030@l
		bl pose_change
		opword 0x4800001C
		lis r3, tou_03_str_00000034@ha
		lis r5, tou_03_str_00000040@ha
		addi r4, r3, tou_03_str_00000034@l
		opword 0x7F63DB78
		addi r5, r5, tou_03_str_00000040@l
		bl pose_change
		opword 0x3BBD0001
		opword 0x3B9C0020
		opword 0x3B7B0020
		opword 0x807E0000
		opword 0x80030004
		opword 0x7C1D0000
		opword 0x4180FBD8
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

EVT_BEGIN(evt_kyaku)
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
    CALL(evt_npc_entry, STRING(((char*)tou_03_str_00000054)), STRING(((char*)tou_03_str_00000000)))
    CALL(evt_npc_entry, STRING(((char*)tou_03_str_0000005C)), STRING(((char*)tou_03_str_00000014)))
    CALL(evt_npc_entry, STRING(((char*)tou_03_str_00000064)), STRING(((char*)tou_03_str_00000028)))
    CALL(evt_npc_entry, STRING(((char*)tou_03_str_0000006C)), STRING(((char*)tou_03_str_00000034)))
    CALL(evt_npc_set_tribe, STRING(((char*)tou_03_str_00000054)), STRING(((char*)tou_03_str_00000074)))
    CALL(evt_npc_set_tribe, STRING(((char*)tou_03_str_0000005C)), STRING(((char*)tou_03_str_00000080)))
    CALL(evt_npc_set_tribe, STRING(((char*)tou_03_str_00000064)), STRING(((char*)tou_03_str_0000008C)))
    CALL(evt_npc_set_tribe, STRING(((char*)tou_03_str_0000006C)), STRING(((char*)tou_03_str_00000094)))
    CALL(evt_npc_set_ry, STRING(((char*)tou_03_str_00000054)), 90)
    CALL(evt_npc_set_ry, STRING(((char*)tou_03_str_0000005C)), 90)
    CALL(evt_npc_set_ry, STRING(((char*)tou_03_str_00000064)), 270)
    CALL(evt_npc_set_ry, STRING(((char*)tou_03_str_0000006C)), 270)
#endif
    CALL(evt_bero_get_entername, LW(0))
#ifdef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000000A0)))
        CALL(evt_npc_set_position, STRING(((char*)str_00000054)), -40, 120, 680)
        CALL(evt_npc_set_position, STRING(((char*)str_0000005C)), -15, 120, 670)
        CALL(evt_npc_set_position, STRING(((char*)str_00000064)), 15, 120, 680)
        CALL(evt_npc_set_position, STRING(((char*)str_0000006C)), 40, 120, 670)
#endif
#ifndef NONMATCHING
    IF_STR_EQUAL(LW(0), STRING(((char*)tou_03_str_000000A0)))
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000054)), -40, 120, 680)
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000005C)), -15, 120, 670)
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000064)), 15, 120, 680)
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000006C)), 40, 120, 670)
#endif
        ELSE
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_00000054)), -50, 0, 370)
        CALL(evt_npc_set_position, STRING(((char*)str_0000005C)), -20, 0, 360)
        CALL(evt_npc_set_position, STRING(((char*)str_00000064)), 20, 0, 370)
        CALL(evt_npc_set_position, STRING(((char*)str_0000006C)), 50, 0, 360)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000054)), -50, 0, 370)
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000005C)), -20, 0, 360)
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000064)), 20, 0, 370)
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000006C)), 50, 0, 360)
#endif
    END_IF
#ifdef NONMATCHING
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00000054)), 1073743360)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_0000005C)), 1073743360)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00000064)), 1073743360)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_0000006C)), 1073743360)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_00000054)), 1073743360)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_0000005C)), 1073743360)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_00000064)), 1073743360)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_0000006C)), 1073743360)
#endif
    CALL(evt_ext_entry, 1000, PTR(ext_kyaku_data), PTR(ext_kyaku_init), PTR(ext_kyaku_main), PTR(ext_kyaku_dispent))
#ifdef NONMATCHING
    CALL(evt_hitobj_onoff, STRING(((char*)str_000000AC)), 1, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_hitobj_onoff, STRING(((char*)tou_03_str_000000AC)), 1, 0)
#endif
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
#ifdef NONMATCHING
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
#endif
#ifndef NONMATCHING
    MULTIPLY_FLOAT(LW(0), FLOAT((0.5f)))
#endif
    CALL(evt_mapobj_rotate, 1, LW(8), LW(0), 0, 0)
    CALL(evt_mapobj_rotate, 1, LW(9), LW(0), 0, 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000000B8)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_000000B8)), LW(0), LW(1), LW(2), 0)
#endif
    RETURN
EVT_END()

EVT_BEGIN(close_main)
    CALL(evt_sub_intpl_msec_init, 2, 180, 0, 500)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
#endif
#ifndef NONMATCHING
    MULTIPLY_FLOAT(LW(0), FLOAT((0.5f)))
#endif
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
#ifdef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000C8)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000D4)), 0, LW(0), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_000000C8)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT((-1.0f)))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_000000D4)), 0, LW(0), 0)
#endif
    RETURN
EVT_END()

static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
#ifdef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000C8)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000D4)), 0, LW(0), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_000000C8)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT((-1.0f)))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_000000D4)), 0, LW(0), 0)
#endif
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
#ifdef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000E0)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000EC)), 0, LW(0), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_000000E0)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT((-1.0f)))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_000000EC)), 0, LW(0), 0)
#endif
    RETURN
EVT_END()

static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
#ifdef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000E0)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000EC)), 0, LW(0), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_000000E0)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT((-1.0f)))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_000000EC)), 0, LW(0), 0)
#endif
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
#ifdef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000F8)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000104)), 0, LW(0), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_000000F8)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT((-1.0f)))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_00000104)), 0, LW(0), 0)
#endif
    RETURN
EVT_END()

EVT_BEGIN(s1_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
#ifdef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000F8)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000104)), 0, LW(0), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_000000F8)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT((-1.0f)))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_00000104)), 0, LW(0), 0)
#endif
    RETURN
EVT_END()

EVT_BEGIN(s1_door_open2)
#ifdef NONMATCHING
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000000F8)), LW(0), 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000104)), LW(0), 0, 0)
#endif
#ifndef NONMATCHING
    MULTIPLY_FLOAT(LW(0), FLOAT((0.5f)))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_000000F8)), LW(0), 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_00000104)), LW(0), 0, 0)
#endif
    RETURN
EVT_END()

static EVT_BEGIN(s1_open)
    BEGIN_INLINE_EVENT
        CALL(evt_bero_exec_wait, 65536)
#ifdef NONMATCHING
        SET_VALUE(LW(8), STRING(((char*)str_000000F8)))
        SET_VALUE(LW(9), STRING(((char*)str_00000104)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(8), STRING(((char*)tou_03_str_000000F8)))
        SET_VALUE(LW(9), STRING(((char*)tou_03_str_00000104)))
#endif
        CALL_CHILD(PTR(open_main))
    END_INLINE_EVENT
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(s1_close)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        SET_VALUE(LW(8), STRING(((char*)str_000000F8)))
        SET_VALUE(LW(9), STRING(((char*)str_00000104)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(8), STRING(((char*)tou_03_str_000000F8)))
        SET_VALUE(LW(9), STRING(((char*)tou_03_str_00000104)))
#endif
        CALL_CHILD(PTR(close_main))
    END_INLINE_EVENT
    WAIT_MS(500)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(s2_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
#ifdef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000110)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_0000011C)), 0, LW(0), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_00000110)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT((-1.0f)))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_0000011C)), 0, LW(0), 0)
#endif
    RETURN
EVT_END()

EVT_BEGIN(s2_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
#ifdef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000110)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_0000011C)), 0, LW(0), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_00000110)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT((-1.0f)))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_0000011C)), 0, LW(0), 0)
#endif
    RETURN
EVT_END()

EVT_BEGIN(s2_door_open2)
#ifdef NONMATCHING
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000110)), LW(0), 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_0000011C)), LW(0), 0, 0)
#endif
#ifndef NONMATCHING
    MULTIPLY_FLOAT(LW(0), FLOAT((0.5f)))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_00000110)), LW(0), 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)tou_03_str_0000011C)), LW(0), 0, 0)
#endif
    RETURN
EVT_END()

static EVT_BEGIN(s2_open)
    BEGIN_INLINE_EVENT
        CALL(evt_bero_exec_wait, 65536)
#ifdef NONMATCHING
        SET_VALUE(LW(8), STRING(((char*)str_00000110)))
        SET_VALUE(LW(9), STRING(((char*)str_0000011C)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(8), STRING(((char*)tou_03_str_00000110)))
        SET_VALUE(LW(9), STRING(((char*)tou_03_str_0000011C)))
#endif
        CALL_CHILD(PTR(open_main))
    END_INLINE_EVENT
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(s2_close)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        SET_VALUE(LW(8), STRING(((char*)str_00000110)))
        SET_VALUE(LW(9), STRING(((char*)str_0000011C)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(8), STRING(((char*)tou_03_str_00000110)))
        SET_VALUE(LW(9), STRING(((char*)tou_03_str_0000011C)))
#endif
        CALL_CHILD(PTR(close_main))
    END_INLINE_EVENT
    WAIT_MS(500)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_data[] = {
#ifdef NONMATCHING
    (s32)((char*)str_00000128), 65542, 20000, 100000, 0, 0, -1, (s32)w_open,
    -1, (s32)w_close, (s32)((char*)str_00000130), (s32)((char*)str_00000138), 327685, (s32)w_door_close, (s32)w_door_open, (s32)((char*)str_00000144),
#endif
#ifndef NONMATCHING
    (s32)((char*)tou_03_str_00000128), 65542, 20000, 100000, 0, 0, -1, (s32)w_open,
    -1, (s32)w_close, (s32)((char*)tou_03_str_00000130), (s32)((char*)tou_03_str_00000138), 327685, (s32)w_door_close, (s32)w_door_open, (s32)((char*)tou_03_str_00000144),
#endif
    65542, 20000, 100000, 0, 0, -1, (s32)e_open, -1,
#ifdef NONMATCHING
    (s32)e_close, (s32)((char*)str_00000130), (s32)((char*)str_0000014C), 327685, (s32)e_door_close, (s32)e_door_open, (s32)((char*)str_00000158), 65542,
#endif
#ifndef NONMATCHING
    (s32)e_close, (s32)((char*)tou_03_str_00000130), (s32)((char*)tou_03_str_0000014C), 327685, (s32)e_door_close, (s32)e_door_open, (s32)((char*)tou_03_str_00000158), 65542,
#endif
    20000, 100000, 0, 0, -1, (s32)s1_open, -1, (s32)s1_close,
#ifdef NONMATCHING
    (s32)((char*)str_00000164), (s32)((char*)str_0000014C), 327685, (s32)s1_door_close, (s32)s1_door_open, (s32)((char*)str_000000A0), 65542, 20000,
    100000, 0, 0, -1, (s32)s2_open, -1, (s32)s2_close, (s32)((char*)str_00000164),
    (s32)((char*)str_00000138), 327685, (s32)s2_door_close, (s32)s2_door_open, 0, 0, 0, 0,
#endif
#ifndef NONMATCHING
    (s32)((char*)tou_03_str_00000164), (s32)((char*)tou_03_str_0000014C), 327685, (s32)s1_door_close, (s32)s1_door_open, (s32)((char*)tou_03_str_000000A0), 65542, 20000,
    100000, 0, 0, -1, (s32)s2_open, -1, (s32)s2_close, (s32)((char*)tou_03_str_00000164),
    (s32)((char*)tou_03_str_00000138), 327685, (s32)s2_door_close, (s32)s2_door_open, 0, 0, 0, 0,
#endif
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

s32 evt_tougi[] = {
    131163, (s32)evt_mario_key_onoff, 0, 131163, (s32)evt_party_stop, 0, 131122, -70000000,
#ifdef NONMATCHING
    0, 131163, (s32)evt_bero_get_entername, -30000000, 131084, -30000000, (s32)((char*)str_000000A0), 131122,
#endif
#ifndef NONMATCHING
    0, 131163, (s32)evt_bero_get_entername, -30000000, 131084, -30000000, (s32)((char*)tou_03_str_000000A0), 131122,
#endif
    -70000000, 1, 33, 131096, -70000000, 0, 262235, (s32)evt_mario_set_pos,
    -25, 0, 635, 327771, (s32)evt_party_set_pos, 0, 25, 0,
    635, 262235, (s32)evt_mario_set_dir, 90, 0, 0, 262235, (s32)evt_party_set_dir,
    0, 270, 0, 32, 262235, (s32)evt_mario_set_pos, -25, 120,
    980, 327771, (s32)evt_party_set_pos, 0, 25, 120, 980, 262235,
    (s32)evt_mario_set_dir, 90, 0, 0, 262235, (s32)evt_party_set_dir, 0, 270,
#ifdef NONMATCHING
    0, 33, 131163, (s32)evt_mario_set_dir_npc, (s32)/*"チャンピョン"*/(char*)str_0000016C, 196699, (s32)evt_party_set_dir_npc, 0,
    (s32)/*"相手"*/(char*)str_0000017C, 196699, (s32)evt_set_dir_to_target, (s32)/*"チャンピョン"*/(char*)str_0000016C, (s32)/*"相手"*/(char*)str_0000017C, 589915, (s32)evt_cam3d_evt_set, 0,
#endif
#ifndef NONMATCHING
    0, 33, 131163, (s32)evt_mario_set_dir_npc, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, 196699, (s32)evt_party_set_dir_npc, 0,
    (s32)/*"相手"*/(char*)tou_03_str_0000017C, 196699, (s32)evt_set_dir_to_target, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, (s32)/*"相手"*/(char*)tou_03_str_0000017C, 589915, (s32)evt_cam3d_evt_set, 0,
#endif
    563, 962, 0, 554, 412, 0, 11, 65545,
#ifdef NONMATCHING
    1, 458843, (s32)evt_npc_sound_data_set, (s32)/*"相手"*/(char*)str_0000017C, -250000000, -250000000, -250000000, -250000000,
    (s32)((char*)str_00000184), 131124, -30000000, -230184320, 131096, -70000000, 0, 65630,
#endif
#ifndef NONMATCHING
    1, 458843, (s32)evt_npc_sound_data_set, (s32)/*"相手"*/(char*)tou_03_str_0000017C, -250000000, -250000000, -250000000, -250000000,
    (s32)((char*)tou_03_str_00000184), 131124, -30000000, -230184320, 131096, -70000000, 0, 65630,
#endif
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
#ifdef NONMATCHING
    -1, 65546, 500, 131163, (s32)evt_msg_print_party, (s32)((char*)str_0000019C), 65546, 300,
    131163, (s32)evt_mario_set_dir_npc, (s32)/*"チャンピョン"*/(char*)str_0000016C, 65546, 1000, 589915, (s32)evt_cam3d_evt_set, 85,
#endif
#ifndef NONMATCHING
    -1, 65546, 500, 131163, (s32)evt_msg_print_party, (s32)((char*)tou_03_str_0000019C), 65546, 300,
    131163, (s32)evt_mario_set_dir_npc, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, 65546, 1000, 589915, (s32)evt_cam3d_evt_set, 85,
#endif
    172, 326, 85, 96, -104, 0, 11, 65545,
#ifdef NONMATCHING
    1, 327771, (s32)evt_msg_print, 0, (s32)((char*)str_000001A8), 0, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), 65546,
#endif
#ifndef NONMATCHING
    1, 327771, (s32)evt_msg_print, 0, (s32)((char*)tou_03_str_000001A8), 0, (s32)/*((char*)tou_03_str_0000016C)*/((char*)tou_03_str_0000016C), 65546,
#endif
    300, 589915, (s32)evt_cam3d_evt_set, -85, 172, 326, -85, 96,
#ifdef NONMATCHING
    -104, 1000, 11, 327771, (s32)evt_npc_get_position, (s32)/*"チャンピョン"*/(char*)str_0000016C, -29999990, -29999989,
    -29999988, 262235, (s32)evt_npc_status_onoff, 1, (s32)/*"チャンピョン"*/(char*)str_0000016C, 2, 327771, (s32)evt_npc_get_position,
    (s32)/*"チャンピョン"*/(char*)str_0000016C, -30000000, -29999999, -29999998, 131126, -30000000, 50, 458843,
    (s32)evt_npc_move_position, (s32)/*"チャンピョン"*/(char*)str_0000016C, -30000000, -29999998, 0, -229897600, 1, 327771,
    (s32)evt_npc_set_rotate, (s32)/*"チャンピョン"*/(char*)str_0000016C, 0, 0, -30, 327771, (s32)evt_npc_get_position, (s32)/*"相手"*/(char*)str_0000017C,
#endif
#ifndef NONMATCHING
    -104, 1000, 11, 327771, (s32)evt_npc_get_position, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, -29999990, -29999989,
    -29999988, 262235, (s32)evt_npc_status_onoff, 1, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, 2, 327771, (s32)evt_npc_get_position,
    (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, -30000000, -29999999, -29999998, 131126, -30000000, 50, 458843,
    (s32)evt_npc_move_position, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, -30000000, -29999998, 0, -229897600, 1, 327771,
    (s32)evt_npc_set_rotate, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, 0, 0, -30, 327771, (s32)evt_npc_get_position, (s32)/*"相手"*/(char*)tou_03_str_0000017C,
#endif
    -30000000, -29999999, -29999998, 131125, -29999999, 20, 458843, (s32)evt_npc_jump_position_nohit,
#ifdef NONMATCHING
    (s32)/*"チャンピョン"*/(char*)str_0000016C, -30000000, -29999999, -29999998, 700, -229959040, 393307, (s32)evt_snd_sfxon_3d,
    (s32)((char*)str_000001B4), -30000000, -29999999, -29999998, 0, 983131, (s32)evt_eff, 0,
    (s32)((char*)str_000001CC), 0, -30000000, -29999999, -29999998, -229996928, 10, 0,
#endif
#ifndef NONMATCHING
    (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, -30000000, -29999999, -29999998, 700, -229959040, 393307, (s32)evt_snd_sfxon_3d,
    (s32)((char*)tou_03_str_000001B4), -30000000, -29999999, -29999998, 0, 983131, (s32)evt_eff, 0,
    (s32)((char*)tou_03_str_000001CC), 0, -30000000, -29999999, -29999998, -229996928, 10, 0,
#endif
    0, 0, 0, 0, 0, 107, 327771, (s32)evt_cam_shake,
    4, -229999990, -230000000, 300, 109, 107, 131122, -30000000,
#ifdef NONMATCHING
    -30, 65541, 10, 327771, (s32)evt_npc_set_rotate, (s32)/*"チャンピョン"*/(char*)str_0000016C, 0, 0,
#endif
#ifndef NONMATCHING
    -30, 65541, 10, 327771, (s32)evt_npc_set_rotate, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, 0, 0,
#endif
    -30000000, 131125, -30000000, 3, 65545, 1, 6, 327771,
#ifdef NONMATCHING
    (s32)evt_npc_set_rotate, (s32)/*"チャンピョン"*/(char*)str_0000016C, 0, 0, 0, 109, 107, 458843,
    (s32)evt_npc_sound_data_set, (s32)/*"チャンピョン"*/(char*)str_0000016C, -250000000, -250000000, -250000000, 0, 0, 131125,
    -30000000, 30, 131126, -29999999, 20, 458843, (s32)evt_npc_jump_position_nohit, (s32)/*"チャンピョン"*/(char*)str_0000016C,
#endif
#ifndef NONMATCHING
    (s32)evt_npc_set_rotate, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, 0, 0, 0, 109, 107, 458843,
    (s32)evt_npc_sound_data_set, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, -250000000, -250000000, -250000000, 0, 0, 131125,
    -30000000, 30, 131126, -29999999, 20, 458843, (s32)evt_npc_jump_position_nohit, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C,
#endif
    -30000000, -29999999, -29999998, 300, -229979520, 131125, -30000000, 30,
#ifdef NONMATCHING
    458843, (s32)evt_npc_jump_position_nohit, (s32)/*"チャンピョン"*/(char*)str_0000016C, -30000000, -29999999, -29999998, 300, -229989760,
    458843, (s32)evt_npc_jump_position_nohit, (s32)/*"チャンピョン"*/(char*)str_0000016C, -29999990, -29999989, -29999988, 300, -229989760,
    131163, (s32)evt_npc_sound_data_reset, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), 109, 196699, (s32)evt_npc_set_anim, (s32)/*((char*)str_0000017C)*/((char*)str_0000017C), (s32)((char*)str_000001D0),
    107, 327771, (s32)evt_npc_get_position, (s32)/*"相手"*/(char*)str_0000017C, -30000000, -29999999, -29999998, 131126,
    -30000000, 30, 458843, (s32)evt_npc_jump_position_nohit, (s32)/*"相手"*/(char*)str_0000017C, -30000000, -29999999, -29999998,
    300, -229979520, 131126, -30000000, 30, 458843, (s32)evt_npc_jump_position_nohit, (s32)/*"相手"*/(char*)str_0000017C,
#endif
#ifndef NONMATCHING
    458843, (s32)evt_npc_jump_position_nohit, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, -30000000, -29999999, -29999998, 300, -229989760,
    458843, (s32)evt_npc_jump_position_nohit, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, -29999990, -29999989, -29999988, 300, -229989760,
    131163, (s32)evt_npc_sound_data_reset, (s32)/*((char*)tou_03_str_0000016C)*/((char*)tou_03_str_0000016C), 109, 196699, (s32)evt_npc_set_anim, (s32)/*((char*)tou_03_str_0000017C)*/((char*)tou_03_str_0000017C), (s32)((char*)tou_03_str_000001D0),
    107, 327771, (s32)evt_npc_get_position, (s32)/*"相手"*/(char*)tou_03_str_0000017C, -30000000, -29999999, -29999998, 131126,
    -30000000, 30, 458843, (s32)evt_npc_jump_position_nohit, (s32)/*"相手"*/(char*)tou_03_str_0000017C, -30000000, -29999999, -29999998,
    300, -229979520, 131126, -30000000, 30, 458843, (s32)evt_npc_jump_position_nohit, (s32)/*"相手"*/(char*)tou_03_str_0000017C,
#endif
    -30000000, -29999999, -29999998, 300, -229989760, 109, 327771, (s32)evt_msg_print,
#ifdef NONMATCHING
    0, (s32)((char*)str_000001D4), 0, (s32)/*((char*)str_0000017C)*/((char*)str_0000017C), 589915, (s32)evt_cam3d_evt_set, 65, 172,
#endif
#ifndef NONMATCHING
    0, (s32)((char*)tou_03_str_000001D4), 0, (s32)/*((char*)tou_03_str_0000017C)*/((char*)tou_03_str_0000017C), 589915, (s32)evt_cam3d_evt_set, 65, 172,
#endif
    326, 65, 96, -104, 1000, 11, 131122, -90000000,
#ifdef NONMATCHING
    0, 107, 262235, (s32)evt_npc_status_onoff, 1, (s32)/*"ガンス"*/(char*)str_000001E0, 2, 327771,
    (s32)evt_npc_set_position, (s32)/*"ガンス"*/(char*)str_000001E0, 160, 60, -65, 458843, (s32)evt_npc_move_position, (s32)/*"ガンス"*/(char*)str_000001E0,
    45, -65, 0, -229948800, 1, 458843, (s32)evt_npc_move_position, (s32)/*"ガンス"*/(char*)str_000001E0,
    20, 0, 0, -229948800, 1, 196699, (s32)evt_set_dir_to_target, (s32)/*"ガンス"*/(char*)str_000001E0,
    (s32)/*"チャンピョン"*/(char*)str_0000016C, 131122, -90000000, 1, 109, 65546, 1200, 196699,
    (s32)evt_npc_set_anim, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), (s32)((char*)str_000001E8), 262235, (s32)evt_npc_set_autotalkpose, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), (s32)((char*)str_000001E8), (s32)((char*)str_000001EC),
    327771, (s32)evt_msg_print, 0, (s32)((char*)str_000001F0), 0, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), 65546, 300,
#endif
#ifndef NONMATCHING
    0, 107, 262235, (s32)evt_npc_status_onoff, 1, (s32)/*"ガンス"*/(char*)tou_03_str_000001E0, 2, 327771,
    (s32)evt_npc_set_position, (s32)/*"ガンス"*/(char*)tou_03_str_000001E0, 160, 60, -65, 458843, (s32)evt_npc_move_position, (s32)/*"ガンス"*/(char*)tou_03_str_000001E0,
    45, -65, 0, -229948800, 1, 458843, (s32)evt_npc_move_position, (s32)/*"ガンス"*/(char*)tou_03_str_000001E0,
    20, 0, 0, -229948800, 1, 196699, (s32)evt_set_dir_to_target, (s32)/*"ガンス"*/(char*)tou_03_str_000001E0,
    (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, 131122, -90000000, 1, 109, 65546, 1200, 196699,
    (s32)evt_npc_set_anim, (s32)/*((char*)tou_03_str_0000016C)*/((char*)tou_03_str_0000016C), (s32)((char*)tou_03_str_000001E8), 262235, (s32)evt_npc_set_autotalkpose, (s32)/*((char*)tou_03_str_0000016C)*/((char*)tou_03_str_0000016C), (s32)((char*)tou_03_str_000001E8), (s32)((char*)tou_03_str_000001EC),
    327771, (s32)evt_msg_print, 0, (s32)((char*)tou_03_str_000001F0), 0, (s32)/*((char*)tou_03_str_0000016C)*/((char*)tou_03_str_0000016C), 65546, 300,
#endif
    65541, 0, 131096, -90000000, 1, 7, 33, 65545,
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
    1, 6, 327771, (s32)evt_msg_print, 0, (s32)((char*)tou_03_str_000001FC), 0, (s32)/*((char*)tou_03_str_000001E0)*/((char*)tou_03_str_000001E0),
    65546, 300, 196699, (s32)evt_npc_set_anim, (s32)/*((char*)tou_03_str_000001E0)*/((char*)tou_03_str_000001E0), (s32)((char*)tou_03_str_00000208), 65546, 300,
    196699, (s32)evt_npc_set_anim, (s32)/*((char*)tou_03_str_000001E0)*/((char*)tou_03_str_000001E0), (s32)((char*)tou_03_str_0000020C), 327771, (s32)evt_msg_print, 0, (s32)((char*)tou_03_str_00000210),
    0, (s32)/*((char*)tou_03_str_0000016C)*/((char*)tou_03_str_0000016C), 196699, (s32)evt_npc_set_anim, (s32)/*((char*)tou_03_str_000001E0)*/((char*)tou_03_str_000001E0), (s32)((char*)tou_03_str_0000021C), 65546, 300,
    196699, (s32)evt_npc_set_anim, (s32)/*((char*)tou_03_str_000001E0)*/((char*)tou_03_str_000001E0), (s32)((char*)tou_03_str_00000220), 196699, (s32)evt_npc_set_anim, (s32)/*((char*)tou_03_str_0000016C)*/((char*)tou_03_str_0000016C), (s32)((char*)tou_03_str_00000224),
    262235, (s32)evt_npc_set_autotalkpose, (s32)/*((char*)tou_03_str_0000016C)*/((char*)tou_03_str_0000016C), (s32)((char*)tou_03_str_00000220), (s32)((char*)tou_03_str_00000228), 65627, (s32)evt_msg_continue, 65546,
    1500, 196699, (s32)evt_npc_set_anim, (s32)/*((char*)tou_03_str_0000016C)*/((char*)tou_03_str_0000016C), (s32)((char*)tou_03_str_0000022C), 65546, 200, 196699,
    (s32)evt_npc_set_anim, (s32)/*((char*)tou_03_str_0000016C)*/((char*)tou_03_str_0000016C), (s32)((char*)tou_03_str_00000230), 196699, (s32)evt_npc_entry, (s32)/*((char*)tou_03_str_00000234)*/((char*)tou_03_str_00000234), (s32)((char*)tou_03_str_0000023C), 327771,
    (s32)evt_npc_get_position, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, -30000000, -29999999, -29999998, 131126, -30000000, 5,
    131125, -29999999, 65, 327771, (s32)evt_npc_set_position, (s32)/*"ベルト"*/(char*)tou_03_str_00000234, -30000000, -29999999,
    -29999998, 196699, (s32)evt_npc_set_anim, (s32)/*((char*)tou_03_str_00000234)*/((char*)tou_03_str_00000234), (s32)((char*)tou_03_str_00000248), 131125, -29999998, 10,
    983131, (s32)evt_eff, 0, (s32)((char*)tou_03_str_0000024C), 9, -30000000, -29999999, -29999998,
#endif
    -229999232, 0, 0, 0, 0, 0, 0, 0,
#ifdef NONMATCHING
    393307, (s32)evt_snd_sfxon_3d, (s32)((char*)str_00000258), -30000000, -29999999, -29999998, 0, 65546,
#endif
#ifndef NONMATCHING
    393307, (s32)evt_snd_sfxon_3d, (s32)((char*)tou_03_str_00000258), -30000000, -29999999, -29999998, 0, 65546,
#endif
    2000, 131096, -70000000, 0, 589915, (s32)evt_cam3d_evt_set, 0, 95,
    692, 0, 43, 397, 0, 11, 32, 589915,
    (s32)evt_cam3d_evt_set, 0, 218, 1037, 0, 165, 742, 0,
#ifdef NONMATCHING
    11, 33, 65545, 1, 131163, (s32)evt_mario_set_dir_npc, (s32)/*"チャンピョン"*/(char*)str_0000016C, 196699,
    (s32)evt_party_set_dir_npc, 0, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), 786523, (s32)evt_eff_fukidashi, 3, (s32)((char*)str_00000270), 0,
#endif
#ifndef NONMATCHING
    11, 33, 65545, 1, 131163, (s32)evt_mario_set_dir_npc, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, 196699,
    (s32)evt_party_set_dir_npc, 0, (s32)/*((char*)tou_03_str_0000016C)*/((char*)tou_03_str_0000016C), 786523, (s32)evt_eff_fukidashi, 3, (s32)((char*)tou_03_str_00000270), 0,
#endif
    0, 0, 0, 0, 0, 0, 0, 0,
#ifdef NONMATCHING
    65546, 1000, 131163, (s32)evt_msg_print_party, (s32)((char*)str_00000274), 65546, 300, 589915,
#endif
#ifndef NONMATCHING
    65546, 1000, 131163, (s32)evt_msg_print_party, (s32)((char*)tou_03_str_00000274), 65546, 300, 589915,
#endif
    (s32)evt_cam3d_evt_set, 80, 67, 225, 80, 172, -161, 0,
    11, 65545, 1, 65546, 1000, 327771, (s32)evt_msg_toge, 1,
#ifdef NONMATCHING
    0, 0, 0, 131163, (s32)evt_msg_print_party, (s32)((char*)str_00000280), 65546, 300,
#endif
#ifndef NONMATCHING
    0, 0, 0, 131163, (s32)evt_msg_print_party, (s32)((char*)tou_03_str_00000280), 65546, 300,
#endif
    393307, (s32)evt_fade_set_mapchange_type, 0, 2, 500, 1, 500, 131122,
#ifdef NONMATCHING
    -129997626, 1, 131096, -70000000, 0, 196699, (s32)evt_bero_mapchange, (s32)((char*)str_00000164),
    (s32)((char*)str_0000014C), 32, 196699, (s32)evt_bero_mapchange, (s32)((char*)str_00000164), (s32)((char*)str_00000138), 33, 2,
#endif
#ifndef NONMATCHING
    -129997626, 1, 131096, -70000000, 0, 196699, (s32)evt_bero_mapchange, (s32)((char*)tou_03_str_00000164),
    (s32)((char*)tou_03_str_0000014C), 32, 196699, (s32)evt_bero_mapchange, (s32)((char*)tou_03_str_00000164), (s32)((char*)tou_03_str_00000138), 33, 2,
#endif
    1,
};

EVT_BEGIN(init_kinosikowa)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 172)
#ifdef NONMATCHING
        CALL(evt_npc_set_tribe, STRING(((char*)str_0000028C)), STRING(((char*)str_00000298)))
        CALL(evt_npc_set_stay_anim, STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_tribe, STRING(((char*)tou_03_str_0000028C)), STRING(((char*)tou_03_str_00000298)))
        CALL(evt_npc_set_stay_anim, STRING(((char*)tou_03_str_0000028C)))
#endif
    END_IF
    RETURN
EVT_END()

static s32 npcEnt[] = {
#ifdef NONMATCHING
    (s32)/*"ガンス"*/(char*)str_000001E0, 1073743360, 0, 0, 0, 0, 0, 0,
#endif
#ifndef NONMATCHING
    (s32)/*"ガンス"*/(char*)tou_03_str_000001E0, 1073743360, 0, 0, 0, 0, 0, 0,
#endif
    0, 0, 0, 0, 0, 0, 0, 0,
#ifdef NONMATCHING
    0, 0, 0, 0, 0, 0, 0, (s32)/*"キノシコワ"*/(char*)str_0000028C,
#endif
#ifndef NONMATCHING
    0, 0, 0, 0, 0, 0, 0, (s32)/*"キノシコワ"*/(char*)tou_03_str_0000028C,
#endif
    1073743360, 0, (s32)init_kinosikowa, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
#ifdef NONMATCHING
    0, 0, 0, 0, 0, 0, (s32)/*"マッチョガンス"*/(char*)str_000002B0, 1073743360,
#endif
#ifndef NONMATCHING
    0, 0, 0, 0, 0, 0, (s32)/*"マッチョガンス"*/(char*)tou_03_str_000002B0, 1073743360,
#endif
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
#ifdef NONMATCHING
    0, 0, 0, 0, 0, (s32)/*"キノシチョフ"*/(char*)str_000002C0, 1073743360, 0,
#endif
#ifndef NONMATCHING
    0, 0, 0, 0, 0, (s32)/*"キノシチョフ"*/(char*)tou_03_str_000002C0, 1073743360, 0,
#endif
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

EVT_BEGIN(evt_damage_pose)
    CALL(evt_mario_dispflag_onoff, 1, 2)
#ifdef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)str_000002D0)))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_000002D0)))
#endif
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_000002D8)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)tou_03_str_000002D8)))
#endif
        CASE_EQUAL(2)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_000002E0)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)tou_03_str_000002E0)))
#endif
        CASE_EQUAL(3)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_000002E8)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)tou_03_str_000002E8)))
#endif
        CASE_EQUAL(4)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_000002EC)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)tou_03_str_000002EC)))
#endif
        CASE_EQUAL(5)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_000002F4)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)tou_03_str_000002F4)))
#endif
        CASE_EQUAL(6)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_000002FC)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)tou_03_str_000002FC)))
#endif
        CASE_EQUAL(7)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000304)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)tou_03_str_00000304)))
#endif
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(evt_kime_pose)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_0000030C)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)tou_03_str_0000030C)))
#endif
        CASE_EQUAL(2)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000314)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)tou_03_str_00000314)))
#endif
        CASE_EQUAL(3)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_0000031C)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)tou_03_str_0000031C)))
#endif
        CASE_EQUAL(4)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000320)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)tou_03_str_00000320)))
#endif
        CASE_EQUAL(5)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000328)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)tou_03_str_00000328)))
#endif
        CASE_EQUAL(6)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000330)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)tou_03_str_00000330)))
#endif
        CASE_EQUAL(7)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000338)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)tou_03_str_00000338)))
#endif
    END_SWITCH
    RETURN
EVT_END()

s32 npc_entry[] = {
#ifdef NONMATCHING
    131098, -170000000, 128, 196699, (s32)evt_npc_entry, (s32)/*((char*)str_0000016C)*/((char*)str_0000016C), (s32)((char*)str_0000023C), 327771,
    (s32)evt_npc_set_position, (s32)/*"チャンピョン"*/(char*)str_0000016C, 80, 60, 0, 196699, (s32)evt_npc_entry, (s32)/*"相手"*/(char*)str_0000017C,
    (s32)((char*)str_00000340), 327771, (s32)evt_npc_set_position, (s32)/*((char*)str_0000017C)*/((char*)str_0000017C), -80, 60, 0, 196699,
    (s32)evt_npc_set_tribe, (s32)/*"チャンピョン"*/(char*)str_0000016C, (s32)/*"ブレッドハート"*/(char*)str_00000350, 196699, (s32)evt_npc_set_tribe, (s32)/*"相手"*/(char*)str_0000017C, (s32)/*"トゲノコエース"*/(char*)str_00000360, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)/*"チャンピョン"*/(char*)str_0000016C, 1073743360, 262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"相手"*/(char*)str_0000017C,
    1073741824, 196699, (s32)evt_npc_set_ry, (s32)/*"チャンピョン"*/(char*)str_0000016C, 270, 196699, (s32)evt_npc_set_ry, (s32)/*"相手"*/(char*)str_0000017C,
#endif
#ifndef NONMATCHING
    131098, -170000000, 128, 196699, (s32)evt_npc_entry, (s32)/*((char*)tou_03_str_0000016C)*/((char*)tou_03_str_0000016C), (s32)((char*)tou_03_str_0000023C), 327771,
    (s32)evt_npc_set_position, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, 80, 60, 0, 196699, (s32)evt_npc_entry, (s32)/*"相手"*/(char*)tou_03_str_0000017C,
    (s32)((char*)tou_03_str_00000340), 327771, (s32)evt_npc_set_position, (s32)/*((char*)tou_03_str_0000017C)*/((char*)tou_03_str_0000017C), -80, 60, 0, 196699,
    (s32)evt_npc_set_tribe, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, (s32)/*"ブレッドハート"*/(char*)tou_03_str_00000350, 196699, (s32)evt_npc_set_tribe, (s32)/*"相手"*/(char*)tou_03_str_0000017C, (s32)/*"トゲノコエース"*/(char*)tou_03_str_00000360, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, 1073743360, 262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"相手"*/(char*)tou_03_str_0000017C,
    1073741824, 196699, (s32)evt_npc_set_ry, (s32)/*"チャンピョン"*/(char*)tou_03_str_0000016C, 270, 196699, (s32)evt_npc_set_ry, (s32)/*"相手"*/(char*)tou_03_str_0000017C,
#endif
    90, 2, 33, 131122, -70000000, 0, 65570, -170000000,
    131119, 128, 162, 131122, -70000000, 1, 65574, 164,
    42, 131122, -70000000, 1, 49, 131096, -70000000, 1,
    131096, -129997612, 0, 196699, (s32)evt_sub_random, 10000, -29999990, 131098,
    -29999990, 5000, 65541, 0, 196699, (s32)evt_sub_random, 3000, -29999990,
#ifdef NONMATCHING
    65570, -29999990, 65574, 1000, 131122, -30000000, (s32)((char*)str_00000370), 131122,
    -29999999, (s32)/*((char*)str_0000037C)*/((char*)str_0000037C), 65574, 2000, 131122, -30000000, (s32)((char*)str_00000384), 131122,
    -29999999, (s32)/*((char*)str_00000390)*/((char*)str_00000390), 42, 131122, -30000000, (s32)((char*)str_0000039C), 131122, -29999999,
    (s32)/*"モノクロクロクモーン"*/(char*)str_000003A8, 49, 196699, (s32)evt_sub_random, 3000, -29999990, 65570, -29999990,
    65574, 1000, 131122, -29999998, (s32)((char*)str_00000370), 131122, -29999997, (s32)/*((char*)str_0000037C)*/((char*)str_0000037C),
    65574, 2000, 131122, -29999998, (s32)((char*)str_00000384), 131122, -29999997, (s32)/*((char*)str_00000390)*/((char*)str_00000390),
    42, 131122, -29999998, (s32)((char*)str_0000039C), 131122, -29999997, (s32)/*((char*)str_000003A8)*/((char*)str_000003A8), 49,
#endif
#ifndef NONMATCHING
    65570, -29999990, 65574, 1000, 131122, -30000000, (s32)((char*)tou_03_str_00000370), 131122,
    -29999999, (s32)/*((char*)tou_03_str_0000037C)*/((char*)tou_03_str_0000037C), 65574, 2000, 131122, -30000000, (s32)((char*)tou_03_str_00000384), 131122,
    -29999999, (s32)/*((char*)tou_03_str_00000390)*/((char*)tou_03_str_00000390), 42, 131122, -30000000, (s32)((char*)tou_03_str_0000039C), 131122, -29999999,
    (s32)/*"モノクロクロクモーン"*/(char*)tou_03_str_000003A8, 49, 196699, (s32)evt_sub_random, 3000, -29999990, 65570, -29999990,
    65574, 1000, 131122, -29999998, (s32)((char*)tou_03_str_00000370), 131122, -29999997, (s32)/*((char*)tou_03_str_0000037C)*/((char*)tou_03_str_0000037C),
    65574, 2000, 131122, -29999998, (s32)((char*)tou_03_str_00000384), 131122, -29999997, (s32)/*((char*)tou_03_str_00000390)*/((char*)tou_03_str_00000390),
    42, 131122, -29999998, (s32)((char*)tou_03_str_0000039C), 131122, -29999997, (s32)/*((char*)tou_03_str_000003A8)*/((char*)tou_03_str_000003A8), 49,
#endif
    131085, -30000000, -29999998, 7, 33, 6, 32, 65541,
    0, 196699, (s32)evt_sub_random, 4000, -29999990, 65570, -29999990, 65574,
#ifdef NONMATCHING
    1000, 131122, -30000000, (s32)((char*)str_000003C0), 131122, -29999999, (s32)/*((char*)str_000003CC)*/((char*)str_000003CC), 65574,
    2000, 131122, -30000000, (s32)((char*)str_000003D8), 131122, -29999999, (s32)/*((char*)str_000003E4)*/((char*)str_000003E4), 65574,
    3000, 131122, -30000000, (s32)((char*)str_000003F4), 131122, -29999999, (s32)/*((char*)str_00000404)*/((char*)str_00000404), 42,
    131122, -30000000, (s32)((char*)str_00000414), 131122, -29999999, (s32)/*((char*)str_00000420)*/((char*)str_00000420), 49, 196699,
#endif
#ifndef NONMATCHING
    1000, 131122, -30000000, (s32)((char*)tou_03_str_000003C0), 131122, -29999999, (s32)/*((char*)tou_03_str_000003CC)*/((char*)tou_03_str_000003CC), 65574,
    2000, 131122, -30000000, (s32)((char*)tou_03_str_000003D8), 131122, -29999999, (s32)/*((char*)tou_03_str_000003E4)*/((char*)tou_03_str_000003E4), 65574,
    3000, 131122, -30000000, (s32)((char*)tou_03_str_000003F4), 131122, -29999999, (s32)/*((char*)tou_03_str_00000404)*/((char*)tou_03_str_00000404), 42,
    131122, -30000000, (s32)((char*)tou_03_str_00000414), 131122, -29999999, (s32)/*((char*)tou_03_str_00000420)*/((char*)tou_03_str_00000420), 49, 196699,
#endif
    (s32)evt_sub_random, 4000, -29999990, 65570, -29999990, 65574, 1000, 131122,
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
    -29999998, (s32)((char*)tou_03_str_000003C0), 131122, -29999997, (s32)/*((char*)tou_03_str_000003CC)*/((char*)tou_03_str_000003CC), 65574, 2000, 131122,
    -29999998, (s32)((char*)tou_03_str_000003D8), 131122, -29999997, (s32)/*((char*)tou_03_str_000003E4)*/((char*)tou_03_str_000003E4), 65574, 3000, 131122,
    -29999998, (s32)((char*)tou_03_str_000003F4), 131122, -29999997, (s32)/*((char*)tou_03_str_00000404)*/((char*)tou_03_str_00000404), 42, 131122, -29999998,
    (s32)((char*)tou_03_str_00000414), 131122, -29999997, (s32)/*((char*)tou_03_str_00000420)*/((char*)tou_03_str_00000420), 49, 131085, -30000000, -29999998,
    7, 33, 6, 33, 196699, (s32)evt_npc_entry, (s32)/*"選手1"*/(char*)tou_03_str_00000434, -30000000,
    327771, (s32)evt_npc_set_position, (s32)/*"選手1"*/(char*)tou_03_str_00000434, -80, 60, 0, 196699, (s32)evt_npc_entry,
    (s32)/*"選手2"*/(char*)tou_03_str_0000043C, -29999998, 327771, (s32)evt_npc_set_position, (s32)/*"選手2"*/(char*)tou_03_str_0000043C, 80, 60, 0,
    196699, (s32)evt_npc_set_tribe, (s32)/*"選手1"*/(char*)tou_03_str_00000434, -29999999, 196699, (s32)evt_npc_set_tribe, (s32)/*"選手2"*/(char*)tou_03_str_0000043C, -29999997,
    262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"選手1"*/(char*)tou_03_str_00000434, 1073743392, 262235, (s32)evt_npc_flag_onoff, 1,
    (s32)/*"選手2"*/(char*)tou_03_str_0000043C, 1073743392, 196699, (s32)evt_npc_set_ry, (s32)/*"選手1"*/(char*)tou_03_str_00000434, 90, 196699, (s32)evt_npc_set_ry,
    (s32)/*"選手2"*/(char*)tou_03_str_0000043C, 270, 131084, -29999999, (s32)/*"バーストワンワン"*/(char*)tou_03_str_00000420, 196699, (s32)evt_npc_set_anim, (s32)/*"選手1"*/(char*)tou_03_str_00000434,
    (s32)((char*)tou_03_str_00000444), 131122, -30000000, 6, 65628, (s32)burst_chain_entry, 33, 131084,
    -29999997, (s32)/*((char*)tou_03_str_00000420)*/((char*)tou_03_str_00000420), 196699, (s32)evt_npc_set_anim, (s32)/*((char*)tou_03_str_00000434)*/((char*)tou_03_str_00000434), (s32)((char*)tou_03_str_00000444), 131122, -30000000,
#endif
    7, 65628, (s32)burst_chain_entry, 33, 2, 33, 33, 131096,
    -129997612, 1, 196699, (s32)evt_tou_get_fighter_num, -169999499, -30000000, 131122, -29999999,
    0, 65541, 0, 131096, -30000000, -29999999, 7, 33,
    131096, -169999499, 11, 65570, -29999999, 65572, 0, 131122,
#ifdef NONMATCHING
    -29999998, (s32)/*"敵３"*/(char*)str_0000044C, 65572, 1, 131122, -29999998, (s32)/*"敵４"*/(char*)str_00000454, 65572,
    2, 131122, -29999998, (s32)/*"敵１"*/(char*)str_0000045C, 65572, 3, 131122, -29999998,
    (s32)/*"敵２"*/(char*)str_00000464, 65572, 4, 131122, -29999998, (s32)/*"敵５"*/(char*)str_0000046C, 42, 65649,
    (s32)/*"おかしい"*/(char*)str_00000474, 7, 49, 32, 65570, -29999999, 65572, 0,
    131122, -29999998, (s32)/*"敵１"*/(char*)str_0000045C, 65572, 1, 131122, -29999998, (s32)/*"敵２"*/(char*)str_00000464,
    65572, 2, 131122, -29999998, (s32)/*"敵３"*/(char*)str_0000044C, 65572, 3, 131122,
    -29999998, (s32)/*"敵４"*/(char*)str_00000454, 65572, 4, 131122, -29999998, (s32)/*"敵５"*/(char*)str_0000046C, 42,
    65649, (s32)/*"おかしい"*/(char*)str_00000474, 7, 49, 33, 327771, (s32)evt_tou_get_fighter_tribe, -169999499,
#endif
#ifndef NONMATCHING
    -29999998, (s32)/*"敵３"*/(char*)tou_03_str_0000044C, 65572, 1, 131122, -29999998, (s32)/*"敵４"*/(char*)tou_03_str_00000454, 65572,
    2, 131122, -29999998, (s32)/*"敵１"*/(char*)tou_03_str_0000045C, 65572, 3, 131122, -29999998,
    (s32)/*"敵２"*/(char*)tou_03_str_00000464, 65572, 4, 131122, -29999998, (s32)/*"敵５"*/(char*)tou_03_str_0000046C, 42, 65649,
    (s32)/*"おかしい"*/(char*)tou_03_str_00000474, 7, 49, 32, 65570, -29999999, 65572, 0,
    131122, -29999998, (s32)/*"敵１"*/(char*)tou_03_str_0000045C, 65572, 1, 131122, -29999998, (s32)/*"敵２"*/(char*)tou_03_str_00000464,
    65572, 2, 131122, -29999998, (s32)/*"敵３"*/(char*)tou_03_str_0000044C, 65572, 3, 131122,
    -29999998, (s32)/*"敵４"*/(char*)tou_03_str_00000454, 65572, 4, 131122, -29999998, (s32)/*"敵５"*/(char*)tou_03_str_0000046C, 42,
    65649, (s32)/*"おかしい"*/(char*)tou_03_str_00000474, 7, 49, 33, 327771, (s32)evt_tou_get_fighter_tribe, -169999499,
#endif
    -29999999, -29999997, -29999996, 196699, (s32)evt_npc_entry, -29999998, -29999997, 196699,
    (s32)evt_npc_set_tribe, -29999998, -29999996, 327771, (s32)evt_npc_set_position, -29999998, 0, -1000,
    0, 262235, (s32)evt_npc_flag_onoff, 1, -29999998, 1073743360, 196699, (s32)evt_npc_set_ry,
    -29999998, 270, 107, 196699, (s32)evt_npc_get_height, -29999998, -30000000, 131099,
    -30000000, 50, 196699, (s32)evt_npc_set_height, -29999998, 50, 33, 109,
    107, 131096, -169999499, 2, 65570, -29999999, 65572, 0,
    131122, -30000000, 0, 65628, (s32)burst_chain_entry, 65572, 1, 131122,
    -30000000, 1, 65628, (s32)burst_chain_entry, 49, 33, 109, 131125,
    -29999999, 1, 6, 262235, (s32)evt_tou_get_fighter_info_28_text_3E58, -169999499, -30000000, -29999999,
#ifdef NONMATCHING
    131096, -29999999, 10, 327771, (s32)evt_npc_set_scale, (s32)/*"敵１"*/(char*)str_0000045C, -229998464, -229998464,
    -229998976, 327771, (s32)evt_npc_set_scale, (s32)/*"敵２"*/(char*)str_00000464, -229998464, -229998464, -229998976, 458843,
    (s32)evt_npc_sound_data_set, (s32)/*((char*)str_0000045C)*/((char*)str_0000045C), (s32)((char*)str_00000480), (s32)((char*)str_00000498), -250000000, -250000000, -250000000, 458843,
    (s32)evt_npc_sound_data_set, (s32)/*((char*)str_00000464)*/((char*)str_00000464), (s32)((char*)str_00000480), (s32)((char*)str_00000498), -250000000, -250000000, -250000000, 33,
#endif
#ifndef NONMATCHING
    131096, -29999999, 10, 327771, (s32)evt_npc_set_scale, (s32)/*"敵１"*/(char*)tou_03_str_0000045C, -229998464, -229998464,
    -229998976, 327771, (s32)evt_npc_set_scale, (s32)/*"敵２"*/(char*)tou_03_str_00000464, -229998464, -229998464, -229998976, 458843,
    (s32)evt_npc_sound_data_set, (s32)/*((char*)tou_03_str_0000045C)*/((char*)tou_03_str_0000045C), (s32)((char*)tou_03_str_00000480), (s32)((char*)tou_03_str_00000498), -250000000, -250000000, -250000000, 458843,
    (s32)evt_npc_sound_data_set, (s32)/*((char*)tou_03_str_00000464)*/((char*)tou_03_str_00000464), (s32)((char*)tou_03_str_00000480), (s32)((char*)tou_03_str_00000498), -250000000, -250000000, -250000000, 33,
#endif
    131122, -70000000, 0, 131163, (s32)evt_tou_get_ranking_28_text_4048, -30000000, 131096, -30000000,
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
    6, 196699, (s32)evt_npc_entry, (s32)/*((char*)tou_03_str_000004B0)*/((char*)tou_03_str_000004B0), (s32)((char*)tou_03_str_000004B4), 327771, (s32)evt_npc_set_position, (s32)/*((char*)tou_03_str_000004B0)*/((char*)tou_03_str_000004B0),
    0, -1000, 0, 196699, (s32)evt_npc_set_tribe, (s32)/*"乱"*/(char*)tou_03_str_000004B0, (s32)/*"クッパ"*/(char*)tou_03_str_000004BC, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)/*"乱"*/(char*)tou_03_str_000004B0, 1073743360, 196699, (s32)evt_npc_set_ry, (s32)/*"乱"*/(char*)tou_03_str_000004B0, 270,
    458843, (s32)evt_npc_sound_data_set, (s32)/*((char*)tou_03_str_000004B0)*/((char*)tou_03_str_000004B0), (s32)((char*)tou_03_str_000004C4), (s32)((char*)tou_03_str_000004DC), 12000, (s32)((char*)tou_03_str_000004F4), -250000000,
    32, 196699, (s32)evt_npc_entry, (s32)/*((char*)tou_03_str_000004B0)*/((char*)tou_03_str_000004B0), (s32)((char*)tou_03_str_0000050C), 327771, (s32)evt_npc_set_position, (s32)/*((char*)tou_03_str_000004B0)*/((char*)tou_03_str_000004B0),
    0, -1000, 0, 196699, (s32)evt_npc_set_tribe, (s32)/*"乱"*/(char*)tou_03_str_000004B0, (s32)/*"アイアンシンエモン"*/(char*)tou_03_str_00000518, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)/*"乱"*/(char*)tou_03_str_000004B0, 1073743360, 196699, (s32)evt_npc_set_ry, (s32)/*"乱"*/(char*)tou_03_str_000004B0, 270,
    327771, (s32)evt_npc_set_scale, (s32)/*"乱"*/(char*)tou_03_str_000004B0, -229998464, -229998464, -229998976, 458843, (s32)evt_npc_sound_data_set,
    (s32)/*((char*)tou_03_str_000004B0)*/((char*)tou_03_str_000004B0), (s32)((char*)tou_03_str_00000480), (s32)((char*)tou_03_str_00000498), -250000000, -250000000, -250000000, 196699, (s32)evt_npc_entry,
    (s32)/*((char*)tou_03_str_0000052C)*/((char*)tou_03_str_0000052C), (s32)((char*)tou_03_str_00000534), 327771, (s32)evt_npc_set_position, (s32)/*((char*)tou_03_str_0000052C)*/((char*)tou_03_str_0000052C), 0, -1000, 0,
    196699, (s32)evt_npc_set_tribe, (s32)/*"乱２"*/(char*)tou_03_str_0000052C, (s32)/*"アイアンシンエモン2"*/(char*)tou_03_str_00000540, 262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"乱２"*/(char*)tou_03_str_0000052C,
    1073743360, 196699, (s32)evt_npc_set_ry, (s32)/*"乱２"*/(char*)tou_03_str_0000052C, 270, 327771, (s32)evt_npc_set_scale, (s32)/*"乱２"*/(char*)tou_03_str_0000052C,
    -229998464, -229998464, -229998976, 458843, (s32)evt_npc_sound_data_set, (s32)/*((char*)tou_03_str_0000052C)*/((char*)tou_03_str_0000052C), (s32)((char*)tou_03_str_00000480), (s32)((char*)tou_03_str_00000498),
#endif
    -250000000, -250000000, -250000000, 33, 33, 2, 1,
};

EVT_BEGIN(evt_random_battle)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000554)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)str_0000056C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000554)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)tou_03_str_0000056C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#endif
    WAIT_MS(1000)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_000004B0)), 370, 0, 210)
    CALL(evt_npc_set_position, STRING(((char*)str_0000052C)), 390, 0, 235)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000570)), 0, STRING(((char*)str_000004B0)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000004B0)), 370, 0, 210)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000052C)), 390, 0, 235)
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000570)), 0, STRING(((char*)tou_03_str_000004B0)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 300, 134, 732, 300, 38, 190, 1000, 11)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)str_0000052C)), 290, 235, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000052C)), 200, 60, 192, 500, 30)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000052C)), 290, 235, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000052C)), 200, 60, 192, 500, 30)
#endif
    END_INLINE_EVENT
#ifdef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)str_000004B0)), 270, 210, 0, FLOAT(80.0f), 1)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000004B0)), 180, 60, 167, 500, 30)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)tou_03_str_000004B0)), 270, 210, 0, FLOAT(80.0f), 1)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_000004B0)), 180, 60, 167, 500, 30)
#endif
    CALL(evt_mario_dispflag_onoff, 1, 2)
#ifdef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)str_00000580)))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_00000580)))
#endif
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)str_0000052C)), 75, 75, 0, FLOAT(80.0f), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000052C)), 75, 75, 0, FLOAT(80.0f), 1)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)str_000004B0)), 55, 50, 0, FLOAT(80.0f), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)tou_03_str_000004B0)), 55, 50, 0, FLOAT(80.0f), 1)
#endif
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
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000588)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000588)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 40, 155, 320, 40, 96, -8, 0, 0)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000598)), 0, STRING(((char*)str_000004B0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000598)), 0, STRING(((char*)tou_03_str_000004B0)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000005A8)), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)tou_03_str_000005A8)), 0)
#endif
    WAIT_MS(500)
#ifdef NONMATCHING
    CALL(evt_npc_set_battle_info, STRING(((char*)str_000004B0)), 10)
    CALL(evt_npc_battle_start, STRING(((char*)str_000004B0)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_battle_info, STRING(((char*)tou_03_str_000004B0)), 10)
    CALL(evt_npc_battle_start, STRING(((char*)tou_03_str_000004B0)))
#endif
    CALL(evt_npc_wait_battle_end)
    CALL(evt_mario_dispflag_onoff, 0, 2)
#ifdef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)str_000005B8)))
    CALL(evt_npc_check, STRING(((char*)str_0000045C)), LW(0))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_000005B8)))
    CALL(evt_npc_check, STRING(((char*)tou_03_str_0000045C)), LW(0))
#endif
    IF_INT_EQUAL(LW(0), 1)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 0, -1000, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000045C)), 0, -1000, 0)
#endif
    END_IF
#ifdef NONMATCHING
    CALL(evt_npc_check, STRING(((char*)str_00000464)), LW(0))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_check, STRING(((char*)tou_03_str_00000464)), LW(0))
#endif
    IF_INT_EQUAL(LW(0), 1)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 0, -1000, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000464)), 0, -1000, 0)
#endif
    END_IF
#ifdef NONMATCHING
    CALL(evt_npc_check, STRING(((char*)str_0000044C)), LW(0))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_check, STRING(((char*)tou_03_str_0000044C)), LW(0))
#endif
    IF_INT_EQUAL(LW(0), 1)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_0000044C)), 0, -1000, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000044C)), 0, -1000, 0)
#endif
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), -50)
    ADD(LW(2), -20)
    CALL(evt_party_set_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_battle_result, LW(0))
    IF_INT_EQUAL(LW(0), 1)
#ifdef NONMATCHING
        CALL(evt_npc_set_anim, STRING(((char*)str_000004B0)), STRING(((char*)str_000005C0)))
        CALL(evt_npc_set_anim, STRING(((char*)str_0000052C)), STRING(((char*)str_000005C0)))
        CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_000004B0)), 1536)
        CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_0000052C)), 1536)
        CALL(evt_msg_print, 0, STRING(((char*)str_000005C8)), 0, STRING(((char*)str_000004B0)))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000004B0)), STRING(((char*)tou_03_str_000005C0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_0000052C)), STRING(((char*)tou_03_str_000005C0)))
        CALL(evt_npc_flag_onoff, 0, STRING(((char*)tou_03_str_000004B0)), 1536)
        CALL(evt_npc_flag_onoff, 0, STRING(((char*)tou_03_str_0000052C)), 1536)
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000005C8)), 0, STRING(((char*)tou_03_str_000004B0)))
#endif
        WAIT_MS(300)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000005D8)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000005D8)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
        WAIT_MS(300)
        ELSE
        CALL_CHILD(PTR(evt_damage_pose))
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000005E8)), 0, STRING(((char*)str_000004B0)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000005E8)), 0, STRING(((char*)tou_03_str_000004B0)))
#endif
        WAIT_MS(300)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000005F8)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000005F8)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
        WAIT_MS(300)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_random_battle2)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000554)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)str_0000056C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000554)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)tou_03_str_0000056C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#endif
    WAIT_MS(1000)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_000004B0)), 370, 0, 210)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000608)), 0, STRING(((char*)str_000004B0)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000004B0)), 370, 0, 210)
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000608)), 0, STRING(((char*)tou_03_str_000004B0)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000618)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)tou_03_str_00000618)))
#endif
    CALL(evt_cam3d_evt_set, 300, 134, 732, 300, 38, 190, 1000, 11)
    WAIT_MS(1000)
#ifdef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)str_000004B0)), 270, 210, 0, FLOAT(80.0f), 1)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000004B0)), 180, 60, 167, 500, 30)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)tou_03_str_000004B0)), 270, 210, 0, FLOAT(80.0f), 1)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_000004B0)), 180, 60, 167, 500, 30)
#endif
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.029296875f), 500)
#endif
#ifndef NONMATCHING
        CALL(evt_cam_shake, 4, FLOAT((0.0f)), FLOAT(0.029296875f), 500)
#endif
    END_INLINE_EVENT
    CALL(evt_mario_dispflag_onoff, 1, 2)
#ifdef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)str_00000580)))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_00000580)))
#endif
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)str_000004B0)), 55, 50, 0, FLOAT(80.0f), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)tou_03_str_000004B0)), 55, 50, 0, FLOAT(80.0f), 1)
#endif
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
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000628)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000628)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 15, 189, 396, 15, 116, -8, 0, 11)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000638)), 0, STRING(((char*)str_000004B0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000638)), 0, STRING(((char*)tou_03_str_000004B0)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000005A8)), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)tou_03_str_000005A8)), 0)
#endif
    WAIT_MS(500)
#ifdef NONMATCHING
    CALL(evt_npc_set_battle_info, STRING(((char*)str_000004B0)), 24)
    CALL(evt_npc_battle_start, STRING(((char*)str_000004B0)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_battle_info, STRING(((char*)tou_03_str_000004B0)), 24)
    CALL(evt_npc_battle_start, STRING(((char*)tou_03_str_000004B0)))
#endif
    CALL(evt_npc_wait_battle_end)
    CALL(evt_mario_dispflag_onoff, 0, 2)
#ifdef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)str_000005B8)))
    CALL(evt_npc_check, STRING(((char*)str_0000045C)), LW(0))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_000005B8)))
    CALL(evt_npc_check, STRING(((char*)tou_03_str_0000045C)), LW(0))
#endif
    IF_INT_EQUAL(LW(0), 1)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 0, -1000, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000045C)), 0, -1000, 0)
#endif
    END_IF
#ifdef NONMATCHING
    CALL(evt_npc_check, STRING(((char*)str_00000464)), LW(0))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_check, STRING(((char*)tou_03_str_00000464)), LW(0))
#endif
    IF_INT_EQUAL(LW(0), 1)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 0, -1000, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000464)), 0, -1000, 0)
#endif
    END_IF
#ifdef NONMATCHING
    CALL(evt_npc_check, STRING(((char*)str_0000044C)), LW(0))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_check, STRING(((char*)tou_03_str_0000044C)), LW(0))
#endif
    IF_INT_EQUAL(LW(0), 1)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_0000044C)), 0, -1000, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000044C)), 0, -1000, 0)
#endif
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), -50)
    ADD(LW(2), -20)
    CALL(evt_party_set_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_battle_result, LW(0))
    IF_INT_EQUAL(LW(0), 1)
#ifdef NONMATCHING
        CALL(evt_npc_set_anim, STRING(((char*)str_000004B0)), STRING(((char*)str_00000648)))
        CALL(evt_npc_set_autotalkpose, STRING(((char*)str_000004B0)), STRING(((char*)str_00000648)), STRING(((char*)str_00000650)))
        CALL(evt_msg_print, 0, STRING(((char*)str_00000658)), 0, STRING(((char*)str_000004B0)))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000004B0)), STRING(((char*)tou_03_str_00000648)))
        CALL(evt_npc_set_autotalkpose, STRING(((char*)tou_03_str_000004B0)), STRING(((char*)tou_03_str_00000648)), STRING(((char*)tou_03_str_00000650)))
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000658)), 0, STRING(((char*)tou_03_str_000004B0)))
#endif
        WAIT_MS(300)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000668)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000668)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
        WAIT_MS(300)
        ELSE
        CALL_CHILD(PTR(evt_damage_pose))
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000678)), 0, STRING(((char*)str_000004B0)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000678)), 0, STRING(((char*)tou_03_str_000004B0)))
#endif
        WAIT_MS(300)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000688)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000688)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
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
#ifdef NONMATCHING
    CALL(evt_npc_move_position, LW(0), LW(5), LW(4), 0, FLOAT(60.0f), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_move_position, LW(0), LW(5), LW(4), 0, FLOAT((60.0f)), 1)
#endif
    WAIT_MS(1000)
#ifdef NONMATCHING
    CALL(evt_npc_move_position, LW(0), 280, LW(4), 0, FLOAT(60.0f), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_move_position, LW(0), 280, LW(4), 0, FLOAT((60.0f)), 1)
#endif
    CALL(evt_npc_jump_position_nohit, LW(0), 250, 20, LW(4), 500, 30)
    CALL(evt_npc_jump_position_nohit, LW(0), 215, 40, LW(4), 500, 30)
    CALL(evt_npc_jump_position_nohit, LW(0), 185, 60, LW(4), 500, 30)
    SET_VALUE(LW(5), 50)
    ADD(LW(5), LW(3))
#ifdef NONMATCHING
    CALL(evt_npc_move_position, LW(0), LW(5), LW(4), 0, FLOAT(60.0f), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_move_position, LW(0), LW(5), LW(4), 0, FLOAT((60.0f)), 1)
#endif
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
#ifdef NONMATCHING
    -30000000, (s32)/*"カメック緑空"*/(char*)str_00000698, -29999995, 131096, -29999995, 1, 327771, (s32)evt_npc_get_position,
#endif
#ifndef NONMATCHING
    -30000000, (s32)/*"カメック緑空"*/(char*)tou_03_str_00000698, -29999995, 131096, -29999995, 1, 327771, (s32)evt_npc_get_position,
#endif
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
#ifdef NONMATCHING
    -30000000, 262235, (s32)tribe_chk, -30000000, (s32)/*"バーストワンワン"*/(char*)str_00000420, -29999995, 131096, -29999995,
#endif
#ifndef NONMATCHING
    -30000000, 262235, (s32)tribe_chk, -30000000, (s32)/*"バーストワンワン"*/(char*)tou_03_str_00000420, -29999995, 131096, -29999995,
#endif
    1, 65628, (s32)burst_wangwang, 33, 33, 2, 1,
};

EVT_BEGIN(burst_chain_entry)
    SWITCH(LW(0))
        CASE_EQUAL(0)
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006A8)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006B0)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006B8)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006C0)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006C8)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006A8)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006B0)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006B8)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006C0)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006C8)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006A8)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006B0)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006B8)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006C0)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006C8)), 1074003968)
        CALL(burst_chain, STRING(((char*)tou_03_str_0000045C)), 0)
#endif
        CASE_EQUAL(1)
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006DC)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006E4)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006EC)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006F4)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006FC)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006DC)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006E4)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006EC)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006F4)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006FC)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006DC)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006E4)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006EC)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006F4)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006FC)), 1074003968)
        CALL(burst_chain, STRING(((char*)tou_03_str_00000464)), 1)
#endif
        CASE_EQUAL(6)
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006A8)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006B0)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006B8)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006C0)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006C8)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006A8)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006B0)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006B8)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006C0)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006C8)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006A8)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006B0)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006B8)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006C0)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006C8)), 1074003968)
        CALL(burst_chain, STRING(((char*)tou_03_str_00000434)), 0)
#endif
        CASE_EQUAL(7)
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006DC)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006E4)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006EC)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006F4)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_entry, STRING(((char*)tou_03_str_000006FC)), STRING(((char*)tou_03_str_00000414)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006DC)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006E4)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006EC)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006F4)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000006FC)), STRING(((char*)tou_03_str_000006D0)))
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006DC)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006E4)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006EC)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006F4)), 1074003968)
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000006FC)), 1074003968)
        CALL(burst_chain, STRING(((char*)tou_03_str_0000043C)), 1)
#endif
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(burst_wangwang)
    SET_VALUE(LW(10), LW(0))
    CALL(evt_npc_get_position, LW(10), LW(0), LW(1), LW(2))
    LOOP(0)
        CALL(evt_sub_random, 360, LW(3))
        CALL(evt_sub_get_sincos, LW(3), LW(4), LW(5))
#ifdef NONMATCHING
        MULTIPLY_FLOAT(LW(4), FLOAT(10.0f))
        MULTIPLY_FLOAT(LW(5), FLOAT(10.0f))
#endif
#ifndef NONMATCHING
        MULTIPLY_FLOAT(LW(4), FLOAT((10.0f)))
        MULTIPLY_FLOAT(LW(5), FLOAT((10.0f)))
#endif
        ADD_FLOAT(LW(4), LW(0))
        ADD_FLOAT(LW(5), LW(2))
        CALL(evt_sub_random, 200, LW(6))
        ADD(LW(6), 300)
        CALL(evt_sub_random, 20, LW(7))
        ADD(LW(7), 20)
        CALL(evt_npc_flag_onoff, 0, LW(10), 1024)
        CALL(evt_npc_jump_position_nohit, LW(10), LW(4), LW(1), LW(5), LW(6), LW(7))
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000704)), LW(4), LW(1), LW(5), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000704)), LW(4), LW(1), LW(5), 0)
#endif
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
#ifdef NONMATCHING
        CALL(evt_npc_set_attack_mode, STRING(((char*)str_0000045C)), 16)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_attack_mode, STRING(((char*)tou_03_str_0000045C)), 16)
#endif
        CALL(_firstattack_setting)
    END_IF
#ifdef NONMATCHING
    CALL(evt_npc_set_battle_info, STRING(((char*)str_0000045C)), LW(1))
    CALL(evt_npc_set_battle_rule, STRING(((char*)str_0000045C)), GSW(502), GSW(503), GSW(504))
    CALL(evt_npc_battle_start, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_battle_info, STRING(((char*)tou_03_str_0000045C)), LW(1))
    CALL(evt_npc_set_battle_rule, STRING(((char*)tou_03_str_0000045C)), GSW(502), GSW(503), GSW(504))
    CALL(evt_npc_battle_start, STRING(((char*)tou_03_str_0000045C)))
#endif
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
#ifdef NONMATCHING
            CALL(evt_npc_set_stay_anim, STRING(((char*)str_000001E0)))
            CALL(evt_npc_set_autotalkpose, STRING(((char*)str_000001E0)), STRING(((char*)str_00000220)), STRING(((char*)str_00000228)))
#endif
#ifndef NONMATCHING
            CALL(evt_npc_set_stay_anim, STRING(((char*)tou_03_str_000001E0)))
            CALL(evt_npc_set_autotalkpose, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00000220)), STRING(((char*)tou_03_str_00000228)))
#endif
            ELSE
#ifdef NONMATCHING
            CALL(evt_npc_set_stay_anim, STRING(((char*)str_0000028C)))
            CALL(evt_npc_set_autotalkpose, STRING(((char*)str_0000028C)), STRING(((char*)str_00000220)), STRING(((char*)str_00000228)))
#endif
#ifndef NONMATCHING
            CALL(evt_npc_set_stay_anim, STRING(((char*)tou_03_str_0000028C)))
            CALL(evt_npc_set_autotalkpose, STRING(((char*)tou_03_str_0000028C)), STRING(((char*)tou_03_str_00000220)), STRING(((char*)tou_03_str_00000228)))
#endif
        END_IF
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(0), 1)
        SWITCH(GSW(501))
            CASE_EQUAL(19)
#ifdef NONMATCHING
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000720)))
#endif
#ifndef NONMATCHING
            CALL(evt_snd_bgmon, 512, STRING(((char*)tou_03_str_00000720)))
#endif
            IF_INT_EQUAL(GSWF(2396), 0)
                SET_VALUE(GSWF(2396), 1)
                CALL_CHILD(PTR(evt_kurikuri_win))
                ELSE
                CALL_CHILD(PTR(evt_default_win))
            END_IF
            CASE_EQUAL(10)
#ifdef NONMATCHING
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000720)))
#endif
#ifndef NONMATCHING
            CALL(evt_snd_bgmon, 512, STRING(((char*)tou_03_str_00000720)))
#endif
            IF_INT_EQUAL(GSWF(2398), 0)
                SET_VALUE(GSWF(2398), 1)
                CALL_CHILD(PTR(evt_shinemon_win))
                ELSE
                CALL_CHILD(PTR(evt_default_win))
            END_IF
            CASE_EQUAL(0)
#ifdef NONMATCHING
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000730)))
#endif
#ifndef NONMATCHING
            CALL(evt_snd_bgmon, 512, STRING(((char*)tou_03_str_00000730)))
#endif
            IF_INT_EQUAL(GSWF(2400), 0)
                SET_VALUE(GSWF(2400), 1)
                CALL_CHILD(PTR(evt_champ_win))
                ELSE
                CALL_CHILD(PTR(evt_default_win))
            END_IF
            CASE_DEFAULT
#ifdef NONMATCHING
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000720)))
#endif
#ifndef NONMATCHING
            CALL(evt_snd_bgmon, 512, STRING(((char*)tou_03_str_00000720)))
#endif
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
#ifdef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000720)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)tou_03_str_00000720)))
#endif
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
#ifdef NONMATCHING
        CALL(evt_bero_mapchange, STRING(((char*)str_00000740)), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_bero_mapchange, STRING(((char*)tou_03_str_00000740)), 0)
#endif
        CASE_LESS(11)
#ifdef NONMATCHING
        CALL(evt_bero_mapchange, STRING(((char*)str_00000748)), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_bero_mapchange, STRING(((char*)tou_03_str_00000748)), 0)
#endif
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_bero_mapchange, STRING(((char*)str_00000750)), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_bero_mapchange, STRING(((char*)tou_03_str_00000750)), 0)
#endif
    END_SWITCH
    RETURN
EVT_END()

s32 evt_kurikuri_opening[] = {
#ifdef NONMATCHING
    131163, (s32)evt_mario_key_onoff, 0, 262235, (s32)evt_npc_status_onoff, 1, (s32)/*"ガンス"*/(char*)str_000001E0, 2,
    327771, (s32)evt_npc_set_position, (s32)/*"ガンス"*/(char*)str_000001E0, 0, 60, -130, 327771, (s32)evt_npc_set_position,
    (s32)/*"敵１"*/(char*)str_0000045C, 50, 60, 0, 327771, (s32)evt_npc_set_position, (s32)/*"敵２"*/(char*)str_00000464, 90,
    60, 25, 327771, (s32)evt_npc_set_position, (s32)/*"敵３"*/(char*)str_0000044C, 70, 60, -25,
    327771, (s32)evt_npc_set_position, (s32)/*"敵４"*/(char*)str_00000454, 110, 60, 0, 327771, (s32)evt_npc_set_position,
    (s32)/*"敵５"*/(char*)str_0000046C, 130, 60, -25, 589915, (s32)evt_cam3d_evt_set, 1075, 547,
#endif
#ifndef NONMATCHING
    131163, (s32)evt_mario_key_onoff, 0, 262235, (s32)evt_npc_status_onoff, 1, (s32)/*"ガンス"*/(char*)tou_03_str_000001E0, 2,
    327771, (s32)evt_npc_set_position, (s32)/*"ガンス"*/(char*)tou_03_str_000001E0, 0, 60, -130, 327771, (s32)evt_npc_set_position,
    (s32)/*"敵１"*/(char*)tou_03_str_0000045C, 50, 60, 0, 327771, (s32)evt_npc_set_position, (s32)/*"敵２"*/(char*)tou_03_str_00000464, 90,
    60, 25, 327771, (s32)evt_npc_set_position, (s32)/*"敵３"*/(char*)tou_03_str_0000044C, 70, 60, -25,
    327771, (s32)evt_npc_set_position, (s32)/*"敵４"*/(char*)tou_03_str_00000454, 110, 60, 0, 327771, (s32)evt_npc_set_position,
    (s32)/*"敵５"*/(char*)tou_03_str_0000046C, 130, 60, -25, 589915, (s32)evt_cam3d_evt_set, 1075, 547,
#endif
    998, 0, 287, -8, 0, 11, 131163, (s32)evt_seq_wait,
#ifdef NONMATCHING
    2, 196699, (s32)evt_snd_bgmon, 512, (s32)((char*)str_00000758), 589915, (s32)evt_cam3d_evt_set, -1024,
#endif
#ifndef NONMATCHING
    2, 196699, (s32)evt_snd_bgmon, 512, (s32)((char*)tou_03_str_00000758), 589915, (s32)evt_cam3d_evt_set, -1024,
#endif
    547, 1050, 0, 287, -8, 6000, 0, 65546,
    6000, 589915, (s32)evt_cam3d_evt_set, 0, 127, 105, 0, 95,
#ifdef NONMATCHING
    -145, 0, 0, 327771, (s32)evt_msg_print, 0, (s32)((char*)str_00000768), 0,
    (s32)/*"ガンス"*/(char*)str_000001E0, 589915, (s32)evt_cam3d_evt_set, 70, 137, 260, 70, 96,
    -70, 2000, 0, 458843, (s32)evt_npc_move_position, (s32)/*"ガンス"*/(char*)str_000001E0, 10, -20,
    0, -229938560, 1, 327771, (s32)evt_msg_print, 0, (s32)((char*)str_00000774), 0,
    (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), 196699, (s32)evt_npc_set_anim, (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), (s32)((char*)str_00000208), 65546, 300, 196699,
    (s32)evt_npc_set_anim, (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), (s32)((char*)str_0000020C), 327771, (s32)evt_msg_print, 0, (s32)((char*)str_00000780), 0,
    (s32)/*((char*)str_00000464)*/((char*)str_00000464), 786523, (s32)evt_eff_fukidashi, 1, (s32)((char*)str_00000270), (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), 0, 0,
#endif
#ifndef NONMATCHING
    -145, 0, 0, 327771, (s32)evt_msg_print, 0, (s32)((char*)tou_03_str_00000768), 0,
    (s32)/*"ガンス"*/(char*)tou_03_str_000001E0, 589915, (s32)evt_cam3d_evt_set, 70, 137, 260, 70, 96,
    -70, 2000, 0, 458843, (s32)evt_npc_move_position, (s32)/*"ガンス"*/(char*)tou_03_str_000001E0, 10, -20,
    0, -229938560, 1, 327771, (s32)evt_msg_print, 0, (s32)((char*)tou_03_str_00000774), 0,
    (s32)/*((char*)tou_03_str_000001E0)*/((char*)tou_03_str_000001E0), 196699, (s32)evt_npc_set_anim, (s32)/*((char*)tou_03_str_000001E0)*/((char*)tou_03_str_000001E0), (s32)((char*)tou_03_str_00000208), 65546, 300, 196699,
    (s32)evt_npc_set_anim, (s32)/*((char*)tou_03_str_000001E0)*/((char*)tou_03_str_000001E0), (s32)((char*)tou_03_str_0000020C), 327771, (s32)evt_msg_print, 0, (s32)((char*)tou_03_str_00000780), 0,
    (s32)/*((char*)tou_03_str_00000464)*/((char*)tou_03_str_00000464), 786523, (s32)evt_eff_fukidashi, 1, (s32)((char*)tou_03_str_00000270), (s32)/*((char*)tou_03_str_000001E0)*/((char*)tou_03_str_000001E0), 0, 0,
#endif
    0, 0, 0, 0, 0, 0, 196699, (s32)evt_npc_set_anim,
#ifdef NONMATCHING
    (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), (s32)((char*)str_0000021C), 65546, 300, 196699, (s32)evt_npc_set_anim, (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), (s32)((char*)str_00000220),
    196699, (s32)evt_set_dir_to_target, (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), (s32)((char*)str_0000078C), 262235, (s32)evt_mario_set_pos, -550, 0,
#endif
#ifndef NONMATCHING
    (s32)/*((char*)tou_03_str_000001E0)*/((char*)tou_03_str_000001E0), (s32)((char*)tou_03_str_0000021C), 65546, 300, 196699, (s32)evt_npc_set_anim, (s32)/*((char*)tou_03_str_000001E0)*/((char*)tou_03_str_000001E0), (s32)((char*)tou_03_str_00000220),
    196699, (s32)evt_set_dir_to_target, (s32)/*((char*)tou_03_str_000001E0)*/((char*)tou_03_str_000001E0), (s32)((char*)tou_03_str_0000078C), 262235, (s32)evt_mario_set_pos, -550, 0,
#endif
    0, 327771, (s32)evt_party_set_pos, 0, -560, 0, -10, 131124,
    -30000000, -230184320, 65630, (s32)w_door_open, 196699, (s32)evt_cam3d_evt_off, 1000, 11,
#ifdef NONMATCHING
    65546, 1000, 107, 65546, 1000, 393307, (s32)evt_snd_sfxon_3d, (s32)((char*)str_00000794),
#endif
#ifndef NONMATCHING
    65546, 1000, 107, 65546, 1000, 393307, (s32)evt_snd_sfxon_3d, (s32)((char*)tou_03_str_00000794),
#endif
    -565, 0, 0, 0, 327771, (s32)evt_sub_intpl_init, 11, -180,
    0, 20, 65541, 21, 65627, (s32)evt_sub_intpl_get_value, 65630, (s32)w_door_open,
    6, 109, 131122, -90000000, 0, 107, 65546, 1000,
#ifdef NONMATCHING
    327771, (s32)evt_msg_print, 0, (s32)((char*)str_000007A8), 0, 0, 131122, -90000000,
#endif
#ifndef NONMATCHING
    327771, (s32)evt_msg_print, 0, (s32)((char*)tou_03_str_000007A8), 0, 0, 131122, -90000000,
#endif
    1, 109, 262235, (s32)evt_mario_mov_pos2, -450, 0, -229877120, 65546,
    1000, 107, 65546, 300, 327771, (s32)evt_party_move_pos2, 0, -280,
    25, -229877120, 65545, 1, 524379, (s32)evt_party_jump_pos, 0, -250,
    20, 25, 400, 1, -1000, 65545, 1, 524379,
    (s32)evt_party_jump_pos, 0, -215, 40, 25, 400, 1, -1000,
    65545, 1, 524379, (s32)evt_party_jump_pos, 0, -185, 60, 25,
    400, 1, -1000, 65545, 1, 327771, (s32)evt_party_move_pos2, 0,
    -90, -25, -229877120, 109, 262235, (s32)evt_mario_mov_pos2, -280, 0,
    -229877120, 327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 393307,
#ifdef NONMATCHING
    (s32)evt_snd_sfxon_3d, (s32)((char*)str_000007B4), -30000000, -29999999, -29999998, 0, 458843, (s32)evt_mario_jump_pos,
#endif
#ifndef NONMATCHING
    (s32)evt_snd_sfxon_3d, (s32)((char*)tou_03_str_000007B4), -30000000, -29999999, -29999998, 0, 458843, (s32)evt_mario_jump_pos,
#endif
    -250, 20, 0, 400, 1, -1000, 327771, (s32)evt_mario_get_pos,
#ifdef NONMATCHING
    0, -30000000, -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)((char*)str_000007D0), -30000000,
#endif
#ifndef NONMATCHING
    0, -30000000, -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)((char*)tou_03_str_000007D0), -30000000,
#endif
    -29999999, -29999998, 0, 458843, (s32)evt_mario_jump_pos, -215, 40, 0,
    400, 1, -1000, 327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999,
#ifdef NONMATCHING
    -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)((char*)str_000007EC), -30000000, -29999999, -29999998, 0,
#endif
#ifndef NONMATCHING
    -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)((char*)tou_03_str_000007EC), -30000000, -29999999, -29999998, 0,
#endif
    458843, (s32)evt_mario_jump_pos, -185, 60, 0, 400, 1, -1000,
    262235, (s32)evt_mario_mov_pos2, -55, 0, -229877120, 65541, 0, 131096,
    -90000000, 1, 7, 33, 65545, 1, 6, 458843,
#ifdef NONMATCHING
    (s32)evt_npc_move_position, (s32)/*"ガンス"*/(char*)str_000001E0, -20, -20, 0, -229938560, 1, 327771,
    (s32)evt_msg_print, 0, (s32)((char*)str_00000808), 0, (s32)/*((char*)str_000001E0)*/((char*)str_000001E0), 107, 327771, (s32)evt_msg_print,
    0, (s32)((char*)str_00000814), 0, (s32)/*((char*)str_0000045C)*/((char*)str_0000045C), 109, 458843, (s32)evt_npc_move_position, (s32)/*((char*)str_0000045C)*/((char*)str_0000045C),
#endif
#ifndef NONMATCHING
    (s32)evt_npc_move_position, (s32)/*"ガンス"*/(char*)tou_03_str_000001E0, -20, -20, 0, -229938560, 1, 327771,
    (s32)evt_msg_print, 0, (s32)((char*)tou_03_str_00000808), 0, (s32)/*((char*)tou_03_str_000001E0)*/((char*)tou_03_str_000001E0), 107, 327771, (s32)evt_msg_print,
    0, (s32)((char*)tou_03_str_00000814), 0, (s32)/*((char*)tou_03_str_0000045C)*/((char*)tou_03_str_0000045C), 109, 458843, (s32)evt_npc_move_position, (s32)/*((char*)tou_03_str_0000045C)*/((char*)tou_03_str_0000045C),
#endif
    0, 0, 0, -229897600, 1, 327771, (s32)evt_mario_get_pos, 0,
#ifdef NONMATCHING
    -30000000, -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)((char*)str_00000820), -30000000, -29999999,
    -29999998, 0, 131163, (s32)evt_mario_set_pose, (s32)((char*)str_0000083C), 107, 131124, -30000000,
#endif
#ifndef NONMATCHING
    -30000000, -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)((char*)tou_03_str_00000820), -30000000, -29999999,
    -29999998, 0, 131163, (s32)evt_mario_set_pose, (s32)((char*)tou_03_str_0000083C), 107, 131124, -30000000,
#endif
    -230000000, 65541, 10, 131130, -30000000, -229986176, 327771, (s32)evt_npc_set_rotate,
#ifdef NONMATCHING
    (s32)/*"敵１"*/(char*)str_0000045C, 0, 0, -30000000, 65545, 1, 6, 109,
    458843, (s32)evt_npc_sound_data_set, (s32)/*((char*)str_0000045C)*/((char*)str_0000045C), -250000000, -250000000, -250000000, (s32)((char*)str_00000844), -250000000,
    458843, (s32)evt_npc_jump_position_nohit, (s32)/*"敵１"*/(char*)str_0000045C, -30, 100, 0, 800, 100,
#endif
#ifndef NONMATCHING
    (s32)/*"敵１"*/(char*)tou_03_str_0000045C, 0, 0, -30000000, 65545, 1, 6, 109,
    458843, (s32)evt_npc_sound_data_set, (s32)/*((char*)tou_03_str_0000045C)*/((char*)tou_03_str_0000045C), -250000000, -250000000, -250000000, (s32)((char*)tou_03_str_00000844), -250000000,
    458843, (s32)evt_npc_jump_position_nohit, (s32)/*"敵１"*/(char*)tou_03_str_0000045C, -30, 100, 0, 800, 100,
#endif
    2, 1,
};

EVT_BEGIN(evt_kurikuri_win)
    CALL(evt_cam3d_evt_set, 70, 138, 263, 70, 90, -8, 0, 11)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 50, 60, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 90, 80, 25)
    CALL(evt_npc_set_position, STRING(((char*)str_0000044C)), 70, 60, -25)
    CALL(evt_npc_set_position, STRING(((char*)str_00000454)), 110, 60, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_0000046C)), 130, 60, -25)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000045C)), 50, 60, 0)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000464)), 90, 80, 25)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000044C)), 70, 60, -25)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000454)), 110, 60, 0)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000046C)), 130, 60, -25)
#endif
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_npc_set_rotate, STRING(((char*)str_0000045C)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)str_00000464)), 0, 0, 180)
    CALL(evt_npc_set_rotate, STRING(((char*)str_0000044C)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)str_00000454)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)str_0000046C)), 0, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_rotate, STRING(((char*)tou_03_str_0000045C)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)tou_03_str_00000464)), 0, 0, 180)
    CALL(evt_npc_set_rotate, STRING(((char*)tou_03_str_0000044C)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)tou_03_str_00000454)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)tou_03_str_0000046C)), 0, 0, 0)
#endif
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_0000045C)), STRING(((char*)str_0000085C)))
    CALL(evt_npc_set_anim, STRING(((char*)str_00000464)), STRING(((char*)str_00000864)))
    CALL(evt_npc_set_anim, STRING(((char*)str_0000044C)), STRING(((char*)str_0000085C)))
    CALL(evt_npc_set_anim, STRING(((char*)str_00000454)), STRING(((char*)str_0000085C)))
    CALL(evt_npc_set_anim, STRING(((char*)str_0000046C)), STRING(((char*)str_0000085C)))
    CALL(evt_mario_set_pose, STRING(((char*)str_000005B8)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_0000045C)), STRING(((char*)tou_03_str_0000085C)))
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_00000464)), STRING(((char*)tou_03_str_00000864)))
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_0000044C)), STRING(((char*)tou_03_str_0000085C)))
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_00000454)), STRING(((char*)tou_03_str_0000085C)))
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_0000046C)), STRING(((char*)tou_03_str_0000085C)))
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_000005B8)))
#endif
    CALL_CHILD(PTR(evt_kime_pose))
#ifdef NONMATCHING
    CALL(evt_npc_get_position, STRING(((char*)str_0000044C)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_0000086C)), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_0000045C)), 512)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_get_position, STRING(((char*)tou_03_str_0000044C)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_0000086C)), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)tou_03_str_0000045C)), 512)
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000884)), 0, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000884)), 0, STRING(((char*)tou_03_str_0000045C)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001E0)), STRING(((char*)str_0000078C)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_0000078C)))
#endif
    CALL(evt_cam3d_evt_set, -70, 138, 263, -70, 90, -8, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000890)), 0, STRING(((char*)str_000001E0)))
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000208)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000890)), 0, STRING(((char*)tou_03_str_000001E0)))
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00000208)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_0000020C)))
    CALL(evt_msg_select, 0, STRING(((char*)str_0000089C)))
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_0000021C)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_0000020C)))
    CALL(evt_msg_select, 0, STRING(((char*)tou_03_str_0000089C)))
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_0000021C)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000220)))
    CALL(evt_msg_print_add, 0, STRING(((char*)str_000008AC)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00000220)))
    CALL(evt_msg_print_add, 0, STRING(((char*)tou_03_str_000008AC)))
#endif
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(1), 100)
#ifdef NONMATCHING
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)tou_03_str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
#endif
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000258)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000258)), LW(0), LW(1), LW(2), 0)
#endif
    CALL(evt_cam3d_evt_set, 0, 850, 2160, 0, 287, -8, 10000, 0)
    WAIT_MS(7000)
    RETURN
EVT_END()

EVT_BEGIN(evt_kurikuri_lose)
    CALL_CHILD(PTR(evt_damage_pose))
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_rotate, STRING(((char*)tou_03_str_0000045C)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)tou_03_str_00000464)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)tou_03_str_0000044C)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)tou_03_str_00000454)), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING(((char*)tou_03_str_0000046C)), 0, 0, 0)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000045C)), 50, 60, 0)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000464)), 90, 60, 25)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000044C)), 70, 60, -25)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000454)), 110, 60, 0)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000046C)), 130, 60, -25)
    CALL(evt_npc_get_position, STRING(((char*)tou_03_str_00000464)), LW(0), LW(1), LW(2))
#endif
    ADD(LW(1), 100)
#ifdef NONMATCHING
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)tou_03_str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
#endif
    CALL(evt_cam3d_evt_set, 70, 138, 263, 70, 90, -8, 0, 0)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000008C8)), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)tou_03_str_000008C8)), 0)
#endif
    IF_INT_LESS(GSW(0), 172)
#ifdef NONMATCHING
        SET_VALUE(LW(2), STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(2), STRING(((char*)tou_03_str_000001E0)))
#endif
        ELSE
#ifdef NONMATCHING
        SET_VALUE(LW(2), STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(2), STRING(((char*)tou_03_str_0000028C)))
#endif
    END_IF
    CALL(evt_npc_set_position, LW(2), 33, 60, -83)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, LW(2), STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, LW(2), STRING(((char*)tou_03_str_0000045C)))
#endif
    CALL(evt_tou_get_fighter_info_28_text_3E58, GSW(501), LW(0), LW(1))
#ifdef NONMATCHING
    CALL(evt_msg_print_insert, 0, STRING(((char*)str_000008E0)), 0, LW(2), LW(0))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_insert, 0, STRING(((char*)tou_03_str_000008E0)), 0, LW(2), LW(0))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000008F0)), 0, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000008F0)), 0, STRING(((char*)tou_03_str_0000045C)))
#endif
    RETURN
EVT_END()

EVT_BEGIN(evt_shinemon_opening)
    CALL(evt_mario_key_onoff, 0)
#ifdef NONMATCHING
    CALL(evt_npc_status_onoff, 1, STRING(((char*)str_000001E0)), 2)
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), 0, 60, -130)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_status_onoff, 1, STRING(((char*)tou_03_str_000001E0)), 2)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000001E0)), 0, 60, -130)
#endif
    CALL(evt_cam3d_evt_set, 1075, 547, 998, 0, 287, -8, 0, 11)
    CALL(evt_seq_wait, 2)
#ifdef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000758)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)tou_03_str_00000758)))
#endif
    CALL(evt_cam3d_evt_set, -1024, 547, 1050, 0, 287, -8, 5000, 0)
    WAIT_MS(5000)
    CALL(evt_cam3d_evt_set, 0, 127, 105, 0, 95, -145, 0, 0)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000008FC)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000008FC)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    WAIT_MS(1000)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_0000090C)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_0000090C)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    CALL(evt_mario_set_pos, -550, 0, 0)
    CALL(evt_party_set_pos, 0, -560, 0, -10)
    SET_FLOAT_VALUE(LW(0), FLOAT(-180.0f))
    CALL_CHILD(PTR(w_door_open))
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000794)), -565, 0, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000794)), -565, 0, 0, 0)
#endif
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
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000007D0)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_000007D0)), LW(0), LW(1), LW(2), 0)
#endif
        CALL(evt_mario_jump_pos, -250, 20, 0, 400, 1, -1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_0000091C)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_0000091C)), LW(0), LW(1), LW(2), 0)
#endif
        CALL(evt_mario_jump_pos, -215, 40, 0, 400, 1, -1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000007B4)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_000007B4)), LW(0), LW(1), LW(2), 0)
#endif
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
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000938)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000938)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(800)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -379, 30, 133)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000948)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000948)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(800)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -293, 60, -180)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000958)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000958)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(800)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -272, 90, 200)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000968)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000968)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(800)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
#ifdef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)str_000001E0)), -20, -20, 0, FLOAT(70.0f), 1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000978)), 0, STRING(((char*)str_000001E0)))
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000208)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)tou_03_str_000001E0)), -20, -20, 0, FLOAT(70.0f), 1)
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000978)), 0, STRING(((char*)tou_03_str_000001E0)))
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00000208)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_0000020C)))
    CALL(evt_msg_select, 0, STRING(((char*)str_00000988)))
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_0000021C)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_0000020C)))
    CALL(evt_msg_select, 0, STRING(((char*)tou_03_str_00000988)))
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_0000021C)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000220)))
    CALL(evt_msg_print_add, 0, STRING(((char*)str_00000998)))
    CALL(evt_eff_fukidashi, 1, STRING(((char*)str_000009A8)), STRING(((char*)str_000001E0)), 0, 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00000220)))
    CALL(evt_msg_print_add, 0, STRING(((char*)tou_03_str_00000998)))
    CALL(evt_eff_fukidashi, 1, STRING(((char*)tou_03_str_000009A8)), STRING(((char*)tou_03_str_000001E0)), 0, 0, 0, 0, 0, 0, 0, 0)
#endif
    WAIT_MS(500)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001E0)), STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_0000045C)))
#endif
    SET_FLOAT_VALUE(LW(0), FLOAT(-180.0f))
    CALL_CHILD(PTR(e_door_open))
    CALL(evt_cam3d_evt_set, 475, 134, 533, 475, 38, -8, 0, 0)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 550, 0, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 550, 0, 0)
    SET_VALUE(LW(0), STRING(((char*)str_00000464)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000045C)), 550, 0, 0)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000464)), 550, 0, 0)
    SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000464)))
#endif
    SET_VALUE(LW(1), 0)
    SET_VALUE(LW(2), 2)
    SPAWN_EVENT(PTR(evt_teki_nyuujyou))
    WAIT_MS(500)
#ifdef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)tou_03_str_0000045C)))
#endif
    SET_VALUE(LW(1), 1)
    SET_VALUE(LW(2), 2)
    SPAWN_EVENT(PTR(evt_teki_nyuujyou))
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000794)), 565, 0, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000794)), 565, 0, 0, 0)
#endif
        CALL(evt_sub_intpl_init, 11, -180, 0, 20)
        LOOP(21)
            CALL(evt_sub_intpl_get_value)
            CALL_CHILD(PTR(e_door_open))
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_msg_toge, 2, 426, 30, -195)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000009AC)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000009AC)), 0, 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(3000)
        CALL(evt_msg_toge, 2, 379, 30, 133)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000009BC)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000009BC)), 0, 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_msg_toge, 2, 293, 30, -180)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000009CC)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000009CC)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(3000)
    CALL(evt_cam3d_evt_set, 50, 146, 273, 50, 96, -8, 6000, 0)
    WAIT_MS(6000)
#ifdef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)str_000001E0)), 0, -30, 0, FLOAT(70.0f), 1)
    CALL(evt_msg_print, 0, STRING(((char*)str_000009DC)), 0, STRING(((char*)str_000001E0)))
    CALL(evt_msg_print, 0, STRING(((char*)str_000009EC)), 0, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)tou_03_str_000001E0)), 0, -30, 0, FLOAT(70.0f), 1)
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000009DC)), 0, STRING(((char*)tou_03_str_000001E0)))
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000009EC)), 0, STRING(((char*)tou_03_str_0000045C)))
#endif
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 80, 146, 273, 80, 96, -8, 500, 11)
    WAIT_MS(500)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000009FC)), 0, STRING(((char*)str_00000464)))
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), 0, 60, -130)
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000009FC)), 0, STRING(((char*)tou_03_str_00000464)))
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000001E0)), 0, 60, -130)
#endif
    CALL(evt_cam3d_evt_set, 0, 150, 141, 0, 100, -154, 0, 11)
    WAIT_MS(200)
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A0C)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00000A0C)))
#endif
    WAIT_MS(200)
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A10)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A10)), STRING(((char*)str_00000A14)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000A18)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00000A10)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00000A10)), STRING(((char*)tou_03_str_00000A14)))
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000A18)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000005A8)), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)tou_03_str_000005A8)), 0)
#endif
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
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 55, 60, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 95, 60, 0)
    CALL(evt_npc_set_anim, STRING(((char*)str_0000045C)), STRING(((char*)str_000005C0)))
    CALL(evt_npc_set_anim, STRING(((char*)str_00000464)), STRING(((char*)str_000005C0)))
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_0000045C)), 1536)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00000464)), 1536)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000045C)), 55, 60, 0)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000464)), 95, 60, 0)
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_0000045C)), STRING(((char*)tou_03_str_000005C0)))
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_00000464)), STRING(((char*)tou_03_str_000005C0)))
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)tou_03_str_0000045C)), 1536)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)tou_03_str_00000464)), 1536)
#endif
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), 30)
    ADD(LW(2), -30)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), LW(0), LW(1), LW(2))
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001E0)), STRING(((char*)str_0000078C)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000001E0)), LW(0), LW(1), LW(2))
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_0000078C)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000A2C)), 0, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000A2C)), 0, STRING(((char*)tou_03_str_0000045C)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000A3C)), 0, STRING(((char*)str_00000464)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000A3C)), 0, STRING(((char*)tou_03_str_00000464)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -65, 143, 263, -65, 95, -8, 0, 0)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000A4C)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000A4C)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(1), 100)
#ifdef NONMATCHING
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_00000A5C)))
#endif
#ifndef NONMATCHING
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)tou_03_str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_00000A5C)))
#endif
    CALL(evt_mario_set_dir, 270, 300, 0)
    WAIT_MS(400)
    CALL(evt_mario_set_dir, 90, 300, 0)
    WAIT_MS(400)
    CALL(evt_mario_set_dir, 270, 300, 0)
    WAIT_MS(400)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000A64)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_00000A7C)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000A64)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_00000A7C)))
#endif
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000258)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000258)), LW(0), LW(1), LW(2), 0)
#endif
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 850, 2160, 0, 287, -8, 10000, 0)
    WAIT_MS(7000)
    RETURN
EVT_END()

EVT_BEGIN(evt_shinemon_lose)
    CALL_CHILD(PTR(evt_damage_pose))
#ifdef NONMATCHING
    CALL(evt_npc_get_position, STRING(((char*)str_0000045C)), LW(0), LW(1), LW(2))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_get_position, STRING(((char*)tou_03_str_0000045C)), LW(0), LW(1), LW(2))
#endif
    ADD(LW(1), 100)
#ifdef NONMATCHING
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING(((char*)str_000008C8)), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)tou_03_str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING(((char*)tou_03_str_000008C8)), 0)
#endif
    IF_INT_LESS(GSW(0), 172)
#ifdef NONMATCHING
        SET_VALUE(LW(2), STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(2), STRING(((char*)tou_03_str_000001E0)))
#endif
        ELSE
#ifdef NONMATCHING
        SET_VALUE(LW(2), STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(2), STRING(((char*)tou_03_str_0000028C)))
#endif
    END_IF
    CALL(evt_tou_get_fighter_info_28_text_3E58, GSW(501), LW(0), LW(1))
#ifdef NONMATCHING
    CALL(evt_msg_print_insert, 0, STRING(((char*)str_000008E0)), 0, LW(2), LW(0))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_insert, 0, STRING(((char*)tou_03_str_000008E0)), 0, LW(2), LW(0))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 60, 143, 263, 60, 95, -8, 0, 0)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000A84)), 0, STRING(((char*)str_0000045C)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000A94)), 0, STRING(((char*)str_00000464)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000A84)), 0, STRING(((char*)tou_03_str_0000045C)))
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000A94)), 0, STRING(((char*)tou_03_str_00000464)))
#endif
    WAIT_MS(300)
    RETURN
EVT_END()

EVT_BEGIN(evt_champ_opening)
    CALL(evt_mario_key_onoff, 0)
#ifdef NONMATCHING
    CALL(evt_npc_status_onoff, 1, STRING(((char*)str_000001E0)), 2)
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), 0, 60, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 80, 60, 0)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000001E0)), 32768)
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001E0)), STRING(((char*)str_0000045C)))
    CALL(evt_set_dir_to_target, STRING(((char*)str_0000045C)), STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_status_onoff, 1, STRING(((char*)tou_03_str_000001E0)), 2)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000001E0)), 0, 60, 0)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000045C)), 80, 60, 0)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000001E0)), 32768)
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_0000045C)))
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_0000045C)), STRING(((char*)tou_03_str_000001E0)))
#endif
    CALL(evt_cam3d_evt_set, 0, 192, 620, 0, 95, -145, 0, 11)
#ifdef NONMATCHING
    CALL(evt_npc_set_tribe, STRING(((char*)str_0000045C)), STRING(((char*)str_00000AA4)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_tribe, STRING(((char*)tou_03_str_0000045C)), STRING(((char*)tou_03_str_00000AA4)))
#endif
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(tou_champion_belt_28_text_2A10, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
        CALL(tou_champion_belt_28_text_2A10, STRING(((char*)tou_03_str_0000045C)))
#endif
    END_INLINE_EVENT
    CALL(evt_seq_wait, 2)
#ifdef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000ABC)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)tou_03_str_00000ABC)))
#endif
    CALL(evt_snd_bgm_scope, 0, 1)
    WAIT_MS(2000)
#ifdef NONMATCHING
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_000001E0)), 32768)
    CALL(evt_eff_fukidashi, 1, STRING(((char*)str_00000ACC)), STRING(((char*)str_000001E0)), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_npc_set_ry, STRING(((char*)str_000001E0)), 270)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)tou_03_str_000001E0)), 32768)
    CALL(evt_eff_fukidashi, 1, STRING(((char*)tou_03_str_00000ACC)), STRING(((char*)tou_03_str_000001E0)), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_npc_set_ry, STRING(((char*)tou_03_str_000001E0)), 270)
#endif
    WAIT_MS(500)
    CALL(evt_mario_set_pos, -550, 0, 0)
    CALL(evt_party_set_pos, 0, -560, 0, -10)
    SET_FLOAT_VALUE(LW(0), FLOAT(-180.0f))
    CALL_CHILD(PTR(w_door_open))
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000794)), -565, 0, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000794)), -565, 0, 0, 0)
#endif
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
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000AD0)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000AD0)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 328, 1219, 0, 130, 145, 3000, 11)
    BEGIN_INLINE_EVENT
        WAIT_MS(2000)
        CALL(evt_msg_toge, 2, -200, 30, -200)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000AE0)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000AE0)), 0, 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(3000)
        CALL(evt_msg_toge, 2, 200, 30, 200)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000AF0)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000AF0)), 0, 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_msg_toge, 2, -300, 200, -400)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B00)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000B00)), 0, 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_msg_toge, 2, 200, 200, -300)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B10)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000B10)), 0, 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(5000)
        CALL(evt_msg_toge, 2, 200, 30, 133)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B20)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000B20)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(7000)
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)str_00000B30)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)tou_03_str_00000B30)))
#endif
    WAIT_MS(300)
    CALL(evt_party_run, 0)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_mario_mov_pos2, -280, 0, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_mario_mov_pos2, -280, 0, FLOAT((60.0f)))
#endif
        CALL(evt_cam3d_evt_set, 0, 192, 620, 0, 95, -145, 4000, 11)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000007EC)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_000007EC)), LW(0), LW(1), LW(2), 0)
#endif
        CALL(evt_mario_jump_pos, -250, 20, 0, 400, 1, -1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000B40)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000B40)), LW(0), LW(1), LW(2), 0)
#endif
        CALL(evt_mario_jump_pos, -215, 40, 0, 400, 1, -1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000007B4)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_000007B4)), LW(0), LW(1), LW(2), 0)
#endif
        CALL(evt_mario_jump_pos, -185, 60, 0, 400, 1, -1000)
#ifdef NONMATCHING
        CALL(evt_mario_mov_pos2, -80, 0, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_mario_mov_pos2, -80, 0, FLOAT((60.0f)))
#endif
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_stop, 0)
        WAIT_MS(300)
#ifdef NONMATCHING
        CALL(evt_party_move_pos2, 0, -280, 25, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_party_move_pos2, 0, -280, 25, FLOAT((60.0f)))
#endif
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -250, 20, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -215, 40, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -185, 60, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
#ifdef NONMATCHING
        CALL(evt_party_move_pos2, 0, -130, -25, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_party_move_pos2, 0, -130, -25, FLOAT((60.0f)))
#endif
        CALL(evt_party_stop, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -426, 30, -195)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B5C)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000B5C)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -379, 30, 233)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B6C)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000B6C)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -293, 30, -180)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B7C)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000B7C)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -272, 30, 100)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B8C)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000B8C)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -150, 100, -200)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B8C)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000B8C)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(1000)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(500)
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A0C)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00000A0C)))
#endif
    WAIT_MS(200)
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A10)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A10)), STRING(((char*)str_00000A14)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000B9C)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00000A10)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00000A10)), STRING(((char*)tou_03_str_00000A14)))
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000B9C)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000005A8)), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)tou_03_str_000005A8)), 0)
#endif
    BEGIN_INLINE_EVENT
        CALL(evt_cam3d_evt_set, 0, 250, 730, 0, 100, -154, 2000, 11)
    END_INLINE_EVENT
    WAIT_MS(1000)
    RETURN
EVT_END()

EVT_BEGIN(evt_champ_opening_re)
    CALL(evt_mario_key_onoff, 0)
#ifdef NONMATCHING
    CALL(evt_npc_status_onoff, 1, STRING(((char*)str_0000028C)), 2)
    CALL(evt_npc_set_position, STRING(((char*)str_0000028C)), 0, 60, -130)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_status_onoff, 1, STRING(((char*)tou_03_str_0000028C)), 2)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000028C)), 0, 60, -130)
#endif
    CALL(evt_cam3d_evt_set, 0, 481, 1310, 0, 295, -145, 0, 11)
    CALL(evt_seq_wait, 2)
#ifdef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000ABC)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)tou_03_str_00000ABC)))
#endif
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_cam3d_evt_set, 0, 281, 1310, 0, 95, -145, 3000, 0)
    WAIT_MS(3000)
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 0, 127, 105, 0, 95, -145, 0, 0)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000BAC)), 0, STRING(((char*)str_0000028C)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000BBC)), 0, STRING(((char*)str_0000028C)))
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 550, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000BAC)), 0, STRING(((char*)tou_03_str_0000028C)))
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000BBC)), 0, STRING(((char*)tou_03_str_0000028C)))
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000045C)), 550, 0, 0)
#endif
    SET_FLOAT_VALUE(LW(0), FLOAT(-180.0f))
    CALL_CHILD(PTR(e_door_open))
    CALL(evt_cam3d_evt_set, 475, 134, 533, 475, 38, -8, 0, 0)
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000794)), 565, 0, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000794)), 565, 0, 0, 0)
#endif
        CALL(evt_sub_intpl_init, 11, -180, 0, 20)
        LOOP(21)
            CALL(evt_sub_intpl_get_value)
            CALL_CHILD(PTR(e_door_open))
        END_LOOP
    END_INLINE_EVENT
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)str_0000045C)), 450, 0, 0, FLOAT(60.0f), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000045C)), 450, 0, 0, FLOAT((60.0f)), 1)
#endif
        WAIT_MS(1000)
#ifdef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)str_0000045C)), 310, 0, 0, FLOAT(60.0f), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000045C)), 280, 20, 0, 500, 30)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000045C)), 245, 40, 0, 500, 30)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000045C)), 215, 60, 0, 500, 30)
        CALL(evt_npc_move_position, STRING(((char*)str_0000045C)), 80, 0, 0, FLOAT(60.0f), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000045C)), 310, 0, 0, FLOAT((60.0f)), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000045C)), 280, 20, 0, 500, 30)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000045C)), 245, 40, 0, 500, 30)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000045C)), 215, 60, 0, 500, 30)
        CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000045C)), 80, 0, 0, FLOAT((60.0f)), 1)
#endif
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_msg_toge, 2, 426, 30, -195)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BCC)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000BCC)), 0, 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(3000)
        CALL(evt_msg_toge, 2, 379, 30, 133)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BDC)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000BDC)), 0, 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_msg_toge, 2, 293, 30, -180)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BEC)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000BEC)), 0, 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(5000)
        CALL(evt_msg_toge, 2, 200, 30, 133)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BFC)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000BFC)), 0, 0)
#endif
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
#ifdef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)str_0000028C)), 20, -20, 0, FLOAT(70.0f), 1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000C0C)), 0, STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000028C)), 20, -20, 0, FLOAT(70.0f), 1)
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000C0C)), 0, STRING(((char*)tou_03_str_0000028C)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000C1C)), 0, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000C1C)), 0, STRING(((char*)tou_03_str_0000045C)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000C2C)), 0, STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000C2C)), 0, STRING(((char*)tou_03_str_0000028C)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000C3C)), 0, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000C3C)), 0, STRING(((char*)tou_03_str_0000045C)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000C4C)), 0, STRING(((char*)str_0000028C)))
    CALL(evt_npc_set_ry, STRING(((char*)str_0000028C)), 270)
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000C4C)), 0, STRING(((char*)tou_03_str_0000028C)))
    CALL(evt_npc_set_ry, STRING(((char*)tou_03_str_0000028C)), 270)
#endif
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
#ifdef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)str_0000028C)), 0, -130, 0, FLOAT(70.0f), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000028C)), 0, -130, 0, FLOAT(70.0f), 1)
#endif
    END_INLINE_EVENT
    CALL(evt_mario_set_pos, -550, 0, 0)
    CALL(evt_party_set_pos, 0, -560, 0, -10)
    SET_FLOAT_VALUE(LW(0), FLOAT(-180.0f))
    CALL_CHILD(PTR(w_door_open))
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000794)), -565, 0, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000794)), -565, 0, 0, 0)
#endif
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
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000C5C)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000C5C)), 0, 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(3000)
        CALL(evt_msg_toge, 2, 200, 30, 200)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000C6C)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000C6C)), 0, 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_msg_toge, 2, -300, 200, -400)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000C7C)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000C7C)), 0, 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_msg_toge, 2, 200, 200, -300)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000C8C)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000C8C)), 0, 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(5000)
        CALL(evt_msg_toge, 2, 200, 30, 133)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000C9C)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000C9C)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(7000)
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)str_00000CAC)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)tou_03_str_00000CAC)))
#endif
    WAIT_MS(300)
    CALL(evt_party_run, 0)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_mario_mov_pos2, -280, 0, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_mario_mov_pos2, -280, 0, FLOAT((60.0f)))
#endif
        CALL(evt_cam3d_evt_set, 0, 192, 620, 0, 95, -145, 5000, 11)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000007EC)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_000007EC)), LW(0), LW(1), LW(2), 0)
#endif
        CALL(evt_mario_jump_pos, -250, 20, 0, 400, 1, -1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_0000091C)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_0000091C)), LW(0), LW(1), LW(2), 0)
#endif
        CALL(evt_mario_jump_pos, -215, 40, 0, 400, 1, -1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000B40)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000B40)), LW(0), LW(1), LW(2), 0)
#endif
        CALL(evt_mario_jump_pos, -185, 60, 0, 400, 1, -1000)
#ifdef NONMATCHING
        CALL(evt_mario_mov_pos2, -80, 0, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_mario_mov_pos2, -80, 0, FLOAT((60.0f)))
#endif
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(300)
#ifdef NONMATCHING
        CALL(evt_party_move_pos2, 0, -280, 25, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_party_move_pos2, 0, -280, 25, FLOAT((60.0f)))
#endif
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -250, 20, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -215, 40, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
        CALL(evt_party_jump_pos, 0, -185, 60, 25, 400, 1, -1000)
        WAIT_FRAMES(1)
#ifdef NONMATCHING
        CALL(evt_party_move_pos2, 0, -130, -25, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_party_move_pos2, 0, -130, -25, FLOAT((60.0f)))
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -426, 30, -195)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000CBC)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000CBC)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -379, 30, 233)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000CCC)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000CCC)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -293, 60, -180)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000CDC)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000CDC)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -272, 90, 300)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000CEC)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000CEC)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 2, -150, 100, -200)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000CFC)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000CFC)), 0, 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(1000)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
#ifdef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)str_0000028C)), STRING(((char*)str_00000D0C)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_0000028C)), STRING(((char*)tou_03_str_00000D0C)))
#endif
    WAIT_MS(200)
#ifdef NONMATCHING
    CALL(evt_npc_set_autotalkpose, STRING(((char*)str_0000028C)), STRING(((char*)str_00000230)), STRING(((char*)str_00000D10)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000D14)), 0, STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_autotalkpose, STRING(((char*)tou_03_str_0000028C)), STRING(((char*)tou_03_str_00000230)), STRING(((char*)tou_03_str_00000D10)))
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000D14)), 0, STRING(((char*)tou_03_str_0000028C)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000005A8)), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)tou_03_str_000005A8)), 0)
#endif
    BEGIN_INLINE_EVENT
        CALL(evt_cam3d_evt_set, 0, 250, 730, 0, 100, -154, 2000, 11)
    END_INLINE_EVENT
    WAIT_MS(1000)
    RETURN
EVT_END()

EVT_BEGIN(evt_champ_win)
    CALL(tou_champion_belt_onoff_28_text_29DC, 1)
    IF_INT_LESS(GSW(0), 172)
#ifdef NONMATCHING
        SET_VALUE(LW(15), STRING(((char*)str_000001E0)))
        SET_VALUE(LW(14), STRING(((char*)str_00000D24)))
        SET_VALUE(LW(13), STRING(((char*)str_00000D34)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(15), STRING(((char*)tou_03_str_000001E0)))
        SET_VALUE(LW(14), STRING(((char*)tou_03_str_00000D24)))
        SET_VALUE(LW(13), STRING(((char*)tou_03_str_00000D34)))
#endif
        ELSE
#ifdef NONMATCHING
        SET_VALUE(LW(15), STRING(((char*)str_0000028C)))
        SET_VALUE(LW(14), STRING(((char*)str_00000D44)))
        SET_VALUE(LW(13), STRING(((char*)str_00000D54)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(15), STRING(((char*)tou_03_str_0000028C)))
        SET_VALUE(LW(14), STRING(((char*)tou_03_str_00000D44)))
        SET_VALUE(LW(13), STRING(((char*)tou_03_str_00000D54)))
#endif
    END_IF
    CALL(evt_npc_set_position, LW(15), -20, 60, -50)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 80, 60, 0)
    CALL(evt_npc_get_position, STRING(((char*)str_0000045C)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000D64)), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_anim, STRING(((char*)str_0000045C)), STRING(((char*)str_000002E8)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)str_0000045C)), STRING(((char*)str_00000D78)), STRING(((char*)str_00000D80)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000045C)), 80, 60, 0)
    CALL(evt_npc_get_position, STRING(((char*)tou_03_str_0000045C)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000D64)), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_0000045C)), STRING(((char*)tou_03_str_000002E8)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)tou_03_str_0000045C)), STRING(((char*)tou_03_str_00000D78)), STRING(((char*)tou_03_str_00000D80)))
#endif
    CALL(evt_cam3d_evt_set, 80, 146, 273, 80, 96, -8, 0, 11)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, LW(14), 0, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, LW(14), 0, STRING(((char*)tou_03_str_0000045C)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -80, 146, 273, -80, 96, -8, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, LW(13), 0, LW(15))
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(1), 100)
#ifdef NONMATCHING
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING(((char*)str_000008C8)), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_00000A5C)))
#endif
#ifndef NONMATCHING
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)tou_03_str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING(((char*)tou_03_str_000008C8)), 0)
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_00000A5C)))
#endif
    CALL(evt_mario_set_dir, 270, 300, 0)
    WAIT_MS(400)
    CALL(evt_mario_set_dir, 90, 300, 0)
    WAIT_MS(400)
    CALL(evt_mario_set_dir, 270, 300, 0)
    WAIT_MS(400)
    CALL(evt_mario_set_dir, 90, 300, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000A64)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_00000A7C)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000A64)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_00000A7C)))
#endif
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000258)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000258)), LW(0), LW(1), LW(2), 0)
#endif
    END_INLINE_EVENT
    WAIT_MS(1000)
#ifdef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)str_000005B8)))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_000005B8)))
#endif
    CALL(evt_cam3d_evt_set, 1075, 547, 998, 0, 287, -8, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_cam3d_evt_set, -1024, 547, 1050, 0, 287, -8, 5000, 0)
    IF_INT_LESS(GSW(0), 172)
#ifdef NONMATCHING
        SET_VALUE(LW(15), STRING(((char*)str_00000D88)))
        SET_VALUE(LW(14), STRING(((char*)str_00000D98)))
        SET_VALUE(LW(13), STRING(((char*)str_00000DA8)))
        SET_VALUE(LW(12), STRING(((char*)str_00000DB8)))
        SET_VALUE(LW(11), STRING(((char*)str_00000DC8)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(15), STRING(((char*)tou_03_str_00000D88)))
        SET_VALUE(LW(14), STRING(((char*)tou_03_str_00000D98)))
        SET_VALUE(LW(13), STRING(((char*)tou_03_str_00000DA8)))
        SET_VALUE(LW(12), STRING(((char*)tou_03_str_00000DB8)))
        SET_VALUE(LW(11), STRING(((char*)tou_03_str_00000DC8)))
#endif
        ELSE
#ifdef NONMATCHING
        SET_VALUE(LW(15), STRING(((char*)str_00000DD8)))
        SET_VALUE(LW(14), STRING(((char*)str_00000DE8)))
        SET_VALUE(LW(13), STRING(((char*)str_00000DF8)))
        SET_VALUE(LW(12), STRING(((char*)str_00000E08)))
        SET_VALUE(LW(11), STRING(((char*)str_00000E18)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(15), STRING(((char*)tou_03_str_00000DD8)))
        SET_VALUE(LW(14), STRING(((char*)tou_03_str_00000DE8)))
        SET_VALUE(LW(13), STRING(((char*)tou_03_str_00000DF8)))
        SET_VALUE(LW(12), STRING(((char*)tou_03_str_00000E08)))
        SET_VALUE(LW(11), STRING(((char*)tou_03_str_00000E18)))
#endif
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
#ifdef NONMATCHING
    CALL(evt_npc_get_position, STRING(((char*)str_0000045C)), LW(0), LW(1), LW(2))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_get_position, STRING(((char*)tou_03_str_0000045C)), LW(0), LW(1), LW(2))
#endif
    ADD(LW(1), 100)
#ifdef NONMATCHING
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING(((char*)str_000008C8)), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)tou_03_str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING(((char*)tou_03_str_000008C8)), 0)
#endif
    CALL(evt_tou_get_fighter_info_28_text_3E58, GSW(501), LW(0), LW(1))
    IF_INT_LESS(GSW(0), 172)
#ifdef NONMATCHING
        SET_VALUE(LW(2), STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(2), STRING(((char*)tou_03_str_000001E0)))
#endif
        ELSE
#ifdef NONMATCHING
        SET_VALUE(LW(2), STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(2), STRING(((char*)tou_03_str_0000028C)))
#endif
    END_IF
#ifdef NONMATCHING
    CALL(evt_msg_print_insert, 0, STRING(((char*)str_000008E0)), 0, LW(2), LW(0))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_insert, 0, STRING(((char*)tou_03_str_000008E0)), 0, LW(2), LW(0))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 40, 142, 250, 40, 96, -8, 0, 0)
    WAIT_FRAMES(1)
    CALL(evt_tou_get_ranking_28_text_4048, LW(1))
    IF_INT_LESS(GSW(0), 172)
        IF_INT_EQUAL(GSWF(2383), 1)
#ifdef NONMATCHING
            SET_VALUE(LW(0), STRING(((char*)str_00000E28)))
#endif
#ifndef NONMATCHING
            SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000E28)))
#endif
            ELSE
            IF_INT_EQUAL(LW(1), 0)
#ifdef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)str_00000E38)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000E38)))
#endif
                ELSE
#ifdef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)str_00000E48)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000E48)))
#endif
            END_IF
        END_IF
        ELSE
        IF_INT_EQUAL(GSWF(2383), 1)
#ifdef NONMATCHING
            SET_VALUE(LW(0), STRING(((char*)str_00000E58)))
#endif
#ifndef NONMATCHING
            SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000E58)))
#endif
            ELSE
            IF_INT_EQUAL(LW(1), 0)
#ifdef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)str_00000E68)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000E68)))
#endif
                ELSE
#ifdef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)str_00000E78)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000E78)))
#endif
            END_IF
        END_IF
    END_IF
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, LW(0), 0, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, LW(0), 0, STRING(((char*)tou_03_str_0000045C)))
#endif
    WAIT_MS(300)
    RETURN
EVT_END()

EVT_BEGIN(evt_default_opening)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    IF_INT_LESS(GSW(0), 172)
#ifdef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)tou_03_str_000001E0)))
#endif
        ELSE
#ifdef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)tou_03_str_0000028C)))
#endif
    END_IF
    CALL(evt_npc_status_onoff, 1, LW(0), 2)
    CALL(evt_npc_set_position, LW(0), 0, 60, -130)
    CALL(evt_mario_set_pos, -350, 0, 0)
    CALL(evt_party_set_pos, 0, -390, 0, 25)
    CALL(evt_tou_get_fighter_num, GSW(501), LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 350, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000045C)), 350, 0, 0)
#endif
        CASE_EQUAL(2)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 350, 0, 0)
        CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 390, 0, 25)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000045C)), 350, 0, 0)
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000464)), 390, 0, 25)
#endif
        CASE_EQUAL(3)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 350, 0, 0)
        CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 390, 0, 25)
        CALL(evt_npc_set_position, STRING(((char*)str_0000044C)), 370, 0, -25)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000045C)), 350, 0, 0)
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000464)), 390, 0, 25)
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000044C)), 370, 0, -25)
#endif
        CASE_EQUAL(4)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 350, 0, 0)
        CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 390, 0, 25)
        CALL(evt_npc_set_position, STRING(((char*)str_0000044C)), 370, 0, -25)
        CALL(evt_npc_set_position, STRING(((char*)str_00000454)), 410, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000045C)), 350, 0, 0)
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000464)), 390, 0, 25)
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000044C)), 370, 0, -25)
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000454)), 410, 0, 0)
#endif
        CASE_EQUAL(5)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 350, 0, 0)
        CALL(evt_npc_set_position, STRING(((char*)str_00000464)), 390, 0, 25)
        CALL(evt_npc_set_position, STRING(((char*)str_0000044C)), 370, 0, -25)
        CALL(evt_npc_set_position, STRING(((char*)str_00000454)), 410, 0, 0)
        CALL(evt_npc_set_position, STRING(((char*)str_0000046C)), 430, 0, -25)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000045C)), 350, 0, 0)
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000464)), 390, 0, 25)
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000044C)), 370, 0, -25)
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_00000454)), 410, 0, 0)
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000046C)), 430, 0, -25)
#endif
    END_SWITCH
    CALL(evt_cam3d_evt_set, 0, 585, 1310, 0, 400, -145, 0, 11)
    IF_INT_LESS(GSW(0), 158)
        IF_INT_EQUAL(GSW(501), 0)
#ifdef NONMATCHING
            CALL(evt_npc_set_tribe, STRING(((char*)str_0000045C)), STRING(((char*)str_00000AA4)))
#endif
#ifndef NONMATCHING
            CALL(evt_npc_set_tribe, STRING(((char*)tou_03_str_0000045C)), STRING(((char*)tou_03_str_00000AA4)))
#endif
            BEGIN_INLINE_EVENT
#ifdef NONMATCHING
                CALL(tou_champion_belt_28_text_2A10, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
                CALL(tou_champion_belt_28_text_2A10, STRING(((char*)tou_03_str_0000045C)))
#endif
            END_INLINE_EVENT
        END_IF
    END_IF
    CALL(evt_seq_wait, 2)
#ifdef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000758)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)tou_03_str_00000758)))
#endif
    CALL(evt_cam3d_evt_set, 0, 331, 1310, 0, 145, -145, 3000, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, -280, 0, FLOAT(120.0f))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_0000091C)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_0000091C)), LW(0), LW(1), LW(2), 0)
#endif
        CALL(evt_mario_jump_pos, -250, 20, 0, 400, 1, -1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000B40)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000B40)), LW(0), LW(1), LW(2), 0)
#endif
        CALL(evt_mario_jump_pos, -215, 40, 0, 400, 1, -1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000007D0)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_000007D0)), LW(0), LW(1), LW(2), 0)
#endif
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
#ifdef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)tou_03_str_0000045C)))
#endif
                CASE_EQUAL(1)
#ifdef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)str_00000464)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000464)))
#endif
                CASE_EQUAL(2)
#ifdef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)str_0000044C)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)tou_03_str_0000044C)))
#endif
                CASE_EQUAL(3)
#ifdef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)str_00000454)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000454)))
#endif
                CASE_EQUAL(4)
#ifdef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)str_0000046C)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)tou_03_str_0000046C)))
#endif
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
#ifdef NONMATCHING
            SET_VALUE(LW(0), STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
            SET_VALUE(LW(0), STRING(((char*)tou_03_str_000001E0)))
#endif
            ELSE
#ifdef NONMATCHING
            SET_VALUE(LW(0), STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
            SET_VALUE(LW(0), STRING(((char*)tou_03_str_0000028C)))
#endif
        END_IF
        CALL(evt_tou_get_ranking_28_text_4048, LW(1))
        SWITCH(LW(1))
            CASE_EQUAL(0)
            IF_INT_LESS(GSW(0), 172)
#ifdef NONMATCHING
                SET_VALUE(LW(1), STRING(((char*)str_00000E88)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(1), STRING(((char*)tou_03_str_00000E88)))
#endif
                ELSE
#ifdef NONMATCHING
                SET_VALUE(LW(1), STRING(((char*)str_00000E98)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(1), STRING(((char*)tou_03_str_00000E98)))
#endif
            END_IF
            CASE_EQUAL(1)
            IF_INT_LESS(GSW(0), 172)
#ifdef NONMATCHING
                SET_VALUE(LW(1), STRING(((char*)str_00000EA8)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(1), STRING(((char*)tou_03_str_00000EA8)))
#endif
                ELSE
#ifdef NONMATCHING
                SET_VALUE(LW(1), STRING(((char*)str_00000EB8)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(1), STRING(((char*)tou_03_str_00000EB8)))
#endif
            END_IF
        END_SWITCH
        CALL(evt_msg_print, 0, LW(1), 0, LW(0))
        ELSE
        IF_INT_LESS(GSW(0), 172)
#ifdef NONMATCHING
            SET_VALUE(LW(3), STRING(((char*)str_000001E0)))
            SET_VALUE(LW(4), STRING(((char*)str_00000EC8)))
            SET_VALUE(LW(5), STRING(((char*)str_00000ED8)))
#endif
#ifndef NONMATCHING
            SET_VALUE(LW(3), STRING(((char*)tou_03_str_000001E0)))
            SET_VALUE(LW(4), STRING(((char*)tou_03_str_00000EC8)))
            SET_VALUE(LW(5), STRING(((char*)tou_03_str_00000ED8)))
#endif
            ELSE
#ifdef NONMATCHING
            SET_VALUE(LW(3), STRING(((char*)str_0000028C)))
            SET_VALUE(LW(4), STRING(((char*)str_00000EE8)))
            SET_VALUE(LW(5), STRING(((char*)str_00000EF8)))
#endif
#ifndef NONMATCHING
            SET_VALUE(LW(3), STRING(((char*)tou_03_str_0000028C)))
            SET_VALUE(LW(4), STRING(((char*)tou_03_str_00000EE8)))
            SET_VALUE(LW(5), STRING(((char*)tou_03_str_00000EF8)))
#endif
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
#ifdef NONMATCHING
                CALL(evt_msg_print_party, STRING(((char*)str_00000F08)))
#endif
#ifndef NONMATCHING
                CALL(evt_msg_print_party, STRING(((char*)tou_03_str_00000F08)))
#endif
                ELSE
#ifdef NONMATCHING
                CALL(evt_msg_print_party, STRING(((char*)str_00000F18)))
#endif
#ifndef NONMATCHING
                CALL(evt_msg_print_party, STRING(((char*)tou_03_str_00000F18)))
#endif
            END_IF
            WAIT_MS(300)
            ELSE
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_00000F28)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000F28)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
        END_IF
        ELSE
        CALL(evt_party_stop, 0)
        WAIT_MS(300)
#ifdef NONMATCHING
        CALL(evt_msg_print_party, STRING(((char*)str_00000F38)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print_party, STRING(((char*)tou_03_str_00000F38)))
#endif
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
#ifdef NONMATCHING
            SET_VALUE(LW(0), STRING(((char*)str_00000F48)))
#endif
#ifndef NONMATCHING
            SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000F48)))
#endif
            CASE_GREATER_OR_EQUAL(172)
            IF_INT_LESS_OR_EQUAL(LW(2), 10)
#ifdef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)str_00000F48)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000F48)))
#endif
            END_IF
        END_SWITCH
        CASE_EQUAL(0)
        SWITCH(GSW(0))
            CASE_LESS(172)
            IF_INT_EQUAL(LW(2), 1)
#ifdef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)str_00000F58)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000F58)))
#endif
            END_IF
            CASE_DEFAULT
            IF_INT_EQUAL(LW(2), 1)
#ifdef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)str_00000F68)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000F68)))
#endif
            END_IF
        END_SWITCH
    END_SWITCH
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, LW(0), 0, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, LW(0), 0, STRING(((char*)tou_03_str_0000045C)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 150, 141, 0, 100, -154, 0, 11)
    IF_INT_LESS(GSW(0), 172)
#ifdef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)str_000001E0)))
        SET_VALUE(LW(1), STRING(((char*)str_00000A18)))
        CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A0C)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)tou_03_str_000001E0)))
        SET_VALUE(LW(1), STRING(((char*)tou_03_str_00000A18)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00000A0C)))
#endif
        WAIT_MS(200)
#ifdef NONMATCHING
        CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A10)))
        CALL(evt_npc_set_autotalkpose, STRING(((char*)str_000001E0)), STRING(((char*)str_00000A10)), STRING(((char*)str_00000A14)))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00000A10)))
        CALL(evt_npc_set_autotalkpose, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00000A10)), STRING(((char*)tou_03_str_00000A14)))
#endif
        ELSE
#ifdef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)str_0000028C)))
        SET_VALUE(LW(1), STRING(((char*)str_00000F78)))
        CALL(evt_npc_set_anim, STRING(((char*)str_0000028C)), STRING(((char*)str_00000D0C)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)tou_03_str_0000028C)))
        SET_VALUE(LW(1), STRING(((char*)tou_03_str_00000F78)))
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_0000028C)), STRING(((char*)tou_03_str_00000D0C)))
#endif
        WAIT_MS(200)
#ifdef NONMATCHING
        CALL(evt_npc_set_autotalkpose, STRING(((char*)str_0000028C)), STRING(((char*)str_00000230)), STRING(((char*)str_00000D10)))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_autotalkpose, STRING(((char*)tou_03_str_0000028C)), STRING(((char*)tou_03_str_00000230)), STRING(((char*)tou_03_str_00000D10)))
#endif
    END_IF
    CALL(evt_msg_print, 0, LW(1), 0, LW(0))
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000005A8)), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)tou_03_str_000005A8)), 0)
#endif
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
#ifdef NONMATCHING
            SET_VALUE(LW(2), STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
            SET_VALUE(LW(2), STRING(((char*)tou_03_str_0000045C)))
#endif
            CASE_EQUAL(1)
#ifdef NONMATCHING
            SET_VALUE(LW(2), STRING(((char*)str_00000464)))
#endif
#ifndef NONMATCHING
            SET_VALUE(LW(2), STRING(((char*)tou_03_str_00000464)))
#endif
            CASE_EQUAL(2)
#ifdef NONMATCHING
            SET_VALUE(LW(2), STRING(((char*)str_0000044C)))
#endif
#ifndef NONMATCHING
            SET_VALUE(LW(2), STRING(((char*)tou_03_str_0000044C)))
#endif
            CASE_EQUAL(3)
#ifdef NONMATCHING
            SET_VALUE(LW(2), STRING(((char*)str_00000454)))
#endif
#ifndef NONMATCHING
            SET_VALUE(LW(2), STRING(((char*)tou_03_str_00000454)))
#endif
            CASE_EQUAL(4)
#ifdef NONMATCHING
            SET_VALUE(LW(2), STRING(((char*)str_0000046C)))
#endif
#ifndef NONMATCHING
            SET_VALUE(LW(2), STRING(((char*)tou_03_str_0000046C)))
#endif
        END_SWITCH
        CALL(confupose, LW(2), LW(3))
        CALL(evt_npc_set_anim, LW(2), LW(3))
        ADD(LW(1), 1)
    END_LOOP
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(1), 100)
#ifdef NONMATCHING
    CALL(evt_eff, 0, STRING(((char*)str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_eff, 0, STRING(((char*)tou_03_str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
#endif
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000A64)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_00000A7C)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000A64)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_00000A7C)))
#endif
    CALL_CHILD(PTR(evt_kime_pose))
    BEGIN_INLINE_EVENT
        WAIT_MS(100)
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000258)), LW(0), LW(1), LW(2), 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000258)), LW(0), LW(1), LW(2), 0)
#endif
    END_INLINE_EVENT
    IF_INT_LESS(GSW(0), 172)
#ifdef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)tou_03_str_000001E0)))
#endif
        ELSE
#ifdef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(0), STRING(((char*)tou_03_str_0000028C)))
#endif
    END_IF
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000F88)), 0, LW(0))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000F88)), 0, LW(0))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)str_000005B8)))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_000005B8)))
#endif
    CALL(evt_cam3d_evt_set, -65, 143, 263, -65, 95, -8, 0, 0)
    WAIT_FRAMES(1)
    IF_INT_LESS(GSW(0), 172)
        CALL(evt_mario_get_party, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(evt_party_stop, 0)
            WAIT_MS(300)
            CALL(evt_sub_random, 1000, LW(0))
            IF_INT_LESS(LW(0), 500)
#ifdef NONMATCHING
                CALL(evt_msg_print_party, STRING(((char*)str_00000F98)))
#endif
#ifndef NONMATCHING
                CALL(evt_msg_print_party, STRING(((char*)tou_03_str_00000F98)))
#endif
                ELSE
#ifdef NONMATCHING
                CALL(evt_msg_print_party, STRING(((char*)str_00000FA8)))
#endif
#ifndef NONMATCHING
                CALL(evt_msg_print_party, STRING(((char*)tou_03_str_00000FA8)))
#endif
            END_IF
            WAIT_MS(300)
        END_IF
        ELSE
        CALL(evt_party_stop, 0)
        WAIT_MS(300)
#ifdef NONMATCHING
        CALL(evt_msg_print_party, STRING(((char*)str_00000FB8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print_party, STRING(((char*)tou_03_str_00000FB8)))
#endif
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_default_lose)
    CALL(evt_cam3d_evt_set, 0, 220, 533, 0, 125, -8, 0, 0)
    CALL_CHILD(PTR(evt_damage_pose))
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_npc_get_position, STRING(((char*)str_0000045C)), LW(0), LW(1), LW(2))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_get_position, STRING(((char*)tou_03_str_0000045C)), LW(0), LW(1), LW(2))
#endif
    ADD(LW(1), 100)
#ifdef NONMATCHING
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING(((char*)str_000008C8)), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_eff, STRING((char*)zero_tou2_00009ea8), STRING(((char*)tou_03_str_000008BC)), 3, LW(0), LW(1), LW(2), 300, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING(((char*)tou_03_str_000008C8)), 0)
#endif
    CALL(evt_tou_get_fighter_info_28_text_3E58, GSW(501), LW(0), LW(1))
    IF_INT_LESS(GSW(0), 172)
#ifdef NONMATCHING
        SET_VALUE(LW(1), STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(1), STRING(((char*)tou_03_str_000001E0)))
#endif
        ELSE
#ifdef NONMATCHING
        SET_VALUE(LW(1), STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
        SET_VALUE(LW(1), STRING(((char*)tou_03_str_0000028C)))
#endif
    END_IF
#ifdef NONMATCHING
    CALL(evt_msg_print_insert, 0, STRING(((char*)str_000008E0)), 0, LW(1), LW(0))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_insert, 0, STRING(((char*)tou_03_str_000008E0)), 0, LW(1), LW(0))
#endif
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
#ifdef NONMATCHING
            SET_VALUE(LW(0), STRING(((char*)str_00000FC8)))
#endif
#ifndef NONMATCHING
            SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000FC8)))
#endif
            CASE_GREATER_OR_EQUAL(172)
            IF_INT_LESS_OR_EQUAL(LW(2), 10)
#ifdef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)str_00000FC8)))
#endif
#ifndef NONMATCHING
                SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000FC8)))
#endif
            END_IF
        END_SWITCH
    END_SWITCH
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, LW(1), 0, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, LW(1), 0, STRING(((char*)tou_03_str_0000045C)))
#endif
    WAIT_MS(300)
    RETURN
EVT_END()

static EVT_BEGIN(evt_champion)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
#ifdef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000ABC)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)tou_03_str_00000ABC)))
#endif
    CALL(evt_snd_bgm_scope, 0, 1)
#ifdef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000000F8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000104)), 1)
    CALL(evt_npc_status_onoff, 1, STRING(((char*)str_000001E0)), 2)
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), 0, 60, 0)
    CALL(evt_npc_set_ry, STRING(((char*)str_000001E0)), 270)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000001E0)), 32768)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_03_str_000000F8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_03_str_00000104)), 1)
    CALL(evt_npc_status_onoff, 1, STRING(((char*)tou_03_str_000001E0)), 2)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000001E0)), 0, 60, 0)
    CALL(evt_npc_set_ry, STRING(((char*)tou_03_str_000001E0)), 270)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000001E0)), 32768)
#endif
    CALL(evt_cam3d_evt_set, 0, 281, 1310, 0, 95, -145, 0, 11)
#ifdef NONMATCHING
    CALL(evt_npc_set_tribe, STRING(((char*)str_0000045C)), STRING(((char*)str_00000AA4)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_tribe, STRING(((char*)tou_03_str_0000045C)), STRING(((char*)tou_03_str_00000AA4)))
#endif
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(tou_champion_belt_28_text_2A10, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
        CALL(tou_champion_belt_28_text_2A10, STRING(((char*)tou_03_str_0000045C)))
#endif
    END_INLINE_EVENT
    CALL(evt_seq_wait, 2)
    WAIT_MS(2000)
#ifdef NONMATCHING
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_000001E0)), 32768)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)tou_03_str_000001E0)), 32768)
#endif
    CALL(evt_cam3d_evt_set, 0, 155, 327, 0, 96, -8, 0, 0)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000FD8)), 0, STRING(((char*)str_000001E0)))
    CALL(evt_npc_set_ry, STRING(((char*)str_000001E0)), 90)
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000FD8)), 0, STRING(((char*)tou_03_str_000001E0)))
    CALL(evt_npc_set_ry, STRING(((char*)tou_03_str_000001E0)), 90)
#endif
    WAIT_MS(1000)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000FE8)), 0, STRING(((char*)str_000001E0)))
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 550, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000FE8)), 0, STRING(((char*)tou_03_str_000001E0)))
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000045C)), 550, 0, 0)
#endif
    SET_FLOAT_VALUE(LW(0), FLOAT(-180.0f))
    CALL_CHILD(PTR(e_door_open))
    CALL(evt_cam3d_evt_set, 475, 134, 533, 475, 38, -8, 0, 0)
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000794)), 565, 0, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000794)), 565, 0, 0, 0)
#endif
        CALL(evt_sub_intpl_init, 11, -180, 0, 20)
        LOOP(21)
            CALL(evt_sub_intpl_get_value)
            CALL_CHILD(PTR(e_door_open))
        END_LOOP
    END_INLINE_EVENT
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)str_0000045C)), 450, 0, 0, FLOAT(60.0f), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000045C)), 450, 0, 0, FLOAT((60.0f)), 1)
#endif
        WAIT_MS(1000)
#ifdef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)str_0000045C)), 310, 0, 0, FLOAT(60.0f), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000045C)), 280, 20, 0, 500, 30)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000045C)), 245, 40, 0, 500, 30)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000045C)), 215, 60, 0, 500, 30)
        CALL(evt_npc_move_position, STRING(((char*)str_0000045C)), 80, 0, 0, FLOAT(60.0f), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000045C)), 310, 0, 0, FLOAT((60.0f)), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000045C)), 280, 20, 0, 500, 30)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000045C)), 245, 40, 0, 500, 30)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000045C)), 215, 60, 0, 500, 30)
        CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000045C)), 80, 0, 0, FLOAT((60.0f)), 1)
#endif
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_msg_toge, 2, 426, 30, -195)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000FF8)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00000FF8)), 0, 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(3000)
        CALL(evt_msg_toge, 2, 379, 30, 133)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00001008)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001008)), 0, 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_msg_toge, 2, 293, 30, -180)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00001018)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001018)), 0, 0)
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(5000)
        CALL(evt_msg_toge, 2, 200, 30, 133)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00001028)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001028)), 0, 0)
#endif
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
#ifdef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)str_000001E0)), 20, -20, 0, FLOAT(70.0f), 1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00001038)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)tou_03_str_000001E0)), 20, -20, 0, FLOAT(70.0f), 1)
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001038)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00001048)), 0, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001048)), 0, STRING(((char*)tou_03_str_0000045C)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00001058)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001058)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00001068)), 0, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001068)), 0, STRING(((char*)tou_03_str_0000045C)))
#endif
    WAIT_MS(300)
    WAIT_MS(1000)
    SET_VALUE(GSWF(2455), 1)
    CALL(evt_fade_set_mapchange_type, 0, 2, 300, 1, 300)
#ifdef NONMATCHING
    CALL(evt_bero_mapchange, STRING(((char*)str_00001078)), STRING(((char*)str_00001080)))
#endif
#ifndef NONMATCHING
    CALL(evt_bero_mapchange, STRING(((char*)tou_03_str_00001078)), STRING(((char*)tou_03_str_00001080)))
#endif
    RETURN
EVT_END()

EVT_BEGIN(evt_champion2)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
#ifdef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000ABC)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)tou_03_str_00000ABC)))
#endif
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_cam3d_evt_set, 50, 155, 273, 50, 106, -8, 0, 0)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_0000045C)), 80, 60, 0)
    CALL(evt_npc_set_ry, STRING(((char*)str_0000045C)), 270)
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), 20, 60, -20)
    CALL(evt_npc_set_ry, STRING(((char*)str_000001E0)), 90)
    CALL(evt_npc_set_tribe, STRING(((char*)str_0000045C)), STRING(((char*)str_00000AA4)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000045C)), 80, 60, 0)
    CALL(evt_npc_set_ry, STRING(((char*)tou_03_str_0000045C)), 270)
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000001E0)), 20, 60, -20)
    CALL(evt_npc_set_ry, STRING(((char*)tou_03_str_000001E0)), 90)
    CALL(evt_npc_set_tribe, STRING(((char*)tou_03_str_0000045C)), STRING(((char*)tou_03_str_00000AA4)))
#endif
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(tou_champion_belt_28_text_2A10, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
        CALL(tou_champion_belt_28_text_2A10, STRING(((char*)tou_03_str_0000045C)))
#endif
    END_INLINE_EVENT
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
#ifdef NONMATCHING
    CALL(evt_npc_set_ry, STRING(((char*)str_000001E0)), 270)
    CALL(evt_msg_print, 0, STRING(((char*)str_00001088)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_ry, STRING(((char*)tou_03_str_000001E0)), 270)
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001088)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -475, 134, 533, -475, 38, -8, 0, 0)
    WAIT_MS(3000)
    CALL(evt_cam3d_evt_set, 20, 155, 273, 20, 106, -8, 0, 0)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00001098)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001098)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 80, 155, 273, 80, 106, -8, 1000, 0)
    WAIT_MS(1000)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000010A8)), 0, STRING(((char*)str_0000045C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000010A8)), 0, STRING(((char*)tou_03_str_0000045C)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 20, 155, 273, 20, 106, -8, 1000, 0)
    WAIT_MS(1000)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001E0)), STRING(((char*)str_0000045C)))
    CALL(evt_msg_print, 0, STRING(((char*)str_000010B8)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_0000045C)))
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000010B8)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 850, 2160, 0, 287, -8, 10000, 0)
    WAIT_MS(7000)
    CALL(evt_fade_set_mapchange_type, 0, 2, 300, 1, 300)
#ifdef NONMATCHING
    CALL(evt_bero_mapchange, STRING(((char*)str_00001078)), STRING(((char*)str_000010C8)))
#endif
#ifndef NONMATCHING
    CALL(evt_bero_mapchange, STRING(((char*)tou_03_str_00001078)), STRING(((char*)tou_03_str_000010C8)))
#endif
    RETURN
EVT_END()

void kyaku_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}

void ext_kyaku_main(void) {
    pose_main();
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void ext_kyaku_dispent(void) {
#ifdef NONMATCHING
    dispEntry(CAMERA_3D, 0.0f, 1, kyaku_disp, NULL);
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, zero_tou2_0000ae40@ha
		lis r4, kyaku_disp@ha
		addi r6, r3, zero_tou2_0000ae40@l
		opword 0x90010014
		opword 0xC0260000
		addi r5, r4, kyaku_disp@l
		opword 0x38600004
		opword 0x38800001
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

static void screen_capture(CameraId cameraId, void* param) {
    GXSetTexCopySrc(0, 0, 0x260, 0x1E0);
    GXSetTexCopyDst(0x130, 0xF0, GX_TF_RGB565, GX_TRUE);
    GXCopyTex(screen_wp->buf, GX_FALSE);
    GXPixModeSync();
    screen_wp->ready = 1;
}

s32 screen_init(EventEntry* event, BOOL isFirstCall) {
    u32 size = GXGetTexBufferSize(0x260, 0x1E0, GX_TF_I4, GX_FALSE, 0);

    screen_wp = _mapAlloc(sizeof(ScreenWork));
    screen_wp->buf = _mapAlloc(size);
    screen_wp->ready = 0;
#ifdef NONMATCHING
    screen_wp->scale = screen_wp->scaleTarget = 1.0f;
    screen_wp->x = screen_wp->xTarget = 0.0f;
    screen_wp->y = screen_wp->yTarget = 0.0f;
#endif
#ifndef NONMATCHING
    screen_wp->scale = screen_wp->scaleTarget = EXT_LIT(float_1_tou2_0000ae44, 1.0f);
    screen_wp->x = screen_wp->xTarget = EXT_LIT(zero_tou2_0000ae40, 0.0f);
    screen_wp->y = screen_wp->yTarget = EXT_LIT(zero_tou2_0000ae40, 0.0f);
#endif
    screen_wp->count = 0;
#ifdef NONMATCHING
    screen_wp->field_0x28 = -1.0f;
#endif
#ifndef NONMATCHING
    screen_wp->field_0x28 = EXT_LIT(float_neg1_tou2_0000aea0, -1.0f);
#endif
    screen_wp->noise = _mapAlloc(GXGetTexBufferSize(64, 64, GX_TF_I8, GX_FALSE, 0));
    if (evtGetValue(event, GSW(0)) == 163) {
        screen_wp->mode = 1;
    }
    return EVT_RETURN_DONE;
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
static s32 screen_evt(EventEntry* event, BOOL isFirstCall) {
#ifdef NONMATCHING
    dispEntry(CAMERA_2D, 1000.0f, 0, screen_capture, NULL);
    return EVT_RETURN_BLOCK;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, float_1000_tou2_0000ae9c@ha
		lis r4, screen_capture@ha
		addi r6, r3, float_1000_tou2_0000ae9c@l
		opword 0x90010014
		opword 0xC0260000
		addi r5, r4, screen_capture@l
		opword 0x38600008
		opword 0x38800000
		opword 0x38C00000
		bl dispEntry
		opword 0x80010014
		opword 0x38600000
		opword 0x7C0803A6
		opword 0x38210010
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#pragma dont_inline on
void GXSetTexCoordGen(GXTexCoordID dst, GXTexGenType func, GXTexGenSrc src, u32 mtx) {
    GXSetTexCoordGen2(dst, func, src, mtx, GX_FALSE, GX_PTIDENTITY);
}
#pragma dont_inline reset

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void screen_tev(MapTevCallbackInfo* info) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FF20
		opword 0x7C0802A6
		lis r4, screen_wp@ha
		opword 0x900100E4
		opword 0xBEE100BC
		opword 0x7C7B1B78
		addi r3, r4, screen_wp@l
		opword 0x80630000
		opword 0x80030004
		opword 0x2C000000
		opword 0x4182065C
		opword 0x80030024
		opword 0x2C000000
		opword 0x418201D4
		opword 0x83A3002C
		opword 0x3B800000
		opword 0x5780F002
		opword 0x57840FFE
		opword 0x7C040050
		opword 0x7F851670
		opword 0x5403103E
		opword 0x38000040
		opword 0x7FE50194
		opword 0x578907FE
		opword 0x7FC32214
		opword 0x39400000
		opword 0x57E4402E
		opword 0x38A000FF
		opword 0x57C31838
		opword 0x7C0903A6
		opword 0x7D461E70
		opword 0x5540E804
		opword 0x55480FFE
		opword 0x394A0001
		opword 0x7D660194
		opword 0x7C080050
		opword 0x20C90000
		opword 0x5407183E
		opword 0x55602834
		opword 0x7CC63110
		opword 0x7CE74214
		opword 0x7C002214
		opword 0x7CA63038
		opword 0x7C003A14
		opword 0x7C001A14
		opword 0x7CDD01AE
		opword 0x4200FFC0
		bl rand
		opword 0x38800064
		opword 0x57F9402E
		opword 0x7C0323D6
		opword 0x57DA1838
		opword 0x3BC00000
		opword 0x7C0021D6
		opword 0x7C601850
		opword 0x3BE30064
		opword 0x480000A4
		bl rand
		opword 0x5460F002
		opword 0x54630FFE
		opword 0x7C030050
		opword 0x5400103E
		opword 0x7C601A14
		opword 0x3B030002
		bl rand
		opword 0x20980041
		opword 0x7C0323D6
		opword 0x7C0021D6
		opword 0x7EE01850
		bl rand
		opword 0x5460C00E
		opword 0x54630FFE
		opword 0x7C030050
		opword 0x7C97C214
		opword 0x5400403E
		opword 0x7EE5BB78
		opword 0x7C601A14
		opword 0x7C172050
		opword 0x5466063E
		opword 0x7C0903A6
		opword 0x7C172000
		opword 0x4080003C
		opword 0x7CA41E70
		opword 0x54A0E804
		opword 0x54A30FFE
		opword 0x38A50001
		opword 0x7C840194
		opword 0x7C030050
		opword 0x54842834
		opword 0x5400183E
		opword 0x7C84CA14
		opword 0x7C001A14
		opword 0x7C040214
		opword 0x7C00D214
		opword 0x7CDD01AE
		opword 0x4200FFCC
		opword 0x3BDE0001
		opword 0x7C1EF800
		opword 0x4180FF5C
		opword 0x3B9C0001
		opword 0x2C1C0040
		opword 0x4180FEAC
		opword 0x7FA3EB78
		opword 0x38801000
		bl DCFlushRange
		opword 0x7FA4EB78
		opword 0x38610008
		opword 0x38A00040
		opword 0x38C00040
		opword 0x38E00001
		opword 0x39000001
		opword 0x39200001
		opword 0x39400000
		bl GXInitTexObj
		lis r4, zero_tou2_0000ae40@ha
		opword 0x38610008
		addi r5, r4, zero_tou2_0000ae40@l
		opword 0x38800000
		opword 0xC0250000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0xFC400890
		opword 0x39000000
		opword 0xFC600890
		bl GXInitTexObjLOD
		opword 0x38610008
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x48000058
		opword 0x80830000
		opword 0x38610008
		opword 0x38A00130
		opword 0x38C000F0
		opword 0x38E00004
		opword 0x39000000
		opword 0x39200000
		opword 0x39400000
		bl GXInitTexObj
		lis r4, zero_tou2_0000ae40@ha
		opword 0x38610008
		addi r5, r4, zero_tou2_0000ae40@l
		opword 0x38800000
		opword 0xC0250000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0xFC400890
		opword 0x39000000
		opword 0xFC600890
		bl GXInitTexObjLOD
		opword 0x38610008
		opword 0x38800000
		bl GXLoadTexObj
		lis r4, inta_tex@ha
		opword 0x38610008
		addi r4, r4, inta_tex@l
		opword 0x38A00004
		opword 0x38C00008
		opword 0x38E00000
		opword 0x39000001
		opword 0x39200001
		opword 0x39400000
		bl GXInitTexObj
		lis r4, zero_tou2_0000ae40@ha
		opword 0x38610008
		addi r5, r4, zero_tou2_0000ae40@l
		opword 0x38800001
		opword 0xC0250000
		opword 0x38A00001
		opword 0x38C00000
		opword 0x38E00000
		opword 0xFC400890
		opword 0x39000000
		opword 0xFC600890
		bl GXInitTexObjLOD
		opword 0x38610008
		opword 0x38800001
		bl GXLoadTexObj
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00008
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600001
		opword 0x38800001
		opword 0x38A00001
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600001
		opword 0x3880000F
		opword 0x38A00008
		opword 0x38C00000
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600001
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00006
		bl GXSetTevAlphaIn
		lis r3, screen_wp@ha
		addi r5, r3, screen_wp@l
		opword 0x80C50000
		opword 0x80060024
		opword 0x2C000000
		opword 0x408201E4
		opword 0x80860020
		opword 0x386000C8
		opword 0x38040001
		opword 0x90060020
		opword 0x80850000
		opword 0x80840020
		opword 0x7C041BD6
		opword 0x7C0019D6
		opword 0x7C002051
		opword 0x408200CC
		bl rand
		opword 0x38800003
		opword 0x7C0323D6
		opword 0x7C0021D6
		opword 0x7C001850
		opword 0x2C000001
		opword 0x4182008C
		opword 0x408000AC
		opword 0x2C000000
		opword 0x4080000C
		opword 0x480000A0
		opword 0x4800009C
		lis r4, screen_wp@ha
		lis r3, float_1_tou2_0000ae44@ha
		addi r4, r4, screen_wp@l
		lis r5, zero_tou2_0000ae40@ha
		opword 0x80840000
		lfs f0, float_1_tou2_0000ae44@l(r3)
		opword 0xC0440008
		lfs f1, zero_tou2_0000ae40@l(r5)
		opword 0xEC001028
		opword 0xEC401024
		bl randf
		lis r4, screen_wp@ha
		lis r3, float_1_tou2_0000ae44@ha
		addi r6, r4, screen_wp@l
		lfs f0, float_1_tou2_0000ae44@l(r3)
		opword 0x80A60000
		lis r4, zero_tou2_0000ae40@ha
		opword 0xD0250014
		lfs f1, zero_tou2_0000ae40@l(r4)
		opword 0x80660000
		opword 0xC0430008
		opword 0xEC001028
		opword 0xEC401024
		bl randf
		lis r3, screen_wp@ha
		addi r3, r3, screen_wp@l
		opword 0x80630000
		opword 0xD023001C
		opword 0x48000028
		lis r4, float_1_tou2_0000ae44@ha
		lis r3, float_0p25_tou2_0000ae88@ha
		lfs f1, float_1_tou2_0000ae44@l(r4)
		lfs f2, float_0p25_tou2_0000ae88@l(r3)
		bl randf
		lis r3, screen_wp@ha
		addi r3, r3, screen_wp@l
		opword 0x80630000
		opword 0xD023000C
		lis r3, screen_wp@ha
		lis r4, float_60_tou2_0000ae84@ha
		addi r6, r3, screen_wp@l
		opword 0x80E60000
		addi r5, r4, float_60_tou2_0000ae84@l
		lis r3, float_1_tou2_0000ae44@ha
		opword 0xC0450000
		opword 0xC0270008
		addi r4, r3, float_1_tou2_0000ae44@l
		opword 0xC007000C
		opword 0x38610058
		opword 0xC0640000
		opword 0xEC000828
		opword 0xEC001024
		opword 0xEC01002A
		opword 0xD0070008
		opword 0x80860000
		opword 0xC0240010
		opword 0xC0040014
		opword 0xEC000828
		opword 0xEC001024
		opword 0xEC01002A
		opword 0xD0040010
		opword 0x80860000
		opword 0xC0240018
		opword 0xC004001C
		opword 0xEC000828
		opword 0xEC001024
		opword 0xEC01002A
		opword 0xD0040018
		opword 0x80860000
		opword 0xC0240008
		opword 0xFC400890
		bl PSMTXScale
		lis r4, screen_wp@ha
		lis r3, float_1_tou2_0000ae44@ha
		addi r4, r4, screen_wp@l
		lfs f0, float_1_tou2_0000ae44@l(r3)
		opword 0x80840000
		opword 0xC0240008
		opword 0xC0440018
		opword 0xEC000828
		opword 0xEC200824
		opword 0xFC020840
		opword 0x40810008
		opword 0xFC400890
		opword 0xC0040010
		opword 0xFC000840
		opword 0x40810008
		opword 0x48000008
		opword 0xFC200090
		lis r3, zero_tou2_0000ae40@ha
		lfs f3, zero_tou2_0000ae40@l(r3)
		opword 0x38610028
		bl PSMTXTrans
		opword 0x38610058
		opword 0x38810028
		opword 0x38A10088
		bl PSMTXConcat
		opword 0x48000024
		lis r6, float_4p75_tou2_0000ae8c@ha
		lis r5, float_3p75_tou2_0000ae90@ha
		lis r4, zero_tou2_0000ae40@ha
		lfs f1, float_4p75_tou2_0000ae8c@l(r6)
		lfs f2, float_3p75_tou2_0000ae90@l(r5)
		opword 0x38610088
		lfs f3, zero_tou2_0000ae40@l(r4)
		bl PSMTXScale
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0001E
		bl GXSetTexCoordGen
		opword 0x38610088
		opword 0x3880001E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x38600004
		bl camGetPtr
		lis r4, float_100_tou2_0000ae3c@ha
		opword 0xC0030014
		addi r5, r4, float_100_tou2_0000ae3c@l
		lis r6, float_1_tou2_0000ae44@ha
		opword 0xC0250000
		lis r5, float_6_tou2_0000ae98@ha
		lis r4, float_1000_tou2_0000ae9c@ha
		lis r3, float_16_tou2_0000ae94@ha
		opword 0xEC410028
		lfs f0, float_1000_tou2_0000ae9c@l(r4)
		lfs f1, float_1_tou2_0000ae44@l(r6)
		lfs f4, float_6_tou2_0000ae98@l(r5)
		opword 0xEC420024
		lfs f0, float_16_tou2_0000ae94@l(r3)
		opword 0x38610088
		opword 0xFC600890
		opword 0xEC4400BA
		bl PSMTXScale
		opword 0x38600001
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C00021
		bl GXSetTexCoordGen
		opword 0x38610088
		opword 0x38800021
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x38000002
		opword 0x901B000C
		opword 0x901B0014
		opword 0x901B0010
		opword 0xBAE100BC
		opword 0x800100E4
		opword 0x7C0803A6
		opword 0x382100E0
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

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

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
s32 burst_chain(EventEntry* event, BOOL isFirstCall) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	char _af_pad[28];
	asm volatile {
		opword 0x7C7B1B78
		opword 0x83830018
		opword 0x809C0000
		bl evtGetValue
		opword 0x809C0004
		opword 0x7C7C1B78
		opword 0x7F63DB78
		bl evtGetValue
		opword 0x7C601B78
		opword 0x7F83E378
		opword 0x7C1F0378
		bl npcNameToPtr
		lis r4, tou_03_str_0000187C@ha
		opword 0x7C7C1B78
		addi r4, r4, tou_03_str_0000187C@l
		opword 0x7FE5FB78
		la r3, _af_pad+0
		opword 0x38C00000
		opword 0x4CC63182
		bl sprintf
		opword 0x38610008
		bl npcNameToPtr
		opword 0x811C008C
		lis r7, float_3_tou2_0000ae74@ha
		opword 0x801C0090
		lis r6, float_1_tou2_0000ae44@ha
		lis r5, float_10_tou2_0000ae78@ha
		lis r4, float_210_tou2_0000ae7c@ha
		opword 0x9103008C
		lis r8, tou_03_str_0000187C@ha
		lfs f29, float_3_tou2_0000ae74@l(r7)
		li r27, 0x0
		opword 0x90030090
		lfs f30, float_1_tou2_0000ae44@l(r6)
		opword 0x801C0094
		addi r28, r8, tou_03_str_0000187C@l
		lfs f31, float_10_tou2_0000ae78@l(r5)
		opword 0x90030094
		lfs f28, float_210_tou2_0000ae7c@l(r4)
		opword 0x7F84E378
		opword 0x7FE5FB78
		opword 0x7F66DB78
		opword 0x38610008
		opword 0x4CC63182
		bl sprintf
		opword 0x38610008
		bl npcNameToPtr
		opword 0x7C7D1B78
		opword 0x7F84E378
		opword 0x7FE5FB78
		opword 0x38610008
		opword 0x38DB0001
		opword 0x4CC63182
		bl sprintf
		opword 0x38610008
		bl npcNameToPtr
		opword 0x7C7E1B78
		opword 0x387D008C
		opword 0xC01E0090
		opword 0x389E008C
		opword 0xEC00E828
		opword 0xD01E0090
		bl PSVECDistance
		opword 0xEC5F0824
		opword 0xC01D008C
		opword 0xC03E008C
		opword 0xEC5E1028
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01E008C
		opword 0xC01D0090
		opword 0xC03E0090
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01E0090
		opword 0xC01D0094
		opword 0xC03E0094
		opword 0xEC000828
		opword 0xEC02083A
		opword 0xD01E0094
		opword 0xC03E008C
		opword 0xFC01E040
		opword 0x41810014
		lis r3, float_neg210_tou2_0000ae80@ha
		lfs f0, float_neg210_tou2_0000ae80@l(r3)
		opword 0xFC010040
		opword 0x40800020
		lis r3, zero_tou2_0000ae40@ha
		opword 0xC03E0090
		lfs f0, zero_tou2_0000ae40@l(r3)
		opword 0xFC010040
		opword 0x40800024
		opword 0xD01E0090
		opword 0x4800001C
		lis r3, float_60_tou2_0000ae84@ha
		opword 0xC03E0090
		lfs f0, float_60_tou2_0000ae84@l(r3)
		opword 0xFC010040
		opword 0x40800008
		opword 0xD01E0090
		opword 0x3B7B0001
		opword 0x2C1B0004
		opword 0x4180FF04
		opword 0x38600000
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

s32 snd_sfx_stop(EventEntry* event, BOOL isFirstCall) {
    psndMapChange();
    return EVT_RETURN_DONE;
}

s32 confupose(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    NpcEntry* npc = npcNameToPtr((const char*)evtGetValue(event, args[0]));

    evtSetValue(event, args[1], (s32)npc->tribe->confuseAnimation);
    return EVT_RETURN_DONE;
}

#pragma dont_inline on
static f32 sinf(f32 x) {
    return sin(x);
}
#pragma dont_inline reset

#pragma dont_inline on
static f32 cosf(f32 x) {
    return cos(x);
}
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
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 item_jump(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FF80
		opword 0x7C0802A6
		opword 0x90010084
		opword 0xDBE10070
		opword 0xF3E10078
		opword 0xDBC10060
		opword 0xF3C10068
		opword 0xDBA10050
		opword 0xF3A10058
		opword 0xDB810040
		opword 0xF3810048
		opword 0xBFA10034
		opword 0x7C7E1B78
		opword 0x7C9D2378
		opword 0x83E30018
		opword 0x809F0000
		bl evtGetFloat
		opword 0xFFC00890
		opword 0x809F0004
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFFE00890
		opword 0x809F0008
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFFA00890
		lis r3, tou_03_str_00001130@ha
		addi r3, r3, tou_03_str_00001130@l
		bl itemNameToPtr
		opword 0x2C1D0000
		opword 0x7C7F1B78
		opword 0x41820078
		opword 0xC01F0040
		opword 0xFC20F090
		opword 0xFC40E890
		opword 0xC07F003C
		opword 0xEF9F0028
		opword 0xC09F0044
		bl distABf
		lis r4, float_1_tou2_0000ae44@ha
		lis r3, float_0p5_tou2_0000ae48@ha
		lfs f0, float_1_tou2_0000ae44@l(r4)
		opword 0xFC60F090
		lfs f6, float_0p5_tou2_0000ae48@l(r3)
		opword 0xFC80E890
		opword 0xECA10024
		opword 0xC03F003C
		opword 0xC05F0044
		opword 0xEC1C2824
		opword 0xD0A1000C
		opword 0xECA60172
		opword 0xEC0501BA
		opword 0xD0010010
		bl angleABf
		opword 0x8001000C
		opword 0xD0210008
		opword 0x80610010
		opword 0x901E0078
		opword 0x80010008
		opword 0x907E007C
		opword 0x901E0080
		lis r3, float_6p2832_tou2_0000ae4c@ha
		opword 0xC05E0080
		addi r4, r3, float_6p2832_tou2_0000ae4c@l
		opword 0xC09E0078
		opword 0xC0040000
		lis r3, float_360_tou2_0000ae50@ha
		opword 0xC07E007C
		opword 0xEC2000B2
		lfs f0, float_360_tou2_0000ae50@l(r3)
		opword 0xD081000C
		opword 0xEC210024
		opword 0xD0610010
		opword 0xD0410008
		bl sinf
		lis r3, float_6p2832_tou2_0000ae4c@ha
		lis r5, float_1_tou2_0000ae44@ha
		addi r4, r3, float_6p2832_tou2_0000ae4c@l
		opword 0xC0010008
		opword 0xC0440000
		lis r3, float_360_tou2_0000ae50@ha
		lfs f4, float_1_tou2_0000ae44@l(r5)
		opword 0xEC420032
		opword 0xC07F003C
		lfs f0, float_360_tou2_0000ae50@l(r3)
		opword 0xEC64187A
		opword 0xEC220024
		opword 0xD07F003C
		bl cosf
		lis r3, float_1_tou2_0000ae44@ha
		opword 0xC05F0044
		addi r5, r3, float_1_tou2_0000ae44@l
		opword 0xC001000C
		opword 0xC0A50000
		lis r4, float_0p5_tou2_0000ae48@ha
		lis r3, zero_tou2_0000ae40@ha
		opword 0xC0610010
		opword 0xEC85107C
		lfs f2, float_0p5_tou2_0000ae48@l(r4)
		opword 0xEC202828
		lfs f0, zero_tou2_0000ae40@l(r3)
		opword 0xEC431028
		opword 0xD09F0044
		opword 0xFC010040
		opword 0xC09F0040
		opword 0xD021000C
		opword 0xEC04182A
		opword 0xD0410010
		opword 0xD01F0040
		opword 0x40800078
		opword 0xD3DF003C
		lis r5, vec3_tou2_0000a6cc@ha
		lis r3, tou_03_str_00001864@ha
		opword 0x38810020
		opword 0xD3FF0040
		addi r7, r5, vec3_tou2_0000a6cc@l
		addi r3, r3, tou_03_str_00001864@l
		opword 0xD3BF0044
		opword 0x80C70000
		opword 0x80A70004
		opword 0x80070008
		opword 0x90C10014
		opword 0xC01F003C
		opword 0x90A10018
		opword 0xC03F0040
		opword 0xD0010014
		opword 0xC01F0044
		opword 0x9001001C
		opword 0x80C10014
		opword 0xD0210018
		opword 0xD001001C
		opword 0x80A10018
		opword 0x8001001C
		opword 0x90C10020
		opword 0x90A10024
		opword 0x90010028
		bl psndSFXOn_3D
		opword 0x38600001
		opword 0x48000018
		opword 0x8081000C
		opword 0x38600000
		opword 0x80010010
		opword 0x909E0078
		opword 0x901E007C
		opword 0xE3E10078
		opword 0xCBE10070
		opword 0xE3C10068
		opword 0xCBC10060
		opword 0xE3A10058
		opword 0xCBA10050
		opword 0xE3810048
		opword 0xCB810040
		opword 0xBBA10034
		opword 0x80010084
		opword 0x7C0803A6
		opword 0x38210080
	}
#endif
}
#ifdef NONMATCHING

s32 item_jump(EventEntry* event, BOOL isFirstCall) {
    return item_jump_sub(event, isFirstCall, 1.0f, 0.5f);
}
#endif
#ifndef NONMATCHING
#pragma pop
#endif

__declspec(section ".data") s32 block_data[] = {
#ifdef NONMATCHING
    (s32)((char*)str_000010E8), (s32)((char*)str_000010F0), (s32)((char*)str_000010F8), (s32)((char*)str_00001100), (s32)((char*)str_00001108), (s32)((char*)str_00001110), (s32)((char*)str_00001118), (s32)((char*)str_00001120),
    (s32)((char*)str_00001128),
#endif
#ifndef NONMATCHING
    (s32)((char*)tou_03_str_000010E8), (s32)((char*)tou_03_str_000010F0), (s32)((char*)tou_03_str_000010F8), (s32)((char*)tou_03_str_00001100), (s32)((char*)tou_03_str_00001108), (s32)((char*)tou_03_str_00001110), (s32)((char*)tou_03_str_00001118), (s32)((char*)tou_03_str_00001120),
    (s32)((char*)tou_03_str_00001128),
#endif
};

static EVT_BEGIN(evt_shake)
    LOOP(0)
#ifdef NONMATCHING
        CALL(evt_npc_get_position, STRING(((char*)str_000001E0)), LW(0), LW(1), LW(2))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_get_position, STRING(((char*)tou_03_str_000001E0)), LW(0), LW(1), LW(2))
#endif
        ADD(LW(0), 2)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), LW(0), LW(1), LW(2))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000001E0)), LW(0), LW(1), LW(2))
#endif
        WAIT_FRAMES(2)
#ifdef NONMATCHING
        CALL(evt_npc_get_position, STRING(((char*)str_000001E0)), LW(0), LW(1), LW(2))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_get_position, STRING(((char*)tou_03_str_000001E0)), LW(0), LW(1), LW(2))
#endif
        ADD(LW(0), -2)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), LW(0), LW(1), LW(2))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000001E0)), LW(0), LW(1), LW(2))
#endif
        WAIT_FRAMES(2)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_boss_stone)
    SET_VALUE(LW(10), 0)
#ifdef NONMATCHING
    CALL(evt_item_entry, STRING(((char*)str_00001130)), 116, 0, 0, 0, 17, -1, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_item_entry, STRING(((char*)tou_03_str_00001130)), 116, 0, 0, 0, 17, -1, 0)
#endif
    LOOP(0)
#ifdef NONMATCHING
        CALL(evt_mapobj_get_position, STRING(((char*)str_00001138)), LW(0), LW(1), LW(2))
#endif
#ifndef NONMATCHING
        CALL(evt_mapobj_get_position, STRING(((char*)tou_03_str_00001138)), LW(0), LW(1), LW(2))
#endif
        ADD_FLOAT(LW(1), FLOAT(20.0f))
        CALL(evt_sub_get_sincos, LW(10), LW(11), LW(12))
#ifdef NONMATCHING
        MULTIPLY_FLOAT(LW(12), FLOAT(10.0f))
#endif
#ifndef NONMATCHING
        MULTIPLY_FLOAT(LW(12), FLOAT((10.0f)))
#endif
        ADD(LW(1), LW(12))
        ADD(LW(10), FLOAT(2.5f))
        MODULO(LW(10), 360)
        IF_INT_LESS(LW(1), 50)
            CALL(starstone_sound_onoff, 0)
            ELSE
            CALL(starstone_sound_onoff, 1)
        END_IF
#ifdef NONMATCHING
        CALL(evt_item_set_position, STRING(((char*)str_00001130)), LW(0), LW(1), LW(2))
#endif
#ifndef NONMATCHING
        CALL(evt_item_set_position, STRING(((char*)tou_03_str_00001130)), LW(0), LW(1), LW(2))
#endif
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
s32 getY(EventEntry* event, BOOL isFirstCall) {
#ifdef NONMATCHING
    NpcEntry* npc = npcNameToPtr("\203K\203\223\203X");
    MapObject* obj = mapGetMapObj("block_5");
    Vec pos;
    f32 y;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		lis r3, tou_03_str_000001E0@ha
		opword 0x90010024
		addi r3, r3, tou_03_str_000001E0@l
		opword 0xBFC10018
		bl npcNameToPtr
		lis r4, tou_03_str_00001108@ha
		opword 0x7C7E1B78
		addi r3, r4, tou_03_str_00001108@l
		bl mapGetMapObj
		lis r4, tou_03_str_00001840@ha
		opword 0x7C7F1B78
		addi r3, r4, tou_03_str_00001840@l
		opword 0x38810008
		bl mapObjGetPos
		lis r3, float_100_tou2_0000ae3c@ha
		opword 0xC03F0038
		lfs f2, float_100_tou2_0000ae3c@l(r3)
		opword 0xC001000C
		opword 0xEC22082A
		opword 0xFC010040
		opword 0x4081000C
		opword 0xD03E0090
		opword 0x4800001C
		lis r3, zero_tou2_0000ae40@ha
		lfs f0, zero_tou2_0000ae40@l(r3)
		opword 0xD01E0094
		opword 0xD01E008C
		opword 0xC001000C
		opword 0xD01E0090
		opword 0xBBC10018
		opword 0x38600002
		opword 0x80010024
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    mapObjGetPos("group151", &pos);
    y = 100.0f + obj->modelWorldMtx[1][3];
    if (y > pos.y) {
        npc->position.y = y;
    } else {
        npc->position.x = npc->position.z = 0.0f;
        npc->position.y = pos.y;
    }
    return EVT_RETURN_DONE;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 starstone_sound_onoff(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		opword 0x93E1000C
		opword 0x80830018
		opword 0x80840000
		bl evtGetValue
		lis r4, tou_03_str_00001130@ha
		opword 0x7C7F1B78
		addi r3, r4, tou_03_str_00001130@l
		bl itemNameToPtr
		opword 0x8083001C
		opword 0x28040000
		opword 0x41820034
		opword 0x2C1F0000
		opword 0x40820014
		opword 0x8064000C
		opword 0xA0030004
		opword 0x540007B8
		opword 0xB0030004
		opword 0x2C1F0001
		opword 0x40820014
		opword 0x8064000C
		opword 0xA0030004
		opword 0x60000004
		opword 0xB0030004
		opword 0x80010014
		opword 0x38600002
		opword 0x83E1000C
		opword 0x7C0803A6
		opword 0x38210010
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
s32 starstone_sound_onoff(EventEntry* event, BOOL isFirstCall) {
    s32 flag = evtGetValue(event, event->args[0]);
    EffectEntry* eff = itemNameToPtr("stone")->effect;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 evt_boss_stone_r(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0xBFA10014
		opword 0x7C7D1B78
		lis r3, tou_03_str_00001130@ha
		addi r3, r3, tou_03_str_00001130@l
		opword 0x83FD0018
		bl itemNameToPtr
		opword 0x83C3001C
		opword 0x7FA3EB78
		opword 0x809F0000
		bl evtGetFloat
		opword 0x809E000C
		opword 0x38600002
		opword 0xD024001C
		opword 0xBBA10014
		opword 0x80010024
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    if (eff) {
        if (flag == 0) {
            ((StoneEffWork3*)eff->userdata)->flags &= ~4;
        }
        if (flag == 1) {
            ((StoneEffWork3*)eff->userdata)->flags |= 4;
        }
    }
    return EVT_RETURN_DONE;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 eff_pos(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, tou_03_str_00001130@ha
		opword 0x90010014
		addi r3, r3, tou_03_str_00001130@l
		opword 0xBFC10008
		bl itemNameToPtr
		lis r4, tou_03_str_00001488@ha
		opword 0x7C7E1B78
		addi r3, r4, tou_03_str_00001488@l
		bl effNameToPtr
		lis r4, tou_03_str_00001450@ha
		opword 0x7C7F1B78
		addi r3, r4, tou_03_str_00001450@l
		bl effNameToPtr
		opword 0x281E0000
		opword 0x41820074
		opword 0x281F0000
		opword 0x41820034
		opword 0xC01E003C
		lis r4, float_15_tou2_0000ae2c@ha
		opword 0x80BF000C
		lfs f1, float_15_tou2_0000ae2c@l(r4)
		opword 0xD0050004
		opword 0xC01E0040
		opword 0x809F000C
		opword 0xEC01002A
		opword 0xD0040008
		opword 0xC01E0044
		opword 0x809F000C
		opword 0xD004000C
		opword 0x28030000
		opword 0x41820034
		opword 0xC01E003C
		lis r4, float_15_tou2_0000ae2c@ha
		opword 0x80A3000C
		lfs f1, float_15_tou2_0000ae2c@l(r4)
		opword 0xD0050004
		opword 0xC01E0040
		opword 0x8083000C
		opword 0xEC01002A
		opword 0xD0040008
		opword 0xC01E0044
		opword 0x8063000C
		opword 0xD003000C
		opword 0xBBC10008
		opword 0x38600000
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
s32 evt_boss_stone_r(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    EffectEntry* eff = itemNameToPtr("stone")->effect;
#endif

#ifdef NONMATCHING
    ((StoneEffWork2*)eff->userdata)->rot = evtGetFloat(event, args[0]);
    return EVT_RETURN_DONE;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
static void callback(MapTevCallbackInfo* info) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		lis r4, dat_tou2_0000a738@ha
		opword 0x90010034
		opword 0xBF61001C
		opword 0x7C7B1B78
		lis r3, gans_alpha@ha
		lwz r5, dat_tou2_0000a738@l(r4)
		opword 0x3881000C
		lwz r0, gans_alpha@l(r3)
		opword 0x38600001
		opword 0x90A10008
		opword 0x83FB000C
		opword 0x9801000B
		opword 0x83DB0010
		opword 0x83BB0014
		opword 0x839B0018
		opword 0x80010008
		opword 0x9001000C
		bl GXSetTevColor
		opword 0x7FE3FB78
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7FE3FB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7FE3FB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7FE3FB78
		opword 0x38800000
		opword 0x38A00002
		opword 0x38C00003
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7FE3FB78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		opword 0x7FE3FB78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x381F0001
		opword 0x901B000C
		opword 0x93BB0014
		opword 0x939B0018
		opword 0x93DB0010
		opword 0xBB61001C
		opword 0x80010034
		opword 0x7C0803A6
		opword 0x38210030
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
s32 eff_pos(EventEntry* event, BOOL isFirstCall) {
    ItemEntry* item = itemNameToPtr("stone");
    EffectEntry* eff1 = effNameToPtr("eff_1");
    EffectEntry* eff2 = effNameToPtr("eff_2");
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 gans_white_on(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, tou_03_str_000001E0@ha
		opword 0x90010014
		addi r3, r3, tou_03_str_000001E0@l
		opword 0x93E1000C
		opword 0x7C9F2378
		bl npcNameToPtr
		opword 0x2C1F0000
		opword 0x7C7F1B78
		opword 0x41820030
		lis r4, gans_alpha@ha
		opword 0x38000000
		addi r5, r4, gans_alpha@l
		lis r3, callback@ha
		opword 0x90050000
		addi r4, r3, callback@l
		opword 0x3860000C
		bl mapSetTevCallback
		opword 0x807F0104
		opword 0x3C800C00
		bl animPoseSetMaterialFlagOn
		lis r3, gans_alpha@ha
		addi r4, r3, gans_alpha@l
		opword 0x80640000
		opword 0x38030005
		opword 0x2C0000FF
		opword 0x90040000
		opword 0x40810014
		opword 0x380000FF
		opword 0x38600002
		opword 0x90040000
		opword 0x48000008
		opword 0x38600000
		opword 0x80010014
		opword 0x83E1000C
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 gans_white_off(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, tou_03_str_000001E0@ha
		opword 0x90010014
		addi r3, r3, tou_03_str_000001E0@l
		opword 0x93E1000C
		bl npcNameToPtr
		opword 0x7C7F1B78
		opword 0x3860000C
		opword 0x38800000
		bl mapSetTevCallback
		opword 0x807F0104
		opword 0x3C800C00
		bl animPoseSetMaterialFlagOff
		opword 0x80010014
		opword 0x38600002
		opword 0x83E1000C
		opword 0x7C0803A6
		opword 0x38210010
	}
#endif
}
#ifdef NONMATCHING

static inline void cb_set_color(u8 a) {
    GXColor color = {255, 255, 255, 0};

    color.a = a;
    GXSetTevColor(GX_TEVREG0, color);
}

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

s32 gans_white_off(EventEntry* event, BOOL isFirstCall) {
    NpcEntry* npc = npcNameToPtr("\203K\203\223\203X");

    mapSetTevCallback(12, NULL);
    animPoseSetMaterialFlagOff(npc->poseId, 0xC000000);
    return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
#pragma pop
#endif

static EVT_BEGIN(evt_boss)
#ifdef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_0000114C)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)str_00001154)), 0, 0)
    SET_VALUE(LW(0), STRING(((char*)str_00000144)))
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_03_str_0000114C)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)tou_03_str_00001154)), 0, 0)
    SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000144)))
#endif
    CALL_CHILD(PTR(bero_case_switch_off))
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), 0, 60, 0)
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001E0)), STRING(((char*)str_0000078C)))
    CALL(evt_npc_set_tribe, STRING(((char*)str_000001E0)), STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000001E0)), 0, 60, 0)
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_0000078C)))
    CALL(evt_npc_set_tribe, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_000001E0)))
#endif
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
#ifdef NONMATCHING
        IF_STR_EQUAL(LW(9), STRING(((char*)str_00001160)))
#endif
#ifndef NONMATCHING
        IF_STR_EQUAL(LW(9), STRING(((char*)tou_03_str_00001160)))
#endif
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_cam3d_evt_set, 0, 197, 484, 0, 110, -8, 2000, 11)
#ifdef NONMATCHING
    CALL(evt_mario_mov_pos2, -75, 0, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_mov_pos2, -75, 0, FLOAT((60.0f)))
#endif
    CALL(evt_mario_set_dir, 90, 200, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_party_set_dir, 0, 90, 200)
#ifdef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00001168)))
    CALL(evt_msg_print, 0, STRING(((char*)str_0000117C)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)tou_03_str_00001168)))
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_0000117C)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_snd_sfxon, STRING(((char*)str_0000118C)), LW(10))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon, STRING(((char*)tou_03_str_0000118C)), LW(10))
#endif
        CALL(evt_cam_shake, 4, FLOAT(0.0029296875f), FLOAT(0.0029296875f), 13000)
        CALL(evt_snd_sfxoff, LW(10))
    END_INLINE_EVENT
    WAIT_MS(1000)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000820)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)str_0000056C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00000820)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)tou_03_str_0000056C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#endif
    CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
    IF_INT_GREATER(LW(1), 50)
#ifdef NONMATCHING
        CALL(evt_eff_fukidashi, 3, STRING(((char*)str_000011A4)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_eff_fukidashi, 3, STRING(((char*)tou_03_str_000011A4)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#endif
    END_IF
    CALL(evt_mario_dispflag_onoff, 1, 2)
#ifdef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)str_0000083C)))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_0000083C)))
#endif
    CALL(evt_cam3d_evt_set, 0, 242, 821, 0, 96, -8, 3000, 11)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_party_move_pos2, 0, -180, 0, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_party_move_pos2, 0, -180, 0, FLOAT((60.0f)))
#endif
        CALL(evt_party_set_dir, 0, 90, 200)
        CALL(evt_party_stop, 0)
    END_INLINE_EVENT
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_mario_jump_pos, -150, 60, 0, 500, 0, -1000)
    CALL(evt_mario_set_dir, 90, 200, 0)
#ifdef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000011A8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000011B0)), 1)
    CALL(evt_map_playanim, STRING(((char*)str_000011B8)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_000011C0)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_000011CC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_000011D4)), 0, 0)
    CALL(evt_map_playanim, STRING(((char*)str_000011DC)), 1, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)tou_03_str_000011A8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_03_str_000011B0)), 1)
    CALL(evt_map_playanim, STRING(((char*)tou_03_str_000011B8)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)tou_03_str_000011C0)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)tou_03_str_000011CC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)tou_03_str_000011D4)), 0, 0)
    CALL(evt_map_playanim, STRING(((char*)tou_03_str_000011DC)), 1, 0)
#endif
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
#ifdef NONMATCHING
        CALL(evt_map_pauseanim, 0, STRING(((char*)str_000011D4)))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000011E4)), 0, 60, 0, LW(10))
#endif
#ifndef NONMATCHING
        CALL(evt_map_pauseanim, 0, STRING(((char*)tou_03_str_000011D4)))
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_000011E4)), 0, 60, 0, LW(10))
#endif
        WAIT_MS(2000)
#ifdef NONMATCHING
        CALL(evt_map_replayanim, 0, STRING(((char*)str_000011D4)))
        CALL(evt_map_checkanim, STRING(((char*)str_000011D4)), LW(0), LW(1))
#endif
#ifndef NONMATCHING
        CALL(evt_map_replayanim, 0, STRING(((char*)tou_03_str_000011D4)))
        CALL(evt_map_checkanim, STRING(((char*)tou_03_str_000011D4)), LW(0), LW(1))
#endif
        SUBTRACT(LW(1), 100)
        WAIT_MS(LW(1))
        CALL(evt_snd_sfxoff, LW(10))
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001200)), 0, 60, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00001200)), 0, 60, 0, 0)
#endif
    END_INLINE_EVENT
    SET_INT_READ_ADDR(PTR(block_data))
    LOOP(9)
        READ_INT(LW(5))
        BEGIN_INLINE_EVENT
            CALL(evt_mapobj_get_position, LW(5), LW(0), LW(1), LW(2))
            LOOP(0)
                CALL(evt_mapobj_get_position, LW(5), LW(10), LW(11), LW(12))
                IF_INT_NOT_EQUAL(LW(1), LW(11))
#ifdef NONMATCHING
                    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001220)), LW(10), LW(11), LW(12), 0)
#endif
#ifndef NONMATCHING
                    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00001220)), LW(10), LW(11), LW(12), 0)
#endif
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_LOOP
#ifdef NONMATCHING
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_000001E0)), 1024)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)tou_03_str_000001E0)), 1024)
#endif
    LOOP(0)
#ifdef NONMATCHING
        CALL(evt_map_checkanim, STRING(((char*)str_000011D4)), LW(0), LW(1))
#endif
#ifndef NONMATCHING
        CALL(evt_map_checkanim, STRING(((char*)tou_03_str_000011D4)), LW(0), LW(1))
#endif
        IF_INT_EQUAL(LW(0), 1)
            BREAK_LOOP
        END_IF
        CALL(getY)
        WAIT_FRAMES(1)
    END_LOOP
#ifdef NONMATCHING
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000001E0)), 1024)
    CALL(evt_hitobj_onoff, STRING(((char*)str_00001234)), 1, 1)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000001E0)), 1024)
    CALL(evt_hitobj_onoff, STRING(((char*)tou_03_str_00001234)), 1, 1)
#endif
    WAIT_MS(1000)
    CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
    IF_INT_GREATER(LW(1), 50)
#ifdef NONMATCHING
        CALL(evt_eff_fukidashi, 3, STRING(((char*)str_000011A4)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_eff_fukidashi, 3, STRING(((char*)tou_03_str_000011A4)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#endif
    END_IF
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 0, 305, 384, 0, 325, -15, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_toge, 1, 0, 0, 0)
#ifdef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)str_0000123C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)tou_03_str_0000123C)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 155, 288, 0, 105, -8, 0, 11)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_0000124C)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_0000124C)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    WAIT_MS(300)
    CALL(evt_mario_dispflag_onoff, 1, 2)
#ifdef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)str_00000580)))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_00000580)))
#endif
    CALL(evt_party_set_pos, 0, -180, 60, 0)
    CALL(evt_party_stop, 0)
    WAIT_FRAMES(1)
    CALL(evt_cam3d_evt_set, -150, 155, 288, -150, 105, -8, 500, 11)
    WAIT_MS(500)
#ifdef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)str_0000125C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)tou_03_str_0000125C)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 155, 288, 0, 105, -8, 0, 11)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_0000126C)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_0000126C)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_0000127C)))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_0000127C)))
#endif
        WAIT_MS(333)
#ifdef NONMATCHING
        CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00001280)))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00001280)))
#endif
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SET_VALUE(GF(10), 0)
#ifdef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001284)), 0, 60, 0, LW(9))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00001284)), 0, 60, 0, LW(9))
#endif
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
#ifdef NONMATCHING
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        CALL(evt_map_set_playrate, STRING(((char*)str_000011B8)), LW(0))
        CALL(evt_map_set_playrate, STRING(((char*)str_000011CC)), LW(0))
        CALL(evt_map_set_playrate, STRING(((char*)str_000011C0)), LW(0))
#endif
#ifndef NONMATCHING
        DIVIDE_FLOAT(LW(0), FLOAT((100.0f)))
        CALL(evt_map_set_playrate, STRING(((char*)tou_03_str_000011B8)), LW(0))
        CALL(evt_map_set_playrate, STRING(((char*)tou_03_str_000011CC)), LW(0))
        CALL(evt_map_set_playrate, STRING(((char*)tou_03_str_000011C0)), LW(0))
#endif
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
#ifdef NONMATCHING
    CALL(evt_npc_get_position, STRING(((char*)str_000001E0)), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_0000129C)), LW(10), LW(11), LW(12), 0)
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00000224)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_get_position, STRING(((char*)tou_03_str_000001E0)), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_0000129C)), LW(10), LW(11), LW(12), 0)
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00000224)))
#endif
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 100, 200, 300)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            CALL(evt_npc_set_scale, STRING(((char*)str_000001E0)), LW(0), LW(0), LW(0))
#endif
#ifndef NONMATCHING
            DIVIDE_FLOAT(LW(0), FLOAT((100.0f)))
            CALL(evt_npc_set_scale, STRING(((char*)tou_03_str_000001E0)), LW(0), LW(0), LW(0))
#endif
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 170, 385, 0, 135, -11, 300, 11)
    WAIT_MS(300)
    CALL(gans_white_on)
#ifdef NONMATCHING
    CALL(evt_paper_entry, STRING(((char*)str_000012B0)))
    CALL(evt_npc_get_position, STRING(((char*)str_000001E0)), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING(((char*)str_000002B0)), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_ry, STRING(((char*)str_000002B0)), 270)
    CALL(evt_npc_set_width, STRING(((char*)str_000002B0)), 60)
    CALL(evt_npc_set_height, STRING(((char*)str_000002B0)), 80)
    CALL(evt_snd_sfxon, STRING(((char*)str_000012BC)), 0)
    CALL(evt_npc_set_paper, STRING(((char*)str_000001E0)), STRING(((char*)str_000012B0)))
    CALL(evt_npc_set_paper_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_000012D0)))
#endif
#ifndef NONMATCHING
    CALL(evt_paper_entry, STRING(((char*)tou_03_str_000012B0)))
    CALL(evt_npc_get_position, STRING(((char*)tou_03_str_000001E0)), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000002B0)), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_ry, STRING(((char*)tou_03_str_000002B0)), 270)
    CALL(evt_npc_set_width, STRING(((char*)tou_03_str_000002B0)), 60)
    CALL(evt_npc_set_height, STRING(((char*)tou_03_str_000002B0)), 80)
    CALL(evt_snd_sfxon, STRING(((char*)tou_03_str_000012BC)), 0)
    CALL(evt_npc_set_paper, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_000012B0)))
    CALL(evt_npc_set_paper_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_000012D0)))
#endif
    WAIT_MS(2500)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), 0, -1000, 0)
    CALL(evt_npc_clear_paper, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000001E0)), 0, -1000, 0)
    CALL(evt_npc_clear_paper, STRING(((char*)tou_03_str_000001E0)))
#endif
    CALL(gans_white_off)
    DELETE_EVENT(LW(9))
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000012D4)), 0, STRING(((char*)str_000002B0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000012D4)), 0, STRING(((char*)tou_03_str_000002B0)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -150, 155, 288, -150, 105, -8, 0, 11)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)str_000012E4)))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_000012E4)))
#endif
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_mario_jump_pos, LW(0), LW(1), LW(2), 300, 0, -1000)
#ifdef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)str_000012EC)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)tou_03_str_000012EC)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 170, 385, 0, 135, -11, 0, 11)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000012FC)), 0, STRING(((char*)str_000002B0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000012FC)), 0, STRING(((char*)tou_03_str_000002B0)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 210, 852, 0, 135, -12, 1000, 11)
    CALL(evt_snd_bgmoff, 512)
#ifdef NONMATCHING
    CALL(evt_npc_set_battle_info, STRING(((char*)str_000002B0)), 23)
    CALL(evt_npc_battle_start, STRING(((char*)str_000002B0)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_battle_info, STRING(((char*)tou_03_str_000002B0)), 23)
    CALL(evt_npc_battle_start, STRING(((char*)tou_03_str_000002B0)))
#endif
    CALL(evt_npc_wait_battle_end)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_0000130C)), LW(15))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)tou_03_str_0000130C)), LW(15))
#endif
    CALL(evt_snd_sfx_vol, LW(15), 38)
    CALL(evt_mario_dispflag_onoff, 0, 2)
#ifdef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)str_000005B8)))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_000005B8)))
#endif
    CALL(evt_party_stop, 0)
#ifdef NONMATCHING
    CALL(evt_npc_get_position, STRING(((char*)str_000002B0)), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING(((char*)str_000002B0)), 0, -1000, 0)
    CALL(evt_npc_set_scale, STRING(((char*)str_000001E0)), FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    CALL(evt_npc_set_anim, STRING(((char*)str_000001E0)), STRING(((char*)str_00001324)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)str_000001E0)), STRING(((char*)str_00001324)), STRING(((char*)str_00001328)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_get_position, STRING(((char*)tou_03_str_000002B0)), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000001E0)), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000002B0)), 0, -1000, 0)
    CALL(evt_npc_set_scale, STRING(((char*)tou_03_str_000001E0)), FLOAT((1.0f)), FLOAT((1.0f)), FLOAT((1.0f)))
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00001324)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)tou_03_str_000001E0)), STRING(((char*)tou_03_str_00001324)), STRING(((char*)tou_03_str_00001328)))
#endif
    CALL(evt_cam3d_evt_set, 0, 140, 385, 0, 105, -11, 0, 11)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_0000132C)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_0000132C)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    WAIT_MS(300)
    SET_VALUE(GF(10), 1)
    CALL(evt_cam3d_evt_set, -130, 140, 385, -130, 105, -11, 700, 11)
    WAIT_MS(700)
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
#ifdef NONMATCHING
        CALL(evt_snd_bgmon_f, 768, STRING(((char*)str_0000133C)), 3000)
#endif
#ifndef NONMATCHING
        CALL(evt_snd_bgmon_f, 768, STRING(((char*)tou_03_str_0000133C)), 3000)
#endif
    END_INLINE_EVENT
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_0000028C)), -325, 0, 0)
    CALL(evt_npc_status_onoff, 1, STRING(((char*)str_0000028C)), 2)
    CALL(evt_msg_print, 0, STRING(((char*)str_0000134C)), 0, STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000028C)), -325, 0, 0)
    CALL(evt_npc_status_onoff, 1, STRING(((char*)tou_03_str_0000028C)), 2)
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_0000134C)), 0, STRING(((char*)tou_03_str_0000028C)))
#endif
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_0000135C)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)str_0000056C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, STRING(((char*)str_000011A4)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_0000135C)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)tou_03_str_0000056C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, STRING(((char*)tou_03_str_000011A4)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#endif
    WAIT_MS(1500)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 270, 200, 0)
    END_INLINE_EVENT
    CALL(evt_party_set_dir, 0, 270, 200)
    CALL(evt_cam3d_evt_set, -320, 95, 287, -320, 40, -8, 1000, 11)
    WAIT_MS(1000)
    WAIT_MS(333)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00001374)), 0, STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001374)), 0, STRING(((char*)tou_03_str_0000028C)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -160, 150, 288, -160, 100, -8, 0, 11)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)str_00001384)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)tou_03_str_00001384)))
#endif
    CALL(evt_cam3d_evt_set, -200, 222, 682, -200, 100, -8, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(333)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00001394)), 0, STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001394)), 0, STRING(((char*)tou_03_str_0000028C)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -320, 95, 287, -320, 40, -8, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(333)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000013A4)), 0, STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000013A4)), 0, STRING(((char*)tou_03_str_0000028C)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -160, 150, 288, -160, 100, -8, 0, 11)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)str_000013B4)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)tou_03_str_000013B4)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -320, 95, 287, -320, 40, -8, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(333)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000013C4)), 0, STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000013C4)), 0, STRING(((char*)tou_03_str_0000028C)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -25, 197, 574, -25, 105, -8, 3000, 11)
#ifdef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)str_0000028C)), -280, 20, 0, FLOAT(60.0f), 1)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000028C)), -250, 20, 20, 500, 30)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000028C)), -215, 40, 20, 500, 30)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000028C)), -185, 60, 20, 500, 30)
    CALL(evt_npc_move_position, STRING(((char*)str_0000028C)), -135, 80, 0, FLOAT(60.0f), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000028C)), -280, 20, 0, FLOAT((60.0f)), 1)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000028C)), -250, 20, 20, 500, 30)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000028C)), -215, 40, 20, 500, 30)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000028C)), -185, 60, 20, 500, 30)
    CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000028C)), -135, 80, 0, FLOAT((60.0f)), 1)
#endif
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 90, 300, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 90, 300)
    END_INLINE_EVENT
#ifdef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)str_0000028C)), -50, 75, 0, FLOAT(60.0f), 1)
    CALL(evt_msg_print, 0, STRING(((char*)str_000013D4)), 0, STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000028C)), -50, 75, 0, FLOAT((60.0f)), 1)
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000013D4)), 0, STRING(((char*)tou_03_str_0000028C)))
#endif
    WAIT_MS(300)
    WAIT_MS(333)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000013E8)), 0, STRING(((char*)str_000001E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000013E8)), 0, STRING(((char*)tou_03_str_000001E0)))
#endif
    WAIT_MS(300)
    WAIT_MS(500)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000013FC)), 0, STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000013FC)), 0, STRING(((char*)tou_03_str_0000028C)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -160, 150, 288, -160, 100, -8, 0, 11)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)str_00001410)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)tou_03_str_00001410)))
#endif
    WAIT_MS(300)
    BEGIN_INLINE_EVENT_GET_ID(LW(10))
        CALL(eff_pos)
    END_INLINE_EVENT
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), 30)
    ADD(LW(1), 30)
#ifdef NONMATCHING
    CALL(evt_eff64, STRING(((char*)str_00001424)), STRING(((char*)str_00001428)), 1, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_eff64, STRING(((char*)tou_03_str_00001424)), STRING(((char*)tou_03_str_00001428)), 1, LW(0), LW(1), LW(2), FLOAT((1.0f)), 0, 0, 0, 0, 0, 0, 0)
#endif
    WAIT_MS(300)
    CALL(evt_eff_fukidashi, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1500)
#ifdef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)str_00001438)))
    CALL(evt_mapobj_get_position, STRING(((char*)str_00001138)), LW(0), LW(1), LW(2))
    ADD_FLOAT(LW(1), FLOAT(40.0f))
    CALL(evt_eff64, STRING(((char*)str_00001450)), STRING(((char*)str_00001458)), 11, LW(0), LW(1), LW(2), FLOAT(1.0f), 270, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)tou_03_str_00001438)))
    CALL(evt_mapobj_get_position, STRING(((char*)tou_03_str_00001138)), LW(0), LW(1), LW(2))
    ADD_FLOAT(LW(1), FLOAT((40.0f)))
    CALL(evt_eff64, STRING(((char*)tou_03_str_00001450)), STRING(((char*)tou_03_str_00001458)), 11, LW(0), LW(1), LW(2), FLOAT((1.0f)), 270, 0, 0, 0, 0, 0, 0)
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_0000146C)), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)tou_03_str_0000146C)), 0)
#endif
    CALL(evt_snd_sfx_vol, LW(15), 161)
    CALL(evt_cam3d_evt_set, 0, 400, 357, 0, 325, -8, 0, 11)
#ifdef NONMATCHING
    CALL(evt_eff_delete, STRING(((char*)str_00001424)))
#endif
#ifndef NONMATCHING
    CALL(evt_eff_delete, STRING(((char*)tou_03_str_00001424)))
#endif
    WAIT_FRAMES(1)
    SET_VALUE(GW(12), 650)
    WAIT_MS(600)
    SET_VALUE(GW(12), 400)
    WAIT_MS(350)
    SET_VALUE(GW(12), 250)
    WAIT_MS(250)
#ifdef NONMATCHING
    CALL(evt_mapobj_get_position, STRING(((char*)str_00001138)), LW(0), LW(1), LW(2))
    ADD_FLOAT(LW(1), FLOAT(40.0f))
    CALL(evt_eff64, STRING(((char*)str_00001488)), STRING(((char*)str_00001458)), 4, LW(0), LW(1), LW(2), FLOAT(1.0f), 180, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_get_position, STRING(((char*)tou_03_str_00001138)), LW(0), LW(1), LW(2))
    ADD_FLOAT(LW(1), FLOAT((40.0f)))
    CALL(evt_eff64, STRING(((char*)tou_03_str_00001488)), STRING(((char*)tou_03_str_00001458)), 4, LW(0), LW(1), LW(2), FLOAT((1.0f)), 180, 0, 0, 0, 0, 0, 0)
#endif
    WAIT_MS(2000)
#ifdef NONMATCHING
    CALL(evt_npc_set_scale, STRING(((char*)str_000002C0)), FLOAT(0.0f), FLOAT(0.0f), FLOAT(0.0f))
    CALL(evt_mapobj_get_position, STRING(((char*)str_00001138)), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING(((char*)str_000002C0)), LW(0), LW(1), LW(2))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_scale, STRING(((char*)tou_03_str_000002C0)), FLOAT((0.0f)), FLOAT((0.0f)), FLOAT((0.0f)))
    CALL(evt_mapobj_get_position, STRING(((char*)tou_03_str_00001138)), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000002C0)), LW(0), LW(1), LW(2))
#endif
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_000002C0)), 1024)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_flag_onoff, 0, STRING(((char*)tou_03_str_000002C0)), 1024)
#endif
        CALL(evt_sub_intpl_msec_init, 11, 0, 1800, 3000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
            CALL(evt_npc_set_rotate, STRING(((char*)str_000002C0)), FLOAT(0.0f), LW(0), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
            CALL(evt_npc_set_rotate, STRING(((char*)tou_03_str_000002C0)), FLOAT((0.0f)), LW(0), FLOAT((0.0f)))
#endif
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
#ifdef NONMATCHING
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000002C0)), 1024)
        CALL(evt_npc_set_rotate, STRING(((char*)str_000002C0)), FLOAT(0.0f), FLOAT(0.0f), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_000002C0)), 1024)
        CALL(evt_npc_set_rotate, STRING(((char*)tou_03_str_000002C0)), FLOAT((0.0f)), FLOAT((0.0f)), FLOAT((0.0f)))
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 100, 300)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            CALL(evt_npc_set_scale, STRING(((char*)str_000002C0)), LW(0), LW(0), LW(0))
#endif
#ifndef NONMATCHING
            DIVIDE_FLOAT(LW(0), FLOAT((100.0f)))
            CALL(evt_npc_set_scale, STRING(((char*)tou_03_str_000002C0)), LW(0), LW(0), LW(0))
#endif
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
#ifdef NONMATCHING
    CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000002C0)), 100, 60, 75, 800, 170)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_000002C0)), 100, 60, 75, 800, 170)
#endif
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
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00001490)), 0, STRING(((char*)str_000002C0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001490)), 0, STRING(((char*)tou_03_str_000002C0)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -75, 133, 339, -75, 85, -8, 0, 11)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000014A4)), 0, STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000014A4)), 0, STRING(((char*)tou_03_str_0000028C)))
#endif
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)str_0000028C)), 75, 75, 0, FLOAT(100.0f), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000028C)), 75, 75, 0, FLOAT((100.0f)), 1)
#endif
    END_INLINE_EVENT
    WAIT_MS(200)
    CALL(evt_cam3d_evt_set, 88, 133, 339, 88, 85, -8, 0, 11)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_000002C0)), STRING(((char*)str_0000028C)))
    CALL(evt_msg_print, 0, STRING(((char*)str_000014B8)), 0, STRING(((char*)str_000002C0)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_000002C0)), STRING(((char*)tou_03_str_0000028C)))
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000014B8)), 0, STRING(((char*)tou_03_str_000002C0)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000014CC)), 0, STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000014CC)), 0, STRING(((char*)tou_03_str_0000028C)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -160, 150, 288, -160, 100, -8, 0, 11)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)str_000014E0)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)tou_03_str_000014E0)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 356, 1016, 25, 180, 32, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
#ifdef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)str_0000028C)), 75, 75, 0, FLOAT(60.0f), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000028C)), 75, 75, 0, FLOAT((60.0f)), 1)
#endif
    WAIT_MS(333)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_0000028C)), STRING(((char*)str_0000078C)))
    CALL(evt_msg_print, 0, STRING(((char*)str_000014F4)), 0, STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_0000028C)), STRING(((char*)tou_03_str_0000078C)))
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000014F4)), 0, STRING(((char*)tou_03_str_0000028C)))
#endif
    WAIT_MS(300)
    CALL(evt_snd_sfxoff, LW(15))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_00001504)), 0)
    CALL(evt_npc_set_anim, STRING(((char*)str_0000028C)), STRING(((char*)str_000012D0)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)tou_03_str_00001504)), 0)
    CALL(evt_npc_set_anim, STRING(((char*)tou_03_str_0000028C)), STRING(((char*)tou_03_str_000012D0)))
#endif
    WAIT_MS(500)
#ifdef NONMATCHING
    CALL(evt_map_pauseanim, 0, STRING(((char*)str_000011DC)))
#endif
#ifndef NONMATCHING
    CALL(evt_map_pauseanim, 0, STRING(((char*)tou_03_str_000011DC)))
#endif
    CALL(evt_sub_intpl_msec_init, 0, 800, 0, 5000)
    LABEL(10)
    CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
    DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
    CALL(evt_map_set_playrate, STRING(((char*)str_000011B8)), LW(0))
    CALL(evt_map_set_playrate, STRING(((char*)str_000011CC)), LW(0))
    CALL(evt_map_set_playrate, STRING(((char*)str_000011C0)), LW(0))
#endif
#ifndef NONMATCHING
    DIVIDE_FLOAT(LW(0), FLOAT((100.0f)))
    CALL(evt_map_set_playrate, STRING(((char*)tou_03_str_000011B8)), LW(0))
    CALL(evt_map_set_playrate, STRING(((char*)tou_03_str_000011CC)), LW(0))
    CALL(evt_map_set_playrate, STRING(((char*)tou_03_str_000011C0)), LW(0))
#endif
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(10)
    END_IF
#ifdef NONMATCHING
    CALL(evt_map_pauseanim, 0, STRING(((char*)str_000011B8)))
    CALL(evt_map_pauseanim, 0, STRING(((char*)str_000011C0)))
    CALL(evt_map_pauseanim, 0, STRING(((char*)str_000011CC)))
#endif
#ifndef NONMATCHING
    CALL(evt_map_pauseanim, 0, STRING(((char*)tou_03_str_000011B8)))
    CALL(evt_map_pauseanim, 0, STRING(((char*)tou_03_str_000011C0)))
    CALL(evt_map_pauseanim, 0, STRING(((char*)tou_03_str_000011CC)))
#endif
    DELETE_EVENT(GW(11))
    DELETE_EVENT(GW(10))
#ifdef NONMATCHING
    CALL(evt_boss_stone_r, FLOAT(0.0f))
    CALL(item_jump, FLOAT(0.0f), FLOAT(200.0f), FLOAT(60.0f))
    CALL(item_jump, FLOAT(0.0f), FLOAT(60.0f), FLOAT(100.0f))
    CALL(item_jump, FLOAT(0.0f), FLOAT(60.0f), FLOAT(100.0f))
#endif
#ifndef NONMATCHING
    CALL(evt_boss_stone_r, FLOAT((0.0f)))
    CALL(item_jump, FLOAT((0.0f)), FLOAT(200.0f), FLOAT((60.0f)))
    CALL(item_jump, FLOAT((0.0f)), FLOAT((60.0f)), FLOAT((100.0f)))
    CALL(item_jump, FLOAT((0.0f)), FLOAT((60.0f)), FLOAT((100.0f)))
#endif
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, -160, 150, 288, -160, 100, -8, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
#ifdef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)str_00001520)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)tou_03_str_00001520)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 88, 133, 339, 88, 85, -8, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00001530)), 0, STRING(((char*)str_0000028C)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001530)), 0, STRING(((char*)tou_03_str_0000028C)))
#endif
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -160, 150, 288, -160, 100, -8, 0, 11)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)str_00001540)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print_party, STRING(((char*)tou_03_str_00001540)))
#endif
    WAIT_MS(300)
    CALL(evt_mario_set_dir, 270, 300, 0)
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001550)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_00001568)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00001550)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)tou_03_str_00001568)))
#endif
    WAIT_MS(500)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_party_run, 0)
    CALL(evt_cam3d_evt_set, 0, 200, 584, 0, 100, -8, 2000, 11)
#ifdef NONMATCHING
    CALL(evt_mario_mov_pos2, 0, 75, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_mov_pos2, 0, 75, FLOAT((60.0f)))
#endif
    SET_VALUE(GSW(0), 164)
    SET_VALUE(LW(0), 3)
#ifdef NONMATCHING
    SET_VALUE(LW(1), STRING(((char*)str_00001130)))
#endif
#ifndef NONMATCHING
    SET_VALUE(LW(1), STRING(((char*)tou_03_str_00001130)))
#endif
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_snd_bgmoff, 513)
    CALL_CHILD(PTR(evt_sub_starstone))
    RETURN
EVT_END()

EVT_BEGIN(evt_watch_match)
    IF_INT_LESS(GSW(0), 172)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_000001E0)), 0, 60, -130)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_000001E0)), 0, 60, -130)
#endif
        ELSE
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_0000028C)), 0, 60, -130)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)tou_03_str_0000028C)), 0, 60, -130)
#endif
    END_IF
#ifdef NONMATCHING
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00000434)), 32)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)tou_03_str_00000434)), 32)
#endif
    LOOP(0)
        CALL(evt_sub_random, 3, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(0)
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
            CALL(evt_npc_move_position, STRING(((char*)tou_03_str_00000434)), -30, 0, 0, FLOAT(200.0f), 0)
            CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_00000434)), 20, 60, 0, 500, 30)
            CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_00000434)), 80, 70, 0, 500, 60)
            CALL(evt_eff, 0, STRING(((char*)tou_03_str_000001CC)), 0, 80, 80, 0, FLOAT((1.0f)), 3, 0, 0, 0, 0, 0, 0)
            CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00001570)), 80, 80, 0, 0)
            CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_00000434)), 60, 60, 0, 500, 30)
            CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_00000434)), 30, 60, 0, 300, 20)
            CALL(evt_npc_move_position, STRING(((char*)tou_03_str_00000434)), -80, 0, 0, FLOAT(200.0f), 0)
            CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000043C)), 30, 0, 0, FLOAT(200.0f), 0)
            CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000043C)), -20, 60, 0, 500, 30)
            CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000043C)), -80, 70, 0, 500, 60)
            CALL(evt_eff, 0, STRING(((char*)tou_03_str_000001CC)), 0, -80, 80, 0, FLOAT((1.0f)), 3, 0, 0, 0, 0, 0, 0)
            CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00001570)), -80, 80, 0, 0)
            CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000043C)), -60, 60, 0, 500, 30)
            CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000043C)), -30, 60, 0, 300, 20)
            CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000043C)), 80, 0, 0, FLOAT(200.0f), 0)
#endif
            CASE_EQUAL(1)
            BEGIN_INLINE_EVENT_GET_ID(LW(12))
#ifdef NONMATCHING
                CALL(evt_npc_move_position, STRING(((char*)str_00000434)), -10, 0, 300, 0, 0)
#endif
#ifndef NONMATCHING
                CALL(evt_npc_move_position, STRING(((char*)tou_03_str_00000434)), -10, 0, 300, 0, 0)
#endif
            END_INLINE_EVENT
#ifdef NONMATCHING
            CALL(evt_npc_move_position, STRING(((char*)str_0000043C)), 10, 0, 300, 0, 0)
            CALL(evt_eff, 0, STRING(((char*)str_000001CC)), 1, 0, 80, 0, FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
            CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001570)), 0, 80, 0, 0)
#endif
#ifndef NONMATCHING
            CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000043C)), 10, 0, 300, 0, 0)
            CALL(evt_eff, 0, STRING(((char*)tou_03_str_000001CC)), 1, 0, 80, 0, FLOAT((1.0f)), 3, 0, 0, 0, 0, 0, 0)
            CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00001570)), 0, 80, 0, 0)
#endif
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
#ifdef NONMATCHING
                        CALL(evt_npc_move_position, STRING(((char*)str_00000434)), -140, 0, 800, 0, 0)
#endif
#ifndef NONMATCHING
                        CALL(evt_npc_move_position, STRING(((char*)tou_03_str_00000434)), -140, 0, 800, 0, 0)
#endif
                    END_INLINE_EVENT
#ifdef NONMATCHING
                    CALL(evt_npc_move_position, STRING(((char*)str_0000043C)), -120, 0, 800, 0, 0)
                    CALL(evt_eff, 0, STRING(((char*)str_000001CC)), 0, -130, 80, 0, FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
                    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001570)), -130, 80, 0, 0)
#endif
#ifndef NONMATCHING
                    CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000043C)), -120, 0, 800, 0, 0)
                    CALL(evt_eff, 0, STRING(((char*)tou_03_str_000001CC)), 0, -130, 80, 0, FLOAT((1.0f)), 3, 0, 0, 0, 0, 0, 0)
                    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00001570)), -130, 80, 0, 0)
#endif
                    ELSE
                    BEGIN_INLINE_EVENT_GET_ID(LW(12))
#ifdef NONMATCHING
                        CALL(evt_npc_move_position, STRING(((char*)str_00000434)), 120, 0, 800, 0, 0)
#endif
#ifndef NONMATCHING
                        CALL(evt_npc_move_position, STRING(((char*)tou_03_str_00000434)), 120, 0, 800, 0, 0)
#endif
                    END_INLINE_EVENT
#ifdef NONMATCHING
                    CALL(evt_npc_move_position, STRING(((char*)str_0000043C)), 140, 0, 800, 0, 0)
                    CALL(evt_eff, 0, STRING(((char*)str_000001CC)), 0, 130, 80, 0, FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
                    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001570)), 130, 80, 0, 0)
#endif
#ifndef NONMATCHING
                    CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000043C)), 140, 0, 800, 0, 0)
                    CALL(evt_eff, 0, STRING(((char*)tou_03_str_000001CC)), 0, 130, 80, 0, FLOAT((1.0f)), 3, 0, 0, 0, 0, 0, 0)
                    CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00001570)), 130, 80, 0, 0)
#endif
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
#ifdef NONMATCHING
                CALL(evt_npc_jump_position_nohit, STRING(((char*)str_00000434)), -80, 60, 0, 500, 30)
#endif
#ifndef NONMATCHING
                CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_00000434)), -80, 60, 0, 500, 30)
#endif
            END_INLINE_EVENT
#ifdef NONMATCHING
            CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000043C)), 80, 60, 0, 500, 30)
#endif
#ifndef NONMATCHING
            CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000043C)), 80, 60, 0, 500, 30)
#endif
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
#ifdef NONMATCHING
                CALL(evt_npc_move_position, STRING(((char*)str_00000434)), -40, 0, 500, 0, 0)
#endif
#ifndef NONMATCHING
                CALL(evt_npc_move_position, STRING(((char*)tou_03_str_00000434)), -40, 0, 500, 0, 0)
#endif
            END_INLINE_EVENT
#ifdef NONMATCHING
            CALL(evt_npc_move_position, STRING(((char*)str_0000043C)), 40, 0, 500, 0, 0)
#endif
#ifndef NONMATCHING
            CALL(evt_npc_move_position, STRING(((char*)tou_03_str_0000043C)), 40, 0, 500, 0, 0)
#endif
            WAIT_MS(100)
            LOOP(0)
                IS_EVENT_RUNNING(LW(12), LW(13))
                IF_INT_EQUAL(LW(13), 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            BEGIN_INLINE_EVENT_GET_ID(LW(12))
#ifdef NONMATCHING
                CALL(evt_npc_jump_position_nohit, STRING(((char*)str_00000434)), -10, 100, 0, 400, 30)
#endif
#ifndef NONMATCHING
                CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_00000434)), -10, 100, 0, 400, 30)
#endif
            END_INLINE_EVENT
#ifdef NONMATCHING
            CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000043C)), 10, 100, 0, 400, 30)
            CALL(evt_eff, 0, STRING(((char*)str_000001CC)), 2, 0, 120, 0, FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
            CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001570)), 0, 120, 0, 0)
#endif
#ifndef NONMATCHING
            CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000043C)), 10, 100, 0, 400, 30)
            CALL(evt_eff, 0, STRING(((char*)tou_03_str_000001CC)), 2, 0, 120, 0, FLOAT((1.0f)), 3, 0, 0, 0, 0, 0, 0)
            CALL(evt_snd_sfxon_3d, STRING(((char*)tou_03_str_00001570)), 0, 120, 0, 0)
#endif
            WAIT_MS(100)
            LOOP(0)
                IS_EVENT_RUNNING(LW(12), LW(13))
                IF_INT_EQUAL(LW(13), 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            BEGIN_INLINE_EVENT_GET_ID(LW(12))
#ifdef NONMATCHING
                CALL(evt_npc_jump_position_nohit, STRING(((char*)str_00000434)), -80, 60, 0, 500, 30)
#endif
#ifndef NONMATCHING
                CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_00000434)), -80, 60, 0, 500, 30)
#endif
            END_INLINE_EVENT
#ifdef NONMATCHING
            CALL(evt_npc_jump_position_nohit, STRING(((char*)str_0000043C)), 80, 60, 0, 500, 30)
#endif
#ifndef NONMATCHING
            CALL(evt_npc_jump_position_nohit, STRING(((char*)tou_03_str_0000043C)), 80, 60, 0, 500, 30)
#endif
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
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_00000054)), STRING(((char*)str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)str_00000054)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_00000054)), STRING(((char*)tou_03_str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)tou_03_str_00000054)))
#endif
    SWITCH(GSW(0))
        CASE_LESS(131)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00001584)), 0, STRING(((char*)str_00000054)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001584)), 0, STRING(((char*)tou_03_str_00000054)))
#endif
        CASE_DEFAULT
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        SWITCH(LW(10))
            CASE_GREATER(10)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_00001584)), 0, STRING(((char*)str_00000054)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001584)), 0, STRING(((char*)tou_03_str_00000054)))
#endif
            CASE_GREATER(0)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_00001594)), 0, STRING(((char*)str_00000054)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001594)), 0, STRING(((char*)tou_03_str_00000054)))
#endif
            CASE_DEFAULT
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_000015A4)), 0, STRING(((char*)str_00000054)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000015A4)), 0, STRING(((char*)tou_03_str_00000054)))
#endif
        END_SWITCH
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_kyaku_2)
    CALL(evt_mario_key_onoff, 0)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_0000005C)), STRING(((char*)str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)str_0000005C)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_0000005C)), STRING(((char*)tou_03_str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)tou_03_str_0000005C)))
#endif
    SWITCH(GSW(0))
        CASE_LESS(131)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000015B4)), 0, STRING(((char*)str_0000005C)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000015B4)), 0, STRING(((char*)tou_03_str_0000005C)))
#endif
        CASE_DEFAULT
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        SWITCH(LW(10))
            CASE_GREATER(10)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_000015B4)), 0, STRING(((char*)str_0000005C)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000015B4)), 0, STRING(((char*)tou_03_str_0000005C)))
#endif
            CASE_GREATER(0)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_000015C4)), 0, STRING(((char*)str_0000005C)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000015C4)), 0, STRING(((char*)tou_03_str_0000005C)))
#endif
            CASE_DEFAULT
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_000015D4)), 0, STRING(((char*)str_0000005C)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000015D4)), 0, STRING(((char*)tou_03_str_0000005C)))
#endif
        END_SWITCH
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_kyaku_3)
    CALL(evt_mario_key_onoff, 0)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_00000064)), STRING(((char*)str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)str_00000064)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_00000064)), STRING(((char*)tou_03_str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)tou_03_str_00000064)))
#endif
    SWITCH(GSW(0))
        CASE_LESS(131)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000015E4)), 0, STRING(((char*)str_00000064)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000015E4)), 0, STRING(((char*)tou_03_str_00000064)))
#endif
        CASE_DEFAULT
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        SWITCH(LW(10))
            CASE_GREATER(10)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_000015E4)), 0, STRING(((char*)str_00000064)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000015E4)), 0, STRING(((char*)tou_03_str_00000064)))
#endif
            CASE_GREATER(0)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_000015F4)), 0, STRING(((char*)str_00000064)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000015F4)), 0, STRING(((char*)tou_03_str_00000064)))
#endif
            CASE_DEFAULT
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_00001604)), 0, STRING(((char*)str_00000064)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001604)), 0, STRING(((char*)tou_03_str_00000064)))
#endif
        END_SWITCH
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_kyaku_4)
    CALL(evt_mario_key_onoff, 0)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_0000006C)), STRING(((char*)str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)str_0000006C)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_0000006C)), STRING(((char*)tou_03_str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)tou_03_str_0000006C)))
#endif
    SWITCH(GSW(0))
        CASE_LESS(131)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00001614)), 0, STRING(((char*)str_0000006C)))
        CALL(evt_msg_select, 0, STRING(((char*)str_00001624)))
        CALL(evt_msg_print_add, 0, STRING(((char*)str_00001634)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001614)), 0, STRING(((char*)tou_03_str_0000006C)))
        CALL(evt_msg_select, 0, STRING(((char*)tou_03_str_00001624)))
        CALL(evt_msg_print_add, 0, STRING(((char*)tou_03_str_00001634)))
#endif
        CASE_DEFAULT
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        SWITCH(LW(10))
            CASE_GREATER(10)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_00001614)), 0, STRING(((char*)str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)str_00001624)))
            CALL(evt_msg_print_add, 0, STRING(((char*)str_00001634)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001614)), 0, STRING(((char*)tou_03_str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)tou_03_str_00001624)))
            CALL(evt_msg_print_add, 0, STRING(((char*)tou_03_str_00001634)))
#endif
            CASE_GREATER(0)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_00001644)), 0, STRING(((char*)str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)str_00001654)))
            CALL(evt_msg_print_add, 0, STRING(((char*)str_00001664)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001644)), 0, STRING(((char*)tou_03_str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)tou_03_str_00001654)))
            CALL(evt_msg_print_add, 0, STRING(((char*)tou_03_str_00001664)))
#endif
            CASE_DEFAULT
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_00001674)), 0, STRING(((char*)str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)str_00001684)))
            CALL(evt_msg_print_add, 0, STRING(((char*)str_00001694)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001674)), 0, STRING(((char*)tou_03_str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)tou_03_str_00001684)))
            CALL(evt_msg_print_add, 0, STRING(((char*)tou_03_str_00001694)))
#endif
        END_SWITCH
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_kyaku_5)
    CALL(evt_mario_key_onoff, 0)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_00000054)), STRING(((char*)str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)str_00000054)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_00000054)), STRING(((char*)tou_03_str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)tou_03_str_00000054)))
#endif
    SWITCH(GSW(0))
        CASE_LESS(131)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000016A4)), 0, STRING(((char*)str_00000054)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000016A4)), 0, STRING(((char*)tou_03_str_00000054)))
#endif
        CASE_DEFAULT
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        SWITCH(LW(10))
            CASE_GREATER(10)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_000016A4)), 0, STRING(((char*)str_00000054)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000016A4)), 0, STRING(((char*)tou_03_str_00000054)))
#endif
            CASE_GREATER(0)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_000016B4)), 0, STRING(((char*)str_00000054)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000016B4)), 0, STRING(((char*)tou_03_str_00000054)))
#endif
            CASE_DEFAULT
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_000016C4)), 0, STRING(((char*)str_00000054)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000016C4)), 0, STRING(((char*)tou_03_str_00000054)))
#endif
        END_SWITCH
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_kyaku_6)
    CALL(evt_mario_key_onoff, 0)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_0000005C)), STRING(((char*)str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)str_0000005C)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_0000005C)), STRING(((char*)tou_03_str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)tou_03_str_0000005C)))
#endif
    SWITCH(GSW(0))
        CASE_LESS(131)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000016D4)), 0, STRING(((char*)str_0000005C)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000016D4)), 0, STRING(((char*)tou_03_str_0000005C)))
#endif
        CASE_DEFAULT
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        SWITCH(LW(10))
            CASE_GREATER(10)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_000016D4)), 0, STRING(((char*)str_0000005C)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000016D4)), 0, STRING(((char*)tou_03_str_0000005C)))
#endif
            CASE_GREATER(0)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_000016E4)), 0, STRING(((char*)str_0000005C)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000016E4)), 0, STRING(((char*)tou_03_str_0000005C)))
#endif
            CASE_DEFAULT
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_000016F4)), 0, STRING(((char*)str_0000005C)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_000016F4)), 0, STRING(((char*)tou_03_str_0000005C)))
#endif
        END_SWITCH
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_kyaku_7)
    CALL(evt_mario_key_onoff, 0)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_00000064)), STRING(((char*)str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)str_00000064)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_00000064)), STRING(((char*)tou_03_str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)tou_03_str_00000064)))
#endif
    SWITCH(GSW(0))
        CASE_LESS(131)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00001704)), 0, STRING(((char*)str_00000064)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001704)), 0, STRING(((char*)tou_03_str_00000064)))
#endif
        CASE_DEFAULT
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        SWITCH(LW(10))
            CASE_GREATER(10)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_00001704)), 0, STRING(((char*)str_00000064)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001704)), 0, STRING(((char*)tou_03_str_00000064)))
#endif
            CASE_GREATER(0)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_00001714)), 0, STRING(((char*)str_00000064)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001714)), 0, STRING(((char*)tou_03_str_00000064)))
#endif
            CASE_DEFAULT
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_00001724)), 0, STRING(((char*)str_00000064)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001724)), 0, STRING(((char*)tou_03_str_00000064)))
#endif
        END_SWITCH
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_kyaku_8)
    CALL(evt_mario_key_onoff, 0)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_0000006C)), STRING(((char*)str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)str_0000006C)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)tou_03_str_0000006C)), STRING(((char*)tou_03_str_0000078C)))
    CALL(evt_mario_set_dir_npc, STRING(((char*)tou_03_str_0000006C)))
#endif
    SWITCH(GSW(0))
        CASE_LESS(131)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00001734)), 0, STRING(((char*)str_0000006C)))
        CALL(evt_msg_select, 0, STRING(((char*)str_00001744)))
        CALL(evt_msg_print_add, 0, STRING(((char*)str_00001754)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001734)), 0, STRING(((char*)tou_03_str_0000006C)))
        CALL(evt_msg_select, 0, STRING(((char*)tou_03_str_00001744)))
        CALL(evt_msg_print_add, 0, STRING(((char*)tou_03_str_00001754)))
#endif
        CASE_DEFAULT
        CALL(evt_tou_get_ranking_28_text_4048, LW(10))
        SWITCH(LW(10))
            CASE_GREATER(10)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_00001734)), 0, STRING(((char*)str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)str_00001744)))
            CALL(evt_msg_print_add, 0, STRING(((char*)str_00001754)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001734)), 0, STRING(((char*)tou_03_str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)tou_03_str_00001744)))
            CALL(evt_msg_print_add, 0, STRING(((char*)tou_03_str_00001754)))
#endif
            CASE_GREATER(0)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_00001764)), 0, STRING(((char*)str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)str_00001774)))
            CALL(evt_msg_print_add, 0, STRING(((char*)str_00001784)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001764)), 0, STRING(((char*)tou_03_str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)tou_03_str_00001774)))
            CALL(evt_msg_print_add, 0, STRING(((char*)tou_03_str_00001784)))
#endif
            CASE_DEFAULT
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_00001794)), 0, STRING(((char*)str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)str_000017A4)))
            CALL(evt_msg_print_add, 0, STRING(((char*)str_000017B4)))
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)tou_03_str_00001794)), 0, STRING(((char*)tou_03_str_0000006C)))
            CALL(evt_msg_select, 0, STRING(((char*)tou_03_str_000017A4)))
            CALL(evt_msg_print_add, 0, STRING(((char*)tou_03_str_000017B4)))
#endif
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
#ifdef NONMATCHING
            CALL(evt_snd_envon, 272, STRING(((char*)str_000017C4)))
#endif
#ifndef NONMATCHING
            CALL(evt_snd_envon, 272, STRING(((char*)tou_03_str_000017C4)))
#endif
        END_INLINE_EVENT
    END_SWITCH
    CALL(evt_bero_get_entername, LW(0))
#ifdef NONMATCHING
    IF_STR_NOT_EQUAL(LW(0), STRING(((char*)str_000000A0)))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000017D4)), 1)
#endif
#ifndef NONMATCHING
    IF_STR_NOT_EQUAL(LW(0), STRING(((char*)tou_03_str_000000A0)))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_03_str_000017D4)), 1)
#endif
    END_IF
#ifdef NONMATCHING
    CALL(evt_map_playanim, STRING(((char*)str_000017D8)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_000017E8)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_000017F0)), 1, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_map_playanim, STRING(((char*)tou_03_str_000017D8)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)tou_03_str_000017E8)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)tou_03_str_000017F0)), 1, 0)
#endif
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
#ifdef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000017F8)), 16777216)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000017F8)), 256)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000011A8)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)str_00001234)), 1, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_03_str_000017F8)), 16777216)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)tou_03_str_000017F8)), 256)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_03_str_000011A8)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)tou_03_str_00001234)), 1, 0)
#endif
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
#ifdef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000ABC)))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_bgmon, 512, STRING(((char*)tou_03_str_00000ABC)))
#endif
        CALL(evt_snd_bgmon, 160, 0)
        SPAWN_EVENT(PTR(evt_tougi))
        CASE_EQUAL(163)
#ifdef NONMATCHING
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000000F8)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000104)), 1)
        SET_VALUE(LW(0), STRING(((char*)str_00000158)))
#endif
#ifndef NONMATCHING
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_03_str_000000F8)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_03_str_00000104)), 1)
        SET_VALUE(LW(0), STRING(((char*)tou_03_str_00000158)))
#endif
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
#ifdef NONMATCHING
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000000F8)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000104)), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_03_str_000000F8)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)tou_03_str_00000104)), 1)
#endif
        CALL(evt_tou_get_ranking_28_text_4048, LW(0))
        SET_VALUE(GSW(506), LW(0))
        SPAWN_EVENT(PTR(evt_match))
        ELSE
        SWITCH(GSW(0))
            CASE_BETWEEN(128, 162)
#ifdef NONMATCHING
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000ABC)))
#endif
#ifndef NONMATCHING
            CALL(evt_snd_bgmon, 512, STRING(((char*)tou_03_str_00000ABC)))
#endif
            CALL(evt_snd_bgmon, 160, 0)
            SPAWN_EVENT(PTR(evt_watch_match))
            CASE_LESS(164)
            CASE_DEFAULT
#ifdef NONMATCHING
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000ABC)))
#endif
#ifndef NONMATCHING
            CALL(evt_snd_bgmon, 512, STRING(((char*)tou_03_str_00000ABC)))
#endif
            CALL(evt_snd_bgmon, 160, 0)
            SPAWN_EVENT(PTR(evt_watch_match))
        END_SWITCH
    END_IF
    IF_INT_NOT_EQUAL(GSW(0), 163)
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
        CALL(evt_hitobj_onoff, STRING(((char*)tou_03_str_00001804)), 1, 1)
        CALL(evt_hitobj_onoff, STRING(((char*)tou_03_str_00001810)), 1, 1)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)tou_03_str_00000054)), 0, PTR(evt_kyaku_1), 0)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)tou_03_str_0000005C)), 0, PTR(evt_kyaku_2), 0)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)tou_03_str_00000064)), 0, PTR(evt_kyaku_3), 0)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)tou_03_str_0000006C)), 0, PTR(evt_kyaku_4), 0)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)tou_03_str_0000181C)), 0, PTR(evt_kyaku_5), 0)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)tou_03_str_00001824)), 0, PTR(evt_kyaku_6), 0)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)tou_03_str_0000182C)), 0, PTR(evt_kyaku_7), 0)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)tou_03_str_00001834)), 0, PTR(evt_kyaku_8), 0)
#endif
        ELSE
#ifdef NONMATCHING
        CALL(evt_hitobj_onoff, STRING(((char*)str_00001804)), 1, 0)
        CALL(evt_hitobj_onoff, STRING(((char*)str_00001810)), 1, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_hitobj_onoff, STRING(((char*)tou_03_str_00001804)), 1, 0)
        CALL(evt_hitobj_onoff, STRING(((char*)tou_03_str_00001810)), 1, 0)
#endif
    END_IF
    RETURN
EVT_END()


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
#pragma force_active reset

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const char tou_03_str_00000000[12] = "c_kinopio\0\0";
__declspec(section ".rodata") const char tou_03_str_0000000C[8] = "KNP_S_1";
__declspec(section ".rodata") const char tou_03_str_00000014[12] = "c_kinopiko\0";
__declspec(section ".rodata") const char tou_03_str_00000020[8] = "KNF_S_1";
__declspec(section ".rodata") const char tou_03_str_00000028[8] = "c_roten";
__declspec(section ".rodata") const char tou_03_str_00000030[4] = "S_1";
__declspec(section ".rodata") const char tou_03_str_00000034[12] = "c_jugemu\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000040[8] = "JGM_S_1";
__declspec(section ".rodata") const f32 vec3_tou2_00009638[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const char tou_03_str_00000054[8] = "kyaku1\0";
__declspec(section ".rodata") const char tou_03_str_0000005C[8] = "kyaku2\0";
__declspec(section ".rodata") const char tou_03_str_00000064[8] = "kyaku3\0";
__declspec(section ".rodata") const char tou_03_str_0000006C[8] = "kyaku4\0";
__declspec(section ".rodata") const char tou_03_str_00000074[12] = "\x83L\x83m\x83s\x83I\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000080[12] = "\x83L\x83m\x83s\x83I\x8f\x97\0";
__declspec(section ".rodata") const char tou_03_str_0000008C[8] = "\x83\x8d\x83" "e\x83\x93\0";
__declspec(section ".rodata") const char tou_03_str_00000094[12] = "\x83W\x83\x85\x83Q\x83\x80\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000000A0[12] = "s_bero_2\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000000AC[12] = "group246\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000000B8[16] = "SFX_DOOR_FALL1\0";
__declspec(section ".rodata") const char tou_03_str_000000C8[12] = "aka_door_a\0";
__declspec(section ".rodata") const char tou_03_str_000000D4[12] = "aka_door_b\0";
__declspec(section ".rodata") const char tou_03_str_000000E0[12] = "ao_door_a\0\0";
__declspec(section ".rodata") const char tou_03_str_000000EC[12] = "ao_ddor_b\0\0";
__declspec(section ".rodata") const char tou_03_str_000000F8[12] = "door_2_a\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000104[12] = "door_2_b\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000110[12] = "door_3_a\0\0\0";
__declspec(section ".rodata") const char tou_03_str_0000011C[12] = "door_3_b\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000128[8] = "w_bero\0";
__declspec(section ".rodata") const char tou_03_str_00000130[8] = "tou_04\0";
__declspec(section ".rodata") const char tou_03_str_00000138[12] = "n_bero_2\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000144[8] = "e_bero\0";
__declspec(section ".rodata") const char tou_03_str_0000014C[12] = "n_bero_1\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000158[12] = "s_bero_1\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000164[8] = "tou_02\0";
__declspec(section ".rodata") const char tou_03_str_0000016C[16] = "\x83`\x83\x83\x83\x93\x83s\x83\x87\x83\x93\0\0\0";
__declspec(section ".rodata") const char tou_03_str_0000017C[8] = "\x91\x8a\x8e\xe8\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000184[24] = "SFX_STG3_TOGENOKO_DOWN1";
__declspec(section ".rodata") const char tou_03_str_0000019C[12] = "stg3_tou_25";
__declspec(section ".rodata") const char tou_03_str_000001A8[12] = "stg3_tou_26";
__declspec(section ".rodata") const char tou_03_str_000001B4[24] = "SFX_STG3_BLED_ATTACK1\0\0";
__declspec(section ".rodata") const char tou_03_str_000001CC[4] = "hit";
__declspec(section ".rodata") const char tou_03_str_000001D0[4] = "K_2";
__declspec(section ".rodata") const char tou_03_str_000001D4[12] = "stg3_tou_27";
__declspec(section ".rodata") const char tou_03_str_000001E0[8] = "\x83K\x83\x93\x83X\0";
__declspec(section ".rodata") const char tou_03_str_000001E8[4] = "S_4";
__declspec(section ".rodata") const char tou_03_str_000001EC[4] = "T_4";
__declspec(section ".rodata") const char tou_03_str_000001F0[12] = "stg3_tou_28";
__declspec(section ".rodata") const char tou_03_str_000001FC[12] = "stg3_tou_29";
__declspec(section ".rodata") const char tou_03_str_00000208[4] = "M_5";
__declspec(section ".rodata") const char tou_03_str_0000020C[4] = "M_6";
__declspec(section ".rodata") const char tou_03_str_00000210[12] = "stg3_tou_30";
__declspec(section ".rodata") const char tou_03_str_0000021C[4] = "M_7";
__declspec(section ".rodata") const char tou_03_str_00000220[4] = "S_2";
__declspec(section ".rodata") const char tou_03_str_00000224[4] = "H_1";
__declspec(section ".rodata") const char tou_03_str_00000228[4] = "T_2";
__declspec(section ".rodata") const char tou_03_str_0000022C[4] = "H_2";
__declspec(section ".rodata") const char tou_03_str_00000230[4] = "S_3";
__declspec(section ".rodata") const char tou_03_str_00000234[8] = "\x83x\x83\x8b\x83g\0";
__declspec(section ".rodata") const char tou_03_str_0000023C[12] = "c_bred_h\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000248[4] = "C_1";
__declspec(section ".rodata") const char tou_03_str_0000024C[12] = "starstone\0\0";
__declspec(section ".rodata") const char tou_03_str_00000258[24] = "SFX_STG3_WIN_AUDIENCE2\0";
__declspec(section ".rodata") const char tou_03_str_00000270[4] = "eff";
__declspec(section ".rodata") const char tou_03_str_00000274[12] = "stg3_tou_31";
__declspec(section ".rodata") const char tou_03_str_00000280[12] = "stg3_tou_32";
__declspec(section ".rodata") const char tou_03_str_0000028C[12] = "\x83L\x83m\x83V\x83R\x83\x8f\0";
__declspec(section ".rodata") const char tou_03_str_00000298[24] = "\x83L\x83m\x83V\x83R\x83\x8f\x81i\x83}\x83" "C\x83N\x81j\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000002B0[16] = "\x83}\x83" "b\x83`\x83\x87\x83K\x83\x93\x83X\0";
__declspec(section ".rodata") const char tou_03_str_000002C0[16] = "\x83L\x83m\x83V\x83`\x83\x87\x83t\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000002D0[8] = "M_D_2\0\0";
__declspec(section ".rodata") const char tou_03_str_000002D8[8] = "PKR_D_3";
__declspec(section ".rodata") const char tou_03_str_000002E0[8] = "PNK_D_3";
__declspec(section ".rodata") const char tou_03_str_000002E8[4] = "D_3";
__declspec(section ".rodata") const char tou_03_str_000002EC[8] = "PYS_D_3";
__declspec(section ".rodata") const char tou_03_str_000002F4[8] = "PWD_D_3";
__declspec(section ".rodata") const char tou_03_str_000002FC[8] = "PTR_D_3";
__declspec(section ".rodata") const char tou_03_str_00000304[8] = "PCH_D_3";
__declspec(section ".rodata") const char tou_03_str_0000030C[8] = "PKR_Y_1";
__declspec(section ".rodata") const char tou_03_str_00000314[8] = "PNK_Y_1";
__declspec(section ".rodata") const char tou_03_str_0000031C[4] = "Y_1";
__declspec(section ".rodata") const char tou_03_str_00000320[8] = "PYS_Y_1";
__declspec(section ".rodata") const char tou_03_str_00000328[8] = "PWD_Y_1";
__declspec(section ".rodata") const char tou_03_str_00000330[8] = "PTR_Y_1";
__declspec(section ".rodata") const char tou_03_str_00000338[8] = "PCH_Y_1";
__declspec(section ".rodata") const char tou_03_str_00000340[16] = "c_togenoko_b\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000350[16] = "\x83u\x83\x8c\x83" "b\x83h\x83n\x81[\x83g\0";
__declspec(section ".rodata") const char tou_03_str_00000360[16] = "\x83g\x83Q\x83m\x83R\x83G\x81[\x83X\0";
__declspec(section ".rodata") const char tou_03_str_00000370[12] = "c_bomhey\0\0\0";
__declspec(section ".rodata") const char tou_03_str_0000037C[8] = "\x83{\x83\x80\x95\xba\0";
__declspec(section ".rodata") const char tou_03_str_00000384[12] = "c_kuribo\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000390[12] = "\x83N\x83\x8a\x83{\x81[\0\0\0";
__declspec(section ".rodata") const char tou_03_str_0000039C[12] = "c_kmoon_wb\0";
__declspec(section ".rodata") const char tou_03_str_000003A8[24] = "\x83\x82\x83m\x83N\x83\x8d\x83N\x83\x8d\x83N\x83\x82\x81[\x83\x93\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000003C0[12] = "c_chorobon\0";
__declspec(section ".rodata") const char tou_03_str_000003CC[12] = "\x83`\x83\x87\x83\x8d\x83{\x83\x93\0";
__declspec(section ".rodata") const char tou_03_str_000003D8[12] = "c_monban_t\0";
__declspec(section ".rodata") const char tou_03_str_000003E4[16] = "\x83_\x81[\x83N\x83L\x81[\x83p\x81[\0";
__declspec(section ".rodata") const char tou_03_str_000003F4[16] = "c_togedaruma\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000404[16] = "\x83g\x83Q\x83_\x83\x8b\x83}\x81[\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000414[12] = "c_wanwan_a\0";
__declspec(section ".rodata") const char tou_03_str_00000420[20] = "\x83o\x81[\x83X\x83g\x83\x8f\x83\x93\x83\x8f\x83\x93\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000434[8] = "\x91I\x8e\xe8" "1\0\0";
__declspec(section ".rodata") const char tou_03_str_0000043C[8] = "\x91I\x8e\xe8" "2\0\0";
__declspec(section ".rodata") const char tou_03_str_00000444[8] = "WAN_A_1";
__declspec(section ".rodata") const char tou_03_str_0000044C[8] = "\x93G\x82R\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000454[8] = "\x93G\x82S\0\0\0";
__declspec(section ".rodata") const char tou_03_str_0000045C[8] = "\x93G\x82P\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000464[8] = "\x93G\x82Q\0\0\0";
__declspec(section ".rodata") const char tou_03_str_0000046C[8] = "\x93G\x82T\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000474[12] = "\x82\xa8\x82\xa9\x82\xb5\x82\xa2\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000480[24] = "SFX_STG3_ISIN_MOVE1L\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000498[24] = "SFX_STG3_ISIN_MOVE1R\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000004B0[4] = "\x97\x90\0";
__declspec(section ".rodata") const char tou_03_str_000004B4[8] = "c_koopa";
__declspec(section ".rodata") const char tou_03_str_000004BC[8] = "\x83N\x83" "b\x83p\0";
__declspec(section ".rodata") const char tou_03_str_000004C4[24] = "SFX_STG3_KOOPA_MOVE1L\0\0";
__declspec(section ".rodata") const char tou_03_str_000004DC[24] = "SFX_STG3_KOOPA_MOVE1R\0\0";
__declspec(section ".rodata") const char tou_03_str_000004F4[24] = "SFX_STG3_KOOPA_JUMP1\0\0\0";
__declspec(section ".rodata") const char tou_03_str_0000050C[12] = "c_sinemon_a";
__declspec(section ".rodata") const char tou_03_str_00000518[20] = "\x83" "A\x83" "C\x83" "A\x83\x93\x83V\x83\x93\x83G\x83\x82\x83\x93\0";
__declspec(section ".rodata") const char tou_03_str_0000052C[8] = "\x97\x90\x82Q\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000534[12] = "c_sinemon_m";
__declspec(section ".rodata") const char tou_03_str_00000540[20] = "\x83" "A\x83" "C\x83" "A\x83\x93\x83V\x83\x93\x83G\x83\x82\x83\x93" "2";
__declspec(section ".rodata") const char tou_03_str_00000554[24] = "SFX_VOICE_MARIO_FIND1_3";
__declspec(section ".rodata") const char tou_03_str_0000056C[4] = "m\0\0";
__declspec(section ".rodata") const char tou_03_str_00000570[16] = "stg3_tou_403\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000580[8] = "M_I_Y\0\0";
__declspec(section ".rodata") const char tou_03_str_00000588[16] = "stg3_tou_403_01";
__declspec(section ".rodata") const char tou_03_str_00000598[16] = "stg3_tou_404\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000005A8[16] = "SFX_STG3_GONG1\0";
__declspec(section ".rodata") const char tou_03_str_000005B8[8] = "M_S_1\0\0";
__declspec(section ".rodata") const char tou_03_str_000005C0[8] = "SIN_K_1";
__declspec(section ".rodata") const char tou_03_str_000005C8[16] = "stg3_tou_406\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000005D8[16] = "stg3_tou_403_02";
__declspec(section ".rodata") const char tou_03_str_000005E8[16] = "stg3_tou_405\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000005F8[16] = "stg3_tou_406_01";
__declspec(section ".rodata") const char tou_03_str_00000608[16] = "stg3_tou_403_04";
__declspec(section ".rodata") const char tou_03_str_00000618[16] = "BGM_EVT_KUPPA2\0";
__declspec(section ".rodata") const char tou_03_str_00000628[16] = "stg3_tou_403_05";
__declspec(section ".rodata") const char tou_03_str_00000638[16] = "stg3_tou_403_06";
__declspec(section ".rodata") const char tou_03_str_00000648[8] = "KPA_Z_3";
__declspec(section ".rodata") const char tou_03_str_00000650[8] = "KPA_T_8";
__declspec(section ".rodata") const char tou_03_str_00000658[16] = "stg3_tou_403_08";
__declspec(section ".rodata") const char tou_03_str_00000668[16] = "stg3_tou_403_10";
__declspec(section ".rodata") const char tou_03_str_00000678[16] = "stg3_tou_403_07";
__declspec(section ".rodata") const char tou_03_str_00000688[16] = "stg3_tou_403_09";
__declspec(section ".rodata") const char tou_03_str_00000698[16] = "\x83J\x83\x81\x83" "b\x83N\x97\xce\x8b\xf3\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000006A8[8] = "\x8d\xbd" "0_0\0\0";
__declspec(section ".rodata") const char tou_03_str_000006B0[8] = "\x8d\xbd" "0_1\0\0";
__declspec(section ".rodata") const char tou_03_str_000006B8[8] = "\x8d\xbd" "0_2\0\0";
__declspec(section ".rodata") const char tou_03_str_000006C0[8] = "\x8d\xbd" "0_3\0\0";
__declspec(section ".rodata") const char tou_03_str_000006C8[8] = "\x8d\xbd" "0_4\0\0";
__declspec(section ".rodata") const char tou_03_str_000006D0[12] = "WAN_S_1B\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000006DC[8] = "\x8d\xbd" "1_0\0\0";
__declspec(section ".rodata") const char tou_03_str_000006E4[8] = "\x8d\xbd" "1_1\0\0";
__declspec(section ".rodata") const char tou_03_str_000006EC[8] = "\x8d\xbd" "1_2\0\0";
__declspec(section ".rodata") const char tou_03_str_000006F4[8] = "\x8d\xbd" "1_3\0\0";
__declspec(section ".rodata") const char tou_03_str_000006FC[8] = "\x8d\xbd" "1_4\0\0";
__declspec(section ".rodata") const char tou_03_str_00000704[28] = "SFX_FLD_ENM_WAN_LANDING1\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000720[16] = "BGM_FF_ENV_TOU2";
__declspec(section ".rodata") const char tou_03_str_00000730[16] = "BGM_FF_ENV_TOU3";
__declspec(section ".rodata") const char tou_03_str_00000740[8] = "tou_07\0";
__declspec(section ".rodata") const char tou_03_str_00000748[8] = "tou_08\0";
__declspec(section ".rodata") const char tou_03_str_00000750[8] = "tou_10\0";
__declspec(section ".rodata") const char tou_03_str_00000758[16] = "BGM_FF_ENV_TOU1";
__declspec(section ".rodata") const char tou_03_str_00000768[12] = "stg3_tou_77";
__declspec(section ".rodata") const char tou_03_str_00000774[12] = "stg3_tou_78";
__declspec(section ".rodata") const char tou_03_str_00000780[12] = "stg3_tou_79";
__declspec(section ".rodata") const char tou_03_str_0000078C[8] = "mario\0\0";
__declspec(section ".rodata") const char tou_03_str_00000794[20] = "SFX_DOOR_SHUT_IRON2";
__declspec(section ".rodata") const char tou_03_str_000007A8[12] = "stg3_tou_80";
__declspec(section ".rodata") const char tou_03_str_000007B4[28] = "SFX_VOICE_MARIO_FLD_JUMP3\0\0";
__declspec(section ".rodata") const char tou_03_str_000007D0[28] = "SFX_VOICE_MARIO_FLD_JUMP1\0\0";
__declspec(section ".rodata") const char tou_03_str_000007EC[28] = "SFX_VOICE_MARIO_FLD_JUMP5\0\0";
__declspec(section ".rodata") const char tou_03_str_00000808[12] = "stg3_tou_81";
__declspec(section ".rodata") const char tou_03_str_00000814[12] = "stg3_tou_82";
__declspec(section ".rodata") const char tou_03_str_00000820[28] = "SFX_VOICE_MARIO_SURPRISED1\0";
__declspec(section ".rodata") const char tou_03_str_0000083C[8] = "M_N_7\0\0";
__declspec(section ".rodata") const char tou_03_str_00000844[24] = "SFX_STG3_KURI_ATTACK1\0\0";
__declspec(section ".rodata") const char tou_03_str_0000085C[8] = "KUR_K_1";
__declspec(section ".rodata") const char tou_03_str_00000864[8] = "KUR_D_1";
__declspec(section ".rodata") const char tou_03_str_0000086C[24] = "SFX_STG3_KURI_FURAFURA1";
__declspec(section ".rodata") const char tou_03_str_00000884[12] = "stg3_tou_86";
__declspec(section ".rodata") const char tou_03_str_00000890[12] = "stg3_tou_87";
__declspec(section ".rodata") const char tou_03_str_0000089C[16] = "stg3_tou_87_yn\0";
__declspec(section ".rodata") const char tou_03_str_000008AC[12] = "stg3_tou_88";
__declspec(section ".rodata") const u32 zero_tou2_00009ea8[1] = {0x00000000};
__declspec(section ".rodata") const char tou_03_str_000008BC[12] = "confetti\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000008C8[24] = "SFX_STG3_WIN_AUDIENCE1\0";
__declspec(section ".rodata") const char tou_03_str_000008E0[16] = "stg3_tou_118_61";
__declspec(section ".rodata") const char tou_03_str_000008F0[12] = "stg3_tou_85";
__declspec(section ".rodata") const char tou_03_str_000008FC[16] = "stg3_tou_257\0\0\0";
__declspec(section ".rodata") const char tou_03_str_0000090C[16] = "stg3_tou_258_00";
__declspec(section ".rodata") const char tou_03_str_0000091C[28] = "SFX_VOICE_MARIO_FLD_JUMP2\0\0";
__declspec(section ".rodata") const char tou_03_str_00000938[16] = "stg3_tou_258_01";
__declspec(section ".rodata") const char tou_03_str_00000948[16] = "stg3_tou_258_02";
__declspec(section ".rodata") const char tou_03_str_00000958[16] = "stg3_tou_258_03";
__declspec(section ".rodata") const char tou_03_str_00000968[16] = "stg3_tou_258_04";
__declspec(section ".rodata") const char tou_03_str_00000978[16] = "stg3_tou_259\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000988[16] = "stg3_tou_259_yn";
__declspec(section ".rodata") const char tou_03_str_00000998[16] = "stg3_tou_260\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000009A8[4] = "e\0\0";
__declspec(section ".rodata") const char tou_03_str_000009AC[16] = "stg3_tou_261_01";
__declspec(section ".rodata") const char tou_03_str_000009BC[16] = "stg3_tou_261_02";
__declspec(section ".rodata") const char tou_03_str_000009CC[16] = "stg3_tou_261_03";
__declspec(section ".rodata") const char tou_03_str_000009DC[16] = "stg3_tou_262\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000009EC[16] = "stg3_tou_263\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000009FC[16] = "stg3_tou_264\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000A0C[4] = "M_1";
__declspec(section ".rodata") const char tou_03_str_00000A10[4] = "M_2";
__declspec(section ".rodata") const char tou_03_str_00000A14[4] = "M_3";
__declspec(section ".rodata") const char tou_03_str_00000A18[20] = "stg3_tou_116_20_01\0";
__declspec(section ".rodata") const char tou_03_str_00000A2C[16] = "stg3_tou_275\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000A3C[16] = "stg3_tou_276\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000A4C[16] = "stg3_tou_277\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000A5C[8] = "M_I_U\0\0";
__declspec(section ".rodata") const char tou_03_str_00000A64[24] = "SFX_VOICE_MARIO_PAUSE2\0";
__declspec(section ".rodata") const char tou_03_str_00000A7C[8] = "M_V_2\0\0";
__declspec(section ".rodata") const char tou_03_str_00000A84[16] = "stg3_tou_274\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000A94[16] = "stg3_tou_274_01";
__declspec(section ".rodata") const char tou_03_str_00000AA4[24] = "\x83u\x83\x8c\x83" "b\x83h\x83n\x81[\x83g\x83x\x83\x8b\x83g\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000ABC[16] = "BGM_STG3_TOU2\0\0";
__declspec(section ".rodata") const char tou_03_str_00000ACC[4] = "a\0\0";
__declspec(section ".rodata") const char tou_03_str_00000AD0[16] = "stg3_tou_424\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000AE0[16] = "stg3_tou_425\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000AF0[16] = "stg3_tou_426\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000B00[16] = "stg3_tou_427\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000B10[16] = "stg3_tou_428\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000B20[16] = "stg3_tou_429\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000B30[16] = "stg3_tou_430\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000B40[28] = "SFX_VOICE_MARIO_FLD_JUMP4\0\0";
__declspec(section ".rodata") const char tou_03_str_00000B5C[16] = "stg3_tou_430_01";
__declspec(section ".rodata") const char tou_03_str_00000B6C[16] = "stg3_tou_430_02";
__declspec(section ".rodata") const char tou_03_str_00000B7C[16] = "stg3_tou_430_03";
__declspec(section ".rodata") const char tou_03_str_00000B8C[16] = "stg3_tou_430_04";
__declspec(section ".rodata") const char tou_03_str_00000B9C[16] = "stg3_tou_431\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000BAC[16] = "stg3_tou_re_086";
__declspec(section ".rodata") const char tou_03_str_00000BBC[16] = "stg3_tou_re_087";
__declspec(section ".rodata") const char tou_03_str_00000BCC[16] = "stg3_tou_re_089";
__declspec(section ".rodata") const char tou_03_str_00000BDC[16] = "stg3_tou_re_090";
__declspec(section ".rodata") const char tou_03_str_00000BEC[16] = "stg3_tou_re_091";
__declspec(section ".rodata") const char tou_03_str_00000BFC[16] = "stg3_tou_re_092";
__declspec(section ".rodata") const char tou_03_str_00000C0C[16] = "stg3_tou_re_093";
__declspec(section ".rodata") const char tou_03_str_00000C1C[16] = "stg3_tou_re_094";
__declspec(section ".rodata") const char tou_03_str_00000C2C[16] = "stg3_tou_re_095";
__declspec(section ".rodata") const char tou_03_str_00000C3C[16] = "stg3_tou_re_096";
__declspec(section ".rodata") const char tou_03_str_00000C4C[16] = "stg3_tou_re_097";
__declspec(section ".rodata") const char tou_03_str_00000C5C[16] = "stg3_tou_re_098";
__declspec(section ".rodata") const char tou_03_str_00000C6C[16] = "stg3_tou_re_099";
__declspec(section ".rodata") const char tou_03_str_00000C7C[16] = "stg3_tou_re_100";
__declspec(section ".rodata") const char tou_03_str_00000C8C[16] = "stg3_tou_re_101";
__declspec(section ".rodata") const char tou_03_str_00000C9C[16] = "stg3_tou_re_102";
__declspec(section ".rodata") const char tou_03_str_00000CAC[16] = "stg3_tou_re_103";
__declspec(section ".rodata") const char tou_03_str_00000CBC[16] = "stg3_tou_re_110";
__declspec(section ".rodata") const char tou_03_str_00000CCC[16] = "stg3_tou_re_111";
__declspec(section ".rodata") const char tou_03_str_00000CDC[16] = "stg3_tou_re_112";
__declspec(section ".rodata") const char tou_03_str_00000CEC[16] = "stg3_tou_re_113";
__declspec(section ".rodata") const char tou_03_str_00000CFC[16] = "stg3_tou_re_114";
__declspec(section ".rodata") const char tou_03_str_00000D0C[4] = "A_2";
__declspec(section ".rodata") const char tou_03_str_00000D10[4] = "T_3";
__declspec(section ".rodata") const char tou_03_str_00000D14[16] = "stg3_tou_re_115";
__declspec(section ".rodata") const char tou_03_str_00000D24[16] = "stg3_tou_438\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000D34[16] = "stg3_tou_439\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000D44[16] = "stg3_tou_re_133";
__declspec(section ".rodata") const char tou_03_str_00000D54[16] = "stg3_tou_re_134";
__declspec(section ".rodata") const char tou_03_str_00000D64[20] = "SFX_STG3_BLED_DIE1\0";
__declspec(section ".rodata") const char tou_03_str_00000D78[8] = "S_10\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000D80[8] = "T_10\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000D88[16] = "stg3_tou_440\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000D98[16] = "stg3_tou_441\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000DA8[16] = "stg3_tou_442\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000DB8[16] = "stg3_tou_443\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000DC8[16] = "stg3_tou_444\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000DD8[16] = "stg3_tou_re_135";
__declspec(section ".rodata") const char tou_03_str_00000DE8[16] = "stg3_tou_re_136";
__declspec(section ".rodata") const char tou_03_str_00000DF8[16] = "stg3_tou_re_137";
__declspec(section ".rodata") const char tou_03_str_00000E08[16] = "stg3_tou_re_138";
__declspec(section ".rodata") const char tou_03_str_00000E18[16] = "stg3_tou_re_139";
__declspec(section ".rodata") const char tou_03_str_00000E28[16] = "stg3_tou_437\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000E38[16] = "stg3_tou_400_03";
__declspec(section ".rodata") const char tou_03_str_00000E48[16] = "stg3_tou_400_01";
__declspec(section ".rodata") const char tou_03_str_00000E58[16] = "stg3_tou_re_132";
__declspec(section ".rodata") const char tou_03_str_00000E68[16] = "stg3_tou_re_290";
__declspec(section ".rodata") const char tou_03_str_00000E78[16] = "stg3_tou_re_288";
__declspec(section ".rodata") const char tou_03_str_00000E88[16] = "stg3_tou_378\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000E98[16] = "stg3_tou_re_266";
__declspec(section ".rodata") const char tou_03_str_00000EA8[16] = "stg3_tou_377\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000EB8[16] = "stg3_tou_re_265";
__declspec(section ".rodata") const char tou_03_str_00000EC8[16] = "stg3_tou_115\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000ED8[16] = "stg3_tou_116_20";
__declspec(section ".rodata") const char tou_03_str_00000EE8[16] = "stg3_tou_re_147";
__declspec(section ".rodata") const char tou_03_str_00000EF8[16] = "stg3_tou_re_149";
__declspec(section ".rodata") const char tou_03_str_00000F08[16] = "stg3_tou_117_00";
__declspec(section ".rodata") const char tou_03_str_00000F18[16] = "stg3_tou_117_01";
__declspec(section ".rodata") const char tou_03_str_00000F28[16] = "stg3_tou_305\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000F38[16] = "stg3_tou_re_151";
__declspec(section ".rodata") const char tou_03_str_00000F48[16] = "stg3_tou_118_37";
__declspec(section ".rodata") const char tou_03_str_00000F58[16] = "stg3_tou_400_00";
__declspec(section ".rodata") const char tou_03_str_00000F68[16] = "stg3_tou_re_287";
__declspec(section ".rodata") const char tou_03_str_00000F78[16] = "stg3_tou_re_150";
__declspec(section ".rodata") const char tou_03_str_00000F88[16] = "stg3_tou_118_39";
__declspec(section ".rodata") const char tou_03_str_00000F98[16] = "stg3_tou_117_02";
__declspec(section ".rodata") const char tou_03_str_00000FA8[16] = "stg3_tou_117_03";
__declspec(section ".rodata") const char tou_03_str_00000FB8[16] = "stg3_tou_re_153";
__declspec(section ".rodata") const char tou_03_str_00000FC8[16] = "stg3_tou_118_38";
__declspec(section ".rodata") const char tou_03_str_00000FD8[16] = "stg3_tou_411\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000FE8[16] = "stg3_tou_412\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00000FF8[16] = "stg3_tou_413_01";
__declspec(section ".rodata") const char tou_03_str_00001008[16] = "stg3_tou_413_02";
__declspec(section ".rodata") const char tou_03_str_00001018[16] = "stg3_tou_413_03";
__declspec(section ".rodata") const char tou_03_str_00001028[16] = "stg3_tou_413_04";
__declspec(section ".rodata") const char tou_03_str_00001038[16] = "stg3_tou_414\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001048[16] = "stg3_tou_415\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001058[16] = "stg3_tou_416\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001068[16] = "stg3_tou_417\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001078[8] = "tou_11\0";
__declspec(section ".rodata") const char tou_03_str_00001080[8] = "nidome\0";
__declspec(section ".rodata") const char tou_03_str_00001088[16] = "stg3_tou_418\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001098[16] = "stg3_tou_419\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000010A8[16] = "stg3_tou_420\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000010B8[16] = "stg3_tou_421\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000010C8[8] = "sandome";
__declspec(section ".rodata") const f32 vec3_tou2_0000a6c0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_tou2_0000a6cc[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const char tou_03_str_000010E8[8] = "block_1";
__declspec(section ".rodata") const char tou_03_str_000010F0[8] = "block_2";
__declspec(section ".rodata") const char tou_03_str_000010F8[8] = "block_3";
__declspec(section ".rodata") const char tou_03_str_00001100[8] = "block_4";
__declspec(section ".rodata") const char tou_03_str_00001108[8] = "block_5";
__declspec(section ".rodata") const char tou_03_str_00001110[8] = "block_6";
__declspec(section ".rodata") const char tou_03_str_00001118[8] = "block_7";
__declspec(section ".rodata") const char tou_03_str_00001120[8] = "block_8";
__declspec(section ".rodata") const char tou_03_str_00001128[8] = "block_9";
__declspec(section ".rodata") const char tou_03_str_00001130[8] = "stone\0\0";
__declspec(section ".rodata") const char tou_03_str_00001138[16] = "kaiten_souti\0\0\0";
__declspec(section ".rodata") const u32 dat_tou2_0000a738 = 0xFFFFFF00;
__declspec(section ".rodata") const char tou_03_str_0000114C[8] = "group34";
__declspec(section ".rodata") const char tou_03_str_00001154[12] = "a_kai_right";
__declspec(section ".rodata") const char tou_03_str_00001160[8] = "a_butai";
__declspec(section ".rodata") const char tou_03_str_00001168[20] = "BGM_EVT_STG3_GANCE2";
__declspec(section ".rodata") const char tou_03_str_0000117C[16] = "stg3_tou_463\0\0\0";
__declspec(section ".rodata") const char tou_03_str_0000118C[24] = "SFX_STG3_GROUND_SHAKE1\0";
__declspec(section ".rodata") const char tou_03_str_000011A4[4] = "p\0\0";
__declspec(section ".rodata") const char tou_03_str_000011A8[8] = "butai_2";
__declspec(section ".rodata") const char tou_03_str_000011B0[8] = "butai_1";
__declspec(section ".rodata") const char tou_03_str_000011B8[8] = "tyuubu\0";
__declspec(section ".rodata") const char tou_03_str_000011C0[12] = "guruguru\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000011CC[8] = "hakkou\0";
__declspec(section ".rodata") const char tou_03_str_000011D4[8] = "souti\0\0";
__declspec(section ".rodata") const char tou_03_str_000011DC[8] = "comp\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000011E4[28] = "SFX_STG3_ABSORB_DEVICE_UP1\0";
__declspec(section ".rodata") const char tou_03_str_00001200[32] = "SFX_STG3_ABSORB_DEVICE_UP_STOP1";
__declspec(section ".rodata") const char tou_03_str_00001220[20] = "SFX_STG3_RING_DOWN1";
__declspec(section ".rodata") const char tou_03_str_00001234[8] = "a_souti";
__declspec(section ".rodata") const char tou_03_str_0000123C[16] = "stg3_tou_464\0\0\0";
__declspec(section ".rodata") const char tou_03_str_0000124C[16] = "stg3_tou_465\0\0\0";
__declspec(section ".rodata") const char tou_03_str_0000125C[16] = "stg3_tou_465_01";
__declspec(section ".rodata") const char tou_03_str_0000126C[16] = "stg3_tou_466\0\0\0";
__declspec(section ".rodata") const char tou_03_str_0000127C[4] = "P_1";
__declspec(section ".rodata") const char tou_03_str_00001280[4] = "P_2";
__declspec(section ".rodata") const char tou_03_str_00001284[24] = "SFX_STG3_ABSORB_DEVICE1";
__declspec(section ".rodata") const char tou_03_str_0000129C[20] = "SFX_STG3_GANSU_BIG1";
__declspec(section ".rodata") const char tou_03_str_000012B0[12] = "OFF_d_bom\0\0";
__declspec(section ".rodata") const char tou_03_str_000012BC[20] = "SFX_STG3_GANSU_BIG2";
__declspec(section ".rodata") const char tou_03_str_000012D0[4] = "A_1";
__declspec(section ".rodata") const char tou_03_str_000012D4[16] = "stg3_tou_466_01";
__declspec(section ".rodata") const char tou_03_str_000012E4[8] = "M_I_N\0\0";
__declspec(section ".rodata") const char tou_03_str_000012EC[16] = "stg3_tou_467\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000012FC[16] = "stg3_tou_468\0\0\0";
__declspec(section ".rodata") const char tou_03_str_0000130C[24] = "SFX_STG3_ABSORB_DEVICE2";
__declspec(section ".rodata") const char tou_03_str_00001324[4] = "D_1";
__declspec(section ".rodata") const char tou_03_str_00001328[4] = "D_2";
__declspec(section ".rodata") const char tou_03_str_0000132C[16] = "stg3_tou_473\0\0\0";
__declspec(section ".rodata") const char tou_03_str_0000133C[16] = "BGM_EVT_ORGEL1\0";
__declspec(section ".rodata") const char tou_03_str_0000134C[16] = "stg3_tou_473_01";
__declspec(section ".rodata") const char tou_03_str_0000135C[24] = "SFX_VOICE_MARIO_FIND1_2";
__declspec(section ".rodata") const char tou_03_str_00001374[16] = "stg3_tou_473_02";
__declspec(section ".rodata") const char tou_03_str_00001384[16] = "stg3_tou_473_03";
__declspec(section ".rodata") const char tou_03_str_00001394[16] = "stg3_tou_473_04";
__declspec(section ".rodata") const char tou_03_str_000013A4[16] = "stg3_tou_473_05";
__declspec(section ".rodata") const char tou_03_str_000013B4[16] = "stg3_tou_473_06";
__declspec(section ".rodata") const char tou_03_str_000013C4[16] = "stg3_tou_473_07";
__declspec(section ".rodata") const char tou_03_str_000013D4[20] = "stg3_tou_473_07_01\0";
__declspec(section ".rodata") const char tou_03_str_000013E8[20] = "stg3_tou_473_07_02\0";
__declspec(section ".rodata") const char tou_03_str_000013FC[20] = "stg3_tou_473_07_03\0";
__declspec(section ".rodata") const char tou_03_str_00001410[20] = "stg3_tou_473_07_04\0";
__declspec(section ".rodata") const char tou_03_str_00001424[4] = "sl\0";
__declspec(section ".rodata") const char tou_03_str_00001428[16] = "sunlight_n64\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001438[24] = "stg3_tou_473_07_04_01\0\0";
__declspec(section ".rodata") const char tou_03_str_00001450[8] = "eff_2\0\0";
__declspec(section ".rodata") const char tou_03_str_00001458[20] = "pokopi_pcharge_n64\0";
__declspec(section ".rodata") const char tou_03_str_0000146C[28] = "SFX_STG3_STARSTONE_ROUND1\0\0";
__declspec(section ".rodata") const char tou_03_str_00001488[8] = "eff_1\0\0";
__declspec(section ".rodata") const char tou_03_str_00001490[20] = "stg3_tou_473_07_05\0";
__declspec(section ".rodata") const char tou_03_str_000014A4[20] = "stg3_tou_473_07_06\0";
__declspec(section ".rodata") const char tou_03_str_000014B8[20] = "stg3_tou_473_07_07\0";
__declspec(section ".rodata") const char tou_03_str_000014CC[20] = "stg3_tou_473_07_08\0";
__declspec(section ".rodata") const char tou_03_str_000014E0[20] = "stg3_tou_473_07_09\0";
__declspec(section ".rodata") const char tou_03_str_000014F4[16] = "stg3_tou_473_08";
__declspec(section ".rodata") const char tou_03_str_00001504[28] = "SFX_STG3_STARSTONE_ROUND2\0\0";
__declspec(section ".rodata") const char tou_03_str_00001520[16] = "stg3_tou_473_09";
__declspec(section ".rodata") const char tou_03_str_00001530[16] = "stg3_tou_473_10";
__declspec(section ".rodata") const char tou_03_str_00001540[16] = "stg3_tou_473_11";
__declspec(section ".rodata") const char tou_03_str_00001550[24] = "SFX_VOICE_MARIO_NOD1_4\0";
__declspec(section ".rodata") const char tou_03_str_00001568[8] = "M_N_2\0\0";
__declspec(section ".rodata") const char tou_03_str_00001570[20] = "SFX_STG3_FIGHTING3\0";
__declspec(section ".rodata") const char tou_03_str_00001584[16] = "stg3_tou_119\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001594[16] = "stg3_tou_120\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000015A4[16] = "stg3_tou_121\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000015B4[16] = "stg3_tou_122\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000015C4[16] = "stg3_tou_123\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000015D4[16] = "stg3_tou_124\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000015E4[16] = "stg3_tou_125\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000015F4[16] = "stg3_tou_126\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001604[16] = "stg3_tou_127\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001614[16] = "stg3_tou_128\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001624[16] = "stg3_tou_128_01";
__declspec(section ".rodata") const char tou_03_str_00001634[16] = "stg3_tou_128_02";
__declspec(section ".rodata") const char tou_03_str_00001644[16] = "stg3_tou_129\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001654[16] = "stg3_tou_129_01";
__declspec(section ".rodata") const char tou_03_str_00001664[16] = "stg3_tou_129_02";
__declspec(section ".rodata") const char tou_03_str_00001674[16] = "stg3_tou_130\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001684[16] = "stg3_tou_130_01";
__declspec(section ".rodata") const char tou_03_str_00001694[16] = "stg3_tou_130_02";
__declspec(section ".rodata") const char tou_03_str_000016A4[16] = "stg3_tou_131\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000016B4[16] = "stg3_tou_132\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000016C4[16] = "stg3_tou_133\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000016D4[16] = "stg3_tou_134\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000016E4[16] = "stg3_tou_135\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000016F4[16] = "stg3_tou_136\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001704[16] = "stg3_tou_137\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001714[16] = "stg3_tou_138\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001724[16] = "stg3_tou_139\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001734[16] = "stg3_tou_140\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001744[16] = "stg3_tou_140_01";
__declspec(section ".rodata") const char tou_03_str_00001754[16] = "stg3_tou_140_02";
__declspec(section ".rodata") const char tou_03_str_00001764[16] = "stg3_tou_141\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001774[16] = "stg3_tou_141_01";
__declspec(section ".rodata") const char tou_03_str_00001784[16] = "stg3_tou_141_02";
__declspec(section ".rodata") const char tou_03_str_00001794[16] = "stg3_tou_142\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000017A4[16] = "stg3_tou_142_01";
__declspec(section ".rodata") const char tou_03_str_000017B4[16] = "stg3_tou_142_02";
__declspec(section ".rodata") const char tou_03_str_000017C4[16] = "ENV_STG3_TOU3\0\0";
__declspec(section ".rodata") const char tou_03_str_000017D4[4] = "ue\0";
__declspec(section ".rodata") const char tou_03_str_000017D8[16] = "light_coloer\0\0\0";
__declspec(section ".rodata") const char tou_03_str_000017E8[8] = "light_l";
__declspec(section ".rodata") const char tou_03_str_000017F0[8] = "light_r";
__declspec(section ".rodata") const char tou_03_str_000017F8[12] = "monittor\0\0\0";
__declspec(section ".rodata") const char tou_03_str_00001804[12] = "a_kyaku_A\0\0";
__declspec(section ".rodata") const char tou_03_str_00001810[12] = "a_kyaku_B\0\0";
__declspec(section ".rodata") const char tou_03_str_0000181C[8] = "kyaku5\0";
__declspec(section ".rodata") const char tou_03_str_00001824[8] = "kyaku6\0";
__declspec(section ".rodata") const char tou_03_str_0000182C[8] = "kyaku7\0";
__declspec(section ".rodata") const char tou_03_str_00001834[8] = "kyaku8\0";
__declspec(section ".rodata") const f32 float_15_tou2_0000ae2c = 15.0f;
__declspec(section ".rodata") const char tou_03_str_00001840[12] = "group151\0\0\0";
__declspec(section ".rodata") const f32 float_100_tou2_0000ae3c = 100.0f;
__declspec(section ".rodata") const f32 zero_tou2_0000ae40 = 0.0f;
__declspec(section ".rodata") const f32 float_1_tou2_0000ae44 = 1.0f;
__declspec(section ".rodata") const f32 float_0p5_tou2_0000ae48 = 0.5f;
__declspec(section ".rodata") const f32 float_6p2832_tou2_0000ae4c = 6.2831855f;
__declspec(section ".rodata") const f32 float_360_tou2_0000ae50 = 360.0f;
__declspec(section ".rodata") const char tou_03_str_00001864[24] = "SFX_EVT_STARSTONE_JUMP1";
__declspec(section ".rodata") const char tou_03_str_0000187C[8] = "\x8d\xbd%d_%d";
__declspec(section ".rodata") const f32 float_3_tou2_0000ae74 = 3.0f;
__declspec(section ".rodata") const f32 float_10_tou2_0000ae78 = 10.0f;
__declspec(section ".rodata") const f32 float_210_tou2_0000ae7c = 210.0f;
__declspec(section ".rodata") const f32 float_neg210_tou2_0000ae80 = -210.0f;
__declspec(section ".rodata") const f32 float_60_tou2_0000ae84 = 60.0f;
__declspec(section ".rodata") const f32 float_0p25_tou2_0000ae88 = 0.25f;
__declspec(section ".rodata") const f32 float_4p75_tou2_0000ae8c = 4.75f;
__declspec(section ".rodata") const f32 float_3p75_tou2_0000ae90 = 3.75f;
__declspec(section ".rodata") const f32 float_16_tou2_0000ae94 = 16.0f;
__declspec(section ".rodata") const f32 float_6_tou2_0000ae98 = 6.0f;
__declspec(section ".rodata") const f32 float_1000_tou2_0000ae9c = 1000.0f;
__declspec(section ".rodata") const f32 float_neg1_tou2_0000aea0 = -1.0f;
__declspec(section ".rodata") const f32 float_6p2832_tou2_0000aea4 = 6.283184f;
__declspec(section ".rodata") const f32 float_250_tou2_0000aea8 = 250.0f;
__declspec(section ".rodata") const f32 float_500_tou2_0000aeac = 500.0f;
__declspec(section ".rodata") const f32 float_550_tou2_0000aeb0 = 550.0f;
__declspec(section ".rodata") const f32 float_650_tou2_0000aeb4 = 650.0f;
__declspec(section ".rodata") const f32 float_850_tou2_0000aeb8 = 850.0f;
__declspec(section ".rodata") const f32 float_0p7854_tou2_0000aebc = 0.7853982f;
__declspec(section ".rodata") const f32 float_5p4978_tou2_0000aec0 = 5.4977875f;
__declspec(section ".rodata") const f64 double_70_tou2_0000aec8 = 70.0;
__declspec(section ".rodata") const f32 float_1E05_tou2_0000aed0 = 100000.0f;
__declspec(section ".rodata") const f32 float_570_tou2_0000aed4 = 570.0f;
__declspec(section ".rodata") const f32 float_40_tou2_0000aed8 = 40.0f;
__declspec(section ".rodata") const f32 float_350_tou2_0000aedc = 350.0f;
__declspec(section ".rodata") const f64 double_to_int_tou2_0000aee0 = 4503601774854144.0;


#endif

#ifdef NONMATCHING // all-C link: pool objects the C names, defined on the asm side only
__declspec(section ".data") const u32 zero_tou2_00009ea8[1] = {0x00000000};
#endif
