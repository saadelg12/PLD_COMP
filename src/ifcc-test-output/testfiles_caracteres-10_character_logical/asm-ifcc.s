# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $65, %eax
    movl %eax, -4(%rbp)
    movl $66, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    andl -8(%rbp), %eax
    movl %eax, -12(%rbp)
    movl $67, %eax
    cmpl $0, %eax
    movl $0, %eax
    sete %al
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    orl -16(%rbp), %eax
    popq %rbp
    ret
