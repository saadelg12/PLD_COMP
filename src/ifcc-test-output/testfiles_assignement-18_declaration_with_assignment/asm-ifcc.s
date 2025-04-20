# Déclaration : b -> -4 (%rbp)
# Déclaration : c -> -8 (%rbp)
# Déclaration : a -> -12 (%rbp)
# Avertissement : Variable 'a' déclarée mais jamais utilisée !
# Avertissement : Variable 'b' déclarée mais jamais utilisée !
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $3, %eax
    movl %eax, -8(%rbp)
    movl %eax, -4(%rbp)
    movl %eax, -12(%rbp)
    movl -8(%rbp), %eax
    popq %rbp
    ret
