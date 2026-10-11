// include: driver/camdrv.h
// include: system.h
// decl: double atan2(double y, double x);
// proto: static f32 camGetRy(void);
static f32 camGetRy(void) {
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    f32 ry = reviseAngle(57.29579f * (f32)atan2(-(cam->cameraAt.x - cam->cameraPos.x), -(cam->cameraAt.z - cam->cameraPos.z)));

    if (ry < 0.0f) {
        ry += 360.0f;
    }
    return ry;
}
