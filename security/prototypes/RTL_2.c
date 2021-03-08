// AFTER => bof10.c
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

void penetrate()
{
    char buf[BUF_SIZE] = {'\0'};
    memset(buf, 0, sizeof(buf));

    fprintf(stdout, Y "> printf() address : %p" N "\n", printf);

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

    unsigned short mistake = -128;
    fprintf(stdout, "Tell me something : ");
    fgets(buf, mistake, stdin);

    fprintf(stdout, Y "> You told... %s, right?" N "\n", buf);
}

int main()
{
    penetrate();
    return 0;
}
