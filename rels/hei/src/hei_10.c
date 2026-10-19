#pragma defer_codegen on
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "memory.h"
#include "string.h"
#include "dolphin/mtx.h"
#include "driver/camdrv.h"
#include "system.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "pmario_sound.h"
#include "stdlib.h"
#include "driver/dispdrv.h"
#include "driver/npcdrv.h"
#include "manager/evtmgr_cmd.h"
#include "driver/animdrv.h"
void PSMTXIdentity(Mtx m);
f32 PSVECDistance(const Vec* a, const Vec* b);
void* _mapAlloc(u32 size);
AnimationPose* animPoseGetAnimPosePtr(s32 poseId);
f32 animPoseGetLoopTimes(s32 id);
void dispEntry(CameraId camera, f32 order, s32 renderMode, DispCallback callback, void* param);
f32 distABf(f32 x1, f32 y1, f32 x2, f32 y2);
f32 evtGetFloat(EventEntry* entry, s32 index);
MarioWork* marioGetPtr(void);
void *memset(void *dest, int ch, size_t count);
NpcEntry* npcNameToPtr(const char* name);
s32 psndSFXOn_3D(const char* name, Vec* position);
#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
extern const f32 vec3_hei_00007a34[3];
extern const f32 vec3_hei_00007a40[3];
extern const f32 vec3_hei_00007a4c[3];
extern const f32 vec3_hei_00007a58[3];
extern const f32 vec3_hei_00007a64[3];
extern const f32 vec3_hei_00007a70[3];
extern const f32 float_60_hei_00007b80;
extern const f32 float_1000_hei_00007b84;
extern const f32 zero_hei_00007b88;
extern const f32 float_0p5_hei_00007b8c;
extern const f32 float_6p2832_hei_00007b90;
extern const f32 float_360_hei_00007b94;
extern const f32 float_0p00761_hei_00007b98;
extern const f32 float_0p16605_hei_00007b9c;
extern const f32 float_1_hei_00007ba0;
extern const f32 float_3p1416_hei_00007ba4;
extern const f32 float_1p5708_hei_00007ba8;
extern const f32 float_4p7124_hei_00007bac;
extern const f32 float_0p03705_hei_00007bb0;
extern const f32 float_0p4967_hei_00007bb4;
extern const f64 double_to_int_hei_00007bb8;
extern const char str_00001D08[24];
extern const f32 float_32767_hei_00007bd8;
extern const f32 float_4_hei_00007bdc;
extern const f32 float_3_hei_00007be0;
extern const f32 float_180_hei_00007be4;
extern const f32 float_0p3_hei_00007be8;
extern const f32 float_0p2_hei_00007bec;
extern const f32 float_800_hei_00007bf0;
extern const f32 float_neg45_hei_00007bf4;
extern const f32 float_90_hei_00007bf8;
extern const f32 float_15_hei_00007bfc;
extern const f32 float_5_hei_00007c00;
extern const f32 float_2_hei_00007c04;
extern const f32 float_0p2_hei_00007c08;
extern const f32 float_0p8_hei_00007c0c;
extern const f32 float_230_hei_00007c10;
extern const f32 float_neg230_hei_00007c14;
extern const f32 float_100_hei_00007c18;
extern const f32 float_neg100_hei_00007c1c;
extern const f32 float_460_hei_00007c20;
extern const f32 float_neg15_hei_00007c24;
extern const f32 float_200_hei_00007c28;
extern const u32 gap_03_00001D74_rodata;
#endif
extern const char str_00001B38[];
extern const char str_00001B40[];
extern const char str_00001B48[];
extern const char str_00001B50[];
extern const char str_00001B58[];
extern const char str_00001B60[];
extern const char str_00001B68[];
extern const char str_00001B74[];
extern const char str_00001BC4[];
extern const char str_00001BD8[];
extern const char str_00001BF0[];
extern const char str_00001C08[];
extern const char str_00001C20[];
extern const char str_00001C28[];
extern const char str_00001C40[];
extern const char str_00001C48[];
extern const char str_00001C50[];
extern const char str_00001C5C[];
extern const char str_00001C7C[];
extern const char str_00001C84[];
extern const char str_00001C8C[];
extern const char str_00001CA0[];
extern const char str_00001CAC[];
extern const char str_00001CBC[];
extern const char str_00001CC0[];

typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
typedef struct Chorobon { s16 flags; s16 state; s16 field_0x4; u8 field_0x6[2]; Vec target; f32 vy; s16 timer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[0x30 - 0x26]; } Chorobon;
typedef struct ChorobonWork { s32 field_0x0; s32 count; Chorobon* chb; } ChorobonWork;
u8 gap_05_00000004_bss[4];
static ChorobonWork* wp;
ExtPose* extGetPosePtr(void);
s32 extGetPoseNum(void);
static f32 randf(f32 min, f32 max);
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
static inline f32 chb_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a; a = a * y; a = -a; } return a; }
static inline f32 chb_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a; } return a; }
void chb_jump(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void ext_disp(CameraId camera, void* param);
void extReset(void);

s32 evt_bero_get_info(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_event_from_road(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_off(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_set(EventEntry* event, BOOL isFirstCall);
s32 evt_chorobon_escape(EventEntry* event, BOOL isFirstCall);
s32 evt_chorobon_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_eff_fukidashi(EventEntry* event, BOOL isFirstCall);
s32 evt_ext_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_map_playanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_set_tevcallback(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_dispflag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_key_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_pose(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_wait_movable(EventEntry* event, BOOL isFirstCall);
s32 evt_mobj_badgeblk(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_battle_start(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_change_fbat_mode(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_jump_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_anim(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_wait_battle_end(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_envon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_set_rev_mode(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxon_3d(EventEntry* event, BOOL isFirstCall);
static s32 npc_jump(EventEntry* event, BOOL isFirstCall);
s32 wait_anim_end(EventEntry* event, BOOL isFirstCall);
s32 wait_anim_frame(EventEntry* event, BOOL isFirstCall);
static void ext_dispent(void);
static void ext_main(void);
void chb_jump(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void ext_shadow_disp(CameraId camera, void* param);
static void ext_disp(CameraId camera, void* param);
static void ext_init(void);
static f32 randf(f32 min, f32 max);
extern s32 evt_bero_info_run[];
extern s32 hei_test_water_tev[];

__declspec(section ".data") u64 fd_hei_10_negone_one_374;
__declspec(section ".data") s32 fd_hei_10_neg_one_382[1];
__declspec(section ".data") s32 fd_hei_10___local_PI_383[1];
__declspec(section ".data") s32 fd_hei_10___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_hei_10_one_negone_373;
__declspec(section ".data") s32 fd_hei_10___local_PIO2_384[1];
__declspec(section ".data") s32 fd_hei_10_one_381[1];
__declspec(section ".data") u64 fd_hei_10_negone_one_360;
__declspec(section ".data") s32 fd_hei_10_neg_one_365[1];
__declspec(section ".data") s32 fd_hei_10___local_PI_366[1];
__declspec(section ".data") s32 fd_hei_10___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_hei_10_one_negone_359;
__declspec(section ".data") s32 fd_hei_10___local_PIO2_367[1];
__declspec(section ".data") s32 fd_hei_10_one_364[1];
static s32 bero_entry_data[60];
static s32 ext_data[63];
s32 golden_se[55];
s32 evt_golden[319];
s32 hei_10_init_evt[80];

int rand(void);

static inline f32 rand01(void) {
    return rand() / 32767.0f;
}

static inline f32 randf_scale(f32 r, f32 min, f32 max) {
    return r * (max - min) + min;
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
		lis r4, double_to_int_hei_00007bb8@ha
		lis r3, float_32767_hei_00007bd8@ha
		lfd f3, double_to_int_hei_00007bb8@l(r4)
		opword 0x90010008
		opword 0xEC1FF028
		lfs f1, float_32767_hei_00007bd8@l(r3)
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
static void ext_init(void) {
    s32 i;
    ExtPose* pose;
    Chorobon* chb;

    wp = _mapAlloc(sizeof(ChorobonWork));
    memset(wp, 0, sizeof(ChorobonWork));
    wp->count = extGetPoseNum();
    wp->chb = _mapAlloc(wp->count * sizeof(Chorobon));
    memset(wp->chb, 0, wp->count * sizeof(Chorobon));
    pose = extGetPosePtr();
    chb = wp->chb;
    for (i = 0; i < wp->count; i++, pose++, chb++) {
        pose->flags |= 7;
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = randf(EXT_LIT(float_neg230_hei_00007c14, -230.0f), EXT_LIT(float_230_hei_00007c10, 230.0f));
        pose->mtx[1][3] = EXT_LIT(float_neg15_hei_00007c24, -15.0f);
        pose->mtx[2][3] = randf(EXT_LIT(float_neg100_hei_00007c1c, -100.0f), EXT_LIT(float_100_hei_00007c18, 100.0f));
        chb->flags = 0;
        chb->state = 0;
        chb->field_0x4 = 0;
    }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
static void ext_init(void) {
	char _af_pad[12];
	asm volatile {
		opword 0x3860000C
		bl _mapAlloc
		lis r5, wp@ha
		opword 0x38800000
		addi r6, r5, wp@l
		opword 0x38A0000C
		opword 0x90660000
		bl memset
		bl extGetPoseNum
		lis r4, wp@ha
		addi r5, r4, wp@l
		opword 0x80850000
		opword 0x90640004
		opword 0x80650000
		opword 0x80030004
		opword 0x1C600030
		bl _mapAlloc
		lis r5, wp@ha
		opword 0x38800000
		addi r6, r5, wp@l
		opword 0x80A60000
		opword 0x90650008
		opword 0x80660000
		opword 0x80030004
		opword 0x80630008
		opword 0x1CA00030
		bl memset
		bl extGetPosePtr
		lis r4, wp@ha
		lis r10, double_to_int_hei_00007bb8@ha
		addi r31, r4, wp@l
		lis r9, float_32767_hei_00007bd8@ha
		opword 0x817F0000
		lis r8, float_460_hei_00007c20@ha
		lis r7, float_neg230_hei_00007c14@ha
		lis r6, float_neg15_hei_00007c24@ha
		lis r5, float_200_hei_00007c28@ha
		lis r4, float_neg100_hei_00007c1c@ha
		opword 0x838B0008
		opword 0x7C7D1B78
		lfd f25, double_to_int_hei_00007bb8@l(r10)
		opword 0x3BC00000
		lfs f26, float_32767_hei_00007bd8@l(r9)
		lis r27, 0x4330
		lfs f27, float_460_hei_00007c20@l(r8)
		lfs f28, float_neg230_hei_00007c14@l(r7)
		lfs f29, float_neg15_hei_00007c24@l(r6)
		lfs f30, float_200_hei_00007c28@l(r5)
		lfs f31, float_neg100_hei_00007c1c@l(r4)
		opword 0x4800008C
		opword 0x801D0000
		opword 0x60000007
		opword 0x901D0000
		opword 0x807D000C
		bl PSMTXIdentity
		bl rand
		opword 0x6C608000
		stw r27, _af_pad+0(r1)
		opword 0x807D000C
		opword 0x9001000C
		opword 0xC8010008
		opword 0xEC00C828
		opword 0xEC00D024
		opword 0xEC00E6FA
		opword 0xD003000C
		opword 0x807D000C
		opword 0xD3A3001C
		bl rand
		opword 0x6C608000
		opword 0x807D000C
		opword 0x90010014
		opword 0x38000000
		opword 0x3BDE0001
		opword 0x3BBD0020
		opword 0x93610010
		opword 0xC8010010
		opword 0xEC00C828
		opword 0xEC00D024
		opword 0xEC00FFBA
		opword 0xD003002C
		opword 0xB01C0000
		opword 0xB01C0002
		opword 0xB01C0004
		opword 0x3B9C0030
		opword 0x807F0000
		opword 0x80030004
		opword 0x7C1E0000
		opword 0x4180FF6C
	}
}
#pragma pop
#endif

static void ext_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}

__declspec(section ".data") u64 fd_hei_10_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hei_10_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hei_10___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hei_10___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hei_10_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hei_10___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hei_10_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_hei_10_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hei_10_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hei_10___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hei_10___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hei_10_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hei_10___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hei_10_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)((char*)str_00001B38), 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)str_00001B40), (s32)((char*)str_00001B48), 65537, 0, 0, (s32)((char*)str_00001B48),
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)((char*)str_00001B50), (s32)((char*)str_00001B38), 65537, 0, 0, (s32)((char*)str_00001B58), 131072,
    6, 100000, 0, 0, -1, 0, 10, 0,
    (s32)((char*)str_00001B60), (s32)((char*)str_00001B58), 65537, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

static s32 ext_data[] = {
    (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 0, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1073741824, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74),
    1082130432, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1086324736, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1090519040, (s32)((char*)str_00001B68),
    (s32)((char*)str_00001B74), 1092616192, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1094713344, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1096810496,
    (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1098907648, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1099956224, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74),
    1101004800, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1102053376, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1103101952, (s32)((char*)str_00001B68),
    (s32)((char*)str_00001B74), 1104150528, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1105199104, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1106247680,
    (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1107296256, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1107820544, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74),
    1108344832, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1108869120, 0, 0, 0,
};

static void ext_shadow_disp(CameraId camera, void* param) {
    static Mtx mt = {
        {8.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 8.0f, 0.0f, 0.5f},
        {0.0f, 0.0f, 8.0f, 0.0f},
    };

    extLoadShadowMtx(mt);
    extLoadShadowRenderMode();
    extLoadShadowVertex();
    extLoadShadowTev();
    extDrawShadow();
}

#ifdef NONMATCHING
void chb_jump(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity) {
    f32 dy;
    f32 dist;
    f32 angle;

    chb->target = (Vec){x, y, z};
    chb->speed = speed;
    chb->gravity = gravity;
    dy = chb->target.y - pose->mtx[1][3];
    dist = distABf(pose->mtx[0][3], pose->mtx[2][3], chb->target.x, chb->target.z);
    angle = angleABf(pose->mtx[0][3], pose->mtx[2][3], chb->target.x, chb->target.z);
    chb->timer = dist / chb->speed;
    chb->vy = dy / chb->timer + chb->gravity * chb->timer / 2;
    chb->state = 100;
    chb->next = next;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void chb_jump(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity) {
	asm volatile {
		opword 0x9421FFA0
		opword 0x7C0802A6
		opword 0x90010064
		opword 0xDBE10050
		opword 0xF3E10058
		opword 0xDBC10040
		opword 0xF3C10048
		opword 0xBFA10034
		lis r6, vec3_hei_00007a34@ha
		opword 0x7C9E2378
		addi r4, r6, vec3_hei_00007a34@l
		opword 0x7C7D1B78
		opword 0x80040000
		opword 0x7CBF2B78
		opword 0x80640004
		opword 0x90010008
		opword 0x80040008
		opword 0x9061000C
		opword 0xD0210008
		opword 0x90010010
		opword 0x80010008
		opword 0xD041000C
		opword 0xD0610010
		opword 0x8061000C
		opword 0x901E0008
		opword 0x80010010
		opword 0x907E000C
		opword 0x901E0010
		opword 0xD09E001C
		opword 0xD0BE0020
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
		opword 0x3C804330
		lis r3, float_0p5_hei_00007b8c@ha
		lis r5, double_to_int_hei_00007bb8@ha
		opword 0xEC1F0024
		lfs f1, float_0p5_hei_00007b8c@l(r3)
		opword 0x90810028
		opword 0x38000064
		lfd f3, double_to_int_hei_00007bb8@l(r5)
		opword 0x90810020
		opword 0xFC00001E
		opword 0xD8010018
		opword 0x8061001C
		opword 0xB07E0018
		opword 0xA87E0018
		opword 0xC09E0020
		opword 0x6C638000
		opword 0x9061002C
		opword 0xC8010028
		opword 0x90610024
		opword 0xEC001828
		opword 0xC8410020
		opword 0xEC1E0024
		opword 0xEC421828
		opword 0xEC4400B2
		opword 0xEC02007A
		opword 0xD01E0014
		opword 0xB01E0002
		opword 0xB3FE0024
		opword 0xE3E10058
		opword 0xCBE10050
		opword 0xE3C10048
		opword 0xCBC10040
		opword 0xBBA10034
		opword 0x80010064
		opword 0x7C0803A6
		opword 0x38210060
	}
}
#pragma pop
#endif
static inline void jump(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 rs, f32 smin, f32 smax, f32 rg, f32 gmin, f32 gmax) { chb_jump(pose, chb, next, x, y, z, rs * (smax - smin) + smin, rg * (gmax - gmin) + gmin); } static inline void escape(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 rs, f32 smin, f32 smax, f32 rg, f32 gmin, f32 gmax) { chb_jump(pose, chb, next, x, y, z, 2.0f * (rs * (smax - smin) + smin), rg * (gmax - gmin) + gmin); }
#pragma push
#pragma opt_lifetimes off
#pragma opt_dead_assignments off
#ifdef NONMATCHING
static void ext_main(void) {
    MarioWork* mario = marioGetPtr();
    const char* sfx;
    s32 i;
    ExtPose* pose;
    Chorobon* chb;
    f32 dist;
    f32 speed;
    f32 x;
    f32 z;
    f32 gravity;
    f32 angle;
    f32 y;
    Vec pos;

    pose = extGetPosePtr();
    chb = wp->chb;
    sfx = (0, "SFX_STG1_CHORO_ESCAPE1");
    for (i = 0; i < wp->count; i++, pose++, chb++) {
        switch (chb->state) {
            case 0: {
                f32 z, speed, gravity, dist, x, y;
                x = rand() / EXT_LIT(float_32767_hei_00007bd8, 32767.0f);
                dist = randf(EXT_LIT(float_4_hei_00007bdc, 4.0f), 7.0f);
                {
                    f32 rad = 3.1415927f * randf_scale(x, 0.0f, 360.0f) / 180.0f;
                    x = pose->mtx[0][3] + chb_sin(rad) * dist;
                    y = pose->mtx[1][3];
                    z = pose->mtx[2][3] - dist * chb_cos(rad);
                }
                speed = rand() / EXT_LIT(float_32767_hei_00007bd8, 32767.0f);
                gravity = rand01();
                jump(pose, chb, chb->state, x, y, z, speed, EXT_LIT(float_0p3_hei_00007be8, 0.3f), EXT_LIT(float_0p5_hei_00007b8c, 0.5f), gravity, EXT_LIT(float_0p5_hei_00007b8c, 0.5f), EXT_LIT(float_0p8_hei_00007c0c, 0.8f));
                break;
            }
            case 1:
                if (distABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]) < EXT_LIT(float_800_hei_00007bf0, 800.0f)) {
                    speed = rand() / 32767.0f;
                    z = angleABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
                    z = z + randf_scale(speed, EXT_LIT(float_neg45_hei_00007bf4, -45.0f), 45.0f);
                    dist = randf(EXT_LIT(float_15_hei_00007bfc, 15.0f), 20.0f);
                    {
                        f32 rad = 3.1415927f * z / 180.0f;
                        x = pose->mtx[0][3] + chb_sin(rad) * dist;
                        y = pose->mtx[1][3];
                        z = pose->mtx[2][3] - dist * chb_cos(rad);
                    }
                    speed = rand() / EXT_LIT(float_32767_hei_00007bd8, 32767.0f);
                    gravity = rand01();
                    escape(pose, chb, chb->state, x, y, z, speed, EXT_LIT(float_1_hei_00007ba0, 1.0f), 1.2f, gravity, EXT_LIT(float_0p8_hei_00007c0c, 0.8f), EXT_LIT(float_0p8_hei_00007c0c, 0.8f));
                    if (rand() % 150 == 0) {
                        pos = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
                        psndSFXOn_3D(sfx, &pos);
                    }
                } else {
                    chb->state = 99;
                }
                break;
            case 99:
                break;
            case 100:
                pose->mtx[1][3] += chb->vy;
                chb->vy -= chb->gravity;
                angle = angleABf(pose->mtx[0][3], pose->mtx[2][3], chb->target.x, chb->target.z);
                {
                    f32 rad = 3.1415927f * angle / 180.0f;
                    pose->mtx[0][3] += chb->speed * chb_sin(rad);
                    pose->mtx[2][3] += chb->speed * -chb_cos(rad);
                }
                if (--chb->timer < 0) {
                    pose->mtx[0][3] = chb->target.x;
                    pose->mtx[1][3] = chb->target.y;
                    pose->mtx[2][3] = chb->target.z;
                    chb->state = chb->next;
                }
                break;
        }
        switch (chb->state) {
            case 0:
                if (pose->mtx[0][3] > EXT_LIT(float_230_hei_00007c10, 230.0f)) {
                    pose->mtx[0][3] = 230.0f;
                }
                if (pose->mtx[0][3] < EXT_LIT(float_neg230_hei_00007c14, -230.0f)) {
                    pose->mtx[0][3] = -230.0f;
                }
                if (pose->mtx[2][3] > EXT_LIT(float_100_hei_00007c18, 100.0f)) {
                    pose->mtx[2][3] = 100.0f;
                }
                if (pose->mtx[2][3] < EXT_LIT(float_neg100_hei_00007c1c, -100.0f)) {
                    pose->mtx[2][3] = -100.0f;
                }
                break;
            case 1:
                break;
        }
        if (gp->retraceCount & 1) {
            pose->frame = (gp->retraceCount + i) % 20;
        }
    }
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
static void ext_main(void) {
	char _af_pad[80];
	asm volatile {
		bl marioGetPtr
		opword 0x7C7D1B78
		bl extGetPosePtr
		lis r5, wp@ha
		lis r4, str_00001D08@ha
		addi r30, r5, wp@l
		opword 0x7C791B78
		opword 0x80BE0000
		addi r27, r4, str_00001D08@l
		lis r4, gp@ha
		opword 0x3B400000
		lwz r24, 0x8(r5)
		addi r31, r4, gp@l
		opword 0x48000B94
		opword 0xA8180002
		opword 0x2C000063
		opword 0x41820AC8
		opword 0x4080001C
		opword 0x2C000001
		opword 0x418203E8
		opword 0x40800AB8
		opword 0x2C000000
		opword 0x40800014
		opword 0x48000AAC
		opword 0x2C000065
		opword 0x40800AA4
		opword 0x48000874
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		stw r3, _af_pad+52(r1)
		lis r4, double_to_int_hei_00007bb8@ha
		lis r3, float_32767_hei_00007bd8@ha
		lfd f2, double_to_int_hei_00007bb8@l(r4)
		opword 0x90010038
		lfs f0, float_32767_hei_00007bd8@l(r3)
		opword 0xC8210038
		opword 0xEC211028
		opword 0xEFC10024
		bl rand
		lis r5, float_360_hei_00007b94@ha
		lis r4, zero_hei_00007b88@ha
		lfs f1, float_360_hei_00007b94@l(r5)
		opword 0x6C668000
		lfs f0, zero_hei_00007b88@l(r4)
		opword 0x3C004330
		lis r3, float_3p1416_hei_00007ba4@ha
		lis r5, double_to_int_hei_00007bb8@ha
		addi r4, r3, float_3p1416_hei_00007ba4@l
		opword 0x90C10044
		addi r6, r5, double_to_int_hei_00007bb8@l
		opword 0xC0440000
		opword 0x90010040
		opword 0xEC1E007A
		opword 0xC8860000
		lis r3, float_180_hei_00007be4@ha
		opword 0xC8610040
		lis r5, float_32767_hei_00007bd8@ha
		opword 0xEC220032
		lfs f0, float_180_hei_00007be4@l(r3)
		opword 0xEC832028
		lfs f3, float_32767_hei_00007bd8@l(r5)
		lis r4, float_3_hei_00007be0@ha
		opword 0xED010024
		addi r7, r4, float_3_hei_00007be0@l
		lis r3, float_4_hei_00007bdc@ha
		addi r6, r3, float_4_hei_00007bdc@l
		lis r5, float_0p00761_hei_00007b98@ha
		lis r4, float_0p16605_hei_00007b9c@ha
		opword 0xEC641824
		lis r3, float_1_hei_00007ba0@ha
		opword 0xC0270000
		opword 0xC0060000
		lfs f6, float_0p00761_hei_00007b98@l(r5)
		lfs f5, float_0p16605_hei_00007b9c@l(r4)
		opword 0xFC081040
		lfs f4, float_1_hei_00007ba0@l(r3)
		opword 0xECE3007A
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_hei_00007ba8@ha
		lfs f1, float_1p5708_hei_00007ba8@l(r3)
		opword 0xFC080840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC080232
		opword 0xECC62838
		opword 0xECC6203A
		opword 0xECC60232
		opword 0x48000070
		opword 0xEC080828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECC62838
		opword 0xECC6203A
		opword 0xECC60072
		opword 0x48000054
		lis r3, float_4p7124_hei_00007bac@ha
		lfs f0, float_4p7124_hei_00007bac@l(r3)
		opword 0xFC080040
		opword 0x40800020
		opword 0xEC281028
		opword 0xEC010072
		opword 0xECC62838
		opword 0xECC6203A
		opword 0xECC60072
		opword 0xFCC03050
		opword 0x48000028
		lis r3, float_1p5708_hei_00007ba8@ha
		opword 0xEC080028
		lfs f1, float_1p5708_hei_00007ba8@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECC62838
		opword 0xECC6203A
		opword 0xECC60072
		opword 0xFCC03050
		opword 0x80D9000C
		lis r3, float_3p1416_hei_00007ba4@ha
		lfs f1, float_3p1416_hei_00007ba4@l(r3)
		lis r5, float_0p03705_hei_00007bb0@ha
		opword 0xC006000C
		lis r4, float_0p4967_hei_00007bb4@ha
		opword 0xFC080840
		lis r3, float_1_hei_00007ba0@ha
		opword 0xEFC701BA
		opword 0xC3E6001C
		lfs f4, float_0p03705_hei_00007bb0@l(r5)
		lfs f3, float_0p4967_hei_00007bb4@l(r4)
		lfs f2, float_1_hei_00007ba0@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_hei_00007ba8@ha
		lfs f1, float_1p5708_hei_00007ba8@l(r3)
		opword 0xFC080840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC080232
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x48000064
		opword 0xEC080828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000048
		lis r3, float_4p7124_hei_00007bac@ha
		lfs f0, float_4p7124_hei_00007bac@l(r3)
		opword 0xFC080040
		opword 0x4080001C
		opword 0xEC080828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_hei_00007ba8@ha
		opword 0xEC080028
		lfs f1, float_1p5708_hei_00007ba8@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xC006002C
		fnmsubs f28, f7, f4, f0
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x90610044
		lis r4, double_to_int_hei_00007bb8@ha
		lis r3, float_32767_hei_00007bd8@ha
		lfd f2, double_to_int_hei_00007bb8@l(r4)
		opword 0x90010040
		lfs f0, float_32767_hei_00007bd8@l(r3)
		opword 0xC8210040
		opword 0xEC211028
		opword 0xEFA10024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_hei_00007bb8@ha
		opword 0x9061003C
		addi r5, r4, double_to_int_hei_00007bb8@l
		lis r3, float_32767_hei_00007bd8@ha
		opword 0x90010038
		addi r4, r3, float_32767_hei_00007bd8@l
		opword 0xC8450000
		lis r3, vec3_hei_00007a34@ha
		opword 0xC8210038
		addi r6, r3, vec3_hei_00007a34@l
		opword 0xC0040000
		lis r4, float_0p2_hei_00007bec@ha
		opword 0xEC211028
		opword 0x80A60000
		opword 0x80060004
		lis r3, float_0p3_hei_00007be8@ha
		opword 0x90A10014
		addi r5, r4, float_0p2_hei_00007bec@l
		opword 0xEC610024
		opword 0x90010018
		addi r4, r3, float_0p3_hei_00007be8@l
		opword 0x80060008
		opword 0xD3C10014
		lis r3, float_0p5_hei_00007b8c@ha
		opword 0x9001001C
		opword 0xAB980002
		opword 0xD3E10018
		opword 0x80C10014
		opword 0xD381001C
		opword 0x80010018
		opword 0x90D80008
		opword 0xC0250000
		opword 0xC0440000
		opword 0x9018000C
		opword 0x8001001C
		opword 0xEC3D107A
		lfs f0, float_0p5_hei_00007b8c@l(r3)
		opword 0x90180010
		opword 0xEC0300BA
		opword 0xD038001C
		opword 0xD0180020
		opword 0x8079000C
		opword 0xC058000C
		opword 0xC003001C
		opword 0xC023000C
		opword 0xEFA20028
		opword 0xC043002C
		opword 0xC0780008
		opword 0xC0980010
		bl distABf
		opword 0x8079000C
		opword 0xFFC00890
		opword 0xC0780008
		opword 0xC023000C
		opword 0xC043002C
		opword 0xC0980010
		bl angleABf
		opword 0xC018001C
		opword 0x3C804330
		lis r3, float_0p5_hei_00007b8c@ha
		lis r5, double_to_int_hei_00007bb8@ha
		opword 0xEC1E0024
		lfs f1, float_0p5_hei_00007b8c@l(r3)
		opword 0x90810058
		opword 0x38000064
		lfd f3, double_to_int_hei_00007bb8@l(r5)
		opword 0x90810050
		opword 0xFC00001E
		opword 0xD8010048
		opword 0x8061004C
		opword 0xB0780018
		opword 0xA8780018
		opword 0xC0980020
		opword 0x6C638000
		opword 0x9061005C
		opword 0xC8010058
		opword 0x90610054
		opword 0xEC001828
		opword 0xC8410050
		opword 0xEC1D0024
		opword 0xEC421828
		opword 0xEC4400B2
		opword 0xEC02007A
		opword 0xD0180014
		opword 0xB0180002
		opword 0xB3980024
		opword 0x480006D8
		opword 0x8079000C
		opword 0xC03D008C
		opword 0xC05D0094
		opword 0xC063000C
		opword 0xC083002C
		bl distABf
		lis r3, float_800_hei_00007bf0@ha
		lfs f0, float_800_hei_00007bf0@l(r3)
		opword 0xFC010040
		opword 0x40800478
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061005C
		lis r4, double_to_int_hei_00007bb8@ha
		lis r3, float_32767_hei_00007bd8@ha
		opword 0x80B9000C
		opword 0x90010058
		lfd f2, double_to_int_hei_00007bb8@l(r4)
		opword 0xC8210058
		lfs f0, float_32767_hei_00007bd8@l(r3)
		opword 0xEC811028
		opword 0xC03D008C
		opword 0xC05D0094
		opword 0xC065000C
		opword 0xEFA40024
		opword 0xC085002C
		bl angleABf
		lis r4, float_90_hei_00007bf8@ha
		lis r3, float_neg45_hei_00007bf4@ha
		lfs f2, float_90_hei_00007bf8@l(r4)
		lfs f0, float_neg45_hei_00007bf4@l(r3)
		opword 0xEC1D00BA
		opword 0xEF81002A
		bl rand
		opword 0x6C648000
		opword 0x3C004330
		lis r3, float_3p1416_hei_00007ba4@ha
		lis r5, double_to_int_hei_00007bb8@ha
		lfs f2, float_3p1416_hei_00007ba4@l(r3)
		addi r6, r5, double_to_int_hei_00007bb8@l
		opword 0x90810054
		lis r3, float_180_hei_00007be4@ha
		lis r4, float_32767_hei_00007bd8@ha
		opword 0xC8860000
		opword 0x90010050
		addi r5, r4, float_32767_hei_00007bd8@l
		lfs f0, float_180_hei_00007be4@l(r3)
		opword 0xEC220732
		opword 0xC8610050
		lis r4, float_5_hei_00007c00@ha
		lis r3, float_15_hei_00007bfc@ha
		opword 0xEC832028
		opword 0xC0650000
		opword 0xED010024
		addi r7, r4, float_5_hei_00007c00@l
		addi r6, r3, float_15_hei_00007bfc@l
		lis r5, float_0p00761_hei_00007b98@ha
		lis r4, float_0p16605_hei_00007b9c@ha
		opword 0xC0270000
		opword 0xEC641824
		opword 0xC0060000
		lis r3, float_1_hei_00007ba0@ha
		lfs f6, float_0p00761_hei_00007b98@l(r5)
		lfs f5, float_0p16605_hei_00007b9c@l(r4)
		lfs f4, float_1_hei_00007ba0@l(r3)
		opword 0xFC081040
		opword 0xECE3007A
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_hei_00007ba8@ha
		lfs f1, float_1p5708_hei_00007ba8@l(r3)
		opword 0xFC080840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC080232
		opword 0xECC62838
		opword 0xECC6203A
		opword 0xECC60232
		opword 0x48000070
		opword 0xEC080828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECC62838
		opword 0xECC6203A
		opword 0xECC60072
		opword 0x48000054
		lis r3, float_4p7124_hei_00007bac@ha
		lfs f0, float_4p7124_hei_00007bac@l(r3)
		opword 0xFC080040
		opword 0x40800020
		opword 0xEC281028
		opword 0xEC010072
		opword 0xECC62838
		opword 0xECC6203A
		opword 0xECC60072
		opword 0xFCC03050
		opword 0x48000028
		lis r3, float_1p5708_hei_00007ba8@ha
		opword 0xEC080028
		lfs f1, float_1p5708_hei_00007ba8@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECC62838
		opword 0xECC6203A
		opword 0xECC60072
		opword 0xFCC03050
		opword 0x80D9000C
		lis r3, float_3p1416_hei_00007ba4@ha
		lfs f1, float_3p1416_hei_00007ba4@l(r3)
		lis r5, float_0p03705_hei_00007bb0@ha
		opword 0xC006000C
		lis r4, float_0p4967_hei_00007bb4@ha
		opword 0xFC080840
		lis r3, float_1_hei_00007ba0@ha
		opword 0xEFE701BA
		opword 0xC3C6001C
		lfs f4, float_0p03705_hei_00007bb0@l(r5)
		lfs f3, float_0p4967_hei_00007bb4@l(r4)
		lfs f2, float_1_hei_00007ba0@l(r3)
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_hei_00007ba8@ha
		lfs f1, float_1p5708_hei_00007ba8@l(r3)
		opword 0xFC080840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC080232
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x48000064
		opword 0xEC080828
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000048
		lis r3, float_4p7124_hei_00007bac@ha
		lfs f0, float_4p7124_hei_00007bac@l(r3)
		opword 0xFC080040
		opword 0x4080001C
		opword 0xEC080828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_hei_00007ba8@ha
		opword 0xEC080028
		lfs f1, float_1p5708_hei_00007ba8@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xC006002C
		opword 0xEF87013C
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061005C
		lis r4, double_to_int_hei_00007bb8@ha
		lis r3, float_32767_hei_00007bd8@ha
		lfd f2, double_to_int_hei_00007bb8@l(r4)
		opword 0x90010058
		lfs f0, float_32767_hei_00007bd8@l(r3)
		opword 0xC8210058
		opword 0xEC211028
		opword 0xEFA10024
		bl rand
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_hei_00007bb8@ha
		opword 0x90610054
		addi r5, r4, double_to_int_hei_00007bb8@l
		lis r3, float_32767_hei_00007bd8@ha
		opword 0x90010050
		addi r4, r3, float_32767_hei_00007bd8@l
		opword 0xC8450000
		lis r3, vec3_hei_00007a34@ha
		opword 0xC8210050
		addi r7, r3, vec3_hei_00007a34@l
		opword 0xC0040000
		lis r4, float_0p2_hei_00007c08@ha
		opword 0xEC211028
		opword 0x80A70000
		opword 0x80070004
		addi r6, r4, float_0p2_hei_00007c08@l
		opword 0x90A10008
		lis r3, float_1_hei_00007ba0@ha
		opword 0xEC610024
		opword 0x9001000C
		addi r5, r3, float_1_hei_00007ba0@l
		opword 0x80070008
		lis r3, float_2_hei_00007c04@ha
		opword 0xD3E10008
		opword 0x90010010
		addi r7, r3, float_2_hei_00007c04@l
		opword 0xAB980002
		lis r4, zero_hei_00007b88@ha
		opword 0x80010008
		lis r3, float_0p8_hei_00007c0c@ha
		opword 0xD3C1000C
		opword 0xC0260000
		opword 0xC0050000
		opword 0x90180008
		opword 0x8001000C
		opword 0xEC1D007A
		opword 0xC0270000
		opword 0xD3810010
		opword 0xEC410032
		lfs f1, zero_hei_00007b88@l(r4)
		opword 0x9018000C
		opword 0x80010010
		lfs f0, float_0p8_hei_00007c0c@l(r3)
		opword 0x90180010
		opword 0xEC03007A
		opword 0xD058001C
		opword 0xD0180020
		opword 0x8079000C
		opword 0xC058000C
		opword 0xC003001C
		opword 0xC023000C
		opword 0xEFA20028
		opword 0xC043002C
		opword 0xC0780008
		opword 0xC0980010
		bl distABf
		opword 0x8079000C
		opword 0xFFC00890
		opword 0xC0780008
		opword 0xC023000C
		opword 0xC043002C
		opword 0xC0980010
		bl angleABf
		opword 0xC018001C
		opword 0x3C804330
		lis r3, float_0p5_hei_00007b8c@ha
		lis r5, double_to_int_hei_00007bb8@ha
		opword 0xEC1E0024
		lfs f1, float_0p5_hei_00007b8c@l(r3)
		opword 0x90810038
		opword 0x38000064
		lfd f3, double_to_int_hei_00007bb8@l(r5)
		opword 0x90810040
		opword 0xFC00001E
		opword 0xD8010048
		opword 0x8061004C
		opword 0xB0780018
		opword 0xA8780018
		opword 0xC0980020
		opword 0x6C638000
		opword 0x9061003C
		opword 0xC8010038
		opword 0x90610044
		opword 0xEC001828
		opword 0xC8410040
		opword 0xEC1D0024
		opword 0xEC421828
		opword 0xEC4400B2
		opword 0xEC02007A
		opword 0xD0180014
		opword 0xB0180002
		opword 0xB3980024
		bl rand
		opword 0x38800096
		opword 0x7C0323D6
		opword 0x7C0021D6
		opword 0x7C001851
		opword 0x408202A0
		lis r3, vec3_hei_00007a40@ha
		opword 0x80B9000C
		addi r8, r3, vec3_hei_00007a40@l
		opword 0x7F63DB78
		opword 0x80E80000
		opword 0x3881002C
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
		opword 0x90C1002C
		opword 0x90A10030
		opword 0x90010034
		bl psndSFXOn_3D
		opword 0x4800023C
		opword 0x38000063
		opword 0xB0180002
		opword 0x48000230
		opword 0x8079000C
		opword 0xC0180014
		opword 0xC023001C
		opword 0xEC01002A
		opword 0xD003001C
		opword 0xC0380014
		opword 0xC0180020
		opword 0xEC010028
		opword 0xD0180014
		opword 0x8079000C
		opword 0xC0780008
		opword 0xC023000C
		opword 0xC043002C
		opword 0xC0980010
		bl angleABf
		lis r4, float_3p1416_hei_00007ba4@ha
		lis r3, float_180_hei_00007be4@ha
		lfs f2, float_3p1416_hei_00007ba4@l(r4)
		addi r6, r3, float_180_hei_00007be4@l
		lis r5, float_0p00761_hei_00007b98@ha
		lis r4, float_0p16605_hei_00007b9c@ha
		opword 0xEC220072
		opword 0xC0060000
		lis r3, float_1_hei_00007ba0@ha
		lfs f5, float_0p00761_hei_00007b98@l(r5)
		lfs f4, float_0p16605_hei_00007b9c@l(r4)
		opword 0xECC10024
		lfs f3, float_1_hei_00007ba0@l(r3)
		opword 0xFC061040
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_hei_00007ba8@ha
		lfs f1, float_1p5708_hei_00007ba8@l(r3)
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
		lis r3, float_4p7124_hei_00007bac@ha
		lfs f0, float_4p7124_hei_00007bac@l(r3)
		opword 0xFC060040
		opword 0x40800020
		opword 0xEC261028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x48000028
		lis r3, float_1p5708_hei_00007ba8@ha
		opword 0xEC060028
		lfs f1, float_1p5708_hei_00007ba8@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xECA52038
		opword 0xECA5183A
		opword 0xECA50072
		opword 0xFCA02850
		opword 0x80F9000C
		lis r3, float_3p1416_hei_00007ba4@ha
		lfs f1, float_3p1416_hei_00007ba4@l(r3)
		lis r6, float_0p03705_hei_00007bb0@ha
		opword 0xC058001C
		lis r5, float_0p4967_hei_00007bb4@ha
		opword 0xC007000C
		opword 0xFC060840
		lis r4, float_1_hei_00007ba0@ha
		lfs f4, float_0p03705_hei_00007bb0@l(r6)
		opword 0xEC02017A
		lfs f3, float_0p4967_hei_00007bb4@l(r5)
		lfs f2, float_1_hei_00007ba0@l(r4)
		opword 0xD007000C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_hei_00007ba8@ha
		lfs f1, float_1p5708_hei_00007ba8@l(r3)
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
		lis r3, float_4p7124_hei_00007bac@ha
		lfs f0, float_4p7124_hei_00007bac@l(r3)
		opword 0xFC060040
		opword 0x4080001C
		opword 0xEC060828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_hei_00007ba8@ha
		opword 0xEC060028
		lfs f1, float_1p5708_hei_00007ba8@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x8079000C
		opword 0xFC202050
		opword 0xC058001C
		opword 0xC003002C
		opword 0xEC02007A
		opword 0xD003002C
		opword 0xA8780018
		opword 0x3863FFFF
		opword 0x7C600735
		opword 0xB0780018
		opword 0x40800030
		opword 0xC0180008
		opword 0x8079000C
		opword 0xD003000C
		opword 0xC018000C
		opword 0x8079000C
		opword 0xD003001C
		opword 0xC0180010
		opword 0x8079000C
		opword 0xD003002C
		opword 0xA8180024
		opword 0xB0180002
		opword 0xA8180002
		opword 0x2C000001
		opword 0x41820084
		opword 0x40800080
		opword 0x2C000000
		opword 0x40800008
		opword 0x48000074
		opword 0x8099000C
		lis r3, float_230_hei_00007c10@ha
		lfs f0, float_230_hei_00007c10@l(r3)
		opword 0xC024000C
		opword 0xFC010040
		opword 0x40810008
		opword 0xD004000C
		opword 0x8099000C
		lis r3, float_neg230_hei_00007c14@ha
		lfs f0, float_neg230_hei_00007c14@l(r3)
		opword 0xC024000C
		opword 0xFC010040
		opword 0x40800008
		opword 0xD004000C
		opword 0x8099000C
		lis r3, float_100_hei_00007c18@ha
		lfs f0, float_100_hei_00007c18@l(r3)
		opword 0xC024002C
		opword 0xFC010040
		opword 0x40810008
		opword 0xD004002C
		opword 0x8099000C
		lis r3, float_neg100_hei_00007c1c@ha
		lfs f0, float_neg100_hei_00007c1c@l(r3)
		opword 0xC024002C
		opword 0xFC010040
		opword 0x40800008
		opword 0xD004002C
		opword 0x807F0000
		opword 0x8063001C
		opword 0x546007FF
		opword 0x4182001C
		opword 0x7C83D214
		opword 0x38600014
		opword 0x7C041B96
		opword 0x7C0019D6
		opword 0x7C002050
		opword 0x90190010
		opword 0x3B5A0001
		opword 0x3B390020
		opword 0x3B180030
		opword 0x807E0000
		opword 0x80030004
		opword 0x7C1A0000
		opword 0x4180F464
	}
}
#pragma pop
#endif
#pragma pop

/* unused in the original build; only its Vec template survives in .rodata */
#ifdef NONMATCHING
static inline void chb_zero(Vec* v) {
    *v = (Vec){0.0f, 0.0f, 0.0f};
}
#endif

#ifdef NONMATCHING
static void ext_dispent(void) {
    dispEntry(CAMERA_3D, 0.0f, 1, ext_disp, NULL);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
static void ext_dispent(void) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r3, zero_hei_00007b88@ha
		lis r4, ext_disp@ha
		addi r6, r3, zero_hei_00007b88@l
		opword 0x90010014
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
#endif

s32 evt_chorobon_escape(EventEntry* event, BOOL isFirstCall) {
    ExtPose* pose = extGetPosePtr();
    s32 i;
    Chorobon* chb = wp->chb;

    for (i = 0; i < wp->count; i++, chb++) {
        chb->state = 1;
        chb->next = 1;
    }
    return EVT_RETURN_DONE;
}

s32 evt_chorobon_wait(EventEntry* event, BOOL isFirstCall) {
    ExtPose* pose = extGetPosePtr();
    Chorobon* chb = wp->chb;
    s32 i;

    for (i = 0; i < wp->count; i++, chb++) {
        if (chb->state != 99) {
            return EVT_RETURN_BLOCK;
        }
    }
    extReset();
    return EVT_RETURN_DONE;
}


static inline s32 npc_jump_get_time(EventEntry* event, s32* args) {
    return evtGetValue(event, args[6]);
}

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING
static s32 npc_jump(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    f32 speed = evtGetFloat(event, args[4]);
    f32 gravity = evtGetFloat(event, args[5]);
    f32 t = EXT_LIT(float_60_hei_00007b80, 60.0f) * (f32)npc_jump_get_time(event, args) / EXT_LIT(float_1000_hei_00007b84, 1000.0f);
    NpcEntry* npc = npcNameToPtr(name);
    f32 vy;
    f32 dist;
    f32 dy;
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
        if (t == EXT_LIT(zero_hei_00007b88, 0.0f)) {
            t = dist / speed;
        } else {
            speed = dist / t;
        }
        vy = dy / t + gravity * t / EXT_LIT(float_2_hei_00007c04, 2.0f);
        event->userdata[0] = *(s32*)&t;
        event->userdata[1] = *(s32*)&vy;
        event->userdata[2] = *(s32*)&speed;
    }
    t = event->userdataf[0];
    vy = event->userdataf[1];
    speed = event->userdataf[2];
    angle = EXT_LIT(float_6p2832_hei_00007b90, 6.2831855f) * angleABf(npc->position.x, npc->position.z, x, z) / EXT_LIT(float_360_hei_00007b94, 360.0f);
    npc->position.x = speed * chb_sin(angle) + npc->position.x;
    npc->position.z = npc->position.z - speed * chb_cos(angle);
    npc->position.y += vy;
    vy -= gravity;
    t -= EXT_LIT(float_1_hei_00007ba0, 1.0f);
    if (t < EXT_LIT(zero_hei_00007b88, 0.0f)) {
        npc->position = (Vec){x, y, z};
        return 1;
    }
    event->userdata[0] = *(s32*)&t;
    event->userdata[1] = *(s32*)&vy;
    return 0;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
static s32 npc_jump(EventEntry* event, BOOL isFirstCall) {
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
		lis r4, double_to_int_hei_00007bb8@ha
		opword 0x9061003C
		addi r3, r4, double_to_int_hei_00007bb8@l
		lis r4, float_60_hei_00007b80@ha
		opword 0x90010038
		addi r5, r4, float_60_hei_00007b80@l
		opword 0xC8230000
		lis r3, float_1000_hei_00007b84@ha
		opword 0xC8010038
		addi r4, r3, float_1000_hei_00007b84@l
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
		lis r3, vec3_hei_00007a64@ha
		lis r4, vec3_hei_00007a58@ha
		addi r7, r3, vec3_hei_00007a64@l
		opword 0x3861002C
		opword 0x80C70000
		addi r5, r4, vec3_hei_00007a58@l
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
		lis r3, zero_hei_00007b88@ha
		opword 0xC05F0090
		opword 0xC061000C
		lfs f0, zero_hei_00007b88@l(r3)
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
		lis r3, float_0p5_hei_00007b8c@ha
		opword 0x8001000C
		opword 0xEC041024
		lfs f1, float_0p5_hei_00007b8c@l(r3)
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
		lis r3, float_6p2832_hei_00007b90@ha
		lis r6, float_0p00761_hei_00007b98@ha
		addi r5, r3, float_6p2832_hei_00007b90@l
		lis r4, float_360_hei_00007b94@ha
		opword 0xC0050000
		lis r5, float_0p16605_hei_00007b9c@ha
		lis r3, float_3p1416_hei_00007ba4@ha
		lfs f4, float_0p00761_hei_00007b98@l(r6)
		opword 0xEC400072
		lfs f0, float_360_hei_00007b94@l(r4)
		lfs f1, float_3p1416_hei_00007ba4@l(r3)
		lis r4, float_1_hei_00007ba0@ha
		lfs f3, float_0p16605_hei_00007b9c@l(r5)
		opword 0xECA20024
		lfs f2, float_1_hei_00007ba0@l(r4)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820048
		lis r3, float_1p5708_hei_00007ba8@ha
		lfs f1, float_1p5708_hei_00007ba8@l(r3)
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
		lis r3, float_4p7124_hei_00007bac@ha
		lfs f0, float_4p7124_hei_00007bac@l(r3)
		opword 0xFC050040
		opword 0x40800020
		opword 0xEC250828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000028
		lis r3, float_1p5708_hei_00007ba8@ha
		opword 0xEC050028
		lfs f1, float_1p5708_hei_00007ba8@l(r3)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		lis r3, float_3p1416_hei_00007ba4@ha
		opword 0xC0410010
		lfs f1, float_3p1416_hei_00007ba4@l(r3)
		lis r4, float_0p4967_hei_00007bb4@ha
		opword 0xC01F008C
		lis r5, float_0p03705_hei_00007bb0@ha
		opword 0xFC050840
		lis r3, float_1_hei_00007ba0@ha
		opword 0xEC02013A
		lfs f4, float_0p03705_hei_00007bb0@l(r5)
		lfs f3, float_0p4967_hei_00007bb4@l(r4)
		lfs f2, float_1_hei_00007ba0@l(r3)
		opword 0xD01F008C
		opword 0x4C401382
		opword 0x40820044
		lis r3, float_1p5708_hei_00007ba8@ha
		lfs f1, float_1p5708_hei_00007ba8@l(r3)
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
		lis r3, float_4p7124_hei_00007bac@ha
		lfs f0, float_4p7124_hei_00007bac@l(r3)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xEC050828
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000020
		lis r3, float_1p5708_hei_00007ba8@ha
		opword 0xEC050028
		lfs f1, float_1p5708_hei_00007ba8@l(r3)
		opword 0xEC010028
		opword 0xEC000032
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xC0210010
		lis r3, float_1_hei_00007ba0@ha
		opword 0xC01F0094
		addi r4, r3, float_1_hei_00007ba0@l
		opword 0xC0610008
		lis r3, zero_hei_00007b88@ha
		opword 0xEC81013C
		opword 0xC021000C
		opword 0xEC43F828
		opword 0xC0040000
		opword 0xD09F0094
		opword 0xEC210028
		lfs f0, zero_hei_00007b88@l(r3)
		opword 0xC09F0090
		opword 0xD0410008
		opword 0xFC010040
		opword 0xEC44182A
		opword 0xD021000C
		opword 0xD05F0090
		opword 0x40800050
		lis r4, vec3_hei_00007a70@ha
		opword 0x38600001
		addi r5, r4, vec3_hei_00007a70@l
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
}
#pragma pop
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

#ifdef NONMATCHING
s32 wait_anim_frame(EventEntry* event, BOOL isFirstCall) {
    f32 frame = evtGetFloat(event, *event->args);
    NpcEntry* npc = npcNameToPtr("\203S\201[\203\213\203h\203`\203\207\203\215\203\173\203\223");

    if (animPoseGetAnimPosePtr(npc->poseId)->localFrame < frame) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 wait_anim_frame(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0xDBE10010
		opword 0xF3E10018
		opword 0x80830018
		opword 0x80840000
		bl evtGetFloat
		opword 0xFFE00890
		lis r3, str_00001BC4@ha
		addi r3, r3, str_00001BC4@l
		bl npcNameToPtr
		opword 0x80630104
		bl animPoseGetAnimPosePtr
		opword 0xC0030024
		opword 0xFC00F840
		opword 0x4080000C
		opword 0x38600000
		opword 0x48000008
		opword 0x38600002
		opword 0xE3E10018
		opword 0x80010024
		opword 0xCBE10010
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
s32 wait_anim_end(EventEntry* event, BOOL isFirstCall) {
    NpcEntry* npc = npcNameToPtr("\203S\201[\203\213\203h\203`\203\207\203\215\203\173\203\223");

    if (isFirstCall) {
        event->lwData[15] = animPoseGetLoopTimes(npc->poseId);
    }
    if (event->lwData[15] == (s32)animPoseGetLoopTimes(npc->poseId)) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 wait_anim_end(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		lis r5, str_00001BC4@ha
		opword 0x90010024
		opword 0xBFC10018
		opword 0x7C7E1B78
		addi r3, r5, str_00001BC4@l
		opword 0x7C9F2378
		bl npcNameToPtr
		opword 0x2C1F0000
		opword 0x7C7F1B78
		opword 0x4182001C
		opword 0x807F0104
		bl animPoseGetLoopTimes
		opword 0xFC00081E
		opword 0xD8010008
		opword 0x8001000C
		opword 0x901E00D8
		opword 0x807F0104
		bl animPoseGetLoopTimes
		opword 0xFC00081E
		opword 0x801E00D8
		opword 0xD8010008
		opword 0x8061000C
		opword 0x7C001800
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000008
		opword 0x38600002
		opword 0xBBC10018
		opword 0x80010024
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop
#endif

EVT_BEGIN(golden_se)
    LOOP(0)
        CALL(wait_anim_frame, 35)
        CALL(evt_npc_get_position, STRING(((char*)str_00001BC4)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001BD8)), LW(0), LW(1), LW(2), 0)
        CALL(wait_anim_frame, 50)
        CALL(evt_npc_get_position, STRING(((char*)str_00001BC4)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001BF0)), LW(0), LW(1), LW(2), 0)
        CALL(wait_anim_frame, 95)
        CALL(evt_npc_get_position, STRING(((char*)str_00001BC4)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001C08)), LW(0), LW(1), LW(2), 0)
        CALL(wait_anim_end)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_golden)
    CALL(evt_npc_entry, STRING(((char*)str_00001C20)), STRING(((char*)str_00001B68)))
    CALL(evt_npc_set_position, STRING(((char*)str_00001C20)), 0, -1000, 0)
    SPAWN_EVENT_GET_ID(PTR(golden_se), LW(15))
    WAIT_FRAMES(10)
    CALL(evt_mario_wait_movable)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001C28)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)str_00001C40)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, STRING(((char*)str_00001C48)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 0, 58, 227, 0, 5, -68, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)str_00001C50)), 0, STRING(((char*)str_00001BC4)))
    WAIT_MS(300)
    CALL(evt_cam3d_event_from_road, 0, -15, 0, 0, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5))
    CALL(evt_cam3d_evt_set, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), 500, 11)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_off, 1000, 11)
    DELETE_EVENT(LW(15))
    CALL(evt_npc_set_anim, STRING(((char*)str_00001BC4)), STRING(((char*)str_00001B74)))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    DIVIDE_FLOAT(LW(0), FLOAT((4.0f)))
    SET_FLOAT_VALUE(LW(3), FLOAT((0.0f)))
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00001BC4)), 131088)
    LOOP(3)
        ADD_FLOAT(LW(3), LW(0))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001BD8)), LW(3), LW(1), LW(2), 0)
        CALL(evt_npc_jump_position, STRING(((char*)str_00001BC4)), LW(3), LW(1), LW(2), 300, 0, FLOAT(30.0f), 0)
    END_LOOP
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00001BC4)), 1073741856)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(1), 30)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001C5C)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_set_pose, STRING(((char*)str_00001C7C)))
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING(((char*)str_00001BC4)), LW(3), LW(4), LW(5))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001BD8)), LW(3), LW(4), LW(5), 0)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00001BC4)), 131088)
    CALL(npc_jump, STRING(((char*)str_00001BC4)), LW(0), LW(1), LW(2), FLOAT(3.5f), FLOAT((2.0f)), 0)
    CALL(evt_npc_battle_start, STRING(((char*)str_00001BC4)))
    CALL(evt_npc_wait_battle_end)
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_mario_set_pose, STRING(((char*)str_00001C84)))
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00001C8C)))
    CALL(evt_npc_set_position, STRING(((char*)str_00001BC4)), 0, -15, 0)
    CALL(evt_ext_entry, 500, PTR(ext_data), PTR(ext_init), PTR(ext_main), PTR(ext_dispent))
    CALL(evt_msg_print, 0, STRING(((char*)str_00001CA0)), 0, STRING(((char*)str_00001BC4)))
    WAIT_MS(300)
    CALL(evt_chorobon_escape)
    CALL(evt_npc_set_position, STRING(((char*)str_00001BC4)), 0, -1000, 0)
    SET_VALUE(GSW(0), 32)
    CALL(evt_mario_key_onoff, 1)
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(LW(0), FLOAT((0.0f)))
        SET_FLOAT_VALUE(LW(1), FLOAT((0.0f)))
        SET_FLOAT_VALUE(LW(2), FLOAT(500.0f))
        DIVIDE_FLOAT(LW(2), FLOAT(40.0f))
        SET_FLOAT_VALUE(LW(3), FLOAT((0.0f)))
        CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00001BC4)), 131088)
        LOOP(40)
            ADD_FLOAT(LW(3), LW(2))
            CALL(npc_jump, STRING(((char*)str_00001BC4)), LW(0), LW(1), LW(3), FLOAT(0.7998047f), FLOAT((1.0f)), 0)
        END_LOOP
        CALL(evt_npc_set_position, STRING(((char*)str_00001BC4)), 0, -1000, 0)
    END_INLINE_EVENT
    CALL(evt_chorobon_wait)
    RETURN
EVT_END()

EVT_BEGIN(hei_10_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00001C8C)))
    CALL(evt_snd_envon, 272, STRING(((char*)str_00001CAC)))
    CALL(evt_snd_set_rev_mode, 1)
    CALL(evt_mobj_badgeblk, STRING(((char*)str_00001CBC)), 100, 46, -75, 241, 0, GSWF(1796), 1)
    CALL(evt_npc_set_position, STRING(((char*)str_00001BC4)), 0, -1000, 0)
    IF_INT_EQUAL(GSWF(1774), 1)
        IF_INT_EQUAL(GSWF(1775), 1)
            IF_INT_LESS(GSW(0), 32)
                CALL(evt_npc_set_position, STRING(((char*)str_00001BC4)), 0, -15, 0)
                CALL(evt_npc_change_fbat_mode, 1)
                SPAWN_EVENT(PTR(evt_golden))
            END_IF
        END_IF
    END_IF
    CALL(evt_map_playanim, STRING(((char*)str_00001CC0)), 1, 0)
    CALL(evt_map_set_tevcallback, 1, PTR(hei_test_water_tev))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00001CC0)), 16777216)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00001CC0)), 256)
    RETURN
EVT_END()

#pragma explicit_zero_data on
__declspec(section ".data") u32 gap_04_0000A464_data[1] = {0};
#pragma explicit_zero_data reset

#pragma force_active on
#pragma explicit_zero_data on
#pragma explicit_zero_data reset

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const char str_00001B38[8] = "w_bero\0";
__declspec(section ".rodata") const char str_00001B40[8] = "hei_09\0";
__declspec(section ".rodata") const char str_00001B48[8] = "e_bero\0";
__declspec(section ".rodata") const char str_00001B50[8] = "hei_11\0";
__declspec(section ".rodata") const char str_00001B58[8] = "dokan\0\0";
__declspec(section ".rodata") const char str_00001B60[8] = "hei_07\0";
__declspec(section ".rodata") const char str_00001B68[12] = "c_chorobon\0";
__declspec(section ".rodata") const char str_00001B74[8] = "CBN_W_1";
__declspec(section ".rodata") const f32 vec3_hei_00007a34[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_hei_00007a40[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_hei_00007a4c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_hei_00007a58[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_hei_00007a64[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_hei_00007a70[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const char str_00001BC4[20] = "\x83S\x81[\x83\x8b\x83h\x83`\x83\x87\x83\x8d\x83{\x83\x93\0";
__declspec(section ".rodata") const char str_00001BD8[24] = "SFX_STG1_CHORO_MOVE1\0\0\0";
__declspec(section ".rodata") const char str_00001BF0[24] = "SFX_STG1_CHORO_G_WAIT2\0";
__declspec(section ".rodata") const char str_00001C08[24] = "SFX_STG1_CHORO_G_WAIT1\0";
__declspec(section ".rodata") const char str_00001C20[8] = "dummy\0\0";
__declspec(section ".rodata") const char str_00001C28[24] = "SFX_VOICE_MARIO_FIND1_3";
__declspec(section ".rodata") const char str_00001C40[8] = "eff0\0\0\0";
__declspec(section ".rodata") const char str_00001C48[8] = "eff1\0\0\0";
__declspec(section ".rodata") const char str_00001C50[12] = "stg1_hei_42";
__declspec(section ".rodata") const char str_00001C5C[32] = "SFX_VOICE_MARIO_SURPRISED2_2\0\0\0";
__declspec(section ".rodata") const char str_00001C7C[8] = "M_N_7\0\0";
__declspec(section ".rodata") const char str_00001C84[8] = "M_S_1\0\0";
__declspec(section ".rodata") const char str_00001C8C[20] = "BGM_STG1_TORIDE1\0\0\0";
__declspec(section ".rodata") const char str_00001CA0[12] = "stg1_hei_44";
__declspec(section ".rodata") const char str_00001CAC[16] = "ENV_STG1_HEI3\0\0";
__declspec(section ".rodata") const char str_00001CBC[4] = "m\0\0";
__declspec(section ".rodata") const char str_00001CC0[8] = "mizu\0\0\0";
__declspec(section ".rodata") const f32 float_60_hei_00007b80 = 60.0f;
__declspec(section ".rodata") const f32 float_1000_hei_00007b84 = 1000.0f;
__declspec(section ".rodata") const f32 zero_hei_00007b88 = 0.0f;
__declspec(section ".rodata") const f32 float_0p5_hei_00007b8c = 0.5f;
__declspec(section ".rodata") const f32 float_6p2832_hei_00007b90 = 6.2831855f;
__declspec(section ".rodata") const f32 float_360_hei_00007b94 = 360.0f;
__declspec(section ".rodata") const f32 float_0p00761_hei_00007b98 = 0.00761f;
__declspec(section ".rodata") const f32 float_0p16605_hei_00007b9c = 0.16605f;
__declspec(section ".rodata") const f32 float_1_hei_00007ba0 = 1.0f;
__declspec(section ".rodata") const f32 float_3p1416_hei_00007ba4 = 3.1415927f;
__declspec(section ".rodata") const f32 float_1p5708_hei_00007ba8 = 1.5707964f;
__declspec(section ".rodata") const f32 float_4p7124_hei_00007bac = 4.712389f;
__declspec(section ".rodata") const f32 float_0p03705_hei_00007bb0 = 0.03705f;
__declspec(section ".rodata") const f32 float_0p4967_hei_00007bb4 = 0.4967f;
__declspec(section ".rodata") const f64 double_to_int_hei_00007bb8 = 4503601774854144.0;
__declspec(section ".rodata") const char str_00001D08[24] = "SFX_STG1_CHORO_ESCAPE1\0";
__declspec(section ".rodata") const f32 float_32767_hei_00007bd8 = 32767.0f;
__declspec(section ".rodata") const f32 float_4_hei_00007bdc = 4.0f;
__declspec(section ".rodata") const f32 float_3_hei_00007be0 = 3.0f;
__declspec(section ".rodata") const f32 float_180_hei_00007be4 = 180.0f;
__declspec(section ".rodata") const f32 float_0p3_hei_00007be8 = 0.3f;
__declspec(section ".rodata") const f32 float_0p2_hei_00007bec = 0.19999999f;
__declspec(section ".rodata") const f32 float_800_hei_00007bf0 = 800.0f;
__declspec(section ".rodata") const f32 float_neg45_hei_00007bf4 = -45.0f;
__declspec(section ".rodata") const f32 float_90_hei_00007bf8 = 90.0f;
__declspec(section ".rodata") const f32 float_15_hei_00007bfc = 15.0f;
__declspec(section ".rodata") const f32 float_5_hei_00007c00 = 5.0f;
__declspec(section ".rodata") const f32 float_2_hei_00007c04 = 2.0f;
__declspec(section ".rodata") const f32 float_0p2_hei_00007c08 = 0.20000005f;
__declspec(section ".rodata") const f32 float_0p8_hei_00007c0c = 0.8f;
__declspec(section ".rodata") const f32 float_230_hei_00007c10 = 230.0f;
__declspec(section ".rodata") const f32 float_neg230_hei_00007c14 = -230.0f;
__declspec(section ".rodata") const f32 float_100_hei_00007c18 = 100.0f;
__declspec(section ".rodata") const f32 float_neg100_hei_00007c1c = -100.0f;
__declspec(section ".rodata") const f32 float_460_hei_00007c20 = 460.0f;
__declspec(section ".rodata") const f32 float_neg15_hei_00007c24 = -15.0f;
__declspec(section ".rodata") const f32 float_200_hei_00007c28 = 200.0f;
__declspec(section ".rodata") const u32 gap_03_00001D74_rodata = 0x00000000;
#endif

#ifdef NONMATCHING // all-C link: pool objects the C names, defined on the asm side only
__declspec(section ".data") const char str_00001B38[8] = "w_bero\0";
__declspec(section ".data") const char str_00001B40[8] = "hei_09\0";
__declspec(section ".data") const char str_00001B48[8] = "e_bero\0";
__declspec(section ".data") const char str_00001B50[8] = "hei_11\0";
__declspec(section ".data") const char str_00001B58[8] = "dokan\0\0";
__declspec(section ".data") const char str_00001B60[8] = "hei_07\0";
__declspec(section ".data") const char str_00001B68[12] = "c_chorobon\0";
__declspec(section ".data") const char str_00001B74[8] = "CBN_W_1";
__declspec(section ".data") const char str_00001BC4[20] = "\x83S\x81[\x83\x8b\x83h\x83`\x83\x87\x83\x8d\x83{\x83\x93\0";
__declspec(section ".data") const char str_00001BD8[24] = "SFX_STG1_CHORO_MOVE1\0\0\0";
__declspec(section ".data") const char str_00001BF0[24] = "SFX_STG1_CHORO_G_WAIT2\0";
__declspec(section ".data") const char str_00001C08[24] = "SFX_STG1_CHORO_G_WAIT1\0";
__declspec(section ".data") const char str_00001C20[8] = "dummy\0\0";
__declspec(section ".data") const char str_00001C28[24] = "SFX_VOICE_MARIO_FIND1_3";
__declspec(section ".data") const char str_00001C40[8] = "eff0\0\0\0";
__declspec(section ".data") const char str_00001C48[8] = "eff1\0\0\0";
__declspec(section ".data") const char str_00001C50[12] = "stg1_hei_42";
__declspec(section ".data") const char str_00001C5C[32] = "SFX_VOICE_MARIO_SURPRISED2_2\0\0\0";
__declspec(section ".data") const char str_00001C7C[8] = "M_N_7\0\0";
__declspec(section ".data") const char str_00001C84[8] = "M_S_1\0\0";
__declspec(section ".data") const char str_00001C8C[20] = "BGM_STG1_TORIDE1\0\0\0";
__declspec(section ".data") const char str_00001CA0[12] = "stg1_hei_44";
__declspec(section ".data") const char str_00001CAC[16] = "ENV_STG1_HEI3\0\0";
__declspec(section ".data") const char str_00001CBC[4] = "m\0\0";
__declspec(section ".data") const char str_00001CC0[8] = "mizu\0\0\0";
#endif
