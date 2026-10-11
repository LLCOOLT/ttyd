// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(evt_dou_normal_puka);
USER_FUNC(evt_dou_normal_puka) {
    evtSetFloat(event, event->args[0], ((f32*)dou_normal_puka_data)[event->lwData[0] & 0xF]);
    return EVT_RETURN_DONE;
}
