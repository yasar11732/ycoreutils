.include "../linux.inc"
.section .text
.globl open
.type open, @function
# Open a file
# argument: address of filename
# argument: flags
# argument: mode
open:
    movl 12(%esp), %edx
    movl 8(%esp), %ecx
    movl 4(%esp), %ebx
    movl $SYS_OPEN, %eax
    int  $LINUX_SYSCALL
    ret
