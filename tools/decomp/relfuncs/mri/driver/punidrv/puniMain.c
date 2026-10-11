// include: driver/punidrv.h
// include: win/win_main.h
// include: system.h
// decl: static f32 camGetRy(void);
// decl: static s32 compare(const void* a, const void* b);
// proto: void puniMain(void);
void puniMain(void) {
    PunidrvWork* wp = work;
    s32 i;
    PunidrvPose* pose;
    PunidrvSort* sort;
    CameraEntry* cam;
    f32 ry, angle, diff, c, s;
    u32 flags;

    if (!winCheck() && wp->mainFunc != NULL) {
        wp->mainFunc();
    }
    if (wp->mainFunc2 != NULL) {
        wp->mainFunc2();
    }
    pose = wp->poses;
    sort = wp->sort;
    ry = camGetRy();
    cam = camGetPtr(CAMERA_3D);
    cam = camGetPtr(CAMERA_3D);
    for (i = wp->poseNum - 1; i >= 0; i--, pose++, sort++) {
        flags = pose->flags;
        sort->index = i;
        if (flags & 1) {
            sort->z = pose->texId;
        }
        angle = 90.0f + (ry - pose->dir);
        while (angle < -360.0f) {
            angle += 360.0f;
        }
        while (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if ((angle > 90.0f && angle <= 270.0f) || (angle < -90.0f && angle >= -270.0f)) {
            pose->targetRy = 180.0f + ry;
        } else {
            pose->targetRy = camGetRy();
        }
        while (pose->targetRy - pose->ry > 180.0f) {
            pose->ry += 360.0f;
        }
        while ((diff = pose->targetRy - pose->ry) < -180.0f) {
            pose->ry -= 360.0f;
        }
        if (flags & 2) {
            pose->ry = pose->ry + diff * 0.1f;
        } else {
            pose->ry = pose->targetRy;
        }
        angle = pose->ry;
        while (angle < 0.0f) {
            angle += 360.0f;
        }
        while (angle >= 360.0f) {
            angle -= 360.0f;
        }
        c = sintbl[(s32)angle + 90];
        s = sintbl[(s32)angle];
        (*pose->mtx)[0][0] = c;
        (*pose->mtx)[2][2] = c;
        (*pose->mtx)[0][2] = s;
        (*pose->mtx)[2][0] = -s;
    }
    if (wp->poseNum != 0) {
        qqsort(wp->sort, wp->poseNum, sizeof(PunidrvSort), (void*)compare);
    }
    wp->curTex = -1;
    wp->usedTmem = 0;
}
