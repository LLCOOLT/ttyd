// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// proto: USER_FUNC(koburon_get_encount_info);
USER_FUNC(koburon_get_encount_info) {
    s32* args = event->args;

    evtSetValue(event, args[0], *(s32*)&fbatGetPointer()->field_C[4]);
    return EVT_RETURN_DONE;
}
