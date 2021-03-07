#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define UID 0
#define GID 0

#define R "\e[31m"
#define G "\e[32m"
#define Y "\e[33m"
#define B "\e[34m"
#define N "\e[39m"
#define LR "\e[91m"
#define LG "\e[92m"

#define BUF_SIZE 128

// NX bit OFF, Canary disabled

void penetrate(char* argument){
    char buf[BUF_SIZE];

    if (setregid(GID, GID))
    {
        perror(R "> setgid failed." N);
        exit(1);
    }
    if (setreuid(UID, UID))
    {
        perror(R "> setuid failed." N);
        exit(1);
    }

    strcpy(buf, argument);
    fprintf(stdout, Y "> First argument at %p, content is %s" N "\n", buf, buf);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, R "> Error: at least one argument is required." N "\n");
        exit(1);
    }

    penetrate(argv[1]);
    return 0;
}
