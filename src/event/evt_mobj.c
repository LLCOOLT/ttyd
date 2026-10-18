// FAKE: whole-unit ASM-STOPGAP (C3b 2026-10-18). Every function is target asm (asm_inline.py + C3b aifix.py/rodatagen.py);
// the C is kept beside each one under NONMATCHING. .rodata/.sdata2 are re-declared in target order. Dead C not in the
// target object (mobj_koopa_stone_blk, mobj_sign, evt_mobj_rideswitch, mobj_itemb) is under NONMATCHING. See docs/FAKES.md.
#include "evt/evt_cmd.h"
#include "driver/mobjdrv.h"
#include "driver/animdrv.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mariost.h"
#include "eff/eff_small_star.h"
#include "mario/mario_motion.h"
#include "memory.h"
#include "mario/mario.h"
#include "party.h"
#include <dolphin/mtx.h>
#include "manager/fontmgr.h"
#include <string.h>
#pragma force_active on
__declspec(section ".rodata") const u32 vec3_802c3dc8[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c3dd4[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 str_802C3DE0[6] = {0x4D4F424A, 0x5F426C75, 0x6554696D, 0x65725377, 0x69746368, 0x00000000};
__declspec(section ".rodata") const u32 str_802C3DF8[5] = {0x4D4F424A, 0x5F526564, 0x54696D65, 0x72537769, 0x74636800};
__declspec(section ".rodata") void* const jumptable_802C3E0C[2] = {(void*)((char*)str_802C3DE0 + 0x0), (void*)((char*)str_802C3DF8 + 0x0)};
__declspec(section ".rodata") const u32 vec3_802c3e14[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c3e20[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c3e2c[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c3e38[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c3e44[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c3e50[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c3e5c[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 str_802C3E68[5] = {0x4D4F424A, 0x5F526564, 0x4A756D70, 0x5374616E, 0x64000000};
__declspec(section ".rodata") const u32 str_802C3E7C[5] = {0x4D4F424A, 0x5F526564, 0x4A756D70, 0x5374616E, 0x64320000};
__declspec(section ".rodata") void* const jumptable_802C3E90[2] = {(void*)((char*)str_802C3E68 + 0x0), (void*)((char*)str_802C3E7C + 0x0)};
__declspec(section ".rodata") const u32 str_802C3E98[5] = {0x4D4F424A, 0x5F426C75, 0x654A756D, 0x70537461, 0x6E640000};
__declspec(section ".rodata") const u32 str_802C3EAC[5] = {0x4D4F424A, 0x5F426C75, 0x654A756D, 0x70537461, 0x6E643200};
__declspec(section ".rodata") void* const jumptable_802C3EC0[2] = {(void*)((char*)str_802C3E98 + 0x0), (void*)((char*)str_802C3EAC + 0x0)};
__declspec(section ".rodata") const u32 str_802C3EC8[4] = {0x6F5F0000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 str_802C3ED8[4] = {0x695F0000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c3ee8[3] = {0x00000000, 0xC4FA0000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c3ef4[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 str_802C3F00[6] = {0x5346585F, 0x4D4F424A, 0x5F4C4F43, 0x4B5F5357, 0x494E4731, 0x00000000};
__declspec(section ".rodata") const u32 str_802C3F18[5] = {0x5346585F, 0x4D4F424A, 0x5F554E4C, 0x4F434B31, 0x00000000};
__declspec(section ".rodata") const u32 str_802C3F2C[8] = {0x5346585F, 0x4D4F424A, 0x5F545245, 0x41535552, 0x455F424F, 0x585F5357, 0x494E4731, 0x00000000};
__declspec(section ".rodata") const u32 str_802C3F4C[7] = {0x5346585F, 0x4D4F424A, 0x5F545245, 0x41535552, 0x455F424F, 0x585F4F50, 0x454E3100};
__declspec(section ".rodata") const u32 str_802C3F68[8] = {0x5346585F, 0x4D4F424A, 0x5F545245, 0x41535552, 0x455F424F, 0x585F5357, 0x494E4732, 0x00000000};
__declspec(section ".rodata") const u32 str_802C3F88[7] = {0x5346585F, 0x4D4F424A, 0x5F545245, 0x41535552, 0x455F424F, 0x585F4F50, 0x454E3200};
__declspec(section ".rodata") const u32 str_802C3FA4[7] = {0x5346585F, 0x4D4F424A, 0x5F424C41, 0x434B424F, 0x585F5357, 0x494E4731, 0x00000000};
__declspec(section ".rodata") const u32 str_802C3FC0[6] = {0x5346585F, 0x4D4F424A, 0x5F424C41, 0x434B424F, 0x585F4F50, 0x454E3100};
__declspec(section ".rodata") const u32 vec3_802c3fd8[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c3fe4[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 str_802C3FF0[4] = {0x73617665, 0x5F666972, 0x73745F68, 0x69740000};
__declspec(section ".rodata") const u32 str_802C4000[4] = {0x6F5F0000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 str_802C4010[4] = {0x695F0000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c4020[3] = {0x00000000, 0xC4FA0000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c402c[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c4038[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c4044[3] = {0x00000000, 0x00000000, 0xBF800000};
__declspec(section ".rodata") const u32 vec3_802c4050[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c405c[3] = {0x43480000, 0x00000000, 0x43480000};
__declspec(section ".rodata") const u32 vec3_802c4068[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 str_802C4074[4] = {0x6F5F0000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 str_802C4084[4] = {0x695F0000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c4094[3] = {0x00000000, 0xC4FA0000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c40a0[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c40ac[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c40b8[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c40c4[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c40d0[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 str_802C40DC[3] = {0x4B504132, 0x5F475F31, 0x00000000};
__declspec(section ".rodata") const u32 str_802C40E8[6] = {0x5346585F, 0x4B555050, 0x415F504F, 0x53545F4A, 0x554D5031, 0x00000000};
__declspec(section ".rodata") const u32 str_802C4100[6] = {0x5346585F, 0x4B555050, 0x415F504F, 0x53545F53, 0x4C494445, 0x31000000};
__declspec(section ".rodata") const u32 str_802C4118[6] = {0x5346585F, 0x4B555050, 0x415F504F, 0x53545F54, 0x48524F57, 0x31000000};
__declspec(section ".rodata") const u32 str_802C4130[2] = {0x6B70615F, 0x30360000};
__declspec(section ".rodata") const u32 str_802C4138[2] = {0x746F7269, 0x64650000};
__declspec(section ".rodata") const u32 str_802C4140[2] = {0x746F7269, 0x64655F00};
__declspec(section ".rodata") const u32 str_802C4148[5] = {0x5346585F, 0x4B555050, 0x415F5354, 0x52554747, 0x4C453100};
__declspec(section ".rodata") const u32 str_802C415C[3] = {0x4B504132, 0x5F535F31, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c4168[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 vec3_802c4174[3] = {0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 str_802C4180[4] = {0x4D4F424A, 0x5F676F61, 0x6C5F706F, 0x6C650000};
__declspec(section ".rodata") const u32 str_802C4190[4] = {0x4D4F424A, 0x5F676F61, 0x6C5F6861, 0x74610000};
__declspec(section ".rodata") const u32 str_802C41A0[4] = {0x4D4F424A, 0x5F666972, 0x655F646F, 0x64616900};
__declspec(section ".rodata") const u32 str_802C41B0[3] = {0x635F6669, 0x72656265, 0x72000000};
__declspec(section ".rodata") const u32 str_802C41BC[2] = {0x4652425F, 0x535F3100};
__declspec(section ".rodata") const u32 gap_rodata_3fc[1] = {0x00000000};
__declspec(section ".rodata") const u32 double_to_int_802c41c8[2] = {0x43300000, 0x80000000};
__declspec(section ".rodata") const u32 str_802C41D0[3] = {0x4D4F424A, 0x5F73616E, 0x676F0000};
__declspec(section ".rodata") const u32 str_802C41DC[5] = {0x4D4F424A, 0x5F477265, 0x656E5069, 0x70655F6B, 0x73000000};
__declspec(section ".rodata") const u32 str_802C41F0[5] = {0x4D4F424A, 0x5F477265, 0x656E5069, 0x70655F6B, 0x6C000000};
__declspec(section ".rodata") const u32 str_802C4204[5] = {0x4D4F424A, 0x5F477265, 0x656E5069, 0x70655F6B, 0x79000000};
__declspec(section ".rodata") const u32 str_802C4218[3] = {0x4D4F424A, 0x5F426C6F, 0x636B0000};
__declspec(section ".rodata") const u32 str_802C4224[6] = {0x4D4F424A, 0x5F486964, 0x64656E48, 0x6174656E, 0x61426C6F, 0x636B0000};
__declspec(section ".rodata") const u32 str_802C423C[5] = {0x4D4F424A, 0x5F486174, 0x656E6142, 0x6C6F636B, 0x00000000};
__declspec(section ".rodata") const u32 str_802C4250[5] = {0x4D4F424A, 0x5F466C6F, 0x77427269, 0x636B426C, 0x6F636B00};
__declspec(section ".rodata") const u32 str_802C4264[4] = {0x4D4F424A, 0x5F626C6F, 0x636B5F6B, 0x79000000};
__declspec(section ".rodata") const u32 str_802C4274[5] = {0x4D4F424A, 0x5F626967, 0x626C6F63, 0x6B5F3031, 0x00000000};
__declspec(section ".rodata") const u32 str_802C4288[5] = {0x4D4F424A, 0x5F626967, 0x626C6F63, 0x6B5F3032, 0x00000000};
__declspec(section ".rodata") const u32 str_802C429C[4] = {0x4D4F424A, 0x5F426F6D, 0x62526F63, 0x6B000000};
__declspec(section ".rodata") const u32 str_802C42AC[3] = {0x4F46465F, 0x645F626F, 0x6D000000};
__declspec(section ".rodata") const u32 str_802C42B8[3] = {0x4D4F424A, 0x5F747261, 0x70000000};
__declspec(section ".rodata") const u32 str_802C42C4[5] = {0x4D4F424A, 0x5F4B7572, 0x7572696E, 0x466C6F6F, 0x72000000};
__declspec(section ".rodata") const u32 double_0p21817_802c42d8[2] = {0x3FCBECDE, 0x60000000};
__declspec(section ".rodata") const u32 double_to_int_mask_802c42e0[2] = {0x43300000, 0x00000000};
__declspec(section ".rodata") const u32 str_802C42E8[5] = {0x4D4F424A, 0x5F427265, 0x616B696E, 0x67466C6F, 0x6F720000};
__declspec(section ".rodata") const u32 str_802C42FC[6] = {0x4D4F424A, 0x5F426C61, 0x636B4272, 0x65616B69, 0x6E67466C, 0x6F6F7200};
__declspec(section ".rodata") const u32 str_802C4314[6] = {0x4D4F424A, 0x5F427269, 0x636B4861, 0x74656E61, 0x426C6F63, 0x6B000000};
__declspec(section ".rodata") const u32 str_802C432C[6] = {0x4D4F424A, 0x5F427269, 0x636B4261, 0x64676542, 0x6C6F636B, 0x00000000};
__declspec(section ".rodata") const u32 str_802C4344[5] = {0x4D4F424A, 0x5F313043, 0x6F756E74, 0x426C6F63, 0x6B000000};
__declspec(section ".rodata") const u32 str_802C4358[6] = {0x4D4F424A, 0x5F486964, 0x64656E42, 0x61646765, 0x426C6F63, 0x6B000000};
__declspec(section ".rodata") const u32 str_802C4370[6] = {0x4D4F424A, 0x5F486964, 0x64656E31, 0x30436F75, 0x6E74426C, 0x6F636B00};
__declspec(section ".rodata") const u32 str_802C4388[2] = {0x505F626F, 0x785F7900};
__declspec(section ".rodata") const u32 str_802C4390[4] = {0x4D4F424A, 0x5F50696E, 0x6B426C6F, 0x636B0000};
__declspec(section ".rodata") const u32 str_802C43A0[5] = {0x4D4F424A, 0x5F506F77, 0x65725570, 0x426C6F63, 0x6B000000};
__declspec(section ".rodata") const u32 str_802C43B4[2] = {0x646F755F, 0x30320000};
__declspec(section ".rodata") const u32 str_802C43BC[2] = {0x646F755F, 0x30350000};
__declspec(section ".rodata") const u32 str_802C43C4[2] = {0x646F755F, 0x31300000};
__declspec(section ".rodata") const u32 str_802C43CC[2] = {0x70777262, 0x6C6B3100};
__declspec(section ".rodata") const u32 str_802C43D4[2] = {0x70777262, 0x6C6B3200};
__declspec(section ".rodata") const u32 str_802C43DC[4] = {0x4D4F424A, 0x5F426164, 0x6765426C, 0x6F636B00};
__declspec(section ".rodata") const u32 str_802C43EC[4] = {0x4D4F424A, 0x5F536176, 0x65426C6F, 0x636B0000};
__declspec(section ".rodata") const u32 str_802C43FC[5] = {0x4D4F424A, 0x5F526563, 0x6F766572, 0x79426C6F, 0x636B0000};
__declspec(section ".rodata") const u32 str_802C4410[7] = {0x4D4F424A, 0x5F436F69, 0x6E54616B, 0x656E5265, 0x636F7665, 0x7279426C, 0x6F636B00};
__declspec(section ".rodata") const u32 str_802C442C[3] = {0x7379735F, 0x6E6F5F63, 0x6F696E00};
__declspec(section ".rodata") const u32 str_802C4438[5] = {0x6B616966, 0x756B755F, 0x66697273, 0x745F6869, 0x74000000};
__declspec(section ".rodata") const u32 str_802C444C[3] = {0x4D4F424A, 0x5F417272, 0x6F770000};
__declspec(section ".rodata") const u32 str_802C4458[4] = {0x4D4F424A, 0x5F536967, 0x6E626F61, 0x72640000};
__declspec(section ".rodata") const u32 str_802C4468[5] = {0x4D4F424A, 0x5F547265, 0x61737572, 0x65426F78, 0x00000000};
__declspec(section ".rodata") const u32 str_802C447C[5] = {0x4D4F424A, 0x5F426967, 0x54726561, 0x73757265, 0x426F7800};
__declspec(section ".rodata") const u32 str_802C4490[6] = {0x4D4F424A, 0x5F477261, 0x79547265, 0x61737572, 0x65426F78, 0x00000000};
__declspec(section ".rodata") const u32 str_802C44A8[6] = {0x4D4F424A, 0x5F426C61, 0x636B5472, 0x65617375, 0x7265426F, 0x78000000};
__declspec(section ".rodata") const u32 str_802C44C0[6] = {0x4D4F424A, 0x5F476F6C, 0x64656E54, 0x72656173, 0x75726542, 0x6F780000};
__declspec(section ".rodata") const u32 double_0p2_802c44d8[2] = {0x3FC99999, 0xA0000000};
__declspec(section ".rodata") const u32 str_802C44E0[3] = {0x4D4F424A, 0x5F4C6F63, 0x6B000000};
__declspec(section ".rodata") const u32 str_802C44EC[3] = {0x7379735F, 0x6E6F5F6B, 0x65790000};
__declspec(section ".rodata") const u32 str_802C44F8[7] = {0x4D4F424A, 0x5F677265, 0x656E5F46, 0x6C6F7742, 0x6C6F636B, 0x53776974, 0x63680000};
__declspec(section ".rodata") const u32 str_802C4514[7] = {0x4D4F424A, 0x5F707572, 0x706C655F, 0x466C6F77, 0x426C6F63, 0x6B537769, 0x74636800};
__declspec(section ".rodata") const u32 str_802C4530[7] = {0x4D4F424A, 0x5F6F7261, 0x6E67655F, 0x466C6F77, 0x426C6F63, 0x6B537769, 0x74636800};
__declspec(section ".rodata") const u32 str_802C454C[7] = {0x4D4F424A, 0x5F726564, 0x5F466C6F, 0x77426C6F, 0x636B5377, 0x69746368, 0x00000000};
__declspec(section ".rodata") const u32 str_802C4568[6] = {0x4D4F424A, 0x5F677265, 0x656E5F46, 0x6C6F7742, 0x6C6F636B, 0x00000000};
__declspec(section ".rodata") const u32 str_802C4580[7] = {0x4D4F424A, 0x5F677265, 0x656E5F62, 0x69675F46, 0x6C6F7742, 0x6C6F636B, 0x00000000};
__declspec(section ".rodata") const u32 str_802C459C[7] = {0x4D4F424A, 0x5F677265, 0x656E5F62, 0x69673032, 0x5F466C6F, 0x77426C6F, 0x636B0000};
__declspec(section ".rodata") const u32 str_802C45B8[6] = {0x4D4F424A, 0x5F707572, 0x706C655F, 0x466C6F77, 0x426C6F63, 0x6B000000};
__declspec(section ".rodata") const u32 str_802C45D0[7] = {0x4D4F424A, 0x5F707572, 0x706C655F, 0x6269675F, 0x466C6F77, 0x426C6F63, 0x6B000000};
__declspec(section ".rodata") const u32 str_802C45EC[7] = {0x4D4F424A, 0x5F707572, 0x706C655F, 0x62696730, 0x325F466C, 0x6F77426C, 0x6F636B00};
__declspec(section ".rodata") const u32 str_802C4608[6] = {0x4D4F424A, 0x5F6F7261, 0x6E67655F, 0x466C6F77, 0x426C6F63, 0x6B000000};
__declspec(section ".rodata") const u32 str_802C4620[7] = {0x4D4F424A, 0x5F6F7261, 0x6E67655F, 0x6269675F, 0x466C6F77, 0x426C6F63, 0x6B000000};
__declspec(section ".rodata") const u32 str_802C463C[7] = {0x4D4F424A, 0x5F6F7261, 0x6E67655F, 0x62696730, 0x325F466C, 0x6F77426C, 0x6F636B00};
__declspec(section ".rodata") const u32 str_802C4658[7] = {0x4D4F424A, 0x5F726564, 0x5F626967, 0x30325F46, 0x6C6F7742, 0x6C6F636B, 0x00000000};
__declspec(section ".rodata") const u32 str_802C4674[4] = {0x4D4F424A, 0x5F4C7631, 0x426C6F63, 0x6B000000};
__declspec(section ".rodata") const u32 str_802C4684[5] = {0x4D4F424A, 0x5F4C7631, 0x42696742, 0x6C6F636B, 0x00000000};
__declspec(section ".rodata") const u32 str_802C4698[5] = {0x4D4F424A, 0x5F4C7631, 0x42696742, 0x6967426C, 0x6F636B00};
__declspec(section ".rodata") const u32 str_802C46AC[4] = {0x4D4F424A, 0x5F4C7632, 0x426C6F63, 0x6B000000};
__declspec(section ".rodata") const u32 str_802C46BC[5] = {0x4D4F424A, 0x5F4C7632, 0x42696742, 0x6C6F636B, 0x00000000};
__declspec(section ".rodata") const u32 str_802C46D0[5] = {0x4D4F424A, 0x5F4C7632, 0x42696742, 0x6967426C, 0x6F636B00};
__declspec(section ".rodata") const u32 str_802C46E4[5] = {0x4D4F424A, 0x5F526964, 0x65537769, 0x74636843, 0x00000000};
__declspec(section ".rodata") const u32 str_802C46F8[5] = {0x4D4F424A, 0x5F526964, 0x65537769, 0x74636842, 0x00000000};
__declspec(section ".rodata") const u32 str_802C470C[5] = {0x4D4F424A, 0x5F526964, 0x65537769, 0x74636841, 0x00000000};
__declspec(section ".rodata") const u32 str_802C4720[6] = {0x4D4F424A, 0x5F526564, 0x546F726E, 0x61646F53, 0x77697463, 0x68000000};
__declspec(section ".rodata") const u32 str_802C4738[5] = {0x4D4F424A, 0x5F526564, 0x53776974, 0x6368426C, 0x6F636B00};
__declspec(section ".rodata") const u32 str_802C474C[4] = {0x4D4F424A, 0x5F526564, 0x53776974, 0x63680000};
__declspec(section ".rodata") const u32 str_802C475C[5] = {0x4D4F424A, 0x5F576869, 0x74655377, 0x69746368, 0x00000000};
__declspec(section ".rodata") const u32 str_802C4770[6] = {0x4D4F424A, 0x5F426C75, 0x65546F72, 0x6E61646F, 0x53776974, 0x63680000};
__declspec(section ".rodata") const u32 str_802C4788[6] = {0x4D4F424A, 0x5F426C75, 0x65537769, 0x74636842, 0x6C6F636B, 0x00000000};
__declspec(section ".rodata") const u32 str_802C47A0[4] = {0x4D4F424A, 0x5F426C75, 0x65537769, 0x74636800};
__declspec(section ".rodata") const u32 str_802C47B0[5] = {0x4D4F424A, 0x5F426C61, 0x636B5377, 0x69746368, 0x00000000};
__declspec(section ".rodata") const u32 str_802C47C4[4] = {0x484F424A, 0x5F426C75, 0x65537769, 0x74636800};
__declspec(section ".rodata") const u32 gap_rodata_a0c[1] = {0x00000000};
__declspec(section ".sdata2") const u32 str_8041A118[1] = {0x415F3100};
__declspec(section ".sdata2") const u32 str_8041A11C[1] = {0x415F3200};
__declspec(section ".sdata2") const u32 str_8041A120[1] = {0x415F3300};
__declspec(section ".sdata2") const u32 str_8041A124[1] = {0x415F3400};
__declspec(section ".sdata2") const u32 str_8041A128[1] = {0x415F3500};
__declspec(section ".sdata2") const u32 str_8041A12C[1] = {0x535F3100};
__declspec(section ".sdata2") const u32 dat_8041a130[1] = {0xFFFFFFFF};
__declspec(section ".sdata2") const u32 dat_8041a134[1] = {0xFFFFFFFF};
__declspec(section ".sdata2") const u32 str_8041A138[1] = {0x5F680000};
__declspec(section ".sdata2") const u32 float_180_8041a13c[1] = {0x43340000};
__declspec(section ".sdata2") const u32 float_25_8041a140[1] = {0x41C80000};
__declspec(section ".sdata2") const u32 float_170_8041a144[1] = {0x432A0000};
__declspec(section ".sdata2") const u32 float_100_8041a148[1] = {0x42C80000};
__declspec(section ".sdata2") const u32 float_50_8041a14c[1] = {0x42480000};
__declspec(section ".sdata2") const u32 float_0_8041a150[1] = {0x00000000};
__declspec(section ".sdata2") const u32 float_230_8041a154[1] = {0x43660000};
__declspec(section ".sdata2") const u32 float_300_8041a158[1] = {0x43960000};
__declspec(section ".sdata2") const u32 float_0p5_8041a15c[1] = {0x3F000000};
__declspec(section ".sdata2") const u32 float_1_8041a160[1] = {0x3F800000};
__declspec(section ".sdata2") const u32 float_175_8041a164[1] = {0x432F0000};
__declspec(section ".sdata2") const u32 str_8041A168[2] = {0x25732532, 0x78000000};
__declspec(section ".sdata2") const u32 float_150_8041a170[1] = {0x43160000};
__declspec(section ".sdata2") const u32 float_deg2rad_8041a174[1] = {0x3C8EFA35};
__declspec(section ".sdata2") const u32 float_12p5_8041a178[1] = {0x41480000};
__declspec(section ".sdata2") const u32 float_neg1000_8041a17c[1] = {0xC47A0000};
__declspec(section ".sdata2") const u32 float_200_8041a180[1] = {0x43480000};
__declspec(section ".sdata2") const u32 float_6_8041a184[1] = {0x40C00000};
__declspec(section ".sdata2") const u32 float_75_8041a188[1] = {0x42960000};
__declspec(section ".sdata2") const u32 float_4p8_8041a18c[1] = {0x4099999A};
__declspec(section ".sdata2") const u32 float_2_8041a190[1] = {0x40000000};
__declspec(section ".sdata2") const u32 float_0p04_8041a194[1] = {0x3D23D70A};
__declspec(section ".sdata2") const u32 float_3_8041a198[1] = {0x40400000};
__declspec(section ".sdata2") const u32 float_0p2_8041a19c[1] = {0x3E4CCCCD};
__declspec(section ".sdata2") const u32 float_1024_8041a1a0[1] = {0x44800000};
__declspec(section ".sdata2") const u32 float_10_8041a1a4[1] = {0x41200000};
__declspec(section ".sdata2") const u32 float_30_8041a1a8[1] = {0x41F00000};
__declspec(section ".sdata2") const u32 float_60_8041a1ac[1] = {0x42700000};
__declspec(section ".sdata2") const u32 float_0p8_8041a1b0[1] = {0x3F4CCCCD};
__declspec(section ".sdata2") const u32 float_0p125_8041a1b4[1] = {0x3E000000};
__declspec(section ".sdata2") const u32 float_0p99_8041a1b8[1] = {0x3F7D70A4};
__declspec(section ".sdata2") const u32 float_7p5_8041a1bc[1] = {0x40F00000};
__declspec(section ".sdata2") const u32 str_8041A1C0[1] = {0x535F3200};
__declspec(section ".sdata2") const u32 float_0p45_8041a1c4[1] = {0x3EE66666};
__declspec(section ".sdata2") const u32 float_0p7_8041a1c8[1] = {0x3F333333};
__declspec(section ".sdata2") const u32 float_500_8041a1cc[1] = {0x43FA0000};
__declspec(section ".sdata2") const u32 float_120_8041a1d0[1] = {0x42F00000};
__declspec(section ".sdata2") const u32 float_0p1_8041a1d4[1] = {0x3DCCCCCD};
__declspec(section ".sdata2") const u32 float_1E05_8041a1d8[1] = {0x47C35000};
__declspec(section ".sdata2") const u32 float_42p42_8041a1dc[1] = {0x4229AE15};
__declspec(section ".sdata2") const u32 float_0p6_8041a1e0[1] = {0x3F19999A};
__declspec(section ".sdata2") const u32 float_32767_8041a1e4[1] = {0x46FFFE00};
__declspec(section ".sdata2") const u32 str_8041A1E8[1] = {0x535F3300};
__declspec(section ".sdata2") const u32 float_40_8041a1ec[1] = {0x42200000};
__declspec(section ".sdata2") const u32 float_360_8041a1f0[1] = {0x43B40000};
__declspec(section ".sdata2") const u32 float_45_8041a1f4[1] = {0x42340000};
__declspec(section ".sdata2") const u32 str_8041A1F8[2] = {0x4D5F495F, 0x31000000};
__declspec(section ".sdata2") const u32 str_8041A200[2] = {0x4D5F535F, 0x31000000};
__declspec(section ".sdata2") const u32 float_1p4_8041a208[1] = {0x3FB33333};
__declspec(section ".sdata2") const u32 float_1p2_8041a20c[1] = {0x3F99999A};
__declspec(section ".sdata2") const u32 float_5_8041a210[1] = {0x40A00000};
__declspec(section ".sdata2") const u32 float_neg1_8041a214[1] = {0xBF800000};
__declspec(section ".sdata2") const u32 str_8041A218[1] = {0x535F3400};
__declspec(section ".sdata2") const u32 str_8041A21C[1] = {0x5A5F3100};
__declspec(section ".sdata2") const u32 float_neg0p8_8041a220[1] = {0xBF4CCCCD};
__declspec(section ".sdata2") const u32 float_4_8041a224[1] = {0x40800000};
__declspec(section ".sdata2") const u32 float_0p9_8041a228[1] = {0x3F666666};
__declspec(section ".sdata2") const u32 float_15_8041a22c[1] = {0x41700000};
__declspec(section ".sdata2") const u32 float_0p3_8041a230[1] = {0x3E99999A};
__declspec(section ".sdata2") const u32 str_8041A234[1] = {0x6D650000};
extern void _restfpr_28(void);
extern void _savefpr_28(void);
extern void* jumptable_8030A78C[];
extern void* jumptable_8030A7C4[];
extern void* jumptable_8030A7FC[];
extern void* jumptable_8030A834[];
s32 mobj_koopa_pole_evt(MapObjectEntry* mobj);
void kpa_disp_pole_score(CameraId camId, void* param);
static USER_FUNC(kpa_get_level);
s32 mobj_koopa_fireber_dodai_evt(MapObjectEntry* mobj);
s32 mobj_koopa_sango_evt(MapObjectEntry* mobj);
s32 mobj_koopa_dokan_evt(MapObjectEntry* mobj);
s32 mobj_koopa_blk(MapObjectEntry* mobj);
s32 mobj_koopa_badgeblk(MapObjectEntry* mobj);
s32 mobj_koopa_brickblk(MapObjectEntry* mobj);
s32 mobj_koopa_stone_blk_evt(MapObjectEntry* mobj);
s32 mobj_koopa_ojama_blk_evt(MapObjectEntry* mobj);
s32 mobj_kururing_floor(MapObjectEntry* mobj);
void kururing_capture(CameraId camId, MapObjectEntry* mobj);
s32 mobj_breaking_floor(MapObjectEntry* mobj);
s32 mobj_10countblk(MapObjectEntry* mobj);
s32 mobj_brickblk(MapObjectEntry* mobj);
s32 mobj_powerupblk(MapObjectEntry* mobj);
s32 mobj_badgeblk(MapObjectEntry* mobj);
s32 mobj_save_blk(MapObjectEntry* mobj);
s32 mobj_recovery_blk(MapObjectEntry* mobj);
s32 mobj_signboard(MapObjectEntry* mobj);
s32 mobj_itembox(MapObjectEntry* mobj);
s32 mobj_lock(MapObjectEntry* mobj);
s32 mobj_switch_float_blk(MapObjectEntry* mobj);
s32 mobj_float_blk(MapObjectEntry* mobj);
s32 mobj_lv_blk_evt(MapObjectEntry* mobj);
s32 mobj_jumpstand_blue(MapObjectEntry* mobj);
s32 mobj_jumpstand_red(MapObjectEntry* mobj);
s32 mobj_rideswitch_lightblue(MapObjectEntry* mobj);
s32 mobj_timerswitch(MapObjectEntry* mobj);
s32 mobj_switch_red(MapObjectEntry* mobj);
s32 mobj_switch_blue(MapObjectEntry* mobj);
USER_FUNC(evt_mobj_koopa_pole);
USER_FUNC(kpa_clear_jump_data);
USER_FUNC(kpa_disp_pole_init);
USER_FUNC(kpa_disp_pole_score_main);
USER_FUNC(kpa_score_to_str);
USER_FUNC(kpa_get_width);
USER_FUNC(kpa_get_hata_name);
USER_FUNC(kpa_get_pole_name);
USER_FUNC(evt_mobj_koopa_fireber_dodai);
USER_FUNC(evt_mobj_koopa_sango);
USER_FUNC(fire_func);
USER_FUNC(evt_mobj_koopa_dokan);
USER_FUNC(evt_mobj_koopa_blk);
USER_FUNC(evt_mobj_koopa_hidden_blk);
USER_FUNC(evt_mobj_koopa_badgeblk);
USER_FUNC(evt_mobj_koopa_brick);
USER_FUNC(evt_mobj_koopa_stone_blk);
USER_FUNC(evt_mobj_koopa_ojama_blk);
USER_FUNC(kpa_powerup);
USER_FUNC(evt_mobj_kururing_floor);
USER_FUNC(evt_mobj_breaking_floor);
USER_FUNC(evt_mobj_brick);
USER_FUNC(evt_mobj_powerupblk);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_mobj_save_blk);
USER_FUNC(evt_mobj_recovery_blk);
USER_FUNC(evt_mobj_signboard);
USER_FUNC(evt_mobj_itembox);
USER_FUNC(evt_mobj_lock);
USER_FUNC(evt_mobj_lock_unlock);
USER_FUNC(evt_mobj_switch_float_blk);
USER_FUNC(evt_mobj_float_blk);
USER_FUNC(evt_mobj_lv_blk);
USER_FUNC(evt_mobj_jumpstand_blue);
USER_FUNC(evt_mobj_jumpstand_red);
USER_FUNC(evt_mobj_rideswitch_lightblue);
USER_FUNC(evt_mobj_timerswitch);
USER_FUNC(evt_mobj_floatswitch_red);
USER_FUNC(evt_mobj_switch_red);
USER_FUNC(evt_mobj_tornadoswitch_blue);
USER_FUNC(evt_mobj_floatswitch_blue);
USER_FUNC(evt_mobj_switch_blue);
USER_FUNC(evt_mobj_hit_onoff);
USER_FUNC(evt_mobj_hitevt_onoff);
USER_FUNC(evt_mobj_set_camid);
USER_FUNC(evt_mobj_wait_animation_end);
USER_FUNC(evt_mobj_set_anim);
USER_FUNC(evt_mobj_set_gravity_bound);
USER_FUNC(evt_mobj_exec_cancel);
USER_FUNC(evt_mobj_set_z_position);
USER_FUNC(evt_mobj_set_y_position);
USER_FUNC(evt_mobj_set_x_position);
USER_FUNC(evt_mobj_set_position);
USER_FUNC(evt_mobj_get_z_position);
USER_FUNC(evt_mobj_get_y_position);
USER_FUNC(evt_mobj_get_x_position);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_set_scale);
USER_FUNC(evt_mobj_get_kindname);
USER_FUNC(evt_mobj_flag_onoff);
USER_FUNC(evt_mobj_check);
USER_FUNC(evt_mobj_delete);
USER_FUNC(evt_mobj_entry);

extern s32 mobjEntry(const char* name, const char* animPoseName);
extern void mobjDelete(const char* name);
extern void hitGrpFlagOn(const char* name, u32 flag);
extern EventEntry* mobjRunEvent(MapObjectEntry* mobj, s32* eventCode);
extern s32 psndSFXOn_3D(const char* name, Vec* position);
extern s32 kpaGetLevel(void);
extern void kpaAddScore(s32 score);
extern void kpaAddScorePos(s32 score, Vec* pos);
extern void kpaPowUp(void);
extern void hitGrpFlagOff(const char* name, u32 flag);

static inline MapObjectEntry* MOBJ_PTR(EventEntry* event, const char* name) {
    return strcmp(name, "me\0") ? mobjNameToPtr(name) : event->thisMapObj;
}

static inline MapObjectEntry* MOBJ_PTR2(EventEntry* event, const char* name) {
    return !strcmp(name, "me\0") ? event->thisMapObj : mobjNameToPtr(name);
}

__declspec(section ".data") u64 fd_evt_mobj_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") u64 lbl_80309CF0 = 0xBF8000003F800000;

__declspec(section ".data") u64 fd_evt_mobj_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") u64 lbl_80309D00 = 0x3F800000BF800000;

__declspec(section ".data") u64 fd_evt_mobj_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") u64 lbl_80309D10 = 0xBF8000003F800000;

__declspec(section ".data") u64 fd_evt_mobj_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") u64 lbl_80309D20 = 0x3F800000BF800000;


extern s32 evt_cam_shake(EventEntry* event, BOOL isFirstCall);
static s32 evt_shake[] = {0x0005005B, (s32)evt_cam_shake, 4, 0xF24A7A80, 0xF24A7A8A, 200, 2, 1};
const char* _switch_anim[] = {(char*)str_8041A118, (char*)str_8041A11C, (char*)str_8041A120, (char*)str_8041A124, (char*)str_8041A128, (char*)str_8041A12C};

#define FLD(type, p, off) (*(type*)((u8*)(p) + (off)))
extern void marioChgJumpStandMotion(f32 power);
extern s32 irand(s32 max);
extern s32 psndSFXOn(const char* name);
extern s32 marioGetPartyId(void);

s32 mobj_lv_blk_evt(MapObjectEntry* mobj);

static inline HitEntry* blkHitCheck(MapObjectEntry* m) {
    f32 hx, hy, hz, dist, nx, ny, nz;
    dist = 1.0f + (f32)__fabs(m->velocity.y);
    return hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, m->position.x, m->position.y + 0.5f, m->position.z, 0.0f, -1.0f, 0.0f);
}

static inline BOOL isAnimA13(const s8* a) {
    if (a[0] == 'A' && a[2] >= '1' && a[2] <= '3') {
        return TRUE;
    }
    return FALSE;
}

extern void* itemEntry(f32 x, f32 y, f32 z, const char* name, s32 id, s32 mode, s32 collect, void* script);
extern void itemForceGet(void* item);
extern void* itemNameToPtr(char* name);
extern void itemFlagOn(void* item, u32 flag);
extern s16 pouchAddCoin(s16 coins);
extern void marioStSystemLevel(s32 level);
extern s32 mobj_save_blk_sysevt[];
s32 mobj_recovery_blk(MapObjectEntry* mobj);

extern void mobjHitEntry(MapObjectEntry* mobj, s32 idx);
extern void npcKoopaModeMobjBoundDeadCheck(void* hit);
extern void effMObjBrokenEntry(s32 type, f32 x, f32 y, f32 z);
s32 mobj_koopa_brickblk(MapObjectEntry* mobj);
s32 mobj_koopa_badgeblk(MapObjectEntry* mobj);

s32 mobj_brickblk(MapObjectEntry* mobj);

extern s32 kpaMutekiCheck(void);
extern void kpaAddCoin(s32 coin);
extern void itemStatusOn(void* item, u32 flag);
s32 kpa_powerup(EventEntry* event, BOOL isFirstCall);
s32 fire_func(EventEntry* event, BOOL isFirstCall);
s32 kpa_powerup_evt[] = {0x0004005B, (s32)kpa_powerup, 0xFE363C80, 0xFE363C81, 0xFE363C82, 2, 1};
s32 evt_fire[] = {0x0005005B, (s32)fire_func, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0xFE363C83, 2, 1};

extern void partyKeyOff(void);
extern void mapGrpFlagOn(const char* name, u32 flag);
extern void animPoseWorldPositionEvalOn(s32 poseId);
s32 mobj_koopa_sango_evt(MapObjectEntry* mobj);
s32 mobj_koopa_fireber_dodai_evt(MapObjectEntry* mobj);
#include "driver/imgdrv.h"
#include "driver/offscreendrv.h"
#include "driver/camdrv.h"
#include "system.h"
extern s32 evt_img_alloc_capture(EventEntry* event, BOOL isFirstCall);
extern void test_kururing_mapdisp(s32 camId);
extern double tan(double);
#include "driver/npcdrv.h"
extern void mobjSetPosition();
extern void strcat();
extern int sprintf(char*, const char*, ...);
s32 mobj_kururing_floor(MapObjectEntry* mobj);
s32 mobj_lock(MapObjectEntry* mobj);

USER_FUNC(evt_cam3d_event_from_road);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam3d_get_shift);
USER_FUNC(evt_cam_get_at);
USER_FUNC(evt_cam_get_pos);
USER_FUNC(evt_cam_letter_box_disable);
USER_FUNC(evt_cam_letter_box_onoff);
USER_FUNC(evt_cam_shake);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mario_cam_y_on);
USER_FUNC(evt_mario_cont_onoff);
USER_FUNC(evt_mario_dispflag_onoff);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_mov_spd);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_wait_landon);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_get_mapname);
USER_FUNC(kpa_chg_pose);
USER_FUNC(kpa_clear_jump_data);
USER_FUNC(kpa_disp_pole_init);
USER_FUNC(kpa_disp_pole_score_main);
USER_FUNC(kpa_get_hata_name);
USER_FUNC(kpa_get_pole_name);
USER_FUNC(kpa_get_width);
USER_FUNC(kpa_powerup);
USER_FUNC(kpa_score_to_str);
static USER_FUNC(kpa_get_level);
extern s32 evt_memcard_save[];

// ---- BEGIN tail (defined in reverse of target order) ----

#ifdef NONMATCHING
USER_FUNC(evt_mobj_entry) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    const char* anim = (const char*)evtGetValue(event, args[1]);
    if (animGroupBaseAsync(anim, gp->inBattle != 0, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_delete) {
    mobjDelete((const char*)evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_check) {
    s32* args = event->args;
    MapObjectEntry* mobj = mobjNameToPtrNoAssert((const char*)evtGetValue(event, args[0]));
    evtSetValue(event, args[1], (s32)mobj);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_flag_onoff) {
    s32* args = event->args;
    s32 on = evtGetValue(event, args[0]);
    const char* name = (const char*)evtGetValue(event, args[1]);
    s32 mask = args[2];
    MapObjectEntry* mobj = mobjNameToPtr(name);
    if (on) {
        mobj->flags |= mask;
    } else {
        mobj->flags &= ~mask;
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_get_kindname) {
    s32* args = event->args;
    MapObjectEntry* mobj = mobjNameToPtr((const char*)evtGetValue(event, args[0]));
    evtSetValue(event, args[1], (s32)mobj->animName);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_set_scale) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    MapObjectEntry* mobj;
    f32 x, y, z;
    Vec scale;
    mobj = MOBJ_PTR2(event, name);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    {
    Vec s2 = {0.0f, 0.0f, 0.0f};
    scale = s2;
    }
    scale.x = x;
    scale.y = y;
    scale.z = z;
    mobj->scale = scale;
    mobj->flags |= 4;
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_get_position) {
    s32* args = event->args;
    MapObjectEntry* mobj = MOBJ_PTR(event, (const char*)evtGetValue(event, args[0]));
    evtSetFloat(event, args[1], mobj->position.x);
    evtSetFloat(event, args[2], mobj->position.y);
    evtSetFloat(event, args[3], mobj->position.z);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_get_x_position) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    evtSetFloat(event, args[1], mobj->position.x);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_get_y_position) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    evtSetFloat(event, args[1], mobj->position.y);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_get_z_position) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    evtSetFloat(event, args[1], mobj->position.z);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_set_position) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    Vec pos = {0.0f, 0.0f, 0.0f};
    pos.x = x;
    pos.y = y;
    pos.z = z;
    mobj->position = pos;
    mobj->flags |= 4;
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_set_x_position) {
    s32* args = event->args;
    MapObjectEntry* mobj = MOBJ_PTR(event, (const char*)evtGetValue(event, args[0]));
    Vec pos = mobj->position;
    pos.x = evtGetFloat(event, args[1]);
    mobj->position = pos;
    mobj->flags |= 4;
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_set_y_position) {
    s32* args = event->args;
    MapObjectEntry* mobj = MOBJ_PTR(event, (const char*)evtGetValue(event, args[0]));
    Vec pos = mobj->position;
    pos.y = evtGetFloat(event, args[1]);
    mobj->position = pos;
    mobj->flags |= 4;
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_set_z_position) {
    s32* args = event->args;
    MapObjectEntry* mobj = MOBJ_PTR(event, (const char*)evtGetValue(event, args[0]));
    Vec pos = mobj->position;
    pos.z = evtGetFloat(event, args[1]);
    mobj->position = pos;
    mobj->flags |= 4;
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_exec_cancel) {
    MapObjectEntry* mobj = MOBJ_PTR(event, (const char*)evtGetValue(event, event->args[0]));
    mobj->flags |= 0x1000;
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_set_gravity_bound) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 a = evtGetFloat(event, args[1]);
    f32 b = evtGetFloat(event, args[2]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    mobj->gravity = a;
    mobj->bounce = b;
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_set_anim) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    const char* anim = (const char*)evtGetValue(event, args[1]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    animPoseSetAnim(mobj->poseId, anim, 1);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_wait_animation_end) {
    const char* name = (const char*)evtGetValue(event, event->args[0]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    if (animPoseGetLoopTimes(mobj->poseId) > 1.0f) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_set_camid) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    u8 cam = evtGetValue(event, args[1]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    mobj->camId = cam;
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_hitevt_onoff) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 on = evtGetValue(event, args[1]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    if (on) {
        mobj->flags &= ~0x10;
    } else {
        mobj->flags |= 0x10;
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_hit_onoff) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 on = evtGetValue(event, args[1]);
    MapObjectEntry* mobj = mobjNameToPtr(name);
    s32 i;
    if (on) {
        for (i = 0; i < 2; i++) {
            if (mobj->hitObj[i].name) {
                hitGrpFlagOff(mobj->hitObj[i].name, 1);
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            if (mobj->hitObj[i].name) {
                hitGrpFlagOn(mobj->hitObj[i].name, 1);
            }
        }
    }
    return EVT_RETURN_DONE;
}
#endif

// ---- switches ----

#ifdef NONMATCHING
s32 mobj_switch_blue(MapObjectEntry* mobj) {
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            mobjRunEvent(mobj, (s32*)mobj->event);
            if (mobj->hitFlag == 0x200000 || mobj->hitFlag == 0x1000000) {
                marioChgMot(MARIO_MOTION_JUMP_SW);
            }
            psndSFXOn_3D((const char*)0x1d2, &mobj->position);
            animPoseSetAnim(mobj->poseId, "A_1", 1);
            mobj->state++;
        }
        break;
    case 1:
        if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
            break;
        }
        animPoseSetAnim(mobj->poseId, "S_1", 1);
        effSmallStarCamChg(effSmallStarEntry(0, 4, mobj->position.x, mobj->position.y + 12.5f, mobj->position.z, 0.0f, -1.0f, 0.0f), mobj->camId);
        evtSetValue(NULL, mobj->flagVar, 1);
        mobj->state = 0x63;
    case 0x63:
        mobjDelete(mobj->name);
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_switch_blue) {
    s32 arg6;
    s32 val;
    s32* args = event->args;
    s32 kind;
    s32 inBattle;
    const char* anim;
    const char* name;
    MapObjectEntry* mobj;
    f32 x, y, z;
    kind = evtGetValue(event, args[0]);
    name = (const char*)evtGetValue(event, args[1]);
    x = evtGetFloat(event, args[2]);
    y = evtGetFloat(event, args[3]);
    z = evtGetFloat(event, args[4]);
    val = evtGetValue(event, args[5]);
    arg6 = args[6];
    inBattle = gp->inBattle != 0;
    switch (kind) {
    case 0:
        anim = "MOBJ_BlueSwitch";
        break;
    case 1:
        anim = "MOBJ_BlackSwitch";
        break;
    case 2:
    default:
        anim = "HOBJ_BlueSwitch\0\0\0\0";
        break;
    }
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_switch_blue;
    mobj->event = val;
    mobj->flags |= 0x44;
    mobj->flags |= 0xa10000;
    mobj->flagVar = arg6;
    mobj->state = 0;
    if (kind == 2) {
        mobj->flags |= 2;
    }
    if (evtGetValue(event, arg6)) {
        mobj->state = 99;
    }
    mobjCalcMtx(mobj);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_floatswitch_blue) {
    s32* args = event->args;
    s32 arg6;
    f32 x, y, z;
    const char* name;
    MapObjectEntry* mobj;
    s32 val;
    const char* anim;
    s32 inBattle;
    evtGetValue(event, args[0]);
    name = (const char*)evtGetValue(event, args[1]);
    x = evtGetFloat(event, args[2]);
    y = evtGetFloat(event, args[3]);
    z = evtGetFloat(event, args[4]);
    val = evtGetValue(event, args[5]);
    arg6 = args[6];
    inBattle = gp->inBattle;
    inBattle = inBattle != 0;
    anim = "MOBJ_BlueSwitchBlock";
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_switch_blue;
    mobj->event = val;
    mobj->flags |= 4;
    mobj->flags |= 0x400000;
    mobj->flagVar = arg6;
    mobj->state = 0;
    if (evtGetValue(event, arg6)) {
        mobj->state = 99;
    }
    mobjCalcMtx(mobj);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_tornadoswitch_blue) {
    s32* args = event->args;
    s32 arg6;
    f32 x, y, z;
    const char* name;
    MapObjectEntry* mobj;
    s32 val;
    const char* anim;
    s32 inBattle;
    evtGetValue(event, args[0]);
    name = (const char*)evtGetValue(event, args[1]);
    x = evtGetFloat(event, args[2]);
    y = evtGetFloat(event, args[3]);
    z = evtGetFloat(event, args[4]);
    val = evtGetValue(event, args[5]);
    arg6 = args[6];
    inBattle = gp->inBattle;
    inBattle = inBattle != 0;
    anim = "MOBJ_BlueTornadoSwitch";
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_switch_blue;
    mobj->event = val;
    mobj->flags |= 4;
    mobj->flags |= 0x1000000;
    mobj->flagVar = arg6;
    mobj->state = 0;
    if (evtGetValue(event, arg6)) {
        mobj->state = 99;
    }
    mobjCalcMtx(mobj);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_switch_red(MapObjectEntry* mobj) {
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            mobjRunEvent(mobj, (s32*)mobj->event);
            if (mobj->hitFlag == 0x200000 || mobj->hitFlag == 0x1000000) {
                marioChgMot(MARIO_MOTION_JUMP_SW);
            }
            psndSFXOn_3D((const char*)0x1d2, &mobj->position);
            animPoseSetAnim(mobj->poseId, "A_1", 1);
            mobj->flags &= ~8;
        }
        break;
    case 1:
        if (mobj->flags & 8) {
            psndSFXOn_3D((const char*)0x1d2, &mobj->position);
            if (mobj->hitFlag == 0x200000) {
                marioChgMot(MARIO_MOTION_JUMP_SW);
            }
            animPoseSetAnim(mobj->poseId, "A_1", 1);
            mobj->flags &= ~8;
        }
        if (!(animPoseGetLoopTimes(mobj->poseId) < 1.0f)) {
            animPoseSetAnim(mobj->poseId, "S_1", 1);
            mobj->flags &= ~8;
            mobj->state = 0;
        }
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_switch_red) {
    s32 arg6;
    s32 val;
    s32* args = event->args;
    s32 kind;
    s32 inBattle;
    const char* anim;
    const char* name;
    MapObjectEntry* mobj;
    f32 x, y, z;
    kind = evtGetValue(event, args[0]);
    name = (const char*)evtGetValue(event, args[1]);
    x = evtGetFloat(event, args[2]);
    y = evtGetFloat(event, args[3]);
    z = evtGetFloat(event, args[4]);
    val = evtGetValue(event, args[5]);
    arg6 = args[6];
    inBattle = gp->inBattle != 0;
    switch (kind) {
    case 0:
        anim = "MOBJ_RedSwitch";
        break;
    case 1:
    default:
        anim = "MOBJ_WhiteSwitch";
        break;
    }
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_switch_red;
    mobj->event = val;
    mobj->flags |= 0x44;
    mobj->flags |= 0xa10000;
    mobj->flagVar = arg6;
    mobj->state = 0;
    mobjCalcMtx(mobj);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_floatswitch_red) {
    s32* args = event->args;
    s32 arg6;
    f32 x, y, z;
    const char* name;
    MapObjectEntry* mobj;
    s32 val;
    const char* anim;
    s32 inBattle;
    evtGetValue(event, args[0]);
    name = (const char*)evtGetValue(event, args[1]);
    x = evtGetFloat(event, args[2]);
    y = evtGetFloat(event, args[3]);
    z = evtGetFloat(event, args[4]);
    val = evtGetValue(event, args[5]);
    arg6 = args[6];
    inBattle = gp->inBattle;
    inBattle = inBattle != 0;
    anim = "MOBJ_RedSwitchBlock";
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_switch_red;
    mobj->event = val;
    mobj->flags |= 4;
    mobj->flags |= 0x400000;
    mobj->flagVar = arg6;
    mobj->state = 0;
    if (evtGetValue(event, arg6)) {
        mobj->state = 99;
    }
    mobjCalcMtx(mobj);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_timerswitch(MapObjectEntry* mobj) {
    MapObjectEntry* other = mobjNameToPtr(mobj->linkedName);
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            if (mobj->hitFlag == 0x200000) {
                marioChgMot(MARIO_MOTION_JUMP_SW);
            }
            if (other->state != 2) {
                psndSFXOn_3D((const char*)0x1c1, &mobj->position);
            } else {
                psndSFXOn_3D((const char*)0x1c2, &mobj->position);
            }
            evtEntryType(evt_shake, 0, 0, 0);
            animPoseSetAnim(mobj->poseId, "A_1", 1);
            mobj->state++;
            mobj->flags &= ~8;
        }
        break;
    case 1:
        if (mobj->flags & 8) {
            animPoseSetAnim(mobj->poseId, "S_1", 1);
            animPoseSetAnim(other->poseId, "S_1", 1);
            mobj->state = 0;
            break;
        }
        if (animPoseGetLoopTimes(mobj->poseId) < 0.3f) {
            break;
        }
        animPoseSetAnim(mobj->poseId, "A_2", 1);
        animPoseSetAnim(other->poseId, "A_2", 1);
        mobj->state++;
        mobj->unk1B0 = mobj->unk1B4;
        mobj->flags &= ~8;
        break;
    case 2:
        if (mobj->flags & 8) {
            animPoseSetAnim(mobj->poseId, "S_1", 1);
            animPoseSetAnim(other->poseId, "S_1", 1);
            mobj->state = 0;
            break;
        }
        mobj->unk1B0--;
        if (mobj->unk1B0 <= 0) {
            mobj->flags &= ~8;
            animPoseSetAnim(mobj->poseId, "S_1", 1);
            animPoseSetAnim(other->poseId, "S_1", 1);
            mobj->state = 0;
            break;
        }
        if (other->state == 2) {
            if (marioKeyOffChk() || marioCtrlOffChk()) {
                mobj->state = 0;
                break;
            }
            mobjRunEvent(mobj, (s32*)mobj->event);
            if (!strcmp(mobj->animName, "MOBJ_RedTimerSwitch")) {
                mobj->flags &= ~8;
                other->flags &= ~8;
                animPoseSetAnim(mobj->poseId, "S_1", 1);
                animPoseSetAnim(other->poseId, "S_1", 1);
                mobj->state = 0;
                other->state = 0;
                break;
            }
            effSmallStarEntry(0, 8, mobj->position.x, mobj->position.y + 12.5f, mobj->position.z, 0.0f, -1.0f, 0.0f);
            effSmallStarEntry(0, 8, other->position.x, other->position.y + 12.5f, other->position.z, 0.0f, -1.0f, 0.0f);
            evtSetValue(NULL, mobj->flagVar, 1);
            evtSetValue(NULL, other->flagVar, 1);
            mobjDelete(mobj->name);
            mobjDelete(other->name);
        }
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_timerswitch) {
    const char* names[2];
    s32 arg;
    s32 i;
    f32 x[2];
    f32 y[2];
    f32 z[2];
    MapObjectEntry* mobjs[2];
    s32* args = event->args;
    s32 kind = evtGetValue(event, args[0]);
    s32 inBattle = gp->inBattle != 0;
    const char* anims[2] = {"MOBJ_BlueTimerSwitch", "MOBJ_RedTimerSwitch"};
    const char* anim = anims[kind];
    s32 time;
    s32 val;
    names[0] = (const char*)evtGetValue(event, args[1]);
    x[0] = evtGetFloat(event, args[2]);
    y[0] = evtGetFloat(event, args[3]);
    z[0] = evtGetFloat(event, args[4]);
    names[1] = (const char*)evtGetValue(event, args[5]);
    x[1] = evtGetFloat(event, args[6]);
    y[1] = evtGetFloat(event, args[7]);
    z[1] = evtGetFloat(event, args[8]);
    time = evtGetValue(event, args[9]);
    val = evtGetValue(event, args[10]);
    arg = args[11];
    if (kind == 0 && evtGetValue(event, arg)) {
        return EVT_RETURN_DONE;
    }
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    for (i = 0; i < 2; i++) {
        mobjEntry(names[i], anim);
        mobjs[i] = mobjNameToPtr(names[i]);
        strcpy(mobjs[i]->linkedName, i == 0 ? names[1] : names[0]);
        mobjSetPosition(names[i], x[i], y[i], z[i]);
        mobjs[i]->mainFunc = mobj_timerswitch;
        mobjs[i]->event = val;
        mobjs[i]->flags |= 0x44;
        mobjs[i]->flags |= 0xa10000;
        mobjs[i]->flagVar = arg;
        mobjs[i]->state = 0;
        mobjs[i]->unk1B4 = time;
        if (evtGetValue(event, arg)) {
            mobjs[i]->state = 99;
        }
        mobjCalcMtx(mobjs[i]);
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_rideswitch_lightblue(MapObjectEntry* mobj) {
    f32 x, y, z;
    void* data;
    f32 mag;
    Vec size;
    {
        Vec d1 = (Vec){x, y, z};
        Vec d2 = (Vec){x, y, z};
        Vec d3 = (Vec){x, y, z};
        Vec d4 = (Vec){x, y, z};
    }
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            mobjRunEvent(mobj, (s32*)mobj->event);
            psndSFXOn_3D((const char*)0x1d3, &mobj->position);
            animPoseSetAnim(mobj->poseId, "A_1", 1);
            mobj->state = 1;
        }
        break;
    case 1:
        y = mobj->scale2.y - 0.9f;
        x = mobj->scale2.x;
        z = mobj->scale2.z;
        if (y <= 0.2f) {
            mobj->state = 2;
            y = 0.2f;
            mobj->flags &= ~8;
        }
        mobj->scale2 = (Vec){x, y, z};
        mobjCalcMtx2(mobj);
        break;
    case 2:
        data = animPoseGetAnimBaseDataPtr(mobj->poseId);
        size = (Vec){0.8f * (10.0f * FLD(f32, data, 0xdc)), 10.0f * FLD(f32, data, 0xe0), 0.8f * (10.0f * FLD(f32, data, 0xe4))};
        mag = PSVECMag(&size);
        if (PSVECDistance(&mobj->position, &FLD(Vec, marioGetPtr(), 0x8c)) > mag) {
            if (!(mobj->flags & 8)) {
                mobj->state = 3;
                animPoseSetAnim(mobj->poseId, "A_2", 1);
                psndSFXOn_3D((const char*)0x1d4, &mobj->position);
                mobjRunEvent(mobj, (s32*)mobj->extraEvent);
            } else {
                mobj->flags &= ~8;
            }
        }
        break;
    case 3:
        x = mobj->scale2.x;
        y = mobj->scale2.y;
        z = mobj->scale2.z;
        y += 0.9f;
        if (y >= 15.0f) {
            mobj->state = 0;
            y = 15.0f;
        }
        mobj->scale2 = (Vec){x, y, z};
        mobjCalcMtx2(mobj);
        mobj->flags &= ~8;
        break;
    case 99:
        break;
    }
    return 0;
}
#endif







#ifdef NONMATCHING /* not in the target object (dead code stripped at link) */
void evt_mobj_rideswitch(void) {
    mobjNameToPtr("MOBJ_RideSwitchB");
    mobjNameToPtr("MOBJ_RideSwitchA");
    mobjNameToPtr("MOBJ_RedTornadoSwitch");
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_rideswitch_lightblue) {
    s32 val2;
    s32 val;
    s32* args = event->args;
    const char* name;
    f32 x, y, z;
    s32 arg6;
    MapObjectEntry* mobj;
    const char* anim;
    s32 inBattle;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    val = evtGetValue(event, args[4]);
    val2 = evtGetValue(event, args[5]);
    arg6 = args[6];
    if (animGroupBaseAsync(anim = "MOBJ_RideSwitchC", gp->inBattle ? 1 : 0, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobj->scale2.x *= 0.8f;
    mobj->scale2.z *= 0.8f;
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_rideswitch_lightblue;
    mobj->event = val;
    mobj->extraEvent = val2;
    mobj->flags |= 4;
    mobj->flags |= 0x200000;
    mobj->flagVar = arg6;
    mobj->state = 0;
    mobjCalcMtx2(mobj);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_jumpstand_red(MapObjectEntry* mobj) {
    void* mario = marioGetPtr();
    EventEntry* ev;
    partyGetPtr(marioGetPartyId());
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            FLD(s32, gp, 0x18) |= 0x10;
            ev = mobjRunEvent(mobj, (s32*)mobj->event);
            if (ev) {
                FLD(s32, ev, 0x9c) = FLD(f32, mario, 0xd8) < FLD(f32, mario, 0x90) ? 0 : (FLD(f32, mario, 0xd8) < mobj->position.y + FLD(f32, mario, 0x1b8) ? 0 : 1);
            }
            if ((s32)FLD(u8, mario, 0x3c) != 2) {
                if (!strcmp(mobj->animName, "MOBJ_RedJumpStand")) {
                    psndSFXOn_3D((const char*)0x1eb, &mobj->position);
                } else {
                    psndSFXOn_3D((const char*)0x1ec, &mobj->position);
                }
                switch (irand(4)) {
                case 0:
                    psndSFXOn_3D((const char*)0xab, &mobj->position);
                    break;
                case 1:
                    psndSFXOn_3D((const char*)0xac, &mobj->position);
                    break;
                case 2:
                    psndSFXOn_3D((const char*)0xad, &mobj->position);
                    break;
                case 3:
                    psndSFXOn_3D((const char*)0xae, &mobj->position);
                    break;
                case 4:
                    psndSFXOn_3D((const char*)0xaf, &mobj->position);
                    break;
                }
            } else if (!strcmp(mobj->animName, "MOBJ_RedJumpStand")) {
                psndSFXOn((const char*)0x1eb);
                do { } while (0);
            } else {
                psndSFXOn((const char*)0x1ec);
            }
            animPoseSetAnim(mobj->poseId, "A_1", 1);
            mobj->flags &= ~8;
            mobj->state++;
        }
        break;
    case 1:
        if ((mobj->flags & 8) && evtCheckID(mobj->eventId) == 0) {
            animPoseSetAnim(mobj->poseId, "S_1", 1);
            mobj->state = 0;
            break;
        }
        if (evtCheckID(mobj->eventId) == 1) {
            break;
        }
        FLD(s32, gp, 0x18) &= ~0x10;
        if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
            break;
        }
        animPoseSetAnim(mobj->poseId, "S_1", 1);
        mobj->state = 0;
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_jumpstand_red) {
    MapObjectEntry* mobj;
    s32* args = event->args;
    s32 kind = evtGetValue(event, args[0]);
    const char* name = (const char*)evtGetValue(event, args[1]);
    f32 x = evtGetFloat(event, args[2]);
    f32 y = evtGetFloat(event, args[3]);
    f32 z = evtGetFloat(event, args[4]);
    s32 val = evtGetValue(event, args[5]);
    s32 arg6 = args[6];
    s32 inBattle = gp->inBattle ? 1 : 0;
    const char* anims[2] = {"MOBJ_RedJumpStand", "MOBJ_RedJumpStand2"};
    if (animGroupBaseAsync(anims[kind], inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anims[kind]);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_jumpstand_red;
    mobj->event = val;
    mobj->flags |= 0x44;
    mobj->flags |= 0x200000;
    mobj->flagVar = arg6;
    mobj->state = 0;
    mobjCalcMtx(mobj);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_jumpstand_blue(MapObjectEntry* mobj) {
    void* mario = marioGetPtr();
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            FLD(s32, gp, 0x18) |= 0x10;
            mobjRunEvent(mobj, (s32*)mobj->event);
            if (mobj->hitFlag == 0x200000) {
                marioChgJumpStandMotion(FLD(f32, mobj, 0x1ac));
            }
            if (FLD(s8, mario, 0x3c) != 2) {
                if (!strcmp(mobj->animName, "MOBJ_BlueJumpStand")) {
                    psndSFXOn_3D((const char*)0x1eb, &mobj->position);
                } else {
                    psndSFXOn_3D((const char*)0x1ec, &mobj->position);
                }
                switch (irand(4)) {
                case 0:
                    psndSFXOn_3D((const char*)0xab, &mobj->position);
                    break;
                case 1:
                    psndSFXOn_3D((const char*)0xac, &mobj->position);
                    break;
                case 2:
                    psndSFXOn_3D((const char*)0xad, &mobj->position);
                    break;
                case 3:
                    psndSFXOn_3D((const char*)0xae, &mobj->position);
                    break;
                case 4:
                    psndSFXOn_3D((const char*)0xaf, &mobj->position);
                    break;
                }
            } else if (!strcmp(mobj->animName, "MOBJ_BlueJumpStand")) {
                psndSFXOn((const char*)0x1eb);
            } else {
                psndSFXOn((const char*)0x1ec);
            }
            animPoseSetAnim(mobj->poseId, "A_1", 1);
            mobj->flags &= ~8;
            mobj->state++;
        }
        break;
    case 1:
        if (mobj->flags & 8) {
            animPoseSetAnim(mobj->poseId, "S_1", 1);
            mobj->state = 0;
            break;
        }
        if (evtCheckID(mobj->eventId) == 1) {
            break;
        }
        FLD(s32, gp, 0x18) &= ~0x10;
        if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
            break;
        }
        animPoseSetAnim(mobj->poseId, "S_1", 1);
        mobj->state = 0;
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_jumpstand_blue) {
    MapObjectEntry* mobj;
    s32* args = event->args;
    s32 kind = evtGetValue(event, args[0]);
    const char* name = (const char*)evtGetValue(event, args[1]);
    f32 power = evtGetFloat(event, args[2]);
    f32 x = evtGetFloat(event, args[3]);
    f32 y = evtGetFloat(event, args[4]);
    f32 z = evtGetFloat(event, args[5]);
    s32 val = evtGetValue(event, args[6]);
    s32 inBattle = gp->inBattle ? 1 : 0;
    const char* anims[2] = {"MOBJ_BlueJumpStand", "MOBJ_BlueJumpStand2"};
    s32 arg7 = args[7];
    if (animGroupBaseAsync(anims[kind], inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anims[kind]);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_jumpstand_blue;
    mobj->event = val;
    mobj->flags |= 0x44;
    mobj->flags |= 0x200000;
    mobj->flagVar = arg7;
    mobj->state = 0;
    FLD(f32, mobj, 0x1ac) = power;
    mobjCalcMtx(mobj);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_lv_blk_evt(MapObjectEntry* mobj) {
    char oname[16] = "o_";
    char iname[16] = "i_";
    EventEntry ev1;
    EventEntry ev2;
    s32 args1[10];
    s32 args2[10];
    ImageEntry* img;
    s32 type = gp->inBattle != 0;
    void* mario = marioGetPtr();
    strcat(oname, mobj->name);
    strcat(iname, mobj->name);
    switch (mobj->state) {
    case 0:
        animGroupBaseAsync("P_box_y", type, NULL);
        if (mobj->flags & 8) {
            if (!strcmp(mobj->animName, "MOBJ_Lv1Block") || !strcmp(mobj->animName, "MOBJ_Lv1BigBlock")) {
            } else if (!strcmp(mobj->animName, "MOBJ_Lv1BigBigBlock")) {
                if (pouchGetHammerLv() < 2 || FLD(u16, mario, 0x2e) != 0x13) {
                    mobj->flags &= ~8;
                    break;
                }
            } else if (!strcmp(mobj->animName, "MOBJ_Lv2Block") || !strcmp(mobj->animName, "MOBJ_Lv2BigBlock")) {
                if (pouchGetHammerLv() < 3) {
                    mobj->flags &= ~8;
                    break;
                }
            } else if (!strcmp(mobj->animName, "MOBJ_Lv2BigBigBlock")) {
                if (pouchGetHammerLv() < 3 || FLD(u16, mario, 0x2e) != 0x13) {
                    mobj->flags &= ~8;
                    break;
                }
            } else {
                mobj->flags &= ~8;
                break;
            }
            mobjRunEvent(mobj, (s32*)mobj->event);
            evtSetValue(NULL, mobj->flagVar, 1);
            mobj->state = 10;
        }
        break;
    case 10:
        animPaperPoseEntry("P_box_y", type);
        offscreenEntry(oname);
        imgEntry(iname, type);
        mobj->offscreenId = offscreenNameToId(oname);
        ev1.args = args1;
        args1[0] = (s32)iname; args1[1] = 0; args1[2] = (s32)oname; args1[3] = 1;
        args1[4] = 0; args1[5] = 0; args1[6] = 0; args1[7] = 0;
        evt_img_alloc_capture(&ev1, TRUE);
        ev2.args = args2;
        args2[0] = (s32)iname; args2[1] = 1; args2[2] = (s32)oname; args2[3] = 1;
        args2[4] = 0; args2[5] = 0; args2[6] = 0; args2[7] = 0;
        evt_img_alloc_capture(&ev2, TRUE);
        img = imgNameToPtr(iname, type);
        img->poseId = animPaperPoseGetId("P_box_y", type);
        img->animName = (s32)"A_1";
        FLD(OSTime, img, 0x110) = animTimeGetTime(type);
        imgSetShadow(img, 2);
        if (!strcmp(mobj->animName, "MOBJ_Lv1Block") || !strcmp(mobj->animName, "MOBJ_Lv2Block")) {
            psndSFXOn_3D((const char*)0x1c7, &mobj->position);
        } else if (!strcmp(mobj->animName, "MOBJ_Lv1BigBlock") || !strcmp(mobj->animName, "MOBJ_Lv2BigBlock")) {
            psndSFXOn_3D((const char*)0x1c8, &mobj->position);
        } else if (!strcmp(mobj->animName, "MOBJ_Lv1BigBigBlock") || !strcmp(mobj->animName, "MOBJ_Lv2BigBigBlock")) {
            psndSFXOn_3D((const char*)0x1c9, &mobj->position);
        }
        mobj->state = 11;
        break;
    case 11:
        img = imgNameToPtr(iname, type);
        if (img->loopTimes >= 1.0f) {
            mobj->state = 12;
        }
        if (img->flags & 0x10000000) {
            mobj->state = 12;
        }
        mobj->position = (Vec){0.0f, -2000.0f, 0.0f};
        mobj->flags |= 4;
        mobj->flags |= 8;
        break;
    case 12:
        img = imgNameToPtr(iname, type);
        imgFreeCapture(img, 0);
        imgFreeCapture(img, 1);
        imgSetShadow(img, 0);
        imgRelease(img, type);
        offscreenDelete(oname);
        mobj->offscreenId = -1;
        mobj->state = 99;
        break;
    case 99:
        mobjDelete(mobj->name);
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_lv_blk) {
    s32 val;
    s32 arg5;
    s32* args = event->args;
    const char* anim;
    const char* name;
    s32 inBattle;
    MapObjectEntry* mobj;
    f32 x, y, z;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    val = evtGetValue(event, args[4]);
    arg5 = args[5];
    anim = (const char*)evtGetValue(event, args[6]);
    inBattle = gp->inBattle != 0;
    if (evtGetValue(event, arg5)) {
        return EVT_RETURN_DONE;
    }
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    if (animGroupBaseAsync("P_box_y", inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobj->flags |= 0x44;
    mobj->position = (Vec){x, y, z};
    mobj->mainFunc = mobj_lv_blk_evt;
    mobj->event = val;
    mobj->extraEvent = 0;
    mobj->flags |= 0x10000;
    mobj->flagVar = arg5;
    mobj->state = 0;
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_float_blk(MapObjectEntry* mobj) {
    MapObjectEntry* other;
    const char* cur;
    switch (mobj->state) {
    case 99:
        if (((s8*)mobj->linkedName)[0] == 0) {
            if ((s32)blkHitCheck(mobj)) {
                if (strcmp((const char*)animPoseGetCurrentAnim(mobj->poseId), "S_1")) {
                    animPoseSetAnim(mobj->poseId, "S_1", 1);
                    mobj->flags |= 2;
                }
            } else if (strcmp((const char*)animPoseGetCurrentAnim(mobj->poseId), "A_1")) {
                animPoseSetAnim(mobj->poseId, "A_1", 1);
                mobj->flags &= ~2;
            }
        } else {
            other = mobjNameToPtr(mobj->linkedName);
            cur = (const char*)animPoseGetCurrentAnim(other->poseId);
            if (((const s8*)cur)[0] == 'A' && ((const s8*)cur)[2] >= '1' && ((const s8*)cur)[2] <= '3') {
                animPoseSetAnim(mobj->poseId, "A_1", 0);
            } else {
                animPoseSetAnim(mobj->poseId, "S_1", 1);
            }
        }
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_float_blk) {
    s32 arg7;
    s32* args = event->args;
    const char* name;
    s32 color;
    s32 size;
    const char* model;
    MapObjectEntry* mobj;
    s32 inBattle;
    f32 x, y, z;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    color = args[4];
    size = args[5];
    evtGetValue(event, args[6]);
    arg7 = args[7];
    inBattle = gp->inBattle != 0;
    switch (color) {
    case 0:
        if (size == 0) {
            model = "MOBJ_green_FlowBlock";
        } else if (size == 1) {
            model = "MOBJ_green_big_FlowBlock";
        } else {
            model = "MOBJ_green_big02_FlowBlock";
        }
        break;
    case 1:
        if (size == 0) {
            model = "MOBJ_purple_FlowBlock";
        } else if (size == 1) {
            model = "MOBJ_purple_big_FlowBlock";
        } else {
            model = "MOBJ_purple_big02_FlowBlock";
        }
        break;
    case 2:
        if (size == 0) {
            model = "MOBJ_orange_FlowBlock";
        } else if (size == 1) {
            model = "MOBJ_orange_big_FlowBlock";
        } else {
            model = "MOBJ_orange_big02_FlowBlock";
        }
        break;
    case 3:
        model = "MOBJ_red_big02_FlowBlock";
        break;
    default:
        if (size == 0) {
            model = "MOBJ_green_FlowBlock";
        } else if (size == 1) {
            model = "MOBJ_green_big_FlowBlock";
        } else {
            model = "MOBJ_green_big02_FlowBlock";
        }
        break;
    }
    if (animGroupBaseAsync(model, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, model);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_float_blk;
    mobj->flags |= 4;
    mobj->flagVar = arg7;
    mobj->state = 99;
    mobjCalcMtx(mobj);
    if ((s32)blkHitCheck(mobj)) {
        animPoseSetAnim(mobj->poseId, "S_1", 1);
        mobj->flags |= 2;
    } else {
        animPoseSetAnim(mobj->poseId, "A_1", 1);
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_switch_float_blk(MapObjectEntry* mobj) {
    s32 i;
    s32 idx;
    const s8* cur;
    const char** p;
    s32 anim;
    BOOL a;
    switch (mobj->state) {
    case 0:
        if (!(mobj->flags & 8)) {
            break;
        }
        cur = (const s8*)animPoseGetCurrentAnim(mobj->poseId);
        idx = 0;
        p = (const char**)_switch_anim;
        i = idx;
        for (; i < 6; i++, p++) {
            if (!strcmp(*p, (const char*)cur)) {
                idx = i;
                break;
            }
        }
        mobj->typeData[1] = (mobj->typeData[1] & 0x40000000) | idx;
        if (((s8*)mobj->linkedName)[0]) {
            if ((s32)blkHitCheck(mobjNameToPtr(mobj->linkedName))) {
                if (evtCheckID(mobj->eventId)) {
                    if (isAnimA13((const s8*)animPoseGetCurrentAnim(mobj->poseId))) {
                        anim = 0;
                    } else {
                        anim = 3;
                    }
                } else {
                    mobj->typeDataU[1] |= 0x80000000;
                    anim = 0;
                }
            } else if (evtCheckID(mobj->eventId)) {
                cur = (const s8*)animPoseGetCurrentAnim(mobj->poseId);
                if (cur[0] == 'A' && cur[2] >= '1' && cur[2] <= '2') {
                    anim = 0;
                } else if (cur[0] == 'A' && cur[2] == '3') {
                    mobj->typeDataU[1] |= 0x40000000;
                    anim = 0;
                } else if (cur[0] == 'A' && cur[2] >= '4' && cur[2] <= '5') {
                    anim = 3;
                } else {
                    anim = 3;
                }
            } else {
                mobj->typeDataU[1] |= 0x80000000;
                anim = 3;
            }
        } else {
            a = isAnimA13((const s8*)animPoseGetCurrentAnim(mobj->poseId));
            anim = a ? 3 : 0;
            mobj->typeDataU[1] |= 0x80000000;
        }
        mobjRunEvent(mobj, (s32*)mobj->event);
        if (mobj->hitFlag == 0x200000) {
            marioChgMot(MARIO_MOTION_JUMP_SW);
        }
        psndSFXOn_3D((const char*)0x1b5, &mobj->position);
        switch (mobj->hitFlag) {
        case 0x400000:
            animPoseSetAnim(mobj->poseId, _switch_anim[anim + 1], 1);
            break;
        default:
            animPoseSetAnim(mobj->poseId, _switch_anim[anim], 1);
            break;
        }
        mobj->flags &= ~8;
        if (mobj->unk1B0) {
            mobj->state = 10;
        } else {
            mobj->state++;
        }
        break;
    case 1:
        if (mobj->flags & 8) {
            mobj->state = 0;
            break;
        }
        if (mobj->flags & 0x1000) {
            mobj->flags &= ~0x1000;
            mobj->state = 10;
            break;
        }
        if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
            break;
        }
        if (((s8*)mobj->linkedName)[0]) {
            mobjNameToPtr(mobj->linkedName);
        }
        {
            const char* a = isAnimA13((const s8*)animPoseGetCurrentAnim(mobj->poseId)) ? "A_3" : "S_1";
            animPoseSetAnim(mobj->poseId, a, 1);
        }
        mobj->state++;
        break;
    case 2:
        if (mobj->flags & 8) {
            mobj->state = 0;
            break;
        }
        if (mobj->flags & 0x1000) {
            mobj->flags &= ~0x1000;
            mobj->state = 10;
        }
        if (evtCheckID(mobj->eventId) == 0) {
            mobj->state = 0;
            mobj->typeData[1] = 0;
        }
        break;
    case 10:
        if (mobj->flags & 8) {
            mobj->state = 0;
            break;
        }
        if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
            break;
        }
        if (isAnimA13((const s8*)animPoseGetCurrentAnim(mobj->poseId))) {
            animPoseSetAnim(mobj->poseId, "A_3", 1);
        } else {
            animPoseSetAnim(mobj->poseId, "S_1", 1);
        }
        mobj->unk1B0 = 120;
        mobj->state++;
    case 11:
        if (mobj->flags & 8) {
            mobj->state = 0;
            break;
        }
        mobj->unk1B0--;
        if (mobj->unk1B0 != 0) {
            break;
        }
        if (((s8*)mobj->linkedName)[0]) {
            if ((s32)blkHitCheck(mobjNameToPtr(mobj->linkedName))) {
                animPoseSetAnim(mobj->poseId, "S_1", 0);
            } else {
                animPoseSetAnim(mobj->poseId, "A_3", 0);
            }
        } else if (isAnimA13((const s8*)animPoseGetCurrentAnim(mobj->poseId))) {
            animPoseSetAnim(mobj->poseId, "A_3", 1);
        } else {
            animPoseSetAnim(mobj->poseId, "S_1", 1);
        }
        mobj->state = 0;
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_switch_float_blk) {
    const char* name;
    s32 partner;
    s32 val;
    s32* args = event->args;
    s32 color;
    const char* anim;
    MapObjectEntry* mobj;
    MapObjectEntry* other;
    s32 inBattle;
    s32 arg7;
    f32 x, y, z;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    partner = evtGetValue(event, args[4]);
    color = args[5];
    val = evtGetValue(event, args[6]);
    arg7 = args[7];
    inBattle = gp->inBattle != 0;
    switch (color) {
    case 0:
        anim = "MOBJ_green_FlowBlockSwitch";
        break;
    case 1:
        anim = "MOBJ_purple_FlowBlockSwitch";
        break;
    case 2:
        anim = "MOBJ_orange_FlowBlockSwitch";
        break;
    case 3:
        anim = "MOBJ_red_FlowBlockSwitch";
        break;
    default:
        anim = "MOBJ_green_FlowBlockSwitch";
        break;
    }
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_switch_float_blk;
    mobj->event = val;
    mobj->flags |= 4;
    mobj->flags |= 0xe10000;
    mobj->flagVar = arg7;
    mobj->state = 0;
    mobj->unk1B0 = 0;
    mobjCalcMtx(mobj);
    strcpy(mobj->linkedName, (const char*)partner);
    if ((s32)(s8)mobj->linkedName[0]) {
        other = mobjNameToPtr(mobj->linkedName);
        strcpy(other->linkedName, mobj->name);
        if ((s32)blkHitCheck(other)) {
            animPoseSetAnim(mobj->poseId, "S_1", 1);
        } else {
            animPoseSetAnim(mobj->poseId, "A_3", 1);
        }
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_lock_unlock) {
    MapObjectEntry* mobj = mobjNameToPtr((const char*)evtGetValue(event, event->args[0]));
    if (strcmp(mobj->animName, "MOBJ_Lock")) {
        return EVT_RETURN_DONE;
    }
    if (!mobj->mainFunc) {
        mobj->mainFunc = mobj_lock;
    }
    mobj->flags |= 8;
    marioKeyOff();
    partyKeyOff();
    marioStSystemLevel(1);
    mobj->state = 3;
    return EVT_RETURN_DONE;
}
#endif

EVT_BEGIN(evt_lock_sound)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3F00), LW(0), LW(1), LW(2), 0)
    WAIT_MS(200)
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3F18), LW(0), LW(1), LW(2), 0)
    RETURN
EVT_END()

extern const char* msgSearch(const char* tag);
extern s32 msgWindow_Entry(const char* msg, s32 a, s32 b);
extern s32 windowCheckID(s32 id);
extern void partyKeyOn(void);

#ifdef NONMATCHING
s32 mobj_lock(MapObjectEntry* mobj) {
    s32 item;
    s32 i;
    EventEntry* ev;
    f32 hx, hy, hz, dist, nx, ny, nz;
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            marioKeyOff();
            partyKeyOff();
            marioStSystemLevel(1);
            mobjRunEvent(mobj, (s32*)mobj->event);
            mobj->state++;
        }
        break;
    case 1:
        if (evtCheckID(mobj->eventId) != 1) {
            if (mobj->flags & 0x1000) {
                mobj->flags &= ~0x1000;
                mobj->flags &= ~8;
                marioKeyOn();
                partyKeyOn();
                marioStSystemLevel(0);
                mobj->eventId = 0;
                mobj->state = 0;
            } else {
                mobj->eventId = 0;
                mobj->state++;
            }
        }
        break;
        if (mobj) {
        }
    case 2:
        if (mobj->typeDataU[0] & 0x80000000) {
            item = 0;
            for (i = 0; ; i++) {
                s32 it = ((s32*)mobj->typeDataP[0])[i];
                s32 r;
                if (it == -1) {
                    break;
                }
                r = pouchCheckItem(it);
                if (r) {
                    item = r;
                    break;
                }
            }
        } else if ((i = pouchCheckItem(mobj->typeData[0])) != 0) {
            item = mobj->typeData[0];
        } else {
            item = 0;
        }
        if (item) {
            pouchRemoveItem((ItemType)item);
            mobj->state++;
        } else {
            mobj->typeData[2] = msgWindow_Entry(msgSearch("sys_no_key"), 0, 0);
            mobj->state = 10;
        }
        break;
    case 3:
        ev = evtEntryType(evt_lock_sound, 0, 0, 0);
        ev->lwData[0] = (s32)(1024.0f * mobj->position.x) + 0xF24A7A80;
        ev->lwData[1] = (s32)(1024.0f * mobj->position.y) + 0xF24A7A80;
        ev->lwData[2] = (s32)(1024.0f * mobj->position.z) + 0xF24A7A80;
        animPoseSetAnim(mobj->poseId, "S_1", 1);
        mobj->state++;
        break;
    case 4:
        if (!(animPoseGetLoopTimes(mobj->poseId) < 1.0f)) {
            mobj->velocity.y = 0.0f;
            mobj->gravity = 0.5f;
            mobj->bounce = 0.0f;
            evtSetValue(NULL, mobj->flagVar, 1);
            mobjRunEvent(mobj, (s32*)mobj->extraEvent);
            mobj->state++;
        }
        break;
    case 5:
        dist = 1.0f + (f32)__fabs(mobj->velocity.y);
        if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, mobj->position.x, 1.0f + mobj->position.y, mobj->position.z, 0.0f, mobj->velocity.y, 0.0f)) {
            mobj->position.y = hy;
            mobj->velocity.y *= -0.8f;
            mobj->bounce += 1.0f;
            if (mobj->bounce < 4.0f) {
                psndSFXOn_3D((const char*)0x1e6, &mobj->position);
            }
        } else {
            mobj->position.y += mobj->velocity.y;
            mobj->velocity.y -= mobj->gravity;
        }
        if (!(mobj->bounce < 4.0f) && evtCheckID(mobj->eventId) != 1) {
            mobj->state++;
            mobj->unk1B0 = 20;
        }
        break;
    case 6:
        mobj->unk1B0--;
        if (mobj->unk1B0 & 2) {
            mobj->flags |= 0x4000;
        } else {
            mobj->flags &= ~0x4000;
        }
        if (mobj->unk1B0 == 0) {
            mobj->state = 99;
        }
        break;
    case 10:
        if (!windowCheckID(mobj->typeData[2])) {
            mobj->flags &= ~8;
            marioKeyOn();
            partyKeyOn();
            marioStSystemLevel(0);
            mobj->state = 0;
        }
        break;
    case 99:
        marioKeyOn();
        partyKeyOn();
        marioStSystemLevel(0);
        mobjDelete(mobj->name);
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_lock) {
    s32* args = event->args;
    const char* name;
    MapObjectEntry* mobj;
    s32 inBattle;
    const char* anim;
    s32 arg8;
    s32 val2;
    s32 val;
    s32 item;
    f32 rot;
    f32 x, y, z;
    name = (const char*)evtGetValue(event, ((0, args))[0]);
    item = evtGetValue(event, args[1]);
    x = evtGetFloat(event, args[2]);
    y = evtGetFloat(event, args[3]);
    z = evtGetFloat(event, args[4]);
    rot = evtGetFloat(event, args[5]);
    val = evtGetValue(event, args[6]);
    val2 = evtGetValue(event, args[7]);
    arg8 = args[8];
    inBattle = gp->inBattle != 0;
    anim = "MOBJ_Lock";
    if (evtGetValue(event, arg8)) {
        return EVT_RETURN_DONE;
    }
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjHitEntry(mobj, 2);
    mobj->typeData[0] = item;
    mobjSetPosition(name, x, y, z);
    mobj->rotation.y = rot;
    mobj->mainFunc = mobj_lock;
    mobj->event = val;
    mobj->extraEvent = val2;
    mobj->flags |= 0x26;
    mobj->flags |= 0x40000;
    mobj->flagVar = arg8;
    mobj->state = 0;
    mobjCalcMtx(mobj);
    animPoseSetAnim(mobj->poseId, "Z_1", 1);
    return EVT_RETURN_DONE;
}
#endif

EVT_BEGIN(evt_box_sound1)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3F2C), LW(0), LW(1), LW(2), 0)
    WAIT_MS(200)
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3F4C), LW(0), LW(1), LW(2), 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_box_sound2)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3F68), LW(0), LW(1), LW(2), 0)
    WAIT_MS(200)
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3F88), LW(0), LW(1), LW(2), 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_box_sound3)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3FA4), LW(0), LW(1), LW(2), LW(15))
    WAIT_MS(200)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3FC0), LW(0), LW(1), LW(2), 0)
    RETURN
EVT_END()

#ifdef NONMATCHING /* not in the target object (dead code stripped at link) */
static inline void mobj_itemb(MapObjectEntry* mobj) { \
    void* data = animPoseGetAnimBaseDataPtr(mobj->poseId); \
    Vec a, b; \
    a = (Vec){FLD(f32, data, 0xd0), FLD(f32, data, 0xd4), FLD(f32, data, 0xd8)}; \
    b = (Vec){FLD(f32, data, 0xdc), FLD(f32, data, 0xe0), FLD(f32, data, 0xe4)}; \
    a.z = a.z - 0.2f * __fabs(b.y - a.y); \
    PSVECAdd(&b, &a, &mobj->translation); \
    PSVECScale(&mobj->translation, &mobj->translation, 0.5f); \
    PSVECScale(&mobj->translation, &mobj->translation, 10.0f); \
    mobj->translation.y = 0.0f; \
    mobj->scale2.y *= 1.4f; \
    mobj->scale2.z *= 1.2f; \
    mobjCalcMtx2(mobj); \
}
#endif
s32 mobj_itembox(MapObjectEntry* mobj);

#ifdef NONMATCHING
s32 mobj_itembox(MapObjectEntry* mobj) {
    EventEntry* ev;
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            marioKeyOff();
            partyKeyOff();
            marioStSystemLevel(1);
            mobj->eventId = 0;
            mobjRunEvent(mobj, (s32*)mobj->event);
            mobj->state++;
        }
        break;
    case 1:
        if (mobj->eventId) {
            if (evtCheckID(mobj->eventId) == 1) {
                break;
            }
            if (mobj->flags & 0x1000) {
                mobj->flags &= ~0x1000;
                mobj->flags &= ~8;
                marioKeyOn();
                partyKeyOn();
                marioStSystemLevel(0);
                mobj->eventId = 0;
                mobj->state = 0;
                break;
            }
        }
        mobj->state++;
        break;
    case 2:
        if (!strcmp(mobj->animName, "MOBJ_TreasureBox") || !strcmp(mobj->animName, "MOBJ_GrayTreasureBox")) {
            ev = evtEntryType(evt_box_sound1, 0, 0, 0);
            ev->lwData[0] = (s32)(1024.0f * mobj->position.x) + 0xF24A7A80;
            ev->lwData[1] = (s32)(1024.0f * mobj->position.y) + 0xF24A7A80;
            ev->lwData[2] = (s32)(1024.0f * mobj->position.z) + 0xF24A7A80;
        } else if (!strcmp(mobj->animName, "MOBJ_BlackTreasureBox")) {
            ev = evtEntryType(evt_box_sound3, 0, 0, 0);
            ev->lwData[0] = (s32)(1024.0f * mobj->position.x) + 0xF24A7A80;
            ev->lwData[1] = (s32)(1024.0f * mobj->position.y) + 0xF24A7A80;
            ev->lwData[2] = (s32)(1024.0f * mobj->position.z) + 0xF24A7A80;
        } else {
            ev = evtEntryType(evt_box_sound2, 0, 0, 0);
            ev->lwData[0] = (s32)(1024.0f * mobj->position.x) + 0xF24A7A80;
            ev->lwData[1] = (s32)(1024.0f * mobj->position.y) + 0xF24A7A80;
            ev->lwData[2] = (s32)(1024.0f * mobj->position.z) + 0xF24A7A80;
        }
        animPoseSetAnim(mobj->poseId, "A_1", 1);
        mobj->eventId = 0;
        mobjRunEvent(mobj, (s32*)mobj->extraEvent);
        mobj->state++;
        break;
    case 3:
        if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
            break;
        }
        {
            if (mobj->eventId && evtCheckID(mobj->eventId) == 1) {
                break;
            }
            mobj->flags &= ~0x20;
            {
                mobj_itemb(mobj);
            }
            marioKeyOn();
            partyKeyOn();
            marioStSystemLevel(0);
            mobj->eventId = 0;
            mobj->state = 99;
        }
        break;
    case 99:
        evtSetValue(NULL, mobj->flagVar, 1);
        mobj->flags |= 8;
        mobj->flags &= ~0x20;
        if (!strcmp(mobj->animName, "MOBJ_BlackTreasureBox")) {
            animPoseSetAnim(mobj->poseId, "S_4", 1);
        } else {
            animPoseSetAnim(mobj->poseId, "S_2", 1);
        }
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_itembox) {
    s32 arg7;
    s32* args = event->args;
    const char* name;
    MapObjectEntry* mobj;
    s32 val, val2, kind, inBattle;
    const char* anim;
    f32 x, y, z;
    f32 hx, hy, hz, dist, nx, ny, nz;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    kind = evtGetValue(event, args[4]);
    val = evtGetValue(event, args[5]);
    val2 = evtGetValue(event, args[6]);
    arg7 = args[7];
    inBattle = gp->inBattle != 0;
    switch (kind) {
    case 0:
        anim = "MOBJ_TreasureBox";
        break;
    case 1:
        anim = "MOBJ_BigTreasureBox";
        break;
    case 2:
        anim = "MOBJ_GrayTreasureBox";
        break;
    case 3:
        anim = "MOBJ_BlackTreasureBox";
        break;
    case 4:
    default:
        anim = "MOBJ_GoldenTreasureBox";
        break;
    }
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjHitEntry(mobj, 2);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_itembox;
    mobj->event = val;
    mobj->extraEvent = val2;
    mobj->flags |= 0x64;
    mobj->flags |= 0x40000;
    mobj->flagVar = arg7;
    mobj->state = 0;
    mobjCalcMtx(mobj);
    if (evtGetValue(event, arg7)) {
        mobj_itemb(mobj);
        mobj->state = 99;
    }
    dist = 5.0f + (f32)__fabs(mobj->velocity.y);
    if (hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, mobj->position.x, 1.0f + mobj->position.y, mobj->position.z, 0.0f, -1.0f, 0.0f)) {
        mobj->flags |= 2;
        mobj->flags &= ~0x40;
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_signboard(MapObjectEntry* mobj) {
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            marioKeyOff();
            mobjRunEvent(mobj, (s32*)mobj->event);
            mobj->state++;
        }
        break;
    case 1:
        if (evtCheckID(mobj->eventId) != 1) {
            marioKeyOn();
            mobj->eventId = 0;
            mobj->flags &= ~8;
            mobj->state = 0;
        }
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_signboard) {
    s32 val;
    s32* args = event->args;
    const char* name;
    s32 arg5;
    MapObjectEntry* mobj;
    const char* anim;
    s32 inBattle;
    f32 x, y, z;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    val = evtGetValue(event, args[4]);
    inBattle = gp->inBattle;
    inBattle = inBattle != 0;
    arg5 = args[5];
    anim = "MOBJ_Signboard";
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_signboard;
    mobj->event = val;
    mobj->flags |= 0x24;
    mobj->flags |= 0x40000;
    mobj->flagVar = arg5;
    mobj->state = 0;
    return EVT_RETURN_DONE;
}
#endif









#ifdef NONMATCHING /* not in the target object (dead code stripped at link) */
void mobj_sign(void) {
    mobjNameToPtr("MOBJ_Arrow");
}
#endif

extern EffectEntry* effCoinFukidashiEntry(f32 x, f32 y, f32 z, s32 type, s32 number, s32 duration);
extern EffectEntry* effStardustEntry(s32 type, s32 arg1, s32 arg2, f32 x, f32 y, f32 z, f32 arg6, f32 arg7);
extern void effSoftDelete(EffectEntry* effect);
extern BOOL swGet(s32 index);
extern void swSet(s32 index);
extern s32 pouchGetCoin(void);
extern PouchData* pouchGetPtr(void);
extern void statusWinForceOpen(void);
extern void statusWinForceOff(void);
extern const char* msgSearch(const char* tag);
extern s32 msgWindow_Entry(const char* msg, s32 a, s32 b);
extern s32 windowCheckID(s32 id);

#ifdef NONMATCHING
s32 mobj_recovery_blk(MapObjectEntry* mobj) {
    MarioWork* mario;
    PouchData* pouch;
    PouchPartyData* party;
    s32 i;
    s32 kind;
    switch (mobj->state) {
    case -1:
        mobj->effect = effCoinFukidashiEntry(mobj->position.x, 25.0f + mobj->position.y, mobj->position.z - 10.0f, 0, mobj->typeData[1], 0);
        mobj->state++;
        break;
    case 0:
        if (!(mobj->flags & 8)) {
            break;
        }
        marioKeyOff();
        FLD(u16, camGetPtr((CameraId)8), 0) |= 0x200;
        psndSFXOn_3D((const char*)0x1d9, &mobj->position);
        mobj->state++;
    case 1:
        if (!(FLD(u32, gp, 0) & 0x1000) && swGet(0xea) == 0) {
            swSet(0xea);
            mobj->state = 20;
            break;
        }
        mobj->state++;
    case 2:
        kind = pouchGetCoin(); // kind reused for the coin count (matches the target codegen)
        if (kind < mobj->typeData[1]) {
            mobj->state = 10;
            break;
        }
        if (mobj->effect) {
            effSoftDelete(mobj->effect);
            mobj->effect = NULL;
        }
        psndSFXOn_3D((const char*)0x1da, &mobj->position);
        animPoseSetAnim(mobj->poseId, "A_1", 1);
        if (mobj->typeData[1] == 0) {
            mobj->state = 3;
        } else {
            mobj->state = 4;
            statusWinForceOpen();
        }
        mobj->unk1B0 = 120;
        break;
    case 3:
        if (mobj->unk1B0 == 100) {
            effStardustEntry(1, 30, 60, mobj->position.x, 45.0f + mobj->position.y, mobj->position.z, 50.0f, 50.0f);
            psndSFXOn_3D((const char*)0x1db, &mobj->position);
        }
        if (mobj->unk1B0 == 100) {
            mario = marioGetPtr();
            party = (PouchPartyData*)pouchGetPtr();
            effStardustEntry(2, 50, 100, mario->position.x, mario->position.y, mario->position.z, 50.0f, 50.0f);
            marioChgPose("M_I_1");
            ((PouchData*)party)->currentHP = ((PouchData*)party)->maximumHP;
            ((PouchData*)party)->currentFP = ((PouchData*)party)->maximumFP;
            for (i = 0; i < 8; party++, i++) {
                if ((party->flags & 1) && !(party->flags & 2)) {
                    party->currentHP = party->maximumHP;
                }
            }
            pouchAddCoin(0);
        }
        mobj->unk1B0--;
        if (mobj->unk1B0 <= 0) {
            mobj->state = 5;
        }
        break;
    case 4:
        if (mobj->unk1B0 == 100) {
            effStardustEntry(1, 30, 60, mobj->position.x, 45.0f + mobj->position.y, mobj->position.z, 50.0f, 50.0f);
            psndSFXOn_3D((const char*)0x1db, &mobj->position);
        }
        if (mobj->unk1B0 == 100) {
            kind = mobj->typeData[1];
            mario = marioGetPtr();
            party = (PouchPartyData*)pouchGetPtr();
            effStardustEntry(2, 50, 100, mario->position.x, mario->position.y, mario->position.z, 50.0f, 50.0f);
            marioChgPose("M_I_1");
            ((PouchData*)party)->currentHP = ((PouchData*)party)->maximumHP;
            ((PouchData*)party)->currentFP = ((PouchData*)party)->maximumFP;
            for (i = 0; i < 8; party++, i++) {
                if ((party->flags & 1) && !(party->flags & 2)) {
                    party->currentHP = party->maximumHP;
                }
            }
            ((s32 (*)(s32))pouchAddCoin)(-kind);
        }
        mobj->unk1B0--;
        if (mobj->unk1B0 <= 0) {
            mobj->state = 5;
        }
        break;
    case 5:
        if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
            break;
        }
        animPoseSetAnim(mobj->poseId, "S_1", 1);
        marioChgPose("M_S_1");
        marioKeyOn();
        statusWinForceOff();
        FLD(u16, camGetPtr((CameraId)8), 0) &= ~0x200;
        mobj->state++;
        break;
    case 6:
        if (mobj->effect == NULL) {
            mobj->effect = effCoinFukidashiEntry(mobj->position.x, 25.0f + mobj->position.y, mobj->position.z - 10.0f, 0, mobj->typeData[1], 0);
        }
        if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
            break;
        }
        animPoseSetAnim(mobj->poseId, "A_2", 1);
        mobj->flags &= ~8;
        mobj->state = 0;
        break;
    case 10:
        mobj->typeData[2] = msgWindow_Entry(msgSearch("sys_no_coin"), 0, 0);
        mobj->state++;
        break;
    case 11:
        if (windowCheckID(mobj->typeData[2]) == 0) {
            marioKeyOn();
            FLD(u16, camGetPtr((CameraId)8), 0) &= ~0x200;
            mobj->flags &= ~8;
            mobj->state = 0;
        }
        break;
    case 20:
        mobj->typeData[2] = msgWindow_Entry(msgSearch("kaifuku_first_hit"), 0, 0);
        mobj->state++;
        break;
    case 21:
        if (windowCheckID(mobj->typeData[2]) == 0) {
            marioKeyOn();
            FLD(u16, camGetPtr((CameraId)8), 0) &= ~0x200;
            mobj->flags &= ~8;
            mobj->state = 0;
        }
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_recovery_blk) {
    BOOL inBattle;
    s32 arg6;
    s32* args = event->args;
    const char* anim;
    s32 kind;
    const char* name;
    MapObjectEntry* mobj;
    f32 x, y, z;
    name = (const char*)evtGetValue(event, args[0]);
    kind = evtGetValue(event, args[1]);
    x = evtGetFloat(event, args[2]);
    y = evtGetFloat(event, args[3]);
    z = evtGetFloat(event, args[4]);
    evtGetValue(event, args[5]);
    arg6 = args[6];
    inBattle = gp->inBattle != 0;
    anim = kind == 0 ? "MOBJ_RecoveryBlock" : "MOBJ_CoinTakenRecoveryBlock";
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobj->typeData[1] = kind;
    mobjSetPosition(name, x, y, z);
    mobj->flags |= 4;
    mobj->mainFunc = mobj_recovery_blk;
    mobj->event = 0;
    mobj->extraEvent = 0;
    mobj->flags |= 4;
    mobj->flags |= 0x400000;
    mobj->flagVar = arg6;
    if (kind == 0) {
        mobj->state = 0;
    } else {
        mobj->state = -1;
    }
    mobjCalcMtx(mobj);
    animPoseSetAnim(mobj->poseId, "S_1", 1);
    return EVT_RETURN_DONE;
}
#endif

EVT_BEGIN(mobj_save_blk_sysevt)
    SET_TYPE(0)
    CALL(evt_mario_key_onoff, 0)
    SET_VALUE(LF(10), 0)
    IF_INT_EQUAL(GSWF(233), 0)
        SET_VALUE(GSWF(233), 1)
        CALL(evt_msg_print, 0, STRING((char*)str_802C3FF0), 0, 0)
        SET_VALUE(LF(10), 1)
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(0), 7)
        SET_VALUE(GSWF(236), 1)
    END_IF
    SET_VALUE(LW(0), 0)
    CALL_CHILD(PTR(evt_memcard_save))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

#ifdef NONMATCHING
s32 mobj_save_blk(MapObjectEntry* mobj) {
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            marioKeyOff();
            marioStSystemLevel(1);
            psndSFXOn_3D((const char*)0x1af, &mobj->position);
            animPoseSetAnim(mobj->poseId, "A_1", 1);
            FLD(u16, camGetPtr((CameraId)8), 0) |= 0x200;
            mobj->state++;
        }
        break;
    case 1:
        if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
            break;
        }
        animPoseSetAnim(mobj->poseId, "S_1", 1);
        if ((void*)mobj->event) {
            mobjRunEvent(mobj, (s32*)mobj->event);
            mobj->state++;
        } else {
            mobj->state = 3;
        }
        break;
    case 2:
        if (evtCheckID(mobj->eventId) != 1) {
            mobj->eventId = 0;
            mobj->state++;
        }
        break;
    case 3:
        mobjRunEvent(mobj, (s32*)mobj->extraEvent);
        mobj->state++;
        break;
    case 4:
        if (evtCheckID(mobj->eventId) != 1) {
            marioStSystemLevel(0);
            FLD(u16, camGetPtr((CameraId)8), 0) &= ~0x200;
            mobj->flags &= ~8;
            marioKeyOn();
            mobj->state = 0;
        }
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_save_blk) {
    s32 arg5;
    s32 val;
    s32* args = event->args;
    const char* name;
    const char* anim;
    MapObjectEntry* mobj;
    s32 inBattle;
    f32 x, y, z;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    val = evtGetValue(event, args[4]);
    arg5 = args[5];
    anim = "MOBJ_SaveBlock";
    inBattle = gp->inBattle != 0;
    if (FLD(u32, gp, 0) & 0x20) {
        return EVT_RETURN_DONE;
    }
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_save_blk;
    mobj->event = val;
    mobj->extraEvent = (s32)mobj_save_blk_sysevt;
    mobj->flags |= 0x84;
    mobj->flags |= 0x400000;
    mobj->flagVar = arg5;
    mobj->state = 0;
    mobjCalcMtx(mobj);
    animPoseSetAnim(mobj->poseId, "S_1", 1);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_badgeblk(MapObjectEntry* mobj) {
    void* item;
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            if (!strcmp(mobj->animName, "MOBJ_BadgeBlock") || !strcmp(mobj->animName, "MOBJ_BrickBadgeBlock") ||
                !strcmp(mobj->animName, "MOBJ_HiddenBadgeBlock")) {
                psndSFXOn_3D((const char*)0x1bb, &mobj->position);
            } else {
                psndSFXOn_3D((const char*)0x1ba, &mobj->position);
            }
            if (mobj->flags & 0x800) {
                mobj->flags &= ~0x800;
            }
            animPoseSetAnim(mobj->poseId, "A_1", 1);
            if (FLD(u32, mobj, 0x1d4) != 0) {
                mobjRunEvent(mobj, (s32*)mobj->event);
            } else if (mobj->typeData[0] != 0x79) {
                itemEntry(mobj->position.x, 40.0f + mobj->position.y, mobj->position.z, mobj->name, mobj->typeData[0], 4, mobj->flagVar, NULL);
                item = itemNameToPtr(mobj->name);
                itemFlagOn(item, 0x10);
                FLD(f32, item, 0x80) = 0.7f;
                FLD(f32, item, 0x84) = 1.0f;
                FLD(s32, item, 0x88) = 0;
                FLD(f32, item, 0x58) = 360.0f;
                psndSFXOn_3D((const char*)0x1bc, &mobj->position);
            } else {
                pouchAddCoin(1);
                itemEntry(mobj->position.x, mobj->position.y, mobj->position.z, NULL, 0x79, 0xf, -1, NULL);
                evtSetValue(NULL, mobj->flagVar, 1);
                psndSFXOn_3D((const char*)0x5b, &mobj->position);
            }
            mobj->state++;
        }
        break;
    case 1:
        if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
            break;
        }
        animPoseSetAnim(mobj->poseId, "S_2", 1);
        mobj->flags &= ~8;
        mobj->state = 90;
        if (!strcmp(mobj->animName, "MOBJ_HatenaBlock") || !strcmp(mobj->animName, "MOBJ_BrickHatenaBlock") ||
            !strcmp(mobj->animName, "MOBJ_HiddenHatenaBlock")) {
            strcpy(mobj->animName, "MOBJ_Block");
        } else {
            strcpy(mobj->animName, "MOBJ_PinkBlock");
        }
        break;
    case 90:
        if (mobj->flags & 8) {
            mobj->flags &= ~8;
            animPoseSetAnim(mobj->poseId, "A_2", 1);
            psndSFXOn_3D((const char*)0x1b7, &mobj->position);
            mobj->state++;
        }
        break;
    case 91:
        if (!(mobj->flags & 8)) {
            mobj->state = 90;
            break;
        }
        if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
            break;
        }
        animPoseSetAnim(mobj->poseId, "S_2", 1);
        mobj->state = 90;
        mobj->flags &= ~8;
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_badgeblk) {
    s32* args = event->args;
    const char* anim;
    f32 x, y, z;
    const char* name;
    s32 val;
    s32 item;
    s32 arg6;
    s32 kind;
    MapObjectEntry* mobj;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    item = evtGetValue(event, args[4]);
    val = evtGetValue(event, args[5]);
    kind = args[7];
    arg6 = args[6];
    {
        BOOL b = gp->inBattle != 0;
        anim = kind != 0 ? "MOBJ_BadgeBlock" : "MOBJ_HatenaBlock";
        if (animGroupBaseAsync(anim, b, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }}
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_badgeblk;
    mobj->event = val;
    mobj->flags |= 4;
    mobj->flags |= 0xc10000;
    mobj->flagVar = arg6;
    mobj->state = 0;
    mobj->typeData[0] = item;
    mobjCalcMtx(mobj);
    animPoseSetAnim(mobj->poseId, "S_1", 1);
    if (evtGetValue(event, arg6)) {
        mobj->state = 90;
        animPoseSetAnim(mobj->poseId, "S_2", 1);
        strcpy(mobj->animName, kind != 0 ? "MOBJ_PinkBlock" : "MOBJ_Block");
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_powerupblk(MapObjectEntry* mobj) {
    switch (mobj->state) {
    case 0:
        if (!(mobj->flags & 8)) {
            break;
        }
        if (marioKeyOffChk() || marioCtrlOffChk()) {
            mobj->flags &= ~8;
            break;
        }
        marioKeyOff();
        if (!strcmp((char*)gp + 0x12c, "dou_02")) {
            marioCtrlOff();
        } else if ((!strcmp((char*)gp + 0x12c, "dou_05") || !strcmp((char*)gp + 0x12c, "dou_10")) && mobj->hitFlag == 0x800000) {
            marioCtrlOff();
        }
        FLD(s32, gp, 0x18) |= 3;
        psndSFXOn_3D((const char*)0x201c0, &mobj->position);
        animPoseSetAnim(mobj->poseId, "A_1", 1);
        itemEntry(mobj->position.x, mobj->position.y, mobj->position.z, "pwrblk1", 0x57, 0xf, -1, NULL);
        mobj->state++;
        break;
    case 1:
        if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
            break;
        }
        animPoseSetAnim(mobj->poseId, "A_2", 1);
        mobj->flags &= ~8;
        mobj->typeData[1] = 1;
        mobj->state++;
        break;
    case 2:
        if (mobj->typeData[1]) {
            mobj->typeData[1]--;
            break;
        }
        itemForceGet(itemEntry(mobj->position.x, 40.0f + mobj->position.y, mobj->position.z, "pwrblk2", 0x57, 0x11, -1, NULL));
        evtSetValue(NULL, mobj->flagVar, 1);
        marioKeyOn();
        if (!strcmp((char*)gp + 0x12c, "dou_02")) {
            marioCtrlOn();
        } else if ((!strcmp((char*)gp + 0x12c, "dou_05") || !strcmp((char*)gp + 0x12c, "dou_10")) && mobj->hitFlag == 0x800000) {
            marioCtrlOn();
        }
        mobj->state = 90;
        break;
    case 90:
        mobjDelete(mobj->name);
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_powerupblk) {
    MapObjectEntry* mobj;
    const char* name;
    const char* anim;
    f32 rot;
    f32 x, y, z;
    s32 arg5;
    s32 val;
    s32* args = event->args;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    val = evtGetValue(event, args[4]);
    arg5 = args[5];
    rot = evtGetFloat(event, args[6]);
    anim = "MOBJ_PowerUpBlock";
    if (animGroupBaseAsync(anim, gp->inBattle != 0, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_powerupblk;
    mobj->event = val;
    mobj->flags |= 4;
    mobj->flags |= 0xc10000;
    mobj->flagVar = arg5;
    mobj->state = 0;
    mobj->rotation.y = rot;
    mobjCalcMtx(mobj);
    animPoseSetAnim(mobj->poseId, "S_1", 1);
    if (evtGetValue(event, arg5)) {
        mobj->state = 90;
        animPoseSetAnim(mobj->poseId, "A_2", 1);
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_brickblk(MapObjectEntry* mobj) {
    char oname[16] = "o_";
    char iname[16] = "i_";
    EventEntry ev1;
    EventEntry ev2;
    s32 args1[10];
    s32 args2[10];
    ImageEntry* img;
    s32 type = gp->inBattle != 0;
    strcat(oname, mobj->name);
    strcat(iname, mobj->name);
    switch (mobj->state) {
    case 0:
        animGroupBaseAsync("P_box_y", type, NULL);
        if (mobj->flags & 8) {
            mobjRunEvent(mobj, (s32*)mobj->event);
            evtSetValue(NULL, mobj->flagVar, 1);
            mobj->state = 10;
        }
        break;
    case 10:
        animPaperPoseEntry("P_box_y", type);
        offscreenEntry(oname);
        imgEntry(iname, type);
        mobj->offscreenId = offscreenNameToId(oname);
        ev1.args = args1;
        args1[0] = (s32)iname; args1[1] = 0; args1[2] = (s32)oname; args1[3] = 1;
        args1[4] = 0; args1[5] = 0; args1[6] = 0; args1[7] = 0;
        evt_img_alloc_capture(&ev1, TRUE);
        ev2.args = args2;
        args2[0] = (s32)iname; args2[1] = 1; args2[2] = (s32)oname; args2[3] = 1;
        args2[4] = 0; args2[5] = 0; args2[6] = 0; args2[7] = 0;
        evt_img_alloc_capture(&ev2, TRUE);
        img = imgNameToPtr(iname, type);
        img->poseId = animPaperPoseGetId("P_box_y", type);
        img->animName = (s32)"A_1";
        FLD(OSTime, img, 0x110) = animTimeGetTime(type);
        imgSetShadow(img, 2);
        psndSFXOn_3D((const char*)0x1b8, &mobj->position);
        mobj->state = 11;
        break;
    case 11:
        img = imgNameToPtr(iname, type);
        if (img->loopTimes >= 1.0f) {
            mobj->state = 12;
        }
        if (img->flags & 0x10000000) {
            mobj->state = 12;
        }
        mobj->position = (Vec){0.0f, -2000.0f, 0.0f};
        mobj->flags |= 4;
        mobj->flags |= 8;
        break;
    case 12:
        img = imgNameToPtr(iname, type);
        imgFreeCapture(img, 0);
        imgFreeCapture(img, 1);
        imgSetShadow(img, 0);
        imgRelease(img, type);
        offscreenDelete(oname);
        mobj->offscreenId = -1;
        mobj->state = 99;
        break;
    case 99:
        mobjDelete(mobj->name);
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
s32 mobj_10countblk(MapObjectEntry* mobj) {
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            if (mobj->flags & 0x800) {
                mobj->flags &= ~0x800;
                strcpy(mobj->animName, "MOBJ_Block");
            }
            animPoseSetAnim(mobj->poseId, "A_1", 1);
            psndSFXOn_3D((const char*)0x1be, &mobj->position);
            evtSetValue(NULL, mobj->flagVar, 1);
            if (FLD(u32, mobj, 0x1d4) != 0) {
                mobjRunEvent(mobj, (s32*)mobj->event);
            } else {
                pouchAddCoin(1);
                itemEntry(mobj->position.x, mobj->position.y, mobj->position.z, NULL, 0x79, 0xf, -1, NULL);
                mobj->unk1B0 = 200;
            }
            mobj->state++;
            mobj->flags &= ~8;
        }
        break;
    case 1:
        if (mobj->unk1B0 > 0) {
            mobj->unk1B0--;
        }
        if (mobj->unk1B0 <= 0) {
            mobj->state = 90;
            animPoseSetAnim(mobj->poseId, "S_2", 1);
            strcpy(mobj->animName, "MOBJ_Block");
            break;
        }
        if (mobj->flags & 8) {
            psndSFXOn_3D((const char*)0x1bf, &mobj->position);
            pouchAddCoin(1);
            itemEntry(mobj->position.x, mobj->position.y, mobj->position.z, NULL, 0x79, 0xf, -1, NULL);
            mobj->flags &= ~8;
            animPoseSetAnim(mobj->poseId, "A_1", 1);
        }
        break;
    case 90:
        if (mobj->flags & 8) {
            psndSFXOn_3D((const char*)0x1b7, &mobj->position);
            animPoseSetAnim(mobj->poseId, "A_3", 1);
            mobj->flags &= ~8;
            mobj->state++;
        }
        break;
    case 91:
        if (!(mobj->flags & 8)) {
            mobj->state = 90;
            break;
        }
        if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
            break;
        }
        animPoseSetAnim(mobj->poseId, "S_2", 1);
        mobj->state = 90;
        mobj->flags &= ~8;
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_brick) {
    f32 x, y, z;
    s32* args = event->args;
    const char* name;
    s32 item;
    s32 inBattle;
    s32 val;
    s32 kind;
    s32 arg7;
    MapObjectEntry* mobj;
    const char* anim;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    item = evtGetValue(event, args[4]);
    kind = args[5];
    val = evtGetValue(event, args[6]);
    arg7 = args[7];
    inBattle = gp->inBattle != 0;
    switch (kind) {
    case 0:
        anim = "MOBJ_FlowBrickBlock";
        break;
    case 1:
        anim = "MOBJ_BrickHatenaBlock";
        break;
    case 2:
        anim = "MOBJ_BrickBadgeBlock";
        break;
    case 3:
        anim = "MOBJ_10CountBlock";
        break;
    case 10:
        anim = "MOBJ_HiddenHatenaBlock";
        break;
    case 11:
        anim = "MOBJ_HiddenHatenaBlock";
        break;
    case 12:
        anim = "MOBJ_HiddenBadgeBlock";
        break;
    case 13:
        anim = "MOBJ_Hidden10CountBlock";
        break;
    }
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    if (animGroupBaseAsync("P_box_y", inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    if ((s32)kind >= 10) {
        mobj->flags |= 0x800;
    }
    switch (kind) {
    case 0:
    case 10:
        mobj->mainFunc = mobj_brickblk;
        break;
    case 1:
    case 11:
        mobj->mainFunc = mobj_badgeblk;
        break;
    case 2:
    case 12:
        mobj->mainFunc = mobj_badgeblk;
        break;
    case 3:
    case 13:
        mobj->mainFunc = mobj_10countblk;
        break;
    }
    mobj->event = val;
    mobj->flags |= 4;
    mobj->flags |= 0xc10000;
    mobj->flagVar = arg7;
    mobj->state = 0;
    mobj->typeData[0] = item;
    mobjCalcMtx(mobj);
    if ((s32)kind < 10) {
        animPoseSetAnim(mobj->poseId, "S_1", 1);
    } else if (kind == 13) {
        animPoseSetAnim(mobj->poseId, "S_3", 1);
    } else {
        animPoseSetAnim(mobj->poseId, "S_1", 1);
    }
    if (evtGetValue(event, arg7)) {
        const char* anim2 = NULL;
        switch (kind) {
        case 0:
        case 10:
            animPoseSetAnim(mobj->poseId, "S_1", 1);
            mobj->state = 99;
            break;
        case 1:
        case 11:
            animPoseSetAnim(mobj->poseId, "S_2", 1);
            anim2 = "MOBJ_Block";
            mobj->state = 90;
            break;
        case 2:
        case 12:
            animPoseSetAnim(mobj->poseId, "S_2", 1);
            anim2 = "MOBJ_PinkBlock";
            mobj->state = 90;
            break;
        case 3:
        case 13:
            animPoseSetAnim(mobj->poseId, "S_2", 1);
            anim2 = "MOBJ_Block";
            mobj->state = 90;
            break;
        }
        if (anim2) {
            strcpy(mobj->animName, anim2);
        }
        mobj->flags &= ~0x800;
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_breaking_floor(MapObjectEntry* mobj) {
    void* mario = marioGetPtr();
    GXColor c3;
    GXColor c2;
    GXColor c1 = {0xff, 0xff, 0xff, 0xff};
    c2 = c1;
    c3 = c1;
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            psndSFXOn_3D((const char*)0x401e8, &mobj->position);
            animPoseSetAnim(mobj->poseId, "A_1", 1);
            if ((u32)mobj->event != 0U) {
                mobjRunEvent(mobj, (s32*)mobj->event);
            }
            if (mobj->hitObj[0].hitObject) {
                FLD(u16, mobj->hitObj[0].hitObject, 0) |= 1;
            }
            mobj->flags |= 2;
            evtSetValue(NULL, mobj->flagVar, 1);
            mobj->state = 1;
            animPoseSetMaterialFlagOn(mobj->poseId, 0x40);
            animPoseSetMaterialEvtColor(mobj->poseId, c2);
            mobj->unk1B0 = 64;
        }
        break;
    case 1:
        c3 = animPoseGetMaterialEvtColor(mobj->poseId);
        if (((0, c3)).a >= 4) {
            c3.a -= 4;
        } else {
            c3.a = 0;
            mobj->state = 99;
        }
        animPoseSetMaterialEvtColor(mobj->poseId, c3);
        mobj->unk1B0--;
        if (mobj->unk1B0 <= 0) {
            mobj->state = 99;
        }
        break;
    case 99:
        mobjDelete(mobj->name);
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_breaking_floor) {
    char anim[128];
    s32 arg6;
    s32 val;
    s32* args = event->args;
    s32 kind;
    const char* name;
    s32 inBattle;
    f32 x, y, z;
    MapObjectEntry* mobj;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    kind = evtGetValue(event, args[4]);
    val = evtGetValue(event, args[5]);
    arg6 = args[6];
    inBattle = gp->inBattle != 0;
    switch (kind) {
    case 0:
        strcpy(anim, "MOBJ_BreakingFloor");
        break;
    case 1:
        strcpy(anim, "MOBJ_BlackBreakingFloor");
        break;
    default:
        strcpy(anim, "MOBJ_BreakingFloor");
        break;
    }
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_breaking_floor;
    mobj->event = val;
    mobj->flags |= 4;
    mobj->flags |= 0x1000000;
    mobj->flagVar = arg6;
    if (evtGetValue(event, arg6)) {
        mobj->state = 99;
    } else {
        mobj->state = 0;
    }
    mobjCalcMtx(mobj);
    animPoseSetAnim(mobj->poseId, "S_1", 1);
    return EVT_RETURN_DONE;
}
#endif

// ---- kpa ----

typedef struct KpaPoleScoreWork {
    char str[8];
    f32 x;
    f32 y;
    f32 z;
} KpaPoleScoreWork;

static u32 gap_08_80418714_sbss;
static KpaPoleScoreWork* psw;

#ifdef NONMATCHING
void kururing_capture(CameraId camId, MapObjectEntry* mobj) {
    u8 saved[0x260];
    CameraEntry* cam;
    AnimationPoseData* data;
    Vec min, max;
    s32 h, w;
    s32 ww, hh;
    smartEntry* e;
    f32 t;
    memcpy(saved, camGetPtr(camId), 0x260);
    data = animPoseGetAnimBaseDataPtr(mobj->poseId);
    min = (Vec){FLD(f32, data, 0xd0), FLD(f32, data, 0xd4), FLD(f32, data, 0xd8)};
    max = (Vec){FLD(f32, data, 0xdc), FLD(f32, data, 0xe0), FLD(f32, data, 0xe4)};
    ww = 10.0f * (max.x - min.x);
    hh = 10.0f * (max.z - min.z);
    cam = camGetPtr(camId);
    h = (u16)(ww + 1) & ~1;
    w = (u16)(hh + 1) & ~1;
    cam->cameraUp = (Vec){0.0f, 0.0f, -1.0f};
    cam->cameraAt = mobj->position;
    cam->cameraPos = mobj->position;
    t = tan(0.21816615760326385);
    cam->cameraPos.y += (f32)(u32)w / 2.0f / t;
    C_MTXPerspective(cam->projection, 25.0f, (f32)(h / w), 1.0f, 32767.0f);
    cam->projType = GX_PERSPECTIVE;
    C_MTXLookAt(cam->view, &cam->cameraPos, &cam->cameraUp, &cam->cameraAt);
    GXSetProjection(cam->projection, cam->projType);
    GXSetViewport(0.0f, 0.0f, (u32)h, (u32)w, 0.0f, 1.0f);
    GXSetScissor(0, 0, h, w);
    test_kururing_mapdisp(camId);
    sysWaitDrawSync();
    hh = ((u32)h >> 1) & 0x7fff;
    ww = ((u32)w >> 1) & 0x7fff;
    FLD(smartEntry*, mobj, 0x208) = smartAlloc(GXGetTexBufferSize(hh, ww, 6, 0, 0), 3);
    GXSetTexCopySrc(0, 0, h, w);
    GXSetTexCopyDst(hh, ww, (GXTexFmt)6, 1);
    GXSetZMode(1, (GXCompare)3, 1);
    GXCopyTex(FLD(smartEntry*, mobj, 0x208)->address, 1);
    GXInvalidateTexAll();
    GXPixModeSync();
    GXTexModeSync();
    GXInitTexObj(&mobj->paperTexObj, FLD(smartEntry*, mobj, 0x208)->address, hh, ww, (GXTexFmt)6, (GXTexWrapMode)0, (GXTexWrapMode)0, 0);
    GXInitTexObjLOD(&mobj->paperTexObj, (GXTexFilter)0, (GXTexFilter)0, 0.0f, 0.0f, 0.0f, 0, 0, (GXAnisotropy)0);
    PSMTXIdentity(mobj->paperTexMtx);
    memcpy(camGetPtr(camId), saved, 0x260);
}
#endif


extern s32 pouchGetJumpLv(void);
extern void* itemHitCheck(f32 x, f32 y, f32 z, f32 r);
extern void* npcNearDistCheck(f32 x, f32 y, f32 z, f32 r);
extern void* itemNearDistCheck(f32 x, f32 y, f32 z, f32 r);
extern s32 psndSFXOnEx_3D(const char* name, Vec* pos, s32 a, s32 b, s32 c, s32 d);
extern s32 marioGetExtraPartyId(void);

static inline BOOL kururing_in_box(f32 x, f32 z, f32 px, f32 pz, f32 r) {
    if (x - r <= px && px <= x + r && z - r <= pz && pz <= z + r) {
        return TRUE;
    }
    return FALSE;
}

#define KURU_POSE_FLAGS(m) FLD(s32, FLD(u8*, animGetPtr(), 0x10), (m)->poseId * 0x170)

#ifdef NONMATCHING
s32 mobj_kururing_floor(MapObjectEntry* mobj) {
    PartyEntry* party;
    MarioWork* mario = marioGetPtr();
    s32 mode;
    f32 dist;
    void* item;
    void* p;
    void* cur2;
    party = partyGetPtr(marioGetPartyId());
    switch (mobj->state) {
    case 0:
        if (!(mobj->flags & 8)) {
            break;
        }
        dist = distABf(mario->position.x, mario->position.z, mobj->position.x, mobj->position.z);
        if (__fabsf(mario->position.y - mobj->position.y) > 10.0f) {
            dist = 100000.0f;
        }
        if (mobj->hitFlag == 0x1000000) {
            if (pouchGetJumpLv() < 2) {
                mode = 0;
            } else if (dist < 60.0f) {
                mode = 2;
            } else if (dist < 100.0f) {
                mode = 1;
            } else {
                mode = 0;
            }
        }
        if (mobj->hitFlag == 0x10000) {
            mode = 1;
        }
        if (mode == 0) {
            mobj->flags &= ~8;
            break;
        }
        if (kururing_in_box(mobj->position.x, mobj->position.z, mario->position.x, mario->position.z, 30.0f)) {
            mode = 1;
        }
        if (party) {
            if (kururing_in_box(mobj->position.x, mobj->position.z, party->position.x, party->position.z, 30.0f)) {
                mode = 1;
            }
        }
        if (itemHitCheck(mobj->position.x, mobj->position.y, mobj->position.z, 42.420002f)) {
            mode = 1;
        }
        if (npcNearDistCheck(mobj->position.x, mobj->position.y, mobj->position.z, 42.420002f)) {
            mode = 1;
        }
        if (mode == 0) {
            mobj->flags &= ~8;
            break;
        }
        if (mode == 1) {
            animPoseSetAnim(mobj->poseId, "A_1", 1);
            psndSFXOnEx_3D((const char*)0x1ee, &mobj->position, 0xff, 0xff, 100, 0x10);
            mobj->state = 10;
        } else if (mode == 2) {
            animPoseSetAnim(mobj->poseId, "A_2", 1);
            psndSFXOn_3D((const char*)0x1ef, &mobj->position);
            mobj->state = 1;
            item = itemNameToPtr(mobj->name);
            if (item == NULL || !(FLD(u16, item, 0) & 1)) {
                if (itemEntry(mobj->position.x, 30.0f + mobj->position.y, mobj->position.z, mobj->name, 0x7d, 4, mobj->flagVar, NULL)) {
                    item = itemNameToPtr(mobj->name);
                    itemFlagOn(item, 0x10);
                    FLD(f32, item, 0x80) = 0.6f;
                    FLD(f32, item, 0x84) = 1.0f;
                    FLD(s32, item, 0x88) = 5;
                    FLD(f32, item, 0x58) = 300.0f;
                }
            }
        }
        KURU_POSE_FLAGS(mobj) |= 0x10;
        mobj->flags |= 0x400;
        dispEntry(CAMERA_SHADOW, 0.0f, 0, (DispCallback)kururing_capture, mobj);
        break;
    case 1:
        KURU_POSE_FLAGS(mobj) |= 0x10;
        mobj->flags |= 0x400;
        dispEntry(CAMERA_SHADOW, 0.0f, 0, (DispCallback)kururing_capture, mobj);
        if (!(animPoseGetLoopTimes(mobj->poseId) < 1.0f)) {
            KURU_POSE_FLAGS(mobj) &= ~0x10;
            mobj->flags &= ~0x400;
            mobj->flags &= ~8;
            animPoseSetAnim(mobj->poseId, "S_1", 1);
            psndSFXOn_3D((const char*)0x1f0, &mobj->position);
            mobj->state = 0;
        }
        break;
    case 10:
    {
        void* joint;
        KURU_POSE_FLAGS(mobj) |= 0x10;
        mobj->flags |= 0x400;
        dispEntry(CAMERA_SHADOW, 0.0f, 0, (DispCallback)kururing_capture, mobj);
        joint = *(void**)FLD(void*, animPoseGetAnimPosePtr(mobj->poseId), 0x15c);
        item = marioGetPtr();
        if (kururing_in_box(mobj->position.x, mobj->position.z, FLD(f32, item, 0x8c), FLD(f32, item, 0x94), 30.0f)) {
            FLD(f32, item, 0x90) = FLD(f32, joint, 0x10);
        }
        p = partyGetPtr(marioGetPartyId());
        if (p) {
            if (kururing_in_box(mobj->position.x, mobj->position.z, FLD(f32, p, 0x58), FLD(f32, p, 0x60), 30.0f)) {
                FLD(f32, p, 0x5c) = FLD(f32, joint, 0x10);
            }
        }
        p = partyGetPtr(marioGetExtraPartyId());
        if (p) {
            if (kururing_in_box(mobj->position.x, mobj->position.z, FLD(f32, p, 0x58), FLD(f32, p, 0x60), 30.0f)) {
                FLD(f32, p, 0x5c) = FLD(f32, joint, 0x10);
            }
        }
        {
            s32 i;
            NpcWork* wp = npcGetWorkPtr();
            u8* npc = (u8*)wp->entries;
            for (i = 0; i < wp->total; i++, npc += 0x340) {
                if (FLD(u32, npc, 0) & 1) {
                    if (kururing_in_box(mobj->position.x, mobj->position.z, FLD(f32, npc, 0x8c), FLD(f32, npc, 0x94), 42.420002f)) {
                        FLD(f32, npc, 0x90) = FLD(f32, joint, 0x10);
                    }
                }
            }
        }
        p = itemNearDistCheck(mobj->position.x, mobj->position.y, mobj->position.z, 42.420002f);
        if (p) {
            FLD(f32, p, 0x40) = FLD(f32, joint, 0x10);
        }
        if (animPoseGetLoopTimes(mobj->poseId) < 2.0f) {
            break;
        }
        KURU_POSE_FLAGS(mobj) &= ~0x10;
        mobj->flags &= ~0x400;
        animPoseSetAnim(mobj->poseId, "S_1", 1);
        psndSFXOn_3D((const char*)0x1f0, &mobj->position);
        mobj->unk1B0 = 20;
        mobj->state++;
    }
    case 11:
        mobj->unk1B0--;
        if (mobj->unk1B0 == 0) {
            mobj->state++;
        }
        break;
    case 12:
        mobj->flags &= ~8;
        mobj->state = 0;
        break;
    }
    return 0;
}
#endif
#ifdef NONMATCHING
USER_FUNC(evt_mobj_kururing_floor) {
    s32 grp;
    s32 arg6;
    s32* args = event->args;
    const char* name;
    const char* anim;
    MapObjectEntry* mobj;
    f32 x, y, z;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    grp = evtGetValue(event, args[4]);
    evtGetValue(event, args[5]);
    arg6 = args[6];
    anim = "MOBJ_KururinFloor";
    if (animGroupBaseAsync(anim, gp->inBattle != 0, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobj->position = (Vec){x, 0.1f + y, z};
    mobj->mainFunc = mobj_kururing_floor;
    mobj->flagVar = arg6;
    mobj->state = 0;
    mobj->flags |= 0x1010000;
    mobj->flags |= 2;
    mobjCalcMtx(mobj);
    mobj->scale2 = (Vec){200.0f, mobj->scale2.y, 200.0f};
    mobjCalcMtx2(mobj);
    {
        Vec dz = (Vec){x, y, z};
        char oname[16] = "o_";
        char iname[16] = "i_";
    }
    mapGrpFlagOn((const char*)grp, 0x400000);
    animPoseSetAnim(mobj->poseId, "S_1", 1);
    animPoseWorldPositionEvalOn(mobj->poseId);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(kpa_powerup) {
    s32* args = event->args;
    Vec pos;
    pos.x = evtGetFloat(event, args[0]);
    pos.y = evtGetFloat(event, args[1]);
    pos.z = evtGetFloat(event, args[2]);
    kpaAddScorePos(500, &pos);
    if (kpaGetLevel() == 3) {
        kpaAddScore(1000);
    }
    kpaPowUp();
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_koopa_ojama_blk_evt(MapObjectEntry* mobj) {
    BOOL ok = FALSE;
    void* item;
    {
        Vec dv = (Vec){0.0f, -2000.0f, 0.0f};
    }
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            switch (kpaGetLevel()) {
            case 0:
            case 1:
                if (mobj->hitFlag == 0x20000000 || mobj->hitFlag == 0x4000000) {
                    ok = TRUE;
                }
                break;
            case 2:
                if (mobj->hitFlag == 0x20000000 || mobj->hitFlag == 0x10000000 || mobj->hitFlag == 0x4000000) {
                    ok = TRUE;
                }
                break;
            case 3:
                ok = TRUE;
                break;
            }
            if (!ok) {
                mobj->flags &= ~8;
                break;
            }
            mobjRunEvent(mobj, (s32*)mobj->event);
            evtSetValue(NULL, mobj->flagVar, 1);
            if (mobj->hitFlag == 0x4000000) {
                npcKoopaModeMobjBoundDeadCheck(mobj->hitObj[0].hitObject);
            }
            if (mobj->hitObj[0].hitObject) {
                FLD(u16, mobj->hitObj[0].hitObject, 0) |= 1;
            }
            mobj->flags |= 2;
            kpaAddScore(kpaMutekiCheck() ? 500 : 400);
            mobj->state = 10;
        }
        break;
    case 10:
        psndSFXOn_3D((const char*)0x1c4, &mobj->position);
        effMObjBrokenEntry(5, mobj->position.x, 25.0f + mobj->position.y, 25.0f + mobj->position.z);
        item = itemEntry(mobj->position.x, 25.0f + mobj->position.y, mobj->position.z, mobj->name, 0x59, 4, -1, kpa_powerup_evt);
        if (item) {
            itemStatusOn(item, 0x10);
            itemFlagOn(item, 0x14);
            FLD(s32, item, 0x7c) = 10000;
            FLD(s32, item, 0x78) = 0;
            FLD(f32, item, 0x80) = 0.45f;
            FLD(f32, item, 0x84) = 0.7f;
            FLD(s32, item, 0x88) = 0;
            FLD(f32, item, 0x58) = 500.0f;
            FLD(f32, item, 0x50) = 120.0f;
            FLD(s32, item, 0x54) = 90;
            psndSFXOn_3D((const char*)0x836, &mobj->position);
        }
        mobj->state = 99;
        break;
    case 99:
        mobjDelete(mobj->name);
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_koopa_ojama_blk) {
    s32 val;
    s32 arg5;
    s32* args = event->args;
    const char* anim;
    const char* name;
    MapObjectEntry* mobj;
    f32 x, y, z;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    val = evtGetValue(event, args[4]);
    arg5 = args[5];
    anim = (const char*)evtGetValue(event, args[6]);
    if (animGroupBaseAsync(anim, gp->inBattle != 0, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobj->flags |= 4;
    mobj->position = (Vec){x, y, z};
    mobj->mainFunc = mobj_koopa_ojama_blk_evt;
    mobj->event = val;
    mobj->extraEvent = 0;
    mobj->flags |= 0x3c000000;
    mobj->flagVar = arg5;
    mobj->state = 0;
    if (evtGetValue(event, arg5)) {
        mobj->state = 99;
    }
    return EVT_RETURN_DONE;
}
#endif









#ifdef NONMATCHING /* not in the target object (dead code stripped at link) */
void mobj_koopa_stone_blk(void) {
    mobjNameToPtr("MOBJ_BombRock");
    mobjNameToPtr("OFF_d_bom");
    mobjNameToPtr("MOBJ_trap");
}
#endif

#ifdef NONMATCHING
s32 mobj_koopa_stone_blk_evt(MapObjectEntry* mobj) {
    "MOBJ_BombRock";
    "OFF_d_bom";
    "MOBJ_trap";
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_koopa_stone_blk) {
    s32 val;
    s32 arg5;
    s32* args = event->args;
    const char* anim;
    const char* name;
    MapObjectEntry* mobj;
    f32 x, y, z;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    val = evtGetValue(event, args[4]);
    arg5 = args[5];
    anim = (const char*)evtGetValue(event, args[6]);
    if (animGroupBaseAsync(anim, gp->inBattle != 0, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobj->flags |= 4;
    mobj->position = (Vec){x, y, z};
    mobj->mainFunc = mobj_koopa_stone_blk_evt;
    mobj->event = val;
    mobj->extraEvent = 0;
    mobj->flagVar = arg5;
    mobj->state = 99;
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_koopa_brickblk(MapObjectEntry* mobj) {
    BOOL ok = FALSE;
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            switch (kpaGetLevel()) {
            case 0:
                if (mobj->hitFlag == 0x20000000) {
                    ok = TRUE;
                }
                break;
            case 1:
                if (mobj->hitFlag == 0x20000000 || mobj->hitFlag == 0x4000000) {
                    ok = TRUE;
                }
                break;
            case 2:
                if (mobj->hitFlag == 0x20000000 || mobj->hitFlag == 0x10000000 || mobj->hitFlag == 0x4000000) {
                    ok = TRUE;
                }
                break;
            case 3:
                ok = TRUE;
                break;
            }
            if (!ok) {
                if (mobj->hitFlag == 0x4000000) {
                    npcKoopaModeMobjBoundDeadCheck(mobj->hitObj[0].hitObject);
                    mobj->state = 20;
                    break;
                }
                mobj->flags &= ~8;
                break;
            }
            mobjRunEvent(mobj, (s32*)mobj->event);
            evtSetValue(NULL, mobj->flagVar, 1);
            if (mobj->hitFlag == 0x4000000) {
                npcKoopaModeMobjBoundDeadCheck(mobj->hitObj[0].hitObject);
            }
            if (mobj->hitObj[0].hitObject) {
                FLD(u16, mobj->hitObj[0].hitObject, 0) |= 1;
            }
            mobj->flags |= 2;
            kpaAddScore(kpaMutekiCheck() ? 500 : 400);
            mobj->state = 10;
        }
        break;
    case 10:
        psndSFXOn_3D((const char*)0x1b8, &mobj->position);
        if (!strcmp(mobj->animName, "MOBJ_FlowBrickBlock")) {
            effMObjBrokenEntry(0, mobj->position.x, 12.5f + mobj->position.y, 12.5f + mobj->position.z);
        } else if (!strcmp(mobj->animName, "MOBJ_block_ky")) {
            effMObjBrokenEntry(1, mobj->position.x, 12.5f + mobj->position.y, 12.5f + mobj->position.z);
        } else if (!strcmp(mobj->animName, "MOBJ_bigblock_01")) {
            effMObjBrokenEntry(3, mobj->position.x, 25.0f + mobj->position.y, 25.0f + mobj->position.z);
        } else if (!strcmp(mobj->animName, "MOBJ_bigblock_02")) {
            effMObjBrokenEntry(4, mobj->position.x, 25.0f + mobj->position.y, 25.0f + mobj->position.z);
        }
        mobj->state = 99;
        break;
    case 20:
        psndSFXOn_3D((const char*)0x1b7, &mobj->position);
        animPoseSetAnim(mobj->poseId, "A_1", 1);
        mobj->state = 21;
        break;
    case 21:
        if (!(mobj->flags & 8)) {
            mobj->state = 0;
            break;
        }
        if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
            break;
        }
        animPoseSetAnim(mobj->poseId, "S_1", 1);
        mobj->state = 0;
        mobj->flags &= ~8;
        break;
    case 99:
        mobjDelete(mobj->name);
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_koopa_brick) {
    const char* name;
    s32 arg7;
    s32 val;
    s32* args = event->args;
    s32 item;
    s32 kind;
    const char* anim;
    s32 inBattle;
    f32 x, y, z;
    MapObjectEntry* mobj;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    item = evtGetValue(event, args[4]);
    kind = args[5];
    val = evtGetValue(event, args[6]);
    arg7 = args[7];
    inBattle = 0;
    inBattle = gp->inBattle != inBattle;
    switch (kind) {
    case 0:
        anim = "MOBJ_FlowBrickBlock";
        break;
    case 1:
        anim = "MOBJ_block_ky";
        break;
    case 2:
        anim = "MOBJ_bigblock_01";
        break;
    case 3:
    default:
        anim = "MOBJ_bigblock_02";
        break;
    }
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_koopa_brickblk;
    mobj->event = val;
    mobj->flags |= 4;
    mobj->flags |= 0x3c000000;
    mobj->flagVar = arg7;
    mobj->state = 0;
    mobj->typeData[0] = item;
    mobjCalcMtx(mobj);
    animPoseSetAnim(mobj->poseId, "S_1", 1);
    if (evtGetValue(event, arg7)) {
        animPoseSetAnim(mobj->poseId, "S_1", 1);
        mobj->state = 99;
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_koopa_badgeblk(MapObjectEntry* mobj) {
    void* item;
    BOOL ok;
    marioGetPtr();
    ok = FALSE;
    switch (mobj->state) {
    case 0:
        if (!(mobj->flags & 8)) {
            break;
        }
        if (mobj->hitFlag != 0x4000000) {
            mobj->flags &= ~8;
            break;
        }
        if (mobj->flags & 0x800) {
            mobjHitEntry(mobj, 0);
        }
        animPoseSetAnim(mobj->poseId, "A_1", 1);
        if ((s32*)mobj->event != NULL) {
            mobjRunEvent(mobj, (s32*)mobj->event);
        } else if (mobj->typeData[0] == 0x59) {
            itemEntry(mobj->position.x, 12.5f + mobj->position.y, mobj->position.z, mobj->name, mobj->typeData[0], 4, -1, kpa_powerup_evt);
            item = itemNameToPtr(mobj->name);
            itemStatusOn(item, 0x10);
            itemFlagOn(item, 0x14);
            FLD(s32, item, 0x7c) = 10000;
            FLD(s32, item, 0x78) = 0;
            FLD(f32, item, 0x80) = 0.45f;
            FLD(f32, item, 0x84) = 0.7f;
            FLD(s32, item, 0x88) = 0;
            FLD(f32, item, 0x58) = 500.0f;
            FLD(f32, item, 0x50) = 120.0f;
            FLD(s32, item, 0x54) = 90;
            psndSFXOn_3D((const char*)0x836, &mobj->position);
        } else {
            kpaAddCoin(1);
            itemEntry(mobj->position.x, mobj->position.y, mobj->position.z, NULL, 0x79, 0xf, -1, NULL);
            evtSetValue(NULL, mobj->flagVar, 1);
            psndSFXOn_3D((const char*)0x5b, &mobj->position);
        }
        if (mobj->hitFlag == 0x4000000) {
            npcKoopaModeMobjBoundDeadCheck(mobj->hitObj[0].hitObject);
        }
        mobj->state++;
        break;
    case 1:
        if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
            break;
        }
        animPoseSetAnim(mobj->poseId, "S_2", 1);
        mobj->flags &= ~8;
        mobj->state = 90;
        strcpy(mobj->animName, "MOBJ_Block");
        break;
    case 90:
        if (mobj->flags & 8) {
            switch (kpaGetLevel()) {
            case 3:
                ok = TRUE;
                break;
            case 2: break;
            }
            if (!ok) {
                mobj->flags &= ~8;
                break;
            }
            if (mobj->hitFlag == 0x4000000) {
                npcKoopaModeMobjBoundDeadCheck(mobj->hitObj[0].hitObject);
            }
            if (mobj->hitObj[0].hitObject) {
                FLD(u16, mobj->hitObj[0].hitObject, 0) |= 1;
            }
            mobj->flags |= 2;
            mobj->state++;
        }
        break;
    case 91:
        psndSFXOn_3D((const char*)0x1b8, &mobj->position);
        effMObjBrokenEntry(2, mobj->position.x, 12.5f + mobj->position.y, 12.5f + mobj->position.z);
        mobj->state = 99;
        break;
    case 99:
        mobjDelete(mobj->name);
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_koopa_badgeblk) {
    s32 val;
    s32 item;
    s32* args = event->args;
    s32 arg6;
    int new_var; // FAKE: separate inBattle temp needed for the target register allocation
    const char* name;
    MapObjectEntry* mobj;
    const char* anim;
    f32 x, y, z;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    item = evtGetValue(event, args[4]);
    val = evtGetValue(event, args[5]);
    arg6 = args[6];
    new_var = gp->inBattle;
    new_var = new_var != 0;
    anim = "MOBJ_HatenaBlock";
    if (animGroupBaseAsync(anim, new_var, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_koopa_badgeblk;
    mobj->event = val;
    mobj->flags |= 4;
    mobj->flags |= 0x3c000000;
    mobj->flagVar = arg6;
    mobj->state = 0;
    mobj->typeData[0] = item;
    mobjCalcMtx(mobj);
    animPoseSetAnim(mobj->poseId, "S_1", 1);
    if (evtGetValue(event, arg6)) {
        mobj->state = 90;
        animPoseSetAnim(mobj->poseId, "S_2", 1);
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_koopa_hidden_blk) {
    const char* name;
    const char* anim;
    s32 item;
    s32* args = event->args;
    s32 inBattle;
    s32 arg7;
    f32 x, y, z;
    s32 val;
    MapObjectEntry* mobj;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    item = evtGetValue(event, args[4]);
    val = evtGetValue(event, args[6]);
    arg7 = args[7];
    inBattle = gp->inBattle;
    inBattle = inBattle != 0;
    anim = "MOBJ_HiddenHatenaBlock";
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->flags |= 0x800;
    mobjHitEntry(mobj, 1);
    mobj->mainFunc = mobj_koopa_badgeblk;
    mobj->event = val;
    mobj->flags |= 4;
    mobj->flags |= 0x3c000000;
    mobj->flagVar = arg7;
    mobj->state = 0;
    mobj->typeData[0] = item;
    mobjCalcMtx(mobj);
    animPoseSetAnim(mobj->poseId, "S_1", 1);
    if (evtGetValue(event, arg7)) {
        mobj->state = 90;
        animPoseSetAnim(mobj->poseId, "S_2", 1);
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_koopa_blk(MapObjectEntry* mobj) {
    BOOL ok = FALSE;
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            switch (kpaGetLevel()) {
            case 3:
                ok = TRUE;
                break;
            case 2:
                break;
            }
            if (!ok) {
                mobj->flags &= ~8;
                break;
            }
            mobjRunEvent(mobj, (s32*)mobj->event);
            evtSetValue(NULL, mobj->flagVar, 1);
            if (mobj->hitFlag == 0x4000000) {
                npcKoopaModeMobjBoundDeadCheck(mobj->hitObj[0].hitObject);
            }
            if (mobj->hitObj[0].hitObject) {
                FLD(u16, mobj->hitObj[0].hitObject, 0) |= 1;
            }
            mobj->flags |= 2;
            mobj->state = 10;
        }
        break;
    case 10:
        psndSFXOn_3D((const char*)0x1b8, &mobj->position);
        effMObjBrokenEntry(2, mobj->position.x, 12.5f + mobj->position.y, 12.5f + mobj->position.z);
        mobj->state = 99;
    case 99:
        mobjDelete(mobj->name);
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_koopa_blk) {
    s32 val;
    s32* args = event->args;
    s32 arg6;
    const char* name;
    MapObjectEntry* mobj;
    f32 x, y, z;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    val = evtGetValue(event, args[5]);
    arg6 = args[6];
    if (animGroupBaseAsync("MOBJ_Block", gp->inBattle != 0, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, "MOBJ_Block");
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_koopa_blk;
    mobj->event = val;
    mobj->flags |= 4;
    mobj->flags |= 0x3c000000;
    mobj->flagVar = arg6;
    mobj->state = 0;
    mobjCalcMtx(mobj);
    animPoseSetAnim(mobj->poseId, "S_1", 1);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 mobj_koopa_dokan_evt(MapObjectEntry* mobj) {
    BOOL ok = FALSE;
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            switch (kpaGetLevel()) {
            case 0:
                break;
            case 1:
            case 2:
                if (mobj->hitFlag == 0x20000000) {
                    ok = TRUE;
                }
                break;
            case 3:
                ok = TRUE;
                break;
            }
            if (!ok) {
                mobj->flags &= ~8;
                break;
            }
            mobjRunEvent(mobj, (s32*)mobj->event);
            evtSetValue(NULL, mobj->flagVar, 1);
            if (mobj->hitFlag == 0x4000000) {
                npcKoopaModeMobjBoundDeadCheck(mobj->hitObj[0].hitObject);
            }
            if (mobj->hitObj[0].hitObject) {
                FLD(u16, mobj->hitObj[0].hitObject, 0) |= 1;
            }
            mobj->flags |= 2;
            kpaAddScore(kpaMutekiCheck() ? 500 : 400);
            mobj->state = 10;
        }
        break;
    case 10:
        if (!strcmp(mobj->animName, "MOBJ_GreenPipe_ks")) {
            effMObjBrokenEntry(6, mobj->position.x, 25.0f + mobj->position.y, 25.0f + mobj->position.z);
        } else if (!strcmp(mobj->animName, "MOBJ_GreenPipe_kl")) {
            effMObjBrokenEntry(6, mobj->position.x, 7.5f + (25.0f + mobj->position.y), 25.0f + mobj->position.z);
        } else {
            effMObjBrokenEntry(6, mobj->position.x - 25.0f, 25.0f + mobj->position.y, 25.0f + mobj->position.z);
        }
        psndSFXOn_3D((const char*)0x834, &mobj->position);
        mobj->state = 99;
        break;
    case 99:
        mobjDelete(mobj->name);
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_koopa_dokan) {
    s32 kind;
    s32 val;
    s32* args = event->args;
    s32 arg6;
    const char* name;
    const char* anim;
    MapObjectEntry* mobj;
    s32 inBattle;
    f32 x, y, z;
    kind = evtGetValue(event, args[0]);
    name = (const char*)evtGetValue(event, args[1]);
    x = evtGetFloat(event, args[2]);
    y = evtGetFloat(event, args[3]);
    z = evtGetFloat(event, args[4]);
    val = evtGetValue(event, args[5]);
    arg6 = args[6];
    inBattle = gp->inBattle != 0;
    switch (kind) {
    case 0:
        anim = "MOBJ_GreenPipe_ks";
        break;
    case 1:
        anim = "MOBJ_GreenPipe_kl";
        break;
    case 2:
        anim = "MOBJ_GreenPipe_ky";
        break;
    }
    if (animGroupBaseAsync(anim, inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobj->flags |= 6;
    mobj->position = (Vec){x, y, z};
    mobj->mainFunc = mobj_koopa_dokan_evt;
    mobj->event = val;
    mobj->extraEvent = 0;
    mobjCalcMtx(mobj);
    animPoseSetAnim(mobj->poseId, "S_1", 1);
    mobj->flags |= 0x3c000000;
    mobj->flagVar = arg6;
    mobj->state = 0;
    if (evtGetValue(event, arg6)) {
        mobj->state = 99;
    }
    return EVT_RETURN_DONE;
}
#endif

extern EffectEntry* effFireEntry(s32 type, s32 duration, f32 x, f32 y, f32 z, f32 scale);

#ifdef NONMATCHING
USER_FUNC(fire_func) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    s32 dur = evtGetValue(event, args[3]);
    EffectEntry* eff;
    f32 a, b;
    if (isFirstCall) {
        f32 t = (f32)irand(10) / 10.0f;
        event->userdatap[0] = effFireEntry(5, dur, x, y, z, 0.8f + t);
    }
    a = event->userdataf[1];
    b = event->userdataf[2];
    a = a + (1.0f - a) / 8.0f;
    b = b + (1.0f - b) / 8.0f;
    eff = event->userdatap[0];
    FLD(f32, eff->userdata, 0x78) = a;
    FLD(f32, eff->userdata, 0x7c) = b;
    if (a >= 0.99f) {
        FLD(f32, eff->userdata, 0x78) = 1.0f;
        FLD(f32, eff->userdata, 0x7c) = 1.0f;
        return EVT_RETURN_DONE;
    }
    event->userdataf[1] = a;
    event->userdataf[2] = b;
    return EVT_RETURN_BLOCK;
}
#endif

#ifdef NONMATCHING
s32 mobj_koopa_sango_evt(MapObjectEntry* mobj) {
    BOOL ok = FALSE;
    EventEntry* ev;
    switch (mobj->state) {
    case 0:
        if (mobj->flags & 8) {
            switch (kpaGetLevel()) {
            case 0:
            case 1:
            case 2:
                if (mobj->hitFlag == 0x20000000) {
                    ok = TRUE;
                }
                break;
            case 3:
                ok = TRUE;
                break;
            }
            if (!ok) {
                mobj->flags &= ~8;
                break;
            }
            mobjRunEvent(mobj, (s32*)mobj->event);
            evtSetValue(NULL, mobj->flagVar, 1);
            if (mobj->hitFlag == 0x4000000) {
                npcKoopaModeMobjBoundDeadCheck(mobj->hitObj[0].hitObject);
            }
            if (mobj->hitObj[0].hitObject) {
                FLD(u16, mobj->hitObj[0].hitObject, 0) |= 1;
            }
            mobj->flags |= 2;
            kpaAddScore(kpaMutekiCheck() ? 500 : 400);
            mobj->state = 10;
        }
        break;
    case 10:
        if (mobj->hitFlag == 0x20000000) {
            psndSFXOn_3D((const char*)0xb67, &mobj->position);
        }
        ev = evtEntry(evt_fire, 0, 0);
        ev->lwData[0] = (s32)(1024.0f * mobj->position.x) + 0xF24A7A80;
        ev->lwData[1] = (s32)(1024.0f * mobj->position.y) + 0xF24A7A80;
        ev->lwData[2] = (s32)(1024.0f * (10.0f + mobj->position.z)) + 0xF24A7A80;
        ev->lwData[3] = 90;
        mobj->state++;
        break;
    case 20:
        ev = evtEntry(evt_fire, 0, 0);
        ev->lwData[0] = (s32)(1024.0f * (10.0f + mobj->position.x)) + 0xF24A7A80;
        ev->lwData[1] = (s32)(1024.0f * (30.0f + mobj->position.y)) + 0xF24A7A80;
        ev->lwData[2] = (s32)(1024.0f * (10.0f + mobj->position.z)) + 0xF24A7A80;
        ev->lwData[3] = 80;
        mobj->state++;
        break;
    case 30:
        ev = evtEntry(evt_fire, 0, 0);
        ev->lwData[0] = (s32)(1024.0f * (mobj->position.x - 10.0f)) + 0xF24A7A80;
        ev->lwData[1] = (s32)(1024.0f * (60.0f + mobj->position.y)) + 0xF24A7A80;
        ev->lwData[2] = (s32)(1024.0f * (10.0f + mobj->position.z)) + 0xF24A7A80;
        ev->lwData[3] = 70;
        mobj->state++;
        break;
    case 98:
        effMObjBrokenEntry(7, mobj->position.x, mobj->position.y, 10.0f + mobj->position.z);
        mobj->state++;
        break;
    case 99:
        mobjDelete(mobj->name);
        break;
    default:
        mobj->state++;
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_koopa_sango) {
    s32 val;
    s32 arg5;
    s32* args = event->args;
    const char* name;
    MapObjectEntry* mobj;
    f32 x, y, z;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    val = evtGetValue(event, args[4]);
    arg5 = args[5];
    if (animGroupBaseAsync("MOBJ_sango", gp->inBattle != 0, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, "MOBJ_sango");
    mobj = mobjNameToPtr(name);
    mobj->flags |= 0x84;
    mobj->position = (Vec){x, y, z};
    mobj->mainFunc = mobj_koopa_sango_evt;
    mobj->event = val;
    mobj->extraEvent = 0;
    mobj->flags |= 0x3c000000;
    mobj->flagVar = arg5;
    mobj->state = 0;
    if (evtGetValue(event, arg5)) {
        mobj->state = 99;
    }
    return EVT_RETURN_DONE;
}
#endif

extern s32 psndSFXChk(s32 id);
extern void psndSFXOff(s32 id);
extern f32 distABf(f32 x1, f32 y1, f32 x2, f32 y2);

#ifdef NONMATCHING
s32 mobj_koopa_fireber_dodai_evt(MapObjectEntry* mobj) {
    Mtx mtx;
    Mtx rot;
    char buf[0x20];
    char buf2[0x20];
    BOOL ok = FALSE;
    NpcEntry* npc;
    s32 i;
    MarioWork* mario = marioGetPtr();
    if (mobj->state < 10) {
        if (distABf(mario->position.x, mario->position.y, mobj->position.x, mobj->position.y) < 150.0f) {
            if (psndSFXChk(mobj->unk1B4)) {
                mobj->unk1B4 = psndSFXOn_3D((const char*)0x1cd, &mobj->position);
            }
        } else if (psndSFXChk(mobj->unk1B4) == 0) {
            psndSFXOff(mobj->unk1B4);
            mobj->unk1B4 = -1;
        }
        PSMTXIdentity(mtx);
        PSMTXTransApply(mtx, mtx, -mobj->position.x, -mobj->position.y, -mobj->position.z);
        PSMTXRotRad(rot, 'Z', 0.017453292f * FLD(f32, mobj, 0x1ac));
        PSMTXConcat(rot, mtx, mtx);
        PSMTXTransApply(mtx, mtx, mobj->position.x, mobj->position.y, mobj->position.z);
        for (i = 0; i < mobj->typeData[1]; i++) {
            sprintf(buf, "%s%2x", mobj->name, i);
            npc = npcNameToPtr(buf);
            PSMTXMultVec(mtx, &FLD(Vec, npc, 0x8c), &FLD(Vec, npc, 0x8c));
        }
    }
    switch (mobj->state) {
    case 0:
        if (!(mobj->flags & 8)) {
            break;
        }
        switch (kpaGetLevel()) {
        case 0:
        case 1:
        case 2:
            if (mobj->hitFlag == 0x20000000) {
                ok = TRUE;
            }
            break;
        case 3:
            ok = TRUE;
            break;
        }
        if (!ok) {
            mobj->flags &= ~8;
            break;
        }
        mobjRunEvent(mobj, (s32*)mobj->event);
        evtSetValue(NULL, mobj->flagVar, 1);
        if (mobj->hitObj[0].hitObject) {
            FLD(u16, mobj->hitObj[0].hitObject, 0) |= 1;
        }
        mobj->flags |= 2;
        kpaAddScore(kpaMutekiCheck() ? 500 : 400);
        mobj->state = 10;
        break;
    case 10:
        psndSFXOn_3D((const char*)0x1b8, &mobj->position);
        effMObjBrokenEntry(0, mobj->position.x, 12.5f + mobj->position.y, 12.5f + mobj->position.z);
        mobj->state++;
        break;
    case 11:
        mobj->position.y = -1000.0f;
        for (i = 0; i < mobj->typeData[1]; i++) {
            sprintf(buf, "%s%2x", mobj->name, i);
            npc = npcNameToPtr(buf);
            FLD(s32, npc, 0x18c) = 0;
            FLD(s32, npc, 0x188) = 0;
            FLD(Vec, npc, 0x158) = FLD(Vec, npc, 0x8c);
            FLD(f32, npc, 0x164) = irand(101) / 200.0f;
            FLD(f32, npc, 0x168) = 6.0f - irand(101) / 75.0f;
            FLD(f32, npc, 0x16c) = 4.8f;
            FLD(f32, npc, 0x1c0) = 2.0f;
            FLD(u32, npc, 0x1d4) |= 4;
        }
        if (psndSFXChk(mobj->unk1B4) == 0) {
            psndSFXOff(mobj->unk1B4);
            mobj->unk1B4 = -1;
        }
        mobj->state++;
        break;
    case 12:
        for (i = 0; i < mobj->typeData[1]; i++) {
            sprintf(buf, "%s%2x", mobj->name, i);
            npc = npcNameToPtr(buf);
            FLD(f32, npc, 0x1b4) += FLD(f32, npc, 0x164);
            FLD(f32, npc, 0x90) += FLD(f32, npc, 0x168);
            FLD(f32, npc, 0x1bc) += FLD(f32, npc, 0x16c);
            FLD(f32, npc, 0xe0) += 0.04f;
            if (FLD(f32, npc, 0xe0) > 3.0f) {
                FLD(f32, npc, 0xe0) = 3.0f;
            }
            FLD(f32, npc, 0xe8) = FLD(f32, npc, 0xe4) = FLD(f32, npc, 0xe0);
            FLD(f32, npc, 0x168) -= 0.2f;
        }
        if (FLD(f32, npc, 0x1c0) <= FLD(f32, npc, 0x1a0)) {
            mobj->state = 99;
        }
        break;
    case 99: {
        s32 j;
        for (j = 0; j < mobj->typeData[1]; j++) {
            sprintf(buf2, "%s%2x", mobj->name, j);
            npcDelete(npcNameToPtr(buf2));
        }
        mobjDelete(mobj->name);
        break;
    }
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_koopa_fireber_dodai) {
    const char* name;
    s32 dir, count, arg7, arg8, i;
    s32* args = event->args;
    MapObjectEntry* mobj;
    void* npc;
    f32 x, y, z, spd, base, step;
    char buf[32];
    s32 inBattle;
    dir = evtGetValue(event, args[0]);
    name = (const char*)evtGetValue(event, args[1]);
    x = evtGetFloat(event, args[2]);
    y = evtGetFloat(event, args[3]);
    z = evtGetFloat(event, args[4]);
    count = evtGetValue(event, args[5]);
    spd = evtGetFloat(event, args[6]);
    arg7 = evtGetValue(event, args[7]);
    arg8 = args[8];
    inBattle = gp->inBattle != 0;
    if (animGroupBaseAsync("MOBJ_fire_dodai", inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    if (animGroupBaseAsync("c_fireber", inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, "MOBJ_fire_dodai");
    mobj = mobjNameToPtr(name);
    mobj->flags |= 4;
    mobj->position = (Vec){x, y, z};
    mobj->mainFunc = mobj_koopa_fireber_dodai_evt;
    mobj->event = arg7;
    mobj->extraEvent = 0;
    mobj->flags |= 0x3c000000;
    mobj->flagVar = arg8;
    mobj->state = 0;
    if (evtGetValue(event, arg8)) {
        mobj->state = 99;
    }
    if (spd == 0.0f) {
        spd = 1.0f;
    }
    mobj->typeData[1] = count;
    FLD(f32, mobj, 0x1ac) = dir ? __fabsf(spd) : -__fabsf(spd);
    mobj->unk1B4 = 0;
    for (i = 0; i < count; i++) {
        sprintf(buf, "%s%2x", name, i);
        npcEntry(buf, "c_fireber");
        npc = npcNameToPtr(buf);
        FLD(u32, npc, 0) |= 0x8000000;
        FLD(u16, npc, 0x31e) |= 0xf;
        FLD(f32, npc, 0x8c) = x;
        FLD(f32, npc, 0x90) = 25.0f + y + 25.0f * i;
        FLD(f32, npc, 0x94) = 175.0f + z;
        animPoseSetAnim(FLD(s32, npc, 0x104), "FRB_S_1", 1);
        FLD(u32, npc, 0) |= 0x40000;
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(kpa_get_pole_name) {
    MapObjectEntry* mobj = event->thisMapObj;
    s32* args = event->args;
    if (mobj != NULL) {
        evtSetValue(event, args[0], (s32)mobj->name);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(kpa_get_hata_name) {
    MapObjectEntry* mobj = event->thisMapObj;
    s32* args = event->args;
    if (mobj != NULL) {
        evtSetValue(event, args[0], (s32)mobj->linkedName);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
static USER_FUNC(kpa_get_level) {
    s32* args = event->args;
    evtSetValue(event, args[0], kpaGetLevel());
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(kpa_get_width) {
    s32* args = event->args;
    evtSetValue(event, args[0], (s32)marioGetPtr()->wPlayerCollisionBox.x);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(kpa_score_to_str) {
    s32 score = evtGetValue(event, event->args[0]);
    s32 d[4];
    s32 i, j;
    d[0] = score / 1000;
    score = score % 1000;
    d[1] = score / 100;
    score = score % 100;
    d[2] = score / 10;
    d[3] = score % 10;
    i = 0;
    for (j = 0; j < 4; j++) {
        if (i != 0 || d[j] != 0) {
            psw->str[i] = d[j] + '0';
            i++;
        }
    }
    psw->str[4] = 0;
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
void kpa_disp_pole_score(CameraId camId, void* param) {
    Mtx trans;
    Mtx scale;
    PSMTXTrans(trans, psw->x, psw->y, 300.0f);
    PSMTXScale(scale, 0.5f, 0.5f, 0.5f);
    PSMTXConcat(trans, scale, trans);
    FontDrawStart();
    FontDrawColor((GXColor){255, 255, 255, 255});
    FontDrawStringMtx(trans, psw->str);
}
#endif

#ifdef NONMATCHING
USER_FUNC(kpa_disp_pole_score_main) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    f32 spd = evtGetFloat(event, args[3]);
    if (isFirstCall) {
        psw->x = x;
        psw->y = y;
        psw->z = z;
    }
    if (psw->y < 230.0f) {
        psw->y += spd;
    } else {
        psw->y = 230.0f;
    }
    dispEntry(CAMERA_3D, 0.0f, 2, kpa_disp_pole_score, NULL);
    return EVT_RETURN_BLOCK;
}
#endif

#ifdef NONMATCHING
USER_FUNC(kpa_disp_pole_init) {
    psw = _mapAlloc(0x14);
    psw->str[0] = 0;
    psw->z = 0.0f;
    psw->y = 0.0f;
    psw->x = 0.0f;
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(kpa_clear_jump_data) {
    MarioWork* mario = marioGetPtr();
    mario->airTimer = 0;
    return EVT_RETURN_DONE;
}
#endif

EVT_BEGIN(kpa_pole)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_cam_letter_box_onoff, 0, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_mario_cam_y_on)
    CALL(kpa_disp_pole_init)
    CALL(kpa_clear_jump_data)
    CALL(kpa_get_hata_name, LW(15))
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(kpa_chg_pose, STRING((char*)str_802C40DC))
    CALL(evt_mario_get_pos, 0, LW(1), LW(2), LW(3))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C40E8), LW(1), LW(2), LW(3), 0)
    CALL(evt_mobj_get_x_position, LW(15), LW(4))
    CALL(kpa_get_width, LW(5))
    MULTIPLY_FLOAT(LW(5), FLOAT(0.5996094f))
    SUBTRACT_FLOAT(LW(4), LW(5))
    CALL(evt_mario_set_pos, LW(4), LW(2), LW(3))
    CALL(kpa_score_to_str, LW(0))
    SET_FLOAT_VALUE(LW(14), FLOAT(2.0f))
    SET_FLOAT_VALUE(LW(13), FLOAT(2.0f))
    SET_FLOAT_VALUE(LW(7), FLOAT(50.0f))
    BEGIN_INLINE_EVENT
        CALL(evt_mobj_get_position, LW(15), LW(3), LW(4), LW(5))
        ADD_FLOAT(LW(3), FLOAT(7.5f))
        CALL(kpa_disp_pole_score_main, LW(3), LW(7), LW(5), LW(13))
    END_INLINE_EVENT
    CALL(evt_mario_get_pos, 0, LW(1), LW(2), LW(3))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C4100), LW(1), LW(2), LW(3), LW(10))
    BEGIN_INLINE_EVENT_GET_ID(LW(6))
        LOOP(0)
            CALL(evt_mobj_get_y_position, LW(15), LW(4))
            SUBTRACT_FLOAT(LW(4), LW(14))
            CALL(evt_mobj_set_y_position, LW(15), LW(4))
            WAIT_FRAMES(1)
            IF_INT_LESS_OR_EQUAL(LW(4), 25)
                CALL(evt_mobj_set_y_position, LW(15), FLOAT(25.0f))
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        SUBTRACT_FLOAT(LW(1), FLOAT(2.0f))
        CALL(evt_mario_set_pos, LW(0), LW(1), LW(2))
        IF_INT_LESS_OR_EQUAL(LW(1), FLOAT(25.0f))
            CALL(evt_mario_set_pos, LW(0), FLOAT(25.0f), LW(2))
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    LOOP(0)
        IS_EVENT_RUNNING(LW(6), LW(7))
        IF_INT_EQUAL(LW(7), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_snd_sfxoff, LW(10))
    WAIT_MS(200)
    CALL(evt_cam_get_pos, 4, LW(4), LW(5), LW(6))
    CALL(evt_cam_get_at, 4, LW(7), LW(8), LW(9))
    CALL(evt_cam3d_evt_set, LW(4), LW(5), LW(6), LW(7), LW(8), LW(9), 0, 11)
    WAIT_FRAMES(1)
    CALL(kpa_get_width, LW(3))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    MULTIPLY_FLOAT(LW(3), FLOAT(1.1992188f))
    ADD_FLOAT(LW(0), LW(3))
    CALL(evt_cam3d_get_shift, LW(0), LW(1), LW(2), LW(3))
    CALL(evt_cam3d_event_from_road, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), LW(6), LW(7), LW(8), LW(9))
    CALL(evt_cam3d_evt_set, LW(4), LW(5), LW(6), LW(7), LW(8), LW(9), 300, 0)
    WAIT_MS(200)
    CALL(evt_mario_set_pos, LW(0), LW(1), LW(2))
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_mario_set_mov_spd, 0)
    WAIT_MS(200)
    ADD(LW(0), 20)
    CALL(evt_mario_set_pos, LW(0), 0, 10)
    WAIT_FRAMES(1)
    CALL(evt_mario_cont_onoff, 1)
    CALL(evt_cam3d_evt_off, 200, 11)
    WAIT_MS(200)
    RETURN
EVT_END()

EVT_BEGIN(kpa_pole_move)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_cam_letter_box_onoff, 0, 0)
    CALL(evt_mario_key_onoff, 0)
    CALL(kpa_get_pole_name, LW(14))
    CALL(kpa_get_hata_name, LW(15))
    CALL(evt_mobj_get_x_position, LW(14), LW(0))
    CALL(evt_mobj_get_y_position, LW(14), LW(1))
    CALL(evt_mobj_get_z_position, LW(14), LW(2))
    SET_FLOAT_VALUE(LW(6), FLOAT(2.0f))
    SET_FLOAT_VALUE(LW(7), FLOAT(9.0f))
    SET_FLOAT_VALUE(LW(8), FLOAT(5.7998047f))
    CALL(evt_mobj_get_x_position, LW(15), LW(3))
    CALL(evt_mobj_get_y_position, LW(15), LW(4))
    CALL(evt_mobj_get_z_position, LW(15), LW(5))
    SET_FLOAT_VALUE(LW(9), FLOAT(2.0f))
    SET_FLOAT_VALUE(LW(11), FLOAT(5.7998047f))
    SET_FLOAT_VALUE(LW(12), FLOAT(1.0f))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C4118), LW(0), LW(1), LW(2), LW(13))
    LOOP(100)
        ADD_FLOAT(LW(0), LW(6))
        ADD_FLOAT(LW(1), LW(7))
        ADD_FLOAT(LW(2), LW(8))
        ADD_FLOAT(LW(3), LW(9))
        SET_FLOAT_VALUE(LW(4), FLOAT(180.0f))
        MULTIPLY_FLOAT(LW(4), LW(12))
        ADD_FLOAT(LW(4), LW(1))
        ADD_FLOAT(LW(5), LW(11))
        CALL(evt_mobj_set_position, LW(14), LW(0), LW(1), LW(2))
        CALL(evt_mobj_set_scale, LW(14), LW(12), LW(12), LW(12))
        CALL(evt_mobj_set_position, LW(15), LW(3), LW(4), LW(5))
        CALL(evt_mobj_set_scale, LW(15), LW(12), LW(12), LW(12))
        ADD_FLOAT(LW(6), FLOAT(0.0f))
        ADD_FLOAT(LW(7), FLOAT(-0.7998047f))
        ADD_FLOAT(LW(8), FLOAT(0.0f))
        ADD_FLOAT(LW(9), FLOAT(0.0f))
        ADD_FLOAT(LW(11), FLOAT(0.0f))
        ADD_FLOAT(LW(12), FLOAT(0.0390625f))
        IF_INT_GREATER(LW(12), 3)
            SET_FLOAT_VALUE(LW(12), FLOAT(3.0f))
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_snd_sfxoff, LW(13))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(kpa_move_to_toride)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_wait_landon)
    SET_VALUE(LSWF(5), 1)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING((char*)str_802C4130))
        CALL(evt_mapobj_get_position, STRING((char*)str_802C4138), LW(0), LW(1), LW(2))
        ELSE
        CALL(evt_mapobj_get_position, STRING((char*)str_802C4140), LW(0), LW(1), LW(2))
    END_IF
    CALL(kpa_get_level, LW(6))
    SWITCH(LW(6))
        CASE_LESS_OR_EQUAL(1)
        ADD(LW(0), 100)
        CASE_EQUAL(2)
        CALL(kpa_get_width, LW(7))
        MULTIPLY_FLOAT(LW(7), FLOAT(1.1992188f))
        SUBTRACT_FLOAT(LW(0), LW(7))
        CASE_EQUAL(3)
        CALL(kpa_get_width, LW(7))
        MULTIPLY_FLOAT(LW(7), FLOAT(1.1992188f))
        SUBTRACT_FLOAT(LW(0), LW(7))
    END_SWITCH
    CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
    CALL(evt_mario_mov_pos2, LW(0), LW(5), 90)
    IF_INT_GREATER_OR_EQUAL(LW(6), 2)
        CALL(evt_mario_get_pos, 0, LW(1), LW(2), LW(3))
        CALL(evt_snd_sfxon_3d, STRING((char*)str_802C4148), LW(1), LW(2), LW(3), LW(10))
        CALL(evt_mario_dispflag_onoff, 1, 2)
        WAIT_MS(2000)
        CALL(evt_mario_dispflag_onoff, 0, 2)
        CALL(evt_snd_sfxoff, LW(10))
        CALL(kpa_chg_pose, STRING((char*)str_802C415C))
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()


s32 mobj_koopa_pole_evt(MapObjectEntry* mobj);

#ifdef NONMATCHING
s32 mobj_koopa_pole_evt(MapObjectEntry* mobj) {
    MarioWork* mario = marioGetPtr();
    s32 score;
    s32 next = 0;
    s32 off;
    s32 i;
    switch (mobj->state) {
    case 0:
        if (!(mobj->flags & 8)) {
            break;
        }
        if (mario->characterId != 2) {
            mobj->flags &= ~8;
            break;
        }
        switch (kpaGetLevel()) {
        case 0:
        case 1:
            if (mario->position.y < 25.0f) {
                mobj->flags &= ~8;
                break;
            }
            next = 10;
            break;
        case 2:
        case 3:
            next = 50;
            break;
        }
        if (next == 0) {
            break;
        }
        for (i = 0, off = 0; i < FLD(s32, npcGetWorkPtr(), 0x4); off += 0x340, i++) {
            NpcEntry* npc = (NpcEntry*)((char*)FLD(NpcEntry*, npcGetWorkPtr(), 0xc) + off);
            u32 flags = FLD(u32, npc, 0);
            if ((flags & 1) && !(FLD(u32, npc, 0x1d4) & 4) && (flags & 0x8000000) && (flags & 8)) {
                npcGroupDead(npc, 0x20);
            }
        }
        marioKeyOff();
        evtSetValue(NULL, mobj->flagVar, 1);
        FLD(s16, mario, 0x78) = 0;
        mobj->state = next;
        break;
    case 10:
        mario = marioGetPtr();
        score = 0;
        if (kpaGetLevel() == 3) {
            kpaAddScore(2000);
        } else if (kpaGetLevel() >= 2) {
            kpaAddScore(1000);
        } else {
            if (mario->position.y >= 170.0f) {
                score = 1000;
            } else if (mario->position.y >= 100.0f) {
                score = 500;
            } else if (mario->position.y >= 50.0f) {
                score = 200;
            } else {
                score = 100;
            }
            kpaAddScore(score);
        }
        mobjRunEvent(mobj, kpa_pole)->lwData[0] = score;
        mobj->state++;
        break;
    case 11:
        if (evtCheckID(mobj->eventId) != 1) {
            mobj->state = 90;
        }
        break;
    case 50:
        mario = marioGetPtr();
        if (kpaGetLevel() == 3) {
            kpaAddScore(2000);
        } else if (kpaGetLevel() >= 2) {
            kpaAddScore(1000);
        } else {
            if (mario->position.y >= 170.0f) {
                score = 1000;
            } else if (mario->position.y >= 100.0f) {
                score = 500;
            } else if (mario->position.y >= 50.0f) {
                score = 200;
            } else {
                score = 100;
            }
            kpaAddScore(score);
        }
        mobjRunEvent(mobj, kpa_pole_move);
        mobj->state++;
        break;
    case 51:
        if (evtCheckID(mobj->eventId) != 1) {
            mobj->state = 90;
        }
        break;
    case 90:
        mobjRunEvent(mobj, kpa_move_to_toride);
        mobj->state++;
        break;
    case 91:
        if (evtCheckID(mobj->eventId) != 1) {
            mobj->eventId = 0;
            mobj->state++;
        }
        break;
    case 92:
        mobjRunEvent(mobj, (s32*)mobj->extraEvent);
        mobj->state++;
        break;
    case 93:
        if (evtCheckID(mobj->eventId) == 1) {
            break;
        }
        mobj->eventId = 0;
        mobj->state++;
    case 94:
        mobjRunEvent(mobj, (s32*)mobj->event);
        mobj->state++;
        break;
    case 95:
        break;
    }
    return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_mobj_koopa_pole) {
    s32 inBattle;
    s32 val2;
    s32 val;
    const char* name;
    s32* args = event->args;
    s32 arg6;
    MapObjectEntry* mobj;
    MapObjectEntry* hata;
    f32 x, y, z;
    inBattle = gp->inBattle != 0;
    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    val = evtGetValue(event, args[4]);
    val2 = evtGetValue(event, args[5]);
    arg6 = args[6];
    inBattle = gp->inBattle != 0;
    if (animGroupBaseAsync("MOBJ_goal_pole", inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    if (animGroupBaseAsync("MOBJ_goal_hata", inBattle, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, "MOBJ_goal_pole");
    mobj = mobjNameToPtr(name);
    mobj->flags |= 0x84;
    mobj->position = (Vec){x, y, z};
    mobj->mainFunc = mobj_koopa_pole_evt;
    mobj->event = val;
    mobj->extraEvent = val2;
    mobj->flags |= 0x1c280000;
    mobj->flagVar = arg6;
    mobj->state = 0;
    if (evtGetValue(event, arg6)) {
        mobj->state = 99;
    }
    strcpy(mobj->linkedName, name);
    strcat(mobj->linkedName, "_h");
    mobjEntry(mobj->linkedName, "MOBJ_goal_hata");
    hata = mobjNameToPtr(mobj->linkedName);
    hata->position = (Vec){x, 180.0f + y, z};
    hata->mainFunc = NULL;
    hata->event = 0;
    hata->extraEvent = 0;
    hata->flagVar = 0;
    hata->state = 0;
    strcpy(hata->linkedName, name);
    if (hata->hitObj[0].hitObject) {
        FLD(u16, hata->hitObj[0].hitObject, 0) |= 1;
    }
    return EVT_RETURN_DONE;
}
#endif

#pragma force_active on
__declspec(section ".sdata") u32 gap_07_80410304_sdata[1] = {0};
#pragma force_active reset

#ifndef NONMATCHING
// ASM-STOPGAP: evt_mobj_entry (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off

asm USER_FUNC(evt_mobj_koopa_pole) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stfd f30, 0x50(r1)
	psq_st f30, 0x58(r1), 0, 0
	stfd f29, 0x40(r1)
	psq_st f29, 0x48(r1), 0, 0
	stmw r25, 0x24(r1)
	mr r25, r3
	lis r4, vec3_802c3dc8@ha
	lwz r26, 0x18(r3)
	addi r28, r4, vec3_802c3dc8@l
	lwz r4, 0x0(r26)
	bl evtGetValue
	lwz r4, 0x4(r26)
	mr r27, r3
	mr r3, r25
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x8(r26)
	mr r3, r25
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r26)
	mr r3, r25
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x10(r26)
	mr r3, r25
	bl evtGetValue
	lwz r4, 0x14(r26)
	mr r29, r3
	mr r3, r25
	bl evtGetValue
	lwz r4, gp(r0)
	mr r30, r3
	lwz r26, 0x18(r26)
	addi r3, r28, 0x3b8
	lwz r4, 0x14(r4)
	li r5, 0x0
	neg r0, r4
	or r0, r0, r4
	srwi r31, r0, 31
	mr r4, r31
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r4, r31
	addi r3, r28, 0x3c8
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @3
	li r3, 0x0
	b @2
	@3:
	mr r3, r27
	addi r4, r28, 0x3b8
	bl mobjEntry
	mr r3, r27
	bl mobjNameToPtr
	mr r31, r3
	lis r3, mobj_koopa_pole_evt@ha
	lwz r4, 0x0(r31)
	addi r5, r3, mobj_koopa_pole_evt@l
	li r0, 0x0
	mr r3, r25
	ori r6, r4, 0x84
	mr r4, r26
	stw r6, 0x0(r31)
	lwz r6, 0x3a0(r28)
	lwz r7, 0x3a4(r28)
	stw r6, 0x14(r1)
	lwz r6, 0x3a8(r28)
	stw r7, 0x18(r1)
	stfs f29, 0x14(r1)
	stw r6, 0x1c(r1)
	lwz r6, 0x14(r1)
	stfs f30, 0x18(r1)
	stfs f31, 0x1c(r1)
	lwz r7, 0x18(r1)
	stw r6, 0x38(r31)
	lwz r6, 0x1c(r1)
	stw r7, 0x3c(r31)
	stw r6, 0x40(r31)
	stw r5, 0x1d0(r31)
	stw r29, 0x1d4(r31)
	stw r30, 0x1d8(r31)
	lwz r5, 0x0(r31)
	oris r5, r5, 0x1c28
	stw r5, 0x0(r31)
	stw r26, 0x1e4(r31)
	stw r0, 0x1dc(r31)
	bl evtGetValue
	cmpwi r3, 0x0
	beq @4
	li r0, 0x63
	stw r0, 0x1dc(r31)
	@4:
	mr r4, r27
	addi r3, r31, 0x1b8
	bl strcpy
	addi r3, r31, 0x1b8
	la r4, str_8041A138(r0)
	bl strcat
	addi r3, r31, 0x1b8
	addi r4, r28, 0x3c8
	bl mobjEntry
	addi r3, r31, 0x1b8
	bl mobjNameToPtr
	lwz r4, 0x3ac(r28)
	mr r25, r3
	lfs f0, float_180_8041a13c(r0)
	li r0, 0x0
	stw r4, 0x8(r1)
	mr r4, r27
	lwz r5, 0x3b0(r28)
	fadds f0, f0, f30
	stfs f29, 0x8(r1)
	addi r3, r25, 0x1b8
	lwz r6, 0x3b4(r28)
	stw r5, 0xc(r1)
	lwz r5, 0x8(r1)
	stw r6, 0x10(r1)
	stfs f0, 0xc(r1)
	stfs f31, 0x10(r1)
	lwz r6, 0xc(r1)
	stw r5, 0x38(r25)
	lwz r5, 0x10(r1)
	stw r6, 0x3c(r25)
	stw r5, 0x40(r25)
	stw r0, 0x1d0(r25)
	stw r0, 0x1d4(r25)
	stw r0, 0x1d8(r25)
	stw r0, 0x1e4(r25)
	stw r0, 0x1dc(r25)
	bl strcpy
	lwz r3, 0x74(r25)
	cmplwi r3, 0x0
	beq @5
	lhz r0, 0x0(r3)
	ori r0, r0, 0x1
	sth r0, 0x0(r3)
	@5:
	li r3, 0x2
	@2:
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	psq_l f30, 0x58(r1), 0, 0
	lfd f30, 0x50(r1)
	psq_l f29, 0x48(r1), 0, 0
	lfd f29, 0x40(r1)
	lmw r25, 0x24(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm s32 mobj_koopa_pole_evt(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, fd_evt_mobj_negone_one_374@ha
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r29, r3
	addi r28, r4, fd_evt_mobj_negone_one_374@l
	bl marioGetPtr
	lwz r0, 0x1dc(r29)
	mr r31, r3
	li r30, 0x0
	cmpwi r0, 0x33
	beq @1
	bge @2
	cmpwi r0, 0xa
	beq @3
	bge @4
	cmpwi r0, 0x0
	beq @5
	b @6
	@4:
	cmpwi r0, 0x32
	bge @7
	cmpwi r0, 0xc
	bge @6
	b @8
	@2:
	cmpwi r0, 0x5d
	beq @9
	bge @10
	cmpwi r0, 0x5b
	beq @11
	bge @12
	cmpwi r0, 0x5a
	bge @13
	b @6
	@10:
	cmpwi r0, 0x5f
	beq @6
	bge @6
	b @14
	@5:
	lwz r3, 0x0(r29)
	rlwinm. r0, r3, 0, 28, 28
	beq @6
	lbz r0, 0x3c(r31)
	cmpwi r0, 0x2
	beq @15
	rlwinm r0, r3, 0, 29, 27
	stw r0, 0x0(r29)
	b @6
	@15:
	bl kpaGetLevel
	cmpwi r3, 0x2
	bge @16
	cmpwi r3, 0x0
	bge @17
	b @18
	@16:
	cmpwi r3, 0x4
	bge @18
	b @19
	@17:
	lfs f1, 0x90(r31)
	lfs f0, float_25_8041a140(r0)
	fcmpo cr0, f1, f0
	bge @20
	lwz r0, 0x0(r29)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r29)
	b @18
	@20:
	li r30, 0xa
	b @18
	@19:
	li r30, 0x32
	@18:
	cmpwi r30, 0x0
	beq @6
	li r27, 0x0
	li r28, 0x0
	b @21
	@22:
	bl npcGetWorkPtr
	lwz r0, 0xc(r3)
	add r3, r0, r28
	lwz r4, 0x0(r3)
	clrlwi. r0, r4, 31
	beq @23
	lwz r0, 0x1d4(r3)
	rlwinm. r0, r0, 0, 29, 29
	bne @23
	rlwinm. r0, r4, 0, 4, 4
	beq @23
	rlwinm. r0, r4, 0, 28, 28
	beq @23
	li r4, 0x20
	bl npcGroupDead
	@23:
	addi r28, r28, 0x340
	addi r27, r27, 0x1
	@21:
	bl npcGetWorkPtr
	lwz r0, 0x4(r3)
	cmpw r27, r0
	blt @22
	bl marioKeyOff
	lwz r4, 0x1e4(r29)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	li r0, 0x0
	sth r0, 0x78(r31)
	stw r30, 0x1dc(r29)
	b @6
	@3:
	bl marioGetPtr
	mr r30, r3
	li r31, 0x0
	bl kpaGetLevel
	cmpwi r3, 0x3
	bne @24
	li r3, 0x7d0
	bl kpaAddScore
	b @25
	@24:
	bl kpaGetLevel
	cmpwi r3, 0x2
	blt @26
	li r3, 0x3e8
	bl kpaAddScore
	b @25
	@26:
	lfs f1, 0x90(r30)
	lfs f0, float_170_8041a144(r0)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @27
	li r31, 0x3e8
	b @28
	@27:
	lfs f0, float_100_8041a148(r0)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @29
	li r31, 0x1f4
	b @28
	@29:
	lfs f0, float_50_8041a14c(r0)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @30
	li r31, 0xc8
	b @28
	@30:
	li r31, 0x64
	@28:
	mr r3, r31
	bl kpaAddScore
	@25:
	mr r3, r29
	addi r4, r28, 0x230
	bl mobjRunEvent
	stw r31, 0x9c(r3)
	lwz r3, 0x1dc(r29)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r29)
	b @6
	@8:
	lwz r3, 0x1cc(r29)
	bl evtCheckID
	cmpwi r3, 0x1
	beq @6
	li r0, 0x5a
	stw r0, 0x1dc(r29)
	b @6
	@7:
	bl marioGetPtr
	mr r30, r3
	bl kpaGetLevel
	cmpwi r3, 0x3
	bne @31
	li r3, 0x7d0
	bl kpaAddScore
	b @32
	@31:
	bl kpaGetLevel
	cmpwi r3, 0x2
	blt @33
	li r3, 0x3e8
	bl kpaAddScore
	b @32
	@33:
	lfs f1, 0x90(r30)
	lfs f0, float_170_8041a144(r0)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @34
	li r3, 0x3e8
	b @35
	@34:
	lfs f0, float_100_8041a148(r0)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @36
	li r3, 0x1f4
	b @35
	@36:
	lfs f0, float_50_8041a14c(r0)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @37
	li r3, 0xc8
	b @35
	@37:
	li r3, 0x64
	@35:
	bl kpaAddScore
	@32:
	mr r3, r29
	addi r4, r28, 0x690
	bl mobjRunEvent
	lwz r3, 0x1dc(r29)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r29)
	b @6
	@1:
	lwz r3, 0x1cc(r29)
	bl evtCheckID
	cmpwi r3, 0x1
	beq @6
	li r0, 0x5a
	stw r0, 0x1dc(r29)
	b @6
	@13:
	mr r3, r29
	addi r4, r28, 0x8ec
	bl mobjRunEvent
	lwz r3, 0x1dc(r29)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r29)
	b @6
	@11:
	lwz r3, 0x1cc(r29)
	bl evtCheckID
	cmpwi r3, 0x1
	beq @6
	li r0, 0x0
	stw r0, 0x1cc(r29)
	lwz r3, 0x1dc(r29)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r29)
	b @6
	@12:
	lwz r4, 0x1d8(r29)
	mr r3, r29
	bl mobjRunEvent
	lwz r3, 0x1dc(r29)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r29)
	b @6
	@9:
	lwz r3, 0x1cc(r29)
	bl evtCheckID
	cmpwi r3, 0x1
	beq @6
	li r0, 0x0
	stw r0, 0x1cc(r29)
	lwz r3, 0x1dc(r29)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r29)
	@14:
	lwz r4, 0x1d4(r29)
	mr r3, r29
	bl mobjRunEvent
	lwz r3, 0x1dc(r29)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r29)
	@6:
	lmw r27, 0xc(r1)
	li r3, 0x0
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm USER_FUNC(kpa_clear_jump_data) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	li r0, 0x0
	sth r0, 0x50(r3)
	li r3, 0x2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(kpa_disp_pole_init) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x14
	stw r0, 0x14(r1)
	bl _mapAlloc
	stw r3, psw(r0)
	li r0, 0x0
	lfs f0, float_0_8041a150(r0)
	stb r0, 0x0(r3)
	li r3, 0x2
	lwz r4, psw(r0)
	stfs f0, 0x10(r4)
	lwz r4, psw(r0)
	stfs f0, 0xc(r4)
	lwz r4, psw(r0)
	stfs f0, 0x8(r4)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(kpa_disp_pole_score_main) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stfd f30, 0x30(r1)
	psq_st f30, 0x38(r1), 0, 0
	stfd f29, 0x20(r1)
	psq_st f29, 0x28(r1), 0, 0
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	mr r30, r4
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x4(r31)
	mr r3, r29
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x8(r31)
	mr r3, r29
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0xc(r31)
	mr r3, r29
	bl evtGetFloat
	cmpwi r30, 0x0
	beq @1
	lwz r3, psw(r0)
	stfs f29, 0x8(r3)
	lwz r3, psw(r0)
	stfs f30, 0xc(r3)
	lwz r3, psw(r0)
	stfs f31, 0x10(r3)
	@1:
	lwz r3, psw(r0)
	lfs f0, float_230_8041a154(r0)
	lfs f2, 0xc(r3)
	fcmpo cr0, f2, f0
	bge @2
	fadds f0, f2, f1
	stfs f0, 0xc(r3)
	b @3
	@2:
	stfs f0, 0xc(r3)
	@3:
	lis r3, kpa_disp_pole_score@ha
	lfs f1, float_0_8041a150(r0)
	addi r5, r3, kpa_disp_pole_score@l
	li r4, 0x2
	li r3, 0x4
	li r6, 0x0
	bl dispEntry
	li r3, 0x0
	psq_l f31, 0x48(r1), 0, 0
	lfd f31, 0x40(r1)
	psq_l f30, 0x38(r1), 0, 0
	lfd f30, 0x30(r1)
	psq_l f29, 0x28(r1), 0, 0
	lfd f29, 0x20(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r0, 0x54(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void kpa_disp_pole_score(CameraId camId, void* param) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	lfs f3, float_300_8041a158(r0)
	stw r0, 0x74(r1)
	addi r3, r1, 0x3c
	lwz r4, psw(r0)
	lfs f1, 0x8(r4)
	lfs f2, 0xc(r4)
	bl PSMTXTrans
	lfs f1, float_0p5_8041a15c(r0)
	addi r3, r1, 0xc
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0x3c
	addi r4, r1, 0xc
	mr r5, r3
	bl PSMTXConcat
	bl FontDrawStart
	lwz r0, dat_8041a134(r0)
	addi r3, r1, 0x8
	stw r0, 0x8(r1)
	bl FontDrawColor
	lwz r4, psw(r0)
	addi r3, r1, 0x3c
	bl FontDrawStringMtx
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm USER_FUNC(kpa_score_to_str) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	lis r4, 0x1062
	lis r6, 0x51ec
	addi r0, r4, 0x4dd3
	lis r5, 0x6666
	mulhw r7, r0, r3
	li r4, 0x0
	addi r0, r5, 0x6667
	subi r6, r6, 0x7ae1
	cmpwi r4, 0x0
	srawi r8, r7, 6
	srawi r5, r7, 6
	srwi r7, r5, 31
	srwi r9, r8, 31
	add r5, r5, r7
	mulli r5, r5, 0x3e8
	add r8, r8, r9
	subf r9, r5, r3
	mulhw r3, r6, r9
	srawi r6, r3, 5
	srawi r3, r3, 5
	srwi r5, r3, 31
	srwi r7, r6, 31
	add r3, r3, r5
	mulli r3, r3, 0x64
	add r5, r6, r7
	mr r6, r5
	subf r9, r3, r9
	mulhw r0, r0, r9
	srawi r5, r0, 2
	srawi r0, r0, 2
	srwi r3, r0, 31
	srwi r7, r5, 31
	add r0, r0, r3
	mulli r0, r0, 0xa
	add r3, r5, r7
	mr r5, r3
	subf r0, r0, r9
	mr r3, r0
	bne @1
	cmpwi r8, 0x0
	beq @2
	@1:
	lwz r7, psw(r0)
	addi r0, r8, 0x30
	li r4, 0x1
	stb r0, 0x0(r7)
	@2:
	cmpwi r4, 0x0
	bne @3
	cmpwi r6, 0x0
	beq @4
	@3:
	lwz r7, psw(r0)
	addi r0, r6, 0x30
	stbx r0, r7, r4
	addi r4, r4, 0x1
	@4:
	cmpwi r4, 0x0
	bne @5
	cmpwi r5, 0x0
	beq @6
	@5:
	lwz r7, psw(r0)
	addi r0, r5, 0x30
	stbx r0, r7, r4
	addi r4, r4, 0x1
	@6:
	cmpwi r4, 0x0
	bne @7
	cmpwi r3, 0x0
	beq @8
	@7:
	lwz r7, psw(r0)
	addi r0, r3, 0x30
	stbx r0, r7, r4
	@8:
	lwz r4, psw(r0)
	li r0, 0x0
	li r3, 0x2
	stb r0, 0x4(r4)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(kpa_get_width) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	bl marioGetPtr
	lfs f0, 0x1b4(r3)
	mr r3, r30
	lwz r4, 0x0(r31)
	fctiwz f0, f0
	stfd f0, 0x8(r1)
	lwz r5, 0xc(r1)
	bl evtSetValue
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm static USER_FUNC(kpa_get_level) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	bl kpaGetLevel
	lwz r4, 0x0(r31)
	mr r5, r3
	mr r3, r30
	bl evtSetValue
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(kpa_get_hata_name) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r5, 0x174(r3)
	lwz r4, 0x18(r3)
	cmplwi r5, 0x0
	beq @1
	lwz r4, 0x0(r4)
	addi r5, r5, 0x1b8
	bl evtSetValue
	b @2
	@1:
	lwz r4, 0x0(r4)
	li r5, 0x0
	bl evtSetValue
	@2:
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(kpa_get_pole_name) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r5, 0x174(r3)
	lwz r4, 0x18(r3)
	cmplwi r5, 0x0
	beq @1
	lwz r4, 0x0(r4)
	addi r5, r5, 0x5
	bl evtSetValue
	b @2
	@1:
	lwz r4, 0x0(r4)
	li r5, 0x0
	bl evtSetValue
	@2:
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_koopa_fireber_dodai) {
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
	stmw r24, 0x40(r1)
	mr r24, r3
	lis r4, vec3_802c3dc8@ha
	lwz r25, 0x18(r3)
	addi r27, r4, vec3_802c3dc8@l
	lwz r4, 0x0(r25)
	bl evtGetValue
	lwz r4, 0x4(r25)
	mr r28, r3
	mr r3, r24
	bl evtGetValue
	lwz r4, 0x8(r25)
	mr r26, r3
	mr r3, r24
	bl evtGetFloat
	fmr f28, f1
	lwz r4, 0xc(r25)
	mr r3, r24
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x10(r25)
	mr r3, r24
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x14(r25)
	mr r3, r24
	bl evtGetValue
	lwz r4, 0x18(r25)
	mr r29, r3
	mr r3, r24
	bl evtGetFloat
	fmr f27, f1
	lwz r4, 0x1c(r25)
	mr r3, r24
	bl evtGetValue
	lwz r4, gp(r0)
	mr r30, r3
	lwz r25, 0x20(r25)
	addi r3, r27, 0x3d8
	lwz r4, 0x14(r4)
	li r5, 0x0
	neg r0, r4
	or r0, r0, r4
	srwi r31, r0, 31
	mr r4, r31
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r4, r31
	addi r3, r27, 0x3e8
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @3
	li r3, 0x0
	b @2
	@3:
	mr r3, r26
	addi r4, r27, 0x3d8
	bl mobjEntry
	mr r3, r26
	bl mobjNameToPtr
	mr r31, r3
	lis r3, mobj_koopa_fireber_dodai_evt@ha
	lwz r4, 0x0(r31)
	addi r0, r3, mobj_koopa_fireber_dodai_evt@l
	li r5, 0x0
	mr r3, r24
	ori r6, r4, 0x4
	mr r4, r25
	stw r6, 0x0(r31)
	lwz r6, 0x308(r27)
	lwz r7, 0x30c(r27)
	stw r6, 0x8(r1)
	lwz r6, 0x310(r27)
	stw r7, 0xc(r1)
	stfs f28, 0x8(r1)
	stw r6, 0x10(r1)
	lwz r6, 0x8(r1)
	stfs f29, 0xc(r1)
	stfs f31, 0x10(r1)
	lwz r7, 0xc(r1)
	stw r6, 0x38(r31)
	lwz r6, 0x10(r1)
	stw r7, 0x3c(r31)
	stw r6, 0x40(r31)
	stw r0, 0x1d0(r31)
	stw r30, 0x1d4(r31)
	stw r5, 0x1d8(r31)
	lwz r0, 0x0(r31)
	oris r0, r0, 0x3c00
	stw r0, 0x0(r31)
	stw r25, 0x1e4(r31)
	stw r5, 0x1dc(r31)
	bl evtGetValue
	cmpwi r3, 0x0
	beq @4
	li r0, 0x63
	stw r0, 0x1dc(r31)
	@4:
	lfs f0, float_0_8041a150(r0)
	fcmpu cr0, f0, f27
	bne @5
	lfs f27, float_1_8041a160(r0)
	@5:
	cmpwi r28, 0x0
	stw r29, 0x1a4(r31)
	beq @6
	fabs f1, f27
	b @7
	@6:
	fabs f0, f27
	fneg f1, f0
	@7:
	lfs f30, float_25_8041a140(r0)
	li r0, 0x0
	lfs f0, float_175_8041a164(r0)
	li r28, 0x0
	stfs f1, 0x1ac(r31)
	fadds f29, f30, f29
	fadds f27, f0, f31
	lfd f31, 0x400(r27)
	stw r0, 0x1b4(r31)
	lis r24, 0x4330
	b @8
	@9:
	mr r5, r26
	mr r6, r28
	addi r3, r1, 0x14
	la r4, str_8041A168(r0)
	crclr 6
	bl sprintf
	addi r3, r1, 0x14
	addi r4, r27, 0x3e8
	bl npcEntry
	addi r3, r1, 0x14
	bl npcNameToPtr
	mr r25, r3
	lwz r3, 0x0(r3)
	xoris r0, r28, 0x8000
	stw r24, 0x38(r1)
	addi r4, r27, 0x3f4
	li r5, 0x1
	stw r0, 0x3c(r1)
	oris r0, r3, 0x800
	stw r0, 0x0(r25)
	lfd f0, 0x38(r1)
	lhz r0, 0x31e(r25)
	fsubs f0, f0, f31
	ori r0, r0, 0xf
	sth r0, 0x31e(r25)
	fmadds f0, f30, f0, f29
	stfs f28, 0x8c(r25)
	stfs f0, 0x90(r25)
	stfs f27, 0x94(r25)
	lwz r3, 0x104(r25)
	bl animPoseSetAnim
	lwz r0, 0x0(r25)
	addi r28, r28, 0x1
	oris r0, r0, 0x4
	stw r0, 0x0(r25)
	@8:
	cmpw r28, r29
	blt @9
	li r3, 0x2
	@2:
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
	lmw r24, 0x40(r1)
	lwz r0, 0xb4(r1)
	mtlr r0
	addi r1, r1, 0xb0
	blr
}

asm s32 mobj_koopa_fireber_dodai_evt(MapObjectEntry* mobj) {
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
	stfd f26, 0xd0(r1)
	psq_st f26, 0xd8(r1), 0, 0
	stw r31, 0xcc(r1)
	stw r30, 0xc8(r1)
	stw r29, 0xc4(r1)
	stw r28, 0xc0(r1)
	mr r31, r3
	li r28, 0x0
	bl marioGetPtr
	lwz r0, 0x1dc(r31)
	cmpwi r0, 0xa
	bge @1
	lfs f1, 0x8c(r3)
	lfs f2, 0x90(r3)
	lfs f3, 0x38(r31)
	lfs f4, 0x3c(r31)
	bl distABf
	lfs f0, float_150_8041a170(r0)
	fcmpo cr0, f1, f0
	bge @2
	lwz r3, 0x1b4(r31)
	bl psndSFXChk
	cmpwi r3, 0x0
	beq @3
	addi r4, r31, 0x38
	li r3, 0x1cd
	bl psndSFXOn_3D
	stw r3, 0x1b4(r31)
	b @3
	@2:
	lwz r3, 0x1b4(r31)
	bl psndSFXChk
	cmpwi r3, 0x0
	bne @3
	lwz r3, 0x1b4(r31)
	bl psndSFXOff
	li r0, -0x1
	stw r0, 0x1b4(r31)
	@3:
	addi r3, r1, 0x78
	bl PSMTXIdentity
	lfs f1, 0x38(r31)
	addi r3, r1, 0x78
	lfs f2, 0x3c(r31)
	mr r4, r3
	lfs f0, 0x40(r31)
	fneg f1, f1
	fneg f2, f2
	fneg f3, f0
	bl PSMTXTransApply
	lfs f1, float_deg2rad_8041a174(r0)
	addi r3, r1, 0x48
	lfs f0, 0x1ac(r31)
	li r4, 0x5a
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r4, r1, 0x78
	addi r3, r1, 0x48
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x78
	lfs f1, 0x38(r31)
	lfs f2, 0x3c(r31)
	mr r4, r3
	lfs f3, 0x40(r31)
	bl PSMTXTransApply
	li r29, 0x0
	b @4
	@5:
	mr r6, r29
	addi r3, r1, 0x28
	addi r5, r31, 0x5
	la r4, str_8041A168(r0)
	crclr 6
	bl sprintf
	addi r3, r1, 0x28
	bl npcNameToPtr
	mr r0, r3
	addi r3, r1, 0x78
	mr r30, r0
	addi r4, r30, 0x8c
	mr r5, r4
	bl PSMTXMultVec
	addi r29, r29, 0x1
	@4:
	lwz r0, 0x1a4(r31)
	cmpw r29, r0
	blt @5
	@1:
	lwz r0, 0x1dc(r31)
	cmpwi r0, 0xb
	beq @6
	bge @7
	cmpwi r0, 0x0
	beq @8
	blt @9
	cmpwi r0, 0xa
	bge @10
	b @9
	@7:
	cmpwi r0, 0x63
	beq @11
	bge @9
	cmpwi r0, 0xd
	bge @9
	b @12
	@8:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @9
	bl kpaGetLevel
	cmpwi r3, 0x3
	beq @13
	bge @14
	cmpwi r3, 0x0
	bge @15
	b @14
	@15:
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x2000
	cmplwi r0, 0x0
	bne @14
	li r28, 0x1
	b @14
	@13:
	li r28, 0x1
	@14:
	cmpwi r28, 0x0
	bne @16
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	b @9
	@16:
	lwz r4, 0x1d4(r31)
	mr r3, r31
	bl mobjRunEvent
	lwz r4, 0x1e4(r31)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	lwz r3, 0x74(r31)
	cmplwi r3, 0x0
	beq @17
	lhz r0, 0x0(r3)
	ori r0, r0, 0x1
	sth r0, 0x0(r3)
	@17:
	lwz r0, 0x0(r31)
	ori r0, r0, 0x2
	stw r0, 0x0(r31)
	bl kpaMutekiCheck
	cmpwi r3, 0x0
	li r3, 0x190
	beq @18
	li r3, 0x1f4
	@18:
	bl kpaAddScore
	li r0, 0xa
	stw r0, 0x1dc(r31)
	b @9
	@10:
	addi r4, r31, 0x38
	li r3, 0x1b8
	bl psndSFXOn_3D
	lfs f3, float_12p5_8041a178(r0)
	li r3, 0x0
	lfs f1, 0x3c(r31)
	lfs f0, 0x40(r31)
	fadds f2, f3, f1
	lfs f1, 0x38(r31)
	fadds f3, f3, f0
	bl effMObjBrokenEntry
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @9
	@6:
	lfs f0, float_neg1000_8041a17c(r0)
	lis r3, double_to_int_802c41c8@ha
	lfs f27, float_200_8041a180(r0)
	li r28, 0x0
	stfs f0, 0x3c(r31)
	lis r30, 0x4330
	lfd f26, double_to_int_802c41c8@l(r3)
	lfs f28, float_75_8041a188(r0)
	lfs f31, float_6_8041a184(r0)
	lfs f30, float_4p8_8041a18c(r0)
	lfs f29, float_2_8041a190(r0)
	b @19
	@20:
	mr r6, r28
	addi r3, r1, 0x28
	addi r5, r31, 0x5
	la r4, str_8041A168(r0)
	crclr 6
	bl sprintf
	addi r3, r1, 0x28
	bl npcNameToPtr
	mr r29, r3
	li r0, 0x0
	stw r0, 0x18c(r3)
	li r3, 0x65
	stw r0, 0x188(r29)
	lwz r4, 0x8c(r29)
	lwz r0, 0x90(r29)
	stw r4, 0x158(r29)
	stw r0, 0x15c(r29)
	lwz r0, 0x94(r29)
	stw r0, 0x160(r29)
	bl irand
	xoris r0, r3, 0x8000
	stw r30, 0xa8(r1)
	li r3, 0x65
	stw r0, 0xac(r1)
	lfd f0, 0xa8(r1)
	fsubs f0, f0, f26
	fdivs f0, f0, f27
	stfs f0, 0x164(r29)
	bl irand
	xoris r0, r3, 0x8000
	stw r30, 0xb0(r1)
	addi r28, r28, 0x1
	stw r0, 0xb4(r1)
	lfd f0, 0xb0(r1)
	fsubs f0, f0, f26
	fdivs f0, f0, f28
	fsubs f0, f31, f0
	stfs f0, 0x168(r29)
	stfs f30, 0x16c(r29)
	stfs f29, 0x1c0(r29)
	lwz r0, 0x1d4(r29)
	ori r0, r0, 0x4
	stw r0, 0x1d4(r29)
	@19:
	lwz r0, 0x1a4(r31)
	cmpw r28, r0
	blt @20
	lwz r3, 0x1b4(r31)
	bl psndSFXChk
	cmpwi r3, 0x0
	bne @21
	lwz r3, 0x1b4(r31)
	bl psndSFXOff
	li r0, -0x1
	stw r0, 0x1b4(r31)
	@21:
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @9
	@12:
	lfs f29, float_0p04_8041a194(r0)
	li r29, 0x0
	lfs f30, float_3_8041a198(r0)
	lfs f31, float_0p2_8041a19c(r0)
	b @22
	@23:
	mr r6, r29
	addi r3, r1, 0x28
	addi r5, r31, 0x5
	la r4, str_8041A168(r0)
	crclr 6
	bl sprintf
	addi r3, r1, 0x28
	bl npcNameToPtr
	lfs f1, 0x1b4(r3)
	mr r30, r3
	lfs f0, 0x164(r3)
	fadds f0, f1, f0
	stfs f0, 0x1b4(r3)
	lfs f1, 0x90(r3)
	lfs f0, 0x168(r3)
	fadds f0, f1, f0
	stfs f0, 0x90(r3)
	lfs f1, 0x1bc(r3)
	lfs f0, 0x16c(r3)
	fadds f0, f1, f0
	stfs f0, 0x1bc(r3)
	lfs f0, 0xe0(r3)
	fadds f0, f0, f29
	stfs f0, 0xe0(r3)
	lfs f0, 0xe0(r3)
	fcmpo cr0, f0, f30
	ble @24
	stfs f30, 0xe0(r30)
	@24:
	lfs f0, 0xe0(r30)
	addi r29, r29, 0x1
	stfs f0, 0xe4(r30)
	stfs f0, 0xe8(r30)
	lfs f0, 0x168(r30)
	fsubs f0, f0, f31
	stfs f0, 0x168(r30)
	@22:
	lwz r0, 0x1a4(r31)
	cmpw r29, r0
	blt @23
	lfs f1, 0x1c0(r30)
	lfs f0, 0x1a0(r30)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @9
	li r0, 0x63
	stw r0, 0x1dc(r31)
	b @9
	@11:
	li r28, 0x0
	b @25
	@26:
	mr r6, r28
	addi r3, r1, 0x8
	addi r5, r31, 0x5
	la r4, str_8041A168(r0)
	crclr 6
	bl sprintf
	addi r3, r1, 0x8
	bl npcNameToPtr
	bl npcDelete
	addi r28, r28, 0x1
	@25:
	lwz r0, 0x1a4(r31)
	cmpw r28, r0
	blt @26
	addi r3, r31, 0x5
	bl mobjDelete
	@9:
	li r3, 0x0
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
	psq_l f26, 0xd8(r1), 0, 0
	lfd f26, 0xd0(r1)
	lwz r31, 0xcc(r1)
	lwz r30, 0xc8(r1)
	lwz r29, 0xc4(r1)
	lwz r0, 0x134(r1)
	lwz r28, 0xc0(r1)
	mtlr r0
	addi r1, r1, 0x130
	blr
}

asm USER_FUNC(evt_mobj_koopa_sango) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x38(r1)
	stfd f30, 0x30(r1)
	stfd f29, 0x28(r1)
	stw r31, 0x24(r1)
	stw r30, 0x20(r1)
	stw r29, 0x1c(r1)
	stw r28, 0x18(r1)
	mr r28, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r31, r3
	mr r3, r28
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x8(r29)
	mr r3, r28
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r29)
	mr r3, r28
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x10(r29)
	mr r3, r28
	bl evtGetValue
	lwz r4, gp(r0)
	lis r5, str_802C41D0@ha
	addi r0, r5, str_802C41D0@l
	mr r30, r3
	lwz r4, 0x14(r4)
	mr r3, r0
	lwz r29, 0x14(r29)
	li r5, 0x0
	neg r0, r4
	or r0, r0, r4
	srwi r4, r0, 31
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	lis r4, str_802C41D0@ha
	mr r3, r31
	addi r4, r4, str_802C41D0@l
	bl mobjEntry
	mr r3, r31
	bl mobjNameToPtr
	mr r31, r3
	lis r4, vec3_802c40c4@ha
	lwz r0, 0x0(r3)
	lis r3, mobj_koopa_sango_evt@ha
	addi r8, r4, vec3_802c40c4@l
	li r5, 0x0
	ori r4, r0, 0x84
	addi r0, r3, mobj_koopa_sango_evt@l
	stw r4, 0x0(r31)
	mr r3, r28
	mr r4, r29
	lwz r6, 0x0(r8)
	lwz r7, 0x4(r8)
	stw r6, 0x8(r1)
	lwz r6, 0x8(r8)
	stw r7, 0xc(r1)
	stfs f29, 0x8(r1)
	stw r6, 0x10(r1)
	lwz r6, 0x8(r1)
	stfs f30, 0xc(r1)
	stfs f31, 0x10(r1)
	lwz r7, 0xc(r1)
	stw r6, 0x38(r31)
	lwz r6, 0x10(r1)
	stw r7, 0x3c(r31)
	stw r6, 0x40(r31)
	stw r0, 0x1d0(r31)
	stw r30, 0x1d4(r31)
	stw r5, 0x1d8(r31)
	lwz r0, 0x0(r31)
	oris r0, r0, 0x3c00
	stw r0, 0x0(r31)
	stw r29, 0x1e4(r31)
	stw r5, 0x1dc(r31)
	bl evtGetValue
	cmpwi r3, 0x0
	beq @3
	li r0, 0x63
	stw r0, 0x1dc(r31)
	@3:
	li r3, 0x2
	@2:
	lwz r0, 0x44(r1)
	lfd f31, 0x38(r1)
	lfd f30, 0x30(r1)
	lfd f29, 0x28(r1)
	lwz r31, 0x24(r1)
	lwz r30, 0x20(r1)
	lwz r29, 0x1c(r1)
	lwz r28, 0x18(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 mobj_koopa_sango_evt(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	mr r31, r3
	stw r30, 0x28(r1)
	li r30, 0x0
	lwz r0, 0x1dc(r3)
	cmpwi r0, 0x14
	beq @1
	bge @2
	cmpwi r0, 0xa
	beq @3
	bge @4
	cmpwi r0, 0x0
	beq @5
	b @4
	@2:
	cmpwi r0, 0x62
	beq @6
	bge @7
	cmpwi r0, 0x1e
	beq @8
	b @4
	@7:
	cmpwi r0, 0x64
	bge @4
	b @9
	@5:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @10
	bl kpaGetLevel
	cmpwi r3, 0x3
	beq @11
	bge @12
	cmpwi r3, 0x0
	bge @13
	b @12
	@13:
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x2000
	cmplwi r0, 0x0
	bne @12
	li r30, 0x1
	b @12
	@11:
	li r30, 0x1
	@12:
	cmpwi r30, 0x0
	bne @14
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	b @10
	@14:
	lwz r4, 0x1d4(r31)
	mr r3, r31
	bl mobjRunEvent
	lwz r4, 0x1e4(r31)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x400
	cmplwi r0, 0x0
	bne @15
	lwz r3, 0x74(r31)
	bl npcKoopaModeMobjBoundDeadCheck
	@15:
	lwz r3, 0x74(r31)
	cmplwi r3, 0x0
	beq @16
	lhz r0, 0x0(r3)
	ori r0, r0, 0x1
	sth r0, 0x0(r3)
	@16:
	lwz r0, 0x0(r31)
	ori r0, r0, 0x2
	stw r0, 0x0(r31)
	bl kpaMutekiCheck
	cmpwi r3, 0x0
	li r3, 0x190
	beq @17
	li r3, 0x1f4
	@17:
	bl kpaAddScore
	li r0, 0xa
	stw r0, 0x1dc(r31)
	b @10
	@3:
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x2000
	cmplwi r0, 0x0
	bne @18
	addi r4, r31, 0x38
	li r3, 0xb67
	bl psndSFXOn_3D
	@18:
	la r3, evt_fire(r0)
	li r4, 0x0
	li r5, 0x0
	bl evtEntry
	lfs f2, float_1024_8041a1a0(r0)
	li r0, 0x5a
	lfs f0, 0x38(r31)
	lfs f1, float_10_8041a1a4(r0)
	fmuls f0, f2, f0
	fctiwz f0, f0
	stfd f0, 0x8(r1)
	lwz r4, 0xc(r1)
	subis r4, r4, 0xdb6
	addi r4, r4, 0x7a80
	stw r4, 0x9c(r3)
	lfs f0, 0x3c(r31)
	fmuls f0, f2, f0
	fctiwz f0, f0
	stfd f0, 0x10(r1)
	lwz r4, 0x14(r1)
	subis r4, r4, 0xdb6
	addi r4, r4, 0x7a80
	stw r4, 0xa0(r3)
	lfs f0, 0x40(r31)
	fadds f0, f1, f0
	fmuls f0, f2, f0
	fctiwz f0, f0
	stfd f0, 0x18(r1)
	lwz r4, 0x1c(r1)
	subis r4, r4, 0xdb6
	addi r4, r4, 0x7a80
	stw r4, 0xa4(r3)
	stw r0, 0xa8(r3)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @10
	@1:
	la r3, evt_fire(r0)
	li r4, 0x0
	li r5, 0x0
	bl evtEntry
	lfs f2, float_10_8041a1a4(r0)
	li r0, 0x50
	lfs f0, 0x38(r31)
	lfs f3, float_1024_8041a1a0(r0)
	fadds f0, f2, f0
	lfs f1, float_30_8041a1a8(r0)
	fmuls f0, f3, f0
	fctiwz f0, f0
	stfd f0, 0x18(r1)
	lwz r4, 0x1c(r1)
	subis r4, r4, 0xdb6
	addi r4, r4, 0x7a80
	stw r4, 0x9c(r3)
	lfs f0, 0x3c(r31)
	fadds f0, f1, f0
	fmuls f0, f3, f0
	fctiwz f0, f0
	stfd f0, 0x10(r1)
	lwz r4, 0x14(r1)
	subis r4, r4, 0xdb6
	addi r4, r4, 0x7a80
	stw r4, 0xa0(r3)
	lfs f0, 0x40(r31)
	fadds f0, f2, f0
	fmuls f0, f3, f0
	fctiwz f0, f0
	stfd f0, 0x8(r1)
	lwz r4, 0xc(r1)
	subis r4, r4, 0xdb6
	addi r4, r4, 0x7a80
	stw r4, 0xa4(r3)
	stw r0, 0xa8(r3)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @10
	@8:
	la r3, evt_fire(r0)
	li r4, 0x0
	li r5, 0x0
	bl evtEntry
	lfs f0, 0x38(r31)
	li r0, 0x46
	lfs f2, float_10_8041a1a4(r0)
	lfs f3, float_1024_8041a1a0(r0)
	fsubs f0, f0, f2
	lfs f1, float_60_8041a1ac(r0)
	fmuls f0, f3, f0
	fctiwz f0, f0
	stfd f0, 0x18(r1)
	lwz r4, 0x1c(r1)
	subis r4, r4, 0xdb6
	addi r4, r4, 0x7a80
	stw r4, 0x9c(r3)
	lfs f0, 0x3c(r31)
	fadds f0, f1, f0
	fmuls f0, f3, f0
	fctiwz f0, f0
	stfd f0, 0x10(r1)
	lwz r4, 0x14(r1)
	subis r4, r4, 0xdb6
	addi r4, r4, 0x7a80
	stw r4, 0xa0(r3)
	lfs f0, 0x40(r31)
	fadds f0, f2, f0
	fmuls f0, f3, f0
	fctiwz f0, f0
	stfd f0, 0x8(r1)
	lwz r4, 0xc(r1)
	subis r4, r4, 0xdb6
	addi r4, r4, 0x7a80
	stw r4, 0xa4(r3)
	stw r0, 0xa8(r3)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @10
	@6:
	lfs f2, float_10_8041a1a4(r0)
	li r3, 0x7
	lfs f0, 0x40(r31)
	lfs f1, 0x38(r31)
	fadds f3, f2, f0
	lfs f2, 0x3c(r31)
	bl effMObjBrokenEntry
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @10
	@9:
	addi r3, r31, 0x5
	bl mobjDelete
	b @10
	@4:
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	@10:
	lwz r0, 0x34(r1)
	li r3, 0x0
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm USER_FUNC(fire_func) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stfd f30, 0x30(r1)
	psq_st f30, 0x38(r1), 0, 0
	stfd f29, 0x20(r1)
	psq_st f29, 0x28(r1), 0, 0
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	mr r30, r4
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x4(r31)
	mr r3, r29
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x8(r31)
	mr r3, r29
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0xc(r31)
	mr r3, r29
	bl evtGetValue
	cmpwi r30, 0x0
	mr r31, r3
	beq @1
	li r3, 0xa
	bl irand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xc(r1)
	lis r4, double_to_int_802c41c8@ha
	lfd f6, double_to_int_802c41c8@l(r4)
	fmr f1, f31
	stw r0, 0x8(r1)
	fmr f2, f30
	lfs f4, float_10_8041a1a4(r0)
	fmr f3, f29
	lfd f5, 0x8(r1)
	lfs f0, float_0p8_8041a1b0(r0)
	mr r4, r31
	fsubs f5, f5, f6
	li r3, 0x5
	fdivs f4, f5, f4
	fadds f4, f0, f4
	bl effFireEntry
	stw r3, 0x78(r29)
	@1:
	lfs f5, 0x7c(r29)
	lfs f4, float_1_8041a160(r0)
	lfs f6, 0x80(r29)
	fsubs f3, f4, f5
	lfs f2, float_0p125_8041a1b4(r0)
	lwz r5, 0x78(r29)
	fsubs f1, f4, f6
	lfs f0, float_0p99_8041a1b8(r0)
	fmadds f5, f3, f2, f5
	lwz r3, 0xc(r5)
	fmadds f6, f1, f2, f6
	stfs f5, 0x78(r3)
	fcmpo cr0, f5, f0
	lwz r3, 0xc(r5)
	stfs f6, 0x7c(r3)
	cror eq, gt, eq
	bne @2
	lwz r4, 0xc(r5)
	li r3, 0x2
	stfs f4, 0x78(r4)
	lwz r4, 0xc(r5)
	stfs f4, 0x7c(r4)
	b @3
	@2:
	stfs f5, 0x7c(r29)
	li r3, 0x0
	stfs f6, 0x80(r29)
	@3:
	psq_l f31, 0x48(r1), 0, 0
	lfd f31, 0x40(r1)
	psq_l f30, 0x38(r1), 0, 0
	lfd f30, 0x30(r1)
	psq_l f29, 0x28(r1), 0, 0
	lfd f29, 0x20(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r0, 0x54(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm USER_FUNC(evt_mobj_koopa_dokan) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	lis r4, vec3_802c3dc8@ha
	stw r0, 0x54(r1)
	stfd f31, 0x48(r1)
	stfd f30, 0x40(r1)
	stfd f29, 0x38(r1)
	stmw r25, 0x1c(r1)
	addi r29, r4, vec3_802c3dc8@l
	mr r27, r3
	lwz r28, 0x18(r3)
	lwz r4, 0x0(r28)
	bl evtGetValue
	lwz r4, 0x4(r28)
	mr r31, r3
	mr r3, r27
	bl evtGetValue
	lwz r4, 0x8(r28)
	mr r26, r3
	mr r3, r27
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0xc(r28)
	mr r3, r27
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x10(r28)
	mr r3, r27
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x14(r28)
	mr r3, r27
	bl evtGetValue
	lwz r4, gp(r0)
	cmpwi r31, 0x1
	lwz r28, 0x18(r28)
	mr r30, r3
	lwz r3, 0x14(r4)
	neg r0, r3
	or r0, r0, r3
	srwi r4, r0, 31
	beq @1
	bge @2
	cmpwi r31, 0x0
	bge @3
	b @4
	@2:
	cmpwi r31, 0x3
	bge @4
	b @5
	@3:
	addi r25, r29, 0x414
	b @4
	@1:
	addi r25, r29, 0x428
	b @4
	@5:
	addi r25, r29, 0x43c
	@4:
	mr r3, r25
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @6
	li r3, 0x0
	b @7
	@6:
	mr r3, r26
	mr r4, r25
	bl mobjEntry
	mr r3, r26
	bl mobjNameToPtr
	mr r31, r3
	lis r4, mobj_koopa_dokan_evt@ha
	lwz r5, 0x0(r3)
	addi r4, r4, mobj_koopa_dokan_evt@l
	li r0, 0x0
	ori r5, r5, 0x6
	stw r5, 0x0(r3)
	lwz r5, 0x2f0(r29)
	lwz r6, 0x2f4(r29)
	stw r5, 0x8(r1)
	lwz r5, 0x2f8(r29)
	stw r6, 0xc(r1)
	stfs f29, 0x8(r1)
	stw r5, 0x10(r1)
	lwz r5, 0x8(r1)
	stfs f30, 0xc(r1)
	stfs f31, 0x10(r1)
	lwz r6, 0xc(r1)
	stw r5, 0x38(r3)
	lwz r5, 0x10(r1)
	stw r6, 0x3c(r3)
	stw r5, 0x40(r3)
	stw r4, 0x1d0(r3)
	stw r30, 0x1d4(r3)
	stw r0, 0x1d8(r3)
	bl mobjCalcMtx
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r5, 0x0(r31)
	li r0, 0x0
	mr r3, r27
	mr r4, r28
	oris r5, r5, 0x3c00
	stw r5, 0x0(r31)
	stw r28, 0x1e4(r31)
	stw r0, 0x1dc(r31)
	bl evtGetValue
	cmpwi r3, 0x0
	beq @8
	li r0, 0x63
	stw r0, 0x1dc(r31)
	@8:
	li r3, 0x2
	@7:
	lfd f31, 0x48(r1)
	lfd f30, 0x40(r1)
	lfd f29, 0x38(r1)
	lmw r25, 0x1c(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm s32 mobj_koopa_dokan_evt(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	stw r30, 0x8(r1)
	li r30, 0x0
	lwz r0, 0x1dc(r3)
	cmpwi r0, 0xa
	beq @1
	bge @2
	cmpwi r0, 0x0
	beq @3
	b @4
	@2:
	cmpwi r0, 0x63
	beq @5
	b @4
	@3:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @4
	bl kpaGetLevel
	cmpwi r3, 0x3
	beq @6
	bge @7
	cmpwi r3, 0x0
	beq @7
	bge @8
	b @7
	@8:
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x2000
	cmplwi r0, 0x0
	bne @7
	li r30, 0x1
	b @7
	@6:
	li r30, 0x1
	@7:
	cmpwi r30, 0x0
	bne @9
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	b @4
	@9:
	lwz r4, 0x1d4(r31)
	mr r3, r31
	bl mobjRunEvent
	lwz r4, 0x1e4(r31)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x400
	cmplwi r0, 0x0
	bne @10
	lwz r3, 0x74(r31)
	bl npcKoopaModeMobjBoundDeadCheck
	@10:
	lwz r3, 0x74(r31)
	cmplwi r3, 0x0
	beq @11
	lhz r0, 0x0(r3)
	ori r0, r0, 0x1
	sth r0, 0x0(r3)
	@11:
	lwz r0, 0x0(r31)
	ori r0, r0, 0x2
	stw r0, 0x0(r31)
	bl kpaMutekiCheck
	cmpwi r3, 0x0
	li r3, 0x190
	beq @12
	li r3, 0x1f4
	@12:
	bl kpaAddScore
	li r0, 0xa
	stw r0, 0x1dc(r31)
	b @4
	@1:
	lis r4, str_802C41DC@ha
	addi r3, r31, 0x15
	addi r4, r4, str_802C41DC@l
	bl strcmp
	cmpwi r3, 0x0
	bne @13
	lfs f3, float_25_8041a140(r0)
	li r3, 0x6
	lfs f1, 0x3c(r31)
	lfs f0, 0x40(r31)
	fadds f2, f3, f1
	lfs f1, 0x38(r31)
	fadds f3, f3, f0
	bl effMObjBrokenEntry
	b @14
	@13:
	lis r4, str_802C41F0@ha
	addi r3, r31, 0x15
	addi r4, r4, str_802C41F0@l
	bl strcmp
	cmpwi r3, 0x0
	bne @15
	lfs f3, float_25_8041a140(r0)
	li r3, 0x6
	lfs f1, 0x3c(r31)
	lfs f0, 0x40(r31)
	fadds f2, f3, f1
	lfs f4, float_7p5_8041a1bc(r0)
	fadds f3, f3, f0
	lfs f1, 0x38(r31)
	fadds f2, f4, f2
	bl effMObjBrokenEntry
	b @14
	@15:
	lfs f1, 0x38(r31)
	li r3, 0x6
	lfs f3, float_25_8041a140(r0)
	lfs f2, 0x3c(r31)
	lfs f0, 0x40(r31)
	fsubs f1, f1, f3
	fadds f2, f3, f2
	fadds f3, f3, f0
	bl effMObjBrokenEntry
	@14:
	addi r4, r31, 0x38
	li r3, 0x834
	bl psndSFXOn_3D
	li r0, 0x63
	stw r0, 0x1dc(r31)
	b @4
	@5:
	addi r3, r31, 0x5
	bl mobjDelete
	@4:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_koopa_blk) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x28(r1)
	stfd f30, 0x20(r1)
	stfd f29, 0x18(r1)
	stw r31, 0x14(r1)
	stw r30, 0x10(r1)
	stw r29, 0xc(r1)
	stw r28, 0x8(r1)
	mr r28, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lwz r4, 0x4(r30)
	mr r29, r3
	mr r3, r28
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r30)
	mr r3, r28
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r30)
	mr r3, r28
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x14(r30)
	mr r3, r28
	bl evtGetValue
	lwz r4, gp(r0)
	lis r5, str_802C4218@ha
	addi r0, r5, str_802C4218@l
	mr r31, r3
	lwz r4, 0x14(r4)
	mr r3, r0
	lwz r30, 0x18(r30)
	li r5, 0x0
	neg r0, r4
	or r0, r0, r4
	srwi r4, r0, 31
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	lis r4, str_802C4218@ha
	mr r3, r29
	addi r4, r4, str_802C4218@l
	bl mobjEntry
	mr r3, r29
	bl mobjNameToPtr
	fmr f1, f31
	mr r28, r3
	fmr f2, f30
	mr r3, r29
	fmr f3, f29
	bl mobjSetPosition
	lis r3, mobj_koopa_blk@ha
	li r0, 0x0
	addi r4, r3, mobj_koopa_blk@l
	mr r3, r28
	stw r4, 0x1d0(r28)
	stw r31, 0x1d4(r28)
	lwz r4, 0x0(r28)
	ori r4, r4, 0x4
	stw r4, 0x0(r28)
	lwz r4, 0x0(r28)
	oris r4, r4, 0x3c00
	stw r4, 0x0(r28)
	stw r30, 0x1e4(r28)
	stw r0, 0x1dc(r28)
	bl mobjCalcMtx
	lwz r3, 0x70(r28)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r3, 0x2
	@2:
	lwz r0, 0x34(r1)
	lfd f31, 0x28(r1)
	lfd f30, 0x20(r1)
	lfd f29, 0x18(r1)
	lwz r31, 0x14(r1)
	lwz r30, 0x10(r1)
	lwz r29, 0xc(r1)
	lwz r28, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 mobj_koopa_blk(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	li r31, 0x0
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r0, 0x1dc(r3)
	cmpwi r0, 0xa
	beq @1
	bge @2
	cmpwi r0, 0x0
	beq @3
	b @4
	@2:
	cmpwi r0, 0x63
	beq @5
	b @4
	@3:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 28, 28
	beq @4
	bl kpaGetLevel
	cmpwi r3, 0x3
	beq @6
	bge @7
	b @7
	@6:
	li r31, 0x1
	@7:
	cmpwi r31, 0x0
	bne @8
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r30)
	b @4
	@8:
	lwz r4, 0x1d4(r30)
	mr r3, r30
	bl mobjRunEvent
	lwz r4, 0x1e4(r30)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	lwz r3, 0x1e0(r30)
	subis r0, r3, 0x400
	cmplwi r0, 0x0
	bne @9
	lwz r3, 0x74(r30)
	bl npcKoopaModeMobjBoundDeadCheck
	@9:
	lwz r3, 0x74(r30)
	cmplwi r3, 0x0
	beq @10
	lhz r0, 0x0(r3)
	ori r0, r0, 0x1
	sth r0, 0x0(r3)
	@10:
	lwz r3, 0x0(r30)
	li r0, 0xa
	ori r3, r3, 0x2
	stw r3, 0x0(r30)
	stw r0, 0x1dc(r30)
	b @4
	@1:
	addi r4, r30, 0x38
	li r3, 0x1b8
	bl psndSFXOn_3D
	lfs f3, float_12p5_8041a178(r0)
	li r3, 0x2
	lfs f1, 0x3c(r30)
	lfs f0, 0x40(r30)
	fadds f2, f3, f1
	lfs f1, 0x38(r30)
	fadds f3, f3, f0
	bl effMObjBrokenEntry
	li r0, 0x63
	stw r0, 0x1dc(r30)
	@5:
	addi r3, r30, 0x5
	bl mobjDelete
	@4:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_koopa_hidden_blk) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x38(r1)
	stfd f30, 0x30(r1)
	stfd f29, 0x28(r1)
	stmw r26, 0x10(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lwz r4, 0x4(r30)
	mr r27, r3
	mr r3, r29
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r30)
	mr r3, r29
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r30)
	mr r3, r29
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x10(r30)
	mr r3, r29
	bl evtGetValue
	lwz r4, 0x18(r30)
	mr r31, r3
	mr r3, r29
	bl evtGetValue
	lwz r5, gp(r0)
	lis r4, str_802C4224@ha
	addi r0, r4, str_802C4224@l
	mr r28, r3
	lwz r4, 0x14(r5)
	mr r26, r0
	mr r3, r0
	lwz r30, 0x1c(r30)
	neg r0, r4
	li r5, 0x0
	or r0, r0, r4
	srwi r4, r0, 31
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r3, r27
	mr r4, r26
	bl mobjEntry
	mr r3, r27
	bl mobjNameToPtr
	fmr f1, f31
	mr r26, r3
	fmr f2, f30
	mr r3, r27
	fmr f3, f29
	bl mobjSetPosition
	lwz r0, 0x0(r26)
	mr r3, r26
	li r4, 0x1
	ori r0, r0, 0x800
	stw r0, 0x0(r26)
	bl mobjHitEntry
	lis r3, mobj_koopa_badgeblk@ha
	li r0, 0x0
	addi r4, r3, mobj_koopa_badgeblk@l
	mr r3, r26
	stw r4, 0x1d0(r26)
	stw r28, 0x1d4(r26)
	lwz r4, 0x0(r26)
	ori r4, r4, 0x4
	stw r4, 0x0(r26)
	lwz r4, 0x0(r26)
	oris r4, r4, 0x3c00
	stw r4, 0x0(r26)
	stw r30, 0x1e4(r26)
	stw r0, 0x1dc(r26)
	stw r31, 0x1a0(r26)
	bl mobjCalcMtx
	lwz r3, 0x70(r26)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	mr r3, r29
	mr r4, r30
	bl evtGetValue
	cmpwi r3, 0x0
	beq @3
	li r0, 0x5a
	la r4, str_8041A1C0(r0)
	stw r0, 0x1dc(r26)
	li r5, 0x1
	lwz r3, 0x70(r26)
	bl animPoseSetAnim
	@3:
	li r3, 0x2
	@2:
	lfd f31, 0x38(r1)
	lfd f30, 0x30(r1)
	lfd f29, 0x28(r1)
	lmw r26, 0x10(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm USER_FUNC(evt_mobj_koopa_badgeblk) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x38(r1)
	stfd f30, 0x30(r1)
	stfd f29, 0x28(r1)
	stmw r26, 0x10(r1)
	mr r31, r3
	lwz r28, 0x18(r3)
	lwz r4, 0x0(r28)
	bl evtGetValue
	lwz r4, 0x4(r28)
	mr r27, r3
	mr r3, r31
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r28)
	mr r3, r31
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r28)
	mr r3, r31
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x10(r28)
	mr r3, r31
	bl evtGetValue
	lwz r4, 0x14(r28)
	mr r29, r3
	mr r3, r31
	bl evtGetValue
	lwz r5, gp(r0)
	lis r4, str_802C423C@ha
	addi r0, r4, str_802C423C@l
	mr r30, r3
	lwz r4, 0x14(r5)
	mr r26, r0
	mr r3, r0
	lwz r28, 0x18(r28)
	neg r0, r4
	li r5, 0x0
	or r0, r0, r4
	srwi r4, r0, 31
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r3, r27
	mr r4, r26
	bl mobjEntry
	mr r3, r27
	bl mobjNameToPtr
	fmr f1, f31
	mr r26, r3
	fmr f2, f30
	mr r3, r27
	fmr f3, f29
	bl mobjSetPosition
	lis r3, mobj_koopa_badgeblk@ha
	li r0, 0x0
	addi r4, r3, mobj_koopa_badgeblk@l
	mr r3, r26
	stw r4, 0x1d0(r26)
	stw r30, 0x1d4(r26)
	lwz r4, 0x0(r26)
	ori r4, r4, 0x4
	stw r4, 0x0(r26)
	lwz r4, 0x0(r26)
	oris r4, r4, 0x3c00
	stw r4, 0x0(r26)
	stw r28, 0x1e4(r26)
	stw r0, 0x1dc(r26)
	stw r29, 0x1a0(r26)
	bl mobjCalcMtx
	lwz r3, 0x70(r26)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	mr r3, r31
	mr r4, r28
	bl evtGetValue
	cmpwi r3, 0x0
	beq @3
	li r0, 0x5a
	la r4, str_8041A1C0(r0)
	stw r0, 0x1dc(r26)
	li r5, 0x1
	lwz r3, 0x70(r26)
	bl animPoseSetAnim
	@3:
	li r3, 0x2
	@2:
	lfd f31, 0x38(r1)
	lfd f30, 0x30(r1)
	lfd f29, 0x28(r1)
	lmw r26, 0x10(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 mobj_koopa_badgeblk(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	stw r30, 0x8(r1)
	bl marioGetPtr
	lwz r0, 0x1dc(r31)
	li r30, 0x0
	cmpwi r0, 0x5a
	beq @1
	bge @2
	cmpwi r0, 0x1
	beq @3
	bge @4
	cmpwi r0, 0x0
	bge @5
	b @4
	@2:
	cmpwi r0, 0x63
	beq @6
	bge @4
	cmpwi r0, 0x5c
	bge @4
	b @7
	@5:
	lwz r4, 0x0(r31)
	rlwinm. r0, r4, 0, 28, 28
	beq @4
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x400
	cmplwi r0, 0x0
	beq @8
	rlwinm r0, r4, 0, 29, 27
	stw r0, 0x0(r31)
	b @4
	@8:
	rlwinm. r0, r4, 0, 20, 20
	beq @9
	mr r3, r31
	li r4, 0x0
	bl mobjHitEntry
	@9:
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r4, 0x1d4(r31)
	cmplwi r4, 0x0
	beq @10
	mr r3, r31
	bl mobjRunEvent
	b @11
	@10:
	lwz r4, 0x1a0(r31)
	cmpwi r4, 0x59
	bne @12
	lfs f2, float_12p5_8041a178(r0)
	addi r3, r31, 0x5
	lfs f0, 0x3c(r31)
	li r5, 0x4
	lfs f1, 0x38(r31)
	li r6, -0x1
	fadds f2, f2, f0
	lfs f3, 0x40(r31)
	la r7, kpa_powerup_evt(r0)
	bl itemEntry
	addi r3, r31, 0x5
	bl itemNameToPtr
	li r4, 0x10
	mr r30, r3
	bl itemStatusOn
	mr r3, r30
	li r4, 0x14
	bl itemFlagOn
	li r0, 0x2710
	li r5, 0x0
	stw r0, 0x7c(r30)
	li r0, 0x5a
	lfs f1, float_0p45_8041a1c4(r0)
	addi r4, r31, 0x38
	stw r5, 0x78(r30)
	li r3, 0x836
	lfs f0, float_0p7_8041a1c8(r0)
	stfs f1, 0x80(r30)
	lfs f1, float_500_8041a1cc(r0)
	stfs f0, 0x84(r30)
	lfs f0, float_120_8041a1d0(r0)
	stw r5, 0x88(r30)
	stfs f1, 0x58(r30)
	stfs f0, 0x50(r30)
	stw r0, 0x54(r30)
	bl psndSFXOn_3D
	b @11
	@12:
	li r3, 0x1
	bl kpaAddCoin
	lfs f1, 0x38(r31)
	li r3, 0x0
	lfs f2, 0x3c(r31)
	li r4, 0x79
	lfs f3, 0x40(r31)
	li r5, 0xf
	li r6, -0x1
	li r7, 0x0
	bl itemEntry
	lwz r4, 0x1e4(r31)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	addi r4, r31, 0x38
	li r3, 0x5b
	bl psndSFXOn_3D
	@11:
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x400
	cmplwi r0, 0x0
	bne @13
	lwz r3, 0x74(r31)
	bl npcKoopaModeMobjBoundDeadCheck
	@13:
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @4
	@3:
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @4
	lwz r3, 0x70(r31)
	la r4, str_8041A1C0(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r5, 0x0(r31)
	lis r3, str_802C4218@ha
	addi r4, r3, str_802C4218@l
	li r0, 0x5a
	rlwinm r5, r5, 0, 29, 27
	addi r3, r31, 0x15
	stw r5, 0x0(r31)
	stw r0, 0x1dc(r31)
	bl strcpy
	b @4
	@1:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @4
	bl kpaGetLevel
	cmpwi r3, 0x3
	beq @14
	bge @15
	b @15
	@14:
	li r30, 0x1
	@15:
	cmpwi r30, 0x0
	bne @16
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	b @4
	@16:
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x400
	cmplwi r0, 0x0
	bne @17
	lwz r3, 0x74(r31)
	bl npcKoopaModeMobjBoundDeadCheck
	@17:
	lwz r3, 0x74(r31)
	cmplwi r3, 0x0
	beq @18
	lhz r0, 0x0(r3)
	ori r0, r0, 0x1
	sth r0, 0x0(r3)
	@18:
	lwz r0, 0x0(r31)
	ori r0, r0, 0x2
	stw r0, 0x0(r31)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @4
	@7:
	addi r4, r31, 0x38
	li r3, 0x1b8
	bl psndSFXOn_3D
	lfs f3, float_12p5_8041a178(r0)
	li r3, 0x2
	lfs f1, 0x3c(r31)
	lfs f0, 0x40(r31)
	fadds f2, f3, f1
	lfs f1, 0x38(r31)
	fadds f3, f3, f0
	bl effMObjBrokenEntry
	li r0, 0x63
	stw r0, 0x1dc(r31)
	b @4
	@6:
	addi r3, r31, 0x5
	bl mobjDelete
	@4:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_koopa_brick) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	lis r4, vec3_802c3dc8@ha
	stw r0, 0x44(r1)
	stfd f31, 0x38(r1)
	stfd f30, 0x30(r1)
	stfd f29, 0x28(r1)
	stmw r25, 0xc(r1)
	addi r27, r4, vec3_802c3dc8@l
	mr r30, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r26, r3
	mr r3, r30
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r29)
	mr r3, r30
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r29)
	mr r3, r30
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x10(r29)
	mr r3, r30
	bl evtGetValue
	lwz r25, 0x14(r29)
	mr r28, r3
	lwz r4, 0x18(r29)
	mr r3, r30
	bl evtGetValue
	lwz r4, gp(r0)
	cmpwi r25, 0x2
	lwz r31, 0x1c(r29)
	mr r29, r3
	lwz r3, 0x14(r4)
	neg r0, r3
	or r0, r0, r3
	srwi r4, r0, 31
	beq @1
	bge @2
	cmpwi r25, 0x0
	beq @3
	bge @4
	b @2
	b @2
	@3:
	addi r25, r27, 0x488
	b @5
	@4:
	addi r25, r27, 0x49c
	b @5
	@1:
	addi r25, r27, 0x4ac
	b @5
	@2:
	addi r25, r27, 0x4c0
	@5:
	mr r3, r25
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @6
	li r3, 0x0
	b @7
	@6:
	mr r3, r26
	mr r4, r25
	bl mobjEntry
	mr r3, r26
	bl mobjNameToPtr
	fmr f1, f31
	mr r25, r3
	fmr f2, f30
	mr r3, r26
	fmr f3, f29
	bl mobjSetPosition
	lis r3, mobj_koopa_brickblk@ha
	li r0, 0x0
	addi r4, r3, mobj_koopa_brickblk@l
	mr r3, r25
	stw r4, 0x1d0(r25)
	stw r29, 0x1d4(r25)
	lwz r4, 0x0(r25)
	ori r4, r4, 0x4
	stw r4, 0x0(r25)
	lwz r4, 0x0(r25)
	oris r4, r4, 0x3c00
	stw r4, 0x0(r25)
	stw r31, 0x1e4(r25)
	stw r0, 0x1dc(r25)
	stw r28, 0x1a0(r25)
	bl mobjCalcMtx
	lwz r3, 0x70(r25)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	mr r3, r30
	mr r4, r31
	bl evtGetValue
	cmpwi r3, 0x0
	beq @8
	lwz r3, 0x70(r25)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x63
	stw r0, 0x1dc(r25)
	@8:
	li r3, 0x2
	@7:
	lfd f31, 0x38(r1)
	lfd f30, 0x30(r1)
	lfd f29, 0x28(r1)
	lmw r25, 0xc(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 mobj_koopa_brickblk(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r3
	lis r3, vec3_802c3dc8@ha
	stw r30, 0x18(r1)
	addi r30, r3, vec3_802c3dc8@l
	stw r29, 0x14(r1)
	li r29, 0x0
	lwz r0, 0x1dc(r31)
	cmpwi r0, 0x14
	beq @1
	bge @2
	cmpwi r0, 0xa
	beq @3
	bge @4
	cmpwi r0, 0x0
	beq @5
	b @4
	@2:
	cmpwi r0, 0x63
	beq @6
	bge @4
	cmpwi r0, 0x16
	bge @4
	b @7
	@5:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @4
	bl kpaGetLevel
	cmpwi r3, 0x2
	beq @8
	bge @9
	cmpwi r3, 0x0
	beq @10
	bge @11
	b @12
	@9:
	cmpwi r3, 0x4
	bge @12
	b @13
	@10:
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x2000
	cmplwi r0, 0x0
	bne @12
	li r29, 0x1
	b @12
	@11:
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x2000
	cmplwi r0, 0x0
	beq @14
	subis r0, r3, 0x400
	cmplwi r0, 0x0
	bne @12
	@14:
	li r29, 0x1
	b @12
	@8:
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x2000
	cmplwi r0, 0x0
	beq @15
	subis r0, r3, 0x1000
	cmplwi r0, 0x0
	beq @15
	subis r0, r3, 0x400
	cmplwi r0, 0x0
	bne @12
	@15:
	li r29, 0x1
	b @12
	@13:
	li r29, 0x1
	@12:
	cmpwi r29, 0x0
	bne @16
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x400
	cmplwi r0, 0x0
	bne @17
	lwz r3, 0x74(r31)
	bl npcKoopaModeMobjBoundDeadCheck
	li r0, 0x14
	stw r0, 0x1dc(r31)
	b @4
	@17:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	b @4
	@16:
	lwz r4, 0x1d4(r31)
	mr r3, r31
	bl mobjRunEvent
	lwz r4, 0x1e4(r31)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x400
	cmplwi r0, 0x0
	bne @18
	lwz r3, 0x74(r31)
	bl npcKoopaModeMobjBoundDeadCheck
	@18:
	lwz r3, 0x74(r31)
	cmplwi r3, 0x0
	beq @19
	lhz r0, 0x0(r3)
	ori r0, r0, 0x1
	sth r0, 0x0(r3)
	@19:
	lwz r0, 0x0(r31)
	ori r0, r0, 0x2
	stw r0, 0x0(r31)
	bl kpaMutekiCheck
	cmpwi r3, 0x0
	li r3, 0x190
	beq @20
	li r3, 0x1f4
	@20:
	bl kpaAddScore
	li r0, 0xa
	stw r0, 0x1dc(r31)
	b @4
	@3:
	addi r4, r31, 0x38
	li r3, 0x1b8
	bl psndSFXOn_3D
	addi r3, r31, 0x15
	addi r4, r30, 0x488
	bl strcmp
	cmpwi r3, 0x0
	bne @21
	lfs f3, float_12p5_8041a178(r0)
	li r3, 0x0
	lfs f1, 0x3c(r31)
	lfs f0, 0x40(r31)
	fadds f2, f3, f1
	lfs f1, 0x38(r31)
	fadds f3, f3, f0
	bl effMObjBrokenEntry
	b @22
	@21:
	addi r3, r31, 0x15
	addi r4, r30, 0x49c
	bl strcmp
	cmpwi r3, 0x0
	bne @23
	lfs f3, float_12p5_8041a178(r0)
	li r3, 0x1
	lfs f1, 0x3c(r31)
	lfs f0, 0x40(r31)
	fadds f2, f3, f1
	lfs f1, 0x38(r31)
	fadds f3, f3, f0
	bl effMObjBrokenEntry
	b @22
	@23:
	addi r3, r31, 0x15
	addi r4, r30, 0x4ac
	bl strcmp
	cmpwi r3, 0x0
	bne @24
	lfs f3, float_25_8041a140(r0)
	li r3, 0x3
	lfs f1, 0x3c(r31)
	lfs f0, 0x40(r31)
	fadds f2, f3, f1
	lfs f1, 0x38(r31)
	fadds f3, f3, f0
	bl effMObjBrokenEntry
	b @22
	@24:
	addi r3, r31, 0x15
	addi r4, r30, 0x4c0
	bl strcmp
	cmpwi r3, 0x0
	bne @22
	lfs f3, float_25_8041a140(r0)
	li r3, 0x4
	lfs f1, 0x3c(r31)
	lfs f0, 0x40(r31)
	fadds f2, f3, f1
	lfs f1, 0x38(r31)
	fadds f3, f3, f0
	bl effMObjBrokenEntry
	@22:
	li r0, 0x63
	stw r0, 0x1dc(r31)
	b @4
	@1:
	addi r4, r31, 0x38
	li r3, 0x1b7
	bl psndSFXOn_3D
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x15
	stw r0, 0x1dc(r31)
	b @4
	@7:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	bne @25
	li r0, 0x0
	stw r0, 0x1dc(r31)
	b @4
	@25:
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @4
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x0
	stw r0, 0x1dc(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	b @4
	@6:
	addi r3, r31, 0x5
	bl mobjDelete
	@4:
	lwz r0, 0x24(r1)
	li r3, 0x0
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm USER_FUNC(evt_mobj_koopa_stone_blk) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x48(r1)
	stfd f30, 0x40(r1)
	stfd f29, 0x38(r1)
	stmw r27, 0x24(r1)
	mr r27, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r28, r3
	mr r3, r27
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x8(r29)
	mr r3, r27
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r29)
	mr r3, r27
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x10(r29)
	mr r3, r27
	bl evtGetValue
	lwz r30, 0x14(r29)
	mr r31, r3
	lwz r4, 0x18(r29)
	mr r3, r27
	bl evtGetValue
	lwz r4, gp(r0)
	mr r29, r3
	li r5, 0x0
	lwz r4, 0x14(r4)
	neg r0, r4
	or r0, r0, r4
	srwi r4, r0, 31
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r3, r28
	mr r4, r29
	bl mobjEntry
	mr r3, r28
	bl mobjNameToPtr
	lwz r0, 0x0(r3)
	lis r6, vec3_802c40ac@ha
	lis r5, mobj_koopa_stone_blk_evt@ha
	li r4, 0x0
	ori r0, r0, 0x4
	addi r8, r6, vec3_802c40ac@l
	stw r0, 0x0(r3)
	addi r5, r5, mobj_koopa_stone_blk_evt@l
	li r0, 0x63
	lwz r6, 0x0(r8)
	lwz r7, 0x4(r8)
	stw r6, 0x8(r1)
	lwz r6, 0x8(r8)
	stw r7, 0xc(r1)
	stfs f29, 0x8(r1)
	stw r6, 0x10(r1)
	lwz r6, 0x8(r1)
	stfs f30, 0xc(r1)
	stfs f31, 0x10(r1)
	lwz r7, 0xc(r1)
	stw r6, 0x38(r3)
	lwz r6, 0x10(r1)
	stw r7, 0x3c(r3)
	stw r6, 0x40(r3)
	stw r5, 0x1d0(r3)
	stw r31, 0x1d4(r3)
	stw r4, 0x1d8(r3)
	stw r30, 0x1e4(r3)
	stw r0, 0x1dc(r3)
	li r3, 0x2
	@2:
	lfd f31, 0x48(r1)
	lfd f30, 0x40(r1)
	lfd f29, 0x38(r1)
	lmw r27, 0x24(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm s32 mobj_koopa_stone_blk_evt(MapObjectEntry* mobj) {
	nofralloc
	li r3, 0x0
	blr
}

asm USER_FUNC(evt_mobj_koopa_ojama_blk) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x48(r1)
	stfd f30, 0x40(r1)
	stfd f29, 0x38(r1)
	stmw r27, 0x24(r1)
	mr r28, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r27, r3
	mr r3, r28
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x8(r31)
	mr r3, r28
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r31)
	mr r3, r28
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x10(r31)
	mr r3, r28
	bl evtGetValue
	lwz r29, 0x14(r31)
	mr r30, r3
	lwz r4, 0x18(r31)
	mr r3, r28
	bl evtGetValue
	lwz r4, gp(r0)
	mr r31, r3
	li r5, 0x0
	lwz r4, 0x14(r4)
	neg r0, r4
	or r0, r0, r4
	srwi r4, r0, 31
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r3, r27
	mr r4, r31
	bl mobjEntry
	mr r3, r27
	bl mobjNameToPtr
	mr r31, r3
	lis r4, vec3_802c40a0@ha
	lwz r0, 0x0(r3)
	lis r3, mobj_koopa_ojama_blk_evt@ha
	addi r8, r4, vec3_802c40a0@l
	li r5, 0x0
	ori r4, r0, 0x4
	addi r0, r3, mobj_koopa_ojama_blk_evt@l
	stw r4, 0x0(r31)
	mr r3, r28
	mr r4, r29
	lwz r6, 0x0(r8)
	lwz r7, 0x4(r8)
	stw r6, 0x8(r1)
	lwz r6, 0x8(r8)
	stw r7, 0xc(r1)
	stfs f29, 0x8(r1)
	stw r6, 0x10(r1)
	lwz r6, 0x8(r1)
	stfs f30, 0xc(r1)
	stfs f31, 0x10(r1)
	lwz r7, 0xc(r1)
	stw r6, 0x38(r31)
	lwz r6, 0x10(r1)
	stw r7, 0x3c(r31)
	stw r6, 0x40(r31)
	stw r0, 0x1d0(r31)
	stw r30, 0x1d4(r31)
	stw r5, 0x1d8(r31)
	lwz r0, 0x0(r31)
	oris r0, r0, 0x3c00
	stw r0, 0x0(r31)
	stw r29, 0x1e4(r31)
	stw r5, 0x1dc(r31)
	bl evtGetValue
	cmpwi r3, 0x0
	beq @3
	li r0, 0x63
	stw r0, 0x1dc(r31)
	@3:
	li r3, 0x2
	@2:
	lfd f31, 0x48(r1)
	lfd f30, 0x40(r1)
	lfd f29, 0x38(r1)
	lmw r27, 0x24(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm s32 mobj_koopa_ojama_blk_evt(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	stw r30, 0x8(r1)
	li r30, 0x0
	lwz r0, 0x1dc(r3)
	cmpwi r0, 0xa
	beq @1
	bge @2
	cmpwi r0, 0x0
	beq @3
	b @4
	@2:
	cmpwi r0, 0x63
	beq @5
	b @4
	@3:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @4
	bl kpaGetLevel
	cmpwi r3, 0x2
	beq @6
	bge @7
	cmpwi r3, 0x0
	bge @8
	b @9
	@7:
	cmpwi r3, 0x4
	bge @9
	b @10
	@8:
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x2000
	cmplwi r0, 0x0
	beq @11
	subis r0, r3, 0x400
	cmplwi r0, 0x0
	bne @9
	@11:
	li r30, 0x1
	b @9
	@6:
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x2000
	cmplwi r0, 0x0
	beq @12
	subis r0, r3, 0x1000
	cmplwi r0, 0x0
	beq @12
	subis r0, r3, 0x400
	cmplwi r0, 0x0
	bne @9
	@12:
	li r30, 0x1
	b @9
	@10:
	li r30, 0x1
	@9:
	cmpwi r30, 0x0
	bne @13
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	b @4
	@13:
	lwz r4, 0x1d4(r31)
	mr r3, r31
	bl mobjRunEvent
	lwz r4, 0x1e4(r31)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x400
	cmplwi r0, 0x0
	bne @14
	lwz r3, 0x74(r31)
	bl npcKoopaModeMobjBoundDeadCheck
	@14:
	lwz r3, 0x74(r31)
	cmplwi r3, 0x0
	beq @15
	lhz r0, 0x0(r3)
	ori r0, r0, 0x1
	sth r0, 0x0(r3)
	@15:
	lwz r0, 0x0(r31)
	ori r0, r0, 0x2
	stw r0, 0x0(r31)
	bl kpaMutekiCheck
	cmpwi r3, 0x0
	li r3, 0x190
	beq @16
	li r3, 0x1f4
	@16:
	bl kpaAddScore
	li r0, 0xa
	stw r0, 0x1dc(r31)
	b @4
	@1:
	addi r4, r31, 0x38
	li r3, 0x1c4
	bl psndSFXOn_3D
	lfs f3, float_25_8041a140(r0)
	li r3, 0x5
	lfs f1, 0x3c(r31)
	lfs f0, 0x40(r31)
	fadds f2, f3, f1
	lfs f1, 0x38(r31)
	fadds f3, f3, f0
	bl effMObjBrokenEntry
	lfs f2, float_25_8041a140(r0)
	addi r3, r31, 0x5
	lfs f0, 0x3c(r31)
	li r4, 0x59
	lfs f1, 0x38(r31)
	li r5, 0x4
	fadds f2, f2, f0
	lfs f3, 0x40(r31)
	li r6, -0x1
	la r7, kpa_powerup_evt(r0)
	bl itemEntry
	mr. r30, r3
	beq @17
	li r4, 0x10
	bl itemStatusOn
	mr r3, r30
	li r4, 0x14
	bl itemFlagOn
	li r0, 0x2710
	li r5, 0x0
	stw r0, 0x7c(r30)
	li r0, 0x5a
	lfs f1, float_0p45_8041a1c4(r0)
	addi r4, r31, 0x38
	stw r5, 0x78(r30)
	li r3, 0x836
	lfs f0, float_0p7_8041a1c8(r0)
	stfs f1, 0x80(r30)
	lfs f1, float_500_8041a1cc(r0)
	stfs f0, 0x84(r30)
	lfs f0, float_120_8041a1d0(r0)
	stw r5, 0x88(r30)
	stfs f1, 0x58(r30)
	stfs f0, 0x50(r30)
	stw r0, 0x54(r30)
	bl psndSFXOn_3D
	@17:
	li r0, 0x63
	stw r0, 0x1dc(r31)
	b @4
	@5:
	addi r3, r31, 0x5
	bl mobjDelete
	@4:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(kpa_powerup) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetFloat
	stfs f1, 0x8(r1)
	mr r3, r30
	lwz r4, 0x4(r31)
	bl evtGetFloat
	stfs f1, 0xc(r1)
	mr r3, r30
	lwz r4, 0x8(r31)
	bl evtGetFloat
	stfs f1, 0x10(r1)
	addi r4, r1, 0x8
	li r3, 0x1f4
	bl kpaAddScorePos
	bl kpaGetLevel
	cmpwi r3, 0x3
	bne @1
	li r3, 0x3e8
	bl kpaAddScore
	@1:
	bl kpaPowUp
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm USER_FUNC(evt_mobj_kururing_floor) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stfd f30, 0x50(r1)
	psq_st f30, 0x58(r1), 0, 0
	stfd f29, 0x40(r1)
	psq_st f29, 0x48(r1), 0, 0
	stmw r26, 0x28(r1)
	mr r26, r3
	lis r4, vec3_802c3dc8@ha
	lwz r28, 0x18(r3)
	addi r31, r4, vec3_802c3dc8@l
	lwz r4, 0x0(r28)
	bl evtGetValue
	lwz r4, 0x4(r28)
	mr r27, r3
	mr r3, r26
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x8(r28)
	mr r3, r26
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r28)
	mr r3, r26
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x10(r28)
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x14(r28)
	mr r30, r3
	mr r3, r26
	bl evtGetValue
	lwz r4, gp(r0)
	addi r26, r31, 0x4fc
	lwz r29, 0x18(r28)
	mr r3, r26
	lwz r4, 0x14(r4)
	li r5, 0x0
	neg r0, r4
	or r0, r0, r4
	srwi r4, r0, 31
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r3, r27
	mr r4, r26
	bl mobjEntry
	mr r3, r27
	bl mobjNameToPtr
	lwz r0, 0x288(r31)
	lis r4, mobj_kururing_floor@ha
	lfs f0, float_0p1_8041a1d4(r0)
	addi r4, r4, mobj_kururing_floor@l
	stw r0, 0x14(r1)
	li r0, 0x0
	lwz r5, 0x28c(r31)
	fadds f0, f0, f30
	lwz r6, 0x290(r31)
	mr r28, r3
	stw r5, 0x18(r1)
	stfs f29, 0x14(r1)
	lwz r5, 0x14(r1)
	stw r6, 0x1c(r1)
	stfs f0, 0x18(r1)
	stfs f31, 0x1c(r1)
	lwz r6, 0x18(r1)
	stw r5, 0x38(r3)
	lwz r5, 0x1c(r1)
	stw r6, 0x3c(r3)
	stw r5, 0x40(r3)
	stw r4, 0x1d0(r3)
	stw r29, 0x1e4(r3)
	stw r0, 0x1dc(r3)
	lwz r0, 0x0(r3)
	oris r0, r0, 0x101
	stw r0, 0x0(r3)
	lwz r0, 0x0(r3)
	ori r0, r0, 0x2
	stw r0, 0x0(r3)
	bl mobjCalcMtx
	lwz r0, 0x298(r31)
	mr r3, r28
	lwz r5, 0x294(r31)
	stw r0, 0xc(r1)
	lfs f0, 0x188(r28)
	lwz r4, 0x29c(r31)
	stfs f0, 0xc(r1)
	stw r5, 0x184(r28)
	lwz r0, 0xc(r1)
	stw r5, 0x8(r1)
	stw r0, 0x188(r28)
	stw r4, 0x10(r1)
	stw r4, 0x18c(r28)
	bl mobjCalcMtx2
	mr r3, r30
	lis r4, 0x40
	bl mapGrpFlagOn
	lwz r3, 0x70(r28)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r3, 0x70(r28)
	bl animPoseWorldPositionEvalOn
	li r3, 0x2
	@2:
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	psq_l f30, 0x58(r1), 0, 0
	lfd f30, 0x50(r1)
	psq_l f29, 0x48(r1), 0, 0
	lfd f29, 0x40(r1)
	lmw r26, 0x28(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm s32 mobj_kururing_floor(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x20(r1)
	psq_st f31, 0x28(r1), 0, 0
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r31, r3
	bl marioGetPtr
	mr r29, r3
	bl marioGetPartyId
	bl partyGetPtr
	lwz r0, 0x1dc(r31)
	mr r30, r3
	cmpwi r0, 0xa
	beq @1
	bge @2
	cmpwi r0, 0x1
	beq @3
	bge @4
	cmpwi r0, 0x0
	bge @5
	b @4
	@2:
	cmpwi r0, 0xc
	beq @6
	bge @4
	b @7
	@5:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @4
	lfs f1, 0x8c(r29)
	lfs f2, 0x94(r29)
	lfs f3, 0x38(r31)
	lfs f4, 0x40(r31)
	bl distABf
	lfs f3, 0x90(r29)
	fmr f31, f1
	lfs f2, 0x3c(r31)
	lfs f0, float_10_8041a1a4(r0)
	fsubs f2, f3, f2
	fabs f1, f2
	fcmpo cr0, f1, f0
	ble @8
	lfs f31, float_1E05_8041a1d8(r0)
	@8:
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x100
	cmplwi r0, 0x0
	bne @9
	bl pouchGetJumpLv
	cmpwi r3, 0x2
	bge @10
	li r28, 0x0
	b @9
	@10:
	lfs f0, float_60_8041a1ac(r0)
	fcmpo cr0, f31, f0
	bge @11
	li r28, 0x2
	b @9
	@11:
	lfs f0, float_100_8041a148(r0)
	fcmpo cr0, f31, f0
	bge @12
	li r28, 0x1
	b @9
	@12:
	li r28, 0x0
	@9:
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x1
	cmplwi r0, 0x0
	bne @13
	li r28, 0x1
	@13:
	cmpwi r28, 0x0
	bne @14
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	b @4
	@14:
	lfs f1, 0x38(r31)
	lfs f2, float_30_8041a1a8(r0)
	lfs f4, 0x8c(r29)
	fsubs f0, f1, f2
	lfs f5, 0x94(r29)
	lfs f3, 0x40(r31)
	fcmpo cr0, f0, f4
	cror eq, lt, eq
	bne @15
	fadds f0, f1, f2
	fcmpo cr0, f4, f0
	cror eq, lt, eq
	bne @15
	fsubs f0, f3, f2
	fcmpo cr0, f0, f5
	cror eq, lt, eq
	bne @15
	fadds f0, f3, f2
	fcmpo cr0, f5, f0
	cror eq, lt, eq
	bne @15
	li r0, 0x1
	b @16
	@15:
	li r0, 0x0
	@16:
	cmpwi r0, 0x0
	beq @17
	li r28, 0x1
	@17:
	cmplwi r30, 0x0
	beq @18
	lfs f2, float_30_8041a1a8(r0)
	lfs f4, 0x58(r30)
	fsubs f0, f1, f2
	lfs f5, 0x60(r30)
	fcmpo cr0, f0, f4
	cror eq, lt, eq
	bne @19
	fadds f0, f1, f2
	fcmpo cr0, f4, f0
	cror eq, lt, eq
	bne @19
	fsubs f0, f3, f2
	fcmpo cr0, f0, f5
	cror eq, lt, eq
	bne @19
	fadds f0, f3, f2
	fcmpo cr0, f5, f0
	cror eq, lt, eq
	bne @19
	li r0, 0x1
	b @20
	@19:
	li r0, 0x0
	@20:
	cmpwi r0, 0x0
	beq @18
	li r28, 0x1
	@18:
	lfs f2, 0x3c(r31)
	lfs f4, float_42p42_8041a1dc(r0)
	bl itemHitCheck
	cmplwi r3, 0x0
	beq @21
	li r28, 0x1
	@21:
	lfs f1, 0x38(r31)
	lfs f2, 0x3c(r31)
	lfs f3, 0x40(r31)
	lfs f4, float_42p42_8041a1dc(r0)
	bl npcNearDistCheck
	cmplwi r3, 0x0
	beq @22
	li r28, 0x1
	@22:
	cmpwi r28, 0x0
	bne @23
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	b @4
	@23:
	cmpwi r28, 0x1
	bne @24
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	addi r4, r31, 0x38
	li r3, 0x1ee
	li r5, 0xff
	li r6, 0xff
	li r7, 0x64
	li r8, 0x10
	bl psndSFXOnEx_3D
	li r0, 0xa
	stw r0, 0x1dc(r31)
	b @25
	@24:
	cmpwi r28, 0x2
	bne @25
	lwz r3, 0x70(r31)
	la r4, str_8041A11C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	addi r4, r31, 0x38
	li r3, 0x1ef
	bl psndSFXOn_3D
	li r0, 0x1
	addi r3, r31, 0x5
	stw r0, 0x1dc(r31)
	bl itemNameToPtr
	cmplwi r3, 0x0
	beq @26
	lhz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	bne @25
	@26:
	lfs f2, float_30_8041a1a8(r0)
	addi r3, r31, 0x5
	lfs f0, 0x3c(r31)
	li r4, 0x7d
	lfs f1, 0x38(r31)
	li r5, 0x4
	fadds f2, f2, f0
	lfs f3, 0x40(r31)
	lwz r6, 0x1e4(r31)
	li r7, 0x0
	bl itemEntry
	cmplwi r3, 0x0
	beq @25
	addi r3, r31, 0x5
	bl itemNameToPtr
	mr r30, r3
	li r4, 0x10
	bl itemFlagOn
	lfs f0, float_0p6_8041a1e0(r0)
	li r0, 0x5
	lfs f1, float_1_8041a160(r0)
	stfs f0, 0x80(r30)
	lfs f0, float_300_8041a158(r0)
	stfs f1, 0x84(r30)
	stw r0, 0x88(r30)
	stfs f0, 0x58(r30)
	@25:
	bl animGetPtr
	lwz r0, 0x70(r31)
	lis r4, kururing_capture@ha
	lwz r8, 0x10(r3)
	addi r5, r4, kururing_capture@l
	mulli r7, r0, 0x170
	lfs f1, float_0_8041a150(r0)
	mr r6, r31
	li r3, 0x2
	lwzx r0, r8, r7
	li r4, 0x0
	ori r0, r0, 0x10
	stwx r0, r8, r7
	lwz r0, 0x0(r31)
	ori r0, r0, 0x400
	stw r0, 0x0(r31)
	bl dispEntry
	b @4
	@3:
	bl animGetPtr
	lwz r0, 0x70(r31)
	lis r4, kururing_capture@ha
	lwz r8, 0x10(r3)
	addi r5, r4, kururing_capture@l
	mulli r7, r0, 0x170
	lfs f1, float_0_8041a150(r0)
	mr r6, r31
	li r3, 0x2
	lwzx r0, r8, r7
	li r4, 0x0
	ori r0, r0, 0x10
	stwx r0, r8, r7
	lwz r0, 0x0(r31)
	ori r0, r0, 0x400
	stw r0, 0x0(r31)
	bl dispEntry
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @4
	bl animGetPtr
	lwz r0, 0x70(r31)
	la r4, str_8041A12C(r0)
	lwz r6, 0x10(r3)
	li r5, 0x1
	mulli r3, r0, 0x170
	lwzx r0, r6, r3
	rlwinm r0, r0, 0, 28, 26
	stwx r0, r6, r3
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 22, 20
	stw r0, 0x0(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	lwz r3, 0x70(r31)
	bl animPoseSetAnim
	addi r4, r31, 0x38
	li r3, 0x1f0
	bl psndSFXOn_3D
	li r0, 0x0
	stw r0, 0x1dc(r31)
	b @4
	@1:
	bl animGetPtr
	lwz r0, 0x70(r31)
	lis r4, kururing_capture@ha
	lwz r8, 0x10(r3)
	addi r5, r4, kururing_capture@l
	mulli r7, r0, 0x170
	lfs f1, float_0_8041a150(r0)
	mr r6, r31
	li r3, 0x2
	lwzx r0, r8, r7
	li r4, 0x0
	ori r0, r0, 0x10
	stwx r0, r8, r7
	lwz r0, 0x0(r31)
	ori r0, r0, 0x400
	stw r0, 0x0(r31)
	bl dispEntry
	lwz r3, 0x70(r31)
	bl animPoseGetAnimPosePtr
	lwz r3, 0x15c(r3)
	lwz r30, 0x0(r3)
	bl marioGetPtr
	lfs f2, 0x38(r31)
	lfs f1, float_30_8041a1a8(r0)
	lfs f4, 0x8c(r3)
	fsubs f0, f2, f1
	lfs f5, 0x94(r3)
	lfs f3, 0x40(r31)
	fcmpo cr0, f0, f4
	cror eq, lt, eq
	bne @27
	fadds f0, f2, f1
	fcmpo cr0, f4, f0
	cror eq, lt, eq
	bne @27
	fsubs f0, f3, f1
	fcmpo cr0, f0, f5
	cror eq, lt, eq
	bne @27
	fadds f0, f3, f1
	fcmpo cr0, f5, f0
	cror eq, lt, eq
	bne @27
	li r0, 0x1
	b @28
	@27:
	li r0, 0x0
	@28:
	cmpwi r0, 0x0
	beq @29
	lfs f0, 0x10(r30)
	stfs f0, 0x90(r3)
	@29:
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @30
	lfs f2, 0x38(r31)
	lfs f1, float_30_8041a1a8(r0)
	lfs f4, 0x58(r3)
	fsubs f0, f2, f1
	lfs f5, 0x60(r3)
	lfs f3, 0x40(r31)
	fcmpo cr0, f0, f4
	cror eq, lt, eq
	bne @31
	fadds f0, f2, f1
	fcmpo cr0, f4, f0
	cror eq, lt, eq
	bne @31
	fsubs f0, f3, f1
	fcmpo cr0, f0, f5
	cror eq, lt, eq
	bne @31
	fadds f0, f3, f1
	fcmpo cr0, f5, f0
	cror eq, lt, eq
	bne @31
	li r0, 0x1
	b @32
	@31:
	li r0, 0x0
	@32:
	cmpwi r0, 0x0
	beq @30
	lfs f0, 0x10(r30)
	stfs f0, 0x5c(r3)
	@30:
	bl marioGetExtraPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @33
	lfs f2, 0x38(r31)
	lfs f1, float_30_8041a1a8(r0)
	lfs f4, 0x58(r3)
	fsubs f0, f2, f1
	lfs f5, 0x60(r3)
	lfs f3, 0x40(r31)
	fcmpo cr0, f0, f4
	cror eq, lt, eq
	bne @34
	fadds f0, f2, f1
	fcmpo cr0, f4, f0
	cror eq, lt, eq
	bne @34
	fsubs f0, f3, f1
	fcmpo cr0, f0, f5
	cror eq, lt, eq
	bne @34
	fadds f0, f3, f1
	fcmpo cr0, f5, f0
	cror eq, lt, eq
	bne @34
	li r0, 0x1
	b @35
	@34:
	li r0, 0x0
	@35:
	cmpwi r0, 0x0
	beq @33
	lfs f0, 0x10(r30)
	stfs f0, 0x5c(r3)
	@33:
	bl npcGetWorkPtr
	lwz r5, 0xc(r3)
	li r4, 0x0
	b @36
	@37:
	lwz r0, 0x0(r5)
	clrlwi. r0, r0, 31
	beq @38
	lfs f2, 0x38(r31)
	lfs f1, float_42p42_8041a1dc(r0)
	lfs f4, 0x8c(r5)
	fsubs f0, f2, f1
	lfs f5, 0x94(r5)
	lfs f3, 0x40(r31)
	fcmpo cr0, f0, f4
	cror eq, lt, eq
	bne @39
	fadds f0, f2, f1
	fcmpo cr0, f4, f0
	cror eq, lt, eq
	bne @39
	fsubs f0, f3, f1
	fcmpo cr0, f0, f5
	cror eq, lt, eq
	bne @39
	fadds f0, f3, f1
	fcmpo cr0, f5, f0
	cror eq, lt, eq
	bne @39
	li r0, 0x1
	b @40
	@39:
	li r0, 0x0
	@40:
	cmpwi r0, 0x0
	beq @38
	lfs f0, 0x10(r30)
	stfs f0, 0x90(r5)
	@38:
	addi r4, r4, 0x1
	addi r5, r5, 0x340
	@36:
	lwz r0, 0x4(r3)
	cmpw r4, r0
	blt @37
	lfs f1, 0x38(r31)
	lfs f2, 0x3c(r31)
	lfs f3, 0x40(r31)
	lfs f4, float_42p42_8041a1dc(r0)
	bl itemNearDistCheck
	cmplwi r3, 0x0
	beq @41
	lfs f0, 0x10(r30)
	stfs f0, 0x40(r3)
	@41:
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_2_8041a190(r0)
	fcmpo cr0, f1, f0
	blt @4
	bl animGetPtr
	lwz r0, 0x70(r31)
	la r4, str_8041A12C(r0)
	lwz r6, 0x10(r3)
	li r5, 0x1
	mulli r3, r0, 0x170
	lwzx r0, r6, r3
	rlwinm r0, r0, 0, 28, 26
	stwx r0, r6, r3
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 22, 20
	stw r0, 0x0(r31)
	lwz r3, 0x70(r31)
	bl animPoseSetAnim
	addi r4, r31, 0x38
	li r3, 0x1f0
	bl psndSFXOn_3D
	li r0, 0x14
	stw r0, 0x1b0(r31)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	@7:
	lwz r3, 0x1b0(r31)
	subi r0, r3, 0x1
	stw r0, 0x1b0(r31)
	lwz r0, 0x1b0(r31)
	cmpwi r0, 0x0
	bne @4
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @4
	@6:
	lwz r3, 0x0(r31)
	li r0, 0x0
	rlwinm r3, r3, 0, 29, 27
	stw r3, 0x0(r31)
	stw r0, 0x1dc(r31)
	@4:
	li r3, 0x0
	psq_l f31, 0x28(r1), 0, 0
	lwz r0, 0x34(r1)
	lfd f31, 0x20(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void kururing_capture(CameraId camId, MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x2e0(r1)
	mflr r0
	lis r5, vec3_802c3dc8@ha
	stw r0, 0x2e4(r1)
	stmw r26, 0x2c8(r1)
	mr r26, r3
	mr r27, r4
	addi r30, r5, vec3_802c3dc8@l
	bl camGetPtr
	mr r4, r3
	addi r3, r1, 0x38
	li r5, 0x260
	bl memcpy
	lwz r3, 0x70(r27)
	bl animPoseGetAnimBaseDataPtr
	lwz r6, 0x264(r30)
	lwz r5, 0x26c(r30)
	lwz r4, 0x270(r30)
	lwz r0, 0x278(r30)
	stw r6, 0x14(r1)
	lfs f1, 0xd0(r3)
	stw r5, 0x1c(r1)
	lfs f0, 0xd8(r3)
	stfs f1, 0x14(r1)
	lfs f1, 0xdc(r3)
	stw r4, 0x8(r1)
	lwz r5, 0x14(r1)
	stfs f0, 0x1c(r1)
	lfs f0, 0xe4(r3)
	stw r0, 0x10(r1)
	lwz r6, 0x1c(r1)
	stfs f1, 0x8(r1)
	lwz r7, 0x268(r30)
	stfs f0, 0x10(r1)
	lwz r4, 0x8(r1)
	lwz r0, 0x10(r1)
	stw r5, 0x2c(r1)
	lwz r5, 0x274(r30)
	stw r6, 0x34(r1)
	lfs f2, 0x2c(r1)
	stw r4, 0x20(r1)
	lfs f0, 0x34(r1)
	stw r0, 0x28(r1)
	lfs f3, 0x20(r1)
	lfs f1, 0x28(r1)
	fsubs f2, f3, f2
	lfs f3, float_10_8041a1a4(r0)
	fsubs f0, f1, f0
	stw r7, 0x18(r1)
	lfs f4, 0xd4(r3)
	fmuls f1, f3, f2
	fmuls f0, f3, f0
	lfs f2, 0xe0(r3)
	stw r5, 0xc(r1)
	mr r3, r26
	fctiwz f1, f1
	fctiwz f0, f0
	stfs f4, 0x18(r1)
	stfs f2, 0xc(r1)
	lwz r4, 0x18(r1)
	stfd f1, 0x298(r1)
	lwz r0, 0xc(r1)
	stfd f0, 0x2a0(r1)
	lwz r28, 0x29c(r1)
	stw r4, 0x30(r1)
	lwz r29, 0x2a4(r1)
	stw r0, 0x24(r1)
	bl camGetPtr
	lwz r4, 0x27c(r30)
	mr r31, r3
	lwz r0, 0x280(r30)
	addi r3, r29, 0x1
	addi r5, r28, 0x1
	lfd f1, 0x510(r30)
	stw r4, 0x24(r31)
	rlwinm r28, r3, 0, 16, 30
	rlwinm r29, r5, 0, 16, 30
	stw r0, 0x28(r31)
	lwz r0, 0x284(r30)
	stw r0, 0x2c(r31)
	lwz r3, 0x38(r27)
	lwz r0, 0x3c(r27)
	stw r3, 0x18(r31)
	stw r0, 0x1c(r31)
	lwz r0, 0x40(r27)
	stw r0, 0x20(r31)
	lwz r3, 0x38(r27)
	lwz r0, 0x3c(r27)
	stw r3, 0xc(r31)
	stw r0, 0x10(r31)
	lwz r0, 0x40(r27)
	stw r0, 0x14(r31)
	bl tan
	lis r4, 0x4330
	frsp f3, f1
	stw r28, 0x2ac(r1)
	divw r0, r29, r28
	lfd f2, 0x518(r30)
	addi r3, r31, 0x15c
	stw r4, 0x2a8(r1)
	lfs f0, float_0p5_8041a15c(r0)
	lfd f1, 0x2a8(r1)
	fsubs f1, f1, f2
	xoris r0, r0, 0x8000
	stw r0, 0x2b4(r1)
	lfs f6, 0x10(r31)
	fmuls f1, f1, f0
	stw r4, 0x2b0(r1)
	lfd f2, 0x400(r30)
	lfd f0, 0x2b0(r1)
	fdivs f5, f1, f3
	lfs f1, float_25_8041a140(r0)
	lfs f3, float_1_8041a160(r0)
	lfs f4, float_32767_8041a1e4(r0)
	fadds f5, f6, f5
	fsubs f2, f0, f2
	stfs f5, 0x10(r31)
	bl C_MTXPerspective
	li r0, 0x0
	addi r3, r31, 0x11c
	stw r0, 0x19c(r31)
	addi r4, r31, 0xc
	addi r5, r31, 0x24
	addi r6, r31, 0x18
	bl C_MTXLookAt
	lwz r4, 0x19c(r31)
	addi r3, r31, 0x15c
	bl GXSetProjection
	lis r0, 0x4330
	lfs f1, float_0_8041a150(r0)
	stw r29, 0x2bc(r1)
	lfd f4, 0x518(r30)
	fmr f2, f1
	stw r0, 0x2b8(r1)
	fmr f5, f1
	lfs f6, float_1_8041a160(r0)
	lfd f0, 0x2b8(r1)
	stw r28, 0x2c4(r1)
	fsubs f3, f0, f4
	stw r0, 0x2c0(r1)
	lfd f0, 0x2c0(r1)
	fsubs f4, f0, f4
	bl GXSetViewport
	mr r5, r29
	mr r6, r28
	li r3, 0x0
	li r4, 0x0
	bl GXSetScissor
	mr r3, r26
	bl test_kururing_mapdisp
	bl sysWaitDrawSync
	extrwi r31, r29, 15, 16
	extrwi r30, r28, 15, 16
	mr r3, r31
	li r5, 0x6
	mr r4, r30
	li r6, 0x0
	li r7, 0x0
	bl GXGetTexBufferSize
	li r4, 0x3
	bl smartAlloc
	stw r3, 0x208(r27)
	mr r5, r29
	mr r6, r28
	li r3, 0x0
	li r4, 0x0
	bl GXSetTexCopySrc
	mr r3, r31
	mr r4, r30
	li r5, 0x6
	li r6, 0x1
	bl GXSetTexCopyDst
	li r3, 0x1
	li r4, 0x3
	li r5, 0x1
	bl GXSetZMode
	lwz r3, 0x208(r27)
	li r4, 0x1
	lwz r3, 0x0(r3)
	bl GXCopyTex
	bl GXInvalidateTexAll
	bl GXPixModeSync
	bl GXTexModeSync
	lwz r4, 0x208(r27)
	mr r5, r31
	mr r6, r30
	addi r3, r27, 0x1e8
	lwz r4, 0x0(r4)
	li r7, 0x6
	li r8, 0x0
	li r9, 0x0
	li r10, 0x0
	bl GXInitTexObj
	lfs f1, float_0_8041a150(r0)
	addi r3, r27, 0x1e8
	li r4, 0x0
	li r5, 0x0
	fmr f2, f1
	li r6, 0x0
	fmr f3, f1
	li r7, 0x0
	li r8, 0x0
	bl GXInitTexObjLOD
	addi r3, r27, 0x20c
	bl PSMTXIdentity
	mr r3, r26
	bl camGetPtr
	addi r4, r1, 0x38
	li r5, 0x260
	bl memcpy
	lmw r26, 0x2c8(r1)
	lwz r0, 0x2e4(r1)
	mtlr r0
	addi r1, r1, 0x2e0
	blr
}

asm USER_FUNC(evt_mobj_breaking_floor) {
	nofralloc
	stwu r1, -0xc0(r1)
	mflr r0
	stw r0, 0xc4(r1)
	stfd f31, 0xb8(r1)
	stfd f30, 0xb0(r1)
	stfd f29, 0xa8(r1)
	stmw r26, 0x90(r1)
	mr r30, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r27, r3
	mr r3, r30
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r29)
	mr r3, r30
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r29)
	mr r3, r30
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x10(r29)
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x14(r29)
	mr r28, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, gp(r0)
	cmpwi r28, 0x1
	lwz r31, 0x18(r29)
	mr r29, r3
	lwz r3, 0x14(r4)
	neg r0, r3
	or r0, r0, r3
	srwi r26, r0, 31
	beq @1
	bge @2
	cmpwi r28, 0x0
	bge @3
	b @2
	@3:
	lis r4, str_802C42E8@ha
	addi r3, r1, 0x8
	addi r4, r4, str_802C42E8@l
	bl strcpy
	b @4
	@1:
	lis r4, str_802C42FC@ha
	addi r3, r1, 0x8
	addi r4, r4, str_802C42FC@l
	bl strcpy
	b @4
	@2:
	lis r4, str_802C42E8@ha
	addi r3, r1, 0x8
	addi r4, r4, str_802C42E8@l
	bl strcpy
	@4:
	mr r4, r26
	addi r3, r1, 0x8
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @5
	li r3, 0x0
	b @6
	@5:
	mr r3, r27
	addi r4, r1, 0x8
	bl mobjEntry
	mr r3, r27
	bl mobjNameToPtr
	fmr f1, f31
	mr r26, r3
	fmr f2, f30
	mr r3, r27
	fmr f3, f29
	bl mobjSetPosition
	lis r4, mobj_breaking_floor@ha
	mr r3, r30
	addi r0, r4, mobj_breaking_floor@l
	mr r4, r31
	stw r0, 0x1d0(r26)
	stw r29, 0x1d4(r26)
	lwz r0, 0x0(r26)
	ori r0, r0, 0x4
	stw r0, 0x0(r26)
	lwz r0, 0x0(r26)
	oris r0, r0, 0x100
	stw r0, 0x0(r26)
	stw r31, 0x1e4(r26)
	bl evtGetValue
	cmpwi r3, 0x0
	beq @7
	li r0, 0x63
	stw r0, 0x1dc(r26)
	b @8
	@7:
	li r0, 0x0
	stw r0, 0x1dc(r26)
	@8:
	mr r3, r26
	bl mobjCalcMtx
	lwz r3, 0x70(r26)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r3, 0x2
	@6:
	lfd f31, 0xb8(r1)
	lfd f30, 0xb0(r1)
	lfd f29, 0xa8(r1)
	lmw r26, 0x90(r1)
	lwz r0, 0xc4(r1)
	mtlr r0
	addi r1, r1, 0xc0
	blr
}

asm s32 mobj_breaking_floor(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	mr r31, r3
	bl marioGetPtr
	lwz r0, 0x1dc(r31)
	lwz r3, dat_8041a130(r0)
	cmpwi r0, 0x1
	stw r3, 0x8(r1)
	stw r3, 0x14(r1)
	stw r3, 0x18(r1)
	beq @1
	bge @2
	cmpwi r0, 0x0
	bge @3
	b @4
	@2:
	cmpwi r0, 0x63
	beq @5
	b @4
	@3:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @4
	lis r3, 0x4
	addi r4, r31, 0x38
	addi r3, r3, 0x1e8
	bl psndSFXOn_3D
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r4, 0x1d4(r31)
	cmplwi r4, 0x0
	beq @6
	mr r3, r31
	bl mobjRunEvent
	@6:
	lwz r3, 0x74(r31)
	cmplwi r3, 0x0
	beq @7
	lhz r0, 0x0(r3)
	ori r0, r0, 0x1
	sth r0, 0x0(r3)
	@7:
	lwz r0, 0x0(r31)
	li r3, 0x0
	li r5, 0x1
	ori r0, r0, 0x2
	stw r0, 0x0(r31)
	lwz r4, 0x1e4(r31)
	bl evtSetValue
	li r0, 0x1
	li r4, 0x40
	stw r0, 0x1dc(r31)
	lwz r3, 0x70(r31)
	bl animPoseSetMaterialFlagOn
	lwz r0, 0x14(r1)
	addi r4, r1, 0x10
	stw r0, 0x10(r1)
	lwz r3, 0x70(r31)
	bl animPoseSetMaterialEvtColor
	li r0, 0x40
	stw r0, 0x1b0(r31)
	b @4
	@1:
	lwz r3, 0x70(r31)
	bl animPoseGetMaterialEvtColor
	stw r3, 0x18(r1)
	lbz r3, 0x1b(r1)
	cmplwi r3, 0x4
	blt @8
	subi r0, r3, 0x4
	stb r0, 0x1b(r1)
	b @9
	@8:
	li r3, 0x0
	li r0, 0x63
	stb r3, 0x1b(r1)
	stw r0, 0x1dc(r31)
	@9:
	lwz r0, 0x18(r1)
	addi r4, r1, 0xc
	stw r0, 0xc(r1)
	lwz r3, 0x70(r31)
	bl animPoseSetMaterialEvtColor
	lwz r3, 0x1b0(r31)
	subi r0, r3, 0x1
	stw r0, 0x1b0(r31)
	lwz r0, 0x1b0(r31)
	cmpwi r0, 0x0
	bgt @4
	li r0, 0x63
	stw r0, 0x1dc(r31)
	b @4
	@5:
	addi r3, r31, 0x5
	bl mobjDelete
	@4:
	lwz r0, 0x34(r1)
	li r3, 0x0
	lwz r31, 0x2c(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm USER_FUNC(evt_mobj_brick) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	lis r4, vec3_802c3dc8@ha
	stw r0, 0x54(r1)
	stfd f31, 0x48(r1)
	stfd f30, 0x40(r1)
	stfd f29, 0x38(r1)
	stmw r23, 0x14(r1)
	addi r29, r4, vec3_802c3dc8@l
	mr r24, r3
	lwz r26, 0x18(r3)
	lwz r4, 0x0(r26)
	bl evtGetValue
	lwz r4, 0x4(r26)
	mr r28, r3
	mr r3, r24
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r26)
	mr r3, r24
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r26)
	mr r3, r24
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x10(r26)
	mr r3, r24
	bl evtGetValue
	lwz r27, 0x14(r26)
	mr r30, r3
	lwz r4, 0x18(r26)
	mr r3, r24
	bl evtGetValue
	lwz r4, gp(r0)
	cmplwi r27, 0xd
	lwz r26, 0x1c(r26)
	mr r31, r3
	lwz r3, 0x14(r4)
	neg r0, r3
	or r0, r0, r3
	srwi r23, r0, 31
	bgt @1
	lis r3, jumptable_8030A7FC@ha
	slwi r0, r27, 2
	addi r3, r3, jumptable_8030A7FC@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@2:
	addi r25, r29, 0x488
	b @1
	@3:
	addi r25, r29, 0x54c
	b @1
	@4:
	addi r25, r29, 0x564
	b @1
	@5:
	addi r25, r29, 0x57c
	b @1
	@6:
	addi r25, r29, 0x45c
	b @1
	@7:
	addi r25, r29, 0x45c
	b @1
	@8:
	addi r25, r29, 0x590
	b @1
	@9:
	addi r25, r29, 0x5a8
	@1:
	mr r3, r25
	mr r4, r23
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @10
	li r3, 0x0
	b @11
	@10:
	mr r4, r23
	addi r3, r29, 0x5c0
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @12
	li r3, 0x0
	b @11
	@12:
	mr r3, r28
	mr r4, r25
	bl mobjEntry
	mr r3, r28
	bl mobjNameToPtr
	fmr f1, f31
	mr r25, r3
	fmr f2, f30
	mr r3, r28
	fmr f3, f29
	bl mobjSetPosition
	cmpwi r27, 0xa
	blt @13
	lwz r0, 0x0(r25)
	ori r0, r0, 0x800
	stw r0, 0x0(r25)
	@13:
	cmplwi r27, 0xd
	bgt @14
	lis r3, jumptable_8030A7C4@ha
	slwi r0, r27, 2
	addi r3, r3, jumptable_8030A7C4@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@15:
	lis r3, mobj_brickblk@ha
	addi r0, r3, mobj_brickblk@l
	stw r0, 0x1d0(r25)
	b @14
	@16:
	lis r3, mobj_badgeblk@ha
	addi r0, r3, mobj_badgeblk@l
	stw r0, 0x1d0(r25)
	b @14
	@17:
	lis r3, mobj_badgeblk@ha
	addi r0, r3, mobj_badgeblk@l
	stw r0, 0x1d0(r25)
	b @14
	@18:
	lis r3, mobj_10countblk@ha
	addi r0, r3, mobj_10countblk@l
	stw r0, 0x1d0(r25)
	@14:
	stw r31, 0x1d4(r25)
	li r0, 0x0
	mr r3, r25
	lwz r4, 0x0(r25)
	ori r4, r4, 0x4
	stw r4, 0x0(r25)
	lwz r4, 0x0(r25)
	oris r4, r4, 0xc1
	stw r4, 0x0(r25)
	stw r26, 0x1e4(r25)
	stw r0, 0x1dc(r25)
	stw r30, 0x1a0(r25)
	bl mobjCalcMtx
	cmpwi r27, 0xa
	bge @19
	lwz r3, 0x70(r25)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	b @20
	@19:
	cmpwi r27, 0xd
	bne @21
	lwz r3, 0x70(r25)
	la r4, str_8041A1E8(r0)
	li r5, 0x1
	bl animPoseSetAnim
	b @20
	@21:
	lwz r3, 0x70(r25)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	@20:
	mr r3, r24
	mr r4, r26
	bl evtGetValue
	cmpwi r3, 0x0
	beq @22
	cmplwi r27, 0xd
	li r23, 0x0
	bgt @23
	lis r3, jumptable_8030A78C@ha
	slwi r0, r27, 2
	addi r3, r3, jumptable_8030A78C@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@24:
	lwz r3, 0x70(r25)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x63
	stw r0, 0x1dc(r25)
	b @23
	@25:
	lwz r3, 0x70(r25)
	la r4, str_8041A1C0(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x5a
	addi r23, r29, 0x450
	stw r0, 0x1dc(r25)
	b @23
	@26:
	lwz r3, 0x70(r25)
	la r4, str_8041A1C0(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x5a
	addi r23, r29, 0x5c8
	stw r0, 0x1dc(r25)
	b @23
	@27:
	lwz r3, 0x70(r25)
	la r4, str_8041A1C0(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x5a
	addi r23, r29, 0x450
	stw r0, 0x1dc(r25)
	@23:
	cmplwi r23, 0x0
	beq @28
	mr r4, r23
	addi r3, r25, 0x15
	bl strcpy
	@28:
	lwz r0, 0x0(r25)
	rlwinm r0, r0, 0, 21, 19
	stw r0, 0x0(r25)
	@22:
	li r3, 0x2
	@11:
	lfd f31, 0x48(r1)
	lfd f30, 0x40(r1)
	lfd f29, 0x38(r1)
	lmw r23, 0x14(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm s32 mobj_10countblk(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r0, 0x1dc(r3)
	cmpwi r0, 0x5a
	beq @1
	bge @2
	cmpwi r0, 0x1
	beq @3
	bge @4
	cmpwi r0, 0x0
	bge @5
	b @4
	@2:
	cmpwi r0, 0x5c
	bge @4
	b @6
	@5:
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 28, 28
	beq @4
	rlwinm. r0, r3, 0, 20, 20
	beq @7
	rlwinm r0, r3, 0, 21, 19
	lis r3, str_802C4218@ha
	stw r0, 0x0(r31)
	addi r4, r3, str_802C4218@l
	addi r3, r31, 0x15
	bl strcpy
	@7:
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	addi r4, r31, 0x38
	li r3, 0x1be
	bl psndSFXOn_3D
	lwz r4, 0x1e4(r31)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	lwz r4, 0x1d4(r31)
	cmplwi r4, 0x0
	beq @8
	mr r3, r31
	bl mobjRunEvent
	b @9
	@8:
	li r3, 0x1
	bl pouchAddCoin
	lfs f1, 0x38(r31)
	li r3, 0x0
	lfs f2, 0x3c(r31)
	li r4, 0x79
	lfs f3, 0x40(r31)
	li r5, 0xf
	li r6, -0x1
	li r7, 0x0
	bl itemEntry
	li r0, 0xc8
	stw r0, 0x1b0(r31)
	@9:
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	b @4
	@3:
	lwz r3, 0x1b0(r31)
	cmpwi r3, 0x0
	ble @10
	subi r0, r3, 0x1
	stw r0, 0x1b0(r31)
	@10:
	lwz r0, 0x1b0(r31)
	cmpwi r0, 0x0
	bgt @11
	li r0, 0x5a
	la r4, str_8041A1C0(r0)
	stw r0, 0x1dc(r31)
	li r5, 0x1
	lwz r3, 0x70(r31)
	bl animPoseSetAnim
	lis r4, str_802C4218@ha
	addi r3, r31, 0x15
	addi r4, r4, str_802C4218@l
	bl strcpy
	b @4
	@11:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @4
	addi r4, r31, 0x38
	li r3, 0x1bf
	bl psndSFXOn_3D
	li r3, 0x1
	bl pouchAddCoin
	lfs f1, 0x38(r31)
	li r3, 0x0
	lfs f2, 0x3c(r31)
	li r4, 0x79
	lfs f3, 0x40(r31)
	li r5, 0xf
	li r6, -0x1
	li r7, 0x0
	bl itemEntry
	lwz r0, 0x0(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	lwz r3, 0x70(r31)
	bl animPoseSetAnim
	b @4
	@1:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @4
	addi r4, r31, 0x38
	li r3, 0x1b7
	bl psndSFXOn_3D
	lwz r3, 0x70(r31)
	la r4, str_8041A120(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @4
	@6:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	bne @12
	li r0, 0x5a
	stw r0, 0x1dc(r31)
	b @4
	@12:
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @4
	lwz r3, 0x70(r31)
	la r4, str_8041A1C0(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x5a
	stw r0, 0x1dc(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	@4:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 mobj_brickblk(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x3f0(r1)
	mflr r0
	lis r4, vec3_802c3dc8@ha
	stw r0, 0x3f4(r1)
	stmw r27, 0x3dc(r1)
	addi r31, r4, vec3_802c3dc8@l
	mr r30, r3
	addi r3, r1, 0x18
	addi r4, r30, 0x5
	lwz r12, 0x238(r31)
	lwz r11, 0x23c(r31)
	lwz r10, 0x240(r31)
	lwz r9, 0x244(r31)
	lwz r8, 0x248(r31)
	lwz r7, 0x24c(r31)
	lwz r6, 0x250(r31)
	lwz r0, 0x254(r31)
	lwz r5, gp(r0)
	stw r12, 0x18(r1)
	stw r11, 0x1c(r1)
	stw r10, 0x20(r1)
	stw r9, 0x24(r1)
	stw r8, 0x8(r1)
	stw r7, 0xc(r1)
	stw r6, 0x10(r1)
	stw r0, 0x14(r1)
	lwz r5, 0x14(r5)
	neg r0, r5
	or r0, r0, r5
	srwi r27, r0, 31
	bl strcat
	addi r3, r1, 0x8
	addi r4, r30, 0x5
	bl strcat
	lwz r0, 0x1dc(r30)
	cmpwi r0, 0xb
	beq @1
	bge @2
	cmpwi r0, 0x0
	beq @3
	blt @4
	cmpwi r0, 0xa
	bge @5
	b @4
	@2:
	cmpwi r0, 0x63
	beq @6
	bge @4
	cmpwi r0, 0xd
	bge @4
	b @7
	@3:
	mr r4, r27
	addi r3, r31, 0x5c0
	li r5, 0x0
	bl animGroupBaseAsync
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 28, 28
	beq @4
	lwz r4, 0x1d4(r30)
	mr r3, r30
	bl mobjRunEvent
	lwz r4, 0x1e4(r30)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	li r0, 0xa
	stw r0, 0x1dc(r30)
	b @4
	@5:
	mr r4, r27
	addi r3, r31, 0x5c0
	bl animPaperPoseEntry
	addi r3, r1, 0x18
	bl offscreenEntry
	mr r4, r27
	addi r3, r1, 0x8
	bl imgEntry
	addi r3, r1, 0x18
	bl offscreenNameToId
	stw r3, 0x19c(r30)
	li r5, 0x0
	addi r3, r1, 0x50
	addi r29, r1, 0x8
	addi r28, r1, 0x18
	li r0, 0x1
	stw r3, 0x240(r1)
	addi r3, r1, 0x228
	li r4, 0x1
	stw r29, 0x50(r1)
	stw r5, 0x54(r1)
	stw r28, 0x58(r1)
	stw r0, 0x5c(r1)
	stw r5, 0x60(r1)
	stw r5, 0x64(r1)
	stw r5, 0x68(r1)
	stw r5, 0x6c(r1)
	bl evt_img_alloc_capture
	li r0, 0x0
	li r5, 0x1
	addi r6, r1, 0x28
	stw r29, 0x28(r1)
	addi r3, r1, 0x78
	li r4, 0x1
	stw r6, 0x90(r1)
	stw r5, 0x2c(r1)
	stw r28, 0x30(r1)
	stw r5, 0x34(r1)
	stw r0, 0x38(r1)
	stw r0, 0x3c(r1)
	stw r0, 0x40(r1)
	stw r0, 0x44(r1)
	bl evt_img_alloc_capture
	mr r4, r27
	mr r3, r29
	bl imgNameToPtr
	mr r28, r3
	mr r4, r27
	addi r3, r31, 0x5c0
	bl animPaperPoseGetId
	stw r3, 0x104(r28)
	la r0, str_8041A118(r0)
	mr r3, r27
	stw r0, 0x108(r28)
	bl animTimeGetTime
	stw r4, 0x114(r28)
	li r4, 0x2
	stw r3, 0x110(r28)
	mr r3, r28
	bl imgSetShadow
	addi r4, r30, 0x38
	li r3, 0x1b8
	bl psndSFXOn_3D
	li r0, 0xb
	stw r0, 0x1dc(r30)
	b @4
	@1:
	mr r4, r27
	addi r3, r1, 0x8
	bl imgNameToPtr
	lfs f1, 0x118(r3)
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @8
	li r0, 0xc
	stw r0, 0x1dc(r30)
	@8:
	lwz r0, 0xcc(r3)
	rlwinm. r0, r0, 0, 3, 3
	beq @9
	li r0, 0xc
	stw r0, 0x1dc(r30)
	@9:
	lwz r3, 0x258(r31)
	lwz r0, 0x25c(r31)
	stw r3, 0x38(r30)
	stw r0, 0x3c(r30)
	lwz r0, 0x260(r31)
	stw r0, 0x40(r30)
	lwz r0, 0x0(r30)
	ori r0, r0, 0x4
	stw r0, 0x0(r30)
	lwz r0, 0x0(r30)
	ori r0, r0, 0x8
	stw r0, 0x0(r30)
	b @4
	@7:
	mr r4, r27
	addi r3, r1, 0x8
	bl imgNameToPtr
	li r4, 0x0
	mr r28, r3
	bl imgFreeCapture
	mr r3, r28
	li r4, 0x1
	bl imgFreeCapture
	mr r3, r28
	li r4, 0x0
	bl imgSetShadow
	mr r3, r28
	mr r4, r27
	bl imgRelease
	addi r3, r1, 0x18
	bl offscreenDelete
	li r3, -0x1
	li r0, 0x63
	stw r3, 0x19c(r30)
	stw r0, 0x1dc(r30)
	b @4
	@6:
	addi r3, r30, 0x5
	bl mobjDelete
	@4:
	lmw r27, 0x3dc(r1)
	li r3, 0x0
	lwz r0, 0x3f4(r1)
	mtlr r0
	addi r1, r1, 0x3f0
	blr
}

asm USER_FUNC(evt_mobj_powerupblk) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	addi r11, r1, 0x40
	bl _savefpr_28
	stmw r27, 0xc(r1)
	mr r30, r3
	lwz r28, 0x18(r3)
	lwz r4, 0x0(r28)
	bl evtGetValue
	lwz r4, 0x4(r28)
	mr r27, r3
	mr r3, r30
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x8(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0xc(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f28, f1
	lwz r4, 0x10(r28)
	mr r3, r30
	bl evtGetValue
	lwz r31, 0x14(r28)
	mr r29, r3
	lwz r4, 0x18(r28)
	mr r3, r30
	bl evtGetFloat
	lwz r4, gp(r0)
	lis r3, str_802C43A0@ha
	addi r3, r3, str_802C43A0@l
	fmr f31, f1
	lwz r4, 0x14(r4)
	mr r28, r3
	li r5, 0x0
	neg r0, r4
	or r0, r0, r4
	srwi r4, r0, 31
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r3, r27
	mr r4, r28
	bl mobjEntry
	mr r3, r27
	bl mobjNameToPtr
	fmr f1, f30
	mr r28, r3
	fmr f2, f29
	mr r3, r27
	fmr f3, f28
	bl mobjSetPosition
	lis r3, mobj_powerupblk@ha
	li r0, 0x0
	addi r4, r3, mobj_powerupblk@l
	mr r3, r28
	stw r4, 0x1d0(r28)
	stw r29, 0x1d4(r28)
	lwz r4, 0x0(r28)
	ori r4, r4, 0x4
	stw r4, 0x0(r28)
	lwz r4, 0x0(r28)
	oris r4, r4, 0xc1
	stw r4, 0x0(r28)
	stw r31, 0x1e4(r28)
	stw r0, 0x1dc(r28)
	stfs f31, 0x54(r28)
	bl mobjCalcMtx
	lwz r3, 0x70(r28)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	mr r3, r30
	mr r4, r31
	bl evtGetValue
	cmpwi r3, 0x0
	beq @3
	li r0, 0x5a
	la r4, str_8041A11C(r0)
	stw r0, 0x1dc(r28)
	li r5, 0x1
	lwz r3, 0x70(r28)
	bl animPoseSetAnim
	@3:
	li r3, 0x2
	@2:
	addi r11, r1, 0x40
	bl _restfpr_28
	lmw r27, 0xc(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 mobj_powerupblk(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lis r3, vec3_802c3dc8@ha
	stw r30, 0x8(r1)
	addi r30, r3, vec3_802c3dc8@l
	lwz r0, 0x1dc(r31)
	cmpwi r0, 0x2
	beq @1
	bge @2
	cmpwi r0, 0x0
	beq @3
	bge @4
	b @5
	@2:
	cmpwi r0, 0x5a
	beq @6
	b @5
	@3:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @5
	bl marioKeyOffChk
	cmpwi r3, 0x0
	bne @7
	bl marioCtrlOffChk
	cmpwi r3, 0x0
	beq @8
	@7:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	b @5
	@8:
	bl marioKeyOff
	lwz r3, gp(r0)
	addi r4, r30, 0x5ec
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	bne @9
	bl marioCtrlOff
	b @10
	@9:
	lwz r3, gp(r0)
	addi r4, r30, 0x5f4
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	beq @11
	lwz r3, gp(r0)
	addi r4, r30, 0x5fc
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	bne @10
	@11:
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x80
	cmplwi r0, 0x0
	bne @10
	bl marioCtrlOff
	@10:
	lwz r5, gp(r0)
	lis r3, 0x2
	addi r3, r3, 0x1c0
	addi r4, r31, 0x38
	lwz r0, 0x18(r5)
	ori r0, r0, 0x3
	stw r0, 0x18(r5)
	bl psndSFXOn_3D
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lfs f1, 0x38(r31)
	addi r3, r30, 0x604
	lfs f2, 0x3c(r31)
	li r4, 0x57
	lfs f3, 0x40(r31)
	li r5, 0xf
	li r6, -0x1
	li r7, 0x0
	bl itemEntry
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @5
	@4:
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @5
	lwz r3, 0x70(r31)
	la r4, str_8041A11C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r3, 0x0(r31)
	li r0, 0x1
	rlwinm r3, r3, 0, 29, 27
	stw r3, 0x0(r31)
	stw r0, 0x1a4(r31)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @5
	@1:
	lwz r3, 0x1a4(r31)
	cmpwi r3, 0x0
	beq @12
	subi r0, r3, 0x1
	stw r0, 0x1a4(r31)
	b @5
	@12:
	lfs f2, float_40_8041a1ec(r0)
	addi r3, r30, 0x60c
	lfs f0, 0x3c(r31)
	li r4, 0x57
	lfs f1, 0x38(r31)
	li r5, 0x11
	fadds f2, f2, f0
	lfs f3, 0x40(r31)
	li r6, -0x1
	li r7, 0x0
	bl itemEntry
	bl itemForceGet
	lwz r4, 0x1e4(r31)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	bl marioKeyOn
	lwz r3, gp(r0)
	addi r4, r30, 0x5ec
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	bne @13
	bl marioCtrlOn
	b @14
	@13:
	lwz r3, gp(r0)
	addi r4, r30, 0x5f4
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	beq @15
	lwz r3, gp(r0)
	addi r4, r30, 0x5fc
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	bne @14
	@15:
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x80
	cmplwi r0, 0x0
	bne @14
	bl marioCtrlOn
	@14:
	li r0, 0x5a
	stw r0, 0x1dc(r31)
	b @5
	@6:
	addi r3, r31, 0x5
	bl mobjDelete
	@5:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_badgeblk) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	lis r4, vec3_802c3dc8@ha
	stw r0, 0x44(r1)
	stfd f31, 0x38(r1)
	stfd f30, 0x30(r1)
	stfd f29, 0x28(r1)
	stmw r24, 0x8(r1)
	addi r30, r4, vec3_802c3dc8@l
	mr r27, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r24, r3
	mr r3, r27
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r29)
	mr r3, r27
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r29)
	mr r3, r27
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x10(r29)
	mr r3, r27
	bl evtGetValue
	lwz r4, 0x14(r29)
	mr r31, r3
	mr r3, r27
	bl evtGetValue
	lwz r4, gp(r0)
	mr r25, r3
	lwz r28, 0x1c(r29)
	addi r26, r30, 0x474
	lwz r3, 0x14(r4)
	cmpwi r28, 0x0
	lwz r29, 0x18(r29)
	neg r0, r3
	or r0, r0, r3
	srwi r4, r0, 31
	beq @1
	addi r26, r30, 0x614
	@1:
	mr r3, r26
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @2
	li r3, 0x0
	b @3
	@2:
	mr r3, r24
	mr r4, r26
	bl mobjEntry
	mr r3, r24
	bl mobjNameToPtr
	fmr f1, f31
	mr r26, r3
	fmr f2, f30
	mr r3, r24
	fmr f3, f29
	bl mobjSetPosition
	lis r3, mobj_badgeblk@ha
	li r0, 0x0
	addi r4, r3, mobj_badgeblk@l
	mr r3, r26
	stw r4, 0x1d0(r26)
	stw r25, 0x1d4(r26)
	lwz r4, 0x0(r26)
	ori r4, r4, 0x4
	stw r4, 0x0(r26)
	lwz r4, 0x0(r26)
	oris r4, r4, 0xc1
	stw r4, 0x0(r26)
	stw r29, 0x1e4(r26)
	stw r0, 0x1dc(r26)
	stw r31, 0x1a0(r26)
	bl mobjCalcMtx
	lwz r3, 0x70(r26)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	mr r3, r27
	mr r4, r29
	bl evtGetValue
	cmpwi r3, 0x0
	beq @4
	li r0, 0x5a
	la r4, str_8041A1C0(r0)
	stw r0, 0x1dc(r26)
	li r5, 0x1
	lwz r3, 0x70(r26)
	bl animPoseSetAnim
	cmpwi r28, 0x0
	addi r3, r26, 0x15
	addi r4, r30, 0x450
	beq @5
	addi r4, r30, 0x5c8
	@5:
	bl strcpy
	@4:
	li r3, 0x2
	@3:
	lfd f31, 0x38(r1)
	lfd f30, 0x30(r1)
	lfd f29, 0x28(r1)
	lmw r24, 0x8(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 mobj_badgeblk(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lis r3, vec3_802c3dc8@ha
	stw r30, 0x8(r1)
	addi r30, r3, vec3_802c3dc8@l
	lwz r0, 0x1dc(r31)
	cmpwi r0, 0x5a
	beq @1
	bge @2
	cmpwi r0, 0x1
	beq @3
	bge @4
	cmpwi r0, 0x0
	bge @5
	b @4
	@2:
	cmpwi r0, 0x5c
	bge @4
	b @6
	@5:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @4
	addi r3, r31, 0x15
	addi r4, r30, 0x614
	bl strcmp
	cmpwi r3, 0x0
	beq @7
	addi r3, r31, 0x15
	addi r4, r30, 0x564
	bl strcmp
	cmpwi r3, 0x0
	beq @7
	addi r3, r31, 0x15
	addi r4, r30, 0x590
	bl strcmp
	cmpwi r3, 0x0
	bne @8
	@7:
	addi r4, r31, 0x38
	li r3, 0x1bb
	bl psndSFXOn_3D
	b @9
	@8:
	addi r4, r31, 0x38
	li r3, 0x1ba
	bl psndSFXOn_3D
	@9:
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 20, 20
	beq @10
	rlwinm r0, r3, 0, 21, 19
	stw r0, 0x0(r31)
	@10:
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r4, 0x1d4(r31)
	cmplwi r4, 0x0
	beq @11
	mr r3, r31
	bl mobjRunEvent
	b @12
	@11:
	lwz r4, 0x1a0(r31)
	cmpwi r4, 0x79
	beq @13
	lfs f2, float_40_8041a1ec(r0)
	addi r3, r31, 0x5
	lfs f0, 0x3c(r31)
	li r5, 0x4
	lfs f1, 0x38(r31)
	li r7, 0x0
	fadds f2, f2, f0
	lfs f3, 0x40(r31)
	lwz r6, 0x1e4(r31)
	bl itemEntry
	addi r3, r31, 0x5
	bl itemNameToPtr
	mr r30, r3
	li r4, 0x10
	bl itemFlagOn
	lfs f0, float_0p7_8041a1c8(r0)
	li r0, 0x0
	lfs f1, float_1_8041a160(r0)
	addi r4, r31, 0x38
	stfs f0, 0x80(r30)
	li r3, 0x1bc
	lfs f0, float_360_8041a1f0(r0)
	stfs f1, 0x84(r30)
	stw r0, 0x88(r30)
	stfs f0, 0x58(r30)
	bl psndSFXOn_3D
	b @12
	@13:
	li r3, 0x1
	bl pouchAddCoin
	lfs f1, 0x38(r31)
	li r3, 0x0
	lfs f2, 0x3c(r31)
	li r4, 0x79
	lfs f3, 0x40(r31)
	li r5, 0xf
	li r6, -0x1
	li r7, 0x0
	bl itemEntry
	lwz r4, 0x1e4(r31)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	addi r4, r31, 0x38
	li r3, 0x5b
	bl psndSFXOn_3D
	@12:
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @4
	@3:
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @4
	lwz r3, 0x70(r31)
	la r4, str_8041A1C0(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r5, 0x0(r31)
	li r0, 0x5a
	addi r3, r31, 0x15
	addi r4, r30, 0x474
	rlwinm r5, r5, 0, 29, 27
	stw r5, 0x0(r31)
	stw r0, 0x1dc(r31)
	bl strcmp
	cmpwi r3, 0x0
	beq @14
	addi r3, r31, 0x15
	addi r4, r30, 0x54c
	bl strcmp
	cmpwi r3, 0x0
	beq @14
	addi r3, r31, 0x15
	addi r4, r30, 0x45c
	bl strcmp
	cmpwi r3, 0x0
	bne @15
	@14:
	addi r3, r31, 0x15
	addi r4, r30, 0x450
	bl strcpy
	b @4
	@15:
	addi r3, r31, 0x15
	addi r4, r30, 0x5c8
	bl strcpy
	b @4
	@1:
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 28, 28
	beq @4
	rlwinm r0, r3, 0, 29, 27
	la r4, str_8041A11C(r0)
	stw r0, 0x0(r31)
	li r5, 0x1
	lwz r3, 0x70(r31)
	bl animPoseSetAnim
	addi r4, r31, 0x38
	li r3, 0x1b7
	bl psndSFXOn_3D
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @4
	@6:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	bne @16
	li r0, 0x5a
	stw r0, 0x1dc(r31)
	b @4
	@16:
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @4
	lwz r3, 0x70(r31)
	la r4, str_8041A1C0(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x5a
	stw r0, 0x1dc(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	@4:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_save_blk) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x28(r1)
	stfd f30, 0x20(r1)
	stfd f29, 0x18(r1)
	stw r31, 0x14(r1)
	stw r30, 0x10(r1)
	stw r29, 0xc(r1)
	stw r28, 0x8(r1)
	mr r28, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lwz r4, 0x4(r30)
	mr r29, r3
	mr r3, r28
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r30)
	mr r3, r28
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r30)
	mr r3, r28
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x10(r30)
	mr r3, r28
	bl evtGetValue
	lwz r6, gp(r0)
	lis r4, str_802C43EC@ha
	addi r5, r4, str_802C43EC@l
	lwz r31, 0x14(r30)
	lwz r0, 0x0(r6)
	mr r30, r3
	lwz r4, 0x14(r6)
	mr r28, r5
	rlwinm. r0, r0, 0, 26, 26
	neg r3, r4
	or r3, r3, r4
	srwi r4, r3, 31
	beq @1
	li r3, 0x2
	b @2
	@1:
	mr r3, r5
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @3
	li r3, 0x0
	b @2
	@3:
	mr r3, r29
	mr r4, r28
	bl mobjEntry
	mr r3, r29
	bl mobjNameToPtr
	fmr f1, f31
	mr r28, r3
	fmr f2, f30
	mr r3, r29
	fmr f3, f29
	bl mobjSetPosition
	lis r4, mobj_save_blk@ha
	lis r3, mobj_save_blk_sysevt@ha
	addi r4, r4, mobj_save_blk@l
	li r0, 0x0
	stw r4, 0x1d0(r28)
	addi r4, r3, mobj_save_blk_sysevt@l
	mr r3, r28
	stw r30, 0x1d4(r28)
	stw r4, 0x1d8(r28)
	lwz r4, 0x0(r28)
	ori r4, r4, 0x84
	stw r4, 0x0(r28)
	lwz r4, 0x0(r28)
	oris r4, r4, 0x40
	stw r4, 0x0(r28)
	stw r31, 0x1e4(r28)
	stw r0, 0x1dc(r28)
	bl mobjCalcMtx
	lwz r3, 0x70(r28)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r3, 0x2
	@2:
	lwz r0, 0x34(r1)
	lfd f31, 0x28(r1)
	lfd f30, 0x20(r1)
	lfd f29, 0x18(r1)
	lwz r31, 0x14(r1)
	lwz r30, 0x10(r1)
	lwz r29, 0xc(r1)
	lwz r28, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 mobj_save_blk(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r0, 0x1dc(r3)
	cmpwi r0, 0x2
	beq @1
	bge @2
	cmpwi r0, 0x0
	beq @3
	bge @4
	b @5
	@2:
	cmpwi r0, 0x4
	beq @6
	bge @5
	b @7
	@3:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @5
	bl marioKeyOff
	li r3, 0x1
	bl marioStSystemLevel
	addi r4, r31, 0x38
	li r3, 0x1af
	bl psndSFXOn_3D
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r3, 0x8
	bl camGetPtr
	lhz r0, 0x0(r3)
	ori r0, r0, 0x200
	sth r0, 0x0(r3)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @5
	@4:
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @5
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r4, 0x1d4(r31)
	cmplwi r4, 0x0
	beq @8
	mr r3, r31
	bl mobjRunEvent
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @5
	@8:
	li r0, 0x3
	stw r0, 0x1dc(r31)
	b @5
	@1:
	lwz r3, 0x1cc(r31)
	bl evtCheckID
	cmpwi r3, 0x1
	beq @5
	li r0, 0x0
	stw r0, 0x1cc(r31)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @5
	@7:
	lwz r4, 0x1d8(r31)
	bl mobjRunEvent
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @5
	@6:
	lwz r3, 0x1cc(r31)
	bl evtCheckID
	cmpwi r3, 0x1
	beq @5
	li r3, 0x0
	bl marioStSystemLevel
	li r3, 0x8
	bl camGetPtr
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 23, 21
	sth r0, 0x0(r3)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	bl marioKeyOn
	li r0, 0x0
	stw r0, 0x1dc(r31)
	@5:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_recovery_blk) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x28(r1)
	stfd f30, 0x20(r1)
	stfd f29, 0x18(r1)
	stw r31, 0x14(r1)
	stw r30, 0x10(r1)
	mr r30, r3
	stw r29, 0xc(r1)
	stw r28, 0x8(r1)
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r28, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x8(r31)
	mr r29, r3
	mr r3, r30
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0xc(r31)
	mr r3, r30
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x10(r31)
	mr r3, r30
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x14(r31)
	mr r3, r30
	bl evtGetValue
	lwz r4, gp(r0)
	lis r3, str_802C4410@ha
	addi r30, r3, str_802C4410@l
	cmpwi r29, 0x0
	lwz r3, 0x14(r4)
	lwz r31, 0x18(r31)
	neg r0, r3
	or r0, r0, r3
	srwi r4, r0, 31
	bne @1
	lis r3, str_802C43FC@ha
	addi r30, r3, str_802C43FC@l
	@1:
	mr r3, r30
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @2
	li r3, 0x0
	b @3
	@2:
	mr r3, r28
	mr r4, r30
	bl mobjEntry
	mr r3, r28
	bl mobjNameToPtr
	fmr f1, f31
	stw r29, 0x1a4(r3)
	fmr f2, f30
	mr r30, r3
	fmr f3, f29
	mr r3, r28
	bl mobjSetPosition
	lwz r4, 0x0(r30)
	lis r3, mobj_recovery_blk@ha
	addi r0, r3, mobj_recovery_blk@l
	li r3, 0x0
	ori r4, r4, 0x4
	cmpwi r29, 0x0
	stw r4, 0x0(r30)
	stw r0, 0x1d0(r30)
	stw r3, 0x1d4(r30)
	stw r3, 0x1d8(r30)
	lwz r0, 0x0(r30)
	ori r0, r0, 0x4
	stw r0, 0x0(r30)
	lwz r0, 0x0(r30)
	oris r0, r0, 0x40
	stw r0, 0x0(r30)
	stw r31, 0x1e4(r30)
	bne @4
	stw r3, 0x1dc(r30)
	b @5
	@4:
	li r0, -0x1
	stw r0, 0x1dc(r30)
	@5:
	mr r3, r30
	bl mobjCalcMtx
	lwz r3, 0x70(r30)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r3, 0x2
	@3:
	lwz r0, 0x34(r1)
	lfd f31, 0x28(r1)
	lfd f30, 0x20(r1)
	lfd f29, 0x18(r1)
	lwz r31, 0x14(r1)
	lwz r30, 0x10(r1)
	lwz r29, 0xc(r1)
	lwz r28, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 mobj_recovery_blk(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r3
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	lwz r3, 0x1dc(r3)
	addi r0, r3, 0x1
	cmplwi r0, 0x16
	bgt @1
	lis r3, jumptable_8030A834@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_8030A834@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@2:
	lfs f2, float_25_8041a140(r0)
	li r3, 0x0
	lfs f1, 0x3c(r31)
	li r5, 0x0
	lfs f3, 0x40(r31)
	lfs f0, float_10_8041a1a4(r0)
	fadds f2, f2, f1
	lfs f1, 0x38(r31)
	fsubs f3, f3, f0
	lwz r4, 0x1a4(r31)
	bl effCoinFukidashiEntry
	stw r3, 0x1c8(r31)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @1
	@3:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @1
	bl marioKeyOff
	li r3, 0x8
	bl camGetPtr
	lhz r0, 0x0(r3)
	addi r4, r31, 0x38
	ori r0, r0, 0x200
	sth r0, 0x0(r3)
	li r3, 0x1d9
	bl psndSFXOn_3D
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	@4:
	lwz r3, gp(r0)
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 19, 19
	bne @5
	li r3, 0xea
	bl swGet
	cmpwi r3, 0x0
	bne @5
	li r3, 0xea
	bl swSet
	li r0, 0x14
	stw r0, 0x1dc(r31)
	b @1
	@5:
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	@6:
	bl pouchGetCoin
	lwz r0, 0x1a4(r31)
	cmpw r3, r0
	bge @7
	li r0, 0xa
	stw r0, 0x1dc(r31)
	b @1
	@7:
	lwz r3, 0x1c8(r31)
	cmplwi r3, 0x0
	beq @8
	bl effSoftDelete
	li r0, 0x0
	stw r0, 0x1c8(r31)
	@8:
	addi r4, r31, 0x38
	li r3, 0x1da
	bl psndSFXOn_3D
	lwz r3, 0x70(r31)
	la r4, str_8041A11C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r0, 0x1a4(r31)
	cmpwi r0, 0x0
	bne @9
	li r0, 0x3
	stw r0, 0x1dc(r31)
	b @10
	@9:
	li r0, 0x4
	stw r0, 0x1dc(r31)
	bl statusWinForceOpen
	@10:
	li r0, 0x78
	stw r0, 0x1b0(r31)
	b @1
	@11:
	lwz r0, 0x1b0(r31)
	cmpwi r0, 0x64
	bne @12
	lfs f4, float_50_8041a14c(r0)
	li r3, 0x1
	lfs f2, float_45_8041a1f4(r0)
	li r4, 0x1e
	lfs f0, 0x3c(r31)
	fmr f5, f4
	lfs f1, 0x38(r31)
	li r5, 0x3c
	fadds f2, f2, f0
	lfs f3, 0x40(r31)
	bl effStardustEntry
	addi r4, r31, 0x38
	li r3, 0x1db
	bl psndSFXOn_3D
	@12:
	lwz r0, 0x1b0(r31)
	cmpwi r0, 0x64
	bne @13
	bl marioGetPtr
	mr r30, r3
	bl pouchGetPtr
	lfs f4, float_50_8041a14c(r0)
	mr r29, r3
	lfs f1, 0x8c(r30)
	li r3, 0x2
	fmr f5, f4
	lfs f2, 0x90(r30)
	lfs f3, 0x94(r30)
	li r4, 0x32
	li r5, 0x64
	bl effStardustEntry
	la r3, str_8041A1F8(r0)
	bl marioChgPose
	lha r3, 0x72(r29)
	li r0, 0x2
	li r4, 0x0
	sth r3, 0x70(r29)
	lha r3, 0x76(r29)
	sth r3, 0x74(r29)
	mtctr r0
	@14:
	lhz r3, 0x0(r29)
	clrlwi. r0, r3, 31
	beq @15
	rlwinm. r0, r3, 0, 30, 30
	bne @15
	lha r0, 0x2(r29)
	sth r0, 0x6(r29)
	@15:
	lhz r3, 0xe(r29)
	clrlwi. r0, r3, 31
	beq @16
	rlwinm. r0, r3, 0, 30, 30
	bne @16
	lha r0, 0x10(r29)
	sth r0, 0x14(r29)
	@16:
	lhz r3, 0x1c(r29)
	clrlwi. r0, r3, 31
	beq @17
	rlwinm. r0, r3, 0, 30, 30
	bne @17
	lha r0, 0x1e(r29)
	sth r0, 0x22(r29)
	@17:
	lhz r3, 0x2a(r29)
	clrlwi. r0, r3, 31
	beq @18
	rlwinm. r0, r3, 0, 30, 30
	bne @18
	lha r0, 0x2c(r29)
	sth r0, 0x30(r29)
	@18:
	addi r29, r29, 0x38
	addi r4, r4, 0x3
	bdnz @14
	li r3, 0x0
	bl pouchAddCoin
	@13:
	lwz r3, 0x1b0(r31)
	subi r0, r3, 0x1
	stw r0, 0x1b0(r31)
	lwz r0, 0x1b0(r31)
	cmpwi r0, 0x0
	bgt @1
	li r0, 0x5
	stw r0, 0x1dc(r31)
	b @1
	@19:
	lwz r0, 0x1b0(r31)
	cmpwi r0, 0x64
	bne @20
	lfs f4, float_50_8041a14c(r0)
	li r3, 0x1
	lfs f2, float_45_8041a1f4(r0)
	li r4, 0x1e
	lfs f0, 0x3c(r31)
	fmr f5, f4
	lfs f1, 0x38(r31)
	li r5, 0x3c
	fadds f2, f2, f0
	lfs f3, 0x40(r31)
	bl effStardustEntry
	addi r4, r31, 0x38
	li r3, 0x1db
	bl psndSFXOn_3D
	@20:
	lwz r0, 0x1b0(r31)
	cmpwi r0, 0x64
	bne @21
	lwz r29, 0x1a4(r31)
	bl marioGetPtr
	mr r30, r3
	bl pouchGetPtr
	lfs f4, float_50_8041a14c(r0)
	mr r28, r3
	lfs f1, 0x8c(r30)
	li r3, 0x2
	fmr f5, f4
	lfs f2, 0x90(r30)
	lfs f3, 0x94(r30)
	li r4, 0x32
	li r5, 0x64
	bl effStardustEntry
	la r3, str_8041A1F8(r0)
	bl marioChgPose
	lha r3, 0x72(r28)
	li r0, 0x2
	li r4, 0x0
	sth r3, 0x70(r28)
	lha r3, 0x76(r28)
	sth r3, 0x74(r28)
	mtctr r0
	@22:
	lhz r3, 0x0(r28)
	clrlwi. r0, r3, 31
	beq @23
	rlwinm. r0, r3, 0, 30, 30
	bne @23
	lha r0, 0x2(r28)
	sth r0, 0x6(r28)
	@23:
	lhz r3, 0xe(r28)
	clrlwi. r0, r3, 31
	beq @24
	rlwinm. r0, r3, 0, 30, 30
	bne @24
	lha r0, 0x10(r28)
	sth r0, 0x14(r28)
	@24:
	lhz r3, 0x1c(r28)
	clrlwi. r0, r3, 31
	beq @25
	rlwinm. r0, r3, 0, 30, 30
	bne @25
	lha r0, 0x1e(r28)
	sth r0, 0x22(r28)
	@25:
	lhz r3, 0x2a(r28)
	clrlwi. r0, r3, 31
	beq @26
	rlwinm. r0, r3, 0, 30, 30
	bne @26
	lha r0, 0x2c(r28)
	sth r0, 0x30(r28)
	@26:
	addi r28, r28, 0x38
	addi r4, r4, 0x3
	bdnz @22
	neg r3, r29
	bl pouchAddCoin
	@21:
	lwz r3, 0x1b0(r31)
	subi r0, r3, 0x1
	stw r0, 0x1b0(r31)
	lwz r0, 0x1b0(r31)
	cmpwi r0, 0x0
	bgt @1
	li r0, 0x5
	stw r0, 0x1dc(r31)
	b @1
	@27:
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @1
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	la r3, str_8041A200(r0)
	bl marioChgPose
	bl marioKeyOn
	bl statusWinForceOff
	li r3, 0x8
	bl camGetPtr
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 23, 21
	sth r0, 0x0(r3)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @1
	@28:
	lwz r0, 0x1c8(r31)
	cmplwi r0, 0x0
	bne @29
	lfs f2, float_25_8041a140(r0)
	li r3, 0x0
	lfs f1, 0x3c(r31)
	li r5, 0x0
	lfs f3, 0x40(r31)
	lfs f0, float_10_8041a1a4(r0)
	fadds f2, f2, f1
	lfs f1, 0x38(r31)
	fsubs f3, f3, f0
	lwz r4, 0x1a4(r31)
	bl effCoinFukidashiEntry
	stw r3, 0x1c8(r31)
	@29:
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @1
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r3, 0x0(r31)
	li r0, 0x0
	rlwinm r3, r3, 0, 29, 27
	stw r3, 0x0(r31)
	stw r0, 0x1dc(r31)
	b @1
	@30:
	lis r3, str_802C442C@ha
	addi r3, r3, str_802C442C@l
	bl msgSearch
	li r4, 0x0
	li r5, 0x0
	bl msgWindow_Entry
	stw r3, 0x1a8(r31)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @1
	@31:
	lwz r3, 0x1a8(r31)
	bl windowCheckID
	cmpwi r3, 0x0
	bne @1
	bl marioKeyOn
	li r3, 0x8
	bl camGetPtr
	lhz r4, 0x0(r3)
	li r0, 0x0
	rlwinm r4, r4, 0, 23, 21
	sth r4, 0x0(r3)
	lwz r3, 0x0(r31)
	rlwinm r3, r3, 0, 29, 27
	stw r3, 0x0(r31)
	stw r0, 0x1dc(r31)
	b @1
	@32:
	lis r3, str_802C4438@ha
	addi r3, r3, str_802C4438@l
	bl msgSearch
	li r4, 0x0
	li r5, 0x0
	bl msgWindow_Entry
	stw r3, 0x1a8(r31)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @1
	@33:
	lwz r3, 0x1a8(r31)
	bl windowCheckID
	cmpwi r3, 0x0
	bne @1
	bl marioKeyOn
	li r3, 0x8
	bl camGetPtr
	lhz r4, 0x0(r3)
	li r0, 0x0
	rlwinm r4, r4, 0, 23, 21
	sth r4, 0x0(r3)
	lwz r3, 0x0(r31)
	rlwinm r3, r3, 0, 29, 27
	stw r3, 0x0(r31)
	stw r0, 0x1dc(r31)
	@1:
	lwz r0, 0x24(r1)
	li r3, 0x0
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm USER_FUNC(evt_mobj_signboard) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x38(r1)
	stfd f30, 0x30(r1)
	stfd f29, 0x28(r1)
	stmw r27, 0x14(r1)
	mr r27, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r29, r3
	mr r3, r27
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r31)
	mr r3, r27
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r31)
	mr r3, r27
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x10(r31)
	mr r3, r27
	bl evtGetValue
	lwz r5, gp(r0)
	lis r4, str_802C4458@ha
	addi r0, r4, str_802C4458@l
	mr r30, r3
	lwz r4, 0x14(r5)
	mr r27, r0
	mr r3, r0
	lwz r28, 0x14(r31)
	neg r0, r4
	li r5, 0x0
	or r0, r0, r4
	srwi r4, r0, 31
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r3, r29
	mr r4, r27
	bl mobjEntry
	mr r3, r29
	bl mobjNameToPtr
	fmr f1, f31
	mr r31, r3
	fmr f2, f30
	mr r3, r29
	fmr f3, f29
	bl mobjSetPosition
	lis r3, mobj_signboard@ha
	li r0, 0x0
	addi r4, r3, mobj_signboard@l
	li r3, 0x2
	stw r4, 0x1d0(r31)
	stw r30, 0x1d4(r31)
	lwz r4, 0x0(r31)
	ori r4, r4, 0x24
	stw r4, 0x0(r31)
	lwz r4, 0x0(r31)
	oris r4, r4, 0x4
	stw r4, 0x0(r31)
	stw r28, 0x1e4(r31)
	stw r0, 0x1dc(r31)
	@2:
	lfd f31, 0x38(r1)
	lfd f30, 0x30(r1)
	lfd f29, 0x28(r1)
	lmw r27, 0x14(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 mobj_signboard(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r0, 0x1dc(r3)
	cmpwi r0, 0x1
	beq @1
	bge @2
	cmpwi r0, 0x0
	bge @3
	b @2
	@3:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @2
	bl marioKeyOff
	lwz r4, 0x1d4(r31)
	mr r3, r31
	bl mobjRunEvent
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @2
	@1:
	lwz r3, 0x1cc(r31)
	bl evtCheckID
	cmpwi r3, 0x1
	beq @2
	bl marioKeyOn
	li r3, 0x0
	stw r3, 0x1cc(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	stw r3, 0x1dc(r31)
	@2:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_itembox) {
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
	stmw r25, 0x64(r1)
	mr r28, r3
	lis r4, vec3_802c3dc8@ha
	lwz r27, 0x18(r3)
	addi r31, r4, vec3_802c3dc8@l
	lwz r4, 0x0(r27)
	bl evtGetValue
	lwz r4, 0x4(r27)
	mr r25, r3
	mr r3, r28
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r27)
	mr r3, r28
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r27)
	mr r3, r28
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x10(r27)
	mr r3, r28
	bl evtGetValue
	lwz r4, 0x14(r27)
	mr r29, r3
	mr r3, r28
	bl evtGetValue
	lwz r4, 0x18(r27)
	mr r26, r3
	mr r3, r28
	bl evtGetValue
	lwz r4, gp(r0)
	cmpwi r29, 0x2
	lwz r30, 0x1c(r27)
	mr r27, r3
	lwz r3, 0x14(r4)
	neg r0, r3
	or r0, r0, r3
	srwi r4, r0, 31
	beq @1
	bge @2
	cmpwi r29, 0x0
	beq @3
	bge @4
	b @5
	@2:
	cmpwi r29, 0x4
	beq @5
	bge @5
	b @6
	@3:
	addi r29, r31, 0x6a0
	b @7
	@4:
	addi r29, r31, 0x6b4
	b @7
	@1:
	addi r29, r31, 0x6c8
	b @7
	@6:
	addi r29, r31, 0x6e0
	b @7
	@5:
	addi r29, r31, 0x6f8
	@7:
	mr r3, r29
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @8
	li r3, 0x0
	b @9
	@8:
	mr r3, r25
	mr r4, r29
	bl mobjEntry
	mr r3, r25
	bl mobjNameToPtr
	li r4, 0x2
	mr r29, r3
	bl mobjHitEntry
	fmr f1, f31
	mr r3, r25
	fmr f2, f30
	fmr f3, f29
	bl mobjSetPosition
	lis r3, mobj_itembox@ha
	li r0, 0x0
	addi r4, r3, mobj_itembox@l
	mr r3, r29
	stw r4, 0x1d0(r29)
	stw r26, 0x1d4(r29)
	stw r27, 0x1d8(r29)
	lwz r4, 0x0(r29)
	ori r4, r4, 0x64
	stw r4, 0x0(r29)
	lwz r4, 0x0(r29)
	oris r4, r4, 0x4
	stw r4, 0x0(r29)
	stw r30, 0x1e4(r29)
	stw r0, 0x1dc(r29)
	bl mobjCalcMtx
	mr r3, r28
	mr r4, r30
	bl evtGetValue
	cmpwi r3, 0x0
	beq @10
	lwz r3, 0x70(r29)
	bl animPoseGetAnimBaseDataPtr
	lwz r7, 0x210(r31)
	addi r4, r1, 0x24
	lwz r0, 0x214(r31)
	addi r5, r29, 0x190
	lwz r6, 0x218(r31)
	stw r7, 0x3c(r1)
	lfs f1, 0xd0(r3)
	stw r0, 0x40(r1)
	lfs f0, 0xd4(r3)
	stfs f1, 0x3c(r1)
	lwz r0, 0x220(r31)
	stfs f0, 0x40(r1)
	lfs f0, 0xd8(r3)
	stw r6, 0x44(r1)
	lwz r8, 0x3c(r1)
	stfs f0, 0x44(r1)
	lwz r7, 0x40(r1)
	lwz r6, 0x44(r1)
	stw r7, 0x28(r1)
	lwz r7, 0x21c(r31)
	stw r6, 0x2c(r1)
	lfs f1, 0x28(r1)
	stw r8, 0x24(r1)
	lwz r6, 0x224(r31)
	stw r0, 0x4c(r1)
	lfs f0, 0xe0(r3)
	lfs f5, 0xdc(r3)
	stfs f0, 0x4c(r1)
	lfs f4, 0xe4(r3)
	addi r3, r1, 0x30
	lwz r0, 0x4c(r1)
	stw r7, 0x48(r1)
	lfd f3, 0x710(r31)
	stw r0, 0x34(r1)
	lfs f0, 0x2c(r1)
	lfs f2, 0x34(r1)
	stw r6, 0x50(r1)
	fsubs f1, f2, f1
	stfs f5, 0x48(r1)
	fabs f1, f1
	stfs f4, 0x50(r1)
	lwz r6, 0x48(r1)
	lwz r0, 0x50(r1)
	fnmsub f0, f3, f1, f0
	stw r6, 0x30(r1)
	stw r0, 0x38(r1)
	frsp f0, f0
	stfs f0, 0x2c(r1)
	bl PSVECAdd
	addi r3, r29, 0x190
	lfs f1, float_0p5_8041a15c(r0)
	mr r4, r3
	bl PSVECScale
	addi r3, r29, 0x190
	lfs f1, float_10_8041a1a4(r0)
	mr r4, r3
	bl PSVECScale
	lfs f0, float_0_8041a150(r0)
	mr r3, r29
	lfs f1, float_1p4_8041a208(r0)
	stfs f0, 0x194(r29)
	lfs f0, float_1p2_8041a20c(r0)
	lfs f2, 0x188(r29)
	fmuls f1, f2, f1
	stfs f1, 0x188(r29)
	lfs f1, 0x18c(r29)
	fmuls f0, f1, f0
	stfs f0, 0x18c(r29)
	bl mobjCalcMtx2
	li r0, 0x63
	stw r0, 0x1dc(r29)
	@10:
	lfs f0, 0x60(r29)
	addi r4, r1, 0x20
	lfs f4, float_0_8041a150(r0)
	addi r5, r1, 0x1c
	fabs f0, f0
	lfs f1, float_5_8041a210(r0)
	lfs f2, float_1_8041a160(r0)
	fmr f6, f4
	lfs f5, float_neg1_8041a214(r0)
	addi r6, r1, 0x18
	frsp f0, f0
	addi r7, r1, 0x14
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	li r3, 0x0
	fadds f0, f1, f0
	stfs f0, 0x14(r1)
	lfs f0, 0x3c(r29)
	lfs f1, 0x38(r29)
	fadds f2, f2, f0
	lfs f3, 0x40(r29)
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @11
	lwz r0, 0x0(r29)
	ori r0, r0, 0x2
	stw r0, 0x0(r29)
	lwz r0, 0x0(r29)
	rlwinm r0, r0, 0, 26, 24
	stw r0, 0x0(r29)
	@11:
	li r3, 0x2
	@9:
	psq_l f31, 0xa8(r1), 0, 0
	lfd f31, 0xa0(r1)
	psq_l f30, 0x98(r1), 0, 0
	lfd f30, 0x90(r1)
	psq_l f29, 0x88(r1), 0, 0
	lfd f29, 0x80(r1)
	lmw r25, 0x64(r1)
	lwz r0, 0xb4(r1)
	mtlr r0
	addi r1, r1, 0xb0
	blr
}

asm s32 mobj_itembox(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	lis r4, fd_evt_mobj_negone_one_374@ha
	stw r0, 0x64(r1)
	stw r31, 0x5c(r1)
	mr r31, r3
	stw r30, 0x58(r1)
	stw r29, 0x54(r1)
	addi r29, r4, fd_evt_mobj_negone_one_374@l
	lwz r0, 0x1dc(r3)
	lis r3, vec3_802c3dc8@ha
	addi r30, r3, vec3_802c3dc8@l
	cmpwi r0, 0x3
	beq @1
	bge @2
	cmpwi r0, 0x1
	beq @3
	bge @4
	cmpwi r0, 0x0
	bge @5
	b @6
	@2:
	cmpwi r0, 0x63
	beq @7
	b @6
	@5:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @6
	bl marioKeyOff
	bl partyKeyOff
	li r3, 0x1
	bl marioStSystemLevel
	li r0, 0x0
	mr r3, r31
	stw r0, 0x1cc(r31)
	lwz r4, 0x1d4(r31)
	bl mobjRunEvent
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @6
	@3:
	lwz r3, 0x1cc(r31)
	cmpwi r3, 0x0
	beq @8
	bl evtCheckID
	cmpwi r3, 0x1
	beq @6
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 19, 19
	beq @8
	rlwinm r0, r3, 0, 20, 18
	stw r0, 0x0(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	bl marioKeyOn
	bl partyKeyOn
	li r3, 0x0
	bl marioStSystemLevel
	li r0, 0x0
	stw r0, 0x1cc(r31)
	stw r0, 0x1dc(r31)
	b @6
	@8:
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @6
	@4:
	addi r3, r31, 0x15
	addi r4, r30, 0x6a0
	bl strcmp
	cmpwi r3, 0x0
	beq @9
	addi r3, r31, 0x15
	addi r4, r30, 0x6c8
	bl strcmp
	cmpwi r3, 0x0
	bne @10
	@9:
	addi r3, r29, 0x90
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	bl evtEntryType
	lfs f1, float_1024_8041a1a0(r0)
	lfs f0, 0x38(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x38(r1)
	lwz r4, 0x3c(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0x9c(r3)
	lfs f0, 0x3c(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x40(r1)
	lwz r4, 0x44(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0xa0(r3)
	lfs f0, 0x40(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x48(r1)
	lwz r4, 0x4c(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0xa4(r3)
	b @11
	@10:
	addi r3, r31, 0x15
	addi r4, r30, 0x6e0
	bl strcmp
	cmpwi r3, 0x0
	bne @12
	addi r3, r29, 0x130
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	bl evtEntryType
	lfs f1, float_1024_8041a1a0(r0)
	lfs f0, 0x38(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x48(r1)
	lwz r4, 0x4c(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0x9c(r3)
	lfs f0, 0x3c(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x40(r1)
	lwz r4, 0x44(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0xa0(r3)
	lfs f0, 0x40(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x38(r1)
	lwz r4, 0x3c(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0xa4(r3)
	b @11
	@12:
	addi r3, r29, 0xe0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	bl evtEntryType
	lfs f1, float_1024_8041a1a0(r0)
	lfs f0, 0x38(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x48(r1)
	lwz r4, 0x4c(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0x9c(r3)
	lfs f0, 0x3c(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x40(r1)
	lwz r4, 0x44(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0xa0(r3)
	lfs f0, 0x40(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x38(r1)
	lwz r4, 0x3c(r1)
	subis r4, r4, 0xdb6
	addi r0, r4, 0x7a80
	stw r0, 0xa4(r3)
	@11:
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x0
	mr r3, r31
	stw r0, 0x1cc(r31)
	lwz r4, 0x1d8(r31)
	bl mobjRunEvent
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @6
	@1:
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @6
	lwz r3, 0x1cc(r31)
	cmpwi r3, 0x0
	beq @13
	bl evtCheckID
	cmpwi r3, 0x1
	beq @6
	@13:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 27, 25
	stw r0, 0x0(r31)
	lwz r3, 0x70(r31)
	bl animPoseGetAnimBaseDataPtr
	lwz r7, 0x210(r30)
	addi r4, r1, 0x8
	lwz r0, 0x214(r30)
	addi r5, r31, 0x190
	lwz r6, 0x218(r30)
	stw r7, 0x20(r1)
	lfs f1, 0xd0(r3)
	stw r0, 0x24(r1)
	lfs f0, 0xd4(r3)
	stfs f1, 0x20(r1)
	lwz r0, 0x220(r30)
	stfs f0, 0x24(r1)
	lfs f0, 0xd8(r3)
	stw r6, 0x28(r1)
	lwz r8, 0x20(r1)
	stfs f0, 0x28(r1)
	lwz r7, 0x24(r1)
	lwz r6, 0x28(r1)
	stw r7, 0xc(r1)
	lwz r7, 0x21c(r30)
	stw r6, 0x10(r1)
	lfs f1, 0xc(r1)
	stw r8, 0x8(r1)
	lwz r6, 0x224(r30)
	stw r0, 0x30(r1)
	lfs f0, 0xe0(r3)
	lfs f5, 0xdc(r3)
	stfs f0, 0x30(r1)
	lfs f4, 0xe4(r3)
	addi r3, r1, 0x14
	lwz r0, 0x30(r1)
	stw r7, 0x2c(r1)
	lfd f3, 0x710(r30)
	stw r0, 0x18(r1)
	lfs f0, 0x10(r1)
	lfs f2, 0x18(r1)
	stw r6, 0x34(r1)
	fsubs f1, f2, f1
	stfs f5, 0x2c(r1)
	fabs f1, f1
	stfs f4, 0x34(r1)
	lwz r6, 0x2c(r1)
	lwz r0, 0x34(r1)
	fnmsub f0, f3, f1, f0
	stw r6, 0x14(r1)
	stw r0, 0x1c(r1)
	frsp f0, f0
	stfs f0, 0x10(r1)
	bl PSVECAdd
	addi r3, r31, 0x190
	lfs f1, float_0p5_8041a15c(r0)
	mr r4, r3
	bl PSVECScale
	addi r3, r31, 0x190
	lfs f1, float_10_8041a1a4(r0)
	mr r4, r3
	bl PSVECScale
	lfs f0, float_0_8041a150(r0)
	mr r3, r31
	lfs f1, float_1p4_8041a208(r0)
	stfs f0, 0x194(r31)
	lfs f0, float_1p2_8041a20c(r0)
	lfs f2, 0x188(r31)
	fmuls f1, f2, f1
	stfs f1, 0x188(r31)
	lfs f1, 0x18c(r31)
	fmuls f0, f1, f0
	stfs f0, 0x18c(r31)
	bl mobjCalcMtx2
	bl marioKeyOn
	bl partyKeyOn
	li r3, 0x0
	bl marioStSystemLevel
	li r3, 0x0
	li r0, 0x63
	stw r3, 0x1cc(r31)
	stw r0, 0x1dc(r31)
	b @6
	@7:
	lwz r4, 0x1e4(r31)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	lwz r0, 0x0(r31)
	addi r3, r31, 0x15
	addi r4, r30, 0x6e0
	ori r0, r0, 0x8
	stw r0, 0x0(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 27, 25
	stw r0, 0x0(r31)
	bl strcmp
	cmpwi r3, 0x0
	bne @14
	lwz r3, 0x70(r31)
	la r4, str_8041A218(r0)
	li r5, 0x1
	bl animPoseSetAnim
	b @6
	@14:
	lwz r3, 0x70(r31)
	la r4, str_8041A1C0(r0)
	li r5, 0x1
	bl animPoseSetAnim
	@6:
	lwz r0, 0x64(r1)
	li r3, 0x0
	lwz r31, 0x5c(r1)
	lwz r30, 0x58(r1)
	lwz r29, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm USER_FUNC(evt_mobj_lock) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	addi r11, r1, 0x50
	bl _savefpr_28
	stmw r25, 0x14(r1)
	mr r26, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lwz r4, 0x4(r30)
	mr r27, r3
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x8(r30)
	mr r28, r3
	mr r3, r26
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r30)
	mr r3, r26
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x10(r30)
	mr r3, r26
	bl evtGetFloat
	fmr f28, f1
	lwz r4, 0x14(r30)
	mr r3, r26
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x18(r30)
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x1c(r30)
	mr r29, r3
	mr r3, r26
	bl evtGetValue
	lwz r5, gp(r0)
	lis r4, str_802C44E0@ha
	lwz r31, 0x20(r30)
	addi r0, r4, str_802C44E0@l
	lwz r5, 0x14(r5)
	mr r30, r3
	mr r25, r0
	mr r3, r26
	neg r0, r5
	mr r4, r31
	or r0, r0, r5
	srwi r26, r0, 31
	bl evtGetValue
	cmpwi r3, 0x0
	beq @1
	li r3, 0x2
	b @2
	@1:
	mr r3, r25
	mr r4, r26
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @3
	li r3, 0x0
	b @2
	@3:
	mr r3, r27
	mr r4, r25
	bl mobjEntry
	mr r3, r27
	bl mobjNameToPtr
	li r4, 0x2
	mr r26, r3
	bl mobjHitEntry
	fmr f1, f30
	stw r28, 0x1a0(r26)
	fmr f2, f29
	mr r3, r27
	fmr f3, f28
	bl mobjSetPosition
	lis r3, mobj_lock@ha
	stfs f31, 0x54(r26)
	addi r3, r3, mobj_lock@l
	li r0, 0x0
	stw r3, 0x1d0(r26)
	mr r3, r26
	stw r29, 0x1d4(r26)
	stw r30, 0x1d8(r26)
	lwz r4, 0x0(r26)
	ori r4, r4, 0x26
	stw r4, 0x0(r26)
	lwz r4, 0x0(r26)
	oris r4, r4, 0x4
	stw r4, 0x0(r26)
	stw r31, 0x1e4(r26)
	stw r0, 0x1dc(r26)
	bl mobjCalcMtx
	lwz r3, 0x70(r26)
	la r4, str_8041A21C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r3, 0x2
	@2:
	addi r11, r1, 0x50
	bl _restfpr_28
	lmw r25, 0x14(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm s32 mobj_lock(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stw r31, 0x4c(r1)
	mr r31, r3
	stw r30, 0x48(r1)
	stw r29, 0x44(r1)
	lwz r0, 0x1dc(r3)
	cmpwi r0, 0x5
	beq @1
	bge @2
	cmpwi r0, 0x2
	beq @3
	bge @4
	cmpwi r0, 0x0
	beq @5
	bge @6
	b @7
	@4:
	cmpwi r0, 0x4
	bge @8
	b @9
	@2:
	cmpwi r0, 0xa
	beq @10
	bge @11
	cmpwi r0, 0x7
	bge @7
	b @12
	@11:
	cmpwi r0, 0x63
	beq @13
	b @7
	@5:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @7
	bl marioKeyOff
	bl partyKeyOff
	li r3, 0x1
	bl marioStSystemLevel
	lwz r4, 0x1d4(r31)
	mr r3, r31
	bl mobjRunEvent
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @7
	@6:
	lwz r3, 0x1cc(r31)
	bl evtCheckID
	cmpwi r3, 0x1
	beq @7
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 19, 19
	beq @14
	rlwinm r0, r3, 0, 20, 18
	stw r0, 0x0(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	bl marioKeyOn
	bl partyKeyOn
	li r3, 0x0
	bl marioStSystemLevel
	li r0, 0x0
	stw r0, 0x1cc(r31)
	stw r0, 0x1dc(r31)
	b @7
	@14:
	li r0, 0x0
	stw r0, 0x1cc(r31)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @7
	@3:
	lwz r3, 0x1a0(r31)
	clrrwi. r0, r3, 31
	beq @15
	li r29, 0x0
	li r30, 0x0
	@16:
	lwz r3, 0x1a0(r31)
	lwzx r3, r3, r30
	cmpwi r3, -0x1
	beq @17
	bl pouchCheckItem
	cmpwi r3, 0x0
	beq @18
	mr r29, r3
	b @17
	@18:
	addi r30, r30, 0x4
	b @16
	@15:
	bl pouchCheckItem
	cmpwi r3, 0x0
	beq @19
	lwz r29, 0x1a0(r31)
	b @17
	@19:
	li r29, 0x0
	@17:
	cmpwi r29, 0x0
	beq @20
	mr r3, r29
	bl pouchRemoveItem
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @7
	@20:
	lis r3, str_802C44EC@ha
	addi r3, r3, str_802C44EC@l
	bl msgSearch
	li r4, 0x0
	li r5, 0x0
	bl msgWindow_Entry
	stw r3, 0x1a8(r31)
	li r0, 0xa
	stw r0, 0x1dc(r31)
	b @7
	@9:
	lis r3, evt_lock_sound@ha
	li r4, 0x0
	addi r3, r3, evt_lock_sound@l
	li r5, 0x0
	li r6, 0x0
	bl evtEntryType
	lfs f1, float_1024_8041a1a0(r0)
	la r4, str_8041A12C(r0)
	lfs f0, 0x38(r31)
	li r5, 0x1
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x28(r1)
	lwz r6, 0x2c(r1)
	subis r6, r6, 0xdb6
	addi r0, r6, 0x7a80
	stw r0, 0x9c(r3)
	lfs f0, 0x3c(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x30(r1)
	lwz r6, 0x34(r1)
	subis r6, r6, 0xdb6
	addi r0, r6, 0x7a80
	stw r0, 0xa0(r3)
	lfs f0, 0x40(r31)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x38(r1)
	lwz r6, 0x3c(r1)
	subis r6, r6, 0xdb6
	addi r0, r6, 0x7a80
	stw r0, 0xa4(r3)
	lwz r3, 0x70(r31)
	bl animPoseSetAnim
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @7
	@8:
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @7
	lfs f1, float_0_8041a150(r0)
	li r3, 0x0
	lfs f0, float_0p5_8041a15c(r0)
	li r5, 0x1
	stfs f1, 0x60(r31)
	stfs f0, 0x68(r31)
	stfs f1, 0x6c(r31)
	lwz r4, 0x1e4(r31)
	bl evtSetValue
	lwz r4, 0x1d8(r31)
	mr r3, r31
	bl mobjRunEvent
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @7
	@1:
	lfs f0, 0x60(r31)
	addi r4, r1, 0x20
	lfs f4, float_0_8041a150(r0)
	addi r5, r1, 0x1c
	fabs f0, f0
	lfs f2, float_1_8041a160(r0)
	fmr f6, f4
	addi r6, r1, 0x18
	addi r7, r1, 0x14
	addi r8, r1, 0x10
	frsp f0, f0
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	li r3, 0x0
	fadds f0, f2, f0
	stfs f0, 0x14(r1)
	lfs f0, 0x3c(r31)
	lfs f1, 0x38(r31)
	fadds f2, f2, f0
	lfs f3, 0x40(r31)
	lfs f5, 0x60(r31)
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @21
	lfs f0, 0x1c(r1)
	lfs f2, float_neg0p8_8041a220(r0)
	stfs f0, 0x3c(r31)
	lfs f1, float_1_8041a160(r0)
	lfs f3, 0x60(r31)
	lfs f0, float_4_8041a224(r0)
	fmuls f2, f3, f2
	stfs f2, 0x60(r31)
	lfs f2, 0x6c(r31)
	fadds f1, f2, f1
	stfs f1, 0x6c(r31)
	lfs f1, 0x6c(r31)
	fcmpo cr0, f1, f0
	bge @22
	addi r4, r31, 0x38
	li r3, 0x1e6
	bl psndSFXOn_3D
	b @22
	@21:
	lfs f1, 0x3c(r31)
	lfs f0, 0x60(r31)
	fadds f0, f1, f0
	stfs f0, 0x3c(r31)
	lfs f1, 0x60(r31)
	lfs f0, 0x68(r31)
	fsubs f0, f1, f0
	stfs f0, 0x60(r31)
	@22:
	lfs f1, 0x6c(r31)
	lfs f0, float_4_8041a224(r0)
	fcmpo cr0, f1, f0
	blt @7
	lwz r3, 0x1cc(r31)
	bl evtCheckID
	cmpwi r3, 0x1
	beq @7
	lwz r3, 0x1dc(r31)
	li r0, 0x14
	addi r3, r3, 0x1
	stw r3, 0x1dc(r31)
	stw r0, 0x1b0(r31)
	b @7
	@12:
	lwz r3, 0x1b0(r31)
	subi r0, r3, 0x1
	stw r0, 0x1b0(r31)
	lwz r0, 0x1b0(r31)
	rlwinm. r0, r0, 0, 30, 30
	beq @23
	lwz r0, 0x0(r31)
	ori r0, r0, 0x4000
	stw r0, 0x0(r31)
	b @24
	@23:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 18, 16
	stw r0, 0x0(r31)
	@24:
	lwz r0, 0x1b0(r31)
	cmpwi r0, 0x0
	bne @7
	li r0, 0x63
	stw r0, 0x1dc(r31)
	b @7
	@10:
	lwz r3, 0x1a8(r31)
	bl windowCheckID
	cmpwi r3, 0x0
	bne @7
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	bl marioKeyOn
	bl partyKeyOn
	li r3, 0x0
	bl marioStSystemLevel
	li r0, 0x0
	stw r0, 0x1dc(r31)
	b @7
	@13:
	bl marioKeyOn
	bl partyKeyOn
	li r3, 0x0
	bl marioStSystemLevel
	addi r3, r31, 0x5
	bl mobjDelete
	@7:
	lwz r0, 0x54(r1)
	li r3, 0x0
	lwz r31, 0x4c(r1)
	lwz r30, 0x48(r1)
	lwz r29, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm USER_FUNC(evt_mobj_lock_unlock) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	bl mobjNameToPtr
	lis r4, str_802C44E0@ha
	mr r31, r3
	addi r4, r4, str_802C44E0@l
	addi r3, r31, 0x15
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	li r3, 0x2
	b @2
	@1:
	lwz r0, 0x1d0(r31)
	cmplwi r0, 0x0
	bne @3
	lis r3, mobj_lock@ha
	addi r0, r3, mobj_lock@l
	stw r0, 0x1d0(r31)
	@3:
	lwz r0, 0x0(r31)
	ori r0, r0, 0x8
	stw r0, 0x0(r31)
	bl marioKeyOff
	bl partyKeyOff
	li r3, 0x1
	bl marioStSystemLevel
	li r0, 0x3
	li r3, 0x2
	stw r0, 0x1dc(r31)
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_switch_float_blk) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stfd f30, 0x50(r1)
	psq_st f30, 0x58(r1), 0, 0
	stfd f29, 0x40(r1)
	psq_st f29, 0x48(r1), 0, 0
	stmw r26, 0x28(r1)
	mr r30, r3
	lis r4, vec3_802c3dc8@ha
	lwz r29, 0x18(r3)
	addi r28, r4, vec3_802c3dc8@l
	lwz r4, 0x0(r29)
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r27, r3
	mr r3, r30
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r29)
	mr r3, r30
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r29)
	mr r3, r30
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x10(r29)
	mr r3, r30
	bl evtGetValue
	lwz r26, 0x14(r29)
	mr r31, r3
	lwz r4, 0x18(r29)
	mr r3, r30
	bl evtGetValue
	lwz r4, gp(r0)
	cmpwi r26, 0x2
	lwz r30, 0x1c(r29)
	mr r29, r3
	lwz r3, 0x14(r4)
	neg r0, r3
	or r0, r0, r3
	srwi r4, r0, 31
	beq @1
	bge @2
	cmpwi r26, 0x0
	beq @3
	bge @4
	b @5
	@2:
	cmpwi r26, 0x4
	bge @5
	b @6
	@3:
	addi r26, r28, 0x730
	b @7
	@4:
	addi r26, r28, 0x74c
	b @7
	@1:
	addi r26, r28, 0x768
	b @7
	@6:
	addi r26, r28, 0x784
	b @7
	@5:
	addi r26, r28, 0x730
	@7:
	mr r3, r26
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @8
	li r3, 0x0
	b @9
	@8:
	mr r3, r27
	mr r4, r26
	bl mobjEntry
	mr r3, r27
	bl mobjNameToPtr
	fmr f1, f31
	mr r26, r3
	fmr f2, f30
	mr r3, r27
	fmr f3, f29
	bl mobjSetPosition
	lis r3, mobj_switch_float_blk@ha
	li r0, 0x0
	addi r4, r3, mobj_switch_float_blk@l
	mr r3, r26
	stw r4, 0x1d0(r26)
	stw r29, 0x1d4(r26)
	lwz r4, 0x0(r26)
	ori r4, r4, 0x4
	stw r4, 0x0(r26)
	lwz r4, 0x0(r26)
	oris r4, r4, 0xe1
	stw r4, 0x0(r26)
	stw r30, 0x1e4(r26)
	stw r0, 0x1dc(r26)
	stw r0, 0x1b0(r26)
	bl mobjCalcMtx
	mr r4, r31
	addi r3, r26, 0x1b8
	bl strcpy
	lbz r0, 0x1b8(r26)
	extsb. r0, r0
	beq @10
	addi r3, r26, 0x1b8
	bl mobjNameToPtr
	mr r30, r3
	addi r4, r26, 0x5
	addi r3, r30, 0x1b8
	bl strcpy
	lfs f0, 0x60(r30)
	addi r4, r1, 0x8
	lfs f4, float_0_8041a150(r0)
	addi r5, r1, 0xc
	fabs f0, f0
	lfs f1, float_1_8041a160(r0)
	lfs f2, float_0p5_8041a15c(r0)
	fmr f6, f4
	lfs f5, float_neg1_8041a214(r0)
	addi r6, r1, 0x10
	frsp f0, f0
	addi r7, r1, 0x14
	addi r8, r1, 0x18
	addi r9, r1, 0x1c
	addi r10, r1, 0x20
	li r3, 0x0
	fadds f0, f1, f0
	stfs f0, 0x14(r1)
	lfs f0, 0x3c(r30)
	lfs f1, 0x38(r30)
	fadds f2, f2, f0
	lfs f3, 0x40(r30)
	bl hitCheckFilter
	cmpwi r3, 0x0
	beq @11
	lwz r3, 0x70(r26)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	b @10
	@11:
	lwz r3, 0x70(r26)
	la r4, str_8041A120(r0)
	li r5, 0x1
	bl animPoseSetAnim
	@10:
	li r3, 0x2
	@9:
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	psq_l f30, 0x58(r1), 0, 0
	lfd f30, 0x50(r1)
	psq_l f29, 0x48(r1), 0, 0
	lfd f29, 0x40(r1)
	lmw r26, 0x28(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm s32 mobj_switch_float_blk(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stmw r27, 0x4c(r1)
	mr r31, r3
	lwz r0, 0x1dc(r3)
	cmpwi r0, 0x2
	beq @1
	bge @2
	cmpwi r0, 0x0
	beq @3
	bge @4
	b @5
	@2:
	cmpwi r0, 0xb
	beq @6
	bge @5
	cmpwi r0, 0xa
	bge @7
	b @5
	@3:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @5
	lwz r3, 0x70(r31)
	bl animPoseGetCurrentAnim
	li r29, 0x0
	mr r28, r3
	la r27, _switch_anim(r0)
	mr r30, r29
	@8:
	lwz r3, 0x0(r27)
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	bne @9
	mr r29, r30
	b @10
	@9:
	addi r30, r30, 0x1
	addi r27, r27, 0x4
	cmpwi r30, 0x6
	blt @8
	@10:
	lwz r0, 0x1a4(r31)
	rlwinm r0, r0, 0, 1, 1
	or r0, r0, r29
	stw r0, 0x1a4(r31)
	lbz r0, 0x1b8(r31)
	extsb. r0, r0
	beq @11
	addi r3, r31, 0x1b8
	bl mobjNameToPtr
	mr r11, r3
	lfs f4, float_0_8041a150(r0)
	lfs f0, 0x60(r3)
	addi r4, r1, 0x24
	lfs f1, float_1_8041a160(r0)
	fmr f6, f4
	fabs f0, f0
	lfs f2, float_0p5_8041a15c(r0)
	lfs f5, float_neg1_8041a214(r0)
	addi r5, r1, 0x28
	addi r6, r1, 0x2c
	frsp f0, f0
	addi r7, r1, 0x30
	addi r8, r1, 0x34
	addi r9, r1, 0x38
	addi r10, r1, 0x3c
	fadds f0, f1, f0
	li r3, 0x0
	stfs f0, 0x30(r1)
	lfs f0, 0x3c(r11)
	lfs f1, 0x38(r11)
	fadds f2, f2, f0
	lfs f3, 0x40(r11)
	bl hitCheckFilter
	cmpwi r3, 0x0
	beq @12
	lwz r3, 0x1cc(r31)
	bl evtCheckID
	cmpwi r3, 0x0
	beq @13
	lwz r3, 0x70(r31)
	bl animPoseGetCurrentAnim
	lbz r0, 0x0(r3)
	cmpwi r0, 0x41
	bne @14
	lbz r0, 0x2(r3)
	extsb r0, r0
	cmpwi r0, 0x31
	blt @14
	cmpwi r0, 0x33
	bgt @14
	li r0, 0x1
	b @15
	@14:
	li r0, 0x0
	@15:
	cmpwi r0, 0x0
	beq @16
	li r27, 0x0
	b @17
	@16:
	li r27, 0x3
	b @17
	@13:
	lwz r0, 0x1a4(r31)
	li r27, 0x0
	oris r0, r0, 0x8000
	stw r0, 0x1a4(r31)
	b @17
	@12:
	lwz r3, 0x1cc(r31)
	bl evtCheckID
	cmpwi r3, 0x0
	beq @18
	lwz r3, 0x70(r31)
	bl animPoseGetCurrentAnim
	lbz r4, 0x0(r3)
	cmpwi r4, 0x41
	bne @19
	lbz r0, 0x2(r3)
	extsb r0, r0
	cmpwi r0, 0x31
	blt @19
	cmpwi r0, 0x32
	bgt @19
	li r27, 0x0
	b @17
	@19:
	extsb r0, r4
	cmpwi r0, 0x41
	bne @20
	lbz r0, 0x2(r3)
	cmpwi r0, 0x33
	bne @20
	lwz r0, 0x1a4(r31)
	li r27, 0x0
	oris r0, r0, 0x4000
	stw r0, 0x1a4(r31)
	b @17
	@20:
	extsb r0, r4
	cmpwi r0, 0x41
	bne @21
	lbz r0, 0x2(r3)
	extsb r0, r0
	cmpwi r0, 0x34
	blt @21
	cmpwi r0, 0x35
	bgt @21
	li r27, 0x3
	b @17
	@21:
	li r27, 0x3
	b @17
	@18:
	lwz r0, 0x1a4(r31)
	li r27, 0x3
	oris r0, r0, 0x8000
	stw r0, 0x1a4(r31)
	b @17
	@11:
	lwz r3, 0x70(r31)
	bl animPoseGetCurrentAnim
	lbz r0, 0x0(r3)
	cmpwi r0, 0x41
	bne @22
	lbz r0, 0x2(r3)
	extsb r0, r0
	cmpwi r0, 0x31
	blt @22
	cmpwi r0, 0x33
	bgt @22
	li r4, 0x1
	b @23
	@22:
	li r4, 0x0
	@23:
	lwz r0, 0x1a4(r31)
	neg r3, r4
	or r4, r3, r4
	li r3, 0x3
	oris r0, r0, 0x8000
	srawi r4, r4, 31
	stw r0, 0x1a4(r31)
	and r27, r3, r4
	@17:
	lwz r4, 0x1d4(r31)
	mr r3, r31
	bl mobjRunEvent
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x20
	cmplwi r0, 0x0
	bne @24
	li r3, 0x5
	bl marioChgMot
	@24:
	addi r4, r31, 0x38
	li r3, 0x1b5
	bl psndSFXOn_3D
	lwz r3, 0x1e0(r31)
	lis r0, 0x40
	cmpw r3, r0
	beq @25
	b @26
	@25:
	slwi r0, r27, 2
	la r3, _switch_anim(r0)
	add r4, r3, r0
	lwz r3, 0x70(r31)
	lwz r4, 0x4(r4)
	li r5, 0x1
	bl animPoseSetAnim
	b @27
	@26:
	slwi r0, r27, 2
	la r4, _switch_anim(r0)
	lwz r3, 0x70(r31)
	li r5, 0x1
	lwzx r4, r4, r0
	bl animPoseSetAnim
	@27:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	lwz r0, 0x1b0(r31)
	cmpwi r0, 0x0
	beq @28
	li r0, 0xa
	stw r0, 0x1dc(r31)
	b @5
	@28:
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @5
	@4:
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 28, 28
	beq @29
	li r0, 0x0
	stw r0, 0x1dc(r31)
	b @5
	@29:
	rlwinm. r0, r3, 0, 19, 19
	beq @30
	rlwinm r3, r3, 0, 20, 18
	li r0, 0xa
	stw r3, 0x0(r31)
	stw r0, 0x1dc(r31)
	b @5
	@30:
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @5
	lbz r0, 0x1b8(r31)
	extsb. r0, r0
	beq @31
	addi r3, r31, 0x1b8
	bl mobjNameToPtr
	@31:
	lwz r3, 0x70(r31)
	bl animPoseGetCurrentAnim
	lbz r0, 0x0(r3)
	cmpwi r0, 0x41
	bne @32
	lbz r0, 0x2(r3)
	extsb r0, r0
	cmpwi r0, 0x31
	blt @32
	cmpwi r0, 0x33
	bgt @32
	li r0, 0x1
	b @33
	@32:
	li r0, 0x0
	@33:
	cmpwi r0, 0x0
	la r4, str_8041A12C(r0)
	beq @34
	la r4, str_8041A120(r0)
	@34:
	lwz r3, 0x70(r31)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @5
	@1:
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 28, 28
	beq @35
	li r0, 0x0
	stw r0, 0x1dc(r31)
	b @5
	@35:
	rlwinm. r0, r3, 0, 19, 19
	beq @36
	rlwinm r3, r3, 0, 20, 18
	li r0, 0xa
	stw r3, 0x0(r31)
	stw r0, 0x1dc(r31)
	@36:
	lwz r3, 0x1cc(r31)
	bl evtCheckID
	cmpwi r3, 0x0
	bne @5
	li r0, 0x0
	stw r0, 0x1dc(r31)
	stw r0, 0x1a4(r31)
	b @5
	@7:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @37
	li r0, 0x0
	stw r0, 0x1dc(r31)
	b @5
	@37:
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @5
	lwz r3, 0x70(r31)
	bl animPoseGetCurrentAnim
	lbz r0, 0x0(r3)
	cmpwi r0, 0x41
	bne @38
	lbz r0, 0x2(r3)
	extsb r0, r0
	cmpwi r0, 0x31
	blt @38
	cmpwi r0, 0x33
	bgt @38
	li r0, 0x1
	b @39
	@38:
	li r0, 0x0
	@39:
	cmpwi r0, 0x0
	beq @40
	lwz r3, 0x70(r31)
	la r4, str_8041A120(r0)
	li r5, 0x1
	bl animPoseSetAnim
	b @41
	@40:
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	@41:
	li r0, 0x78
	stw r0, 0x1b0(r31)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	@6:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @42
	li r0, 0x0
	stw r0, 0x1dc(r31)
	b @5
	@42:
	lwz r3, 0x1b0(r31)
	subi r0, r3, 0x1
	stw r0, 0x1b0(r31)
	lwz r0, 0x1b0(r31)
	cmpwi r0, 0x0
	bne @5
	lbz r0, 0x1b8(r31)
	extsb. r0, r0
	beq @43
	addi r3, r31, 0x1b8
	bl mobjNameToPtr
	mr r11, r3
	lfs f4, float_0_8041a150(r0)
	lfs f0, 0x60(r3)
	addi r4, r1, 0x8
	lfs f1, float_1_8041a160(r0)
	fmr f6, f4
	fabs f0, f0
	lfs f2, float_0p5_8041a15c(r0)
	lfs f5, float_neg1_8041a214(r0)
	addi r5, r1, 0xc
	addi r6, r1, 0x10
	frsp f0, f0
	addi r7, r1, 0x14
	addi r8, r1, 0x18
	addi r9, r1, 0x1c
	addi r10, r1, 0x20
	fadds f0, f1, f0
	li r3, 0x0
	stfs f0, 0x14(r1)
	lfs f0, 0x3c(r11)
	lfs f1, 0x38(r11)
	fadds f2, f2, f0
	lfs f3, 0x40(r11)
	bl hitCheckFilter
	cmpwi r3, 0x0
	beq @44
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x0
	bl animPoseSetAnim
	b @45
	@44:
	lwz r3, 0x70(r31)
	la r4, str_8041A120(r0)
	li r5, 0x0
	bl animPoseSetAnim
	b @45
	@43:
	lwz r3, 0x70(r31)
	bl animPoseGetCurrentAnim
	lbz r0, 0x0(r3)
	cmpwi r0, 0x41
	bne @46
	lbz r0, 0x2(r3)
	extsb r0, r0
	cmpwi r0, 0x31
	blt @46
	cmpwi r0, 0x33
	bgt @46
	li r0, 0x1
	b @47
	@46:
	li r0, 0x0
	@47:
	cmpwi r0, 0x0
	beq @48
	lwz r3, 0x70(r31)
	la r4, str_8041A120(r0)
	li r5, 0x1
	bl animPoseSetAnim
	b @45
	@48:
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	@45:
	li r0, 0x0
	stw r0, 0x1dc(r31)
	@5:
	lmw r27, 0x4c(r1)
	li r3, 0x0
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm USER_FUNC(evt_mobj_float_blk) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stfd f30, 0x50(r1)
	psq_st f30, 0x58(r1), 0, 0
	stfd f29, 0x40(r1)
	psq_st f29, 0x48(r1), 0, 0
	stmw r26, 0x28(r1)
	mr r26, r3
	lis r4, vec3_802c3dc8@ha
	lwz r30, 0x18(r3)
	addi r31, r4, vec3_802c3dc8@l
	lwz r4, 0x0(r30)
	bl evtGetValue
	lwz r4, 0x4(r30)
	mr r29, r3
	mr r3, r26
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r30)
	mr r3, r26
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r30)
	mr r3, r26
	bl evtGetFloat
	fmr f29, f1
	lwz r28, 0x10(r30)
	lwz r27, 0x14(r30)
	mr r3, r26
	lwz r4, 0x18(r30)
	bl evtGetValue
	lwz r3, gp(r0)
	cmpwi r28, 0x2
	lwz r30, 0x1c(r30)
	lwz r3, 0x14(r3)
	neg r0, r3
	or r0, r0, r3
	srwi r4, r0, 31
	beq @1
	bge @2
	cmpwi r28, 0x0
	beq @3
	bge @4
	b @5
	@2:
	cmpwi r28, 0x4
	bge @5
	b @6
	@3:
	cmpwi r27, 0x0
	bne @7
	addi r27, r31, 0x7a0
	b @8
	@7:
	cmpwi r27, 0x1
	bne @9
	addi r27, r31, 0x7b8
	b @8
	@9:
	addi r27, r31, 0x7d4
	b @8
	@4:
	cmpwi r27, 0x0
	bne @10
	addi r27, r31, 0x7f0
	b @8
	@10:
	cmpwi r27, 0x1
	bne @11
	addi r27, r31, 0x808
	b @8
	@11:
	addi r27, r31, 0x824
	b @8
	@1:
	cmpwi r27, 0x0
	bne @12
	addi r27, r31, 0x840
	b @8
	@12:
	cmpwi r27, 0x1
	bne @13
	addi r27, r31, 0x858
	b @8
	@13:
	addi r27, r31, 0x874
	b @8
	@6:
	addi r27, r31, 0x890
	b @8
	@5:
	cmpwi r27, 0x0
	bne @14
	addi r27, r31, 0x7a0
	b @8
	@14:
	cmpwi r27, 0x1
	bne @15
	addi r27, r31, 0x7b8
	b @8
	@15:
	addi r27, r31, 0x7d4
	@8:
	mr r3, r27
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @16
	li r3, 0x0
	b @17
	@16:
	mr r3, r29
	mr r4, r27
	bl mobjEntry
	mr r3, r29
	bl mobjNameToPtr
	fmr f1, f31
	mr r27, r3
	fmr f2, f30
	mr r3, r29
	fmr f3, f29
	bl mobjSetPosition
	lis r3, mobj_float_blk@ha
	li r0, 0x63
	addi r4, r3, mobj_float_blk@l
	mr r3, r27
	stw r4, 0x1d0(r27)
	lwz r4, 0x0(r27)
	ori r4, r4, 0x4
	stw r4, 0x0(r27)
	stw r30, 0x1e4(r27)
	stw r0, 0x1dc(r27)
	bl mobjCalcMtx
	lfs f0, 0x60(r27)
	addi r4, r1, 0x8
	lfs f4, float_0_8041a150(r0)
	addi r5, r1, 0xc
	fabs f0, f0
	lfs f1, float_1_8041a160(r0)
	lfs f2, float_0p5_8041a15c(r0)
	fmr f6, f4
	lfs f5, float_neg1_8041a214(r0)
	addi r6, r1, 0x10
	frsp f0, f0
	addi r7, r1, 0x14
	addi r8, r1, 0x18
	addi r9, r1, 0x1c
	addi r10, r1, 0x20
	li r3, 0x0
	fadds f0, f1, f0
	stfs f0, 0x14(r1)
	lfs f0, 0x3c(r27)
	lfs f1, 0x38(r27)
	fadds f2, f2, f0
	lfs f3, 0x40(r27)
	bl hitCheckFilter
	cmpwi r3, 0x0
	beq @18
	lwz r3, 0x70(r27)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r0, 0x0(r27)
	ori r0, r0, 0x2
	stw r0, 0x0(r27)
	b @19
	@18:
	lwz r3, 0x70(r27)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	@19:
	li r3, 0x2
	@17:
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	psq_l f30, 0x58(r1), 0, 0
	lfd f30, 0x50(r1)
	psq_l f29, 0x48(r1), 0, 0
	lfd f29, 0x40(r1)
	lmw r26, 0x28(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm s32 mobj_float_blk(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	mr r31, r3
	lwz r0, 0x1dc(r3)
	cmpwi r0, 0x63
	beq @1
	b @2
	@1:
	lbz r0, 0x1b8(r31)
	extsb. r0, r0
	bne @3
	lfs f0, 0x60(r31)
	addi r4, r1, 0x8
	lfs f4, float_0_8041a150(r0)
	addi r5, r1, 0xc
	fabs f0, f0
	lfs f1, float_1_8041a160(r0)
	lfs f2, float_0p5_8041a15c(r0)
	fmr f6, f4
	lfs f5, float_neg1_8041a214(r0)
	addi r6, r1, 0x10
	frsp f0, f0
	addi r7, r1, 0x14
	addi r8, r1, 0x18
	addi r9, r1, 0x1c
	addi r10, r1, 0x20
	li r3, 0x0
	fadds f0, f1, f0
	stfs f0, 0x14(r1)
	lfs f0, 0x3c(r31)
	lfs f1, 0x38(r31)
	fadds f2, f2, f0
	lfs f3, 0x40(r31)
	bl hitCheckFilter
	cmpwi r3, 0x0
	beq @4
	lwz r3, 0x70(r31)
	bl animPoseGetCurrentAnim
	la r4, str_8041A12C(r0)
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r0, 0x0(r31)
	ori r0, r0, 0x2
	stw r0, 0x0(r31)
	b @2
	@4:
	lwz r3, 0x70(r31)
	bl animPoseGetCurrentAnim
	la r4, str_8041A118(r0)
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r31)
	b @2
	@3:
	addi r3, r31, 0x1b8
	bl mobjNameToPtr
	lwz r3, 0x70(r3)
	bl animPoseGetCurrentAnim
	lbz r0, 0x0(r3)
	cmpwi r0, 0x41
	bne @5
	lbz r0, 0x2(r3)
	extsb r0, r0
	cmpwi r0, 0x31
	blt @5
	cmpwi r0, 0x33
	bgt @5
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x0
	bl animPoseSetAnim
	b @2
	@5:
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	@2:
	lwz r0, 0x34(r1)
	li r3, 0x0
	lwz r31, 0x2c(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm USER_FUNC(evt_mobj_lv_blk) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x48(r1)
	stfd f30, 0x40(r1)
	stfd f29, 0x38(r1)
	stmw r27, 0x24(r1)
	mr r27, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r28, r3
	mr r3, r27
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x8(r29)
	mr r3, r27
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r29)
	mr r3, r27
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x10(r29)
	mr r3, r27
	bl evtGetValue
	lwz r30, 0x14(r29)
	mr r31, r3
	lwz r4, 0x18(r29)
	mr r3, r27
	bl evtGetValue
	lwz r4, gp(r0)
	mr r29, r3
	mr r3, r27
	lwz r5, 0x14(r4)
	mr r4, r30
	neg r0, r5
	or r0, r0, r5
	srwi r27, r0, 31
	bl evtGetValue
	cmpwi r3, 0x0
	beq @1
	li r3, 0x2
	b @2
	@1:
	mr r3, r29
	mr r4, r27
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @3
	li r3, 0x0
	b @2
	@3:
	lis r3, str_802C4388@ha
	mr r4, r27
	addi r3, r3, str_802C4388@l
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @4
	li r3, 0x0
	b @2
	@4:
	mr r3, r28
	mr r4, r29
	bl mobjEntry
	mr r3, r28
	bl mobjNameToPtr
	lwz r0, 0x0(r3)
	lis r6, vec3_802c3ef4@ha
	lis r5, mobj_lv_blk_evt@ha
	li r4, 0x0
	ori r0, r0, 0x44
	addi r7, r6, vec3_802c3ef4@l
	stw r0, 0x0(r3)
	addi r0, r5, mobj_lv_blk_evt@l
	lwz r5, 0x0(r7)
	lwz r6, 0x4(r7)
	stw r5, 0x8(r1)
	lwz r5, 0x8(r7)
	stw r6, 0xc(r1)
	stfs f29, 0x8(r1)
	stw r5, 0x10(r1)
	lwz r5, 0x8(r1)
	stfs f30, 0xc(r1)
	stfs f31, 0x10(r1)
	lwz r6, 0xc(r1)
	stw r5, 0x38(r3)
	lwz r5, 0x10(r1)
	stw r6, 0x3c(r3)
	stw r5, 0x40(r3)
	stw r0, 0x1d0(r3)
	stw r31, 0x1d4(r3)
	stw r4, 0x1d8(r3)
	lwz r0, 0x0(r3)
	oris r0, r0, 0x1
	stw r0, 0x0(r3)
	stw r30, 0x1e4(r3)
	stw r4, 0x1dc(r3)
	li r3, 0x2
	@2:
	lfd f31, 0x48(r1)
	lfd f30, 0x40(r1)
	lfd f29, 0x38(r1)
	lmw r27, 0x24(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm s32 mobj_lv_blk_evt(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x3f0(r1)
	mflr r0
	lis r5, vec3_802c3dc8@ha
	stw r0, 0x3f4(r1)
	stmw r27, 0x3dc(r1)
	addi r31, r5, vec3_802c3dc8@l
	mr r29, r3
	lwz r10, 0x100(r31)
	lwz r9, 0x104(r31)
	lwz r8, 0x108(r31)
	lwz r7, 0x10c(r31)
	lwz r6, 0x110(r31)
	lwz r5, 0x114(r31)
	lwz r3, 0x118(r31)
	lwz r0, 0x11c(r31)
	lwz r4, gp(r0)
	stw r10, 0x18(r1)
	stw r9, 0x1c(r1)
	stw r8, 0x20(r1)
	stw r7, 0x24(r1)
	stw r6, 0x8(r1)
	stw r5, 0xc(r1)
	stw r3, 0x10(r1)
	stw r0, 0x14(r1)
	lwz r3, 0x14(r4)
	neg r0, r3
	or r0, r0, r3
	srwi r30, r0, 31
	bl marioGetPtr
	mr r28, r3
	addi r3, r1, 0x18
	addi r4, r29, 0x5
	bl strcat
	addi r3, r1, 0x8
	addi r4, r29, 0x5
	bl strcat
	lwz r0, 0x1dc(r29)
	cmpwi r0, 0xb
	beq @1
	bge @2
	cmpwi r0, 0x0
	beq @3
	blt @4
	cmpwi r0, 0xa
	bge @5
	b @4
	@2:
	cmpwi r0, 0x63
	beq @6
	bge @4
	cmpwi r0, 0xd
	bge @4
	b @7
	@3:
	mr r4, r30
	addi r3, r31, 0x5c0
	li r5, 0x0
	bl animGroupBaseAsync
	lwz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 28, 28
	beq @4
	addi r3, r29, 0x15
	addi r4, r31, 0x8ac
	bl strcmp
	cmpwi r3, 0x0
	beq @8
	addi r3, r29, 0x15
	addi r4, r31, 0x8bc
	bl strcmp
	cmpwi r3, 0x0
	beq @8
	addi r3, r29, 0x15
	addi r4, r31, 0x8d0
	bl strcmp
	cmpwi r3, 0x0
	bne @9
	bl pouchGetHammerLv
	cmpwi r3, 0x2
	blt @10
	lhz r0, 0x2e(r28)
	cmplwi r0, 0x13
	beq @8
	@10:
	lwz r0, 0x0(r29)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r29)
	b @4
	@9:
	addi r3, r29, 0x15
	addi r4, r31, 0x8e4
	bl strcmp
	cmpwi r3, 0x0
	beq @11
	addi r3, r29, 0x15
	addi r4, r31, 0x8f4
	bl strcmp
	cmpwi r3, 0x0
	bne @12
	@11:
	bl pouchGetHammerLv
	cmpwi r3, 0x3
	bge @8
	lwz r0, 0x0(r29)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r29)
	b @4
	@12:
	addi r3, r29, 0x15
	addi r4, r31, 0x908
	bl strcmp
	cmpwi r3, 0x0
	bne @13
	bl pouchGetHammerLv
	cmpwi r3, 0x3
	blt @14
	lhz r0, 0x2e(r28)
	cmplwi r0, 0x13
	beq @8
	@14:
	lwz r0, 0x0(r29)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r29)
	b @4
	@13:
	lwz r0, 0x0(r29)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r29)
	b @4
	@8:
	lwz r4, 0x1d4(r29)
	mr r3, r29
	bl mobjRunEvent
	lwz r4, 0x1e4(r29)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	li r0, 0xa
	stw r0, 0x1dc(r29)
	b @4
	@5:
	mr r4, r30
	addi r3, r31, 0x5c0
	bl animPaperPoseEntry
	addi r3, r1, 0x18
	bl offscreenEntry
	mr r4, r30
	addi r3, r1, 0x8
	bl imgEntry
	addi r3, r1, 0x18
	bl offscreenNameToId
	stw r3, 0x19c(r29)
	li r5, 0x0
	addi r3, r1, 0x50
	addi r28, r1, 0x8
	addi r27, r1, 0x18
	li r0, 0x1
	stw r3, 0x240(r1)
	addi r3, r1, 0x228
	li r4, 0x1
	stw r28, 0x50(r1)
	stw r5, 0x54(r1)
	stw r27, 0x58(r1)
	stw r0, 0x5c(r1)
	stw r5, 0x60(r1)
	stw r5, 0x64(r1)
	stw r5, 0x68(r1)
	stw r5, 0x6c(r1)
	bl evt_img_alloc_capture
	li r0, 0x0
	li r5, 0x1
	addi r6, r1, 0x28
	stw r28, 0x28(r1)
	addi r3, r1, 0x78
	li r4, 0x1
	stw r6, 0x90(r1)
	stw r5, 0x2c(r1)
	stw r27, 0x30(r1)
	stw r5, 0x34(r1)
	stw r0, 0x38(r1)
	stw r0, 0x3c(r1)
	stw r0, 0x40(r1)
	stw r0, 0x44(r1)
	bl evt_img_alloc_capture
	mr r4, r30
	mr r3, r28
	bl imgNameToPtr
	mr r27, r3
	mr r4, r30
	addi r3, r31, 0x5c0
	bl animPaperPoseGetId
	stw r3, 0x104(r27)
	la r0, str_8041A118(r0)
	mr r3, r30
	stw r0, 0x108(r27)
	bl animTimeGetTime
	stw r4, 0x114(r27)
	li r4, 0x2
	stw r3, 0x110(r27)
	mr r3, r27
	bl imgSetShadow
	addi r3, r29, 0x15
	addi r4, r31, 0x8ac
	bl strcmp
	cmpwi r3, 0x0
	beq @15
	addi r3, r29, 0x15
	addi r4, r31, 0x8e4
	bl strcmp
	cmpwi r3, 0x0
	bne @16
	@15:
	addi r4, r29, 0x38
	li r3, 0x1c7
	bl psndSFXOn_3D
	b @17
	@16:
	addi r3, r29, 0x15
	addi r4, r31, 0x8bc
	bl strcmp
	cmpwi r3, 0x0
	beq @18
	addi r3, r29, 0x15
	addi r4, r31, 0x8f4
	bl strcmp
	cmpwi r3, 0x0
	bne @19
	@18:
	addi r4, r29, 0x38
	li r3, 0x1c8
	bl psndSFXOn_3D
	b @17
	@19:
	addi r3, r29, 0x15
	addi r4, r31, 0x8d0
	bl strcmp
	cmpwi r3, 0x0
	beq @20
	addi r3, r29, 0x15
	addi r4, r31, 0x908
	bl strcmp
	cmpwi r3, 0x0
	bne @17
	@20:
	addi r4, r29, 0x38
	li r3, 0x1c9
	bl psndSFXOn_3D
	@17:
	li r0, 0xb
	stw r0, 0x1dc(r29)
	b @4
	@1:
	mr r4, r30
	addi r3, r1, 0x8
	bl imgNameToPtr
	lfs f1, 0x118(r3)
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @21
	li r0, 0xc
	stw r0, 0x1dc(r29)
	@21:
	lwz r0, 0xcc(r3)
	rlwinm. r0, r0, 0, 3, 3
	beq @22
	li r0, 0xc
	stw r0, 0x1dc(r29)
	@22:
	lwz r3, 0x120(r31)
	lwz r0, 0x124(r31)
	stw r3, 0x38(r29)
	stw r0, 0x3c(r29)
	lwz r0, 0x128(r31)
	stw r0, 0x40(r29)
	lwz r0, 0x0(r29)
	ori r0, r0, 0x4
	stw r0, 0x0(r29)
	lwz r0, 0x0(r29)
	ori r0, r0, 0x8
	stw r0, 0x0(r29)
	b @4
	@7:
	mr r4, r30
	addi r3, r1, 0x8
	bl imgNameToPtr
	li r4, 0x0
	mr r27, r3
	bl imgFreeCapture
	mr r3, r27
	li r4, 0x1
	bl imgFreeCapture
	mr r3, r27
	li r4, 0x0
	bl imgSetShadow
	mr r3, r27
	mr r4, r30
	bl imgRelease
	addi r3, r1, 0x18
	bl offscreenDelete
	li r3, -0x1
	li r0, 0x63
	stw r3, 0x19c(r29)
	stw r0, 0x1dc(r29)
	b @4
	@6:
	addi r3, r29, 0x5
	bl mobjDelete
	@4:
	lmw r27, 0x3dc(r1)
	li r3, 0x0
	lwz r0, 0x3f4(r1)
	mtlr r0
	addi r1, r1, 0x3f0
	blr
}

asm USER_FUNC(evt_mobj_jumpstand_blue) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	addi r11, r1, 0x40
	bl _savefpr_28
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r30, r3
	lwz r28, 0x18(r3)
	lwz r4, 0x0(r28)
	bl evtGetValue
	lwz r4, 0x4(r28)
	mr r29, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x8(r28)
	mr r31, r3
	mr r3, r30
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0xc(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x10(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x14(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f28, f1
	lwz r4, 0x18(r28)
	mr r3, r30
	bl evtGetValue
	lis r4, jumptable_802C3EC0@ha
	lwzu r7, jumptable_802C3EC0@l(r4)
	lwz r5, gp(r0)
	slwi r0, r29, 2
	lwz r4, 0x4(r4)
	addi r6, r1, 0x8
	lwz r8, 0x14(r5)
	mr r29, r3
	stw r7, 0x8(r1)
	li r5, 0x0
	neg r3, r8
	lwz r30, 0x1c(r28)
	stw r4, 0xc(r1)
	or r3, r3, r8
	srwi r4, r3, 31
	lwzx r28, r6, r0
	mr r3, r28
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r3, r31
	mr r4, r28
	bl mobjEntry
	mr r3, r31
	bl mobjNameToPtr
	fmr f1, f30
	mr r28, r3
	fmr f2, f29
	mr r3, r31
	fmr f3, f28
	bl mobjSetPosition
	lis r3, mobj_jumpstand_blue@ha
	li r0, 0x0
	addi r4, r3, mobj_jumpstand_blue@l
	mr r3, r28
	stw r4, 0x1d0(r28)
	stw r29, 0x1d4(r28)
	lwz r4, 0x0(r28)
	ori r4, r4, 0x44
	stw r4, 0x0(r28)
	lwz r4, 0x0(r28)
	oris r4, r4, 0x20
	stw r4, 0x0(r28)
	stw r30, 0x1e4(r28)
	stw r0, 0x1dc(r28)
	stfs f31, 0x1ac(r28)
	bl mobjCalcMtx
	li r3, 0x2
	@2:
	addi r11, r1, 0x40
	bl _restfpr_28
	lwz r0, 0x44(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 mobj_jumpstand_blue(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	stw r30, 0x8(r1)
	bl marioGetPtr
	lwz r0, 0x1dc(r31)
	mr r30, r3
	cmpwi r0, 0x1
	beq @1
	bge @2
	cmpwi r0, 0x0
	bge @3
	b @2
	@3:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @2
	lwz r4, gp(r0)
	mr r3, r31
	lwz r0, 0x18(r4)
	ori r0, r0, 0x10
	stw r0, 0x18(r4)
	lwz r4, 0x1d4(r31)
	bl mobjRunEvent
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x20
	cmplwi r0, 0x0
	bne @4
	lfs f1, 0x1ac(r31)
	bl marioChgJumpStandMotion
	@4:
	lbz r0, 0x3c(r30)
	cmpwi r0, 0x2
	beq @5
	lis r4, str_802C3E98@ha
	addi r3, r31, 0x15
	addi r4, r4, str_802C3E98@l
	bl strcmp
	cmpwi r3, 0x0
	bne @6
	addi r4, r31, 0x38
	li r3, 0x1eb
	bl psndSFXOn_3D
	b @7
	@6:
	addi r4, r31, 0x38
	li r3, 0x1ec
	bl psndSFXOn_3D
	@7:
	li r3, 0x4
	bl irand
	cmpwi r3, 0x2
	beq @8
	bge @9
	cmpwi r3, 0x0
	beq @10
	bge @11
	b @12
	@9:
	cmpwi r3, 0x4
	beq @13
	bge @12
	b @14
	@10:
	addi r4, r31, 0x38
	li r3, 0xab
	bl psndSFXOn_3D
	b @12
	@11:
	addi r4, r31, 0x38
	li r3, 0xac
	bl psndSFXOn_3D
	b @12
	@8:
	addi r4, r31, 0x38
	li r3, 0xad
	bl psndSFXOn_3D
	b @12
	@14:
	addi r4, r31, 0x38
	li r3, 0xae
	bl psndSFXOn_3D
	b @12
	@13:
	addi r4, r31, 0x38
	li r3, 0xaf
	bl psndSFXOn_3D
	b @12
	@5:
	lis r4, str_802C3E98@ha
	addi r3, r31, 0x15
	addi r4, r4, str_802C3E98@l
	bl strcmp
	cmpwi r3, 0x0
	bne @15
	li r3, 0x1eb
	bl psndSFXOn
	b @12
	@15:
	li r3, 0x1ec
	bl psndSFXOn
	@12:
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @2
	@1:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @16
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x0
	stw r0, 0x1dc(r31)
	b @2
	@16:
	lwz r3, 0x1cc(r31)
	bl evtCheckID
	cmpwi r3, 0x1
	beq @2
	lwz r3, gp(r0)
	lwz r0, 0x18(r3)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x18(r3)
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @2
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x0
	stw r0, 0x1dc(r31)
	@2:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_jumpstand_red) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x38(r1)
	stfd f30, 0x30(r1)
	stfd f29, 0x28(r1)
	stw r31, 0x24(r1)
	stw r30, 0x20(r1)
	mr r30, r3
	stw r29, 0x1c(r1)
	stw r28, 0x18(r1)
	lwz r28, 0x18(r3)
	lwz r4, 0x0(r28)
	bl evtGetValue
	lwz r4, 0x4(r28)
	mr r29, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x8(r28)
	mr r31, r3
	mr r3, r30
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0xc(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x10(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x14(r28)
	mr r3, r30
	bl evtGetValue
	lis r4, jumptable_802C3E90@ha
	lwzu r7, jumptable_802C3E90@l(r4)
	lwz r5, gp(r0)
	slwi r0, r29, 2
	lwz r4, 0x4(r4)
	addi r6, r1, 0x8
	lwz r8, 0x14(r5)
	mr r29, r3
	stw r7, 0x8(r1)
	li r5, 0x0
	neg r3, r8
	lwz r30, 0x18(r28)
	stw r4, 0xc(r1)
	or r3, r3, r8
	srwi r4, r3, 31
	lwzx r28, r6, r0
	mr r3, r28
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r3, r31
	mr r4, r28
	bl mobjEntry
	mr r3, r31
	bl mobjNameToPtr
	fmr f1, f31
	mr r28, r3
	fmr f2, f30
	mr r3, r31
	fmr f3, f29
	bl mobjSetPosition
	lis r3, mobj_jumpstand_red@ha
	li r0, 0x0
	addi r4, r3, mobj_jumpstand_red@l
	mr r3, r28
	stw r4, 0x1d0(r28)
	stw r29, 0x1d4(r28)
	lwz r4, 0x0(r28)
	ori r4, r4, 0x44
	stw r4, 0x0(r28)
	lwz r4, 0x0(r28)
	oris r4, r4, 0x20
	stw r4, 0x0(r28)
	stw r30, 0x1e4(r28)
	stw r0, 0x1dc(r28)
	bl mobjCalcMtx
	li r3, 0x2
	@2:
	lwz r0, 0x44(r1)
	lfd f31, 0x38(r1)
	lfd f30, 0x30(r1)
	lfd f29, 0x28(r1)
	lwz r31, 0x24(r1)
	lwz r30, 0x20(r1)
	lwz r29, 0x1c(r1)
	lwz r28, 0x18(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 mobj_jumpstand_red(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	stw r30, 0x8(r1)
	bl marioGetPtr
	mr r30, r3
	bl marioGetPartyId
	bl partyGetPtr
	lwz r0, 0x1dc(r31)
	cmpwi r0, 0x1
	beq @1
	bge @2
	cmpwi r0, 0x0
	bge @3
	b @2
	@3:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @2
	lwz r4, gp(r0)
	mr r3, r31
	lwz r0, 0x18(r4)
	ori r0, r0, 0x10
	stw r0, 0x18(r4)
	lwz r4, 0x1d4(r31)
	bl mobjRunEvent
	cmplwi r3, 0x0
	beq @4
	lfs f2, 0xd8(r30)
	lfs f0, 0x90(r30)
	fcmpo cr0, f2, f0
	bge @5
	li r0, 0x0
	b @6
	@5:
	lfs f1, 0x3c(r31)
	lfs f0, 0x1b8(r30)
	fadds f0, f1, f0
	fcmpo cr0, f2, f0
	bge @7
	li r0, 0x0
	b @6
	@7:
	li r0, 0x1
	@6:
	stw r0, 0x9c(r3)
	@4:
	lbz r0, 0x3c(r30)
	cmpwi r0, 0x2
	beq @8
	lis r4, str_802C3E68@ha
	addi r3, r31, 0x15
	addi r4, r4, str_802C3E68@l
	bl strcmp
	cmpwi r3, 0x0
	bne @9
	addi r4, r31, 0x38
	li r3, 0x1eb
	bl psndSFXOn_3D
	b @10
	@9:
	addi r4, r31, 0x38
	li r3, 0x1ec
	bl psndSFXOn_3D
	@10:
	li r3, 0x4
	bl irand
	cmpwi r3, 0x2
	beq @11
	bge @12
	cmpwi r3, 0x0
	beq @13
	bge @14
	b @15
	@12:
	cmpwi r3, 0x4
	beq @16
	bge @15
	b @17
	@13:
	addi r4, r31, 0x38
	li r3, 0xab
	bl psndSFXOn_3D
	b @15
	@14:
	addi r4, r31, 0x38
	li r3, 0xac
	bl psndSFXOn_3D
	b @15
	@11:
	addi r4, r31, 0x38
	li r3, 0xad
	bl psndSFXOn_3D
	b @15
	@17:
	addi r4, r31, 0x38
	li r3, 0xae
	bl psndSFXOn_3D
	b @15
	@16:
	addi r4, r31, 0x38
	li r3, 0xaf
	bl psndSFXOn_3D
	b @15
	@8:
	lis r4, str_802C3E68@ha
	addi r3, r31, 0x15
	addi r4, r4, str_802C3E68@l
	bl strcmp
	cmpwi r3, 0x0
	bne @18
	li r3, 0x1eb
	bl psndSFXOn
	b @15
	@18:
	li r3, 0x1ec
	bl psndSFXOn
	@15:
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @2
	@1:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @19
	lwz r3, 0x1cc(r31)
	bl evtCheckID
	cmpwi r3, 0x0
	bne @19
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x0
	stw r0, 0x1dc(r31)
	b @2
	@19:
	lwz r3, 0x1cc(r31)
	bl evtCheckID
	cmpwi r3, 0x1
	beq @2
	lwz r3, gp(r0)
	lwz r0, 0x18(r3)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x18(r3)
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @2
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x0
	stw r0, 0x1dc(r31)
	@2:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_rideswitch_lightblue) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stfd f30, 0x30(r1)
	psq_st f30, 0x38(r1), 0, 0
	stfd f29, 0x20(r1)
	psq_st f29, 0x28(r1), 0, 0
	stmw r27, 0xc(r1)
	mr r27, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r28, r3
	mr r3, r27
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r29)
	mr r3, r27
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r29)
	mr r3, r27
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x10(r29)
	mr r3, r27
	bl evtGetValue
	lwz r4, 0x14(r29)
	mr r30, r3
	mr r3, r27
	bl evtGetValue
	lwz r5, gp(r0)
	lis r4, str_802C46E4@ha
	addi r0, r4, str_802C46E4@l
	mr r31, r3
	lwz r4, 0x14(r5)
	mr r27, r0
	mr r3, r0
	lwz r29, 0x18(r29)
	neg r0, r4
	li r5, 0x0
	or r0, r0, r4
	srwi r4, r0, 31
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r3, r28
	mr r4, r27
	bl mobjEntry
	mr r3, r28
	bl mobjNameToPtr
	lfs f4, float_0p8_8041a1b0(r0)
	mr r27, r3
	lfs f0, 0x184(r3)
	fmr f1, f31
	fmr f2, f30
	mr r3, r28
	fmuls f0, f0, f4
	fmr f3, f29
	stfs f0, 0x184(r27)
	lfs f0, 0x18c(r27)
	fmuls f0, f0, f4
	stfs f0, 0x18c(r27)
	bl mobjSetPosition
	lis r3, mobj_rideswitch_lightblue@ha
	li r0, 0x0
	addi r4, r3, mobj_rideswitch_lightblue@l
	mr r3, r27
	stw r4, 0x1d0(r27)
	stw r30, 0x1d4(r27)
	stw r31, 0x1d8(r27)
	lwz r4, 0x0(r27)
	ori r4, r4, 0x4
	stw r4, 0x0(r27)
	lwz r4, 0x0(r27)
	oris r4, r4, 0x20
	stw r4, 0x0(r27)
	stw r29, 0x1e4(r27)
	stw r0, 0x1dc(r27)
	bl mobjCalcMtx2
	li r3, 0x2
	@2:
	psq_l f31, 0x48(r1), 0, 0
	lfd f31, 0x40(r1)
	psq_l f30, 0x38(r1), 0, 0
	lfd f30, 0x30(r1)
	psq_l f29, 0x28(r1), 0, 0
	lfd f29, 0x20(r1)
	lmw r27, 0xc(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm s32 mobj_rideswitch_lightblue(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stw r31, 0x3c(r1)
	stw r30, 0x38(r1)
	mr r31, r3
	lis r4, vec3_802c3dc8@ha
	lwz r0, 0x1dc(r3)
	addi r30, r4, vec3_802c3dc8@l
	cmpwi r0, 0x3
	beq @1
	bge @2
	cmpwi r0, 0x1
	beq @3
	bge @4
	cmpwi r0, 0x0
	bge @5
	b @6
	@2:
	cmpwi r0, 0x63
	beq @6
	b @6
	@5:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @6
	lwz r4, 0x1d4(r31)
	bl mobjRunEvent
	addi r4, r31, 0x38
	li r3, 0x1d3
	bl psndSFXOn_3D
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x1
	stw r0, 0x1dc(r31)
	b @6
	@3:
	lfs f2, 0x188(r31)
	lfs f1, float_0p9_8041a228(r0)
	lfs f0, float_0p2_8041a19c(r0)
	fsubs f2, f2, f1
	lfs f1, 0x184(r31)
	lfs f3, 0x18c(r31)
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	bne @7
	li r0, 0x2
	fmr f2, f0
	stw r0, 0x1dc(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	@7:
	lwz r0, 0x7c(r30)
	mr r3, r31
	lwz r4, 0x80(r30)
	stw r0, 0x20(r1)
	lwz r0, 0x84(r30)
	stw r4, 0x24(r1)
	stfs f1, 0x20(r1)
	stw r0, 0x28(r1)
	lwz r0, 0x20(r1)
	stfs f2, 0x24(r1)
	stfs f3, 0x28(r1)
	lwz r4, 0x24(r1)
	stw r0, 0x184(r31)
	lwz r0, 0x28(r1)
	stw r4, 0x188(r31)
	stw r0, 0x18c(r31)
	bl mobjCalcMtx2
	b @6
	@4:
	lwz r3, 0x70(r31)
	bl animPoseGetAnimBaseDataPtr
	lfs f3, float_10_8041a1a4(r0)
	lfs f2, 0xdc(r3)
	lfs f0, 0xe4(r3)
	lfs f1, 0xe0(r3)
	fmuls f2, f3, f2
	lfs f4, float_0p8_8041a1b0(r0)
	fmuls f0, f3, f0
	lwz r3, 0x88(r30)
	fmuls f1, f3, f1
	lwz r4, 0x8c(r30)
	lwz r0, 0x90(r30)
	fmuls f2, f4, f2
	stw r3, 0x14(r1)
	fmuls f0, f4, f0
	addi r3, r1, 0x2c
	stw r4, 0x18(r1)
	stw r0, 0x1c(r1)
	stfs f2, 0x14(r1)
	stfs f1, 0x18(r1)
	lwz r5, 0x14(r1)
	stfs f0, 0x1c(r1)
	lwz r4, 0x18(r1)
	lwz r0, 0x1c(r1)
	stw r5, 0x2c(r1)
	stw r4, 0x30(r1)
	stw r0, 0x34(r1)
	bl PSVECMag
	fmr f31, f1
	bl marioGetPtr
	mr r4, r3
	addi r3, r31, 0x38
	addi r4, r4, 0x8c
	bl PSVECDistance
	fcmpo cr0, f1, f31
	ble @6
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 28, 28
	bne @8
	li r0, 0x3
	la r4, str_8041A11C(r0)
	stw r0, 0x1dc(r31)
	li r5, 0x1
	lwz r3, 0x70(r31)
	bl animPoseSetAnim
	addi r4, r31, 0x38
	li r3, 0x1d4
	bl psndSFXOn_3D
	lwz r4, 0x1d8(r31)
	mr r3, r31
	bl mobjRunEvent
	b @6
	@8:
	rlwinm r0, r3, 0, 29, 27
	stw r0, 0x0(r31)
	b @6
	@1:
	lfs f2, 0x188(r31)
	lfs f1, float_0p9_8041a228(r0)
	lfs f0, float_15_8041a22c(r0)
	fadds f2, f2, f1
	lfs f1, 0x184(r31)
	lfs f3, 0x18c(r31)
	fcmpo cr0, f2, f0
	cror eq, gt, eq
	bne @9
	li r0, 0x0
	fmr f2, f0
	stw r0, 0x1dc(r31)
	@9:
	lwz r0, 0x94(r30)
	mr r3, r31
	lwz r4, 0x98(r30)
	stw r0, 0x8(r1)
	lwz r0, 0x9c(r30)
	stw r4, 0xc(r1)
	stfs f1, 0x8(r1)
	stw r0, 0x10(r1)
	lwz r0, 0x8(r1)
	stfs f2, 0xc(r1)
	stfs f3, 0x10(r1)
	lwz r4, 0xc(r1)
	stw r0, 0x184(r31)
	lwz r0, 0x10(r1)
	stw r4, 0x188(r31)
	stw r0, 0x18c(r31)
	bl mobjCalcMtx2
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	@6:
	li r3, 0x0
	psq_l f31, 0x48(r1), 0, 0
	lwz r0, 0x54(r1)
	lfd f31, 0x40(r1)
	lwz r31, 0x3c(r1)
	lwz r30, 0x38(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm USER_FUNC(evt_mobj_timerswitch) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stmw r19, 0x3c(r1)
	mr r19, r3
	lwz r22, 0x18(r3)
	lwz r4, 0x0(r22)
	bl evtGetValue
	lis r4, jumptable_802C3E0C@ha
	mr r21, r3
	addi r3, r4, jumptable_802C3E0C@l
	lwz r7, gp(r0)
	lwz r4, 0x0(r3)
	slwi r0, r21, 2
	lwz r6, 0x4(r3)
	addi r5, r1, 0x8
	lwz r8, 0x14(r7)
	mr r3, r19
	stw r4, 0x8(r1)
	neg r7, r8
	lwz r4, 0x4(r22)
	stw r6, 0xc(r1)
	or r6, r7, r8
	srwi r23, r6, 31
	lwzx r20, r5, r0
	bl evtGetValue
	stw r3, 0x30(r1)
	mr r3, r19
	lwz r4, 0x8(r22)
	bl evtGetFloat
	stfs f1, 0x28(r1)
	mr r3, r19
	lwz r4, 0xc(r22)
	bl evtGetFloat
	stfs f1, 0x20(r1)
	mr r3, r19
	lwz r4, 0x10(r22)
	bl evtGetFloat
	stfs f1, 0x18(r1)
	mr r3, r19
	lwz r4, 0x14(r22)
	bl evtGetValue
	stw r3, 0x34(r1)
	mr r3, r19
	lwz r4, 0x18(r22)
	bl evtGetFloat
	stfs f1, 0x2c(r1)
	mr r3, r19
	lwz r4, 0x1c(r22)
	bl evtGetFloat
	stfs f1, 0x24(r1)
	mr r3, r19
	lwz r4, 0x20(r22)
	bl evtGetFloat
	stfs f1, 0x1c(r1)
	mr r3, r19
	lwz r4, 0x24(r22)
	bl evtGetValue
	lwz r4, 0x28(r22)
	mr r29, r3
	mr r3, r19
	bl evtGetValue
	cmpwi r21, 0x0
	lwz r22, 0x2c(r22)
	mr r30, r3
	bne @1
	mr r3, r19
	mr r4, r22
	bl evtGetValue
	cmpwi r3, 0x0
	beq @1
	li r3, 0x2
	b @2
	@1:
	mr r3, r20
	mr r4, r23
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @3
	li r3, 0x0
	b @2
	@3:
	lis r3, mobj_timerswitch@ha
	lwz r23, 0x34(r1)
	addi r28, r1, 0x30
	addi r27, r1, 0x10
	addi r26, r1, 0x18
	addi r25, r1, 0x20
	addi r24, r1, 0x28
	addi r31, r3, mobj_timerswitch@l
	li r21, 0x0
	@4:
	lwz r3, 0x0(r28)
	mr r4, r20
	bl mobjEntry
	lwz r3, 0x0(r28)
	bl mobjNameToPtr
	stw r3, 0x0(r27)
	cmpwi r21, 0x0
	lwz r3, 0x0(r27)
	addi r3, r3, 0x1b8
	bne @5
	mr r4, r23
	b @6
	@5:
	lwz r4, 0x30(r1)
	@6:
	bl strcpy
	lwz r3, 0x0(r28)
	lfs f1, 0x0(r24)
	lfs f2, 0x0(r25)
	lfs f3, 0x0(r26)
	bl mobjSetPosition
	lwz r6, 0x0(r27)
	li r0, 0x0
	mr r3, r19
	mr r4, r22
	stw r31, 0x1d0(r6)
	stw r30, 0x1d4(r6)
	lwz r5, 0x0(r6)
	ori r5, r5, 0x44
	stw r5, 0x0(r6)
	lwz r5, 0x0(r6)
	oris r5, r5, 0xa1
	stw r5, 0x0(r6)
	stw r22, 0x1e4(r6)
	stw r0, 0x1dc(r6)
	stw r29, 0x1b4(r6)
	bl evtGetValue
	cmpwi r3, 0x0
	beq @7
	lwz r3, 0x0(r27)
	li r0, 0x63
	stw r0, 0x1dc(r3)
	@7:
	lwz r3, 0x0(r27)
	bl mobjCalcMtx
	addi r21, r21, 0x1
	addi r27, r27, 0x4
	cmpwi r21, 0x2
	addi r26, r26, 0x4
	addi r25, r25, 0x4
	addi r24, r24, 0x4
	addi r28, r28, 0x4
	blt @4
	li r3, 0x2
	@2:
	lmw r19, 0x3c(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm s32 mobj_timerswitch(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	addi r3, r30, 0x1b8
	bl mobjNameToPtr
	lwz r0, 0x1dc(r30)
	mr r31, r3
	cmpwi r0, 0x1
	beq @1
	bge @2
	cmpwi r0, 0x0
	bge @3
	b @4
	@2:
	cmpwi r0, 0x3
	bge @4
	b @5
	@3:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 28, 28
	beq @4
	lwz r3, 0x1e0(r30)
	subis r0, r3, 0x20
	cmplwi r0, 0x0
	bne @6
	li r3, 0x5
	bl marioChgMot
	@6:
	lwz r0, 0x1dc(r31)
	cmpwi r0, 0x2
	beq @7
	addi r4, r30, 0x38
	li r3, 0x1c1
	bl psndSFXOn_3D
	b @8
	@7:
	addi r4, r30, 0x38
	li r3, 0x1c2
	bl psndSFXOn_3D
	@8:
	la r3, evt_shake(r0)
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	bl evtEntryType
	lwz r3, 0x70(r30)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r3, 0x1dc(r30)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r30)
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r30)
	b @4
	@1:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 28, 28
	beq @9
	lwz r3, 0x70(r30)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x0
	stw r0, 0x1dc(r30)
	b @4
	@9:
	lwz r3, 0x70(r30)
	bl animPoseGetLoopTimes
	lfs f0, float_0p3_8041a230(r0)
	fcmpo cr0, f1, f0
	blt @4
	lwz r3, 0x70(r30)
	la r4, str_8041A11C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r3, 0x70(r31)
	la r4, str_8041A11C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r3, 0x1dc(r30)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r30)
	lwz r0, 0x1b4(r30)
	stw r0, 0x1b0(r30)
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r30)
	b @4
	@5:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 28, 28
	beq @10
	lwz r3, 0x70(r30)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x0
	stw r0, 0x1dc(r30)
	b @4
	@10:
	lwz r3, 0x1b0(r30)
	subi r0, r3, 0x1
	stw r0, 0x1b0(r30)
	lwz r0, 0x1b0(r30)
	cmpwi r0, 0x0
	bgt @11
	lwz r0, 0x0(r30)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r30)
	lwz r3, 0x70(r30)
	bl animPoseSetAnim
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x0
	stw r0, 0x1dc(r30)
	b @4
	@11:
	lwz r0, 0x1dc(r31)
	cmpwi r0, 0x2
	bne @4
	bl marioKeyOffChk
	cmpwi r3, 0x0
	bne @12
	bl marioCtrlOffChk
	cmpwi r3, 0x0
	beq @13
	@12:
	li r0, 0x0
	stw r0, 0x1dc(r30)
	b @4
	@13:
	lwz r4, 0x1d4(r30)
	mr r3, r30
	bl mobjRunEvent
	lis r4, str_802C3DF8@ha
	addi r3, r30, 0x15
	addi r4, r4, str_802C3DF8@l
	bl strcmp
	cmpwi r3, 0x0
	bne @14
	lwz r0, 0x0(r30)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r30)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	lwz r3, 0x70(r30)
	bl animPoseSetAnim
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	li r0, 0x0
	stw r0, 0x1dc(r30)
	stw r0, 0x1dc(r31)
	b @4
	@14:
	lfs f4, float_0_8041a150(r0)
	li r3, 0x0
	lfs f2, float_12p5_8041a178(r0)
	li r4, 0x8
	lfs f0, 0x3c(r30)
	fmr f6, f4
	lfs f1, 0x38(r30)
	fadds f2, f2, f0
	lfs f3, 0x40(r30)
	lfs f5, float_neg1_8041a214(r0)
	bl effSmallStarEntry
	lfs f4, float_0_8041a150(r0)
	li r3, 0x0
	lfs f2, float_12p5_8041a178(r0)
	li r4, 0x8
	lfs f0, 0x3c(r31)
	fmr f6, f4
	lfs f1, 0x38(r31)
	fadds f2, f2, f0
	lfs f3, 0x40(r31)
	lfs f5, float_neg1_8041a214(r0)
	bl effSmallStarEntry
	lwz r4, 0x1e4(r30)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	lwz r4, 0x1e4(r31)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	addi r3, r30, 0x5
	bl mobjDelete
	addi r3, r31, 0x5
	bl mobjDelete
	@4:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_floatswitch_red) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x38(r1)
	stfd f30, 0x30(r1)
	stfd f29, 0x28(r1)
	stmw r27, 0x14(r1)
	mr r31, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r3, r31
	bl evtGetValue
	lwz r4, 0x8(r29)
	mr r28, r3
	mr r3, r31
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0xc(r29)
	mr r3, r31
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x10(r29)
	mr r3, r31
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x14(r29)
	mr r3, r31
	bl evtGetValue
	lwz r5, gp(r0)
	lis r4, str_802C4738@ha
	addi r0, r4, str_802C4738@l
	mr r30, r3
	lwz r4, 0x14(r5)
	mr r27, r0
	mr r3, r0
	lwz r29, 0x18(r29)
	neg r0, r4
	li r5, 0x0
	or r0, r0, r4
	srwi r4, r0, 31
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r3, r28
	mr r4, r27
	bl mobjEntry
	mr r3, r28
	bl mobjNameToPtr
	fmr f1, f31
	mr r27, r3
	fmr f2, f30
	mr r3, r28
	fmr f3, f29
	bl mobjSetPosition
	lis r3, mobj_switch_red@ha
	li r0, 0x0
	addi r4, r3, mobj_switch_red@l
	mr r3, r31
	stw r4, 0x1d0(r27)
	mr r4, r29
	stw r30, 0x1d4(r27)
	lwz r5, 0x0(r27)
	ori r5, r5, 0x4
	stw r5, 0x0(r27)
	lwz r5, 0x0(r27)
	oris r5, r5, 0x40
	stw r5, 0x0(r27)
	stw r29, 0x1e4(r27)
	stw r0, 0x1dc(r27)
	bl evtGetValue
	cmpwi r3, 0x0
	beq @3
	li r0, 0x63
	stw r0, 0x1dc(r27)
	@3:
	mr r3, r27
	bl mobjCalcMtx
	li r3, 0x2
	@2:
	lfd f31, 0x38(r1)
	lfd f30, 0x30(r1)
	lfd f29, 0x28(r1)
	lmw r27, 0x14(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm USER_FUNC(evt_mobj_switch_red) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x28(r1)
	stfd f30, 0x20(r1)
	stfd f29, 0x18(r1)
	stw r31, 0x14(r1)
	mr r31, r3
	stw r30, 0x10(r1)
	stw r29, 0xc(r1)
	stw r28, 0x8(r1)
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lwz r4, 0x4(r30)
	mr r29, r3
	mr r3, r31
	bl evtGetValue
	lwz r4, 0x8(r30)
	mr r28, r3
	mr r3, r31
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0xc(r30)
	mr r3, r31
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x10(r30)
	mr r3, r31
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x14(r30)
	mr r3, r31
	bl evtGetValue
	lwz r4, gp(r0)
	cmpwi r29, 0x1
	lwz r31, 0x18(r30)
	mr r30, r3
	lwz r3, 0x14(r4)
	neg r0, r3
	or r0, r0, r3
	srwi r4, r0, 31
	beq @1
	bge @1
	cmpwi r29, 0x0
	bge @2
	b @1
	@2:
	lis r3, str_802C474C@ha
	addi r0, r3, str_802C474C@l
	mr r29, r0
	b @3
	@1:
	lis r3, str_802C475C@ha
	addi r0, r3, str_802C475C@l
	mr r29, r0
	@3:
	mr r3, r29
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @4
	li r3, 0x0
	b @5
	@4:
	mr r3, r28
	mr r4, r29
	bl mobjEntry
	mr r3, r28
	bl mobjNameToPtr
	fmr f1, f31
	mr r29, r3
	fmr f2, f30
	mr r3, r28
	fmr f3, f29
	bl mobjSetPosition
	lis r3, mobj_switch_red@ha
	li r0, 0x0
	addi r4, r3, mobj_switch_red@l
	mr r3, r29
	stw r4, 0x1d0(r29)
	stw r30, 0x1d4(r29)
	lwz r4, 0x0(r29)
	ori r4, r4, 0x44
	stw r4, 0x0(r29)
	lwz r4, 0x0(r29)
	oris r4, r4, 0xa1
	stw r4, 0x0(r29)
	stw r31, 0x1e4(r29)
	stw r0, 0x1dc(r29)
	bl mobjCalcMtx
	li r3, 0x2
	@5:
	lwz r0, 0x34(r1)
	lfd f31, 0x28(r1)
	lfd f30, 0x20(r1)
	lfd f29, 0x18(r1)
	lwz r31, 0x14(r1)
	lwz r30, 0x10(r1)
	lwz r29, 0xc(r1)
	lwz r28, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 mobj_switch_red(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r0, 0x1dc(r3)
	cmpwi r0, 0x1
	beq @1
	bge @2
	cmpwi r0, 0x0
	bge @3
	b @2
	@3:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @2
	lwz r4, 0x1d4(r31)
	bl mobjRunEvent
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x20
	cmplwi r0, 0x0
	beq @4
	subis r0, r3, 0x100
	cmplwi r0, 0x0
	bne @5
	@4:
	li r3, 0x5
	bl marioChgMot
	@5:
	addi r4, r31, 0x38
	li r3, 0x1d2
	bl psndSFXOn_3D
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	b @2
	@1:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @6
	addi r4, r31, 0x38
	li r3, 0x1d2
	bl psndSFXOn_3D
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x20
	cmplwi r0, 0x0
	bne @7
	li r3, 0x5
	bl marioChgMot
	@7:
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x0(r31)
	@6:
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @2
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r3, 0x0(r31)
	li r0, 0x0
	rlwinm r3, r3, 0, 29, 27
	stw r3, 0x0(r31)
	stw r0, 0x1dc(r31)
	@2:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_tornadoswitch_blue) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x38(r1)
	stfd f30, 0x30(r1)
	stfd f29, 0x28(r1)
	stmw r27, 0x14(r1)
	mr r31, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r3, r31
	bl evtGetValue
	lwz r4, 0x8(r29)
	mr r28, r3
	mr r3, r31
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0xc(r29)
	mr r3, r31
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x10(r29)
	mr r3, r31
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x14(r29)
	mr r3, r31
	bl evtGetValue
	lwz r5, gp(r0)
	lis r4, str_802C4770@ha
	addi r0, r4, str_802C4770@l
	mr r30, r3
	lwz r4, 0x14(r5)
	mr r27, r0
	mr r3, r0
	lwz r29, 0x18(r29)
	neg r0, r4
	li r5, 0x0
	or r0, r0, r4
	srwi r4, r0, 31
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r3, r28
	mr r4, r27
	bl mobjEntry
	mr r3, r28
	bl mobjNameToPtr
	fmr f1, f31
	mr r27, r3
	fmr f2, f30
	mr r3, r28
	fmr f3, f29
	bl mobjSetPosition
	lis r3, mobj_switch_blue@ha
	li r0, 0x0
	addi r4, r3, mobj_switch_blue@l
	mr r3, r31
	stw r4, 0x1d0(r27)
	mr r4, r29
	stw r30, 0x1d4(r27)
	lwz r5, 0x0(r27)
	ori r5, r5, 0x4
	stw r5, 0x0(r27)
	lwz r5, 0x0(r27)
	oris r5, r5, 0x100
	stw r5, 0x0(r27)
	stw r29, 0x1e4(r27)
	stw r0, 0x1dc(r27)
	bl evtGetValue
	cmpwi r3, 0x0
	beq @3
	li r0, 0x63
	stw r0, 0x1dc(r27)
	@3:
	mr r3, r27
	bl mobjCalcMtx
	li r3, 0x2
	@2:
	lfd f31, 0x38(r1)
	lfd f30, 0x30(r1)
	lfd f29, 0x28(r1)
	lmw r27, 0x14(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm USER_FUNC(evt_mobj_floatswitch_blue) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x38(r1)
	stfd f30, 0x30(r1)
	stfd f29, 0x28(r1)
	stmw r27, 0x14(r1)
	mr r31, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r3, r31
	bl evtGetValue
	lwz r4, 0x8(r29)
	mr r28, r3
	mr r3, r31
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0xc(r29)
	mr r3, r31
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x10(r29)
	mr r3, r31
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x14(r29)
	mr r3, r31
	bl evtGetValue
	lwz r5, gp(r0)
	lis r4, str_802C4788@ha
	addi r0, r4, str_802C4788@l
	mr r30, r3
	lwz r4, 0x14(r5)
	mr r27, r0
	mr r3, r0
	lwz r29, 0x18(r29)
	neg r0, r4
	li r5, 0x0
	or r0, r0, r4
	srwi r4, r0, 31
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r3, r28
	mr r4, r27
	bl mobjEntry
	mr r3, r28
	bl mobjNameToPtr
	fmr f1, f31
	mr r27, r3
	fmr f2, f30
	mr r3, r28
	fmr f3, f29
	bl mobjSetPosition
	lis r3, mobj_switch_blue@ha
	li r0, 0x0
	addi r4, r3, mobj_switch_blue@l
	mr r3, r31
	stw r4, 0x1d0(r27)
	mr r4, r29
	stw r30, 0x1d4(r27)
	lwz r5, 0x0(r27)
	ori r5, r5, 0x4
	stw r5, 0x0(r27)
	lwz r5, 0x0(r27)
	oris r5, r5, 0x40
	stw r5, 0x0(r27)
	stw r29, 0x1e4(r27)
	stw r0, 0x1dc(r27)
	bl evtGetValue
	cmpwi r3, 0x0
	beq @3
	li r0, 0x63
	stw r0, 0x1dc(r27)
	@3:
	mr r3, r27
	bl mobjCalcMtx
	li r3, 0x2
	@2:
	lfd f31, 0x38(r1)
	lfd f30, 0x30(r1)
	lfd f29, 0x28(r1)
	lmw r27, 0x14(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm USER_FUNC(evt_mobj_switch_blue) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	lis r4, vec3_802c3dc8@ha
	stw r0, 0x44(r1)
	stfd f31, 0x38(r1)
	stfd f30, 0x30(r1)
	stfd f29, 0x28(r1)
	stmw r26, 0x10(r1)
	addi r27, r4, vec3_802c3dc8@l
	mr r30, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r28, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x8(r29)
	mr r26, r3
	mr r3, r30
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0xc(r29)
	mr r3, r30
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x10(r29)
	mr r3, r30
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x14(r29)
	mr r3, r30
	bl evtGetValue
	lwz r4, gp(r0)
	cmpwi r28, 0x1
	lwz r31, 0x18(r29)
	mr r29, r3
	lwz r3, 0x14(r4)
	neg r0, r3
	or r0, r0, r3
	srwi r4, r0, 31
	beq @1
	bge @2
	cmpwi r28, 0x0
	bge @3
	b @2
	b @2
	@3:
	addi r27, r27, 0x9d8
	b @4
	@1:
	addi r27, r27, 0x9e8
	b @4
	@2:
	addi r27, r27, 0x9fc
	@4:
	mr r3, r27
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @5
	li r3, 0x0
	b @6
	@5:
	mr r3, r26
	mr r4, r27
	bl mobjEntry
	mr r3, r26
	bl mobjNameToPtr
	fmr f1, f31
	mr r27, r3
	fmr f2, f30
	mr r3, r26
	fmr f3, f29
	bl mobjSetPosition
	lis r3, mobj_switch_blue@ha
	cmpwi r28, 0x2
	addi r3, r3, mobj_switch_blue@l
	li r0, 0x0
	stw r3, 0x1d0(r27)
	stw r29, 0x1d4(r27)
	lwz r3, 0x0(r27)
	ori r3, r3, 0x44
	stw r3, 0x0(r27)
	lwz r3, 0x0(r27)
	oris r3, r3, 0xa1
	stw r3, 0x0(r27)
	stw r31, 0x1e4(r27)
	stw r0, 0x1dc(r27)
	bne @7
	lwz r0, 0x0(r27)
	ori r0, r0, 0x2
	stw r0, 0x0(r27)
	@7:
	mr r3, r30
	mr r4, r31
	bl evtGetValue
	cmpwi r3, 0x0
	beq @8
	li r0, 0x63
	stw r0, 0x1dc(r27)
	@8:
	mr r3, r27
	bl mobjCalcMtx
	li r3, 0x2
	@6:
	lfd f31, 0x38(r1)
	lfd f30, 0x30(r1)
	lfd f29, 0x28(r1)
	lmw r26, 0x10(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 mobj_switch_blue(MapObjectEntry* mobj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r0, 0x1dc(r3)
	cmpwi r0, 0x1
	beq @1
	bge @2
	cmpwi r0, 0x0
	bge @3
	b @4
	@2:
	cmpwi r0, 0x63
	beq @5
	b @4
	@3:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @4
	lwz r4, 0x1d4(r31)
	bl mobjRunEvent
	lwz r3, 0x1e0(r31)
	subis r0, r3, 0x20
	cmplwi r0, 0x0
	beq @6
	subis r0, r3, 0x100
	cmplwi r0, 0x0
	bne @7
	@6:
	li r3, 0x5
	bl marioChgMot
	@7:
	addi r4, r31, 0x38
	li r3, 0x1d2
	bl psndSFXOn_3D
	lwz r3, 0x70(r31)
	la r4, str_8041A118(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r3, 0x1dc(r31)
	addi r0, r3, 0x1
	stw r0, 0x1dc(r31)
	b @4
	@1:
	lwz r3, 0x70(r31)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	blt @4
	lwz r3, 0x70(r31)
	la r4, str_8041A12C(r0)
	li r5, 0x1
	bl animPoseSetAnim
	lfs f4, float_0_8041a150(r0)
	li r3, 0x0
	lfs f2, float_12p5_8041a178(r0)
	li r4, 0x4
	lfs f0, 0x3c(r31)
	fmr f6, f4
	lfs f1, 0x38(r31)
	fadds f2, f2, f0
	lfs f3, 0x40(r31)
	lfs f5, float_neg1_8041a214(r0)
	bl effSmallStarEntry
	lbz r4, 0x4(r31)
	bl effSmallStarCamChg
	lwz r4, 0x1e4(r31)
	li r3, 0x0
	li r5, 0x1
	bl evtSetValue
	li r0, 0x63
	stw r0, 0x1dc(r31)
	@5:
	addi r3, r31, 0x5
	bl mobjDelete
	@4:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_hit_onoff) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	stw r30, 0x8(r1)
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lwz r4, 0x4(r30)
	mr r30, r3
	mr r3, r31
	bl evtGetValue
	mr r31, r3
	mr r3, r30
	bl mobjNameToPtr
	cmpwi r31, 0x0
	beq @1
	li r30, 0x0
	mr r31, r3
	@2:
	addic. r0, r31, 0x78
	beq @3
	addi r3, r31, 0x78
	li r4, 0x1
	bl hitGrpFlagOff
	@3:
	addi r30, r30, 0x1
	addi r31, r31, 0x88
	cmpwi r30, 0x2
	blt @2
	b @4
	@1:
	li r30, 0x0
	mr r31, r3
	@5:
	addic. r0, r31, 0x78
	beq @6
	addi r3, r31, 0x78
	li r4, 0x1
	bl hitGrpFlagOn
	@6:
	addi r30, r30, 0x1
	addi r31, r31, 0x88
	cmpwi r30, 0x2
	blt @5
	@4:
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_hitevt_onoff) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
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
	la r4, str_8041A234(r0)
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	mr r3, r30
	bl mobjNameToPtr
	b @2
	@1:
	lwz r3, 0x174(r29)
	@2:
	cmpwi r31, 0x0
	beq @3
	lwz r0, 0x0(r3)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x0(r3)
	b @4
	@3:
	lwz r0, 0x0(r3)
	ori r0, r0, 0x10
	stw r0, 0x0(r3)
	@4:
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm USER_FUNC(evt_mobj_set_camid) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r29
	bl evtGetValue
	clrlwi r30, r3, 24
	mr r3, r31
	la r4, str_8041A234(r0)
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	mr r3, r31
	bl mobjNameToPtr
	b @2
	@1:
	lwz r3, 0x174(r29)
	@2:
	stb r30, 0x4(r3)
	li r3, 0x2
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm USER_FUNC(evt_mobj_wait_animation_end) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	la r4, str_8041A234(r0)
	mr r31, r3
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	mr r3, r31
	bl mobjNameToPtr
	b @2
	@1:
	lwz r3, 0x174(r30)
	@2:
	lwz r3, 0x70(r3)
	bl animPoseGetLoopTimes
	lfs f0, float_1_8041a160(r0)
	fcmpo cr0, f1, f0
	ble @3
	li r3, 0x2
	b @4
	@3:
	li r3, 0x0
	@4:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_set_anim) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r29
	bl evtGetValue
	mr r0, r3
	mr r3, r31
	mr r30, r0
	la r4, str_8041A234(r0)
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	mr r3, r31
	bl mobjNameToPtr
	b @2
	@1:
	lwz r3, 0x174(r29)
	@2:
	lwz r3, 0x70(r3)
	mr r4, r30
	li r5, 0x1
	bl animPoseSetAnim
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm USER_FUNC(evt_mobj_set_gravity_bound) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x28(r1)
	stfd f30, 0x20(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r30, r3
	mr r3, r29
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x8(r31)
	mr r3, r29
	bl evtGetFloat
	fmr f31, f1
	mr r3, r30
	la r4, str_8041A234(r0)
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	mr r3, r30
	bl mobjNameToPtr
	mr r4, r3
	b @2
	@1:
	lwz r4, 0x174(r29)
	@2:
	stfs f30, 0x68(r4)
	li r3, 0x2
	stfs f31, 0x6c(r4)
	lfd f31, 0x28(r1)
	lfd f30, 0x20(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm USER_FUNC(evt_mobj_exec_cancel) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	la r4, str_8041A234(r0)
	mr r31, r3
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	mr r3, r31
	bl mobjNameToPtr
	mr r4, r3
	b @2
	@1:
	lwz r4, 0x174(r30)
	@2:
	lwz r0, 0x0(r4)
	li r3, 0x2
	ori r0, r0, 0x1000
	stw r0, 0x0(r4)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_set_z_position) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	stw r29, 0x24(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	la r4, str_8041A234(r0)
	mr r31, r3
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	mr r3, r31
	bl mobjNameToPtr
	mr r31, r3
	b @2
	@1:
	lwz r31, 0x174(r29)
	@2:
	lwz r4, 0x38(r31)
	mr r3, r29
	lwz r5, 0x3c(r31)
	lwz r0, 0x40(r31)
	stw r4, 0x8(r1)
	lwz r4, 0x4(r30)
	stw r5, 0xc(r1)
	stw r0, 0x10(r1)
	bl evtGetFloat
	lwz r0, 0x8(r1)
	li r3, 0x2
	stfs f1, 0x10(r1)
	lwz r4, 0xc(r1)
	stw r0, 0x38(r31)
	lwz r0, 0x10(r1)
	stw r4, 0x3c(r31)
	stw r0, 0x40(r31)
	lwz r0, 0x0(r31)
	ori r0, r0, 0x4
	stw r0, 0x0(r31)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm USER_FUNC(evt_mobj_set_y_position) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	stw r29, 0x24(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	la r4, str_8041A234(r0)
	mr r31, r3
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	mr r3, r31
	bl mobjNameToPtr
	mr r31, r3
	b @2
	@1:
	lwz r31, 0x174(r29)
	@2:
	lwz r4, 0x38(r31)
	mr r3, r29
	lwz r5, 0x3c(r31)
	lwz r0, 0x40(r31)
	stw r4, 0x8(r1)
	lwz r4, 0x4(r30)
	stw r5, 0xc(r1)
	stw r0, 0x10(r1)
	bl evtGetFloat
	stfs f1, 0xc(r1)
	li r3, 0x2
	lwz r0, 0x8(r1)
	lwz r4, 0xc(r1)
	stw r0, 0x38(r31)
	lwz r0, 0x10(r1)
	stw r4, 0x3c(r31)
	stw r0, 0x40(r31)
	lwz r0, 0x0(r31)
	ori r0, r0, 0x4
	stw r0, 0x0(r31)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm USER_FUNC(evt_mobj_set_x_position) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	stw r29, 0x24(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	la r4, str_8041A234(r0)
	mr r31, r3
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	mr r3, r31
	bl mobjNameToPtr
	mr r31, r3
	b @2
	@1:
	lwz r31, 0x174(r29)
	@2:
	lwz r4, 0x38(r31)
	mr r3, r29
	lwz r5, 0x3c(r31)
	lwz r0, 0x40(r31)
	stw r4, 0x8(r1)
	lwz r4, 0x4(r30)
	stw r5, 0xc(r1)
	stw r0, 0x10(r1)
	bl evtGetFloat
	stfs f1, 0x8(r1)
	li r3, 0x2
	lwz r4, 0xc(r1)
	lwz r5, 0x8(r1)
	lwz r0, 0x10(r1)
	stw r5, 0x38(r31)
	stw r4, 0x3c(r31)
	stw r0, 0x40(r31)
	lwz r0, 0x0(r31)
	ori r0, r0, 0x4
	stw r0, 0x0(r31)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm USER_FUNC(evt_mobj_set_position) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x38(r1)
	stfd f30, 0x30(r1)
	stfd f29, 0x28(r1)
	stw r31, 0x24(r1)
	stw r30, 0x20(r1)
	stw r29, 0x1c(r1)
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
	la r4, str_8041A234(r0)
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	mr r3, r30
	bl mobjNameToPtr
	mr r6, r3
	b @2
	@1:
	lwz r6, 0x174(r29)
	@2:
	lis r4, vec3_802c3dd4@ha
	li r3, 0x2
	addi r5, r4, vec3_802c3dd4@l
	lwz r0, 0x0(r5)
	lwz r4, 0x4(r5)
	stw r0, 0x8(r1)
	lwz r0, 0x8(r5)
	stw r4, 0xc(r1)
	stfs f29, 0x8(r1)
	stw r0, 0x10(r1)
	lwz r0, 0x8(r1)
	stfs f30, 0xc(r1)
	stfs f31, 0x10(r1)
	lwz r4, 0xc(r1)
	stw r0, 0x38(r6)
	lwz r0, 0x10(r1)
	stw r4, 0x3c(r6)
	stw r0, 0x40(r6)
	lwz r0, 0x0(r6)
	ori r0, r0, 0x4
	stw r0, 0x0(r6)
	lfd f31, 0x38(r1)
	lfd f30, 0x30(r1)
	lfd f29, 0x28(r1)
	lwz r31, 0x24(r1)
	lwz r30, 0x20(r1)
	lwz r29, 0x1c(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm USER_FUNC(evt_mobj_get_z_position) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	la r4, str_8041A234(r0)
	mr r30, r3
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	mr r3, r30
	bl mobjNameToPtr
	mr r5, r3
	b @2
	@1:
	lwz r5, 0x174(r29)
	@2:
	lwz r4, 0x4(r31)
	mr r3, r29
	lfs f1, 0x40(r5)
	bl evtSetFloat
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm USER_FUNC(evt_mobj_get_y_position) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	la r4, str_8041A234(r0)
	mr r30, r3
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	mr r3, r30
	bl mobjNameToPtr
	mr r5, r3
	b @2
	@1:
	lwz r5, 0x174(r29)
	@2:
	lwz r4, 0x4(r31)
	mr r3, r29
	lfs f1, 0x3c(r5)
	bl evtSetFloat
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm USER_FUNC(evt_mobj_get_x_position) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	la r4, str_8041A234(r0)
	mr r30, r3
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	mr r3, r30
	bl mobjNameToPtr
	mr r5, r3
	b @2
	@1:
	lwz r5, 0x174(r29)
	@2:
	lwz r4, 0x4(r31)
	mr r3, r29
	lfs f1, 0x38(r5)
	bl evtSetFloat
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm USER_FUNC(evt_mobj_get_position) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	la r4, str_8041A234(r0)
	mr r31, r3
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	mr r3, r31
	bl mobjNameToPtr
	mr r31, r3
	b @2
	@1:
	lwz r31, 0x174(r29)
	@2:
	lwz r4, 0x4(r30)
	mr r3, r29
	lfs f1, 0x38(r31)
	bl evtSetFloat
	lwz r4, 0x8(r30)
	mr r3, r29
	lfs f1, 0x3c(r31)
	bl evtSetFloat
	lwz r4, 0xc(r30)
	mr r3, r29
	lfs f1, 0x40(r31)
	bl evtSetFloat
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm USER_FUNC(evt_mobj_set_scale) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x38(r1)
	stfd f30, 0x30(r1)
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	stw r29, 0x24(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	la r4, str_8041A234(r0)
	mr r31, r3
	bl strcmp
	cmpwi r3, 0x0
	bne @1
	lwz r31, 0x174(r29)
	b @2
	@1:
	mr r3, r31
	bl mobjNameToPtr
	mr r31, r3
	@2:
	lwz r4, 0x4(r30)
	mr r3, r29
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x8(r30)
	mr r3, r29
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0xc(r30)
	mr r3, r29
	bl evtGetFloat
	lis r4, vec3_802c3dc8@ha
	li r3, 0x2
	addi r5, r4, vec3_802c3dc8@l
	lwz r0, 0x0(r5)
	lwz r4, 0x4(r5)
	stw r0, 0x8(r1)
	lwz r0, 0x8(r5)
	stw r4, 0xc(r1)
	stfs f30, 0x8(r1)
	stw r0, 0x10(r1)
	lwz r0, 0x8(r1)
	stfs f31, 0xc(r1)
	stfs f1, 0x10(r1)
	lwz r4, 0xc(r1)
	stw r0, 0x44(r31)
	lwz r0, 0x10(r1)
	stw r4, 0x48(r31)
	stw r0, 0x4c(r31)
	lwz r0, 0x0(r31)
	ori r0, r0, 0x4
	stw r0, 0x0(r31)
	lfd f31, 0x38(r1)
	lfd f30, 0x30(r1)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm USER_FUNC(evt_mobj_get_kindname) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	bl mobjNameToPtr
	mr r5, r3
	lwz r4, 0x4(r31)
	mr r3, r30
	addi r5, r5, 0x15
	bl evtSetValue
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_flag_onoff) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lwz r4, 0x4(r30)
	mr r31, r3
	mr r3, r29
	bl evtGetValue
	lwz r30, 0x8(r30)
	bl mobjNameToPtr
	cmpwi r31, 0x0
	beq @1
	lwz r0, 0x0(r3)
	or r0, r0, r30
	stw r0, 0x0(r3)
	b @2
	@1:
	lwz r0, 0x0(r3)
	andc r0, r0, r30
	stw r0, 0x0(r3)
	@2:
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm USER_FUNC(evt_mobj_check) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	bl mobjNameToPtrNoAssert
	lwz r4, 0x4(r31)
	mr r5, r3
	mr r3, r30
	bl evtSetValue
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_delete) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	bl mobjDelete
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm USER_FUNC(evt_mobj_entry) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, gp(r0)
	mr r30, r3
	li r5, 0x0
	lwz r4, 0x14(r4)
	neg r0, r4
	or r0, r0, r4
	srwi r4, r0, 31
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r3, r31
	mr r4, r30
	bl mobjEntry
	li r3, 0x2
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}
// clang-format on
#endif

__declspec(section ".data") void* jumptable_8030A78C[14] = {
    (void*)((char*)evt_mobj_brick + 0x290),
    (void*)((char*)evt_mobj_brick + 0x2ac),
    (void*)((char*)evt_mobj_brick + 0x2cc),
    (void*)((char*)evt_mobj_brick + 0x2ec),
    (void*)((char*)evt_mobj_brick + 0x308),
    (void*)((char*)evt_mobj_brick + 0x308),
    (void*)((char*)evt_mobj_brick + 0x308),
    (void*)((char*)evt_mobj_brick + 0x308),
    (void*)((char*)evt_mobj_brick + 0x308),
    (void*)((char*)evt_mobj_brick + 0x308),
    (void*)((char*)evt_mobj_brick + 0x290),
    (void*)((char*)evt_mobj_brick + 0x2ac),
    (void*)((char*)evt_mobj_brick + 0x2cc),
    (void*)((char*)evt_mobj_brick + 0x2ec)
};
__declspec(section ".data") void* jumptable_8030A7C4[14] = {
    (void*)((char*)evt_mobj_brick + 0x1a0),
    (void*)((char*)evt_mobj_brick + 0x1b0),
    (void*)((char*)evt_mobj_brick + 0x1c0),
    (void*)((char*)evt_mobj_brick + 0x1d0),
    (void*)((char*)evt_mobj_brick + 0x1dc),
    (void*)((char*)evt_mobj_brick + 0x1dc),
    (void*)((char*)evt_mobj_brick + 0x1dc),
    (void*)((char*)evt_mobj_brick + 0x1dc),
    (void*)((char*)evt_mobj_brick + 0x1dc),
    (void*)((char*)evt_mobj_brick + 0x1dc),
    (void*)((char*)evt_mobj_brick + 0x1a0),
    (void*)((char*)evt_mobj_brick + 0x1b0),
    (void*)((char*)evt_mobj_brick + 0x1c0),
    (void*)((char*)evt_mobj_brick + 0x1d0)
};
__declspec(section ".data") void* jumptable_8030A7FC[14] = {
    (void*)((char*)evt_mobj_brick + 0xc4),
    (void*)((char*)evt_mobj_brick + 0xcc),
    (void*)((char*)evt_mobj_brick + 0xd4),
    (void*)((char*)evt_mobj_brick + 0xdc),
    (void*)((char*)evt_mobj_brick + 0x100),
    (void*)((char*)evt_mobj_brick + 0x100),
    (void*)((char*)evt_mobj_brick + 0x100),
    (void*)((char*)evt_mobj_brick + 0x100),
    (void*)((char*)evt_mobj_brick + 0x100),
    (void*)((char*)evt_mobj_brick + 0x100),
    (void*)((char*)evt_mobj_brick + 0xe4),
    (void*)((char*)evt_mobj_brick + 0xec),
    (void*)((char*)evt_mobj_brick + 0xf4),
    (void*)((char*)evt_mobj_brick + 0xfc)
};
__declspec(section ".data") void* jumptable_8030A834[23] = {
    (void*)((char*)mobj_recovery_blk + 0x48),
    (void*)((char*)mobj_recovery_blk + 0x88),
    (void*)((char*)mobj_recovery_blk + 0xc4),
    (void*)((char*)mobj_recovery_blk + 0x104),
    (void*)((char*)mobj_recovery_blk + 0x184),
    (void*)((char*)mobj_recovery_blk + 0x2d4),
    (void*)((char*)mobj_recovery_blk + 0x428),
    (void*)((char*)mobj_recovery_blk + 0x480),
    (void*)((char*)mobj_recovery_blk + 0x5cc),
    (void*)((char*)mobj_recovery_blk + 0x5cc),
    (void*)((char*)mobj_recovery_blk + 0x5cc),
    (void*)((char*)mobj_recovery_blk + 0x4f8),
    (void*)((char*)mobj_recovery_blk + 0x524),
    (void*)((char*)mobj_recovery_blk + 0x5cc),
    (void*)((char*)mobj_recovery_blk + 0x5cc),
    (void*)((char*)mobj_recovery_blk + 0x5cc),
    (void*)((char*)mobj_recovery_blk + 0x5cc),
    (void*)((char*)mobj_recovery_blk + 0x5cc),
    (void*)((char*)mobj_recovery_blk + 0x5cc),
    (void*)((char*)mobj_recovery_blk + 0x5cc),
    (void*)((char*)mobj_recovery_blk + 0x5cc),
    (void*)((char*)mobj_recovery_blk + 0x564),
    (void*)((char*)mobj_recovery_blk + 0x590)
};
#pragma force_active reset
