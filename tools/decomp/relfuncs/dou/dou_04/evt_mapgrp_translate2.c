// include: mario/mario.h
// include: driver/hitdrv.h
// include: manager/evtmgr_cmd.h
// include: string.h
// decl: void mapObjTranslate(const char* name, f32 x, f32 y, f32 z);
// proto: USER_FUNC(evt_mapgrp_translate2);
USER_FUNC(evt_mapgrp_translate2) {
    s32* args = event->args;
    MarioWork* mario = marioGetPtr();
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    const char* hitName = (const char*)evtGetValue(event, args[4]);
    f32* prev = (f32*)&event->lwData[6];
    HitEntry* hit;

    mapObjTranslate(name, x, y, z);
    x = 10.0f * (x / 10.0f);
    y = 10.0f * (y / 10.0f);
    z = 10.0f * (z / 10.0f);
    hit = marioGetPtr()->hitobjStandOn;
    if (hit != NULL && strcmp(hitName, hitGetName(hit)) == 0) {
        mario->unk174.x = x - prev[0];
        mario->unk174.y = y - prev[1];
        mario->unk174.z = z - prev[2];
    }
    prev[0] = 10.0f * (x / 10.0f);
    prev[1] = 10.0f * (y / 10.0f);
    prev[2] = 10.0f * (z / 10.0f);
    return EVT_RETURN_DONE;
}
