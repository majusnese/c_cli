#include "f_matcher.h"
#include "f_m_regex.h"
#include "logger.h"
#include <stdlib.h>
int total_number_matchers = 0;

boolean is_file_match(const char *filename) {
  boolean match = check_regex_match(filename);
  return match;
}

std_return_type register_regex_matcher(const char *regex_pattern) {
  if (regex_pattern == NULL) {
    LOG_ERROR("Regex pattern is NULL");
    return STD_RETURN_ERROR;
  }
  if (register_regex_matcher_internal(regex_pattern) != STD_RETURN_OK) {
    LOG_ERROR("Failed to register regex matcher for pattern: %s",
              regex_pattern);
    return STD_RETURN_ERROR;
  } else {
    LOG_INFO("Registered regex matcher for pattern: %s", regex_pattern);
    total_number_matchers++;
  }

  return STD_RETURN_OK;
}
