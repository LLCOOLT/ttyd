// Battle action records: counts and points used to judge the conditions of the battle ranking.
#include "battle/battle_actrecord.h"
#include "battle/battle.h"

// this unit is size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on
// inlining off for BtlActRec_AddCount, BtlActRec_AddPoint, BtlActRec_JudgeTurnRuleKeep and 5 more, as in the original (the object differs without it)
#pragma dont_inline on
static s32 _check_turn_count_0_end(s32 n);
static s32 _check_turn_count_0_turn(s32 n);
static s32 _check_use(s32 n);
static s32 _check_no_use(s32 n);

void BtlActRec_AddCount(u8* count) {
    if (*count < 100) {
        *count = *count + 1;
    }
}

void BtlActRec_AddPoint(u8* point, s32 amount) {
    *point += amount;
    if (*point > 100) {
        *point = 100;
    }
}

void BtlActRec_JudgeTurnRuleKeep(void) {
    s32 v;
    BattleWork* wp = _battleWorkPointer;
    FieldBattleInfo* rec = wp->fbatInfo;
    BattleActRecord* ar = &wp->actRecord;
    switch (rec->ruleType) {
        case ACT_RECORD_COND_WAIT_TURNS_BEFORE_MARIO_ACTIONS:
        case ACT_RECORD_COND_WAIT_TURNS_BEFORE_PARTNER_ACTIONS:
        case ACT_RECORD_COND_WAIT_TURNS_BEFORE_PARTY_ACTIONS:
            if (rec->ruleType == ACT_RECORD_COND_WAIT_TURNS_BEFORE_PARTY_ACTIONS) {
                v = ar->marioJumpMoves + ar->marioHammerMoves + ar->marioSpecialAttacks + ar->marioSpecialSupports + ar->marioAttackItems + ar->marioSupportItems + ar->marioPartyChanges + ar->marioCharges + ar->marioSuperCharges + ar->marioEscapes + ar->partnerAttackMoves + ar->partnerSupportMoves + ar->partnerAttackItems + ar->partnerSupportItems + ar->partnerPartyChanges + ar->partnerCharges + ar->partnerSuperCharges + ar->partnerEscapes;
            } else if (rec->ruleType == ACT_RECORD_COND_WAIT_TURNS_BEFORE_MARIO_ACTIONS) {
                v = ar->marioJumpMoves + ar->marioHammerMoves + ar->marioSpecialAttacks + ar->marioSpecialSupports + ar->marioAttackItems + ar->marioSupportItems + ar->marioPartyChanges + ar->marioCharges + ar->marioSuperCharges + ar->marioEscapes;
            } else {
                v = ar->partnerAttackMoves + ar->partnerSupportMoves + ar->partnerAttackItems + ar->partnerSupportItems + ar->partnerPartyChanges + ar->partnerCharges + ar->partnerSuperCharges + ar->partnerEscapes;
            }
            _check_turn_count_0_turn(v);
            break;
        case ACT_RECORD_COND_WAIT_TURNS_BEFORE_MARIO_ATTACKS:
        case ACT_RECORD_COND_WAIT_TURNS_BEFORE_PARTNER_ATTACKS:
        case ACT_RECORD_COND_WAIT_TURNS_BEFORE_PARTY_ATTACKS:
            if (rec->ruleType == ACT_RECORD_COND_WAIT_TURNS_BEFORE_PARTY_ATTACKS) {
                v = ar->marioJumpMoves + ar->marioHammerMoves + ar->marioSpecialAttacks + ar->marioAttackItems + ar->partnerAttackMoves + ar->partnerAttackItems;
            } else if (rec->ruleType == ACT_RECORD_COND_WAIT_TURNS_BEFORE_MARIO_ATTACKS) {
                v = ar->marioJumpMoves + ar->marioHammerMoves + ar->marioSpecialAttacks + ar->marioAttackItems;
            } else {
                v = ar->partnerAttackMoves + ar->partnerAttackItems;
            }
            _check_turn_count_0_turn(v);
            break;
    }
}

void BtlActRec_JudgeRuleKeep(void) {
    s32 v;
    BattleWork* wp = _battleWorkPointer;
    BattleActRecord* ar;
    FieldBattleInfo* rec;
    BattleUnit* mario;
    rec = wp->fbatInfo;
    ar = &wp->actRecord;
    mario = BattleGetMarioPtr(wp);
    BattleGetPartyPtr(wp);
    switch (rec->ruleType) {
        case ACT_RECORD_COND_NONE:
            rec->ruleKeepResult = 6;
            break;
        case ACT_RECORD_COND_JUMP_LESS:
            rec->ruleKeepResult = _check_no_use(ar->marioJumpMoves);
            break;
        case ACT_RECORD_COND_JUMP_MORE:
            rec->ruleKeepResult = _check_use(ar->marioJumpMoves);
            break;
        case ACT_RECORD_COND_HAMMER_LESS:
            rec->ruleKeepResult = _check_no_use(ar->marioHammerMoves);
            break;
        case ACT_RECORD_COND_HAMMER_MORE:
            rec->ruleKeepResult = _check_use(ar->marioHammerMoves);
            break;
        case ACT_RECORD_COND_USE_SPECIAL_MOVES_LESS:
            rec->ruleKeepResult = _check_no_use(ar->marioSpecialAttacks + ar->marioSpecialSupports);
            break;
        case ACT_RECORD_COND_USE_SPECIAL_MOVES_MORE:
            rec->ruleKeepResult = _check_use(ar->marioSpecialAttacks + ar->marioSpecialSupports);
            break;
        case ACT_RECORD_COND_MARIO_TAKE_LESS_DAMAGE:
            rec->ruleKeepResult = _check_no_use(ar->marioDamageTaken);
            break;
        case ACT_RECORD_COND_MARIO_TAKE_MORE_DAMAGE:
            rec->ruleKeepResult = _check_use(ar->marioDamageTaken);
            break;
        case ACT_RECORD_COND_PARTNERS_TAKE_LESS_DAMAGE:
            rec->ruleKeepResult = _check_no_use(ar->partnerDamageTaken);
            break;
        case ACT_RECORD_COND_PARTNERS_TAKE_MORE_DAMAGE:
            rec->ruleKeepResult = _check_use(ar->partnerDamageTaken);
            break;
        case ACT_RECORD_COND_PARTY_TAKE_LESS_DAMAGE:
            rec->ruleKeepResult = _check_no_use(ar->marioDamageTaken + ar->partnerDamageTaken);
            break;
        case ACT_RECORD_COND_PARTY_TAKE_MORE_DAMAGE:
            rec->ruleKeepResult = _check_use(ar->marioDamageTaken + ar->partnerDamageTaken);
            break;
        case ACT_RECORD_COND_MARIO_TAKE_FEWER_HITS:
            rec->ruleKeepResult = _check_no_use(ar->marioHitsTaken);
            break;
        case ACT_RECORD_COND_MARIO_TAKE_MORE_HITS:
            rec->ruleKeepResult = _check_use(ar->marioHitsTaken);
            break;
        case ACT_RECORD_COND_PARTNERS_TAKE_FEWER_HITS:
            rec->ruleKeepResult = _check_no_use(ar->partnerHitsTaken);
            break;
        case ACT_RECORD_COND_PARTNERS_TAKE_MORE_HITS:
            rec->ruleKeepResult = _check_use(ar->partnerHitsTaken);
            break;
        case ACT_RECORD_COND_PARTY_TAKE_FEWER_HITS:
            rec->ruleKeepResult = _check_no_use(ar->marioHitsTaken + ar->partnerHitsTaken);
            break;
        case ACT_RECORD_COND_PARTY_TAKE_MORE_HITS:
            rec->ruleKeepResult = _check_use(ar->marioHitsTaken + ar->partnerHitsTaken);
            break;
        case ACT_RECORD_COND_MARIO_WIN_MORE_HP:
            if (mario != NULL) {
                rec->ruleKeepResult = _check_use(mario->currentHp);
            } else {
                rec->ruleKeepResult = 1;
            }
            break;
        case ACT_RECORD_COND_MARIO_WIN_LESS_HP:
            if (mario != NULL) {
                rec->ruleKeepResult = _check_no_use(mario->currentHp);
            } else {
                rec->ruleKeepResult = 1;
            }
            break;
        case ACT_RECORD_COND_POWER_BOUNCE_COMBO:
            rec->ruleKeepResult = _check_use(ar->powerBounceCombo);
            break;
        case ACT_RECORD_COND_MARIO_USE_FEWER_ITEMS:
            rec->ruleKeepResult = _check_no_use(ar->marioAttackItems + ar->marioSupportItems);
            break;
        case ACT_RECORD_COND_MARIO_USE_MORE_ITEMS:
            rec->ruleKeepResult = _check_use(ar->marioAttackItems + ar->marioSupportItems);
            break;
        case ACT_RECORD_COND_PARTNERS_USE_FEWER_ITEMS:
            rec->ruleKeepResult = _check_no_use(ar->partnerAttackItems + ar->partnerSupportItems);
            break;
        case ACT_RECORD_COND_PARTNERS_USE_MORE_ITEMS:
            rec->ruleKeepResult = _check_use(ar->partnerAttackItems + ar->partnerSupportItems);
            break;
        case ACT_RECORD_COND_PARTY_USE_FEWER_ITEMS:
            rec->ruleKeepResult = _check_no_use(ar->marioAttackItems + ar->marioSupportItems + ar->partnerAttackItems + ar->partnerSupportItems);
            break;
        case ACT_RECORD_COND_PARTY_USE_MORE_ITEMS:
            rec->ruleKeepResult = _check_use(ar->marioAttackItems + ar->marioSupportItems + ar->partnerAttackItems + ar->partnerSupportItems);
            break;
        case ACT_RECORD_COND_MARIO_SWAP_PARTNERS_LESS:
            rec->ruleKeepResult = _check_no_use(ar->marioPartyChanges);
            break;
        case ACT_RECORD_COND_MARIO_SWAP_PARTNERS_MORE:
            rec->ruleKeepResult = _check_use(ar->marioPartyChanges);
            break;
        case ACT_RECORD_COND_PARTNERS_SWAP_PARTNERS_LESS:
            rec->ruleKeepResult = _check_no_use(ar->partnerPartyChanges);
            break;
        case ACT_RECORD_COND_PARTNERS_SWAP_PARTNERS_MORE:
            rec->ruleKeepResult = _check_use(ar->partnerPartyChanges);
            break;
        case ACT_RECORD_COND_PARTY_SWAP_PARTNERS_LESS:
            rec->ruleKeepResult = _check_no_use(ar->marioPartyChanges + ar->partnerPartyChanges);
            break;
        case ACT_RECORD_COND_PARTY_SWAP_PARTNERS_MORE:
            rec->ruleKeepResult = _check_use(ar->marioPartyChanges + ar->partnerPartyChanges);
            break;
        case ACT_RECORD_COND_MARIO_ATTACK_AUDIENCE_LESS:
            rec->ruleKeepResult = _check_no_use(ar->marioAudienceAttacks);
            break;
        case ACT_RECORD_COND_MARIO_ATTACK_AUDIENCE_MORE:
            rec->ruleKeepResult = _check_use(ar->marioAudienceAttacks);
            break;
        case ACT_RECORD_COND_PARTNERS_ATTACK_AUDIENCE_LESS:
            rec->ruleKeepResult = _check_no_use(ar->partnerAudienceAttacks);
            break;
        case ACT_RECORD_COND_PARTNERS_ATTACK_AUDIENCE_MORE:
            rec->ruleKeepResult = _check_use(ar->partnerAudienceAttacks);
            break;
        case ACT_RECORD_COND_MARIO_APPEAL_LESS:
            rec->ruleKeepResult = _check_no_use(ar->marioAppeals);
            break;
        case ACT_RECORD_COND_MARIO_APPEAL_MORE:
            rec->ruleKeepResult = _check_use(ar->marioAppeals);
            break;
        case ACT_RECORD_COND_PARTNERS_APPEAL_LESS:
            rec->ruleKeepResult = _check_no_use(ar->partnerAppeals);
            break;
        case ACT_RECORD_COND_PARTNERS_APPEAL_MORE:
            rec->ruleKeepResult = _check_use(ar->partnerAppeals);
            break;
        case ACT_RECORD_COND_PARTY_APPEAL_LESS:
            rec->ruleKeepResult = _check_no_use(ar->marioAppeals + ar->partnerAppeals);
            break;
        case ACT_RECORD_COND_PARTY_APPEAL_MORE:
            rec->ruleKeepResult = _check_use(ar->marioAppeals + ar->partnerAppeals);
            break;
        case ACT_RECORD_COND_MARIO_SPEND_LESS_FP:
            rec->ruleKeepResult = _check_no_use(ar->marioFpSpent);
            break;
        case ACT_RECORD_COND_MARIO_SPEND_MORE_FP:
            rec->ruleKeepResult = _check_use(ar->marioFpSpent);
            break;
        case ACT_RECORD_COND_PARTNERS_SPEND_LESS_FP:
            rec->ruleKeepResult = _check_no_use(ar->partnerFpSpent);
            break;
        case ACT_RECORD_COND_PARTNERS_SPEND_MORE_FP:
            rec->ruleKeepResult = _check_use(ar->partnerFpSpent);
            break;
        case ACT_RECORD_COND_PARTY_SPEND_LESS_FP_0x30:
            rec->ruleKeepResult = _check_no_use(ar->marioFpSpent + ar->partnerFpSpent);
            break;
        case ACT_RECORD_COND_PARTY_SPEND_MORE_FP_0x31:
            rec->ruleKeepResult = _check_use(ar->marioFpSpent + ar->partnerFpSpent);
            break;
        case ACT_RECORD_COND_MARIO_USE_MOVES_LESS:
            rec->ruleKeepResult = _check_no_use(ar->marioFpMoves);
            break;
        case ACT_RECORD_COND_MARIO_USE_MOVES_MORE:
            rec->ruleKeepResult = _check_use(ar->marioFpMoves);
            break;
        case ACT_RECORD_COND_PARTNERS_USE_MOVES_LESS:
            rec->ruleKeepResult = _check_no_use(ar->partnerFpMoves);
            break;
        case ACT_RECORD_COND_PARTNERS_USE_MOVES_MORE:
            rec->ruleKeepResult = _check_use(ar->partnerFpMoves);
            break;
        case ACT_RECORD_COND_PARTY_SPEND_LESS_FP_0x36:
            rec->ruleKeepResult = _check_no_use(ar->marioFpSpent + ar->partnerFpSpent);
            break;
        case ACT_RECORD_COND_PARTY_SPEND_MORE_FP_0x37:
            rec->ruleKeepResult = _check_use(ar->marioFpSpent + ar->partnerFpSpent);
            break;
        case ACT_RECORD_COND_PARTY_USE_MOVES_LESS:
            rec->ruleKeepResult = _check_no_use(ar->marioFpMoves + ar->partnerFpMoves);
            break;
        case ACT_RECORD_COND_PARTY_USE_MOVES_MORE:
            rec->ruleKeepResult = _check_use(ar->marioFpMoves + ar->partnerFpMoves);
            break;
        case ACT_RECORD_COND_WIN_IN_MORE_TURNS:
            if (ar->turnCount > rec->ruleParam) {
                rec->ruleKeepResult = 6;
            } else if (ar->turnCount > rec->ruleParam2) {
                rec->ruleKeepResult = 2;
            } else {
                rec->ruleKeepResult = 1;
            }
            break;
        case ACT_RECORD_COND_WIN_IN_FEWER_TURNS:
            if (ar->turnCount <= rec->ruleParam) {
                rec->ruleKeepResult = 6;
            } else if (ar->turnCount <= rec->ruleParam2) {
                rec->ruleKeepResult = 2;
            } else {
                rec->ruleKeepResult = 1;
            }
            break;
        case ACT_RECORD_COND_WAIT_TURNS_BEFORE_MARIO_ACTIONS:
        case ACT_RECORD_COND_WAIT_TURNS_BEFORE_PARTNER_ACTIONS:
        case ACT_RECORD_COND_WAIT_TURNS_BEFORE_PARTY_ACTIONS:
            if (rec->ruleType == ACT_RECORD_COND_WAIT_TURNS_BEFORE_PARTY_ACTIONS) {
                v = ar->marioJumpMoves + ar->marioHammerMoves + ar->marioSpecialAttacks + ar->marioSpecialSupports + ar->marioAttackItems + ar->marioSupportItems + ar->marioPartyChanges + ar->marioCharges + ar->marioSuperCharges + ar->marioEscapes + ar->partnerAttackMoves + ar->partnerSupportMoves + ar->partnerAttackItems + ar->partnerSupportItems + ar->partnerPartyChanges + ar->partnerCharges + ar->partnerSuperCharges + ar->partnerEscapes;
            } else if (rec->ruleType == ACT_RECORD_COND_WAIT_TURNS_BEFORE_MARIO_ACTIONS) {
                v = ar->marioJumpMoves + ar->marioHammerMoves + ar->marioSpecialAttacks + ar->marioSpecialSupports + ar->marioAttackItems + ar->marioSupportItems + ar->marioPartyChanges + ar->marioCharges + ar->marioSuperCharges + ar->marioEscapes;
            } else {
                v = ar->partnerAttackMoves + ar->partnerSupportMoves + ar->partnerAttackItems + ar->partnerSupportItems + ar->partnerPartyChanges + ar->partnerCharges + ar->partnerSuperCharges + ar->partnerEscapes;
            }
            _check_turn_count_0_end(v);
            break;
        case ACT_RECORD_COND_WAIT_TURNS_BEFORE_MARIO_ATTACKS:
        case ACT_RECORD_COND_WAIT_TURNS_BEFORE_PARTNER_ATTACKS:
        case ACT_RECORD_COND_WAIT_TURNS_BEFORE_PARTY_ATTACKS:
            if (rec->ruleType == ACT_RECORD_COND_WAIT_TURNS_BEFORE_PARTY_ATTACKS) {
                v = ar->marioJumpMoves + ar->marioHammerMoves + ar->marioSpecialAttacks + ar->marioAttackItems + ar->partnerAttackMoves + ar->partnerAttackItems;
            } else if (rec->ruleType == ACT_RECORD_COND_WAIT_TURNS_BEFORE_MARIO_ATTACKS) {
                v = ar->marioJumpMoves + ar->marioHammerMoves + ar->marioSpecialAttacks + ar->marioAttackItems;
            } else {
                v = ar->partnerAttackMoves + ar->partnerAttackItems;
            }
            _check_turn_count_0_end(v);
            break;
        case ACT_RECORD_COND_MARIO_ONLY_JUMP_OR_DEFEND:
            if (ar->marioHammerMoves + ar->marioSpecialAttacks + ar->marioSpecialSupports + ar->marioAttackItems + ar->marioSupportItems + ar->marioPartyChanges + ar->marioCharges + ar->marioSuperCharges + ar->marioAppeals + ar->marioEscapes == 0) {
                rec->ruleKeepResult = 6;
            } else {
                rec->ruleKeepResult = 1;
            }
            break;
        case ACT_RECORD_COND_MARIO_ONLY_HAMMER_OR_DEFEND:
            if (ar->marioJumpMoves + ar->marioSpecialAttacks + ar->marioSpecialSupports + ar->marioAttackItems + ar->marioSupportItems + ar->marioPartyChanges + ar->marioCharges + ar->marioSuperCharges + ar->marioAppeals + ar->marioEscapes == 0) {
                rec->ruleKeepResult = 6;
            } else {
                rec->ruleKeepResult = 1;
            }
            break;
    }
}

static s32 _check_use(s32 n) {
    FieldBattleInfo* rec = _battleWorkPointer->fbatInfo;
    if (n >= rec->ruleParam) {
        return 6;
    }
    return (n >= rec->ruleParam2) + 1;
}

static s32 _check_no_use(s32 n) {
    FieldBattleInfo* rec = _battleWorkPointer->fbatInfo;
    if (n >= rec->ruleParam2) {
        return 1;
    }
    return n >= rec->ruleParam ? 2 : 6;
}

static s32 _check_turn_count_0_turn(s32 n) {
    BattleWork* wp = _battleWorkPointer;
    FieldBattleInfo* rec = wp->fbatInfo;
    BattleActRecord* ar = &wp->actRecord;
    if (ar->turnCount <= rec->ruleParam2 || rec->ruleParam2 == 0xff) {
        if (n == 0) {
            rec->ruleKeepResult = 2;
        } else {
            rec->ruleKeepResult = 1;
        }
    }
    if (ar->turnCount <= rec->ruleParam || rec->ruleParam == 0xff) {
        if (n == 0) {
            rec->ruleKeepResult = 6;
        } else if (!(rec->ruleKeepResult & 2)) {
            rec->ruleKeepResult = 1;
        }
    }
    return rec->ruleKeepResult;
}

static s32 _check_turn_count_0_end(s32 n) {
    BattleWork* wp = _battleWorkPointer;
    FieldBattleInfo* rec = wp->fbatInfo;
    BattleActRecord* ar = &wp->actRecord;
    if (ar->turnCount <= rec->ruleParam2 || rec->ruleParam2 == 0xff) {
        if (n == 0) {
            rec->ruleKeepResult = 2;
        } else {
            rec->ruleKeepResult = 1;
        }
    }
    if (ar->turnCount <= rec->ruleParam || rec->ruleParam == 0xff) {
        if (n == 0) {
            rec->ruleKeepResult = 6;
        } else if (!(rec->ruleKeepResult & 2)) {
            rec->ruleKeepResult = 1;
        }
    }
    return rec->ruleKeepResult;
}
