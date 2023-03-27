#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	for(int i = 0; i < 10; i++) {
		sleep(1);
		printf("Printing\n");
	}
	exit(1);
	return 1;
}