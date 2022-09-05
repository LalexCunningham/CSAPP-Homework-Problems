long rproduct(long *start, long count);

int main(int argc, char const *argv[]) {
	long data[2];
	int val;

	data[0] = 12;
	data[1] = 13;

	val = (int) rproduct(data, 2);

	return 0;
}

long rproduct(long *start, long count) {
	if (count <= 1) {
		return 1;
	}
	return *start * rproduct(start+1, count-1);
}