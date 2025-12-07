#include "cli_parser.h"
#include "logger.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  LOG_INFO("Received %d arguments!\n", argc);
  parse_to_cfg_struct(argc, argv);
  return 0;
}