#include "f_xml_accessor.h"
#include "logger.h"

std_return_type load_xml_file(const char *file_path, xmlDocPtr *out_doc,
                              xmlNodePtr *out_root) {
  if (file_path == NULL || out_doc == NULL || out_root == NULL) {
    LOG_ERROR("Invalid arguments to load_xml_file");
    return STD_RETURN_ERROR;
  }
  xmlDoc *doc = NULL;
  xmlNode *root_element = NULL;
  LIBXML_TEST_VERSION
  doc = xmlReadFile(file_path, NULL, 0);
  if (doc == NULL) {
    LOG_ERROR("Failed to parse %s!", file_path);
    return STD_RETURN_ERROR;
  }
  root_element = xmlDocGetRootElement(doc);
  if (root_element == NULL) {
    LOG_ERROR("Empty XML document: %s", file_path);
    xmlFreeDoc(doc);
    return STD_RETURN_ERROR;
  }
  *out_root = root_element;
  *out_doc = doc;
  LOG_INFO("Successfully loaded XML file: %s", file_path);
  LOG_DEBUG("Root element: %s", root_element->name);
  return STD_RETURN_OK;
}