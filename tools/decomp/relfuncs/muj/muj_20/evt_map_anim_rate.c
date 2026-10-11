// include: driver/mapdrv.h
// decl: void mapSetPlayRate(const char* name, f32 rate);
// decl: typedef struct MapAnimRate { f32 fune; f32 funeTarget; f32 nami; f32 namiTarget; } MapAnimRate;
// decl: MapAnimRate mapAnimRate;
// proto: USER_FUNC(evt_map_anim_rate);
USER_FUNC(evt_map_anim_rate) {
    MapAnimRate* rate = &mapAnimRate;
    f32 d;

    if (isFirstCall) {
        rate->fune = 1.0f;
        rate->nami = 1.0f;
        rate->funeTarget = 1.0f;
        rate->namiTarget = 1.0f;
    }
    d = rate->funeTarget - rate->fune;
    if (d >= 0.005f) {
        d = 0.005f;
    } else if (d <= -0.005f) {
        d = -0.005f;
    }
    rate->fune += d;
    d = rate->namiTarget - rate->nami;
    if (d >= 0.005f) {
        d = 0.005f;
    } else if (d <= -0.005f) {
        d = -0.005f;
    }
    rate->nami += d;
    mapSetPlayRate("fune", rate->fune);
    mapSetPlayRate("fune_01", rate->fune);
    mapSetPlayRate("nami", rate->nami);
    mapSetPlayRate("nami_02", rate->nami);
    return EVT_RETURN_BLOCK;
}
