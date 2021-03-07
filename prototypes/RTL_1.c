#include <stdio.h>

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

// NX bit on, Canary disabled

void penetrate()
{
    char buf[BUF_SIZE];

    fprintf(stdout, "Tell me something : ");
    gets(buf);

    fprintf(stdout, Y "> You told... %s, right?" N "\n", buf);
}

int main()
{
    penetrate();
    return 0;
}
