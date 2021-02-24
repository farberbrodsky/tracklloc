#define TRACKLLOC
#include "tracklloc.h"

int main() {
    int *x = malloc(sizeof(int));
    printf("x is %i at %p\n", *x, x);
    TRACK_log_unfreed();
} 
