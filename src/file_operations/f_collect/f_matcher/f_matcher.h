#ifndef F_MATCHER_H
#define F_MATCHER_H
#include "general_types.h"

extern int total_number_matchers;

boolean is_file_match(const char *filename);
std_return_type register_regex_matcher(const char *regex_pattern);

#endif