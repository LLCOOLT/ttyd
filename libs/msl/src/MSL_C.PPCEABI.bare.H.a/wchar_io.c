#include "ansi_files.h"

/**
 * Standard fwide(): returns 0 for a null or closed stream;
 * an unoriented stream becomes wide- or byte-oriented according to the sign of the argument;
 * otherwise returns 1 if wide-oriented and -1 if byte-oriented.
 */
int fwide(FILE* stream, int orientation) {
    if (stream == NULL || stream->mode.file_kind == __closed_file)
        return 0;

    switch (stream->mode.file_orientation) {
        case __unoriented:
            if (orientation > 0)
                stream->mode.file_orientation = __wide_oriented;
            else if (orientation < 0)
                stream->mode.file_orientation = __char_oriented;
            return orientation;
        case __wide_oriented:
            return 1;
        case __char_oriented:
            return -1;
    }
}
