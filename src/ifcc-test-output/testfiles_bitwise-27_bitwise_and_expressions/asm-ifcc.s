# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Déclaration : c -> -12 (%rbp)
# Déclaration : d -> -16 (%rbp)
# Déclaration : result -> -20 (%rbp)
# Avertissement : Variable 'a' déclarée mais jamais utilisée !
# Avertissement : Variable 'b' déclarée mais jamais utilisée !
# Avertissement : Variable 'c' déclarée mais jamais utilisée !
# Avertissement : Variable 'd' déclarée mais jamais utilisée !
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $13, %eax
    movl %eax, -4(%rbp)
    movl $7, %eax
    movl %eax, -8(%rbp)
    movl $10, %eax
    movl %eax, -12(%rbp)
    movl $4, %eax
    movl %eax, -16(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -24(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -28(%rbp)
    movl -24(%rbp), %eax
    addl -28(%rbp), %eax
    movl %eax, -32(%rbp)
    movl -12(%rbp), %eax
    movl %eax, -36(%rbp)
    movl -16(%rbp), %eax
    movl %eax, -40(%rbp)
    movl -36(%rbp), %eax
    subl -40(%rbp), %eax
    movl %eax, -44(%rbp)
    movl -32(%rbp), %eax
    andl -44(%rbp), %eax
    movl %eax, -20(%rbp)
    movl -20(%rbp), %eax
    popq %rbp
    ret
