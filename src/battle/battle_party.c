// Battle party setup: the table that places each partner (Goombella, Koops, Flurrie, ...) into a battle.
#include "battle/battle_party.h"
#include "battle/battle_unit.h"
#include "unit/party/unit_party_nokotarou.h"
#include "unit/party/unit_party_yoshi.h"
#include "unit/party/unit_party_clauda.h"
#include "unit/party/unit_party_vivian.h"
#include "unit/party/unit_party_sanders.h"
#include "unit/party/unit_party_chuchurina.h"
#include "unit/party/unit_party_christine.h"

#define PARTY_SETUP(kind) {&kind, 0, {0}, BATTLE_PHASE_PLAYER, {1000.0f, 0.0f, 1000.0f}, 0, {0, 0, 0, 0}, NULL}

/**
 * Battle entries for the seven partners in unit-kind order 0xE0-0xE6 (Goombella, Koops, Yoshi, Flurrie, Vivian,
 * Bobbery, Ms. Mowz). Btl_UnitSetup enters the partner the field party has; BattleChangeParty and
 * BattlePartyAnimeLoad use it when the player switches partners.
 */
BattleUnitSetup entryunit_party[7] = {
    PARTY_SETUP(unitdata_Party_Christine),
    PARTY_SETUP(unitdata_Party_Nokotarou),
    PARTY_SETUP(unitdata_Party_Yoshi),
    PARTY_SETUP(unitdata_Party_Clauda),
    PARTY_SETUP(unitdata_Party_Vivian),
    PARTY_SETUP(unitdata_Party_Sanders),
    PARTY_SETUP(unitdata_Party_Chuchurina),
};
