// include: manager/evtmgr_cmd.h
// include: memory.h
// proto: USER_FUNC(irai_end_func);
USER_FUNC(irai_end_func) {
    _mapFree((void*)event->lwData[10]);
    return EVT_RETURN_DONE;
}
