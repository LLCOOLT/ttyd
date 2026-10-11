// include: stdio.h
// include: string.h
// decl: typedef struct RshDebugStr { char str[256]; } RshDebugStr;
// proto: USER_FUNC(debug_print_func);
USER_FUNC(debug_print_func) {
    s32* args = event->args;
    s32 room = evtGetValue(event, args[0]);
    s32 group = evtGetValue(event, args[1]);
    s32 index = evtGetValue(event, args[2]);
    s32 value = evtGetValue(event, args[3]);
    char header[256];
    char buf[256];
    const char** list;

    *(RshDebugStr*)header = rsh_debug_str_init;

    switch (room) {
    case 0:
        strcpy(header, "RSH_01:");
        switch (group) {
        case 0:
            list = (const char**)rsh_01_rnd_npc_1_list;
            break;
        case 1:
            list = (const char**)rsh_01_rnd_npc_2_list;
            break;
        case 2:
            list = (const char**)rsh_01_rnd_npc_3_list;
            break;
        }
        break;
    case 1:
        strcpy(header, "RSH_03:");
        switch (group) {
        case 0:
            list = (const char**)rsh_03_rnd_npc_1_list;
            break;
        case 1:
            list = (const char**)rsh_03_rnd_npc_2_list;
            break;
        }
        break;
    case 2:
        strcpy(header, "RSH_04:");
        switch (group) {
        case 0:
            list = (const char**)rsh_04_rnd_npc_1_list;
            break;
        case 1:
            list = (const char**)rsh_04_rnd_npc_2_list;
            break;
        case 2:
            list = (const char**)rsh_04_rnd_npc_3_list;
            break;
        case 3:
            list = (const char**)rsh_04_rnd_npc_4_list;
            break;
        }
        break;
    }
    sprintf(buf, "%s%d(%s, %s)\n", header, group, list[index], value);
    return EVT_RETURN_DONE;
}
