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

#define MAX_BUFFER_SIZE 32
const char* KEY = "deadbeef";
#define ANOTHER_KEY 0x8f2beefa1067

// NX bit on, Canary disabled

void penetrate()
{
	char target[MAX_BUFFER_SIZE];
	long long another_target;

    fprintf(stdout, "Enter password to acquire hint : ");
	gets(target);

	if(!strcmp(target, KEY))
	{
        fprintf(stdout, G "> Your answer matches with the password given!" N "\n");

        if(another_target == ANOTHER_KEY)
        {
            fprintf(stdout, G "> Second authentication successfully done." N "\n");
            
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

            fprintf(stdout, Y "> Entering sh...\n");
            system("/bin/sh");
            fprintf(stdout, N);
        }
        else
        {
            fprintf(stderr, R "> The another key does NOT match the given password. Second authentication failed." N "\n");
        }
	}
    else
    {
        fprintf(stderr, R "> Your answer does NOT match the given password." N "\n");
    }
}

int main()
{
	penetrate();
	return 0;
}