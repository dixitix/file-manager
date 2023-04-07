#include "user_interface.h"

#include <stdio.h>

void display_welcome_message() {
    printf("Добро пожаловать в файловый менеджер!\n");
}

void display_current_directory(const char* path) {
    printf("Текущая директория: %s\n", path);
}

void display_command_result(const char* result) {
    printf("%s\n", result);
}

void display_error_message(const char* message) {
    printf("Ошибка: %s\n", message);
}

void display_success_message(const char* message) {
    printf("Успешно: %s\n", message);
}

void display_list(const char* path) {
    printf("Список файлов в директории %s:\n", path);
    // код для отображения списка файлов в директории
}

void display_file_content(const char* path) {
    printf("Содержимое файла %s:\n", path);
    // код для отображения содержимого файла
}

void display_file_info(const char* path) {
    printf("Информация о файле %s:\n", path);
    // код для отображения информации о файле
}
