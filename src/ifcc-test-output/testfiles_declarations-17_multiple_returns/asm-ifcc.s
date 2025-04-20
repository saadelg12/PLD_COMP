# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $5, %eax
    popq %rbp
    ret
    movl $10, %eax
    popq %rbp
    ret
