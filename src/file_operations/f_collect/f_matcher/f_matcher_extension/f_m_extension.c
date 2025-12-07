#include "f_m_extension.h"

static char *get_file_extension(const char *filename) {
  char *dot = strrchr(filename, '.');
  if (!dot || dot == filename) {
    // no extension found
    return "";
  }
  return dot + 1;
}
