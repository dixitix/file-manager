#include "testing.h"
#include "file_system.h"
#include "security.h"
#include "user_interface.h"
#include <unistd.h>
#include <cstdio>
#include <string.h>


void create_big_file(const char *path) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        display_error_message("Не удалось создать файл");
        return;
    }
    for (int i = 0; i < 10000; i++) {  // Создаем большой файл, написав много строк
        fprintf(file, "This is a line in a big file\n");
    }
    fclose(file);
}

void create_small_file(const char *path) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        display_error_message("Не удалось создать файл");
        return;
    }
    fprintf(file, "This is a line in a small file\n");  // Создаем маленький файл, написав одну строку
    fclose(file);
}


void test_find_files() {
    const char* dir_path = "test_dir";
    const char* sub_dir_path = "test_dir/sub_dir";
    const char* file1 = "test_dir/file1.txt";
    const char* file2 = "test_dir/sub_dir/file2.txt";

    // Создаем директории и файлы
    create_directory(dir_path);
    create_directory(sub_dir_path);
    create_file(file1);
    create_file(file2);

    // Ищем файлы с именем "file1.txt"
    find_files(dir_path, "file1.txt");  // должно найти "test_dir/file1.txt"

    // Ищем файлы с именем "file2.txt"
    find_files(dir_path, "file2.txt");  // должно найти "test_dir/sub_dir/file2.txt"

    // Удаляем файлы и директории
    my_delete(file1);
    my_delete(file2);
    my_delete(sub_dir_path);
    my_delete(dir_path);
}

void test_list_sorted_files() {
    const char* dir_path = "test_dir";
    const char* file1 = "test_dir/file1.txt";  // Большой файл, измененный поздно
    const char* file2 = "test_dir/file2.txt";  // Маленький файл, измененный рано

    // Создаем директорию и файлы
    create_directory(dir_path);
    create_big_file(file1);  // Эта функция создает большой файл
    sleep(2);  // Ждем некоторое время
    create_small_file(file2);  // Эта функция создает маленький файл

    // Отображаем файлы, отсортированные по времени изменения
    printf("Files sorted by modification time:\n");
    list_sorted_files(dir_path, true);  // должно отобразить file2, затем file1

    // Отображаем файлы, отсортированные по размеру
    printf("Files sorted by size:\n");
    list_sorted_files(dir_path, false);  // должно отобразить file1, затем file2

    // Удаляем файлы и директорию
    my_delete(file1);
    my_delete(file2);
    my_delete(dir_path);
}

int run_tests() {
    int result = 0;

    // Тестирование функции copy
    const char* source_file = "source_file.txt";
    const char* copied_file = "copied_file.txt";
    create_file(source_file);  // создаем файл для копирования
    my_copy(source_file, copied_file);
    if (!is_accessible(copied_file)) {  // проверяем, что файл скопирован
        printf("Test copy failed!\n");
        result = 1;
    }
    my_delete(source_file);
    my_delete(copied_file);

    // Тестирование функции move_file
    const char* moved_file = "moved_file.txt";
    create_file(source_file);  // создаем файл для перемещения
    move_file(source_file, moved_file);
    if (is_accessible(source_file) || !is_accessible(moved_file)) {  // проверяем, что файл перемещен
        printf("Test move_file failed!\n");
        result = 1;
    }
    my_delete(moved_file);

    // Тестирование функции create_file
    create_file(source_file);
    if (!is_accessible(source_file)) {  // проверяем, что файл создан
        printf("Test create_file failed!\n");
        result = 1;
    }
    my_delete(source_file);

    // Тестирование функции delete_file
    create_file(source_file);  // создаем файл для удаления
    my_delete(source_file);
    if (is_accessible(source_file)) {  // проверяем, что файл удален
        printf("Test delete_file failed!\n");
        result = 1;
    }

    // Тестирование функции create_directory и delete_directory
    const char* dir_path = "test9_dir";
    create_directory(dir_path);
    if (!is_accessible(dir_path)) {  // проверяем, что директория создана
        printf("Test create_directory failed!\n");
        result = 1;
    }
    my_delete(dir_path);
    if (is_accessible(dir_path)) {  // проверяем, что директория удалена
        printf("Test delete_directory failed!\n");
        result = 1;
    }

    // Тестирование функции list_directory
    dir_path = "test17_dir";
    const char* file1 = "test17_dir/file1.txt";
    const char* file2 = "test17_dir/file2.txt";
    create_directory(dir_path);
    if (is_accessible(dir_path) == 0) {
        perror("Ошибка при создании директории");
    }
    create_file(file1);
    create_file(file2);
    int num_files = get_num_files(dir_path);
    if (num_files != 2) {  // проверяем, что в директории два файла
        printf("Test list_directory failed!\n");
        result = 1;
    }
    my_delete(file1);
    my_delete(file2);
    my_delete(dir_path);

    // Тестирование функции change_directory
    dir_path = "test_new_dir";
    create_directory(dir_path);
    if (!change_directory(dir_path)) {  // проверяем, что удалось сменить директорию
        printf("Test change_directory failed!\n");
        result = 1;
    }
    change_directory("..");
    my_delete(dir_path);

    // Тестирование функции get_file_size
    create_file(source_file);
    // предполагается, что файл пустой, поэтому его размер равен нулю
    if (get_file_size(source_file) != 0) {
        printf("Test get_file_size failed!\n");
        result = 1;
    }
    my_delete(source_file);

    //Тестирование функции get_file_modification_time
    create_file(source_file);
    char* mod_time = get_file_modification_time(source_file);
    if (mod_time == NULL || strlen(mod_time) == 0) {
        printf("Test get_file_modification_time failed!\n");
        result = 1;
    }
    my_delete(source_file);

// Тестирование функции is_file_accessible
    if (is_accessible(source_file)) {  // файл уже удален, поэтому не должен быть доступен
        printf("Test is_file_accessible failed!\n");
        result = 1;
    }

//    test_find_files();
//    test_list_sorted_files();

    printf("Everything is ok!");
    return result;
}
