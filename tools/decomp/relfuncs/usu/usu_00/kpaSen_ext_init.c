// include: memory.h
// include: dolphin/mtx.h
// include: stdlib.h
// decl: typedef struct KpaSen { s8 state; u8 field_0x1; u16 wait; f32 t; Vec start; Vec end; u8 pose99Lo; u8 pose99Hi; u8 pose1Lo; u8 pose1Hi; } KpaSen;
// decl: KpaSen* kpaSen;
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// proto: void kpaSen_ext_init(void);
void kpaSen_ext_init(void) {
    ExtPose* pose = extGetPosePtr();
    Vec base = {85.0f, 0.0f, 75.0f};
    s32 i;

    kpaSen = _mapAlloc(sizeof(KpaSen) * 200);
    for (i = 0; i < extGetPoseNum(); i++, pose++) {
        pose->flags |= 3;
        PSMTXIdentity(pose->mtx);
        if (i < 100) {
            pose->rot = 90.0f;
            kpaSen[i].end.x = (base.x + 30.0f * ((f32)i / 10.0f)) - 9.0f;
            kpaSen[i].end.y = 0.0f;
            kpaSen[i].end.z = base.z + 50.0f * (f32)(i % 10 - 5);
            pose->mtx[0][3] = kpaSen[i].start.x = base.x + 200.0f;
            pose->mtx[1][3] = kpaSen[i].start.y = 0.0f;
            pose->mtx[2][3] = kpaSen[i].start.z = base.z + 20.0f * (f32)(i % 10 - 5);
            kpaSen[i].wait = (i / 10) * 3 + 1;
            kpaSen[i].pose99Lo = 0;
            kpaSen[i].pose99Hi = 5;
            kpaSen[i].pose1Lo = 6;
            kpaSen[i].pose1Hi = 8;
        } else {
            pose->rot = 270.0f;
            kpaSen[i].end.x = (base.x + -30.0f * ((f32)(i - 100) / 10.0f)) - 150.0f;
            kpaSen[i].end.y = 0.0f;
            kpaSen[i].end.z = base.z + 50.0f * (f32)((i - 100) % 10 - 5);
            pose->mtx[0][3] = kpaSen[i].start.x = base.x - 350.0f;
            pose->mtx[1][3] = kpaSen[i].start.y = 0.0f;
            pose->mtx[2][3] = kpaSen[i].start.z = base.z + 20.0f * (f32)((i - 100) % 10 - 5);
            kpaSen[i].wait = ((i - 100) / 10) * 3 + 1;
            switch (rand() % 3) {
                case 0:
                    kpaSen[i].pose99Lo = 9;
                    kpaSen[i].pose99Hi = 14;
                    kpaSen[i].pose1Lo = 15;
                    kpaSen[i].pose1Hi = 17;
                    break;
                case 1:
                    kpaSen[i].pose99Lo = 18;
                    kpaSen[i].pose99Hi = 23;
                    kpaSen[i].pose1Lo = 24;
                    kpaSen[i].pose1Hi = 26;
                    break;
                case 2:
                    kpaSen[i].pose99Lo = 27;
                    kpaSen[i].pose99Hi = 34;
                    kpaSen[i].pose1Lo = 35;
                    kpaSen[i].pose1Hi = 37;
                    break;
            }
        }
        kpaSen[i].state = -1;
        kpaSen[i].t = 0.0f;
        if (i == 6) {
            pose->flags &= ~1;
        }
        if (i == 106 || i == 116) {
            pose->flags &= ~1;
        }
    }
}
