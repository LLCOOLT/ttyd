// include: mario/mariost.h
// decl: typedef struct KpaSen { s8 state; u8 field_0x1; u16 wait; f32 t; Vec start; Vec end; u8 pose99Lo; u8 pose99Hi; u8 pose1Lo; u8 pose1Hi; } KpaSen;
// decl: KpaSen* kpaSen;
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: s32 calcPose(s32 i, s32 lo, s32 hi, s32 flag);
// proto: void kpaSen_ext_main(void);
void kpaSen_ext_main(void) {
    ExtPose* pose = extGetPosePtr();
    s32 i;

    for (i = 0; i < extGetPoseNum(); i++, pose++) {
        switch (kpaSen[i].state) {
            case 0:
                kpaSen[i].wait--;
                if (kpaSen[i].wait == 0) {
                    kpaSen[i].state++;
                }
                break;
            case 1:
                if (i < 100) {
                    pose->frame = calcPose(i, kpaSen[i].pose1Lo, kpaSen[i].pose1Hi, 1);
                    if (i % 10 == 0) {
                    }
                } else {
                    pose->frame = calcPose(i - 100, kpaSen[i].pose1Lo, kpaSen[i].pose1Hi, 1);
                }
                pose->mtx[0][3] = kpaSen[i].start.x * (1.0f - kpaSen[i].t) + kpaSen[i].end.x * kpaSen[i].t;
                pose->mtx[2][3] = kpaSen[i].start.z * (1.0f - kpaSen[i].t) + kpaSen[i].end.z * kpaSen[i].t;
                kpaSen[i].t += 0.03;
                kpaSen[i].wait++;
                if (kpaSen[i].t >= 1.0f) {
                    pose->mtx[0][3] = kpaSen[i].end.x;
                    pose->mtx[2][3] = kpaSen[i].end.z;
                    kpaSen[i].state = 99;
                }
                break;
            case 99:
                if (i < 100) {
                    pose->frame = calcPose(i, kpaSen[i].pose99Lo, kpaSen[i].pose99Hi, 0);
                } else {
                    pose->frame = calcPose(i - 100, kpaSen[i].pose99Lo, kpaSen[i].pose99Hi, 0);
                }
                break;
            case -1:
                break;
        }
    }
}
