#include "logger.h"
#include "configuration.h"
#include "general_types.h"
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>

static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

static boolean should_log(log_level log_level,
                          verbosity_level current_verbosity) {
  if (log_level == LOG_LEVEL_ERROR) {
    return 1;
  } else if (log_level == LOG_LEVEL_WARNING) {
    return (current_verbosity >= VERBOSITY_NORMAL);
  } else if (log_level == LOG_LEVEL_INFO) {
    return (current_verbosity >= VERBOSITY_VERBOSE);
  } else if (log_level == LOG_LEVEL_DEBUG) {
    return (current_verbosity >= VERBOSITY_DEBUG);
  }
  return 0;
}

static char *prefix_for_log_level(log_level log_level) {
  switch (log_level) {
  case LOG_LEVEL_ERROR:
    return "[ERROR]: ";
  case LOG_LEVEL_WARNING:
    return "[WARNING]: ";
  case LOG_LEVEL_INFO:
    return "[INFO]: ";
  case LOG_LEVEL_DEBUG:
    return "[DEBUG]: ";
  default:
    return "";
  }
}

void log_message(log_level log_level, const char *format, ...) {
  verbosity_level current_verbosity = global_configuration.verbosity_level;

  if (!should_log(log_level, current_verbosity)) {
    return;
  }

  const char *prefix = prefix_for_log_level(log_level);
  FILE *output_stream = stdout;
  va_list args;

  pthread_mutex_lock(&log_mutex);

  fputs(prefix, output_stream);
  va_start(args, format);
  vfprintf(output_stream, format, args);
  va_end(args);
  fputc('\n', output_stream);

  pthread_mutex_unlock(&log_mutex);
}