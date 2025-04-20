# Déclaration : max -> -4 (%rbp)
# Déclaration : min -> -8 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $2147483647, %eax
    movl %eax, -4(%rbp)
    movl $2147483648, %eax
    negl %eax
    movl %eax, -8(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -12(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    cmpl -16(%rbp), %eax
    setl %al
    movzbl %al, %eax
    popq %rbp
    ret
