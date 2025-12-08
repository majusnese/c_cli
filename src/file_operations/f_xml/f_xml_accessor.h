#ifndef F_XML_ACCESSOR_H
#define F_XML_ACCESSOR_H
#include "general_types.h"
#include <libxml/tree.h>

xmlNode *get_xml_tag(xmlNode *root, const char *tag_name);
std_return_type load_xml_file(const char *file_path, xmlDocPtr *out_doc,
                              xmlNodePtr *out_root);
#endif