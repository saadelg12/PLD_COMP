# Déclaration : a -> -4 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $0, %eax
    movl %eax, -4(%rbp)
    movl -4(%rbp), %eax
    cmpl $0, %eax
    movl $0, %eax
    sete %al
    movl %eax, -8(%rbp)
    movl $1, %eax
    movl %eax, -12(%rbp)
    movl -8(%rbp), %eax
    cmpl -12(%rbp), %eax
    sete %al
    movzbl %al, %eax
    popq %rbp
    ret
