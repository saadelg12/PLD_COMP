# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Déclaration : c -> -12 (%rbp)
# Avertissement : Variable 'a' déclarée mais jamais utilisée !
# Avertissement : Variable 'b' déclarée mais jamais utilisée !
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $1, %eax
    movl %eax, -4(%rbp)
    movl $2, %eax
    movl %eax, -8(%rbp)
    movl $4, %eax
    movl %eax, -12(%rbp)
    movl $3, %eax
    movl %eax, -8(%rbp)
    movl %eax, -12(%rbp)
    movl %eax, -4(%rbp)
    movl -12(%rbp), %eax
    popq %rbp
    ret
