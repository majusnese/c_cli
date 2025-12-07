#include "cli_parser.h"
#include "logger.h"
#include <string.h>

static std_return_type handle_verbosity_level(char *argument_value) {
  if (strcmp(argument_value, "silent") == 0) {
    global_configuration.verbosity_level = VERBOSITY_SILENT;
    LOG_INFO("Verbosity set to SILENT");
  } else if (strcmp(argument_value, "normal") == 0) {
    global_configuration.verbosity_level = VERBOSITY_NORMAL;
    LOG_INFO("Verbosity set to NORMAL");
  } else if (strcmp(argument_value, "verbose") == 0) {
    global_configuration.verbosity_level = VERBOSITY_VERBOSE;
    LOG_INFO("Verbosity set to VERBOSE");
  } else if (strcmp(argument_value, "debug") == 0) {
    global_configuration.verbosity_level = VERBOSITY_DEBUG;
    LOG_INFO("Verbosity set to DEBUG");
  } else {
    LOG_ERROR("Invalid verbosity level specified");
    return STD_RETURN_ERROR;
  }
  return STD_RETURN_OK;
}

static std_return_type handle_help() {
  char *help_message =
      "Usage: cli_tool [OPTIONS]\n"
      "Options:\n"
      "  -h, --help            Show this help message and exit\n"
      "  -v, --verbosity LEVEL Set verbosity level (silent, normal, verbose, "
      "debug)\n";
  LOG_INFO("%s", help_message);
  return STD_RETURN_OK;
}

std_return_type parse_to_cfg_struct(int argc, char *argv[]) {
  if (argc == 1) {
    return handle_help();
  }

  std_return_type return_value = STD_RETURN_OK;
  int valid_arguments_count = 0;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
      // if help is requested immediately handle it and exit processing
      return_value = handle_help();
      break;
    }

    if (strcmp(argv[i], "--verbosity") == 0 || strcmp(argv[i], "-v") == 0) {
      if (i + 1 < argc) {
        i += 1;
        return_value = handle_verbosity_level(argv[i]);
        if (return_value == STD_RETURN_OK) {
          valid_arguments_count += 1;
        }
      } else {
        LOG_WARNING("No verbosity level specified after --verbosity/-v");
      }
      continue;
    }
  }

  if (valid_arguments_count == 0 && return_value == STD_RETURN_OK) {
    LOG_WARNING("No valid command line arguments were provided");
    return handle_help();
  }
  return return_value;
}