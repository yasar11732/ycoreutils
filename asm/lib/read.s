.include "../linux.inc"
.section .text
.globl read
.type read, @function
# Read a file into a buffer
# argument: file descriptor
# argument: buffer address
# argument: size
read:
    movl 12(%esp), %edx
    movl 8(%esp), %ecx
    movl 4(%esp), %ebx
    movl $SYS_READ, %eax
    int  $LINUX_SYSCALL
    ret
