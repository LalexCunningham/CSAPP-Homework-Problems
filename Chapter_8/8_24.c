#include "csapp.h"
#define N 5

int dummyFunction(int i) {
	return 1+i;
}

int main(int argc, char const *argv[])
{
	int status, i;
	pid_t pid;

	/* Parent creates N children */
	for (i = 0; i < N; i++) {
		if((pid = Fork()) == 0) {
			/* Child Process */
			
			/* Get the address of a function (in read only segment) */
			int (*functionPointer)(int) = &dummyFunction;
			
			/* Cast pointer to integer type */
			int *integerPointer = (int*) functionPointer;

			/* Write value to pointer address */
			*integerPointer = 0;

			exit(100+i);
		}
	}

	/* Parent reaps N children in no particular order */
	while ((pid = waitpid(-1, &status, 0)) > 0) {
		if (WIFEXITED(status)) {
			printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			// Retrieve Signal info
			int signalNumber = WTERMSIG(status);
			const char signalInfoBuffer[80];
			psignal(signalNumber, signalInfoBuffer);

			printf("child %d terminated abnormally by signal %d: %s\n", pid, signalNumber, signalInfoBuffer);
		} else {
			printf("child %d terminated abnormally\n", pid);
		}
	}

	/* The only normal termination is if there are no more children */
	if (errno != ECHILD) {
		unix_error("waitpid error");
	}

	return 0;
}