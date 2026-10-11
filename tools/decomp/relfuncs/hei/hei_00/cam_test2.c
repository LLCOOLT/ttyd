// include: mario/mario.h
// include: mario/mario_party.h
// include: party.h
// include: driver/camdrv.h
// include: dolphin/mtx.h
// decl: typedef struct CamRoadOut { Vec unk0; Vec target; Vec pos; } CamRoadOut;
// decl: void camRoadMain(CamRoadOut* out, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);
// proto: USER_FUNC(cam_test2);
USER_FUNC(cam_test2) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    CameraEntry* camera = camGetPtr(4);
    f32 cx = (mario->position.x + party->position.x) / 2;
    f32 cz = (mario->position.z + party->position.z) / 2;
    CamRoadOut road;
    Vec dir;

    camRoadMain(&road, 0.0f, 75.0f, 0.0f, 0.0f, 75.0f, 0.0f, 0.0f);
    dir = (Vec){road.target.x - road.pos.x, road.target.y - road.pos.y, road.target.z - road.pos.z};
    PSVECNormalize(&dir, &dir);
    event->lwData[0] = cx + road.pos.x + 270.0f * dir.x;
    event->lwData[1] = road.pos.y + 270.0f * dir.y;
    event->lwData[2] = cz + road.pos.z + 270.0f * dir.z;
    event->lwData[3] = cx + road.pos.x;
    event->lwData[4] = road.pos.y;
    event->lwData[5] = cz + road.pos.z;
    return EVT_RETURN_DONE;
}
