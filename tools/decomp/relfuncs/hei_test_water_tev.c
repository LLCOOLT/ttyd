// include: driver/mapdrv.h
// include: driver/envdrv.h
// proto: void hei_test_water_tev(MapTevCallbackInfo* info);
void hei_test_water_tev(MapTevCallbackInfo* info) {
    envSetWater(info);
}
