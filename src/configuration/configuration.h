#ifndef CONFIGURATION_H
#define CONFIGURATION_H

typedef enum verbosity_level {
  VERBOSITY_SILENT = 0,
  VERBOSITY_NORMAL = 1,
  VERBOSITY_VERBOSE = 2,
  VERBOSITY_DEBUG = 3,
} verbosity_level;

typedef struct cli_tool_configuration {
  verbosity_level verbosity_level;
} cli_tool_configuration;

extern cli_tool_configuration global_configuration;
#endif