# Déclaration : a -> -4 (%rbp)
# Fonction avec `return` !
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
read_car_0:
    call getchar@PLT
    cmp $10, %eax
    je read_car_0
    cvttsd2si %xmm0, %eax
    movl %eax, -4(%rbp)
    movl -4(%rbp), %eax
    movl %eax, -8(%rbp)
    movl $49, %eax
    movl %eax, -12(%rbp)
    movl -8(%rbp), %eax
    cmpl -12(%rbp), %eax
    sete %al
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
    popq %rbp
    ret
