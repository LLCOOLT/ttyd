#include "battle/battle.h"
#include "battle/battle_audience.h"
#include "battle/battle_database_common.h"
#include "battle/battle_unit.h"
#include "data/item_data.h"
#include "driver/dispdrv.h"
#include "driver/msgdrv.h"
#include "driver/windowdrv.h"
#include "eff/eff_hit.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr_cmd.h"
#include "manager/fontmgr.h"
#include "mario/mario_pouch.h"
#include "pmario_sound.h"

#pragma optimize_for_size on

extern BattleWork* _battleWorkPointer;
extern ItemData itemDataTable[];
extern int sprintf(char* str, const char* format, ...);
extern void* itemEntry(const char* name, s32 itemId, s32 type, s32 evtId, s32 a5, f32 x, f32 y, f32 z);
extern void itemDelete(const char* name);
extern void psndSFX_pit(s32 id, s32 pitch);
extern s32 BattleAudience_GetPresentItemType(void);
extern s32 BattleAudience_GetPresentItemNo(void);
extern s32 BattleAudience_GetPresentTargetUnitId(void);
extern void BattleAudience_SetPresentItemNo(s32 no);

USER_FUNC(_damage);
USER_FUNC(_delete_present_item);
USER_FUNC(_get_item_announce);
USER_FUNC(_get_present_target_id);
USER_FUNC(_get_present_item);
USER_FUNC(_attack_aud);
USER_FUNC(_get_attack_aud_no);
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_GetBodyId[];
extern s32 btlevtcmd_GetUnitId[];
extern s32 btlevtcmd_StartWaitEvent[];
extern s32 btlevtcmd_StopWaitEvent[];
extern s32 btlevtcmd_WaitEventEnd[];

extern s32 btlataudevtPresentItem_Damage[];
extern s32 btlataudevtPresentItem_Get[];

s32 _get_attack_aud_no(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    s32 a0 = args[0];
    s32 a1 = args[1];
    s32 a2 = args[2];
    s32 a3 = args[3];
    s32 no;
    f32 x;
    f32 y;
    f32 z;

    BattleAudience_GetItemOn2(&no, &x, &y, &z, NULL);
    if (a0 != -250000000) {
        evtSetValue(event, a0, no);
    }
    if (a1 != -250000000) {
        evtSetValue(event, a1, (s32)x);
    }
    if (a2 != -250000000) {
        evtSetValue(event, a2, (s32)y);
    }
    if (a3 != -250000000) {
        evtSetValue(event, a3, (s32)z);
    }
    return 2;
}

s32 _attack_aud(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    s32 no;
    s32 mode;
    const char* sfx;
    f32 pos[3];

    no = evtGetValue(event, args[0]);
    mode = evtGetValue(event, args[1]);
    sfx = NULL;
    BattleAudience_GetItemOn2(&no, &pos[0], &pos[1], &pos[2], NULL);
    pos[1] += 32.0f;
    if (mode != 1) {
        effHitEntry(0, 3, pos[0], pos[1], pos[2], 1.0f);
        sfx = "SFX_BTL_DAMAGED_PLIABLE1\0\0\0";
    }
    BattleAudience_GetPosition(no, &pos[0], &pos[1], &pos[2]);
    if (sfx) {
        psndSFX_pit(psndSFXOn_3D(sfx, (Vec*)pos), 0x3FF);
    }
    BattleAudience_Attack(no);
    return 2;
}

s32 _check_aud_item_type(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    s32 out = args[0];
    s32 item;
    s32 flag;

    evtSetValue(event, out, 1);
    BattleAudience_GetItemOn2(NULL, NULL, NULL, NULL, (ItemType*)&item);
    if (item == 0) {
        return 2;
    }
    if (item >= 0xEC && item < 0xF0) {
        flag = 1;
    } else {
        flag = 0;
    }
    evtSetValue(event, out, flag);
    return 2;
}

s32 _delete_present_item(EventEntry* event, BOOL isFirstCall) {
    s32 out = event->args[0];
    s32 item = BattleAudience_GetPresentItemNo();

    if (out != -250000000) {
        evtSetValue(event, out, item);
    }
    BattleAudience_SetPresentItemNo(0);
    return 2;
}

s32 _get_present_item(EventEntry* event, BOOL isFirstCall) {
    BattleWork* wp = _battleWorkPointer;
    s32 item = BattleAudience_GetPresentItemNo();
    s32 id = BattleAudience_GetPresentTargetUnitId();
    BattleUnit* unit = BattleGetUnitPtr(wp, id);

    if (unit->mAlliance == 0) {
        pouchGetItem(item);
    } else if (unit->heldItem == 0) {
        unit->heldItem = item;
    }
    return 2;
}

s32 _get_present_target_id(EventEntry* event, BOOL isFirstCall) {
    s32 out = event->args[0];

    evtSetValue(event, out, BattleAudience_GetPresentTargetUnitId());
    return 2;
}

void _get_item_announce_disp(s32 cameraId, void* param) {
    u16 lines;
    const char* itemName;
    char buf[128];
    const char* msg;
    s32 width;
    s32 no;
    f32 x;
    f32 y;
    GXColor col;

    no = BattleAudience_GetPresentItemNo();
    itemName = msgSearch(itemDataTable[no].name);
    msg = msgSearch("btl_msg_get_item");
    sprintf(buf, msg, itemName);
    width = FontGetMessageWidthLine(buf, &lines);
    lines++;
    x = 0.0f;
    y = 60.0f;
    windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, (x - width / 2) - 10.0f, 34.0f, width + 20, lines * 29 + 3, 10.0f);
    FontDrawStart();
    FontDrawMessage(x - width / 2, (s32)y - 29, buf);
}

s32 _get_item_announce(EventEntry* event, BOOL isFirstCall) {
    BattleWork* wp = _battleWorkPointer;
    s32 item = BattleAudience_GetPresentItemNo();

    if (isFirstCall) {
        s32 id = BattleAudience_GetPresentTargetUnitId();
        BattleUnit* unit = BattleGetUnitPtr(wp, id);
        f32 x;
        f32 y;
        f32 z;

        BtlUnit_GetPos(unit, &x, &y, &z);
        y = y + (unit->mSizeMultiplier * (f32)BtlUnit_GetHeight(unit) + 8.0f);
        event->userdatap[1] = itemEntry(NULL, item, 0x11, -1, 0, x, y, z);
        event->userdata[2] = 90;
    } else {
        if (event->userdata[2] > 0) {
            event->userdata[2]--;
        }
        if (event->userdata[2] <= 0) {
            itemDelete((char*)event->userdatap[1] + 0xC);
            return 2;
        }
    }
    dispEntry(8, 900.0f, 1, (void*)_get_item_announce_disp, NULL);
    return 0;
}

s32 _damage(EventEntry* event, BOOL isFirstCall) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = BattleAudience_GetPresentTargetUnitId();
    BattleUnit* unit = BattleGetUnitPtr(wp, id);
    s32 body = BtlUnit_GetBodyPartsId(unit);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, body);
    u8* aud;

    evtGetValue(event, args[0]);
    aud = (u8*)BattleAudienceBaseGetPtr();
    BattleActionCommandResetDefenceResult();
    BattleCheckDamage(BattleGetSystemPtr(wp), unit, (struct BattleWorkUnitPart*)part, (BattleWeapon*)(aud + 0x137FC), 0x100);
    return 2;
}

s32* btlataudGetMoveEventPtr(void) {
    switch (BattleAudience_GetPresentItemType()) {
        case 1:
            return btlataudevtPresentItem_Damage;
        case 0:
        default:
            return btlataudevtPresentItem_Get;
    }
}








__declspec(section ".data") static s32 btlataudevtDummyPad[1] = {0};
s32 btlataudevtDummy[] = {
    327771, (s32)_get_attack_aud_no, -29999997, -30000000, -29999999, -29999998, 196699,
    (s32)_attack_aud, -29999997, 0, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};
s32* btlataudGetAttackEventPtr(s32 unitId) {
    s32* p = BtlUnit_GetData(BattleGetUnitPtr(_battleWorkPointer, unitId), 6);
    if (p == NULL) {
        p = btlataudevtDummy;
    }
    return p;
}

EVT_BEGIN(btlataudevtPresentItem_Damage)
    CALL(_delete_present_item, LW(0))
    BEGIN_INLINE_EVENT_GET_ID(LW(15))
        CALL(_damage, LW(0))
    END_INLINE_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    RETURN
EVT_END()

s32 btlataudevtPresentItem_Get[] = {
    131163, (s32)_get_present_target_id, -29999997, 131163, (s32)btlevtcmd_StopWaitEvent, -2, 196699, (s32)btlevtcmd_GetUnitId,
    -2, -30000000, 131097, -30000000, -29999997, 131163, (s32)btlevtcmd_StopWaitEvent, -29999997,
    33, 65627, (s32)_get_present_item, 196699, (s32)btlevtcmd_GetBodyId, -29999997, -29999996, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -29999997, -29999996, 52, 65627, (s32)_get_item_announce, 131163, (s32)_delete_present_item,
    -250000000, 196699, (s32)btlevtcmd_GetUnitId, -2, -30000000, 131097, -30000000, -29999997,
    131163, (s32)btlevtcmd_StartWaitEvent, -29999997, 33, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    1,
};

