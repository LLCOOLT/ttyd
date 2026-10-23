#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "party/party_bomhei.h"
#include "party/party_chuchu.h"
#include "party/party_cloud.h"
#include "party/party_kuribo.h"
#include "party/party_nokonoko.h"
#include "party/party_move.h"
#include "party/party_yoshi.h"

#ifdef VERSION_G8ME01
// US has no local duplicates of these: use the global functions
#define bomhei_init_800BFBB0 bomhei_init
#define kuribo_init_800C23B4 kuribo_init
#define vivian_init_801809C0 vivian_init
#endif

extern s32 bomhei_init_800BFBB0[];
extern s32 kuribo_init_800C23B4[];
extern s32 vivian_init_801809C0[];
extern s32 vivian_move[];
extern s32 vivian_use[];


s32 partyDataTbl[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)"c_pkr", (s32)kuribo_init_800C23B4, (s32)partyMoveWalk, (s32)kuribo_use, (s32)kuribo_use_post, (s32)kuribo_bye,
    0, 0, 0, 0, (s32)"c_pnk", (s32)nokonoko_init, (s32)nokonoko_move, (s32)nokonoko_use,
    (s32)nokonoko_use_post, (s32)nokonoko_bye, 0, 0, 0, 0, (s32)"c_bomt_n", (s32)bomhei_init_800BFBB0,
    (s32)partyMoveWalk, (s32)bomhei_use, (s32)bomhei_use_post, (s32)bomhei_bye, 0, 0, 0, (s32)bomhei_exit,
    (s32)"c_babyyoshi", (s32)yoshi_init, (s32)partyMoveWalk, (s32)yoshi_use, 0, (s32)yoshi_bye, 0, 0,
    0, (s32)yoshi_exit, (s32)"c_windy", (s32)cloud_init, (s32)cloud_move, (s32)cloud_use, 0, (s32)kuribo_bye,
    0, 0, 0, (s32)cloud_exit, (s32)"c_vivian", (s32)vivian_init_801809C0, (s32)vivian_move, (s32)vivian_use,
    0, (s32)kuribo_bye, 0, 0, 0, 0, (s32)"c_tyutyu", (s32)chuchu_init,
    (s32)chuchu_move, (s32)chuchu_use, 0, (s32)kuribo_bye, 0, 0, 0, (s32)chuchu_exit,
    (s32)"c_babyyoshi", (s32)kuribo_init_800C23B4, (s32)partyMoveWalk, (s32)kuribo_use, 0, (s32)kuribo_bye, 0, 0,
    0, 0, (s32)"c_marco", (s32)kuribo_init_800C23B4, (s32)partyMoveWalk, (s32)kuribo_use, 0, (s32)kuribo_bye,
    0, 0, 0, 0, (s32)"c_pguide", (s32)kuribo_init_800C23B4, (s32)partyMoveWalk, (s32)kuribo_use,
    0, (s32)kuribo_bye, 0, 0, 0, 0, (s32)"c_kuri_h", (s32)kuribo_init_800C23B4,
    (s32)partyMoveWalk, (s32)kuribo_use, 0, (s32)kuribo_bye, 0, 0, 0, 0,
    (s32)"c_monban", (s32)kuribo_init_800C23B4, (s32)partyMoveWalk, (s32)kuribo_use, 0, (s32)kuribo_bye, 0, 0,
    0, 0, (s32)"c_pkr", (s32)kuribo_init_800C23B4, (s32)partyMoveWalk, (s32)kuribo_use, 0, (s32)kuribo_bye,
    0, 0, 0, 0, (s32)"c_pnk", (s32)nokonoko_init, (s32)nokonoko_move, (s32)nokonoko_use,
    0, (s32)nokonoko_bye, 0, 0, 0, 0, (s32)"c_bomt_n", (s32)bomhei_init_800BFBB0,
    (s32)partyMoveWalk, (s32)bomhei_use, (s32)bomhei_use_post, (s32)bomhei_bye, 0, 0, 0, 0,
    (s32)"c_babyyoshi", (s32)yoshi_init, (s32)partyMoveWalk, (s32)yoshi_use, 0, (s32)yoshi_bye, 0, 0,
    0, 0, (s32)"c_windy", (s32)cloud_init, (s32)cloud_move, (s32)cloud_use, 0, (s32)kuribo_bye,
    0, 0, 0, (s32)cloud_exit, (s32)"c_vivian", (s32)vivian_init_801809C0, (s32)vivian_move, (s32)vivian_use,
    0, (s32)kuribo_bye, 0, 0, 0, 0, (s32)"c_tyutyu", (s32)chuchu_init,
    (s32)partyMoveWalk, (s32)chuchu_use, 0, (s32)kuribo_bye, 0, 0, 0, 0,
};

s32 partyPoseTbl[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)"PKR_Z_1",
    (s32)"PKR_S_1", (s32)"PKR_W_1", (s32)"PKR_R_1", (s32)"PKR_J_1A", (s32)"PKR_J_1B", (s32)"PKR_N_1", (s32)"PKR_T_1", (s32)"PKR_D_1",
    (s32)"PKR_D_4", (s32)"PKR_S_1", (s32)"PKR_S_1", (s32)"PKR_D_2", (s32)"PKR_W_2", (s32)"PKR_R_2", (s32)"PNK_Z_1", (s32)"PNK_S_1",
    (s32)"PNK_W_1", (s32)"PNK_R_1", (s32)"PNK_J_1A", (s32)"PNK_J_1B", (s32)"PNK_N_1", (s32)"PNK_T_1", (s32)"PNK_D_1", (s32)"PNK_D_4",
    (s32)"PNK_S_1", (s32)"PNK_S_1", (s32)"PNK_D_2", (s32)"PNK_W_2", (s32)"PNK_R_2", (s32)"Z_1", (s32)"S_1", (s32)"W_1",
    (s32)"R_1", (s32)"J_1A", (s32)"J_1B", (s32)"N_1", (s32)"T_1", (s32)"D_1", (s32)"F_1", (s32)"S_1",
    (s32)"S_1", (s32)"D_2", (s32)"W_3", (s32)"R_3", (s32)"PYS_Z_1", (s32)"PYS_S_1", (s32)"PYS_W_1", (s32)"PYS_R_1",
    (s32)"PYS_J_1A", (s32)"PYS_J_1B", (s32)"PYS_N_1", (s32)"PYS_T_1", (s32)"PYS_D_1", (s32)"PYS_D_4", (s32)"PYS_S_1", (s32)"PYS_S_1",
    (s32)"PYS_D_2", (s32)"PYS_W_3", (s32)"PYS_R_3", (s32)"PWD_Z_1", (s32)"PWD_S_1", (s32)"PWD_W_1", (s32)"PWD_R_1", (s32)"PWD_S_1",
    (s32)"PWD_S_1", (s32)"PWD_N_1", (s32)"PWD_T_1", (s32)"PWD_D_1", (s32)"PWD_F_1", (s32)"PWD_S_1", (s32)"PWD_S_1", (s32)"PWD_D_2",
    (s32)"PWD_W_2", (s32)"PWD_R_2", (s32)"PTR_Z_1", (s32)"PTR_S_1", (s32)"PTR_W_1", (s32)"PTR_R_1", (s32)"PTR_S_1", (s32)"PTR_S_1",
    (s32)"PTR_N_1", (s32)"PTR_T_1", (s32)"PTR_D_1", (s32)"PTR_F_1", (s32)"PTR_Z_1", (s32)"PTR_Z_1", (s32)"PTR_D_2", (s32)"PTR_W_2",
    (s32)"PTR_R_2", (s32)"PCH_Z_1", (s32)"PCH_S_1", (s32)"PCH_W_1", (s32)"PCH_R_1", (s32)"PCH_J_1A", (s32)"PCH_J_1B", (s32)"PCH_N_1",
    (s32)"PCH_T_1", (s32)"PCH_D_1", (s32)"PCH_F_1", (s32)"PCH_S_1", (s32)"PCH_S_1", (s32)"PCH_D_2", (s32)"PCH_R_2", (s32)"PCH_W_2",
    (s32)"PYS_E_1", (s32)"PYS_E_2", (s32)"PYS_E_3", (s32)"PYS_E_3", (s32)"PYS_E_2", (s32)"PYS_E_2", (s32)"PYS_E_2", (s32)"PYS_E_2",
    (s32)"PYS_E_2", (s32)"PYS_E_2", (s32)"PYS_E_2", (s32)"PYS_E_2", (s32)"PYS_E_2", (s32)"PYS_E_3", (s32)"PYS_E_3", (s32)"Z_1",
    (s32)"S_1", (s32)"W_1", (s32)"R_1", (s32)"J_1A", (s32)"J_1B", (s32)"S_1", (s32)"T_1", (s32)"D_1",
    (s32)"D_1", (s32)"Z_1", (s32)"Z_1", (s32)"S_1", (s32)"W_1", (s32)"R_1", (s32)"Z_1", (s32)"S_1",
    (s32)"W_1", (s32)"R_1", (s32)"J_1A", (s32)"J_1B", (s32)"S_1", (s32)"T_1", (s32)"Z_1", (s32)"Z_1",
    (s32)"S_1", (s32)"Z_1", (s32)"Z_1", (s32)"W_1", (s32)"R_1", (s32)"Z_1", (s32)"S_1", (s32)"W_1",
    (s32)"R_1", (s32)"W_1", (s32)"W_1", (s32)"S_1", (s32)"T_1", (s32)"Z_1", (s32)"Z_1", (s32)"S_1",
    (s32)"Z_1", (s32)"Z_1", (s32)"W_1", (s32)"R_1", (s32)"Z_1", (s32)"S_1", (s32)"W_1", (s32)"R_1",
    (s32)"S_1", (s32)"S_1", (s32)"S_1", (s32)"T_1", (s32)"S_1", (s32)"S_1", (s32)"S_1", (s32)"S_1",
    (s32)"S_1", (s32)"W_1", (s32)"R_1", (s32)"PKR_Z_1", (s32)"PKR_S_1", (s32)"PKR_W_1", (s32)"PKR_R_1", (s32)"PKR_J_1A",
    (s32)"PKR_J_1B", (s32)"PKR_N_1", (s32)"PKR_T_1", (s32)"PKR_D_1", (s32)"PKR_D_4", (s32)"PKR_S_1", (s32)"PKR_S_1", (s32)"PKR_D_2",
    (s32)"PKR_W_2", (s32)"PKR_R_2", (s32)"PNK_Z_1", (s32)"PNK_S_1", (s32)"PNK_W_1", (s32)"PNK_R_1", (s32)"PNK_J_1A", (s32)"PNK_J_1B",
    (s32)"PNK_N_1", (s32)"PNK_T_1", (s32)"PNK_D_1", (s32)"PNK_D_4", (s32)"PNK_S_1", (s32)"PNK_S_1", (s32)"PNK_D_2", (s32)"PNK_W_2",
    (s32)"PNK_R_2", (s32)"Z_1", (s32)"S_1", (s32)"W_1", (s32)"R_1", (s32)"J_1A", (s32)"J_1B", (s32)"N_1",
    (s32)"T_1", (s32)"D_1", (s32)"F_1", (s32)"S_1", (s32)"S_1", (s32)"D_2", (s32)"W_3", (s32)"R_3",
    (s32)"PYS_Z_1", (s32)"PYS_S_1", (s32)"PYS_W_1", (s32)"PYS_R_1", (s32)"PYS_J_1A", (s32)"PYS_J_1B", (s32)"PYS_N_1", (s32)"PYS_T_1",
    (s32)"PYS_D_1", (s32)"PYS_D_4", (s32)"PYS_S_1", (s32)"PYS_S_1", (s32)"PYS_D_2", (s32)"PYS_W_2", (s32)"PYS_R_2", (s32)"PWD_Z_1",
    (s32)"PWD_S_1", (s32)"PWD_W_1", (s32)"PWD_R_1", (s32)"PWD_S_1", (s32)"PWD_S_1", (s32)"PWD_N_1", (s32)"PWD_T_1", (s32)"PWD_D_1",
    (s32)"PWD_F_1", (s32)"PWD_S_1", (s32)"PWD_S_1", (s32)"PWD_D_2", (s32)"PWD_W_2", (s32)"PWD_R_2", (s32)"PTR_Z_1", (s32)"PTR_S_1",
    (s32)"PTR_W_1", (s32)"PTR_R_1", (s32)"PTR_S_1", (s32)"PTR_S_1", (s32)"PTR_N_1", (s32)"PTR_T_1", (s32)"PTR_D_1", (s32)"PTR_F_1",
    (s32)"PTR_Z_1", (s32)"PTR_Z_1", (s32)"PTR_D_2", (s32)"PTR_W_2", (s32)"PTR_R_2", (s32)"PCH_Z_1", (s32)"PCH_S_1", (s32)"PCH_W_1",
    (s32)"PCH_R_1", (s32)"PCH_J_1A", (s32)"PCH_J_1B", (s32)"PCH_N_1", (s32)"PCH_T_1", (s32)"PCH_D_1", (s32)"PCH_F_1", (s32)"PCH_S_1",
    (s32)"PCH_S_1", (s32)"PCH_D_2", (s32)"PCH_R_2", (s32)"PCH_W_2",
};

s32 partyDotPoseTbl[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)"Z_2",
    (s32)"Z_2", (s32)"W_2", (s32)"R_2", (s32)"Z_2", (s32)"Z_2", (s32)"Z_2", (s32)"Z_2", (s32)"Z_2",
    (s32)"Z_2", (s32)"Z_2", (s32)"Z_2", (s32)"Z_2", (s32)"W_2", (s32)"R_2", (s32)"Z_3", (s32)"Z_3",
    (s32)"W_3", (s32)"R_3", (s32)"Z_3", (s32)"Z_3", (s32)"Z_3", (s32)"Z_3", (s32)"Z_3", (s32)"Z_3",
    (s32)"Z_3", (s32)"Z_3", (s32)"Z_3", (s32)"W_3", (s32)"R_3", (s32)"Z_13", (s32)"Z_13", (s32)"W_13",
    (s32)"R_13", (s32)"Z_13", (s32)"Z_13", (s32)"Z_13", (s32)"Z_13", (s32)"Z_13", (s32)"Z_13", (s32)"Z_13",
    (s32)"Z_13", (s32)"Z_13", (s32)"W_13", (s32)"R_13", (s32)"Z_5", (s32)"Z_5", (s32)"W_5", (s32)"R_5",
    (s32)"Z_5", (s32)"Z_5", (s32)"Z_5", (s32)"Z_5", (s32)"Z_5", (s32)"Z_5", (s32)"Z_5", (s32)"Z_5",
    (s32)"Z_5", (s32)"W_5", (s32)"R_5", (s32)"Z_4", (s32)"Z_4", (s32)"W_4", (s32)"R_4", (s32)"Z_4",
    (s32)"Z_4", (s32)"Z_4", (s32)"Z_4", (s32)"Z_4", (s32)"Z_4", (s32)"Z_4", (s32)"Z_4", (s32)"Z_4",
    (s32)"W_4", (s32)"R_4", (s32)"Z_12", (s32)"Z_12", (s32)"W_12", (s32)"R_12", (s32)"Z_12", (s32)"Z_12",
    (s32)"Z_12", (s32)"Z_12", (s32)"Z_12", (s32)"Z_12", (s32)"Z_12", (s32)"Z_12", (s32)"Z_12", (s32)"W_12",
    (s32)"R_12", (s32)"Z_14", (s32)"Z_14", (s32)"W_14", (s32)"R_14", (s32)"Z_14", (s32)"Z_14", (s32)"Z_14",
    (s32)"Z_14", (s32)"Z_14", (s32)"Z_14", (s32)"Z_14", (s32)"Z_14", (s32)"Z_14", (s32)"W_14", (s32)"R_14",
};

s32 yoshiDotPoseTbl[] = {
    (s32)"Z_5", (s32)"Z_5", (s32)"W_5", (s32)"R_5", (s32)"Z_5", (s32)"Z_5", (s32)"Z_5", (s32)"Z_5",
    (s32)"Z_5", (s32)"Z_5", (s32)"Z_5", (s32)"Z_5", (s32)"Z_5", (s32)"W_5", (s32)"R_5", (s32)"Z_6",
    (s32)"Z_6", (s32)"W_6", (s32)"R_6", (s32)"Z_6", (s32)"Z_6", (s32)"Z_6", (s32)"Z_6", (s32)"Z_6",
    (s32)"Z_6", (s32)"Z_6", (s32)"Z_6", (s32)"Z_6", (s32)"W_6", (s32)"R_6", (s32)"Z_7", (s32)"Z_7",
    (s32)"W_7", (s32)"R_7", (s32)"Z_7", (s32)"Z_7", (s32)"Z_7", (s32)"Z_7", (s32)"Z_7", (s32)"Z_7",
    (s32)"Z_7", (s32)"Z_7", (s32)"Z_7", (s32)"W_7", (s32)"R_7", (s32)"Z_8", (s32)"Z_8", (s32)"W_8",
    (s32)"R_8", (s32)"Z_8", (s32)"Z_8", (s32)"Z_8", (s32)"Z_8", (s32)"Z_8", (s32)"Z_8", (s32)"Z_8",
    (s32)"Z_8", (s32)"Z_8", (s32)"W_8", (s32)"R_8", (s32)"Z_9", (s32)"Z_9", (s32)"W_9", (s32)"R_9",
    (s32)"Z_9", (s32)"Z_9", (s32)"Z_9", (s32)"Z_9", (s32)"Z_9", (s32)"Z_9", (s32)"Z_9", (s32)"Z_9",
    (s32)"Z_9", (s32)"W_9", (s32)"R_9", (s32)"Z_10", (s32)"Z_10", (s32)"W_10", (s32)"R_10", (s32)"Z_10",
    (s32)"Z_10", (s32)"Z_10", (s32)"Z_10", (s32)"Z_10", (s32)"Z_10", (s32)"Z_10", (s32)"Z_10", (s32)"Z_10",
    (s32)"W_10", (s32)"R_10", (s32)"Z_11", (s32)"Z_11", (s32)"W_11", (s32)"R_11", (s32)"Z_11", (s32)"Z_11",
    (s32)"Z_11", (s32)"Z_11", (s32)"Z_11", (s32)"Z_11", (s32)"Z_11", (s32)"Z_11", (s32)"Z_11", (s32)"W_11",
    (s32)"R_11",
};

#pragma force_active on
#pragma explicit_zero_data on
#pragma explicit_zero_data reset
#pragma force_active reset
