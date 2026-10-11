// include: mario/mario.h
// proto: USER_FUNC(mariowalk_wait);
USER_FUNC(mariowalk_wait) {
    return !(marioGetPtr()->flags & 0x20);
}
