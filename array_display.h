#ifndef ARRAY_DISPLAY_H
#define ARRAY_DISPLAY_H

#include "types.h"

typedef enum{
    SKIP_OK, DONT_SKIP_OK
}Skip;

void print_array_verbose(Entries *entries, ArrayFilter filter, Skip skip_ok);
void print_array_concise(Entries *entries, ArrayFilter filter, Skip skip_ok);

#endif

