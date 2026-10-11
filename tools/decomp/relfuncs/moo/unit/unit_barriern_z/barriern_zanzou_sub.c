// include: battle/battle.h
// include: battle/battle_unit.h
// decl: f32 intplGetValue(f32 start, f32 end, s32 mode, s32 cur, s32 steps);
// decl: static s32 zanzou_count[5];
// proto: static s32 barriern_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 type);
static inline f32 intpl_ff(f32 start, f32 end, s32 mode, s32 cur, s32 total) {
    return intplGetValue(start, end, mode, cur, total);
}

static s32 barriern_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 type) {
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
            scale = 0.75f;
            frames = 36;
            for (i = 0; i < 5; i++) {
                start[i] = scales[i];
                end[i] = scale;
            }
            ofs = 0.5f;
            alphaStart = 0;
            alphaEnd = 64;
            mode = 4;
            break;
        case 1:
        case 2:
            scale = 1.0f;
            frames = 8;
            for (i = 0; i < 5; i++) {
                start[i] = scale;
                end[i] = scales[i];
            }
            ofs = -0.5f;
            alphaStart = 64;
            alphaEnd = 0;
            mode = 1;
            break;
    }
    if (type == 2) {
        frames = 36;
    }
    if (isFirstCall) {
        zanzou_count[0] = 0;
        BtlUnit_GetPos(unit, &x, &y, &z);
        BtlUnit_SetPartsScale(BtlUnit_GetPartsPtr(unit, 1), 1.0f, 1.0f, 1.0f);
        for (i = 2, j = 0; i <= 6; i++, j++) {
            part = BtlUnit_GetPartsPtr(unit, i);
            BtlUnit_SetPartsPos(part, x, y, i * ofs + z);
            BtlUnit_SetPartsScale(part, start[j], start[j], 1.0f);
            part->color.a = alphaEnd;
            part->attributes &= ~0x1000000;
        }
    }
    part = BtlUnit_GetPartsPtr(unit, 1);
    {
        f32 s = intplGetValue(1.0f, scale, mode, zanzou_count[0], frames);
        BtlUnit_SetPartsScale(part, s, s, 1.0f);
    }
    for (i = 2, j = 0; i <= 6; i++, j++) {
        f32 s;

        part = BtlUnit_GetPartsPtr(unit, i);
        s = intpl_ff(start[j], end[j], mode, zanzou_count[0], frames);
        BtlUnit_SetPartsScale(part, s, s, 1.0f);
        part->color.a = intplGetValue(alphaStart, alphaEnd, 0, zanzou_count[0], frames);
    }
    if (zanzou_count[0] >= frames) {
        part = BtlUnit_GetPartsPtr(unit, 1);
        BtlUnit_SetPartsScale(part, 1.0f, 1.0f, 1.0f);
        part->color.a = 255;
        for (i = 2; i <= 6; i++) {
            BtlUnit_GetPartsPtr(unit, i)->attributes |= 0x1000000;
        }
        return EVT_RETURN_DONE;
    }
    zanzou_count[0]++;
    return EVT_RETURN_BLOCK;
}
