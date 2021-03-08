#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main()
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);

    srand(ts.tv_nsec);

    char password[16];
    int random_character;
    int i;

    sprintf(password, "%x", rand() * rand());
    fprintf(stdout, "%s", password);
    
    return 0;
}