#include "f_m_extension.h"
#include "f_matcher.h"
#include "logger.h"
#include <stdlib.h>
#include <string.h>

typedef struct extension_contexts {
  char **extensions;
  size_t count;
  size_t capacity;
} extension_contexts;

static extension_contexts global_extension_contexts = {NULL, 0, 0};

static char *get_file_extension(const char *filename) {
  if (filename == NULL)
    return NULL;
  const char *dot = strrchr(filename, '.');
  if (!dot || dot == filename) {
    return NULL;
  }
  return (char *)(dot + 1);
}

static std_return_type resize_extension_contexts_if_needed(void) {
  if (global_extension_contexts.count >= global_extension_contexts.capacity) {
    size_t new_capacity = (global_extension_contexts.capacity == 0)
                              ? 4
                              : global_extension_contexts.capacity * 2;

    char **new_array = realloc(global_extension_contexts.extensions,
                               new_capacity * sizeof(char *));
    if (new_array == NULL) {
      LOG_ERROR("Failed to allocate memory for extension contexts");
      return STD_RETURN_ERROR;
    }
    global_extension_contexts.extensions = new_array;
    global_extension_contexts.capacity = new_capacity;
  }
  return STD_RETURN_OK;
}

std_return_type register_extension_matcher_internal(const char *extension) {

  /* normalize: skip a leading '.' if the caller passed it */
  const char *src = extension[0] == '.' ? extension + 1 : extension;

  if (resize_extension_contexts_if_needed() != STD_RETURN_OK) {
    return STD_RETURN_ERROR;
  }

  size_t len = strlen(src);
  //   will be freed later in free_extension_matchers
  char *dup = malloc(len + 1);
  if (!dup) {
    LOG_ERROR("Out of memory while registering extension: %s", src);
    return STD_RETURN_ERROR;
  }
  memcpy(dup, src, len + 1);

  global_extension_contexts.extensions[global_extension_contexts.count] = dup;
  global_extension_contexts.count++;

  LOG_INFO("Registered extension matcher: %s", dup);
  return STD_RETURN_OK;
}

boolean check_extension_match(const char *filename) {
  char *ext = get_file_extension(filename);
  if (!ext)
    return FALSE;

  for (size_t i = 0; i < global_extension_contexts.count; ++i) {
    if (strcmp(global_extension_contexts.extensions[i], ext) == 0) {
      return TRUE;
    }
  }
  return FALSE;
}

std_return_type free_extension_matchers(void) {
  for (size_t i = 0; i < global_extension_contexts.count; ++i) {
    free(global_extension_contexts.extensions[i]);
  }
  free(global_extension_contexts.extensions);
  global_extension_contexts.extensions = NULL;
  global_extension_contexts.count = 0;
  global_extension_contexts.capacity = 0;
  return STD_RETURN_OK;
}
