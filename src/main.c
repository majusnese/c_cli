#include "cli_parser.h"
#include "f_collect.h"
#include "logger.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  LOG_INFO("Received %d arguments!", argc);
  parse_to_cfg_struct(argc, argv);
  files_by_regex("./test/file_operations/test_files", ".*\\.txt$");
  return 0;
}