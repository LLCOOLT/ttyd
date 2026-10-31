#include <dolphin.h>
#include <dolphin/dvd.h>

#include "__dvd.h"

static void (*FatalFunc)();

/**
 * Japanese text of the fatal DVD error screen: an error has occurred, turn the power off and follow the
 * console manual.
 */
const char* Japanese =
    "\n\n\nエラーが発生しました。\n\n"
    "本体のパワーボタンを押して電源をOFFにし、\n"
    "本体の取扱説明書の指示に従ってください。";

/**
 * English text of the fatal DVD error screen: an error has occurred, turn the power off and see the GameCube
 * instruction booklet.
 */
const char* English = 
    "\n\n\nAn error has occurred.\n"
    "Turn the power off and refer to the\n"
    "Nintendo GameCube Instruction Booklet\n"
    "for further instructions.";

// Accented characters are written as hex escapes, with the string split where a hex digit follows one.
const char* const Europe[6] = {
    {
        "\n\n\nAn error has occurred.\n"
        "Turn the power off and refer to the\n"
        "Nintendo GameCube Instruction Booklet\n"
        "for further instructions."
    },
    {
        "\n\n\nEin Fehler ist aufgetreten.\n"
        "Bitte schalten Sie den Nintendo GameCube\n"
        "aus und lesen Sie die Bedienungsanleitung,\n"
        "um weitere Informationen zu erhalten."
    },
    {
        "\n\n\nUne erreur est survenue.\n"
        "Eteignez la console et r\xE9" "f" "\xE9rez-vous au\n"
        "manuel d'instructions Nintendo GameCube\n"
        "pour de plus amples informations."
    },
    {
        "\n\n\nSe ha producido un error.\n"
        "Apaga la consola y consulta el manual\n"
        "de instrucciones de Nintendo GameCube\n"
        "para obtener m\xE1" "s informaci\xF3" "n."
    },
    {
        "\n\n\nSi \xE8" " verificato un errore.\n"
        "Spegni (OFF) e controlla il manuale\n"
        "d'istruzioni del Nintendo GameCube\n"
        "per ulteriori indicazioni."
    },
    {
        "\n\n\nEr is een fout opgetreden.\n"
        "Zet de Nintendo GameCube uit en\n"
        "raadpleeg de handleiding van de\n"
        "Nintendo GameCube voor nadere\n"
        "instructies."
    },
};

/**
 * Shows the "An error has occurred. Turn the power off..." screen with OSFatal (white text on black).
 * NTSC consoles show the Japanese text if the font encoding is Shift-JIS and English otherwise;
 * other regions pick the translation from the Europe table by OSGetLanguage.
 */
static void ShowMessage(void) {
    const char* message;
    GXColor bg = {0x00, 0x00, 0x00, 0x00};
    GXColor fg = {0xFF, 0xFF, 0xFF, 0x00};

    if (VIGetTvFormat() == VI_NTSC) {
        if (OSGetFontEncode() == OS_FONT_ENCODE_SJIS) {
            message = Japanese;
        } else {
            message = English;
        }
    } else {
        message = Europe[OSGetLanguage()];
    }

    OSFatal(fg, bg, message);
}

/** Enables or disables the automatic fatal drive error screen; returns the previous setting. */
int DVDSetAutoFatalMessaging(BOOL enable) {
    BOOL enabled;
    int prev;

    enabled = OSDisableInterrupts();

    prev = FatalFunc ? 1 : 0;
    FatalFunc = enable ? ShowMessage : NULL;

    OSRestoreInterrupts(enabled);
    return prev;
}

/** Shows the fatal drive error message through the registered handler if automatic messaging is on. */
void __DVDPrintFatalMessage(void) {
    if (FatalFunc) {
        FatalFunc();
    }
}
