// include: manager/evtmgr_cmd.h
// decl: void winLectureOn(void);
// decl: BOOL winLectureCheck(void);
// proto: USER_FUNC(lecture);
USER_FUNC(lecture) {
    if (isFirstCall) {
        winLectureOn();
    }
    if (winLectureCheck()) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
