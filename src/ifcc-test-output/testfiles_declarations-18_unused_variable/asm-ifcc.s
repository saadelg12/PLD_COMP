# Déclaration : b -> -4 (%rbp)
# Avertissement : Variable 'b' déclarée mais jamais utilisée !
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $0, %eax
    popq %rbp
    ret
