# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $6, %eax
    movl %eax, -12(%rbp)
    movl $3, %eax
    movl %eax, -16(%rbp)
    movl -12(%rbp), %eax
    andl -16(%rbp), %eax
    movl %eax, -4(%rbp)
    movl $5, %eax
    movl %eax, -20(%rbp)
    movl $2, %eax
    movl %eax, -24(%rbp)
    movl -20(%rbp), %eax
    orl -24(%rbp), %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -28(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -32(%rbp)
    movl -28(%rbp), %eax
    cmpl -32(%rbp), %eax
    setl %al
    movzbl %al, %eax
    popq %rbp
    ret
