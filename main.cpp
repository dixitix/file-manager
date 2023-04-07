#include <iostream>

#include "command_line.h"

int main(int argc, char *argv[]) {
    int result;
    result = parse_arguments(argc, argv);
    return result;
}
