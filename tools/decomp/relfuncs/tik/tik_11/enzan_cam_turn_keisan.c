// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// proto: static USER_FUNC(enzan_cam_turn_keisan);
static USER_FUNC(enzan_cam_turn_keisan) {
    s32* args = event->args;
    f32 angle = evtGetValue(event, args[0]) % 360;
    s32 xVar = args[1];
    s32 zVar = args[2];
    Vec pos;
    Vec center;
    Mtx mtx;

    pos.x = evtGetValue(event, xVar);
    pos.z = evtGetValue(event, zVar);
    pos.y = 0.0f;
    center.x = evtGetValue(event, args[3]);
    center.z = evtGetValue(event, args[4]);
    center.y = 0.0f;
    PSVECSubtract(&pos, &center, &pos);
    PSMTXRotRad(mtx, 'Y', 0.017453292f * angle);
    PSMTXMultVec(mtx, &pos, &pos);
    PSVECAdd(&pos, &center, &pos);
    evtSetValue(event, xVar, pos.x);
    evtSetValue(event, zVar, pos.z);
    return EVT_RETURN_DONE;
}
