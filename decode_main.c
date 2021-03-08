#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define R "\e[31m"
#define G "\e[32m"
#define Y "\e[33m"
#define B "\e[34m"
#define N "\e[39m"

#define LR "\e[91m"
#define LG "\e[92m"

const char* passwords[] = {"dfz", "abc", "kjdap4", "faus12", "bruh"};
const char* hints[] = {"I protect.", "I\'m not well known.", "I\'m paradoxical.", "I like math.", "I have 2 vowels on my name."};

#define SLOT_FILE ".lock_slots"

int main()
{
	int menu;

	int is_unlocked[5] = {0, 0, 0, 0, 0};
	int lock_status = 0;

	char password[16];
	
	FILE *fp;
	int i, n;
	
	// Take root privilege first
	if(setregid(0, 0) != 0)
	{
		perror(R "Error: setgid failed" N);
		exit(1);
	}
	if(setreuid(0, 0) != 0)
	{
		perror(R "Error: setuid failed" N);
		exit(2);
	}
	
	// Check for file about slots
	lock_status = 0;
	fp = fopen(SLOT_FILE, "rb");
	if(fp != NULL)
	{
		for(i = 0; i < 5; i++)
		{
			fscanf(fp, "%d", &is_unlocked[i]);
		}
	}
	
	fclose(fp);

	do
	{
		lock_status = 0;
		fprintf(stdout, "Current lock status:\n");
		for(i = 0; i < 5; i++)
		{
			fprintf(stdout, "\tSlot #%d : ", (i + 1));
			if(is_unlocked[i] != 1)
			{
				fprintf(stdout, R "Engaged" N);
				lock_status = 1;
			}
			else fprintf(stdout, LG "Disengaged" N);
			fprintf(stdout, "\n");
		}

		if(!lock_status)
		{
			fprintf(stdout, B "Congratulations! All slots unlocked, you can go outside." N "\n");
			fprintf(stdout, B "Password for user \'outside\' : \'password\'" N "\n");
			break;
		}
		
		fprintf(stdout, "Enter slot to try (1 ~ 5) (6 to quit) : ");
		fscanf(stdin, "%d", &n);

		if(n == 6) break;
		else if(n < 1 || n > 6)
			fprintf(stderr, R "Invalid range of slot number. Try again with numbers in range [1, 5]." N "\n");

		else if(is_unlocked[n - 1] == 1) fprintf(stderr, Y "The slot #%d is already unlocked. Try again with different one." N "\n", n);
		else
		{
			fprintf(stdout, "Enter password to unlock slot #%d : ", n);
			fscanf(stdin, "%s", password);
			if(strcmp(password, passwords[n - 1]))
				fprintf(stderr, R "Incorrect password for the slot #%d, try again." N "\n", n);
			else
			{
				is_unlocked[n - 1] = 1;
				fprintf(stdout, G "Correct password, slot #%d disengaged." N "\n", n);
			}
		}

		fprintf(stdout, "\n");
	}while(1);

	fp = fopen(SLOT_FILE, "wb");
	fprintf(fp, "%d %d %d %d %d", is_unlocked[0], is_unlocked[1], is_unlocked[2], is_unlocked[3], is_unlocked[4]);
	fclose(fp);

	fprintf(stdout, "Shutting down...\n");

	return 0;
}
