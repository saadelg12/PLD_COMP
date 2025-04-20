# Déclaration : a -> -4 (%rbp)
# Déclaration : b -> -8 (%rbp)
# Déclaration : c -> -12 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $10, %eax
    movl %eax, -16(%rbp)
    movl $5, %eax
    movl %eax, -20(%rbp)
    movl -16(%rbp), %eax
    cmpl -20(%rbp), %eax
    setg %al
    movzbl %al, %eax
    movl %eax, -4(%rbp)
    movl $7, %eax
    movl %eax, -24(%rbp)
    movl $3, %eax
    movl %eax, -28(%rbp)
    movl -24(%rbp), %eax
    cmpl -28(%rbp), %eax
    setl %al
    movzbl %al, %eax
    movl %eax, -8(%rbp)
    movl $8, %eax
    movl %eax, -32(%rbp)
    movl $8, %eax
    movl %eax, -36(%rbp)
    movl -32(%rbp), %eax
    cmpl -36(%rbp), %eax
    setge %al
    movzbl %al, %eax
    movl %eax, -40(%rbp)
    movl $9, %eax
    movl %eax, -44(%rbp)
    movl $10, %eax
    movl %eax, -48(%rbp)
    movl -44(%rbp), %eax
    cmpl -48(%rbp), %eax
    setle %al
    movzbl %al, %eax
    movl %eax, -52(%rbp)
    movl -40(%rbp), %eax
    addl -52(%rbp), %eax
    movl %eax, -12(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -56(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -60(%rbp)
    movl -56(%rbp), %eax
    addl -60(%rbp), %eax
    movl %eax, -64(%rbp)
    movl -12(%rbp), %eax
    movl %eax, -68(%rbp)
    movl -64(%rbp), %eax
    addl -68(%rbp), %eax
    popq %rbp
    ret
