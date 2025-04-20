# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Déclaration : result -> -12 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $15, %eax
    movl %eax, -4(%rbp)
    movl $6, %eax
    movl %eax, -8(%rbp)
    movl $0, %eax
    movl %eax, -12(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -16(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -20(%rbp)
    movl -16(%rbp), %eax
    andl -20(%rbp), %eax
    movl %eax, -12(%rbp)
    movl -12(%rbp), %eax
    movl %eax, -24(%rbp)
    movl $9, %eax
    movl %eax, -28(%rbp)
    movl -24(%rbp), %eax
    orl -28(%rbp), %eax
    movl %eax, -12(%rbp)
    movl -12(%rbp), %eax
    popq %rbp
    ret
