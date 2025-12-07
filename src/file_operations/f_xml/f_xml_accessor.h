#ifndef F_XML_ACCESSOR_H
#define F_XML_ACCESSOR_H
#include "general_types.h"
#include <libxml/tree.h>

char *get_xml_element_value(const char *xml_content, const char *element_name);
std_return_type load_xml_file(const char *file_path, xmlDocPtr *out_doc,
                              xmlNodePtr *out_root);
#endif