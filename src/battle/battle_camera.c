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
#endif

#ifdef NONMATCHING
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

#ifdef NONMATCHING
void battleCameraMoveTo(s32 mode, s32 clamp, f32 x, f32 y, f32 z, f32 atX, f32 atY, f32 atZ,
                        f32* dX, f32* dY, f32* dZ, f32* dAtX, f32* dAtY, f32* dAtZ) {
  CameraEntry* cam = camGetPtr(4);
  BattleWork* wp = _battleWorkPointer;
  BattleUnit* mario = BattleGetMarioPtr(wp);
  f32 half;

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

#ifdef NONMATCHING
f32 battleCameraGetPosMoveSpeed(void) {
  BattleWork* wp = _battleWorkPointer;
  f32 x = wp->cameraWork.moveSpeed.x;
  f32 y = wp->cameraWork.moveSpeed.y;
  f32 z = wp->cameraWork.moveSpeed.z;
  return sqrt(x * x + y * y + z * z);
}
#endif

#ifdef NONMATCHING
void btl_camera_set_prilimit(s32 pri) {
  _battleWorkPointer->cameraWork.priLimit = pri;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_set_prilimit) {
  btl_camera_set_prilimit(evtGetValue(event, event->args[0]));
  return 2;
}
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

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_set_mode) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  s32 val = evtGetValue(event, args[1]);
  btl_camera_set_mode(pri, val);
  return 2;
}
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
#endif

#ifdef NONMATCHING
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
}
#endif

#ifdef NONMATCHING
void btl_camera_set_zoom(s32 pri, f32 zoom) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    wp->cameraWork.zoom = zoom;
  }
}
#endif

#ifdef NONMATCHING
void btl_camera_add_zoom(s32 pri, f32 zoom) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    wp->cameraWork.zoom += zoom;
  }
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_set_zoom) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  btl_camera_set_zoom(pri, (s32)evtGetFloat(event, args[1]));
  return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_add_zoom) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  btl_camera_add_zoom(pri, (s32)evtGetFloat(event, args[1]));
  return 2;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_set_moveSpeedLv) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  s32 val = evtGetValue(event, args[1]);
  btl_camera_set_moveSpeedLv(pri, val);
  return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_set_zoomSpeedLv) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  s32 val = evtGetValue(event, args[1]);
  btl_camera_set_zoomSpeedLv(pri, val);
  return 2;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_set_moveto) {
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_shake_w) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  f32 a = evtGetValue(event, args[1]);
  f32 b = evtGetValue(event, args[2]);
  s32 frames = evtGetValue(event, args[3]);
  btl_camera_shake_w(pri, a, b, frames, evtGetValue(event, args[4]));
  return 2;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_shake_h) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  f32 a = evtGetValue(event, args[1]);
  f32 b = evtGetValue(event, args[2]);
  s32 frames = evtGetValue(event, args[3]);
  btl_camera_shake_h(pri, a, b, frames, evtGetValue(event, args[4]));
  return 2;
}
#endif

#ifdef NONMATCHING
void btl_camera_noshake(s32 pri) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    wp->cameraWork.flags &= ~1;
    wp->cameraWork.flags &= ~2;
  }
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_noshake) {
  btl_camera_noshake(evtGetValue(event, event->args[0]));
  return 2;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_nomove_x_onoff) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  s32 val = evtGetValue(event, args[1]);
  btl_camera_nomove_x_onoff(pri, val);
  return 2;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_nomove_y_onoff) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  s32 val = evtGetValue(event, args[1]);
  btl_camera_nomove_y_onoff(pri, val);
  return 2;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_nomove_z_onoff) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  s32 val = evtGetValue(event, args[1]);
  btl_camera_nomove_z_onoff(pri, val);
  return 2;
}
#endif

#ifdef NONMATCHING
void btl_camera_set_posoffset(s32 pri, f32 x, f32 y, f32 z) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    wp->cameraWork.flags |= 0x20;
    wp->cameraWork.position.x = x;
    wp->cameraWork.position.y = y;
    wp->cameraWork.position.z = z;
  }
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_set_posoffset) {
  s32* args = event->args;
  s32 pri = evtGetValue(event, args[0]);
  f32 x = evtGetFloat(event, args[1]);
  f32 y = evtGetFloat(event, args[2]);
  f32 z = evtGetFloat(event, args[3]);
  btl_camera_set_posoffset(pri, x, y, z);
  return 2;
}
#endif

#ifdef NONMATCHING
void btl_camera_off_posoffset_manual(s32 pri) {
  BattleWork* wp = _battleWorkPointer;
  if (pri >= wp->cameraWork.priLimit) {
    wp->cameraWork.flags &= ~0x20;
    wp->cameraWork.position.x = 0.0f;
    wp->cameraWork.position.y = 0.0f;
    wp->cameraWork.position.z = 0.0f;
  }
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_off_posoffset_manual) {
  btl_camera_off_posoffset_manual(evtGetValue(event, event->args[0]));
  return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_btl_camera_wait_move_end) {
  if (battleCameraGetPosMoveSpeed() >= 2.0f) {
    return 0;
  }
  return 2;
}
#endif

#ifndef NONMATCHING
// ASM-STOPGAP: battleCameraInit (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
#pragma force_active on // FAKE: keep asm-only-referenced data from being dead-stripped
__declspec(section ".rodata") const f32 vec3_802efc40[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802efc4c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802efc58[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802efc64[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802efc70[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802efc7c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802efc88[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802efc94[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802efca0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f64 double_to_int_802efcb0 = 4503601774854144;
__declspec(section ".rodata") const char str_802EFCB8[] = "\202\251\202\337\202\347\201@\202\305\202\323\202\247\202\351\202\306\000";
__declspec(section ".rodata") const char str_802EFCCC[] = "\202\251\202\337\202\347\201@\202\305\202\323\202\247\202\351\202\306\203Y\201[\203\200\000\000\000";
__declspec(section ".rodata") const char str_802EFCE8[] = "\202\251\202\337\202\347\201@\202\251\201[\202\273\202\351\202\252\202\244\202\246\202\311\000\000\000";
__declspec(section ".rodata") const char str_802EFD04[] = "\202\251\202\337\202\347\201@\202\323\202\350\201[\000";
__declspec(section ".rodata") const char str_802EFD14[] = "\202\251\202\337\202\347\201@\202\324\202\275\202\242\202\244\202\347\000";
__declspec(section ".rodata") const char str_802EFD28[] = "\202\251\202\337\202\347\201@\202\324\202\275\202\242\202\244\202\347\202Q\000\000\000";
__declspec(section ".rodata") const char str_802EFD40[] = "\202\251\202\337\202\347\201@\202\251\202\361\202\253\202\341\202\255\000";
__declspec(section ".rodata") const char str_802EFD54[] = "\202\251\202\337\202\347\201@\202\344\202\311\202\301\202\306\202\302\202\242\202\321\000";
__declspec(section ".rodata") const u32 gap_04_802EFD6C_rodata[1] = { 0x00000000 };
__declspec(section ".rodata") const f64 double_20_802efd70 = 20;
__declspec(section ".rodata") const f64 double_1_802efd78 = 1;
__declspec(section ".rodata") const char str_802EFD80[] = "\202\251\202\337\202\347\201@\202Q\202\344\202\311\202\301\202\306\202\251\202\361\202\302\202\242\202\321\000\000\000";
__declspec(section ".rodata") const char str_802EFDA0[] = "\202\251\202\337\202\347\201@\202\317\201[\202\302\202\302\202\242\202\321\000\000\000";
__declspec(section ".rodata") const char str_802EFDB8[] = "\202\251\202\337\202\347\201@\202Q\202\317\201[\202\302\202\251\202\361\202\302\202\242\202\321\000";
__declspec(section ".rodata") const char str_802EFDD4[] = "\202\251\202\337\202\347\201@\202\251\202\361\202\253\202\341\202\255\202\302\202\242\202\321\000\000\000";
__declspec(section ".rodata") const char str_802EFDF0[] = "\202\251\202\337\202\347\201@\202\344\202\311\202\301\202\306\202\251\202\361\202\253\202\341\202\255\202\251\202\361\202\302\202\242\202\321\000\000\000";
__declspec(section ".rodata") const char str_802EFE18[] = "\202\251\202\337\202\347\201@\202\323\202\302\202\244\202\311\202\315\202\242\202\301\202\275\000\000\000";
__declspec(section ".rodata") const char str_802EFE34[] = "\202\251\202\337\202\347\201@\202\244\202\334\202\255\202\315\202\242\202\301\202\275\000";
__declspec(section ".rodata") const char str_802EFE4C[] = "\202\251\202\337\202\347\201@\202\276\202\337\202\311\202\315\202\242\202\301\202\275\000";
__declspec(section ".rodata") const char str_802EFE64[] = "\202\251\202\337\202\347\201@\202\265\202\345\202\244\202\350\000\000\000";
__declspec(section ".rodata") const char str_802EFE78[] = "\202\251\202\337\202\347\201@\202\315\202\242\202\332\202\255\000\000\000";
__declspec(section ".rodata") const char str_802EFE8C[] = "\202\251\202\337\202\347\201@\202\311\202\260\202\304\202\351\000\000\000";
__declspec(section ".rodata") const char str_802EFEA0[] = "\202\251\202\337\202\347\201@\202\250\202\251\202\265\202\242\000\000\000";
__declspec(section ".rodata") const u32 gap_04_802EFEB4_rodata[1] = { 0x00000000 };
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

BattleAudience* BattleAudienceBaseGetPtr(void);
BattleUnit* BattleGetMarioPtr(BattleWork* work);
BattleUnit* BattleGetPartyPtr(BattleWork* wp);
BattleUnitPart* BattleGetUnitPartsPtr(s32 index, s32 partNum);
BattleUnit* BattleGetUnitPtr(BattleWork* wp, s32 index);
s32 BattleTransID(EventEntry* event, s32 type);
s32 BtlUnit_GetBodyPartsId(BattleUnit* unit);
s32 BtlUnit_GetHeight(BattleUnit* unit);
void BtlUnit_GetHitPos(BattleUnit* unit, BattleUnitPart* part, f32* x, f32* y, f32* z);
void BtlUnit_GetHomePos(BattleUnit* unit, f32* x, f32* y, f32* z);
void BtlUnit_GetPartsWorldPos(BattleUnitPart* part, f32* x, f32* y, f32* z);
void BtlUnit_GetPos(BattleUnit* unit, f32* x, f32* y, f32* z);
s32 BtlUnit_GetWidth(BattleUnit* unit);
void _restfpr_26();
void _savefpr_26();
void btl_camera_add_zoom(s32 pri, f32 zoom);
void btl_camera_noshake(s32 pri);
void btl_camera_off_posoffset_manual(s32 pri);
void btl_camera_set_moveSpeedLv(s32 pri, s32 lv);
void btl_camera_set_posoffset(s32 pri, f32 x, f32 y, f32 z);
void btl_camera_set_prilimit(s32 pri);
void btl_camera_set_zoom(s32 pri, f32 zoom);
void btl_camera_set_zoomSpeedLv(s32 pri, s32 lv);
void btl_camera_shake_h(s32 pri, f32 a, f32 b, s32 frames, s32 type);
void btl_camera_shake_w(s32 pri, f32 a, f32 b, s32 frames, s32 type);
CameraEntry* camGetPtr(CameraId cameraId);
f32 evtGetFloat(EventEntry* entry, s32 index);
s32 evtGetValue(EventEntry* entry, s32 index);
f32 intplGetValue(s32 mode, s32 currStep, s32 steps, f32 start, f32 end);
void *memset(void *dest, int ch, size_t count);
void padRumbleOff(u32 chan);
void padRumbleOn(u32 chan);
PouchData* pouchGetPtr(void);
char *strcpy(char *dest, const char *src);
asm s32 evt_btl_camera_wait_move_end(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl battleCameraGetPosMoveSpeed
	lfs f0, float_2_8041c450(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @1
	li r3, 0x0
	b @2
	@1:
	li r3, 0x2
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_btl_camera_off_posoffset_manual(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	bl btl_camera_off_posoffset_manual
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

void battleCameraMain(void);
__declspec(section ".data") static void* jumptable_80362040[] = {
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
asm void btl_camera_off_posoffset_manual(s32 pri) {
	nofralloc
	lwz r4, _battleWorkPointer(r13)
	lwz r0, 0x275c(r4)
	cmpw r3, r0
	bltlr
	lwz r0, 0x2754(r4)
	lfs f0, float_0_8041c454(r2)
	rlwinm r0, r0, 0, 27, 25
	stw r0, 0x2754(r4)
	stfs f0, 0x27b0(r4)
	stfs f0, 0x27b4(r4)
	stfs f0, 0x27b8(r4)
	blr
}

asm s32 evt_btl_camera_set_posoffset(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x28(r1)
	stfd f30, 0x20(r1)
	stmw r29, 0x14(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r30, r3
	mr r3, r29
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r31)
	mr r3, r29
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r31)
	mr r3, r29
	bl evtGetFloat
	fmr f0, f1
	mr r3, r30
	fmr f1, f31
	fmr f2, f30
	fmr f3, f0
	bl btl_camera_set_posoffset
	lfd f31, 0x28(r1)
	li r3, 0x2
	lfd f30, 0x20(r1)
	lmw r29, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void btl_camera_set_posoffset(s32 pri, f32 x, f32 y, f32 z) {
	nofralloc
	lwz r4, _battleWorkPointer(r13)
	lwz r0, 0x275c(r4)
	cmpw r3, r0
	bltlr
	lwz r0, 0x2754(r4)
	ori r0, r0, 0x20
	stw r0, 0x2754(r4)
	stfs f1, 0x27b0(r4)
	stfs f2, 0x27b4(r4)
	stfs f3, 0x27b8(r4)
	blr
}

asm s32 evt_btl_camera_nomove_z_onoff(EventEntry* event, BOOL isFirstCall) {
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
	mr r0, r3
	mr r3, r31
	mr r4, r0
	bl btl_camera_nomove_z_onoff
	lmw r30, 0x8(r1)
	li r3, 0x2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void btl_camera_nomove_z_onoff(s32 pri, s32 on) {
	nofralloc
	lwz r5, _battleWorkPointer(r13)
	lwz r0, 0x275c(r5)
	cmpw r3, r0
	bltlr
	cmpwi r4, 0x1
	bne @1
	lwz r0, 0x2754(r5)
	ori r0, r0, 0x10
	stw r0, 0x2754(r5)
	blr
	@1:
	lwz r0, 0x2754(r5)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x2754(r5)
	blr
}

asm s32 evt_btl_camera_nomove_y_onoff(EventEntry* event, BOOL isFirstCall) {
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
	mr r0, r3
	mr r3, r31
	mr r4, r0
	bl btl_camera_nomove_y_onoff
	lmw r30, 0x8(r1)
	li r3, 0x2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void btl_camera_nomove_y_onoff(s32 pri, s32 on) {
	nofralloc
	lwz r5, _battleWorkPointer(r13)
	lwz r0, 0x275c(r5)
	cmpw r3, r0
	bltlr
	cmpwi r4, 0x1
	bne @1
	lwz r0, 0x2754(r5)
	ori r0, r0, 0x8
	stw r0, 0x2754(r5)
	blr
	@1:
	lwz r0, 0x2754(r5)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x2754(r5)
	blr
}

asm s32 evt_btl_camera_nomove_x_onoff(EventEntry* event, BOOL isFirstCall) {
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
	mr r0, r3
	mr r3, r31
	mr r4, r0
	bl btl_camera_nomove_x_onoff
	lmw r30, 0x8(r1)
	li r3, 0x2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void btl_camera_nomove_x_onoff(s32 pri, s32 on) {
	nofralloc
	lwz r5, _battleWorkPointer(r13)
	lwz r0, 0x275c(r5)
	cmpw r3, r0
	bltlr
	cmpwi r4, 0x1
	bne @1
	lwz r0, 0x2754(r5)
	ori r0, r0, 0x4
	stw r0, 0x2754(r5)
	blr
	@1:
	lwz r0, 0x2754(r5)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x2754(r5)
	blr
}

asm s32 evt_btl_camera_noshake(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	bl btl_camera_noshake
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void btl_camera_noshake(s32 pri) {
	nofralloc
	lwz r4, _battleWorkPointer(r13)
	lwz r0, 0x275c(r4)
	cmpw r3, r0
	bltlr
	lwz r0, 0x2754(r4)
	clrrwi r0, r0, 1
	stw r0, 0x2754(r4)
	lwz r0, 0x2754(r4)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x2754(r4)
	blr
}

asm s32 evt_btl_camera_shake_h(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stfd f30, 0x30(r1)
	psq_st f30, 0x38(r1), 0, 0
	stmw r29, 0x24(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r30, r3
	mr r3, r29
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802efcb0@ha
	stw r3, 0xc(r1)
	addi r5, r4, double_to_int_802efcb0@l
	lwz r4, 0x8(r31)
	stw r0, 0x8(r1)
	mr r3, r29
	lfd f1, 0x0(r5)
	lfd f0, 0x8(r1)
	fsubs f31, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802efcb0@ha
	stw r3, 0x14(r1)
	addi r5, r4, double_to_int_802efcb0@l
	lwz r4, 0xc(r31)
	stw r0, 0x10(r1)
	mr r3, r29
	lfd f1, 0x0(r5)
	lfd f0, 0x10(r1)
	fsubs f30, f0, f1
	bl evtGetValue
	lwz r4, 0x10(r31)
	mr r31, r3
	mr r3, r29
	bl evtGetValue
	fmr f1, f31
	mr r5, r3
	fmr f2, f30
	mr r3, r30
	mr r4, r31
	bl btl_camera_shake_h
	li r3, 0x2
	psq_l f31, 0x48(r1), 0, 0
	lfd f31, 0x40(r1)
	psq_l f30, 0x38(r1), 0, 0
	lfd f30, 0x30(r1)
	lmw r29, 0x24(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void btl_camera_shake_h(s32 pri, f32 a, f32 b, s32 frames, s32 type) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r6, _battleWorkPointer(r13)
	lwz r0, 0x275c(r6)
	cmpw r3, r0
	blt @1
	lwz r0, 0x2754(r6)
	ori r0, r0, 0x2
	stw r0, 0x2754(r6)
	stfs f1, 0x2848(r6)
	stfs f2, 0x284c(r6)
	stw r5, 0x282c(r6)
	stw r4, 0x2834(r6)
	stw r4, 0x283c(r6)
	lwz r0, 0x2754(r6)
	rlwinm. r0, r0, 0, 25, 25
	bne @1
	li r3, 0x0
	bl padRumbleOn
	@1:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_btl_camera_shake_w(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stfd f30, 0x30(r1)
	psq_st f30, 0x38(r1), 0, 0
	stmw r29, 0x24(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r30, r3
	mr r3, r29
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802efcb0@ha
	stw r3, 0xc(r1)
	addi r5, r4, double_to_int_802efcb0@l
	lwz r4, 0x8(r31)
	stw r0, 0x8(r1)
	mr r3, r29
	lfd f1, 0x0(r5)
	lfd f0, 0x8(r1)
	fsubs f31, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802efcb0@ha
	stw r3, 0x14(r1)
	addi r5, r4, double_to_int_802efcb0@l
	lwz r4, 0xc(r31)
	stw r0, 0x10(r1)
	mr r3, r29
	lfd f1, 0x0(r5)
	lfd f0, 0x10(r1)
	fsubs f30, f0, f1
	bl evtGetValue
	lwz r4, 0x10(r31)
	mr r31, r3
	mr r3, r29
	bl evtGetValue
	fmr f1, f31
	mr r5, r3
	fmr f2, f30
	mr r3, r30
	mr r4, r31
	bl btl_camera_shake_w
	li r3, 0x2
	psq_l f31, 0x48(r1), 0, 0
	lfd f31, 0x40(r1)
	psq_l f30, 0x38(r1), 0, 0
	lfd f30, 0x30(r1)
	lmw r29, 0x24(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void btl_camera_shake_w(s32 pri, f32 a, f32 b, s32 frames, s32 type) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r6, _battleWorkPointer(r13)
	lwz r0, 0x275c(r6)
	cmpw r3, r0
	blt @1
	lwz r0, 0x2754(r6)
	ori r0, r0, 0x1
	stw r0, 0x2754(r6)
	stfs f1, 0x2840(r6)
	stfs f2, 0x2844(r6)
	stw r5, 0x2828(r6)
	stw r4, 0x2830(r6)
	stw r4, 0x2838(r6)
	lwz r0, 0x2754(r6)
	rlwinm. r0, r0, 0, 25, 25
	bne @1
	li r3, 0x0
	bl padRumbleOn
	@1:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_btl_camera_set_moveto(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	addi r11, r1, 0x50
	bl _savefpr_26
	stmw r29, 0x14(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r30, r3
	mr r3, r29
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r31)
	mr r3, r29
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r31)
	mr r3, r29
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x10(r31)
	mr r3, r29
	bl evtGetFloat
	fmr f28, f1
	lwz r4, 0x14(r31)
	mr r3, r29
	bl evtGetFloat
	fmr f27, f1
	lwz r4, 0x18(r31)
	mr r3, r29
	bl evtGetFloat
	fmr f26, f1
	lwz r4, 0x1c(r31)
	mr r3, r29
	bl evtGetValue
	lwz r4, 0x20(r31)
	mr r31, r3
	mr r3, r29
	bl evtGetValue
	fmr f1, f31
	mr r5, r3
	fmr f2, f30
	mr r3, r30
	fmr f3, f29
	mr r4, r31
	fmr f4, f28
	fmr f5, f27
	fmr f6, f26
	bl btl_camera_set_moveto
	li r3, 0x2
	addi r11, r1, 0x50
	bl _restfpr_26
	lmw r29, 0x14(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void btl_camera_set_moveto(s32 pri, f32 x, f32 y, f32 z, f32 atX, f32 atY, f32 atZ, s32 frames,
                           s32 type) {
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
	stfd f27, 0x30(r1)
	psq_st f27, 0x38(r1), 0, 0
	stfd f26, 0x20(r1)
	psq_st f26, 0x28(r1), 0, 0
	stmw r28, 0x10(r1)
	fmr f26, f1
	mr r28, r3
	fmr f27, f2
	lwz r31, _battleWorkPointer(r13)
	fmr f28, f3
	mr r29, r4
	fmr f29, f4
	mr r30, r5
	fmr f30, f5
	li r3, 0x4
	fmr f31, f6
	bl camGetPtr
	lwz r0, 0x275c(r31)
	cmpw r28, r0
	blt @1
	lfs f0, 0xc(r3)
	stfs f0, 0x27e0(r31)
	lfs f0, 0x10(r3)
	stfs f0, 0x27e4(r31)
	lfs f0, 0x14(r3)
	stfs f0, 0x27e8(r31)
	stfs f26, 0x27ec(r31)
	stfs f27, 0x27f0(r31)
	stfs f28, 0x27f4(r31)
	lfs f0, 0x18(r3)
	stfs f0, 0x27f8(r31)
	lfs f0, 0x1c(r3)
	stfs f0, 0x27fc(r31)
	lfs f0, 0x20(r3)
	stfs f0, 0x2800(r31)
	stfs f29, 0x2804(r31)
	stfs f30, 0x2808(r31)
	stfs f31, 0x280c(r31)
	stw r29, 0x27d8(r31)
	stw r29, 0x27dc(r31)
	stw r30, 0x27d4(r31)
	@1:
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	psq_l f30, 0x68(r1), 0, 0
	lfd f30, 0x60(r1)
	psq_l f29, 0x58(r1), 0, 0
	lfd f29, 0x50(r1)
	psq_l f28, 0x48(r1), 0, 0
	lfd f28, 0x40(r1)
	psq_l f27, 0x38(r1), 0, 0
	lfd f27, 0x30(r1)
	psq_l f26, 0x28(r1), 0, 0
	lfd f26, 0x20(r1)
	lmw r28, 0x10(r1)
	lwz r0, 0x84(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm s32 evt_btl_camera_set_zoomSpeedLv(EventEntry* event, BOOL isFirstCall) {
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
	mr r0, r3
	mr r3, r31
	mr r4, r0
	bl btl_camera_set_zoomSpeedLv
	lmw r30, 0x8(r1)
	li r3, 0x2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_btl_camera_set_moveSpeedLv(EventEntry* event, BOOL isFirstCall) {
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
	mr r0, r3
	mr r3, r31
	mr r4, r0
	bl btl_camera_set_moveSpeedLv
	lmw r30, 0x8(r1)
	li r3, 0x2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void btl_camera_set_zoomSpeedLv(s32 pri, s32 lv) {
	nofralloc
	lwz r5, _battleWorkPointer(r13)
	lwz r0, 0x275c(r5)
	cmpw r3, r0
	bltlr
	cmpwi r4, 0x0
	blt @1
	cmpwi r4, 0x5
	bgt @1
	sth r4, 0x277e(r5)
	blr
	@1:
	li r0, 0x1
	sth r0, 0x277e(r5)
	blr
}

asm void btl_camera_set_moveSpeedLv(s32 pri, s32 lv) {
	nofralloc
	lwz r5, _battleWorkPointer(r13)
	lwz r0, 0x275c(r5)
	cmpw r3, r0
	bltlr
	cmpwi r4, 0x0
	blt @1
	cmpwi r4, 0x5
	bgt @1
	sth r4, 0x277c(r5)
	b @2
	@1:
	li r0, 0x1
	sth r0, 0x277c(r5)
	@2:
	lha r0, 0x277c(r5)
	sth r0, 0x277e(r5)
	blr
}

asm s32 evt_btl_camera_add_zoom(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r30, 0x18(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r30
	bl evtGetFloat
	fctiwz f0, f1
	lis r0, 0x4330
	lis r3, double_to_int_802efcb0@ha
	stw r0, 0x10(r1)
	addi r4, r3, double_to_int_802efcb0@l
	stfd f0, 0x8(r1)
	lfd f1, 0x0(r4)
	mr r3, r31
	lwz r0, 0xc(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x14(r1)
	lfd f0, 0x10(r1)
	fsubs f1, f0, f1
	bl btl_camera_add_zoom
	lmw r30, 0x18(r1)
	li r3, 0x2
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_btl_camera_set_zoom(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r30, 0x18(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r30
	bl evtGetFloat
	fctiwz f0, f1
	lis r0, 0x4330
	lis r3, double_to_int_802efcb0@ha
	stw r0, 0x10(r1)
	addi r4, r3, double_to_int_802efcb0@l
	stfd f0, 0x8(r1)
	lfd f1, 0x0(r4)
	mr r3, r31
	lwz r0, 0xc(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x14(r1)
	lfd f0, 0x10(r1)
	fsubs f1, f0, f1
	bl btl_camera_set_zoom
	lmw r30, 0x18(r1)
	li r3, 0x2
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void btl_camera_add_zoom(s32 pri, f32 zoom) {
	nofralloc
	lwz r4, _battleWorkPointer(r13)
	lwz r0, 0x275c(r4)
	cmpw r3, r0
	bltlr
	lfs f0, 0x2778(r4)
	fadds f0, f0, f1
	stfs f0, 0x2778(r4)
	blr
}

asm void btl_camera_set_zoom(s32 pri, f32 zoom) {
	nofralloc
	lwz r4, _battleWorkPointer(r13)
	lwz r0, 0x275c(r4)
	cmpw r3, r0
	bltlr
	stfs f1, 0x2778(r4)
	blr
}

asm s32 evt_btl_camera_set_homing_unit_audience(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stmw r25, 0x44(r1)
	mr r25, r3
	lwz r28, 0x18(r3)
	lwz r4, 0x0(r28)
	bl evtGetValue
	lwz r4, 0x4(r28)
	mr r27, r3
	mr r3, r25
	bl evtGetValue
	lwz r4, 0x8(r28)
	mr r26, r3
	mr r3, r25
	bl evtGetValue
	lwz r4, 0xc(r28)
	mr r28, r3
	mr r3, r25
	bl evtGetValue
	lwz r30, _battleWorkPointer(r13)
	mr r31, r3
	bl BattleAudienceBaseGetPtr
	lwz r0, 0x275c(r30)
	mr r29, r3
	cmpw r27, r0
	bge @1
	li r3, 0x2
	b @2
	@1:
	mr r3, r25
	mr r4, r26
	bl BattleTransID
	stw r3, 0x2764(r30)
	mr r3, r30
	stw r28, 0x276c(r30)
	lwz r4, 0x2764(r30)
	bl BattleGetUnitPtr
	mr r0, r3
	lwz r3, 0x2764(r30)
	lwz r4, 0x276c(r30)
	mr r26, r0
	bl BattleGetUnitPartsPtr
	mr r0, r3
	addi r5, r1, 0x30
	addi r6, r1, 0x34
	mr r3, r26
	mr r27, r0
	addi r4, r1, 0x2c
	bl BtlUnit_GetPos
	mr r3, r26
	mr r4, r27
	addi r5, r1, 0x20
	addi r6, r1, 0x24
	addi r7, r1, 0x28
	bl BtlUnit_GetHitPos
	lis r4, vec3_802efc94@ha
	lis r3, vec3_802efca0@ha
	addi r7, r4, vec3_802efc94@l
	lfs f0, 0x2c(r1)
	lwz r0, 0x0(r7)
	mulli r4, r31, 0x134
	lwz r5, 0x4(r7)
	addi r6, r3, vec3_802efca0@l
	stw r0, 0x14(r1)
	li r3, 0x2
	lwz r0, 0x8(r7)
	stfs f0, 0x14(r1)
	addi r7, r4, 0x1bc
	lfs f1, 0x30(r1)
	add r7, r29, r7
	stw r5, 0x18(r1)
	lfs f0, 0x34(r1)
	stw r0, 0x1c(r1)
	lwz r0, 0x14(r1)
	stfs f1, 0x18(r1)
	stfs f0, 0x1c(r1)
	lwz r4, 0x18(r1)
	stw r0, 0x2810(r30)
	lwz r0, 0x1c(r1)
	stw r4, 0x2814(r30)
	stw r0, 0x2818(r30)
	stw r31, 0x2774(r30)
	lwz r5, 0x0(r6)
	lwz r4, 0x4(r6)
	lwz r0, 0x8(r6)
	stw r5, 0x8(r1)
	lfs f0, 0x48(r7)
	stw r4, 0xc(r1)
	lfs f1, 0x4c(r7)
	stfs f0, 0x8(r1)
	lfs f0, 0x50(r7)
	stw r0, 0x10(r1)
	lwz r0, 0x8(r1)
	stfs f1, 0xc(r1)
	stfs f0, 0x10(r1)
	lwz r4, 0xc(r1)
	stw r0, 0x281c(r30)
	lwz r0, 0x10(r1)
	stw r4, 0x2820(r30)
	stw r0, 0x2824(r30)
	@2:
	lmw r25, 0x44(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm s32 evt_btl_camera_set_homing_unitparts(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stmw r25, 0x44(r1)
	mr r29, r3
	lwz r28, 0x18(r3)
	lwz r4, 0x0(r28)
	bl evtGetValue
	lwz r4, 0x4(r28)
	mr r26, r3
	mr r3, r29
	bl evtGetValue
	lwz r4, 0x8(r28)
	mr r25, r3
	mr r3, r29
	bl evtGetValue
	lwz r4, 0xc(r28)
	mr r27, r3
	mr r3, r29
	bl evtGetValue
	lwz r4, 0x10(r28)
	mr r30, r3
	mr r3, r29
	bl evtGetValue
	lwz r31, _battleWorkPointer(r13)
	mr r28, r3
	lwz r0, 0x275c(r31)
	cmpw r26, r0
	bge @1
	li r3, 0x2
	b @2
	@1:
	mr r3, r29
	mr r4, r25
	bl BattleTransID
	stw r3, 0x2764(r31)
	mr r3, r31
	stw r27, 0x276c(r31)
	lwz r4, 0x2764(r31)
	bl BattleGetUnitPtr
	mr r26, r3
	lwz r3, 0x2764(r31)
	lwz r4, 0x276c(r31)
	bl BattleGetUnitPartsPtr
	addi r5, r1, 0x30
	addi r6, r1, 0x34
	mr r3, r26
	addi r4, r1, 0x2c
	bl BtlUnit_GetHomePos
	lis r3, vec3_802efc7c@ha
	lfs f2, 0x2c(r1)
	addi r4, r3, vec3_802efc7c@l
	lfs f1, 0x30(r1)
	lwz r0, 0x0(r4)
	cmpwi r30, -0x1
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
	beq @3
	mr r3, r29
	mr r4, r30
	bl BattleTransID
	stw r3, 0x2768(r31)
	mr r3, r31
	stw r28, 0x2770(r31)
	lwz r4, 0x2768(r31)
	bl BattleGetUnitPtr
	mr r26, r3
	lwz r3, 0x2768(r31)
	lwz r4, 0x2770(r31)
	bl BattleGetUnitPartsPtr
	mr r4, r3
	addi r6, r1, 0x24
	addi r7, r1, 0x28
	mr r3, r26
	addi r5, r1, 0x20
	bl BtlUnit_GetHitPos
	lis r3, vec3_802efc88@ha
	lfs f2, 0x20(r1)
	addi r4, r3, vec3_802efc88@l
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
	@3:
	li r3, 0x2
	@2:
	lmw r25, 0x44(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

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
	beq @1
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
	@1:
	lmw r28, 0x40(r1)
	li r3, 0x2
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm s32 evt_btl_camera_set_mode(EventEntry* event, BOOL isFirstCall) {
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
	mr r0, r3
	mr r3, r31
	mr r4, r0
	bl btl_camera_set_mode
	lmw r30, 0x8(r1)
	li r3, 0x2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void btl_camera_set_mode(s32 pri, s32 mode) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r31, _battleWorkPointer(r13)
	lwz r0, 0x275c(r31)
	cmpw r3, r0
	blt @1
	stw r4, 0x2760(r31)
	li r5, 0x1
	lfs f0, float_0_8041c454(r2)
	li r0, 0x0
	li r3, 0x0
	li r4, 0x0
	stfs f0, 0x2778(r31)
	sth r5, 0x277c(r31)
	sth r5, 0x277e(r31)
	stw r0, 0x2758(r31)
	bl btl_camera_nomove_x_onoff
	li r3, 0x0
	li r4, 0x0
	bl btl_camera_nomove_y_onoff
	li r3, 0x0
	li r4, 0x0
	bl btl_camera_nomove_z_onoff
	lwz r0, 0x2754(r31)
	rlwinm r0, r0, 0, 27, 25
	stw r0, 0x2754(r31)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_btl_camera_set_prilimit(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	bl btl_camera_set_prilimit
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void btl_camera_set_prilimit(s32 pri) {
	nofralloc
	lwz r4, _battleWorkPointer(r13)
	stw r3, 0x275c(r4)
	blr
}

asm f32 battleCameraGetPosMoveSpeed(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r3, _battleWorkPointer(r13)
	lfs f0, 0x27c0(r3)
	lfs f1, 0x27bc(r3)
	fmuls f0, f0, f0
	lfs f2, 0x27c4(r3)
	fmadds f0, f1, f1, f0
	fmadds f1, f2, f2, f0
	bl sqrt
	lwz r0, 0x14(r1)
	frsp f1, f1
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void battleCameraMoveTo(s32 mode, s32 clamp, f32 x, f32 y, f32 z, f32 atX, f32 atY, f32 atZ,
                        f32* dX, f32* dY, f32* dZ, f32* dAtX, f32* dAtY, f32* dAtZ) {
	nofralloc
	stwu r1, -0x90(r1)
	mflr r0
	stw r0, 0x94(r1)
	stfd f31, 0x80(r1)
	psq_st f31, 0x88(r1), 0, 0
	stfd f30, 0x70(r1)
	psq_st f30, 0x78(r1), 0, 0
	stfd f29, 0x60(r1)
	psq_st f29, 0x68(r1), 0, 0
	stfd f28, 0x50(r1)
	psq_st f28, 0x58(r1), 0, 0
	stfd f27, 0x40(r1)
	psq_st f27, 0x48(r1), 0, 0
	stfd f26, 0x30(r1)
	psq_st f26, 0x38(r1), 0, 0
	stmw r22, 0x8(r1)
	fmr f26, f1
	mr r22, r3
	fmr f27, f2
	mr r23, r4
	fmr f28, f3
	mr r24, r5
	fmr f29, f4
	mr r25, r6
	fmr f30, f5
	mr r26, r7
	fmr f31, f6
	mr r27, r8
	mr r28, r9
	mr r29, r10
	li r3, 0x4
	bl camGetPtr
	lwz r30, _battleWorkPointer(r13)
	mr r31, r3
	mr r3, r30
	bl BattleGetMarioPtr
	lha r4, 0x277c(r30)
	extsh. r0, r4
	blt @1
	cmpwi r4, 0x5
	blt @2
	@1:
	li r0, 0x1
	sth r0, 0x277c(r30)
	@2:
	lha r4, 0x277e(r30)
	extsh. r0, r4
	blt @3
	cmpwi r4, 0x6
	blt @4
	@3:
	li r0, 0x1
	sth r0, 0x277e(r30)
	@4:
	cmpwi r22, 0x1
	bne @5
	lwz r0, 0xef4(r30)
	rlwinm. r0, r0, 0, 23, 23
	beq @6
	lfs f3, 0x38(r3)
	lfs f0, float_0_8041c454(r2)
	fneg f1, f3
	lfs f2, float_0p25_8041c458(r2)
	fadds f26, f26, f0
	fadds f28, f28, f3
	fmuls f1, f2, f1
	fadds f29, f29, f0
	fadds f31, f31, f3
	fadds f27, f27, f1
	fadds f30, f30, f1
	@6:
	lfs f0, 0x27b0(r30)
	lfs f1, 0x27b4(r30)
	lfs f2, 0x27b8(r30)
	fadds f26, f26, f0
	fadds f27, f27, f1
	fadds f28, f28, f2
	fadds f29, f29, f0
	fadds f30, f30, f1
	fadds f31, f31, f2
	@5:
	lfs f0, float_600_8041c45c(r2)
	lfs f1, float_0p5_8041c460(r2)
	fsubs f2, f0, f28
	lfs f0, float_0_8041c454(r2)
	fmuls f2, f2, f1
	fcmpo cr0, f2, f0
	bge @7
	fmr f2, f0
	@7:
	cmpwi r23, 0x1
	bne @8
	lfs f0, float_100_8041c464(r2)
	fadds f1, f0, f2
	fcmpo cr0, f26, f1
	ble @9
	fmr f26, f1
	@9:
	lfs f0, float_neg100_8041c468(r2)
	fsubs f0, f0, f2
	fcmpo cr0, f26, f0
	bge @10
	fmr f26, f0
	@10:
	fcmpo cr0, f29, f1
	ble @11
	fmr f29, f1
	@11:
	fcmpo cr0, f29, f0
	bge @8
	fmr f29, f0
	@8:
	lha r0, 0x277c(r30)
	cmpwi r0, 0x3
	beq @12
	bge @13
	cmpwi r0, 0x1
	beq @14
	bge @15
	cmpwi r0, 0x0
	bge @16
	b @17
	@13:
	cmpwi r0, 0x5
	beq @18
	bge @17
	b @19
	@16:
	lfs f0, 0xc(r31)
	lfs f3, float_1p5_8041c46c(r2)
	fsubs f2, f26, f0
	lfs f1, float_0_8041c454(r2)
	lfs f0, float_1_8041c470(r2)
	fdivs f2, f2, f3
	stfs f2, 0x0(r24)
	lfs f2, 0x10(r31)
	fsubs f2, f27, f2
	fdivs f2, f2, f3
	stfs f2, 0x0(r25)
	lfs f2, 0x18(r31)
	fsubs f2, f29, f2
	fdivs f2, f2, f3
	stfs f2, 0x0(r27)
	lfs f2, 0x1c(r31)
	fsubs f2, f30, f2
	fdivs f2, f2, f3
	stfs f2, 0x0(r28)
	lfs f3, 0xc(r31)
	lfs f2, 0x0(r24)
	fadds f2, f3, f2
	stfs f2, 0xc(r31)
	lfs f3, 0x10(r31)
	lfs f2, 0x0(r25)
	fadds f2, f3, f2
	stfs f2, 0x10(r31)
	lfs f3, 0x18(r31)
	lfs f2, 0x0(r27)
	fadds f2, f3, f2
	stfs f2, 0x18(r31)
	lfs f3, 0x1c(r31)
	lfs f2, 0x0(r28)
	fadds f2, f3, f2
	stfs f2, 0x1c(r31)
	stfs f1, 0x24(r31)
	stfs f0, 0x28(r31)
	stfs f1, 0x2c(r31)
	b @17
	@14:
	lfs f0, 0xc(r31)
	lfs f3, float_15_8041c474(r2)
	fsubs f2, f26, f0
	lfs f1, float_0_8041c454(r2)
	lfs f0, float_1_8041c470(r2)
	fdivs f2, f2, f3
	stfs f2, 0x0(r24)
	lfs f2, 0x10(r31)
	fsubs f2, f27, f2
	fdivs f2, f2, f3
	stfs f2, 0x0(r25)
	lfs f2, 0x18(r31)
	fsubs f2, f29, f2
	fdivs f2, f2, f3
	stfs f2, 0x0(r27)
	lfs f2, 0x1c(r31)
	fsubs f2, f30, f2
	fdivs f2, f2, f3
	stfs f2, 0x0(r28)
	lfs f3, 0xc(r31)
	lfs f2, 0x0(r24)
	fadds f2, f3, f2
	stfs f2, 0xc(r31)
	lfs f3, 0x10(r31)
	lfs f2, 0x0(r25)
	fadds f2, f3, f2
	stfs f2, 0x10(r31)
	lfs f3, 0x14(r31)
	lfs f2, 0x0(r26)
	fadds f2, f3, f2
	stfs f2, 0x14(r31)
	lfs f3, 0x18(r31)
	lfs f2, 0x0(r27)
	fadds f2, f3, f2
	stfs f2, 0x18(r31)
	lfs f3, 0x1c(r31)
	lfs f2, 0x0(r28)
	fadds f2, f3, f2
	stfs f2, 0x1c(r31)
	stfs f1, 0x24(r31)
	stfs f0, 0x28(r31)
	stfs f1, 0x2c(r31)
	b @17
	@15:
	lfs f0, 0xc(r31)
	lfs f3, float_5_8041c478(r2)
	fsubs f2, f26, f0
	lfs f1, float_0_8041c454(r2)
	lfs f0, float_1_8041c470(r2)
	fdivs f2, f2, f3
	stfs f2, 0x0(r24)
	lfs f2, 0x10(r31)
	fsubs f2, f27, f2
	fdivs f2, f2, f3
	stfs f2, 0x0(r25)
	lfs f2, 0x18(r31)
	fsubs f2, f29, f2
	fdivs f2, f2, f3
	stfs f2, 0x0(r27)
	lfs f2, 0x1c(r31)
	fsubs f2, f30, f2
	fdivs f2, f2, f3
	stfs f2, 0x0(r28)
	lfs f3, 0xc(r31)
	lfs f2, 0x0(r24)
	fadds f2, f3, f2
	stfs f2, 0xc(r31)
	lfs f3, 0x10(r31)
	lfs f2, 0x0(r25)
	fadds f2, f3, f2
	stfs f2, 0x10(r31)
	lfs f3, 0x18(r31)
	lfs f2, 0x0(r27)
	fadds f2, f3, f2
	stfs f2, 0x18(r31)
	lfs f3, 0x1c(r31)
	lfs f2, 0x0(r28)
	fadds f2, f3, f2
	stfs f2, 0x1c(r31)
	stfs f1, 0x24(r31)
	stfs f0, 0x28(r31)
	stfs f1, 0x2c(r31)
	b @17
	@12:
	lfs f0, 0xc(r31)
	lfs f1, float_0_8041c454(r2)
	fsubs f2, f26, f0
	lfs f0, float_1_8041c470(r2)
	stfs f2, 0x0(r24)
	lfs f2, 0x10(r31)
	fsubs f2, f27, f2
	stfs f2, 0x0(r25)
	lfs f2, 0x18(r31)
	fsubs f2, f29, f2
	stfs f2, 0x0(r27)
	lfs f2, 0x1c(r31)
	fsubs f2, f30, f2
	stfs f2, 0x0(r28)
	lfs f3, 0xc(r31)
	lfs f2, 0x0(r24)
	fadds f2, f3, f2
	stfs f2, 0xc(r31)
	lfs f3, 0x10(r31)
	lfs f2, 0x0(r25)
	fadds f2, f3, f2
	stfs f2, 0x10(r31)
	lfs f3, 0x18(r31)
	lfs f2, 0x0(r27)
	fadds f2, f3, f2
	stfs f2, 0x18(r31)
	lfs f3, 0x1c(r31)
	lfs f2, 0x0(r28)
	fadds f2, f3, f2
	stfs f2, 0x1c(r31)
	stfs f1, 0x24(r31)
	stfs f0, 0x28(r31)
	stfs f1, 0x2c(r31)
	b @17
	@19:
	lfs f0, 0xc(r31)
	lfs f3, float_200_8041c47c(r2)
	fsubs f2, f26, f0
	lfs f1, float_0_8041c454(r2)
	lfs f0, float_1_8041c470(r2)
	fdivs f2, f2, f3
	stfs f2, 0x0(r24)
	lfs f2, 0x10(r31)
	fsubs f2, f27, f2
	fdivs f2, f2, f3
	stfs f2, 0x0(r25)
	lfs f2, 0x18(r31)
	fsubs f2, f29, f2
	fdivs f2, f2, f3
	stfs f2, 0x0(r27)
	lfs f2, 0x1c(r31)
	fsubs f2, f30, f2
	fdivs f2, f2, f3
	stfs f2, 0x0(r28)
	lfs f3, 0xc(r31)
	lfs f2, 0x0(r24)
	fadds f2, f3, f2
	stfs f2, 0xc(r31)
	lfs f3, 0x10(r31)
	lfs f2, 0x0(r25)
	fadds f2, f3, f2
	stfs f2, 0x10(r31)
	lfs f3, 0x18(r31)
	lfs f2, 0x0(r27)
	fadds f2, f3, f2
	stfs f2, 0x18(r31)
	lfs f3, 0x1c(r31)
	lfs f2, 0x0(r28)
	fadds f2, f3, f2
	stfs f2, 0x1c(r31)
	stfs f1, 0x24(r31)
	stfs f0, 0x28(r31)
	stfs f1, 0x2c(r31)
	b @17
	@18:
	lfs f0, 0xc(r31)
	lfs f3, float_100_8041c464(r2)
	fsubs f2, f26, f0
	lfs f1, float_0_8041c454(r2)
	lfs f0, float_1_8041c470(r2)
	fdivs f2, f2, f3
	stfs f2, 0x0(r24)
	lfs f2, 0x10(r31)
	fsubs f2, f27, f2
	fdivs f2, f2, f3
	stfs f2, 0x0(r25)
	lfs f2, 0x18(r31)
	fsubs f2, f29, f2
	fdivs f2, f2, f3
	stfs f2, 0x0(r27)
	lfs f2, 0x1c(r31)
	fsubs f2, f30, f2
	fdivs f2, f2, f3
	stfs f2, 0x0(r28)
	lfs f3, 0xc(r31)
	lfs f2, 0x0(r24)
	fadds f2, f3, f2
	stfs f2, 0xc(r31)
	lfs f3, 0x10(r31)
	lfs f2, 0x0(r25)
	fadds f2, f3, f2
	stfs f2, 0x10(r31)
	lfs f3, 0x18(r31)
	lfs f2, 0x0(r27)
	fadds f2, f3, f2
	stfs f2, 0x18(r31)
	lfs f3, 0x1c(r31)
	lfs f2, 0x0(r28)
	fadds f2, f3, f2
	stfs f2, 0x1c(r31)
	stfs f1, 0x24(r31)
	stfs f0, 0x28(r31)
	stfs f1, 0x2c(r31)
	@17:
	lha r0, 0x277e(r30)
	cmpwi r0, 0x3
	beq @20
	bge @21
	cmpwi r0, 0x1
	beq @22
	bge @23
	cmpwi r0, 0x0
	bge @24
	b @25
	@21:
	cmpwi r0, 0x5
	beq @26
	bge @25
	b @27
	@24:
	lfs f0, 0x14(r31)
	lfs f1, float_1p5_8041c46c(r2)
	fsubs f0, f28, f0
	fdivs f0, f0, f1
	stfs f0, 0x0(r26)
	lfs f0, 0x20(r31)
	fsubs f0, f31, f0
	fdivs f0, f0, f1
	stfs f0, 0x0(r29)
	lfs f1, 0x14(r31)
	lfs f0, 0x0(r26)
	fadds f0, f1, f0
	stfs f0, 0x14(r31)
	lfs f1, 0x20(r31)
	lfs f0, 0x0(r29)
	fadds f0, f1, f0
	stfs f0, 0x20(r31)
	b @25
	@22:
	lfs f0, 0x14(r31)
	lfs f1, float_15_8041c474(r2)
	fsubs f0, f28, f0
	fdivs f0, f0, f1
	stfs f0, 0x0(r26)
	lfs f0, 0x20(r31)
	fsubs f0, f31, f0
	fdivs f0, f0, f1
	stfs f0, 0x0(r29)
	lfs f1, 0x14(r31)
	lfs f0, 0x0(r26)
	fadds f0, f1, f0
	stfs f0, 0x14(r31)
	lfs f1, 0x20(r31)
	lfs f0, 0x0(r29)
	fadds f0, f1, f0
	stfs f0, 0x20(r31)
	b @25
	@23:
	lfs f0, 0x14(r31)
	lfs f1, float_5_8041c478(r2)
	fsubs f0, f28, f0
	fdivs f0, f0, f1
	stfs f0, 0x0(r26)
	lfs f0, 0x20(r31)
	fsubs f0, f31, f0
	fdivs f0, f0, f1
	stfs f0, 0x0(r29)
	lfs f1, 0x14(r31)
	lfs f0, 0x0(r26)
	fadds f0, f1, f0
	stfs f0, 0x14(r31)
	lfs f1, 0x20(r31)
	lfs f0, 0x0(r29)
	fadds f0, f1, f0
	stfs f0, 0x20(r31)
	b @25
	@20:
	lfs f0, 0x14(r31)
	fsubs f0, f28, f0
	stfs f0, 0x0(r26)
	lfs f0, 0x20(r31)
	fsubs f0, f31, f0
	stfs f0, 0x0(r29)
	lfs f1, 0x14(r31)
	lfs f0, 0x0(r26)
	fadds f0, f1, f0
	stfs f0, 0x14(r31)
	lfs f1, 0x20(r31)
	lfs f0, 0x0(r29)
	fadds f0, f1, f0
	stfs f0, 0x20(r31)
	b @25
	@27:
	lfs f0, 0x14(r31)
	lfs f1, float_200_8041c47c(r2)
	fsubs f0, f28, f0
	fdivs f0, f0, f1
	stfs f0, 0x0(r26)
	lfs f0, 0x20(r31)
	fsubs f0, f31, f0
	fdivs f0, f0, f1
	stfs f0, 0x0(r29)
	lfs f1, 0x14(r31)
	lfs f0, 0x0(r26)
	fadds f0, f1, f0
	stfs f0, 0x14(r31)
	lfs f1, 0x20(r31)
	lfs f0, 0x0(r29)
	fadds f0, f1, f0
	stfs f0, 0x20(r31)
	b @25
	@26:
	lfs f0, 0x14(r31)
	lfs f1, float_100_8041c464(r2)
	fsubs f0, f28, f0
	fdivs f0, f0, f1
	stfs f0, 0x0(r26)
	lfs f0, 0x20(r31)
	fsubs f0, f31, f0
	fdivs f0, f0, f1
	stfs f0, 0x0(r29)
	lfs f1, 0x14(r31)
	lfs f0, 0x0(r26)
	fadds f0, f1, f0
	stfs f0, 0x14(r31)
	lfs f1, 0x20(r31)
	lfs f0, 0x0(r29)
	fadds f0, f1, f0
	stfs f0, 0x20(r31)
	@25:
	psq_l f31, 0x88(r1), 0, 0
	lfd f31, 0x80(r1)
	psq_l f30, 0x78(r1), 0, 0
	lfd f30, 0x70(r1)
	psq_l f29, 0x68(r1), 0, 0
	lfd f29, 0x60(r1)
	psq_l f28, 0x58(r1), 0, 0
	lfd f28, 0x50(r1)
	psq_l f27, 0x48(r1), 0, 0
	lfd f27, 0x40(r1)
	psq_l f26, 0x38(r1), 0, 0
	lfd f26, 0x30(r1)
	lmw r22, 0x8(r1)
	lwz r0, 0x94(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

asm void battleCameraMain(void) {
	nofralloc
	stwu r1, -0x100(r1)
	mflr r0
	stw r0, 0x104(r1)
	stfd f31, 0xf0(r1)
	psq_st f31, 0xf8(r1), 0, 0
	stfd f30, 0xe0(r1)
	psq_st f30, 0xe8(r1), 0, 0
	stmw r25, 0xc4(r1)
	lis r4, vec3_802efc40@ha
	li r3, 0x4
	addi r29, r4, vec3_802efc40@l
	bl camGetPtr
	lwz r31, _battleWorkPointer(r13)
	mr r30, r3
	bl BattleAudienceBaseGetPtr
	lfs f30, float_0_8041c454(r2)
	mr r28, r3
	mr r3, r31
	bl BattleGetMarioPtr
	lfs f0, float_0_8041c454(r2)
	stfs f0, 0x34(r1)
	stfs f0, 0x30(r1)
	stfs f0, 0x2c(r1)
	stfs f0, 0x28(r1)
	stfs f0, 0x24(r1)
	stfs f0, 0x20(r1)
	lwz r0, 0x2760(r31)
	cmpwi r0, 0x3
	beq @1
	li r0, 0x0
	stw r0, 0x27d8(r31)
	@1:
	lfs f0, 0x2780(r31)
	stfs f0, 0xc(r30)
	lfs f0, 0x2784(r31)
	stfs f0, 0x10(r30)
	lfs f0, 0x2788(r31)
	stfs f0, 0x14(r30)
	lfs f0, 0x2798(r31)
	stfs f0, 0x18(r30)
	lfs f0, 0x279c(r31)
	stfs f0, 0x1c(r30)
	lfs f0, 0x27a0(r31)
	stfs f0, 0x20(r30)
	lfs f0, 0xc(r30)
	stfs f0, 0x278c(r31)
	lfs f0, 0x10(r30)
	stfs f0, 0x2790(r31)
	lfs f0, 0x14(r30)
	stfs f0, 0x2794(r31)
	lfs f0, 0x18(r30)
	stfs f0, 0x27a4(r31)
	lfs f0, 0x1c(r30)
	stfs f0, 0x27a8(r31)
	lfs f0, 0x20(r30)
	stfs f0, 0x27ac(r31)
	lwz r0, 0x2760(r31)
	cmplwi r0, 0x14
	bgt @2
	lis r3, jumptable_80362040@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_80362040@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@3:
	lfs f1, float_0_8041c454(r2)
	addi r5, r1, 0x34
	lfs f2, float_110_8041c480(r2)
	addi r6, r1, 0x30
	fmr f4, f1
	lfs f3, float_750_8041c484(r2)
	fmr f6, f1
	lfs f5, float_60_8041c488(r2)
	addi r7, r1, 0x2c
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x1
	li r4, 0x1
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0x78
	bl strcpy
	b @4
	@5:
	lfs f2, float_0p5_8041c460(r2)
	addi r5, r1, 0x34
	lfs f0, 0x2778(r31)
	addi r6, r1, 0x30
	lfs f1, float_0_8041c454(r2)
	addi r7, r1, 0x2c
	fmuls f6, f2, f0
	lfs f0, float_750_8041c484(r2)
	fmr f4, f1
	lfs f2, float_110_8041c480(r2)
	lfs f5, float_60_8041c488(r2)
	addi r8, r1, 0x28
	fsubs f3, f0, f6
	addi r9, r1, 0x24
	fneg f6, f6
	addi r10, r1, 0x20
	li r3, 0x1
	li r4, 0x1
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0x8c
	bl strcpy
	b @4
	@6:
	lfs f1, float_0_8041c454(r2)
	addi r5, r1, 0x34
	lfs f2, float_160_8041c48c(r2)
	addi r6, r1, 0x30
	fmr f4, f1
	lfs f3, float_750_8041c484(r2)
	fmr f6, f1
	lfs f5, float_110_8041c480(r2)
	addi r7, r1, 0x2c
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x1
	li r4, 0x1
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0xa8
	bl strcpy
	@7:
	lwz r3, 0x27d8(r31)
	cmpwi r3, 0x0
	ble @8
	lha r28, 0x277c(r31)
	subi r0, r3, 0x1
	stw r0, 0x27d8(r31)
	lwz r5, 0x27dc(r31)
	lwz r0, 0x27d8(r31)
	lwz r3, 0x27d4(r31)
	lfs f1, 0x27e0(r31)
	subf r4, r0, r5
	lfs f2, 0x27ec(r31)
	bl intplGetValue
	stfs f1, 0x5c(r1)
	lwz r5, 0x27dc(r31)
	lwz r0, 0x27d8(r31)
	lwz r3, 0x27d4(r31)
	lfs f1, 0x27e4(r31)
	subf r4, r0, r5
	lfs f2, 0x27f0(r31)
	bl intplGetValue
	stfs f1, 0x60(r1)
	lwz r5, 0x27dc(r31)
	lwz r0, 0x27d8(r31)
	lwz r3, 0x27d4(r31)
	lfs f1, 0x27e8(r31)
	subf r4, r0, r5
	lfs f2, 0x27f4(r31)
	bl intplGetValue
	stfs f1, 0x64(r1)
	lwz r5, 0x27dc(r31)
	lwz r0, 0x27d8(r31)
	lwz r3, 0x27d4(r31)
	lfs f1, 0x27f8(r31)
	subf r4, r0, r5
	lfs f2, 0x2804(r31)
	bl intplGetValue
	fmr f31, f1
	lwz r5, 0x27dc(r31)
	lwz r0, 0x27d8(r31)
	lwz r3, 0x27d4(r31)
	lfs f1, 0x27fc(r31)
	subf r4, r0, r5
	lfs f2, 0x2808(r31)
	bl intplGetValue
	fmr f30, f1
	lwz r5, 0x27dc(r31)
	lwz r0, 0x27d8(r31)
	lwz r3, 0x27d4(r31)
	lfs f1, 0x2800(r31)
	subf r4, r0, r5
	lfs f2, 0x280c(r31)
	bl intplGetValue
	li r0, 0x3
	fmr f4, f31
	sth r0, 0x277c(r31)
	fmr f5, f30
	fmr f6, f1
	addi r5, r1, 0x34
	sth r0, 0x277e(r31)
	addi r6, r1, 0x30
	addi r7, r1, 0x2c
	lfs f1, 0x5c(r1)
	lfs f2, 0x60(r1)
	addi r8, r1, 0x28
	lfs f3, 0x64(r1)
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x0
	li r4, 0x0
	bl battleCameraMoveTo
	sth r28, 0x277c(r31)
	@8:
	addi r3, r1, 0x68
	addi r4, r29, 0xc4
	bl strcpy
	b @4
	@9:
	lfs f1, float_0_8041c454(r2)
	addi r5, r1, 0x34
	lfs f2, float_110_8041c480(r2)
	addi r6, r1, 0x30
	fmr f4, f1
	lfs f3, float_neg750_8041c490(r2)
	fmr f6, f1
	lfs f5, float_60_8041c488(r2)
	addi r7, r1, 0x2c
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x1
	li r4, 0x1
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0xd4
	bl strcpy
	b @4
	@10:
	lfs f1, float_0_8041c454(r2)
	addi r5, r1, 0x34
	lfs f2, float_400_8041c494(r2)
	addi r6, r1, 0x30
	fmr f4, f1
	lfs f3, float_neg617_8041c498(r2)
	fmr f6, f1
	lfs f5, float_60_8041c488(r2)
	addi r7, r1, 0x2c
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x1
	li r4, 0x1
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0xe8
	bl strcpy
	b @4
	@11:
	bl pouchGetPtr
	lha r0, 0x88(r3)
	cmpwi r0, 0x2
	beq @12
	bge @13
	cmpwi r0, 0x0
	beq @14
	bge @15
	b @16
	@13:
	cmpwi r0, 0x4
	bge @16
	b @17
	@14:
	lfs f30, float_750_8041c484(r2)
	b @16
	@15:
	lfs f30, float_830_8041c49c(r2)
	b @16
	@12:
	lfs f30, float_920_8041c4a0(r2)
	b @16
	@17:
	lfs f30, float_1000_8041c4a4(r2)
	@16:
	lfs f1, float_0_8041c454(r2)
	fmr f3, f30
	lfs f2, float_110_8041c480(r2)
	addi r5, r1, 0x34
	fmr f4, f1
	lfs f5, float_60_8041c488(r2)
	fmr f6, f1
	addi r6, r1, 0x30
	addi r7, r1, 0x2c
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x1
	li r4, 0x1
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0x100
	bl strcpy
	b @4
	@18:
	lwz r4, 0x2764(r31)
	mr r3, r31
	bl BattleGetUnitPtr
	mr. r28, r3
	bne @19
	li r3, 0x0
	li r4, 0x0
	bl btl_camera_set_mode
	b @4
	@19:
	lwz r3, 0x2764(r31)
	lwz r4, 0x276c(r31)
	bl BattleGetUnitPartsPtr
	addi r5, r1, 0x60
	mr r3, r28
	addi r4, r1, 0x5c
	addi r6, r1, 0x64
	bl BtlUnit_GetPos
	mr r3, r28
	bl BtlUnit_GetHeight
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	mr r3, r28
	lfd f3, 0x70(r29)
	stw r0, 0xa8(r1)
	lfs f2, float_50_8041c4a8(r2)
	lfd f0, 0xa8(r1)
	lfs f1, float_0p5_8041c460(r2)
	fsubs f3, f0, f3
	lfs f0, 0x60(r1)
	fsubs f2, f3, f2
	fmuls f1, f2, f1
	fadds f0, f0, f1
	stfs f0, 0x60(r1)
	bl BtlUnit_GetWidth
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lfd f3, 0x70(r29)
	stw r0, 0xb0(r1)
	lfs f1, float_24_8041c4ac(r2)
	lfd f2, 0xb0(r1)
	lfs f0, float_0_8041c454(r2)
	fsubs f2, f2, f3
	fsubs f1, f2, f1
	fcmpo cr0, f1, f0
	bge @20
	fmr f1, f0
	@20:
	lfs f5, 0x2778(r31)
	lfs f0, float_1p5_8041c46c(r2)
	lfs f3, 0x60(r1)
	fnmsubs f5, f0, f1, f5
	lfs f0, float_100_8041c464(r2)
	lfs f1, float_9_8041c4b0(r2)
	fmr f2, f3
	fcmpo cr0, f3, f0
	fneg f6, f5
	fdivs f7, f6, f1
	ble @21
	fmr f3, f0
	@21:
	lfs f0, float_0_8041c454(r2)
	fcmpo cr0, f2, f0
	bge @22
	fmr f3, f0
	@22:
	lfs f1, float_110_8041c480(r2)
	addi r5, r1, 0x34
	lfs f0, float_60_8041c488(r2)
	addi r6, r1, 0x30
	fadds f2, f1, f3
	lfs f1, 0x5c(r1)
	fadds f0, f0, f3
	lfs f3, float_750_8041c484(r2)
	fmr f4, f1
	addi r7, r1, 0x2c
	fsubs f3, f3, f5
	addi r8, r1, 0x28
	fadds f2, f2, f7
	addi r9, r1, 0x24
	fadds f5, f0, f7
	addi r10, r1, 0x20
	li r3, 0x1
	li r4, 0x1
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0x114
	bl strcpy
	b @4
	@23:
	lwz r4, 0x2764(r31)
	mr r3, r31
	bl BattleGetUnitPtr
	lwz r4, 0x2768(r31)
	mr r26, r3
	mr r3, r31
	bl BattleGetUnitPtr
	cmplwi r26, 0x0
	mr r28, r3
	beq @24
	cmplwi r28, 0x0
	bne @25
	@24:
	li r3, 0x0
	li r4, 0x0
	bl btl_camera_set_mode
	b @4
	@25:
	lwz r3, 0x2764(r31)
	lwz r4, 0x276c(r31)
	bl BattleGetUnitPartsPtr
	lwz r3, 0x2768(r31)
	lwz r4, 0x2770(r31)
	bl BattleGetUnitPartsPtr
	mr r27, r3
	addi r5, r1, 0x60
	mr r3, r26
	addi r4, r1, 0x5c
	addi r6, r1, 0x64
	bl BtlUnit_GetPos
	mr r3, r28
	mr r4, r27
	addi r5, r1, 0x50
	addi r6, r1, 0x54
	addi r7, r1, 0x58
	bl BtlUnit_GetHitPos
	mr r3, r26
	bl BtlUnit_GetWidth
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	mr r3, r28
	lfd f2, 0x70(r29)
	stw r0, 0xb0(r1)
	lfs f0, float_24_8041c4ac(r2)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fsubs f30, f1, f0
	bl BtlUnit_GetWidth
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lfs f0, float_0_8041c454(r2)
	stw r0, 0xa8(r1)
	lfd f3, 0x70(r29)
	fcmpo cr0, f30, f0
	lfd f2, 0xa8(r1)
	lfs f1, float_24_8041c4ac(r2)
	fsubs f2, f2, f3
	fsubs f3, f2, f1
	bge @26
	fmr f30, f0
	@26:
	lfs f0, float_0_8041c454(r2)
	fcmpo cr0, f3, f0
	bge @27
	fmr f3, f0
	@27:
	lfs f6, 0x281c(r31)
	lfs f0, 0x2810(r31)
	lfs f2, 0x50(r1)
	lfs f1, 0x5c(r1)
	fsubs f4, f6, f0
	lfs f0, float_0_8041c454(r2)
	fsubs f1, f2, f1
	fcmpu cr0, f0, f4
	bne @28
	lfs f8, float_0p5_8041c460(r2)
	b @29
	@28:
	fdivs f8, f1, f4
	@29:
	lfs f0, float_1_8041c470(r2)
	fcmpo cr0, f8, f0
	ble @30
	fmr f8, f0
	@30:
	lfs f0, float_0p5_8041c460(r2)
	fcmpo cr0, f8, f0
	bge @31
	fmr f8, f0
	@31:
	lfs f1, float_2_8041c450(r2)
	fadds f2, f30, f3
	lfs f0, 0x2778(r31)
	lfs f3, float_1_8041c470(r2)
	fmuls f0, f1, f0
	lfs f1, float_1p5_8041c46c(r2)
	fsubs f7, f3, f8
	lfs f5, 0x2820(r31)
	lfs f4, float_80_8041c4b4(r2)
	fnmsubs f1, f1, f2, f0
	lfs f3, 0x60(r1)
	fdivs f4, f5, f4
	lfs f2, float_10_8041c4b8(r2)
	lfs f0, float_100_8041c464(r2)
	fmuls f10, f7, f1
	fsubs f3, f3, f5
	fmuls f1, f7, f6
	fneg f6, f10
	fmuls f9, f4, f3
	fdivs f11, f6, f2
	fcmpo cr0, f9, f0
	ble @32
	fmr f9, f0
	@32:
	lfs f0, float_0_8041c454(r2)
	fcmpo cr0, f9, f0
	bge @33
	fmr f9, f0
	@33:
	lfd f0, 0x138(r29)
	fmr f4, f1
	lfs f2, float_750_8041c484(r2)
	addi r5, r1, 0x34
	fsub f3, f0, f8
	lfd f8, 0x130(r29)
	lfs f5, float_110_8041c480(r2)
	lfs f0, float_60_8041c488(r2)
	addi r6, r1, 0x30
	fneg f7, f3
	fsubs f3, f2, f10
	addi r7, r1, 0x2c
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	fmadd f7, f8, f7, f9
	addi r10, r1, 0x20
	li r3, 0x1
	li r4, 0x1
	frsp f7, f7
	fadds f2, f5, f7
	fadds f0, f0, f7
	fadds f2, f2, f11
	fadds f5, f0, f11
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0x140
	bl strcpy
	b @4
	@34:
	lwz r4, 0x2764(r31)
	mr r3, r31
	bl BattleGetUnitPtr
	lwz r4, 0x2768(r31)
	mr r27, r3
	mr r3, r31
	bl BattleGetUnitPtr
	cmplwi r27, 0x0
	mr r26, r3
	beq @35
	cmplwi r26, 0x0
	bne @36
	@35:
	li r3, 0x0
	li r4, 0x0
	bl btl_camera_set_mode
	b @4
	@36:
	lwz r3, 0x2764(r31)
	lwz r4, 0x276c(r31)
	bl BattleGetUnitPartsPtr
	lwz r3, 0x2768(r31)
	lwz r4, 0x2770(r31)
	bl BattleGetUnitPartsPtr
	mr r25, r3
	addi r5, r1, 0x60
	mr r3, r27
	addi r4, r1, 0x5c
	addi r6, r1, 0x64
	bl BtlUnit_GetPos
	addi r6, r1, 0x54
	mr r3, r26
	mr r4, r25
	addi r5, r1, 0x50
	addi r7, r1, 0x58
	bl BtlUnit_GetHitPos
	mr r3, r27
	bl BtlUnit_GetWidth
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	mr r3, r26
	lfd f2, 0x70(r29)
	stw r0, 0xb0(r1)
	lfs f0, float_24_8041c4ac(r2)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fsubs f30, f1, f0
	bl BtlUnit_GetWidth
	lfs f0, float_0_8041c454(r2)
	fcmpo cr0, f30, f0
	bge @37
	fmr f30, f0
	@37:
	lfs f1, float_2_8041c450(r2)
	lfs f0, 0x2778(r31)
	lfs f3, float_1p5_8041c46c(r2)
	fmuls f7, f1, f0
	lfs f1, float_10_8041c4b8(r2)
	lfs f2, 0x60(r1)
	lfs f0, 0x54(r1)
	fnmsubs f7, f3, f30, f7
	lfs f3, float_0p5_8041c460(r2)
	fadds f2, f2, f0
	lfs f0, float_50_8041c4a8(r2)
	fneg f6, f7
	fmuls f2, f3, f2
	fdivs f8, f6, f1
	fcmpo cr0, f2, f0
	ble @38
	fmr f31, f0
	@38:
	lfs f0, float_0_8041c454(r2)
	fcmpo cr0, f2, f0
	bge @39
	fmr f31, f0
	@39:
	lfs f3, 0x5c(r1)
	addi r5, r1, 0x34
	lfs f2, 0x50(r1)
	addi r6, r1, 0x30
	lfs f0, float_60_8041c488(r2)
	addi r7, r1, 0x2c
	fadds f4, f3, f2
	lfs f1, float_110_8041c480(r2)
	lfs f5, float_0p5_8041c460(r2)
	fadds f0, f0, f31
	fadds f2, f1, f31
	lfs f3, float_750_8041c484(r2)
	fmuls f1, f5, f4
	addi r8, r1, 0x28
	fadds f2, f2, f8
	addi r9, r1, 0x24
	fsubs f3, f3, f7
	addi r10, r1, 0x20
	fmr f4, f1
	li r3, 0x1
	fadds f5, f0, f8
	li r4, 0x1
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0x114
	bl strcpy
	b @4
	@40:
	lwz r4, 0x2764(r31)
	mr r3, r31
	bl BattleGetUnitPtr
	mr. r27, r3
	bne @41
	li r3, 0x0
	li r4, 0x0
	bl btl_camera_set_mode
	b @4
	@41:
	lwz r3, 0x2764(r31)
	lwz r4, 0x276c(r31)
	bl BattleGetUnitPartsPtr
	mr. r4, r3
	bne @42
	li r3, 0x0
	li r4, 0x0
	bl btl_camera_set_mode
	b @4
	@42:
	addi r6, r1, 0x60
	mr r3, r27
	addi r5, r1, 0x5c
	addi r7, r1, 0x64
	bl BtlUnit_GetHitPos
	mr r3, r27
	bl BtlUnit_GetHeight
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	mr r3, r27
	lfd f3, 0x70(r29)
	stw r0, 0xb0(r1)
	lfs f2, float_50_8041c4a8(r2)
	lfd f0, 0xb0(r1)
	lfs f1, float_0p5_8041c460(r2)
	fsubs f3, f0, f3
	lfs f0, 0x60(r1)
	fsubs f2, f3, f2
	fmuls f1, f2, f1
	fadds f0, f0, f1
	stfs f0, 0x60(r1)
	bl BtlUnit_GetWidth
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lfd f3, 0x70(r29)
	stw r0, 0xa8(r1)
	lfs f1, float_24_8041c4ac(r2)
	lfd f2, 0xa8(r1)
	lfs f0, float_0_8041c454(r2)
	fsubs f2, f2, f3
	fsubs f1, f2, f1
	fcmpo cr0, f1, f0
	bge @43
	fmr f1, f0
	@43:
	lfs f5, 0x2778(r31)
	lfs f0, float_1p5_8041c46c(r2)
	lfs f3, 0x60(r1)
	fnmsubs f5, f0, f1, f5
	lfs f0, float_100_8041c464(r2)
	lfs f1, float_9_8041c4b0(r2)
	fmr f2, f3
	fcmpo cr0, f3, f0
	fneg f6, f5
	fdivs f7, f6, f1
	ble @44
	fmr f3, f0
	@44:
	lfs f0, float_0_8041c454(r2)
	fcmpo cr0, f2, f0
	bge @45
	fmr f3, f0
	@45:
	lfs f1, float_110_8041c480(r2)
	addi r5, r1, 0x34
	lfs f0, float_60_8041c488(r2)
	addi r6, r1, 0x30
	fadds f2, f1, f3
	lfs f1, 0x5c(r1)
	fadds f0, f0, f3
	lfs f3, float_750_8041c484(r2)
	fmr f4, f1
	addi r7, r1, 0x2c
	fsubs f3, f3, f5
	addi r8, r1, 0x28
	fadds f2, f2, f7
	addi r9, r1, 0x24
	fadds f5, f0, f7
	addi r10, r1, 0x20
	li r3, 0x1
	li r4, 0x1
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0x160
	bl strcpy
	b @4
	@46:
	lwz r4, 0x2764(r31)
	mr r3, r31
	bl BattleGetUnitPtr
	lwz r4, 0x2768(r31)
	mr r27, r3
	mr r3, r31
	bl BattleGetUnitPtr
	cmplwi r27, 0x0
	mr r28, r3
	beq @47
	cmplwi r28, 0x0
	bne @48
	@47:
	li r3, 0x0
	li r4, 0x0
	bl btl_camera_set_mode
	b @4
	@48:
	lwz r3, 0x2764(r31)
	lwz r4, 0x276c(r31)
	bl BattleGetUnitPartsPtr
	mr r26, r3
	lwz r3, 0x2768(r31)
	lwz r4, 0x2770(r31)
	bl BattleGetUnitPartsPtr
	cmplwi r26, 0x0
	mr r25, r3
	beq @49
	cmplwi r25, 0x0
	bne @50
	@49:
	li r3, 0x0
	li r4, 0x0
	bl btl_camera_set_mode
	b @4
	@50:
	addi r5, r1, 0x60
	mr r3, r26
	addi r4, r1, 0x5c
	addi r6, r1, 0x64
	bl BtlUnit_GetPartsWorldPos
	mr r3, r28
	mr r4, r25
	addi r5, r1, 0x50
	addi r6, r1, 0x54
	addi r7, r1, 0x58
	bl BtlUnit_GetHitPos
	mr r3, r27
	bl BtlUnit_GetWidth
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	mr r3, r28
	lfd f2, 0x70(r29)
	stw r0, 0xb0(r1)
	lfs f0, float_24_8041c4ac(r2)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fsubs f30, f1, f0
	bl BtlUnit_GetWidth
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lfs f0, float_0_8041c454(r2)
	stw r0, 0xa8(r1)
	lfd f3, 0x70(r29)
	fcmpo cr0, f30, f0
	lfd f2, 0xa8(r1)
	lfs f1, float_24_8041c4ac(r2)
	fsubs f2, f2, f3
	fsubs f3, f2, f1
	bge @51
	fmr f30, f0
	@51:
	lfs f0, float_0_8041c454(r2)
	fcmpo cr0, f3, f0
	bge @52
	fmr f3, f0
	@52:
	lfs f6, 0x281c(r31)
	lfs f0, 0x2810(r31)
	lfs f2, 0x50(r1)
	lfs f1, 0x5c(r1)
	fsubs f4, f6, f0
	lfs f0, float_0_8041c454(r2)
	fsubs f1, f2, f1
	fcmpu cr0, f0, f4
	bne @53
	lfs f4, float_1Eneg05_8041c4bc(r2)
	@53:
	fdivs f8, f1, f4
	lfs f0, float_1_8041c470(r2)
	fcmpo cr0, f8, f0
	ble @54
	fmr f8, f0
	@54:
	lfs f0, float_0p5_8041c460(r2)
	fcmpo cr0, f8, f0
	bge @55
	fmr f8, f0
	@55:
	lfs f1, float_2_8041c450(r2)
	fadds f2, f30, f3
	lfs f0, 0x2778(r31)
	lfs f3, float_1_8041c470(r2)
	fmuls f0, f1, f0
	lfs f1, float_1p5_8041c46c(r2)
	fsubs f7, f3, f8
	lfs f5, 0x2820(r31)
	lfs f4, float_80_8041c4b4(r2)
	fnmsubs f1, f1, f2, f0
	lfs f3, 0x60(r1)
	fdivs f4, f5, f4
	lfs f2, float_10_8041c4b8(r2)
	lfs f0, float_100_8041c464(r2)
	fmuls f10, f7, f1
	fsubs f3, f3, f5
	fmuls f1, f7, f6
	fneg f6, f10
	fmuls f9, f4, f3
	fdivs f11, f6, f2
	fcmpo cr0, f9, f0
	ble @56
	fmr f9, f0
	@56:
	lfs f0, float_0_8041c454(r2)
	fcmpo cr0, f9, f0
	bge @57
	fmr f9, f0
	@57:
	lfd f0, 0x138(r29)
	fmr f4, f1
	lfs f2, float_750_8041c484(r2)
	addi r5, r1, 0x34
	fsub f3, f0, f8
	lfd f8, 0x130(r29)
	lfs f5, float_110_8041c480(r2)
	lfs f0, float_60_8041c488(r2)
	addi r6, r1, 0x30
	fneg f7, f3
	fsubs f3, f2, f10
	addi r7, r1, 0x2c
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	fmadd f7, f8, f7, f9
	addi r10, r1, 0x20
	li r3, 0x1
	li r4, 0x1
	frsp f7, f7
	fadds f2, f5, f7
	fadds f0, f0, f7
	fadds f2, f2, f11
	fadds f5, f0, f11
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0x178
	bl strcpy
	b @4
	@58:
	lwz r0, 0x2774(r31)
	addi r5, r1, 0x34
	lfs f0, float_400_8041c494(r2)
	addi r6, r1, 0x30
	mulli r3, r0, 0x134
	lfs f2, float_200_8041c47c(r2)
	lfs f5, float_0_8041c454(r2)
	addi r7, r1, 0x2c
	addi r8, r1, 0x28
	addi r3, r3, 0x1bc
	add r3, r28, r3
	addi r9, r1, 0x24
	lfs f6, 0x50(r3)
	addi r10, r1, 0x20
	lfs f1, 0x48(r3)
	li r3, 0x1
	fadds f3, f0, f6
	li r4, 0x0
	fmr f4, f1
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0x194
	bl strcpy
	b @4
	@59:
	lwz r4, 0x2764(r31)
	mr r3, r31
	bl BattleGetUnitPtr
	mr. r27, r3
	bne @60
	li r3, 0x0
	li r4, 0x0
	bl btl_camera_set_mode
	b @4
	@60:
	lwz r3, 0x2764(r31)
	lwz r4, 0x276c(r31)
	bl BattleGetUnitPartsPtr
	cmplwi r3, 0x0
	bne @61
	li r3, 0x0
	li r4, 0x0
	bl btl_camera_set_mode
	b @4
	@61:
	li r0, 0xa
	addi r5, r1, 0x60
	stw r0, 0x2774(r31)
	mr r3, r27
	addi r4, r1, 0x5c
	addi r6, r1, 0x64
	lfs f1, 0x281c(r31)
	lfs f0, 0x2810(r31)
	fsubs f30, f1, f0
	bl BtlUnit_GetPos
	lfs f0, float_0_8041c454(r2)
	lfs f3, 0x281c(r31)
	lfs f1, 0x5c(r1)
	fcmpu cr0, f0, f30
	fsubs f0, f3, f1
	bne @62
	lfs f7, float_0p5_8041c460(r2)
	b @63
	@62:
	fdivs f7, f0, f30
	@63:
	lfs f0, float_1_8041c470(r2)
	fcmpo cr0, f7, f0
	ble @64
	fmr f7, f0
	@64:
	lfs f0, float_0p5_8041c460(r2)
	fcmpo cr0, f7, f0
	bge @65
	fmr f7, f0
	@65:
	lfs f2, 0x60(r1)
	lfs f0, 0x2814(r31)
	lfs f1, float_1_8041c470(r2)
	fsubs f5, f2, f0
	lfs f0, float_100_8041c464(r2)
	fsubs f4, f1, f7
	lfs f2, float_2_8041c450(r2)
	lfs f1, 0x2778(r31)
	fsubs f5, f5, f0
	lfs f0, float_0_8041c454(r2)
	fmuls f6, f2, f1
	fmuls f1, f4, f3
	fcmpo cr0, f5, f0
	ble @66
	fmr f5, f0
	@66:
	lfs f0, float_neg30_8041c4c0(r2)
	fcmpo cr0, f5, f0
	bge @67
	fmr f5, f0
	@67:
	lfd f2, 0x138(r29)
	fmuls f6, f4, f6
	lfs f0, float_125_8041c4c4(r2)
	fmr f4, f1
	fsub f3, f2, f7
	lfs f2, float_750_8041c484(r2)
	fsubs f7, f0, f5
	lfs f5, float_110_8041c480(r2)
	addi r5, r1, 0x34
	fneg f8, f3
	fsubs f3, f2, f6
	lfs f0, float_60_8041c488(r2)
	fneg f6, f6
	addi r6, r1, 0x30
	fmul f7, f8, f7
	addi r7, r1, 0x2c
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x1
	frsp f7, f7
	li r4, 0x1
	fadds f2, f5, f7
	fadds f5, f0, f7
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0x1b0
	bl strcpy
	b @4
	@68:
	lwz r3, 0x2758(r31)
	addi r0, r3, 0x1
	stw r0, 0x2758(r31)
	lwz r0, 0x2758(r31)
	cmpwi r0, 0x1
	bne @69
	bl pouchGetPtr
	lha r0, 0x88(r3)
	cmpwi r0, 0x2
	beq @70
	bge @71
	cmpwi r0, 0x0
	beq @72
	bge @73
	b @74
	@71:
	cmpwi r0, 0x4
	bge @74
	b @75
	@72:
	lfs f30, float_750_8041c484(r2)
	b @74
	@73:
	lfs f30, float_830_8041c49c(r2)
	b @74
	@70:
	lfs f30, float_920_8041c4a0(r2)
	b @74
	@75:
	lfs f30, float_1000_8041c4a4(r2)
	@74:
	lfs f1, float_0_8041c454(r2)
	li r0, 0x3
	sth r0, 0x277c(r31)
	fmr f3, f30
	fmr f4, f1
	lfs f2, float_110_8041c480(r2)
	fmr f6, f1
	sth r0, 0x277e(r31)
	lfs f5, float_60_8041c488(r2)
	addi r5, r1, 0x34
	addi r6, r1, 0x30
	addi r7, r1, 0x2c
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x1
	li r4, 0x1
	bl battleCameraMoveTo
	@69:
	lwz r0, 0x2758(r31)
	cmpwi r0, 0xa
	bne @76
	li r0, 0x0
	li r3, 0x0
	stw r0, 0x2758(r31)
	li r4, 0x3
	bl btl_camera_set_mode
	lfs f1, float_0_8041c454(r2)
	li r3, 0x0
	lfs f2, float_110_8041c480(r2)
	li r4, 0x78
	fmr f4, f1
	lfs f3, float_750_8041c484(r2)
	fmr f6, f1
	lfs f5, float_60_8041c488(r2)
	li r5, 0x4
	bl btl_camera_set_moveto
	@76:
	addi r3, r1, 0x68
	addi r4, r29, 0x1d8
	bl strcpy
	b @4
	@77:
	lfs f1, float_0_8041c454(r2)
	li r0, 0x3
	sth r0, 0x277c(r31)
	addi r5, r1, 0x34
	fmr f4, f1
	lfs f2, float_110_8041c480(r2)
	fmr f6, f1
	sth r0, 0x277e(r31)
	lfs f3, float_500_8041c4c8(r2)
	addi r6, r1, 0x30
	lfs f5, float_60_8041c488(r2)
	addi r7, r1, 0x2c
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x1
	li r4, 0x1
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0x1f4
	bl strcpy
	b @4
	@78:
	lfs f1, float_neg100_8041c468(r2)
	li r0, 0x3
	sth r0, 0x277c(r31)
	addi r5, r1, 0x34
	fmr f4, f1
	lfs f2, float_110_8041c480(r2)
	sth r0, 0x277e(r31)
	addi r6, r1, 0x30
	lfs f3, float_500_8041c4c8(r2)
	addi r7, r1, 0x2c
	lfs f5, float_60_8041c488(r2)
	addi r8, r1, 0x28
	lfs f6, float_0_8041c454(r2)
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x1
	li r4, 0x1
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0x20c
	bl strcpy
	b @4
	@79:
	mr r3, r31
	bl BattleGetMarioPtr
	mr r0, r3
	mr r3, r31
	mr r25, r0
	bl BattleGetPartyPtr
	mr. r26, r3
	beq @80
	mr r3, r25
	addi r4, r1, 0x1c
	addi r5, r1, 0x18
	addi r6, r1, 0x14
	bl BtlUnit_GetHomePos
	mr r3, r26
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	addi r6, r1, 0x8
	bl BtlUnit_GetHomePos
	lfs f3, 0x1c(r1)
	lfs f2, 0x10(r1)
	lfs f1, 0x18(r1)
	lfs f0, 0xc(r1)
	fadds f4, f3, f2
	lfs f5, float_0p5_8041c460(r2)
	fadds f3, f1, f0
	lwz r0, 0x2760(r31)
	lfs f2, 0x14(r1)
	fmuls f1, f5, f4
	lfs f0, 0x8(r1)
	cmpwi r0, 0x12
	fadds f0, f2, f0
	fmuls f6, f5, f3
	fmuls f5, f5, f0
	bne @81
	lfs f0, float_20_8041c4cc(r2)
	fsubs f6, f6, f0
	b @81
	@80:
	mr r3, r25
	addi r4, r1, 0x1c
	addi r5, r1, 0x18
	addi r6, r1, 0x14
	bl BtlUnit_GetHomePos
	lfs f1, 0x1c(r1)
	lfs f6, 0x18(r1)
	lfs f5, 0x14(r1)
	@81:
	lfs f2, float_100_8041c464(r2)
	li r0, 0x1
	lfs f3, float_350_8041c4d0(r2)
	fmr f4, f1
	sth r0, 0x277c(r31)
	fadds f2, f2, f6
	lfs f0, float_50_8041c4a8(r2)
	fadds f3, f3, f5
	sth r0, 0x277e(r31)
	fadds f5, f0, f6
	lfs f6, float_0_8041c454(r2)
	addi r5, r1, 0x34
	addi r6, r1, 0x30
	addi r7, r1, 0x2c
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x0
	li r4, 0x1
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0x224
	bl strcpy
	b @4
	@82:
	addi r3, r1, 0x68
	addi r4, r29, 0x238
	bl strcpy
	b @4
	@83:
	lfs f1, float_neg100_8041c468(r2)
	li r0, 0x2
	sth r0, 0x277c(r31)
	addi r5, r1, 0x34
	fmr f4, f1
	lfs f2, float_100_8041c464(r2)
	sth r0, 0x277e(r31)
	addi r6, r1, 0x30
	lfs f3, float_400_8041c494(r2)
	addi r7, r1, 0x2c
	lfs f5, float_50_8041c4a8(r2)
	addi r8, r1, 0x28
	lfs f6, float_0_8041c454(r2)
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x1
	li r4, 0x1
	bl battleCameraMoveTo
	addi r3, r1, 0x68
	addi r4, r29, 0x24c
	bl strcpy
	b @4
	@2:
	addi r3, r1, 0x68
	addi r4, r29, 0x260
	bl strcpy
	@4:
	lfs f1, 0x14(r30)
	lfs f0, float_1000_8041c4a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @84
	stfs f0, 0x14(r30)
	@84:
	lwz r0, 0x2754(r31)
	rlwinm. r0, r0, 0, 29, 29
	beq @85
	lfs f1, 0x278c(r31)
	lfs f0, float_0_8041c454(r2)
	stfs f1, 0xc(r30)
	lfs f1, 0x27a4(r31)
	stfs f1, 0x18(r30)
	stfs f0, 0x34(r1)
	stfs f0, 0x28(r1)
	@85:
	lwz r0, 0x2754(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @86
	lfs f1, 0x2790(r31)
	lfs f0, float_0_8041c454(r2)
	stfs f1, 0x10(r30)
	lfs f1, 0x27a8(r31)
	stfs f1, 0x1c(r30)
	stfs f0, 0x30(r1)
	stfs f0, 0x24(r1)
	@86:
	lwz r0, 0x2754(r31)
	rlwinm. r0, r0, 0, 27, 27
	beq @87
	lfs f1, 0x2794(r31)
	lfs f0, float_0_8041c454(r2)
	stfs f1, 0x14(r30)
	lfs f1, 0x27ac(r31)
	stfs f1, 0x20(r30)
	stfs f0, 0x2c(r1)
	stfs f0, 0x20(r1)
	@87:
	lfs f0, 0xc(r30)
	stfs f0, 0x2780(r31)
	lfs f0, 0x10(r30)
	stfs f0, 0x2784(r31)
	lfs f0, 0x14(r30)
	stfs f0, 0x2788(r31)
	lfs f0, 0x18(r30)
	stfs f0, 0x2798(r31)
	lfs f0, 0x1c(r30)
	stfs f0, 0x279c(r31)
	lfs f0, 0x20(r30)
	stfs f0, 0x27a0(r31)
	lwz r0, 0xc(r29)
	lwz r3, 0x10(r29)
	stw r0, 0x44(r1)
	lfs f0, 0x34(r1)
	lwz r0, 0x14(r29)
	stfs f0, 0x44(r1)
	lfs f1, 0x30(r1)
	stw r3, 0x48(r1)
	lfs f0, 0x2c(r1)
	stw r0, 0x4c(r1)
	lwz r0, 0x44(r1)
	stfs f1, 0x48(r1)
	stfs f0, 0x4c(r1)
	lwz r3, 0x48(r1)
	stw r0, 0x27bc(r31)
	lwz r0, 0x4c(r1)
	stw r3, 0x27c0(r31)
	stw r0, 0x27c4(r31)
	lwz r4, 0x18(r29)
	lwz r3, 0x1c(r29)
	lwz r0, 0x20(r29)
	stw r4, 0x38(r1)
	lfs f0, 0x28(r1)
	stw r3, 0x3c(r1)
	lfs f1, 0x24(r1)
	stfs f0, 0x38(r1)
	lfs f0, 0x20(r1)
	stw r0, 0x40(r1)
	lwz r0, 0x38(r1)
	stfs f1, 0x3c(r1)
	stfs f0, 0x40(r1)
	lwz r3, 0x3c(r1)
	stw r0, 0x27c8(r31)
	lwz r0, 0x40(r1)
	stw r3, 0x27cc(r31)
	stw r0, 0x27d0(r31)
	lwz r3, 0x2754(r31)
	clrlwi. r0, r3, 31
	bne @88
	rlwinm. r0, r3, 0, 30, 30
	bne @88
	li r3, 0x0
	bl padRumbleOff
	@88:
	lwz r0, 0x2754(r31)
	rlwinm. r0, r0, 0, 25, 25
	beq @89
	li r3, 0x0
	bl padRumbleOff
	@89:
	lwz r0, 0x2754(r31)
	clrlwi. r0, r0, 31
	beq @90
	lha r25, 0x277c(r31)
	li r0, 0x3
	lha r26, 0x277e(r31)
	lwz r4, 0x2838(r31)
	lwz r3, 0x2830(r31)
	sth r0, 0x277c(r31)
	subf r3, r4, r3
	rlwinm r27, r3, 0, 30, 30
	sth r0, 0x277e(r31)
	lwz r5, 0x2830(r31)
	lwz r0, 0x2838(r31)
	lwz r3, 0x2828(r31)
	subf r0, r0, r5
	lfs f1, 0x2840(r31)
	srawi r0, r0, 1
	lfs f2, 0x2844(r31)
	addze r4, r0
	srawi r0, r5, 1
	addze r5, r0
	bl intplGetValue
	stfs f1, 0x2850(r31)
	lwz r0, 0x2838(r31)
	cmpwi r0, 0x0
	ble @91
	cmpwi r27, 0x0
	bne @92
	lfs f3, 0x2850(r31)
	addi r5, r1, 0x34
	lfs f1, 0xc(r30)
	addi r6, r1, 0x30
	lfs f0, 0x18(r30)
	addi r7, r1, 0x2c
	fadds f1, f1, f3
	lfs f2, 0x10(r30)
	fadds f4, f0, f3
	lfs f3, 0x14(r30)
	lfs f5, 0x1c(r30)
	addi r8, r1, 0x28
	lfs f6, 0x20(r30)
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x0
	li r4, 0x0
	bl battleCameraMoveTo
	b @93
	@92:
	lfs f3, 0x2850(r31)
	addi r5, r1, 0x34
	lfs f1, 0xc(r30)
	addi r6, r1, 0x30
	lfs f0, 0x18(r30)
	addi r7, r1, 0x2c
	fsubs f1, f1, f3
	lfs f2, 0x10(r30)
	fsubs f4, f0, f3
	lfs f3, 0x14(r30)
	lfs f5, 0x1c(r30)
	addi r8, r1, 0x28
	lfs f6, 0x20(r30)
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x0
	li r4, 0x0
	bl battleCameraMoveTo
	b @93
	@91:
	bne @93
	lwz r0, 0x2754(r31)
	clrrwi r0, r0, 1
	stw r0, 0x2754(r31)
	@93:
	sth r25, 0x277c(r31)
	sth r26, 0x277e(r31)
	lwz r3, 0x2838(r31)
	subi r0, r3, 0x1
	stw r0, 0x2838(r31)
	@90:
	lwz r0, 0x2754(r31)
	rlwinm. r0, r0, 0, 30, 30
	beq @94
	lha r25, 0x277c(r31)
	li r0, 0x3
	lha r26, 0x277e(r31)
	lwz r4, 0x283c(r31)
	lwz r3, 0x2834(r31)
	sth r0, 0x277c(r31)
	subf r3, r4, r3
	rlwinm r27, r3, 0, 30, 30
	sth r0, 0x277e(r31)
	lwz r5, 0x2834(r31)
	lwz r0, 0x283c(r31)
	lwz r3, 0x282c(r31)
	subf r0, r0, r5
	lfs f1, 0x2848(r31)
	srawi r0, r0, 1
	lfs f2, 0x284c(r31)
	addze r4, r0
	srawi r0, r5, 1
	addze r5, r0
	bl intplGetValue
	stfs f1, 0x2854(r31)
	lwz r0, 0x283c(r31)
	cmpwi r0, 0x0
	ble @95
	cmpwi r27, 0x0
	bne @96
	lfs f3, 0x2854(r31)
	addi r5, r1, 0x34
	lfs f1, 0x10(r30)
	addi r6, r1, 0x30
	lfs f0, 0x1c(r30)
	addi r7, r1, 0x2c
	fadds f2, f1, f3
	lfs f1, 0xc(r30)
	fadds f5, f0, f3
	lfs f3, 0x14(r30)
	lfs f4, 0x18(r30)
	addi r8, r1, 0x28
	lfs f6, 0x20(r30)
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x0
	li r4, 0x0
	bl battleCameraMoveTo
	b @97
	@96:
	lfs f3, 0x2854(r31)
	addi r5, r1, 0x34
	lfs f1, 0x10(r30)
	addi r6, r1, 0x30
	lfs f0, 0x1c(r30)
	addi r7, r1, 0x2c
	fsubs f2, f1, f3
	lfs f1, 0xc(r30)
	fsubs f5, f0, f3
	lfs f3, 0x14(r30)
	lfs f4, 0x18(r30)
	addi r8, r1, 0x28
	lfs f6, 0x20(r30)
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x0
	li r4, 0x0
	bl battleCameraMoveTo
	b @97
	@95:
	bne @97
	lwz r0, 0x2754(r31)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x2754(r31)
	@97:
	sth r25, 0x277c(r31)
	sth r26, 0x277e(r31)
	lwz r3, 0x283c(r31)
	subi r0, r3, 0x1
	stw r0, 0x283c(r31)
	@94:
	psq_l f31, 0xf8(r1), 0, 0
	lfd f31, 0xf0(r1)
	psq_l f30, 0xe8(r1), 0, 0
	lfd f30, 0xe0(r1)
	lmw r25, 0xc4(r1)
	lwz r0, 0x104(r1)
	mtlr r0
	addi r1, r1, 0x100
	blr
}

asm void battleCameraInit(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r4, 0x0
	li r5, 0x104
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	lwz r31, _battleWorkPointer(r13)
	addi r30, r31, 0x2754
	mr r3, r30
	bl memset
	li r0, 0x0
	stw r0, 0x0(r30)
	lwz r3, 0x2738(r31)
	lwz r0, 0x8(r3)
	cmpwi r0, 0x9
	beq @1
	bge @2
	cmpwi r0, 0x0
	beq @3
	bge @4
	b @2
	@4:
	li r0, 0xf
	stw r0, 0xc(r30)
	b @2
	@1:
	li r0, 0x10
	stw r0, 0xc(r30)
	b @2
	@3:
	li r0, 0xe
	stw r0, 0xc(r30)
	@2:
	li r5, 0x0
	lis r3, vec3_802efc40@ha
	stw r5, 0x8(r30)
	li r0, 0x1
	lfs f0, float_0_8041c454(r2)
	addi r4, r3, vec3_802efc40@l
	stfs f0, 0x24(r30)
	sth r0, 0x28(r30)
	sth r0, 0x2a(r30)
	lwz r3, 0x0(r4)
	lwz r0, 0x4(r4)
	stw r3, 0x5c(r30)
	stw r0, 0x60(r30)
	lwz r0, 0x8(r4)
	stw r0, 0x64(r30)
	stw r5, 0x4(r30)
	lmw r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_05_80362094_data[1] = {0};
__declspec(section ".sdata2") const u32 gap_09_8041C4D4_sdata2[1] = {0};
