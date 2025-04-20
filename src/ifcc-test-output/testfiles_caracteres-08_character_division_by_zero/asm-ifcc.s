# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $65, %eax
    movl %eax, -4(%rbp)
    movl $0, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    cltd
    idivl -8(%rbp)
    popq %rbp
    ret
