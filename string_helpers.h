/** 
 * Copied from "The C Programming Language" section 6.6 (slightly edited
 * function names / struct names)
 */
#include <stdlib.h>
#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H
extern char *substring(char *out, char const *in, size_t len);
#endif