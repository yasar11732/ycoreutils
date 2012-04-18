.include "../linux.inc"
.section .text
.globl close
.type close, @function
# close a file
# argument: file descriptor
close:
    movl 4(%esp), %ebx
    movl $SYS_CLOSE, %eax
    int  $LINUX_SYSCALL
    ret
