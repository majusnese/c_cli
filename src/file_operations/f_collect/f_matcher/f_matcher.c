#include "f_matcher.h"
#include "f_m_regex.h"
#include "logger.h"
#include <stdlib.h>

boolean is_file_match(const char *filename) {
  boolean match = check_regex_match(filename);
  return match;
}

std_return_type register_regex_matcher(const char *regex_pattern) {
  return register_regex_matcher_internal(regex_pattern);
}
