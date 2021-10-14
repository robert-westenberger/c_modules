#include <string.h>
#include "string_helpers.h"

char *substring(char *out, char const *in, size_t len) { 
    memcpy(out, in, len);
    out[len] = '\0';
    return out;
}