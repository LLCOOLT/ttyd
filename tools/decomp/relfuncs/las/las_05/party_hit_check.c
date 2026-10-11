// include: party.h
// include: mario/mario_party.h
// include: party/party_cloud.h
// decl: s32 nokonokoGetStatus(void);
// decl: f32 cloudGetBreathDist(void);
// proto: s32 party_hit_check(f32* dir, f32 x, f32 z);
s32 party_hit_check(f32* dir, f32 x, f32 z) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    s32 hit = 0;
    s32 active = 0;
    f32 dx;
    f32 dz;

    if (party == NULL) {
        return 0;
    }
    dx = __fabsf(x - party->position.x);
    dz = __fabsf(z - party->position.z);
    switch (party->currentMemberId) {
        case 2:
            switch (nokonokoGetStatus()) {
                case 2:
                case 3:
                case 4:
                case 5:
                    active = 1;
                    break;
            }
            if (active && dx < party->width && dz < party->width) {
                hit = 1;
                if (x < party->position.x) {
                    *dir = 1.0f;
                } else {
                    *dir = -1.0f;
                }
            }
            break;
        case 3:
            if (partyGetPtr(0)->useMotionId == 0x46 && dx < 80.0f && dz < 80.0f) {
                hit = 1;
                if (x < party->position.x) {
                    *dir = 1.0f;
                } else {
                    *dir = -1.0f;
                }
            }
            break;
        case 5:
            if ((party->flags & 0x100) && dx < cloudGetBreathDist() && dz < 30.0f) {
                if (cloudGetBreathDir() < 180.0f) {
                    if (x > party->position.x) {
                        hit = 1;
                        *dir = -1.0f;
                    }
                } else {
                    if (x < party->position.x) {
                        hit = 1;
                        *dir = 1.0f;
                    }
                }
            }
            break;
    }
    return hit;
}
