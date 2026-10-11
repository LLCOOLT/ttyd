// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_audience.h
// include: evt/evt_cmd.h
// include: eff/eff_kemu_test.h
// decl: typedef struct AudMember { s32 flags; s32 field_0x4; s32 field_0x8; u8 field_0xC[0x48 - 0xC]; Vec position; u8 field_0x54[0x60 - 0x54]; Vec scale; u8 field_0x6C[0x9C - 0x6C]; Vec rotation; u8 field_0xA8[0xB4 - 0xA8]; Vec home; u8 field_0xC0[0xF8 - 0xC0]; s32 frame; s32 frames; } AudMember;
// decl: s32 irand(s32 scalar);
// decl: int rand(void);
// decl: static s32* list;
// decl: extern s32 aud_hit_event[];
// decl: void aud_get_pod_pos(BattleUnit* unit, f32* x, f32* y, f32* z);
// decl: void aud_fire_eff(f32 x, f32 y, f32 z);
// proto: USER_FUNC(aud_fire_hit);
USER_FUNC(aud_fire_hit) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    s32 target = BattleTransID(event, evtGetValue(event, args[1]));
    s32 start = evtGetValue(event, args[2]);
    BattleUnit* unit;
    BattleUnitPart* part;
    AudMember* mem;
    EventEntry* evt;
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    f32 hx;
    f32 hy;
    f32 hz;

    if (isFirstCall) {
        aud_get_pod_pos(BattleGetUnitPtr(_battleWorkPointer, id), &x, &y, &z);
        aud_fire_eff(x, y, z);
        unit = BattleGetUnitPtr(_battleWorkPointer, target);
        part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
        BtlUnit_GetHitPos(unit, part, &hx, &hy, &hz);
        for (i = start; i < start + 2; i++) {
            mem = (AudMember*)BattleAudienceGetPtr(list[i]);
            BattleAudience_SetAnim(list[i], 9, FALSE);
            mem->position = (Vec){x, y, z};
            mem->frames = 0;
            mem->field_0x8 = 0;
            mem->rotation.y = 0.0f;
            mem->scale.x = mem->scale.y = 1.0f;
            mem->flags |= 4;
            evt = evtEntry(aud_hit_event, 0, 0x20);
            evt->lwData[0] = list[i];
            evt->lwData[1] = (s32)(1024.0f * hx) - EVTDAT_FLOAT_BASE;
            evt->lwData[2] = (s32)(1024.0f * hy) - EVTDAT_FLOAT_BASE;
            evt->lwData[3] = (s32)(1024.0f * hz) - EVTDAT_FLOAT_BASE;
            evt->lwData[4] = 0;
            evt->lwData[5] = irand(3) + 10;
            evt->lwData[6] = (s32)(1024.0f * (hx + 200.0f * rand() / 32767.0f - 100.0f)) - EVTDAT_FLOAT_BASE;
            evt->lwData[7] = FLOAT(-100.0f);
            evt->lwData[8] = (s32)(1024.0f * (hz + 100.0f * rand() / 32767.0f - 50.0f)) - EVTDAT_FLOAT_BASE;
            evt->lwData[9] = irand(30) + 30;
            evt->lwData[10] = FLOAT(-0.3f);
        }
    }
    return EVT_RETURN_DONE;
}
