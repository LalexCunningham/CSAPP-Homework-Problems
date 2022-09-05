	.file	"PP_4_4.c"
# GNU C17 (Debian 8.3.0-6) version 8.3.0 (x86_64-linux-gnu)
#	compiled by GNU C version 8.3.0, GMP version 6.1.2, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.20-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -imultiarch x86_64-linux-gnu PP_4_4.c -mtune=generic
# -march=x86-64 -fverbose-asm
# options enabled:  -fPIC -fPIE -faggressive-loop-optimizations
# -fasynchronous-unwind-tables -fauto-inc-dec -fchkp-check-incomplete-type
# -fchkp-check-read -fchkp-check-write -fchkp-instrument-calls
# -fchkp-narrow-bounds -fchkp-optimize -fchkp-store-bounds
# -fchkp-use-static-bounds -fchkp-use-static-const-bounds
# -fchkp-use-wrappers -fcommon -fdelete-null-pointer-checks
# -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-types
# -ffp-int-builtin-inexact -ffunction-cse -fgcse-lm -fgnu-runtime
# -fgnu-unique -fident -finline-atomics -fira-hoist-pressure
# -fira-share-save-slots -fira-share-spill-slots -fivopts
# -fkeep-static-consts -fleading-underscore -flifetime-dse
# -flto-odr-type-merging -fmath-errno -fmerge-debug-strings -fpeephole
# -fplt -fprefetch-loop-arrays -freg-struct-return
# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
# -fsched-stalled-insns-dep -fschedule-fusion -fsemantic-interposition
# -fshow-column -fshrink-wrap-separate -fsigned-zeros
# -fsplit-ivs-in-unroller -fssa-backprop -fstdarg-opt
# -fstrict-volatile-bitfields -fsync-libcalls -ftrapping-math -ftree-cselim
# -ftree-forwprop -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
# -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop
# -ftree-reassoc -ftree-scev-cprop -funit-at-a-time -funwind-tables
# -fverbose-asm -fzero-initialized-in-bss -m128bit-long-double -m64 -m80387
# -malign-stringops -mavx256-split-unaligned-load
# -mavx256-split-unaligned-store -mfancy-math-387 -mfp-ret-in-387 -mfxsr
# -mglibc -mieee-fp -mlong-double-80 -mmmx -mno-sse4 -mpush-args -mred-zone
# -msse -msse2 -mstv -mtls-direct-seg-refs -mvzeroupper

	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$48, %rsp	#,
	movl	%edi, -36(%rbp)	# argc, argc
	movq	%rsi, -48(%rbp)	# argv, argv
# PP_4_4.c:7: 	data[0] = 12;
	movq	$12, -32(%rbp)	#, data
# PP_4_4.c:8: 	data[1] = 13;
	movq	$13, -24(%rbp)	#, data
# PP_4_4.c:10: 	val = (int) rproduct(data, 2);
	leaq	-32(%rbp), %rax	#, tmp90
	movl	$2, %esi	#,
	movq	%rax, %rdi	# tmp90,
	call	rproduct	#
# PP_4_4.c:10: 	val = (int) rproduct(data, 2);
	movl	%eax, -4(%rbp)	# _1, val
# PP_4_4.c:12: 	return 0;
	movl	$0, %eax	#, _7
# PP_4_4.c:13: }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	rproduct
	.type	rproduct, @function
rproduct:
.LFB1:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$24, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)	# start, start
	movq	%rsi, -32(%rbp)	# count, count
# PP_4_4.c:16: 	if (count <= 1) {
	cmpq	$1, -32(%rbp)	#, count
	jg	.L4	#,
# PP_4_4.c:17: 		return 1;
	movl	$1, %eax	#, _5
	jmp	.L5	#
.L4:
# PP_4_4.c:19: 	return *start * rproduct(start+1, count-1);
	movq	-24(%rbp), %rax	# start, tmp93
	movq	(%rax), %rbx	# *start_10(D), _1
# PP_4_4.c:19: 	return *start * rproduct(start+1, count-1);
	movq	-32(%rbp), %rax	# count, tmp94
	leaq	-1(%rax), %rdx	#, _2
	movq	-24(%rbp), %rax	# start, tmp95
	addq	$8, %rax	#, _3
	movq	%rdx, %rsi	# _2,
	movq	%rax, %rdi	# _3,
	call	rproduct	#
# PP_4_4.c:19: 	return *start * rproduct(start+1, count-1);
	imulq	%rbx, %rax	# _1, _5
.L5:
# PP_4_4.c:20: }
	addq	$24, %rsp	#,
	popq	%rbx	#
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1:
	.size	rproduct, .-rproduct
	.ident	"GCC: (Debian 8.3.0-6) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
