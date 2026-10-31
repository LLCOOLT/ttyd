#include "ansi_files.h"

/**
 * Empties the stream buffer: resets the buffer pointer to the start
 * and sets the usable length to the buffer size less the file position's offset within the buffer alignment,
 * recording the position the buffer starts at.
 */
void __prep_buffer(FILE* file) {
    file->buffer_ptr = file->buffer;
    file->buffer_len = file->buffer_size;
    file->buffer_len -= file->position & file->buffer_alignment;
    file->buffer_pos = file->position;
}

/**
 * Writes the bytes between buffer and buffer_ptr through the stream's write_proc,
 * advances the file position by what was written (reported in *bytes_flushed if given),
 * then re-empties the buffer; returns the handler's error code if the write failed.
 */
int __flush_buffer(FILE* file, size_t* bytes_flushed) {
    size_t buffer_len;
    int ioresult;

    buffer_len = file->buffer_ptr - file->buffer;

    if (buffer_len) {
        file->buffer_len = buffer_len;

        ioresult = (*file->write_proc)(file->handle, file->buffer, &file->buffer_len, file->ref_con);

        if (bytes_flushed)
            *bytes_flushed = file->buffer_len;

        if (ioresult)
            return (ioresult);

        file->position += file->buffer_len;
    }

    __prep_buffer(file);

    return (__no_io_error);
}
