// decl: void npcSetTalkPose(const char* name);
// decl: void npcSetStayPose(const char* name);
// proto: void b_peach_msgcb(s32 type, void* param);
void b_peach_msgcb(s32 type, void* param) {
    switch (type) {
        case 0:
        case 3:
            npcSetTalkPose("\211e\202\314\217\227\211\244");
            break;
        case 1:
        case 2:
            npcSetStayPose("\211e\202\314\217\227\211\244");
            break;
    }
}
