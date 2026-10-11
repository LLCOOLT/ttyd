// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(wait_anim_frame);
USER_FUNC(wait_anim_frame) {
    f32 frame = evtGetFloat(event, *event->args);
    NpcEntry* npc = npcNameToPtr("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223");

    if (animPoseGetAnimPosePtr(npc->poseId)->localFrame < frame) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
