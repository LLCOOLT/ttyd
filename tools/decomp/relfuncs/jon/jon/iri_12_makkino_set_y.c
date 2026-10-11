// include: driver/npcdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(iri_12_makkino_set_y);
USER_FUNC(iri_12_makkino_set_y) {
    f32 y = evtGetFloat(event, event->args[0]);

    npcNameToPtr("\203}\203b\203L\203m")->position.y = y;
    return EVT_RETURN_DONE;
}
