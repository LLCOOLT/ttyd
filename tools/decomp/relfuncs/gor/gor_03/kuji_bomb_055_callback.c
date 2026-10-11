// include: driver/npcdrv.h
// include: driver/animdrv.h
// decl: typedef struct KujiMsgWork { u8 unk0[8]; u16 unk8; u8 unkA[6]; s32 unk10; } KujiMsgWork;
// proto: void kuji_bomb_055_callback(s32 type, KujiMsgWork** work);
void kuji_bomb_055_callback(s32 type, KujiMsgWork** work) {
    KujiMsgWork* wp = *work;
    NpcEntry* npc = npcNameToPtr("\203O\203\213\203\201\203{\203\200\225\272");

    switch (type) {
        case 3:
            if (wp->unk8 == 1) {
                evtSetValue(NULL, GF(0), 1);
            }
            break;
        case 5:
            switch (wp->unk10) {
                case 0x1D:
                    animPoseSetAnim(npc->poseId, "T_3", 1);
                    break;
                case 0xC8:
                    animPoseSetAnim(npc->poseId, "T_4", 1);
                    break;
                case 0x158:
                    animPoseSetAnim(npc->poseId, "T_3", 1);
                    break;
                case 0x1F1:
                    animPoseSetAnim(npc->poseId, "T_4", 1);
                    break;
                case 0x2B7:
                case 0x2B8:
                    npc->flags &= ~0x200;
                    animPoseSetAnim(npc->poseId, "B_1", 1);
                    break;
            }
            break;
    }
}
