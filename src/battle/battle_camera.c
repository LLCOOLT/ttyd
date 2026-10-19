// FAKE: whole unit as G5 asm stopgap (force_active + fixbase); C under #ifdef NONMATCHING.
#include "battle/battle_camera.h"
#include "battle/battle.h"
#include "battle/battle_audience.h"
#include "battle/battle_sub.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "manager/evtmgr_cmd.h"
#include "system.h"
#include <string.h>
#ifndef NONMATCHING
#include "mario/mario_pouch.h"
__declspec(section ".rodata") extern const f32 vec3_802efc40[3];
__declspec(section ".rodata") extern const f32 vec3_802efc4c[3];
__declspec(section ".rodata") extern const f32 vec3_802efc58[3];
__declspec(section ".rodata") extern const f32 vec3_802efc64[3];
__declspec(section ".rodata") extern const f32 vec3_802efc70[3];
__declspec(section ".rodata") extern const f32 vec3_802efc7c[3];
__declspec(section ".rodata") extern const f32 vec3_802efc88[3];
__declspec(section ".rodata") extern const f32 vec3_802efc94[3];
__declspec(section ".rodata") extern const f32 vec3_802efca0[3];
__declspec(section ".rodata") extern const f64 double_to_int_802efcb0;
__declspec(section ".rodata") extern const char str_802EFCB8[];
__declspec(section ".rodata") extern const char str_802EFCCC[];
__declspec(section ".rodata") extern const char str_802EFCE8[];
__declspec(section ".rodata") extern const char str_802EFD04[];
__declspec(section ".rodata") extern const char str_802EFD14[];
__declspec(section ".rodata") extern const char str_802EFD28[];
__declspec(section ".rodata") extern const char str_802EFD40[];
__declspec(section ".rodata") extern const char str_802EFD54[];
__declspec(section ".rodata") extern const u32 gap_04_802EFD6C_rodata;
__declspec(section ".rodata") extern const f64 double_20_802efd70;
__declspec(section ".rodata") extern const f64 double_1_802efd78;
__declspec(section ".rodata") extern const char str_802EFD80[];
__declspec(section ".rodata") extern const char str_802EFDA0[];
__declspec(section ".rodata") extern const char str_802EFDB8[];
__declspec(section ".rodata") extern const char str_802EFDD4[];
__declspec(section ".rodata") extern const char str_802EFDF0[];
__declspec(section ".rodata") extern const char str_802EFE18[];
__declspec(section ".rodata") extern const char str_802EFE34[];
__declspec(section ".rodata") extern const char str_802EFE4C[];
__declspec(section ".rodata") extern const char str_802EFE64[];
__declspec(section ".rodata") extern const char str_802EFE78[];
__declspec(section ".rodata") extern const char str_802EFE8C[];
__declspec(section ".rodata") extern const char str_802EFEA0[];
__declspec(section ".rodata") extern const u32 gap_04_802EFEB4_rodata;
__declspec(section ".sdata2") extern const f32 float_2_8041c450;
__declspec(section ".sdata2") extern const f32 float_0_8041c454;
__declspec(section ".sdata2") extern const f32 float_0p25_8041c458;
__declspec(section ".sdata2") extern const f32 float_600_8041c45c;
__declspec(section ".sdata2") extern const f32 float_0p5_8041c460;
__declspec(section ".sdata2") extern const f32 float_100_8041c464;
__declspec(section ".sdata2") extern const f32 float_neg100_8041c468;
__declspec(section ".sdata2") extern const f32 float_1p5_8041c46c;
__declspec(section ".sdata2") extern const f32 float_1_8041c470;
__declspec(section ".sdata2") extern const f32 float_15_8041c474;
__declspec(section ".sdata2") extern const f32 float_5_8041c478;
__declspec(section ".sdata2") extern const f32 float_200_8041c47c;
__declspec(section ".sdata2") extern const f32 float_110_8041c480;
__declspec(section ".sdata2") extern const f32 float_750_8041c484;
__declspec(section ".sdata2") extern const f32 float_60_8041c488;
__declspec(section ".sdata2") extern const f32 float_160_8041c48c;
__declspec(section ".sdata2") extern const f32 float_neg750_8041c490;
__declspec(section ".sdata2") extern const f32 float_400_8041c494;
__declspec(section ".sdata2") extern const f32 float_neg617_8041c498;
__declspec(section ".sdata2") extern const f32 float_830_8041c49c;
__declspec(section ".sdata2") extern const f32 float_920_8041c4a0;
__declspec(section ".sdata2") extern const f32 float_1000_8041c4a4;
__declspec(section ".sdata2") extern const f32 float_50_8041c4a8;
__declspec(section ".sdata2") extern const f32 float_24_8041c4ac;
__declspec(section ".sdata2") extern const f32 float_9_8041c4b0;
__declspec(section ".sdata2") extern const f32 float_80_8041c4b4;
__declspec(section ".sdata2") extern const f32 float_10_8041c4b8;
__declspec(section ".sdata2") extern const f32 float_1Eneg05_8041c4bc;
__declspec(section ".sdata2") extern const f32 float_neg30_8041c4c0;
__declspec(section ".sdata2") extern const f32 float_125_8041c4c4;
__declspec(section ".sdata2") extern const f32 float_500_8041c4c8;
__declspec(section ".sdata2") extern const f32 float_20_8041c4cc;
__declspec(section ".sdata2") extern const f32 float_350_8041c4d0;
#define EXT_LIT(sym, val) (sym)

#endif

extern BattleWork *_battleWorkPointer;
double sqrt(double);
#pragma dont_inline on
#pragma optimize_for_size on
#pragma fp_contract on

void btl_camera_nomove_x_onoff(s32 pri, s32 on);
void btl_camera_nomove_y_onoff(s32 pri, s32 on);
void btl_camera_nomove_z_onoff(s32 pri, s32 on);
f32 battleCameraGetPosMoveSpeed(void);
void btl_camera_set_mode(s32 pri, s32 mode);
void btl_camera_set_moveto(s32 pri, f32 x, f32 y, f32 z, f32 atX, f32 atY, f32 atZ, s32 frames, s32 type);
void battleCameraMoveTo(s32 mode, s32 clamp, f32 x, f32 y, f32 z, f32 atX, f32 atY, f32 atZ, f32* dX, f32* dY, f32* dZ, f32* dAtX, f32* dAtY, f32* dAtZ);

// this file uses -O4,s
#ifdef NONMATCHING
void battleCameraInit(void) {
  BattleWork *wp = _battleWorkPointer;
  BattleCameraWork *camera;
#endif
#ifndef NONMATCHING
void *memset(void *dest, int ch, size_t count);
char *strcpy(char *dest, const char *src);
void btl_camera_add_zoom(s32 pri, f32 zoom);
void btl_camera_set_zoom(s32 pri, f32 zoom);
void btl_camera_shake_h(s32 pri, f32 a, f32 b, s32 frames, s32 type);
void btl_camera_shake_w(s32 pri, f32 a, f32 b, s32 frames, s32 type);
void battleCameraInit(void);
#endif

#ifdef NONMATCHING
  camera = &wp->cameraWork;
  memset(camera, 0, sizeof(BattleCameraWork));
  camera->flags = 0;
  switch (wp->fbatInfo->partyId) {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
    camera->mode = 15;
    break;
  case 9:
    camera->mode = 16;
    break;
  case 0:
    camera->mode = 14;
    break;
  }
  camera->priLimit = 0;
  camera->zoom = 0.0f;
  camera->moveSpeedLv = 1;
  camera->zoomSpeedLv = 1;
  camera->position = (Vec){0.0f, 0.0f, 0.0f};
  camera->unk4 = 0;
}

void battleCameraMain(void) {
  CameraEntry* cam = camGetPtr(4);
  BattleWork* wp = _battleWorkPointer;
  BattleAudience* aud = BattleAudienceBaseGetPtr();
  f32 zoomZ = 0.0f;
  BattleUnit* mario;
  char name[64];
  Vec pos;
  Vec hit;
  f32 dX, dY, dZ, dAtX, dAtY, dAtZ;
  f32 mx, my, mz;
  f32 px, py, pz;
  BattleUnit* unit2;
  BattleUnitPart* part;
  BattleUnit* party;
  BattleUnitPart* part2;
  BattleUnit* unit;
  f32 w, w2, zz, y, ofs, t, d, yy, atX, atY, atZ;
  s16 moveLv, zoomLv;
  s32 phase;
  s16 moveLv2, zoomLv2;
  s32 phase2;
  s16 moveLv3;

  BattleGetMarioPtr(wp);
  dX = 0.0f;
  dY = 0.0f;
  dZ = 0.0f;
  dAtX = 0.0f;
  dAtY = 0.0f;
  dAtZ = 0.0f;
  if (wp->cameraWork.mode != 3) {
    wp->cameraWork.moveToTimer = 0;
  }
  cam->cameraPos.x = wp->cameraWork.pos.x;
  cam->cameraPos.y = wp->cameraWork.pos.y;
  cam->cameraPos.z = wp->cameraWork.pos.z;
  cam->cameraAt.x = wp->cameraWork.at.x;
  cam->cameraAt.y = wp->cameraWork.at.y;
  cam->cameraAt.z = wp->cameraWork.at.z;
  wp->cameraWork.prevPos.x = cam->cameraPos.x;
  wp->cameraWork.prevPos.y = cam->cameraPos.y;
  wp->cameraWork.prevPos.z = cam->cameraPos.z;
  wp->cameraWork.prevAt.x = cam->cameraAt.x;
  wp->cameraWork.prevAt.y = cam->cameraAt.y;
  wp->cameraWork.prevAt.z = cam->cameraAt.z;
  switch (wp->cameraWork.mode) {
  case 0:
    battleCameraMoveTo(1, 1, 0.0f, 110.0f, 750.0f, 0.0f, 60.0f, 0.0f, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    strcpy(name, "\202\251\202\337\202\347\201\100\202\305\202\323\202\247\202\351\202\306");
    break;
  case 1:
    zz = 0.5f * wp->cameraWork.zoom;
    battleCameraMoveTo(1, 1, 0.0f, 110.0f, 750.0f - zz, 0.0f, 60.0f, -zz, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    strcpy(name, "\202\251\202\337\202\347\201\100\202\305\202\323\202\247\202\351\202\306\203\131\201\133\203\200");
    break;
  case 2:
    battleCameraMoveTo(1, 1, 0.0f, 160.0f, 750.0f, 0.0f, 110.0f, 0.0f, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    strcpy(name, "\202\251\202\337\202\347\201\100\202\251\201\133\202\273\202\351\202\252\202\244\202\246\202\311");
  case 3:
    if (wp->cameraWork.moveToTimer > 0) {
      moveLv3 = wp->cameraWork.moveSpeedLv;
      wp->cameraWork.moveToTimer--;
      pos.x = intplGetValue(wp->cameraWork.moveToType, wp->cameraWork.moveToFrames - wp->cameraWork.moveToTimer, wp->cameraWork.moveToFrames, wp->cameraWork.moveToStartPos.x, wp->cameraWork.moveToEndPos.x);
      pos.y = intplGetValue(wp->cameraWork.moveToType, wp->cameraWork.moveToFrames - wp->cameraWork.moveToTimer, wp->cameraWork.moveToFrames, wp->cameraWork.moveToStartPos.y, wp->cameraWork.moveToEndPos.y);
      pos.z = intplGetValue(wp->cameraWork.moveToType, wp->cameraWork.moveToFrames - wp->cameraWork.moveToTimer, wp->cameraWork.moveToFrames, wp->cameraWork.moveToStartPos.z, wp->cameraWork.moveToEndPos.z);
      atX = intplGetValue(wp->cameraWork.moveToType, wp->cameraWork.moveToFrames - wp->cameraWork.moveToTimer, wp->cameraWork.moveToFrames, wp->cameraWork.moveToStartAt.x, wp->cameraWork.moveToEndAt.x);
      atY = intplGetValue(wp->cameraWork.moveToType, wp->cameraWork.moveToFrames - wp->cameraWork.moveToTimer, wp->cameraWork.moveToFrames, wp->cameraWork.moveToStartAt.y, wp->cameraWork.moveToEndAt.y);
      atZ = intplGetValue(wp->cameraWork.moveToType, wp->cameraWork.moveToFrames - wp->cameraWork.moveToTimer, wp->cameraWork.moveToFrames, wp->cameraWork.moveToStartAt.z, wp->cameraWork.moveToEndAt.z);
      wp->cameraWork.moveSpeedLv = 3;
      wp->cameraWork.zoomSpeedLv = 3;
      battleCameraMoveTo(0, 0, pos.x, pos.y, pos.z, atX, atY, atZ, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
      wp->cameraWork.moveSpeedLv = moveLv3;
    }
    strcpy(name, "\202\251\202\337\202\347\201\100\202\323\202\350\201\133");
    break;
  case 4:
    battleCameraMoveTo(1, 1, 0.0f, 110.0f, -750.0f, 0.0f, 60.0f, 0.0f, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    strcpy(name, "\202\251\202\337\202\347\201\100\202\324\202\275\202\242\202\244\202\347");
    break;
  case 5:
    battleCameraMoveTo(1, 1, 0.0f, 400.0f, -617.0f, 0.0f, 60.0f, 0.0f, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    strcpy(name, "\202\251\202\337\202\347\201\100\202\324\202\275\202\242\202\244\202\347\202\121");
    break;
  case 6:
    switch (pouchGetPtr()->rank) {
    case 0:
      zoomZ = 750.0f;
      break;
    case 1:
      zoomZ = 830.0f;
      break;
    case 2:
      zoomZ = 920.0f;
      break;
    case 3:
      zoomZ = 1000.0f;
      break;
    }
    battleCameraMoveTo(1, 1, 0.0f, 110.0f, zoomZ, 0.0f, 60.0f, 0.0f, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    strcpy(name, "\202\251\202\337\202\347\201\100\202\251\202\361\202\253\202\341\202\255");
    break;
  case 7:
    unit2 = BattleGetUnitPtr(wp, wp->cameraWork.unitId);
    if (unit2 == NULL) {
      btl_camera_set_mode(0, 0);
      break;
    }
    BattleGetUnitPartsPtr(wp->cameraWork.unitId, wp->cameraWork.partsId);
    BtlUnit_GetPos(unit2, &pos.x, &pos.y, &pos.z);
    ofs = (BtlUnit_GetHeight(unit2) - 50.0f) / 2.0f;
    pos.y += ofs;
    w = BtlUnit_GetWidth(unit2) - 24.0f;
    if (w < 0.0f) {
      w = 0.0f;
    }
    zz = wp->cameraWork.zoom;
    zz -= 1.5f * w;
    ofs = -zz / 9.0f;
    t = pos.y;
    y = t;
    if (t > 100.0f) {
      t = 100.0f;
    }
    if (y < 0.0f) {
      t = 0.0f;
    }
    battleCameraMoveTo(1, 1, pos.x, 110.0f + t + ofs, 750.0f - zz, pos.x, 60.0f + t + ofs, -zz, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    strcpy(name, "\202\251\202\337\202\347\201\100\202\344\202\311\202\301\202\306\202\302\202\242\202\321");
    break;
  case 8: {f32 w, w2, d, ofs, t, zz, yy, atX, y;
    unit = BattleGetUnitPtr(wp, wp->cameraWork.unitId);
    unit2 = BattleGetUnitPtr(wp, wp->cameraWork.unitId2);
    if (unit == NULL || unit2 == NULL) {
      btl_camera_set_mode(0, 0);
      break;
    }
    BattleGetUnitPartsPtr(wp->cameraWork.unitId, wp->cameraWork.partsId);
    part2 = BattleGetUnitPartsPtr(wp->cameraWork.unitId2, wp->cameraWork.partsId2);
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    BtlUnit_GetHitPos(unit2, part2, &hit.x, &hit.y, &hit.z);
    w = BtlUnit_GetWidth(unit) - 24.0f;
    w2 = BtlUnit_GetWidth(unit2) - 24.0f;
    if (w < 0.0f) {
      w = 0.0f;
    }
    if (w2 < 0.0f) {
      w2 = 0.0f;
    }
    d = wp->cameraWork.homingOffset2.x - wp->cameraWork.homingOffset.x;
    yy = hit.x - pos.x;
    if (d == 0.0f) {
      t = 0.5f;
    } else {
      t = yy / d;
    }
    if (t > 1.0f) {
      t = 1.0f;
    }
    if (t < 0.5f) {
      t = 0.5f;
    }
    zz = 2.0f * wp->cameraWork.zoom;
    w2 = w + w2;
    yy = (wp->cameraWork.homingOffset2.y / 80.0f) * (pos.y - wp->cameraWork.homingOffset2.y);
    atX = (1.0f - t) * wp->cameraWork.homingOffset2.x;
    zz = (1.0f - t) * (zz - 1.5f * w2);
    ofs = -zz / 10.0f;
    if (yy > 100.0f) {
      yy = 100.0f;
    }
    if (yy < 0.0f) {
      yy = 0.0f;
    }
    y = 20.0 * -(1.0 - t) + yy;
    battleCameraMoveTo(1, 1, atX, 110.0f + y + ofs, 750.0f - zz, atX, 60.0f + y + ofs, -zz, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    strcpy(name, "\202\251\202\337\202\347\201\100\202\121\202\344\202\311\202\301\202\306\202\251\202\361\202\302\202\242\202\321");
    break;
  }
  case 9:
    unit = BattleGetUnitPtr(wp, wp->cameraWork.unitId);
    party = BattleGetUnitPtr(wp, wp->cameraWork.unitId2);
    if (unit == NULL || party == NULL) {
      btl_camera_set_mode(0, 0);
      break;
    }
    BattleGetUnitPartsPtr(wp->cameraWork.unitId, wp->cameraWork.partsId);
    part = BattleGetUnitPartsPtr(wp->cameraWork.unitId2, wp->cameraWork.partsId2);
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    BtlUnit_GetHitPos(party, part, &hit.x, &hit.y, &hit.z);
    w = BtlUnit_GetWidth(unit) - 24.0f;
    BtlUnit_GetWidth(party);
    if (w < 0.0f) {
      w = 0.0f;
    }
    zz = 2.0f * wp->cameraWork.zoom;
    zz -= 1.5f * w;
    yy = 0.5f * (pos.y + hit.y);
    ofs = -zz / 10.0f;
    if (yy > 50.0f) {
      atX = 50.0f;
    }
    if (yy < 0.0f) {
      atX = 0.0f;
    }
    atY = 0.5f * (pos.x + hit.x);
    battleCameraMoveTo(1, 1, atY, 110.0f + atX + ofs, 750.0f - zz, atY, 60.0f + atX + ofs, -zz, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    strcpy(name, "\202\251\202\337\202\347\201\100\202\344\202\311\202\301\202\306\202\302\202\242\202\321");
    break;
  case 10:
    unit = BattleGetUnitPtr(wp, wp->cameraWork.unitId);
    if (unit == NULL) {
      btl_camera_set_mode(0, 0);
      break;
    }
    part = BattleGetUnitPartsPtr(wp->cameraWork.unitId, wp->cameraWork.partsId);
    if (part == NULL) {
      btl_camera_set_mode(0, 0);
      break;
    }
    BtlUnit_GetHitPos(unit, part, &pos.x, &pos.y, &pos.z);
    ofs = (BtlUnit_GetHeight(unit) - 50.0f) / 2.0f;
    pos.y += ofs;
    w = BtlUnit_GetWidth(unit) - 24.0f;
    if (w < 0.0f) {
      w = 0.0f;
    }
    zz = wp->cameraWork.zoom;
    zz -= 1.5f * w;
    ofs = -zz / 9.0f;
    y = pos.y;
    t = y;
    if (y > 100.0f) {
      y = 100.0f;
    }
    if (t < 0.0f) {
      y = 0.0f;
    }
    battleCameraMoveTo(1, 1, pos.x, 110.0f + y + ofs, 750.0f - zz, pos.x, 60.0f + y + ofs, -zz, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    strcpy(name, "\202\251\202\337\202\347\201\100\202\317\201\133\202\302\202\302\202\242\202\321");
    break;
  case 11: {f32 w, w2, t, zz, yy, d, ofs, y, atX;
    unit = BattleGetUnitPtr(wp, wp->cameraWork.unitId);
    unit2 = BattleGetUnitPtr(wp, wp->cameraWork.unitId2);
    if (unit == NULL || unit2 == NULL) {
      btl_camera_set_mode(0, 0);
      break;
    }
    part2 = BattleGetUnitPartsPtr(wp->cameraWork.unitId, wp->cameraWork.partsId);
    part = BattleGetUnitPartsPtr(wp->cameraWork.unitId2, wp->cameraWork.partsId2);
    if (part2 == NULL || part == NULL) {
      btl_camera_set_mode(0, 0);
      break;
    }
    BtlUnit_GetPartsWorldPos(part2, &pos.x, &pos.y, &pos.z);
    BtlUnit_GetHitPos(unit2, part, &hit.x, &hit.y, &hit.z);
    w = BtlUnit_GetWidth(unit) - 24.0f;
    w2 = BtlUnit_GetWidth(unit2) - 24.0f;
    if (w < 0.0f) {
      w = 0.0f;
    }
    if (w2 < 0.0f) {
      w2 = 0.0f;
    }
    d = wp->cameraWork.homingOffset2.x - wp->cameraWork.homingOffset.x;
    yy = hit.x - pos.x;
    if (d == 0.0f) {
      d = 1e-05f;
    }
    t = yy / d;
    if (t > 1.0f) {
      t = 1.0f;
    }
    if (t < 0.5f) {
      t = 0.5f;
    }
    zz = 2.0f * wp->cameraWork.zoom;
    w2 = w + w2;
    zz = (1.0f - t) * (zz - 1.5f * w2);
    yy = (wp->cameraWork.homingOffset2.y / 80.0f) * (pos.y - wp->cameraWork.homingOffset2.y);
    atX = (1.0f - t) * wp->cameraWork.homingOffset2.x;
    ofs = -zz / 10.0f;
    if (yy > 100.0f) {
      yy = 100.0f;
    }
    if (yy < 0.0f) {
      yy = 0.0f;
    }
    y = 20.0 * -(1.0 - t) + yy;
    battleCameraMoveTo(1, 1, atX, 110.0f + y + ofs, 750.0f - zz, atX, 60.0f + y + ofs, -zz, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    strcpy(name, "\202\251\202\337\202\347\201\100\202\121\202\317\201\133\202\302\202\251\202\361\202\302\202\242\202\321");
    break;
  }
  case 12:
    {
      BattleAudienceMember* m = &aud->members[wp->cameraWork.audienceId];
      battleCameraMoveTo(1, 0, m->position.x, 200.0f, 400.0f + m->position.z, m->position.x, 0.0f, m->position.z, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    }
    strcpy(name, "\202\251\202\337\202\347\201\100\202\251\202\361\202\253\202\341\202\255\202\302\202\242\202\321");
    break;
  case 13:
    unit = BattleGetUnitPtr(wp, wp->cameraWork.unitId);
    if (unit == NULL) {
      btl_camera_set_mode(0, 0);
      break;
    }
    if (BattleGetUnitPartsPtr(wp->cameraWork.unitId, wp->cameraWork.partsId) == NULL) {
      btl_camera_set_mode(0, 0);
      break;
    }
    wp->cameraWork.audienceId = 10;
    d = wp->cameraWork.homingOffset2.x - wp->cameraWork.homingOffset.x;
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    ofs = wp->cameraWork.homingOffset2.x - pos.x;
    if (d == 0.0f) {
      t = 0.5f;
    } else {
      t = ofs / d;
    }
    if (t > 1.0f) {
      t = 1.0f;
    }
    if (t < 0.5f) {
      t = 0.5f;
    }
    yy = pos.y - wp->cameraWork.homingOffset.y;
    zz = 2.0f * wp->cameraWork.zoom;
    atX = (1.0f - t) * wp->cameraWork.homingOffset2.x;
    yy -= 100.0f;
    if (yy > 0.0f) {
      yy = 0.0f;
    }
    if (yy < -30.0f) {
      yy = -30.0f;
    }
    zz = (1.0f - t) * zz;
    y = -(1.0 - t) * (125.0f - yy);
    battleCameraMoveTo(1, 1, atX, 110.0f + y, 750.0f - zz, atX, 60.0f + y, -zz, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    strcpy(name, "\202\251\202\337\202\347\201\100\202\344\202\311\202\301\202\306\202\251\202\361\202\253\202\341\202\255\202\251\202\361\202\302\202\242\202\321");
    break;
  case 14:
    wp->cameraWork.unk4++;
    if (wp->cameraWork.unk4 == 1) {
      switch (pouchGetPtr()->rank) {
      case 0:
        zoomZ = 750.0f;
        break;
      case 1:
        zoomZ = 830.0f;
        break;
      case 2:
        zoomZ = 920.0f;
        break;
      case 3:
        zoomZ = 1000.0f;
        break;
      }
      wp->cameraWork.moveSpeedLv = 3;
      wp->cameraWork.zoomSpeedLv = 3;
      battleCameraMoveTo(1, 1, 0.0f, 110.0f, zoomZ, 0.0f, 60.0f, 0.0f, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    }
    if (wp->cameraWork.unk4 == 10) {
      wp->cameraWork.unk4 = 0;
      btl_camera_set_mode(0, 3);
      btl_camera_set_moveto(0, 0.0f, 110.0f, 750.0f, 0.0f, 60.0f, 0.0f, 120, 4);
    }
    strcpy(name, "\202\251\202\337\202\347\201\100\202\323\202\302\202\244\202\311\202\315\202\242\202\301\202\275");
    break;
  case 15:
    wp->cameraWork.moveSpeedLv = 3;
    wp->cameraWork.zoomSpeedLv = 3;
    battleCameraMoveTo(1, 1, 0.0f, 110.0f, 500.0f, 0.0f, 60.0f, 0.0f, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    strcpy(name, "\202\251\202\337\202\347\201\100\202\244\202\334\202\255\202\315\202\242\202\301\202\275");
    break;
  case 16:
    wp->cameraWork.moveSpeedLv = 3;
    wp->cameraWork.zoomSpeedLv = 3;
    battleCameraMoveTo(1, 1, -100.0f, 110.0f, 500.0f, -100.0f, 60.0f, 0.0f, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    strcpy(name, "\202\251\202\337\202\347\201\100\202\276\202\337\202\311\202\315\202\242\202\301\202\275");
    break;
  case 17:
  case 18:
    mario = BattleGetMarioPtr(wp);
    party = BattleGetPartyPtr(wp);
    if (party != NULL) {
      BtlUnit_GetHomePos(mario, &mx, &my, &mz);
      BtlUnit_GetHomePos(party, &px, &py, &pz);
      atX = 0.5f * (mx + px);
      atY = 0.5f * (my + py);
      atZ = 0.5f * (mz + pz);
      if (wp->cameraWork.mode == 18) {
        atY -= 20.0f;
      }
    } else {
      BtlUnit_GetHomePos(mario, &mx, &my, &mz);
      atX = mx;
      atY = my;
      atZ = mz;
    }
    wp->cameraWork.moveSpeedLv = 1;
    wp->cameraWork.zoomSpeedLv = 1;
    battleCameraMoveTo(0, 1, atX, 100.0f + atY, 350.0f + atZ, atX, 50.0f + atY, 0.0f, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    strcpy(name, "\202\251\202\337\202\347\201\100\202\265\202\345\202\244\202\350");
    break;
  case 19:
    strcpy(name, "\202\251\202\337\202\347\201\100\202\315\202\242\202\332\202\255");
    break;
  case 20:
    wp->cameraWork.moveSpeedLv = 2;
    wp->cameraWork.zoomSpeedLv = 2;
    battleCameraMoveTo(1, 1, -100.0f, 100.0f, 400.0f, -100.0f, 50.0f, 0.0f, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
    strcpy(name, "\202\251\202\337\202\347\201\100\202\311\202\260\202\304\202\351");
    break;
  default:
    strcpy(name, "\202\251\202\337\202\347\201\100\202\250\202\251\202\265\202\242\0\0\0\0\0\0\0");
    break;
  }
  if (cam->cameraPos.z >= 1000.0f) {
    cam->cameraPos.z = 1000.0f;
  }
  if (wp->cameraWork.flags & 4) {
    cam->cameraPos.x = wp->cameraWork.prevPos.x;
    cam->cameraAt.x = wp->cameraWork.prevAt.x;
    dX = 0.0f;
    dAtX = 0.0f;
  }
  if (wp->cameraWork.flags & 8) {
    cam->cameraPos.y = wp->cameraWork.prevPos.y;
    cam->cameraAt.y = wp->cameraWork.prevAt.y;
    dY = 0.0f;
    dAtY = 0.0f;
  }
  if (wp->cameraWork.flags & 0x10) {
    cam->cameraPos.z = wp->cameraWork.prevPos.z;
    cam->cameraAt.z = wp->cameraWork.prevAt.z;
    dZ = 0.0f;
    dAtZ = 0.0f;
  }
  wp->cameraWork.pos.x = cam->cameraPos.x;
  wp->cameraWork.pos.y = cam->cameraPos.y;
  wp->cameraWork.pos.z = cam->cameraPos.z;
  wp->cameraWork.at.x = cam->cameraAt.x;
  wp->cameraWork.at.y = cam->cameraAt.y;
  wp->cameraWork.at.z = cam->cameraAt.z;
  wp->cameraWork.moveSpeed = (Vec){dX, dY, dZ};
  wp->cameraWork.moveSpeedAt = (Vec){dAtX, dAtY, dAtZ};
  if (!(wp->cameraWork.flags & 1) && !(wp->cameraWork.flags & 2)) {
    padRumbleOff(0);
  }
  if (wp->cameraWork.flags & 0x40) {
    padRumbleOff(0);
  }
  if (wp->cameraWork.flags & 1) {
    moveLv = wp->cameraWork.moveSpeedLv;
    zoomLv = wp->cameraWork.zoomSpeedLv;
    phase = (wp->cameraWork.shakeWFrames - wp->cameraWork.shakeWTimer) & 2;
    wp->cameraWork.moveSpeedLv = 3;
    wp->cameraWork.zoomSpeedLv = 3;
    wp->cameraWork.shakeWOfs = intplGetValue(wp->cameraWork.shakeWType, (wp->cameraWork.shakeWFrames - wp->cameraWork.shakeWTimer) / 2, wp->cameraWork.shakeWFrames / 2, wp->cameraWork.shakeWAmp[0], wp->cameraWork.shakeWAmp[1]);
    if (wp->cameraWork.shakeWTimer > 0) {
      if (phase == 0) {
        battleCameraMoveTo(0, 0, cam->cameraPos.x + wp->cameraWork.shakeWOfs, cam->cameraPos.y, cam->cameraPos.z, cam->cameraAt.x + wp->cameraWork.shakeWOfs, cam->cameraAt.y, cam->cameraAt.z, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
      } else {
        battleCameraMoveTo(0, 0, cam->cameraPos.x - wp->cameraWork.shakeWOfs, cam->cameraPos.y, cam->cameraPos.z, cam->cameraAt.x - wp->cameraWork.shakeWOfs, cam->cameraAt.y, cam->cameraAt.z, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
      }
    } else if (wp->cameraWork.shakeWTimer == 0) {
      wp->cameraWork.flags &= ~1;
    }
    wp->cameraWork.moveSpeedLv = moveLv;
    wp->cameraWork.zoomSpeedLv = zoomLv;
    wp->cameraWork.shakeWTimer--;
  }
  if (wp->cameraWork.flags & 2) {
    moveLv2 = wp->cameraWork.moveSpeedLv;
    zoomLv2 = wp->cameraWork.zoomSpeedLv;
    phase2 = (wp->cameraWork.shakeHFrames - wp->cameraWork.shakeHTimer) & 2;
    wp->cameraWork.moveSpeedLv = 3;
    wp->cameraWork.zoomSpeedLv = 3;
    wp->cameraWork.shakeHOfs = intplGetValue(wp->cameraWork.shakeHType, (wp->cameraWork.shakeHFrames - wp->cameraWork.shakeHTimer) / 2, wp->cameraWork.shakeHFrames / 2, wp->cameraWork.shakeHAmp[0], wp->cameraWork.shakeHAmp[1]);
    if (wp->cameraWork.shakeHTimer > 0) {
      if (phase2 == 0) {
        battleCameraMoveTo(0, 0, cam->cameraPos.x, cam->cameraPos.y + wp->cameraWork.shakeHOfs, cam->cameraPos.z, cam->cameraAt.x, cam->cameraAt.y + wp->cameraWork.shakeHOfs, cam->cameraAt.z, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
      } else {
        battleCameraMoveTo(0, 0, cam->cameraPos.x, cam->cameraPos.y - wp->cameraWork.shakeHOfs, cam->cameraPos.z, cam->cameraAt.x, cam->cameraAt.y - wp->cameraWork.shakeHOfs, cam->cameraAt.z, &dX, &dY, &dZ, &dAtX, &dAtY, &dAtZ);
      }
    } else if (wp->cameraWork.shakeHTimer == 0) {
      wp->cameraWork.flags &= ~2;
    }
    wp->cameraWork.moveSpeedLv = moveLv2;
    wp->cameraWork.zoomSpeedLv = zoomLv2;
    wp->cameraWork.shakeHTimer--;
  }
}
#endif
#ifndef NONMATCHING
void battleCameraMain(void);
extern void* jumptable_80362040[];
void battleCameraMain(void);
#endif

void battleCameraMoveTo(s32 mode, s32 clamp, f32 x, f32 y, f32 z, f32 atX, f32 atY, f32 atZ,
#ifdef NONMATCHING
                        f32* dX, f32* dY, f32* dZ, f32* dAtX, f32* dAtY, f32* dAtZ) {
  CameraEntry* cam = camGetPtr(4);
  BattleWork* wp = _battleWorkPointer;
  BattleUnit* mario = BattleGetMarioPtr(wp);
  f32 half;
#endif
#ifndef NONMATCHING
                        f32* dX, f32* dY, f32* dZ, f32* dAtX, f32* dAtY, f32* dAtZ);
#endif

#ifdef NONMATCHING
  if (wp->cameraWork.moveSpeedLv < 0 || wp->cameraWork.moveSpeedLv >= 5) {
    wp->cameraWork.moveSpeedLv = 1;
  }
  if (wp->cameraWork.zoomSpeedLv < 0 || wp->cameraWork.zoomSpeedLv >= 6) {
    wp->cameraWork.zoomSpeedLv = 1;
  }
  if (mode == 1) {
    if (wp->flags & 0x100) {
      f32 mz = mario->mHomePosition.z;
      f32 ox = 0.0f;
      f32 oy = 0.25f * -mz;
      f32 oz = mz;
      x += ox;
      y += oy;
      z += oz;
      atX += ox;
      atY += oy;
      atZ += oz;
    }
    x += wp->cameraWork.position.x;
    y += wp->cameraWork.position.y;
    z += wp->cameraWork.position.z;
    atX += wp->cameraWork.position.x;
    atY += wp->cameraWork.position.y;
    atZ += wp->cameraWork.position.z;
  }
  half = (600.0f - z) / 2.0f;
  if (half < 0.0f) {
    half = 0.0f;
  }
  if (clamp == 1) {
    if (x > 100.0f + half) {
      x = 100.0f + half;
    }
    if (x < -100.0f - half) {
      x = -100.0f - half;
    }
    if (atX > 100.0f + half) {
      atX = 100.0f + half;
    }
    if (atX < -100.0f - half) {
      atX = -100.0f - half;
    }
  }
  switch (wp->cameraWork.moveSpeedLv) {
  case 0:
    *dX = (x - cam->cameraPos.x) / 1.5f;
    *dY = (y - cam->cameraPos.y) / 1.5f;
    *dAtX = (atX - cam->cameraAt.x) / 1.5f;
    *dAtY = (atY - cam->cameraAt.y) / 1.5f;
    cam->cameraPos.x += *dX;
    cam->cameraPos.y += *dY;
    cam->cameraAt.x += *dAtX;
    cam->cameraAt.y += *dAtY;
    cam->cameraUp.x = 0.0f;
    cam->cameraUp.y = 1.0f;
    cam->cameraUp.z = 0.0f;
    break;
  case 1:
    *dX = (x - cam->cameraPos.x) / 15.0f;
    *dY = (y - cam->cameraPos.y) / 15.0f;
    *dAtX = (atX - cam->cameraAt.x) / 15.0f;
    *dAtY = (atY - cam->cameraAt.y) / 15.0f;
    cam->cameraPos.x += *dX;
    cam->cameraPos.y += *dY;
    cam->cameraPos.z += *dZ;
    cam->cameraAt.x += *dAtX;
    cam->cameraAt.y += *dAtY;
    cam->cameraUp.x = 0.0f;
    cam->cameraUp.y = 1.0f;
    cam->cameraUp.z = 0.0f;
    break;
  case 2:
    *dX = (x - cam->cameraPos.x) / 5.0f;
    *dY = (y - cam->cameraPos.y) / 5.0f;
    *dAtX = (atX - cam->cameraAt.x) / 5.0f;
    *dAtY = (atY - cam->cameraAt.y) / 5.0f;
    cam->cameraPos.x += *dX;
    cam->cameraPos.y += *dY;
    cam->cameraAt.x += *dAtX;
    cam->cameraAt.y += *dAtY;
    cam->cameraUp.x = 0.0f;
    cam->cameraUp.y = 1.0f;
    cam->cameraUp.z = 0.0f;
    break;
  case 3:
    *dX = x - cam->cameraPos.x;
    *dY = y - cam->cameraPos.y;
    *dAtX = atX - cam->cameraAt.x;
    *dAtY = atY - cam->cameraAt.y;
    cam->cameraPos.x += *dX;
    cam->cameraPos.y += *dY;
    cam->cameraAt.x += *dAtX;
    cam->cameraAt.y += *dAtY;
    cam->cameraUp.x = 0.0f;
    cam->cameraUp.y = 1.0f;
    cam->cameraUp.z = 0.0f;
    break;
  case 4:
    *dX = (x - cam->cameraPos.x) / 200.0f;
    *dY = (y - cam->cameraPos.y) / 200.0f;
    *dAtX = (atX - cam->cameraAt.x) / 200.0f;
    *dAtY = (atY - cam->cameraAt.y) / 200.0f;
    cam->cameraPos.x += *dX;
    cam->cameraPos.y += *dY;
    cam->cameraAt.x += *dAtX;
    cam->cameraAt.y += *dAtY;
    cam->cameraUp.x = 0.0f;
    cam->cameraUp.y = 1.0f;
    cam->cameraUp.z = 0.0f;
    break;
  case 5:
    *dX = (x - cam->cameraPos.x) / 100.0f;
    *dY = (y - cam->cameraPos.y) / 100.0f;
    *dAtX = (atX - cam->cameraAt.x) / 100.0f;
    *dAtY = (atY - cam->cameraAt.y) / 100.0f;
    cam->cameraPos.x += *dX;
    cam->cameraPos.y += *dY;
    cam->cameraAt.x += *dAtX;
    cam->cameraAt.y += *dAtY;
    cam->cameraUp.x = 0.0f;
    cam->cameraUp.y = 1.0f;
    cam->cameraUp.z = 0.0f;
    break;
  }
  switch (wp->cameraWork.zoomSpeedLv) {
  case 0:
    *dZ = (z - cam->cameraPos.z) / 1.5f;
    *dAtZ = (atZ - cam->cameraAt.z) / 1.5f;
    cam->cameraPos.z += *dZ;
    cam->cameraAt.z += *dAtZ;
    break;
  case 1:
    *dZ = (z - cam->cameraPos.z) / 15.0f;
    *dAtZ = (atZ - cam->cameraAt.z) / 15.0f;
    cam->cameraPos.z += *dZ;
    cam->cameraAt.z += *dAtZ;
    break;
  case 2:
    *dZ = (z - cam->cameraPos.z) / 5.0f;
    *dAtZ = (atZ - cam->cameraAt.z) / 5.0f;
    cam->cameraPos.z += *dZ;
    cam->cameraAt.z += *dAtZ;
    break;
  case 3:
    *dZ = z - cam->cameraPos.z;
    *dAtZ = atZ - cam->cameraAt.z;
    cam->cameraPos.z += *dZ;
    cam->cameraAt.z += *dAtZ;
    break;
  case 4:
    *dZ = (z - cam->cameraPos.z) / 200.0f;
    *dAtZ = (atZ - cam->cameraAt.z) / 200.0f;
    cam->cameraPos.z += *dZ;
    cam->cameraAt.z += *dAtZ;
    break;
  case 5:
    *dZ = (z - cam->cameraPos.z) / 100.0f;
    *dAtZ = (atZ - cam->cameraAt.z) / 100.0f;
    cam->cameraPos.z += *dZ;
    cam->cameraAt.z += *dAtZ;
    break;
  }
}
#endif
#ifndef NONMATCHING
f32 battleCameraGetPosMoveSpeed(void);
#endif

#ifdef NONMATCHING
f32 battleCameraGetPosMoveSpeed(void) {
  BattleWork* wp = _battleWorkPointer;
  f32 x = wp->cameraWork.moveSpeed.x;
  f32 y = wp->cameraWork.moveSpeed.y;
  f32 z = wp->cameraWork.moveSpeed.z;
  return sqrt(x * x + y * y + z * z);
}
#endif
#ifndef NONMATCHING
void btl_camera_set_prilimit(s32 pri);
#endif

#ifdef NONMATCHING
void btl_camera_set_prilimit(s32 pri) {
  _battleWorkPointer->cameraWork.priLimit = pri;
}
#endif
#ifndef NONMATCHING
s32 evt_btl_camera_set_prilimit(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_set_prilimit) {
  btl_camera_set_prilimit(evtGetValue(event, event->args[0]));
  return 2;
}
#endif
#ifndef NONMATCHING
void btl_camera_set_mode(s32 pri, s32 mode);
#endif

#ifdef NONMATCHING
void btl_camera_set_mode(s32 pri, s32 mode) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    wp->cameraWork.mode = mode;
    wp->cameraWork.zoom = 0.0f;
    wp->cameraWork.moveSpeedLv = 1;
    wp->cameraWork.zoomSpeedLv = 1;
    wp->cameraWork.unk4 = 0;
    btl_camera_nomove_x_onoff(0, 0);
    btl_camera_nomove_y_onoff(0, 0);
    btl_camera_nomove_z_onoff(0, 0);
    wp->cameraWork.flags &= ~0x20;
  }
}
#endif
#ifndef NONMATCHING
s32 evt_btl_camera_set_mode(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_set_mode) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  s32 val = evtGetValue(event, args[1]);
  btl_camera_set_mode(pri, val);
  return 2;
}
#endif
#ifndef NONMATCHING
s32 evt_btl_camera_set_homing_unit(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_set_homing_unit) {
  BattleWork* wp;
  BattleUnit* u;
  BattleUnit* u2;
  s32* args = event->args;
  s32 unit;
  s32 unit2;
  BattleUnitPart* part;
  Vec pos;
  Vec hit;

  evtGetValue(event, args[0]);
  unit = evtGetValue(event, args[1]);
  unit2 = evtGetValue(event, args[2]);
  wp = _battleWorkPointer;
  wp->cameraWork.unitId = BattleTransID(event, unit);
  u = BattleGetUnitPtr(wp, wp->cameraWork.unitId);
  wp->cameraWork.partsId = BtlUnit_GetBodyPartsId(u);
  BattleGetUnitPartsPtr(wp->cameraWork.unitId, wp->cameraWork.partsId);
  BtlUnit_GetHomePos(u, &pos.x, &pos.y, &pos.z);
  wp->cameraWork.homingOffset = (Vec){pos.x, pos.y, pos.z};
  if (unit2 != -1) {
    wp->cameraWork.unitId2 = BattleTransID(event, unit2);
    u2 = BattleGetUnitPtr(wp, wp->cameraWork.unitId2);
    wp->cameraWork.partsId2 = BtlUnit_GetBodyPartsId(u2);
    part = BattleGetUnitPartsPtr(wp->cameraWork.unitId2, wp->cameraWork.partsId2);
    BtlUnit_GetHitPos(u2, part, &hit.x, &hit.y, &hit.z);
    wp->cameraWork.homingOffset2 = (Vec){hit.x, hit.y, hit.z};
  }
  return 2;
}

USER_FUNC(evt_btl_camera_set_homing_unitparts) {
  s32* args = event->args;
  BattleWork* wp;
  BattleUnit* u;
  s32 unit, parts, unit2, parts2;
  BattleUnitPart* part;
  Vec pos;
  Vec hit;

  /* pri shares a register with u in the original */
  u = (BattleUnit*)evtGetValue(event, args[0]);
  unit = evtGetValue(event, args[1]);
  parts = evtGetValue(event, args[2]);
  unit2 = evtGetValue(event, args[3]);
  parts2 = evtGetValue(event, args[4]);
  if ((s32)u < (wp = _battleWorkPointer)->cameraWork.priLimit) {
    return 2;
  }
  wp->cameraWork.unitId = BattleTransID(event, unit);
  wp->cameraWork.partsId = parts;
  u = BattleGetUnitPtr(wp, wp->cameraWork.unitId);
  BattleGetUnitPartsPtr(wp->cameraWork.unitId, wp->cameraWork.partsId);
  BtlUnit_GetHomePos(u, &pos.x, &pos.y, &pos.z);
  wp->cameraWork.homingOffset = (Vec){pos.x, pos.y, pos.z};
  if (unit2 != -1) {
    wp->cameraWork.unitId2 = BattleTransID(event, unit2);
    wp->cameraWork.partsId2 = parts2;
    u = BattleGetUnitPtr(wp, wp->cameraWork.unitId2);
    part = BattleGetUnitPartsPtr(wp->cameraWork.unitId2, wp->cameraWork.partsId2);
    BtlUnit_GetHitPos(u, part, &hit.x, &hit.y, &hit.z);
    wp->cameraWork.homingOffset2 = (Vec){hit.x, hit.y, hit.z};
  }
  return 2;
}
#endif
#ifndef NONMATCHING
s32 evt_btl_camera_set_homing_unitparts(EventEntry* event, BOOL isFirstCall);
#endif


#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_set_homing_unit_audience) {
  s32 audId;
  BattleWork* wp;
  BattleAudience* aud;
  s32* args = event->args;
  s32 pri, unit, parts;
  BattleUnit* u;
  BattleUnitPart* part;
  Vec pos;
  Vec hit;
#endif
#ifndef NONMATCHING
s32 evt_btl_camera_set_homing_unit_audience(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
  pri = evtGetValue(event, args[0]);
  unit = evtGetValue(event, args[1]);
  parts = evtGetValue(event, args[2]);
  audId = evtGetValue(event, args[3]);
  wp = _battleWorkPointer;
  aud = BattleAudienceBaseGetPtr();
  if (pri < wp->cameraWork.priLimit) {
    return 2;
  }
  wp->cameraWork.unitId = BattleTransID(event, unit);
  wp->cameraWork.partsId = parts;
  u = BattleGetUnitPtr(wp, wp->cameraWork.unitId);
  part = BattleGetUnitPartsPtr(wp->cameraWork.unitId, wp->cameraWork.partsId);
  BtlUnit_GetPos(u, &pos.x, &pos.y, &pos.z);
  BtlUnit_GetHitPos(u, part, &hit.x, &hit.y, &hit.z);
  wp->cameraWork.homingOffset = (Vec){pos.x, pos.y, pos.z};
  wp->cameraWork.audienceId = audId;
  {
    BattleAudienceMember* m = &aud->members[audId];
    wp->cameraWork.homingOffset2 = (Vec){m->position.x, m->position.y, m->position.z};
  }
  return 2;
#endif
#ifndef NONMATCHING
void btl_camera_set_zoom(s32 pri, f32 zoom);

void btl_camera_add_zoom(s32 pri, f32 zoom);

s32 evt_btl_camera_set_zoom(EventEntry* event, BOOL isFirstCall);

s32 evt_btl_camera_add_zoom(EventEntry* event, BOOL isFirstCall);

void btl_camera_set_moveSpeedLv(s32 pri, s32 lv);

void btl_camera_set_zoomSpeedLv(s32 pri, s32 lv);

s32 evt_btl_camera_set_moveSpeedLv(EventEntry* event, BOOL isFirstCall);

s32 evt_btl_camera_set_zoomSpeedLv(EventEntry* event, BOOL isFirstCall);

void btl_camera_set_moveto(s32 pri, f32 x, f32 y, f32 z, f32 atX, f32 atY, f32 atZ, s32 frames,
                           s32 type);

s32 evt_btl_camera_set_moveto(EventEntry* event, BOOL isFirstCall);

void btl_camera_shake_w(s32 pri, f32 a, f32 b, s32 frames, s32 type);

s32 evt_btl_camera_shake_w(EventEntry* event, BOOL isFirstCall);

void btl_camera_shake_h(s32 pri, f32 a, f32 b, s32 frames, s32 type);

s32 evt_btl_camera_shake_h(EventEntry* event, BOOL isFirstCall);

void btl_camera_noshake(s32 pri);

s32 evt_btl_camera_noshake(EventEntry* event, BOOL isFirstCall);

void btl_camera_nomove_x_onoff(s32 pri, s32 on);

s32 evt_btl_camera_nomove_x_onoff(EventEntry* event, BOOL isFirstCall);

void btl_camera_nomove_y_onoff(s32 pri, s32 on);

s32 evt_btl_camera_nomove_y_onoff(EventEntry* event, BOOL isFirstCall);

void btl_camera_nomove_z_onoff(s32 pri, s32 on);

s32 evt_btl_camera_nomove_z_onoff(EventEntry* event, BOOL isFirstCall);

void btl_camera_set_posoffset(s32 pri, f32 x, f32 y, f32 z);

s32 evt_btl_camera_set_posoffset(EventEntry* event, BOOL isFirstCall);

void btl_camera_off_posoffset_manual(s32 pri);

s32 evt_btl_camera_off_posoffset_manual(EventEntry* event, BOOL isFirstCall);

s32 evt_btl_camera_wait_move_end(EventEntry* event, BOOL isFirstCall);



// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 evt_btl_camera_set_homing_unitparts(EventEntry* event, BOOL isFirstCall) {
	char _af_pad[52];
	asm volatile {
		opword 0x7C7D1B78
		opword 0x83830018
		opword 0x809C0000
		bl evtGetValue
		opword 0x809C0004
		opword 0x7C7A1B78
		opword 0x7FA3EB78
		bl evtGetValue
		opword 0x809C0008
		mr r25, r3
		opword 0x7FA3EB78
		bl evtGetValue
		opword 0x809C000C
		opword 0x7C7B1B78
		opword 0x7FA3EB78
		bl evtGetValue
		opword 0x809C0010
		opword 0x7C7E1B78
		opword 0x7FA3EB78
		bl evtGetValue
		lwz r31, _battleWorkPointer(r13)
		opword 0x7C7C1B78
		opword 0x801F275C
		opword 0x7C1A0000
		opword 0x4080000C
		opword 0x38600002
		opword 0x4800013C
		opword 0x7FA3EB78
		opword 0x7F24CB78
		bl BattleTransID
		opword 0x907F2764
		opword 0x7FE3FB78
		opword 0x937F276C
		opword 0x809F2764
		bl BattleGetUnitPtr
		opword 0x7C7A1B78
		opword 0x807F2764
		opword 0x809F276C
		bl BattleGetUnitPartsPtr
		la r5, _af_pad+40
		opword 0x38C10034
		opword 0x7F43D378
		opword 0x3881002C
		bl BtlUnit_GetHomePos
		lis r3, vec3_802efc7c@ha
		opword 0xC041002C
		addi r4, r3, vec3_802efc7c@l
		opword 0xC0210030
		opword 0x80040000
		opword 0x2C1EFFFF
		opword 0x80640004
		opword 0x90010014
		opword 0x80040008
		opword 0x90610018
		opword 0xC0010034
		opword 0xD0410014
		opword 0x9001001C
		opword 0x80010014
		opword 0xD0210018
		opword 0xD001001C
		opword 0x80610018
		opword 0x901F2810
		opword 0x8001001C
		opword 0x907F2814
		opword 0x901F2818
		opword 0x4182009C
		opword 0x7FA3EB78
		opword 0x7FC4F378
		bl BattleTransID
		opword 0x907F2768
		opword 0x7FE3FB78
		opword 0x939F2770
		opword 0x809F2768
		bl BattleGetUnitPtr
		opword 0x7C7A1B78
		opword 0x807F2768
		opword 0x809F2770
		bl BattleGetUnitPartsPtr
		opword 0x7C641B78
		opword 0x38C10024
		opword 0x38E10028
		opword 0x7F43D378
		opword 0x38A10020
		bl BtlUnit_GetHitPos
		lis r3, vec3_802efc88@ha
		opword 0xC0410020
		addi r4, r3, vec3_802efc88@l
		opword 0xC0210024
		opword 0x80040000
		opword 0x80640004
		opword 0x90010008
		opword 0x80040008
		opword 0x9061000C
		opword 0xC0010028
		opword 0xD0410008
		opword 0x90010010
		opword 0x80010008
		opword 0xD021000C
		opword 0xD0010010
		opword 0x8061000C
		opword 0x901F281C
		opword 0x80010010
		opword 0x907F2820
		opword 0x901F2824
		opword 0x38600002
	}
#endif
}
#ifndef NONMATCHING
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 evt_btl_camera_set_homing_unit_audience(EventEntry* event, BOOL isFirstCall) {
	char _af_pad[52];
	asm volatile {
		mr r25, r3
		opword 0x83830018
		opword 0x809C0000
		bl evtGetValue
		opword 0x809C0004
		opword 0x7C7B1B78
		opword 0x7F23CB78
		bl evtGetValue
		opword 0x809C0008
		opword 0x7C7A1B78
		opword 0x7F23CB78
		bl evtGetValue
		opword 0x809C000C
		opword 0x7C7C1B78
		opword 0x7F23CB78
		bl evtGetValue
		lwz r30, _battleWorkPointer(r13)
		opword 0x7C7F1B78
		bl BattleAudienceBaseGetPtr
		opword 0x801E275C
		opword 0x7C7D1B78
		opword 0x7C1B0000
		opword 0x4080000C
		opword 0x38600002
		opword 0x48000120
		opword 0x7F23CB78
		opword 0x7F44D378
		bl BattleTransID
		opword 0x907E2764
		opword 0x7FC3F378
		opword 0x939E276C
		opword 0x809E2764
		bl BattleGetUnitPtr
		opword 0x7C601B78
		opword 0x807E2764
		opword 0x809E276C
		opword 0x7C1A0378
		bl BattleGetUnitPartsPtr
		opword 0x7C601B78
		la r5, _af_pad+40
		opword 0x38C10034
		opword 0x7F43D378
		opword 0x7C1B0378
		opword 0x3881002C
		bl BtlUnit_GetPos
		opword 0x7F43D378
		opword 0x7F64DB78
		opword 0x38A10020
		opword 0x38C10024
		opword 0x38E10028
		bl BtlUnit_GetHitPos
		lis r4, vec3_802efc94@ha
		lis r3, vec3_802efca0@ha
		addi r7, r4, vec3_802efc94@l
		opword 0xC001002C
		opword 0x80070000
		opword 0x1C9F0134
		opword 0x80A70004
		addi r6, r3, vec3_802efca0@l
		opword 0x90010014
		opword 0x38600002
		opword 0x80070008
		opword 0xD0010014
		opword 0x38E401BC
		opword 0xC0210030
		opword 0x7CFD3A14
		opword 0x90A10018
		opword 0xC0010034
		opword 0x9001001C
		opword 0x80010014
		opword 0xD0210018
		opword 0xD001001C
		opword 0x80810018
		opword 0x901E2810
		opword 0x8001001C
		opword 0x909E2814
		opword 0x901E2818
		opword 0x93FE2774
		opword 0x80A60000
		opword 0x80860004
		opword 0x80060008
		opword 0x90A10008
		opword 0xC0070048
		opword 0x9081000C
		opword 0xC027004C
		opword 0xD0010008
		opword 0xC0070050
		opword 0x90010010
		opword 0x80010008
		opword 0xD021000C
		opword 0xD0010010
		opword 0x8081000C
		opword 0x901E281C
		opword 0x80010010
		opword 0x909E2820
		opword 0x901E2824
	}
}
#pragma pop
#endif

void btl_camera_set_zoom(s32 pri, f32 zoom) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    wp->cameraWork.zoom = zoom;
  }
}

void btl_camera_add_zoom(s32 pri, f32 zoom) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    wp->cameraWork.zoom += zoom;
  }
}

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_set_zoom) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  btl_camera_set_zoom(pri, (s32)evtGetFloat(event, args[1]));
  return 2;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 evt_btl_camera_set_zoom(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0xBFC10018
		opword 0x7C7E1B78
		opword 0x83E30018
		opword 0x809F0000
		bl evtGetValue
		opword 0x809F0004
		opword 0x7C7F1B78
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFC00081E
		opword 0x3C004330
		lis r3, double_to_int_802efcb0@ha
		opword 0x90010010
		addi r4, r3, double_to_int_802efcb0@l
		opword 0xD8010008
		opword 0xC8240000
		opword 0x7FE3FB78
		opword 0x8001000C
		opword 0x6C008000
		opword 0x90010014
		opword 0xC8010010
		opword 0xEC200828
		bl btl_camera_set_zoom
		opword 0xBBC10018
		opword 0x38600002
		opword 0x80010024
		opword 0x7C0803A6
		opword 0x38210020
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_add_zoom) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  btl_camera_add_zoom(pri, (s32)evtGetFloat(event, args[1]));
  return 2;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 evt_btl_camera_add_zoom(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0xBFC10018
		opword 0x7C7E1B78
		opword 0x83E30018
		opword 0x809F0000
		bl evtGetValue
		opword 0x809F0004
		opword 0x7C7F1B78
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFC00081E
		opword 0x3C004330
		lis r3, double_to_int_802efcb0@ha
		opword 0x90010010
		addi r4, r3, double_to_int_802efcb0@l
		opword 0xD8010008
		opword 0xC8240000
		opword 0x7FE3FB78
		opword 0x8001000C
		opword 0x6C008000
		opword 0x90010014
		opword 0xC8010010
		opword 0xEC200828
		bl btl_camera_add_zoom
		opword 0xBBC10018
		opword 0x38600002
		opword 0x80010024
		opword 0x7C0803A6
		opword 0x38210020
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void btl_camera_set_moveSpeedLv(s32 pri, s32 lv) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    if (lv >= 0 && lv <= 5) {
      wp->cameraWork.moveSpeedLv = lv;
    } else {
      wp->cameraWork.moveSpeedLv = 1;
    }
    wp->cameraWork.zoomSpeedLv = wp->cameraWork.moveSpeedLv;
  }
}

void btl_camera_set_zoomSpeedLv(s32 pri, s32 lv) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    if (lv >= 0 && lv <= 5) {
      wp->cameraWork.zoomSpeedLv = lv;
    } else {
      wp->cameraWork.zoomSpeedLv = 1;
    }
  }
}

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_set_moveSpeedLv) {
#endif
#ifndef NONMATCHING
#pragma dont_inline on
s32 evt_btl_camera_set_moveSpeedLv(EventEntry* event, BOOL isFirstCall) {
#endif
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  s32 val = evtGetValue(event, args[1]);
  btl_camera_set_moveSpeedLv(pri, val);
  return 2;
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_set_zoomSpeedLv) {
#endif
#ifndef NONMATCHING
#pragma dont_inline on
s32 evt_btl_camera_set_zoomSpeedLv(EventEntry* event, BOOL isFirstCall) {
#endif
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  s32 val = evtGetValue(event, args[1]);
  btl_camera_set_zoomSpeedLv(pri, val);
  return 2;
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

void btl_camera_set_moveto(s32 pri, f32 x, f32 y, f32 z, f32 atX, f32 atY, f32 atZ, s32 frames,
                           s32 type) {
  BattleWork* wp = _battleWorkPointer;
  CameraEntry* cam = camGetPtr(4);
  if (pri >= wp->cameraWork.priLimit) {
    wp->cameraWork.moveToStartPos.x = cam->cameraPos.x;
    wp->cameraWork.moveToStartPos.y = cam->cameraPos.y;
    wp->cameraWork.moveToStartPos.z = cam->cameraPos.z;
    wp->cameraWork.moveToEndPos.x = x;
    wp->cameraWork.moveToEndPos.y = y;
    wp->cameraWork.moveToEndPos.z = z;
    wp->cameraWork.moveToStartAt.x = cam->cameraAt.x;
    wp->cameraWork.moveToStartAt.y = cam->cameraAt.y;
    wp->cameraWork.moveToStartAt.z = cam->cameraAt.z;
    wp->cameraWork.moveToEndAt.x = atX;
    wp->cameraWork.moveToEndAt.y = atY;
    wp->cameraWork.moveToEndAt.z = atZ;
    wp->cameraWork.moveToTimer = frames;
    wp->cameraWork.moveToFrames = frames;
    wp->cameraWork.moveToType = type;
  }
}

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_set_moveto) {
#endif
#ifndef NONMATCHING
#pragma dont_inline on
s32 evt_btl_camera_set_moveto(EventEntry* event, BOOL isFirstCall) {
#endif
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  f32 x = evtGetFloat(event, args[1]);
  f32 y = evtGetFloat(event, args[2]);
  f32 z = evtGetFloat(event, args[3]);
  f32 atX = evtGetFloat(event, args[4]);
  f32 atY = evtGetFloat(event, args[5]);
  f32 atZ = evtGetFloat(event, args[6]);
  s32 frames = evtGetValue(event, args[7]);
  btl_camera_set_moveto(pri, x, y, z, atX, atY, atZ, frames, evtGetValue(event, args[8]));
  return 2;
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

void btl_camera_shake_w(s32 pri, f32 a, f32 b, s32 frames, s32 type) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    wp->cameraWork.flags |= 1;
    wp->cameraWork.shakeWAmp[0] = a;
    wp->cameraWork.shakeWAmp[1] = b;
    wp->cameraWork.shakeWType = type;
    wp->cameraWork.shakeWFrames = frames;
    wp->cameraWork.shakeWTimer = frames;
    if (!(wp->cameraWork.flags & 0x40)) {
      padRumbleOn(0);
    }
  }
}

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_shake_w) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  f32 a = evtGetValue(event, args[1]);
  f32 b = evtGetValue(event, args[2]);
  s32 frames = evtGetValue(event, args[3]);
  btl_camera_shake_w(pri, a, b, frames, evtGetValue(event, args[4]));
  return 2;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 evt_btl_camera_shake_w(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFB0
		opword 0x7C0802A6
		opword 0x90010054
		opword 0xDBE10040
		opword 0xF3E10048
		opword 0xDBC10030
		opword 0xF3C10038
		opword 0xBFA10024
		opword 0x7C7D1B78
		opword 0x83E30018
		opword 0x809F0000
		bl evtGetValue
		opword 0x809F0004
		opword 0x7C7E1B78
		opword 0x7FA3EB78
		bl evtGetValue
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_802efcb0@ha
		opword 0x9061000C
		addi r5, r4, double_to_int_802efcb0@l
		opword 0x809F0008
		opword 0x90010008
		opword 0x7FA3EB78
		opword 0xC8250000
		opword 0xC8010008
		opword 0xEFE00828
		bl evtGetValue
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_802efcb0@ha
		opword 0x90610014
		addi r5, r4, double_to_int_802efcb0@l
		opword 0x809F000C
		opword 0x90010010
		opword 0x7FA3EB78
		opword 0xC8250000
		opword 0xC8010010
		opword 0xEFC00828
		bl evtGetValue
		opword 0x809F0010
		opword 0x7C7F1B78
		opword 0x7FA3EB78
		bl evtGetValue
		opword 0xFC20F890
		opword 0x7C651B78
		opword 0xFC40F090
		opword 0x7FC3F378
		opword 0x7FE4FB78
		bl btl_camera_shake_w
		opword 0x38600002
		opword 0xE3E10048
		opword 0xCBE10040
		opword 0xE3C10038
		opword 0xCBC10030
		opword 0xBBA10024
		opword 0x80010054
		opword 0x7C0803A6
		opword 0x38210050
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void btl_camera_shake_h(s32 pri, f32 a, f32 b, s32 frames, s32 type) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    wp->cameraWork.flags |= 2;
    wp->cameraWork.shakeHAmp[0] = a;
    wp->cameraWork.shakeHAmp[1] = b;
    wp->cameraWork.shakeHType = type;
    wp->cameraWork.shakeHFrames = frames;
    wp->cameraWork.shakeHTimer = frames;
    if (!(wp->cameraWork.flags & 0x40)) {
      padRumbleOn(0);
    }
  }
}

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_shake_h) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  f32 a = evtGetValue(event, args[1]);
  f32 b = evtGetValue(event, args[2]);
  s32 frames = evtGetValue(event, args[3]);
  btl_camera_shake_h(pri, a, b, frames, evtGetValue(event, args[4]));
  return 2;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 evt_btl_camera_shake_h(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFB0
		opword 0x7C0802A6
		opword 0x90010054
		opword 0xDBE10040
		opword 0xF3E10048
		opword 0xDBC10030
		opword 0xF3C10038
		opword 0xBFA10024
		opword 0x7C7D1B78
		opword 0x83E30018
		opword 0x809F0000
		bl evtGetValue
		opword 0x809F0004
		opword 0x7C7E1B78
		opword 0x7FA3EB78
		bl evtGetValue
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_802efcb0@ha
		opword 0x9061000C
		addi r5, r4, double_to_int_802efcb0@l
		opword 0x809F0008
		opword 0x90010008
		opword 0x7FA3EB78
		opword 0xC8250000
		opword 0xC8010008
		opword 0xEFE00828
		bl evtGetValue
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_802efcb0@ha
		opword 0x90610014
		addi r5, r4, double_to_int_802efcb0@l
		opword 0x809F000C
		opword 0x90010010
		opword 0x7FA3EB78
		opword 0xC8250000
		opword 0xC8010010
		opword 0xEFC00828
		bl evtGetValue
		opword 0x809F0010
		opword 0x7C7F1B78
		opword 0x7FA3EB78
		bl evtGetValue
		opword 0xFC20F890
		opword 0x7C651B78
		opword 0xFC40F090
		opword 0x7FC3F378
		opword 0x7FE4FB78
		bl btl_camera_shake_h
		opword 0x38600002
		opword 0xE3E10048
		opword 0xCBE10040
		opword 0xE3C10038
		opword 0xCBC10030
		opword 0xBBA10024
		opword 0x80010054
		opword 0x7C0803A6
		opword 0x38210050
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void btl_camera_noshake(s32 pri) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    wp->cameraWork.flags &= ~1;
    wp->cameraWork.flags &= ~2;
  }
}

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_noshake) {
#endif
#ifndef NONMATCHING
#pragma dont_inline on
s32 evt_btl_camera_noshake(EventEntry* event, BOOL isFirstCall) {
#endif
  btl_camera_noshake(evtGetValue(event, event->args[0]));
  return 2;
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

void btl_camera_nomove_x_onoff(s32 pri, s32 on) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    if (on == 1) {
      wp->cameraWork.flags |= 4;
    } else {
      wp->cameraWork.flags &= ~4;
    }
  }
}

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_nomove_x_onoff) {
#endif
#ifndef NONMATCHING
#pragma dont_inline on
s32 evt_btl_camera_nomove_x_onoff(EventEntry* event, BOOL isFirstCall) {
#endif
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  s32 val = evtGetValue(event, args[1]);
  btl_camera_nomove_x_onoff(pri, val);
  return 2;
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

void btl_camera_nomove_y_onoff(s32 pri, s32 on) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    if (on == 1) {
      wp->cameraWork.flags |= 8;
    } else {
      wp->cameraWork.flags &= ~8;
    }
  }
}

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_nomove_y_onoff) {
#endif
#ifndef NONMATCHING
#pragma dont_inline on
s32 evt_btl_camera_nomove_y_onoff(EventEntry* event, BOOL isFirstCall) {
#endif
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  s32 val = evtGetValue(event, args[1]);
  btl_camera_nomove_y_onoff(pri, val);
  return 2;
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

void btl_camera_nomove_z_onoff(s32 pri, s32 on) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    if (on == 1) {
      wp->cameraWork.flags |= 0x10;
    } else {
      wp->cameraWork.flags &= ~0x10;
    }
  }
}

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_nomove_z_onoff) {
#endif
#ifndef NONMATCHING
#pragma dont_inline on
s32 evt_btl_camera_nomove_z_onoff(EventEntry* event, BOOL isFirstCall) {
#endif
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  s32 val = evtGetValue(event, args[1]);
  btl_camera_nomove_z_onoff(pri, val);
  return 2;
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

void btl_camera_set_posoffset(s32 pri, f32 x, f32 y, f32 z) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    wp->cameraWork.flags |= 0x20;
    wp->cameraWork.position.x = x;
    wp->cameraWork.position.y = y;
    wp->cameraWork.position.z = z;
  }
}

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_set_posoffset) {
#endif
#ifndef NONMATCHING
#pragma dont_inline on
s32 evt_btl_camera_set_posoffset(EventEntry* event, BOOL isFirstCall) {
#endif
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  f32 x = evtGetFloat(event, args[1]);
  f32 y = evtGetFloat(event, args[2]);
  f32 z = evtGetFloat(event, args[3]);
  btl_camera_set_posoffset(pri, x, y, z);
  return 2;
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

void btl_camera_off_posoffset_manual(s32 pri) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    wp->cameraWork.flags &= ~0x20;
#ifdef NONMATCHING
    wp->cameraWork.position.x = 0.0f;
    wp->cameraWork.position.y = 0.0f;
    wp->cameraWork.position.z = 0.0f;
#endif
#ifndef NONMATCHING
    wp->cameraWork.position.x = EXT_LIT(float_0_8041c454, 0.0f);
    wp->cameraWork.position.y = EXT_LIT(float_0_8041c454, 0.0f);
    wp->cameraWork.position.z = EXT_LIT(float_0_8041c454, 0.0f);
#endif
  }
}

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_off_posoffset_manual) {
#endif
#ifndef NONMATCHING
#pragma dont_inline on
s32 evt_btl_camera_off_posoffset_manual(EventEntry* event, BOOL isFirstCall) {
#endif
  btl_camera_off_posoffset_manual(evtGetValue(event, event->args[0]));
  return 2;
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_wait_move_end) {
  if (battleCameraGetPosMoveSpeed() >= 2.0f) {
    return 0;
  }
#endif
#ifndef NONMATCHING
#pragma defer_codegen off
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 evt_btl_camera_wait_move_end(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		bl battleCameraGetPosMoveSpeed
		lfs f0, float_2_8041c450(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000008
		opword 0x38600002
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop

#pragma defer_codegen reset

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
asm s32 evt_btl_camera_set_homing_unit(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stmw r28, 0x40(r1)
	mr r30, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x8(r29)
	mr r29, r3
	mr r3, r30
	bl evtGetValue
	lwz r31, _battleWorkPointer(r13)
	mr r28, r3
	mr r3, r30
	mr r4, r29
	bl BattleTransID
	stw r3, 0x2764(r31)
	mr r3, r31
	lwz r4, 0x2764(r31)
	bl BattleGetUnitPtr
	mr r29, r3
	bl BtlUnit_GetBodyPartsId
	stw r3, 0x276c(r31)
	lwz r3, 0x2764(r31)
	lwz r4, 0x276c(r31)
	bl BattleGetUnitPartsPtr
	addi r5, r1, 0x30
	addi r6, r1, 0x34
	mr r3, r29
	addi r4, r1, 0x2c
	bl BtlUnit_GetHomePos
	lis r3, vec3_802efc64@ha
	lfs f2, 0x2c(r1)
	addi r4, r3, vec3_802efc64@l
	lfs f1, 0x30(r1)
	lwz r0, 0x0(r4)
	cmpwi r28, -0x1
	lwz r3, 0x4(r4)
	stw r0, 0x14(r1)
	lwz r0, 0x8(r4)
	stw r3, 0x18(r1)
	lfs f0, 0x34(r1)
	stfs f2, 0x14(r1)
	stw r0, 0x1c(r1)
	lwz r0, 0x14(r1)
	stfs f1, 0x18(r1)
	stfs f0, 0x1c(r1)
	lwz r3, 0x18(r1)
	stw r0, 0x2810(r31)
	lwz r0, 0x1c(r1)
	stw r3, 0x2814(r31)
	stw r0, 0x2818(r31)
	beq L_af_1
	mr r3, r30
	mr r4, r28
	bl BattleTransID
	stw r3, 0x2768(r31)
	mr r3, r31
	lwz r4, 0x2768(r31)
	bl BattleGetUnitPtr
	mr r29, r3
	bl BtlUnit_GetBodyPartsId
	stw r3, 0x2770(r31)
	lwz r3, 0x2768(r31)
	lwz r4, 0x2770(r31)
	bl BattleGetUnitPartsPtr
	mr r4, r3
	addi r6, r1, 0x24
	addi r7, r1, 0x28
	mr r3, r29
	addi r5, r1, 0x20
	bl BtlUnit_GetHitPos
	lis r3, vec3_802efc70@ha
	lfs f2, 0x20(r1)
	addi r4, r3, vec3_802efc70@l
	lfs f1, 0x24(r1)
	lwz r0, 0x0(r4)
	lwz r3, 0x4(r4)
	stw r0, 0x8(r1)
	lwz r0, 0x8(r4)
	stw r3, 0xc(r1)
	lfs f0, 0x28(r1)
	stfs f2, 0x8(r1)
	stw r0, 0x10(r1)
	lwz r0, 0x8(r1)
	stfs f1, 0xc(r1)
	stfs f0, 0x10(r1)
	lwz r3, 0xc(r1)
	stw r0, 0x281c(r31)
	lwz r0, 0x10(r1)
	stw r3, 0x2820(r31)
	stw r0, 0x2824(r31)
L_af_1:
	lmw r28, 0x40(r1)
	li r3, 0x2
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void battleCameraInit(void) {
	asm {
		li r4, 0x0
		li r5, 0x104
	}
	asm volatile {
		lwz r31, _battleWorkPointer(r13)
		addi r30, r31, 0x2754
		opword 0x7FC3F378
		bl memset
		opword 0x38000000
		opword 0x901E0000
		opword 0x807F2738
		opword 0x80030008
		opword 0x2C000009
		opword 0x41820024
		opword 0x40800034
		opword 0x2C000000
		opword 0x41820024
		opword 0x40800008
		opword 0x48000024
		opword 0x3800000F
		opword 0x901E000C
		opword 0x48000018
		opword 0x38000010
		opword 0x901E000C
		opword 0x4800000C
		opword 0x3800000E
		opword 0x901E000C
		opword 0x38A00000
		lis r3, vec3_802efc40@ha
		opword 0x90BE0008
		opword 0x38000001
		lfs f0, float_0_8041c454(r2)
		addi r4, r3, vec3_802efc40@l
		opword 0xD01E0024
		opword 0xB01E0028
		opword 0xB01E002A
		opword 0x80640000
		opword 0x80040004
		opword 0x907E005C
		opword 0x901E0060
		opword 0x80040008
		opword 0x901E0064
		opword 0x90BE0004
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void battleCameraMain(void) {
	char _af_pad[180];
	asm volatile {
		lis r4, vec3_802efc40@ha
		opword 0x38600004
		addi r29, r4, vec3_802efc40@l
		bl camGetPtr
		lwz r31, _battleWorkPointer(r13)
		opword 0x7C7E1B78
		bl BattleAudienceBaseGetPtr
		lfs f30, float_0_8041c454(r2)
		opword 0x7C7C1B78
		opword 0x7FE3FB78
		bl BattleGetMarioPtr
		lfs f0, float_0_8041c454(r2)
		stfs f0, _af_pad+44(r1)
		opword 0xD0010030
		opword 0xD001002C
		opword 0xD0010028
		opword 0xD0010024
		opword 0xD0010020
		opword 0x801F2760
		opword 0x2C000003
		opword 0x4182000C
		opword 0x38000000
		opword 0x901F27D8
		opword 0xC01F2780
		opword 0xD01E000C
		opword 0xC01F2784
		opword 0xD01E0010
		opword 0xC01F2788
		opword 0xD01E0014
		opword 0xC01F2798
		opword 0xD01E0018
		opword 0xC01F279C
		opword 0xD01E001C
		opword 0xC01F27A0
		opword 0xD01E0020
		opword 0xC01E000C
		opword 0xD01F278C
		opword 0xC01E0010
		opword 0xD01F2790
		opword 0xC01E0014
		opword 0xD01F2794
		opword 0xC01E0018
		opword 0xD01F27A4
		opword 0xC01E001C
		opword 0xD01F27A8
		opword 0xC01E0020
		opword 0xD01F27AC
		opword 0x801F2760
		opword 0x28000014
		opword 0x41811144
		lis r3, jumptable_80362040@ha
		opword 0x5400103A
		addi r3, r3, jumptable_80362040@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		lfs f1, float_0_8041c454(r2)
		opword 0x38A10034
		lfs f2, float_110_8041c480(r2)
		opword 0x38C10030
		opword 0xFC800890
		lfs f3, float_750_8041c484(r2)
		opword 0xFCC00890
		lfs f5, float_60_8041c488(r2)
		opword 0x38E1002C
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600001
		opword 0x38800001
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D0078
		bl strcpy
		opword 0x480010EC
		lfs f2, float_0p5_8041c460(r2)
		opword 0x38A10034
		opword 0xC01F2778
		opword 0x38C10030
		lfs f1, float_0_8041c454(r2)
		opword 0x38E1002C
		opword 0xECC20032
		lfs f0, float_750_8041c484(r2)
		opword 0xFC800890
		lfs f2, float_110_8041c480(r2)
		lfs f5, float_60_8041c488(r2)
		opword 0x39010028
		opword 0xEC603028
		opword 0x39210024
		opword 0xFCC03050
		opword 0x39410020
		opword 0x38600001
		opword 0x38800001
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D008C
		bl strcpy
		opword 0x48001090
		lfs f1, float_0_8041c454(r2)
		opword 0x38A10034
		lfs f2, float_160_8041c48c(r2)
		opword 0x38C10030
		opword 0xFC800890
		lfs f3, float_750_8041c484(r2)
		opword 0xFCC00890
		lfs f5, float_110_8041c480(r2)
		opword 0x38E1002C
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600001
		opword 0x38800001
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D00A8
		bl strcpy
		opword 0x807F27D8
		opword 0x2C030000
		opword 0x40810118
		opword 0xAB9F277C
		opword 0x3803FFFF
		opword 0x901F27D8
		opword 0x80BF27DC
		opword 0x801F27D8
		opword 0x807F27D4
		opword 0xC03F27E0
		opword 0x7C802850
		opword 0xC05F27EC
		bl intplGetValue
		opword 0xD021005C
		opword 0x80BF27DC
		opword 0x801F27D8
		opword 0x807F27D4
		opword 0xC03F27E4
		opword 0x7C802850
		opword 0xC05F27F0
		bl intplGetValue
		opword 0xD0210060
		opword 0x80BF27DC
		opword 0x801F27D8
		opword 0x807F27D4
		opword 0xC03F27E8
		opword 0x7C802850
		opword 0xC05F27F4
		bl intplGetValue
		opword 0xD0210064
		opword 0x80BF27DC
		opword 0x801F27D8
		opword 0x807F27D4
		opword 0xC03F27F8
		opword 0x7C802850
		opword 0xC05F2804
		bl intplGetValue
		opword 0xFFE00890
		opword 0x80BF27DC
		opword 0x801F27D8
		opword 0x807F27D4
		opword 0xC03F27FC
		opword 0x7C802850
		opword 0xC05F2808
		bl intplGetValue
		opword 0xFFC00890
		opword 0x80BF27DC
		opword 0x801F27D8
		opword 0x807F27D4
		opword 0xC03F2800
		opword 0x7C802850
		opword 0xC05F280C
		bl intplGetValue
		opword 0x38000003
		opword 0xFC80F890
		opword 0xB01F277C
		opword 0xFCA0F090
		opword 0xFCC00890
		opword 0x38A10034
		opword 0xB01F277E
		opword 0x38C10030
		opword 0x38E1002C
		opword 0xC021005C
		opword 0xC0410060
		opword 0x39010028
		opword 0xC0610064
		opword 0x39210024
		opword 0x39410020
		opword 0x38600000
		opword 0x38800000
		bl battleCameraMoveTo
		opword 0xB39F277C
		opword 0x38610068
		opword 0x389D00C4
		bl strcpy
		opword 0x48000F18
		lfs f1, float_0_8041c454(r2)
		opword 0x38A10034
		lfs f2, float_110_8041c480(r2)
		opword 0x38C10030
		opword 0xFC800890
		lfs f3, float_neg750_8041c490(r2)
		opword 0xFCC00890
		lfs f5, float_60_8041c488(r2)
		opword 0x38E1002C
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600001
		opword 0x38800001
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D00D4
		bl strcpy
		opword 0x48000ECC
		lfs f1, float_0_8041c454(r2)
		opword 0x38A10034
		lfs f2, float_400_8041c494(r2)
		opword 0x38C10030
		opword 0xFC800890
		lfs f3, float_neg617_8041c498(r2)
		opword 0xFCC00890
		lfs f5, float_60_8041c488(r2)
		opword 0x38E1002C
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600001
		opword 0x38800001
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D00E8
		bl strcpy
		opword 0x48000E80
		bl pouchGetPtr
		opword 0xA8030088
		opword 0x2C000002
		opword 0x41820034
		opword 0x40800014
		opword 0x2C000000
		opword 0x41820018
		opword 0x4080001C
		opword 0x4800002C
		opword 0x2C000004
		opword 0x40800024
		opword 0x4800001C
		lfs f30, float_750_8041c484(r2)
		opword 0x48000018
		lfs f30, float_830_8041c49c(r2)
		opword 0x48000010
		lfs f30, float_920_8041c4a0(r2)
		opword 0x48000008
		lfs f30, float_1000_8041c4a4(r2)
		lfs f1, float_0_8041c454(r2)
		opword 0xFC60F090
		lfs f2, float_110_8041c480(r2)
		opword 0x38A10034
		opword 0xFC800890
		lfs f5, float_60_8041c488(r2)
		opword 0xFCC00890
		opword 0x38C10030
		opword 0x38E1002C
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600001
		opword 0x38800001
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D0100
		bl strcpy
		opword 0x48000DE8
		opword 0x809F2764
		opword 0x7FE3FB78
		bl BattleGetUnitPtr
		opword 0x7C7C1B79
		opword 0x40820014
		opword 0x38600000
		opword 0x38800000
		bl btl_camera_set_mode
		opword 0x48000DC4
		opword 0x807F2764
		opword 0x809F276C
		bl BattleGetUnitPartsPtr
		opword 0x38A10060
		opword 0x7F83E378
		opword 0x3881005C
		opword 0x38C10064
		bl BtlUnit_GetPos
		opword 0x7F83E378
		bl BtlUnit_GetHeight
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		opword 0x7F83E378
		opword 0xC87D0070
		opword 0x900100A8
		lfs f2, float_50_8041c4a8(r2)
		opword 0xC80100A8
		lfs f1, float_0p5_8041c460(r2)
		opword 0xEC601828
		opword 0xC0010060
		opword 0xEC431028
		opword 0xEC220072
		opword 0xEC00082A
		opword 0xD0010060
		bl BtlUnit_GetWidth
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		opword 0xC87D0070
		opword 0x900100B0
		lfs f1, float_24_8041c4ac(r2)
		opword 0xC84100B0
		lfs f0, float_0_8041c454(r2)
		opword 0xEC421828
		opword 0xEC220828
		opword 0xFC010040
		opword 0x40800008
		opword 0xFC200090
		opword 0xC0BF2778
		lfs f0, float_1p5_8041c46c(r2)
		opword 0xC0610060
		opword 0xECA0287C
		lfs f0, float_100_8041c464(r2)
		lfs f1, float_9_8041c4b0(r2)
		opword 0xFC401890
		opword 0xFC030040
		opword 0xFCC02850
		opword 0xECE60824
		opword 0x40810008
		opword 0xFC600090
		lfs f0, float_0_8041c454(r2)
		opword 0xFC020040
		opword 0x40800008
		opword 0xFC600090
		lfs f1, float_110_8041c480(r2)
		opword 0x38A10034
		lfs f0, float_60_8041c488(r2)
		opword 0x38C10030
		opword 0xEC41182A
		opword 0xC021005C
		opword 0xEC00182A
		lfs f3, float_750_8041c484(r2)
		opword 0xFC800890
		opword 0x38E1002C
		opword 0xEC632828
		opword 0x39010028
		opword 0xEC42382A
		opword 0x39210024
		opword 0xECA0382A
		opword 0x39410020
		opword 0x38600001
		opword 0x38800001
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D0114
		bl strcpy
		opword 0x48000C8C
		opword 0x809F2764
		opword 0x7FE3FB78
		bl BattleGetUnitPtr
		opword 0x809F2768
		opword 0x7C7A1B78
		opword 0x7FE3FB78
		bl BattleGetUnitPtr
		opword 0x281A0000
		opword 0x7C7C1B78
		opword 0x4182000C
		opword 0x281C0000
		opword 0x40820014
		opword 0x38600000
		opword 0x38800000
		bl btl_camera_set_mode
		opword 0x48000C4C
		opword 0x807F2764
		opword 0x809F276C
		bl BattleGetUnitPartsPtr
		opword 0x807F2768
		opword 0x809F2770
		bl BattleGetUnitPartsPtr
		opword 0x7C7B1B78
		opword 0x38A10060
		opword 0x7F43D378
		opword 0x3881005C
		opword 0x38C10064
		bl BtlUnit_GetPos
		opword 0x7F83E378
		opword 0x7F64DB78
		opword 0x38A10050
		opword 0x38C10054
		opword 0x38E10058
		bl BtlUnit_GetHitPos
		opword 0x7F43D378
		bl BtlUnit_GetWidth
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		opword 0x7F83E378
		opword 0xC85D0070
		opword 0x900100B0
		lfs f0, float_24_8041c4ac(r2)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEFC10028
		bl BtlUnit_GetWidth
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lfs f0, float_0_8041c454(r2)
		opword 0x900100A8
		opword 0xC87D0070
		opword 0xFC1E0040
		opword 0xC84100A8
		lfs f1, float_24_8041c4ac(r2)
		opword 0xEC421828
		opword 0xEC620828
		opword 0x40800008
		opword 0xFFC00090
		lfs f0, float_0_8041c454(r2)
		opword 0xFC030040
		opword 0x40800008
		opword 0xFC600090
		opword 0xC0DF281C
		opword 0xC01F2810
		opword 0xC0410050
		opword 0xC021005C
		opword 0xEC860028
		lfs f0, float_0_8041c454(r2)
		opword 0xEC220828
		opword 0xFC002000
		opword 0x4082000C
		lfs f8, float_0p5_8041c460(r2)
		opword 0x48000008
		opword 0xED012024
		lfs f0, float_1_8041c470(r2)
		opword 0xFC080040
		opword 0x40810008
		opword 0xFD000090
		lfs f0, float_0p5_8041c460(r2)
		opword 0xFC080040
		opword 0x40800008
		opword 0xFD000090
		lfs f1, float_2_8041c450(r2)
		opword 0xEC5E182A
		opword 0xC01F2778
		lfs f3, float_1_8041c470(r2)
		opword 0xEC010032
		lfs f1, float_1p5_8041c46c(r2)
		opword 0xECE34028
		opword 0xC0BF2820
		lfs f4, float_80_8041c4b4(r2)
		opword 0xEC2100BC
		opword 0xC0610060
		opword 0xEC852024
		lfs f2, float_10_8041c4b8(r2)
		lfs f0, float_100_8041c464(r2)
		opword 0xED470072
		opword 0xEC632828
		opword 0xEC2701B2
		opword 0xFCC05050
		opword 0xED2400F2
		opword 0xED661024
		opword 0xFC090040
		opword 0x40810008
		opword 0xFD200090
		lfs f0, float_0_8041c454(r2)
		opword 0xFC090040
		opword 0x40800008
		opword 0xFD200090
		opword 0xC81D0138
		opword 0xFC800890
		lfs f2, float_750_8041c484(r2)
		opword 0x38A10034
		opword 0xFC604028
		opword 0xC91D0130
		lfs f5, float_110_8041c480(r2)
		lfs f0, float_60_8041c488(r2)
		opword 0x38C10030
		opword 0xFCE01850
		opword 0xEC625028
		opword 0x38E1002C
		opword 0x39010028
		opword 0x39210024
		opword 0xFCE849FA
		opword 0x39410020
		opword 0x38600001
		opword 0x38800001
		opword 0xFCE03818
		opword 0xEC45382A
		opword 0xEC00382A
		opword 0xEC42582A
		opword 0xECA0582A
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D0140
		bl strcpy
		opword 0x48000A60
		opword 0x809F2764
		opword 0x7FE3FB78
		bl BattleGetUnitPtr
		opword 0x809F2768
		opword 0x7C7B1B78
		opword 0x7FE3FB78
		bl BattleGetUnitPtr
		opword 0x281B0000
		opword 0x7C7A1B78
		opword 0x4182000C
		opword 0x281A0000
		opword 0x40820014
		opword 0x38600000
		opword 0x38800000
		bl btl_camera_set_mode
		opword 0x48000A20
		opword 0x807F2764
		opword 0x809F276C
		bl BattleGetUnitPartsPtr
		opword 0x807F2768
		opword 0x809F2770
		bl BattleGetUnitPartsPtr
		opword 0x7C791B78
		opword 0x38A10060
		opword 0x7F63DB78
		opword 0x3881005C
		opword 0x38C10064
		bl BtlUnit_GetPos
		opword 0x38C10054
		opword 0x7F43D378
		opword 0x7F24CB78
		opword 0x38A10050
		opword 0x38E10058
		bl BtlUnit_GetHitPos
		opword 0x7F63DB78
		bl BtlUnit_GetWidth
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		opword 0x7F43D378
		opword 0xC85D0070
		opword 0x900100B0
		lfs f0, float_24_8041c4ac(r2)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEFC10028
		bl BtlUnit_GetWidth
		lfs f0, float_0_8041c454(r2)
		opword 0xFC1E0040
		opword 0x40800008
		opword 0xFFC00090
		lfs f1, float_2_8041c450(r2)
		opword 0xC01F2778
		lfs f3, float_1p5_8041c46c(r2)
		opword 0xECE10032
		lfs f1, float_10_8041c4b8(r2)
		opword 0xC0410060
		opword 0xC0010054
		opword 0xECE33FBC
		lfs f3, float_0p5_8041c460(r2)
		opword 0xEC42002A
		lfs f0, float_50_8041c4a8(r2)
		opword 0xFCC03850
		opword 0xEC4300B2
		opword 0xED060824
		opword 0xFC020040
		opword 0x40810008
		opword 0xFFE00090
		lfs f0, float_0_8041c454(r2)
		opword 0xFC020040
		opword 0x40800008
		opword 0xFFE00090
		opword 0xC061005C
		opword 0x38A10034
		opword 0xC0410050
		opword 0x38C10030
		lfs f0, float_60_8041c488(r2)
		opword 0x38E1002C
		opword 0xEC83102A
		lfs f1, float_110_8041c480(r2)
		lfs f5, float_0p5_8041c460(r2)
		opword 0xEC00F82A
		opword 0xEC41F82A
		lfs f3, float_750_8041c484(r2)
		opword 0xEC250132
		opword 0x39010028
		opword 0xEC42402A
		opword 0x39210024
		opword 0xEC633828
		opword 0x39410020
		opword 0xFC800890
		opword 0x38600001
		opword 0xECA0402A
		opword 0x38800001
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D0114
		bl strcpy
		opword 0x480008D4
		opword 0x809F2764
		opword 0x7FE3FB78
		bl BattleGetUnitPtr
		opword 0x7C7B1B79
		opword 0x40820014
		opword 0x38600000
		opword 0x38800000
		bl btl_camera_set_mode
		opword 0x480008B0
		opword 0x807F2764
		opword 0x809F276C
		bl BattleGetUnitPartsPtr
		opword 0x7C641B79
		opword 0x40820014
		opword 0x38600000
		opword 0x38800000
		bl btl_camera_set_mode
		opword 0x4800088C
		opword 0x38C10060
		opword 0x7F63DB78
		opword 0x38A1005C
		opword 0x38E10064
		bl BtlUnit_GetHitPos
		opword 0x7F63DB78
		bl BtlUnit_GetHeight
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		opword 0x7F63DB78
		opword 0xC87D0070
		opword 0x900100B0
		lfs f2, float_50_8041c4a8(r2)
		opword 0xC80100B0
		lfs f1, float_0p5_8041c460(r2)
		opword 0xEC601828
		opword 0xC0010060
		opword 0xEC431028
		opword 0xEC220072
		opword 0xEC00082A
		opword 0xD0010060
		bl BtlUnit_GetWidth
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		opword 0xC87D0070
		opword 0x900100A8
		lfs f1, float_24_8041c4ac(r2)
		opword 0xC84100A8
		lfs f0, float_0_8041c454(r2)
		opword 0xEC421828
		opword 0xEC220828
		opword 0xFC010040
		opword 0x40800008
		opword 0xFC200090
		opword 0xC0BF2778
		lfs f0, float_1p5_8041c46c(r2)
		opword 0xC0610060
		opword 0xECA0287C
		lfs f0, float_100_8041c464(r2)
		lfs f1, float_9_8041c4b0(r2)
		opword 0xFC401890
		opword 0xFC030040
		opword 0xFCC02850
		opword 0xECE60824
		opword 0x40810008
		opword 0xFC600090
		lfs f0, float_0_8041c454(r2)
		opword 0xFC020040
		opword 0x40800008
		opword 0xFC600090
		lfs f1, float_110_8041c480(r2)
		opword 0x38A10034
		lfs f0, float_60_8041c488(r2)
		opword 0x38C10030
		opword 0xEC41182A
		opword 0xC021005C
		opword 0xEC00182A
		lfs f3, float_750_8041c484(r2)
		opword 0xFC800890
		opword 0x38E1002C
		opword 0xEC632828
		opword 0x39010028
		opword 0xEC42382A
		opword 0x39210024
		opword 0xECA0382A
		opword 0x39410020
		opword 0x38600001
		opword 0x38800001
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D0160
		bl strcpy
		opword 0x48000760
		opword 0x809F2764
		opword 0x7FE3FB78
		bl BattleGetUnitPtr
		opword 0x809F2768
		opword 0x7C7B1B78
		opword 0x7FE3FB78
		bl BattleGetUnitPtr
		opword 0x281B0000
		opword 0x7C7C1B78
		opword 0x4182000C
		opword 0x281C0000
		opword 0x40820014
		opword 0x38600000
		opword 0x38800000
		bl btl_camera_set_mode
		opword 0x48000720
		opword 0x807F2764
		opword 0x809F276C
		bl BattleGetUnitPartsPtr
		opword 0x7C7A1B78
		opword 0x807F2768
		opword 0x809F2770
		bl BattleGetUnitPartsPtr
		opword 0x281A0000
		opword 0x7C791B78
		opword 0x4182000C
		opword 0x28190000
		opword 0x40820014
		opword 0x38600000
		opword 0x38800000
		bl btl_camera_set_mode
		opword 0x480006E0
		opword 0x38A10060
		opword 0x7F43D378
		opword 0x3881005C
		opword 0x38C10064
		bl BtlUnit_GetPartsWorldPos
		opword 0x7F83E378
		opword 0x7F24CB78
		opword 0x38A10050
		opword 0x38C10054
		opword 0x38E10058
		bl BtlUnit_GetHitPos
		opword 0x7F63DB78
		bl BtlUnit_GetWidth
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100B4
		opword 0x7F83E378
		opword 0xC85D0070
		opword 0x900100B0
		lfs f0, float_24_8041c4ac(r2)
		opword 0xC82100B0
		opword 0xEC211028
		opword 0xEFC10028
		bl BtlUnit_GetWidth
		opword 0x6C638000
		opword 0x3C004330
		opword 0x906100AC
		lfs f0, float_0_8041c454(r2)
		opword 0x900100A8
		opword 0xC87D0070
		opword 0xFC1E0040
		opword 0xC84100A8
		lfs f1, float_24_8041c4ac(r2)
		opword 0xEC421828
		opword 0xEC620828
		opword 0x40800008
		opword 0xFFC00090
		lfs f0, float_0_8041c454(r2)
		opword 0xFC030040
		opword 0x40800008
		opword 0xFC600090
		opword 0xC0DF281C
		opword 0xC01F2810
		opword 0xC0410050
		opword 0xC021005C
		opword 0xEC860028
		lfs f0, float_0_8041c454(r2)
		opword 0xEC220828
		opword 0xFC002000
		opword 0x40820008
		lfs f4, float_1Eneg05_8041c4bc(r2)
		opword 0xED012024
		lfs f0, float_1_8041c470(r2)
		opword 0xFC080040
		opword 0x40810008
		opword 0xFD000090
		lfs f0, float_0p5_8041c460(r2)
		opword 0xFC080040
		opword 0x40800008
		opword 0xFD000090
		lfs f1, float_2_8041c450(r2)
		opword 0xEC5E182A
		opword 0xC01F2778
		lfs f3, float_1_8041c470(r2)
		opword 0xEC010032
		lfs f1, float_1p5_8041c46c(r2)
		opword 0xECE34028
		opword 0xC0BF2820
		lfs f4, float_80_8041c4b4(r2)
		opword 0xEC2100BC
		opword 0xC0610060
		opword 0xEC852024
		lfs f2, float_10_8041c4b8(r2)
		lfs f0, float_100_8041c464(r2)
		opword 0xED470072
		opword 0xEC632828
		opword 0xEC2701B2
		opword 0xFCC05050
		opword 0xED2400F2
		opword 0xED661024
		opword 0xFC090040
		opword 0x40810008
		opword 0xFD200090
		lfs f0, float_0_8041c454(r2)
		opword 0xFC090040
		opword 0x40800008
		opword 0xFD200090
		opword 0xC81D0138
		opword 0xFC800890
		lfs f2, float_750_8041c484(r2)
		opword 0x38A10034
		opword 0xFC604028
		opword 0xC91D0130
		lfs f5, float_110_8041c480(r2)
		lfs f0, float_60_8041c488(r2)
		opword 0x38C10030
		opword 0xFCE01850
		opword 0xEC625028
		opword 0x38E1002C
		opword 0x39010028
		opword 0x39210024
		opword 0xFCE849FA
		opword 0x39410020
		opword 0x38600001
		opword 0x38800001
		opword 0xFCE03818
		opword 0xEC45382A
		opword 0xEC00382A
		opword 0xEC42582A
		opword 0xECA0582A
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D0178
		bl strcpy
		opword 0x48000514
		opword 0x801F2774
		opword 0x38A10034
		lfs f0, float_400_8041c494(r2)
		opword 0x38C10030
		opword 0x1C600134
		lfs f2, float_200_8041c47c(r2)
		lfs f5, float_0_8041c454(r2)
		opword 0x38E1002C
		opword 0x39010028
		opword 0x386301BC
		opword 0x7C7C1A14
		opword 0x39210024
		opword 0xC0C30050
		opword 0x39410020
		opword 0xC0230048
		opword 0x38600001
		opword 0xEC60302A
		opword 0x38800000
		opword 0xFC800890
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D0194
		bl strcpy
		opword 0x480004B4
		opword 0x809F2764
		opword 0x7FE3FB78
		bl BattleGetUnitPtr
		opword 0x7C7B1B79
		opword 0x40820014
		opword 0x38600000
		opword 0x38800000
		bl btl_camera_set_mode
		opword 0x48000490
		opword 0x807F2764
		opword 0x809F276C
		bl BattleGetUnitPartsPtr
		opword 0x28030000
		opword 0x40820014
		opword 0x38600000
		opword 0x38800000
		bl btl_camera_set_mode
		opword 0x4800046C
		opword 0x3800000A
		opword 0x38A10060
		opword 0x901F2774
		opword 0x7F63DB78
		opword 0x3881005C
		opword 0x38C10064
		opword 0xC03F281C
		opword 0xC01F2810
		opword 0xEFC10028
		bl BtlUnit_GetPos
		lfs f0, float_0_8041c454(r2)
		opword 0xC07F281C
		opword 0xC021005C
		opword 0xFC00F000
		opword 0xEC030828
		opword 0x4082000C
		lfs f7, float_0p5_8041c460(r2)
		opword 0x48000008
		opword 0xECE0F024
		lfs f0, float_1_8041c470(r2)
		opword 0xFC070040
		opword 0x40810008
		opword 0xFCE00090
		lfs f0, float_0p5_8041c460(r2)
		opword 0xFC070040
		opword 0x40800008
		opword 0xFCE00090
		opword 0xC0410060
		opword 0xC01F2814
		lfs f1, float_1_8041c470(r2)
		opword 0xECA20028
		lfs f0, float_100_8041c464(r2)
		opword 0xEC813828
		lfs f2, float_2_8041c450(r2)
		opword 0xC03F2778
		opword 0xECA50028
		lfs f0, float_0_8041c454(r2)
		opword 0xECC20072
		opword 0xEC2400F2
		opword 0xFC050040
		opword 0x40810008
		opword 0xFCA00090
		lfs f0, float_neg30_8041c4c0(r2)
		opword 0xFC050040
		opword 0x40800008
		opword 0xFCA00090
		opword 0xC85D0138
		opword 0xECC401B2
		lfs f0, float_125_8041c4c4(r2)
		opword 0xFC800890
		opword 0xFC623828
		lfs f2, float_750_8041c484(r2)
		opword 0xECE02828
		lfs f5, float_110_8041c480(r2)
		opword 0x38A10034
		opword 0xFD001850
		opword 0xEC623028
		lfs f0, float_60_8041c488(r2)
		opword 0xFCC03050
		opword 0x38C10030
		opword 0xFCE801F2
		opword 0x38E1002C
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600001
		opword 0xFCE03818
		opword 0x38800001
		opword 0xEC45382A
		opword 0xECA0382A
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D01B0
		bl strcpy
		opword 0x48000340
		opword 0x807F2758
		opword 0x38030001
		opword 0x901F2758
		opword 0x801F2758
		opword 0x2C000001
		opword 0x40820098
		bl pouchGetPtr
		opword 0xA8030088
		opword 0x2C000002
		opword 0x41820034
		opword 0x40800014
		opword 0x2C000000
		opword 0x41820018
		opword 0x4080001C
		opword 0x4800002C
		opword 0x2C000004
		opword 0x40800024
		opword 0x4800001C
		lfs f30, float_750_8041c484(r2)
		opword 0x48000018
		lfs f30, float_830_8041c49c(r2)
		opword 0x48000010
		lfs f30, float_920_8041c4a0(r2)
		opword 0x48000008
		lfs f30, float_1000_8041c4a4(r2)
		lfs f1, float_0_8041c454(r2)
		opword 0x38000003
		opword 0xB01F277C
		opword 0xFC60F090
		opword 0xFC800890
		lfs f2, float_110_8041c480(r2)
		opword 0xFCC00890
		opword 0xB01F277E
		lfs f5, float_60_8041c488(r2)
		opword 0x38A10034
		opword 0x38C10030
		opword 0x38E1002C
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600001
		opword 0x38800001
		bl battleCameraMoveTo
		opword 0x801F2758
		opword 0x2C00000A
		opword 0x40820040
		opword 0x38000000
		opword 0x38600000
		opword 0x901F2758
		opword 0x38800003
		bl btl_camera_set_mode
		lfs f1, float_0_8041c454(r2)
		opword 0x38600000
		lfs f2, float_110_8041c480(r2)
		opword 0x38800078
		opword 0xFC800890
		lfs f3, float_750_8041c484(r2)
		opword 0xFCC00890
		lfs f5, float_60_8041c488(r2)
		opword 0x38A00004
		bl btl_camera_set_moveto
		opword 0x38610068
		opword 0x389D01D8
		bl strcpy
		opword 0x4800023C
		lfs f1, float_0_8041c454(r2)
		opword 0x38000003
		opword 0xB01F277C
		opword 0x38A10034
		opword 0xFC800890
		lfs f2, float_110_8041c480(r2)
		opword 0xFCC00890
		opword 0xB01F277E
		lfs f3, float_500_8041c4c8(r2)
		opword 0x38C10030
		lfs f5, float_60_8041c488(r2)
		opword 0x38E1002C
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600001
		opword 0x38800001
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D01F4
		bl strcpy
		opword 0x480001E4
		lfs f1, float_neg100_8041c468(r2)
		opword 0x38000003
		opword 0xB01F277C
		opword 0x38A10034
		opword 0xFC800890
		lfs f2, float_110_8041c480(r2)
		opword 0xB01F277E
		opword 0x38C10030
		lfs f3, float_500_8041c4c8(r2)
		opword 0x38E1002C
		lfs f5, float_60_8041c488(r2)
		opword 0x39010028
		lfs f6, float_0_8041c454(r2)
		opword 0x39210024
		opword 0x39410020
		opword 0x38600001
		opword 0x38800001
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D020C
		bl strcpy
		opword 0x4800018C
		opword 0x7FE3FB78
		bl BattleGetMarioPtr
		opword 0x7C601B78
		opword 0x7FE3FB78
		opword 0x7C190378
		bl BattleGetPartyPtr
		opword 0x7C7A1B79
		opword 0x41820078
		opword 0x7F23CB78
		opword 0x3881001C
		opword 0x38A10018
		opword 0x38C10014
		bl BtlUnit_GetHomePos
		opword 0x7F43D378
		opword 0x38810010
		opword 0x38A1000C
		opword 0x38C10008
		bl BtlUnit_GetHomePos
		opword 0xC061001C
		opword 0xC0410010
		opword 0xC0210018
		opword 0xC001000C
		opword 0xEC83102A
		lfs f5, float_0p5_8041c460(r2)
		opword 0xEC61002A
		opword 0x801F2760
		opword 0xC0410014
		opword 0xEC250132
		opword 0xC0010008
		opword 0x2C000012
		opword 0xEC02002A
		opword 0xECC500F2
		opword 0xECA50032
		opword 0x40820030
		lfs f0, float_20_8041c4cc(r2)
		opword 0xECC60028
		opword 0x48000024
		opword 0x7F23CB78
		opword 0x3881001C
		opword 0x38A10018
		opword 0x38C10014
		bl BtlUnit_GetHomePos
		opword 0xC021001C
		opword 0xC0C10018
		opword 0xC0A10014
		lfs f2, float_100_8041c464(r2)
		opword 0x38000001
		lfs f3, float_350_8041c4d0(r2)
		opword 0xFC800890
		opword 0xB01F277C
		opword 0xEC42302A
		lfs f0, float_50_8041c4a8(r2)
		opword 0xEC63282A
		opword 0xB01F277E
		opword 0xECA0302A
		lfs f6, float_0_8041c454(r2)
		opword 0x38A10034
		opword 0x38C10030
		opword 0x38E1002C
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600000
		opword 0x38800001
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D0224
		bl strcpy
		opword 0x48000078
		opword 0x38610068
		opword 0x389D0238
		bl strcpy
		opword 0x48000068
		lfs f1, float_neg100_8041c468(r2)
		opword 0x38000002
		opword 0xB01F277C
		opword 0x38A10034
		opword 0xFC800890
		lfs f2, float_100_8041c464(r2)
		opword 0xB01F277E
		opword 0x38C10030
		lfs f3, float_400_8041c494(r2)
		opword 0x38E1002C
		lfs f5, float_50_8041c4a8(r2)
		opword 0x39010028
		lfs f6, float_0_8041c454(r2)
		opword 0x39210024
		opword 0x39410020
		opword 0x38600001
		opword 0x38800001
		bl battleCameraMoveTo
		opword 0x38610068
		opword 0x389D024C
		bl strcpy
		opword 0x48000010
		opword 0x38610068
		opword 0x389D0260
		bl strcpy
		opword 0xC03E0014
		lfs f0, float_1000_8041c4a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820008
		opword 0xD01E0014
		opword 0x801F2754
		opword 0x5400077B
		opword 0x41820020
		opword 0xC03F278C
		lfs f0, float_0_8041c454(r2)
		opword 0xD03E000C
		opword 0xC03F27A4
		opword 0xD03E0018
		opword 0xD0010034
		opword 0xD0010028
		opword 0x801F2754
		opword 0x54000739
		opword 0x41820020
		opword 0xC03F2790
		lfs f0, float_0_8041c454(r2)
		opword 0xD03E0010
		opword 0xC03F27A8
		opword 0xD03E001C
		opword 0xD0010030
		opword 0xD0010024
		opword 0x801F2754
		opword 0x540006F7
		opword 0x41820020
		opword 0xC03F2794
		lfs f0, float_0_8041c454(r2)
		opword 0xD03E0014
		opword 0xC03F27AC
		opword 0xD03E0020
		opword 0xD001002C
		opword 0xD0010020
		opword 0xC01E000C
		opword 0xD01F2780
		opword 0xC01E0010
		opword 0xD01F2784
		opword 0xC01E0014
		opword 0xD01F2788
		opword 0xC01E0018
		opword 0xD01F2798
		opword 0xC01E001C
		opword 0xD01F279C
		opword 0xC01E0020
		opword 0xD01F27A0
		opword 0x801D000C
		opword 0x807D0010
		opword 0x90010044
		opword 0xC0010034
		opword 0x801D0014
		opword 0xD0010044
		opword 0xC0210030
		opword 0x90610048
		opword 0xC001002C
		opword 0x9001004C
		opword 0x80010044
		opword 0xD0210048
		opword 0xD001004C
		opword 0x80610048
		opword 0x901F27BC
		opword 0x8001004C
		opword 0x907F27C0
		opword 0x901F27C4
		opword 0x809D0018
		opword 0x807D001C
		opword 0x801D0020
		opword 0x90810038
		opword 0xC0010028
		opword 0x9061003C
		opword 0xC0210024
		opword 0xD0010038
		opword 0xC0010020
		opword 0x90010040
		opword 0x80010038
		opword 0xD021003C
		opword 0xD0010040
		opword 0x8061003C
		opword 0x901F27C8
		opword 0x80010040
		opword 0x907F27CC
		opword 0x901F27D0
		opword 0x807F2754
		opword 0x546007FF
		opword 0x40820014
		opword 0x546007BD
		opword 0x4082000C
		opword 0x38600000
		bl padRumbleOff
		opword 0x801F2754
		opword 0x54000673
		opword 0x4182000C
		opword 0x38600000
		bl padRumbleOff
		opword 0x801F2754
		opword 0x540007FF
		opword 0x41820128
		lha r25, 0x277c(r31)
		opword 0x38000003
		opword 0xAB5F277E
		opword 0x809F2838
		opword 0x807F2830
		opword 0xB01F277C
		opword 0x7C641850
		opword 0x547B07BC
		opword 0xB01F277E
		opword 0x80BF2830
		opword 0x801F2838
		opword 0x807F2828
		opword 0x7C002850
		opword 0xC03F2840
		opword 0x7C000E70
		opword 0xC05F2844
		opword 0x7C800194
		opword 0x7CA00E70
		opword 0x7CA00194
		bl intplGetValue
		opword 0xD03F2850
		opword 0x801F2838
		opword 0x2C000000
		opword 0x408100A4
		opword 0x2C1B0000
		opword 0x40820050
		opword 0xC07F2850
		opword 0x38A10034
		opword 0xC03E000C
		opword 0x38C10030
		opword 0xC01E0018
		opword 0x38E1002C
		opword 0xEC21182A
		opword 0xC05E0010
		opword 0xEC80182A
		opword 0xC07E0014
		opword 0xC0BE001C
		opword 0x39010028
		opword 0xC0DE0020
		opword 0x39210024
		opword 0x39410020
		opword 0x38600000
		opword 0x38800000
		bl battleCameraMoveTo
		opword 0x48000060
		opword 0xC07F2850
		opword 0x38A10034
		opword 0xC03E000C
		opword 0x38C10030
		opword 0xC01E0018
		opword 0x38E1002C
		opword 0xEC211828
		opword 0xC05E0010
		opword 0xEC801828
		opword 0xC07E0014
		opword 0xC0BE001C
		opword 0x39010028
		opword 0xC0DE0020
		opword 0x39210024
		opword 0x39410020
		opword 0x38600000
		opword 0x38800000
		bl battleCameraMoveTo
		opword 0x48000014
		opword 0x40820010
		opword 0x801F2754
		opword 0x5400003C
		opword 0x901F2754
		opword 0xB33F277C
		opword 0xB35F277E
		opword 0x807F2838
		opword 0x3803FFFF
		opword 0x901F2838
		opword 0x801F2754
		opword 0x540007BD
		opword 0x41820128
		opword 0xAB3F277C
		opword 0x38000003
		opword 0xAB5F277E
		opword 0x809F283C
		opword 0x807F2834
		opword 0xB01F277C
		opword 0x7C641850
		opword 0x547B07BC
		opword 0xB01F277E
		opword 0x80BF2834
		opword 0x801F283C
		opword 0x807F282C
		opword 0x7C002850
		opword 0xC03F2848
		opword 0x7C000E70
		opword 0xC05F284C
		opword 0x7C800194
		opword 0x7CA00E70
		opword 0x7CA00194
		bl intplGetValue
		opword 0xD03F2854
		opword 0x801F283C
		opword 0x2C000000
		opword 0x408100A4
		opword 0x2C1B0000
		opword 0x40820050
		opword 0xC07F2854
		opword 0x38A10034
		opword 0xC03E0010
		opword 0x38C10030
		opword 0xC01E001C
		opword 0x38E1002C
		opword 0xEC41182A
		opword 0xC03E000C
		opword 0xECA0182A
		opword 0xC07E0014
		opword 0xC09E0018
		opword 0x39010028
		opword 0xC0DE0020
		opword 0x39210024
		opword 0x39410020
		opword 0x38600000
		opword 0x38800000
		bl battleCameraMoveTo
		opword 0x48000060
		opword 0xC07F2854
		opword 0x38A10034
		opword 0xC03E0010
		opword 0x38C10030
		opword 0xC01E001C
		opword 0x38E1002C
		opword 0xEC411828
		opword 0xC03E000C
		opword 0xECA01828
		opword 0xC07E0014
		opword 0xC09E0018
		opword 0x39010028
		opword 0xC0DE0020
		opword 0x39210024
		opword 0x39410020
		opword 0x38600000
		opword 0x38800000
		bl battleCameraMoveTo
		opword 0x48000014
		opword 0x40820010
		opword 0x801F2754
		opword 0x540007FA
		opword 0x901F2754
		opword 0xB33F277C
		opword 0xB35F277E
		opword 0x807F283C
		opword 0x3803FFFF
		opword 0x901F283C
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void battleCameraMoveTo(s32 mode, s32 clamp, f32 x, f32 y, f32 z, f32 atX, f32 atY, f32 atZ,
                        f32* dX, f32* dY, f32* dZ, f32* dAtX, f32* dAtY, f32* dAtZ) {
	asm volatile {
		opword 0xFF400890
		mr r22, r3
		opword 0xFF601090
		opword 0x7C972378
		opword 0xFF801890
		opword 0x7CB82B78
		opword 0xFFA02090
		opword 0x7CD93378
		opword 0xFFC02890
		opword 0x7CFA3B78
		opword 0xFFE03090
		opword 0x7D1B4378
		opword 0x7D3C4B78
		opword 0x7D5D5378
		opword 0x38600004
		bl camGetPtr
		lwz r30, _battleWorkPointer(r13)
		opword 0x7C7F1B78
		opword 0x7FC3F378
		bl BattleGetMarioPtr
		opword 0xA89E277C
		opword 0x7C800735
		opword 0x4180000C
		opword 0x2C040005
		opword 0x4180000C
		opword 0x38000001
		opword 0xB01E277C
		opword 0xA89E277E
		opword 0x7C800735
		opword 0x4180000C
		opword 0x2C040006
		opword 0x4180000C
		opword 0x38000001
		opword 0xB01E277E
		opword 0x2C160001
		opword 0x40820060
		opword 0x801E0EF4
		opword 0x540005EF
		opword 0x41820030
		opword 0xC0630038
		lfs f0, float_0_8041c454(r2)
		opword 0xFC201850
		lfs f2, float_0p25_8041c458(r2)
		fadds f26, f26, f0
		opword 0xEF9C182A
		opword 0xEC220072
		opword 0xEFBD002A
		opword 0xEFFF182A
		opword 0xEF7B082A
		opword 0xEFDE082A
		opword 0xC01E27B0
		opword 0xC03E27B4
		opword 0xC05E27B8
		opword 0xEF5A002A
		opword 0xEF7B082A
		opword 0xEF9C102A
		opword 0xEFBD002A
		opword 0xEFDE082A
		opword 0xEFFF102A
		lfs f0, float_600_8041c45c(r2)
		lfs f1, float_0p5_8041c460(r2)
		opword 0xEC40E028
		lfs f0, float_0_8041c454(r2)
		opword 0xEC420072
		opword 0xFC020040
		opword 0x40800008
		opword 0xFC400090
		opword 0x2C170001
		opword 0x40820044
		lfs f0, float_100_8041c464(r2)
		opword 0xEC20102A
		opword 0xFC1A0840
		opword 0x40810008
		opword 0xFF400890
		lfs f0, float_neg100_8041c468(r2)
		opword 0xEC001028
		opword 0xFC1A0040
		opword 0x40800008
		opword 0xFF400090
		opword 0xFC1D0840
		opword 0x40810008
		opword 0xFFA00890
		opword 0xFC1D0040
		opword 0x40800008
		opword 0xFFA00090
		opword 0xA81E277C
		opword 0x2C000003
		opword 0x41820214
		opword 0x4080001C
		opword 0x2C000001
		opword 0x418200C0
		opword 0x40800168
		opword 0x2C000000
		opword 0x40800018
		opword 0x480003B4
		opword 0x2C000005
		opword 0x41820314
		opword 0x408003A8
		opword 0x48000270
		opword 0xC01F000C
		lfs f3, float_1p5_8041c46c(r2)
		opword 0xEC5A0028
		lfs f1, float_0_8041c454(r2)
		lfs f0, float_1_8041c470(r2)
		opword 0xEC421824
		opword 0xD0580000
		opword 0xC05F0010
		opword 0xEC5B1028
		opword 0xEC421824
		opword 0xD0590000
		opword 0xC05F0018
		opword 0xEC5D1028
		opword 0xEC421824
		opword 0xD05B0000
		opword 0xC05F001C
		opword 0xEC5E1028
		opword 0xEC421824
		opword 0xD05C0000
		opword 0xC07F000C
		opword 0xC0580000
		opword 0xEC43102A
		opword 0xD05F000C
		opword 0xC07F0010
		opword 0xC0590000
		opword 0xEC43102A
		opword 0xD05F0010
		opword 0xC07F0018
		opword 0xC05B0000
		opword 0xEC43102A
		opword 0xD05F0018
		opword 0xC07F001C
		opword 0xC05C0000
		opword 0xEC43102A
		opword 0xD05F001C
		opword 0xD03F0024
		opword 0xD01F0028
		opword 0xD03F002C
		opword 0x48000308
		opword 0xC01F000C
		lfs f3, float_15_8041c474(r2)
		opword 0xEC5A0028
		lfs f1, float_0_8041c454(r2)
		lfs f0, float_1_8041c470(r2)
		opword 0xEC421824
		opword 0xD0580000
		opword 0xC05F0010
		opword 0xEC5B1028
		opword 0xEC421824
		opword 0xD0590000
		opword 0xC05F0018
		opword 0xEC5D1028
		opword 0xEC421824
		opword 0xD05B0000
		opword 0xC05F001C
		opword 0xEC5E1028
		opword 0xEC421824
		opword 0xD05C0000
		opword 0xC07F000C
		opword 0xC0580000
		opword 0xEC43102A
		opword 0xD05F000C
		opword 0xC07F0010
		opword 0xC0590000
		opword 0xEC43102A
		opword 0xD05F0010
		opword 0xC07F0014
		opword 0xC05A0000
		opword 0xEC43102A
		opword 0xD05F0014
		opword 0xC07F0018
		opword 0xC05B0000
		opword 0xEC43102A
		opword 0xD05F0018
		opword 0xC07F001C
		opword 0xC05C0000
		opword 0xEC43102A
		opword 0xD05F001C
		opword 0xD03F0024
		opword 0xD01F0028
		opword 0xD03F002C
		opword 0x4800025C
		opword 0xC01F000C
		lfs f3, float_5_8041c478(r2)
		opword 0xEC5A0028
		lfs f1, float_0_8041c454(r2)
		lfs f0, float_1_8041c470(r2)
		opword 0xEC421824
		opword 0xD0580000
		opword 0xC05F0010
		opword 0xEC5B1028
		opword 0xEC421824
		opword 0xD0590000
		opword 0xC05F0018
		opword 0xEC5D1028
		opword 0xEC421824
		opword 0xD05B0000
		opword 0xC05F001C
		opword 0xEC5E1028
		opword 0xEC421824
		opword 0xD05C0000
		opword 0xC07F000C
		opword 0xC0580000
		opword 0xEC43102A
		opword 0xD05F000C
		opword 0xC07F0010
		opword 0xC0590000
		opword 0xEC43102A
		opword 0xD05F0010
		opword 0xC07F0018
		opword 0xC05B0000
		opword 0xEC43102A
		opword 0xD05F0018
		opword 0xC07F001C
		opword 0xC05C0000
		opword 0xEC43102A
		opword 0xD05F001C
		opword 0xD03F0024
		opword 0xD01F0028
		opword 0xD03F002C
		opword 0x480001C0
		opword 0xC01F000C
		lfs f1, float_0_8041c454(r2)
		opword 0xEC5A0028
		lfs f0, float_1_8041c470(r2)
		opword 0xD0580000
		opword 0xC05F0010
		opword 0xEC5B1028
		opword 0xD0590000
		opword 0xC05F0018
		opword 0xEC5D1028
		opword 0xD05B0000
		opword 0xC05F001C
		opword 0xEC5E1028
		opword 0xD05C0000
		opword 0xC07F000C
		opword 0xC0580000
		opword 0xEC43102A
		opword 0xD05F000C
		opword 0xC07F0010
		opword 0xC0590000
		opword 0xEC43102A
		opword 0xD05F0010
		opword 0xC07F0018
		opword 0xC05B0000
		opword 0xEC43102A
		opword 0xD05F0018
		opword 0xC07F001C
		opword 0xC05C0000
		opword 0xEC43102A
		opword 0xD05F001C
		opword 0xD03F0024
		opword 0xD01F0028
		opword 0xD03F002C
		opword 0x48000138
		opword 0xC01F000C
		lfs f3, float_200_8041c47c(r2)
		opword 0xEC5A0028
		lfs f1, float_0_8041c454(r2)
		lfs f0, float_1_8041c470(r2)
		opword 0xEC421824
		opword 0xD0580000
		opword 0xC05F0010
		opword 0xEC5B1028
		opword 0xEC421824
		opword 0xD0590000
		opword 0xC05F0018
		opword 0xEC5D1028
		opword 0xEC421824
		opword 0xD05B0000
		opword 0xC05F001C
		opword 0xEC5E1028
		opword 0xEC421824
		opword 0xD05C0000
		opword 0xC07F000C
		opword 0xC0580000
		opword 0xEC43102A
		opword 0xD05F000C
		opword 0xC07F0010
		opword 0xC0590000
		opword 0xEC43102A
		opword 0xD05F0010
		opword 0xC07F0018
		opword 0xC05B0000
		opword 0xEC43102A
		opword 0xD05F0018
		opword 0xC07F001C
		opword 0xC05C0000
		opword 0xEC43102A
		opword 0xD05F001C
		opword 0xD03F0024
		opword 0xD01F0028
		opword 0xD03F002C
		opword 0x4800009C
		opword 0xC01F000C
		lfs f3, float_100_8041c464(r2)
		opword 0xEC5A0028
		lfs f1, float_0_8041c454(r2)
		lfs f0, float_1_8041c470(r2)
		opword 0xEC421824
		opword 0xD0580000
		opword 0xC05F0010
		opword 0xEC5B1028
		opword 0xEC421824
		opword 0xD0590000
		opword 0xC05F0018
		opword 0xEC5D1028
		opword 0xEC421824
		opword 0xD05B0000
		opword 0xC05F001C
		opword 0xEC5E1028
		opword 0xEC421824
		opword 0xD05C0000
		opword 0xC07F000C
		opword 0xC0580000
		opword 0xEC43102A
		opword 0xD05F000C
		opword 0xC07F0010
		opword 0xC0590000
		opword 0xEC43102A
		opword 0xD05F0010
		opword 0xC07F0018
		opword 0xC05B0000
		opword 0xEC43102A
		opword 0xD05F0018
		opword 0xC07F001C
		opword 0xC05C0000
		opword 0xEC43102A
		opword 0xD05F001C
		opword 0xD03F0024
		opword 0xD01F0028
		opword 0xD03F002C
		opword 0xA81E277E
		opword 0x2C000003
		opword 0x41820108
		opword 0x4080001C
		opword 0x2C000001
		opword 0x4182006C
		opword 0x408000B0
		opword 0x2C000000
		opword 0x40800018
		opword 0x480001B4
		opword 0x2C000005
		opword 0x41820168
		opword 0x408001A8
		opword 0x48000118
		opword 0xC01F0014
		lfs f1, float_1p5_8041c46c(r2)
		opword 0xEC1C0028
		opword 0xEC000824
		opword 0xD01A0000
		opword 0xC01F0020
		opword 0xEC1F0028
		opword 0xEC000824
		opword 0xD01D0000
		opword 0xC03F0014
		opword 0xC01A0000
		opword 0xEC01002A
		opword 0xD01F0014
		opword 0xC03F0020
		opword 0xC01D0000
		opword 0xEC01002A
		opword 0xD01F0020
		opword 0x4800015C
		opword 0xC01F0014
		lfs f1, float_15_8041c474(r2)
		opword 0xEC1C0028
		opword 0xEC000824
		opword 0xD01A0000
		opword 0xC01F0020
		opword 0xEC1F0028
		opword 0xEC000824
		opword 0xD01D0000
		opword 0xC03F0014
		opword 0xC01A0000
		opword 0xEC01002A
		opword 0xD01F0014
		opword 0xC03F0020
		opword 0xC01D0000
		opword 0xEC01002A
		opword 0xD01F0020
		opword 0x48000114
		opword 0xC01F0014
		lfs f1, float_5_8041c478(r2)
		opword 0xEC1C0028
		opword 0xEC000824
		opword 0xD01A0000
		opword 0xC01F0020
		opword 0xEC1F0028
		opword 0xEC000824
		opword 0xD01D0000
		opword 0xC03F0014
		opword 0xC01A0000
		opword 0xEC01002A
		opword 0xD01F0014
		opword 0xC03F0020
		opword 0xC01D0000
		opword 0xEC01002A
		opword 0xD01F0020
		opword 0x480000CC
		opword 0xC01F0014
		opword 0xEC1C0028
		opword 0xD01A0000
		opword 0xC01F0020
		opword 0xEC1F0028
		opword 0xD01D0000
		opword 0xC03F0014
		opword 0xC01A0000
		opword 0xEC01002A
		opword 0xD01F0014
		opword 0xC03F0020
		opword 0xC01D0000
		opword 0xEC01002A
		opword 0xD01F0020
		opword 0x48000090
		opword 0xC01F0014
		lfs f1, float_200_8041c47c(r2)
		opword 0xEC1C0028
		opword 0xEC000824
		opword 0xD01A0000
		opword 0xC01F0020
		opword 0xEC1F0028
		opword 0xEC000824
		opword 0xD01D0000
		opword 0xC03F0014
		opword 0xC01A0000
		opword 0xEC01002A
		opword 0xD01F0014
		opword 0xC03F0020
		opword 0xC01D0000
		opword 0xEC01002A
		opword 0xD01F0020
		opword 0x48000048
		opword 0xC01F0014
		lfs f1, float_100_8041c464(r2)
		opword 0xEC1C0028
		opword 0xEC000824
		opword 0xD01A0000
		opword 0xC01F0020
		opword 0xEC1F0028
		opword 0xEC000824
		opword 0xD01D0000
		opword 0xC03F0014
		opword 0xC01A0000
		opword 0xEC01002A
		opword 0xD01F0014
		opword 0xC03F0020
		opword 0xC01D0000
		opword 0xEC01002A
		opword 0xD01F0020
	}
}
#pragma pop

f32 battleCameraGetPosMoveSpeed(void) {
  BattleWork* wp = _battleWorkPointer;
  f32 x = wp->cameraWork.moveSpeed.x;
  f32 y = wp->cameraWork.moveSpeed.y;
  f32 z = wp->cameraWork.moveSpeed.z;
  return sqrt(x * x + y * y + z * z);
}

void btl_camera_set_prilimit(s32 pri) {
  _battleWorkPointer->cameraWork.priLimit = pri;
}

#pragma dont_inline on
s32 evt_btl_camera_set_prilimit(EventEntry* event, BOOL isFirstCall) {
  btl_camera_set_prilimit(evtGetValue(event, event->args[0]));
#endif
  return 2;
}
#ifndef NONMATCHING
#pragma dont_inline reset

#pragma dont_inline on
void btl_camera_set_mode(s32 pri, s32 mode) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    wp->cameraWork.mode = mode;
    wp->cameraWork.zoom = EXT_LIT(float_0_8041c454, 0.0f);
    wp->cameraWork.moveSpeedLv = 1;
    wp->cameraWork.zoomSpeedLv = 1;
    wp->cameraWork.unk4 = 0;
    btl_camera_nomove_x_onoff(0, 0);
    btl_camera_nomove_y_onoff(0, 0);
    btl_camera_nomove_z_onoff(0, 0);
    wp->cameraWork.flags &= ~0x20;
  }
}
#pragma dont_inline reset

#pragma dont_inline on
s32 evt_btl_camera_set_mode(EventEntry* event, BOOL isFirstCall) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  s32 val = evtGetValue(event, args[1]);
  btl_camera_set_mode(pri, val);
  return 2;
}
#pragma dont_inline reset
#endif


#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802efc40[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802efc4c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802efc58[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802efc64[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802efc70[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802efc7c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802efc88[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802efc94[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802efca0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f64 double_to_int_802efcb0 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802EFCB8[20] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xc5\x82\xd3\x82\xa7\x82\xe9\x82\xc6\0";
__declspec(section ".rodata") const char str_802EFCCC[28] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xc5\x82\xd3\x82\xa7\x82\xe9\x82\xc6\x83Y\x81[\x83\x80\0\0\0";
__declspec(section ".rodata") const char str_802EFCE8[28] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xa9\x81[\x82\xbb\x82\xe9\x82\xaa\x82\xa4\x82\xa6\x82\xc9\0\0\0";
__declspec(section ".rodata") const char str_802EFD04[16] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xd3\x82\xe8\x81[\0";
__declspec(section ".rodata") const char str_802EFD14[20] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xd4\x82\xbd\x82\xa2\x82\xa4\x82\xe7\0";
__declspec(section ".rodata") const char str_802EFD28[24] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xd4\x82\xbd\x82\xa2\x82\xa4\x82\xe7\x82Q\0\0\0";
__declspec(section ".rodata") const char str_802EFD40[20] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xa9\x82\xf1\x82\xab\x82\xe1\x82\xad\0";
__declspec(section ".rodata") const char str_802EFD54[24] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xe4\x82\xc9\x82\xc1\x82\xc6\x82\xc2\x82\xa2\x82\xd1\0";
__declspec(section ".rodata") const u32 gap_04_802EFD6C_rodata = 0x00000000;
__declspec(section ".rodata") const f64 double_20_802efd70 = 20.0;
__declspec(section ".rodata") const f64 double_1_802efd78 = 1.0;
__declspec(section ".rodata") const char str_802EFD80[32] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82Q\x82\xe4\x82\xc9\x82\xc1\x82\xc6\x82\xa9\x82\xf1\x82\xc2\x82\xa2\x82\xd1\0\0\0";
__declspec(section ".rodata") const char str_802EFDA0[24] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xcf\x81[\x82\xc2\x82\xc2\x82\xa2\x82\xd1\0\0\0";
__declspec(section ".rodata") const char str_802EFDB8[28] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82Q\x82\xcf\x81[\x82\xc2\x82\xa9\x82\xf1\x82\xc2\x82\xa2\x82\xd1\0";
__declspec(section ".rodata") const char str_802EFDD4[28] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xa9\x82\xf1\x82\xab\x82\xe1\x82\xad\x82\xc2\x82\xa2\x82\xd1\0\0\0";
__declspec(section ".rodata") const char str_802EFDF0[40] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xe4\x82\xc9\x82\xc1\x82\xc6\x82\xa9\x82\xf1\x82\xab\x82\xe1\x82\xad\x82\xa9\x82\xf1\x82\xc2\x82\xa2\x82\xd1\0\0\0";
__declspec(section ".rodata") const char str_802EFE18[28] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xd3\x82\xc2\x82\xa4\x82\xc9\x82\xcd\x82\xa2\x82\xc1\x82\xbd\0\0\0";
__declspec(section ".rodata") const char str_802EFE34[24] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xa4\x82\xdc\x82\xad\x82\xcd\x82\xa2\x82\xc1\x82\xbd\0";
__declspec(section ".rodata") const char str_802EFE4C[24] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xbe\x82\xdf\x82\xc9\x82\xcd\x82\xa2\x82\xc1\x82\xbd\0";
__declspec(section ".rodata") const char str_802EFE64[20] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xb5\x82\xe5\x82\xa4\x82\xe8\0\0\0";
__declspec(section ".rodata") const char str_802EFE78[20] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xcd\x82\xa2\x82\xda\x82\xad\0\0\0";
__declspec(section ".rodata") const char str_802EFE8C[20] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xc9\x82\xb0\x82\xc4\x82\xe9\0\0\0";
__declspec(section ".rodata") const char str_802EFEA0[20] = "\x82\xa9\x82\xdf\x82\xe7\x81@\x82\xa8\x82\xa9\x82\xb5\x82\xa2\0\0\0";
__declspec(section ".rodata") const u32 gap_04_802EFEB4_rodata = 0x00000000;
__declspec(section ".sdata2") const f32 float_2_8041c450 = 2.0f;
__declspec(section ".sdata2") const f32 float_0_8041c454 = 0.0f;
__declspec(section ".sdata2") const f32 float_0p25_8041c458 = 0.25f;
__declspec(section ".sdata2") const f32 float_600_8041c45c = 600.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041c460 = 0.5f;
__declspec(section ".sdata2") const f32 float_100_8041c464 = 100.0f;
__declspec(section ".sdata2") const f32 float_neg100_8041c468 = -100.0f;
__declspec(section ".sdata2") const f32 float_1p5_8041c46c = 1.5f;
__declspec(section ".sdata2") const f32 float_1_8041c470 = 1.0f;
__declspec(section ".sdata2") const f32 float_15_8041c474 = 15.0f;
__declspec(section ".sdata2") const f32 float_5_8041c478 = 5.0f;
__declspec(section ".sdata2") const f32 float_200_8041c47c = 200.0f;
__declspec(section ".sdata2") const f32 float_110_8041c480 = 110.0f;
__declspec(section ".sdata2") const f32 float_750_8041c484 = 750.0f;
__declspec(section ".sdata2") const f32 float_60_8041c488 = 60.0f;
__declspec(section ".sdata2") const f32 float_160_8041c48c = 160.0f;
__declspec(section ".sdata2") const f32 float_neg750_8041c490 = -750.0f;
__declspec(section ".sdata2") const f32 float_400_8041c494 = 400.0f;
__declspec(section ".sdata2") const f32 float_neg617_8041c498 = -617.0f;
__declspec(section ".sdata2") const f32 float_830_8041c49c = 830.0f;
__declspec(section ".sdata2") const f32 float_920_8041c4a0 = 920.0f;
__declspec(section ".sdata2") const f32 float_1000_8041c4a4 = 1000.0f;
__declspec(section ".sdata2") const f32 float_50_8041c4a8 = 50.0f;
__declspec(section ".sdata2") const f32 float_24_8041c4ac = 24.0f;
__declspec(section ".sdata2") const f32 float_9_8041c4b0 = 9.0f;
__declspec(section ".sdata2") const f32 float_80_8041c4b4 = 80.0f;
__declspec(section ".sdata2") const f32 float_10_8041c4b8 = 10.0f;
__declspec(section ".sdata2") const f32 float_1Eneg05_8041c4bc = 0.00001f;
__declspec(section ".sdata2") const f32 float_neg30_8041c4c0 = -30.0f;
__declspec(section ".sdata2") const f32 float_125_8041c4c4 = 125.0f;
__declspec(section ".sdata2") const f32 float_500_8041c4c8 = 500.0f;
__declspec(section ".sdata2") const f32 float_20_8041c4cc = 20.0f;
__declspec(section ".sdata2") const f32 float_350_8041c4d0 = 350.0f;
__declspec(section ".sdata2") const u32 gap_09_8041C4D4_sdata2[1] = {0};

// jumptables last, as the target emitted them with their functions
__declspec(section ".data") void* jumptable_80362040[] = {
    (char*)battleCameraMain + 0x100,
    (char*)battleCameraMain + 0x14C,
    (char*)battleCameraMain + 0x1A8,
    (char*)battleCameraMain + 0x1F0,
    (char*)battleCameraMain + 0x320,
    (char*)battleCameraMain + 0x36C,
    (char*)battleCameraMain + 0x3B8,
    (char*)battleCameraMain + 0x450,
    (char*)battleCameraMain + 0x5AC,
    (char*)battleCameraMain + 0x7D8,
    (char*)battleCameraMain + 0x964,
    (char*)battleCameraMain + 0xAD8,
    (char*)battleCameraMain + 0xD24,
    (char*)battleCameraMain + 0xD84,
    (char*)battleCameraMain + 0xEF8,
    (char*)battleCameraMain + 0xFFC,
    (char*)battleCameraMain + 0x1054,
    (char*)battleCameraMain + 0x10AC,
    (char*)battleCameraMain + 0x10AC,
    (char*)battleCameraMain + 0x11C0,
    (char*)battleCameraMain + 0x11D0,
};
#endif
// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_05_80362094_data[1] = {0};
#ifdef NONMATCHING
__declspec(section ".sdata2") const u32 gap_09_8041C4D4_sdata2[1] = {0};
#endif
#ifndef NONMATCHING
#pragma force_active reset
#endif
