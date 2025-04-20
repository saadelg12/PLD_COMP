# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Déclaration : c -> -12 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $10, %eax
    movl %eax, -8(%rbp)
    movl $0, %eax
    movl %eax, -12(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    movl %eax, -20(%rbp)
    movl -16(%rbp), %eax
    cltd
    idivl -20(%rbp)
    movl %eax, -4(%rbp)
    movl -4(%rbp), %eax
    popq %rbp
    ret
