#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"
#define MAXLINELENGTH 50

jmp_buf buf;

char *tfgets(char *str, int n, FILE *stream);
void sigAlarmHandler(int sig);

int main(int argc, char const *argv[])
{
	char *buffer = malloc(MAXLINELENGTH);

	printf("Stdin: %d\n", stdin);

	if (tfgets(buffer, MAXLINELENGTH, stdin) != NULL) {
		printf("Read val: %s\n", buffer);
	} else {
		printf("tfgets returned NULL\n");
	}

	return 0;
}

char *tfgets(char *str, int n, FILE *stream) {
	Signal(SIGALRM, sigAlarmHandler);
	Alarm(5);
	if (!setjmp(buf)) {
		return fgets(str, n, stream);
	} else {
		return NULL;
	}
}

void sigAlarmHandler(int sig) {
	printf("Caught Alarm Signal\n");
	fflush(stdin);
	longjmp(buf, 1);
}