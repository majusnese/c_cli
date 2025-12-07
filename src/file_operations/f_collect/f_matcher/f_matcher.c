#include "f_matcher.h"
#include "f_m_extension.h"
#include "f_m_regex.h"
#include "logger.h"
#include <stdlib.h>

int total_number_matchers = 0;

boolean is_file_match(const char *filename) {
  /* A file matches if any registered matcher matches it.  Check regex
     matchers first, then extension matchers. */
  if (check_regex_match(filename))
    return TRUE;
  if (check_extension_match(filename))
    return TRUE;
  return FALSE;
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

std_return_type register_extension_matcher(const char *extension) {
  if (extension == NULL) {
    LOG_ERROR("Extension is NULL");
    return STD_RETURN_ERROR;
  }
  if (register_extension_matcher_internal(extension) != STD_RETURN_OK) {
    LOG_ERROR("Failed to register extension for pattern: %s", extension);
    return STD_RETURN_ERROR;
  } else {
    LOG_INFO("Registered extension matcher for pattern: %s", extension);
    total_number_matchers++;
  }

  return STD_RETURN_OK;
}