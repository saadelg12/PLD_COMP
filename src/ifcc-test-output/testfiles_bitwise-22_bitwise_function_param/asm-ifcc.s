# Fonction avec `return` !
# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Déclaration : result -> -12 (%rbp)
# Avertissement : Variable 'a' déclarée mais jamais utilisée !
# Avertissement : Variable 'b' déclarée mais jamais utilisée !
# Fonction avec `return` !
.globl main
calculate:
    pushq %rbp
    movq %rsp, %rbp
    movl %edi, -4(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -8(%rbp)
    movl $10, %eax
    movl %eax, -12(%rbp)
    movl -8(%rbp), %eax
    addl -12(%rbp), %eax
    popq %rbp
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $13, %eax
    movl %eax, -4(%rbp)
    movl $7, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -16(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -20(%rbp)
    movl -16(%rbp), %eax
    andl -20(%rbp), %eax
    movl %eax, %edi
    call calculate
    movl %eax, -12(%rbp)
    movl -12(%rbp), %eax
    popq %rbp
    ret
