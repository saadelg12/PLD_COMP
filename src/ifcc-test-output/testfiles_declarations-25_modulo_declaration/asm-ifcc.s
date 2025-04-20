# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $17, %eax
    movl %eax, -12(%rbp)
    movl $5, %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    cltd
    idivl -16(%rbp)
    movl %edx, %eax 
    movl %eax, -4(%rbp)
    movl $20, %eax
    movl %eax, -20(%rbp)
    movl $6, %eax
    movl %eax, -24(%rbp)
    movl -20(%rbp), %eax
    cltd
    idivl -24(%rbp)
    movl %edx, %eax 
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -28(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -32(%rbp)
    movl -28(%rbp), %eax
    imull -32(%rbp), %eax
    popq %rbp
    ret
