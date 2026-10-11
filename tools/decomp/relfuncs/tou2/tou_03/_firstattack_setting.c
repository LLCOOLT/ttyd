// include: driver/npcdrv.h
// decl: void fbatSetAttackAnnounce(s32 type);
// decl: void fbatSetAttackAnnounceEnable(void);
// proto: USER_FUNC(_firstattack_setting);
USER_FUNC(_firstattack_setting) {
    FieldBattleData* fbat = fbatGetPointer();

    *(s32*)&fbat->field_C[4] = 0x10000000;
    *(s32*)&fbat->field_C[8] = 0x10;
    *(u32*)&fbat->field_C[0x10] &= ~1;
    fbatSetAttackAnnounce(0x10000000);
    fbatSetAttackAnnounceEnable();
    return EVT_RETURN_DONE;
}
