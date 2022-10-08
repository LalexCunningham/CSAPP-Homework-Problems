
int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}

long switch_prob(long x, long n) {
	long result = x;
	switch(n) {
		// Fill in code here
		case (60):
		case (62):
			result = n * 8;
			break;
		case (63):
			result = x >> 3;
			break;
		case (64):
			x= (x << 4) - x
		case (65):
			result = x * x;
		default:
			result = x + 75;
	}

	return result;
}

/*
(gdb) x/6gx 0x4006f8
0x4006f8: 0x00 00 00 00 00 40 05 a1 | 0x00 00 00 00 00 40 05 c3 (0x400700)
0x400708: 0x00 00 00 00 00 40 05 a1 | 0x00 00 00 00 00 40 05 aa	(0x400710)
0x400718: 0x00 00 00 00 00 40 05 b2 | 0x00 00 00 00 00 40 05 bf	(0x400720)

352 Chapter 3 Machine-Level Representation of Programs
long switch_prob(long x, long n)
x in %rdi, n in %rsi
1 0000000000400590 <switch_prob>:
400590: 48 83 ee 3c 			sub $0x3c,%rsi						n - 60	// so n can eq 60, 61, 62, 63, 64, 65
400594: 48 83 fe 05 			cmp $0x5,%rsi						(n > 5)
400598: 77 29 					ja 4005c3 <switch_prob+0x33>		if (n > 5) default direct jump to 4005c3
40059a: ff 24 f5 f8 06 40 00 	jmpq *0x4006f8(,%rsi,8)				jump table
4005a1: 48 8d 04 fd 00 00 00 	lea 0x0(,%rdi,8),%rax				jt(0), jt(2) result = 0 + n * 8
4005a8: 00															noop?
4005a9: c3 						retq
4005aa: 48 89 f8 				mov %rdi,%rax						jt(3)
4005ad: 48 c1 f8 03 			sar $0x3,%rax						
4005b1: c3 						retq
4005b2: 48 89 f8 				mov %rdi,%rax						jt(4)
4005b5: 48 c1 e0 04 			shl $0x4,%rax			
4005b9: 48 29 f8 				sub %rdi,%rax
4005bc: 48 89 c7 				mov %rax,%rdi
4005bf: 48 0f af ff 			imul %rdi,%rdi						jt(5)	result *= result // Falls through
4005c3: 48 8d 47 4b 			lea 0x4b(%rdi),%rax					jt(1)	result = 75 + x 
4005c7: c3 						retq
*/