// include: driver/imgdrv.h
// include: driver/animdrv.h
// include: mario/mariost.h
// proto: USER_FUNC(img_set_color);
USER_FUNC(img_set_color) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    u8 r = evtGetValue(event, args[1]);
    u8 g = evtGetValue(event, args[2]);
    u8 b = evtGetValue(event, args[3]);
    u8 a = evtGetValue(event, args[4]);
    ImageEntry* img = imgNameToPtr(name, gp->inBattle != 0);

    animPoseSetMaterialFlagOn(img->poseId, 0x40);
    animPoseSetMaterialEvtColor(img->poseId, (GXColor){r, g, b, a});
    return EVT_RETURN_DONE;
}
