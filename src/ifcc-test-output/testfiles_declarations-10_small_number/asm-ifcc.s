# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $3, %eax
    negl %eax
    popq %rbp
    ret
