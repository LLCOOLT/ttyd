// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// decl: void mapSetProjMtx(Mtx mtx);
// proto: static USER_FUNC(proj_mtx);
static USER_FUNC(proj_mtx) {
    s32* args = event->args;
    f32 px = evtGetFloat(event, args[0]);
    f32 py = evtGetFloat(event, args[1]);
    f32 pz = evtGetFloat(event, args[2]);
    f32 tx = evtGetFloat(event, args[3]);
    f32 ty = evtGetFloat(event, args[4]);
    f32 tz = evtGetFloat(event, args[5]);
    Mtx view;
    Mtx proj;
    Mtx rot;
    Vec pos;
    Vec target;
    Vec up;

    pos = (Vec){px, py, pz};
    target = (Vec){tx, ty, tz};
    up = (Vec){1.0f, 0.0f, 0.0f};
    C_MTXLightPerspective(proj, 25.0f, 1.2666667f, 0.5f, 0.5f, 0.5f, 0.5f);
    C_MTXLookAt(view, &pos, &up, &target);
    PSMTXRotRad(rot, 'y', 0.17453292f);
    PSMTXConcat(proj, view, proj);
    PSMTXConcat(proj, rot, proj);
    mapSetProjMtx(proj);
    return EVT_RETURN_DONE;
}
