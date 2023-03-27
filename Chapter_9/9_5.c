#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	FILE *fp;

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Error reading file: %s\n", strerror(errno));
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	size_t size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char *start = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fp->_fileno, 0);

	printf("################# File #################\n%s", start);

	return 0;
}