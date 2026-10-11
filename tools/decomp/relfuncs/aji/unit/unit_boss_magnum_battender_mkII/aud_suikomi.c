// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_audience.h
// decl: s32 irand(s32 scalar);
// decl: f32 intplGetValue(f32 start, f32 end, s32 mode, s32 cur, s32 steps);
// decl: s32 psndSFXOn(const char* name);
// decl: EffectEntry* effKumokumoN64Entry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 rot, f32 scale1, f32 scale2);
// decl: typedef struct AudMember { s32 flags; s32 field_0x4; s32 field_0x8; u8 field_0xC[0x48 - 0xC]; Vec position; u8 field_0x54[0x60 - 0x54]; Vec scale; u8 field_0x6C[0x9C - 0x6C]; Vec rotation; u8 field_0xA8[0xB4 - 0xA8]; Vec home; u8 field_0xC0[0xF8 - 0xC0]; s32 frame; s32 frames; } AudMember;
// decl: static s32* list;
// decl: s32 screamId;
// decl: EffectEntry* eff_suikomi;
// proto: USER_FUNC(aud_suikomi);
USER_FUNC(aud_suikomi) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    s32 done = 0;
    AudMember* mem;
    s32 i;
    s32 j;
    f32 x;
    f32 y;
    f32 z;
    f32 x2;
    f32 y2;
    f32 z2;
    s32 ids[200];

    if (isFirstCall) {
        s32 n = 0;

        if (list != NULL) {
            BattleFree(list);
        }
        list = BattleAlloc(sizeof(s32) * 20);
        for (i = 0; i < 200; i++) {
            if ((u8)BattleAudience_GetExist(i) == TRUE) {
                ids[n] = i;
                n++;
            }
        }
        for (i = 0; i < 1000; i++) {
            s32 a = irand(n);
            s32 b = irand(n);
            s32 tmp = ids[a];

            ids[a] = ids[b];
            ids[b] = tmp;
        }
        for (i = 0; i < 20; i++) {
            mem = (AudMember*)BattleAudienceGetPtr(ids[i]);
            mem->flags |= 0x10;
            BattleAudience_SetAnim(ids[i], 9, FALSE);
            mem->frames = i * 3 + 60;
            mem->field_0x8 = 0;
            mem->rotation.y = 0.0f;
            list[i] = ids[i];
        }
        BtlUnit_GetPos(BattleGetUnitPtr(_battleWorkPointer, id), &x, &y, &z);
        eff_suikomi = effKumokumoN64Entry(2, 120, x - 10.0f, 10.0f + y, z, -40.0f, 1.0f, 1.5f);
        screamId = psndSFXOn("SFX_AUDIENCE_PANIC_SCREAM1");
    }
    BtlUnit_GetPos(BattleGetUnitPtr(_battleWorkPointer, id), &x2, &y2, &z2);
    y2 += 5.0f;
    for (i = 0; i < 200; i++) {
        for (j = 0; j < 20; j++) {
            if (i == list[j]) {
                mem = (AudMember*)BattleAudienceGetPtr(i);
                mem->rotation.y += 19.0f;
                if (mem->frame < mem->frames) {
                    mem->frame++;
                } else {
                    done++;
                    mem->flags &= ~4;
                    mem->flags |= 2;
                }
                mem->position.x = intplGetValue(mem->home.x, x2, 4, mem->frame, mem->frames);
                mem->position.y = intplGetValue(mem->home.y, y2, 2, mem->frame, mem->frames);
                mem->position.z = intplGetValue(mem->home.z, z2, 4, mem->frame, mem->frames);
                mem->scale.x = mem->scale.y = intplGetValue(1.0f, 0.65f, 4, mem->frame, mem->frames);
                break;
            }
        }
    }
    return done < 20 ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}
