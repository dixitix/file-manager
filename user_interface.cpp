#include "user_interface.h"
#include "file_system.h"

#include <cstdio>

void display_welcome_message() {
    printf("Добро пожаловать в файловый менеджер!\n");
    printf("Для получения справки введите fm help\n");
}

void display_current_directory() {
    printf("Текущая директория: %s\n", current_directory());
}

void display_error_message(const char* message) {
    printf("Ошибка: %s\n", message);
}

void display_success_message(const char* message) {
    printf("Успешно: %s\n", message);
}

void display_list(const char* path) {
    if (*path == '.') {
        printf("Список файлов в директории %s:\n", current_directory());
    } else {
        printf("Список файлов в директории %s:\n", path);
    }
    list_directory(path);
}

void display_file_content(const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return;
    }

    char ch;
    printf("Содержимое файла %s:\n", path);
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}

void display_file_info(const char *path) {
    printf("Информация о файле %s:\n", path);

    int size = get_file_size(path);
    printf("Размер файла: %d байт\n", size);

    char* mod_time = get_file_modification_time(path);
    printf("Время последнего изменения файла: %s\n", mod_time);
}

void display_directory_info(const char* path) {
    printf("Информация о директории %s:\n", path);

    int num_files = get_num_files(path);
    printf("Количество файлов в директории: %d\n", num_files);

    char* mod_time = get_file_modification_time(path);
    printf("Время последнего изменения файла: %s\n", mod_time);
}
