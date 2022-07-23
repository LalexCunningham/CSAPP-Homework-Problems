#include <stdio.h>

long fact_do_goto(long n);

int main(int argc, char const *argv[])
{
	printf("%d\n", fact_do_goto(12));
	printf("%d\n", fact_do_goto(13));
	printf("%d\n", fact_do_goto(14));
	return 0;
}

long fact_do_goto(long n) {
	long result = 1;
	loop:
		result *= n;
		n = n - 1;
		if(n > 1)
			goto loop;
	return result;
}