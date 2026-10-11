// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_audience.h
// include: system.h
// decl: typedef struct CortezWork { s16 state; s16 count; s16 audienceId[100]; s16 wait[100]; s16 timer[100]; s16 seq[100]; void* eff[100]; Vec srcPos[100]; Vec dstPos[100]; } CortezWork;
// decl: void* effSpiritEntry(s32 type, s32 time, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, f32 scale);
// decl: void* effKumokumoN64Entry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 a, f32 b, f32 c);
// proto: USER_FUNC(_cortez_collect_energy);
USER_FUNC(_cortez_collect_energy) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit;
    CortezWork* work;
    BattleAudienceMember* member;
    BOOL done;
    s32 aid;
    s32 i;
    BOOL kumo;
    f32 x, y, z;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    work = (CortezWork*)unit->countersetWeapon;
    if (isFirstCall) {
        work->state = 0;
    }
    switch (work->state) {
        case 0:
            kumo = FALSE;
            for (i = 0; i < 100; i++) {
                aid = work->audienceId[i];
                if (aid != -1) {
                    member = BattleAudienceGetPtr(aid);
                    member->flags |= 0x12;
                    BattleAudience_SetAnim(aid, 9, TRUE);
                    work->wait[i] = irand(60) + 30;
                    work->srcPos[i] = member->position;
                    BtlUnit_GetPos(unit, &work->dstPos[i].x, &work->dstPos[i].y, &work->dstPos[i].z);
                    work->dstPos[i].y += 20.0f;
                    effSpiritEntry(0, work->wait[i] + 60, work->srcPos[i].x, work->srcPos[i].y, work->srcPos[i].z,
                                   work->dstPos[i].x, work->dstPos[i].y, work->dstPos[i].z, 2.0f);
                    if (!kumo) {
                        kumo = TRUE;
                        effKumokumoN64Entry(1, 60, work->dstPos[i].x, work->dstPos[i].y, work->dstPos[i].z, 180.0f,
                                            -1.0f, 1.0f);
                    }
                }
            }
            work->state++;
        case 1:
            done = TRUE;
            for (i = 0; i < 100; i++) {
                aid = work->audienceId[i];
                if (aid != -1) {
                    switch (work->seq[i]) {
                        case 0:
                            if (work->wait[i] > 0) {
                                work->wait[i]--;
                                done = FALSE;
                                break;
                            }
                            work->seq[i]++;
                            work->timer[i] = 0;
                        case 1:
                            work->timer[i]++;
                            BattleAudience_GetRotate(aid, &x, &y, &z);
                            x = intplGetValue(0, work->timer[i], 30, 0.0f, -90.0f);
                            BattleAudience_SetRotate(aid, x, y, z);
                            if (work->timer[i] >= 30) {
                                work->seq[i]++;
                            } else {
                                done = FALSE;
                                break;
                            }
                        case 2:
                            work->timer[i] = 0;
                            work->seq[i]++;
                        case 3:
                            work->timer[i]++;
                            if (work->timer[i] >= 60) {
                                work->seq[i]++;
                            }
                            done = FALSE;
                            break;
                        case 4:
                            break;
                    }
                }
            }
            if (!done) {
                break;
            }
        default:
            return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
