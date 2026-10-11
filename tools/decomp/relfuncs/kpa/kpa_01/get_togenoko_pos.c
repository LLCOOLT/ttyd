// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// proto: USER_FUNC(get_togenoko_pos);
USER_FUNC(get_togenoko_pos) {
    s32* args = event->args;
    f32 cx = evtGetFloat(event, args[0]);
    f32 cz = evtGetFloat(event, args[1]);
    f32 x = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    f32 angle = evtGetFloat(event, args[4]);
    Mtx mtx;
    Vec pos;

    PSMTXRotRad(mtx, 'Y', 0.017453292f * angle);
    pos.x = x - cx;
    pos.y = 0.0f;
    pos.z = z - cz;
    PSMTXMultVec(mtx, &pos, &pos);
    pos.x += cx;
    pos.z += cz;
    evtSetFloat(event, args[5], pos.x);
    evtSetFloat(event, args[6], pos.z);
    return EVT_RETURN_DONE;
}
