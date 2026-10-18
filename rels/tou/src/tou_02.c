#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "string.h"
#include "mario/mariost.h"
#include "dolphin/os.h"
#include "stdlib.h"
#include "memory.h"
#include "pmario_sound.h"
#include "system.h"
#include "dolphin/mtx.h"
#include "driver/camdrv.h"
#include "mario/mario.h"
#include "party/party_cloud.h"
#include "driver/npcdrv.h"
#include "driver/hitdrv.h"
#include "driver/dispdrv.h"
#include "party.h"
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)
#pragma force_active on
u32 gap_05_00000024_bss[1];
extern const char str_0000455C[];
extern const char str_00004564[];
extern const char str_00004570[];
extern const char str_00004580[];
extern const char str_0000459C[];
extern const char str_000045A8[];
extern const char str_000045B4[];
extern const char str_000045E8[];
extern const char str_000045F4[];
extern const char str_00004600[];
extern const char str_00003BC0[];
extern const char str_00003BD4[];
extern const char str_00003BE0[];
extern const char str_00003BEC[];
extern const char str_00003BF8[];
extern const char str_00003C04[];
extern const char str_00003C10[];
extern const char str_00003C1C[];
extern const char str_00003C24[];
extern const char str_00003C2C[];
extern const char str_00003C34[];
extern const char str_00003C3C[];
extern const char str_00003C48[];
extern const char str_00003C54[];
extern const char str_00003C5C[];
extern const char str_00003C68[];
extern const char str_00003C74[];
extern const char str_00003C80[];
extern const char str_00003C8C[];
extern const char str_00003C94[];
extern const char str_00003C9C[];
extern const char str_00003CA8[];
extern const char str_00003CB0[];
extern const char str_00003CB4[];
extern const char str_00003CC4[];
extern const char str_00003CCC[];
extern const char str_00003CDC[];
extern const char str_00003CE8[];
extern const char str_00003CF4[];
extern const char str_00003D04[];
extern const char str_00003D14[];
extern const char str_00003D28[];
extern const char str_00003D38[];
extern const char str_00003D48[];
extern const char str_00003D5C[];
extern const char str_00003D70[];
extern const char str_00003D84[];
extern const char str_00003D98[];
extern const char str_00003DAC[];
extern const char str_00003DC0[];
extern const char str_00003DD4[];
extern const char str_00003DE8[];
extern const char str_00003DFC[];
extern const char str_00003E10[];
extern const char str_00003E24[];
extern const char str_00003E38[];
extern const char str_00003E4C[];
extern const char str_00003E60[];
extern const char str_00003E70[];
extern const char str_00003E84[];
extern const char str_00003E94[];
extern const char str_00003EA8[];
extern const char str_00003EBC[];
extern const char str_00003ED0[];
extern const char str_00003EE4[];
extern const char str_00003EF8[];
extern const char str_00003F0C[];
extern const char str_00003F20[];
extern const char str_00003F30[];
extern const char str_00003F44[];
extern const char str_00003F54[];
extern const char str_00003F68[];
extern const char str_00003F7C[];
extern const char str_00003F90[];
extern const char str_00003FA4[];
extern const char str_00003FB8[];
extern const char str_00003FCC[];
extern const char str_00003FE0[];
extern const char str_00003FF0[];
extern const char str_00004004[];
extern const char str_00004014[];
extern const char str_00004028[];
extern const char str_0000403C[];
extern const char str_00004050[];
extern const char str_00004064[];
extern const char str_00004078[];
extern const char str_0000408C[];
extern const char str_000040A0[];
extern const char str_000040B0[];
extern const char str_000040C4[];
extern const char str_000040D4[];
extern const char str_000040E8[];
extern const char str_000040FC[];
extern const char str_00004110[];
extern const char str_00004128[];
extern const char str_0000413C[];
extern const char str_00004154[];
extern const char str_00004168[];
extern const char str_00004180[];
extern const char str_00004194[];
extern const char str_000041AC[];
extern const char str_000041C0[];
extern const char str_000041D4[];
extern const char str_000041E4[];
extern const char str_000041FC[];
extern const char str_00004210[];
extern const char str_00004224[];
extern const char str_00004234[];
extern const char str_00004248[];
extern const char str_0000425C[];
extern const char str_00004270[];
extern const char str_00004284[];
extern const char str_00004298[];
extern const char str_000042AC[];
extern const char str_000042C0[];
extern const char str_000042D0[];
extern const char str_000042E4[];
extern const char str_000042F4[];
extern const char str_00004300[];
extern const char str_00004314[];
extern const char str_00004328[];
extern const char str_0000433C[];
extern const char str_00004350[];
extern const char str_00004364[];
extern const char str_00004378[];
extern const char str_0000438C[];
extern const char str_0000439C[];
extern const char str_000043B0[];
extern const char str_000043C0[];
extern const char str_000043D4[];
extern const char str_000043E8[];
extern const char str_000043FC[];
extern const char str_00004410[];
extern const char str_00004424[];
extern const char str_00004438[];
extern const char str_0000444C[];
extern const char str_0000445C[];
extern const char str_0000446C[];
extern const char str_0000447C[];
extern const char str_0000448C[];
extern const char str_0000449C[];
extern const char str_000044AC[];
extern const char str_000044BC[];
extern const char str_000044CC[];
extern const char str_000044DC[];
extern const char str_000044EC[];
extern const char str_000044FC[];
extern const char str_0000450C[];
extern const char str_0000451C[];
extern const char str_0000452C[];
extern const char str_0000453C[];
extern const char str_0000454C[];
extern const char str_00004590[];
extern const char str_000045C0[];
extern const char str_000045D0[];
extern const char str_000045DC[];
extern const char str_0000460C[];
extern const char str_00004618[];
extern const char str_00004628[];
extern const char str_00004638[];
extern const char str_00004648[];
extern const char str_00004658[];
extern const char str_00004668[];
extern const char str_00004678[];
extern const char str_00004688[];
extern const char str_000046A0[];
extern const char str_000046A8[];
extern const char str_000046B0[];
extern const char str_000046BC[];
extern const char str_000046C8[];
extern const char str_000046D0[];
extern const char str_000046DC[];
extern const char str_000046E4[];
extern const char str_000046F0[];
extern const char str_00004740[];
extern const char str_00004750[];
extern const char str_00004760[];
extern const char str_00004770[];
extern const char str_00004780[];
extern const char str_00004790[];
extern const char str_000047A0[];
extern const char str_000047A4[];
extern const char str_000047AC[];
extern const char str_000047B4[];
extern const char str_000047B8[];
extern const char str_000047C8[];
extern const char str_000047E0[];
extern const char str_000047F8[];
extern const char str_0000480C[];
extern const char str_00004814[];
extern const char str_00004828[];
extern const char str_00004830[];
extern const char str_00004840[];
extern const char str_00004848[];
extern const char str_0000485C[];
extern const char str_00004870[];
extern const char str_00004884[];
extern const char str_00004898[];
extern const char str_000048AC[];
extern const char str_000048B4[];
extern const char str_000048C4[];
extern const char str_000048D4[];
extern const char str_000048E4[];
extern const char str_000048F0[];
extern const char str_000048F8[];
extern const char str_00004904[];
extern const char str_00004920[];
extern const char str_0000493C[];
extern const char str_00004944[];
extern const char str_0000494C[];
extern const char str_00004954[];
extern const char str_0000495C[];
extern const char str_00004964[];
extern const char str_0000496C[];
extern const char str_00004974[];
extern const char str_0000497C[];
extern const char str_00004984[];
extern const char str_0000498C[];
extern const char str_00004994[];
extern const char str_0000499C[];
extern const char str_000049A4[];
extern const char str_000049AC[];
extern const char str_000049B4[];
extern const char str_000049BC[];
extern const char str_000049C4[];
extern const char str_000049CC[];
extern const char str_000049D4[];
extern const char str_000049DC[];
extern const char str_000049E4[];
extern const char str_000049EC[];

typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
typedef struct Fan { u16 flags; s16 state; s16 animIdx; u8 pad_0x6[2]; u64 time; Vec pos; Vec vel; f32 field_0x28; Vec target; Vec param; s16 timer; } Fan;
typedef struct FanAnim { char name[16]; char anim[8]; s16 loop; f32 rate; s32 start; s32 count; } FanAnim;
typedef struct FanWork { s32 num; Fan* fans; s32 animNum; FanAnim anim[32]; s32 hammerTimer; s32 count; s32 sfxId; u8 vol; } FanWork;
typedef struct FanData { const char* name; const char* anim; f32 rate; } FanData;
FanWork* fan_wp;
ExtPose* extGetPosePtr(void);
s32 extGetPoseNum(void);
static void pose_init(void);
static void pose_init(void);
static void pose_change(Fan* fan, const char* name, const char* anim);
static void pose_change(Fan* fan, const char* name, const char* anim);
static f32 randf(f32 min, f32 max);
static f32 randf(f32 min, f32 max);
u8 psndSFX_get_vol(s32 id);
void extLoadRenderMode(void);
void extLoadVertex(void);
void extLoadTexture(void);
void extLoadTev(void);
void extDraw(void);
void extLoadTextureExit(void);
#ifdef NONMATCHING
static inline f32 fan_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
#endif
#ifdef NONMATCHING
static inline f32 fan_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
#endif
s32 check_hammer(Fan* fan);
s32 check_hammer(Fan* fan);
void psndSFX_pos(s32 id, Vec* pos);
void psndSFX_vol(s32 id, u8 vol);
static void pose_main(void);
static void pose_main(void);
void fan_disp(CameraId camera, void* param);
void fan_disp(CameraId camera, void* param);
f32 cloudGetBreathDist(void);

s32 N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_exec_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_entername(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_info(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_mapchange(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_off(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_set(EventEntry* event, BOOL isFirstCall);
s32 evt_cloud_ent(EventEntry* event, BOOL isFirstCall);
s32 evt_cloud_init(EventEntry* event, BOOL isFirstCall);
s32 evt_eff_fukidashi(EventEntry* event, BOOL isFirstCall);
s32 evt_end_count(EventEntry* event, BOOL isFirstCall);
s32 evt_end_count(EventEntry* event, BOOL isFirstCall);
s32 evt_ext_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_fade_end_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_hitobj_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_item_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_item_get_item_end_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_item_set_bound_rate(EventEntry* event, BOOL isFirstCall);
s32 evt_item_set_gravity(EventEntry* event, BOOL isFirstCall);
s32 evt_item_set_jump_power(EventEntry* event, BOOL isFirstCall);
s32 evt_item_set_move_dir_speed(EventEntry* event, BOOL isFirstCall);
s32 evt_item_status_on(EventEntry* event, BOOL isFirstCall);
s32 evt_key_get_buttontrg(EventEntry* event, BOOL isFirstCall);
s32 evt_map_checkanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_playanim(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_rotate(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_trans(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_balloon_bikkuri(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_balloon_off(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_party(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_key_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_mov_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_mov_pos2(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_normalize(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_dir(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_party(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_pose(EventEntry* event, BOOL isFirstCall);
s32 evt_mobj_kururing_floor(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print_add(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print_insert(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print_party(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_select(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_toge(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_change_interrupt(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_move_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_reverse_ry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_scale(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_setup(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_status_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_party_get_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_move_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_run(EventEntry* event, BOOL isFirstCall);
s32 evt_party_set_dir(EventEntry* event, BOOL isFirstCall);
s32 evt_party_set_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_stop(EventEntry* event, BOOL isFirstCall);
s32 evt_party_yoshi_ride(EventEntry* event, BOOL isFirstCall);
s32 evt_pouch_all_party_recovery(EventEntry* event, BOOL isFirstCall);
s32 evt_pouch_get_yoshiname(EventEntry* event, BOOL isFirstCall);
s32 evt_pouch_mario_recovery(EventEntry* event, BOOL isFirstCall);
s32 evt_pouch_open_mail(EventEntry* event, BOOL isFirstCall);
s32 evt_pouch_receive_mail(EventEntry* event, BOOL isFirstCall);
s32 evt_pouch_remove_item(EventEntry* event, BOOL isFirstCall);
s32 evt_seq_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_set_dir_to_target(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_envon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxon_3d(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_intpl_msec_get_value(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_intpl_msec_init(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_random(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_rumble_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_tou_get_ranking_27_text_1ED4(EventEntry* event, BOOL isFirstCall);
s32 check_hammer(Fan* fan);
void ext_fan_dispent(void);
void ext_fan_dispent(void);
void ext_fan_main(void);
void ext_fan_main(void);
void fan_disp(CameraId camera, void* param);
void ext_fan_init(void);
void ext_fan_init(void);
static f32 randf(f32 min, f32 max);
static void pose_change(Fan* fan, const char* name, const char* anim);
static void pose_main(void);
static void pose_init(void);
extern s32 bero_case_entry[];
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 bero_close_door_play_se[];
extern s32 bero_open_door_play_se[];
extern s32 evt_bero_info_run[];
extern s32 evt_sub_mail_vibration[];

__declspec(section ".data") u64 fd_tou_02_negone_one_374;
__declspec(section ".data") s32 fd_tou_02_neg_one_382[1];
__declspec(section ".data") s32 fd_tou_02___local_PI_383[1];
__declspec(section ".data") s32 fd_tou_02___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tou_02_one_negone_373;
__declspec(section ".data") s32 fd_tou_02___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tou_02_one_381[1];
__declspec(section ".data") u64 fd_tou_02_negone_one_360;
__declspec(section ".data") s32 fd_tou_02_neg_one_365[1];
__declspec(section ".data") s32 fd_tou_02___local_PI_366[1];
__declspec(section ".data") s32 fd_tou_02___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tou_02_one_negone_359;
__declspec(section ".data") s32 fd_tou_02___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tou_02_one_364[1];
static s32 s_door_open[58];
static s32 s_door_close[58];
s32 n_1_door_open[22];
s32 n_1_door_close[22];
static s32 n_2_door_open[22];
static s32 n_2_door_close[22];
__declspec(section ".data") s32 n_3_door_open[12];
__declspec(section ".data") s32 n_3_door_close[12];
__declspec(section ".data") s32 n_4_door_open[12];
__declspec(section ".data") s32 n_4_door_close[12];
static s32 bero_data[90];
s32 evt_move_g[63];
s32 init_gard1[39];
s32 talk_gard1[70];
s32 init_gard2[39];
s32 talk_gard2[70];
static s32 init_madam[39];
static s32 talk_madam[67];
__declspec(section ".data") s32 init_repo[8];
s32 talk_repo[112];
__declspec(section ".data") s32 init_cam1[8];
s32 talk_cam1[112];
s32 init_cam2[19];
s32 talk_cam2[112];
s32 init_kino4[13];
s32 reg_kino4[31];
s32 talk_kino4[112];
__declspec(section ".data") s32 init_kino5[8];
s32 talk_kino5[236];
__declspec(section ".data") s32 init_kinopiko[8];
s32 talk_kinopiko[112];
__declspec(section ".data") s32 init_kinopio_f[8];
s32 talk_kinopio_f[112];
s32 init_chu[20];
s32 talk_chu[67];
static s32 init_champ[32];
s32 move_pos[26];
s32 move_champ[155];
s32 talk_champ[34];
s32 init_shikowa[32];
s32 talk_shikowa[13];
static s32 init_uranoko[32];
static s32 talk_uranoko[13];
s32 init_ironA[38];
s32 talk_ironA[13];
s32 init_ironB[38];
s32 talk_ironB[13];
s32 init_borodo[32];
s32 talk_borodo[13];
static s32 npcEnt[391];
s32 evt_tougi2[285];
s32 ext_fan_data[84];
s32 mario_momikucha_msg[111];
s32 evt_momikucha[105];
static s32 evt_key[173];
__declspec(section ".data") static s32 evt_poster_1[5];
__declspec(section ".data") static s32 evt_poster_2[5];
__declspec(section ".data") static s32 evt_poster_3[5];
__declspec(section ".data") static s32 evt_poster_4[5];
__declspec(section ".data") static s32 evt_poster_5[5];
__declspec(section ".data") static s32 evt_poster_6[5];
__declspec(section ".data") static s32 evt_poster_7[5];
static s32 evt_poster_8[46];
__declspec(section ".data") static s32 evt_poster_9[5];
static s32 evt_after_peach[188];
s32 tou_02_init_evt[576];

#ifdef NONMATCHING
static void pose_init(void) {
    char name[32];
    char anim[32];
    FanData* d = (FanData*)ext_fan_data;
    s32 i = 0;
    s32 start;

    strcpy(name, "");
    strcpy(anim, "");
    fan_wp->animNum = -1;
    do {
        if (strcmp(d->name, name) != 0) {
            strcpy(name, d->name);
            strcpy(anim, "");
        }
        if (strcmp(d->anim, anim) != 0) {
            strcpy(anim, d->anim);
            start = i;
            fan_wp->animNum++;
        }
        strcpy(fan_wp->anim[fan_wp->animNum].name, name);
        strcpy(fan_wp->anim[fan_wp->animNum].anim, anim);
        fan_wp->anim[fan_wp->animNum].start = start;
        fan_wp->anim[fan_wp->animNum].count = i - start + 1;
        fan_wp->anim[fan_wp->animNum].rate = d->rate;
        fan_wp->anim[fan_wp->animNum].loop = 1;
        i++;
        d++;
    } while (d->name != NULL);
    fan_wp->animNum++;
}
#endif

#ifdef NONMATCHING
static void pose_main(void) {
    s32 i;
    ExtPose* pose;
    Fan* fan;
    FanAnim* a;
    f32 t;

    pose = extGetPosePtr();
    fan = fan_wp->fans;

    for (i = 0; i < fan_wp->num; i++, fan++, pose++) {
        a = &fan_wp->anim[fan->animIdx];
        t = 60.0f * OSTicksToMilliseconds((u64)(gp->renderTime - fan->time)) / 1000.0f / a->rate;
        if (t >= 1.0f) {
            fan->time = gp->renderTime;
            t = 0.0f;
        }
        pose->frame = a->start + (s32)((a->count - 1) * t);
    }
}
#endif

#ifdef NONMATCHING
static void pose_change(Fan* fan, const char* name, const char* anim) {
    FanAnim* a;
    s32 i;

    for (i = 0, a = fan_wp->anim; i < fan_wp->animNum; i++, a++) {
        if (strcmp(a->name, name) == 0 && strcmp(a->anim, anim) == 0) {
            break;
        }
    }
    if (i < fan_wp->animNum && fan->animIdx != i) {
        fan->animIdx = i;
        fan->time = gp->renderTime;
    }
}
#endif

#ifdef NONMATCHING
static f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return r * (max - min) + min;
}
#endif

__declspec(section ".data") u64 fd_tou_02_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tou_02_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tou_02___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tou_02___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tou_02_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tou_02___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tou_02_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tou_02_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tou_02_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tou_02___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tou_02___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tou_02_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tou_02___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tou_02_one_364[] = {
    1065353216,
};

static EVT_BEGIN(s_door_open)
    IF_FLOAT_EQUAL(LW(0), FLOAT(0.0f))
        IF_INT_EQUAL(GSWF(2526), 0)
            SET_VALUE(GSWF(2526), 1)
            BEGIN_INLINE_EVENT
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING(((char*)str_00003BC0)), LW(0), LW(1), LW(2), GW(13))
            END_INLINE_EVENT
        END_IF
    END_IF
    IF_FLOAT_EQUAL(LW(0), FLOAT(180.0f))
        SET_VALUE(GSWF(2526), 0)
        CALL(evt_snd_sfxoff, GW(13))
    END_IF
    MULTIPLY_FLOAT(LW(0), FLOAT(0.3330078f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00003BD4)), LW(0), 0, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00003BE0)), LW(0), 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(s_door_close)
    IF_FLOAT_EQUAL(LW(0), FLOAT(180.0f))
        IF_INT_EQUAL(GSWF(2526), 0)
            SET_VALUE(GSWF(2526), 1)
            BEGIN_INLINE_EVENT
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING(((char*)str_00003BC0)), LW(0), LW(1), LW(2), GW(13))
            END_INLINE_EVENT
        END_IF
    END_IF
    IF_FLOAT_EQUAL(LW(0), FLOAT(0.0f))
        SET_VALUE(GSWF(2526), 0)
        CALL(evt_snd_sfxoff, GW(13))
    END_IF
    MULTIPLY_FLOAT(LW(0), FLOAT(0.3330078f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00003BD4)), LW(0), 0, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00003BE0)), LW(0), 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(n_1_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00003BEC)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00003BF8)), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(n_1_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00003BEC)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00003BF8)), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(n_2_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00003C04)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00003C10)), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(n_2_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00003C04)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00003C10)), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n_3_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00003C1C)), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n_3_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00003C1C)), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n_4_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00003C24)), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n_4_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00003C24)), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_data[] = {
    (s32)((char*)str_00003C2C), 65536, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)str_00003C34), (s32)((char*)str_00003C3C), 327685, (s32)s_door_close, (s32)s_door_open, (s32)((char*)str_00003C48),
    65542, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)((char*)str_00003C54), (s32)((char*)str_00003C5C), 327685, (s32)n_1_door_close, (s32)n_1_door_open, (s32)((char*)str_00003C68), 65542,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)((char*)str_00003C54), (s32)((char*)str_00003C74), 327685, (s32)n_2_door_close, (s32)n_2_door_open, (s32)((char*)str_00003C80), 65540, 20000,
    100000, 0, 0, -1, 0, -1, 0, (s32)((char*)str_00003C8C),
    (s32)((char*)str_00003C94), 327685, (s32)n_3_door_close, (s32)n_3_door_open, (s32)((char*)str_00003C9C), 65540, 20000, 100000,
    0, 0, -1, 0, -1, 0, (s32)((char*)str_00003C8C), (s32)((char*)str_00003CA8),
    327685, (s32)n_4_door_close, (s32)n_4_door_open, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

EVT_BEGIN(evt_move_g)
    CALL(evt_npc_get_position, STRING(((char*)str_00003CB0)), LW(0), LW(1), LW(2))
    ADD(LW(2), 100)
    CALL(evt_mario_mov_pos, LW(0), LW(2), 500)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)str_00003CB4)), -530, -185, 0, FLOAT(80.0f), 1)
        CALL(evt_set_dir_to_target, STRING(((char*)str_00003CB4)), STRING(((char*)str_00003CC4)))
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING(((char*)str_00003CCC)), 530, -185, 0, FLOAT(80.0f), 1)
    CALL(evt_set_dir_to_target, STRING(((char*)str_00003CCC)), STRING(((char*)str_00003CC4)))
    SET_VALUE(LW(0), 3)
    CALL_CHILD(PTR(bero_case_switch_on))
    SET_VALUE(LW(0), 4)
    CALL_CHILD(PTR(bero_case_switch_on))
    IF_INT_LESS(GSW(0), 129)
        SET_VALUE(GSW(0), 129)
        ELSE
        SET_VALUE(GSWF(2497), 1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(init_gard1)
    SWITCH(GSW(0))
        CASE_LESS(129)
        CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), -470, 0, -185)
        CASE_LESS(171)
        CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), -530, 0, -185)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2497), 0)
            CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), -470, 0, -185)
            ELSE
            CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), -530, 0, -185)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_gard1)
    SWITCH(GSW(0))
        CASE_LESS(128)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003CDC)), 0, 0)
        CASE_LESS(129)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003CE8)), 0, 0)
        CALL_CHILD(PTR(evt_move_g))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003CF4)), 0, 0)
        CASE_LESS(171)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003D04)), 0, 0)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003D14)), 0, 0)
            ELSE
            IF_INT_EQUAL(GSWF(2497), 0)
                CALL(evt_msg_print, 0, STRING(((char*)str_00003D28)), 0, 0)
                CALL_CHILD(PTR(evt_move_g))
                ELSE
                CALL(evt_msg_print, 0, STRING(((char*)str_00003D38)), 0, 0)
            END_IF
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_gard2)
    SWITCH(GSW(0))
        CASE_LESS(129)
        CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), 470, 0, -185)
        CASE_LESS(171)
        CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), 530, 0, -185)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2497), 0)
            CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), 470, 0, -185)
            ELSE
            CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), 530, 0, -185)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_gard2)
    SWITCH(GSW(0))
        CASE_LESS(128)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003CDC)), 0, 0)
        CASE_LESS(129)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003CE8)), 0, 0)
        CALL_CHILD(PTR(evt_move_g))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003CF4)), 0, 0)
        CASE_LESS(171)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003D04)), 0, 0)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003D14)), 0, 0)
            ELSE
            IF_INT_EQUAL(GSWF(2497), 0)
                CALL(evt_msg_print, 0, STRING(((char*)str_00003D28)), 0, 0)
                CALL_CHILD(PTR(evt_move_g))
                ELSE
                CALL(evt_msg_print, 0, STRING(((char*)str_00003D38)), 0, 0)
            END_IF
        END_IF
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(init_madam)
    SWITCH(GSW(0))
        CASE_LESS(172)
        CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), 525, 0, 0)
        CASE_EQUAL(172)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), 525, 0, 0)
            ELSE
            CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), 0, -1000, 0)
        END_IF
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), 0, -1000, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_madam)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003D48)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003D5C)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003D70)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003D84)), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003D98)), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)str_00003DAC)), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)str_00003DC0)), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_repo)
    CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), -100, 0, -25)
    RETURN
EVT_END()

EVT_BEGIN(talk_repo)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003DD4)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003DE8)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003DFC)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003E10)), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003E24)), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)str_00003E38)), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003E4C)), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING(((char*)str_00003E60)), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING(((char*)str_00003E70)), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING(((char*)str_00003E84)), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING(((char*)str_00003E70)), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_cam1)
    CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), -150, 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(talk_cam1)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003E94)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003EA8)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003EBC)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003ED0)), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003EE4)), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)str_00003EF8)), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003F0C)), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING(((char*)str_00003F20)), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING(((char*)str_00003F30)), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING(((char*)str_00003F44)), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING(((char*)str_00003F30)), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_cam2)
    IF_INT_LESS(GSW(0), 128)
        CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), 80, 200, -125)
        ELSE
        CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), 30, 200, -60)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(talk_cam2)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003F54)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003F68)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003F7C)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003F90)), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003FA4)), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)str_00003FB8)), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00003FCC)), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING(((char*)str_00003FE0)), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING(((char*)str_00003FF0)), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING(((char*)str_00004004)), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING(((char*)str_00003FF0)), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_kino4)
    CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), -350, 0, 75)
    CALL(evt_npc_status_onoff, 1, STRING(((char*)str_00003CB0)), 2)
    RETURN
EVT_END()

EVT_BEGIN(reg_kino4)
    LOOP(0)
        CALL(evt_npc_move_position, STRING(((char*)str_00003CB0)), -350, 75, 0, FLOAT(48.0f), 0)
        WAIT_MS(1000)
        CALL(evt_npc_reverse_ry, STRING(((char*)str_00003CB0)))
        CALL(evt_npc_move_position, STRING(((char*)str_00003CB0)), 350, 75, 0, FLOAT(48.0f), 0)
        WAIT_MS(1000)
        CALL(evt_npc_reverse_ry, STRING(((char*)str_00003CB0)))
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(talk_kino4)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_00004014)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)str_00004028)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_0000403C)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING(((char*)str_00004050)), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00004064)), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)str_00004078)), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING(((char*)str_0000408C)), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING(((char*)str_000040A0)), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING(((char*)str_000040B0)), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING(((char*)str_000040C4)), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING(((char*)str_000040B0)), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_kino5)
    CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), -520, 0, 25)
    RETURN
EVT_END()

EVT_BEGIN(talk_kino5)
    CALL(evt_pouch_get_yoshiname, LW(10))
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_000040D4)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)str_000040E8)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_000040FC)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_mario_get_party, LW(0))
            IF_INT_EQUAL(LW(0), 4)
                CALL(evt_msg_print_insert, 0, STRING(((char*)str_00004110)), 0, 0, LW(10))
                ELSE
                CALL(evt_msg_print_insert, 0, STRING(((char*)str_00004128)), 0, 0, LW(10))
            END_IF
            CASE_GREATER(0)
            CALL(evt_mario_get_party, LW(0))
            IF_INT_EQUAL(LW(0), 4)
                CALL(evt_msg_print_insert, 0, STRING(((char*)str_0000413C)), 0, 0, LW(10), LW(10))
                ELSE
                CALL(evt_msg_print_insert, 0, STRING(((char*)str_00004154)), 0, 0, LW(10))
            END_IF
            CASE_DEFAULT
            CALL(evt_mario_get_party, LW(0))
            IF_INT_EQUAL(LW(0), 4)
                CALL(evt_msg_print_insert, 0, STRING(((char*)str_00004168)), 0, 0, LW(10))
                ELSE
                CALL(evt_msg_print_insert, 0, STRING(((char*)str_00004180)), 0, 0, LW(10))
            END_IF
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_mario_get_party, LW(0))
            IF_INT_EQUAL(LW(0), 4)
                CALL(evt_msg_print_insert, 0, STRING(((char*)str_00004194)), 0, 0, LW(10))
                ELSE
                CALL(evt_msg_print, 0, STRING(((char*)str_000041AC)), 0, 0)
            END_IF
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_mario_get_party, LW(0))
                IF_INT_EQUAL(LW(0), 4)
                    CALL(evt_msg_print, 0, STRING(((char*)str_000041C0)), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING(((char*)str_000041D4)), 0, 0)
                END_IF
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_mario_get_party, LW(0))
                IF_INT_EQUAL(LW(0), 4)
                    CALL(evt_msg_print, 0, STRING(((char*)str_000041E4)), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING(((char*)str_000041FC)), 0, 0)
                END_IF
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_mario_get_party, LW(0))
                    IF_INT_EQUAL(LW(0), 4)
                        CALL(evt_msg_print_insert, 0, STRING(((char*)str_00004210)), 0, 0, LW(10))
                        ELSE
                        CALL(evt_msg_print, 0, STRING(((char*)str_00004224)), 0, 0)
                    END_IF
                    ELSE
                    CALL(evt_mario_get_party, LW(0))
                    IF_INT_EQUAL(LW(0), 4)
                        CALL(evt_msg_print, 0, STRING(((char*)str_000041E4)), 0, 0)
                        ELSE
                        CALL(evt_msg_print, 0, STRING(((char*)str_000041FC)), 0, 0)
                    END_IF
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_kinopiko)
    CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), -490, 0, 25)
    RETURN
EVT_END()

EVT_BEGIN(talk_kinopiko)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_00004234)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)str_00004248)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_0000425C)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING(((char*)str_00004270)), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00004284)), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)str_00004298)), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING(((char*)str_000042AC)), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING(((char*)str_000042C0)), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING(((char*)str_000042D0)), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING(((char*)str_000042E4)), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING(((char*)str_000042D0)), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_kinopio_f)
    CALL(evt_npc_set_position, STRING(((char*)str_000042F4)), 100, 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(talk_kinopio_f)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_00004300)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)str_00004314)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_00004328)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING(((char*)str_0000433C)), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00004350)), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)str_00004364)), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00004378)), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING(((char*)str_0000438C)), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING(((char*)str_0000439C)), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING(((char*)str_000043B0)), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING(((char*)str_0000439C)), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_chu)
    SWITCH(GSW(0))
        CASE_LESS(144)
        CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), 245, 0, 125)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), 0, -1000, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_chu)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING(((char*)str_000043C0)), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING(((char*)str_000043D4)), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING(((char*)str_000043E8)), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING(((char*)str_000043FC)), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00004410)), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING(((char*)str_00004424)), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)str_00004438)), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(init_champ)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), -15, 0, 25)
            CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00003CB0)), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00003CB0)), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

s32 move_pos[] = {
    0, 0, -100, -70, -225, 50, -230, 135,
    -105, 110, 10, -10, 135, 135, 220, 40,
    138, -65, 35, -50, 0, 110, -80, -40,
    110, -40,
};

EVT_BEGIN(move_champ)
    SET_VALUE(LW(10), 0)
    LOOP(0)
        SET_INT_READ_ADDR(PTR(move_pos))
        LOOP(13)
            READ_INT2(LW(0), LW(1))
            CALL(evt_sub_random, 5, LW(0))
            ADD(LW(0), 2)
            MULTIPLY(LW(0), 1000)
            WAIT_MS(LW(0))
            CALL(evt_npc_get_position, STRING(((char*)str_00003CB0)), LW(5), LW(6), LW(7))
            CALL(evt_sub_random, 100, LW(0))
            CALL(evt_sub_random, 100, LW(1))
            SUBTRACT(LW(0), 50)
            ADD(LW(5), LW(0))
            ADD(LW(6), 40)
            SUBTRACT(LW(7), LW(1))
            CALL(evt_msg_toge, 2, LW(5), LW(6), LW(7))
            CALL(evt_end_count, LW(0))
            IF_INT_LESS(LW(0), 10)
                RETURN
            END_IF
            BEGIN_INLINE_EVENT
                SWITCH(LW(10))
                    CASE_EQUAL(0)
                    CALL(evt_msg_print, 0, STRING(((char*)str_0000444C)), 0, 0)
                    CASE_EQUAL(1)
                    CALL(evt_msg_print, 0, STRING(((char*)str_0000445C)), 0, 0)
                    CASE_EQUAL(2)
                    CALL(evt_msg_print, 0, STRING(((char*)str_0000446C)), 0, 0)
                    CASE_EQUAL(3)
                    CALL(evt_msg_print, 0, STRING(((char*)str_0000447C)), 0, 0)
                    CASE_EQUAL(4)
                    CALL(evt_msg_print, 0, STRING(((char*)str_0000448C)), 0, 0)
                    CASE_EQUAL(5)
                    CALL(evt_msg_print, 0, STRING(((char*)str_0000449C)), 0, 0)
                    CASE_EQUAL(6)
                    CALL(evt_msg_print, 0, STRING(((char*)str_000044AC)), 0, 0)
                    CASE_EQUAL(7)
                    CALL(evt_msg_print, 0, STRING(((char*)str_000044BC)), 0, 0)
                    CASE_EQUAL(8)
                    CALL(evt_msg_print, 0, STRING(((char*)str_000044CC)), 0, 0)
                END_SWITCH
            END_INLINE_EVENT
            ADD(LW(10), 1)
            IF_INT_GREATER(LW(10), 8)
                SET_VALUE(LW(10), 0)
            END_IF
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(talk_champ)
    SWITCH(GSW(0))
        CASE_LESS(171)
        CALL(evt_end_count, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_msg_print, 0, STRING(((char*)str_000044DC)), 0, STRING(((char*)str_00003CB0)))
            ELSE
            CALL(evt_msg_print, 0, STRING(((char*)str_000044EC)), 0, STRING(((char*)str_00003CB0)))
        END_IF
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)str_000044FC)), 0, STRING(((char*)str_00003CB0)))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_shikowa)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), -25, 0, 75)
            CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00003CB0)), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00003CB0)), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_shikowa)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        CALL(evt_msg_print, 0, STRING(((char*)str_0000450C)), 0, STRING(((char*)str_00003CB0)))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(init_uranoko)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), -75, 0, 50)
            CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00003CB0)), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00003CB0)), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_uranoko)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        CALL(evt_msg_print, 0, STRING(((char*)str_0000451C)), 0, STRING(((char*)str_00003CB0)))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_ironA)
    CALL(evt_npc_set_scale, STRING(((char*)str_00003CB0)), FLOAT(1.5f), FLOAT(1.5f), FLOAT(1.0f))
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), -30, 0, -50)
            CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00003CB0)), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00003CB0)), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_ironA)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        CALL(evt_msg_print, 0, STRING(((char*)str_0000452C)), 0, STRING(((char*)str_00003CB0)))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_ironB)
    CALL(evt_npc_set_scale, STRING(((char*)str_00003CB0)), FLOAT(1.5f), FLOAT(1.5f), FLOAT(1.0f))
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), -60, 0, -25)
            CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00003CB0)), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00003CB0)), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_ironB)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        CALL(evt_msg_print, 0, STRING(((char*)str_0000453C)), 0, STRING(((char*)str_00003CB0)))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_borodo)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING(((char*)str_00003CB0)), -100, 0, 100)
            CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00003CB0)), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00003CB0)), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_borodo)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        CALL(evt_msg_print, 0, STRING(((char*)str_0000454C)), 0, STRING(((char*)str_00003CB0)))
    END_SWITCH
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"ガードマン１"*/(char*)str_00003CB4, 1074267648, 0, (s32)init_gard1, 0, (s32)talk_gard1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ガードマン２"*/(char*)str_00003CCC,
    1074267648, 0, (s32)init_gard2, 0, (s32)talk_gard2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"マダム"*/(char*)str_0000455C, 1074267648,
    0, (s32)init_madam, 0, (s32)talk_madam, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"レポーター"*/(char*)str_00004564, 1074267648, 0,
    (s32)init_repo, 0, (s32)talk_repo, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"カメラマン１"*/(char*)str_00004570, 1074267648, 0, (s32)init_cam1,
    0, (s32)talk_cam1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"カメラマン２"*/(char*)str_00004580, 1074267648, 0, (s32)init_cam2, 0,
    (s32)talk_cam2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"キノピオ４"*/(char*)str_00004590, 1074267648, 0, (s32)init_kino4, (s32)reg_kino4, (s32)talk_kino4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)/*"キノピオ５"*/(char*)str_0000459C, 1074267648, 0, (s32)init_kino5, 0, (s32)talk_kino5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    (s32)/*"キノピコ"*/(char*)str_000045A8, 1074267648, 0, (s32)init_kinopiko, 0, (s32)talk_kinopiko, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"バッジ屋"*/(char*)str_000045B4,
    1074267648, 0, (s32)init_chu, 0, (s32)talk_chu, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"チャンピョン"*/(char*)str_000045C0, 1074267648,
    0, (s32)init_champ, 0, (s32)talk_champ, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"キノシコワ"*/(char*)str_000045D0, 1074267648, 0,
    (s32)init_shikowa, 0, (s32)talk_shikowa, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"ウラノコ"*/(char*)str_000045DC, 1074267648, 0, (s32)init_uranoko,
    0, (s32)talk_uranoko, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"アイアンＡ"*/(char*)str_000045E8, 1074267648, 0, (s32)init_ironA, 0,
    (s32)talk_ironA, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"アイアンＢ"*/(char*)str_000045F4, 1074267648, 0, (s32)init_ironB, 0, (s32)talk_ironB,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)/*"ボロドー"*/(char*)str_00004600, 1074267648, 0, (s32)init_borodo, 0, (s32)talk_borodo, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(evt_tougi2)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    SET_VALUE(LF(0), 0)
    CALL(evt_bero_get_entername, LW(0))
    IF_STR_EQUAL(LW(0), STRING(((char*)str_00003C68)))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_EQUAL(LF(0), 1)
        CALL(evt_mario_set_pos, -25, 200, -220)
        CALL(evt_party_set_pos, 0, 25, 200, -220)
        ELSE
        CALL(evt_mario_set_pos, -25, 0, -220)
        CALL(evt_party_set_pos, 0, 25, 0, -220)
    END_IF
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_set_dir, 0, 270, -1)
    IF_INT_EQUAL(LF(0), 1)
        CALL(evt_cam3d_evt_set, 0, 290, 190, 0, 238, -158, 0, 11)
        ELSE
        CALL(evt_cam3d_evt_set, 0, 90, 190, 0, 38, -158, 0, 11)
    END_IF
    CALL(evt_seq_wait, 2)
    SET_VALUE(LW(1), 2)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, -180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        IF_INT_EQUAL(LF(0), 1)
            CALL_CHILD(PTR(n_2_door_open))
            ELSE
            CALL_CHILD(PTR(n_1_door_open))
        END_IF
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(2), 100)
        CALL(evt_mario_mov_pos, LW(0), LW(2), 1000)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(2), 100)
        CALL(evt_party_move_pos, 0, LW(0), LW(2), 1000)
    END_INLINE_EVENT
    WAIT_MS(700)
    SET_VALUE(LW(1), 2)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        IF_INT_EQUAL(LF(0), 1)
            CALL_CHILD(PTR(n_2_door_close))
            ELSE
            CALL_CHILD(PTR(n_1_door_close))
        END_IF
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_msg_print_party, STRING(((char*)str_0000460C)))
    CALL(evt_msg_select, 0, STRING(((char*)str_00004618)))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_mario_get_party, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(1)
            CALL(evt_msg_print_add, 0, STRING(((char*)str_00004628)))
            CASE_EQUAL(2)
            CALL(evt_msg_print_add, 0, STRING(((char*)str_00004638)))
            CASE_EQUAL(5)
            CALL(evt_msg_print_add, 0, STRING(((char*)str_00004648)))
        END_SWITCH
        ELSE
        CALL(evt_mario_get_party, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(1)
            CALL(evt_msg_print_add, 0, STRING(((char*)str_00004658)))
            CASE_EQUAL(2)
            CALL(evt_msg_print_add, 0, STRING(((char*)str_00004668)))
            CASE_EQUAL(5)
            CALL(evt_msg_print_add, 0, STRING(((char*)str_00004678)))
        END_SWITCH
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004688)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_000046A0)))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING(((char*)str_000046A8)))
    CALL(evt_msg_print_party, STRING(((char*)str_000046B0)))
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    SET_VALUE(GSWF(2374), 0)
    SET_VALUE(GSW(0), 128)
    CALL(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

s32 ext_fan_data[] = {
    (s32)((char*)str_000046BC), (s32)((char*)str_000046C8), 1073741824, (s32)((char*)str_000046BC), (s32)((char*)str_000046C8), 1086324736, (s32)((char*)str_000046BC), (s32)((char*)str_000046C8),
    1092616192, (s32)((char*)str_000046BC), (s32)((char*)str_000046C8), 1096810496, (s32)((char*)str_000046BC), (s32)((char*)str_000046C8), 1099956224, (s32)((char*)str_000046BC),
    (s32)((char*)str_000046C8), 1102053376, (s32)((char*)str_000046BC), (s32)((char*)str_000046C8), 1104150528, (s32)((char*)str_000046BC), (s32)((char*)str_000046C8), 1106247680,
    (s32)((char*)str_000046BC), (s32)((char*)str_000046C8), 1107820544, (s32)((char*)str_000046D0), (s32)((char*)str_000046DC), 1073741824, (s32)((char*)str_000046D0), (s32)((char*)str_000046DC),
    1086324736, (s32)((char*)str_000046D0), (s32)((char*)str_000046DC), 1092616192, (s32)((char*)str_000046D0), (s32)((char*)str_000046DC), 1096810496, (s32)((char*)str_000046D0),
    (s32)((char*)str_000046DC), 1099956224, (s32)((char*)str_000046D0), (s32)((char*)str_000046DC), 1102053376, (s32)((char*)str_000046D0), (s32)((char*)str_000046DC), 1104150528,
    (s32)((char*)str_000046D0), (s32)((char*)str_000046DC), 1106247680, (s32)((char*)str_000046D0), (s32)((char*)str_000046DC), 1107820544, (s32)((char*)str_000046D0), (s32)((char*)str_000046DC),
    1108869120, (s32)((char*)str_000046E4), (s32)((char*)str_000046F0), 0, (s32)((char*)str_000046E4), (s32)((char*)str_000046F0), 1082130432, (s32)((char*)str_000046E4),
    (s32)((char*)str_000046F0), 1090519040, (s32)((char*)str_000046E4), (s32)((char*)str_000046F0), 1094713344, (s32)((char*)str_000046E4), (s32)((char*)str_000046F0), 1098907648,
    (s32)((char*)str_000046E4), (s32)((char*)str_000046F0), 1101004800, (s32)((char*)str_000046E4), (s32)((char*)str_000046F0), 1103101952, (s32)((char*)str_000046E4), (s32)((char*)str_000046F0),
    1105199104, 0, 0, 0,
};

#ifdef NONMATCHING
void ext_fan_init(void) {
    s32 i;
    ExtPose* pose;
    Fan* fan;

    fan_wp = _mapAlloc(sizeof(FanWork));
    memset(fan_wp, 0, sizeof(FanWork));
    fan_wp->num = extGetPoseNum();
    fan_wp->fans = _mapAlloc(fan_wp->num * sizeof(Fan));
    memset(fan_wp->fans, 0, fan_wp->num * sizeof(Fan));
    pose_init();
    pose = extGetPosePtr();
    fan = fan_wp->fans;
    for (i = 0; i < fan_wp->num; i++, pose++, fan++) {
        pose->flags |= 7;
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = 0.0f;
        pose->mtx[1][3] = 0.0f;
        pose->mtx[2][3] = 0.0f;
        pose->rot = randf(0.0f, 360.0f);
        switch (irand(1000) % 3) {
            case 0:
                pose_change(fan, "c_kinopio", "KNP_W_1");
                break;
            case 1:
                pose_change(fan, "c_kinopiko", "KNF_W_1");
                break;
            case 2:
            default:
                pose_change(fan, "c_jugemu", "JGM_W_1");
                break;
        }
        fan->state = 0;
        {
            Vec pos = {0.0f, 0.0f, 0.0f};

            pos.x = randf(-100.0f, 100.0f);
            pos.z = randf(-100.0f, 100.0f);
            fan->pos = pos;
            fan->vel = (Vec){0.0f, 0.0f, 0.0f};
        }
    }
    fan_wp->sfxId = psndSFXOn_3D("SFX_STG3_AUDIENCE_FAN1\0", &(Vec){0.0f, 0.0f, 0.0f});
    fan_wp->vol = psndSFX_get_vol(fan_wp->sfxId);
}
#endif

#ifdef NONMATCHING
void fan_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}
#endif

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING  // restored C definition (nmrepair)
static __declspec(section ".rodata") Vec fan_zero = {0.0f, 0.0f, 0.0f};
#endif
#ifdef NONMATCHING
void ext_fan_main(void) {
    MarioWork* mario = marioGetPtr();
    Vec dir;
    Vec target = {0.0f, 0.0f, 0.0f};
    Fan* fan;
    ExtPose* pose;
    s32 i;

    if (mario->currMotionId == 0x12) {
        fan_wp->hammerTimer++;
    } else {
        fan_wp->hammerTimer = 0;
    }
    if (evtGetValue(NULL, GF(10))) {
        ExtPose* pose = extGetPosePtr();
        Fan* fan = fan_wp->fans;

        for (i = 0; i < fan_wp->num; i++, fan++, pose++) {
            if (fan->state == 0) {
                fan->pos = mario->position;
                target = fan->pos;
                pose->flags &= ~1;
                fan->flags |= 1;
                break;
            }
        }
    } else {
        s32 i;
        s32 found = 0;

        pose = extGetPosePtr();
        fan = fan_wp->fans;

        for (i = 0; i < fan_wp->num; i++, fan++, pose++) {
            if (fan->state == 0) {
                if (!found) {
                    found = 1;
                    fan->pos = mario->position;
                    pose->flags &= ~1;
                    fan->flags |= 1;
                } else {
                    fan->pos = npcNameToPtr("\203`\203\203\203\223\203s\203\207\203\223")->position;
                    target = fan->pos;
                    pose->flags &= ~1;
                    fan->flags |= 1;
                    break;
                }
            }
        }
    }

    {

        Fan* fan;
        s32 i;

        for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
            if (fan->state == 0) {
                PSVECSubtract(&target, &fan->pos, &dir);
                if (PSVECMag(&dir)) {
                    PSVECNormalize(&dir, &dir);
                    dir.y = 0.0f;
                    PSVECScale(&dir, &dir, 0.1f);
                    PSVECAdd(&fan->vel, &dir, &fan->vel);
                }
            }
        }
    }

    {

        for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
            if (fan->state == 0) {
                s32 j;
                Fan* other;

                for (j = 0, other = fan_wp->fans; j < fan_wp->num; j++, other++) {
                    if (other->state == 0 && i != j && PSVECSquareDistance(&fan->pos, &other->pos) < 900.0f) {
                        PSVECSubtract(&fan->pos, &other->pos, &dir);
                        dir.y = 0.0f;
                        PSVECNormalize(&dir, &dir);
                        PSVECScale(&dir, &dir, 5.0f);
                        PSVECAdd(&fan->vel, &dir, &fan->vel);
                        PSVECSubtract(&other->vel, &dir, &other->vel);
                    }
                }
            }
        }
    }

    {
        const char* sfx2;
        const char* sfx1;
        f32 angle;
        f32 dist;
        f32 dy;
        f32 spd;
        f32 x;
        f32 z;
        f32 dir2;
        sfx2 = sfx1 = "SFX_STG3_AUDIENCE_FAN_FLY1";
        for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
            if (fan->state == 0) {
                switch (check_hammer(fan)) {
                    case 0:
                        break;
                    case 1:
                        fan->state = 10;
                        dist = 6.2831855f; angle = 6.2831855f * randf(135.0f, 225.0f) / 360.0f;
                        dist = randf(400.0f, 500.0f);
                        x = fan->pos.x + dist * fan_sin(angle);
                        z = fan->pos.z - dist * fan_cos(angle);
                        {
                            Vec tgt = {0.0f, 0.0f, 0.0f};

                            tgt.x = x;
                            tgt.y = -100.0f;
                            tgt.z = z;
                            fan->target = tgt;
                        }
                        fan->param.y = randf(4.0f, 6.0f);
                        fan->param.z = randf(0.1f, 0.2f);
                        dy = fan->target.y - fan->pos.y;
                        dist = distABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                        angleABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                        fan->timer = dist / fan->param.y;
                        fan->param.x = dy / fan->timer + fan->param.z * fan->timer / 2.0f;
                        psndSFXOn_3D(sfx1, &fan->pos);
                        break;
                    case 2: {

                        angle = angleABf(mario->position.x, mario->position.z, fan->pos.x, fan->pos.z);
                        dir2 = cloudGetBreathDir();
                        fan->state = 20;
                        fan->target = fan_zero;
                        angle = (angle + dir2) / 2.0f;
                        spd = randf(0.1f, 0.2f);
                        angle = 6.2831855f * angle / 360.0f;
                        fan->param.x = spd * fan_sin(angle);
                        fan->param.y = randf(0.03f, 0.06f);
                        fan->param.z = spd * -fan_cos(angle);
                        fan->timer = 120;
                        psndSFXOn_3D(sfx2, &fan->pos);
                        break;
                    }
                }
            }
        }
    }
    fan_wp->count = fan_wp->num;

    {
        f32 angle;
        f32 dist;
        f32 h;

        pose = extGetPosePtr();
        fan = fan_wp->fans;
        for (i = 0; i < fan_wp->num; i++, pose++, fan++) {
            switch (fan->state) {
                case 0: {
                    HitCheckQuery query;
                    HitCheckQuery* q = &query;
                    PSVECNormalize(&fan->vel, &fan->vel);
                    dist = PSVECMag(&fan->vel);
                    query.targetPos = fan->pos;
                    query.targetPos.y += 4.0f;
                    query.targetDir = fan->vel;
                    query.targetDir.y = 0.0f;
                    query.targetDistance = 25.0f + dist;
                    if (hitCheckVecFilter(&query, NULL)) {
                        C_VECReflect(&fan->vel, &q->hitNormal, &fan->vel);
                    } else {
                        fan->pos.x += fan->vel.x;
                        fan->pos.z += fan->vel.z;
                        fan->vel.x *= 0.6f;
                        fan->vel.z *= 0.6f;
                    }
                    if (fan->pos.x < -350.0f) {
                        fan->pos.x = -350.0f;
                    }
                    if (fan->pos.x > 350.0f) {
                        fan->pos.x = 350.0f;
                    }
                    if (fan->pos.z > (h = 195.0f + i / 100.0f)) {
                        fan->pos.z = h;
                    }
                    break;
                }
                case 10:
                    fan->pos.y += fan->param.x;
                    fan->param.x -= fan->param.z;
                    angle = angleABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                    angle = 6.2831855f * angle / 360.0f;
                    fan->pos.x += fan->param.y * fan_sin(angle);
                    fan->pos.z += fan->param.y * -fan_cos(angle);
                    if (--fan->timer < 0) {
                        fan->state = 100;
                    }
                    break;
                case 20:
                    if (--fan->timer > 0) {
                        fan->target.x += fan->param.x;
                        fan->target.y += fan->param.y;
                        fan->target.z += fan->param.z;
                        fan->pos.x += fan->target.x;
                        fan->pos.y += fan->target.y;
                        fan->pos.z += fan->target.z;
                    } else {
                        fan->state = 100;
                    }
                    break;
                case 100:
                    pose->flags &= ~3;
                    fan->state++;
                    break;
                case 101:
                    break;
            }
            if (fan->flags & 1) {
                fan_wp->count--;
            } else if (fan->state != 0) {
                fan_wp->count--;
            }
            pose->mtx[0][3] = fan->pos.x;
            pose->mtx[1][3] = fan->pos.y;
            pose->mtx[2][3] = fan->pos.z;
            pose->rot = angleABf(target.x, target.z, fan->pos.x, fan->pos.z);
        }
    }
    psndSFX_pos(fan_wp->sfxId, &target);
    psndSFX_vol(fan_wp->sfxId, fan_wp->vol * fan_wp->count / fan_wp->num);
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

EVT_BEGIN(mario_momikucha_msg)
    SET_VALUE(LW(10), 0)
    LOOP(0)
        CALL(evt_sub_random, 5, LW(0))
        ADD(LW(0), 2)
        MULTIPLY(LW(0), 1000)
        WAIT_MS(LW(0))
        CALL(evt_sub_random, 200, LW(0))
        CALL(evt_sub_random, 200, LW(1))
        SUBTRACT(LW(0), 50)
        SUBTRACT(LW(1), 50)
        CALL(evt_msg_toge, 2, LW(0), 30, LW(1))
        CALL(evt_end_count, LW(0))
        IF_INT_LESS(LW(0), 10)
            RETURN
        END_IF
        BEGIN_INLINE_EVENT
            SWITCH(LW(10))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING(((char*)str_00004740)), 0, 0)
                CASE_EQUAL(1)
                CALL(evt_msg_print, 0, STRING(((char*)str_00004750)), 0, 0)
                CASE_EQUAL(2)
                CALL(evt_msg_print, 0, STRING(((char*)str_00004760)), 0, 0)
                CASE_EQUAL(3)
                CALL(evt_msg_print, 0, STRING(((char*)str_00004770)), 0, 0)
                CASE_EQUAL(4)
                CALL(evt_msg_print, 0, STRING(((char*)str_00004780)), 0, 0)
                CASE_EQUAL(5)
                CALL(evt_msg_print, 0, STRING(((char*)str_00004790)), 0, 0)
            END_SWITCH
        END_INLINE_EVENT
        ADD(LW(10), 1)
        IF_INT_GREATER(LW(10), 5)
            SET_VALUE(LW(10), 0)
        END_IF
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_momikucha)
    SET_VALUE(LF(0), 0)
    SET_VALUE(GF(10), 0)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 133)
        IF_INT_EQUAL(GSWF(2402), 0)
            SET_VALUE(GSWF(2402), 1)
            SET_VALUE(LF(0), 1)
            SET_VALUE(GF(10), 0)
        END_IF
    END_IF
    CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        IF_INT_EQUAL(GSWF(2403), 0)
            SET_VALUE(GSWF(2403), 1)
            SET_VALUE(LF(0), 1)
            SET_VALUE(GF(10), 1)
        END_IF
    END_IF
    IF_INT_EQUAL(LF(0), 0)
        RETURN
    END_IF
    CALL(evt_npc_entry, STRING(((char*)str_000047A0)), STRING(((char*)str_000046BC)))
    CALL(evt_npc_entry, STRING(((char*)str_000047A4)), STRING(((char*)str_000046D0)))
    CALL(evt_npc_entry, STRING(((char*)str_000047AC)), STRING(((char*)str_000046E4)))
    CALL(evt_npc_set_position, STRING(((char*)str_000047A0)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_000047A4)), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_000047AC)), 0, -1000, 0)
    CALL(evt_ext_entry, 200, PTR(ext_fan_data), PTR(ext_fan_init), PTR(ext_fan_main), PTR(ext_fan_dispent))
    IF_INT_EQUAL(GF(10), 0)
        CALL(evt_npc_set_position, STRING(((char*)str_000045C0)), 0, 0, 0)
        CALL(evt_npc_change_interrupt, STRING(((char*)str_000045C0)), 1, PTR(move_champ))
        ELSE
        SPAWN_EVENT(PTR(mario_momikucha_msg))
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(evt_key)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_party_yoshi_ride, 0, 0)
    SET_VALUE(GSW(0), 154)
    CALL(evt_item_get_item_end_wait, STRING(((char*)str_000047B4)))
    CALL(evt_party_stop, 0)
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING(((char*)str_000047B8)))
    WAIT_MS(500)
    BEGIN_INLINE_EVENT_GET_ID(LW(11))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_000047C8)), LW(0), LW(1), LW(2), 0)
        CALL(evt_eff_fukidashi, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(1500)
    END_INLINE_EVENT
    CALL(evt_snd_bgmoff, 1024)
    CALL(evt_snd_bgmon, 1, STRING(((char*)str_000047E0)))
    SPAWN_EVENT_GET_ID(PTR(evt_sub_mail_vibration), LW(10))
    WAIT_MS(500)
    LOOP(0)
        IS_EVENT_RUNNING(LW(11), LW(12))
        IF_INT_EQUAL(LW(12), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_bikkuri)
    LOOP(0)
        CALL(evt_key_get_buttontrg, 0, LW(0))
        IF_INT_EQUAL(LW(0), 256)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_off)
    CALL(evt_snd_bgmoff, 513)
    CALL(evt_snd_bgmon, 288, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000047F8)), LW(0), LW(1), LW(2), 0)
    DELETE_EVENT(LW(10))
    WAIT_FRAMES(1)
    CALL(evt_sub_rumble_onoff, 1, 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_0000480C)))
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004814)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_00004828)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)str_00004830)), 0, 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_000046A8)))
    CALL(evt_pouch_receive_mail, 15)
    CALL(evt_pouch_open_mail, 15)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

#ifdef NONMATCHING
void ext_fan_dispent(void) {
    pose_main();
    dispEntry(CAMERA_3D, 0.0f, 1, fan_disp, NULL);
}
#endif

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING
s32 check_hammer(Fan* fan) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;
    f32 rot;
    f32 x;
    f32 z;
    f32 angle;
    f32 dist;
    Vec pos;

    if (mario->position.y > 0.0f) {
        return 0;
    }
    if (fan->flags & 1) {
        return 0;
    }
    if (mario->currMotionId == 0x12 && fan_wp->hammerTimer > 10) {
        rot = 6.2831855f * reviseAngle(mario->displayDirection - 90.0f + camGetPtr(CAMERA_3D)->viewYaw) / 360.0f;

        x = mario->position.x + 35.0f * fan_sin(rot);
        z = mario->position.z - 35.0f * fan_cos(rot);
        if (distABf(fan->pos.x, fan->pos.z, x, z) < 35.0f) {
            return 1;
        }
    }
    if (mario->currMotionId == 0x13 && (s32)mario->currSubMotionId == 0x14 && PSVECDistance(&mario->position, &fan->pos) < 65.0f) {
        return 1;
    }
    party = partyGetPtr(0);
    if (party != NULL && party->currentMemberId == 5 && (party->flags & 0x100)) {
        angle = 6.2831855f * cloudGetBreathDir() / 360.0f;
        dist = cloudGetBreathDist();
        pos.x = party->position.x + dist * fan_sin(angle);
        pos.y = party->position.y;
        pos.z = party->position.z - dist * fan_cos(angle);
        if (angle >= 0.0f && PSVECDistance(&pos, &fan->pos) < 30.0f) {
            return 2;
        }
    }
    return 0;
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

#ifdef NONMATCHING
s32 evt_end_count(EventEntry* event, BOOL isFirstCall) {
    evtSetValue(event, event->args[0], fan_wp->count);
    return EVT_RETURN_DONE;
}
#endif

__declspec(section ".data") static EVT_BEGIN(evt_poster_1)
    SET_VALUE(GSWF(2456), 1)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_poster_2)
    SET_VALUE(GSWF(2457), 1)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_poster_3)
    SET_VALUE(GSWF(2458), 1)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_poster_4)
    SET_VALUE(GSWF(2459), 1)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_poster_5)
    SET_VALUE(GSWF(2460), 1)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_poster_6)
    SET_VALUE(GSWF(2461), 1)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_poster_7)
    SET_VALUE(GSWF(2462), 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_poster_8)
    SET_VALUE(GSWF(2463), 1)
    IF_INT_EQUAL(GSW(0), 153)
        CALL(evt_mapobj_get_position, STRING(((char*)str_00004840)), LW(0), LW(1), LW(2))
        CALL(evt_item_entry, STRING(((char*)str_000047B4)), 19, LW(0), LW(1), LW(2), 4, -1, PTR(evt_key))
        CALL(evt_item_set_move_dir_speed, STRING(((char*)str_000047B4)), FLOAT(180.0f), FLOAT(90.0f))
        CALL(evt_item_set_gravity, STRING(((char*)str_000047B4)), FLOAT(1.0f))
        CALL(evt_item_set_bound_rate, STRING(((char*)str_000047B4)), FLOAT(0.5996094f))
        CALL(evt_item_set_jump_power, STRING(((char*)str_000047B4)), FLOAT(500.0f))
        CALL(evt_item_status_on, STRING(((char*)str_000047B4)), 16)
    END_IF
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_poster_9)
    SET_VALUE(GSWF(2464), 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_after_peach)
    CALL(evt_cam3d_evt_set, 0, 120, 494, 0, 40, 0, 0, 11)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_dir, 0, 270, 0)
    CALL(evt_mario_set_pos, 25, 0, 75)
    CALL(evt_party_set_pos, 0, 60, 0, 100)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00003BE0)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00003BD4)), 1)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_fade_end_wait)
    WAIT_MS(2000)
    CALL(evt_msg_print, 0, STRING(((char*)str_00004848)), 0, STRING(((char*)str_000045D0)))
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004688)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_000046A0)))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING(((char*)str_000046A8)))
    CALL(evt_cam3d_evt_set, 0, 100, 395, 0, 40, 0, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)str_0000485C)), 0, STRING(((char*)str_000045D0)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -40, 100, 395, -40, 40, 0, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)str_00004870)), 0, STRING(((char*)str_000045C0)))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00004884)), 0, STRING(((char*)str_000045DC)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 100, 395, 0, 40, 0, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)str_00004898)), 0, STRING(((char*)str_000045D0)))
    WAIT_MS(300)
    CALL(evt_mario_set_pose, STRING(((char*)str_000048AC)))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING(((char*)str_000046A8)))
    CALL(evt_cam3d_evt_set, 0, 120, 494, 0, 40, 0, 500, 11)
    CALL(evt_party_run, 0)
    CALL(evt_mario_mov_pos2, 0, 190, FLOAT(80.0f))
    CALL(evt_bero_mapchange, STRING(((char*)str_00003C34)), STRING(((char*)str_00003C3C)))
    RETURN
EVT_END()

EVT_BEGIN(tou_02_init_evt)
    SWITCH(GSW(0))
        CASE_BETWEEN(127, 137)
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_000048B4)))
        CALL(evt_snd_envon, 272, STRING(((char*)str_000048C4)))
        CALL(evt_snd_bgmoff, 26624)
        CASE_GREATER_OR_EQUAL(165)
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_000048B4)))
        CALL(evt_snd_envon, 272, STRING(((char*)str_000048C4)))
        CALL(evt_snd_bgmoff, 26624)
        CASE_DEFAULT
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_000048D4)))
        CALL(evt_snd_bgmon, 160, 0)
        CALL(evt_snd_envon, 272, STRING(((char*)str_000048C4)))
    END_SWITCH
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    IF_INT_EQUAL(GSWF(2374), 1)
        CALL_CHILD(PTR(bero_case_entry))
        SPAWN_EVENT(PTR(evt_tougi2))
        ELSE
        CALL_CHILD(PTR(evt_bero_info_run))
    END_IF
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL_CHILD(PTR(init_kinopio_f))
    CALL(evt_npc_change_interrupt, STRING(((char*)str_000042F4)), 6, PTR(talk_kinopio_f))
    CALL(evt_mobj_kururing_floor, STRING(((char*)str_000048E4)), -260, 0, -120, STRING(((char*)str_000048F0)), 125, GSWF(5623))
    IF_INT_LESS(GSW(0), 129)
        SET_VALUE(LW(0), 3)
        CALL_CHILD(PTR(bero_case_switch_off))
        SET_VALUE(LW(0), 4)
        CALL_CHILD(PTR(bero_case_switch_off))
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(0), 172)
        IF_INT_EQUAL(GSWF(2497), 0)
            SET_VALUE(LW(0), 3)
            CALL_CHILD(PTR(bero_case_switch_off))
            SET_VALUE(LW(0), 4)
            CALL_CHILD(PTR(bero_case_switch_off))
        END_IF
    END_IF
    IF_INT_EQUAL(GSW(0), 171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING(((char*)str_000042F4)), 0, -1000, 0)
            CALL(evt_npc_set_position, STRING(((char*)str_00004590)), 0, -1000, 0)
        END_IF
    END_IF
    IF_INT_EQUAL(GSW(0), 171)
        CALL(evt_mario_get_party, LW(15))
        IF_INT_EQUAL(LW(15), 0)
            CALL(evt_mario_set_party, 0, 1)
            CALL(evt_party_run, 0)
            CALL(evt_pouch_mario_recovery)
            CALL(evt_pouch_all_party_recovery)
        END_IF
        CALL(evt_pouch_remove_item, 65, LW(0))
        SPAWN_EVENT(PTR(evt_after_peach))
        SET_VALUE(GSWF(2402), 1)
        SET_VALUE(GSWF(2403), 1)
    END_IF
    CALL(evt_map_playanim, STRING(((char*)str_000048F8)), 1, 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            LOOP(0)
                CALL(evt_map_checkanim, STRING(((char*)str_000048F8)), LW(0), LW(1))
                IF_INT_LESS(LW(1), 5333)
                    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004904)), 178, 0, -98, 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            WAIT_FRAMES(10)
            CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004920)), 178, 0, -98, 0)
            LOOP(0)
                CALL(evt_map_checkanim, STRING(((char*)str_000048F8)), LW(0), LW(1))
                IF_INT_LESS(LW(1), 2000)
                    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004904)), 178, 0, -98, 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            WAIT_FRAMES(5)
            CALL(evt_snd_sfxon_3d, STRING(((char*)str_00004920)), 178, 0, -98, 0)
            LOOP(0)
                CALL(evt_map_checkanim, STRING(((char*)str_000048F8)), LW(0), LW(1))
                IF_INT_GREATER(LW(1), 6333)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
        END_LOOP
    END_INLINE_EVENT
    CALL_CHILD(PTR(evt_momikucha))
    CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
    SWITCH(LW(0))
        CASE_LESS(2)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_0000493C)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00004944)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_0000494C)), 1)
        CALL(evt_hitobj_onoff, STRING(((char*)str_00004954)), 1, 0)
        CALL(evt_hitobj_onoff, STRING(((char*)str_0000495C)), 1, 1)
        CALL(evt_cloud_init)
        IF_INT_EQUAL(GSWF(2457), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)str_00004964)), STRING(((char*)str_0000496C)), PTR(evt_poster_2))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)str_00004964)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)str_0000496C)), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2458), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)str_00004974)), STRING(((char*)str_0000497C)), PTR(evt_poster_3))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)str_00004974)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)str_0000497C)), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2459), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)str_00004984)), STRING(((char*)str_0000498C)), PTR(evt_poster_4))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)str_00004984)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)str_0000498C)), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2460), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)str_00004994)), STRING(((char*)str_0000499C)), PTR(evt_poster_5))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)str_00004994)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)str_0000499C)), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2461), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)str_000049A4)), STRING(((char*)str_000049AC)), PTR(evt_poster_6))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)str_000049A4)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)str_000049AC)), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2462), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)str_000049B4)), STRING(((char*)str_000049BC)), PTR(evt_poster_7))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)str_000049B4)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)str_000049BC)), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2463), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)str_00004840)), STRING(((char*)str_000049C4)), PTR(evt_poster_8))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)str_00004840)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)str_000049C4)), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2464), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)str_000049CC)), STRING(((char*)str_000049D4)), PTR(evt_poster_9))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)str_000049CC)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)str_000049D4)), 1, 0)
        END_IF
        CASE_LESS(11)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_0000493C)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00004944)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_0000494C)), 1)
        CALL(evt_hitobj_onoff, STRING(((char*)str_00004954)), 1, 1)
        CALL(evt_hitobj_onoff, STRING(((char*)str_0000495C)), 1, 0)
        CALL(evt_cloud_init)
        IF_INT_EQUAL(GSWF(2456), 0)
            CALL(evt_cloud_ent, 0, STRING(((char*)str_000049DC)), STRING(((char*)str_000049E4)), PTR(evt_poster_1))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING(((char*)str_000049DC)), 1)
            CALL(evt_hitobj_onoff, STRING(((char*)str_000049E4)), 1, 0)
        END_IF
        CASE_DEFAULT
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_0000493C)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00004944)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_0000494C)), 1)
        CALL(evt_hitobj_onoff, STRING(((char*)str_00004954)), 1, 0)
        CALL(evt_hitobj_onoff, STRING(((char*)str_0000495C)), 1, 0)
    END_SWITCH
    IF_INT_EQUAL(GSWF(2463), 1)
        IF_INT_EQUAL(GSW(0), 153)
            CALL(evt_item_entry, STRING(((char*)str_000047B4)), 19, -110, 200, -180, 16, -1, PTR(evt_key))
        END_IF
    END_IF
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000049EC)), 2)
    RETURN
EVT_END()

#ifndef NONMATCHING
// FAKE (asm stopgap, asmfake.py --whole): pose_init (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
#pragma force_active on
__declspec(section ".rodata") const char str_00003BC0[] = "SFX_STG3_AUTO_DOOR1";
__declspec(section ".rodata") const char str_00003BD4[] = "door_1_b\000\000\000";
__declspec(section ".rodata") const char str_00003BE0[] = "door_1_a\000\000\000";
__declspec(section ".rodata") const char str_00003BEC[] = "door_2_b\000\000\000";
__declspec(section ".rodata") const char str_00003BF8[] = "door_2_a\000\000\000";
__declspec(section ".rodata") const char str_00003C04[] = "door_3_b\000\000\000";
__declspec(section ".rodata") const char str_00003C10[] = "door_3_a\000\000\000";
__declspec(section ".rodata") const char str_00003C1C[] = "door_4\000";
__declspec(section ".rodata") const char str_00003C24[] = "door_5\000";
__declspec(section ".rodata") const char str_00003C2C[] = "s_bero\000";
__declspec(section ".rodata") const char str_00003C34[] = "tou_01\000";
__declspec(section ".rodata") const char str_00003C3C[] = "a_door_mon\000";
__declspec(section ".rodata") const char str_00003C48[] = "n_bero_1\000\000\000";
__declspec(section ".rodata") const char str_00003C54[] = "tou_03\000";
__declspec(section ".rodata") const char str_00003C5C[] = "s_bero_1\000\000\000";
__declspec(section ".rodata") const char str_00003C68[] = "n_bero_2\000\000\000";
__declspec(section ".rodata") const char str_00003C74[] = "s_bero_2\000\000\000";
__declspec(section ".rodata") const char str_00003C80[] = "n_bero_3\000\000\000";
__declspec(section ".rodata") const char str_00003C8C[] = "tou_04\000";
__declspec(section ".rodata") const char str_00003C94[] = "e_bero\000";
__declspec(section ".rodata") const char str_00003C9C[] = "n_bero_4\000\000\000";
__declspec(section ".rodata") const char str_00003CA8[] = "w_bero\000";
__declspec(section ".rodata") const char str_00003CB0[] = "me\000";
__declspec(section ".rodata") const char str_00003CB4[] = "\203K\201[\203h\203}\203\223\202P\000\000\000";
__declspec(section ".rodata") const char str_00003CC4[] = "mario\000\000";
__declspec(section ".rodata") const char str_00003CCC[] = "\203K\201[\203h\203}\203\223\202Q\000\000\000";
__declspec(section ".rodata") const char str_00003CDC[] = "stg3_tou_24";
__declspec(section ".rodata") const char str_00003CE8[] = "stg3_tou_37";
__declspec(section ".rodata") const char str_00003CF4[] = "stg3_tou_37_01\000";
__declspec(section ".rodata") const char str_00003D04[] = "stg3_tou_37_02\000";
__declspec(section ".rodata") const char str_00003D14[] = "stg3_tou_re_002_1\000\000";
__declspec(section ".rodata") const char str_00003D28[] = "stg3_tou_re_001";
__declspec(section ".rodata") const char str_00003D38[] = "stg3_tou_re_002";
__declspec(section ".rodata") const char str_00003D48[] = "stg3_npc_02_01_01\000\000";
__declspec(section ".rodata") const char str_00003D5C[] = "stg3_npc_02_01_02\000\000";
__declspec(section ".rodata") const char str_00003D70[] = "stg3_npc_02_01_03\000\000";
__declspec(section ".rodata") const char str_00003D84[] = "stg3_npc_02_01_04\000\000";
__declspec(section ".rodata") const char str_00003D98[] = "stg3_npc_02_01_05\000\000";
__declspec(section ".rodata") const char str_00003DAC[] = "stg3_npc_02_01_06\000\000";
__declspec(section ".rodata") const char str_00003DC0[] = "stg3_npc_02_01_07\000\000";
__declspec(section ".rodata") const char str_00003DD4[] = "stg3_npc_02_02_01\000\000";
__declspec(section ".rodata") const char str_00003DE8[] = "stg3_npc_02_02_02\000\000";
__declspec(section ".rodata") const char str_00003DFC[] = "stg3_npc_02_02_03\000\000";
__declspec(section ".rodata") const char str_00003E10[] = "stg3_npc_02_02_04\000\000";
__declspec(section ".rodata") const char str_00003E24[] = "stg3_npc_02_02_05\000\000";
__declspec(section ".rodata") const char str_00003E38[] = "stg3_npc_02_02_06\000\000";
__declspec(section ".rodata") const char str_00003E4C[] = "stg3_npc_02_02_07\000\000";
__declspec(section ".rodata") const char str_00003E60[] = "stg3_npc_re_024";
__declspec(section ".rodata") const char str_00003E70[] = "stg3_npc_re_024_1\000\000";
__declspec(section ".rodata") const char str_00003E84[] = "stg3_npc_re_023";
__declspec(section ".rodata") const char str_00003E94[] = "stg3_npc_02_03_01\000\000";
__declspec(section ".rodata") const char str_00003EA8[] = "stg3_npc_02_03_02\000\000";
__declspec(section ".rodata") const char str_00003EBC[] = "stg3_npc_02_03_03\000\000";
__declspec(section ".rodata") const char str_00003ED0[] = "stg3_npc_02_03_04\000\000";
__declspec(section ".rodata") const char str_00003EE4[] = "stg3_npc_02_03_05\000\000";
__declspec(section ".rodata") const char str_00003EF8[] = "stg3_npc_02_03_06\000\000";
__declspec(section ".rodata") const char str_00003F0C[] = "stg3_npc_02_03_07\000\000";
__declspec(section ".rodata") const char str_00003F20[] = "stg3_npc_re_026";
__declspec(section ".rodata") const char str_00003F30[] = "stg3_npc_re_026_1\000\000";
__declspec(section ".rodata") const char str_00003F44[] = "stg3_npc_re_025";
__declspec(section ".rodata") const char str_00003F54[] = "stg3_npc_02_04_01\000\000";
__declspec(section ".rodata") const char str_00003F68[] = "stg3_npc_02_04_02\000\000";
__declspec(section ".rodata") const char str_00003F7C[] = "stg3_npc_02_04_03\000\000";
__declspec(section ".rodata") const char str_00003F90[] = "stg3_npc_02_04_04\000\000";
__declspec(section ".rodata") const char str_00003FA4[] = "stg3_npc_02_04_05\000\000";
__declspec(section ".rodata") const char str_00003FB8[] = "stg3_npc_02_04_06\000\000";
__declspec(section ".rodata") const char str_00003FCC[] = "stg3_npc_02_04_07\000\000";
__declspec(section ".rodata") const char str_00003FE0[] = "stg3_npc_re_028";
__declspec(section ".rodata") const char str_00003FF0[] = "stg3_npc_re_028_1\000\000";
__declspec(section ".rodata") const char str_00004004[] = "stg3_npc_re_027";
__declspec(section ".rodata") const char str_00004014[] = "stg3_npc_02_05_01\000\000";
__declspec(section ".rodata") const char str_00004028[] = "stg3_npc_02_05_02\000\000";
__declspec(section ".rodata") const char str_0000403C[] = "stg3_npc_02_05_03\000\000";
__declspec(section ".rodata") const char str_00004050[] = "stg3_npc_02_05_04\000\000";
__declspec(section ".rodata") const char str_00004064[] = "stg3_npc_02_05_05\000\000";
__declspec(section ".rodata") const char str_00004078[] = "stg3_npc_02_05_06\000\000";
__declspec(section ".rodata") const char str_0000408C[] = "stg3_npc_02_05_07\000\000";
__declspec(section ".rodata") const char str_000040A0[] = "stg3_npc_re_030";
__declspec(section ".rodata") const char str_000040B0[] = "stg3_npc_re_030_1\000\000";
__declspec(section ".rodata") const char str_000040C4[] = "stg3_npc_re_029";
__declspec(section ".rodata") const char str_000040D4[] = "stg3_npc_02_06_01\000\000";
__declspec(section ".rodata") const char str_000040E8[] = "stg3_npc_02_06_02\000\000";
__declspec(section ".rodata") const char str_000040FC[] = "stg3_npc_02_06_03\000\000";
__declspec(section ".rodata") const char str_00004110[] = "stg3_npc_02_06_04_yos\000\000";
__declspec(section ".rodata") const char str_00004128[] = "stg3_npc_02_06_04\000\000";
__declspec(section ".rodata") const char str_0000413C[] = "stg3_npc_02_06_05_yos\000\000";
__declspec(section ".rodata") const char str_00004154[] = "stg3_npc_02_06_05\000\000";
__declspec(section ".rodata") const char str_00004168[] = "stg3_npc_02_06_06_yos\000\000";
__declspec(section ".rodata") const char str_00004180[] = "stg3_npc_02_06_06\000\000";
__declspec(section ".rodata") const char str_00004194[] = "stg3_npc_02_06_07_yos\000\000";
__declspec(section ".rodata") const char str_000041AC[] = "stg3_npc_02_06_07\000\000";
__declspec(section ".rodata") const char str_000041C0[] = "stg3_npc_re_032_yos";
__declspec(section ".rodata") const char str_000041D4[] = "stg3_npc_re_032";
__declspec(section ".rodata") const char str_000041E4[] = "stg3_npc_re_032_1_yos\000\000";
__declspec(section ".rodata") const char str_000041FC[] = "stg3_npc_re_032_1\000\000";
__declspec(section ".rodata") const char str_00004210[] = "stg3_npc_re_031_yos";
__declspec(section ".rodata") const char str_00004224[] = "stg3_npc_re_031";
__declspec(section ".rodata") const char str_00004234[] = "stg3_npc_02_07_01\000\000";
__declspec(section ".rodata") const char str_00004248[] = "stg3_npc_02_07_02\000\000";
__declspec(section ".rodata") const char str_0000425C[] = "stg3_npc_02_07_03\000\000";
__declspec(section ".rodata") const char str_00004270[] = "stg3_npc_02_07_04\000\000";
__declspec(section ".rodata") const char str_00004284[] = "stg3_npc_02_07_05\000\000";
__declspec(section ".rodata") const char str_00004298[] = "stg3_npc_02_07_06\000\000";
__declspec(section ".rodata") const char str_000042AC[] = "stg3_npc_02_07_07\000\000";
__declspec(section ".rodata") const char str_000042C0[] = "stg3_npc_re_034";
__declspec(section ".rodata") const char str_000042D0[] = "stg3_npc_re_034_1\000\000";
__declspec(section ".rodata") const char str_000042E4[] = "stg3_npc_re_033";
__declspec(section ".rodata") const char str_000042F4[] = "\203L\203m\203s\203I\217\227\000";
__declspec(section ".rodata") const char str_00004300[] = "stg3_npc_02_08_01\000\000";
__declspec(section ".rodata") const char str_00004314[] = "stg3_npc_02_08_02\000\000";
__declspec(section ".rodata") const char str_00004328[] = "stg3_npc_02_08_03\000\000";
__declspec(section ".rodata") const char str_0000433C[] = "stg3_npc_02_08_04\000\000";
__declspec(section ".rodata") const char str_00004350[] = "stg3_npc_02_08_05\000\000";
__declspec(section ".rodata") const char str_00004364[] = "stg3_npc_02_08_06\000\000";
__declspec(section ".rodata") const char str_00004378[] = "stg3_npc_02_08_07\000\000";
__declspec(section ".rodata") const char str_0000438C[] = "stg3_npc_re_036";
__declspec(section ".rodata") const char str_0000439C[] = "stg3_npc_re_036_1\000\000";
__declspec(section ".rodata") const char str_000043B0[] = "stg3_npc_re_035";
__declspec(section ".rodata") const char str_000043C0[] = "stg3_npc_02_10_01\000\000";
__declspec(section ".rodata") const char str_000043D4[] = "stg3_npc_02_10_02\000\000";
__declspec(section ".rodata") const char str_000043E8[] = "stg3_npc_02_10_03\000\000";
__declspec(section ".rodata") const char str_000043FC[] = "stg3_npc_02_10_04\000\000";
__declspec(section ".rodata") const char str_00004410[] = "stg3_npc_02_10_05\000\000";
__declspec(section ".rodata") const char str_00004424[] = "stg3_npc_02_10_06\000\000";
__declspec(section ".rodata") const char str_00004438[] = "stg3_npc_02_10_07\000\000";
__declspec(section ".rodata") const char str_0000444C[] = "stg3_tou_182\000\000\000";
__declspec(section ".rodata") const char str_0000445C[] = "stg3_tou_183\000\000\000";
__declspec(section ".rodata") const char str_0000446C[] = "stg3_tou_184\000\000\000";
__declspec(section ".rodata") const char str_0000447C[] = "stg3_tou_185\000\000\000";
__declspec(section ".rodata") const char str_0000448C[] = "stg3_tou_186\000\000\000";
__declspec(section ".rodata") const char str_0000449C[] = "stg3_tou_187\000\000\000";
__declspec(section ".rodata") const char str_000044AC[] = "stg3_tou_188\000\000\000";
__declspec(section ".rodata") const char str_000044BC[] = "stg3_tou_189\000\000\000";
__declspec(section ".rodata") const char str_000044CC[] = "stg3_tou_186_01";
__declspec(section ".rodata") const char str_000044DC[] = "stg3_tou_190_01";
__declspec(section ".rodata") const char str_000044EC[] = "stg3_tou_190\000\000\000";
__declspec(section ".rodata") const char str_000044FC[] = "stg3_tou_479_02";
__declspec(section ".rodata") const char str_0000450C[] = "stg3_tou_479_01";
__declspec(section ".rodata") const char str_0000451C[] = "stg3_tou_479_03";
__declspec(section ".rodata") const char str_0000452C[] = "stg3_tou_479_04";
__declspec(section ".rodata") const char str_0000453C[] = "stg3_tou_479_05";
__declspec(section ".rodata") const char str_0000454C[] = "stg3_tou_479_06";
__declspec(section ".rodata") const char str_0000455C[] = "\203}\203_\203\200\000";
__declspec(section ".rodata") const char str_00004564[] = "\203\214\203|\201[\203^\201[\000";
__declspec(section ".rodata") const char str_00004570[] = "\203J\203\201\203\211\203}\203\223\202P\000\000\000";
__declspec(section ".rodata") const char str_00004580[] = "\203J\203\201\203\211\203}\203\223\202Q\000\000\000";
__declspec(section ".rodata") const char str_00004590[] = "\203L\203m\203s\203I\202S\000";
__declspec(section ".rodata") const char str_0000459C[] = "\203L\203m\203s\203I\202T\000";
__declspec(section ".rodata") const char str_000045A8[] = "\203L\203m\203s\203R\000\000\000";
__declspec(section ".rodata") const char str_000045B4[] = "\203o\203b\203W\211\256\000\000\000";
__declspec(section ".rodata") const char str_000045C0[] = "\203`\203\203\203\223\203s\203\207\203\223\000\000\000";
__declspec(section ".rodata") const char str_000045D0[] = "\203L\203m\203V\203R\203\217\000";
__declspec(section ".rodata") const char str_000045DC[] = "\203E\203\211\203m\203R\000\000\000";
__declspec(section ".rodata") const char str_000045E8[] = "\203A\203C\203A\203\223\202`\000";
__declspec(section ".rodata") const char str_000045F4[] = "\203A\203C\203A\203\223\202a\000";
__declspec(section ".rodata") const char str_00004600[] = "\203{\203\215\203h\201[\000\000\000";
__declspec(section ".rodata") const char str_0000460C[] = "stg3_tou_33";
__declspec(section ".rodata") const char str_00004618[] = "stg3_tou_33_yn\000";
__declspec(section ".rodata") const char str_00004628[] = "stg3_tou_34_kur";
__declspec(section ".rodata") const char str_00004638[] = "stg3_tou_34_nok";
__declspec(section ".rodata") const char str_00004648[] = "stg3_tou_34_win";
__declspec(section ".rodata") const char str_00004658[] = "stg3_tou_35_kur";
__declspec(section ".rodata") const char str_00004668[] = "stg3_tou_35_nok";
__declspec(section ".rodata") const char str_00004678[] = "stg3_tou_35_win";
__declspec(section ".rodata") const char str_00004688[] = "SFX_VOICE_MARIO_NOD1_4\000";
__declspec(section ".rodata") const char str_000046A0[] = "M_N_2\000\000";
__declspec(section ".rodata") const char str_000046A8[] = "M_S_1\000\000";
__declspec(section ".rodata") const char str_000046B0[] = "stg3_tou_36";
__declspec(section ".rodata") const char str_000046BC[] = "c_kinopio\000\000";
__declspec(section ".rodata") const char str_000046C8[] = "KNP_W_1";
__declspec(section ".rodata") const char str_000046D0[] = "c_kinopiko\000";
__declspec(section ".rodata") const char str_000046DC[] = "KNF_W_1";
__declspec(section ".rodata") const char str_000046E4[] = "c_jugemu\000\000\000";
__declspec(section ".rodata") const char str_000046F0[] = "JGM_W_1";
__declspec(section ".rodata") const f32 vec3_tou_0000d028[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_tou_0000d034[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_tou_0000d040[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_tou_0000d04c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_tou_0000d058[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_tou_0000d064[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const char str_00004740[] = "stg3_tou_236\000\000\000";
__declspec(section ".rodata") const char str_00004750[] = "stg3_tou_237\000\000\000";
__declspec(section ".rodata") const char str_00004760[] = "stg3_tou_238\000\000\000";
__declspec(section ".rodata") const char str_00004770[] = "stg3_tou_239\000\000\000";
__declspec(section ".rodata") const char str_00004780[] = "stg3_tou_240\000\000\000";
__declspec(section ".rodata") const char str_00004790[] = "stg3_tou_240_01";
__declspec(section ".rodata") const char str_000047A0[] = "fan";
__declspec(section ".rodata") const char str_000047A4[] = "fan2\000\000\000";
__declspec(section ".rodata") const char str_000047AC[] = "fan3\000\000\000";
__declspec(section ".rodata") const char str_000047B4[] = "key";
__declspec(section ".rodata") const char str_000047B8[] = "stg3_tou_307_08";
__declspec(section ".rodata") const char str_000047C8[] = "SFX_VOICE_MARIO_FIND1_3";
__declspec(section ".rodata") const char str_000047E0[] = "BGM_FF_MAIL_RECEPTION2\000";
__declspec(section ".rodata") const char str_000047F8[] = "SFX_MAIL_RECEPTION1";
__declspec(section ".rodata") const char str_0000480C[] = "M_N_9\000\000";
__declspec(section ".rodata") const char str_00004814[] = "SFX_MAIL_RECEPTION2";
__declspec(section ".rodata") const char str_00004828[] = "M_N_10\000";
__declspec(section ".rodata") const char str_00004830[] = "stg3_tou_307_09";
__declspec(section ".rodata") const char str_00004840[] = "p_m_8\000\000";
__declspec(section ".rodata") const char str_00004848[] = "stg3_tou_479_00_01\000";
__declspec(section ".rodata") const char str_0000485C[] = "stg3_tou_479_00_02\000";
__declspec(section ".rodata") const char str_00004870[] = "stg3_tou_479_00_03\000";
__declspec(section ".rodata") const char str_00004884[] = "stg3_tou_479_00_04\000";
__declspec(section ".rodata") const char str_00004898[] = "stg3_tou_479_00_05\000";
__declspec(section ".rodata") const char str_000048AC[] = "M_I_2\000\000";
__declspec(section ".rodata") const char str_000048B4[] = "BGM_STG3_TOU2\000\000";
__declspec(section ".rodata") const char str_000048C4[] = "ENV_STG3_TOU2\000\000";
__declspec(section ".rodata") const char str_000048D4[] = "BGM_STG3_TOU1\000\000";
__declspec(section ".rodata") const char str_000048E4[] = "kururin1\000\000\000";
__declspec(section ".rodata") const char str_000048F0[] = "sita\000\000\000";
__declspec(section ".rodata") const char str_000048F8[] = "anm_paneru\000";
__declspec(section ".rodata") const char str_00004904[] = "SFX_STG3_AMB_OBJ_SCREEN2\000\000\000";
__declspec(section ".rodata") const char str_00004920[] = "SFX_STG3_AMB_OBJ_SCREEN1\000\000\000";
__declspec(section ".rodata") const char str_0000493C[] = "p_p_1\000\000";
__declspec(section ".rodata") const char str_00004944[] = "p_p_2\000\000";
__declspec(section ".rodata") const char str_0000494C[] = "p_p_3\000\000";
__declspec(section ".rodata") const char str_00004954[] = "a_p_p_2";
__declspec(section ".rodata") const char str_0000495C[] = "a_p_p_3";
__declspec(section ".rodata") const char str_00004964[] = "p_m_2\000\000";
__declspec(section ".rodata") const char str_0000496C[] = "a_p_m_2";
__declspec(section ".rodata") const char str_00004974[] = "p_m_3\000\000";
__declspec(section ".rodata") const char str_0000497C[] = "a_p_m_3";
__declspec(section ".rodata") const char str_00004984[] = "p_m_4\000\000";
__declspec(section ".rodata") const char str_0000498C[] = "a_p_m_4";
__declspec(section ".rodata") const char str_00004994[] = "p_m_5\000\000";
__declspec(section ".rodata") const char str_0000499C[] = "a_p_m_5";
__declspec(section ".rodata") const char str_000049A4[] = "p_m_6\000\000";
__declspec(section ".rodata") const char str_000049AC[] = "a_p_m_6";
__declspec(section ".rodata") const char str_000049B4[] = "p_m_7\000\000";
__declspec(section ".rodata") const char str_000049BC[] = "a_p_m_7";
__declspec(section ".rodata") const char str_000049C4[] = "a_p_m_8";
__declspec(section ".rodata") const char str_000049CC[] = "p_m_9\000\000";
__declspec(section ".rodata") const char str_000049D4[] = "a_p_m_9";
__declspec(section ".rodata") const char str_000049DC[] = "p_m_1\000\000";
__declspec(section ".rodata") const char str_000049E4[] = "a_p_m_1";
__declspec(section ".rodata") const char str_000049EC[] = "s_kaidan_7\000";
__declspec(section ".rodata") const f32 zero_tou_0000d328[1] = { 0.0f };
__declspec(section ".rodata") const f32 float_6p2832_tou_0000d32c[1] = { 6.2831855f };
__declspec(section ".rodata") const f32 float_90_tou_0000d330[1] = { 90.0f };
__declspec(section ".rodata") const f32 float_360_tou_0000d334[1] = { 360.0f };
__declspec(section ".rodata") const f32 float_0p00761_tou_0000d338[1] = { 0.00761f };
__declspec(section ".rodata") const f32 float_0p16605_tou_0000d33c[1] = { 0.16605f };
__declspec(section ".rodata") const f32 float_1_tou_0000d340[1] = { 1.0f };
__declspec(section ".rodata") const f32 float_3p1416_tou_0000d344[1] = { 3.1415927f };
__declspec(section ".rodata") const f32 float_1p5708_tou_0000d348[1] = { 1.5707964f };
__declspec(section ".rodata") const f32 float_4p7124_tou_0000d34c[1] = { 4.712389f };
__declspec(section ".rodata") const f32 float_35_tou_0000d350[1] = { 35.0f };
__declspec(section ".rodata") const f32 float_0p03705_tou_0000d354[1] = { 0.03705f };
__declspec(section ".rodata") const f32 float_0p4967_tou_0000d358[1] = { 0.4967f };
__declspec(section ".rodata") const f32 float_65_tou_0000d35c[1] = { 65.0f };
__declspec(section ".rodata") const f32 float_30_tou_0000d360[1] = { 30.0f };
__declspec(section ".rodata") const f32 float_60_tou_0000d364[1] = { 60.0f };
__declspec(section ".rodata") const f32 float_1000_tou_0000d368[1] = { 1000.0f };
__declspec(section ".rodata") const f64 double_to_int_tou_0000d370 = 4503601774854144;
__declspec(section ".rodata") const f32 float_0p1_tou_0000d378[1] = { 0.1f };
__declspec(section ".rodata") const f32 float_900_tou_0000d37c[1] = { 900.0f };
__declspec(section ".rodata") const f32 float_5_tou_0000d380[1] = { 5.0f };
__declspec(section ".rodata") const char str_00004A54[] = "SFX_STG3_AUDIENCE_FAN_FLY1\000";
__declspec(section ".rodata") const f32 float_32767_tou_0000d3a0[1] = { 32767.0f };
__declspec(section ".rodata") const f32 float_135_tou_0000d3a4[1] = { 135.0f };
__declspec(section ".rodata") const f32 float_400_tou_0000d3a8[1] = { 400.0f };
__declspec(section ".rodata") const f32 float_100_tou_0000d3ac[1] = { 100.0f };
__declspec(section ".rodata") const f32 float_neg100_tou_0000d3b0[1] = { -100.0f };
__declspec(section ".rodata") const f32 float_4_tou_0000d3b4[1] = { 4.0f };
__declspec(section ".rodata") const f32 float_2_tou_0000d3b8[1] = { 2.0f };
__declspec(section ".rodata") const f32 float_0p5_tou_0000d3bc[1] = { 0.5f };
__declspec(section ".rodata") const f32 float_0p03_tou_0000d3c0[1] = { 0.03f };
__declspec(section ".rodata") const f32 float_25_tou_0000d3c4[1] = { 25.0f };
__declspec(section ".rodata") const f32 float_0p6_tou_0000d3c8[1] = { 0.6f };
__declspec(section ".rodata") const f32 float_neg350_tou_0000d3cc[1] = { -350.0f };
__declspec(section ".rodata") const f32 float_350_tou_0000d3d0[1] = { 350.0f };
__declspec(section ".rodata") const f32 float_195_tou_0000d3d4[1] = { 195.0f };
__declspec(section ".rodata") const u32 zero_tou_0000d3d8[1] = { 0x00000000 };
__declspec(section ".rodata") const f32 float_200_tou_0000d3dc[1] = { 200.0f };
__declspec(section ".rodata") const char str_00004AB0[] = "SFX_STG3_AUDIENCE_FAN1\000";
s32 evt_end_count(EventEntry* event, BOOL isFirstCall);
s32 check_hammer(Fan* fan);
void ext_fan_dispent(void);
void ext_fan_main(void);
void fan_disp(CameraId camera, void* param);
void ext_fan_init(void);
static f32 randf(f32 min, f32 max);
static void pose_change(Fan* fan, const char* name, const char* anim);
static void pose_main(void);
static void pose_init(void);

void C_VECReflect(const Vec* src, const Vec* normal, Vec* dst);
void PSMTXIdentity(Mtx m);
void PSVECAdd(const Vec* a, const Vec* b, Vec* ab);
f32 PSVECDistance(const Vec* a, const Vec* b);
f32 PSVECMag(const Vec* v);
void PSVECNormalize(const Vec* src, Vec* dst);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
f32 PSVECSquareDistance(const Vec* a, const Vec* b);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
void __cvt_ull_flt();
void __div2u();
void* _mapAlloc(u32 size);
f32 angleABf(f32 x1, f32 y1, f32 x2, f32 y2);
CameraEntry* camGetPtr(CameraId cameraId);
f32 cloudGetBreathDir(void);
void dispEntry(CameraId camera, f32 order, s32 renderMode, DispCallback callback, void* param);
f32 distABf(f32 x1, f32 y1, f32 x2, f32 y2);
s32 evtGetValue(EventEntry* entry, s32 index);
s32 evtSetValue(EventEntry* entry, s32 index, s32 value);
HitEntry* hitCheckVecFilter(HitCheckQuery* query, HitFilterCallback callback);
s32 irand(s32 scalar);
MarioWork* marioGetPtr(void);
void *memset(void *dest, int ch, size_t count);
NpcEntry* npcNameToPtr(const char* name);
PartyEntry* partyGetPtr(s32 index);
s32 psndSFXOn_3D(const char* name, Vec* position);
int rand(void);
f32 reviseAngle(f32 angle);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
asm s32 evt_end_count(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, fan_wp@ha
	stw r0, 0x14(r1)
	lwz r5, fan_wp@l(r4)
	lwz r6, 0x18(r3)
	lwz r5, 0x510(r5)
	lwz r4, 0x0(r6)
	bl evtSetValue
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 check_hammer(Fan* fan) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x20(r1)
	psq_st f31, 0x28(r1), 0, 0
	stmw r30, 0x18(r1)
	mr r30, r3
	bl marioGetPtr
	lis r4, zero_tou_0000d328@ha
	lfs f1, 0x90(r3)
	lfs f0, zero_tou_0000d328@l(r4)
	mr r31, r3
	fcmpo cr0, f1, f0
	ble @1
	li r3, 0x0
	b @2
	@1:
	lhz r0, 0x0(r30)
	clrlwi. r0, r0, 31
	beq @3
	li r3, 0x0
	b @2
	@3:
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x12
	bne @4
	lis r3, fan_wp@ha
	addi r3, r3, fan_wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x50c(r3)
	cmpwi r0, 0xa
	ble @4
	li r3, 0x4
	bl camGetPtr
	lis r4, float_90_tou_0000d330@ha
	lfs f1, 0x1a8(r31)
	lfs f0, float_90_tou_0000d330@l(r4)
	lfs f2, 0x114(r3)
	fsubs f0, f1, f0
	fadds f1, f0, f2
	bl reviseAngle
	lis r3, float_6p2832_tou_0000d32c@ha
	lis r6, float_0p00761_tou_0000d338@ha
	addi r5, r3, float_6p2832_tou_0000d32c@l
	lis r4, float_360_tou_0000d334@ha
	lfs f0, 0x0(r5)
	lis r5, float_0p16605_tou_0000d33c@ha
	lis r3, float_3p1416_tou_0000d344@ha
	lfs f4, float_0p00761_tou_0000d338@l(r6)
	fmuls f2, f0, f1
	lfs f0, float_360_tou_0000d334@l(r4)
	lfs f1, float_3p1416_tou_0000d344@l(r3)
	lis r4, float_1_tou_0000d340@ha
	lfs f3, float_0p16605_tou_0000d33c@l(r5)
	fdivs f6, f2, f0
	lfs f2, float_1_tou_0000d340@l(r4)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @5
	lis r3, float_1p5708_tou_0000d348@ha
	lfs f1, float_1p5708_tou_0000d348@l(r3)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @6
	fmuls f0, f6, f6
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f6
	b @7
	@6:
	fsubs f0, f6, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @7
	@5:
	lis r3, float_4p7124_tou_0000d34c@ha
	lfs f0, float_4p7124_tou_0000d34c@l(r3)
	fcmpo cr0, f6, f0
	bge @8
	fsubs f1, f6, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @7
	@8:
	lis r3, float_1p5708_tou_0000d348@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_tou_0000d348@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@7:
	lis r3, float_3p1416_tou_0000d344@ha
	lis r4, float_35_tou_0000d350@ha
	lfs f1, float_3p1416_tou_0000d344@l(r3)
	lis r5, float_0p03705_tou_0000d354@ha
	lfs f2, float_35_tou_0000d350@l(r4)
	lis r4, float_0p4967_tou_0000d358@ha
	lfs f0, 0x8c(r31)
	fcmpo cr0, f6, f1
	lis r3, float_1_tou_0000d340@ha
	lfs f5, float_0p03705_tou_0000d354@l(r5)
	fmadds f3, f2, f4, f0
	lfs f4, float_0p4967_tou_0000d358@l(r4)
	lfs f2, float_1_tou_0000d340@l(r3)
	cror eq, lt, eq
	bne @9
	lis r3, float_1p5708_tou_0000d348@ha
	lfs f1, float_1p5708_tou_0000d348@l(r3)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @10
	fmuls f0, f6, f6
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	b @11
	@10:
	fsubs f0, f6, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fneg f5, f5
	b @11
	@9:
	lis r3, float_4p7124_tou_0000d34c@ha
	lfs f0, float_4p7124_tou_0000d34c@l(r3)
	fcmpo cr0, f6, f0
	bge @12
	fsubs f0, f6, f1
	fmuls f0, f0, f0
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fneg f5, f5
	b @11
	@12:
	lis r3, float_1p5708_tou_0000d348@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_tou_0000d348@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	@11:
	lis r3, float_35_tou_0000d350@ha
	lfs f0, 0x94(r31)
	lfs f2, float_35_tou_0000d350@l(r3)
	lfs f1, 0x10(r30)
	fnmsubs f4, f2, f5, f0
	lfs f2, 0x18(r30)
	bl distABf
	lis r3, float_35_tou_0000d350@ha
	lfs f0, float_35_tou_0000d350@l(r3)
	fcmpo cr0, f1, f0
	bge @4
	li r3, 0x1
	b @2
	@4:
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x13
	bne @13
	lwz r0, 0x44(r31)
	cmpwi r0, 0x14
	bne @13
	addi r3, r31, 0x8c
	addi r4, r30, 0x10
	bl PSVECDistance
	lis r3, float_65_tou_0000d35c@ha
	lfs f0, float_65_tou_0000d35c@l(r3)
	fcmpo cr0, f1, f0
	bge @13
	li r3, 0x1
	b @2
	@13:
	li r3, 0x0
	bl partyGetPtr
	mr. r31, r3
	beq @14
	lbz r0, 0x31(r31)
	cmpwi r0, 0x5
	bne @14
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 23, 23
	beq @14
	bl cloudGetBreathDir
	lis r4, float_6p2832_tou_0000d32c@ha
	lis r3, float_360_tou_0000d334@ha
	lfs f2, float_6p2832_tou_0000d32c@l(r4)
	lfs f0, float_360_tou_0000d334@l(r3)
	fmuls f1, f2, f1
	fdivs f31, f1, f0
	bl cloudGetBreathDist
	lis r3, float_3p1416_tou_0000d344@ha
	lis r5, float_0p00761_tou_0000d338@ha
	lfs f2, float_3p1416_tou_0000d344@l(r3)
	lis r4, float_0p16605_tou_0000d33c@ha
	lis r3, float_1_tou_0000d340@ha
	lfs f5, float_0p00761_tou_0000d338@l(r5)
	fcmpo cr0, f31, f2
	lfs f4, float_0p16605_tou_0000d33c@l(r4)
	lfs f3, float_1_tou_0000d340@l(r3)
	cror eq, lt, eq
	bne @15
	lis r3, float_1p5708_tou_0000d348@ha
	lfs f2, float_1p5708_tou_0000d348@l(r3)
	fcmpo cr0, f31, f2
	cror eq, lt, eq
	bne @16
	fmuls f0, f31, f31
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f31
	b @17
	@16:
	fsubs f0, f31, f2
	fsubs f2, f2, f0
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f2
	b @17
	@15:
	lis r3, float_4p7124_tou_0000d34c@ha
	lfs f0, float_4p7124_tou_0000d34c@l(r3)
	fcmpo cr0, f31, f0
	bge @18
	fsubs f2, f31, f2
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f2
	fneg f5, f5
	b @17
	@18:
	lis r3, float_1p5708_tou_0000d348@ha
	fsubs f0, f31, f0
	lfs f2, float_1p5708_tou_0000d348@l(r3)
	fsubs f2, f2, f0
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f2
	fneg f5, f5
	@17:
	lfs f0, 0x58(r31)
	lis r3, float_3p1416_tou_0000d344@ha
	lfs f2, float_3p1416_tou_0000d344@l(r3)
	lis r4, float_0p4967_tou_0000d358@ha
	fmadds f0, f1, f5, f0
	lis r5, float_0p03705_tou_0000d354@ha
	lis r3, float_1_tou_0000d340@ha
	fcmpo cr0, f31, f2
	lfs f5, float_0p03705_tou_0000d354@l(r5)
	stfs f0, 0x8(r1)
	lfs f4, float_0p4967_tou_0000d358@l(r4)
	lfs f0, 0x5c(r31)
	lfs f3, float_1_tou_0000d340@l(r3)
	stfs f0, 0xc(r1)
	cror eq, lt, eq
	bne @19
	lis r3, float_1p5708_tou_0000d348@ha
	lfs f2, float_1p5708_tou_0000d348@l(r3)
	fcmpo cr0, f31, f2
	cror eq, lt, eq
	bne @20
	fmuls f0, f31, f31
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	b @21
	@20:
	fsubs f0, f31, f2
	fsubs f0, f2, f0
	fmuls f0, f0, f0
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fneg f5, f5
	b @21
	@19:
	lis r3, float_4p7124_tou_0000d34c@ha
	lfs f0, float_4p7124_tou_0000d34c@l(r3)
	fcmpo cr0, f31, f0
	bge @22
	fsubs f0, f31, f2
	fmuls f0, f0, f0
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fneg f5, f5
	b @21
	@22:
	lis r3, float_1p5708_tou_0000d348@ha
	fsubs f0, f31, f0
	lfs f2, float_1p5708_tou_0000d348@l(r3)
	fsubs f0, f2, f0
	fmuls f0, f0, f0
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	@21:
	lis r3, zero_tou_0000d328@ha
	lfs f2, 0x60(r31)
	lfs f0, zero_tou_0000d328@l(r3)
	fnmsubs f1, f1, f5, f2
	fcmpo cr0, f31, f0
	stfs f1, 0x10(r1)
	cror eq, gt, eq
	bne @14
	addi r3, r1, 0x8
	addi r4, r30, 0x10
	bl PSVECDistance
	lis r3, float_30_tou_0000d360@ha
	lfs f0, float_30_tou_0000d360@l(r3)
	fcmpo cr0, f1, f0
	bge @14
	li r3, 0x2
	b @2
	@14:
	li r3, 0x0
	@2:
	psq_l f31, 0x28(r1), 0, 0
	lfd f31, 0x20(r1)
	lmw r30, 0x18(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void ext_fan_dispent(void) {
	nofralloc
	stwu r1, -0x80(r1)
	mflr r0
	stw r0, 0x84(r1)
	stfd f31, 0x70(r1)
	psq_st f31, 0x78(r1), 0, 0
	stfd f30, 0x60(r1)
	psq_st f30, 0x68(r1), 0, 0
	stfd f29, 0x50(r1)
	psq_st f29, 0x58(r1), 0, 0
	stfd f28, 0x40(r1)
	psq_st f28, 0x48(r1), 0, 0
	stmw r22, 0x18(r1)
	bl extGetPosePtr
	lis r4, fan_wp@ha
	lis r7, float_60_tou_0000d364@ha
	addi r29, r4, fan_wp@l
	lis r6, float_1000_tou_0000d368@ha
	lwz r9, 0x0(r29)
	lis r5, float_1_tou_0000d340@ha
	lis r4, double_to_int_tou_0000d370@ha
	lis r8, gp@ha
	lwz r28, 0x4(r9)
	mr r27, r3
	lfs f28, float_60_tou_0000d364@l(r7)
	addi r30, r8, gp@l
	lfs f29, float_1000_tou_0000d368@l(r6)
	li r26, 0x0
	lfs f30, float_1_tou_0000d340@l(r5)
	lis r31, 0x8000
	lfd f31, double_to_int_tou_0000d370@l(r4)
	lis r23, 0x4330
	b @1
	@2:
	lwz r3, 0xf8(r31)
	li r0, 0x3e8
	lwz r4, 0x0(r30)
	li r5, 0x0
	srwi r3, r3, 2
	lha r7, 0x4(r28)
	divwu r6, r3, r0
	lwz r24, 0x3c(r4)
	lwz r0, 0xc(r28)
	lwz r25, 0x38(r4)
	subfc r4, r0, r24
	lwz r0, 0x8(r28)
	mulli r7, r7, 0x28
	subfe r3, r0, r25
	addi r22, r7, 0xc
	add r22, r8, r22
	bl __div2u
	bl __cvt_ull_flt
	fmuls f1, f28, f1
	lfs f0, 0x1c(r22)
	fdivs f1, f1, f29
	fdivs f1, f1, f0
	fcmpo cr0, f1, f30
	cror eq, gt, eq
	bne @3
	stw r24, 0xc(r28)
	lis r3, zero_tou_0000d328@ha
	lfs f1, zero_tou_0000d328@l(r3)
	stw r25, 0x8(r28)
	@3:
	lwz r3, 0x24(r22)
	addi r26, r26, 0x1
	stw r23, 0x8(r1)
	addi r28, r28, 0x48
	subi r0, r3, 0x1
	lwz r3, 0x20(r22)
	xoris r0, r0, 0x8000
	stw r0, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f31
	fmuls f0, f0, f1
	fctiwz f0, f0
	stfd f0, 0x10(r1)
	lwz r0, 0x14(r1)
	add r0, r3, r0
	stw r0, 0x10(r27)
	addi r27, r27, 0x20
	@1:
	lwz r8, 0x0(r29)
	lwz r0, 0x0(r8)
	cmpw r26, r0
	blt @2
	lis r3, zero_tou_0000d328@ha
	lis r4, fan_disp@ha
	addi r6, r3, zero_tou_0000d328@l
	lfs f1, 0x0(r6)
	addi r5, r4, fan_disp@l
	li r3, 0x4
	li r4, 0x1
	li r6, 0x0
	bl dispEntry
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	psq_l f30, 0x68(r1), 0, 0
	lfd f30, 0x60(r1)
	psq_l f29, 0x58(r1), 0, 0
	lfd f29, 0x50(r1)
	psq_l f28, 0x48(r1), 0, 0
	lfd f28, 0x40(r1)
	lmw r22, 0x18(r1)
	lwz r0, 0x84(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm void ext_fan_main(void) {
	nofralloc
	stwu r1, -0xe0(r1)
	mflr r0
	stw r0, 0xe4(r1)
	stfd f31, 0xd0(r1)
	psq_st f31, 0xd8(r1), 0, 0
	stfd f30, 0xc0(r1)
	psq_st f30, 0xc8(r1), 0, 0
	stmw r25, 0xa4(r1)
	bl marioGetPtr
	lis r4, vec3_tou_0000d04c@ha
	mr r31, r3
	addi r5, r4, vec3_tou_0000d04c@l
	lwz r4, 0x0(r5)
	lwz r3, 0x4(r5)
	lwz r0, 0x8(r5)
	stw r4, 0x14(r1)
	stw r3, 0x18(r1)
	stw r0, 0x1c(r1)
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x12
	bne @1
	lis r3, fan_wp@ha
	lwz r4, fan_wp@l(r3)
	lwz r3, 0x50c(r4)
	addi r0, r3, 0x1
	stw r0, 0x50c(r4)
	b @2
	@1:
	lis r3, fan_wp@ha
	li r0, 0x0
	addi r3, r3, fan_wp@l
	lwz r3, 0x0(r3)
	stw r0, 0x50c(r3)
	@2:
	lis r4, 0xfaa3
	li r3, 0x0
	subi r4, r4, 0x4a76
	bl evtGetValue
	cmpwi r3, 0x0
	beq @3
	bl extGetPosePtr
	lis r4, fan_wp@ha
	addi r4, r4, fan_wp@l
	lwz r4, 0x0(r4)
	lwz r0, 0x0(r4)
	lwz r5, 0x4(r4)
	mtctr r0
	cmpwi r0, 0x0
	ble @4
	@5:
	lha r0, 0x2(r5)
	cmpwi r0, 0x0
	bne @6
	lwz r4, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r4, 0x10(r5)
	stw r0, 0x14(r5)
	lwz r0, 0x94(r31)
	stw r0, 0x18(r5)
	lwz r4, 0x10(r5)
	lwz r0, 0x14(r5)
	stw r4, 0x14(r1)
	stw r0, 0x18(r1)
	lwz r0, 0x18(r5)
	stw r0, 0x1c(r1)
	lwz r0, 0x0(r3)
	clrrwi r0, r0, 1
	stw r0, 0x0(r3)
	lhz r0, 0x0(r5)
	ori r0, r0, 0x1
	sth r0, 0x0(r5)
	b @4
	@6:
	addi r5, r5, 0x48
	addi r3, r3, 0x20
	bdnz @5
	b @4
	@3:
	li r27, 0x0
	bl extGetPosePtr
	lis r4, fan_wp@ha
	li r6, 0x0
	addi r5, r4, fan_wp@l
	mr r29, r3
	lwz r4, 0x0(r5)
	lwz r28, 0x4(r4)
	b @7
	@8:
	lha r0, 0x2(r28)
	cmpwi r0, 0x0
	bne @9
	cmpwi r27, 0x0
	bne @10
	lwz r3, 0x8c(r31)
	li r27, 0x1
	lwz r0, 0x90(r31)
	stw r3, 0x10(r28)
	stw r0, 0x14(r28)
	lwz r0, 0x94(r31)
	stw r0, 0x18(r28)
	lwz r0, 0x0(r29)
	clrrwi r0, r0, 1
	stw r0, 0x0(r29)
	lhz r0, 0x0(r28)
	ori r0, r0, 0x1
	sth r0, 0x0(r28)
	b @9
	@10:
	lis r3, str_000045C0@ha
	addi r3, r3, str_000045C0@l
	bl npcNameToPtr
	lwz r4, 0x8c(r3)
	lwz r0, 0x90(r3)
	stw r4, 0x10(r28)
	stw r0, 0x14(r28)
	lwz r0, 0x94(r3)
	stw r0, 0x18(r28)
	lwz r3, 0x10(r28)
	lwz r0, 0x14(r28)
	stw r3, 0x14(r1)
	stw r0, 0x18(r1)
	lwz r0, 0x18(r28)
	stw r0, 0x1c(r1)
	lwz r0, 0x0(r29)
	clrrwi r0, r0, 1
	stw r0, 0x0(r29)
	lhz r0, 0x0(r28)
	ori r0, r0, 0x1
	sth r0, 0x0(r28)
	b @4
	@9:
	addi r6, r6, 0x1
	addi r28, r28, 0x48
	addi r29, r29, 0x20
	@7:
	lwz r3, 0x0(r5)
	lwz r0, 0x0(r3)
	cmpw r6, r0
	blt @8
	@4:
	lis r3, fan_wp@ha
	li r28, 0x0
	addi r26, r3, fan_wp@l
	lwz r3, 0x0(r26)
	lwz r27, 0x4(r3)
	b @11
	@12:
	lha r0, 0x2(r27)
	cmpwi r0, 0x0
	bne @13
	addi r3, r1, 0x14
	addi r4, r27, 0x10
	addi r5, r1, 0x20
	bl PSVECSubtract
	addi r3, r1, 0x20
	bl PSVECMag
	lis r3, zero_tou_0000d328@ha
	lfs f0, zero_tou_0000d328@l(r3)
	fcmpu cr0, f1, f0
	beq @13
	addi r3, r1, 0x20
	mr r4, r3
	bl PSVECNormalize
	lis r3, zero_tou_0000d328@ha
	lis r4, float_0p1_tou_0000d378@ha
	addi r5, r3, zero_tou_0000d328@l
	lfs f1, float_0p1_tou_0000d378@l(r4)
	lfs f0, 0x0(r5)
	addi r3, r1, 0x20
	mr r4, r3
	stfs f0, 0x24(r1)
	bl PSVECScale
	addi r3, r27, 0x1c
	addi r4, r1, 0x20
	mr r5, r3
	bl PSVECAdd
	@13:
	addi r28, r28, 0x1
	addi r27, r27, 0x48
	@11:
	lwz r4, 0x0(r26)
	lwz r0, 0x0(r4)
	cmpw r28, r0
	blt @12
	lis r3, fan_wp@ha
	lwz r28, 0x4(r4)
	addi r26, r3, fan_wp@l
	li r27, 0x0
	b @14
	@15:
	lha r0, 0x2(r28)
	cmpwi r0, 0x0
	bne @16
	lis r3, fan_wp@ha
	lwz r25, 0x4(r5)
	addi r29, r3, fan_wp@l
	li r30, 0x0
	b @17
	@18:
	lha r0, 0x2(r25)
	cmpwi r0, 0x0
	bne @19
	cmpw r27, r30
	beq @19
	addi r3, r28, 0x10
	addi r4, r25, 0x10
	bl PSVECSquareDistance
	lis r3, float_900_tou_0000d37c@ha
	lfs f0, float_900_tou_0000d37c@l(r3)
	fcmpo cr0, f1, f0
	bge @19
	addi r3, r28, 0x10
	addi r4, r25, 0x10
	addi r5, r1, 0x20
	bl PSVECSubtract
	lis r4, zero_tou_0000d328@ha
	addi r3, r1, 0x20
	lfs f0, zero_tou_0000d328@l(r4)
	mr r4, r3
	stfs f0, 0x24(r1)
	bl PSVECNormalize
	lis r4, float_5_tou_0000d380@ha
	addi r3, r1, 0x20
	lfs f1, float_5_tou_0000d380@l(r4)
	mr r4, r3
	bl PSVECScale
	addi r3, r28, 0x1c
	addi r4, r1, 0x20
	mr r5, r3
	bl PSVECAdd
	addi r3, r25, 0x1c
	addi r4, r1, 0x20
	mr r5, r3
	bl PSVECSubtract
	@19:
	addi r30, r30, 0x1
	addi r25, r25, 0x48
	@17:
	lwz r3, 0x0(r29)
	lwz r0, 0x0(r3)
	cmpw r30, r0
	blt @18
	@16:
	addi r27, r27, 0x1
	addi r28, r28, 0x48
	@14:
	lwz r5, 0x0(r26)
	lwz r0, 0x0(r5)
	cmpw r27, r0
	blt @15
	lis r4, str_00004A54@ha
	lis r3, fan_wp@ha
	addi r30, r4, str_00004A54@l
	lwz r28, 0x4(r5)
	addi r26, r3, fan_wp@l
	li r27, 0x0
	mr r29, r30
	b @20
	@21:
	lha r0, 0x2(r28)
	cmpwi r0, 0x0
	bne @22
	mr r3, r28
	bl check_hammer
	cmpwi r3, 0x1
	beq @23
	bge @24
	b @22
	@24:
	cmpwi r3, 0x3
	bge @22
	b @25
	@23:
	li r0, 0xa
	sth r0, 0x2(r28)
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x74(r1)
	lis r4, double_to_int_tou_0000d370@ha
	lfd f2, double_to_int_tou_0000d370@l(r4)
	lis r3, float_32767_tou_0000d3a0@ha
	stw r0, 0x70(r1)
	addi r5, r3, float_32767_tou_0000d3a0@l
	lis r6, float_6p2832_tou_0000d32c@ha
	lfs f0, 0x0(r5)
	lfd f1, 0x70(r1)
	lis r4, float_90_tou_0000d330@ha
	lis r3, float_135_tou_0000d3a4@ha
	lfs f3, float_6p2832_tou_0000d32c@l(r6)
	fsubs f1, f1, f2
	addi r5, r4, float_90_tou_0000d330@l
	addi r4, r3, float_135_tou_0000d3a4@l
	lfs f2, 0x0(r5)
	lis r3, float_360_tou_0000d334@ha
	fdivs f4, f1, f0
	lfs f1, 0x0(r4)
	lfs f0, float_360_tou_0000d334@l(r3)
	fmadds f1, f4, f2, f1
	fmuls f1, f3, f1
	fdivs f30, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_tou_0000d370@ha
	stw r3, 0x7c(r1)
	addi r5, r4, double_to_int_tou_0000d370@l
	lis r3, float_32767_tou_0000d3a0@ha
	stw r0, 0x78(r1)
	addi r4, r3, float_32767_tou_0000d3a0@l
	lfd f2, 0x0(r5)
	lis r5, float_100_tou_0000d3ac@ha
	lfd f1, 0x78(r1)
	addi r7, r5, float_100_tou_0000d3ac@l
	lfs f0, 0x0(r4)
	lis r4, float_400_tou_0000d3a8@ha
	fsubs f2, f1, f2
	lis r3, float_3p1416_tou_0000d344@ha
	lfs f1, float_3p1416_tou_0000d344@l(r3)
	addi r6, r4, float_400_tou_0000d3a8@l
	lis r5, float_0p00761_tou_0000d338@ha
	lis r4, float_0p16605_tou_0000d33c@ha
	fdivs f3, f2, f0
	lfs f2, 0x0(r7)
	lfs f0, 0x0(r6)
	lis r3, float_1_tou_0000d340@ha
	lfs f4, float_0p00761_tou_0000d338@l(r5)
	fmadds f5, f3, f2, f0
	fcmpo cr0, f30, f1
	lfs f3, float_0p16605_tou_0000d33c@l(r4)
	lfs f2, float_1_tou_0000d340@l(r3)
	cror eq, lt, eq
	bne @26
	lis r3, float_1p5708_tou_0000d348@ha
	lfs f1, float_1p5708_tou_0000d348@l(r3)
	fcmpo cr0, f30, f1
	cror eq, lt, eq
	bne @27
	fmuls f0, f30, f30
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f30
	b @28
	@27:
	fsubs f0, f30, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @28
	@26:
	lis r3, float_4p7124_tou_0000d34c@ha
	lfs f0, float_4p7124_tou_0000d34c@l(r3)
	fcmpo cr0, f30, f0
	bge @29
	fsubs f1, f30, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @28
	@29:
	lis r3, float_1p5708_tou_0000d348@ha
	fsubs f0, f30, f0
	lfs f1, float_1p5708_tou_0000d348@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@28:
	lis r3, float_3p1416_tou_0000d344@ha
	lfs f0, 0x10(r28)
	lfs f1, float_3p1416_tou_0000d344@l(r3)
	lis r4, float_0p4967_tou_0000d358@ha
	lis r3, float_1_tou_0000d340@ha
	lis r5, float_0p03705_tou_0000d354@ha
	fcmpo cr0, f30, f1
	lfs f3, float_0p4967_tou_0000d358@l(r4)
	fmadds f6, f5, f4, f0
	lfs f4, float_0p03705_tou_0000d354@l(r5)
	lfs f2, float_1_tou_0000d340@l(r3)
	cror eq, lt, eq
	bne @30
	lis r3, float_1p5708_tou_0000d348@ha
	lfs f1, float_1p5708_tou_0000d348@l(r3)
	fcmpo cr0, f30, f1
	cror eq, lt, eq
	bne @31
	fmuls f0, f30, f30
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @32
	@31:
	fsubs f0, f30, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @32
	@30:
	lis r3, float_4p7124_tou_0000d34c@ha
	lfs f0, float_4p7124_tou_0000d34c@l(r3)
	fcmpo cr0, f30, f0
	bge @33
	fsubs f0, f30, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @32
	@33:
	lis r3, float_1p5708_tou_0000d348@ha
	fsubs f0, f30, f0
	lfs f1, float_1p5708_tou_0000d348@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@32:
	lis r4, vec3_tou_0000d058@ha
	lfs f0, 0x18(r28)
	addi r5, r4, vec3_tou_0000d058@l
	lis r3, float_neg100_tou_0000d3b0@ha
	lwz r4, 0x0(r5)
	fnmsubs f1, f5, f4, f0
	lwz r0, 0x4(r5)
	stw r4, 0x8(r1)
	lwz r4, 0x8(r5)
	stfs f6, 0x8(r1)
	lfs f0, float_neg100_tou_0000d3b0@l(r3)
	stw r0, 0xc(r1)
	lwz r0, 0x8(r1)
	stw r4, 0x10(r1)
	stfs f0, 0xc(r1)
	stfs f1, 0x10(r1)
	lwz r3, 0xc(r1)
	stw r0, 0x2c(r28)
	lwz r0, 0x10(r1)
	stw r3, 0x30(r28)
	stw r0, 0x34(r28)
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x7c(r1)
	lis r4, double_to_int_tou_0000d370@ha
	lfd f1, double_to_int_tou_0000d370@l(r4)
	lis r3, float_32767_tou_0000d3a0@ha
	stw r0, 0x78(r1)
	addi r5, r3, float_32767_tou_0000d3a0@l
	lfs f2, 0x0(r5)
	lis r4, float_2_tou_0000d3b8@ha
	lfd f0, 0x78(r1)
	lis r3, float_4_tou_0000d3b4@ha
	fsubs f3, f0, f1
	lfs f1, float_2_tou_0000d3b8@l(r4)
	lfs f0, float_4_tou_0000d3b4@l(r3)
	fdivs f2, f3, f2
	fmadds f0, f2, f1, f0
	stfs f0, 0x3c(r28)
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_tou_0000d370@ha
	stw r3, 0x74(r1)
	addi r5, r4, double_to_int_tou_0000d370@l
	lis r3, float_32767_tou_0000d3a0@ha
	stw r0, 0x70(r1)
	addi r4, r3, float_32767_tou_0000d3a0@l
	lfd f2, 0x0(r5)
	lis r3, float_0p1_tou_0000d378@ha
	lfd f0, 0x70(r1)
	lfs f1, 0x0(r4)
	fsubs f2, f0, f2
	lfs f0, float_0p1_tou_0000d378@l(r3)
	fdivs f1, f2, f1
	fmadds f0, f1, f0, f0
	stfs f0, 0x40(r28)
	lfs f2, 0x30(r28)
	lfs f0, 0x14(r28)
	lfs f1, 0x10(r28)
	fsubs f31, f2, f0
	lfs f2, 0x18(r28)
	lfs f3, 0x2c(r28)
	lfs f4, 0x34(r28)
	bl distABf
	fmr f30, f1
	lfs f1, 0x10(r28)
	lfs f2, 0x18(r28)
	lfs f3, 0x2c(r28)
	lfs f4, 0x34(r28)
	bl angleABf
	lfs f0, 0x3c(r28)
	lis r0, 0x4330
	lis r4, double_to_int_tou_0000d370@ha
	lis r3, float_0p5_tou_0000d3bc@ha
	fdivs f0, f30, f0
	addi r5, r4, double_to_int_tou_0000d370@l
	addi r4, r3, float_0p5_tou_0000d3bc@l
	stw r0, 0x90(r1)
	lfd f3, 0x0(r5)
	mr r3, r30
	fctiwz f0, f0
	stw r0, 0x88(r1)
	lfs f1, 0x0(r4)
	addi r4, r28, 0x10
	stfd f0, 0x80(r1)
	lwz r0, 0x84(r1)
	sth r0, 0x44(r28)
	lha r0, 0x44(r28)
	lfs f4, 0x40(r28)
	xoris r0, r0, 0x8000
	stw r0, 0x94(r1)
	lfd f0, 0x90(r1)
	stw r0, 0x8c(r1)
	fsubs f0, f0, f3
	lfd f2, 0x88(r1)
	fdivs f0, f31, f0
	fsubs f2, f2, f3
	fmuls f2, f4, f2
	fmadds f0, f2, f1, f0
	stfs f0, 0x38(r28)
	bl psndSFXOn_3D
	b @22
	@25:
	lfs f1, 0x8c(r31)
	lfs f2, 0x94(r31)
	lfs f3, 0x10(r28)
	lfs f4, 0x18(r28)
	bl angleABf
	fmr f30, f1
	bl cloudGetBreathDir
	li r0, 0x14
	lis r3, vec3_tou_0000d064@ha
	sth r0, 0x2(r28)
	addi r4, r3, vec3_tou_0000d064@l
	lis r5, float_0p5_tou_0000d3bc@ha
	fadds f1, f30, f1
	lwz r3, 0x0(r4)
	lwz r0, 0x4(r4)
	lfs f0, float_0p5_tou_0000d3bc@l(r5)
	stw r3, 0x2c(r28)
	fmuls f30, f1, f0
	stw r0, 0x30(r28)
	lwz r0, 0x8(r4)
	stw r0, 0x34(r28)
	bl rand
	xoris r4, r3, 0x8000
	lis r0, 0x4330
	lis r3, float_6p2832_tou_0000d32c@ha
	stw r4, 0x94(r1)
	lfs f0, float_6p2832_tou_0000d32c@l(r3)
	lis r5, double_to_int_tou_0000d370@ha
	stw r0, 0x90(r1)
	lis r3, float_360_tou_0000d334@ha
	lfd f3, double_to_int_tou_0000d370@l(r5)
	fmuls f1, f0, f30
	lfs f0, float_360_tou_0000d334@l(r3)
	lis r4, float_32767_tou_0000d3a0@ha
	lfd f2, 0x90(r1)
	lis r5, float_0p00761_tou_0000d338@ha
	fdivs f30, f1, f0
	lis r3, float_3p1416_tou_0000d344@ha
	lfs f5, float_0p00761_tou_0000d338@l(r5)
	lfs f1, float_3p1416_tou_0000d344@l(r3)
	lis r3, float_1_tou_0000d340@ha
	fsubs f3, f2, f3
	lfs f2, float_32767_tou_0000d3a0@l(r4)
	lis r4, float_0p1_tou_0000d378@ha
	addi r6, r4, float_0p1_tou_0000d378@l
	fcmpo cr0, f30, f1
	fdivs f2, f3, f2
	lfs f0, 0x0(r6)
	lis r4, float_0p16605_tou_0000d33c@ha
	lfs f4, float_0p16605_tou_0000d33c@l(r4)
	lfs f3, float_1_tou_0000d340@l(r3)
	fmadds f31, f2, f0, f0
	cror eq, lt, eq
	bne @34
	lis r3, float_1p5708_tou_0000d348@ha
	lfs f1, float_1p5708_tou_0000d348@l(r3)
	fcmpo cr0, f30, f1
	cror eq, lt, eq
	bne @35
	fmuls f0, f30, f30
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f30
	b @36
	@35:
	fsubs f0, f30, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	b @36
	@34:
	lis r3, float_4p7124_tou_0000d34c@ha
	lfs f0, float_4p7124_tou_0000d34c@l(r3)
	fcmpo cr0, f30, f0
	bge @37
	fsubs f1, f30, f1
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	b @36
	@37:
	lis r3, float_1p5708_tou_0000d348@ha
	fsubs f0, f30, f0
	lfs f1, float_1p5708_tou_0000d348@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	@36:
	fmuls f0, f31, f5
	stfs f0, 0x38(r28)
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_tou_0000d370@ha
	stw r3, 0x94(r1)
	addi r5, r4, double_to_int_tou_0000d370@l
	lis r3, float_32767_tou_0000d3a0@ha
	stw r0, 0x90(r1)
	addi r4, r3, float_32767_tou_0000d3a0@l
	lfd f2, 0x0(r5)
	lis r3, float_0p03_tou_0000d3c0@ha
	lfd f1, 0x90(r1)
	addi r6, r3, float_0p03_tou_0000d3c0@l
	lfs f0, 0x0(r4)
	lis r5, float_0p03705_tou_0000d354@ha
	fsubs f2, f1, f2
	lis r3, float_3p1416_tou_0000d344@ha
	lfs f1, float_3p1416_tou_0000d344@l(r3)
	lis r4, float_0p4967_tou_0000d358@ha
	lis r3, float_1_tou_0000d340@ha
	lfs f4, float_0p03705_tou_0000d354@l(r5)
	fdivs f2, f2, f0
	lfs f0, 0x0(r6)
	lfs f3, float_0p4967_tou_0000d358@l(r4)
	fmadds f0, f2, f0, f0
	lfs f2, float_1_tou_0000d340@l(r3)
	fcmpo cr0, f30, f1
	stfs f0, 0x3c(r28)
	cror eq, lt, eq
	bne @38
	lis r3, float_1p5708_tou_0000d348@ha
	lfs f1, float_1p5708_tou_0000d348@l(r3)
	fcmpo cr0, f30, f1
	cror eq, lt, eq
	bne @39
	fmuls f0, f30, f30
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @40
	@39:
	fsubs f0, f30, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @40
	@38:
	lis r3, float_4p7124_tou_0000d34c@ha
	lfs f0, float_4p7124_tou_0000d34c@l(r3)
	fcmpo cr0, f30, f0
	bge @41
	fsubs f0, f30, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @40
	@41:
	lis r3, float_1p5708_tou_0000d348@ha
	fsubs f0, f30, f0
	lfs f1, float_1p5708_tou_0000d348@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@40:
	fneg f0, f4
	li r0, 0x78
	mr r3, r29
	addi r4, r28, 0x10
	fmuls f0, f31, f0
	stfs f0, 0x40(r28)
	sth r0, 0x44(r28)
	bl psndSFXOn_3D
	@22:
	addi r27, r27, 0x1
	addi r28, r28, 0x48
	@20:
	lwz r3, 0x0(r26)
	lwz r0, 0x0(r3)
	cmpw r27, r0
	blt @21
	stw r0, 0x510(r3)
	bl extGetPosePtr
	lis r4, fan_wp@ha
	li r28, 0x0
	addi r31, r4, fan_wp@l
	mr r29, r3
	lwz r4, 0x0(r31)
	lwz r30, 0x4(r4)
	b @42
	@43:
	lha r0, 0x2(r30)
	cmpwi r0, 0x14
	beq @44
	bge @45
	cmpwi r0, 0xa
	beq @46
	bge @47
	cmpwi r0, 0x0
	beq @48
	b @47
	@45:
	cmpwi r0, 0x65
	beq @47
	bge @47
	cmpwi r0, 0x64
	bge @49
	b @47
	@48:
	addi r3, r30, 0x1c
	mr r4, r3
	bl PSVECNormalize
	addi r3, r30, 0x1c
	bl PSVECMag
	lwz r7, 0x10(r30)
	lis r3, float_4_tou_0000d3b4@ha
	lwz r0, 0x14(r30)
	addi r6, r3, float_4_tou_0000d3b4@l
	lis r3, float_25_tou_0000d3c4@ha
	lis r4, zero_tou_0000d328@ha
	stw r0, 0x3c(r1)
	addi r5, r3, float_25_tou_0000d3c4@l
	lfs f0, 0x0(r6)
	addi r6, r4, zero_tou_0000d328@l
	lfs f2, 0x3c(r1)
	addi r3, r1, 0x2c
	stw r7, 0x38(r1)
	li r4, 0x0
	fadds f2, f2, f0
	lfs f0, 0x0(r5)
	lwz r0, 0x18(r30)
	fadds f0, f0, f1
	lfs f1, 0x0(r6)
	stw r0, 0x40(r1)
	stfs f2, 0x3c(r1)
	lwz r5, 0x1c(r30)
	lwz r0, 0x20(r30)
	stw r5, 0x44(r1)
	stw r0, 0x48(r1)
	lwz r0, 0x24(r30)
	stw r0, 0x4c(r1)
	stfs f1, 0x48(r1)
	stfs f0, 0x68(r1)
	bl hitCheckVecFilter
	cmplwi r3, 0x0
	beq @50
	addi r3, r30, 0x1c
	addi r4, r1, 0x5c
	mr r5, r3
	bl C_VECReflect
	b @51
	@50:
	lfs f2, 0x10(r30)
	lis r3, float_0p6_tou_0000d3c8@ha
	lfs f0, 0x1c(r30)
	lfs f1, float_0p6_tou_0000d3c8@l(r3)
	fadds f0, f2, f0
	stfs f0, 0x10(r30)
	lfs f2, 0x18(r30)
	lfs f0, 0x24(r30)
	fadds f0, f2, f0
	stfs f0, 0x18(r30)
	lfs f0, 0x1c(r30)
	fmuls f0, f0, f1
	stfs f0, 0x1c(r30)
	lfs f0, 0x24(r30)
	fmuls f0, f0, f1
	stfs f0, 0x24(r30)
	@51:
	lis r3, float_neg350_tou_0000d3cc@ha
	lfs f1, 0x10(r30)
	lfs f0, float_neg350_tou_0000d3cc@l(r3)
	fcmpo cr0, f1, f0
	bge @52
	stfs f0, 0x10(r30)
	@52:
	lis r3, float_350_tou_0000d3d0@ha
	lfs f1, 0x10(r30)
	lfs f0, float_350_tou_0000d3d0@l(r3)
	fcmpo cr0, f1, f0
	ble @53
	stfs f0, 0x10(r30)
	@53:
	xoris r3, r28, 0x8000
	lis r0, 0x4330
	stw r3, 0x94(r1)
	lis r4, double_to_int_tou_0000d370@ha
	lfd f2, double_to_int_tou_0000d370@l(r4)
	lis r3, float_100_tou_0000d3ac@ha
	stw r0, 0x90(r1)
	lis r4, float_195_tou_0000d3d4@ha
	lfs f0, float_100_tou_0000d3ac@l(r3)
	lfd f1, 0x90(r1)
	lfs f3, 0x18(r30)
	fsubs f1, f1, f2
	lfs f2, float_195_tou_0000d3d4@l(r4)
	fdivs f0, f1, f0
	fadds f0, f2, f0
	fcmpo cr0, f3, f0
	ble @47
	stfs f0, 0x18(r30)
	b @47
	@46:
	lfs f1, 0x14(r30)
	lfs f0, 0x38(r30)
	fadds f0, f1, f0
	stfs f0, 0x14(r30)
	lfs f1, 0x38(r30)
	lfs f0, 0x40(r30)
	fsubs f0, f1, f0
	stfs f0, 0x38(r30)
	lfs f1, 0x10(r30)
	lfs f2, 0x18(r30)
	lfs f3, 0x2c(r30)
	lfs f4, 0x34(r30)
	bl angleABf
	lis r3, float_6p2832_tou_0000d32c@ha
	lis r6, float_0p00761_tou_0000d338@ha
	addi r5, r3, float_6p2832_tou_0000d32c@l
	lis r4, float_360_tou_0000d334@ha
	lfs f0, 0x0(r5)
	lis r5, float_0p16605_tou_0000d33c@ha
	lis r3, float_3p1416_tou_0000d344@ha
	lfs f4, float_0p00761_tou_0000d338@l(r6)
	fmuls f2, f0, f1
	lfs f0, float_360_tou_0000d334@l(r4)
	lfs f1, float_3p1416_tou_0000d344@l(r3)
	lis r4, float_1_tou_0000d340@ha
	lfs f3, float_0p16605_tou_0000d33c@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_tou_0000d340@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @54
	lis r3, float_1p5708_tou_0000d348@ha
	lfs f1, float_1p5708_tou_0000d348@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @55
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @56
	@55:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @56
	@54:
	lis r3, float_4p7124_tou_0000d34c@ha
	lfs f0, float_4p7124_tou_0000d34c@l(r3)
	fcmpo cr0, f5, f0
	bge @57
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @56
	@57:
	lis r3, float_1p5708_tou_0000d348@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_tou_0000d348@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@56:
	lis r3, float_3p1416_tou_0000d344@ha
	lfs f2, 0x3c(r30)
	lfs f1, float_3p1416_tou_0000d344@l(r3)
	lis r4, float_0p4967_tou_0000d358@ha
	lfs f0, 0x10(r30)
	lis r5, float_0p03705_tou_0000d354@ha
	fcmpo cr0, f5, f1
	lis r3, float_1_tou_0000d340@ha
	fmadds f0, f2, f4, f0
	lfs f4, float_0p03705_tou_0000d354@l(r5)
	lfs f3, float_0p4967_tou_0000d358@l(r4)
	lfs f2, float_1_tou_0000d340@l(r3)
	stfs f0, 0x10(r30)
	cror eq, lt, eq
	bne @58
	lis r3, float_1p5708_tou_0000d348@ha
	lfs f1, float_1p5708_tou_0000d348@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @59
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @60
	@59:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @60
	@58:
	lis r3, float_4p7124_tou_0000d34c@ha
	lfs f0, float_4p7124_tou_0000d34c@l(r3)
	fcmpo cr0, f5, f0
	bge @61
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @60
	@61:
	lis r3, float_1p5708_tou_0000d348@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_tou_0000d348@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@60:
	fneg f1, f4
	lfs f2, 0x3c(r30)
	lfs f0, 0x18(r30)
	fmadds f0, f2, f1, f0
	stfs f0, 0x18(r30)
	lha r3, 0x44(r30)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x44(r30)
	bge @47
	li r0, 0x64
	sth r0, 0x2(r30)
	b @47
	@44:
	lha r3, 0x44(r30)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x44(r30)
	ble @62
	lfs f1, 0x2c(r30)
	lfs f0, 0x38(r30)
	fadds f0, f1, f0
	stfs f0, 0x2c(r30)
	lfs f1, 0x30(r30)
	lfs f0, 0x3c(r30)
	fadds f0, f1, f0
	stfs f0, 0x30(r30)
	lfs f1, 0x34(r30)
	lfs f0, 0x40(r30)
	fadds f0, f1, f0
	stfs f0, 0x34(r30)
	lfs f1, 0x10(r30)
	lfs f0, 0x2c(r30)
	fadds f0, f1, f0
	stfs f0, 0x10(r30)
	lfs f1, 0x14(r30)
	lfs f0, 0x30(r30)
	fadds f0, f1, f0
	stfs f0, 0x14(r30)
	lfs f1, 0x18(r30)
	lfs f0, 0x34(r30)
	fadds f0, f1, f0
	stfs f0, 0x18(r30)
	b @47
	@62:
	li r0, 0x64
	sth r0, 0x2(r30)
	b @47
	@49:
	lwz r0, 0x0(r29)
	clrrwi r0, r0, 2
	stw r0, 0x0(r29)
	lha r3, 0x2(r30)
	addi r0, r3, 0x1
	sth r0, 0x2(r30)
	@47:
	lhz r0, 0x0(r30)
	clrlwi. r0, r0, 31
	beq @63
	lis r3, fan_wp@ha
	lwz r4, fan_wp@l(r3)
	lwz r3, 0x510(r4)
	subi r0, r3, 0x1
	stw r0, 0x510(r4)
	b @64
	@63:
	lha r0, 0x2(r30)
	cmpwi r0, 0x0
	beq @64
	lis r3, fan_wp@ha
	lwz r4, fan_wp@l(r3)
	lwz r3, 0x510(r4)
	subi r0, r3, 0x1
	stw r0, 0x510(r4)
	@64:
	lfs f0, 0x10(r30)
	lwz r3, 0xc(r29)
	stfs f0, 0xc(r3)
	lfs f0, 0x14(r30)
	lwz r3, 0xc(r29)
	stfs f0, 0x1c(r3)
	lfs f0, 0x18(r30)
	lwz r3, 0xc(r29)
	stfs f0, 0x2c(r3)
	lfs f1, 0x14(r1)
	lfs f2, 0x1c(r1)
	lfs f3, 0x10(r30)
	lfs f4, 0x18(r30)
	bl angleABf
	stfs f1, 0x4(r29)
	addi r28, r28, 0x1
	addi r29, r29, 0x20
	addi r30, r30, 0x48
	@42:
	lwz r3, 0x0(r31)
	lwz r0, 0x0(r3)
	cmpw r28, r0
	blt @43
	lwz r3, 0x514(r3)
	addi r4, r1, 0x14
	bl psndSFX_pos
	lis r3, fan_wp@ha
	lwz r5, fan_wp@l(r3)
	lbz r4, 0x518(r5)
	lwz r3, 0x510(r5)
	lwz r0, 0x0(r5)
	mullw r4, r4, r3
	lwz r3, 0x514(r5)
	divw r0, r4, r0
	clrlwi r4, r0, 24
	bl psndSFX_vol
	psq_l f31, 0xd8(r1), 0, 0
	lfd f31, 0xd0(r1)
	psq_l f30, 0xc8(r1), 0, 0
	lfd f30, 0xc0(r1)
	lmw r25, 0xa4(r1)
	lwz r0, 0xe4(r1)
	mtlr r0
	addi r1, r1, 0xe0
	blr
}

asm void fan_disp(CameraId camera, void* param) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl extLoadRenderMode
	bl extLoadVertex
	bl extLoadTexture
	bl extLoadTev
	bl extDraw
	bl extLoadTextureExit
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void ext_fan_init(void) {
	nofralloc
	stwu r1, -0x100(r1)
	mflr r0
	stw r0, 0x104(r1)
	stfd f31, 0xf0(r1)
	psq_st f31, 0xf8(r1), 0, 0
	stfd f30, 0xe0(r1)
	psq_st f30, 0xe8(r1), 0, 0
	stfd f29, 0xd0(r1)
	psq_st f29, 0xd8(r1), 0, 0
	stfd f28, 0xc0(r1)
	psq_st f28, 0xc8(r1), 0, 0
	stfd f27, 0xb0(r1)
	psq_st f27, 0xb8(r1), 0, 0
	stfd f26, 0xa0(r1)
	psq_st f26, 0xa8(r1), 0, 0
	stmw r20, 0x70(r1)
	li r3, 0x51c
	bl _mapAlloc
	lis r5, fan_wp@ha
	li r4, 0x0
	addi r6, r5, fan_wp@l
	li r5, 0x51c
	stw r3, 0x0(r6)
	bl memset
	bl extGetPoseNum
	lis r4, fan_wp@ha
	addi r5, r4, fan_wp@l
	lwz r4, 0x0(r5)
	stw r3, 0x0(r4)
	lwz r3, 0x0(r5)
	lwz r0, 0x0(r3)
	mulli r3, r0, 0x48
	bl _mapAlloc
	lis r5, fan_wp@ha
	li r4, 0x0
	addi r6, r5, fan_wp@l
	lwz r5, 0x0(r6)
	stw r3, 0x4(r5)
	lwz r3, 0x0(r6)
	lwz r0, 0x0(r3)
	lwz r3, 0x4(r3)
	mulli r5, r0, 0x48
	bl memset
	lis r3, ext_fan_data@ha
	lis r4, zero_tou_0000d3d8@ha
	addi r28, r3, ext_fan_data@l
	li r31, 0x0
	addi r3, r1, 0x20
	addi r4, r4, zero_tou_0000d3d8@l
	bl strcpy
	lis r4, zero_tou_0000d3d8@ha
	addi r3, r1, 0x40
	addi r4, r4, zero_tou_0000d3d8@l
	bl strcpy
	lis r3, fan_wp@ha
	li r0, -0x1
	addi r29, r3, fan_wp@l
	lwz r3, 0x0(r29)
	stw r0, 0x8(r3)
	@1:
	lwz r3, 0x0(r28)
	addi r4, r1, 0x20
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	lwz r4, 0x0(r28)
	addi r3, r1, 0x20
	bl strcpy
	lis r4, zero_tou_0000d3d8@ha
	addi r3, r1, 0x40
	addi r4, r4, zero_tou_0000d3d8@l
	bl strcpy
	@2:
	lwz r3, 0x4(r28)
	addi r4, r1, 0x40
	bl strcmp
	cmpwi r3, 0x0
	beq @3
	lwz r4, 0x4(r28)
	addi r3, r1, 0x40
	bl strcpy
	lis r3, fan_wp@ha
	mr r30, r31
	lwz r4, fan_wp@l(r3)
	lwz r3, 0x8(r4)
	addi r0, r3, 0x1
	stw r0, 0x8(r4)
	@3:
	lwz r5, 0x0(r29)
	addi r4, r1, 0x20
	lwz r0, 0x8(r5)
	mulli r3, r0, 0x28
	addi r3, r3, 0xc
	add r3, r5, r3
	bl strcpy
	lwz r5, 0x0(r29)
	addi r4, r1, 0x40
	lwz r0, 0x8(r5)
	mulli r3, r0, 0x28
	addi r3, r3, 0x1c
	add r3, r5, r3
	bl strcpy
	lwz r6, 0x0(r29)
	subf r3, r30, r31
	addi r5, r3, 0x1
	li r4, 0x1
	lwz r0, 0x8(r6)
	addi r31, r31, 0x1
	mulli r3, r0, 0x28
	addi r0, r3, 0x2c
	stwx r30, r6, r0
	lwz r6, 0x0(r29)
	lwz r0, 0x8(r6)
	mulli r3, r0, 0x28
	addi r0, r3, 0x30
	stwx r5, r6, r0
	lwz r5, 0x0(r29)
	lfs f0, 0x8(r28)
	lwz r0, 0x8(r5)
	mulli r3, r0, 0x28
	addi r0, r3, 0x28
	stfsx f0, r5, r0
	lwz r5, 0x0(r29)
	lwz r0, 0x8(r5)
	mulli r3, r0, 0x28
	addi r0, r3, 0x24
	sthx r4, r5, r0
	lwzu r0, 0xc(r28)
	cmplwi r0, 0x0
	bne @1
	lis r3, fan_wp@ha
	lwz r4, fan_wp@l(r3)
	lwz r3, 0x8(r4)
	addi r0, r3, 0x1
	stw r0, 0x8(r4)
	bl extGetPosePtr
	lis r4, fan_wp@ha
	lis r9, zero_tou_0000d328@ha
	addi r29, r4, fan_wp@l
	lis r8, double_to_int_tou_0000d370@ha
	lwz r12, 0x0(r29)
	lis r7, float_32767_tou_0000d3a0@ha
	addi r11, r9, zero_tou_0000d328@l
	addi r10, r8, double_to_int_tou_0000d370@l
	addi r9, r7, float_32767_tou_0000d3a0@l
	lis r6, float_360_tou_0000d334@ha
	addi r8, r6, float_360_tou_0000d334@l
	lis r5, float_200_tou_0000d3dc@ha
	addi r6, r5, float_200_tou_0000d3dc@l
	lis r4, float_neg100_tou_0000d3b0@ha
	addi r5, r4, float_neg100_tou_0000d3b0@l
	lis r7, vec3_tou_0000d028@ha
	lis r4, vec3_tou_0000d034@ha
	lwz r25, 0x4(r12)
	lfs f26, 0x0(r11)
	mr r26, r3
	lfd f27, 0x0(r10)
	addi r31, r7, vec3_tou_0000d028@l
	lfs f28, 0x0(r9)
	addi r24, r4, vec3_tou_0000d034@l
	lfs f29, 0x0(r8)
	li r27, 0x0
	lfs f30, 0x0(r6)
	lis r30, 0x4330
	lfs f31, 0x0(r5)
	b @4
	@5:
	lwz r0, 0x0(r26)
	ori r0, r0, 0x7
	stw r0, 0x0(r26)
	lwz r3, 0xc(r26)
	bl PSMTXIdentity
	lwz r3, 0xc(r26)
	stfs f26, 0xc(r3)
	lwz r3, 0xc(r26)
	stfs f26, 0x1c(r3)
	lwz r3, 0xc(r26)
	stfs f26, 0x2c(r3)
	bl rand
	xoris r0, r3, 0x8000
	stw r30, 0x60(r1)
	li r3, 0x3e8
	stw r0, 0x64(r1)
	lfd f0, 0x60(r1)
	fsubs f0, f0, f27
	fdivs f0, f0, f28
	fmadds f0, f0, f29, f26
	stfs f0, 0x4(r26)
	bl irand
	li r4, 0x3
	divw r0, r3, r4
	mullw r0, r0, r4
	subf r0, r0, r3
	cmpwi r0, 0x1
	beq @6
	bge @7
	cmpwi r0, 0x0
	bge @8
	b @7
	b @7
	@8:
	lis r4, fan_wp@ha
	lis r3, str_000046C8@ha
	addi r23, r4, fan_wp@l
	lis r4, str_000046BC@ha
	lwz r5, 0x0(r23)
	addi r21, r3, str_000046C8@l
	addi r22, r4, str_000046BC@l
	li r28, 0x0
	addi r20, r5, 0xc
	b @9
	@10:
	mr r3, r20
	mr r4, r22
	bl strcmp
	cmpwi r3, 0x0
	bne @11
	mr r4, r21
	addi r3, r20, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @12
	@11:
	addi r28, r28, 0x1
	addi r20, r20, 0x28
	@9:
	lwz r3, 0x0(r23)
	lwz r0, 0x8(r3)
	cmpw r28, r0
	blt @10
	@12:
	lis r3, fan_wp@ha
	addi r3, r3, fan_wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x8(r3)
	cmpw r28, r0
	bge @13
	lha r0, 0x4(r25)
	cmpw r0, r28
	beq @13
	lis r3, gp@ha
	sth r28, 0x4(r25)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0xc(r25)
	stw r0, 0x8(r25)
	b @13
	@6:
	lis r4, fan_wp@ha
	lis r3, str_000046DC@ha
	addi r23, r4, fan_wp@l
	lis r4, str_000046D0@ha
	lwz r5, 0x0(r23)
	addi r21, r3, str_000046DC@l
	addi r22, r4, str_000046D0@l
	li r28, 0x0
	addi r20, r5, 0xc
	b @14
	@15:
	mr r3, r20
	mr r4, r22
	bl strcmp
	cmpwi r3, 0x0
	bne @16
	mr r4, r21
	addi r3, r20, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @17
	@16:
	addi r28, r28, 0x1
	addi r20, r20, 0x28
	@14:
	lwz r3, 0x0(r23)
	lwz r0, 0x8(r3)
	cmpw r28, r0
	blt @15
	@17:
	lis r3, fan_wp@ha
	addi r3, r3, fan_wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x8(r3)
	cmpw r28, r0
	bge @13
	lha r0, 0x4(r25)
	cmpw r0, r28
	beq @13
	lis r3, gp@ha
	sth r28, 0x4(r25)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0xc(r25)
	stw r0, 0x8(r25)
	b @13
	@7:
	lis r4, fan_wp@ha
	lis r3, str_000046F0@ha
	addi r21, r4, fan_wp@l
	lis r4, str_000046E4@ha
	lwz r5, 0x0(r21)
	addi r23, r3, str_000046F0@l
	addi r22, r4, str_000046E4@l
	li r28, 0x0
	addi r20, r5, 0xc
	b @18
	@19:
	mr r3, r20
	mr r4, r22
	bl strcmp
	cmpwi r3, 0x0
	bne @20
	mr r4, r23
	addi r3, r20, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @21
	@20:
	addi r28, r28, 0x1
	addi r20, r20, 0x28
	@18:
	lwz r3, 0x0(r21)
	lwz r0, 0x8(r3)
	cmpw r28, r0
	blt @19
	@21:
	lis r3, fan_wp@ha
	addi r3, r3, fan_wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x8(r3)
	cmpw r28, r0
	bge @13
	lha r0, 0x4(r25)
	cmpw r0, r28
	beq @13
	lis r3, gp@ha
	sth r28, 0x4(r25)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0xc(r25)
	stw r0, 0x8(r25)
	@13:
	li r0, 0x0
	sth r0, 0x2(r25)
	lwz r4, 0x0(r31)
	lwz r3, 0x4(r31)
	lwz r0, 0x8(r31)
	stw r4, 0x14(r1)
	stw r3, 0x18(r1)
	stw r0, 0x1c(r1)
	bl rand
	xoris r0, r3, 0x8000
	stw r30, 0x60(r1)
	stw r0, 0x64(r1)
	lfd f0, 0x60(r1)
	fsubs f0, f0, f27
	fdivs f0, f0, f28
	fmadds f0, f0, f30, f31
	stfs f0, 0x14(r1)
	bl rand
	xoris r0, r3, 0x8000
	lwz r3, 0x14(r1)
	stw r0, 0x6c(r1)
	addi r27, r27, 0x1
	lwz r0, 0x18(r1)
	addi r26, r26, 0x20
	stw r30, 0x68(r1)
	lfd f0, 0x68(r1)
	stw r3, 0x10(r25)
	fsubs f0, f0, f27
	stw r0, 0x14(r25)
	fdivs f0, f0, f28
	fmadds f0, f0, f30, f31
	stfs f0, 0x1c(r1)
	lwz r0, 0x1c(r1)
	stw r0, 0x18(r25)
	lwz r3, 0x0(r24)
	lwz r0, 0x4(r24)
	stw r3, 0x1c(r25)
	stw r0, 0x20(r25)
	lwz r0, 0x8(r24)
	stw r0, 0x24(r25)
	addi r25, r25, 0x48
	@4:
	lwz r3, 0x0(r29)
	lwz r0, 0x0(r3)
	cmpw r27, r0
	blt @5
	lis r4, vec3_tou_0000d040@ha
	lis r3, str_00004AB0@ha
	addi r7, r4, vec3_tou_0000d040@l
	lwz r6, 0x0(r7)
	addi r4, r1, 0x8
	lwz r5, 0x4(r7)
	addi r3, r3, str_00004AB0@l
	lwz r0, 0x8(r7)
	stw r6, 0x8(r1)
	stw r5, 0xc(r1)
	stw r0, 0x10(r1)
	bl psndSFXOn_3D
	lis r4, fan_wp@ha
	addi r5, r4, fan_wp@l
	lwz r4, 0x0(r5)
	stw r3, 0x514(r4)
	lwz r3, 0x0(r5)
	lwz r3, 0x514(r3)
	bl psndSFX_get_vol
	lis r4, fan_wp@ha
	addi r4, r4, fan_wp@l
	lwz r4, 0x0(r4)
	stb r3, 0x518(r4)
	psq_l f31, 0xf8(r1), 0, 0
	lfd f31, 0xf0(r1)
	psq_l f30, 0xe8(r1), 0, 0
	lfd f30, 0xe0(r1)
	psq_l f29, 0xd8(r1), 0, 0
	lfd f29, 0xd0(r1)
	psq_l f28, 0xc8(r1), 0, 0
	lfd f28, 0xc0(r1)
	psq_l f27, 0xb8(r1), 0, 0
	lfd f27, 0xb0(r1)
	psq_l f26, 0xa8(r1), 0, 0
	lfd f26, 0xa0(r1)
	lmw r20, 0x70(r1)
	lwz r0, 0x104(r1)
	mtlr r0
	addi r1, r1, 0x100
	blr
}

asm static f32 randf(f32 min, f32 max) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x20(r1)
	psq_st f31, 0x28(r1), 0, 0
	stfd f30, 0x10(r1)
	psq_st f30, 0x18(r1), 0, 0
	fmr f30, f1
	fmr f31, f2
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xc(r1)
	lis r4, double_to_int_tou_0000d370@ha
	lis r3, float_32767_tou_0000d3a0@ha
	lfd f3, double_to_int_tou_0000d370@l(r4)
	stw r0, 0x8(r1)
	fsubs f0, f31, f30
	lfs f1, float_32767_tou_0000d3a0@l(r3)
	lfd f2, 0x8(r1)
	fsubs f2, f2, f3
	fdivs f1, f2, f1
	fmadds f1, f1, f0, f30
	psq_l f31, 0x28(r1), 0, 0
	lfd f31, 0x20(r1)
	psq_l f30, 0x18(r1), 0, 0
	lwz r0, 0x34(r1)
	lfd f30, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm static void pose_change(Fan* fan, const char* name, const char* anim) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r6, fan_wp@ha
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	addi r30, r6, fan_wp@l
	mr r31, r3
	mr r26, r4
	mr r27, r5
	li r28, 0x0
	lwz r3, 0x0(r30)
	addi r29, r3, 0xc
	b @1
	@2:
	mr r3, r29
	mr r4, r26
	bl strcmp
	cmpwi r3, 0x0
	bne @3
	mr r4, r27
	addi r3, r29, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @4
	@3:
	addi r28, r28, 0x1
	addi r29, r29, 0x28
	@1:
	lwz r3, 0x0(r30)
	lwz r0, 0x8(r3)
	cmpw r28, r0
	blt @2
	@4:
	lis r3, fan_wp@ha
	addi r3, r3, fan_wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x8(r3)
	cmpw r28, r0
	bge @5
	lha r0, 0x4(r31)
	cmpw r0, r28
	beq @5
	lis r3, gp@ha
	sth r28, 0x4(r31)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0xc(r31)
	stw r0, 0x8(r31)
	@5:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm static void pose_main(void) {
	nofralloc
	stwu r1, -0x80(r1)
	mflr r0
	stw r0, 0x84(r1)
	stfd f31, 0x70(r1)
	psq_st f31, 0x78(r1), 0, 0
	stfd f30, 0x60(r1)
	psq_st f30, 0x68(r1), 0, 0
	stfd f29, 0x50(r1)
	psq_st f29, 0x58(r1), 0, 0
	stfd f28, 0x40(r1)
	psq_st f28, 0x48(r1), 0, 0
	stmw r22, 0x18(r1)
	bl extGetPosePtr
	lis r4, fan_wp@ha
	lis r7, float_60_tou_0000d364@ha
	addi r29, r4, fan_wp@l
	lis r6, float_1000_tou_0000d368@ha
	lwz r9, 0x0(r29)
	lis r5, float_1_tou_0000d340@ha
	lis r4, double_to_int_tou_0000d370@ha
	lis r8, gp@ha
	lwz r24, 0x4(r9)
	mr r25, r3
	lfs f28, float_60_tou_0000d364@l(r7)
	addi r30, r8, gp@l
	lfs f29, float_1000_tou_0000d368@l(r6)
	li r26, 0x0
	lfs f30, float_1_tou_0000d340@l(r5)
	lis r31, 0x8000
	lfd f31, double_to_int_tou_0000d370@l(r4)
	lis r23, 0x4330
	b @1
	@2:
	lwz r3, 0xf8(r31)
	li r0, 0x3e8
	lwz r4, 0x0(r30)
	li r5, 0x0
	srwi r3, r3, 2
	lha r7, 0x4(r24)
	divwu r6, r3, r0
	lwz r27, 0x3c(r4)
	lwz r0, 0xc(r24)
	lwz r28, 0x38(r4)
	subfc r4, r0, r27
	lwz r0, 0x8(r24)
	mulli r7, r7, 0x28
	subfe r3, r0, r28
	addi r22, r7, 0xc
	add r22, r8, r22
	bl __div2u
	bl __cvt_ull_flt
	fmuls f1, f28, f1
	lfs f0, 0x1c(r22)
	fdivs f1, f1, f29
	fdivs f1, f1, f0
	fcmpo cr0, f1, f30
	cror eq, gt, eq
	bne @3
	stw r27, 0xc(r24)
	lis r3, zero_tou_0000d328@ha
	lfs f1, zero_tou_0000d328@l(r3)
	stw r28, 0x8(r24)
	@3:
	lwz r3, 0x24(r22)
	addi r26, r26, 0x1
	stw r23, 0x8(r1)
	addi r24, r24, 0x48
	subi r0, r3, 0x1
	lwz r3, 0x20(r22)
	xoris r0, r0, 0x8000
	stw r0, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f31
	fmuls f0, f0, f1
	fctiwz f0, f0
	stfd f0, 0x10(r1)
	lwz r0, 0x14(r1)
	add r0, r3, r0
	stw r0, 0x10(r25)
	addi r25, r25, 0x20
	@1:
	lwz r8, 0x0(r29)
	lwz r0, 0x0(r8)
	cmpw r26, r0
	blt @2
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	psq_l f30, 0x68(r1), 0, 0
	lfd f30, 0x60(r1)
	psq_l f29, 0x58(r1), 0, 0
	lfd f29, 0x50(r1)
	psq_l f28, 0x48(r1), 0, 0
	lfd f28, 0x40(r1)
	lmw r22, 0x18(r1)
	lwz r0, 0x84(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm static void pose_init(void) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	lis r4, zero_tou_0000d3d8@ha
	lis r3, ext_fan_data@ha
	stw r0, 0x64(r1)
	addi r0, r3, ext_fan_data@l
	addi r3, r1, 0x28
	addi r4, r4, zero_tou_0000d3d8@l
	stmw r28, 0x50(r1)
	li r29, 0x0
	mr r30, r0
	bl strcpy
	lis r4, zero_tou_0000d3d8@ha
	addi r3, r1, 0x8
	addi r4, r4, zero_tou_0000d3d8@l
	bl strcpy
	lis r3, fan_wp@ha
	li r0, -0x1
	addi r31, r3, fan_wp@l
	lwz r3, 0x0(r31)
	stw r0, 0x8(r3)
	@1:
	lwz r3, 0x0(r30)
	addi r4, r1, 0x28
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	lwz r4, 0x0(r30)
	addi r3, r1, 0x28
	bl strcpy
	lis r4, zero_tou_0000d3d8@ha
	addi r3, r1, 0x8
	addi r4, r4, zero_tou_0000d3d8@l
	bl strcpy
	@2:
	lwz r3, 0x4(r30)
	addi r4, r1, 0x8
	bl strcmp
	cmpwi r3, 0x0
	beq @3
	lwz r4, 0x4(r30)
	addi r3, r1, 0x8
	bl strcpy
	lis r3, fan_wp@ha
	mr r28, r29
	lwz r4, fan_wp@l(r3)
	lwz r3, 0x8(r4)
	addi r0, r3, 0x1
	stw r0, 0x8(r4)
	@3:
	lwz r5, 0x0(r31)
	addi r4, r1, 0x28
	lwz r0, 0x8(r5)
	mulli r3, r0, 0x28
	addi r3, r3, 0xc
	add r3, r5, r3
	bl strcpy
	lwz r5, 0x0(r31)
	addi r4, r1, 0x8
	lwz r0, 0x8(r5)
	mulli r3, r0, 0x28
	addi r3, r3, 0x1c
	add r3, r5, r3
	bl strcpy
	lwz r6, 0x0(r31)
	subf r3, r28, r29
	addi r5, r3, 0x1
	li r4, 0x1
	lwz r0, 0x8(r6)
	addi r29, r29, 0x1
	mulli r3, r0, 0x28
	addi r0, r3, 0x2c
	stwx r28, r6, r0
	lwz r6, 0x0(r31)
	lwz r0, 0x8(r6)
	mulli r3, r0, 0x28
	addi r0, r3, 0x30
	stwx r5, r6, r0
	lwz r5, 0x0(r31)
	lfs f0, 0x8(r30)
	lwz r0, 0x8(r5)
	mulli r3, r0, 0x28
	addi r0, r3, 0x28
	stfsx f0, r5, r0
	lwz r5, 0x0(r31)
	lwz r0, 0x8(r5)
	mulli r3, r0, 0x28
	addi r0, r3, 0x24
	sthx r4, r5, r0
	lwzu r0, 0xc(r30)
	cmplwi r0, 0x0
	bne @1
	lis r3, fan_wp@ha
	lwz r4, fan_wp@l(r3)
	lwz r3, 0x8(r4)
	addi r0, r3, 0x1
	stw r0, 0x8(r4)
	lmw r28, 0x50(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
