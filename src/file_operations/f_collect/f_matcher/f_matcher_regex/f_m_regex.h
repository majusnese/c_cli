#ifndef M_REGEX_H
#define M_REGEX_H
#include "general_types.h"
#include <regex.h>
#include <stddef.h>

typedef struct regex_contexts {
  regex_t *regexes;
  size_t count;
  size_t capacity;
} regex_contexts;

std_return_type register_regex_matcher_internal(const char *regex_pattern);

boolean check_regex_match(const char *filename);

std_return_type free_regex_matchers();

#endif