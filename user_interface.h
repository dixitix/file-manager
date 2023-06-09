#ifndef FILE_MANAGER_USER_INTERFACE_H
#define FILE_MANAGER_USER_INTERFACE_H

void display_welcome_message();
void display_current_directory();
void display_error_message(const char* message);
void display_success_message(const char* message);
void display_list(const char* path);
void display_file_content(const char* path);
void display_file_info(const char* path);
void display_directory_info(const char* path);

#endif //FILE_MANAGER_USER_INTERFACE_H
