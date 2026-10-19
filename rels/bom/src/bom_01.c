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
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
__declspec(section ".rodata") extern const u32 dat_bom_00006360;
__declspec(section ".rodata") extern const f32 vec3_bom_00006364[3];
__declspec(section ".rodata") extern const f32 vec3_bom_00006370[3];
__declspec(section ".rodata") extern const u32 dat_bom_0000637c;
__declspec(section ".rodata") extern const u32 dat_bom_00006380;
__declspec(section ".rodata") extern const f32 vec3_bom_00006384[3];
__declspec(section ".rodata") extern const f32 vec3_bom_00006390[3];
__declspec(section ".rodata") extern const f32 vec3_bom_0000639c[3];
__declspec(section ".rodata") extern const f32 vec3_bom_000063a8[3];
__declspec(section ".rodata") extern const f32 vec3_bom_000063b4[3];
__declspec(section ".rodata") extern const f32 vec3_bom_000063c0[3];
__declspec(section ".rodata") extern const f32 vec3_bom_0000649c[3];
__declspec(section ".rodata") extern const f32 vec3_bom_000064a8[3];
__declspec(section ".rodata") extern const f32 vec3_bom_000064b4[3];
__declspec(section ".rodata") extern const f32 vec3_bom_000064c0[3];
__declspec(section ".rodata") extern const f32 vec3_bom_000064cc[3];
__declspec(section ".rodata") extern const f32 vec3_bom_000064d8[3];
__declspec(section ".rodata") extern const f32 vec3_bom_00006ea4[3];
__declspec(section ".rodata") extern const f32 vec3_bom_00006eb0[3];
__declspec(section ".rodata") extern const f32 vec3_bom_00006ebc[3];
__declspec(section ".rodata") extern const f32 vec3_bom_00006ec8[3];
__declspec(section ".rodata") extern const f32 vec3_bom_00006ed4[3];
__declspec(section ".rodata") extern const f32 float_1_bom_00006ffc;
__declspec(section ".rodata") extern const f32 float_100_bom_00007000;
__declspec(section ".rodata") extern const f32 zero_bom_00007004;
__declspec(section ".rodata") extern const f32 float_0p1_bom_00007008;
__declspec(section ".rodata") extern const f32 float_0p5_bom_0000700c;
__declspec(section ".rodata") extern const f32 float_10_bom_00007010;
__declspec(section ".rodata") extern const char bom_01_str_00000DDC[];
__declspec(section ".rodata") extern const f64 double_to_int_bom_00007030;
__declspec(section ".rodata") extern const u32 zero_bom_00007038;
__declspec(section ".rodata") extern const f32 float_270_bom_0000703c;
__declspec(section ".rodata") extern const char bom_01_str_00000E08[];
__declspec(section ".rodata") extern const f32 float_4_bom_00007044;
__declspec(section ".rodata") extern const char bom_01_str_00000E10[];
__declspec(section ".rodata") extern const f32 float_2_bom_0000704c;
__declspec(section ".rodata") extern const char bom_01_str_00000E18[];
__declspec(section ".rodata") extern const f32 float_1000_bom_0000705c;
__declspec(section ".rodata") extern const f32 float_6p2832_bom_00007060;
__declspec(section ".rodata") extern const f32 float_0p125_bom_00007064;
__declspec(section ".rodata") extern const f32 float_0p00761_bom_00007068;
__declspec(section ".rodata") extern const f32 float_0p16605_bom_0000706c;
__declspec(section ".rodata") extern const f32 float_3p1416_bom_00007070;
__declspec(section ".rodata") extern const f32 float_1p5708_bom_00007074;
__declspec(section ".rodata") extern const f32 float_4p7124_bom_00007078;
__declspec(section ".rodata") extern const f32 float_0p03705_bom_0000707c;
__declspec(section ".rodata") extern const f32 float_0p4967_bom_00007080;
__declspec(section ".rodata") extern const f64 double_0p7854_bom_00007088;
__declspec(section ".rodata") extern const char bom_01_str_00000E58[];
__declspec(section ".rodata") extern const f32 float_280_bom_000070a4;
__declspec(section ".rodata") extern const f32 float_3_bom_000070a8;
__declspec(section ".rodata") extern const f32 float_32767_bom_000070ac;
__declspec(section ".rodata") extern const f32 float_150_bom_000070b0;
__declspec(section ".rodata") extern const f32 float_30_bom_000070b4;
__declspec(section ".rodata") extern const f32 float_50_bom_000070b8;
__declspec(section ".rodata") extern const f32 float_400_bom_000070bc;
__declspec(section ".rodata") extern const f32 float_70_bom_000070c0;
__declspec(section ".rodata") extern const f32 float_350_bom_000070c4;
__declspec(section ".rodata") extern const f32 float_180_bom_000070c8;
__declspec(section ".rodata") extern const f32 float_neg1000_bom_000070cc;
__declspec(section ".rodata") extern const f32 float_neg20_bom_000070d0;
__declspec(section ".rodata") extern const f32 float_deg2rad_bom_000070d4;
__declspec(section ".rodata") extern const f32 float_20_bom_000070d8;
__declspec(section ".rodata") extern const f32 float_60_bom_000070dc;
__declspec(section ".rodata") extern const f64 double_to_int_mask_bom_000070e0;
__declspec(section ".rodata") extern const f32 float_500_bom_000070e8;
__declspec(section ".rodata") extern const char bom_01_str_00000EB4[];
__declspec(section ".rodata") extern const f32 float_6_bom_000070f0;
__declspec(section ".rodata") extern const f32 float_600_bom_000070f4;
__declspec(section ".rodata") extern const f32 float_300_bom_000070f8;
__declspec(section ".rodata") extern const f32 float_3700_bom_000070fc;
__declspec(section ".rodata") extern const f32 float_neg650_bom_00007100;
__declspec(section ".rodata") extern const f32 float_neg450_bom_00007104;
__declspec(section ".rodata") extern const char bom_01_str_00000ED0[];
__declspec(section ".rodata") extern const char bom_01_str_00000ED8[];
__declspec(section ".rodata") extern const f32 float_800_bom_0000711c;
__declspec(section ".rodata") extern const f32 float_neg1_bom_00007120;
__declspec(section ".rodata") extern const f32 float_neg100_bom_00007124;
__declspec(section ".rodata") extern const f32 float_neg60_bom_00007128;
__declspec(section ".rodata") extern const f32 float_0p6_bom_0000712c;
__declspec(section ".rodata") extern const f32 float_90_bom_00007130;
__declspec(section ".rodata") extern const f32 float_126_bom_00007134;
__declspec(section ".rodata") extern const f32 float_162_bom_00007138;
__declspec(section ".rodata") extern const f32 float_120_bom_0000713c;
__declspec(section ".rodata") extern const f32 float_110_bom_00007140;
__declspec(section ".rodata") extern const f32 float_neg160_bom_00007144;
__declspec(section ".rodata") extern const f32 float_0p8_bom_00007148;
__declspec(section ".rodata") extern const f32 float_230_bom_0000714c;
__declspec(section ".rodata") extern const f32 float_neg170_bom_00007150;
__declspec(section ".rodata") extern const f32 float_neg240_bom_00007154;
__declspec(section ".rodata") extern const f32 float_neg190_bom_00007158;
__declspec(section ".rodata") extern const f32 float_16_bom_0000715c;
__declspec(section ".rodata") extern const f32 float_neg16_bom_00007160;
__declspec(section ".rodata") extern const f32 float_neg180_bom_00007164;
__declspec(section ".rodata") extern const f32 float_neg220_bom_00007168;
__declspec(section ".rodata") extern const f32 float_200_bom_0000716c;
#define EXT_LIT(sym, val) (sym)

extern const char bom_01_str_00000194[];
extern const char bom_01_str_000001A0[];
extern const char bom_01_str_000001AC[];
extern const char bom_01_str_000001B8[];
extern const char bom_01_str_000001C8[];
extern const char bom_01_str_000001D4[];
extern const char bom_01_str_000001E0[];
extern const char bom_01_str_000001EC[];
extern const char bom_01_str_000001F8[];
extern const char bom_01_str_00000200[];
extern const char bom_01_str_00000208[];
extern const char bom_01_str_00000210[];
extern const char bom_01_str_00000218[];
extern const char bom_01_str_00000220[];
extern const char bom_01_str_00000234[];
extern const char bom_01_str_00000244[];
extern const char bom_01_str_0000025C[];
extern const char bom_01_str_000002AC[];
extern const char bom_01_str_000002B4[];
extern const char bom_01_str_000002C0[];
extern const char bom_01_str_000002DC[];
extern const char bom_01_str_000002E4[];
extern const char bom_01_str_000002EC[];
extern const char bom_01_str_000002F8[];
extern const char bom_01_str_00000300[];
extern const char bom_01_str_0000030C[];
extern const char bom_01_str_00000318[];
extern const char bom_01_str_0000031C[];
extern const char bom_01_str_00000324[];
extern const char bom_01_str_0000032C[];
extern const char bom_01_str_00000330[];
extern const char bom_01_str_00000338[];
extern const char bom_01_str_00000340[];
extern const char bom_01_str_00000348[];
extern const char bom_01_str_00000350[];
extern const char bom_01_str_00000368[];
extern const char bom_01_str_00000370[];
extern const char bom_01_str_00000380[];
extern const char bom_01_str_00000390[];
extern const char bom_01_str_000003A0[];
extern const char bom_01_str_000003AC[];
extern const char bom_01_str_000003BC[];
extern const char bom_01_str_000003C8[];
extern const char bom_01_str_000003CC[];
extern const char bom_01_str_000003D8[];
extern const char bom_01_str_000003E4[];
extern const char bom_01_str_000003EC[];
extern const char bom_01_str_000003F4[];
extern const char bom_01_str_00000410[];
extern const char bom_01_str_00000418[];
extern const char bom_01_str_00000430[];
extern const char bom_01_str_00000440[];
extern const char bom_01_str_00000450[];
extern const char bom_01_str_00000468[];
extern const char bom_01_str_0000047C[];
extern const char bom_01_str_00000484[];
extern const char bom_01_str_00000490[];
extern const char bom_01_str_000004A0[];
extern const char bom_01_str_000004AC[];
extern const char bom_01_str_000004B8[];
extern const char bom_01_str_000004C4[];
extern const char bom_01_str_000004D0[];
extern const char bom_01_str_000004EC[];
extern const char bom_01_str_00000508[];
extern const char bom_01_str_00000510[];
extern const char bom_01_str_0000051C[];
extern const char bom_01_str_00000528[];
extern const char bom_01_str_00000534[];
extern const char bom_01_str_0000054C[];
extern const char bom_01_str_00000558[];
extern const char bom_01_str_00000564[];
extern const char bom_01_str_0000057C[];
extern const char bom_01_str_00000594[];
extern const char bom_01_str_000005AC[];
extern const char bom_01_str_000005B4[];
extern const char bom_01_str_000005C0[];
extern const char bom_01_str_000005D8[];
extern const char bom_01_str_000005E8[];
extern const char bom_01_str_000005F8[];
extern const char bom_01_str_00000610[];
extern const char bom_01_str_0000061C[];
extern const char bom_01_str_0000062C[];
extern const char bom_01_str_0000063C[];
extern const char bom_01_str_0000064C[];
extern const char bom_01_str_0000065C[];
extern const char bom_01_str_0000066C[];
extern const char bom_01_str_0000067C[];
extern const char bom_01_str_0000068C[];
extern const char bom_01_str_0000069C[];
extern const char bom_01_str_000006A8[];
extern const char bom_01_str_000006BC[];
extern const char bom_01_str_000006C8[];
extern const char bom_01_str_000006E0[];
extern const char bom_01_str_000006EC[];
extern const char bom_01_str_00000704[];
extern const char bom_01_str_0000071C[];
extern const char bom_01_str_00000728[];
extern const char bom_01_str_00000730[];
extern const char bom_01_str_0000073C[];
extern const char bom_01_str_00000748[];
extern const char bom_01_str_00000760[];
extern const char bom_01_str_00000768[];
extern const char bom_01_str_00000774[];
extern const char bom_01_str_0000077C[];
extern const char bom_01_str_00000794[];
extern const char bom_01_str_000007A0[];
extern const char bom_01_str_000007BC[];
extern const char bom_01_str_000007CC[];
extern const char bom_01_str_000007DC[];
extern const char bom_01_str_000007EC[];
extern const char bom_01_str_00000804[];
extern const char bom_01_str_00000814[];
extern const char bom_01_str_00000824[];
extern const char bom_01_str_00000834[];
extern const char bom_01_str_00000840[];
extern const char bom_01_str_0000084C[];
extern const char bom_01_str_00000854[];
extern const char bom_01_str_00000870[];
extern const char bom_01_str_00000888[];
extern const char bom_01_str_0000089C[];
extern const char bom_01_str_000008B4[];
extern const char bom_01_str_000008C4[];
extern const char bom_01_str_000008D0[];
extern const char bom_01_str_000008DC[];
extern const char bom_01_str_000008E8[];
extern const char bom_01_str_000008F4[];
extern const char bom_01_str_000008FC[];
extern const char bom_01_str_00000910[];
extern const char bom_01_str_00000924[];
extern const char bom_01_str_00000934[];
extern const char bom_01_str_00000940[];
extern const char bom_01_str_00000950[];
extern const char bom_01_str_0000095C[];
extern const char bom_01_str_0000096C[];
extern const char bom_01_str_0000097C[];
extern const char bom_01_str_00000988[];
extern const char bom_01_str_00000998[];
extern const char bom_01_str_000009A4[];
extern const char bom_01_str_000009B4[];
extern const char bom_01_str_000009C4[];
extern const char bom_01_str_000009D0[];
extern const char bom_01_str_000009E0[];
extern const char bom_01_str_000009EC[];
extern const char bom_01_str_000009FC[];
extern const char bom_01_str_00000A0C[];
extern const char bom_01_str_00000A18[];
extern const char bom_01_str_00000A28[];
extern const char bom_01_str_00000A34[];
extern const char bom_01_str_00000A44[];
extern const char bom_01_str_00000A54[];
extern const char bom_01_str_00000A60[];
extern const char bom_01_str_00000A6C[];
extern const char bom_01_str_00000A7C[];
extern const char bom_01_str_00000A88[];
extern const char bom_01_str_00000A94[];
extern const char bom_01_str_00000AA4[];
extern const char bom_01_str_00000AB0[];
extern const char bom_01_str_00000ABC[];
extern const char bom_01_str_00000ACC[];
extern const char bom_01_str_00000AD8[];
extern const char bom_01_str_00000AE4[];
extern const char bom_01_str_00000AF4[];
extern const char bom_01_str_00000B00[];
extern const char bom_01_str_00000B0C[];
extern const char bom_01_str_00000B1C[];
extern const char bom_01_str_00000B2C[];
extern const char bom_01_str_00000B3C[];
extern const char bom_01_str_00000B4C[];
extern const char bom_01_str_00000B60[];
extern const char bom_01_str_00000B6C[];
extern const char bom_01_str_00000B80[];
extern const char bom_01_str_00000B8C[];
extern const char bom_01_str_00000BA0[];
extern const char bom_01_str_00000BAC[];
extern const char bom_01_str_00000BC0[];
extern const char bom_01_str_00000BD4[];
extern const char bom_01_str_00000BE8[];
extern const char bom_01_str_00000BFC[];
extern const char bom_01_str_00000C10[];
extern const char bom_01_str_00000C24[];
extern const char bom_01_str_00000C30[];
extern const char bom_01_str_00000C38[];
extern const char bom_01_str_00000C44[];
extern const char bom_01_str_00000C54[];
extern const char bom_01_str_00000C60[];
extern const char bom_01_str_00000CA8[];
extern const char bom_01_str_00000CB0[];
extern const char bom_01_str_00000CBC[];
extern const char bom_01_str_00000CCC[];
extern const char bom_01_str_00000CDC[];
extern const char bom_01_str_00000CEC[];
extern const char bom_01_str_00000CFC[];
extern const char bom_01_str_00000D0C[];
extern const char bom_01_str_00000D1C[];
extern const char bom_01_str_00000D2C[];
extern const char bom_01_str_00000D34[];
extern const char bom_01_str_00000D40[];
extern const char bom_01_str_00000D50[];
extern const char bom_01_str_00000D64[];
extern const char bom_01_str_00000D74[];
extern const char bom_01_str_00000D84[];
extern const char bom_01_str_00000D8C[];
extern const char bom_01_str_00000D94[];
extern const char bom_01_str_00000D9C[];
extern const char bom_01_str_00000DA4[];
extern const char bom_01_str_00000DAC[];
extern const char bom_01_str_00000DB4[];
extern const char bom_01_str_00000DBC[];
#endif

typedef struct SightWork { FileEntry* tpl; s32 level[5]; f32 rot; s32 dir; s32 count1; s32 count2; } SightWork;
SightWork* sight_wp;
#ifndef NONMATCHING
__declspec(section ".data") u8 g5_name_s915[64];
#endif
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
smartEntry* lp;
#define EXT_DATA ((ExtAnimDef*)ext_data)
ExtPose* extGetPosePtr(void);
s32 extGetPoseNum(void);
static void pose_change(s32 i, const char* name);
static void pose_change(s32 i, const char* name);
static s32 ext_data[93];
#ifdef NONMATCHING
static inline f32 chb_sin(f32 x) { f32 y; f32 x2; f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
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
#ifdef NONMATCHING
static USER_FUNC(anim_tevcallback);
#endif
#ifndef NONMATCHING
static s32 anim_tevcallback(EventEntry* event, BOOL isFirstCall);
#endif
s32 bom1000_jump(EventEntry* event, BOOL isFirstCall);
s32 bom1000_jump(EventEntry* event, BOOL isFirstCall);
s32 bom1000_msg(EventEntry* event, BOOL isFirstCall);
s32 bom1000_msg(EventEntry* event, BOOL isFirstCall);
s32 bom_fall(EventEntry* event, BOOL isFirstCall);
s32 bom_fall(EventEntry* event, BOOL isFirstCall);
s32 bom_flag(EventEntry* event, BOOL isFirstCall);
s32 bom_flag(EventEntry* event, BOOL isFirstCall);
static s32 depth(EventEntry* event, BOOL isFirstCall);
#ifdef NONMATCHING
static USER_FUNC(depth);
#endif
#ifndef NONMATCHING
static s32 depth(EventEntry* event, BOOL isFirstCall);
#endif
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
#ifdef NONMATCHING
static USER_FUNC(make_name);
#endif
#ifndef NONMATCHING
static s32 make_name(EventEntry* event, BOOL isFirstCall);
#endif
s32 sight(EventEntry* event, BOOL isFirstCall);
s32 sight(EventEntry* event, BOOL isFirstCall);
s32 sight_dir(EventEntry* event, BOOL isFirstCall);
s32 sight_dir(EventEntry* event, BOOL isFirstCall);
static s32 starstone_entry(EventEntry* event, BOOL isFirstCall);
#ifdef NONMATCHING
static USER_FUNC(starstone_entry);
#endif
#ifndef NONMATCHING
static s32 starstone_entry(EventEntry* event, BOOL isFirstCall);
#endif
static s32 starstone_set_pos(EventEntry* event, BOOL isFirstCall);
#ifdef NONMATCHING
static USER_FUNC(starstone_set_pos);
#endif
#ifndef NONMATCHING
static s32 starstone_set_pos(EventEntry* event, BOOL isFirstCall);
#endif
static s32 starstone_set_ry(EventEntry* event, BOOL isFirstCall);
#ifdef NONMATCHING
static USER_FUNC(starstone_set_ry);
#endif
#ifndef NONMATCHING
static s32 starstone_set_ry(EventEntry* event, BOOL isFirstCall);
#endif
s32 taihou_r(EventEntry* event, BOOL isFirstCall);
s32 taihou_r(EventEntry* event, BOOL isFirstCall);
static s32 yami_view(EventEntry* event, BOOL isFirstCall);
#ifdef NONMATCHING
static USER_FUNC(yami_view);
#endif
#ifndef NONMATCHING
static s32 yami_view(EventEntry* event, BOOL isFirstCall);
#endif
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
#endif
#ifndef NONMATCHING
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
int __cvt_ull_flt();
int __div2i();
int __div2u();
void *memset(void *dest, int ch, size_t count);
int rand(void);
int sprintf(char *s, const char *format, ...);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
void envSetYamiView(Mtx mtx);
void drawBG(s32 id, f32 x, f32 y, f32 sx, f32 sy, f32 rot);
#endif

#ifdef NONMATCHING
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
#ifndef NONMATCHING
void drawNum(s32 num, s32 digits, f32 x, f32 y, f32 scale);
#endif

#ifdef NONMATCHING
void drawNum(s32 num, s32 digits, f32 x, f32 y, f32 scale) {
    GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
    GXTexObj obj;
    s32 i;
    s32 id;
    f32 w;
    s32 n = num < 0 ? -num : num;
#endif
#ifndef NONMATCHING
void disp_sight(CameraId camera, void* param);
#endif

#ifdef NONMATCHING
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
#ifndef NONMATCHING
s32 sight(EventEntry* event, BOOL isFirstCall);
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
#endif
#ifndef NONMATCHING
s32 sight_dir(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
s32 bom_flag(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
s32 bom_fall(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
    winTexInit(*sight_wp->tpl->data);
    winTexSet(23, (Vec){-200.0f, 150.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    drawNum((gp->renderTime / 100) / 1000, 10, 90.0f, 180.0f, 0.6f);
    drawNum((gp->renderTime / 200) / 1000, 8, 126.0f, 150.0f, 0.6f);
    drawNum((gp->renderTime / 300) / 1000, 6, 162.0f, 120.0f, 0.6f);
    drawNum((gp->renderTime / 400) / 1000, 6, 162.0f, 90.0f, 0.6f);
    drawNum(gp->retraceCount / 4, 4, 110.0f, -160.0f, 1.0f);
    drawNum(gp->retraceCount / 8, 2, 230.0f, -170.0f, 0.8f);
#endif
#ifndef NONMATCHING
static void pose_init(void);
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
static void pose_main(void);
#endif

#ifdef NONMATCHING
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
#ifndef NONMATCHING
static void pose_change(s32 i, const char* name);
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

s32 sight_dir(EventEntry* event, BOOL isFirstCall) {
    sight_wp->dir = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

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

static void pose_init(void) {
    BomWork* wp; ExtAnimDef* def; char buf[32]; s32 i; s32 start; i = 0; wp = lp->address; def = EXT_DATA; strcpy(buf, ""); wp->animCount = -1; do { if (strcmp(def->name, buf) != 0) { strcpy(buf, def->name); wp->animCount++; start = i; } strcpy(wp->anims[wp->animCount].name, buf); wp->anims[wp->animCount].start = start; wp->anims[wp->animCount].count = i - start + 1; i++; wp->anims[wp->animCount].time = def->time; } while ((++def)->file != NULL); wp->animCount++;
}

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

static void pose_change(s32 i, const char* name) {
    BomWork* wp = lp->address; s32 j = 0; BomAnim* a; for (a = wp->anims; j < wp->animCount; j++, a++) { if (strcmp(a->name, name) == 0) { break; } } if (j < wp->animCount && wp->bom[i].anim != j) { wp->bom[i].anim = (s16)j; wp->bom[i].time = gp->renderTime + rand(); }
}

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
#ifndef NONMATCHING
s32 make_ext_table(EventEntry* event, BOOL isFirstCall);
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
#ifdef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000194)), FLOAT(0.0f), LW(0), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)bom_01_str_00000194)), FLOAT((0.0f)), LW(0), FLOAT((0.0f)))
#endif
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_door_2)
#ifdef NONMATCHING
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000194)), LW(0), FLOAT(0.0f), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
    MULTIPLY_FLOAT(LW(0), FLOAT((0.5f)))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)bom_01_str_00000194)), LW(0), FLOAT((0.0f)), FLOAT((0.0f)))
#endif
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_wall)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.5f))
#ifdef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000001A0)), FLOAT(0.0f), LW(0), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)bom_01_str_000001A0)), FLOAT((0.0f)), LW(0), FLOAT((0.0f)))
#endif
    RETURN
EVT_END()

__declspec(section ".data") s32 door_npc[] = {
#ifdef NONMATCHING
    (s32)/*"ホワイト"*/(char*)str_000001AC, (s32)/*"ペントリット"*/(char*)str_000001B8, (s32)/*"スラリー"*/(char*)str_000001C8, 0,
#endif
#ifndef NONMATCHING
    (s32)/*"ホワイト"*/(char*)bom_01_str_000001AC, (s32)/*"ペントリット"*/(char*)bom_01_str_000001B8, (s32)/*"スラリー"*/(char*)bom_01_str_000001C8, 0,
#endif
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
#ifdef NONMATCHING
    0, 3, 1, (s32)((char*)str_00000194), (s32)((char*)str_000001D4), (s32)((char*)str_000001E0), (s32)((char*)str_000001A0), 0,
    (s32)((char*)str_000001EC), 0, (s32)evt_door_1, (s32)evt_door_2, (s32)evt_wall, (s32)door_npc, 0, 0,
#endif
#ifndef NONMATCHING
    0, 3, 1, (s32)((char*)bom_01_str_00000194), (s32)((char*)bom_01_str_000001D4), (s32)((char*)bom_01_str_000001E0), (s32)((char*)bom_01_str_000001A0), 0,
    (s32)((char*)bom_01_str_000001EC), 0, (s32)evt_door_1, (s32)evt_door_2, (s32)evt_wall, (s32)door_npc, 0, 0,
#endif
    (s32)door_open, (s32)door_close,
};

static s32 bero_entry_data[] = {
#ifdef NONMATCHING
    (s32)((char*)str_000001F8), 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)str_00000200), (s32)((char*)str_00000208), 65537, 0, 0, (s32)((char*)str_00000210),
#endif
#ifndef NONMATCHING
    (s32)((char*)bom_01_str_000001F8), 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)bom_01_str_00000200), (s32)((char*)bom_01_str_00000208), 65537, 0, 0, (s32)((char*)bom_01_str_00000210),
#endif
    0, 20000, 100000, 0, 0, -1, 0, -1,
#ifdef NONMATCHING
    0, (s32)((char*)str_00000218), (s32)((char*)str_000001F8), 65537, 0, 0, 0, 0,
#endif
#ifndef NONMATCHING
    0, (s32)((char*)bom_01_str_00000218), (s32)((char*)bom_01_str_000001F8), 65537, 0, 0, 0, 0,
#endif
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
#ifdef NONMATCHING
    CALL(evt_mario_mov_pos2, -351, 0, FLOAT(120.0f))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_mov_pos2, -351, 0, FLOAT((120.0f)))
#endif
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, -380, 97, 267, -380, 38, -9, 0, 11)
    WAIT_MS(300)
    CALL(evt_mario_set_dir, 270, 300, 0)
    CALL(evt_party_stop, 0)
    WAIT_MS(200)
    IF_INT_EQUAL(GSWF(3885), 1)
#ifdef NONMATCHING
        CALL(evt_msg_print_party, STRING(((char*)str_00000220)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print_party, STRING(((char*)bom_01_str_00000220)))
#endif
        ELSE
#ifdef NONMATCHING
        CALL(evt_msg_print_party, STRING(((char*)str_00000234)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print_party, STRING(((char*)bom_01_str_00000234)))
#endif
    END_IF
    CALL(evt_party_run, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000244)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_0000025C)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)bom_01_str_00000244)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)bom_01_str_0000025C)))
#endif
    WAIT_MS(500)
    CALL(evt_cam3d_evt_off, 500, 11)
    SET_VALUE(GSW(0), 353)
    CALL(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos)
#ifdef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)str_000001F8)))
#endif
#ifndef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)bom_01_str_000001F8)))
#endif
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
#ifndef NONMATCHING
static void ext_init(void);
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
#ifndef NONMATCHING
static void ext_disp(CameraId camera, void* param);
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
#ifndef NONMATCHING
void jump(s32 i, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
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
#ifndef NONMATCHING
static void ext_main(void);
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
#ifndef NONMATCHING
static void ext_dispent(void);
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
#ifdef NONMATCHING
    CALL(evt_npc_entry, STRING(((char*)str_000002AC)), STRING(((char*)str_000002B4)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_entry, STRING(((char*)bom_01_str_000002AC)), STRING(((char*)bom_01_str_000002B4)))
#endif
    CALL(evt_ext_entry, 1000, PTR(ext_data), PTR(ext_init), PTR(ext_main), PTR(ext_dispent))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(gamen_shake)
#ifdef NONMATCHING
    CALL(evt_cam_shake, 4, FLOAT(0.001953125f), FLOAT(0.0f), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_cam_shake, 4, FLOAT(0.001953125f), FLOAT((0.0f)), 0)
#endif
    RETURN
EVT_END()

EVT_BEGIN(gamen_shake2)
#ifdef NONMATCHING
    CALL(evt_cam_shake, 4, FLOAT(0.01953125f), FLOAT(0.0f), 100)
    CALL(evt_cam_shake, 4, FLOAT(0.009765625f), FLOAT(0.0f), 100)
    CALL(evt_cam_shake, 4, FLOAT(0.0048828125f), FLOAT(0.0f), 100)
    CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.0f), 100)
#endif
#ifndef NONMATCHING
    CALL(evt_cam_shake, 4, FLOAT(0.01953125f), FLOAT((0.0f)), 100)
    CALL(evt_cam_shake, 4, FLOAT(0.009765625f), FLOAT((0.0f)), 100)
    CALL(evt_cam_shake, 4, FLOAT(0.0048828125f), FLOAT((0.0f)), 100)
    CALL(evt_cam_shake, 4, FLOAT((0.0f)), FLOAT((0.0f)), 100)
#endif
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
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000002C0)), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000002C0)), 0)
#endif
    CALL(evt_sub_intpl_msec_init, 2, 0, -50, 150)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000002DC)), 0, 0, -40)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000002DC)), 0, LW(0), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)bom_01_str_000002DC)), 0, 0, -40)
    CALL(evt_mapobj_trans, 1, STRING(((char*)bom_01_str_000002DC)), 0, LW(0), 0)
#endif
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    SPAWN_EVENT(PTR(gamen_shake2))
#ifdef NONMATCHING
    CALL(evt_eff, STRING(((char*)str_000002E4)), STRING(((char*)str_000002EC)), 11, 570, 950, 0, FLOAT(3.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff64, STRING(((char*)str_000002F8)), STRING(((char*)str_00000300)), 2, 570, 950, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff, STRING(((char*)str_0000030C)), STRING(((char*)str_0000030C)), 0, 520, 900, 0, 1, 1, 0, 100, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_eff, STRING(((char*)bom_01_str_000002E4)), STRING(((char*)bom_01_str_000002EC)), 11, 570, 950, 0, FLOAT((3.0f)), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff64, STRING(((char*)bom_01_str_000002F8)), STRING(((char*)bom_01_str_00000300)), 2, 570, 950, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff, STRING(((char*)bom_01_str_0000030C)), STRING(((char*)bom_01_str_0000030C)), 0, 520, 900, 0, 1, 1, 0, 100, 0, 0, 0, 0)
#endif
    CALL(taihou_r)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_eff, 0, STRING(((char*)str_00000318)), 1, 570, 950, 0, FLOAT(3.0f), 4, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_eff, 0, STRING(((char*)bom_01_str_00000318)), 1, 570, 950, 0, FLOAT((3.0f)), 4, 0, 0, 0, 0, 0, 0)
#endif
        WAIT_MS(200)
#ifdef NONMATCHING
        CALL(evt_eff, 0, STRING(((char*)str_00000318)), 1, 570, 950, 0, FLOAT(3.0f), 4, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_eff, 0, STRING(((char*)bom_01_str_00000318)), 1, 570, 950, 0, FLOAT((3.0f)), 4, 0, 0, 0, 0, 0, 0)
#endif
    END_INLINE_EVENT
    CALL(evt_sub_intpl_msec_init, 5, -50, 0, 150)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000002DC)), 0, 0, -40)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000002DC)), 0, LW(0), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)bom_01_str_000002DC)), 0, 0, -40)
    CALL(evt_mapobj_trans, 1, STRING(((char*)bom_01_str_000002DC)), 0, LW(0), 0)
#endif
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(effect_delete)
#ifdef NONMATCHING
    CALL(evt_eff_delete, STRING(((char*)str_000002E4)))
    CALL(evt_eff_delete, STRING(((char*)str_000002F8)))
    CALL(evt_eff_delete, STRING(((char*)str_0000030C)))
#endif
#ifndef NONMATCHING
    CALL(evt_eff_delete, STRING(((char*)bom_01_str_000002E4)))
    CALL(evt_eff_delete, STRING(((char*)bom_01_str_000002F8)))
    CALL(evt_eff_delete, STRING(((char*)bom_01_str_0000030C)))
#endif
    RETURN
EVT_END()

static EVT_BEGIN(mario_kemuri)
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
        CALL(evt_eff, 0, STRING(((char*)str_000002EC)), 12, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_eff, 0, STRING(((char*)bom_01_str_000002EC)), 12, LW(0), LW(1), LW(2), FLOAT((1.0f)), 0, 0, 0, 0, 0, 0, 0)
#endif
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
#ifdef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000194)), 0, 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000001A0)), 0, 0, 0)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000001EC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000001A0)), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)bom_01_str_00000194)), 0, 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)bom_01_str_000001A0)), 0, 0, 0)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)bom_01_str_000001EC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)bom_01_str_000001A0)), 1)
#endif
    RETURN
EVT_END()

EVT_BEGIN(cam_inside)
    CALL(evt_cam3d_evt_set, -160, 125, -100, 10, 55, -427, 0, 11)
    CALL(evt_map_set_blend, 0, 0, 0, 0, 0)
    CALL(evt_map_set_blend, 1, 0, 0, 0, 0)
#ifdef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000194)), 90, 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000001A0)), 0, -90, 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000001EC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000001A0)), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)bom_01_str_00000194)), 90, 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)bom_01_str_000001A0)), 0, -90, 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)bom_01_str_000001EC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)bom_01_str_000001A0)), 1)
#endif
    RETURN
EVT_END()

EVT_BEGIN(cam_inside2)
    CALL(evt_cam3d_evt_set, -93, 104, -250, 9, 62, -447, 0, 11)
    CALL(evt_map_set_blend, 0, 0, 0, 0, 0)
    CALL(evt_map_set_blend, 1, 0, 0, 0, 0)
#ifdef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000194)), 90, 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000001A0)), 0, -90, 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000001EC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000001A0)), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_rotate, 1, STRING(((char*)bom_01_str_00000194)), 90, 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)bom_01_str_000001A0)), 0, -90, 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)bom_01_str_000001EC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)bom_01_str_000001A0)), 1)
#endif
    RETURN
EVT_END()

static EVT_BEGIN(party_damage_pose)
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_0000031C)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)bom_01_str_0000031C)))
#endif
        CASE_EQUAL(2)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000324)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)bom_01_str_00000324)))
#endif
        CASE_EQUAL(3)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_0000032C)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)bom_01_str_0000032C)))
#endif
        CASE_EQUAL(4)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000330)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)bom_01_str_00000330)))
#endif
        CASE_EQUAL(5)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000338)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)bom_01_str_00000338)))
#endif
        CASE_EQUAL(6)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000340)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)bom_01_str_00000340)))
#endif
        CASE_EQUAL(7)
#ifdef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000348)))
#endif
#ifndef NONMATCHING
        CALL(evt_party_set_pose, 0, STRING(((char*)bom_01_str_00000348)))
#endif
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(effect_1)
    SET_VALUE(LW(0), -220)
    LOOP(22)
#ifdef NONMATCHING
        CALL(evt_eff, 0, STRING(((char*)str_000002EC)), 2, LW(0), 5, -220, FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
        CALL(evt_eff, 0, STRING(((char*)str_000002EC)), 2, LW(0), 5, 220, FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_eff, 0, STRING(((char*)bom_01_str_000002EC)), 2, LW(0), 5, -220, FLOAT((1.0f)), 0, 0, 0, 0, 0, 0, 0)
        CALL(evt_eff, 0, STRING(((char*)bom_01_str_000002EC)), 2, LW(0), 5, 220, FLOAT((1.0f)), 0, 0, 0, 0, 0, 0, 0)
#endif
        ADD(LW(0), 20)
    END_LOOP
    SET_VALUE(LW(0), -220)
    LOOP(22)
#ifdef NONMATCHING
        CALL(evt_eff, 0, STRING(((char*)str_000002EC)), 2, -220, 5, LW(0), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
        CALL(evt_eff, 0, STRING(((char*)str_000002EC)), 2, 220, 5, LW(0), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_eff, 0, STRING(((char*)bom_01_str_000002EC)), 2, -220, 5, LW(0), FLOAT((1.0f)), 0, 0, 0, 0, 0, 0, 0)
        CALL(evt_eff, 0, STRING(((char*)bom_01_str_000002EC)), 2, 220, 5, LW(0), FLOAT((1.0f)), 0, 0, 0, 0, 0, 0, 0)
#endif
        ADD(LW(0), 20)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(open_hatch)
    CALL(evt_mapobj_get_position, LW(1), LW(10), LW(11), LW(12))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000350)), LW(10), LW(11), LW(12), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)bom_01_str_00000350)), LW(10), LW(11), LW(12), 0)
#endif
    SET_VALUE(LW(8), LW(0))
    SET_VALUE(LW(9), LW(1))
    SET_VALUE(LW(7), LW(2))
    CALL(evt_sub_intpl_msec_init, 1, 0, 180, 500)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    IF_INT_EQUAL(LW(7), 0)
        CALL(evt_mapobj_trans, 1, LW(9), 0, 0, LW(0))
#ifdef NONMATCHING
        MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
#endif
#ifndef NONMATCHING
        MULTIPLY_FLOAT(LW(0), FLOAT((-1.0f)))
#endif
        CALL(evt_mapobj_trans, 1, LW(8), 0, 0, LW(0))
        ELSE
        CALL(evt_mapobj_trans, 1, LW(9), LW(0), 0, 0)
#ifdef NONMATCHING
        MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
#endif
#ifndef NONMATCHING
        MULTIPLY_FLOAT(LW(0), FLOAT((-1.0f)))
#endif
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
#ifdef NONMATCHING
    (s32)/*((char*)str_00000368)*/((char*)str_00000368), (s32)((char*)str_00000370), (s32)/*((char*)str_000001B8)*/((char*)str_000001B8), (s32)((char*)str_00000380), (s32)/*((char*)str_000001C8)*/((char*)str_000001C8), (s32)((char*)str_00000390), (s32)/*((char*)str_000003A0)*/((char*)str_000003A0), (s32)((char*)str_000003AC),
#endif
#ifndef NONMATCHING
    (s32)/*((char*)bom_01_str_00000368)*/((char*)bom_01_str_00000368), (s32)((char*)bom_01_str_00000370), (s32)/*((char*)bom_01_str_000001B8)*/((char*)bom_01_str_000001B8), (s32)((char*)bom_01_str_00000380), (s32)/*((char*)bom_01_str_000001C8)*/((char*)bom_01_str_000001C8), (s32)((char*)bom_01_str_00000390), (s32)/*((char*)bom_01_str_000003A0)*/((char*)bom_01_str_000003A0), (s32)((char*)bom_01_str_000003AC),
#endif
};

static EVT_BEGIN(evt_taihou)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000003BC)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000003BC)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000003C8)), 32)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)bom_01_str_000003C8)), 32)
#endif
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos, 0, 10, 0, 500)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos, 0, 10, 500)
    CALL(evt_cam3d_evt_set, 0, 152, 555, 0, 57, 13, 1000, 11)
    WAIT_MS(1000)
#ifdef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000003CC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000003D8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000003E4)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000003EC)), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)bom_01_str_000003CC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)bom_01_str_000003D8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)bom_01_str_000003E4)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)bom_01_str_000003EC)), 1)
#endif
    CALL(evt_party_stop, 0)
    CALL(evt_mario_dispflag_onoff, 1, 2)
    WAIT_FRAMES(1)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000003F4)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_00000410)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)bom_01_str_000003F4)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)bom_01_str_00000410)))
#endif
    CALL_CHILD(PTR(party_damage_pose))
    CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000418)), LW(10), LW(11), LW(12), LW(9))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)bom_01_str_00000418)), LW(10), LW(11), LW(12), LW(9))
#endif
    CALL(evt_sub_intpl_msec_init, 12, 0, 20, 1000)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00000430)), LW(0), -5, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00000440)), LW(0), -5, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_trans, 1, STRING(((char*)bom_01_str_00000430)), LW(0), -5, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT((-1.0f)))
    CALL(evt_mapobj_trans, 1, STRING(((char*)bom_01_str_00000440)), LW(0), -5, 0)
#endif
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(evt_snd_sfxoff, LW(9))
    WAIT_MS(800)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000450)), LW(3), LW(4), LW(5), LW(6))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)bom_01_str_00000450)), LW(3), LW(4), LW(5), LW(6))
#endif
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
#ifdef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)str_00000410)))
#endif
#ifndef NONMATCHING
    CALL(evt_mario_set_pose, STRING(((char*)bom_01_str_00000410)))
#endif
    WAIT_FRAMES(1)
    CALL(evt_mario_cont_onoff, 0)
#ifdef NONMATCHING
    DEBUG_PUT_MSG(STRING(((char*)str_00000468)))
#endif
#ifndef NONMATCHING
    DEBUG_PUT_MSG(STRING(((char*)bom_01_str_00000468)))
#endif
    CALL(L_evt_party_vivian_tail, 0, 0)
#ifdef NONMATCHING
    CALL(evt_npc_status_onoff, 1, STRING(((char*)str_000003C8)), 2)
    CALL(evt_npc_move_position, STRING(((char*)str_000003C8)), -50, -40, 0, FLOAT(80.0f), 1)
    CALL(evt_npc_move_position, STRING(((char*)str_000003C8)), -55, -30, 0, FLOAT(80.0f), 1)
    CALL(evt_npc_move_position, STRING(((char*)str_000003C8)), -45, 80, 0, FLOAT(80.0f), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_status_onoff, 1, STRING(((char*)bom_01_str_000003C8)), 2)
    CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000003C8)), -50, -40, 0, FLOAT(80.0f), 1)
    CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000003C8)), -55, -30, 0, FLOAT(80.0f), 1)
    CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000003C8)), -45, 80, 0, FLOAT(80.0f), 1)
#endif
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)str_000003C8)), 0, 275, 0, FLOAT(80.0f), 1)
        CALL(evt_set_dir_to_target, STRING(((char*)str_000003C8)), STRING(((char*)str_0000047C)))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000003C8)), 0, 275, 0, FLOAT(80.0f), 1)
        CALL(evt_set_dir_to_target, STRING(((char*)bom_01_str_000003C8)), STRING(((char*)bom_01_str_0000047C)))
#endif
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
#ifdef NONMATCHING
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000003C8)), 32768)
    CALL(evt_npc_set_ry, STRING(((char*)str_000003C8)), 90)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000484)), 0, STRING(((char*)str_000003C8)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000490)), 0, STRING(((char*)str_000001AC)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)bom_01_str_000003C8)), 32768)
    CALL(evt_npc_set_ry, STRING(((char*)bom_01_str_000003C8)), 90)
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000484)), 0, STRING(((char*)bom_01_str_000003C8)))
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000490)), 0, STRING(((char*)bom_01_str_000001AC)))
#endif
    SET_INT_READ_ADDR(PTR(oh_data))
    LOOP(4)
        READ_INT2(LW(0), LW(1))
        BEGIN_INLINE_EVENT
#ifdef NONMATCHING
            CALL(evt_set_dir_to_target, LW(0), STRING(((char*)str_0000047C)))
#endif
#ifndef NONMATCHING
            CALL(evt_set_dir_to_target, LW(0), STRING(((char*)bom_01_str_0000047C)))
#endif
            CALL(evt_msg_print, 0, LW(1), 0, LW(0))
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            CALL(evt_npc_get_position, LW(0), LW(10), LW(11), LW(12))
#ifdef NONMATCHING
            CALL(evt_npc_jump_position_nohit, LW(0), LW(10), LW(11), LW(12), 300, FLOAT(20.0f))
#endif
#ifndef NONMATCHING
            CALL(evt_npc_jump_position_nohit, LW(0), LW(10), LW(11), LW(12), 300, FLOAT((20.0f)))
#endif
        END_INLINE_EVENT
        WAIT_MS(300)
    END_LOOP
    WAIT_MS(500)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000004A0)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000004A0)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
    SET_VALUE(GF(0), 0)
#ifdef NONMATCHING
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_000001AC)), 512)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_000001B8)), 512)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_000001C8)), 512)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)bom_01_str_000001AC)), 512)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)bom_01_str_000001B8)), 512)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)bom_01_str_000001C8)), 512)
#endif
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000004AC)), 0, STRING(((char*)str_000001AC)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000004AC)), 0, STRING(((char*)bom_01_str_000001AC)))
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_get_position, STRING(((char*)str_000001AC)), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000001AC)), LW(0), LW(1), LW(2), 300, FLOAT(20.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_get_position, STRING(((char*)bom_01_str_000001AC)), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position_nohit, STRING(((char*)bom_01_str_000001AC)), LW(0), LW(1), LW(2), 300, FLOAT((20.0f)))
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000004AC)), 0, STRING(((char*)str_000001B8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000004AC)), 0, STRING(((char*)bom_01_str_000001B8)))
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_get_position, STRING(((char*)str_000001B8)), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000001B8)), LW(0), LW(1), LW(2), 300, FLOAT(20.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_get_position, STRING(((char*)bom_01_str_000001B8)), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position_nohit, STRING(((char*)bom_01_str_000001B8)), LW(0), LW(1), LW(2), 300, FLOAT((20.0f)))
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_get_position, STRING(((char*)str_000001C8)), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000001C8)), LW(0), LW(1), LW(2), 300, FLOAT(20.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_npc_get_position, STRING(((char*)bom_01_str_000001C8)), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position_nohit, STRING(((char*)bom_01_str_000001C8)), LW(0), LW(1), LW(2), 300, FLOAT((20.0f)))
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000004AC)), 0, STRING(((char*)str_000001C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000004AC)), 0, STRING(((char*)bom_01_str_000001C8)))
#endif
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
#ifdef NONMATCHING
        CALL(evt_npc_status_onoff, 1, STRING(((char*)str_000001AC)), 2)
        CALL(evt_npc_move_position, STRING(((char*)str_000001AC)), -50, -80, 0, FLOAT(100.0f), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_status_onoff, 1, STRING(((char*)bom_01_str_000001AC)), 2)
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001AC)), -50, -80, 0, FLOAT((100.0f)), 1)
#endif
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_status_onoff, 1, STRING(((char*)str_000001B8)), 2)
        CALL(evt_npc_move_position, STRING(((char*)str_000001B8)), 0, -80, 0, FLOAT(100.0f), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_status_onoff, 1, STRING(((char*)bom_01_str_000001B8)), 2)
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001B8)), 0, -80, 0, FLOAT((100.0f)), 1)
#endif
        SET_VALUE(GF(1), 1)
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_status_onoff, 1, STRING(((char*)str_000001C8)), 2)
        CALL(evt_npc_move_position, STRING(((char*)str_000001C8)), 50, -80, 0, FLOAT(100.0f), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_status_onoff, 1, STRING(((char*)bom_01_str_000001C8)), 2)
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001C8)), 50, -80, 0, FLOAT((100.0f)), 1)
#endif
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
#ifdef NONMATCHING
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000001AC)), 512)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000001B8)), 512)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000001C8)), 512)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)bom_01_str_000001AC)), 512)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)bom_01_str_000001B8)), 512)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)bom_01_str_000001C8)), 512)
#endif
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)str_000001AC)), -50, -200, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)str_000001AC)), -35, -260, 0, FLOAT(80.0f), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001AC)), -50, -200, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001AC)), -35, -260, 0, FLOAT(80.0f), 1)
#endif
    END_INLINE_EVENT
    WAIT_MS(400)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)str_000001B8)), -50, -80, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)str_000001B8)), -55, -225, 0, FLOAT(80.0f), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001B8)), -50, -80, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001B8)), -55, -225, 0, FLOAT(80.0f), 1)
#endif
    END_INLINE_EVENT
    WAIT_MS(400)
#ifdef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)str_000001C8)), -50, -80, 0, FLOAT(80.0f), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001C8)), -50, -80, 0, FLOAT(80.0f), 1)
#endif
    CALL(evt_cam3d_evt_set, 0, 152, 108, 0, 57, -432, 0, 11)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)str_000001C8)), -70, -180, 0, FLOAT(80.0f), 1)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001C8)), -70, -180, 0, FLOAT(80.0f), 1)
#endif
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
#ifdef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)str_000001AC)), 0, -320, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)str_000001AC)), 35, -330, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)str_000001AC)), 80, -380, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000001AC)), 70, 30, -435, 300, FLOAT(20.0f))
        CALL(evt_npc_move_position, STRING(((char*)str_000001AC)), 40, -445, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000001AC)), 0, 40, -430, 300, FLOAT(20.0f))
        CALL(evt_npc_set_ry, STRING(((char*)str_000001AC)), 90)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001AC)), 0, -320, 0, FLOAT((70.0f)), 1)
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001AC)), 35, -330, 0, FLOAT((70.0f)), 1)
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001AC)), 80, -380, 0, FLOAT((70.0f)), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)bom_01_str_000001AC)), 70, 30, -435, 300, FLOAT((20.0f)))
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001AC)), 40, -445, 0, FLOAT((70.0f)), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)bom_01_str_000001AC)), 0, 40, -430, 300, FLOAT((20.0f)))
        CALL(evt_npc_set_ry, STRING(((char*)bom_01_str_000001AC)), 90)
#endif
    END_INLINE_EVENT
    WAIT_MS(400)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)str_000001B8)), 0, -320, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)str_000001B8)), 35, -330, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)str_000001B8)), 80, -380, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)str_000001B8)), 80, -415, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)str_000001B8)), 45, -415, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000001B8)), -20, 15, -390, 300, FLOAT(20.0f))
        CALL(evt_npc_set_ry, STRING(((char*)str_000001B8)), 315)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001B8)), 0, -320, 0, FLOAT((70.0f)), 1)
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001B8)), 35, -330, 0, FLOAT((70.0f)), 1)
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001B8)), 80, -380, 0, FLOAT((70.0f)), 1)
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001B8)), 80, -415, 0, FLOAT((70.0f)), 1)
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001B8)), 45, -415, 0, FLOAT((70.0f)), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)bom_01_str_000001B8)), -20, 15, -390, 300, FLOAT((20.0f)))
        CALL(evt_npc_set_ry, STRING(((char*)bom_01_str_000001B8)), 315)
#endif
    END_INLINE_EVENT
    WAIT_MS(400)
#ifdef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)str_000001C8)), 0, -320, 0, FLOAT(70.0f), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001C8)), 0, -320, 0, FLOAT((70.0f)), 1)
#endif
    SET_VALUE(GF(0), 0)
#ifdef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)str_000001C8)), 35, -330, 0, FLOAT(70.0f), 1)
    CALL(evt_npc_move_position, STRING(((char*)str_000001C8)), 80, -380, 0, FLOAT(70.0f), 1)
    CALL(evt_npc_move_position, STRING(((char*)str_000001C8)), 80, -415, 0, FLOAT(70.0f), 1)
    CALL(evt_npc_move_position, STRING(((char*)str_000001C8)), 45, -415, 0, FLOAT(70.0f), 1)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000001C8)), 20, 15, -390, 300, FLOAT(20.0f))
    CALL(evt_npc_set_ry, STRING(((char*)str_000001C8)), 90)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001C8)), 35, -330, 0, FLOAT((70.0f)), 1)
    CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001C8)), 80, -380, 0, FLOAT((70.0f)), 1)
    CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001C8)), 80, -415, 0, FLOAT((70.0f)), 1)
    CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000001C8)), 45, -415, 0, FLOAT((70.0f)), 1)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)bom_01_str_000001C8)), 20, 15, -390, 300, FLOAT((20.0f)))
    CALL(evt_npc_set_ry, STRING(((char*)bom_01_str_000001C8)), 90)
#endif
    CALL(evt_cam3d_evt_set, -160, 125, -100, 10, 55, -427, 1000, 11)
    WAIT_MS(1000)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001AC)), STRING(((char*)str_000001B8)))
    CALL(evt_msg_print, 0, STRING(((char*)str_000004B8)), 0, STRING(((char*)str_000001AC)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)bom_01_str_000001AC)), STRING(((char*)bom_01_str_000001B8)))
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000004B8)), 0, STRING(((char*)bom_01_str_000001AC)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001B8)), STRING(((char*)str_000001AC)))
    CALL(evt_msg_print, 0, STRING(((char*)str_000004C4)), 0, STRING(((char*)str_000001B8)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)bom_01_str_000001B8)), STRING(((char*)bom_01_str_000001AC)))
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000004C4)), 0, STRING(((char*)bom_01_str_000001B8)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_npc_reverse_ry, STRING(((char*)str_000001B8)))
    CALL(evt_snd_sfxon, STRING(((char*)str_000004D0)), 0)
    CALL(evt_snd_sfxon, STRING(((char*)str_000004EC)), LW(10))
    CALL(evt_map_playanim, STRING(((char*)str_00000508)), 1, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_reverse_ry, STRING(((char*)bom_01_str_000001B8)))
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000004D0)), 0)
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000004EC)), LW(10))
    CALL(evt_map_playanim, STRING(((char*)bom_01_str_00000508)), 1, 0)
#endif
    WAIT_MS(1000)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001B8)), STRING(((char*)str_000001AC)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000510)), 0, STRING(((char*)str_000001B8)))
    CALL(evt_npc_set_ry, STRING(((char*)str_000001B8)), 315)
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)bom_01_str_000001B8)), STRING(((char*)bom_01_str_000001AC)))
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000510)), 0, STRING(((char*)bom_01_str_000001B8)))
    CALL(evt_npc_set_ry, STRING(((char*)bom_01_str_000001B8)), 315)
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001AC)), STRING(((char*)str_000001C8)))
    CALL(evt_msg_print, 0, STRING(((char*)str_0000051C)), 0, STRING(((char*)str_000001AC)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)bom_01_str_000001AC)), STRING(((char*)bom_01_str_000001C8)))
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_0000051C)), 0, STRING(((char*)bom_01_str_000001AC)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001C8)), STRING(((char*)str_000001AC)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000528)), 0, STRING(((char*)str_000001C8)))
#endif
#ifndef NONMATCHING
    CALL(evt_set_dir_to_target, STRING(((char*)bom_01_str_000001C8)), STRING(((char*)bom_01_str_000001AC)))
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000528)), 0, STRING(((char*)bom_01_str_000001C8)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_npc_reverse_ry, STRING(((char*)str_000001C8)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_reverse_ry, STRING(((char*)bom_01_str_000001C8)))
#endif
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_cam3d_evt_set, 200, 350, 1224, 200, 125, 250, 0, 11)
    CALL_CHILD(PTR(cam_outside))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_00000534)), LW(10))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_00000534)), LW(10))
#endif
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 1, 0, 0, 0)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_0000054C)), 0, STRING(((char*)str_000001AC)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_0000054C)), 0, STRING(((char*)bom_01_str_000001AC)))
#endif
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
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000004EC)), LW(10))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000004EC)), LW(10))
#endif
    CALL_CHILD(PTR(cam_inside))
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000558)), 0, STRING(((char*)str_000001AC)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000558)), 0, STRING(((char*)bom_01_str_000001AC)))
#endif
    WAIT_MS(300)
    CALL(evt_snd_sfxoff, LW(10))
#ifdef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000564)))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_bgmon, 512, STRING(((char*)bom_01_str_00000564)))
#endif
    CALL(evt_cam3d_evt_set, 0, 350, 1224, 0, 125, 250, 0, 11)
    CALL_CHILD(PTR(cam_outside))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 283, 932, 0, 125, 250, 3000, 11)
    WAIT_MS(1500)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_0000057C)), LW(7))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_0000057C)), LW(7))
#endif
    SPAWN_EVENT_GET_ID(PTR(gamen_shake), LW(9))
    WAIT_MS(1500)
    SPAWN_EVENT(PTR(effect_1))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_00000594)), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_00000594)), 0)
#endif
    SPAWN_EVENT(PTR(gamen_shake2))
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000003EC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000005AC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000003CC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000005B4)), 1)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000003CC)), 0, FLOAT(0.0f), 0)
    CALL(evt_snd_sfxon, STRING(((char*)str_000005C0)), LW(8))
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)bom_01_str_000003EC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)bom_01_str_000005AC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)bom_01_str_000003CC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)bom_01_str_000005B4)), 1)
    CALL(evt_mapobj_trans, 1, STRING(((char*)bom_01_str_000003CC)), 0, FLOAT((0.0f)), 0)
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000005C0)), LW(8))
#endif
    CALL(evt_sub_intpl_msec_init, 0, 0, -20, 1000)
    LABEL(3)
    CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000005D8)), 0, LW(0), 0)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000005E8)), 0, LW(0), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_trans, 1, STRING(((char*)bom_01_str_000005D8)), 0, LW(0), 0)
    CALL(evt_mapobj_trans, 1, STRING(((char*)bom_01_str_000005E8)), 0, LW(0), 0)
#endif
    ADD(LW(0), -5)
#ifdef NONMATCHING
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00000440)), -20, LW(0), 0)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00000430)), 20, LW(0), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_trans, 1, STRING(((char*)bom_01_str_00000440)), -20, LW(0), 0)
    CALL(evt_mapobj_trans, 1, STRING(((char*)bom_01_str_00000430)), 20, LW(0), 0)
#endif
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(3)
    END_IF
    CALL(evt_snd_sfxoff, LW(8))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000005F8)), LW(8))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000005F8)), LW(8))
#endif
    CALL(evt_sub_intpl_msec_init, 0, 0, 170, 3000)
    LABEL(4)
    CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000005E8)), LW(0), -20, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000005D8)), LW(0), -20, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_trans, 1, STRING(((char*)bom_01_str_000005E8)), LW(0), -20, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT((-1.0f)))
    CALL(evt_mapobj_trans, 1, STRING(((char*)bom_01_str_000005D8)), LW(0), -20, 0)
#endif
    ADD(LW(0), -20)
#ifdef NONMATCHING
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00000440)), LW(0), -25, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00000430)), LW(0), -25, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_trans, 1, STRING(((char*)bom_01_str_00000440)), LW(0), -25, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT((-1.0f)))
    CALL(evt_mapobj_trans, 1, STRING(((char*)bom_01_str_00000430)), LW(0), -25, 0)
#endif
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(4)
    END_IF
    CALL(evt_snd_sfxoff, LW(8))
    SPAWN_EVENT(PTR(gamen_shake2))
    WAIT_MS(600)
    DELETE_EVENT(LW(9))
    CALL(evt_snd_sfxoff, LW(7))
#ifdef NONMATCHING
    CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.0f), 100)
    CALL(evt_snd_sfxon, STRING(((char*)str_000004EC)), LW(8))
#endif
#ifndef NONMATCHING
    CALL(evt_cam_shake, 4, FLOAT((0.0f)), FLOAT((0.0f)), 100)
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000004EC)), LW(8))
#endif
    CALL_CHILD(PTR(cam_inside))
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000610)), 0, STRING(((char*)str_000001AC)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000610)), 0, STRING(((char*)bom_01_str_000001AC)))
#endif
    WAIT_MS(300)
    CALL(evt_snd_sfxoff, LW(8))
    CALL(evt_cam3d_evt_set, 0, 283, 932, 0, 125, 250, 0, 11)
    CALL_CHILD(PTR(cam_outside))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -200, 734, 684, -10, 50, 63, 2800, 11)
    WAIT_MS(1800)
#ifdef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)str_0000061C)))
    SET_VALUE(LW(1), STRING(((char*)str_0000062C)))
#endif
#ifndef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)bom_01_str_0000061C)))
    SET_VALUE(LW(1), STRING(((char*)bom_01_str_0000062C)))
#endif
    SET_VALUE(LW(2), 0)
    SPAWN_EVENT(PTR(open_hatch))
    WAIT_MS(400)
#ifdef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)str_0000063C)))
    SET_VALUE(LW(1), STRING(((char*)str_0000064C)))
#endif
#ifndef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)bom_01_str_0000063C)))
    SET_VALUE(LW(1), STRING(((char*)bom_01_str_0000064C)))
#endif
    SET_VALUE(LW(2), 1)
    SPAWN_EVENT(PTR(open_hatch))
    WAIT_MS(400)
#ifdef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)str_0000065C)))
    SET_VALUE(LW(1), STRING(((char*)str_0000066C)))
#endif
#ifndef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)bom_01_str_0000065C)))
    SET_VALUE(LW(1), STRING(((char*)bom_01_str_0000066C)))
#endif
    SET_VALUE(LW(2), 0)
    SPAWN_EVENT(PTR(open_hatch))
    WAIT_MS(400)
#ifdef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)str_0000067C)))
    SET_VALUE(LW(1), STRING(((char*)str_0000068C)))
#endif
#ifndef NONMATCHING
    SET_VALUE(LW(0), STRING(((char*)bom_01_str_0000067C)))
    SET_VALUE(LW(1), STRING(((char*)bom_01_str_0000068C)))
#endif
    SET_VALUE(LW(2), 1)
    SPAWN_EVENT(PTR(open_hatch))
    WAIT_MS(400)
    WAIT_MS(1000)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000004EC)), LW(8))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000004EC)), LW(8))
#endif
    CALL_CHILD(PTR(cam_inside2))
    WAIT_MS(300)
    WAIT_MS(1000)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_0000069C)), 0, STRING(((char*)str_000001AC)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_0000069C)), 0, STRING(((char*)bom_01_str_000001AC)))
#endif
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
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000006A8)), LW(8))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000006A8)), LW(8))
#endif
    CALL(evt_sub_intpl_msec_init, 1, 0, 1600, 11250)
    LABEL(5)
    CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000006BC)), 0, LW(0), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_trans, 1, STRING(((char*)bom_01_str_000006BC)), 0, LW(0), 0)
#endif
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(5)
    END_IF
    SPAWN_EVENT(PTR(effect_1))
    CALL(evt_snd_sfxoff, LW(8))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000006C8)), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000006C8)), 0)
#endif
    DELETE_EVENT(LW(9))
    SPAWN_EVENT(PTR(gamen_shake2))
    WAIT_MS(2000)
#ifdef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000005B4)), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)bom_01_str_000005B4)), 1)
#endif
    CALL(evt_cam3d_evt_set, 1500, 100, 2539, 0, 650, 0, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_cam3d_evt_set, -1500, 100, 2539, 0, 650, 0, 5000, 11)
    WAIT_MS(5000)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000004EC)), LW(10))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000004EC)), LW(10))
#endif
    CALL_CHILD(PTR(cam_inside))
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000006E0)), 0, STRING(((char*)str_000001AC)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000006E0)), 0, STRING(((char*)bom_01_str_000001AC)))
#endif
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
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000006EC)), LW(8))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000006EC)), LW(8))
#endif
    SPAWN_EVENT_GET_ID(PTR(gamen_shake), LW(9))
    CALL(evt_sub_intpl_msec_init, 11, 0, -500, 3000)
    LABEL(6)
    CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
    DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000002DC)), 0, 0, LW(0))
#endif
#ifndef NONMATCHING
    DIVIDE_FLOAT(LW(0), FLOAT((10.0f)))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)bom_01_str_000002DC)), 0, 0, LW(0))
#endif
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(6)
    END_IF
    DELETE_EVENT(LW(9))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_00000704)), 0)
    CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.0f), 500)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_00000704)), 0)
    CALL(evt_cam_shake, 4, FLOAT((0.0f)), FLOAT((0.0f)), 500)
#endif
    CALL(evt_snd_sfxoff, LW(8))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000004EC)), LW(8))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000004EC)), LW(8))
#endif
    SET_VALUE(GW(10), 70)
    SPAWN_EVENT_GET_ID(PTR(evt_depth), LW(9))
    CALL(sight_dir, 4)
    CALL_CHILD(PTR(cam_outside))
    CALL(evt_cam3d_evt_set, 400, 151, -171, 400, 62, -676, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(300)
    CALL(evt_msg_toge, 1, 0, 0, 0)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_0000071C)), 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_0000071C)), 0, 0)
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00000728)), 1)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00000728)), 400, -738, -676)
    CALL(evt_mapobj_scale, 1, STRING(((char*)str_00000728)), FLOAT(0.7998047f), FLOAT(0.7998047f), FLOAT(0.7998047f))
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)bom_01_str_00000728)), 1)
    CALL(evt_mapobj_trans, 1, STRING(((char*)bom_01_str_00000728)), 400, -738, -676)
    CALL(evt_mapobj_scale, 1, STRING(((char*)bom_01_str_00000728)), FLOAT(0.7998047f), FLOAT(0.7998047f), FLOAT(0.7998047f))
#endif
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
#ifdef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000728)), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)bom_01_str_00000728)), 1)
#endif
    CALL_CHILD(PTR(cam_inside))
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000730)), 0, STRING(((char*)str_000001AC)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000730)), 0, STRING(((char*)bom_01_str_000001AC)))
#endif
    WAIT_MS(300)
    CALL(evt_snd_sfxoff, LW(8))
    CALL(evt_cam3d_evt_set, -1500, 100, 2539, 0, 650, 0, 0, 11)
    CALL_CHILD(PTR(cam_outside))
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000006EC)), LW(8))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000006EC)), LW(8))
#endif
    SPAWN_EVENT_GET_ID(PTR(gamen_shake), LW(9))
    CALL(evt_sub_intpl_msec_init, 11, -500, -400, 1000)
    LABEL(7)
    CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
    DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000002DC)), 0, 0, LW(0))
#endif
#ifndef NONMATCHING
    DIVIDE_FLOAT(LW(0), FLOAT((10.0f)))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)bom_01_str_000002DC)), 0, 0, LW(0))
#endif
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(7)
    END_IF
    DELETE_EVENT(LW(9))
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_00000704)), 0)
    CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.0f), 500)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_00000704)), 0)
    CALL(evt_cam_shake, 4, FLOAT((0.0f)), FLOAT((0.0f)), 500)
#endif
    CALL(evt_snd_sfxoff, LW(8))
    CALL(evt_msg_toge, 1, 0, 0, 0)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_0000073C)), 0, STRING(((char*)str_000001AC)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_0000073C)), 0, STRING(((char*)bom_01_str_000001AC)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_00000748)), LW(8))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_00000748)), LW(8))
#endif
    CALL(evt_sub_intpl_msec_init, 11, 0, -1200, 1000)
    LABEL(8)
    CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
    DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000760)), 0, LW(0), 0)
#endif
#ifndef NONMATCHING
    DIVIDE_FLOAT(LW(0), FLOAT((10.0f)))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)bom_01_str_00000760)), 0, LW(0), 0)
#endif
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(8)
    END_IF
    CALL(evt_snd_sfxoff, LW(8))
    CALL(evt_cam3d_evt_set, 21, 175, 781, 9, 42, 265, 0, 11)
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000768)), 0, STRING(((char*)str_00000774)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000768)), 0, STRING(((char*)bom_01_str_00000774)))
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_0000077C)), LW(8))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_0000077C)), LW(8))
#endif
    CALL_CHILD(PTR(evt_bom1000))
    WAIT_MS(5000)
    CALL(evt_snd_sfxoff, LW(8))
    CALL(evt_cam3d_evt_set, -120, 697, 788, 39, 556, 265, 0, 11)
    WAIT_MS(5000)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000004EC)), LW(10))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000004EC)), LW(10))
#endif
    CALL(bom_flag, 1, 1)
    CALL_CHILD(PTR(cam_inside2))
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000794)), 0, STRING(((char*)str_000001AC)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000794)), 0, STRING(((char*)bom_01_str_000001AC)))
#endif
    WAIT_MS(300)
    CALL(bom_flag, 0, 1)
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_cam3d_evt_set, -120, 697, 788, 39, 556, 265, 0, 11)
    CALL_CHILD(PTR(cam_outside))
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000007A0)), LW(7))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000007A0)), LW(7))
#endif
    CALL(evt_msg_toge, 2, 180, 520, 100)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000007BC)), 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000007BC)), 0, 0)
#endif
    CALL(evt_msg_toge, 2, 100, 400, 95)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000007CC)), 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000007CC)), 0, 0)
#endif
    CALL(evt_msg_toge, 2, 10, 475, 75)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000007DC)), 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000007DC)), 0, 0)
#endif
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
#ifdef NONMATCHING
        CALL(evt_snd_sfxon, STRING(((char*)str_000007EC)), LW(8))
#endif
#ifndef NONMATCHING
        CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000007EC)), LW(8))
#endif
        CALL(evt_sub_intpl_msec_init, 11, -1200, 0, 3000)
        LABEL(9)
        CALL(evt_sub_intpl_msec_get_value)
#ifdef NONMATCHING
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000760)), 0, LW(0), 0)
#endif
#ifndef NONMATCHING
        DIVIDE_FLOAT(LW(0), FLOAT((10.0f)))
        CALL(evt_mapobj_rotate, 1, STRING(((char*)bom_01_str_00000760)), 0, LW(0), 0)
#endif
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(9)
        END_IF
        CALL(evt_snd_sfxoff, LW(8))
        CALL(evt_snd_sfxoff, LW(7))
    END_INLINE_EVENT
    WAIT_MS(500)
    CALL(evt_msg_toge, 2, 180, 520, 100)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000804)), 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000804)), 0, 0)
#endif
    CALL(evt_msg_toge, 2, 100, 400, 95)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000814)), 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000814)), 0, 0)
#endif
    CALL(evt_msg_toge, 2, 10, 475, 75)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000824)), 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000824)), 0, 0)
#endif
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_npc_reverse_ry, STRING(((char*)str_00000774)))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_reverse_ry, STRING(((char*)bom_01_str_00000774)))
#endif
    CALL(bom_flag, 1, 1)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_000004EC)), LW(10))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_000004EC)), LW(10))
#endif
    CALL_CHILD(PTR(cam_inside))
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000834)), 0, STRING(((char*)str_000001AC)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000834)), 0, STRING(((char*)bom_01_str_000001AC)))
#endif
    WAIT_MS(300)
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_cam3d_evt_set, 21, 175, 781, 9, 42, 265, 0, 11)
    CALL_CHILD(PTR(cam_outside))
    WAIT_MS(300)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_00000840)), 0, STRING(((char*)str_00000774)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000840)), 0, STRING(((char*)bom_01_str_00000774)))
#endif
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
#ifdef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_0000084C)), 1)
#endif
#ifndef NONMATCHING
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)bom_01_str_0000084C)), 1)
#endif
    WAIT_FRAMES(1)
#ifdef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000854)), 200, 0, -650, 0)
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000870)), 200, 0, -650, LW(4))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000888)), 200, 0, -650, LW(5))
    SET_FLOAT_VALUE(LW(6), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon_3d, STRING(((char*)bom_01_str_00000854)), 200, 0, -650, 0)
    CALL(evt_snd_sfxon_3d, STRING(((char*)bom_01_str_00000870)), 200, 0, -650, LW(4))
    CALL(evt_snd_sfxon_3d, STRING(((char*)bom_01_str_00000888)), 200, 0, -650, LW(5))
    SET_FLOAT_VALUE(LW(6), FLOAT((0.0f)))
#endif
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
#ifdef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)str_0000089C)), 0)
    CALL(evt_eff64, 0, STRING(((char*)str_000008B4)), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
#endif
#ifndef NONMATCHING
    CALL(evt_snd_sfxon, STRING(((char*)bom_01_str_0000089C)), 0)
    CALL(evt_eff64, 0, STRING(((char*)bom_01_str_000008B4)), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
#endif
    WAIT_MS(2000)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_msg_toge, 2, 340, 200, -590)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000008C4)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000008C4)), 0, 0)
#endif
        CALL(evt_msg_toge, 2, 400, 160, -590)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000008D0)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000008D0)), 0, 0)
#endif
        CALL(evt_msg_toge, 2, 373, 135, -590)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000008DC)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000008DC)), 0, 0)
#endif
    END_INLINE_EVENT
    CALL(bom_flag, 0, 1)
    CALL(bom_fall)
    WAIT_MS(6000)
    CALL(evt_ext_reset)
#ifdef NONMATCHING
    CALL(evt_npc_set_ry, STRING(((char*)str_00000774)), 90)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00000774)), 32768)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_ry, STRING(((char*)bom_01_str_00000774)), 90)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)bom_01_str_00000774)), 32768)
#endif
    CALL(evt_cam3d_evt_set, -60, 26, 493, 22, 33, 257, 0, 11)
    WAIT_MS(2000)
#ifdef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)str_000008E8)), 0, STRING(((char*)str_00000774)))
#endif
#ifndef NONMATCHING
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000008E8)), 0, STRING(((char*)bom_01_str_00000774)))
#endif
    CALL(evt_snd_bgmoff_f, 512, 2000)
    WAIT_MS(300)
    WAIT_MS(2000)
    CALL(evt_pouch_remove_item, 82, LW(0))
#ifdef NONMATCHING
    CALL(evt_bero_mapchange, STRING(((char*)str_000008F4)), 0)
#endif
#ifndef NONMATCHING
    CALL(evt_bero_mapchange, STRING(((char*)bom_01_str_000008F4)), 0)
#endif
    RETURN
EVT_END()

static EVT_BEGIN(init_soncho)
    SWITCH(GSW(0))
        CASE_GREATER_OR_EQUAL(356)
#ifdef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), -15, 0, -35)
#endif
#ifndef NONMATCHING
        CALL(evt_npc_set_position, STRING(((char*)bom_01_str_000003C8)), -15, 0, -35)
#endif
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_soncho)
    SWITCH(GSW(0))
        CASE_LESS(357)
        CALL_CHILD(PTR(evt_taihou))
        CASE_LESS_OR_EQUAL(402)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000008FC)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000008FC)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000910)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000910)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_nitoro)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), -120, 0, -220)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_000003C8)), -120, 0, -220)
#endif
    RETURN
EVT_END()

EVT_BEGIN(talk_nitoro)
    SWITCH(GSW(0))
        CASE_LESS(349)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000924)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000924)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS(356)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000934)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000934)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS(357)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000940)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000940)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS_OR_EQUAL(402)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000950)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000950)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_0000095C)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_0000095C)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_pentrit)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), -150, 0, 130)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_000003C8)), -150, 0, 130)
#endif
    RETURN
EVT_END()

EVT_BEGIN(talk_pentrit)
    SWITCH(GSW(0))
        CASE_LESS(349)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_0000096C)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_0000096C)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS(356)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_0000097C)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_0000097C)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS(357)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000988)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000988)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS_OR_EQUAL(402)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000998)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000998)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000009A4)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000009A4)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_surary)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), 152, 0, -188)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_000003C8)), 152, 0, -188)
#endif
    RETURN
EVT_END()

EVT_BEGIN(talk_surary)
    SWITCH(GSW(0))
        CASE_LESS(349)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000009B4)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000009B4)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS(356)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000009C4)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000009C4)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS(357)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000009D0)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000009D0)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS_OR_EQUAL(402)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000009E0)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000009E0)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000009EC)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000009EC)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_murabito_d)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), 175, 0, 210)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_000003C8)), 175, 0, 210)
#endif
    RETURN
EVT_END()

EVT_BEGIN(talk_murabito_d)
    SWITCH(GSW(0))
        CASE_LESS(349)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_000009FC)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_000009FC)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS(356)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A0C)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000A0C)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS(357)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A18)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000A18)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS_OR_EQUAL(402)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A28)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000A28)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A34)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000A34)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(init_murabito_e)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), -200, 0, -80)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_000003C8)), -200, 0, -80)
#endif
    RETURN
EVT_END()

static EVT_BEGIN(talk_murabito_e)
    SWITCH(GSW(0))
        CASE_LESS(349)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A44)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000A44)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS(357)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A54)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000A54)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A60)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000A60)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(init_murabito_f)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), -150, 0, -80)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_000003C8)), -150, 0, -80)
#endif
    RETURN
EVT_END()

static EVT_BEGIN(talk_murabito_f)
    SWITCH(GSW(0))
        CASE_LESS(349)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A6C)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000A6C)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS(357)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A7C)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000A7C)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A88)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000A88)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(init_murabito_g)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), -100, 0, -80)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_000003C8)), -100, 0, -80)
#endif
    RETURN
EVT_END()

static EVT_BEGIN(talk_murabito_g)
    SWITCH(GSW(0))
        CASE_LESS(349)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A94)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000A94)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS(357)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000AA4)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000AA4)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000AB0)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000AB0)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(init_murabito_h)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), -50, 0, -80)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_000003C8)), -50, 0, -80)
#endif
    RETURN
EVT_END()

static EVT_BEGIN(talk_murabito_h)
    SWITCH(GSW(0))
        CASE_LESS(349)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000ABC)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000ABC)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS(357)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000ACC)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000ACC)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000AD8)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000AD8)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(init_murabito_i)
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), 0, 0, -80)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_000003C8)), 0, 0, -80)
#endif
    RETURN
EVT_END()

static EVT_BEGIN(talk_murabito_i)
    SWITCH(GSW(0))
        CASE_LESS(349)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000AE4)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000AE4)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_LESS(357)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000AF4)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000AF4)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B00)), 0, STRING(((char*)str_000003C8)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000B00)), 0, STRING(((char*)bom_01_str_000003C8)))
#endif
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
#ifdef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), 50, 0, -100)
#endif
#ifndef NONMATCHING
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_000003C8)), 50, 0, -100)
#endif
END_IF
RETURN
EVT_END()

static EVT_BEGIN(talk_white)
    SWITCH(GSW(0))
        CASE_LESS(357)
        IF_INT_EQUAL(GSWF(3874), 0)
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_00000B0C)), 0, 0)
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000B0C)), 0, 0)
#endif
            ELSE
#ifdef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)str_00000B1C)), 0, 0)
#endif
#ifndef NONMATCHING
            CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000B1C)), 0, 0)
#endif
        END_IF
        CASE_LESS_OR_EQUAL(402)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B2C)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000B2C)), 0, 0)
#endif
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B3C)), 0, 0)
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000B3C)), 0, 0)
#endif
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(musume_talk)
    SWITCH(GSW(0))
        CASE_LESS(354)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B4C)), 0, STRING(((char*)str_00000B60)))
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B6C)), 0, STRING(((char*)str_00000B80)))
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B8C)), 0, STRING(((char*)str_00000BA0)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000B4C)), 0, STRING(((char*)bom_01_str_00000B60)))
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000B6C)), 0, STRING(((char*)bom_01_str_00000B80)))
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000B8C)), 0, STRING(((char*)bom_01_str_00000BA0)))
#endif
        CASE_LESS(356)
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BAC)), 0, STRING(((char*)str_00000B60)))
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BC0)), 0, STRING(((char*)str_00000B80)))
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BD4)), 0, STRING(((char*)str_00000BA0)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000BAC)), 0, STRING(((char*)bom_01_str_00000B60)))
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000BC0)), 0, STRING(((char*)bom_01_str_00000B80)))
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000BD4)), 0, STRING(((char*)bom_01_str_00000BA0)))
#endif
        CASE_DEFAULT
#ifdef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BE8)), 0, STRING(((char*)str_00000B60)))
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BFC)), 0, STRING(((char*)str_00000B80)))
        CALL(evt_msg_print, 0, STRING(((char*)str_00000C10)), 0, STRING(((char*)str_00000BA0)))
#endif
#ifndef NONMATCHING
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000BE8)), 0, STRING(((char*)bom_01_str_00000B60)))
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000BFC)), 0, STRING(((char*)bom_01_str_00000B80)))
        CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000C10)), 0, STRING(((char*)bom_01_str_00000BA0)))
#endif
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(musume_a_entry)
#ifdef NONMATCHING
    CALL(evt_npc_entry, STRING(((char*)str_00000B60)), STRING(((char*)str_00000C24)))
    CALL(evt_npc_set_tribe, STRING(((char*)str_00000B60)), STRING(((char*)str_00000C30)))
    CALL(evt_npc_set_position, STRING(((char*)str_00000B60)), 370, 5, -120)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00000B60)), 1536)
    CALL(evt_npc_change_interrupt, STRING(((char*)str_00000B60)), 6, PTR(musume_talk))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_entry, STRING(((char*)bom_01_str_00000B60)), STRING(((char*)bom_01_str_00000C24)))
    CALL(evt_npc_set_tribe, STRING(((char*)bom_01_str_00000B60)), STRING(((char*)bom_01_str_00000C30)))
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_00000B60)), 370, 5, -120)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)bom_01_str_00000B60)), 1536)
    CALL(evt_npc_change_interrupt, STRING(((char*)bom_01_str_00000B60)), 6, PTR(musume_talk))
#endif
    RETURN
EVT_END()

static EVT_BEGIN(musume_b_entry)
#ifdef NONMATCHING
    CALL(evt_npc_entry, STRING(((char*)str_00000B80)), STRING(((char*)str_00000C38)))
    CALL(evt_npc_set_tribe, STRING(((char*)str_00000B80)), STRING(((char*)str_00000C44)))
    CALL(evt_npc_set_position, STRING(((char*)str_00000B80)), 400, 5, -150)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00000B80)), 1536)
    CALL(evt_npc_change_interrupt, STRING(((char*)str_00000B80)), 6, PTR(musume_talk))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_entry, STRING(((char*)bom_01_str_00000B80)), STRING(((char*)bom_01_str_00000C38)))
    CALL(evt_npc_set_tribe, STRING(((char*)bom_01_str_00000B80)), STRING(((char*)bom_01_str_00000C44)))
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_00000B80)), 400, 5, -150)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)bom_01_str_00000B80)), 1536)
    CALL(evt_npc_change_interrupt, STRING(((char*)bom_01_str_00000B80)), 6, PTR(musume_talk))
#endif
    RETURN
EVT_END()

static EVT_BEGIN(musume_c_entry)
#ifdef NONMATCHING
    CALL(evt_npc_entry, STRING(((char*)str_00000BA0)), STRING(((char*)str_00000C54)))
    CALL(evt_npc_set_tribe, STRING(((char*)str_00000BA0)), STRING(((char*)str_00000C60)))
    CALL(evt_npc_set_position, STRING(((char*)str_00000BA0)), 430, 5, -100)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00000BA0)), 1536)
    CALL(evt_npc_change_interrupt, STRING(((char*)str_00000BA0)), 6, PTR(musume_talk))
#endif
#ifndef NONMATCHING
    CALL(evt_npc_entry, STRING(((char*)bom_01_str_00000BA0)), STRING(((char*)bom_01_str_00000C54)))
    CALL(evt_npc_set_tribe, STRING(((char*)bom_01_str_00000BA0)), STRING(((char*)bom_01_str_00000C60)))
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_00000BA0)), 430, 5, -100)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)bom_01_str_00000BA0)), 1536)
    CALL(evt_npc_change_interrupt, STRING(((char*)bom_01_str_00000BA0)), 6, PTR(musume_talk))
#endif
    RETURN
EVT_END()

static s32 npcEnt[] = {
#ifdef NONMATCHING
    (s32)/*"村長"*/(char*)str_00000774, 1073743360, 0, (s32)init_soncho, 0, (s32)talk_soncho, 0, 0,
#endif
#ifndef NONMATCHING
    (s32)/*"村長"*/(char*)bom_01_str_00000774, 1073743360, 0, (s32)init_soncho, 0, (s32)talk_soncho, 0, 0,
#endif
    0, 0, 0, 0, 0, 0, 0, 0,
#ifdef NONMATCHING
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ニトロ"*/(char*)str_00000368,
#endif
#ifndef NONMATCHING
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ニトロ"*/(char*)bom_01_str_00000368,
#endif
    1073743360, 0, (s32)init_nitoro, 0, (s32)talk_nitoro, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
#ifdef NONMATCHING
    0, 0, 0, 0, 0, 0, (s32)/*"ペントリット"*/((char*)str_000001B8), 1073743360,
#endif
#ifndef NONMATCHING
    0, 0, 0, 0, 0, 0, (s32)/*"ペントリット"*/((char*)bom_01_str_000001B8), 1073743360,
#endif
    0, (s32)init_pentrit, 0, (s32)talk_pentrit, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
#ifdef NONMATCHING
    0, 0, 0, 0, 0, (s32)/*"スラリー"*/((char*)str_000001C8), 1073743360, 0,
#endif
#ifndef NONMATCHING
    0, 0, 0, 0, 0, (s32)/*"スラリー"*/((char*)bom_01_str_000001C8), 1073743360, 0,
#endif
    (s32)init_surary, 0, (s32)talk_surary, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
#ifdef NONMATCHING
    0, 0, 0, 0, (s32)/*"ボムヘイD"*/(char*)str_000003A0, 1073743360, 0, (s32)init_murabito_d,
#endif
#ifndef NONMATCHING
    0, 0, 0, 0, (s32)/*"ボムヘイD"*/(char*)bom_01_str_000003A0, 1073743360, 0, (s32)init_murabito_d,
#endif
    0, (s32)talk_murabito_d, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
#ifdef NONMATCHING
    0, 0, 0, (s32)/*"ホワイト"*/((char*)str_000001AC), 1073743360, 0, (s32)init_white, 0,
#endif
#ifndef NONMATCHING
    0, 0, 0, (s32)/*"ホワイト"*/((char*)bom_01_str_000001AC), 1073743360, 0, (s32)init_white, 0,
#endif
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
#endif
#ifndef NONMATCHING
s32 taihou_r(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
    x = 100.0f * c;
    rx = -angleABf(0.0f, 0.0f, 0.0f, y = 100.0f * s);
    rz = -angleABf(0.0f, 0.0f, x, y);
#endif

#ifdef NONMATCHING
    effKemuTestSetRxRz(effNameToPtr("kemuri"), rx, rz);
    effRippleN64SetRxRz(effNameToPtr("ripple"), rx, rz);
#endif
#ifndef NONMATCHING

#pragma opt_propagation off
#pragma opt_lifetimes off
static void depthDisp(CameraId camera, void* param);
#pragma opt_propagation reset
#pragma opt_lifetimes reset

static s32 depth(EventEntry* event, BOOL isFirstCall);

static s32 make_name(EventEntry* event, BOOL isFirstCall);

s32 make_ext_table_minnnanokoe(EventEntry* event, BOOL isFirstCall);

void ext_init_minnnanokoe(void);

void jump_minnnanokoe(s32 i, f32 h);

void ext_disp_minnnanokoe(CameraId camera, void* param);

void ext_dispent_minnnanokoe(void);

s32 bom1000_msg(EventEntry* event, BOOL isFirstCall);

s32 bom1000_jump(EventEntry* event, BOOL isFirstCall);

void envSetYamiView(Mtx mtx);

static s32 yami_view(EventEntry* event, BOOL isFirstCall);

static s32 anim_tevcallback(EventEntry* event, BOOL isFirstCall);

EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);

static s32 starstone_entry(EventEntry* event, BOOL isFirstCall);

static s32 starstone_set_pos(EventEntry* event, BOOL isFirstCall);

static s32 starstone_set_ry(EventEntry* event, BOOL isFirstCall);


EVT_BEGIN(bom1000_minnnanokoe)
    CALL(make_ext_table_minnnanokoe)
    CALL(evt_npc_entry, STRING(((char*)bom_01_str_000002AC)), STRING(((char*)bom_01_str_000002B4)))
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_000002AC)), 0, -1000, 0)
    CALL(evt_ext_entry, 250, PTR(ext_data), PTR(ext_init_minnnanokoe), PTR(ext_main), PTR(ext_dispent_minnnanokoe))
    RETURN
EVT_END()

static EVT_BEGIN(minnnanokoe_evt)
    SPAWN_EVENT(PTR(bom1000_minnnanokoe))
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)bom_01_str_000003E4)), 1)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_00000774)), 520, 0, 0)
    CALL(evt_npc_set_ry, STRING(((char*)bom_01_str_00000774)), 270)
    CALL(evt_npc_status_onoff, 1, STRING(((char*)bom_01_str_00000774)), 2)
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_00000368)), -30, 0, -180)
    CALL(evt_npc_set_ry, STRING(((char*)bom_01_str_00000368)), 270)
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_000001B8)), 0, 0, -180)
    CALL(evt_npc_set_ry, STRING(((char*)bom_01_str_000001B8)), 270)
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_000001C8)), 30, 0, -180)
    CALL(evt_npc_set_ry, STRING(((char*)bom_01_str_000001C8)), 90)
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_000003A0)), 570, 0, 25)
    CALL(evt_npc_set_ry, STRING(((char*)bom_01_str_000003A0)), 270)
    CALL(evt_npc_status_onoff, 1, STRING(((char*)bom_01_str_000003A0)), 2)
    CALL(evt_npc_set_position, STRING(((char*)bom_01_str_000001AC)), 0, 0, -230)
    CALL(evt_npc_set_ry, STRING(((char*)bom_01_str_000001AC)), 270)
    CALL(evt_map_set_tevcallback, 1, PTR(envSetYami))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)bom_01_str_00000CA8)), 16777216)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)bom_01_str_00000CA8)), 256)
    CALL(anim_tevcallback, STRING(((char*)bom_01_str_00000774)), 1)
    CALL(anim_tevcallback, STRING(((char*)bom_01_str_00000368)), 1)
    CALL(anim_tevcallback, STRING(((char*)bom_01_str_000001B8)), 1)
    CALL(anim_tevcallback, STRING(((char*)bom_01_str_000001C8)), 1)
    CALL(anim_tevcallback, STRING(((char*)bom_01_str_000003A0)), 1)
    CALL(anim_tevcallback, STRING(((char*)bom_01_str_000001AC)), 1)
    CALL(yami_view, -1500)
    CALL(evt_bg_set_color, 64, 64, 64, 255)
    CALL(starstone_entry, STRING(((char*)bom_01_str_00000CB0)), 0, 50, 10)
    SET_VALUE(GW(0), 50)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(starstone_set_pos, STRING(((char*)bom_01_str_00000CB0)), 0, GW(0), 10)
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(LW(0), FLOAT((0.0f)))
        LOOP(0)
            CALL(starstone_set_ry, STRING(((char*)bom_01_str_00000CB0)), LW(0))
            SUBTRACT_FLOAT(LW(0), FLOAT((3.0f)))
            IF_INT_LESS_OR_EQUAL(LW(0), FLOAT((0.0f)))
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
            DIVIDE_FLOAT(LW(0), FLOAT((100.0f)))
            SET_FLOAT_VALUE(GW(0), LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(1)
            END_IF
            CALL(evt_sub_intpl_msec_init, 11, 5500, 5000, 500)
            LABEL(2)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT((100.0f)))
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
        CALL(evt_npc_move_position, STRING(((char*)bom_01_str_000003A0)), 450, 25, 0, 90, 0)
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING(((char*)bom_01_str_00000774)), 400, 0, 0, 90, 0)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000CBC)), 0, STRING(((char*)bom_01_str_00000774)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000CCC)), 0, STRING(((char*)bom_01_str_00000774)))
    CALL(evt_cam3d_evt_set, 0, 283, 1182, 0, 75, 0, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000CDC)), 0, 0)
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
                SET_VALUE(LW(3), STRING(((char*)bom_01_str_00000CEC)))
                CASE_EQUAL(1)
                SET_VALUE(LW(3), STRING(((char*)bom_01_str_00000CFC)))
                CASE_EQUAL(2)
                SET_VALUE(LW(3), STRING(((char*)bom_01_str_00000D0C)))
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
    CALL(evt_npc_set_ry, STRING(((char*)bom_01_str_00000774)), 90)
    WAIT_MS(300)
    CALL(evt_npc_set_ry, STRING(((char*)bom_01_str_000003A0)), 90)
    WAIT_FRAMES(1)
    CALL(evt_npc_wait_pera, STRING(((char*)bom_01_str_000003A0)))
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000D1C)), 0, STRING(((char*)bom_01_str_00000774)))
    WAIT_MS(2000)
    CALL(evt_fade_set_mapchange_type, 1, 10, 300, 9, 300)
    CALL(evt_bero_mapchange, STRING(((char*)bom_01_str_00000D2C)), STRING(((char*)bom_01_str_00000D34)))
    RETURN
EVT_END()

static EVT_BEGIN(evt_door)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING(((char*)bom_01_str_00000D40)), 0, 0)
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
        IF_STR_EQUAL(LW(0), STRING(((char*)bom_01_str_00000D34)))
            CALL(evt_snd_bgmon, 512, STRING(((char*)bom_01_str_00000D50)))
            CALL(evt_snd_envoff, 512)
            SET_VALUE(LF(0), 1)
        END_IF
    END_IF
    IF_INT_EQUAL(LF(0), 0)
        CALL(evt_snd_bgmon, 512, STRING(((char*)bom_01_str_00000D64)))
        CALL(evt_snd_envon, 272, STRING(((char*)bom_01_str_00000D74)))
    END_IF
    SET_VALUE(LW(0), STRING(((char*)bom_01_str_00000D84)))
    SPAWN_EVENT(PTR(evt_bom_01_karakara))
    SET_VALUE(LW(0), STRING(((char*)bom_01_str_00000D8C)))
    SPAWN_EVENT(PTR(evt_bom_01_karakara))
    SET_VALUE(LW(0), STRING(((char*)bom_01_str_00000D94)))
    SPAWN_EVENT(PTR(evt_bom_01_karakara))
    SET_VALUE(LW(0), STRING(((char*)bom_01_str_00000D9C)))
    SPAWN_EVENT(PTR(evt_bom_01_karakara))
    SET_VALUE(LW(0), STRING(((char*)bom_01_str_00000DA4)))
    SPAWN_EVENT(PTR(evt_bom_01_karakara))
    SET_VALUE(LW(0), STRING(((char*)bom_01_str_00000DAC)))
    SPAWN_EVENT(PTR(evt_bom_01_karakara))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)bom_01_str_000003CC)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)bom_01_str_00000DB4)), 1, 0)
    CALL_CHILD(PTR(evt_bom_snowfall))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)bom_01_str_00000728)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)bom_01_str_000003EC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)bom_01_str_000005AC)), 1)
    CALL(evt_mapobj_trans, 1, STRING(((char*)bom_01_str_000003CC)), 0, FLOAT((-1.0f)), 0)
    CALL(evt_npc_setup, PTR(npcEnt))
    SWITCH(GSW(0))
        CASE_BETWEEN(352, 357)
        CALL_CHILD(PTR(musume_a_entry))
        CALL_CHILD(PTR(musume_b_entry))
        CALL_CHILD(PTR(musume_c_entry))
    END_SWITCH
    CALL(evt_run_case_evt, 9, 1, STRING(((char*)bom_01_str_000001E0)), 0, PTR(evt_door), 0)
    CALL(evt_item_entry, STRING(((char*)bom_01_str_00000DBC)), 125, -180, 5, 450, 16, GSWF(5659), 0)
    SWITCH(GSW(0))
        CASE_LESS(349)
        SET_VALUE(GSWF(3885), 1)
        CASE_LESS(353)
        SPAWN_EVENT(PTR(first_evt))
    END_SWITCH
    IF_INT_EQUAL(GSW(0), 400)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_EQUAL(LW(0), STRING(((char*)bom_01_str_00000D34)))
            SPAWN_EVENT(PTR(minnnanokoe_evt))
        END_IF
    END_IF
    SPAWN_EVENT(PTR(evt_sub_mail_event))
    BEGIN_INLINE_EVENT
        CALL(sight)
    END_INLINE_EVENT
    RETURN
EVT_END()


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void disp_sight(CameraId camera, void* param) {
	char _af_pad[816];
	asm volatile {
		lis r4, zero_bom_00007004@ha
		lis r3, float_1_bom_00006ffc@ha
		lfs f1, zero_bom_00007004@l(r4)
		lis r4, dat_bom_00006380@ha
		lfs f3, float_1_bom_00006ffc@l(r3)
		lis r5, dat_bom_0000637c@ha
		lwz r3, dat_bom_0000637c@l(r5)
		opword 0xFC400890
		lwz r0, dat_bom_00006380@l(r4)
		opword 0xFC801890
		stw r3, _af_pad+80(r1)
		opword 0xFCA00890
		opword 0x38600000
		opword 0x90010054
		bl drawBG
		lis r3, zero_bom_00007004@ha
		lis r4, float_neg1_bom_00007120@ha
		addi r5, r3, zero_bom_00007004@l
		lfs f3, float_neg1_bom_00007120@l(r4)
		opword 0xC0250000
		lis r3, float_1_bom_00006ffc@ha
		lfs f4, float_1_bom_00006ffc@l(r3)
		opword 0x38600000
		opword 0xFC400890
		opword 0xFCA00890
		bl drawBG
		lis r3, zero_bom_00007004@ha
		lis r4, float_1_bom_00006ffc@ha
		addi r5, r3, zero_bom_00007004@l
		lfs f3, float_1_bom_00006ffc@l(r4)
		opword 0xC0250000
		lis r3, float_neg1_bom_00007120@ha
		lfs f4, float_neg1_bom_00007120@l(r3)
		opword 0x38600000
		opword 0xFC400890
		opword 0xFCA00890
		bl drawBG
		lis r3, zero_bom_00007004@ha
		lis r4, float_neg1_bom_00007120@ha
		addi r5, r3, zero_bom_00007004@l
		lfs f3, float_neg1_bom_00007120@l(r4)
		opword 0xC0250000
		opword 0x38600000
		opword 0xFC801890
		opword 0xFC400890
		opword 0xFCA00890
		bl drawBG
		lis r3, zero_bom_00007004@ha
		lis r4, float_1_bom_00006ffc@ha
		addi r5, r3, zero_bom_00007004@l
		lfs f3, float_1_bom_00006ffc@l(r4)
		lis r3, sight_wp@ha
		opword 0xC0250000
		lwz r4, sight_wp@l(r3)
		opword 0xFC801890
		opword 0xFC400890
		opword 0x38600001
		opword 0xC0A40018
		bl drawBG
		lis r3, sight_wp@ha
		lis r4, zero_bom_00007004@ha
		addi r3, r3, sight_wp@l
		lfs f1, zero_bom_00007004@l(r4)
		opword 0x80630000
		lis r5, float_neg1_bom_00007120@ha
		lis r4, float_1_bom_00006ffc@ha
		opword 0xFC400890
		opword 0xC0030018
		opword 0x38600001
		lfs f3, float_neg1_bom_00007120@l(r5)
		opword 0xFCA00050
		lfs f4, float_1_bom_00006ffc@l(r4)
		bl drawBG
		lis r3, sight_wp@ha
		lis r4, zero_bom_00007004@ha
		addi r3, r3, sight_wp@l
		lfs f1, zero_bom_00007004@l(r4)
		opword 0x80630000
		lis r5, float_1_bom_00006ffc@ha
		lis r4, float_neg1_bom_00007120@ha
		opword 0xFC400890
		opword 0xC0030018
		opword 0x38600001
		lfs f3, float_1_bom_00006ffc@l(r5)
		opword 0xFCA00050
		lfs f4, float_neg1_bom_00007120@l(r4)
		bl drawBG
		lis r3, zero_bom_00007004@ha
		lis r4, float_neg1_bom_00007120@ha
		addi r5, r3, zero_bom_00007004@l
		lfs f3, float_neg1_bom_00007120@l(r4)
		lis r3, sight_wp@ha
		opword 0xC0250000
		lwz r4, sight_wp@l(r3)
		opword 0xFC801890
		opword 0xFC400890
		opword 0x38600001
		opword 0xC0A40018
		bl drawBG
		lis r3, sight_wp@ha
		lwz r4, sight_wp@l(r3)
		opword 0x8004001C
		opword 0x2C000002
		opword 0x4082001C
		lis r3, float_2_bom_0000704c@ha
		opword 0xC0240018
		lfs f0, float_2_bom_0000704c@l(r3)
		opword 0xEC01002A
		opword 0xD0040018
		opword 0x48000058
		opword 0x2C000003
		opword 0x4082001C
		lis r3, float_2_bom_0000704c@ha
		opword 0xC0240018
		lfs f0, float_2_bom_0000704c@l(r3)
		opword 0xEC010028
		opword 0xD0040018
		opword 0x48000038
		opword 0x2C000000
		opword 0x4082001C
		lis r3, float_2_bom_0000704c@ha
		opword 0xC0240018
		lfs f0, float_2_bom_0000704c@l(r3)
		opword 0xEC010028
		opword 0xD0040018
		opword 0x48000018
		lis r3, float_1_bom_00006ffc@ha
		opword 0xC0240018
		lfs f0, float_1_bom_00006ffc@l(r3)
		opword 0xEC01002A
		opword 0xD0040018
		lis r3, sight_wp@ha
		addi r3, r3, sight_wp@l
		opword 0x80630000
		opword 0x80630000
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit
		lis r4, vec3_bom_00006390@ha
		lis r3, vec3_bom_00006384@ha
		addi r5, r4, vec3_bom_00006390@l
		opword 0x83210054
		addi r9, r3, vec3_bom_00006384@l
		opword 0x81850000
		opword 0x81650004
		opword 0x38810218
		opword 0x81450008
		opword 0x38A1020C
		opword 0x81090000
		opword 0x38C10050
		opword 0x80E90004
		opword 0x38600005
		opword 0x80090008
		opword 0x93210050
		opword 0x9181020C
		opword 0x91610210
		opword 0x91410214
		opword 0x91010218
		opword 0x90E1021C
		opword 0x90010220
		bl winTexSet
		lis r3, gp@ha
		opword 0x3B400000
		addi r27, r3, gp@l
		opword 0x807B0000
		opword 0x3880001E
		opword 0x3800000A
		opword 0x80A3001C
		opword 0x7C652396
		opword 0x7C6321D6
		opword 0x7C632850
		opword 0x7C0303D6
		opword 0x7C00D000
		opword 0x41820100
		lis r3, float_1_bom_00006ffc@ha
		lis r5, float_100_bom_00007000@ha
		lfs f3, float_1_bom_00006ffc@l(r3)
		addi r6, r5, float_100_bom_00007000@l
		lis r4, float_60_bom_000070dc@ha
		lis r3, zero_bom_00007004@ha
		addi r5, r4, float_60_bom_000070dc@l
		opword 0xFC801890
		addi r4, r3, zero_bom_00007004@l
		opword 0x233A0004
		opword 0xC0260000
		opword 0x7F23CB78
		opword 0xC0450000
		opword 0xC0A40000
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
		opword 0xC0280000
		opword 0x7F23CB78
		opword 0xC0470000
		opword 0xC0660000
		opword 0xC0850000
		opword 0xC0A40000
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
		opword 0xC0280000
		opword 0x7F23CB78
		opword 0xC0470000
		opword 0xC0660000
		opword 0xC0850000
		opword 0xC0A40000
		bl drawBG
		lis r3, float_neg1_bom_00007120@ha
		lis r5, float_neg100_bom_00007124@ha
		lfs f3, float_neg1_bom_00007120@l(r3)
		addi r6, r5, float_neg100_bom_00007124@l
		lis r4, float_neg60_bom_00007128@ha
		lis r3, zero_bom_00007004@ha
		addi r5, r4, float_neg60_bom_00007128@l
		opword 0xFC801890
		addi r4, r3, zero_bom_00007004@l
		opword 0xC0260000
		opword 0xC0450000
		opword 0x7F23CB78
		opword 0xC0A40000
		bl drawBG
		opword 0x3B5A0001
		opword 0x2C1A0003
		opword 0x4180FED4
		lis r3, sight_wp@ha
		addi r3, r3, sight_wp@l
		opword 0x80630000
		opword 0x80630000
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit
		lis r4, vec3_bom_000063a8@ha
		lis r3, vec3_bom_0000639c@ha
		addi r5, r4, vec3_bom_000063a8@l
		opword 0x83210058
		addi r9, r3, vec3_bom_0000639c@l
		opword 0x81850000
		opword 0x81650004
		opword 0x38810200
		opword 0x81450008
		opword 0x38A101F4
		opword 0x81090000
		opword 0x38C1004C
		opword 0x80E90004
		opword 0x38600017
		opword 0x80090008
		opword 0x9321004C
		opword 0x918101F4
		opword 0x916101F8
		opword 0x914101FC
		opword 0x91010200
		opword 0x90E10204
		opword 0x90010208
		bl winTexSet
		lis r3, gp@ha
		opword 0x38A00000
		lwz r4, gp@l(r3)
		opword 0x38C00064
		opword 0x80640038
		opword 0x8084003C
		bl __div2i
		opword 0x38A00000
		opword 0x38C003E8
		bl __div2i
		lis r3, sight_wp@ha
		lis r6, dat_bom_00006360@ha
		addi r3, r3, sight_wp@l
		opword 0x7C85FE70
		opword 0x80630000
		addi r6, r6, dat_bom_00006360@l
		opword 0x80C60000
		opword 0x7CA02278
		opword 0x80630000
		opword 0x7F450050
		opword 0x90C10040
		opword 0x806300A0
		opword 0x80630000
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
		opword 0xCBEA0000
		addi r31, r11, sight_wp@l
		opword 0xC3C90000
		addi r28, r7, vec3_bom_00006370@l
		opword 0xC3A80000
		addi r27, r6, vec3_bom_00006364@l
		opword 0x83A10040
		opword 0x3B200000
		lfd f28, double_to_int_bom_00007030@l(r5)
		opword 0x3FC04330
		lfs f27, float_90_bom_00007130@l(r4)
		lfs f26, float_180_bom_000070c8@l(r3)
		opword 0x38A0000A
		opword 0x807F0000
		opword 0x7C1A2BD6
		opword 0x38810304
		opword 0x80630000
		opword 0x806300A0
		opword 0x80630000
		opword 0x7C0029D6
		opword 0x7CA0D050
		addi r24, r5, 0xd
		opword 0x7F05C378
		bl TEXGetGXTexObjFromPalette
		opword 0x38610304
		bl GXGetTexObjWidth
		opword 0x5460043E
		opword 0x811B0008
		opword 0x9001032C
		opword 0x2079000A
		opword 0x3803FFFF
		opword 0x817C0000
		opword 0x93C10328
		opword 0x6C008000
		opword 0x815C0004
		opword 0x7F03C378
		opword 0xC8010328
		opword 0x388101AC
		opword 0x813C0008
		opword 0x38A101C4
		opword 0xEC00F828
		opword 0x90010334
		opword 0x80FB0000
		opword 0x38C10044
		opword 0x93C10330
		opword 0xEC3E0032
		opword 0xC8010330
		opword 0x801B0004
		opword 0xEC21E82A
		opword 0x916101D0
		opword 0xEC00E028
		opword 0x914101D4
		opword 0x912101D8
		opword 0xEC01D83A
		opword 0x90E101B8
		opword 0x900101BC
		opword 0xD3C101D0
		opword 0xD3C101D4
		opword 0x816101D0
		opword 0xD3C101D8
		opword 0x814101D4
		opword 0xD00101B8
		opword 0x812101D8
		opword 0xD34101BC
		opword 0x80E101B8
		opword 0x800101BC
		opword 0x93A10044
		opword 0x916101C4
		opword 0x914101C8
		opword 0x912101CC
		opword 0x910101C0
		opword 0x90E101AC
		opword 0x900101B0
		opword 0x910101B4
		bl winTexSet
		opword 0x3800000A
		opword 0x3B390001
		opword 0x7F5A03D6
		opword 0x2C19000A
		opword 0x4180FEF4
		lis r3, gp@ha
		opword 0x38A00000
		lwz r4, gp@l(r3)
		opword 0x38C000C8
		opword 0x80640038
		opword 0x8084003C
		bl __div2i
		opword 0x38A00000
		opword 0x38C003E8
		bl __div2i
		lis r3, sight_wp@ha
		lis r6, dat_bom_00006360@ha
		addi r3, r3, sight_wp@l
		opword 0x7C85FE70
		opword 0x80630000
		addi r6, r6, dat_bom_00006360@l
		opword 0x80C60000
		opword 0x7CA02278
		opword 0x80630000
		opword 0x7F250050
		opword 0x90C10038
		opword 0x806300A0
		opword 0x80630000
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
		opword 0xCBEA0000
		addi r31, r11, sight_wp@l
		opword 0xC3C90000
		addi r28, r7, vec3_bom_00006370@l
		opword 0xC3A80000
		addi r27, r6, vec3_bom_00006364@l
		opword 0x83A10038
		opword 0x3B400000
		lfd f28, double_to_int_bom_00007030@l(r5)
		opword 0x3FC04330
		lfs f27, float_126_bom_00007134@l(r4)
		lfs f26, float_150_bom_000070b0@l(r3)
		opword 0x38A0000A
		opword 0x807F0000
		opword 0x7C192BD6
		opword 0x388102E4
		opword 0x80630000
		opword 0x806300A0
		opword 0x80630000
		opword 0x7C0029D6
		opword 0x7CA0C850
		opword 0x3B05000D
		opword 0x7F05C378
		bl TEXGetGXTexObjFromPalette
		opword 0x386102E4
		bl GXGetTexObjWidth
		opword 0x5460043E
		opword 0x811B0008
		opword 0x90010334
		opword 0x207A0008
		opword 0x3803FFFF
		opword 0x817C0000
		opword 0x93C10330
		opword 0x6C008000
		opword 0x815C0004
		opword 0x7F03C378
		opword 0xC8010330
		opword 0x3881017C
		opword 0x813C0008
		opword 0x38A10194
		opword 0xEC00F828
		opword 0x9001032C
		opword 0x80FB0000
		opword 0x38C1003C
		opword 0x93C10328
		opword 0xEC3E0032
		opword 0xC8010328
		opword 0x801B0004
		opword 0xEC21E82A
		opword 0x916101A0
		opword 0xEC00E028
		opword 0x914101A4
		opword 0x912101A8
		opword 0xEC01D83A
		opword 0x90E10188
		opword 0x9001018C
		opword 0xD3C101A0
		opword 0xD3C101A4
		opword 0x816101A0
		opword 0xD3C101A8
		opword 0x814101A4
		opword 0xD0010188
		opword 0x812101A8
		opword 0xD341018C
		opword 0x80E10188
		opword 0x8001018C
		opword 0x93A1003C
		opword 0x91610194
		opword 0x91410198
		opword 0x9121019C
		opword 0x91010190
		opword 0x90E1017C
		opword 0x90010180
		opword 0x91010184
		bl winTexSet
		opword 0x3800000A
		opword 0x3B5A0001
		opword 0x7F3903D6
		opword 0x2C1A0008
		opword 0x4180FEF4
		lis r3, gp@ha
		opword 0x38A00000
		lwz r4, gp@l(r3)
		opword 0x38C0012C
		opword 0x80640038
		opword 0x8084003C
		bl __div2i
		opword 0x38A00000
		opword 0x38C003E8
		bl __div2i
		lis r3, sight_wp@ha
		lis r6, dat_bom_00006360@ha
		addi r3, r3, sight_wp@l
		opword 0x7C85FE70
		opword 0x80630000
		addi r6, r6, dat_bom_00006360@l
		opword 0x80C60000
		opword 0x7CA02278
		opword 0x80630000
		opword 0x7F250050
		opword 0x90C10030
		opword 0x806300A0
		opword 0x80630000
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
		opword 0xCBEA0000
		addi r31, r11, sight_wp@l
		opword 0xC3C90000
		addi r28, r7, vec3_bom_00006370@l
		opword 0xC3A80000
		addi r27, r6, vec3_bom_00006364@l
		opword 0x83A10030
		opword 0x3B400000
		lfd f28, double_to_int_bom_00007030@l(r5)
		opword 0x3FC04330
		lfs f27, float_162_bom_00007138@l(r4)
		lfs f26, float_120_bom_0000713c@l(r3)
		opword 0x38A0000A
		opword 0x807F0000
		opword 0x7C192BD6
		opword 0x388102C4
		opword 0x80630000
		opword 0x806300A0
		opword 0x80630000
		opword 0x7C0029D6
		opword 0x7CA0C850
		opword 0x3B05000D
		opword 0x7F05C378
		bl TEXGetGXTexObjFromPalette
		opword 0x386102C4
		bl GXGetTexObjWidth
		opword 0x5460043E
		opword 0x811B0008
		opword 0x90010334
		opword 0x207A0006
		opword 0x3803FFFF
		opword 0x817C0000
		opword 0x93C10330
		opword 0x6C008000
		opword 0x815C0004
		opword 0x7F03C378
		opword 0xC8010330
		opword 0x3881014C
		opword 0x813C0008
		opword 0x38A10164
		opword 0xEC00F828
		opword 0x9001032C
		opword 0x80FB0000
		opword 0x38C10034
		opword 0x93C10328
		opword 0xEC3E0032
		opword 0xC8010328
		opword 0x801B0004
		opword 0xEC21E82A
		opword 0x91610170
		opword 0xEC00E028
		opword 0x91410174
		opword 0x91210178
		opword 0xEC01D83A
		opword 0x90E10158
		opword 0x9001015C
		opword 0xD3C10170
		opword 0xD3C10174
		opword 0x81610170
		opword 0xD3C10178
		opword 0x81410174
		opword 0xD0010158
		opword 0x81210178
		opword 0xD341015C
		opword 0x80E10158
		opword 0x8001015C
		opword 0x93A10034
		opword 0x91610164
		opword 0x91410168
		opword 0x9121016C
		opword 0x91010160
		opword 0x90E1014C
		opword 0x90010150
		opword 0x91010154
		bl winTexSet
		opword 0x3800000A
		opword 0x3B5A0001
		opword 0x7F3903D6
		opword 0x2C1A0006
		opword 0x4180FEF4
		lis r3, gp@ha
		opword 0x38A00000
		lwz r4, gp@l(r3)
		opword 0x38C00190
		opword 0x80640038
		opword 0x8084003C
		bl __div2i
		opword 0x38A00000
		opword 0x38C003E8
		bl __div2i
		lis r3, sight_wp@ha
		lis r6, dat_bom_00006360@ha
		addi r3, r3, sight_wp@l
		opword 0x7C85FE70
		opword 0x80630000
		addi r6, r6, dat_bom_00006360@l
		opword 0x80C60000
		opword 0x7CA02278
		opword 0x80630000
		opword 0x7F250050
		opword 0x90C10028
		opword 0x806300A0
		opword 0x80630000
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
		opword 0xCBEA0000
		addi r31, r11, sight_wp@l
		opword 0xC3C90000
		addi r28, r7, vec3_bom_00006370@l
		opword 0xC3A80000
		addi r27, r6, vec3_bom_00006364@l
		opword 0x83A10028
		opword 0x3B400000
		lfd f28, double_to_int_bom_00007030@l(r5)
		opword 0x3FC04330
		lfs f27, float_162_bom_00007138@l(r4)
		lfs f26, float_90_bom_00007130@l(r3)
		opword 0x38A0000A
		opword 0x807F0000
		opword 0x7C192BD6
		opword 0x388102A4
		opword 0x80630000
		opword 0x806300A0
		opword 0x80630000
		opword 0x7C0029D6
		opword 0x7CA0C850
		opword 0x3B05000D
		opword 0x7F05C378
		bl TEXGetGXTexObjFromPalette
		opword 0x386102A4
		bl GXGetTexObjWidth
		opword 0x5460043E
		opword 0x811B0008
		opword 0x90010334
		opword 0x207A0006
		opword 0x3803FFFF
		opword 0x817C0000
		opword 0x93C10330
		opword 0x6C008000
		opword 0x815C0004
		opword 0x7F03C378
		opword 0xC8010330
		opword 0x3881011C
		opword 0x813C0008
		opword 0x38A10134
		opword 0xEC00F828
		opword 0x9001032C
		opword 0x80FB0000
		opword 0x38C1002C
		opword 0x93C10328
		opword 0xEC3E0032
		opword 0xC8010328
		opword 0x801B0004
		opword 0xEC21E82A
		opword 0x91610140
		opword 0xEC00E028
		opword 0x91410144
		opword 0x91210148
		opword 0xEC01D83A
		opword 0x90E10128
		opword 0x9001012C
		opword 0xD3C10140
		opword 0xD3C10144
		opword 0x81610140
		opword 0xD3C10148
		opword 0x81410144
		opword 0xD0010128
		opword 0x81210148
		opword 0xD341012C
		opword 0x80E10128
		opword 0x8001012C
		opword 0x93A1002C
		opword 0x91610134
		opword 0x91410138
		opword 0x9121013C
		opword 0x91010130
		opword 0x90E1011C
		opword 0x90010120
		opword 0x91010124
		bl winTexSet
		opword 0x3800000A
		opword 0x3B5A0001
		opword 0x7F3903D6
		opword 0x2C1A0006
		opword 0x4180FEF4
		lis r4, gp@ha
		lis r3, sight_wp@ha
		addi r5, r4, gp@l
		addi r3, r3, sight_wp@l
		opword 0x80A50000
		opword 0x80630000
		lis r4, dat_bom_00006360@ha
		opword 0x8005001C
		opword 0x80630000
		lwz r5, dat_bom_00006360@l(r4)
		opword 0x5400F0BE
		opword 0x806300A0
		opword 0x7C04FE70
		opword 0x7C800278
		opword 0x90A10020
		opword 0x80630000
		opword 0x7F240050
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
		opword 0xCBEA0000
		addi r31, r11, sight_wp@l
		opword 0xC3C90000
		addi r28, r7, vec3_bom_00006370@l
		opword 0xC3A80000
		addi r27, r6, vec3_bom_00006364@l
		opword 0x83A10020
		opword 0x3B400000
		lfd f28, double_to_int_bom_00007030@l(r5)
		opword 0x3FC04330
		lfs f27, float_110_bom_00007140@l(r4)
		lfs f26, float_neg160_bom_00007144@l(r3)
		opword 0x38A0000A
		opword 0x807F0000
		opword 0x7C192BD6
		opword 0x38810284
		opword 0x80630000
		opword 0x806300A0
		opword 0x80630000
		opword 0x7C0029D6
		opword 0x7CA0C850
		opword 0x3B05000D
		opword 0x7F05C378
		bl TEXGetGXTexObjFromPalette
		opword 0x38610284
		bl GXGetTexObjWidth
		opword 0x5460043E
		opword 0x811B0008
		opword 0x90010334
		opword 0x207A0004
		opword 0x3803FFFF
		opword 0x817C0000
		opword 0x93C10330
		opword 0x6C008000
		opword 0x815C0004
		opword 0x7F03C378
		opword 0xC8010330
		opword 0x388100EC
		opword 0x813C0008
		opword 0x38A10104
		opword 0xEC00F828
		opword 0x9001032C
		opword 0x80FB0000
		opword 0x38C10024
		opword 0x93C10328
		opword 0xEC3E0032
		opword 0xC8010328
		opword 0x801B0004
		opword 0xEC21E82A
		opword 0x91610110
		opword 0xEC00E028
		opword 0x91410114
		opword 0x91210118
		opword 0xEC01D83A
		opword 0x90E100F8
		opword 0x900100FC
		opword 0xD3C10110
		opword 0xD3C10114
		opword 0x81610110
		opword 0xD3C10118
		opword 0x81410114
		opword 0xD00100F8
		opword 0x81210118
		opword 0xD34100FC
		opword 0x80E100F8
		opword 0x800100FC
		opword 0x93A10024
		opword 0x91610104
		opword 0x91410108
		opword 0x9121010C
		opword 0x91010100
		opword 0x90E100EC
		opword 0x900100F0
		opword 0x910100F4
		bl winTexSet
		opword 0x3800000A
		opword 0x3B5A0001
		opword 0x7F3903D6
		opword 0x2C1A0004
		opword 0x4180FEF4
		lis r4, gp@ha
		lis r3, sight_wp@ha
		addi r5, r4, gp@l
		addi r3, r3, sight_wp@l
		opword 0x80A50000
		opword 0x80630000
		lis r4, dat_bom_00006360@ha
		opword 0x8005001C
		opword 0x80630000
		lwz r5, dat_bom_00006360@l(r4)
		opword 0x5400E8FE
		opword 0x806300A0
		opword 0x7C04FE70
		opword 0x7C800278
		opword 0x90A10018
		opword 0x80630000
		opword 0x7F240050
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
		opword 0xCBEA0000
		addi r31, r11, sight_wp@l
		opword 0xC3C90000
		addi r28, r7, vec3_bom_00006370@l
		opword 0xC3A80000
		addi r27, r6, vec3_bom_00006364@l
		opword 0x83A10018
		opword 0x3B400000
		lfd f28, double_to_int_bom_00007030@l(r5)
		opword 0x3FC04330
		lfs f27, float_230_bom_0000714c@l(r4)
		lfs f26, float_neg170_bom_00007150@l(r3)
		opword 0x38A0000A
		opword 0x807F0000
		opword 0x7C192BD6
		opword 0x38810264
		opword 0x80630000
		opword 0x806300A0
		opword 0x80630000
		opword 0x7C0029D6
		opword 0x7CA0C850
		opword 0x3B05000D
		opword 0x7F05C378
		bl TEXGetGXTexObjFromPalette
		opword 0x38610264
		bl GXGetTexObjWidth
		opword 0x5460043E
		opword 0x811B0008
		opword 0x90010334
		opword 0x207A0002
		opword 0x3803FFFF
		opword 0x817C0000
		opword 0x93C10330
		opword 0x6C008000
		opword 0x815C0004
		opword 0x7F03C378
		opword 0xC8010330
		opword 0x388100BC
		opword 0x813C0008
		opword 0x38A100D4
		opword 0xEC00F828
		opword 0x9001032C
		opword 0x80FB0000
		opword 0x38C1001C
		opword 0x93C10328
		opword 0xEC3E0032
		opword 0xC8010328
		opword 0x801B0004
		opword 0xEC21E82A
		opword 0x916100E0
		opword 0xEC00E028
		opword 0x914100E4
		opword 0x912100E8
		opword 0xEC01D83A
		opword 0x90E100C8
		opword 0x900100CC
		opword 0xD3C100E0
		opword 0xD3C100E4
		opword 0x816100E0
		opword 0xD3C100E8
		opword 0x814100E4
		opword 0xD00100C8
		opword 0x812100E8
		opword 0xD34100CC
		opword 0x80E100C8
		opword 0x800100CC
		opword 0x93A1001C
		opword 0x916100D4
		opword 0x914100D8
		opword 0x912100DC
		opword 0x910100D0
		opword 0x90E100BC
		opword 0x900100C0
		opword 0x910100C4
		bl winTexSet
		opword 0x3800000A
		opword 0x3B5A0001
		opword 0x7F3903D6
		opword 0x2C1A0002
		opword 0x4180FEF4
		lis r4, vec3_bom_000063c0@ha
		lis r3, vec3_bom_000063b4@ha
		addi r5, r4, vec3_bom_000063c0@l
		opword 0x83210058
		addi r9, r3, vec3_bom_000063b4@l
		opword 0x81850000
		opword 0x81650004
		opword 0x388101E8
		opword 0x81450008
		opword 0x38A101DC
		opword 0x81090000
		opword 0x38C10048
		opword 0x80E90004
		opword 0x38600008
		opword 0x80090008
		opword 0x93210048
		opword 0x918101DC
		opword 0x916101E0
		opword 0x914101E4
		opword 0x910101E8
		opword 0x90E101EC
		opword 0x900101F0
		bl winTexSet
		lis r3, gp@ha
		addi r3, r3, gp@l
		opword 0x80630000
		opword 0x8003001C
		opword 0x540007BF
		opword 0x40820070
		lis r3, sight_wp@ha
		opword 0x38000004
		addi r4, r3, sight_wp@l
		opword 0x38600000
		opword 0x7C0903A6
		opword 0x80040000
		opword 0x7CA01A14
		opword 0x38630004
		opword 0x80050008
		opword 0x90050004
		opword 0x4200FFEC
		lis r4, sound@ha
		lis r3, sight_wp@ha
		addi r5, r4, sound@l
		opword 0xA0850330
		addi r3, r3, sight_wp@l
		opword 0x800515C0
		opword 0x54845828
		opword 0x80630000
		opword 0x7C852214
		opword 0x5400083C
		opword 0x7C840214
		opword 0xA80405C0
		opword 0x7C04FE70
		opword 0x7C800278
		opword 0x7C040050
		opword 0x90030014
		lis r5, float_16_bom_0000715c@ha
		lis r4, double_to_int_bom_00007030@ha
		lis r3, float_neg190_bom_00007158@ha
		lis r7, float_20_bom_000070d8@ha
		lis r6, float_neg240_bom_00007154@ha
		lis r8, sight_wp@ha
		lfs f28, float_16_bom_0000715c@l(r5)
		addi r27, r8, sight_wp@l
		lfd f27, double_to_int_bom_00007030@l(r4)
		opword 0x3B200000
		lfs f26, float_neg190_bom_00007158@l(r3)
		opword 0x3B400000
		lfs f30, float_20_bom_000070d8@l(r7)
		opword 0x3F804330
		lfs f29, float_neg240_bom_00007154@l(r6)
		opword 0x809B0000
		opword 0x387A0004
		opword 0x3800012C
		opword 0x7FA4182E
		opword 0x7FBD03D6
		opword 0x2C1D0007
		opword 0x40810008
		opword 0x3BA00007
		opword 0x6F208000
		opword 0x93810330
		opword 0x3B000000
		opword 0x90010334
		opword 0xC8010330
		opword 0xEC00D828
		opword 0xEFFEE83A
		opword 0x4800006C
		opword 0x6F008000
		opword 0x93810330
		opword 0x2C180006
		opword 0x90010334
		opword 0xC8010330
		opword 0xEC00D828
		opword 0xEC5CD03A
		opword 0x40820028
		lis r4, float_1_bom_00006ffc@ha
		lis r3, zero_bom_00007004@ha
		lfs f3, float_1_bom_00006ffc@l(r4)
		opword 0xFC20F890
		lfs f5, zero_bom_00007004@l(r3)
		opword 0x3860000A
		opword 0xFC801890
		bl drawBG
		opword 0x48000024
		lis r4, float_1_bom_00006ffc@ha
		lis r3, zero_bom_00007004@ha
		lfs f3, float_1_bom_00006ffc@l(r4)
		opword 0xFC20F890
		lfs f5, zero_bom_00007004@l(r3)
		opword 0x38600009
		opword 0xFC801890
		bl drawBG
		opword 0x3B180001
		opword 0x7C18E800
		opword 0x4180FF94
		opword 0x7FB8EB78
		opword 0x4800006C
		opword 0x6F008000
		opword 0x93810330
		opword 0x2C180006
		opword 0x90010334
		opword 0xC8010330
		opword 0xEC00D828
		opword 0xEC5CD03A
		opword 0x40820028
		lis r4, float_1_bom_00006ffc@ha
		lis r3, zero_bom_00007004@ha
		lfs f3, float_1_bom_00006ffc@l(r4)
		opword 0xFC20F890
		lfs f5, zero_bom_00007004@l(r3)
		opword 0x3860000C
		opword 0xFC801890
		bl drawBG
		opword 0x48000024
		lis r4, float_1_bom_00006ffc@ha
		lis r3, zero_bom_00007004@ha
		lfs f3, float_1_bom_00006ffc@l(r4)
		opword 0xFC20F890
		lfs f5, zero_bom_00007004@l(r3)
		opword 0x3860000B
		opword 0xFC801890
		bl drawBG
		opword 0x3B180001
		opword 0x2C180007
		opword 0x4180FF94
		opword 0x3B390001
		opword 0x3B5A0004
		opword 0x2C190005
		opword 0x4180FECC
		lis r3, sight_wp@ha
		addi r3, r3, sight_wp@l
		opword 0x80630000
		opword 0x80630000
		opword 0x806300A0
		opword 0x80630000
		bl winTexInit
		lis r4, gp@ha
		lis r3, sight_wp@ha
		addi r28, r4, gp@l
		opword 0x3B200000
		addi r27, r3, sight_wp@l
		opword 0x809C0000
		opword 0x38600014
		opword 0x38A00000
		opword 0x8084001C
		opword 0x7C041B96
		opword 0x7C0019D6
		opword 0x7C002050
		opword 0x28000006
		opword 0x40810020
		lis r3, sight_wp@ha
		addi r3, r3, sight_wp@l
		opword 0x80630000
		opword 0x8003001C
		opword 0x7C190000
		opword 0x40820008
		opword 0x38A00001
		opword 0x3065FFFF
		opword 0x38000007
		opword 0x7C632911
		opword 0x7C7A1B78
		opword 0x41820008
		opword 0x38000006
		opword 0x809B0000
		opword 0x7C030378
		opword 0x8004001C
		opword 0x2C000004
		opword 0x4082000C
		opword 0x3B400000
		opword 0x38600007
		opword 0x2C190002
		opword 0x4182007C
		opword 0x40800014
		opword 0x2C190000
		opword 0x41820018
		opword 0x40800040
		opword 0x48000124
		opword 0x2C190004
		opword 0x4080011C
		opword 0x480000BC
		lis r4, float_1_bom_00006ffc@ha
		lis r6, float_16_bom_0000715c@ha
		lfs f3, float_1_bom_00006ffc@l(r4)
		lis r5, float_180_bom_000070c8@ha
		lis r4, float_90_bom_00007130@ha
		lfs f1, float_16_bom_0000715c@l(r6)
		opword 0xFC801890
		lfs f2, float_180_bom_000070c8@l(r5)
		lfs f5, float_90_bom_00007130@l(r4)
		bl drawBG
		opword 0x480000EC
		lis r4, float_1_bom_00006ffc@ha
		lis r6, float_neg16_bom_00007160@ha
		lfs f3, float_1_bom_00006ffc@l(r4)
		lis r5, float_neg180_bom_00007164@ha
		lis r4, float_270_bom_0000703c@ha
		lfs f1, float_neg16_bom_00007160@l(r6)
		opword 0xFC801890
		lfs f2, float_neg180_bom_00007164@l(r5)
		lfs f5, float_270_bom_0000703c@l(r4)
		bl drawBG
		opword 0x480000C0
		lis r4, float_1_bom_00006ffc@ha
		lis r6, float_neg180_bom_00007164@ha
		lfs f3, float_1_bom_00006ffc@l(r4)
		lis r5, float_16_bom_0000715c@ha
		lis r4, float_180_bom_000070c8@ha
		lfs f1, float_neg180_bom_00007164@l(r6)
		opword 0xFC801890
		lfs f2, float_16_bom_0000715c@l(r5)
		lfs f5, float_180_bom_000070c8@l(r4)
		bl drawBG
		opword 0x2C1A0000
		opword 0x41820090
		lis r3, gp@ha
		addi r3, r3, gp@l
		opword 0x80630000
		opword 0x8003001C
		opword 0x540007BF
		opword 0x40820078
		lis r3, sight_wp@ha
		lwz r4, sight_wp@l(r3)
		opword 0x80640020
		opword 0x38030001
		opword 0x90040020
		opword 0x48000060
		lis r4, float_1_bom_00006ffc@ha
		lis r6, float_180_bom_000070c8@ha
		lfs f3, float_1_bom_00006ffc@l(r4)
		lis r5, float_neg16_bom_00007160@ha
		lis r4, zero_bom_00007004@ha
		lfs f1, float_180_bom_000070c8@l(r6)
		opword 0xFC801890
		lfs f2, float_neg16_bom_00007160@l(r5)
		lfs f5, zero_bom_00007004@l(r4)
		bl drawBG
		opword 0x2C1A0000
		opword 0x41820030
		lis r3, gp@ha
		addi r3, r3, gp@l
		opword 0x80630000
		opword 0x8003001C
		opword 0x540007BF
		opword 0x40820018
		lis r3, sight_wp@ha
		lwz r4, sight_wp@l(r3)
		opword 0x80640024
		opword 0x38030001
		opword 0x90040024
		opword 0x3B390001
		opword 0x2C190004
		opword 0x4180FE48
		lis r4, sight_wp@ha
		lis r3, dat_bom_00006360@ha
		addi r4, r4, sight_wp@l
		lwz r0, dat_bom_00006360@l(r3)
		opword 0x80840000
		opword 0x90010010
		opword 0x80640000
		opword 0x80A40020
		opword 0x806300A0
		opword 0x7CA4FE70
		opword 0x7C802A78
		opword 0x80630000
		opword 0x7F240050
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
		opword 0xCBEA0000
		addi r31, r11, sight_wp@l
		opword 0xC3C90000
		addi r28, r7, vec3_bom_00006370@l
		opword 0xC3A80000
		addi r27, r6, vec3_bom_00006364@l
		opword 0x83A10010
		opword 0x3B400000
		lfd f28, double_to_int_bom_00007030@l(r5)
		opword 0x3FC04330
		lfs f27, float_neg220_bom_00007168@l(r4)
		lfs f26, zero_bom_00007004@l(r3)
		opword 0x38A0000A
		opword 0x807F0000
		opword 0x7C192BD6
		opword 0x38810244
		opword 0x80630000
		opword 0x806300A0
		opword 0x80630000
		opword 0x7C0029D6
		opword 0x7CA0C850
		opword 0x3B05000D
		opword 0x7F05C378
		bl TEXGetGXTexObjFromPalette
		opword 0x38610244
		bl GXGetTexObjWidth
		opword 0x5460043E
		opword 0x811B0008
		opword 0x90010334
		opword 0x207A0002
		opword 0x3803FFFF
		opword 0x817C0000
		opword 0x93C10330
		opword 0x6C008000
		opword 0x815C0004
		opword 0x7F03C378
		opword 0xC8010330
		opword 0x3881008C
		opword 0x813C0008
		opword 0x38A100A4
		opword 0xEC00F828
		opword 0x9001032C
		opword 0x80FB0000
		opword 0x38C10014
		opword 0x93C10328
		opword 0xEC3E0032
		opword 0xC8010328
		opword 0x801B0004
		opword 0xEC21E82A
		opword 0x916100B0
		opword 0xEC00E028
		opword 0x914100B4
		opword 0x912100B8
		opword 0xEC01D83A
		opword 0x90E10098
		opword 0x9001009C
		opword 0xD3C100B0
		opword 0xD3C100B4
		opword 0x816100B0
		opword 0xD3C100B8
		opword 0x814100B4
		opword 0xD0010098
		opword 0x812100B8
		opword 0xD341009C
		opword 0x80E10098
		opword 0x8001009C
		opword 0x93A10014
		opword 0x916100A4
		opword 0x914100A8
		opword 0x912100AC
		opword 0x910100A0
		opword 0x90E1008C
		opword 0x90010090
		opword 0x91010094
		bl winTexSet
		opword 0x3800000A
		opword 0x3B5A0001
		opword 0x7F3903D6
		opword 0x2C1A0002
		opword 0x4180FEF4
		lis r4, sight_wp@ha
		lis r3, dat_bom_00006360@ha
		addi r4, r4, sight_wp@l
		lwz r0, dat_bom_00006360@l(r3)
		opword 0x80840000
		opword 0x90010008
		opword 0x80640000
		opword 0x80A40024
		opword 0x806300A0
		opword 0x7CA4FE70
		opword 0x7C802A78
		opword 0x80630000
		opword 0x7F240050
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
		opword 0xCB4A0000
		addi r27, r11, sight_wp@l
		opword 0xC3690000
		addi r30, r7, vec3_bom_00006370@l
		opword 0xC3880000
		addi r31, r6, vec3_bom_00006364@l
		opword 0x83A10008
		opword 0x3B400000
		lfd f29, double_to_int_bom_00007030@l(r5)
		opword 0x3F804330
		lfs f30, float_200_bom_0000716c@l(r4)
		lfs f31, zero_bom_00007004@l(r3)
		opword 0x38A0000A
		opword 0x807B0000
		opword 0x7C192BD6
		opword 0x38810224
		opword 0x80630000
		opword 0x806300A0
		opword 0x80630000
		opword 0x7C0029D6
		opword 0x7CA0C850
		opword 0x3B05000D
		opword 0x7F05C378
		bl TEXGetGXTexObjFromPalette
		opword 0x38610224
		bl GXGetTexObjWidth
		opword 0x5460043E
		opword 0x811F0008
		opword 0x90010334
		opword 0x207A0002
		opword 0x3803FFFF
		opword 0x817E0000
		opword 0x93810330
		opword 0x6C008000
		opword 0x815E0004
		opword 0x7F03C378
		opword 0xC8010330
		opword 0x3881005C
		opword 0x813E0008
		opword 0x38A10074
		opword 0xEC00D028
		opword 0x9001032C
		opword 0x80FF0000
		opword 0x38C1000C
		opword 0x93810328
		opword 0xEC3B0032
		opword 0xC8010328
		opword 0x801F0004
		opword 0xEC21E02A
		opword 0x91610080
		opword 0xEC00E828
		opword 0x91410084
		opword 0x91210088
		opword 0xEC01F03A
		opword 0x90E10068
		opword 0x9001006C
		opword 0xD3610080
		opword 0xD3610084
		opword 0x81610080
		opword 0xD3610088
		opword 0x81410084
		opword 0xD0010068
		opword 0x81210088
		opword 0xD3E1006C
		opword 0x80E10068
		opword 0x8001006C
		opword 0x93A1000C
		opword 0x91610074
		opword 0x91410078
		opword 0x9121007C
		opword 0x91010070
		opword 0x90E1005C
		opword 0x90010060
		opword 0x91010064
		bl winTexSet
		opword 0x3800000A
		opword 0x3B5A0001
		opword 0x7F3903D6
		opword 0x2C1A0002
		opword 0x4180FEF4
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 sight(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x2C040000
		opword 0x90010014
		opword 0x41820084
		opword 0x38600028
		bl _mapAlloc
		lis r5, sight_wp@ha
		opword 0x38800000
		addi r6, r5, sight_wp@l
		opword 0x38A00028
		opword 0x90660000
		bl memset
		opword 0x38600000
		lis r4, sight_wp@ha
		opword 0x38000005
		opword 0x7C661B78
		addi r5, r4, sight_wp@l
		opword 0x7C0903A6
		opword 0x80850000
		opword 0x38030004
		opword 0x38630004
		opword 0x7CC4012E
		opword 0x4200FFF0
		bl rand
		lis r4, sight_wp@ha
		addi r4, r4, sight_wp@l
		opword 0x80840000
		opword 0x90640020
		bl rand
		lis r4, sight_wp@ha
		opword 0x38000005
		addi r5, r4, sight_wp@l
		opword 0x80850000
		opword 0x90640024
		opword 0x80650000
		opword 0x9003001C
		lis r3, sight_wp@ha
		addi r3, r3, sight_wp@l
		opword 0x80630000
		opword 0x80030000
		opword 0x28000000
		opword 0x40820070
		bl getMarioStDvdRoot
		lis r5, bom_01_str_00000ED0@ha
		lis r4, bom_01_str_00000ED8@ha
		opword 0x7C661B78
		opword 0x38600004
		addi r7, r4, bom_01_str_00000ED8@l
		addi r5, r5, bom_01_str_00000ED0@l
		opword 0x38800000
		opword 0x4CC63182
		bl fileAsyncf
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x480000A0
		bl getMarioStDvdRoot
		lis r4, bom_01_str_00000ED0@ha
		lis r6, bom_01_str_00000ED8@ha
		opword 0x7C651B78
		opword 0x38600004
		addi r4, r4, bom_01_str_00000ED0@l
		addi r6, r6, bom_01_str_00000ED8@l
		opword 0x4CC63182
		bl fileAllocf
		lis r4, sight_wp@ha
		addi r4, r4, sight_wp@l
		opword 0x80840000
		opword 0x90640000
		lis r3, sight_wp@ha
		addi r3, r3, sight_wp@l
		opword 0x80630000
		opword 0x8003001C
		opword 0x2C000006
		opword 0x40820024
		opword 0x80630000
		bl fileFree
		lis r3, sight_wp@ha
		addi r3, r3, sight_wp@l
		opword 0x80630000
		bl _mapFree
		opword 0x38600002
		opword 0x48000034
		opword 0x2C000005
		opword 0x41820028
		lis r3, float_800_bom_0000711c@ha
		lis r4, disp_sight@ha
		addi r6, r3, float_800_bom_0000711c@l
		opword 0xC0260000
		addi r5, r4, disp_sight@l
		opword 0x38600008
		opword 0x38800000
		opword 0x38C00000
		bl dispEntry
		opword 0x38600000
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop

s32 sight_dir(EventEntry* event, BOOL isFirstCall) {
    sight_wp->dir = evtGetValue(event, event->args[0]);
#endif
    return EVT_RETURN_DONE;
}

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
#endif
#ifndef NONMATCHING
s32 bom_flag(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    s32 on = evtGetValue(event, args[0]);
    s32 mask = evtGetValue(event, args[1]);
    BomWork* wp = lp->address;

    if (on) {
        wp->flags |= mask;
#endif
    } else {
#ifdef NONMATCHING
        y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a;
#endif
#ifndef NONMATCHING
        wp->flags &= ~mask;
#endif
    }
#ifdef NONMATCHING
    return a;
}

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

#pragma opt_propagation off
#pragma opt_lifetimes off
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
#pragma opt_propagation reset
#pragma opt_lifetimes reset

static s32 depth(EventEntry* event, BOOL isFirstCall) {
    dispEntry(CAMERA_2D, 1000.0f, 0, depthDisp, NULL);
    return EVT_RETURN_BLOCK;
}

static s32 make_name(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    static char name[64];

    sprintf(name, "S_hikari%d", evtGetValue(event, args[0]));
    evtSetValue(event, args[1], (s32)name);
#endif
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
s32 make_ext_table_minnnanokoe(EventEntry* event, BOOL isFirstCall) {
    s32 i;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 bom_fall(EventEntry* event, BOOL isFirstCall) {
	char _af_pad[24];
	asm volatile {
		lis r3, lp@ha
		addi r3, r3, lp@l
		opword 0x80630000
		opword 0x83630000
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
		opword 0xCBCC0000
		lis r4, bom_01_str_00000EB4@ha
		opword 0xC3EB0000
		lfs f25, 0x0(r10)
		opword 0x7C7A1B78
		opword 0xC3490000
		addi r31, r4, bom_01_str_00000EB4@l
		opword 0xC3680000
		addi r30, r5, lp@l
		opword 0xC3870000
		opword 0x3B200000
		opword 0xC3A60000
		opword 0x3B000000
		opword 0x3FA04330
		opword 0x48000128
		opword 0x381800B0
		opword 0x3860007F
		opword 0x7C7B01AE
		bl rand
		opword 0x6C608000
		stw r29, _af_pad+0(r1)
		opword 0x807A000C
		opword 0x9001000C
		opword 0xC8010008
		opword 0xEC00F028
		opword 0xEC1F0032
		opword 0xEC00C824
		opword 0xD003000C
		bl rand
		opword 0x6C608000
		opword 0x93A10010
		opword 0x807A000C
		opword 0x90010014
		opword 0xC8010010
		opword 0xEC00F028
		opword 0xEC1A0032
		opword 0xEC00C824
		opword 0xEC1B002A
		opword 0xD003001C
		bl rand
		opword 0x6C608000
		opword 0x93A10018
		opword 0x807A000C
		opword 0x3AE00000
		opword 0x9001001C
		opword 0xC8010018
		opword 0xEC00F028
		opword 0xEC1C0032
		opword 0xEC00C824
		opword 0xEC1D002A
		opword 0xD003002C
		opword 0x807E0000
		lwz r22, 0x0(r3)
		opword 0x3B960008
		opword 0x48000020
		opword 0x7F83E378
		opword 0x7FE4FB78
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x3AF70001
		opword 0x3B9C0014
		opword 0x801600A8
		opword 0x7C170000
		opword 0x4180FFDC
		opword 0x801600A8
		opword 0x7C170000
		opword 0x40800048
		opword 0x7F96C214
		opword 0x801C00D0
		opword 0x7C00B800
		opword 0x41820038
		opword 0x7EE00734
		opword 0x901C00D0
		bl rand
		lis r4, gp@ha
		opword 0x7C60FE70
		addi r4, r4, gp@l
		opword 0x80840000
		opword 0x80A4003C
		opword 0x80840038
		opword 0x7C651814
		opword 0x907C00DC
		opword 0x7C040114
		opword 0x901C00D8
		opword 0x3B390001
		opword 0x3B180030
		opword 0x3B5A0020
		opword 0x801B0004
		opword 0x7C190000
		opword 0x4180FED4
		opword 0x38600002
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
static void pose_init(void) {
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		lis r3, lp@ha
		lis r4, ext_data@ha
		opword 0x90010044
		addi r5, r3, lp@l
		lis r3, zero_bom_00007038@ha
		addi r0, r4, ext_data@l
		opword 0xBF810030
		addi r4, r3, zero_bom_00007038@l
		opword 0x38610008
		opword 0x7C1E0378
		opword 0x3BA00000
		opword 0x80A50000
		opword 0x83E50000
		bl strcpy
		opword 0x3800FFFF
		opword 0x901F00A8
		opword 0x807E0004
		opword 0x38810008
		bl strcmp
		opword 0x2C030000
		opword 0x41820020
		opword 0x809E0004
		opword 0x38610008
		bl strcpy
		opword 0x807F00A8
		opword 0x7FBCEB78
		opword 0x38030001
		opword 0x901F00A8
		opword 0x801F00A8
		opword 0x38810008
		opword 0x1C600014
		opword 0x38630008
		opword 0x7C7F1A14
		bl strcpy
		opword 0x801F00A8
		opword 0x7C7CE850
		opword 0x38830001
		opword 0x3BBD0001
		opword 0x1C600014
		opword 0x38030014
		opword 0x7F9F012E
		opword 0x801F00A8
		opword 0x1C600014
		opword 0x38030018
		opword 0x7C9F012E
		opword 0x801F00A8
		opword 0xC01E0008
		opword 0x1C600014
		opword 0x38030010
		opword 0x7C1F052E
		opword 0x841E000C
		opword 0x28000000
		opword 0x4082FF70
		opword 0x807F00A8
		opword 0x38030001
		opword 0x901F00A8
		opword 0xBB810030
		opword 0x80010044
		opword 0x7C0803A6
		opword 0x38210040
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
static void pose_main(void) {
	char _af_pad[20];
	asm volatile {
		lis r3, lp@ha
		addi r3, r3, lp@l
		opword 0x80630000
		opword 0x83430000
		bl extGetPosePtr
		lis r7, float_60_bom_000070dc@ha
		lis r6, float_1000_bom_0000705c@ha
		lis r5, float_1_bom_00006ffc@ha
		lis r4, double_to_int_bom_00007030@ha
		lis r8, gp@ha
		lfs f28, float_60_bom_000070dc@l(r7)
		lfs f29, float_1000_bom_0000705c@l(r6)
		opword 0x7C781B78
		lfs f30, float_1_bom_00006ffc@l(r5)
		addi r30, r8, gp@l
		lfd f31, double_to_int_bom_00007030@l(r4)
		opword 0x3B200000
		opword 0x3AE00000
		opword 0x3FE08000
		opword 0x3EC04330
		opword 0x480000C0
		opword 0x807F00F8
		opword 0x7FBABA14
		opword 0x809E0000
		opword 0x380003E8
		opword 0x5463F0BE
		opword 0x80FD00D0
		opword 0x7CC30396
		opword 0x8364003C
		opword 0x801D00DC
		opword 0x38A00000
		opword 0x83840038
		opword 0x7C80D810
		opword 0x1CE70014
		opword 0x801D00D8
		opword 0x7C60E110
		addi r21, r7, 0x8
		opword 0x7EBAAA14
		bl __div2u
		bl __cvt_ull_flt
		opword 0xEC3C0072
		opword 0xC0150008
		opword 0xEC21E824
		opword 0xEC210024
		opword 0xFC01F040
		opword 0x4C411382
		opword 0x40820014
		opword 0x937D00DC
		lis r3, zero_bom_00007004@ha
		lfs f1, zero_bom_00007004@l(r3)
		opword 0x939D00D8
		opword 0x80750010
		opword 0x3B390001
		stw r22, _af_pad+0(r1)
		opword 0x3AF70030
		opword 0x3803FFFF
		opword 0x8075000C
		opword 0x6C008000
		opword 0x9001000C
		opword 0xC8010008
		opword 0xEC00F828
		opword 0xEC000072
		opword 0xFC00001E
		opword 0xD8010010
		opword 0x80010014
		opword 0x7C030214
		opword 0x90180010
		opword 0x3B180020
		opword 0x801A0004
		opword 0x7C190000
		opword 0x4180FF3C
	}
}
#pragma pop

static void pose_change(s32 i, const char* name) {
    BomWork* wp = lp->address; s32 j = 0; BomAnim* a; for (a = wp->anims; j < wp->animCount; j++, a++) { if (strcmp(a->name, name) == 0) { break; } } if (j < wp->animCount && wp->bom[i].anim != j) { wp->bom[i].anim = (s16)j; wp->bom[i].time = gp->renderTime + rand(); }
#endif
}

#ifdef NONMATCHING
void ext_init_minnnanokoe(void) {
    s32 i;
    BomWork* wp;
    ExtPose* pose;
    s32 x;
    s32 z;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 make_ext_table(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, ext_data@ha
		opword 0x38800000
		opword 0x90010014
		addi r3, r3, ext_data@l
		opword 0x38A00174
		bl memset
		lis r4, float_2_bom_0000704c@ha
		lis r3, double_to_int_bom_00007030@ha
		lis r7, bom_01_str_000002B4@ha
		lis r6, ext_data@ha
		lis r5, bom_01_str_00000E10@ha
		lfs f2, float_2_bom_0000704c@l(r4)
		lfd f1, double_to_int_bom_00007030@l(r3)
		opword 0x3800000A
		addi r7, r7, bom_01_str_000002B4@l
		addi r6, r6, ext_data@l
		addi r5, r5, bom_01_str_00000E10@l
		opword 0x39200000
		opword 0x38600000
		opword 0x3C804330
		opword 0x7C0903A6
		opword 0x6D208000
		opword 0x7D061A14
		opword 0x9001000C
		opword 0x39290001
		opword 0x3863000C
		opword 0x90810008
		opword 0xC8010008
		opword 0x90E80000
		opword 0xEC000828
		opword 0x90A80004
		opword 0xEC020032
		opword 0xD0080008
		opword 0x4200FFD0
		lis r4, float_6_bom_000070f0@ha
		lis r3, double_to_int_bom_00007030@ha
		lis r7, bom_01_str_000002B4@ha
		lis r6, ext_data@ha
		lis r5, bom_01_str_00000EB4@ha
		lfs f2, float_6_bom_000070f0@l(r4)
		lfd f1, double_to_int_bom_00007030@l(r3)
		opword 0x38000014
		addi r7, r7, bom_01_str_000002B4@l
		addi r6, r6, ext_data@l
		addi r5, r5, bom_01_str_00000EB4@l
		opword 0x39200000
		opword 0x38600000
		opword 0x3C804330
		opword 0x7C0903A6
		opword 0x6D208000
		opword 0x7D061A14
		opword 0x9001000C
		opword 0x39290001
		opword 0x3863000C
		opword 0x90810008
		opword 0xC8010008
		opword 0x90E80078
		opword 0xEC000828
		opword 0x90A8007C
		opword 0xEC020032
		opword 0xD0080080
		opword 0x4200FFD0
		lis r3, ext_data@ha
		opword 0x38000000
		addi r4, r3, ext_data@l
		opword 0x38600002
		opword 0x90040168
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    lp = smartAlloc(sizeof(BomWork), 1);
    wp = lp->address;
    memset(wp, 0, sizeof(BomWork));
    wp->count = extGetPoseNum();
    pose_init();
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
static void ext_init(void) {
	char _af_pad[48];
	asm volatile {
		opword 0x3C600001
		opword 0x38800001
		opword 0x3863BC30
		bl smartAlloc
		lis r4, lp@ha
		opword 0x3CA00001
		addi r6, r4, lp@l
		opword 0x38800000
		opword 0x90660000
		opword 0x38A5BC30
		opword 0x83030000
		opword 0x7F03C378
		bl memset
		bl extGetPoseNum
		opword 0x90780004
		lis r3, lp@ha
		addi r4, r3, lp@l
		opword 0x3B800000
		opword 0x80A40000
		lis r3, ext_data@ha
		lis r4, zero_bom_00007038@ha
		opword 0x83C50000
		addi r29, r3, ext_data@l
		la r3, _af_pad+0
		addi r4, r4, zero_bom_00007038@l
		bl strcpy
		opword 0x3800FFFF
		opword 0x901E00A8
		opword 0x807D0004
		opword 0x38810008
		bl strcmp
		opword 0x2C030000
		opword 0x41820020
		opword 0x809D0004
		opword 0x38610008
		bl strcpy
		opword 0x807E00A8
		opword 0x7F9BE378
		opword 0x38030001
		opword 0x901E00A8
		opword 0x801E00A8
		opword 0x38810008
		opword 0x1C600014
		opword 0x38630008
		opword 0x7C7E1A14
		bl strcpy
		opword 0x801E00A8
		opword 0x7C7BE050
		opword 0x38830001
		opword 0x3B9C0001
		opword 0x1C600014
		opword 0x38030014
		opword 0x7F7E012E
		opword 0x801E00A8
		opword 0x1C600014
		opword 0x38030018
		opword 0x7C9E012E
		opword 0x801E00A8
		opword 0xC01D0008
		opword 0x1C600014
		opword 0x38030010
		opword 0x7C1E052E
		opword 0x841D000C
		opword 0x28000000
		opword 0x4082FF70
		opword 0x807E00A8
		opword 0x38030001
		opword 0x901E00A8
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
		lis r4, bom_01_str_00000E10@ha
		lis r5, lp@ha
		opword 0xC33B0000
		addi r31, r4, bom_01_str_00000E10@l
		opword 0xCB570000
		opword 0x7C771B78
		opword 0xC3990000
		addi r28, r11, float_0p00761_bom_00007068@l
		opword 0xC3B60000
		addi r29, r7, float_0p03705_bom_0000707c@l
		opword 0xC37A0000
		addi r30, r5, lp@l
		opword 0xC3CC0000
		opword 0x3B200000
		opword 0xC2EA0000
		opword 0x3AC00000
		opword 0xC3090000
		opword 0x3F604330
		opword 0xC3E80000
		opword 0xC2C60000
		opword 0x48000270
		opword 0x7C78B214
		opword 0x38000000
		opword 0xD32300CC
		opword 0xD32300C4
		opword 0x980300B0
		opword 0x80170000
		opword 0x60000007
		opword 0x90170000
		opword 0x8077000C
		bl PSMTXIdentity
		bl rand
		opword 0x6C608000
		opword 0x93610028
		opword 0x9001002C
		opword 0xC8010028
		opword 0xEC00D028
		opword 0xEC1B0032
		fdivs f21, f0, f28
		bl rand
		opword 0x6C608000
		opword 0x93610030
		opword 0xFC15F840
		opword 0xC07C0000
		opword 0x90010034
		opword 0xC8010030
		opword 0xEC00D028
		opword 0xEC1D0032
		opword 0xEC00E024
		opword 0xEC1E002A
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_bom_00007074@ha
		lfs f2, float_1p5708_bom_00007074@l(r3)
		opword 0xFC151040
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC350572
		opword 0xEC63B878
		opword 0xEC63C07A
		opword 0xEC630572
		opword 0x48000078
		opword 0xEC351028
		opword 0xEC420828
		opword 0xEC2200B2
		opword 0xEC63B878
		opword 0xEC63C07A
		opword 0xEC6300B2
		opword 0x4800005C
		lis r3, float_4p7124_bom_00007078@ha
		lfs f1, float_4p7124_bom_00007078@l(r3)
		opword 0xFC150840
		opword 0x40800028
		lis r3, float_3p1416_bom_00007070@ha
		lfs f1, float_3p1416_bom_00007070@l(r3)
		opword 0xEC550828
		opword 0xEC2200B2
		opword 0xEC63B878
		opword 0xEC63C07A
		opword 0xEC6300B2
		opword 0xFC601850
		opword 0x48000028
		lis r3, float_1p5708_bom_00007074@ha
		opword 0xEC350828
		lfs f2, float_1p5708_bom_00007074@l(r3)
		opword 0xEC420828
		opword 0xEC2200B2
		opword 0xEC63B878
		opword 0xEC63C07A
		opword 0xEC6300B2
		opword 0xFC601850
		opword 0xEC2000F2
		opword 0x8077000C
		opword 0xFC15F840
		opword 0xC07D0000
		opword 0xD023000C
		opword 0x8077000C
		opword 0xD323001C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_bom_00007074@ha
		lfs f2, float_1p5708_bom_00007074@l(r3)
		opword 0xFC151040
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC350572
		opword 0xEC63B078
		opword 0xEC63C07A
		opword 0x4800006C
		opword 0xEC351028
		opword 0xEC220828
		opword 0xEC210072
		opword 0xEC63B078
		opword 0xEC63C07A
		opword 0xFC601850
		opword 0x48000050
		lis r3, float_4p7124_bom_00007078@ha
		lfs f1, float_4p7124_bom_00007078@l(r3)
		opword 0xFC150840
		opword 0x40800024
		lis r3, float_3p1416_bom_00007070@ha
		lfs f1, float_3p1416_bom_00007070@l(r3)
		opword 0xEC350828
		opword 0xEC210072
		opword 0xEC63B078
		opword 0xEC63C07A
		opword 0xFC601850
		opword 0x48000020
		lis r3, float_1p5708_bom_00007074@ha
		opword 0xEC350828
		lfs f2, float_1p5708_bom_00007074@l(r3)
		opword 0xEC220828
		opword 0xEC210072
		opword 0xEC63B078
		opword 0xEC63C07A
		opword 0xEC0000F2
		opword 0x8077000C
		opword 0x3AA00000
		opword 0xD003002C
		opword 0x807E0000
		lwz r20, 0x0(r3)
		opword 0x3B540008
		opword 0x48000020
		opword 0x7F43D378
		opword 0x7FE4FB78
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x3AB50001
		opword 0x3B5A0014
		opword 0x801400A8
		opword 0x7C150000
		opword 0x4180FFDC
		opword 0x801400A8
		opword 0x7C150000
		opword 0x40800048
		opword 0x7F54B214
		opword 0x801A00D0
		opword 0x7C00A800
		opword 0x41820038
		opword 0x7EA00734
		opword 0x901A00D0
		bl rand
		lis r4, gp@ha
		opword 0x7C60FE70
		addi r4, r4, gp@l
		opword 0x80840000
		opword 0x80A4003C
		opword 0x80840038
		opword 0x7C651814
		opword 0x907A00DC
		opword 0x7C040114
		opword 0x901A00D8
		opword 0x3B390001
		opword 0x3AD60030
		opword 0x3AF70020
		opword 0x80180004
		opword 0x7C190000
		opword 0x4180FD8C
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
static void ext_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
#endif
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void jump(s32 i, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity) {
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
		opword 0xBF410048
		lis r5, lp@ha
		opword 0xFF600890
		addi r5, r5, lp@l
		opword 0xFF801090
		opword 0x80A50000
		opword 0xFFA01890
		opword 0xFFE02090
		opword 0xFFC02890
		opword 0x83C50000
		opword 0x7C7B1B78
		opword 0x7C9C2378
		bl extGetPosePtr
		lis r4, vec3_bom_0000649c@ha
		opword 0x57662834
		addi r5, r4, vec3_bom_0000649c@l
		opword 0xFC60D890
		opword 0x80050000
		opword 0x1FFB0030
		opword 0x80850004
		opword 0x7FA33214
		opword 0x90010014
		opword 0x80050008
		opword 0x7F5EFA14
		opword 0x90810018
		opword 0xFC80E890
		opword 0xD3610014
		opword 0x9001001C
		opword 0x80010014
		opword 0xD3810018
		opword 0xD3A1001C
		opword 0x80610018
		opword 0x901A00B4
		opword 0x8001001C
		opword 0x907A00B8
		opword 0x901A00BC
		opword 0xD3FA00C0
		opword 0xD3DA00C4
		opword 0x807D000C
		opword 0xC003001C
		opword 0xC023000C
		opword 0xEFDC0028
		opword 0xC043002C
		bl distABf
		opword 0x807D000C
		opword 0xFFE00890
		opword 0xFC60D890
		opword 0xFC80E890
		opword 0xC023000C
		opword 0xC043002C
		bl angleABf
		opword 0xC01A00C0
		opword 0x3C804330
		lis r3, float_0p5_bom_0000700c@ha
		lis r5, double_to_int_bom_00007030@ha
		opword 0xEC1F0024
		lfs f3, float_0p5_bom_0000700c@l(r3)
		opword 0x90810040
		opword 0x38000064
		lfd f5, double_to_int_bom_00007030@l(r5)
		opword 0x90810038
		opword 0xFC00001E
		opword 0xFC20D890
		opword 0xFC40E890
		opword 0xD8010030
		opword 0x80610034
		opword 0xB07A00C8
		opword 0xA87A00C8
		opword 0xC0DA00C4
		opword 0x6C638000
		opword 0x90610044
		opword 0xC8010040
		opword 0x9061003C
		opword 0xEC002828
		opword 0xC8810038
		opword 0xEC1E0024
		opword 0xEC842828
		opword 0xEC860132
		opword 0xEC0400FA
		opword 0xD01A00CC
		opword 0x9B9A00B1
		opword 0x981A00B0
		opword 0x807D000C
		opword 0xC063000C
		opword 0xC083002C
		bl angleABf
		opword 0x38600014
		opword 0xD03D0004
		opword 0x7C1B1BD6
		opword 0x7C0019D6
		opword 0x7C00D851
		opword 0x40820074
		opword 0xA01E0000
		opword 0x540007FF
		opword 0x40820068
		lis r3, vec3_bom_000064a8@ha
		opword 0x80FD000C
		addi r4, r3, vec3_bom_000064a8@l
		opword 0x80C40000
		lis r3, bom_01_str_00000DDC@ha
		opword 0x80A40004
		addi r3, r3, bom_01_str_00000DDC@l
		opword 0x80040008
		opword 0x38810020
		opword 0x90C10008
		opword 0xC007000C
		opword 0x90A1000C
		opword 0xC027001C
		opword 0xD0010008
		opword 0xC007002C
		opword 0x90010010
		opword 0x80C10008
		opword 0xD021000C
		opword 0xD0010010
		opword 0x80A1000C
		opword 0x80010010
		opword 0x90C10020
		opword 0x90A10024
		opword 0x90010028
		bl psndSFXOn_3D
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
		opword 0xBB410048
		opword 0x800100B4
		opword 0x7C0803A6
		opword 0x382100B0
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
static void ext_main(void) {
	char _af_pad[372];
	asm volatile {
		lis r3, lp@ha
		addi r3, r3, lp@l
		opword 0x80630000
		opword 0x83430000
		bl extGetPosePtr
		lis r5, bom_01_str_00000DDC@ha
		lis r4, bom_01_str_00000E58@ha
		addi r31, r5, bom_01_str_00000DDC@l
		lis r6, vec3_bom_000064b4@ha
		addi r28, r4, bom_01_str_00000E58@l
		lis r5, vec3_bom_000064c0@ha
		lis r4, vec3_bom_000064cc@ha
		opword 0x7C791B78
		opword 0x7FFEFB78
		opword 0x7FFDFB78
		addi r20, r6, vec3_bom_000064b4@l
		addi r21, r5, vec3_bom_000064c0@l
		addi r22, r4, vec3_bom_000064cc@l
		opword 0x3B600000
		opword 0x3B000000
		opword 0x3AE00000
		opword 0x48001294
		opword 0x80140000
		add r17, r26, r23
		opword 0x80940004
		opword 0x80740008
		stw r0, _af_pad+180(r1)
		opword 0x80F50000
		opword 0x80D50004
		opword 0x80150008
		opword 0x908100C0
		opword 0x80B60000
		opword 0x906100C4
		opword 0x80760004
		opword 0x8099000C
		opword 0x90E10080
		opword 0xC024000C
		opword 0x90C10084
		opword 0xC044001C
		opword 0xC004002C
		opword 0x90010088
		opword 0x80160008
		opword 0xD0210080
		opword 0xD0410084
		opword 0x81010080
		opword 0xD0010088
		opword 0x80E10084
		opword 0x80C10088
		opword 0x910100B0
		opword 0x90E100B4
		opword 0x90C100B8
		opword 0x90A100A4
		opword 0x906100A8
		opword 0x900100AC
		opword 0x887100B0
		opword 0x7C600774
		opword 0x2C000005
		opword 0x418211F4
		opword 0x4080002C
		opword 0x2C000002
		opword 0x4182055C
		opword 0x40800014
		opword 0x2C000000
		opword 0x41820030
		opword 0x408000E0
		opword 0x480011D4
		opword 0x2C000004
		opword 0x40800E08
		opword 0x480009A8
		opword 0x2C00007F
		opword 0x41821030
		opword 0x408011BC
		opword 0x2C000064
		opword 0x41820DFC
		opword 0x480011B0
		opword 0x386100BC
		opword 0x388100B0
		bl PSVECDistance
		lis r3, float_280_bom_000070a4@ha
		lfs f0, float_280_bom_000070a4@l(r3)
		opword 0xFC010040
		opword 0x4081008C
		opword 0x386100BC
		opword 0x388100B0
		opword 0x38A10098
		bl PSVECSubtract
		opword 0x38610098
		opword 0x7C641B78
		bl PSVECNormalize
		lis r4, float_3_bom_000070a8@ha
		opword 0x38610098
		addi r5, r4, float_3_bom_000070a8@l
		opword 0x388100A4
		opword 0xC0250000
		bl PSVECScale
		opword 0x386100B0
		opword 0x388100A4
		opword 0x7C651B78
		bl PSVECAdd
		opword 0xC00100B0
		lis r3, zero_bom_00007004@ha
		opword 0x8099000C
		lfs f1, zero_bom_00007004@l(r3)
		opword 0xD004000C
		opword 0xFC400890
		opword 0xC00100B4
		opword 0x8079000C
		opword 0xD003001C
		opword 0xC00100B8
		opword 0x8079000C
		opword 0xD003002C
		opword 0xC06100B0
		opword 0xC08100B8
		bl angleABf
		opword 0xD0390004
		opword 0x4800110C
		opword 0x887100B0
		opword 0x38030001
		opword 0x981100B0
		opword 0x480010FC
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_bom_00007030@ha
		opword 0x9061015C
		addi r5, r4, double_to_int_bom_00007030@l
		lis r3, float_6p2832_bom_00007060@ha
		opword 0x90010158
		addi r4, r3, float_6p2832_bom_00007060@l
		opword 0xC8450000
		lis r3, float_32767_bom_000070ac@ha
		opword 0xC8010158
		opword 0xC0240000
		opword 0xEC401028
		lfs f0, float_32767_bom_000070ac@l(r3)
		opword 0xEC2100B2
		opword 0xEF610024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x90610164
		lis r4, double_to_int_bom_00007030@ha
		lis r3, float_30_bom_000070b4@ha
		lfd f1, double_to_int_bom_00007030@l(r4)
		opword 0x90010160
		addi r5, r3, float_30_bom_000070b4@l
		lis r3, float_32767_bom_000070ac@ha
		opword 0xC0450000
		opword 0xC8010160
		addi r4, r3, float_32767_bom_000070ac@l
		lis r3, float_150_bom_000070b0@ha
		opword 0xEC600828
		opword 0xC0240000
		lfs f0, float_150_bom_000070b0@l(r3)
		opword 0xEC4200F2
		opword 0xEC220824
		opword 0xEF80082A
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_bom_00007030@ha
		opword 0x9061016C
		addi r5, r4, double_to_int_bom_00007030@l
		lis r3, float_0p1_bom_00007008@ha
		opword 0x90010168
		addi r4, r3, float_0p1_bom_00007008@l
		opword 0xC8250000
		lis r3, float_32767_bom_000070ac@ha
		opword 0xC8010168
		opword 0xC0440000
		opword 0xEC200828
		lfs f0, float_32767_bom_000070ac@l(r3)
		opword 0xEC220072
		opword 0xEC010024
		opword 0xEFA2002A
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_bom_00007030@ha
		opword 0x90610174
		addi r5, r4, double_to_int_bom_00007030@l
		lis r3, float_32767_bom_000070ac@ha
		opword 0x90010170
		addi r4, r3, float_32767_bom_000070ac@l
		opword 0xC8450000
		lis r5, float_0p03705_bom_0000707c@ha
		opword 0xC8210170
		lis r3, float_3p1416_bom_00007070@ha
		opword 0xC0040000
		lis r4, float_3_bom_000070a8@ha
		opword 0xEC411028
		lfs f1, float_3p1416_bom_00007070@l(r3)
		addi r6, r4, float_3_bom_000070a8@l
		lis r4, float_0p4967_bom_00007080@ha
		opword 0xFC1B0840
		lis r3, float_1_bom_00006ffc@ha
		opword 0xEC420024
		opword 0xC0060000
		lfs f4, float_0p03705_bom_0000707c@l(r5)
		lfs f3, float_0p4967_bom_00007080@l(r4)
		opword 0xEFC0102A
		lfs f2, float_1_bom_00006ffc@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_bom_00007074@ha
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xFC1B0840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC1B06F2
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x48000064
		opword 0xEC1B0828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000048
		lis r3, float_4p7124_bom_00007078@ha
		lfs f0, float_4p7124_bom_00007078@l(r3)
		opword 0xFC1B0040
		opword 0x4080001C
		opword 0xEC1B0828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_bom_00007074@ha
		opword 0xEC1B0028
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_3p1416_bom_00007070@ha
		opword 0xFC002050
		lfs f1, float_3p1416_bom_00007070@l(r3)
		lis r5, float_0p00761_bom_00007068@ha
		lis r4, float_0p16605_bom_0000706c@ha
		lis r3, float_1_bom_00006ffc@ha
		opword 0xFC1B0840
		opword 0xEFFC0032
		lfs f4, float_0p00761_bom_00007068@l(r5)
		lfs f3, float_0p16605_bom_0000706c@l(r4)
		lfs f2, float_1_bom_00006ffc@l(r3)
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_bom_00007074@ha
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xFC1B0840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC1B06F2
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC8406F2
		opword 0x48000070
		opword 0xEC1B0828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0x48000054
		lis r3, float_4p7124_bom_00007078@ha
		lfs f0, float_4p7124_bom_00007078@l(r3)
		opword 0xFC1B0040
		opword 0x40800020
		opword 0xEC3B0828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_bom_00007074@ha
		opword 0xEC1B0028
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		lis r3, lp@ha
		fmuls f26, f28, f4
		addi r3, r3, lp@l
		opword 0x80630000
		opword 0x82430000
		bl extGetPosePtr
		lis r5, vec3_bom_0000649c@ha
		lis r4, float_150_bom_000070b0@ha
		addi r6, r5, vec3_bom_0000649c@l
		opword 0x7E63C214
		opword 0x80A60000
		opword 0x7E32BA14
		opword 0x80060004
		opword 0xFC60D090
		opword 0x90A1005C
		opword 0xFC80F890
		opword 0x80660008
		opword 0xD341005C
		lfs f2, float_150_bom_000070b0@l(r4)
		opword 0x90010060
		opword 0x8001005C
		opword 0x90610064
		opword 0xD0410060
		opword 0xD3E10064
		opword 0x80610060
		opword 0x901100B4
		opword 0x80010064
		opword 0x907100B8
		opword 0x901100BC
		opword 0xD3D100C0
		opword 0xD3B100C4
		opword 0x8073000C
		opword 0xC003001C
		opword 0xC023000C
		opword 0xEF820028
		opword 0xC043002C
		bl distABf
		opword 0x8073000C
		opword 0xFF600890
		opword 0xFC60D090
		opword 0xFC80F890
		opword 0xC023000C
		opword 0xC043002C
		bl angleABf
		opword 0xC01100C0
		opword 0x3C004330
		lis r4, double_to_int_bom_00007030@ha
		lis r3, float_0p5_bom_0000700c@ha
		opword 0xEC1B0024
		addi r5, r4, double_to_int_bom_00007030@l
		addi r4, r3, float_0p5_bom_0000700c@l
		opword 0x90010160
		opword 0xC8A50000
		opword 0x38600002
		opword 0xFC00001E
		opword 0x90010168
		opword 0xC0640000
		opword 0x38000064
		opword 0xFC20D090
		opword 0xD8010170
		opword 0xFC40F890
		opword 0x80810174
		opword 0xB09100C8
		opword 0xA89100C8
		opword 0xC0D100C4
		opword 0x6C848000
		opword 0x90810164
		opword 0xC8010160
		opword 0x9081016C
		opword 0xEC002828
		opword 0xC8810168
		opword 0xEC1C0024
		opword 0xEC842828
		opword 0xEC860132
		opword 0xEC0400FA
		opword 0xD01100CC
		opword 0x987100B1
		opword 0x981100B0
		opword 0x8073000C
		opword 0xC063000C
		opword 0xC083002C
		bl angleABf
		opword 0x38600014
		opword 0xD0330004
		opword 0x7C1B1BD6
		opword 0x7C0019D6
		opword 0x7C00D851
		opword 0x40820D00
		opword 0xA0120000
		opword 0x540007FF
		opword 0x40820CF4
		lis r3, vec3_bom_000064a8@ha
		opword 0x80B3000C
		addi r8, r3, vec3_bom_000064a8@l
		opword 0x7FE3FB78
		opword 0x80E80000
		opword 0x38810050
		opword 0x80C80004
		opword 0x80080008
		opword 0x90E10068
		opword 0xC005000C
		opword 0x90C1006C
		opword 0xC025001C
		opword 0xD0010068
		opword 0xC005002C
		opword 0x90010070
		opword 0x80C10068
		opword 0xD021006C
		opword 0xD0010070
		opword 0x80A1006C
		opword 0x80010070
		opword 0x90C10050
		opword 0x90A10054
		opword 0x90010058
		bl psndSFXOn_3D
		opword 0x48000C90
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_bom_00007030@ha
		opword 0x90610174
		addi r5, r4, double_to_int_bom_00007030@l
		lis r3, float_6p2832_bom_00007060@ha
		opword 0x90010170
		addi r4, r3, float_6p2832_bom_00007060@l
		opword 0xC8450000
		lis r3, float_32767_bom_000070ac@ha
		opword 0xC8010170
		opword 0xC0240000
		opword 0xEC401028
		lfs f0, float_32767_bom_000070ac@l(r3)
		opword 0xEC2100B2
		opword 0xEF610024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061016C
		lis r4, double_to_int_bom_00007030@ha
		lis r3, float_30_bom_000070b4@ha
		lfd f1, double_to_int_bom_00007030@l(r4)
		opword 0x90010168
		addi r5, r3, float_30_bom_000070b4@l
		lis r3, float_32767_bom_000070ac@ha
		opword 0xC0450000
		opword 0xC8010168
		addi r4, r3, float_32767_bom_000070ac@l
		lis r3, float_50_bom_000070b8@ha
		opword 0xEC600828
		opword 0xC0240000
		lfs f0, float_50_bom_000070b8@l(r3)
		opword 0xEC4200F2
		opword 0xEC220824
		opword 0xEF80082A
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_bom_00007030@ha
		opword 0x90610164
		addi r5, r4, double_to_int_bom_00007030@l
		lis r3, float_0p1_bom_00007008@ha
		opword 0x90010160
		addi r4, r3, float_0p1_bom_00007008@l
		opword 0xC8250000
		lis r3, float_32767_bom_000070ac@ha
		opword 0xC8010160
		opword 0xC0440000
		opword 0xEC200828
		lfs f0, float_32767_bom_000070ac@l(r3)
		opword 0xEC220072
		opword 0xEC010024
		opword 0xEFE2002A
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_bom_00007030@ha
		opword 0x9061015C
		addi r5, r4, double_to_int_bom_00007030@l
		lis r3, float_32767_bom_000070ac@ha
		opword 0x90010158
		addi r4, r3, float_32767_bom_000070ac@l
		opword 0xC8450000
		lis r5, float_0p03705_bom_0000707c@ha
		opword 0xC8210158
		lis r3, float_3p1416_bom_00007070@ha
		opword 0xC0040000
		lis r4, float_3_bom_000070a8@ha
		opword 0xEC411028
		lfs f1, float_3p1416_bom_00007070@l(r3)
		addi r6, r4, float_3_bom_000070a8@l
		lis r4, float_0p4967_bom_00007080@ha
		opword 0xFC1B0840
		lis r3, float_1_bom_00006ffc@ha
		opword 0xEC420024
		opword 0xC0060000
		lfs f4, float_0p03705_bom_0000707c@l(r5)
		lfs f3, float_0p4967_bom_00007080@l(r4)
		opword 0xEFC0102A
		lfs f2, float_1_bom_00006ffc@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_bom_00007074@ha
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xFC1B0840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC1B06F2
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x48000064
		opword 0xEC1B0828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000048
		lis r3, float_4p7124_bom_00007078@ha
		lfs f0, float_4p7124_bom_00007078@l(r3)
		opword 0xFC1B0040
		opword 0x4080001C
		opword 0xEC1B0828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_bom_00007074@ha
		opword 0xEC1B0028
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_3p1416_bom_00007070@ha
		opword 0xFC002050
		lfs f1, float_3p1416_bom_00007070@l(r3)
		lis r5, float_0p00761_bom_00007068@ha
		lis r4, float_0p16605_bom_0000706c@ha
		lis r3, float_1_bom_00006ffc@ha
		opword 0xFC1B0840
		opword 0xEFBC0032
		lfs f4, float_0p00761_bom_00007068@l(r5)
		lfs f3, float_0p16605_bom_0000706c@l(r4)
		lfs f2, float_1_bom_00006ffc@l(r3)
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_bom_00007074@ha
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xFC1B0840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC1B06F2
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC8406F2
		opword 0x48000070
		opword 0xEC1B0828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0x48000054
		lis r3, float_4p7124_bom_00007078@ha
		lfs f0, float_4p7124_bom_00007078@l(r3)
		opword 0xFC1B0040
		opword 0x40800020
		opword 0xEC3B0828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_bom_00007074@ha
		opword 0xEC1B0028
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		lis r3, lp@ha
		opword 0xEF9C0132
		addi r3, r3, lp@l
		opword 0x80630000
		opword 0x82630000
		bl extGetPosePtr
		lis r5, vec3_bom_0000649c@ha
		lis r4, float_400_bom_000070bc@ha
		addi r6, r5, vec3_bom_0000649c@l
		opword 0x7E43C214
		opword 0x80A60000
		opword 0x7E33BA14
		opword 0x80060004
		opword 0xFC60E090
		opword 0x90A10038
		opword 0xFC80E890
		opword 0x80660008
		opword 0xD3810038
		lfs f2, float_400_bom_000070bc@l(r4)
		opword 0x9001003C
		opword 0x80010038
		opword 0x90610040
		opword 0xD041003C
		opword 0xD3A10040
		opword 0x8061003C
		opword 0x901100B4
		opword 0x80010040
		opword 0x907100B8
		opword 0x901100BC
		opword 0xD3D100C0
		opword 0xD3F100C4
		opword 0x8072000C
		opword 0xC003001C
		opword 0xC023000C
		opword 0xEF420028
		opword 0xC043002C
		bl distABf
		opword 0x8072000C
		opword 0xFF600890
		opword 0xFC60E090
		opword 0xFC80E890
		opword 0xC023000C
		opword 0xC043002C
		bl angleABf
		opword 0xC01100C0
		opword 0x3C004330
		lis r4, double_to_int_bom_00007030@ha
		lis r3, float_0p5_bom_0000700c@ha
		opword 0xEC1B0024
		addi r5, r4, double_to_int_bom_00007030@l
		addi r4, r3, float_0p5_bom_0000700c@l
		opword 0x90010160
		opword 0xC8A50000
		opword 0x38600003
		opword 0xFC00001E
		opword 0x90010168
		opword 0xC0640000
		opword 0x38000064
		opword 0xFC20E090
		opword 0xD8010170
		opword 0xFC40E890
		opword 0x80810174
		opword 0xB09100C8
		opword 0xA89100C8
		opword 0xC0D100C4
		opword 0x6C848000
		opword 0x90810164
		opword 0xC8010160
		opword 0x9081016C
		opword 0xEC002828
		opword 0xC8810168
		opword 0xEC1A0024
		opword 0xEC842828
		opword 0xEC860132
		opword 0xEC0400FA
		opword 0xD01100CC
		opword 0x987100B1
		opword 0x981100B0
		opword 0x8072000C
		opword 0xC063000C
		opword 0xC083002C
		bl angleABf
		opword 0x38600014
		opword 0xD0320004
		opword 0x7C1B1BD6
		opword 0x7C0019D6
		opword 0x7C00D851
		opword 0x40820894
		opword 0xA0130000
		opword 0x540007FF
		opword 0x40820888
		lis r3, vec3_bom_000064a8@ha
		opword 0x80B2000C
		addi r8, r3, vec3_bom_000064a8@l
		opword 0x7FC3F378
		opword 0x80E80000
		opword 0x3881002C
		opword 0x80C80004
		opword 0x80080008
		opword 0x90E10044
		opword 0xC005000C
		opword 0x90C10048
		opword 0xC025001C
		opword 0xD0010044
		opword 0xC005002C
		opword 0x9001004C
		opword 0x80C10044
		opword 0xD0210048
		opword 0xD001004C
		opword 0x80A10048
		opword 0x8001004C
		opword 0x90C1002C
		opword 0x90A10030
		opword 0x90010034
		bl psndSFXOn_3D
		opword 0x48000824
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_bom_00007030@ha
		opword 0x90610174
		addi r5, r4, double_to_int_bom_00007030@l
		lis r3, float_6p2832_bom_00007060@ha
		opword 0x90010170
		addi r4, r3, float_6p2832_bom_00007060@l
		opword 0xC8450000
		lis r3, float_32767_bom_000070ac@ha
		opword 0xC8010170
		opword 0xC0240000
		opword 0xEC401028
		lfs f0, float_32767_bom_000070ac@l(r3)
		opword 0xEC2100B2
		opword 0xEF610024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_bom_00007030@ha
		opword 0x9061016C
		addi r5, r4, double_to_int_bom_00007030@l
		lis r3, float_70_bom_000070c0@ha
		opword 0x90010168
		addi r4, r3, float_70_bom_000070c0@l
		opword 0xC8450000
		lis r3, float_32767_bom_000070ac@ha
		opword 0xC8010168
		opword 0xC0240000
		opword 0xEC401028
		lfs f0, float_32767_bom_000070ac@l(r3)
		opword 0xEC2100B2
		opword 0xEF810024
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
		opword 0xFC1B0840
		lfs f30, float_3_bom_000070a8@l(r6)
		lfs f4, float_0p03705_bom_0000707c@l(r5)
		lfs f3, float_0p4967_bom_00007080@l(r4)
		lfs f2, float_1_bom_00006ffc@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_bom_00007074@ha
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xFC1B0840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC1B06F2
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x48000064
		opword 0xEC1B0828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000048
		lis r3, float_4p7124_bom_00007078@ha
		lfs f0, float_4p7124_bom_00007078@l(r3)
		opword 0xFC1B0040
		opword 0x4080001C
		opword 0xEC1B0828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_bom_00007074@ha
		opword 0xEC1B0028
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		lis r3, float_3p1416_bom_00007070@ha
		opword 0xFC002050
		lfs f1, float_3p1416_bom_00007070@l(r3)
		lis r5, float_0p00761_bom_00007068@ha
		lis r4, float_0p16605_bom_0000706c@ha
		lis r3, float_1_bom_00006ffc@ha
		opword 0xFC1B0840
		opword 0xEFBC0032
		lfs f4, float_0p00761_bom_00007068@l(r5)
		lfs f3, float_0p16605_bom_0000706c@l(r4)
		lfs f2, float_1_bom_00006ffc@l(r3)
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_bom_00007074@ha
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xFC1B0840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC1B06F2
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC8406F2
		opword 0x48000070
		opword 0xEC1B0828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0x48000054
		lis r3, float_4p7124_bom_00007078@ha
		lfs f0, float_4p7124_bom_00007078@l(r3)
		opword 0xFC1B0040
		opword 0x40800020
		opword 0xEC3B0828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_bom_00007074@ha
		opword 0xEC1B0028
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x38C00064
		opword 0x3C004330
		opword 0x7CBB33D6
		opword 0x90010170
		lis r3, double_to_int_bom_00007030@ha
		lis r7, float_100_bom_00007000@ha
		addi r4, r3, double_to_int_bom_00007030@l
		lfs f2, float_100_bom_00007000@l(r7)
		opword 0x7C0531D6
		lis r3, lp@ha
		opword 0xC8240000
		addi r3, r3, lp@l
		opword 0x80630000
		opword 0x7C00D850
		opword 0x6C008000
		opword 0x82630000
		opword 0x90010174
		opword 0xC8010170
		opword 0xEC000828
		opword 0xEC02002A
		opword 0xEF9C013A
		bl extGetPosePtr
		opword 0x38C00096
		opword 0x3C004330
		opword 0x7CBB33D6
		opword 0x90010168
		lis r4, double_to_int_bom_00007030@ha
		opword 0xFC60E090
		lis r7, vec3_bom_0000649c@ha
		lfd f1, double_to_int_bom_00007030@l(r4)
		opword 0x7C0531D6
		addi r8, r7, vec3_bom_0000649c@l
		lis r5, float_350_bom_000070c4@ha
		opword 0x80E80000
		opword 0x80C80004
		opword 0x7E43C214
		opword 0x7C00D850
		opword 0x90E10014
		opword 0x6C008000
		opword 0x80680008
		opword 0x9001016C
		opword 0x7E33BA14
		lfs f2, float_350_bom_000070c4@l(r5)
		opword 0xFC80E890
		opword 0xC8010168
		opword 0xD3810014
		opword 0xEC000828
		opword 0x80010014
		opword 0x90C10018
		opword 0xEC42002A
		opword 0x9061001C
		opword 0xD0410018
		opword 0xD3A1001C
		opword 0x80610018
		opword 0x901100B4
		opword 0x8001001C
		opword 0x907100B8
		opword 0x901100BC
		opword 0xD3D100C0
		opword 0xD3F100C4
		opword 0x8072000C
		opword 0xC003001C
		opword 0xC023000C
		opword 0xEF420028
		opword 0xC043002C
		bl distABf
		opword 0x8072000C
		opword 0xFF600890
		opword 0xFC60E090
		opword 0xFC80E890
		opword 0xC023000C
		opword 0xC043002C
		bl angleABf
		opword 0xC01100C0
		opword 0x3C004330
		lis r4, double_to_int_bom_00007030@ha
		lis r3, float_0p5_bom_0000700c@ha
		opword 0xEC1B0024
		addi r5, r4, double_to_int_bom_00007030@l
		addi r4, r3, float_0p5_bom_0000700c@l
		opword 0x90010178
		opword 0xC8A50000
		opword 0x38600004
		opword 0xFC00001E
		opword 0x90010158
		opword 0xC0640000
		opword 0x38000064
		opword 0xFC20E090
		opword 0xD8010160
		opword 0xFC40E890
		opword 0x80810164
		opword 0xB09100C8
		opword 0xA89100C8
		opword 0xC0D100C4
		opword 0x6C848000
		opword 0x9081017C
		opword 0xC8010178
		opword 0x9081015C
		opword 0xEC002828
		opword 0xC8810158
		opword 0xEC1A0024
		opword 0xEC842828
		opword 0xEC860132
		opword 0xEC0400FA
		opword 0xD01100CC
		opword 0x987100B1
		opword 0x981100B0
		opword 0x8072000C
		opword 0xC063000C
		opword 0xC083002C
		bl angleABf
		opword 0x38600014
		opword 0xD0320004
		opword 0x7C1B1BD6
		opword 0x7C0019D6
		opword 0x7C00D851
		opword 0x40820438
		opword 0xA0130000
		opword 0x540007FF
		opword 0x4082042C
		lis r3, vec3_bom_000064a8@ha
		opword 0x80B2000C
		addi r8, r3, vec3_bom_000064a8@l
		opword 0x7FA3EB78
		opword 0x80E80000
		opword 0x38810008
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
		opword 0x90C10008
		opword 0x90A1000C
		opword 0x90010010
		bl psndSFXOn_3D
		opword 0x480003C8
		opword 0x38030001
		opword 0x981100B0
		opword 0x480003BC
		opword 0xC01100CC
		opword 0xEC02002A
		opword 0xD004001C
		opword 0xC03100CC
		opword 0xC01100C4
		opword 0xEC010028
		opword 0xD01100CC
		opword 0x8079000C
		opword 0xC07100B4
		opword 0xC023000C
		opword 0xC043002C
		opword 0xC09100BC
		bl angleABf
		lis r4, float_3p1416_bom_00007070@ha
		lis r3, float_180_bom_000070c8@ha
		lfs f2, float_3p1416_bom_00007070@l(r4)
		addi r6, r3, float_180_bom_000070c8@l
		lis r5, float_0p00761_bom_00007068@ha
		lis r4, float_0p16605_bom_0000706c@ha
		opword 0xEC220072
		opword 0xC0060000
		lis r3, float_1_bom_00006ffc@ha
		lfs f5, float_0p00761_bom_00007068@l(r5)
		lfs f4, float_0p16605_bom_0000706c@l(r4)
		opword 0xECC10024
		lfs f3, float_1_bom_00006ffc@l(r3)
		opword 0xFC061040
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_bom_00007074@ha
		lfs f1, float_1p5708_bom_00007074@l(r3)
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
		lis r3, float_4p7124_bom_00007078@ha
		lfs f0, float_4p7124_bom_00007078@l(r3)
		opword 0xFC060040
		opword 0x40800020
		opword 0xEC261028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_bom_00007074@ha
		opword 0xEC060028
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x80F9000C
		lis r3, float_3p1416_bom_00007070@ha
		lfs f1, float_3p1416_bom_00007070@l(r3)
		lis r6, float_0p03705_bom_0000707c@ha
		opword 0xC05100C0
		lis r5, float_0p4967_bom_00007080@ha
		opword 0xC007000C
		opword 0xFC060840
		lis r4, float_1_bom_00006ffc@ha
		lfs f4, float_0p03705_bom_0000707c@l(r6)
		opword 0xEC02017A
		lfs f3, float_0p4967_bom_00007080@l(r5)
		lfs f2, float_1_bom_00006ffc@l(r4)
		opword 0xD007000C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_bom_00007074@ha
		lfs f1, float_1p5708_bom_00007074@l(r3)
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
		lis r3, float_4p7124_bom_00007078@ha
		lfs f0, float_4p7124_bom_00007078@l(r3)
		opword 0xFC060040
		opword 0x4080001C
		opword 0xEC060828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_bom_00007074@ha
		opword 0xEC060028
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x8079000C
		opword 0xFC202050
		opword 0xC05100C0
		opword 0xC003002C
		opword 0xEC02007A
		opword 0xD003002C
		opword 0xA87100C8
		opword 0x3863FFFF
		opword 0x7C600735
		opword 0xB07100C8
		opword 0x408001C4
		opword 0xC01100B4
		opword 0x8079000C
		opword 0xD003000C
		opword 0xC01100B8
		opword 0x8079000C
		opword 0xD003001C
		opword 0xC01100BC
		opword 0x8079000C
		opword 0xD003002C
		opword 0x881100B1
		opword 0x981100B0
		opword 0x48000194
		lis r3, float_neg1000_bom_000070cc@ha
		lfs f0, float_neg1000_bom_000070cc@l(r3)
		opword 0xFC020040
		opword 0x40810184
		lis r3, float_2_bom_0000704c@ha
		lis r5, zero_bom_00007004@ha
		addi r6, r3, float_2_bom_0000704c@l
		lfs f1, zero_bom_00007004@l(r5)
		opword 0xC0060000
		lis r3, float_neg20_bom_000070d0@ha
		opword 0xFC600890
		opword 0xEC020028
		lfs f2, float_neg20_bom_000070d0@l(r3)
		opword 0x38610128
		opword 0xD004001C
		opword 0x80190000
		opword 0x540007FA
		opword 0x90190000
		bl PSMTXTrans
		lis r3, gp@ha
		opword 0x3C004330
		addi r4, r3, gp@l
		opword 0x90010178
		opword 0x80A40000
		lis r3, double_to_int_mask_bom_000070e0@ha
		addi r4, r3, double_to_int_mask_bom_000070e0@l
		opword 0x8005001C
		lis r3, float_100_bom_00007000@ha
		opword 0xC8440000
		opword 0x7C1B0214
		lfs f0, float_100_bom_00007000@l(r3)
		opword 0x9001017C
		opword 0xC8210178
		opword 0xEC211028
		opword 0xEC210024
		bl sin
		lis r3, float_10_bom_00007010@ha
		opword 0xFC400818
		lfs f0, float_10_bom_00007010@l(r3)
		lis r4, float_deg2rad_bom_000070d4@ha
		lfs f1, float_deg2rad_bom_000070d4@l(r4)
		opword 0x386100F8
		opword 0xEC0000B2
		opword 0x3880007A
		opword 0xEC210032
		bl PSMTXRotRad
		lis r3, zero_bom_00007004@ha
		lis r4, float_20_bom_000070d8@ha
		addi r5, r3, zero_bom_00007004@l
		lfs f2, float_20_bom_000070d8@l(r4)
		opword 0xC0250000
		opword 0x386100C8
		opword 0xFC600890
		bl PSMTXTrans
		opword 0x388100F8
		opword 0x38610128
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x388100C8
		opword 0x386100F8
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x8099000C
		opword 0x38610128
		opword 0xC024000C
		opword 0xC044001C
		opword 0xC064002C
		bl PSMTXTrans
		opword 0x80B9000C
		opword 0x38610128
		opword 0x388100C8
		bl PSMTXConcat
		opword 0x38600064
		bl irand
		opword 0x2C030000
		opword 0x40820064
		lis r3, vec3_bom_000064d8@ha
		opword 0x80B9000C
		addi r8, r3, vec3_bom_000064d8@l
		opword 0x7F83E378
		opword 0x80E80000
		opword 0x3881008C
		opword 0x80C80004
		opword 0x80080008
		opword 0x90E10074
		opword 0xC005000C
		opword 0x90C10078
		opword 0xC025001C
		opword 0xD0010074
		opword 0xC005002C
		opword 0x9001007C
		opword 0x80C10074
		opword 0xD0210078
		opword 0xD001007C
		opword 0x80A10078
		opword 0x8001007C
		opword 0x90C1008C
		opword 0x90A10090
		opword 0x90010094
		bl psndSFXOn_3D
		opword 0x3B7B0001
		opword 0x3B180020
		opword 0x3AF70030
		opword 0x3B390020
		opword 0x801A0004
		opword 0x7C1B0000
		opword 0x4180ED68
		lis r3, lp@ha
		addi r3, r3, lp@l
		opword 0x80630000
		opword 0x82830000
		bl extGetPosePtr
		lis r7, float_60_bom_000070dc@ha
		lis r6, float_1000_bom_0000705c@ha
		lis r5, float_1_bom_00006ffc@ha
		lis r4, double_to_int_bom_00007030@ha
		lis r8, gp@ha
		lfs f30, float_60_bom_000070dc@l(r7)
		lfs f29, float_1000_bom_0000705c@l(r6)
		opword 0x7C721B78
		lfs f28, float_1_bom_00006ffc@l(r5)
		addi r24, r8, gp@l
		lfd f27, double_to_int_bom_00007030@l(r4)
		opword 0x3A600000
		opword 0x3B200000
		opword 0x3EE08000
		opword 0x3F404330
		opword 0x480000C0
		opword 0x807700F8
		opword 0x7E34CA14
		opword 0x80980000
		opword 0x380003E8
		opword 0x5463F0BE
		opword 0x80F100D0
		opword 0x7CC30396
		opword 0x82C4003C
		opword 0x801100DC
		opword 0x38A00000
		opword 0x82A40038
		opword 0x7C80B010
		opword 0x1CE70014
		opword 0x801100D8
		opword 0x7C60A910
		opword 0x3B670008
		opword 0x7F74DA14
		bl __div2u
		bl __cvt_ull_flt
		opword 0xEC3E0072
		opword 0xC01B0008
		opword 0xEC21E824
		opword 0xEC210024
		opword 0xFC01E040
		opword 0x4C411382
		opword 0x40820014
		opword 0x92D100DC
		lis r3, zero_bom_00007004@ha
		lfs f1, zero_bom_00007004@l(r3)
		opword 0x92B100D8
		opword 0x807B0010
		opword 0x3A730001
		opword 0x93410178
		opword 0x3B390030
		opword 0x3803FFFF
		opword 0x807B000C
		opword 0x6C008000
		opword 0x9001017C
		opword 0xC8010178
		opword 0xEC00D828
		opword 0xEC000072
		opword 0xFC00001E
		opword 0xD8010170
		opword 0x80010174
		opword 0x7C030214
		opword 0x90120010
		opword 0x3A520020
		opword 0x80140004
		opword 0x7C130000
		opword 0x4180FF3C
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
static void ext_dispent(void) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, lp@ha
		opword 0x90010014
		addi r3, r3, lp@l
		opword 0x80630000
		opword 0x80630000
		opword 0xA0030000
		opword 0x540007FF
		opword 0x40820028
		lis r3, zero_bom_00007004@ha
		lis r4, ext_disp@ha
		addi r6, r3, zero_bom_00007004@l
		opword 0xC0260000
		addi r5, r4, ext_disp@l
		opword 0x38600004
		opword 0x38800001
		opword 0x38C00000
		bl dispEntry
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 taihou_r(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x90010044
		opword 0xDBE10030
		opword 0xF3E10038
		opword 0xDBC10020
		opword 0xF3C10028
		opword 0xDBA10010
		opword 0xF3A10018
		lis r3, double_0p7854_bom_00007088@ha
		lfd f1, double_0p7854_bom_00007088@l(r3)
		bl cos
		lis r3, double_0p7854_bom_00007088@ha
		opword 0xFFE00818
		lfd f1, double_0p7854_bom_00007088@l(r3)
		bl sin
		lis r3, float_100_bom_00007000@ha
		opword 0xFC400818
		lfs f0, float_100_bom_00007000@l(r3)
		lis r4, zero_bom_00007004@ha
		lfs f1, zero_bom_00007004@l(r4)
		opword 0xEFC000B2
		opword 0xFC400890
		opword 0xFC600890
		opword 0xFC80F090
		bl angleABf
		lis r3, float_100_bom_00007000@ha
		lis r4, zero_bom_00007004@ha
		opword 0xFFA00850
		lfs f0, float_100_bom_00007000@l(r3)
		lfs f1, zero_bom_00007004@l(r4)
		opword 0xFC80F090
		opword 0xEC6007F2
		opword 0xFC400890
		bl angleABf
		opword 0xFFC00850
		lis r3, bom_01_str_000002E4@ha
		addi r3, r3, bom_01_str_000002E4@l
		bl effNameToPtr
		opword 0xFC20E890
		opword 0xFC40F090
		bl effKemuTestSetRxRz
		lis r3, bom_01_str_000002F8@ha
		addi r3, r3, bom_01_str_000002F8@l
		bl effNameToPtr
		opword 0xFC20E890
		opword 0xFC40F090
		bl effRippleN64SetRxRz
		opword 0x38600002
		opword 0xE3E10038
		opword 0xCBE10030
		opword 0xE3C10028
		opword 0xCBC10020
		opword 0xE3A10018
		opword 0x80010044
		opword 0xCBA10010
		opword 0x7C0803A6
		opword 0x38210040
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
static void depthDisp(CameraId camera, void* param) {
	char _af_pad[80];
	asm volatile {
		opword 0x3C80FD05
		opword 0x7C781B78
		opword 0x38840F85
		opword 0x38600000
		bl evtGetValue
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_bom_00007030@ha
		opword 0x9061005C
		addi r5, r4, double_to_int_bom_00007030@l
		lis r3, float_100_bom_00007000@ha
		opword 0x90010058
		addi r4, r3, float_100_bom_00007000@l
		opword 0xC8450000
		opword 0x7F03C378
		opword 0xC8210058
		opword 0xC0040000
		opword 0xEC211028
		opword 0xEF010024
		bl camGetPtr
		opword 0x7C7C1B78
		opword 0x38600260
		opword 0x388001E0
		opword 0x38A00004
		opword 0x38C00000
		opword 0x38E00000
		bl GXGetTexBufferSize
		opword 0x38800003
		bl smartAlloc
		opword 0x7C781B78
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00260
		opword 0x38C001E0
		bl GXSetTexCopySrc
		opword 0x38600260
		opword 0x388001E0
		opword 0x38A00004
		opword 0x38C00000
		bl GXSetTexCopyDst
		opword 0x80780000
		opword 0x38800000
		bl GXCopyTex
		bl GXPixModeSync
		opword 0x80980000
		la r3, _af_pad+0
		opword 0x38A00260
		opword 0x38C001E0
		opword 0x38E00004
		opword 0x39000000
		opword 0x39200000
		opword 0x39400000
		bl GXInitTexObj
		lis r4, zero_bom_00007004@ha
		opword 0x38610008
		addi r5, r4, zero_bom_00007004@l
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
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x38600001
		opword 0x38800004
		opword 0x38A00005
		opword 0x38C00000
		bl GXSetBlendMode
		opword 0x38600001
		bl GXSetZCompLoc
		opword 0x38600007
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetAlphaCompare
		opword 0x38600000
		opword 0x38800003
		opword 0x38A00000
		bl GXSetZMode
		opword 0x38600000
		bl GXSetNumChans
		opword 0x38600004
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0x39000002
		opword 0x39200002
		bl GXSetChanCtrl
		opword 0x38600008
		bl GXSetNumTexGens
		opword 0x38600008
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
		opword 0xC3980000
		opword 0xCBAC0000
		addi r30, r10, float_0p00761_bom_00007068@l
		opword 0xC3CB0000
		addi r31, r6, float_0p03705_bom_0000707c@l
		opword 0xC3490000
		addi r24, r3, zero_bom_00007004@l
		opword 0xC3680000
		opword 0x3B600000
		opword 0xC3E70000
		opword 0x3B400000
		opword 0xC3250000
		opword 0x3FA04330
		lfs f23, 0x0(r4)
		opword 0x6F608000
		opword 0x93A10058
		opword 0xC05E0000
		opword 0x9001005C
		opword 0xC8010058
		opword 0xEC00E828
		opword 0xEC1C0032
		opword 0xEC6007B2
		opword 0xFC03F840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_bom_00007074@ha
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xFC030840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC0300F2
		opword 0xEC42D038
		opword 0xEC42D83A
		opword 0xEC4200F2
		opword 0x48000078
		opword 0xEC030828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC42D038
		opword 0xEC42D83A
		opword 0xEC420072
		opword 0x4800005C
		lis r3, float_4p7124_bom_00007078@ha
		lfs f0, float_4p7124_bom_00007078@l(r3)
		opword 0xFC030040
		opword 0x40800028
		lis r3, float_3p1416_bom_00007070@ha
		lfs f0, float_3p1416_bom_00007070@l(r3)
		opword 0xEC230028
		opword 0xEC010072
		opword 0xEC42D038
		opword 0xEC42D83A
		opword 0xEC420072
		opword 0xFC401050
		opword 0x48000028
		lis r3, float_1p5708_bom_00007074@ha
		opword 0xEC030028
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC42D038
		opword 0xEC42D83A
		opword 0xEC420072
		opword 0xFC401050
		opword 0xFC03F840
		opword 0xC09F0000
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_bom_00007074@ha
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xFC030840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC0300F2
		opword 0xEC84C838
		opword 0xEC84D83A
		opword 0x4800006C
		opword 0xEC030828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC84C838
		opword 0xEC84D83A
		opword 0xFC802050
		opword 0x48000050
		lis r3, float_4p7124_bom_00007078@ha
		lfs f0, float_4p7124_bom_00007078@l(r3)
		opword 0xFC030040
		opword 0x40800024
		lis r3, float_3p1416_bom_00007070@ha
		lfs f0, float_3p1416_bom_00007070@l(r3)
		opword 0xEC030028
		opword 0xEC000032
		opword 0xEC84C838
		opword 0xEC84D83A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_bom_00007074@ha
		opword 0xEC030028
		lfs f1, float_1p5708_bom_00007074@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC84C838
		opword 0xEC84D83A
		opword 0xEC3800B2
		opword 0xC0780000
		opword 0xEC180132
		opword 0x38610028
		opword 0xEC21B824
		opword 0xEC40B824
		bl PSMTXTrans
		opword 0x3B3A001E
		opword 0x38610028
		opword 0x7F24CB78
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x7F63DB78
		opword 0x7F26CB78
		opword 0x38800001
		opword 0x38A00004
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7F63DB78
		opword 0x38800007
		bl GXSetTevKColorSel
		opword 0x7F63DB78
		opword 0x38800007
		bl GXSetTevKAlphaSel
		opword 0x7F63DB78
		opword 0x7F64DB78
		opword 0x38A00000
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F63DB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F63DB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F600034
		opword 0x38E00000
		opword 0x5419D97F
		opword 0x41820008
		opword 0x38E0000F
		opword 0x7F63DB78
		opword 0x3880000F
		opword 0x38A00008
		opword 0x38C0000E
		bl GXSetTevColorIn
		opword 0x2C190000
		opword 0x7F63DB78
		opword 0x38800007
		opword 0x38A00004
		opword 0x38C00006
		opword 0x38E00000
		opword 0x41820008
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x7F63DB78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B7B0001
		opword 0x3B5A0003
		opword 0x2C1B0008
		opword 0x4180FD84
		opword 0x387C011C
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
		opword 0x38600002
		bl GXSetCullMode
		bl GXClearVtxDesc
		opword 0x38600009
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x3860000D
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x38800009
		opword 0x38A00001
		opword 0x38C00003
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x38600000
		opword 0x3880000D
		opword 0x38A00001
		opword 0x38C00003
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x38600080
		opword 0x38800000
		opword 0x38A00004
		bl GXBegin
		opword 0x3900FED0
		opword 0x3CE0CC01
		opword 0xB1078000
		opword 0x38C000F0
		opword 0x38A00000
		opword 0x38800130
		opword 0xB0C78000
		opword 0x38600001
		opword 0x3800FF10
		opword 0xB0A78000
		opword 0xB0A78000
		opword 0xB0A78000
		opword 0xB0878000
		opword 0xB0C78000
		opword 0xB0A78000
		opword 0xB0678000
		opword 0xB0A78000
		opword 0xB0878000
		opword 0xB0078000
		opword 0xB0A78000
		opword 0xB0678000
		opword 0xB0678000
		opword 0xB1078000
		opword 0xB0078000
		opword 0xB0A78000
		opword 0xB0A78000
		opword 0xB0678000
		bl sysWaitDrawSync
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
static s32 depth(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, float_1000_bom_0000705c@ha
		lis r4, depthDisp@ha
		addi r6, r3, float_1000_bom_0000705c@l
		opword 0x90010014
		opword 0xC0260000
		addi r5, r4, depthDisp@l
		opword 0x38600008
		opword 0x38800000
		opword 0x38C00000
		bl dispEntry
		opword 0x80010014
		opword 0x38600000
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
static s32 make_name(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		opword 0xBFC10008
		opword 0x7C7E1B78
		opword 0x83E30018
		opword 0x809F0000
		bl evtGetValue
		lis r4, bom_01_str_00000E18@ha
		lis r6, g5_name_s915@ha
		opword 0x7C651B78
		addi r3, r6, g5_name_s915@l
		addi r4, r4, bom_01_str_00000E18@l
		opword 0x4CC63182
		bl sprintf
		lis r3, g5_name_s915@ha
		opword 0x809F0004
		addi r5, r3, g5_name_s915@l
		opword 0x7FC3F378
		bl evtSetValue
		opword 0xBBC10008
		opword 0x38600002
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 make_ext_table_minnnanokoe(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, ext_data@ha
		opword 0x38800000
		opword 0x90010014
		addi r3, r3, ext_data@l
		opword 0x38A00174
		bl memset
		lis r4, float_4_bom_00007044@ha
		lis r3, double_to_int_bom_00007030@ha
		lis r7, bom_01_str_000002B4@ha
		lis r6, ext_data@ha
		lis r5, bom_01_str_00000E08@ha
		lfs f2, float_4_bom_00007044@l(r4)
		lfd f1, double_to_int_bom_00007030@l(r3)
		opword 0x3800000A
		addi r7, r7, bom_01_str_000002B4@l
		addi r6, r6, ext_data@l
		addi r5, r5, bom_01_str_00000E08@l
		opword 0x39200000
		opword 0x38600000
		opword 0x3C804330
		opword 0x7C0903A6
		opword 0x6D208000
		opword 0x7D061A14
		opword 0x9001000C
		opword 0x39290001
		opword 0x3863000C
		opword 0x90810008
		opword 0xC8010008
		opword 0x90E80000
		opword 0xEC000828
		opword 0x90A80004
		opword 0xEC020032
		opword 0xD0080008
		opword 0x4200FFD0
		lis r4, float_2_bom_0000704c@ha
		lis r3, double_to_int_bom_00007030@ha
		lis r7, bom_01_str_000002B4@ha
		lis r6, ext_data@ha
		lis r5, bom_01_str_00000E10@ha
		lfs f2, float_2_bom_0000704c@l(r4)
		lfd f1, double_to_int_bom_00007030@l(r3)
		opword 0x38000014
		addi r7, r7, bom_01_str_000002B4@l
		addi r6, r6, ext_data@l
		addi r5, r5, bom_01_str_00000E10@l
		opword 0x39200000
		opword 0x38600000
		opword 0x3C804330
		opword 0x7C0903A6
		opword 0x6D208000
		opword 0x7D061A14
		opword 0x9001000C
		opword 0x39290001
		opword 0x3863000C
		opword 0x90810008
		opword 0xC8010008
		opword 0x90E80078
		opword 0xEC000828
		opword 0x90A8007C
		opword 0xEC020032
		opword 0xD0080080
		opword 0x4200FFD0
		lis r3, ext_data@ha
		opword 0x38000000
		addi r4, r3, ext_data@l
		opword 0x38600002
		opword 0x90040168
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void ext_init_minnnanokoe(void) {
	char _af_pad[40];
	asm volatile {
		opword 0x3C600001
		opword 0x38800001
		opword 0x3863BC30
		bl smartAlloc
		lis r4, lp@ha
		opword 0x3CA00001
		addi r6, r4, lp@l
		opword 0x38800000
		opword 0x90660000
		opword 0x38A5BC30
		opword 0x83230000
		opword 0x7F23CB78
		bl memset
		bl extGetPoseNum
		opword 0x90790004
		lis r3, lp@ha
		addi r4, r3, lp@l
		opword 0x3BC00000
		opword 0x80A40000
		lis r3, ext_data@ha
		lis r4, zero_bom_00007038@ha
		opword 0x83850000
		addi r31, r3, ext_data@l
		la r3, _af_pad+0
		addi r4, r4, zero_bom_00007038@l
		bl strcpy
		opword 0x3800FFFF
		opword 0x901C00A8
		opword 0x807F0004
		opword 0x38810008
		bl strcmp
		opword 0x2C030000
		opword 0x41820020
		opword 0x809F0004
		opword 0x38610008
		bl strcpy
		opword 0x807C00A8
		opword 0x7FDDF378
		opword 0x38030001
		opword 0x901C00A8
		opword 0x801C00A8
		opword 0x38810008
		opword 0x1C600014
		opword 0x38630008
		opword 0x7C7C1A14
		bl strcpy
		opword 0x801C00A8
		opword 0x7C7DF050
		opword 0x38830001
		opword 0x3BDE0001
		opword 0x1C600014
		opword 0x38030014
		opword 0x7FBC012E
		opword 0x801C00A8
		opword 0x1C600014
		opword 0x38030018
		opword 0x7C9C012E
		opword 0x801C00A8
		opword 0xC01F0008
		opword 0x1C600014
		opword 0x38030010
		opword 0x7C1C052E
		opword 0x841F000C
		opword 0x28000000
		opword 0x4082FF70
		opword 0x807C00A8
		opword 0x38030001
		opword 0x901C00A8
		bl extGetPosePtr
		lis r6, zero_bom_00007004@ha
		lis r5, double_to_int_bom_00007030@ha
		addi r7, r5, double_to_int_bom_00007030@l
		lis r4, float_270_bom_0000703c@ha
		addi r8, r6, zero_bom_00007004@l
		lis r5, lp@ha
		addi r6, r4, float_270_bom_0000703c@l
		lis r4, bom_01_str_00000E08@ha
		lfs f29, 0x0(r8)
		opword 0x7C781B78
		opword 0xCBC70000
		addi r31, r4, bom_01_str_00000E08@l
		opword 0xC3E60000
		addi r30, r5, lp@l
		opword 0x3B400000
		opword 0x3AE00000
		opword 0x3FA04330
		opword 0x48000160
		opword 0x7C79BA14
		opword 0x38000005
		opword 0xD3A300CC
		opword 0xD3A300C4
		opword 0x980300B0
		opword 0x80180000
		opword 0x60000003
		opword 0x90180000
		opword 0x8078000C
		bl PSMTXIdentity
		bl rand
		opword 0x3880000E
		opword 0x38C0000A
		opword 0x7C1A23D6
		opword 0x7CA333D6
		opword 0x7C0021D6
		opword 0x7C8531D6
		opword 0x7C00D050
		opword 0x1C00001E
		opword 0x7C641850
		add r22, r0, r3
		opword 0x3AD6FF33
		bl rand
		opword 0x38E00014
		opword 0x38A0000E
		opword 0x7CC33BD6
		opword 0x6EC08000
		opword 0x9001002C
		opword 0x3B800000
		opword 0x8098000C
		opword 0x93A10028
		opword 0x7C1A2BD6
		opword 0xC8010028
		opword 0x93A10030
		opword 0xEC00F028
		opword 0xD004000C
		opword 0x8098000C
		opword 0x7CA639D6
		opword 0xD3A4001C
		opword 0x8098000C
		opword 0x1C000014
		opword 0x7C651850
		opword 0x200000BE
		opword 0x7C001A14
		opword 0x6C008000
		opword 0x90010034
		opword 0xC8010030
		opword 0xEC00F028
		opword 0xD004002C
		opword 0xD3F80004
		opword 0x807E0000
		opword 0x82C30000
		opword 0x3B760008
		opword 0x48000020
		opword 0x7F63DB78
		opword 0x7FE4FB78
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x3B9C0001
		opword 0x3B7B0014
		opword 0x801600A8
		opword 0x7C1C0000
		opword 0x4180FFDC
		opword 0x801600A8
		opword 0x7C1C0000
		opword 0x40800048
		opword 0x7F76BA14
		opword 0x801B00D0
		opword 0x7C00E000
		opword 0x41820038
		opword 0x7F800734
		opword 0x901B00D0
		bl rand
		lis r4, gp@ha
		opword 0x7C60FE70
		addi r4, r4, gp@l
		opword 0x80840000
		opword 0x80A4003C
		opword 0x80840038
		opword 0x7C651814
		opword 0x907B00DC
		opword 0x7C040114
		opword 0x901B00D8
		opword 0x3B5A0001
		opword 0x3AF70030
		opword 0x3B180020
		opword 0x80190004
		opword 0x7C1A0000
		opword 0x4180FE9C
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void jump_minnnanokoe(s32 i, f32 h) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFA0
		opword 0x7C0802A6
		opword 0x90010064
		opword 0xDBE10050
		opword 0xF3E10058
		opword 0xBFA10044
		lis r4, lp@ha
		opword 0x7C7E1B78
		lwz r3, lp@l(r4)
		opword 0xFFE00890
		opword 0x83A30000
		bl extGetPosePtr
		opword 0x57C02834
		lis r4, vec3_bom_00006ea4@ha
		addi r6, r4, vec3_bom_00006ea4@l
		opword 0x3CE04330
		opword 0x7FE30214
		opword 0x80060000
		opword 0x811F000C
		opword 0x1D3E0030
		opword 0x80A60004
		lis r3, float_0p1_bom_00007008@ha
		opword 0x90010014
		lis r4, zero_bom_00007004@ha
		opword 0xC008000C
		opword 0x80060008
		opword 0x7FBD4A14
		opword 0xD0010014
		addi r10, r3, float_0p1_bom_00007008@l
		opword 0xC028001C
		lis r3, double_to_int_bom_00007030@ha
		opword 0x90A10018
		opword 0x39200014
		opword 0xC008002C
		addi r8, r3, double_to_int_bom_00007030@l
		opword 0x9001001C
		lis r3, float_0p5_bom_0000700c@ha
		opword 0x81610014
		addi r6, r3, float_0p5_bom_0000700c@l
		opword 0xD0210018
		opword 0x38A00005
		lfs f1, zero_bom_00007004@l(r4)
		opword 0x3C60F5DE
		opword 0xD001001C
		opword 0x38830180
		opword 0x81810018
		opword 0x38000064
		opword 0x917D00B4
		opword 0x38600000
		opword 0x8161001C
		opword 0x919D00B8
		opword 0xC00A0000
		opword 0x917D00BC
		opword 0xC8680000
		opword 0xD03D00C0
		opword 0xC0260000
		opword 0xD01D00C4
		opword 0xB13D00C8
		opword 0xA8DD00C8
		opword 0x90E10038
		opword 0x6CC68000
		opword 0xC09D00C4
		opword 0x90C1003C
		opword 0xC8010038
		opword 0x90C10034
		opword 0xEC001828
		opword 0x90E10030
		opword 0xEC1F0024
		opword 0xC8410030
		opword 0xEC421828
		opword 0xEC4400B2
		opword 0xEC02007A
		opword 0xD01D00CC
		opword 0x98BD00B1
		opword 0x981D00B0
		bl evtGetValue
		opword 0x2C030191
		opword 0x4182007C
		opword 0x38600005
		opword 0x7C1E1BD6
		opword 0x7C0019D6
		opword 0x7C00F051
		opword 0x40820068
		lis r3, vec3_bom_00006eb0@ha
		opword 0x80FF000C
		addi r4, r3, vec3_bom_00006eb0@l
		opword 0x80C40000
		lis r3, bom_01_str_00000DDC@ha
		opword 0x80A40004
		addi r3, r3, bom_01_str_00000DDC@l
		opword 0x80040008
		opword 0x38810020
		opword 0x90C10008
		opword 0xC007000C
		opword 0x90A1000C
		opword 0xC027001C
		opword 0xD0010008
		opword 0xC007002C
		opword 0x90010010
		opword 0x80C10008
		opword 0xD021000C
		opword 0xD0010010
		opword 0x80A1000C
		opword 0x80010010
		opword 0x90C10020
		opword 0x90A10024
		opword 0x90010028
		bl psndSFXOn_3D
		opword 0xE3E10058
		opword 0xCBE10050
		opword 0xBBA10044
		opword 0x80010064
		opword 0x7C0803A6
		opword 0x38210060
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

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

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void ext_dispent_minnnanokoe(void) {
#ifdef NONMATCHING
    dispEntry(CAMERA_3D, 0.0f, 1, ext_disp_minnnanokoe, NULL);
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, zero_bom_00007004@ha
		lis r4, ext_disp_minnnanokoe@ha
		addi r6, r3, zero_bom_00007004@l
		opword 0x90010014
		opword 0xC0260000
		addi r5, r4, ext_disp_minnnanokoe@l
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

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
s32 bom1000_jump(EventEntry* event, BOOL isFirstCall) {
#ifdef NONMATCHING
    BomWork* wp = lp->address;
    s32 i = rand() % wp->count;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFB0
		opword 0x7C0802A6
		lis r3, lp@ha
		opword 0x90010054
		addi r3, r3, lp@l
		opword 0xBF810040
		opword 0x80630000
		opword 0x83830000
		bl rand
		opword 0x809C0004
		opword 0x7C0323D6
		opword 0x7C0021D6
		opword 0x7FA01850
		opword 0x1FDD0030
		opword 0x7C7CF214
		opword 0x880300B0
		opword 0x2C000064
		opword 0x418201A4
		lis r3, lp@ha
		addi r3, r3, lp@l
		opword 0x80630000
		opword 0x83830000
		bl extGetPosePtr
		opword 0x57A02834
		lis r4, vec3_bom_00006ea4@ha
		addi r6, r4, vec3_bom_00006ea4@l
		opword 0x3D004330
		opword 0x7FE30214
		opword 0x80060000
		opword 0x80FF000C
		lis r3, zero_bom_00007004@ha
		opword 0x80A60004
		addi r4, r3, zero_bom_00007004@l
		opword 0x90010014
		lis r3, float_0p1_bom_00007008@ha
		opword 0xC007000C
		addi r11, r3, float_0p1_bom_00007008@l
		opword 0x80060008
		lis r3, double_to_int_bom_00007030@ha
		opword 0xD0010014
		addi r9, r3, double_to_int_bom_00007030@l
		opword 0xC027001C
		opword 0x7F9CF214
		opword 0x90A10018
		lis r3, float_10_bom_00007010@ha
		opword 0xC007002C
		addi r6, r3, float_10_bom_00007010@l
		opword 0x9001001C
		lis r3, float_0p5_bom_0000700c@ha
		opword 0x81810014
		addi r7, r3, float_0p5_bom_0000700c@l
		opword 0xD0210018
		opword 0x3C60F5DE
		opword 0xC0240000
		opword 0x39400014
		opword 0xD001001C
		opword 0x38A00005
		opword 0x83C10018
		opword 0x38000064
		opword 0x919C00B4
		opword 0x38830180
		opword 0x8181001C
		opword 0x38600000
		opword 0x93DC00B8
		opword 0xC00B0000
		opword 0x919C00BC
		opword 0xC8690000
		opword 0xD03C00C0
		opword 0xC0260000
		opword 0xD01C00C4
		opword 0xC0470000
		opword 0xB15C00C8
		opword 0xA8DC00C8
		opword 0x91010038
		opword 0x6CC68000
		opword 0xC09C00C4
		opword 0x90C1003C
		opword 0xC8010038
		opword 0x90C10034
		opword 0xEC001828
		opword 0x91010030
		opword 0xEC010024
		opword 0xC8210030
		opword 0xEC211828
		opword 0xEC240072
		opword 0xEC0100BA
		opword 0xD01C00CC
		opword 0x98BC00B1
		opword 0x981C00B0
		bl evtGetValue
		opword 0x2C030191
		opword 0x4182007C
		opword 0x38600005
		opword 0x7C1D1BD6
		opword 0x7C0019D6
		opword 0x7C00E851
		opword 0x40820068
		lis r3, vec3_bom_00006eb0@ha
		opword 0x80FF000C
		addi r4, r3, vec3_bom_00006eb0@l
		opword 0x80C40000
		lis r3, bom_01_str_00000DDC@ha
		opword 0x80A40004
		addi r3, r3, bom_01_str_00000DDC@l
		opword 0x80040008
		opword 0x38810008
		opword 0x90C10020
		opword 0xC007000C
		opword 0x90A10024
		opword 0xC027001C
		opword 0xD0010020
		opword 0xC007002C
		opword 0x90010028
		opword 0x80C10020
		opword 0xD0210024
		opword 0xD0010028
		opword 0x80A10024
		opword 0x80010028
		opword 0x90C10008
		opword 0x90A1000C
		opword 0x90010010
		bl psndSFXOn_3D
		opword 0xBB810040
		opword 0x38600002
		opword 0x80010054
		opword 0x7C0803A6
		opword 0x38210050
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    s32 state = wp->bom[i].state;

    if (state != 100) {
        jump_minnnanokoe(i, 10.0f);
    }
    return EVT_RETURN_DONE;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
static s32 yami_view(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FF90
		opword 0x7C0802A6
		opword 0x90010074
		opword 0x93E1006C
		opword 0x80830018
		opword 0x80840000
		bl evtGetFloat
		lis r3, float_100_bom_00007000@ha
		lis r5, vec3_bom_00006ed4@ha
		addi r5, r5, vec3_bom_00006ed4@l
		lfs f0, float_100_bom_00007000@l(r3)
		lis r4, vec3_bom_00006ebc@ha
		lis r3, vec3_bom_00006ec8@ha
		addi r6, r3, vec3_bom_00006ec8@l
		opword 0xEC00082A
		addi r8, r4, vec3_bom_00006ebc@l
		opword 0x80850008
		opword 0x80080008
		opword 0x3861002C
		opword 0x90810010
		opword 0x83E50000
		opword 0x38810020
		opword 0x90010028
		opword 0x81850004
		opword 0x38A10014
		opword 0x81660000
		opword 0x81460004
		opword 0x81260008
		opword 0x38C10008
		opword 0x80E80000
		opword 0x80080004
		opword 0x93E10008
		opword 0x9181000C
		opword 0xD0210010
		opword 0x91610014
		opword 0x91410018
		opword 0x9121001C
		opword 0x90E10020
		opword 0x90010024
		opword 0xD0010028
		bl C_MTXLookAt
		opword 0x3861002C
		bl envSetYamiView
		opword 0x80010074
		opword 0x38600002
		opword 0x83E1006C
		opword 0x7C0803A6
		opword 0x38210070
	}
#endif
}
#ifdef NONMATCHING

void envSetYamiView(Mtx mtx);

static s32 yami_view(EventEntry* event, BOOL isFirstCall) {
    f32 z = evtGetFloat(event, event->args[0]);
    Mtx mtx;

    C_MTXLookAt(mtx, &(Vec){0.0f, 100.0f, 100.0f + z}, &(Vec){0.0f, 1.0f, 0.0f}, &(Vec){0.0f, 0.0f, z});
    envSetYamiView(mtx);
    return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
#pragma pop
#endif

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

#ifdef NONMATCHING
EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);

#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
static s32 starstone_entry(EventEntry* event, BOOL isFirstCall) {
#ifdef NONMATCHING
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);

    effSetName(effStarStoneEntry(6, x, y, z, 1.0f), name);
    return EVT_RETURN_DONE;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x90010044
		opword 0xDBE10030
		opword 0xF3E10038
		opword 0xDBC10020
		opword 0xF3C10028
		opword 0xBFA10014
		opword 0x7C7D1B78
		opword 0x83E30018
		opword 0x809F0000
		bl evtGetValue
		opword 0x809F0004
		opword 0x7C7E1B78
		opword 0x7FA3EB78
		bl evtGetFloat
		opword 0xFFE00890
		opword 0x809F0008
		opword 0x7FA3EB78
		bl evtGetFloat
		opword 0xFFC00890
		opword 0x809F000C
		opword 0x7FA3EB78
		bl evtGetFloat
		opword 0xFC000890
		lis r3, float_1_bom_00006ffc@ha
		lfs f4, float_1_bom_00006ffc@l(r3)
		opword 0xFC20F890
		opword 0xFC40F090
		opword 0x38600006
		opword 0xFC600090
		bl effStarStoneEntry
		opword 0x7FC4F378
		bl effSetName
		opword 0x38600002
		opword 0xE3E10038
		opword 0xCBE10030
		opword 0xE3C10028
		opword 0xCBC10020
		opword 0xBBA10014
		opword 0x80010044
		opword 0x7C0803A6
		opword 0x38210040
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

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

#ifndef NONMATCHING
#pragma defer_codegen off
#endif
static s32 starstone_set_ry(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 ry = evtGetFloat(event, args[1]);

    ((f32*)effNameToPtr(name)->userdata)[7] = ry;
    return EVT_RETURN_DONE;
}

#ifndef NONMATCHING
#pragma defer_codegen reset
#endif

#ifdef NONMATCHING
EVT_BEGIN(bom1000_minnnanokoe)
    CALL(make_ext_table_minnnanokoe)
    CALL(evt_npc_entry, STRING(((char*)str_000002AC)), STRING(((char*)str_000002B4)))
    CALL(evt_npc_set_position, STRING(((char*)str_000002AC)), 0, -1000, 0)
    CALL(evt_ext_entry, 250, PTR(ext_data), PTR(ext_init_minnnanokoe), PTR(ext_main), PTR(ext_dispent_minnnanokoe))
    RETURN
EVT_END()
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
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
	b L_af_1
L_af_2:
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
L_af_1:
	cmpw r27, r25
	blt L_af_2
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
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void drawBG(s32 id, f32 x, f32 y, f32 sx, f32 sy, f32 rot) {
	asm volatile {
		opword 0x9421FEF0
		opword 0x7C0802A6
		opword 0x90010114
		opword 0xDBE10100
		opword 0xF3E10108
		opword 0xDBC100F0
		opword 0xF3C100F8
		opword 0xDBA100E0
		opword 0xF3A100E8
		opword 0xDB8100D0
		opword 0xF38100D8
		opword 0xDB6100C0
		opword 0xF36100C8
		opword 0xBFC100B8
		opword 0xFF600890
		opword 0x7C7E1B78
		opword 0xFF801090
		opword 0x38600008
		opword 0xFFA01890
		opword 0xFFC02090
		opword 0xFFE02890
		bl camGetPtr
		lis r4, sight_wp@ha
		opword 0x7C7F1B78
		addi r3, r4, sight_wp@l
		opword 0x7FC5F378
		opword 0x80630000
		opword 0x38810008
		opword 0x80630000
		opword 0x806300A0
		opword 0x80630000
		bl TEXGetGXTexObjFromPalette
		opword 0x38610008
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x38600001
		opword 0x38800004
		opword 0x38A00005
		opword 0x38C00000
		bl GXSetBlendMode
		opword 0x38600001
		bl GXSetZCompLoc
		opword 0x38600007
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetAlphaCompare
		opword 0x38600000
		opword 0x38800003
		opword 0x38A00000
		bl GXSetZMode
		opword 0x38600000
		bl GXSetNumChans
		opword 0x38600001
		bl GXSetNumTexGens
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0003C
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x38600001
		bl GXSetNumTevStages
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x38600000
		opword 0x38800003
		bl GXSetTevOp
		opword 0x2C1E0000
		opword 0x40820040
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800006
		opword 0x38A00007
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		bl GXSetTevKAlphaSel
		lis r3, zero_bom_00007004@ha
		opword 0xFC20D890
		lfs f3, zero_bom_00007004@l(r3)
		opword 0xFC40E090
		opword 0x38610088
		bl PSMTXTrans
		lis r3, float_1_bom_00006ffc@ha
		opword 0xFC20E890
		lfs f3, float_1_bom_00006ffc@l(r3)
		opword 0xFC40F090
		opword 0x38610028
		bl PSMTXScale
		lis r4, float_deg2rad_bom_000070d4@ha
		opword 0x38610058
		addi r5, r4, float_deg2rad_bom_000070d4@l
		opword 0x3880007A
		opword 0xC0050000
		opword 0xEC2007F2
		bl PSMTXRotRad
		opword 0x38810028
		opword 0x38610088
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38610028
		opword 0x38810058
		opword 0x38A10088
		bl PSMTXConcat
		opword 0x38810088
		opword 0x387F011C
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38610088
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
		opword 0x38600000
		bl GXSetCullMode
		bl GXClearVtxDesc
		opword 0x38600009
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x3860000D
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x38800009
		opword 0x38A00001
		opword 0x38C00003
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x38600000
		opword 0x3880000D
		opword 0x38A00001
		opword 0x38C00003
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x38600080
		opword 0x38800000
		opword 0x38A00004
		bl GXBegin
		opword 0x38610008
		bl GXGetTexObjWidth
		opword 0x7C7F0734
		opword 0x38610008
		bl GXGetTexObjHeight
		opword 0x7CDF00D0
		opword 0x3CA0CC01
		opword 0xB0C58000
		opword 0x38800000
		opword 0x38000001
		opword 0xB0658000
		opword 0xB0858000
		opword 0xB0858000
		opword 0xB0858000
		opword 0xB0858000
		opword 0xB0658000
		opword 0xB0858000
		opword 0xB0058000
		opword 0xB0858000
		opword 0xB0858000
		opword 0xB0858000
		opword 0xB0858000
		opword 0xB0058000
		opword 0xB0058000
		opword 0xB0C58000
		opword 0xB0858000
		opword 0xB0858000
		opword 0xB0858000
		opword 0xB0058000
		opword 0xE3E10108
		opword 0xCBE10100
		opword 0xE3C100F8
		opword 0xCBC100F0
		opword 0xE3A100E8
		opword 0xCBA100E0
		opword 0xE38100D8
		opword 0xCB8100D0
		opword 0xE36100C8
		opword 0xCB6100C0
		opword 0xBBC100B8
		opword 0x80010114
		opword 0x7C0803A6
		opword 0x38210110
	}
}
#pragma pop
#endif


#ifdef NONMATCHING
// target pad words (G5: section sizes must match or later DOL addresses shift)
#endif
#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#endif
#pragma force_active on
#ifndef NONMATCHING
__declspec(section ".rodata") const u32 dat_bom_00006360 = 0xFFFFFFFF;
__declspec(section ".rodata") const f32 vec3_bom_00006364[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_bom_00006370[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const u32 dat_bom_0000637c = 0xFFFFFFFF;
__declspec(section ".rodata") const u32 dat_bom_00006380 = 0x000000FF;
__declspec(section ".rodata") const f32 vec3_bom_00006384[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_bom_00006390[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_bom_0000639c[3] = {-200.0f, 150.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_bom_000063a8[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_bom_000063b4[3] = {-210.0f, -140.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_bom_000063c0[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const char bom_01_str_00000194[12] = "s_ie_door\0\0";
__declspec(section ".rodata") const char bom_01_str_000001A0[12] = "s_ie_kai\0\0\0";
__declspec(section ".rodata") const char bom_01_str_000001AC[12] = "\x83z\x83\x8f\x83" "C\x83g\0\0\0";
__declspec(section ".rodata") const char bom_01_str_000001B8[16] = "\x83y\x83\x93\x83g\x83\x8a\x83" "b\x83g\0\0\0";
__declspec(section ".rodata") const char bom_01_str_000001C8[12] = "\x83X\x83\x89\x83\x8a\x81[\0\0\0";
__declspec(section ".rodata") const char bom_01_str_000001D4[12] = "A_ie_door_u";
__declspec(section ".rodata") const char bom_01_str_000001E0[12] = "A_ie_door\0\0";
__declspec(section ".rodata") const char bom_01_str_000001EC[12] = "S_ie_naka\0\0";
__declspec(section ".rodata") const char bom_01_str_000001F8[8] = "w_bero\0";
__declspec(section ".rodata") const char bom_01_str_00000200[8] = "bom_04\0";
__declspec(section ".rodata") const char bom_01_str_00000208[8] = "e_bero4";
__declspec(section ".rodata") const char bom_01_str_00000210[8] = "e_bero\0";
__declspec(section ".rodata") const char bom_01_str_00000218[8] = "bom_02\0";
__declspec(section ".rodata") const char bom_01_str_00000220[20] = "stg7_bom_01__2_00\0\0";
__declspec(section ".rodata") const char bom_01_str_00000234[16] = "stg7_bom_01__2\0";
__declspec(section ".rodata") const char bom_01_str_00000244[24] = "SFX_VOICE_MARIO_NOD1_3\0";
__declspec(section ".rodata") const char bom_01_str_0000025C[8] = "M_N_2\0\0";
__declspec(section ".rodata") const f32 vec3_bom_0000649c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_bom_000064a8[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_bom_000064b4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_bom_000064c0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_bom_000064cc[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_bom_000064d8[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const char bom_01_str_000002AC[8] = "dummy\0\0";
__declspec(section ".rodata") const char bom_01_str_000002B4[12] = "c_bom_sen\0\0";
__declspec(section ".rodata") const char bom_01_str_000002C0[28] = "SFX_STG7_CANNON_DISCHARGE1\0";
__declspec(section ".rodata") const char bom_01_str_000002DC[8] = "dekatai";
__declspec(section ".rodata") const char bom_01_str_000002E4[8] = "kemuri\0";
__declspec(section ".rodata") const char bom_01_str_000002EC[12] = "kemuri_test";
__declspec(section ".rodata") const char bom_01_str_000002F8[8] = "ripple\0";
__declspec(section ".rodata") const char bom_01_str_00000300[12] = "ripple_n64\0";
__declspec(section ".rodata") const char bom_01_str_0000030C[12] = "particle\0\0\0";
__declspec(section ".rodata") const char bom_01_str_00000318[4] = "hit";
__declspec(section ".rodata") const char bom_01_str_0000031C[8] = "PKR_D_1";
__declspec(section ".rodata") const char bom_01_str_00000324[8] = "PNK_D_1";
__declspec(section ".rodata") const char bom_01_str_0000032C[4] = "D_1";
__declspec(section ".rodata") const char bom_01_str_00000330[8] = "PYS_D_1";
__declspec(section ".rodata") const char bom_01_str_00000338[8] = "PWD_D_1";
__declspec(section ".rodata") const char bom_01_str_00000340[8] = "PTR_D_1";
__declspec(section ".rodata") const char bom_01_str_00000348[8] = "PCH_D_1";
__declspec(section ".rodata") const char bom_01_str_00000350[24] = "SFX_STG7_SHUTTER_OPEN1\0";
__declspec(section ".rodata") const char bom_01_str_00000368[8] = "\x83j\x83g\x83\x8d\0";
__declspec(section ".rodata") const char bom_01_str_00000370[16] = "stg7_bom_65_a\0\0";
__declspec(section ".rodata") const char bom_01_str_00000380[16] = "stg7_bom_65_b\0\0";
__declspec(section ".rodata") const char bom_01_str_00000390[16] = "stg7_bom_65_c\0\0";
__declspec(section ".rodata") const char bom_01_str_000003A0[12] = "\x83{\x83\x80\x83w\x83" "CD\0\0";
__declspec(section ".rodata") const char bom_01_str_000003AC[16] = "stg7_bom_65_d\0\0";
__declspec(section ".rodata") const char bom_01_str_000003BC[12] = "stg7_bom_63";
__declspec(section ".rodata") const char bom_01_str_000003C8[4] = "me\0";
__declspec(section ".rodata") const char bom_01_str_000003CC[12] = "chika_off\0\0";
__declspec(section ".rodata") const char bom_01_str_000003D8[12] = "jime_ugo\0\0\0";
__declspec(section ".rodata") const char bom_01_str_000003E4[8] = "S_yuka1";
__declspec(section ".rodata") const char bom_01_str_000003EC[8] = "S_yuka2";
__declspec(section ".rodata") const char bom_01_str_000003F4[28] = "SFX_VOICE_MARIO_SURPRISED1\0";
__declspec(section ".rodata") const char bom_01_str_00000410[8] = "M_N_7\0\0";
__declspec(section ".rodata") const char bom_01_str_00000418[24] = "SFX_STG7_FLOOR_OPEN1\0\0\0";
__declspec(section ".rodata") const char bom_01_str_00000430[16] = "hiraku_ss_1_b\0\0";
__declspec(section ".rodata") const char bom_01_str_00000440[16] = "hiraku_ss_1_a\0\0";
__declspec(section ".rodata") const char bom_01_str_00000450[24] = "SFX_STG7_MARIO_FALL1\0\0\0";
__declspec(section ".rodata") const char bom_01_str_00000468[20] = "\x83r\x83r\x83" "A\x83\x93\x82\xb5\x82\xc1\x82\xdb\x96\xb3\x8c\xf8\0";
__declspec(section ".rodata") const char bom_01_str_0000047C[8] = "mario\0\0";
__declspec(section ".rodata") const char bom_01_str_00000484[12] = "stg7_bom_64";
__declspec(section ".rodata") const char bom_01_str_00000490[16] = "stg7_bom_64_01\0";
__declspec(section ".rodata") const char bom_01_str_000004A0[12] = "stg7_bom_66";
__declspec(section ".rodata") const char bom_01_str_000004AC[12] = "stg7_bom_67";
__declspec(section ".rodata") const char bom_01_str_000004B8[12] = "stg7_bom_68";
__declspec(section ".rodata") const char bom_01_str_000004C4[12] = "stg7_bom_69";
__declspec(section ".rodata") const char bom_01_str_000004D0[28] = "SFX_STG7_CANNON_SYS_ACTIVE1";
__declspec(section ".rodata") const char bom_01_str_000004EC[28] = "SFX_STG7_CANNON_SYS_ACTIVE2";
__declspec(section ".rodata") const char bom_01_str_00000508[8] = "kikai\0\0";
__declspec(section ".rodata") const char bom_01_str_00000510[12] = "stg7_bom_70";
__declspec(section ".rodata") const char bom_01_str_0000051C[12] = "stg7_bom_71";
__declspec(section ".rodata") const char bom_01_str_00000528[12] = "stg7_bom_72";
__declspec(section ".rodata") const char bom_01_str_00000534[24] = "SFX_STG7_CANNON_SIREN1\0";
__declspec(section ".rodata") const char bom_01_str_0000054C[12] = "stg7_bom_73";
__declspec(section ".rodata") const char bom_01_str_00000558[12] = "stg7_bom_74";
__declspec(section ".rodata") const char bom_01_str_00000564[24] = "BGM_EVT_STG7_HUGE_GUN1\0";
__declspec(section ".rodata") const char bom_01_str_0000057C[24] = "SFX_STG7_FLOOR_QUAKE1\0\0";
__declspec(section ".rodata") const char bom_01_str_00000594[24] = "SFX_STG7_FLOOR_QUAKE2\0\0";
__declspec(section ".rodata") const char bom_01_str_000005AC[8] = "S_yuka3";
__declspec(section ".rodata") const char bom_01_str_000005B4[12] = "S_hikari\0\0\0";
__declspec(section ".rodata") const char bom_01_str_000005C0[24] = "SFX_STG7_FLOOR_DOWN1\0\0\0";
__declspec(section ".rodata") const char bom_01_str_000005D8[16] = "hiraku_l_1_a\0\0\0";
__declspec(section ".rodata") const char bom_01_str_000005E8[16] = "hiraku_l_1_b\0\0\0";
__declspec(section ".rodata") const char bom_01_str_000005F8[24] = "SFX_STG7_FLOOR_OPEN2\0\0\0";
__declspec(section ".rodata") const char bom_01_str_00000610[12] = "stg7_bom_75";
__declspec(section ".rodata") const char bom_01_str_0000061C[16] = "hiraku_s_1_a\0\0\0";
__declspec(section ".rodata") const char bom_01_str_0000062C[16] = "hiraku_s_1_b\0\0\0";
__declspec(section ".rodata") const char bom_01_str_0000063C[16] = "hiraku_s_2_a\0\0\0";
__declspec(section ".rodata") const char bom_01_str_0000064C[16] = "hiraku_s_2_b\0\0\0";
__declspec(section ".rodata") const char bom_01_str_0000065C[16] = "hiraku_s_3_a\0\0\0";
__declspec(section ".rodata") const char bom_01_str_0000066C[16] = "hiraku_s_3_b\0\0\0";
__declspec(section ".rodata") const char bom_01_str_0000067C[16] = "hiraku_s_4_a\0\0\0";
__declspec(section ".rodata") const char bom_01_str_0000068C[16] = "hiraku_s_4_b\0\0\0";
__declspec(section ".rodata") const char bom_01_str_0000069C[12] = "stg7_bom_76";
__declspec(section ".rodata") const char bom_01_str_000006A8[20] = "SFX_STG7_CANNON_UP1";
__declspec(section ".rodata") const char bom_01_str_000006BC[12] = "S_dekatai\0\0";
__declspec(section ".rodata") const char bom_01_str_000006C8[24] = "SFX_STG7_CANNON_STOP1\0\0";
__declspec(section ".rodata") const char bom_01_str_000006E0[12] = "stg7_bom_77";
__declspec(section ".rodata") const char bom_01_str_000006EC[24] = "SFX_STG7_CANNON_MOVE1\0\0";
__declspec(section ".rodata") const char bom_01_str_00000704[24] = "SFX_STG7_CANNON_STOP2\0\0";
__declspec(section ".rodata") const char bom_01_str_0000071C[12] = "stg7_bom_78";
__declspec(section ".rodata") const char bom_01_str_00000728[8] = "S_moon\0";
__declspec(section ".rodata") const char bom_01_str_00000730[12] = "stg7_bom_79";
__declspec(section ".rodata") const char bom_01_str_0000073C[12] = "stg7_bom_80";
__declspec(section ".rodata") const char bom_01_str_00000748[24] = "SFX_STG7_HATCH_OPEN1\0\0\0";
__declspec(section ".rodata") const char bom_01_str_00000760[8] = "futa\0\0\0";
__declspec(section ".rodata") const char bom_01_str_00000768[12] = "stg7_bom_81";
__declspec(section ".rodata") const char bom_01_str_00000774[8] = "\x91\xba\x92\xb7\0\0\0";
__declspec(section ".rodata") const char bom_01_str_0000077C[24] = "SFX_STG7_BOMB_TOGETHER1";
__declspec(section ".rodata") const char bom_01_str_00000794[12] = "stg7_bom_85";
__declspec(section ".rodata") const char bom_01_str_000007A0[28] = "SFX_STG7_BOMB_TOGETHER1_2\0\0";
__declspec(section ".rodata") const char bom_01_str_000007BC[16] = "stg7_bom_85_1\0\0";
__declspec(section ".rodata") const char bom_01_str_000007CC[16] = "stg7_bom_85_2\0\0";
__declspec(section ".rodata") const char bom_01_str_000007DC[16] = "stg7_bom_85_3\0\0";
__declspec(section ".rodata") const char bom_01_str_000007EC[24] = "SFX_STG7_HATCH_SHUT1\0\0\0";
__declspec(section ".rodata") const char bom_01_str_00000804[16] = "stg7_bom_85_4\0\0";
__declspec(section ".rodata") const char bom_01_str_00000814[16] = "stg7_bom_85_5\0\0";
__declspec(section ".rodata") const char bom_01_str_00000824[16] = "stg7_bom_85_6\0\0";
__declspec(section ".rodata") const char bom_01_str_00000834[12] = "stg7_bom_86";
__declspec(section ".rodata") const char bom_01_str_00000840[12] = "stg7_bom_87";
__declspec(section ".rodata") const char bom_01_str_0000084C[8] = "HAIKEI\0";
__declspec(section ".rodata") const char bom_01_str_00000854[28] = "SFX_VOICE_MARIO_DAMAGED2\0\0\0";
__declspec(section ".rodata") const char bom_01_str_00000870[24] = "SFX_VOICE_MARIO_AC3_4\0\0";
__declspec(section ".rodata") const char bom_01_str_00000888[20] = "SFX_STG7_MARIO_FLY1";
__declspec(section ".rodata") const char bom_01_str_0000089C[24] = "SFX_STG7_MARIO_LIGHT1\0\0";
__declspec(section ".rodata") const char bom_01_str_000008B4[16] = "wangflush_n64\0\0";
__declspec(section ".rodata") const char bom_01_str_000008C4[12] = "stg7_bom_88";
__declspec(section ".rodata") const char bom_01_str_000008D0[12] = "stg7_bom_89";
__declspec(section ".rodata") const char bom_01_str_000008DC[12] = "stg7_bom_90";
__declspec(section ".rodata") const char bom_01_str_000008E8[12] = "stg7_bom_91";
__declspec(section ".rodata") const char bom_01_str_000008F4[8] = "moo_03\0";
__declspec(section ".rodata") const char bom_01_str_000008FC[20] = "stg7_bom_59_04_1\0\0\0";
__declspec(section ".rodata") const char bom_01_str_00000910[20] = "stg7_bom_59_04_2\0\0\0";
__declspec(section ".rodata") const char bom_01_str_00000924[16] = "stg7_bom_02_00\0";
__declspec(section ".rodata") const char bom_01_str_00000934[12] = "stg7_bom_02";
__declspec(section ".rodata") const char bom_01_str_00000940[16] = "stg7_bom_02_1\0\0";
__declspec(section ".rodata") const char bom_01_str_00000950[12] = "stg7_bom_03";
__declspec(section ".rodata") const char bom_01_str_0000095C[16] = "stg7_bom_03_1\0\0";
__declspec(section ".rodata") const char bom_01_str_0000096C[16] = "stg7_bom_04_00\0";
__declspec(section ".rodata") const char bom_01_str_0000097C[12] = "stg7_bom_04";
__declspec(section ".rodata") const char bom_01_str_00000988[16] = "stg7_bom_04_1\0\0";
__declspec(section ".rodata") const char bom_01_str_00000998[12] = "stg7_bom_05";
__declspec(section ".rodata") const char bom_01_str_000009A4[16] = "stg7_bom_05_1\0\0";
__declspec(section ".rodata") const char bom_01_str_000009B4[16] = "stg7_bom_06_00\0";
__declspec(section ".rodata") const char bom_01_str_000009C4[12] = "stg7_bom_06";
__declspec(section ".rodata") const char bom_01_str_000009D0[16] = "stg7_bom_06_1\0\0";
__declspec(section ".rodata") const char bom_01_str_000009E0[12] = "stg7_bom_07";
__declspec(section ".rodata") const char bom_01_str_000009EC[16] = "stg7_bom_07_1\0\0";
__declspec(section ".rodata") const char bom_01_str_000009FC[16] = "stg7_bom_08_00\0";
__declspec(section ".rodata") const char bom_01_str_00000A0C[12] = "stg7_bom_08";
__declspec(section ".rodata") const char bom_01_str_00000A18[16] = "stg7_bom_08_1\0\0";
__declspec(section ".rodata") const char bom_01_str_00000A28[12] = "stg7_bom_09";
__declspec(section ".rodata") const char bom_01_str_00000A34[16] = "stg7_bom_09_1\0\0";
__declspec(section ".rodata") const char bom_01_str_00000A44[16] = "stg7_bom_10_00\0";
__declspec(section ".rodata") const char bom_01_str_00000A54[12] = "stg7_bom_10";
__declspec(section ".rodata") const char bom_01_str_00000A60[12] = "stg7_bom_11";
__declspec(section ".rodata") const char bom_01_str_00000A6C[16] = "stg7_bom_12_00\0";
__declspec(section ".rodata") const char bom_01_str_00000A7C[12] = "stg7_bom_12";
__declspec(section ".rodata") const char bom_01_str_00000A88[12] = "stg7_bom_13";
__declspec(section ".rodata") const char bom_01_str_00000A94[16] = "stg7_bom_14_00\0";
__declspec(section ".rodata") const char bom_01_str_00000AA4[12] = "stg7_bom_14";
__declspec(section ".rodata") const char bom_01_str_00000AB0[12] = "stg7_bom_15";
__declspec(section ".rodata") const char bom_01_str_00000ABC[16] = "stg7_bom_16_00\0";
__declspec(section ".rodata") const char bom_01_str_00000ACC[12] = "stg7_bom_16";
__declspec(section ".rodata") const char bom_01_str_00000AD8[12] = "stg7_bom_17";
__declspec(section ".rodata") const char bom_01_str_00000AE4[16] = "stg7_bom_18_00\0";
__declspec(section ".rodata") const char bom_01_str_00000AF4[12] = "stg7_bom_18";
__declspec(section ".rodata") const char bom_01_str_00000B00[12] = "stg7_bom_19";
__declspec(section ".rodata") const char bom_01_str_00000B0C[16] = "stg7_bom_59_02\0";
__declspec(section ".rodata") const char bom_01_str_00000B1C[16] = "stg7_bom_59_03\0";
__declspec(section ".rodata") const char bom_01_str_00000B2C[16] = "stg7_bom_59_04\0";
__declspec(section ".rodata") const char bom_01_str_00000B3C[16] = "stg7_bom_59_05\0";
__declspec(section ".rodata") const char bom_01_str_00000B4C[20] = "stg7_bom_09_01_01\0\0";
__declspec(section ".rodata") const char bom_01_str_00000B60[12] = "\x82R\x90l\x96\xba\x82`\0\0\0";
__declspec(section ".rodata") const char bom_01_str_00000B6C[20] = "stg7_bom_09_01_02\0\0";
__declspec(section ".rodata") const char bom_01_str_00000B80[12] = "\x82R\x90l\x96\xba\x82" "a\0\0\0";
__declspec(section ".rodata") const char bom_01_str_00000B8C[20] = "stg7_bom_09_01_03\0\0";
__declspec(section ".rodata") const char bom_01_str_00000BA0[12] = "\x82R\x90l\x96\xba\x82" "b\0\0\0";
__declspec(section ".rodata") const char bom_01_str_00000BAC[20] = "stg7_bom_09_01_04\0\0";
__declspec(section ".rodata") const char bom_01_str_00000BC0[20] = "stg7_bom_09_01_05\0\0";
__declspec(section ".rodata") const char bom_01_str_00000BD4[20] = "stg7_bom_09_01_06\0\0";
__declspec(section ".rodata") const char bom_01_str_00000BE8[20] = "stg7_bom_09_01_07\0\0";
__declspec(section ".rodata") const char bom_01_str_00000BFC[20] = "stg7_bom_09_01_08\0\0";
__declspec(section ".rodata") const char bom_01_str_00000C10[20] = "stg7_bom_09_01_09\0\0";
__declspec(section ".rodata") const char bom_01_str_00000C24[12] = "c_dance_r\0\0";
__declspec(section ".rodata") const char bom_01_str_00000C30[8] = "\x97x\x82\xe8\x8eq\0";
__declspec(section ".rodata") const char bom_01_str_00000C38[12] = "c_dance_p\0\0";
__declspec(section ".rodata") const char bom_01_str_00000C44[16] = "\x97x\x82\xe8\x8eq\x83s\x83\x93\x83N\0\0\0";
__declspec(section ".rodata") const char bom_01_str_00000C54[12] = "c_dance_k\0\0";
__declspec(section ".rodata") const char bom_01_str_00000C60[12] = "\x97x\x82\xe8\x8eq\x89\xa9\x97\xce\0";
__declspec(section ".rodata") const f32 vec3_bom_00006ea4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_bom_00006eb0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_bom_00006ebc[3] = {0.0f, 100.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_bom_00006ec8[3] = {0.0f, 1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_bom_00006ed4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const char bom_01_str_00000CA8[8] = "S_bom01";
__declspec(section ".rodata") const char bom_01_str_00000CB0[12] = "starstone\0\0";
__declspec(section ".rodata") const char bom_01_str_00000CBC[16] = "stg8_las_148_65";
__declspec(section ".rodata") const char bom_01_str_00000CCC[16] = "stg8_las_148_66";
__declspec(section ".rodata") const char bom_01_str_00000CDC[16] = "stg8_las_148_67";
__declspec(section ".rodata") const char bom_01_str_00000CEC[16] = "stg8_las_148_68";
__declspec(section ".rodata") const char bom_01_str_00000CFC[16] = "stg8_las_148_69";
__declspec(section ".rodata") const char bom_01_str_00000D0C[16] = "stg8_las_148_70";
__declspec(section ".rodata") const char bom_01_str_00000D1C[16] = "stg8_las_148_71";
__declspec(section ".rodata") const char bom_01_str_00000D2C[8] = "las_29\0";
__declspec(section ".rodata") const char bom_01_str_00000D34[12] = "minnnanokoe";
__declspec(section ".rodata") const char bom_01_str_00000D40[16] = "stg7_bom_09_01\0";
__declspec(section ".rodata") const char bom_01_str_00000D50[20] = "BGM_EVT_STG8_VOICE1";
__declspec(section ".rodata") const char bom_01_str_00000D64[16] = "BGM_STG7_BOM1\0\0";
__declspec(section ".rodata") const char bom_01_str_00000D74[16] = "ENV_STG7_BOM2\0\0";
__declspec(section ".rodata") const char bom_01_str_00000D84[8] = "group10";
__declspec(section ".rodata") const char bom_01_str_00000D8C[8] = "group11";
__declspec(section ".rodata") const char bom_01_str_00000D94[8] = "group12";
__declspec(section ".rodata") const char bom_01_str_00000D9C[8] = "group13";
__declspec(section ".rodata") const char bom_01_str_00000DA4[8] = "group14";
__declspec(section ".rodata") const char bom_01_str_00000DAC[8] = "group15";
__declspec(section ".rodata") const char bom_01_str_00000DB4[8] = "A_chika";
__declspec(section ".rodata") const char bom_01_str_00000DBC[8] = "item_00";
__declspec(section ".rodata") const f32 float_1_bom_00006ffc = 1.0f;
__declspec(section ".rodata") const f32 float_100_bom_00007000 = 100.0f;
__declspec(section ".rodata") const f32 zero_bom_00007004 = 0.0f;
__declspec(section ".rodata") const f32 float_0p1_bom_00007008 = 0.1f;
__declspec(section ".rodata") const f32 float_0p5_bom_0000700c = 0.5f;
__declspec(section ".rodata") const f32 float_10_bom_00007010 = 10.0f;
__declspec(section ".rodata") const char bom_01_str_00000DDC[24] = "SFX_STG7_BOMB_TOGETHER2";
__declspec(section ".rodata") const f64 double_to_int_bom_00007030 = 4503601774854144.0;
__declspec(section ".rodata") const u32 zero_bom_00007038 = 0x00000000;
__declspec(section ".rodata") const f32 float_270_bom_0000703c = 270.0f;
__declspec(section ".rodata") const char bom_01_str_00000E08[4] = "S_1";
__declspec(section ".rodata") const f32 float_4_bom_00007044 = 4.0f;
__declspec(section ".rodata") const char bom_01_str_00000E10[4] = "R_1";
__declspec(section ".rodata") const f32 float_2_bom_0000704c = 2.0f;
__declspec(section ".rodata") const char bom_01_str_00000E18[12] = "S_hikari%d\0";
__declspec(section ".rodata") const f32 float_1000_bom_0000705c = 1000.0f;
__declspec(section ".rodata") const f32 float_6p2832_bom_00007060 = 6.2831855f;
__declspec(section ".rodata") const f32 float_0p125_bom_00007064 = 0.125f;
__declspec(section ".rodata") const f32 float_0p00761_bom_00007068 = 0.00761f;
__declspec(section ".rodata") const f32 float_0p16605_bom_0000706c = 0.16605f;
__declspec(section ".rodata") const f32 float_3p1416_bom_00007070 = 3.1415927f;
__declspec(section ".rodata") const f32 float_1p5708_bom_00007074 = 1.5707964f;
__declspec(section ".rodata") const f32 float_4p7124_bom_00007078 = 4.712389f;
__declspec(section ".rodata") const f32 float_0p03705_bom_0000707c = 0.03705f;
__declspec(section ".rodata") const f32 float_0p4967_bom_00007080 = 0.4967f;
__declspec(section ".rodata") const f64 double_0p7854_bom_00007088 = 0.7853981852531433;
__declspec(section ".rodata") const char bom_01_str_00000E58[20] = "SFX_STG7_BOMB_FALL1";
__declspec(section ".rodata") const f32 float_280_bom_000070a4 = 280.0f;
__declspec(section ".rodata") const f32 float_3_bom_000070a8 = 3.0f;
__declspec(section ".rodata") const f32 float_32767_bom_000070ac = 32767.0f;
__declspec(section ".rodata") const f32 float_150_bom_000070b0 = 150.0f;
__declspec(section ".rodata") const f32 float_30_bom_000070b4 = 30.0f;
__declspec(section ".rodata") const f32 float_50_bom_000070b8 = 50.0f;
__declspec(section ".rodata") const f32 float_400_bom_000070bc = 400.0f;
__declspec(section ".rodata") const f32 float_70_bom_000070c0 = 70.0f;
__declspec(section ".rodata") const f32 float_350_bom_000070c4 = 350.0f;
__declspec(section ".rodata") const f32 float_180_bom_000070c8 = 180.0f;
__declspec(section ".rodata") const f32 float_neg1000_bom_000070cc = -1000.0f;
__declspec(section ".rodata") const f32 float_neg20_bom_000070d0 = -20.0f;
__declspec(section ".rodata") const f32 float_deg2rad_bom_000070d4 = 0.017453292f;
__declspec(section ".rodata") const f32 float_20_bom_000070d8 = 20.0f;
__declspec(section ".rodata") const f32 float_60_bom_000070dc = 60.0f;
__declspec(section ".rodata") const f64 double_to_int_mask_bom_000070e0 = 4503599627370496.0;
__declspec(section ".rodata") const f32 float_500_bom_000070e8 = 500.0f;
__declspec(section ".rodata") const char bom_01_str_00000EB4[4] = "S_2";
__declspec(section ".rodata") const f32 float_6_bom_000070f0 = 6.0f;
__declspec(section ".rodata") const f32 float_600_bom_000070f4 = 600.0f;
__declspec(section ".rodata") const f32 float_300_bom_000070f8 = 300.0f;
__declspec(section ".rodata") const f32 float_3700_bom_000070fc = 3700.0f;
__declspec(section ".rodata") const f32 float_neg650_bom_00007100 = -650.0f;
__declspec(section ".rodata") const f32 float_neg450_bom_00007104 = -450.0f;
__declspec(section ".rodata") const char bom_01_str_00000ED0[8] = "%s/%s\0\0";
__declspec(section ".rodata") const char bom_01_str_00000ED8[12] = "taihou.tpl\0";
__declspec(section ".rodata") const f32 float_800_bom_0000711c = 800.0f;
__declspec(section ".rodata") const f32 float_neg1_bom_00007120 = -1.0f;
__declspec(section ".rodata") const f32 float_neg100_bom_00007124 = -100.0f;
__declspec(section ".rodata") const f32 float_neg60_bom_00007128 = -60.0f;
__declspec(section ".rodata") const f32 float_0p6_bom_0000712c = 0.6f;
__declspec(section ".rodata") const f32 float_90_bom_00007130 = 90.0f;
__declspec(section ".rodata") const f32 float_126_bom_00007134 = 126.0f;
__declspec(section ".rodata") const f32 float_162_bom_00007138 = 162.0f;
__declspec(section ".rodata") const f32 float_120_bom_0000713c = 120.0f;
__declspec(section ".rodata") const f32 float_110_bom_00007140 = 110.0f;
__declspec(section ".rodata") const f32 float_neg160_bom_00007144 = -160.0f;
__declspec(section ".rodata") const f32 float_0p8_bom_00007148 = 0.8f;
__declspec(section ".rodata") const f32 float_230_bom_0000714c = 230.0f;
__declspec(section ".rodata") const f32 float_neg170_bom_00007150 = -170.0f;
__declspec(section ".rodata") const f32 float_neg240_bom_00007154 = -240.0f;
__declspec(section ".rodata") const f32 float_neg190_bom_00007158 = -190.0f;
__declspec(section ".rodata") const f32 float_16_bom_0000715c = 16.0f;
__declspec(section ".rodata") const f32 float_neg16_bom_00007160 = -16.0f;
__declspec(section ".rodata") const f32 float_neg180_bom_00007164 = -180.0f;
__declspec(section ".rodata") const f32 float_neg220_bom_00007168 = -220.0f;
__declspec(section ".rodata") const f32 float_200_bom_0000716c = 200.0f;
#endif

#ifdef NONMATCHING // all-C link: pool objects the C names, defined on the asm side only
__declspec(section ".data") const char str_00000194[12] = "s_ie_door\0\0";
__declspec(section ".data") const char str_000001A0[12] = "s_ie_kai\0\0\0";
__declspec(section ".data") const char str_000001AC[12] = "\x83z\x83\x8f\x83" "C\x83g\0\0\0";
__declspec(section ".data") const char str_000001B8[16] = "\x83y\x83\x93\x83g\x83\x8a\x83" "b\x83g\0\0\0";
__declspec(section ".data") const char str_000001C8[12] = "\x83X\x83\x89\x83\x8a\x81[\0\0\0";
__declspec(section ".data") const char str_000001D4[12] = "A_ie_door_u";
__declspec(section ".data") const char str_000001E0[12] = "A_ie_door\0\0";
__declspec(section ".data") const char str_000001EC[12] = "S_ie_naka\0\0";
__declspec(section ".data") const char str_000001F8[8] = "w_bero\0";
__declspec(section ".data") const char str_00000200[8] = "bom_04\0";
__declspec(section ".data") const char str_00000208[8] = "e_bero4";
__declspec(section ".data") const char str_00000210[8] = "e_bero\0";
__declspec(section ".data") const char str_00000218[8] = "bom_02\0";
__declspec(section ".data") const char str_00000220[20] = "stg7_bom_01__2_00\0\0";
__declspec(section ".data") const char str_00000234[16] = "stg7_bom_01__2\0";
__declspec(section ".data") const char str_00000244[24] = "SFX_VOICE_MARIO_NOD1_3\0";
__declspec(section ".data") const char str_0000025C[8] = "M_N_2\0\0";
__declspec(section ".data") const char str_000002AC[8] = "dummy\0\0";
__declspec(section ".data") const char str_000002B4[12] = "c_bom_sen\0\0";
__declspec(section ".data") const char str_000002C0[28] = "SFX_STG7_CANNON_DISCHARGE1\0";
__declspec(section ".data") const char str_000002DC[8] = "dekatai";
__declspec(section ".data") const char str_000002E4[8] = "kemuri\0";
__declspec(section ".data") const char str_000002EC[12] = "kemuri_test";
__declspec(section ".data") const char str_000002F8[8] = "ripple\0";
__declspec(section ".data") const char str_00000300[12] = "ripple_n64\0";
__declspec(section ".data") const char str_0000030C[12] = "particle\0\0\0";
__declspec(section ".data") const char str_00000318[4] = "hit";
__declspec(section ".data") const char str_0000031C[8] = "PKR_D_1";
__declspec(section ".data") const char str_00000324[8] = "PNK_D_1";
__declspec(section ".data") const char str_0000032C[4] = "D_1";
__declspec(section ".data") const char str_00000330[8] = "PYS_D_1";
__declspec(section ".data") const char str_00000338[8] = "PWD_D_1";
__declspec(section ".data") const char str_00000340[8] = "PTR_D_1";
__declspec(section ".data") const char str_00000348[8] = "PCH_D_1";
__declspec(section ".data") const char str_00000350[24] = "SFX_STG7_SHUTTER_OPEN1\0";
__declspec(section ".data") const char str_00000368[8] = "\x83j\x83g\x83\x8d\0";
__declspec(section ".data") const char str_00000370[16] = "stg7_bom_65_a\0\0";
__declspec(section ".data") const char str_00000380[16] = "stg7_bom_65_b\0\0";
__declspec(section ".data") const char str_00000390[16] = "stg7_bom_65_c\0\0";
__declspec(section ".data") const char str_000003A0[12] = "\x83{\x83\x80\x83w\x83" "CD\0\0";
__declspec(section ".data") const char str_000003AC[16] = "stg7_bom_65_d\0\0";
__declspec(section ".data") const char str_000003BC[12] = "stg7_bom_63";
__declspec(section ".data") const char str_000003C8[4] = "me\0";
__declspec(section ".data") const char str_000003CC[12] = "chika_off\0\0";
__declspec(section ".data") const char str_000003D8[12] = "jime_ugo\0\0\0";
__declspec(section ".data") const char str_000003E4[8] = "S_yuka1";
__declspec(section ".data") const char str_000003EC[8] = "S_yuka2";
__declspec(section ".data") const char str_000003F4[28] = "SFX_VOICE_MARIO_SURPRISED1\0";
__declspec(section ".data") const char str_00000410[8] = "M_N_7\0\0";
__declspec(section ".data") const char str_00000418[24] = "SFX_STG7_FLOOR_OPEN1\0\0\0";
__declspec(section ".data") const char str_00000430[16] = "hiraku_ss_1_b\0\0";
__declspec(section ".data") const char str_00000440[16] = "hiraku_ss_1_a\0\0";
__declspec(section ".data") const char str_00000450[24] = "SFX_STG7_MARIO_FALL1\0\0\0";
__declspec(section ".data") const char str_00000468[20] = "\x83r\x83r\x83" "A\x83\x93\x82\xb5\x82\xc1\x82\xdb\x96\xb3\x8c\xf8\0";
__declspec(section ".data") const char str_0000047C[8] = "mario\0\0";
__declspec(section ".data") const char str_00000484[12] = "stg7_bom_64";
__declspec(section ".data") const char str_00000490[16] = "stg7_bom_64_01\0";
__declspec(section ".data") const char str_000004A0[12] = "stg7_bom_66";
__declspec(section ".data") const char str_000004AC[12] = "stg7_bom_67";
__declspec(section ".data") const char str_000004B8[12] = "stg7_bom_68";
__declspec(section ".data") const char str_000004C4[12] = "stg7_bom_69";
__declspec(section ".data") const char str_000004D0[28] = "SFX_STG7_CANNON_SYS_ACTIVE1";
__declspec(section ".data") const char str_000004EC[28] = "SFX_STG7_CANNON_SYS_ACTIVE2";
__declspec(section ".data") const char str_00000508[8] = "kikai\0\0";
__declspec(section ".data") const char str_00000510[12] = "stg7_bom_70";
__declspec(section ".data") const char str_0000051C[12] = "stg7_bom_71";
__declspec(section ".data") const char str_00000528[12] = "stg7_bom_72";
__declspec(section ".data") const char str_00000534[24] = "SFX_STG7_CANNON_SIREN1\0";
__declspec(section ".data") const char str_0000054C[12] = "stg7_bom_73";
__declspec(section ".data") const char str_00000558[12] = "stg7_bom_74";
__declspec(section ".data") const char str_00000564[24] = "BGM_EVT_STG7_HUGE_GUN1\0";
__declspec(section ".data") const char str_0000057C[24] = "SFX_STG7_FLOOR_QUAKE1\0\0";
__declspec(section ".data") const char str_00000594[24] = "SFX_STG7_FLOOR_QUAKE2\0\0";
__declspec(section ".data") const char str_000005AC[8] = "S_yuka3";
__declspec(section ".data") const char str_000005B4[12] = "S_hikari\0\0\0";
__declspec(section ".data") const char str_000005C0[24] = "SFX_STG7_FLOOR_DOWN1\0\0\0";
__declspec(section ".data") const char str_000005D8[16] = "hiraku_l_1_a\0\0\0";
__declspec(section ".data") const char str_000005E8[16] = "hiraku_l_1_b\0\0\0";
__declspec(section ".data") const char str_000005F8[24] = "SFX_STG7_FLOOR_OPEN2\0\0\0";
__declspec(section ".data") const char str_00000610[12] = "stg7_bom_75";
__declspec(section ".data") const char str_0000061C[16] = "hiraku_s_1_a\0\0\0";
__declspec(section ".data") const char str_0000062C[16] = "hiraku_s_1_b\0\0\0";
__declspec(section ".data") const char str_0000063C[16] = "hiraku_s_2_a\0\0\0";
__declspec(section ".data") const char str_0000064C[16] = "hiraku_s_2_b\0\0\0";
__declspec(section ".data") const char str_0000065C[16] = "hiraku_s_3_a\0\0\0";
__declspec(section ".data") const char str_0000066C[16] = "hiraku_s_3_b\0\0\0";
__declspec(section ".data") const char str_0000067C[16] = "hiraku_s_4_a\0\0\0";
__declspec(section ".data") const char str_0000068C[16] = "hiraku_s_4_b\0\0\0";
__declspec(section ".data") const char str_0000069C[12] = "stg7_bom_76";
__declspec(section ".data") const char str_000006A8[20] = "SFX_STG7_CANNON_UP1";
__declspec(section ".data") const char str_000006BC[12] = "S_dekatai\0\0";
__declspec(section ".data") const char str_000006C8[24] = "SFX_STG7_CANNON_STOP1\0\0";
__declspec(section ".data") const char str_000006E0[12] = "stg7_bom_77";
__declspec(section ".data") const char str_000006EC[24] = "SFX_STG7_CANNON_MOVE1\0\0";
__declspec(section ".data") const char str_00000704[24] = "SFX_STG7_CANNON_STOP2\0\0";
__declspec(section ".data") const char str_0000071C[12] = "stg7_bom_78";
__declspec(section ".data") const char str_00000728[8] = "S_moon\0";
__declspec(section ".data") const char str_00000730[12] = "stg7_bom_79";
__declspec(section ".data") const char str_0000073C[12] = "stg7_bom_80";
__declspec(section ".data") const char str_00000748[24] = "SFX_STG7_HATCH_OPEN1\0\0\0";
__declspec(section ".data") const char str_00000760[8] = "futa\0\0\0";
__declspec(section ".data") const char str_00000768[12] = "stg7_bom_81";
__declspec(section ".data") const char str_00000774[8] = "\x91\xba\x92\xb7\0\0\0";
__declspec(section ".data") const char str_0000077C[24] = "SFX_STG7_BOMB_TOGETHER1";
__declspec(section ".data") const char str_00000794[12] = "stg7_bom_85";
__declspec(section ".data") const char str_000007A0[28] = "SFX_STG7_BOMB_TOGETHER1_2\0\0";
__declspec(section ".data") const char str_000007BC[16] = "stg7_bom_85_1\0\0";
__declspec(section ".data") const char str_000007CC[16] = "stg7_bom_85_2\0\0";
__declspec(section ".data") const char str_000007DC[16] = "stg7_bom_85_3\0\0";
__declspec(section ".data") const char str_000007EC[24] = "SFX_STG7_HATCH_SHUT1\0\0\0";
__declspec(section ".data") const char str_00000804[16] = "stg7_bom_85_4\0\0";
__declspec(section ".data") const char str_00000814[16] = "stg7_bom_85_5\0\0";
__declspec(section ".data") const char str_00000824[16] = "stg7_bom_85_6\0\0";
__declspec(section ".data") const char str_00000834[12] = "stg7_bom_86";
__declspec(section ".data") const char str_00000840[12] = "stg7_bom_87";
__declspec(section ".data") const char str_0000084C[8] = "HAIKEI\0";
__declspec(section ".data") const char str_00000854[28] = "SFX_VOICE_MARIO_DAMAGED2\0\0\0";
__declspec(section ".data") const char str_00000870[24] = "SFX_VOICE_MARIO_AC3_4\0\0";
__declspec(section ".data") const char str_00000888[20] = "SFX_STG7_MARIO_FLY1";
__declspec(section ".data") const char str_0000089C[24] = "SFX_STG7_MARIO_LIGHT1\0\0";
__declspec(section ".data") const char str_000008B4[16] = "wangflush_n64\0\0";
__declspec(section ".data") const char str_000008C4[12] = "stg7_bom_88";
__declspec(section ".data") const char str_000008D0[12] = "stg7_bom_89";
__declspec(section ".data") const char str_000008DC[12] = "stg7_bom_90";
__declspec(section ".data") const char str_000008E8[12] = "stg7_bom_91";
__declspec(section ".data") const char str_000008F4[8] = "moo_03\0";
__declspec(section ".data") const char str_000008FC[20] = "stg7_bom_59_04_1\0\0\0";
__declspec(section ".data") const char str_00000910[20] = "stg7_bom_59_04_2\0\0\0";
__declspec(section ".data") const char str_00000924[16] = "stg7_bom_02_00\0";
__declspec(section ".data") const char str_00000934[12] = "stg7_bom_02";
__declspec(section ".data") const char str_00000940[16] = "stg7_bom_02_1\0\0";
__declspec(section ".data") const char str_00000950[12] = "stg7_bom_03";
__declspec(section ".data") const char str_0000095C[16] = "stg7_bom_03_1\0\0";
__declspec(section ".data") const char str_0000096C[16] = "stg7_bom_04_00\0";
__declspec(section ".data") const char str_0000097C[12] = "stg7_bom_04";
__declspec(section ".data") const char str_00000988[16] = "stg7_bom_04_1\0\0";
__declspec(section ".data") const char str_00000998[12] = "stg7_bom_05";
__declspec(section ".data") const char str_000009A4[16] = "stg7_bom_05_1\0\0";
__declspec(section ".data") const char str_000009B4[16] = "stg7_bom_06_00\0";
__declspec(section ".data") const char str_000009C4[12] = "stg7_bom_06";
__declspec(section ".data") const char str_000009D0[16] = "stg7_bom_06_1\0\0";
__declspec(section ".data") const char str_000009E0[12] = "stg7_bom_07";
__declspec(section ".data") const char str_000009EC[16] = "stg7_bom_07_1\0\0";
__declspec(section ".data") const char str_000009FC[16] = "stg7_bom_08_00\0";
__declspec(section ".data") const char str_00000A0C[12] = "stg7_bom_08";
__declspec(section ".data") const char str_00000A18[16] = "stg7_bom_08_1\0\0";
__declspec(section ".data") const char str_00000A28[12] = "stg7_bom_09";
__declspec(section ".data") const char str_00000A34[16] = "stg7_bom_09_1\0\0";
__declspec(section ".data") const char str_00000A44[16] = "stg7_bom_10_00\0";
__declspec(section ".data") const char str_00000A54[12] = "stg7_bom_10";
__declspec(section ".data") const char str_00000A60[12] = "stg7_bom_11";
__declspec(section ".data") const char str_00000A6C[16] = "stg7_bom_12_00\0";
__declspec(section ".data") const char str_00000A7C[12] = "stg7_bom_12";
__declspec(section ".data") const char str_00000A88[12] = "stg7_bom_13";
__declspec(section ".data") const char str_00000A94[16] = "stg7_bom_14_00\0";
__declspec(section ".data") const char str_00000AA4[12] = "stg7_bom_14";
__declspec(section ".data") const char str_00000AB0[12] = "stg7_bom_15";
__declspec(section ".data") const char str_00000ABC[16] = "stg7_bom_16_00\0";
__declspec(section ".data") const char str_00000ACC[12] = "stg7_bom_16";
__declspec(section ".data") const char str_00000AD8[12] = "stg7_bom_17";
__declspec(section ".data") const char str_00000AE4[16] = "stg7_bom_18_00\0";
__declspec(section ".data") const char str_00000AF4[12] = "stg7_bom_18";
__declspec(section ".data") const char str_00000B00[12] = "stg7_bom_19";
__declspec(section ".data") const char str_00000B0C[16] = "stg7_bom_59_02\0";
__declspec(section ".data") const char str_00000B1C[16] = "stg7_bom_59_03\0";
__declspec(section ".data") const char str_00000B2C[16] = "stg7_bom_59_04\0";
__declspec(section ".data") const char str_00000B3C[16] = "stg7_bom_59_05\0";
__declspec(section ".data") const char str_00000B4C[20] = "stg7_bom_09_01_01\0\0";
__declspec(section ".data") const char str_00000B60[12] = "\x82R\x90l\x96\xba\x82`\0\0\0";
__declspec(section ".data") const char str_00000B6C[20] = "stg7_bom_09_01_02\0\0";
__declspec(section ".data") const char str_00000B80[12] = "\x82R\x90l\x96\xba\x82" "a\0\0\0";
__declspec(section ".data") const char str_00000B8C[20] = "stg7_bom_09_01_03\0\0";
__declspec(section ".data") const char str_00000BA0[12] = "\x82R\x90l\x96\xba\x82" "b\0\0\0";
__declspec(section ".data") const char str_00000BAC[20] = "stg7_bom_09_01_04\0\0";
__declspec(section ".data") const char str_00000BC0[20] = "stg7_bom_09_01_05\0\0";
__declspec(section ".data") const char str_00000BD4[20] = "stg7_bom_09_01_06\0\0";
__declspec(section ".data") const char str_00000BE8[20] = "stg7_bom_09_01_07\0\0";
__declspec(section ".data") const char str_00000BFC[20] = "stg7_bom_09_01_08\0\0";
__declspec(section ".data") const char str_00000C10[20] = "stg7_bom_09_01_09\0\0";
__declspec(section ".data") const char str_00000C24[12] = "c_dance_r\0\0";
__declspec(section ".data") const char str_00000C30[8] = "\x97x\x82\xe8\x8eq\0";
__declspec(section ".data") const char str_00000C38[12] = "c_dance_p\0\0";
__declspec(section ".data") const char str_00000C44[16] = "\x97x\x82\xe8\x8eq\x83s\x83\x93\x83N\0\0\0";
__declspec(section ".data") const char str_00000C54[12] = "c_dance_k\0\0";
__declspec(section ".data") const char str_00000C60[12] = "\x97x\x82\xe8\x8eq\x89\xa9\x97\xce\0";
__declspec(section ".data") const char str_00000CA8[8] = "S_bom01";
__declspec(section ".data") const char str_00000CB0[12] = "starstone\0\0";
__declspec(section ".data") const char str_00000CBC[16] = "stg8_las_148_65";
__declspec(section ".data") const char str_00000CCC[16] = "stg8_las_148_66";
__declspec(section ".data") const char str_00000CDC[16] = "stg8_las_148_67";
__declspec(section ".data") const char str_00000CEC[16] = "stg8_las_148_68";
__declspec(section ".data") const char str_00000CFC[16] = "stg8_las_148_69";
__declspec(section ".data") const char str_00000D0C[16] = "stg8_las_148_70";
__declspec(section ".data") const char str_00000D1C[16] = "stg8_las_148_71";
__declspec(section ".data") const char str_00000D2C[8] = "las_29\0";
__declspec(section ".data") const char str_00000D34[12] = "minnnanokoe";
__declspec(section ".data") const char str_00000D40[16] = "stg7_bom_09_01\0";
__declspec(section ".data") const char str_00000D50[20] = "BGM_EVT_STG8_VOICE1";
__declspec(section ".data") const char str_00000D64[16] = "BGM_STG7_BOM1\0\0";
__declspec(section ".data") const char str_00000D74[16] = "ENV_STG7_BOM2\0\0";
__declspec(section ".data") const char str_00000D84[8] = "group10";
__declspec(section ".data") const char str_00000D8C[8] = "group11";
__declspec(section ".data") const char str_00000D94[8] = "group12";
__declspec(section ".data") const char str_00000D9C[8] = "group13";
__declspec(section ".data") const char str_00000DA4[8] = "group14";
__declspec(section ".data") const char str_00000DAC[8] = "group15";
__declspec(section ".data") const char str_00000DB4[8] = "A_chika";
__declspec(section ".data") const char str_00000DBC[8] = "item_00";
#endif
