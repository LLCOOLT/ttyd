#include "evt/evt_cmd.h"
#include "driver/icondrv.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/hitdrv.h"
#include "driver/mapdrv.h"
#include "driver/msgdrv.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "manager/fontmgr.h"
#include "manager/winmgr.h"
#include "mario/mario.h"
#include "mario/mario_pouch.h"
#include "mario/mariost.h"
#include "data/item_data.h"
#include "driver/windowdrv.h"
#include "evt/evt_badgeshop.h"
#include "evt/evt_johoya.h"
#include "evt/evt_lottery.h"
#include "pmario_sound.h"
#include "memory.h"
#include "party.h"
#include "system.h"
#include <dolphin/mtx.h>
#include <stdio.h>
#include <string.h>
#ifndef NONMATCHING
#include "mario/mario_party.h"
__declspec(section ".rodata") extern const f32 vec3_802f64b8[3];
__declspec(section ".rodata") extern const f32 vec3_802f64c4[3];
__declspec(section ".rodata") extern const f32 vec3_802f64d0[3];
__declspec(section ".rodata") extern const f32 vec3_802f64dc[3];
__declspec(section ".rodata") extern const u32 zero_802f64e8[16];
__declspec(section ".rodata") extern const f32 vec3_802f6528[3];
__declspec(section ".rodata") extern const u32 zero_802f6534[16];
__declspec(section ".rodata") extern const f32 vec3_802f6574[3];
__declspec(section ".rodata") extern const f32 vec3_802f6580[3];
__declspec(section ".rodata") extern const f32 vec3_802f658c[3];
__declspec(section ".rodata") extern const f32 vec3_802f6598[3];
__declspec(section ".rodata") extern const u32 zero_802f65a4[16];
__declspec(section ".rodata") extern const f32 vec3_802f65e4[3];
__declspec(section ".rodata") extern const u32 zero_802f65f0[16];
__declspec(section ".rodata") extern const f32 vec3_802f6630[3];
__declspec(section ".rodata") extern const char str_802F663C[];
__declspec(section ".rodata") extern const char str_802F664C[];
__declspec(section ".rodata") extern const char str_802F6660[];
__declspec(section ".rodata") extern const char str_802F6674[];
__declspec(section ".rodata") extern const char str_802F6688[];
__declspec(section ".rodata") extern const char str_802F669C[];
__declspec(section ".rodata") extern const char str_802F66B0[];
__declspec(section ".rodata") extern const char str_802F66C4[];
__declspec(section ".rodata") extern const char str_802F66D8[];
__declspec(section ".rodata") extern const char str_802F66EC[];
__declspec(section ".rodata") extern const char str_802F66F8[];
__declspec(section ".rodata") extern const char str_802F6704[];
__declspec(section ".rodata") extern const char str_802F6710[];
__declspec(section ".rodata") extern const char str_802F671C[];
__declspec(section ".rodata") extern const char str_802F6728[];
__declspec(section ".rodata") extern const char str_802F6734[];
__declspec(section ".rodata") extern const char str_802F673C[];
__declspec(section ".rodata") extern const char str_802F6744[];
__declspec(section ".rodata") extern const char str_802F6750[];
__declspec(section ".rodata") extern const char str_802F6760[];
__declspec(section ".rodata") extern const char str_802F6774[];
__declspec(section ".rodata") extern const char str_802F6788[];
__declspec(section ".rodata") extern const char str_802F6798[];
__declspec(section ".rodata") extern const char str_802F67A8[];
__declspec(section ".rodata") extern const char str_802F67BC[];
__declspec(section ".rodata") extern const char str_802F67D0[];
__declspec(section ".rodata") extern const char str_802F67E4[];
__declspec(section ".rodata") extern const char str_802F67FC[];
__declspec(section ".rodata") extern const char str_802F6810[];
__declspec(section ".rodata") extern const char str_802F6824[];
__declspec(section ".rodata") extern const char str_802F6838[];
__declspec(section ".rodata") extern const char str_802F6850[];
__declspec(section ".rodata") extern const char str_802F6868[];
__declspec(section ".rodata") extern const char str_802F687C[];
__declspec(section ".rodata") extern const char str_802F6894[];
__declspec(section ".rodata") extern const f64 double_to_int_802f68a8;
__declspec(section ".rodata") extern const f64 double_to_int_mask_802f68b8;
__declspec(section ".sdata2") extern const u32 dat_8041d9b4;
__declspec(section ".sdata2") extern const u32 dat_8041d9b8;
__declspec(section ".sdata2") extern const u32 dat_8041d9bc;
__declspec(section ".sdata2") extern const u32 dat_8041d9c0;
__declspec(section ".sdata2") extern const u32 dat_8041d9c4;
__declspec(section ".sdata2") extern const u32 dat_8041d9c8;
__declspec(section ".sdata2") extern const u32 dat_8041d9cc;
__declspec(section ".sdata2") extern const u32 dat_8041d9d0;
__declspec(section ".sdata2") extern const u32 dat_8041d9d4;
__declspec(section ".sdata2") extern const u32 dat_8041d9d8;
__declspec(section ".sdata2") extern const u32 dat_8041d9dc;
__declspec(section ".sdata2") extern const u32 dat_8041d9e0;
__declspec(section ".sdata2") extern const u32 dat_8041d9e4;
__declspec(section ".sdata2") extern const u32 dat_8041d9e8;
__declspec(section ".sdata2") extern const u32 dat_8041d9ec;
__declspec(section ".sdata2") extern const u32 dat_8041d9f0;
__declspec(section ".sdata2") extern const u32 dat_8041d9f4;
__declspec(section ".sdata2") extern const u32 dat_8041d9f8;
__declspec(section ".sdata2") extern const u32 dat_8041d9fc;
__declspec(section ".sdata2") extern const u32 dat_8041da00;
__declspec(section ".sdata2") extern const u32 dat_8041da04;
__declspec(section ".sdata2") extern const u32 dat_8041da08;
__declspec(section ".sdata2") extern const u32 dat_8041da0c;
__declspec(section ".sdata2") extern const u32 dat_8041da10;
__declspec(section ".sdata2") extern const u32 dat_8041da14;
__declspec(section ".sdata2") extern const u32 dat_8041da18;
__declspec(section ".sdata2") extern const u32 dat_8041da1c;
__declspec(section ".sdata2") extern const u32 dat_8041da20;
__declspec(section ".sdata2") extern const u32 dat_8041da24;
__declspec(section ".sdata2") extern const u32 dat_8041da28;
__declspec(section ".sdata2") extern const u32 dat_8041da2c;
__declspec(section ".sdata2") extern const u32 dat_8041da30;
__declspec(section ".sdata2") extern const u32 dat_8041da34;
__declspec(section ".sdata2") extern const u32 dat_8041da38;
__declspec(section ".sdata2") extern const u32 dat_8041da3c;
__declspec(section ".sdata2") extern const u32 dat_8041da40;
__declspec(section ".sdata2") extern const u32 dat_8041da44;
__declspec(section ".sdata2") extern const u32 dat_8041da48;
__declspec(section ".sdata2") extern const u32 dat_8041da4c;
__declspec(section ".sdata2") extern const u32 dat_8041da50;
__declspec(section ".sdata2") extern const u32 dat_8041da54;
__declspec(section ".sdata2") extern const u32 dat_8041da58;
__declspec(section ".sdata2") extern const u32 dat_8041da5c;
__declspec(section ".sdata2") extern const u32 dat_8041da60;
__declspec(section ".sdata2") extern const u32 dat_8041da64;
__declspec(section ".sdata2") extern const u32 dat_8041da68;
__declspec(section ".sdata2") extern const u32 dat_8041da6c;
__declspec(section ".sdata2") extern const u32 dat_8041da70;
__declspec(section ".sdata2") extern const u32 dat_8041da74;
__declspec(section ".sdata2") extern const u32 dat_8041da78;
__declspec(section ".sdata2") extern const u32 dat_8041da7c;
__declspec(section ".sdata2") extern const u32 dat_8041da80;
__declspec(section ".sdata2") extern const u32 dat_8041da84;
__declspec(section ".sdata2") extern const u32 dat_8041da88;
__declspec(section ".sdata2") extern const u32 dat_8041da8c;
__declspec(section ".sdata2") extern const u32 dat_8041da90;
__declspec(section ".sdata2") extern const u32 dat_8041da94;
__declspec(section ".sdata2") extern const u32 dat_8041da98;
__declspec(section ".sdata2") extern const u32 dat_8041da9c;
__declspec(section ".sdata2") extern const u32 dat_8041daa0;
__declspec(section ".sdata2") extern const u32 dat_8041daa4;
__declspec(section ".sdata2") extern const u32 dat_8041daa8;
__declspec(section ".sdata2") extern const u32 dat_8041daac;
__declspec(section ".sdata2") extern const u32 dat_8041dab0;
__declspec(section ".sdata2") extern const u32 dat_8041dab4;
__declspec(section ".sdata2") extern const u32 dat_8041dab8;
__declspec(section ".sdata2") extern const u32 dat_8041dabc;
__declspec(section ".sdata2") extern const char str_8041DAC0[];
__declspec(section ".sdata2") extern const f32 float_neg150_8041dac8;
__declspec(section ".sdata2") extern const f32 float_120_8041dacc;
__declspec(section ".sdata2") extern const f32 float_300_8041dad0;
__declspec(section ".sdata2") extern const f32 float_50_8041dad4;
__declspec(section ".sdata2") extern const f32 float_20_8041dad8;
__declspec(section ".sdata2") extern const f32 float_108_8041dadc;
__declspec(section ".sdata2") extern const f32 float_neg240_8041dae0;
__declspec(section ".sdata2") extern const f32 float_neg130_8041dae4;
__declspec(section ".sdata2") extern const f32 float_480_8041dae8;
__declspec(section ".sdata2") extern const f32 float_70_8041daec;
__declspec(section ".sdata2") extern const f32 float_8_8041daf0;
__declspec(section ".sdata2") extern const f32 float_neg304_8041daf4;
__declspec(section ".sdata2") extern const f32 float_240_8041daf8;
__declspec(section ".sdata2") extern const f32 float_60_8041dafc;
__declspec(section ".sdata2") extern const f32 float_0_8041db00;
__declspec(section ".sdata2") extern const f32 float_neg250_8041db04;
__declspec(section ".sdata2") extern const f32 float_neg75_8041db08;
__declspec(section ".sdata2") extern const f32 float_150_8041db0c;
__declspec(section ".sdata2") extern const f32 float_45_8041db10;
__declspec(section ".sdata2") extern const f32 float_neg220_8041db14;
__declspec(section ".sdata2") extern const f32 float_neg113_8041db18;
__declspec(section ".sdata2") extern const f32 float_0p7_8041db1c;
__declspec(section ".sdata2") extern const f32 float_neg192_8041db20;
__declspec(section ".sdata2") extern const f32 float_neg126_8041db24;
__declspec(section ".sdata2") extern const f32 float_neg210_8041db28;
__declspec(section ".sdata2") extern const f32 float_neg166_8041db2c;
__declspec(section ".sdata2") extern const f32 float_1p1_8041db30;
__declspec(section ".sdata2") extern const f32 float_neg168_8041db34;
__declspec(section ".sdata2") extern const f32 float_neg172_8041db38;
__declspec(section ".sdata2") extern const char str_8041DB3C[];
__declspec(section ".sdata2") extern const f32 float_neg24_8041db44;
__declspec(section ".sdata2") extern const f32 float_100_8041db48;
__declspec(section ".sdata2") extern const f32 float_51_8041db4c;
__declspec(section ".sdata2") extern const f32 float_114_8041db50;
__declspec(section ".sdata2") extern const f32 float_28_8041db54;
__declspec(section ".sdata2") extern const f32 float_81_8041db58;
__declspec(section ".sdata2") extern const f32 float_111_8041db5c;
__declspec(section ".sdata2") extern const f32 float_0p5_8041db60;
__declspec(section ".sdata2") extern const f32 float_36_8041db64;
__declspec(section ".sdata2") extern const f32 float_244_8041db68;
__declspec(section ".sdata2") extern const f32 float_82_8041db6c;
__declspec(section ".sdata2") extern const f32 float_0p6_8041db70;
__declspec(section ".sdata2") extern const f32 float_0p8_8041db74;
__declspec(section ".sdata2") extern const f32 float_2_8041db78;
__declspec(section ".sdata2") extern const char str_8041DB7C[];
__declspec(section ".sdata2") extern const f32 float_1_8041db80;
__declspec(section ".sdata2") extern const char str_8041DB84[];
__declspec(section ".sdata2") extern const char str_8041DB88[];
__declspec(section ".sdata2") extern const f32 float_71_8041db8c;
__declspec(section ".sdata2") extern const f32 float_0_8041db90;
__declspec(section ".sdata2") extern const f32 float_221_8041db94;
__declspec(section ".sdata2") extern const f32 float_16_8041db98;
__declspec(section ".sdata2") extern const f32 float_41_8041db9c;
__declspec(section ".sdata2") extern const f32 float_167_8041dba0;
__declspec(section ".sdata2") extern const f32 float_85_8041dba4;
__declspec(section ".sdata2") extern const f32 float_177_8041dba8;
__declspec(section ".sdata2") extern const char str_8041DBAC[];
__declspec(section ".sdata2") extern const f32 float_236_8041dbb0;
__declspec(section ".sdata2") extern const char str_8041DBB4[];
__declspec(section ".sdata2") extern const f32 float_21_8041dbbc;
__declspec(section ".sdata2") extern const char str_8041DBC0[];
__declspec(section ".sdata2") extern const char str_8041DBC8[];
__declspec(section ".sdata2") extern const f32 float_206_8041dbd0;
__declspec(section ".sdata2") extern const f32 float_neg280_8041dbd4;
__declspec(section ".sdata2") extern const f32 float_228_8041dbd8;
__declspec(section ".sdata2") extern const f32 float_90_8041dbdc;
__declspec(section ".sdata2") extern const f32 float_66_8041dbe0;
__declspec(section ".sdata2") extern const f32 float_1000_8041dbe4;
__declspec(section ".sdata2") extern const f32 float_6_8041dbe8;
__declspec(section ".sdata2") extern const f32 float_10_8041dbec;
__declspec(section ".sdata2") extern const f32 float_30_8041dbf0;
__declspec(section ".sdata2") extern const f32 float_124_8041dbf4;
__declspec(section ".sdata2") extern const f32 float_38_8041dbf8;
__declspec(section ".sdata2") extern const f32 float_12_8041dbfc;
#define EXT_LIT(sym, val) (sym)

#endif
extern const char str_802F68B0[];
extern const char str_8041D958[];
extern const char str_8041D960[];
extern const char str_8041D968[];
extern const char str_8041D970[];
extern const char str_8041D978[];
extern const char str_8041D980[];
extern const char str_8041D988[];
extern const char str_8041D990[];
extern const char str_8041D994[];
extern const char str_8041D998[];
extern const char str_8041D99C[];
extern const char str_8041D9A4[];
extern const char str_8041D9AC[];

extern ItemData itemDataTable[];
extern GlobalWork* gp;

void mapObjGetPos(const char* name, Vec* pos);
void mapObjFlagOn(const char* name, u32 flags);
void mapObjFlagOff(const char* name, u32 flags);
void FontDrawString(f32 x, f32 y, const char* str);
void FontDrawEdge(void);
void FontDrawEdgeOff(void);
BOOL winGhostDiaryChk(void);
BOOL N_itemPickUpFromFieldCheck(void);
void statusWinForceUpdateCoin(void);
void FontDrawScale(f32 scale);
s16 johoya_get(u8* table, s16 id);
extern BadgeShopWork* bdsw;
extern s32 badge_bottakuru100_table[];
extern InformantWork _jdt;
s32 marioKeyOn(void);

typedef struct UnitWinEntry {
	const char* mapObj; // 0x0
	const char* hitName; // 0x4
	void* evt;          // 0x8
} UnitWinEntry;

typedef struct UnitWinWork {
	u16 flags;             // 0x0
	u16 pad2;              // 0x2
	UnitWinEntry* entries; // 0x4
	s32* goods;            // 0x8
	u16 itemFlags[6];      // 0xC
	s32 goodsMax;          // 0x18
	EventEntry* evt;       // 0x1C
	EventEntry* childEvt;  // 0x20
	s32 goodsIdx;          // 0x24
	s32 timer;             // 0x28
	s32 coin;              // 0x2C
	s32 coinDisp;          // 0x30
	f32 cursor;            // 0x34
	u8 pad38[4];           // 0x38
	f32 cursorX;           // 0x3C
	f32 cursorY;           // 0x40
	f32 scroll;            // 0x44
	u8 pad48[4];           // 0x48
	s32 field_0x4C;        // 0x4C
	s32 field_0x50;        // 0x50
	u16 flags2;            // 0x54
	u8 pad56[2];           // 0x56
	s32 count;             // 0x58
	s32 field_0x5C;        // 0x5C
	s32 winId[3];          // 0x60
	u8 pad6C[0xE0 - 0x6C]; // 0x6C
	s32 selected;          // 0xE0
	s32 bought;            // 0xE4
} UnitWinWork;

#pragma force_active on
__declspec(section ".sdata") u32 gap_08_80418A0C_sbss[1];
static s16* mario_status_point_table[3];
s32 unk_804189fc;
static UnitWinWork* _wp;

#ifdef NONMATCHING
USER_FUNC(evt_unitwin_main_func);
USER_FUNC(unk_80174e98);
#endif
#ifndef NONMATCHING
s32 evt_unitwin_main_func(EventEntry* event, BOOL isFirstCall);
s32 unk_80174e98(EventEntry* event, BOOL isFirstCall);
#endif
void evt_unitwin_disp_func(CameraId cameraId, void* param);

void unk_8017597c(WinMgrEntry* entry);
void unk_801758fc(WinMgrEntry* entry);
void unk_80175710(WinMgrEntry* entry);
void unk_8017599c(WinMgrEntry* entry);

WinMgrDesc unk_80375478[3] = {
	{0, 0, 8, -150, 120, 300, 50, {0x2B, 0xA4, 0xFF, 0xFF}, NULL, unk_8017599c},
	{0, 0, 8, -240, -130, 500, 80, {0xF0, 0xF0, 0xF0, 0xFF}, unk_8017597c, unk_801758fc},
	{2, 0, 8, -250, -130, 150, 45, {0xF0, 0xF0, 0xF0, 0xFF}, NULL, unk_80175710},
};

static s32 party_id_table[8] = {1, 2, 5, 4, 6, 3, 7, 0};
static s32 party_icon_table[7] = {0x155, 0x156, 0x15F, 0x158, 0x160, 0x157, 0x161};
static const char* party_labelname_table[7] = {((char*)str_8041D958), ((char*)str_8041D960), ((char*)str_8041D968), ((char*)str_8041D970), ((char*)str_8041D978), ((char*)str_8041D980), ((char*)str_8041D988)};
static s32 mario_status_icon_table[3] = {0x19F, 0x1A0, 0x1A1};
static const char* mario_status_labelname_table[3] = {((char*)str_8041D990), ((char*)str_8041D994), ((char*)str_8041D998)};
static const char* mario_status_name_table[3] = {((char*)str_8041D99C), ((char*)str_8041D9A4), ((char*)str_8041D9AC)};
static s32 mario_status_henka_table[3] = {5, 5, 3};

static EVT_BEGIN(main_evt)
	CALL(evt_unitwin_main_func)
	RETURN
EVT_END()

EVT_BEGIN(select_evt)
	CALL(unk_80174e98)
	RETURN
EVT_END()

#ifndef NONMATCHING
void GXGetProjectionv(f32* ptr);
void GXGetScissor(u32* left, u32* top, u32* wd, u32* ht);
void GXGetViewportv(f32* vp);
void GXProject(f32 x, f32 y, f32 z, const f32 mtx[3][4], const f32* pm, const f32* vp, f32* sx, f32* sy, f32* sz);
void GXSetProjection(const f32 mtx[4][4], GXProjectionType type);
void GXSetScissor(u32 left, u32 top, u32 wd, u32 ht);
void PSMTX44MultVec(const Mtx44 m, const Vec* src, Vec* dst);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
int sprintf(char *s, const char *format, ...);
char *strcpy(char *dest, const char *src);
size_t strlen(const char *s);
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void unk_8017599c(WinMgrEntry* entry) {
#ifdef NONMATCHING
	UnitWinWork* wp = _wp;
	const char* msg = msgSearch(itemDataTable[wp->goods[wp->goodsIdx]].name);
	s32 i;
	if (!winMgrAction(wp->winId[0])) {
		FontDrawStart();
		FontDrawEdge();
		FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
		FontDrawString(-FontGetMessageWidth(msg) / 2, 108.0f, msg);
		FontDrawEdgeOff();
	}
	for (i = 0; i < wp->goodsMax; i++) {
		if (!(wp->itemFlags[i] & 1)) {
			Mtx mtx;
			char buf[64];
			Vec pos;
			mapObjGetPos(wp->entries[i].mapObj, &pos);
			pos.y += 30.0f;
			PSMTXMultVec(camGetPtr(4)->view, &pos, &pos);
			PSMTX44MultVec(camGetPtr(4)->projection, &pos, &pos);
			pos.x *= gp->fbWidth / 2.0f;
			pos.y *= gp->efbHeight / 2.0f;
			sprintf(buf, "%d", itemDataTable[wp->goods[i]].discount_price);
			PSMTXTrans(mtx, 12.0f * (strlen(buf) - 1) + pos.x, pos.y, pos.z);
			iconNumberDispGx(mtx, itemDataTable[wp->goods[i]].discount_price, 0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
		}
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FF40
		opword 0x7C0802A6
		lis r3, itemDataTable@ha
		opword 0x900100C4
		addi r4, r3, itemDataTable@l
		opword 0xBF6100AC
		lwz r5, _wp(r13)
		opword 0x80050024
		opword 0x7CBC2B78
		opword 0x80650008
		opword 0x5400103A
		opword 0x7C03002E
		opword 0x1C000028
		opword 0x7C640214
		opword 0x80630004
		bl msgSearch
		opword 0x7C601B78
		opword 0x807C0060
		opword 0x7C1B0378
		bl winMgrAction
		opword 0x2C030000
		opword 0x40820068
		bl FontDrawStart
		bl FontDrawEdge
		lwz r0, dat_8041d9b4(r2)
		opword 0x3861000C
		opword 0x9001000C
		bl FontDrawColor
		opword 0x7F63DB78
		bl FontGetMessageWidth
		opword 0x5463043E
		opword 0x3C004330
		opword 0x7CA300D0
		opword 0x90010090
		opword 0x54A40FFE
		lis r3, double_to_int_802f68a8@ha
		opword 0x7C042A14
		lfd f1, double_to_int_802f68a8@l(r3)
		opword 0x7C000E70
		lfs f2, float_108_8041dadc(r2)
		opword 0x6C008000
		opword 0x7F63DB78
		opword 0x90010094
		opword 0xC8010090
		opword 0xEC200828
		bl FontDrawString
		bl FontDrawEdgeOff
		opword 0x3BC00000
		opword 0x7F9FE378
		opword 0x7FDDF378
		opword 0x3B600000
		opword 0x48000174
		opword 0xA01F000C
		opword 0x540007FF
		opword 0x40820158
		opword 0x807C0004
		opword 0x38810010
		opword 0x7C63F02E
		bl mapObjGetPos
		opword 0xC0210014
		opword 0x38600004
		lfs f0, float_30_8041dbf0(r2)
		opword 0xEC01002A
		opword 0xD0010014
		bl camGetPtr
		opword 0x38810010
		opword 0x3863011C
		opword 0x7C852378
		bl PSMTXMultVec
		opword 0x38600004
		bl camGetPtr
		opword 0x38810010
		opword 0x3863015C
		opword 0x7C852378
		bl PSMTX44MultVec
		lwz r7, gp(r13)
		opword 0x3CA04330
		lis r4, double_to_int_mask_802f68b8@ha
		lis r3, itemDataTable@ha
		opword 0xA0C70170
		addi r0, r3, itemDataTable@l
		lfd f3, double_to_int_mask_802f68b8@l(r4)
		opword 0x3861001C
		opword 0x90A10090
		la r4, str_8041DBAC(r2)
		lfs f2, float_0p5_8041db60(r2)
		opword 0x90C10094
		opword 0xC0810010
		opword 0xC8010090
		opword 0x90A10098
		opword 0xEC001828
		opword 0xC0210014
		opword 0xEC0000B2
		opword 0xEC040032
		opword 0xD0010010
		opword 0xA0A70172
		opword 0x90A1009C
		opword 0xC8010098
		opword 0xEC001828
		opword 0xEC0000B2
		opword 0xEC010032
		opword 0xD0010014
		opword 0x80BC0008
		opword 0x7CA5E82E
		opword 0x1CA50028
		opword 0x7CA02A14
		opword 0xA0A50016
		opword 0x4CC63182
		bl sprintf
		opword 0x3861001C
		bl strlen
		opword 0x3883FFFF
		opword 0x3C004330
		lis r3, double_to_int_mask_802f68b8@ha
		opword 0x908100A4
		addi r4, r3, double_to_int_mask_802f68b8@l
		lfs f1, float_12_8041dbfc(r2)
		opword 0x900100A0
		opword 0x3861005C
		opword 0xC8640000
		opword 0xC84100A0
		opword 0xC0010010
		opword 0xEC821828
		opword 0xC0410014
		opword 0xC0610018
		opword 0xEC21013A
		bl PSMTXTrans
		lwz r4, dat_8041d9b8(r2)
		lis r3, itemDataTable@ha
		addi r0, r3, itemDataTable@l
		opword 0x3861005C
		opword 0x90810008
		opword 0x38C10008
		opword 0x38A00000
		opword 0x809C0008
		opword 0x7C84E82E
		opword 0x1C840028
		opword 0x7C802214
		opword 0xA0840016
		bl iconNumberDispGx
		opword 0x3BFF0002
		opword 0x3BDE000C
		opword 0x3BBD0004
		opword 0x3B7B0001
		opword 0x801C0018
		opword 0x7C1B0000
		opword 0x4180FE88
		opword 0xBB6100AC
		opword 0x800100C4
		opword 0x7C0803A6
		opword 0x382100C0
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif


#define UNITWIN_UNUSED_INLINE(fn) static void fn(char* buf, const char* name, s32 n) { sprintf(buf, ((char*)str_802F68B0), name, n); }
#ifdef NONMATCHING
UNITWIN_UNUSED_INLINE(unitwin_fmt)
#endif

void unk_8017597c(WinMgrEntry* entry) {
	winMgrHelpMain(entry);
}

void unk_801758fc(WinMgrEntry* entry) {
	UnitWinWork* wp = _wp;
	s32 idx = wp->goodsIdx * 4;
	s32* goods = wp->goods;
	if (!winMgrAction(wp->winId[1])) {
		entry->msg = msgSearch(itemDataTable[*(s32*)((u8*)goods + idx)].description);
		winMgrHelpDraw(entry);
	}
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void unk_80175710(WinMgrEntry* entry) {
#ifdef NONMATCHING
	UnitWinWork* wp = _wp;
	PouchData* pouch = pouchGetPtr();
	s32 mode;
	Mtx trans;
	Mtx scale;
	s32 d;
	if (!(entry->flags & 4)) {
		PSMTXTrans(trans, 10.0f + (30.0f + entry->x), entry->y - 36.0f, 0.0f);
		if ((u32)gp->language == 0) {
			PSMTXScale(scale, 1.1f, 1.1f, 1.1f);
			PSMTXConcat(trans, scale, trans);
			iconDispGx2(trans, 0x10, 0x1F1);
		} else {
			PSMTXScale(scale, 0.8f, 1.1f, 1.1f);
			PSMTXConcat(trans, scale, trans);
			iconDispGx2(trans, 0x10, 0x20A);
		}
		PSMTXTrans(trans, 124.0f + entry->x, entry->y - 38.0f, 0.0f);
		{
			GXColor c = {0xFF, 0xFF, 0xFF, 0xFF};
			iconNumberDispGx(trans, wp->coinDisp, 0, c);
		}
		d = *(s16*)&pouch->mShopPoints - wp->coinDisp;
		if (d) {
			d /= 10;
			if (!d) {
				d = *(s16*)&pouch->mShopPoints > wp->coinDisp ? 1 : -1;
			}
			wp->coinDisp += d;
		}
#endif
#ifndef NONMATCHING
	char _af_pad[116];
	asm volatile {
		mr r29, r3
		lwz r30, _wp(r13)
		bl pouchGetPtr
		opword 0x801D0000
		opword 0x7C7F1B78
		opword 0x5400077B
		opword 0x408201A0
		opword 0x807D0018
		opword 0x3C804330
		opword 0x801D001C
		lis r5, double_to_int_802f68a8@ha
		opword 0x6C638000
		stw r4, _af_pad+104(r1)
		opword 0x6C008000
		lfd f2, double_to_int_802f68a8@l(r5)
		opword 0x90610074
		opword 0x3861003C
		lfs f3, float_30_8041dbf0(r2)
		opword 0xC8010070
		opword 0x9001007C
		opword 0xEC001028
		lfs f5, float_10_8041dbec(r2)
		opword 0x90810078
		opword 0xEC83002A
		opword 0xC8210078
		lfs f0, float_36_8041db64(r2)
		opword 0xEC411028
		lfs f3, float_0_8041db00(r2)
		opword 0xEC25202A
		opword 0xEC420028
		bl PSMTXTrans
		lwz r3, gp(r13)
		opword 0x8003016C
		opword 0x28000000
		opword 0x4082003C
		lfs f1, float_1p1_8041db30(r2)
		opword 0x3861000C
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x3861003C
		opword 0x3881000C
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x3861003C
		opword 0x38800010
		opword 0x38A001F1
		bl iconDispGx2
		opword 0x48000038
		lfs f2, float_1p1_8041db30(r2)
		opword 0x3861000C
		lfs f1, float_0p8_8041db74(r2)
		opword 0xFC601090
		bl PSMTXScale
		opword 0x3861003C
		opword 0x3881000C
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x3861003C
		opword 0x38800010
		opword 0x38A0020A
		bl iconDispGx2
		opword 0x807D0018
		opword 0x3C804330
		opword 0x801D001C
		lis r5, double_to_int_802f68a8@ha
		opword 0x6C638000
		opword 0x90810078
		opword 0x6C008000
		lfd f4, double_to_int_802f68a8@l(r5)
		opword 0x9061007C
		opword 0x3861003C
		lfs f3, float_124_8041dbf4(r2)
		opword 0xC8010078
		opword 0x90010074
		opword 0xEC202028
		lfs f0, float_38_8041dbf8(r2)
		opword 0x90810070
		opword 0xC8410070
		opword 0xEC23082A
		lfs f3, float_0_8041db00(r2)
		opword 0xEC422028
		opword 0xEC420028
		bl PSMTXTrans
		lwz r0, dat_8041d9bc(r2)
		opword 0x3861003C
		opword 0x38C10008
		opword 0x38A00000
		opword 0x90010008
		opword 0x809E0030
		bl iconNumberDispGx
		opword 0x809E0030
		opword 0xA8BF05B0
		opword 0x7CC42851
		opword 0x41820040
		opword 0x3C606666
		opword 0x38036667
		opword 0x7C003096
		opword 0x7C001670
		opword 0x54030FFE
		opword 0x7CC01A15
		opword 0x40820018
		opword 0x7C052000
		opword 0x3800FFFF
		opword 0x40810008
		opword 0x38000001
		opword 0x7C060378
		opword 0x801E0030
		opword 0x7C003214
		opword 0x901E0030
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
USER_FUNC(evt_unitwin_alloc) {
#endif
#ifndef NONMATCHING
s32 evt_unitwin_alloc(EventEntry* event, BOOL isFirstCall) {
#endif
	s32 arg = evtGetValue(event, event->args[0]);
	UnitWinWork* wp = _mapAlloc(sizeof(UnitWinWork));
	memset(wp, 0, sizeof(UnitWinWork));
	wp->field_0x50 = 0;
	_wp = wp;
	if (arg) {
		wp->flags |= 0x80;
	} else {
		wp->flags &= ~0x80;
	}
#ifdef NONMATCHING
	iconEntry2D("yubicursor_2", 0x1F0);
	iconFlagOn("yubicursor_2", 2);
	iconFlagOn("yubicursor_2", 4);
#endif
#ifndef NONMATCHING
	iconEntry2D(EXT_LIT((char*)str_802F6894, "yubicursor_2"), 0x1F0);
	iconFlagOn(EXT_LIT((char*)str_802F6894, "yubicursor_2"), 2);
	iconFlagOn(EXT_LIT((char*)str_802F6894, "yubicursor_2"), 4);
#endif
	if (!(wp->flags & 0x80)) {
		wp->evt = evtEntry(main_evt, 0, 0);
		wp->evt->lwData[0] = (s32)wp;
	}
	mario_status_point_table[0] = &pouchGetPtr()->baseMaxHP;
	mario_status_point_table[1] = &pouchGetPtr()->baseMaxFP;
	mario_status_point_table[2] = &pouchGetPtr()->maximumBP;
	return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_unitwin_free) {
#endif
#ifndef NONMATCHING
s32 evt_unitwin_free(EventEntry* event, BOOL isFirstCall) {
#endif
	UnitWinWork* wp = _wp;
	s32 i;
	char name[32];
	if (wp == NULL) {
		return EVT_RETURN_DONE;
	}
	if (isFirstCall) {
		wp->flags2 |= 1;
	}
	if (!(wp->flags2 & 2)) {
		return EVT_RETURN_BLOCK;
	}
	for (i = 0; i < wp->goodsMax; i++) {
		mapObjFlagOff(wp->entries[i].mapObj, 0x4000);
#ifdef NONMATCHING
		sprintf(name, "uwn%d", i);
#endif
#ifndef NONMATCHING
		sprintf(name, EXT_LIT((char*)str_8041DAC0, "uwn%d"), i);
#endif
		iconDelete(name);
	}
	if (wp->flags & 0x80) {
		for (i = 0; i < 3; i++) {
			winMgrDelete(wp->winId[i]);
		}
	}
#ifdef NONMATCHING
	iconDelete("yubicursor_2");
#endif
#ifndef NONMATCHING
	iconDelete(EXT_LIT((char*)str_802F6894, "yubicursor_2"));
#endif
	_mapFree(_wp);
	_wp = NULL;
	return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_unitwin_selltable_setup) {
	s32 i;
	s32* args = event->args;
	UnitWinEntry* tbl = (UnitWinEntry*)evtGetValue(event, args[0]);
	s32* goods = (s32*)evtGetValue(event, args[1]);
	UnitWinWork* wp = _wp;
	char name[32];
	Vec pos;
	wp->entries = tbl;
	wp->goods = goods;
	wp->goodsMax = 0;
	for (i = 0; wp->entries[i].mapObj != NULL; i++) {
		wp->goodsMax++;
		mapObjGetPos(wp->entries[i].mapObj, &pos);
		mapObjFlagOn(wp->entries[i].mapObj, 0x4000);
		if (wp->goods[i] != 0) {
			sprintf(name, "uwn%d", i);
			((void (*)(const char*, u16))iconEntry)(name, itemDataTable[wp->goods[i]].icon_id);
			iconSetPos(name, pos.x, pos.y + 6.0f, pos.z);
			iconFlagOn(name, 0x40);
		} else {
			wp->itemFlags[i] |= 1;
		}
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 evt_unitwin_selltable_setup(EventEntry* event, BOOL isFirstCall) {
	char _af_pad[44];
	asm volatile {
		opword 0x7C7C1B78
		lwz r27, 0x18(r3)
		opword 0x809B0000
		bl evtGetValue
		opword 0x809B0004
		opword 0x7C7B1B78
		opword 0x7F83E378
		bl evtGetValue
		lwz r29, _wp(r13)
		opword 0x3BE00000
		opword 0x3B800000
		opword 0x937D0004
		opword 0x7FBBEB78
		opword 0x7FFEFB78
		opword 0x907D0008
		opword 0x93FD0018
		opword 0x480000C0
		opword 0x807B0018
		la r4, _af_pad+0
		opword 0x38030001
		opword 0x901B0018
		opword 0x807B0004
		opword 0x7C63F82E
		bl mapObjGetPos
		opword 0x807B0004
		opword 0x38804000
		opword 0x7C63F82E
		bl mapObjFlagOn
		opword 0x807B0008
		opword 0x7C03F02E
		opword 0x2C000000
		opword 0x41820068
		opword 0x7F85E378
		opword 0x38610014
		la r4, str_8041DAC0(r2)
		opword 0x4CC63182
		bl sprintf
		opword 0x809B0008
		lis r3, itemDataTable@ha
		addi r0, r3, itemDataTable@l
		opword 0x38610014
		opword 0x7C84F02E
		opword 0x1C840028
		opword 0x7C802214
		opword 0xA0840020
		bl iconEntry
		lfs f2, float_6_8041dbe8(r2)
		opword 0x38610014
		opword 0xC001000C
		opword 0xC0210008
		opword 0xEC42002A
		opword 0xC0610010
		bl iconSetPos
		opword 0x38610014
		opword 0x38800040
		bl iconFlagOn
		opword 0x48000010
		opword 0xA01D000C
		opword 0x60000001
		opword 0xB01D000C
		opword 0x3BFF000C
		opword 0x3BDE0004
		opword 0x3BBD0002
		opword 0x3B9C0001
		opword 0x807B0004
		opword 0x7C03F82E
		opword 0x28000000
		opword 0x4082FF38
		la r3, select_evt(r13)
		opword 0x38800000
		opword 0x38A00020
		opword 0x38C00000
		bl evtEntryType
		opword 0x907B001C
		lis r3, unk_80375478@ha
		addi r28, r3, unk_80375478@l
		opword 0x7F7DDB78
		opword 0x807B001C
		opword 0x3BC00000
		opword 0x9363009C
		opword 0x7F83E378
		bl winMgrEntry
		opword 0x3BDE0001
		opword 0x907D0060
		opword 0x2C1E0003
		opword 0x3B9C0028
		opword 0x3BBD0004
		opword 0x4180FFE4
		opword 0x3800FFFF
		opword 0x38600002
		opword 0x901B00E0
#endif
	}
#ifdef NONMATCHING
	wp->evt = evtEntryType(select_evt, 0, 0x20, 0);
	wp->evt->lwData[0] = (s32)wp;
	for (i = 0; i < 3; i++) {
		wp->winId[i] = winMgrEntry(&unk_80375478[i]);
	}
	wp->selected = -1;
	return EVT_RETURN_DONE;
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
USER_FUNC(unitwincoin_disp_onoff) {
#endif
#ifndef NONMATCHING
s32 unitwincoin_disp_onoff(EventEntry* event, BOOL isFirstCall) {
#endif
	s32 on = evtGetValue(event, event->args[0]);
	UnitWinWork* wp;
	pouchGetPtr();
	wp = _wp;
	wp->coin = pouchGetCoin();
	wp->field_0x5C = 0;
	if (on) {
		wp->flags |= 0x1000;
	} else {
		wp->flags &= ~0x1000;
	}
	return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(unitwincoin_wait) {
#endif
#ifndef NONMATCHING
s32 unitwincoin_wait(EventEntry* event, BOOL isFirstCall) {
#endif
	UnitWinWork* wp = _wp;
	pouchGetPtr();
	if (wp->coin != pouchGetCoin()) {
		return EVT_RETURN_BLOCK;
	}
	return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(unk_8017524c) {
#endif
#ifndef NONMATCHING
s32 unk_8017524c(EventEntry* event, BOOL isFirstCall) {
#endif
	s32 on = evtGetValue(event, event->args[0]);
	UnitWinWork* wp = _wp;
	if (on) {
		wp->flags |= 0x100;
	} else {
		wp->flags &= ~0x100;
	}
	return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(unk_801751f8) {
#endif
#ifndef NONMATCHING
s32 unk_801751f8(EventEntry* event, BOOL isFirstCall) {
#endif
	s32* args = event->args;
	UnitWinWork* wp = (UnitWinWork*)evtGetValue(event, args[0]);
	wp->bought = evtGetValue(event, args[1]);
	return EVT_RETURN_DONE;
}

#define UNITWIN_CLOSE(wp)                \
	if ((wp)->selected != -1) {          \
		(wp)->selected = -1;             \
		winMgrClose((wp)->winId[0]);     \
		winMgrClose((wp)->winId[1]);     \
	}

#ifdef NONMATCHING
USER_FUNC(unk_80174e98) {
#endif
#ifndef NONMATCHING
s32 unk_80174e98(EventEntry* event, BOOL isFirstCall) {
#endif
	UnitWinWork* wp = (UnitWinWork*)event->lwData[0];
	s32 found = FALSE;
	MarioWork* mario = marioGetPtr();
	PartyEntry* party = partyGetPtr(0);
	HitEntry* hit = mario->hitobjStandOn;
	u32 btn;
	s32 i;
	char name[32];
	MapObject* obj;
	if (wp->flags2 & 1) {
		wp->flags2 |= 2;
		return EVT_RETURN_DONE;
	}
	wp->flags &= ~1;
	btn = keyGetButtonTrg(0);
	if ((marioChkCtrl() ? FALSE : TRUE) || (marioChkKey() ? FALSE : TRUE)) {
		btn = 0;
	}
	if (party != NULL && (party->flags & 0x100)) {
		UNITWIN_CLOSE(wp);
		return EVT_RETURN_BLOCK;
	}
	if (winGhostDiaryChk() || N_itemPickUpFromFieldCheck()) {
		UNITWIN_CLOSE(wp);
		return EVT_RETURN_BLOCK;
	}
	if (!(wp->flags & 2)) {
		if (hit != NULL) {
			for (i = 0; i < wp->goodsMax; i++) {
				const char* hitName = hitGetName(hit);
				if (!strcmp(wp->entries[i].hitName, hitName)) {
					break;
				}
			}
			if (!(wp->itemFlags[i] & 1) && i < wp->goodsMax) {
				if (wp->selected != i) {
					if (wp->selected == -1) {
						winMgrOpen(wp->winId[0]);
						winMgrOpen(wp->winId[1]);
					}
					wp->selected = i;
					wp->goodsIdx = i;
					winMgrHelpInit(winMgrGetPtr(wp->winId[1]));
				}
				found = TRUE;
			}
		}
		if (!found) {
			UNITWIN_CLOSE(wp);
		}
		if (wp->selected != -1) {
			wp->flags |= 1;
			if (btn & 0x100) {
				marioKeyOff();
				wp->childEvt = evtEntry(wp->entries[wp->goodsIdx].evt, 0, 0);
				wp->childEvt->lwData[0] = (s32)wp;
				wp->flags |= 2;
				winMgrClose(wp->winId[0]);
				winMgrClose(wp->winId[1]);
				wp->selected = -1;
				wp->bought = 0;
			}
		}
	} else if (!evtCheckID(wp->childEvt->eventId)) {
		wp->flags &= ~2;
		marioKeyOn();
		if (wp->bought) {
			wp->itemFlags[wp->goodsIdx] |= 1;
		}
	}
	for (i = 0; i < wp->goodsMax; i++) {
		obj = mapGetMapObj(wp->entries[i].mapObj);
		if (obj != NULL) {
#ifdef NONMATCHING
			sprintf(name, "uwn%d", i);
#endif
#ifndef NONMATCHING
			sprintf(name, EXT_LIT((char*)str_8041DAC0, "uwn%d"), i);
#endif
			if (wp->itemFlags[i] & 1) {
				iconFlagOn(name, 2);
			} else if (obj->flags & 1) {
				iconFlagOn(name, 2);
			} else {
				iconFlagOff(name, 2);
			}
		}
	}
	return EVT_RETURN_BLOCK;
}

#ifdef NONMATCHING
USER_FUNC(evt_unitwin_main_func) {
#endif
#ifndef NONMATCHING
s32 evt_unitwin_main_func(EventEntry* event, BOOL isFirstCall) {
#endif
	UnitWinWork* wp = (UnitWinWork*)event->lwData[0];
	if (wp->flags2 & 1) {
		wp->flags2 |= 2;
		return EVT_RETURN_DONE;
	}
	if (wp->timer > 0) {
		wp->timer--;
	} else {
		wp->flags &= ~1;
	}
#ifdef NONMATCHING
	dispEntry((CameraId)8, 1000.0f, 0, evt_unitwin_disp_func, wp);
#endif
#ifndef NONMATCHING
	dispEntry((CameraId)8, EXT_LIT(float_1000_8041dbe4, 1000.0f), 0, evt_unitwin_disp_func, wp);
#endif
	return EVT_RETURN_BLOCK;
}

#ifdef NONMATCHING
static inline s32 unitwin_party_icon(s32 icon) {
	if (icon == 0x158) {
		switch (pouchGetPartyColor(4)) {
			case 0:
				icon = 0x158;
				break;
			case 1:
				icon = 0x159;
				break;
			case 2:
				icon = 0x15A;
				break;
			case 3:
				icon = 0x15B;
				break;
			case 4:
				icon = 0x15C;
				break;
			case 5:
				icon = 0x15D;
				break;
			case 6:
			default:
				icon = 0x15E;
				break;
		}
	}
	return icon;
}
#endif

#define ICONGX ((void (*)(Vec*, u16, u16, f32))iconDispGx)
#define ICONGX2 ((void (*)(Vec*, u16, f32, u16))iconDispGx)

#ifndef NONMATCHING
extern void* jumptable_803754F0[];
extern void* jumptable_8037553C[];
extern void* jumptable_80375558[];
extern void* jumptable_80375574[];
extern void* jumptable_803755B8[];
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void evt_unitwin_disp_func(CameraId cameraId, void* param) {
#ifdef NONMATCHING
	PouchData* pouch = pouchGetPtr();
	UnitWinWork* wp = (UnitWinWork*)param;
	s32 mode;
	s32 row;
	s32 i;
	char fbuf[64];

	if (wp->flags & 1) {
		const char* desc = itemDataTable[wp->goods[wp->goodsIdx]].description;
		const char* name = itemDataTable[wp->goods[wp->goodsIdx]].id;

		windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, -150.0f, 120.0f, 300.0f, 50.0f, 20.0f);
		FontDrawStart();
		FontDrawEdge();
		FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
		FontDrawString((s32)(strlen(name) * 24 / 4) * -1, 108.0f, name);
		FontDrawEdgeOff();
		windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -240.0f, -130.0f, 480.0f, 70.0f, 20.0f);
		FontDrawStart();
		FontDrawMessage(-220, -138, msgSearch(desc));

		for (i = 0; i < wp->goodsMax; i++) {
			if (wp->goods[i] != 0) {
				Vec pos;
				f32 proj[7];
				f32 vp[6];
				f32 sx, sy, sz;
				Mtx mtx;
				CameraEntry* cam;
				s32 id;
				u8 price;

				mapObjGetPos(wp->entries[i].mapObj, &pos);
				cam = camGetPtr(4);
				GXSetProjection(cam->projection, cam->projType);
				GXGetProjectionv(proj);
				GXGetViewportv(vp);
				GXProject(pos.x, pos.y, pos.z, cam->view, proj, vp, &sx, &sy, &sz);
				cam = camGetPtr(cameraId);
				GXSetProjection(cam->projection, cam->projType);
				id = wp->goods[i];
				if (id >= 0xF0 && id < 0x153) {
					price = itemDataTable[id].discount_price;
				} else {
					price = itemDataTable[id].buy_price;
				}
				PSMTXTrans(mtx, 8.0f + (-304.0f + sx), 240.0f - (sy - 60.0f), 0.0f);
				iconNumberDispGx(mtx, price, 1, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			}
		}
#endif
#ifndef NONMATCHING
	char _af_pad[1768];
	asm volatile {
		lis r5, vec3_802f64b8@ha
		opword 0x7C741B78
		opword 0x7C8F2378
		addi r30, r5, vec3_802f64b8@l
		bl pouchGetPtr
		opword 0xA00F0000
		opword 0x7C6E1B78
		opword 0x540007FF
		opword 0x41820238
		opword 0x800F0024
		lis r3, itemDataTable@ha
		opword 0x808F0008
		addi r6, r3, itemDataTable@l
		opword 0x5403103A
		lwz r0, dat_8041d9c0(r2)
		opword 0x7CA4182E
		la r4, _af_pad+220
		lfs f1, float_neg150_8041dac8(r2)
		opword 0x38600000
		opword 0x1CE50028
		opword 0x900100E4
		lfs f2, float_120_8041dacc(r2)
		lfs f3, float_300_8041dad0(r2)
		opword 0x7CA63A14
		opword 0x7E26382E
		opword 0x82450008
		lfs f4, float_50_8041dad4(r2)
		lfs f5, float_20_8041dad8(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		bl FontDrawEdge
		lwz r0, dat_8041d9c4(r2)
		opword 0x386100E0
		opword 0x900100E0
		bl FontDrawColor
		opword 0x7E238B78
		bl strlen
		opword 0x1C830018
		opword 0x3C004330
		opword 0x900106D8
		opword 0x7E238B78
		opword 0xC83E03F0
		opword 0x5480F0BE
		opword 0x1C00FFFF
		lfs f2, float_108_8041dadc(r2)
		opword 0x6C008000
		opword 0x900106DC
		opword 0xC80106D8
		opword 0xEC200828
		bl FontDrawString
		bl FontDrawEdgeOff
		lwz r0, dat_8041d9c8(r2)
		opword 0x388100DC
		lfs f1, float_neg240_8041dae0(r2)
		opword 0x38600000
		opword 0x900100DC
		lfs f2, float_neg130_8041dae4(r2)
		lfs f3, float_480_8041dae8(r2)
		lfs f4, float_70_8041daec(r2)
		lfs f5, float_20_8041dad8(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		opword 0x7E439378
		bl msgSearch
		opword 0x7C651B78
		opword 0x3860FF24
		opword 0x3880FF76
		bl FontDrawMessage
		opword 0x3A200000
		opword 0x3A600000
		opword 0x7E328B78
		opword 0x48000130
		opword 0x806F0008
		opword 0x7C03882E
		opword 0x2C000000
		opword 0x41820114
		opword 0x806F0004
		opword 0x38810250
		opword 0x7C63902E
		bl mapObjGetPos
		opword 0x38600004
		bl camGetPtr
		opword 0x7C751B78
		opword 0x8083019C
		opword 0x3875015C
		bl GXSetProjection
		opword 0x38610354
		bl GXGetProjectionv
		opword 0x3861033C
		bl GXGetViewportv
		opword 0xC0210250
		opword 0x3875011C
		opword 0xC0410254
		opword 0x38810354
		opword 0xC0610258
		opword 0x38A1033C
		opword 0x38C10178
		opword 0x38E10174
		opword 0x39010170
		bl GXProject
		opword 0x7E83A378
		bl camGetPtr
		opword 0x8083019C
		opword 0x3863015C
		bl GXSetProjection
		opword 0x806F0008
		opword 0x7C03882E
		opword 0x2C0000F0
		opword 0x41800028
		opword 0x2C000153
		opword 0x40800020
		opword 0x1C800028
		lis r3, itemDataTable@ha
		addi r0, r3, itemDataTable@l
		opword 0x7C602214
		opword 0xA0030016
		opword 0x5415063E
		opword 0x4800001C
		opword 0x1C800028
		lis r3, itemDataTable@ha
		addi r0, r3, itemDataTable@l
		opword 0x7C602214
		opword 0xA0030014
		opword 0x5415063E
		lfs f3, float_neg304_8041daf4(r2)
		opword 0x38610620
		opword 0xC0410178
		opword 0xC0210174
		lfs f0, float_60_8041dafc(r2)
		opword 0xEC63102A
		lfs f4, float_8_8041daf0(r2)
		opword 0xEC010028
		lfs f2, float_240_8041daf8(r2)
		opword 0xEC24182A
		lfs f3, float_0_8041db00(r2)
		opword 0xEC420028
		bl PSMTXTrans
		lwz r0, dat_8041d9cc(r2)
		opword 0x38610620
		opword 0x56A4063E
		opword 0x38C100D8
		opword 0x900100D8
		opword 0x38A00001
		bl iconNumberDispGx
		opword 0x3A310004
		opword 0x3A52000C
		opword 0x3A730001
		opword 0x800F0018
		opword 0x7C130000
		opword 0x4180FECC
		opword 0xA00F0000
		opword 0x7000D000
		opword 0x418201D8
		lwz r0, dat_8041d9d0(r2)
		opword 0x388100D4
		lfs f1, float_neg250_8041db04(r2)
		opword 0x38600000
		opword 0x900100D4
		lfs f2, float_neg75_8041db08(r2)
		lfs f3, float_150_8041db0c(r2)
		lfs f4, float_45_8041db10(r2)
		lfs f5, float_20_8041dad8(r2)
		bl windowDispGX_Waku_col
		lfs f1, float_neg220_8041db14(r2)
		opword 0x386105F0
		lfs f2, float_neg113_8041db18(r2)
		lfs f3, float_0_8041db00(r2)
		bl PSMTXTrans
		lfs f1, float_0p7_8041db1c(r2)
		opword 0x386105C0
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x386105F0
		opword 0x388105C0
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0xA06F0000
		opword 0x546004E7
		opword 0x41820020
		opword 0x386105F0
		opword 0x38800010
		opword 0x38A0018B
		bl iconDispGx2
		bl pouchGetCoin
		opword 0x7C711B78
		opword 0x48000040
		opword 0x54600463
		opword 0x41820020
		opword 0x386105F0
		opword 0x38800010
		opword 0x38A00102
		bl iconDispGx2
		bl pouchGetSuperCoin
		opword 0x7C711B78
		opword 0x4800001C
		opword 0x386105F0
		opword 0x38800010
		opword 0x38A0018D
		bl iconDispGx2
		bl pouchGetStarPiece
		opword 0x7C711B78
		lfs f1, float_neg192_8041db20(r2)
		opword 0x386105F0
		lfs f2, float_neg113_8041db18(r2)
		lfs f3, float_0_8041db00(r2)
		bl PSMTXTrans
		opword 0x386105F0
		opword 0x38800010
		opword 0x38A001D6
		bl iconDispGx2
		lfs f1, float_neg126_8041db24(r2)
		opword 0x386105F0
		lfs f2, float_neg113_8041db18(r2)
		lfs f3, float_0_8041db00(r2)
		bl PSMTXTrans
		lwz r0, dat_8041d9d4(r2)
		opword 0x386105F0
		opword 0x38C100D0
		opword 0x38A00000
		opword 0x900100D0
		opword 0x808F002C
		bl iconNumberDispGx
		opword 0x808F002C
		opword 0x7CA48851
		opword 0x418200A0
		opword 0x3C606666
		opword 0x38036667
		opword 0x7C002896
		opword 0x7C001670
		opword 0x54030FFE
		opword 0x7CA01A15
		opword 0x40820018
		opword 0x7C112000
		opword 0x3800FFFF
		opword 0x40810008
		opword 0x38000001
		opword 0x7C050378
		opword 0x800F005C
		opword 0x540007FF
		opword 0x41820014
		opword 0x800F002C
		opword 0x7C002A14
		opword 0x900F002C
		bl statusWinForceUpdateCoin
		opword 0x808F005C
		opword 0x3C601B4F
		opword 0x380381B5
		opword 0x38640001
		opword 0x906F005C
		opword 0x808F005C
		opword 0x7C002096
		opword 0x7C003E70
		opword 0x54030FFE
		opword 0x7C001A14
		opword 0x1C0004B0
		opword 0x7C002050
		opword 0x900F005C
		lwz r0, unk_804189fc(r13)
		opword 0x2C000000
		opword 0x40820014
		opword 0x387E0184
		bl psndSFXOn
		opword 0x38000007
		stw r0, unk_804189fc(r13)
		lwz r3, unk_804189fc(r13)
		opword 0x2C030000
		opword 0x4081000C
		opword 0x3803FFFF
		stw r0, unk_804189fc(r13)
		opword 0xA00F0000
		opword 0x540004A5
		opword 0x41820100
		lwz r0, dat_8041d9d8(r2)
		opword 0x388100CC
		lfs f1, float_neg250_8041db04(r2)
		opword 0x38600000
		opword 0x900100CC
		lfs f2, float_neg130_8041dae4(r2)
		lfs f3, float_150_8041db0c(r2)
		lfs f4, float_45_8041db10(r2)
		lfs f5, float_20_8041dad8(r2)
		bl windowDispGX_Waku_col
		lfs f1, float_neg210_8041db28(r2)
		opword 0x38610590
		lfs f2, float_neg166_8041db2c(r2)
		lfs f3, float_0_8041db00(r2)
		bl PSMTXTrans
		lfs f1, float_1p1_8041db30(r2)
		opword 0x38610560
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x38610590
		opword 0x38810560
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x38610590
		opword 0x38800010
		opword 0x38A001F1
		bl iconDispGx2
		lfs f1, float_neg126_8041db24(r2)
		opword 0x38610590
		lfs f2, float_neg168_8041db34(r2)
		lfs f3, float_0_8041db00(r2)
		bl PSMTXTrans
		lwz r0, dat_8041d9dc(r2)
		opword 0x38610590
		opword 0x38C100C8
		opword 0x38A00000
		opword 0x900100C8
		opword 0x808F0030
		bl iconNumberDispGx
		lwz r3, gp(r13)
		opword 0x8003001C
		opword 0x540007BF
		opword 0x40820050
		opword 0x808F0030
		opword 0xA8AE009C
		opword 0x7CC42851
		opword 0x41820040
		opword 0x3C606666
		opword 0x38036667
		opword 0x7C003096
		opword 0x7C001670
		opword 0x54030FFE
		opword 0x7CC01A15
		opword 0x40820018
		opword 0x7C052000
		opword 0x3800FFFF
		opword 0x40810008
		opword 0x38000001
		opword 0x7C060378
		opword 0x800F0030
		opword 0x7C003214
		opword 0x900F0030
		opword 0xA00F0000
		opword 0x540005EF
		opword 0x418200F4
		bl lotteryGetPtr
		opword 0xA0030000
		opword 0x540007BD
		opword 0x418200E4
		lwz r0, dat_8041d9e0(r2)
		opword 0x388100C4
		lfs f1, float_neg250_8041db04(r2)
		opword 0x38600000
		opword 0x900100C4
		lfs f2, float_neg130_8041dae4(r2)
		lfs f3, float_150_8041db0c(r2)
		lfs f4, float_45_8041db10(r2)
		lfs f5, float_20_8041dad8(r2)
		bl windowDispGX_Waku_col
		lfs f1, float_neg220_8041db14(r2)
		opword 0x38610530
		lfs f2, float_neg172_8041db38(r2)
		lfs f3, float_0_8041db00(r2)
		bl PSMTXTrans
		opword 0x38610530
		opword 0x38800010
		opword 0x38A00140
		bl iconDispGx2
		bl lotteryGetPtr
		opword 0xA8A30020
		opword 0x3861031C
		la r4, str_8041DB3C(r2)
		opword 0x4CC63182
		bl sprintf
		lfs f28, float_20_8041dad8(r2)
		opword 0x3A41031C
		opword 0xCBBE03F0
		opword 0x3A600000
		lfs f30, float_neg126_8041db24(r2)
		opword 0x3E204330
		lfs f31, float_60_8041dafc(r2)
		opword 0x6E608000
		opword 0x922106D8
		lfs f2, float_neg168_8041db34(r2)
		opword 0x38610530
		opword 0x900106DC
		lfs f3, float_0_8041db00(r2)
		opword 0xC80106D8
		opword 0xEC00E828
		opword 0xEC1CF03A
		opword 0xEC20F828
		bl PSMTXTrans
		lwz r4, dat_8041d9e4(r2)
		opword 0x38610530
		opword 0x88120000
		opword 0x38C100C0
		opword 0x908100C0
		opword 0x38A00000
		opword 0x7C040774
		opword 0x3884FFD0
		bl iconNumberDispGx
		opword 0x3A730001
		opword 0x3A520001
		opword 0x2C130004
		opword 0x4180FFA4
		opword 0x808F0050
		opword 0x28040012
		opword 0x41812204
		lis r3, jumptable_803755B8@ha
		opword 0x5480103A
		addi r3, r3, jumptable_803755B8@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x3A400000
		opword 0x3A600000
		bl pouchGetKeepItemCnt
		opword 0x20030008
		opword 0x2C000000
		opword 0x40810010
		bl pouchGetKeepItemCnt
		opword 0x20030008
		opword 0x48000008
		opword 0x38000000
		opword 0x1DC00018
		opword 0x3C004330
		lwz r5, dat_8041d9e8(r2)
		opword 0x388100BC
		opword 0x900106D8
		opword 0x38600000
		opword 0x200E00DC
		opword 0xC89E03F0
		opword 0x6C008000
		opword 0x90A100BC
		lfs f1, float_neg24_8041db44(r2)
		opword 0x900106DC
		lfs f2, float_100_8041db48(r2)
		opword 0xC80106D8
		lfs f3, float_300_8041dad0(r2)
		opword 0xEC802028
		lfs f5, float_20_8041dad8(r2)
		bl windowDispGX_Waku_col
		lwz r0, dat_8041d9ec(r2)
		opword 0x388100B8
		lfs f1, float_51_8041db4c(r2)
		opword 0x38600000
		opword 0x900100B8
		lfs f2, float_114_8041db50(r2)
		lfs f3, float_150_8041db0c(r2)
		lfs f4, float_28_8041db54(r2)
		lfs f5, float_8_8041daf0(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		bl FontDrawEdge
		lwz r0, dat_8041d9f0(r2)
		opword 0x386100B4
		opword 0x900100B4
		bl FontDrawColor
		opword 0x387E0194
		bl msgSearch
		lfs f1, float_81_8041db58(r2)
		lfs f2, float_111_8041db5c(r2)
		bl FontDrawString
		bl FontDrawEdgeOff
		opword 0x3861016C
		opword 0x38810168
		opword 0x38A10164
		opword 0x38C10160
		bl GXGetScissor
		opword 0x20CE00BE
		opword 0x38600120
		opword 0x388000A2
		opword 0x38A0011C
		bl GXSetScissor
		opword 0x3A200000
		lis r3, itemDataTable@ha
		opword 0x7E308B78
		addi r14, r3, itemDataTable@l
		opword 0x7E238B78
		bl pouchKeepItem
		opword 0x1C030028
		opword 0x2C030000
		opword 0x7E8E0214
		opword 0x418200C8
		opword 0x20700038
		opword 0x3C004330
		opword 0x6C638000
		opword 0x80DE0000
		opword 0x906106DC
		opword 0x386101F4
		opword 0x80BE0004
		opword 0x38800010
		opword 0x900106D8
		opword 0x801E0008
		opword 0xC83E03F0
		opword 0xC80106D8
		opword 0x90C101F4
		opword 0xEC000828
		lfs f1, float_0p5_8041db60(r2)
		opword 0x90A101F8
		opword 0xA0B40020
		opword 0x900101FC
		opword 0xC04F0044
		opword 0xEC02002A
		opword 0xD00101F8
		bl iconDispGx
		bl FontDrawStart
		opword 0x20700050
		opword 0x3C004330
		opword 0x6C638000
		opword 0x900106E0
		opword 0xC85E03F0
		opword 0x906106E4
		opword 0xC06F0044
		opword 0xC80106E0
		lfs f1, float_36_8041db64(r2)
		opword 0xEC001028
		opword 0x80740000
		opword 0xEC43002A
		bl FontDrawString
		opword 0x6E438000
		opword 0x3C004330
		opword 0x906106EC
		opword 0xC85E03F0
		opword 0x900106E8
		opword 0xC00F0034
		opword 0xC82106E8
		opword 0xEC211028
		opword 0xFC010000
		opword 0x40820008
		opword 0x82740008
		opword 0x3A100018
		opword 0x3A520001
		opword 0x3A310001
		opword 0x2C110020
		opword 0x4180FF1C
		opword 0x8061016C
		opword 0x80810168
		opword 0x80A10164
		opword 0x80C10160
		bl GXSetScissor
		opword 0x28130000
		opword 0x41821FE8
		lwz r0, dat_8041d9f4(r2)
		opword 0x388100B0
		lfs f1, float_neg240_8041dae0(r2)
		opword 0x38600000
		opword 0x900100B0
		lfs f2, float_neg130_8041dae4(r2)
		lfs f3, float_480_8041dae8(r2)
		lfs f4, float_70_8041daec(r2)
		lfs f5, float_20_8041dad8(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		opword 0x7E639B78
		bl msgSearch
		opword 0x7C651B78
		opword 0x3860FF24
		opword 0x3880FF76
		bl FontDrawMessage
		opword 0x48001FA0
		opword 0x2C040002
		opword 0x3A800000
		opword 0x3AA00000
		opword 0x4182000C
		opword 0x2C040003
		opword 0x40820040
		bl pouchGetHaveItemCnt
		opword 0x20030008
		opword 0x2C000000
		opword 0x40810010
		bl pouchGetHaveItemCnt
		opword 0x20030008
		opword 0x48000008
		opword 0x38000000
		opword 0x1DC00018
		opword 0x387E0194
		opword 0x3AC00014
		bl msgSearch
		opword 0x3A20001E
		opword 0x7C701B78
		opword 0x4800012C
		opword 0x2C04000C
		opword 0x40820040
		bl pouchGetHaveBadgeCnt
		opword 0x20030008
		opword 0x2C000000
		opword 0x40810010
		bl pouchGetHaveBadgeCnt
		opword 0x20030008
		opword 0x48000008
		opword 0x38000000
		opword 0x1DC00018
		opword 0x387E01A8
		opword 0x3AC000C8
		bl msgSearch
		opword 0x3A200028
		opword 0x7C701B78
		opword 0x480000E8
		opword 0x2C04000E
		opword 0x40820038
		opword 0x800F0058
		opword 0x387E01BC
		opword 0x3AC00152
		opword 0x20800008
		opword 0x7C0400D0
		opword 0x7C002078
		opword 0x7C00FE70
		opword 0x7C800038
		opword 0x1DC00018
		bl msgSearch
		opword 0x3A200014
		opword 0x7C701B78
		opword 0x480000AC
		opword 0x2C04000F
		opword 0x40820038
		opword 0x800F0058
		opword 0x387E01BC
		opword 0x20800008
		opword 0x7C160378
		opword 0x7C0400D0
		opword 0x7C002078
		opword 0x7C00FE70
		opword 0x7C800038
		opword 0x1DC00018
		bl msgSearch
		opword 0x3A200014
		opword 0x7C701B78
		opword 0x48000070
		opword 0x2C040010
		opword 0x40820038
		opword 0x800F0058
		opword 0x387E01D0
		opword 0x3AC00152
		opword 0x20800008
		opword 0x7C0400D0
		opword 0x7C002078
		opword 0x7C00FE70
		opword 0x7C800038
		opword 0x1DC00018
		bl msgSearch
		opword 0x3A20001E
		opword 0x7C701B78
		opword 0x48000034
		opword 0x800F0058
		opword 0x387E01A8
		opword 0x3AC00063
		opword 0x20800008
		opword 0x7C0400D0
		opword 0x7C002078
		opword 0x7C00FE70
		opword 0x7C800038
		opword 0x1DC00018
		bl msgSearch
		opword 0x3A200028
		opword 0x7C701B78
		opword 0x206E00DC
		opword 0x3C004330
		opword 0x6C638000
		lwz r5, dat_8041d9f8(r2)
		opword 0x906106EC
		opword 0x388100AC
		opword 0xC85E03F0
		opword 0x38600000
		opword 0x900106E8
		lfs f1, float_neg24_8041db44(r2)
		opword 0xC80106E8
		opword 0x90A100AC
		opword 0xEC801028
		lfs f2, float_100_8041db48(r2)
		lfs f3, float_300_8041dad0(r2)
		lfs f5, float_20_8041dad8(r2)
		bl windowDispGX_Waku_col
		lwz r0, dat_8041d9fc(r2)
		opword 0x388100A8
		lfs f1, float_51_8041db4c(r2)
		opword 0x38600000
		opword 0x900100A8
		lfs f2, float_114_8041db50(r2)
		lfs f3, float_150_8041db0c(r2)
		lfs f4, float_28_8041db54(r2)
		lfs f5, float_8_8041daf0(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		bl FontDrawEdge
		lwz r0, dat_8041da00(r2)
		opword 0x386100A4
		opword 0x900100A4
		bl FontDrawColor
		opword 0x38710033
		opword 0x3C004330
		opword 0x6C648000
		opword 0x900106E0
		opword 0xC83E03F0
		opword 0x7E038378
		opword 0x908106E4
		lfs f2, float_111_8041db5c(r2)
		opword 0xC80106E0
		opword 0xEC200828
		bl FontDrawString
		bl FontDrawEdgeOff
		opword 0x800F0050
		opword 0x2C000003
		opword 0x418200AC
		lfs f1, float_244_8041db68(r2)
		opword 0x38610500
		lfs f2, float_82_8041db6c(r2)
		lfs f3, float_0_8041db00(r2)
		bl PSMTXTrans
		lfs f1, float_0p6_8041db70(r2)
		opword 0x386104D0
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x38610500
		opword 0x388104D0
		opword 0x7C651B78
		bl PSMTXConcat
		lwz r0, dat_8041da04(r2)
		opword 0x38610500
		opword 0x38C100A0
		opword 0x38800010
		opword 0x900100A0
		opword 0x38A00211
		bl iconDispGxCol
		opword 0x800F0050
		opword 0x2C00000D
		opword 0x4082000C
		opword 0x3800018D
		opword 0x48000018
		opword 0x2C000010
		opword 0x4082000C
		opword 0x3800013F
		opword 0x48000008
		opword 0x3800018B
		opword 0x80FE000C
		opword 0x386101E8
		opword 0x80DE0010
		opword 0x5405043E
		opword 0x801E0014
		opword 0x38800010
		opword 0x90E101E8
		lfs f1, float_0p6_8041db70(r2)
		opword 0x90C101EC
		opword 0x900101F0
		bl iconDispGx
		opword 0x3861015C
		opword 0x38810158
		opword 0x38A10154
		opword 0x38C10150
		bl GXGetScissor
		opword 0x20CE00BE
		opword 0x38600120
		opword 0x388000A2
		opword 0x38A0011C
		bl GXSetScissor
		lis r3, badge_bottakuru100_table@ha
		opword 0x3A600000
		addi r16, r3, badge_bottakuru100_table@l
		lis r3, itemDataTable@ha
		opword 0x7E719B78
		addi r14, r3, itemDataTable@l
		opword 0x48000400
		opword 0x800F0050
		opword 0x3A400000
		lwz r3, dat_8041da08(r2)
		opword 0x28000010
		opword 0x9061014C
		opword 0x418100FC
		lis r3, jumptable_80375574@ha
		opword 0x5400103A
		addi r3, r3, jumptable_80375574@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x7E639B78
		bl pouchHaveItem
		opword 0x7C771B78
		opword 0x480000D4
		opword 0x7E639B78
		bl pouchHaveBadge
		opword 0x7C771B78
		opword 0x480000C4
		lwz r3, bdsw(r13)
		opword 0x381300F0
		opword 0x7C040734
		opword 0x38630019
		bl badgeShop_get
		opword 0x7C770734
		opword 0x387300F0
		bl badgeShop_ThrowCheck
		opword 0x7C03B851
		opword 0x4081000C
		opword 0x3AF300F0
		opword 0x48000094
		opword 0x3AE00000
		opword 0x4800008C
		lwz r3, bdsw(r13)
		opword 0x381300F0
		opword 0x7C040734
		opword 0x38630032
		bl badgeShop_get
		opword 0x7C600735
		opword 0x4081000C
		opword 0x3AF300F0
		opword 0x48000068
		opword 0x3AE00000
		opword 0x48000060
		lwz r3, bdsw(r13)
		opword 0x38130001
		opword 0x7C040734
		opword 0x3863004B
		bl badgeShop_get
		opword 0x7C600735
		opword 0x4081000C
		opword 0x3AF30001
		opword 0x4800003C
		opword 0x3AE00000
		opword 0x48000034
		opword 0x82F00000
		opword 0x4800002C
		lwz r3, bdsw(r13)
		opword 0x38130001
		opword 0x7C040734
		opword 0x386300A0
		bl badgeShop_get
		opword 0x7C600735
		opword 0x4081000C
		opword 0x3AF30001
		opword 0x48000008
		opword 0x3AE00000
		opword 0x1C170028
		opword 0x2C170000
		opword 0x7F0E0214
		opword 0x418202D8
		opword 0x800F0050
		opword 0x2C00000D
		opword 0x40820020
		bl pouchGetStarPiece
		opword 0xA0180018
		opword 0x7C001800
		opword 0x40810010
		lwz r0, dat_8041da0c(r2)
		opword 0x3A400020
		opword 0x9001014C
		opword 0x20110038
		opword 0x3C804330
		opword 0x6C008000
		opword 0x80DE0018
		opword 0x900106EC
		opword 0x62400010
		opword 0x80BE001C
		opword 0x386101DC
		opword 0x908106E8
		opword 0x5404043E
		opword 0x801E0020
		opword 0xC83E03F0
		opword 0xC80106E8
		opword 0x90C101DC
		opword 0xEC000828
		lfs f1, float_0p5_8041db60(r2)
		opword 0x90A101E0
		opword 0xA0B80020
		opword 0x900101E4
		opword 0xC04F0044
		opword 0xEC02002A
		opword 0xD00101E0
		bl iconDispGx
		bl FontDrawStart
		lfs f1, float_0p8_8041db74(r2)
		bl FontDrawScale
		opword 0x8001014C
		opword 0x3861009C
		opword 0x9001009C
		bl FontDrawColor
		opword 0x22510050
		opword 0x3C004330
		opword 0x6E438000
		opword 0x900106E0
		opword 0xC85E03F0
		opword 0x906106E4
		opword 0xC06F0044
		opword 0xC82106E0
		lfs f0, float_2_8041db78(r2)
		opword 0xEC411028
		lfs f1, float_36_8041db64(r2)
		opword 0x80780000
		opword 0xEC43102A
		opword 0xEC420028
		bl FontDrawString
		opword 0x800F0050
		opword 0x2C000003
		opword 0x418201BC
		opword 0x2C00000E
		opword 0x41820030
		opword 0x4080001C
		opword 0x2C00000C
		opword 0x4182012C
		opword 0x40800108
		opword 0x2C00000B
		opword 0x408000E0
		opword 0x4800011C
		opword 0x2C000010
		opword 0x41820098
		opword 0x40800110
		opword 0x48000040
		opword 0xA0180014
		opword 0x3C606666
		opword 0x38A36667
		opword 0x386102FC
		opword 0x1C00000C
		la r4, str_8041DB7C(r2)
		opword 0x7C050096
		opword 0x7C001670
		opword 0x54050FFE
		opword 0x7CA02A14
		opword 0x4CC63182
		bl sprintf
		lfs f28, float_1_8041db80(r2)
		opword 0x3B200000
		opword 0x480000EC
		opword 0x3C80F5DE
		opword 0x38600000
		opword 0x388406A9
		bl evtGetValue
		opword 0xA0180014
		opword 0x3883000B
		opword 0x3CA06666
		opword 0x386102FC
		opword 0x7C0021D6
		la r4, str_8041DB84(r2)
		opword 0x38A56667
		opword 0x7C050096
		opword 0x7C001670
		opword 0x54050FFE
		opword 0x7CA02A14
		opword 0x4CC63182
		bl sprintf
		lfs f28, float_1_8041db80(r2)
		opword 0x3B20FFF2
		opword 0x4800009C
		opword 0xA0180014
		opword 0x3C605555
		opword 0x38C35556
		opword 0x386102FC
		opword 0x5405083C
		la r4, str_8041DB88(r2)
		opword 0x38050002
		opword 0x7CA60096
		opword 0x54A00FFE
		opword 0x7CA50214
		opword 0x4CC63182
		bl sprintf
		lfs f28, float_0p8_8041db74(r2)
		opword 0x3B20FFEC
		opword 0x48000060
		opword 0xA0B80014
		opword 0x386102FC
		la r4, str_8041DB7C(r2)
		opword 0x4CC63182
		bl sprintf
		lfs f28, float_1_8041db80(r2)
		opword 0x3B200000
		opword 0x48000040
		opword 0xA0B80018
		opword 0x386102FC
		la r4, str_8041DB7C(r2)
		opword 0x4CC63182
		bl sprintf
		lfs f28, float_1_8041db80(r2)
		opword 0x3B200000
		opword 0x48000020
		opword 0xA0B8001A
		opword 0x386102FC
		la r4, str_8041DB7C(r2)
		opword 0x4CC63182
		bl sprintf
		opword 0x3B200000
		lfs f28, float_1_8041db80(r2)
		bl FontDrawStart
		opword 0xFC20E090
		bl FontDrawScale
		opword 0x8001014C
		opword 0x38610098
		opword 0x90010098
		bl FontDrawColor
		opword 0x3C804330
		opword 0x6E408000
		opword 0x900106E4
		opword 0x381900E2
		opword 0x6C008000
		opword 0xC89E03F0
		opword 0x908106E0
		opword 0x386102FC
		opword 0xC02F0044
		opword 0xC80106E0
		opword 0x900106EC
		opword 0xEC002028
		opword 0x908106E8
		opword 0xC86106E8
		opword 0xEC41002A
		opword 0xEC232028
		bl FontDrawString
		opword 0x6E838000
		opword 0x3C004330
		opword 0x906106EC
		opword 0xC85E03F0
		opword 0x900106E8
		opword 0xC00F0034
		opword 0xC82106E8
		opword 0xEC211028
		opword 0xFC010000
		opword 0x40820008
		opword 0x82B80008
		opword 0x3A310018
		opword 0x3A940001
		opword 0x3A100004
		opword 0x3A730001
		opword 0x7C13B000
		opword 0x4180FC00
		opword 0x8061015C
		opword 0x80810158
		opword 0x80A10154
		opword 0x80C10150
		bl GXSetScissor
		opword 0x28150000
		opword 0x41821858
		lwz r0, dat_8041da10(r2)
		opword 0x38810094
		lfs f1, float_neg240_8041dae0(r2)
		opword 0x38600000
		opword 0x90010094
		lfs f2, float_neg130_8041dae4(r2)
		lfs f3, float_480_8041dae8(r2)
		lfs f4, float_70_8041daec(r2)
		lfs f5, float_20_8041dad8(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		opword 0x7EA3AB78
		bl msgSearch
		opword 0x7C651B78
		opword 0x3860FF24
		opword 0x3880FF76
		bl FontDrawMessage
		opword 0x48001810
		opword 0x800F0058
		lis r3, _jdt@ha
		opword 0x2C040011
		opword 0x20800008
		addi r14, r3, _jdt@l
		opword 0x7C0400D0
		opword 0x7C002078
		opword 0x7C00FE70
		opword 0x7C800038
		opword 0x1E200018
		opword 0x40820018
		opword 0x387E01E4
		bl msgSearch
		opword 0x3A4E0021
		opword 0x7C701B78
		opword 0x48000014
		opword 0x387E01F8
		bl msgSearch
		opword 0x3A4E002E
		opword 0x7C701B78
		opword 0x207100DC
		opword 0x3C004330
		opword 0x6C638000
		lwz r5, dat_8041da14(r2)
		opword 0x906106EC
		opword 0x38810090
		opword 0xC85E03F0
		opword 0x38600000
		opword 0x900106E8
		lfs f1, float_neg24_8041db44(r2)
		opword 0xC80106E8
		opword 0x90A10090
		opword 0xEC801028
		lfs f2, float_100_8041db48(r2)
		lfs f3, float_300_8041dad0(r2)
		lfs f5, float_20_8041dad8(r2)
		bl windowDispGX_Waku_col
		lwz r0, dat_8041da18(r2)
		opword 0x3881008C
		lfs f1, float_51_8041db4c(r2)
		opword 0x38600000
		opword 0x9001008C
		lfs f2, float_114_8041db50(r2)
		lfs f3, float_150_8041db0c(r2)
		lfs f4, float_28_8041db54(r2)
		lfs f5, float_8_8041daf0(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		bl FontDrawEdge
		lwz r0, dat_8041da1c(r2)
		opword 0x38610088
		opword 0x90010088
		bl FontDrawColor
		lfs f1, float_71_8041db8c(r2)
		opword 0x7E038378
		lfs f2, float_111_8041db5c(r2)
		bl FontDrawString
		bl FontDrawEdgeOff
		opword 0x800F0050
		opword 0x2C000011
		opword 0x40820084
		lfs f1, float_244_8041db68(r2)
		opword 0x386104A0
		lfs f2, float_82_8041db6c(r2)
		lfs f3, float_0_8041db00(r2)
		bl PSMTXTrans
		lfs f1, float_0p6_8041db70(r2)
		opword 0x38610470
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x386104A0
		opword 0x38810470
		opword 0x7C651B78
		bl PSMTXConcat
		lwz r0, dat_8041da20(r2)
		opword 0x386104A0
		opword 0x38C10084
		opword 0x38800010
		opword 0x90010084
		opword 0x38A00211
		bl iconDispGxCol
		opword 0x80FE0024
		opword 0x386101D0
		opword 0x80DE0028
		opword 0x38800010
		opword 0x801E002C
		opword 0x38A0018B
		opword 0x90E101D0
		lfs f1, float_0p6_8041db70(r2)
		opword 0x90C101D4
		opword 0x900101D8
		bl iconDispGx
		opword 0x38610148
		opword 0x38810144
		opword 0x38A10140
		opword 0x38C1013C
		bl GXGetScissor
		opword 0x20D100BE
		opword 0x38600120
		opword 0x388000A2
		opword 0x38A0011C
		bl GXSetScissor
		opword 0x3A000000
		opword 0x822E0000
		opword 0xCBFE03F0
		opword 0x7E0E8378
		opword 0x3E604330
		opword 0x48000114
		opword 0xA891000C
		opword 0x7E439378
		bl johoya_get
		opword 0x7C600735
		opword 0x41820020
		opword 0x386102DC
		la r4, float_0_8041db90(r2)
		opword 0x4CC63182
		bl sprintf
		lwz r0, dat_8041da24(r2)
		opword 0x90010138
		opword 0x48000020
		opword 0xA8B1000A
		opword 0x386102DC
		la r4, str_8041DB84(r2)
		opword 0x4CC63182
		bl sprintf
		lwz r0, dat_8041da28(r2)
		opword 0x90010138
		bl FontDrawStart
		opword 0x80D10004
		opword 0x38800000
		opword 0xA8B10008
		opword 0x38610080
		opword 0x80010138
		opword 0x7EA628AE
		opword 0x7C8629AE
		opword 0x90010080
		bl FontDrawColor
		lfs f1, float_0p8_8041db74(r2)
		bl FontDrawScale
		opword 0x228E0050
		opword 0x926106E8
		opword 0x6E808000
		opword 0xC04F0044
		opword 0x900106EC
		lfs f1, float_1_8041db80(r2)
		opword 0xC80106E8
		opword 0x80710004
		opword 0xEC00F828
		opword 0xEC42002A
		bl FontDrawString
		opword 0x80710004
		opword 0xA8110008
		opword 0x7EA301AE
		opword 0x800F0050
		opword 0x2C000011
		opword 0x40820048
		bl FontDrawStart
		opword 0x80010138
		opword 0x3861007C
		opword 0x9001007C
		bl FontDrawColor
		opword 0x6E838000
		opword 0x3C004330
		opword 0x906106EC
		opword 0x386102DC
		opword 0xC85E03F0
		opword 0x900106E8
		opword 0xC06F0044
		opword 0xC80106E8
		lfs f1, float_221_8041db94(r2)
		opword 0xEC001028
		opword 0xEC43002A
		bl FontDrawString
		opword 0x39CE0018
		opword 0x3A100001
		opword 0x3A310010
		opword 0x800F0058
		opword 0x7C100000
		opword 0x4180FEE8
		opword 0x80610148
		opword 0x80810144
		opword 0x80A10140
		opword 0x80C1013C
		bl GXSetScissor
		opword 0x48001528
		opword 0x833E0030
		opword 0x3C004330
		opword 0x80BE0034
		opword 0x38810078
		opword 0x82FE0038
		opword 0x3B000000
		opword 0x82DE003C
		opword 0x38600000
		opword 0x82BE0040
		opword 0x829E0044
		opword 0x827E0048
		opword 0x825E004C
		opword 0x823E0050
		opword 0x819E0054
		opword 0x817E0058
		opword 0x815E005C
		opword 0x813E0060
		opword 0x811E0064
		opword 0x80FE0068
		opword 0x80DE006C
		opword 0x93210430
		opword 0xC89E03F0
		opword 0x90A10434
		lwz r5, dat_8041da2c(r2)
		opword 0x92E10438
		lfs f1, float_neg24_8041db44(r2)
		opword 0x92C1043C
		lfs f2, float_100_8041db48(r2)
		opword 0x92A10440
		lfs f3, float_300_8041dad0(r2)
		opword 0x92810444
		lfs f5, float_20_8041dad8(r2)
		opword 0x92610448
		opword 0x9241044C
		opword 0x92210450
		opword 0x91810454
		opword 0x91610458
		opword 0x9141045C
		opword 0x91210460
		opword 0x91010464
		opword 0x90E10468
		opword 0x90C1046C
		opword 0x80CF0058
		opword 0x900106E8
		opword 0x20C60008
		opword 0x7C0600D0
		opword 0x90A10078
		opword 0x7C003078
		opword 0x7C00FE70
		opword 0x7CC00038
		opword 0x1E200018
		opword 0x201100DC
		opword 0x6C008000
		opword 0x900106EC
		opword 0xC80106E8
		opword 0xEC802028
		bl windowDispGX_Waku_col
		lwz r0, dat_8041da30(r2)
		opword 0x38810074
		lfs f1, float_16_8041db98(r2)
		opword 0x38600000
		opword 0x90010074
		lfs f2, float_114_8041db50(r2)
		lfs f3, float_120_8041dacc(r2)
		lfs f4, float_28_8041db54(r2)
		lfs f5, float_8_8041daf0(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		bl FontDrawEdge
		lwz r0, dat_8041da34(r2)
		opword 0x38610070
		opword 0x90010070
		bl FontDrawColor
		opword 0x387E020C
		bl msgSearch
		lfs f1, float_41_8041db9c(r2)
		lfs f2, float_111_8041db5c(r2)
		bl FontDrawString
		bl FontDrawEdgeOff
		lwz r0, dat_8041da38(r2)
		opword 0x3881006C
		lfs f1, float_167_8041dba0(r2)
		opword 0x38600000
		opword 0x9001006C
		lfs f2, float_114_8041db50(r2)
		lfs f3, float_85_8041dba4(r2)
		lfs f4, float_28_8041db54(r2)
		lfs f5, float_8_8041daf0(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		bl FontDrawEdge
		lwz r0, dat_8041da3c(r2)
		opword 0x38610068
		opword 0x90010068
		bl FontDrawColor
		opword 0x387E0220
		bl msgSearch
		lfs f1, float_177_8041dba8(r2)
		lfs f2, float_111_8041db5c(r2)
		bl FontDrawString
		bl FontDrawEdgeOff
		opword 0x38610134
		opword 0x38810130
		opword 0x38A1012C
		opword 0x38C10128
		bl GXGetScissor
		opword 0x20D100BE
		opword 0x38600120
		opword 0x388000A2
		opword 0x38A0011C
		bl GXSetScissor
		opword 0x3AC00000
		la r17, party_id_table(r13)
		opword 0x7ED9B378
		la r19, party_icon_table(r13)
		opword 0x7ED2B378
		la r20, party_labelname_table(r13)
		opword 0x480003CC
		opword 0x800F0050
		opword 0x2C000005
		opword 0x4182000C
		opword 0x2C000006
		opword 0x408200A8
		bl partyChkJoin
		opword 0x2C030000
		opword 0x41820398
		opword 0x3C80F840
		opword 0x38600000
		opword 0x38846022
		bl evtGetValue
		opword 0x2C030000
		opword 0x40820044
		opword 0x80110000
		opword 0x1C60000E
		opword 0x3803000C
		opword 0x7C0E02AE
		opword 0x2C000001
		opword 0x40800018
		lwz r0, dat_8041da40(r2)
		opword 0x3AE00000
		opword 0x3AA00000
		opword 0x90010124
		opword 0x480000AC
		lwz r0, dat_8041da44(r2)
		opword 0x3AE00001
		opword 0x3AA00020
		opword 0x90010124
		opword 0x48000098
		opword 0x80110000
		opword 0x1C60000E
		opword 0x3803000C
		opword 0x7C0E02AE
		opword 0x2C000002
		opword 0x40800018
		lwz r0, dat_8041da48(r2)
		opword 0x3AE00000
		opword 0x3AA00000
		opword 0x90010124
		opword 0x4800006C
		lwz r0, dat_8041da4c(r2)
		opword 0x3AE00002
		opword 0x3AA00020
		opword 0x90010124
		opword 0x48000058
		bl partyChkJoin
		opword 0x2C030000
		opword 0x418202F4
		opword 0x800F004C
		opword 0x80710000
		opword 0x7C001800
		opword 0x418202E4
		opword 0x1C63000E
		opword 0x3803000C
		opword 0x7C0E02AE
		opword 0x2C000000
		opword 0x40810018
		lwz r0, dat_8041da50(r2)
		opword 0x3AE00000
		opword 0x3AA00000
		opword 0x90010124
		opword 0x48000014
		lwz r0, dat_8041da54(r2)
		opword 0x3AE00001
		opword 0x3AA00020
		opword 0x90010124
		opword 0x20720038
		opword 0x3C004330
		opword 0x6C638000
		opword 0x809E0070
		opword 0x906106EC
		opword 0x807E0074
		opword 0x900106E8
		opword 0x801E0078
		opword 0xC83E03F0
		opword 0xC80106E8
		opword 0x908101C4
		opword 0x80930000
		opword 0xEC000828
		opword 0x906101C8
		opword 0x2C040158
		opword 0x900101CC
		opword 0xC02F0044
		opword 0xEC01002A
		opword 0xD00101C8
		opword 0x40820060
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x28030006
		opword 0x4181004C
		lis r4, jumptable_80375558@ha
		opword 0x5460103A
		addi r3, r4, jumptable_80375558@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x38800158
		opword 0x48000030
		opword 0x38800159
		opword 0x48000028
		opword 0x3880015A
		opword 0x48000020
		opword 0x3880015B
		opword 0x48000018
		opword 0x3880015C
		opword 0x48000010
		opword 0x3880015D
		opword 0x48000008
		opword 0x3880015E
		opword 0x62A00010
		lfs f1, float_0p5_8041db60(r2)
		opword 0x386101C4
		opword 0x5485043E
		opword 0x5404043E
		bl iconDispGx
		bl FontDrawStart
		opword 0x80010124
		opword 0x38610064
		opword 0x90010064
		bl FontDrawColor
		opword 0x28160006
		opword 0x41810080
		lis r3, jumptable_8037553C@ha
		addi r3, r3, jumptable_8037553C@l
		opword 0x7C03C82E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x387E0234
		bl msgSearch
		opword 0x7C701B78
		opword 0x4800005C
		opword 0x387E0240
		bl msgSearch
		opword 0x7C701B78
		opword 0x4800004C
		opword 0x387E024C
		bl msgSearch
		opword 0x7C701B78
		opword 0x4800003C
		bl pouchGetYoshiName
		opword 0x7C701B78
		opword 0x48000030
		opword 0x387E0258
		bl msgSearch
		opword 0x7C701B78
		opword 0x48000020
		opword 0x387E0264
		bl msgSearch
		opword 0x7C701B78
		opword 0x48000010
		opword 0x387E0270
		bl msgSearch
		opword 0x7C701B78
		opword 0x22B20050
		opword 0x3C004330
		opword 0x6EA48000
		opword 0x900106E8
		opword 0xC85E03F0
		opword 0x7E038378
		opword 0x908106EC
		opword 0xC06F0044
		opword 0xC80106E8
		lfs f1, float_36_8041db64(r2)
		opword 0xEC001028
		opword 0xEC43002A
		bl FontDrawString
		opword 0x80110000
		opword 0x386102BC
		la r4, str_8041DBAC(r2)
		opword 0x1CA0000E
		opword 0x3805000C
		opword 0x7CAE02AE
		opword 0x4CC63182
		bl sprintf
		bl FontDrawStart
		opword 0x6EA38000
		opword 0x3C004330
		opword 0x906106E4
		opword 0x386102BC
		opword 0xC85E03F0
		opword 0x900106E0
		opword 0xC06F0044
		opword 0xC80106E0
		lfs f1, float_236_8041dbb0(r2)
		opword 0xEC001028
		opword 0xEC43002A
		bl FontDrawString
		opword 0x6F038000
		opword 0x3C004330
		opword 0x906106DC
		opword 0xC85E03F0
		opword 0x900106D8
		opword 0xC00F0034
		opword 0xC82106D8
		opword 0xEC211028
		opword 0xFC010000
		opword 0x40820098
		opword 0x2C170000
		opword 0x40820018
		opword 0x38610240
		la r4, str_8041DBB4(r2)
		opword 0x4CC63182
		bl sprintf
		opword 0x48000014
		opword 0x38610240
		opword 0x389E027C
		opword 0x4CC63182
		bl sprintf
		opword 0x800F0050
		opword 0x2C000005
		opword 0x4182000C
		opword 0x2C000006
		opword 0x40820018
		opword 0x38610230
		opword 0x389E0284
		opword 0x4CC63182
		bl sprintf
		opword 0x48000014
		opword 0x38610230
		opword 0x389E028C
		opword 0x4CC63182
		bl sprintf
		opword 0x80110000
		opword 0x38610430
		opword 0x81140000
		opword 0x389E0298
		opword 0x1CE0000E
		opword 0x38A10240
		opword 0x38C10230
		opword 0x3807000C
		opword 0x7CEE02AE
		opword 0x38E70001
		opword 0x4CC63182
		bl sprintf
		opword 0x3A520018
		opword 0x3B180001
		opword 0x3A310004
		opword 0x3A730004
		opword 0x3A940004
		opword 0x3AD60001
		opword 0x3B390004
		opword 0x80710000
		opword 0x2C030000
		opword 0x4082FC30
		opword 0x80610134
		opword 0x80810130
		opword 0x80A1012C
		opword 0x80C10128
		bl GXSetScissor
		opword 0x88010430
		opword 0x7C000775
		opword 0x41820F5C
		lwz r0, dat_8041da58(r2)
		opword 0x38810060
		lfs f1, float_neg240_8041dae0(r2)
		opword 0x38600000
		opword 0x90010060
		lfs f2, float_neg130_8041dae4(r2)
		lfs f3, float_480_8041dae8(r2)
		lfs f4, float_70_8041daec(r2)
		lfs f5, float_20_8041dad8(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		opword 0x38610430
		bl msgSearch
		opword 0x7C651B78
		opword 0x3860FF24
		opword 0x3880FF76
		bl FontDrawMessage
		opword 0x48000F14
		opword 0x82FE007C
		opword 0x3C004330
		opword 0x80BE0080
		opword 0x3881005C
		opword 0x82DE0084
		opword 0x3A400000
		opword 0x82BE0088
		opword 0x38600000
		opword 0x829E008C
		opword 0x827E0090
		opword 0x823E0094
		opword 0x821E0098
		opword 0x81DE009C
		opword 0x819E00A0
		opword 0x817E00A4
		opword 0x815E00A8
		opword 0x813E00AC
		opword 0x811E00B0
		opword 0x80FE00B4
		opword 0x80DE00B8
		opword 0x92E103F0
		opword 0xC89E03F0
		opword 0x90A103F4
		lwz r5, dat_8041da5c(r2)
		opword 0x92C103F8
		lfs f1, float_neg24_8041db44(r2)
		opword 0x92A103FC
		lfs f2, float_100_8041db48(r2)
		opword 0x92810400
		lfs f3, float_300_8041dad0(r2)
		opword 0x92610404
		lfs f5, float_20_8041dad8(r2)
		opword 0x92210408
		opword 0x9201040C
		opword 0x91C10410
		opword 0x91810414
		opword 0x91610418
		opword 0x9141041C
		opword 0x91210420
		opword 0x91010424
		opword 0x90E10428
		opword 0x90C1042C
		opword 0x80CF0058
		opword 0x900106E8
		opword 0x20C60008
		opword 0x7C0600D0
		opword 0x90A1005C
		opword 0x7C003078
		opword 0x7C00FE70
		opword 0x7CC00038
		opword 0x1DC00018
		opword 0x200E00DC
		opword 0x6C008000
		opword 0x900106EC
		opword 0xC80106E8
		opword 0xEC802028
		bl windowDispGX_Waku_col
		lwz r0, dat_8041da60(r2)
		opword 0x38810058
		lfs f1, float_16_8041db98(r2)
		opword 0x38600000
		opword 0x90010058
		lfs f2, float_114_8041db50(r2)
		lfs f3, float_120_8041dacc(r2)
		lfs f4, float_28_8041db54(r2)
		lfs f5, float_8_8041daf0(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		bl FontDrawEdge
		lwz r0, dat_8041da64(r2)
		opword 0x38610054
		opword 0x90010054
		bl FontDrawColor
		opword 0x387E02A8
		bl msgSearch
		lfs f1, float_21_8041dbbc(r2)
		lfs f2, float_111_8041db5c(r2)
		bl FontDrawString
		bl FontDrawEdgeOff
		lwz r0, dat_8041da68(r2)
		opword 0x38810050
		lfs f1, float_167_8041dba0(r2)
		opword 0x38600000
		opword 0x90010050
		lfs f2, float_114_8041db50(r2)
		lfs f3, float_85_8041dba4(r2)
		lfs f4, float_28_8041db54(r2)
		lfs f5, float_8_8041daf0(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		bl FontDrawEdge
		lwz r0, dat_8041da6c(r2)
		opword 0x3861004C
		opword 0x9001004C
		bl FontDrawColor
		opword 0x387E02BC
		bl msgSearch
		lfs f1, float_177_8041dba8(r2)
		lfs f2, float_111_8041db5c(r2)
		bl FontDrawString
		bl FontDrawEdgeOff
		opword 0x38610120
		opword 0x3881011C
		opword 0x38A10118
		opword 0x38C10114
		bl GXGetScissor
		opword 0x20CE00BE
		opword 0x38600120
		opword 0x388000A2
		opword 0x38A0011C
		bl GXSetScissor
		opword 0x3A800000
		la r14, mario_status_point_table(r13)
		opword 0xCBFE03F0
		opword 0x7E9DA378
		opword 0x7DDB7378
		la r24, mario_status_henka_table(r13)
		la r28, mario_status_icon_table(r13)
		la r26, mario_status_name_table(r13)
		la r25, mario_status_labelname_table(r13)
		opword 0x3FE04330
		opword 0x480003E0
		la r5, mario_status_henka_table(r13)
		opword 0x7DC67378
		opword 0x39000000
		opword 0x38E00000
		opword 0x7C0903A6
		opword 0x2C000000
		opword 0x4081004C
		opword 0x6CE08000
		opword 0x93E106E8
		opword 0xC00F0034
		opword 0x900106EC
		opword 0xC82106E8
		opword 0xEC21F828
		opword 0xFC010000
		opword 0x4182001C
		opword 0x80660000
		opword 0x80850000
		opword 0xA8030000
		opword 0x7C040051
		opword 0x41810008
		opword 0x39000001
		opword 0x38A50004
		opword 0x38C60004
		opword 0x38E70001
		opword 0x4200FFBC
		opword 0x2C080000
		opword 0x40820018
		lwz r0, dat_8041da70(r2)
		opword 0x3A000000
		opword 0x38600000
		opword 0x90010110
		opword 0x48000014
		lwz r0, dat_8041da74(r2)
		opword 0x3A000001
		opword 0x38600020
		opword 0x90010110
		opword 0x22FD0038
		opword 0x80BE00BC
		opword 0x6EE08000
		opword 0x80FE00C0
		opword 0x900106EC
		opword 0x60760010
		opword 0x80DE00C4
		opword 0x386101B8
		opword 0x93E106E8
		opword 0x56C4043E
		opword 0x801C0000
		opword 0xC80106E8
		opword 0x90A101B8
		opword 0x5405043E
		opword 0xEC00F828
		lfs f1, float_0p5_8041db60(r2)
		opword 0x90E101BC
		opword 0x90C101C0
		opword 0xC04F0044
		opword 0xEC02002A
		opword 0xD00101BC
		bl iconDispGx
		bl FontDrawStart
		opword 0x80010110
		opword 0x38610048
		opword 0x90010048
		bl FontDrawColor
		opword 0x80DB0000
		opword 0x3861029C
		opword 0x80BA0000
		la r4, str_8041DBC0(r2)
		opword 0xA8C60000
		opword 0x4CC63182
		bl sprintf
		opword 0x22BD0050
		opword 0x93E106E0
		opword 0x6EA08000
		opword 0xC04F0044
		opword 0x900106E4
		opword 0x3861029C
		lfs f1, float_36_8041db64(r2)
		opword 0xC80106E0
		opword 0xEC00F828
		opword 0xEC42002A
		bl FontDrawString
		opword 0x6E408000
		lwz r4, gp(r13)
		opword 0x900106DC
		opword 0x38600007
		opword 0x8084001C
		opword 0x38000002
		opword 0x93E106D8
		opword 0x5484073E
		opword 0xC00F0034
		opword 0xC82106D8
		opword 0x7C641810
		opword 0x7C631910
		opword 0xEC21F828
		opword 0x7C131878
		opword 0xFC010000
		opword 0x4082014C
		opword 0x2C100000
		opword 0x40820018
		opword 0x38610220
		la r4, str_8041DBB4(r2)
		opword 0x4CC63182
		bl sprintf
		opword 0x48000014
		opword 0x38610220
		opword 0x389E027C
		opword 0x4CC63182
		bl sprintf
		opword 0x80D90000
		opword 0x386103F0
		opword 0x389E02D0
		opword 0x38A10220
		opword 0x4CC63182
		bl sprintf
		opword 0x807B0000
		opword 0x80180000
		opword 0xA8630000
		opword 0x5400083C
		opword 0x7E230215
		opword 0x4081000C
		opword 0x3A0001B5
		opword 0x4800000C
		opword 0x3A000162
		opword 0x3A600000
		opword 0x3CC04330
		opword 0x6EE08000
		opword 0x900106E4
		opword 0x6E608000
		opword 0x813E00C8
		opword 0x386101AC
		opword 0x90C106E0
		opword 0x56C4043E
		opword 0x811E00CC
		opword 0x5605043E
		opword 0x80FE00D0
		opword 0xC87E03F0
		opword 0xC80106E0
		opword 0x912101AC
		opword 0xEC001828
		lfs f1, float_0p5_8041db60(r2)
		opword 0x910101B0
		opword 0x90E101B4
		opword 0xC04F0044
		opword 0x900106EC
		opword 0xEC02002A
		opword 0x90C106E8
		opword 0xC84106E8
		opword 0xEC421828
		opword 0xEC02002A
		opword 0xD00101B0
		bl iconDispGx
		opword 0x3CC04330
		opword 0x6EE08000
		opword 0x900106F4
		opword 0x6E608000
		opword 0x813E00D4
		opword 0x386101A0
		opword 0x90C106F0
		opword 0x56C4043E
		opword 0x811E00D8
		opword 0x5605043E
		opword 0x80FE00DC
		opword 0xC87E03F0
		opword 0xC80106F0
		opword 0x912101A0
		opword 0xEC001828
		lfs f1, float_0p5_8041db60(r2)
		opword 0x910101A4
		opword 0x90E101A8
		opword 0xC04F0044
		opword 0x900106DC
		opword 0xEC02002A
		opword 0x90C106D8
		opword 0xC84106D8
		opword 0xEC421828
		opword 0xEC02002A
		opword 0xD00101A4
		bl iconDispGx
		opword 0x48000094
		opword 0x807B0000
		opword 0x80980000
		opword 0xA8030000
		opword 0x7E240051
		opword 0x4081000C
		opword 0x38A001B6
		opword 0x4800000C
		opword 0x38A00162
		opword 0x3A600000
		opword 0x3CC04330
		opword 0x6EE08000
		opword 0x900106F4
		opword 0x6E608000
		opword 0x813E00E0
		opword 0x38610194
		opword 0x90C106F0
		opword 0x56C4043E
		opword 0x811E00E4
		opword 0x54A5043E
		opword 0x80FE00E8
		opword 0xC87E03F0
		opword 0xC80106F0
		opword 0x91210194
		opword 0xEC001828
		lfs f1, float_0p5_8041db60(r2)
		opword 0x91010198
		opword 0x90E1019C
		opword 0xC04F0044
		opword 0x900106EC
		opword 0xEC42002A
		opword 0x90C106E8
		opword 0xC80106E8
		opword 0xEC001828
		opword 0xEC020028
		opword 0xD0010198
		bl iconDispGx
		opword 0x2C110000
		opword 0x4081001C
		opword 0x7E258B78
		opword 0x3861029C
		la r4, str_8041DB84(r2)
		opword 0x4CC63182
		bl sprintf
		opword 0x48000018
		opword 0x7E258B78
		opword 0x3861029C
		la r4, str_8041DBC8(r2)
		opword 0x4CC63182
		bl sprintf
		bl FontDrawStart
		opword 0x6EA08000
		opword 0x93E106F0
		opword 0xC04F0044
		opword 0x3861029C
		opword 0x900106F4
		lfs f1, float_206_8041dbd0(r2)
		opword 0xC80106F0
		opword 0xEC00F828
		opword 0xEC42002A
		bl FontDrawString
		opword 0x3BBD0018
		opword 0x3A520001
		opword 0x3B9C0004
		opword 0x3B7B0004
		opword 0x3B5A0004
		opword 0x3B390004
		opword 0x3B180004
		opword 0x3A940001
		opword 0x800F0058
		opword 0x7C140000
		opword 0x4180FC1C
		opword 0x80610120
		opword 0x8081011C
		opword 0x80A10118
		opword 0x80C10114
		bl GXSetScissor
		opword 0x880103F0
		opword 0x7C000775
		opword 0x41820924
		lwz r0, dat_8041da78(r2)
		opword 0x38810044
		lfs f1, float_neg240_8041dae0(r2)
		opword 0x38600000
		opword 0x90010044
		lfs f2, float_neg130_8041dae4(r2)
		lfs f3, float_480_8041dae8(r2)
		lfs f4, float_70_8041daec(r2)
		lfs f5, float_20_8041dad8(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		opword 0x386103F0
		bl msgSearch
		opword 0x7C651B78
		opword 0x3860FF24
		opword 0x3880FF76
		bl FontDrawMessage
		opword 0x480008DC
		opword 0x82DE00EC
		opword 0x3C004330
		opword 0x80BE00F0
		opword 0x38810040
		opword 0x82BE00F4
		opword 0x3B600000
		opword 0x829E00F8
		opword 0x38600000
		opword 0x827E00FC
		opword 0x825E0100
		opword 0x823E0104
		opword 0x821E0108
		opword 0x81DE010C
		opword 0x819E0110
		opword 0x817E0114
		opword 0x815E0118
		opword 0x813E011C
		opword 0x811E0120
		opword 0x80FE0124
		opword 0x80DE0128
		opword 0x92C103B0
		opword 0xC89E03F0
		opword 0x90A103B4
		lwz r5, dat_8041da7c(r2)
		opword 0x92A103B8
		lfs f1, float_neg24_8041db44(r2)
		opword 0x928103BC
		lfs f2, float_100_8041db48(r2)
		opword 0x926103C0
		lfs f3, float_300_8041dad0(r2)
		opword 0x924103C4
		lfs f5, float_20_8041dad8(r2)
		opword 0x922103C8
		opword 0x920103CC
		opword 0x91C103D0
		opword 0x918103D4
		opword 0x916103D8
		opword 0x914103DC
		opword 0x912103E0
		opword 0x910103E4
		opword 0x90E103E8
		opword 0x90C103EC
		opword 0x80CF0058
		opword 0x900106F0
		opword 0x20C60008
		opword 0x7C0600D0
		opword 0x90A10040
		opword 0x7C003078
		opword 0x7C00FE70
		opword 0x7CC00038
		opword 0x1DC00018
		opword 0x200E00DC
		opword 0x6C008000
		opword 0x900106F4
		opword 0xC80106F0
		opword 0xEC802028
		bl windowDispGX_Waku_col
		lwz r0, dat_8041da80(r2)
		opword 0x3881003C
		lfs f1, float_16_8041db98(r2)
		opword 0x38600000
		opword 0x9001003C
		lfs f2, float_114_8041db50(r2)
		lfs f3, float_120_8041dacc(r2)
		lfs f4, float_28_8041db54(r2)
		lfs f5, float_8_8041daf0(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		bl FontDrawEdge
		lwz r0, dat_8041da84(r2)
		opword 0x38610038
		opword 0x90010038
		bl FontDrawColor
		opword 0x387E02A8
		bl msgSearch
		lfs f1, float_21_8041dbbc(r2)
		lfs f2, float_111_8041db5c(r2)
		bl FontDrawString
		bl FontDrawEdgeOff
		lwz r0, dat_8041da88(r2)
		opword 0x38810034
		lfs f1, float_167_8041dba0(r2)
		opword 0x38600000
		opword 0x90010034
		lfs f2, float_114_8041db50(r2)
		lfs f3, float_85_8041dba4(r2)
		lfs f4, float_28_8041db54(r2)
		lfs f5, float_8_8041daf0(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		bl FontDrawEdge
		lwz r0, dat_8041da8c(r2)
		opword 0x38610030
		opword 0x90010030
		bl FontDrawColor
		opword 0x387E02BC
		bl msgSearch
		lfs f1, float_177_8041dba8(r2)
		lfs f2, float_111_8041db5c(r2)
		bl FontDrawString
		bl FontDrawEdgeOff
		opword 0x3861010C
		opword 0x38810108
		opword 0x38A10104
		opword 0x38C10100
		bl GXGetScissor
		opword 0x20CE00BE
		opword 0x38600120
		opword 0x388000A2
		opword 0x38A0011C
		bl GXSetScissor
		opword 0x3B200000
		la r23, mario_status_point_table(r13)
		la r22, mario_status_henka_table(r13)
		opword 0xCBFE03F0
		opword 0x7F30CB78
		opword 0x7EF2BB78
		opword 0x7ED5B378
		la r17, mario_status_icon_table(r13)
		la r19, mario_status_name_table(r13)
		la r20, mario_status_labelname_table(r13)
		opword 0x3DC04330
		opword 0x48000238
		opword 0x7EC5B378
		opword 0x7EE6BB78
		opword 0x39000000
		opword 0x38E00000
		opword 0x7C0903A6
		opword 0x2C000000
		opword 0x4081004C
		opword 0x6CE08000
		opword 0x91C106F0
		opword 0xC00F0034
		opword 0x900106F4
		opword 0xC82106F0
		opword 0xEC21F828
		opword 0xFC010000
		opword 0x4182001C
		opword 0x80660000
		opword 0x80850000
		opword 0xA8030000
		opword 0x7C040051
		opword 0x41810008
		opword 0x39080001
		opword 0x38A50004
		opword 0x38C60004
		opword 0x38E70001
		opword 0x4200FFBC
		opword 0x2C080002
		opword 0x40800018
		lwz r0, dat_8041da90(r2)
		opword 0x3B400000
		opword 0x38600000
		opword 0x900100FC
		opword 0x48000014
		lwz r0, dat_8041da94(r2)
		opword 0x3B400001
		opword 0x38600020
		opword 0x900100FC
		opword 0x20100038
		opword 0x80BE012C
		opword 0x6C008000
		opword 0x80FE0130
		opword 0x900106F4
		opword 0x60600010
		opword 0x80DE0134
		opword 0x38610188
		opword 0x91C106F0
		opword 0x5404043E
		opword 0x80110000
		opword 0xC80106F0
		opword 0x90A10188
		opword 0x5405043E
		opword 0xEC00F828
		lfs f1, float_0p5_8041db60(r2)
		opword 0x90E1018C
		opword 0x90C10190
		opword 0xC04F0044
		opword 0xEC02002A
		opword 0xD001018C
		bl iconDispGx
		bl FontDrawStart
		opword 0x800100FC
		opword 0x3861002C
		opword 0x9001002C
		bl FontDrawColor
		opword 0x80D20000
		opword 0x3861027C
		opword 0x80B30000
		la r4, str_8041DBC0(r2)
		opword 0xA8C60000
		opword 0x4CC63182
		bl sprintf
		opword 0x23100050
		opword 0x91C106E8
		opword 0x6F008000
		opword 0xC04F0044
		opword 0x900106EC
		opword 0x3861027C
		lfs f1, float_36_8041db64(r2)
		opword 0xC80106E8
		opword 0xEC00F828
		opword 0xEC42002A
		bl FontDrawString
		opword 0x6F608000
		opword 0x91C106E0
		opword 0xC00F0034
		opword 0x900106E4
		opword 0xC82106E0
		opword 0xEC21F828
		opword 0xFC010000
		opword 0x408200B4
		opword 0x2C1A0000
		opword 0x40820018
		opword 0x38610210
		la r4, str_8041DBB4(r2)
		opword 0x4CC63182
		bl sprintf
		opword 0x48000014
		opword 0x38610210
		opword 0x389E027C
		opword 0x4CC63182
		bl sprintf
		opword 0x80D40000
		opword 0x386103B0
		opword 0x389E02D0
		opword 0x38A10210
		opword 0x4CC63182
		bl sprintf
		opword 0x80720000
		opword 0x80150000
		opword 0xA8630000
		opword 0x7CA30215
		opword 0x40810018
		opword 0x3861027C
		la r4, str_8041DB84(r2)
		opword 0x4CC63182
		bl sprintf
		opword 0x48000014
		opword 0x3861027C
		la r4, str_8041DBC8(r2)
		opword 0x4CC63182
		bl sprintf
		bl FontDrawStart
		opword 0x6F038000
		opword 0x3C004330
		opword 0x906106F4
		opword 0x3861027C
		opword 0xC85E03F0
		opword 0x900106F0
		opword 0xC06F0044
		opword 0xC80106F0
		lfs f1, float_206_8041dbd0(r2)
		opword 0xEC001028
		opword 0xEC43002A
		bl FontDrawString
		opword 0x3A100018
		opword 0x3B7B0001
		opword 0x3A310004
		opword 0x3A520004
		opword 0x3A730004
		opword 0x3A940004
		opword 0x3AB50004
		opword 0x3B390001
		opword 0x800F0058
		opword 0x7C190000
		opword 0x4180FDC4
		opword 0x8061010C
		opword 0x80810108
		opword 0x80A10104
		opword 0x80C10100
		bl GXSetScissor
		opword 0x880103B0
		opword 0x7C000775
		opword 0x41820490
		lwz r0, dat_8041da98(r2)
		opword 0x38810028
		lfs f1, float_neg240_8041dae0(r2)
		opword 0x38600000
		opword 0x90010028
		lfs f2, float_neg130_8041dae4(r2)
		lfs f3, float_480_8041dae8(r2)
		lfs f4, float_70_8041daec(r2)
		lfs f5, float_20_8041dad8(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		opword 0x386103B0
		bl msgSearch
		opword 0x7C651B78
		opword 0x3860FF24
		opword 0x3880FF76
		bl FontDrawMessage
		opword 0x48000448
		opword 0x82DE0138
		opword 0x3C004330
		opword 0x80BE013C
		opword 0x38810024
		opword 0x82BE0140
		opword 0x3AE00000
		opword 0x829E0144
		opword 0x38600000
		opword 0x827E0148
		opword 0x825E014C
		opword 0x823E0150
		opword 0x821E0154
		opword 0x81DE0158
		opword 0x819E015C
		opword 0x817E0160
		opword 0x815E0164
		opword 0x813E0168
		opword 0x811E016C
		opword 0x80FE0170
		opword 0x80DE0174
		opword 0x92C10370
		opword 0xC89E03F0
		opword 0x90A10374
		lwz r5, dat_8041da9c(r2)
		opword 0x92A10378
		lfs f1, float_neg24_8041db44(r2)
		opword 0x9281037C
		lfs f2, float_100_8041db48(r2)
		opword 0x92610380
		lfs f3, float_300_8041dad0(r2)
		opword 0x92410384
		lfs f5, float_20_8041dad8(r2)
		opword 0x92210388
		opword 0x9201038C
		opword 0x91C10390
		opword 0x91810394
		opword 0x91610398
		opword 0x9141039C
		opword 0x912103A0
		opword 0x910103A4
		opword 0x90E103A8
		opword 0x90C103AC
		opword 0x80CF0058
		opword 0x900106F0
		opword 0x20C60008
		opword 0x7C0600D0
		opword 0x90A10024
		opword 0x7C003078
		opword 0x7C00FE70
		opword 0x7CC00038
		opword 0x1DC00018
		opword 0x200E00DC
		opword 0x6C008000
		opword 0x900106F4
		opword 0xC80106F0
		opword 0xEC802028
		bl windowDispGX_Waku_col
		lwz r0, dat_8041daa0(r2)
		opword 0x38810020
		lfs f1, float_16_8041db98(r2)
		opword 0x38600000
		opword 0x90010020
		lfs f2, float_114_8041db50(r2)
		lfs f3, float_120_8041dacc(r2)
		lfs f4, float_28_8041db54(r2)
		lfs f5, float_8_8041daf0(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		bl FontDrawEdge
		lwz r0, dat_8041daa4(r2)
		opword 0x3861001C
		opword 0x9001001C
		bl FontDrawColor
		opword 0x387E02A8
		bl msgSearch
		lfs f1, float_21_8041dbbc(r2)
		lfs f2, float_111_8041db5c(r2)
		bl FontDrawString
		bl FontDrawEdgeOff
		lwz r0, dat_8041daa8(r2)
		opword 0x38810018
		lfs f1, float_167_8041dba0(r2)
		opword 0x38600000
		opword 0x90010018
		lfs f2, float_114_8041db50(r2)
		lfs f3, float_85_8041dba4(r2)
		lfs f4, float_28_8041db54(r2)
		lfs f5, float_8_8041daf0(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		bl FontDrawEdge
		lwz r0, dat_8041daac(r2)
		opword 0x38610014
		opword 0x90010014
		bl FontDrawColor
		opword 0x387E02BC
		bl msgSearch
		lfs f1, float_177_8041dba8(r2)
		lfs f2, float_111_8041db5c(r2)
		bl FontDrawString
		bl FontDrawEdgeOff
		opword 0x386100F8
		opword 0x388100F4
		opword 0x38A100F0
		opword 0x38C100EC
		bl GXGetScissor
		opword 0x20CE00BE
		opword 0x38600120
		opword 0x388000A2
		opword 0x38A0011C
		bl GXSetScissor
		opword 0x3AC00000
		la r14, mario_status_henka_table(r13)
		opword 0x7ED1B378
		la r16, mario_status_point_table(r13)
		la r18, mario_status_icon_table(r13)
		la r19, mario_status_name_table(r13)
		la r20, mario_status_labelname_table(r13)
		opword 0x800F004C
		opword 0x7C160000
		opword 0x418201E0
		opword 0x80700000
		opword 0x808E0000
		opword 0xA8030000
		opword 0x7C040051
		opword 0x40810018
		lwz r0, dat_8041dab0(r2)
		opword 0x3B000000
		opword 0x38600000
		opword 0x900100E8
		opword 0x48000014
		lwz r0, dat_8041dab4(r2)
		opword 0x3B000001
		opword 0x38600020
		opword 0x900100E8
		opword 0x20110038
		opword 0x3C804330
		opword 0x6C008000
		opword 0x80FE0178
		opword 0x900106F4
		opword 0x60600010
		opword 0x80BE017C
		opword 0x3861017C
		opword 0x908106F0
		opword 0x5404043E
		opword 0x80DE0180
		opword 0xC83E03F0
		opword 0xC80106F0
		opword 0x90E1017C
		opword 0xEC000828
		opword 0x80120000
		opword 0x90A10180
		lfs f1, float_0p5_8041db60(r2)
		opword 0x5405043E
		opword 0x90C10184
		opword 0xC04F0044
		opword 0xEC02002A
		opword 0xD0010180
		bl iconDispGx
		bl FontDrawStart
		opword 0x800100E8
		opword 0x38610010
		opword 0x90010010
		bl FontDrawColor
		opword 0x80D00000
		opword 0x3861025C
		opword 0x80B30000
		la r4, str_8041DBC0(r2)
		opword 0xA8C60000
		opword 0x4CC63182
		bl sprintf
		opword 0x22B10050
		opword 0x3C004330
		opword 0x6EA48000
		opword 0x900106E8
		opword 0xC85E03F0
		opword 0x3861025C
		opword 0x908106EC
		opword 0xC06F0044
		opword 0xC80106E8
		lfs f1, float_36_8041db64(r2)
		opword 0xEC001028
		opword 0xEC43002A
		bl FontDrawString
		opword 0x6EE38000
		opword 0x3C004330
		opword 0x906106E4
		opword 0xC85E03F0
		opword 0x900106E0
		opword 0xC00F0034
		opword 0xC82106E0
		opword 0xEC211028
		opword 0xFC010000
		opword 0x408200B4
		opword 0x2C180000
		opword 0x40820018
		opword 0x38610200
		la r4, str_8041DBB4(r2)
		opword 0x4CC63182
		bl sprintf
		opword 0x48000014
		opword 0x38610200
		opword 0x389E027C
		opword 0x4CC63182
		bl sprintf
		opword 0x80D40000
		opword 0x38610370
		opword 0x389E02E0
		opword 0x38A10200
		opword 0x4CC63182
		bl sprintf
		opword 0x80700000
		opword 0x808E0000
		opword 0xA8030000
		opword 0x7CA40051
		opword 0x40810018
		opword 0x3861025C
		la r4, str_8041DB84(r2)
		opword 0x4CC63182
		bl sprintf
		opword 0x48000014
		opword 0x3861025C
		la r4, str_8041DBC8(r2)
		opword 0x4CC63182
		bl sprintf
		bl FontDrawStart
		opword 0x6EA38000
		opword 0x3C004330
		opword 0x906106F4
		opword 0x3861025C
		opword 0xC85E03F0
		opword 0x900106F0
		opword 0xC06F0044
		opword 0xC80106F0
		lfs f1, float_206_8041dbd0(r2)
		opword 0xEC001028
		opword 0xEC43002A
		bl FontDrawString
		opword 0x3A310018
		opword 0x3AF70001
		opword 0x3AD60001
		opword 0x3A100004
		opword 0x2C160003
		opword 0x3A520004
		opword 0x3A730004
		opword 0x3A940004
		opword 0x39CE0004
		opword 0x4180FDFC
		opword 0x806100F8
		opword 0x808100F4
		opword 0x80A100F0
		opword 0x80C100EC
		bl GXSetScissor
		opword 0x88010370
		opword 0x7C000775
		opword 0x41820048
		lwz r0, dat_8041dab8(r2)
		opword 0x3881000C
		lfs f1, float_neg240_8041dae0(r2)
		opword 0x38600000
		opword 0x9001000C
		lfs f2, float_neg130_8041dae4(r2)
		lfs f3, float_480_8041dae8(r2)
		lfs f4, float_70_8041daec(r2)
		lfs f5, float_20_8041dad8(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		opword 0x38610370
		bl msgSearch
		opword 0x7C651B78
		opword 0x3860FF24
		opword 0x3880FF76
		bl FontDrawMessage
		opword 0x800F0050
		opword 0x2C000000
		opword 0x418202FC
		opword 0x2C000001
		opword 0x418202F4
		opword 0x28000012
		opword 0x3A000000
		opword 0x41810138
		lis r3, jumptable_803754F0@ha
		opword 0x5400103A
		addi r3, r3, jumptable_803754F0@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x387E02F0
		bl msgSearch
		opword 0x7C641B78
		opword 0x38610650
		bl strcpy
		opword 0x48000108
		opword 0x387E0304
		bl msgSearch
		opword 0x7C641B78
		opword 0x38610650
		bl strcpy
		opword 0x480000F0
		opword 0x387E0318
		bl msgSearch
		opword 0x7C641B78
		opword 0x38610650
		bl strcpy
		opword 0x480000D8
		opword 0x387E032C
		bl msgSearch
		opword 0x7C641B78
		opword 0x38610650
		bl strcpy
		opword 0x480000C0
		opword 0x387E0344
		bl msgSearch
		opword 0x7C641B78
		opword 0x38610650
		bl strcpy
		opword 0x480000A8
		opword 0x387E0358
		bl msgSearch
		opword 0x7C641B78
		opword 0x38610650
		bl strcpy
		opword 0x48000090
		opword 0x387E036C
		bl msgSearch
		opword 0x7C641B78
		opword 0x38610650
		bl strcpy
		opword 0x48000078
		opword 0x387E0380
		bl msgSearch
		opword 0x7C641B78
		opword 0x38610650
		bl strcpy
		opword 0x48000060
		opword 0x387E0380
		bl msgSearch
		opword 0x7C641B78
		opword 0x38610650
		bl strcpy
		opword 0x48000048
		opword 0x387E0398
		bl msgSearch
		opword 0x7C641B78
		opword 0x38610650
		bl strcpy
		opword 0x48000030
		opword 0x387E03B0
		bl msgSearch
		opword 0x7C641B78
		opword 0x38610650
		bl strcpy
		opword 0x48000018
		opword 0x387E03C4
		bl msgSearch
		opword 0x7C641B78
		opword 0x38610650
		bl strcpy
		opword 0x39C10650
		opword 0x38C00001
		opword 0x7DC37378
		opword 0x38A00000
		opword 0x48000034
		opword 0x7C800774
		opword 0x2C00000A
		opword 0x40820020
		opword 0x38610650
		opword 0x38000000
		opword 0x7C632A14
		opword 0x38C00002
		opword 0x98030000
		opword 0x3A030001
		opword 0x48000018
		opword 0x38630001
		opword 0x38A50001
		opword 0x88830000
		opword 0x7C800775
		opword 0x4082FFC8
		opword 0x3866FFFF
		opword 0x3C004330
		opword 0x1CA30018
		lwz r6, dat_8041dabc(r2)
		opword 0x900106F0
		opword 0x38810008
		opword 0xC89E03F0
		opword 0x38600000
		opword 0x3805002D
		opword 0x90C10008
		opword 0x6C008000
		lfs f1, float_neg280_8041dbd4(r2)
		opword 0x900106F4
		lfs f2, float_100_8041db48(r2)
		opword 0xC80106F0
		lfs f3, float_240_8041daf8(r2)
		opword 0xEC802028
		lfs f5, float_20_8041dad8(r2)
		bl windowDispGX_Waku_col
		bl FontDrawStart
		opword 0x280E0000
		opword 0x41820014
		opword 0x7DC37378
		bl FontGetMessageWidth
		opword 0x5471043E
		opword 0x48000008
		opword 0x3A200000
		opword 0x28100000
		opword 0x41820014
		opword 0x7E038378
		bl FontGetMessageWidth
		opword 0x5460043E
		opword 0x48000008
		opword 0x38000000
		opword 0x7C008800
		opword 0x40810008
		opword 0x7C110378
		opword 0x2C1100E4
		opword 0x41810018
		opword 0x207100E4
		opword 0x54600FFE
		opword 0x7C001A14
		opword 0x7C110E70
		opword 0x48000030
		opword 0x6E238000
		opword 0x3C004330
		opword 0x906106F4
		opword 0xC83E03F0
		opword 0x900106F0
		lfs f2, float_228_8041dbd8(r2)
		opword 0xC80106F0
		opword 0xEC000828
		opword 0xEC220024
		bl FontDrawScale
		opword 0x3A200000
		opword 0x3871FEEE
		opword 0x3C004330
		opword 0x6C648000
		opword 0x900106F0
		opword 0xC83E03F0
		opword 0x7DC37378
		opword 0x908106F4
		lfs f2, float_90_8041dbdc(r2)
		opword 0xC80106F0
		opword 0xEC200828
		bl FontDrawString
		opword 0x28100000
		opword 0x41820030
		opword 0x3871FEEE
		opword 0x3C004330
		opword 0x6C648000
		opword 0x900106F0
		opword 0xC83E03F0
		opword 0x7E038378
		opword 0x908106F4
		lfs f2, float_66_8041dbe0(r2)
		opword 0xC80106F0
		opword 0xEC200828
		bl FontDrawString
		opword 0x387E03DC
		opword 0x38800002
		bl iconFlagOff
		opword 0xC02F003C
		opword 0x387E03DC
		opword 0xC04F0040
		lfs f3, float_0_8041db00(r2)
		bl iconSetPos
		opword 0x48000010
		opword 0x387E03DC
		opword 0x38800002
		bl iconFlagOn
#endif
	}
#ifdef NONMATCHING

	if (wp->flags & 0xD000) {
		Mtx mtx;
		Mtx scale;
		s32 coin;
		s32 delta;

		windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -250.0f, -75.0f, 150.0f, 45.0f, 20.0f);
		PSMTXTrans(mtx, -220.0f, -113.0f, 0.0f);
		PSMTXScale(scale, 0.7f, 0.7f, 0.7f);
		PSMTXConcat(mtx, scale, mtx);
		if (wp->flags & 0x1000) {
			iconDispGx2(mtx, 0x10, 0x18B);
			coin = pouchGetCoin();
		} else if (wp->flags & 0x4000) {
			iconDispGx2(mtx, 0x10, 0x102);
			coin = ((s32 (*)(void))pouchGetSuperCoin)();
		} else {
			iconDispGx2(mtx, 0x10, 0x18D);
			coin = ((s32 (*)(void))pouchGetStarPiece)();
		}
		PSMTXTrans(mtx, -192.0f, -113.0f, 0.0f);
		iconDispGx2(mtx, 0x10, 0x1D6);
		PSMTXTrans(mtx, -126.0f, -113.0f, 0.0f);
		iconNumberDispGx(mtx, wp->coin, 0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
		if ((delta = coin - wp->coin)) {
			delta /= 10;
			if (!delta) {
				delta = coin > wp->coin ? 1 : -1;
			}
			if (wp->field_0x5C & 1) {
				wp->coin += delta;
				statusWinForceUpdateCoin();
			}
			wp->field_0x5C++;
			wp->field_0x5C %= 1200;
			if (!unk_804189fc) {
				psndSFXOn("SFX_COUNT_COIN1");
				unk_804189fc = 7;
			}
		}
		if (unk_804189fc > 0) {
			unk_804189fc--;
		}
	}

	if (wp->flags & 0x2000) {
		Mtx mtx;
		Mtx scale;
		s32 delta;

		windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -250.0f, -130.0f, 150.0f, 45.0f, 20.0f);
		PSMTXTrans(mtx, -210.0f, -166.0f, 0.0f);
		PSMTXScale(scale, 1.1f, 1.1f, 1.1f);
		PSMTXConcat(mtx, scale, mtx);
		iconDispGx2(mtx, 0x10, 0x1F1);
		PSMTXTrans(mtx, -126.0f, -168.0f, 0.0f);
		iconNumberDispGx(mtx, wp->coinDisp, 0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
		if (!(gp->retraceCount & 3)) {
			if ((delta = pouch->mShineSpriteCount - wp->coinDisp)) {
				delta /= 10;
				if (!delta) {
					delta = pouch->mShineSpriteCount > wp->coinDisp ? 1 : -1;
				}
				wp->coinDisp += delta;
			}
		}
	}

	if ((wp->flags & 0x100) && (lotteryGetPtr()->mFlags & 2)) {
		Mtx mtx;
		char buf[32];

		windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -250.0f, -130.0f, 150.0f, 45.0f, 20.0f);
		PSMTXTrans(mtx, -220.0f, -172.0f, 0.0f);
		iconDispGx2(mtx, 0x10, 0x140);
		sprintf(buf, "%04d", *(s16*)((u8*)lotteryGetPtr() + 0x20));
		for (i = 0; i < 4; i++) {
			PSMTXTrans(mtx, 20.0f * i + -126.0f - 60.0f, -168.0f, 0.0f);
			iconNumberDispGx(mtx, ((s8*)buf)[i] - '0', 0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
		}
	}

	switch (mode = wp->field_0x50) {
		case 0:
		case 1:
			break;
		case 4: {
			const char* desc;
			s32 h;
			u32 sl, st, sw, sh;

			row = 0;
			desc = NULL;

			h = (8 - pouchGetKeepItemCnt() > 0 ? 8 - pouchGetKeepItemCnt() : 0) * 24;
			windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -24.0f, 100.0f, 300.0f, 220 - h, 20.0f);
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 51.0f, 114.0f, 150.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(81.0f, 111.0f, msgSearch("msg_window_title_1"));
			FontDrawEdgeOff();
			GXGetScissor(&sl, &st, &sw, &sh);
			GXSetScissor(0x120, 0xA2, 0x11C, 0xBE - h);
			for (i = 0; i < 32; i++) {
				s32 id = pouchKeepItem(i);
				ItemData* item = &itemDataTable[id];
				if (id) {
					ICONGX2(&(Vec){11.0f, wp->scroll + (56 - row * 24), 0.0f}, 0x10, 0.5f, item->icon_id);
					FontDrawStart();
					FontDrawString(36.0f, wp->scroll + (80 - row * 24), item->id);
					if (row == wp->cursor) {
						desc = item->description;
					}
					row++;
				}
			}
			GXSetScissor(sl, st, sw, sh);
			if (desc) {
				windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -240.0f, -130.0f, 480.0f, 70.0f, 20.0f);
				FontDrawStart();
				FontDrawMessage(-220, -138, msgSearch(desc));
			}
			break;
		}
		case 2:
		case 3:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16: {
			s32 h;
			s32* tbl;
			const char* title;
			s32 titleX;
			s32 i;
			const char* desc;
			s32 max;
			s32 flag;
			u32 sl, st, sw, sh;

			desc = NULL;
			i = 0;
			if (mode == 2 || mode == 3) {
				h = (8 - pouchGetHaveItemCnt() > 0 ? 8 - pouchGetHaveItemCnt() : 0) * 24;
				max = 20;
				title = msgSearch("msg_window_title_1");
				titleX = 30;
			} else if (mode == 12) {
				h = (8 - pouchGetHaveBadgeCnt() > 0 ? 8 - pouchGetHaveBadgeCnt() : 0) * 24;
				max = 200;
				title = msgSearch("msg_window_title_2");
				titleX = 40;
			} else if (mode == 14) {
				h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
				max = 0x152;
				title = msgSearch("msg_window_title_3");
				titleX = 20;
			} else if (mode == 15) {
				h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
				max = wp->count;
				title = msgSearch("msg_window_title_3");
				titleX = 20;
			} else if (mode == 16) {
				h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
				max = 0x152;
				title = msgSearch("msg_window_title_4");
				titleX = 30;
			} else {
				h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
				max = 99;
				title = msgSearch("msg_window_title_2");
				titleX = 40;
			}
			windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -24.0f, 100.0f, 300.0f, 220 - h, 20.0f);
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 51.0f, 114.0f, 150.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(titleX + 51, 111.0f, title);
			FontDrawEdgeOff();
			if (wp->field_0x50 != 3) {
				Mtx mtx;
				Mtx scale;
				s32 icon;
				PSMTXTrans(mtx, 244.0f, 82.0f, 0.0f);
				PSMTXScale(scale, 0.6f, 0.6f, 0.6f);
				PSMTXConcat(mtx, scale, mtx);
				iconDispGxCol(mtx, 0x10, 0x211, (GXColor){0xF0, 0xF0, 0xF0, 0xFF});
				if (wp->field_0x50 == 13) {
					icon = 0x18D;
				} else if (wp->field_0x50 == 16) {
					icon = 0x13F;
				} else {
					icon = 0x18B;
				}
				{
					iconDispGx(&(Vec){244.0f, 86.0f, 0.0f}, 0x10, icon, 0.6f);
				}
			}
			GXGetScissor(&sl, &st, &sw, &sh);
			GXSetScissor(0x120, 0xA2, 0x11C, 0xBE - h);
			for (tbl = badge_bottakuru100_table, row = i; i < max; i++) {
				
				GXColor color = {0x00, 0x00, 0x00, 0xFF};
				s32 id;
				ItemData* item;
				flag = 0;
				switch (wp->field_0x50) {
					case 2:
					case 3:
						id = pouchHaveItem(i);
						break;
					case 12:
						id = pouchHaveBadge(i);
						break;
					case 11:
						id = (s16)badgeShop_get(bdsw->bargain_table, i + 0xF0);
						if (id - badgeShop_ThrowCheck(i + 0xF0) > 0) {
							id = i + 0xF0;
						} else {
							id = 0;
						}
						break;
					case 13:
						if ((s16)badgeShop_get(bdsw->starmaniac_table, i + 0xF0) > 0) {
							id = i + 0xF0;
						} else {
							id = 0;
						}
						break;
					case 14:
						if ((s16)badgeShop_get(bdsw->bottakuru_table, i + 1) > 0) {
							id = i + 1;
						} else {
							id = 0;
						}
						break;
					case 15:
						id = tbl[i];
						break;
					case 16:
						if ((s16)badgeShop_get(bdsw->bteresa_table, i + 1) > 0) {
							id = i + 1;
						} else {
							id = 0;
						}
						break;
				}
				item = &itemDataTable[id];
				if (id) {
					s32 ty;
					if (wp->field_0x50 == 13 && item->star_piece_price > ((s32 (*)(void))pouchGetStarPiece)()) {
						color = (GXColor){0xA0, 0xA0, 0xA0, 0xFF};
						flag = 0x20;
					}
					{
						ICONGX2(&(Vec){11.0f, wp->scroll + (56 - row * 24), 0.0f}, flag | 0x10, 0.5f, item->icon_id);
					}
					FontDrawStart();
					FontDrawScale(0.8f);
					FontDrawColor(color);
					FontDrawString(36.0f, wp->scroll + (80 - row * 24) - 2.0f, item->id);
					if (wp->field_0x50 != 3) {
						char buf[32];
						f32 sc;
						s32 xoff;
						switch (wp->field_0x50) {
							case 14:
								sprintf(buf, "%2d", item->buy_price * 12 / 10);
								sc = 1.0f;
								xoff = 0;
								break;
							case 15:
								sprintf(buf, "%3d", item->buy_price * (evtGetValue(NULL, 0xF5DE06A9) + 11) / 10);
								sc = 1.0f;
								xoff = -14;
								break;
							case 16:
								sprintf(buf, "%4d", (item->buy_price * 2 + 2) / 3);
								sc = 0.8f;
								xoff = -20;
								break;
							case 11:
								sprintf(buf, "%2d", item->buy_price);
								sc = 1.0f;
								xoff = 0;
								break;
							case 13:
								sprintf(buf, "%2d", item->star_piece_price);
								sc = 1.0f;
								xoff = 0;
								break;
							case 12:
							default:
								sprintf(buf, "%2d", item->sell_price);
								xoff = 0;
								sc = 1.0f;
								break;
						}
						FontDrawStart();
						FontDrawScale(sc);
						FontDrawColor(color);
						FontDrawString(xoff + 226, wp->scroll + (80 - row * 24), buf);
					}
					if (row == wp->cursor) {
						desc = item->description;
					}
					row++;
				}
			}
			GXSetScissor(sl, st, sw, sh);
			if (desc) {
				windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -240.0f, -130.0f, 480.0f, 70.0f, 20.0f);
				FontDrawStart();
				FontDrawMessage(-220, -138, msgSearch(desc));
			}
			break;
		}
		case 17:
		case 18: {
			InformantWork* jdt = &_jdt;
			InformantInfo* info;
			s32 h;
			u8* tbl;
			const char* title;
			u32 sl, st, sw, sh;
#endif
#ifndef NONMATCHING
}
#pragma pop
#endif


#ifdef NONMATCHING
			h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
			if (mode == 17) {
				title = msgSearch("msg_window_title_5");
				tbl = jdt->readFlags.perfectRead;
			} else {
				title = msgSearch("msg_window_title_6");
				tbl = jdt->readFlags.luigiRead;
			}
			windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -24.0f, 100.0f, 300.0f, 220 - h, 20.0f);
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 51.0f, 114.0f, 150.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(71.0f, 111.0f, title);
			FontDrawEdgeOff();
			if (wp->field_0x50 == 17) {
				Mtx mtx;
				Mtx scale;
				PSMTXTrans(mtx, 244.0f, 82.0f, 0.0f);
				PSMTXScale(scale, 0.6f, 0.6f, 0.6f);
				PSMTXConcat(mtx, scale, mtx);
				iconDispGxCol(mtx, 0x10, 0x211, (GXColor){0xF0, 0xF0, 0xF0, 0xFF});
				{
					iconDispGx(&(Vec){244.0f, 86.0f, 0.0f}, 0x10, 0x18B, 0.6f);
				}
			}
			GXGetScissor(&sl, &st, &sw, &sh);
			GXSetScissor(0x120, 0xA2, 0x11C, 0xBE - h);
			for (i = 0, info = jdt->info; i < wp->count; i++, info++) {
				char buf[32];
				GXColor color;
				char c;
				s32 ty;
				if (johoya_get(tbl, info->storyId)) {
					sprintf(buf, "");
					color = (GXColor){0xA0, 0xA0, 0xA0, 0xFF};
				} else {
					sprintf(buf, "%3d", info->unkA);
					color = (GXColor){0x00, 0x00, 0x00, 0xFF};
				}
				FontDrawStart();
				c = ((char*)info->initEndPos)[info->tagEndPos];
				((char*)info->initEndPos)[info->tagEndPos] = 0;
				FontDrawColor(color);
				FontDrawScale(0.8f);
				FontDrawString(1.0f, wp->scroll + (80 - i * 24), (char*)info->initEndPos);
				((char*)info->initEndPos)[info->tagEndPos] = c;
				if (wp->field_0x50 == 17) {
					FontDrawStart();
					FontDrawColor(color);
					FontDrawString(221.0f, wp->scroll + (80 - i * 24), buf);
				}
			}
			GXSetScissor(sl, st, sw, sh);
			break;
		}
		case 5:
		case 6:
		case 7: {
			const char* name;
			char msgName[64] = {0};
			s32 row = 0;
			s32 h;
			u32 sl, st, sw, sh;
			
			s32 lv;
			s32 flag;
			GXColor color;

			h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
			windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -24.0f, 100.0f, 300.0f, 220 - h, 20.0f);
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 16.0f, 114.0f, 120.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(41.0f, 111.0f, msgSearch("msg_window_title_7"));
			FontDrawEdgeOff();
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 167.0f, 114.0f, 85.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(177.0f, 111.0f, msgSearch("msg_window_title_8"));
			FontDrawEdgeOff();
			GXGetScissor(&sl, &st, &sw, &sh);
			GXSetScissor(0x120, 0xA2, 0x11C, 0xBE - h);
			for (i = 0; party_id_table[i]; i++) {
				s32 icon;
				s32 ty;
				char buf[32];
				char help[16];
				char dir[16];
				if (wp->field_0x50 == 5 || wp->field_0x50 == 6) {
					if (!partyChkJoin(party_id_table[i])) {
						continue;
					}
					if (evtGetValue(NULL, 0xF8406022) == 0) {
						if (pouch->partyData[party_id_table[i]].techLevel < 1) {
							color = (GXColor){0x00, 0x00, 0x00, 0xFF};
							lv = 0;
							flag = 0;
						} else {
							color = (GXColor){0xA0, 0xA0, 0xA0, 0xFF};
							lv = 1;
							flag = 0x20;
						}
					} else {
						if (pouch->partyData[party_id_table[i]].techLevel < 2) {
							color = (GXColor){0x00, 0x00, 0x00, 0xFF};
							lv = 0;
							flag = 0;
						} else {
							color = (GXColor){0xA0, 0xA0, 0xA0, 0xFF};
							lv = 2;
							flag = 0x20;
						}
					}
				} else {
					if (!partyChkJoin(party_id_table[i])) {
						continue;
					}
					if (wp->field_0x4C == party_id_table[i]) {
						continue;
					}
					if (pouch->partyData[party_id_table[i]].techLevel > 0) {
						color = (GXColor){0x00, 0x00, 0x00, 0xFF};
						lv = 0;
						flag = 0;
					} else {
						color = (GXColor){0xA0, 0xA0, 0xA0, 0xFF};
						lv = 1;
						flag = 0x20;
					}
				}
				ICONGX2(&(Vec){11.0f, wp->scroll + (56 - row * 24), 0.0f}, flag | 0x10, 0.5f, unitwin_party_icon(party_icon_table[i]));
				FontDrawStart();
				FontDrawColor(color);
				switch (i) {
					case 0:
						name = msgSearch("name_party0");
						break;
					case 1:
						name = msgSearch("name_party1");
						break;
					case 2:
						name = msgSearch("name_party4");
						break;
					case 3:
						name = pouchGetYoshiName();
						break;
					case 4:
						name = msgSearch("name_party5");
						break;
					case 5:
						name = msgSearch("name_party2");
						break;
					case 6:
						name = msgSearch("name_party6");
						break;
				}
				ty = 80 - row * 24;
				FontDrawString(36.0f, wp->scroll + ty, name);
				sprintf(buf, "%d", pouch->partyData[party_id_table[i]].techLevel);
				FontDrawStart();
				FontDrawString(236.0f, wp->scroll + ty, buf);
				if (row == wp->cursor) {
					if (lv == 0) {
						sprintf(help, "help");
					} else {
						sprintf(help, "helperr");
					}
					if (wp->field_0x50 == 5 || wp->field_0x50 == 6) {
						sprintf(dir, "lankup");
					} else {
						sprintf(dir, "lankdown");
					}
					sprintf(msgName, "%s_%s_lank%d%s", help, dir, pouch->partyData[party_id_table[i]].techLevel + 1, party_labelname_table[i]);
				}
				row++;
			}
			GXSetScissor(sl, st, sw, sh);
			if (*(s8*)msgName) {
				windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -240.0f, -130.0f, 480.0f, 70.0f, 20.0f);
				FontDrawStart();
				FontDrawMessage(-220, -138, msgSearch(msgName));
			}
			break;
		}
		case 8: {
			char msgName[64] = {0};
			s32 row = 0;
			s32 h;
			u32 sl, st, sw, sh;
			
			s32 j;
			s32 flag;
			s32 lv;
			s32 bob;
			s32 iy;
			s32 iflag;
			s32 v;
			s32 ty;
			GXColor color;
			s32 icon;

			h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
			windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -24.0f, 100.0f, 300.0f, 220 - h, 20.0f);
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 16.0f, 114.0f, 120.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(21.0f, 111.0f, msgSearch("msg_window_title_9"));
			FontDrawEdgeOff();
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 167.0f, 114.0f, 85.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(177.0f, 111.0f, msgSearch("msg_window_title_10"));
			FontDrawEdgeOff();
			GXGetScissor(&sl, &st, &sw, &sh);
			GXSetScissor(0x120, 0xA2, 0x11C, 0xBE - h);
			for (i = 0; i < wp->count; i++) {
				char buf[32];
				char help[16];
				flag = 0;
				for (j = 0; j < wp->count; j++) {
					if (j != wp->cursor && *mario_status_point_table[j] - mario_status_henka_table[j] <= 0) {
						flag = 1;
					}
				}
				if (!flag) {
					color = (GXColor){0x00, 0x00, 0x00, 0xFF};
					lv = 0;
					flag = 0;
				} else {
					color = (GXColor){0xA0, 0xA0, 0xA0, 0xFF};
					lv = 1;
					flag = 0x20;
				}
				{
					ICONGX2(&(Vec){11.0f, wp->scroll + (56 - i * 24), 0.0f}, iflag = flag | 0x10, 0.5f, mario_status_icon_table[i]);
				}
				FontDrawStart();
				FontDrawColor(color);
				sprintf(buf, "%s%3d", mario_status_name_table[i], *mario_status_point_table[i]);
				FontDrawString(36.0f, wp->scroll + (80 - i * 24), buf);
				bob = (gp->retraceCount & 0xF) > 7 ? 0 : 2;
				if (row == wp->cursor) {
					if (lv == 0) {
						sprintf(help, "help");
					} else {
						sprintf(help, "helperr");
					}
					sprintf(msgName, "%s_levelup%s", help, mario_status_labelname_table[i]);
					v = *mario_status_point_table[i] + mario_status_henka_table[i] * 2;
					if (v > 0) {
						icon = 0x1B5;
					} else {
						icon = 0x162;
						bob = 0;
					}
					{
						ICONGX2(&(Vec){166.0f, bob + (wp->scroll + (56 - i * 24)), 0.0f}, iflag, 0.5f, icon);
					}
					{
						ICONGX2(&(Vec){186.0f, bob + (wp->scroll + (56 - i * 24)), 0.0f}, iflag, 0.5f, icon);
					}
				} else {
					v = *mario_status_point_table[i] - mario_status_henka_table[i];
					if (v > 0) {
						icon = 0x1B6;
					} else {
						icon = 0x162;
						bob = 0;
					}
					{
						ICONGX2(&(Vec){176.0f, (wp->scroll + (56 - i * 24)) - bob, 0.0f}, iflag, 0.5f, icon);
					}
				}
				if (v > 0) {
					sprintf(buf, "%3d", v);
				} else {
					sprintf(buf, "  \x81\x48", v);
				}
				FontDrawStart();
				FontDrawString(206.0f, wp->scroll + (80 - i * 24), buf);
				row++;
			}
			GXSetScissor(sl, st, sw, sh);
			if (*(s8*)msgName) {
				windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -240.0f, -130.0f, 480.0f, 70.0f, 20.0f);
				FontDrawStart();
				FontDrawMessage(-220, -138, msgSearch(msgName));
			}
			break;
		}
		case 9: {
			char msgName[64] = {0};
			s32 row = 0;
			s32 h;
			u32 sl, st, sw, sh;
			
			s32 j;
			s32 cnt;
			s32 lv;
			s32 v;
			s32 ty;
			GXColor color;

			h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
			windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -24.0f, 100.0f, 300.0f, 220 - h, 20.0f);
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 16.0f, 114.0f, 120.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(21.0f, 111.0f, msgSearch("msg_window_title_9"));
			FontDrawEdgeOff();
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 167.0f, 114.0f, 85.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(177.0f, 111.0f, msgSearch("msg_window_title_10"));
			FontDrawEdgeOff();
			GXGetScissor(&sl, &st, &sw, &sh);
			GXSetScissor(0x120, 0xA2, 0x11C, 0xBE - h);
			for (i = 0; i < wp->count; i++) {
				char buf[32];
				char help[16];
				cnt = 0;
				for (j = 0; j < wp->count; j++) {
					if (j != wp->cursor && *mario_status_point_table[j] - mario_status_henka_table[j] <= 0) {
						cnt++;
					}
				}
				if (cnt < 2) {
					color = (GXColor){0x00, 0x00, 0x00, 0xFF};
					lv = 0;
					j = 0;
				} else {
					color = (GXColor){0xA0, 0xA0, 0xA0, 0xFF};
					lv = 1;
					j = 0x20;
				}
				{
					ICONGX2(&(Vec){11.0f, wp->scroll + (56 - i * 24), 0.0f}, j | 0x10, 0.5f, mario_status_icon_table[i]);
				}
				FontDrawStart();
				FontDrawColor(color);
				sprintf(buf, "%s%3d", mario_status_name_table[i], *mario_status_point_table[i]);
				FontDrawString(36.0f, wp->scroll + (80 - i * 24), buf);
				if (row == wp->cursor) {
					if (lv == 0) {
						sprintf(help, "help");
					} else {
						sprintf(help, "helperr");
					}
					sprintf(msgName, "%s_levelup%s", help, mario_status_labelname_table[i]);
					v = *mario_status_point_table[i] + mario_status_henka_table[i];
					if (v > 0) {
						sprintf(buf, "%3d", v);
					} else {
						sprintf(buf, "  \x81\x48", v);
					}
					FontDrawStart();
					FontDrawString(206.0f, wp->scroll + (80 - i * 24), buf);
				}
				row++;
			}
			GXSetScissor(sl, st, sw, sh);
			if (*(s8*)msgName) {
				windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -240.0f, -130.0f, 480.0f, 70.0f, 20.0f);
				FontDrawStart();
				FontDrawMessage(-220, -138, msgSearch(msgName));
			}
			break;
		}
		case 10: {
			char msgName[64] = {0};
			s32 row = 0;
			s32 h;
			u32 sl, st, sw, sh;
			
			s32 v;
			s32 ty;
			s32 flag;
			GXColor color;
			s32 lv;

			h = 8 - wp->count;
			h = (h > 0 ? h : 0) * 24;
			windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -24.0f, 100.0f, 300.0f, 220 - h, 20.0f);
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 16.0f, 114.0f, 120.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(21.0f, 111.0f, msgSearch("msg_window_title_9"));
			FontDrawEdgeOff();
			windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA4, 0xFF, 0xFF}, 167.0f, 114.0f, 85.0f, 28.0f, 8.0f);
			FontDrawStart();
			FontDrawEdge();
			FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
			FontDrawString(177.0f, 111.0f, msgSearch("msg_window_title_10"));
			FontDrawEdgeOff();
			GXGetScissor(&sl, &st, &sw, &sh);
			GXSetScissor(0x120, 0xA2, 0x11C, 0xBE - h);
			for (i = 0; i < 3; i++) {
				char buf[32];
				char help[16];
				if (i == wp->field_0x4C) {
					continue;
				}
				if (*mario_status_point_table[i] - mario_status_henka_table[i] > 0) {
					color = (GXColor){0x00, 0x00, 0x00, 0xFF};
					lv = 0;
					flag = 0;
				} else {
					color = (GXColor){0xA0, 0xA0, 0xA0, 0xFF};
					lv = 1;
					flag = 0x20;
				}
				{
					ICONGX2(&(Vec){11.0f, wp->scroll + (56 - row * 24), 0.0f}, flag | 0x10, 0.5f, mario_status_icon_table[i]);
				}
				FontDrawStart();
				FontDrawColor(color);
				sprintf(buf, "%s%3d", mario_status_name_table[i], *mario_status_point_table[i]);
				FontDrawString(36.0f, wp->scroll + (80 - row * 24), buf);
				if (row == wp->cursor) {
					if (lv == 0) {
						sprintf(help, "help");
					} else {
						sprintf(help, "helperr");
					}
					sprintf(msgName, "%s_leveldown%s", help, mario_status_labelname_table[i]);
					v = *mario_status_point_table[i] - mario_status_henka_table[i];
					if (v > 0) {
						sprintf(buf, "%3d", v);
					} else {
						sprintf(buf, "  \x81\x48", v);
					}
					FontDrawStart();
					FontDrawString(206.0f, wp->scroll + (80 - row * 24), buf);
				}
				row++;
			}
			GXSetScissor(sl, st, sw, sh);
			if (*(s8*)msgName) {
				windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -240.0f, -130.0f, 480.0f, 70.0f, 20.0f);
				FontDrawStart();
				FontDrawMessage(-220, -138, msgSearch(msgName));
			}
			break;
		}
	}

	if (wp->field_0x50 != 0 && wp->field_0x50 != 1) {
		char text[136];
		char* line1;
		char* line2 = NULL;
		s8* p;
		s32 k;
		s32 lines;
		s32 w2;

		switch (wp->field_0x50) {
			case 0:
			case 1:
				break;
			case 11:
			case 14:
			case 15:
				strcpy(text, msgSearch("msg_window_select_6"));
				break;
			case 17:
				strcpy(text, msgSearch("msg_window_select_8"));
				break;
			case 18:
				strcpy(text, msgSearch("msg_window_select_7"));
				break;
			case 13:
			case 16:
				strcpy(text, msgSearch("msg_window_select_10"));
				break;
			case 2:
			case 12:
				strcpy(text, msgSearch("msg_window_select_2"));
				break;
			case 3:
				strcpy(text, msgSearch("msg_window_select_3"));
				break;
			case 4:
				strcpy(text, msgSearch("msg_window_select_4"));
				break;
			case 5:
				strcpy(text, msgSearch("msg_window_select_11"));
				break;
			case 6:
				strcpy(text, msgSearch("msg_window_select_11"));
				break;
			case 7:
				strcpy(text, msgSearch("msg_window_select_12"));
				break;
			case 8:
			case 9:
				strcpy(text, msgSearch("msg_window_select_9"));
				break;
			case 10:
				strcpy(text, msgSearch("msg_window_select_9_1"));
				break;
		}
		line1 = text;
		lines = 1;
		for (p = (s8*)line1, k = 0; *p; p++, k++) {
			if (*p == '\n') {
				text[k] = 0;
				lines = 2;
				line2 = &text[k] + 1;
				break;
			}
		}
		windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -280.0f, 100.0f, 240.0f, (lines - 1) * 24 + 45, 20.0f);
		FontDrawStart();
		k = line1 ? FontGetMessageWidth(line1) : 0;
		if (line2) {
			w2 = FontGetMessageWidth(line2);
		} else {
			w2 = 0;
		}
		if (w2 > k) {
			k = w2;
		}
		if (k <= 228) {
			k = (228 - k) / 2;
		} else {
			FontDrawScale(228.0f / k);
			k = 0;
		}
		FontDrawString(k - 274, 90.0f, line1);
		if (line2) {
			FontDrawString(k - 274, 66.0f, line2);
		}
		iconFlagOff("yubicursor_2", 2);
		iconSetPos("yubicursor_2", wp->cursorX, wp->cursorY, 0.0f);
	} else {
		iconFlagOn("yubicursor_2", 2);
	}
}


USER_FUNC(set_new_goods_list) {
#endif
#ifndef NONMATCHING
s32 set_new_goods_list(EventEntry* event, BOOL isFirstCall) {
#endif
	s32* args = event->args;
	UnitWinWork* wp = (UnitWinWork*)evtGetValue(event, args[0]);
	s32 item = evtGetValue(event, args[1]);
	char name[32];
	wp->goods[wp->goodsIdx] = item;
	if (wp->goodsIdx < wp->goodsMax) {
#ifdef NONMATCHING
		sprintf(name, "uwn%d", wp->goodsIdx);
#endif
#ifndef NONMATCHING
		sprintf(name, EXT_LIT((char*)str_8041DAC0, "uwn%d"), wp->goodsIdx);
#endif
		if (item != 0) {
			((void (*)(char*, u16))iconChange)(name, itemDataTable[item].icon_id);
		} else {
			iconDelete(name);
		}
	}
	return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(unitwin_get_work_ptr) {
#endif
#ifndef NONMATCHING
s32 unitwin_get_work_ptr(EventEntry* event, BOOL isFirstCall) {
#endif
	evtSetValue(event, event->args[0], (s32)_wp);
	return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(unitwin_getpartylank) {
#endif
#ifndef NONMATCHING
s32 unitwin_getpartylank(EventEntry* event, BOOL isFirstCall) {
#endif
	s32* args = event->args;
	PouchData* pouch = pouchGetPtr();
	s32 idx = evtGetValue(event, args[0]);
	evtSetValue(event, args[1], pouch->partyData[idx].techLevel);
	return EVT_RETURN_DONE;
}

#define PP ((PouchPartyData*)((u8*)pouch + idx))
#ifdef NONMATCHING
USER_FUNC(unitwin_setpartylank) {
#endif
#ifndef NONMATCHING
s32 unitwin_setpartylank(EventEntry* event, BOOL isFirstCall) {
#endif
	PouchPartyData* new_var2;
	unsigned int idx;
	s16 v;
	s32 new_var;
	s32* args = event->args;
	PouchData* pouch = pouchGetPtr();
	idx = evtGetValue(event, args[0]) * 14;
	v = evtGetValue(event, args[1]);
	new_var = idx;
	new_var2 = (PouchPartyData*)((u8*)pouch + new_var);
	new_var2->HPLevel = ((PouchPartyData*)((u8*)pouch + new_var))->attackLevel = ((PouchPartyData*)((u8*)pouch + new_var))->techLevel = v;
	pouchRevisePartyParam();
	PP->currentHP = PP->maximumHP;
	return EVT_RETURN_DONE;
}
#undef PP

#ifdef NONMATCHING
USER_FUNC(unitwin_setmariolevel) {
#endif
#ifndef NONMATCHING
s32 unitwin_setmariolevel(EventEntry* event, BOOL isFirstCall) {
#endif
	s32* args = event->args;
	PouchData* pouch = pouchGetPtr();
	s32 i;
	BOOL r;
	pouch->baseMaxHP = evtGetValue(event, args[0]);
	pouch->baseMaxFP = evtGetValue(event, args[1]);
	pouch->maximumBP = evtGetValue(event, args[2]);
	pouchReviseMarioParam();
	pouch->currentHP = pouch->maximumHP;
	pouch->currentFP = pouch->maximumFP;
	if (pouch->availableBP < 0) {
		for (i = 0; i < 200; i++) {
			if (pouchEquipCheckBadgeIndex(i)) {
				pouchUnEquipBadgeIndex(i);
			}
		}
		pouchReviseMarioParam();
		r = TRUE;
	} else {
		r = FALSE;
	}
	evtSetValue(event, args[3], r);
	return EVT_RETURN_DONE;
}

#pragma force_active on
#pragma explicit_zero_data on
#ifndef NONMATCHING
#pragma explicit_zero_data reset

// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802f64b8[3] = {11.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f64c4[3] = {244.0f, 86.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f64d0[3] = {11.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f64dc[3] = {244.0f, 86.0f, 0.0f};
__declspec(section ".rodata") const u32 zero_802f64e8[16] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const f32 vec3_802f6528[3] = {11.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const u32 zero_802f6534[16] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const f32 vec3_802f6574[3] = {11.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f6580[3] = {166.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f658c[3] = {186.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802f6598[3] = {176.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const u32 zero_802f65a4[16] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const f32 vec3_802f65e4[3] = {11.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const u32 zero_802f65f0[16] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const f32 vec3_802f6630[3] = {11.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const char str_802F663C[16] = "SFX_COUNT_COIN1";
__declspec(section ".rodata") const char str_802F664C[20] = "msg_window_title_1\0";
__declspec(section ".rodata") const char str_802F6660[20] = "msg_window_title_2\0";
__declspec(section ".rodata") const char str_802F6674[20] = "msg_window_title_3\0";
__declspec(section ".rodata") const char str_802F6688[20] = "msg_window_title_4\0";
__declspec(section ".rodata") const char str_802F669C[20] = "msg_window_title_5\0";
__declspec(section ".rodata") const char str_802F66B0[20] = "msg_window_title_6\0";
__declspec(section ".rodata") const char str_802F66C4[20] = "msg_window_title_7\0";
__declspec(section ".rodata") const char str_802F66D8[20] = "msg_window_title_8\0";
__declspec(section ".rodata") const char str_802F66EC[12] = "name_party0";
__declspec(section ".rodata") const char str_802F66F8[12] = "name_party1";
__declspec(section ".rodata") const char str_802F6704[12] = "name_party4";
__declspec(section ".rodata") const char str_802F6710[12] = "name_party5";
__declspec(section ".rodata") const char str_802F671C[12] = "name_party2";
__declspec(section ".rodata") const char str_802F6728[12] = "name_party6";
__declspec(section ".rodata") const char str_802F6734[8] = "helperr";
__declspec(section ".rodata") const char str_802F673C[8] = "lankup\0";
__declspec(section ".rodata") const char str_802F6744[12] = "lankdown\0\0\0";
__declspec(section ".rodata") const char str_802F6750[16] = "%s_%s_lank%d%s\0";
__declspec(section ".rodata") const char str_802F6760[20] = "msg_window_title_9\0";
__declspec(section ".rodata") const char str_802F6774[20] = "msg_window_title_10";
__declspec(section ".rodata") const char str_802F6788[16] = "%s_levelup%s\0\0\0";
__declspec(section ".rodata") const char str_802F6798[16] = "%s_leveldown%s\0";
__declspec(section ".rodata") const char str_802F67A8[20] = "msg_window_select_6";
__declspec(section ".rodata") const char str_802F67BC[20] = "msg_window_select_8";
__declspec(section ".rodata") const char str_802F67D0[20] = "msg_window_select_7";
__declspec(section ".rodata") const char str_802F67E4[24] = "msg_window_select_10\0\0\0";
__declspec(section ".rodata") const char str_802F67FC[20] = "msg_window_select_2";
__declspec(section ".rodata") const char str_802F6810[20] = "msg_window_select_3";
__declspec(section ".rodata") const char str_802F6824[20] = "msg_window_select_4";
__declspec(section ".rodata") const char str_802F6838[24] = "msg_window_select_11\0\0\0";
__declspec(section ".rodata") const char str_802F6850[24] = "msg_window_select_12\0\0\0";
__declspec(section ".rodata") const char str_802F6868[20] = "msg_window_select_9";
__declspec(section ".rodata") const char str_802F687C[24] = "msg_window_select_9_1\0\0";
__declspec(section ".rodata") const char str_802F6894[16] = "yubicursor_2\0\0\0";
__declspec(section ".rodata") const f64 double_to_int_802f68a8 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802F68B0[8] = "%s_%04d";
__declspec(section ".rodata") const f64 double_to_int_mask_802f68b8 = 4503599627370496.0;
__declspec(section ".sdata2") const char str_8041D958[8] = "_kur\0\0\0";
__declspec(section ".sdata2") const char str_8041D960[8] = "_nok\0\0\0";
__declspec(section ".sdata2") const char str_8041D968[8] = "_win\0\0\0";
__declspec(section ".sdata2") const char str_8041D970[8] = "_yos\0\0\0";
__declspec(section ".sdata2") const char str_8041D978[8] = "_viv\0\0\0";
__declspec(section ".sdata2") const char str_8041D980[8] = "_bom\0\0\0";
__declspec(section ".sdata2") const char str_8041D988[8] = "_chu\0\0\0";
__declspec(section ".sdata2") const char str_8041D990[4] = "_hp";
__declspec(section ".sdata2") const char str_8041D994[4] = "_fp";
__declspec(section ".sdata2") const char str_8041D998[4] = "_bp";
__declspec(section ".sdata2") const char str_8041D99C[8] = "\x82g\x82o\0\0\0";
__declspec(section ".sdata2") const char str_8041D9A4[8] = "\x82" "e\x82o\0\0\0";
__declspec(section ".sdata2") const char str_8041D9AC[8] = "\x82" "a\x82o\0\0\0";
__declspec(section ".sdata2") const u32 dat_8041d9b4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9b8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9bc = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9c0 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041d9c4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9c8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9cc = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9d0 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9d4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9d8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9dc = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9e0 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9e4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9e8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9ec = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041d9f0 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9f4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9f8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d9fc = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041da00 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da04 = 0xF0F0F0FF;
__declspec(section ".sdata2") const u32 dat_8041da08 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041da0c = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041da10 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da14 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da18 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041da1c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da20 = 0xF0F0F0FF;
__declspec(section ".sdata2") const u32 dat_8041da24 = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041da28 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041da2c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da30 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041da34 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da38 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041da3c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da40 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041da44 = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041da48 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041da4c = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041da50 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041da54 = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041da58 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da5c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da60 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041da64 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da68 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041da6c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da70 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041da74 = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041da78 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da7c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da80 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041da84 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da88 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041da8c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da90 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041da94 = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041da98 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041da9c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041daa0 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041daa4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041daa8 = 0x2BA4FFFF;
__declspec(section ".sdata2") const u32 dat_8041daac = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041dab0 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041dab4 = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041dab8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041dabc = 0xFFFFFFFF;
__declspec(section ".sdata2") const char str_8041DAC0[8] = "uwn%d\0\0";
__declspec(section ".sdata2") const f32 float_neg150_8041dac8 = -150.0f;
__declspec(section ".sdata2") const f32 float_120_8041dacc = 120.0f;
__declspec(section ".sdata2") const f32 float_300_8041dad0 = 300.0f;
__declspec(section ".sdata2") const f32 float_50_8041dad4 = 50.0f;
__declspec(section ".sdata2") const f32 float_20_8041dad8 = 20.0f;
__declspec(section ".sdata2") const f32 float_108_8041dadc = 108.0f;
__declspec(section ".sdata2") const f32 float_neg240_8041dae0 = -240.0f;
__declspec(section ".sdata2") const f32 float_neg130_8041dae4 = -130.0f;
__declspec(section ".sdata2") const f32 float_480_8041dae8 = 480.0f;
__declspec(section ".sdata2") const f32 float_70_8041daec = 70.0f;
__declspec(section ".sdata2") const f32 float_8_8041daf0 = 8.0f;
__declspec(section ".sdata2") const f32 float_neg304_8041daf4 = -304.0f;
__declspec(section ".sdata2") const f32 float_240_8041daf8 = 240.0f;
__declspec(section ".sdata2") const f32 float_60_8041dafc = 60.0f;
__declspec(section ".sdata2") const f32 float_0_8041db00 = 0.0f;
__declspec(section ".sdata2") const f32 float_neg250_8041db04 = -250.0f;
__declspec(section ".sdata2") const f32 float_neg75_8041db08 = -75.0f;
__declspec(section ".sdata2") const f32 float_150_8041db0c = 150.0f;
__declspec(section ".sdata2") const f32 float_45_8041db10 = 45.0f;
__declspec(section ".sdata2") const f32 float_neg220_8041db14 = -220.0f;
__declspec(section ".sdata2") const f32 float_neg113_8041db18 = -113.0f;
__declspec(section ".sdata2") const f32 float_0p7_8041db1c = 0.7f;
__declspec(section ".sdata2") const f32 float_neg192_8041db20 = -192.0f;
__declspec(section ".sdata2") const f32 float_neg126_8041db24 = -126.0f;
__declspec(section ".sdata2") const f32 float_neg210_8041db28 = -210.0f;
__declspec(section ".sdata2") const f32 float_neg166_8041db2c = -166.0f;
__declspec(section ".sdata2") const f32 float_1p1_8041db30 = 1.1f;
__declspec(section ".sdata2") const f32 float_neg168_8041db34 = -168.0f;
__declspec(section ".sdata2") const f32 float_neg172_8041db38 = -172.0f;
__declspec(section ".sdata2") const char str_8041DB3C[8] = "%04d\0\0\0";
__declspec(section ".sdata2") const f32 float_neg24_8041db44 = -24.0f;
__declspec(section ".sdata2") const f32 float_100_8041db48 = 100.0f;
__declspec(section ".sdata2") const f32 float_51_8041db4c = 51.0f;
__declspec(section ".sdata2") const f32 float_114_8041db50 = 114.0f;
__declspec(section ".sdata2") const f32 float_28_8041db54 = 28.0f;
__declspec(section ".sdata2") const f32 float_81_8041db58 = 81.0f;
__declspec(section ".sdata2") const f32 float_111_8041db5c = 111.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041db60 = 0.5f;
__declspec(section ".sdata2") const f32 float_36_8041db64 = 36.0f;
__declspec(section ".sdata2") const f32 float_244_8041db68 = 244.0f;
__declspec(section ".sdata2") const f32 float_82_8041db6c = 82.0f;
__declspec(section ".sdata2") const f32 float_0p6_8041db70 = 0.6f;
__declspec(section ".sdata2") const f32 float_0p8_8041db74 = 0.8f;
__declspec(section ".sdata2") const f32 float_2_8041db78 = 2.0f;
__declspec(section ".sdata2") const char str_8041DB7C[4] = "%2d";
__declspec(section ".sdata2") const f32 float_1_8041db80 = 1.0f;
__declspec(section ".sdata2") const char str_8041DB84[4] = "%3d";
__declspec(section ".sdata2") const char str_8041DB88[4] = "%4d";
__declspec(section ".sdata2") const f32 float_71_8041db8c = 71.0f;
__declspec(section ".sdata2") const f32 float_0_8041db90 = 0.0f;
__declspec(section ".sdata2") const f32 float_221_8041db94 = 221.0f;
__declspec(section ".sdata2") const f32 float_16_8041db98 = 16.0f;
__declspec(section ".sdata2") const f32 float_41_8041db9c = 41.0f;
__declspec(section ".sdata2") const f32 float_167_8041dba0 = 167.0f;
__declspec(section ".sdata2") const f32 float_85_8041dba4 = 85.0f;
__declspec(section ".sdata2") const f32 float_177_8041dba8 = 177.0f;
__declspec(section ".sdata2") const char str_8041DBAC[4] = "%d\0";
__declspec(section ".sdata2") const f32 float_236_8041dbb0 = 236.0f;
__declspec(section ".sdata2") const char str_8041DBB4[8] = "help\0\0\0";
__declspec(section ".sdata2") const f32 float_21_8041dbbc = 21.0f;
__declspec(section ".sdata2") const char str_8041DBC0[8] = "%s%3d\0\0";
__declspec(section ".sdata2") const char str_8041DBC8[8] = "  \x81H\0\0\0";
__declspec(section ".sdata2") const f32 float_206_8041dbd0 = 206.0f;
__declspec(section ".sdata2") const f32 float_neg280_8041dbd4 = -280.0f;
__declspec(section ".sdata2") const f32 float_228_8041dbd8 = 228.0f;
__declspec(section ".sdata2") const f32 float_90_8041dbdc = 90.0f;
__declspec(section ".sdata2") const f32 float_66_8041dbe0 = 66.0f;
__declspec(section ".sdata2") const f32 float_1000_8041dbe4 = 1000.0f;
__declspec(section ".sdata2") const f32 float_6_8041dbe8 = 6.0f;
__declspec(section ".sdata2") const f32 float_10_8041dbec = 10.0f;
__declspec(section ".sdata2") const f32 float_30_8041dbf0 = 30.0f;
__declspec(section ".sdata2") const f32 float_124_8041dbf4 = 124.0f;
__declspec(section ".sdata2") const f32 float_38_8041dbf8 = 38.0f;
__declspec(section ".sdata2") const f32 float_12_8041dbfc = 12.0f;

// jumptables last, as the target emitted them with their functions
__declspec(section ".data") void* jumptable_803754F0[] = {
    (char*)evt_unitwin_disp_func + 0x29CC,
    (char*)evt_unitwin_disp_func + 0x29CC,
    (char*)evt_unitwin_disp_func + 0x2910,
    (char*)evt_unitwin_disp_func + 0x2928,
    (char*)evt_unitwin_disp_func + 0x2940,
    (char*)evt_unitwin_disp_func + 0x2958,
    (char*)evt_unitwin_disp_func + 0x2970,
    (char*)evt_unitwin_disp_func + 0x2988,
    (char*)evt_unitwin_disp_func + 0x29A0,
    (char*)evt_unitwin_disp_func + 0x29A0,
    (char*)evt_unitwin_disp_func + 0x29B8,
    (char*)evt_unitwin_disp_func + 0x28B0,
    (char*)evt_unitwin_disp_func + 0x2910,
    (char*)evt_unitwin_disp_func + 0x28F8,
    (char*)evt_unitwin_disp_func + 0x28B0,
    (char*)evt_unitwin_disp_func + 0x28B0,
    (char*)evt_unitwin_disp_func + 0x28F8,
    (char*)evt_unitwin_disp_func + 0x28C8,
    (char*)evt_unitwin_disp_func + 0x28E0,
};
__declspec(section ".data") void* jumptable_8037553C[] = {
    (char*)evt_unitwin_disp_func + 0x172C,
    (char*)evt_unitwin_disp_func + 0x173C,
    (char*)evt_unitwin_disp_func + 0x174C,
    (char*)evt_unitwin_disp_func + 0x175C,
    (char*)evt_unitwin_disp_func + 0x1768,
    (char*)evt_unitwin_disp_func + 0x1778,
    (char*)evt_unitwin_disp_func + 0x1788,
};
__declspec(section ".data") void* jumptable_80375558[] = {
    (char*)evt_unitwin_disp_func + 0x16B0,
    (char*)evt_unitwin_disp_func + 0x16B8,
    (char*)evt_unitwin_disp_func + 0x16C0,
    (char*)evt_unitwin_disp_func + 0x16C8,
    (char*)evt_unitwin_disp_func + 0x16D0,
    (char*)evt_unitwin_disp_func + 0x16D8,
    (char*)evt_unitwin_disp_func + 0x16E0,
};
__declspec(section ".data") void* jumptable_80375574[] = {
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xC34,
    (char*)evt_unitwin_disp_func + 0xC34,
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xD14,
    (char*)evt_unitwin_disp_func + 0xC54,
    (char*)evt_unitwin_disp_func + 0xC44,
    (char*)evt_unitwin_disp_func + 0xC8C,
    (char*)evt_unitwin_disp_func + 0xCB8,
    (char*)evt_unitwin_disp_func + 0xCE4,
    (char*)evt_unitwin_disp_func + 0xCEC,
};
__declspec(section ".data") void* jumptable_803755B8[] = {
    (char*)evt_unitwin_disp_func + 0x2878,
    (char*)evt_unitwin_disp_func + 0x2878,
    (char*)evt_unitwin_disp_func + 0x8DC,
    (char*)evt_unitwin_disp_func + 0x8DC,
    (char*)evt_unitwin_disp_func + 0x690,
    (char*)evt_unitwin_disp_func + 0x1354,
    (char*)evt_unitwin_disp_func + 0x1354,
    (char*)evt_unitwin_disp_func + 0x1354,
    (char*)evt_unitwin_disp_func + 0x1968,
    (char*)evt_unitwin_disp_func + 0x1FA0,
    (char*)evt_unitwin_disp_func + 0x2434,
    (char*)evt_unitwin_disp_func + 0x8DC,
    (char*)evt_unitwin_disp_func + 0x8DC,
    (char*)evt_unitwin_disp_func + 0x8DC,
    (char*)evt_unitwin_disp_func + 0x8DC,
    (char*)evt_unitwin_disp_func + 0x8DC,
    (char*)evt_unitwin_disp_func + 0x8DC,
    (char*)evt_unitwin_disp_func + 0x106C,
    (char*)evt_unitwin_disp_func + 0x106C,
};
#pragma force_active on
#pragma explicit_zero_data on
#endif
__declspec(section ".data") u32 gap_05_80375604_data[1] = {0};
#pragma explicit_zero_data reset
#ifndef NONMATCHING
#pragma force_active reset
#endif
