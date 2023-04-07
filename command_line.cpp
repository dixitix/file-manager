#include "command_line.h"
#include "user_interface.h"
#include "file_system.h"

#include <string.h>

int parse_arguments(int argc, char *argv[]) {
    // Проверяем, есть ли какие-либо аргументы
    if (argc == 1) {
        display_welcome_message();
        return 0;
    }

    // Проверяем, какой аргумент передан и выполняем соответствующее действие
    if (strcmp(argv[1], "ls") == 0) {
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
            display_file_info(argv[2]);
        } else {
            display_error_message("Файл не указан.");
        }
    } else if (strcmp(argv[1], "cp") == 0) {
        if (argc >= 4) {
            copy_file(argv[2], argv[3]);
        } else {
            display_error_message("Неправильное использование команды cp. Используйте cp source_file destination_file");
        }
    } else if (strcmp(argv[1], "mv") == 0) {
        if (argc >= 4) {
            move_file(argv[2], argv[3]);
        } else {
            display_error_message("Неправильное использование команды mv. Используйте mv source_file destination_file");
        }
    } else if (strcmp(argv[1], "rm") == 0) {
        if (argc >= 3) {
            delete_file(argv[2]);
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
    } else {
        display_error_message("Неизвестная команда. Доступные команды: ls, cd, cat, info, cp, mv, rm, mkdir, touch");
    }
    return 0;
}
