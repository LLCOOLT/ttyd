#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "manager/evtmgr_cmd.h"
#include "driver/npcdrv.h"
#include "driver/animdrv.h"
#include "mario/mario.h"
#include "string.h"
#include "eff/eff_peach_fukidashi.h"
#include "manager/evtmgr.h"
#include "driver/effdrv.h"
#include "system.h"
#include "mario/mariost.h"
#include "dolphin/os.h"
#include "dolphin/gx.h"
#include "memory.h"
#include "driver/dispdrv.h"
#include "driver/camdrv.h"
#include "dolphin/mtx.h"
__declspec(section ".rodata") extern const u32 zero_aji_00014dfc;
__declspec(section ".rodata") extern const u32 dat_aji_000152e4;
__declspec(section ".rodata") extern const f32 vec3_aji_000152e8[3];
__declspec(section ".rodata") extern const f32 vec3_aji_000152f4[3];
__declspec(section ".rodata") extern const f32 vec3_aji_00015300[3];
__declspec(section ".rodata") extern const char aji_17_str_00005184[];
__declspec(section ".rodata") extern const f32 zero_aji_00016000;
__declspec(section ".rodata") extern const f32 float_5p5_aji_00016004;
__declspec(section ".rodata") extern const f32 float_neg80_aji_00016008;
__declspec(section ".rodata") extern const f32 float_neg0p47124_aji_0001600c;
__declspec(section ".rodata") extern const f32 float_6p2832_aji_00016010;
__declspec(section ".rodata") extern const f32 float_1000_aji_00016014;
__declspec(section ".rodata") extern const f32 float_90_aji_00016018;
__declspec(section ".rodata") extern const f32 float_270_aji_0001601c;
__declspec(section ".rodata") extern const f32 float_608_aji_00016020;
__declspec(section ".rodata") extern const f32 float_480_aji_00016024;
__declspec(section ".rodata") extern const f32 float_1_aji_00016028;
__declspec(section ".rodata") extern const f32 float_28_aji_0001602c;
__declspec(section ".rodata") extern const f32 float_neg14_aji_00016030;
__declspec(section ".rodata") extern const f32 float_14_aji_00016034;
__declspec(section ".rodata") extern const f32 float_100_aji_00016038;
__declspec(section ".rodata") extern const f32 float_180_aji_0001603c;
__declspec(section ".rodata") extern const f32 float_deg2rad_aji_00016040;
__declspec(section ".rodata") extern const f32 float_neg28_aji_00016044;
__declspec(section ".rodata") extern const f32 float_55_aji_00016048;
__declspec(section ".rodata") extern const f32 float_1100_aji_0001604c;
__declspec(section ".rodata") extern const f32 float_9p5_aji_00016050;
__declspec(section ".rodata") extern const f32 float_7p5_aji_00016054;
#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
#define horogram_amb (*(const GXColor*)&dat_aji_000152e4)
#define horogram_pos (*(const Vec*)&vec3_aji_000152e8)
#define horogram_up (*(const Vec*)&vec3_aji_000152f4)
#define horogram_target (*(const Vec*)&vec3_aji_00015300)
#endif
#ifdef NONMATCHING
__declspec(section ".rodata") const char aji_17_str_00003F50[12] = "S_door1_1\0\0";
__declspec(section ".rodata") const char aji_17_str_00003F5C[12] = "S_door1_2\0\0";
__declspec(section ".rodata") const char aji_17_str_00003F68[8] = "w_bero\0";
__declspec(section ".rodata") const char aji_17_str_00003F70[8] = "aji_01\0";
__declspec(section ".rodata") const char aji_17_str_00003F78[12] = "e_bero_5\0\0\0";
__declspec(section ".rodata") const u32 zero_aji_00014dfc = 0x00000000;
__declspec(section ".rodata") const char aji_17_str_00003F88[12] = "stg7_aji_46";
__declspec(section ".rodata") const char aji_17_str_00003F94[8] = "S_kurai";
__declspec(section ".rodata") const char aji_17_str_00003F9C[24] = "SFX_VOICE_MARIO_FIND1\0\0";
__declspec(section ".rodata") const char aji_17_str_00003FB4[8] = "eff0\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00003FBC[8] = "eff1\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00003FC4[24] = "SFX_PEACH_TEC_ACTIVE1\0\0";
__declspec(section ".rodata") const char aji_17_str_00003FDC[8] = "kika_1\0";
__declspec(section ".rodata") const char str_00003FE4[8] = "kika_2\0";
__declspec(section ".rodata") const char aji_17_str_00003FEC[8] = "kika_3\0";
__declspec(section ".rodata") const char aji_17_str_00003FF4[24] = "SFX_STG7_TEC_ACTIVE1\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000400C[8] = "moni_1\0";
__declspec(section ".rodata") const char aji_17_str_00004014[12] = "S_kikai_0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004020[8] = "moza\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004028[12] = "stg7_aji_47";
__declspec(section ".rodata") const char aji_17_str_00004034[12] = "stg7_aji_48";
__declspec(section ".rodata") const char aji_17_str_00004040[24] = "SFX_STG7_TEC_SANDSTORM1";
__declspec(section ".rodata") const char aji_17_str_00004058[8] = "M_I_2\0\0";
__declspec(section ".rodata") const char aji_17_str_00004060[12] = "stg7_aji_49";
__declspec(section ".rodata") const char aji_17_str_0000406C[8] = "M_S_1\0\0";
__declspec(section ".rodata") const char aji_17_str_00004074[12] = "stg7_aji_50";
__declspec(section ".rodata") const char aji_17_str_00004080[12] = "stg7_aji_51";
__declspec(section ".rodata") const char aji_17_str_0000408C[12] = "stg7_aji_52";
__declspec(section ".rodata") const char aji_17_str_00004098[12] = "stg7_aji_53";
__declspec(section ".rodata") const char str_000040A4[12] = "stg7_aji_54";
__declspec(section ".rodata") const char aji_17_str_000040B0[8] = "M_I_N\0\0";
__declspec(section ".rodata") const char aji_17_str_000040B8[12] = "stg7_aji_55";
__declspec(section ".rodata") const char aji_17_str_000040C4[12] = "stg7_aji_56";
__declspec(section ".rodata") const char aji_17_str_000040D0[12] = "stg7_aji_57";
__declspec(section ".rodata") const char aji_17_str_000040DC[8] = "aji_16\0";
__declspec(section ".rodata") const char aji_17_str_000040E4[8] = "peach\0\0";
__declspec(section ".rodata") const char aji_17_str_000040EC[12] = "stg7_aji_59";
__declspec(section ".rodata") const char aji_17_str_000040F8[12] = "stg7_aji_60";
__declspec(section ".rodata") const char aji_17_str_00004104[24] = "SFX_STG7_TEC_SHUTDOWN1\0";
__declspec(section ".rodata") const char aji_17_str_0000411C[12] = "stg7_aji_61";
__declspec(section ".rodata") const char aji_17_str_00004128[12] = "stg7_aji_62";
__declspec(section ".rodata") const char aji_17_str_00004134[24] = "SFX_VOICE_MARIO_NOD1_4\0";
__declspec(section ".rodata") const char aji_17_str_0000414C[8] = "M_N_2\0\0";
__declspec(section ".rodata") const char aji_17_str_00004154[24] = "SFX_PEACH_MAIL_SOUSIN1\0";
__declspec(section ".rodata") const char aji_17_str_0000416C[24] = "SFX_PEACH_MAIL_SOUSIN2\0";
__declspec(section ".rodata") const char aji_17_str_00004184[16] = "ENV_STG7_AJI4\0\0";
__declspec(section ".rodata") const char aji_17_str_00004194[32] = "SFX_VOICE_PEACH_SURPRISED1_3\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000041B4[8] = "P_S_4\0\0";
__declspec(section ".rodata") const char aji_17_str_000041BC[8] = "S_kikai";
__declspec(section ".rodata") const char aji_17_str_000041C4[16] = "peach_aji_42\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000041D4[8] = "mario\0\0";
__declspec(section ".rodata") const char aji_17_str_000041DC[8] = "P_T_4\0\0";
__declspec(section ".rodata") const char aji_17_str_000041E4[16] = "peach_aji_43\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000041F4[8] = "ren1\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000041FC[16] = "peach_aji_44\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000420C[8] = "P_S_1R\0";
__declspec(section ".rodata") const char aji_17_str_00004214[8] = "P_T_1R\0";
__declspec(section ".rodata") const char aji_17_str_0000421C[16] = "peach_aji_45\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000422C[16] = "peach_aji_48\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000423C[16] = "peach_aji_49\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000424C[16] = "peach_aji_50\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000425C[16] = "peach_aji_52\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000426C[16] = "peach_aji_53\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000427C[32] = "SFX_VOICE_PEACH_SURPRISED1_2\0\0\0";
__declspec(section ".rodata") const u32 zero_aji_00015114[1] = {0x00000000};
__declspec(section ".rodata") const char aji_17_str_000042A0[8] = "P_B_2\0\0";
__declspec(section ".rodata") const char aji_17_str_000042A8[8] = "P_T_7\0\0";
__declspec(section ".rodata") const char str_000042B0[16] = "peach_aji_53_01";
__declspec(section ".rodata") const char aji_17_str_000042C0[16] = "peach_aji_54\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000042D0[8] = "P_S_1\0\0";
__declspec(section ".rodata") const char aji_17_str_000042D8[8] = "P_T_1\0\0";
__declspec(section ".rodata") const char aji_17_str_000042E0[16] = "peach_aji_55\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000042F0[16] = "peach_aji_56\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004300[16] = "peach_aji_57\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004310[16] = "peach_aji_58\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004320[8] = "P_P_1\0\0";
__declspec(section ".rodata") const char aji_17_str_00004328[8] = "P_T_9\0\0";
__declspec(section ".rodata") const char aji_17_str_00004330[16] = "peach_aji_58_01";
__declspec(section ".rodata") const char str_00004340[16] = "peach_aji_58_02";
__declspec(section ".rodata") const char aji_17_str_00004350[16] = "peach_aji_58_03";
__declspec(section ".rodata") const char aji_17_str_00004360[16] = "peach_aji_58_04";
__declspec(section ".rodata") const char aji_17_str_00004370[16] = "peach_aji_58_05";
__declspec(section ".rodata") const char aji_17_str_00004380[16] = "peach_aji_58_06";
__declspec(section ".rodata") const char aji_17_str_00004390[8] = "P_C_1\0\0";
__declspec(section ".rodata") const char aji_17_str_00004398[8] = "P_T_8\0\0";
__declspec(section ".rodata") const char aji_17_str_000043A0[16] = "peach_aji_58_07";
__declspec(section ".rodata") const char aji_17_str_000043B0[16] = "peach_aji_65\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000043C0[16] = "peach_aji_66\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000043D0[16] = "peach_aji_67\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000043E0[16] = "peach_aji_68\0\0\0";
__declspec(section ".rodata") const char str_000043F0[20] = "SFX_PEACH_KEYBOARD1";
__declspec(section ".rodata") const char aji_17_str_00004404[8] = "P_A_1R\0";
__declspec(section ".rodata") const char aji_17_str_0000440C[16] = "peach_aji_69\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000441C[8] = "S_meil\0";
__declspec(section ".rodata") const char aji_17_str_00004424[4] = "mel";
__declspec(section ".rodata") const char aji_17_str_00004428[16] = "peach_aji_70\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004438[16] = "peach_aji_71\0\0\0";
__declspec(section ".rodata") const char str_00004448[16] = "peach_aji_72\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004458[12] = "S_aji_17\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004464[8] = "kpa_00\0";
__declspec(section ".rodata") const u32 dat_aji_000152e4 = 0xFFFFFFFF;
__declspec(section ".rodata") const f32 vec3_aji_000152e8[3] = {0.0f, 0.0f, 20.0f};
__declspec(section ".rodata") const f32 vec3_aji_000152f4[3] = {0.0f, 1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_aji_00015300[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const char aji_17_str_00004494[12] = "\x83z\x83\x8d\x83O\x83\x89\x83\x80\0";
__declspec(section ".rodata") const char aji_17_str_000044A0[8] = "\x83_\x83~\x81[\0";
__declspec(section ".rodata") const char aji_17_str_000044A8[8] = "P_O_F_1";
__declspec(section ".rodata") const char aji_17_str_000044B0[8] = "P_O_F_2";
__declspec(section ".rodata") const char aji_17_str_000044B8[8] = "P_O_R_1";
__declspec(section ".rodata") const char aji_17_str_000044C0[8] = "P_O_R_2";
__declspec(section ".rodata") const char aji_17_str_000044C8[8] = "P_O_N_1";
__declspec(section ".rodata") const char aji_17_str_000044D0[8] = "P_O_N_2";
__declspec(section ".rodata") const char str_000044D8[20] = "dance_dt.step error";
__declspec(section ".rodata") const char aji_17_str_000044EC[24] = "SFX_PEACH_DANCE_TURN1\0\0";
__declspec(section ".rodata") const char aji_17_str_00004504[8] = "P_O_D_1";
__declspec(section ".rodata") const char aji_17_str_0000450C[8] = "btn_01\0";
__declspec(section ".rodata") const char aji_17_str_00004514[8] = "btn_02\0";
__declspec(section ".rodata") const char aji_17_str_0000451C[8] = "btn_03\0";
__declspec(section ".rodata") const char aji_17_str_00004524[12] = "\x83z\x83\x8d\x83O\x83\x89\x83\x80" "2";
__declspec(section ".rodata") const char aji_17_str_00004530[8] = "P_O_Z_1";
__declspec(section ".rodata") const char aji_17_str_00004538[12] = "P_O_Z_1R\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004544[8] = "P_O_S_1";
__declspec(section ".rodata") const char aji_17_str_0000454C[8] = "P_O_S_2";
__declspec(section ".rodata") const char aji_17_str_00004554[24] = "BGM_EVT_PEACH_WALTZ1\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000456C[20] = "SFX_PEACH_DANCE_NG1";
__declspec(section ".rodata") const char aji_17_str_00004580[24] = "SFX_PEACH_DANCE_APPEAR1";
__declspec(section ".rodata") const char aji_17_str_00004598[16] = "peach_aji_94\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000045A8[16] = "peach_aji_95\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000045B8[8] = "c_peach";
__declspec(section ".rodata") const char aji_17_str_000045C0[12] = "\x83s\x81[\x83`\x95P\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000045CC[12] = "c_peach_r\0\0";
__declspec(section ".rodata") const char aji_17_str_000045D8[16] = "peach_aji_76\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000045E8[16] = "peach_aji_76_01";
__declspec(section ".rodata") const char aji_17_str_000045F8[16] = "peach_aji_76_02";
__declspec(section ".rodata") const char aji_17_str_00004608[16] = "peach_aji_77\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004618[16] = "peach_aji_78\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004628[16] = "peach_aji_79\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004638[16] = "peach_aji_80\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004648[16] = "peach_aji_83\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004658[16] = "peach_aji_84\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004668[16] = "peach_aji_85\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004678[16] = "peach_aji_86\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004688[16] = "peach_aji_91\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004698[16] = "peach_aji_92\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000046A8[12] = "move_pos\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000046B4[16] = "peach_aji_93\0\0\0";
__declspec(section ".rodata") const char str_000046C4[16] = "peach_aji_96\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000046D4[16] = "peach_aji_97\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000046E4[16] = "peach_aji_98\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000046F4[16] = "peach_aji_99\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004704[16] = "peach_aji_100\0\0";
__declspec(section ".rodata") const char aji_17_str_00004714[8] = "P_S_7\0\0";
__declspec(section ".rodata") const char aji_17_str_0000471C[8] = "P_T_13\0";
__declspec(section ".rodata") const char aji_17_str_00004724[16] = "peach_aji_101\0\0";
__declspec(section ".rodata") const char aji_17_str_00004734[20] = "peach_aji_101_01\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004748[16] = "peach_aji_102\0\0";
__declspec(section ".rodata") const char aji_17_str_00004758[8] = "hei_00\0";
__declspec(section ".rodata") const char aji_17_str_00004760[16] = "peach_aji_115\0\0";
__declspec(section ".rodata") const char aji_17_str_00004770[16] = "peach_aji_116\0\0";
__declspec(section ".rodata") const char aji_17_str_00004780[16] = "peach_aji_117\0\0";
__declspec(section ".rodata") const char aji_17_str_00004790[16] = "peach_aji_118\0\0";
__declspec(section ".rodata") const char aji_17_str_000047A0[16] = "peach_aji_119\0\0";
__declspec(section ".rodata") const char aji_17_str_000047B0[20] = "peach_aji_119_01\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000047C4[20] = "peach_aji_119_02\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000047D8[16] = "peach_aji_120\0\0";
__declspec(section ".rodata") const char aji_17_str_000047E8[16] = "peach_aji_121\0\0";
__declspec(section ".rodata") const char aji_17_str_000047F8[8] = "P_G_1\0\0";
__declspec(section ".rodata") const char aji_17_str_00004800[8] = "P_G_10\0";
__declspec(section ".rodata") const char aji_17_str_00004808[16] = "peach_aji_122\0\0";
__declspec(section ".rodata") const char aji_17_str_00004818[8] = "P_E_1\0\0";
__declspec(section ".rodata") const char aji_17_str_00004820[8] = "P_E_2\0\0";
__declspec(section ".rodata") const char aji_17_str_00004828[16] = "peach_aji_123\0\0";
__declspec(section ".rodata") const char aji_17_str_00004838[16] = "peach_aji_124\0\0";
__declspec(section ".rodata") const char aji_17_str_00004848[16] = "peach_aji_125\0\0";
__declspec(section ".rodata") const char aji_17_str_00004858[16] = "peach_aji_156\0\0";
__declspec(section ".rodata") const char aji_17_str_00004868[16] = "peach_aji_157\0\0";
__declspec(section ".rodata") const char aji_17_str_00004878[20] = "peach_aji_157_01\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000488C[20] = "peach_aji_157_02\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000048A0[20] = "peach_aji_157_03\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000048B4[20] = "peach_aji_157_04\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000048C8[16] = "peach_aji_158\0\0";
__declspec(section ".rodata") const char aji_17_str_000048D8[16] = "peach_aji_159\0\0";
__declspec(section ".rodata") const char aji_17_str_000048E8[16] = "peach_aji_160\0\0";
__declspec(section ".rodata") const char aji_17_str_000048F8[16] = "peach_aji_161\0\0";
__declspec(section ".rodata") const char aji_17_str_00004908[16] = "peach_aji_163\0\0";
__declspec(section ".rodata") const char aji_17_str_00004918[16] = "peach_aji_164\0\0";
__declspec(section ".rodata") const char aji_17_str_00004928[16] = "peach_aji_165\0\0";
__declspec(section ".rodata") const char aji_17_str_00004938[16] = "peach_aji_166\0\0";
__declspec(section ".rodata") const char aji_17_str_00004948[8] = "mri_01\0";
__declspec(section ".rodata") const char aji_17_str_00004950[16] = "peach_aji_174\0\0";
__declspec(section ".rodata") const char aji_17_str_00004960[16] = "peach_aji_175\0\0";
__declspec(section ".rodata") const char aji_17_str_00004970[20] = "peach_aji_175_sel\0\0";
__declspec(section ".rodata") const char aji_17_str_00004984[16] = "peach_aji_178\0\0";
__declspec(section ".rodata") const char aji_17_str_00004994[16] = "peach_aji_179\0\0";
__declspec(section ".rodata") const char aji_17_str_000049A4[20] = "peach_aji_179_sel\0\0";
__declspec(section ".rodata") const char aji_17_str_000049B8[16] = "peach_aji_180\0\0";
__declspec(section ".rodata") const char aji_17_str_000049C8[16] = "peach_aji_181\0\0";
__declspec(section ".rodata") const char aji_17_str_000049D8[20] = "peach_aji_183_sel\0\0";
__declspec(section ".rodata") const char aji_17_str_000049EC[16] = "peach_aji_184\0\0";
__declspec(section ".rodata") const char aji_17_str_000049FC[16] = "peach_aji_185\0\0";
__declspec(section ".rodata") const char aji_17_str_00004A0C[20] = "peach_aji_185_sel\0\0";
__declspec(section ".rodata") const char aji_17_str_00004A20[16] = "peach_aji_186\0\0";
__declspec(section ".rodata") const char aji_17_str_00004A30[16] = "peach_aji_187\0\0";
__declspec(section ".rodata") const char aji_17_str_00004A40[20] = "peach_aji_187_sel\0\0";
__declspec(section ".rodata") const char aji_17_str_00004A54[20] = "peach_aji_166_01\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004A68[20] = "peach_aji_166_02\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004A7C[20] = "peach_aji_166_03\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004A90[20] = "peach_aji_166_04\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004AA4[20] = "peach_aji_166_05\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004AB8[20] = "peach_aji_166_06\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004ACC[20] = "peach_aji_166_07\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004AE0[20] = "peach_aji_166_08\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004AF4[16] = "peach_aji_167\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B04[16] = "peach_aji_168\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B14[16] = "peach_aji_169\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B24[20] = "peach_aji_181_01\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B38[16] = "peach_aji_182\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B48[16] = "peach_aji_183\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B58[16] = "peach_aji_190\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B68[16] = "peach_aji_188\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B78[20] = "peach_aji_190_01\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B8C[20] = "peach_aji_190_02\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004BA0[16] = "peach_aji_192\0\0";
__declspec(section ".rodata") const char aji_17_str_00004BB0[16] = "peach_aji_193\0\0";
__declspec(section ".rodata") const char aji_17_str_00004BC0[16] = "peach_aji_194\0\0";
__declspec(section ".rodata") const char aji_17_str_00004BD0[16] = "peach_aji_195\0\0";
__declspec(section ".rodata") const char aji_17_str_00004BE0[8] = "gor_04\0";
__declspec(section ".rodata") const char aji_17_str_00004BE8[16] = "peach_aji_206\0\0";
__declspec(section ".rodata") const char aji_17_str_00004BF8[16] = "peach_aji_207\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C08[16] = "peach_aji_208\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C18[16] = "peach_aji_209\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C28[16] = "peach_aji_210\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C38[16] = "peach_aji_211\0\0";
__declspec(section ".rodata") const char str_00004C48[16] = "peach_aji_212\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C58[16] = "peach_aji_213\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C68[16] = "peach_aji_214\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C78[16] = "peach_aji_215\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C88[16] = "peach_aji_216\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C98[16] = "peach_aji_217\0\0";
__declspec(section ".rodata") const char aji_17_str_00004CA8[16] = "peach_aji_260\0\0";
__declspec(section ".rodata") const char aji_17_str_00004CB8[16] = "peach_aji_261\0\0";
__declspec(section ".rodata") const char aji_17_str_00004CC8[16] = "peach_aji_262\0\0";
__declspec(section ".rodata") const char aji_17_str_00004CD8[16] = "peach_aji_263\0\0";
__declspec(section ".rodata") const char aji_17_str_00004CE8[16] = "peach_aji_264\0\0";
__declspec(section ".rodata") const char aji_17_str_00004CF8[16] = "peach_aji_265\0\0";
__declspec(section ".rodata") const char aji_17_str_00004D08[16] = "peach_aji_266\0\0";
__declspec(section ".rodata") const char aji_17_str_00004D18[16] = "peach_aji_267\0\0";
__declspec(section ".rodata") const char aji_17_str_00004D28[20] = "peach_aji_267_01\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004D3C[20] = "peach_aji_267_02\0\0\0";
__declspec(section ".rodata") const char str_00004D50[16] = "peach_aji_268\0\0";
__declspec(section ".rodata") const char aji_17_str_00004D60[8] = "usu_00\0";
__declspec(section ".rodata") const char aji_17_str_00004D68[16] = "peach_aji_282\0\0";
__declspec(section ".rodata") const char aji_17_str_00004D78[20] = "peach_aji_282_01\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004D8C[28] = "SFX_VOICE_PEACH_QUESTION1\0\0";
__declspec(section ".rodata") const char aji_17_str_00004DA8[20] = "peach_aji_282_02\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004DBC[20] = "peach_aji_282_03\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004DD0[20] = "peach_aji_282_04\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004DE4[16] = "peach_aji_283\0\0";
__declspec(section ".rodata") const char str_00004DF4[16] = "peach_aji_284\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E04[16] = "peach_aji_285\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E14[16] = "peach_aji_286\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E24[16] = "peach_aji_287\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E34[16] = "peach_aji_288\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E44[16] = "peach_aji_289\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E54[16] = "peach_aji_290\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E64[16] = "peach_aji_291\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E74[16] = "peach_aji_292\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E84[16] = "peach_aji_293\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E94[16] = "peach_aji_294\0\0";
__declspec(section ".rodata") const char str_00004EA4[16] = "peach_aji_295\0\0";
__declspec(section ".rodata") const char aji_17_str_00004EB4[16] = "peach_aji_296\0\0";
__declspec(section ".rodata") const char aji_17_str_00004EC4[16] = "peach_aji_297\0\0";
__declspec(section ".rodata") const char aji_17_str_00004ED4[16] = "peach_aji_298\0\0";
__declspec(section ".rodata") const char aji_17_str_00004EE4[16] = "peach_aji_299\0\0";
__declspec(section ".rodata") const char aji_17_str_00004EF4[16] = "peach_aji_300\0\0";
__declspec(section ".rodata") const char aji_17_str_00004F04[16] = "peach_aji_301\0\0";
__declspec(section ".rodata") const char aji_17_str_00004F14[16] = "peach_aji_302\0\0";
__declspec(section ".rodata") const char aji_17_str_00004F24[8] = "\x8e\xe8\x89\xba\x82P\0";
__declspec(section ".rodata") const char aji_17_str_00004F2C[12] = "\x83V\x83\x85\x83\x8a\x83\x87\x81[\0";
__declspec(section ".rodata") const char aji_17_str_00004F38[8] = "\x8e\xe8\x89\xba\x82Q\0";
__declspec(section ".rodata") const char str_00004F40[16] = "peach_aji_303\0\0";
__declspec(section ".rodata") const char aji_17_str_00004F50[32] = "SFX_VOICE_PEACH_SURPRISED2_1\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004F70[16] = "peach_aji_304\0\0";
__declspec(section ".rodata") const char aji_17_str_00004F80[24] = "BGM_EVT_STG8_3RDHEAD1\0\0";
__declspec(section ".rodata") const char aji_17_str_00004F98[16] = "peach_aji_305\0\0";
__declspec(section ".rodata") const char aji_17_str_00004FA8[16] = "peach_aji_306\0\0";
__declspec(section ".rodata") const char aji_17_str_00004FB8[16] = "peach_aji_307\0\0";
__declspec(section ".rodata") const char aji_17_str_00004FC8[16] = "peach_aji_308\0\0";
__declspec(section ".rodata") const char aji_17_str_00004FD8[16] = "peach_aji_309\0\0";
__declspec(section ".rodata") const char aji_17_str_00004FE8[16] = "peach_aji_310\0\0";
__declspec(section ".rodata") const char aji_17_str_00004FF8[16] = "peach_aji_311\0\0";
__declspec(section ".rodata") const char aji_17_str_00005008[16] = "peach_aji_312\0\0";
__declspec(section ".rodata") const char aji_17_str_00005018[8] = "S_sui2\0";
__declspec(section ".rodata") const char aji_17_str_00005020[8] = "S_sui3\0";
__declspec(section ".rodata") const char aji_17_str_00005028[24] = "SFX_PEACH_TEC_BUTTON1\0\0";
__declspec(section ".rodata") const char aji_17_str_00005040[16] = "peach_aji_313\0\0";
__declspec(section ".rodata") const char aji_17_str_00005050[16] = "peach_aji_314\0\0";
__declspec(section ".rodata") const char aji_17_str_00005060[16] = "peach_aji_315\0\0";
__declspec(section ".rodata") const char aji_17_str_00005070[12] = "monihiraku\0";
__declspec(section ".rodata") const char aji_17_str_0000507C[16] = "peach_aji_316\0\0";
__declspec(section ".rodata") const char aji_17_str_0000508C[16] = "peach_aji_317\0\0";
__declspec(section ".rodata") const char aji_17_str_0000509C[8] = "P_S_6\0\0";
__declspec(section ".rodata") const char aji_17_str_000050A4[8] = "P_T_6\0\0";
__declspec(section ".rodata") const char aji_17_str_000050AC[16] = "peach_aji_318\0\0";
__declspec(section ".rodata") const char aji_17_str_000050BC[16] = "peach_aji_319\0\0";
__declspec(section ".rodata") const char aji_17_str_000050CC[16] = "peach_aji_320\0\0";
__declspec(section ".rodata") const char aji_17_str_000050DC[16] = "peach_aji_321\0\0";
__declspec(section ".rodata") const char aji_17_str_000050EC[8] = "gor_01\0";
__declspec(section ".rodata") const char aji_17_str_000050F4[4] = "me\0";
__declspec(section ".rodata") const char aji_17_str_000050F8[16] = "stg7_aji_tec_00";
__declspec(section ".rodata") const char aji_17_str_00005108[16] = "stg7_aji_tec_01";
__declspec(section ".rodata") const char aji_17_str_00005118[12] = "S_camera_1\0";
__declspec(section ".rodata") const char aji_17_str_00005124[12] = "S_camera_2\0";
__declspec(section ".rodata") const char aji_17_str_00005130[24] = "polySurface1161_q00063\0";
__declspec(section ".rodata") const char aji_17_str_00005148[24] = "polySurface1168_q00065\0";
__declspec(section ".rodata") const char aji_17_str_00005160[8] = "ren2\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00005168[16] = "BGM_STG7_DUN2\0\0";
__declspec(section ".rodata") const char aji_17_str_00005178[12] = "keyboard\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00005184[4] = "R\0\0";
__declspec(section ".rodata") const f32 zero_aji_00016000 = 0.0f;
__declspec(section ".rodata") const f32 float_5p5_aji_00016004 = 5.5f;
__declspec(section ".rodata") const f32 float_neg80_aji_00016008 = -80.0f;
__declspec(section ".rodata") const f32 float_neg0p47124_aji_0001600c = -0.4712389f;
__declspec(section ".rodata") const f32 float_6p2832_aji_00016010 = 6.2831855f;
__declspec(section ".rodata") const f32 float_1000_aji_00016014 = 1000.0f;
__declspec(section ".rodata") const f32 float_90_aji_00016018 = 90.0f;
__declspec(section ".rodata") const f32 float_270_aji_0001601c = 270.0f;
__declspec(section ".rodata") const f32 float_608_aji_00016020 = 608.0f;
__declspec(section ".rodata") const f32 float_480_aji_00016024 = 480.0f;
__declspec(section ".rodata") const f32 float_1_aji_00016028 = 1.0f;
__declspec(section ".rodata") const f32 float_28_aji_0001602c = 28.0f;
__declspec(section ".rodata") const f32 float_neg14_aji_00016030 = -14.0f;
__declspec(section ".rodata") const f32 float_14_aji_00016034 = 14.0f;
__declspec(section ".rodata") const f32 float_100_aji_00016038 = 100.0f;
__declspec(section ".rodata") const f32 float_180_aji_0001603c = 180.0f;
__declspec(section ".rodata") const f32 float_deg2rad_aji_00016040 = 0.017453292f;
__declspec(section ".rodata") const f32 float_neg28_aji_00016044 = -28.0f;
__declspec(section ".rodata") const f32 float_55_aji_00016048 = 55.0f;
__declspec(section ".rodata") const f32 float_1100_aji_0001604c = 1100.0f;
__declspec(section ".rodata") const f32 float_9p5_aji_00016050 = 9.5f;
__declspec(section ".rodata") const f32 float_7p5_aji_00016054 = 7.5f;
#endif
extern const u32 zero_aji_00015114[];
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)
#pragma force_active on
u32 gap_05_0000014C_bss[1];
extern const char aji_17_str_00003F50[];
extern const char aji_17_str_00003F5C[];
extern const char aji_17_str_00003F68[];
extern const char aji_17_str_00003F70[];
extern const char aji_17_str_00003F78[];
extern const char aji_17_str_00003F88[];
extern const char aji_17_str_00003F94[];
extern const char aji_17_str_00003F9C[];
extern const char aji_17_str_00003FB4[];
extern const char aji_17_str_00003FBC[];
extern const char aji_17_str_00003FC4[];
extern const char aji_17_str_00003FDC[];
extern const char str_00003FE4[];
extern const char aji_17_str_00003FEC[];
extern const char aji_17_str_00003FF4[];
extern const char aji_17_str_0000400C[];
extern const char aji_17_str_00004014[];
extern const char aji_17_str_00004020[];
extern const char aji_17_str_00004028[];
extern const char aji_17_str_00004034[];
extern const char aji_17_str_00004040[];
extern const char aji_17_str_00004058[];
extern const char aji_17_str_00004060[];
extern const char aji_17_str_0000406C[];
extern const char aji_17_str_00004074[];
extern const char aji_17_str_00004080[];
extern const char aji_17_str_0000408C[];
extern const char aji_17_str_00004098[];
extern const char str_000040A4[];
extern const char aji_17_str_000040B0[];
extern const char aji_17_str_000040B8[];
extern const char aji_17_str_000040C4[];
extern const char aji_17_str_000040D0[];
extern const char aji_17_str_000040DC[];
extern const char aji_17_str_000040E4[];
extern const char aji_17_str_000040EC[];
extern const char aji_17_str_000040F8[];
extern const char aji_17_str_00004104[];
extern const char aji_17_str_0000411C[];
extern const char aji_17_str_00004128[];
extern const char aji_17_str_00004134[];
extern const char aji_17_str_0000414C[];
extern const char aji_17_str_00004154[];
extern const char aji_17_str_0000416C[];
extern const char aji_17_str_00004184[];
extern const char aji_17_str_00004194[];
extern const char aji_17_str_000041B4[];
extern const char aji_17_str_000041BC[];
extern const char aji_17_str_000041C4[];
extern const char aji_17_str_000041D4[];
extern const char aji_17_str_000041DC[];
extern const char aji_17_str_000041E4[];
extern const char aji_17_str_000041F4[];
extern const char aji_17_str_000041FC[];
extern const char aji_17_str_0000420C[];
extern const char aji_17_str_00004214[];
extern const char aji_17_str_0000421C[];
extern const char aji_17_str_0000422C[];
extern const char aji_17_str_0000423C[];
extern const char aji_17_str_0000424C[];
extern const char aji_17_str_0000425C[];
extern const char aji_17_str_0000426C[];
extern const char aji_17_str_0000427C[];
extern const char aji_17_str_000042A0[];
extern const char aji_17_str_000042A8[];
extern const char str_000042B0[];
extern const char aji_17_str_000042C0[];
extern const char aji_17_str_000042D0[];
extern const char aji_17_str_000042D8[];
extern const char aji_17_str_000042E0[];
extern const char aji_17_str_000042F0[];
extern const char aji_17_str_00004300[];
extern const char aji_17_str_00004310[];
extern const char aji_17_str_00004320[];
extern const char aji_17_str_00004328[];
extern const char aji_17_str_00004330[];
extern const char str_00004340[];
extern const char aji_17_str_00004350[];
extern const char aji_17_str_00004360[];
extern const char aji_17_str_00004370[];
extern const char aji_17_str_00004380[];
extern const char aji_17_str_00004390[];
extern const char aji_17_str_00004398[];
extern const char aji_17_str_000043A0[];
extern const char aji_17_str_000043B0[];
extern const char aji_17_str_000043C0[];
extern const char aji_17_str_000043D0[];
extern const char aji_17_str_000043E0[];
extern const char str_000043F0[];
extern const char aji_17_str_00004404[];
extern const char aji_17_str_0000440C[];
extern const char aji_17_str_0000441C[];
extern const char aji_17_str_00004424[];
extern const char aji_17_str_00004428[];
extern const char aji_17_str_00004438[];
extern const char str_00004448[];
extern const char aji_17_str_00004458[];
extern const char aji_17_str_00004464[];
extern const char aji_17_str_00004494[];
extern const char aji_17_str_000044A0[];
extern const char aji_17_str_000044A8[];
extern const char aji_17_str_000044B0[];
extern const char aji_17_str_000044B8[];
extern const char aji_17_str_000044C0[];
extern const char aji_17_str_000044C8[];
extern const char aji_17_str_000044D0[];
extern const char str_000044D8[];
extern const char aji_17_str_000044EC[];
extern const char aji_17_str_00004504[];
extern const char aji_17_str_0000450C[];
extern const char aji_17_str_00004514[];
extern const char aji_17_str_0000451C[];
extern const char aji_17_str_00004524[];
extern const char aji_17_str_00004530[];
extern const char aji_17_str_00004538[];
extern const char aji_17_str_00004544[];
extern const char aji_17_str_0000454C[];
extern const char aji_17_str_00004554[];
extern const char aji_17_str_0000456C[];
extern const char aji_17_str_00004580[];
extern const char aji_17_str_00004598[];
extern const char aji_17_str_000045A8[];
extern const char aji_17_str_000045B8[];
extern const char aji_17_str_000045C0[];
extern const char aji_17_str_000045CC[];
extern const char aji_17_str_000045D8[];
extern const char aji_17_str_000045E8[];
extern const char aji_17_str_000045F8[];
extern const char aji_17_str_00004608[];
extern const char aji_17_str_00004618[];
extern const char aji_17_str_00004628[];
extern const char aji_17_str_00004638[];
extern const char aji_17_str_00004648[];
extern const char aji_17_str_00004658[];
extern const char aji_17_str_00004668[];
extern const char aji_17_str_00004678[];
extern const char aji_17_str_00004688[];
extern const char aji_17_str_00004698[];
extern const char aji_17_str_000046A8[];
extern const char aji_17_str_000046B4[];
extern const char str_000046C4[];
extern const char aji_17_str_000046D4[];
extern const char aji_17_str_000046E4[];
extern const char aji_17_str_000046F4[];
extern const char aji_17_str_00004704[];
extern const char aji_17_str_00004714[];
extern const char aji_17_str_0000471C[];
extern const char aji_17_str_00004724[];
extern const char aji_17_str_00004734[];
extern const char aji_17_str_00004748[];
extern const char aji_17_str_00004758[];
extern const char aji_17_str_00004760[];
extern const char aji_17_str_00004770[];
extern const char aji_17_str_00004780[];
extern const char aji_17_str_00004790[];
extern const char aji_17_str_000047A0[];
extern const char aji_17_str_000047B0[];
extern const char aji_17_str_000047C4[];
extern const char aji_17_str_000047D8[];
extern const char aji_17_str_000047E8[];
extern const char aji_17_str_000047F8[];
extern const char aji_17_str_00004800[];
extern const char aji_17_str_00004808[];
extern const char aji_17_str_00004818[];
extern const char aji_17_str_00004820[];
extern const char aji_17_str_00004828[];
extern const char aji_17_str_00004838[];
extern const char aji_17_str_00004848[];
extern const char aji_17_str_00004858[];
extern const char aji_17_str_00004868[];
extern const char aji_17_str_00004878[];
extern const char aji_17_str_0000488C[];
extern const char aji_17_str_000048A0[];
extern const char aji_17_str_000048B4[];
extern const char aji_17_str_000048C8[];
extern const char aji_17_str_000048D8[];
extern const char aji_17_str_000048E8[];
extern const char aji_17_str_000048F8[];
extern const char aji_17_str_00004908[];
extern const char aji_17_str_00004918[];
extern const char aji_17_str_00004928[];
extern const char aji_17_str_00004938[];
extern const char aji_17_str_00004948[];
extern const char aji_17_str_00004950[];
extern const char aji_17_str_00004960[];
extern const char aji_17_str_00004970[];
extern const char aji_17_str_00004984[];
extern const char aji_17_str_00004994[];
extern const char aji_17_str_000049A4[];
extern const char aji_17_str_000049B8[];
extern const char aji_17_str_000049C8[];
extern const char aji_17_str_000049D8[];
extern const char aji_17_str_000049EC[];
extern const char aji_17_str_000049FC[];
extern const char aji_17_str_00004A0C[];
extern const char aji_17_str_00004A20[];
extern const char aji_17_str_00004A30[];
extern const char aji_17_str_00004A40[];
extern const char aji_17_str_00004A54[];
extern const char aji_17_str_00004A68[];
extern const char aji_17_str_00004A7C[];
extern const char aji_17_str_00004A90[];
extern const char aji_17_str_00004AA4[];
extern const char aji_17_str_00004AB8[];
extern const char aji_17_str_00004ACC[];
extern const char aji_17_str_00004AE0[];
extern const char aji_17_str_00004AF4[];
extern const char aji_17_str_00004B04[];
extern const char aji_17_str_00004B14[];
extern const char aji_17_str_00004B24[];
extern const char aji_17_str_00004B38[];
extern const char aji_17_str_00004B48[];
extern const char aji_17_str_00004B58[];
extern const char aji_17_str_00004B68[];
extern const char aji_17_str_00004B78[];
extern const char aji_17_str_00004B8C[];
extern const char aji_17_str_00004BA0[];
extern const char aji_17_str_00004BB0[];
extern const char aji_17_str_00004BC0[];
extern const char aji_17_str_00004BD0[];
extern const char aji_17_str_00004BE0[];
extern const char aji_17_str_00004BE8[];
extern const char aji_17_str_00004BF8[];
extern const char aji_17_str_00004C08[];
extern const char aji_17_str_00004C18[];
extern const char aji_17_str_00004C28[];
extern const char aji_17_str_00004C38[];
extern const char str_00004C48[];
extern const char aji_17_str_00004C58[];
extern const char aji_17_str_00004C68[];
extern const char aji_17_str_00004C78[];
extern const char aji_17_str_00004C88[];
extern const char aji_17_str_00004C98[];
extern const char aji_17_str_00004CA8[];
extern const char aji_17_str_00004CB8[];
extern const char aji_17_str_00004CC8[];
extern const char aji_17_str_00004CD8[];
extern const char aji_17_str_00004CE8[];
extern const char aji_17_str_00004CF8[];
extern const char aji_17_str_00004D08[];
extern const char aji_17_str_00004D18[];
extern const char aji_17_str_00004D28[];
extern const char aji_17_str_00004D3C[];
extern const char str_00004D50[];
extern const char aji_17_str_00004D60[];
extern const char aji_17_str_00004D68[];
extern const char aji_17_str_00004D78[];
extern const char aji_17_str_00004D8C[];
extern const char aji_17_str_00004DA8[];
extern const char aji_17_str_00004DBC[];
extern const char aji_17_str_00004DD0[];
extern const char aji_17_str_00004DE4[];
extern const char str_00004DF4[];
extern const char aji_17_str_00004E04[];
extern const char aji_17_str_00004E14[];
extern const char aji_17_str_00004E24[];
extern const char aji_17_str_00004E34[];
extern const char aji_17_str_00004E44[];
extern const char aji_17_str_00004E54[];
extern const char aji_17_str_00004E64[];
extern const char aji_17_str_00004E74[];
extern const char aji_17_str_00004E84[];
extern const char aji_17_str_00004E94[];
extern const char str_00004EA4[];
extern const char aji_17_str_00004EB4[];
extern const char aji_17_str_00004EC4[];
extern const char aji_17_str_00004ED4[];
extern const char aji_17_str_00004EE4[];
extern const char aji_17_str_00004EF4[];
extern const char aji_17_str_00004F04[];
extern const char aji_17_str_00004F14[];
extern const char aji_17_str_00004F24[];
extern const char aji_17_str_00004F2C[];
extern const char aji_17_str_00004F38[];
extern const char str_00004F40[];
extern const char aji_17_str_00004F50[];
extern const char aji_17_str_00004F70[];
extern const char aji_17_str_00004F80[];
extern const char aji_17_str_00004F98[];
extern const char aji_17_str_00004FA8[];
extern const char aji_17_str_00004FB8[];
extern const char aji_17_str_00004FC8[];
extern const char aji_17_str_00004FD8[];
extern const char aji_17_str_00004FE8[];
extern const char aji_17_str_00004FF8[];
extern const char aji_17_str_00005008[];
extern const char aji_17_str_00005018[];
extern const char aji_17_str_00005020[];
extern const char aji_17_str_00005028[];
extern const char aji_17_str_00005040[];
extern const char aji_17_str_00005050[];
extern const char aji_17_str_00005060[];
extern const char aji_17_str_00005070[];
extern const char aji_17_str_0000507C[];
extern const char aji_17_str_0000508C[];
extern const char aji_17_str_0000509C[];
extern const char aji_17_str_000050A4[];
extern const char aji_17_str_000050AC[];
extern const char aji_17_str_000050BC[];
extern const char aji_17_str_000050CC[];
extern const char aji_17_str_000050DC[];
extern const char aji_17_str_000050EC[];
extern const char aji_17_str_000050F4[];
extern const char aji_17_str_000050F8[];
extern const char aji_17_str_00005108[];
extern const char aji_17_str_00005118[];
extern const char aji_17_str_00005124[];
extern const char aji_17_str_00005130[];
extern const char aji_17_str_00005148[];
extern const char aji_17_str_00005160[];
extern const char aji_17_str_00005168[];
extern const char aji_17_str_00005178[];

typedef struct DanceData { u16 flags; u8 step; u8 movePos; f32 cx; f32 cy; f32 rot; } DanceData;
double sin(double x);
double cos(double x);
typedef struct HorogramWork { void* buf0; void* buf1; GXTexObj tex0; GXTexObj tex1; u16 ready; u16 flags; } HorogramWork;
HorogramWork* horogram_wp;
DanceData dance_dt;
void peach_capture(CameraId cameraId, void* param);
void peach_capture(CameraId cameraId, void* param);
void disp_horogram(CameraId cameraId, void* param);
void disp_horogram(CameraId cameraId, void* param);
void noiseDisp(CameraId cameraId, void* param);
void noiseDisp(CameraId cameraId, void* param);
int rand(void);

static s32 bgm_start_wait(EventEntry* event, BOOL isFirstCall);
static s32 bgm_start_wait(EventEntry* event, BOOL isFirstCall);
s32 btn_check(EventEntry* event, BOOL isFirstCall);
s32 btn_check(EventEntry* event, BOOL isFirstCall);
s32 compute_horogram_pos(EventEntry* event, BOOL isFirstCall);
s32 compute_horogram_pos(EventEntry* event, BOOL isFirstCall);
s32 compute_move_pos(EventEntry* event, BOOL isFirstCall);
s32 compute_move_pos(EventEntry* event, BOOL isFirstCall);
s32 compute_peach_pos(EventEntry* event, BOOL isFirstCall);
s32 compute_peach_pos(EventEntry* event, BOOL isFirstCall);
s32 dance_data_init(EventEntry* event, BOOL isFirstCall);
s32 dance_data_init(EventEntry* event, BOOL isFirstCall);
s32 dance_flag_check(EventEntry* event, BOOL isFirstCall);
s32 dance_flag_check(EventEntry* event, BOOL isFirstCall);
s32 dance_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 dance_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 dance_get_step(EventEntry* event, BOOL isFirstCall);
s32 dance_get_step(EventEntry* event, BOOL isFirstCall);
s32 dance_reverse(EventEntry* event, BOOL isFirstCall);
s32 dance_reverse(EventEntry* event, BOOL isFirstCall);
s32 disp_horogram_evt(EventEntry* event, BOOL isFirstCall);
s32 disp_horogram_evt(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_exec_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_info(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_mapchange(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_off(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_set(EventEntry* event, BOOL isFirstCall);
s32 evt_eff_fukidashi(EventEntry* event, BOOL isFirstCall);
s32 evt_eff_softdelete(EventEntry* event, BOOL isFirstCall);
s32 evt_fade_end_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_fade_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_fade_in(EventEntry* event, BOOL isFirstCall);
s32 evt_fade_out(EventEntry* event, BOOL isFirstCall);
s32 evt_fade_set_mapchange_type(EventEntry* event, BOOL isFirstCall);
s32 evt_fade_softfocus_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_fade_tec_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_fuki_btn(EventEntry* event, BOOL isFirstCall);
s32 evt_fuki_btn(EventEntry* event, BOOL isFirstCall);
s32 evt_fuki_btn_set_batu(EventEntry* event, BOOL isFirstCall);
s32 evt_fuki_btn_set_batu(EventEntry* event, BOOL isFirstCall);
s32 evt_map_checkanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_pauseanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_playanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_replayanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_set_blend(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_rotate(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_scale(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_trans(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_adjust_dir(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_dispflag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_dispdir(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_mode(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_party(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_jump_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_key_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_kill_party(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_mov_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_mov_pos2(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_dir(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_dispdir(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_mode(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_party(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_pose(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_reardir(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_wait_move_end(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_continue(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print_party(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_select(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_toge(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_move_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_pera_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_anim(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_autotalkpose(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_color(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_height(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_ry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_tribe(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_width(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_setup(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_status_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_party_move_pos2(EventEntry* event, BOOL isFirstCall);
s32 evt_party_run(EventEntry* event, BOOL isFirstCall);
s32 evt_party_set_dir(EventEntry* event, BOOL isFirstCall);
s32 evt_party_set_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_stop(EventEntry* event, BOOL isFirstCall);
s32 evt_peach_set_condition(EventEntry* event, BOOL isFirstCall);
s32 evt_pouch_all_party_recovery(EventEntry* event, BOOL isFirstCall);
s32 evt_pouch_mario_recovery(EventEntry* event, BOOL isFirstCall);
s32 evt_run_case_evt(EventEntry* event, BOOL isFirstCall);
s32 evt_seq_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_shuryolight_init_2_text_B870(EventEntry* event, BOOL isFirstCall);
s32 evt_shuryolight_run_evt_2_text_B538(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmoff_f(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_envoff_f(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_envon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_envon_f(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_set_rev_mode(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfx_all_stop(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfx_vol(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxon_3d(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_get_stopwatch(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_intpl_msec_get_value(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_intpl_msec_init(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_random(EventEntry* event, BOOL isFirstCall);
s32 get_center(EventEntry* event, BOOL isFirstCall);
s32 get_center(EventEntry* event, BOOL isFirstCall);
s32 get_local_rotate(EventEntry* event, BOOL isFirstCall);
s32 get_local_rotate(EventEntry* event, BOOL isFirstCall);
s32 horogram_cap_evt(EventEntry* event, BOOL isFirstCall);
s32 horogram_cap_evt(EventEntry* event, BOOL isFirstCall);
s32 horogram_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 horogram_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 horogram_init(EventEntry* event, BOOL isFirstCall);
s32 horogram_init(EventEntry* event, BOOL isFirstCall);
s32 horogram_set_pose(EventEntry* event, BOOL isFirstCall);
s32 horogram_set_pose(EventEntry* event, BOOL isFirstCall);
s32 move_center(EventEntry* event, BOOL isFirstCall);
s32 move_center(EventEntry* event, BOOL isFirstCall);
s32 noise(EventEntry* event, BOOL isFirstCall);
s32 noise(EventEntry* event, BOOL isFirstCall);
s32 peach_dance_after_fail(EventEntry* event, BOOL isFirstCall);
s32 peach_dance_after_fail(EventEntry* event, BOOL isFirstCall);
s32 peach_evt_stg4_read_quiz_data(EventEntry* event, BOOL isFirstCall);
s32 peach_evt_stg4_read_quiz_data(EventEntry* event, BOOL isFirstCall);
static s32 peach_set_pose(EventEntry* event, BOOL isFirstCall);
static s32 peach_set_pose(EventEntry* event, BOOL isFirstCall);
s32 set_local_rotate(EventEntry* event, BOOL isFirstCall);
s32 set_local_rotate(EventEntry* event, BOOL isFirstCall);
s32 set_npc_pos(EventEntry* event, BOOL isFirstCall);
s32 set_npc_pos(EventEntry* event, BOOL isFirstCall);
static s32 viewport(EventEntry* event, BOOL isFirstCall);
static s32 viewport(EventEntry* event, BOOL isFirstCall);
s32 wait_move_end(EventEntry* event, BOOL isFirstCall);
s32 wait_move_end(EventEntry* event, BOOL isFirstCall);
s32 wait_action_begin(EventEntry* event, BOOL isFirstCall);
s32 wait_action_begin(EventEntry* event, BOOL isFirstCall);
s32 wait_action_end(EventEntry* event, BOOL isFirstCall);
s32 wait_action_end(EventEntry* event, BOOL isFirstCall);
void peach_capture(CameraId cameraId, void* param);
void disp_horogram(CameraId cameraId, void* param);
static void polygon(f32 x, f32 y, f32 w, f32 h, f32 s, f32 t);
static void polygon(f32 x, f32 y, f32 w, f32 h, f32 s, f32 t);
void noiseDisp(CameraId cameraId, void* param);
extern s32 bero_case_entry[];
extern s32 bero_close_door_play_se[];
extern s32 bero_open_door_play_se[];
extern s32 evt_bero_info_run[];
extern s32 evt_memcard_save[];
extern s32 evt_sub_stopwatch[];
extern s32 npc_init_evt[];
extern s32 shuryolight_head_normal_2_data_37004[];
extern s32 shuryolight_pow_normal_2_data_36ED8[];
extern s32 shuryolight_tue_normal_2_data_37104[];

__declspec(section ".data") u64 fd_aji_17_negone_one_374;
__declspec(section ".data") s32 fd_aji_17_neg_one_382[1];
__declspec(section ".data") s32 fd_aji_17___local_PI_383[1];
__declspec(section ".data") s32 fd_aji_17___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_aji_17_one_negone_373;
__declspec(section ".data") s32 fd_aji_17___local_PIO2_384[1];
__declspec(section ".data") s32 fd_aji_17_one_381[1];
__declspec(section ".data") u64 fd_aji_17_negone_one_360;
__declspec(section ".data") s32 fd_aji_17_neg_one_365[1];
__declspec(section ".data") s32 fd_aji_17___local_PI_366[1];
__declspec(section ".data") s32 fd_aji_17___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_aji_17_one_negone_359;
__declspec(section ".data") s32 fd_aji_17___local_PIO2_367[1];
__declspec(section ".data") s32 fd_aji_17_one_364[1];
static s32 w_door_close[22];
static s32 w_door_open[22];
static s32 bero_entry_data[30];
s32 evt_emergency[48];
s32 evt_last[728];
s32 evt_last2[339];
s32 evt_camera[68];
s32 mail_sousin_se[36];
static s32 peach_evt_stg1[1131];
f32 move_pos_list[15][2];
s32 peach_dance_move[95];
s32 peach_dance_pose[44];
__declspec(section ".data") s32 peach_dance_action_step[2];
s32 dance_action_turn_sub[108];
__declspec(section ".data") s32 peach_dance_action_turn[12];
s32 peach_dance_action_reverse[18];
s32 peach_dance_action_fail[28];
s32 dance_btn_disp_sub[49];
s32 dance_btn_disp[25];
s32 dance_btn_batu[20];
s32 dance_btn_clear[56];
s32 dance_btn_clear_all[47];
s32 wait_action_time[16];
s32 peach_dance_dark[27];
s32 peach_dance_light[27];
s32 peach_evt_dance[504];
static s32 peach_evt_stg2[900];
static s32 peach_evt_stg3[352];
static s32 peach_evt_stg3_1[650];
s32 peach_evt_stg4_quiz_data[5][4];
static s32 peach_evt_stg4[980];
static s32 peach_evt_stg5[408];
static s32 peach_evt_stg5_1[528];
static s32 peach_evt_stg6[1467];
__declspec(section ".data") static s32 teshita1_init[9];
__declspec(section ".data") static s32 teshita2_init[9];
__declspec(section ".data") static s32 syuryo_init[9];
static s32 npcEnt[92];
s32 tec_talk[36];
s32 aji_17_init_evt[253];

#pragma defer_codegen off
s32 peach_evt_stg4_read_quiz_data(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    s32 no = evtGetValue(event, args[0]);

    evtSetValue(event, args[1], peach_evt_stg4_quiz_data[no][0]);
    evtSetValue(event, args[2], peach_evt_stg4_quiz_data[no][1]);
    evtSetValue(event, args[3], peach_evt_stg4_quiz_data[no][2]);
    evtSetValue(event, args[4], peach_evt_stg4_quiz_data[no][3]);
    return EVT_RETURN_DONE;
}

BOOL psndBGMStartCheck(s32 id);

static s32 bgm_start_wait(EventEntry* event, BOOL isFirstCall) {
    return psndBGMStartCheck(1) ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}
#pragma defer_codegen on

__declspec(section ".data") u64 fd_aji_17_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_17_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_17___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_17___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_17_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_17___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_17_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_aji_17_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_17_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_17___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_17___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_17_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_17___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_17_one_364[] = {
    1065353216,
};

static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
    CALL(evt_mapobj_trans, 0, STRING(((char*)aji_17_str_00003F50)), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING(((char*)aji_17_str_00003F5C)), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
    CALL(evt_mapobj_trans, 0, STRING(((char*)aji_17_str_00003F50)), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING(((char*)aji_17_str_00003F5C)), 0, 0, LW(0))
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)((char*)aji_17_str_00003F68), 65546, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)aji_17_str_00003F70), (s32)((char*)aji_17_str_00003F78), 327685, (s32)w_door_close, (s32)w_door_open, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};
static s32 viewport(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 w = evtGetFloat(event, args[2]);
    f32 h = evtGetFloat(event, args[3]);
    CameraEntry* cam;

    cam = camGetPtr(CAMERA_3D);
    cam->viewport[0] = x;
    cam->viewport[1] = y;
    cam->viewport[2] = w;
    cam->viewport[3] = h;
    cam = camGetPtr(CAMERA_2D);
    cam->viewport[0] = x;
    cam->viewport[1] = y;
    cam->viewport[2] = w;
    cam->viewport[3] = h;
    return EVT_RETURN_DONE;
}

void C_MTXLookAt(Mtx m, const Point3d* camPos, const Vec* camUp, const Point3d* target);
void C_MTXOrtho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void DCFlushRange(void* addr, u32 nBytes);
void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
void GXClearVtxDesc(void);
void GXCopyTex(void* dest, GXBool clear);
void GXGetCullMode(GXCullMode* mode);
void GXGetProjectionv(f32* ptr);
void GXGetScissor(u32* left, u32* top, u32* wd, u32* ht);
u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, u8 mipmap, u8 max_lod);
void GXGetViewportv(f32* vp);
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
void GXSetChanAmbColor(GXChannelID chan, GXColor amb_color);
void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src, u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn);
void GXSetChanMatColor(GXChannelID chan, GXColor mat_color);
void GXSetCullMode(GXCullMode mode);
void GXSetCurrentMtx(u32 id);
void GXSetNumChans(u8 nChans);
void GXSetNumTevStages(u8 nStages);
void GXSetNumTexGens(u8 nTexGens);
void GXSetProjection(const f32 mtx[4][4], GXProjectionType type);
void GXSetProjectionv(const f32* ptr);
void GXSetScissor(u32 left, u32 top, u32 wd, u32 ht);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevColor(GXTevRegID id, GXColor color);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx);
void GXSetTexCopyDst(u16 wd, u16 ht, GXTexFmt fmt, GXBool mipmap);
void GXSetTexCopySrc(u16 left, u16 top, u16 wd, u16 ht);
void GXSetViewport(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz);
void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac);
void GXSetVtxDesc(GXAttr attr, GXAttrType type);
void GXSetZCompLoc(GXBool before_tex);
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXCopy(const Mtx src, Mtx dst);
void PSMTXIdentity(Mtx m);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
int strcat();
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
#ifdef NONMATCHING
void noiseDisp(CameraId cameraId, void* param) {
    s32 x;
    s32 ry;
    s32 y;
    s32 by;
    s32 off;
    CameraEntry* cam;
    s32 len;
    u8 col;
    GXTexObj tex;
    s32 n;
    u8* buf;
    Mtx mtx;
    s32 start;
    s32 y1;
    cam = camGetPtr(cameraId);
    buf = smartAlloc(GXGetTexBufferSize(64, 64, GX_TF_I8, GX_FALSE, 0), 3)->address;
    for (y = 0; y < 64; y++) {
        by = y / 4;
        ry = y % 4;
        for (x = 0; x < 64; x++) {
            off = (x / 8) * 32 + (by << 8); off += x % 8; off += (ry << 3); col = (y & 1) ? 0xFF : 0; buf[off] = col;
        }
        n = rand() % 100 + 100;
        by = by * 256;
        y1 = ry * 8;
        for (ry = 0; ry < n; ry++) {
            len = rand() % 4 + 2;
            start = rand() % (65 - len);
            col = rand() % 255;
            for (x = start; x < start + len; x++) {
                off = x / 8 * 32; off = off + by; off += x % 8; off += y1; buf[off] = col;
            }
        }
    }
    DCFlushRange(buf, 0x1000);
    GXInitTexObj(&tex, buf, 64, 64, GX_TF_I8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(&tex, GX_NEAR, GX_NEAR, EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(zero_aji_00016000, 0.0f), GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&tex, GX_TEXMAP0);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    PSMTXScale(mtx, EXT_LIT(float_9p5_aji_00016050, 9.5f), EXT_LIT(float_7p5_aji_00016054, 7.5f), EXT_LIT(zero_aji_00016000, 0.0f));
    GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevColor(GX_TEVREG0, (GXColor){0, 0, 0, (u8)(s32)param});
    GXLoadPosMtxImm(cam->view, GX_PNMTX0);
    GXSetCurrentMtx(0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3s16(-gp->fbWidth / 2, gp->efbHeight / 2, 0);
    GXTexCoord2s16(0, 1);
    GXPosition3s16(gp->fbWidth / 2, gp->efbHeight / 2, 0);
    GXTexCoord2s16(1, 1);
    GXPosition3s16(gp->fbWidth / 2, -gp->efbHeight / 2, 0);
    GXTexCoord2s16(1, 0);
    GXPosition3s16(-gp->fbWidth, -gp->efbHeight / 2, 0);
    GXTexCoord2s16(0, 0);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void noiseDisp(CameraId cameraId, void* param) {
	asm volatile {
		opword 0x9421FF70
		opword 0x7C0802A6
		opword 0x90010094
		opword 0xBEC10068
		opword 0x7C992378
		bl camGetPtr
		opword 0x7C7E1B78
		opword 0x38600040
		opword 0x38800040
		opword 0x38A00001
		opword 0x38C00000
		opword 0x38E00000
		bl GXGetTexBufferSize
		opword 0x38800003
		bl smartAlloc
		opword 0x83430000
		opword 0x3B800000
		opword 0x5780F002
		opword 0x57840FFE
		opword 0x7C040050
		opword 0x7F851670
		opword 0x5403103E
		opword 0x38000040
		opword 0x7FE50194
		opword 0x578907FE
		opword 0x7FA32214
		opword 0x39400000
		opword 0x57E4402E
		opword 0x38A000FF
		opword 0x57A31838
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
		opword 0x7CDA01AE
		opword 0x4200FFC0
		bl rand
		opword 0x38800064
		opword 0x57FF402E
		opword 0x7C0323D6
		opword 0x57B81838
		opword 0x3BA00000
		opword 0x7C0021D6
		opword 0x7C601850
		opword 0x3B630064
		opword 0x480000A0
		bl rand
		opword 0x5460F002
		opword 0x54630FFE
		opword 0x7C030050
		opword 0x5400103E
		opword 0x7C601A14
		opword 0x3AE30002
		bl rand
		opword 0x20970041
		opword 0x7C0323D6
		opword 0x7C0021D6
		opword 0x7EC01850
		bl rand
		opword 0x38A000FF
		opword 0x7CD6BA14
		opword 0x7C832BD6
		opword 0x7EC7B378
		opword 0x7C163050
		opword 0x7C8429D6
		opword 0x7C641850
		opword 0x5465063E
		opword 0x7C0903A6
		opword 0x7C163000
		opword 0x4080003C
		opword 0x7CE41E70
		opword 0x54E0E804
		opword 0x54E30FFE
		opword 0x38E70001
		opword 0x7C840194
		opword 0x7C030050
		opword 0x54842834
		opword 0x5400183E
		opword 0x7C84FA14
		opword 0x7C001A14
		opword 0x7C040214
		opword 0x7C00C214
		opword 0x7CBA01AE
		opword 0x4200FFCC
		opword 0x3BBD0001
		opword 0x7C1DD800
		opword 0x4180FF60
		opword 0x3B9C0001
		opword 0x2C1C0040
		opword 0x4180FEB0
		opword 0x7F43D378
		opword 0x38801000
		bl DCFlushRange
		opword 0x7F44D378
		opword 0x38610010
		opword 0x38A00040
		opword 0x38C00040
		opword 0x38E00001
		opword 0x39000001
		opword 0x39200001
		opword 0x39400000
		bl GXInitTexObj
		lis r4, zero_aji_00016000@ha
		opword 0x38610010
		addi r5, r4, zero_aji_00016000@l
		opword 0x38800000
		opword 0xC0250000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0xFC400890
		opword 0x39000000
		opword 0xFC600890
		bl GXInitTexObjLOD
		opword 0x38610010
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x38600000
		bl GXSetNumChans
		opword 0x38600001
		bl GXSetNumTexGens
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0001E
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		lis r6, float_9p5_aji_00016050@ha
		lis r5, float_7p5_aji_00016054@ha
		lis r4, zero_aji_00016000@ha
		lfs f1, float_9p5_aji_00016050@l(r6)
		lfs f2, float_7p5_aji_00016054@l(r5)
		opword 0x38610030
		lfs f3, zero_aji_00016000@l(r4)
		bl PSMTXScale
		opword 0x38610030
		opword 0x3880001E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x38600001
		bl GXSetNumTevStages
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
		opword 0x38E00001
		bl GXSetTevAlphaIn
		lis r3, zero_aji_00014dfc@ha
		opword 0x3881000C
		lwz r0, zero_aji_00014dfc@l(r3)
		opword 0x38600001
		opword 0x90010008
		opword 0x9B21000B
		opword 0x80010008
		opword 0x9001000C
		bl GXSetTevColor
		opword 0x387E011C
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
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
		lis r3, gp@ha
		opword 0x3CC0CC01
		lwz r7, gp@l(r3)
		opword 0x38A00000
		opword 0x38800001
		opword 0xA0070170
		opword 0xA0670172
		opword 0x7C0000D0
		opword 0x7C000E70
		opword 0x5463F87E
		opword 0x7C000194
		opword 0xB0068000
		opword 0xB0668000
		opword 0xB0A68000
		opword 0xB0A68000
		opword 0xB0868000
		opword 0xA0070170
		opword 0xA0670172
		opword 0x5400F87E
		opword 0xB0068000
		opword 0x5460F87E
		opword 0xB0068000
		opword 0xB0A68000
		opword 0xB0868000
		opword 0xB0868000
		opword 0xA0670172
		opword 0xA0070170
		opword 0x7C6300D0
		opword 0x5400F87E
		opword 0x7C630E70
		opword 0xB0068000
		opword 0x7C030194
		opword 0xB0068000
		opword 0xB0A68000
		opword 0xB0868000
		opword 0xB0A68000
		opword 0xA0670172
		opword 0xA0070170
		opword 0x7C6300D0
		opword 0x7C0000D0
		opword 0x7C630E70
		opword 0xB0068000
		opword 0x7C030194
		opword 0xB0068000
		opword 0xB0A68000
		opword 0xB0A68000
		opword 0xB0A68000
		opword 0xBAC10068
		opword 0x80010094
		opword 0x7C0803A6
		opword 0x38210090
	}
}
#pragma pop
#endif


EVT_BEGIN(evt_emergency)
    IF_INT_NOT_EQUAL(GSW(0), 376)
        LOOP(0)
            IF_INT_EQUAL(GSW(0), 376)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_msec_init, 11, 255, 96, 1000)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, 255, LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
    END_IF
    CALL(evt_map_set_blend, 0, 255, 96, 96, 255)
    RETURN
EVT_END()

EVT_BEGIN(evt_last)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_party_stop, 0)
    WAIT_MS(800)
    CALL(evt_msg_print_party, STRING(((char*)aji_17_str_00003F88)))
    WAIT_MS(300)
    LOOP(3)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00003F94)), 1)
        WAIT_MS(100)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_00003F94)), 1)
        WAIT_MS(100)
    END_LOOP
    WAIT_MS(300)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00003F94)), 1)
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00003F9C)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)aji_17_str_00003FB4)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, STRING(((char*)aji_17_str_00003FBC)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        WAIT_MS(1600)
        CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00003FC4)), 0, 0, -120, 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FDC)), 1, 0)
    WAIT_MS(1000)
    CALL(evt_map_playanim, STRING(((char*)str_00003FE4)), 1, 0)
    WAIT_MS(1000)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FEC)), 1, 0)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00003FF4)), 0, 0, -100, 0)
        WAIT_MS(800)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_0000400C)), 0, 0)
    CALL(evt_map_checkanim, STRING(((char*)aji_17_str_0000400C)), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_00004014)), 1)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00004020)), 1, 0)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004028)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(500)
    CALL(evt_party_stop, 0)
    CALL(evt_cam3d_evt_set, 0, 100, -170, 0, 40, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_fade_tec_onoff, 1, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, 20, 20, FLOAT(80.0f))
        CALL(evt_mario_set_dir, 90, 200, 0)
    END_INLINE_EVENT
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, -20, 20, FLOAT(80.0f))
        CALL(evt_party_set_dir, 0, 270, 200)
    END_INLINE_EVENT
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004034)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_snd_sfxon, STRING(((char*)aji_17_str_00004040)), LW(10))
    CALL(evt_snd_sfx_vol, LW(10), 0)
    SET_VALUE(LF(0), 0)
    LOOP(2)
        CALL(evt_sub_intpl_msec_init, 11, 0, 128, 300)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(noise, LW(0))
        IF_INT_GREATER(LW(0), 127)
            SET_VALUE(LW(0), 127)
        END_IF
        CALL(evt_snd_sfx_vol, LW(10), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        IF_INT_EQUAL(LF(0), 0)
            SET_VALUE(LF(0), 1)
            CALL(evt_mario_set_pose, STRING(((char*)aji_17_str_00004058)))
        END_IF
    END_LOOP
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004060)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 0, 152, 565, 0, 57, 24, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_pose, STRING(((char*)aji_17_str_0000406C)))
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_dir, 0, 90, 0)
    CALL(evt_mario_set_reardir)
    CALL(evt_fade_tec_onoff, 0, 0)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004074)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 0, 100, -170, 0, 40, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_set_dir, 0, 270, 0)
    CALL(evt_mario_set_reardir)
    CALL(evt_fade_tec_onoff, 1, 0)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004080)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_snd_sfxon, STRING(((char*)aji_17_str_00004040)), LW(10))
    CALL(evt_snd_sfx_vol, LW(10), 0)
    LOOP(2)
        CALL(evt_sub_intpl_msec_init, 11, 0, 255, 300)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(noise, LW(0))
        IF_INT_GREATER(LW(0), 127)
            SET_VALUE(LW(0), 127)
        END_IF
        CALL(evt_snd_sfx_vol, LW(10), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
    END_LOOP
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, 2000)
    LABEL(2)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(noise, LW(0))
    IF_INT_GREATER(LW(0), 127)
        SET_VALUE(LW(0), 127)
    END_IF
    CALL(evt_snd_sfx_vol, LW(10), LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(2)
    END_IF
    CALL(evt_sub_intpl_msec_init, 11, 0, 128, 300)
    LABEL(3)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(noise, LW(0))
    IF_INT_GREATER(LW(0), 127)
        SET_VALUE(LW(0), 127)
    END_IF
    CALL(evt_snd_sfx_vol, LW(10), LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(3)
    END_IF
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, 2000)
    LABEL(4)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(noise, 255)
    CALL(evt_snd_sfx_vol, LW(10), 255)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(4)
    END_IF
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_0000408C)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING(((char*)aji_17_str_00004098)))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)str_000040A4)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 0, 152, 565, 0, 57, 24, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_pose, STRING(((char*)aji_17_str_000040B0)))
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_dir, 0, 90, 0)
    CALL(evt_mario_set_reardir)
    CALL(evt_fade_tec_onoff, 0, 0)
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING(((char*)aji_17_str_000040B8)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 100, -170, 0, 40, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_set_dir, 0, 270, 0)
    CALL(evt_mario_adjust_dir)
    CALL(evt_fade_tec_onoff, 1, 0)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000040C4)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 0, 152, 565, 0, 57, 24, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_dir, 0, 90, 0)
    CALL(evt_mario_set_reardir)
    CALL(evt_fade_tec_onoff, 0, 0)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000040D0)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_bero_mapchange, STRING(((char*)aji_17_str_000040DC)), STRING(((char*)aji_17_str_000040E4)))
    RETURN
EVT_END()

EVT_BEGIN(evt_last2)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_mario_set_pos, 20, 0, 20)
    CALL(evt_party_set_pos, 0, -20, 0, 20)
    CALL(evt_cam3d_evt_set, 0, 100, -170, 0, 40, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_set_dir, 0, 270, 0)
    CALL(evt_mario_set_reardir)
    CALL(evt_fade_softfocus_onoff, 0)
    CALL(evt_fade_tec_onoff, 1, 0)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING(((char*)aji_17_str_000040EC)))
    WAIT_MS(300)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_00004014)), 1)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00004020)), 1, 0)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000040F8)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(300)
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 255, 2000)
        LABEL(10)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(noise, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(10)
        END_IF
    END_INLINE_EVENT
    WAIT_MS(1000)
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00004104)), 0, 0, -100, 0)
    CALL(evt_sub_intpl_msec_init, 2, 0, 239, 200)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    SET_VALUE(LW(2), 480)
    SUBTRACT(LW(2), LW(0))
    SUBTRACT(LW(2), LW(0))
    CALL(viewport, 0, LW(0), 608, LW(2))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(evt_sub_intpl_msec_init, 2, 0, 303, 300)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    SET_VALUE(LW(2), 608)
    SUBTRACT(LW(2), LW(0))
    SUBTRACT(LW(2), LW(0))
    CALL(viewport, LW(0), 240, LW(2), 1)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    CALL(viewport, 0, 0, 1, 1)
    CALL(evt_fade_tec_onoff, 0, 0)
    WAIT_MS(2000)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00004014)), 1)
    CALL(evt_mario_set_pos, 20, 0, 35)
    CALL(evt_party_set_pos, 0, -30, 0, 35)
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_dir, 0, 90, 0)
    CALL(evt_mario_adjust_dir)
    CALL(evt_cam3d_evt_set, 0, 152, 565, 0, 57, 24, 0, 11)
    WAIT_FRAMES(1)
    CALL(viewport, 0, 0, 608, 480)
    WAIT_MS(300)
    SPAWN_EVENT(PTR(evt_emergency))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_0000411C)), 0, 0)
    WAIT_MS(300)
    SET_VALUE(GSW(0), 376)
    CALL(evt_cam3d_evt_set, 0, 92, 320, 0, 40, 24, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING(((char*)aji_17_str_00004128)))
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00004134)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)aji_17_str_0000414C)))
    WAIT_MS(500)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
        IF_FLOAT_NOT_EQUAL(LW(0), LW(3))
            BREAK_LOOP
        END_IF
        IF_FLOAT_NOT_EQUAL(LW(1), LW(4))
            BREAK_LOOP
        END_IF
        IF_FLOAT_NOT_EQUAL(LW(2), LW(5))
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_camera)
    SET_VALUE(LW(5), LW(0))
    SET_VALUE(LW(6), LW(1))
    SET_VALUE(LW(7), LW(2))
    LOOP(0)
        CALL(evt_sub_intpl_msec_init, 11, LW(6), LW(7), 2000)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, LW(5), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        WAIT_MS(1000)
        CALL(evt_sub_intpl_msec_init, 11, LW(7), LW(6), 2000)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, LW(5), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
        WAIT_MS(1000)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(mail_sousin_se)
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00004154)), 0, 0, -100, 0)
    WAIT_MS(600)
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00004154)), 0, 0, -100, 0)
    WAIT_MS(600)
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00004154)), 0, 0, -100, 0)
    WAIT_MS(900)
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_0000416C)), 0, 0, -100, 0)
    RETURN
EVT_END()

static EVT_BEGIN(peach_evt_stg1)
    CALL(evt_mario_set_mode, 1)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING(((char*)aji_17_str_00004184)))
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_set_pos, -230, 0, 0)
    CALL(evt_seq_wait, 2)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_open))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    BEGIN_INLINE_EVENT
        WAIT_MS(800)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_close_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
        LABEL(2)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(w_door_close))
        IF_INT_EQUAL(LW(1), 1)
            GOTO(2)
        END_IF
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, -140, 0, 60)
    WAIT_MS(800)
    CALL(evt_mario_set_dir, 270, 200, 0)
    WAIT_MS(300)
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(300)
    WAIT_MS(500)
    LOOP(3)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00003F94)), 1)
        WAIT_MS(100)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_00003F94)), 1)
        WAIT_MS(100)
    END_LOOP
    WAIT_MS(300)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00003F94)), 1)
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00004194)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)aji_17_str_00003FB4)), 0, 0, 0, 0, 0, 0, 0, 0, 60)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000041B4)))
    BEGIN_INLINE_EVENT
        WAIT_MS(1600)
        CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00003FC4)), 0, 0, -120, 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FDC)), 1, 0)
    WAIT_MS(1000)
    CALL(evt_map_playanim, STRING(((char*)str_00003FE4)), 1, 0)
    WAIT_MS(1000)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FEC)), 1, 0)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00003FF4)), 0, 0, -100, 0)
        WAIT_MS(800)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_0000400C)), 0, 0)
    WAIT_MS(500)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00004020)), 1, 0)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000041C4)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000041B4)), STRING(((char*)aji_17_str_000041DC)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000041E4)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 450, 0, 105, -150, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_sub_intpl_msec_init, 11, 0, 20, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING(((char*)aji_17_str_000041F4)), LW(0), 0, 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 20, 45, 2700)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING(((char*)aji_17_str_000041F4)), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos, -30, -68, 2700)
    END_INLINE_EVENT
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000041FC)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_mario_wait_move_end)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_0000420C)), STRING(((char*)aji_17_str_00004214)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_0000421C)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_0000422C)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000041B4)))
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000041B4)), STRING(((char*)aji_17_str_000041DC)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_0000423C)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_0000424C)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_0000425C)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_0000426C)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_0000427C)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING((char*)zero_aji_00015114), 0, 0, 0, 0, 0, 0, 0, 0, 60)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000042A0)))
    WAIT_MS(1200)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042A0)), STRING(((char*)aji_17_str_000042A8)))
    CALL(evt_msg_print, 0, STRING(((char*)str_000042B0)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000042C0)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000042D0)))
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042D0)), STRING(((char*)aji_17_str_000042D8)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000042E0)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000042F0)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000041B4)))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000041B4)), STRING(((char*)aji_17_str_000041DC)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004300)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004310)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, 230, 45, 372, 22, 85, -25, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_00004320)), STRING(((char*)aji_17_str_00004328)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004330)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00004340)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000042D0)))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042D0)), STRING(((char*)aji_17_str_000042D8)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004350)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004360)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042A0)), STRING(((char*)aji_17_str_000042A8)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004370)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004320)))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004380)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_00004390)), STRING(((char*)aji_17_str_00004398)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000043A0)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000043B0)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000042D0)))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042D0)), STRING(((char*)aji_17_str_000042D8)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000043C0)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000043D0)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, 0, 92, 171, 0, 59, -13, 500, 11)
    WAIT_MS(500)
    CALL(evt_mario_mov_pos, 0, -95, 700)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000043E0)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000043F0)), 0, 25, -120, LW(15))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004404)))
    WAIT_MS(3000)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_0000420C)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_0000440C)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    SPAWN_EVENT(PTR(mail_sousin_se))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_0000441C)), 1)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00004424)), 0, 0)
    CALL(evt_map_checkanim, STRING(((char*)aji_17_str_00004424)), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_0000441C)), 1)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004428)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_mario_set_dir, 270, 200, 0)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, -140, 92, 226, -140, 59, 55, 2000, 11)
    CALL(evt_mario_mov_pos, -140, 0, 2000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LABEL(3)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_open))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(3)
    END_IF
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004438)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(600)
    CALL(evt_mario_mov_pos, -230, 0, 1200)
    WAIT_MS(500)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LABEL(4)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_close))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(4)
    END_IF
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00004448)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(1000)
    CALL(evt_sub_intpl_msec_init, 11, 255, 96, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_MS(2000)
    SET_VALUE(GSW(0), 59)
    CALL(evt_snd_bgmoff_f, 512, 1000)
    CALL(evt_snd_envoff_f, 512, 1000)
    CALL(evt_fade_entry, 15, 300, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00004458)), 1)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    SET_VALUE(LF(10), 0)
    SET_VALUE(LW(0), 2)
    CALL_CHILD(PTR(evt_memcard_save))
    CALL(evt_mario_set_mode, 2)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_snd_envoff_f, 512, 2000)
    CALL(evt_snd_sfx_all_stop)
    CALL(evt_fade_set_mapchange_type, 1, 57, 0, 56, 0)
    CALL(evt_bero_mapchange, STRING(((char*)aji_17_str_00004464)), STRING((char*)zero_aji_00015114))
    RETURN
EVT_END()

#ifdef NONMATCHING
static const GXColor horogram_amb = {0xFF, 0xFF, 0xFF, 0xFF};
#endif
#ifdef NONMATCHING
static const Vec horogram_pos = {0.0f, 0.0f, 20.0f};
#endif
#ifdef NONMATCHING
static const Vec horogram_up = {0.0f, 1.0f, 0.0f};
#endif
#ifdef NONMATCHING
static const Vec horogram_target = {0.0f, 0.0f, 0.0f};
#endif

f32 move_pos_list[15][2] = {
    {0.0f, -80.0f},
    {39.37592f, -74.69887f},
    {75.489975f, -58.18756f},
    {102.47971f, -29.07189f},
    {109.125275f, 10.068815f},
    {90.71562f, 45.247093f},
    {58.11264f, 67.92478f},
    {19.846874f, 78.68708f},
    {-19.921722f, 78.67708f},
    {-58.15683f, 67.90478f},
    {-90.7439f, 45.2171f},
    {-109.13224f, 10.028812f},
    {-102.458244f, -29.111893f},
    {-75.446236f, -58.217556f},
    {-39.30409f, -74.71887f},
};

EVT_BEGIN(peach_dance_move)
    CALL(get_center, LW(2), LW(3))
    CALL(compute_move_pos, LW(4), LW(5))
    BEGIN_INLINE_EVENT
        CALL(move_center, LW(2), LW(3), LW(4), LW(5), 600)
    END_INLINE_EVENT
    SET_VALUE(LW(6), LW(5))
    ADD(LW(5), 323)
    ADD(LW(6), 27)
    CALL(evt_cam3d_evt_set, LW(4), 95, LW(5), LW(4), 45, LW(6), 600, 11)
    WAIT_FRAMES(1)
    SPAWN_EVENT(PTR(peach_dance_pose))
    LOOP(0)
        CALL(dance_flag_check, 4, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        CALL(get_center, LW(0), LW(1))
        CALL(evt_mario_get_pos, 0, LW(2), LW(4), LW(3))
        CALL(compute_peach_pos, LW(0), LW(1), LW(2), LW(3))
        CALL(evt_mario_set_pos, LW(2), LW(4), LW(3))
        CALL(compute_horogram_pos, LW(0), LW(1), LW(2), LW(3))
        CALL(set_npc_pos, STRING(((char*)aji_17_str_00004494)), LW(2), FLOAT((0.0f)), LW(3))
        CALL(set_npc_pos, STRING(((char*)aji_17_str_000044A0)), LW(0), FLOAT(5.0f), LW(1))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(peach_dance_pose)
    CALL(dance_flag_check, 8, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    CALL(dance_get_step, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(peach_set_pose, STRING(((char*)aji_17_str_000044A8)))
        CALL(horogram_set_pose, STRING(((char*)aji_17_str_000044B0)))
        CASE_EQUAL(1)
        CALL(peach_set_pose, STRING(((char*)aji_17_str_000044B8)))
        CALL(horogram_set_pose, STRING(((char*)aji_17_str_000044C0)))
        CASE_EQUAL(2)
        CALL(peach_set_pose, STRING(((char*)aji_17_str_000044C8)))
        CALL(horogram_set_pose, STRING(((char*)aji_17_str_000044D0)))
        CASE_DEFAULT
        DEBUG_PUT_MSG(STRING(((char*)str_000044D8)))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(peach_dance_action_step)
    RETURN
EVT_END()

EVT_BEGIN(dance_action_turn_sub)
    CALL(evt_mario_get_dispdir, LW(6))
    IF_INT_EQUAL(LW(6), 0)
        SET_VALUE(LW(6), 360)
    END_IF
    SET_VALUE(LW(7), LW(6))
    SUBTRACT(LW(7), 180)
    CALL(get_local_rotate, LW(8))
    SET_FLOAT_VALUE(LW(9), LW(8))
    ADD_FLOAT(LW(9), FLOAT(3.140625f))
    MULTIPLY_FLOAT(LW(8), FLOAT((1000.0f)))
    MULTIPLY_FLOAT(LW(9), FLOAT((1000.0f)))
    CALL(evt_npc_get_position, STRING(((char*)aji_17_str_00004494)), LW(2), LW(0), LW(3))
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_000044EC)), LW(2), 0, LW(3), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, LW(6), LW(7), 400)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        SET_VALUE(LW(2), 360)
        SUBTRACT(LW(2), LW(0))
        CALL(evt_npc_set_ry, STRING(((char*)aji_17_str_00004494)), LW(2))
        CALL(evt_mario_set_dir, LW(0), 0, 0)
        CALL(evt_mario_set_dispdir, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
    END_INLINE_EVENT
    CALL(evt_sub_intpl_msec_init, 11, LW(8), LW(9), 400)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT((1000.0f)))
    CALL(set_local_rotate, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(peach_dance_action_turn)
    CALL(dance_flag_onoff, 2, 1)
    CALL_CHILD(PTR(dance_action_turn_sub))
    CALL(dance_flag_onoff, 2, 0)
    RETURN
EVT_END()

EVT_BEGIN(peach_dance_action_reverse)
    CALL(dance_flag_onoff, 2, 1)
    CALL_CHILD(PTR(dance_action_turn_sub))
    CALL(dance_reverse)
    CALL(dance_flag_check, 1, LW(0))
    CALL(dance_flag_onoff, 2, 0)
    RETURN
EVT_END()

EVT_BEGIN(peach_dance_action_fail)
    CALL(dance_flag_onoff, 2, 1)
    CALL(dance_flag_onoff, 8, 1)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004504)))
    CALL(horogram_set_pose, STRING(((char*)aji_17_str_000044B0)))
    WAIT_MS(400)
    CALL(peach_dance_after_fail)
    CALL(dance_flag_onoff, 8, 0)
    CALL(dance_flag_onoff, 2, 0)
    RETURN
EVT_END()

EVT_BEGIN(dance_btn_disp_sub)
    SWITCH(LW(1))
        CASE_EQUAL(0)
        SET_VALUE(LW(4), STRING(((char*)aji_17_str_0000450C)))
        CASE_EQUAL(1)
        SET_VALUE(LW(4), STRING(((char*)aji_17_str_00004514)))
        CASE_EQUAL(2)
        SET_VALUE(LW(4), STRING(((char*)aji_17_str_0000451C)))
    END_SWITCH
    SWITCH(LW(2))
        CASE_EQUAL(1)
        SET_VALUE(LW(3), 0)
        CASE_EQUAL(2)
        SET_VALUE(LW(3), 45)
        CASE_EQUAL(0)
        SET_VALUE(LW(3), -45)
    END_SWITCH
    CALL(evt_fuki_btn, LW(2), LW(4), STRING(((char*)aji_17_str_000044A0)), 0, 0, 0, 0, LW(3), -1)
    RETURN
EVT_END()

EVT_BEGIN(dance_btn_disp)
    SWITCH(LW(1))
        CASE_EQUAL(0)
        CALL(dance_flag_onoff, 4096, 1)
        CASE_EQUAL(1)
        CALL(dance_flag_onoff, 8192, 1)
        CASE_EQUAL(2)
        CALL(dance_flag_onoff, 16384, 1)
    END_SWITCH
    CALL_CHILD(PTR(dance_btn_disp_sub))
    RETURN
EVT_END()

EVT_BEGIN(dance_btn_batu)
    SWITCH(LW(1))
        CASE_EQUAL(0)
        CALL(evt_fuki_btn_set_batu, STRING(((char*)aji_17_str_0000450C)))
        CASE_EQUAL(1)
        CALL(evt_fuki_btn_set_batu, STRING(((char*)aji_17_str_00004514)))
        CASE_EQUAL(2)
        CALL(evt_fuki_btn_set_batu, STRING(((char*)aji_17_str_0000451C)))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(dance_btn_clear)
    SWITCH(LW(1))
        CASE_EQUAL(0)
        CALL(dance_flag_check, 4096, LW(3))
        IF_INT_EQUAL(LW(3), 1)
            CALL(evt_eff_softdelete, STRING(((char*)aji_17_str_0000450C)))
            CALL(dance_flag_onoff, 4096, 0)
        END_IF
        CASE_EQUAL(1)
        CALL(dance_flag_check, 8192, LW(3))
        IF_INT_EQUAL(LW(3), 1)
            CALL(evt_eff_softdelete, STRING(((char*)aji_17_str_00004514)))
            CALL(dance_flag_onoff, 8192, 0)
        END_IF
        CASE_EQUAL(2)
        CALL(dance_flag_check, 16384, LW(3))
        IF_INT_EQUAL(LW(3), 1)
            CALL(evt_eff_softdelete, STRING(((char*)aji_17_str_0000451C)))
            CALL(dance_flag_onoff, 16384, 0)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(dance_btn_clear_all)
    CALL(dance_flag_check, 4096, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_eff_softdelete, STRING(((char*)aji_17_str_0000450C)))
        CALL(dance_flag_onoff, 4096, 0)
    END_IF
    CALL(dance_flag_check, 8192, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_eff_softdelete, STRING(((char*)aji_17_str_00004514)))
        CALL(dance_flag_onoff, 8192, 0)
    END_IF
    CALL(dance_flag_check, 16384, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_eff_softdelete, STRING(((char*)aji_17_str_0000451C)))
        CALL(dance_flag_onoff, 16384, 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(wait_action_time)
    LOOP(0)
        CALL(evt_sub_get_stopwatch, LW(12), LW(4))
        IF_INT_GREATER_OR_EQUAL(LW(4), 660)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(peach_dance_dark)
    CALL(evt_sub_intpl_msec_init, 11, 255, 192, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(peach_dance_light)
    CALL(evt_sub_intpl_msec_init, 11, 192, 255, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(peach_evt_dance)
    CALL(evt_npc_pera_onoff, STRING(((char*)aji_17_str_00004494)), 0)
    CALL(evt_npc_set_ry, STRING(((char*)aji_17_str_00004494)), 180)
    CALL(evt_npc_pera_onoff, STRING(((char*)aji_17_str_00004524)), 0)
    CALL(evt_npc_set_ry, STRING(((char*)aji_17_str_00004524)), 180)
    LABEL(100)
    SET_VALUE(LW(15), 0)
    SET_VALUE(LW(14), 0)
    SET_VALUE(LW(13), 0)
    SET_VALUE(LW(12), 0)
    SET_VALUE(LW(11), 0)
    CALL(dance_data_init)
    CALL(get_center, LW(2), LW(3))
    CALL(evt_npc_set_position, STRING(((char*)aji_17_str_000044A0)), LW(2), FLOAT(5.0f), LW(3))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004530)))
    CALL(evt_npc_set_anim, STRING(((char*)aji_17_str_00004494)), STRING(((char*)aji_17_str_00004530)))
    CALL(evt_npc_set_anim, STRING(((char*)aji_17_str_00004524)), STRING(((char*)aji_17_str_00004538)))
    WAIT_MS(350)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004544)))
    CALL(horogram_set_pose, STRING(((char*)aji_17_str_0000454C)))
    WAIT_MS(1000)
    CALL(evt_snd_bgmoff, 1024)
    CALL(evt_snd_bgmon, 1, STRING(((char*)aji_17_str_00004554)))
    CALL(bgm_start_wait)
    WAIT_MS(4000)
    SPAWN_EVENT_GET_ID(PTR(evt_sub_stopwatch), LW(13))
    SPAWN_EVENT(PTR(peach_dance_move))
    LOOP(0)
        CALL(evt_sub_get_stopwatch, LW(13), LW(4))
        IF_INT_GREATER_OR_EQUAL(LW(4), 660)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(LW(11), 2000)
    LOOP(0)
        CALL(evt_sub_get_stopwatch, LW(13), LW(4))
        IF_INT_GREATER_OR_EQUAL(LW(4), 32000)
            BREAK_LOOP
        END_IF
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT_GET_ID(PTR(evt_sub_stopwatch), LW(12))
        SPAWN_EVENT(PTR(peach_dance_move))
        LOOP(0)
            CALL(evt_sub_get_stopwatch, LW(12), LW(4))
            IF_INT_GREATER_OR_EQUAL(LW(4), 660)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_random, 2, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(0)
            SET_RAW_VALUE(LW(2), 1)
            CASE_EQUAL(1)
            SET_RAW_VALUE(LW(2), 0)
            CASE_EQUAL(2)
            SET_RAW_VALUE(LW(2), 2)
        END_SWITCH
        CALL_CHILD(PTR(dance_btn_disp))
        SPAWN_EVENT(PTR(peach_dance_move))
        SPAWN_EVENT_GET_ID(PTR(evt_sub_stopwatch), LW(14))
        LOOP(0)
            CALL(evt_sub_get_stopwatch, LW(14), LW(4))
            IF_INT_GREATER_OR_EQUAL(LW(4), 660)
                SET_VALUE(LW(3), 2)
                BREAK_LOOP
            END_IF
            CALL(btn_check, LW(2), LW(3))
            IF_INT_NOT_EQUAL(LW(3), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        DELETE_EVENT(LW(14))
        LOOP(0)
            CALL(evt_sub_get_stopwatch, LW(12), LW(4))
            IF_INT_GREATER_OR_EQUAL(LW(4), 1320)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(0)
            CALL(evt_sub_get_stopwatch, LW(13), LW(4))
            IF_INT_GREATER_OR_EQUAL(LW(4), LW(11))
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        ADD(LW(11), 2000)
        SPAWN_EVENT(PTR(peach_dance_move))
        IF_INT_NOT_EQUAL(LW(3), 0)
            SWITCH(LW(3))
                CASE_EQUAL(1)
                ADD(LW(15), 1)
                CALL_CHILD(PTR(dance_btn_clear))
                SWITCH(LW(2))
                    CASE_EQUAL(1)
                    SPAWN_EVENT(PTR(peach_dance_action_step))
                    CASE_EQUAL(2)
                    SPAWN_EVENT(PTR(peach_dance_action_turn))
                    CASE_EQUAL(0)
                    SPAWN_EVENT(PTR(peach_dance_action_reverse))
                END_SWITCH
                CASE_EQUAL(2)
                CALL(evt_npc_get_position, STRING(((char*)aji_17_str_00004494)), LW(5), LW(6), LW(7))
                CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_0000456C)), LW(5), 0, LW(7), 0)
                CALL_CHILD(PTR(dance_btn_batu))
                SPAWN_EVENT(PTR(peach_dance_action_fail))
            END_SWITCH
        END_IF
        CALL_CHILD(PTR(dance_btn_clear_all))
        LOOP(0)
            CALL(evt_sub_get_stopwatch, LW(12), LW(4))
            IF_INT_GREATER_OR_EQUAL(LW(4), 1980)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        DELETE_EVENT(LW(12))
    END_LOOP
    DELETE_EVENT(LW(13))
    CALL(evt_snd_bgmoff, 513)
    CALL(evt_snd_bgmon, 288, 0)
    CALL(evt_snd_envon_f, 272, STRING(((char*)aji_17_str_00004184)), 2000)
    WAIT_MS(400)
    CALL(horogram_flag_onoff, 1, 4)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000042D0)))
    CALL(horogram_set_pose, STRING(((char*)aji_17_str_000042D0)))
    WAIT_MS(300)
    SET_VALUE(LW(10), LW(15))
    CALL(evt_npc_get_position, STRING(((char*)aji_17_str_00004494)), LW(2), LW(0), LW(3))
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00004580)), LW(2), 0, LW(3), 0)
    CALL(evt_sub_intpl_msec_init, 11, 192, 0, 500)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_npc_set_color, STRING(((char*)aji_17_str_00004494)), 255, 255, 255, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)aji_17_str_00004494)), 128)
    CALL_CHILD(PTR(peach_dance_light))
    SET_VALUE(LW(15), LW(10))
    CALL(evt_cam3d_evt_set, 0, 105, 243, 0, 55, -53, 1500, 11)
    CALL(dance_data_init)
    CALL(compute_peach_pos, 0, -80, LW(0), LW(1))
    CALL(evt_mario_mov_pos, LW(0), LW(1), 1500)
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(500)
    IF_INT_LESS(LW(15), 10)
        CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
        CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004598)), 0, 0)
        CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_npc_set_position, STRING(((char*)aji_17_str_000044A0)), LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000045A8)), 0, STRING(((char*)aji_17_str_000044A0)))
        CALL(horogram_flag_onoff, 0, 4)
        CALL(evt_npc_set_ry, STRING(((char*)aji_17_str_00004494)), 180)
        CALL_CHILD(PTR(peach_dance_dark))
        CALL(compute_horogram_pos, 0, -80, LW(2), LW(3))
        CALL(evt_npc_set_position, STRING(((char*)aji_17_str_00004494)), LW(2), 0, LW(3))
        CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00004580)), LW(2), 0, LW(3), 0)
        CALL(evt_sub_intpl_msec_init, 11, 0, 192, 500)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_npc_set_color, STRING(((char*)aji_17_str_00004494)), 255, 255, 255, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
        CALL(evt_cam3d_evt_set, 0, 95, 243, 0, 45, -53, 700, 11)
        WAIT_MS(700)
        GOTO(100)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(peach_evt_stg2)
    CALL(evt_mario_set_mode, 1)
    CALL(evt_npc_entry, STRING(((char*)aji_17_str_000044A0)), STRING(((char*)aji_17_str_000045B8)))
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)aji_17_str_000044A0)), 128)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)aji_17_str_000044A0)), 32)
    CALL(evt_npc_set_width, STRING(((char*)aji_17_str_000044A0)), FLOAT(20.0f))
    CALL(evt_npc_set_height, STRING(((char*)aji_17_str_000044A0)), FLOAT(47.0f))
    CALL(evt_npc_entry, STRING(((char*)aji_17_str_00004494)), STRING(((char*)aji_17_str_000045B8)))
    CALL(evt_npc_set_tribe, STRING(((char*)aji_17_str_00004494)), STRING(((char*)aji_17_str_000045C0)))
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)aji_17_str_00004494)), 128)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)aji_17_str_00004494)), 32)
    CALL(evt_npc_set_color, STRING(((char*)aji_17_str_00004494)), 255, 255, 255, 255)
    CALL(evt_npc_set_width, STRING(((char*)aji_17_str_00004494)), FLOAT(20.0f))
    CALL(evt_npc_set_height, STRING(((char*)aji_17_str_00004494)), FLOAT(47.0f))
    CALL(evt_npc_entry, STRING(((char*)aji_17_str_00004524)), STRING(((char*)aji_17_str_000045CC)))
    CALL(evt_npc_set_tribe, STRING(((char*)aji_17_str_00004524)), STRING(((char*)aji_17_str_000045C0)))
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)aji_17_str_00004524)), 128)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)aji_17_str_00004524)), 32)
    CALL(evt_npc_set_color, STRING(((char*)aji_17_str_00004524)), 255, 255, 255, 255)
    CALL(evt_npc_set_width, STRING(((char*)aji_17_str_00004524)), FLOAT(20.0f))
    CALL(evt_npc_set_height, STRING(((char*)aji_17_str_00004524)), FLOAT(47.0f))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00003F94)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FDC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_00003FE4)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FEC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_0000400C)), 2, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00004020)), 1, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING(((char*)aji_17_str_00004184)))
    CALL(horogram_init)
    WAIT_FRAMES(1)
    CALL(evt_npc_set_color, STRING(((char*)aji_17_str_00004494)), 255, 255, 255, 0)
    CALL(evt_npc_set_color, STRING(((char*)aji_17_str_00004524)), 255, 255, 255, 0)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(horogram_cap_evt)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(disp_horogram_evt)
    END_INLINE_EVENT
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000045D8)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000045E8)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000045F8)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004608)), 0, STRING(((char*)aji_17_str_000041D4)))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 45, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING(((char*)aji_17_str_000041F4)), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 1500, 11)
    CALL(evt_mario_mov_pos, -30, -68, 1500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004618)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00004194)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_jump_pos, LW(0), LW(1), LW(2), 300, 1, 20)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004628)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004638)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_mario_adjust_dir)
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004648)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004658)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004390)))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_00004390)), STRING(((char*)aji_17_str_00004398)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004668)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004678)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(300)
    CALL(evt_snd_envoff_f, 512, 1000)
    CALL_CHILD(PTR(peach_dance_dark))
    LABEL(100)
    CALL(evt_npc_set_position, STRING(((char*)aji_17_str_00004494)), 30, 0, -68)
    CALL(evt_sub_intpl_msec_init, 11, 0, 192, 500)
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00004580)), 30, 0, -67, 0)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_npc_set_color, STRING(((char*)aji_17_str_00004494)), 255, 255, 255, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000042A0)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042A0)), STRING(((char*)aji_17_str_000042A8)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004688)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000042D0)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042D0)), STRING(((char*)aji_17_str_000042D8)))
    CALL(evt_cam3d_evt_set, 0, 95, 243, 0, 45, -53, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004698)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(dance_data_init)
    CALL(compute_peach_pos, 0, -80, LW(0), LW(1))
    CALL(compute_horogram_pos, 0, -80, LW(2), LW(3))
    DEBUG_PUT_MSG(STRING(((char*)aji_17_str_000046A8)))
    DEBUG_PUT_REG(LW(0))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)aji_17_str_00004494)), LW(2), LW(3), 0, FLOAT(48.0f), 0)
        CALL(evt_npc_set_ry, STRING(((char*)aji_17_str_00004494)), 180)
        CALL(evt_npc_set_anim, STRING(((char*)aji_17_str_00004494)), STRING(((char*)aji_17_str_000042D0)))
        CALL(evt_npc_set_anim, STRING(((char*)aji_17_str_00004524)), STRING(((char*)aji_17_str_0000420C)))
        CALL(horogram_flag_onoff, 1, 1)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, LW(0), LW(1), FLOAT(48.0f))
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000046B4)), 0, 0)
    CALL_CHILD(PTR(peach_evt_dance))
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)str_000046C4)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000046D4)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000046E4)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 0, 92, 171, 0, 59, -13, 1000, 11)
    CALL(evt_mario_mov_pos, 0, -95, 700)
    WAIT_MS(150)
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000043F0)), 0, 25, 120, LW(15))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004404)))
    WAIT_MS(3000)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_0000420C)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000046F4)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    SPAWN_EVENT(PTR(mail_sousin_se))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_0000441C)), 1)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00004424)), 0, 0)
    CALL(evt_map_checkanim, STRING(((char*)aji_17_str_00004424)), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_0000441C)), 1)
    CALL(evt_mario_set_dir, 270, 200, 0)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004704)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, -140, 88, 226, -140, 55, 55, 2000, 11)
    CALL(evt_mario_mov_pos, -140, 0, 2000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_open))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    CALL(evt_peach_set_condition, 6)
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_00004714)), STRING(((char*)aji_17_str_0000471C)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004724)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004734)), 0, 0)
    CALL(evt_mario_mov_pos, -230, 0, 1000)
    WAIT_MS(500)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LABEL(2)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_close))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(2)
    END_IF
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004748)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(1000)
    CALL(evt_sub_intpl_msec_init, 11, 255, 96, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_MS(2000)
    CALL(evt_peach_set_condition, 0)
    SET_VALUE(GSW(0), 114)
    CALL(evt_snd_bgmoff_f, 512, 1000)
    CALL(evt_snd_envoff_f, 512, 1000)
    CALL(evt_fade_entry, 15, 300, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00004458)), 1)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    SET_VALUE(LF(10), 0)
    SET_VALUE(LW(0), 5)
    CALL_CHILD(PTR(evt_memcard_save))
    CALL(evt_mario_set_mode, 2)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_snd_envoff_f, 512, 2000)
    CALL(evt_snd_sfx_all_stop)
    CALL(evt_fade_set_mapchange_type, 1, 57, 0, 56, 0)
    CALL(evt_bero_mapchange, STRING(((char*)aji_17_str_00004758)), STRING((char*)zero_aji_00015114))
    RETURN
EVT_END()

static EVT_BEGIN(peach_evt_stg3)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING(((char*)aji_17_str_00004184)))
    CALL(evt_mario_set_mode, 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00003F94)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FDC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_00003FE4)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FEC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_0000400C)), 2, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00004020)), 1, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004760)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004770)), 0, STRING(((char*)aji_17_str_000041D4)))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 45, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING(((char*)aji_17_str_000041F4)), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 1500, 11)
    CALL(evt_mario_mov_pos, -30, -68, 1500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004780)), 0, 0)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004790)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000047A0)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(500)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000047B0)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000047C4)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_mario_set_dir, 90, 0, 0)
    WAIT_FRAMES(1)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000041B4)))
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000041B4)), STRING(((char*)aji_17_str_000041DC)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000047D8)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000047E8)), 0, 0)
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 1000, 11)
    WAIT_MS(1300)
    CALL(evt_mario_set_dir, 270, 200, 0)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000047F8)))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000047F8)), STRING(((char*)aji_17_str_00004800)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004808)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004818)))
    WAIT_MS(400)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004820)))
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004828)), 0, 0)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000042D0)))
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042D0)), STRING(((char*)aji_17_str_000042D8)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004838)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004848)), 0, 0)
    CALL(evt_fade_set_mapchange_type, 0, 10, 600, 9, 300)
    CALL(evt_bero_mapchange, STRING(((char*)aji_17_str_00003F70)), STRING(((char*)aji_17_str_00003F78)))
    RETURN
EVT_END()

static EVT_BEGIN(peach_evt_stg3_1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING(((char*)aji_17_str_00004184)))
    CALL(evt_mario_set_mode, 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00003F94)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FDC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_00003FE4)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FEC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_0000400C)), 2, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00004020)), 1, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_mario_set_pos, -215, 0, 0)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_open))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, -140, 0, 80)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_close_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
        LABEL(2)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(w_door_close))
        IF_INT_EQUAL(LW(1), 1)
            GOTO(2)
        END_IF
    END_INLINE_EVENT
    WAIT_MS(100)
    CALL(evt_mario_wait_move_end)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004858)), 0, STRING(((char*)aji_17_str_000041D4)))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 45, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING(((char*)aji_17_str_000041F4)), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 1500, 11)
    CALL(evt_mario_mov_pos, -30, -68, 1500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004868)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 800, 11)
    WAIT_MS(800)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004878)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000041B4)))
    CALL(evt_cam3d_evt_set, -30, 67, -220, -30, 37, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_fade_tec_onoff, 1, 0)
    CALL(evt_mario_dispflag_onoff, 1, 512)
    CALL(evt_mario_set_dispdir, 0)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_0000488C)), 0, 0)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042D0)), STRING(((char*)aji_17_str_000042D8)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000048A0)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000048B4)), 0, 0)
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_fade_tec_onoff, 0, 0)
    CALL(evt_mario_set_dispdir, 180)
    WAIT_MS(300)
    CALL(evt_mario_dispflag_onoff, 0, 512)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000048C8)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000048D8)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 800, 11)
    WAIT_MS(800)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000048E8)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000048F8)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_mov_pos, 0, -95, 700)
    WAIT_MS(150)
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000043F0)), 0, 25, 120, LW(15))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004404)))
    WAIT_MS(3000)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_0000420C)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004908)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    SPAWN_EVENT(PTR(mail_sousin_se))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_0000441C)), 1)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00004424)), 0, 0)
    CALL(evt_map_checkanim, STRING(((char*)aji_17_str_00004424)), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_0000441C)), 1)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004918)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004928)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, -140, 92, 226, -140, 59, 55, 2000, 11)
    CALL(evt_mario_mov_pos, -140, 0, 2000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LABEL(3)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_open))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(3)
    END_IF
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(2500)
    CALL(evt_mario_mov_pos, -230, 0, 1000)
    WAIT_MS(500)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LABEL(4)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_close))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(4)
    END_IF
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004938)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(1000)
    CALL(evt_sub_intpl_msec_init, 11, 255, 96, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_MS(2000)
    SET_VALUE(GSW(0), 169)
    CALL(evt_snd_bgmoff_f, 512, 1000)
    CALL(evt_snd_envoff_f, 512, 1000)
    CALL(evt_fade_entry, 15, 300, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00004458)), 1)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    SET_VALUE(LF(10), 0)
    SET_VALUE(LW(0), 8)
    CALL_CHILD(PTR(evt_memcard_save))
    CALL(evt_mario_set_mode, 2)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_snd_envoff_f, 512, 2000)
    CALL(evt_snd_sfx_all_stop)
    CALL(evt_fade_set_mapchange_type, 1, 57, 0, 56, 0)
    CALL(evt_bero_mapchange, STRING(((char*)aji_17_str_00004948)), STRING((char*)zero_aji_00015114))
    RETURN
EVT_END()

s32 peach_evt_stg4_quiz_data[5][4] = {
    (s32)((char*)aji_17_str_00004950), (s32)((char*)aji_17_str_00004960), (s32)((char*)aji_17_str_00004970), 1, (s32)((char*)aji_17_str_00004984), (s32)((char*)aji_17_str_00004994), (s32)((char*)aji_17_str_000049A4), 0,
    (s32)((char*)aji_17_str_000049B8), (s32)((char*)aji_17_str_000049C8), (s32)((char*)aji_17_str_000049D8), 2, (s32)((char*)aji_17_str_000049EC), (s32)((char*)aji_17_str_000049FC), (s32)((char*)aji_17_str_00004A0C), 1,
    (s32)((char*)aji_17_str_00004A20), (s32)((char*)aji_17_str_00004A30), (s32)((char*)aji_17_str_00004A40), 2,
};

static EVT_BEGIN(peach_evt_stg4)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING(((char*)aji_17_str_00004184)))
    CALL(evt_mario_set_mode, 1)
    CALL(evt_mario_kill_party, 0)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00003F94)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FDC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_00003FE4)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FEC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_0000400C)), 2, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00004020)), 1, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, 115, 133, 430, 115, 55, -13, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_mario_set_pos, -215, 0, 0)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_cam3d_evt_set, -105, 133, 430, -105, 55, -13, 3000, 0)
    WAIT_MS(3000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(w_door_open))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, -140, 0, 80)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_close_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(PTR(w_door_close))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(100)
    CALL(evt_mario_wait_move_end)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004A54)), 0, STRING(((char*)aji_17_str_000041D4)))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 45, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING(((char*)aji_17_str_000041F4)), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 1500, 11)
    CALL(evt_mario_mov_pos, -30, -68, 1500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004A68)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(2000)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004A7C)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004A90)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(3000)
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 700, 11)
    WAIT_MS(700)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004AA4)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004AB8)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(500)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004ACC)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_mario_set_dir, 90, 0, 0)
    WAIT_FRAMES(1)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000041B4)))
    CALL(evt_cam3d_evt_set, -30, 67, -220, -30, 37, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_fade_tec_onoff, 1, 0)
    CALL(evt_mario_dispflag_onoff, 1, 512)
    CALL(evt_mario_set_dispdir, 0)
    WAIT_MS(800)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004AE0)), 0, 0)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000042D0)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004AF4)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004B04)), 0, 0)
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_fade_tec_onoff, 0, 0)
    CALL(evt_mario_set_dispdir, 180)
    WAIT_MS(300)
    CALL(evt_mario_dispflag_onoff, 0, 512)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004B14)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    SET_VALUE(LW(15), 0)
    SET_VALUE(LF(15), 0)
    LOOP(0)
        CALL(peach_evt_stg4_read_quiz_data, LW(15), LW(2), LW(3), LW(4), LW(5))
        CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
        CALL(evt_msg_print, 0, LW(2), 0, 0)
        CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
        CALL(peach_set_pose, STRING(((char*)aji_17_str_00004390)))
        CALL(evt_cam3d_evt_set, 0, 108, 233, 0, 65, -13, 0, 11)
        WAIT_FRAMES(1)
        WAIT_MS(500)
        CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
        SET_VALUE(LF(0), 0)
        IF_INT_EQUAL(LW(15), 2)
            IF_INT_EQUAL(LF(15), 1)
                SET_VALUE(LF(0), 1)
            END_IF
        END_IF
        IF_INT_EQUAL(LF(0), 0)
            CALL(evt_msg_print, 0, LW(3), 0, 0)
            ELSE
            CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004B24)), 0, 0)
        END_IF
        CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
        IF_INT_EQUAL(LW(15), 2)
            IF_INT_EQUAL(LF(15), 0)
                CALL(evt_mario_get_pos, 0, LW(12), LW(13), LW(14))
                CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00004194)), LW(12), LW(13), LW(14), 0)
                CALL(peach_set_pose, STRING(((char*)aji_17_str_000042A0)))
                WAIT_MS(500)
                CALL(evt_cam3d_evt_set, 230, 45, 327, 22, 85, -25, 0, 11)
                WAIT_FRAMES(1)
                CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042A0)), STRING(((char*)aji_17_str_000042A8)))
                CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004B38)), 0, STRING(((char*)aji_17_str_000041D4)))
                WAIT_MS(500)
                CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
                CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004B48)), 0, 0)
                CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
                CALL(peach_set_pose, STRING(((char*)aji_17_str_00004390)))
                WAIT_FRAMES(1)
                CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042D0)), STRING(((char*)aji_17_str_000042D8)))
                SET_VALUE(LF(15), 1)
            END_IF
        END_IF
        CALL(evt_msg_select, 0, LW(4))
        CALL(evt_msg_continue)
        IF_INT_EQUAL(LW(5), LW(0))
            CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(15), 4)
                CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
                CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004B58)), 0, 0)
                CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
                BREAK_LOOP
            END_IF
            ADD(LW(15), 1)
            ELSE
            CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
            CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004B68)), 0, 0)
            CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
            SET_VALUE(LW(15), 0)
            CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
            WAIT_FRAMES(1)
        END_IF
        WAIT_MS(500)
    END_LOOP
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004B78)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004B8C)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 0, 92, 171, 0, 59, -13, 700, 11)
    CALL(evt_mario_mov_pos, 0, -95, 700)
    WAIT_MS(150)
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000043F0)), 0, 25, 120, LW(15))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004404)))
    WAIT_MS(3000)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_0000420C)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004BA0)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    SPAWN_EVENT(PTR(mail_sousin_se))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_0000441C)), 1)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00004424)), 0, 0)
    CALL(evt_map_checkanim, STRING(((char*)aji_17_str_00004424)), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_0000441C)), 1)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004BB0)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, -140, 92, 226, -140, 59, 55, 2000, 11)
    CALL(evt_mario_mov_pos, -140, 0, 2000)
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_open_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(w_door_open))
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
    END_INLINE_EVENT
    WAIT_MS(1000)
    CALL(evt_peach_set_condition, 6)
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_00004714)), STRING(((char*)aji_17_str_0000471C)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004BC0)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_mario_mov_pos, -230, 0, 1000)
    WAIT_MS(500)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_close))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004BD0)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(1000)
    CALL(evt_sub_intpl_msec_init, 11, 255, 96, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_MS(2000)
    CALL(evt_peach_set_condition, 0)
    SET_VALUE(GSW(0), 215)
    CALL(evt_snd_bgmoff_f, 512, 1000)
    CALL(evt_snd_envoff_f, 512, 1000)
    CALL(evt_fade_entry, 15, 300, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00004458)), 1)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    SET_VALUE(LF(10), 0)
    SET_VALUE(LW(0), 11)
    CALL_CHILD(PTR(evt_memcard_save))
    CALL(evt_mario_set_mode, 2)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_snd_envoff_f, 512, 2000)
    CALL(evt_snd_sfx_all_stop)
    CALL(evt_fade_set_mapchange_type, 1, 57, 0, 56, 0)
    CALL(evt_bero_mapchange, STRING(((char*)aji_17_str_00004BE0)), 0)
    RETURN
EVT_END()

static EVT_BEGIN(peach_evt_stg5)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING(((char*)aji_17_str_00004184)))
    CALL(evt_mario_set_mode, 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00003F94)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FDC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_00003FE4)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FEC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_0000400C)), 2, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00004020)), 1, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_mario_set_pos, -200, 0, 0)
    CALL(evt_cam3d_evt_set, 230, 45, 372, 22, 85, -25, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    WAIT_MS(2000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    WAIT_MS(500)
    CALL(evt_mario_mov_pos2, -140, 0, 60)
    WAIT_MS(500)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 45, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING(((char*)aji_17_str_000041F4)), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos, -30, -68, 1500)
    WAIT_MS(200)
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000047F8)))
    CALL(evt_mario_set_dir, 270, 200, 0)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000047F8)), STRING(((char*)aji_17_str_00004800)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004BE8)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004818)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004BF8)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(2000)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000042D0)))
    CALL(evt_mario_set_dir, 90, 200, 0)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042D0)), STRING(((char*)aji_17_str_000042D8)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004C08)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(2000)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004C18)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_00004390)), STRING(((char*)aji_17_str_00004398)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004C28)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000042D0)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042D0)), STRING(((char*)aji_17_str_000042D8)))
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004C38)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00004C48)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, -30, 67, -220, -30, 37, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_fade_tec_onoff, 1, 0)
    CALL(evt_mario_dispflag_onoff, 1, 512)
    CALL(evt_mario_set_dispdir, 0)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004C58)), 0, 0)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004C68)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004C78)), 0, 0)
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_fade_tec_onoff, 0, 0)
    CALL(evt_mario_set_dispdir, 180)
    WAIT_MS(300)
    CALL(evt_mario_dispflag_onoff, 0, 512)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004C88)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004C98)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_off, 1000, 11)
    SET_VALUE(GSW(0), 262)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(peach_evt_stg5_1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING(((char*)aji_17_str_00004184)))
    CALL(evt_mario_set_mode, 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00003F94)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_00004014)), 1)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FDC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_00003FE4)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FEC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_0000400C)), 2, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00004020)), 1, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_mario_set_pos, -220, 0, 0)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(w_door_open))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 45, 2000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING(((char*)aji_17_str_000041F4)), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 2000, 11)
        CALL(evt_mario_mov_pos, -30, -68, 2000)
        CALL(evt_mario_set_dir, 90, 200, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(w_door_close))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_mario_wait_move_end)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004CA8)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004CB8)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004CC8)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004CD8)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004CE8)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 92, 171, 0, 59, -13, 700, 11)
    CALL(evt_mario_mov_pos, 0, -95, 700)
    WAIT_MS(150)
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000043F0)), 0, 25, 120, LW(15))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004404)))
    WAIT_MS(3000)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_0000420C)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004CF8)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    SPAWN_EVENT(PTR(mail_sousin_se))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_0000441C)), 1)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00004424)), 0, 0)
    CALL(evt_map_checkanim, STRING(((char*)aji_17_str_00004424)), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_0000441C)), 1)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004D08)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004D18)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, -140, 92, 226, -140, 59, 55, 2000, 11)
    CALL(evt_mario_mov_pos, -140, 0, 2000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LABEL(3)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_open))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(3)
    END_IF
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004D28)), 0, 0)
    CALL(evt_peach_set_condition, 6)
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_00004714)), STRING(((char*)aji_17_str_0000471C)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004D3C)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042D0)), STRING(((char*)aji_17_str_000042D8)))
    CALL(evt_mario_mov_pos, -230, 0, 1000)
    WAIT_MS(500)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LABEL(4)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_close))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(4)
    END_IF
    WAIT_MS(2000)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00004D50)), 0, 0)
    WAIT_MS(1000)
    CALL(evt_sub_intpl_msec_init, 11, 255, 96, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_MS(2000)
    SET_VALUE(GSW(0), 265)
    CALL(evt_peach_set_condition, 0)
    CALL(evt_snd_bgmoff_f, 512, 1000)
    CALL(evt_snd_envoff_f, 512, 1000)
    CALL(evt_fade_entry, 15, 300, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00004458)), 1)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    SET_VALUE(LF(10), 0)
    SET_VALUE(LW(0), 14)
    CALL_CHILD(PTR(evt_memcard_save))
    CALL(evt_mario_set_mode, 2)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_snd_envoff_f, 512, 2000)
    CALL(evt_snd_sfx_all_stop)
    CALL(evt_fade_set_mapchange_type, 1, 57, 0, 56, 0)
    CALL(evt_bero_mapchange, STRING(((char*)aji_17_str_00004D60)), STRING((char*)zero_aji_00015114))
    RETURN
EVT_END()

static EVT_BEGIN(peach_evt_stg6)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING(((char*)aji_17_str_00004184)))
    CALL(evt_mario_set_mode, 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00003F94)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FDC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_00003FE4)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FEC)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_0000400C)), 2, 0)
    CALL(evt_map_playanim, STRING(((char*)aji_17_str_00004020)), 1, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004D68)), 0, STRING(((char*)aji_17_str_000041D4)))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 45, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING(((char*)aji_17_str_000041F4)), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 1500, 11)
    CALL(evt_mario_mov_pos, -30, -68, 1500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004D78)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00004D8C)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING((char*)zero_aji_00015114), 0, 1, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1200)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004DA8)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004DBC)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, -30, 67, -220, -30, 37, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_fade_tec_onoff, 1, 0)
    CALL(evt_mario_dispflag_onoff, 1, 512)
    CALL(evt_mario_set_dispdir, 0)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004DD0)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004DE4)), 0, 0)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000041B4)))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000041B4)), STRING(((char*)aji_17_str_000041DC)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00004DF4)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_fade_tec_onoff, 0, 0)
    CALL(evt_mario_set_dispdir, 180)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004E04)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004E14)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004E24)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, 220, 200, 380, -147, 60, -4, 0, 11)
    WAIT_FRAMES(1)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000042D0)))
    CALL(evt_mario_set_reardir)
    WAIT_MS(3000)
    CALL(evt_fade_out, 1000)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_adjust_dir)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000042A0)))
    CALL(evt_fade_in, 1000)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042A0)), STRING(((char*)aji_17_str_000042A8)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004E34)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004390)))
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004E44)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_00004390)), STRING(((char*)aji_17_str_00004398)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004E54)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004E64)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, -30, 67, -220, -30, 37, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_fade_tec_onoff, 1, 0)
    CALL(evt_mario_set_dispdir, 0)
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004E74)), 0, 0)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004E84)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004E94)), 0, 0)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)str_00004EA4)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004EB4)), 0, 0)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004EC4)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004ED4)), 0, 0)
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_fade_tec_onoff, 0, 0)
    CALL(evt_mario_set_dispdir, 180)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000041B4)))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000041B4)), STRING(((char*)aji_17_str_000041DC)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004EE4)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004EF4)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    WAIT_MS(500)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004320)))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_00004320)), STRING(((char*)aji_17_str_00004328)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004F04)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004F14)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    LABEL(100)
    CALL(evt_cam3d_evt_set, 0, 92, 171, 0, 59, -13, 700, 11)
    CALL(evt_mario_mov_pos, 0, -95, 700)
    WAIT_MS(1000)
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000043F0)), 0, 25, 120, LW(15))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004404)))
    WAIT_MS(1000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    WAIT_MS(500)
    SET_VALUE(LW(0), 180)
    CALL_CHILD(PTR(w_door_open))
    CALL(evt_npc_set_position, STRING(((char*)aji_17_str_00004F24)), -140, 0, 0)
    CALL(evt_npc_set_position, STRING(((char*)aji_17_str_00004F2C)), -190, 0, 0)
    CALL(evt_npc_set_position, STRING(((char*)aji_17_str_00004F38)), -240, 0, 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_close_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(w_door_close))
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)aji_17_str_00004F24)), -80, 0, 0, FLOAT(60.0f), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)aji_17_str_00004F2C)), -130, 0, 0, FLOAT(60.0f), 0)
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING(((char*)aji_17_str_00004F38)), -180, 0, 0, FLOAT(60.0f), 0)
    CALL(evt_msg_print, 0, STRING(((char*)str_00004F40)), 0, STRING(((char*)aji_17_str_00004F2C)))
    CALL(evt_snd_sfxoff, LW(15))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00004F50)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_jump_pos, LW(0), LW(1), LW(2), 200, 1, 10)
    WAIT_MS(300)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004390)))
    CALL(evt_mario_set_dir, 270, 200, 0)
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00004194)), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042A0)), STRING(((char*)aji_17_str_000042A8)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004F70)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, -130, 121, 344, -130, 65, 66, 1500, 11)
    WAIT_MS(1500)
    CALL(evt_snd_bgmon, 512, STRING(((char*)aji_17_str_00004F80)))
    WAIT_MS(2000)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004F98)), 0, STRING(((char*)aji_17_str_00004F2C)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)aji_17_str_00004F24)), 30, -70, 0, FLOAT(60.0f), 0)
        CALL(evt_npc_set_ry, STRING(((char*)aji_17_str_00004F24)), 270)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)aji_17_str_00004F2C)), 32)
        CALL(evt_npc_move_position, STRING(((char*)aji_17_str_00004F2C)), -30, -70, 0, FLOAT(60.0f), 0)
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)aji_17_str_00004F38)), -100, -70, 0, FLOAT(60.0f), 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004FA8)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    WAIT_WHILE(GF(0))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004FB8)), 0, STRING(((char*)aji_17_str_00004F2C)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004FC8)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, -30, 100, 184, -30, 65, -13, 800, 11)
    WAIT_MS(800)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004FD8)), 0, STRING(((char*)aji_17_str_00004F2C)))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004390)))
    WAIT_MS(700)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004FE8)), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_cam3d_evt_set, 0, 75, 387, 0, 75, -13, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00004FF8)), 0, STRING(((char*)aji_17_str_00004F2C)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00005008)), 0, STRING(((char*)aji_17_str_00004F38)))
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)aji_17_str_00004F24)), 105, -95, 0, 70, 4)
        CALL(evt_npc_set_ry, STRING(((char*)aji_17_str_00004F24)), 270)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)aji_17_str_00004F38)), -105, -95, 0, 60, 4)
        CALL(evt_npc_set_ry, STRING(((char*)aji_17_str_00004F38)), 90)
    END_INLINE_EVENT
    WAIT_MS(1400)
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)aji_17_str_00004F24)), 1073741824)
        CALL(evt_npc_status_onoff, 0, STRING(((char*)aji_17_str_00004F24)), 2)
        WAIT_FRAMES(1)
        CALL(evt_npc_move_position, STRING(((char*)aji_17_str_00004F24)), 105, -100, 100, 0, 0)
        WAIT_MS(100)
        CALL(evt_npc_move_position, STRING(((char*)aji_17_str_00004F24)), 105, -95, 100, 0, 0)
        WAIT_MS(100)
        CALL(evt_npc_status_onoff, 1, STRING(((char*)aji_17_str_00004F24)), 2)
        CALL(evt_npc_flag_onoff, 0, STRING(((char*)aji_17_str_00004F24)), 1073741824)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING(((char*)aji_17_str_00004F38)), 1073741824)
        CALL(evt_npc_status_onoff, 0, STRING(((char*)aji_17_str_00004F38)), 2)
        WAIT_FRAMES(1)
        CALL(evt_npc_move_position, STRING(((char*)aji_17_str_00004F38)), -105, -100, 100, 0, 0)
        WAIT_MS(100)
        CALL(evt_npc_move_position, STRING(((char*)aji_17_str_00004F38)), -105, -95, 100, 0, 0)
        WAIT_MS(100)
        CALL(evt_npc_status_onoff, 1, STRING(((char*)aji_17_str_00004F38)), 2)
        CALL(evt_npc_flag_onoff, 0, STRING(((char*)aji_17_str_00004F38)), 1073741824)
    END_INLINE_EVENT
    CALL(evt_mapobj_get_position, STRING(((char*)aji_17_str_00005018)), LW(0), LW(1), LW(2))
    CALL(evt_mapobj_get_position, STRING(((char*)aji_17_str_00005020)), LW(3), LW(4), LW(5))
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00005028)), LW(0), LW(1), LW(2), 0)
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00005028)), LW(3), LW(4), LW(5), 0)
    WAIT_MS(500)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000042D0)))
    CALL(evt_mario_adjust_dir)
    CALL(evt_mario_set_dir, 90, 300, 0)
    CALL(evt_mario_set_reardir)
    WAIT_MS(300)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042D0)), STRING(((char*)aji_17_str_000042D8)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00005040)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, 0, 80, -249, 0, 25, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_fade_tec_onoff, 1, 0)
    CALL(evt_mario_set_dispdir, 0)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_00004390)))
    WAIT_MS(300)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_00004390)), STRING(((char*)aji_17_str_00004398)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00005050)), 0, 0)
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 0, 75, 387, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_000041BC)), 1)
    CALL(evt_fade_tec_onoff, 0, 0)
    CALL(peach_set_pose, STRING(((char*)aji_17_str_000042D0)))
    CALL(evt_mario_set_dispdir, 180)
    CALL(evt_mario_set_reardir)
    WAIT_MS(300)
    CALL(evt_mario_dispflag_onoff, 0, 512)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00005060)), 0, 0)
    CALL(evt_snd_envoff_f, 512, 2000)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00003FEC)))
    WAIT_MS(500)
    CALL(evt_map_pauseanim, 0, STRING(((char*)str_00003FE4)))
    WAIT_MS(500)
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00003FDC)))
    WAIT_MS(500)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00004014)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00005070)), 1)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042D0)), STRING(((char*)aji_17_str_000042D8)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_0000507C)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_0000508C)), 0, STRING(((char*)aji_17_str_00004F2C)))
    CALL(peach_set_pose, STRING(((char*)aji_17_str_0000509C)))
    CALL(evt_mario_set_dir, 270, 200, 0)
    WAIT_MS(300)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_0000509C)), STRING(((char*)aji_17_str_000050A4)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000050AC)), 0, STRING(((char*)aji_17_str_000041D4)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000050BC)), 0, STRING(((char*)aji_17_str_00004F2C)))
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)aji_17_str_00004194)), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_autotalkpose, STRING(((char*)aji_17_str_000041D4)), STRING(((char*)aji_17_str_000042A0)), STRING(((char*)aji_17_str_000042A8)))
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000050CC)), 0, STRING(((char*)aji_17_str_000041D4)))
    CALL(evt_cam3d_evt_set, -35, 100, 184, -35, 65, -13, 800, 11)
    WAIT_MS(800)
    CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000050DC)), 0, STRING(((char*)aji_17_str_00004F2C)))
    SET_VALUE(GSW(0), 341)
    WAIT_MS(2000)
    CALL(evt_snd_bgmoff_f, 512, 1000)
    CALL(evt_snd_envoff_f, 512, 1000)
    CALL(evt_fade_entry, 15, 300, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00004458)), 1)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    SET_VALUE(LF(10), 0)
    SET_VALUE(LW(0), 17)
    CALL_CHILD(PTR(evt_memcard_save))
    CALL(evt_mario_set_mode, 2)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_snd_envoff_f, 512, 2000)
    CALL(evt_snd_sfx_all_stop)
    CALL(evt_fade_set_mapchange_type, 1, 57, 0, 56, 0)
    CALL(evt_bero_mapchange, STRING(((char*)aji_17_str_000050EC)), STRING((char*)zero_aji_00015114))
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(teshita1_init)
    CALL_CHILD(PTR(npc_init_evt))
    CALL(evt_npc_status_onoff, 1, STRING(((char*)aji_17_str_000050F4)), 2)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(teshita2_init)
    CALL_CHILD(PTR(npc_init_evt))
    CALL(evt_npc_status_onoff, 1, STRING(((char*)aji_17_str_000050F4)), 2)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(syuryo_init)
    CALL_CHILD(PTR(npc_init_evt))
    CALL(evt_npc_status_onoff, 1, STRING(((char*)aji_17_str_000050F4)), 2)
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"手下１"*/(char*)aji_17_str_00004F24, 0, 0, (s32)teshita1_init, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"手下２"*/(char*)aji_17_str_00004F38,
    0, 0, (s32)teshita2_init, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"シュリョー"*/(char*)aji_17_str_00004F2C, 0,
    0, (s32)syuryo_init, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

EVT_BEGIN(tec_talk)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_map_replayanim, 0, STRING(((char*)aji_17_str_00004020)))
    IF_INT_EQUAL(GSWF(4219), 0)
        CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_000050F8)), 0, 0)
        SET_VALUE(GSWF(4219), 1)
        ELSE
        CALL(evt_msg_print, 0, STRING(((char*)aji_17_str_00005108)), 0, 0)
    END_IF
    CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(aji_17_init_evt)
    SET_VALUE(LW(0), STRING(((char*)aji_17_str_00005118)))
    SET_VALUE(LW(1), -30)
    SET_VALUE(LW(2), 60)
    SPAWN_EVENT(PTR(evt_camera))
    SET_VALUE(LW(0), STRING(((char*)aji_17_str_00005124)))
    SET_VALUE(LW(1), -60)
    SET_VALUE(LW(2), 30)
    SPAWN_EVENT(PTR(evt_camera))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_0000441C)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00004014)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_00005130)), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_00005148)), 2)
    CALL(evt_mapobj_scale, 0, STRING(((char*)aji_17_str_00005160)), 5, 5, 1)
    IF_INT_EQUAL(GSW(0), 58)
        SPAWN_EVENT(PTR(peach_evt_stg1))
    END_IF
    IF_INT_EQUAL(GSW(0), 113)
        SPAWN_EVENT(PTR(peach_evt_stg2))
    END_IF
    IF_INT_EQUAL(GSW(0), 165)
        SPAWN_EVENT(PTR(peach_evt_stg3))
    END_IF
    IF_INT_EQUAL(GSW(0), 168)
        SPAWN_EVENT(PTR(peach_evt_stg3_1))
        CALL(evt_mario_kill_party, 0)
    END_IF
    IF_INT_EQUAL(GSW(0), 214)
        SPAWN_EVENT(PTR(peach_evt_stg4))
    END_IF
    IF_INT_EQUAL(GSW(0), 261)
        SPAWN_EVENT(PTR(peach_evt_stg5))
    END_IF
    IF_INT_EQUAL(GSW(0), 264)
        SPAWN_EVENT(PTR(peach_evt_stg5_1))
    END_IF
    IF_INT_EQUAL(GSW(0), 340)
        CALL(evt_npc_setup, PTR(npcEnt))
        CALL(evt_shuryolight_init_2_text_B870, STRING(((char*)aji_17_str_00004F2C)))
        CALL(evt_shuryolight_run_evt_2_text_B538, PTR(shuryolight_pow_normal_2_data_36ED8), PTR(shuryolight_head_normal_2_data_37004), PTR(shuryolight_tue_normal_2_data_37104))
        SPAWN_EVENT(PTR(peach_evt_stg6))
    END_IF
    IF_INT_EQUAL(GSW(0), 375)
        IF_INT_EQUAL(GSWF(4186), 0)
            CALL(evt_mario_get_party, LW(15))
            IF_INT_EQUAL(LW(15), 0)
                CALL(evt_mario_set_party, 0, 1)
                CALL(evt_party_run, 0)
                CALL(evt_pouch_mario_recovery)
                CALL(evt_pouch_all_party_recovery)
            END_IF
            SET_VALUE(GSWF(4186), 1)
            SPAWN_EVENT(PTR(evt_last))
            ELSE
            SPAWN_EVENT(PTR(evt_last2))
            SET_VALUE(LW(0), PTR(bero_entry_data))
            CALL(evt_bero_get_info)
            CALL_CHILD(PTR(bero_case_entry))
            RETURN
        END_IF
    END_IF
    SPAWN_EVENT(PTR(evt_emergency))
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    SWITCH(GSW(0))
        CASE_EQUAL(58)
        CASE_EQUAL(168)
        CASE_EQUAL(214)
        CASE_DEFAULT
        CALL_CHILD(PTR(evt_bero_info_run))
    END_SWITCH
    CALL(evt_mario_get_mode, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_mario_kill_party, 0)
        ELSE
        CALL(evt_snd_bgmon, 512, STRING(((char*)aji_17_str_00005168)))
        CALL(evt_snd_envon, 272, STRING(((char*)aji_17_str_00004184)))
    END_IF
    IF_INT_GREATER(GSW(0), 402)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)aji_17_str_00003F94)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)aji_17_str_000041BC)), 1)
        CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FDC)), 1, 0)
        CALL(evt_map_playanim, STRING(((char*)str_00003FE4)), 1, 0)
        CALL(evt_map_playanim, STRING(((char*)aji_17_str_00003FEC)), 1, 0)
        CALL(evt_map_playanim, STRING(((char*)aji_17_str_0000400C)), 2, 0)
        CALL(evt_map_playanim, STRING(((char*)aji_17_str_00004020)), 1, 0)
        CALL(evt_map_pauseanim, 0, STRING(((char*)aji_17_str_00004020)))
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)aji_17_str_00005178)), 0, PTR(tec_talk), 0)
    END_IF
    CALL(evt_snd_set_rev_mode, 1)
    RETURN
EVT_END()


#ifdef NONMATCHING
s32 noise(EventEntry* event, BOOL isFirstCall) {
    s32 alpha = evtGetValue(event, event->args[0]);
    dispEntry(CAMERA_2D, EXT_LIT(float_1100_aji_0001604c, 1100.0f), 0, noiseDisp, (void*)alpha);
    return EVT_RETURN_DONE;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 noise(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		opword 0x80830018
		opword 0x80840000
		bl evtGetValue
		lis r4, float_1100_aji_0001604c@ha
		opword 0x7C661B78
		addi r5, r4, float_1100_aji_0001604c@l
		opword 0x38600008
		lis r4, noiseDisp@ha
		opword 0xC0250000
		addi r5, r4, noiseDisp@l
		opword 0x38800000
		bl dispEntry
		opword 0x80010014
		opword 0x38600002
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop
#endif

static s32 peach_set_pose(EventEntry* event, BOOL isFirstCall) {
    const char* pose = (const char*)evtGetValue(event, event->args[0]);
    MarioWork* mario = marioGetPtr();
    marioChgPose(pose);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
static void polygon(f32 x, f32 y, f32 w, f32 h, f32 s, f32 t) {
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x, y, EXT_LIT(zero_aji_00016000, 0.0f));
    GXTexCoord2f32(EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(zero_aji_00016000, 0.0f));
    GXPosition3f32(x + w, y, EXT_LIT(zero_aji_00016000, 0.0f));
    GXTexCoord2f32(s, EXT_LIT(zero_aji_00016000, 0.0f));
    GXPosition3f32(x + w, y - h, EXT_LIT(zero_aji_00016000, 0.0f));
    GXTexCoord2f32(s, t);
    GXPosition3f32(x, y - h, EXT_LIT(zero_aji_00016000, 0.0f));
    GXTexCoord2f32(EXT_LIT(zero_aji_00016000, 0.0f), t);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
static void polygon(f32 x, f32 y, f32 w, f32 h, f32 s, f32 t) {
	asm volatile {
		opword 0x9421FF90
		opword 0x7C0802A6
		opword 0x90010074
		opword 0xDBE10060
		opword 0xF3E10068
		opword 0xDBC10050
		opword 0xF3C10058
		opword 0xDBA10040
		opword 0xF3A10048
		opword 0xDB810030
		opword 0xF3810038
		opword 0xDB610020
		opword 0xF3610028
		opword 0xDB410010
		opword 0xF3410018
		opword 0xFF400890
		opword 0x38600080
		opword 0xFF601090
		opword 0x38800000
		opword 0xFF801890
		opword 0x38A00004
		opword 0xFFA02090
		opword 0xFFC02890
		opword 0xFFE03090
		bl GXBegin
		opword 0x3C80CC01
		lis r3, zero_aji_00016000@ha
		opword 0xD3448000
		opword 0xEC3AE02A
		opword 0xEC5BE828
		opword 0xD3648000
		lfsu f0, zero_aji_00016000@l(r3)
		opword 0xD0048000
		opword 0xC0030000
		opword 0xD0048000
		opword 0xC0030000
		opword 0xD0048000
		opword 0xD0248000
		opword 0xD3648000
		opword 0xC0030000
		opword 0xD0048000
		opword 0xD3C48000
		opword 0xC0030000
		opword 0xD0048000
		opword 0xD0248000
		opword 0xD0448000
		opword 0xC0030000
		opword 0xD0048000
		opword 0xD3C48000
		opword 0xD3E48000
		opword 0xD3448000
		opword 0xD0448000
		opword 0xC0030000
		opword 0xD0048000
		opword 0xC0030000
		opword 0xD0048000
		opword 0xD3E48000
		opword 0xE3E10068
		opword 0xCBE10060
		opword 0xE3C10058
		opword 0xCBC10050
		opword 0xE3A10048
		opword 0xCBA10040
		opword 0xE3810038
		opword 0xCB810030
		opword 0xE3610028
		opword 0xCB610020
		opword 0xE3410018
		opword 0x80010074
		opword 0xCB410010
		opword 0x7C0803A6
		opword 0x38210070
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
void disp_horogram(CameraId cameraId, void* param) {
    GXCullMode cull;
    Mtx mtx;
    Mtx trans;
    Mtx rot;
    GXColor mat;
    f32 angle;
    NpcEntry* npc = npcNameToPtr("\203z\203\215\203O\203\211\203\200");

    if (horogram_wp->ready) {
        GXGetCullMode(&cull);
        GXInitTexObj(&horogram_wp->tex0, horogram_wp->buf0, 0x130, 0xF0, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&horogram_wp->tex0, GX_NEAR, GX_NEAR, EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(zero_aji_00016000, 0.0f), GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXInitTexObj(&horogram_wp->tex1, horogram_wp->buf1, 0x130, 0xF0, GX_TF_Z8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&horogram_wp->tex1, GX_NEAR, GX_NEAR, EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(zero_aji_00016000, 0.0f), GX_FALSE, GX_FALSE, GX_ANISO_1);
        PSMTXTrans(trans, npc->position.x, npc->position.y, npc->position.z);
        angle = reviseAngle(-npc->direction);
        angle -= camGetPtr(cameraId)->viewYaw;
        angle += (horogram_wp->flags & 4) ? EXT_LIT(float_180_aji_0001603c, 180.0f) : EXT_LIT(zero_aji_00016000, 0.0f);
        PSMTXRotRad(rot, 'y', EXT_LIT(float_deg2rad_aji_00016040, 0.017453292f) * angle);
        PSMTXConcat(trans, rot, mtx);
        PSMTXConcat(camGetPtr(cameraId)->view, mtx, mtx);
        GXSetCurrentMtx(0);
        GXLoadTexObj(&horogram_wp->tex0, GX_TEXMAP0);
        GXLoadTexObj(&horogram_wp->tex1, GX_TEXMAP1);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        mat = npc->color;
        GXSetChanMatColor(GX_COLOR0A0, mat);
        GXSetChanAmbColor(GX_COLOR0A0, horogram_amb);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetNumTevStages(2);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR_NULL);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_C0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_A0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_ZERO);
        GXSetCullMode(GX_CULL_NONE);
        GXLoadPosMtxImm(mtx, GX_PNMTX0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(EXT_LIT(float_neg28_aji_00016044, -28.0f), EXT_LIT(float_55_aji_00016048, 55.0f), EXT_LIT(zero_aji_00016000, 0.0f));
        GXTexCoord2f32(EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(zero_aji_00016000, 0.0f));
        GXPosition3f32(EXT_LIT(float_28_aji_0001602c, 28.0f), EXT_LIT(float_55_aji_00016048, 55.0f), EXT_LIT(zero_aji_00016000, 0.0f));
        GXTexCoord2f32(EXT_LIT(float_1_aji_00016028, 1.0f), EXT_LIT(zero_aji_00016000, 0.0f));
        GXPosition3f32(EXT_LIT(float_28_aji_0001602c, 28.0f), EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(zero_aji_00016000, 0.0f));
        GXTexCoord2f32(EXT_LIT(float_1_aji_00016028, 1.0f), EXT_LIT(float_1_aji_00016028, 1.0f));
        GXPosition3f32(EXT_LIT(float_neg28_aji_00016044, -28.0f), EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(zero_aji_00016000, 0.0f));
        GXTexCoord2f32(EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(float_1_aji_00016028, 1.0f));
        GXSetCullMode(cull);
    }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void disp_horogram(CameraId cameraId, void* param) {
	asm volatile {
		opword 0x9421FF40
		opword 0x7C0802A6
		opword 0x900100C4
		opword 0xDBE100B0
		opword 0xF3E100B8
		opword 0xBFC100A8
		lis r4, aji_17_str_00004494@ha
		opword 0x7C7E1B78
		addi r3, r4, aji_17_str_00004494@l
		bl npcNameToPtr
		lis r4, horogram_wp@ha
		opword 0x7C7F1B78
		addi r3, r4, horogram_wp@l
		opword 0x80630000
		opword 0xA0030048
		opword 0x28000000
		opword 0x41820470
		opword 0x38610010
		bl GXGetCullMode
		lis r3, horogram_wp@ha
		opword 0x38A00130
		addi r3, r3, horogram_wp@l
		opword 0x38C000F0
		opword 0x80630000
		opword 0x38E00006
		opword 0x39000000
		opword 0x39200000
		opword 0x80830000
		opword 0x38630008
		opword 0x39400000
		bl GXInitTexObj
		lis r3, zero_aji_00016000@ha
		lis r5, horogram_wp@ha
		lfs f1, zero_aji_00016000@l(r3)
		addi r3, r5, horogram_wp@l
		opword 0x80630000
		opword 0x38800000
		opword 0xFC400890
		opword 0x38A00000
		opword 0xFC600890
		opword 0x38C00000
		opword 0x38630008
		opword 0x38E00000
		opword 0x39000000
		bl GXInitTexObjLOD
		lis r3, horogram_wp@ha
		opword 0x38A00130
		addi r3, r3, horogram_wp@l
		opword 0x38C000F0
		opword 0x80630000
		opword 0x38E00011
		opword 0x39000000
		opword 0x39200000
		opword 0x80830004
		opword 0x38630028
		opword 0x39400000
		bl GXInitTexObj
		lis r3, zero_aji_00016000@ha
		lis r5, horogram_wp@ha
		lfs f1, zero_aji_00016000@l(r3)
		addi r3, r5, horogram_wp@l
		opword 0x80630000
		opword 0x38800000
		opword 0xFC400890
		opword 0x38A00000
		opword 0xFC600890
		opword 0x38C00000
		opword 0x38630028
		opword 0x38E00000
		opword 0x39000000
		bl GXInitTexObjLOD
		opword 0xC03F008C
		opword 0x38610044
		opword 0xC05F0090
		opword 0xC07F0094
		bl PSMTXTrans
		opword 0xC01F0144
		opword 0xFC200050
		bl reviseAngle
		opword 0xFFE00890
		opword 0x7FC3F378
		bl camGetPtr
		lis r4, horogram_wp@ha
		opword 0xC0030114
		addi r3, r4, horogram_wp@l
		opword 0x80630000
		opword 0xEC3F0028
		opword 0xA003004A
		opword 0x5400077B
		opword 0x41820010
		lis r3, float_180_aji_0001603c@ha
		lfs f0, float_180_aji_0001603c@l(r3)
		opword 0x4800000C
		lis r3, zero_aji_00016000@ha
		lfs f0, zero_aji_00016000@l(r3)
		lis r3, float_deg2rad_aji_00016040@ha
		opword 0xEC21002A
		addi r4, r3, float_deg2rad_aji_00016040@l
		opword 0x38610014
		opword 0xC0040000
		opword 0x38800079
		opword 0xEC200072
		bl PSMTXRotRad
		opword 0x38610044
		opword 0x38810014
		opword 0x38A10074
		bl PSMTXConcat
		opword 0x7FC3F378
		bl camGetPtr
		opword 0x38810074
		opword 0x3863011C
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38600000
		bl GXSetCurrentMtx
		lis r3, horogram_wp@ha
		opword 0x38800000
		addi r3, r3, horogram_wp@l
		opword 0x80630000
		opword 0x38630008
		bl GXLoadTexObj
		lis r3, horogram_wp@ha
		opword 0x38800001
		addi r3, r3, horogram_wp@l
		opword 0x80630000
		opword 0x38630028
		bl GXLoadTexObj
		bl GXClearVtxDesc
		opword 0x38600009
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x38800009
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x3860000D
		opword 0x38800001
		bl GXSetVtxDesc
		opword 0x38600000
		opword 0x3880000D
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00000
		bl GXSetVtxAttrFmt
		opword 0x38600001
		bl GXSetNumChans
		opword 0x38600004
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0x39000002
		opword 0x39200002
		bl GXSetChanCtrl
		opword 0x801F0114
		opword 0x3881000C
		opword 0x38600004
		opword 0x9001000C
		bl GXSetChanMatColor
		lis r3, dat_aji_000152e4@ha
		opword 0x38810008
		addi r5, r3, dat_aji_000152e4@l
		opword 0x38600004
		opword 0x80050000
		opword 0x90010008
		bl GXSetChanAmbColor
		opword 0x38600001
		bl GXSetNumTexGens
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0003C
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x38600002
		bl GXSetNumTevStages
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00004
		bl GXSetTevOrder
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000001
		bl GXSetTevColorOp
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000001
		bl GXSetTevAlphaOp
		opword 0x38600000
		opword 0x38800008
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800005
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600001
		opword 0x38800000
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
		opword 0x38800002
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600001
		opword 0x38800001
		opword 0x38A00007
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600000
		bl GXSetCullMode
		opword 0x38610074
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x38600080
		opword 0x38800000
		opword 0x38A00004
		bl GXBegin
		lis r4, float_neg28_aji_00016044@ha
		lis r3, float_55_aji_00016048@ha
		addi r8, r4, float_neg28_aji_00016044@l
		opword 0x3CE0CC01
		opword 0xC0080000
		addi r6, r3, float_55_aji_00016048@l
		lis r5, zero_aji_00016000@ha
		lis r4, float_28_aji_0001602c@ha
		opword 0xD0078000
		lis r3, float_1_aji_00016028@ha
		opword 0xC0060000
		opword 0xD0078000
		lfsu f0, zero_aji_00016000@l(r5)
		opword 0xD0078000
		opword 0xC0050000
		opword 0xD0078000
		opword 0xC0050000
		opword 0xD0078000
		lfsu f0, float_28_aji_0001602c@l(r4)
		opword 0xD0078000
		opword 0xC0060000
		opword 0xD0078000
		opword 0xC0050000
		opword 0xD0078000
		lfsu f0, float_1_aji_00016028@l(r3)
		opword 0xD0078000
		opword 0xC0050000
		opword 0xD0078000
		opword 0xC0040000
		opword 0xD0078000
		opword 0xC0050000
		opword 0xD0078000
		opword 0xC0050000
		opword 0xD0078000
		opword 0xC0030000
		opword 0xD0078000
		opword 0xC0030000
		opword 0xD0078000
		opword 0xC0080000
		opword 0xD0078000
		opword 0xC0050000
		opword 0xD0078000
		opword 0xC0050000
		opword 0xD0078000
		opword 0xC0050000
		opword 0xD0078000
		opword 0xC0030000
		opword 0xD0078000
		opword 0x80610010
		bl GXSetCullMode
		opword 0xE3E100B8
		opword 0xCBE100B0
		opword 0xBBC100A8
		opword 0x800100C4
		opword 0x7C0803A6
		opword 0x382100C0
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
s32 disp_horogram_evt(EventEntry* event, BOOL isFirstCall) {
    dispEntry(CAMERA_3D, 0.0f, 2, disp_horogram, NULL);
    return EVT_RETURN_BLOCK;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 disp_horogram_evt(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, zero_aji_00016000@ha
		lis r4, disp_horogram@ha
		addi r6, r3, zero_aji_00016000@l
		opword 0x90010014
		opword 0xC0260000
		addi r5, r4, disp_horogram@l
		opword 0x38600004
		opword 0x38800002
		opword 0x38C00000
		bl dispEntry
		opword 0x80010014
		opword 0x38600000
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
void peach_capture(CameraId cameraId, void* param) {
    CameraEntry saved = *camGetCurPtr();
    Mtx44 projMtx;
    Mtx lookAt;
    Mtx ident;
    f32 viewport[6];
    f32 proj[7];
    u32 sx, sy, sw, sh;
    NpcEntry* holo;
    NpcEntry* holo2;
    NpcEntry* npc;

    holo = npcNameToPtr("\203z\203\215\203O\203\211\203\200");
    holo2 = npcNameToPtr("\203z\203\215\203O\203\211\203\2002");
    if (EXT_LIT(float_90_aji_00016018, 90.0f) <= holo->direction && holo->direction < EXT_LIT(float_270_aji_0001601c, 270.0f)) {
        npc = holo2;
        if (!(horogram_wp->flags & 2)) {
            animPoseSetLocalTime(holo2->poseId, 0.0f);
        }
        horogram_wp->flags |= 2;
    } else {
        npc = holo;
        if (horogram_wp->flags & 2) {
            animPoseSetLocalTime(holo->poseId, 0.0f);
        }
        horogram_wp->flags &= ~2;
    }
    if (!(horogram_wp->flags & 1)) {
        npc = holo;
    }
    GXGetViewportv(viewport);
    GXGetProjectionv(proj);
    GXGetScissor(&sx, &sy, &sw, &sh);
    GXSetViewport(EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(float_608_aji_00016020, 608.0f), EXT_LIT(float_480_aji_00016024, 480.0f), EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(float_1_aji_00016028, 1.0f));
    GXSetScissor(1, 1, 606, 478);
    C_MTXOrtho(projMtx, EXT_LIT(float_28_aji_0001602c, 28.0f), EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(float_neg14_aji_00016030, -14.0f), EXT_LIT(float_14_aji_00016034, 14.0f), EXT_LIT(float_1_aji_00016028, 1.0f), EXT_LIT(float_100_aji_00016038, 100.0f));
    GXSetProjection(projMtx, GX_ORTHOGRAPHIC);
    {
        Vec pos;
        Vec up;
        Vec target;

        target = horogram_target;
        up = horogram_up;
        pos = horogram_pos;

        C_MTXLookAt(lookAt, &pos, &up, &target);
    }
    PSMTXCopy(lookAt, camGetCurPtr()->view);
    PSMTXIdentity(ident);
    animPoseSetMaterialFlagOff(npc->poseId, 0x40);
    animPoseMain(npc->poseId);
    animPoseDrawMtx(npc->poseId, ident, 1, EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(float_1_aji_00016028, 1.0f));
    animPoseDrawMtx(npc->poseId, ident, 2, EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(float_1_aji_00016028, 1.0f));
    animPoseDrawMtx(npc->poseId, ident, 3, EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(float_1_aji_00016028, 1.0f));
    GXSetTexCopySrc(0, 0, 0x260, 0x1E0);
    GXSetTexCopyDst(0x130, 0xF0, GX_TF_RGBA8, GX_TRUE);
    GXCopyTex(horogram_wp->buf0, GX_FALSE);
    GXPixModeSync();
    GXSetTexCopyDst(0x130, 0xF0, GX_TF_Z8, GX_TRUE);
    GXCopyTex(horogram_wp->buf1, GX_TRUE);
    GXPixModeSync();
    PSMTXCopy(saved.view, camGetCurPtr()->view);
    GXSetViewport(viewport[0], viewport[1], viewport[2], viewport[3], viewport[4], viewport[5]);
    GXSetProjectionv(proj);
    GXSetScissor(sx, sy, sw, sh);
    horogram_wp->ready = 1;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void peach_capture(CameraId cameraId, void* param) {
	asm volatile {
		opword 0x9421FC80
		opword 0x7C0802A6
		opword 0x90010384
		opword 0xBF810370
		bl camGetCurPtr
		opword 0x3800004C
		opword 0x38A1010C
		opword 0x3883FFFC
		opword 0x7C0903A6
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
		lis r3, aji_17_str_00004494@ha
		addi r3, r3, aji_17_str_00004494@l
		bl npcNameToPtr
		lis r4, aji_17_str_00004524@ha
		opword 0x7C7F1B78
		addi r0, r4, aji_17_str_00004524@l
		opword 0x7C030378
		bl npcNameToPtr
		lis r4, float_90_aji_00016018@ha
		opword 0xC03F0144
		lfs f0, float_90_aji_00016018@l(r4)
		opword 0xFC000840
		opword 0x4C401382
		opword 0x4082005C
		lis r4, float_270_aji_0001601c@ha
		lfs f0, float_270_aji_0001601c@l(r4)
		opword 0xFC010040
		opword 0x4080004C
		lis r4, horogram_wp@ha
		opword 0x7C7E1B78
		addi r4, r4, horogram_wp@l
		opword 0x80840000
		opword 0xA004004A
		opword 0x540007BD
		opword 0x40820014
		lis r4, zero_aji_00016000@ha
		opword 0x80630104
		lfs f1, zero_aji_00016000@l(r4)
		bl animPoseSetLocalTime
		lis r3, horogram_wp@ha
		addi r3, r3, horogram_wp@l
		opword 0x80630000
		opword 0xA003004A
		opword 0x60000002
		opword 0xB003004A
		opword 0x48000048
		lis r3, horogram_wp@ha
		opword 0x7FFEFB78
		addi r3, r3, horogram_wp@l
		opword 0x80630000
		opword 0xA003004A
		opword 0x540007BD
		opword 0x41820014
		lis r4, zero_aji_00016000@ha
		opword 0x807F0104
		lfs f1, zero_aji_00016000@l(r4)
		bl animPoseSetLocalTime
		lis r3, horogram_wp@ha
		addi r3, r3, horogram_wp@l
		opword 0x80630000
		opword 0xA003004A
		opword 0x540007FA
		opword 0xB003004A
		lis r3, horogram_wp@ha
		addi r3, r3, horogram_wp@l
		opword 0x80630000
		opword 0xA003004A
		opword 0x540007FF
		opword 0x40820008
		opword 0x7FFEFB78
		opword 0x38610058
		bl GXGetViewportv
		opword 0x3861003C
		bl GXGetProjectionv
		opword 0x38610014
		opword 0x38810010
		opword 0x38A1000C
		opword 0x38C10008
		bl GXGetScissor
		lis r3, zero_aji_00016000@ha
		lis r5, float_608_aji_00016020@ha
		lfs f1, zero_aji_00016000@l(r3)
		lis r4, float_480_aji_00016024@ha
		lis r3, float_1_aji_00016028@ha
		lfs f3, float_608_aji_00016020@l(r5)
		opword 0xFC400890
		lfs f4, float_480_aji_00016024@l(r4)
		opword 0xFCA00890
		lfs f6, float_1_aji_00016028@l(r3)
		bl GXSetViewport
		opword 0x38600001
		opword 0x38800001
		opword 0x38A0025E
		opword 0x38C001DE
		bl GXSetScissor
		lis r8, float_28_aji_0001602c@ha
		lis r7, zero_aji_00016000@ha
		lis r6, float_neg14_aji_00016030@ha
		lis r5, float_14_aji_00016034@ha
		lis r4, float_1_aji_00016028@ha
		lis r3, float_100_aji_00016038@ha
		addi r9, r8, float_28_aji_0001602c@l
		addi r8, r7, zero_aji_00016000@l
		addi r7, r6, float_neg14_aji_00016030@l
		addi r6, r5, float_14_aji_00016034@l
		addi r5, r4, float_1_aji_00016028@l
		addi r4, r3, float_100_aji_00016038@l
		opword 0xC0290000
		opword 0x386100D0
		opword 0xC0480000
		opword 0xC0670000
		opword 0xC0860000
		opword 0xC0A50000
		opword 0xC0C40000
		bl C_MTXOrtho
		opword 0x386100D0
		opword 0x38800001
		bl GXSetProjection
		lis r3, vec3_aji_00015300@ha
		lis r4, vec3_aji_000152f4@ha
		addi r5, r3, vec3_aji_00015300@l
		lis r3, vec3_aji_000152e8@ha
		addi r6, r4, vec3_aji_000152f4@l
		opword 0x83850000
		addi r9, r3, vec3_aji_000152e8@l
		opword 0x83A50004
		opword 0x83E50008
		opword 0x386100A0
		opword 0x81860000
		opword 0x38810030
		opword 0x81660004
		opword 0x38A10024
		opword 0x81460008
		opword 0x38C10018
		opword 0x81090000
		opword 0x80E90004
		opword 0x80090008
		opword 0x93810018
		opword 0x93A1001C
		opword 0x93E10020
		opword 0x91810024
		opword 0x91610028
		opword 0x9141002C
		opword 0x91010030
		opword 0x90E10034
		opword 0x90010038
		bl C_MTXLookAt
		bl camGetCurPtr
		opword 0x7C641B78
		opword 0x386100A0
		opword 0x3884011C
		bl PSMTXCopy
		opword 0x38610070
		bl PSMTXIdentity
		opword 0x807E0104
		opword 0x38800040
		bl animPoseSetMaterialFlagOff
		opword 0x807E0104
		bl animPoseMain
		lis r3, zero_aji_00016000@ha
		lis r4, float_1_aji_00016028@ha
		addi r5, r3, zero_aji_00016000@l
		lfs f2, float_1_aji_00016028@l(r4)
		opword 0xC0250000
		opword 0x38810070
		opword 0x807E0104
		opword 0x38A00001
		bl animPoseDrawMtx
		lis r3, zero_aji_00016000@ha
		lis r4, float_1_aji_00016028@ha
		addi r5, r3, zero_aji_00016000@l
		lfs f2, float_1_aji_00016028@l(r4)
		opword 0xC0250000
		opword 0x38810070
		opword 0x807E0104
		opword 0x38A00002
		bl animPoseDrawMtx
		lis r3, zero_aji_00016000@ha
		lis r4, float_1_aji_00016028@ha
		addi r5, r3, zero_aji_00016000@l
		lfs f2, float_1_aji_00016028@l(r4)
		opword 0xC0250000
		opword 0x38810070
		opword 0x807E0104
		opword 0x38A00003
		bl animPoseDrawMtx
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00260
		opword 0x38C001E0
		bl GXSetTexCopySrc
		opword 0x38600130
		opword 0x388000F0
		opword 0x38A00006
		opword 0x38C00001
		bl GXSetTexCopyDst
		lis r3, horogram_wp@ha
		opword 0x38800000
		addi r3, r3, horogram_wp@l
		opword 0x80630000
		opword 0x80630000
		bl GXCopyTex
		bl GXPixModeSync
		opword 0x38600130
		opword 0x388000F0
		opword 0x38A00011
		opword 0x38C00001
		bl GXSetTexCopyDst
		lis r3, horogram_wp@ha
		opword 0x38800001
		addi r3, r3, horogram_wp@l
		opword 0x80630000
		opword 0x80630004
		bl GXCopyTex
		bl GXPixModeSync
		bl camGetCurPtr
		opword 0x7C641B78
		opword 0x3861022C
		opword 0x3884011C
		bl PSMTXCopy
		opword 0xC0210058
		opword 0xC041005C
		opword 0xC0610060
		opword 0xC0810064
		opword 0xC0A10068
		opword 0xC0C1006C
		bl GXSetViewport
		opword 0x3861003C
		bl GXSetProjectionv
		opword 0x80610014
		opword 0x80810010
		opword 0x80A1000C
		opword 0x80C10008
		bl GXSetScissor
		lis r3, horogram_wp@ha
		opword 0x38000001
		addi r3, r3, horogram_wp@l
		opword 0x80630000
		opword 0xB0030048
		opword 0xBB810370
		opword 0x80010384
		opword 0x7C0803A6
		opword 0x38210380
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
s32 horogram_cap_evt(EventEntry* event, BOOL isFirstCall) {
    dispEntry(CAMERA_3D, 1000.0f, 0, peach_capture, NULL);
    return EVT_RETURN_BLOCK;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 horogram_cap_evt(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, float_1000_aji_00016014@ha
		lis r4, peach_capture@ha
		addi r6, r3, float_1000_aji_00016014@l
		opword 0x90010014
		opword 0xC0260000
		addi r5, r4, peach_capture@l
		opword 0x38600004
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
#endif

s32 horogram_init(EventEntry* event, BOOL isFirstCall) {
    u32 size = GXGetTexBufferSize(0x260, 0x1E0, GX_TF_RGBA8, GX_FALSE, 0);

    horogram_wp = _mapAlloc(sizeof(HorogramWork));
    horogram_wp->buf0 = _mapAlloc(size);
    horogram_wp->buf1 = _mapAlloc(GXGetTexBufferSize(0x260, 0x1E0, GX_TF_Z8, GX_FALSE, 0));
    horogram_wp->ready = 0;
    horogram_wp->flags = 0;
    return EVT_RETURN_DONE;
}

s32 horogram_flag_onoff(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    s32 on = evtGetValue(event, args[0]);
    s32 mask = evtGetValue(event, args[1]);

    if (on) {
        horogram_wp->flags |= mask;
    } else {
        horogram_wp->flags &= ~mask;
    }
    return EVT_RETURN_DONE;
}

s32 get_center(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;

    evtSetFloat(event, args[0], dance_dt.cx);
    evtSetFloat(event, args[1], dance_dt.cy);
    return EVT_RETURN_DONE;
}

s32 get_local_rotate(EventEntry* event, BOOL isFirstCall) {
    evtSetFloat(event, event->args[0], dance_dt.rot);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
s32 set_local_rotate(EventEntry* event, BOOL isFirstCall) {
    f32 r;

    dance_dt.rot = evtGetFloat(event, event->args[0]);
    r = dance_dt.rot;
    if (r > EXT_LIT(float_6p2832_aji_00016010, 6.2831855f)) {
        dance_dt.rot = r - 6.2831855f;
    }
    if (dance_dt.rot < EXT_LIT(zero_aji_00016000, 0.0f)) {
        dance_dt.rot += 6.2831855f;
    }
    return EVT_RETURN_DONE;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 set_local_rotate(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		opword 0x80830018
		opword 0x80840000
		bl evtGetFloat
		lis r3, float_6p2832_aji_00016010@ha
		opword 0xFC400818
		lfs f0, float_6p2832_aji_00016010@l(r3)
		lis r4, dance_dt@ha
		addi r4, r4, dance_dt@l
		opword 0xFC020040
		opword 0xD024000C
		opword 0x4081000C
		opword 0xEC020028
		opword 0xD004000C
		lis r3, zero_aji_00016000@ha
		opword 0xC024000C
		lfs f0, zero_aji_00016000@l(r3)
		opword 0xFC010040
		opword 0x40800014
		lis r3, float_6p2832_aji_00016010@ha
		lfs f0, float_6p2832_aji_00016010@l(r3)
		opword 0xEC01002A
		opword 0xD004000C
		opword 0x80010014
		opword 0x38600002
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop
#endif

s32 dance_get_step(EventEntry* event, BOOL isFirstCall) {
    evtSetValue(event, event->args[0], dance_dt.step);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
s32 dance_data_init(EventEntry* event, BOOL isFirstCall) {
    dance_dt.flags = 0;
    dance_dt.cx = EXT_LIT(zero_aji_00016000, 0.0f);
    dance_dt.cy = EXT_LIT(float_neg80_aji_00016008, -80.0f);
    dance_dt.rot = EXT_LIT(float_neg0p47124_aji_0001600c, -0.4712389f);
    dance_dt.step = 0;
    dance_dt.movePos = 0;
    return EVT_RETURN_DONE;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 dance_data_init(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		lis r5, zero_aji_00016000@ha
		lis r4, float_neg80_aji_00016008@ha
		lis r3, float_neg0p47124_aji_0001600c@ha
		lis r7, dance_dt@ha
		addi r6, r5, zero_aji_00016000@l
		addi r5, r4, float_neg80_aji_00016008@l
		addi r4, r3, float_neg0p47124_aji_0001600c@l
		opword 0xC0460000
		addi r6, r7, dance_dt@l
		opword 0x38000000
		opword 0xC0250000
		opword 0x38600002
		opword 0xC0040000
		opword 0xB0060000
		opword 0xD0460004
		opword 0xD0260008
		opword 0xD006000C
		opword 0x98060002
		opword 0x98060003
	}
}
#pragma pop
#endif

s32 dance_flag_onoff(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    s32 mask = evtGetValue(event, args[0]);
    s32 on = evtGetValue(event, args[1]);

    if (on) {
        dance_dt.flags |= mask;
    } else {
        dance_dt.flags &= ~mask;
    }
    return EVT_RETURN_DONE;
}

s32 dance_flag_check(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    s32 mask = evtGetValue(event, args[0]);

    if (dance_dt.flags & mask) {
        evtSetValue(event, args[1], 1);
    } else {
        evtSetValue(event, args[1], 0);
    }
    return EVT_RETURN_DONE;
}

s32 dance_reverse(EventEntry* event, BOOL isFirstCall) {
    if (dance_dt.flags & 1) {
        dance_dt.flags &= ~1;
    } else {
        dance_dt.flags |= 1;
    }
    return EVT_RETURN_DONE;
}

s32 move_center(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    f32 x0 = evtGetFloat(event, args[0]);
    f32 z0 = evtGetFloat(event, args[1]);
    f32 x1 = evtGetFloat(event, args[2]);
    f32 z1 = evtGetFloat(event, args[3]);
    s32 frames = evtGetValue(event, args[4]);
    OSTime now = gp->renderTime;
    s32 elapsed;

    if (isFirstCall) {
        dance_dt.flags |= 4;
        event->userdata[0] = ((u64)now >> 32) & 0xFFFFFFFF;
        event->userdata[1] = now & 0xFFFFFFFF;
        return EVT_RETURN_BLOCK;
    }
    elapsed = OSTicksToMilliseconds((u64)(s32)((u32)now - event->userdata[1]));
    if (elapsed < frames) {
        dance_dt.cx = intplGetValue(11, elapsed, frames, x0, x1);
        dance_dt.cy = intplGetValue(11, elapsed, frames, z0, z1);
        return EVT_RETURN_BLOCK;
    }
    dance_dt.cx = x1;
    dance_dt.cy = z1;
    dance_dt.flags &= ~4;
    if (++dance_dt.step >= 3) {
        dance_dt.step = 0;
    }
    return EVT_RETURN_DONE;
}

s32 compute_move_pos(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;

    if (!(dance_dt.flags & 1)) {
        dance_dt.movePos = (dance_dt.movePos + 1) % 15;
    } else if (dance_dt.movePos != 0) {
        dance_dt.movePos--;
    } else {
        dance_dt.movePos = 14;
    }
    evtSetFloat(event, args[0], move_pos_list[dance_dt.movePos][0]);
    evtSetFloat(event, args[1], move_pos_list[dance_dt.movePos][1]);
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
s32 compute_peach_pos(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 z = evtGetFloat(event, args[1]);
    f32 s = sin(dance_dt.rot);
    f32 c = cos(dance_dt.rot);

    evtSetFloat(event, args[2], x + EXT_LIT(float_5p5_aji_00016004, 5.5f) * s);
    evtSetFloat(event, args[3], z - 5.5f * c);
    return EVT_RETURN_DONE;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 compute_peach_pos(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		mr r29, r3
		opword 0x83C30018
		opword 0x809E0000
		bl evtGetFloat
		opword 0xFFC00890
		opword 0x809E0004
		opword 0x7FA3EB78
		bl evtGetFloat
		lis r3, dance_dt@ha
		opword 0xFFE00890
		addi r31, r3, dance_dt@l
		opword 0xC03F000C
		bl sin
		opword 0xFFA00818
		opword 0xC03F000C
		bl cos
		lis r3, float_5p5_aji_00016004@ha
		frsp f28, f1
		lfs f0, float_5p5_aji_00016004@l(r3)
		opword 0x7FA3EB78
		opword 0x809E0008
		opword 0xEC20F77A
		bl evtSetFloat
		lis r3, float_5p5_aji_00016004@ha
		opword 0x809E000C
		addi r5, r3, float_5p5_aji_00016004@l
		opword 0x7FA3EB78
		opword 0xC0050000
		opword 0xEC20FF3C
		bl evtSetFloat
		opword 0x38600002
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
s32 compute_horogram_pos(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 z = evtGetFloat(event, args[1]);
    f32 s = sin(dance_dt.rot);
    f32 c = cos(dance_dt.rot);

    evtSetFloat(event, args[2], x - 5.5f * s);
    evtSetFloat(event, args[3], z + EXT_LIT(float_5p5_aji_00016004, 5.5f) * c);
    return EVT_RETURN_DONE;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 compute_horogram_pos(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		mr r29, r3
		opword 0x83C30018
		opword 0x809E0000
		bl evtGetFloat
		opword 0xFFC00890
		opword 0x809E0004
		opword 0x7FA3EB78
		bl evtGetFloat
		lis r3, dance_dt@ha
		opword 0xFFE00890
		addi r31, r3, dance_dt@l
		opword 0xC03F000C
		bl sin
		opword 0xFFA00818
		opword 0xC03F000C
		bl cos
		lis r3, float_5p5_aji_00016004@ha
		frsp f28, f1
		lfs f0, float_5p5_aji_00016004@l(r3)
		opword 0x7FA3EB78
		opword 0x809E0008
		opword 0xEC20F77C
		bl evtSetFloat
		lis r3, float_5p5_aji_00016004@ha
		opword 0x809E000C
		addi r5, r3, float_5p5_aji_00016004@l
		opword 0x7FA3EB78
		opword 0xC0050000
		opword 0xEC20FF3A
		bl evtSetFloat
		opword 0x38600002
	}
}
#pragma pop
#endif

s32 wait_action_end(EventEntry* event, BOOL isFirstCall) {
    return (dance_dt.flags & 2) ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}

s32 wait_action_begin(EventEntry* event, BOOL isFirstCall) {
    return (dance_dt.flags & 2) ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

s32 wait_move_end(EventEntry* event, BOOL isFirstCall) {
    return (dance_dt.flags & 4) ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}

s32 btn_check(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    s32 dir = evtGetValue(event, args[0]);
    u32 btn = keyGetButtonTrg(0);
    s32 a = btn & 0x100;
    s32 b = btn & 0x200;
    s32 x = btn & 0x400;
    s32 ret = 0;

    switch (dir) {
    case 1:
        if (a && !(b | x)) {
            ret = 1;
        } else if (!a && (b | x)) {
            ret = 2;
        }
        break;
    case 2:
        if (b && !(a | x)) {
            ret = 1;
        } else if (!b && (a | x)) {
            ret = 2;
        }
        break;
    case 0:
        if (x && !(a | b)) {
            ret = 1;
        } else if (!x && (a | b)) {
            ret = 2;
        }
        break;
    default:
        if (a | b | x) {
            ret = 2;
        }
        break;
    }
    evtSetValue(event, args[1], ret);
    return EVT_RETURN_DONE;
}

s32 set_npc_pos(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    NpcEntry* npc = npcNameToPtr(name);

    npc->position.x = npc->prevPosition.x = x;
    npc->position.y = npc->prevPosition.y = y;
    npc->position.z = npc->prevPosition.z = z;
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
s32 peach_dance_after_fail(EventEntry* event, BOOL isFirstCall) {
    marioChgPoseTime("P_O_F_1", 20);
    return EVT_RETURN_DONE;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 peach_dance_after_fail(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, aji_17_str_000044A8@ha
		opword 0x38800014
		opword 0x90010014
		addi r3, r3, aji_17_str_000044A8@l
		bl marioChgPoseTime
		opword 0x80010014
		opword 0x38600002
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
s32 evt_fuki_btn(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    s32 type = evtGetValue(event, args[0]);
    const char* name = (const char*)evtGetValue(event, args[1]);
    const char* npcName = (const char*)evtGetValue(event, args[2]);
    f32 x = evtGetFloat(event, args[3]);
    f32 y = evtGetFloat(event, args[4]);
    f32 z = evtGetFloat(event, args[5]);
    f32 size = evtGetFloat(event, args[6]);
    f32 angle = evtGetFloat(event, args[7]);
    f32 unk = evtGetFloat(event, args[8]);
    NpcEntry* npc;
    EffectEntry* eff;

    if (strcmp(npcName, "me") == 0) {
        npc = event->ownerNPC;
    } else {
        npc = npcNameToPtr(npcName);
    }
    eff = effPeachFukidashiEntry(type, npc, 10000, EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(zero_aji_00016000, 0.0f), EXT_LIT(zero_aji_00016000, 0.0f), angle);
    if (name != NULL && strcmp(name, "") != 0) {
        effSetName(eff, name);
    }
    return EVT_RETURN_DONE;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 evt_fuki_btn(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0xDBE10020
		opword 0xF3E10028
		opword 0xBF61000C
		opword 0x7C7B1B78
		opword 0x83E30018
		opword 0x809F0000
		bl evtGetValue
		opword 0x809F0004
		opword 0x7C7E1B78
		opword 0x7F63DB78
		bl evtGetValue
		opword 0x809F0008
		opword 0x7C7D1B78
		opword 0x7F63DB78
		bl evtGetValue
		opword 0x809F000C
		opword 0x7C7C1B78
		opword 0x7F63DB78
		bl evtGetFloat
		opword 0x809F0010
		opword 0x7F63DB78
		bl evtGetFloat
		opword 0x809F0014
		opword 0x7F63DB78
		bl evtGetFloat
		opword 0x809F0018
		opword 0x7F63DB78
		bl evtGetFloat
		opword 0x809F001C
		opword 0x7F63DB78
		bl evtGetFloat
		opword 0xFFE00890
		opword 0x809F0020
		opword 0x7F63DB78
		bl evtGetFloat
		lis r4, aji_17_str_000050F4@ha
		opword 0x7F83E378
		addi r4, r4, aji_17_str_000050F4@l
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x809B0170
		opword 0x48000010
		opword 0x7F83E378
		bl npcNameToPtr
		opword 0x7C641B78
		lis r3, zero_aji_00016000@ha
		opword 0xFCA0F890
		addi r5, r3, zero_aji_00016000@l
		opword 0xC0250000
		opword 0x7FC3F378
		opword 0x38A02710
		opword 0xFC400890
		opword 0xFC600890
		opword 0xFC800890
		bl effPeachFukidashiEntry
		opword 0x281D0000
		opword 0x7C7C1B78
		opword 0x41820028
		lis r4, zero_aji_00015114@ha
		opword 0x7FA3EB78
		addi r4, r4, zero_aji_00015114@l
		bl strcmp
		opword 0x2C030000
		opword 0x41820010
		opword 0x7F83E378
		opword 0x7FA4EB78
		bl effSetName
		opword 0x38600002
		opword 0xE3E10028
		opword 0xCBE10020
		opword 0xBB61000C
		opword 0x80010034
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop
#endif

s32 evt_fuki_btn_set_batu(EventEntry* event, BOOL isFirstCall) {
    effSetPeachFukiBatu((const char*)evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING // only the NONMATCHING C uses it
static __declspec(section ".rodata") const char horogram_pose_suffix[] = "R";
#endif
#ifdef NONMATCHING
s32 horogram_set_pose(EventEntry* event, BOOL isFirstCall) {
    char name[24];
    const char* pose = (const char*)evtGetValue(event, event->args[0]);
    NpcEntry* npc = npcNameToPtr("\203z\203\215\203O\203\211\203\200");
    NpcEntry* npc2 = npcNameToPtr("\203z\203\215\203O\203\211\203\2002");
    MarioWork* mario = marioGetPtr();

    animPoseSetAnim(npc->poseId, pose, TRUE);
    strcpy(name, pose);
    strcat(name, horogram_pose_suffix);
    animPoseSetAnim(npc2->poseId, name, TRUE);
    return EVT_RETURN_DONE;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 horogram_set_pose(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0xBFA10024
		opword 0x80830018
		opword 0x80840000
		bl evtGetValue
		lis r4, aji_17_str_00004494@ha
		opword 0x7C7D1B78
		addi r0, r4, aji_17_str_00004494@l
		opword 0x7C030378
		bl npcNameToPtr
		lis r4, aji_17_str_00004524@ha
		opword 0x7C7E1B78
		addi r3, r4, aji_17_str_00004524@l
		bl npcNameToPtr
		opword 0x7C7F1B78
		bl marioGetPtr
		opword 0x807E0104
		opword 0x7FA4EB78
		opword 0x38A00001
		bl animPoseSetAnim
		opword 0x7FA4EB78
		opword 0x38610008
		bl strcpy
		lis r4, aji_17_str_00005184@ha
		opword 0x38610008
		addi r4, r4, aji_17_str_00005184@l
		bl strcat
		opword 0x807F0104
		opword 0x38810008
		opword 0x38A00001
		bl animPoseSetAnim
		opword 0xBBA10024
		opword 0x38600002
		opword 0x80010034
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop
#endif


#pragma explicit_zero_data on
#pragma explicit_zero_data reset


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_04_000271D4_data[1] = {0};

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const char aji_17_str_00003F50[12] = "S_door1_1\0\0";
__declspec(section ".rodata") const char aji_17_str_00003F5C[12] = "S_door1_2\0\0";
__declspec(section ".rodata") const char aji_17_str_00003F68[8] = "w_bero\0";
__declspec(section ".rodata") const char aji_17_str_00003F70[8] = "aji_01\0";
__declspec(section ".rodata") const char aji_17_str_00003F78[12] = "e_bero_5\0\0\0";
__declspec(section ".rodata") const u32 zero_aji_00014dfc = 0x00000000;
__declspec(section ".rodata") const char aji_17_str_00003F88[12] = "stg7_aji_46";
__declspec(section ".rodata") const char aji_17_str_00003F94[8] = "S_kurai";
__declspec(section ".rodata") const char aji_17_str_00003F9C[24] = "SFX_VOICE_MARIO_FIND1\0\0";
__declspec(section ".rodata") const char aji_17_str_00003FB4[8] = "eff0\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00003FBC[8] = "eff1\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00003FC4[24] = "SFX_PEACH_TEC_ACTIVE1\0\0";
__declspec(section ".rodata") const char aji_17_str_00003FDC[8] = "kika_1\0";
__declspec(section ".rodata") const char str_00003FE4[8] = "kika_2\0";
__declspec(section ".rodata") const char aji_17_str_00003FEC[8] = "kika_3\0";
__declspec(section ".rodata") const char aji_17_str_00003FF4[24] = "SFX_STG7_TEC_ACTIVE1\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000400C[8] = "moni_1\0";
__declspec(section ".rodata") const char aji_17_str_00004014[12] = "S_kikai_0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004020[8] = "moza\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004028[12] = "stg7_aji_47";
__declspec(section ".rodata") const char aji_17_str_00004034[12] = "stg7_aji_48";
__declspec(section ".rodata") const char aji_17_str_00004040[24] = "SFX_STG7_TEC_SANDSTORM1";
__declspec(section ".rodata") const char aji_17_str_00004058[8] = "M_I_2\0\0";
__declspec(section ".rodata") const char aji_17_str_00004060[12] = "stg7_aji_49";
__declspec(section ".rodata") const char aji_17_str_0000406C[8] = "M_S_1\0\0";
__declspec(section ".rodata") const char aji_17_str_00004074[12] = "stg7_aji_50";
__declspec(section ".rodata") const char aji_17_str_00004080[12] = "stg7_aji_51";
__declspec(section ".rodata") const char aji_17_str_0000408C[12] = "stg7_aji_52";
__declspec(section ".rodata") const char aji_17_str_00004098[12] = "stg7_aji_53";
__declspec(section ".rodata") const char str_000040A4[12] = "stg7_aji_54";
__declspec(section ".rodata") const char aji_17_str_000040B0[8] = "M_I_N\0\0";
__declspec(section ".rodata") const char aji_17_str_000040B8[12] = "stg7_aji_55";
__declspec(section ".rodata") const char aji_17_str_000040C4[12] = "stg7_aji_56";
__declspec(section ".rodata") const char aji_17_str_000040D0[12] = "stg7_aji_57";
__declspec(section ".rodata") const char aji_17_str_000040DC[8] = "aji_16\0";
__declspec(section ".rodata") const char aji_17_str_000040E4[8] = "peach\0\0";
__declspec(section ".rodata") const char aji_17_str_000040EC[12] = "stg7_aji_59";
__declspec(section ".rodata") const char aji_17_str_000040F8[12] = "stg7_aji_60";
__declspec(section ".rodata") const char aji_17_str_00004104[24] = "SFX_STG7_TEC_SHUTDOWN1\0";
__declspec(section ".rodata") const char aji_17_str_0000411C[12] = "stg7_aji_61";
__declspec(section ".rodata") const char aji_17_str_00004128[12] = "stg7_aji_62";
__declspec(section ".rodata") const char aji_17_str_00004134[24] = "SFX_VOICE_MARIO_NOD1_4\0";
__declspec(section ".rodata") const char aji_17_str_0000414C[8] = "M_N_2\0\0";
__declspec(section ".rodata") const char aji_17_str_00004154[24] = "SFX_PEACH_MAIL_SOUSIN1\0";
__declspec(section ".rodata") const char aji_17_str_0000416C[24] = "SFX_PEACH_MAIL_SOUSIN2\0";
__declspec(section ".rodata") const char aji_17_str_00004184[16] = "ENV_STG7_AJI4\0\0";
__declspec(section ".rodata") const char aji_17_str_00004194[32] = "SFX_VOICE_PEACH_SURPRISED1_3\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000041B4[8] = "P_S_4\0\0";
__declspec(section ".rodata") const char aji_17_str_000041BC[8] = "S_kikai";
__declspec(section ".rodata") const char aji_17_str_000041C4[16] = "peach_aji_42\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000041D4[8] = "mario\0\0";
__declspec(section ".rodata") const char aji_17_str_000041DC[8] = "P_T_4\0\0";
__declspec(section ".rodata") const char aji_17_str_000041E4[16] = "peach_aji_43\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000041F4[8] = "ren1\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000041FC[16] = "peach_aji_44\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000420C[8] = "P_S_1R\0";
__declspec(section ".rodata") const char aji_17_str_00004214[8] = "P_T_1R\0";
__declspec(section ".rodata") const char aji_17_str_0000421C[16] = "peach_aji_45\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000422C[16] = "peach_aji_48\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000423C[16] = "peach_aji_49\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000424C[16] = "peach_aji_50\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000425C[16] = "peach_aji_52\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000426C[16] = "peach_aji_53\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000427C[32] = "SFX_VOICE_PEACH_SURPRISED1_2\0\0\0";
__declspec(section ".rodata") const u32 zero_aji_00015114[1] = {0x00000000};
__declspec(section ".rodata") const char aji_17_str_000042A0[8] = "P_B_2\0\0";
__declspec(section ".rodata") const char aji_17_str_000042A8[8] = "P_T_7\0\0";
__declspec(section ".rodata") const char str_000042B0[16] = "peach_aji_53_01";
__declspec(section ".rodata") const char aji_17_str_000042C0[16] = "peach_aji_54\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000042D0[8] = "P_S_1\0\0";
__declspec(section ".rodata") const char aji_17_str_000042D8[8] = "P_T_1\0\0";
__declspec(section ".rodata") const char aji_17_str_000042E0[16] = "peach_aji_55\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000042F0[16] = "peach_aji_56\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004300[16] = "peach_aji_57\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004310[16] = "peach_aji_58\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004320[8] = "P_P_1\0\0";
__declspec(section ".rodata") const char aji_17_str_00004328[8] = "P_T_9\0\0";
__declspec(section ".rodata") const char aji_17_str_00004330[16] = "peach_aji_58_01";
__declspec(section ".rodata") const char str_00004340[16] = "peach_aji_58_02";
__declspec(section ".rodata") const char aji_17_str_00004350[16] = "peach_aji_58_03";
__declspec(section ".rodata") const char aji_17_str_00004360[16] = "peach_aji_58_04";
__declspec(section ".rodata") const char aji_17_str_00004370[16] = "peach_aji_58_05";
__declspec(section ".rodata") const char aji_17_str_00004380[16] = "peach_aji_58_06";
__declspec(section ".rodata") const char aji_17_str_00004390[8] = "P_C_1\0\0";
__declspec(section ".rodata") const char aji_17_str_00004398[8] = "P_T_8\0\0";
__declspec(section ".rodata") const char aji_17_str_000043A0[16] = "peach_aji_58_07";
__declspec(section ".rodata") const char aji_17_str_000043B0[16] = "peach_aji_65\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000043C0[16] = "peach_aji_66\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000043D0[16] = "peach_aji_67\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000043E0[16] = "peach_aji_68\0\0\0";
__declspec(section ".rodata") const char str_000043F0[20] = "SFX_PEACH_KEYBOARD1";
__declspec(section ".rodata") const char aji_17_str_00004404[8] = "P_A_1R\0";
__declspec(section ".rodata") const char aji_17_str_0000440C[16] = "peach_aji_69\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000441C[8] = "S_meil\0";
__declspec(section ".rodata") const char aji_17_str_00004424[4] = "mel";
__declspec(section ".rodata") const char aji_17_str_00004428[16] = "peach_aji_70\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004438[16] = "peach_aji_71\0\0\0";
__declspec(section ".rodata") const char str_00004448[16] = "peach_aji_72\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004458[12] = "S_aji_17\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004464[8] = "kpa_00\0";
__declspec(section ".rodata") const u32 dat_aji_000152e4 = 0xFFFFFFFF;
__declspec(section ".rodata") const f32 vec3_aji_000152e8[3] = {0.0f, 0.0f, 20.0f};
__declspec(section ".rodata") const f32 vec3_aji_000152f4[3] = {0.0f, 1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_aji_00015300[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const char aji_17_str_00004494[12] = "\x83z\x83\x8d\x83O\x83\x89\x83\x80\0";
__declspec(section ".rodata") const char aji_17_str_000044A0[8] = "\x83_\x83~\x81[\0";
__declspec(section ".rodata") const char aji_17_str_000044A8[8] = "P_O_F_1";
__declspec(section ".rodata") const char aji_17_str_000044B0[8] = "P_O_F_2";
__declspec(section ".rodata") const char aji_17_str_000044B8[8] = "P_O_R_1";
__declspec(section ".rodata") const char aji_17_str_000044C0[8] = "P_O_R_2";
__declspec(section ".rodata") const char aji_17_str_000044C8[8] = "P_O_N_1";
__declspec(section ".rodata") const char aji_17_str_000044D0[8] = "P_O_N_2";
__declspec(section ".rodata") const char str_000044D8[20] = "dance_dt.step error";
__declspec(section ".rodata") const char aji_17_str_000044EC[24] = "SFX_PEACH_DANCE_TURN1\0\0";
__declspec(section ".rodata") const char aji_17_str_00004504[8] = "P_O_D_1";
__declspec(section ".rodata") const char aji_17_str_0000450C[8] = "btn_01\0";
__declspec(section ".rodata") const char aji_17_str_00004514[8] = "btn_02\0";
__declspec(section ".rodata") const char aji_17_str_0000451C[8] = "btn_03\0";
__declspec(section ".rodata") const char aji_17_str_00004524[12] = "\x83z\x83\x8d\x83O\x83\x89\x83\x80" "2";
__declspec(section ".rodata") const char aji_17_str_00004530[8] = "P_O_Z_1";
__declspec(section ".rodata") const char aji_17_str_00004538[12] = "P_O_Z_1R\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004544[8] = "P_O_S_1";
__declspec(section ".rodata") const char aji_17_str_0000454C[8] = "P_O_S_2";
__declspec(section ".rodata") const char aji_17_str_00004554[24] = "BGM_EVT_PEACH_WALTZ1\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000456C[20] = "SFX_PEACH_DANCE_NG1";
__declspec(section ".rodata") const char aji_17_str_00004580[24] = "SFX_PEACH_DANCE_APPEAR1";
__declspec(section ".rodata") const char aji_17_str_00004598[16] = "peach_aji_94\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000045A8[16] = "peach_aji_95\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000045B8[8] = "c_peach";
__declspec(section ".rodata") const char aji_17_str_000045C0[12] = "\x83s\x81[\x83`\x95P\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000045CC[12] = "c_peach_r\0\0";
__declspec(section ".rodata") const char aji_17_str_000045D8[16] = "peach_aji_76\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000045E8[16] = "peach_aji_76_01";
__declspec(section ".rodata") const char aji_17_str_000045F8[16] = "peach_aji_76_02";
__declspec(section ".rodata") const char aji_17_str_00004608[16] = "peach_aji_77\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004618[16] = "peach_aji_78\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004628[16] = "peach_aji_79\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004638[16] = "peach_aji_80\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004648[16] = "peach_aji_83\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004658[16] = "peach_aji_84\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004668[16] = "peach_aji_85\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004678[16] = "peach_aji_86\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004688[16] = "peach_aji_91\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004698[16] = "peach_aji_92\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000046A8[12] = "move_pos\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000046B4[16] = "peach_aji_93\0\0\0";
__declspec(section ".rodata") const char str_000046C4[16] = "peach_aji_96\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000046D4[16] = "peach_aji_97\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000046E4[16] = "peach_aji_98\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000046F4[16] = "peach_aji_99\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004704[16] = "peach_aji_100\0\0";
__declspec(section ".rodata") const char aji_17_str_00004714[8] = "P_S_7\0\0";
__declspec(section ".rodata") const char aji_17_str_0000471C[8] = "P_T_13\0";
__declspec(section ".rodata") const char aji_17_str_00004724[16] = "peach_aji_101\0\0";
__declspec(section ".rodata") const char aji_17_str_00004734[20] = "peach_aji_101_01\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004748[16] = "peach_aji_102\0\0";
__declspec(section ".rodata") const char aji_17_str_00004758[8] = "hei_00\0";
__declspec(section ".rodata") const char aji_17_str_00004760[16] = "peach_aji_115\0\0";
__declspec(section ".rodata") const char aji_17_str_00004770[16] = "peach_aji_116\0\0";
__declspec(section ".rodata") const char aji_17_str_00004780[16] = "peach_aji_117\0\0";
__declspec(section ".rodata") const char aji_17_str_00004790[16] = "peach_aji_118\0\0";
__declspec(section ".rodata") const char aji_17_str_000047A0[16] = "peach_aji_119\0\0";
__declspec(section ".rodata") const char aji_17_str_000047B0[20] = "peach_aji_119_01\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000047C4[20] = "peach_aji_119_02\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000047D8[16] = "peach_aji_120\0\0";
__declspec(section ".rodata") const char aji_17_str_000047E8[16] = "peach_aji_121\0\0";
__declspec(section ".rodata") const char aji_17_str_000047F8[8] = "P_G_1\0\0";
__declspec(section ".rodata") const char aji_17_str_00004800[8] = "P_G_10\0";
__declspec(section ".rodata") const char aji_17_str_00004808[16] = "peach_aji_122\0\0";
__declspec(section ".rodata") const char aji_17_str_00004818[8] = "P_E_1\0\0";
__declspec(section ".rodata") const char aji_17_str_00004820[8] = "P_E_2\0\0";
__declspec(section ".rodata") const char aji_17_str_00004828[16] = "peach_aji_123\0\0";
__declspec(section ".rodata") const char aji_17_str_00004838[16] = "peach_aji_124\0\0";
__declspec(section ".rodata") const char aji_17_str_00004848[16] = "peach_aji_125\0\0";
__declspec(section ".rodata") const char aji_17_str_00004858[16] = "peach_aji_156\0\0";
__declspec(section ".rodata") const char aji_17_str_00004868[16] = "peach_aji_157\0\0";
__declspec(section ".rodata") const char aji_17_str_00004878[20] = "peach_aji_157_01\0\0\0";
__declspec(section ".rodata") const char aji_17_str_0000488C[20] = "peach_aji_157_02\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000048A0[20] = "peach_aji_157_03\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000048B4[20] = "peach_aji_157_04\0\0\0";
__declspec(section ".rodata") const char aji_17_str_000048C8[16] = "peach_aji_158\0\0";
__declspec(section ".rodata") const char aji_17_str_000048D8[16] = "peach_aji_159\0\0";
__declspec(section ".rodata") const char aji_17_str_000048E8[16] = "peach_aji_160\0\0";
__declspec(section ".rodata") const char aji_17_str_000048F8[16] = "peach_aji_161\0\0";
__declspec(section ".rodata") const char aji_17_str_00004908[16] = "peach_aji_163\0\0";
__declspec(section ".rodata") const char aji_17_str_00004918[16] = "peach_aji_164\0\0";
__declspec(section ".rodata") const char aji_17_str_00004928[16] = "peach_aji_165\0\0";
__declspec(section ".rodata") const char aji_17_str_00004938[16] = "peach_aji_166\0\0";
__declspec(section ".rodata") const char aji_17_str_00004948[8] = "mri_01\0";
__declspec(section ".rodata") const char aji_17_str_00004950[16] = "peach_aji_174\0\0";
__declspec(section ".rodata") const char aji_17_str_00004960[16] = "peach_aji_175\0\0";
__declspec(section ".rodata") const char aji_17_str_00004970[20] = "peach_aji_175_sel\0\0";
__declspec(section ".rodata") const char aji_17_str_00004984[16] = "peach_aji_178\0\0";
__declspec(section ".rodata") const char aji_17_str_00004994[16] = "peach_aji_179\0\0";
__declspec(section ".rodata") const char aji_17_str_000049A4[20] = "peach_aji_179_sel\0\0";
__declspec(section ".rodata") const char aji_17_str_000049B8[16] = "peach_aji_180\0\0";
__declspec(section ".rodata") const char aji_17_str_000049C8[16] = "peach_aji_181\0\0";
__declspec(section ".rodata") const char aji_17_str_000049D8[20] = "peach_aji_183_sel\0\0";
__declspec(section ".rodata") const char aji_17_str_000049EC[16] = "peach_aji_184\0\0";
__declspec(section ".rodata") const char aji_17_str_000049FC[16] = "peach_aji_185\0\0";
__declspec(section ".rodata") const char aji_17_str_00004A0C[20] = "peach_aji_185_sel\0\0";
__declspec(section ".rodata") const char aji_17_str_00004A20[16] = "peach_aji_186\0\0";
__declspec(section ".rodata") const char aji_17_str_00004A30[16] = "peach_aji_187\0\0";
__declspec(section ".rodata") const char aji_17_str_00004A40[20] = "peach_aji_187_sel\0\0";
__declspec(section ".rodata") const char aji_17_str_00004A54[20] = "peach_aji_166_01\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004A68[20] = "peach_aji_166_02\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004A7C[20] = "peach_aji_166_03\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004A90[20] = "peach_aji_166_04\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004AA4[20] = "peach_aji_166_05\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004AB8[20] = "peach_aji_166_06\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004ACC[20] = "peach_aji_166_07\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004AE0[20] = "peach_aji_166_08\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004AF4[16] = "peach_aji_167\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B04[16] = "peach_aji_168\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B14[16] = "peach_aji_169\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B24[20] = "peach_aji_181_01\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B38[16] = "peach_aji_182\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B48[16] = "peach_aji_183\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B58[16] = "peach_aji_190\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B68[16] = "peach_aji_188\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B78[20] = "peach_aji_190_01\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004B8C[20] = "peach_aji_190_02\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004BA0[16] = "peach_aji_192\0\0";
__declspec(section ".rodata") const char aji_17_str_00004BB0[16] = "peach_aji_193\0\0";
__declspec(section ".rodata") const char aji_17_str_00004BC0[16] = "peach_aji_194\0\0";
__declspec(section ".rodata") const char aji_17_str_00004BD0[16] = "peach_aji_195\0\0";
__declspec(section ".rodata") const char aji_17_str_00004BE0[8] = "gor_04\0";
__declspec(section ".rodata") const char aji_17_str_00004BE8[16] = "peach_aji_206\0\0";
__declspec(section ".rodata") const char aji_17_str_00004BF8[16] = "peach_aji_207\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C08[16] = "peach_aji_208\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C18[16] = "peach_aji_209\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C28[16] = "peach_aji_210\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C38[16] = "peach_aji_211\0\0";
__declspec(section ".rodata") const char str_00004C48[16] = "peach_aji_212\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C58[16] = "peach_aji_213\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C68[16] = "peach_aji_214\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C78[16] = "peach_aji_215\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C88[16] = "peach_aji_216\0\0";
__declspec(section ".rodata") const char aji_17_str_00004C98[16] = "peach_aji_217\0\0";
__declspec(section ".rodata") const char aji_17_str_00004CA8[16] = "peach_aji_260\0\0";
__declspec(section ".rodata") const char aji_17_str_00004CB8[16] = "peach_aji_261\0\0";
__declspec(section ".rodata") const char aji_17_str_00004CC8[16] = "peach_aji_262\0\0";
__declspec(section ".rodata") const char aji_17_str_00004CD8[16] = "peach_aji_263\0\0";
__declspec(section ".rodata") const char aji_17_str_00004CE8[16] = "peach_aji_264\0\0";
__declspec(section ".rodata") const char aji_17_str_00004CF8[16] = "peach_aji_265\0\0";
__declspec(section ".rodata") const char aji_17_str_00004D08[16] = "peach_aji_266\0\0";
__declspec(section ".rodata") const char aji_17_str_00004D18[16] = "peach_aji_267\0\0";
__declspec(section ".rodata") const char aji_17_str_00004D28[20] = "peach_aji_267_01\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004D3C[20] = "peach_aji_267_02\0\0\0";
__declspec(section ".rodata") const char str_00004D50[16] = "peach_aji_268\0\0";
__declspec(section ".rodata") const char aji_17_str_00004D60[8] = "usu_00\0";
__declspec(section ".rodata") const char aji_17_str_00004D68[16] = "peach_aji_282\0\0";
__declspec(section ".rodata") const char aji_17_str_00004D78[20] = "peach_aji_282_01\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004D8C[28] = "SFX_VOICE_PEACH_QUESTION1\0\0";
__declspec(section ".rodata") const char aji_17_str_00004DA8[20] = "peach_aji_282_02\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004DBC[20] = "peach_aji_282_03\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004DD0[20] = "peach_aji_282_04\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004DE4[16] = "peach_aji_283\0\0";
__declspec(section ".rodata") const char str_00004DF4[16] = "peach_aji_284\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E04[16] = "peach_aji_285\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E14[16] = "peach_aji_286\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E24[16] = "peach_aji_287\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E34[16] = "peach_aji_288\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E44[16] = "peach_aji_289\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E54[16] = "peach_aji_290\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E64[16] = "peach_aji_291\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E74[16] = "peach_aji_292\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E84[16] = "peach_aji_293\0\0";
__declspec(section ".rodata") const char aji_17_str_00004E94[16] = "peach_aji_294\0\0";
__declspec(section ".rodata") const char str_00004EA4[16] = "peach_aji_295\0\0";
__declspec(section ".rodata") const char aji_17_str_00004EB4[16] = "peach_aji_296\0\0";
__declspec(section ".rodata") const char aji_17_str_00004EC4[16] = "peach_aji_297\0\0";
__declspec(section ".rodata") const char aji_17_str_00004ED4[16] = "peach_aji_298\0\0";
__declspec(section ".rodata") const char aji_17_str_00004EE4[16] = "peach_aji_299\0\0";
__declspec(section ".rodata") const char aji_17_str_00004EF4[16] = "peach_aji_300\0\0";
__declspec(section ".rodata") const char aji_17_str_00004F04[16] = "peach_aji_301\0\0";
__declspec(section ".rodata") const char aji_17_str_00004F14[16] = "peach_aji_302\0\0";
__declspec(section ".rodata") const char aji_17_str_00004F24[8] = "\x8e\xe8\x89\xba\x82P\0";
__declspec(section ".rodata") const char aji_17_str_00004F2C[12] = "\x83V\x83\x85\x83\x8a\x83\x87\x81[\0";
__declspec(section ".rodata") const char aji_17_str_00004F38[8] = "\x8e\xe8\x89\xba\x82Q\0";
__declspec(section ".rodata") const char str_00004F40[16] = "peach_aji_303\0\0";
__declspec(section ".rodata") const char aji_17_str_00004F50[32] = "SFX_VOICE_PEACH_SURPRISED2_1\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00004F70[16] = "peach_aji_304\0\0";
__declspec(section ".rodata") const char aji_17_str_00004F80[24] = "BGM_EVT_STG8_3RDHEAD1\0\0";
__declspec(section ".rodata") const char aji_17_str_00004F98[16] = "peach_aji_305\0\0";
__declspec(section ".rodata") const char aji_17_str_00004FA8[16] = "peach_aji_306\0\0";
__declspec(section ".rodata") const char aji_17_str_00004FB8[16] = "peach_aji_307\0\0";
__declspec(section ".rodata") const char aji_17_str_00004FC8[16] = "peach_aji_308\0\0";
__declspec(section ".rodata") const char aji_17_str_00004FD8[16] = "peach_aji_309\0\0";
__declspec(section ".rodata") const char aji_17_str_00004FE8[16] = "peach_aji_310\0\0";
__declspec(section ".rodata") const char aji_17_str_00004FF8[16] = "peach_aji_311\0\0";
__declspec(section ".rodata") const char aji_17_str_00005008[16] = "peach_aji_312\0\0";
__declspec(section ".rodata") const char aji_17_str_00005018[8] = "S_sui2\0";
__declspec(section ".rodata") const char aji_17_str_00005020[8] = "S_sui3\0";
__declspec(section ".rodata") const char aji_17_str_00005028[24] = "SFX_PEACH_TEC_BUTTON1\0\0";
__declspec(section ".rodata") const char aji_17_str_00005040[16] = "peach_aji_313\0\0";
__declspec(section ".rodata") const char aji_17_str_00005050[16] = "peach_aji_314\0\0";
__declspec(section ".rodata") const char aji_17_str_00005060[16] = "peach_aji_315\0\0";
__declspec(section ".rodata") const char aji_17_str_00005070[12] = "monihiraku\0";
__declspec(section ".rodata") const char aji_17_str_0000507C[16] = "peach_aji_316\0\0";
__declspec(section ".rodata") const char aji_17_str_0000508C[16] = "peach_aji_317\0\0";
__declspec(section ".rodata") const char aji_17_str_0000509C[8] = "P_S_6\0\0";
__declspec(section ".rodata") const char aji_17_str_000050A4[8] = "P_T_6\0\0";
__declspec(section ".rodata") const char aji_17_str_000050AC[16] = "peach_aji_318\0\0";
__declspec(section ".rodata") const char aji_17_str_000050BC[16] = "peach_aji_319\0\0";
__declspec(section ".rodata") const char aji_17_str_000050CC[16] = "peach_aji_320\0\0";
__declspec(section ".rodata") const char aji_17_str_000050DC[16] = "peach_aji_321\0\0";
__declspec(section ".rodata") const char aji_17_str_000050EC[8] = "gor_01\0";
__declspec(section ".rodata") const char aji_17_str_000050F4[4] = "me\0";
__declspec(section ".rodata") const char aji_17_str_000050F8[16] = "stg7_aji_tec_00";
__declspec(section ".rodata") const char aji_17_str_00005108[16] = "stg7_aji_tec_01";
__declspec(section ".rodata") const char aji_17_str_00005118[12] = "S_camera_1\0";
__declspec(section ".rodata") const char aji_17_str_00005124[12] = "S_camera_2\0";
__declspec(section ".rodata") const char aji_17_str_00005130[24] = "polySurface1161_q00063\0";
__declspec(section ".rodata") const char aji_17_str_00005148[24] = "polySurface1168_q00065\0";
__declspec(section ".rodata") const char aji_17_str_00005160[8] = "ren2\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00005168[16] = "BGM_STG7_DUN2\0\0";
__declspec(section ".rodata") const char aji_17_str_00005178[12] = "keyboard\0\0\0";
__declspec(section ".rodata") const char aji_17_str_00005184[4] = "R\0\0";
__declspec(section ".rodata") const f32 zero_aji_00016000 = 0.0f;
__declspec(section ".rodata") const f32 float_5p5_aji_00016004 = 5.5f;
__declspec(section ".rodata") const f32 float_neg80_aji_00016008 = -80.0f;
__declspec(section ".rodata") const f32 float_neg0p47124_aji_0001600c = -0.4712389f;
__declspec(section ".rodata") const f32 float_6p2832_aji_00016010 = 6.2831855f;
__declspec(section ".rodata") const f32 float_1000_aji_00016014 = 1000.0f;
__declspec(section ".rodata") const f32 float_90_aji_00016018 = 90.0f;
__declspec(section ".rodata") const f32 float_270_aji_0001601c = 270.0f;
__declspec(section ".rodata") const f32 float_608_aji_00016020 = 608.0f;
__declspec(section ".rodata") const f32 float_480_aji_00016024 = 480.0f;
__declspec(section ".rodata") const f32 float_1_aji_00016028 = 1.0f;
__declspec(section ".rodata") const f32 float_28_aji_0001602c = 28.0f;
__declspec(section ".rodata") const f32 float_neg14_aji_00016030 = -14.0f;
__declspec(section ".rodata") const f32 float_14_aji_00016034 = 14.0f;
__declspec(section ".rodata") const f32 float_100_aji_00016038 = 100.0f;
__declspec(section ".rodata") const f32 float_180_aji_0001603c = 180.0f;
__declspec(section ".rodata") const f32 float_deg2rad_aji_00016040 = 0.017453292f;
__declspec(section ".rodata") const f32 float_neg28_aji_00016044 = -28.0f;
__declspec(section ".rodata") const f32 float_55_aji_00016048 = 55.0f;
__declspec(section ".rodata") const f32 float_1100_aji_0001604c = 1100.0f;
__declspec(section ".rodata") const f32 float_9p5_aji_00016050 = 9.5f;
__declspec(section ".rodata") const f32 float_7p5_aji_00016054 = 7.5f;
#endif
