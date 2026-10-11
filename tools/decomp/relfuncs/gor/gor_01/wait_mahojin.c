// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// include: driver/animdrv.h
// proto: USER_FUNC(wait_mahojin);
USER_FUNC(wait_mahojin) {
    s32 anim = ((s32*)effNameToPtr("mahojin")->userdata)[6];

    if (anim != -1 && 0.0f != animPoseGetLoopTimes(anim)) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
