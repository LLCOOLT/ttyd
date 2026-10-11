// include: driver/hitdrv.h
// decl: static BOOL _hitIsGroupSub(HitEntry* target, HitEntry* node, BOOL checkSibling);
// proto: BOOL hitIsGroup(HitEntry* target, HitEntry* group);
BOOL hitIsGroup(HitEntry* target, HitEntry* group) {
    // whether target is group or one of its descendants
    return _hitIsGroupSub(target, group, FALSE);
}
