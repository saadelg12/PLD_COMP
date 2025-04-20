# Déclaration : a -> -4 (%rbp)
# Avertissement : Variable 'a' déclarée mais jamais utilisée !
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $42, %eax
    movl %eax, -4(%rbp)
    popq %rbp
    ret
