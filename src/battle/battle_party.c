#include "battle/battle_party.h"
#include "battle/battle_unit.h"
#include "unit/party/unit_party_nokotarou.h"
#include "unit/party/unit_party_yoshi.h"
#include "unit/party/unit_party_clauda.h"
#include "unit/party/unit_party_vivian.h"
#include "unit/party/unit_party_sanders.h"
#include "unit/party/unit_party_chuchurina.h"

extern BattleUnitKind unitdata_Party_Christine;

// field_4 bytes: alliance 0, attack phase 0x04000002, position {1000.0f, 0.0f, 1000.0f}
#define PARTY_SETUP(kind) \
	{&kind, {0, 0, 0, 0, 0x04, 0x00, 0x00, 0x02, 0x44, 0x7A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x7A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0, 0, 0, 0}, NULL}

BattleUnitSetup entryunit_party[7] = {
	PARTY_SETUP(unitdata_Party_Christine),
	PARTY_SETUP(unitdata_Party_Nokotarou),
	PARTY_SETUP(unitdata_Party_Yoshi),
	PARTY_SETUP(unitdata_Party_Clauda),
	PARTY_SETUP(unitdata_Party_Vivian),
	PARTY_SETUP(unitdata_Party_Sanders),
	PARTY_SETUP(unitdata_Party_Chuchurina),
};
