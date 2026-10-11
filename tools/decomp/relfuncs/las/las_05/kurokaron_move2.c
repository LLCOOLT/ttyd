// include: mario/mario.h
// include: driver/npcdrv.h
// include: system.h
// decl: extern u8 kurokaron_move_index;
// decl: extern u8 kurokaron_move_flag;
// decl: int rand(void);
// decl: s32 _kurokaron_run_away(f32 x, f32 z, f32 tx, f32 tz);
// proto: s32 kurokaron_move2(NpcEntry* npc, MarioWork* mario);
s32 kurokaron_move2(NpcEntry* npc, MarioWork* mario) {
    static s32 count;
    static s32 flag;
    f32 angle;

    if (!(kurokaron_move_flag & 2)) {
        flag = 0;
        return 0;
    }
    kurokaron_move_flag &= ~4;
    if (npc->position.x < -560.0f || npc->position.x > 560.0f || npc->position.z < -260.0f || npc->position.z > 260.0f) {
        if (rand() % 100 == 0) {
            if (kurokaron_move_flag & 8) {
                kurokaron_move_flag &= ~8;
            } else {
                kurokaron_move_flag |= 8;
            }
        }
        angle = angleABf(mario->position.x, mario->position.z, npc->position.x, npc->position.z);
        if (kurokaron_move_flag & 8) {
            npc->moveDir = reviseAngle(angle - 90.0f);
        } else {
            npc->moveDir = reviseAngle(angle + 90.0f);
        }
        kurokaron_move_flag |= 4;
        flag = 0;
        return 0;
    }
    if (distABf(npc->position.x, npc->position.z, mario->position.x, mario->position.z) < 100.0f) {
        if (count != 0) {
            count--;
        } else {
            if (npc->position.x < -490.0f || npc->position.x > 490.0f || npc->position.z < -190.0f || npc->position.z > 190.0f) {
                angle = angleABf(mario->position.x, mario->position.z, npc->position.x, npc->position.z);
                if (kurokaron_move_flag & 8) {
                    npc->moveDir = angle - 90.0f;
                } else {
                    npc->moveDir = angle + 90.0f;
                }
                count = 10;
            } else {
                npc->moveDir = angleABf(mario->position.x, mario->position.z, npc->position.x, npc->position.z);
                count = 20;
            }
            flag = 0;
        }
        return 0;
    }
    if (flag == 0) {
        kurokaron_move_index = _kurokaron_run_away(npc->position.x, npc->position.z, mario->position.x, mario->position.z);
        flag = 1;
        return 1;
    }
    return 0;
}
