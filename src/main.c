#include "cli_parser.h"
#include "f_collect.h"
#include "f_data.h"
#include "f_matcher.h"
#include "f_xml_accessor.h"
#include "logger.h"
#include "module_handler.h"
#include <libxml/tree.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  LOG_INFO("Received %d arguments!", argc);
  parse_to_cfg_struct(argc, argv);
  register_extension_matcher(".vttmake");

  FileList vttmake_list = {0};
  std_return_type result =
      find_files("./test/file_operations/test_files", &vttmake_list);

  if (result == STD_RETURN_OK) {
    for (size_t i = 0; i < vttmake_list.count; i++) {
      LOG_INFO("Found .vttmake file: %s", vttmake_list.files[i]);
      // Access XML data from the .vttmake file
      xmlDoc *vttmake_xml = NULL;
      xmlNode *root_element = NULL;
      load_xml_file(vttmake_list.files[i], &vttmake_xml, &root_element);
      xmlFreeDoc(vttmake_xml);
    }
  }

  filelist_free(&vttmake_list);
  cleanup_all_resources();
  return 0;
}