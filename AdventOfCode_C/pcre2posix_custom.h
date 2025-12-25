#ifndef pcre2posix_custom_h
#define pcre2posix_custom_h

#define PCRE2_STATIC
#define PCRE2_CODE_UNIT_WIDTH 8

#include <pcre2posix.h>  // Essentially regex.h.

/// @brief Creates the substring of sourceString described by match.
/// @param match The match which describes the substring.
/// @param sourceString The string in which the match was found.
/// @return A pointer to the created substring.
char *MatchToStr(regmatch_t *match, char *sourceString);

#endif
