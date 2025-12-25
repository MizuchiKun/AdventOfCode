#include <string.h>
#include "malloc_custom.h"
#include "pcre2posix_custom.h"

char *MatchToStr(regmatch_t *match, char *sourceString)
{
    const char NUL = '\0';
    const size_t NUL_SIZE = sizeof(NUL);
    size_t size = (size_t)(match->rm_eo - match->rm_so);
    char *substring = SafeMalloc(size + NUL_SIZE);

    memcpy(substring, sourceString + match->rm_so, size);
    substring[size] = NUL;

    return substring;
}