// include: manager/evtmgr_cmd.h
// decl: void door_position_sub(s32 type, const char* mapObj, const char* hitA, const char* hitB, Vec* outPos, Vec* inPos, s32 flag);
// proto: USER_FUNC(evt_gor_door_out_info);
USER_FUNC(evt_gor_door_out_info) {
    s32* args = event->args;
    Vec outPos = {0.0f, 0.0f, 0.0f};
    Vec inPos = {0.0f, 0.0f, 0.0f};

    door_position_sub(3, "S_ie_03_doao", "A_ie_03_doa_02", "A_ie_03_doa_04", &outPos, &inPos, 0);
    evtSetValue(event, args[0], inPos.x);
    evtSetValue(event, args[1], inPos.y);
    evtSetValue(event, args[2], inPos.z);
    return EVT_RETURN_DONE;
}
