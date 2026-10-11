// include: driver/dispdrv.h
// decl: void yuunpc_disp(CameraId camera, void* param);
// proto: void ext_yuunpc_dispent(void);
void ext_yuunpc_dispent(void) {
    dispEntry(4, 0.0f, 1, yuunpc_disp, NULL);
}
