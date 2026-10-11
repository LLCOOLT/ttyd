// include: manager/evtmgr_cmd.h
// include: driver/mobjdrv.h
// include: driver/animdrv.h
// include: mario/mario_motion.h
// include: pmario_sound.h
// include: string.h
// decl: static s32 lock;
// decl: extern s32 evt_sw_complete[];
// proto: s32 sw_main(MapObjectEntry* mobj);
s32 sw_main(MapObjectEntry* mobj) {
    switch (mobj->unk1DC) {
        case 2:
            break;
        case 0:
            if (!(mobj->flags & 8)) {
                break;
            }
            if (lock != 0) {
                break;
            }
            lock = 1;
            if (mobj->unk1E0 == 0x200000) {
                marioChgMot(5);
            }
            psndSFXOn_3D("SFX_STG6_OBJ_SWITCH_ON1", &mobj->position);
            sw_cntup(mobj);
            if (strcmp(mobj->name, "MOBJ_eki_06_su1") == 0) {
                if (sw_cnt(mobj) == 1) {
                    animPoseSetAnim(mobj->poseId, "ANIM_2", 1);
                } else {
                    sw_reset();
                }
            }
            if (strcmp(mobj->name, "MOBJ_eki_06_su2") == 0) {
                if (sw_cnt(mobj) < 10) {
                    animPoseSetAnim(mobj->poseId, "ANIM_2", 1);
                } else if (sw_cnt(mobj) == 10) {
                    animPoseSetAnim(mobj->poseId, "ANIM_4", 1);
                } else {
                    sw_reset();
                }
            }
            if (strcmp(mobj->name, "MOBJ_eki_06_su3") == 0) {
                if (sw_cnt(mobj) < 3) {
                    animPoseSetAnim(mobj->poseId, "ANIM_2", 1);
                } else if (sw_cnt(mobj) == 3) {
                    animPoseSetAnim(mobj->poseId, "ANIM_4", 1);
                } else {
                    sw_reset();
                }
            }
            mobj->unk1DC++;
            break;
        case 1:
            if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
                break;
            }
            if (evtGetValue(NULL, GW(0)) == 1 && evtGetValue(NULL, GW(1)) == 10 && evtGetValue(NULL, GW(2)) == 3) {
                evtEntry(evt_sw_complete, 0, 0);
                mobj->unk1DC++;
                break;
            }
            mobjNameToPtr("MOBJ_eki_06_su1")->flags |= 2;
            mobjNameToPtr("MOBJ_eki_06_su2")->flags |= 2;
            mobjNameToPtr("MOBJ_eki_06_su3")->flags |= 2;
            if (strcmp(mobj->name, "MOBJ_eki_06_su1") == 0) {
                if (sw_cnt(mobj) == 1) {
                    animPoseSetAnim(mobj->poseId, "ANIM_3", 1);
                } else {
                    animPoseSetAnim(mobj->poseId, "ANIM_1", 1);
                }
            }
            if (strcmp(mobj->name, "MOBJ_eki_06_su2") == 0) {
                if (sw_cnt(mobj) == 10) {
                    animPoseSetAnim(mobj->poseId, "ANIM_5", 1);
                } else {
                    animPoseSetAnim(mobj->poseId, "ANIM_1", 1);
                }
            }
            if (strcmp(mobj->name, "MOBJ_eki_06_su3") == 0) {
                if (sw_cnt(mobj) == 3) {
                    animPoseSetAnim(mobj->poseId, "ANIM_5", 1);
                } else {
                    animPoseSetAnim(mobj->poseId, "ANIM_1", 1);
                }
            }
            mobj->flags &= ~8;
            mobj->unk1DC = 0;
            lock = 0;
            break;
    }
    return 0;
}
