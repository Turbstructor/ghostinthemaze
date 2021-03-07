#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define UID 0
#define GID 0

#define R "\e[31m"
#define G "\e[32m"
#define Y "\e[33m"
#define B "\e[34m"
#define N "\e[39m"

#define LR "\e[91m"
#define LG "\e[92m"

int main()
{
    if(setregid(GID, GID))
    {
        perror(R "> setgid failed." N);
        exit(1);
    }
    if(setreuid(UID, UID))
    {
        perror(R "> setuid failed." N);
        exit(1);
    }

    system("echo $(cat .aslr) > /dev/null | tee /proc/sys/kernel/randomize_va_space");
    return 0;
}