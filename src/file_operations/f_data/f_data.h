#ifndef F_DATA_H
#define F_DATA_H

#include <stddef.h>

typedef struct {
  char **files;
  size_t count;
  size_t capacity;
} FileList;

void filelist_init(FileList *list);
void filelist_add(FileList *list, const char *filename);
void filelist_free(FileList *list);
#endif