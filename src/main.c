#include "cli_parser.h"
#include "f_collect.h"
#include "f_matcher.h"
#include "logger.h"
#include "module_handler.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  LOG_INFO("Received %d arguments!", argc);
  parse_to_cfg_struct(argc, argv);
  register_regex_matcher(".*\\.mytestextension$");
  find_files("./test/file_operations/test_files");

  cleanup_all_resources();
  return 0;
}