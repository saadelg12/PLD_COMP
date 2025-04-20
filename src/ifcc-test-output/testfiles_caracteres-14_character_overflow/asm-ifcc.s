# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $65, %eax
    movl %eax, -4(%rbp)
    movl $300, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    addl -8(%rbp), %eax
    popq %rbp
    ret
