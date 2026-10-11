// include: driver/npcdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(kpa_hikousen_yure);
USER_FUNC(kpa_hikousen_yure) {
    f32 y = evtGetFloat(event, event->args[0]);

    // 飛クッパ
    npcNameToPtr("\x94\xF2\x83\x4E\x83\x62\x83\x70")->moveOffset.y = y;
    return EVT_RETURN_DONE;
}
