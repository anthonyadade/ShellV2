#include "builtins.h"

int my_cd(char **argv) {
        if (argv[1] && argv[2]){
                printf("Error changing directory: Too many arguments\n");
                return -1;
        }
        if (chdir(argv[1]) == -1) {
                perror("Error changing directory");
                return -1;
        }
        return 0;
}
