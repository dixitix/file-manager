#ifndef FILE_MANAGER_FILE_SYSTEM_H
#define FILE_MANAGER_FILE_SYSTEM_H

void copy_file(const char* source_path, const char* destination_path);
void move_file(const char* source_path, const char* destination_path);
void create_file(const char* path);
void delete_file(const char* path);
void create_directory(const char* path);
void delete_directory(const char* path);
void list_directory(const char* path);
bool change_directory(const char* path);
int get_num_files(const char* path);
int get_file_size(const char* fname);
const char* get_file_modification_time(const char* fname);

#endif //FILE_MANAGER_FILE_SYSTEM_H
