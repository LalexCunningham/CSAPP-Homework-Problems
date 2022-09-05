

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}

long cread(long *xp) {
	return (xp ? *xp : 0);
}

long creat_alt(long *xp) {
	long val = 0;
	if (xp) {
		val = *xp;
	}
	return val;
}

// Answer from internet:
long creat_alt_answ(long *xp) {
	return (!xp ? 0 : *xp);
}

/*
xp in %rdi
cread:
	movq	(%rdi), %rax
	testq	%rdi, %rdi
	movl 	$0, %edx
	cmove	%rdx, %rax
	ret
*/