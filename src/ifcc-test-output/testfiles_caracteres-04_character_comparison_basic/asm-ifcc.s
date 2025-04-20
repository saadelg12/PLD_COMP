# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movl $97, %eax
    movl %eax, -4(%rbp)
    movl $90, %eax
    movl %eax, -8(%rbp)
    movl -4(%rbp), %eax
    cmpl -8(%rbp), %eax
    setg %al
    movzbl %al, %eax
    popq %rbp
    ret
