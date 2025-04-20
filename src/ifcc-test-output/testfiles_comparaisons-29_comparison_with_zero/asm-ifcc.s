# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $0, %eax
    movl %eax, -4(%rbp)
    movl $0, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    cmpl -8(%rbp), %eax
    sete %al
    movzbl %al, %eax
    popq %rbp
    ret
