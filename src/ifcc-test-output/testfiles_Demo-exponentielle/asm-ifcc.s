# Déclaration : base -> -4 (%rbp)
# Déclaration : exp -> -8 (%rbp)
# Déclaration : result -> -12 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $2, %eax
    movl %eax, -4(%rbp)
    movl $5, %eax
    movl %eax, -8(%rbp)
    movl $1, %eax
    movl %eax, -12(%rbp)
    jmp label1
label1:
    movl -8(%rbp), %eax
    movl %eax, -16(%rbp)
    movl $0, %eax
    movl %eax, -20(%rbp)
    movl -16(%rbp), %eax
    cmpl -20(%rbp), %eax
    setg %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label3
    jnz label2
label2:
    movl -12(%rbp), %eax
    movl %eax, -24(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -28(%rbp)
    movl -24(%rbp), %eax
    imull -28(%rbp), %eax
    movl %eax, -12(%rbp)
    movl -8(%rbp), %eax
    movl %eax, -32(%rbp)
    movl $1, %eax
    movl %eax, -36(%rbp)
    movl -32(%rbp), %eax
    subl -36(%rbp), %eax
    movl %eax, -8(%rbp)
    jmp label1
label3:
    movl -12(%rbp), %eax
    popq %rbp
    ret
