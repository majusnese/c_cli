#include "f_m_regex.h"
#include "logger.h"
#include <stdlib.h>

static std_return_type resize_regex_contexts_if_needed(void) {
  if (global_regex_contexts.count >= global_regex_contexts.capacity) {
    size_t new_capacity = (global_regex_contexts.capacity == 0)
                              ? 4
                              : global_regex_contexts.capacity * 2;

    regex_t *new_regexes =
        realloc(global_regex_contexts.regexes, new_capacity * sizeof(regex_t));

    if (new_regexes == NULL) {
      LOG_ERROR("Failed to allocate memory for regex contexts");
      return STD_RETURN_ERROR;
    }
    global_regex_contexts.regexes = new_regexes;
    global_regex_contexts.capacity = new_capacity;
  }
  return STD_RETURN_OK;
}

regex_contexts global_regex_contexts = {NULL, 0, 0};

std_return_type register_regex_matcher_internal(const char *regex_pattern) {
  if (resize_regex_contexts_if_needed() != STD_RETURN_OK) {
    return STD_RETURN_ERROR;
  }

  int rc = regcomp(&global_regex_contexts.regexes[global_regex_contexts.count],
                   regex_pattern, REG_EXTENDED | REG_NOSUB);
  if (rc != 0) {
    LOG_ERROR("Failed to compile regex pattern: %s", regex_pattern);
    return STD_RETURN_ERROR;
  }
  global_regex_contexts.count++;

  return STD_RETURN_OK;
}

boolean check_regex_match(const char *filename) {
  for (size_t i = 0; i < global_regex_contexts.count; i++) {
    int rc = regexec(&global_regex_contexts.regexes[i], filename, 0, NULL, 0);
    if (rc == 0) {
      return TRUE;
    }
  }
  return FALSE;
}

std_return_type free_regex_matchers() {
  for (size_t i = 0; i < global_regex_contexts.count; i++) {
    regfree(&global_regex_contexts.regexes[i]);
  }
  free(global_regex_contexts.regexes);
  global_regex_contexts.regexes = NULL;
  global_regex_contexts.count = 0;
  global_regex_contexts.capacity = 0;
  return STD_RETURN_OK;
}
