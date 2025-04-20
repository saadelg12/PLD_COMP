# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $9, %eax
    movl %eax, -4(%rbp)
    movl $4, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    cmpl -8(%rbp), %eax
    setge %al
    movzbl %al, %eax
    popq %rbp
    ret
