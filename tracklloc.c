#include "tracklloc_functions.h"

#ifndef TRACKLLOC_H
#define TRACKLLOC_H
struct malloc_tracking_t {
    void *ptr;
    char *file_name;
    size_t line_number;
};
static const size_t S = sizeof(struct malloc_tracking_t);

static struct malloc_tracking_t *malloc_tracking = NULL;
static size_t malloc_tracking_length = 0;

void *_TRACK_malloc(size_t size, char *file_name, size_t line_number) {
    malloc_tracking = realloc(malloc_tracking, S * (malloc_tracking_length + 1));
    void *result = malloc(size);

    malloc_tracking[malloc_tracking_length].ptr = result;
    malloc_tracking[malloc_tracking_length].file_name = strdup(file_name);
    malloc_tracking[malloc_tracking_length++].line_number = line_number;
    return result;
}

void _TRACK_free(void *ptr, char *file_name, size_t line_number) {
    // find the index for it
    for (size_t i = 0; i < malloc_tracking_length; ++i) {
        if (malloc_tracking[i].ptr == ptr) {
            free(ptr);
            // remove this from the malloc_tracking
            free(malloc_tracking[i].file_name);
            --malloc_tracking_length;

            for (size_t j = i; j < malloc_tracking_length; ++j) {
                malloc_tracking[j] = malloc_tracking[j + 1];
            }

            malloc_tracking = realloc(malloc_tracking, S * malloc_tracking_length);
            return;
        }
    }
    // double freed!
    fprintf(stderr, "\033[91mfreeing memory that wasn't malloc'd/double freeing: %p in %s:%zu\033[0m\n", ptr, file_name, line_number);
    free(ptr);
}

void TRACK_log_unfreed() {
    // print unfreed memory
    for (size_t i = 0; i < malloc_tracking_length; ++i) {
        fprintf(stderr, "\033[91munfreed memory: %p in %s:%zu\033[0m\n", malloc_tracking[i].ptr, malloc_tracking[i].file_name, malloc_tracking[i].line_number);
    }
}

#endif
