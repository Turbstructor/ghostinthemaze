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

#define BUF_SIZE 64

#define KEY 0x0

// NX bit on, Canary disabled

void penetrate()
{
	char target[BUF_SIZE];
	int hans;

	fprintf(stdout, "Tell me something... : ");
	gets(target);

	if(hans == KEY)
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

		fprintf(stdout, Y "> Entering sh...\n");
		system("/bin/sh");
		fprintf(stdout, N);
	}
	else
	{
		fprintf(stderr, R "> Nah... Try again." N "\n");
	}
}

int main()
{
	penetrate();
	return 0;
}