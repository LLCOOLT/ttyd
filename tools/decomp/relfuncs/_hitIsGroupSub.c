// include: driver/hitdrv.h
// include: string.h
// proto: BOOL _hitIsGroupSub(HitEntry* target, HitEntry* node, BOOL checkSibling);
BOOL _hitIsGroupSub(HitEntry* target, HitEntry* node, BOOL checkSibling) {
    if (strcmp(target->joint->name, node->joint->name) == 0) {
        return TRUE;
    }
    if (node->child != NULL) {
        return _hitIsGroupSub(target, node->child, TRUE);
    }
    if (checkSibling && node->sibling != NULL) {
        return _hitIsGroupSub(target, node->sibling, TRUE);
    }
    return FALSE;
}
