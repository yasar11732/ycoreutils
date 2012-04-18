.include "../linux.inc"
.section .text
.globl exit
.type exit, @function
# Exit with status code
# argument: status code
exit:
    movl 4(%esp), %ebx
    movl $SYS_EXIT, %eax
    int  $LINUX_SYSCALL
    ret
