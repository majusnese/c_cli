#include "f_collect.h"
#include "f_data.h"
#include "f_matcher.h"
#include "logger.h"
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>

static boolean is_dot_file(const char *filename) {
  return (!strcmp(filename, ".") || !strcmp(filename, ".."));
}

static std_return_type collect_in_dir(const char *directory_path,
                                      FileList *file_list) {
  DIR *dir = opendir(directory_path);
  if (dir == NULL) {
    LOG_ERROR("Failed to open directory: %s", directory_path);
    return STD_RETURN_ERROR;
  }

  struct dirent *entry;
  char full_path[PATH_MAX];

  while ((entry = readdir(dir)) != NULL) {
    if (is_dot_file(entry->d_name)) {
      continue;
    }

    struct stat st;
    char full_entry_path[PATH_MAX];
    snprintf(full_entry_path, PATH_MAX, "%s/%s", directory_path, entry->d_name);
    if (stat(full_entry_path, &st) == -1) {
      LOG_WARNING("Failed to get status of file: %s", full_entry_path);
      continue;
    }

    if (S_ISDIR(st.st_mode)) {
      // Recursively walk into subdirectory
      collect_in_dir(full_entry_path, file_list);
    } else if (S_ISREG(st.st_mode)) {
      // Process regular file
      if (is_file_match(entry->d_name)) {
        filelist_add(file_list, full_entry_path);
      }
    }
  }
  closedir(dir);

  return STD_RETURN_OK;
};

std_return_type find_files(const char *directory_path, FileList *file_list) {
  if (directory_path == NULL) {
    LOG_ERROR("Directory path is NULL");
    return STD_RETURN_ERROR;
  }
  if (file_list == NULL) {
    LOG_ERROR("FileList pointer is NULL");
    return STD_RETURN_ERROR;
  }
  if (total_number_matchers == 0) {
    LOG_WARNING("No file matchers registered; no files will be collected");
    return STD_RETURN_OK;
  }

  filelist_init(file_list);
  std_return_type result = collect_in_dir(directory_path, file_list);
  if (file_list->count == 0) {
    LOG_WARNING("No matching files found in directory: %s", directory_path);
  } else {
    LOG_INFO("Found %zu matching files in directory: %s", file_list->count,
             directory_path);
  }
  if (result == STD_RETURN_OK) {
    for (size_t i = 0; i < file_list->count; i++) {
      LOG_INFO("Collected file: %s", file_list->files[i]);
    }
  }
  return result;
}