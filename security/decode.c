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

#define SLOT_FILE ".lock_slots"

int main()
{
	int menu;
	char password[6][33];
	char filename[65];

	int is_unlocked[6] = {1, 1, 1, 1, 1, 1};
	int lock_status = 0;
	
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

	// Check for password files
	for(i = 1; i <= 5; i++)
	{
		sprintf(filename, "/home/sectorE/roomE%d/slot%d.key", i, i);
		fp = fopen(filename, "r");

		if(fp == NULL)
		{
			fprintf(stderr, R "Error: failed to read file %s" N "\n", filename);
			exit(3);
		}
		
		fscanf(fp, "%s", password[i]);
		fclose(fp);
	}
	
	// Check for file about slots
	lock_status = -1;
	fp = fopen(SLOT_FILE, "rb");
	if(fp != NULL)
	{
		for(i = 1; i <= 5; i++)
		{
			fscanf(fp, "%d", &is_unlocked[i]);
			if(is_unlocked[i] != -1) lock_status = 1; 
		}
	}
	
	fclose(fp);

	// for(i = 1; i <= 5; i++) fprintf(stdout, "%s\n", password[i]);
	
	if(lock_status == -1)
	{
		fprintf(stderr, LR "The lock has been completely engaged; you cannot try to disable it anymore.\n");
		fprintf(stderr, "All saved data will be lost, passwords will be changed and you have to restart this program." N "\n");

		system("./re-initialize.sh");
		exit(127);
	}

	do
	{
		lock_status = 1;
		fprintf(stdout, "Current lock status:\n");
		for(i = 1; i <= 5; i++)
		{
			fprintf(stdout, "\tSlot #%d : ", i);
			if(is_unlocked[i] != 0)
			{
				if(is_unlocked[i] == 1) fprintf(stdout, R "Engaged" N);
				else fprintf(stdout, LR "Enforced" N);
				lock_status = 0;
			}
			else fprintf(stdout, LG "Disengaged" N);
			fprintf(stdout, "\n");
		}

		if(lock_status)
		{
			fprintf(stdout, B "Congratulations! All slots unlocked, and you have passed my stage." N "\n");
			break;
		}
		
		fprintf(stdout, "Enter slot to try (1 ~ 5) (6 to quit) : ");
		fscanf(stdin, "%d", &n);

		if(n == 6) break;
		else if(n < 1 || n > 6)
			fprintf(stderr, R "Invalid range of slot number. Try again with numbers in range [1, 5]." N "\n");

		else if(is_unlocked[n] == 0) fprintf(stderr, Y "The slot #%d is already unlocked. Try again with different one." N "\n", n);
		else
		{
			fprintf(stdout, "Enter password to unlock slot #%d : ", n);
			fscanf(stdin, "%s", password[0]);
			if(strcmp(password[0], password[n]))
			{
				fprintf(stderr, R "Incorrect password for the slot #%d, slot enforced." N "\n", n);
				if(is_unlocked[n] == 1) is_unlocked[n] = -1;
				else
				{
					fprintf(stderr, LR "You failed to unlock the enforced slot. Full lock engaged.\n");
					fprintf(stderr, "Run the same program again to re-initialize the rooms." N "\n");
					is_unlocked[1] = is_unlocked[2] = is_unlocked[3] = is_unlocked[4] = is_unlocked[5] = -1;
					break;		
				}
			}
			else
			{
				is_unlocked[n] = 0;
				fprintf(stdout, G "Correct password, slot #%d disengaged." N "\n", n);
			}
		}

		fprintf(stdout, "\n");
	}while(1);

	fp = fopen(SLOT_FILE, "wb");
	fprintf(fp, "%d %d %d %d %d", is_unlocked[1], is_unlocked[2], is_unlocked[3], is_unlocked[4], is_unlocked[5]);
	fclose(fp);

	fprintf(stdout, "Shutting down...\n");

	return 0;
}
