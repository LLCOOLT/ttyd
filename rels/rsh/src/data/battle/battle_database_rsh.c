#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle_stage_object.h"
#include "battle/battle.h"

USER_FUNC(_set_destroy_flag);
USER_FUNC(_set_offset);
extern s32 battle_heart_drop_param_default[];
extern s32 battle_item_moamoa[];
extern s32 unit_boss_moamoa[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_battle_database_rsh_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_rsh_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_rsh___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_rsh___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_rsh_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_rsh___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_rsh_one_381[1];
__declspec(section ".data") u64 fd_battle_database_rsh_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_rsh_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_rsh___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_rsh___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_rsh_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_rsh___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_rsh_one_364[1];
s32 rsh_btlobject_data[42];
s32 rsh_btlstage_data[109];
__declspec(section ".data") s32 btlparty_rsh_rsh_06_01_off_1[12];
__declspec(section ".data") s32 btlgrp_rsh_rsh_06_01_off_1[8];
__declspec(section ".data") s32 btlgrpsel_rsh_btlno_rsh_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_rsh_btlno_rsh_06_01_off[6];
s32 btlsetup_rsh_tbl[51];
__declspec(section ".data") s32 btl_rsh_setup_no_tbl[6];
s32 bgset_rsh_bg_event[30];

__declspec(section ".data") u64 fd_battle_database_rsh_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_rsh_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_rsh___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_rsh___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_rsh_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_rsh___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_rsh_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_rsh_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_rsh_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_rsh___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_rsh___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_rsh_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_rsh___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_rsh_one_364[] = {
    1065353216,
};

s32 rsh_btlobject_data[] = {
    (s32)"r_mae", 131073, 1126825984, 0, -1035468800, 3932160, (s32)"r_oku", 131073,
    1126825984, -998637568, -1035468800, 171048960, (s32)"l_mae", 131073, -1020657664, 0,
    -1035468800, 338165760, (s32)"l_oku", 131073, -1020657664, -998637568, -1035468800, 505282560,
    (s32)"iwayama_1", 131074, 0, 0, 0, 3932160, (s32)"iwayama_2", 131074,
    0, 0, 0, 3932160, (s32)"C", 131075, 0, 0,
    0, 3932160,
};

s32 rsh_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_06_0", 7, (s32)rsh_btlobject_data, 0, 0, 0, 0,
    1677721602, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 34603104, 536870912, 1704706,
    0, 0, 2047, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 100, 0, 0, 0, 0, 0, 0,
    1677721602, 0, 0, (s32)weaponGetPowerDefault, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 34603104, 536870912, 1704706,
    0, 0, 2047, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 100, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)bgset_rsh_bg_event, 0, 0,
};

__declspec(section ".data") s32 btlparty_rsh_rsh_06_01_off_1[] = {
    (s32)unit_boss_moamoa, 16777216, 67108868, 1116471296, -1046478848, 0, 0, 0,
    0, 0, 0, (s32)battle_item_moamoa,
};

__declspec(section ".data") s32 btlgrp_rsh_rsh_06_01_off_1[] = {
    1, (s32)btlparty_rsh_rsh_06_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

__declspec(section ".data") s32 btlgrpsel_rsh_btlno_rsh_test1_off[] = {
    50, (s32)btlgrp_rsh_rsh_06_01_off_1, (s32)rsh_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_rsh_btlno_rsh_06_01_off[] = {
    50, (s32)btlgrp_rsh_rsh_06_01_off_1, (s32)rsh_btlstage_data, 0, 0, 0,
};

s32 btlsetup_rsh_tbl[] = {
    (s32)/*"マップstg_06_0"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x36\x5F\x30", 0, 0, -1, 0, (s32)btlgrpsel_rsh_btlno_rsh_test1_off, 0, 0,
    50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"rsh_06 もあもあ"*/"\x72\x73\x68\x5F\x30\x36\x20\x82\xE0\x82\xA0\x82\xE0\x82\xA0", 0, 0, -1, 0, (s32)btlgrpsel_rsh_btlno_rsh_06_01_off, 536870928,
    6, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_BOSS_STG6_GREAT_MOAMOA1", 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

__declspec(section ".data") s32 btl_rsh_setup_no_tbl[] = {
    (s32)"BTLNO_RSH_TEST1", 0, (s32)"BTLNO_RSH_06_01", 1, 0, 0,
};

EVT_BEGIN(bgset_rsh_bg_event)
    CALL(_set_destroy_flag)
    SET_VALUE(LW(0), 0)
    SET_VALUE(LW(1), 200)
    LABEL(0)
    CALL(_set_offset, STRING("iwayama_1"), LW(0), 400, -300, 800)
    CALL(_set_offset, STRING("iwayama_2"), LW(1), 400, -400, 800)
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

USER_FUNC(_set_offset) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 outVar = args[1];
    s32 step = evtGetValue(event, outVar);
    s32 total = evtGetValue(event, args[2]);
    s32 base = evtGetValue(event, args[3]);
    s32 amp = evtGetValue(event, args[4]);
    BattleStageObject* obj = BattleSearchObjectPtr(name);

    obj->positionOffset.x = base + amp * step / total;
    step--;
    if (step < 0) {
        step = total;
    }
    evtSetValue(event, outVar, step);
    return EVT_RETURN_DONE;
}
USER_FUNC(_set_destroy_flag) {
    _battleWorkPointer->field_180DC |= 8;
    return EVT_RETURN_DONE;
}
