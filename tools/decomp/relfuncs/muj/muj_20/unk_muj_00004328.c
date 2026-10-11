// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// proto: USER_FUNC(unk_muj_00004328);
USER_FUNC(unk_muj_00004328) {
    f32 x = evtGetFloat(event, GW(0));
    f32 y = evtGetFloat(event, GW(1));
    f32 z = evtGetFloat(event, GW(2));
    f32 rot = evtGetFloat(event, LW(0));
    f32 angle = 5.0f * x / -6000.0f;
    Vec pos = {0.0f, 0.0f, 0.0f};
    Vec out;
    Mtx m, rotm, trans;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    out = pos;
    MTXTrans(trans, 0.0f, -6000.0f, 0.0f);
    MTXRotRad(rotm, 'z', angle * 0.017453292f);
    MTXConcat(trans, rotm, m);
    MTXTrans(trans, 0.0f, 6000.0f, 0.0f);
    MTXConcat(m, trans, m);
    MTXMultVec(m, &out, &out);
    evtSetFloat(event, LW(7), out.x);
    evtSetFloat(event, LW(8), out.y);
    evtSetFloat(event, LW(9), out.z);
    evtSetFloat(event, LW(0), rot + angle);
    return EVT_RETURN_DONE;
}
