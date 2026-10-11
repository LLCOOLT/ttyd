// include: driver/npcdrv.h
// include: driver/camdrv.h
// include: mario/mario.h
// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// proto: USER_FUNC(zoom);
USER_FUNC(zoom) {
    s32* args = event->args;
    // ナリキンパパ
    NpcEntry* npc = npcNameToPtr("\x83\x69\x83\x8A\x83\x4C\x83\x93\x83\x70\x83\x70");
    MarioWork* mario = marioGetPtr();
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    Vec v;

    PSVECSubtract(&cam->cameraPos, &cam->cameraAt, &v);
    PSVECScale(&v, &v, 0.7f);
    PSVECAdd(&cam->cameraAt, &v, &v);
    evtSetFloat(event, args[0], (npc->position.x + mario->position.x) / 2);
    evtSetFloat(event, args[1], v.y);
    evtSetFloat(event, args[2], v.z);
    evtSetFloat(event, args[3], (npc->position.x + mario->position.x) / 2);
    evtSetFloat(event, args[4], cam->cameraAt.y);
    evtSetFloat(event, args[5], cam->cameraAt.z);
    return EVT_RETURN_DONE;
}
