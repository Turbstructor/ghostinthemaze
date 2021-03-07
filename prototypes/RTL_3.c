// AFTER => bof8.c
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

#define BUF_SIZE 8

// NX bit on, Canary disabled

char * binsh = "/bin/sh";

void penetrate()
{
    char buf[BUF_SIZE];

    if (setregid(GID, GID)) {
        perror("setgid");
        exit(1);
    }
    
    if (setreuid(UID, UID)) {
        perror("setuid");
        exit(1);
    }
    fprintf(stdout, Y "> system located at        %p" N "\n", system);
    fprintf(stdout, Y "> /bin/sh string stored at %p" N "\n", binsh);

    fprintf(stdout, "Tell me something : ");
    gets(buf);
    fprintf(stdout, Y "> You told... %s, right?" N "\n", buf);
}

int main()
{
    penetrate();
    return 0;
}
