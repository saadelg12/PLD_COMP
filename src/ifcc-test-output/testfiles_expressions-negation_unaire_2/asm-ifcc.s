# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $3, %eax
    movl %eax, -4(%rbp)
    movl $3, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    subl -8(%rbp), %eax
    movl %eax, -12(%rbp)
    movl $2, %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    imull -16(%rbp), %eax
    cmpl $0, %eax
    movl $0, %eax
    sete %al
    popq %rbp
    ret
