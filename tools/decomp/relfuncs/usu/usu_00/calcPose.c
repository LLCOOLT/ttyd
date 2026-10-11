// include: mario/mariost.h
// proto: s32 calcPose(s32 i, s32 lo, s32 hi, s32 flag);
s32 calcPose(s32 i, s32 lo, s32 hi, s32 flag) {
    s32 range = hi - lo + 1;
    s32 n = flag ? 6 : 7;

    return lo + ((gp->retraceCount + i * i) % (range * n)) / n;
}
