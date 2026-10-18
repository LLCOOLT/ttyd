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
#undef EXT_LIT
#define EXT_LIT(sym, val) (val)
extern const char zero_rsh_000145bc[];
extern const char str_00004B20[];
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
extern const char str_00004334[];
extern const char str_0000433C[];
extern const char str_00004344[];
extern const char str_0000434C[];
extern const char str_00004354[];
extern const char str_0000435C[];
extern const char str_00004364[];
extern const char str_0000436C[];
extern const char str_00004374[];
extern const char str_0000437C[];
extern const char str_00004384[];
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
extern const char str_000043F4[];
extern const char str_00004400[];
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
extern const char str_00004488[];
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
extern const char str_000045BC[];
extern const char str_000045D8[];
extern const char str_000045E0[];
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
extern const char str_0000465C[];
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
extern const char str_0000470C[];
extern const char str_00004718[];
extern const char str_00004724[];
extern const char str_00004730[];
extern const char str_00004738[];
extern const char str_00004740[];
extern const char str_0000474C[];
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
extern const char str_0000483C[];
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
extern const char str_00004980[];
extern const char str_00004990[];
extern const char str_000049A0[];
extern const char str_000049B0[];
extern const char str_000049C0[];
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
extern const char str_00004334[];
extern const char str_0000433C[];
extern const char str_00004344[];
extern const char str_0000434C[];
extern const char str_00004354[];
extern const char str_0000435C[];
extern const char str_00004364[];
extern const char str_0000436C[];
extern const char str_00004374[];
extern const char str_0000437C[];
extern const char str_00004384[];
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
extern const char str_000043F4[];
extern const char str_00004400[];
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
extern const char str_00004488[];
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
extern const char str_000045BC[];
extern const char str_000045D8[];
extern const char str_000045E0[];
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
extern const char str_0000465C[];
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
extern const char str_0000470C[];
extern const char str_00004718[];
extern const char str_00004724[];
extern const char str_00004730[];
extern const char str_00004738[];
extern const char str_00004740[];
extern const char str_0000474C[];
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
extern const char str_0000483C[];
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
extern const char str_00004980[];
extern const char str_00004990[];
extern const char str_000049A0[];
extern const char str_000049B0[];
extern const char str_000049C0[];
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)
#pragma force_active on
#pragma force_active reset
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
extern const char str_00004334[];
extern const char str_0000433C[];
extern const char str_00004344[];
extern const char str_0000434C[];
extern const char str_00004354[];
extern const char str_0000435C[];
extern const char str_00004364[];
extern const char str_0000436C[];
extern const char str_00004374[];
extern const char str_0000437C[];
extern const char str_00004384[];
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
extern const char str_000043F4[];
extern const char str_00004400[];
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
extern const char str_00004488[];
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
extern const char str_000045BC[];
extern const char str_000045D8[];
extern const char str_000045E0[];
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
extern const char str_0000465C[];
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
extern const char str_0000470C[];
extern const char str_00004718[];
extern const char str_00004724[];
extern const char str_00004730[];
extern const char str_00004738[];
extern const char str_00004740[];
extern const char str_0000474C[];
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
extern const char str_0000483C[];
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
extern const char str_00004980[];
extern const char str_00004990[];
extern const char str_000049A0[];
extern const char str_000049B0[];
extern const char str_000049C0[];

typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; f32 field_0x14; f32 field_0x18; f32 field_0x1c; } ExtPose;
typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
typedef struct Moamoa { u16 flags; s16 state; s16 timer; u8 field_0x6[2]; Vec target; f32 vy; s16 jumpTimer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[2]; f32 lastX; f32 lastZ; Vec jitter; s16 pose; u8 field_0x3e[2]; OSTime startTime; s16 group; s16 order; u8 kind; u8 field_0x4d[3]; } Moamoa;
typedef struct MoamoaWork { u16 flags; u8 field_0x2[2]; s32 count; Moamoa* moa; MapObject* mobj; f32 mobjY; Vec target[3]; s16 hitCount; s16 field_0x3a[2]; s16 field_0x3e; s16 field_0x40; s16 idleFrames; void* escapeEvt; s32 animPoseId; s32 numDefs; MoamoaPoseDef defs[32]; f32 angle; f32 dist; s32 bounceCount; f32 breathDir; f32 breathDist; Vec breathPos; s16 chainNum[128]; s16 chainIdx[128][2]; } MoamoaWork;
typedef struct MoamoaData { const char* model; const char* anim; f32 speed; } MoamoaData;
static s32 bss_pad;
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
static inline f32 moa_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } return a; }
static inline f32 moa_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; } return a; }
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
        if (!strncmp(anim, (char*)str_00004B20, 1)) {
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
}
#endif
#ifdef NONMATCHING
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim) {
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
    MoamoaPoseDef* def = wp->defs;
    s32 i;

    if (moa->flags & 0x800) {
        model = group_tbl[moa->kind][0];
        if (moa->kind >= 2) {
            anim = group_tbl[moa->kind][1];
        }
        if (moa->kind == 10) {
            anim = (char*)str_000048C4;
        }
    }
    for (i = 0; i < wp->numDefs; i++, def++) {
        if (!strcmp(def->model, model) && !strcmp(def->anim, anim)) {
            break;
        }
    }
    if (i < wp->numDefs && moa->pose != i) {
        if (moa->flags & 4) {
            if (strncmp(anim, (char*)str_00004A40, 1)) {
                return;
            }
        }
        if (moa->flags & 0x10) {
            if (strncmp(anim, (char*)str_00004A44, 1)) {
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
        pose->field_0x14 = zero_rsh_00014490[0];
        pose->field_0x1c = zero_rsh_00014490[0];
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
        moamoa_pose_change(moa, (char*)str_000041D0, (char*)str_000041DC);
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
        moamoa_pose_change(moa, (char*)str_000041D0, (char*)str_000041DC);
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
        moamoa_pose_change(moa, (char*)str_000041D0, (char*)str_000041DC);
    }
    return EVT_RETURN_DONE;
}
#endif
#ifdef NONMATCHING
void evalOn(void) {
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
    f32 r = rand() / float_32767_rsh_000144ec[0];

    return r * (max - min) + min;
}
#endif
#ifdef NONMATCHING
static void ext_moamoa_init(void) {
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
}
#endif
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
        offscreenAddBoundingBox(offscreenNameToId((char*)str_00004B00), left, top, right, bottom);
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
        offscreenAddBoundingBox(offscreenNameToId((char*)str_00004B00), left, top, right, bottom);
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
static void ext_moamoa_main(void) {
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
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset
#ifdef NONMATCHING
static void ext_moamoa_dispent(void) {
    if (wp->flags & 1) {
        dispEntry(CAMERA_3D, zero_rsh_00014490[0], 1, ext_disp, NULL);
        dispEntry(CAMERA_3D, zero_rsh_00014490[0], 2, ext_shadow_disp, NULL);
    }
    if (wp->flags & 2) {
        dispEntry(CAMERA_OFFSCREEN2, -5000.0f, 1, ext_disp, NULL);
        dispEntry(CAMERA_OFFSCREEN2, -5000.0f, 2, ext_shadow_disp, NULL);
    }
}
#endif
#ifdef NONMATCHING
void moamoa_joint_position(Moamoa* moa, Vec* out) {
    NpcEntry* npc = npcNameToPtr((char*)str_000047B4);
    AnimationPose* anim = animPoseGetAnimPosePtr(npc->poseId);
    f32 t;
    Vec* a = anim->worldPositions[0] + wp->chainIdx[moa->group][0];
    Vec* b = anim->worldPositions[0] + wp->chainIdx[moa->group][1];
    Vec tmp;

    t = (f32)moa->order / (f32)wp->chainNum[moa->group];
    PSVECScale(a, out, t);
    PSVECScale(b, &tmp, float_1_rsh_00014470[0] - t);
    PSVECAdd(out, &tmp, out);
}
#endif

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
static s32 sharinDt[] = {
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
    (s32)((char*)str_000043F4), 0, 0, -229998976, (s32)((char*)str_00004400), 0, 0, -229998976,
    0, 0, 0, 0,
};

static EVT_BEGIN(evt_sharin_main)
    SET_FLOAT_VALUE(LW(10), FLOAT(0.0f))
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
        IF_INT_GREATER(LW(10), FLOAT(360.0f))
            SUBTRACT_FLOAT(LW(10), FLOAT(360.0f))
        END_IF
        IF_INT_LESS(LW(10), FLOAT(0.0f))
            ADD_FLOAT(LW(10), FLOAT(360.0f))
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
    (s32)((char*)str_0000440C), 0, 0, -229979520, -229998976, (s32)((char*)str_00004414), 1, 1,
    -229983104, -229998976, (s32)((char*)str_0000441C), 0, 0, -229979520, -229998976, (s32)((char*)str_00004424),
    1, 1, -229983104, -229998976, (s32)((char*)str_0000442C), 0, 0, -229979520,
    -230001024, (s32)((char*)str_00004434), 1, 1, -229983104, -230001024, (s32)((char*)str_0000443C), 0,
    0, -229979520, -230001024, (s32)((char*)str_00004444), 1, 1, -229983104, -230001024,
    0, 0, 0, 0, 0,
};

static EVT_BEGIN(evt_clank_main)
    SET_FLOAT_VALUE(LW(10), FLOAT(0.0f))
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
        IF_INT_GREATER(LW(10), FLOAT(360.0f))
            SUBTRACT_FLOAT(LW(10), FLOAT(360.0f))
        END_IF
        IF_INT_LESS(LW(10), FLOAT(0.0f))
            ADD_FLOAT(LW(10), FLOAT(360.0f))
        END_IF
        SET_FLOAT_VALUE(LW(12), LW(10))
        MULTIPLY_FLOAT(LW(12), LW(4))
        CALL(evt_sub_get_sincos, LW(12), LW(13), LW(14))
        MULTIPLY_FLOAT(LW(13), LW(3))
        MULTIPLY_FLOAT(LW(14), LW(3))
        SUBTRACT_FLOAT(LW(14), LW(3))
        MULTIPLY_FLOAT(LW(14), FLOAT(-1.0f))
        CALL(evt_mapobj_trans, 1, LW(0), LW(14), LW(13), FLOAT(0.0f))
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
    SET_FLOAT_VALUE(LW(10), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(11), FLOAT(0.0f))
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
        CALL(evt_mapobj_trans, 1, STRING(((char*)str_0000444C)), LW(10), 0, 0)
        CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004454)), LW(10), 0, 0)
        CALL(evt_mapobj_trans, 1, STRING(((char*)str_0000445C)), LW(11), 0, 0)
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
    SET_FLOAT_VALUE(LW(10), FLOAT(0.0f))
    LOOP(0)
        SET_FLOAT_VALUE(LW(9), GW(0))
        DIVIDE_FLOAT(LW(9), FLOAT(30.0f))
        MULTIPLY_FLOAT(LW(9), FLOAT(57.29492f))
        ADD_FLOAT(LW(10), LW(9))
        IF_INT_GREATER(LW(10), FLOAT(360.0f))
            SUBTRACT_FLOAT(LW(10), FLOAT(360.0f))
        END_IF
        IF_INT_LESS(LW(10), FLOAT(0.0f))
            ADD_FLOAT(LW(10), FLOAT(360.0f))
        END_IF
        CALL(evt_mapobj_rotate, 0, STRING(((char*)str_00004464)), LW(10), 0, 0)
        CALL(evt_mapobj_rotate, 0, STRING(((char*)str_00004470)), LW(10), 0, 0)
        CALL(evt_mapobj_rotate, 0, STRING(((char*)str_0000447C)), LW(10), 0, 0)
        CALL(evt_mapobj_rotate, 0, STRING(((char*)str_00004488)), LW(10), 0, 0)
        CALL(evt_mapobj_rotate, 0, STRING(((char*)str_00004498)), LW(10), 0, 0)
        CALL(evt_mapobj_rotate, 0, STRING(((char*)str_000044A4)), LW(10), 0, 0)
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
    CALL(evt_mapobj_get_position, STRING(((char*)str_000044B4)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000044BC)), LW(0), LW(1), LW(2), 0)
    WAIT_MS(200)
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000044BC)), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044D4)))
        CALL(evt_snd_sfxon, STRING(((char*)str_000044DC)), 0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044F4)))
        IF_INT_LESS(GSW(0), 339)
            CALL(evt_snd_sfxon, STRING(((char*)str_000044FC)), 0)
            ELSE
            CALL(evt_snd_sfxon, STRING(((char*)str_00004514)), 0)
        END_IF
    END_IF
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00004530)))
        CALL(evt_snd_sfxon, STRING(((char*)str_00004538)), 0)
    END_IF
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044F4)))
        BEGIN_INLINE_EVENT
            SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
            LOOP(0)
                ADD_FLOAT(LW(0), GW(0))
                CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004550)), LW(0), 0, 0)
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044D4)))
        BEGIN_INLINE_EVENT
            SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
            LOOP(0)
                ADD_FLOAT(LW(0), GW(0))
                CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004550)), LW(0), 0, 0)
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
        CALL(evt_sub_intpl_msec_init, 11, 0, -1500, 20000)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
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
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(1), GW(0))
        ADD_FLOAT(GW(1), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
        CALL(evt_sub_intpl_msec_init, 11, -1000, 0, 1000)
        LABEL(2)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
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
    CALL(evt_mapobj_get_position, STRING(((char*)str_000044B4)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000044BC)), LW(0), LW(1), LW(2), 0)
    WAIT_MS(200)
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000044BC)), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044D4)))
        CALL(evt_snd_sfxon, STRING(((char*)str_000044DC)), 0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044F4)))
        CALL(evt_snd_sfxon, STRING(((char*)str_00004558)), 0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00004530)))
        CALL(evt_snd_sfxon, STRING(((char*)str_00004538)), 0)
    END_IF
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044F4)))
        BEGIN_INLINE_EVENT
            SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
            LOOP(0)
                ADD_FLOAT(LW(0), GW(0))
                CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004550)), LW(0), 0, 0)
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044D4)))
        BEGIN_INLINE_EVENT
            SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
            LOOP(0)
                ADD_FLOAT(LW(0), GW(0))
                CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004550)), LW(0), 0, 0)
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00004530)))
        BEGIN_INLINE_EVENT
            SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
            LOOP(0)
                ADD_FLOAT(LW(0), GW(0))
                CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004550)), LW(0), 0, 0)
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
        CALL(evt_sub_intpl_msec_init, 11, 0, 1500, 20000)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(0), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        LOOP(0)
            SET_FLOAT_VALUE(GW(0), FLOAT(15.0f))
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
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(1), GW(0))
        ADD_FLOAT(GW(1), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
        CALL(evt_sub_intpl_msec_init, 11, 1000, 0, 1000)
        LABEL(2)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
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
    SET_FLOAT_VALUE(GW(0), FLOAT(15.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(15.0f))
    RETURN
EVT_END()

static EVT_BEGIN(stop_1)
    SET_VALUE(GSWF(3583), 1)
    SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(2), FLOAT(3000.0f))
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044D4)))
        CALL(evt_snd_sfxon, STRING(((char*)str_00004574)), 0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044F4)))
        CALL(evt_snd_sfxon, STRING(((char*)str_0000458C)), 0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00004530)))
        CALL(evt_snd_sfxon, STRING(((char*)str_000045A4)), 0)
    END_IF
    CALL(evt_sub_intpl_msec_init, 11, 3000, 0, 10000)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    MULTIPLY_FLOAT(LW(0), FLOAT(1.0f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004550)), LW(0), 0, 0)
    SUBTRACT_FLOAT(LW(2), LW(0))
    SET_FLOAT_VALUE(GW(0), LW(2))
    SET_FLOAT_VALUE(GW(1), LW(2))
    MULTIPLY_FLOAT(GW(0), FLOAT(-1.0f))
    MULTIPLY_FLOAT(GW(1), FLOAT(-1.0f))
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
    SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(2), FLOAT(-3000.0f))
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044D4)))
        CALL(evt_snd_sfxon, STRING(((char*)str_00004574)), 0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044F4)))
        CALL(evt_snd_sfxon, STRING(((char*)str_000045BC)), 0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00004530)))
        CALL(evt_snd_sfxon, STRING(((char*)str_000045A4)), 0)
    END_IF
    CALL(evt_sub_intpl_msec_init, 11, -3000, 0, 10000)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    MULTIPLY_FLOAT(LW(0), FLOAT(1.0f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004550)), LW(0), 0, 0)
    SUBTRACT_FLOAT(LW(2), LW(0))
    SET_FLOAT_VALUE(GW(0), LW(2))
    SET_FLOAT_VALUE(GW(1), LW(2))
    MULTIPLY_FLOAT(GW(0), FLOAT(-1.0f))
    MULTIPLY_FLOAT(GW(1), FLOAT(-1.0f))
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
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00004530)))
        SPAWN_EVENT(PTR(stop_1))
    END_IF
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044D4)))
        SPAWN_EVENT(PTR(stop_2))
    END_IF
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING(((char*)str_000044F4)))
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
        CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000044B4)), 0, 0, LW(10))
        CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000045D8)), 0, 0, LW(10))
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
    (s32)((char*)str_000045E0), (s32)((char*)str_000045EC), (s32)((char*)str_000045F8), (s32)((char*)str_00004604), (s32)((char*)str_00004610), (s32)((char*)str_00004618), (s32)((char*)str_00004620), (s32)((char*)str_00004628),
    (s32)((char*)str_00004630), (s32)((char*)str_00004638), (s32)((char*)str_00004644), (s32)((char*)str_00004650), (s32)((char*)str_0000465C), (s32)((char*)str_00004668), 0,
};

__declspec(section ".data") static s32 pika_tbl_rsh_06[] = {
    (s32)((char*)str_000045E0), (s32)((char*)str_000045EC), (s32)((char*)str_000045F8), (s32)((char*)str_00004604), (s32)((char*)str_00004610), (s32)((char*)str_00004618), (s32)((char*)str_00004620), (s32)((char*)str_00004628),
    (s32)((char*)str_00004630), 0,
};

static EVT_BEGIN(hom_10_evt_resha_sub)
    SET_VALUE(GSWF(3583), 0)
    SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(0.0f))
    SPAWN_EVENT(PTR(evt_sharin))
    SPAWN_EVENT(PTR(evt_clank))
    SET_VALUE(LF(0), 0)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00004674)))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_STR_EQUAL(LW(0), STRING(((char*)str_0000467C)))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00004684)))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_STR_EQUAL(LW(0), STRING(((char*)str_0000468C)))
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
    IF_STR_EQUAL(LW(0), STRING(((char*)str_0000468C)))
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
    IF_STR_NOT_EQUAL(LW(0), STRING(((char*)str_0000468C)))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00004698)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000046A0)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000046A8)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000046B4)), 1)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(hom_10_evt_resha_left)
    CALL_CHILD(PTR(hom_10_evt_resha_sub))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000046C0)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000046C8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000046D0)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000046DC)), 1)
    RETURN
EVT_END()

static EVT_BEGIN(hom_10_init_evt)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING(((char*)str_000046E8)))
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
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000046F8)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000046D0)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00004700)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_0000470C)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00004718)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000046DC)), 1)
        ELSE
        CALL_CHILD(PTR(hom_10_evt_resha_left))
        CALL_CHILD(PTR(hom_10_evt_resha_start4))
        SET_VALUE(LW(0), 0)
        SET_VALUE(LW(1), 1000)
        CALL(evt_mapobj_trans, 1, STRING(((char*)str_00004550)), -1500, 0, 0)
    END_IF
    CALL(evt_cam_letter_box_onoff, 1, 1)
    CALL(evt_cam3d_evt_set, LW(0), 300, 1400, LW(0), 125, 0, 0, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_seq_wait, 2)
        CALL(evt_cam3d_evt_set, LW(1), 300, 1400, LW(1), 125, 0, 8000, 0)
        WAIT_MS(4000)
        CALL(evt_bero_mapchange, STRING(((char*)str_00004724)), STRING(((char*)str_00004730)))
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
    (s32)((char*)str_00004738), 8, 2, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)str_00004740), (s32)((char*)str_00004738), 65537, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static EVT_BEGIN(evt_moamoa_init)
    CALL(evt_npc_entry, STRING(((char*)str_0000474C)), STRING(((char*)str_000041D0)))
    CALL(evt_npc_entry, STRING(((char*)str_00004754)), STRING(((char*)str_000041E4)))
    CALL(evt_npc_set_position, STRING(((char*)str_0000474C)), 0, -1000, 0)
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
    CALL(evt_msg_print, 0, STRING(((char*)str_000047C8)), 0, 0)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000047D8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000047E4)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000047F0)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000047FC)), 1)
    CALL(evt_npc_set_position, STRING(((char*)str_000047B4)), 10, 190, 0)
    CALL(evt_npc_pera_onoff, STRING(((char*)str_000047B4)), 0)
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_00004804)))
    CALL(evt_snd_sfxoff, GW(2))
    CALL(evt_snd_sfxon, STRING(((char*)str_00004808)), GW(2))
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004824)), LW(0), LW(1), LW(2), 0)
        CALL(evt_eff_fukidashi, 0, STRING(((char*)str_0000483C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
        CALL(evt_eff_fukidashi, 3, STRING(((char*)str_00004844)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(1000)
        CALL(evt_mario_set_dir, 90, 200, 0)
        CALL(evt_party_set_dir, 0, 90, 200)
        WAIT_MS(300)
        CALL(evt_cam3d_evt_set, 10, 349, 516, 10, 253, -25, 3000, 11)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(15)
            CALL(evt_snd_sfxon, STRING(((char*)str_0000484C)), 0)
            WAIT_MS(500)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_moamoa_fusion)
    CALL(evt_snd_sfxoff, GW(2))
    CALL(evt_snd_sfxon, STRING(((char*)str_0000479C)), GW(2))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00004868)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000047D8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000047E4)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000047F0)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000047FC)), 1)
    WAIT_MS(2000)
    CALL(evt_moamoa_kind_onoff, 1, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING(((char*)str_000047B4)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004874)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(800)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004874)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(800)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004874)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(800)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004874)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_0000488C)))
    CALL(npc_anim_wait)
    CALL(evt_cam3d_evt_set, 10, 335, 369, 10, 265, -25, 1000, 11)
    CALL(evt_moamoa_kind_onoff, 1, 1)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING(((char*)str_000047B4)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004890)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_0000420C)))
    WAIT_MS(2000)
    BEGIN_INLINE_EVENT
        WAIT_MS(1700)
        CALL(evt_npc_get_position, STRING(((char*)str_000047B4)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000048A8)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_cam3d_evt_set, 10, 300, 450, 10, 300, -25, 1000, 11)
    END_INLINE_EVENT
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_000048C0)))
    CALL(npc_anim_wait)
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_000048C4)))
    WAIT_MS(1000)
    CALL(evt_mario_set_pos, -160, 215, 0)
    CALL(evt_party_set_pos, 0, -200, 215, -10)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_set_dir, 0, 90, 0)
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_set_pose, STRING(((char*)str_000048C8)))
    CALL(evt_cam3d_evt_set, -180, 308, 270, -180, 255, -25, 0, 11)
    WAIT_MS(500)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING(((char*)str_000048D0)))
    WAIT_MS(300)
    CALL(evt_party_run, 0)
    CALL(evt_cam3d_evt_set, 10, 498, 467, 10, 410, -25, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_000048E0)), 0, 0)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_000048F0)), 0, 0)
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 1000, 20, 841, -50, 200, -66, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_cam3d_evt_set, -440, 230, 180, 5, 300, -36, 4000, 11)
    WAIT_MS(4000)
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING(((char*)str_000047B4)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004900)), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_00004918)))
    CALL(npc_anim_wait)
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_0000491C)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)str_00004920)), 0, 0)
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -100, 488, 1370, -100, 245, -8, 4000, 11)
    WAIT_MS(2000)
    CALL(evt_snd_sfxoff, GW(2))
    CALL(evt_npc_set_battle_info, STRING(((char*)str_000047B4)), 1)
    CALL(evt_npc_battle_start, STRING(((char*)str_000047B4)))
    CALL(evt_npc_wait_battle_end)
    CALL(evt_cam3d_evt_set, -50, 355, 534, -50, 260, -8, 0, 11)
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_00004804)))
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_mario_set_pose, STRING(((char*)str_00004930)))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), -25)
    CALL(evt_party_set_pos, 0, LW(0), LW(1), LW(2))
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
    CALL(evt_moamoa_kind_onoff, 0, 0)
    CALL(evt_msg_print, 0, STRING(((char*)str_00004938)), 0, STRING(((char*)str_000047B4)))
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING(((char*)str_000047B4)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004948)), LW(0), LW(1), LW(2), 0)
    CALL(evt_moamoa_blow)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set, -150, 485, 1469, -150, 225, -8, 4000, 11)
    WAIT_MS(4000)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_npc_reverse_ry, STRING(((char*)str_0000476C)))
            WAIT_MS(1500)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_npc_reverse_ry, STRING(((char*)str_00004794)))
            WAIT_MS(1000)
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(2000)
    SET_VALUE(GSW(0), 332)
    CALL(evt_bero_mapchange, STRING(((char*)str_00004964)), STRING(((char*)str_00004738)))
    RETURN
EVT_END()

__declspec(section ".data") s32 pose_name[] = {
    (s32)((char*)str_00004804), (s32)((char*)str_0000488C), (s32)((char*)str_000041DC), (s32)((char*)str_0000420C), (s32)((char*)str_000048C0), (s32)((char*)str_000048C4), (s32)((char*)str_00004918), (s32)((char*)str_0000491C),
};

EVT_BEGIN(moamoa_debug)
    CALL(evt_npc_entry, STRING(((char*)str_0000474C)), STRING(((char*)str_000041D0)))
    CALL(evt_npc_entry, STRING(((char*)str_00004754)), STRING(((char*)str_000041E4)))
    CALL(evt_npc_set_position, STRING(((char*)str_0000474C)), 0, -1000, 0)
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
    CALL(evt_ext_entry, 700, PTR(ext_moamoa_data), PTR(ext_moamoa_init), PTR(ext_moamoa_main), PTR(ext_moamoa_dispent))
    CALL(evt_moamoa_flag_onoff, 1, 1)
    CALL(evt_moamoa_flag_onoff, 1, 4)
    CALL(evt_moamoa_fusion_debug)
    CALL(evt_npc_set_position, STRING(((char*)str_000047B4)), 10, 190, 0)
    CALL(evt_npc_pera_onoff, STRING(((char*)str_000047B4)), 0)
    CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), STRING(((char*)str_000048C4)))
    CALL(evt_npc_set_scale, STRING(((char*)str_000047B4)), FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
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
                CALL(evt_npc_set_anim, STRING(((char*)str_000047B4)), LW(2))
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
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004970)))
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004980)))
        CASE_BETWEEN(304, 309)
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004970)))
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004980)))
        CASE_BETWEEN(310, 325)
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004990)))
        CALL(evt_snd_envoff, 512)
        CALL(evt_snd_bgmoff, 26624)
        CASE_BETWEEN(327, 328)
        CALL(evt_snd_bgmoff, 512)
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004980)))
        CASE_BETWEEN(329, 331)
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_000049A0)))
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004980)))
        CASE_BETWEEN(334, 344)
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_000049B0)))
        CALL(evt_snd_envoff, 512)
        CALL(evt_snd_bgmoff, 26624)
        CASE_DEFAULT
        CALL(evt_snd_bgmoff, 512)
        CALL(evt_snd_envon, 272, STRING(((char*)str_000046E8)))
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
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_000049B0)))
        CALL(evt_snd_envoff, 512)
        CALL(evt_snd_bgmoff, 26624)
        ELSE
        IF_INT_EQUAL(GSWF(3461), 1)
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_000049C0)))
            CALL(evt_snd_envoff, 512)
            CALL(evt_snd_bgmoff, 26624)
            ELSE
            CALL(evt_snd_bgmoff, 512)
            CALL(evt_snd_envon, 272, STRING(((char*)str_000046E8)))
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




#ifdef NONMATCHING
static s32 ramp_r(EventEntry* event, BOOL isFirstCall) {
    f32 amp = __fabsf(evtGetFloat(event, GW(0)));
    f32 wave = sin(gp->retraceCount / float_15_rsh_00014474[0]);

    evtSetFloat(event, LW(10), float_1p8_rsh_00014478[0] * amp * wave);
    return EVT_RETURN_DONE;
}
#endif
#ifdef NONMATCHING
static void resha_tev(MapTevCallbackInfo* info) {
    envAddTev(7, info);
}
#endif
#ifdef NONMATCHING
s32 npc_anim_wait(EventEntry* event, BOOL isFirstCall) {
    NpcEntry* npc = npcNameToPtr((char*)str_000047B4);

    if (animPoseGetLoopTimes(npc->poseId) >= float_1_rsh_00014470[0]) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
#endif

void __cvt_ull_flt();
void __div2u();
#ifndef NONMATCHING
// FAKE (asm stopgap, asmfake.py --whole): moamoa_pose_init (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
void jt_00009330(void);
void jt_00009E38(void);
void jt_0000A130(void);
void jt_0000A394(void);
void jt_0000A5F0(void);
void jt_0000B1A0(void);
void jt_000095DC(void);
void jt_00009608(void);
void jt_0000A614(void);
void jt_0000A918(void);
void jt_0000A978(void);
void jt_0000ACC8(void);
void jt_0000AD58(void);
void jt_00009BA0(void);
void jt_00009BCC(void);
void jt_00009C94(void);
void jt_00009A9C(void);
void jt_0000ADFC(void);
void jt_0000AE24(void);
void jt_0000B0B0(void);
void jt_0000B0D4(void);
__declspec(section ".data") void* jumptable_000183EC[66] = {jt_00009330, jt_00009E38, jt_0000A130, jt_0000A394, jt_0000A5F0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_000095DC, jt_00009608, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000A614, jt_0000A614, jt_0000A614, jt_0000A918, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000A978, jt_0000ACC8, jt_0000AD58, jt_00009BA0, jt_00009BCC, jt_00009C94, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_0000B1A0, jt_00009A9C, jt_0000ADFC, jt_0000AE24, jt_0000B0B0, jt_0000B0D4};
#pragma force_active on
__declspec(section ".rodata") const char str_000041D0[] = "c_n_moa_a\000\000";
__declspec(section ".rodata") const char str_000041DC[] = "S_1";
__declspec(section ".rodata") const char str_000041E0[] = "D_1";
__declspec(section ".rodata") const char str_000041E4[] = "c_n_moa_b\000\000";
__declspec(section ".rodata") const char str_000041F0[] = "c_kinodebu\000";
__declspec(section ".rodata") const char str_000041FC[] = "G_1";
__declspec(section ".rodata") const char str_00004200[] = "c_puku_c\000\000\000";
__declspec(section ".rodata") const char str_0000420C[] = "U_1";
__declspec(section ".rodata") const char str_00004210[] = "c_powan";
__declspec(section ".rodata") const char str_00004218[] = "O_1";
__declspec(section ".rodata") const char str_0000421C[] = "c_smoko";
__declspec(section ".rodata") const char str_00004224[] = "T_2";
__declspec(section ".rodata") const char str_00004228[] = "c_rose\000";
__declspec(section ".rodata") const char str_00004230[] = "c_papab";
__declspec(section ".rodata") const char str_00004238[] = "c_mamab";
__declspec(section ".rodata") const char str_00004240[] = "c_konari\000\000\000";
__declspec(section ".rodata") const f32 vec3_rsh_00013cec[3] = { 0.0f, -1000.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013cf8[3] = { 10.0f, 215.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013d04[3] = { 10.0f, 215.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013d10[3] = { 10.0f, 215.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013d1c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013d28[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013d34[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013d40[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013d4c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013d58[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013d64[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013d70[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013d7c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013d88[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013d94[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013da0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const char str_0000430C[] = "sha_1_1";
__declspec(section ".rodata") const char str_00004314[] = "sha_1_2";
__declspec(section ".rodata") const char str_0000431C[] = "sha_1_3";
__declspec(section ".rodata") const char str_00004324[] = "sha_1_4";
__declspec(section ".rodata") const char str_0000432C[] = "sha_1_5";
__declspec(section ".rodata") const char str_00004334[] = "sha_2_1";
__declspec(section ".rodata") const char str_0000433C[] = "sha_2_2";
__declspec(section ".rodata") const char str_00004344[] = "sha_2_3";
__declspec(section ".rodata") const char str_0000434C[] = "sha_3_1";
__declspec(section ".rodata") const char str_00004354[] = "sha_3_2";
__declspec(section ".rodata") const char str_0000435C[] = "sha_3_3";
__declspec(section ".rodata") const char str_00004364[] = "sha_4_1";
__declspec(section ".rodata") const char str_0000436C[] = "sha_4_2";
__declspec(section ".rodata") const char str_00004374[] = "sha_4_3";
__declspec(section ".rodata") const char str_0000437C[] = "sha_5_1";
__declspec(section ".rodata") const char str_00004384[] = "sha_5_2";
__declspec(section ".rodata") const char str_0000438C[] = "sha_5_3";
__declspec(section ".rodata") const char str_00004394[] = "sha_6_1";
__declspec(section ".rodata") const char str_0000439C[] = "sha_6_2";
__declspec(section ".rodata") const char str_000043A4[] = "sha_6_3";
__declspec(section ".rodata") const char str_000043AC[] = "sha_1_1_c\000\000";
__declspec(section ".rodata") const char str_000043B8[] = "sha_1_2_c\000\000";
__declspec(section ".rodata") const char str_000043C4[] = "sha_1_3_c\000\000";
__declspec(section ".rodata") const char str_000043D0[] = "sha_1_4_c\000\000";
__declspec(section ".rodata") const char str_000043DC[] = "sha_1_5_c\000\000";
__declspec(section ".rodata") const char str_000043E8[] = "sha_6_1_c\000\000";
__declspec(section ".rodata") const char str_000043F4[] = "sha_6_2_c\000\000";
__declspec(section ".rodata") const char str_00004400[] = "sha_6_3_c\000\000";
__declspec(section ".rodata") const char str_0000440C[] = "bou_1\000\000";
__declspec(section ".rodata") const char str_00004414[] = "bou_2\000\000";
__declspec(section ".rodata") const char str_0000441C[] = "bou_3\000\000";
__declspec(section ".rodata") const char str_00004424[] = "bou_4\000\000";
__declspec(section ".rodata") const char str_0000442C[] = "bou_1_c";
__declspec(section ".rodata") const char str_00004434[] = "bou_2_c";
__declspec(section ".rodata") const char str_0000443C[] = "bou_3_c";
__declspec(section ".rodata") const char str_00004444[] = "bou_4_c";
__declspec(section ".rodata") const char str_0000444C[] = "jimen\000\000";
__declspec(section ".rodata") const char str_00004454[] = "yama\000\000\000";
__declspec(section ".rodata") const char str_0000445C[] = "iwayama";
__declspec(section ".rodata") const char str_00004464[] = "hosi_right\000";
__declspec(section ".rodata") const char str_00004470[] = "hosi_left\000\000";
__declspec(section ".rodata") const char str_0000447C[] = "hosi_center";
__declspec(section ".rodata") const char str_00004488[] = "hosi_right_c\000\000\000";
__declspec(section ".rodata") const char str_00004498[] = "hosi_left_c";
__declspec(section ".rodata") const char str_000044A4[] = "hosi_center_c\000\000";
__declspec(section ".rodata") const char str_000044B4[] = "ranpu\000\000";
__declspec(section ".rodata") const char str_000044BC[] = "SFX_STG6_TRAIN_BELL1\000\000\000";
__declspec(section ".rodata") const char str_000044D4[] = "gor_04\000";
__declspec(section ".rodata") const char str_000044DC[] = "SFX_STG6_TRAIN_MOVE1\000\000\000";
__declspec(section ".rodata") const char str_000044F4[] = "hom_00\000";
__declspec(section ".rodata") const char str_000044FC[] = "SFX_STG6_TRAIN_MOVE1_2\000";
__declspec(section ".rodata") const char str_00004514[] = "SFX_STG6_TRAIN_MOVE1_2_2\000\000\000";
__declspec(section ".rodata") const char str_00004530[] = "pik_00\000";
__declspec(section ".rodata") const char str_00004538[] = "SFX_STG6_TRAIN_MOVE1_3\000";
__declspec(section ".rodata") const char str_00004550[] = "train\000\000";
__declspec(section ".rodata") const char str_00004558[] = "SFX_STG6_TRAIN_MOVE1_2_3\000\000\000";
__declspec(section ".rodata") const char str_00004574[] = "SFX_STG6_TRAIN_MOVE2\000\000\000";
__declspec(section ".rodata") const char str_0000458C[] = "SFX_STG6_TRAIN_MOVE2_2\000";
__declspec(section ".rodata") const char str_000045A4[] = "SFX_STG6_TRAIN_MOVE2_3\000";
__declspec(section ".rodata") const char str_000045BC[] = "SFX_STG6_TRAIN_MOVE2_2_2\000\000\000";
__declspec(section ".rodata") const char str_000045D8[] = "ranpu_c";
__declspec(section ".rodata") const char str_000045E0[] = "pika_1_1\000\000\000";
__declspec(section ".rodata") const char str_000045EC[] = "pika_1_2\000\000\000";
__declspec(section ".rodata") const char str_000045F8[] = "pika_1_3\000\000\000";
__declspec(section ".rodata") const char str_00004604[] = "pika_1_4\000\000\000";
__declspec(section ".rodata") const char str_00004610[] = "pika_2\000";
__declspec(section ".rodata") const char str_00004618[] = "pika_3\000";
__declspec(section ".rodata") const char str_00004620[] = "pika_4\000";
__declspec(section ".rodata") const char str_00004628[] = "pika_5\000";
__declspec(section ".rodata") const char str_00004630[] = "pika_6\000";
__declspec(section ".rodata") const char str_00004638[] = "pika_1_1_c\000";
__declspec(section ".rodata") const char str_00004644[] = "pika_1_2_c\000";
__declspec(section ".rodata") const char str_00004650[] = "pika_1_3_c\000";
__declspec(section ".rodata") const char str_0000465C[] = "pika_1_4_c\000";
__declspec(section ".rodata") const char str_00004668[] = "pika_6_c\000\000\000";
__declspec(section ".rodata") const char str_00004674[] = "hom_10\000";
__declspec(section ".rodata") const char str_0000467C[] = "hom_11\000";
__declspec(section ".rodata") const char str_00004684[] = "hom_12\000";
__declspec(section ".rodata") const char str_0000468C[] = "rsh_06_a\000\000\000";
__declspec(section ".rodata") const char str_00004698[] = "train_7";
__declspec(section ".rodata") const char str_000046A0[] = "train_8";
__declspec(section ".rodata") const char str_000046A8[] = "renketu_6\000\000";
__declspec(section ".rodata") const char str_000046B4[] = "renketu_7\000\000";
__declspec(section ".rodata") const char str_000046C0[] = "train_1";
__declspec(section ".rodata") const char str_000046C8[] = "train_6";
__declspec(section ".rodata") const char str_000046D0[] = "renketu_1\000\000";
__declspec(section ".rodata") const char str_000046DC[] = "renketu_5\000\000";
__declspec(section ".rodata") const char str_000046E8[] = "ENV_STG6_RSH2\000\000";
__declspec(section ".rodata") const char str_000046F8[] = "renketu";
__declspec(section ".rodata") const char str_00004700[] = "renketu_2\000\000";
__declspec(section ".rodata") const char str_0000470C[] = "renketu_3\000\000";
__declspec(section ".rodata") const char str_00004718[] = "renketu_4\000\000";
__declspec(section ".rodata") const char str_00004724[] = "rsh_02_a\000\000\000";
__declspec(section ".rodata") const char str_00004730[] = "nidome\000";
__declspec(section ".rodata") const char str_00004738[] = "w_bero\000";
__declspec(section ".rodata") const char str_00004740[] = "rsh_05_a\000\000\000";
__declspec(section ".rodata") const char str_0000474C[] = "moa_a\000\000";
__declspec(section ".rodata") const char str_00004754[] = "moa_b\000\000";
__declspec(section ".rodata") const char str_0000475C[] = "kinopio";
__declspec(section ".rodata") const char str_00004764[] = "cook\000\000\000";
__declspec(section ".rodata") const char str_0000476C[] = "powan\000\000";
__declspec(section ".rodata") const char str_00004774[] = "sarary\000";
__declspec(section ".rodata") const char str_0000477C[] = "rose\000\000\000";
__declspec(section ".rodata") const char str_00004784[] = "papa\000\000\000";
__declspec(section ".rodata") const char str_0000478C[] = "mama\000\000\000";
__declspec(section ".rodata") const char str_00004794[] = "konari\000";
__declspec(section ".rodata") const char str_0000479C[] = "SFX_STG6_MOAMOA_VOICE2\000";
__declspec(section ".rodata") const char str_000047B4[] = "base\000\000\000";
__declspec(section ".rodata") const char str_000047BC[] = "c_g_moamoa\000";
__declspec(section ".rodata") const char str_000047C8[] = "stg6_rsh_244\000\000\000";
__declspec(section ".rodata") const char str_000047D8[] = "group339\000\000\000";
__declspec(section ".rodata") const char str_000047E4[] = "group340\000\000\000";
__declspec(section ".rodata") const char str_000047F0[] = "group341\000\000\000";
__declspec(section ".rodata") const char str_000047FC[] = "senro\000\000";
__declspec(section ".rodata") const char str_00004804[] = "Z_1";
__declspec(section ".rodata") const char str_00004808[] = "SFX_STG6_MOA_TOGETHER_MOVE1";
__declspec(section ".rodata") const char str_00004824[] = "SFX_VOICE_MARIO_FIND1_3";
__declspec(section ".rodata") const char str_0000483C[] = "eff0\000\000\000";
__declspec(section ".rodata") const char str_00004844[] = "eff1\000\000\000";
__declspec(section ".rodata") const char str_0000484C[] = "SFX_STG6_MOA_TOGETHER_MOVE2";
__declspec(section ".rodata") const char str_00004868[] = "group166\000\000\000";
__declspec(section ".rodata") const char str_00004874[] = "SFX_STG6_MOAMOA_G_LEG1\000";
__declspec(section ".rodata") const char str_0000488C[] = "H_1";
__declspec(section ".rodata") const char str_00004890[] = "SFX_STG6_MOAMOA_G_LEG2\000";
__declspec(section ".rodata") const char str_000048A8[] = "SFX_STG6_MOAMOA_G_LEG3\000";
__declspec(section ".rodata") const char str_000048C0[] = "H_2";
__declspec(section ".rodata") const char str_000048C4[] = "S_2";
__declspec(section ".rodata") const char str_000048C8[] = "M_I_Y\000\000";
__declspec(section ".rodata") const char str_000048D0[] = "stg6_rsh_245\000\000\000";
__declspec(section ".rodata") const char str_000048E0[] = "stg6_rsh_246_02";
__declspec(section ".rodata") const char str_000048F0[] = "stg6_rsh_246_03";
__declspec(section ".rodata") const char str_00004900[] = "SFX_STG6_MOAMOA_G_LEG4\000";
__declspec(section ".rodata") const char str_00004918[] = "P_1";
__declspec(section ".rodata") const char str_0000491C[] = "S_3";
__declspec(section ".rodata") const char str_00004920[] = "stg6_rsh_246_01";
__declspec(section ".rodata") const char str_00004930[] = "M_S_1\000\000";
__declspec(section ".rodata") const char str_00004938[] = "stg6_rsh_247\000\000\000";
__declspec(section ".rodata") const char str_00004948[] = "SFX_STG6_MOAMOA_G_ESCAPE1\000\000";
__declspec(section ".rodata") const char str_00004964[] = "rsh_01_a\000\000\000";
__declspec(section ".rodata") const char str_00004970[] = "BGM_EVT_POWAN1\000";
__declspec(section ".rodata") const char str_00004980[] = "ENV_STG6_RSH1_3";
__declspec(section ".rodata") const char str_00004990[] = "BGM_STG6_HOM1\000\000";
__declspec(section ".rodata") const char str_000049A0[] = "BGM_EVT_DANGER4";
__declspec(section ".rodata") const char str_000049B0[] = "BGM_STG6_PIK1\000\000";
__declspec(section ".rodata") const char str_000049C0[] = "BGM_STG0_GOR1\000\000";
__declspec(section ".rodata") const f32 float_1_rsh_00014470[1] = { 1.0f };
__declspec(section ".rodata") const f32 float_15_rsh_00014474[1] = { 15.0f };
__declspec(section ".rodata") const f32 float_1p8_rsh_00014478[1] = { 1.8f };
__declspec(section ".rodata") const f64 double_to_int_mask_rsh_00014480 = 4503599627370496;
__declspec(section ".rodata") const f64 double_to_int_rsh_00014488 = 4503601774854144;
__declspec(section ".rodata") const f32 zero_rsh_00014490[1] = { 0.0f };
__declspec(section ".rodata") const f32 float_neg5000_rsh_00014494[1] = { -5000.0f };
__declspec(section ".rodata") const f32 float_neg1_rsh_00014498[1] = { -1.0f };
__declspec(section ".rodata") const f32 float_6p2832_rsh_0001449c[1] = { 6.2831855f };
__declspec(section ".rodata") const f32 float_360_rsh_000144a0[1] = { 360.0f };
__declspec(section ".rodata") const f32 float_0p00761_rsh_000144a4[1] = { 0.00761f };
__declspec(section ".rodata") const f32 float_0p16605_rsh_000144a8[1] = { 0.16605f };
__declspec(section ".rodata") const f32 float_3p1416_rsh_000144ac[1] = { 3.1415927f };
__declspec(section ".rodata") const f32 float_1p5708_rsh_000144b0[1] = { 1.5707964f };
__declspec(section ".rodata") const f32 float_4p7124_rsh_000144b4[1] = { 4.712389f };
__declspec(section ".rodata") const f32 float_0p03705_rsh_000144b8[1] = { 0.03705f };
__declspec(section ".rodata") const f32 float_0p4967_rsh_000144bc[1] = { 0.4967f };
__declspec(section ".rodata") const char str_00004A20[] = "SFX_STG6_MOAMOA_VOICE1\000";
__declspec(section ".rodata") const f32 float_200_rsh_000144d8[1] = { 200.0f };
__declspec(section ".rodata") const f32 float_30_rsh_000144dc[1] = { 30.0f };
__declspec(section ".rodata") const char str_00004A40[] = "D\000\000";
__declspec(section ".rodata") const char str_00004A44[] = "R\000\000";
__declspec(section ".rodata") const f32 float_0p5_rsh_000144e8[1] = { 0.5f };
__declspec(section ".rodata") const f32 float_32767_rsh_000144ec[1] = { 32767.0f };
__declspec(section ".rodata") const f32 float_0p1_rsh_000144f0[1] = { 0.1f };
__declspec(section ".rodata") const f32 float_0p03_rsh_000144f4[1] = { 0.03f };
__declspec(section ".rodata") const f32 float_100_rsh_000144f8[1] = { 100.0f };
__declspec(section ".rodata") const f32 float_50_rsh_000144fc[1] = { 50.0f };
__declspec(section ".rodata") const f32 float_5_rsh_00014500[1] = { 5.0f };
__declspec(section ".rodata") const f32 float_215_rsh_00014504[1] = { 215.0f };
__declspec(section ".rodata") const f32 float_0p3_rsh_00014508[1] = { 0.3f };
__declspec(section ".rodata") const f32 float_0p2_rsh_0001450c[1] = { 0.19999999f };
__declspec(section ".rodata") const f32 float_31_rsh_00014510[1] = { 31.0f };
__declspec(section ".rodata") const f32 float_2_rsh_00014514[1] = { 2.0f };
__declspec(section ".rodata") const f32 float_0p4_rsh_00014518[1] = { 0.4f };
__declspec(section ".rodata") const f32 float_1p5_rsh_0001451c[1] = { 1.5f };
__declspec(section ".rodata") const f32 float_0p8_rsh_00014520[1] = { 0.8f };
__declspec(section ".rodata") const f32 float_300_rsh_00014524[1] = { 300.0f };
__declspec(section ".rodata") const f32 float_600_rsh_00014528[1] = { 600.0f };
__declspec(section ".rodata") const f32 float_0p25_rsh_0001452c[1] = { 0.25f };
__declspec(section ".rodata") const f32 float_neg45_rsh_00014530[1] = { -45.0f };
__declspec(section ".rodata") const f32 float_90_rsh_00014534[1] = { 90.0f };
__declspec(section ".rodata") const f32 float_180_rsh_00014538[1] = { 180.0f };
__declspec(section ".rodata") const f32 float_0p9_rsh_0001453c[1] = { 0.9f };
__declspec(section ".rodata") const f32 float_135_rsh_00014540[1] = { 135.0f };
__declspec(section ".rodata") const f32 float_0p2_rsh_00014544[1] = { 0.2f };
__declspec(section ".rodata") const f32 float_0p1_rsh_00014548[1] = { 0.10000001f };
__declspec(section ".rodata") const f32 float_neg100_rsh_0001454c[1] = { -100.0f };
__declspec(section ".rodata") const f32 float_225_rsh_00014550[1] = { 225.0f };
__declspec(section ".rodata") const f32 float_1p1_rsh_00014554[1] = { 1.1f };
__declspec(section ".rodata") const f32 float_1p02_rsh_00014558[1] = { 1.02f };
__declspec(section ".rodata") const f32 float_0p20944_rsh_0001455c[1] = { 0.20943952f };
__declspec(section ".rodata") const f32 float_neg1000_rsh_00014560[1] = { -1000.0f };
__declspec(section ".rodata") const f32 float_250_rsh_00014564[1] = { 250.0f };
__declspec(section ".rodata") const f32 float_450_rsh_00014568[1] = { 450.0f };
__declspec(section ".rodata") const f32 float_neg50_rsh_0001456c[1] = { -50.0f };
__declspec(section ".rodata") const f32 float_neg1870_rsh_00014570[1] = { -1870.0f };
__declspec(section ".rodata") const f32 float_45_rsh_00014574[1] = { 45.0f };
__declspec(section ".rodata") const f32 float_60_rsh_00014578[1] = { 60.0f };
__declspec(section ".rodata") const f32 float_1000_rsh_0001457c[1] = { 1000.0f };
__declspec(section ".rodata") const f32 float_20_rsh_00014580[1] = { 20.0f };
__declspec(section ".rodata") const f32 float_10_rsh_00014584[1] = { 10.0f };
__declspec(section ".rodata") const f32 float_35_rsh_00014588[1] = { 35.0f };
__declspec(section ".rodata") const f32 float_65_rsh_0001458c[1] = { 65.0f };
__declspec(section ".rodata") const f32 float_40_rsh_00014590[1] = { 40.0f };
__declspec(section ".rodata") const f32 float_1E06_rsh_00014594[1] = { 1000000.0f };
__declspec(section ".rodata") const f64 double_30_rsh_00014598 = 30;
__declspec(section ".rodata") const char str_00004B00[] = "offscreen\000\000";
__declspec(section ".rodata") const f32 float_neg500_rsh_000145ac[1] = { -500.0f };
__declspec(section ".rodata") const f32 float_115_rsh_000145b0[1] = { 115.0f };
__declspec(section ".rodata") const f32 float_70_rsh_000145b4[1] = { 70.0f };
__declspec(section ".rodata") const f32 float_neg10_rsh_000145b8[1] = { -10.0f };
__declspec(section ".rodata") const char zero_rsh_000145bc[4] = {0};
__declspec(section ".rodata") const char str_00004B20[] = "J\000\000";
__declspec(section ".rodata") const u32 gap_03_00004B24_rodata[1] = { 0x00000000 };
#pragma force_active reset
s32 npc_anim_wait(EventEntry* event, BOOL isFirstCall);
static void resha_tev(MapTevCallbackInfo* info);
static s32 ramp_r(EventEntry* event, BOOL isFirstCall);
void moamoa_joint_position(Moamoa* moa, Vec* out);
static void ext_moamoa_dispent(void);
static void ext_moamoa_main(void);
static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa);
static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void ext_shadow_disp(CameraId camera, void* param);
static void ext_disp(CameraId camera, void* param);
static void ext_moamoa_init(void);
static f32 randf(f32 min, f32 max);
static s32 evt_moamoa_target_off(EventEntry* event, BOOL isFirstCall);
void evalOn(void);
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

asm s32 npc_anim_wait(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, str_000047B4@ha
	stw r0, 0x14(r1)
	addi r3, r3, str_000047B4@l
	bl npcNameToPtr
	lwz r3, 0x104(r3)
	bl animPoseGetLoopTimes
	lis r3, float_1_rsh_00014470@ha
	lfs f0, float_1_rsh_00014470@l(r3)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @1
	li r3, 0x2
	b @2
	@1:
	li r3, 0x0
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static void resha_tev(MapTevCallbackInfo* info) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	mr r4, r3
	li r3, 0x7
	stw r0, 0x14(r1)
	bl envAddTev
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static s32 ramp_r(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x20(r1)
	psq_st f31, 0x28(r1), 0, 0
	stw r31, 0x1c(r1)
	lis r4, 0xfd05
	mr r31, r3
	addi r4, r4, 0xf80
	bl evtGetFloat
	lis r3, gp@ha
	lis r0, 0x4330
	addi r4, r3, gp@l
	stw r0, 0x8(r1)
	lwz r5, 0x0(r4)
	lis r3, double_to_int_mask_rsh_00014480@ha
	addi r4, r3, double_to_int_mask_rsh_00014480@l
	fabs f31, f1
	lwz r0, 0x1c(r5)
	lis r3, float_15_rsh_00014474@ha
	lfd f2, 0x0(r4)
	stw r0, 0xc(r1)
	lfs f0, float_15_rsh_00014474@l(r3)
	lfd f1, 0x8(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f0
	bl sin
	lis r3, float_1p8_rsh_00014478@ha
	lis r4, 0xfe36
	lfs f0, float_1p8_rsh_00014478@l(r3)
	frsp f1, f1
	mr r3, r31
	addi r4, r4, 0x3c8a
	fmuls f0, f0, f31
	fmuls f1, f0, f1
	bl evtSetFloat
	li r3, 0x2
	psq_l f31, 0x28(r1), 0, 0
	lwz r0, 0x34(r1)
	lfd f31, 0x20(r1)
	lwz r31, 0x1c(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void moamoa_joint_position(Moamoa* moa, Vec* out) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x30(r1)
	psq_st f31, 0x38(r1), 0, 0
	stmw r30, 0x28(r1)
	lis r5, str_000047B4@ha
	mr r30, r3
	addi r3, r5, str_000047B4@l
	mr r31, r4
	bl npcNameToPtr
	lwz r3, 0x104(r3)
	bl animPoseGetAnimPosePtr
	lis r4, wp@ha
	lha r8, 0x48(r30)
	lwz r9, wp@l(r4)
	lis r6, 0x4330
	slwi r0, r8, 1
	lha r7, 0x4a(r30)
	add r4, r9, r0
	slwi r8, r8, 2
	lha r0, 0x570(r4)
	xoris r4, r7, 0x8000
	lis r5, double_to_int_rsh_00014488@ha
	stw r4, 0x1c(r1)
	addi r7, r5, double_to_int_rsh_00014488@l
	add r9, r9, r8
	xoris r5, r0, 0x8000
	stw r6, 0x18(r1)
	lfd f2, 0x0(r7)
	mr r4, r31
	lfd f0, 0x18(r1)
	stw r5, 0x24(r1)
	fsubs f1, f0, f2
	lha r8, 0x672(r9)
	stw r6, 0x20(r1)
	lha r0, 0x670(r9)
	mulli r8, r8, 0xc
	lfd f0, 0x20(r1)
	lwz r3, 0x15c(r3)
	fsubs f0, f0, f2
	mulli r0, r0, 0xc
	lwz r3, 0x0(r3)
	fdivs f31, f1, f0
	add r30, r3, r8
	add r3, r3, r0
	fmr f1, f31
	bl PSVECScale
	lis r4, float_1_rsh_00014470@ha
	mr r3, r30
	addi r5, r4, float_1_rsh_00014470@l
	addi r4, r1, 0x8
	lfs f0, 0x0(r5)
	fsubs f1, f0, f31
	bl PSVECScale
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x8
	bl PSVECAdd
	psq_l f31, 0x38(r1), 0, 0
	lfd f31, 0x30(r1)
	lmw r30, 0x28(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
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
	lis r3, zero_rsh_00014490@ha
	lis r4, ext_disp@ha
	addi r6, r3, zero_rsh_00014490@l
	lfs f1, 0x0(r6)
	addi r5, r4, ext_disp@l
	li r3, 0x4
	li r4, 0x1
	li r6, 0x0
	bl dispEntry
	lis r3, zero_rsh_00014490@ha
	lis r4, ext_shadow_disp@ha
	addi r6, r3, zero_rsh_00014490@l
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
	lis r3, float_neg5000_rsh_00014494@ha
	lis r4, ext_disp@ha
	addi r6, r3, float_neg5000_rsh_00014494@l
	lfs f1, 0x0(r6)
	addi r5, r4, ext_disp@l
	li r3, 0x1
	li r4, 0x1
	li r6, 0x0
	bl dispEntry
	lis r3, float_neg5000_rsh_00014494@ha
	lis r4, ext_shadow_disp@ha
	addi r6, r3, float_neg5000_rsh_00014494@l
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
	stwu r1, -0x150(r1)
	mflr r0
	stw r0, 0x154(r1)
	stfd f31, 0x140(r1)
	psq_st f31, 0x148(r1), 0, 0
	stfd f30, 0x130(r1)
	psq_st f30, 0x138(r1), 0, 0
	stfd f29, 0x120(r1)
	psq_st f29, 0x128(r1), 0, 0
	stfd f28, 0x110(r1)
	psq_st f28, 0x118(r1), 0, 0
	stfd f27, 0x100(r1)
	psq_st f27, 0x108(r1), 0, 0
	stfd f26, 0xf0(r1)
	psq_st f26, 0xf8(r1), 0, 0
	stmw r17, 0xb4(r1)
	bl marioGetPtr
	mr r28, r3
	li r3, 0x0
	bl partyGetPtr
	mr r21, r3
	li r3, 0x4
	bl camGetPtr
	lhz r0, 0x2e(r28)
	lis r4, zero_rsh_00014490@ha
	lfs f31, zero_rsh_00014490@l(r4)
	mr r23, r3
	cmplwi r0, 0x12
	li r25, 0x0
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
	lwz r0, 0x0(r21)
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
	lis r4, float_neg1_rsh_00014498@ha
	lis r3, wp@ha
	addi r5, r4, float_neg1_rsh_00014498@l
	addi r4, r3, wp@l
	lfs f0, 0x0(r5)
	lwz r3, 0x0(r4)
	stfs f0, 0x55c(r3)
	lwz r3, 0x0(r4)
	stfs f0, 0x560(r3)
	lbz r0, 0x31(r21)
	cmpwi r0, 0x5
	bne @7
	lwz r0, 0x0(r21)
	rlwinm. r0, r0, 0, 23, 23
	beq @7
	bl cloudGetBreathDir
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	stfs f1, 0x55c(r3)
	bl cloudGetBreathDist
	lis r3, wp@ha
	lis r4, float_6p2832_rsh_0001449c@ha
	addi r10, r3, wp@l
	lis r7, float_0p00761_rsh_000144a4@ha
	lwz r5, 0x0(r10)
	lis r3, float_360_rsh_000144a0@ha
	addi r8, r3, float_360_rsh_000144a0@l
	addi r9, r4, float_6p2832_rsh_0001449c@l
	stfs f1, 0x560(r5)
	lis r3, float_3p1416_rsh_000144ac@ha
	addi r4, r3, float_3p1416_rsh_000144ac@l
	lis r6, float_0p16605_rsh_000144a8@ha
	lwz r3, 0x0(r10)
	lis r5, float_1_rsh_00014470@ha
	lfs f2, 0x0(r9)
	lfs f1, 0x55c(r3)
	lfs f0, 0x0(r8)
	fmuls f2, f2, f1
	lfs f1, 0x0(r4)
	lfs f4, float_0p00761_rsh_000144a4@l(r7)
	lfs f3, float_0p16605_rsh_000144a8@l(r6)
	fdivs f5, f2, f0
	lfs f2, float_1_rsh_00014470@l(r5)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @8
	lis r4, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r4)
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
	lis r4, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r4)
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
	lis r4, float_1p5708_rsh_000144b0@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r4)
	fsubs f5, f1, f0
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	fneg f4, f4
	@10:
	lfs f1, 0x560(r3)
	lis r9, wp@ha
	lfs f0, 0x58(r21)
	lis r4, float_6p2832_rsh_0001449c@ha
	addi r8, r4, float_6p2832_rsh_0001449c@l
	lis r6, float_0p03705_rsh_000144b8@ha
	fmadds f0, f1, f4, f0
	lis r4, float_360_rsh_000144a0@ha
	addi r7, r4, float_360_rsh_000144a0@l
	lis r5, float_0p4967_rsh_000144bc@ha
	lis r4, float_3p1416_rsh_000144ac@ha
	addi r10, r9, wp@l
	stfs f0, 0x564(r3)
	lis r3, float_1_rsh_00014470@ha
	lfs f3, 0x0(r8)
	lfs f0, 0x5c(r21)
	lwz r9, 0x0(r10)
	lfs f1, float_3p1416_rsh_000144ac@l(r4)
	stfs f0, 0x568(r9)
	lfs f0, 0x0(r7)
	lwz r7, 0x0(r10)
	lfs f5, float_0p03705_rsh_000144b8@l(r6)
	lfs f2, 0x55c(r7)
	lfs f4, float_0p4967_rsh_000144bc@l(r5)
	fmuls f2, f3, f2
	lfs f3, float_1_rsh_00014470@l(r3)
	fdivs f2, f2, f0
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @12
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f2, f0
	bge @15
	fsubs f2, f2, f1
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fneg f5, f5
	b @14
	@15:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f2, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	@14:
	lfs f1, 0x560(r7)
	lfs f0, 0x60(r21)
	fnmsubs f0, f1, f5, f0
	stfs f0, 0x56c(r7)
	@7:
	bl extGetPosePtr
	lis r5, wp@ha
	lis r4, str_00004A20@ha
	addi r27, r5, wp@l
	mr r30, r3
	lwz r5, 0x0(r27)
	addi r24, r4, str_00004A20@l
	li r26, 0x0
	li r29, 0x0
	lwz r31, 0x8(r5)
	b @16
	@17:
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
	lhz r0, 0x0(r31)
	andi. r0, r0, 0x154
	bne @18
	lis r3, float_200_rsh_000144d8@ha
	lfs f1, 0x90(r28)
	lfs f0, float_200_rsh_000144d8@l(r3)
	fcmpo cr0, f1, f0
	ble @18
	lis r4, wp@ha
	lis r3, float_30_rsh_000144dc@ha
	addi r4, r4, wp@l
	lfs f0, float_30_rsh_000144dc@l(r3)
	lwz r4, 0x0(r4)
	lfs f1, 0x554(r4)
	fcmpo cr0, f1, f0
	bge @18
	lis r3, float_1_rsh_00014470@ha
	lfs f0, float_1_rsh_00014470@l(r3)
	fadds f31, f31, f0
	@18:
	lwz r3, 0x0(r27)
	lhz r3, 0x0(r3)
	clrlwi. r0, r3, 31
	beq @19
	rlwinm. r0, r3, 0, 29, 29
	bne @19
	bl marioKeyOffChk
	cmpwi r3, 0x0
	bne @19
	bl marioCtrlOffChk
	cmpwi r3, 0x0
	bne @19
	cmpwi r25, 0x0
	bne @19
	lhz r0, 0x0(r31)
	andi. r0, r0, 0x154
	bne @19
	mr r3, r30
	mr r4, r31
	bl moamoa_hit_check
	mr r21, r3
	cmpwi r21, 0x1
	bne @20
	lhz r0, 0x0(r31)
	lis r4, str_000041E0@ha
	lis r3, str_000041D0@ha
	lis r5, wp@ha
	ori r6, r0, 0x4
	li r0, 0x24
	sth r6, 0x0(r31)
	addi r20, r4, str_000041E0@l
	addi r25, r3, str_000041D0@l
	sth r0, 0x2(r31)
	lwzu r4, wp@l(r5)
	lha r3, 0x38(r4)
	addi r0, r3, 0x1
	sth r0, 0x38(r4)
	lhz r0, 0x0(r31)
	lwz r3, 0x0(r5)
	rlwinm. r0, r0, 0, 20, 20
	addi r22, r3, 0x50
	beq @21
	lbz r4, 0x4c(r31)
	lis r3, fs_group_tbl@ha
	addi r0, r3, fs_group_tbl@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r25, 0x0(r3)
	blt @22
	lwz r20, 0x4(r3)
	@22:
	cmplwi r4, 0xa
	bne @21
	lis r3, str_000048C4@ha
	addi r20, r3, str_000048C4@l
	@21:
	lis r3, wp@ha
	li r21, 0x0
	addi r17, r3, wp@l
	b @23
	@24:
	mr r3, r22
	mr r4, r25
	bl strcmp
	cmpwi r3, 0x0
	bne @25
	mr r4, r20
	addi r3, r22, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @26
	@25:
	addi r21, r21, 0x1
	addi r22, r22, 0x28
	@23:
	lwz r3, 0x0(r17)
	lwz r0, 0x4c(r3)
	cmpw r21, r0
	blt @24
	@26:
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x4c(r3)
	cmpw r21, r0
	bge @27
	lha r0, 0x3c(r31)
	cmpw r0, r21
	beq @27
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 29, 29
	beq @28
	lis r4, str_00004A40@ha
	mr r3, r20
	addi r4, r4, str_00004A40@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @27
	@28:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 27, 27
	beq @29
	lis r4, str_00004A44@ha
	mr r3, r20
	addi r4, r4, str_00004A44@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @27
	@29:
	lis r3, gp@ha
	sth r21, 0x3c(r31)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x44(r31)
	stw r0, 0x40(r31)
	@27:
	li r25, 0x1
	b @19
	@20:
	cmpwi r21, 0x2
	beq @30
	cmpwi r21, 0x4
	bne @31
	@30:
	lhz r0, 0x0(r31)
	lis r4, str_000041E0@ha
	lis r3, str_000041D0@ha
	lis r5, wp@ha
	ori r6, r0, 0xc
	li r0, 0x2f
	sth r6, 0x0(r31)
	addi r18, r4, str_000041E0@l
	addi r19, r3, str_000041D0@l
	sth r0, 0x2(r31)
	lwzu r4, wp@l(r5)
	lha r3, 0x38(r4)
	addi r0, r3, 0x1
	sth r0, 0x38(r4)
	lhz r0, 0x0(r31)
	lwz r3, 0x0(r5)
	rlwinm. r0, r0, 0, 20, 20
	addi r22, r3, 0x50
	beq @32
	lbz r4, 0x4c(r31)
	lis r3, fs_group_tbl@ha
	addi r0, r3, fs_group_tbl@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r19, 0x0(r3)
	blt @33
	lwz r18, 0x4(r3)
	@33:
	cmplwi r4, 0xa
	bne @32
	lis r3, str_000048C4@ha
	addi r18, r3, str_000048C4@l
	@32:
	lis r3, wp@ha
	li r20, 0x0
	addi r17, r3, wp@l
	b @34
	@35:
	mr r3, r22
	mr r4, r19
	bl strcmp
	cmpwi r3, 0x0
	bne @36
	mr r4, r18
	addi r3, r22, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @37
	@36:
	addi r20, r20, 0x1
	addi r22, r22, 0x28
	@34:
	lwz r3, 0x0(r17)
	lwz r0, 0x4c(r3)
	cmpw r20, r0
	blt @35
	@37:
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x4c(r3)
	cmpw r20, r0
	bge @38
	lha r0, 0x3c(r31)
	cmpw r0, r20
	beq @38
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 29, 29
	beq @39
	lis r4, str_00004A40@ha
	mr r3, r18
	addi r4, r4, str_00004A40@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @38
	@39:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 27, 27
	beq @40
	lis r4, str_00004A44@ha
	mr r3, r18
	addi r4, r4, str_00004A44@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @38
	@40:
	lis r3, gp@ha
	sth r20, 0x3c(r31)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x44(r31)
	stw r0, 0x40(r31)
	@38:
	cmpwi r21, 0x4
	beq @19
	li r25, 0x1
	b @19
	@31:
	cmpwi r21, 0x3
	bne @19
	lis r3, wp@ha
	lhz r0, 0x0(r31)
	addi r4, r3, wp@l
	lwz r7, 0x0(r4)
	ori r5, r0, 0x84
	lis r4, float_0p5_rsh_000144e8@ha
	li r0, 0x30
	lfs f2, 0x55c(r7)
	addi r6, r4, float_0p5_rsh_000144e8@l
	lfs f1, 0x550(r7)
	lis r3, vec3_rsh_00013d88@ha
	addi r4, r3, vec3_rsh_00013d88@l
	lfs f0, 0x0(r6)
	sth r5, 0x0(r31)
	fadds f1, f2, f1
	sth r0, 0x2(r31)
	fmuls f26, f1, f0
	lwz r3, 0x0(r4)
	lwz r0, 0x4(r4)
	stw r3, 0x8(r31)
	stw r0, 0xc(r31)
	lwz r0, 0x8(r4)
	stw r0, 0x10(r31)
	bl rand
	xoris r4, r3, 0x8000
	lis r0, 0x4330
	lis r3, float_6p2832_rsh_0001449c@ha
	stw r4, 0x94(r1)
	lfs f0, float_6p2832_rsh_0001449c@l(r3)
	lis r5, double_to_int_rsh_00014488@ha
	stw r0, 0x90(r1)
	lis r3, float_360_rsh_000144a0@ha
	lfd f3, double_to_int_rsh_00014488@l(r5)
	fmuls f1, f0, f26
	lfs f0, float_360_rsh_000144a0@l(r3)
	lis r4, float_32767_rsh_000144ec@ha
	lfd f2, 0x90(r1)
	lis r5, float_0p00761_rsh_000144a4@ha
	fdivs f29, f1, f0
	lis r3, float_3p1416_rsh_000144ac@ha
	lfs f5, float_0p00761_rsh_000144a4@l(r5)
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r3, float_1_rsh_00014470@ha
	fsubs f3, f2, f3
	lfs f2, float_32767_rsh_000144ec@l(r4)
	lis r4, float_0p1_rsh_000144f0@ha
	addi r6, r4, float_0p1_rsh_000144f0@l
	fcmpo cr0, f29, f1
	fdivs f2, f3, f2
	lfs f0, 0x0(r6)
	lis r4, float_0p16605_rsh_000144a8@ha
	lfs f4, float_0p16605_rsh_000144a8@l(r4)
	lfs f3, float_1_rsh_00014470@l(r3)
	fmadds f30, f2, f0, f0
	cror eq, lt, eq
	bne @41
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f29, f1
	cror eq, lt, eq
	bne @42
	fmuls f0, f29, f29
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f29
	b @43
	@42:
	fsubs f0, f29, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	b @43
	@41:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f29, f0
	bge @44
	fsubs f1, f29, f1
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	b @43
	@44:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f29, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	@43:
	fmuls f0, f30, f5
	stfs f0, 0x14(r31)
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_rsh_00014488@ha
	stw r3, 0x94(r1)
	addi r5, r4, double_to_int_rsh_00014488@l
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0x90(r1)
	addi r4, r3, float_32767_rsh_000144ec@l
	lfd f2, 0x0(r5)
	lis r3, float_0p03_rsh_000144f4@ha
	lfd f1, 0x90(r1)
	addi r6, r3, float_0p03_rsh_000144f4@l
	lfs f0, 0x0(r4)
	lis r5, float_0p03705_rsh_000144b8@ha
	fsubs f2, f1, f2
	lis r3, float_3p1416_rsh_000144ac@ha
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r4, float_0p4967_rsh_000144bc@ha
	lis r3, float_1_rsh_00014470@ha
	lfs f4, float_0p03705_rsh_000144b8@l(r5)
	fdivs f2, f2, f0
	lfs f0, 0x0(r6)
	lfs f3, float_0p4967_rsh_000144bc@l(r4)
	fmadds f0, f2, f0, f0
	lfs f2, float_1_rsh_00014470@l(r3)
	fcmpo cr0, f29, f1
	stfs f0, 0x1c(r31)
	cror eq, lt, eq
	bne @45
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f29, f1
	cror eq, lt, eq
	bne @46
	fmuls f0, f29, f29
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @47
	@46:
	fsubs f0, f29, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @47
	@45:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f29, f0
	bge @48
	fsubs f0, f29, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @47
	@48:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f29, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@47:
	fneg f0, f4
	lis r4, str_000041E0@ha
	lis r3, str_000041D0@ha
	li r0, 0x78
	lis r5, wp@ha
	addi r21, r4, str_000041E0@l
	fmuls f0, f30, f0
	addi r20, r3, str_000041D0@l
	stfs f0, 0x20(r31)
	sth r0, 0x18(r31)
	lwzu r4, wp@l(r5)
	lha r3, 0x38(r4)
	addi r0, r3, 0x1
	sth r0, 0x38(r4)
	lhz r0, 0x0(r31)
	lwz r3, 0x0(r5)
	rlwinm. r0, r0, 0, 20, 20
	addi r19, r3, 0x50
	beq @49
	lbz r4, 0x4c(r31)
	lis r3, fs_group_tbl@ha
	addi r0, r3, fs_group_tbl@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r20, 0x0(r3)
	blt @50
	lwz r21, 0x4(r3)
	@50:
	cmplwi r4, 0xa
	bne @49
	lis r3, str_000048C4@ha
	addi r21, r3, str_000048C4@l
	@49:
	lis r3, wp@ha
	li r18, 0x0
	addi r22, r3, wp@l
	b @51
	@52:
	mr r3, r19
	mr r4, r20
	bl strcmp
	cmpwi r3, 0x0
	bne @53
	mr r4, r21
	addi r3, r19, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @54
	@53:
	addi r18, r18, 0x1
	addi r19, r19, 0x28
	@51:
	lwz r3, 0x0(r22)
	lwz r0, 0x4c(r3)
	cmpw r18, r0
	blt @52
	@54:
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x4c(r3)
	cmpw r18, r0
	bge @55
	lha r0, 0x3c(r31)
	cmpw r0, r18
	beq @55
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 29, 29
	beq @56
	lis r4, str_00004A40@ha
	mr r3, r21
	addi r4, r4, str_00004A40@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @55
	@56:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 27, 27
	beq @57
	lis r4, str_00004A44@ha
	mr r3, r21
	addi r4, r4, str_00004A44@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @55
	@57:
	lis r3, gp@ha
	sth r18, 0x3c(r31)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x44(r31)
	stw r0, 0x40(r31)
	@55:
	li r25, 0x1
	@19:
	lwz r4, 0x0(r27)
	lhz r0, 0x0(r4)
	clrlwi. r0, r0, 31
	beq @58
	lhz r5, 0x0(r31)
	andi. r0, r5, 0x155
	bne @58
	lhz r3, 0x2e(r28)
	cmplwi r3, 0x0
	beq @59
	subi r0, r3, 0x1
	clrlwi r0, r0, 16
	cmplwi r0, 0x1
	ble @59
	subi r0, r3, 0x15
	clrlwi r0, r0, 16
	cmplwi r0, 0x1
	ble @59
	cmplwi r3, 0x1a
	bne @60
	@59:
	lis r3, float_200_rsh_000144d8@ha
	lfs f1, 0x90(r28)
	lfs f0, float_200_rsh_000144d8@l(r3)
	fcmpo cr0, f1, f0
	ble @58
	lis r3, float_30_rsh_000144dc@ha
	lfs f1, 0x554(r4)
	lfs f0, float_30_rsh_000144dc@l(r3)
	fcmpo cr0, f1, f0
	ble @58
	lis r3, float_100_rsh_000144f8@ha
	lfs f0, float_100_rsh_000144f8@l(r3)
	fcmpo cr0, f1, f0
	bge @58
	clrlwi. r0, r29, 31
	beq @58
	rlwinm. r0, r5, 0, 30, 30
	beq @61
	li r0, 0x2
	sth r0, 0x24(r31)
	b @58
	@61:
	li r0, 0x2
	sth r0, 0x2(r31)
	b @58
	@60:
	lis r3, float_50_rsh_000144fc@ha
	lfs f1, 0x554(r4)
	lfs f0, float_50_rsh_000144fc@l(r3)
	fcmpo cr0, f1, f0
	bge @58
	rlwinm. r0, r5, 0, 30, 30
	beq @62
	li r0, 0x1
	sth r0, 0x24(r31)
	b @58
	@62:
	li r0, 0x1
	sth r0, 0x2(r31)
	@58:
	lwz r3, 0x0(r27)
	lhz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @63
	lhz r0, 0x0(r31)
	andi. r0, r0, 0x444
	bne @63
	lis r4, gp@ha
	lwz r3, 0x4(r3)
	addi r4, r4, gp@l
	lwz r4, 0x0(r4)
	lwz r4, 0x1c(r4)
	divwu r0, r4, r3
	mullw r0, r0, r3
	subf r0, r0, r4
	cmplw r29, r0
	bne @63
	li r3, 0x3e8
	bl irand
	cmpwi r3, 0xc8
	bge @63
	lis r3, vec3_rsh_00013d94@ha
	lwz r5, 0xc(r30)
	addi r8, r3, vec3_rsh_00013d94@l
	mr r3, r24
	lwz r7, 0x0(r8)
	addi r4, r1, 0x50
	lwz r6, 0x4(r8)
	lwz r0, 0x8(r8)
	stw r7, 0x2c(r1)
	lfs f0, 0xc(r5)
	stw r6, 0x30(r1)
	lfs f1, 0x1c(r5)
	stfs f0, 0x2c(r1)
	lfs f0, 0x2c(r5)
	stw r0, 0x34(r1)
	lwz r6, 0x2c(r1)
	stfs f1, 0x30(r1)
	stfs f0, 0x34(r1)
	lwz r5, 0x30(r1)
	lwz r0, 0x34(r1)
	stw r6, 0x50(r1)
	stw r5, 0x54(r1)
	stw r0, 0x58(r1)
	bl psndSFXOn_3D
	@63:
	lha r0, 0x2(r31)
	cmplwi r0, 0x41
	bgt @64
	lis r3, jumptable_000183EC@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_000183EC@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@65:
	entry jt_00009330
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 25, 25
	bne @64
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x94(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0x90(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfs f0, 0x0(r5)
	lis r4, float_360_rsh_000144a0@ha
	lfd f1, 0x90(r1)
	lis r3, zero_rsh_00014490@ha
	addi r8, r4, float_360_rsh_000144a0@l
	lis r4, float_6p2832_rsh_0001449c@ha
	fsubs f1, f1, f2
	addi r9, r4, float_6p2832_rsh_0001449c@l
	addi r7, r3, zero_rsh_00014490@l
	lis r6, float_0p00761_rsh_000144a4@ha
	lis r5, float_0p16605_rsh_000144a8@ha
	lfs f2, 0x0(r8)
	fdivs f1, f1, f0
	lfs f0, 0x0(r7)
	lfs f3, 0x0(r9)
	lis r3, float_3p1416_rsh_000144ac@ha
	lis r4, float_1_rsh_00014470@ha
	lfs f5, float_0p00761_rsh_000144a4@l(r6)
	fmadds f0, f1, f2, f0
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lfs f4, float_0p16605_rsh_000144a8@l(r5)
	fmuls f0, f3, f0
	lfs f3, float_1_rsh_00014470@l(r4)
	fdivs f6, f0, f2
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @66
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @67
	fmuls f0, f6, f6
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f6
	b @68
	@67:
	fsubs f0, f6, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	b @68
	@66:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f6, f0
	bge @69
	fsubs f1, f6, f1
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	b @68
	@69:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	@68:
	lis r3, float_3p1416_rsh_000144ac@ha
	lwz r6, 0xc(r30)
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r4, float_5_rsh_00014500@ha
	lfs f2, float_5_rsh_00014500@l(r4)
	lis r5, float_0p03705_rsh_000144b8@ha
	lfs f0, 0xc(r6)
	fcmpo cr0, f6, f1
	lis r4, float_0p4967_rsh_000144bc@ha
	lis r3, float_1_rsh_00014470@ha
	fmadds f27, f2, f5, f0
	lfs f4, float_0p03705_rsh_000144b8@l(r5)
	lfs f3, float_0p4967_rsh_000144bc@l(r4)
	lfs f2, float_1_rsh_00014470@l(r3)
	cror eq, lt, eq
	bne @70
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @71
	fmuls f0, f6, f6
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @72
	@71:
	fsubs f0, f6, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @72
	@70:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f6, f0
	bge @73
	fsubs f0, f6, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @72
	@73:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@72:
	lis r3, float_5_rsh_00014500@ha
	lfs f0, 0x2c(r6)
	lfs f1, float_5_rsh_00014500@l(r3)
	fnmsubs f26, f1, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x94(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lis r3, float_32767_rsh_000144ec@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	stw r0, 0x90(r1)
	lfs f0, float_32767_rsh_000144ec@l(r3)
	lfd f1, 0x90(r1)
	fsubs f1, f1, f2
	fdivs f28, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x9c(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0x98(r1)
	lis r5, float_0p2_rsh_0001450c@ha
	lfs f0, float_32767_rsh_000144ec@l(r3)
	lis r4, float_0p3_rsh_00014508@ha
	lfd f1, 0x98(r1)
	lis r3, float_0p5_rsh_000144e8@ha
	lfs f4, float_0p2_rsh_0001450c@l(r5)
	lis r6, float_215_rsh_00014504@ha
	fsubs f1, f1, f2
	lfs f5, float_0p3_rsh_00014508@l(r4)
	lfs f2, float_215_rsh_00014504@l(r6)
	fmr f3, f26
	fmadds f4, f28, f4, f5
	lha r5, 0x2(r31)
	fdivs f6, f1, f0
	lfs f0, float_0p5_rsh_000144e8@l(r3)
	mr r3, r30
	mr r4, r31
	li r6, 0x0
	fmr f1, f27
	fmadds f5, f6, f5, f0
	bl moamoa_jump
	b @64
	@74:
	entry jt_000095DC
	lha r3, 0x4(r31)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x4(r31)
	bge @64
	li r0, 0x0
	sth r0, 0x4(r31)
	lha r3, 0x2(r31)
	addi r0, r3, 0x1
	sth r0, 0x2(r31)
	b @64
	@75:
	entry jt_00009608
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
	mulli r17, r0, 0xc
	add r3, r4, r17
	lfs f3, 0x14(r3)
	lfs f4, 0x1c(r3)
	bl distABf
	lis r3, wp@ha
	lwz r4, 0xc(r30)
	lwz r0, wp@l(r3)
	fmr f27, f1
	lfs f1, 0xc(r4)
	add r3, r0, r17
	lfs f2, 0x2c(r4)
	lfs f3, 0x14(r3)
	lfs f4, 0x1c(r3)
	bl angleABf
	lis r3, float_31_rsh_00014510@ha
	lfs f0, float_31_rsh_00014510@l(r3)
	fcmpo cr0, f27, f0
	ble @76
	lis r3, float_6p2832_rsh_0001449c@ha
	lis r6, float_0p00761_rsh_000144a4@ha
	addi r5, r3, float_6p2832_rsh_0001449c@l
	lis r4, float_360_rsh_000144a0@ha
	lfs f0, 0x0(r5)
	lis r5, float_0p16605_rsh_000144a8@ha
	lis r3, float_3p1416_rsh_000144ac@ha
	lfs f4, float_0p00761_rsh_000144a4@l(r6)
	fmuls f2, f0, f1
	lfs f0, float_360_rsh_000144a0@l(r4)
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r4, float_1_rsh_00014470@ha
	lfs f3, float_0p16605_rsh_000144a8@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_rsh_00014470@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @77
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @78
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @79
	@78:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @79
	@77:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f5, f0
	bge @80
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @79
	@80:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@79:
	lis r3, float_3p1416_rsh_000144ac@ha
	lwz r6, 0xc(r30)
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r4, float_30_rsh_000144dc@ha
	lfs f2, float_30_rsh_000144dc@l(r4)
	lis r4, float_0p4967_rsh_000144bc@ha
	lfs f0, 0xc(r6)
	fcmpo cr0, f5, f1
	lis r5, float_0p03705_rsh_000144b8@ha
	lis r3, float_1_rsh_00014470@ha
	fmadds f29, f2, f4, f0
	lfs f4, float_0p03705_rsh_000144b8@l(r5)
	lfs f3, float_0p4967_rsh_000144bc@l(r4)
	lfs f2, float_1_rsh_00014470@l(r3)
	cror eq, lt, eq
	bne @81
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @82
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @83
	@82:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @83
	@81:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f5, f0
	bge @84
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @83
	@84:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@83:
	lis r3, float_30_rsh_000144dc@ha
	lfs f0, 0x2c(r6)
	lfs f1, float_30_rsh_000144dc@l(r3)
	fnmsubs f28, f1, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x9c(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lis r3, float_32767_rsh_000144ec@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	stw r0, 0x98(r1)
	lfs f0, float_32767_rsh_000144ec@l(r3)
	lfd f1, 0x98(r1)
	fsubs f1, f1, f2
	fdivs f27, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x94(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0x90(r1)
	lis r5, zero_rsh_00014490@ha
	lfs f0, float_32767_rsh_000144ec@l(r3)
	lis r4, float_1_rsh_00014470@ha
	lfd f1, 0x90(r1)
	addi r6, r5, zero_rsh_00014490@l
	lis r3, float_0p4_rsh_00014518@ha
	addi r5, r4, float_1_rsh_00014470@l
	fsubs f1, f1, f2
	addi r4, r3, float_0p4_rsh_00014518@l
	lfs f2, 0x0(r6)
	lis r3, float_2_rsh_00014514@ha
	addi r7, r3, float_2_rsh_00014514@l
	lis r8, float_215_rsh_00014504@ha
	fdivs f3, f1, f0
	lfs f1, 0x0(r5)
	lfs f0, 0x0(r4)
	mr r3, r30
	lfs f5, 0x0(r7)
	mr r4, r31
	fmadds f4, f27, f2, f1
	lha r5, 0x2(r31)
	fmadds f0, f3, f2, f0
	lfs f2, float_215_rsh_00014504@l(r8)
	fmr f1, f29
	li r6, 0x0
	fmuls f4, f5, f4
	fmr f3, f28
	fmuls f5, f5, f0
	bl moamoa_jump
	b @64
	@76:
	lis r3, str_000047B4@ha
	addi r3, r3, str_000047B4@l
	bl npcNameToPtr
	lwz r3, 0x104(r3)
	bl animPoseGetAnimPosePtr
	lha r7, 0x48(r31)
	lis r5, 0x4330
	lis r4, wp@ha
	lwz r3, 0x15c(r3)
	addi r6, r4, wp@l
	stw r5, 0x98(r1)
	slwi r4, r7, 1
	lwz r8, 0x0(r6)
	addi r0, r4, 0x570
	lha r4, 0x4a(r31)
	lhax r0, r8, r0
	lis r6, double_to_int_rsh_00014488@ha
	xoris r4, r4, 0x8000
	slwi r7, r7, 2
	stw r4, 0x9c(r1)
	xoris r0, r0, 0x8000
	lfd f2, double_to_int_rsh_00014488@l(r6)
	add r8, r8, r7
	lfd f0, 0x98(r1)
	addi r4, r1, 0x44
	stw r0, 0x94(r1)
	fsubs f1, f0, f2
	lha r7, 0x672(r8)
	stw r5, 0x90(r1)
	lha r0, 0x670(r8)
	mulli r6, r7, 0xc
	lfd f0, 0x90(r1)
	lwz r3, 0x0(r3)
	fsubs f0, f0, f2
	mulli r0, r0, 0xc
	add r17, r3, r6
	fdivs f27, f1, f0
	add r3, r3, r0
	fmr f1, f27
	bl PSVECScale
	lis r4, float_1_rsh_00014470@ha
	mr r3, r17
	addi r5, r4, float_1_rsh_00014470@l
	addi r4, r1, 0x14
	lfs f0, 0x0(r5)
	fsubs f1, f0, f27
	bl PSVECScale
	addi r3, r1, 0x44
	addi r4, r1, 0x14
	mr r5, r3
	bl PSVECAdd
	addi r3, r1, 0x44
	addi r4, r31, 0x30
	mr r5, r3
	bl PSVECAdd
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xa4(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lis r3, float_32767_rsh_000144ec@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	stw r0, 0xa0(r1)
	lfs f0, float_32767_rsh_000144ec@l(r3)
	lfd f1, 0xa0(r1)
	fsubs f1, f1, f2
	fdivs f27, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa8(r1)
	lis r6, float_2_rsh_00014514@ha
	lfs f0, float_32767_rsh_000144ec@l(r3)
	lis r5, zero_rsh_00014490@ha
	lfd f1, 0xa8(r1)
	lis r4, float_1p5_rsh_0001451c@ha
	lfs f5, float_2_rsh_00014514@l(r6)
	lis r3, float_0p8_rsh_00014520@ha
	fsubs f1, f1, f2
	lfs f2, zero_rsh_00014490@l(r5)
	li r5, 0x3d
	li r6, 0x0
	fdivs f3, f1, f0
	lfs f1, float_1p5_rsh_0001451c@l(r4)
	lfs f0, float_0p8_rsh_00014520@l(r3)
	mr r3, r30
	mr r4, r31
	fmadds f4, f27, f2, f1
	fmadds f0, f3, f2, f0
	lfs f1, 0x44(r1)
	lfs f2, 0x48(r1)
	fmuls f4, f5, f4
	lfs f3, 0x4c(r1)
	fmuls f5, f5, f0
	bl moamoa_jump
	lhz r0, 0x0(r31)
	ori r0, r0, 0x200
	sth r0, 0x0(r31)
	lwz r0, 0x0(r30)
	ori r0, r0, 0x4
	stw r0, 0x0(r30)
	b @64
	@85:
	entry jt_00009A9C
	lis r3, str_000047B4@ha
	addi r3, r3, str_000047B4@l
	bl npcNameToPtr
	lwz r3, 0x104(r3)
	bl animPoseGetAnimPosePtr
	lha r7, 0x48(r31)
	lis r5, 0x4330
	lis r4, wp@ha
	lwz r3, 0x15c(r3)
	addi r6, r4, wp@l
	stw r5, 0xa8(r1)
	slwi r4, r7, 1
	lwz r8, 0x0(r6)
	addi r0, r4, 0x570
	lha r4, 0x4a(r31)
	lhax r0, r8, r0
	lis r6, double_to_int_rsh_00014488@ha
	xoris r4, r4, 0x8000
	slwi r7, r7, 2
	stw r4, 0xac(r1)
	xoris r0, r0, 0x8000
	lfd f2, double_to_int_rsh_00014488@l(r6)
	add r8, r8, r7
	lfd f0, 0xa8(r1)
	addi r4, r1, 0x38
	stw r0, 0xa4(r1)
	fsubs f1, f0, f2
	lha r7, 0x672(r8)
	stw r5, 0xa0(r1)
	lha r0, 0x670(r8)
	mulli r6, r7, 0xc
	lfd f0, 0xa0(r1)
	lwz r3, 0x0(r3)
	fsubs f0, f0, f2
	mulli r0, r0, 0xc
	add r17, r3, r6
	fdivs f27, f1, f0
	add r3, r3, r0
	fmr f1, f27
	bl PSVECScale
	lis r4, float_1_rsh_00014470@ha
	mr r3, r17
	addi r5, r4, float_1_rsh_00014470@l
	addi r4, r1, 0x8
	lfs f0, 0x0(r5)
	fsubs f1, f0, f27
	bl PSVECScale
	addi r3, r1, 0x38
	addi r4, r1, 0x8
	mr r5, r3
	bl PSVECAdd
	addi r3, r1, 0x38
	addi r4, r31, 0x30
	mr r5, r3
	bl PSVECAdd
	lfs f0, 0x38(r1)
	lwz r3, 0xc(r30)
	stfs f0, 0xc(r3)
	lfs f0, 0x3c(r1)
	lwz r3, 0xc(r30)
	stfs f0, 0x1c(r3)
	lfs f0, 0x40(r1)
	lwz r3, 0xc(r30)
	stfs f0, 0x2c(r3)
	b @64
	@86:
	entry jt_00009BA0
	lha r3, 0x4(r31)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x4(r31)
	bge @64
	li r0, 0x0
	sth r0, 0x4(r31)
	lha r3, 0x2(r31)
	addi r0, r3, 0x1
	sth r0, 0x2(r31)
	b @64
	@87:
	entry jt_00009BCC
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfs f1, 0x0(r5)
	lis r4, float_200_rsh_000144d8@ha
	lfd f0, 0xa8(r1)
	lis r3, zero_rsh_00014490@ha
	addi r5, r4, float_200_rsh_000144d8@l
	fsubs f3, f0, f2
	addi r4, r3, zero_rsh_00014490@l
	lfs f2, 0x0(r5)
	lis r3, float_300_rsh_00014524@ha
	lfs f0, 0x0(r4)
	fdivs f3, f3, f1
	lfs f1, float_300_rsh_00014524@l(r3)
	fmadds f0, f3, f2, f0
	stfs f0, 0x1c(r31)
	lfs f0, 0x1c(r31)
	fmuls f0, f1, f0
	fdivs f27, f0, f2
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_rsh_00014488@ha
	stw r3, 0xa4(r1)
	addi r5, r4, double_to_int_rsh_00014488@l
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa0(r1)
	addi r4, r3, float_32767_rsh_000144ec@l
	lfd f1, 0x0(r5)
	lis r3, zero_rsh_00014490@ha
	lfd f0, 0xa0(r1)
	li r0, 0x0
	lfs f2, 0x0(r4)
	fsubs f3, f0, f1
	lfs f1, zero_rsh_00014490@l(r3)
	fsubs f0, f27, f1
	fdivs f2, f3, f2
	fmadds f0, f2, f0, f1
	stfs f0, 0x20(r31)
	lha r3, 0x2(r31)
	addi r3, r3, 0x1
	sth r3, 0x2(r31)
	sth r0, 0x4(r31)
	@88:
	entry jt_00009C94
	lha r0, 0x4(r31)
	cmpwi r0, 0xc8
	bge @89
	lis r3, float_1_rsh_00014470@ha
	lfs f1, float_1_rsh_00014470@l(r3)
	b @90
	@89:
	subfic r3, r0, 0x320
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_rsh_00014488@ha
	stw r3, 0xac(r1)
	lis r3, float_600_rsh_00014528@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	stw r0, 0xa8(r1)
	lfs f0, float_600_rsh_00014528@l(r3)
	lfd f1, 0xa8(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f0
	@90:
	lis r3, zero_rsh_00014490@ha
	fmr f29, f1
	lfs f0, zero_rsh_00014490@l(r3)
	fcmpo cr0, f1, f0
	bge @91
	lhz r0, 0x0(r31)
	fmr f29, f0
	ori r0, r0, 0x200
	sth r0, 0x0(r31)
	@91:
	li r6, 0x3
	lis r3, gp@ha
	divw r5, r29, r6
	lwz r4, gp@l(r3)
	lis r0, 0x4330
	stw r0, 0xa8(r1)
	lis r3, double_to_int_mask_rsh_00014480@ha
	lwz r0, 0x1c(r4)
	mullw r4, r5, r6
	add r0, r29, r0
	stw r0, 0xac(r1)
	lis r5, wp@ha
	lfd f1, double_to_int_mask_rsh_00014480@l(r3)
	lis r3, float_0p25_rsh_0001452c@ha
	lfd f0, 0xa8(r1)
	subf r0, r4, r29
	mulli r0, r0, 0xc
	fsubs f1, f0, f1
	lfs f0, float_0p25_rsh_0001452c@l(r3)
	lwz r3, wp@l(r5)
	add r3, r3, r0
	fmuls f1, f1, f0
	lfs f26, 0x14(r3)
	lfs f27, 0x18(r3)
	lfs f28, 0x1c(r3)
	bl sin
	lis r3, gp@ha
	lis r0, 0x4330
	addi r4, r3, gp@l
	frsp f2, f1
	lwz r5, 0x0(r4)
	lis r3, double_to_int_mask_rsh_00014480@ha
	lfs f1, 0x20(r31)
	addi r4, r3, double_to_int_mask_rsh_00014480@l
	lwz r5, 0x1c(r5)
	fmuls f3, f1, f2
	stw r0, 0xa0(r1)
	add r0, r29, r5
	lfs f0, 0x1c(r31)
	stw r0, 0xa4(r1)
	lis r3, float_0p25_rsh_0001452c@ha
	lfd f2, 0x0(r4)
	fmadds f27, f0, f29, f27
	lfd f1, 0xa0(r1)
	fmadds f26, f29, f3, f26
	lfs f0, float_0p25_rsh_0001452c@l(r3)
	fsubs f1, f1, f2
	fmuls f1, f1, f0
	bl cos
	lwz r4, 0xc(r30)
	lis r3, float_15_rsh_00014474@ha
	lfs f0, 0x20(r31)
	frsp f4, f1
	lfs f3, 0xc(r4)
	fneg f1, f0
	lfs f2, float_15_rsh_00014474@l(r3)
	fsubs f0, f26, f3
	fmuls f1, f1, f4
	fdivs f0, f0, f2
	fadds f0, f3, f0
	fmadds f28, f29, f1, f28
	stfs f0, 0xc(r4)
	lwz r3, 0xc(r30)
	lfs f1, 0x1c(r3)
	fsubs f0, f27, f1
	fdivs f0, f0, f2
	fadds f0, f1, f0
	stfs f0, 0x1c(r3)
	lwz r3, 0xc(r30)
	lfs f1, 0x2c(r3)
	fsubs f0, f28, f1
	fdivs f0, f0, f2
	fadds f0, f1, f0
	stfs f0, 0x2c(r3)
	lha r3, 0x4(r31)
	addi r0, r3, 0x1
	sth r0, 0x4(r31)
	b @64
	@92:
	entry jt_00009E38
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lis r4, float_90_rsh_00014534@ha
	lfs f0, 0x0(r5)
	lfd f1, 0xa8(r1)
	lis r3, float_neg45_rsh_00014530@ha
	addi r9, r4, float_90_rsh_00014534@l
	lis r4, float_6p2832_rsh_0001449c@ha
	fsubs f1, f1, f2
	addi r5, r3, float_neg45_rsh_00014530@l
	lis r3, wp@ha
	addi r8, r4, float_6p2832_rsh_0001449c@l
	addi r6, r3, wp@l
	lis r4, float_1_rsh_00014470@ha
	fdivs f2, f1, f0
	lwz r10, 0x0(r6)
	lfs f0, 0x0(r5)
	lis r3, float_360_rsh_000144a0@ha
	lfs f1, 0x0(r9)
	addi r7, r3, float_360_rsh_000144a0@l
	fmadds f1, f2, f1, f0
	lfs f3, 0x550(r10)
	lfs f2, 0x0(r8)
	lis r6, float_0p00761_rsh_000144a4@ha
	lis r5, float_0p16605_rsh_000144a8@ha
	lfs f0, 0x0(r7)
	fadds f3, f3, f1
	lis r3, float_3p1416_rsh_000144ac@ha
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lfs f27, 0x554(r10)
	fmuls f2, f2, f3
	lfs f5, float_0p00761_rsh_000144a4@l(r6)
	lfs f4, float_0p16605_rsh_000144a8@l(r5)
	lfs f3, float_1_rsh_00014470@l(r4)
	fdivs f6, f2, f0
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @93
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @94
	fmuls f0, f6, f6
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f6
	b @95
	@94:
	fsubs f0, f6, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	b @95
	@93:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f6, f0
	bge @96
	fsubs f1, f6, f1
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	b @95
	@96:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	@95:
	lwz r6, 0xc(r30)
	lis r3, float_3p1416_rsh_000144ac@ha
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r4, float_15_rsh_00014474@ha
	lfs f2, float_15_rsh_00014474@l(r4)
	lis r5, float_0p03705_rsh_000144b8@ha
	lfs f0, 0xc(r6)
	fcmpo cr0, f6, f1
	lis r4, float_0p4967_rsh_000144bc@ha
	lis r3, float_1_rsh_00014470@ha
	fmadds f29, f2, f5, f0
	lfs f30, 0x1c(r6)
	lfs f4, float_0p03705_rsh_000144b8@l(r5)
	lfs f3, float_0p4967_rsh_000144bc@l(r4)
	lfs f2, float_1_rsh_00014470@l(r3)
	cror eq, lt, eq
	bne @97
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @98
	fmuls f0, f6, f6
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @99
	@98:
	fsubs f0, f6, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @99
	@97:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f6, f0
	bge @L100
	fsubs f0, f6, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @99
	@L100:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@99:
	lis r3, float_15_rsh_00014474@ha
	lfs f0, 0x2c(r6)
	lfs f1, float_15_rsh_00014474@l(r3)
	fnmsubs f28, f1, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f1, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfs f2, 0x0(r5)
	lis r4, zero_rsh_00014490@ha
	lfd f0, 0xa8(r1)
	lis r3, float_1_rsh_00014470@ha
	fsubs f3, f0, f1
	lfs f1, zero_rsh_00014490@l(r4)
	lfs f0, float_1_rsh_00014470@l(r3)
	fdivs f2, f3, f2
	fmadds f26, f2, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xa4(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa0(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfs f0, 0x0(r5)
	lis r4, zero_rsh_00014490@ha
	lfd f1, 0xa0(r1)
	lis r3, float_0p4_rsh_00014518@ha
	addi r5, r4, zero_rsh_00014490@l
	fmr f4, f26
	fsubs f3, f1, f2
	addi r4, r3, float_0p4_rsh_00014518@l
	lfs f1, 0x0(r4)
	lis r3, float_100_rsh_000144f8@ha
	lfs f2, 0x0(r5)
	fdivs f3, f3, f0
	lfs f0, float_100_rsh_000144f8@l(r3)
	mr r3, r30
	mr r4, r31
	fmadds f5, f3, f2, f1
	fmr f1, f29
	fmr f2, f30
	fmr f3, f28
	fcmpo cr0, f27, f0
	bge @L101
	lha r5, 0x2(r31)
	b @L102
	@L101:
	li r5, 0x0
	@L102:
	li r6, 0x0
	bl moamoa_jump
	b @64
	@L103:
	entry jt_0000A130
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lis r4, float_90_rsh_00014534@ha
	lis r3, float_neg45_rsh_00014530@ha
	lfd f1, 0xa8(r1)
	addi r7, r4, float_90_rsh_00014534@l
	lfs f0, 0x0(r5)
	addi r6, r3, float_neg45_rsh_00014530@l
	fsubs f1, f1, f2
	lis r3, wp@ha
	addi r5, r3, wp@l
	lis r4, float_180_rsh_00014538@ha
	lwz r9, 0x0(r5)
	addi r8, r4, float_180_rsh_00014538@l
	fdivs f2, f1, f0
	lfs f0, 0x0(r6)
	lfs f1, 0x0(r7)
	lis r3, float_6p2832_rsh_0001449c@ha
	addi r5, r3, float_6p2832_rsh_0001449c@l
	lis r4, float_360_rsh_000144a0@ha
	fmadds f0, f2, f1, f0
	lfs f4, 0x550(r9)
	lfs f3, 0x0(r8)
	addi r7, r4, float_360_rsh_000144a0@l
	lfs f2, 0x0(r5)
	lis r3, float_3p1416_rsh_000144ac@ha
	fadds f4, f4, f0
	lis r6, float_0p00761_rsh_000144a4@ha
	lfs f0, 0x0(r7)
	lis r5, float_0p16605_rsh_000144a8@ha
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r4, float_1_rsh_00014470@ha
	fadds f4, f4, f3
	lfs f27, 0x554(r9)
	lfs f5, float_0p00761_rsh_000144a4@l(r6)
	lfs f3, float_1_rsh_00014470@l(r4)
	fmuls f2, f2, f4
	lfs f4, float_0p16605_rsh_000144a8@l(r5)
	fdivs f2, f2, f0
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @L104
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @L105
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f2
	b @L106
	@L105:
	fsubs f0, f2, f1
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f2
	b @L106
	@L104:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f2, f0
	bge @L107
	fsubs f2, f2, f1
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f2
	fneg f5, f5
	b @L106
	@L107:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f2, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f2
	fneg f5, f5
	@L106:
	lwz r4, 0xc(r30)
	lis r3, float_30_rsh_000144dc@ha
	lfs f1, float_30_rsh_000144dc@l(r3)
	lfs f0, 0xc(r4)
	lfs f30, 0x1c(r4)
	fmadds f29, f1, f5, f0
	lfs f28, 0x2c(r4)
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f1, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfs f2, 0x0(r5)
	lis r4, zero_rsh_00014490@ha
	lfd f0, 0xa8(r1)
	lis r3, float_1_rsh_00014470@ha
	lis r5, float_2_rsh_00014514@ha
	fsubs f3, f0, f1
	lfs f1, zero_rsh_00014490@l(r4)
	lfs f0, float_1_rsh_00014470@l(r3)
	fdivs f3, f3, f2
	lfs f2, float_2_rsh_00014514@l(r5)
	fmadds f0, f3, f1, f0
	fmuls f26, f2, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xa4(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa0(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lis r6, float_2_rsh_00014514@ha
	lfs f0, 0x0(r5)
	lfd f1, 0xa0(r1)
	lis r4, zero_rsh_00014490@ha
	lis r3, float_0p4_rsh_00014518@ha
	lfs f4, float_2_rsh_00014514@l(r6)
	fsubs f1, f1, f2
	addi r5, r4, zero_rsh_00014490@l
	addi r4, r3, float_0p4_rsh_00014518@l
	lfs f2, 0x0(r5)
	lis r3, float_100_rsh_000144f8@ha
	fdivs f3, f1, f0
	lfs f1, 0x0(r4)
	mr r4, r31
	lfs f0, float_100_rsh_000144f8@l(r3)
	mr r3, r30
	fmadds f3, f3, f2, f1
	fmr f1, f29
	fmr f2, f30
	fmuls f5, f4, f3
	fmr f3, f28
	fmr f4, f26
	fcmpo cr0, f27, f0
	bge @L108
	lha r5, 0x2(r31)
	b @L109
	@L108:
	li r5, 0x0
	@L109:
	li r6, 0x0
	bl moamoa_jump
	b @64
	@L110:
	entry jt_0000A394
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
	lis r3, float_6p2832_rsh_0001449c@ha
	lis r6, float_0p00761_rsh_000144a4@ha
	addi r5, r3, float_6p2832_rsh_0001449c@l
	lis r4, float_360_rsh_000144a0@ha
	lfs f0, 0x0(r5)
	lis r5, float_0p16605_rsh_000144a8@ha
	lis r3, float_3p1416_rsh_000144ac@ha
	lfs f4, float_0p00761_rsh_000144a4@l(r6)
	fmuls f2, f0, f1
	lfs f0, float_360_rsh_000144a0@l(r4)
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r4, float_1_rsh_00014470@ha
	lfs f3, float_0p16605_rsh_000144a8@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_rsh_00014470@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @L111
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @L112
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @L113
	@L112:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @L113
	@L111:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f5, f0
	bge @L114
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @L113
	@L114:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@L113:
	lwz r7, 0xc(r30)
	lis r3, float_3p1416_rsh_000144ac@ha
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r5, float_0p4967_rsh_000144bc@ha
	lfs f2, 0x1c(r31)
	lis r6, float_0p03705_rsh_000144b8@ha
	lfs f0, 0xc(r7)
	fcmpo cr0, f5, f1
	lis r4, float_1_rsh_00014470@ha
	lfs f3, float_0p4967_rsh_000144bc@l(r5)
	fmadds f0, f2, f4, f0
	lfs f4, float_0p03705_rsh_000144b8@l(r6)
	lfs f2, float_1_rsh_00014470@l(r4)
	stfs f0, 0xc(r7)
	cror eq, lt, eq
	bne @L115
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @L116
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @L117
	@L116:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @L117
	@L115:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f5, f0
	bge @L118
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @L117
	@L118:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@L117:
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
	bge @64
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
	b @64
	@L119:
	entry jt_0000A5F0
	lha r3, 0x4(r31)
	addi r3, r3, 0x1
	extsh r0, r3
	sth r3, 0x4(r31)
	cmpwi r0, 0x4
	ble @64
	lha r0, 0x24(r31)
	sth r0, 0x2(r31)
	b @64
	@L120:
	entry jt_0000A614
	lhz r0, 0x0(r31)
	clrlwi. r0, r0, 31
	bne @L121
	lfs f26, 0x8c(r28)
	lfs f27, 0x94(r28)
	b @L122
	@L121:
	li r3, 0x3
	lis r4, wp@ha
	divw r0, r29, r3
	addi r4, r4, wp@l
	lwz r4, 0x0(r4)
	mullw r0, r0, r3
	subf r0, r0, r29
	mulli r0, r0, 0xc
	add r3, r4, r0
	lfs f26, 0x14(r3)
	lfs f27, 0x1c(r3)
	@L122:
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lis r3, float_32767_rsh_000144ec@ha
	lfd f4, double_to_int_rsh_00014488@l(r4)
	stw r0, 0xa8(r1)
	fmr f2, f27
	lfs f0, float_32767_rsh_000144ec@l(r3)
	fmr f1, f26
	lfd f3, 0xa8(r1)
	lwz r5, 0xc(r30)
	fsubs f5, f3, f4
	lfs f3, 0xc(r5)
	lfs f4, 0x2c(r5)
	fdivs f27, f5, f0
	bl angleABf
	lis r3, float_90_rsh_00014534@ha
	lis r4, float_neg45_rsh_00014530@ha
	addi r5, r3, float_90_rsh_00014534@l
	lfs f0, float_neg45_rsh_00014530@l(r4)
	lfs f2, 0x0(r5)
	lis r3, float_6p2832_rsh_0001449c@ha
	addi r8, r3, float_6p2832_rsh_0001449c@l
	lis r4, float_360_rsh_000144a0@ha
	fmadds f0, f27, f2, f0
	addi r7, r4, float_360_rsh_000144a0@l
	lis r6, float_0p00761_rsh_000144a4@ha
	lis r5, float_0p16605_rsh_000144a8@ha
	lis r3, float_3p1416_rsh_000144ac@ha
	lis r4, float_1_rsh_00014470@ha
	fadds f2, f1, f0
	lfs f1, 0x0(r8)
	lfs f0, 0x0(r7)
	lfs f4, float_0p00761_rsh_000144a4@l(r6)
	fmuls f2, f1, f2
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lfs f3, float_0p16605_rsh_000144a8@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_rsh_00014470@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @L123
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @L124
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @L125
	@L124:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @L125
	@L123:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f5, f0
	bge @L126
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @L125
	@L126:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@L125:
	lwz r6, 0xc(r30)
	lis r3, float_3p1416_rsh_000144ac@ha
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r4, float_15_rsh_00014474@ha
	lfs f2, float_15_rsh_00014474@l(r4)
	lis r4, float_0p4967_rsh_000144bc@ha
	lfs f0, 0xc(r6)
	fcmpo cr0, f5, f1
	lis r5, float_0p03705_rsh_000144b8@ha
	lis r3, float_1_rsh_00014470@ha
	fmadds f29, f2, f4, f0
	lfs f30, 0x1c(r6)
	lfs f4, float_0p03705_rsh_000144b8@l(r5)
	lfs f3, float_0p4967_rsh_000144bc@l(r4)
	lfs f2, float_1_rsh_00014470@l(r3)
	cror eq, lt, eq
	bne @L127
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @L128
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @L129
	@L128:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @L129
	@L127:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f5, f0
	bge @L130
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @L129
	@L130:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@L129:
	lis r3, float_15_rsh_00014474@ha
	lfs f0, 0x2c(r6)
	lfs f1, float_15_rsh_00014474@l(r3)
	fnmsubs f26, f1, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lis r3, float_32767_rsh_000144ec@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	stw r0, 0xa8(r1)
	lfs f0, float_32767_rsh_000144ec@l(r3)
	lfd f1, 0xa8(r1)
	fsubs f1, f1, f2
	fdivs f27, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xa4(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa0(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfs f0, 0x0(r5)
	lis r4, zero_rsh_00014490@ha
	lfd f1, 0xa0(r1)
	lis r3, float_1_rsh_00014470@ha
	lfs f5, zero_rsh_00014490@l(r4)
	mr r4, r31
	fsubs f3, f1, f2
	lha r5, 0x2(r31)
	fmr f1, f29
	li r6, 0x1
	fmr f2, f30
	addi r5, r5, 0x1
	fdivs f6, f3, f0
	lfs f0, float_1_rsh_00014470@l(r3)
	mr r3, r30
	fmadds f4, f27, f5, f0
	fmr f3, f26
	fmadds f5, f6, f5, f0
	bl moamoa_jump
	b @64
	@L131:
	entry jt_0000A918
	lha r3, 0x4(r31)
	addi r3, r3, 0x1
	extsh r0, r3
	sth r3, 0x4(r31)
	cmpwi r0, 0x1e
	bge @L132
	lwz r4, 0xc(r30)
	lis r3, float_0p9_rsh_0001453c@ha
	lfs f1, float_0p9_rsh_0001453c@l(r3)
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
	b @64
	@L132:
	li r0, 0x31
	sth r0, 0x2(r31)
	b @64
	@L133:
	entry jt_0000A978
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lis r3, float_32767_rsh_000144ec@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	stw r0, 0xa8(r1)
	lfs f0, float_32767_rsh_000144ec@l(r3)
	lfd f1, 0xa8(r1)
	fsubs f1, f1, f2
	fdivs f27, f1, f0
	bl rand
	lis r5, float_90_rsh_00014534@ha
	lis r4, float_135_rsh_00014540@ha
	lfs f0, float_135_rsh_00014540@l(r4)
	xoris r6, r3, 0x8000
	lfs f1, float_90_rsh_00014534@l(r5)
	lis r0, 0x4330
	lis r3, float_6p2832_rsh_0001449c@ha
	lis r4, double_to_int_rsh_00014488@ha
	addi r5, r3, float_6p2832_rsh_0001449c@l
	stw r6, 0xa4(r1)
	fmadds f0, f27, f1, f0
	addi r6, r4, double_to_int_rsh_00014488@l
	stw r0, 0xa0(r1)
	lis r3, float_360_rsh_000144a0@ha
	lfs f1, 0x0(r5)
	addi r4, r3, float_360_rsh_000144a0@l
	lis r3, float_32767_rsh_000144ec@ha
	fmuls f1, f1, f0
	lfs f0, 0x0(r4)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfd f3, 0x0(r6)
	lis r4, float_300_rsh_00014524@ha
	lfd f2, 0xa0(r1)
	fdivs f7, f1, f0
	addi r6, r4, float_300_rsh_00014524@l
	lis r3, float_3p1416_rsh_000144ac@ha
	lis r4, float_0p16605_rsh_000144a8@ha
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r3, float_1_rsh_00014470@ha
	fsubs f3, f2, f3
	lfs f2, 0x0(r5)
	lis r5, float_200_rsh_000144d8@ha
	lfs f0, 0x0(r6)
	addi r7, r5, float_200_rsh_000144d8@l
	fcmpo cr0, f7, f1
	fdivs f3, f3, f2
	lfs f2, 0x0(r7)
	lis r5, float_0p00761_rsh_000144a4@ha
	lfs f4, float_0p16605_rsh_000144a8@l(r4)
	lfs f5, float_0p00761_rsh_000144a4@l(r5)
	fmadds f6, f3, f2, f0
	lfs f2, float_1_rsh_00014470@l(r3)
	cror eq, lt, eq
	bne @L134
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f7, f1
	cror eq, lt, eq
	bne @L135
	fmuls f0, f7, f7
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fmuls f5, f5, f7
	b @L136
	@L135:
	fsubs f0, f7, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fmuls f5, f5, f1
	b @L136
	@L134:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f7, f0
	bge @L137
	fsubs f1, f7, f1
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fmuls f5, f5, f1
	fneg f5, f5
	b @L136
	@L137:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f7, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fmuls f5, f5, f1
	fneg f5, f5
	@L136:
	lis r3, float_3p1416_rsh_000144ac@ha
	lwz r6, 0xc(r30)
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r5, float_0p03705_rsh_000144b8@ha
	lfs f0, 0xc(r6)
	lis r4, float_0p4967_rsh_000144bc@ha
	fcmpo cr0, f7, f1
	lis r3, float_1_rsh_00014470@ha
	fmadds f29, f6, f5, f0
	lfs f4, float_0p03705_rsh_000144b8@l(r5)
	lfs f3, float_0p4967_rsh_000144bc@l(r4)
	lfs f2, float_1_rsh_00014470@l(r3)
	cror eq, lt, eq
	bne @L138
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f7, f1
	cror eq, lt, eq
	bne @L139
	fmuls f0, f7, f7
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @L140
	@L139:
	fsubs f0, f7, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @L140
	@L138:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f7, f0
	bge @L141
	fsubs f0, f7, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @L140
	@L141:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f7, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@L140:
	lfs f0, 0x2c(r6)
	fnmsubs f30, f6, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f1, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfs f2, 0x0(r5)
	lis r4, float_1_rsh_00014470@ha
	lfd f0, 0xa8(r1)
	lis r3, float_5_rsh_00014500@ha
	fsubs f3, f0, f1
	lfs f1, float_1_rsh_00014470@l(r4)
	lfs f0, float_5_rsh_00014500@l(r3)
	fdivs f2, f3, f2
	fmadds f26, f2, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xa4(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f1, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa0(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfs f2, 0x0(r5)
	lis r4, float_0p1_rsh_00014548@ha
	lfd f0, 0xa0(r1)
	lis r3, float_0p2_rsh_00014544@ha
	cmpwi r26, 0x0
	fsubs f3, f0, f1
	lfs f1, float_0p1_rsh_00014548@l(r4)
	lfs f0, float_0p2_rsh_00014544@l(r3)
	fdivs f2, f3, f2
	fmadds f27, f2, f1, f0
	bne @L142
	lis r3, vec3_rsh_00013da0@ha
	addi r4, r1, 0x20
	addi r7, r3, vec3_rsh_00013da0@l
	li r3, 0x6c3
	lwz r6, 0x0(r7)
	lwz r5, 0x4(r7)
	lwz r0, 0x8(r7)
	stw r6, 0x20(r1)
	stw r5, 0x24(r1)
	stw r0, 0x28(r1)
	lwz r5, 0xc(r30)
	lfs f0, 0xc(r5)
	stfs f0, 0x20(r1)
	lfs f0, 0x1c(r5)
	stfs f0, 0x24(r1)
	lfs f0, 0x2c(r5)
	stfs f0, 0x28(r1)
	bl psndSFXOn_3D
	li r26, 0x1
	@L142:
	lis r3, float_neg100_rsh_0001454c@ha
	fmr f1, f29
	lfs f2, float_neg100_rsh_0001454c@l(r3)
	fmr f3, f30
	fmr f4, f26
	mr r3, r30
	fmr f5, f27
	mr r4, r31
	li r5, 0x31
	li r6, 0x0
	bl moamoa_jump
	b @64
	@L143:
	entry jt_0000ACC8
	lha r3, 0x18(r31)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x18(r31)
	ble @L144
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
	b @64
	@L144:
	li r0, 0x31
	sth r0, 0x2(r31)
	b @64
	@L145:
	entry jt_0000AD58
	lwz r3, 0xc(r30)
	bl PSMTXIdentity
	lis r3, wp@ha
	li r21, 0x2bc
	addi r22, r3, wp@l
	@L146:
	bl rand
	divw r0, r3, r21
	lwz r4, 0x0(r22)
	lwz r4, 0x8(r4)
	mullw r0, r0, r21
	subf r18, r0, r3
	mulli r0, r18, 0x50
	add r4, r4, r0
	lha r3, 0x2(r4)
	extsh. r0, r3
	beq @L147
	cmpwi r3, 0x3
	bne @L146
	@L147:
	lhz r0, 0x0(r4)
	rlwinm. r0, r0, 0, 25, 25
	bne @L146
	bl extGetPosePtr
	slwi r0, r18, 5
	lis r4, float_215_rsh_00014504@ha
	add r7, r3, r0
	lwz r5, 0xc(r30)
	lwz r6, 0xc(r7)
	li r0, 0x0
	lfs f0, float_215_rsh_00014504@l(r4)
	lfs f1, 0xc(r6)
	stfs f1, 0xc(r5)
	lwz r3, 0xc(r30)
	stfs f0, 0x1c(r3)
	lwz r4, 0xc(r7)
	lwz r3, 0xc(r30)
	lfs f0, 0x2c(r4)
	stfs f0, 0x2c(r3)
	sth r0, 0x0(r31)
	sth r0, 0x2(r31)
	sth r0, 0x4(r31)
	b @64
	@L148:
	entry jt_0000ADFC
	lhz r0, 0x0(r31)
	ori r0, r0, 0x20
	sth r0, 0x0(r31)
	lwz r0, 0x0(r30)
	clrrwi r0, r0, 1
	stw r0, 0x0(r30)
	lwz r0, 0x0(r30)
	ori r0, r0, 0x4
	stw r0, 0x0(r30)
	b @64
	@L149:
	entry jt_0000AE24
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lis r3, float_32767_rsh_000144ec@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	stw r0, 0xa8(r1)
	lfs f0, float_32767_rsh_000144ec@l(r3)
	lfd f1, 0xa8(r1)
	fsubs f1, f1, f2
	fdivs f27, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xa4(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f1, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa0(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfs f2, 0x0(r5)
	lis r4, float_1_rsh_00014470@ha
	lfd f0, 0xa0(r1)
	lis r3, float_2_rsh_00014514@ha
	srawi r0, r29, 1
	fsubs f3, f0, f1
	lfs f0, float_2_rsh_00014514@l(r3)
	lfs f1, float_1_rsh_00014470@l(r4)
	addze r3, r0
	fdivs f2, f3, f2
	fmadds f30, f2, f1, f0
	bl irand
	lis r5, float_90_rsh_00014534@ha
	lis r4, float_225_rsh_00014550@ha
	lfs f1, float_90_rsh_00014534@l(r5)
	lis r7, float_0p00761_rsh_000144a4@ha
	lfs f0, float_225_rsh_00014550@l(r4)
	lis r6, float_6p2832_rsh_0001449c@ha
	lis r5, float_360_rsh_000144a0@ha
	lis r4, float_3p1416_rsh_000144ac@ha
	fmadds f0, f27, f1, f0
	lfs f1, float_6p2832_rsh_0001449c@l(r6)
	lis r6, float_0p16605_rsh_000144a8@ha
	sth r3, 0x4(r31)
	lfs f4, float_0p00761_rsh_000144a4@l(r7)
	fmuls f2, f1, f0
	lfs f0, float_360_rsh_000144a0@l(r5)
	lis r5, float_1_rsh_00014470@ha
	lfs f1, float_3p1416_rsh_000144ac@l(r4)
	fdivs f29, f2, f0
	lfs f3, float_0p16605_rsh_000144a8@l(r6)
	lfs f2, float_1_rsh_00014470@l(r5)
	fcmpo cr0, f29, f1
	cror eq, lt, eq
	bne @L150
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f29, f1
	cror eq, lt, eq
	bne @L151
	fmuls f0, f29, f29
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f29
	b @L152
	@L151:
	fsubs f0, f29, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @L152
	@L150:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f29, f0
	bge @L153
	fsubs f1, f29, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @L152
	@L153:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f29, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@L152:
	fmuls f0, f30, f4
	stfs f0, 0x8(r31)
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_rsh_00014488@ha
	stw r3, 0xac(r1)
	addi r5, r4, double_to_int_rsh_00014488@l
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa8(r1)
	addi r4, r3, float_32767_rsh_000144ec@l
	lfd f2, 0x0(r5)
	lis r3, float_1_rsh_00014470@ha
	lfd f1, 0xa8(r1)
	addi r5, r3, float_1_rsh_00014470@l
	lfs f0, 0x0(r4)
	lis r4, float_0p03705_rsh_000144b8@ha
	fsubs f3, f1, f2
	lis r3, float_3p1416_rsh_000144ac@ha
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r3, float_0p4967_rsh_000144bc@ha
	lfs f2, 0x0(r5)
	fdivs f0, f3, f0
	lfs f4, float_0p03705_rsh_000144b8@l(r4)
	lfs f3, float_0p4967_rsh_000144bc@l(r3)
	fmadds f0, f0, f2, f2
	fcmpo cr0, f29, f1
	stfs f0, 0xc(r31)
	cror eq, lt, eq
	bne @L154x
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fcmpo cr0, f29, f1
	cror eq, lt, eq
	bne @L155
	fmuls f0, f29, f29
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @L156
	@L155:
	fsubs f0, f29, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @L156
	@L154x:
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f29, f0
	bge @L157
	fsubs f0, f29, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @L156
	@L157:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f29, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@L156:
	fneg f0, f4
	fmuls f0, f30, f0
	stfs f0, 0x10(r31)
	lha r3, 0x2(r31)
	addi r0, r3, 0x1
	sth r0, 0x2(r31)
	b @64
	@L158:
	entry jt_0000B0B0
	lha r3, 0x4(r31)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x4(r31)
	bge @64
	lha r3, 0x2(r31)
	addi r0, r3, 0x1
	sth r0, 0x2(r31)
	b @64
	@L159:
	entry jt_0000B0D4
	lis r3, float_1p1_rsh_00014554@ha
	lis r4, float_1p02_rsh_00014558@ha
	addi r6, r3, float_1p1_rsh_00014554@l
	lis r3, float_0p20944_rsh_0001455c@ha
	lfs f1, 0x8(r31)
	addi r5, r4, float_1p02_rsh_00014558@l
	lfs f3, 0x0(r6)
	addi r4, r3, float_0p20944_rsh_0001455c@l
	lfs f0, 0x0(r5)
	addi r3, r1, 0x5c
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
	addi r4, r1, 0x5c
	mr r5, r3
	bl PSMTXConcat
	lwz r0, 0x0(r30)
	lis r3, float_neg1000_rsh_00014560@ha
	lfs f0, float_neg1000_rsh_00014560@l(r3)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r30)
	lwz r3, 0xc(r30)
	lfs f1, 0xc(r3)
	fcmpo cr0, f1, f0
	bge @64
	li r0, 0x3e
	sth r0, 0x2(r31)
	@64:
	entry jt_0000B1A0
	lhz r0, 0x0(r31)
	andi. r0, r0, 0x588
	bne @L160
	lwz r5, 0xc(r30)
	lis r3, float_250_rsh_00014564@ha
	lfs f3, 0x18(r23)
	lfs f2, 0xc(r5)
	lfs f1, float_250_rsh_00014564@l(r3)
	fsubs f0, f3, f2
	fcmpo cr0, f0, f1
	ble @L161
	lis r4, float_450_rsh_00014568@ha
	lis r3, float_neg50_rsh_0001456c@ha
	lfs f1, float_450_rsh_00014568@l(r4)
	lfs f0, float_neg50_rsh_0001456c@l(r3)
	fadds f1, f1, f2
	fcmpo cr0, f1, f0
	bge @L160
	stfs f1, 0xc(r5)
	b @L160
	@L161:
	fsubs f0, f2, f3
	fcmpo cr0, f0, f1
	ble @L160
	lis r4, float_450_rsh_00014568@ha
	lis r3, float_neg1870_rsh_00014570@ha
	lfs f1, float_450_rsh_00014568@l(r4)
	lfs f0, float_neg1870_rsh_00014570@l(r3)
	fsubs f1, f2, f1
	fcmpo cr0, f1, f0
	ble @L160
	stfs f1, 0xc(r5)
	@L160:
	lhz r0, 0x0(r31)
	andi. r0, r0, 0x588
	bne @L162
	lwz r4, 0xc(r30)
	lis r3, float_100_rsh_000144f8@ha
	lfs f0, float_100_rsh_000144f8@l(r3)
	lfs f1, 0xc(r4)
	fcmpo cr0, f1, f0
	ble @L163
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f1, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfs f2, 0x0(r5)
	lis r4, float_5_rsh_00014500@ha
	lfd f0, 0xa8(r1)
	lis r3, zero_rsh_00014490@ha
	lis r5, float_100_rsh_000144f8@ha
	fsubs f3, f0, f1
	lfs f0, zero_rsh_00014490@l(r3)
	lfs f1, float_5_rsh_00014500@l(r4)
	lwz r3, 0xc(r30)
	fdivs f3, f3, f2
	lfs f2, float_100_rsh_000144f8@l(r5)
	fmadds f0, f3, f1, f0
	fadds f0, f2, f0
	stfs f0, 0xc(r3)
	@L163:
	lwz r4, 0xc(r30)
	lis r3, float_neg1870_rsh_00014570@ha
	lfs f0, float_neg1870_rsh_00014570@l(r3)
	lfs f1, 0xc(r4)
	fcmpo cr0, f1, f0
	bge @L164
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f1, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfs f2, 0x0(r5)
	lis r4, float_5_rsh_00014500@ha
	lfd f0, 0xa8(r1)
	lis r3, zero_rsh_00014490@ha
	lis r5, float_neg1870_rsh_00014570@ha
	fsubs f3, f0, f1
	lfs f0, zero_rsh_00014490@l(r3)
	lfs f1, float_5_rsh_00014500@l(r4)
	lwz r3, 0xc(r30)
	fdivs f3, f3, f2
	lfs f2, float_neg1870_rsh_00014570@l(r5)
	fmadds f0, f3, f1, f0
	fadds f0, f2, f0
	stfs f0, 0xc(r3)
	@L164:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 25, 25
	bne @L162
	lwz r4, 0xc(r30)
	lis r3, float_45_rsh_00014574@ha
	lfs f0, float_45_rsh_00014574@l(r3)
	lfs f1, 0x2c(r4)
	fcmpo cr0, f1, f0
	ble @L165
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f1, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfs f2, 0x0(r5)
	lis r4, float_5_rsh_00014500@ha
	lfd f0, 0xa8(r1)
	lis r3, zero_rsh_00014490@ha
	lis r5, float_45_rsh_00014574@ha
	fsubs f3, f0, f1
	lfs f0, zero_rsh_00014490@l(r3)
	lfs f1, float_5_rsh_00014500@l(r4)
	lwz r3, 0xc(r30)
	fdivs f3, f3, f2
	lfs f2, float_45_rsh_00014574@l(r5)
	fmadds f0, f3, f1, f0
	fadds f0, f2, f0
	stfs f0, 0x2c(r3)
	@L165:
	lwz r4, 0xc(r30)
	lis r3, float_neg45_rsh_00014530@ha
	lfs f0, float_neg45_rsh_00014530@l(r3)
	lfs f1, 0x2c(r4)
	fcmpo cr0, f1, f0
	bge @L162
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f1, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfs f2, 0x0(r5)
	lis r4, float_5_rsh_00014500@ha
	lfd f0, 0xa8(r1)
	lis r3, zero_rsh_00014490@ha
	lis r5, float_neg45_rsh_00014530@ha
	fsubs f3, f0, f1
	lfs f0, zero_rsh_00014490@l(r3)
	lfs f1, float_5_rsh_00014500@l(r4)
	lwz r3, 0xc(r30)
	fdivs f3, f3, f2
	lfs f2, float_neg45_rsh_00014530@l(r5)
	fmadds f0, f3, f1, f0
	fadds f0, f2, f0
	stfs f0, 0x2c(r3)
	@L162:
	lwz r3, 0xc(r30)
	addi r29, r29, 0x1
	lfs f0, 0xc(r3)
	stfs f0, 0x28(r31)
	lwz r3, 0xc(r30)
	addi r30, r30, 0x20
	lfs f0, 0x2c(r3)
	stfs f0, 0x2c(r31)
	addi r31, r31, 0x50
	@16:
	lwz r3, 0x0(r27)
	lwz r0, 0x4(r3)
	cmpw r29, r0
	blt @17
	bl extGetPosePtr
	lis r4, wp@ha
	lis r7, float_60_rsh_00014578@ha
	addi r25, r4, wp@l
	lis r6, float_1000_rsh_0001457c@ha
	lwz r9, 0x0(r25)
	lis r5, float_1_rsh_00014470@ha
	lis r4, double_to_int_rsh_00014488@ha
	lis r8, gp@ha
	lwz r18, 0x8(r9)
	mr r19, r3
	lfs f30, float_60_rsh_00014578@l(r7)
	addi r24, r8, gp@l
	lfs f29, float_1000_rsh_0001457c@l(r6)
	li r20, 0x0
	lfs f28, float_1_rsh_00014470@l(r5)
	lis r23, 0x8000
	lfd f27, double_to_int_rsh_00014488@l(r4)
	lis r26, 0x4330
	b @L166
	@L167:
	lwz r3, 0xf8(r23)
	li r0, 0x3e8
	lwz r4, 0x0(r24)
	li r5, 0x0
	srwi r3, r3, 2
	lha r8, 0x3c(r18)
	divwu r6, r3, r0
	lwz r22, 0x3c(r4)
	lwz r0, 0x44(r18)
	lwz r21, 0x38(r4)
	subfc r4, r0, r22
	lwz r0, 0x40(r18)
	mulli r8, r8, 0x28
	subfe r3, r0, r21
	addi r17, r8, 0x50
	add r17, r7, r17
	bl __div2u
	bl __cvt_ull_flt
	fmuls f1, f30, f1
	lfs f0, 0x1c(r17)
	fdivs f1, f1, f29
	fdivs f1, f1, f0
	fcmpo cr0, f1, f28
	cror eq, gt, eq
	bne @L168
	stw r22, 0x44(r18)
	lis r3, zero_rsh_00014490@ha
	lfs f1, zero_rsh_00014490@l(r3)
	stw r21, 0x40(r18)
	@L168:
	lwz r3, 0x24(r17)
	addi r20, r20, 0x1
	stw r26, 0xa8(r1)
	addi r18, r18, 0x50
	subi r0, r3, 0x1
	lwz r3, 0x20(r17)
	xoris r0, r0, 0x8000
	stw r0, 0xac(r1)
	lfd f0, 0xa8(r1)
	fsubs f0, f0, f27
	fmuls f0, f0, f1
	fctiwz f0, f0
	stfd f0, 0xa0(r1)
	lwz r0, 0xa4(r1)
	add r0, r3, r0
	stw r0, 0x10(r19)
	addi r19, r19, 0x20
	@L166:
	lwz r7, 0x0(r25)
	lwz r0, 0x4(r7)
	cmpw r20, r0
	blt @L167
	lis r4, zero_rsh_00014490@ha
	lis r3, wp@ha
	lfs f0, zero_rsh_00014490@l(r4)
	addi r3, r3, wp@l
	stfs f0, 0x174(r28)
	stfs f0, 0x178(r28)
	stfs f0, 0x17c(r28)
	lwz r3, 0x0(r3)
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 27, 28
	bne @L169
	lis r3, float_20_rsh_00014580@ha
	fneg f1, f31
	lfs f0, float_20_rsh_00014580@l(r3)
	fdivs f0, f1, f0
	stfs f0, 0x174(r28)
	@L169:
	psq_l f31, 0x148(r1), 0, 0
	lfd f31, 0x140(r1)
	psq_l f30, 0x138(r1), 0, 0
	lfd f30, 0x130(r1)
	psq_l f29, 0x128(r1), 0, 0
	lfd f29, 0x120(r1)
	psq_l f28, 0x118(r1), 0, 0
	lfd f28, 0x110(r1)
	psq_l f27, 0x108(r1), 0, 0
	lfd f27, 0x100(r1)
	psq_l f26, 0xf8(r1), 0, 0
	lfd f26, 0xf0(r1)
	lmw r17, 0xb4(r1)
	lwz r0, 0x154(r1)
	mtlr r0
	addi r1, r1, 0x150
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
	lis r4, float_20_rsh_00014580@ha
	lfs f0, float_20_rsh_00014580@l(r4)
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
	lis r4, float_20_rsh_00014580@ha
	lis r3, float_0p5_rsh_000144e8@ha
	lfs f2, 0x1b4(r31)
	lfs f3, float_20_rsh_00014580@l(r4)
	lfs f0, float_0p5_rsh_000144e8@l(r3)
	fadds f2, f3, f2
	fmuls f0, f2, f0
	fcmpo cr0, f1, f0
	bge @4
	lwz r3, 0xc(r29)
	lis r4, float_10_rsh_00014584@ha
	lfs f1, float_10_rsh_00014584@l(r4)
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
	lis r4, float_90_rsh_00014534@ha
	lfs f1, 0x1a8(r31)
	lfs f0, float_90_rsh_00014534@l(r4)
	lfs f2, 0x114(r3)
	fsubs f0, f1, f0
	fadds f1, f0, f2
	bl reviseAngle
	lis r3, float_6p2832_rsh_0001449c@ha
	lis r6, float_0p00761_rsh_000144a4@ha
	addi r5, r3, float_6p2832_rsh_0001449c@l
	lis r4, float_360_rsh_000144a0@ha
	lfs f0, 0x0(r5)
	lis r5, float_0p16605_rsh_000144a8@ha
	lis r3, float_3p1416_rsh_000144ac@ha
	lfs f4, float_0p00761_rsh_000144a4@l(r6)
	fmuls f2, f0, f1
	lfs f0, float_360_rsh_000144a0@l(r4)
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r4, float_1_rsh_00014470@ha
	lfs f3, float_0p16605_rsh_000144a8@l(r5)
	fdivs f6, f2, f0
	lfs f2, float_1_rsh_00014470@l(r4)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @8
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
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
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@10:
	lis r3, float_3p1416_rsh_000144ac@ha
	lis r4, float_35_rsh_00014588@ha
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r5, float_0p03705_rsh_000144b8@ha
	lfs f2, float_35_rsh_00014588@l(r4)
	lis r4, float_0p4967_rsh_000144bc@ha
	lfs f0, 0x8c(r31)
	fcmpo cr0, f6, f1
	lis r3, float_1_rsh_00014470@ha
	lfs f5, float_0p03705_rsh_000144b8@l(r5)
	fmadds f3, f2, f4, f0
	lfs f4, float_0p4967_rsh_000144bc@l(r4)
	lfs f2, float_1_rsh_00014470@l(r3)
	cror eq, lt, eq
	bne @12
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f6, f0
	bge @15
	fsubs f0, f6, f1
	fmuls f0, f0, f0
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fneg f5, f5
	b @14
	@15:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	@14:
	lis r3, float_35_rsh_00014588@ha
	lwz r4, 0xc(r29)
	lfs f0, 0x94(r31)
	lfs f2, float_35_rsh_00014588@l(r3)
	lfs f1, 0xc(r4)
	fnmsubs f4, f2, f5, f0
	lfs f2, 0x2c(r4)
	bl distABf
	lis r3, float_35_rsh_00014588@ha
	lfs f0, float_35_rsh_00014588@l(r3)
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
	lis r3, vec3_rsh_00013d34@ha
	lwz r8, 0xc(r29)
	addi r7, r3, vec3_rsh_00013d34@l
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
	lis r3, float_65_rsh_0001458c@ha
	lfs f0, float_65_rsh_0001458c@l(r3)
	fcmpo cr0, f1, f0
	bge @16
	li r3, 0x2
	b @2
	@16:
	lis r4, wp@ha
	lis r3, zero_rsh_00014490@ha
	addi r4, r4, wp@l
	lfs f0, zero_rsh_00014490@l(r3)
	lwz r4, 0x0(r4)
	lfs f1, 0x55c(r4)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @17
	lis r3, vec3_rsh_00013d40@ha
	lwz r8, 0xc(r29)
	addi r7, r3, vec3_rsh_00013d40@l
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
	lis r3, float_30_rsh_000144dc@ha
	lfs f0, float_30_rsh_000144dc@l(r3)
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
	lis r3, vec3_rsh_00013d4c@ha
	lwz r7, 0xc(r29)
	addi r6, r3, vec3_rsh_00013d4c@l
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
	lis r3, float_30_rsh_000144dc@ha
	lfs f0, float_30_rsh_000144dc@l(r3)
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
	lis r3, vec3_rsh_00013d58@ha
	lwz r7, 0xc(r29)
	addi r6, r3, vec3_rsh_00013d58@l
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
	lis r3, float_50_rsh_000144fc@ha
	lfs f0, float_50_rsh_000144fc@l(r3)
	fcmpo cr0, f1, f0
	bge @19
	li r3, 0x4
	b @2
	@19:
	lis r3, vec3_rsh_00013d64@ha
	lwz r11, 0xc(r29)
	addi r5, r3, vec3_rsh_00013d64@l
	lis r3, vec3_rsh_00013d70@ha
	lwz r4, 0x0(r5)
	addi r9, r3, vec3_rsh_00013d70@l
	lwz r0, 0x4(r5)
	lis r3, float_20_rsh_00014580@ha
	lwz r10, 0x8(r5)
	addi r6, r3, float_20_rsh_00014580@l
	stw r4, 0x20(r1)
	lis r3, float_0p5_rsh_000144e8@ha
	lfs f0, 0x8c(r31)
	addi r5, r3, float_0p5_rsh_000144e8@l
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
	lis r3, vec3_rsh_00013d7c@ha
	lwz r5, 0xc(r29)
	addi r7, r3, vec3_rsh_00013d7c@l
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
	lis r3, float_40_rsh_00014590@ha
	fabs f1, f1
	lfs f0, float_40_rsh_00014590@l(r3)
	fcmpo cr0, f1, f0
	bge @21
	lis r3, float_6p2832_rsh_0001449c@ha
	lis r6, float_0p00761_rsh_000144a4@ha
	addi r5, r3, float_6p2832_rsh_0001449c@l
	lfs f0, 0x1a0(r31)
	lfs f1, 0x0(r5)
	lis r5, float_0p16605_rsh_000144a8@ha
	lis r4, float_360_rsh_000144a0@ha
	lis r3, float_3p1416_rsh_000144ac@ha
	fmuls f2, f1, f0
	lfs f0, float_360_rsh_000144a0@l(r4)
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r4, float_1_rsh_00014470@ha
	lfs f4, float_0p00761_rsh_000144a4@l(r6)
	fdivs f5, f2, f0
	lfs f3, float_0p16605_rsh_000144a8@l(r5)
	lfs f2, float_1_rsh_00014470@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @22
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
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
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f5, f1, f0
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	fneg f4, f4
	@24:
	fsubs f6, f31, f29
	lis r3, float_6p2832_rsh_0001449c@ha
	addi r8, r3, float_6p2832_rsh_0001449c@l
	lis r6, float_0p03705_rsh_000144b8@ha
	lis r3, float_360_rsh_000144a0@ha
	lfs f3, 0x0(r8)
	fmuls f0, f6, f4
	addi r7, r3, float_360_rsh_000144a0@l
	lis r5, float_0p4967_rsh_000144bc@ha
	lis r3, float_3p1416_rsh_000144ac@ha
	lis r4, float_1_rsh_00014470@ha
	lfs f5, float_0p03705_rsh_000144b8@l(r6)
	fneg f1, f0
	lfs f0, 0x0(r7)
	lfs f4, float_0p4967_rsh_000144bc@l(r5)
	stfs f1, 0x174(r31)
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lfs f2, 0x1a0(r31)
	fmuls f2, f3, f2
	lfs f3, float_1_rsh_00014470@l(r4)
	fdivs f2, f2, f0
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @26
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f2, f0
	bge @29
	fsubs f2, f2, f1
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fneg f5, f5
	b @28
	@29:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f2, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	@28:
	fmuls f0, f6, f5
	stfs f0, 0x17c(r31)
	b @20
	@21:
	lis r3, float_6p2832_rsh_0001449c@ha
	lis r6, float_0p00761_rsh_000144a4@ha
	addi r5, r3, float_6p2832_rsh_0001449c@l
	lis r4, float_360_rsh_000144a0@ha
	lfs f0, 0x0(r5)
	lis r3, float_3p1416_rsh_000144ac@ha
	lis r5, float_0p16605_rsh_000144a8@ha
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	fmuls f2, f0, f30
	lfs f0, float_360_rsh_000144a0@l(r4)
	lis r4, float_1_rsh_00014470@ha
	lfs f4, float_0p00761_rsh_000144a4@l(r6)
	lfs f3, float_0p16605_rsh_000144a8@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_rsh_00014470@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @30
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
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
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@32:
	lwz r4, 0xc(r29)
	lis r3, float_3p1416_rsh_000144ac@ha
	lfs f1, float_3p1416_rsh_000144ac@l(r3)
	lis r5, float_0p03705_rsh_000144b8@ha
	lfs f0, 0xc(r4)
	lis r4, float_0p4967_rsh_000144bc@ha
	fcmpo cr0, f5, f1
	lis r3, float_1_rsh_00014470@ha
	fnmsubs f2, f31, f4, f0
	lfs f0, 0x8c(r31)
	lfs f4, float_0p03705_rsh_000144b8@l(r5)
	lfs f3, float_0p4967_rsh_000144bc@l(r4)
	fsubs f0, f2, f0
	lfs f2, float_1_rsh_00014470@l(r3)
	stfs f0, 0x174(r31)
	cror eq, lt, eq
	bne @34
	lis r3, float_1p5708_rsh_000144b0@ha
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
	lis r3, float_4p7124_rsh_000144b4@ha
	lfs f0, float_4p7124_rsh_000144b4@l(r3)
	fcmpo cr0, f5, f0
	bge @37
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @36
	@37:
	lis r3, float_1p5708_rsh_000144b0@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_000144b0@l(r3)
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
	lis r4, zero_rsh_00014490@ha
	lis r3, float_100_rsh_000144f8@ha
	addi r5, r4, zero_rsh_00014490@l
	lfs f0, float_100_rsh_000144f8@l(r3)
	lfs f4, 0x0(r5)
	lis r4, float_1E06_rsh_00014594@ha
	lfs f7, float_1E06_rsh_00014594@l(r4)
	lis r3, float_neg1_rsh_00014498@ha
	fmr f6, f4
	lfs f5, float_neg1_rsh_00014498@l(r3)
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
	lis r3, double_30_rsh_00014598@ha
	fsubs f1, f28, f0
	lfd f0, double_30_rsh_00014598@l(r3)
	fabs f1, f1
	fcmpo cr0, f1, f0
	ble @2
	lis r3, float_0p1_rsh_000144f0@ha
	lfs f0, float_0p1_rsh_000144f0@l(r3)
	fsubs f31, f31, f0
	fadds f30, f30, f0
	@2:
	lfs f28, 0x1c(r1)
	@1:
	lis r3, vec3_rsh_00013d28@ha
	addi r4, r3, vec3_rsh_00013d28@l
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
	lis r4, double_to_int_rsh_00014488@ha
	lis r3, float_0p5_rsh_000144e8@ha
	fdivs f0, f31, f0
	addi r6, r4, double_to_int_rsh_00014488@l
	addi r4, r3, float_0p5_rsh_000144e8@l
	lis r3, float_180_rsh_00014538@ha
	stw r5, 0x40(r1)
	li r0, 0x3
	fctiwz f2, f0
	lfs f0, float_180_rsh_00014538@l(r3)
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
	lis r3, fs_mt@ha
	addi r3, r3, fs_mt@l
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
	lis r3, str_00004B00@ha
	addi r3, r3, str_00004B00@l
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
	lis r3, str_00004B00@ha
	addi r3, r3, str_00004B00@l
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
	stwu r1, -0x150(r1)
	mflr r0
	stw r0, 0x154(r1)
	stfd f31, 0x140(r1)
	psq_st f31, 0x148(r1), 0, 0
	stfd f30, 0x130(r1)
	psq_st f30, 0x138(r1), 0, 0
	stfd f29, 0x120(r1)
	psq_st f29, 0x128(r1), 0, 0
	stfd f28, 0x110(r1)
	psq_st f28, 0x118(r1), 0, 0
	stfd f27, 0x100(r1)
	psq_st f27, 0x108(r1), 0, 0
	stfd f26, 0xf0(r1)
	psq_st f26, 0xf8(r1), 0, 0
	stfd f25, 0xe0(r1)
	psq_st f25, 0xe8(r1), 0, 0
	stfd f24, 0xd0(r1)
	psq_st f24, 0xd8(r1), 0, 0
	stfd f23, 0xc0(r1)
	psq_st f23, 0xc8(r1), 0, 0
	stfd f22, 0xb0(r1)
	psq_st f22, 0xb8(r1), 0, 0
	stfd f21, 0xa0(r1)
	psq_st f21, 0xa8(r1), 0, 0
	stfd f20, 0x90(r1)
	psq_st f20, 0x98(r1), 0, 0
	stmw r17, 0x54(r1)
	li r3, 0x870
	bl _mapAlloc
	lis r5, wp@ha
	li r4, 0x0
	addi r6, r5, wp@l
	li r5, 0x870
	stw r3, 0x0(r6)
	bl memset
	lis r5, wp@ha
	lis r3, vec3_rsh_00013cf8@ha
	addi r7, r3, vec3_rsh_00013cf8@l
	lis r4, vec3_rsh_00013d04@ha
	addi r9, r5, wp@l
	lwz r6, 0x0(r7)
	lwz r8, 0x0(r9)
	lis r3, vec3_rsh_00013d10@ha
	lwz r0, 0x4(r7)
	addi r5, r4, vec3_rsh_00013d04@l
	addi r4, r3, vec3_rsh_00013d10@l
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
	lis r17, zero_rsh_00014490@ha
	addi r25, r4, wp@l
	lis r12, double_to_int_rsh_00014488@ha
	lwz r22, 0x0(r25)
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
	lis r24, str_000041DC@ha
	lis r21, str_000041D0@ha
	lis r20, vec3_rsh_00013d1c@ha
	lis r17, float_neg1_rsh_00014498@ha
	lwz r31, 0x8(r22)
	addi r26, r24, str_000041DC@l
	lfd f20, double_to_int_rsh_00014488@l(r12)
	mr r23, r3
	lfs f21, float_32767_rsh_000144ec@l(r11)
	addi r27, r21, str_000041D0@l
	lfs f22, float_1000_rsh_0001457c@l(r10)
	addi r22, r17, float_neg1_rsh_00014498@l
	lfs f23, float_neg500_rsh_000145ac@l(r9)
	addi r30, r20, vec3_rsh_00013d1c@l
	lfs f24, float_215_rsh_00014504@l(r8)
	li r24, 0x0
	lfs f25, float_90_rsh_00014534@l(r7)
	lis r28, 0x4330
	lfs f26, float_neg45_rsh_00014530@l(r6)
	lfs f27, 0x0(r29)
	lfs f28, float_1E06_rsh_00014594@l(r5)
	lfs f29, float_100_rsh_000144f8@l(r4)
	lfs f30, float_20_rsh_00014580@l(r19)
	lfs f31, float_neg10_rsh_000145b8@l(r18)
	b @1
	@2:
	li r0, 0x0
	mr r18, r26
	sth r0, 0x0(r31)
	mr r19, r27
	sth r0, 0x2(r31)
	sth r0, 0x4(r31)
	lhz r0, 0x0(r31)
	lwz r3, 0x0(r25)
	rlwinm. r0, r0, 0, 20, 20
	addi r20, r3, 0x50
	beq @3
	lbz r4, 0x4c(r31)
	lis r3, fs_group_tbl@ha
	addi r0, r3, fs_group_tbl@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r19, 0x0(r3)
	blt @4
	lwz r18, 0x4(r3)
	@4:
	cmplwi r4, 0xa
	bne @3
	lis r3, str_000048C4@ha
	addi r18, r3, str_000048C4@l
	@3:
	li r21, 0x0
	b @5
	@6:
	mr r3, r20
	mr r4, r19
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	mr r4, r18
	addi r3, r20, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @8
	@7:
	addi r21, r21, 0x1
	addi r20, r20, 0x28
	@5:
	lwz r3, 0x0(r25)
	lwz r0, 0x4c(r3)
	cmpw r21, r0
	blt @6
	@8:
	lwz r3, 0x0(r25)
	lwz r0, 0x4c(r3)
	cmpw r21, r0
	bge @9
	lha r0, 0x3c(r31)
	cmpw r0, r21
	beq @9
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 29, 29
	beq @10
	lis r4, str_00004A40@ha
	mr r3, r18
	addi r4, r4, str_00004A40@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @9
	@10:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 27, 27
	beq @11
	lis r4, str_00004A44@ha
	mr r3, r18
	addi r4, r4, str_00004A44@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @9
	@11:
	lis r3, gp@ha
	sth r21, 0x3c(r31)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x44(r31)
	stw r0, 0x40(r31)
	@9:
	lwz r0, 0x0(r23)
	ori r0, r0, 0x7
	stw r0, 0x0(r23)
	lwz r3, 0xc(r23)
	bl PSMTXIdentity
	bl rand
	xoris r0, r3, 0x8000
	stw r28, 0x30(r1)
	lwz r3, 0xc(r23)
	stw r0, 0x34(r1)
	lfd f0, 0x30(r1)
	fsubs f0, f0, f20
	fdivs f0, f0, f21
	fmadds f0, f0, f22, f23
	stfs f0, 0xc(r3)
	lwz r3, 0xc(r23)
	stfs f24, 0x1c(r3)
	bl rand
	xoris r0, r3, 0x8000
	lfs f4, 0x0(r29)
	stw r0, 0x3c(r1)
	addi r4, r1, 0x20
	lwz r11, 0xc(r23)
	fmr f6, f4
	stw r28, 0x38(r1)
	addi r5, r1, 0x1c
	lfs f5, 0x0(r22)
	addi r6, r1, 0x18
	lfd f0, 0x38(r1)
	addi r7, r1, 0x14
	addi r8, r1, 0x10
	fsubs f0, f0, f20
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	li r3, 0x0
	fdivs f0, f0, f21
	fmadds f0, f0, f25, f26
	stfs f0, 0x2c(r11)
	stfs f27, 0x18(r1)
	stfs f27, 0x1c(r1)
	stfs f27, 0x20(r1)
	stfs f28, 0x14(r1)
	lwz r11, 0xc(r23)
	lfs f0, 0x1c(r11)
	lfs f1, 0xc(r11)
	fadds f2, f29, f0
	lfs f3, 0x2c(r11)
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @12
	lfs f0, 0x1c(r1)
	lwz r3, 0xc(r23)
	stfs f0, 0x1c(r3)
	b @13
	@12:
	lwz r0, 0x0(r23)
	ori r0, r0, 0x4
	stw r0, 0x0(r23)
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x3c(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f1, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0x38(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfs f2, 0x0(r5)
	lis r4, float_1000_rsh_0001457c@ha
	lfd f0, 0x38(r1)
	lis r3, float_neg500_rsh_000145ac@ha
	fsubs f3, f0, f1
	lfs f0, float_neg500_rsh_000145ac@l(r3)
	lfs f1, float_1000_rsh_0001457c@l(r4)
	lwz r3, 0xc(r23)
	fdivs f2, f3, f2
	fmadds f0, f2, f1, f0
	stfs f0, 0xc(r3)
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x34(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f1, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0x30(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfs f2, 0x0(r5)
	lis r4, float_115_rsh_000145b0@ha
	lfd f0, 0x30(r1)
	lis r3, float_100_rsh_000144f8@ha
	fsubs f3, f0, f1
	lfs f0, float_100_rsh_000144f8@l(r3)
	lfs f1, float_115_rsh_000145b0@l(r4)
	lwz r3, 0xc(r23)
	fdivs f2, f3, f2
	fmadds f0, f2, f1, f0
	stfs f0, 0x1c(r3)
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x44(r1)
	lis r4, double_to_int_rsh_00014488@ha
	lfd f2, double_to_int_rsh_00014488@l(r4)
	lis r3, float_32767_rsh_000144ec@ha
	stw r0, 0x40(r1)
	addi r5, r3, float_32767_rsh_000144ec@l
	lfs f0, 0x0(r5)
	lis r4, float_5_rsh_00014500@ha
	lfd f1, 0x40(r1)
	lis r3, float_70_rsh_000145b4@ha
	addi r7, r4, float_5_rsh_00014500@l
	lis r4, str_000041D0@ha
	fsubs f2, f1, f2
	addi r6, r3, float_70_rsh_000145b4@l
	addi r20, r4, str_000041D0@l
	lis r3, wp@ha
	lis r5, str_000041DC@ha
	lfs f1, 0x0(r7)
	fdivs f2, f2, f0
	lfs f0, 0x0(r6)
	lwz r4, 0xc(r23)
	addi r3, r3, wp@l
	addi r21, r5, str_000041DC@l
	fmadds f0, f2, f1, f0
	stfs f0, 0x2c(r4)
	lhz r0, 0x0(r31)
	ori r0, r0, 0x40
	sth r0, 0x0(r31)
	lhz r0, 0x0(r31)
	lwz r3, 0x0(r3)
	rlwinm. r0, r0, 0, 20, 20
	addi r19, r3, 0x50
	beq @14
	lbz r4, 0x4c(r31)
	lis r3, fs_group_tbl@ha
	addi r0, r3, fs_group_tbl@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r20, 0x0(r3)
	blt @15
	lwz r21, 0x4(r3)
	@15:
	cmplwi r4, 0xa
	bne @14
	lis r3, str_000048C4@ha
	addi r21, r3, str_000048C4@l
	@14:
	lis r3, wp@ha
	li r18, 0x0
	addi r17, r3, wp@l
	b @16
	@17:
	mr r3, r19
	mr r4, r20
	bl strcmp
	cmpwi r3, 0x0
	bne @18
	mr r4, r21
	addi r3, r19, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @19
	@18:
	addi r18, r18, 0x1
	addi r19, r19, 0x28
	@16:
	lwz r3, 0x0(r17)
	lwz r0, 0x4c(r3)
	cmpw r18, r0
	blt @17
	@19:
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x4c(r3)
	cmpw r18, r0
	bge @13
	lha r0, 0x3c(r31)
	cmpw r0, r18
	beq @13
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 29, 29
	beq @20
	lis r4, str_00004A40@ha
	mr r3, r21
	addi r4, r4, str_00004A40@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @13
	@20:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 27, 27
	beq @21
	lis r4, str_00004A44@ha
	mr r3, r21
	addi r4, r4, str_00004A44@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @13
	@21:
	lis r3, gp@ha
	sth r18, 0x3c(r31)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x44(r31)
	stw r0, 0x40(r31)
	@13:
	lwz r4, 0x0(r30)
	lwz r3, 0x4(r30)
	lwz r0, 0x8(r30)
	stw r4, 0x24(r1)
	stw r3, 0x28(r1)
	stw r0, 0x2c(r1)
	bl rand
	xoris r0, r3, 0x8000
	stw r28, 0x40(r1)
	stw r0, 0x44(r1)
	lfd f0, 0x40(r1)
	fsubs f0, f0, f20
	fdivs f0, f0, f21
	fmadds f0, f0, f30, f31
	stfs f0, 0x24(r1)
	bl rand
	xoris r0, r3, 0x8000
	stw r28, 0x38(r1)
	stw r0, 0x3c(r1)
	lfd f0, 0x38(r1)
	fsubs f0, f0, f20
	fdivs f0, f0, f21
	fmadds f0, f0, f30, f31
	stfs f0, 0x28(r1)
	bl rand
	xoris r0, r3, 0x8000
	lwz r3, 0x24(r1)
	stw r0, 0x34(r1)
	addi r24, r24, 0x1
	lwz r0, 0x28(r1)
	addi r23, r23, 0x20
	stw r28, 0x30(r1)
	lfd f0, 0x30(r1)
	stw r3, 0x30(r31)
	fsubs f0, f0, f20
	stw r0, 0x34(r31)
	fdivs f0, f0, f21
	fmadds f0, f0, f30, f31
	stfs f0, 0x2c(r1)
	lwz r0, 0x2c(r1)
	stw r0, 0x38(r31)
	addi r31, r31, 0x50
	@1:
	lwz r3, 0x0(r25)
	lwz r0, 0x4(r3)
	cmpw r24, r0
	blt @2
	bl evalOn
	li r17, 0x0
	@22:
	bl ext_moamoa_main
	addi r17, r17, 0x1
	cmpwi r17, 0x258
	blt @22
	psq_l f31, 0x148(r1), 0, 0
	lfd f31, 0x140(r1)
	psq_l f30, 0x138(r1), 0, 0
	lfd f30, 0x130(r1)
	psq_l f29, 0x128(r1), 0, 0
	lfd f29, 0x120(r1)
	psq_l f28, 0x118(r1), 0, 0
	lfd f28, 0x110(r1)
	psq_l f27, 0x108(r1), 0, 0
	lfd f27, 0x100(r1)
	psq_l f26, 0xf8(r1), 0, 0
	lfd f26, 0xf0(r1)
	psq_l f25, 0xe8(r1), 0, 0
	lfd f25, 0xe0(r1)
	psq_l f24, 0xd8(r1), 0, 0
	lfd f24, 0xd0(r1)
	psq_l f23, 0xc8(r1), 0, 0
	lfd f23, 0xc0(r1)
	psq_l f22, 0xb8(r1), 0, 0
	lfd f22, 0xb0(r1)
	psq_l f21, 0xa8(r1), 0, 0
	lfd f21, 0xa0(r1)
	psq_l f20, 0x98(r1), 0, 0
	lfd f20, 0x90(r1)
	lmw r17, 0x54(r1)
	lwz r0, 0x154(r1)
	mtlr r0
	addi r1, r1, 0x150
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
	lis r4, double_to_int_rsh_00014488@ha
	lis r3, float_32767_rsh_000144ec@ha
	lfd f3, double_to_int_rsh_00014488@l(r4)
	stw r0, 0x8(r1)
	fsubs f0, f31, f30
	lfs f1, float_32767_rsh_000144ec@l(r3)
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

asm void evalOn(void) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	lis r3, str_000047B4@ha
	stw r0, 0x34(r1)
	addi r3, r3, str_000047B4@l
	stmw r24, 0x10(r1)
	bl npcNameToPtr
	mr r31, r3
	lwz r3, 0x104(r3)
	bl animPoseWorldPositionEvalOn
	lis r3, wp@ha
	lwz r0, 0x104(r31)
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	stw r0, 0x48(r3)
	lwz r3, 0x104(r31)
	bl animPoseGetAnimPosePtr
	lwz r6, 0x15c(r3)
	lis r4, vec3_rsh_00013cec@ha
	lwz r0, 0x160(r3)
	addi r5, r4, vec3_rsh_00013cec@l
	lwz r7, 0x0(r6)
	li r3, 0x0
	mtctr r0
	cmpwi r0, 0x0
	ble @1
	@2:
	lwz r4, 0x0(r5)
	add r6, r7, r3
	lwz r0, 0x4(r5)
	addi r3, r3, 0xc
	stw r4, 0x0(r6)
	stw r0, 0x4(r6)
	lwz r0, 0x8(r5)
	stw r0, 0x8(r6)
	bdnz @2
	@1:
	lis r3, dat_80419a28@ha
	lis r5, g_moamoa_chain_tbl@ha
	lis r4, wp@ha
	lwz r28, dat_80419a28@l(r3)
	addi r26, r5, g_moamoa_chain_tbl@l
	li r24, 0x0
	addi r27, r4, wp@l
	li r30, 0x0
	li r29, 0x0
	b @3
	@4:
	add r25, r26, r29
	lwz r3, 0x104(r31)
	lwz r4, 0x0(r25)
	bl animPoseGetGroupIdx
	lwz r4, 0x0(r27)
	addi r0, r30, 0x670
	sthx r3, r4, r0
	lwz r3, 0x104(r31)
	lwz r4, 0x4(r25)
	bl animPoseGetGroupIdx
	lwz r4, 0x0(r27)
	addi r0, r30, 0x672
	addi r30, r30, 0x4
	addi r29, r29, 0x8
	sthx r3, r4, r0
	addi r24, r24, 0x1
	@3:
	cmpw r24, r28
	blt @4
	lis r4, wp@ha
	lis r3, dat_80419a28@ha
	addi r7, r4, wp@l
	lwz r6, dat_80419a28@l(r3)
	lwz r4, 0x0(r7)
	li r9, 0x0
	lwz r8, 0x8(r4)
	b @5
	@6:
	divw r0, r9, r6
	mullw r0, r0, r6
	subf r0, r0, r9
	addi r9, r9, 0x1
	sth r0, 0x48(r8)
	lha r0, 0x48(r8)
	lwz r5, 0x0(r7)
	slwi r3, r0, 1
	addi r4, r3, 0x570
	lhax r3, r5, r4
	addi r0, r3, 0x1
	sthx r0, r5, r4
	sth r3, 0x4a(r8)
	addi r8, r8, 0x50
	@5:
	lwz r4, 0x0(r7)
	lwz r0, 0x4(r4)
	cmpw r9, r0
	blt @6
	lis r3, wp@ha
	lwz r5, 0x8(r4)
	addi r4, r3, wp@l
	li r6, 0x0
	b @7
	@8:
	lha r3, 0x48(r5)
	extsh. r0, r3
	beq @9
	cmpwi r3, 0x5
	beq @9
	cmpwi r3, 0xa
	beq @9
	cmpwi r3, 0xf
	beq @9
	cmpwi r3, 0x1e
	beq @9
	cmpwi r3, 0x22
	beq @9
	cmpwi r3, 0x26
	beq @9
	cmpwi r3, 0x2a
	beq @9
	cmpwi r3, 0x2e
	bne @10
	@9:
	li r0, 0x1
	stb r0, 0x4c(r5)
	@10:
	lha r0, 0x4a(r5)
	cmpwi r0, 0x0
	bne @11
	lha r0, 0x48(r5)
	cmpwi r0, 0x3
	bne @12
	li r0, 0x2
	stb r0, 0x4c(r5)
	@12:
	lha r0, 0x48(r5)
	cmpwi r0, 0x4
	bne @13
	li r0, 0x3
	stb r0, 0x4c(r5)
	@13:
	lha r0, 0x48(r5)
	cmpwi r0, 0x7
	bne @14
	li r0, 0x4
	stb r0, 0x4c(r5)
	@14:
	lha r0, 0x48(r5)
	cmpwi r0, 0x8
	bne @15
	li r0, 0x5
	stb r0, 0x4c(r5)
	@15:
	lha r0, 0x48(r5)
	cmpwi r0, 0x9
	bne @16
	li r0, 0x6
	stb r0, 0x4c(r5)
	@16:
	lha r0, 0x48(r5)
	cmpwi r0, 0xc
	bne @17
	li r0, 0x7
	stb r0, 0x4c(r5)
	@17:
	lha r0, 0x48(r5)
	cmpwi r0, 0xd
	bne @18
	li r0, 0x8
	stb r0, 0x4c(r5)
	@18:
	lha r0, 0x48(r5)
	cmpwi r0, 0xe
	bne @11
	li r0, 0x9
	stb r0, 0x4c(r5)
	@11:
	addi r6, r6, 0x1
	addi r5, r5, 0x50
	@7:
	lwz r3, 0x0(r4)
	lwz r0, 0x4(r3)
	cmpw r6, r0
	blt @8
	lmw r24, 0x10(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
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
	lis r5, str_000041DC@ha
	addi r29, r4, wp@l
	mr r24, r3
	lwz r6, 0x0(r29)
	lis r4, str_000041D0@ha
	addi r30, r5, str_000041DC@l
	li r25, 0x0
	lwz r23, 0x8(r6)
	addi r31, r4, str_000041D0@l
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
	lis r3, fs_group_tbl@ha
	addi r0, r3, fs_group_tbl@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r27, 0x0(r3)
	blt @4
	lwz r26, 0x4(r3)
	@4:
	cmplwi r4, 0xa
	bne @3
	lis r3, str_000048C4@ha
	addi r26, r3, str_000048C4@l
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
	lis r4, str_00004A40@ha
	mr r3, r26
	addi r4, r4, str_00004A40@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @9
	@10:
	lhz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 27, 27
	beq @11
	lis r4, str_00004A44@ha
	mr r3, r26
	addi r4, r4, str_00004A44@l
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
	lis r4, str_000041DC@ha
	addi r29, r3, wp@l
	lis r3, str_000041D0@ha
	lwz r5, 0x0(r29)
	addi r30, r4, str_000041DC@l
	addi r31, r3, str_000041D0@l
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
	lis r3, fs_group_tbl@ha
	addi r0, r3, fs_group_tbl@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r21, 0x0(r3)
	blt @8
	lwz r25, 0x4(r3)
	@8:
	cmplwi r4, 0xa
	bne @7
	lis r3, str_000048C4@ha
	addi r25, r3, str_000048C4@l
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
	lis r4, str_00004A40@ha
	mr r3, r25
	addi r4, r4, str_00004A40@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @13
	@14:
	lhz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 27, 27
	beq @15
	lis r4, str_00004A44@ha
	mr r3, r25
	addi r4, r4, str_00004A44@l
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
	lis r4, float_1_rsh_00014470@ha
	addi r6, r5, wp@l
	lfs f0, float_1_rsh_00014470@l(r4)
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
	lis r5, str_000041DC@ha
	addi r29, r4, wp@l
	mr r25, r3
	lwz r6, 0x0(r29)
	lis r4, str_000041D0@ha
	addi r30, r5, str_000041DC@l
	li r23, 0x0
	lwz r24, 0x8(r6)
	addi r31, r4, str_000041D0@l
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
	lis r3, fs_group_tbl@ha
	addi r0, r3, fs_group_tbl@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r27, 0x0(r3)
	blt @13
	lwz r26, 0x4(r3)
	@13:
	cmplwi r4, 0xa
	bne @12
	lis r3, str_000048C4@ha
	addi r26, r3, str_000048C4@l
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
	lis r4, str_00004A40@ha
	mr r3, r26
	addi r4, r4, str_00004A40@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @18
	@19:
	lhz r0, 0x0(r24)
	rlwinm. r0, r0, 0, 27, 27
	beq @20
	lis r4, str_00004A44@ha
	mr r3, r26
	addi r4, r4, str_00004A44@l
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
	lis r4, zero_rsh_00014490@ha
	li r6, 0x0
	addi r5, r4, zero_rsh_00014490@l
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
	lis r3, fs_group_tbl@ha
	addi r3, r3, fs_group_tbl@l
	clrlslwi r4, r0, 24, 3
	cmplwi r0, 0x2
	lwzx r26, r3, r4
	blt @2
	add r3, r3, r4
	lwz r30, 0x4(r3)
	@2:
	cmplwi r0, 0xa
	bne @1
	lis r3, str_000048C4@ha
	addi r0, r3, str_000048C4@l
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
	lis r4, str_00004A40@ha
	mr r3, r30
	addi r4, r4, str_00004A40@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @7
	@8:
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 27, 27
	beq @9
	lis r4, str_00004A44@ha
	mr r3, r30
	addi r4, r4, str_00004A44@l
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
	lis r7, float_60_rsh_00014578@ha
	addi r29, r4, wp@l
	lis r6, float_1000_rsh_0001457c@ha
	lwz r9, 0x0(r29)
	lis r5, float_1_rsh_00014470@ha
	lis r4, double_to_int_rsh_00014488@ha
	lis r8, gp@ha
	lwz r24, 0x8(r9)
	mr r25, r3
	lfs f28, float_60_rsh_00014578@l(r7)
	addi r30, r8, gp@l
	lfs f29, float_1000_rsh_0001457c@l(r6)
	li r26, 0x0
	lfs f30, float_1_rsh_00014470@l(r5)
	lis r31, 0x8000
	lfd f31, double_to_int_rsh_00014488@l(r4)
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
	lis r3, zero_rsh_00014490@ha
	lfs f1, zero_rsh_00014490@l(r3)
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
__declspec(section ".data") u32 gap_04_000184F4_data[1] = {0};
#pragma force_active reset
