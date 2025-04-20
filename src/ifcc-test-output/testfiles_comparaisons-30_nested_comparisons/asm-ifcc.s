# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Déclaration : c -> -12 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $5, %eax
    movl %eax, -4(%rbp)
    movl $10, %eax
    movl %eax, -8(%rbp)
    movl $15, %eax
    movl %eax, -12(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -16(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -20(%rbp)
    movl -16(%rbp), %eax
    cmpl -20(%rbp), %eax
    setl %al
    movzbl %al, %eax
    movl %eax, -24(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -28(%rbp)
    movl -12(%rbp), %eax
    movl %eax, -32(%rbp)
    movl -28(%rbp), %eax
    cmpl -32(%rbp), %eax
    setl %al
    movzbl %al, %eax
    movl %eax, -36(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -40(%rbp)
    movl -12(%rbp), %eax
    movl %eax, -44(%rbp)
    movl -40(%rbp), %eax
    cmpl -44(%rbp), %eax
    sete %al
    movzbl %al, %eax
    movl %eax, -48(%rbp)
    movl -36(%rbp), %eax
    orl -48(%rbp), %eax
    movl %eax, -52(%rbp)
    movl -24(%rbp), %eax
    andl -52(%rbp), %eax
    popq %rbp
    ret
