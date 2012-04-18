.include "linux.inc"
.section .bss
    .equ B_SIZE, 512
    .lcomm BUFFER, B_SIZE
.section .text
.globl _start
_start:
    movl %esp, %ebp
    subl $4, %esp # save spot for fd
    movl $2, %edi
loop_begin:
    cmpl (%ebp), %edi
    jg   loop_end
    movl (%ebp, %edi, 4), %eax # save pointer on eax
    cmpb $'-', (%eax) # if doesn't start with - open it
    jne  open_file
    cmpb $0, 1(%eax)
    jne  open_file
    movl $STDIN, -4(%ebp)
    jmp  read_write_loop
open_file:
    pushl $0666
    pushl $0 # readonly
    pushl %eax
    call  open
    addl  $12, %esp
    cmpl  $0, %eax
    jl    error_exit
    movl  %eax, -4(%ebp)
read_write_loop:
    pushl $B_SIZE
    pushl $BUFFER
    pushl -4(%ebp)
    call  read
    addl  $12, %esp # restore stack
    pushl %eax
    pushl $BUFFER
    pushl $STDOUT
    call  write
    addl  $8, %esp
    popl  %eax
    cmpl  $B_SIZE, %eax # didn't read enough
    jl    end_read_write_loop
    jmp read_write_loop
end_read_write_loop: 
    cmpl $STDIN, -4(%ebp)
    je   continue # continue if reading from stdin
    pushl -4(%ebp)
    call  close
    addl  $4, %esp 
continue:
    incl  %edi
    jmp loop_begin
loop_end:
    pushl $0
    call  exit

error_exit:
    pushl %eax
    call  exit
