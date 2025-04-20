# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $2147483647, %eax
    popq %rbp
    ret
