// include: driver/npcdrv.h
// include: driver/effdrv.h
// include: driver/camdrv.h
// include: system.h
// include: dolphin/mtx.h
// proto: USER_FUNC(syuryo_baria_recalc_pos);
USER_FUNC(syuryo_baria_recalc_pos) {
    // ピーチ単
    NpcEntry* npc = npcNameToPtr("\x83\x73\x81\x5B\x83\x60\x95\x50");
    static const Vec base = {0.0f, -8.0f, 10.0f};
    Vec offset = base;
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    EffectEntry* eff = effNameToPtr("baria");
    Mtx mtx;
    f32 angle;

    angle = angleABf(cam->cameraPos.x, cam->cameraPos.z, npc->position.x, npc->position.z);
    PSMTXRotRad(mtx, 'Y', 0.017453292f * -angle);
    PSMTXMultVec(mtx, &offset, &offset);
    ((f32*)eff->userdata)[1] = npc->position.x + offset.x;
    ((f32*)eff->userdata)[2] = npc->position.y + offset.y;
    ((f32*)eff->userdata)[3] = npc->position.z + offset.z;
    return EVT_RETURN_DONE;
}
