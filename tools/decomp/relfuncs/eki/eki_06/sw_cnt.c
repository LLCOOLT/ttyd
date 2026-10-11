// include: manager/evtmgr_cmd.h
// include: driver/mobjdrv.h
// include: string.h
// proto: s32 sw_cnt(MapObjectEntry* mobj);
s32 sw_cnt(MapObjectEntry* mobj) {
    if (strcmp(mobj->name, "MOBJ_eki_06_su1") == 0) {
        return evtGetValue(NULL, GW(0));
    }
    if (strcmp(mobj->name, "MOBJ_eki_06_su2") == 0) {
        return evtGetValue(NULL, GW(1));
    }
    if (!strcmp(mobj->name, "MOBJ_eki_06_su3")) {
        return evtGetValue(NULL, GW(2));
    }
    return 0;
}
