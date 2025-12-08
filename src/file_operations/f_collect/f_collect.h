#ifndef F_COLLECT_H
#define F_COLLECT_H
#include "f_data.h"
#include "general_types.h"
#include <stdio.h>

// FILE *find_file_extension(const char *directory_path, size_t *file_count);
/* Find files matching registered matchers and populate the provided list.
   Returns STD_RETURN_OK on success, STD_RETURN_ERROR on failure. */
std_return_type find_files(const char *directory_path, FileList *file_list);
#endif