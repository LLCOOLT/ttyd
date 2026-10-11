typedef int BOOL;

BOOL GetTRKConnected(void);
void SetTRKConnected(BOOL connected);
void OSReport(const char* msg);

BOOL usr_puts_serial(const char* msg) {
    BOOL chars_left = 0;
    char c;
    char buf[2];

    while (!chars_left && (c = *msg++) != '\0') {
        BOOL connect_ = GetTRKConnected();

        buf[0] = c;
        buf[1] = '\0';

        SetTRKConnected(0);
        OSReport(buf);
        SetTRKConnected(connect_);

        chars_left = 0;
    }

    return chars_left;
}

void usr_put_initialize(void) {}
