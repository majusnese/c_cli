#include "f_data.h"
#include <stdlib.h>
#include <string.h>

void filelist_init(FileList *list) {
  list->count = 0;
  list->capacity = 16; // start small
  list->files = malloc(list->capacity * sizeof(char *));
}

void filelist_add(FileList *list, const char *filename) {
  if (list->count >= list->capacity) {
    list->capacity *= 2;
    list->files = realloc(list->files, list->capacity * sizeof(char *));
  }
  list->files[list->count] = strdup(filename);
  list->count++;
}

void filelist_free(FileList *list) {
  for (size_t i = 0; i < list->count; i++) {
    free(list->files[i]);
  }
  free(list->files);
}
