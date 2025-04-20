# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $5, %eax
    negl %eax
    movl %eax, -4(%rbp)
    movl $3, %eax
    negl %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    cmpl -8(%rbp), %eax
    setl %al
    movzbl %al, %eax
    popq %rbp
    ret
