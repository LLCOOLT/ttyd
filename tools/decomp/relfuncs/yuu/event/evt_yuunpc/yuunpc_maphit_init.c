// include: driver/npcdrv.h
// include: driver/extdrv.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct YuuNpcPose { char name[16]; char anim[8]; u16 field_0x18; f32 frames; f32 jump; s32 start; s32 count; u16 flags; f32 field_0x30; } YuuNpcPose;
// decl: typedef struct YuuNpc { s16 id; u16 flags; s16 state; f32 field_0x8; Vec goal; Vec dest; Vec pos; u8 field_0x30[0xC]; f32 radius; f32 vy; u8 field_0x44[0x10]; s16 poseId; u8 field_0x56[0xA]; NpcEntry* npc; f32 animSpeed; u64 time; } YuuNpc;
// decl: typedef struct YuuNpcWork { u16 flags; s32 numNpc; u8 field_0x8[0xC]; YuuNpc* npcs; s32 basePoseNum; s32 numPoses; s32 chusanPose; s16 hit[6][72]; s16 hitY[72]; YuuNpcPose pose[32]; } YuuNpcWork;
// decl: static YuuNpcWork* yuunpc_wp;
// proto: void yuunpc_maphit_init(void);
void yuunpc_maphit_init(void) {
    char key[3] = "\x81\xA1";
    s32 i;
    s32 j;

    for (i = 0; i < 72; i++) {
        yuunpc_wp->hitY[i] = (hitdata[i * 2] - '0') * 10 + hitdata[i * 2 + 1] - '0';
    }
    for (i = 0; i < 72; i++) {
        s16 h = -((hitdata[0x90 + i * 2] - '0') * 10 + hitdata[0x90 + i * 2 + 1] - '0');
        yuunpc_wp->hit[5][i] = h;
        yuunpc_wp->hit[4][i] = h;
        yuunpc_wp->hit[3][i] = h;
        yuunpc_wp->hit[2][i] = h;
        yuunpc_wp->hit[1][i] = h;
        yuunpc_wp->hit[0][i] = h;
    }
    for (j = 0; j < 6; j++) {
        for (i = 0; i < 72; i++) {
            if (key[0] == hitdata[0x120 + j * 0x90 + i * 2] && key[1] == hitdata[0x120 + j * 0x90 + i * 2 + 1]) {
                yuunpc_wp->hit[j][i] = -500;
            }
        }
    }
}
