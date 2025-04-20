# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Déclaration : c -> -12 (%rbp)
# Déclaration : result -> -16 (%rbp)
# Avertissement : Variable 'a' déclarée mais jamais utilisée !
# Avertissement : Variable 'b' déclarée mais jamais utilisée !
# Avertissement : Variable 'c' déclarée mais jamais utilisée !
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $10, %eax
    movl %eax, -4(%rbp)
    movl $7, %eax
    movl %eax, -8(%rbp)
    movl $3, %eax
    movl %eax, -12(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -20(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -24(%rbp)
    movl -12(%rbp), %eax
    movl %eax, -28(%rbp)
    movl -24(%rbp), %eax
    imull -28(%rbp), %eax
    movl %eax, -32(%rbp)
    movl -20(%rbp), %eax
    xorl -32(%rbp), %eax
    movl %eax, -16(%rbp)
    movl -16(%rbp), %eax
    popq %rbp
    ret
