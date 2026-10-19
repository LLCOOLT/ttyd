#include "driver/mapdrv.h"
#include "driver/arcdrv.h"
#include "manager/dvdmgr.h"
#include "manager/arammgr.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#include "texPalette.h"
#include "driver/offscreendrv.h"
#include "driver/camdrv.h"
#include "driver/lightdrv.h"
#include "driver/shadowdrv.h"
double sin(double);
double cos(double);
#ifdef NONMATCHING
static inline f32 sinf(f32 x) { return sin(x); }
#endif
#include <string.h>
#ifndef NONMATCHING
#include "sdk/texPalette.h"
extern void* jumptable_80303414[];
#define EXT_LIT(sym, val) (sym)
__declspec(section ".rodata") extern const f32 vec3_802c16d8[3];
__declspec(section ".rodata") extern const f32 vec3_802c16e4[3];
__declspec(section ".rodata") extern const u32 culling_678[4];
__declspec(section ".rodata") extern const f32 vec3_802c1700[3];
__declspec(section ".rodata") extern const f32 vec3_802c170c[3];
__declspec(section ".rodata") extern const f32 vec3_802c1718[3];
__declspec(section ".rodata") extern const f32 vec3_802c1724[3];
__declspec(section ".rodata") extern const f32 vec3_802c1730[3];
__declspec(section ".rodata") extern const f32 vec3_802c173c[3];
__declspec(section ".rodata") extern const f32 vec3_802c1748[3];
__declspec(section ".rodata") extern const f32 vec3_802c1754[3];
__declspec(section ".rodata") extern const GXTexMtx texmtx_tbl[10];
__declspec(section ".rodata") extern const s32 texfmt_tbl[11];
__declspec(section ".rodata") extern const s32 texwrap_tbl[3];
__declspec(section ".rodata") extern const s32 palfmt_tbl[2];
__declspec(section ".rodata") extern const GXLightID lightid_tbl[8];
__declspec(section ".rodata") extern const f32 vec3_802c17f8[3];
__declspec(section ".rodata") extern const f32 vec3_802c1804[3];
__declspec(section ".rodata") extern const f32 vec3_802c1810[3];
__declspec(section ".rodata") extern const f32 vec3_802c181c[3];
__declspec(section ".rodata") extern const f32 vec3_802c1828[3];
__declspec(section ".rodata") extern const GXVtxAttrFmtList attr_fmt[12];
__declspec(section ".rodata") extern const f32 vec3_802c18f4[3];
__declspec(section ".rodata") extern const f32 vec3_802c1900[3];
__declspec(section ".rodata") extern const char str_802C190C[12];
__declspec(section ".rodata") extern const char str_802C1918[12];
__declspec(section ".rodata") extern const char str_802C1924[8];
__declspec(section ".rodata") extern const char str_802C192C[8];
__declspec(section ".rodata") extern const char str_802C1934[20];
__declspec(section ".rodata") extern const char str_802C1948[28];
__declspec(section ".rodata") extern const char str_802C1964[16];
__declspec(section ".rodata") extern const char str_802C1974[12];
__declspec(section ".rodata") extern const f64 double_0p5_802c1980;
__declspec(section ".rodata") extern const f64 double_3_802c1988;
__declspec(section ".rodata") extern const f64 double_0_802c1990;
__declspec(section ".rodata") extern const f64 double_to_int_802c1998;
__declspec(section ".rodata") extern const f64 double_to_int_mask_802c19a0;
__declspec(section ".rodata") extern const char str_802C19A8[12];
__declspec(section ".rodata") extern const char str_802C19B4[12];
__declspec(section ".rodata") extern const char str_802C19C0[16];
__declspec(section ".rodata") extern const char str_802C19D0[12];
__declspec(section ".rodata") extern const char str_802C19DC[12];
__declspec(section ".rodata") extern const char str_802C19E8[20];
__declspec(section ".rodata") extern const char str_802C19FC[12];
__declspec(section ".rodata") extern const char str_802C1A08[16];
__declspec(section ".rodata") extern const char str_802C1A18[12];
__declspec(section ".rodata") extern const char str_802C1A24[20];
__declspec(section ".rodata") extern const char str_802C1A38[12];
__declspec(section ".rodata") extern const char str_802C1A44[12];
__declspec(section ".rodata") extern const char str_802C1A50[12];
__declspec(section ".rodata") extern const char str_802C1A5C[52];
__declspec(section ".sdata2") extern const u32 dat_80419800;
__declspec(section ".sdata2") extern const u32 dat_80419804;
__declspec(section ".sdata2") extern const u32 dat_80419808;
__declspec(section ".sdata2") extern const u32 dat_8041980c;
__declspec(section ".sdata2") extern const u32 dat_80419810;
__declspec(section ".sdata2") extern const u32 dat_80419814;
__declspec(section ".sdata2") extern const u32 dat_80419818;
__declspec(section ".sdata2") extern const u32 dat_8041981c;
__declspec(section ".sdata2") extern const u32 dat_80419820;
__declspec(section ".sdata2") extern const u32 dat_80419824;
__declspec(section ".sdata2") extern const u32 dat_80419828;
__declspec(section ".sdata2") extern const u32 dat_8041982c;
__declspec(section ".sdata2") extern const u32 dat_80419830;
__declspec(section ".sdata2") extern const u32 dat_80419834;
__declspec(section ".sdata2") extern const u32 dat_80419838;
__declspec(section ".sdata2") extern const u32 dat_8041983c;
__declspec(section ".sdata2") extern const u32 dat_80419840;
__declspec(section ".sdata2") extern const u32 dat_80419844;
__declspec(section ".sdata2") extern const char str_80419848[4];
__declspec(section ".sdata2") extern const f32 float_3_8041984c;
__declspec(section ".sdata2") extern const f32 float_0_80419850;
__declspec(section ".sdata2") extern const f32 float_0p5_80419854;
__declspec(section ".sdata2") extern const f32 float_2_80419858;
__declspec(section ".sdata2") extern const f32 float_0p0001_8041985c;
__declspec(section ".sdata2") extern const f32 float_1_80419860;
__declspec(section ".sdata2") extern const f32 float_10_80419864;
__declspec(section ".sdata2") extern const f32 float_deg2rad_80419868;
__declspec(section ".sdata2") extern const char str_8041986C[4];
__declspec(section ".sdata2") extern const f32 float_neg1p0486E06_80419870;
__declspec(section ".sdata2") extern const f32 float_1000_80419874;
__declspec(section ".sdata2") extern const f32 float_6p2832_80419878;
__declspec(section ".sdata2") extern const f32 float_360_8041987c;
__declspec(section ".sdata2") extern const f32 float_127_80419880;
__declspec(section ".sdata2") extern const f32 float_100_80419884;
__declspec(section ".sdata2") extern const f32 float_neg100_80419888;
__declspec(section ".sdata2") extern const f32 float_1p5708_8041988c;
__declspec(section ".sdata2") extern const f32 float_20_80419890;
__declspec(section ".sdata2") extern const f32 float_64_80419894;
__declspec(section ".sdata2") extern const f32 float_30_80419898;
__declspec(section ".sdata2") extern const f32 float_128_8041989c;
__declspec(section ".sdata2") extern const f32 float_neg2_804198a0;
__declspec(section ".sdata2") extern const f32 float_50_804198a4;
__declspec(section ".sdata2") extern const f32 float_neg1_804198a8;
__declspec(section ".sdata2") extern const f32 float_5000_804198ac;
__declspec(section ".sdata2") extern const f32 float_10000_804198b0;
__declspec(section ".sdata2") extern const f32 float_0p01_804198b4;
__declspec(section ".sdata2") extern const f32 float_1Eneg08_804198b8;
__declspec(section ".sdata2") extern const char str_804198BC[4];
__declspec(section ".sdata2") extern const char str_804198C0[8];
__declspec(section ".sdata2") extern const f32 float_255_804198c8;
__declspec(section ".sdata2") extern const f32 float_0_804198cc;
__declspec(section ".sdata2") extern const char str_804198D0[8];
__declspec(section ".sdata2") extern const f32 float_20000_804198d8;
__declspec(section ".sdata2") extern const u32 gap_09_804198DC_sdata2;
#endif
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)
#pragma force_active on
#pragma force_active on
__declspec(section ".sdata") u32 gap_08_804184BC_sbss[1];
#pragma force_active reset
void envReInit(void);

__declspec(section ".sdata2") const u32 gap_10_80422F94_sbss2;
__declspec(section ".sdata2") const u32 unk_80422f90;
__declspec(section ".sdata2") const u32 unk_80422f8c;
__declspec(section ".sdata2") const u32 unk_80422f88;
__declspec(section ".sdata2") const u32 unk_80422f84;
__declspec(section ".sdata2") const u32 unk_80422f80;
void mapSetMaterialTev(s32 texCount, s32 drawMode, s32 flags, Mtx mtx);
void mapBuildTexture(MapObject* obj, TEXPalette* texture, void* table);
int __cvt_dbl_usll();
int __cvt_ull_flt();
int __div2i();
void _mapDispMapGrp(CameraId cam, MapObject* obj);
void _mapDispMapGrp_NoMaterial(CameraId cam, MapObject* obj);
void _mapDispMapObj(CameraId cam, MapObject *obj);
void _mapDispMapObj_NoMaterial(CameraId cam, MapObject* obj);
MapObject* _mapEnt(MapFileJoint* joint, MapObject* parent, Mtx mtx, s32 index);
void _mapLoad(MapWork* wp, BOOL group, const char* map);
void _setOffScrnId(MapObject* obj, s32 id, BOOL doNext);
void makeDisplayList(BOOL group);
MapObject* mapEntry(MapFileJoint* joint, Mtx mtx, s32 index);
MapObject* mapEntrySub(MapFileJoint* joint, MapObject* parent, Mtx mtx, BOOL isRoot, s32 index);
void mapFlgOff(MapObject* obj, u32 flags, BOOL doNext);
void mapFlgOn(MapObject* obj, u32 flags, BOOL doNext);
void mapGetBoundingBox(Vec* min, Vec* max);
void mapGetJointsSub(MapFileJoint* joint, s32* numJoints);
void mapGrpFlagOff(const char* name, u32 flags);
void mapGrpFlagOn(const char* name, u32 flags);
void mapGrpSetColor(const char* name, GXColor color);
void mapObjGetPosSub(MapObject* obj, Vec* sum, s32* count, BOOL doNext);
void mapReCalcMatrix(MapObject* obj, Mtx mtx, BOOL force);
MapFileJoint* mapSearchDmdJoint(MapFileJoint* joint, const char* name);
MapFileJoint* mapSearchDmdJointSub(MapFileJoint* joint, const char* name);
MapFileJoint* mapSearchDmdJointSub2(MapFileJoint* joint, const char* name, const char* prefix);
s32 mapSetLight(MapObject* obj, LightEntry** lights);
void mapSetMaterial(MapObject* obj, void* material);
void mapSetPolygon(MapObject* obj, MapFileMesh* mesh);
void mapSetPolygonVtxDesc(MapObject* obj, MapFileMesh* mesh);
void setColor(MapObject* obj, GXColor color, BOOL doNext);
int strcat();
__declspec(section ".sdata") f32 g5_scrl_uv_s1622[4] = {0.0f, 0.0f, 0.0f, 0.0f};
void mapDispMapGrp(CameraId cam, MapObject* obj);
void mapDispMapGrp_bbox(CameraId cam, MapObject* obj);
void mapDispMapGrp_off(CameraId cam, MapObject* obj);
void mapDispMapObj(CameraId cam, MapObject* obj);
void mapDispMapObj_bbox(CameraId cam, MapObject* obj);
void mapDispMapObj_off(CameraId cam, MapObject* obj);
#ifdef NONMATCHING
asm void bmapUnLoad(void);
#endif
#ifndef NONMATCHING
void bmapUnLoad(void);
#endif
extern f32 queen_uv[]; //gxsub.c
extern GlobalWork* gp;
// FAKE: the last .sdata2 constants (0xCC-0xDB) are named objects defined at the end of the file so the
// bmapUnLoad asm can address "" and they keep the original pool order (explicit data lands after the pool)
extern const char mapEmptyStr[4];
extern const char mapPathFmt[8];
extern const f32 mapF20000;
extern int sprintf(char* str, const char* format, ...);

#define TWO_PI 6.28318530717958647692528676655900576839433879875021f

//.bss
MapError error_data[32];

//.sbss
GXColor paper_ambient;
GXColor paperCraft_ambient;
GXTexObj projTexObj;
void* projTexImgRef;
Mtx projMtx;
BOOL __mapdrv_make_dl;
BOOL unk_80418458;
s32 error_count;
BOOL error_flag;
MapObject* current_mp;
BOOL mapClipOffFlag;
s32 activeGroup;
MapWork* mapWork; //allocates two entries

typedef struct MapAnimHeader {
	const char* name; // 0x0
	u8 field_0x4[0x8 - 0x4]; // 0x4
	f32 length; // 0x8
} MapAnimHeader;

typedef struct MapAnim {
	u16 flags; // 0x0
	u8 field_0x2[0x8 - 0x2]; // 0x2
	OSTime startTime; // 0x8
	f32 time; // 0x10
	f32 rate; // 0x14
	MapAnimHeader* anim; // 0x18
	u8 field_0x1C[0x20 - 0x1C]; // 0x1C
} MapAnim;

#define MAPENT_FIELD(entry, type, off) (*(type*)((u8*)(entry) + (off)))

typedef struct MapJointDrawModeEx {
	u8 field_0x0[0x2 - 0x0]; // 0x0
	u8 flags;                 // 0x2
	u8 field_0x3;             // 0x3
	u32 lightMask;            // 0x4
} MapJointDrawModeEx;


LightEntry* lightGetPaper(void);
LightEntry* lightGetPaperCraft(void);
LightEntry* lightGetCharaAmbient(void);
void mapGetJointsSub(MapFileJoint* joint, s32* numJoints);
s32 lightCheckCharaLight(void);
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)

//.sdata
#ifdef NONMATCHING
s32 fog_type[5] = {2, 4, 5, 6, 7};
#endif
#ifndef NONMATCHING
__declspec(section ".sdata") s32 fog_type[5] = {2, 4, 5, 6, 7};
#endif

//local prototypes
void mapGetJointsSub(MapFileJoint* joint, s32* numJoints);
void mapGetBoundingBox(Vec* min, Vec* max);
void mapGetBoundingBox(Vec* min, Vec* max);
void mapBuildTexture(MapObject* obj, TEXPalette* texture, void* table);
void mapBuildTexture(MapObject* obj, TEXPalette* texture, void* table);
MapObject* _mapEnt(MapFileJoint* joint, MapObject* parent, Mtx mtx, s32 index);
MapObject* _mapEnt(MapFileJoint* joint, MapObject* parent, Mtx mtx, s32 index);
MapObject* mapEntrySub(MapFileJoint* joint, MapObject* parent, Mtx mtx, BOOL isRoot, s32 index);
MapObject* mapEntrySub(MapFileJoint* joint, MapObject* parent, Mtx mtx, BOOL isRoot, s32 index);
MapObject* mapEntry(MapFileJoint* joint, Mtx mtx, s32 index);
MapObject* mapEntry(MapFileJoint* joint, Mtx mtx, s32 index);
void _mapLoad(MapWork* wp, BOOL group, const char* map);
void makeDisplayList(BOOL group);
void makeDisplayList(BOOL group);
//anim functions?
void _mapLoad(MapWork* wp, BOOL group, const char* map);

#ifdef NONMATCHING
void mapErrorEntry(s32 arg0, const char* arg1) { //1:1
	MapError* error = error_data;
#endif
#ifndef NONMATCHING
void mapErrorEntry(s32 arg0, const char* arg1);
#endif

#ifdef NONMATCHING
	error += error_count;
	error->field_0x20 = arg0;
	strncpy(error->field_0x0, arg1, sizeof(error->field_0x0) - 1);
	error_flag = TRUE;
	error_count++;
	error_count %= 32;
}
#endif
#ifndef NONMATCHING
void C_MTXLightOrtho(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 scaleS, f32 scaleT, f32 transS, f32 transT);
void C_MTXLookAt(Mtx m, const Point3d* camPos, const Vec* camUp, const Point3d* target);
void GXCallDisplayList(void* list, u32 nbytes);
void GXClearBoundingBox(void);
void GXGetCullMode(GXCullMode* mode);
void GXGetProjectionv(f32* ptr);
void GXInitLightAttn(GXLightObj* lt_obj, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);
void GXInitLightColor(GXLightObj* lt_obj, GXColor color);
void GXInitLightDir(GXLightObj* lt_obj, f32 nx, f32 ny, f32 nz);
void GXInitLightDistAttn(GXLightObj* lt_obj, f32 ref_dist, f32 ref_br, GXDistAttnFn dist_func);
void GXInitLightPos(GXLightObj* lt_obj, f32 x, f32 y, f32 z);
void GXInitLightSpot(GXLightObj* lt_obj, f32 cutoff, GXSpotFn spot_func);
void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXTexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
    f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp,
    GXBool do_edge_lod, GXAnisotropy max_aniso);
void GXInvalidateVtxCache(void);
void GXLoadLightObjImm(const GXLightObj* lt_obj, GXLightID light);
void GXLoadNrmMtxImm(const f32 mtx[3][4], u32 id);
void GXLoadPosMtxImm(const f32 mtx[3][4], u32 id);
void GXLoadTexMtxImm(const f32 mtx[][4], u32 id, GXTexMtxType type);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
void GXReadBoundingBox(u16* left, u16* top, u16* right, u16* bottom);
void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1);
void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op);
void GXSetChanAmbColor(GXChannelID chan, GXColor amb_color);
void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src, u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn);
void GXSetChanMatColor(GXChannelID chan, GXColor mat_color);
void GXSetCullMode(GXCullMode mode);
void GXSetCurrentMtx(u32 id);
void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color);
void GXSetNumChans(u8 nChans);
void GXSetNumIndStages(u8 nIndStages);
void GXSetNumTevStages(u8 nStages);
void GXSetNumTexGens(u8 nTexGens);
void GXSetProjection(const f32 mtx[4][4], GXProjectionType type);
void GXSetProjectionv(const f32* ptr);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevColor(GXTevRegID id, GXColor color);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevDirect(GXTevStageID tev_stage);
void GXSetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel sel);
void GXSetTevKColor(GXTevKColorID id, GXColor color);
void GXSetTevKColorSel(GXTevStageID stage, GXTevKColorSel sel);
void GXSetTevOp(GXTevStageID id, GXTevMode mode);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras_sel, GXTevSwapSel tex_sel);
void GXSetTevSwapModeTable(GXTevSwapSel table, GXTevColorChan red, GXTevColorChan green, GXTevColorChan blue, GXTevColorChan alpha);
void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx);
void GXSetZCompLoc(GXBool before_tex);
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
extern void OSPanic(const char* file, int line, const char* msg, ...);
void PSMTX44MultVec(const Mtx44 m, const Vec* src, Vec* dst);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXCopy(const Mtx src, Mtx dst);
void PSMTXIdentity(Mtx m);
u32 PSMTXInvXpose(const Mtx src, Mtx invX);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXMultVecSR(const Mtx m, const Vec* src, Vec* dst);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void PSVECAdd(const Vec* a, const Vec* b, Vec* ab);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
f32 PSVECSquareDistance(const Vec* a, const Vec* b);
void UnpackTexPalette(TEXPalette* pal);
void *memcpy(void *dest, const void *src, size_t num);
void *memset(void *dest, int ch, size_t count);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t num);
void dispEntry(CameraId camera, f32 order, s32 renderMode, void* callback, void* param);
struct HitEntry* hitEntry(MapFileJoint* root, Mtx rootMtx, s32 mapIndex);
void hitReInit(void);
LightEntry* lightGetAmbient(void);
void mapCalcAnimMatrix(Mtx out, Mtx in, MapAnim* anim, struct MapAnimJoint* joint);
void mapSetTextureMatrix(struct MapMaterial* mat);
GXColor shadowGetCharShadowColor(void);
f32 (*shadowGetCharShadowProjTexMtx(void))[4];
s32 shadowGetCharShadowProjection(void);
GXTexObj* shadowGetCharShadowTexObj(void);
GXColor shadowGetDepthShadowColor(void);
ShadowConfig* shadowGetDepthShadowConfig(void);
f32 (*shadowGetDepthShadowDepthMtx(void))[4];
f32 (*shadowGetDepthShadowProjTexMtx(void))[4];
GXTexObj* shadowGetDepthShadowTexObj(void);
GXColor shadowGetProjShadowColor(void);
ShadowConfig* shadowGetProjShadowConfig(void);
f32 (*shadowGetProjShadowProjTexMtx(void))[4];
GXTexObj* shadowGetProjShadowTexObj(void);
GXTexObj* shadowGetRamp16TexObj(void);
GXTexObj* shadowGetRamp8TexObj(void);
const char* getMapDataDvdRoot(void);
#endif

#ifdef NONMATCHING
const char* getMapDataDvdRoot(void) {
	return ".";
}
#endif
#ifndef NONMATCHING
void N_mapDispOff(void);
#endif

#ifdef NONMATCHING
void N_mapDispOff(void) {
	unk_80418458 = TRUE;
}
#endif
#ifndef NONMATCHING
void N_mapDispOn(void);
#endif

#ifdef NONMATCHING
void N_mapDispOn(void) {
	unk_80418458 = FALSE;
}
#endif
#ifndef NONMATCHING
MapWork* mapGetWork(void);
#endif

#ifdef NONMATCHING
MapWork* mapGetWork(void) {
	return &mapWork[activeGroup];
}
#endif
#ifndef NONMATCHING
s32 mapGetActiveGroup(void);
#endif

#ifdef NONMATCHING
s32 mapGetActiveGroup(void) {
	return activeGroup;
}
#endif
#ifndef NONMATCHING
void mapGetJointsSub(MapFileJoint* joint, s32* numJoints);
#endif

#ifdef NONMATCHING
void mapGetJointsSub(MapFileJoint* joint, s32* numJoints) { //1:1
	(*numJoints)++;
	if (joint->child) {
		mapGetJointsSub(joint->child, numJoints);
	}
	if (joint->next) {
		mapGetJointsSub(joint->next, numJoints);
	}
}
#endif
#ifndef NONMATCHING
s32 mapGetJoints(MapFileJoint* joint);
#endif

#ifdef NONMATCHING
s32 mapGetJoints(MapFileJoint* joint) { //1:1
	s32 numJoints;
#endif
#ifndef NONMATCHING
void mapGetBoundingBox(Vec* min, Vec* max);
#endif

#ifdef NONMATCHING
	numJoints = 0;
	if (joint) {
		numJoints = 1;
		if (joint->child) {
			mapGetJointsSub(joint->child, &numJoints);
		}
	}
	return numJoints;
}

void mapGetBoundingBox(Vec* min, Vec* max) {
	MapWork* wp = &mapWork[activeGroup];
	MapObject* obj;
	int i;
	Vec vec;

	*min = (Vec){0.0f, 0.0f, 0.0f};
	*max = (Vec){0.0f, 0.0f, 0.0f};
	obj = wp->entries[0].objects;
	for (i = 0; i < wp->entries[0].numJoints; i++, obj++) {
		if (obj->joints && obj->joints->partCount) {
			MTXMultVec(obj->modelWorldMtx, &obj->joints->bboxMin, &vec);
			if (min->x > vec.x) min->x = vec.x;
			if (min->y > vec.y) min->y = vec.y;
			if (min->z > vec.z) min->z = vec.z;
			if (max->x < vec.x) max->x = vec.x;
			if (max->y < vec.y) max->y = vec.y;
			if (max->z < vec.z) max->z = vec.z;
			MTXMultVec(obj->modelWorldMtx, &obj->joints->bboxMax, &vec);
			if (min->x > vec.x) min->x = vec.x;
			if (min->y > vec.y) min->y = vec.y;
			if (min->z > vec.z) min->z = vec.z;
			if (max->x < vec.x) max->x = vec.x;
			if (max->y < vec.y) max->y = vec.y;
			if (max->z < vec.z) max->z = vec.z;
		}
	}
}

void mapInit(void) {
	mapWork = __memAlloc(HEAP_DEFAULT, sizeof(MapWork) * 2);
	memset(mapWork, 0, sizeof(MapWork) * 2);
	activeGroup = 0;
	mapClipOffFlag = FALSE;
}
#endif
#ifndef NONMATCHING
void mapInit(void);
#endif

typedef struct MapTexInfo {
	char* name;   // 0x0
	u8 format;    // 0x4
	u8 pad5[3];
	u16 width;    // 0x8
	u16 height;   // 0xA
	void* data;   // 0xC
} MapTexInfo;

typedef struct MapTexSampler {
	MapTexInfo* tex; // 0x0
} MapTexSampler;

typedef struct MapTexMaterial {
	u8 pad0[0xB];
	u8 samplerCount;          // 0xB
	MapTexSampler* samplers[]; // 0xC
} MapTexMaterial;

typedef struct MapTexTable {
	s32 count;
	char* names[];
} MapTexTable;

#ifdef NONMATCHING
static inline s32 mapSearchTexName(MapTexTable* table, char* name) {
	s32 i;
#endif

#ifdef NONMATCHING
	for (i = 0; i < table->count; i++) {
		if (strcmp(table->names[i], name) == 0) {
			return i;
		}
	}
	return -1;
}

void mapBuildTexture(MapObject* obj, TEXPalette* texture, void* table) {
	int i;
	int j;
	int k;
	int idx;
	MapTexMaterial* mat;
	MapTexSampler* sampler;
	TEXDescriptor* desc;

	for (i = 0; i < obj->joints->partCount; i++) {
		mat = obj->joints->parts[i].material;
		for (j = 0; j < mat->samplerCount; j++) {
			sampler = mat->samplers[j];
			k = mapSearchTexName(table, sampler->tex->name);
			idx = k;
			if (k == -1) {
				idx = 0;
			}
			desc = TEXGet(texture, idx);
			sampler->tex->data = desc->textureHeader->data;
			sampler->tex->width = desc->textureHeader->width;
			sampler->tex->height = desc->textureHeader->height;
			switch (desc->textureHeader->format) {
				case 4: sampler->tex->format = 0; break;
				if (!k) {
				}
				case 5: sampler->tex->format = 1; break;
				case 6: sampler->tex->format = 2; break;
				case 14: sampler->tex->format = 3; break;
				case 0: sampler->tex->format = 4; break;
				case 1: sampler->tex->format = 5; break;
				case 2: sampler->tex->format = 6; break;
				case 3: sampler->tex->format = 7; break;
				case 8: sampler->tex->format = 8; break;
				case 9: sampler->tex->format = 9; break;
				case 10: sampler->tex->format = 10; break;
			}
		}
	}
	if (obj->child) {
		mapBuildTexture(obj->child, texture, table);
	}
	if (obj->next) {
		mapBuildTexture(obj->next, texture, table);
	}
}
#endif
#ifndef NONMATCHING
void mapBuildTexture(MapObject* obj, TEXPalette* texture, void* table);
#endif

#pragma dont_inline on
#ifdef NONMATCHING
MapObject* _mapEnt(MapFileJoint* joint, MapObject* parent, Mtx mtx, s32 index) {
	MapWork* wp = &mapWork[activeGroup];
	MapObject* obj;
	s32 i;
	Mtx trans, scale, rotX, rotY, rotZ;
	Vec a, b;

	obj = wp->entries[index].objects;
	for (i = 0; i < wp->entries[index].numJoints; i++, obj++) {
		if (!obj->joints) break;
	}
	obj->flags = 0;
	obj->joints = joint;
	obj->groupIndex = (s16)index;
	PSMTXTrans(trans, joint->translation.x, joint->translation.y, joint->translation.z);
	PSMTXScale(scale, joint->scale.x, joint->scale.y, joint->scale.z);
	PSMTXRotRad(rotX, 'x', 0.017453292f * joint->rotation.x);
	PSMTXRotRad(rotY, 'y', 0.017453292f * joint->rotation.y);
	PSMTXRotRad(rotZ, 'z', 0.017453292f * joint->rotation.z);
	PSMTXConcat(trans, rotZ, trans);
	PSMTXConcat(trans, rotY, trans);
	PSMTXConcat(trans, rotX, trans);
	PSMTXConcat(trans, scale, obj->localMtx);
	PSMTXConcat(mtx, obj->localMtx, obj->modelWorldMtx);
	PSMTXIdentity(obj->unkAC);
	obj->flags |= 0x200;
	obj->unk5 = 4;
	obj->offscreenId = -1;
	obj->parent = parent;
	obj->next = NULL;
	obj->child = NULL;
	if (joint->drawMode) {
		if (((u8*)joint->drawMode)[2] & 1) {
			obj->flags |= 8;
		}
		switch (joint->drawMode->unk0[0]) {
			case 0: {
				MapFileJoint* j = obj->joints;
				s32 k, n2 = 0, n1 = 0;
				for (i = 0; i < obj->joints->partCount; i++) {
					u8 t = *((u8*)obj->joints->parts[i].material + 0xa);
					if (t == 2) { n2++; if (!obj) { } }
					else if (t == 1) { if (1) { } n1++; }
					for (k = 0; k < 8; k++) {
						u8* tex = *(u8**)((u8*)obj->joints->parts[i].material + 0xc + k * 4);
						if (!tex) break;
						t = tex[0xa];
						if (t == 2) n2++;
						else if (t == 1) n1++;
					}
				}
				if (n2) obj->blendMode = 2;
				else if (n1) obj->blendMode = 1;
				else obj->blendMode = 0;
				break;
			}
			case 1:
				{ u8 m = 0; if (obj->flags & 8) m = 3; obj->blendMode = m; }
				break;
			case 2:
				obj->blendMode = (obj->flags & 8) ? 4 : 1;
				break;
			case 3:
				obj->blendMode = (obj->flags & 8) ? 5 : 2;
				break;
		}
		if (((u8*)joint->drawMode)[2] & 2) {
			obj->flags |= 0x10;
			if (((u8*)joint->drawMode)[2] & 0x10) {
				obj->flags |= 0x8000;
			}
			switch (joint->drawMode->unk0[0]) {
				case 0: obj->blendMode = 2; break;
				case 1: obj->blendMode = 0; break;
				case 2: obj->blendMode = 1; break;
				case 3:
				default: obj->blendMode = 2; break;
			}
		}
		if (obj->flags & 0x10) {
			if (parent && (parent->flags & 0x10 || parent->flags & 0x20)) {
				obj->flags &= ~0x10;
			}
		} else if (parent && (parent->flags & 0x10 || parent->flags & 0x20)) {
			obj->flags |= 0x20;
			if (parent->flags & 0x8000) {
				obj->flags |= 0x8000;
			}
		}
		if (((u8*)joint->drawMode)[2] & 4) {
			obj->flags |= 4;
		}
	} else {
		OSPanic("mapdrv.c", 0x2e5, "\x83\x57\x83\x87\x83\x43\x83\x93\x83\x67\x82\xcc\x83\x66\x81\x5b\x83\x5e\x82\xcc\x8e\x77\x92\xe8\x82\xc9\x82\xa8\x82\xa9\x82\xb5\x82\xc8\x82\xe0\x82\xcc\x82\xaa\x82\xa0\x82\xe9\n");
	}
	if (joint->partCount) {
		PSVECAdd(&joint->bboxMin, &joint->bboxMax, &obj->center);
		PSVECScale(&obj->center, &obj->center, 0.5f);
	} else {
		obj->center = joint->translation;
	}
	if (joint->partCount) {
		PSMTXMultVec(obj->modelWorldMtx, &obj->center, &a);
		PSMTXMultVec(obj->modelWorldMtx, &joint->bboxMax, &b);
		if (PSVECSquareDistance(&a, &b) < mapF20000) {
			obj->flags |= 2;
		}
	}
	return obj;
}
#endif
#ifndef NONMATCHING
MapObject* _mapEnt(MapFileJoint* joint, MapObject* parent, Mtx mtx, s32 index);
#endif

#pragma dont_inline reset
#ifdef NONMATCHING
MapObject* mapEntrySub(MapFileJoint* joint, MapObject* parent, Mtx mtx, BOOL isRoot, s32 index) {
	MapObject* obj = _mapEnt(joint, parent, mtx, index);
	if (joint->child) {
		obj->child = mapEntrySub(joint->child, obj, obj->modelWorldMtx, FALSE, index);
	}
	if (!isRoot) {
		if (joint->next) {
			obj->next = mapEntrySub(joint->next, parent, mtx, FALSE, index);
		}
	}
	return obj;
}
#endif
#ifndef NONMATCHING
MapObject* mapEntrySub(MapFileJoint* joint, MapObject* parent, Mtx mtx, BOOL isRoot, s32 index);
#endif

#ifdef NONMATCHING
MapObject* mapEntry(MapFileJoint* joint, Mtx mtx, s32 index) {
	MapWork* wp = (0, &mapWork[activeGroup]);
	u32 size;

	wp->entries[index].numJoints = mapGetJoints(joint);
	size = (((wp->entries[index].numJoints * sizeof(MapObject)) + 32) - 1) & ~(32 - 1);
	wp->entries[index].objects = _mapAlloc(size);
	memset(wp->entries[index].objects, 0, size);
	return mapEntrySub(joint, NULL, mtx, TRUE, index);
}
#endif
#ifndef NONMATCHING
MapObject* mapEntry(MapFileJoint* joint, Mtx mtx, s32 index);
#endif

s32 shadowGetCharShadowProjection(void);
GXTexObj* shadowGetCharShadowTexObj(void);
GXColor shadowGetCharShadowColor(void);
f32 (*shadowGetCharShadowProjTexMtx(void))[4];
GXTexObj* shadowGetDepthShadowTexObj(void);
f32 (*shadowGetDepthShadowDepthMtx(void))[4];
f32 (*shadowGetDepthShadowProjTexMtx(void))[4];
GXColor shadowGetDepthShadowColor(void);
ShadowConfig* shadowGetDepthShadowConfig(void);
GXTexObj* shadowGetRamp8TexObj(void);
GXTexObj* shadowGetRamp16TexObj(void);
GXTexObj* shadowGetProjShadowTexObj(void);
f32 (*shadowGetProjShadowProjTexMtx(void))[4];
GXColor shadowGetProjShadowColor(void);
ShadowConfig* shadowGetProjShadowConfig(void);
void mapSetMaterial(MapObject* obj, void* material);
void mapSetMaterial(MapObject* obj, void* material);
void mapResetPaperAmbColor(void);
void mapResetPaperAmbColor(void);
static inline void mapResetPaperCraftAmbColor(void);

typedef struct MapObjectDL {
	u8 field_0x0[0xF4];  // 0x0
	void* dl[8];         // 0xF4
	u32 dlSize[8];       // 0x114
} MapObjectDL;
#define MAPOBJ_DL(obj) (((MapObjectDL*)(obj))->dl)
#define MAPOBJ_DLSIZE(obj) (((MapObjectDL*)(obj))->dlSize)

#ifdef NONMATCHING
void makeDisplayList(BOOL group) {
	static const GXCullMode culling[4] = {GX_CULL_FRONT, GX_CULL_BACK, GX_CULL_ALL, GX_CULL_NONE};
	MapEntry* e;
	MapWork* wp = mapGetWork();
	void* buf;
	int i;
	int j;
	int pass;
	u32 total;
	u8* dst;
	MapObject* obj;
	MapJointDrawModeEx* dm;
	s32 k;
	void* material;

	buf = _mapAlloc(0x10000);
	e = &wp->entries[group];
	__mapdrv_make_dl = TRUE;
	total = 0;
	for (pass = 0; pass < 2; pass++) {
		obj = e->objects;
		for (k = 0; k < 8; k++) {
			MAPOBJ_DL(obj)[k] = NULL;
			MAPOBJ_DLSIZE(obj)[k] = 0;
		}
		for (i = 0; i < wp->entries[group].numJoints; i++, obj++) {
			if (obj->joints->partCount < 1 || obj->joints->partCount > 8) {
				continue;
			}
			dm = (MapJointDrawModeEx*)obj->joints->drawMode;
			if (dm->flags & 8) {
				continue;
			}
			if (dm->lightMask) {
				continue;
			}
			if (shadowGetCharShadowProjection() && (obj->flags & 4)) {
				continue;
			}
			if (!(e->flags & 0x8000)) {
				continue;
			}
			for (j = 0; j < obj->joints->partCount; j++) {
				material = obj->joints->parts[j].material;
				memset(buf, 0, 0x10000);
				DCInvalidateRange(buf, 0x10000);
				GXBeginDisplayList(buf, 0x10000);
				GXResetWriteGatherPipe();
				mapSetMaterial(obj, material);
				GXSetCullMode(culling[obj->joints->drawMode->cullMode]);
				MAPOBJ_DLSIZE(obj)[j] = GXEndDisplayList();
				if (pass == 0) {
					total += MAPOBJ_DLSIZE(obj)[j];
				}
				else {
					MAPOBJ_DL(obj)[j] = dst;
					dst += MAPOBJ_DLSIZE(obj)[j];
					memcpy(MAPOBJ_DL(obj)[j], buf, MAPOBJ_DLSIZE(obj)[j]);
					DCFlushRange(MAPOBJ_DL(obj)[j], MAPOBJ_DLSIZE(obj)[j]);
				}
			}
		}
		if (pass == 0) {
			e->dispListSize = total;
			if (e->dispListSize) {
				e->dispListBuf = _mapAllocTail(e->dispListSize);
				dst = e->dispListBuf;
			}
			else {
				((void**)((u8*)wp + 0x16C))[group * 0x5E] = NULL;
				break;
			}
		}
	}
	_mapFree(buf);
	__mapdrv_make_dl = FALSE;
}
#endif
#ifndef NONMATCHING
void makeDisplayList(BOOL group);
#endif

static inline MapAnim* mapSearchAnmObj_inl(const char* animName) {
	MapEntry* entry;
	MapWork* wp = &mapWork[activeGroup];
	int j;
	int i;
	MapAnim* anim;

	entry = wp->entries;
	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		anim = (MapAnim*)entry->animData;
		for (j = 0; j < entry->numAnims; j++, anim++) {
			if ((anim->flags & 1) && !strcmp(anim->anim->name, animName)) {
				return anim;
			}
		}
	}
	return NULL;
}

#ifdef NONMATCHING
MapEntryAnimData* mapSearchAnmObj(const char* animName) {
	MapWork* wp = &mapWork[activeGroup];
	MapEntry* entry;
	int j;
	int i;
	MapAnim* anim;
#endif
#ifndef NONMATCHING
MapEntryAnimData* mapSearchAnmObj(const char* animName);
#endif

#ifdef NONMATCHING
	entry = wp->entries;
	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		anim = (MapAnim*)entry->animData;
		for (j = 0; j < entry->numAnims; j++, anim++) {
			if ((anim->flags & 1) && !strcmp(anim->anim->name, animName)) {
				return (MapEntryAnimData*)anim;
			}
		}
	}
	return NULL;
}
#endif
#ifndef NONMATCHING
void mapCheckAnimation(const char* animName, BOOL* valid, f32* a3);
#endif

#ifdef NONMATCHING
void mapCheckAnimation(const char* animName, BOOL* valid, f32* a3) {
	MapAnim* anim = mapSearchAnmObj_inl(animName);
#endif
#ifndef NONMATCHING
void mapPlayAnimationLv(const char* name, s32 a, s32 b);
#endif

#ifdef NONMATCHING
	*valid = FALSE;
	*a3 = 0.0f;
	if (anim) {
		if (anim->flags & 2) {
			*valid = TRUE;
		}
		*a3 = 1000.0f * (anim->anim->length - anim->time) / gp->framerate;
	}
	else {
		*valid = TRUE;
	}
}
#endif
#ifndef NONMATCHING
void mapPauseAnimation(const char* name);
#endif

#ifdef NONMATCHING
void mapPlayAnimationLv(const char* name, s32 a, s32 b) {
	MapAnim* anim = NULL;
	MapWork* wp;
	MapEntry* entry;
	int j;
	int i = 0;
	BOOL found = FALSE;
	OSTime t;
#endif
#ifndef NONMATCHING
void mapReStartAnimation(const char* name);
#endif

#ifdef NONMATCHING
	wp = &mapWork[activeGroup];
	entry = wp->entries;
	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		anim = (MapAnim*)entry->animData;
		for (j = 0; j < entry->numAnims; j++, anim++) {
			if (!strcmp(anim->anim->name, name)) {
				found = TRUE;
				break;
			}
		}
		if (found) {
			break;
		}
	}
	if (found) {
		anim->flags = 0;
		switch (b) {
			case 0:
				break;
			case 1:
				anim->flags |= 0x100;
				break;
			case 2:
				anim->flags |= 0x200;
				break;
			case 3:
				anim->flags |= 0x400;
				break;
			case 4:
				anim->flags |= 0x800;
				break;
		}
		if (anim->flags & 0x100) {
			t = gp->systemLv0Time;
		}
		else if (anim->flags & 0x200) {
			t = gp->systemLv1Time;
		}
		else if (anim->flags & 0x400) {
			t = gp->systemLv2Time;
		}
		else if (anim->flags & 0x800) {
			t = gp->systemLv3Time;
		}
		else if (gp->inBattle) {
			t = gp->renderTime;
		}
		else {
			t = gp->renderFieldTime;
		}
		anim->startTime = OSTicksToMilliseconds(t);
		anim->time = 0.0f;
		anim->rate = 1.0f;
		anim->flags |= 1;
		if (a == 1) {
			anim->flags |= 4;
		}
		if (a == 2) {
			anim->startTime -= (u64)(1000.0f * anim->anim->length / gp->framerate);
		}
	}
}
#endif
#ifndef NONMATCHING
void mapPauseAnimationAll(const char* name);
#endif

#ifdef NONMATCHING
void mapPauseAnimation(const char* name) {
	MapAnim* anim = mapSearchAnmObj_inl(name);
	if (anim) {
		anim->flags |= 0x10;
	}
}
#endif
#ifndef NONMATCHING
void mapReStartAnimationAll(const char* name);
#endif

#ifdef NONMATCHING
void mapReStartAnimation(const char* name) {
	MapAnim* anim = mapSearchAnmObj_inl(name);
	if (anim) {
		anim->flags |= 0x20;
	}
}

void mapPauseAnimationAll(const char* name) {
	MapWork* wp = &mapWork[activeGroup];
	MapEntry* entry = wp->entries;
	int j;
	int i;
	MapAnim* anim;

	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		anim = (MapAnim*)entry->animData;
		for (j = 0; j < entry->numAnims; j++, anim++) {
			anim->flags |= 0x10;
		}
	}
}

void mapReStartAnimationAll(const char* name) {
	MapWork* wp = &mapWork[activeGroup];
	MapEntry* entry = wp->entries;
	int j;
	int i;
	MapAnim* anim;

	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		anim = (MapAnim*)entry->animData;
		for (j = 0; j < entry->numAnims; j++, anim++) {
			anim->flags |= 0x20;
		}
	}
}

void mapSetPlayRate(const char* name, f32 rate) {
	MapAnim* anim = mapSearchAnmObj_inl(name);
	if (anim) {
		anim->rate = rate;
	}
}
#endif
#ifndef NONMATCHING
void mapSetPlayRate(const char* name, f32 rate);
#endif

typedef struct MapFileLightEx {
	const char* name;   // 0x0
	const char* type;   // 0x4
	Vec position;       // 0x8
	Vec rotation;       // 0x14
	u8 pad20[0x2C - 0x20];
	GXColor color;      // 0x2C
	f32 spotAngle;      // 0x30
	f32 attenAngle;     // 0x34
	s32 attenType;      // 0x38
	s32 lflags;         // 0x3C
	s32 magic;          // 0x40
} MapFileLightEx;

struct HitEntry* hitEntry(MapFileJoint* root, Mtx rootMtx, s32 mapIndex);
MapFileJoint* mapSearchDmdJoint(MapFileJoint* joint, const char* name);
MapFileJoint* mapSearchDmdJoint(MapFileJoint* joint, const char* name);

#ifdef NONMATCHING
static inline void* mapSearchChunk(MapHeader* header, const char* name) {
	u32 k;

	for (k = 0; k < header->file.chunkCount; k++) {
		if (!strcmp(&header->strings[header->chunks[k].string], name)) {
			return (u8*)header->data + header->chunks[k].offset;
		}
	}
	return NULL;
}
#endif


#ifdef NONMATCHING
static inline u32* mapLoadFindChunk_(MapEntry* e2, const char* name) {
	u32 k;
	for (k = 0; k < e2->header.file.chunkCount; k++) {
		if (!strcmp(&e2->header.strings[e2->header.chunks[k].string], name)) {
			return (u32*)((u8*)e2->header.data + e2->header.chunks[k].offset);
		}
	}
	return NULL;
}
#endif
typedef struct MapEntryOv {
	u8 pad0[0x24];
	s32 fogEnable;
	u8 pad28[0x78 - 0x28];
	void* hdr40;
	u8 pad7C[0x94 - 0x7C];
	void* textureTable;
	void* lightTable;
	void* fogTable;
	void* materialNameTable;
	void* vcdTable;
	u8 padA8[0x178 - 0xA8];
} MapEntryOv;
typedef struct MapWorkOv {
	MapEntryOv entries[2];
} MapWorkOv;
#ifdef NONMATCHING
static inline void mapLoadReloc_(MapEntry* entry) {
	u32 k;
	for (k = 0; k < (u32)entry->header.file.relCount; k++) {
		u32* rel = (u32*)((u8*)entry->header.data + ((u32*)entry->header.rel)[k]);
		if (*rel <= 0x80000000) {
			*rel += (u32)entry->header.data;
		}
	}
}
static inline void mapLoadHeader_(MapWork* wp, BOOL group) {
	u32 datSize = wp->entries[group].datSize;
	u8* data = (u8*)wp->entries[group].dat;
	u32 sizeCheck;
	MapHeader* header = &wp->entries[group].header;
	if (header != NULL) {
		memset(header, 0, sizeof(MapHeader));
		wp->entries[group].header.field_0x3C |= 1;
		memcpy(header, data, sizeof(MapFileHeader));
		if (wp->entries[group].header.file.fileSize == datSize) {
			sizeCheck = sizeof(MapFileHeader);
			if ((u32)wp->entries[group].header.file.dataSize != 0u) {
				wp->entries[group].header.data = &data[sizeCheck];
				sizeCheck = wp->entries[group].header.file.dataSize;
				sizeCheck += sizeof(MapFileHeader);
			}
			if ((u32)wp->entries[group].header.file.relCount != 0u) {
				wp->entries[group].header.rel = &data[sizeCheck];
				sizeCheck += 4 * wp->entries[group].header.file.relCount;
			}
			if ((u32)wp->entries[group].header.file.chunkCount != 0u) {
				wp->entries[group].header.chunks = (MapFileChunk*)&data[sizeCheck];
				sizeCheck += sizeof(MapFileChunk) * wp->entries[group].header.file.chunkCount;
			}
			if ((u32)wp->entries[group].header.file.unused != 0u) {
				wp->entries[group].header.unused = &data[sizeCheck];
				sizeCheck += 8 * wp->entries[group].header.file.unused;
			}
			if (sizeCheck < wp->entries[group].header.file.fileSize) {
				wp->entries[group].header.strings = (const char*)&data[sizeCheck];
			}
			*(u8**)((u8*)&wp->entries[group] + 0x78) = data;

			mapLoadReloc_(&wp->entries[group]);
		}
	}
}
void _mapLoad(MapWork* wp, BOOL group, const char* map) {
	MapFileInfo* info;
	u32 datSize, k;
	int i;
	u32 r4, r7, r0;
	u32 sizeCheck;
	char str1[128];
	char str2[128];
	char str3[128];
	DVDEntry* dvd;
	MapWorkOv* wo;
	u8 *data;
	MapHeader* header;

	wo = (MapWorkOv*)wp;
	error_flag = FALSE;
	error_count = 0;
	strncpy(wp->entries[group].name, map, sizeof(wp->entries[group].name));

	sprintf(str1, "./m/%s/d", map);
	arcOpen(str1, &wp->entries[group].dat, &wp->entries[group].datSize);
	if (!wp->entries[group].dat) {
		sprintf(str2, mapPathFmt, ".", str1);
		dvd = DVDMgrOpen(str2, 2, 0);
		wp->entries[group].datSize = DVDMgrGetLength(dvd);
		wp->entries[group].dat = _mapAllocTail(OSRoundUp32B(wp->entries[group].datSize));
		DVDMgrRead(dvd, wp->entries[group].dat, OSRoundUp32B(wp->entries[group].datSize), 0);
		DVDMgrClose(dvd);
	}

	sprintf(str1, "./m/%s/t", map);
	wp->entries[group].tpl = NULL;
	arcOpen(str1, &wp->entries[group].tpl, &wp->entries[group].tplSize);
	if (wp->entries[group].tpl) {
		UnpackTexPalette(wp->entries[group].tpl);
	}
	else {
		sprintf(str3, mapPathFmt, ".", str1);
		dvd = DVDMgrOpen(str3, 2, 0);
		if (dvd) {
			wp->entries[group].tplSize = DVDMgrGetLength(dvd);
			wp->entries[group].tpl = _mapAllocTail(OSRoundUp32B(wp->entries[group].tplSize));
			DVDMgrRead(dvd, wp->entries[group].tpl, OSRoundUp32B(wp->entries[group].tplSize), 0);
			DVDMgrClose(dvd);
			UnpackTexPalette(wp->entries[group].tpl);
		}
	}

	GXInvalidateVtxCache();
	mapLoadHeader_(wp, group);
	header = &wp->entries[group].header;
	info = (MapFileInfo*)mapSearchChunk(header, "information");
	wo->entries[group].textureTable = mapSearchChunk(header, "texture_table");
	wo->entries[group].lightTable = mapSearchChunk(header, "light_table");
	wo->entries[group].fogTable = mapSearchChunk(header, "fog_table");
	wo->entries[group].materialNameTable = mapSearchChunk(header, "material_name_table");
	wo->entries[group].vcdTable = mapSearchChunk(header, "vcd_table");
	{
		MapFileJoint* mapJoint = mapSearchDmdJoint(info->joint, info->mapName);
		MapFileJoint* hitJoint = mapSearchDmdJoint(info->joint, info->hitName);
		Mtx scale;
		s32 n;
		u32* animTbl;
		MapEntry* e2;
		MapWork* w;
		if (strcmp(info->version, "ver1.02") == 0) {
			wp->entries[group].flags |= 0x8000;
		}
		else {
			wp->entries[group].flags &= 0x7FFF;
		}
		PSMTXScale(scale, 1.0f, 1.0f, 1.0f);
		wp->entries[group].rootMapObj = mapEntry(mapJoint, scale, group);
		wp->entries[group].rootHitObj = hitEntry(hitJoint, scale, group);
		{
			for (i = 0; i < ((s32*)wp->entries[group].lightTable)[0]; i++) {
				MapFileLightEx* light = (MapFileLightEx*)((u32*)wp->entries[group].lightTable)[i + 1];
				Vec pos;
				GXColor lcolor;
				s32 type = 1;
				s32 lflags = 0;
				PSVECScale(&light->position, &pos, 1.0f);
				if (!strcmp(light->type, "ambientLight")) {
					type = 0;
				}
				else if (!strcmp(light->type, "pointLight")) {
					type = 1;
				}
				else if (!strcmp(light->type, "directionalLight")) {
					type = 2;
				}
				else if (!strcmp(light->type, "spotLight")) {
					type = 3;
				}
				if (light->magic == 0x12D60D8) {
					lflags = light->lflags;
				}
				lcolor = light->color;
				((s32(*)(const char*, s32, Vec*, Vec*, GXColor*, f32, f32, s32, s32))lightEntry)(light->name, type, &pos, &light->rotation, &lcolor, light->spotAngle, light->attenAngle, light->attenType, lflags);
			}
		}
		mapResetPaperAmbColor();
		mapResetPaperCraftAmbColor();
		if ((&wo->entries[group])->fogTable != NULL) {
			wo->entries[group].fogEnable = ((s32*)(&wo->entries[group])->fogTable)[0];
			wp->entries[group].fogType = ((s32*)(&wo->entries[group])->fogTable)[1];
			wp->entries[group].fogStart = ((f32*)(&wo->entries[group])->fogTable)[2];
			wp->entries[group].fogEnd = ((f32*)(&wo->entries[group])->fogTable)[3];
			wp->entries[group].fogColor = ((GXColor*)(&wo->entries[group])->fogTable)[4];
			if (wo->entries[group].fogEnable != 0) {
				wp->entries[group].flags |= 1;
			}
		}
		else {
			wo->entries[group].fogEnable = 0;
			wp->entries[group].fogType = 0;
			wp->entries[group].fogStart = 0.0f;
			wp->entries[group].fogEnd = 0.0f;
			wp->entries[group].fogColor = (GXColor){0, 0, 0, 0};
			wp->entries[group].flags &= ~1;
		}
		if (activeGroup != 1) {
			sprintf(str1, "./m/%s/c", map);
			camLoadRoad(4, str1);
		}
		camSetTypePersp(4);
		mapBuildTexture(wp->entries[group].rootMapObj, wp->entries[group].tpl, (&wo->entries[group])->textureTable);
		{
			Vec mn;
			Vec mx;
			mapGetBoundingBox(&mn, &mx);
#define BBOX(idx, X, Y, Z) { Vec v = {0.0f, 0.0f, 0.0f}; v.x = X; v.y = Y; v.z = Z; wp->entries[group].bbox[idx] = v; }
			BBOX(0, mx.x, mx.y, mx.z)
			BBOX(1, mn.x, mx.y, mx.z)
			BBOX(2, mx.x, mn.y, mx.z)
			BBOX(3, mx.x, mx.y, mn.z)
			BBOX(4, mn.x, mn.y, mx.z)
			BBOX(5, mx.x, mn.y, mn.z)
			BBOX(6, mn.x, mx.y, mn.z)
			BBOX(7, mn.x, mn.y, mn.z)
#undef BBOX
		}
		w = &mapWork[activeGroup];
		e2 = &w->entries[group];
		animTbl = mapLoadFindChunk_(e2, "animation_table");
		if (animTbl != NULL) {
			w->entries[group].numAnims = animTbl[0];
			if (w->entries[group].numAnims != 0) {
				n = OSRoundUp32B(w->entries[group].numAnims * 32);
				w->entries[group].animData = _mapAlloc(n);
				memset(w->entries[group].animData, 0, n);
				{
					MapEntryAnimData* a = w->entries[group].animData;
					for (i = 0; i < e2->numAnims; i++) {
						a->flags = 0;
						MAPENT_FIELD(a, u32, 0x18) = *++animTbl;
						a++;
					}
				}
			}
		}
	}
	makeDisplayList(group);
	{
		MapWork* w3 = &mapWork[activeGroup];
		MapObject* o = w3->entries[group].objects;
		for (i = 0; i < w3->entries[group].numJoints; i++, o++) {
			MapJointDrawModeEx* dm;
			if (o->joints->partCount < 1 || o->joints->partCount > 8) {
				continue;
			}
			dm = (MapJointDrawModeEx*)o->joints->drawMode;
			if (dm->flags & 8) {
				continue;
			}
			if (dm->lightMask) {
				continue;
			}
			if (shadowGetCharShadowProjection() && (o->flags & 4)) {
				continue;
			}
			if (!(w3->entries[group].flags & 0x8000)) {
				continue;
			}
			o->flags |= 0x100;
		}
	}
	unk_80418458 = FALSE;
}
#endif
#ifndef NONMATCHING
void _mapLoad(MapWork* wp, BOOL group, const char* map);
#endif

void hitReInit(void);


#ifdef NONMATCHING
void mapUnLoad(void) {
	MapEntry* entry2;
	MapEntry* entry;
	int i;
	MapWork* wp;
#endif
#ifndef NONMATCHING
void mapUnLoad(void);
#endif

#ifdef NONMATCHING
	sysWaitDrawSync();
	entry = mapWork->entries;
	wp = mapWork;
	activeGroup = i = 0;
	for (; i < wp->entries[0].count; entry++, i++) {
		if (entry->objects) {
			_mapFree(entry->objects);
			entry->numJoints = 0;
			entry->objects = NULL;
		}
		if (entry->animData) {
			_mapFree(entry->animData);
			entry->numAnims = 0;
			entry->animData = NULL;
		}
		if (entry->dispListBuf) {
			_mapFree(entry->dispListBuf);
			entry->dispListBuf = NULL;
			entry->dispListSize = 0;
		}
	}
	unk_80418458 = FALSE;
	hitReInit();
	lightReInit();
	envReInit();
	camUnLoadRoad(4);
	camSetTypePersp(4);
	entry2 = wp->entries;
	for (i = 0; i < wp->entries[0].count; entry2++, i++) {
		if (entry2->dat) {
			if (!arcDataCheck(entry2->dat)) {
				_mapFree(entry2->dat);
			}
			entry2->dat = NULL;
		}
		if (entry2->tpl) {
			if (!arcDataCheck(entry2->tpl)) {
				_mapFree(entry2->tpl);
			}
			entry2->tpl = NULL;
		}
		if (entry2->arcData) {
			_mapFree(entry2->arcData);
			entry2->arcData = NULL;
		}
		strncpy(entry2->name, mapEmptyStr, sizeof(entry2->name));
	}
	arcDelete(1);
	memset(wp, 0, sizeof(MapWork));
}
#endif
#ifndef NONMATCHING
BOOL mapPreLoad(void);
#endif

#ifdef NONMATCHING
BOOL mapPreLoad(void) {
	return TRUE; //do nothing
}

void mapLoad(const char* map) {
	MapWork* wp;

	MapWork* wp2;
	sysWaitDrawSync();
	wp2 = wp = mapWork;
	activeGroup = 0;

	memset(wp2, 0, sizeof(MapWork));
	_mapLoad(wp, 0, map);
	wp->entries[0].count = 1;
}
#endif
#ifndef NONMATCHING
void mapLoad(const char* map);
#endif

// FAKE: whole-function asm; best pure C 99.62 (loop-3 r30/r31 tie: const 0 vs mapWork)
#ifdef NONMATCHING
asm void bmapUnLoad(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    bl sysWaitDrawSync
    lwz r3, mapWork(r13)
    li r0, 0x1
    stw r0, activeGroup(r13)
    li r30, 0x0
    addi r31, r3, 0x2f4
    mr r29, r31
    b lbl_80028570
lbl_80028514:
    lwz r3, 0x154(r29)
    cmplwi r3, 0x0
    beq lbl_80028530
    bl _mapFree
    li r0, 0x0
    stw r0, 0x150(r29)
    stw r0, 0x154(r29)
lbl_80028530:
    lwz r3, 0x164(r29)
    cmplwi r3, 0x0
    beq lbl_8002854C
    bl _mapFree
    li r0, 0x0
    stw r0, 0x160(r29)
    stw r0, 0x164(r29)
lbl_8002854C:
    lwz r3, 0x16c(r29)
    cmplwi r3, 0x0
    beq lbl_80028568
    bl _mapFree
    li r0, 0x0
    stw r0, 0x16c(r29)
    stw r0, 0x168(r29)
lbl_80028568:
    addi r29, r29, 0x178
    addi r30, r30, 0x1
lbl_80028570:
    lwz r0, 0x0(r31)
    cmpw r30, r0
    blt lbl_80028514
    li r0, 0x0
    stw r0, unk_80418458(r13)
    bl hitReInit
    bl lightReInit
    bl envReInit
    mr r29, r31
    li r30, 0x0
    b lbl_8002861C
lbl_8002859C:
    lwz r3, 0x7c(r29)
    cmplwi r3, 0x0
    beq lbl_800285C4
    bl arcDataCheck
    cmpwi r3, 0x0
    bne lbl_800285BC
    lwz r3, 0x7c(r29)
    bl _mapFree
lbl_800285BC:
    li r0, 0x0
    stw r0, 0x7c(r29)
lbl_800285C4:
    lwz r3, 0x84(r29)
    cmplwi r3, 0x0
    beq lbl_800285EC
    bl arcDataCheck
    cmpwi r3, 0x0
    bne lbl_800285E4
    lwz r3, 0x84(r29)
    bl _mapFree
lbl_800285E4:
    li r0, 0x0
    stw r0, 0x84(r29)
lbl_800285EC:
    lwz r3, 0x8c(r29)
    cmplwi r3, 0x0
    beq lbl_80028604
    bl _mapFree
    li r0, 0x0
    stw r0, 0x8c(r29)
lbl_80028604:
    addi r3, r29, 0x6
    la r4, mapEmptyStr(r2)
    li r5, 0x10
    bl strncpy
    addi r29, r29, 0x178
    addi r30, r30, 0x1
lbl_8002861C:
    lwz r0, 0x0(r31)
    cmpw r30, r0
    blt lbl_8002859C
    li r3, 0x1
    bl arcDelete
    li r3, 0x2
    bl arcDelete
    mr r3, r31
    li r4, 0x0
    li r5, 0x2f4
    bl memset
    li r31, 0x0
    lwz r30, mapWork(r13)
    stw r31, activeGroup(r13)
    mr r29, r30
    b lbl_800286D8
lbl_8002865C:
    lwz r0, 0x170(r29)
    cmplwi r0, 0x0
    beq lbl_800286A8
    lwz r3, 0x80(r29)
    bl _mapAllocTail
    stw r3, 0x7c(r29)
    lwz r3, 0x88(r29)
    bl _mapAllocTail
    stw r3, 0x84(r29)
    lwz r3, 0x170(r29)
    lwz r4, 0x7c(r29)
    bl aramMgrToMram
    lwz r3, 0x178(r29)
    lwz r4, 0x84(r29)
    bl aramMgrToMram
    li r0, 0x0
    stw r0, 0x170(r29)
    stw r0, 0x178(r29)
    b lbl_800286C8
lbl_800286A8:
    lwz r3, 0x90(r29)
    bl _mapAllocTail
    stw r3, 0x8c(r29)
    lwz r3, 0x174(r29)
    lwz r4, 0x8c(r29)
    bl aramMgrToMram
    li r0, 0x0
    stw r0, 0x174(r29)
lbl_800286C8:
    mr r3, r31
    bl makeDisplayList
    addi r29, r29, 0x178
    addi r31, r31, 0x1
lbl_800286D8:
    lwz r0, 0x0(r30)
    cmpw r31, r0
    blt lbl_8002865C
    lwz r4, 0x8c(r30)
    cmplwi r4, 0x0
    beq lbl_800286FC
    lwz r5, 0x90(r30)
    li r3, 0x1
    bl arcEntry
lbl_800286FC:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
#endif

#ifdef NONMATCHING
void bmapLoad(const char *map, const char *map2)
{
  MapWork *wp;
  MapEntry *entry;
  MapEntry *e;
  int i;
  sysWaitDrawSync();
  activeGroup = 0;
  wp = mapGetWork();
  for (i = 0; i < wp->entries[0].count; i++)
  {
    e = &mapWork[activeGroup].entries[i];
    entry = &wp->entries[i];
    if (e->dispListBuf)
    {
      _mapFree(e->dispListBuf);
    }
    e->dispListSize = 0;
    e->dispListBuf = (void *) 0;
    // NB: +0x178 is past sizeof(MapEntry) (0x178): it is the next entry's count (or MapWork.field_2F0 for entry 1).
    // The original strides entries by 0x178 everywhere, so this matches the game; the real layout is probably
    // MapWork { s32 count; entries } with a tplAram as each entry's last field (all MapEntry offsets +4).
    entry->datAram = (void *) 0;
    *((void **) (((u8 *) entry) + 0x178)) = (void *) 0;
    entry->arcAram = (void *) 0;
    if (entry->dat)
    {
      if (!arcDataCheck(entry->dat))
      {
        entry->datAram = aramMgrToAram(entry->dat, entry->datSize);
        *((ARAMEntry **) (((u8 *) entry) + 0x178)) = aramMgrToAram(entry->tpl, entry->tplSize);
        _mapFree(entry->tpl);
        _mapFree(entry->dat);
        entry->tpl = (void *) 0;
        entry->dat = (void *) 0;
      }
      else
      {
        entry->arcAram = aramMgrToAram(entry->arcData, entry->arcSize);
        _mapFree(entry->arcData);
        entry->arcData = (void *) 0;
      }
    }
  }

  wp = (0, &mapWork[1]);
  activeGroup = 1;
  memset(wp, 0, sizeof(MapWork));
  _mapLoad(wp, 0, map);
  wp->entries[0].count = 1;
  if (map2)
  {
    _mapLoad(wp, 1, map2);
    wp->entries[0].count = 2;
  }
}
#endif
#ifndef NONMATCHING
void bmapLoad(const char *map, const char *map2);
#endif

typedef struct MapAnimKeyCh {
	f32 value;  // 0x0
	f32 tanIn;  // 0x4
	f32 tanOut; // 0x8
	f32 unkC;   // 0xC
	s32 step;   // 0x10
} MapAnimKeyCh;

typedef struct MapAnimKey {
	f32 time;             // 0x0
	MapAnimKeyCh ch[21];  // 0x4
} MapAnimKey;

typedef struct MapAnimJoint {
	u8 field_0x0[0x4 - 0x0];    // 0x0
	f32 base[9];                // 0x4
	u8 field_0x28[0x58 - 0x28]; // 0x28
	s32 keyCount;               // 0x58
	MapAnimKey keys[];          // 0x5C
} MapAnimJoint;
void mapCalcAnimMatrix(Mtx out, Mtx in, MapAnim* anim, MapAnimJoint* joint);

#ifdef NONMATCHING
static inline f32 mapHermite(f32 cur, f32 t0, f32 t1, f32 p0, f32 m0, f32 p1, f32 m1) {
	f32 s = cur - t0;
	f32 dt = t1 - t0;
	f32 t = s / (!dt ? 1e-8f : dt);
	f32 t2 = t * t;
	f32 t3 = t2 * t;

	return p0 * (2.0f * t3 - 3.0f * t2 + 1.0f)
		+ m0 * (dt * (t3 - 2.0f * t2 + t))
		+ p1 * (-2.0f * t3 + 3.0f * t2)
		+ m1 * (dt * (t3 - t2));
}
#endif


static inline f32 mapHermiteCh(f32 cur, f32 t0, f32 t1, MapAnimKeyCh* a, MapAnimKeyCh* b) {
	f32 s = cur - t0;
	f32 dt = t1 - t0;
	f32 m1 = b->tanIn;
	f32 p1 = b->value;
	f32 m0 = a->tanOut;
	f32 p0 = a->value;
#ifdef NONMATCHING
	f32 t = s / (!dt ? 1e-8f : dt);
#endif
#ifndef NONMATCHING
	f32 t = s / (!dt ? EXT_LIT(float_1Eneg08_804198b8, 1e-8f) : dt);
#endif
	f32 t2 = t * t;
	f32 t3 = t2 * t;

#ifdef NONMATCHING
	return p0 * (2.0f * t3 - 3.0f * t2 + 1.0f)
#endif
#ifndef NONMATCHING
	return p0 * (EXT_LIT(float_2_80419858, 2.0f) * t3 - 3.0f * t2 + EXT_LIT(float_1_80419860, 1.0f))
#endif
		+ m0 * (dt * (t3 - 2.0f * t2 + t))
#ifdef NONMATCHING
		+ p1 * (-2.0f * t3 + 3.0f * t2)
#endif
#ifndef NONMATCHING
		+ p1 * (EXT_LIT(float_neg2_804198a0, -2.0f) * t3 + EXT_LIT(float_3_8041984c, 3.0f) * t2)
#endif
		+ m1 * (dt * (t3 - t2));
}

#ifdef NONMATCHING
void mapCalcAnimMatrix(Mtx out, Mtx in, MapAnim* anim, MapAnimJoint* joint) {
	f32 v[21];
	Mtx mT;
	Mtx mS;
	Mtx mX;
	Mtx mY;
	Mtx mZ;
	Mtx m;
	f32 dx, dy, dz, rx, ry, sx, sy, sz, rz;
	f32 cur, t, t2, t3, dt;
	int c;
	int i;
	MapAnimKey* k0;
	MapAnimKey* k1;
#endif
#ifndef NONMATCHING
void mapCalcAnimMatrix(Mtx out, Mtx in, MapAnim* anim, MapAnimJoint* joint);
#endif

#ifdef NONMATCHING

	for (i = 1; i < joint->keyCount; i++) {
		k1 = &joint->keys[i];
		k0 = &joint->keys[i - 1];
		if (anim->time <= k1->time) {
			cur = anim->time;
		}
		else if (i == joint->keyCount - 1) {
			cur = k1->time;
		}
		else {
			continue;
		}
		for (c = 0; c < 9; c++) {
			if (k0->ch[c].step) {
				v[c] = k0->ch[c].value;
			}
			else {
				v[c] = mapHermiteCh(cur, k0->time, k1->time, &k0->ch[c], &k1->ch[c]);
			}
		}
		dx = v[0] - joint->base[0];
		dy = v[1] - joint->base[1];
		dz = v[2] - joint->base[2];
		rx = v[3] - joint->base[3];
		ry = v[4] - joint->base[4];
		rz = v[5] - joint->base[5];
		sx = v[6] / joint->base[6];
		sy = v[7] / joint->base[7];
		sz = v[8] / joint->base[8];
		if (dx || dy || dz) {
			PSMTXTrans(mT, dx, dy, dz);
		}
		if (rx) {
			PSMTXRotRad(mX, 'x', 0.017453292f * rx);
		}
		if (ry) {
			PSMTXRotRad(mY, 'y', 0.017453292f * ry);
		}
		if (rz) {
			PSMTXRotRad(mZ, 'z', 0.017453292f * rz);
		}
		PSMTXScale(mS, sx, sy, sz);
		PSMTXIdentity(m);
		if (dx || dy || dz) {
			PSMTXConcat(m, mT, m);
		}
		if (rz) {
			PSMTXConcat(m, mZ, m);
		}
		if (ry) {
			PSMTXConcat(m, mY, m);
		}
		if (rx) {
			PSMTXConcat(m, mX, m);
		}
		if (sx || sy || sz) {
			PSMTXConcat(m, mS, m);
		}
		PSMTXConcat(in, m, out);
		return;
	}
}

void mapReCalcMatrix(MapObject* obj, Mtx mtx, BOOL force) {
	BOOL dirty = FALSE;

	if (obj->flags & 0x200) {
		dirty = TRUE;
	}
	if (force) {
		dirty = TRUE;
	}
	if (dirty) {
		if (obj->flags & 0x2000) {
			PSMTXConcat(mtx, obj->unk7C, obj->modelWorldMtx);
		}
		else {
			PSMTXConcat(mtx, obj->localMtx, obj->modelWorldMtx);
		}
		if (obj->flags & 0x200000) {
			PSMTXConcat(obj->modelWorldMtx, obj->unkAC, obj->modelWorldMtx);
		}
		obj->flags &= ~0x200;
		if (obj->child) {
			mapReCalcMatrix(obj->child, obj->modelWorldMtx, TRUE);
		}
		if (obj->next) {
			mapReCalcMatrix(obj->next, mtx, force);
		}
	}
	else {
		if (obj->child) {
			mapReCalcMatrix(obj->child, obj->modelWorldMtx, force);
		}
		if (obj->next) {
			mapReCalcMatrix(obj->next, mtx, force);
		}
	}
}
#endif
#ifndef NONMATCHING
void mapReCalcMatrix(MapObject* obj, Mtx mtx, BOOL force);
#endif

typedef struct MapAnimNm {
	const char** name; // 0x0
	u8* data;          // 0x4
} MapAnimNm;

typedef struct MapAnimList {
	s32 count;
	MapAnimNm* items[1];
} MapAnimList;

typedef struct MapAnimKey4 {
	f32 time;
	MapAnimKeyCh ch[4];
} MapAnimKey4;

typedef struct MapAnimKey5 {
	f32 time;
	MapAnimKeyCh ch[5];
} MapAnimKey5;

typedef struct MapAnimKey9 {
	f32 time;
	MapAnimKeyCh ch[9];
} MapAnimKey9;

typedef struct MapAnimMatData {
	const char* name;
	s32 idx;
	f32 u;
	f32 v;
	s32 keyCount;
	MapAnimKey5 keys[1];
} MapAnimMatData;

typedef struct MapAnimAlphaData {
	const char* name;
	s32 keyCount;
	MapAnimKey4 keys[1];
} MapAnimAlphaData;

typedef struct MapAnimLightData {
	const char* name;
	s32 keyCount;
	MapAnimKey9 keys[1];
} MapAnimLightData;

typedef struct MapAnimLightData2 {
	const char* name;
	s32 keyCount;
	MapAnimKey5 keys[1];
} MapAnimLightData2;


static inline void mapMainMatKeys_(MapAnim* a_, MapAnimMatData* d, u8* obj) {
	int n, c;
	f32 cur;
	for (n = 1; n < d->keyCount; n++) {
		MapAnimKey5* k0 = &d->keys[n - 1];
		MapAnimKey5* k1 = &d->keys[n];
		if (a_->time <= k1->time) {
			cur = a_->time;
		}
		else if (n == d->keyCount - 1) {
			cur = k1->time;
		}
		else { continue; }

		for (c = 0; c < 5; c++) {
			if (k0->ch[c].step) {
				*(f32*)(obj + d->idx * 0x1c + c * 4 + 0x2c) = k0->ch[c].value;
			}
			else {
				*(f32*)(obj + d->idx * 0x1c + c * 4 + 0x2c) = mapHermiteCh(cur, k0->time, k1->time, &k0->ch[c], &k1->ch[c]);
			}
		}
		*(f32*)(obj + d->idx * 0x1c + 0x40) = d->u;
		*(f32*)(obj + d->idx * 0x1c + 0x44) = d->v;
		break;
	}
}
static inline void mapMainAlphaKeys_(MapAnim* a_, MapAnimAlphaData* d, u8* obj) {
	int n;
	f32 cur;
	for (n = 1; n < d->keyCount; n++) {
		MapAnimKey4* k0 = &d->keys[n - 1];
		MapAnimKey4* k1 = &d->keys[n];

		cur = a_->time;
		if (cur <= d->keys[n].time) {
			cur = a_->time;
		}
		else if (n == d->keyCount - 1) {
			cur = k1->time;
		}
		else { continue; }

		if (k0->ch[0].step) {
			*(u8*)(obj + 0x10c) = (u8)(255.0f - 255.0f * k0->ch[0].value);
		}
		else {
			*(u8*)(obj + 0x10c) = (u8)(255.0f - 255.0f * mapHermiteCh(cur, k0->time, k1->time, (MapAnimKeyCh*)&k0->ch[0], (MapAnimKeyCh*)&k1->ch[0]));
		}

		break;
	}
}
#ifdef NONMATCHING
static inline void mapMainLight_ll(MapAnim* anim, LightEntry* lp, MapAnimLightData* d, f32* v) {
	int n, c;
	f32 cur;

						
						for (n = 1; n < d->keyCount; n++) {
							MapAnimKey9* k0 = &d->keys[n - 1];
							MapAnimKey9* k1 = &d->keys[n];
							if (anim->time <= k1->time) {
								cur = anim->time;
							}
							else if (n == d->keyCount - 1) {
								cur = k1->time;
							}
							else {
								continue;
							}
							for (c = 0; c < 9; c++) {
								if (k0->ch[c].step) {
									v[c] = k0->ch[c].value;
								}
								else {
									v[c] = mapHermiteCh(cur, k0->time, k1->time, &k0->ch[c], &k1->ch[c]);
								}
							}
							lp->position.x = 10.0f * v[0];
							lp->position.y = 10.0f * v[1];
							lp->position.z = 10.0f * v[2];
							lp->rotation.x = v[3];
							lp->rotation.y = v[4];
							lp->rotation.z = v[5];
							break;
						}
					}
static inline void mapMainLight_lc(MapAnim* anim, LightEntry* lp, MapAnimLightData2* d, f32* cv) {
	int n, c;
	f32 cur;

						
						for (n = 1; n < d->keyCount; n++) {
							MapAnimKey5* k0 = &d->keys[n - 1];
							MapAnimKey5* k1 = &d->keys[n];
							if (anim->time <= k1->time) {
								cur = anim->time;
							}
							else if (n == d->keyCount - 1) {
								cur = k1->time;
							}
							else {
								continue;
							}
							for (c = 0; c < 5; c++) {
								if (k0->ch[c].step) {
									cv[c] = k0->ch[c].value;
								}
								else {
									cv[c] = mapHermiteCh(cur, k0->time, k1->time, &k0->ch[c], &k1->ch[c]);
								}
							}
							lp->color.r = (u8)(255.0f * cv[0]);
							lp->color.g = (u8)(255.0f * cv[1]);
							lp->color.b = (u8)(255.0f * cv[2]);
							lp->color.a = 0xff;
							lp->spotAngle = cv[4];
							lp->attenAngle = cv[3];
							break;
						}
					}
#endif

static inline u8* mapMainFindTbl_(const char* nm_) {
	MapEntry* e_;
	MapWork* w_;
	int j_;
	u32* pr_;
	int i_;
	w_ = &mapWork[activeGroup];

	for (i_ = 0; i_ < w_->entries[0].count; i_++) {
		e_ = &w_->entries[i_];
		if (!((u32*)e_->materialNameTable)) {
			return NULL;
		}
		for (j_ = 0; j_ < (s32)((u32*)e_->materialNameTable)[0]; j_++) {
			pr_ = (u32*)&((struct { u32 n_; struct { const char* nm; u8* p; } e_[1]; }*)((u32*)e_->materialNameTable))->e_[j_];
			if (!strcmp((const char*)pr_[0], nm_)) {
				return (u8*)pr_[1];
			}
		}
	}
	return NULL;
}

#define mapMainMat(a_, i_, b_, x_) \
{ \
	u8* obj; \
	strcpy(b_, (const char*)i_->name); \
	if (x_) { \
		strcat(b_, x_); \
	} \
	obj = mapMainFindTbl_(b_); \
	if (obj) { \
		mapMainMatKeys_(a_, (void*)i_, obj); \
	} \
}

#define mapMainAlpha(a_, i_, b_, x_) \
{ \
	u8* obj; \
	strcpy(b_, (const char*)i_->name); \
	if (x_) { \
		strcat(b_, x_); \
	} \
	obj = mapMainFindTbl_(b_); \
	if (obj) { \
		mapMainAlphaKeys_(a_, (void*)i_, obj); \
	} \
}

#ifdef NONMATCHING
void mapMain(void) {
	int i_, j_;
	MapEntry* e_;
	MapWork* w_;
	MapObject* o;
	MapObject* o_;
	s32 c, n;
	f32 cur;
	MapWork* wp = &mapWork[activeGroup];
	MapEntry* entry;
	char mbuf[0x100];
	s32 i, j;
	s32 k;
	MapAnim* anim;
	BOOL changed;
	OSTime ms, t;
	char abuf[0x100];
	Mtx scale;
	f32 v[9];
	f32 cv[5];

	entry = wp->entries;
	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		changed = FALSE;
		anim = (MapAnim*)entry->animData;
		for (j = 0; j < entry->numAnims; j++, anim++) {
			MapAnimList* jl = MAPENT_FIELD(anim->anim, MapAnimList*, 0xC);
			MapAnimList* ml = MAPENT_FIELD(anim->anim, MapAnimList*, 0x10);
			MapAnimList* al = MAPENT_FIELD(anim->anim, MapAnimList*, 0x14);
			MapAnimList* ll = MAPENT_FIELD(anim->anim, MapAnimList*, 0x18);
			MapAnimList* lc = MAPENT_FIELD(anim->anim, MapAnimList*, 0x1C);

			if (!(anim->flags & 1) || (anim->flags & 2)) {
				continue;
			}
			if (anim->flags & 0x100) {
				t = gp->systemLv0Time;
			}
			else if (anim->flags & 0x200) {
				t = gp->systemLv1Time;
			}
			else if (anim->flags & 0x400) {
				t = gp->systemLv2Time;
			}
			else if (anim->flags & 0x800) {
				t = gp->systemLv3Time;
			}
			else if (gp->inBattle) {
				t = gp->renderTime;
			}
			else {
				t = gp->renderFieldTime;
			}
			if (!(anim->flags & 0x10)) {
				ms = OSTicksToMilliseconds(t);
				cur = gp->framerate * (f32)(u64)(ms - anim->startTime) / 1000.0f;
				if (cur < anim->time) {
					anim->time = anim->time - (anim->time - cur);
				}
				else {
					anim->time = anim->time + anim->rate * (cur - anim->time);
				}
				anim->startTime = OSTicksToMilliseconds(t);
				anim->startTime -= (u64)(1000.0f * anim->time / gp->framerate);
			}
			else if (anim->flags & 0x20) {
				anim->startTime = OSTicksToMilliseconds(t);
				anim->startTime -= (u64)(1000.0f * anim->time / gp->framerate);
				anim->flags &= ~0x20;
				anim->flags &= ~0x10;
			}
			if (anim->time >= anim->anim->length) {
				if (anim->flags & 4) {
					f32 t2 = anim->time;
					while (t2 > anim->anim->length) {
						t2 -= anim->anim->length;
					}
					anim->time = t2;
					anim->startTime = OSTicksToMilliseconds(t);
					anim->startTime -= (u64)(1000.0f * anim->time / gp->framerate);
				}
				else {
					anim->time = anim->anim->length;
					anim->flags |= 2;
				}
			}
			if (jl) {
				for (k = 0; k < jl->count; k++) {
					o = mapGetMapObj((const char*)jl->items[k]->name);
					if (o) {
						mapCalcAnimMatrix(o->unk7C, o->localMtx, anim, (MapAnimJoint*)jl->items[k]);
						changed = TRUE;
						o->flags |= 0x2000;
						o->flags |= 0x200;
					}
				}
			}
			if (ml) {
				for (k = 0; k < ml->count; k++) {
					mapMainMat(anim, ml->items[k], mbuf, NULL);
					mapMainMat(anim, ml->items[k], mbuf, "_v");
					mapMainMat(anim, ml->items[k], mbuf, "_v_x");
				}
			}
			if (al) {
				for (k = 0; k < al->count; k++) {
					mapMainAlpha(anim, al->items[k], abuf, NULL);
					mapMainAlpha(anim, al->items[k], abuf, "_v");
					mapMainAlpha(anim, al->items[k], abuf, "_v_x");
				}
			}
			if (ll) {
				for (k = 0; k < ll->count; k++) {
					LightEntry* lp = lightNameToPtr((const char*)ll->items[k]->name);
					if (lp) {
						mapMainLight_ll(anim, lp, (MapAnimLightData*)ll->items[k], v);
					}
				}
			}
			if (lc) {
				for (k = 0; k < lc->count; k++) {
					LightEntry* lp = lightNameToPtr((const char*)lc->items[k]->name);
					if (lp) {
						mapMainLight_lc(anim, lp, (MapAnimLightData2*)lc->items[k], cv);
					}
				}
			}
		}
		if (changed) {
			PSMTXScale(scale, 1.0f, 1.0f, 1.0f);
			mapReCalcMatrix(entry->rootMapObj, scale, 0);
		}
	}
}
#endif
#ifndef NONMATCHING
void mapMain(void);
#endif

typedef struct MapTexXform {
	f32 tx;  // 0x0
	f32 ty;  // 0x4
	f32 sx;  // 0x8
	f32 sy;  // 0xC
	f32 rot; // 0x10
	f32 cx;  // 0x14
	f32 cy;  // 0x18
} MapTexXform;

typedef struct MapMatSampler {
	MapTexInfo* tex; // 0x0
	u8 pad4[4];      // 0x4
	u8 wrapS;        // 0x8
	u8 wrapT;        // 0x9
} MapMatSampler;

void mapSetMaterialLastStageBlend(s32 flags, GXColor color1, GXColor color2);
typedef struct MapMaterial {
	char* name;                  // 0x0
	GXColor color;               // 0x4
	u8 lightMode;                // 0x8
	u8 pad9[2];                  // 0x9
	u8 samplerCount;             // 0xB
	MapMatSampler* samplers[8];  // 0xC
	MapTexXform xforms[8];       // 0x2C
	GXColor blendColor;          // 0x10C, last-stage blend colour (translucency test, mapSetMaterialLastStageBlend)
	u8* tevMode;                 // 0x110
} MapMaterial;
void mapSetTextureMatrix(MapMaterial* mat);

void _mapDispMapObj(CameraId cam, MapObject *obj);
void _mapDispMapObj(CameraId cam, MapObject* obj);
static inline void mapSetObjFog(MapObject* obj);
void _mapDispMapGrp(CameraId cam, MapObject* obj);
void _mapDispMapGrp(CameraId cam, MapObject* obj);
void _mapDispMapGrp_NoMaterial(CameraId cam, MapObject* obj);
void _mapDispMapGrp_NoMaterial(CameraId cam, MapObject* obj);
void mapSetPolygon(MapObject* obj, MapFileMesh* mesh);
void mapSetPolygon(MapObject* obj, MapFileMesh* mesh);
extern const GXCullMode culling[4];
void mapSetMaterialLastStageBlend(s32 flags, GXColor color1, GXColor color2);
void mapSetTextureMatrix(MapMaterial* mat);
void mapSetTextureMatrix(struct MapMaterial* mat);
void mapSetPolygonVtxDesc(MapObject* obj, MapFileMesh* mesh);
void mapSetPolygonVtxDesc(MapObject* obj, MapFileMesh* mesh);

#ifdef NONMATCHING
static inline BOOL mapObjIsTranslucent(u32 flags, GXColor objColor, GXColor matColor) {
	if ((flags & 0x40) && objColor.a != 0xFF) {
		return TRUE;
	}
	if (matColor.a != 0xFF) {
		return TRUE;
	}
	if (!(flags & 0x800) && (mapGetWork()->entries[0].flags & 2) && mapGetWork()->entries[0].blend.a != 0xFF) {
		return TRUE;
	}
	if (!(flags & 0x1000) && (mapGetWork()->entries[0].flags & 4) && mapGetWork()->entries[0].blend2.a != 0xFF) {
		return TRUE;
	}
	return FALSE;
#endif
#ifndef NONMATCHING


void _mapDispMapObj(CameraId cam, MapObject *obj);


void _mapDispMapGrp(CameraId cam, MapObject* obj);

void mapDispMapObj(CameraId cam, MapObject* obj);

void mapDispMapGrp(CameraId cam, MapObject* obj);

void mapDispMapObj_off(CameraId cam, MapObject* obj);

void mapDispMapGrp_off(CameraId cam, MapObject* obj);

void test_kururing_mapdisp(CameraId cam);

void _mapDispMapObj_NoMaterial(CameraId cam, MapObject* obj);

void _mapDispMapGrp_NoMaterial(CameraId cam, MapObject* obj);

void mapDispMapObj_bbox(CameraId cam, MapObject* obj);

void mapDispMapGrp_bbox(CameraId cam, MapObject* obj);


void dispEntry(CameraId camera, f32 order, s32 renderMode, void* callback, void* param);
#define MAP_CLIP_IN(v) ((v).z > -1.0f && (v).z < 0.0f && (v).x >= -1.0f && (v).x <= 1.0f && (v).y >= -1.0f && (v).y <= 1.0f)
#define MJF(j, off) (*(f32*)((u8*)(j) + (off)))

void mapDisp(void);


typedef struct MapFileLight {
	const char* name; // 0x0
} MapFileLight;

typedef struct MapFileLightTable {
	s32 count;              // 0x0
	MapFileLight* lights[]; // 0x4
} MapFileLightTable;

#define MAP_LIGHT_TABLE(entry) ((MapFileLightTable*)(entry)->lightTable)

s32 mapSetLight(MapObject* obj, LightEntry** lights);


static u32 texture_0[64] ATTRIBUTE_ALIGN(32) = {
	0xEB88E228, 0x55FFAA00, 0x00000000, 0x00000000,
	0xF528EC08, 0x55FFAA00, 0x00000000, 0x00000000,
	0xFEE8F5A8, 0x55FFAA00, 0x00000000, 0x00000000,
	0xFF47D6E8, 0x00AAFF55, 0x00000000, 0x00000000,
	0xBEA8860A, 0x00AAFF55, 0x00000000, 0x00000000,
	0x7DEA0D8B, 0x00AAFF55, 0x00000000, 0x00000000,
	0x056B054A, 0x00AAAA00, 0x00000000, 0x00000000,
	0x056B054E, 0x0000AAFF, 0x00000000, 0x00000000,
	0x05BA0570, 0x55FFAAAA, 0x00000000, 0x00000000,
	0x05DE05BA, 0x55FFAAAA, 0x00000000, 0x00000000,
	0x05BD051B, 0x0000AA55, 0x00000000, 0x00000000,
	0x1376049A, 0x55FFAA00, 0x00000000, 0x00000000,
	0x33154253, 0x00AA5555, 0x00000000, 0x00000000,
	0x6A333A53, 0xFFFFAA00, 0x00000000, 0x00000000,
	0xB1F28212, 0x55FFAA00, 0x00000000, 0x00000000,
	0xE9F2C212, 0x55FFAA00, 0x00000000, 0x00000000,
};
__declspec(section ".data") static void* jumptable_803033E0[] = {
    (char*)mapSetMaterialTev + 0x58,
    (char*)mapSetMaterialTev + 0x90,
    (char*)mapSetMaterialTev + 0x23C,
    (char*)mapSetMaterialTev + 0x594,
    (char*)mapSetMaterialTev + 0x740,
    (char*)mapSetMaterialTev + 0x8EC,
    (char*)mapSetMaterialTev + 0xB24,
    (char*)mapSetMaterialTev + 0xCD0,
    (char*)mapSetMaterialTev + 0xE7C,
    (char*)mapSetMaterialTev + 0xF80,
    (char*)mapSetMaterialTev + 0x12A4,
    (char*)mapSetMaterialTev + 0x12A4,
    (char*)mapSetMaterialTev + 0x3E8,
};
__declspec(section ".data") void* jumptable_80303414[] = {
    (char*)mapBuildTexture + 0x134,
    (char*)mapBuildTexture + 0x144,
    (char*)mapBuildTexture + 0x154,
    (char*)mapBuildTexture + 0x164,
    (char*)mapBuildTexture + 0xF4,
    (char*)mapBuildTexture + 0x104,
    (char*)mapBuildTexture + 0x114,
    (char*)mapBuildTexture + 0x1A0,
    (char*)mapBuildTexture + 0x174,
    (char*)mapBuildTexture + 0x184,
    (char*)mapBuildTexture + 0x194,
    (char*)mapBuildTexture + 0x1A0,
    (char*)mapBuildTexture + 0x1A0,
    (char*)mapBuildTexture + 0x1A0,
    (char*)mapBuildTexture + 0x124,
};

#pragma push
#pragma opt_lifetimes off
void mapSetMaterialTev(s32 texCount, s32 drawMode, s32 flags, Mtx mtx);
#pragma pop

void mapSetMaterialLastStageBlend(s32 flags, GXColor color1, GXColor color2);

void mapSetMaterialFog(void);




LightEntry* lightGetAmbient(void);

void mapSetTextureMatrix(MapMaterial* mat);


void mapSetMaterial(MapObject* obj, void* material);

void mapSetPaperAmbColor(GXColor* color);

void mapResetPaperAmbColor(void);


void mapSetMaterialLight(s32 flags, Vec position);

typedef struct MapVcdTable {
	void* positions;          // 0x0
	void* normals;            // 0x4
	u8 field_0x8[0xC - 0x8];  // 0x8
	void* colors[2];          // 0xC
	s32 texCount;             // 0x14
	void* texCoords[8];       // 0x18
} MapVcdTable;

typedef struct MapVtxFmtInfo {
	u8 field_0x0[0x44 - 0x0]; // 0x0
	s32 posFrac;              // 0x44
	s32 texFrac[8];           // 0x48
} MapVtxFmtInfo;

#define MAP_VTXFMT(entry) ((MapVtxFmtInfo*)(entry)->vcdTable)

typedef struct MapVtxRec {
	s16 pos;     // 0x0
	s16 nrm;     // 0x2
	s16 clr;     // 0x4
	s16 unk6;    // 0x6
	s16 tex[8];  // 0x8
} MapVtxRec;

typedef struct MapRawDL {
	s32 count;        // 0x0

	MapVtxRec vtx[];  // 0x4
} MapRawDL;


void mapSetPolygon(MapObject* obj, MapFileMesh* mesh);

void mapSetPolygonVtxDesc(MapObject* obj, MapFileMesh* mesh);

MapFileJoint* mapSearchDmdJointSub(MapFileJoint* joint, const char* name);

MapFileJoint* mapSearchDmdJointSub2(MapFileJoint* joint, const char* name, const char* prefix);

MapFileJoint* mapSearchDmdJoint(MapFileJoint* joint, const char* name);

MapObject* mapGetMapObj(const char *name);

void mapObjFlagOn(const char* name, u32 flags);

void mapObjFlagOff(const char* name, u32 flags);

void mapFlgOn(MapObject* obj, u32 flags, BOOL doNext);

void mapFlgOff(MapObject* obj, u32 flags, BOOL doNext);

void mapGrpFlagOn(const char* name, u32 flags);

void mapGrpFlagOff(const char* name, u32 flags);

void _setOffScrnId(MapObject* obj, s32 id, BOOL doNext);

void mapObjSetOffScreen(const char* name, const char* offscreen);

void mapGrpSetOffScreen(const char* name, const char* offscreen);

void mapObjClearOffScreen(const char* name);

void mapGrpClearOffScreen(const char* name);


void mapObjRotate(const char* name, f32 x, f32 y, f32 z);

void mapObjTranslate(const char* name, f32 x, f32 y, f32 z);

void mapObjScale(const char* name, f32 x, f32 y, f32 z);

void mapObjGetPosSub(MapObject* obj, Vec* sum, s32* count, BOOL doNext);

void mapObjGetPos(const char* name, Vec* pos);

void mapSetFog(s32 type, f32 start, f32 end, GXColor color);

void mapGetFog(s32* type, f32* start, f32* end, GXColor* color);

void mapFogOn(void);

void mapFogOff(void);

void mapSetBlend(GXColor* color);

void mapSetBlend2(GXColor* color);

void mapGetBlend(GXColor* color);

void mapGetBlend2(GXColor* color);

void mapBlendOff(void);

void mapBlendOff2(void);

void mapObjSetColor(const char* name, GXColor* color);

void setColor(MapObject* obj, GXColor color, BOOL doNext);

void mapGrpSetColor(const char* name, GXColor color);

void mapSetProjTexObj(GXTexObj* obj, void* imgRef);

void mapSetProjMtx(Mtx mtx);

extern int __float_nan[];

void spline_maketable(s32 n, Vec* pts, f32* t, Vec* out);

void spline_getvalue(Vec* out, f32 t, s32 n, Vec* pts, f32* ts, Vec* tbl);

BOOL mapTestXLU(u32 flags, GXColor* color, GXColor* matColor);

void mapSetTevCallback(s32 index, MapTevCallback callback);

void mapObjFlushOn(const char* name);

void mapObjFlushOff(const char* name);

void mapGrpFlushOn(const char* name);

void mapGrpFlushOff(const char* name);

void mapObjSetFlushColor(const char* name, u8 r, u8 g, u8 b, u8 a);

void mapGrpSetFlushColor(const char* name, u8 r, u8 g, u8 b, u8 a);

void mapObjGetFlushColor(const char* name, u8* r, u8* g, u8* b, u8* a);

// Stand-in for a function the original linker dead-stripped; it only keeps the
// constants that function left behind in .rodata/.sdata2 in their original order.

#pragma force_active on
#pragma explicit_zero_data on
__declspec(section ".sdata") u32 gap_07_8040F3F4_sdata[3] = {0};
#pragma explicit_zero_data reset
#pragma force_active reset



// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_05_80303450_data[4] = {0};
#pragma force_active reset

static inline MapWork* mapGetWork__af_inl(void) {
	return &mapWork[activeGroup];
#endif
}

#ifdef NONMATCHING
static inline void callPackedLists(MapFileMesh* mesh) {
  int j;
  for (j = 0; j < mesh->displayListCount; j++)
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
asm void mapObjGetFlushColor(const char* name, u8* r, u8* g, u8* b, u8* a) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r22, 0x8(r1)
	mr. r31, r3
	mr r22, r4
	mr r23, r5
	mr r24, r6
	mr r25, r7
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r27, r3, r0
	bne L_af_1
	li r30, 0x0
	b L_af_2
L_af_1:
	mr r26, r27
	li r29, 0x0
	b L_af_3
L_af_4:
	lwz r30, 0x154(r26)
	li r28, 0x0
	b L_af_5
L_af_6:
	lwz r3, 0x8(r30)
	mr r4, r31
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
L_af_7:
	addi r28, r28, 0x1
	addi r30, r30, 0x134
L_af_5:
	lwz r0, 0x150(r26)
	cmpw r28, r0
	blt L_af_6
	addi r26, r26, 0x178
	addi r29, r29, 0x1
L_af_3:
	lwz r0, 0x0(r27)
	cmpw r29, r0
	blt L_af_4
	li r30, 0x0
L_af_2:
	cmplwi r30, 0x0
	bne L_af_8
	lwz r0, error_count(r13)
	lis r3, error_data@ha
	addi r3, r3, error_data@l
	li r6, 0x0
	mulli r0, r0, 0x24
	mr r4, r31
	li r5, 0x1f
	add r3, r3, r0
	stw r6, 0x20(r3)
	bl strncpy
	lwz r3, error_count(r13)
	li r0, 0x1
	stw r0, error_flag(r13)
	addi r3, r3, 0x1
	slwi r0, r3, 27
	stw r3, error_count(r13)
	srwi r3, r3, 31
	subf r0, r3, r0
	rotlwi r0, r0, 5
	add r0, r0, r3
	stw r0, error_count(r13)
	b L_af_9
L_af_8:
	lbz r0, 0xc(r30)
	stb r0, 0x0(r22)
	lbz r0, 0xd(r30)
	stb r0, 0x0(r23)
	lbz r0, 0xe(r30)
	stb r0, 0x0(r24)
	lbz r0, 0xf(r30)
	stb r0, 0x0(r25)
L_af_9:
	lmw r22, 0x8(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
void mapGrpFlushOn(const char* name) {
	mapGrpFlagOn(name, 0x100000);
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
void mapGrpFlushOff(const char* name) {
	mapGrpFlagOff(name, 0x100000);
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void mapObjSetFlushColor(const char* name, u8 r, u8 g, u8 b, u8 a) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0xBF410018
		opword 0x7C7F1B79
		lwz r8, unk_80422f8c(r2)
		lwz r0, activeGroup(r13)
		opword 0x91010008
		opword 0x1C0002F4
		lwz r3, mapWork(r13)
		opword 0x98810008
		opword 0x98A10009
		opword 0x7F630214
		opword 0x98C1000A
		opword 0x98E1000B
		opword 0x4082000C
		opword 0x3BC00000
		opword 0x48000064
		opword 0x7F7ADB78
		opword 0x3BA00000
		opword 0x48000048
		opword 0x83DA0154
		opword 0x3B800000
		opword 0x48000028
		opword 0x807E0008
		opword 0x7FE4FB78
		opword 0x80630000
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x48000030
		opword 0x3B9C0001
		opword 0x3BDE0134
		opword 0x801A0150
		opword 0x7C1C0000
		opword 0x4180FFD4
		opword 0x3B5A0178
		opword 0x3BBD0001
		opword 0x801B0000
		opword 0x7C1D0000
		opword 0x4180FFB4
		opword 0x3BC00000
		opword 0x281E0000
		opword 0x41820018
		opword 0x80010008
		opword 0x901E000C
		opword 0x801E0000
		opword 0x60000040
		opword 0x901E0000
		lwz r0, activeGroup(r13)
		opword 0x281F0000
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7F630214
		opword 0x4082000C
		opword 0x3B800000
		opword 0x48000064
		opword 0x7F7ADB78
		opword 0x3BA00000
		opword 0x48000048
		opword 0x839A0154
		opword 0x3BC00000
		opword 0x48000028
		opword 0x807C0008
		opword 0x7FE4FB78
		opword 0x80630000
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x48000030
		opword 0x3BDE0001
		opword 0x3B9C0134
		opword 0x801A0150
		opword 0x7C1E0000
		opword 0x4180FFD4
		opword 0x3B5A0178
		opword 0x3BBD0001
		opword 0x801B0000
		opword 0x7C1D0000
		opword 0x4180FFB4
		opword 0x3B800000
		opword 0x281C0000
		opword 0x4082005C
		lwz r0, error_count(r13)
		lis r3, error_data@ha
		addi r3, r3, error_data@l
		opword 0x38C00000
		opword 0x1C000024
		opword 0x7FE4FB78
		opword 0x38A0001F
		opword 0x7C630214
		opword 0x90C30020
		bl strncpy
		lwz r3, error_count(r13)
		opword 0x38000001
		stw r0, error_flag(r13)
		opword 0x38630001
		opword 0x5460D808
		stw r3, error_count(r13)
		opword 0x54630FFE
		opword 0x7C030050
		opword 0x5400283E
		opword 0x7C001A14
		stw r0, error_count(r13)
		opword 0x48000010
		opword 0x801C0000
		opword 0x540006B0
		opword 0x901C0000
		opword 0xBB410018
		opword 0x80010034
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#pragma defer_codegen off
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void mapGrpSetFlushColor(const char* name, u8 r, u8 g, u8 b, u8 a) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x93E1001C
		opword 0x7C7F1B78
		lwz r0, unk_80422f90(r2)
		opword 0x90010008
		opword 0x98810008
		opword 0x3881000C
		opword 0x98A10009
		opword 0x98C1000A
		opword 0x98E1000B
		opword 0x80010008
		opword 0x9001000C
		bl mapGrpSetColor
		opword 0x7FE3FB78
		opword 0x38800040
		bl mapGrpFlagOff
		opword 0x80010024
		opword 0x83E1001C
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop

#pragma defer_codegen reset

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
asm void mapObjFlushOff(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr. r26, r3
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r28, r3, r0
	bne L_af_1
	li r31, 0x0
	b L_af_2
L_af_1:
	mr r27, r28
	li r30, 0x0
	b L_af_3
L_af_4:
	lwz r31, 0x154(r27)
	li r29, 0x0
	b L_af_5
L_af_6:
	lwz r3, 0x8(r31)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
L_af_7:
	addi r29, r29, 0x1
	addi r31, r31, 0x134
L_af_5:
	lwz r0, 0x150(r27)
	cmpw r29, r0
	blt L_af_6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
L_af_3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt L_af_4
	li r31, 0x0
L_af_2:
	cmplwi r31, 0x0
	bne L_af_8
	lwz r0, error_count(r13)
	lis r3, error_data@ha
	addi r3, r3, error_data@l
	li r6, 0x0
	mulli r0, r0, 0x24
	mr r4, r26
	li r5, 0x1f
	add r3, r3, r0
	stw r6, 0x20(r3)
	bl strncpy
	lwz r3, error_count(r13)
	li r0, 0x1
	stw r0, error_flag(r13)
	addi r3, r3, 0x1
	slwi r0, r3, 27
	stw r3, error_count(r13)
	srwi r3, r3, 31
	subf r0, r3, r0
	rotlwi r0, r0, 5
	add r0, r0, r3
	stw r0, error_count(r13)
	b L_af_9
L_af_8:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 12, 10
	stw r0, 0x0(r31)
L_af_9:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
asm void mapObjFlushOn(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr. r26, r3
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r28, r3, r0
	bne L_af_1
	li r31, 0x0
	b L_af_2
L_af_1:
	mr r27, r28
	li r30, 0x0
	b L_af_3
L_af_4:
	lwz r31, 0x154(r27)
	li r29, 0x0
	b L_af_5
L_af_6:
	lwz r3, 0x8(r31)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
L_af_7:
	addi r29, r29, 0x1
	addi r31, r31, 0x134
L_af_5:
	lwz r0, 0x150(r27)
	cmpw r29, r0
	blt L_af_6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
L_af_3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt L_af_4
	li r31, 0x0
L_af_2:
	cmplwi r31, 0x0
	bne L_af_8
	lwz r0, error_count(r13)
	lis r3, error_data@ha
	addi r3, r3, error_data@l
	li r6, 0x0
	mulli r0, r0, 0x24
	mr r4, r26
	li r5, 0x1f
	add r3, r3, r0
	stw r6, 0x20(r3)
	bl strncpy
	lwz r3, error_count(r13)
	li r0, 0x1
	stw r0, error_flag(r13)
	addi r3, r3, 0x1
	slwi r0, r3, 27
	stw r3, error_count(r13)
	srwi r3, r3, 31
	subf r0, r3, r0
	rotlwi r0, r0, 5
	add r0, r0, r3
	stw r0, error_count(r13)
	b L_af_9
L_af_8:
	lwz r0, 0x0(r31)
	oris r0, r0, 0x10
	stw r0, 0x0(r31)
L_af_9:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#define mapGetWork mapGetWork__af_inl
void bmapLoad(const char *map, const char *map2)
{
  MapWork *wp;
  MapEntry *entry;
  MapEntry *e;
  int i;
  sysWaitDrawSync();
  activeGroup = 0;
  wp = mapGetWork();
  for (i = 0; i < wp->entries[0].count; i++)
#endif
  {
#ifdef NONMATCHING
    GXCallDisplayList((void *) mesh->displayLists.packedLists[j].offset, *((u32 *) (&mesh->displayLists.packedLists[j].vertexCount)));
#endif
#ifndef NONMATCHING
    e = &mapWork[activeGroup].entries[i];
    entry = &wp->entries[i];
    if (e->dispListBuf)
    {
      _mapFree(e->dispListBuf);
    }
    e->dispListSize = 0;
    e->dispListBuf = (void *) 0;
    // NB: +0x178 is past sizeof(MapEntry) (0x178): it is the next entry's count (or MapWork.field_2F0 for entry 1).
    // The original strides entries by 0x178 everywhere, so this matches the game; the real layout is probably
    // MapWork { s32 count; entries } with a tplAram as each entry's last field (all MapEntry offsets +4).
    entry->datAram = (void *) 0;
    *((void **) (((u8 *) entry) + 0x178)) = (void *) 0;
    entry->arcAram = (void *) 0;
    if (entry->dat)
    {
      if (!arcDataCheck(entry->dat))
      {
        entry->datAram = aramMgrToAram(entry->dat, entry->datSize);
        *((ARAMEntry **) (((u8 *) entry) + 0x178)) = aramMgrToAram(entry->tpl, entry->tplSize);
        _mapFree(entry->tpl);
        _mapFree(entry->dat);
        entry->tpl = (void *) 0;
        entry->dat = (void *) 0;
      }
      else
      {
        entry->arcAram = aramMgrToAram(entry->arcData, entry->arcSize);
        _mapFree(entry->arcData);
        entry->arcData = (void *) 0;
      }
    }
  }

  wp = (0, &mapWork[1]);
  activeGroup = 1;
  memset(wp, 0, sizeof(MapWork));
  _mapLoad(wp, 0, map);
  wp->entries[0].count = 1;
  if (map2)
  {
    _mapLoad(wp, 1, map2);
    wp->entries[0].count = 2;
#endif
  }
}

#ifdef NONMATCHING
void _mapDispMapObj(CameraId cam, MapObject *obj)
{
  CameraEntry *camera;
  CameraEntry *cur;
  MapFileJoint *joint;
  f32 scale;
  s32 n;
  s32 mode;
  GXCullMode cull;
  f32 d;
  Mtx mtx;
  Mtx nrm;
  f32 proj[7];
  MapFileMesh *mesh;
  int i;
  MapWork *wp;
  int j;
  void *material;
  camera = camGetPtr(cam);
  current_mp = obj;
  if (!(obj->flags & 0x20))
  {
    goto setup;
  }
  if (obj->flags & 0x8000)
  {
    n = 0;
    for (joint = obj->joints; joint->prev; joint = joint->prev)
    {
    }
#endif
#ifndef NONMATCHING
#undef mapGetWork
#endif

#ifdef NONMATCHING
    for (; joint != obj->joints; joint = joint->next)
    {
      n++;
    }
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifdef NONMATCHING
    scale = 0.01f * n;
    GXGetProjectionv(proj);
    d = 1.0f;
    d = (d * (camera->far + camera->near)) * (d + scale);
    proj[5] *= 1.0f + ((scale * (((-2.0f) * camera->far) * camera->near)) / d);
    GXSetProjectionv(proj);
  }
  mode = obj->blendMode;
  if (obj->joints->partCount > 0)
  {
    if (mapObjIsTranslucent(obj->flags, obj->color, *((GXColor *) (((u8 *) obj->joints->parts[0].material) + 0x10C))))
    {
      mode = 2;
    }
  }
  switch (mode)
  {
    case 0:
      GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, 7);
      GXSetZCompLoc((GXBool) 1);
      GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
      GXSetZMode((GXBool) 1, GX_LEQUAL, (GXBool) 1);
      break;
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void mapCalcAnimMatrix(Mtx out, Mtx in, MapAnim* anim, MapAnimJoint* joint) {
	asm volatile {
		opword 0x9421FDE0
		opword 0x7C0802A6
		opword 0x90010224
		opword 0xDBE10210
		opword 0xF3E10218
		opword 0xDBC10200
		opword 0xF3C10208
		opword 0xDBA101F0
		opword 0xF3A101F8
		opword 0xDB8101E0
		opword 0xF38101E8
		opword 0xDB6101D0
		opword 0xF36101D8
		opword 0xDB4101C0
		opword 0xF34101C8
		opword 0xDB2101B0
		opword 0xF32101B8
		opword 0xDB0101A0
		opword 0xF30101A8
		opword 0xDAE10190
		opword 0xF2E10198
		opword 0x93E1018C
		opword 0x93C10188
		opword 0x80E60058
		opword 0x7C7E1B78
		opword 0x7C9F2378
		opword 0x388601A8
		opword 0x3807FFFF
		opword 0x39000001
		opword 0x7C0903A6
		opword 0x2C070001
		opword 0x40810300
		opword 0x3924005C
		opword 0x3868FFFF
		opword 0xC0050010
		opword 0x1C6301A8
		opword 0xC024005C
		opword 0xFC000840
		opword 0x38E3005C
		opword 0x7CE63A14
		opword 0x4C401382
		opword 0x4082000C
		opword 0xFDA00090
		opword 0x48000010
		opword 0x7C080000
		opword 0x408202BC
		opword 0xFDA00890
		opword 0x38000009
		opword 0x7CE33B78
		opword 0x7D254B78
		opword 0x38810128
		opword 0x7C0903A6
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820010
		opword 0xC0030004
		opword 0xD0040000
		opword 0x480000A4
		opword 0xC0670000
		opword 0xC0290000
		lfs f0, float_0_80419850(r2)
		opword 0xEC4D1828
		opword 0xED611828
		opword 0xC1450008
		opword 0xC1250004
		opword 0xC103000C
		opword 0xFC0B0000
		opword 0xC0E30004
		opword 0x7C000026
		opword 0x54001FFE
		opword 0x68000001
		opword 0x7C000034
		opword 0x5400D97F
		opword 0x4182000C
		lfs f0, float_1Eneg08_804198b8(r2)
		opword 0x48000008
		opword 0xFC005890
		opword 0xECC20024
		lfs f1, float_2_80419858(r2)
		lfs f0, float_3_8041984c(r2)
		lfs f2, float_1_80419860(r2)
		lfs f3, float_neg2_804198a0(r2)
		opword 0xEC8601B2
		opword 0xECA401B2
		opword 0xED800132
		opword 0xEC01293C
		opword 0xEC216178
		opword 0xEC852028
		opword 0xEC06002A
		opword 0xEC22082A
		opword 0xEC43617A
		opword 0xEC0B0032
		opword 0xEC6B0132
		opword 0xEC080032
		opword 0xEC07007A
		opword 0xEC0900BA
		opword 0xEC0A00FA
		opword 0xD0040000
		opword 0x38630014
		opword 0x38840004
		opword 0x38A50014
		opword 0x4200FF3C
		opword 0xC0210140
		opword 0xC006001C
		opword 0xC0610144
		opword 0xC0460020
		opword 0xEF410024
		opword 0xC0210148
		opword 0xC0060024
		opword 0xC1810128
		opword 0xC1660004
		opword 0xC141012C
		opword 0xC1260008
		opword 0xEF231024
		opword 0xC1010130
		opword 0xC0E6000C
		opword 0xC0C10134
		opword 0xC0A60010
		opword 0xC0810138
		opword 0xC0660014
		opword 0xEF010024
		opword 0xC041013C
		opword 0xC0260018
		lfs f0, float_0_80419850(r2)
		opword 0xEFEC5828
		opword 0xEFCA4828
		opword 0xEFA83828
		opword 0xFC1F0000
		opword 0xEF862828
		opword 0xEF641828
		opword 0xEEE20828
		opword 0x40820014
		opword 0xFC1E0000
		opword 0x4082000C
		opword 0xFC1D0000
		opword 0x41820018
		opword 0xFC20F890
		opword 0x386100F8
		opword 0xFC40F090
		opword 0xFC60E890
		bl PSMTXTrans
		lfs f0, float_0_80419850(r2)
		opword 0xFC1C0000
		opword 0x41820018
		lfs f0, float_deg2rad_80419868(r2)
		opword 0x38610098
		opword 0x38800078
		opword 0xEC200732
		bl PSMTXRotRad
		lfs f0, float_0_80419850(r2)
		opword 0xFC1B0000
		opword 0x41820018
		lfs f0, float_deg2rad_80419868(r2)
		opword 0x38610068
		opword 0x38800079
		opword 0xEC2006F2
		bl PSMTXRotRad
		lfs f0, float_0_80419850(r2)
		opword 0xFC170000
		opword 0x41820018
		lfs f0, float_deg2rad_80419868(r2)
		opword 0x38610038
		opword 0x3880007A
		opword 0xEC2005F2
		bl PSMTXRotRad
		opword 0xFC20D090
		opword 0x386100C8
		opword 0xFC40C890
		opword 0xFC60C090
		bl PSMTXScale
		opword 0x38610008
		bl PSMTXIdentity
		lfs f0, float_0_80419850(r2)
		opword 0xFC1F0000
		opword 0x40820014
		opword 0xFC1E0000
		opword 0x4082000C
		opword 0xFC1D0000
		opword 0x41820014
		opword 0x38610008
		opword 0x388100F8
		opword 0x7C651B78
		bl PSMTXConcat
		lfs f0, float_0_80419850(r2)
		opword 0xFC170000
		opword 0x41820014
		opword 0x38610008
		opword 0x38810038
		opword 0x7C651B78
		bl PSMTXConcat
		lfs f0, float_0_80419850(r2)
		opword 0xFC1B0000
		opword 0x41820014
		opword 0x38610008
		opword 0x38810068
		opword 0x7C651B78
		bl PSMTXConcat
		lfs f0, float_0_80419850(r2)
		opword 0xFC1C0000
		opword 0x41820014
		opword 0x38610008
		opword 0x38810098
		opword 0x7C651B78
		bl PSMTXConcat
		lfs f0, float_0_80419850(r2)
		opword 0xFC1A0000
		opword 0x40820014
		opword 0xFC190000
		opword 0x4082000C
		opword 0xFC180000
		opword 0x41820014
		opword 0x38610008
		opword 0x388100C8
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x7FE3FB78
		opword 0x7FC5F378
		opword 0x38810008
		bl PSMTXConcat
		opword 0x48000010
		opword 0x388401A8
		opword 0x39080001
		opword 0x4200FD08
		opword 0xE3E10218
		opword 0xCBE10210
		opword 0xE3C10208
		opword 0xCBC10200
		opword 0xE3A101F8
		opword 0xCBA101F0
		opword 0xE38101E8
		opword 0xCB8101E0
		opword 0xE36101D8
		opword 0xCB6101D0
		opword 0xE34101C8
		opword 0xCB4101C0
		opword 0xE32101B8
		opword 0xCB2101B0
		opword 0xE30101A8
		opword 0xCB0101A0
		opword 0xE2E10198
		opword 0xCAE10190
		opword 0x83E1018C
		opword 0x80010224
		opword 0x83C10188
		opword 0x7C0803A6
		opword 0x38210220
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    case 3:
      GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, 0);
      GXSetZCompLoc((GXBool) 1);
      GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
      GXSetZMode((GXBool) 0, GX_LEQUAL, (GXBool) 0);
      break;
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifdef NONMATCHING
    case 1:
      GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, 0);
      GXSetZCompLoc((GXBool) 0);
      GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
      GXSetZMode((GXBool) 1, GX_LEQUAL, (GXBool) 1);
      break;
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
void mapReCalcMatrix(MapObject* obj, Mtx mtx, BOOL force) {
	BOOL dirty = FALSE;
#endif

#ifdef NONMATCHING
    case 4:
      GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, 0);
      GXSetZCompLoc((GXBool) 0);
      GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
      GXSetZMode((GXBool) 0, GX_LEQUAL, (GXBool) 0);
      break;

    case 2:

    case 5:

    default:
      GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, 0);
      GXSetZCompLoc((GXBool) 1);
      GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
      GXSetZMode((GXBool) 1, GX_LEQUAL, (GXBool) 0);
      break;

  }

  setup:
  if (cam == 1)
  {
    GXSetZCompLoc((GXBool) 0);
  }

  PSMTXConcat(camera->view, obj->modelWorldMtx, mtx);
  GXLoadPosMtxImm(mtx, 0);
  if (!(obj->flags & 0x100))
  {
    PSMTXInvXpose(mtx, nrm);
    GXLoadNrmMtxImm(nrm, 0);
  }
  GXSetCurrentMtx(0);
  GXGetCullMode(&cull);
  if (cull != culling[obj->joints->drawMode->cullMode])
  {
    GXSetCullMode(culling[obj->joints->drawMode->cullMode]);
  }
  mapSetObjFog(obj);
  if (obj->flags & 0x20)
  {
    if (obj->flags & 0x4000)
    {
      goto end;
    }
    if ((obj->flags & 1) && (!(obj->flags & 0x80)))
    {
      goto end;
    }
    if ((obj->flags & 0x40) && (obj->color.a == 0))
    {
      goto end;
    }
  }
  if (obj->flags & 0x100)
  {
    for (i = 0; i < obj->joints->partCount; i++)
    {
      mesh = obj->joints->parts[i].mesh;
      material = obj->joints->parts[i].material;
      mapSetTextureMatrix(material);
      mapSetMaterialLastStageBlend(obj->flags, obj->color, *((GXColor *) (((u8 *) material) + 0x10C)));
      mapSetPolygonVtxDesc(obj, mesh);
      GXCallDisplayList(((MapObjectDL *) obj)->dl[i], ((MapObjectDL *) obj)->dlSize[i]);
      callPackedLists(mesh);

    }

  }
  else
  {
    for (i = 0; i < obj->joints->partCount; i++)
    {
      material = obj->joints->parts[i].material;
      mesh = obj->joints->parts[i].mesh;
      mapSetTextureMatrix(material);
      mapSetMaterialLastStageBlend(obj->flags, obj->color, *((GXColor *) (((u8 *) material) + 0x10C)));
      mapSetMaterial(obj, material);
      mapSetPolygon(obj, mesh);
    }

  }
  end:
  if (obj->flags & 0x8000)
  {
    GXSetProjection(camera->projection, camera->projType);
  }

  if (obj->flags & 0x0F000000)
  {
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
    GXSetTevDirect(GX_TEVSTAGE2);
    GXSetTevDirect(GX_TEVSTAGE3);
    GXSetTevDirect(GX_TEVSTAGE4);
    GXSetNumIndStages(0);
  }
#endif
#ifndef NONMATCHING
	if (obj->flags & 0x200) {
		dirty = TRUE;
	}
	if (force) {
		dirty = TRUE;
	}
	if (dirty) {
		if (obj->flags & 0x2000) {
			PSMTXConcat(mtx, obj->unk7C, obj->modelWorldMtx);
		}
		else {
			PSMTXConcat(mtx, obj->localMtx, obj->modelWorldMtx);
		}
		if (obj->flags & 0x200000) {
			PSMTXConcat(obj->modelWorldMtx, obj->unkAC, obj->modelWorldMtx);
		}
		obj->flags &= ~0x200;
		if (obj->child) {
			mapReCalcMatrix(obj->child, obj->modelWorldMtx, TRUE);
		}
		if (obj->next) {
			mapReCalcMatrix(obj->next, mtx, force);
		}
	}
	else {
		if (obj->child) {
			mapReCalcMatrix(obj->child, obj->modelWorldMtx, force);
		}
		if (obj->next) {
			mapReCalcMatrix(obj->next, mtx, force);
		}
	}
#endif
}

#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void mapMain(void) {
	asm volatile {
		opword 0x9421FD20
		opword 0x7C0802A6
		opword 0x900102E4
		opword 0xBDC10298
		opword 0x39C00000
		lwz r0, activeGroup(r13)
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7C030214
		opword 0x90010288
		opword 0x7C180378
		opword 0x48001528
		opword 0x82B80164
		opword 0x3A800000
		opword 0x3AE00000
		opword 0x480014D8
		opword 0xA0950000
		opword 0x80750018
		opword 0x548007FF
		opword 0x8263000C
		opword 0x82430010
		opword 0x82230014
		opword 0x82030018
		opword 0x81E3001C
		opword 0x418214AC
		opword 0x548007BD
		opword 0x408214A4
		opword 0x548005EF
		opword 0x41820014
		lwz r3, gp(r13)
		opword 0x82C30048
		opword 0x8323004C
		opword 0x48000070
		opword 0x548005AD
		opword 0x41820014
		lwz r3, gp(r13)
		opword 0x82C30050
		opword 0x83230054
		opword 0x48000058
		opword 0x5480056B
		opword 0x41820014
		lwz r3, gp(r13)
		opword 0x82C30058
		opword 0x8323005C
		opword 0x48000040
		opword 0x54800529
		opword 0x41820014
		lwz r3, gp(r13)
		opword 0x82C30060
		opword 0x83230064
		opword 0x48000028
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820010
		opword 0x82C30038
		opword 0x8323003C
		opword 0x4800000C
		opword 0x82C30040
		opword 0x83230044
		opword 0x548006F7
		opword 0x40820130
		opword 0x3C808000
		opword 0x3C601062
		opword 0x800400F8
		opword 0x38C34DD3
		opword 0x7EC3B378
		opword 0x7F24CB78
		opword 0x5400F0BE
		opword 0x38A00000
		opword 0x7C060016
		opword 0x5406D1BE
		bl __div2i
		opword 0x80B5000C
		opword 0x80150008
		opword 0x7C852010
		opword 0x7C601910
		bl __cvt_ull_flt
		lwz r4, gp(r13)
		opword 0x3C004330
		opword 0x90010270
		lis r3, double_to_int_802c1998@ha
		opword 0x80040004
		lfd f3, double_to_int_802c1998@l(r3)
		opword 0x6C008000
		lfs f0, float_1000_80419874(r2)
		opword 0x90010274
		opword 0xC0950010
		opword 0xC8410270
		opword 0xEC421828
		opword 0xEC220072
		opword 0xEC010024
		opword 0xFC002040
		opword 0x40800014
		opword 0xEC040028
		opword 0xEC040028
		opword 0xD0150010
		opword 0x48000014
		opword 0xEC002028
		opword 0xC0350014
		opword 0xEC01203A
		opword 0xD0150010
		opword 0x3C808000
		opword 0x3C601062
		opword 0x800400F8
		opword 0x38C34DD3
		opword 0x7EC3B378
		opword 0x7F24CB78
		opword 0x5400F0BE
		opword 0x38A00000
		opword 0x7C060016
		opword 0x5406D1BE
		bl __div2i
		opword 0x9095000C
		opword 0x3C004330
		lis r4, double_to_int_802c1998@ha
		lfs f2, float_1000_80419874(r2)
		opword 0x90750008
		lfd f1, double_to_int_802c1998@l(r4)
		lwz r3, gp(r13)
		opword 0xC0150010
		opword 0x80630004
		opword 0x90010270
		opword 0xEC420032
		opword 0x6C608000
		opword 0x90010274
		opword 0xC8010270
		opword 0xEC000828
		opword 0xEC220024
		bl __cvt_dbl_usll
		opword 0x8015000C
		opword 0x80B50008
		opword 0x7C040010
		opword 0x9015000C
		opword 0x7C032910
		opword 0x90150008
		opword 0x480000AC
		opword 0x548006B5
		opword 0x418200A4
		opword 0x3C808000
		opword 0x3C601062
		opword 0x800400F8
		opword 0x38C34DD3
		opword 0x7EC3B378
		opword 0x7F24CB78
		opword 0x5400F0BE
		opword 0x38A00000
		opword 0x7C060016
		opword 0x5406D1BE
		bl __div2i
		opword 0x9095000C
		opword 0x3C004330
		lis r4, double_to_int_802c1998@ha
		lfs f2, float_1000_80419874(r2)
		opword 0x90750008
		lfd f1, double_to_int_802c1998@l(r4)
		lwz r3, gp(r13)
		opword 0xC0150010
		opword 0x80630004
		opword 0x90010270
		opword 0xEC420032
		opword 0x6C608000
		opword 0x90010274
		opword 0xC8010270
		opword 0xEC000828
		opword 0xEC220024
		bl __cvt_dbl_usll
		opword 0x8015000C
		opword 0x80B50008
		opword 0x7C040010
		opword 0x9015000C
		opword 0x7C032910
		opword 0x90150008
		opword 0xA0150000
		opword 0x540006F2
		opword 0xB0150000
		opword 0xA0150000
		opword 0x54000734
		opword 0xB0150000
		opword 0x80750018
		opword 0xC0150010
		opword 0xC0230008
		opword 0xFC000840
		opword 0x4C411382
		opword 0x408200C0
		opword 0xA0150000
		opword 0x5400077B
		opword 0x418200A4
		opword 0x48000008
		opword 0xEC000828
		opword 0xFC000840
		opword 0x4181FFF8
		opword 0xD0150010
		opword 0x3CA08000
		opword 0x3C801062
		opword 0x7EC3B378
		opword 0x800500F8
		opword 0x38C44DD3
		opword 0x7F24CB78
		opword 0x38A00000
		opword 0x5400F0BE
		opword 0x7C060016
		opword 0x5406D1BE
		bl __div2i
		opword 0x9095000C
		opword 0x3C004330
		lis r4, double_to_int_802c1998@ha
		lfs f2, float_1000_80419874(r2)
		opword 0x90750008
		lfd f1, double_to_int_802c1998@l(r4)
		lwz r3, gp(r13)
		opword 0xC0150010
		opword 0x80630004
		opword 0x90010270
		opword 0xEC420032
		opword 0x6C608000
		opword 0x90010274
		opword 0xC8010270
		opword 0xEC000828
		opword 0xEC220024
		bl __cvt_dbl_usll
		opword 0x8015000C
		opword 0x80B50008
		opword 0x7C040010
		opword 0x9015000C
		opword 0x7C032910
		opword 0x90150008
		opword 0x48000014
		opword 0xD0350010
		opword 0xA0150000
		opword 0x60000002
		opword 0xB0150000
		opword 0x28130000
		opword 0x418200E4
		opword 0x7E799B78
		opword 0x3AC00000
		opword 0x480000CC
		opword 0x80790004
		lwz r0, activeGroup(r13)
		opword 0x83830000
		opword 0x1C0002F4
		lwz r3, mapWork(r13)
		opword 0x281C0000
		opword 0x7F630214
		opword 0x4082000C
		opword 0x3BE00000
		opword 0x48000064
		opword 0x7F7ADB78
		opword 0x3BC00000
		opword 0x48000048
		opword 0x83FA0154
		opword 0x3BA00000
		opword 0x48000028
		opword 0x807F0008
		opword 0x7F84E378
		opword 0x80630000
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x48000030
		opword 0x3BBD0001
		opword 0x3BFF0134
		opword 0x801A0150
		opword 0x7C1D0000
		opword 0x4180FFD4
		opword 0x3B5A0178
		opword 0x3BDE0001
		opword 0x801B0000
		opword 0x7C1E0000
		opword 0x4180FFB4
		opword 0x3BE00000
		opword 0x281F0000
		opword 0x41820034
		opword 0x80D90004
		opword 0x7EA5AB78
		opword 0x387F007C
		opword 0x389F004C
		bl mapCalcAnimMatrix
		opword 0x801F0000
		opword 0x3A800001
		opword 0x60002000
		opword 0x901F0000
		opword 0x801F0000
		opword 0x60000200
		opword 0x901F0000
		opword 0x3B390004
		opword 0x3AD60001
		opword 0x80130000
		opword 0x7C160000
		opword 0x4180FF30
		opword 0x28120000
		opword 0x418206D8
		opword 0x7E539378
		opword 0x3AC00000
		opword 0x480006C0
		opword 0x80930004
		opword 0x38610170
		opword 0x80840000
		bl strcpy
		lwz r0, activeGroup(r13)
		opword 0x3B200000
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7F630214
		opword 0x7F7DDB78
		opword 0x48000068
		opword 0x801D00A0
		opword 0x28000000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000064
		opword 0x3B400000
		opword 0x7F5CD378
		opword 0x48000030
		opword 0x3BDC0004
		opword 0x38810170
		opword 0x7FC3F214
		opword 0x807E0000
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x807E0004
		opword 0x48000034
		opword 0x3B9C0008
		opword 0x3B5A0001
		opword 0x807D00A0
		opword 0x80030000
		opword 0x7C1A0000
		opword 0x4180FFC8
		opword 0x3BBD0178
		opword 0x3B390001
		opword 0x801B0000
		opword 0x7C190000
		opword 0x4180FF94
		opword 0x38600000
		opword 0x28030000
		opword 0x41820190
		opword 0x80D30004
		opword 0x38E00001
		opword 0x80860010
		opword 0x39060068
		opword 0x3804FFFF
		opword 0x7C0903A6
		opword 0x2C040001
		opword 0x40810170
		opword 0x38880014
		opword 0x38A7FFFF
		opword 0xC1950010
		opword 0x1CA50068
		opword 0xC0080014
		opword 0xFC0C0040
		opword 0x38A50014
		opword 0x7CA62A14
		opword 0x4C401382
		opword 0x40820008
		opword 0x48000010
		opword 0x7C070000
		opword 0x40820130
		opword 0xFD800090
		opword 0x38000005
		opword 0x7CA72B78
		opword 0x7C892378
		opword 0x39000000
		opword 0x7C0903A6
		opword 0x80070014
		opword 0x2C000000
		opword 0x41820020
		opword 0x80060004
		opword 0xC0070004
		opword 0x1C00001C
		opword 0x7D404214
		opword 0x380A002C
		opword 0x7C03052E
		opword 0x480000B4
		opword 0xC0650000
		opword 0xC0240000
		lfs f0, float_0_80419850(r2)
		opword 0xEC4C1828
		opword 0xED611828
		opword 0xC1490008
		opword 0xC1290004
		opword 0xC107000C
		opword 0xFC0B0000
		opword 0xC0E70004
		opword 0x7C000026
		opword 0x54001FFE
		opword 0x68000001
		opword 0x7C000034
		opword 0x5400D97F
		opword 0x4182000C
		lfs f0, float_1Eneg08_804198b8(r2)
		opword 0x48000008
		opword 0xFC005890
		opword 0xECC20024
		opword 0x80060004
		lfs f1, float_2_80419858(r2)
		opword 0x1C00001C
		lfs f0, float_3_8041984c(r2)
		lfs f2, float_1_80419860(r2)
		opword 0xEC8601B2
		opword 0x7D404214
		lfs f3, float_neg2_804198a0(r2)
		opword 0x380A002C
		opword 0xECA401B2
		opword 0xEDA00132
		opword 0xEC01293C
		opword 0xEC216978
		opword 0xEC852028
		opword 0xEC06002A
		opword 0xEC22082A
		opword 0xEC43697A
		opword 0xEC0B0032
		opword 0xEC6B0132
		opword 0xEC080032
		opword 0xEC07007A
		opword 0xEC0900BA
		opword 0xEC0A00FA
		opword 0x7C03052E
		opword 0x38E70014
		opword 0x39080004
		opword 0x39290014
		opword 0x4200FF1C
		opword 0x80060004
		opword 0xC0060008
		opword 0x1C80001C
		opword 0x38040040
		opword 0x7C03052E
		opword 0x80060004
		opword 0xC006000C
		opword 0x1C80001C
		opword 0x38040044
		opword 0x7C03052E
		opword 0x48000010
		opword 0x39080068
		opword 0x38E70001
		opword 0x4200FE98
		opword 0x80930004
		opword 0x38610170
		opword 0x80840000
		bl strcpy
		opword 0x38610170
		la r4, str_804198BC(r2)
		bl strcat
		lwz r0, activeGroup(r13)
		opword 0x3B200000
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7F630214
		opword 0x7F7DDB78
		opword 0x48000068
		opword 0x801D00A0
		opword 0x28000000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000064
		opword 0x3B400000
		opword 0x7F5CD378
		opword 0x48000030
		opword 0x3BDC0004
		opword 0x38810170
		opword 0x7FC3F214
		opword 0x807E0000
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x807E0004
		opword 0x48000034
		opword 0x3B9C0008
		opword 0x3B5A0001
		opword 0x807D00A0
		opword 0x80030000
		opword 0x7C1A0000
		opword 0x4180FFC8
		opword 0x3BBD0178
		opword 0x3B390001
		opword 0x801B0000
		opword 0x7C190000
		opword 0x4180FF94
		opword 0x38600000
		opword 0x28030000
		opword 0x41820190
		opword 0x80D30004
		opword 0x38E00001
		opword 0x80860010
		opword 0x39060068
		opword 0x3804FFFF
		opword 0x7C0903A6
		opword 0x2C040001
		opword 0x40810170
		opword 0x38880014
		opword 0x38A7FFFF
		opword 0xC1950010
		opword 0x1CA50068
		opword 0xC0080014
		opword 0xFC0C0040
		opword 0x38A50014
		opword 0x7CA62A14
		opword 0x4C401382
		opword 0x40820008
		opword 0x48000010
		opword 0x7C070000
		opword 0x40820130
		opword 0xFD800090
		opword 0x38000005
		opword 0x7CA72B78
		opword 0x7C892378
		opword 0x39000000
		opword 0x7C0903A6
		opword 0x80070014
		opword 0x2C000000
		opword 0x41820020
		opword 0x80060004
		opword 0xC0070004
		opword 0x1C00001C
		opword 0x7D404214
		opword 0x380A002C
		opword 0x7C03052E
		opword 0x480000B4
		opword 0xC0650000
		opword 0xC0240000
		lfs f0, float_0_80419850(r2)
		opword 0xEC4C1828
		opword 0xED611828
		opword 0xC1490008
		opword 0xC1290004
		opword 0xC107000C
		opword 0xFC0B0000
		opword 0xC0E70004
		opword 0x7C000026
		opword 0x54001FFE
		opword 0x68000001
		opword 0x7C000034
		opword 0x5400D97F
		opword 0x4182000C
		lfs f0, float_1Eneg08_804198b8(r2)
		opword 0x48000008
		opword 0xFC005890
		opword 0xECC20024
		opword 0x80060004
		lfs f1, float_2_80419858(r2)
		opword 0x1C00001C
		lfs f0, float_3_8041984c(r2)
		lfs f2, float_1_80419860(r2)
		opword 0xEC8601B2
		opword 0x7D404214
		lfs f3, float_neg2_804198a0(r2)
		opword 0x380A002C
		opword 0xECA401B2
		opword 0xEDA00132
		opword 0xEC01293C
		opword 0xEC216978
		opword 0xEC852028
		opword 0xEC06002A
		opword 0xEC22082A
		opword 0xEC43697A
		opword 0xEC0B0032
		opword 0xEC6B0132
		opword 0xEC080032
		opword 0xEC07007A
		opword 0xEC0900BA
		opword 0xEC0A00FA
		opword 0x7C03052E
		opword 0x38E70014
		opword 0x39080004
		opword 0x39290014
		opword 0x4200FF1C
		opword 0x80060004
		opword 0xC0060008
		opword 0x1C80001C
		opword 0x38040040
		opword 0x7C03052E
		opword 0x80060004
		opword 0xC006000C
		opword 0x1C80001C
		opword 0x38040044
		opword 0x7C03052E
		opword 0x48000010
		opword 0x39080068
		opword 0x38E70001
		opword 0x4200FE98
		opword 0x80930004
		opword 0x38610170
		opword 0x80840000
		bl strcpy
		opword 0x38610170
		la r4, str_804198C0(r2)
		bl strcat
		lwz r0, activeGroup(r13)
		opword 0x3B200000
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7F630214
		opword 0x7F7DDB78
		opword 0x48000068
		opword 0x801D00A0
		opword 0x28000000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000064
		opword 0x3B400000
		opword 0x7F5CD378
		opword 0x48000030
		opword 0x3BDC0004
		opword 0x38810170
		opword 0x7FC3F214
		opword 0x807E0000
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x807E0004
		opword 0x48000034
		opword 0x3B9C0008
		opword 0x3B5A0001
		opword 0x807D00A0
		opword 0x80030000
		opword 0x7C1A0000
		opword 0x4180FFC8
		opword 0x3BBD0178
		opword 0x3B390001
		opword 0x801B0000
		opword 0x7C190000
		opword 0x4180FF94
		opword 0x38600000
		opword 0x28030000
		opword 0x41820190
		opword 0x80D30004
		opword 0x38E00001
		opword 0x80860010
		opword 0x39060068
		opword 0x3804FFFF
		opword 0x7C0903A6
		opword 0x2C040001
		opword 0x40810170
		opword 0x38880014
		opword 0x38A7FFFF
		opword 0xC1950010
		opword 0x1CA50068
		opword 0xC0080014
		opword 0xFC0C0040
		opword 0x38A50014
		opword 0x7CA62A14
		opword 0x4C401382
		opword 0x40820008
		opword 0x48000010
		opword 0x7C070000
		opword 0x40820130
		opword 0xFD800090
		opword 0x38000005
		opword 0x7CA72B78
		opword 0x7C892378
		opword 0x39000000
		opword 0x7C0903A6
		opword 0x80070014
		opword 0x2C000000
		opword 0x41820020
		opword 0x80060004
		opword 0xC0070004
		opword 0x1C00001C
		opword 0x7D404214
		opword 0x380A002C
		opword 0x7C03052E
		opword 0x480000B4
		opword 0xC0650000
		opword 0xC0240000
		lfs f0, float_0_80419850(r2)
		opword 0xEC4C1828
		opword 0xED611828
		opword 0xC1490008
		opword 0xC1290004
		opword 0xC107000C
		opword 0xFC0B0000
		opword 0xC0E70004
		opword 0x7C000026
		opword 0x54001FFE
		opword 0x68000001
		opword 0x7C000034
		opword 0x5400D97F
		opword 0x4182000C
		lfs f0, float_1Eneg08_804198b8(r2)
		opword 0x48000008
		opword 0xFC005890
		opword 0xECC20024
		opword 0x80060004
		lfs f1, float_2_80419858(r2)
		opword 0x1C00001C
		lfs f0, float_3_8041984c(r2)
		lfs f2, float_1_80419860(r2)
		opword 0xEC8601B2
		opword 0x7D404214
		lfs f3, float_neg2_804198a0(r2)
		opword 0x380A002C
		opword 0xECA401B2
		opword 0xEDA00132
		opword 0xEC01293C
		opword 0xEC216978
		opword 0xEC852028
		opword 0xEC06002A
		opword 0xEC22082A
		opword 0xEC43697A
		opword 0xEC0B0032
		opword 0xEC6B0132
		opword 0xEC080032
		opword 0xEC07007A
		opword 0xEC0900BA
		opword 0xEC0A00FA
		opword 0x7C03052E
		opword 0x38E70014
		opword 0x39080004
		opword 0x39290014
		opword 0x4200FF1C
		opword 0x80060004
		opword 0xC0060008
		opword 0x1C80001C
		opword 0x38040040
		opword 0x7C03052E
		opword 0x80060004
		opword 0xC006000C
		opword 0x1C80001C
		opword 0x38040044
		opword 0x7C03052E
		opword 0x48000010
		opword 0x39080068
		opword 0x38E70001
		opword 0x4200FE98
		opword 0x3A730004
		opword 0x3AD60001
		opword 0x80120000
		opword 0x7C160000
		opword 0x4180F93C
		opword 0x28110000
		opword 0x41820600
		opword 0x7E328B78
		opword 0x3A600000
		opword 0x480005E8
		opword 0x80920004
		opword 0x38610070
		opword 0x80840000
		bl strcpy
		lwz r0, activeGroup(r13)
		opword 0x3AC00000
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7F230214
		opword 0x7F3ACB78
		opword 0x48000068
		opword 0x801A00A0
		opword 0x28000000
		opword 0x4082000C
		opword 0x38800000
		opword 0x48000064
		opword 0x3B800000
		opword 0x7F9DE378
		opword 0x48000030
		opword 0x3B7D0004
		opword 0x38810070
		opword 0x7F63DA14
		opword 0x807B0000
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x809B0004
		opword 0x48000034
		opword 0x3BBD0008
		opword 0x3B9C0001
		opword 0x807A00A0
		opword 0x80030000
		opword 0x7C1C0000
		opword 0x4180FFC8
		opword 0x3B5A0178
		opword 0x3AD60001
		opword 0x80190000
		opword 0x7C160000
		opword 0x4180FF94
		opword 0x38800000
		opword 0x28040000
		opword 0x41820148
		opword 0x80D20004
		opword 0x38A00001
		opword 0x80660004
		opword 0x38E60054
		opword 0x3803FFFF
		opword 0x7C0903A6
		opword 0x2C030001
		opword 0x40810128
		opword 0x3865FFFF
		opword 0xC0550010
		opword 0xC0070008
		opword 0x1C630054
		opword 0xFC020040
		opword 0x38630008
		opword 0x7C661A14
		opword 0x4C401382
		opword 0x40820008
		opword 0x48000010
		opword 0x7C050000
		opword 0x408200EC
		opword 0xFC400090
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820024
		lfs f1, float_255_804198c8(r2)
		opword 0xC0030004
		opword 0xEC01083C
		opword 0xFC00001E
		opword 0xD8010270
		opword 0x80010274
		opword 0x9804010C
		opword 0x480000C8
		opword 0xC0630000
		opword 0xC0270008
		lfs f0, float_0_80419850(r2)
		opword 0xEC421828
		opword 0xED811828
		opword 0xC1670010
		opword 0xC147000C
		opword 0xC123000C
		opword 0xFC0C0000
		opword 0xC1030004
		opword 0x7C000026
		opword 0x54001FFE
		opword 0x68000001
		opword 0x7C000034
		opword 0x5400D97F
		opword 0x4182000C
		lfs f0, float_1Eneg08_804198b8(r2)
		opword 0x48000008
		opword 0xFC006090
		opword 0xECE20024
		lfs f2, float_2_80419858(r2)
		lfs f1, float_3_8041984c(r2)
		lfs f3, float_1_80419860(r2)
		lfs f4, float_neg2_804198a0(r2)
		lfs f0, float_255_804198c8(r2)
		opword 0xECA701F2
		opword 0xECC501F2
		opword 0xEDA10172
		opword 0xEC22317C
		opword 0xEC4269B8
		opword 0xECA62828
		opword 0xEC27082A
		opword 0xEC43102A
		opword 0xEC6469BA
		opword 0xEC2C0072
		opword 0xEC8C0172
		opword 0xEC290072
		opword 0xEC2808BA
		opword 0xEC2A08FA
		opword 0xEC2B093A
		opword 0xEC00007C
		opword 0xFC00001E
		opword 0xD8010270
		opword 0x80010274
		opword 0x9804010C
		opword 0x48000010
		opword 0x38E70054
		opword 0x38A50001
		opword 0x4200FEE0
		opword 0x80920004
		opword 0x38610070
		opword 0x80840000
		bl strcpy
		opword 0x38610070
		la r4, str_804198BC(r2)
		bl strcat
		lwz r0, activeGroup(r13)
		opword 0x3AC00000
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7F230214
		opword 0x7F3ACB78
		opword 0x48000068
		opword 0x801A00A0
		opword 0x28000000
		opword 0x4082000C
		opword 0x38800000
		opword 0x48000064
		opword 0x3B800000
		opword 0x7F9DE378
		opword 0x48000030
		opword 0x3B7D0004
		opword 0x38810070
		opword 0x7F63DA14
		opword 0x807B0000
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x809B0004
		opword 0x48000034
		opword 0x3BBD0008
		opword 0x3B9C0001
		opword 0x807A00A0
		opword 0x80030000
		opword 0x7C1C0000
		opword 0x4180FFC8
		opword 0x3B5A0178
		opword 0x3AD60001
		opword 0x80190000
		opword 0x7C160000
		opword 0x4180FF94
		opword 0x38800000
		opword 0x28040000
		opword 0x41820148
		opword 0x80D20004
		opword 0x38A00001
		opword 0x80660004
		opword 0x38E60054
		opword 0x3803FFFF
		opword 0x7C0903A6
		opword 0x2C030001
		opword 0x40810128
		opword 0x3865FFFF
		opword 0xC0550010
		opword 0xC0070008
		opword 0x1C630054
		opword 0xFC020040
		opword 0x38630008
		opword 0x7C661A14
		opword 0x4C401382
		opword 0x40820008
		opword 0x48000010
		opword 0x7C050000
		opword 0x408200EC
		opword 0xFC400090
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820024
		lfs f1, float_255_804198c8(r2)
		opword 0xC0030004
		opword 0xEC01083C
		opword 0xFC00001E
		opword 0xD8010270
		opword 0x80010274
		opword 0x9804010C
		opword 0x480000C8
		opword 0xC0630000
		opword 0xC0270008
		lfs f0, float_0_80419850(r2)
		opword 0xEC421828
		opword 0xED811828
		opword 0xC1670010
		opword 0xC147000C
		opword 0xC123000C
		opword 0xFC0C0000
		opword 0xC1030004
		opword 0x7C000026
		opword 0x54001FFE
		opword 0x68000001
		opword 0x7C000034
		opword 0x5400D97F
		opword 0x4182000C
		lfs f0, float_1Eneg08_804198b8(r2)
		opword 0x48000008
		opword 0xFC006090
		opword 0xECE20024
		lfs f2, float_2_80419858(r2)
		lfs f1, float_3_8041984c(r2)
		lfs f3, float_1_80419860(r2)
		lfs f4, float_neg2_804198a0(r2)
		lfs f0, float_255_804198c8(r2)
		opword 0xECA701F2
		opword 0xECC501F2
		opword 0xEDA10172
		opword 0xEC22317C
		opword 0xEC4269B8
		opword 0xECA62828
		opword 0xEC27082A
		opword 0xEC43102A
		opword 0xEC6469BA
		opword 0xEC2C0072
		opword 0xEC8C0172
		opword 0xEC290072
		opword 0xEC2808BA
		opword 0xEC2A08FA
		opword 0xEC2B093A
		opword 0xEC00007C
		opword 0xFC00001E
		opword 0xD8010270
		opword 0x80010274
		opword 0x9804010C
		opword 0x48000010
		opword 0x38E70054
		opword 0x38A50001
		opword 0x4200FEE0
		opword 0x80920004
		opword 0x38610070
		opword 0x80840000
		bl strcpy
		opword 0x38610070
		la r4, str_804198C0(r2)
		bl strcat
		lwz r0, activeGroup(r13)
		opword 0x3AC00000
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7F230214
		opword 0x7F3ACB78
		opword 0x48000068
		opword 0x801A00A0
		opword 0x28000000
		opword 0x4082000C
		opword 0x38800000
		opword 0x48000064
		opword 0x3B800000
		opword 0x7F9DE378
		opword 0x48000030
		opword 0x3B7D0004
		opword 0x38810070
		opword 0x7F63DA14
		opword 0x807B0000
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x809B0004
		opword 0x48000034
		opword 0x3BBD0008
		opword 0x3B9C0001
		opword 0x807A00A0
		opword 0x80030000
		opword 0x7C1C0000
		opword 0x4180FFC8
		opword 0x3B5A0178
		opword 0x3AD60001
		opword 0x80190000
		opword 0x7C160000
		opword 0x4180FF94
		opword 0x38800000
		opword 0x28040000
		opword 0x41820148
		opword 0x80D20004
		opword 0x38A00001
		opword 0x80660004
		opword 0x38E60054
		opword 0x3803FFFF
		opword 0x7C0903A6
		opword 0x2C030001
		opword 0x40810128
		opword 0x3865FFFF
		opword 0xC0550010
		opword 0xC0070008
		opword 0x1C630054
		opword 0xFC020040
		opword 0x38630008
		opword 0x7C661A14
		opword 0x4C401382
		opword 0x40820008
		opword 0x48000010
		opword 0x7C050000
		opword 0x408200EC
		opword 0xFC400090
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820024
		lfs f1, float_255_804198c8(r2)
		opword 0xC0030004
		opword 0xEC01083C
		opword 0xFC00001E
		opword 0xD8010270
		opword 0x80010274
		opword 0x9804010C
		opword 0x480000C8
		opword 0xC0630000
		opword 0xC0270008
		lfs f0, float_0_80419850(r2)
		opword 0xEC421828
		opword 0xED811828
		opword 0xC1670010
		opword 0xC147000C
		opword 0xC123000C
		opword 0xFC0C0000
		opword 0xC1030004
		opword 0x7C000026
		opword 0x54001FFE
		opword 0x68000001
		opword 0x7C000034
		opword 0x5400D97F
		opword 0x4182000C
		lfs f0, float_1Eneg08_804198b8(r2)
		opword 0x48000008
		opword 0xFC006090
		opword 0xECE20024
		lfs f2, float_2_80419858(r2)
		lfs f1, float_3_8041984c(r2)
		lfs f3, float_1_80419860(r2)
		lfs f4, float_neg2_804198a0(r2)
		lfs f0, float_255_804198c8(r2)
		opword 0xECA701F2
		opword 0xECC501F2
		opword 0xEDA10172
		opword 0xEC22317C
		opword 0xEC4269B8
		opword 0xECA62828
		opword 0xEC27082A
		opword 0xEC43102A
		opword 0xEC6469BA
		opword 0xEC2C0072
		opword 0xEC8C0172
		opword 0xEC290072
		opword 0xEC2808BA
		opword 0xEC2A08FA
		opword 0xEC2B093A
		opword 0xEC00007C
		opword 0xFC00001E
		opword 0xD8010270
		opword 0x80010274
		opword 0x9804010C
		opword 0x48000010
		opword 0x38E70054
		opword 0x38A50001
		opword 0x4200FEE0
		opword 0x3A520004
		opword 0x3A730001
		opword 0x80110000
		opword 0x7C130000
		opword 0x4180FA14
		opword 0x28100000
		opword 0x418201BC
		opword 0x7E118378
		opword 0x3A400000
		opword 0x480001A4
		opword 0x80710004
		opword 0x80630000
		bl lightNameToPtr
		opword 0x28030000
		opword 0x41820188
		opword 0x80F10004
		opword 0x38C00001
		opword 0x80870004
		opword 0x390700B8
		opword 0x3804FFFF
		opword 0x7C0903A6
		opword 0x2C040001
		opword 0x40810168
		opword 0x38A80008
		opword 0x3886FFFF
		opword 0xC1950010
		opword 0x1C8400B8
		opword 0xC0080008
		opword 0xFC0C0040
		opword 0x38840008
		opword 0x7C872214
		opword 0x4C401382
		opword 0x40820008
		opword 0x48000010
		opword 0x7C060000
		opword 0x40820128
		opword 0xFD800090
		opword 0x38000009
		opword 0x7C862378
		opword 0x7CA82B78
		opword 0x38E1001C
		opword 0x7C0903A6
		opword 0x80060014
		opword 0x2C000000
		opword 0x41820010
		opword 0xC0060004
		opword 0xD0070000
		opword 0x480000A4
		opword 0xC0640000
		opword 0xC0250000
		lfs f0, float_0_80419850(r2)
		opword 0xEC4C1828
		opword 0xED611828
		opword 0xC1480008
		opword 0xC1280004
		opword 0xC106000C
		opword 0xFC0B0000
		opword 0xC0E60004
		opword 0x7C000026
		opword 0x54001FFE
		opword 0x68000001
		opword 0x7C000034
		opword 0x5400D97F
		opword 0x4182000C
		lfs f0, float_1Eneg08_804198b8(r2)
		opword 0x48000008
		opword 0xFC005890
		opword 0xECC20024
		lfs f1, float_2_80419858(r2)
		lfs f0, float_3_8041984c(r2)
		lfs f2, float_1_80419860(r2)
		lfs f3, float_neg2_804198a0(r2)
		opword 0xEC8601B2
		opword 0xECA401B2
		opword 0xEDA00132
		opword 0xEC01293C
		opword 0xEC216978
		opword 0xEC852028
		opword 0xEC06002A
		opword 0xEC22082A
		opword 0xEC43697A
		opword 0xEC0B0032
		opword 0xEC6B0132
		opword 0xEC080032
		opword 0xEC07007A
		opword 0xEC0900BA
		opword 0xEC0A00FA
		opword 0xD0070000
		opword 0x38C60014
		opword 0x38E70004
		opword 0x39080014
		opword 0x4200FF3C
		lfs f3, float_10_80419864(r2)
		opword 0xC001001C
		opword 0xC0210020
		opword 0xECA30032
		opword 0xC0010024
		opword 0xEC830072
		opword 0xC0410028
		opword 0xEC630032
		opword 0xC021002C
		opword 0xD0A30024
		opword 0xC0010030
		opword 0xD0830028
		opword 0xD063002C
		opword 0xD0430030
		opword 0xD0230034
		opword 0xD0030038
		opword 0x48000010
		opword 0x390800B8
		opword 0x38C60001
		opword 0x4200FEA0
		opword 0x3A310004
		opword 0x3A520001
		opword 0x80100000
		opword 0x7C120000
		opword 0x4180FE58
		opword 0x280F0000
		opword 0x418201E0
		opword 0x7DF07B78
		opword 0x3A200000
		opword 0x480001C8
		opword 0x80700004
		opword 0x80630000
		bl lightNameToPtr
		opword 0x28030000
		opword 0x418201AC
		opword 0x80F00004
		opword 0x38C00001
		opword 0x80870004
		opword 0x39070068
		opword 0x3804FFFF
		opword 0x7C0903A6
		opword 0x2C040001
		opword 0x4081018C
		opword 0x38A80008
		opword 0x3886FFFF
		opword 0xC1950010
		opword 0x1C840068
		opword 0xC0080008
		opword 0xFC0C0040
		opword 0x38840008
		opword 0x7C872214
		opword 0x4C401382
		opword 0x40820008
		opword 0x48000010
		opword 0x7C060000
		opword 0x4082014C
		opword 0xFD800090
		opword 0x38000005
		opword 0x7C862378
		opword 0x7CA82B78
		opword 0x38E10008
		opword 0x7C0903A6
		opword 0x80060014
		opword 0x2C000000
		opword 0x41820010
		opword 0xC0060004
		opword 0xD0070000
		opword 0x480000A4
		opword 0xC0640000
		opword 0xC0250000
		lfs f0, float_0_80419850(r2)
		opword 0xEC4C1828
		opword 0xED611828
		opword 0xC1480008
		opword 0xC1280004
		opword 0xC106000C
		opword 0xFC0B0000
		opword 0xC0E60004
		opword 0x7C000026
		opword 0x54001FFE
		opword 0x68000001
		opword 0x7C000034
		opword 0x5400D97F
		opword 0x4182000C
		lfs f0, float_1Eneg08_804198b8(r2)
		opword 0x48000008
		opword 0xFC005890
		opword 0xECC20024
		lfs f1, float_2_80419858(r2)
		lfs f0, float_3_8041984c(r2)
		lfs f2, float_1_80419860(r2)
		lfs f3, float_neg2_804198a0(r2)
		opword 0xEC8601B2
		opword 0xECA401B2
		opword 0xEDA00132
		opword 0xEC01293C
		opword 0xEC216978
		opword 0xEC852028
		opword 0xEC06002A
		opword 0xEC22082A
		opword 0xEC43697A
		opword 0xEC0B0032
		opword 0xEC6B0132
		opword 0xEC080032
		opword 0xEC07007A
		opword 0xEC0900BA
		opword 0xEC0A00FA
		opword 0xD0070000
		opword 0x38C60014
		opword 0x38E70004
		opword 0x39080014
		opword 0x4200FF3C
		lfs f2, float_255_804198c8(r2)
		opword 0x380000FF
		opword 0xC0010008
		opword 0xC021000C
		opword 0xEC820032
		opword 0xC0010010
		opword 0xEC620072
		opword 0xC0210018
		opword 0xEC420032
		opword 0xC0010014
		opword 0xFC80201E
		opword 0xFC60181E
		opword 0xFC40101E
		opword 0xD8810270
		opword 0xD8610278
		opword 0x80810274
		opword 0xD8410280
		opword 0x80A1027C
		opword 0x98830048
		opword 0x80810284
		opword 0x98A30049
		opword 0x9883004A
		opword 0x9803004B
		opword 0xD023004C
		opword 0xD0030050
		opword 0x48000010
		opword 0x39080068
		opword 0x38C60001
		opword 0x4200FE7C
		opword 0x3A100004
		opword 0x3A310001
		opword 0x800F0000
		opword 0x7C110000
		opword 0x4180FE34
		opword 0x3AF70001
		opword 0x3AB50020
		opword 0x80180160
		opword 0x7C170000
		opword 0x4180EB24
		opword 0x2C140000
		opword 0x41820028
		lfs f1, float_10_80419864(r2)
		opword 0x38610040
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x807800A8
		opword 0x38810040
		opword 0x38A00000
		bl mapReCalcMatrix
		opword 0x3B180178
		opword 0x39CE0001
		opword 0x80610288
		opword 0x80030000
		opword 0x7C0E0000
		opword 0x4180EAD0
		opword 0xB9C10298
		opword 0x800102E4
		opword 0x7C0803A6
		opword 0x382102E0
	}
}
#pragma pop

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void _mapDispMapObj(CameraId cam, MapObject *obj) {
	char _af_pad[176];
	asm volatile {
		opword 0x7C7A1B78
		opword 0x7C9F2378
		bl camGetPtr
		stw r31, current_mp(r13)
		opword 0x7C7E1B78
		opword 0x807F0000
		opword 0x546006B5
		opword 0x4182032C
		opword 0x54600421
		opword 0x418200B0
		opword 0x807F0008
		opword 0x38A00000
		opword 0x7C641B78
		opword 0x48000008
		opword 0x7C040378
		opword 0x80040014
		opword 0x28000000
		opword 0x4082FFF4
		opword 0x4800000C
		opword 0x80840010
		opword 0x38A50001
		opword 0x7C041840
		opword 0x4082FFF4
		opword 0x6CA38000
		opword 0x3C004330
		opword 0x906100BC
		lis r4, double_to_int_802c1998@ha
		lfd f1, double_to_int_802c1998@l(r4)
		la r3, _af_pad+52
		opword 0x900100B8
		lfs f2, float_0p01_804198b4(r2)
		opword 0xC80100B8
		opword 0xEC000828
		fmuls f31, f2, f0
		bl GXGetProjectionv
		opword 0xC0BE0030
		opword 0x3861003C
		opword 0xC05E0034
		lfs f0, float_neg2_804198a0(r2)
		lfs f3, float_1_80419860(r2)
		opword 0xEC22282A
		opword 0xEC4000B2
		opword 0xC0810050
		opword 0xEC03F82A
		opword 0xEC230072
		opword 0xEC420172
		opword 0xEC010032
		opword 0xEC3F00B2
		opword 0xEC010024
		opword 0xEC03002A
		opword 0xEC040032
		opword 0xD0010050
		bl GXSetProjectionv
		opword 0x809F0008
		opword 0x881F0004
		opword 0x8064005C
		opword 0x2C030000
		opword 0x408100CC
		opword 0x80840060
		opword 0x80DF0000
		opword 0x80BF000C
		opword 0x8084010C
		opword 0x54C30673
		opword 0x90A10034
		opword 0x90810030
		opword 0x41820018
		opword 0x88610037
		opword 0x280300FF
		opword 0x4182000C
		opword 0x38600001
		opword 0x4800008C
		opword 0x88610033
		opword 0x280300FF
		opword 0x4182000C
		opword 0x38600001
		opword 0x48000078
		opword 0x54C30529
		opword 0x40820034
		lwz r3, activeGroup(r13)
		lwz r4, mapWork(r13)
		opword 0x1C6302F4
		opword 0x7C841A14
		opword 0xA0640004
		opword 0x546307BD
		opword 0x41820018
		opword 0x88640019
		opword 0x280300FF
		opword 0x4182000C
		opword 0x38600001
		opword 0x48000040
		opword 0x54C304E7
		opword 0x40820034
		lwz r3, activeGroup(r13)
		lwz r4, mapWork(r13)
		opword 0x1C6302F4
		opword 0x7C841A14
		opword 0xA0640004
		opword 0x5463077B
		opword 0x41820018
		opword 0x8864001D
		opword 0x280300FF
		opword 0x4182000C
		opword 0x38600001
		opword 0x48000008
		opword 0x38600000
		opword 0x2C030000
		opword 0x41820008
		opword 0x38000002
		opword 0x2C000003
		opword 0x41820078
		opword 0x4080001C
		opword 0x2C000001
		opword 0x418200B4
		opword 0x40800140
		opword 0x2C000000
		opword 0x40800018
		opword 0x48000134
		opword 0x2C000005
		opword 0x4182012C
		opword 0x40800128
		opword 0x480000DC
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00000
		opword 0x38C00007
		bl GXSetBlendMode
		opword 0x38600001
		bl GXSetZCompLoc
		opword 0x38600007
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetAlphaCompare
		opword 0x38600001
		opword 0x38800003
		opword 0x38A00001
		bl GXSetZMode
		opword 0x48000120
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00000
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
		opword 0x480000D8
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00000
		opword 0x38C00000
		bl GXSetBlendMode
		opword 0x38600000
		bl GXSetZCompLoc
		opword 0x38600006
		opword 0x38800080
		opword 0x38A00001
		opword 0x38C00000
		opword 0x38E00000
		bl GXSetAlphaCompare
		opword 0x38600001
		opword 0x38800003
		opword 0x38A00001
		bl GXSetZMode
		opword 0x48000090
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00000
		opword 0x38C00000
		bl GXSetBlendMode
		opword 0x38600000
		bl GXSetZCompLoc
		opword 0x38600006
		opword 0x38800080
		opword 0x38A00001
		opword 0x38C00000
		opword 0x38E00000
		bl GXSetAlphaCompare
		opword 0x38600000
		opword 0x38800003
		opword 0x38A00000
		bl GXSetZMode
		opword 0x48000048
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
		opword 0x38600001
		opword 0x38800003
		opword 0x38A00000
		bl GXSetZMode
		opword 0x2C1A0001
		opword 0x4082000C
		opword 0x38600000
		bl GXSetZCompLoc
		opword 0x387E011C
		opword 0x389F001C
		opword 0x38A10088
		bl PSMTXConcat
		opword 0x38610088
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x801F0000
		opword 0x540005EF
		opword 0x4082001C
		opword 0x38610088
		opword 0x38810058
		bl PSMTXInvXpose
		opword 0x38610058
		opword 0x38800000
		bl GXLoadNrmMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
		opword 0x38610038
		bl GXGetCullMode
		opword 0x809F0008
		lis r3, culling@ha
		addi r3, r3, culling@l
		opword 0x80A10038
		opword 0x80840058
		opword 0x88040001
		opword 0x5400103A
		opword 0x7C63002E
		opword 0x7C051800
		opword 0x41820008
		bl GXSetCullMode
		bl camGetCurPtr
		lwz r0, activeGroup(r13)
		opword 0x7C651B78
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7CC30214
		opword 0xA0060004
		opword 0x540007FF
		opword 0x41820044
		opword 0x801F0000
		opword 0x54000319
		opword 0x40820038
		opword 0x80060034
		la r3, fog_type(r13)
		opword 0x38810018
		opword 0x90010018
		opword 0x80060028
		opword 0xC026002C
		opword 0x5400103A
		opword 0xC0460030
		opword 0x7C63002E
		opword 0xC0650030
		opword 0xC0850034
		bl GXSetFog
		opword 0x48000028
		lfs f1, float_0_80419850(r2)
		opword 0x3881001C
		lwz r0, dat_80419824(r2)
		opword 0x38600000
		opword 0xFC400890
		opword 0xFC600890
		opword 0x9001001C
		opword 0xFC800890
		bl GXSetFog
		opword 0x807F0000
		opword 0x546006B5
		opword 0x41820030
		opword 0x54600463
		opword 0x40820738
		opword 0x546007FF
		opword 0x4182000C
		opword 0x54600631
		opword 0x41820728
		opword 0x54600673
		opword 0x41820010
		opword 0x881F000F
		opword 0x28000000
		opword 0x41820714
		opword 0x546005EF
		opword 0x418203A4
		opword 0x7FFCFB78
		opword 0x3B600000
		opword 0x3BA00000
		opword 0x48000380
		opword 0x7C63EA14
		lwz r24, 0x60(r3)
		opword 0x83430064
		opword 0x7F03C378
		bl mapSetTextureMatrix
		opword 0x807F0000
		lwz r4, activeGroup(r13)
		opword 0x54600673
		opword 0x80F8010C
		opword 0x80DF000C
		opword 0x1C8402F4
		lwz r5, dat_8041981c(r2)
		lwz r0, mapWork(r13)
		opword 0x90E10028
		opword 0x7C802214
		opword 0x90C1002C
		opword 0x90A10010
		opword 0x4182009C
		opword 0x88E10010
		opword 0x3CA08081
		opword 0x88C1002C
		opword 0x38058081
		opword 0x89410011
		opword 0x7D6731D6
		opword 0x8921002D
		opword 0x88C10013
		opword 0x88A1002F
		opword 0x89010012
		opword 0x88E1002E
		opword 0x7CA629D6
		opword 0x7CC05896
		opword 0x7D2A49D6
		opword 0x7CC65A14
		opword 0x7CCA3E70
		opword 0x7CE839D6
		opword 0x554B0FFE
		opword 0x7D004896
		opword 0x7CC03896
		opword 0x7D084A14
		opword 0x7D2A5A14
		opword 0x7D083E70
		opword 0x99210010
		opword 0x7CC63A14
		opword 0x7C002896
		opword 0x55070FFE
		opword 0x7CC63E70
		opword 0x7D083A14
		opword 0x54C70FFE
		opword 0x99010011
		opword 0x7C002A14
		opword 0x7CC63A14
		opword 0x7C003E70
		opword 0x98C10012
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010013
		opword 0x88C10028
		opword 0x280600FF
		opword 0x4182002C
		opword 0x88010013
		opword 0x3CA08081
		opword 0x38A58081
		opword 0x7C0031D6
		opword 0x7CA50096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010013
		opword 0xA0040004
		opword 0x540007BD
		opword 0x418200A4
		opword 0x54600529
		opword 0x4082009C
		opword 0x88E10010
		opword 0x3CA08081
		opword 0x88C40016
		opword 0x38058081
		opword 0x89410011
		opword 0x7D6731D6
		opword 0x89240017
		opword 0x88C10013
		opword 0x88A40019
		opword 0x89010012
		opword 0x88E40018
		opword 0x7CA629D6
		opword 0x7CC05896
		opword 0x7D2A49D6
		opword 0x7CC65A14
		opword 0x7CCA3E70
		opword 0x7CE839D6
		opword 0x554B0FFE
		opword 0x7D004896
		opword 0x7CC03896
		opword 0x7D084A14
		opword 0x7D2A5A14
		opword 0x7D083E70
		opword 0x99210010
		opword 0x7CC63A14
		opword 0x7C002896
		opword 0x55070FFE
		opword 0x7CC63E70
		opword 0x7D083A14
		opword 0x54C70FFE
		opword 0x99010011
		opword 0x7C002A14
		opword 0x7CC63A14
		opword 0x7C003E70
		opword 0x98C10012
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010013
		opword 0xA0040004
		opword 0x5400077B
		opword 0x418200A4
		opword 0x546004E7
		opword 0x4082009C
		opword 0x88E10010
		opword 0x3CA08081
		opword 0x88C4001A
		opword 0x38058081
		opword 0x89410011
		opword 0x7D6731D6
		opword 0x8924001B
		opword 0x88C10013
		opword 0x88A4001D
		opword 0x89010012
		opword 0x88E4001C
		opword 0x7CA629D6
		opword 0x7CC05896
		opword 0x7D2A49D6
		opword 0x7CC65A14
		opword 0x7CCA3E70
		opword 0x7CE839D6
		opword 0x554B0FFE
		opword 0x7D004896
		opword 0x7CC03896
		opword 0x7D084A14
		opword 0x7D2A5A14
		opword 0x7D083E70
		opword 0x99210010
		opword 0x7CC63A14
		opword 0x7C002896
		opword 0x55070FFE
		opword 0x7CC63E70
		opword 0x7D083A14
		opword 0x54C70FFE
		opword 0x99010011
		opword 0x7C002A14
		opword 0x7CC63A14
		opword 0x7C003E70
		opword 0x98C10012
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010013
		opword 0xA0040004
		opword 0x54000739
		opword 0x418200A4
		opword 0x54600529
		opword 0x4082009C
		opword 0x88A10010
		opword 0x3C608081
		opword 0x8804001E
		opword 0x39438081
		opword 0x89010011
		opword 0x7D2501D6
		opword 0x88E4001F
		opword 0x88C10012
		opword 0x88A40020
		opword 0x88040021
		opword 0x88610013
		opword 0x7C8629D6
		opword 0x7CAA4896
		opword 0x7CA54A14
		opword 0x7CA63E70
		opword 0x7CE839D6
		opword 0x54C80FFE
		opword 0x7C0301D6
		opword 0x7C6A3896
		opword 0x7CAA2096
		opword 0x7C633A14
		opword 0x7CE64214
		opword 0x7C663E70
		opword 0x98E10010
		opword 0x7C852214
		opword 0x7C6A0096
		opword 0x54C50FFE
		opword 0x7C843E70
		opword 0x7CC62A14
		opword 0x54850FFE
		opword 0x98C10011
		opword 0x7C030214
		opword 0x7C842A14
		opword 0x7C003E70
		opword 0x98810012
		opword 0x54030FFE
		opword 0x7C001A14
		opword 0x98010013
		opword 0x80010010
		opword 0x38810014
		opword 0x38600000
		opword 0x90010014
		bl GXSetTevKColor
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl mapSetPolygonVtxDesc
		opword 0x807C00F4
		opword 0x809C0114
		bl GXCallDisplayList
		opword 0x7F58D378
		opword 0x3B200000
		opword 0x48000018
		opword 0x80780010
		opword 0x80980014
		bl GXCallDisplayList
		opword 0x3B180008
		opword 0x3B390001
		opword 0x801A0004
		opword 0x7C190000
		opword 0x4180FFE4
		opword 0x3BBD0008
		opword 0x3B9C0004
		opword 0x3B7B0001
		opword 0x807F0008
		opword 0x8003005C
		opword 0x7C1B0000
		opword 0x4180FC78
		opword 0x4800036C
		opword 0x3BA00000
		opword 0x7FBCEB78
		opword 0x48000350
		opword 0x7C63E214
		opword 0x83430060
		opword 0x83630064
		opword 0x7F43D378
		bl mapSetTextureMatrix
		opword 0x807F0000
		lwz r4, activeGroup(r13)
		opword 0x54600673
		opword 0x80FA010C
		opword 0x80DF000C
		opword 0x1C8402F4
		lwz r5, dat_8041981c(r2)
		lwz r0, mapWork(r13)
		opword 0x90E10020
		opword 0x7C802214
		opword 0x90C10024
		opword 0x90A10008
		opword 0x4182009C
		opword 0x88E10008
		opword 0x3CA08081
		opword 0x88C10024
		opword 0x38058081
		opword 0x89410009
		opword 0x7D6731D6
		opword 0x89210025
		opword 0x88C1000B
		opword 0x88A10027
		opword 0x8901000A
		opword 0x88E10026
		opword 0x7CA629D6
		opword 0x7CC05896
		opword 0x7D2A49D6
		opword 0x7CC65A14
		opword 0x7CCA3E70
		opword 0x7CE839D6
		opword 0x554B0FFE
		opword 0x7D004896
		opword 0x7CC03896
		opword 0x7D084A14
		opword 0x7D2A5A14
		opword 0x7D083E70
		opword 0x99210008
		opword 0x7CC63A14
		opword 0x7C002896
		opword 0x55070FFE
		opword 0x7CC63E70
		opword 0x7D083A14
		opword 0x54C70FFE
		opword 0x99010009
		opword 0x7C002A14
		opword 0x7CC63A14
		opword 0x7C003E70
		opword 0x98C1000A
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x9801000B
		opword 0x88C10020
		opword 0x280600FF
		opword 0x4182002C
		opword 0x8801000B
		opword 0x3CA08081
		opword 0x38A58081
		opword 0x7C0031D6
		opword 0x7CA50096
		opword 0x7C050214
		opword 0x7C003E70
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x9801000B
		opword 0xA0040004
		opword 0x540007BD
		opword 0x418200A4
		opword 0x54600529
		opword 0x4082009C
		opword 0x88E10008
		opword 0x3CA08081
		opword 0x88C40016
		opword 0x38058081
		opword 0x89410009
		opword 0x7D6731D6
		opword 0x89240017
		opword 0x88C1000B
		opword 0x88A40019
		opword 0x8901000A
		opword 0x88E40018
		opword 0x7CA629D6
		opword 0x7CC05896
		opword 0x7D2A49D6
		opword 0x7CC65A14
		opword 0x7CCA3E70
		opword 0x7CE839D6
		opword 0x554B0FFE
		opword 0x7D004896
		opword 0x7CC03896
		opword 0x7D084A14
		opword 0x7D2A5A14
		opword 0x7D083E70
		opword 0x99210008
		opword 0x7CC63A14
		opword 0x7C002896
		opword 0x55070FFE
		opword 0x7CC63E70
		opword 0x7D083A14
		opword 0x54C70FFE
		opword 0x99010009
		opword 0x7C002A14
		opword 0x7CC63A14
		opword 0x7C003E70
		opword 0x98C1000A
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x9801000B
		opword 0xA0040004
		opword 0x5400077B
		opword 0x418200A4
		opword 0x546004E7
		opword 0x4082009C
		opword 0x88E10008
		opword 0x3CA08081
		opword 0x88C4001A
		opword 0x38058081
		opword 0x89410009
		opword 0x7D6731D6
		opword 0x8924001B
		opword 0x88C1000B
		opword 0x88A4001D
		opword 0x8901000A
		opword 0x88E4001C
		opword 0x7CA629D6
		opword 0x7CC05896
		opword 0x7D2A49D6
		opword 0x7CC65A14
		opword 0x7CCA3E70
		opword 0x7CE839D6
		opword 0x554B0FFE
		opword 0x7D004896
		opword 0x7CC03896
		opword 0x7D084A14
		opword 0x7D2A5A14
		opword 0x7D083E70
		opword 0x99210008
		opword 0x7CC63A14
		opword 0x7C002896
		opword 0x55070FFE
		opword 0x7CC63E70
		opword 0x7D083A14
		opword 0x54C70FFE
		opword 0x99010009
		opword 0x7C002A14
		opword 0x7CC63A14
		opword 0x7C003E70
		opword 0x98C1000A
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x9801000B
		opword 0xA0040004
		opword 0x54000739
		opword 0x418200A4
		opword 0x54600529
		opword 0x4082009C
		opword 0x88A10008
		opword 0x3C608081
		opword 0x8804001E
		opword 0x39438081
		opword 0x89010009
		opword 0x7D2501D6
		opword 0x88E4001F
		opword 0x88C1000A
		opword 0x88A40020
		opword 0x88040021
		opword 0x8861000B
		opword 0x7C8629D6
		opword 0x7CAA4896
		opword 0x7CA54A14
		opword 0x7CA63E70
		opword 0x7CE839D6
		opword 0x54C80FFE
		opword 0x7C0301D6
		opword 0x7C6A3896
		opword 0x7CAA2096
		opword 0x7C633A14
		opword 0x7CE64214
		opword 0x7C663E70
		opword 0x98E10008
		opword 0x7C852214
		opword 0x7C6A0096
		opword 0x54C50FFE
		opword 0x7C843E70
		opword 0x7CC62A14
		opword 0x54850FFE
		opword 0x98C10009
		opword 0x7C030214
		opword 0x7C842A14
		opword 0x7C003E70
		opword 0x9881000A
		opword 0x54030FFE
		opword 0x7C001A14
		opword 0x9801000B
		opword 0x80010008
		opword 0x3881000C
		opword 0x38600000
		opword 0x9001000C
		bl GXSetTevKColor
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl mapSetMaterial
		opword 0x7FE3FB78
		opword 0x7F64DB78
		bl mapSetPolygon
		opword 0x3B9C0008
		opword 0x3BBD0001
		opword 0x807F0008
		opword 0x8003005C
		opword 0x7C1D0000
		opword 0x4180FCA8
		opword 0x801F0000
		opword 0x54000421
		opword 0x41820010
		opword 0x809E019C
		opword 0x387E015C
		bl GXSetProjection
		opword 0x801F0000
		opword 0x5400010F
		opword 0x41820034
		opword 0x38600000
		bl GXSetTevDirect
		opword 0x38600001
		bl GXSetTevDirect
		opword 0x38600002
		bl GXSetTevDirect
		opword 0x38600003
		bl GXSetTevDirect
		opword 0x38600004
		bl GXSetTevDirect
		opword 0x38600000
		bl GXSetNumIndStages
	}
}
#pragma pop

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void _mapDispMapGrp(CameraId cam, MapObject* obj) {
	_mapDispMapObj(cam, obj);
	if (obj->child) {
		_mapDispMapGrp(cam, obj->child);
	}
	if ((obj->flags & 0x20) && obj->next) {
		_mapDispMapGrp(cam, obj->next);
	}
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapDispMapObj(CameraId cam, MapObject* obj) {
	_mapDispMapObj(cam, obj);
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapDispMapGrp(CameraId cam, MapObject* obj) {
	_mapDispMapGrp(cam, obj);
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapDispMapObj_off(CameraId cam, MapObject* obj) {
	u16 left, top, right, bottom;

	sysWaitDrawSync();
	GXClearBoundingBox();
	_mapDispMapObj(cam, obj);
	sysWaitDrawSync();
	GXReadBoundingBox(&left, &top, &right, &bottom);
	offscreenAddBoundingBox(obj->offscreenId, left, top, right, bottom);
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapDispMapGrp_off(CameraId cam, MapObject* obj) {
	u16 left, top, right, bottom;

	sysWaitDrawSync();
	GXClearBoundingBox();
	_mapDispMapGrp(cam, obj);
	sysWaitDrawSync();
	GXReadBoundingBox(&left, &top, &right, &bottom);
	offscreenAddBoundingBox(obj->offscreenId, left, top, right, bottom);
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void test_kururing_mapdisp(CameraId cam) {
	MapWork* wp = &mapWork[activeGroup];
	MapEntry* entry = wp->entries;
	u32 flags;
	int j;
	int i;
	MapObject* obj;

	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		obj = entry->objects;
		for (j = 0; j < entry->numJoints; j++, obj++) {
			flags = obj->flags;
			if (flags & 0x400000) {
				obj->flags = flags & ~2;
				_mapDispMapObj(cam, obj);
				obj->flags = flags;
			}
		}
	}
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void _mapDispMapObj_NoMaterial(CameraId cam, MapObject* obj) {
	Mtx mtx;
	Mtx nrm;
	int i;

	PSMTXConcat(camGetPtr(cam)->view, obj->modelWorldMtx, mtx);
	GXLoadPosMtxImm(mtx, 0);
	PSMTXInvXpose(mtx, nrm);
	GXLoadNrmMtxImm(nrm, 0);
	GXSetCurrentMtx(0);
	GXSetCullMode(GX_CULL_ALL);
	GXSetNumChans(1);
#ifdef NONMATCHING
	GXSetChanMatColor(GX_COLOR0A0, (GXColor){0, 0, 0, 0});
#endif
#ifndef NONMATCHING
	GXSetChanMatColor(GX_COLOR0A0, *(GXColor*)&unk_80422f84); // FAKE: the target's named zero color
#endif
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
	GXSetNumTexGens(0);
	GXSetNumTevStages(1);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
	for (i = 0; i < obj->joints->partCount; i++) {
		mapSetPolygon(obj, obj->joints->parts[i].mesh);
	}
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void _mapDispMapGrp_NoMaterial(CameraId cam, MapObject* obj) {
	_mapDispMapObj_NoMaterial(cam, obj);
	if (obj->child) {
		_mapDispMapGrp_NoMaterial(cam, obj->child);
	}
	if ((obj->flags & 0x20) && obj->next) {
		_mapDispMapGrp_NoMaterial(cam, obj->next);
	}
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void mapDispMapObj_bbox(CameraId cam, MapObject* obj) {
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FF80
		opword 0x7C0802A6
		opword 0x90010084
		opword 0x93E1007C
		opword 0x93C10078
		opword 0x7C7E1B78
		opword 0x93A10074
		opword 0x7C9D2378
		bl sysWaitDrawSync
		bl GXClearBoundingBox
		opword 0x7FC3F378
		bl camGetPtr
		opword 0x3863011C
		opword 0x389D001C
		opword 0x38A1000C
		bl PSMTXConcat
		opword 0x3861000C
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x3861000C
		opword 0x3881003C
		bl PSMTXInvXpose
		opword 0x3861003C
		opword 0x38800000
		bl GXLoadNrmMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
		opword 0x38600003
		bl GXSetCullMode
		opword 0x38600001
		bl GXSetNumChans
		lwz r0, unk_80422f84(r2)
		opword 0x38810008
		opword 0x38600004
		opword 0x90010008
		bl GXSetChanMatColor
		opword 0x38600004
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0x39000000
		opword 0x39200002
		bl GXSetChanCtrl
		opword 0x38600000
		bl GXSetNumTexGens
		opword 0x38600001
		bl GXSetNumTevStages
		opword 0x38600000
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C00004
		bl GXSetTevOrder
		opword 0x38600000
		opword 0x38800004
		bl GXSetTevOp
		opword 0x3BE00000
		opword 0x7FFEFB78
		opword 0x4800001C
		opword 0x381E0064
		opword 0x7FA3EB78
		opword 0x7C84002E
		bl mapSetPolygon
		opword 0x3BDE0008
		opword 0x3BFF0001
		opword 0x809D0008
		opword 0x8004005C
		opword 0x7C1F0000
		opword 0x4180FFDC
		bl sysWaitDrawSync
		opword 0x387D00EC
		opword 0x389D00EE
		opword 0x38BD00F0
		opword 0x38DD00F2
		bl GXReadBoundingBox
		opword 0x80010084
		opword 0x83E1007C
		opword 0x83C10078
		opword 0x83A10074
		opword 0x7C0803A6
		opword 0x38210080
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
	int new_var[2];
	Mtx nrm;
	Mtx mtx;
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifdef NONMATCHING
	sysWaitDrawSync();
	GXClearBoundingBox();
	PSMTXConcat(camGetPtr(cam)->view, obj->modelWorldMtx, mtx);
	GXLoadPosMtxImm(mtx, 0);
	PSMTXInvXpose(mtx, nrm);
	GXLoadNrmMtxImm(nrm, 0);
	GXSetCurrentMtx(0);
	GXSetCullMode(GX_CULL_ALL);
	GXSetNumChans(1);
	GXSetChanMatColor(GX_COLOR0A0, (GXColor){0, 0, 0, 0});
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
	GXSetNumTexGens(0);
	GXSetNumTevStages(1);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
	for (new_var[1] = 0, new_var[0] = 0; obj->joints->partCount > new_var[1]; new_var[0] += 8, new_var[1]++) {
		mapSetPolygon(obj, *(void**)((u8*)obj->joints + 0x64 + new_var[0]));
	}
	sysWaitDrawSync();
	GXReadBoundingBox(&obj->screenRect[0], &obj->screenRect[1], &obj->screenRect[2], &obj->screenRect[3]);
}

#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapDispMapGrp_bbox(CameraId cam, MapObject* obj) {
	sysWaitDrawSync();
	GXClearBoundingBox();
	_mapDispMapGrp_NoMaterial(cam, obj);
	sysWaitDrawSync();
	GXReadBoundingBox(&obj->screenRect[0], &obj->screenRect[1], &obj->screenRect[2], &obj->screenRect[3]);
}

#ifdef NONMATCHING
const GXTexMtx texmtx_tbl[10] = {GX_TEXMTX0, GX_TEXMTX1, GX_TEXMTX2, GX_TEXMTX3, GX_TEXMTX4, GX_TEXMTX5, GX_TEXMTX6, GX_TEXMTX7, GX_TEXMTX8, GX_TEXMTX9};
const s32 texfmt_tbl[11] = {4, 5, 6, 14, 0, 1, 2, 3, 8, 9, 10};
const s32 texwrap_tbl[3] = {GX_CLAMP, GX_REPEAT, GX_MIRROR};
const s32 palfmt_tbl[2] = {1, 2};
const GXLightID lightid_tbl[8] = {GX_LIGHT0, GX_LIGHT1, GX_LIGHT2, GX_LIGHT3, GX_LIGHT4, GX_LIGHT5, GX_LIGHT6, GX_LIGHT7};
static inline BOOL mapClipTest(Vec* v) {
	if (v->z > -1.0f && v->z < 0.0f && v->x >= -1.0f && v->x <= 1.0f && v->y >= -1.0f && v->y <= 1.0f) {
		return TRUE;
	}
	return FALSE;
}
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifdef NONMATCHING
void dispEntry(CameraId camera, f32 order, s32 renderMode, void* callback, void* param);
#define MAP_CLIP_IN(v) ((v).z > -1.0f && (v).z < 0.0f && (v).x >= -1.0f && (v).x <= 1.0f && (v).y >= -1.0f && (v).y <= 1.0f)
#define MJF(j, off) (*(f32*)((u8*)(j) + (off)))

#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void mapDisp(void) {
#ifdef NONMATCHING
	MapWork* wp = &mapWork[activeGroup];
	CameraEntry* camera = camGetPtr(4);
	MapEntry* entry;
	MapObject* obj;
	int j, i;
	Mtx scale;
	Mtx mtx;
	Vec v;
	Vec center;
	f32 z;
	s32 mode;
	u8* joint;
	BOOL clipped;

	if (unk_80418458) {
		return;
	}
	entry = wp->entries;
	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		if (entry->rootMapObj != NULL) {
			PSMTXScale(scale, 1.0f, 1.0f, 1.0f);
			mapReCalcMatrix(entry->rootMapObj, scale, 0);
		}
		obj = entry->objects;
		for (j = 0; j < entry->numJoints; j++, obj++) {
			if (obj->flags & 0x4000) continue;
			if ((obj->flags & 1) && !(obj->flags & 0x80)) continue;
			if ((obj->flags & 0x40) && obj->color.a == 0) continue;
			if (obj->flags & 0x20000000) {
				obj->screenRect[2] = 0;
				obj->screenRect[3] = 0;
				obj->screenRect[0] = 0;
				obj->screenRect[1] = 0;
			}
			if (obj->flags & 0x20) continue;
			if (!(obj->flags & 0x10) && *(s32*)((u8*)obj->joints + 0x5C) < 1) continue;
			if (!(obj->flags & 0x800) && (entry->flags & 2) && entry->blend.a == 0) continue;
			if (!(obj->flags & 0x1000) && (entry->flags & 4) && entry->blend2.a == 0) continue;
			PSMTXConcat(camera->view, obj->modelWorldMtx, mtx);
			if ((obj->flags & 2) && !mapClipOffFlag) {
				joint = (u8*)obj->joints;
				clipped = FALSE;
				v.x = MJF(joint, 0x48); v.y = MJF(joint, 0x4C); v.z = MJF(joint, 0x50);
				PSMTXMultVec(mtx, &v, &v);
				PSMTX44MultVec(camera->projection, &v, &v);
				if (MAP_CLIP_IN(v)) goto vis;
				v.x = MJF(joint, 0x3C); v.y = MJF(joint, 0x40); v.z = MJF(joint, 0x44);
				PSMTXMultVec(mtx, &v, &v);
				PSMTX44MultVec(camera->projection, &v, &v);
				if (MAP_CLIP_IN(v)) goto vis;
				v.x = MJF(joint, 0x3C); v.y = MJF(joint, 0x4C); v.z = MJF(joint, 0x50);
				PSMTXMultVec(mtx, &v, &v);
				PSMTX44MultVec(camera->projection, &v, &v);
				if (MAP_CLIP_IN(v)) goto vis;
				v.x = MJF(joint, 0x48); v.y = MJF(joint, 0x40); v.z = MJF(joint, 0x50);
				PSMTXMultVec(mtx, &v, &v);
				PSMTX44MultVec(camera->projection, &v, &v);
				if (MAP_CLIP_IN(v)) goto vis;
				v.x = MJF(joint, 0x48); v.y = MJF(joint, 0x4C); v.z = MJF(joint, 0x44);
				PSMTXMultVec(mtx, &v, &v);
				PSMTXMultVec(mtx, &v, &v);
				PSMTX44MultVec(camera->projection, &v, &v);
				if (MAP_CLIP_IN(v)) goto vis;
				v.x = MJF(joint, 0x3C); v.y = MJF(joint, 0x40); v.z = MJF(joint, 0x50);
				PSMTXMultVec(mtx, &v, &v);
				PSMTX44MultVec(camera->projection, &v, &v);
				if (MAP_CLIP_IN(v)) goto vis;
				v.x = MJF(joint, 0x48); v.y = MJF(joint, 0x40); v.z = MJF(joint, 0x44);
				PSMTXMultVec(mtx, &v, &v);
				PSMTX44MultVec(camera->projection, &v, &v);
				if (MAP_CLIP_IN(v)) goto vis;
				v.x = MJF(joint, 0x3C); v.y = MJF(joint, 0x4C); v.z = MJF(joint, 0x44);
				PSMTXMultVec(mtx, &v, &v);
				PSMTX44MultVec(camera->projection, &v, &v);
				if (MAP_CLIP_IN(v)) goto vis;
				clipped = TRUE;
			vis:
				if (clipped) continue;
			}
			PSMTXMultVec(mtx, &obj->center, &center);
			PSMTX44MultVec(camera->projection, &center, &center);
			z = 5000.0f * center.z + 5000.0f;
			if (z < 0.0f) {
				z = 0.0f;
			} else if (z > 10000.0f) {
				z = 10000.0f;
			}
			z *= -1.0f;
			mode = obj->blendMode;
			if (*(s32*)((u8*)obj->joints + 0x5C) > 0) {
				if (mapObjIsTranslucent(obj->flags, obj->color,
						(*(MapMaterial**)((u8*)obj->joints + 0x60))->blendColor)) {
					mode = 2;
				}
			}
			if (obj->flags & 0x20000000) {
				dispEntry((CameraId)1, 5000.0f, 3, !(obj->flags & 0x10) ? mapDispMapObj_bbox : mapDispMapGrp_bbox, obj);
			}
			if (obj->flags & 0x80) {
				dispEntry((CameraId)1, z, mode, !(obj->flags & 0x10) ? mapDispMapObj_off : mapDispMapGrp_off, obj);
			}
			if (!(obj->flags & 1)) {
				dispEntry(obj->unk5, z, mode, !(obj->flags & 0x10) ? mapDispMapObj : mapDispMapGrp, obj);
			}
		}
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FF40
		opword 0x7C0802A6
		opword 0x900100C4
		opword 0xDBE100B0
		opword 0xF3E100B8
		opword 0xBF010090
		lwz r0, activeGroup(r13)
		opword 0x38600004
		lwz r4, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7FC40214
		bl camGetPtr
		lwz r0, unk_80418458(r13)
		opword 0x7C7F1B78
		opword 0x2C000000
		opword 0x408207CC
		opword 0x7FDDF378
		opword 0x3B400000
		opword 0x480007B4
		opword 0x801D00A8
		opword 0x28000000
		opword 0x41820028
		lfs f1, float_10_80419864(r2)
		opword 0x38610058
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x807D00A8
		opword 0x38810058
		opword 0x38A00000
		bl mapReCalcMatrix
		opword 0x839D0154
		opword 0x3B600000
		opword 0x48000764
		opword 0x807C0000
		opword 0x54600463
		opword 0x40820750
		opword 0x546007FF
		opword 0x4182000C
		opword 0x54600631
		opword 0x41820740
		opword 0x54600673
		opword 0x41820010
		opword 0x881C000F
		opword 0x28000000
		opword 0x4182072C
		opword 0x54600085
		opword 0x41820018
		opword 0x38000000
		opword 0xB01C00F0
		opword 0xB01C00F2
		opword 0xB01C00EC
		opword 0xB01C00EE
		opword 0x809C0000
		opword 0x548006B5
		opword 0x40820704
		opword 0x548006F7
		opword 0x40820014
		opword 0x807C0008
		opword 0x8003005C
		opword 0x2C000001
		opword 0x418006EC
		opword 0x54800529
		opword 0x4082001C
		opword 0xA01D0004
		opword 0x540007BD
		opword 0x41820010
		opword 0x881D0019
		opword 0x28000000
		opword 0x418206CC
		opword 0x548004E7
		opword 0x4082001C
		opword 0xA01D0004
		opword 0x5400077B
		opword 0x41820010
		opword 0x881D001D
		opword 0x28000000
		opword 0x418206AC
		opword 0x387F011C
		opword 0x389C001C
		opword 0x38A10028
		bl PSMTXConcat
		opword 0x801C0000
		opword 0x540007BD
		opword 0x418204B4
		lwz r0, mapClipOffFlag(r13)
		opword 0x2C000000
		opword 0x408204A8
		opword 0x833C0008
		opword 0x3881001C
		opword 0x7C852378
		opword 0x38610028
		opword 0xC0190048
		opword 0x3B000000
		opword 0xD001001C
		opword 0xC019004C
		opword 0xD0010020
		opword 0xC0190050
		opword 0xD0010024
		bl PSMTXMultVec
		opword 0x3881001C
		opword 0x387F015C
		opword 0x7C852378
		bl PSMTX44MultVec
		opword 0xC0410024
		lfs f1, float_neg1_804198a8(r2)
		opword 0xFC020840
		opword 0x4081004C
		lfs f0, float_0_80419850(r2)
		opword 0xFC020040
		opword 0x40800040
		opword 0xC041001C
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820030
		lfs f0, float_1_80419860(r2)
		opword 0xFC020040
		opword 0x4C401382
		opword 0x40820020
		opword 0xC0410020
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820010
		opword 0xFC020040
		opword 0x4C401382
		opword 0x41820408
		opword 0xC019003C
		opword 0x3881001C
		opword 0x7C852378
		opword 0x38610028
		opword 0xD001001C
		opword 0xC0190040
		opword 0xD0010020
		opword 0xC0190044
		opword 0xD0010024
		bl PSMTXMultVec
		opword 0x3881001C
		opword 0x387F015C
		opword 0x7C852378
		bl PSMTX44MultVec
		opword 0xC0410024
		lfs f1, float_neg1_804198a8(r2)
		opword 0xFC020840
		opword 0x4081004C
		lfs f0, float_0_80419850(r2)
		opword 0xFC020040
		opword 0x40800040
		opword 0xC041001C
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820030
		lfs f0, float_1_80419860(r2)
		opword 0xFC020040
		opword 0x4C401382
		opword 0x40820020
		opword 0xC0410020
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820010
		opword 0xFC020040
		opword 0x4C401382
		opword 0x41820378
		opword 0xC019003C
		opword 0x3881001C
		opword 0x7C852378
		opword 0x38610028
		opword 0xD001001C
		opword 0xC019004C
		opword 0xD0010020
		opword 0xC0190050
		opword 0xD0010024
		bl PSMTXMultVec
		opword 0x3881001C
		opword 0x387F015C
		opword 0x7C852378
		bl PSMTX44MultVec
		opword 0xC0410024
		lfs f1, float_neg1_804198a8(r2)
		opword 0xFC020840
		opword 0x4081004C
		lfs f0, float_0_80419850(r2)
		opword 0xFC020040
		opword 0x40800040
		opword 0xC041001C
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820030
		lfs f0, float_1_80419860(r2)
		opword 0xFC020040
		opword 0x4C401382
		opword 0x40820020
		opword 0xC0410020
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820010
		opword 0xFC020040
		opword 0x4C401382
		opword 0x418202E8
		opword 0xC0190048
		opword 0x3881001C
		opword 0x7C852378
		opword 0x38610028
		opword 0xD001001C
		opword 0xC0190040
		opword 0xD0010020
		opword 0xC0190050
		opword 0xD0010024
		bl PSMTXMultVec
		opword 0x3881001C
		opword 0x387F015C
		opword 0x7C852378
		bl PSMTX44MultVec
		opword 0xC0410024
		lfs f1, float_neg1_804198a8(r2)
		opword 0xFC020840
		opword 0x4081004C
		lfs f0, float_0_80419850(r2)
		opword 0xFC020040
		opword 0x40800040
		opword 0xC041001C
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820030
		lfs f0, float_1_80419860(r2)
		opword 0xFC020040
		opword 0x4C401382
		opword 0x40820020
		opword 0xC0410020
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820010
		opword 0xFC020040
		opword 0x4C401382
		opword 0x41820258
		opword 0xC0190048
		opword 0x3881001C
		opword 0x7C852378
		opword 0x38610028
		opword 0xD001001C
		opword 0xC019004C
		opword 0xD0010020
		opword 0xC0190044
		opword 0xD0010024
		bl PSMTXMultVec
		opword 0x3881001C
		opword 0x38610028
		opword 0x7C852378
		bl PSMTXMultVec
		opword 0x3881001C
		opword 0x387F015C
		opword 0x7C852378
		bl PSMTX44MultVec
		opword 0xC0410024
		lfs f1, float_neg1_804198a8(r2)
		opword 0xFC020840
		opword 0x4081004C
		lfs f0, float_0_80419850(r2)
		opword 0xFC020040
		opword 0x40800040
		opword 0xC041001C
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820030
		lfs f0, float_1_80419860(r2)
		opword 0xFC020040
		opword 0x4C401382
		opword 0x40820020
		opword 0xC0410020
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820010
		opword 0xFC020040
		opword 0x4C401382
		opword 0x418201B8
		opword 0xC019003C
		opword 0x3881001C
		opword 0x7C852378
		opword 0x38610028
		opword 0xD001001C
		opword 0xC0190040
		opword 0xD0010020
		opword 0xC0190050
		opword 0xD0010024
		bl PSMTXMultVec
		opword 0x3881001C
		opword 0x387F015C
		opword 0x7C852378
		bl PSMTX44MultVec
		opword 0xC0410024
		lfs f1, float_neg1_804198a8(r2)
		opword 0xFC020840
		opword 0x4081004C
		lfs f0, float_0_80419850(r2)
		opword 0xFC020040
		opword 0x40800040
		opword 0xC041001C
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820030
		lfs f0, float_1_80419860(r2)
		opword 0xFC020040
		opword 0x4C401382
		opword 0x40820020
		opword 0xC0410020
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820010
		opword 0xFC020040
		opword 0x4C401382
		opword 0x41820128
		opword 0xC0190048
		opword 0x3881001C
		opword 0x7C852378
		opword 0x38610028
		opword 0xD001001C
		opword 0xC0190040
		opword 0xD0010020
		opword 0xC0190044
		opword 0xD0010024
		bl PSMTXMultVec
		opword 0x3881001C
		opword 0x387F015C
		opword 0x7C852378
		bl PSMTX44MultVec
		opword 0xC0410024
		lfs f1, float_neg1_804198a8(r2)
		opword 0xFC020840
		opword 0x4081004C
		lfs f0, float_0_80419850(r2)
		opword 0xFC020040
		opword 0x40800040
		opword 0xC041001C
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820030
		lfs f0, float_1_80419860(r2)
		opword 0xFC020040
		opword 0x4C401382
		opword 0x40820020
		opword 0xC0410020
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820010
		opword 0xFC020040
		opword 0x4C401382
		opword 0x41820098
		opword 0xC019003C
		opword 0x3881001C
		opword 0x7C852378
		opword 0x38610028
		opword 0xD001001C
		opword 0xC019004C
		opword 0xD0010020
		opword 0xC0190044
		opword 0xD0010024
		bl PSMTXMultVec
		opword 0x3881001C
		opword 0x387F015C
		opword 0x7C852378
		bl PSMTX44MultVec
		opword 0xC0410024
		lfs f1, float_neg1_804198a8(r2)
		opword 0xFC020840
		opword 0x4081004C
		lfs f0, float_0_80419850(r2)
		opword 0xFC020040
		opword 0x40800040
		opword 0xC041001C
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820030
		lfs f0, float_1_80419860(r2)
		opword 0xFC020040
		opword 0x4C401382
		opword 0x40820020
		opword 0xC0410020
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820010
		opword 0xFC020040
		opword 0x4C401382
		opword 0x41820008
		opword 0x3B000001
		opword 0x2C180000
		opword 0x408201E0
		opword 0x38610028
		opword 0x389C0010
		opword 0x38A10010
		bl PSMTXMultVec
		opword 0x38810010
		opword 0x387F015C
		opword 0x7C852378
		bl PSMTX44MultVec
		lfs f2, float_5000_804198ac(r2)
		opword 0xC0210018
		lfs f0, float_0_80419850(r2)
		opword 0xEFE2107A
		opword 0xFC1F0040
		opword 0x4080000C
		opword 0xFFE00090
		opword 0x48000014
		lfs f0, float_10000_804198b0(r2)
		opword 0xFC1F0040
		opword 0x40810008
		opword 0xFFE00090
		opword 0x807C0008
		lfs f0, float_neg1_804198a8(r2)
		opword 0x8003005C
		opword 0xEFFF0032
		opword 0x8B3C0004
		opword 0x2C000000
		opword 0x408100CC
		opword 0x80630060
		opword 0x80BC0000
		opword 0x809C000C
		opword 0x8063010C
		opword 0x54A00673
		opword 0x9081000C
		opword 0x90610008
		opword 0x41820018
		opword 0x8801000F
		opword 0x280000FF
		opword 0x4182000C
		opword 0x38000001
		opword 0x4800008C
		opword 0x8801000B
		opword 0x280000FF
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000078
		opword 0x54A00529
		opword 0x40820034
		lwz r0, activeGroup(r13)
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7C630214
		opword 0xA0030004
		opword 0x540007BD
		opword 0x41820018
		opword 0x88030019
		opword 0x280000FF
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000040
		opword 0x54A004E7
		opword 0x40820034
		lwz r0, activeGroup(r13)
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7C630214
		opword 0xA0030004
		opword 0x5400077B
		opword 0x41820018
		opword 0x8803001D
		opword 0x280000FF
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000008
		opword 0x38000000
		opword 0x2C000000
		opword 0x41820008
		opword 0x3B200002
		opword 0x807C0000
		opword 0x54600085
		opword 0x41820030
		opword 0x546006F7
		lis r3, mapDispMapGrp_bbox@ha
		lfs f1, float_5000_804198ac(r2)
		addi r5, r3, mapDispMapGrp_bbox@l
		opword 0x38600001
		opword 0x38800003
		opword 0x4082000C
		lis r5, mapDispMapObj_bbox@ha
		addi r5, r5, mapDispMapObj_bbox@l
		opword 0x7F86E378
		bl dispEntry
		opword 0x807C0000
		opword 0x54600631
		opword 0x41820030
		opword 0x546006F7
		opword 0xFC20F890
		lis r3, mapDispMapGrp_off@ha
		opword 0x7F24CB78
		addi r5, r3, mapDispMapGrp_off@l
		opword 0x38600001
		opword 0x4082000C
		lis r5, mapDispMapObj_off@ha
		addi r5, r5, mapDispMapObj_off@l
		opword 0x7F86E378
		bl dispEntry
		opword 0x807C0000
		opword 0x546007FF
		opword 0x40820030
		opword 0x546006F7
		lis r3, mapDispMapGrp@ha
		addi r5, r3, mapDispMapGrp@l
		opword 0xFC20F890
		opword 0x887C0005
		opword 0x7F24CB78
		opword 0x4082000C
		lis r5, mapDispMapObj@ha
		addi r5, r5, mapDispMapObj@l
		opword 0x7F86E378
		bl dispEntry
		opword 0x3B7B0001
		opword 0x3B9C0134
		opword 0x801D0150
		opword 0x7C1B0000
		opword 0x4180F898
		opword 0x3BBD0178
		opword 0x3B5A0001
		opword 0x801E0000
		opword 0x7C1A0000
		opword 0x4180F848
		opword 0xE3E100B8
		opword 0xCBE100B0
		opword 0xBB010090
		opword 0x800100C4
		opword 0x7C0803A6
		opword 0x382100C0
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifdef NONMATCHING
typedef struct MapFileLight {
	const char* name; // 0x0
} MapFileLight;

typedef struct MapFileLightTable {
	s32 count;              // 0x0
	MapFileLight* lights[]; // 0x4
} MapFileLightTable;

#define MAP_LIGHT_TABLE(entry) ((MapFileLightTable*)(entry)->lightTable)

#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
s32 mapSetLight(MapObject* obj, LightEntry** lights) {
	Vec pos;
	s32 count;
	s32 i;
	LightEntry* light;
	MapJointDrawModeEx* dm;

	count = 0;
	PSMTXMultVec(obj->modelWorldMtx, &obj->center, &pos);
	dm = (MapJointDrawModeEx*)obj->joints->drawMode;
	if (dm->flags & 8) {
		if (!dm->lightMask) {
			count = lightGetNearObj(&pos, lights, 8, 0);
		}
		else {
			for (i = 0; i < 32; i++) {
				if (((MapJointDrawModeEx*)obj->joints->drawMode)->lightMask & (1 << i)) {
					light = lightNameToPtr(MAP_LIGHT_TABLE(&mapWork[activeGroup].entries[obj->groupIndex])->lights[i]->name);
					if (!(light->flags & 0x8000)) {
						lights[count] = light;
						count++;
						if (count >= 8) {
							break;
						}
					}
				}
			}
			if (count < 8) {
				count += lightGetNearObj(&pos, &lights[count], 8 - count, 0);
			}
		}
	}
	else if (dm->lightMask) {
		for (i = 0; i < 32; i++) {
			if (((MapJointDrawModeEx*)obj->joints->drawMode)->lightMask & (1 << i)) {
				light = lightNameToPtr(MAP_LIGHT_TABLE(&mapWork[activeGroup].entries[obj->groupIndex])->lights[i]->name);
				if (!(light->flags & 0x8000)) {
					lights[count] = light;
						count++;
					if (count >= 8) {
						break;
					}
				}
			}
		}
	}
	else {
		count = 0; // FAKE: redundant (count is already 0); the target emits this else branch
	}
	return count;
}

#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifdef NONMATCHING
static u32 texture_0[64] ATTRIBUTE_ALIGN(32) = {
	0xEB88E228, 0x55FFAA00, 0x00000000, 0x00000000,
	0xF528EC08, 0x55FFAA00, 0x00000000, 0x00000000,
	0xFEE8F5A8, 0x55FFAA00, 0x00000000, 0x00000000,
	0xFF47D6E8, 0x00AAFF55, 0x00000000, 0x00000000,
	0xBEA8860A, 0x00AAFF55, 0x00000000, 0x00000000,
	0x7DEA0D8B, 0x00AAFF55, 0x00000000, 0x00000000,
	0x056B054A, 0x00AAAA00, 0x00000000, 0x00000000,
	0x056B054E, 0x0000AAFF, 0x00000000, 0x00000000,
	0x05BA0570, 0x55FFAAAA, 0x00000000, 0x00000000,
	0x05DE05BA, 0x55FFAAAA, 0x00000000, 0x00000000,
	0x05BD051B, 0x0000AA55, 0x00000000, 0x00000000,
	0x1376049A, 0x55FFAA00, 0x00000000, 0x00000000,
	0x33154253, 0x00AA5555, 0x00000000, 0x00000000,
	0x6A333A53, 0xFFFFAA00, 0x00000000, 0x00000000,
	0xB1F28212, 0x55FFAA00, 0x00000000, 0x00000000,
	0xE9F2C212, 0x55FFAA00, 0x00000000, 0x00000000,
};
__declspec(section ".data") static void* jumptable_803033E0[] = {
    (char*)mapSetMaterialTev + 0x58,
    (char*)mapSetMaterialTev + 0x90,
    (char*)mapSetMaterialTev + 0x23C,
    (char*)mapSetMaterialTev + 0x594,
    (char*)mapSetMaterialTev + 0x740,
    (char*)mapSetMaterialTev + 0x8EC,
    (char*)mapSetMaterialTev + 0xB24,
    (char*)mapSetMaterialTev + 0xCD0,
    (char*)mapSetMaterialTev + 0xE7C,
    (char*)mapSetMaterialTev + 0xF80,
    (char*)mapSetMaterialTev + 0x12A4,
    (char*)mapSetMaterialTev + 0x12A4,
    (char*)mapSetMaterialTev + 0x3E8,
};
__declspec(section ".data") static void* jumptable_80303414[] = {
    (char*)mapBuildTexture + 0x134,
    (char*)mapBuildTexture + 0x144,
    (char*)mapBuildTexture + 0x154,
    (char*)mapBuildTexture + 0x164,
    (char*)mapBuildTexture + 0xF4,
    (char*)mapBuildTexture + 0x104,
    (char*)mapBuildTexture + 0x114,
    (char*)mapBuildTexture + 0x1A0,
    (char*)mapBuildTexture + 0x174,
    (char*)mapBuildTexture + 0x184,
    (char*)mapBuildTexture + 0x194,
    (char*)mapBuildTexture + 0x1A0,
    (char*)mapBuildTexture + 0x1A0,
    (char*)mapBuildTexture + 0x1A0,
    (char*)mapBuildTexture + 0x124,
};

#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#endif
#pragma push
#ifdef NONMATCHING
#pragma opt_lifetimes off
#endif
#ifndef NONMATCHING
#pragma optimization_level 0  // lets the prologue scheduler run
#endif
void mapSetMaterialTev(s32 texCount, s32 drawMode, s32 flags, Mtx mtx) {
#ifdef NONMATCHING
	static f32 scrl_uv[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	GXTexMapID map;
	GXTexCoordID coord;
	s32 tevStage;
	s32 indStages;
	s32 i;
	Mtx queen_mtx;

	map = (GXTexMapID)texCount;
	coord = (GXTexCoordID)texCount;
	indStages = 0;
	
	if ((s32)texCount > 0) {
		switch (drawMode) {
			case 0:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
				GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE1;
				break;

			case 1:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE3;
				break;

			case 2:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXA, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE3;
				break;

			case 12:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE3;
				break;

			case 3:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_ZERO, GX_CC_TEXA, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_ZERO, GX_CA_TEXA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE3;
				break;

			case 4:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_TEXC, GX_CC_CPREV, GX_CC_APREV, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE3;
				break;

			case 5:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG1);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG1);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD2, GX_TEXMAP2, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C0, GX_CC_C1, GX_CC_TEXA, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_A0, GX_CA_A1, GX_CA_TEXA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE4;
				break;

			case 6:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_APREV, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE3;
				break;

			case 7:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_ZERO, GX_CA_TEXA, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE3;
				break;

			case 8:
				GXSetTevColor(GX_TEVREG0, (GXColor) {
					0, (u8)((127.0f * sinf((TWO_PI * (f32)(2 * gp->retraceCount)) / 360.0f)) + 127.0f),
					0, 0}); //TODO: check
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_C0);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_A0);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE1;
				break;

			case 9:
				for (i = 0; i < 4; i++) {
					scrl_uv[i] += queen_uv[i];
					if (scrl_uv[i] > 100.0f) {
						scrl_uv[i] -= 100.0f;
					}
					if (scrl_uv[i] < -100.0f) {
						scrl_uv[i] += 100.0f;
					}
				}

				MTXTrans(queen_mtx, scrl_uv[0], scrl_uv[1], 0.0f);
				GXLoadTexMtxImm(queen_mtx, 0x1E, GX_MTX2x4);
				GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
				MTXTrans(queen_mtx, scrl_uv[2], scrl_uv[3], 0.0f);
				GXLoadTexMtxImm(queen_mtx, 0x21, GX_MTX2x4);
				GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_ZERO, GX_CA_TEXA, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE3;
				break;

			default:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE1;
				break;
		}
#endif
#ifndef NONMATCHING
	char _af_pad[588];
	asm {
		cmpwi r3, 0x0
		lis r7, vec3_802c16d8@ha
#endif
	}
#ifdef NONMATCHING
	else {
		GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
		GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
		GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
		GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
		tevStage = GX_TEVSTAGE1;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x7C9D2378
		opword 0x7CBE2B78
		opword 0x7CDF3378
		opword 0x7C7B1B78
		opword 0x7C7A1B78
		addi r28, r7, vec3_802c16d8@l
		opword 0x3B000000
		opword 0x40811304
		opword 0x281D000C
		opword 0x41811268
		lis r3, jumptable_803033E0@ha
		opword 0x57A0103A
		addi r3, r3, jumptable_803033E0@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00004
		bl GXSetTevOrder
		opword 0x38600000
		opword 0x38800000
		bl GXSetTevOp
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B200001
		opword 0x4800133C
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
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
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
		opword 0x38800000
		opword 0x38A00008
		opword 0x38C00009
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600001
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x38600002
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C00004
		bl GXSetTevOrder
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600002
		opword 0x3880000F
		opword 0x38A00000
		opword 0x38C0000A
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600002
		opword 0x38800007
		opword 0x38A00000
		opword 0x38C00005
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B200003
		opword 0x48001190
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
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
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
		opword 0x38A00000
		opword 0x38C00009
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600001
		opword 0x38800007
		opword 0x38A00000
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x38600002
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C00004
		bl GXSetTevOrder
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600002
		opword 0x3880000F
		opword 0x38A00000
		opword 0x38C0000A
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600002
		opword 0x38800007
		opword 0x38A00000
		opword 0x38C00005
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B200003
		opword 0x48000FE4
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
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
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
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00000
		bl GXSetTevColorIn
		opword 0x38600001
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x38600002
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C00004
		bl GXSetTevOrder
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600002
		opword 0x3880000F
		opword 0x38A00000
		opword 0x38C0000A
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600002
		opword 0x38800007
		opword 0x38A00000
		opword 0x38C00005
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B200003
		opword 0x48000E38
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
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
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
		opword 0x38800000
		opword 0x38A0000F
		opword 0x38C00009
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00007
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x38600002
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C00004
		bl GXSetTevOrder
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600002
		opword 0x3880000F
		opword 0x38A00000
		opword 0x38C0000A
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600002
		opword 0x38800007
		opword 0x38A00000
		opword 0x38C00005
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B200003
		opword 0x48000C8C
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
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
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
		opword 0x38A00000
		opword 0x38C00008
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600001
		opword 0x38800007
		opword 0x38A00000
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600002
		opword 0x38800008
		opword 0x38A00000
		opword 0x38C00001
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600002
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B200003
		opword 0x48000AE0
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
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00008
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
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
		opword 0x39000002
		bl GXSetTevColorOp
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000002
		bl GXSetTevAlphaOp
		opword 0x38600001
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00008
		bl GXSetTevColorIn
		opword 0x38600001
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x38600002
		opword 0x38800002
		opword 0x38A00002
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600002
		opword 0x38800002
		opword 0x38A00004
		opword 0x38C00009
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600002
		opword 0x38800001
		opword 0x38A00002
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x38600003
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C00004
		bl GXSetTevOrder
		opword 0x38600003
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600003
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600003
		opword 0x3880000F
		opword 0x38A00000
		opword 0x38C0000A
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600003
		opword 0x38800007
		opword 0x38A00000
		opword 0x38C00005
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600003
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B200004
		opword 0x480008A8
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
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
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
		opword 0x38800000
		opword 0x38A00008
		opword 0x38C00001
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600001
		opword 0x38800007
		opword 0x38A00004
		opword 0x38C00000
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x38600002
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C00004
		bl GXSetTevOrder
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600002
		opword 0x3880000F
		opword 0x38A00000
		opword 0x38C0000A
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600002
		opword 0x38800007
		opword 0x38A00000
		opword 0x38C00005
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B200003
		opword 0x480006FC
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
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
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
		opword 0x38800000
		opword 0x38A00008
		opword 0x38C00009
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00007
		opword 0x38C00004
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x38600002
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C00004
		bl GXSetTevOrder
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600002
		opword 0x3880000F
		opword 0x38A00000
		opword 0x38C0000A
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600002
		opword 0x38800007
		opword 0x38A00000
		opword 0x38C00005
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B200003
		opword 0x48000550
		lwz r3, gp(r13)
		opword 0x3C004330
		lwz r4, unk_80422f88(r2)
		opword 0x8063001C
		stw r0, _af_pad+568(r1)
		opword 0x5460083C
		opword 0xC85C02C8
		opword 0x90010244
		lfs f3, float_6p2832_80419878(r2)
		opword 0xC8210240
		lfs f0, float_360_8041987c(r2)
		opword 0xEC211028
		opword 0x90810044
		opword 0xEC230072
		opword 0xEC210024
		bl sin
		opword 0xFC200818
		lfs f0, float_127_80419880(r2)
		opword 0x38810048
		opword 0x38600001
		opword 0xEC00007A
		opword 0xFC00001E
		opword 0xD8010248
		opword 0x8001024C
		opword 0x98010045
		opword 0x80010044
		opword 0x90010048
		bl GXSetTevColor
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
		opword 0x38A0000A
		opword 0x38C00008
		opword 0x38E00002
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00005
		opword 0x38C00004
		opword 0x38E00001
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B200001
		opword 0x4800044C
		lis r3, queen_uv@ha
		lfs f3, g5_scrl_uv_s1622(r13)
		lfsu f0, queen_uv@l(r3)
		la r4, g5_scrl_uv_s1622(r13)
		lfs f2, float_100_80419884(r2)
		opword 0xEC03002A
		lfs f1, float_neg100_80419888(r2)
		stfs f0, g5_scrl_uv_s1622(r13)
		lfs f0, g5_scrl_uv_s1622(r13)
		opword 0xFC001040
		opword 0x4081000C
		opword 0xEC001028
		opword 0xD0040000
		opword 0xC0040000
		opword 0xFC000840
		opword 0x4080000C
		opword 0xEC00102A
		opword 0xD0040000
		opword 0xC0640004
		opword 0xC4030004
		opword 0xEC03002A
		opword 0xD0040004
		opword 0xC4040004
		opword 0xFC001040
		opword 0x4081000C
		opword 0xEC001028
		opword 0xD0040000
		opword 0xC0040000
		opword 0xFC000840
		opword 0x4080000C
		opword 0xEC00102A
		opword 0xD0040000
		opword 0xC0640004
		opword 0xC4030004
		opword 0xEC03002A
		opword 0xD0040004
		opword 0xC4040004
		opword 0xFC001040
		opword 0x4081000C
		opword 0xEC001028
		opword 0xD0040000
		opword 0xC0040000
		opword 0xFC000840
		opword 0x4080000C
		opword 0xEC00102A
		opword 0xD0040000
		opword 0xC0640004
		opword 0xC0030004
		opword 0xEC03002A
		opword 0xD0040004
		opword 0xC4040004
		opword 0xFC001040
		opword 0x4081000C
		opword 0xEC001028
		opword 0xD0040000
		opword 0xC0040000
		opword 0xFC000840
		opword 0x4080000C
		opword 0xEC00102A
		opword 0xD0040000
		la r3, g5_scrl_uv_s1622(r13)
		lfs f1, g5_scrl_uv_s1622(r13)
		opword 0xC0430004
		opword 0x3861020C
		lfs f3, float_0_80419850(r2)
		bl PSMTXTrans
		opword 0x3861020C
		opword 0x3880001E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0001E
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		la r4, g5_scrl_uv_s1622(r13)
		lfs f3, float_0_80419850(r2)
		opword 0xC0240008
		opword 0x3861020C
		opword 0xC044000C
		bl PSMTXTrans
		opword 0x3861020C
		opword 0x38800021
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x38600001
		opword 0x38800001
		opword 0x38A00005
		opword 0x38C00021
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
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
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
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
		opword 0x38800000
		opword 0x38A00008
		opword 0x38C00009
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00007
		opword 0x38C00004
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x38600002
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C00004
		bl GXSetTevOrder
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600002
		opword 0x3880000F
		opword 0x38A00000
		opword 0x38C0000A
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600002
		opword 0x38800007
		opword 0x38A00000
		opword 0x38C00005
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B200003
		opword 0x48000128
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
		opword 0x38A0000A
		opword 0x38C00008
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00005
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B200001
		opword 0x48000094
		opword 0x38600000
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C00004
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
		opword 0x38E0000A
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00005
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B200001
		opword 0x57C000C7
		opword 0x408200AC
		opword 0x7F23CB78
		opword 0x3880000C
		bl GXSetTevKColorSel
		opword 0x7F23CB78
		opword 0x3880001C
		bl GXSetTevKAlphaSel
		opword 0x7F23CB78
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F23CB78
		opword 0x3880000F
		opword 0x38A00000
		opword 0x38C0000E
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7F23CB78
		opword 0x38800007
		opword 0x38A00000
		opword 0x38C00006
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B390001
		opword 0x57C0077B
		opword 0x4182012C
		bl shadowGetCharShadowProjection
		opword 0x2C030000
		opword 0x41820120
		bl shadowGetCharShadowTexObj
		opword 0x28030000
		opword 0x41820114
		bl shadowGetCharShadowColor
		opword 0x90610058
		bl shadowGetCharShadowProjTexMtx
		opword 0x7FE4FB78
		opword 0x38A101DC
		bl PSMTXConcat
		opword 0x5774103A
		opword 0x3ABC0098
		opword 0x7CD5A02E
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7C95A02E
		opword 0x386101DC
		opword 0x38A00000
		bl GXLoadTexMtxImm
		bl shadowGetCharShadowTexObj
		opword 0x7F64DB78
		bl GXLoadTexObj
		opword 0x7F23CB78
		opword 0x7F44D378
		opword 0x7F65DB78
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A0000E
		opword 0x38C00008
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7F23CB78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x80010058
		opword 0x38810040
		opword 0x38600001
		opword 0x90010040
		bl GXSetTevKColor
		opword 0x7F23CB78
		opword 0x3880000D
		bl GXSetTevKColorSel
		opword 0x3B390001
		opword 0x3B7B0001
		opword 0x3B5A0001
		opword 0x57C0056B
		opword 0x418201E8
		opword 0x3879FFFF
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000001
		bl GXSetTevColorOp
		opword 0x3879FFFF
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000001
		bl GXSetTevAlphaOp
		opword 0x7FE4FB78
		opword 0x38A101AC
		la r3, projMtx(r13)
		bl PSMTXConcat
		opword 0x5774103A
		opword 0x3ABC0098
		opword 0x7CD5A02E
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7C95A02E
		opword 0x386101AC
		opword 0x38A00000
		bl GXLoadTexMtxImm
		lwz r4, projTexImgRef(r13)
		la r3, projTexObj(r13)
		bl smartTexObj
		opword 0x7F64DB78
		bl GXLoadTexObj
		opword 0x7F23CB78
		opword 0x7F44D378
		opword 0x7F65DB78
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00001
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F23CB78
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00004
		bl GXSetTevColorIn
		opword 0x7F23CB78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x7F23CB78
		opword 0x38800003
		opword 0x38A00003
		bl GXSetTevSwapMode
		opword 0x38600003
		opword 0x38800000
		opword 0x38A00001
		opword 0x38C00002
		opword 0x38E00000
		bl GXSetTevSwapModeTable
		lwz r0, dat_80419800(r2)
		opword 0x3881003C
		opword 0x38600002
		opword 0x9001003C
		bl GXSetTevColor
		opword 0x3A990001
		opword 0x388000FF
		opword 0x7E83A378
		opword 0x38A000FF
		opword 0x38C000FF
		opword 0x3B7B0001
		opword 0x3B5A0001
		bl GXSetTevOrder
		opword 0x7E83A378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7E83A378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7E83A378
		opword 0x38800002
		opword 0x38A00000
		opword 0x38C00001
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7E83A378
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00001
		bl GXSetTevAlphaIn
		opword 0x7E83A378
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B390002
		opword 0x57C003DF
		opword 0x41820A40
		bl shadowGetDepthShadowTexObj
		opword 0x28030000
		opword 0x41820A34
		bl shadowGetDepthShadowTexObj
		opword 0x7C771B78
		bl shadowGetDepthShadowDepthMtx
		opword 0x7C761B78
		bl shadowGetDepthShadowProjTexMtx
		opword 0x7C751B78
		bl shadowGetDepthShadowColor
		opword 0x90610054
		bl shadowGetDepthShadowConfig
		opword 0x8003003C
		opword 0x2C000003
		opword 0x418204EC
		opword 0x4080001C
		opword 0x2C000001
		opword 0x418202E0
		opword 0x408003DC
		opword 0x2C000000
		opword 0x40800018
		opword 0x480009E8
		opword 0x2C000005
		opword 0x418208CC
		opword 0x408009DC
		opword 0x480007AC
		opword 0x3879FFFF
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000001
		bl GXSetTevColorOp
		opword 0x3879FFFF
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000001
		bl GXSetTevAlphaOp
		opword 0x7F23CB78
		opword 0x7F44D378
		opword 0x7F65DB78
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F23CB78
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00008
		bl GXSetTevColorIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F23CB78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x5774103A
		addi r19, r28, 0x98
		opword 0x7CD3A02E
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		bl shadowGetRamp8TexObj
		opword 0x7F64DB78
		bl GXLoadTexObj
		opword 0x7EC3B378
		opword 0x7FE4FB78
		opword 0x38A1017C
		bl PSMTXConcat
		opword 0x7C93A02E
		opword 0x3861017C
		opword 0x38A00000
		bl GXLoadTexMtxImm
		opword 0x3A790001
		opword 0x3ADA0001
		opword 0x3B7B0001
		opword 0x38C000FF
		opword 0x7E639B78
		opword 0x7EC4B378
		opword 0x7F65DB78
		bl GXSetTevOrder
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00008
		opword 0x38C0000C
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7E639B78
		opword 0x38800008
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7E639B78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x5774103A
		opword 0x3A7C0098
		opword 0x7CD3A02E
		opword 0x7EC3B378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7EE3BB78
		opword 0x7F64DB78
		bl GXLoadTexObj
		opword 0x7EA3AB78
		opword 0x7FE4FB78
		opword 0x38A1017C
		bl PSMTXConcat
		opword 0x7C93A02E
		opword 0x3861017C
		opword 0x38A00000
		bl GXLoadTexMtxImm
		opword 0x3A790002
		opword 0x388000FF
		opword 0x7E639B78
		opword 0x38A000FF
		opword 0x38C000FF
		opword 0x3B7B0001
		opword 0x3B5A0002
		bl GXSetTevOrder
		opword 0x7E639B78
		opword 0x3880000F
		opword 0x38A0000E
		opword 0x38C00000
		opword 0x38E00002
		bl GXSetTevColorIn
		opword 0x7E639B78
		opword 0x38800001
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x80010054
		opword 0x38810038
		opword 0x38600001
		opword 0x90010038
		bl GXSetTevKColor
		opword 0x7E639B78
		opword 0x3880000D
		bl GXSetTevKColorSel
		opword 0x7E639B78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00001
		bl GXSetTevAlphaIn
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B390003
		opword 0x4800071C
		lwz r0, dat_80419804(r2)
		opword 0x38810034
		opword 0x38600002
		opword 0x90010034
		bl GXSetTevColor
		opword 0x7F23CB78
		opword 0x7F44D378
		opword 0x7F65DB78
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F23CB78
		opword 0x3880000F
		opword 0x38A00008
		opword 0x38C00004
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F23CB78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x5774103A
		opword 0x3A7C0098
		opword 0x7CD3A02E
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		bl shadowGetRamp8TexObj
		opword 0x7F64DB78
		bl GXLoadTexObj
		opword 0x7EC3B378
		opword 0x7FE4FB78
		opword 0x38A1017C
		bl PSMTXConcat
		opword 0x7C93A02E
		opword 0x3861017C
		opword 0x38A00000
		bl GXLoadTexMtxImm
		opword 0x3B390001
		opword 0x3B7B0001
		opword 0x3B5A0001
		opword 0x4800061C
		lwz r0, dat_80419808(r2)
		opword 0x38810030
		opword 0x38600002
		opword 0x90010030
		bl GXSetTevColor
		opword 0x7F23CB78
		opword 0x7F44D378
		opword 0x7F65DB78
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F23CB78
		opword 0x3880000F
		opword 0x38A00008
		opword 0x38C00004
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F23CB78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x5774103A
		opword 0x3A7C0098
		opword 0x7CD3A02E
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7EE3BB78
		opword 0x7F64DB78
		bl GXLoadTexObj
		opword 0x7EA3AB78
		opword 0x7FE4FB78
		opword 0x38A1017C
		bl PSMTXConcat
		opword 0x7C93A02E
		opword 0x3861017C
		opword 0x38A00000
		bl GXLoadTexMtxImm
		opword 0x3B390001
		opword 0x3B7B0001
		opword 0x3B5A0001
		opword 0x4800051C
		opword 0x3879FFFF
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000001
		bl GXSetTevColorOp
		opword 0x3879FFFF
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000001
		bl GXSetTevAlphaOp
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00003
		opword 0x38C00002
		opword 0x38E00003
		bl GXSetTevSwapModeTable
		opword 0x38600002
		opword 0x38800003
		opword 0x38A00001
		opword 0x38C00002
		opword 0x38E00003
		bl GXSetTevSwapModeTable
		opword 0x7F23CB78
		opword 0x7F44D378
		opword 0x7F65DB78
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F23CB78
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00008
		bl GXSetTevColorIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F23CB78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00001
		bl GXSetTevSwapMode
		opword 0x5774103A
		opword 0x3A7C0098
		opword 0x7CD3A02E
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		bl shadowGetRamp16TexObj
		opword 0x7F64DB78
		bl GXLoadTexObj
		opword 0x7EC3B378
		opword 0x7FE4FB78
		opword 0x38A1017C
		bl PSMTXConcat
		opword 0x7C93A02E
		opword 0x3861017C
		opword 0x38A00000
		bl GXLoadTexMtxImm
		opword 0x3A790001
		opword 0x3A9A0001
		opword 0x3B7B0001
		opword 0x38C000FF
		opword 0x7E639B78
		opword 0x7E84A378
		opword 0x7F65DB78
		bl GXSetTevOrder
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00008
		opword 0x38C0000C
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7E639B78
		opword 0x3880000A
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7E639B78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00002
		bl GXSetTevSwapMode
		opword 0x5776103A
		opword 0x3A7C0098
		opword 0x7CD3B02E
		opword 0x7E83A378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7EE3BB78
		opword 0x7F64DB78
		bl GXLoadTexObj
		opword 0x7EA3AB78
		opword 0x7FE4FB78
		opword 0x38A1017C
		bl PSMTXConcat
		opword 0x7C93B02E
		opword 0x3861017C
		opword 0x38A00000
		bl GXLoadTexMtxImm
		opword 0x3A790002
		opword 0x388000FF
		opword 0x7E639B78
		opword 0x38A000FF
		opword 0x38C00004
		opword 0x3B7B0001
		opword 0x3B5A0002
		bl GXSetTevOrder
		opword 0x7E639B78
		opword 0x3880000F
		opword 0x38A0000E
		opword 0x38C00000
		opword 0x38E00002
		bl GXSetTevColorIn
		opword 0x7E639B78
		opword 0x38800001
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x80010054
		opword 0x3881002C
		opword 0x38600001
		opword 0x9001002C
		bl GXSetTevKColor
		opword 0x7E639B78
		opword 0x3880000D
		bl GXSetTevKColorSel
		opword 0x7E639B78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00001
		bl GXSetTevAlphaIn
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x3B390003
		opword 0x48000230
		lwz r0, dat_8041980c(r2)
		opword 0x38810028
		opword 0x38600002
		opword 0x90010028
		bl GXSetTevColor
		opword 0x38600001
		opword 0x38800003
		opword 0x38A00001
		opword 0x38C00002
		opword 0x38E00003
		bl GXSetTevSwapModeTable
		opword 0x7F23CB78
		opword 0x7F44D378
		opword 0x7F65DB78
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F23CB78
		opword 0x3880000F
		opword 0x38A00008
		opword 0x38C00004
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F23CB78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00001
		bl GXSetTevSwapMode
		opword 0x5775103A
		opword 0x3A7C0098
		opword 0x7CD3A82E
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		bl shadowGetRamp16TexObj
		opword 0x7F64DB78
		bl GXLoadTexObj
		opword 0x7EC3B378
		opword 0x7FE4FB78
		opword 0x38A1017C
		bl PSMTXConcat
		opword 0x7C93A82E
		opword 0x3861017C
		opword 0x38A00000
		bl GXLoadTexMtxImm
		opword 0x3B390001
		opword 0x3B7B0001
		opword 0x3B5A0001
		opword 0x48000118
		lwz r0, dat_80419810(r2)
		opword 0x38810024
		opword 0x38600002
		opword 0x90010024
		bl GXSetTevColor
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00003
		opword 0x38C00002
		opword 0x38E00003
		bl GXSetTevSwapModeTable
		opword 0x7F23CB78
		opword 0x7F44D378
		opword 0x7F65DB78
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F23CB78
		opword 0x3880000F
		opword 0x38A00008
		opword 0x38C00004
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F23CB78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00001
		bl GXSetTevSwapMode
		opword 0x5776103A
		opword 0x3A7C0098
		opword 0x7CD3B02E
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7EE3BB78
		opword 0x7F64DB78
		bl GXLoadTexObj
		opword 0x7EA3AB78
		opword 0x7FE4FB78
		opword 0x38A1017C
		bl PSMTXConcat
		opword 0x7C93B02E
		opword 0x3861017C
		opword 0x38A00000
		bl GXLoadTexMtxImm
		opword 0x3B390001
		opword 0x3B7B0001
		opword 0x3B5A0001
		opword 0x57C0039D
		opword 0x41820140
		bl shadowGetProjShadowTexObj
		opword 0x28030000
		opword 0x41820134
		bl shadowGetProjShadowTexObj
		opword 0x7C741B78
		bl shadowGetProjShadowProjTexMtx
		opword 0x7C761B78
		bl shadowGetProjShadowColor
		opword 0x90610050
		bl shadowGetProjShadowConfig
		opword 0x7F23CB78
		opword 0x7F44D378
		opword 0x7F65DB78
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A0000E
		opword 0x38C00009
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F23CB78
		opword 0x38800007
		opword 0x38A00006
		opword 0x38C00004
		opword 0x38E00000
		bl GXSetTevAlphaIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x5775103A
		opword 0x3A7C0098
		opword 0x7CD3A82E
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7E83A378
		opword 0x7F64DB78
		bl GXLoadTexObj
		opword 0x7EC3B378
		opword 0x7FE4FB78
		opword 0x38A1014C
		bl PSMTXConcat
		opword 0x7C93A82E
		opword 0x3861014C
		opword 0x38A00000
		bl GXLoadTexMtxImm
		opword 0x80010050
		opword 0x38810020
		opword 0x38600001
		opword 0x90010020
		bl GXSetTevKColor
		opword 0x7F23CB78
		opword 0x3880000D
		bl GXSetTevKColorSel
		opword 0x7F23CB78
		opword 0x3880001D
		bl GXSetTevKAlphaSel
		opword 0x3B390001
		opword 0x3B7B0001
		opword 0x3B5A0001
		opword 0x57C0035B
		opword 0x4182060C
		bl shadowGetDepthShadowTexObj
		opword 0x28030000
		opword 0x41820600
		bl shadowGetDepthShadowTexObj
		opword 0x7C751B78
		bl shadowGetDepthShadowDepthMtx
		opword 0x7C741B78
		bl shadowGetDepthShadowProjTexMtx
		opword 0x7C761B78
		bl shadowGetDepthShadowColor
		opword 0x9061004C
		bl shadowGetDepthShadowConfig
		opword 0x8003003C
		opword 0x2C000003
		opword 0x418202DC
		opword 0x408005CC
		opword 0x2C000000
		opword 0x41820008
		opword 0x480005C0
		opword 0x3879FFFF
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000001
		bl GXSetTevColorOp
		opword 0x3879FFFF
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000001
		bl GXSetTevAlphaOp
		opword 0x7F23CB78
		opword 0x7F44D378
		opword 0x7F65DB78
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F23CB78
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00008
		bl GXSetTevColorIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F23CB78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x5777103A
		opword 0x3A7C0098
		opword 0x7CD3B82E
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		bl shadowGetRamp8TexObj
		opword 0x7F64DB78
		bl GXLoadTexObj
		opword 0x7E83A378
		opword 0x7FE4FB78
		opword 0x38A1011C
		bl PSMTXConcat
		opword 0x7C93B82E
		opword 0x3861011C
		opword 0x38A00000
		bl GXLoadTexMtxImm
		opword 0x3A790001
		opword 0x3A9A0001
		opword 0x3B7B0001
		opword 0x38C000FF
		opword 0x7E639B78
		opword 0x7E84A378
		opword 0x7F65DB78
		bl GXSetTevOrder
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00008
		opword 0x38C0000C
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7E639B78
		opword 0x38800008
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7E639B78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x5777103A
		opword 0x3A7C0098
		opword 0x7CD3B82E
		opword 0x7E83A378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7EA3AB78
		opword 0x7F64DB78
		bl GXLoadTexObj
		opword 0x7EC3B378
		opword 0x7FE4FB78
		opword 0x38A1011C
		bl PSMTXConcat
		opword 0x7C93B82E
		opword 0x3861011C
		opword 0x38A00000
		bl GXLoadTexMtxImm
		opword 0x3A790002
		opword 0x388000FF
		opword 0x7E639B78
		opword 0x38A000FF
		opword 0x38C00004
		opword 0x3B7B0001
		opword 0x3B5A0002
		bl GXSetTevOrder
		opword 0x7E639B78
		opword 0x38800002
		opword 0x38A0000E
		opword 0x38C00000
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7E639B78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00006
		bl GXSetTevAlphaIn
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x8001004C
		opword 0x3881001C
		opword 0x38600001
		opword 0x9001001C
		bl GXSetTevKColor
		opword 0x7E639B78
		opword 0x3880000D
		bl GXSetTevKColorSel
		opword 0x7E639B78
		opword 0x3880001D
		bl GXSetTevKAlphaSel
		opword 0x3B390003
		opword 0x480002F8
		opword 0x3879FFFF
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000001
		bl GXSetTevColorOp
		opword 0x3879FFFF
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000001
		bl GXSetTevAlphaOp
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00003
		opword 0x38C00002
		opword 0x38E00003
		bl GXSetTevSwapModeTable
		opword 0x38600002
		opword 0x38800003
		opword 0x38A00001
		opword 0x38C00002
		opword 0x38E00003
		bl GXSetTevSwapModeTable
		opword 0x7F23CB78
		opword 0x7F44D378
		opword 0x7F65DB78
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F23CB78
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00008
		bl GXSetTevColorIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F23CB78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00001
		bl GXSetTevSwapMode
		opword 0x5777103A
		opword 0x3A7C0098
		opword 0x7CD3B82E
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		bl shadowGetRamp16TexObj
		opword 0x7F64DB78
		bl GXLoadTexObj
		opword 0x7E83A378
		opword 0x7FE4FB78
		opword 0x38A1011C
		bl PSMTXConcat
		opword 0x7C93B82E
		opword 0x3861011C
		opword 0x38A00000
		bl GXLoadTexMtxImm
		opword 0x3A790001
		opword 0x3A9A0001
		opword 0x3B7B0001
		opword 0x38C000FF
		opword 0x7E639B78
		opword 0x7E84A378
		opword 0x7F65DB78
		bl GXSetTevOrder
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00008
		opword 0x38C0000C
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7E639B78
		opword 0x3880000A
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7E639B78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00002
		bl GXSetTevSwapMode
		opword 0x5777103A
		opword 0x3A7C0098
		opword 0x7CD3B82E
		opword 0x7E83A378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7EA3AB78
		opword 0x7F64DB78
		bl GXLoadTexObj
		opword 0x7EC3B378
		opword 0x7FE4FB78
		opword 0x38A1011C
		bl PSMTXConcat
		opword 0x7C93B82E
		opword 0x3861011C
		opword 0x38A00000
		bl GXLoadTexMtxImm
		opword 0x3A790002
		opword 0x388000FF
		opword 0x7E639B78
		opword 0x38A000FF
		opword 0x38C00004
		opword 0x3B7B0001
		opword 0x3B5A0002
		bl GXSetTevOrder
		opword 0x7E639B78
		opword 0x38800002
		opword 0x38A0000E
		opword 0x38C00000
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7E639B78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00006
		bl GXSetTevAlphaIn
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7E639B78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x8001004C
		opword 0x38810018
		opword 0x38600001
		opword 0x90010018
		bl GXSetTevKColor
		opword 0x7E639B78
		opword 0x3880000D
		bl GXSetTevKColorSel
		opword 0x7E639B78
		opword 0x3880001D
		bl GXSetTevKAlphaSel
		opword 0x3B390003
		opword 0x77C08010
		opword 0x418201A4
		opword 0x57C002D7
		opword 0x4182001C
		lwz r3, current_mp(r13)
		opword 0x8A63000C
		opword 0x8AA3000D
		opword 0x8AC3000E
		opword 0x8A83000F
		opword 0x48000070
		lwz r3, gp(r13)
		opword 0x3C004330
		opword 0x90010248
		opword 0x3A6000F0
		opword 0x8003001C
		opword 0x3AA000F0
		opword 0xC85C02C8
		opword 0x3AC00064
		opword 0x9001024C
		lfs f3, float_1p5708_8041988c(r2)
		opword 0xC8210248
		lfs f0, float_20_80419890(r2)
		opword 0xEC211028
		opword 0xEC230072
		opword 0xEC210024
		bl cos
		opword 0xFC600818
		lfs f1, float_1_80419860(r2)
		lfs f2, float_64_80419894(r2)
		lfs f0, float_0p5_80419854(r2)
		opword 0xEC211828
		opword 0xEC220072
		opword 0xEC01103A
		opword 0xFC00001E
		opword 0xD8010240
		opword 0x80010244
		opword 0x5414063E
		opword 0x7F23CB78
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E0000E
		bl GXSetTevColorIn
		opword 0x7F23CB78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		opword 0x7CB3A1D6
		opword 0x3C608081
		lwz r0, dat_80419814(r2)
		opword 0x38810014
		opword 0x39238081
		opword 0x90010010
		opword 0x7CD5A1D6
		opword 0x38600001
		opword 0x7D092896
		opword 0x7CE93096
		opword 0x7CA82A14
		opword 0x7CA83E70
		opword 0x7C16A1D6
		opword 0x7CC73214
		opword 0x7CC63E70
		opword 0x7CA90096
		opword 0x55090FFE
		opword 0x7CE84A14
		opword 0x98E10010
		opword 0x7C050214
		opword 0x54C50FFE
		opword 0x7CA62A14
		opword 0x7C003E70
		opword 0x98A10011
		opword 0x54050FFE
		opword 0x7C002A14
		opword 0x98010012
		opword 0x80010010
		opword 0x90010014
		bl GXSetTevKColor
		opword 0x7F23CB78
		opword 0x3880000D
		bl GXSetTevKColorSel
		opword 0x3B390001
		opword 0x57C00211
		opword 0x41820250
		opword 0x807C0120
		opword 0x3C004330
		opword 0x817C0124
		opword 0x815C0128
		opword 0x813C012C
		opword 0x811C0130
		opword 0x80FC0134
		opword 0x80DC0138
		opword 0x80BC013C
		opword 0x809C0140
		opword 0x90610074
		lwz r3, gp(r13)
		opword 0x91610078
		opword 0xC85C02C8
		opword 0x9141007C
		lfs f3, float_1p5708_8041988c(r2)
		opword 0x91210068
		lfs f0, float_30_80419898(r2)
		opword 0x9101006C
		opword 0x90E10070
		opword 0x90C1005C
		opword 0x90A10060
		opword 0x90810064
		opword 0x8063001C
		opword 0x90010248
		opword 0x9061024C
		opword 0xC8210248
		opword 0xEC211028
		opword 0xEC230072
		opword 0xEC210024
		bl cos
		opword 0xFC400818
		lfs f0, float_1_80419860(r2)
		lis r3, texture_0@ha
		lfs f3, float_127_80419880(r2)
		addi r4, r3, texture_0@l
		lfs f1, float_0p5_80419854(r2)
		opword 0xEC401028
		lfs f0, float_128_8041989c(r2)
		opword 0x3861009C
		opword 0x38A00004
		opword 0x38C00040
		opword 0x38E0000E
		opword 0xEC4300B2
		opword 0x39000000
		opword 0x39200001
		opword 0x39400000
		opword 0xEC02007A
		opword 0xFC00001E
		opword 0xD8010240
		opword 0x82810244
		bl GXInitTexObj
		opword 0x7F64DB78
		opword 0x3861009C
		bl GXLoadTexObj
		lwz r4, gp(r13)
		opword 0x3C004330
		lfs f5, float_0p5_80419854(r2)
		opword 0x386100EC
		opword 0x8084001C
		lfs f1, float_neg2_804198a0(r2)
		opword 0xFCC02890
		opword 0x90810254
		opword 0xFCE02890
		lfs f2, float_2_80419858(r2)
		opword 0xFC600890
		opword 0x90010250
		opword 0xC93C02C8
		opword 0xFC801090
		opword 0xC9010250
		lfs f0, float_50_804198a4(r2)
		opword 0xED084828
		opword 0xED080024
		bl C_MTXLightOrtho
		opword 0x386100BC
		opword 0x38810074
		opword 0x38A10068
		opword 0x38C1005C
		bl C_MTXLookAt
		opword 0x386100EC
		opword 0x388100BC
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x5775103A
		opword 0x3A7C0098
		opword 0x7C93A82E
		opword 0x386100EC
		opword 0x38A00000
		bl GXLoadTexMtxImm
		opword 0x7CD3A82E
		opword 0x7F43D378
		opword 0x38800000
		opword 0x38A00000
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x7F23CB78
		opword 0x7F44D378
		opword 0x7F65DB78
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x7F23CB78
		opword 0x38800008
		opword 0x38A00000
		opword 0x38C0000E
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x7F23CB78
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00000
		bl GXSetTevAlphaIn
		opword 0x7F23CB78
		opword 0x38800000
		opword 0x38A00000
		bl GXSetTevSwapMode
		lwz r0, dat_80419818(r2)
		opword 0x3881000C
		opword 0x38600001
		opword 0x90010008
		opword 0x9A810008
		opword 0x9A810009
		opword 0x9A81000A
		opword 0x80010008
		opword 0x9001000C
		bl GXSetTevKColor
		opword 0x7F23CB78
		opword 0x3880000D
		bl GXSetTevKColorSel
		opword 0x3B390001
		opword 0x3B7B0001
		opword 0x3B5A0001
		opword 0x57C0010F
		opword 0x41820064
		lwz r3, activeGroup(r13)
		opword 0x38C00000
		lwz r7, current_mp(r13)
		opword 0x540055BA
		opword 0x1C8302F4
		opword 0x93E10084
		lwz r5, mapWork(r13)
		opword 0x38610080
		opword 0x90E10080
		opword 0x38840110
		opword 0x93A10088
		opword 0x7C040214
		opword 0x9321008C
		opword 0x93610090
		opword 0x93410094
		opword 0x90C10098
		opword 0x7D85002E
		opword 0x280C0000
		opword 0x4182000C
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x8321008C
		opword 0x83410094
		opword 0x83010098
		opword 0x5743063E
		bl GXSetNumTexGens
		opword 0x5723063E
		bl GXSetNumTevStages
		opword 0x5703063E
		bl GXSetNumIndStages
#endif
	}
#ifdef NONMATCHING

	if (!(flags & 0x10000000)) {
		GXSetTevKColorSel(tevStage, GX_TEV_KCSEL_K0);
		GXSetTevKAlphaSel(tevStage, GX_TEV_KASEL_K0_A);
		GXSetTevOrder(tevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
		GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_CPREV, GX_CC_KONST, GX_CC_ZERO);
		GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_APREV, GX_CA_KONST, GX_CA_ZERO);
		GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
		tevStage++;
	}

	if ((flags & 4) && shadowGetCharShadowProjection() && shadowGetCharShadowTexObj()) {
		GXColor shColor = shadowGetCharShadowColor();
		Mtx shMtx;
		PSMTXConcat(shadowGetCharShadowProjTexMtx(), mtx, shMtx);
		GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
		GXLoadTexMtxImm(shMtx, texmtx_tbl[map], GX_MTX3x4);
		GXLoadTexObj(shadowGetCharShadowTexObj(), (GXTexMapID)map);
		GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
		GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_KONST, GX_CC_TEXC, GX_CC_ZERO);
		GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
		GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
		GXSetTevKColor(GX_KCOLOR1, shColor);
		GXSetTevKColorSel(tevStage, GX_TEV_KCSEL_K1);
		tevStage++;
		map = (GXTexMapID)(map + 1);
		coord = (GXTexCoordID)(coord + 1);
	}

	if (flags & 0x400) {
		Mtx pjMtx;
		GXSetTevColorOp((GXTevStageID)(tevStage - 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
		GXSetTevAlphaOp((GXTevStageID)tevStage - 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
		PSMTXConcat(projMtx, mtx, pjMtx);
		GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
		GXLoadTexMtxImm(pjMtx, texmtx_tbl[map], GX_MTX3x4);
		GXLoadTexObj(smartTexObj(&projTexObj, projTexImgRef), (GXTexMapID)map);
		GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
		GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
		GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C1);
		GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
		GXSetTevSwapMode(tevStage, GX_TEV_SWAP3, GX_TEV_SWAP3);
		GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_RED);
		GXSetTevColor(GX_TEVREG1, (GXColor){0, 0, 0, 0xFF});
		map = (GXTexMapID)(map + 1);
		coord = (GXTexCoordID)(coord + 1);
		GXSetTevOrder((GXTevStageID)(tevStage + 1), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
		GXSetTevColorOp((GXTevStageID)(tevStage + 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaOp((GXTevStageID)(tevStage + 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevColorIn((GXTevStageID)(tevStage + 1), GX_CC_C0, GX_CC_CPREV, GX_CC_APREV, GX_CC_ZERO);
		GXSetTevAlphaIn((GXTevStageID)(tevStage + 1), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
		GXSetTevSwapMode((GXTevStageID)(tevStage + 1), GX_TEV_SWAP0, GX_TEV_SWAP0);
		tevStage += 2;
	}

	if ((flags & 0x10000) && shadowGetDepthShadowTexObj()) {
		GXTexObj* depthTex = shadowGetDepthShadowTexObj();
		MtxPtr depthMtx = shadowGetDepthShadowDepthMtx();
		MtxPtr projTexMtx = shadowGetDepthShadowProjTexMtx();
		GXColor depthColor = shadowGetDepthShadowColor();
		Mtx dsMtx;

		switch ((s32)shadowGetDepthShadowConfig()->format) {
			case 0:
				GXSetTevColorOp((GXTevStageID)(tevStage - 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevAlphaOp((GXTevStageID)tevStage - 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(shadowGetRamp8TexObj(), (GXTexMapID)map);
				PSMTXConcat(depthMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				map = (GXTexMapID)(map + 1);
				GXSetTevOrder((GXTevStageID)(tevStage + 1), (GXTexCoordID)(coord + 1), (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn((GXTevStageID)(tevStage + 1), GX_CC_CPREV, GX_CC_TEXC, GX_CC_ONE, GX_CC_ZERO);
				GXSetTevColorOp((GXTevStageID)(tevStage + 1), GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
				GXSetTevAlphaIn((GXTevStageID)(tevStage + 1), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevAlphaOp((GXTevStageID)(tevStage + 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode((GXTevStageID)(tevStage + 1), GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTexCoordGen2((GXTexCoordID)(coord + 1), GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(depthTex, (GXTexMapID)map);
				PSMTXConcat(projTexMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				map = (GXTexMapID)(map + 1);
				coord = (GXTexCoordID)(coord + 2);
				GXSetTevOrder((GXTevStageID)(tevStage + 2), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
				GXSetTevColorIn((GXTevStageID)(tevStage + 2), GX_CC_ZERO, GX_CC_KONST, GX_CC_CPREV, GX_CC_C0);
				GXSetTevColorOp((GXTevStageID)(tevStage + 2), GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevKColor(GX_KCOLOR1, depthColor);
				GXSetTevKColorSel((GXTevStageID)(tevStage + 2), GX_TEV_KCSEL_K1);
				GXSetTevAlphaIn((GXTevStageID)(tevStage + 2), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
				GXSetTevAlphaOp((GXTevStageID)(tevStage + 2), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode((GXTevStageID)(tevStage + 2), GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage += 3;
				break;

			case 1:
				GXSetTevColor(GX_TEVREG1, (GXColor){0xFF, 0x00, 0x00, 0x00});
				GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_ZERO);
				GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
				GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(shadowGetRamp8TexObj(), (GXTexMapID)map);
				PSMTXConcat(depthMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				tevStage++;
				map = (GXTexMapID)(map + 1);
				coord = (GXTexCoordID)(coord + 1);
				break;

			case 2:
				GXSetTevColor(GX_TEVREG1, (GXColor){0xFF, 0x00, 0x00, 0x00});
				GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_ZERO);
				GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
				GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(depthTex, (GXTexMapID)map);
				PSMTXConcat(projTexMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				tevStage++;
				map = (GXTexMapID)(map + 1);
				coord = (GXTexCoordID)(coord + 1);
				break;

			case 3:
				GXSetTevColorOp((GXTevStageID)(tevStage - 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevAlphaOp((GXTevStageID)tevStage - 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_BLUE, GX_CH_ALPHA);
				GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_ALPHA, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
				GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP1);
				GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(shadowGetRamp16TexObj(), (GXTexMapID)map);
				PSMTXConcat(depthMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				map = (GXTexMapID)(map + 1);
				GXSetTevOrder((GXTevStageID)(tevStage + 1), (GXTexCoordID)(coord + 1), (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn((GXTevStageID)(tevStage + 1), GX_CC_CPREV, GX_CC_TEXC, GX_CC_ONE, GX_CC_ZERO);
				GXSetTevColorOp((GXTevStageID)(tevStage + 1), GX_TEV_COMP_GR16_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
				GXSetTevAlphaIn((GXTevStageID)(tevStage + 1), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevAlphaOp((GXTevStageID)(tevStage + 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode((GXTevStageID)(tevStage + 1), GX_TEV_SWAP0, GX_TEV_SWAP2);
				GXSetTexCoordGen2((GXTexCoordID)(coord + 1), GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(depthTex, (GXTexMapID)map);
				PSMTXConcat(projTexMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				map = (GXTexMapID)(map + 1);
				coord = (GXTexCoordID)(coord + 2);
				GXSetTevOrder((GXTevStageID)(tevStage + 2), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorIn((GXTevStageID)(tevStage + 2), GX_CC_ZERO, GX_CC_KONST, GX_CC_CPREV, GX_CC_C0);
				GXSetTevColorOp((GXTevStageID)(tevStage + 2), GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevKColor(GX_KCOLOR1, depthColor);
				GXSetTevKColorSel((GXTevStageID)(tevStage + 2), GX_TEV_KCSEL_K1);
				GXSetTevAlphaIn((GXTevStageID)(tevStage + 2), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
				GXSetTevAlphaOp((GXTevStageID)(tevStage + 2), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode((GXTevStageID)(tevStage + 2), GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage += 3;
				break;

			case 4:
				GXSetTevColor(GX_TEVREG1, (GXColor){0xFF, 0xFF, 0x00, 0x00});
				GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_ALPHA, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
				GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_ZERO);
				GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
				GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP1);
				GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(shadowGetRamp16TexObj(), (GXTexMapID)map);
				PSMTXConcat(depthMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				tevStage++;
				map = (GXTexMapID)(map + 1);
				coord = (GXTexCoordID)(coord + 1);
				break;

			case 5:
				GXSetTevColor(GX_TEVREG1, (GXColor){0xFF, 0xFF, 0x00, 0x00});
				GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_BLUE, GX_CH_ALPHA);
				GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_ZERO);
				GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
				GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP1);
				GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(depthTex, (GXTexMapID)map);
				PSMTXConcat(projTexMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				tevStage++;
				map = (GXTexMapID)(map + 1);
				coord = (GXTexCoordID)(coord + 1);
				break;
		}
	}

	if ((flags & 0x20000) && shadowGetProjShadowTexObj()) {
		GXTexObj* projTex = shadowGetProjShadowTexObj();
		MtxPtr projTexMtx = shadowGetProjShadowProjTexMtx();
		GXColor projColor = shadowGetProjShadowColor();
		Mtx psMtx;

		shadowGetProjShadowConfig();
		GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
		GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_KONST, GX_CC_TEXA, GX_CC_ZERO);
		GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_APREV);
		GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
		GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
		GXLoadTexObj(projTex, (GXTexMapID)map);
		PSMTXConcat(projTexMtx, mtx, psMtx);
		GXLoadTexMtxImm(psMtx, texmtx_tbl[map], GX_MTX3x4);
		GXSetTevKColor(GX_KCOLOR1, projColor);
		GXSetTevKColorSel(tevStage, GX_TEV_KCSEL_K1);
		GXSetTevKAlphaSel(tevStage, GX_TEV_KASEL_K1_A);
		tevStage++;
		map = (GXTexMapID)(map + 1);
		coord = (GXTexCoordID)(coord + 1);
	}

	if ((flags & 0x40000) && shadowGetDepthShadowTexObj()) {
		GXTexObj* depthTex = shadowGetDepthShadowTexObj();
		MtxPtr depthMtx = shadowGetDepthShadowDepthMtx();
		MtxPtr projTexMtx = shadowGetDepthShadowProjTexMtx();
		GXColor depthColor = shadowGetDepthShadowColor();
		Mtx dsMtx;

		switch ((s32)shadowGetDepthShadowConfig()->format) {
			case 0:
				GXSetTevColorOp((GXTevStageID)(tevStage - 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevAlphaOp((GXTevStageID)tevStage - 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(shadowGetRamp8TexObj(), (GXTexMapID)map);
				PSMTXConcat(depthMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				map = (GXTexMapID)(map + 1);
				GXSetTevOrder((GXTevStageID)(tevStage + 1), (GXTexCoordID)(coord + 1), (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn((GXTevStageID)(tevStage + 1), GX_CC_CPREV, GX_CC_TEXC, GX_CC_ONE, GX_CC_ZERO);
				GXSetTevColorOp((GXTevStageID)(tevStage + 1), GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
				GXSetTevAlphaIn((GXTevStageID)(tevStage + 1), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevAlphaOp((GXTevStageID)(tevStage + 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode((GXTevStageID)(tevStage + 1), GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTexCoordGen2((GXTexCoordID)(coord + 1), GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(depthTex, (GXTexMapID)map);
				PSMTXConcat(projTexMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				map = (GXTexMapID)(map + 1);
				coord = (GXTexCoordID)(coord + 2);
				GXSetTevOrder((GXTevStageID)(tevStage + 2), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorIn((GXTevStageID)(tevStage + 2), GX_CC_C0, GX_CC_KONST, GX_CC_CPREV, GX_CC_ZERO);
				GXSetTevColorOp((GXTevStageID)(tevStage + 2), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn((GXTevStageID)(tevStage + 2), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
				GXSetTevAlphaOp((GXTevStageID)(tevStage + 2), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode((GXTevStageID)(tevStage + 2), GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevKColor(GX_KCOLOR1, depthColor);
				GXSetTevKColorSel((GXTevStageID)(tevStage + 2), GX_TEV_KCSEL_K1);
				GXSetTevKAlphaSel((GXTevStageID)(tevStage + 2), GX_TEV_KASEL_K1_A);
				tevStage += 3;
				break;

			case 3:
				GXSetTevColorOp((GXTevStageID)(tevStage - 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevAlphaOp((GXTevStageID)tevStage - 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_BLUE, GX_CH_ALPHA);
				GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_ALPHA, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
				GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP1);
				GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(shadowGetRamp16TexObj(), (GXTexMapID)map);
				PSMTXConcat(depthMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				map = (GXTexMapID)(map + 1);
				GXSetTevOrder((GXTevStageID)(tevStage + 1), (GXTexCoordID)(coord + 1), (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn((GXTevStageID)(tevStage + 1), GX_CC_CPREV, GX_CC_TEXC, GX_CC_ONE, GX_CC_ZERO);
				GXSetTevColorOp((GXTevStageID)(tevStage + 1), GX_TEV_COMP_GR16_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
				GXSetTevAlphaIn((GXTevStageID)(tevStage + 1), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevAlphaOp((GXTevStageID)(tevStage + 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode((GXTevStageID)(tevStage + 1), GX_TEV_SWAP0, GX_TEV_SWAP2);
				GXSetTexCoordGen2((GXTexCoordID)(coord + 1), GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(depthTex, (GXTexMapID)map);
				PSMTXConcat(projTexMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				map = (GXTexMapID)(map + 1);
				coord = (GXTexCoordID)(coord + 2);
				GXSetTevOrder((GXTevStageID)(tevStage + 2), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorIn((GXTevStageID)(tevStage + 2), GX_CC_C0, GX_CC_KONST, GX_CC_CPREV, GX_CC_ZERO);
				GXSetTevColorOp((GXTevStageID)(tevStage + 2), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn((GXTevStageID)(tevStage + 2), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
				GXSetTevAlphaOp((GXTevStageID)(tevStage + 2), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode((GXTevStageID)(tevStage + 2), GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevKColor(GX_KCOLOR1, depthColor);
				GXSetTevKColorSel((GXTevStageID)(tevStage + 2), GX_TEV_KCSEL_K1);
				GXSetTevKAlphaSel((GXTevStageID)(tevStage + 2), GX_TEV_KASEL_K1_A);
				tevStage += 3;
				break;
		}
	}

	if (flags & 0x80100000) {
		s32 r, g, b, a;
		f32 pulse;

		if (flags & 0x100000) {
			r = current_mp->color.r;
			g = current_mp->color.g;
			b = current_mp->color.b;
			a = current_mp->color.a;
		}
		else {
			r = 0xF0;
			g = 0xF0;
			b = 0x64;
			pulse = cos((1.5707964f * gp->retraceCount) / 20.0f);
			a = (u8)(64.0f * (1.0f - pulse) / 2.0f + 64.0f);
		}
		GXSetTevOrder(tevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
		GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_ZERO, GX_CC_ZERO, GX_CC_KONST);
		GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
		GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
		GXSetTevKColor(GX_KCOLOR1, (GXColor){r * a / 255, g * a / 255, b * a / 255, 0xFF});
		GXSetTevKColorSel(tevStage, GX_TEV_KCSEL_K1);
		tevStage++;
	}

	if (flags & 0x800000) {
		Vec camPos = {0.0f, 0.0f, 1.0f};
		Vec camUp = {0.0f, 1.0f, 0.0f};
		Vec target = {0.0f, 0.0f, 0.0f};
		GXTexObj waveTex;
		Mtx texMtx;
		Mtx lookMtx;
		s32 level;
		f32 pulse;

		pulse = cos((1.5707964f * gp->retraceCount) / 30.0f);
		level = (127.0f * (1.0f - pulse)) / 2.0f + 128.0f;
		GXInitTexObj(&waveTex, texture_0, 4, 64, GX_TF_CMPR, GX_CLAMP, GX_REPEAT, GX_FALSE);
		GXLoadTexObj(&waveTex, (GXTexMapID)map);
		C_MTXLightOrtho(texMtx, -2.0f, 2.0f, -2.0f, 2.0f, 0.5f, 0.5f, 0.5f, gp->retraceCount / 50.0f);
		C_MTXLookAt(lookMtx, &camPos, &camUp, &target);
		PSMTXConcat(texMtx, lookMtx, texMtx);
		GXLoadTexMtxImm(texMtx, texmtx_tbl[map], GX_MTX3x4);
		GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
		GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
		GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevColorIn(tevStage, GX_CC_TEXC, GX_CC_CPREV, GX_CC_KONST, GX_CC_ZERO);
		GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
		GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
		GXSetTevKColor(GX_KCOLOR1, (GXColor){level, level, level, 0xFF});
		GXSetTevKColorSel(tevStage, GX_TEV_KCSEL_K1);
		tevStage++;
		map = (GXTexMapID)(map + 1);
		coord = (GXTexCoordID)(coord + 1);
	}

	if (flags & 0xF000000) {
		MapTevCallbackInfo info;
		MapTevCallback callback;
		MapTevCallbackInfo* ip = &info;

		*(MapObject**)info.field_0x0 = current_mp;
		info.mtx = mtx;
		*(s32*)info.field_0x8 = drawMode;
		info.tevStage = tevStage;
		info.texCoord = map;
		info.texMap = coord;
		info.indStage = 0;
		callback = ((MapTevCallback*)((u8*)&mapWork[activeGroup] + offsetof(MapEntry, tevCallbacks)))[(u32)(flags & 0xF000000) >> 24];
		if (callback) {
			callback(ip);
		}
		tevStage = info.tevStage;
		coord = info.texMap;
		indStages = info.indStage;
	}

	GXSetNumTexGens((u8)coord);
	GXSetNumTevStages((u8)tevStage);
	GXSetNumIndStages((u8)indStages);
#endif
}
#pragma pop

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void mapSetMaterialLastStageBlend(s32 flags, GXColor color1, GXColor color2) {
#ifdef NONMATCHING
	MapWork* wp = mapGetWork();
	GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};

	if (flags & 0x40) {
		color.r = color.r * color1.r / 255;
		color.g = color.g * color1.g / 255;
		color.b = color.b * color1.b / 255;
		color.a = color.a * color1.a / 255;
	}
	if (color2.r != 0xFF) {
		color.a = color.a * color2.r / 255;
	}
	if ((wp->entries[0].flags & 2) && !(flags & 0x800)) {
		color.r = color.r * wp->entries[0].blend.r / 255;
		color.g = color.g * wp->entries[0].blend.g / 255;
		color.b = color.b * wp->entries[0].blend.b / 255;
		color.a = color.a * wp->entries[0].blend.a / 255;
	}
	if ((wp->entries[0].flags & 4) && !(flags & 0x1000)) {
		color.r = color.r * wp->entries[0].blend2.r / 255;
		color.g = color.g * wp->entries[0].blend2.g / 255;
		color.b = color.b * wp->entries[0].blend2.b / 255;
		color.a = color.a * wp->entries[0].blend2.a / 255;
	}
	if ((wp->entries[0].flags & 8) && !(flags & 0x800)) {
		color.r = color.r * wp->entries[0].color.r / 255;
		color.g = color.g * wp->entries[0].color.g / 255;
		color.b = color.b * wp->entries[0].color.b / 255;
		color.a = color.a * wp->entries[0].color.a / 255;
	}
	GXSetTevKColor(GX_KCOLOR0, color);
}

void mapSetMaterialFog(void) {
	CameraEntry* camera = camGetCurPtr();
	MapWork* wp = mapGetWork();

	if (wp->entries[0].flags & 1) {
		GXSetFog((GXFogType)fog_type[wp->entries[0].fogType], wp->entries[0].fogStart, wp->entries[0].fogEnd,
				 camera->near, camera->far, wp->entries[0].fogColor);
	}
	else {
		GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x54600673
		opword 0x93E1001C
		lwz r7, activeGroup(r13)
		lwz r6, dat_8041981c(r2)
		opword 0x1C0702F4
		lwz r7, mapWork(r13)
		opword 0x90C1000C
		opword 0x7CC70214
		opword 0x4182009C
		opword 0x8901000C
		opword 0x3CE08081
		opword 0x88040000
		opword 0x3BE78081
		opword 0x8961000D
		opword 0x7D8801D6
		opword 0x89440001
		opword 0x89040002
		opword 0x88040003
		opword 0x88E1000F
		opword 0x8921000E
		opword 0x7C0701D6
		opword 0x7CFF6096
		opword 0x7C8B51D6
		opword 0x7CE76214
		opword 0x7CEA3E70
		opword 0x7D0941D6
		opword 0x554B0FFE
		opword 0x7D4A5A14
		opword 0x9941000C
		opword 0x7D3F2096
		opword 0x7CFF4096
		opword 0x7C892214
		opword 0x7C893E70
		opword 0x7CE74214
		opword 0x55280FFE
		opword 0x7C9F0096
		opword 0x7D294214
		opword 0x7CE73E70
		opword 0x9921000D
		opword 0x54E80FFE
		opword 0x7C040214
		opword 0x7C003E70
		opword 0x7CE74214
		opword 0x54040FFE
		opword 0x98E1000E
		opword 0x7C002214
		opword 0x9801000F
		opword 0x88A50000
		opword 0x280500FF
		opword 0x4182002C
		opword 0x8801000F
		opword 0x3C808081
		opword 0x38848081
		opword 0x7C0029D6
		opword 0x7C840096
		opword 0x7C040214
		opword 0x7C003E70
		opword 0x54040FFE
		opword 0x7C002214
		opword 0x9801000F
		opword 0xA0060004
		opword 0x540407BD
		opword 0x418200A4
		opword 0x54640529
		opword 0x4082009C
		opword 0x88E1000C
		opword 0x3C808081
		opword 0x88A60016
		opword 0x39848081
		opword 0x8941000D
		opword 0x7D6729D6
		opword 0x89260017
		opword 0x8901000E
		opword 0x88E60018
		opword 0x88A1000F
		opword 0x88860019
		opword 0x7CE839D6
		opword 0x7D0C5896
		opword 0x7D2A49D6
		opword 0x7D085A14
		opword 0x7D0A3E70
		opword 0x7C8521D6
		opword 0x554B0FFE
		opword 0x7D4A5A14
		opword 0x9941000C
		opword 0x7CAC4896
		opword 0x7D0C3896
		opword 0x7CA54A14
		opword 0x7CA93E70
		opword 0x7CE83A14
		opword 0x7CAC2096
		opword 0x55280FFE
		opword 0x7CE73E70
		opword 0x7D294214
		opword 0x54E80FFE
		opword 0x9921000D
		opword 0x7C852214
		opword 0x7CE74214
		opword 0x7C843E70
		opword 0x98E1000E
		opword 0x54850FFE
		opword 0x7C842A14
		opword 0x9881000F
		opword 0x5404077B
		opword 0x418200A4
		opword 0x546404E7
		opword 0x4082009C
		opword 0x88E1000C
		opword 0x3C808081
		opword 0x88A6001A
		opword 0x39848081
		opword 0x8941000D
		opword 0x7D6729D6
		opword 0x8926001B
		opword 0x8901000E
		opword 0x88E6001C
		opword 0x88A1000F
		opword 0x8886001D
		opword 0x7CE839D6
		opword 0x7D0C5896
		opword 0x7D2A49D6
		opword 0x7D085A14
		opword 0x7D0A3E70
		opword 0x7C8521D6
		opword 0x554B0FFE
		opword 0x7D4A5A14
		opword 0x9941000C
		opword 0x7CAC4896
		opword 0x7D0C3896
		opword 0x7CA54A14
		opword 0x7CA93E70
		opword 0x7CE83A14
		opword 0x7CAC2096
		opword 0x55280FFE
		opword 0x7CE73E70
		opword 0x7D294214
		opword 0x54E80FFE
		opword 0x9921000D
		opword 0x7C852214
		opword 0x7CE74214
		opword 0x7C843E70
		opword 0x98E1000E
		opword 0x54850FFE
		opword 0x7C842A14
		opword 0x9881000F
		opword 0x54000739
		opword 0x418200A4
		opword 0x54600529
		opword 0x4082009C
		opword 0x8881000C
		opword 0x3C608081
		opword 0x8806001E
		opword 0x39438081
		opword 0x8901000D
		opword 0x7D2401D6
		opword 0x88E6001F
		opword 0x88860020
		opword 0x88060021
		opword 0x88A1000E
		opword 0x8861000F
		opword 0x7C8521D6
		opword 0x7CAA4896
		opword 0x7CC839D6
		opword 0x7CA54A14
		opword 0x7CA73E70
		opword 0x7C0301D6
		opword 0x54E80FFE
		opword 0x7CE74214
		opword 0x98E1000C
		opword 0x7C6A3096
		opword 0x7CAA2096
		opword 0x7C633214
		opword 0x7C663E70
		opword 0x7C852214
		opword 0x7C6A0096
		opword 0x54C50FFE
		opword 0x7C843E70
		opword 0x7CC62A14
		opword 0x54850FFE
		opword 0x98C1000D
		opword 0x7C030214
		opword 0x7C842A14
		opword 0x7C003E70
		opword 0x9881000E
		opword 0x54030FFE
		opword 0x7C001A14
		opword 0x9801000F
		opword 0x8001000C
		opword 0x38810008
		opword 0x38600000
		opword 0x90010008
		bl GXSetTevKColor
		opword 0x80010024
		opword 0x83E1001C
		opword 0x7C0803A6
		opword 0x38210020
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
static inline void mapSetObjFog(MapObject* obj) {
	CameraEntry* camera = camGetCurPtr();
	MapWork* wp = mapGetWork();
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifdef NONMATCHING
	if ((wp->entries[0].flags & 1) && !(obj->flags & 0x80000)) {
		GXSetFog((GXFogType)fog_type[wp->entries[0].fogType], wp->entries[0].fogStart, wp->entries[0].fogEnd,
				 camera->near, camera->far, wp->entries[0].fogColor);
	}
	else {
		GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void mapSetMaterialFog(void) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		bl camGetCurPtr
		lwz r0, activeGroup(r13)
		opword 0x7C651B78
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7CC30214
		opword 0xA0060004
		opword 0x540007FF
		opword 0x41820038
		opword 0x80060034
		la r3, fog_type(r13)
		opword 0x3881000C
		opword 0x9001000C
		opword 0x80060028
		opword 0xC026002C
		opword 0x5400103A
		opword 0xC0460030
		opword 0x7C63002E
		opword 0xC0650030
		opword 0xC0850034
		bl GXSetFog
		opword 0x48000028
		lfs f1, float_0_80419850(r2)
		opword 0x38810008
		lwz r0, dat_80419820(r2)
		opword 0x38600000
		opword 0xFC400890
		opword 0xFC600890
		opword 0x90010008
		opword 0xFC800890
		bl GXSetFog
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifdef NONMATCHING

LightEntry* lightGetAmbient(void);

#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void mapSetTextureMatrix(MapMaterial* mat) {
#ifdef NONMATCHING
	s32 j;
	s32 k;
	s32 i;
	f32 rot, sx, sy, tx, ty;
	f32 cx, cy;
	Mtx mtx, tmpMtx, transMtx, rotMtx, scaleMtx;

	j = 0;
	k = 0;
	for (i = mat->samplerCount - 1; i >= 0; j++, k++, i--) {
		sx = mat->xforms[i].sx;
		rot = -mat->xforms[i].rot;
		sy = mat->xforms[i].sy;
		ty = -mat->xforms[i].ty;
		tx = mat->xforms[i].tx;
		if (1.0f != mat->xforms[i].sx || 1.0f != mat->xforms[i].sy || 0.0f != tx || 0.0f != ty || 0.0f != rot) {
			if (rot) {
				cx = 0.5f * mat->xforms[i].cx * mat->xforms[i].sx;
				cy = (1.0f - 0.5f * mat->xforms[i].cy) * mat->xforms[i].sy;
				MTXTrans(mtx, cx, cy, 0.0f);
				MTXRotRad(rotMtx, 'z', MTXDegToRad(rot));
				MTXTrans(tmpMtx, -cx, -cy, 0.0f);
				MTXConcat(mtx, rotMtx, rotMtx);
				MTXConcat(rotMtx, tmpMtx, rotMtx);
			}
			if (sx || sy) {
				MTXScale(scaleMtx, sx, sy, 1.0f);
			}
			if (tx || ty) {
				MTXTrans(transMtx, tx, ty, 0.0f);
			}
			if (rot) {
				if (sx || sy) {
					MTXConcat(rotMtx, scaleMtx, mtx);
					if (tx || ty) {
						MTXConcat(mtx, transMtx, mtx);
					}
				}
				else if (tx || ty) {
					MTXConcat(rotMtx, transMtx, mtx);
				}
				else {
					MTXCopy(rotMtx, mtx);
				}
			}
			else if (sx || sy) {
				if (tx || ty) {
					MTXConcat(scaleMtx, transMtx, mtx);
				}
				else {
					MTXCopy(scaleMtx, mtx);
				}
			}
			else if (tx || ty) {
				MTXCopy(transMtx, mtx);
			}
			GXLoadTexMtxImm(mtx, texmtx_tbl[i], GX_MTX2x4);
			GXSetTexCoordGen2((GXTexCoordID)j, GX_TG_MTX2x4, (GXTexGenSrc)(mat->samplerCount + 3 - k), texmtx_tbl[i], GX_FALSE, GX_PTIDENTITY);
		}
		else {
			GXSetTexCoordGen2((GXTexCoordID)j, GX_TG_MTX2x4, (GXTexGenSrc)(mat->samplerCount + 3 - k), GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
		}
#endif
#ifndef NONMATCHING
	char _af_pad[232];
	asm volatile {
		mr r26, r3
		lis r3, texmtx_tbl@ha
		opword 0x889A000B
		addi r0, r3, texmtx_tbl@l
		lfs f31, float_1_80419860(r2)
		opword 0x3BA00000
		opword 0x3B64FFFF
		opword 0x3B800000
		opword 0x1C9B001C
		opword 0x5763103A
		opword 0x7FFA2214
		opword 0x7FC01A14
		opword 0x48000284
		opword 0xC0BF0034
		opword 0xC03F003C
		opword 0xC0DF0038
		opword 0xFFA02890
		opword 0xC01F0030
		opword 0xFC1F2800
		opword 0xFF803090
		opword 0xC37F002C
		opword 0xFFC00850
		opword 0xFF400050
		opword 0x40820028
		opword 0xFC1F3000
		opword 0x40820020
		lfs f0, float_0_80419850(r2)
		opword 0xFC00D800
		opword 0x40820014
		opword 0xFC00D000
		opword 0x4082000C
		opword 0xFC00F000
		opword 0x418201FC
		lfs f3, float_0_80419850(r2)
		opword 0xFC1E1800
		opword 0x4182007C
		lfs f4, float_0p5_80419854(r2)
		la r3, _af_pad+192
		opword 0xC05F0040
		opword 0xC03F0044
		lfs f0, float_1_80419860(r2)
		opword 0xEC4400B2
		opword 0xEC04007C
		opword 0xEF220172
		fmuls f24, f0, f6
		opword 0xFC20C890
		opword 0xFC40C090
		bl PSMTXTrans
		lfs f0, float_deg2rad_80419868(r2)
		opword 0x38610038
		opword 0x3880007A
		opword 0xEC2007B2
		bl PSMTXRotRad
		opword 0xFC20C850
		lfs f3, float_0_80419850(r2)
		opword 0xFC40C050
		opword 0x38610098
		bl PSMTXTrans
		opword 0x38810038
		opword 0x386100C8
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38610038
		opword 0x38810098
		opword 0x7C651B78
		bl PSMTXConcat
		lfs f0, float_0_80419850(r2)
		opword 0xFC1D0000
		opword 0x4082000C
		opword 0xFC1C0000
		opword 0x41820018
		opword 0xFC20E890
		lfs f3, float_1_80419860(r2)
		opword 0xFC40E090
		opword 0x38610008
		bl PSMTXScale
		lfs f0, float_0_80419850(r2)
		opword 0xFC1B0000
		opword 0x4082000C
		opword 0xFC1A0000
		opword 0x41820018
		opword 0xFC20D890
		lfs f3, float_0_80419850(r2)
		opword 0xFC40D090
		opword 0x38610068
		bl PSMTXTrans
		lfs f0, float_0_80419850(r2)
		opword 0xFC1E0000
		opword 0x41820080
		opword 0xFC1D0000
		opword 0x4082000C
		opword 0xFC1C0000
		opword 0x4182003C
		opword 0x38610038
		opword 0x38810008
		opword 0x38A100C8
		bl PSMTXConcat
		lfs f0, float_0_80419850(r2)
		opword 0xFC1B0000
		opword 0x4082000C
		opword 0xFC1A0000
		opword 0x418200B0
		opword 0x386100C8
		opword 0x38810068
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x4800009C
		opword 0xFC1B0000
		opword 0x4082000C
		opword 0xFC1A0000
		opword 0x41820018
		opword 0x38610038
		opword 0x38810068
		opword 0x38A100C8
		bl PSMTXConcat
		opword 0x48000078
		opword 0x38610038
		opword 0x388100C8
		bl PSMTXCopy
		opword 0x48000068
		opword 0xFC1D0000
		opword 0x4082000C
		opword 0xFC1C0000
		opword 0x4182003C
		lfs f0, float_0_80419850(r2)
		opword 0xFC1B0000
		opword 0x4082000C
		opword 0xFC1A0000
		opword 0x41820018
		opword 0x38610008
		opword 0x38810068
		opword 0x38A100C8
		bl PSMTXConcat
		opword 0x48000030
		opword 0x38610008
		opword 0x388100C8
		bl PSMTXCopy
		opword 0x48000020
		opword 0xFC1B0000
		opword 0x4082000C
		opword 0xFC1A0000
		opword 0x41820010
		opword 0x38610068
		opword 0x388100C8
		bl PSMTXCopy
		opword 0x809E0000
		opword 0x386100C8
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x88BA000B
		opword 0x7FA3EB78
		opword 0x80DE0000
		opword 0x38800001
		opword 0x38050003
		opword 0x38E00000
		opword 0x7CBC0050
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x48000028
		opword 0x88BA000B
		opword 0x7FA3EB78
		opword 0x38800001
		opword 0x38C0003C
		opword 0x38050003
		opword 0x38E00000
		opword 0x7CBC0050
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x3BBD0001
		opword 0x3B9C0001
		opword 0x3BFFFFE4
		opword 0x3BDEFFFC
		opword 0x3B7BFFFF
		opword 0x2C1B0000
		opword 0x4080FD7C
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void mapSetMaterial(MapObject* obj, void* material) {
#ifdef NONMATCHING
	MapMaterial* mat = material;
	GXColor ambient;
	GXColor ambColor = {0x00, 0x00, 0x00, 0xFF};
	s32 count;
	s32 texIdx;
	u32 lightMask;
	s32 attnFn;
	s32 i;
	LightEntry* light;
	LightEntry** lp;
	MapWork* wp;
	MapMatSampler* sampler;
	MapTexTable* table;
	char* name;
	s32 k;
	TEXDescriptor* desc;
	GXBool mip;
	GXLightObj lightObj;
	Mtx rotX, rotY, rotZ;
	LightEntry* lights[8];
	GXTexObj texObj;
	Vec pos;
#endif
#ifndef NONMATCHING
	char _af_pad[348];
	asm volatile {
		lwz r0, dat_80419828(r2)
		lis r5, vec3_802c16d8@ha
		opword 0x7C9F2378
		opword 0x7C7E1B78
		stw r0, _af_pad+20(r1)
		addi r28, r5, vec3_802c16d8@l
		opword 0x3881005C
		opword 0x3B200000
		opword 0x3AE00002
		bl mapSetLight
		opword 0x7C7D1B78
		opword 0x3B61005C
		opword 0x3B5C0100
		opword 0x3B000000
		opword 0x3AC00000
		opword 0x4800030C
		opword 0x809C0144
		opword 0x807C0148
		opword 0x801C014C
		opword 0x90810024
		lwz r19, 0x0(r27)
		opword 0x90610028
		opword 0x9001002C
		opword 0xA0730000
		opword 0x546004E7
		opword 0x4182007C
		bl camGetCurPtr
		opword 0x3863011C
		opword 0x38930024
		opword 0x38A10030
		bl PSMTXMultVec
		opword 0xC0210030
		opword 0x3861010C
		opword 0xC0410034
		opword 0xC0610038
		bl GXInitLightPos
		opword 0x80BB0000
		opword 0x3861010C
		opword 0x38810018
		opword 0x80050048
		opword 0x90010018
		bl GXInitLightColor
		lfs f2, float_0_80419850(r2)
		opword 0x3861010C
		opword 0x809B0000
		opword 0xFC601090
		opword 0xC0240050
		opword 0xC0840054
		opword 0xC0A40058
		opword 0xC0C4005C
		bl GXInitLightAttn
		opword 0x809A0000
		opword 0x3861010C
		bl GXLoadLightObjImm
		opword 0x3AE00001
		opword 0x48000258
		opword 0x546004A5
		opword 0x4182011C
		lfs f1, float_deg2rad_80419868(r2)
		opword 0x386100DC
		opword 0xC0130030
		opword 0x38800078
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x80BB0000
		opword 0x386100AC
		lfs f1, float_deg2rad_80419868(r2)
		opword 0x38800079
		opword 0xC0050034
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x80BB0000
		opword 0x3861007C
		lfs f1, float_deg2rad_80419868(r2)
		opword 0x3880007A
		opword 0xC0050038
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x388100AC
		opword 0x3861007C
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x388100DC
		opword 0x386100AC
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810024
		opword 0x386100DC
		opword 0x7C852378
		bl PSMTXMultVec
		opword 0x38610024
		lfs f1, float_neg1p0486E06_80419870(r2)
		opword 0x7C641B78
		bl PSVECScale
		opword 0x807B0000
		opword 0x38810024
		opword 0x38A10030
		opword 0x38630024
		bl PSVECAdd
		bl camGetCurPtr
		opword 0x38810030
		opword 0x3863011C
		opword 0x7C852378
		bl PSMTXMultVec
		opword 0xC0210030
		opword 0x3861010C
		opword 0xC0410034
		opword 0xC0610038
		bl GXInitLightPos
		opword 0x80BB0000
		opword 0x3861010C
		opword 0x38810014
		opword 0x80050048
		opword 0x90010014
		bl GXInitLightColor
		lfs f2, float_0_80419850(r2)
		opword 0x3861010C
		opword 0x809B0000
		opword 0xFC601090
		lfs f6, float_1_80419860(r2)
		opword 0xFC801090
		opword 0xC0240050
		opword 0xFCA01090
		bl GXInitLightAttn
		opword 0x809A0000
		opword 0x3861010C
		bl GXLoadLightObjImm
		opword 0x48000138
		opword 0x54600463
		opword 0x41820130
		bl camGetCurPtr
		opword 0x3863011C
		opword 0x38930024
		opword 0x38A10030
		bl PSMTXMultVec
		opword 0x80BB0000
		opword 0x386100DC
		lfs f1, float_deg2rad_80419868(r2)
		opword 0x38800078
		opword 0xC0050030
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x80BB0000
		opword 0x386100AC
		lfs f1, float_deg2rad_80419868(r2)
		opword 0x38800079
		opword 0xC0050034
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x80BB0000
		opword 0x3861007C
		lfs f1, float_deg2rad_80419868(r2)
		opword 0x3880007A
		opword 0xC0050038
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x388100AC
		opword 0x3861007C
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x388100DC
		opword 0x386100AC
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38810024
		opword 0x386100DC
		opword 0x7C852378
		bl PSMTXMultVec
		bl camGetCurPtr
		opword 0x38810024
		opword 0x3863011C
		opword 0x7C852378
		bl PSMTXMultVecSR
		opword 0xC0210030
		opword 0x3861010C
		opword 0xC0410034
		opword 0xC0610038
		bl GXInitLightPos
		opword 0xC0210024
		opword 0x3861010C
		opword 0xC0410028
		opword 0xC061002C
		bl GXInitLightDir
		opword 0x80BB0000
		opword 0x3861010C
		lfs f0, float_0p5_80419854(r2)
		opword 0x38800004
		opword 0xC025004C
		opword 0xEC210032
		bl GXInitLightSpot
		lfs f1, float_1000_80419874(r2)
		opword 0x3861010C
		lfs f2, float_0p5_80419854(r2)
		opword 0x38800000
		bl GXInitLightDistAttn
		opword 0x80BB0000
		opword 0x3861010C
		opword 0x38810010
		opword 0x80050048
		opword 0x90010010
		bl GXInitLightColor
		opword 0x809A0000
		opword 0x3861010C
		bl GXLoadLightObjImm
		opword 0x3AE00001
		opword 0x801A0000
		opword 0x3B7B0004
		opword 0x3B5A0004
		opword 0x3AD60001
		opword 0x7F180378
		opword 0x7C16E800
		opword 0x4180FCF4
		bl lightGetAmbient
		opword 0x28030000
		opword 0x41820010
		opword 0x80030048
		opword 0x9001014C
		opword 0x4800000C
		opword 0x8001001C
		opword 0x9001014C
		opword 0x8001014C
		opword 0x38600001
		opword 0x90010020
		bl GXSetNumChans
		opword 0x80010020
		opword 0x3881000C
		opword 0x38600004
		opword 0x9001000C
		bl GXSetChanAmbColor
		opword 0x801F0004
		opword 0x38810008
		opword 0x38600004
		opword 0x90010008
		bl GXSetChanMatColor
		opword 0x881F0008
		opword 0x2C000001
		opword 0x41820060
		opword 0x408000A4
		opword 0x2C000000
		opword 0x40800008
		opword 0x48000098
		opword 0x7C1D00D0
		opword 0x7F07C378
		opword 0x7C00E878
		opword 0x7EE9BB78
		opword 0x54040FFE
		opword 0x38600000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x39000002
		bl GXSetChanCtrl
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0x39000000
		opword 0x39200002
		bl GXSetChanCtrl
		opword 0x4800004C
		opword 0x7C1D00D0
		opword 0x7F07C378
		opword 0x7C00E878
		opword 0x7EE9BB78
		opword 0x54040FFE
		opword 0x38600000
		opword 0x38A00000
		opword 0x38C00001
		opword 0x39000002
		bl GXSetChanCtrl
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00001
		opword 0x38E00000
		opword 0x39000000
		opword 0x39200002
		bl GXSetChanCtrl
		opword 0x887F000B
		opword 0x3B1C00EC
		lfd f31, 0x2c8(r28)
		opword 0x3EE04330
		opword 0x3B63FFFF
		opword 0x5760103A
		opword 0x7F5F0214
		opword 0x4800013C
		lwz r3, activeGroup(r13)
		opword 0x3B800000
		opword 0xA81E00DE
		opword 0x1CA302F4
		opword 0x82DA000C
		lwz r6, mapWork(r13)
		opword 0x80960000
		opword 0x1C600178
		opword 0x7FA62A14
		opword 0x82840000
		opword 0x38030094
		opword 0x7EBD002E
		opword 0x7EB3AB78
		opword 0x48000024
		opword 0x80730004
		opword 0x7E84A378
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x4800001C
		opword 0x3A730004
		opword 0x3B9C0001
		opword 0x80150000
		opword 0x7C1C0000
		opword 0x4180FFD8
		opword 0x3B80FFFF
		opword 0xA81E00DE
		opword 0x7F84E378
		opword 0x1C600178
		opword 0x38030084
		opword 0x7C7D002E
		bl TEXGet
		opword 0x7C7C1B78
		opword 0x80E30000
		opword 0x88670021
		opword 0x88070022
		opword 0x7C030040
		opword 0x4082000C
		opword 0x39400000
		opword 0x48000008
		opword 0x39400001
		opword 0x88960008
		opword 0x3861003C
		opword 0x88160009
		opword 0x5488103A
		opword 0x80870008
		opword 0x5400103A
		opword 0xA0A70002
		opword 0xA0C70000
		opword 0x80E70004
		opword 0x7D18402E
		opword 0x7D38002E
		bl GXInitTexObj
		opword 0x813C0000
		opword 0x3861003C
		opword 0x92E10150
		opword 0x38800001
		opword 0x88E90021
		opword 0x38A00001
		opword 0x88090022
		opword 0x38C00000
		opword 0x90E10154
		opword 0x39000000
		opword 0xC069001C
		opword 0xC8010150
		opword 0x9001015C
		opword 0xEC20F828
		opword 0x88E90020
		opword 0x92E10158
		opword 0xC8010158
		opword 0xEC40F828
		bl GXInitTexObjLOD
		opword 0x7F24CB78
		opword 0x3861003C
		bl GXLoadTexObj
		opword 0x3B390001
		opword 0x3B5AFFFC
		opword 0x3B7BFFFF
		opword 0x2C1B0000
		opword 0x4080FEC4
		opword 0x807F0110
		opword 0x28030000
		opword 0x4182000C
		opword 0x88830000
		opword 0x48000008
		opword 0x38800000
		opword 0x887F000B
		opword 0x38DE001C
		opword 0x80BE0000
		bl mapSetMaterialTev
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
	texIdx = 0;
	attnFn = GX_AF_NONE;
	count = mapSetLight(obj, lights);
	lightMask = 0;
	for (i = 0; i < count; i++) {
		Vec dir = {0.0f, 0.0f, -1.0f};
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifdef NONMATCHING
		light = lights[i];
		if (light->flags & LIGHT_POINT) {
			MTXMultVec(camGetCurPtr()->view, &light->position, &pos);
			GXInitLightPos(&lightObj, pos.x, pos.y, pos.z);
			GXInitLightColor(&lightObj, lights[i]->color);
			GXInitLightAttn(&lightObj, lights[i]->attenAngle, 0.0f, 0.0f, lights[i]->attenDistCoef.x, lights[i]->attenDistCoef.y, lights[i]->attenDistCoef.z);
			GXLoadLightObjImm(&lightObj, lightid_tbl[i]);
			attnFn = GX_AF_SPOT;
		}
		else if (light->flags & LIGHT_SPOT) {
			MTXRotRad(rotX, 'x', MTXDegToRad(light->rotation.x));
			MTXRotRad(rotY, 'y', MTXDegToRad(lights[i]->rotation.y));
			MTXRotRad(rotZ, 'z', MTXDegToRad(lights[i]->rotation.z));
			MTXConcat(rotZ, rotY, rotY);
			MTXConcat(rotY, rotX, rotX);
			MTXMultVec(rotX, &dir, &dir);
			VECScale(&dir, &dir, -1048576.0f);
			VECAdd(&lights[i]->position, &dir, &pos);
			MTXMultVec(camGetCurPtr()->view, &pos, &pos);
			GXInitLightPos(&lightObj, pos.x, pos.y, pos.z);
			GXInitLightColor(&lightObj, lights[i]->color);
			GXInitLightAttn(&lightObj, lights[i]->attenAngle, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
			GXLoadLightObjImm(&lightObj, lightid_tbl[i]);
		}
		else if (light->flags & LIGHT_DIRECTIONAL) {
			MTXMultVec(camGetCurPtr()->view, &light->position, &pos);
			MTXRotRad(rotX, 'x', MTXDegToRad(lights[i]->rotation.x));
			MTXRotRad(rotY, 'y', MTXDegToRad(lights[i]->rotation.y));
			MTXRotRad(rotZ, 'z', MTXDegToRad(lights[i]->rotation.z));
			MTXConcat(rotZ, rotY, rotY);
			MTXConcat(rotY, rotX, rotX);
			MTXMultVec(rotX, &dir, &dir);
			MTXMultVecSR(camGetCurPtr()->view, &dir, &dir);
			GXInitLightPos(&lightObj, pos.x, pos.y, pos.z);
			GXInitLightDir(&lightObj, dir.x, dir.y, dir.z);
			GXInitLightSpot(&lightObj, lights[i]->spotAngle / 2, GX_SP_SHARP);
			GXInitLightDistAttn(&lightObj, 1000.0f, 0.5f, GX_DA_OFF);
			GXInitLightColor(&lightObj, lights[i]->color);
			GXLoadLightObjImm(&lightObj, lightid_tbl[i]);
			attnFn = GX_AF_SPOT;
		}
		lightMask |= lightid_tbl[i];
	}

	light = lightGetAmbient();
	if (light) {
		ambient = light->color;
	}
	else {
		ambient = ambColor;
	}
	GXSetNumChans(1);
	GXSetChanAmbColor(GX_COLOR0A0, ambient);
	GXSetChanMatColor(GX_COLOR0A0, mat->color);
	switch (mat->lightMode) {
		case 0:
			GXSetChanCtrl(GX_COLOR0, count > 0, GX_SRC_REG, GX_SRC_REG, lightMask, GX_DF_CLAMP, (GXAttnFn)attnFn);
			GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
			break;
		case 1:
			GXSetChanCtrl(GX_COLOR0, count > 0, GX_SRC_REG, GX_SRC_VTX, lightMask, GX_DF_CLAMP, (GXAttnFn)attnFn);
			GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
			break;
	}

	for (i = mat->samplerCount - 1; i >= 0; i--) {
		sampler = mat->samplers[i];
		wp = mapGetWork();
		k = mapSearchTexName(MAPENT_FIELD(&wp->entries[obj->groupIndex], MapTexTable*, 0x94), sampler->tex->name);
		desc = TEXGet(wp->entries[obj->groupIndex].tpl, k);
		if (desc->textureHeader->minLOD == desc->textureHeader->maxLOD) {
			mip = GX_FALSE;
		} else {
			mip = GX_TRUE;
		}
		GXInitTexObj(&texObj, desc->textureHeader->data, desc->textureHeader->width, desc->textureHeader->height, (GXTexFmt)desc->textureHeader->format,
					 (GXTexWrapMode)texwrap_tbl[sampler->wrapS], (GXTexWrapMode)texwrap_tbl[sampler->wrapT],
					 mip);
		GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, desc->textureHeader->minLOD, desc->textureHeader->maxLOD, desc->textureHeader->LODBias, GX_FALSE, desc->textureHeader->edgeLODEnable, GX_ANISO_1);
		GXLoadTexObj(&texObj, (GXTexMapID)texIdx);
		texIdx++;
	}
	mapSetMaterialTev(mat->samplerCount, mat->tevMode ? *mat->tevMode : 0, obj->flags, obj->modelWorldMtx);
}

#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapSetPaperAmbColor(GXColor* color) {
	paper_ambient = *color;
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void mapResetPaperAmbColor(void) {
#ifdef NONMATCHING
	paper_ambient = (GXColor){0x70, 0x70, 0x70, 0xFF};
}

static inline void mapResetPaperCraftAmbColor(void) {
	paperCraft_ambient = (GXColor){0x70, 0x70, 0x70, 0xFF};
}

void mapSetMaterialLight(s32 flags, Vec position) {
	GXColor matColor = {0xFF, 0xFF, 0xFF, 0xFF};
	GXColor ambColor = {0x00, 0x00, 0x00, 0xFF};
	s32 count;
	u32 lightMask;
	u32 paper;
	s32 attnFn;
	s32 i;
	u32 paperCraft;
	LightEntry* light;
	GXLightObj lightObj;
	Mtx rotX, rotY, rotZ;
	LightEntry* lights[8];
	GXColor ambient;
	Vec pos;

	count = 0;
	attnFn = GX_AF_NONE;
	paper = flags & 1;
	if (paper) {
		lights[0] = lightGetPaper();
		count = 1;
	}
	paperCraft = flags & 8;
	if (paperCraft) {
		lights[count] = lightGetPaperCraft();
		count++;
	}
	if (flags & 0x10) {
		lights[count] = lightGetPaper();
		count++;
	}
	if ((flags & 2) && lightCheckCharaLight() && count < 8) {
		count += lightGetNearObj(&position, &lights[count], 8 - count, LIGHT_CHARA);
	}
	if (flags & 0x19) {
		if (count == 1) {
			if (paper) {
				ambColor = paper_ambient;
			}
			else if (paperCraft) {
				ambColor = paperCraft_ambient;
			}
			else {
				ambColor = (GXColor){0x00, 0x00, 0x00, 0xFF};
			}
		}
		else {
			count = lightGetNearObj(&position, lights, 8, LIGHT_CHARA);
		}
	}

	lightMask = 0;
	for (i = 0; i < count; i++) {
		Vec dir = {0.0f, 0.0f, -1.0f};

		light = lights[i];
		if (light->flags & LIGHT_POINT) {
			MTXMultVec(camGetCurPtr()->view, &light->position, &pos);
			GXInitLightPos(&lightObj, pos.x, pos.y, pos.z);
			GXInitLightColor(&lightObj, lights[i]->color);
			if (lights[i]->flags & LIGHT_NO_DIST_ATTEN) {
				GXInitLightAttn(&lightObj, lights[i]->attenAngle, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
			}
			else {
				GXInitLightAttn(&lightObj, lights[i]->attenAngle, 0.0f, 0.0f, lights[i]->attenDistCoef.x, lights[i]->attenDistCoef.y, lights[i]->attenDistCoef.z);
				attnFn = GX_AF_SPOT;
			}
			GXLoadLightObjImm(&lightObj, lightid_tbl[i]);
		}
		else if (light->flags & LIGHT_SPOT) {
			MTXRotRad(rotX, 'x', MTXDegToRad(light->rotation.x));
			MTXRotRad(rotY, 'y', MTXDegToRad(lights[i]->rotation.y));
			MTXRotRad(rotZ, 'z', MTXDegToRad(lights[i]->rotation.z));
			MTXConcat(rotZ, rotY, rotY);
			MTXConcat(rotY, rotX, rotX);
			MTXMultVec(rotX, &dir, &dir);
			VECScale(&dir, &dir, -1048576.0f);
			VECAdd(&lights[i]->position, &dir, &pos);
			MTXMultVec(camGetCurPtr()->view, &pos, &pos);
			GXInitLightPos(&lightObj, pos.x, pos.y, pos.z);
			GXInitLightColor(&lightObj, lights[i]->color);
			GXLoadLightObjImm(&lightObj, lightid_tbl[i]);
		}
		else if (light->flags & LIGHT_DIRECTIONAL) {
			MTXMultVec(camGetCurPtr()->view, &light->position, &pos);
			MTXRotRad(rotX, 'x', MTXDegToRad(lights[i]->rotation.x));
			MTXRotRad(rotY, 'y', MTXDegToRad(lights[i]->rotation.y));
			MTXRotRad(rotZ, 'z', MTXDegToRad(lights[i]->rotation.z));
			MTXConcat(rotZ, rotY, rotY);
			MTXConcat(rotY, rotX, rotX);
			MTXMultVec(rotX, &dir, &dir);
			MTXMultVecSR(camGetCurPtr()->view, &dir, &dir);
			GXInitLightPos(&lightObj, pos.x, pos.y, pos.z);
			GXInitLightDir(&lightObj, dir.x, dir.y, dir.z);
			{
				f32 ang = lights[i]->spotAngle;
				ang *= 0.5f;
				GXInitLightSpot(&lightObj, ang, GX_SP_SHARP);
			}
			GXInitLightDistAttn(&lightObj, 1000.0f, 0.5f, GX_DA_OFF);
			GXInitLightColor(&lightObj, lights[i]->color);
			GXLoadLightObjImm(&lightObj, lightid_tbl[i]);
			attnFn = GX_AF_SPOT;
		}
		lightMask |= lightid_tbl[i];
	}

	light = lightGetCharaAmbient();
	if (light) {
		ambient = light->color;
	}
	else {
		ambient = ambColor;
	}
	GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, matColor);
	GXSetNumChans(1);
	GXSetChanAmbColor(GX_COLOR0A0, ambient);
	if (flags & 4) {
		GXSetChanMatColor(GX_COLOR0A0, matColor);
		GXSetChanCtrl(GX_COLOR0, count > 0, GX_SRC_REG, GX_SRC_REG, lightMask, GX_DF_CLAMP, (GXAttnFn)attnFn);
		GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
	}
	else {
		GXSetChanCtrl(GX_COLOR0, count > 0, GX_SRC_REG, GX_SRC_VTX, lightMask, GX_DF_CLAMP, (GXAttnFn)attnFn);
		GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
#endif
#ifndef NONMATCHING
	asm volatile {
		lwz r0, dat_8041982c(r2)
		stw r0, paper_ambient(r13)
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
typedef struct MapVcdTable {
	void* positions;          // 0x0
	void* normals;            // 0x4
	u8 field_0x8[0xC - 0x8];  // 0x8
	void* colors[2];          // 0xC
	s32 texCount;             // 0x14
	void* texCoords[8];       // 0x18
} MapVcdTable;
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifdef NONMATCHING
typedef struct MapVtxFmtInfo {
	u8 field_0x0[0x44 - 0x0]; // 0x0
	s32 posFrac;              // 0x44
	s32 texFrac[8];           // 0x48
} MapVtxFmtInfo;
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#undef lightGetNearObj
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void mapSetMaterialLight(s32 flags, Vec position) {
	char _af_pad[300];
	asm volatile {
		opword 0x7C781B78
		opword 0x571907FF
		opword 0x7C972378
		opword 0x3B800000
		opword 0x3B400002
		lwz r3, dat_80419834(r2)
		lwz r0, dat_80419838(r2)
		stw r3, _af_pad+32(r1)
		opword 0x90010024
		opword 0x41820010
		bl lightGetPaper
		opword 0x90610044
		opword 0x3B800001
		opword 0x571B0739
		opword 0x41820018
		bl lightGetPaperCraft
		opword 0x5780103A
		opword 0x38810044
		opword 0x7C64012E
		opword 0x3B9C0001
		opword 0x570006F7
		opword 0x41820018
		bl lightGetPaper
		opword 0x5780103A
		opword 0x38810044
		opword 0x7C64012E
		opword 0x3B9C0001
		opword 0x570007BD
		opword 0x41820038
		bl lightCheckCharaLight
		opword 0x2C030000
		opword 0x4182002C
		opword 0x2C1C0008
		opword 0x40800024
		opword 0x5780103A
		opword 0x38810044
		opword 0x7EE3BB78
		opword 0x20BC0008
		opword 0x7C840214
		opword 0x38C00080
		bl lightGetNearObj
		opword 0x7F9C1A14
		opword 0x73000019
		opword 0x41820058
		opword 0x2C1C0001
		opword 0x40820038
		opword 0x28190000
		opword 0x41820010
		lwz r0, paper_ambient(r13)
		opword 0x90010024
		opword 0x4800003C
		opword 0x281B0000
		opword 0x41820010
		lwz r0, paperCraft_ambient(r13)
		opword 0x90010024
		opword 0x48000028
		lwz r0, dat_8041983c(r2)
		opword 0x90010024
		opword 0x4800001C
		opword 0x7EE3BB78
		opword 0x38810044
		opword 0x38A00008
		opword 0x38C00080
		bl lightGetNearObj
		opword 0x7C7C1B78
		lis r4, lightid_tbl@ha
		lis r3, vec3_802c1828@ha
		addi r29, r4, lightid_tbl@l
		opword 0x3BC10044
		addi r31, r3, vec3_802c1828@l
		opword 0x3B600000
		opword 0x3B200000
		opword 0x48000318
		opword 0x809F0000
		opword 0x807F0004
		opword 0x801F0008
		opword 0x9081002C
		lwz r23, 0x0(r30)
		opword 0x90610030
		opword 0x90010034
		opword 0xA0770000
		opword 0x546004E7
		opword 0x418200AC
		bl camGetCurPtr
		opword 0x3863011C
		opword 0x38970024
		opword 0x38A10038
		bl PSMTXMultVec
		opword 0xC0210038
		opword 0x386100F4
		opword 0xC041003C
		opword 0xC0610040
		bl GXInitLightPos
		opword 0x80BE0000
		opword 0x386100F4
		opword 0x3881001C
		opword 0x80050048
		opword 0x9001001C
		bl GXInitLightColor
		opword 0x809E0000
		opword 0xA0040000
		opword 0x54000673
		opword 0x41820028
		lfs f2, float_0_80419850(r2)
		opword 0x386100F4
		opword 0xC0240050
		opword 0xFC601090
		lfs f4, float_1_80419860(r2)
		opword 0xFCA01090
		opword 0xFCC01090
		bl GXInitLightAttn
		opword 0x48000028
		lfs f2, float_0_80419850(r2)
		opword 0x386100F4
		opword 0xC0240050
		opword 0xFC601090
		opword 0xC0840054
		opword 0xC0A40058
		opword 0xC0C4005C
		bl GXInitLightAttn
		opword 0x3B400001
		opword 0x809D0000
		opword 0x386100F4
		bl GXLoadLightObjImm
		opword 0x48000234
		opword 0x546004A5
		opword 0x418200F8
		lfs f1, float_deg2rad_80419868(r2)
		opword 0x386100C4
		opword 0xC0170030
		opword 0x38800078
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x80BE0000
		opword 0x38610094
		lfs f1, float_deg2rad_80419868(r2)
		opword 0x38800079
		opword 0xC0050034
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x80BE0000
		opword 0x38610064
		lfs f1, float_deg2rad_80419868(r2)
		opword 0x3880007A
		opword 0xC0050038
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x38810094
		opword 0x38610064
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x388100C4
		opword 0x38610094
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x3881002C
		opword 0x386100C4
		opword 0x7C852378
		bl PSMTXMultVec
		opword 0x3861002C
		lfs f1, float_neg1p0486E06_80419870(r2)
		opword 0x7C641B78
		bl PSVECScale
		opword 0x807E0000
		opword 0x3881002C
		opword 0x38A10038
		opword 0x38630024
		bl PSVECAdd
		bl camGetCurPtr
		opword 0x38810038
		opword 0x3863011C
		opword 0x7C852378
		bl PSMTXMultVec
		opword 0xC0210038
		opword 0x386100F4
		opword 0xC041003C
		opword 0xC0610040
		bl GXInitLightPos
		opword 0x80BE0000
		opword 0x386100F4
		opword 0x38810018
		opword 0x80050048
		opword 0x90010018
		bl GXInitLightColor
		opword 0x809D0000
		opword 0x386100F4
		bl GXLoadLightObjImm
		opword 0x48000138
		opword 0x54600463
		opword 0x41820130
		bl camGetCurPtr
		opword 0x3863011C
		opword 0x38970024
		opword 0x38A10038
		bl PSMTXMultVec
		opword 0x80BE0000
		opword 0x386100C4
		lfs f1, float_deg2rad_80419868(r2)
		opword 0x38800078
		opword 0xC0050030
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x80BE0000
		opword 0x38610094
		lfs f1, float_deg2rad_80419868(r2)
		opword 0x38800079
		opword 0xC0050034
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x80BE0000
		opword 0x38610064
		lfs f1, float_deg2rad_80419868(r2)
		opword 0x3880007A
		opword 0xC0050038
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x38810094
		opword 0x38610064
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x388100C4
		opword 0x38610094
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x3881002C
		opword 0x386100C4
		opword 0x7C852378
		bl PSMTXMultVec
		bl camGetCurPtr
		opword 0x3881002C
		opword 0x3863011C
		opword 0x7C852378
		bl PSMTXMultVecSR
		opword 0xC0210038
		opword 0x386100F4
		opword 0xC041003C
		opword 0xC0610040
		bl GXInitLightPos
		opword 0xC021002C
		opword 0x386100F4
		opword 0xC0410030
		opword 0xC0610034
		bl GXInitLightDir
		opword 0x80BE0000
		opword 0x386100F4
		lfs f0, float_0p5_80419854(r2)
		opword 0x38800004
		opword 0xC025004C
		opword 0xEC210032
		bl GXInitLightSpot
		lfs f1, float_1000_80419874(r2)
		opword 0x386100F4
		lfs f2, float_0p5_80419854(r2)
		opword 0x38800000
		bl GXInitLightDistAttn
		opword 0x80BE0000
		opword 0x386100F4
		opword 0x38810014
		opword 0x80050048
		opword 0x90010014
		bl GXInitLightColor
		opword 0x809D0000
		opword 0x386100F4
		bl GXLoadLightObjImm
		opword 0x3B400001
		opword 0x801D0000
		opword 0x3BDE0004
		opword 0x3BBD0004
		opword 0x3B390001
		opword 0x7F7B0378
		opword 0x7C19E000
		opword 0x4180FCE8
		bl lightGetCharaAmbient
		opword 0x28030000
		opword 0x41820010
		opword 0x80030048
		opword 0x90010134
		opword 0x4800000C
		opword 0x80010024
		opword 0x90010134
		lfs f1, float_0_80419850(r2)
		opword 0x38810010
		opword 0x80A10134
		opword 0x38600000
		opword 0x80010028
		opword 0xFC400890
		opword 0xFC600890
		opword 0x90A10020
		opword 0xFC800890
		opword 0x90010010
		bl GXSetFog
		opword 0x38600001
		bl GXSetNumChans
		opword 0x80010020
		opword 0x3881000C
		opword 0x38600004
		opword 0x9001000C
		bl GXSetChanAmbColor
		opword 0x5700077B
		opword 0x41820064
		opword 0x80010028
		opword 0x38810008
		opword 0x38600004
		opword 0x90010008
		bl GXSetChanMatColor
		opword 0x7C1C00D0
		opword 0x7F67DB78
		opword 0x7C00E078
		opword 0x7F49D378
		opword 0x54040FFE
		opword 0x38600000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x39000002
		bl GXSetChanCtrl
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00000
		opword 0x39000002
		opword 0x39200002
		bl GXSetChanCtrl
		opword 0x4800004C
		opword 0x7C1C00D0
		opword 0x7F67DB78
		opword 0x7C00E078
		opword 0x7F49D378
		opword 0x54040FFE
		opword 0x38600000
		opword 0x38A00000
		opword 0x38C00001
		opword 0x39000002
		bl GXSetChanCtrl
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00001
		opword 0x38E00000
		opword 0x39000002
		opword 0x39200002
		bl GXSetChanCtrl
	}
}
#pragma pop
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif

#ifdef NONMATCHING
#define MAP_VTXFMT(entry) ((MapVtxFmtInfo*)(entry)->vcdTable)
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifdef NONMATCHING
typedef struct MapVtxRec {
	s16 pos;     // 0x0
	s16 nrm;     // 0x2
	s16 clr;     // 0x4
	s16 unk6;    // 0x6
	s16 tex[8];  // 0x8
} MapVtxRec;

typedef struct MapRawDL {
	s32 count;        // 0x0

	MapVtxRec vtx[];  // 0x4
} MapRawDL;
const GXVtxAttrFmtList attr_fmt[12] = {
	{GX_VA_POS, GX_POS_XYZ, GX_F32, 0},
	{GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0},
	{GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0},
	{GX_VA_TEX0, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX1, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX2, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX3, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX4, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX5, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX6, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX7, GX_TEX_ST, GX_F32, 0},
	{GX_VA_NULL, GX_POS_XY, GX_U8, 0},
};


#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#define mapGetWork mapGetWork__af_inl
#endif
void mapSetPolygon(MapObject* obj, MapFileMesh* mesh) {
	MapWork* wp;
	void* pos;
	void* nrm;
	s32 texCount;
	MapVcdTable* vcd;

	int i;
	int j;
	int k;
	MapRawDL* dl;
	MapVtxRec* v;

	wp = mapGetWork();
	vcd = (MapVcdTable*)mesh->vcdTableOffset;
	pos = (u8*)vcd->positions + 4;
	nrm = (u8*)vcd->normals + 4;
	texCount = vcd->texCount;

	GXSetCullMode(culling[obj->joints->drawMode->cullMode]);
	if (!(wp->entries[obj->groupIndex].flags & 0x8000)) {
		GXClearVtxDesc();
		GXSetVtxAttrFmtv(GX_VTXFMT0, attr_fmt);
		GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
		GXSetArray(GX_VA_POS, pos, 12);
		GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
		GXSetArray(GX_VA_NRM, nrm, 12);
		GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
		GXSetArray(GX_VA_CLR0, (u8*)((MapVcdTable*)mesh->vcdTableOffset)->colors[0] + 4, 4);
		for (i = 0; i < texCount; i++) {
			GXSetVtxDesc(GX_VA_TEX0 + i, GX_INDEX16);
			GXSetArray(GX_VA_TEX0 + i, (u8*)((MapVcdTable*)mesh->vcdTableOffset)->texCoords[i] + 4, 8);
		}
		for (i = 0; i < mesh->displayListCount; i++) {
			dl = (MapRawDL*)mesh->displayLists.normalLists[i];
			GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, (u16)dl->count);
			for (j = 0; j < dl->count; j++) {
				v = &dl->vtx[j];
				GXPosition1x16(v->pos);
				GXNormal1x16(v->nrm);
				GXColor1x16(v->clr);
				for (k = 0; k < texCount; k++) {

					GXTexCoord1x16(v->tex[k] != -1 ? (u16)v->tex[k] : 0);
				}
			}
		}
	}
	else {
		u32 mask = mesh->elementMask;
		GXClearVtxDesc();
		GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, (u8)((MapVtxFmtInfo*)wp->entries[obj->groupIndex].vcdTable)->posFrac);
		GXSetArray(GX_VA_POS, pos, 6);
		GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S8, 6);
		GXSetArray(GX_VA_NRM, nrm, 3);
		for (i = 0; i < 2; i++) {
			if (!(mask & (1 << (i + 2)))) {
				break;
			}
			GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
			GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
			GXSetArray(GX_VA_CLR0, (u8*)((MapVcdTable*)mesh->vcdTableOffset)->colors[i] + 4, 4);
		}
		for (i = 0; i < 8; i++) {
			if (!(mask & (1 << (i + 4)))) {

				break;
			}
			GXSetVtxDesc(GX_VA_TEX0 + i, GX_INDEX16);
			GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0 + i, GX_TEX_ST, GX_S16, (u8)MAP_VTXFMT(&wp->entries[obj->groupIndex])->texFrac[i]);
			GXSetArray(GX_VA_TEX0 + i, (u8*)((MapVcdTable*)mesh->vcdTableOffset)->texCoords[i] + 4, 4);
		}
		for (i = 0; i < mesh->displayListCount; i++) {
			GXCallDisplayList((void*)mesh->displayLists.packedLists[i].offset, *(u32*)&mesh->displayLists.packedLists[i].vertexCount);
		}
	}
}

#ifndef NONMATCHING
#undef mapGetWork

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#define mapGetWork mapGetWork__af_inl
#endif
void mapSetPolygonVtxDesc(MapObject* obj, MapFileMesh* mesh) {

	MapWork* wp;
	u32 mask;
	MapVcdTable* vcd;
	void* pos;
	void* nrm;
	int i;

	wp = mapGetWork();

	vcd = (MapVcdTable*)mesh->vcdTableOffset;
	mask = mesh->elementMask;
	pos = (u8*)vcd->positions + 4;
	nrm = (u8*)vcd->normals + 4;
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, (u8)((MapVtxFmtInfo*)wp->entries[obj->groupIndex].vcdTable)->posFrac);
	GXSetArray(GX_VA_POS, pos, 6);
	GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S8, 6);
	GXSetArray(GX_VA_NRM, nrm, 3);
	for (i = 0; i < 2; i++) {
		if (!(mask & (1 << (i + 2)))) {
			break;
		}
		GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
		GXSetArray(GX_VA_CLR0, (u8*)((MapVcdTable*)mesh->vcdTableOffset)->colors[i] + 4, 4);
	}
	for (i = 0; i < 8; i++) {
		if (!(mask & (1 << (i + 4)))) {
			break;
		}
		GXSetVtxDesc(GX_VA_TEX0 + i, GX_INDEX16);
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0 + i, GX_TEX_ST, GX_S16, (u8)MAP_VTXFMT(&wp->entries[obj->groupIndex])->texFrac[i]);
		GXSetArray(GX_VA_TEX0 + i, (u8*)((MapVcdTable*)mesh->vcdTableOffset)->texCoords[i] + 4, 4);
	}
}

#ifndef NONMATCHING
#undef mapGetWork

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
MapFileJoint* mapSearchDmdJointSub(MapFileJoint* joint, const char* name) {
	MapFileJoint* found;

	if (!strcmp(joint->name, name)) {
		return joint;
	}
	if (joint->child) {
		found = mapSearchDmdJointSub(joint->child, name);
		if (found) {
			return found;
		}
	}
	if (joint->next) {
		found = mapSearchDmdJointSub(joint->next, name);
		if (found) {
			return found;
		}
	}
	return NULL;
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
MapFileJoint* mapSearchDmdJointSub2(MapFileJoint* joint, const char* name, const char* prefix) {
#ifdef NONMATCHING
	MapFileJoint* found;
	char path[256];
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421F8E0
		opword 0x7C0802A6
		opword 0x90010724
		opword 0xBF61070C
		opword 0x7C7D1B78
		opword 0x7CBE2B78
		opword 0x7C9F2378
		opword 0x38610608
		opword 0x7FC4F378
		bl strcpy
		opword 0x809D0000
		opword 0x38610608
		bl strcat
		opword 0x7FE4FB78
		opword 0x38610608
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x7FA3EB78
		opword 0x48000390
		opword 0x801D000C
		opword 0x28000000
		opword 0x418201C4
		opword 0x38610608
		la r4, str_8041986C(r2)
		bl strcat
		opword 0x837D000C
		opword 0x38610508
		opword 0x38810608
		bl strcpy
		opword 0x809B0000
		opword 0x38610508
		bl strcat
		opword 0x7FE4FB78
		opword 0x38610508
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x48000174
		opword 0x801B000C
		opword 0x28000000
		opword 0x418200B8
		opword 0x38610508
		la r4, str_8041986C(r2)
		bl strcat
		opword 0x839B000C
		opword 0x38610308
		opword 0x38810508
		bl strcpy
		opword 0x809C0000
		opword 0x38610308
		bl strcat
		opword 0x7FE4FB78
		opword 0x38610308
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x48000068
		opword 0x801C000C
		opword 0x28000000
		opword 0x41820030
		opword 0x38610308
		la r4, str_8041986C(r2)
		bl strcat
		opword 0x807C000C
		opword 0x7FE4FB78
		opword 0x38A10308
		bl mapSearchDmdJointSub2
		opword 0x28030000
		opword 0x4182000C
		opword 0x7C7C1B78
		opword 0x48000030
		opword 0x807C0010
		opword 0x28030000
		opword 0x41820020
		opword 0x7FE4FB78
		opword 0x38A10508
		bl mapSearchDmdJointSub2
		opword 0x28030000
		opword 0x4182000C
		opword 0x7C7C1B78
		opword 0x48000008
		opword 0x3B800000
		opword 0x281C0000
		opword 0x4182000C
		opword 0x7F9BE378
		opword 0x480000B4
		opword 0x837B0010
		opword 0x281B0000
		opword 0x418200A4
		opword 0x38610208
		opword 0x38810608
		bl strcpy
		opword 0x809B0000
		opword 0x38610208
		bl strcat
		opword 0x7FE4FB78
		opword 0x38610208
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x48000068
		opword 0x801B000C
		opword 0x28000000
		opword 0x41820030
		opword 0x38610208
		la r4, str_8041986C(r2)
		bl strcat
		opword 0x807B000C
		opword 0x7FE4FB78
		opword 0x38A10208
		bl mapSearchDmdJointSub2
		opword 0x28030000
		opword 0x4182000C
		opword 0x7C7B1B78
		opword 0x48000030
		opword 0x807B0010
		opword 0x28030000
		opword 0x41820020
		opword 0x7FE4FB78
		opword 0x38A10608
		bl mapSearchDmdJointSub2
		opword 0x28030000
		opword 0x4182000C
		opword 0x7C7B1B78
		opword 0x48000008
		opword 0x3B600000
		opword 0x281B0000
		opword 0x41820008
		opword 0x48000008
		opword 0x3B600000
		opword 0x281B0000
		opword 0x4182000C
		opword 0x7F63DB78
		opword 0x480001C4
		opword 0x837D0010
		opword 0x281B0000
		opword 0x418201B4
		opword 0x7FC4F378
		opword 0x38610408
		bl strcpy
		opword 0x809B0000
		opword 0x38610408
		bl strcat
		opword 0x7FE4FB78
		opword 0x38610408
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x48000174
		opword 0x801B000C
		opword 0x28000000
		opword 0x418200B8
		opword 0x38610408
		la r4, str_8041986C(r2)
		bl strcat
		opword 0x839B000C
		opword 0x38610108
		opword 0x38810408
		bl strcpy
		opword 0x809C0000
		opword 0x38610108
		bl strcat
		opword 0x7FE4FB78
		opword 0x38610108
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x48000068
		opword 0x801C000C
		opword 0x28000000
		opword 0x41820030
		opword 0x38610108
		la r4, str_8041986C(r2)
		bl strcat
		opword 0x807C000C
		opword 0x7FE4FB78
		opword 0x38A10108
		bl mapSearchDmdJointSub2
		opword 0x28030000
		opword 0x4182000C
		opword 0x7C7C1B78
		opword 0x48000030
		opword 0x807C0010
		opword 0x28030000
		opword 0x41820020
		opword 0x7FE4FB78
		opword 0x38A10408
		bl mapSearchDmdJointSub2
		opword 0x28030000
		opword 0x4182000C
		opword 0x7C7C1B78
		opword 0x48000008
		opword 0x3B800000
		opword 0x281C0000
		opword 0x4182000C
		opword 0x7F9BE378
		opword 0x480000B4
		opword 0x837B0010
		opword 0x281B0000
		opword 0x418200A4
		opword 0x7FC4F378
		opword 0x38610008
		bl strcpy
		opword 0x809B0000
		opword 0x38610008
		bl strcat
		opword 0x7FE4FB78
		opword 0x38610008
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x48000068
		opword 0x801B000C
		opword 0x28000000
		opword 0x41820030
		opword 0x38610008
		la r4, str_8041986C(r2)
		bl strcat
		opword 0x807B000C
		opword 0x7FE4FB78
		opword 0x38A10008
		bl mapSearchDmdJointSub2
		opword 0x28030000
		opword 0x4182000C
		opword 0x7C7B1B78
		opword 0x48000030
		opword 0x807B0010
		opword 0x28030000
		opword 0x41820020
		opword 0x7FE4FB78
		opword 0x7FC5F378
		bl mapSearchDmdJointSub2
		opword 0x28030000
		opword 0x4182000C
		opword 0x7C7B1B78
		opword 0x48000008
		opword 0x3B600000
		opword 0x281B0000
		opword 0x41820008
		opword 0x48000008
		opword 0x3B600000
		opword 0x281B0000
		opword 0x4182000C
		opword 0x7F63DB78
		opword 0x48000008
		opword 0x38600000
		opword 0xBB61070C
		opword 0x80010724
		opword 0x7C0803A6
		opword 0x38210720
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
	strcpy(path, prefix);
	strcat(path, joint->name);
	if (!strcmp(path, name)) {
		return joint;
#endif
#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
MapFileJoint* mapSearchDmdJoint(MapFileJoint* joint, const char* name) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		opword 0x88040000
		opword 0x2C00007C
		opword 0x4182000C
		bl mapSearchDmdJointSub
		opword 0x4800000C
		la r5, str_8041986C(r2)
		bl mapSearchDmdJointSub2
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
#endif
	}
#ifdef NONMATCHING
	if (joint->child) {
		strcat(path, "|");
		found = mapSearchDmdJointSub2(joint->child, name, path);
		if (found) {
			return found;
		}
	}
	if (joint->next) {
		found = mapSearchDmdJointSub2(joint->next, name, prefix);
		if (1) {
			if (found) {
				return found;
			}
		}
	}
	return NULL;
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
MapFileJoint* mapSearchDmdJoint(MapFileJoint* joint, const char* name) {
	if ((s32)name[0] != '|') {
		return mapSearchDmdJointSub(joint, name);
	}
	return mapSearchDmdJointSub2(joint, name, "|");
}
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#define mapGetWork mapGetWork__af_inl
#endif
MapObject* mapGetMapObj(const char *name) { // 1:1
    MapWork *wp;
    MapEntry* entry;
    int j;
    int i;
    MapObject *object;

    wp = mapGetWork();
    if (!name) {
        return 0;
    }
    for (i = 0; i < wp->entries[0].count; i++) {
        entry = &wp->entries[i];
        object = entry->objects;
        for (j = 0; j < entry->numJoints; j++, object++) {
            if (!strcmp(object->joints->name, name)) {
                return object;
            }
        }
    }
    return 0;
}

#ifndef NONMATCHING
#undef mapGetWork

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapObjFlagOn(const char* name, u32 flags) {
	MapObject* obj = mapGetMapObj(name);

	if (!obj) {
		error_data[error_count].field_0x20 = 0;
		strncpy(error_data[error_count].field_0x0, name, sizeof(error_data[0].field_0x0) - 1);
		error_flag = TRUE;
		error_count++;
		error_count %= 32;
		return;
	}
	if (!(flags & 0x100) || obj->unk114) {
		obj->flags |= flags;
	}
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapObjFlagOff(const char* name, u32 flags) {
	MapObject* obj = mapGetMapObj(name);

	if (!obj) {
		error_data[error_count].field_0x20 = 0;
		strncpy(error_data[error_count].field_0x0, name, sizeof(error_data[0].field_0x0) - 1);
		error_flag = TRUE;
		error_count++;
		error_count %= 32;
		return;
	}
	obj->flags &= ~flags;
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapFlgOn(MapObject* obj, u32 flags, BOOL doNext) {
	if (!(flags & 0x100) || obj->unk114) {
		obj->flags |= flags;
	}
	if (obj->child) {
		mapFlgOn(obj->child, flags, TRUE);
	}
	if (doNext && obj->next) {
		mapFlgOn(obj->next, flags, TRUE);
	}
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapFlgOff(MapObject* obj, u32 flags, BOOL doNext) {
	obj->flags &= ~flags;
	if (obj->child) {
		mapFlgOff(obj->child, flags, TRUE);
	}
	if (doNext && obj->next) {
		mapFlgOff(obj->next, flags, TRUE);
	}
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapGrpFlagOn(const char* name, u32 flags) {
	MapObject* obj = mapGetMapObj(name);

	if (!obj) {
		error_data[error_count].field_0x20 = 0;
		strncpy(error_data[error_count].field_0x0, name, sizeof(error_data[0].field_0x0) - 1);
		error_flag = TRUE;
		error_count++;
		error_count %= 32;
		return;
	}
	mapFlgOn(obj, flags, FALSE);
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapGrpFlagOff(const char* name, u32 flags) {
	MapObject* obj = mapGetMapObj(name);

	if (!obj) {
		error_data[error_count].field_0x20 = 0;
		strncpy(error_data[error_count].field_0x0, name, sizeof(error_data[0].field_0x0) - 1);
		error_flag = TRUE;
		error_count++;
		error_count %= 32;
		return;
	}
	mapFlgOff(obj, flags, FALSE);
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void _setOffScrnId(MapObject* obj, s32 id, BOOL doNext) {
	obj->offscreenId = id;
	if (id != -1) {
		obj->flags |= 0x80;
	}
	else {
		obj->flags &= ~0x80;
	}
	if (obj->child) {
		_setOffScrnId(obj->child, id, TRUE);
	}
	if (doNext && obj->next) {
		_setOffScrnId(obj->next, id, TRUE);
	}
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapObjSetOffScreen(const char* name, const char* offscreen) {
	MapObject* obj;
	MapObject* object;
	int i;
	int j;
	MapWork* wp;
	MapEntry* entry;

	wp = &mapWork[activeGroup];
	if (!name) {
		obj = NULL;
		goto done;
	}
	entry = &wp->entries[0];
	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		object = entry->objects;
		for (j = 0; j < entry->numJoints; j++, object++) {
			if (!strcmp(object->joints->name, name)) {
				obj = object;
				goto done;
			}
		}
	}
	obj = NULL;
done:

	obj->offscreenId = offscreenNameToId(offscreen);
	obj->flags |= 0x80;
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapGrpSetOffScreen(const char* name, const char* offscreen) {
	MapObject* obj = mapGetMapObj(name);
	s32 id = offscreenNameToId(offscreen);

	_setOffScrnId(obj, id, FALSE);
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapObjClearOffScreen(const char* name) {
	MapObject* obj = mapGetMapObj(name);

	obj->offscreenId = -1;
	obj->flags &= ~0x80;
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapGrpClearOffScreen(const char* name) {
	MapObject* obj = mapGetMapObj(name);

	_setOffScrnId(obj, -1, FALSE);
}

#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void mapObjRotate(const char* name, f32 x, f32 y, f32 z) {
#ifdef NONMATCHING
	MapObject* obj = mapGetMapObj(name);
	Mtx rotX, rotY, rotZ;

	if (obj) {
		if (!(obj->flags & 0x200)) {
			MTXIdentity(obj->unkAC);
		}
		MTXRotRad(rotX, 'x', MTXDegToRad(x));
		MTXRotRad(rotY, 'y', MTXDegToRad(y));
		MTXRotRad(rotZ, 'z', MTXDegToRad(z));
		if (1) {
			MTXConcat(obj->unkAC, rotZ, obj->unkAC);
			MTXConcat(obj->unkAC, rotY, obj->unkAC);
			MTXConcat(obj->unkAC, rotX, obj->unkAC);
		}
		obj->flags |= 0x200000;
		obj->flags |= 0x200;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FF20
		opword 0x7C0802A6
		opword 0x900100E4
		opword 0xDBE100D0
		opword 0xF3E100D8
		opword 0xDBC100C0
		opword 0xF3C100C8
		opword 0xDBA100B0
		opword 0xF3A100B8
		opword 0xBF410098
		lwz r0, activeGroup(r13)
		opword 0x7C7A1B79
		opword 0xFFA00890
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0xFFC01090
		opword 0xFFE01890
		opword 0x7F830214
		opword 0x4082000C
		opword 0x3BE00000
		opword 0x48000064
		opword 0x7F9BE378
		opword 0x3BC00000
		opword 0x48000048
		opword 0x83FB0154
		opword 0x3BA00000
		opword 0x48000028
		opword 0x807F0008
		opword 0x7F44D378
		opword 0x80630000
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x48000030
		opword 0x3BBD0001
		opword 0x3BFF0134
		opword 0x801B0150
		opword 0x7C1D0000
		opword 0x4180FFD4
		opword 0x3B7B0178
		opword 0x3BDE0001
		opword 0x801C0000
		opword 0x7C1E0000
		opword 0x4180FFB4
		opword 0x3BE00000
		opword 0x281F0000
		opword 0x4182009C
		opword 0x801F0000
		opword 0x540005AD
		opword 0x4082000C
		opword 0x387F00AC
		bl PSMTXIdentity
		lfs f0, float_deg2rad_80419868(r2)
		opword 0x38610068
		opword 0x38800078
		opword 0xEC200772
		bl PSMTXRotRad
		lfs f0, float_deg2rad_80419868(r2)
		opword 0x38610038
		opword 0x38800079
		opword 0xEC2007B2
		bl PSMTXRotRad
		lfs f0, float_deg2rad_80419868(r2)
		opword 0x38610008
		opword 0x3880007A
		opword 0xEC2007F2
		bl PSMTXRotRad
		opword 0x387F00AC
		opword 0x38810008
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x387F00AC
		opword 0x38810038
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x387F00AC
		opword 0x38810068
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x801F0000
		opword 0x64000020
		opword 0x901F0000
		opword 0x801F0000
		opword 0x60000200
		opword 0x901F0000
		opword 0xE3E100D8
		opword 0xCBE100D0
		opword 0xE3C100C8
		opword 0xCBC100C0
		opword 0xE3A100B8
		opword 0xCBA100B0
		opword 0xBB410098
		opword 0x800100E4
		opword 0x7C0803A6
		opword 0x382100E0
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapObjTranslate(const char* name, f32 x, f32 y, f32 z) {
	MapObject* obj = mapGetMapObj(name);
	Mtx trans;

	if (obj) {
		if (!(obj->flags & 0x200)) {
			MTXIdentity(obj->unkAC);
		}
#ifdef NONMATCHING
		MTXTrans(trans, x / 10.0f, y / 10.0f, z / 10.0f);
#endif
#ifndef NONMATCHING
		MTXTrans(trans, x / EXT_LIT(float_10_80419864, 10.0f), y / EXT_LIT(float_10_80419864, 10.0f), z / EXT_LIT(float_10_80419864, 10.0f));
#endif
		MTXConcat(obj->unkAC, trans, obj->unkAC);
		obj->flags |= 0x200000;
		obj->flags |= 0x200;
	}
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapObjScale(const char* name, f32 x, f32 y, f32 z) {
	MapObject* obj = mapGetMapObj(name);
	Mtx scale;

	if (obj) {
		if (!(obj->flags & 0x200)) {
			MTXIdentity(obj->unkAC);
		}
		MTXScale(scale, x, y, z);
		MTXConcat(obj->unkAC, scale, obj->unkAC);
		obj->flags |= 0x200000;
		obj->flags |= 0x200;
	}
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapObjGetPosSub(MapObject* obj, Vec* sum, s32* count, BOOL doNext) {
	Vec pos;

	if (obj->child) {
		mapObjGetPosSub(obj->child, sum, count, TRUE);
	}
	else {
		MTXMultVec(obj->modelWorldMtx, &obj->center, &pos);
		VECAdd(sum, &pos, sum);
		(*count)++;
	}
	if (doNext && obj->next) {
		mapObjGetPosSub(obj->next, sum, count, TRUE);
	}
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void mapObjGetPos(const char* name, Vec* pos) {
#ifdef NONMATCHING
	s32 count = 0;
	Vec sum = {0.0f, 0.0f, 0.0f};
	MapObject* obj = mapGetMapObj(name);
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		lis r5, vec3_802c18f4@ha
		opword 0x90010044
		opword 0xBF210024
		opword 0x7C7E1B79
		opword 0x3B800000
		opword 0x7C9F2378
		lwzu r7, vec3_802c18f4@l(r5)
		lwz r0, activeGroup(r13)
		opword 0x80C50004
		opword 0x80A50008
		opword 0x1C0002F4
		lwz r3, mapWork(r13)
		opword 0x93810008
		opword 0x7F430214
		opword 0x90E1000C
		opword 0x90C10010
		opword 0x90A10014
		opword 0x40820008
		opword 0x48000064
		opword 0x7F59D378
		opword 0x4800004C
		opword 0x83B90154
		opword 0x3B600000
		opword 0x4800002C
		opword 0x807D0008
		opword 0x7FC4F378
		opword 0x80630000
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x7FBCEB78
		opword 0x48000030
		opword 0x3B7B0001
		opword 0x3BBD0134
		opword 0x80190150
		opword 0x7C1B0000
		opword 0x4180FFD0
		opword 0x3B390178
		opword 0x3B9C0001
		opword 0x801A0000
		opword 0x7C1C0000
		opword 0x4180FFB0
		opword 0x3B800000
		opword 0x281C0000
		opword 0x40820028
		lis r3, vec3_802c1900@ha
		addi r4, r3, vec3_802c1900@l
		opword 0x80640000
		opword 0x80040004
		opword 0x907F0000
		opword 0x901F0004
		opword 0x80040008
		opword 0x901F0008
		opword 0x48000050
		opword 0x7F83E378
		opword 0x3881000C
		opword 0x38A10008
		opword 0x38C00000
		bl mapObjGetPosSub
		opword 0x80810008
		opword 0x3C004330
		opword 0x90010018
		lis r3, double_to_int_802c1998@ha
		opword 0x6C808000
		lfd f1, double_to_int_802c1998@l(r3)
		opword 0x9001001C
		opword 0x7FE4FB78
		lfs f2, float_1_80419860(r2)
		opword 0x3861000C
		opword 0xC8010018
		opword 0xEC000828
		opword 0xEC220024
		bl PSVECScale
		opword 0xBB210024
		opword 0x80010044
		opword 0x7C0803A6
		opword 0x38210040
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
	if (!obj) {
		*pos = (Vec){0.0f, 0.0f, 0.0f};
		return;
	}
	mapObjGetPosSub(obj, &sum, &count, FALSE);
	VECScale(&sum, pos, 1.0f / count);
}
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapSetFog(s32 type, f32 start, f32 end, GXColor color) {
	MapWork* wp = &mapWork[activeGroup];

	wp->entries[0].fogType = type;
	wp->entries[0].fogStart = start;
	wp->entries[0].fogEnd = end;
	wp->entries[0].fogColor = color;
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapGetFog(s32* type, f32* start, f32* end, GXColor* color) {
	MapWork* wp = &mapWork[activeGroup];

	*type = wp->entries[0].fogType;
	*start = wp->entries[0].fogStart;
	*end = wp->entries[0].fogEnd;
	*color = wp->entries[0].fogColor;
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#define mapGetWork mapGetWork__af_inl
#endif
void mapFogOn(void) {
	mapGetWork()->entries[0].flags |= 1;
}

#ifndef NONMATCHING
#undef mapGetWork

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#define mapGetWork mapGetWork__af_inl
#endif
void mapFogOff(void) {
	mapGetWork()->entries[0].flags &= ~1;
}

#ifndef NONMATCHING
#undef mapGetWork

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapSetBlend(GXColor* color) {
	MapWork* wp = &mapWork[activeGroup];

	wp->entries[0].blend = *color;
	wp->entries[0].flags |= 2;
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapSetBlend2(GXColor* color) {
	MapWork* wp = &mapWork[activeGroup];

	wp->entries[0].blend2 = *color;
	wp->entries[0].flags |= 4;
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void mapGetBlend(GXColor* color) {
#ifdef NONMATCHING
	MapWork* wp = &mapWork[activeGroup];

	if (wp->entries[0].flags & 2) {
		*color = wp->entries[0].blend;
	}
	else {
		*color = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
#endif
#ifndef NONMATCHING
	asm volatile {
		lwz r0, activeGroup(r13)
		lwz r4, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7C840214
		opword 0xA0040004
		opword 0x540007BD
		opword 0x41820010
		opword 0x80040016
		opword 0x90030000
		opword 0x4E800020
		lwz r0, dat_80419840(r2)
		opword 0x90030000
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void mapGetBlend2(GXColor* color) {
#ifdef NONMATCHING
	MapWork* wp = &mapWork[activeGroup];

	if (wp->entries[0].flags & 4) {
		*color = wp->entries[0].blend2;
	}
	else {
		*color = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
#endif
#ifndef NONMATCHING
	asm volatile {
		lwz r0, activeGroup(r13)
		lwz r4, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7C840214
		opword 0xA0040004
		opword 0x5400077B
		opword 0x41820010
		opword 0x8004001A
		opword 0x90030000
		opword 0x4E800020
		lwz r0, dat_80419844(r2)
		opword 0x90030000
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#define mapGetWork mapGetWork__af_inl
#endif
void mapBlendOff(void) {
	mapGetWork()->entries[0].flags &= ~2;
}

#ifndef NONMATCHING
#undef mapGetWork

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#define mapGetWork mapGetWork__af_inl
#endif
void mapBlendOff2(void) {
	mapGetWork()->entries[0].flags &= ~4;
}

#ifndef NONMATCHING
#undef mapGetWork

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapObjSetColor(const char* name, GXColor* color) {
	MapObject* obj = mapGetMapObj(name);

	if (obj) {
		obj->color = *color;
		obj->flags |= 0x40;
	}
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void setColor(MapObject* obj, GXColor color, BOOL doNext) {
	if (obj) {
		obj->color = color;
		obj->flags |= 0x40;
		if (obj->child) {
			setColor(obj->child, color, TRUE);
		}
		if (doNext && obj->next) {
			setColor(obj->next, color, TRUE);
		}
	}
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapGrpSetColor(const char* name, GXColor color) {
	setColor(mapGetMapObj(name), color, FALSE);
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapSetProjTexObj(GXTexObj* obj, void* imgRef) {
	projTexObj = *obj;
	projTexImgRef = imgRef;
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void mapSetProjMtx(Mtx mtx) {
	MTXCopy(mtx, projMtx);
}

#ifdef NONMATCHING
extern int __float_nan[];
static inline s32 sp_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32 sp_sqrtf(f32 x) { const f64 _half = .5; const f64 _three = 3.0; if (x > 0.0f) { f64 guess = __frsqrte(x); guess = _half * guess * (_three - guess * guess * x); guess = _half * guess * (_three - guess * guess * x); guess = _half * guess * (_three - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (sp_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void spline_maketable(s32 n, Vec* pts, f32* t, Vec* out) {
#ifdef NONMATCHING
	f32* h;
	Vec* w;
	s32 i;
	f32 dx, dy, dz;
	f32 ax, ay, az;
#endif
#ifndef NONMATCHING
	char _af_pad[8];
	asm volatile {
		mr r26, r3
		lis r3, vec3_802c16d8@ha
		opword 0x7C9B2378
		addi r31, r3, vec3_802c16d8@l
		opword 0x7CBC2B78
		opword 0x7CDD3378
		opword 0x5743103A
		bl _mapAlloc
		opword 0x7C601B78
		opword 0x1C7A000C
		opword 0x7C1E0378
		bl _mapAlloc
		lfs f4, float_0_80419850(r2)
		opword 0x381AFFFF
		opword 0x38BB000C
		opword 0x38DC0004
		opword 0xD09C0000
		opword 0x7C0903A6
		opword 0x2C1A0001
		opword 0x40810120
		opword 0xC0250004
		opword 0xC005FFF8
		opword 0xC0650000
		opword 0xECA10028
		opword 0xC005FFF4
		opword 0xC0450008
		opword 0xEC630028
		opword 0xC025FFFC
		opword 0xEC050172
		opword 0xEC220828
		opword 0xEC0300FA
		opword 0xECA1007A
		opword 0xFC052040
		opword 0x4081004C
		opword 0xFC202834
		opword 0xC87F02A8
		opword 0xC85F02B0
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC05103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC05103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC05103C
		opword 0xFC010032
		opword 0xFCA50032
		opword 0xFCA02818
		opword 0x48000088
		opword 0xC81F02B8
		opword 0xFC050040
		opword 0x40800010
		lis r4, __float_nan@ha
		lfs f5, __float_nan@l(r4)
		opword 0x48000070
		stfs f5, _af_pad+0(r1)
		opword 0x3C007F80
		opword 0x80E10008
		opword 0x54E40050
		opword 0x7C040000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C040000
		opword 0x41820020
		opword 0x48000034
		opword 0x54E0027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x54E0027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r4, __float_nan@ha
		lfs f5, __float_nan@l(r4)
		opword 0xC006FFFC
		opword 0x38A5000C
		opword 0xEC00282A
		opword 0xD0060000
		opword 0x38C60004
		opword 0x4200FEE8
		opword 0x2C1A0001
		opword 0x38E00001
		opword 0x408100F8
		opword 0x381AFFFF
		opword 0x38BAFFF8
		opword 0x2C000008
		opword 0x408100B0
		opword 0x38050006
		opword 0x5744103A
		opword 0x5400E8FE
		opword 0x38DC0004
		opword 0x3884FFFC
		opword 0x7C0903A6
		opword 0x2C050001
		opword 0x40810090
		opword 0xC0260000
		opword 0x38E70008
		opword 0x7C1C242E
		opword 0xEC010024
		opword 0xD0060000
		opword 0xC0260004
		opword 0x7C1C242E
		opword 0xEC010024
		opword 0xD0060004
		opword 0xC0260008
		opword 0x7C1C242E
		opword 0xEC010024
		opword 0xD0060008
		opword 0xC026000C
		opword 0x7C1C242E
		opword 0xEC010024
		opword 0xD006000C
		opword 0xC0260010
		opword 0x7C1C242E
		opword 0xEC010024
		opword 0xD0060010
		opword 0xC0260014
		opword 0x7C1C242E
		opword 0xEC010024
		opword 0xD0060014
		opword 0xC0260018
		opword 0x7C1C242E
		opword 0xEC010024
		opword 0xD0060018
		opword 0xC026001C
		opword 0x7C1C242E
		opword 0xEC010024
		opword 0xD006001C
		opword 0x38C60020
		opword 0x4200FF78
		opword 0x54E5103A
		opword 0x5744103A
		opword 0x7C07D050
		opword 0x7CBC2A14
		opword 0x3884FFFC
		opword 0x7C0903A6
		opword 0x7C07D000
		opword 0x4080001C
		opword 0xC0250000
		opword 0x7C1C242E
		opword 0xEC010024
		opword 0xD0050000
		opword 0x38A50004
		opword 0x4200FFEC
		lfs f3, float_0_80419850(r2)
		opword 0x1D3A000C
		opword 0x341AFFFF
		opword 0xD07D0000
		opword 0x7F84E378
		opword 0x7D5D4A14
		opword 0x7FC5F378
		opword 0xD07D0004
		opword 0x7F66DB78
		opword 0x7C671B78
		opword 0xD07D0008
		opword 0xD06AFFF4
		opword 0xD06AFFF8
		opword 0xD06AFFFC
		opword 0x7C0903A6
		opword 0x40810084
		opword 0xC0240004
		opword 0xC0040000
		opword 0xEC010028
		opword 0xD0050000
		opword 0xC0050000
		opword 0xFC030000
		opword 0x4082000C
		lfs f0, float_0p0001_8041985c(r2)
		opword 0xD0050000
		opword 0xC046000C
		opword 0x38840004
		opword 0xC0260000
		opword 0xC0050000
		opword 0xEC220828
		opword 0xEC010024
		opword 0xD007000C
		opword 0xC0460010
		opword 0xC0260004
		opword 0xC0050000
		opword 0xEC220828
		opword 0xEC010024
		opword 0xD0070010
		opword 0xC0460014
		opword 0xC0260008
		opword 0x38C6000C
		opword 0xC0050000
		opword 0x38A50004
		opword 0xEC220828
		opword 0xEC010024
		opword 0xD0070014
		opword 0x38E7000C
		opword 0x4200FF84
		opword 0xC0430018
		opword 0x389AFFFE
		opword 0xC023000C
		opword 0x3804FFFF
		lfs f0, float_2_80419858(r2)
		opword 0x38A3000C
		opword 0xEC220828
		opword 0x38DE0004
		opword 0x38FD000C
		opword 0x391C0004
		opword 0xD03D000C
		opword 0xC043001C
		opword 0xC0230010
		opword 0xEC220828
		opword 0xD03D0010
		opword 0xC0430020
		opword 0xC0230014
		opword 0xEC220828
		opword 0xD03D0014
		opword 0xC05C0008
		opword 0xC03C0000
		opword 0xEC220828
		opword 0xEC200072
		opword 0xD023000C
		opword 0xC05C0008
		opword 0xC03C0000
		opword 0xEC220828
		opword 0xEC200072
		opword 0xD0230010
		opword 0xC05C0008
		opword 0xC03C0000
		opword 0xEC220828
		opword 0xEC200072
		opword 0xD0230014
		opword 0x7C0903A6
		opword 0x2C040001
		opword 0x408100D0
		opword 0xC0C60000
		opword 0xC0250000
		opword 0xC0A50004
		opword 0xECE60824
		opword 0xC0850008
		opword 0xC0450018
		opword 0xC025000C
		opword 0xC0670000
		opword 0xEC220828
		opword 0xECA62824
		opword 0xEC2708FC
		opword 0xEC862024
		opword 0xD027000C
		opword 0xC045001C
		opword 0xC0250010
		opword 0xC0670004
		opword 0xEC220828
		opword 0xEC2508FC
		opword 0xD0270010
		opword 0xC0450020
		opword 0xC0250014
		opword 0xC0670008
		opword 0xEC220828
		opword 0xEC2408FC
		opword 0xD0270014
		opword 0x38E7000C
		opword 0xC0260000
		opword 0xC0680008
		opword 0xC0480000
		opword 0xEC270072
		opword 0xEC431028
		opword 0xEC2008B8
		opword 0xD025000C
		opword 0xC0260000
		opword 0xC0680008
		opword 0xC0480000
		opword 0xEC250072
		opword 0xEC431028
		opword 0xEC2008B8
		opword 0xD0250010
		opword 0xC0260000
		opword 0x38C60004
		opword 0xC0680008
		opword 0xC0480000
		opword 0xEC240072
		opword 0x39080004
		opword 0xEC431028
		opword 0xEC2008B8
		opword 0xD0250014
		opword 0x38A5000C
		opword 0x4200FF38
		opword 0x5740103A
		opword 0x7CBD4A14
		opword 0x7D3E0214
		opword 0xC02AFFF4
		opword 0xC049FFF8
		opword 0x1D04000C
		opword 0xC005FFE8
		opword 0x5480103A
		opword 0x2C040000
		opword 0xEC02007C
		opword 0x7CDD4214
		opword 0x7CFE0214
		opword 0x7D034214
		opword 0xD005FFE8
		opword 0xC049FFF8
		opword 0xC02AFFF8
		opword 0xC005FFEC
		opword 0xEC02007C
		opword 0xD005FFEC
		opword 0xC049FFF8
		opword 0xC02AFFFC
		opword 0xC005FFF0
		opword 0xEC02007C
		opword 0xD005FFF0
		opword 0x40810138
		opword 0x5480F87F
		opword 0x7C0903A6
		opword 0x418200C4
		opword 0xC0670000
		opword 0xC046000C
		opword 0xC0260000
		opword 0xC0080000
		opword 0xEC2308BC
		opword 0xEC010024
		opword 0xD0060000
		opword 0xC0670000
		opword 0xC0460010
		opword 0xC0260004
		opword 0xC0080004
		opword 0xEC2308BC
		opword 0xEC010024
		opword 0xD0060004
		opword 0xC0670000
		opword 0xC0460014
		opword 0xC0260008
		opword 0xC0080008
		opword 0xEC2308BC
		opword 0xEC010024
		opword 0xD0060008
		opword 0xC067FFFC
		opword 0xC0460000
		opword 0xC026FFF4
		opword 0xC008FFF4
		opword 0xEC2308BC
		opword 0xEC010024
		opword 0xD006FFF4
		opword 0xC067FFFC
		opword 0xC0460004
		opword 0xC026FFF8
		opword 0xC008FFF8
		opword 0xEC2308BC
		opword 0xEC010024
		opword 0xD006FFF8
		opword 0xC067FFFC
		opword 0x38E7FFF8
		opword 0xC008FFFC
		opword 0x3908FFE8
		opword 0xC0460008
		opword 0xC026FFFC
		opword 0xEC2308BC
		opword 0xEC010024
		opword 0xD006FFFC
		opword 0x38C6FFE8
		opword 0x4200FF4C
		opword 0x70840001
		opword 0x4182006C
		opword 0x7C8903A6
		opword 0xC0670000
		opword 0xC046000C
		opword 0xC0260000
		opword 0xC0080000
		opword 0xEC2308BC
		opword 0xEC010024
		opword 0xD0060000
		opword 0xC0670000
		opword 0xC0460010
		opword 0xC0260004
		opword 0xC0080004
		opword 0xEC2308BC
		opword 0xEC010024
		opword 0xD0060004
		opword 0xC0670000
		opword 0x38E7FFFC
		opword 0xC0080008
		opword 0x3908FFF4
		opword 0xC0460014
		opword 0xC0260008
		opword 0xEC2308BC
		opword 0xEC010024
		opword 0xD0060008
		opword 0x38C6FFF4
		opword 0x4200FFA0
		bl _mapFree
		opword 0x7FC3F378
		bl _mapFree
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
	h = _mapAlloc(n * sizeof(f32));
	w = _mapAlloc(n * sizeof(Vec));
	t[0] = 0.0f;
	for (i = 1; i < n; i++) {
		dx = pts[i].x - pts[i - 1].x;
		dy = pts[i].y - pts[i - 1].y;
		dz = pts[i].z - pts[i - 1].z;
		t[i] = t[i - 1] + sp_sqrtf(dx * dx + dy * dy + dz * dz);
	}
	for (i = 1; i < n; i++) {
		t[i] /= t[n - 1];
	}
	out[0].x = 0.0f;
	out[0].y = 0.0f;
	out[0].z = 0.0f;
	out[n - 1].x = 0.0f;
	out[n - 1].y = 0.0f;
	out[n - 1].z = 0.0f;
	for (i = 0; i < n - 1; i++) {
		h[i] = t[i + 1] - t[i];
		if (h[i] == 0.0f) {
			h[i] = 0.0001f;
		}
		w[i + 1].x = (pts[i + 1].x - pts[i].x) / h[i];
		w[i + 1].y = (pts[i + 1].y - pts[i].y) / h[i];
		w[i + 1].z = (pts[i + 1].z - pts[i].z) / h[i];
	}
	out[1].x = w[2].x - w[1].x;
	out[1].y = w[2].y - w[1].y;
	out[1].z = w[2].z - w[1].z;
	w[1].x = 2.0f * (t[2] - t[0]);
	w[1].y = 2.0f * (t[2] - t[0]);
	w[1].z = 2.0f * (t[2] - t[0]);
	for (i = 1; i < n - 2; i++) {
		ax = h[i] / w[i].x;
		ay = h[i] / w[i].y;
		az = h[i] / w[i].z;
		out[i + 1].x = (w[i + 2].x - w[i + 1].x) - ax * out[i].x;
		out[i + 1].y = (w[i + 2].y - w[i + 1].y) - ay * out[i].y;
		out[i + 1].z = (w[i + 2].z - w[i + 1].z) - az * out[i].z;
		w[i + 1].x = 2.0f * (t[i + 2] - t[i]) - ax * h[i];
		w[i + 1].y = 2.0f * (t[i + 2] - t[i]) - ay * h[i];
		w[i + 1].z = 2.0f * (t[i + 2] - t[i]) - az * h[i];
	}
	out[n - 2].x -= h[n - 2] * out[n - 1].x;
	out[n - 2].y -= h[n - 2] * out[n - 1].y;
	out[n - 2].z -= h[n - 2] * out[n - 1].z;
	for (i = n - 2; i > 0; i--) {
		out[i].x = (out[i].x - h[i] * out[i + 1].x) / w[i].x;
		out[i].y = (out[i].y - h[i] * out[i + 1].y) / w[i].y;
		out[i].z = (out[i].z - h[i] * out[i + 1].z) / w[i].z;
	}
	_mapFree(w);
	_mapFree(h);
}
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#endif
void spline_getvalue(Vec* out, f32 t, s32 n, Vec* pts, f32* ts, Vec* tbl) {
	s32 lo;
	s32 hi;
	s32 mid;
	f32 new_var;
	f32 u;
	f32 h;

	if (n == 2) {
		out->x = t * (pts[1].x - pts[0].x) + pts[0].x;
		new_var = pts[0].y;
		out->y = t * (pts[1].y - new_var) + new_var;
		out->z = t * (pts[1].z - pts[0].z) + pts[0].z;
		return;
	}
	hi = n - 1;
	lo = 0;
	while (lo < hi) {
		mid = (lo + hi) / 2;
		if (ts[mid] < t) {
			lo = mid + 1;
		}
		else {
			hi = mid;
		}
	}
	if (lo > 0) {
		lo--;
	}
	u = t - ts[lo];
	h = ts[lo + 1] - ts[lo];
#ifdef NONMATCHING
	out->x = pts[lo].x + u * ((pts[lo + 1].x - pts[lo].x) / h - h * (2.0f * tbl[lo].x + tbl[lo + 1].x) + u * (3.0f * tbl[lo].x + u * (tbl[lo + 1].x - tbl[lo].x) / h));
	out->y = pts[lo].y + u * ((pts[lo + 1].y - pts[lo].y) / h - h * (2.0f * tbl[lo].y + tbl[lo + 1].y) + u * (3.0f * tbl[lo].y + u * (tbl[lo + 1].y - tbl[lo].y) / h));
	out->z = pts[lo].z + u * ((pts[lo + 1].z - pts[lo].z) / h - h * (2.0f * tbl[lo].z + tbl[lo + 1].z) + u * (3.0f * tbl[lo].z + u * (tbl[lo + 1].z - tbl[lo].z) / h));
#endif
#ifndef NONMATCHING
	out->x = pts[lo].x + u * ((pts[lo + 1].x - pts[lo].x) / h - h * (EXT_LIT(float_2_80419858, 2.0f) * tbl[lo].x + tbl[lo + 1].x) + u * (EXT_LIT(float_3_8041984c, 3.0f) * tbl[lo].x + u * (tbl[lo + 1].x - tbl[lo].x) / h));
	out->y = pts[lo].y + u * ((pts[lo + 1].y - pts[lo].y) / h - h * (EXT_LIT(float_2_80419858, 2.0f) * tbl[lo].y + tbl[lo + 1].y) + u * (EXT_LIT(float_3_8041984c, 3.0f) * tbl[lo].y + u * (tbl[lo + 1].y - tbl[lo].y) / h));
	out->z = pts[lo].z + u * ((pts[lo + 1].z - pts[lo].z) / h - h * (EXT_LIT(float_2_80419858, 2.0f) * tbl[lo].z + tbl[lo + 1].z) + u * (EXT_LIT(float_3_8041984c, 3.0f) * tbl[lo].z + u * (tbl[lo + 1].z - tbl[lo].z) / h));
#endif
}

#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#define mapGetWork mapGetWork__af_inl
#endif
BOOL mapTestXLU(u32 flags, GXColor* color, GXColor* matColor) {
	if ((flags & 0x40) && color->a != 0xFF) {
		return TRUE;
	}
	if (matColor->a != 0xFF) {
		return TRUE;
	}
	if (!(flags & 0x800) && (mapGetWork()->entries[0].flags & 2) && mapGetWork()->entries[0].blend.a != 0xFF) {
		return TRUE;
	}
	if (!(flags & 0x1000) && (mapGetWork()->entries[0].flags & 4) && mapGetWork()->entries[0].blend2.a != 0xFF) {
		return TRUE;
	}
	return FALSE;
}

#ifndef NONMATCHING
#undef mapGetWork

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#define mapGetWork mapGetWork__af_inl
#pragma defer_codegen off
#endif
void mapSetTevCallback(s32 index, MapTevCallback callback) {
	mapGetWork()->entries[0].tevCallbacks[index] = callback;
}

#ifdef NONMATCHING
void mapObjFlushOn(const char* name) {
	mapObjFlagOn(name, 0x100000);
#endif
#ifndef NONMATCHING
#pragma defer_codegen reset

#undef mapGetWork

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
asm void bmapUnLoad(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	bl sysWaitDrawSync
	lwz r3, mapWork(r13)
	li r0, 0x1
	stw r0, activeGroup(r13)
	li r30, 0x0
	addi r31, r3, 0x2f4
	mr r29, r31
	b L_af_1
L_af_2:
	lwz r3, 0x154(r29)
	cmplwi r3, 0x0
	beq L_af_3
	bl _mapFree
	li r0, 0x0
	stw r0, 0x150(r29)
	stw r0, 0x154(r29)
L_af_3:
	lwz r3, 0x164(r29)
	cmplwi r3, 0x0
	beq L_af_4
	bl _mapFree
	li r0, 0x0
	stw r0, 0x160(r29)
	stw r0, 0x164(r29)
L_af_4:
	lwz r3, 0x16c(r29)
	cmplwi r3, 0x0
	beq L_af_5
	bl _mapFree
	li r0, 0x0
	stw r0, 0x16c(r29)
	stw r0, 0x168(r29)
L_af_5:
	addi r29, r29, 0x178
	addi r30, r30, 0x1
L_af_1:
	lwz r0, 0x0(r31)
	cmpw r30, r0
	blt L_af_2
	li r0, 0x0
	stw r0, unk_80418458(r13)
	bl hitReInit
	bl lightReInit
	bl envReInit
	mr r29, r31
	li r30, 0x0
	b L_af_6
L_af_7:
	lwz r3, 0x7c(r29)
	cmplwi r3, 0x0
	beq L_af_8
	bl arcDataCheck
	cmpwi r3, 0x0
	bne L_af_9
	lwz r3, 0x7c(r29)
	bl _mapFree
L_af_9:
	li r0, 0x0
	stw r0, 0x7c(r29)
L_af_8:
	lwz r3, 0x84(r29)
	cmplwi r3, 0x0
	beq L_af_10
	bl arcDataCheck
	cmpwi r3, 0x0
	bne L_af_11
	lwz r3, 0x84(r29)
	bl _mapFree
L_af_11:
	li r0, 0x0
	stw r0, 0x84(r29)
L_af_10:
	lwz r3, 0x8c(r29)
	cmplwi r3, 0x0
	beq L_af_12
	bl _mapFree
	li r0, 0x0
	stw r0, 0x8c(r29)
L_af_12:
	addi r3, r29, 0x6
	la r4, float_0_804198cc(r2)
	li r5, 0x10
	bl strncpy
	addi r29, r29, 0x178
	addi r30, r30, 0x1
L_af_6:
	lwz r0, 0x0(r31)
	cmpw r30, r0
	blt L_af_7
	li r3, 0x1
	bl arcDelete
	li r3, 0x2
	bl arcDelete
	mr r3, r31
	li r4, 0x0
	li r5, 0x2f4
	bl memset
	li r31, 0x0
	lwz r30, mapWork(r13)
	stw r31, activeGroup(r13)
	mr r29, r30
	b L_af_13
L_af_14:
	lwz r0, 0x170(r29)
	cmplwi r0, 0x0
	beq L_af_15
	lwz r3, 0x80(r29)
	bl _mapAllocTail
	stw r3, 0x7c(r29)
	lwz r3, 0x88(r29)
	bl _mapAllocTail
	stw r3, 0x84(r29)
	lwz r3, 0x170(r29)
	lwz r4, 0x7c(r29)
	bl aramMgrToMram
	lwz r3, 0x178(r29)
	lwz r4, 0x84(r29)
	bl aramMgrToMram
	li r0, 0x0
	stw r0, 0x170(r29)
	stw r0, 0x178(r29)
	b L_af_16
L_af_15:
	lwz r3, 0x90(r29)
	bl _mapAllocTail
	stw r3, 0x8c(r29)
	lwz r3, 0x174(r29)
	lwz r4, 0x8c(r29)
	bl aramMgrToMram
	li r0, 0x0
	stw r0, 0x174(r29)
L_af_16:
	mr r3, r31
	bl makeDisplayList
	addi r29, r29, 0x178
	addi r31, r31, 0x1
L_af_13:
	lwz r0, 0x0(r30)
	cmpw r31, r0
	blt L_af_14
	lwz r4, 0x8c(r30)
	cmplwi r4, 0x0
	beq L_af_17
	lwz r5, 0x90(r30)
	li r3, 0x1
	bl arcEntry
L_af_17:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
#endif
}

#ifdef NONMATCHING
void mapObjFlushOff(const char* name) {
	mapObjFlagOff(name, 0x100000);
#endif
#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
BOOL mapPreLoad(void) {
	return TRUE; //do nothing
#endif
}

#ifdef NONMATCHING
void mapGrpFlushOn(const char* name) {
	mapGrpFlagOn(name, 0x100000);
#endif
#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#pragma defer_codegen off
void mapLoad(const char* map) {
	MapWork* wp;

	MapWork* wp2;
	sysWaitDrawSync();
	wp2 = wp = mapWork;
	activeGroup = 0;

	memset(wp2, 0, sizeof(MapWork));
	_mapLoad(wp, 0, map);
	wp->entries[0].count = 1;
#endif
}

#ifdef NONMATCHING
void mapGrpFlushOff(const char* name) {
	mapGrpFlagOff(name, 0x100000);
#endif
#ifndef NONMATCHING
#pragma defer_codegen reset

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
asm void mapUnLoad(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	bl sysWaitDrawSync
	lwz r31, mapWork(r13)
	li r30, 0x0
	stw r30, activeGroup(r13)
	mr r29, r31
	b L_af_1
L_af_2:
	lwz r3, 0x154(r29)
	cmplwi r3, 0x0
	beq L_af_3
	bl _mapFree
	li r0, 0x0
	stw r0, 0x150(r29)
	stw r0, 0x154(r29)
L_af_3:
	lwz r3, 0x164(r29)
	cmplwi r3, 0x0
	beq L_af_4
	bl _mapFree
	li r0, 0x0
	stw r0, 0x160(r29)
	stw r0, 0x164(r29)
L_af_4:
	lwz r3, 0x16c(r29)
	cmplwi r3, 0x0
	beq L_af_5
	bl _mapFree
	li r0, 0x0
	stw r0, 0x16c(r29)
	stw r0, 0x168(r29)
L_af_5:
	addi r29, r29, 0x178
	addi r30, r30, 0x1
L_af_1:
	lwz r0, 0x0(r31)
	cmpw r30, r0
	blt L_af_2
	li r0, 0x0
	stw r0, unk_80418458(r13)
	bl hitReInit
	bl lightReInit
	bl envReInit
	li r3, 0x4
	bl camUnLoadRoad
	li r3, 0x4
	bl camSetTypePersp
	mr r29, r31
	li r30, 0x0
	b L_af_6
L_af_7:
	lwz r3, 0x7c(r29)
	cmplwi r3, 0x0
	beq L_af_8
	bl arcDataCheck
	cmpwi r3, 0x0
	bne L_af_9
	lwz r3, 0x7c(r29)
	bl _mapFree
L_af_9:
	li r0, 0x0
	stw r0, 0x7c(r29)
L_af_8:
	lwz r3, 0x84(r29)
	cmplwi r3, 0x0
	beq L_af_10
	bl arcDataCheck
	cmpwi r3, 0x0
	bne L_af_11
	lwz r3, 0x84(r29)
	bl _mapFree
L_af_11:
	li r0, 0x0
	stw r0, 0x84(r29)
L_af_10:
	lwz r3, 0x8c(r29)
	cmplwi r3, 0x0
	beq L_af_12
	bl _mapFree
	li r0, 0x0
	stw r0, 0x8c(r29)
L_af_12:
	addi r3, r29, 0x6
	la r4, float_0_804198cc(r2)
	li r5, 0x10
	bl strncpy
	addi r29, r29, 0x178
	addi r30, r30, 0x1
L_af_6:
	lwz r0, 0x0(r31)
	cmpw r30, r0
	blt L_af_7
	li r3, 0x1
	bl arcDelete
	mr r3, r31
	li r4, 0x0
	li r5, 0x2f4
	bl memset
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
#endif
}

#ifdef NONMATCHING
void mapObjSetFlushColor(const char* name, u8 r, u8 g, u8 b, u8 a) {
	GXColor color = {0};
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifdef NONMATCHING
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
void mapErrorEntry(s32 arg0, const char* arg1) { //1:1
	MapError* error = error_data;
#endif

#ifdef NONMATCHING
	mapObjSetColor(name, &color);
	mapObjFlagOff(name, 0x40);
#endif
#ifndef NONMATCHING
	error += error_count;
	error->field_0x20 = arg0;
	strncpy(error->field_0x0, arg1, sizeof(error->field_0x0) - 1);
	error_flag = TRUE;
	error_count++;
	error_count %= 32;
#endif
}

#ifdef NONMATCHING
void mapGrpSetFlushColor(const char* name, u8 r, u8 g, u8 b, u8 a) {
	mapGrpSetColor(name, (GXColor){r, g, b, a});
	mapGrpFlagOff(name, 0x40);
#endif
#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
const char* getMapDataDvdRoot(void) {
	asm volatile {
		la r3, str_80419848(r2)
	}
}
#pragma pop

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
void N_mapDispOff(void) {
	unk_80418458 = TRUE;
#endif
}

#ifdef NONMATCHING
void mapObjGetFlushColor(const char* name, u8* r, u8* g, u8* b, u8* a) {
	MapObject* obj = mapGetMapObj(name);
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#endif

#ifdef NONMATCHING
	if (!obj) {
		error_data[error_count].field_0x20 = 0;
		strncpy(error_data[error_count].field_0x0, name, sizeof(error_data[0].field_0x0) - 1);
		error_flag = TRUE;
		error_count++;
		error_count %= 32;
		return;
	}
	*r = obj->color.r;
	*g = obj->color.g;
	*b = obj->color.b;
	*a = obj->color.a;
#endif
#ifndef NONMATCHING
#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
void N_mapDispOn(void) {
	unk_80418458 = FALSE;
#endif
}

#ifdef NONMATCHING
// Stand-in for a function the original linker dead-stripped; it only keeps the
// constants that function left behind in .rodata/.sdata2 in their original order.
void mapStrippedPool(const char** str, f32* val) {
	str[0] = ".";
	val[0] = 3.0f;
	val[1] = 0.0f;
	val[2] = 0.5f;
	val[3] = 2.0f;
	str[1] = "%s/m/%s/d";
	str[2] = "information";
	str[3] = "ver1.01";
	str[4] = "ver1.02";
	str[5] = "--/--/-- --:--:--";
	str[6] = "\x83\x52\x83\x93\x83\x6F\x81\x5B\x83\x67\x82\xB3\x82\xEA\x82\xC4\x82\xA2\x82\xDC\x82\xB9\x82\xF1";
	str[7] = "animation_table";
	str[8] = "curve_table";
#endif
#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
MapWork* mapGetWork(void) {
	return &mapWork[activeGroup];
#endif
}

#ifdef NONMATCHING
#pragma force_active on
#pragma explicit_zero_data on
__declspec(section ".sdata") u32 gap_07_8040F3F4_sdata[3] = {0};
#pragma explicit_zero_data reset
#pragma force_active reset
#endif
#ifndef NONMATCHING
#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
s32 mapGetActiveGroup(void) {
	return activeGroup;
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
void mapGetJointsSub(MapFileJoint* joint, s32* numJoints) { //1:1
	(*numJoints)++;
	if (joint->child) {
		mapGetJointsSub(joint->child, numJoints);
	}
	if (joint->next) {
		mapGetJointsSub(joint->next, numJoints);
	}
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
s32 mapGetJoints(MapFileJoint* joint) { //1:1
	s32 numJoints;

	numJoints = 0;
	if (joint) {
		numJoints = 1;
		if (joint->child) {
			mapGetJointsSub(joint->child, &numJoints);
		}
	}
	return numJoints;
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void mapGetBoundingBox(Vec* min, Vec* max) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		lis r5, vec3_802c16d8@ha
		opword 0x90010034
		addi r7, r5, vec3_802c16d8@l
		lis r5, vec3_802c16e4@ha
		opword 0xBF61001C
		opword 0x7C7E1B78
		opword 0x7C9F2378
		opword 0x3B600000
		lwz r0, activeGroup(r13)
		lwz r9, mapWork(r13)
		opword 0x1D0002F4
		opword 0x80C70000
		opword 0x80070004
		opword 0x90C30000
		opword 0x7FA94214
		opword 0x90030004
		opword 0x80070008
		opword 0x90030008
		lwzu r3, vec3_802c16e4@l(r5)
		opword 0x80050004
		opword 0x90640000
		opword 0x90040004
		opword 0x80050008
		opword 0x90040008
		opword 0x839D0154
		opword 0x48000138
		opword 0x809C0008
		opword 0x28040000
		opword 0x41820124
		opword 0x8004005C
		opword 0x2C000000
		opword 0x41820118
		opword 0x387C001C
		opword 0x3884003C
		opword 0x38A10008
		bl PSMTXMultVec
		opword 0xC01E0000
		opword 0xC0210008
		opword 0xFC000840
		opword 0x40810008
		opword 0xD03E0000
		opword 0xC01E0004
		opword 0xC021000C
		opword 0xFC000840
		opword 0x40810008
		opword 0xD03E0004
		opword 0xC01E0008
		opword 0xC0210010
		opword 0xFC000840
		opword 0x40810008
		opword 0xD03E0008
		opword 0xC01F0000
		opword 0xC0210008
		opword 0xFC000840
		opword 0x40800008
		opword 0xD03F0000
		opword 0xC01F0004
		opword 0xC021000C
		opword 0xFC000840
		opword 0x40800008
		opword 0xD03F0004
		opword 0xC01F0008
		opword 0xC0210010
		opword 0xFC000840
		opword 0x40800008
		opword 0xD03F0008
		opword 0x809C0008
		opword 0x387C001C
		opword 0x38A10008
		opword 0x38840048
		bl PSMTXMultVec
		opword 0xC01E0000
		opword 0xC0210008
		opword 0xFC000840
		opword 0x40810008
		opword 0xD03E0000
		opword 0xC01E0004
		opword 0xC021000C
		opword 0xFC000840
		opword 0x40810008
		opword 0xD03E0004
		opword 0xC01E0008
		opword 0xC0210010
		opword 0xFC000840
		opword 0x40810008
		opword 0xD03E0008
		opword 0xC01F0000
		opword 0xC0210008
		opword 0xFC000840
		opword 0x40800008
		opword 0xD03F0000
		opword 0xC01F0004
		opword 0xC021000C
		opword 0xFC000840
		opword 0x40800008
		opword 0xD03F0004
		opword 0xC01F0008
		opword 0xC0210010
		opword 0xFC000840
		opword 0x40800008
		opword 0xD03F0008
		opword 0x3B7B0001
		opword 0x3B9C0134
		opword 0x801D0150
		opword 0x7C1B0000
		opword 0x4180FEC4
		opword 0xBB61001C
		opword 0x80010034
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
void mapInit(void) {
	mapWork = __memAlloc(HEAP_DEFAULT, sizeof(MapWork) * 2);
	memset(mapWork, 0, sizeof(MapWork) * 2);
	activeGroup = 0;
	mapClipOffFlag = FALSE;
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void mapBuildTexture(MapObject* obj, TEXPalette* texture, void* table) {
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x90010044
		opword 0xBE810010
		opword 0x7C771B78
		opword 0x7C982378
		opword 0x7CB92B78
		opword 0x3BA00000
		opword 0x3BC00000
		opword 0x48000198
		opword 0x381E0060
		opword 0x3B800000
		opword 0x7F63002E
		opword 0x7F7FDB78
		opword 0x48000170
		opword 0x835F000C
		opword 0x7F34CB78
		opword 0x3AC00000
		opword 0x807A0000
		opword 0x82A30000
		opword 0x48000024
		opword 0x80740004
		opword 0x7EA4AB78
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x4800001C
		opword 0x3A940004
		opword 0x3AD60001
		opword 0x80190000
		opword 0x7C160000
		opword 0x4180FFD8
		opword 0x3AC0FFFF
		opword 0x2C16FFFF
		opword 0x7EC4B378
		opword 0x40820008
		opword 0x38800000
		opword 0x7F03C378
		bl TEXGet
		opword 0x80A30000
		opword 0x809A0000
		opword 0x80050008
		opword 0x9004000C
		opword 0x80A30000
		opword 0x809A0000
		opword 0xA0050002
		opword 0xB0040008
		opword 0x80A30000
		opword 0x809A0000
		opword 0xA0050000
		opword 0xB004000A
		opword 0x80630000
		opword 0x80030004
		opword 0x2800000E
		opword 0x418100C8
		lis r3, jumptable_80303414@ha
		opword 0x5400103A
		addi r3, r3, jumptable_80303414@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x807A0000
		opword 0x38000000
		opword 0x98030004
		opword 0x480000A0
		opword 0x807A0000
		opword 0x38000001
		opword 0x98030004
		opword 0x48000090
		opword 0x807A0000
		opword 0x38000002
		opword 0x98030004
		opword 0x48000080
		opword 0x807A0000
		opword 0x38000003
		opword 0x98030004
		opword 0x48000070
		opword 0x807A0000
		opword 0x38000004
		opword 0x98030004
		opword 0x48000060
		opword 0x807A0000
		opword 0x38000005
		opword 0x98030004
		opword 0x48000050
		opword 0x807A0000
		opword 0x38000006
		opword 0x98030004
		opword 0x48000040
		opword 0x807A0000
		opword 0x38000007
		opword 0x98030004
		opword 0x48000030
		opword 0x807A0000
		opword 0x38000008
		opword 0x98030004
		opword 0x48000020
		opword 0x807A0000
		opword 0x38000009
		opword 0x98030004
		opword 0x48000010
		opword 0x807A0000
		opword 0x3800000A
		opword 0x98030004
		opword 0x3BFF0004
		opword 0x3B9C0001
		opword 0x881B000B
		opword 0x7C1C0000
		opword 0x4180FE8C
		opword 0x3BDE0008
		opword 0x3BBD0001
		opword 0x80770008
		opword 0x8003005C
		opword 0x7C1D0000
		opword 0x4180FE60
		opword 0x807700E4
		opword 0x28030000
		opword 0x41820010
		opword 0x7F04C378
		opword 0x7F25CB78
		bl mapBuildTexture
		opword 0x807700E8
		opword 0x28030000
		opword 0x41820010
		opword 0x7F04C378
		opword 0x7F25CB78
		bl mapBuildTexture
		opword 0xBA810010
		opword 0x80010044
		opword 0x7C0803A6
		opword 0x38210040
	}
}
#pragma pop

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
MapObject* _mapEnt(MapFileJoint* joint, MapObject* parent, Mtx mtx, s32 index) {
	asm volatile {
		opword 0x9421FEE0
		opword 0x7C0802A6
		opword 0x1D060178
		opword 0x90010124
		opword 0x93E1011C
		opword 0x93C10118
		opword 0x7C9E2378
		opword 0x93A10114
		opword 0x7C7D1B78
		opword 0x93810110
		opword 0x7CBC2B78
		lwz r0, activeGroup(r13)
		lwz r7, mapWork(r13)
		opword 0x1C6002F4
		opword 0x38080150
		opword 0x7C871A14
		opword 0x7C04002E
		opword 0x7C644214
		opword 0x83E30154
		opword 0x7C0903A6
		opword 0x2C000000
		opword 0x40810018
		opword 0x801F0008
		opword 0x28000000
		opword 0x4182000C
		opword 0x3BFF0134
		opword 0x4200FFF0
		opword 0x38000000
		opword 0x386100E0
		opword 0x901F0000
		opword 0x93BF0008
		opword 0xB0DF00DE
		opword 0xC03D0030
		opword 0xC05D0034
		opword 0xC07D0038
		bl PSMTXTrans
		opword 0xC03D0018
		opword 0x386100B0
		opword 0xC05D001C
		opword 0xC07D0020
		bl PSMTXScale
		lfs f1, float_deg2rad_80419868(r2)
		opword 0x38610080
		opword 0xC01D0024
		opword 0x38800078
		opword 0xEC210032
		bl PSMTXRotRad
		lfs f1, float_deg2rad_80419868(r2)
		opword 0x38610050
		opword 0xC01D0028
		opword 0x38800079
		opword 0xEC210032
		bl PSMTXRotRad
		lfs f1, float_deg2rad_80419868(r2)
		opword 0x38610020
		opword 0xC01D002C
		opword 0x3880007A
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x386100E0
		opword 0x38810020
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386100E0
		opword 0x38810050
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386100E0
		opword 0x38810080
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386100E0
		opword 0x388100B0
		opword 0x38BF004C
		bl PSMTXConcat
		opword 0x7F83E378
		opword 0x389F004C
		opword 0x38BF001C
		bl PSMTXConcat
		opword 0x387F00AC
		bl PSMTXIdentity
		opword 0x80BF0000
		opword 0x38800004
		opword 0x3860FFFF
		opword 0x38000000
		opword 0x60A50200
		opword 0x90BF0000
		opword 0x989F0005
		opword 0xB07F00DC
		opword 0x93DF00E0
		opword 0x901F00E8
		opword 0x901F00E4
		opword 0x807D0058
		opword 0x28030000
		opword 0x41820338
		opword 0x88030002
		opword 0x540007FF
		opword 0x41820010
		opword 0x801F0000
		opword 0x60000008
		opword 0x901F0000
		opword 0x807D0058
		opword 0x88030000
		opword 0x2C000002
		opword 0x418201B8
		opword 0x40800014
		opword 0x2C000000
		opword 0x41820018
		opword 0x4080018C
		opword 0x480001D8
		opword 0x2C000004
		opword 0x408001D0
		opword 0x480001B4
		opword 0x811F0008
		opword 0x39200000
		opword 0x7D264B78
		opword 0x39600000
		opword 0x80E8005C
		opword 0x39800000
		opword 0x48000124
		opword 0x38060060
		opword 0x7C68002E
		opword 0x8803000A
		opword 0x28000002
		opword 0x4082000C
		opword 0x396B0001
		opword 0x48000010
		opword 0x28000001
		opword 0x40820008
		opword 0x398C0001
		opword 0x38000002
		opword 0x38860060
		opword 0x39400000
		opword 0x38A00000
		opword 0x7C0903A6
		opword 0x7C68202E
		opword 0x3805000C
		opword 0x7C63002E
		opword 0x28030000
		opword 0x418200CC
		opword 0x8803000A
		opword 0x28000002
		opword 0x4082000C
		opword 0x396B0001
		opword 0x48000010
		opword 0x28000001
		opword 0x40820008
		opword 0x398C0001
		opword 0x7C68202E
		opword 0x38050010
		opword 0x7C63002E
		opword 0x28030000
		opword 0x41820098
		opword 0x8803000A
		opword 0x28000002
		opword 0x4082000C
		opword 0x396B0001
		opword 0x48000010
		opword 0x28000001
		opword 0x40820008
		opword 0x398C0001
		opword 0x7C68202E
		opword 0x38050014
		opword 0x7C63002E
		opword 0x28030000
		opword 0x41820064
		opword 0x8803000A
		opword 0x28000002
		opword 0x4082000C
		opword 0x396B0001
		opword 0x48000010
		opword 0x28000001
		opword 0x40820008
		opword 0x398C0001
		opword 0x7C68202E
		opword 0x38050018
		opword 0x7C63002E
		opword 0x28030000
		opword 0x41820030
		opword 0x8803000A
		opword 0x28000002
		opword 0x4082000C
		opword 0x396B0001
		opword 0x48000010
		opword 0x28000001
		opword 0x40820008
		opword 0x398C0001
		opword 0x38A50010
		opword 0x394A0003
		opword 0x4200FF28
		opword 0x38C60008
		opword 0x39290001
		opword 0x7C093800
		opword 0x4180FEDC
		opword 0x2C0B0000
		opword 0x41820010
		opword 0x38000002
		opword 0x981F0004
		opword 0x48000074
		opword 0x2C0C0000
		opword 0x41820010
		opword 0x38000001
		opword 0x981F0004
		opword 0x48000060
		opword 0x38000000
		opword 0x981F0004
		opword 0x48000054
		opword 0x801F0000
		opword 0x38600000
		opword 0x54000739
		opword 0x41820008
		opword 0x38600003
		opword 0x987F0004
		opword 0x48000038
		opword 0x801F0000
		opword 0x38600001
		opword 0x54000739
		opword 0x41820008
		opword 0x38600004
		opword 0x987F0004
		opword 0x4800001C
		opword 0x801F0000
		opword 0x38600002
		opword 0x54000739
		opword 0x41820008
		opword 0x38600005
		opword 0x987F0004
		opword 0x807D0058
		opword 0x88030002
		opword 0x540007BD
		opword 0x41820080
		opword 0x801F0000
		opword 0x60000010
		opword 0x901F0000
		opword 0x807D0058
		opword 0x88030002
		opword 0x540006F7
		opword 0x41820010
		opword 0x801F0000
		opword 0x60008000
		opword 0x901F0000
		opword 0x807D0058
		opword 0x88030000
		opword 0x2C000002
		opword 0x41820034
		opword 0x4080003C
		opword 0x2C000000
		opword 0x41820010
		opword 0x40800018
		opword 0x4800002C
		opword 0x48000028
		opword 0x38000002
		opword 0x981F0004
		opword 0x48000024
		opword 0x38000000
		opword 0x981F0004
		opword 0x48000018
		opword 0x38000001
		opword 0x981F0004
		opword 0x4800000C
		opword 0x38000002
		opword 0x981F0004
		opword 0x801F0000
		opword 0x540006F7
		opword 0x41820030
		opword 0x281E0000
		opword 0x41820068
		opword 0x807E0000
		opword 0x546006F7
		opword 0x4082000C
		opword 0x546006B5
		opword 0x41820054
		opword 0x801F0000
		opword 0x54000734
		opword 0x901F0000
		opword 0x48000044
		opword 0x281E0000
		opword 0x4182003C
		opword 0x807E0000
		opword 0x546006F7
		opword 0x4082000C
		opword 0x546006B5
		opword 0x41820028
		opword 0x801F0000
		opword 0x60000020
		opword 0x901F0000
		opword 0x801E0000
		opword 0x54000421
		opword 0x41820010
		opword 0x801F0000
		opword 0x60008000
		opword 0x901F0000
		opword 0x807D0058
		opword 0x88030002
		opword 0x5400077B
		opword 0x41820030
		opword 0x801F0000
		opword 0x60000004
		opword 0x901F0000
		opword 0x48000020
		lis r3, str_802C1A50@ha
		lis r5, str_802C1A5C@ha
		addi r3, r3, str_802C1A50@l
		opword 0x388002E5
		addi r5, r5, str_802C1A5C@l
		opword 0x4CC63182
		bl OSPanic
		opword 0x801D005C
		opword 0x2C000000
		opword 0x41820028
		opword 0x387D003C
		opword 0x389D0048
		opword 0x38BF0010
		bl PSVECAdd
		opword 0x387F0010
		lfs f1, float_0p5_80419854(r2)
		opword 0x7C641B78
		bl PSVECScale
		opword 0x4800001C
		opword 0x807D0030
		opword 0x801D0034
		opword 0x907F0010
		opword 0x901F0014
		opword 0x801D0038
		opword 0x901F0018
		opword 0x801D005C
		opword 0x2C000000
		opword 0x41820048
		opword 0x387F001C
		opword 0x389F0010
		opword 0x38A10014
		bl PSMTXMultVec
		opword 0x387F001C
		opword 0x389D0048
		opword 0x38A10008
		bl PSMTXMultVec
		opword 0x38610014
		opword 0x38810008
		bl PSVECSquareDistance
		lfs f0, float_20000_804198d8(r2)
		opword 0xFC010040
		opword 0x40800010
		opword 0x801F0000
		opword 0x60000002
		opword 0x901F0000
		opword 0x80010124
		opword 0x7FE3FB78
		opword 0x83E1011C
		opword 0x83C10118
		opword 0x83A10114
		opword 0x83810110
		opword 0x7C0803A6
		opword 0x38210120
	}
}
#pragma pop

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
MapObject* mapEntrySub(MapFileJoint* joint, MapObject* parent, Mtx mtx, BOOL isRoot, s32 index) {
	MapObject* obj = _mapEnt(joint, parent, mtx, index);
	if (joint->child) {
		obj->child = mapEntrySub(joint->child, obj, obj->modelWorldMtx, FALSE, index);
	}
	if (!isRoot) {
		if (joint->next) {
			obj->next = mapEntrySub(joint->next, parent, mtx, FALSE, index);
		}
	}
	return obj;
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
MapObject* mapEntry(MapFileJoint* joint, Mtx mtx, s32 index) {
	MapWork* wp = (0, &mapWork[activeGroup]);
	u32 size;

	wp->entries[index].numJoints = mapGetJoints(joint);
	size = (((wp->entries[index].numJoints * sizeof(MapObject)) + 32) - 1) & ~(32 - 1);
	wp->entries[index].objects = _mapAlloc(size);
	memset(wp->entries[index].objects, 0, size);
	return mapEntrySub(joint, NULL, mtx, TRUE, index);
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
#define culling ((const GXCullMode*)culling_678) // FAKE: local static named by the pool
void makeDisplayList(BOOL group) {
	MapEntry* e;
	MapWork* wp = mapGetWork();
	void* buf;
	int i;
	int j;
	int pass;
	u32 total;
	u8* dst;
	MapObject* obj;
	MapJointDrawModeEx* dm;
	s32 k;
	void* material;

	buf = _mapAlloc(0x10000);
	e = &wp->entries[group];
	__mapdrv_make_dl = TRUE;
	total = 0;
	for (pass = 0; pass < 2; pass++) {
		obj = e->objects;
		for (k = 0; k < 8; k++) {
			MAPOBJ_DL(obj)[k] = NULL;
			MAPOBJ_DLSIZE(obj)[k] = 0;
		}
		for (i = 0; i < wp->entries[group].numJoints; i++, obj++) {
			if (obj->joints->partCount < 1 || obj->joints->partCount > 8) {
				continue;
			}
			dm = (MapJointDrawModeEx*)obj->joints->drawMode;
			if (dm->flags & 8) {
				continue;
			}
			if (dm->lightMask) {
				continue;
			}
			if (shadowGetCharShadowProjection() && (obj->flags & 4)) {
				continue;
			}
			if (!(e->flags & 0x8000)) {
				continue;
			}
			for (j = 0; j < obj->joints->partCount; j++) {
				material = obj->joints->parts[j].material;
				memset(buf, 0, 0x10000);
				DCInvalidateRange(buf, 0x10000);
				GXBeginDisplayList(buf, 0x10000);
				GXResetWriteGatherPipe();
				mapSetMaterial(obj, material);
				GXSetCullMode(culling[obj->joints->drawMode->cullMode]);
				MAPOBJ_DLSIZE(obj)[j] = GXEndDisplayList();
				if (pass == 0) {
					total += MAPOBJ_DLSIZE(obj)[j];
				}
				else {
					MAPOBJ_DL(obj)[j] = dst;
					dst += MAPOBJ_DLSIZE(obj)[j];
					memcpy(MAPOBJ_DL(obj)[j], buf, MAPOBJ_DLSIZE(obj)[j]);
					DCFlushRange(MAPOBJ_DL(obj)[j], MAPOBJ_DLSIZE(obj)[j]);
				}
			}
		}
		if (pass == 0) {
			e->dispListSize = total;
			if (e->dispListSize) {
				e->dispListBuf = _mapAllocTail(e->dispListSize);
				dst = e->dispListBuf;
			}
			else {
				((void**)((u8*)wp + 0x16C))[group * 0x5E] = NULL;
				break;
			}
		}
	}
	_mapFree(buf);
	__mapdrv_make_dl = FALSE;
}
#undef culling

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
MapEntryAnimData* mapSearchAnmObj(const char* animName) {
	MapWork* wp = &mapWork[activeGroup];
	MapEntry* entry;
	int j;
	int i;
	MapAnim* anim;

	entry = wp->entries;
	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		anim = (MapAnim*)entry->animData;
		for (j = 0; j < entry->numAnims; j++, anim++) {
			if ((anim->flags & 1) && !strcmp(anim->anim->name, animName)) {
				return (MapEntryAnimData*)anim;
			}
		}
	}
	return NULL;
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void mapCheckAnimation(const char* animName, BOOL* valid, f32* a3) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0xBF010010
		opword 0x7C781B78
		opword 0x7C9D2378
		opword 0x7CBE2B78
		opword 0x3B800000
		lwz r0, activeGroup(r13)
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7F430214
		opword 0x7F59D378
		opword 0x48000054
		opword 0x83F90164
		opword 0x3B600000
		opword 0x48000034
		opword 0xA01F0000
		opword 0x540007FF
		opword 0x41820020
		opword 0x807F0018
		opword 0x7F04C378
		opword 0x80630000
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x48000030
		opword 0x3B7B0001
		opword 0x3BFF0020
		opword 0x80190160
		opword 0x7C1B0000
		opword 0x4180FFC8
		opword 0x3B390178
		opword 0x3B9C0001
		opword 0x801A0000
		opword 0x7C1C0000
		opword 0x4180FFA8
		opword 0x3BE00000
		opword 0x38000000
		lfs f0, float_0_80419850(r2)
		opword 0x901D0000
		opword 0x281F0000
		opword 0xD01E0000
		opword 0x41820068
		opword 0xA01F0000
		opword 0x540007BD
		opword 0x4182000C
		opword 0x38000001
		opword 0x901D0000
		lwz r4, gp(r13)
		opword 0x3C004330
		opword 0x80DF0018
		lis r3, double_to_int_802c1998@ha
		opword 0x80A40004
		addi r4, r3, double_to_int_802c1998@l
		opword 0xC0260008
		opword 0x6CA38000
		opword 0xC01F0010
		opword 0x9061000C
		opword 0xEC410028
		lfs f3, float_1000_80419874(r2)
		opword 0x90010008
		opword 0xC8240000
		opword 0xC8010008
		opword 0xEC4300B2
		opword 0xEC000828
		opword 0xEC020024
		opword 0xD01E0000
		opword 0x4800000C
		opword 0x38000001
		opword 0x901D0000
		opword 0xBB010010
		opword 0x80010034
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void mapPlayAnimationLv(const char* name, s32 a, s32 b) {
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x90010044
		opword 0xBEE1001C
		opword 0x7C771B78
		opword 0x7C9E2378
		opword 0x7CB82B78
		opword 0x3BE00000
		opword 0x3B200000
		opword 0x3B400000
		lwz r0, activeGroup(r13)
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7FA30214
		opword 0x7FBCEB78
		opword 0x48000054
		opword 0x83FC0164
		opword 0x3B600000
		opword 0x4800002C
		opword 0x807F0018
		opword 0x7EE4BB78
		opword 0x80630000
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x3B200001
		opword 0x48000018
		opword 0x3B7B0001
		opword 0x3BFF0020
		opword 0x801C0160
		opword 0x7C1B0000
		opword 0x4180FFD0
		opword 0x2C190000
		opword 0x40820018
		opword 0x3B9C0178
		opword 0x3B5A0001
		opword 0x801D0000
		opword 0x7C1A0000
		opword 0x4180FFA8
		opword 0x2C190000
		opword 0x418201B8
		opword 0x38000000
		opword 0x2C180002
		opword 0xB01F0000
		opword 0x41820038
		opword 0x40800014
		opword 0x2C180000
		opword 0x41820058
		opword 0x40800018
		opword 0x48000050
		opword 0x2C180004
		opword 0x4182003C
		opword 0x40800044
		opword 0x48000024
		opword 0xA01F0000
		opword 0x60000100
		opword 0xB01F0000
		opword 0x48000030
		opword 0xA01F0000
		opword 0x60000200
		opword 0xB01F0000
		opword 0x48000020
		opword 0xA01F0000
		opword 0x60000400
		opword 0xB01F0000
		opword 0x48000010
		opword 0xA01F0000
		opword 0x60000800
		opword 0xB01F0000
		opword 0xA07F0000
		opword 0x546005EF
		opword 0x41820014
		lwz r4, gp(r13)
		opword 0x80640048
		opword 0x8084004C
		opword 0x48000070
		opword 0x546005AD
		opword 0x41820014
		lwz r4, gp(r13)
		opword 0x80640050
		opword 0x80840054
		opword 0x48000058
		opword 0x5460056B
		opword 0x41820014
		lwz r4, gp(r13)
		opword 0x80640058
		opword 0x8084005C
		opword 0x48000040
		opword 0x54600529
		opword 0x41820014
		lwz r4, gp(r13)
		opword 0x80640060
		opword 0x80840064
		opword 0x48000028
		lwz r4, gp(r13)
		opword 0x80040014
		opword 0x2C000000
		opword 0x41820010
		opword 0x80640038
		opword 0x8084003C
		opword 0x4800000C
		opword 0x80640040
		opword 0x80840044
		opword 0x3CC08000
		opword 0x3CA01062
		opword 0x800600F8
		opword 0x38C54DD3
		opword 0x38A00000
		opword 0x5400F0BE
		opword 0x7C060016
		opword 0x5406D1BE
		bl __div2i
		opword 0x909F000C
		opword 0x2C1E0001
		lfs f1, float_0_80419850(r2)
		opword 0x907F0008
		lfs f0, float_1_80419860(r2)
		opword 0xD03F0010
		opword 0xD01F0014
		opword 0xA01F0000
		opword 0x60000001
		opword 0xB01F0000
		opword 0x40820010
		opword 0xA01F0000
		opword 0x60000004
		opword 0xB01F0000
		opword 0x2C1E0002
		opword 0x4082005C
		lwz r4, gp(r13)
		opword 0x3C004330
		opword 0x80BF0018
		lis r3, double_to_int_802c1998@ha
		opword 0x80840004
		opword 0x90010008
		opword 0x6C808000
		lfs f3, float_1000_80419874(r2)
		opword 0x9001000C
		opword 0xC0450008
		lfd f1, double_to_int_802c1998@l(r3)
		opword 0xC8010008
		opword 0xEC4300B2
		opword 0xEC000828
		opword 0xEC220024
		bl __cvt_dbl_usll
		opword 0x801F000C
		opword 0x80BF0008
		opword 0x7C040010
		opword 0x901F000C
		opword 0x7C032910
		opword 0x901F0008
		opword 0xBAE1001C
		opword 0x80010044
		opword 0x7C0803A6
		opword 0x38210040
	}
}
#pragma pop

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
void mapPauseAnimation(const char* name) {
	MapAnim* anim = mapSearchAnmObj_inl(name);
	if (anim) {
		anim->flags |= 0x10;
	}
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
void mapReStartAnimation(const char* name) {
	MapAnim* anim = mapSearchAnmObj_inl(name);
	if (anim) {
		anim->flags |= 0x20;
	}
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
void mapPauseAnimationAll(const char* name) {
	MapWork* wp = &mapWork[activeGroup];
	MapEntry* entry = wp->entries;
	int j;
	int i;
	MapAnim* anim;

	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		anim = (MapAnim*)entry->animData;
		for (j = 0; j < entry->numAnims; j++, anim++) {
			anim->flags |= 0x10;
		}
	}
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
void mapReStartAnimationAll(const char* name) {
	MapWork* wp = &mapWork[activeGroup];
	MapEntry* entry = wp->entries;
	int j;
	int i;
	MapAnim* anim;

	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		anim = (MapAnim*)entry->animData;
		for (j = 0; j < entry->numAnims; j++, anim++) {
			anim->flags |= 0x20;
		}
	}
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
void mapSetPlayRate(const char* name, f32 rate) {
	MapAnim* anim = mapSearchAnmObj_inl(name);
	if (anim) {
		anim->rate = rate;
	}
}

#undef lightGetNearObj

#undef lightGetNearObj
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void _mapLoad(MapWork* wp, BOOL group, const char* map) {
	char _af_pad[564];
	asm {
		li r0, 0x0
	}
	asm volatile {
		opword 0x7C992378
		opword 0x7CBA2B78
		opword 0x7C781B78
		opword 0x1FD90178
		lis r3, vec3_802c16d8@ha
		opword 0x7F44D378
		addi r23, r3, vec3_802c16d8@l
		opword 0x7FF8F214
		opword 0x38A00010
		opword 0x387F0006
		stw r0, error_flag(r13)
		stw r0, error_count(r13)
		bl strncpy
		opword 0x7F45D378
		la r3, _af_pad+440
		opword 0x389702D0
		opword 0x4CC63182
		bl sprintf
		opword 0x386101C0
		opword 0x389F007C
		opword 0x38BF0080
		bl arcOpen
		opword 0x801F007C
		opword 0x7FF4FB78
		opword 0x28000000
		opword 0x40820074
		opword 0x38610140
		opword 0x38C101C0
		la r4, str_804198D0(r2)
		la r5, str_80419848(r2)
		opword 0x4CC63182
		bl sprintf
		opword 0x38610140
		opword 0x38800002
		opword 0x38A00000
		bl DVDMgrOpen
		opword 0x7C721B78
		bl DVDMgrGetLength
		opword 0x907F0080
		opword 0x7FF1FB78
		opword 0x807F0080
		opword 0x3803001F
		opword 0x54030034
		bl _mapAllocTail
		opword 0x9074007C
		opword 0x7E439378
		opword 0x38C00000
		opword 0x80B10080
		opword 0x8094007C
		opword 0x3805001F
		opword 0x54050034
		bl DVDMgrRead
		opword 0x7E439378
		bl DVDMgrClose
		opword 0x7F45D378
		opword 0x386101C0
		opword 0x389702DC
		opword 0x4CC63182
		bl sprintf
		opword 0x7FB8F214
		opword 0x38000000
		opword 0x901D0084
		opword 0x386101C0
		opword 0x389F0084
		opword 0x38BF0088
		bl arcOpen
		opword 0x807D0084
		opword 0x28030000
		opword 0x4182000C
		bl UnpackTexPalette
		opword 0x48000080
		opword 0x386100C0
		opword 0x38C101C0
		la r4, str_804198D0(r2)
		la r5, str_80419848(r2)
		opword 0x4CC63182
		bl sprintf
		opword 0x386100C0
		opword 0x38800002
		opword 0x38A00000
		bl DVDMgrOpen
		opword 0x7C721B79
		opword 0x41820050
		bl DVDMgrGetLength
		opword 0x907D0088
		opword 0x7FB1EB78
		opword 0x807D0088
		opword 0x3803001F
		opword 0x54030034
		bl _mapAllocTail
		opword 0x907D0084
		opword 0x7E439378
		opword 0x38C00000
		opword 0x80B10088
		opword 0x809D0084
		opword 0x3805001F
		opword 0x54050034
		bl DVDMgrRead
		opword 0x7E439378
		bl DVDMgrClose
		opword 0x807D0084
		bl UnpackTexPalette
		bl GXInvalidateVtxCache
		opword 0x7C78F214
		opword 0x379F0038
		lwz r17, 0x80(r3)
		opword 0x8374007C
		opword 0x41820134
		opword 0x7F83E378
		opword 0x38800000
		opword 0x38A00044
		bl memset
		opword 0x7CD8F214
		opword 0x7F83E378
		opword 0x80060074
		opword 0x7F64DB78
		opword 0x38A00020
		opword 0x60000001
		opword 0x90060074
		bl memcpy
		opword 0x7C78F214
		opword 0x80030038
		opword 0x7C008840
		opword 0x408200F4
		opword 0x8003003C
		opword 0x38800020
		opword 0x28000000
		opword 0x41820014
		opword 0x381B0020
		opword 0x90030058
		opword 0x8083003C
		opword 0x38840020
		opword 0x7CB8F214
		opword 0x80050040
		opword 0x28000000
		opword 0x41820018
		opword 0x7C1B2214
		opword 0x9005005C
		opword 0x80050040
		opword 0x5400103A
		opword 0x7C840214
		opword 0x7CB8F214
		opword 0x80050044
		opword 0x28000000
		opword 0x41820018
		opword 0x7C1B2214
		opword 0x90050060
		opword 0x80050044
		opword 0x54001838
		opword 0x7C840214
		opword 0x7CB8F214
		opword 0x80050048
		opword 0x28000000
		opword 0x41820018
		opword 0x7C1B2214
		opword 0x90050064
		opword 0x80050048
		opword 0x54001838
		opword 0x7C840214
		opword 0x80030038
		opword 0x7C040040
		opword 0x40800010
		opword 0x7C1B2214
		opword 0x7C78F214
		opword 0x90030068
		opword 0x7C78F214
		opword 0x38A00000
		opword 0x93630078
		opword 0x7CA62B78
		opword 0x3C608000
		opword 0x4800002C
		opword 0x809F005C
		opword 0x80FF0058
		opword 0x7C84302E
		opword 0x7C07202E
		opword 0x7C001840
		opword 0x4181000C
		opword 0x7C003A14
		opword 0x7C07212E
		opword 0x38C60004
		opword 0x38A50001
		opword 0x801F0040
		opword 0x7C050040
		opword 0x4180FFD0
		opword 0x3A200000
		opword 0x7E328B78
		opword 0x48000048
		opword 0x807C0028
		opword 0x38120004
		opword 0x80BC0030
		opword 0x38970240
		opword 0x7C03002E
		opword 0x7C650214
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x807C0028
		opword 0x56201838
		opword 0x809C0020
		opword 0x7C03002E
		opword 0x7EC40214
		opword 0x4800001C
		opword 0x3A520008
		opword 0x3A310001
		opword 0x801C000C
		opword 0x7C110040
		opword 0x4180FFB4
		opword 0x3AC00000
		opword 0x3A200000
		opword 0x7E328B78
		opword 0x48000048
		opword 0x807C0028
		opword 0x38120004
		opword 0x80BC0030
		opword 0x389702E8
		opword 0x7C03002E
		opword 0x7C650214
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x807C0028
		opword 0x56201838
		opword 0x809C0020
		opword 0x7C03002E
		opword 0x7C040214
		opword 0x4800001C
		opword 0x3A520008
		opword 0x3A310001
		opword 0x801C000C
		opword 0x7C110040
		opword 0x4180FFB4
		opword 0x38000000
		opword 0x7F78F214
		opword 0x3AA00000
		opword 0x901B0094
		opword 0x7EB1AB78
		opword 0x48000048
		opword 0x807C0028
		opword 0x38110004
		opword 0x80BC0030
		opword 0x389702F8
		opword 0x7C03002E
		opword 0x7C650214
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x807C0028
		opword 0x56A01838
		opword 0x809C0020
		opword 0x7C03002E
		opword 0x7C040214
		opword 0x4800001C
		opword 0x3A310008
		opword 0x3AB50001
		opword 0x801C000C
		opword 0x7C150040
		opword 0x4180FFB4
		opword 0x38000000
		opword 0x7C78F214
		opword 0x3AA00000
		opword 0x90030098
		opword 0x7EB1AB78
		opword 0x48000048
		opword 0x807C0028
		opword 0x38110004
		opword 0x80BC0030
		opword 0x38970304
		opword 0x7C03002E
		opword 0x7C650214
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x807C0028
		opword 0x56A01838
		opword 0x809C0020
		opword 0x7C03002E
		opword 0x7C040214
		opword 0x4800001C
		opword 0x3A310008
		opword 0x3AB50001
		opword 0x801C000C
		opword 0x7C150040
		opword 0x4180FFB4
		opword 0x38000000
		opword 0x7E78F214
		opword 0x3AA00000
		opword 0x9013009C
		opword 0x7EB4AB78
		opword 0x48000048
		opword 0x807C0028
		opword 0x38140004
		opword 0x80BC0030
		opword 0x38970310
		opword 0x7C03002E
		opword 0x7C650214
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x807C0028
		opword 0x56A01838
		opword 0x809C0020
		opword 0x7C03002E
		opword 0x7C040214
		opword 0x4800001C
		opword 0x3A940008
		opword 0x3AB50001
		opword 0x801C000C
		opword 0x7C150040
		opword 0x4180FFB4
		opword 0x38000000
		opword 0x7C78F214
		opword 0x3AA00000
		opword 0x900300A0
		opword 0x7EB4AB78
		opword 0x48000048
		opword 0x807C0028
		opword 0x38140004
		opword 0x80BC0030
		opword 0x38970324
		opword 0x7C03002E
		opword 0x7C650214
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x807C0028
		opword 0x56A01838
		opword 0x809C0020
		opword 0x7C03002E
		opword 0x7C040214
		opword 0x4800001C
		opword 0x3A940008
		opword 0x3AB50001
		opword 0x801C000C
		opword 0x7C150040
		opword 0x4180FFB4
		opword 0x38000000
		opword 0x7C78F214
		opword 0x900300A4
		opword 0x80760004
		opword 0x80960008
		bl mapSearchDmdJoint
		opword 0x7C601B78
		opword 0x80760004
		opword 0x8096000C
		opword 0x7C140378
		bl mapSearchDmdJoint
		opword 0x7C601B78
		opword 0x80760000
		opword 0x7C160378
		opword 0x38970254
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x7C78F214
		opword 0xA0030004
		opword 0x60008000
		opword 0xB0030004
		opword 0x48000014
		opword 0x7C78F214
		opword 0xA0030004
		opword 0x5400047E
		opword 0xB0030004
		lfs f1, float_10_80419864(r2)
		opword 0x38610090
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x7E83A378
		opword 0x7F25CB78
		opword 0x38810090
		bl mapEntry
		opword 0x7EB8F214
		opword 0x7F25CB78
		opword 0x907500A8
		opword 0x7EC3B378
		opword 0x38810090
		bl hitEntry
		opword 0x907500AC
		opword 0x3AC00000
		opword 0x3A800000
		opword 0x480000DC
		opword 0x38140004
		lfs f1, float_10_80419864(r2)
		opword 0x7F83002E
		opword 0x38810084
		opword 0x3A400001
		opword 0x3A200000
		opword 0x387C0008
		bl PSVECScale
		opword 0x807C0004
		opword 0x38970330
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x3A400000
		opword 0x48000054
		opword 0x807C0004
		opword 0x38970340
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x3A400001
		opword 0x48000038
		opword 0x807C0004
		opword 0x3897034C
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x3A400002
		opword 0x4800001C
		opword 0x807C0004
		opword 0x38970360
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x3A400003
		opword 0x807C0040
		opword 0x3C03FED3
		opword 0x280060D8
		opword 0x40820008
		opword 0x823C003C
		opword 0x801C002C
		opword 0x7E449378
		opword 0x7E298B78
		opword 0x38A10084
		opword 0x90010008
		opword 0x38DC0014
		opword 0x38E10008
		opword 0x807C0000
		opword 0xC03C0030
		opword 0xC05C0034
		opword 0x811C0038
		bl lightEntry
		opword 0x3A940004
		opword 0x3AD60001
		opword 0x807F0098
		opword 0x80030000
		opword 0x7C160000
		opword 0x4180FF1C
		lwz r3, dat_8041982c(r2)
		lwz r0, dat_80419830(r2)
		stw r3, paper_ambient(r13)
		stw r0, paperCraft_ambient(r13)
		opword 0x8073009C
		opword 0x28030000
		opword 0x4182005C
		opword 0x80030000
		opword 0x7C98F214
		opword 0x90040024
		opword 0x8073009C
		opword 0x80030004
		opword 0x90040028
		opword 0x8073009C
		opword 0xC0030008
		opword 0xD004002C
		opword 0x8073009C
		opword 0xC003000C
		opword 0xD0040030
		opword 0x8073009C
		opword 0x80030010
		opword 0x90040034
		opword 0x80040024
		opword 0x2C000000
		opword 0x41820044
		opword 0xA0040004
		opword 0x60000001
		opword 0xB0040004
		opword 0x48000034
		opword 0x7C78F214
		opword 0x38000000
		opword 0x90030024
		lfs f0, float_0_80419850(r2)
		opword 0x90030028
		opword 0xD003002C
		opword 0xD0030030
		lwz r0, unk_80422f80(r2)
		opword 0x90030034
		opword 0xA0030004
		opword 0x5400043C
		opword 0xB0030004
		lwz r0, activeGroup(r13)
		opword 0x2C000001
		opword 0x41820024
		opword 0x7F45D378
		opword 0x386101C0
		opword 0x3897036C
		opword 0x4CC63182
		bl sprintf
		opword 0x388101C0
		opword 0x38600004
		bl camLoadRoad
		opword 0x38600004
		bl camSetTypePersp
		opword 0x807500A8
		opword 0x809D0084
		opword 0x80BB0094
		bl mapBuildTexture
		opword 0x38610078
		opword 0x3881006C
		bl mapGetBoundingBox
		opword 0x80170028
		opword 0x7C78F214
		opword 0x8097002C
		opword 0x90010060
		opword 0xC001006C
		opword 0x80170030
		opword 0xD0010060
		opword 0xC0210070
		opword 0x90810064
		opword 0xC0010074
		opword 0x90010068
		opword 0x80010060
		opword 0xD0210064
		opword 0xD0010068
		opword 0x80810064
		opword 0x900300B0
		opword 0x80010068
		opword 0x908300B4
		opword 0x900300B8
		opword 0x80B70034
		opword 0x80970038
		opword 0x8017003C
		opword 0x90A10054
		opword 0xC0010078
		opword 0x90810058
		opword 0xC0210070
		opword 0xD0010054
		opword 0xC0010074
		opword 0x9001005C
		opword 0x80010054
		opword 0xD0210058
		opword 0xD001005C
		opword 0x80810058
		opword 0x900300BC
		opword 0x8001005C
		opword 0x908300C0
		opword 0x900300C4
		opword 0x80B70040
		opword 0x80970044
		opword 0x80170048
		opword 0x90A10048
		opword 0xC001006C
		opword 0x9081004C
		opword 0xC021007C
		opword 0xD0010048
		opword 0xC0010074
		opword 0x90010050
		opword 0x80010048
		opword 0xD021004C
		opword 0xD0010050
		opword 0x8081004C
		opword 0x900300C8
		opword 0x80010050
		opword 0x908300CC
		opword 0x900300D0
		opword 0x80B7004C
		opword 0x80970050
		opword 0x80170054
		opword 0x90A1003C
		opword 0xC001006C
		opword 0x90810040
		opword 0xC0210070
		opword 0xD001003C
		opword 0xC0010080
		opword 0x90010044
		opword 0x8001003C
		opword 0xD0210040
		opword 0xD0010044
		opword 0x80810040
		opword 0x900300D4
		opword 0x80010044
		opword 0x908300D8
		opword 0x900300DC
		opword 0x80B70058
		opword 0x8097005C
		opword 0x80170060
		opword 0x90A10030
		opword 0xC0010078
		opword 0x90810034
		opword 0xC021007C
		opword 0xD0010030
		opword 0xC0010074
		opword 0x90010038
		opword 0x80010030
		opword 0xD0210034
		opword 0xD0010038
		opword 0x80810034
		opword 0x900300E0
		opword 0x80010038
		opword 0x908300E4
		opword 0x900300E8
		opword 0x80B70064
		opword 0x80970068
		opword 0x8017006C
		opword 0x90A10024
		opword 0x90810028
		opword 0x9001002C
		opword 0xC001006C
		opword 0x3AA00000
		opword 0xC021007C
		opword 0x7EB4AB78
		opword 0xD0010024
		opword 0xC0010080
		opword 0xD0210028
		opword 0x80010024
		opword 0xD001002C
		opword 0x80810028
		opword 0x900300EC
		opword 0x8001002C
		opword 0x908300F0
		opword 0x900300F4
		opword 0x80B70070
		opword 0x80970074
		opword 0x80170078
		opword 0x90A10018
		opword 0xC0010078
		opword 0x9081001C
		opword 0xC0210070
		opword 0xD0010018
		opword 0xC0010080
		opword 0x90010020
		opword 0x80010018
		opword 0xD021001C
		opword 0xD0010020
		opword 0x8081001C
		opword 0x900300F8
		opword 0x80010020
		opword 0x908300FC
		opword 0x90030100
		opword 0x80B7007C
		opword 0x80970080
		opword 0x80170084
		opword 0x90A1000C
		opword 0xC0010078
		opword 0x90810010
		opword 0xC021007C
		opword 0xD001000C
		opword 0xC0010080
		opword 0x90010014
		opword 0x8001000C
		opword 0xD0210010
		opword 0xD0010014
		opword 0x80810010
		opword 0x90030104
		opword 0x80010014
		opword 0x90830108
		opword 0x9003010C
		lwz r0, activeGroup(r13)
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7EC30214
		opword 0x7E76F214
		opword 0x48000048
		opword 0x80730060
		opword 0x38140004
		opword 0x80B30068
		opword 0x3897028C
		opword 0x7C03002E
		opword 0x7C650214
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0x80730060
		opword 0x56A01838
		opword 0x80930058
		opword 0x7C03002E
		opword 0x7E440214
		opword 0x4800001C
		opword 0x3A940008
		opword 0x3AB50001
		opword 0x80130044
		opword 0x7C150040
		opword 0x4180FFB4
		opword 0x3A400000
		opword 0x28120000
		opword 0x41820078
		opword 0x80120000
		opword 0x7C76F214
		opword 0x90030160
		opword 0x80030160
		opword 0x2C000000
		opword 0x41820060
		opword 0x54032834
		opword 0x3803001F
		opword 0x54110034
		opword 0x7E238B78
		bl _mapAlloc
		opword 0x7E96F214
		opword 0x7E258B78
		opword 0x90740164
		opword 0x38800000
		opword 0x80740164
		bl memset
		opword 0x38800000
		opword 0x80B40164
		opword 0x7C832378
		opword 0x48000018
		opword 0xB0650000
		opword 0x38840001
		opword 0x84120004
		opword 0x90050018
		opword 0x38A50020
		opword 0x80130160
		opword 0x7C040000
		opword 0x4180FFE4
		opword 0x7F23CB78
		bl makeDisplayList
		lwz r0, activeGroup(r13)
		opword 0x3A400000
		lwz r3, mapWork(r13)
		opword 0x1C0002F4
		opword 0x7C030214
		opword 0x7E20F214
		opword 0x82710154
		opword 0x48000070
		opword 0x80730008
		opword 0x8003005C
		opword 0x2C000001
		opword 0x41800058
		opword 0x2C000008
		opword 0x41810050
		opword 0x80630058
		opword 0x88030002
		opword 0x54000739
		opword 0x40820040
		opword 0x80030004
		opword 0x28000000
		opword 0x40820034
		bl shadowGetCharShadowProjection
		opword 0x2C030000
		opword 0x41820010
		opword 0x80130000
		opword 0x5400077B
		opword 0x4082001C
		opword 0xA0110004
		opword 0x54000421
		opword 0x41820010
		opword 0x80130000
		opword 0x60000100
		opword 0x90130000
		opword 0x3A520001
		opword 0x3A730134
		opword 0x80110150
		opword 0x7C120000
		opword 0x4180FF8C
		opword 0x38000000
		stw r0, unk_80418458(r13)
	}
}
#pragma pop

#undef lightGetNearObj
#endif


#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802c16d8[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c16e4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const u32 culling_678[4] = {0x00000001, 0x00000002, 0x00000003, 0x00000000};
__declspec(section ".rodata") const f32 vec3_802c1700[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c170c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c1718[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c1724[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c1730[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c173c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c1748[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c1754[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const GXCullMode culling[4] = { (GXCullMode)0x00000001, (GXCullMode)0x00000002, (GXCullMode)0x00000003, (GXCullMode)0x00000000 };
__declspec(section ".rodata") const GXTexMtx texmtx_tbl[10] = {GX_TEXMTX0, GX_TEXMTX1, GX_TEXMTX2, GX_TEXMTX3, GX_TEXMTX4, GX_TEXMTX5, GX_TEXMTX6, GX_TEXMTX7, GX_TEXMTX8, GX_TEXMTX9};
__declspec(section ".rodata") const s32 texfmt_tbl[11] = {4, 5, 6, 14, 0, 1, 2, 3, 8, 9, 10};
__declspec(section ".rodata") const s32 texwrap_tbl[3] = {GX_CLAMP, GX_REPEAT, GX_MIRROR};
__declspec(section ".rodata") const s32 palfmt_tbl[2] = {1, 2};
__declspec(section ".rodata") const GXLightID lightid_tbl[8] = {GX_LIGHT0, GX_LIGHT1, GX_LIGHT2, GX_LIGHT3, GX_LIGHT4, GX_LIGHT5, GX_LIGHT6, GX_LIGHT7};
__declspec(section ".rodata") const f32 vec3_802c17f8[3] = {0.0f, 0.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802c1804[3] = {0.0f, 1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c1810[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c181c[3] = {0.0f, 0.0f, -1.0f};
__declspec(section ".rodata") const f32 vec3_802c1828[3] = {0.0f, 0.0f, -1.0f};
__declspec(section ".rodata") const GXVtxAttrFmtList attr_fmt[12] = {
	{GX_VA_POS, GX_POS_XYZ, GX_F32, 0},
	{GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0},
	{GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0},
	{GX_VA_TEX0, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX1, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX2, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX3, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX4, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX5, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX6, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX7, GX_TEX_ST, GX_F32, 0},
	{GX_VA_NULL, GX_POS_XY, GX_U8, 0},
};
__declspec(section ".rodata") const f32 vec3_802c18f4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c1900[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const char str_802C190C[12] = "%s/m/%s/d\0\0";
__declspec(section ".rodata") const char str_802C1918[12] = "information";
__declspec(section ".rodata") const char str_802C1924[8] = "ver1.01";
__declspec(section ".rodata") const char str_802C192C[8] = "ver1.02";
__declspec(section ".rodata") const char str_802C1934[20] = "--/--/-- --:--:--\0\0";
__declspec(section ".rodata") const char str_802C1948[28] = "\x83R\x83\x93\x83o\x81[\x83g\x82\xb3\x82\xea\x82\xc4\x82\xa2\x82\xdc\x82\xb9\x82\xf1\0\0\0";
__declspec(section ".rodata") const char str_802C1964[16] = "animation_table";
__declspec(section ".rodata") const char str_802C1974[12] = "curve_table";
__declspec(section ".rodata") const f64 double_0p5_802c1980 = 0.5;
__declspec(section ".rodata") const f64 double_3_802c1988 = 3.0;
__declspec(section ".rodata") const f64 double_0_802c1990 = 0.0;
__declspec(section ".rodata") const f64 double_to_int_802c1998 = 4503601774854144.0;
__declspec(section ".rodata") const f64 double_to_int_mask_802c19a0 = 4503599627370496.0;
__declspec(section ".rodata") const char str_802C19A8[12] = "./m/%s/d\0\0\0";
__declspec(section ".rodata") const char str_802C19B4[12] = "./m/%s/t\0\0\0";
__declspec(section ".rodata") const char str_802C19C0[16] = "texture_table\0\0";
__declspec(section ".rodata") const char str_802C19D0[12] = "light_table";
__declspec(section ".rodata") const char str_802C19DC[12] = "fog_table\0\0";
__declspec(section ".rodata") const char str_802C19E8[20] = "material_name_table";
__declspec(section ".rodata") const char str_802C19FC[12] = "vcd_table\0\0";
__declspec(section ".rodata") const char str_802C1A08[16] = "ambientLight\0\0\0";
__declspec(section ".rodata") const char str_802C1A18[12] = "pointLight\0";
__declspec(section ".rodata") const char str_802C1A24[20] = "directionalLight\0\0\0";
__declspec(section ".rodata") const char str_802C1A38[12] = "spotLight\0\0";
__declspec(section ".rodata") const char str_802C1A44[12] = "./m/%s/c\0\0\0";
__declspec(section ".rodata") const char str_802C1A50[12] = "mapdrv.c\0\0\0";
__declspec(section ".rodata") const char str_802C1A5C[52] = "\x83W\x83\x87\x83" "C\x83\x93\x83g\x82\xcc\x83" "f\x81[\x83^\x82\xcc\x8ew\x92\xe8\x82\xc9\x82\xa8\x82\xa9\x82\xb5\x82\xc8\x82\xe0\x82\xcc\x82\xaa\x82\xa0\x82\xe9\n\0\0\0\0";
__declspec(section ".sdata2") const u32 dat_80419800 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_80419804 = 0xFF000000;
__declspec(section ".sdata2") const u32 dat_80419808 = 0xFF000000;
__declspec(section ".sdata2") const u32 dat_8041980c = 0xFFFF0000;
__declspec(section ".sdata2") const u32 dat_80419810 = 0xFFFF0000;
__declspec(section ".sdata2") const u32 dat_80419814 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_80419818 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041981c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419820 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419824 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419828 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041982c = 0x707070FF;
__declspec(section ".sdata2") const u32 dat_80419830 = 0x707070FF;
__declspec(section ".sdata2") const u32 dat_80419834 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419838 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041983c = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_80419840 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419844 = 0xFFFFFFFF;
__declspec(section ".sdata2") const char str_80419848[4] = ".\0\0";
__declspec(section ".sdata2") const f32 float_3_8041984c = 3.0f;
__declspec(section ".sdata2") const f32 float_0_80419850 = 0.0f;
__declspec(section ".sdata2") const f32 float_0p5_80419854 = 0.5f;
__declspec(section ".sdata2") const f32 float_2_80419858 = 2.0f;
__declspec(section ".sdata2") const f32 float_0p0001_8041985c = 0.0001f;
__declspec(section ".sdata2") const f32 float_1_80419860 = 1.0f;
__declspec(section ".sdata2") const f32 float_10_80419864 = 10.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_80419868 = 0.017453292f;
__declspec(section ".sdata2") const char str_8041986C[4] = "|\0\0";
__declspec(section ".sdata2") const f32 float_neg1p0486E06_80419870 = -1048576.0f;
__declspec(section ".sdata2") const f32 float_1000_80419874 = 1000.0f;
__declspec(section ".sdata2") const f32 float_6p2832_80419878 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_360_8041987c = 360.0f;
__declspec(section ".sdata2") const f32 float_127_80419880 = 127.0f;
__declspec(section ".sdata2") const f32 float_100_80419884 = 100.0f;
__declspec(section ".sdata2") const f32 float_neg100_80419888 = -100.0f;
__declspec(section ".sdata2") const f32 float_1p5708_8041988c = 1.5707964f;
__declspec(section ".sdata2") const f32 float_20_80419890 = 20.0f;
__declspec(section ".sdata2") const f32 float_64_80419894 = 64.0f;
__declspec(section ".sdata2") const f32 float_30_80419898 = 30.0f;
__declspec(section ".sdata2") const f32 float_128_8041989c = 128.0f;
__declspec(section ".sdata2") const f32 float_neg2_804198a0 = -2.0f;
__declspec(section ".sdata2") const f32 float_50_804198a4 = 50.0f;
__declspec(section ".sdata2") const f32 float_neg1_804198a8 = -1.0f;
__declspec(section ".sdata2") const f32 float_5000_804198ac = 5000.0f;
__declspec(section ".sdata2") const f32 float_10000_804198b0 = 10000.0f;
__declspec(section ".sdata2") const f32 float_0p01_804198b4 = 0.01f;
__declspec(section ".sdata2") const f32 float_1Eneg08_804198b8 = 0.00000001f;
__declspec(section ".sdata2") const char str_804198BC[4] = "_v\0";
__declspec(section ".sdata2") const char str_804198C0[8] = "_v_x\0\0\0";
__declspec(section ".sdata2") const f32 float_255_804198c8 = 255.0f;
__declspec(section ".sdata2") const f32 float_0_804198cc = 0.0f;
__declspec(section ".sdata2") const char str_804198D0[8] = "%s/%s\0\0";
__declspec(section ".sdata2") const f32 float_20000_804198d8 = 20000.0f;
__declspec(section ".sdata2") const u32 gap_09_804198DC_sdata2 = 0x00000000;
#endif

#ifdef NONMATCHING
// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_05_80303450_data[4] = {0};
#pragma force_active reset

#endif

#ifdef NONMATCHING // all-C link: pool objects the C names, defined on the asm side only
__declspec(section ".data") const GXCullMode culling[4] = { (GXCullMode)0x00000001, (GXCullMode)0x00000002, (GXCullMode)0x00000003, (GXCullMode)0x00000000 };
__declspec(section ".sdata2") const char mapEmptyStr[4] = "";  // the old FAKE names (target .sdata2 0xCC/0xD0/0xD8) the NM C uses
__declspec(section ".data") const char mapPathFmt[8] = "%s/%s";
__declspec(section ".sdata2") const f32 mapF20000 = 20000.0f;
#endif
