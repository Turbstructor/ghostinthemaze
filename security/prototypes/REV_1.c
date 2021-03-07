#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define UID 0
#define GID 0

#define R "\e[31m"
#define G "\e[32m"
#define Y "\e[33m"
#define N "\e[39m"
#define LR "\e[91m"
#define LG "\e[92m"

// Maximum 16 hexadecimal digits for KEY
#define KEY 0x9a93ce6d97

// NX bit on, Canary enabled

void penetrate()
{
	long long target;

	fprintf(stdout, "Enter a number to get hint : ");
	fscanf(stdin, "%lld", &target);

	if(target == KEY)
	{
		fprintf(stdout, G "> You made it!" N "\n");

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
		fprintf(stdout, R "> Nah... Try again." N "\n");
	}
}

int main()
{
	penetrate();
	return 0;
}