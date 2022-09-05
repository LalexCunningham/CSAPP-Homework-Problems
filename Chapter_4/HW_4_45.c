/*
	A. The code does not do the same thing, as it pushes the value of %rsp AFTER it's decremented
	B. Better would be 

		movq REG, -8(%rsp)
		subq $8, %rsp
*/