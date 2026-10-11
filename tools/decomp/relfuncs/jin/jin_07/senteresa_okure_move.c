// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// proto: USER_FUNC(senteresa_okure_move);
USER_FUNC(senteresa_okure_move) {
    s32* args = event->args;
    NpcEntry* npc = npcNameToPtr("\203e\203\214\203T");
    f32 t = evtGetFloat(event, args[0]);
    Vec pos;
    Vec m0 = {0.0f, 250.0f, 0.0f};
    Vec m1 = {1.0f, 0.0f, 0.0f};
    f32 u = 1.0f - t;
    f32 t2 = 2.0f * t;
    f32 h00 = (1.0f + t2) * u * u;
    f32 h10 = t * u * u;
    f32 tt = (0, t * t);
    f32 h11 = (t - 1.0f) * tt;
    f32 h01 = (3.0f - t2) * tt;

    pos.x = event->lwData[10] * h00 + m0.x * h10 + m1.x * h11 + event->lwData[13] * h01;
    pos.y = event->lwData[11] * h00 + m0.y * h10 + m1.y * h11 + event->lwData[14] * h01;
    pos.z = event->lwData[12] * h00 + m0.z * h10 + m1.z * h11 + event->lwData[15] * h01;
    npc->position = pos;
    return EVT_RETURN_DONE;
}
