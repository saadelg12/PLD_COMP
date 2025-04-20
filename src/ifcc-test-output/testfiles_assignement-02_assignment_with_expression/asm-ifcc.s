# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Avertissement : Variable 'b' déclarée mais jamais utilisée !
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $3, %eax
    movl %eax, -12(%rbp)
    movl $2, %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    imull -16(%rbp), %eax
    movl %eax, -20(%rbp)
    movl $1, %eax
    movl %eax, -24(%rbp)
    movl -20(%rbp), %eax
    addl -24(%rbp), %eax
    movl %eax, -8(%rbp)
    movl %eax, -4(%rbp)
    movl -4(%rbp), %eax
    popq %rbp
    ret
