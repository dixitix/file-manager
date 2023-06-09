#include "security.h"
#include <unistd.h>

int is_accessible(const char *path) {
    if (access(path, F_OK) == -1) {
        return 0;  // Файл недоступен
    } else {
        return 1;  // Файл доступен
    }
}
