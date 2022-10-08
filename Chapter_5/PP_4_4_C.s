	.file	"PP_4_4_C.c"
# GNU C17 (Debian 8.3.0-6) version 8.3.0 (x86_64-linux-gnu)
#	compiled by GNU C version 8.3.0, GMP version 6.1.2, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.20-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -imultiarch x86_64-linux-gnu PP_4_4_C.c -mtune=generic
# -march=x86-64 -Og -fverbose-asm
# options enabled:  -fPIC -fPIE -faggressive-loop-optimizations
# -fasynchronous-unwind-tables -fauto-inc-dec -fchkp-check-incomplete-type
# -fchkp-check-read -fchkp-check-write -fchkp-instrument-calls
# -fchkp-narrow-bounds -fchkp-optimize -fchkp-store-bounds
# -fchkp-use-static-bounds -fchkp-use-static-const-bounds
# -fchkp-use-wrappers -fcombine-stack-adjustments -fcommon -fcompare-elim
# -fcprop-registers -fdefer-pop -fdelete-null-pointer-checks
# -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-types
# -fforward-propagate -ffp-int-builtin-inexact -ffunction-cse -fgcse-lm
# -fgnu-runtime -fgnu-unique -fguess-branch-probability -fident -finline
# -finline-atomics -fipa-profile -fipa-pure-const -fipa-reference
# -fira-hoist-pressure -fira-share-save-slots -fira-share-spill-slots
# -fivopts -fkeep-static-consts -fleading-underscore -flifetime-dse
# -flto-odr-type-merging -fmath-errno -fmerge-constants
# -fmerge-debug-strings -fomit-frame-pointer -fpeephole -fplt
# -fprefetch-loop-arrays -freg-struct-return -freorder-blocks
# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
# -fsched-stalled-insns-dep -fschedule-fusion -fsemantic-interposition
# -fshow-column -fshrink-wrap -fshrink-wrap-separate -fsigned-zeros
# -fsplit-ivs-in-unroller -fsplit-wide-types -fssa-backprop -fstdarg-opt
# -fstrict-volatile-bitfields -fsync-libcalls -ftoplevel-reorder
# -ftrapping-math -ftree-builtin-call-dce -ftree-ccp -ftree-ch
# -ftree-coalesce-vars -ftree-copy-prop -ftree-cselim -ftree-dce
# -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre
# -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
# -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop
# -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr -ftree-ter
# -funit-at-a-time -funwind-tables -fverbose-asm -fzero-initialized-in-bss
# -m128bit-long-double -m64 -m80387 -malign-stringops
# -mavx256-split-unaligned-load -mavx256-split-unaligned-store
# -mfancy-math-387 -mfp-ret-in-387 -mfxsr -mglibc -mieee-fp
# -mlong-double-80 -mmmx -mno-sse4 -mpush-args -mred-zone -msse -msse2
# -mstv -mtls-direct-seg-refs -mvzeroupper

	.text
	.globl	rproduct
	.type	rproduct, @function
rproduct:
.LFB1:
	.cfi_startproc
# PP_4_4_C.c:16: 	if (count <= 1) {
	cmpq	$1, %rsi	#, count
	jle	.L3	#,
# PP_4_4_C.c:15: long rproduct(long *start, long count) {
	pushq	%rbx	#
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
# PP_4_4_C.c:19: 	return *start * rproduct(start+1, count-1);
	movq	(%rdi), %rbx	# *start_9(D), _1
# PP_4_4_C.c:19: 	return *start * rproduct(start+1, count-1);
	subq	$1, %rsi	#, tmp94
	addq	$8, %rdi	#, tmp95
	call	rproduct	#
# PP_4_4_C.c:19: 	return *start * rproduct(start+1, count-1);
	imulq	%rbx, %rax	# _1, <retval>
# PP_4_4_C.c:20: }
	popq	%rbx	#
	.cfi_def_cfa_offset 8
	ret	
.L3:
	.cfi_restore 3
# PP_4_4_C.c:17: 		return 1;
	movl	$1, %eax	#, <retval>
# PP_4_4_C.c:20: }
	ret	
	.cfi_endproc
.LFE1:
	.size	rproduct, .-rproduct
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	subq	$24, %rsp	#,
	.cfi_def_cfa_offset 32
# PP_4_4_C.c:7: 	data[0] = 12;
	movq	$12, (%rsp)	#, data
# PP_4_4_C.c:8: 	data[1] = 13;
	movq	$13, 8(%rsp)	#, data
# PP_4_4_C.c:10: 	val = (int) rproduct(data, 2);
	movq	%rsp, %rdi	#, tmp90
	movl	$2, %esi	#,
	call	rproduct	#
# PP_4_4_C.c:13: }
	movl	$0, %eax	#,
	addq	$24, %rsp	#,
	.cfi_def_cfa_offset 8
	ret	
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 8.3.0-6) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
