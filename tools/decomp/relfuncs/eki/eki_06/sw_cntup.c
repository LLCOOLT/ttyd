// include: manager/evtmgr_cmd.h
// include: driver/mobjdrv.h
// include: string.h
// proto: void sw_cntup(MapObjectEntry* mobj);
void sw_cntup(MapObjectEntry* mobj) {
    if (strcmp(mobj->name, "MOBJ_eki_06_su1") == 0) {
        evtSetValue(NULL, GW(0), evtGetValue(NULL, GW(0)) + 1);
    } else if (strcmp(mobj->name, "MOBJ_eki_06_su2") == 0) {
        evtSetValue(NULL, GW(1), evtGetValue(NULL, GW(1)) + 1);
    } else if (strcmp(mobj->name, "MOBJ_eki_06_su3") == 0) {
        evtSetValue(NULL, GW(2), evtGetValue(NULL, GW(2)) + 1);
    }
}
