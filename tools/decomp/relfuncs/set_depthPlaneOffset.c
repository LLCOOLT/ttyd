// include: manager/evtmgr_cmd.h
// include: driver/imgdrv.h
// include: mario/mariost.h
// proto: USER_FUNC(set_depthPlaneOffset);
USER_FUNC(set_depthPlaneOffset) {
    s32* args = event->args;
    ImageEntry* img = imgNameToPtr((const char*)evtGetValue(event, args[0]), gp->inBattle != 0);

    img->field_0x11C = evtGetFloat(event, args[1]);
    return EVT_RETURN_DONE;
}
