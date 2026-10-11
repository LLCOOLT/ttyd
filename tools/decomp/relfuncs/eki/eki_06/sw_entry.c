// include: manager/evtmgr_cmd.h
// include: driver/mobjdrv.h
// include: driver/animdrv.h
// include: mario/mariost.h
// decl: static s32 lock;
// proto: USER_FUNC(sw_entry);
USER_FUNC(sw_entry) {
    s32* args = event->args;
    const char* name;
    f32 x, y, z;
    MapObjectEntry* mobj;
    Vec pos;

    name = (const char*)evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    if (!animGroupBaseAsync(name, gp->inBattle != 0, NULL)) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, name);
    mobj = mobjNameToPtr(name);
    mobj->flags |= 6;
    pos = (Vec){0.0f, 0.0f, 0.0f};
    pos.x = x;
    pos.y = y;
    pos.z = z;
    mobj->position = pos;
    mobj->mainFunc = sw_main;
    mobj->flags |= 0xA10000;
    mobj->unk1DC = 0;
    mobjCalcMtx(mobj);
    animPoseSetAnim(mobj->poseId, "ANIM_1", 1);
    lock = 0;
    return EVT_RETURN_DONE;
}
