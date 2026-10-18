#pragma optimize_for_size on
#include "battle/battle_stage.h"
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "memory.h"
#include "system.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>
// G5 keepall: asm stopgap reaches data via section-relative relocs; keep it from being stripped
#pragma force_active on

extern int rand(void);

typedef struct StageLight {
	u32 flags;              // 0x0
	char name[0x20];        // 0x4
	GXColor color;          // 0x24
	GXColor colorStart;     // 0x28
	GXColor colorTarget;    // 0x2C
	s32 colorTime;          // 0x30
	s32 colorMax;           // 0x34
	u8 colorMode;           // 0x38
	f32 width;              // 0x3C
	f32 widthStart;         // 0x40
	f32 widthTarget;        // 0x44
	s32 widthTime;          // 0x48
	s32 widthMax;           // 0x4C
	u8 widthMode;           // 0x50
	Vec pos;                // 0x54
	Vec posStart;           // 0x60
	Vec posTarget;          // 0x6C
	s32 posTime;            // 0x78
	s32 posMax;             // 0x7C
	u8 posMode;             // 0x80
	Vec target;             // 0x84
	Vec targetStart;        // 0x90
	Vec targetTarget;       // 0x9C
	s32 targetTime;         // 0xA8
	s32 targetMax;          // 0xAC
	u8 targetMode;          // 0xB0
	Vec up;                 // 0xB4
	Vec upStart;            // 0xC0
	Vec upTarget;           // 0xCC
	s32 upTime;             // 0xD8
	s32 upMax;              // 0xDC
	u8 upMode;              // 0xE0
	void* data;             // 0xE4
} StageLight;

typedef struct StageDark {
	s32 flags;      // 0x0
	u8 cur;         // 0x4
	u8 base;        // 0x5
	u8 start;       // 0x6
	u8 baseStart;   // 0x7
	u8 target;      // 0x8
	u8 baseTarget;  // 0x9
	u8 pad_a[2];    // 0xA
	s32 time;       // 0xC
	s32 baseTime;   // 0x10
	s32 max;        // 0x14
	s32 baseMax;    // 0x18
	u8 mode;        // 0x1C
	u8 baseMode;    // 0x1D
} StageDark;

typedef struct StageWork {
	s32 field_0;            // 0x0
	StageLight lights[12];  // 0x4
	StageDark stgDark;      // 0xAE4
	StageDark audDark;      // 0xB04
	f32 stageSizeX;          // 0xB24
	f32 stageSizeY;          // 0xB28
	f32 stageSizeZ;          // 0xB2C
	f32 audienceSizeX;          // 0xB30
	f32 audienceSizeY;          // 0xB34
	f32 audienceSizeZ;          // 0xB38
} StageWork;

#define STG ((StageWork*)BattleStageGetPtr())

typedef struct ScreenWork {
	void* tex;      // 0x0
	s32 captured;   // 0x4
	f32 field_8;    // 0x8
	f32 field_C;    // 0xC
	f32 field_10;   // 0x10
	f32 field_14;   // 0x14
	f32 field_18;   // 0x18
	f32 field_1C;   // 0x1C
	s32 field_20;   // 0x20
	s32 field_24;   // 0x24
	f32 field_28;   // 0x28
} ScreenWork;

//.sbss
static BattleSpotWork work;
static ScreenWork* screen_wp;


//.sdata
static BattleSpotWork* wp = &work;


__declspec(section ".sdata") u32 gap_07_804117E4_sdata[7] = {0};
static u8 inta_tex[32] = {0xFF,0xFF,0xFF,0xFF,0,0,0,0,0xFF,0xFF,0xFF,0xFF,0,0,0,0,0xFF,0xFF,0xFF,0xFF,0,0,0,0,0xFF,0xFF,0xFF,0xFF,0,0,0,0};

USER_FUNC(screen_evt_func);

__declspec(section ".sdata") EVT_BEGIN(screen_evt)
	BEGIN_INLINE_EVENT
		CALL(screen_evt_func, LW(0))
	END_INLINE_EVENT
	RETURN
EVT_END()


__declspec(section ".sdata") u32 gap_07_8041183C_sdata[1] = {0};

// forward declarations
void batSpotDisp(CameraId camId, void* param);
BattleSpotEntry* batSpotEntry(void);
void BattleStageDispDark(CameraId camId, void* param);
void BattleStageDispLight(CameraId camId, void* param);
void DarkByPoint(u8 alpha, f32 x, f32 y, f32 z);
void DarkBySquare(f32 x0, f32 y0, f32 x1, f32 y1, f32 z, u8 alpha);
void BattleStageSetDark(StageDark* d, u8 v, s32 time, u8 mode);
void BattleStageSetDarkBase(StageDark* d, u8 v, s32 time, u8 mode);
void BattleStageLightSetTarget(s32 idx, f32 x, f32 y, f32 z, s32 time, u8 mode);
void batSpotInit(void);
f32 getSpline(f32* a, f32* b, f32* c, f32* d, s32* t, s32 n, s32 x);
void batSpotMain();
void drawCone(CameraId camId, BattleSpotEntry* e);
double sin(double);
double cos(double);

#ifdef NONMATCHING
BattleStage* BattleStageGetPtr(void) {
    return &_battleWorkPointer->stage;
}
#endif

#ifdef NONMATCHING
void BattleStageInit(void) {
	StageWork* s = STG;
	s32 i;

	memset(s, 0, sizeof(StageWork));
	s->field_0 = 0;
	for (i = 0; i < 12; i++) {
		StageLight* l = &s->lights[i];
		l->flags = 0;
		l->data = NULL;
	}
	s->stgDark.flags = 1;
	s->stgDark.cur = s->stgDark.base = 0;
	s->stgDark.start = 0;
	s->stgDark.target = 0;
	s->stgDark.time = 0;
	s->stgDark.max = 0;
	s->audDark.flags = 1;
	s->audDark.cur = s->audDark.base = 0x8C;
	s->audDark.start = 0;
	s->audDark.target = 0;
	s->audDark.time = 0;
	s->audDark.max = 0;
	s->stageSizeX = 290.0f;
	s->stageSizeY = 200.0f;
	s->stageSizeZ = 90.0f;
	s->audienceSizeX = s->stageSizeX;
	s->audienceSizeY = -50.0f;
	s->audienceSizeZ = 200.0f;
	BattleStageObjectInit();
	batSpotInit();
}
#endif

typedef struct LightSpline {
	s32 n;          // 0x0
	s32 t[8];       // 0x4
	f32 x[4][8];    // 0x24
	f32 y[4][8];    // 0xA4
	f32 z[4][8];    // 0x124
} LightSpline;

#ifdef NONMATCHING
void BattleStageMain(void) {
	StageLight* l;
	s32 i;
	LightSpline* sp;
	StageWork* s = STG;

	batSpotMain();
	for (i = 0; i < 12; i++) {
		l = &s->lights[i];
		if (l->flags & 1) {
			if (l->colorTime > 0) {
				l->colorTime--;
				l->color.r = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->colorMode, l->colorStart.r, l->colorTarget.r, l->colorMax - l->colorTime, l->colorMax);
				l->color.g = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->colorMode, l->colorStart.g, l->colorTarget.g, l->colorMax - l->colorTime, l->colorMax);
				l->color.b = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->colorMode, l->colorStart.b, l->colorTarget.b, l->colorMax - l->colorTime, l->colorMax);
				if ((l->flags & 2) && l->color.r == 0 && l->color.g == 0 && l->color.b == 0) {
					l->flags = 0;
					continue;
				}
			}
			if (l->widthTime > 0) {
				l->widthTime--;
				l->width = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->widthMode, l->widthStart, l->widthTarget, l->widthMax - l->widthTime, l->widthMax);
			}
			if (l->posTime > 0) {
				l->posTime--;
				l->pos.x = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->posMode, l->posStart.x, l->posTarget.x, l->posMax - l->posTime, l->posMax);
				l->pos.y = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->posMode, l->posStart.y, l->posTarget.y, l->posMax - l->posTime, l->posMax);
				l->pos.z = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->posMode, l->posStart.z, l->posTarget.z, l->posMax - l->posTime, l->posMax);
			}
			if (l->flags & 4) {
				sp = l->data;
				l->target.x = getSpline(sp->x[0], sp->x[1], sp->x[2], sp->x[3], sp->t, sp->n, l->targetTime);
				l->target.y = getSpline(sp->y[0], sp->y[1], sp->y[2], sp->y[3], sp->t, sp->n, l->targetTime);
				l->target.z = getSpline(sp->z[0], sp->z[1], sp->z[2], sp->z[3], sp->t, sp->n, l->targetTime);
				l->targetTime++;
				if (l->targetTime >= sp->t[sp->n - 1]) {
					if (l->flags & 8) {
						l->targetTime -= sp->t[sp->n - 1];
					} else {
						l->targetTime = sp->t[sp->n - 1];
					}
				}
			} else {
				if (l->targetTime > 0) {
					l->targetTime--;
					l->target.x = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->targetMode, l->targetStart.x, l->targetTarget.x, l->targetMax - l->targetTime, l->targetMax);
					l->target.y = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->targetMode, l->targetStart.y, l->targetTarget.y, l->targetMax - l->targetTime, l->targetMax);
					l->target.z = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->targetMode, l->targetStart.z, l->targetTarget.z, l->targetMax - l->targetTime, l->targetMax);
				}
				if (l->data != NULL) {
					__memFree(HEAP_BATTLE, l->data);
					l->data = NULL;
				}
			}
			if (l->upTime > 0) {
				l->upTime--;
				l->up.x = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->upMode, l->upStart.x, l->upTarget.x, l->upMax - l->upTime, l->upMax);
				l->up.y = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->upMode, l->upStart.y, l->upTarget.y, l->upMax - l->upTime, l->upMax);
				l->up.z = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&l->upMode, l->upStart.z, l->upTarget.z, l->upMax - l->upTime, l->upMax);
			}
		} else {
			if (l->data != NULL) {
				__memFree(HEAP_BATTLE, l->data);
				l->data = NULL;
			}
		}
	}
	if (s->stgDark.time > 0) {
		s->stgDark.time--;
		s->stgDark.cur = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&s->stgDark.mode, s->stgDark.start, s->stgDark.target, s->stgDark.max - s->stgDark.time, s->stgDark.max);
	}
	if (s->stgDark.baseTime > 0) {
		s->stgDark.baseTime--;
		s->stgDark.base = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&s->stgDark.baseMode, s->stgDark.baseStart, s->stgDark.baseTarget, s->stgDark.baseMax - s->stgDark.baseTime, s->stgDark.baseMax);
	}
	if (s->audDark.time > 0) {
		s->audDark.time--;
		s->audDark.cur = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&s->audDark.mode, s->audDark.start, s->audDark.target, s->audDark.max - s->audDark.time, s->audDark.max);
	}
	if (s->audDark.baseTime > 0) {
		s->audDark.baseTime--;
		s->audDark.base = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(*(s8*)&s->audDark.baseMode, s->audDark.baseStart, s->audDark.baseTarget, s->audDark.baseMax - s->audDark.baseTime, s->audDark.baseMax);
	}
}
#endif

#ifdef NONMATCHING
void BattleStageEnd(void) {
	s32 i;
	StageWork* s = STG;

	for (i = 0; i < 12; i++) {
		StageLight* l = &s->lights[i];
		if (l->data != NULL) {
			__memFree(HEAP_BATTLE, l->data);
			l->data = NULL;
		}
	}
}
#endif

#ifdef NONMATCHING
void BattleStageDisp(void) {
	BattleGetUnitPtr(_battleWorkPointer, _battleWorkPointer->activeUnitId);
	dispEntry(CAMERA_3D, 5000.0f, 2, BattleStageDispDark, NULL);
	dispEntry(CAMERA_3D, 6000.0f, 2, BattleStageDispLight, NULL);
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
void DarkByPoint(u8 alpha, f32 x, f32 y, f32 z) {
	GXPosition3f32(x, y, z);
	GXColor4u8(0, 0, 0, alpha);
}
#endif
#pragma dont_inline reset

#pragma dont_inline on
#ifdef NONMATCHING
void DarkBySquare(f32 x0, f32 y0, f32 x1, f32 y1, f32 z, u8 alpha) {
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	DarkByPoint(alpha, x0, y0, z);
	DarkByPoint(alpha, x1, y0, z);
	DarkByPoint(alpha, x1, y1, z);
	DarkByPoint(alpha, x0, y1, z);
}
#endif
#pragma dont_inline reset

#ifdef NONMATCHING
void BattleStageDispDark(CameraId camId, void* param) {
	StageWork* s = STG;
	CameraEntry* cam = camGetPtr(CAMERA_3D);
	StageDark* aud;

	GXSetCullMode(GX_CULL_BACK);
	GXSetZCompLoc(GX_TRUE);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
	GXSetNumTexGens(0);
	GXLoadPosMtxImm(cam->view, GX_PNMTX0);
	GXSetNumTevStages(1);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	aud = &s->audDark;
	GXSetZMode(GX_TRUE, GX_GEQUAL, GX_FALSE);
	DarkBySquare(-640.0f, 640.0f, 640.0f, -640.0f, 105.0f, aud->cur);
	GXSetZMode(GX_TRUE, GX_LESS, GX_FALSE);
	DarkBySquare(640.0f, 640.0f, -640.0f, -640.0f, 105.0f, aud->cur);
	GXSetZMode(GX_TRUE, GX_LESS, GX_FALSE);
	DarkBySquare(-640.0f, 640.0f, 640.0f, -640.0f, 105.0f, s->stgDark.cur);
}
#endif

#ifdef NONMATCHING
void BattleStageDispLight(CameraId camId, void* param) {
	s32 i, j;
	f32 width;
	StageWork* s = STG;
	CameraEntry* cam = camGetPtr(CAMERA_3D);

	GXSetCullMode(GX_CULL_BACK);
	GXSetZCompLoc(GX_TRUE);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCCLR, GX_BL_ONE, GX_LO_NOOP);
	GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GXSetNumChans(1);
	GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
	GXSetNumTexGens(0);
	GXSetNumTevStages(1);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GXLoadPosMtxImm(cam->view, GX_PNMTX0);
	for (i = 0; i < 12; i++) {
		if (s->lights[i].flags & 1) {
			Mtx m;
			Vec v;
			Vec axis;

			axis = (Vec){s->lights[i].target.x - s->lights[i].pos.x, s->lights[i].target.y - s->lights[i].pos.y, s->lights[i].target.z - s->lights[i].pos.z};
			width = s->lights[i].width;
			v = s->lights[i].up;
			for (j = 0; j < 18; j++) {
				f32 px = s->lights[i].pos.x;
				f32 py = s->lights[i].pos.y;
				f32 pz = s->lights[i].pos.z;
				f32 ex = (s->lights[i].target.x - px) * 2.0f + px;
				f32 ey = (s->lights[i].target.y - py) * 2.0f + py;
				f32 ez = (s->lights[i].target.z - pz) * 2.0f + pz;
				f32 ax = v.x * width + ex;
				f32 ay = v.y * width + ey;
				f32 az = v.z * width + ez;
				f32 bx, by, bz;
				u8 r, g, b;

				PSMTXRotAxisRad(m, &axis, 0.34906584f);
				PSMTXMultVec(m, &v, &v);
				PSVECNormalize(&v, &v);
				bx = v.x * width + ex;
				by = v.y * width + ey;
				bz = v.z * width + ez;
				r = s->lights[i].color.r;
				g = s->lights[i].color.g;
				b = s->lights[i].color.b;
				GXBegin(GX_TRIANGLES, GX_VTXFMT0, 3);
				GXPosition3f32(px, py, pz);
				GXColor4u8(r, g, b, 0);
				GXPosition3f32(ax, ay, az);
				GXColor4u8(r, g, b, 0);
				GXPosition3f32(bx, by, bz);
				GXColor4u8(r, g, b, 0);
			}
		}
	}
}
#endif

#ifdef NONMATCHING
void BattleStageOnLightInCommand(void) {
}
#endif

#ifdef NONMATCHING
void BattleStageOffLightInCommand(void) {
}
#endif

#ifdef NONMATCHING
void BattleStageOnLightFriendInCommand(void) {
}
#endif

#ifdef NONMATCHING
void BattleStageOffLightFriendInCommand(void) {
}
#endif

#ifdef NONMATCHING
void BattleStageOnLightEnemyInCommand(void) {
}
#endif

#ifdef NONMATCHING
void BattleStageOffLightEnemyInCommand(void) {
}
#endif

#ifdef NONMATCHING
s32 BattleStageGetLightNumberByName(const char* name) {
	StageWork* s = STG;
	s32 i;

	for (i = 0; i < 12; i++) {
		StageLight* l = &s->lights[i];
		if ((l->flags & 1) && !strcmp(l->name, name)) {
			return i;
		}
	}
	return -1;
}
#endif

#ifdef NONMATCHING
s32 BattleStageSysLightEntry(const char* name) {
	StageWork* s = STG;
	s32 i;

	for (i = 0; i <= 6; i++) {
		StageLight* l = &s->lights[i];
		if ((l->flags & 1) && !strcmp(l->name, name)) {
		}
	}
	for (i = 0; i < 7; i++) {
		StageLight* l = &s->lights[i];
		if (!(l->flags & 1)) {
			l->flags = 1;
			strcpy(l->name, name);
			break;
		}
	}
	return i;
}
#endif

#pragma opt_propagation off
#ifdef NONMATCHING
void BattleStageLightRelease(s32 idx, s32 time, u8 mode) {
	StageLight* l = &STG->lights[idx];

	if (l->flags & 1) {
		if (time == 0) {
			l->flags = 0;
		} else {
			l->flags |= 2;
			l->colorStart = (GXColor){l->color.r, l->color.g, l->color.b};
			{ GXColor z = {0, 0, 0}; l->colorTarget = z; }
			l->colorTime = time;
			l->colorMax = time;
			l->colorMode = mode;
		}
	}
}
#endif
#pragma opt_propagation reset

#pragma opt_propagation off
#ifdef NONMATCHING
void BattleStageLightSetLightColor(s32 idx, u8 r, u8 g, u8 b, s32 time, u8 mode) {
	StageLight* l = &STG->lights[idx];

	l->colorStart = (GXColor){l->color.r, l->color.g, l->color.b};
	l->colorTarget = (GXColor){r, g, b};
	l->colorTime = time;
	l->colorMax = time;
	l->colorMode = mode;
	if (time == 0) {
		l->color = (GXColor){l->color.r, l->color.g, l->color.b, 0xFF};
	}
}
#endif
#pragma opt_propagation reset

#pragma opt_propagation off
#ifdef NONMATCHING
void BattleStageLightSetWidth(s32 idx, s32 width, s32 time, u8 mode) {
	StageLight* l = &STG->lights[idx];

	l->widthStart = l->width;
	l->widthTarget = width;
	l->widthTime = time;
	l->widthMax = time;
	l->widthMode = mode;
	if (time == 0) {
		l->width = width;
	}
}
#endif
#pragma opt_propagation reset

#pragma opt_propagation off
#ifdef NONMATCHING
void BattleStageLightSetPosition(s32 idx, f32 x, f32 y, f32 z, s32 time, u8 mode) {
	StageLight* l = &STG->lights[idx];

	l->posStart.x = l->pos.x;
	l->posStart.y = l->pos.y;
	l->posStart.z = l->pos.z;
	l->posTarget.x = x;
	l->posTarget.y = y;
	l->posTarget.z = z;
	l->posTime = time;
	l->posMax = time;
	l->posMode = mode;
	if (time == 0) {
		l->pos = (Vec){x, y, z};
	}
}
#endif
#pragma opt_propagation reset

#pragma dont_inline on
#pragma opt_propagation off
#ifdef NONMATCHING
void BattleStageLightSetTarget(s32 idx, f32 x, f32 y, f32 z, s32 time, u8 mode) {
	StageLight* l = &STG->lights[idx];

	l->targetStart.x = l->target.x;
	l->targetStart.y = l->target.y;
	l->targetStart.z = l->target.z;
	l->targetTarget.x = x;
	l->targetTarget.y = y;
	l->targetTarget.z = z;
	l->targetTime = time;
	l->targetMax = time;
	l->targetMode = mode;
	l->flags &= ~4;
	if (time == 0) {
		l->target = (Vec){x, y, z};
	}
}
#endif
#pragma opt_propagation reset
#pragma dont_inline reset

#ifdef NONMATCHING
void BattleStageLightSetTargetByUnit(s32 idx, s32 unitId, f32 x, f32 y, f32 z, s32 time, u8 mode) {
	f32 px, py, pz;
	BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, unitId);

	BtlUnit_GetPos(unit, &px, &py, &pz);
	px += x;
	py += y;
	pz += z;
	BattleStageLightSetTarget(idx, px, py, pz, time, mode);
}
#endif

#pragma opt_propagation off
#ifdef NONMATCHING
void BattleStageLightSetUpVec(s32 idx, f32 x, f32 y, f32 z, s32 time, u8 mode) {
	StageLight* l = &STG->lights[idx];

	l->upStart.x = l->up.x;
	l->upStart.y = l->up.y;
	l->upStart.z = l->up.z;
	l->upTarget.x = x;
	l->upTarget.y = y;
	l->upTarget.z = z;
	l->upTime = time;
	l->upMax = time;
	l->upMode = mode;
	if (time == 0) {
		l->up = (Vec){x, y, z};
	}
}
#endif
#pragma opt_propagation reset

#pragma dont_inline on
#ifdef NONMATCHING
void BattleStageSetDark(StageDark* d, u8 v, s32 time, u8 mode) {
	d->start = d->cur;
	d->target = v;
	d->time = time;
	d->max = time;
	d->mode = mode;
	if (time == 0) {
		d->cur = v;
	}
}
#endif
#pragma dont_inline reset

#pragma dont_inline on
#ifdef NONMATCHING
void BattleStageSetDarkBase(StageDark* d, u8 v, s32 time, u8 mode) {
	d->baseStart = d->base;
	d->baseTarget = v;
	d->baseTime = time;
	d->baseMax = time;
	d->baseMode = mode;
	if (time == 0) {
		d->base = v;
	}
}
#endif
#pragma dont_inline reset

#ifdef NONMATCHING
void BattleStageSetStgDark(u8 v, s32 time, u8 mode) {
	BattleStageSetDark(&STG->stgDark, v, time, mode);
}
#endif

#ifdef NONMATCHING
void BattleStageSetStgDarkBase(u8 v, s32 time, u8 mode) {
	BattleStageSetDarkBase(&STG->stgDark, v, time, mode);
}
#endif

#ifdef NONMATCHING
void BattleStageReturnStgDarkBase(s32 time, u8 mode) {
	StageDark* d = &STG->stgDark;
	BattleStageSetDark(d, d->base, time, mode);
}
#endif

#ifdef NONMATCHING
void BattleStageSetAudDark(u8 v, s32 time, u8 mode) {
	BattleStageSetDark(&STG->audDark, v, time, mode);
}
#endif

#ifdef NONMATCHING
void BattleStageSetAudDarkBase(u8 v, s32 time, u8 mode) {
	BattleStageSetDarkBase(&STG->audDark, v, time, mode);
}
#endif

#ifdef NONMATCHING
void BattleStageReturnAudDarkBase(s32 time, u8 mode) {
	StageDark* d = &STG->audDark;
	BattleStageSetDark(d, d->base, time, mode);
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
f32 getSpline(f32* a, f32* b, f32* c, f32* d, s32* t, s32 n, s32 x) {
	s32 i;
	f32 f;

	for (i = n - 1; i >= 0; i--) {
		if ((f32)(x - t[i]) >= 0.0f) {
			break;
		}
	}
	f = x - t[i];
	return f * (f * (f * d[i] + c[i]) + b[i]) + a[i];
}
#endif
#pragma dont_inline reset
#ifdef NONMATCHING
BattleSpotWork* BatSpotGetPtr(void) {
    return wp;
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
void batSpotInit(void) {
	int i;
	BattleSpotEntry* entry;

	wp->count = 5;
	wp->entries = __memAlloc(HEAP_BATTLE, sizeof(BattleSpotEntry) * wp->count);
	memset(wp->entries, 0, sizeof(BattleSpotEntry) * wp->count);

	for (i = 0; i < 5; i++) {
		entry = batSpotEntry();
		entry->field_4 = (Vec){50.0f * i + -100.0f, 0.0f, -50.0f};
		entry->field_10 = (Vec){0.0f, 0.0f, 0.0f};
		entry->field_1C = (Vec){20.0f, 20.0f, 150.0f};
		*(GXColor*)&entry->field_28 = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
	}
}
#endif
#pragma dont_inline reset

#pragma dont_inline on
#ifdef NONMATCHING
void batSpotMain() {
    s32 count = wp->count;

    while (count-- > 0) {}
    if (wp->skipRender > 0) {
        dispEntry(CAMERA_3D_IMAGE, -1000.0f, 0, batSpotDisp, NULL);
    }
}
#endif
#pragma dont_inline reset

#ifdef NONMATCHING
void batSpotDisp(CameraId camId, void* param) {
	int i;
	BattleSpotEntry* e;

	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GXSetNumTexGens(0);
	GXSetNumTevStages(1);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
	GXSetZCompLoc(GX_TRUE);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetNumChans(1);
	for (i = 0, e = wp->entries; i < wp->count; i++, e++) {
		if ((e->flags & 1) && (e->flags & 2)) {
			GXSetCullMode(GX_CULL_BACK);
			GXSetAlphaUpdate(GX_TRUE);
			GXSetColorUpdate(GX_FALSE);
			GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
			GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
			GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
			drawCone(camId, e);
			GXSetCullMode(GX_CULL_FRONT);
			GXSetAlphaUpdate(GX_TRUE);
			GXSetColorUpdate(GX_FALSE);
			GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
			GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
			GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
			GXSetChanMatColor(GX_COLOR0A0, (GXColor){0, 0, 0, 0});
			drawCone(camId, e);
			GXSetCullMode(GX_CULL_BACK);
			GXSetAlphaUpdate(GX_FALSE);
			GXSetColorUpdate(GX_TRUE);
			GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
			GXSetBlendMode(GX_BM_BLEND, GX_BL_DSTALPHA, GX_BL_INVDSTALPHA, GX_LO_CLEAR);
			GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
			GXSetChanMatColor(GX_COLOR0A0, *(GXColor*)&e->field_28);
			drawCone(camId, e);
		}
	}
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
void drawCone(CameraId camId, BattleSpotEntry* e) {
	Mtx trans, scale, m, rx, ry, rz;
	CameraEntry* cam;
	s32 i;
	f32 a, s, c;

	cam = camGetPtr(camId);
	PSMTXTrans(trans, e->field_4.x, e->field_4.y, e->field_4.z);
	PSMTXScale(scale, e->field_1C.x, e->field_1C.y, e->field_1C.z);
	PSMTXRotRad(rx, 'x', 0.017453292f * e->field_10.x);
	PSMTXRotRad(ry, 'y', 0.017453292f * e->field_10.y);
	PSMTXRotRad(rz, 'z', 0.017453292f * e->field_10.z);
	PSMTXConcat(rz, ry, ry);
	PSMTXConcat(ry, rx, m);
	PSMTXConcat(cam->view, trans, trans);
	PSMTXConcat(trans, m, m);
	PSMTXConcat(m, scale, m);
	GXLoadPosMtxImm(m, GX_PNMTX0);
	GXSetCurrentMtx(GX_PNMTX0);
	GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 32);
	GXPosition3f32(0.0f, 0.0f, 0.0f);
	GXColor4u8(0, 0, 0, ((GXColor*)&e->field_28)->a);
	for (i = 0; i < 31; i++) {
		if (i == 30) {
			a = 0.0f;
		} else {
			a = 6.2831855f * (f32)-i / 30.0f;
		}
		s = (f32)sin(a);
		c = (f32)cos(a);
		GXPosition3f32(c, s, -1.0f);
		GXColor4u8(0, 0, 0, ((GXColor*)&e->field_28)->a / 3);
	}
}
#endif
#pragma dont_inline reset

// TODO: get this to not inline into batSpotInit
#pragma dont_inline on
#ifdef NONMATCHING
BattleSpotEntry* batSpotEntry(void) {
	int i;
	BattleSpotEntry* entry = wp->entries;

	for (i = 0; i < wp->count; i++, entry++) {
		if (!(entry->flags & 1)) {
			break;
		}
	}

	entry->field_4 = (Vec){0.0, 0.0, 0.0};
	entry->field_1C = (Vec){1.0, 1.0, 1.0};
	entry->field_10 = (Vec){0.0, 0.0, 0.0};
	*(GXColor*)&entry->field_28 = (GXColor){0, 0, 0, 0};
	entry->flags |= 1;

	return entry;
}
#endif
#pragma dont_inline reset

#pragma dont_inline on
#ifdef NONMATCHING
static f32 randf(f32 min, f32 max) {
	f32 r = (f32)rand() / 32767.0f;
	f32 d = max - min;
	return r * d + min;
}
#endif
#pragma dont_inline reset

#ifdef NONMATCHING
static void screen_capture(CameraId camId, void* param) {
	GXSetTexCopySrc(0, 0, 608, 480);
	GXSetTexCopyDst(304, 240, GX_TF_RGB565, GX_TRUE);
	GXCopyTex(screen_wp->tex, GX_FALSE);
	GXPixModeSync();
	screen_wp->captured = 1;
}
#endif

#ifdef NONMATCHING
USER_FUNC(screen_evt_func) {
	dispEntry(CAMERA_2D, 1000.0f, 0, screen_capture, NULL);
	return 0;
}
#endif

#ifdef NONMATCHING
USER_FUNC(tou_gamen_screen_tev_init) {
	u32 size = GXGetTexBufferSize(608, 480, GX_TF_I4, GX_FALSE, 0);

	screen_wp = _mapAlloc(sizeof(ScreenWork));
	screen_wp->tex = _mapAlloc(size);
	screen_wp->captured = 0;
	screen_wp->field_8 = screen_wp->field_C = 1.0f;
	screen_wp->field_10 = screen_wp->field_14 = 0.0f;
	screen_wp->field_18 = screen_wp->field_1C = 0.0f;
	screen_wp->field_20 = 0;
	screen_wp->field_28 = -1.0f;
	if (evtGetValue(event, GSW(0)) == 163) {
		screen_wp->field_24 = 1;
	}
	evtEntry(screen_evt, 0, 0);
	return 2;
}
#endif

typedef struct TevCbWork {
	u8 pad_0[0xC];
	s32 field_C;
	s32 field_10;
	s32 field_14;
} TevCbWork;

#ifdef NONMATCHING
void tou_gamen_screen_tev(TevCbWork* p) {
	GXTexObj obj;
	Mtx m;
	Mtx m1;
	Mtx m2;
	u8* tex;
	s32 i, j, n, w, s, k, idx;
	s32 rc[2];
	u8 c;
	f32 lim;
	f32 x, y;
	f32* camf;

	if (screen_wp->captured == 0) {
		return;
	}
	if (screen_wp->field_24 != 0) {
		tex = screen_wp->tex;
		for (i = 0; i < 64; i++) {
			rc[1] = i / 4;
			rc[0] = i % 4;
			for (j = 0; j < 64; j++) {
				idx = (j / 8) * 32 + (rc[1] << 8); idx += j % 8; idx += rc[0] << 3; tex[idx] = (i & 1) ? 0xFF : 0;
			}
			n = rand() % 100 + 100;
			rc[1] = rc[1] * 256;
			k = rc[0] * 8;
			for (rc[0] = 0; rc[0] < n; rc[0]++) {
				w = rand() % 4 + 2;
				s = rand() % (65 - w);
				c = rand() % 256;
				for (j = s; j < s + w; j++) {
					idx = j / 8 * 32; idx = idx + rc[1]; idx += j % 8; idx += k; tex[idx] = c;
				}
			}
		}
		DCFlushRange(tex, 0x1000);
		GXInitTexObj(&obj, tex, 64, 64, GX_TF_I8, GX_REPEAT, GX_REPEAT, GX_FALSE);
		GXInitTexObjLOD(&obj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
		GXLoadTexObj(&obj, GX_TEXMAP0);
	} else {
		GXInitTexObj(&obj, screen_wp->tex, 304, 240, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
		GXInitTexObjLOD(&obj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
	}
	GXLoadTexObj(&obj, GX_TEXMAP0);
	GXInitTexObj(&obj, inta_tex, 4, 8, GX_TF_I4, GX_REPEAT, GX_REPEAT, GX_FALSE);
	GXInitTexObjLOD(&obj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
	GXLoadTexObj(&obj, GX_TEXMAP1);
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
	if (screen_wp->field_24 == 0) {
		screen_wp->field_20++;
		if (screen_wp->field_20 % 200 == 0) {
			switch (rand() % 3) {
				case 0:
					screen_wp->field_14 = randf(0.0f, (1.0f - screen_wp->field_8) / screen_wp->field_8);
					screen_wp->field_1C = randf(0.0f, (1.0f - screen_wp->field_8) / screen_wp->field_8);
					break;
				case 1:
					screen_wp->field_C = randf(1.0f, 0.25f);
					break;
				case 2:
					break;
			}
		}
		screen_wp->field_8 += (screen_wp->field_C - screen_wp->field_8) / 60.0f;
		screen_wp->field_10 += (screen_wp->field_14 - screen_wp->field_10) / 60.0f;
		screen_wp->field_18 += (screen_wp->field_1C - screen_wp->field_18) / 60.0f;
		PSMTXScale(m1, screen_wp->field_8, screen_wp->field_8, 1.0f);
		lim = (1.0f - screen_wp->field_8) / screen_wp->field_8;
		y = screen_wp->field_18 > lim ? lim : screen_wp->field_18;
		if (screen_wp->field_10 > lim) {
			x = lim;
		} else {
			x = screen_wp->field_10;
		}
		PSMTXTrans(m2, x, y, 0.0f);
		PSMTXConcat(m1, m2, m);
	} else {
		PSMTXScale(m, 4.75f, 3.75f, 0.0f);
	}
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
	GXLoadTexMtxImm(m, GX_TEXMTX0, GX_MTX2x4);
	camf = (f32*)camGetPtr(CAMERA_3D);
	PSMTXScale(m, 1.0f, 16.0f + 6.0f * ((100.0f - camf[5]) / 1000.0f), 1.0f);
	GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
	GXLoadTexMtxImm(m, GX_TEXMTX1, GX_MTX2x4);
	p->field_C = 2;
	p->field_14 = 2;
	p->field_10 = 2;
}
#endif

#ifndef NONMATCHING
// FAKE (asm stopgap): BattleStageGetPtr (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802f31a8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f31b4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f31c0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f31cc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f31d8[3] = { 0.0f, 0.0f, -50.0f };
__declspec(section ".rodata") const f32 vec3_802f31e4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f31f0[3] = { 20.0f, 20.0f, 150.0f };
__declspec(section ".rodata") const f32 vec3_802f31fc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f3208[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f3214[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f64 double_to_int_802f3220 = 4503601774854144;
__declspec(section ".rodata") const f64 double_to_int_mask_802f3228 = 4503599627370496;
#pragma force_active reset
__declspec(section ".sdata2") const u32 dat_8041c7e8 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041c7ec = 0xFFFFFFFF;
__declspec(section ".sdata2") const f32 float_0_8041c7f0 = 0.0f;
__declspec(section ".sdata2") const f32 float_1_8041c7f4 = 1.0f;
__declspec(section ".sdata2") const f32 float_0p25_8041c7f8 = 0.25f;
__declspec(section ".sdata2") const f32 float_60_8041c7fc = 60.0f;
__declspec(section ".sdata2") const f32 float_4p75_8041c800 = 4.75f;
__declspec(section ".sdata2") const f32 float_3p75_8041c804 = 3.75f;
__declspec(section ".sdata2") const f32 float_16_8041c808 = 16.0f;
__declspec(section ".sdata2") const f32 float_6_8041c80c = 6.0f;
__declspec(section ".sdata2") const f32 float_100_8041c810 = 100.0f;
__declspec(section ".sdata2") const f32 float_1000_8041c814 = 1000.0f;
__declspec(section ".sdata2") const f32 float_neg1_8041c818 = -1.0f;
__declspec(section ".sdata2") const f32 float_32767_8041c81c = 32767.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_8041c820 = 0.017453292f;
__declspec(section ".sdata2") const f32 float_6p2832_8041c824 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_30_8041c828 = 30.0f;
__declspec(section ".sdata2") const f32 float_neg1000_8041c82c = -1000.0f;
__declspec(section ".sdata2") const f32 float_neg100_8041c830 = -100.0f;
__declspec(section ".sdata2") const f32 float_50_8041c834 = 50.0f;
__declspec(section ".sdata2") const f32 float_2_8041c838 = 2.0f;
__declspec(section ".sdata2") const f32 float_0p34907_8041c83c = 0.34906584f;
__declspec(section ".sdata2") const f32 float_neg640_8041c840 = -640.0f;
__declspec(section ".sdata2") const f32 float_640_8041c844 = 640.0f;
__declspec(section ".sdata2") const f32 float_105_8041c848 = 105.0f;
__declspec(section ".sdata2") const f32 float_5000_8041c84c = 5000.0f;
__declspec(section ".sdata2") const f32 float_6000_8041c850 = 6000.0f;
__declspec(section ".sdata2") const f32 float_290_8041c854 = 290.0f;
__declspec(section ".sdata2") const f32 float_200_8041c858 = 200.0f;
__declspec(section ".sdata2") const f32 float_90_8041c85c = 90.0f;
__declspec(section ".sdata2") const f32 float_neg50_8041c860 = -50.0f;

__declspec(section ".sdata2") const u32 unk_8042302c;
__declspec(section ".sdata2") const u32 unk_80423028;
__declspec(section ".sdata2") const u32 unk_80423024;
__declspec(section ".sdata2") const u32 unk_80423020;
__declspec(section ".sdata2") const u32 unk_8042301c;
__declspec(section ".sdata2") const u32 unk_80423018;
BattleUnit* BattleGetUnitPtr(BattleWork* wp, s32 index);
void BattleStageObjectInit(void);
void BtlUnit_GetPos(BattleUnit* unit, f32* x, f32* y, f32* z);
void DCFlushRange(void* addr, u32 nBytes);
void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
void GXClearVtxDesc(void);
void GXCopyTex(void* dest, GXBool clear);
u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, u8 mipmap, u8 max_lod);
void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXTexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
    f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp,
    GXBool do_edge_lod, GXAnisotropy max_aniso);
void GXLoadPosMtxImm(const f32 mtx[3][4], u32 id);
void GXLoadTexMtxImm(const f32 mtx[][4], u32 id, GXTexMtxType type);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
void GXPixModeSync(void);
void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1);
void GXSetAlphaUpdate(GXBool update_enable);
void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op);
void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src, u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn);
void GXSetChanMatColor(GXChannelID chan, GXColor mat_color);
void GXSetColorUpdate(GXBool update_enable);
void GXSetCullMode(GXCullMode mode);
void GXSetCurrentMtx(u32 id);
void GXSetNumChans(u8 nChans);
void GXSetNumTevStages(u8 nStages);
void GXSetNumTexGens(u8 nTexGens);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx);
void GXSetTexCopyDst(u16 wd, u16 ht, GXTexFmt fmt, GXBool mipmap);
void GXSetTexCopySrc(u16 left, u16 top, u16 wd, u16 ht);
void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac);
void GXSetVtxDesc(GXAttr attr, GXAttrType type);
void GXSetZCompLoc(GXBool before_tex);
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXRotAxisRad(Mtx m, const Vec* axis, f32 rad);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void PSVECNormalize(const Vec* src, Vec* dst);
void* __memAlloc(HEAP_TYPE heap, u32 size);
void __memFree(HEAP_TYPE heap, void* ptr);
void* _mapAlloc(u32 size);
void _restfpr_27();
void _savefpr_27();
CameraEntry* camGetPtr(CameraId cameraId);
void dispEntry(CameraId camera, f32 order, s32 renderMode, DispCallback callback, void* param);
EventEntry* evtEntry(void* evtCode, u8 priority, u8 flags);
s32 evtGetValue(EventEntry* entry, s32 index);
f32 intplGetValue(s32 mode, s32 currStep, s32 steps, f32 start, f32 end);
void *memset(void *dest, int ch, size_t count);
static f32 randf(f32 min, f32 max);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
static void screen_capture(CameraId camId, void* param);
asm void tou_gamen_screen_tev(TevCbWork* p) {
	nofralloc
	stwu r1, -0xe0(r1)
	mflr r0
	stw r0, 0xe4(r1)
	stmw r23, 0xbc(r1)
	mr r27, r3
	lwz r4, screen_wp(r13)
	lwz r0, 0x4(r4)
	cmpwi r0, 0x0
	beq L_g5_1
	lwz r0, 0x24(r4)
	cmpwi r0, 0x0
	beq L_g5_2
	lwz r29, 0x0(r4)
	li r28, 0x0
	L_g5_3:
	slwi r0, r28, 30
	srwi r4, r28, 31
	subf r0, r4, r0
	srawi r5, r28, 2
	rotlwi r3, r0, 2
	li r0, 0x40
	addze r31, r5
	clrlwi r9, r28, 31
	add r30, r3, r4
	li r10, 0x0
	slwi r4, r31, 8
	li r5, 0xff
	slwi r3, r30, 3
	mtctr r0
	L_g5_4:
	srawi r6, r10, 3
	slwi r0, r10, 29
	srwi r8, r10, 31
	addi r10, r10, 0x1
	addze r11, r6
	subf r0, r8, r0
	subfic r6, r9, 0x0
	rotlwi r7, r0, 3
	slwi r0, r11, 5
	subfe r6, r6, r6
	add r7, r7, r8
	add r0, r0, r4
	and r6, r5, r6
	add r0, r0, r7
	add r0, r0, r3
	stbx r6, r29, r0
	bdnz L_g5_4
	bl rand
	li r4, 0x64
	slwi r25, r31, 8
	divw r0, r3, r4
	slwi r26, r30, 3
	li r30, 0x0
	mullw r0, r0, r4
	subf r3, r0, r3
	addi r31, r3, 0x64
	b L_g5_5
	L_g5_6:
	bl rand
	slwi r0, r3, 30
	srwi r3, r3, 31
	subf r0, r3, r0
	rotlwi r0, r0, 2
	add r3, r0, r3
	addi r24, r3, 0x2
	bl rand
	subfic r4, r24, 0x41
	divw r0, r3, r4
	mullw r0, r0, r4
	subf r23, r0, r3
	bl rand
	slwi r0, r3, 24
	srwi r3, r3, 31
	subf r0, r3, r0
	add r4, r23, r24
	rotlwi r0, r0, 8
	mr r5, r23
	add r3, r0, r3
	subf r0, r23, r4
	clrlwi r6, r3, 24
	mtctr r0
	cmpw r23, r4
	bge L_g5_7
	L_g5_8:
	srawi r4, r5, 3
	slwi r0, r5, 29
	srwi r3, r5, 31
	addi r5, r5, 0x1
	addze r4, r4
	subf r0, r3, r0
	slwi r4, r4, 5
	rotlwi r0, r0, 3
	add r4, r4, r25
	add r0, r0, r3
	add r0, r4, r0
	add r0, r0, r26
	stbx r6, r29, r0
	bdnz L_g5_8
	L_g5_7:
	addi r30, r30, 0x1
	L_g5_5:
	cmpw r30, r31
	blt L_g5_6
	addi r28, r28, 0x1
	cmpwi r28, 0x40
	blt L_g5_3
	mr r3, r29
	li r4, 0x1000
	bl DCFlushRange
	mr r4, r29
	addi r3, r1, 0x8
	li r5, 0x40
	li r6, 0x40
	li r7, 0x1
	li r8, 0x1
	li r9, 0x1
	li r10, 0x0
	bl GXInitTexObj
	lfs f1, float_0_8041c7f0(r2)
	addi r3, r1, 0x8
	li r4, 0x0
	li r5, 0x0
	fmr f2, f1
	li r6, 0x0
	fmr f3, f1
	li r7, 0x0
	li r8, 0x0
	bl GXInitTexObjLOD
	addi r3, r1, 0x8
	li r4, 0x0
	bl GXLoadTexObj
	b L_g5_9
	L_g5_2:
	lwz r4, 0x0(r4)
	addi r3, r1, 0x8
	li r5, 0x130
	li r6, 0xf0
	li r7, 0x4
	li r8, 0x0
	li r9, 0x0
	li r10, 0x0
	bl GXInitTexObj
	lfs f1, float_0_8041c7f0(r2)
	addi r3, r1, 0x8
	li r4, 0x0
	li r5, 0x0
	fmr f2, f1
	li r6, 0x0
	fmr f3, f1
	li r7, 0x0
	li r8, 0x0
	bl GXInitTexObjLOD
	L_g5_9:
	addi r3, r1, 0x8
	li r4, 0x0
	bl GXLoadTexObj
	addi r3, r1, 0x8
	la r4, inta_tex(r13)
	li r5, 0x4
	li r6, 0x8
	li r7, 0x0
	li r8, 0x1
	li r9, 0x1
	li r10, 0x0
	bl GXInitTexObj
	lfs f1, float_0_8041c7f0(r2)
	addi r3, r1, 0x8
	li r4, 0x1
	li r5, 0x1
	fmr f2, f1
	li r6, 0x0
	fmr f3, f1
	li r7, 0x0
	li r8, 0x0
	bl GXInitTexObjLOD
	addi r3, r1, 0x8
	li r4, 0x1
	bl GXLoadTexObj
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x1
	li r4, 0x1
	li r5, 0x1
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x1
	li r4, 0xf
	li r5, 0x8
	li r6, 0x0
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x6
	bl GXSetTevAlphaIn
	lwz r5, screen_wp(r13)
	lwz r0, 0x24(r5)
	cmpwi r0, 0x0
	bne L_g5_10
	lwz r4, 0x20(r5)
	li r3, 0xc8
	addi r0, r4, 0x1
	stw r0, 0x20(r5)
	lwz r4, screen_wp(r13)
	lwz r4, 0x20(r4)
	divw r0, r4, r3
	mullw r0, r0, r3
	subf. r0, r0, r4
	bne L_g5_11
	bl rand
	li r4, 0x3
	divw r0, r3, r4
	mullw r0, r0, r4
	subf r0, r0, r3
	cmpwi r0, 0x1
	beq L_g5_12
	bge L_g5_11
	cmpwi r0, 0x0
	bge L_g5_13
	b L_g5_11
	b L_g5_11
	L_g5_13:
	lwz r3, screen_wp(r13)
	lfs f0, float_1_8041c7f4(r2)
	lfs f2, 0x8(r3)
	lfs f1, float_0_8041c7f0(r2)
	fsubs f0, f0, f2
	fdivs f2, f0, f2
	bl randf
	lwz r3, screen_wp(r13)
	lfs f0, float_1_8041c7f4(r2)
	stfs f1, 0x14(r3)
	lfs f1, float_0_8041c7f0(r2)
	lwz r3, screen_wp(r13)
	lfs f2, 0x8(r3)
	fsubs f0, f0, f2
	fdivs f2, f0, f2
	bl randf
	lwz r3, screen_wp(r13)
	stfs f1, 0x1c(r3)
	b L_g5_11
	L_g5_12:
	lfs f1, float_1_8041c7f4(r2)
	lfs f2, float_0p25_8041c7f8(r2)
	bl randf
	lwz r3, screen_wp(r13)
	stfs f1, 0xc(r3)
	L_g5_11:
	lwz r4, screen_wp(r13)
	addi r3, r1, 0x58
	lfs f2, float_60_8041c7fc(r2)
	lfs f1, 0x8(r4)
	lfs f0, 0xc(r4)
	lfs f3, float_1_8041c7f4(r2)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	fadds f0, f1, f0
	stfs f0, 0x8(r4)
	lwz r4, screen_wp(r13)
	lfs f1, 0x10(r4)
	lfs f0, 0x14(r4)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	fadds f0, f1, f0
	stfs f0, 0x10(r4)
	lwz r4, screen_wp(r13)
	lfs f1, 0x18(r4)
	lfs f0, 0x1c(r4)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	fadds f0, f1, f0
	stfs f0, 0x18(r4)
	lwz r4, screen_wp(r13)
	lfs f1, 0x8(r4)
	fmr f2, f1
	bl PSMTXScale
	lwz r3, screen_wp(r13)
	lfs f0, float_1_8041c7f4(r2)
	lfs f1, 0x8(r3)
	lfs f2, 0x18(r3)
	fsubs f0, f0, f1
	fdivs f1, f0, f1
	fcmpo cr0, f2, f1
	ble L_g5_14
	fmr f2, f1
	L_g5_14:
	lfs f0, 0x10(r3)
	fcmpo cr0, f0, f1
	ble L_g5_15
	b L_g5_16
	L_g5_15:
	fmr f1, f0
	L_g5_16:
	lfs f3, float_0_8041c7f0(r2)
	addi r3, r1, 0x28
	bl PSMTXTrans
	addi r3, r1, 0x58
	addi r4, r1, 0x28
	addi r5, r1, 0x88
	bl PSMTXConcat
	b L_g5_17
	L_g5_10:
	lfs f1, float_4p75_8041c800(r2)
	addi r3, r1, 0x88
	lfs f2, float_3p75_8041c804(r2)
	lfs f3, float_0_8041c7f0(r2)
	bl PSMTXScale
	L_g5_17:
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x1e
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	addi r3, r1, 0x88
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	li r3, 0x4
	bl camGetPtr
	mr r4, r3
	lfs f1, float_1_8041c7f4(r2)
	lfs f4, float_100_8041c810(r2)
	addi r3, r1, 0x88
	lfs f0, 0x14(r4)
	fmr f3, f1
	lfs f2, float_1000_8041c814(r2)
	fsubs f4, f4, f0
	lfs f5, float_6_8041c80c(r2)
	lfs f0, float_16_8041c808(r2)
	fdivs f2, f4, f2
	fmadds f2, f5, f2, f0
	bl PSMTXScale
	li r3, 0x1
	li r4, 0x1
	li r5, 0x4
	li r6, 0x21
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	addi r3, r1, 0x88
	li r4, 0x21
	li r5, 0x1
	bl GXLoadTexMtxImm
	li r0, 0x2
	stw r0, 0xc(r27)
	stw r0, 0x14(r27)
	stw r0, 0x10(r27)
	L_g5_1:
	lmw r23, 0xbc(r1)
	lwz r0, 0xe4(r1)
	mtlr r0
	addi r1, r1, 0xe0
	blr
}

asm s32 tou_gamen_screen_tev_init(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r4, 0x1e0
	li r5, 0x0
	stw r0, 0x14(r1)
	li r6, 0x0
	li r7, 0x0
	stmw r30, 0x8(r1)
	mr r30, r3
	li r3, 0x260
	bl GXGetTexBufferSize
	mr r0, r3
	li r3, 0x2c
	mr r31, r0
	bl _mapAlloc
	stw r3, screen_wp(r13)
	mr r3, r31
	bl _mapAlloc
	lwz r5, screen_wp(r13)
	lis r4, 0xf5de
	li r0, 0x0
	lfs f2, float_1_8041c7f4(r2)
	stw r3, 0x0(r5)
	mr r3, r30
	lfs f1, float_0_8041c7f0(r2)
	addi r4, r4, 0x180
	lwz r5, screen_wp(r13)
	lfs f0, float_neg1_8041c818(r2)
	stw r0, 0x4(r5)
	lwz r5, screen_wp(r13)
	stfs f2, 0xc(r5)
	lwz r5, screen_wp(r13)
	stfs f2, 0x8(r5)
	lwz r5, screen_wp(r13)
	stfs f1, 0x14(r5)
	lwz r5, screen_wp(r13)
	stfs f1, 0x10(r5)
	lwz r5, screen_wp(r13)
	stfs f1, 0x1c(r5)
	lwz r5, screen_wp(r13)
	stfs f1, 0x18(r5)
	lwz r5, screen_wp(r13)
	stw r0, 0x20(r5)
	lwz r5, screen_wp(r13)
	stfs f0, 0x28(r5)
	bl evtGetValue
	cmpwi r3, 0xa3
	bne L_g5_1
	lwz r3, screen_wp(r13)
	li r0, 0x1
	stw r0, 0x24(r3)
	L_g5_1:
	la r3, screen_evt(r13)
	li r4, 0x0
	li r5, 0x0
	bl evtEntry
	lmw r30, 0x8(r1)
	li r3, 0x2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 screen_evt_func(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, screen_capture@ha
	lfs f1, float_1000_8041c814(r2)
	stw r0, 0x14(r1)
	addi r5, r3, screen_capture@l
	li r3, 0x8
	li r4, 0x0
	li r6, 0x0
	bl dispEntry
	lwz r0, 0x14(r1)
	li r3, 0x0
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static void screen_capture(CameraId camId, void* param) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x0
	li r4, 0x0
	stw r0, 0x14(r1)
	li r5, 0x260
	li r6, 0x1e0
	bl GXSetTexCopySrc
	li r3, 0x130
	li r4, 0xf0
	li r5, 0x4
	li r6, 0x1
	bl GXSetTexCopyDst
	lwz r3, screen_wp(r13)
	li r4, 0x0
	lwz r3, 0x0(r3)
	bl GXCopyTex
	bl GXPixModeSync
	lwz r3, screen_wp(r13)
	li r0, 0x1
	stw r0, 0x4(r3)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
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
	lis r4, double_to_int_802f3220@ha
	lfd f3, double_to_int_802f3220@l(r4)
	fsubs f0, f31, f30
	stw r0, 0x8(r1)
	lfs f1, float_32767_8041c81c(r2)
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

asm BattleSpotEntry* batSpotEntry(void) {
	nofralloc
	lwz r4, wp(r13)
	lis r3, vec3_802f31a8@ha
	addi r5, r3, vec3_802f31a8@l
	lwz r0, 0x0(r4)
	lwz r3, 0x4(r4)
	mtctr r0
	cmpwi r0, 0x0
	ble L_g5_1
	L_g5_2:
	lhz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq L_g5_1
	addi r3, r3, 0x2c
	bdnz L_g5_2
	L_g5_1:
	lwz r4, 0x54(r5)
	lwz r0, 0x58(r5)
	stw r4, 0x4(r3)
	stw r0, 0x8(r3)
	lwz r0, 0x5c(r5)
	stw r0, 0xc(r3)
	lwz r4, 0x60(r5)
	lwz r0, 0x64(r5)
	stw r4, 0x1c(r3)
	stw r0, 0x20(r3)
	lwz r0, 0x68(r5)
	stw r0, 0x24(r3)
	lwz r4, 0x6c(r5)
	lwz r0, 0x70(r5)
	stw r4, 0x10(r3)
	stw r0, 0x14(r3)
	lwz r0, 0x74(r5)
	stw r0, 0x18(r3)
	lwz r0, unk_8042302c(r2)
	stw r0, 0x28(r3)
	lhz r0, 0x0(r3)
	ori r0, r0, 0x1
	sth r0, 0x0(r3)
	blr
}

asm void drawCone(CameraId camId, BattleSpotEntry* e) {
	nofralloc
	stwu r1, -0x160(r1)
	mflr r0
	stw r0, 0x164(r1)
	stfd f31, 0x150(r1)
	psq_st f31, 0x158(r1), 0, 0
	stfd f30, 0x140(r1)
	psq_st f30, 0x148(r1), 0, 0
	stmw r29, 0x134(r1)
	mr r29, r4
	bl camGetPtr
	lfs f1, 0x4(r29)
	mr r31, r3
	lfs f2, 0x8(r29)
	addi r3, r1, 0xf8
	lfs f3, 0xc(r29)
	bl PSMTXTrans
	lfs f1, 0x1c(r29)
	addi r3, r1, 0xc8
	lfs f2, 0x20(r29)
	lfs f3, 0x24(r29)
	bl PSMTXScale
	lfs f1, float_deg2rad_8041c820(r2)
	addi r3, r1, 0x68
	lfs f0, 0x10(r29)
	li r4, 0x78
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lfs f1, float_deg2rad_8041c820(r2)
	addi r3, r1, 0x38
	lfs f0, 0x14(r29)
	li r4, 0x79
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lfs f1, float_deg2rad_8041c820(r2)
	addi r3, r1, 0x8
	lfs f0, 0x18(r29)
	li r4, 0x7a
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r4, r1, 0x38
	addi r3, r1, 0x8
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x38
	addi r4, r1, 0x68
	addi r5, r1, 0x98
	bl PSMTXConcat
	addi r4, r1, 0xf8
	addi r3, r31, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x98
	addi r3, r1, 0xf8
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x98
	addi r4, r1, 0xc8
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x98
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	li r3, 0xa0
	li r4, 0x0
	li r5, 0x20
	bl GXBegin
	lfs f0, float_0_8041c7f0(r2)
	lis r31, 0xcc01
	li r0, 0x0
	li r30, 0x0
	stfs f0, -0x8000(r31)
	lfs f0, float_0_8041c7f0(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_0_8041c7f0(r2)
	stfs f0, -0x8000(r31)
	lbz r3, 0x2b(r29)
	stb r0, -0x8000(r31)
	stb r0, -0x8000(r31)
	stb r0, -0x8000(r31)
	stb r3, -0x8000(r31)
	L_g5_1:
	cmpwi r30, 0x1e
	bne L_g5_2
	lfs f31, float_0_8041c7f0(r2)
	b L_g5_3
	L_g5_2:
	neg r3, r30
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802f3220@ha
	stw r3, 0x12c(r1)
	lfd f2, double_to_int_802f3220@l(r4)
	stw r0, 0x128(r1)
	lfs f3, float_6p2832_8041c824(r2)
	lfd f1, 0x128(r1)
	lfs f0, float_30_8041c828(r2)
	fsubs f1, f1, f2
	fmuls f1, f3, f1
	fdivs f31, f1, f0
	L_g5_3:
	fmr f1, f31
	bl sin
	frsp f30, f1
	fmr f1, f31
	bl cos
	frsp f0, f1
	addi r30, r30, 0x1
	li r3, 0x3
	li r0, 0x0
	cmpwi r30, 0x1f
	stfs f0, -0x8000(r31)
	stfs f30, -0x8000(r31)
	lfs f0, float_neg1_8041c818(r2)
	stfs f0, -0x8000(r31)
	lbz r4, 0x2b(r29)
	divw r3, r4, r3
	stb r0, -0x8000(r31)
	stb r0, -0x8000(r31)
	stb r0, -0x8000(r31)
	stb r3, -0x8000(r31)
	blt L_g5_1
	psq_l f31, 0x158(r1), 0, 0
	lfd f31, 0x150(r1)
	psq_l f30, 0x148(r1), 0, 0
	lfd f30, 0x140(r1)
	lmw r29, 0x134(r1)
	lwz r0, 0x164(r1)
	mtlr r0
	addi r1, r1, 0x160
	blr
}

asm void batSpotDisp(CameraId camId, void* param) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r29, 0x14(r1)
	mr r29, r3
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xb
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xb
	li r5, 0x1
	li r6, 0x5
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	bl GXSetNumTexGens
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0xa
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x5
	bl GXSetTevAlphaIn
	li r3, 0x1
	bl GXSetZCompLoc
	li r3, 0x7
	li r4, 0x0
	li r5, 0x0
	li r6, 0x7
	li r7, 0x0
	bl GXSetAlphaCompare
	li r3, 0x1
	bl GXSetNumChans
	lwz r3, wp(r13)
	li r31, 0x0
	lwz r30, 0x4(r3)
	b L_g5_1
	L_g5_2:
	lhz r3, 0x0(r30)
	clrlwi. r0, r3, 31
	beq L_g5_3
	rlwinm. r0, r3, 0, 30, 30
	beq L_g5_3
	li r3, 0x2
	bl GXSetCullMode
	li r3, 0x1
	bl GXSetAlphaUpdate
	li r3, 0x0
	bl GXSetColorUpdate
	li r3, 0x1
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	li r3, 0x0
	li r4, 0x4
	li r5, 0x5
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x1
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	mr r3, r29
	mr r4, r30
	bl drawCone
	li r3, 0x1
	bl GXSetCullMode
	li r3, 0x1
	bl GXSetAlphaUpdate
	li r3, 0x0
	bl GXSetColorUpdate
	li r3, 0x1
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	li r3, 0x0
	li r4, 0x4
	li r5, 0x5
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	lwz r0, unk_80423028(r2)
	addi r4, r1, 0xc
	li r3, 0x4
	stw r0, 0xc(r1)
	bl GXSetChanMatColor
	mr r3, r29
	mr r4, r30
	bl drawCone
	li r3, 0x2
	bl GXSetCullMode
	li r3, 0x0
	bl GXSetAlphaUpdate
	li r3, 0x1
	bl GXSetColorUpdate
	li r3, 0x1
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	li r3, 0x1
	li r4, 0x6
	li r5, 0x7
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	lwz r0, 0x28(r30)
	addi r4, r1, 0x8
	li r3, 0x4
	stw r0, 0x8(r1)
	bl GXSetChanMatColor
	mr r3, r29
	mr r4, r30
	bl drawCone
	L_g5_3:
	addi r31, r31, 0x1
	addi r30, r30, 0x2c
	L_g5_1:
	lwz r3, wp(r13)
	lwz r0, 0x0(r3)
	cmpw r31, r0
	blt L_g5_2
	lmw r29, 0x14(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void batSpotMain() {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r3, wp(r13)
	lwz r0, 0x0(r3)
	mtctr r0
	cmpwi r0, 0x0
	ble L_g5_1
	L_g5_2:
	bdnz L_g5_2
	L_g5_1:
	lwz r0, 0x8(r3)
	cmpwi r0, 0x0
	ble L_g5_3
	lis r3, batSpotDisp@ha
	lfs f1, float_neg1000_8041c82c(r2)
	addi r5, r3, batSpotDisp@l
	li r4, 0x0
	li r3, 0x6
	li r6, 0x0
	bl dispEntry
	L_g5_3:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void batSpotInit(void) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stfd f30, 0x40(r1)
	psq_st f30, 0x48(r1), 0, 0
	stfd f29, 0x30(r1)
	psq_st f29, 0x38(r1), 0, 0
	stmw r29, 0x24(r1)
	lwz r4, wp(r13)
	li r0, 0x5
	lis r5, vec3_802f31a8@ha
	li r3, 0x4
	stw r0, 0x0(r4)
	addi r31, r5, vec3_802f31a8@l
	lwz r4, wp(r13)
	lwz r0, 0x0(r4)
	mulli r4, r0, 0x2c
	bl __memAlloc
	lwz r5, wp(r13)
	li r4, 0x0
	stw r3, 0x4(r5)
	lwz r3, wp(r13)
	lwz r0, 0x0(r3)
	lwz r3, 0x4(r3)
	mulli r5, r0, 0x2c
	bl memset
	lfs f29, float_50_8041c834(r2)
	li r29, 0x0
	lfd f30, 0x78(r31)
	lis r30, 0x4330
	lfs f31, float_neg100_8041c830(r2)
	L_g5_1:
	bl batSpotEntry
	xoris r0, r29, 0x8000
	lwz r6, 0x30(r31)
	stw r0, 0x1c(r1)
	addi r29, r29, 0x1
	lwz r5, 0x34(r31)
	cmpwi r29, 0x5
	stw r30, 0x18(r1)
	lwz r4, 0x38(r31)
	lfd f0, 0x18(r1)
	stw r6, 0x8(r1)
	fsubs f0, f0, f30
	stw r4, 0x10(r1)
	fmadds f0, f29, f0, f31
	stw r5, 0xc(r1)
	stfs f0, 0x8(r1)
	lwz r0, 0x8(r1)
	stw r0, 0x4(r3)
	stw r5, 0x8(r3)
	stw r4, 0xc(r3)
	lwz r4, 0x3c(r31)
	lwz r0, 0x40(r31)
	stw r4, 0x10(r3)
	stw r0, 0x14(r3)
	lwz r0, 0x44(r31)
	stw r0, 0x18(r3)
	lwz r4, 0x48(r31)
	lwz r0, 0x4c(r31)
	stw r4, 0x1c(r3)
	stw r0, 0x20(r3)
	lwz r0, 0x50(r31)
	stw r0, 0x24(r3)
	lwz r0, dat_8041c7ec(r2)
	stw r0, 0x28(r3)
	blt L_g5_1
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	psq_l f29, 0x38(r1), 0, 0
	lfd f29, 0x30(r1)
	lmw r29, 0x24(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm BattleSpotWork* BatSpotGetPtr(void) {
	nofralloc
	lwz r3, wp(r13)
	blr
}

asm f32 getSpline(f32* a, f32* b, f32* c, f32* d, s32* t, s32 n, s32 x) {
	nofralloc
	subic. r11, r8, 0x1
	lis r8, double_to_int_802f3220@ha
	addi r10, r8, double_to_int_802f3220@l
	stwu r1, -0x10(r1)
	lfd f2, 0x0(r10)
	lis r10, 0x4330
	addi r0, r11, 0x1
	lfs f0, float_0_8041c7f0(r2)
	slwi r8, r11, 2
	mtctr r0
	blt L_g5_1
	L_g5_2:
	lwzx r0, r7, r8
	stw r10, 0x8(r1)
	subf r0, r0, r9
	xoris r0, r0, 0x8000
	stw r0, 0xc(r1)
	lfd f1, 0x8(r1)
	fsubs f1, f1, f2
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	beq L_g5_1
	subi r11, r11, 0x1
	subi r8, r8, 0x4
	bdnz L_g5_2
	L_g5_1:
	slwi r10, r11, 2
	lis r0, 0x4330
	lwzx r8, r7, r10
	lis r7, double_to_int_802f3220@ha
	stw r0, 0x8(r1)
	subf r0, r8, r9
	lfd f4, double_to_int_802f3220@l(r7)
	xoris r0, r0, 0x8000
	lfsx f3, r6, r10
	stw r0, 0xc(r1)
	lfsx f2, r5, r10
	lfd f0, 0x8(r1)
	lfsx f1, r4, r10
	fsubs f4, f0, f4
	lfsx f0, r3, r10
	fmadds f2, f4, f3, f2
	fmadds f1, f4, f2, f1
	fmadds f1, f4, f1, f0
	addi r1, r1, 0x10
	blr
}

asm void BattleStageReturnAudDarkBase(s32 time, u8 mode) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r5, _battleWorkPointer(r13)
	addis r6, r5, 0x1
	mr r5, r3
	addi r3, r6, 0x6ee4
	mr r6, r4
	lbz r4, 0x5(r3)
	bl BattleStageSetDark
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleStageSetAudDarkBase(u8 v, s32 time, u8 mode) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	mr r0, r4
	mr r4, r3
	lwz r6, _battleWorkPointer(r13)
	addis r7, r6, 0x1
	mr r6, r5
	mr r5, r0
	addi r3, r7, 0x6ee4
	bl BattleStageSetDarkBase
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleStageSetAudDark(u8 v, s32 time, u8 mode) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	mr r0, r4
	mr r4, r3
	lwz r6, _battleWorkPointer(r13)
	addis r7, r6, 0x1
	mr r6, r5
	mr r5, r0
	addi r3, r7, 0x6ee4
	bl BattleStageSetDark
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleStageReturnStgDarkBase(s32 time, u8 mode) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r5, _battleWorkPointer(r13)
	addis r6, r5, 0x1
	mr r5, r3
	addi r3, r6, 0x6ec4
	mr r6, r4
	lbz r4, 0x5(r3)
	bl BattleStageSetDark
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleStageSetStgDarkBase(u8 v, s32 time, u8 mode) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	mr r0, r4
	mr r4, r3
	lwz r6, _battleWorkPointer(r13)
	addis r7, r6, 0x1
	mr r6, r5
	mr r5, r0
	addi r3, r7, 0x6ec4
	bl BattleStageSetDarkBase
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleStageSetStgDark(u8 v, s32 time, u8 mode) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	mr r0, r4
	mr r4, r3
	lwz r6, _battleWorkPointer(r13)
	addis r7, r6, 0x1
	mr r6, r5
	mr r5, r0
	addi r3, r7, 0x6ec4
	bl BattleStageSetDark
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleStageSetDarkBase(StageDark* d, u8 v, s32 time, u8 mode) {
	nofralloc
	lbz r0, 0x5(r3)
	cmpwi r5, 0x0
	stb r0, 0x7(r3)
	stb r4, 0x9(r3)
	stw r5, 0x10(r3)
	stw r5, 0x18(r3)
	stb r6, 0x1d(r3)
	bnelr
	stb r4, 0x5(r3)
	blr
}

asm void BattleStageSetDark(StageDark* d, u8 v, s32 time, u8 mode) {
	nofralloc
	lbz r0, 0x4(r3)
	cmpwi r5, 0x0
	stb r0, 0x6(r3)
	stb r4, 0x8(r3)
	stw r5, 0xc(r3)
	stw r5, 0x14(r3)
	stb r6, 0x1c(r3)
	bnelr
	stb r4, 0x4(r3)
	blr
}

asm void BattleStageLightSetUpVec(s32 idx, f32 x, f32 y, f32 z, s32 time, u8 mode) {
	nofralloc
	stwu r1, -0x20(r1)
	mulli r3, r3, 0xe8
	cmpwi r4, 0x0
	lwz r6, _battleWorkPointer(r13)
	addi r7, r3, 0x4
	addis r6, r6, 0x1
	addi r6, r6, 0x63e0
	add r7, r6, r7
	lfs f0, 0xb4(r7)
	stfs f0, 0xc0(r7)
	lfs f0, 0xb8(r7)
	stfs f0, 0xc4(r7)
	lfs f0, 0xbc(r7)
	stfs f0, 0xc8(r7)
	stfs f1, 0xcc(r7)
	stfs f2, 0xd0(r7)
	stfs f3, 0xd4(r7)
	stw r4, 0xd8(r7)
	stw r4, 0xdc(r7)
	stb r5, 0xe0(r7)
	bne L_g5_1
	lis r3, vec3_802f31cc@ha
	addi r4, r3, vec3_802f31cc@l
	lwz r0, 0x0(r4)
	lwz r3, 0x4(r4)
	stw r0, 0x8(r1)
	lwz r0, 0x8(r4)
	stw r3, 0xc(r1)
	stfs f1, 0x8(r1)
	stw r0, 0x10(r1)
	lwz r0, 0x8(r1)
	stfs f2, 0xc(r1)
	stfs f3, 0x10(r1)
	lwz r3, 0xc(r1)
	stw r0, 0xb4(r7)
	lwz r0, 0x10(r1)
	stw r3, 0xb8(r7)
	stw r0, 0xbc(r7)
	L_g5_1:
	addi r1, r1, 0x20
	blr
}

asm void BattleStageLightSetTargetByUnit(s32 idx, s32 unitId, f32 x, f32 y, f32 z, s32 time, u8 mode) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stfd f30, 0x40(r1)
	psq_st f30, 0x48(r1), 0, 0
	stfd f29, 0x30(r1)
	psq_st f29, 0x38(r1), 0, 0
	stmw r29, 0x24(r1)
	fmr f29, f1
	mr r29, r3
	fmr f30, f2
	lwz r3, _battleWorkPointer(r13)
	fmr f31, f3
	mr r30, r5
	mr r31, r6
	bl BattleGetUnitPtr
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	addi r6, r1, 0x8
	bl BtlUnit_GetPos
	lfs f0, 0x10(r1)
	mr r3, r29
	lfs f2, 0xc(r1)
	mr r4, r30
	fadds f1, f0, f29
	lfs f0, 0x8(r1)
	fadds f2, f2, f30
	mr r5, r31
	fadds f3, f0, f31
	stfs f1, 0x10(r1)
	stfs f2, 0xc(r1)
	stfs f3, 0x8(r1)
	bl BattleStageLightSetTarget
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	psq_l f29, 0x38(r1), 0, 0
	lfd f29, 0x30(r1)
	lmw r29, 0x24(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm void BattleStageLightSetTarget(s32 idx, f32 x, f32 y, f32 z, s32 time, u8 mode) {
	nofralloc
	stwu r1, -0x20(r1)
	mulli r3, r3, 0xe8
	cmpwi r4, 0x0
	lwz r6, _battleWorkPointer(r13)
	addi r7, r3, 0x4
	addis r6, r6, 0x1
	addi r6, r6, 0x63e0
	add r7, r6, r7
	lfs f0, 0x84(r7)
	stfs f0, 0x90(r7)
	lfs f0, 0x88(r7)
	stfs f0, 0x94(r7)
	lfs f0, 0x8c(r7)
	stfs f0, 0x98(r7)
	stfs f1, 0x9c(r7)
	stfs f2, 0xa0(r7)
	stfs f3, 0xa4(r7)
	stw r4, 0xa8(r7)
	stw r4, 0xac(r7)
	stb r5, 0xb0(r7)
	lwz r0, 0x0(r7)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x0(r7)
	bne L_g5_1
	lis r3, vec3_802f31c0@ha
	addi r4, r3, vec3_802f31c0@l
	lwz r0, 0x0(r4)
	lwz r3, 0x4(r4)
	stw r0, 0x8(r1)
	lwz r0, 0x8(r4)
	stw r3, 0xc(r1)
	stfs f1, 0x8(r1)
	stw r0, 0x10(r1)
	lwz r0, 0x8(r1)
	stfs f2, 0xc(r1)
	stfs f3, 0x10(r1)
	lwz r3, 0xc(r1)
	stw r0, 0x84(r7)
	lwz r0, 0x10(r1)
	stw r3, 0x88(r7)
	stw r0, 0x8c(r7)
	L_g5_1:
	addi r1, r1, 0x20
	blr
}

asm void BattleStageLightSetPosition(s32 idx, f32 x, f32 y, f32 z, s32 time, u8 mode) {
	nofralloc
	stwu r1, -0x20(r1)
	mulli r3, r3, 0xe8
	cmpwi r4, 0x0
	lwz r6, _battleWorkPointer(r13)
	addi r7, r3, 0x4
	addis r6, r6, 0x1
	addi r6, r6, 0x63e0
	add r7, r6, r7
	lfs f0, 0x54(r7)
	stfs f0, 0x60(r7)
	lfs f0, 0x58(r7)
	stfs f0, 0x64(r7)
	lfs f0, 0x5c(r7)
	stfs f0, 0x68(r7)
	stfs f1, 0x6c(r7)
	stfs f2, 0x70(r7)
	stfs f3, 0x74(r7)
	stw r4, 0x78(r7)
	stw r4, 0x7c(r7)
	stb r5, 0x80(r7)
	bne L_g5_1
	lis r3, vec3_802f31b4@ha
	addi r4, r3, vec3_802f31b4@l
	lwz r0, 0x0(r4)
	lwz r3, 0x4(r4)
	stw r0, 0x8(r1)
	lwz r0, 0x8(r4)
	stw r3, 0xc(r1)
	stfs f1, 0x8(r1)
	stw r0, 0x10(r1)
	lwz r0, 0x8(r1)
	stfs f2, 0xc(r1)
	stfs f3, 0x10(r1)
	lwz r3, 0xc(r1)
	stw r0, 0x54(r7)
	lwz r0, 0x10(r1)
	stw r3, 0x58(r7)
	stw r0, 0x5c(r7)
	L_g5_1:
	addi r1, r1, 0x20
	blr
}

asm void BattleStageLightSetWidth(s32 idx, s32 width, s32 time, u8 mode) {
	nofralloc
	stwu r1, -0x10(r1)
	mulli r7, r3, 0xe8
	xoris r3, r4, 0x8000
	lwz r8, _battleWorkPointer(r13)
	lis r0, 0x4330
	lis r4, double_to_int_802f3220@ha
	stw r3, 0xc(r1)
	addis r8, r8, 0x1
	addi r7, r7, 0x4
	stw r0, 0x8(r1)
	addi r8, r8, 0x63e0
	add r7, r8, r7
	lfd f1, double_to_int_802f3220@l(r4)
	lfd f0, 0x8(r1)
	cmpwi r5, 0x0
	lfs f2, 0x3c(r7)
	fsubs f0, f0, f1
	stfs f2, 0x40(r7)
	stfs f0, 0x44(r7)
	stw r5, 0x48(r7)
	stw r5, 0x4c(r7)
	stb r6, 0x50(r7)
	bne L_g5_1
	stw r3, 0xc(r1)
	stw r0, 0x8(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f1
	stfs f0, 0x3c(r7)
	L_g5_1:
	addi r1, r1, 0x10
	blr
}

asm void BattleStageLightSetLightColor(s32 idx, u8 r, u8 g, u8 b, s32 time, u8 mode) {
	nofralloc
	stwu r1, -0x20(r1)
	mulli r3, r3, 0xe8
	cmpwi r7, 0x0
	lwz r9, _battleWorkPointer(r13)
	lwz r0, unk_80423020(r2)
	addi r10, r3, 0x4
	addis r9, r9, 0x1
	addi r9, r9, 0x63e0
	stw r0, 0x10(r1)
	add r10, r9, r10
	lbz r9, 0x24(r10)
	lbz r3, 0x25(r10)
	lbz r0, 0x26(r10)
	stb r9, 0x10(r1)
	stb r3, 0x11(r1)
	stb r0, 0x12(r1)
	lwz r0, 0x10(r1)
	stw r0, 0x28(r10)
	lwz r0, unk_80423024(r2)
	stw r0, 0xc(r1)
	stb r4, 0xc(r1)
	stb r5, 0xd(r1)
	stb r6, 0xe(r1)
	lwz r0, 0xc(r1)
	stw r0, 0x2c(r10)
	stw r7, 0x30(r10)
	stw r7, 0x34(r10)
	stb r8, 0x38(r10)
	bne L_g5_1
	lwz r0, dat_8041c7e8(r2)
	lbz r4, 0x24(r10)
	stw r0, 0x8(r1)
	lbz r3, 0x25(r10)
	lbz r0, 0x26(r10)
	stb r4, 0x8(r1)
	stb r3, 0x9(r1)
	stb r0, 0xa(r1)
	lwz r0, 0x8(r1)
	stw r0, 0x24(r10)
	L_g5_1:
	addi r1, r1, 0x20
	blr
}

asm void BattleStageLightRelease(s32 idx, s32 time, u8 mode) {
	nofralloc
	stwu r1, -0x10(r1)
	mulli r3, r3, 0xe8
	lwz r6, _battleWorkPointer(r13)
	addi r7, r3, 0x4
	addis r6, r6, 0x1
	addi r6, r6, 0x63e0
	add r7, r6, r7
	lwz r3, 0x0(r7)
	clrlwi. r0, r3, 31
	beq L_g5_1
	cmpwi r4, 0x0
	bne L_g5_2
	li r0, 0x0
	stw r0, 0x0(r7)
	b L_g5_1
	L_g5_2:
	ori r0, r3, 0x2
	stw r0, 0x0(r7)
	lwz r0, unk_80423018(r2)
	lbz r6, 0x24(r7)
	stw r0, 0x8(r1)
	lbz r3, 0x25(r7)
	lbz r0, 0x26(r7)
	stb r6, 0x8(r1)
	stb r3, 0x9(r1)
	stb r0, 0xa(r1)
	lwz r0, 0x8(r1)
	stw r0, 0x28(r7)
	lwz r0, unk_8042301c(r2)
	stw r0, 0x2c(r7)
	stw r4, 0x30(r7)
	stw r4, 0x34(r7)
	stb r5, 0x38(r7)
	L_g5_1:
	addi r1, r1, 0x10
	blr
}

asm s32 BattleStageSysLightEntry(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r28, 0x10(r1)
	mr r28, r3
	li r29, 0x0
	li r31, 0x0
	lwz r4, _battleWorkPointer(r13)
	addis r30, r4, 0x1
	addi r30, r30, 0x63e0
	L_g5_1:
	addi r3, r31, 0x4
	add r3, r30, r3
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq L_g5_2
	mr r4, r28
	addi r3, r3, 0x4
	bl strcmp
	L_g5_2:
	addi r29, r29, 0x1
	addi r31, r31, 0xe8
	cmpwi r29, 0x6
	ble L_g5_1
	li r0, 0x7
	li r31, 0x0
	li r3, 0x0
	mtctr r0
	L_g5_3:
	addi r5, r3, 0x4
	add r5, r30, r5
	lwz r0, 0x0(r5)
	clrlwi. r0, r0, 31
	bne L_g5_4
	li r0, 0x1
	mr r4, r28
	stw r0, 0x0(r5)
	addi r3, r5, 0x4
	bl strcpy
	b L_g5_5
	L_g5_4:
	addi r31, r31, 0x1
	addi r3, r3, 0xe8
	bdnz L_g5_3
	L_g5_5:
	mr r3, r31
	lmw r28, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 BattleStageGetLightNumberByName(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r28, 0x10(r1)
	mr r28, r3
	li r29, 0x0
	li r31, 0x0
	lwz r4, _battleWorkPointer(r13)
	addis r30, r4, 0x1
	addi r30, r30, 0x63e0
	L_g5_1:
	addi r3, r31, 0x4
	add r3, r30, r3
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq L_g5_2
	mr r4, r28
	addi r3, r3, 0x4
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_2
	mr r3, r29
	b L_g5_3
	L_g5_2:
	addi r29, r29, 0x1
	addi r31, r31, 0xe8
	cmpwi r29, 0xc
	blt L_g5_1
	li r3, -0x1
	L_g5_3:
	lmw r28, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void BattleStageOffLightEnemyInCommand(void) {
	nofralloc
	blr
}

asm void BattleStageOnLightEnemyInCommand(void) {
	nofralloc
	blr
}

asm void BattleStageOffLightFriendInCommand(void) {
	nofralloc
	blr
}

asm void BattleStageOnLightFriendInCommand(void) {
	nofralloc
	blr
}

asm void BattleStageOffLightInCommand(void) {
	nofralloc
	blr
}

asm void BattleStageOnLightInCommand(void) {
	nofralloc
	blr
}

asm void BattleStageDispLight(CameraId camId, void* param) {
	nofralloc
	stwu r1, -0x140(r1)
	mflr r0
	stw r0, 0x144(r1)
	stfd f31, 0x130(r1)
	psq_st f31, 0x138(r1), 0, 0
	stfd f30, 0x120(r1)
	psq_st f30, 0x128(r1), 0, 0
	stfd f29, 0x110(r1)
	psq_st f29, 0x118(r1), 0, 0
	stfd f28, 0x100(r1)
	psq_st f28, 0x108(r1), 0, 0
	stfd f27, 0xf0(r1)
	psq_st f27, 0xf8(r1), 0, 0
	stfd f26, 0xe0(r1)
	psq_st f26, 0xe8(r1), 0, 0
	stfd f25, 0xd0(r1)
	psq_st f25, 0xd8(r1), 0, 0
	stfd f24, 0xc0(r1)
	psq_st f24, 0xc8(r1), 0, 0
	stfd f23, 0xb0(r1)
	psq_st f23, 0xb8(r1), 0, 0
	stfd f22, 0xa0(r1)
	psq_st f22, 0xa8(r1), 0, 0
	stfd f21, 0x90(r1)
	psq_st f21, 0x98(r1), 0, 0
	stmw r23, 0x6c(r1)
	lwz r4, _battleWorkPointer(r13)
	li r3, 0x4
	addis r29, r4, 0x1
	addi r29, r29, 0x63e0
	bl camGetPtr
	mr r27, r3
	li r3, 0x2
	bl GXSetCullMode
	li r3, 0x1
	bl GXSetZCompLoc
	li r3, 0x7
	li r4, 0x0
	li r5, 0x0
	li r6, 0x7
	li r7, 0x0
	bl GXSetAlphaCompare
	li r3, 0x1
	li r4, 0x2
	li r5, 0x1
	li r6, 0x5
	bl GXSetBlendMode
	li r3, 0x1
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xb
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xb
	li r5, 0x1
	li r6, 0x5
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x1
	bl GXSetNumChans
	li r3, 0x2
	li r4, 0x0
	li r5, 0x1
	li r6, 0x1
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	li r3, 0x0
	bl GXSetNumTexGens
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0xa
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x4
	bl GXSetTevOrder
	addi r3, r27, 0x11c
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r30, 0x0
	li r28, 0x0
	L_g5_1:
	add r31, r29, r28
	lwz r0, 0x4(r31)
	clrlwi. r0, r0, 31
	beq L_g5_2
	lis r3, vec3_802f31a8@ha
	lfs f1, 0x88(r31)
	addi r5, r3, vec3_802f31a8@l
	lfs f0, 0x58(r31)
	lwz r4, 0x0(r5)
	li r26, 0x0
	lwz r3, 0x4(r5)
	fsubs f1, f1, f0
	lwz r0, 0x8(r5)
	lis r27, 0xcc01
	stw r4, 0x8(r1)
	lfs f2, 0x8c(r31)
	lfs f0, 0x5c(r31)
	stfs f1, 0x8(r1)
	lfs f1, 0x90(r31)
	fsubs f2, f2, f0
	lfs f0, 0x60(r31)
	stw r3, 0xc(r1)
	lwz r4, 0x8(r1)
	fsubs f0, f1, f0
	stw r0, 0x10(r1)
	lfs f30, float_2_8041c838(r2)
	stfs f2, 0xc(r1)
	stfs f0, 0x10(r1)
	lwz r3, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r4, 0x14(r1)
	stw r3, 0x18(r1)
	stw r0, 0x1c(r1)
	lfs f31, 0x40(r31)
	lwz r3, 0xb8(r31)
	lwz r0, 0xbc(r31)
	stw r3, 0x20(r1)
	stw r0, 0x24(r1)
	lwz r0, 0xc0(r31)
	stw r0, 0x28(r1)
	L_g5_3:
	lfs f29, 0x58(r31)
	addi r3, r1, 0x2c
	lfs f0, 0x88(r31)
	addi r4, r1, 0x14
	lfs f28, 0x5c(r31)
	lfs f1, 0x8c(r31)
	fsubs f2, f0, f29
	lfs f27, 0x60(r31)
	lfs f0, 0x90(r31)
	fsubs f4, f1, f28
	fmadds f26, f30, f2, f29
	lfs f3, 0x20(r1)
	fsubs f1, f0, f27
	lfs f2, 0x24(r1)
	fmadds f25, f30, f4, f28
	lfs f0, 0x28(r1)
	fmadds f24, f30, f1, f27
	lfs f1, float_0p34907_8041c83c(r2)
	fmadds f23, f3, f31, f26
	fmadds f22, f2, f31, f25
	fmadds f21, f0, f31, f24
	bl PSMTXRotAxisRad
	addi r4, r1, 0x20
	addi r3, r1, 0x2c
	mr r5, r4
	bl PSMTXMultVec
	addi r3, r1, 0x20
	mr r4, r3
	bl PSVECNormalize
	lfs f2, 0x20(r1)
	li r3, 0x90
	lfs f1, 0x24(r1)
	li r4, 0x0
	lfs f0, 0x28(r1)
	fmadds f26, f2, f31, f26
	fmadds f25, f1, f31, f25
	lbz r25, 0x28(r31)
	fmadds f24, f0, f31, f24
	lbz r24, 0x29(r31)
	lbz r23, 0x2a(r31)
	li r5, 0x3
	bl GXBegin
	stfs f29, -0x8000(r27)
	addi r26, r26, 0x1
	li r0, 0x0
	stfs f28, -0x8000(r27)
	cmpwi r26, 0x12
	stfs f27, -0x8000(r27)
	stb r25, -0x8000(r27)
	stb r24, -0x8000(r27)
	stb r23, -0x8000(r27)
	stb r0, -0x8000(r27)
	stfs f23, -0x8000(r27)
	stfs f22, -0x8000(r27)
	stfs f21, -0x8000(r27)
	stb r25, -0x8000(r27)
	stb r24, -0x8000(r27)
	stb r23, -0x8000(r27)
	stb r0, -0x8000(r27)
	stfs f26, -0x8000(r27)
	stfs f25, -0x8000(r27)
	stfs f24, -0x8000(r27)
	stb r25, -0x8000(r27)
	stb r24, -0x8000(r27)
	stb r23, -0x8000(r27)
	stb r0, -0x8000(r27)
	blt L_g5_3
	L_g5_2:
	addi r30, r30, 0x1
	addi r28, r28, 0xe8
	cmpwi r30, 0xc
	blt L_g5_1
	psq_l f31, 0x138(r1), 0, 0
	lfd f31, 0x130(r1)
	psq_l f30, 0x128(r1), 0, 0
	lfd f30, 0x120(r1)
	psq_l f29, 0x118(r1), 0, 0
	lfd f29, 0x110(r1)
	psq_l f28, 0x108(r1), 0, 0
	lfd f28, 0x100(r1)
	psq_l f27, 0xf8(r1), 0, 0
	lfd f27, 0xf0(r1)
	psq_l f26, 0xe8(r1), 0, 0
	lfd f26, 0xe0(r1)
	psq_l f25, 0xd8(r1), 0, 0
	lfd f25, 0xd0(r1)
	psq_l f24, 0xc8(r1), 0, 0
	lfd f24, 0xc0(r1)
	psq_l f23, 0xb8(r1), 0, 0
	lfd f23, 0xb0(r1)
	psq_l f22, 0xa8(r1), 0, 0
	lfd f22, 0xa0(r1)
	psq_l f21, 0x98(r1), 0, 0
	lfd f21, 0x90(r1)
	lmw r23, 0x6c(r1)
	lwz r0, 0x144(r1)
	mtlr r0
	addi r1, r1, 0x140
	blr
}

asm void BattleStageDispDark(CameraId camId, void* param) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x4
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	lwz r4, _battleWorkPointer(r13)
	addis r30, r4, 0x1
	bl camGetPtr
	mr r31, r3
	li r3, 0x2
	bl GXSetCullMode
	li r3, 0x1
	bl GXSetZCompLoc
	li r3, 0x7
	li r4, 0x0
	li r5, 0x0
	li r6, 0x7
	li r7, 0x0
	bl GXSetAlphaCompare
	li r3, 0x1
	li r4, 0x4
	li r5, 0x5
	li r6, 0x5
	bl GXSetBlendMode
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xb
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xb
	li r5, 0x1
	li r6, 0x5
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x1
	bl GXSetNumChans
	li r3, 0x4
	li r4, 0x0
	li r5, 0x1
	li r6, 0x1
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	li r3, 0x0
	bl GXSetNumTexGens
	addi r3, r31, 0x11c
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0xa
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x5
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	addi r31, r30, 0x6ee4
	li r3, 0x1
	li r4, 0x6
	li r5, 0x0
	bl GXSetZMode
	lfs f1, float_neg640_8041c840(r2)
	lfs f2, float_640_8041c844(r2)
	fmr f4, f1
	lfs f5, float_105_8041c848(r2)
	fmr f3, f2
	lbz r3, 0x4(r31)
	bl DarkBySquare
	li r3, 0x1
	li r4, 0x1
	li r5, 0x0
	bl GXSetZMode
	lfs f1, float_640_8041c844(r2)
	lfs f3, float_neg640_8041c840(r2)
	fmr f2, f1
	lfs f5, float_105_8041c848(r2)
	fmr f4, f3
	lbz r3, 0x4(r31)
	bl DarkBySquare
	li r3, 0x1
	li r4, 0x1
	li r5, 0x0
	bl GXSetZMode
	lfs f1, float_neg640_8041c840(r2)
	lfs f2, float_640_8041c844(r2)
	fmr f4, f1
	lfs f5, float_105_8041c848(r2)
	fmr f3, f2
	lbz r3, 0x6ec8(r30)
	bl DarkBySquare
	lmw r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void DarkBySquare(f32 x0, f32 y0, f32 x1, f32 y1, f32 z, u8 alpha) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	addi r11, r1, 0x40
	bl _savefpr_27
	stw r31, 0x14(r1)
	fmr f27, f1
	mr r31, r3
	fmr f28, f2
	li r3, 0x80
	fmr f29, f3
	li r4, 0x0
	fmr f30, f4
	li r5, 0x4
	fmr f31, f5
	bl GXBegin
	fmr f1, f27
	mr r3, r31
	fmr f2, f28
	fmr f3, f31
	bl DarkByPoint
	fmr f1, f29
	mr r3, r31
	fmr f2, f28
	fmr f3, f31
	bl DarkByPoint
	fmr f1, f29
	mr r3, r31
	fmr f2, f30
	fmr f3, f31
	bl DarkByPoint
	fmr f1, f27
	mr r3, r31
	fmr f2, f30
	fmr f3, f31
	bl DarkByPoint
	addi r11, r1, 0x40
	bl _restfpr_27
	lwz r0, 0x44(r1)
	lwz r31, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void DarkByPoint(u8 alpha, f32 x, f32 y, f32 z) {
	nofralloc
	lis r4, 0xcc01
	li r0, 0x0
	stfs f1, -0x8000(r4)
	stfs f2, -0x8000(r4)
	stfs f3, -0x8000(r4)
	stb r0, -0x8000(r4)
	stb r0, -0x8000(r4)
	stb r0, -0x8000(r4)
	stb r3, -0x8000(r4)
	blr
}

asm void BattleStageDisp(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r3, _battleWorkPointer(r13)
	lwz r4, 0x420(r3)
	bl BattleGetUnitPtr
	lis r3, BattleStageDispDark@ha
	lfs f1, float_5000_8041c84c(r2)
	addi r5, r3, BattleStageDispDark@l
	li r4, 0x2
	li r3, 0x4
	li r6, 0x0
	bl dispEntry
	lis r3, BattleStageDispLight@ha
	lfs f1, float_6000_8041c850(r2)
	addi r5, r3, BattleStageDispLight@l
	li r4, 0x2
	li r3, 0x4
	li r6, 0x0
	bl dispEntry
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleStageEnd(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	li r31, 0x0
	mr r30, r31
	li r29, 0x0
	lwz r3, _battleWorkPointer(r13)
	addis r28, r3, 0x1
	addi r28, r28, 0x63e0
	L_g5_1:
	addi r27, r31, 0x4
	add r27, r28, r27
	lwz r4, 0xe4(r27)
	cmplwi r4, 0x0
	beq L_g5_2
	li r3, 0x4
	bl __memFree
	stw r30, 0xe4(r27)
	L_g5_2:
	addi r29, r29, 0x1
	addi r31, r31, 0xe8
	cmpwi r29, 0xc
	blt L_g5_1
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void BattleStageMain(void) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stmw r27, 0x5c(r1)
	lwz r3, _battleWorkPointer(r13)
	addis r31, r3, 0x1
	addi r31, r31, 0x63e0
	bl batSpotMain
	li r29, 0x0
	li r28, 0x0
	L_g5_1:
	addi r30, r28, 0x4
	add r30, r31, r30
	lwz r0, 0x0(r30)
	clrlwi. r0, r0, 31
	beq L_g5_2
	lwz r3, 0x30(r30)
	cmpwi r3, 0x0
	ble L_g5_3
	subi r0, r3, 0x1
	lis r6, 0x4330
	stw r0, 0x30(r30)
	lis r3, double_to_int_mask_802f3228@ha
	lfd f2, double_to_int_mask_802f3228@l(r3)
	lbz r0, 0x28(r30)
	lbz r4, 0x2c(r30)
	stw r0, 0xc(r1)
	lbz r3, 0x38(r30)
	stw r6, 0x8(r1)
	lwz r5, 0x34(r30)
	extsb r3, r3
	lfd f0, 0x8(r1)
	stw r4, 0x14(r1)
	lwz r0, 0x30(r30)
	fsubs f1, f0, f2
	stw r6, 0x10(r1)
	subf r4, r0, r5
	lfd f0, 0x10(r1)
	fsubs f2, f0, f2
	bl intplGetValue
	fctiwz f0, f1
	lis r0, 0x4330
	lis r3, double_to_int_mask_802f3228@ha
	stw r0, 0x20(r1)
	lfd f2, double_to_int_mask_802f3228@l(r3)
	stfd f0, 0x18(r1)
	lwz r3, 0x1c(r1)
	stw r0, 0x28(r1)
	stb r3, 0x24(r30)
	lbz r3, 0x29(r30)
	lbz r0, 0x2d(r30)
	stw r3, 0x24(r1)
	lbz r3, 0x38(r30)
	stw r0, 0x2c(r1)
	lfd f1, 0x20(r1)
	extsb r3, r3
	lfd f0, 0x28(r1)
	fsubs f1, f1, f2
	lwz r5, 0x34(r30)
	lwz r0, 0x30(r30)
	fsubs f2, f0, f2
	subf r4, r0, r5
	bl intplGetValue
	fctiwz f0, f1
	lis r0, 0x4330
	lis r3, double_to_int_mask_802f3228@ha
	stw r0, 0x38(r1)
	lfd f2, double_to_int_mask_802f3228@l(r3)
	stfd f0, 0x30(r1)
	lwz r3, 0x34(r1)
	stw r0, 0x40(r1)
	stb r3, 0x25(r30)
	lbz r3, 0x2a(r30)
	lbz r0, 0x2e(r30)
	stw r3, 0x3c(r1)
	lbz r3, 0x38(r30)
	stw r0, 0x44(r1)
	lfd f1, 0x38(r1)
	extsb r3, r3
	lfd f0, 0x40(r1)
	fsubs f1, f1, f2
	lwz r5, 0x34(r30)
	lwz r0, 0x30(r30)
	fsubs f2, f0, f2
	subf r4, r0, r5
	bl intplGetValue
	fctiwz f0, f1
	stfd f0, 0x48(r1)
	lwz r0, 0x4c(r1)
	stb r0, 0x26(r30)
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 30, 30
	beq L_g5_3
	lbz r0, 0x24(r30)
	cmplwi r0, 0x0
	bne L_g5_3
	lbz r0, 0x25(r30)
	cmplwi r0, 0x0
	bne L_g5_3
	lbz r0, 0x26(r30)
	cmplwi r0, 0x0
	bne L_g5_3
	li r0, 0x0
	stw r0, 0x0(r30)
	b L_g5_4
	L_g5_3:
	lwz r3, 0x48(r30)
	cmpwi r3, 0x0
	ble L_g5_5
	subi r0, r3, 0x1
	stw r0, 0x48(r30)
	lbz r3, 0x50(r30)
	lwz r5, 0x4c(r30)
	lwz r0, 0x48(r30)
	extsb r3, r3
	lfs f1, 0x40(r30)
	lfs f2, 0x44(r30)
	subf r4, r0, r5
	bl intplGetValue
	stfs f1, 0x3c(r30)
	L_g5_5:
	lwz r3, 0x78(r30)
	cmpwi r3, 0x0
	ble L_g5_6
	subi r0, r3, 0x1
	stw r0, 0x78(r30)
	lbz r3, 0x80(r30)
	lwz r5, 0x7c(r30)
	lwz r0, 0x78(r30)
	extsb r3, r3
	lfs f1, 0x60(r30)
	lfs f2, 0x6c(r30)
	subf r4, r0, r5
	bl intplGetValue
	stfs f1, 0x54(r30)
	lbz r3, 0x80(r30)
	lwz r5, 0x7c(r30)
	lwz r0, 0x78(r30)
	extsb r3, r3
	lfs f1, 0x64(r30)
	lfs f2, 0x70(r30)
	subf r4, r0, r5
	bl intplGetValue
	stfs f1, 0x58(r30)
	lbz r3, 0x80(r30)
	lwz r5, 0x7c(r30)
	lwz r0, 0x78(r30)
	extsb r3, r3
	lfs f1, 0x68(r30)
	lfs f2, 0x74(r30)
	subf r4, r0, r5
	bl intplGetValue
	stfs f1, 0x5c(r30)
	L_g5_6:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 29, 29
	beq L_g5_7
	lwz r27, 0xe4(r30)
	lwz r9, 0xa8(r30)
	lwz r8, 0x0(r27)
	addi r3, r27, 0x24
	addi r4, r27, 0x44
	addi r5, r27, 0x64
	addi r6, r27, 0x84
	addi r7, r27, 0x4
	bl getSpline
	stfs f1, 0x84(r30)
	addi r3, r27, 0xa4
	addi r4, r27, 0xc4
	addi r5, r27, 0xe4
	lwz r8, 0x0(r27)
	addi r6, r27, 0x104
	lwz r9, 0xa8(r30)
	addi r7, r27, 0x4
	bl getSpline
	stfs f1, 0x88(r30)
	addi r3, r27, 0x124
	addi r4, r27, 0x144
	addi r5, r27, 0x164
	lwz r8, 0x0(r27)
	addi r6, r27, 0x184
	lwz r9, 0xa8(r30)
	addi r7, r27, 0x4
	bl getSpline
	stfs f1, 0x8c(r30)
	lwz r3, 0xa8(r30)
	addi r0, r3, 0x1
	stw r0, 0xa8(r30)
	lwz r0, 0x0(r27)
	lwz r3, 0xa8(r30)
	slwi r0, r0, 2
	lwzx r4, r27, r0
	cmpw r3, r4
	blt L_g5_8
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 28, 28
	beq L_g5_9
	subf r0, r4, r3
	stw r0, 0xa8(r30)
	b L_g5_8
	L_g5_9:
	stw r4, 0xa8(r30)
	b L_g5_8
	L_g5_7:
	lwz r3, 0xa8(r30)
	cmpwi r3, 0x0
	ble L_g5_10
	subi r0, r3, 0x1
	stw r0, 0xa8(r30)
	lbz r3, 0xb0(r30)
	lwz r5, 0xac(r30)
	lwz r0, 0xa8(r30)
	extsb r3, r3
	lfs f1, 0x90(r30)
	lfs f2, 0x9c(r30)
	subf r4, r0, r5
	bl intplGetValue
	stfs f1, 0x84(r30)
	lbz r3, 0xb0(r30)
	lwz r5, 0xac(r30)
	lwz r0, 0xa8(r30)
	extsb r3, r3
	lfs f1, 0x94(r30)
	lfs f2, 0xa0(r30)
	subf r4, r0, r5
	bl intplGetValue
	stfs f1, 0x88(r30)
	lbz r3, 0xb0(r30)
	lwz r5, 0xac(r30)
	lwz r0, 0xa8(r30)
	extsb r3, r3
	lfs f1, 0x98(r30)
	lfs f2, 0xa4(r30)
	subf r4, r0, r5
	bl intplGetValue
	stfs f1, 0x8c(r30)
	L_g5_10:
	lwz r4, 0xe4(r30)
	cmplwi r4, 0x0
	beq L_g5_8
	li r3, 0x4
	bl __memFree
	li r0, 0x0
	stw r0, 0xe4(r30)
	L_g5_8:
	lwz r3, 0xd8(r30)
	cmpwi r3, 0x0
	ble L_g5_4
	subi r0, r3, 0x1
	stw r0, 0xd8(r30)
	lbz r3, 0xe0(r30)
	lwz r5, 0xdc(r30)
	lwz r0, 0xd8(r30)
	extsb r3, r3
	lfs f1, 0xc0(r30)
	lfs f2, 0xcc(r30)
	subf r4, r0, r5
	bl intplGetValue
	stfs f1, 0xb4(r30)
	lbz r3, 0xe0(r30)
	lwz r5, 0xdc(r30)
	lwz r0, 0xd8(r30)
	extsb r3, r3
	lfs f1, 0xc4(r30)
	lfs f2, 0xd0(r30)
	subf r4, r0, r5
	bl intplGetValue
	stfs f1, 0xb8(r30)
	lbz r3, 0xe0(r30)
	lwz r5, 0xdc(r30)
	lwz r0, 0xd8(r30)
	extsb r3, r3
	lfs f1, 0xc8(r30)
	lfs f2, 0xd4(r30)
	subf r4, r0, r5
	bl intplGetValue
	stfs f1, 0xbc(r30)
	b L_g5_4
	L_g5_2:
	lwz r4, 0xe4(r30)
	cmplwi r4, 0x0
	beq L_g5_4
	li r3, 0x4
	bl __memFree
	li r0, 0x0
	stw r0, 0xe4(r30)
	L_g5_4:
	addi r29, r29, 0x1
	addi r28, r28, 0xe8
	cmpwi r29, 0xc
	blt L_g5_1
	lwz r3, 0xaf0(r31)
	cmpwi r3, 0x0
	ble L_g5_11
	subi r0, r3, 0x1
	lis r6, 0x4330
	stw r0, 0xaf0(r31)
	lis r3, double_to_int_mask_802f3228@ha
	lfd f2, double_to_int_mask_802f3228@l(r3)
	lbz r0, 0xaea(r31)
	lbz r4, 0xaec(r31)
	stw r0, 0x4c(r1)
	lbz r3, 0xb00(r31)
	stw r6, 0x48(r1)
	lwz r5, 0xaf8(r31)
	extsb r3, r3
	lfd f0, 0x48(r1)
	stw r4, 0x44(r1)
	lwz r0, 0xaf0(r31)
	fsubs f1, f0, f2
	stw r6, 0x40(r1)
	subf r4, r0, r5
	lfd f0, 0x40(r1)
	fsubs f2, f0, f2
	bl intplGetValue
	fctiwz f0, f1
	stfd f0, 0x38(r1)
	lwz r0, 0x3c(r1)
	stb r0, 0xae8(r31)
	L_g5_11:
	lwz r3, 0xaf4(r31)
	cmpwi r3, 0x0
	ble L_g5_12
	subi r0, r3, 0x1
	lis r6, 0x4330
	stw r0, 0xaf4(r31)
	lis r3, double_to_int_mask_802f3228@ha
	lfd f2, double_to_int_mask_802f3228@l(r3)
	lbz r0, 0xaeb(r31)
	lbz r4, 0xaed(r31)
	stw r0, 0x4c(r1)
	lbz r3, 0xb01(r31)
	stw r6, 0x48(r1)
	lwz r5, 0xafc(r31)
	extsb r3, r3
	lfd f0, 0x48(r1)
	stw r4, 0x44(r1)
	lwz r0, 0xaf4(r31)
	fsubs f1, f0, f2
	stw r6, 0x40(r1)
	subf r4, r0, r5
	lfd f0, 0x40(r1)
	fsubs f2, f0, f2
	bl intplGetValue
	fctiwz f0, f1
	stfd f0, 0x38(r1)
	lwz r0, 0x3c(r1)
	stb r0, 0xae9(r31)
	L_g5_12:
	lwz r3, 0xb10(r31)
	cmpwi r3, 0x0
	ble L_g5_13
	subi r0, r3, 0x1
	lis r6, 0x4330
	stw r0, 0xb10(r31)
	lis r3, double_to_int_mask_802f3228@ha
	lfd f2, double_to_int_mask_802f3228@l(r3)
	lbz r0, 0xb0a(r31)
	lbz r4, 0xb0c(r31)
	stw r0, 0x4c(r1)
	lbz r3, 0xb20(r31)
	stw r6, 0x48(r1)
	lwz r5, 0xb18(r31)
	extsb r3, r3
	lfd f0, 0x48(r1)
	stw r4, 0x44(r1)
	lwz r0, 0xb10(r31)
	fsubs f1, f0, f2
	stw r6, 0x40(r1)
	subf r4, r0, r5
	lfd f0, 0x40(r1)
	fsubs f2, f0, f2
	bl intplGetValue
	fctiwz f0, f1
	stfd f0, 0x38(r1)
	lwz r0, 0x3c(r1)
	stb r0, 0xb08(r31)
	L_g5_13:
	lwz r3, 0xb14(r31)
	cmpwi r3, 0x0
	ble L_g5_14
	subi r0, r3, 0x1
	lis r6, 0x4330
	stw r0, 0xb14(r31)
	lis r3, double_to_int_mask_802f3228@ha
	lfd f2, double_to_int_mask_802f3228@l(r3)
	lbz r0, 0xb0b(r31)
	lbz r4, 0xb0d(r31)
	stw r0, 0x4c(r1)
	lbz r3, 0xb21(r31)
	stw r6, 0x48(r1)
	lwz r5, 0xb1c(r31)
	extsb r3, r3
	lfd f0, 0x48(r1)
	stw r4, 0x44(r1)
	lwz r0, 0xb14(r31)
	fsubs f1, f0, f2
	stw r6, 0x40(r1)
	subf r4, r0, r5
	lfd f0, 0x40(r1)
	fsubs f2, f0, f2
	bl intplGetValue
	fctiwz f0, f1
	stfd f0, 0x38(r1)
	lwz r0, 0x3c(r1)
	stb r0, 0xb09(r31)
	L_g5_14:
	lmw r27, 0x5c(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void BattleStageInit(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r4, 0x0
	li r5, 0xb3c
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r3, _battleWorkPointer(r13)
	addis r31, r3, 0x1
	addi r31, r31, 0x63e0
	mr r3, r31
	bl memset
	li r4, 0x0
	li r0, 0xc
	mr r3, r4
	stw r4, 0x0(r31)
	mtctr r0
	L_g5_1:
	addi r5, r3, 0x4
	addi r3, r3, 0xe8
	add r5, r31, r5
	stw r4, 0x0(r5)
	stw r4, 0xe4(r5)
	bdnz L_g5_1
	li r4, 0x1
	li r3, 0x0
	stw r4, 0xae4(r31)
	li r0, 0x8c
	lfs f3, float_290_8041c854(r2)
	stb r3, 0xae9(r31)
	lfs f2, float_200_8041c858(r2)
	stb r3, 0xae8(r31)
	lfs f1, float_90_8041c85c(r2)
	stb r3, 0xaea(r31)
	lfs f0, float_neg50_8041c860(r2)
	stb r3, 0xaec(r31)
	stw r3, 0xaf0(r31)
	stw r3, 0xaf8(r31)
	stw r4, 0xb04(r31)
	stb r0, 0xb09(r31)
	stb r0, 0xb08(r31)
	stb r3, 0xb0a(r31)
	stb r3, 0xb0c(r31)
	stw r3, 0xb10(r31)
	stw r3, 0xb18(r31)
	stfs f3, 0xb24(r31)
	stfs f2, 0xb28(r31)
	stfs f1, 0xb2c(r31)
	lfs f1, 0xb24(r31)
	stfs f1, 0xb30(r31)
	stfs f0, 0xb34(r31)
	stfs f2, 0xb38(r31)
	bl BattleStageObjectInit
	bl batSpotInit
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm BattleStage* BattleStageGetPtr(void) {
	nofralloc
	lwz r3, _battleWorkPointer(r13)
	addis r3, r3, 0x1
	addi r3, r3, 0x63e0
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".sdata2") const u32 gap_09_8041C864_sdata2[1] = {0};
#pragma force_active reset
#pragma force_active reset
