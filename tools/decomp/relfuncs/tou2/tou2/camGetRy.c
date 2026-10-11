// include: tou2.h
// include: dolphin/types.h
// include: dolphin/mtx.h
// include: dolphin/gx.h
// include: driver/swdrv.h
// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: driver/camdrv.h
// include: driver/effdrv.h
// include: driver/dispdrv.h
// include: driver/windowdrv.h
// include: driver/icondrv.h
// include: driver/msgdrv.h
// include: manager/fontmgr.h
// include: manager/evtmgr_cmd.h
// include: evt/evt_cmd.h
// include: battle/battle_monosiri.h
// include: data/mapdata.h
// include: mario/mario_pouch.h
// include: pmario_sound.h
// include: system.h
// include: memory.h
// include: string.h
// include: stdio.h
// note: tou2.c is hand-maintained (typed data/structs are defined there); this snippet mirrors it
// proto: static f32 camGetRy(void);
static f32 camGetRy(void) {
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    f32 ry = reviseAngle(57.29579f * atan2f(-(cam->cameraAt.x - cam->cameraPos.x), -(cam->cameraAt.z - cam->cameraPos.z)));

    if (ry < 0.0f) {
        ry += 360.0f;
    }
    return ry;
}
