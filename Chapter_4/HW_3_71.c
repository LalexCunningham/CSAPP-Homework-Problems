/*
Write a function good_echo that reads a line from standard input and writes it to standard output.
Your implementation should work for an input line of arbitrary length. You may use the function
fgets, but you must make sure your function works correctly even when the input line requires more
space than you have allocated in your buffer. You code should also check for error conditions and
return when one is encountered. Refer to the definitions of the standard I/O functions for 
documentation.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 5

int main(int argc, char const *argv[])
{
	good_echo();
	return 0;
}

void good_echo() {
	char buffer[MAXLENGTH];
	char c;

	if (fgets(buffer, MAXLENGTH, stdin) != NULL) {
		puts(buffer);
	}

	return;
}