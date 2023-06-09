#include "file_system.h"
#include "user_interface.h"
#include <cstdio>
#include <dirent.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>
#include <vector>
#include <algorithm>

// Структура для хранения информации о файлах
struct FileInfo {
    char path[1024];
    time_t mod_time;
    off_t size;
};

void create_file(const char *path) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Ошибка: ");
        display_error_message("Не удалось создать файл");
        return;
    }
    fclose(file);
}

bool remove_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;
    char file_path[PATH_MAX];

    dir = opendir(path);
    if (dir == NULL) {
        perror("Ошибка при открытии директории");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        snprintf(file_path, PATH_MAX, "%s/%s", path, entry->d_name);
        if (entry->d_type == DT_DIR) {
            remove_directory(file_path);
        } else {
            remove(file_path);
        }
    }

    closedir(dir);
    if (rmdir(path) != 0) {
        perror("Ошибка при удалении директории");
        return -1;
    }

    return 0;
}

void my_delete(const char *path) {
    if (is_path_a_directory(path)) {
        if (remove_directory(path) != 0) {
            display_error_message("Не удалось удалить директорию");
        }
    } else {
        if (remove(path) != 0) {
            display_error_message("Не удалось удалить файл");
            return;
        }
    }
}


void list_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        display_error_message("Не удалось открыть директорию");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        std::cout << entry->d_name << std::endl;
    }

    closedir(dir);
}

void my_copy(const char *source_path, const char *destination_path) {
    std::ifstream src(source_path, std::ios::binary);
    std::ofstream dst(destination_path, std::ios::binary);

    if (!src) {
        std::cerr << "Ошибка при открытии исходного файла.\n";
        return;
    }

    if (!dst) {
        std::cerr << "Ошибка при открытии целевого файла.\n";
        return;
    }

    dst << src.rdbuf();
}

void move_file(const char *source_path, const char *destination_path) {
    // вызов функции copy, которую мы определили ранее

     my_copy(source_path, destination_path);
     if (remove(source_path) != 0) {
         display_error_message("Ошибка при удалении исходного файла");
     }
}

bool change_directory(const char *path) {
    int result = chdir(path);
    if (result == 0) {
        return true;
    } else {
        display_error_message("Ошибка при смене директории");
        return false;
    }
}

int get_num_files(const char *path) {
    DIR *dir;
    struct dirent *entry;
    int file_count = 0;

    if ((dir = opendir(path)) == NULL) {
        display_error_message("Не удалось открыть директорию");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  // Проверяем, является ли файл регулярным
            file_count++;
        }
    }

    closedir(dir);
    return file_count;
}

int get_file_size(const char *fname) {
    struct stat st;

    if (stat(fname, &st) != 0) {
        display_error_message("Ошибка при получении информации о файле");
        return -1;
    }

    return st.st_size;
}

void create_directory(const char* path) {
    if (mkdir(path, 0777) == -1) {
        display_error_message("Ошибка при создании директории");
    }
}

char* get_file_modification_time(const char *fname) {
    struct stat attr;
    stat(fname, &attr);

    char *mtime = ctime(&attr.st_mtime);
    return mtime;
}

// Функция для сравнения файлов по времени изменения
bool compare_by_time(const FileInfo& a, const FileInfo& b) {
    return a.mod_time > b.mod_time;
}

// Функция для сравнения файлов по размеру
bool compare_by_size(const FileInfo& a, const FileInfo& b) {
    return a.size > b.size;
}

// Функция рекурсивно ищет файлы с заданным именем
void find_files(const char* dir_path, const char* file_name) {
    DIR* dir = opendir(dir_path);

    if (dir == NULL) {
        return;
    }

    struct dirent* entry;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            char sub_dir_path[1024];
            snprintf(sub_dir_path, sizeof(sub_dir_path), "%s/%s", dir_path, entry->d_name);
            find_files(sub_dir_path, file_name);
        } else if (strstr(entry->d_name, file_name) != NULL) {
            printf("%s/%s\n", dir_path, entry->d_name);
        }
    }

    closedir(dir);
}

// Функция для отображения файлов в заданном каталоге, отсортированных по времени изменения или размеру
void list_sorted_files(const char* dir_path, bool sort_by_time) {
    DIR* dir = opendir(dir_path);

    if (dir == NULL) {
        return;
    }

    std::vector<FileInfo> files;
    struct dirent* entry;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char file_path[1024];
            snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);

            struct stat st;
            if (stat(file_path, &st) == 0) {
                FileInfo info;
                strcpy(info.path, file_path);
                info.mod_time = st.st_mtime;
                info.size = st.st_size;
                files.push_back(info);
            }
        }
    }

    closedir(dir);

    // Сортируем файлы
    if (sort_by_time) {
        std::sort(files.begin(), files.end(), compare_by_time);
    } else {
        std::sort(files.begin(), files.end(), compare_by_size);
    }

    // Отображаем отсортированный список файлов
    for (const FileInfo& file : files) {
        printf("%s\n", file.path);
        if (sort_by_time) {
            char mod_time_str[20];
            strftime(mod_time_str, 20, "%Y-%m-%d %H:%M:%S", localtime(&file.mod_time));
            printf("Время изменения: %s\n", mod_time_str);
        } else {
            printf("Размер: %ld байт\n", file.size);
        }
    }
}

bool is_path_a_directory(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        return false;
    } else {
        return S_ISDIR(path_stat.st_mode);
    }
}

const char* current_directory() {
    static char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        return cwd;
    } else {
        return NULL;
    }
}
