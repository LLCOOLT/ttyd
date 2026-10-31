// Pit of 100 Trials (jon, "dungeon"): battle database: the enemy groups (BattleSetup) and stages of the Pit floors.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_weapon_power.h"
#include "battle/battle_database_common.h"
#include "jon.h"
#include "battle/battle_stage.h"
#include "battle/battle_stage_object.h"
#include "driver/npcdrv.h"

extern BattleUnitKind unit_hyper_jyugem;
extern BattleUnitKind unit_jyugem;

BattleStageObjectData jon_btlobject_data[8];
BattleStageData jon_btlstage_data[4];
BattleUnitSetup btlparty_jon_jon_100_01_off_1[1];
BattleGroupSetup btlgrp_jon_jon_100_01_off_1;
BattleUnitSetup btlparty_jon_jon_01_01_off_1[1];
BattleGroupSetup btlgrp_jon_jon_01_01_off_1;
BattleUnitSetup btlparty_jon_jon_01_01_off_2[2];
BattleGroupSetup btlgrp_jon_jon_01_01_off_2;
BattleUnitSetup btlparty_jon_jon_01_01_off_3[2];
BattleGroupSetup btlgrp_jon_jon_01_01_off_3;
BattleUnitSetup btlparty_jon_jon_01_02_off_1[5];
BattleGroupSetup btlgrp_jon_jon_01_02_off_1;
BattleUnitSetup btlparty_jon_jon_01_02_off_2[2];
BattleGroupSetup btlgrp_jon_jon_01_02_off_2;
BattleUnitSetup btlparty_jon_jon_01_02_off_3[5];
BattleGroupSetup btlgrp_jon_jon_01_02_off_3;
BattleUnitSetup btlparty_jon_jon_01_03_off_1[4];
BattleGroupSetup btlgrp_jon_jon_01_03_off_1;
BattleUnitSetup btlparty_jon_jon_01_03_off_2[2];
BattleGroupSetup btlgrp_jon_jon_01_03_off_2;
BattleUnitSetup btlparty_jon_jon_01_03_off_3[4];
BattleGroupSetup btlgrp_jon_jon_01_03_off_3;
BattleUnitSetup btlparty_jon_jon_01_04_off_1[4];
BattleGroupSetup btlgrp_jon_jon_01_04_off_1;
BattleUnitSetup btlparty_jon_jon_01_04_off_2[2];
BattleGroupSetup btlgrp_jon_jon_01_04_off_2;
BattleUnitSetup btlparty_jon_jon_01_04_off_3[3];
BattleGroupSetup btlgrp_jon_jon_01_04_off_3;
BattleUnitSetup btlparty_jon_jon_01_05_off_1[5];
BattleGroupSetup btlgrp_jon_jon_01_05_off_1;
BattleUnitSetup btlparty_jon_jon_01_05_off_2[3];
BattleGroupSetup btlgrp_jon_jon_01_05_off_2;
BattleUnitSetup btlparty_jon_jon_01_05_off_3[4];
BattleGroupSetup btlgrp_jon_jon_01_05_off_3;
BattleUnitSetup btlparty_jon_jon_11_01_off_1[2];
BattleGroupSetup btlgrp_jon_jon_11_01_off_1;
BattleUnitSetup btlparty_jon_jon_11_01_off_2[3];
BattleGroupSetup btlgrp_jon_jon_11_01_off_2;
BattleUnitSetup btlparty_jon_jon_11_01_off_3[3];
BattleGroupSetup btlgrp_jon_jon_11_01_off_3;
BattleUnitSetup btlparty_jon_jon_11_02_off_1[4];
BattleGroupSetup btlgrp_jon_jon_11_02_off_1;
BattleUnitSetup btlparty_jon_jon_11_02_off_2[3];
BattleGroupSetup btlgrp_jon_jon_11_02_off_2;
BattleUnitSetup btlparty_jon_jon_11_02_off_3[3];
BattleGroupSetup btlgrp_jon_jon_11_02_off_3;
BattleUnitSetup btlparty_jon_jon_11_03_off_1[4];
BattleGroupSetup btlgrp_jon_jon_11_03_off_1;
BattleUnitSetup btlparty_jon_jon_11_03_off_2[2];
BattleGroupSetup btlgrp_jon_jon_11_03_off_2;
BattleUnitSetup btlparty_jon_jon_11_03_off_3[4];
BattleGroupSetup btlgrp_jon_jon_11_03_off_3;
BattleUnitSetup btlparty_jon_jon_11_04_off_1[3];
BattleGroupSetup btlgrp_jon_jon_11_04_off_1;
BattleUnitSetup btlparty_jon_jon_11_04_off_2[3];
BattleGroupSetup btlgrp_jon_jon_11_04_off_2;
BattleUnitSetup btlparty_jon_jon_11_04_off_3[2];
BattleGroupSetup btlgrp_jon_jon_11_04_off_3;
BattleUnitSetup btlparty_jon_jon_11_05_off_1[4];
BattleGroupSetup btlgrp_jon_jon_11_05_off_1;
BattleUnitSetup btlparty_jon_jon_11_05_off_2[2];
BattleGroupSetup btlgrp_jon_jon_11_05_off_2;
BattleUnitSetup btlparty_jon_jon_11_05_off_3[4];
BattleGroupSetup btlgrp_jon_jon_11_05_off_3;
BattleUnitSetup btlparty_jon_jon_21_01_off_1[3];
BattleGroupSetup btlgrp_jon_jon_21_01_off_1;
BattleUnitSetup btlparty_jon_jon_21_01_off_2[4];
BattleGroupSetup btlgrp_jon_jon_21_01_off_2;
BattleUnitSetup btlparty_jon_jon_21_01_off_3[4];
BattleGroupSetup btlgrp_jon_jon_21_01_off_3;
BattleUnitSetup btlparty_jon_jon_21_02_off_1[5];
BattleGroupSetup btlgrp_jon_jon_21_02_off_1;
BattleUnitSetup btlparty_jon_jon_21_02_off_2[2];
BattleGroupSetup btlgrp_jon_jon_21_02_off_2;
BattleUnitSetup btlparty_jon_jon_21_02_off_3[5];
BattleGroupSetup btlgrp_jon_jon_21_02_off_3;
BattleUnitSetup btlparty_jon_jon_21_03_off_1[4];
BattleGroupSetup btlgrp_jon_jon_21_03_off_1;
BattleUnitSetup btlparty_jon_jon_21_03_off_2[2];
BattleGroupSetup btlgrp_jon_jon_21_03_off_2;
BattleUnitSetup btlparty_jon_jon_21_03_off_3[4];
BattleGroupSetup btlgrp_jon_jon_21_03_off_3;
BattleUnitSetup btlparty_jon_jon_21_04_off_1[4];
BattleGroupSetup btlgrp_jon_jon_21_04_off_1;
BattleUnitSetup btlparty_jon_jon_21_04_off_2[3];
BattleGroupSetup btlgrp_jon_jon_21_04_off_2;
BattleUnitSetup btlparty_jon_jon_21_04_off_3[4];
BattleGroupSetup btlgrp_jon_jon_21_04_off_3;
BattleUnitSetup btlparty_jon_jon_21_05_off_1[4];
BattleGroupSetup btlgrp_jon_jon_21_05_off_1;
BattleUnitSetup btlparty_jon_jon_21_05_off_2[3];
BattleGroupSetup btlgrp_jon_jon_21_05_off_2;
BattleUnitSetup btlparty_jon_jon_21_05_off_3[4];
BattleGroupSetup btlgrp_jon_jon_21_05_off_3;
BattleUnitSetup btlparty_jon_jon_31_01_off_1[2];
BattleGroupSetup btlgrp_jon_jon_31_01_off_1;
BattleUnitSetup btlparty_jon_jon_31_01_off_2[3];
BattleGroupSetup btlgrp_jon_jon_31_01_off_2;
BattleUnitSetup btlparty_jon_jon_31_01_off_3[3];
BattleGroupSetup btlgrp_jon_jon_31_01_off_3;
BattleUnitSetup btlparty_jon_jon_31_02_off_1[3];
BattleGroupSetup btlgrp_jon_jon_31_02_off_1;
BattleUnitSetup btlparty_jon_jon_31_02_off_2[3];
BattleGroupSetup btlgrp_jon_jon_31_02_off_2;
BattleUnitSetup btlparty_jon_jon_31_02_off_3[3];
BattleGroupSetup btlgrp_jon_jon_31_02_off_3;
BattleUnitSetup btlparty_jon_jon_31_03_off_1[4];
BattleGroupSetup btlgrp_jon_jon_31_03_off_1;
BattleUnitSetup btlparty_jon_jon_31_03_off_2[4];
BattleGroupSetup btlgrp_jon_jon_31_03_off_2;
BattleUnitSetup btlparty_jon_jon_31_03_off_3[2];
BattleGroupSetup btlgrp_jon_jon_31_03_off_3;
BattleUnitSetup btlparty_jon_jon_31_04_off_1[4];
BattleGroupSetup btlgrp_jon_jon_31_04_off_1;
BattleUnitSetup btlparty_jon_jon_31_04_off_2[3];
BattleGroupSetup btlgrp_jon_jon_31_04_off_2;
BattleUnitSetup btlparty_jon_jon_31_04_off_3[3];
BattleGroupSetup btlgrp_jon_jon_31_04_off_3;
BattleUnitSetup btlparty_jon_jon_31_05_off_1[5];
BattleGroupSetup btlgrp_jon_jon_31_05_off_1;
BattleUnitSetup btlparty_jon_jon_31_05_off_2[3];
BattleGroupSetup btlgrp_jon_jon_31_05_off_2;
BattleUnitSetup btlparty_jon_jon_31_05_off_3[2];
BattleGroupSetup btlgrp_jon_jon_31_05_off_3;
BattleUnitSetup btlparty_jon_jon_41_01_off_1[4];
BattleGroupSetup btlgrp_jon_jon_41_01_off_1;
BattleUnitSetup btlparty_jon_jon_41_01_off_2[3];
BattleGroupSetup btlgrp_jon_jon_41_01_off_2;
BattleUnitSetup btlparty_jon_jon_41_01_off_3[3];
BattleGroupSetup btlgrp_jon_jon_41_01_off_3;
BattleUnitSetup btlparty_jon_jon_41_02_off_1[4];
BattleGroupSetup btlgrp_jon_jon_41_02_off_1;
BattleUnitSetup btlparty_jon_jon_41_02_off_2[2];
BattleGroupSetup btlgrp_jon_jon_41_02_off_2;
BattleUnitSetup btlparty_jon_jon_41_02_off_3[3];
BattleGroupSetup btlgrp_jon_jon_41_02_off_3;
BattleUnitSetup btlparty_jon_jon_41_03_off_1[3];
BattleGroupSetup btlgrp_jon_jon_41_03_off_1;
BattleUnitSetup btlparty_jon_jon_41_03_off_2[3];
BattleGroupSetup btlgrp_jon_jon_41_03_off_2;
BattleUnitSetup btlparty_jon_jon_41_03_off_3[4];
BattleGroupSetup btlgrp_jon_jon_41_03_off_3;
BattleUnitSetup btlparty_jon_jon_41_04_off_1[4];
BattleGroupSetup btlgrp_jon_jon_41_04_off_1;
BattleUnitSetup btlparty_jon_jon_41_04_off_2[4];
BattleGroupSetup btlgrp_jon_jon_41_04_off_2;
BattleUnitSetup btlparty_jon_jon_41_04_off_3[2];
BattleGroupSetup btlgrp_jon_jon_41_04_off_3;
BattleUnitSetup btlparty_jon_jon_41_05_off_1[2];
BattleGroupSetup btlgrp_jon_jon_41_05_off_1;
BattleUnitSetup btlparty_jon_jon_41_05_off_2[4];
BattleGroupSetup btlgrp_jon_jon_41_05_off_2;
BattleUnitSetup btlparty_jon_jon_41_05_off_3[4];
BattleGroupSetup btlgrp_jon_jon_41_05_off_3;
BattleUnitSetup btlparty_jon_jon_51_01_off_1[3];
BattleGroupSetup btlgrp_jon_jon_51_01_off_1;
BattleUnitSetup btlparty_jon_jon_51_01_off_2[3];
BattleGroupSetup btlgrp_jon_jon_51_01_off_2;
BattleUnitSetup btlparty_jon_jon_51_01_off_3[3];
BattleGroupSetup btlgrp_jon_jon_51_01_off_3;
BattleUnitSetup btlparty_jon_jon_51_02_off_1[4];
BattleGroupSetup btlgrp_jon_jon_51_02_off_1;
BattleUnitSetup btlparty_jon_jon_51_02_off_2[3];
BattleGroupSetup btlgrp_jon_jon_51_02_off_2;
BattleUnitSetup btlparty_jon_jon_51_02_off_3[2];
BattleGroupSetup btlgrp_jon_jon_51_02_off_3;
BattleUnitSetup btlparty_jon_jon_51_03_off_1[4];
BattleGroupSetup btlgrp_jon_jon_51_03_off_1;
BattleUnitSetup btlparty_jon_jon_51_03_off_2[3];
BattleGroupSetup btlgrp_jon_jon_51_03_off_2;
BattleUnitSetup btlparty_jon_jon_51_03_off_3[3];
BattleGroupSetup btlgrp_jon_jon_51_03_off_3;
BattleUnitSetup btlparty_jon_jon_51_04_off_1[3];
BattleGroupSetup btlgrp_jon_jon_51_04_off_1;
BattleUnitSetup btlparty_jon_jon_51_04_off_2[3];
BattleGroupSetup btlgrp_jon_jon_51_04_off_2;
BattleUnitSetup btlparty_jon_jon_51_04_off_3[3];
BattleGroupSetup btlgrp_jon_jon_51_04_off_3;
BattleUnitSetup btlparty_jon_jon_51_05_off_1[4];
BattleGroupSetup btlgrp_jon_jon_51_05_off_1;
BattleUnitSetup btlparty_jon_jon_51_05_off_2[3];
BattleGroupSetup btlgrp_jon_jon_51_05_off_2;
BattleUnitSetup btlparty_jon_jon_51_05_off_3[3];
BattleGroupSetup btlgrp_jon_jon_51_05_off_3;
BattleUnitSetup btlparty_jon_jon_61_01_off_1[3];
BattleGroupSetup btlgrp_jon_jon_61_01_off_1;
BattleUnitSetup btlparty_jon_jon_61_01_off_2[3];
BattleGroupSetup btlgrp_jon_jon_61_01_off_2;
BattleUnitSetup btlparty_jon_jon_61_01_off_3[2];
BattleGroupSetup btlgrp_jon_jon_61_01_off_3;
BattleUnitSetup btlparty_jon_jon_61_02_off_1[4];
BattleGroupSetup btlgrp_jon_jon_61_02_off_1;
BattleUnitSetup btlparty_jon_jon_61_02_off_2[2];
BattleGroupSetup btlgrp_jon_jon_61_02_off_2;
BattleUnitSetup btlparty_jon_jon_61_02_off_3[3];
BattleGroupSetup btlgrp_jon_jon_61_02_off_3;
BattleUnitSetup btlparty_jon_jon_61_03_off_1[3];
BattleGroupSetup btlgrp_jon_jon_61_03_off_1;
BattleUnitSetup btlparty_jon_jon_61_03_off_2[3];
BattleGroupSetup btlgrp_jon_jon_61_03_off_2;
BattleUnitSetup btlparty_jon_jon_61_03_off_3[3];
BattleGroupSetup btlgrp_jon_jon_61_03_off_3;
BattleUnitSetup btlparty_jon_jon_61_04_off_1[4];
BattleGroupSetup btlgrp_jon_jon_61_04_off_1;
BattleUnitSetup btlparty_jon_jon_61_04_off_2[3];
BattleGroupSetup btlgrp_jon_jon_61_04_off_2;
BattleUnitSetup btlparty_jon_jon_61_04_off_3[2];
BattleGroupSetup btlgrp_jon_jon_61_04_off_3;
BattleUnitSetup btlparty_jon_jon_61_05_off_1[3];
BattleGroupSetup btlgrp_jon_jon_61_05_off_1;
BattleUnitSetup btlparty_jon_jon_61_05_off_2[2];
BattleGroupSetup btlgrp_jon_jon_61_05_off_2;
BattleUnitSetup btlparty_jon_jon_61_05_off_3[2];
BattleGroupSetup btlgrp_jon_jon_61_05_off_3;
BattleUnitSetup btlparty_jon_jon_71_01_off_1[3];
BattleGroupSetup btlgrp_jon_jon_71_01_off_1;
BattleUnitSetup btlparty_jon_jon_71_01_off_2[3];
BattleGroupSetup btlgrp_jon_jon_71_01_off_2;
BattleUnitSetup btlparty_jon_jon_71_01_off_3[3];
BattleGroupSetup btlgrp_jon_jon_71_01_off_3;
BattleUnitSetup btlparty_jon_jon_71_02_off_1[3];
BattleGroupSetup btlgrp_jon_jon_71_02_off_1;
BattleUnitSetup btlparty_jon_jon_71_02_off_2[3];
BattleGroupSetup btlgrp_jon_jon_71_02_off_2;
BattleUnitSetup btlparty_jon_jon_71_02_off_3[3];
BattleGroupSetup btlgrp_jon_jon_71_02_off_3;
BattleUnitSetup btlparty_jon_jon_71_03_off_1[5];
BattleGroupSetup btlgrp_jon_jon_71_03_off_1;
BattleUnitSetup btlparty_jon_jon_71_03_off_2[4];
BattleGroupSetup btlgrp_jon_jon_71_03_off_2;
BattleUnitSetup btlparty_jon_jon_71_03_off_3[4];
BattleGroupSetup btlgrp_jon_jon_71_03_off_3;
BattleUnitSetup btlparty_jon_jon_71_04_off_1[4];
BattleGroupSetup btlgrp_jon_jon_71_04_off_1;
BattleUnitSetup btlparty_jon_jon_71_04_off_2[4];
BattleGroupSetup btlgrp_jon_jon_71_04_off_2;
BattleUnitSetup btlparty_jon_jon_71_04_off_3[4];
BattleGroupSetup btlgrp_jon_jon_71_04_off_3;
BattleUnitSetup btlparty_jon_jon_71_05_off_1[4];
BattleGroupSetup btlgrp_jon_jon_71_05_off_1;
BattleUnitSetup btlparty_jon_jon_71_05_off_2[3];
BattleGroupSetup btlgrp_jon_jon_71_05_off_2;
BattleUnitSetup btlparty_jon_jon_71_05_off_3[3];
BattleGroupSetup btlgrp_jon_jon_71_05_off_3;
BattleUnitSetup btlparty_jon_jon_81_01_off_1[4];
BattleGroupSetup btlgrp_jon_jon_81_01_off_1;
BattleUnitSetup btlparty_jon_jon_81_01_off_2[4];
BattleGroupSetup btlgrp_jon_jon_81_01_off_2;
BattleUnitSetup btlparty_jon_jon_81_01_off_3[3];
BattleGroupSetup btlgrp_jon_jon_81_01_off_3;
BattleUnitSetup btlparty_jon_jon_81_02_off_1[2];
BattleGroupSetup btlgrp_jon_jon_81_02_off_1;
BattleUnitSetup btlparty_jon_jon_81_02_off_2[4];
BattleGroupSetup btlgrp_jon_jon_81_02_off_2;
BattleUnitSetup btlparty_jon_jon_81_02_off_3[3];
BattleGroupSetup btlgrp_jon_jon_81_02_off_3;
BattleUnitSetup btlparty_jon_jon_81_03_off_1[4];
BattleGroupSetup btlgrp_jon_jon_81_03_off_1;
BattleUnitSetup btlparty_jon_jon_81_03_off_2[3];
BattleGroupSetup btlgrp_jon_jon_81_03_off_2;
BattleUnitSetup btlparty_jon_jon_81_03_off_3[3];
BattleGroupSetup btlgrp_jon_jon_81_03_off_3;
BattleUnitSetup btlparty_jon_jon_81_04_off_1[4];
BattleGroupSetup btlgrp_jon_jon_81_04_off_1;
BattleUnitSetup btlparty_jon_jon_81_04_off_2[3];
BattleGroupSetup btlgrp_jon_jon_81_04_off_2;
BattleUnitSetup btlparty_jon_jon_81_04_off_3[4];
BattleGroupSetup btlgrp_jon_jon_81_04_off_3;
BattleUnitSetup btlparty_jon_jon_81_05_off_1[4];
BattleGroupSetup btlgrp_jon_jon_81_05_off_1;
BattleUnitSetup btlparty_jon_jon_81_05_off_2[3];
BattleGroupSetup btlgrp_jon_jon_81_05_off_2;
BattleUnitSetup btlparty_jon_jon_81_05_off_3[5];
BattleGroupSetup btlgrp_jon_jon_81_05_off_3;
BattleUnitSetup btlparty_jon_jon_91_01_off_1[5];
BattleGroupSetup btlgrp_jon_jon_91_01_off_1;
BattleUnitSetup btlparty_jon_jon_91_01_off_2[3];
BattleGroupSetup btlgrp_jon_jon_91_01_off_2;
BattleUnitSetup btlparty_jon_jon_91_01_off_3[3];
BattleGroupSetup btlgrp_jon_jon_91_01_off_3;
BattleUnitSetup btlparty_jon_jon_91_02_off_1[4];
BattleGroupSetup btlgrp_jon_jon_91_02_off_1;
BattleUnitSetup btlparty_jon_jon_91_02_off_2[4];
BattleGroupSetup btlgrp_jon_jon_91_02_off_2;
BattleUnitSetup btlparty_jon_jon_91_02_off_3[4];
BattleGroupSetup btlgrp_jon_jon_91_02_off_3;
BattleUnitSetup btlparty_jon_jon_91_03_off_1[4];
BattleGroupSetup btlgrp_jon_jon_91_03_off_1;
BattleUnitSetup btlparty_jon_jon_91_03_off_2[3];
BattleGroupSetup btlgrp_jon_jon_91_03_off_2;
BattleUnitSetup btlparty_jon_jon_91_03_off_3[4];
BattleGroupSetup btlgrp_jon_jon_91_03_off_3;
BattleUnitSetup btlparty_jon_jon_91_04_off_1[5];
BattleGroupSetup btlgrp_jon_jon_91_04_off_1;
BattleUnitSetup btlparty_jon_jon_91_04_off_2[3];
BattleGroupSetup btlgrp_jon_jon_91_04_off_2;
BattleUnitSetup btlparty_jon_jon_91_04_off_3[4];
BattleGroupSetup btlgrp_jon_jon_91_04_off_3;
BattleUnitSetup btlparty_jon_jon_91_05_off_1[5];
BattleGroupSetup btlgrp_jon_jon_91_05_off_1;
BattleUnitSetup btlparty_jon_jon_91_05_off_2[5];
BattleGroupSetup btlgrp_jon_jon_91_05_off_2;
BattleUnitSetup btlparty_jon_jon_91_05_off_3[5];
BattleGroupSetup btlgrp_jon_jon_91_05_off_3;
NpcBattleSelect btlgrpsel_jon_btlno_jon_test1_off[2];
NpcBattleSelect btlgrpsel_jon_btlno_jon_01_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_02_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_03_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_04_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_05_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_11_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_12_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_13_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_14_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_15_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_21_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_22_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_23_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_24_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_25_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_31_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_32_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_33_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_34_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_35_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_41_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_42_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_43_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_44_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_45_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_51_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_52_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_53_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_54_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_55_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_61_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_62_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_63_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_64_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_65_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_71_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_72_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_73_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_74_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_75_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_81_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_82_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_83_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_84_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_85_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_91_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_92_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_93_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_94_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_95_off[4];
NpcBattleSelect btlgrpsel_jon_btlno_jon_100_zonbaba_off[2];
NpcSetupBattleInfo btlsetup_jon_tbl[53];
NpcTerritoryInfo btl_jon_setup_no_tbl[53];

BattleStageObjectData jon_btlobject_data[] = {
    {"B_0", 2, 2, {0}, 0, 60, {0}},
    {"jon_0", 2, 3, {0}, 0, 60, {0}},
    {"B_1", 2, 2, {0}, 0, 60, {0}},
    {"jon_1", 2, 3, {0}, 0, 60, {0}},
    {"B_2", 2, 2, {0}, 0, 60, {0}},
    {"jon_2", 2, 3, {0}, 0, 60, {0}},
    {"B_6", 2, 2, {0}, 0, 60, {0}},
    {"jon_6", 2, 3, {0}, 0, 60, {0}},
};

BattleStageData jon_btlstage_data[] = {
    {
        "bti_01", // globalStageDataDir
        "stg_00_3", // specificStageDataDir
        2, // numObjects
        jon_btlobject_data, // objects
        {NULL, 0, {0}, 0, NULL, 100, 0, 0, 2, 0.0f, 0, 0, 0, 0, NULL, {0}, NULL, {0}, 0x2100060, 0x20000000, 0, 26, 3, 2, NULL, 0, 0x7FF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, NULL, {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}}, // bgAWeapon
        {NULL, 0, {0}, 0, NULL, 100, 0, 0, 2, 0.0f, 0, 0, 0, 0, weaponGetPowerDefault, {1, 0, 0, 0, 0, 0, 0, 0}, NULL, {0}, 0x2100060, 0x20000000, 0, 26, 3, 2, NULL, 0, 0x7FF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, NULL, {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}}, // bgBWeapon
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, // initEvt..bgCEvt
        0, 0, 0, 0, // reserved_1B0..disableBgBDestroy
    },
    {
        "bti_01", // globalStageDataDir
        "stg_00_3", // specificStageDataDir
        2, // numObjects
        &jon_btlobject_data[2], // objects
        {NULL, 0, {0}, 0, NULL, 100, 0, 0, 2, 0.0f, 0, 0, 0, 0, NULL, {0}, NULL, {0}, 0x2100060, 0x20000000, 0, 26, 3, 2, NULL, 0, 0x7FF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, NULL, {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}}, // bgAWeapon
        {NULL, 0, {0}, 0, NULL, 100, 0, 0, 2, 0.0f, 0, 0, 0, 0, weaponGetPowerDefault, {1, 0, 0, 0, 0, 0, 0, 0}, NULL, {0}, 0x2100060, 0x20000000, 0, 26, 3, 2, NULL, 0, 0x7FF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, NULL, {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}}, // bgBWeapon
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, // initEvt..bgCEvt
        0, 0, 0, 0, // reserved_1B0..disableBgBDestroy
    },
    {
        "bti_01", // globalStageDataDir
        "stg_00_3", // specificStageDataDir
        2, // numObjects
        &jon_btlobject_data[4], // objects
        {NULL, 0, {0}, 0, NULL, 100, 0, 0, 2, 0.0f, 0, 0, 0, 0, NULL, {0}, NULL, {0}, 0x2100060, 0x20000000, 0, 26, 3, 2, NULL, 0, 0x7FF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, NULL, {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}}, // bgAWeapon
        {NULL, 0, {0}, 0, NULL, 100, 0, 0, 2, 0.0f, 0, 0, 0, 0, weaponGetPowerDefault, {1, 0, 0, 0, 0, 0, 0, 0}, NULL, {0}, 0x2100060, 0x20000000, 0, 26, 3, 2, NULL, 0, 0x7FF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, NULL, {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}}, // bgBWeapon
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, // initEvt..bgCEvt
        0, 0, 0, 0, // reserved_1B0..disableBgBDestroy
    },
    {
        "bti_01", // globalStageDataDir
        "stg_00_3", // specificStageDataDir
        2, // numObjects
        &jon_btlobject_data[6], // objects
        {NULL, 0, {0}, 0, NULL, 100, 0, 0, 2, 0.0f, 0, 0, 0, 0, NULL, {0}, NULL, {0}, 0x2100060, 0x20000000, 0, 26, 3, 2, NULL, 0, 0x7FF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, NULL, {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}}, // bgAWeapon
        {NULL, 0, {0}, 0, NULL, 100, 0, 0, 2, 0.0f, 0, 0, 0, 0, weaponGetPowerDefault, {1, 0, 0, 0, 0, 0, 0, 0}, NULL, {0}, 0x2100060, 0x20000000, 0, 26, 3, 2, NULL, 0, 0x7FF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, NULL, {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}}, // bgBWeapon
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, // initEvt..bgCEvt
        0, 0, 0, 0, // reserved_1B0..disableBgBDestroy
    },
};

BattleUnitSetup btlparty_jon_jon_100_01_off_1[] = {
    {
        &unit_boss_zonbaba, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {365.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_zonbaba, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_100_01_off_1 = {
    1, // numEnemies
    btlparty_jon_jon_100_01_off_1, // enemyData
    0, 0, // heldItemWeight..randomItemWeight
    100, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_01_01_off_1[] = {
    {
        &unit_yami_kuriboo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_kuriboo, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_01_01_off_1 = {
    1, // numEnemies
    btlparty_jon_jon_01_01_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_01_01_off_2[] = {
    {
        &unit_yami_kuriboo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_kuriboo, // itemDropTable
    },
    {
        &unit_hannya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hannya, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_01_01_off_2 = {
    2, // numEnemies
    btlparty_jon_jon_01_01_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_01_01_off_3[] = {
    {
        &unit_yami_kuriboo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_kuriboo, // itemDropTable
    },
    {
        &unit_honenoko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_honenoko, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_01_01_off_3 = {
    2, // numEnemies
    btlparty_jon_jon_01_01_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_01_02_off_1[] = {
    {
        &unit_hinnya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {10.0f, 0.0f, -20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hinnya, // itemDropTable
    },
    {
        &unit_hinnya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hinnya, // itemDropTable
    },
    {
        &unit_hinnya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hinnya, // itemDropTable
    },
    {
        &unit_hinnya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hinnya, // itemDropTable
    },
    {
        &unit_hinnya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {170.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hinnya, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_01_02_off_1 = {
    5, // numEnemies
    btlparty_jon_jon_01_02_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_01_02_off_2[] = {
    {
        &unit_hinnya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hinnya, // itemDropTable
    },
    {
        &unit_yami_kuriboo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_kuriboo, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_01_02_off_2 = {
    2, // numEnemies
    btlparty_jon_jon_01_02_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_01_02_off_3[] = {
    {
        &unit_hinnya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {10.0f, 0.0f, -20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hinnya, // itemDropTable
    },
    {
        &unit_hannya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hannya, // itemDropTable
    },
    {
        &unit_hinnya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hinnya, // itemDropTable
    },
    {
        &unit_hannya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hannya, // itemDropTable
    },
    {
        &unit_hinnya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {170.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hinnya, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_01_02_off_3 = {
    5, // numEnemies
    btlparty_jon_jon_01_02_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_01_03_off_1[] = {
    {
        &unit_hannya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hannya, // itemDropTable
    },
    {
        &unit_hannya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hannya, // itemDropTable
    },
    {
        &unit_hannya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hannya, // itemDropTable
    },
    {
        &unit_hannya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hannya, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_01_03_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_01_03_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_01_03_off_2[] = {
    {
        &unit_hannya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hannya, // itemDropTable
    },
    {
        &unit_yami_kuriboo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_kuriboo, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_01_03_off_2 = {
    2, // numEnemies
    btlparty_jon_jon_01_03_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_01_03_off_3[] = {
    {
        &unit_hannya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hannya, // itemDropTable
    },
    {
        &unit_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_chorobon, // itemDropTable
    },
    {
        &unit_hannya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hannya, // itemDropTable
    },
    {
        &unit_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_chorobon, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_01_03_off_3 = {
    4, // numEnemies
    btlparty_jon_jon_01_03_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_01_04_off_1[] = {
    {
        &unit_honenoko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_honenoko, // itemDropTable
    },
    {
        &unit_honenoko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_honenoko, // itemDropTable
    },
    {
        &unit_honenoko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_honenoko, // itemDropTable
    },
    {
        &unit_honenoko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_honenoko, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_01_04_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_01_04_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_01_04_off_2[] = {
    {
        &unit_honenoko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_honenoko, // itemDropTable
    },
    {
        &unit_yami_kuriboo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_kuriboo, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_01_04_off_2 = {
    2, // numEnemies
    btlparty_jon_jon_01_04_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_01_04_off_3[] = {
    {
        &unit_honenoko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_honenoko, // itemDropTable
    },
    {
        &unit_hinnya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hinnya, // itemDropTable
    },
    {
        &unit_hinnya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hinnya, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_01_04_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_01_04_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_01_05_off_1[] = {
    {
        &unit_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {10.0f, 0.0f, -20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_chorobon, // itemDropTable
    },
    {
        &unit_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_chorobon, // itemDropTable
    },
    {
        &unit_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_chorobon, // itemDropTable
    },
    {
        &unit_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_chorobon, // itemDropTable
    },
    {
        &unit_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {170.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_chorobon, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_01_05_off_1 = {
    5, // numEnemies
    btlparty_jon_jon_01_05_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_01_05_off_2[] = {
    {
        &unit_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_chorobon, // itemDropTable
    },
    {
        &unit_yami_kuriboo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_kuriboo, // itemDropTable
    },
    {
        &unit_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_chorobon, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_01_05_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_01_05_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_01_05_off_3[] = {
    {
        &unit_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_chorobon, // itemDropTable
    },
    {
        &unit_honenoko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_honenoko, // itemDropTable
    },
    {
        &unit_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_chorobon, // itemDropTable
    },
    {
        &unit_honenoko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_honenoko, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_01_05_off_3 = {
    4, // numEnemies
    btlparty_jon_jon_01_05_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_11_01_off_1[] = {
    {
        &unit_yami_patakuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
    {
        &unit_yami_patakuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_11_01_off_1 = {
    2, // numEnemies
    btlparty_jon_jon_11_01_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_11_01_off_2[] = {
    {
        &unit_yami_patakuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
    {
        &unit_piders, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_piders, // itemDropTable
    },
    {
        &unit_piders, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_piders, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_11_01_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_11_01_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_11_01_off_3[] = {
    {
        &unit_yami_patakuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
    {
        &unit_sambo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo, // itemDropTable
    },
    {
        &unit_sambo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_11_01_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_11_01_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_11_02_off_1[] = {
    {
        &unit_monochrome_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_monochrome_kurokumorn, // itemDropTable
    },
    {
        &unit_monochrome_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_monochrome_kurokumorn, // itemDropTable
    },
    {
        &unit_monochrome_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_monochrome_kurokumorn, // itemDropTable
    },
    {
        &unit_monochrome_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_monochrome_kurokumorn, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_11_02_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_11_02_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_11_02_off_2[] = {
    {
        &unit_monochrome_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_monochrome_kurokumorn, // itemDropTable
    },
    {
        &unit_monochrome_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_monochrome_kurokumorn, // itemDropTable
    },
    {
        &unit_yami_patakuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_11_02_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_11_02_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_11_02_off_3[] = {
    {
        &unit_monochrome_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_monochrome_kurokumorn, // itemDropTable
    },
    {
        &unit_piders, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_piders, // itemDropTable
    },
    {
        &unit_monochrome_kurokumorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_monochrome_kurokumorn, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_11_02_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_11_02_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_11_03_off_1[] = {
    {
        &unit_sambo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo, // itemDropTable
    },
    {
        &unit_sambo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo, // itemDropTable
    },
    {
        &unit_sambo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo, // itemDropTable
    },
    {
        &unit_sambo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_11_03_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_11_03_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_11_03_off_2[] = {
    {
        &unit_sambo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo, // itemDropTable
    },
    {
        &unit_monochrome_kurokumorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_monochrome_kurokumorn, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_11_03_off_2 = {
    2, // numEnemies
    btlparty_jon_jon_11_03_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_11_03_off_3[] = {
    {
        &unit_sambo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo, // itemDropTable
    },
    {
        &unit_piders, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_piders, // itemDropTable
    },
    {
        &unit_piders, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_piders, // itemDropTable
    },
    {
        &unit_sambo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_11_03_off_3 = {
    4, // numEnemies
    btlparty_jon_jon_11_03_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_11_04_off_1[] = {
    {
        &unit_monochrome_kurokumorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_monochrome_kurokumorn, // itemDropTable
    },
    {
        &unit_monochrome_kurokumorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_monochrome_kurokumorn, // itemDropTable
    },
    {
        &unit_monochrome_kurokumorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_monochrome_kurokumorn, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_11_04_off_1 = {
    3, // numEnemies
    btlparty_jon_jon_11_04_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_11_04_off_2[] = {
    {
        &unit_monochrome_kurokumorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_monochrome_kurokumorn, // itemDropTable
    },
    {
        &unit_sambo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo, // itemDropTable
    },
    {
        &unit_monochrome_kurokumorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_monochrome_kurokumorn, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_11_04_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_11_04_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_11_04_off_3[] = {
    {
        &unit_monochrome_kurokumorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_monochrome_kurokumorn, // itemDropTable
    },
    {
        &unit_yami_patakuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_11_04_off_3 = {
    2, // numEnemies
    btlparty_jon_jon_11_04_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_11_05_off_1[] = {
    {
        &unit_piders, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_piders, // itemDropTable
    },
    {
        &unit_piders, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_piders, // itemDropTable
    },
    {
        &unit_piders, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_piders, // itemDropTable
    },
    {
        &unit_piders, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 40.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_piders, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_11_05_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_11_05_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_11_05_off_2[] = {
    {
        &unit_piders, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_piders, // itemDropTable
    },
    {
        &unit_yami_patakuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_11_05_off_2 = {
    2, // numEnemies
    btlparty_jon_jon_11_05_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_11_05_off_3[] = {
    {
        &unit_piders, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_piders, // itemDropTable
    },
    {
        &unit_sambo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo, // itemDropTable
    },
    {
        &unit_piders, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_piders, // itemDropTable
    },
    {
        &unit_sambo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_11_05_off_3 = {
    4, // numEnemies
    btlparty_jon_jon_11_05_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_21_01_off_1[] = {
    {
        &unit_yami_togekuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_togekuri, // itemDropTable
    },
    {
        &unit_yami_togekuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_togekuri, // itemDropTable
    },
    {
        &unit_yami_togekuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_togekuri, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_21_01_off_1 = {
    3, // numEnemies
    btlparty_jon_jon_21_01_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_21_01_off_2[] = {
    {
        &unit_yami_togekuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_togekuri, // itemDropTable
    },
    {
        &unit_yami_togekuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_togekuri, // itemDropTable
    },
    {
        &unit_bomhei, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bomhei, // itemDropTable
    },
    {
        &unit_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_borodo, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_21_01_off_2 = {
    4, // numEnemies
    btlparty_jon_jon_21_01_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_21_01_off_3[] = {
    {
        &unit_yami_togekuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_togekuri, // itemDropTable
    },
    {
        &unit_yami_togekuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_togekuri, // itemDropTable
    },
    {
        &unit_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_teresa, // itemDropTable
    },
    {
        &unit_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_teresa, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_21_01_off_3 = {
    4, // numEnemies
    btlparty_jon_jon_21_01_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_21_02_off_1[] = {
    {
        &unit_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {10.0f, 0.0f, -20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_borodo, // itemDropTable
    },
    {
        &unit_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_borodo, // itemDropTable
    },
    {
        &unit_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_borodo, // itemDropTable
    },
    {
        &unit_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_borodo, // itemDropTable
    },
    {
        &unit_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {170.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_borodo, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_21_02_off_1 = {
    5, // numEnemies
    btlparty_jon_jon_21_02_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_21_02_off_2[] = {
    {
        &unit_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_borodo, // itemDropTable
    },
    {
        &unit_yami_togekuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_togekuri, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_21_02_off_2 = {
    2, // numEnemies
    btlparty_jon_jon_21_02_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_21_02_off_3[] = {
    {
        &unit_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {10.0f, 0.0f, -20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_borodo, // itemDropTable
    },
    {
        &unit_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_teresa, // itemDropTable
    },
    {
        &unit_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_borodo, // itemDropTable
    },
    {
        &unit_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_teresa, // itemDropTable
    },
    {
        &unit_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {170.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_borodo, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_21_02_off_3 = {
    5, // numEnemies
    btlparty_jon_jon_21_02_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_21_03_off_1[] = {
    {
        &unit_jyugem, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_jyugem, // itemDropTable
    },
    {
        &unit_jyugem, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_jyugem, // itemDropTable
    },
    {
        &unit_jyugem, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_jyugem, // itemDropTable
    },
    {
        &unit_jyugem, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 40.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_jyugem, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_21_03_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_21_03_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_21_03_off_2[] = {
    {
        &unit_jyugem, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_jyugem, // itemDropTable
    },
    {
        &unit_yami_togekuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_togekuri, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_21_03_off_2 = {
    2, // numEnemies
    btlparty_jon_jon_21_03_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_21_03_off_3[] = {
    {
        &unit_jyugem, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_jyugem, // itemDropTable
    },
    {
        &unit_bomhei, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bomhei, // itemDropTable
    },
    {
        &unit_bomhei, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bomhei, // itemDropTable
    },
    {
        &unit_jyugem, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 40.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_jyugem, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_21_03_off_3 = {
    4, // numEnemies
    btlparty_jon_jon_21_03_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_21_04_off_1[] = {
    {
        &unit_bomhei, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bomhei, // itemDropTable
    },
    {
        &unit_bomhei, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bomhei, // itemDropTable
    },
    {
        &unit_bomhei, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bomhei, // itemDropTable
    },
    {
        &unit_bomhei, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bomhei, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_21_04_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_21_04_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_21_04_off_2[] = {
    {
        &unit_bomhei, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bomhei, // itemDropTable
    },
    {
        &unit_yami_togekuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_togekuri, // itemDropTable
    },
    {
        &unit_bomhei, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bomhei, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_21_04_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_21_04_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_21_04_off_3[] = {
    {
        &unit_bomhei, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bomhei, // itemDropTable
    },
    {
        &unit_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_teresa, // itemDropTable
    },
    {
        &unit_bomhei, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bomhei, // itemDropTable
    },
    {
        &unit_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_teresa, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_21_04_off_3 = {
    4, // numEnemies
    btlparty_jon_jon_21_04_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_21_05_off_1[] = {
    {
        &unit_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_teresa, // itemDropTable
    },
    {
        &unit_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_teresa, // itemDropTable
    },
    {
        &unit_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_teresa, // itemDropTable
    },
    {
        &unit_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_teresa, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_21_05_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_21_05_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_21_05_off_2[] = {
    {
        &unit_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_teresa, // itemDropTable
    },
    {
        &unit_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_teresa, // itemDropTable
    },
    {
        &unit_yami_togekuri, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_togekuri, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_21_05_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_21_05_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_21_05_off_3[] = {
    {
        &unit_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_teresa, // itemDropTable
    },
    {
        &unit_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_teresa, // itemDropTable
    },
    {
        &unit_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_borodo, // itemDropTable
    },
    {
        &unit_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_borodo, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_21_05_off_3 = {
    4, // numEnemies
    btlparty_jon_jon_21_05_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_31_01_off_1[] = {
    {
        &unit_yami_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_noko, // itemDropTable
    },
    {
        &unit_yami_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_noko, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_31_01_off_1 = {
    2, // numEnemies
    btlparty_jon_jon_31_01_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_31_01_off_2[] = {
    {
        &unit_yami_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_noko, // itemDropTable
    },
    {
        &unit_patamet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patamet, // itemDropTable
    },
    {
        &unit_patamet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patamet, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_31_01_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_31_01_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_31_01_off_3[] = {
    {
        &unit_yami_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_noko, // itemDropTable
    },
    {
        &unit_flower_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_flower_chorobon, // itemDropTable
    },
    {
        &unit_flower_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_flower_chorobon, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_31_01_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_31_01_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_31_02_off_1[] = {
    {
        &unit_hyper_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_sinemon, // itemDropTable
    },
    {
        &unit_hyper_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_sinemon, // itemDropTable
    },
    {
        &unit_hyper_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_sinemon, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_31_02_off_1 = {
    3, // numEnemies
    btlparty_jon_jon_31_02_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_31_02_off_2[] = {
    {
        &unit_hyper_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_sinemon, // itemDropTable
    },
    {
        &unit_ura_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ura_noko, // itemDropTable
    },
    {
        &unit_hyper_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_sinemon, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_31_02_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_31_02_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_31_02_off_3[] = {
    {
        &unit_hyper_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_sinemon, // itemDropTable
    },
    {
        &unit_hyper_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_sinemon, // itemDropTable
    },
    {
        &unit_patamet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patamet, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_31_02_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_31_02_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_31_03_off_1[] = {
    {
        &unit_patamet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patamet, // itemDropTable
    },
    {
        &unit_patamet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patamet, // itemDropTable
    },
    {
        &unit_patamet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patamet, // itemDropTable
    },
    {
        &unit_patamet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 40.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patamet, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_31_03_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_31_03_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_31_03_off_2[] = {
    {
        &unit_patamet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patamet, // itemDropTable
    },
    {
        &unit_ura_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ura_noko, // itemDropTable
    },
    {
        &unit_patamet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patamet, // itemDropTable
    },
    {
        &unit_ura_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ura_noko, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_31_03_off_2 = {
    4, // numEnemies
    btlparty_jon_jon_31_03_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_31_03_off_3[] = {
    {
        &unit_patamet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patamet, // itemDropTable
    },
    {
        &unit_flower_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_flower_chorobon, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_31_03_off_3 = {
    2, // numEnemies
    btlparty_jon_jon_31_03_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_31_04_off_1[] = {
    {
        &unit_ura_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ura_noko, // itemDropTable
    },
    {
        &unit_ura_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ura_noko, // itemDropTable
    },
    {
        &unit_ura_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ura_noko, // itemDropTable
    },
    {
        &unit_ura_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ura_noko, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_31_04_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_31_04_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_31_04_off_2[] = {
    {
        &unit_ura_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ura_noko, // itemDropTable
    },
    {
        &unit_yami_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_noko, // itemDropTable
    },
    {
        &unit_ura_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ura_noko, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_31_04_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_31_04_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_31_04_off_3[] = {
    {
        &unit_ura_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ura_noko, // itemDropTable
    },
    {
        &unit_ura_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ura_noko, // itemDropTable
    },
    {
        &unit_patamet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patamet, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_31_04_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_31_04_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_31_05_off_1[] = {
    {
        &unit_flower_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {10.0f, 0.0f, -20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_flower_chorobon, // itemDropTable
    },
    {
        &unit_flower_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_flower_chorobon, // itemDropTable
    },
    {
        &unit_flower_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_flower_chorobon, // itemDropTable
    },
    {
        &unit_flower_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_flower_chorobon, // itemDropTable
    },
    {
        &unit_flower_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {170.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_flower_chorobon, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_31_05_off_1 = {
    5, // numEnemies
    btlparty_jon_jon_31_05_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_31_05_off_2[] = {
    {
        &unit_flower_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_flower_chorobon, // itemDropTable
    },
    {
        &unit_flower_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_flower_chorobon, // itemDropTable
    },
    {
        &unit_yami_noko, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_noko, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_31_05_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_31_05_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_31_05_off_3[] = {
    {
        &unit_flower_chorobon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_flower_chorobon, // itemDropTable
    },
    {
        &unit_hyper_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_sinemon, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_31_05_off_3 = {
    2, // numEnemies
    btlparty_jon_jon_31_05_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_41_01_off_1[] = {
    {
        &unit_yami_pata, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
    {
        &unit_yami_pata, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
    {
        &unit_yami_pata, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
    {
        &unit_yami_pata, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 40.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_41_01_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_41_01_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_41_01_off_2[] = {
    {
        &unit_yami_pata, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
    {
        &unit_yami_pata, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
    {
        &unit_patatogemet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patatogemet, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_41_01_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_41_01_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_41_01_off_3[] = {
    {
        &unit_yami_pata, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
    {
        &unit_yami_pata, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
    {
        &unit_heavy_bom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_heavy_bom, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_41_01_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_41_01_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_41_02_off_1[] = {
    {
        &unit_heavy_bom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_heavy_bom, // itemDropTable
    },
    {
        &unit_heavy_bom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_heavy_bom, // itemDropTable
    },
    {
        &unit_heavy_bom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_heavy_bom, // itemDropTable
    },
    {
        &unit_heavy_bom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_heavy_bom, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_41_02_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_41_02_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_41_02_off_2[] = {
    {
        &unit_heavy_bom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_heavy_bom, // itemDropTable
    },
    {
        &unit_heavy_bom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_heavy_bom, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_41_02_off_2 = {
    2, // numEnemies
    btlparty_jon_jon_41_02_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_41_02_off_3[] = {
    {
        &unit_heavy_bom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_heavy_bom, // itemDropTable
    },
    {
        &unit_sambo_mummy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo_mummy, // itemDropTable
    },
    {
        &unit_patatogemet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patatogemet, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_41_02_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_41_02_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_41_03_off_1[] = {
    {
        &unit_bubble, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bubble, // itemDropTable
    },
    {
        &unit_bubble, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bubble, // itemDropTable
    },
    {
        &unit_bubble, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bubble, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_41_03_off_1 = {
    3, // numEnemies
    btlparty_jon_jon_41_03_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_41_03_off_2[] = {
    {
        &unit_bubble, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bubble, // itemDropTable
    },
    {
        &unit_bubble, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bubble, // itemDropTable
    },
    {
        &unit_yami_pata, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_41_03_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_41_03_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_41_03_off_3[] = {
    {
        &unit_bubble, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bubble, // itemDropTable
    },
    {
        &unit_sambo_mummy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo_mummy, // itemDropTable
    },
    {
        &unit_bubble, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bubble, // itemDropTable
    },
    {
        &unit_heavy_bom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_heavy_bom, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_41_03_off_3 = {
    4, // numEnemies
    btlparty_jon_jon_41_03_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_41_04_off_1[] = {
    {
        &unit_sambo_mummy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo_mummy, // itemDropTable
    },
    {
        &unit_sambo_mummy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo_mummy, // itemDropTable
    },
    {
        &unit_sambo_mummy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo_mummy, // itemDropTable
    },
    {
        &unit_sambo_mummy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo_mummy, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_41_04_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_41_04_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_41_04_off_2[] = {
    {
        &unit_sambo_mummy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo_mummy, // itemDropTable
    },
    {
        &unit_patatogemet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patatogemet, // itemDropTable
    },
    {
        &unit_sambo_mummy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo_mummy, // itemDropTable
    },
    {
        &unit_patatogemet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 40.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patatogemet, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_41_04_off_2 = {
    4, // numEnemies
    btlparty_jon_jon_41_04_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_41_04_off_3[] = {
    {
        &unit_sambo_mummy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sambo_mummy, // itemDropTable
    },
    {
        &unit_yami_pata, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yami_patakuri, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_41_04_off_3 = {
    2, // numEnemies
    btlparty_jon_jon_41_04_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_41_05_off_1[] = {
    {
        &unit_patatogemet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patatogemet, // itemDropTable
    },
    {
        &unit_patatogemet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patatogemet, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_41_05_off_1 = {
    2, // numEnemies
    btlparty_jon_jon_41_05_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_41_05_off_2[] = {
    {
        &unit_patatogemet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patatogemet, // itemDropTable
    },
    {
        &unit_patatogemet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patatogemet, // itemDropTable
    },
    {
        &unit_patatogemet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patatogemet, // itemDropTable
    },
    {
        &unit_patatogemet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 40.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patatogemet, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_41_05_off_2 = {
    4, // numEnemies
    btlparty_jon_jon_41_05_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_41_05_off_3[] = {
    {
        &unit_patatogemet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patatogemet, // itemDropTable
    },
    {
        &unit_patatogemet, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_patatogemet, // itemDropTable
    },
    {
        &unit_bubble, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bubble, // itemDropTable
    },
    {
        &unit_bubble, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 40.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bubble, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_41_05_off_3 = {
    4, // numEnemies
    btlparty_jon_jon_41_05_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_51_01_off_1[] = {
    {
        &unit_badge_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_badge_borodo, // itemDropTable
    },
    {
        &unit_badge_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_badge_borodo, // itemDropTable
    },
    {
        &unit_badge_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_badge_borodo, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_51_01_off_1 = {
    3, // numEnemies
    btlparty_jon_jon_51_01_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_51_01_off_2[] = {
    {
        &unit_badge_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_badge_borodo, // itemDropTable
    },
    {
        &unit_badge_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_badge_borodo, // itemDropTable
    },
    {
        &unit_bllizard, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bllizard, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_51_01_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_51_01_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_51_01_off_3[] = {
    {
        &unit_badge_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_badge_borodo, // itemDropTable
    },
    {
        &unit_badge_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_badge_borodo, // itemDropTable
    },
    {
        &unit_purple_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_purple_teresa, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_51_01_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_51_01_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_51_02_off_1[] = {
    {
        &unit_bllizard, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bllizard, // itemDropTable
    },
    {
        &unit_bllizard, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bllizard, // itemDropTable
    },
    {
        &unit_bllizard, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bllizard, // itemDropTable
    },
    {
        &unit_bllizard, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 40.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bllizard, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_51_02_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_51_02_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_51_02_off_2[] = {
    {
        &unit_bllizard, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bllizard, // itemDropTable
    },
    {
        &unit_purple_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_purple_teresa, // itemDropTable
    },
    {
        &unit_bllizard, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bllizard, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_51_02_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_51_02_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_51_02_off_3[] = {
    {
        &unit_bllizard, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bllizard, // itemDropTable
    },
    {
        &unit_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sinemon, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_51_02_off_3 = {
    2, // numEnemies
    btlparty_jon_jon_51_02_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_51_03_off_1[] = {
    {
        &unit_purple_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_purple_teresa, // itemDropTable
    },
    {
        &unit_purple_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_purple_teresa, // itemDropTable
    },
    {
        &unit_purple_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_purple_teresa, // itemDropTable
    },
    {
        &unit_purple_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_purple_teresa, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_51_03_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_51_03_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_51_03_off_2[] = {
    {
        &unit_purple_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_purple_teresa, // itemDropTable
    },
    {
        &unit_badge_borodo, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_badge_borodo, // itemDropTable
    },
    {
        &unit_purple_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_purple_teresa, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_51_03_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_51_03_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_51_03_off_3[] = {
    {
        &unit_purple_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_purple_teresa, // itemDropTable
    },
    {
        &unit_purple_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_purple_teresa, // itemDropTable
    },
    {
        &unit_burst_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_burst_wanwan, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_51_03_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_51_03_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_51_04_off_1[] = {
    {
        &unit_burst_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_burst_wanwan, // itemDropTable
    },
    {
        &unit_burst_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_burst_wanwan, // itemDropTable
    },
    {
        &unit_burst_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_burst_wanwan, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_51_04_off_1 = {
    3, // numEnemies
    btlparty_jon_jon_51_04_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_51_04_off_2[] = {
    {
        &unit_burst_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_burst_wanwan, // itemDropTable
    },
    {
        &unit_purple_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_purple_teresa, // itemDropTable
    },
    {
        &unit_burst_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_burst_wanwan, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_51_04_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_51_04_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_51_04_off_3[] = {
    {
        &unit_burst_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_burst_wanwan, // itemDropTable
    },
    {
        &unit_bllizard, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bllizard, // itemDropTable
    },
    {
        &unit_bllizard, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_bllizard, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_51_04_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_51_04_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_51_05_off_1[] = {
    {
        &unit_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sinemon, // itemDropTable
    },
    {
        &unit_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sinemon, // itemDropTable
    },
    {
        &unit_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sinemon, // itemDropTable
    },
    {
        &unit_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sinemon, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_51_05_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_51_05_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_51_05_off_2[] = {
    {
        &unit_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sinemon, // itemDropTable
    },
    {
        &unit_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sinemon, // itemDropTable
    },
    {
        &unit_burst_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_burst_wanwan, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_51_05_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_51_05_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_51_05_off_3[] = {
    {
        &unit_sinemon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_sinemon, // itemDropTable
    },
    {
        &unit_purple_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_purple_teresa, // itemDropTable
    },
    {
        &unit_purple_teresa, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_purple_teresa, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_51_05_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_51_05_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_61_01_off_1[] = {
    {
        &unit_hyper_jyugem, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_jyugem, // itemDropTable
    },
    {
        &unit_hyper_jyugem, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_jyugem, // itemDropTable
    },
    {
        &unit_hyper_jyugem, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_jyugem, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_61_01_off_1 = {
    3, // numEnemies
    btlparty_jon_jon_61_01_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_61_01_off_2[] = {
    {
        &unit_hyper_jyugem, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_jyugem, // itemDropTable
    },
    {
        &unit_hyper_jyugem, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_jyugem, // itemDropTable
    },
    {
        &unit_dark_keeper, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dark_keeper, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_61_01_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_61_01_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_61_01_off_3[] = {
    {
        &unit_hyper_jyugem, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_jyugem, // itemDropTable
    },
    {
        &unit_super_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_super_mahorn, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_61_01_off_3 = {
    2, // numEnemies
    btlparty_jon_jon_61_01_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_61_02_off_1[] = {
    {
        &unit_karon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_karon, // itemDropTable
    },
    {
        &unit_karon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_karon, // itemDropTable
    },
    {
        &unit_karon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_karon, // itemDropTable
    },
    {
        &unit_karon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_karon, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_61_02_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_61_02_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_61_02_off_2[] = {
    {
        &unit_karon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_karon, // itemDropTable
    },
    {
        &unit_dark_keeper, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dark_keeper, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_61_02_off_2 = {
    2, // numEnemies
    btlparty_jon_jon_61_02_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_61_02_off_3[] = {
    {
        &unit_karon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_karon, // itemDropTable
    },
    {
        &unit_ice_pakkun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ice_pakkun, // itemDropTable
    },
    {
        &unit_ice_pakkun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ice_pakkun, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_61_02_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_61_02_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_61_03_off_1[] = {
    {
        &unit_super_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_super_mahorn, // itemDropTable
    },
    {
        &unit_super_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_super_mahorn, // itemDropTable
    },
    {
        &unit_super_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_super_mahorn, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_61_03_off_1 = {
    3, // numEnemies
    btlparty_jon_jon_61_03_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_61_03_off_2[] = {
    {
        &unit_super_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_super_mahorn, // itemDropTable
    },
    {
        &unit_dark_keeper, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dark_keeper, // itemDropTable
    },
    {
        &unit_super_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_super_mahorn, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_61_03_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_61_03_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_61_03_off_3[] = {
    {
        &unit_super_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_super_mahorn, // itemDropTable
    },
    {
        &unit_karon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_karon, // itemDropTable
    },
    {
        &unit_karon, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_karon, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_61_03_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_61_03_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_61_04_off_1[] = {
    {
        &unit_ice_pakkun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ice_pakkun, // itemDropTable
    },
    {
        &unit_ice_pakkun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ice_pakkun, // itemDropTable
    },
    {
        &unit_ice_pakkun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ice_pakkun, // itemDropTable
    },
    {
        &unit_ice_pakkun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ice_pakkun, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_61_04_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_61_04_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_61_04_off_2[] = {
    {
        &unit_ice_pakkun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ice_pakkun, // itemDropTable
    },
    {
        &unit_hyper_jyugem, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_jyugem, // itemDropTable
    },
    {
        &unit_hyper_jyugem, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_jyugem, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_61_04_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_61_04_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_61_04_off_3[] = {
    {
        &unit_ice_pakkun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_ice_pakkun, // itemDropTable
    },
    {
        &unit_dark_keeper, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dark_keeper, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_61_04_off_3 = {
    2, // numEnemies
    btlparty_jon_jon_61_04_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_61_05_off_1[] = {
    {
        &unit_dark_keeper, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dark_keeper, // itemDropTable
    },
    {
        &unit_dark_keeper, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dark_keeper, // itemDropTable
    },
    {
        &unit_dark_keeper, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dark_keeper, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_61_05_off_1 = {
    3, // numEnemies
    btlparty_jon_jon_61_05_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_61_05_off_2[] = {
    {
        &unit_dark_keeper, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dark_keeper, // itemDropTable
    },
    {
        &unit_hyper_jyugem, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hyper_jyugem, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_61_05_off_2 = {
    2, // numEnemies
    btlparty_jon_jon_61_05_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_61_05_off_3[] = {
    {
        &unit_dark_keeper, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dark_keeper, // itemDropTable
    },
    {
        &unit_dark_keeper, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dark_keeper, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_61_05_off_3 = {
    2, // numEnemies
    btlparty_jon_jon_61_05_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_71_01_off_1[] = {
    {
        &unit_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn, // itemDropTable
    },
    {
        &unit_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn, // itemDropTable
    },
    {
        &unit_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_71_01_off_1 = {
    3, // numEnemies
    btlparty_jon_jon_71_01_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_71_01_off_2[] = {
    {
        &unit_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn, // itemDropTable
    },
    {
        &unit_togenoko_ace, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_togenoko_ace, // itemDropTable
    },
    {
        &unit_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_71_01_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_71_01_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_71_01_off_3[] = {
    {
        &unit_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn, // itemDropTable
    },
    {
        &unit_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_wanwan, // itemDropTable
    },
    {
        &unit_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_wanwan, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_71_01_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_71_01_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_71_02_off_1[] = {
    {
        &unit_togenoko_ace, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_togenoko_ace, // itemDropTable
    },
    {
        &unit_togenoko_ace, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_togenoko_ace, // itemDropTable
    },
    {
        &unit_togenoko_ace, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_togenoko_ace, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_71_02_off_1 = {
    3, // numEnemies
    btlparty_jon_jon_71_02_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_71_02_off_2[] = {
    {
        &unit_togenoko_ace, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_togenoko_ace, // itemDropTable
    },
    {
        &unit_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_wanwan, // itemDropTable
    },
    {
        &unit_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_wanwan, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_71_02_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_71_02_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_71_02_off_3[] = {
    {
        &unit_togenoko_ace, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_togenoko_ace, // itemDropTable
    },
    {
        &unit_togenoko_ace, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_togenoko_ace, // itemDropTable
    },
    {
        &unit_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_71_02_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_71_02_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default2, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_71_03_off_1[] = {
    {
        &unit_phantom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {10.0f, 0.0f, -20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_phantom, // itemDropTable
    },
    {
        &unit_phantom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_phantom, // itemDropTable
    },
    {
        &unit_phantom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_phantom, // itemDropTable
    },
    {
        &unit_phantom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_phantom, // itemDropTable
    },
    {
        &unit_phantom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {170.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_phantom, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_71_03_off_1 = {
    5, // numEnemies
    btlparty_jon_jon_71_03_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_71_03_off_2[] = {
    {
        &unit_phantom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_phantom, // itemDropTable
    },
    {
        &unit_phantom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_phantom, // itemDropTable
    },
    {
        &unit_phantom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_phantom, // itemDropTable
    },
    {
        &unit_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_71_03_off_2 = {
    4, // numEnemies
    btlparty_jon_jon_71_03_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_71_03_off_3[] = {
    {
        &unit_phantom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_phantom, // itemDropTable
    },
    {
        &unit_basabasa_chururu, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 130.0f, 0.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_chururu, // itemDropTable
    },
    {
        &unit_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_wanwan, // itemDropTable
    },
    {
        &unit_togenoko_ace, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_togenoko_ace, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_71_03_off_3 = {
    4, // numEnemies
    btlparty_jon_jon_71_03_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_71_04_off_1[] = {
    {
        &unit_basabasa_chururu, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 130.0f, -10.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_chururu, // itemDropTable
    },
    {
        &unit_basabasa_chururu, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 130.0f, 0.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_chururu, // itemDropTable
    },
    {
        &unit_basabasa_chururu, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 130.0f, 10.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_chururu, // itemDropTable
    },
    {
        &unit_basabasa_chururu, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 130.0f, 20.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_chururu, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_71_04_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_71_04_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_71_04_off_2[] = {
    {
        &unit_basabasa_chururu, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 130.0f, -10.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_chururu, // itemDropTable
    },
    {
        &unit_basabasa_chururu, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 130.0f, 0.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_chururu, // itemDropTable
    },
    {
        &unit_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn, // itemDropTable
    },
    {
        &unit_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_71_04_off_2 = {
    4, // numEnemies
    btlparty_jon_jon_71_04_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_71_04_off_3[] = {
    {
        &unit_basabasa_chururu, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 130.0f, -10.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_chururu, // itemDropTable
    },
    {
        &unit_togenoko_ace, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_togenoko_ace, // itemDropTable
    },
    {
        &unit_basabasa_chururu, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 130.0f, 10.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_chururu, // itemDropTable
    },
    {
        &unit_togenoko_ace, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_togenoko_ace, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_71_04_off_3 = {
    4, // numEnemies
    btlparty_jon_jon_71_04_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default2, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_71_05_off_1[] = {
    {
        &unit_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_wanwan, // itemDropTable
    },
    {
        &unit_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_wanwan, // itemDropTable
    },
    {
        &unit_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_wanwan, // itemDropTable
    },
    {
        &unit_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_wanwan, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_71_05_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_71_05_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_71_05_off_2[] = {
    {
        &unit_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_wanwan, // itemDropTable
    },
    {
        &unit_togenoko_ace, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_togenoko_ace, // itemDropTable
    },
    {
        &unit_togenoko_ace, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_togenoko_ace, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_71_05_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_71_05_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_71_05_off_3[] = {
    {
        &unit_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_wanwan, // itemDropTable
    },
    {
        &unit_wanwan, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_wanwan, // itemDropTable
    },
    {
        &unit_mahorn, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_71_05_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_71_05_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_81_01_off_1[] = {
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_81_01_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_81_01_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_81_01_off_2[] = {
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_churantalar, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_churantalar, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_churantalar, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 40.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_churantalar, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_81_01_off_2 = {
    4, // numEnemies
    btlparty_jon_jon_81_01_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_81_01_off_3[] = {
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_pakkun_flower, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_pakkun_flower, // itemDropTable
    },
    {
        &unit_yamitogedaruma, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yamitogedaruma, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_81_01_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_81_01_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_81_02_off_1[] = {
    {
        &unit_yamitogedaruma, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yamitogedaruma, // itemDropTable
    },
    {
        &unit_yamitogedaruma, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yamitogedaruma, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_81_02_off_1 = {
    2, // numEnemies
    btlparty_jon_jon_81_02_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default4, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_81_02_off_2[] = {
    {
        &unit_yamitogedaruma, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yamitogedaruma, // itemDropTable
    },
    {
        &unit_churantalar, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_churantalar, // itemDropTable
    },
    {
        &unit_churantalar, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_churantalar, // itemDropTable
    },
    {
        &unit_churantalar, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 40.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_churantalar, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_81_02_off_2 = {
    4, // numEnemies
    btlparty_jon_jon_81_02_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default4, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_81_02_off_3[] = {
    {
        &unit_yamitogedaruma, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yamitogedaruma, // itemDropTable
    },
    {
        &unit_yamitogedaruma, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yamitogedaruma, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_81_02_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_81_02_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default4, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_81_03_off_1[] = {
    {
        &unit_churantalar, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_churantalar, // itemDropTable
    },
    {
        &unit_churantalar, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_churantalar, // itemDropTable
    },
    {
        &unit_churantalar, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_churantalar, // itemDropTable
    },
    {
        &unit_churantalar, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 40.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_churantalar, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_81_03_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_81_03_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_81_03_off_2[] = {
    {
        &unit_churantalar, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_churantalar, // itemDropTable
    },
    {
        &unit_pakkun_flower, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_pakkun_flower, // itemDropTable
    },
    {
        &unit_churantalar, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_churantalar, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_81_03_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_81_03_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_81_03_off_3[] = {
    {
        &unit_churantalar, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_churantalar, // itemDropTable
    },
    {
        &unit_churantalar, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_churantalar, // itemDropTable
    },
    {
        &unit_yamitogedaruma, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yamitogedaruma, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_81_03_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_81_03_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_81_04_off_1[] = {
    {
        &unit_pakkun_flower, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_pakkun_flower, // itemDropTable
    },
    {
        &unit_pakkun_flower, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_pakkun_flower, // itemDropTable
    },
    {
        &unit_pakkun_flower, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_pakkun_flower, // itemDropTable
    },
    {
        &unit_pakkun_flower, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_pakkun_flower, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_81_04_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_81_04_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default5, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_81_04_off_2[] = {
    {
        &unit_pakkun_flower, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_pakkun_flower, // itemDropTable
    },
    {
        &unit_yamitogedaruma, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_yamitogedaruma, // itemDropTable
    },
    {
        &unit_pakkun_flower, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_pakkun_flower, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_81_04_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_81_04_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default5, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_81_04_off_3[] = {
    {
        &unit_pakkun_flower, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_pakkun_flower, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_81_04_off_3 = {
    4, // numEnemies
    btlparty_jon_jon_81_04_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default, // hpDropTable
    battle_flower_drop_param_default5, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_81_05_off_1[] = {
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_81_05_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_81_05_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_81_05_off_2[] = {
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_81_05_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_81_05_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_81_05_off_3[] = {
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {10.0f, 0.0f, -20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
    {
        &unit_hennya, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {170.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_hennya, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_81_05_off_3 = {
    5, // numEnemies
    btlparty_jon_jon_81_05_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_91_01_off_1[] = {
    {
        &unit_mahorn_custom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {10.0f, 0.0f, -20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn_custom, // itemDropTable
    },
    {
        &unit_mahorn_custom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn_custom, // itemDropTable
    },
    {
        &unit_mahorn_custom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn_custom, // itemDropTable
    },
    {
        &unit_mahorn_custom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn_custom, // itemDropTable
    },
    {
        &unit_mahorn_custom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {170.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn_custom, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_91_01_off_1 = {
    5, // numEnemies
    btlparty_jon_jon_91_01_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default4, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_91_01_off_2[] = {
    {
        &unit_mahorn_custom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn_custom, // itemDropTable
    },
    {
        &unit_dokugassun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dokugassun, // itemDropTable
    },
    {
        &unit_dokugassun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dokugassun, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_91_01_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_91_01_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default4, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_91_01_off_3[] = {
    {
        &unit_mahorn_custom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn_custom, // itemDropTable
    },
    {
        &unit_mahorn_custom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn_custom, // itemDropTable
    },
    {
        &unit_basabasa_green, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 130.0f, 10.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_green, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_91_01_off_3 = {
    3, // numEnemies
    btlparty_jon_jon_91_01_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default4, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_91_02_off_1[] = {
    {
        &unit_dokugassun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dokugassun, // itemDropTable
    },
    {
        &unit_dokugassun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dokugassun, // itemDropTable
    },
    {
        &unit_dokugassun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dokugassun, // itemDropTable
    },
    {
        &unit_dokugassun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 40.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dokugassun, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_91_02_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_91_02_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_91_02_off_2[] = {
    {
        &unit_dokugassun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dokugassun, // itemDropTable
    },
    {
        &unit_dokugassun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dokugassun, // itemDropTable
    },
    {
        &unit_dokugassun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dokugassun, // itemDropTable
    },
    {
        &unit_giant_bomb, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_giant_bomb, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_91_02_off_2 = {
    4, // numEnemies
    btlparty_jon_jon_91_02_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_91_02_off_3[] = {
    {
        &unit_dokugassun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 40.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dokugassun, // itemDropTable
    },
    {
        &unit_basabasa_green, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 130.0f, 0.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_green, // itemDropTable
    },
    {
        &unit_dokugassun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dokugassun, // itemDropTable
    },
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_91_02_off_3 = {
    4, // numEnemies
    btlparty_jon_jon_91_02_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default3, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_91_03_off_1[] = {
    {
        &unit_giant_bomb, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_giant_bomb, // itemDropTable
    },
    {
        &unit_giant_bomb, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_giant_bomb, // itemDropTable
    },
    {
        &unit_giant_bomb, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_giant_bomb, // itemDropTable
    },
    {
        &unit_giant_bomb, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_giant_bomb, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_91_03_off_1 = {
    4, // numEnemies
    btlparty_jon_jon_91_03_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default5, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_91_03_off_2[] = {
    {
        &unit_giant_bomb, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_giant_bomb, // itemDropTable
    },
    {
        &unit_giant_bomb, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_giant_bomb, // itemDropTable
    },
    {
        &unit_mahorn_custom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn_custom, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_91_03_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_91_03_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default5, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_91_03_off_3[] = {
    {
        &unit_giant_bomb, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_giant_bomb, // itemDropTable
    },
    {
        &unit_giant_bomb, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_giant_bomb, // itemDropTable
    },
    {
        &unit_giant_bomb, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_giant_bomb, // itemDropTable
    },
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_91_03_off_3 = {
    4, // numEnemies
    btlparty_jon_jon_91_03_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default5, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_91_04_off_1[] = {
    {
        &unit_basabasa_green, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {10.0f, 130.0f, -20.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_green, // itemDropTable
    },
    {
        &unit_basabasa_green, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 130.0f, -10.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_green, // itemDropTable
    },
    {
        &unit_basabasa_green, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 130.0f, 0.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_green, // itemDropTable
    },
    {
        &unit_basabasa_green, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 130.0f, 10.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_green, // itemDropTable
    },
    {
        &unit_basabasa_green, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {170.0f, 130.0f, 20.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_green, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_91_04_off_1 = {
    5, // numEnemies
    btlparty_jon_jon_91_04_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_91_04_off_2[] = {
    {
        &unit_basabasa_green, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 130.0f, -10.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_green, // itemDropTable
    },
    {
        &unit_dokugassun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 40.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dokugassun, // itemDropTable
    },
    {
        &unit_dokugassun, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 40.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_dokugassun, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_91_04_off_2 = {
    3, // numEnemies
    btlparty_jon_jon_91_04_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_91_04_off_3[] = {
    {
        &unit_basabasa_green, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {30.0f, 130.0f, -10.0f}, // position
        0, // hitOffsetX
        {1, 0, 0, 0}, // unitWork
        battle_item_basabasa_green, // itemDropTable
    },
    {
        &unit_mahorn_custom, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {70.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_mahorn_custom, // itemDropTable
    },
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {110.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {150.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_91_04_off_3 = {
    4, // numEnemies
    btlparty_jon_jon_91_04_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default4, // hpDropTable
    battle_flower_drop_param_default, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_91_05_off_1[] = {
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {10.0f, 0.0f, -20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {170.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_91_05_off_1 = {
    5, // numEnemies
    btlparty_jon_jon_91_05_off_1, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default5, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_91_05_off_2[] = {
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {10.0f, 0.0f, -20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {170.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_91_05_off_2 = {
    5, // numEnemies
    btlparty_jon_jon_91_05_off_2, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default5, // fpDropTable
    5, // reserved_1C
};

BattleUnitSetup btlparty_jon_jon_91_05_off_3[] = {
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {10.0f, 0.0f, -20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {50.0f, 0.0f, -10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {90.0f, 0.0f, 0.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {130.0f, 0.0f, 10.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
    {
        &unit_twinkling_pansy, // unitKindParams
        1, // alliance
        {0}, // pad_05
        BATTLE_PHASE_ENEMY, // attackPhase
        {170.0f, 0.0f, 20.0f}, // position
        0, // hitOffsetX
        {0}, // unitWork
        battle_item_twinkling_pansy, // itemDropTable
    },
};

BattleGroupSetup btlgrp_jon_jon_91_05_off_3 = {
    5, // numEnemies
    btlparty_jon_jon_91_05_off_3, // enemyData
    20, // heldItemWeight
    20, // randomItemWeight
    60, // noItemWeight
    battle_heart_drop_param_default3, // hpDropTable
    battle_flower_drop_param_default5, // fpDropTable
    5, // reserved_1C
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_test1_off[] = {
    {50, &btlgrp_jon_jon_01_01_off_1, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_01_off[] = {
    {10, &btlgrp_jon_jon_01_01_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_01_01_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_01_01_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_02_off[] = {
    {10, &btlgrp_jon_jon_01_02_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_01_02_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_01_02_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_03_off[] = {
    {10, &btlgrp_jon_jon_01_03_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_01_03_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_01_03_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_04_off[] = {
    {10, &btlgrp_jon_jon_01_04_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_01_04_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_01_04_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_05_off[] = {
    {10, &btlgrp_jon_jon_01_05_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_01_05_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_01_05_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_11_off[] = {
    {10, &btlgrp_jon_jon_11_01_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_11_01_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_11_01_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_12_off[] = {
    {10, &btlgrp_jon_jon_11_02_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_11_02_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_11_02_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_13_off[] = {
    {10, &btlgrp_jon_jon_11_03_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_11_03_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_11_03_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_14_off[] = {
    {10, &btlgrp_jon_jon_11_04_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_11_04_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_11_04_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_15_off[] = {
    {10, &btlgrp_jon_jon_11_05_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_11_05_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_11_05_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_21_off[] = {
    {10, &btlgrp_jon_jon_21_01_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_21_01_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_21_01_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_22_off[] = {
    {10, &btlgrp_jon_jon_21_02_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_21_02_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_21_02_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_23_off[] = {
    {10, &btlgrp_jon_jon_21_03_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_21_03_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_21_03_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_24_off[] = {
    {10, &btlgrp_jon_jon_21_04_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_21_04_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_21_04_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_25_off[] = {
    {10, &btlgrp_jon_jon_21_05_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_21_05_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_21_05_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_31_off[] = {
    {10, &btlgrp_jon_jon_31_01_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_31_01_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_31_01_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_32_off[] = {
    {10, &btlgrp_jon_jon_31_02_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_31_02_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_31_02_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_33_off[] = {
    {10, &btlgrp_jon_jon_31_03_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_31_03_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_31_03_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_34_off[] = {
    {10, &btlgrp_jon_jon_31_04_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_31_04_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_31_04_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_35_off[] = {
    {10, &btlgrp_jon_jon_31_05_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_31_05_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_31_05_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_41_off[] = {
    {10, &btlgrp_jon_jon_41_01_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_41_01_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_41_01_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_42_off[] = {
    {10, &btlgrp_jon_jon_41_02_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_41_02_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_41_02_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_43_off[] = {
    {10, &btlgrp_jon_jon_41_03_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_41_03_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_41_03_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_44_off[] = {
    {10, &btlgrp_jon_jon_41_04_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_41_04_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_41_04_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_45_off[] = {
    {10, &btlgrp_jon_jon_41_05_off_1, jon_btlstage_data},
    {10, &btlgrp_jon_jon_41_05_off_2, jon_btlstage_data},
    {10, &btlgrp_jon_jon_41_05_off_3, jon_btlstage_data},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_51_off[] = {
    {10, &btlgrp_jon_jon_51_01_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_51_01_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_51_01_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_52_off[] = {
    {10, &btlgrp_jon_jon_51_02_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_51_02_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_51_02_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_53_off[] = {
    {10, &btlgrp_jon_jon_51_03_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_51_03_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_51_03_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_54_off[] = {
    {10, &btlgrp_jon_jon_51_04_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_51_04_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_51_04_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_55_off[] = {
    {10, &btlgrp_jon_jon_51_05_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_51_05_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_51_05_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_61_off[] = {
    {10, &btlgrp_jon_jon_61_01_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_61_01_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_61_01_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_62_off[] = {
    {10, &btlgrp_jon_jon_61_02_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_61_02_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_61_02_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_63_off[] = {
    {10, &btlgrp_jon_jon_61_03_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_61_03_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_61_03_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_64_off[] = {
    {10, &btlgrp_jon_jon_61_04_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_61_04_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_61_04_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_65_off[] = {
    {10, &btlgrp_jon_jon_61_05_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_61_05_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_61_05_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_71_off[] = {
    {10, &btlgrp_jon_jon_71_01_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_71_01_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_71_01_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_72_off[] = {
    {10, &btlgrp_jon_jon_71_02_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_71_02_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_71_02_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_73_off[] = {
    {10, &btlgrp_jon_jon_71_03_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_71_03_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_71_03_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_74_off[] = {
    {10, &btlgrp_jon_jon_71_04_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_71_04_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_71_04_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_75_off[] = {
    {10, &btlgrp_jon_jon_71_05_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_71_05_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_71_05_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_81_off[] = {
    {10, &btlgrp_jon_jon_81_01_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_81_01_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_81_01_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_82_off[] = {
    {10, &btlgrp_jon_jon_81_02_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_81_02_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_81_02_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_83_off[] = {
    {10, &btlgrp_jon_jon_81_03_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_81_03_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_81_03_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_84_off[] = {
    {10, &btlgrp_jon_jon_81_04_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_81_04_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_81_04_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_85_off[] = {
    {10, &btlgrp_jon_jon_81_05_off_1, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_81_05_off_2, &jon_btlstage_data[1]},
    {10, &btlgrp_jon_jon_81_05_off_3, &jon_btlstage_data[1]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_91_off[] = {
    {10, &btlgrp_jon_jon_91_01_off_1, &jon_btlstage_data[2]},
    {10, &btlgrp_jon_jon_91_01_off_2, &jon_btlstage_data[2]},
    {10, &btlgrp_jon_jon_91_01_off_3, &jon_btlstage_data[2]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_92_off[] = {
    {10, &btlgrp_jon_jon_91_02_off_1, &jon_btlstage_data[2]},
    {10, &btlgrp_jon_jon_91_02_off_2, &jon_btlstage_data[2]},
    {10, &btlgrp_jon_jon_91_02_off_3, &jon_btlstage_data[2]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_93_off[] = {
    {10, &btlgrp_jon_jon_91_03_off_1, &jon_btlstage_data[2]},
    {10, &btlgrp_jon_jon_91_03_off_2, &jon_btlstage_data[2]},
    {10, &btlgrp_jon_jon_91_03_off_3, &jon_btlstage_data[2]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_94_off[] = {
    {10, &btlgrp_jon_jon_91_04_off_1, &jon_btlstage_data[2]},
    {10, &btlgrp_jon_jon_91_04_off_2, &jon_btlstage_data[2]},
    {10, &btlgrp_jon_jon_91_04_off_3, &jon_btlstage_data[2]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_95_off[] = {
    {10, &btlgrp_jon_jon_91_05_off_1, &jon_btlstage_data[2]},
    {10, &btlgrp_jon_jon_91_05_off_2, &jon_btlstage_data[2]},
    {10, &btlgrp_jon_jon_91_05_off_3, &jon_btlstage_data[2]},
    {0},
};

NpcBattleSelect btlgrpsel_jon_btlno_jon_100_zonbaba_off[] = {
    {10, &btlgrp_jon_jon_100_01_off_1, &jon_btlstage_data[3]},
    {0},
};

NpcSetupBattleInfo btlsetup_jon_tbl[] = {
    {
        "マップstg_00_3", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_test1_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ヤミクリボー", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_01_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{5, 5}, {0}, {0}, {0}, {5, 5}, {5, 5}, {0}, {0}, {5, 5}, {0}, {10, 10}, {0}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ヒンニャー", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_02_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{5, 5}, {0}, {0}, {0}, {5, 5}, {5, 5}, {0}, {0}, {5, 5}, {0}, {5, 5}, {0}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ハンニャー", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_03_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{5, 5}, {0}, {0}, {0}, {5, 5}, {5, 5}, {0}, {0}, {5, 5}, {0}, {5, 5}, {0}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ホネノコ", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_04_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{5, 5}, {0}, {0}, {0}, {10, 10}, {5, 5}, {0}, {0}, {5, 5}, {0}, {5, 5}, {0}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "チョロボン", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_05_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{5, 5}, {0}, {0}, {0}, {5, 5}, {5, 5}, {0}, {0}, {5, 5}, {0}, {5, 5}, {0}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ヤミパタクリ", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_11_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{5, 5}, {5, 5}, {0}, {0}, {5, 5}, {5, 5}, {0}, {0}, {5, 5}, {0}, {10, 10}, {0}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "モノクロシンエモン", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_12_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{5, 5}, {5, 5}, {0}, {0}, {5, 5}, {5, 5}, {0}, {0}, {5, 5}, {0}, {5, 5}, {0}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "サンボ", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_13_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{5, 5}, {5, 5}, {0}, {0}, {5, 5}, {5, 5}, {0}, {0}, {5, 5}, {0}, {5, 5}, {0}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "モノクロクロクモーン", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_14_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{5, 5}, {5, 5}, {0}, {0}, {5, 5}, {5, 5}, {0}, {0}, {5, 5}, {0}, {5, 5}, {0}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "パイダース", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_15_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{5, 5}, {5, 5}, {0}, {0}, {5, 5}, {5, 5}, {0}, {0}, {5, 5}, {0}, {5, 5}, {0}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ヤミトゲクリ", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_21_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{5, 5}, {5, 5}, {0}, {0}, {5, 5}, {5, 5}, {0}, {0}, {5, 5}, {0}, {10, 10}, {0}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ボロドー", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_22_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{5, 5}, {5, 5}, {0}, {0}, {5, 5}, {5, 5}, {0}, {0}, {5, 5}, {0}, {5, 5}, {0}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ジュゲム", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_23_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{5, 5}, {5, 5}, {0}, {0}, {5, 5}, {5, 5}, {0}, {0}, {5, 5}, {0}, {5, 5}, {0}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ボムへい", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_24_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{5, 5}, {5, 5}, {0}, {0}, {5, 5}, {5, 5}, {0}, {0}, {5, 5}, {0}, {5, 5}, {0}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "テレサ", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_25_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{5, 5}, {5, 5}, {10, 10}, {0}, {5, 5}, {5, 5}, {0}, {0}, {5, 5}, {0}, {5, 5}, {0}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ヤミノコノコ", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_31_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{4, 4}, {4, 4}, {4, 4}, {0}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {10, 10}, {0}, {4, 4}, {4, 4}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ハイパーシンエモン", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_32_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{4, 4}, {4, 4}, {4, 4}, {0}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {0}, {4, 4}, {4, 4}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "パタメット", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_33_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{4, 4}, {4, 4}, {4, 4}, {0}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {0}, {4, 4}, {4, 4}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ウラノコ", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_34_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{4, 4}, {4, 4}, {4, 4}, {0}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {10, 10}, {0}, {4, 4}, {4, 4}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "フラワーチョロボン", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_35_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{4, 4}, {4, 4}, {4, 4}, {0}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {0}, {4, 4}, {4, 4}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ヤミパタパタ", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_41_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{4, 4}, {4, 4}, {4, 4}, {0}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {10, 10}, {0}, {4, 4}, {4, 4}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ヘビーボム", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_42_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{4, 4}, {4, 4}, {4, 4}, {0}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {10, 10}, {4, 4}, {4, 4}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "バブル", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_43_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{4, 4}, {4, 4}, {4, 4}, {0}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {0}, {4, 4}, {4, 4}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "サンボマミー", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_44_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{4, 4}, {4, 4}, {4, 4}, {0}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {0}, {4, 4}, {4, 4}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "パタトゲメット", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_45_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{4, 4}, {4, 4}, {4, 4}, {0}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {4, 4}, {0}, {4, 4}, {4, 4}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "バッジボロドー", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_51_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ブリザード", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_52_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "パープルテレサ", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_53_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "バーストワンワン", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_54_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "シンエモン", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_55_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ハイパージュゲム", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_61_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "カロン", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_62_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "スーパーマホーン", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_63_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "アイスパックン", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_64_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ダークキーパー", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_65_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "マホーン", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_71_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "トゲノコエース", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_72_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ファントム", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_73_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "バサバサチュルル", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_74_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ワンワン", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_75_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ヘンニャー", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_81_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ヤミトゲダルマー", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_82_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "チュランタラー", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_83_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "パックンフラワー", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_84_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ヘンニャー", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_85_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "マホーンカスタム", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_91_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ドクガッスン", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_92_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ジャイアントボム", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_93_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "バサバサグリーン", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_94_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "きらめくパンジーさん", // name
        NULL, 0, // mapName..fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_95_off, // select
        NPC_BATTLE_NO_BUMP_ATTACK, // battleFlags
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_ZAKO_BATTLE1", // bgmName
    },
    {
        "ゾンババ", // name
        "jon_06", // mapName
        0, // fixedItem
        -1, // swFlag
        NULL, // altSelect
        btlgrpsel_jon_btlno_jon_100_zonbaba_off, // select
#if VERSION <= VERSION_DEMO_US
        NPC_BATTLE_MAX_COUNT | NPC_BATTLE_MARIO_PAUSE3_VOICE, // battleFlags
#else
        NPC_BATTLE_MAX_COUNT | NPC_BATTLE_NO_PLAYER_ENTRY | NPC_BATTLE_MARIO_PAUSE3_VOICE, // battleFlags
#endif
        0, // randomMode
        {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 1}}, // randomRanges
        "BGM_BOSS_STG1_GONBABA1", // bgmName
    },
    {0},
};

NpcTerritoryInfo btl_jon_setup_no_tbl[] = {
    {"BTLNO_JON_TEST1", 0},
    {"BTLNO_JON_01", 1},
    {"BTLNO_JON_02", 2},
    {"BTLNO_JON_03", 3},
    {"BTLNO_JON_04", 4},
    {"BTLNO_JON_05", 5},
    {"BTLNO_JON_11", 6},
    {"BTLNO_JON_12", 7},
    {"BTLNO_JON_13", 8},
    {"BTLNO_JON_14", 9},
    {"BTLNO_JON_15", 10},
    {"BTLNO_JON_21", 11},
    {"BTLNO_JON_22", 12},
    {"BTLNO_JON_23", 13},
    {"BTLNO_JON_24", 14},
    {"BTLNO_JON_25", 15},
    {"BTLNO_JON_31", 16},
    {"BTLNO_JON_32", 17},
    {"BTLNO_JON_33", 18},
    {"BTLNO_JON_34", 19},
    {"BTLNO_JON_35", 20},
    {"BTLNO_JON_41", 21},
    {"BTLNO_JON_42", 22},
    {"BTLNO_JON_43", 23},
    {"BTLNO_JON_44", 24},
    {"BTLNO_JON_45", 25},
    {"BTLNO_JON_51", 26},
    {"BTLNO_JON_52", 27},
    {"BTLNO_JON_53", 28},
    {"BTLNO_JON_54", 29},
    {"BTLNO_JON_55", 30},
    {"BTLNO_JON_61", 31},
    {"BTLNO_JON_62", 32},
    {"BTLNO_JON_63", 33},
    {"BTLNO_JON_64", 34},
    {"BTLNO_JON_65", 35},
    {"BTLNO_JON_71", 36},
    {"BTLNO_JON_72", 37},
    {"BTLNO_JON_73", 38},
    {"BTLNO_JON_74", 39},
    {"BTLNO_JON_75", 40},
    {"BTLNO_JON_81", 41},
    {"BTLNO_JON_82", 42},
    {"BTLNO_JON_83", 43},
    {"BTLNO_JON_84", 44},
    {"BTLNO_JON_85", 45},
    {"BTLNO_JON_91", 46},
    {"BTLNO_JON_92", 47},
    {"BTLNO_JON_93", 48},
    {"BTLNO_JON_94", 49},
    {"BTLNO_JON_95", 50},
    {"BTLNO_JON_100_ZONBABA", 51},
    {0},
};
