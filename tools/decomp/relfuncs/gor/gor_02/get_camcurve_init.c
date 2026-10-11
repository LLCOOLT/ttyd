// include: manager/evtmgr_cmd.h
// include: memory.h
// decl: char* camstring;
// proto: USER_FUNC(get_camcurve_init);
USER_FUNC(get_camcurve_init) {
    camstring = _mapAlloc(0x100);
    camstring[0] = '\0';
    return EVT_RETURN_DONE;
}
