#include "tracklloc_functions.h"
#define malloc(size) _TRACK_malloc(size, __FILE__, __LINE__)
#define free(ptr)    _TRACK_free(ptr, __FILE__, __LINE__)
