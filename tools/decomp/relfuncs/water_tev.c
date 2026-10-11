// include: driver/mapdrv.h
// include: driver/envdrv.h
// proto: void water_tev(MapTevCallbackInfo* info);
void water_tev(MapTevCallbackInfo* info) {
    envSetWater(info);
}
