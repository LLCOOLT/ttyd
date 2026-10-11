// include: mario/mario.h
// include: driver/npcdrv.h
// include: evt/evt_npc.h
// decl: void npcTuningRy(NpcEntry* npc, f32 ry);
// include: system.h
// include: pmario_sound.h
// include: party/party_vivian.h
// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// decl: extern u8 kurokaron_move_index;
// decl: extern u8 kurokaron_move_flag;
// decl: extern u8 kurokaron_same_goal;
// decl: extern u8 kurokaron_prev_goal;
// decl: extern s32 kurokaron_vivian_prev_sts;
// decl: extern u8 kurokaron_stop_cnt;
// decl: extern u16 kurokaron_run_cnt;
// decl: extern int __float_nan[];
// decl: double sin(double x);
// decl: double cos(double x);
// decl: s32 psndSFXOn_3D(const char* name, Vec* position);
// decl: static inline s32 k_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
// decl: static inline f32 k_sqrtf(f32 x) { const f64 _half = .5; const f64 _three = 3.0; if (x > 0.0f) { f64 guess = __frsqrte(x); guess = _half * guess * (_three - guess * guess * x); guess = _half * guess * (_three - guess * guess * x); guess = _half * guess * (_three - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (k_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }
// decl: s32 _kurokaron_run_away(f32 x, f32 z, f32 tx, f32 tz);
// decl: s32 kurokaron_move2(NpcEntry* npc, MarioWork* mario);
// decl: void _kurokaron_next_move_index(void);
// proto: USER_FUNC(kurokaron_move_position);
USER_FUNC(kurokaron_move_position) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    f32 speed = evtGetFloat(event, args[3]);
    NpcEntry* npc = evtNpcNameToPtr(event, name);
    MarioWork* mario;
    Vec diff;
    f32 dist;
    f32 step;
    f32 marioDist;

    npc->jumpFlags |= 0x10;
    if (isFirstCall) {
        npc->field_188 = 0;
        npc->field_108 = 0;
        npc->jumpTargetPos.x = x;
        npc->jumpTargetPos.y = npc->position.y;
        npc->jumpTargetPos.z = z;
        npc->jumpStartPos = npc->position;
        PSVECSubtract(&npc->jumpTargetPos, &npc->jumpStartPos, &diff);
        dist = k_sqrtf(diff.x * diff.x + diff.z * diff.z);
        npc->moveDir = angleABf(0.0f, 0.0f, diff.x, diff.z);
        npc->moveSpeed = speed;
        npc->moveOffset.y = 0.0f;
        if (npc->moveSpeed <= 0.1f && npc->moveTime == 0.0f) {
            npc->moveSpeed = 1.0f;
        }
        npc->footstepAccum = 0.0f;
        npc->footstepToggle = TRUE;
    }
    mario = marioGetPtr();
    PSVECSubtract(&npc->jumpTargetPos, &npc->position, &diff);
    dist = k_sqrtf(diff.x * diff.x + diff.z * diff.z);
    step = (20.0f * npc->moveSpeed) / 1000.0f;
    PSVECSubtract(&mario->position, &npc->position, &diff);
    marioDist = k_sqrtf(diff.x * diff.x + diff.z * diff.z);
    if (marioDist < 80.0f && kurokaron_vivian_prev_sts == 3 && vivianGetStatus() == 0) {
        kurokaron_stop_cnt = 60;
    }
    kurokaron_vivian_prev_sts = vivianGetStatus();
    if (kurokaron_stop_cnt != 0) {
        npc->jumpFlags &= ~0x10;
        kurokaron_stop_cnt--;
        return EVT_RETURN_BLOCK;
    }
    if (!(kurokaron_move_flag & 2) && vivianGetStatus() != 1 && vivianGetStatus() != 2 && vivianGetStatus() != 3 &&
        marioDist < 80.0f) {
        kurokaron_move_index = _kurokaron_run_away(npc->position.x, npc->position.z, mario->position.x, mario->position.z);
        kurokaron_run_cnt = 350;
        kurokaron_move_flag |= 2;
        return EVT_RETURN_DONE;
    }
    if (kurokaron_move2(npc, mario)) {
        return EVT_RETURN_DONE;
    }
    if (kurokaron_run_cnt != 0) {
        kurokaron_run_cnt--;
    }
    if (npc->field_2FC) {
        f32 angle = angleABf(mario->position.x, mario->position.z, npc->position.x, npc->position.z);

        if (kurokaron_move_flag & 4) {
            if (kurokaron_move_flag & 8) {
                kurokaron_move_flag &= ~8;
                npc->moveDir = reviseAngle(angle + 90.0f);
            } else {
                kurokaron_move_flag |= 8;
                npc->moveDir = reviseAngle(angle - 90.0f);
            }
        }
        kurokaron_run_cnt = 350;
        kurokaron_move_flag |= 2;
    }
    if (dist <= step && marioDist > 100.0f) {
        npc->moveSpeed = 0.0f;
        kurokaron_move_flag &= ~2;
        if (kurokaron_prev_goal == kurokaron_move_index) {
            if (++kurokaron_same_goal > 3) {
                kurokaron_move_flag |= 2;
            }
        } else {
            kurokaron_same_goal = 0;
        }
        kurokaron_prev_goal = kurokaron_move_index;
        _kurokaron_next_move_index();
        return EVT_RETURN_DONE;
    }
    if ((npc->jumpFlags & 2) && npc->moveSpeed > 0.1f) {
        npcTuningRy(npc, npc->moveDir);
    }
    if ((kurokaron_move_flag & 2) && kurokaron_run_cnt != 0) {
        speed = 1.8f * npc->moveSpeed;
    } else {
        speed = npc->moveSpeed;
    }
    {
        f32 temp = (f32)sin(npc->moveDir * 6.2831855f / 360.0f);
        npc->moveOffset.x += npc->moveDt * (speed * temp);
        temp = (f32)cos(npc->moveDir * 6.2831855f / 360.0f);
        npc->moveOffset.z += npc->moveDt * (speed * -temp);
    }
    if (npc->footstepAccum > (f32)npc->footstepStride / npc->moveSpeed) {
        if (npc->footstepToggle != 0) {
            if (npc->footstepSfxA != NULL) {
                psndSFXOn_3D(npc->footstepSfxA, &npc->position);
            }
        } else {
            if (npc->footstepSfxB != NULL) {
                psndSFXOn_3D(npc->footstepSfxB, &npc->position);
            }
        }
        npc->footstepAccum = 0.0f;
        npc->footstepToggle = (s8)(1 - npc->footstepToggle);
    }
    if (npc->footstepSfxB != NULL || npc->footstepToggle != 0) {
        npc->footstepAccum += 1000.0f * npc->moveDt;
    }
    return EVT_RETURN_BLOCK;
}
