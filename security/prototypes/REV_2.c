#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define R "\e[31m"
#define G "\e[32m"
#define Y "\e[33m"
#define B "\e[34m"
#define N "\e[39m"
#define LR "\e[91m"
#define LG "\e[92m"

#define UID 0
#define GID 0

#define KEY 0x0

#define XOR_A 0b10101010101010101010101010101010
#define XOR_B 0b01010101010101010101010101010101
#define XOR_C 0b11001100110011001100110011001100
#define XOR_D 0b00110011001100110011001100110011
#define XOR_E 0b11110000111100001111000011110000
#define XOR_F 0b00001111000011110000111100001111

// NX bit on, Canary enabled

void penetrate();
int main()
{
	penetrate();
	return 0;
}

void penetrate()
{
	int a, b, c, d, e, f;
	int xa, xb, xc, xd, xe, xf;

	fprintf(stdout, "Enter 6 numbers to match the password : ");
	fscanf(stdin, "%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);

	xa = a ^ XOR_A;
	xb = b ^ XOR_B;
	xc = c ^ XOR_C;
	xd = d ^ XOR_D;
	xe = e ^ XOR_E;
	xf = f ^ XOR_F;

	if(xa == KEY && xb == KEY && xc == KEY && xd == KEY && xe == KEY && xf == KEY)
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
		fprintf(stderr, R "> Nah... Try again." N "\n");
	}
}