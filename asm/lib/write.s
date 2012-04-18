.include "../linux.inc"
.section .text
.globl write
.type write, @function
# Write buffer to a file
# argument: file descriptor
# argument: buffer address
# argument: count
write:
    movl 12(%esp), %edx
    movl 8(%esp), %ecx
    movl 4(%esp), %ebx
    movl $SYS_WRITE, %eax
    int  $LINUX_SYSCALL
    ret
