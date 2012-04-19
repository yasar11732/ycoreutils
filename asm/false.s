.include "linux.inc"
.section .text
.globl _start
_start:
    xorl %eax, %eax
    incl %eax
    movb $1, %bl
	int  $LINUX_SYSCALL 
