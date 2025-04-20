# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Avertissement : Variable 'b' déclarée mais jamais utilisée !
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $1, %eax
    movl %eax, -4(%rbp)
    movl $3, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    popq %rbp
    ret
