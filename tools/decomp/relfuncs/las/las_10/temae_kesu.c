// include: driver/camdrv.h
// decl: void mapGrpFlagOn(const char* name, u32 flags);
// decl: void mapGrpFlagOff(const char* name, u32 flags);
// proto: USER_FUNC(temae_kesu);
USER_FUNC(temae_kesu) {
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    s32 idx;
    s32 prev;
    s32 next;

    mapGrpFlagOff("S_kesu", 1);
    mapGrpFlagOff("S11_kabe", 1);
    mapGrpFlagOff("S112_kabe", 1);
    mapGrpFlagOff("S113_kabe", 1);
    // show the walls of the camera's octant and its neighbours
    idx = (157.5f + cam->viewYaw) / 45.0f;
    idx %= 8;
    prev = idx != 0 ? idx - 1 : 7;
    next = idx == 7 ? 0 : idx + 1;
    mapGrpFlagOn((const char*)kabe_list_1[idx], 1);
    mapGrpFlagOn((const char*)kabe_list_1[prev], 1);
    mapGrpFlagOn((const char*)kabe_list_1[next], 1);
    mapGrpFlagOn((const char*)kabe_list_2[idx], 1);
    mapGrpFlagOn((const char*)kabe_list_2[prev], 1);
    mapGrpFlagOn((const char*)kabe_list_2[next], 1);
    mapGrpFlagOn((const char*)kabe_list_3[idx], 1);
    mapGrpFlagOn((const char*)kabe_list_3[prev], 1);
    mapGrpFlagOn((const char*)kabe_list_3[next], 1);
    if (idx >= 2 && idx <= 4) {
        mapGrpFlagOn("S14_hashira", 1);
        mapGrpFlagOn("S115_hashira", 1);
        mapGrpFlagOn("S116_hashira", 1);
    }
    return EVT_RETURN_DONE;
}
