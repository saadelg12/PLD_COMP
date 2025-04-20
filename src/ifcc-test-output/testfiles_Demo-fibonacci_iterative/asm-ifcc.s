# Déclaration : a -> -8 (%rbp)
# Déclaration : b -> -12 (%rbp)
# Déclaration : i -> -16 (%rbp)
# Déclaration : fib -> -20 (%rbp)
# Fonction avec `return` !
# Déclaration : num -> -4 (%rbp)
# Fonction avec `return` !
.globl main
fibonacci:
    pushq %rbp
    movq %rsp, %rbp
    movl %edi, -4(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -24(%rbp)
    movl $1, %eax
    movl %eax, -28(%rbp)
    movl -24(%rbp), %eax
    cmpl -28(%rbp), %eax
    setle %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label2
    jnz label1
label1:
    movl -4(%rbp), %eax
    popq %rbp
    ret
    jmp label2
label2:
    movl $0, %eax
    movl %eax, -8(%rbp)
    movl $1, %eax
    movl %eax, -12(%rbp)
    movl $2, %eax
    movl %eax, -16(%rbp)
    movl $0, %eax
    movl %eax, -20(%rbp)
    jmp label3
label3:
    movl -16(%rbp), %eax
    movl %eax, -32(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -36(%rbp)
    movl -32(%rbp), %eax
    cmpl -36(%rbp), %eax
    setle %al
    movzbl %al, %eax
    testl %eax, %eax
      jz label5
    jnz label4
label4:
    movl -8(%rbp), %eax
    movl %eax, -40(%rbp)
    movl -12(%rbp), %eax
    movl %eax, -44(%rbp)
    movl -40(%rbp), %eax
    addl -44(%rbp), %eax
    movl %eax, -20(%rbp)
    movl -12(%rbp), %eax
    movl %eax, -8(%rbp)
    movl -20(%rbp), %eax
    movl %eax, -12(%rbp)
    movl -16(%rbp), %eax
    movl %eax, -48(%rbp)
    movl $1, %eax
    movl %eax, -52(%rbp)
    movl -48(%rbp), %eax
    addl -52(%rbp), %eax
    movl %eax, -16(%rbp)
    jmp label3
label5:
    movl -20(%rbp), %eax
    popq %rbp
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $10, %eax
    movl %eax, -4(%rbp)
    movl -4(%rbp), %eax
    movl %eax, %edi
    call fibonacci
    popq %rbp
    ret
