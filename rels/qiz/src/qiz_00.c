// qiz_00 (はてなむしクイズ, question-bug quiz): an empty map left in JP and PAL; its init event only returns.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "qiz.h"

/** Map init script of qiz_00: does nothing and returns at once; the quiz map was left without content. */
EVT_BEGIN(qiz_00_init_evt)
    RETURN
EVT_END()
