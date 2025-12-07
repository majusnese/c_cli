#ifndef F_M_EXTENSION_H
#define F_M_EXTENSION_H
#include "general_types.h"

std_return_type register_extension_matcher_internal(const char *extension);

boolean check_extension_match(const char *filename);

std_return_type free_extension_matchers(void);

#endif
