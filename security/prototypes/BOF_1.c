#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define UID 0
#define GID 0

#define R "\e[31m"
#define G "\e[32m"
#define Y "\e[33m"
#define B "\e[34m"
#define N "\e[39m"
#define LR "\e[91m"
#define LG "\e[92m"

// NX bit on, Canary disabled

int main(int argc, char *argv[])
{
    FILE *fp;
    char filename[64];
    char this_filename[64]; // ./hint_slot_#*
    int i = 1;

    fprintf(stdout, "Enter argv[0] to open all password files : ");
    gets(this_filename);
    fprintf(stdout, "%s\n", argv[0]);

    if(strcmp(this_filename, argv[0]))
    {
        fprintf(stderr, R "> Your answer does not match argv[0], failed to authenticate." N "\n");
        exit(1);
    }

    for(; i <= 5; i++)
    {
        sprintf(filename, "/home/roomE%d/slot%d.key", i, i);
        fp = fopen(filename, "r");

        if(fp == NULL) break;
    }

    if(i > 5)
    {
        fprintf(stderr, R "> All files required should be open, but the program failed to do it." N "\n");
        exit(2);
    }
    else
    {
        fprintf(stdout, G "> Yup, you made it." N "\n");

        if(setregid(GID, GID))
        {
            perror(R "> setgid failed." N);
            exit(3);
        }
        if(setreuid(UID, UID))
        {
            perror(R "> setuid failed." N);
            exit(3);
        }

        fprintf(stdout, Y "> Entering sh...\n");
        system("/bin/sh");
        fprintf(stdout, N);
    }

    return 0;
}