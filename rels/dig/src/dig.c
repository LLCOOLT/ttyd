// dig.rel (ダイジェスト, digest movie): registers dig_00 and starts the THP movie player on load, stops it on unload.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "data/mapdata.h"
#include "dig.h"
#include "rel_module.h"

void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("dig_00", dig_00_init_evt);
    dig_thpInit();
}

void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
    dig_thpStop();
}
void _unresolved(void) {
}
