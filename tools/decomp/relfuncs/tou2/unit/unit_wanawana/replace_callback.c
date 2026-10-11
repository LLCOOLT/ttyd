// include: battle/battle_unit.h
// include: driver/animdrv.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// decl: typedef struct WanaWork { s32 ready; s32 poseId; Mtx mtx; GXTexObj obj; BattleUnitPart* part; smartEntry* tex; } WanaWork;
// proto: void replace_callback(BattleUnitPart* part, s32 type);
void replace_callback(BattleUnitPart* part, s32 type) {
    WanaWork* wp = *(WanaWork**)((u8*)part->mOwner + 0x310);

    if (wp->ready) {
        Mtx mtx;

        PSMTXIdentity(mtx);
        if (type == 0) {
            animSetPaperTexMtx(mtx, NULL, NULL);
            animSetPaperTexObj(&wp->obj, NULL, NULL, wp->tex, NULL, NULL, 1, 1);
        } else {
            animSetPaperTexMtx(NULL, NULL, NULL);
            animSetPaperTexObj(NULL, NULL, NULL, NULL, NULL, NULL, 1, 1);
        }
    }
}
