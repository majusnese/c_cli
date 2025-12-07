#ifndef F_COLLECT_H
#define F_COLLECT_H
#include "general_types.h"
#include <stdio.h>

// FILE *find_file_extension(const char *directory_path, size_t *file_count);
std_return_type find_files(const char *directory_path);
#endif