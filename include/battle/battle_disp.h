// Declares the battle drawing helpers.
#pragma once

#include <dolphin/mtx.h>
#include "battle/battle_unit.h"
#include "driver/camdrv.h"

void btlDispGXInit2DRasta(void);
void btlDispGXInit2D(void);
void btlDispChangePeraAnime(BattleUnitPart* part, const char* name);
void btlDispGXPoint2DRasta(f32 x, f32 y, u8 r, u8 g, u8 b, u8 a);
void btlDispGXQuads2DRasta(f32 x0, f32 y0, f32 x1, f32 y1, u8 r, u8 g, u8 b, u8 a);
void btlDispGXPoint2D(f32 x, f32 y, u8 r, u8 g, u8 b, u8 a, f32 s, f32 t);
void btlDispGXQuads2D(f32 x0, f32 y0, f32 x1, f32 y1, u8 r, u8 g, u8 b, u8 a);
void btlDispTexPlane(u32 id, GXColor color, s32 unused, f32 tX, f32 tY, f32 tZ, f32 sX, f32 sY);
void btlDispTexPlane2(Mtx mtx, u32 id, GXColor color, s32 unused);
void btlDispTexPlane3(Mtx mtx, u32 id, GXColor color0, GXColor color1, GXColor color2, GXColor color3, s32 unused);
void btlDispInit(void);
// The pose type for the unit's current status: the first status in _status_pose_table it has (status ids double
// as pose types), or BTL_POSE_NORMAL when none applies.
BattlePoseType _GetStatusPoseType(BattleUnit* unit);

void btlDispMain(void);

void btlDispEntAnime(BattleUnit* unit);

void btlDispTex4(u32 id, Vec pos, Vec scale, Vec rot, GXColor color);
void btlUnitPartsDisp(CameraId camId, BattleUnitPart* param);
void btlDispPoseAnime(BattleUnitPart* part);
void btlGetScreenPoint(Vec* in, Vec* out);
void btlDispChangeAnime(BattleUnitPart* part, const char* name, BOOL flag);
