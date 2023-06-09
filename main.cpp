#include "command_line.h"
#include "testing.h"

int main(int argc, char *argv[]) {
    //run_tests();
    
    int result = 0;
    result = parse_arguments(argc, argv);
    return result;
}
