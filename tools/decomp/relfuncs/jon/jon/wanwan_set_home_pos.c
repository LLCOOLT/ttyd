// include: manager/evtmgr_cmd.h
// decl: extern s32 npcEnt_wanwan[];
// proto: USER_FUNC(wanwan_set_home_pos);
USER_FUNC(wanwan_set_home_pos) {
    s32* args = event->args;
    s32 x = evtGetValue(event, args[0]);
    s32 y = evtGetValue(event, args[1]);
    s32 z = evtGetValue(event, args[2]);

    ((f32*)npcEnt_wanwan)[12] = x;
    ((f32*)npcEnt_wanwan)[13] = y;
    ((f32*)npcEnt_wanwan)[14] = z;
    return EVT_RETURN_DONE;
}
