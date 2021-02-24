#include "tracklloc.h"

int main() {
    int *x = malloc(sizeof(int));
    printf("x is %i at %p\n", *x, x);
    free(x);
    // can't detect unfreed memory in files that don't include tracklloc
    char *s = strdup("hello world");
    // if we'd free s it says it's double freeing
    TRACK_log_unfreed();
} 
