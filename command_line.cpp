#include "command_line.h"
#include "file_system.h"
#include "user_interface.h"

#include <string.h>

void display_help() {
    printf("Файловый менеджер\n");
    printf("Использование:\n");
    printf("  fm cp <source_path> <destination_path>   : Копировать файлы/папки\n");
    printf("  fm mv <source_path> <destination_path>   : Переместить файлы/папки\n");
    printf("  fm rm <file_path>                        : Удалить выбранные файлы/папки\n");
    printf("  fm mkdir <directory_path>                : Создать новую папку\n");
    printf("  fm touch <file_path>                     : Создать новый файл\n");
    printf("  fm ls <directory_path>                   : Просмотр файловой системы\n");
    printf("  fm cd <directory_path>                   : Переход между директориями\n");
    printf("  fm cat <file_path>                       : Просмотр содержимого файла\n");
    printf("  fm info <file_path>                      : Просмотр информации о файле\n");
    printf("  fm grep <file_name>                      : Поиск файлов\n");
    printf("  fm ls -t <directory_path>                : Сортировка файлов по времени создания\n");
    printf("  fm ls -S <directory_path>                : Сортировка файлов по размеру\n");
}

int parse_arguments(int argc, char *argv[]) {
    // Проверяем, есть ли какие-либо аргументы
    if (argc == 1) {
        display_welcome_message();
        return 0;
    }

    // Проверяем, какой аргумент передан и выполняем соответствующее действие
    if (strcmp(argv[1], "help") == 0) {
        display_help();
    } else if (strcmp(argv[1], "ls") == 0) {
        if (argc >= 3) {
            display_list(argv[2]);
        } else {
            display_list(".");
        }
    } else if (strcmp(argv[1], "cd") == 0) {
        if (argc >= 3) {
            if (!change_directory(argv[2])) {
                display_error_message("Ошибка при смене каталога.");
            } else {
                display_success_message("Каталог успешно изменен.");
            }
        } else {
            display_error_message("Каталог не указан.");
        }
    } else if (strcmp(argv[1], "cat") == 0) {
        if (argc >= 3) {
            display_file_content(argv[2]);
        } else {
            display_error_message("Файл не указан.");
        }
    } else if (strcmp(argv[1], "info") == 0) {
        if (argc >= 3) {
            if (is_path_a_directory(argv[1])) {
                display_directory_info(argv[1]);
            } else {
                display_file_info(argv[1]);
            }
        } else {
            display_error_message("Файл не указан.");
        }
    } else if (strcmp(argv[1], "cp") == 0) {
        if (argc >= 4) {
            my_copy(argv[2], argv[3]);
        } else {
            display_error_message("Неправильное использование команды cp. "
                                  "Используйте cp source_file destination_file");
        }
    } else if (strcmp(argv[1], "mv") == 0) {
        if (argc >= 4) {
            move_file(argv[2], argv[3]);
        } else {
            display_error_message("Неправильное использование команды mv. "
                                  "Используйте mv source_file destination_file");
        }
    } else if (strcmp(argv[1], "rm") == 0) {
        if (argc >= 3) {
            my_delete(argv[2]);
        } else {
            display_error_message("Файл не указан.");
        }
    } else if (strcmp(argv[1], "mkdir") == 0) {
        if (argc >= 3) {
            create_directory(argv[2]);
        } else {
            display_error_message("Каталог не указан.");
        }
    } else if (strcmp(argv[1], "touch") == 0) {
        if (argc >= 3) {
            create_file(argv[2]);
        } else {
            display_error_message("Файл не указан.");
        }
    } else if (strcmp(argv[1], "grep") == 0 && argc == 3) {
        find_files(".", argv[2]);
    } else if (strcmp(argv[1], "ls") == 0 && argc == 4) {
        if (strcmp(argv[2], "-t") == 0) {
            list_sorted_files(argv[3], true);
        } else if (strcmp(argv[2], "-S") == 0) {
            list_sorted_files(argv[3], false);
        }
    } else if (strcmp(argv[1], "cur_d") == 0) {
        display_current_directory();
    } else {
        display_error_message("Неизвестная команда. Введите fm help, чтобы посмотреть список доступных команд");
    }
    return 0;
}
