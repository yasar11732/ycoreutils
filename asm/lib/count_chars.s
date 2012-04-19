.include "../linux.inc"
.section .text
.globl count_chars
.type count_chars, @function
# Count number of characters in a null terminated string
# argument: address of string
count_chars:
    xorl  %eax, %eax # will be our counter, and index!
    movl  4(%esp), %ebx # strings address
loop_start:
    cmpb $0, (%ebx, %eax,1)
    je   loop_end
    incl %eax
    jmp loop_start
loop_end:
    ret
