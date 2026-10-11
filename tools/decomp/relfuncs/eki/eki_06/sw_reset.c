// include: manager/evtmgr_cmd.h
// include: driver/mobjdrv.h
// include: driver/animdrv.h
// proto: void sw_reset(void);
void sw_reset(void) {
    MapObjectEntry* mobj;

    mobj = mobjNameToPtr("MOBJ_eki_06_su1");
    mobj->flags &= ~2;
    switch (sw_cnt(mobj)) {
        case 2:
            animPoseSetAnim(mobj->poseId, "ANIM_5", 1);
            evtSetValue(NULL, GW(0), 0);
            break;
    }

    mobj = mobjNameToPtr("MOBJ_eki_06_su2");
    mobj->flags &= ~2;
    switch (sw_cnt(mobj)) {
        case 11:
            animPoseSetAnim(mobj->poseId, "ANIM_7", 1);
            evtSetValue(NULL, GW(1), 0);
            break;
    }

    mobj = mobjNameToPtr("MOBJ_eki_06_su3");
    mobj->flags &= ~2;
    switch (sw_cnt(mobj)) {
        case 4:
            animPoseSetAnim(mobj->poseId, "ANIM_7", 1);
            evtSetValue(NULL, GW(2), 0);
            break;
    }
}
