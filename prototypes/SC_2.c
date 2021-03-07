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

#define BUF_SIZE 64

// NX bit off, Canary disabled

void penetrate()
{
    char buf[BUF_SIZE];

    if (setregid(GID, GID))
    {
        perror(Y "> setgid failed." N);
        exit(1);
    }
    if (setreuid(UID, UID))
    {
        perror(Y "> setuid failed." N);
        exit(1);
    }

    fprintf(stdout, "Tell me something : ");
    gets(buf);

    fprintf(stdout, Y "> You told %s, and that\'s at %p" N "\n", buf, buf);
    fprintf(stdout, Y "> Environment variable " B "\"SHELLCODE\"" Y " at %p" N "\n", getenv("SHELLCODE"));
}

int main()
{
    penetrate();
    return 0;
}