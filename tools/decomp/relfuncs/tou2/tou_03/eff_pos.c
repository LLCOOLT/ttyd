// include: driver/itemdrv.h
// include: driver/effdrv.h
// decl: typedef struct StoneEffWork { s32 field_0x0; Vec pos; } StoneEffWork;
// proto: USER_FUNC(eff_pos);
USER_FUNC(eff_pos) {
    ItemEntry* item = itemNameToPtr("stone");
    EffectEntry* eff1 = effNameToPtr("eff_1");
    EffectEntry* eff2 = effNameToPtr("eff_2");

    if (item) {
        if (eff1) {
            ((StoneEffWork*)eff1->userdata)->pos.x = item->position.x;
            ((StoneEffWork*)eff1->userdata)->pos.y = 15.0f + item->position.y;
            ((StoneEffWork*)eff1->userdata)->pos.z = item->position.z;
        }
        if (eff2) {
            ((StoneEffWork*)eff2->userdata)->pos.x = item->position.x;
            ((StoneEffWork*)eff2->userdata)->pos.y = 15.0f + item->position.y;
            ((StoneEffWork*)eff2->userdata)->pos.z = item->position.z;
        }
    }
    return EVT_RETURN_BLOCK;
}
