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
  register_extension_matcher(".xml");

  FileList xml_list = {0};
  std_return_type result =
      find_files("./test/file_operations/test_files", &xml_list);

  if (result == STD_RETURN_OK) {
    for (size_t i = 0; i < xml_list.count; i++) {
      LOG_INFO("Found .xml file: %s", xml_list.files[i]);
      xmlDoc *xml_doc = NULL;
      xmlNode *root_element = NULL;
      load_xml_file(xml_list.files[i], &xml_doc, &root_element);
      LOG_INFO("Age element of test file: %s",
               get_xml_tag(root_element, "age")->children->content);
      xmlFreeDoc(xml_doc);
    }
  }

  filelist_free(&xml_list);
  cleanup_all_resources();
  return 0;
}