#include "module_handler.h"
#include "f_m_regex.h"

void cleanup_all_resources() { free_regex_matchers(); }