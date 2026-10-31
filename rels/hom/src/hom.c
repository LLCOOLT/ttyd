// hom.rel (途中駅ホーム, Excess Express platform): registers hom_00 and the train scenes hom_10..hom_12.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "data/mapdata.h"
#include "hom.h"
#include "rel_module.h"

void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("hom_00", hom_00_init_evt);
    relSetEvtAddr("hom_10", hom_10_init_evt);
    relSetEvtAddr("hom_11", hom_11_init_evt);
    relSetEvtAddr("hom_12", hom_12_init_evt);
}

void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
void _unresolved(void) {
}
