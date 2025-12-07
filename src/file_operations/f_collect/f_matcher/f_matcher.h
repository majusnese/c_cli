#ifndef F_MATCHER_H
#define F_MATCHER_H
#include "general_types.h"

boolean is_file_match(const char *filename);
std_return_type register_regex_matcher(const char *regex_pattern);

#endif