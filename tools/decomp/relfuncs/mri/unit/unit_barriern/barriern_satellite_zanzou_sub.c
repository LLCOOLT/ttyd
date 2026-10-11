// include: battle/battle.h
// include: battle/battle_unit.h
// decl: f32 intplGetValue(f32 start, f32 end, s32 mode, s32 cur, s32 steps);
// decl: static s32 zanzou_count[3];
// decl: void BtlUnit_SetAnim(BattleUnitPart* part, const char* anim);
// proto: static s32 barriern_satellite_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 n, s32 type);
static s32 barriern_satellite_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 n, s32 type) {
    f32 start[5];
    f32 end[5];
    f32 x;
    f32 y;
    f32 z;
    BattleUnitPart* part;
    s32 frames;
    f32 scale;
    f32 ofs;
    u8 alphaStart;
    u8 alphaEnd;
    s32 mode = 4;
    s32 i;
    s32 j;

    switch (type) {
        case 0:
            scale = 0.6f;
            frames = 36;
            for (i = 0; i < 5; i++) {
                start[i] = 0.8f * scales[i];
                end[i] = scale;
            }
            ofs = 0.5f;
            alphaStart = 0;
            alphaEnd = 64;
            mode = 4;
            break;
        case 1:
            scale = 0.8f;
            frames = 8;
            for (i = 0; i < 5; i++) {
                start[i] = scale;
                end[i] = scale * scales[i];
            }
            ofs = -0.5f;
            alphaStart = 64;
            alphaEnd = 0;
            mode = 1;
            break;
    }
    if (isFirstCall) {
        zanzou_count[(s32)(n + 1)] = 0;
        BtlUnit_GetPos(unit, &x, &y, &z);
        BtlUnit_SetPartsScale(BtlUnit_GetPartsPtr(unit, 1), 0.8f, 0.8f, 1.0f);
        for (i = 2, j = 0; i <= 6; i++, j++) {
            part = BtlUnit_GetPartsPtr(unit, i);
            BtlUnit_SetPartsPos(part, x, y, i * ofs + z);
            BtlUnit_SetPartsScale(part, start[j], start[j], 1.0f);
            BtlUnit_SetPartsRotate(part, 0.0f, 0.0f, 0.0f);
            part->color.a = alphaStart;
            BtlUnit_SetAnim(part, "Z_2");
            part->attributes &= ~0x1000000;
        }
    }
    part = BtlUnit_GetPartsPtr(unit, 1);
    {
        f32 s = intplGetValue(0.8f, scale, 4, zanzou_count[0], frames);
        BtlUnit_SetPartsScale(part, s, s, 1.0f);
    }
    for (i = 2, j = 0; i <= 6; i++, j++) {
        f32 s;

        part = BtlUnit_GetPartsPtr(unit, i);
        s = intplGetValue(start[j], end[j], mode, zanzou_count[(s32)(n + 1)], frames);
        BtlUnit_SetPartsScale(part, s, s, 1.0f);
        part->color.a = intplGetValue(alphaStart, alphaEnd, 0, zanzou_count[(s32)(n + 1)], frames);
    }
    if (zanzou_count[(s32)(n + 1)] >= frames) {
        part = BtlUnit_GetPartsPtr(unit, 1);
        BtlUnit_SetPartsScale(part, 0.8f, 0.8f, 1.0f);
        part->color.a = 255;
        for (i = 2; i <= 6; i++) {
            BtlUnit_GetPartsPtr(unit, i)->attributes |= 0x1000000;
        }
        return EVT_RETURN_DONE;
    }
    zanzou_count[(s32)(n + 1)]++;
    return EVT_RETURN_BLOCK;
}
