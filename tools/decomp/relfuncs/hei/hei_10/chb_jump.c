// include: system.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Chorobon { s16 flags; s16 state; s16 field_0x4; u8 field_0x6[2]; Vec target; f32 vy; s16 timer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[0x30 - 0x26]; } Chorobon;
// proto: void chb_jump(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
void chb_jump(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity) {
    f32 dy;
    f32 dist;
    f32 angle;

    chb->target = (Vec){x, y, z};
    chb->speed = speed;
    chb->gravity = gravity;
    dy = chb->target.y - pose->mtx[1][3];
    dist = distABf(pose->mtx[0][3], pose->mtx[2][3], chb->target.x, chb->target.z);
    angle = angleABf(pose->mtx[0][3], pose->mtx[2][3], chb->target.x, chb->target.z);
    chb->timer = dist / chb->speed;
    chb->vy = dy / chb->timer + chb->gravity * chb->timer / 2;
    chb->state = 100;
    chb->next = next;
}
