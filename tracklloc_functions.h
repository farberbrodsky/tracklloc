#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *_TRACK_malloc(size_t size, char *file_name, size_t line_number);
void _TRACK_free(void *ptr, char *file_name, size_t line_number);
void TRACK_log_unfreed();
