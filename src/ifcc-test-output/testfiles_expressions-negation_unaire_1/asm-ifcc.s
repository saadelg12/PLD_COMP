# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $0, %eax
    cmpl $0, %eax
    movl $0, %eax
    sete %al
    popq %rbp
    ret
