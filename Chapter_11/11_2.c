#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "./../csapp.h"

int solution(int argc, char **argv);

int main(int argc, char **argv)
{
	solution(argc, argv);
	/*
	if (argc < 1) {
		printf("Not enough arguments\n");
		return -1;
	}

	// Parse input
	const char *inputStr = argv[1];
	short inputValue = 0;

	if (inputStr[0] == '0' && (inputStr[1] == 'X' || inputStr[1] == 'x')) {
		inputStr += 2; // Ignore preamble
	}

	int inputDigits = strlen(inputStr);
	if (inputDigits > 4) {
		printf("%d\n", inputDigits);
		return -1; // Not a 16 bit input
	}

	// Convert
	uint16_t input = (uint16_t) strtol(argv[1], NULL, 16);

	uint16_t output = htons(input);

	printf("Out: %d\n", output);
	return 0;

	*/
}

// Solution

int solution(int argc, char **argv) {
	struct in_addr inaddr;
	uint16_t addr;
	char buf[MAXBUF];

	if (argc != 2) {
		fprintf(stderr, "usage: %s <hex number>\n", argv[0]);
		exit(0);
	}

	sscanf(argv[1], "%x", &addr);
	inaddr.s_addr = htons(addr);

	if (!inet_ntop(AF_INET, &inaddr, buf, MAXBUF))
		unix_error("inet_ntop");
	printf("%s\n", buf);
}
