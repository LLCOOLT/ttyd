// decl: extern u8 kurokaron_move_index;
// decl: extern u8 kurokaron_move_flag;
// proto: void _kurokaron_next_move_index(void);
void _kurokaron_next_move_index(void) {
    if (kurokaron_move_flag & 1) {
        if (kurokaron_move_index == 0) {
            kurokaron_move_index = 5;
        } else {
            kurokaron_move_index--;
        }
    } else {
        kurokaron_move_index++;
        kurokaron_move_index %= 6;
    }
}
