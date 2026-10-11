// include: driver/hitdrv.h
// decl: static BOOL _hitIsGroupSub(HitEntry* target, HitEntry* node, BOOL checkSibling);
// proto: BOOL hitIsGroup(HitEntry* target, HitEntry* group);
BOOL hitIsGroup(HitEntry* target, HitEntry* group) {
    if (target != NULL) {
        return _hitIsGroupSub(target, group, FALSE);
    }
    return FALSE;
}
