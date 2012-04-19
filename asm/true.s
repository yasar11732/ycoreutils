.include "linux.inc"
.section .text
.globl _start
_start:
    xorl %eax, %eax
    incl %eax
	xorb %bl, %bl
	int  $LINUX_SYSCALL 
