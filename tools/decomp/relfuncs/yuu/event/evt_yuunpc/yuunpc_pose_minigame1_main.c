// include: driver/npcdrv.h
// include: driver/extdrv.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct YuuNpcPose { char name[16]; char anim[8]; u16 field_0x18; f32 frames; f32 jump; s32 start; s32 count; u16 flags; f32 field_0x30; } YuuNpcPose;
// decl: typedef struct YuuNpc { s16 id; u16 flags; s16 state; f32 field_0x8; Vec goal; Vec dest; Vec pos; u8 field_0x30[0xC]; f32 radius; f32 vy; u8 field_0x44[0x10]; s16 poseId; u8 field_0x56[0xA]; NpcEntry* npc; f32 animSpeed; u64 time; } YuuNpc;
// decl: typedef struct YuuNpcWork { u16 flags; s32 numNpc; u8 field_0x8[0xC]; YuuNpc* npcs; s32 basePoseNum; s32 numPoses; s32 chusanPose; s16 hit[6][72]; s16 hitY[72]; YuuNpcPose pose[32]; } YuuNpcWork;
// decl: static YuuNpcWork* yuunpc_wp;
// include: driver/camdrv.h
// include: system.h
// decl: f32 yuunpc_pose_sub(ExtPose* ext, YuuNpc* npc);
// decl: ExtPose* extGetPosePtr(void);
// proto: void yuunpc_pose_minigame1_main(void);
void yuunpc_pose_minigame1_main(void) {
    f32 camX = camGetPtr(4)->cameraAt.x;
    ExtPose* ext = extGetPosePtr();
    f32 right = 500.0f + camX;
    s32 i;
    YuuNpc* npc = yuunpc_wp->npcs;
    f32 x, y, z;

    for (i = 0; i < yuunpc_wp->numNpc; i++, ext++, npc++) {
        if (npc->flags & 1) {
            x = ext->mtx[0][3];
            if (x > camX) {
                while (x > right) {
                    x -= 1000.0f;
                    ext->mtx[0][3] = x;
                }
            } else {
                while (x < camX - 500.0f) {
                    x += 1000.0f;
                    ext->mtx[0][3] = x;
                }
            }
            z = ext->mtx[2][3];
            if (z < -260.0f) {
                y = ext->mtx[1][3];
                if ((x >= -5000.0f && x <= -1500.0f) || (x >= 1700.0f && x <= 5000.0f) || (x >= 6000.0f && x <= 7000.0f)) {
                    if (y > -500.0f) {
                        ext->mtx[1][3] = y + -1000.0f;
                    }
                } else {
                    if (y < -500.0f) {
                        ext->mtx[1][3] = y - -1000.0f;
                    }
                }
            }
            if (irand(150) == 0) {
                if (irand(101) <= 80) {
                    ext->rot = angleABf(camX, 0.0f, x, z);
                } else {
                    ext->rot = angleABf(camX, 0.0f, x - 2.0f * (x - camX), z);
                }
            }
        }
        yuunpc_pose_sub(ext, npc);
    }
}
