#include "ansi_files.h"

int __flush_all(void);
long ftell(FILE* file);

enum { __read = 1, __write = 2 };

#define set_error(file)          \
    do {                         \
        (file)->state.error = 1; \
        (file)->buffer_len = 0;  \
    } while (0)

/**
 * Standard fflush(): NULL flushes all streams; read-only streams return 0;
 * a stream in write state has its buffer flushed through __flush_buffer
 * and its position reset (disk files use ftell); returns EOF on error or a closed stream.
 */
int fflush(FILE* file) {
    fpos_t position;

    if (!file)
        return (__flush_all());

    if (file->state.error || file->mode.file_kind == __closed_file)
        return (EOF);

    if (file->mode.io_mode == __read)
        return (0);

    if (file->state.io_state >= __rereading)
        file->state.io_state = __reading;

    if (file->state.io_state == __reading)
        file->buffer_len = 0;

    if (file->state.io_state != __writing) {
        file->state.io_state = __neutral;
        return (0);
    }

    if (file->mode.file_kind != __disk_file)
        position = 0;
    else
        position = ftell(file);

    if (__flush_buffer(file, NULL)) {
        set_error(file);
        return (EOF);
    }

    file->state.io_state = __neutral;
    file->position = position;
    file->buffer_len = 0;

    return (0);
}

/**
 * Standard fclose(): flushes the stream, calls its close_proc, marks it closed,
 * and frees the buffer if the stream owns it (free_buffer); returns EOF if the flush or close failed.
 * The list entry itself is released later by __close_all.
 */
int fclose(FILE* file) {
    int flush_result, close_result;

    if (file == NULL)
        return (EOF);

    if (file->mode.file_kind == __closed_file)
        return (0);

    flush_result = fflush(file);

    close_result = (*file->close_proc)(file->handle);

    file->mode.file_kind = __closed_file;
    file->handle = NULL;

    if (file->state.free_buffer)
        free(file->buffer);

    return ((flush_result || close_result) ? EOF : 0);
}
