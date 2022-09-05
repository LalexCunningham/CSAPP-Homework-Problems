#include <stdio.h>

int main(int argc, char const *argv[])
{
	long arr[3] = {3, 2, 1};

	printf("%ld\n", *arr);
	printf("%ld\n", *(arr+1+1));
	//printf("%ld\n", *arr+1+1);

	bubble_p(arr, 3);


	printf("Sorted:\n");
	for (int i = 0; i < 3; i++) {
		printf("%ld,", arr[i]);
	}
	printf("\n");
	return 0;
}

/* Bubble sort: Pointer Version */

void bubble_p(long *data, long count) {
	long i, last;
	for (last = count-1; last > 0; last--) {
		for (i = 0; i < last; i++) {
			printf("%lu, %lu, %lu, %lu;\n", (data+i), (data+i+1), *(data+i), *(data+i+1));
			if(*(data+i+1) < *(data+i)) {
				long t = *(data+i+1);
				*(data+i+1) = *(data+i);
				*(data+i) = t;
			}
		}
	}
}