// include: system.h
// decl: extern u8 kurokaron_move_index;
// decl: extern u8 kurokaron_move_flag;
// decl: extern f32 kurokaron_move_list[6][2];
// decl: int rand(void);
// proto: s32 _kurokaron_run_away(f32 x, f32 z, f32 tx, f32 tz);
s32 _kurokaron_run_away(f32 x, f32 z, f32 tx, f32 tz) {
    s32 cand[6];
    f32 base;
    f32 diff;
    f32 curDiff;
    f32 nextDiff;
    u8 cur;
    s32 cnt;
    s32 next;
    s32 i;
    s32 result;

    base = angleABf(x, z, tx, tz);
    cur = kurokaron_move_index;
    if (!(kurokaron_move_flag & 1)) {
        if (cur == 0) {
            next = 5;
        } else {
            next = cur - 1;
        }
    } else {
        next = (cur + 1) % 6;
    }
    cnt = 0;
    for (i = 0; i < 6; i++) {
        diff = __fabsf(compAngle(angleABf(x, z, kurokaron_move_list[i][0], kurokaron_move_list[i][1]), base));
        if (i == cur) {
            curDiff = diff;
        }
        if (i == next) {
            nextDiff = diff;
        }
        if (diff > 90.0f) {
            cand[cnt++] = i;
        }
    }
    if (cnt > 0) {
        result = cand[rand() % cnt];
        if (curDiff < 90.0f) {
            if (!(kurokaron_move_flag & 1)) {
                kurokaron_move_flag |= 1;
            } else {
                kurokaron_move_flag &= ~1;
            }
        }
    } else if (curDiff < nextDiff) {
        if (!(kurokaron_move_flag & 1)) {
            if (kurokaron_move_index == 0) {
                result = 5;
            } else {
                result = kurokaron_move_index - 1;
            }
            kurokaron_move_flag |= 1;
        } else {
            kurokaron_move_flag &= ~1;
            result = (kurokaron_move_index + 1) % 6;
        }
    }
    return result;
}
