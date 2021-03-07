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
    int key;
    
    fprintf(stdout, "Enter number 1337 to open the safe : ");
    fscanf(stdin, "%d", &key);

    if(key == 1337)
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
		fprintf(stderr, R "> Nah... Have faith. Try again." N "\n");
	}
    return 0;
}