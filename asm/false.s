.include "linux.inc"
.section .text
.globl _start
_start:
	movl $SYS_EXIT, %eax
	movl $1 , %ebx
	int  $LINUX_SYSCALL 
