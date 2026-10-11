// include: driver/mapdrv.h
// proto: static void lect_map_cam_chg_sub(MapObject* obj, s32 camId, BOOL siblings);
static void lect_map_cam_chg_sub(MapObject* obj, s32 camId, BOOL siblings) {
    obj->field_0x4[1] = camId;
    if (obj->child != NULL) {
        lect_map_cam_chg_sub(obj->child, camId, TRUE);
    }
    if (siblings && obj->next != NULL) {
        lect_map_cam_chg_sub(obj->next, camId, TRUE);
    }
}
