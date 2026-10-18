/* "imgdrv" - Image Driver
 * Status: All functions added, needs Disps done, struct names, and a couple register tweaks
 *
 * Function: still not quite sure, TODO something about shadows that shadowdrv doesn't handle
 *
 * Last Update: 5/17/2021 decompile most of the file
 */
#include "driver/imgdrv.h"
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "mario/mariost.h"
#include <string.h>

extern GlobalWork* gp;

//.data

//.sbss
static ImageWork work;

//.sdata
static ImageWork* wp = &work;
#pragma explicit_zero_data on
__declspec(section ".sdata") s32 gap_07_8041034C_sdata = 0;
#pragma explicit_zero_data off

//local prototypes
static void zFill(void);
void imgDisp(CameraId camId, void* param);
void imgDisp_ProjPlane(CameraId camId, void* param);
void imgCapture_Prim(ImageEntry* entry, s32 id);
void imgCapture(CameraId camId, void* param);


void imgShadowDisp(CameraId camId, void* param);

static void zFill(void) { //almost 1:1
	static s32 depth_image[32] = {
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	CameraEntry* camera;
	f32 y0, y1, x0, x1;
	f32 zpos;
	GXTexObj obj;
	Mtx mtx;

	camera = camGetCurPtr();
	{ extern double tan(double); f32 t = (6.2831855f * camera->fovY) / 360.0f; y0 = (camera->near + camera->far) / 2.0f; y0 = y0 * (f32)tan(0.5f * t); }
	x1 = (y0 * camera->aspect);
	y1 = -y0;
	x0 = -x1;
	/*x0 = (camera->mNearZ + camera->mFarZ) * 0.5f;
	x1 = tan(((6.2831855f * camera->mFovY) / 360.0f) * 0.5f);
	y0 = (x0 * x1);
	x1 = (y0 * camera->mAspect);
	y1 = -y0;
	x0 = -x1;*/
	GXInitTexObj(&obj, depth_image, 4, 4, GX_TF_Z8, GX_REPEAT, GX_REPEAT, GX_FALSE);
	GXLoadTexObj(&obj, GX_TEXMAP0);
	GXSetNumTexGens(1);
	GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
	GXSetNumTevStages(1);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
	GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
	GXSetZTexture(GX_ZT_REPLACE, GX_TF_Z8, 0);
	GXSetNumChans(0);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
	GXSetZCompLoc(GX_TRUE);
	GXSetBlendMode(GX_BM_LOGIC, GX_BL_ONE, GX_BL_ZERO, GX_LO_COPY);
	GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
	GXSetColorUpdate(GX_FALSE);
	GXSetAlphaUpdate(GX_FALSE);
	GXSetCullMode(GX_CULL_NONE);
	GXClearVtxDesc();
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	MTXIdentity(mtx);
	GXLoadPosMtxImm(camera->view, 0);
	GXSetCurrentMtx(0);
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	zpos = -1000.0f;
	GXPosition3f32(x0, y0, zpos);
	GXTexCoord2u8(0, 0);
	GXPosition3f32(x1, y0, zpos);
	GXTexCoord2u8(1, 0);
	GXPosition3f32(x1, y1, zpos);
	GXTexCoord2u8(1, 1);
	GXPosition3f32(x0, y1, zpos);
	GXTexCoord2u8(0, 1);
	GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z8, 0);
	GXSetColorUpdate(GX_TRUE);
}

typedef struct ImgDispSh {
	u32 flags;
	u16 x, y;
	u16 left, top, right, bottom;
	s32 offId;
	s32 dstFmt;
	s32 fmt;
	GXTexObj tex;
	void* data;
	s32 alloc;
} ImgDispSh;
extern double tan(double);
extern void* DEMOGetRenderModeObj(void);
extern void sysWaitDrawSync(void);

void imgDisp(CameraId camId, void* param) {
	ImageEntry* entry = param;
	ImgDispSh* sh;
	GXTexObj* texs[3];
	void* datas[3];
	Mtx mtxs[3];
	MtxPtr mp[3];
	Mtx m3, m4, m2, m1;
	Vec v1, v2;
	CameraEntry* cam;
	int i;
	int first = -1;
	f32 fh, fw, fy, fx, scale, zoff, fl, ft, fr, fb;
	ImageEntry* e2;

	for (i = 0; i < 3; i++) {
		sh = (ImgDispSh*)entry + i;
		if (!(sh->flags & 4)) {
			texs[i] = NULL;
			datas[i] = NULL;
		} else if (sh->flags & 0x10) {
			texs[i] = NULL;
			datas[i] = NULL;
		} else {
			if (entry->flags & 4) {
				fx = sh->left;
				fy = sh->top;
				fw = sh->right;
				fh = sh->bottom;
			} else {
				fx = sh->x;
				fy = sh->y;
				fw = entry->width;
				fh = entry->height;
			}
			PSMTXTrans(m1, -((f32)sh->left - fx) / (f32)sh->right, -((f32)sh->top - fy) / (f32)sh->bottom, 0.0f);
			PSMTXScale(m2, fw / (f32)sh->right, fh / (f32)sh->bottom, 1.0f);
			PSMTXConcat(m1, m2, mtxs[i]);
			texs[i] = &sh->tex;
			datas[i] = sh->data;
		}
		if (texs[i] != NULL) {
			mp[i] = mtxs[i];
			if (first == -1) first = i;
		} else {
			mp[i] = NULL;
		}
	}
	if (first == -1) {
		entry->flags |= 0x10000000;
		return;
	}
	entry->flags &= ~0x10000000;
	animSetPaperTexMtx(mp[0], mp[1], mp[2]);
	animSetPaperTexObj(texs[0], texs[1], texs[2], datas[0], datas[1], datas[2],
	                   entry->shadows[0].field_0x10 != -1 ? 1 : 0, entry->shadows[1].field_0x10 != -1 ? 1 : 0);
	if ((u32)entry->animName != 0) {
		animPoseSetAnim(entry->poseId, (const char*)entry->animName, FALSE);
	}
	animPoseSetStartTime(entry->poseId, *(OSTime*)&entry->field_0x10C[4]);
	animPoseMain(entry->poseId);
	animPoseSetMaterialLightFlagOn(entry->poseId, 1);
	entry->loopTimes = animPoseGetLoopTimes(entry->poseId);
	if (entry->flags & 8) {
		zFill();
		scale = 1.0f;
		zoff = 0.0f;
	} else {
		f32 d, t;
		t = 3.141592f * (camGetPtr(CAMERA_3D)->fovY / 2.0f / 180.0f);
		d = 24.0f / (f32)tan(t);
		PSVECSubtract(&camGetPtr(CAMERA_3D)->cameraPos, &entry->point, &v1);
		v2 = *(Vec*)((u8*)camGetPtr(CAMERA_3D) + 0x13C);
		PSVECNormalize(&v2, &v2);
		v1.x = v1.x * v2.x;
		v1.y = v1.y * v2.y;
		v1.z = v1.z * v2.z;
		t = PSVECMag(&v1);
		scale = t / d;
		zoff = d - t;
	}
	{
		if (entry->flags & 4) {
			fl = ((ImgDispSh*)entry + first)->left; ft = ((ImgDispSh*)entry + first)->top; fr = ((ImgDispSh*)entry + first)->right; fb = ((ImgDispSh*)entry + first)->bottom;
		} else {
			fl = ((ImgDispSh*)entry + first)->x; ft = ((ImgDispSh*)entry + first)->y; fr = entry->width; fb = entry->height;
		}
	}
	PSMTXTrans(m3, 64.0f * ((entry->offsetX + fl) / (f32)((GXRenderModeObj*)DEMOGetRenderModeObj())->fbWidth), 48.0f * (-(entry->offsetY + ft) / (f32)((GXRenderModeObj*)DEMOGetRenderModeObj())->efbHeight), zoff);
	PSMTXTrans(m4, -32.0f, 24.0f, 0.0f);
	PSMTXConcat(m3, m4, m3);
	PSMTXScale(m4, fr / (f32)((GXRenderModeObj*)DEMOGetRenderModeObj())->fbWidth, fb / (f32)((GXRenderModeObj*)DEMOGetRenderModeObj())->efbHeight, fr / (f32)((GXRenderModeObj*)DEMOGetRenderModeObj())->fbWidth);
	PSMTXConcat(m3, m4, m3);
	PSMTXTrans(m4, 32.0f, -24.0f, 0.0f);
	PSMTXConcat(m3, m4, m3);
	PSMTXConcat(entry->mtx, m3, m3);
	animPoseDrawMtx(entry->poseId, m3, 1, 0.0f, scale);
	animPoseDrawMtx(entry->poseId, m3, 2, 0.0f, scale);
	animPoseDrawMtx(entry->poseId, m3, 3, 0.0f, scale);
	animSetPaperTexMtx(NULL, NULL, NULL);
	e2 = wp->entries;
	for (i = 0; i < wp->count; i++, e2++) {
		if ((e2->flags & 1) && e2->poseId != -1 && !(e2->flags & 2) && strcmp(e2->name, entry->name) != 0 &&
		    strcmp(((char*)animPoseGetAnimBaseDataPtr(e2->poseId) + 4), ((char*)animPoseGetAnimBaseDataPtr(entry->poseId) + 4)) == 0)
			break;
	}
	if (i < wp->count) sysWaitDrawSync();
}

void mapSetMaterialLight(s32 flags, Vec position);
void mapSetMaterialLastStageBlend(s32 flags, GXColor color1, GXColor color2);
void mapSetMaterialTev(s32 texCount, s32 drawMode, s32 flags, Mtx mtx);

void imgDisp_ProjPlane(CameraId camId, void* param) {
	ImageEntry* entry = param;
	static const Vec lightPos = {0.0f, 0.0f, 0.0f};
	static const GXColor color1 = {0xFF, 0xFF, 0xFF, 0xFF};
	static const GXColor color2 = {0xFF, 0xFF, 0xFF, 0xFF};
	Mtx mtx;
	Mtx mtx2;
	Vec pos;
	s32 flags;

	switch (entry->shadowId) {
		case 0:
			return;
		case 1:
			flags = 0x20000;
			PSMTXIdentity(mtx);
			GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
			break;
		case 2:
			flags = 0x40000;
			PSMTXTrans(mtx, 0.0f, 0.0f, entry->offsetZ);
			GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
			break;
	}
	pos = lightPos;
	PSMTXMultVec(mtx, &pos, &pos);
	mapSetMaterialLight(0, pos);
	mapSetMaterialLastStageBlend(flags, color1, color2);
	mapSetMaterialTev(0, 0, flags, mtx);
	PSMTXConcat(camGetCurPtr()->view, mtx, mtx2);
	GXLoadPosMtxImm(mtx2, GX_PNMTX0);
	GXSetCurrentMtx(GX_PNMTX0);
	GXSetAlphaUpdate(GX_TRUE);
	GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
	GXSetZCompLoc(GX_TRUE);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetCullMode(GX_CULL_NONE);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	GXPosition3f32(-32.0f, 24.0f, 0.0f);
	GXColor4u8(0, 0, 0, 0);
	GXPosition3f32(32.0f, 24.0f, 0.0f);
	GXColor4u8(0, 0, 0, 0);
	GXPosition3f32(32.0f, -24.0f, 0.0f);
	GXColor4u8(0, 0, 0, 0);
	GXPosition3f32(-32.0f, -24.0f, 0.0f);
	GXColor4u8(0, 0, 0, 0);
}

#pragma push
#pragma dont_inline on
typedef struct ImgShd {
	u32 flags;
	u16 x, y;
	u16 left, top, right, bottom;
	s32 offId;
	s32 dstFmt;
	s32 fmt;
	GXTexObj tex;
	smartEntry* data;
	s32 alloc;
} ImgShd;
extern void offscreenGetTexObj(s32 id, GXTexObj** texObj, smartEntry** texBuf);
extern BOOL offscreenGetBoundingBox(s32 id, u16* left, u16* top, u16* right, u16* bottom);

static inline void imgCaptureCopy(ImgShd* sh, ImageEntry* entry) {
	s32 fmt, dstFmt, alloc;
	u16 h, w;
	u32 size;
	smartEntry* data;
	sh->left = sh->x;
	sh->top = sh->y;
	sh->right = entry->width;
	sh->bottom = entry->height;
	h = sh->bottom;
	w = sh->right;
	fmt = sh->fmt;
	dstFmt = sh->dstFmt;
	alloc = sh->alloc;
	GXSetTexCopySrc(sh->left, sh->top, w, h);
	GXSetTexCopyDst(w, h, dstFmt, 0);
	size = GXGetTexBufferSize(w, h, fmt, 0, 0);
	if (alloc == 1) data = smartAlloc(size, 1);
	else if (alloc == 2) data = smartAlloc(size, 0);
	else data = smartAlloc(size, 3);
	GXSetZMode(1, 3, 1);
	GXCopyTex(data->address, 0);
	GXPixModeSync();
	GXInitTexObj(&sh->tex, data->address, w, h, fmt, 0, 0, 0);
	GXInitTexObjLOD(&sh->tex, 0, 0, 0.0f, 0.0f, 0.0f, 0, 0, 0);
	sh->data = data;
}

void imgCapture_Prim(ImageEntry* entry, s32 id) {
	ImgShd* sh = (ImgShd*)&entry->shadows[id];
	s32 offId;
	u16 w, h;
	s32 alloc, fmt, dstFmt;
	u32 size;
	smartEntry* data;
	GXTexObj* obj;
	smartEntry* buf;
	if (!(sh->flags & 4)) return;
	offId = sh->offId;
	sh->flags |= 0x10;
	if (offId != -1) {
		if (sh->alloc) {
			if (sh->flags & 0x100) {
				offscreenGetTexObj(offId, &obj, &buf);
				if (obj) {
					w = GXGetTexObjWidth(obj);
					h = GXGetTexObjHeight(obj);
					fmt = GXGetTexObjFmt(obj);
					size = GXGetTexBufferSize(w, h, fmt, 0, 0);
					if (sh->alloc == 1) {
						sh->data = smartAlloc(size, 1);
					} else if (sh->alloc == 2) {
						sh->data = smartAlloc(size, 0);
					}
					memcpy(sh->data->address, buf->address, size);
					DCFlushRange(sh->data->address, size);
					GXInitTexObj(&sh->tex, sh->data->address, w, h, fmt, 0, 0, 0);
					GXInitTexObjLOD(&sh->tex, 0, 0, 0.0f, 0.0f, 0.0f, 0, 0, 0);
					offscreenGetBoundingBox(offId, &sh->left, &sh->top, &sh->right, &sh->bottom);
					sh->right -= sh->left;
					sh->bottom -= sh->top;
					sh->flags &= ~0x100;
				}
			}
			if (!(sh->flags & 0x100)) sh->flags &= ~0x10;
		} else {
			GXTexObj* o2; smartEntry* b2;
			offscreenGetTexObj(offId, &o2, &b2);
			if (o2) {
				sh->tex = *o2;
				sh->data = b2;
				offscreenGetBoundingBox(offId, &sh->left, &sh->top, &sh->right, &sh->bottom);
				sh->right -= sh->left;
				sh->bottom -= sh->top;
				sh->flags &= ~0x10;
			}
		}
	} else if (sh->alloc) {
		if (sh->flags & 0x100) {
			imgCaptureCopy(sh, entry);
			sh->flags &= ~0x100;
		}
		if (!(sh->flags & 0x100)) sh->flags &= ~0x10;
	} else {
		imgCaptureCopy(sh, entry);
		sh->flags &= ~0x10;
	}
}

#pragma pop
void imgCapture(CameraId camId, void* param) {
	s32 type = gp->inBattle != 0;
	int i, count;
	ImageEntry* entry;

	i = 0;
	count = wp->count;
	for (entry = wp->entries; i < count; i++, entry++) {
		if (entry->flags & 1 && entry->poseId != -1) {
			if (entry->type == 2 || entry->type == type) {
				if (entry->dispCamId == camId) {
					int j;
					for (j = 0; j < 3; j++) {
						imgCapture_Prim(entry, j);
					}
				}
			}
		}
	}
}

void imgInit(void) { //1:1
	wp->count = 10;
	wp->entries = __memAlloc(HEAP_DEFAULT, wp->count * sizeof(ImageEntry));
	memset(wp->entries, 0, wp->count * sizeof(ImageEntry));
}

void imgAutoRelease(s32 type) {
	int i, count;
	ImageEntry* entry;

	i = 0;
	count = wp->count;
	for (entry = wp->entries; i < count; i++, entry++) {
		if (entry->flags & 1 && entry->type == type) {
			imgRelease(entry, type);
		}
	}
}

s32 imgEntry(const char* name, s32 type) { //1:1, needs variable names
	int i, count;
	ImageEntry* entry;

	//check if already created
	for (i = 0, count = wp->count, entry = wp->entries; i < count; i++, entry++) {
		if (entry->flags & 1 && entry->type == type) {
			if (!strcmp(entry->name, name)) break;
		}
	}

	//find new slot
	for (i = 0, entry = wp->entries; i < count; i++, entry++) {
		if (!(entry->flags & 1)) break;
	}

	entry->flags = 9;
	entry->type = type;
	strcpy(entry->name, name);
	entry->poseId = -1;
	entry->animName = 0;
	entry->width = 0;
	entry->height = 0;
	entry->offsetX = 0.0f;
	entry->offsetY = 0.0f;
	entry->order = 0.0f;
	entry->loopTimes = 0.0f;
	entry->shadowId = 0;
	entry->offsetZ = 0.0f;
	MTXIdentity(entry->mtx);
	entry->camId = CAMERA_3D_IMAGE;
	entry->dispCamId = 4;

	entry->shadows[0].flags = 0;
	entry->shadows[0].x = 0;
	entry->shadows[0].y = 0;
	entry->shadows[0].field_0x10 = -1;
	entry->shadows[0].field_0x14 = 6;
	entry->shadows[0].field_0x18 = 6;
	entry->shadows[0].field_0x40 = 0;

	entry->shadows[1].flags = 0;
	entry->shadows[1].x = 0;
	entry->shadows[1].y = 0;
	entry->shadows[1].field_0x10 = -1;
	entry->shadows[1].field_0x14 = 6;
	entry->shadows[1].field_0x18 = 6;
	entry->shadows[1].field_0x40 = 0;

	entry->shadows[2].flags = 0;
	entry->shadows[2].x = 0;
	entry->shadows[2].y = 0;
	entry->shadows[2].field_0x10 = -1;
	entry->shadows[2].field_0x14 = 6;
	entry->shadows[2].field_0x18 = 6;
	entry->shadows[2].field_0x40 = 0;
	entry->shadows[2].field_0x14 = 39;
	entry->shadows[2].field_0x18 = 1;

	return i;
}

void imgMain(void) { //1:1
	s32 type = gp->inBattle != 0;
	int shadow, i, count;
	ImageEntry* entry;

	i = 0;
	count = wp->count;
	for (entry = wp->entries; i < count; i++, entry++) {
		if (entry->flags & 1 && entry->poseId != -1 && !(entry->flags & 2)) {
			if (entry->type == 2 || entry->type == type) {
				for (shadow = 0; shadow < 3; shadow++) {
					if (entry->shadows[shadow].flags & 4) break;
				}
				if (shadow != 3) {
					dispEntry(entry->camId, entry->order, 1, imgDisp, entry);
					switch (entry->shadowId) {
						case 0:
							animPoseSetMaterialFlagOff(entry->poseId, 0x10000);
							break;
						case 1:
							dispEntry(CAMERA_SHADOW, 0.0f, 1, imgShadowDisp, entry);
							dispEntry(CAMERA_3D_IMAGE, 0.0f, 5, imgDisp_ProjPlane, entry);
							break;
						case 2:
							animPoseSetMaterialFlagOn(entry->poseId, 0x10000);
							dispEntry(CAMERA_SHADOW, 0.0f, 6, imgShadowDisp, entry);
							dispEntry(CAMERA_3D_IMAGE, 0.0f, 5, imgDisp_ProjPlane, entry);
							break;
					}
				}
			}
		}
	}

	for (i = 0; i < 13; i++) {
		dispEntry(i, 0.0f, 7, imgCapture, NULL);
	}
}

ImageEntry* imgNameToPtr(const char* name, s32 type) { //1:1
	int i, count;
	ImageEntry* entry;

	i = 0;
	count = wp->count;
	for (entry = wp->entries; i < count; i++, entry++) {
		if (entry->flags & 1 && (entry->type == 2 || entry->type == type)) {
			if (!strcmp(entry->name, name)) break;
		}
	}
	return entry;
}

void imgFreeCapture(ImageEntry* entry, s32 shadowId) { //1:1, needs enums
	ImageShadow* shadow = &entry->shadows[shadowId];
	if (shadow->flags & 4) {
		shadow->flags &= ~0x10;
		if (shadow->flags & 0x100) {
			shadow->flags = 0;
		}
		else if (!shadow->field_0x40) {
			shadow->flags = 0;
		}
		else {
			shadow->flags = 0;
			smartFree(shadow->data);
		}
	}
}

void imgSetVirtualPoint(ImageEntry* entry, const Vec* point) { //1:1
	entry->flags &= ~8;
	entry->point = *point;
}

void imgClearVirtualPoint(ImageEntry* entry) { //1:1
	entry->flags |= 8;
}

void imgRelease(ImageEntry* entry, s32 type) { //1:1 after inlining
	int i;

	for (i = 0; i < 3; i++) {
		imgFreeCapture(entry, i); //TODO: double check this inlines correctly
	}
	entry->flags = 0;
	memset(entry, 0, sizeof(ImageEntry));
}

void imgSetShadow(ImageEntry* entry, s32 shadowId) { //1:1
	entry->shadowId = shadowId;
}

extern void shadowProjShadowDrawCountUp(void);
extern void shadowDepthShadowDrawCountUp(void);
extern void* DEMOGetRenderModeObj(void);
typedef struct { u16 a, b, c, d; } ImgRect;

void imgShadowDisp(CameraId camId, void* param) {
	ImageShadow* sh;
	ImageEntry* entry = param;
	GXTexObj* objs[3];
	void* datas[3];
	Mtx mtxs[3];
	Mtx* mp[3];
	int first = -1;
	int i;
	f32 y0, x0, h, w;
	f32 sx, sy, ox, oy;
	f32 s0, s1;
	Mtx t, m2, m1, m;

	for (i = 0; i < 3; i++) {
		sh = &entry->shadows[i];
		if (!(sh->flags & 4)) {
			objs[i] = NULL;
			datas[i] = NULL;
		} else if (sh->flags & 0x10) {
			objs[i] = NULL;
			datas[i] = NULL;
		} else {
			ImgRect* r = (ImgRect*)sh->field_0x8;
			if (entry->flags & 4) {
				x0 = r->a;
				y0 = r->b;
				w = r->c;
				h = r->d;
			} else {
				x0 = sh->x;
				y0 = sh->y;
				w = entry->width;
				h = entry->height;
			}
			r = (ImgRect*)sh->field_0x8;
			PSMTXTrans(m, -((f32)r->a - x0) / (f32)r->c, -((f32)r->b - y0) / (f32)r->d, 0.0f);
			PSMTXScale(m1, w / (f32)r->c, h / (f32)r->d, 1.0f);
			PSMTXConcat(m, m1, mtxs[i]);
			objs[i] = (GXTexObj*)((u8*)sh + 0x1C);
			datas[i] = sh->data;
		}
		if (objs[i] != NULL) {
			mp[i] = &mtxs[i];
			if (first == -1) first = i;
		} else {
			mp[i] = NULL;
		}
	}
	if (first == -1) {
		entry->flags |= 0x10000000;
		return;
	}
	entry->flags &= ~0x10000000;
	animSetPaperTexMtx((void*)mp[0], (void*)mp[1], (void*)mp[2]);
	animSetPaperTexObj(objs[0], objs[1], objs[2], datas[0], datas[1], datas[2],
	                   entry->shadows[0].field_0x10 != -1 ? 1 : 0, entry->shadows[1].field_0x10 != -1 ? 1 : 0);
	if ((u32)entry->animName != 0) animPoseSetAnim(entry->poseId, (const char*)entry->animName, 0);
	animPoseSetStartTime(entry->poseId, *(OSTime*)&entry->field_0x10C[4]);
	animPoseMain(entry->poseId);
	animPoseSetMaterialLightFlagOn(entry->poseId, 1);
	entry->loopTimes = animPoseGetLoopTimes(entry->poseId);
	{
		f32 x0, y0, w, h; f32 sc, z;
		typedef struct { u16 p, q, w, h; } RM;
		RM* rm;
		if (entry->flags & 8) {
			sc = 1.0f; z = 0.0f;
		} else {
			sc = 1.0f; z = 0.0f;
		}
		if (entry->flags & 4) {
			x0 = ((u16*)&entry->shadows[first])[4]; y0 = ((u16*)&entry->shadows[first])[5]; w = ((u16*)&entry->shadows[first])[6]; h = ((u16*)&entry->shadows[first])[7];
		} else {
			x0 = entry->shadows[first].x;
			y0 = entry->shadows[first].y;
			w = entry->width; h = entry->height;
		}
		PSMTXTrans(t, 64.0f * ((entry->offsetX + x0) / (f32)((RM*)DEMOGetRenderModeObj())->w), 48.0f * (-(entry->offsetY + y0) / (f32)((RM*)DEMOGetRenderModeObj())->h), z);
		PSMTXTrans(m2, -32.0f, 24.0f, 0.0f);
		PSMTXConcat(t, m2, t);
		PSMTXScale(m2, w / (f32)((RM*)DEMOGetRenderModeObj())->w, h / (f32)((RM*)DEMOGetRenderModeObj())->h, w / (f32)((RM*)DEMOGetRenderModeObj())->w);
		PSMTXConcat(t, m2, t);
		PSMTXTrans(m2, 32.0f, -24.0f, 0.0f);
		PSMTXConcat(t, m2, t);
		animPoseDrawMtx(entry->poseId, t, 1, 0.0f, sc);
		animPoseDrawMtx(entry->poseId, t, 2, 0.0f, sc);
	}
	switch (entry->shadowId) {
	case 1: shadowProjShadowDrawCountUp(); break;
	case 2: shadowDepthShadowDrawCountUp(); break;
	}
}
