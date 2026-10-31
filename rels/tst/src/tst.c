#include "evt/evt_cmd.h"

#include "data/mapdata.h"
#include "tst.h"

typedef void (*voidfunctionptr)(void);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];

void _prolog(void);
void _epilog(void);
void _unresolved(void);

void mobjKoopaOn(void);

USER_FUNC(tst_mobj_koopa_on) {
    mobjKoopaOn();
    return EVT_RETURN_DONE;
}

void _unresolved(void) {
}

void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}

void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("tst_bt00", tst_bt00_init_evt);
    relSetEvtAddr("tst_00", tst_00_init_evt);
    relSetEvtAddr("tst_01", tst_01_init_evt);
    relSetEvtAddr("tst_02", tst_02_init_evt);
    relSetEvtAddr("tst_moj_00", tst_moj_00_init_evt);
    relSetEvtAddr("tst_moj_01", tst_moj_01_init_evt);
    relSetEvtAddr("tst_moj_02", tst_moj_02_init_evt);
    relSetEvtAddr("tst_moj_03", tst_moj_03_init_evt);
    relSetEvtAddr("tst_off_01", tst_off_01_init_evt);
    relSetEvtAddr("tst_npc", tst_npc_init_evt);
    relSetEvtAddr("tst_nakayama", tst_nakayama_init_evt);
    relSetEvtAddr("tst_item_00", tst_item_00_init_evt);
    relSetEvtAddr("btl_tst_00", btl_tst_00_init_evt);
    relSetBtlAddr("tst", btlsetup_tst_tbl, btl_tst_setup_no_tbl);
}
