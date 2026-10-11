// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// proto: USER_FUNC(koburon_get_encount_info);
USER_FUNC(koburon_get_encount_info) {
    s32 arg = event->args[0];
    FieldBattleData* fbat = fbatGetPointer();

    evtSetValue(event, arg, *(s32*)&fbat->field_C[4]);
    return EVT_RETURN_DONE;
}
