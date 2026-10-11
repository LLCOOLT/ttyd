// decl: typedef struct RshRndNpc { const char* name; const char* model; s32* talkEvt; } RshRndNpc;
// proto: RshRndNpc* _get_rnd_npc_data(s32 room, s32 group, s32 index);
RshRndNpc* _get_rnd_npc_data(s32 room, s32 group, s32 index) {
    RshRndNpc* data = NULL;

    switch (room) {
    case 0:
        switch (group) {
        case 0:
            data = (RshRndNpc*)rsh_01_rnd_npc_1;
            break;
        case 1:
            data = (RshRndNpc*)rsh_01_rnd_npc_2;
            break;
        case 2:
            data = (RshRndNpc*)rsh_01_rnd_npc_3;
            break;
        }
        break;
    case 1:
        switch (group) {
        case 0:
            data = (RshRndNpc*)rsh_03_rnd_npc_1;
            break;
        case 1:
            data = (RshRndNpc*)rsh_03_rnd_npc_2;
            break;
        }
        break;
    case 2:
        switch (group) {
        case 0:
            data = (RshRndNpc*)rsh_04_rnd_npc_1;
            break;
        case 1:
            data = (RshRndNpc*)rsh_04_rnd_npc_2;
            break;
        case 2:
            data = (RshRndNpc*)rsh_04_rnd_npc_3;
            break;
        case 3:
            data = (RshRndNpc*)rsh_04_rnd_npc_4;
            break;
        }
        break;
    }
    if (data == NULL) {
        data = (RshRndNpc*)rsh_01_rnd_npc_1;
        index = 0;
    }
    return &data[index];
}
