#ifndef FILE_MANAGER_FILE_SYSTEM_H
#define FILE_MANAGER_FILE_SYSTEM_H

void my_copy(const char *source_path, const char *destination_path);
void move_file(const char *source_path, const char *destination_path);
void create_file(const char *path);
void my_delete(const char *path);
void create_directory(const char* path);
void list_directory(const char *path);
bool change_directory(const char *path);
int get_num_files(const char *path);
int get_file_size(const char *fname);
char* get_file_modification_time(const char *fname);
void list_sorted_files(const char* dir_path, bool sort_by_time);
void find_files(const char* dir_path, const char* file_name);
bool is_path_a_directory(const char *path);
const char* current_directory();

#endif // FILE_MANAGER_FILE_SYSTEM_H
